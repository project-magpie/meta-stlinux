require tdt-tools.inc

DEPENDS += "jpeg"

DESCRIPTION = "MME image library"

do_install_append () {
	install -d ${D}${includedir}/mmeimage
	install -m 644 ${WORKDIR}/git/libmmeimage/*.h ${D}${includedir}/mmeimage
}

FILES_libmmeimage-dev += "${includedir}/mmeimage"

