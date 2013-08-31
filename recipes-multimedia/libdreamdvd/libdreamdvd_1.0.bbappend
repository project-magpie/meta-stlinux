PRINC = "1"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}"

SRC_URI_append = " \
	file://libdreamdvd-1.0-support_sh4.patch;patch=1 \
"

