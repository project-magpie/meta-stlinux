FILESEXTRAPATHS := "${THISDIR}/files"
PRINC := "${@int(PRINC) + 1}"

SRC_URI += " \
            file://enigma2-networkbrowser-support_autofs.patch;patch=1 \
"

