FILESEXTRAPATHS := "${THISDIR}/files"
PRINC := "${@int(PRINC) + 1}"

SRC_URI += " \
            file://libdvbsi++-fix-unaligned-access-on-SuperH.patch \
"


