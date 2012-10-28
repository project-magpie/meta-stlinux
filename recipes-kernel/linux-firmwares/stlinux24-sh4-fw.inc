require linux-firmware.inc

SRC_URI = "ftp://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/${STLINUX_FW_FILE_NAME} \
"

SRC_URI[md5sum] = "9d3feac1d878de02858c85fdf3ea0ba7"
SRC_URI[sha256sum] = "bb373f570585573b10a6c46eb09fd8b92bca72e0c4aa8148af90331e939651b8"

S = "${WORKDIR}/opt/STM/STLinux-2.4/devkit/sh4/target"

# fix architecture mismatch QA error
INSANE_SKIP_${PN} = "arch"

do_unpack() {
	rpm2cpio.sh ${DL_DIR}/${STLINUX_FW_FILE_NAME} | cpio -di
}

