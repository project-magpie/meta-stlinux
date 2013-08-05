PRINC = "1"

FILESEXTRAPATHS_append := "${THISDIR}/${PN}"

SRC_URI_append = " \
           file://gentoo/sh4-atomic-ops.patch \
"

