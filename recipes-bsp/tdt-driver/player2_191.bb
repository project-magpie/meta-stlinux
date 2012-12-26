require tdt-driver.inc

SUMMARY = "Player2 Module from TDT "
LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://player/player/player_playback.cpp;endline=33;md5=6b5c84c5d98af78c7a0bc53d1b3e1282"

PR = "r2"

S = "${WORKDIR}/git/tdt/cvs/driver/${PN}_${PV}"

do_compile() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
                   KERNEL_SRC=${STAGING_KERNEL_DIR}    \
                   KERNEL_VERSION=${KERNEL_VERSION}    \
		   -C ${STAGING_KERNEL_DIR}   \
	           SPARK=spark \
                   M=$PWD V=1\
		   PLAYER191=player191 \
		   CONFIG_STGFB_PATH?="${STAGING_HOST_DIR}/usr/src/tdt-driver/stgfb" \
        	   DRIVER_TOPDIR="${WORKDIR}/git/tdt/cvs/driver" \
	           KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
	           CONFIG_MODULES_PATH="${WORKDIR}/git/tdt/cvs/driver" \
		   CONFIG_PLAYER_191=y \
                   CCFLAGSY="-D__TDT__ -D__LINUX__ -D__SH4__ -D__KERNEL__ -DMODULE -DEXPORT_SYMTAB -I${STAGING_DIR}/${MACHINE}/usr/include" \
                   modules 
	
}


