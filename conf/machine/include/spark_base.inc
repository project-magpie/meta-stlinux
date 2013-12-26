require conf/machine/include/tune-sh4.inc
TARGET_ARCH = "sh4"
STLINUX_SH_UPD_SRPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/SRPMS"
STLINUX_SH_UPD_RPMS = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/"
STM_PATCH_STR ??= "0211"
LINUX_VERSION ??= "2.6.32.59"

PREFERRED_VERSION_stlinux24-${MACHINE} = "${LINUX_VERSION}-stm24-${STM_PATCH_STR}"
PREFERRED_VERSION_linux-libc-headers = "2.6.32"
PREFERRED_PROVIDER_virtual/kernel = "stlinux24-${MACHINE}"
PREFERRED_PROVIDER_openssl = "openssl"
PREFERRED_PROVIDER_libcrypto = "openssl"
PREFERRED_PROVIDER_libssl = "openssl"
#PREFERRED_PROVIDER_virtual/nativesdk-libc = "nativesdk-glibc"
#PREFERRED_PROVIDER_virtual/nativesdk-libiconv = "nativesdk-libiconv"
#PREFERRED_PROVIDER_virtual/nativesdk-libintl = "nativesdk-gettext"
#PREFERRED_VERSION_glibc = "2.10"
#PREFERRED_VERSION_glibc                   ?= "${GLIBCVERSION}"
#PREFERRED_VERSION_glibc-locale            ?= "${GLIBCVERSION}"
#PREFERRED_VERSION_glibc-nativesdk         ?= "2.10"
#PREFERRED_VERSION_glibc-initial           ?= "${GLIBCVERSION}"
#PREFERRED_VERSION_glibc-initial-nativesdk ?= "2.10"

USE_VT = "0"
MACHINE_FEATURES = "kernel26 ext2 alsa ext3 usbhost serial"

SERIAL_CONSOLE = "115200 ttyAS0"

KERNEL_IMAGETYPE = "uImage"

# save some extra space, kernel has its own mtd partion 
RDEPENDS_kernel-base = ""

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 129024 -c 638   -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB -O 512"

JFFS2_ERASEBLOCK = "0x20000"
JFFS2_ENDIANNESS = "${@base_conditional('SITEINFO_ENDIANNESS', 'le', '--little-endian', '--big-endian', d)}"
EXTRA_IMAGECMD_jffs2 = "--pad ${JFFS2_ENDIANNESS} --eraseblock=${JFFS2_ERASEBLOCK} --no-cleanmarkers"

INHERIT += "usb_image-spark71xx"
IMAGE_FSTYPES ?= "tar.gz ubi ext2 jffs2 spark71xx-usbimg"

IMAGE_CLASSES += "usb_image-spark71xx"
INITRAMFS_FSTYPES = "ext2.gz spark-updt"

MACHINE_EXTRA_RRECOMMENDS = "kernel-modules"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += " \
                                     stlinux24-sh4-stx7111-fdma-firmware \
                                     stlinux24-sh4-stmfb-firmware-stx7111 \
                                     stslave-fw \
                                     fp-control \
                                     stfbcontrol \
                                     ustslave \
                                     libmmeimage \
                                     lirc \
                                     lrzsz \
                                     mtd-utils \
                                     mtd-utils-jffs2 \
                                     mtd-utils-ubifs \
                                     mtd-utils-misc \
                                     tdt-driver \
"

##
## We have a RTC in aotom thx to seife.
## I have to check for removale 
## 
#Spark Boxes have no hardware clock
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"


##
## This would not work unless the kernel supports open by handle syscall
## http://lwn.net/Articles/390863/ 
##
#DISTRO_FEATURES_append = " systemd"
#VIRTUAL-RUNTIME_init_manager = "systemd"
#DISTRO_FEATURES_BACKFILL_CONSIDERED = "sysvinit"

##
## gcc-4.8 as in dora or newer (yocto-1.5+) will fail compiling the kernel
## with "error: 'asm' operand requires impossible reload"
## seems to be http://gcc.gnu.org/bugzilla/show_bug.cgi?id=58314
## which is not fixed in any released 4.8.x, so just use 4.7 for now:
##
GCCVERSION ?= "4.7%"
