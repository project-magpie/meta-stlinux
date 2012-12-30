DESCRIPTION = "STM ST-231 Coprocessor firmware"
LICENSE = "CLOSED"
SECTION = "base"
PACKAGE_ARCH = "all"

# fix architecture mismatch QA error
INSANE_SKIP_${PN} = "arch"

PR = "r1"

BINARY_STSLAVE_FW_PATH ?= "/data/stslave_fw"

SRC_URI = "file://${BINARY_STSLAVE_FW_PATH}/audio.elf \
           file://${BINARY_STSLAVE_FW_PATH}/video.elf \
"


FILES_${PN} += "/boot"

do_install () {
	install -d ${D}/boot
	install -m 644 ${BINARY_STSLAVE_FW_PATH}/audio.elf  ${D}/boot
	install -m 644 ${BINARY_STSLAVE_FW_PATH}/video.elf  ${D}/boot
}


