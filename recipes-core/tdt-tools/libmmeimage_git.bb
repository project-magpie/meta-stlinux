require tdt-tools.inc

RDEPEND += "libmmeimage"

DESCRIPTION = "MME image library"

do_patch_append () {
        os.symlink("${WORKDIR}/git/tdt/cvs/driver/include/player2_179","${WORKDIR}/git/tdt/cvs/driver/include/player2")
}

