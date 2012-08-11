require linux-firmware.inc

SRC_URI = "ftp://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/${STLINUX_FW_FILE_NAME} \
"

SRC_URI[md5sum] = "a5b506d279aebba72bb2ac8436e9f8ff"
SRC_URI[sha256sum] = "f5ac77765ad6e3d747f76ae89f1377b7f4c2bcd4bc714048b453881f3d7dbc1b"

S = "${WORKDIR}/opt/STM/STLinux-2.4/devkit/sh4/target"

# fix architecture mismatch QA error
INSANE_SKIP_${PN} = "arch"

do_unpack() {
	rpm2cpio.sh ${DL_DIR}/${STLINUX_FW_FILE_NAME} | cpio -di
}

