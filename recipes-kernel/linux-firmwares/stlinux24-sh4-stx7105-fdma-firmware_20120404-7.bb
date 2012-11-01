STLINUX_FW_FILE_NAME = "stlinux24-sh4-fdma-firmware-${PV}.noarch.rpm"
DESCRIPTION = "Firmware for the STx7111 CPU Flexible DMA engine (FDMA)"

require stlinux24-sh4-fw.inc 

PR = "r2"

do_install() {
	install -d ${D}${base_libdir}/firmware
	install -m 0644 ${S}/lib/firmware/fdma_STx7105_* ${D}${base_libdir}/firmware
}
