SUMMARY = "Player2 Module from TDT "
HOMEPAGE = "http://gitorious.org/open-duckbox-project-sh4"
SECTION = "kernel/modules"
LICENSE = " GPLv2"
#RDEPENDS_${PN} = ""
LIC_FILES_CHKSUM = "file://player/player/player_playback.cpp;endline=33;md5=6b5c84c5d98af78c7a0bc53d1b3e1282"


inherit module

PR = "r1"

SRCREV = "f5159041295774ef5bbb338c7f5d831bc2620d03"

SRC_URI = " \
	git://gitorious.org/open-duckbox-project-sh4/tdt.git \
"


S = "${WORKDIR}/git/tdt/cvs/driver/${PN}_${PV}"

do_compile() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	if [ -L ${WORKDIR}/git/tdt/cvs/driver/include/player2 ]; then
		rm ${WORKDIR}/git/tdt/cvs/driver/include/player2
	fi
	if [ -L ${WORKDIR}/git/tdt/cvs/driver/include/stmfb ]; then
		rm ${WORKDIR}/git/tdt/cvs/driver/include/stmfb
	fi
	if [ -L ${WORKDIR}/git/tdt/cvs/driver/player2 ]; then
                rm ${WORKDIR}/git/tdt/cvs/driver/player2
        fi
	if [ -L ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb ]; then
                rm ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb
        fi
	
	ln -s ${WORKDIR}/git/tdt/cvs/driver/include/stmfb-3.1_stm24_0102 ${WORKDIR}/git/tdt/cvs/driver/include/stmfb
	ln -s ${WORKDIR}/git/tdt/cvs/driver/include/player2_179 ${WORKDIR}/git/tdt/cvs/driver/include/player2
	ln -s ${WORKDIR}/git/tdt/cvs/driver/player2_191 ${WORKDIR}/git/tdt/cvs/driver/player2
	ln -s ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb-3.1_stm24_0102/ ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb
	
	

        oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
                   KERNEL_SRC=${STAGING_KERNEL_DIR}    \
                   KERNEL_VERSION=${KERNEL_VERSION}    \
		   -C ${STAGING_KERNEL_DIR}   \
	           SPARK=spark \
                   M=$PWD V=1\
		   PLAYER191=player191 \
        	   DRIVER_TOPDIR="${WORKDIR}/git/tdt/cvs/driver" \
	           KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
	           CONFIG_MODULES_PATH="${WORKDIR}/git/tdt/cvs/driver" \
		   CONFIG_PLAYER_191=y \
                   CCFLAGSY="-D__TDT__ -D__LINUX__ -D__SH4__ -D__KERNEL__ -DMODULE -DEXPORT_SYMTAB -I${STAGING_DIR}/${MACHINE}/usr/include" \
                   modules 
	
}

do_install() {
        install -d ${D}${base_libdir}/modules/${KERNEL_VERSION}/kernel/drivers/net
#        install -m 0644 ${S}/zd1211*${KERNEL_OBJECT_SUFFIX} ${D}${base_libdir}/modules/${KERNEL_VERSION}/kernel/drivers/net
}
