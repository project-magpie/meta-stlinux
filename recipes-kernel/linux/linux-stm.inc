inherit kernel siteinfo
DESCRIPTION = "Linux kernel from stlinux"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-stm:"



KEEPUIMAGE = "true"
KTAG = "stlinux24_${STM_PATCH_STR}"
INC_PR = "r1"

# Quirk for udev greater or equal 141
UDEV_GE_141 ?= "0"

KBRANCH = "stmicro"

SRC_URI = "git://git.stlinux.com/stm/linux-sh4-2.6.32.y.git;protocol=git;branch=stmicro \
           file://${MACHINE}_defconfig \
           file://st-coprocessor.h \
"
S = "${WORKDIR}/git"
PARALLEL_MAKEINST = ""

do_configure () {
	sed -i "s#^\(CONFIG_EXTRA_FIRMWARE_DIR=\).*#\1\"${STAGING_DIR_HOST}/lib/firmware\"#" .config;
        yes '' | oe_runmake oldconfig
}

do_configure_prepend() {
	rm -f ${S}/.config || true
   	cp ${WORKDIR}/${MACHINE}_defconfig ${S}/.config
}

do_install_append() {
	kerneldir=${D}${KERNEL_SRC_PATH}
	if [ -f include/linux/bounds.h ]; then
		mkdir -p $kerneldir/include/linux
                cp include/linux/bounds.h $kerneldir/include/linux/bounds.h
        fi
        if [ -f include/asm-sh/machtypes.h ]; then
		mkdir -p $kerneldir/include/asm-sh
		cp include/asm-sh/machtypes.h $kerneldir/include/asm-sh
	fi
	install -d ${D}${includedir}/linux	
   	install -m 644 ${WORKDIR}/st-coprocessor.h ${D}${includedir}/linux
}


FILES_kernel-dev += "${includedir}/linux"

do_configure_append() {
        if test -e scripts/Makefile.fwinst ; then
		sed -i -e "s:-m0644:-m 0644:g" scripts/Makefile.fwinst
	fi
}

# bitbake.conf only prepends PARALLEL make in tasks called do_compile, which isn't the case for compile_modules
# So explicitly enable it for that in here
EXTRA_OEMAKE = "${PARALLEL_MAKE} "

do_install_append() {
	oe_runmake headers_install INSTALL_HDR_PATH=${D}${exec_prefix}/src/linux-${KERNEL_VERSION} ARCH=$ARCH
}

PACKAGES =+ "kernel-headers"
FILES_kernel-headers = "${exec_prefix}/src/linux*"


## Automatically depend on lzop-native if CONFIG_KERNEL_LZO is enabled
python () {
    try:
        defconfig = bb.fetch2.localpath('file://defconfig', d)
    except bb.fetch2.FetchError:
        return

    try:
        configfile = open(defconfig)
    except IOError:
        return

    if 'CONFIG_KERNEL_LZO=y\n' in configfile.readlines():
        depends = d.getVar('DEPENDS', False)
        d.setVar('DEPENDS', depends + ' lzop-native')
}


