require linux-firmware.inc

DESCRIPTION = "Firmware for the STM Flexible DMA engine (FDMA)"

FDMA_FILE_NAME = "stlinux24-sh4-fdma-firmware-20120404-7.noarch.rpm"

SRC_URI = "ftp://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/${FDMA_FILE_NAME} \
"

S = "${WORKDIR}/opt/STM/STLinux-2.4/devkit/sh4/target"


# fix architecture mismatch QA error
INSANE_SKIP_${PN} = "arch"

do_unpack() {
	echo "workdir: " ${WORKDIR}/files
	echo "curr: " $PWD
	cpio --version
	which rpm2cpio 
	rpm2cpio.sh ${DL_DIR}/stlinux24-sh4-fdma-firmware-20120404-7.noarch.rpm | cpio -di
}

do_install() {
	install -d ${D}${base_libdir}/firmware
	install -m 0644 ${S}/lib/firmware/fdma_STx7111_* ${D}${base_libdir}/firmware
}
