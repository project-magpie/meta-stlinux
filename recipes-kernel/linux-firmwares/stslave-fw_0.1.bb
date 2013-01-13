DESCRIPTION = "STM ST-231 Coprocessor firmware"
LICENSE = "CLOSED"
SECTION = "base"
PACKAGE_ARCH = "all"

# fix architecture mismatch QA error
INSANE_SKIP_${PN} = "arch"

PR = "r3"

BINARY_STSLAVE_FW_PATH ?= "/data/stslave_fw"

SRC_URI = "file://${BINARY_STSLAVE_FW_PATH}/${MACHINE}/audio.elf \
           file://${BINARY_STSLAVE_FW_PATH}/${MACHINE}/video.elf \
           file://30-stm-stslave-firmware.rules \
"


FILES_${PN} += "/boot"

do_install () {
	install -d ${D}/boot
	install -d ${D}/${sysconfdir}/udev/rules.d
        cp ${WORKDIR}/30-stm-stslave-firmware.rules ${D}/${sysconfdir}/udev/rules.d
	install -m 644 ${BINARY_STSLAVE_FW_PATH}/${MACHINE}/audio.elf  ${D}/boot
	install -m 644 ${BINARY_STSLAVE_FW_PATH}/${MACHINE}/video.elf  ${D}/boot
}


