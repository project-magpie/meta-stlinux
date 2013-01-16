require conf/machine/include/tune-sh4.inc

TARGET_ARCH = "sh4"

STLINUX_SH_UPD_SRPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/SRPMS"
STLINUX_SH_UPD_RPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/"

STLINUX_SH_KERNEL_VER = "2.6.32.46-45"

PREFERRED_VERSION_linux-${MACHINE} = "2.6.32.57-stm24-0210"
PREFERRED_VERSION_linux-libc-headers = "2.6.32"
PREFERRED_PROVIDER_virtual/kernel = "linux-stm"

PREFERRED_VERSION_glibc = "2.10"

#PREFERRED_PROVIDER_virtual/libc = "glibc"
#PREFERRED_PROVIDER_virtual/sh4-poky-linux-libc-initial = "glibc"
PREFERRED_VERSION_glibc                   ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-locale            ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-nativesdk         ?= "2.10"
PREFERRED_VERSION_glibc-initial           ?= "${GLIBCVERSION}"
PREFERRED_VERSION_glibc-initial-nativesdk ?= "2.10"

USE_VT = "0"
MACHINE_FEATURES = "kernel26 ext2 alsa usbhost serial"

SERIAL_CONSOLE = "115200 ttyAS0"

KERNEL_IMAGETYPE = "uImage"

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096 -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB"


INHERIT += "update_image-spark"
IMAGE_FSTYPES ?= "tar.gz ubi"


INITRAMFS_FSTYPES = "ext2.gz spark-updt"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "stlinux24-sh4-stx7111-fdma-firmware \
	                             stlinux24-sh4-stmfb-firmware-stx7111 \
                                     u-boot-fw-utils \
                                     stslave-fw \
				     lirc \
				     fp-control stfbcontrol ustslave \
"

#Spark Boxes have no hardware clock
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

