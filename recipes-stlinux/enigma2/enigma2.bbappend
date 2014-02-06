FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/${MACHINE}"

DEPENDS_append_spark = " \
	tdt-driver \
        libmmeimage \
	"

DEPENDS_append_spark7162 = " \
        tdt-driver \
        libmmeimage \
        "

EXTRA_OECONF += " \
	--enable-sh=yes \
	"


