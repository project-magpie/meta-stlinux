require sh4-fdma-firmware.inc

DESCRIPTION = "Firmware for the STx7111 CPU Flexible DMA engine (FDMA)"


do_install() {
	install -d ${D}${base_libdir}/firmware
	install -m 0644 ${S}/lib/firmware/fdma_STx7111_* ${D}${base_libdir}/firmware
}
