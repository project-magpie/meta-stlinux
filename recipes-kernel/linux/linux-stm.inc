inherit kernel siteinfo
DESCRIPTION = "Linux kernel from stlinux"
SECTION = "kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-stm:"

KEEPUIMAGE = "true"
KTAG = "stlinux24_${STM_PATCH_STR}"
INC_PR = "r3"

# Quirk for udev greater or equal 141
UDEV_GE_141 ?= "0"

KBRANCH = "project-magpie"

SRC_URI = "git://github.com/project-magpie/linux-sh4-2.6.32.y.git;protocol=https;branch=${KBRANCH} \
           file://defconfig_spark7111 \
           file://defconfig_spark7162 \
           file://st-coprocessor.h \
           file://linux-sh4-spark7162_setup_stm24_0211-magpie.patch \
"
S = "${WORKDIR}/git"
PARALLEL_MAKEINST = ""

# KERNEL_VERSION = "${@get_kernelversion('${WORKDIR}/git-7111')}"

do_configure() {
	cd ${WORKDIR}/git
	if test -e scripts/Makefile.fwinst ; then
		sed -i -e "s:-m0644:-m 0644:g" scripts/Makefile.fwinst
	fi
	# ugly... this has no business in do_configure...
	rm -fr ${WORKDIR}/git-*
	ln -s git ${WORKDIR}/git-7111
	cp -al ${WORKDIR}/git ${WORKDIR}/git-7162
	for i in 7111 7162; do
		bbnote "changing into ${WORKDIR}/git-$i"
		cd ${WORKDIR}/git-$i
		# we'll only install 7111 config in ${STAGING_DIR_HOST}, so the configs
		# need to be sufficiently similar, differ only in really board specific things...
		rm -f .config
		sed "s#^\(CONFIG_EXTRA_FIRMWARE_DIR=\).*#\1\"${STAGING_DIR_HOST}/lib/firmware\"#" < ${WORKDIR}/defconfig_spark$i > .config
		yes '' | oe_runmake oldconfig
	done
}

do_compile() {
	for i in 7162 7111; do
		bbnote "changing into ${WORKDIR}/git-$i"
		cd ${WORKDIR}/git-$i
		kernel_do_compile
	done
}

do_compile_kernelmodules() {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS MACHINE
	for i in 7162 7111; do
		bbnote "changing into ${WORKDIR}/git-$i"
		cd ${WORKDIR}/git-$i
		if (grep -q -i -e '^CONFIG_MODULES=y$' .config); then
			oe_runmake modules CC="${KERNEL_CC}" LD="${KERNEL_LD}"
		else
			bbnote "no modules to compile"
		fi
	done
}

do_install() {
	for i in 7162 7111; do
		bbnote "changing into ${WORKDIR}/git-$i"
		cd ${WORKDIR}/git-$i
		kernel_do_install
		mkdir ${D}/lib/modules/$i
		mv ${D}/lib/modules/${KERNEL_VERSION} ${D}/lib/modules/$i
		cp -a ${D}/usr/src/kernel/.config ${D}/usr/src/kernel/.config-$i
		# do not copy to -7111...
		[ $i = 7111 ] && break
		cp -a ${D}/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${KERNEL_VERSION} ${D}/${KERNEL_IMAGEDEST}/${KERNEL_IMAGETYPE}-${KERNEL_VERSION}-$i
		for j in System.map config vmlinux Module.symvers; do
			[ -e ${D}/boot/$j-${KERNEL_VERSION} ] || continue
			cp -a ${D}/boot/$j-${KERNEL_VERSION} ${D}/boot/$j-${KERNEL_VERSION}-$i
		done
	done
	# $PWD is git-7111
	kerneldir=${D}${KERNEL_SRC_PATH}
	if [ -f include/linux/bounds.h ]; then
		mkdir -p $kerneldir/include/linux
		cp include/linux/bounds.h $kerneldir/include/linux/bounds.h
	fi
	if [ -f include/asm-sh/machtypes.h ]; then
		mkdir -p $kerneldir/include/asm-sh
		cp include/asm-sh/machtypes.h $kerneldir/include/asm-sh
	fi
	oe_runmake headers_install INSTALL_HDR_PATH=${D}${exec_prefix}/src/linux-${KERNEL_VERSION} ARCH=$ARCH
	cd ${WORKDIR}/git

	install -d ${D}${includedir}/linux	
   	install -m 644 ${WORKDIR}/st-coprocessor.h ${D}${includedir}/linux

	cd ${D}/lib/modules
	for i in `find 7111 -name '*.ko'`; do
		j=7162${i#7111}
		[ -e $j ] || continue
		A="`md5sum < $i`"
		B="`md5sum < $j`"
		[ "$A" = "$B" ] || continue
		bbnote "$i == $j => hardlink"
		rm $j
		ln $i $j # hardlink!
	done
}

do_deploy() {
	for i in 7162 7111; do
		bbnote "changing into ${WORKDIR}/git-$i"
		cd ${WORKDIR}/git-$i
		kernel_do_deploy
		[ x$i = x7111 ] && break
		mv ${DEPLOYDIR}/${KERNEL_IMAGE_BASE_NAME}.bin ${DEPLOYDIR}/${KERNEL_IMAGE_BASE_NAME}.bin-$i
		ln -sf ${KERNEL_IMAGE_BASE_NAME}.bin-7162 ${DEPLOYDIR}/${KERNEL_IMAGETYPE}-$i
	done
}

# hack to override kernel.bbclass...
# uimages are already built in kernel compile
do_uboot_mkimage() {
	:
}

FILES_kernel-dev += "${includedir}/linux"

FILES_kernel-base += " \
	/lib/modules/7111/${KERNEL_VERSION}/modules.order \
	/lib/modules/7162/${KERNEL_VERSION}/modules.order \
	/lib/modules/7111/${KERNEL_VERSION}/modules.builtin \
	/lib/modules/7162/${KERNEL_VERSION}/modules.builtin \
"

# bitbake.conf only prepends PARALLEL make in tasks called do_compile, which isn't the case for compile_modules
# So explicitly enable it for that in here
EXTRA_OEMAKE = "${PARALLEL_MAKE} "


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


