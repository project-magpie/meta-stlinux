FILESEXTRAPATHS := "${THISDIR}/files"
PRINC := "${@int(PRINC) + 1}"

SRC_URI += " \
            file://enigma2-pli-nightly.patch;patch=1 \
"

