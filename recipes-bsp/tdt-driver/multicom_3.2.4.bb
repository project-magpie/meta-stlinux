require tdt-driver.inc
SUMMARY = "multicom  Module from TDT "
LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING.GPL;md5=751419260aa954499f7abaabaa882bbe"

PR = "r1"

S = "${WORKDIR}/git/tdt/cvs/driver/${PN}-${PV}"

SRC_URI += "file://COPYING.GPL"

do_configure_prepend () {

	if [ -L ${WORKDIR}/git/tdt/cvs/driver/${PN} ]; then
                rm ${WORKDIR}/git/tdt/cvs/driver/${PN}
        fi

	ln -s ${WORKDIR}/git/tdt/cvs/driver/${PN}-${PV} ${WORKDIR}/git/tdt/cvs/driver/${PN}
	ln -s ${WORKDIR}/git/tdt/cvs/driver/${PN}/include ${WORKDIR}/git/tdt/cvs/driver/include/${PN}
}

do_install_append() {
        install -d ${D}/${includedir}/linux
	install -d ${D}/usr/src/tdt-driver/include/${PN}
        install -m 644 ${WORKDIR}/git/tdt/cvs/driver/include/${PN}/*  ${D}/usr/src/tdt-driver/include/${PN} 
}

FILES_${PN}-dev = "/usr/src/tdt-driver/include/${PN}/*"
