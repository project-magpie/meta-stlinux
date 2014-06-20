HOMEPAGE = "http://gitorious.org/open-duckbox-project-sh4"
SECTION = "kernel/modules"
RDEPENDS_${PN} = "ustslave"

LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING;md5=751419260aa954499f7abaabaa882bbe"

inherit module

PACKAGES = "${PN} ${PN}-dev"
# PACKAGES_DYNAMIC += "kernel-module-*"
# without this, tdt-driver package will depend on lots of unavailable kernel-module-*
# (all those modules are in tdt-driver)
KERNEL_MODULES_META_PACKAGE = "None"

SRCREV = "${AUTOREV}"



BINARY_PTI_NP_PATH ?= "/data/pti_np"

# using our own tdt drivers because this has less overhead
SRC_URI = " \
        git://bitbucket.org/graugans/tdt-dvb-modules.git;protocol=https \
        file://tdt-driver.init \
        file://COPYING \
" 



PV = "0.4+git${SRCPV}"

FILES_${PN} = "/etc/udev/rules.d "
FILES = ""

S = "${WORKDIR}/git"

do_configure() {
    rm -f .config
    printf "export CONFIG_PLAYER_191=y\nexport CONFIG_MULTICOM324=y\n" > .config
}



do_compile() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake \
                   KLIB_BUILD=${STAGING_KERNEL_DIR} \
                   DRIVER_TOPDIR=${S}  \
	           ${@d.getVar('MACHINE',1).upper()}=1 \
                   modules 
}

do_install() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
                   KERNEL_SRC=${STAGING_KERNEL_DIR}    \
                   KERNEL_VERSION=${KERNEL_VERSION}    \
		   -C ${STAGING_KERNEL_DIR}   \
	           ${@d.getVar('MACHINE',1).upper()}=1 \
                   M=${S} V=1 \
                   ARCH=sh \
		   PLAYER191=player191 \
        	   DRIVER_TOPDIR="${S}" \
	           KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
	           CONFIG_MODULES_PATH="${D}" \
		   CONFIG_PLAYER_191=y \
		   CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
		   INSTALL_MOD_PATH=${D} modules_install

        # install header files
	install -d ${D}/${includedir}/linux/dvb
       
	install -m 644 bpamem/bpamem.h ${D}/${includedir} 
	install -m 644 player2_191/linux/include/linux/dvb/stm_ioctls.h ${D}/${includedir}/linux/dvb
	install -m 644 stgfb/stmfb-3.1_stm24_0104/linux/drivers/video/stmfb.h ${D}/${includedir}/linux

 
	find ${D} -name stmcore-display-sti7106.ko | xargs -r rm # we don't have a 7106 chip

	install -D -m 0755 ${WORKDIR}/tdt-driver.init ${D}/etc/init.d/tdt-driver
	# drivers seem to be right at about ~ 30
	update-rc.d -r ${D} tdt-driver start 30 S .
}


FILES_${PN} += " \
        /lib/modules/${KERNEL_VERSION}/extra \
	/etc/init.d \
	/etc/rcS.d \
"


pkg_postinst_${PN}() {
#!/bin/sh
if [ -z "$D" ]; then
	depmod -a ${KERNEL_VERSION}
else
	depmodwrapper -a -b $D ${KERNEL_VERSION}
fi
}

FILES_${PN}-dev += "${includedir}"

