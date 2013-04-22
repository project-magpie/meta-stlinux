require tdt-tools.inc

RDEPEND += "libmmeimage"

DESCRIPTION = "MME image library"

do_patch_append () {
        os.symlink("${WORKDIR}/git/tdt/cvs/driver/include/player2_179","${WORKDIR}/git/tdt/cvs/driver/include/player2")
}

do_install_append () {
	install -d ${D}${includedir}/mmeimage
	install -m 644 ${WORKDIR}/git/tdt/cvs/apps/misc/tools/libmmeimage/*.h ${D}${includedir}/mmeimage
}

FILES_libmmeimage-dev += "${includedir}/mmeimage"

