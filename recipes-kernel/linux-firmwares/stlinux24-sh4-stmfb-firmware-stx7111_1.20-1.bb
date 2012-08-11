STLINUX_FW_FILE_NAME = "stlinux24-sh4-stmfb-firmware-${PV}.noarch.rpm"
DESCRIPTION = "STLinux 2.4 STM Framebuffer firmware"

require stlinux24-sh4-fw.inc

do_install() {
        install -d ${D}${base_libdir}/firmware
        install -d ${D}/etc/udev/rules.d/
        install -d ${D}/sbin/
	install -m 0644 ${S}/etc/udev/rules.d/40-stm-awg-firmware.rules ${D}/etc/udev/rules.d/
        install -m 0644 ${S}/lib/firmware/component_7111* ${D}${base_libdir}/firmware
	install -m 0644 ${S}/sbin/firmware_helper.awg ${D}/sbin/firmware_helper.awg 
}
 
