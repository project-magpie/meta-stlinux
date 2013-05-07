require conf/machine/include/tune-sh4.inc
TARGET_ARCH = "sh4"
STLINUX_SH_UPD_SRPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/SRPMS"
STLINUX_SH_UPD_RPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/"
STM_LINUX_PATCH_STR = "0210"
PREFERRED_VERSION_linux-${MACHINE} = "2.6.32.57-stm24-0210"
PREFERRED_VERSION_linux-libc-headers = "2.6.32"
PREFERRED_PROVIDER_virtual/kernel = "stlinux24-${MACHINE}"
PREFERRED_PROVIDER_openssl = "openssl"
PREFERRED_PROVIDER_libcrypto = "openssl"
PREFERRED_PROVIDER_libssl = "openssl"
PREFERRED_VERSION_glibc = "2.10"
PREFERRED_VERSION_glibc                   ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-locale            ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-nativesdk         ?= "2.10"
PREFERRED_VERSION_glibc-initial           ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-initial-nativesdk ?= "2.10"

USE_VT = "0"
MACHINE_FEATURES = "kernel26 ext2 alsa usbhost serial"

SERIAL_CONSOLE = "115200 ttyAS0"

KERNEL_IMAGETYPE = "uImage"

# save some extra space, kernel has its own mtd partion 
RDEPENDS_kernel-base = ""

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096 -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

JFFS2_ERASEBLOCK = "0x20000"
EXTRA_IMAGECMD_jffs2 = "-e ${JFFS2_ERASEBLOCK} -pn"

INHERIT += "usb_image-spark71xx"
IMAGE_FSTYPES ?= "tar.gz ubi ext2 jffs2 spark71xx-usbimg"

IMAGE_CLASSES += "usb_image-spark71xx"
INITRAMFS_FSTYPES = "ext2.gz spark-updt"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
                                     stlinux24-sh4-stx7111-fdma-firmware \
                                     stlinux24-sh4-stmfb-firmware-stx7111 \
                                     u-boot-fw-utils \
                                     stslave-fw \
                                     lirc \
                                     fp-control \
                                     stfbcontrol \
                                     ustslave \
                                     libmmeimage \
                                     tdt-driver \
"

#Spark Boxes have no hardware clock
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"
