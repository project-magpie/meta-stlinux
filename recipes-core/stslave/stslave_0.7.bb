
STLINUX_STSLAVE = "stlinux24-target-stslave-${PV}-24.src.rpm"
SRC_URI = "${STLINUX_SH_UPD_SRPMS}/${STLINUX_STSLAVE}"

SRC_URI[md5sum] = "e66a9c9af6a60dc46134fdacf6ce97d7"
SRC_URI[sha256sum] = "f52583a83a63633701c5f71db3dc40aab87b7f76b29723aeb27941eff42df6e1"

DESCRIPTION = "The Linux stslave command loads an ST2x ST2xx application in the target \
memory and trigger its execution. The program can handle different types of \
target devices (slaves from now on) and different slaves of the same type"

SECTION = "console/utils"

PR = "r1"

S = "${WORKDIR}\stslave"

do_unpack() {
	rpm2cpio.sh ${DL_DIR}/${STLINUX_STSLAVE} | cpio -di
	tar xzf stslave-${PV}.tar.gz
}

do_patch() {
	echo $PWD
	echo $CC
	patch -p1 < stslave-0.6.udev.patch
	patch -p1 < stslave-0.7.fix_dump_and_disc_syst.patch
	patch -p1 < stslave-0.7-buildfix.patch
	patch -p1 < stslave-fix-getenv.patch
	patch -p1 < stslave-0.7-empty_section.patch
	patch -p1 < stslave-0.7-new-toolchain-support.patch
}

