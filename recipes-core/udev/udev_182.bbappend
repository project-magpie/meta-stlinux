FILESEXTRAPATHS_prepend := "${THISDIR}/udev"
PRINC := "${@int(PRINC) + 3}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI += " \
    file://udev-builtin-input_id.patch \
"

