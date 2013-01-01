HOMEPAGE = "http://gitorious.org/open-duckbox-project-sh4"
SECTION = "kernel/modules"
RDEPENDS = "ustslave"

LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING;md5=751419260aa954499f7abaabaa882bbe"

inherit module

PR = "r11"

SRCREV = "54b4849686bcc6a8834c1ed3f3e92994ba1e9d2a"

# using seifes tdt drivers because this has less overhead
SRC_URI = " \
	git://gitorious.org/neutrino-mp/tdt-driver.git \
        file://COPYING \
        file://aotom_udev.rules \
	file://${MACHINE}/tdt-driver_load.conf \
        file://${MACHINE}/tdt-driver_options.conf \
" 

PV = "0.1+git${SRCPV}"


S = "${WORKDIR}/git"

do_configure_prepend () {
	if [ -L include/stmfb ]; then
		rm include/stmfb
	fi
	if [ -L include/player2 ]; then
		rm include/player2
	fi
	if [ -L include/multicom ]; then
		rm include/multicom
	fi
	if [ -L player2 ]; then
                rm player2
        fi
	if [ -L stgfb/stmfb ]; then
                rm stgfb/stmfb
        fi
	if [ -L multicom ]; then
                rm multicom 
        fi
	ln -s ${S}/include/stmfb-3.1_stm24_0102 ${S}/include/stmfb
	ln -s ${S}/include/player2_179 ${S}/include/player2
	ln -s ${S}/multicom-3.2.4/include ${S}/include/multicom
	ln -s ${S}/player2_191 ${S}/player2
	ln -s ${S}/multicom-3.2.4 ${S}/multicom
	ln -s ${S}/stgfb/stmfb-3.1_stm24_0102 ${S}/stgfb/stmfb
	rm -f .config 
        printf "export CONFIG_PLAYER_191=y\nexport CONFIG_MULTICOM324=y\n" > .config
	# disable wireless build
	sed -i 's/^\(obj-y.*+= wireless\)/# \1/' Makefile
	# disable led and button - it's not for spark
	sed -i 's@^\(obj-y.*+= \(led\|button\)/\)@# \1@' Makefile
}



do_compile() {
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
 	install -m 644 frontcontroller/aotom/aotom_main.h ${D}/${includedir}
 	install -m 644 player2/linux/include/linux/dvb/stm_ioctls.h ${D}/${includedir}/linux/dvb
 	install -m 644 stgfb/stmfb/linux/drivers/video/stmfb.h ${D}/${includedir}/linux

	#install modutils config
	install -d ${D}/${sysconfdir}/modules-load.d
	install -d ${D}/${sysconfdir}/modprobe.d
	install -d ${D}/${sysconfdir}/udev/rules.d/
	
	cp ${WORKDIR}/${MACHINE}/tdt-driver_load.conf ${D}/${sysconfdir}/modules-load.d/tdt-driver.conf
	cp ${WORKDIR}/${MACHINE}/tdt-driver_options.conf ${D}/${sysconfdir}/modprobe.d/tdt-driver.conf
	cp ${WORKDIR}/aotom_udev.rules ${D}/${sysconfdir}/udev/rules.d/32-aotom.rules

}

FILES_${PN}-dev += "${includedir}"

