FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

DEPENDS_append_spark = " \
	tdt-driver \
        libmmeimage \
	"

DEPENDS_append_spark7162 = " \
        tdt-driver \
        libmmeimage \
        "

SRC_URI_append = " \
	file://enigma2-${DISTRO}.patch;patch=1 \
"

