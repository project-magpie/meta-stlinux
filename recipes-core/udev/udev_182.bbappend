FILESEXTRAPATHS := "${THISDIR}/udev"
PRINC := "${@int(PRINC) + 2}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI += " \
    file://udev-builtin-input_id.patch \
"

