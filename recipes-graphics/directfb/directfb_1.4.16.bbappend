PRi_INC = "1"

FILESEXTRAPATHS := "${THISDIR}/directfb"

SRC_URI_append = " \
	file://DirectFB-1.4.12-directfb-DVPLAY_PACED-declaration.patch;patch=1 \
"

