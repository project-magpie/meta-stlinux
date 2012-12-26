require tdt-driver.inc
SUMMARY = "STMFB Module from TDT "
LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://STMCommon/stmbdisp.h;endline=10;md5=8cca6a77ab153c7151fc6f7e1a46c3c3"

PR = "r4"

S = "${WORKDIR}/git/tdt/cvs/driver/stgfb/${PN}-${PV}_stm24_0102"

do_configure_prepend () {

	if [ -L ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb ]; then
                rm ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb
        fi

	ln -s ${WORKDIR}/git/tdt/cvs/driver/include/stmfb-3.1_stm24_0102 ${WORKDIR}/git/tdt/cvs/driver/include/stmfb
	ln -s ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb-3.1_stm24_0102/ ${WORKDIR}/git/tdt/cvs/driver/stgfb/stmfb
}

do_install_append() {
        install -d ${D}/${includedir}/linux
	install -d ${D}/usr/src/tdt-driver/include/${PN}
        install -m 644 ${WORKDIR}/git/tdt/cvs/driver/include/${PN}-${PV}_stm24_0102/*  ${D}/usr/src/tdt-driver/include/${PN} 
        install -m 644 linux/drivers/video/stmfb.h ${D}/${includedir}/linux 
}

FILES_${PN}-dev = "/usr/src/tdt-driver/include/${PN}/* ${includedir}/linux/*"
