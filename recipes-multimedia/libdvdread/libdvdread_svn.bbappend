PRINC = "1"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}"

SRC_URI_append = " \
	file://libdvdread_4.2.0.patch;patch=1 \
"

