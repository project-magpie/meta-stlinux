#require recipes-core/glibc/glibc-package.inc

INHIBIT_DEFAULT_DEPS = "1"
INHIBIT_PACKAGE_STRIP = '1'

# License applies to this recipe code, not the toolchain itself
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58 \
                    file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

PROVIDES += "\
	linux-libc-headers \
	virtual/${TARGET_PREFIX}gcc \
	virtual/${TARGET_PREFIX}g++ \
	virtual/${TARGET_PREFIX}gcc-initial \
	virtual/${TARGET_PREFIX}gcc-intermediate \
	virtual/${TARGET_PREFIX}binutils \
	virtual/${TARGET_PREFIX}libc-for-gcc \
	virtual/${TARGET_PREFIX}compilerlibs \
	virtual/libc \
	virtual/libintl \
	virtual/libiconv \
	glibc-thread-db \
	libgcc \
	virtual/linux-libc-headers \
"



STL_ARCHIVE = "http://ftp.stlinux.com/pub/stlinux/2.4/updates/RPMS/sh4/"


STL_BINUTILS_VER = "2.20.51.0.7-48"
STL_GCC_VER = "4.5.3-97"
STMKERNEL_VER = "2.6.32.46-45"
STL_LIBGCC_VER = "4.5.3-100"
STL_GLIBC_VER = "2.10.2-34"

STL_VER_MAIN = "${STL_GCC_VER}"
PV = "${STL_VER_MAIN}"
PR = "r8"

STL_RPM_BINUTILS = "stlinux24-cross-sh4-binutils-${STL_BINUTILS_VER}.i386.rpm"
STL_RPM_BINUTILS_DEV = "stlinux24-cross-sh4-binutils-dev-${STL_BINUTILS_VER}.i386.rpm"
STL_RPM_CROSS_SH4_CPP = "stlinux24-cross-sh4-cpp-${STL_GCC_VER}.i386.rpm"
STL_RPM_CROSS_SH4_GCC = "stlinux24-cross-sh4-gcc-${STL_GCC_VER}.i386.rpm"
STL_RPM_CROSS_SH4_GPP = "stlinux24-cross-sh4-g++-${STL_GCC_VER}.i386.rpm"
STL_RPM_LINUX_HEADER = "stlinux24-sh4-linux-kernel-headers-${STMKERNEL_VER}.noarch.rpm"
STL_RPM_LIBGCC = "stlinux24-sh4-libgcc-${STL_LIBGCC_VER}.sh4.rpm"
STL_RPM_GLIBC = "stlinux24-sh4-glibc-${STL_GLIBC_VER}.sh4.rpm"
STL_RPM_GLIBC_DEV = "stlinux24-sh4-glibc-dev-${STL_GLIBC_VER}.sh4.rpm"
STL_RPM_LIBSTDC = "stlinux24-sh4-libstdc++-${STL_LIBGCC_VER}.sh4.rpm"
STL_RPM_LIBSTDC_DEV = "stlinux24-sh4-libstdc++-dev-${STL_LIBGCC_VER}.sh4.rpm"


SRC_URI ="\
	${STL_ARCHIVE}/${STL_RPM_BINUTILS};name=stl-binutils \
        ${STL_ARCHIVE}/${STL_RPM_BINUTILS_DEV};name=stl-binutils-dev \
	${STL_ARCHIVE}/${STL_RPM_CROSS_SH4_CPP};name=stl-cpp \
	${STL_ARCHIVE}/${STL_RPM_CROSS_SH4_GCC};name=stl-gcc \
	${STL_ARCHIVE}/${STL_RPM_CROSS_SH4_GPP};name=stl-gpp \
	${STL_ARCHIVE}/${STL_RPM_LINUX_HEADER};name=stl-headers \
	${STL_ARCHIVE}/${STL_RPM_LIBGCC};name=stl-libgcc \
	${STL_ARCHIVE}/${STL_RPM_GLIBC};name=stl-glibc \
	${STL_ARCHIVE}/${STL_RPM_GLIBC_DEV};name=stl-glibc-dev \
	${STL_ARCHIVE}/${STL_RPM_LIBSTDC};name=stl-libstdc \
	${STL_ARCHIVE}/${STL_RPM_LIBSTDC_DEV};name=stl-libstdc-dev \
"

SRC_URI[stl-binutils.md5sum] = "70ba1bd436c2e7f46c88d42485f3c970"
SRC_URI[stl-binutils.sha256sum] = "3eac6361f2359b66178982b73613f544d21bd9704d8a49cba257f0734ab4dec8"
SRC_URI[stl-binutils-dev.sha256sum] = "3eac6361f2359b66178982b73613f544d21bd9704d8a49cba257f0734ab4dec8"
SRC_URI[stl-binutils-dev.md5sum] = "9e631b722fc5ad9431d1e1f10dbb6e2c"
SRC_URI[stl-binutils-dev.sha256sum] = "a0660656e5bed7198d1e5d660094ebb8d5f702ff835bad29bd3024e5ed7a9e76"
SRC_URI[stl-cpp.md5sum] = "3d66689db04c4ba96dd3389f44ceb06c"
SRC_URI[stl-cpp.sha256sum] = "9db614438aa7ef1a54f696ef0b15de8cf2d86edf337e1bfe431f1c2917d54da4"
SRC_URI[stl-gcc.md5sum] = "f77a39141f03b2b91ff203cf6eeb012e"
SRC_URI[stl-gcc.sha256sum] = "cad4950777a781f132ea87e9c6d32df639a14415168250d70e4a9070a9e53eb3"
SRC_URI[stl-gpp.md5sum] = "e960cc1988fde2f8bacb7a425f658cbc"
SRC_URI[stl-gpp.sha256sum] = "17256664788a50accdc46612f8722103999cc00a5b3ea997c16ecd9b91a22763"
SRC_URI[stl-headers.md5sum] = "86e6524ac4e8183fe4062216e618dee3"
SRC_URI[stl-headers.sha256sum] = "a6da2a4e327a58a270f6875d230931d2bcc9b5d84d67d8ab071fad2b092577de"
SRC_URI[stl-libgcc.md5sum] = "d6dadd2e7fcfd8e1f9bcebba6d970b85"
SRC_URI[stl-libgcc.sha256sum] = "f01aa89bd5b3094f1297751ffffd854e01838c528738fc974835a80cc9d1d6c2"
SRC_URI[stl-glibc.md5sum] = "c2e4fe18e6fcc6f1d20c65fd1a4851ef"
SRC_URI[stl-glibc.sha256sum] = "a27f78d977f0801220f3a2dd3d237fb7fdfc741430743b7b6db553454191fed2"
SRC_URI[stl-glibc-dev.md5sum] = "f5d99e6c21a8210e5e4dad14597d5e30"
SRC_URI[stl-glibc-dev.sha256sum] = "77d6536c8d0e86e612e32a70e166bcb95060a89510a7599f1160801a012b579b"
SRC_URI[stl-libstdc.md5sum] = "8c71de1006552ecc64c5d2f2a7d8fd35"
SRC_URI[stl-libstdc.sha256sum] = "2b10e869a8a3da6cc12029ec5086943f8977c886af52a58e7f9153533c13654c"
SRC_URI[stl-libstdc-dev.md5sum] = "02a92de32fba13d9f1827f49f03c7c6d"
SRC_URI[stl-libstdc-dev.sha256sum] = "4089117a230feedcd67dbb589198b1079cb0e1c4618897dadf0bf9d4794da67e"

STL_CPIO_OPTS = "--extract --unconditional --preserve-modification-time --make-directories"

#SRC_URI = "file://SUPPORTED"

do_unpack() {
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_BINUTILS} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_BINUTILS_DEV} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_CROSS_SH4_CPP} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_CROSS_SH4_GCC} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_CROSS_SH4_GPP} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_LINUX_HEADER} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_LIBGCC} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_GLIBC} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_GLIBC_DEV} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_LIBSTDC} | cpio ${STL_CPIO_OPTS}
	rpm2cpio.sh ${DL_DIR}/${STL_RPM_LIBSTDC_DEV} | cpio ${STL_CPIO_OPTS}
}

STL_RELOCATE = "/opt/STM/STLinux-2.4/devkit/sh4"

do_install() {
	# Use optimized files if available
	sysroot="${EXTERNAL_TOOLCHAIN_SYSROOT}"

	install -d ${D}/usr
	cp -a ${WORKDIR}/${STL_RELOCATE}/* ${D}/usr	
	install -d  ${STAGING_DIR_TARGET}/usr
	cp -a ${WORKDIR}/${STL_RELOCATE}/* ${STAGING_DIR_TARGET}/usr

	echo ${base_libdir}

	#ln -s ../../bin/gdbserver ${D}${libdir}/bin/sysroot-gdbserver

	#sed -i -e 's/__packed/__attribute__ ((packed))/' ${D}${includedir}/mtd/ubi-user.h
        #sed -i -e "s# ${base_libdir}# ../..${base_libdir}#g" -e "s# ${libdir}# .#g" ${D}${libdir}/libc.so
        #sed -i -e "s# ${base_libdir}# ../..${base_libdir}#g" -e "s# ${libdir}# .#g" ${D}${libdir}/libpthread.so
}

SYSROOT_PREPROCESS_FUNCS += "external_toolchain_sysroot_adjust"
external_toolchain_sysroot_adjust() {
	dest_sysroot="$(${CC} -print-sysroot | sed -e's,^${STAGING_DIR_HOST},,; s,/$,,')"
	if [ -n "$dest_sysroot" ]; then
		rm -f ${SYSROOT_DESTDIR}/$dest_sysroot
		ln -s . ${SYSROOT_DESTDIR}/$dest_sysroot
	fi

	# If the usr/lib directory doesn't exist, the toolchain fails to even
	# try to find crti.o in a completely different directory (usr/lib64)
	install -d ${SYSROOT_DESTDIR}/usr/lib
}

PACKAGES =+ "libgcc libgcc-dev libstdc++ libstdc++-dev libstdc++-staticdev linux-libc-headers linux-libc-headers-dev gdbserver gdbserver-dbg"

# This test should be fixed to ignore .a files in .debug dirs
INSANE_SKIP_${PN}-dbg = "staticdev"

# We don't care about GNU_HASH in prebuilt binaries
INSANE_SKIP_${PN}-utils += "ldflags"
INSANE_SKIP_libstdc++ += "ldflags"
INSANE_SKIP_libgcc += "ldflags"
INSANE_SKIP_gdbserver += "ldflags"
INSANE_SKIP_${PN} = "arch"


PKG_${PN} = "glibc"
PKG_${PN}-dev = "glibc-dev"
PKG_${PN}-staticdev = "glibc-staticdev"
PKG_${PN}-doc = "glibc-doc"
PKG_${PN}-dbg = "glibc-dbg"
PKG_${PN}-pic = "glibc-pic"
PKG_${PN}-utils = "glibc-utils"
PKG_${PN}-gconv = "glibc-gconv"
PKG_${PN}-extra-nss = "glibc-extra-nss"
PKG_${PN}-thread-db = "glibc-thread-db"
PKG_${PN}-pcprofile = "glibc-pcprofile"

PKGV = "${STL_VER_LIBC}"
PKGV_libgcc = "${STL_VER_GCC}"
PKGV_libgcc-dev = "${STL_VER_GCC}"
PKGV_libstdc++ = "${STL_VER_GCC}"
PKGV_libstdc++-dev = "${STL_VER_GCC}"
PKGV_libstdc++-staticdev = "${STL_VER_GCC}"
PKGV_linux-libc-headers = "${STL_VER_KERNEL}"
PKGV_linux-libc-headers-dev = "${STL_VER_KERNEL}"
PKGV_gdbserver = "${STL_VER_GDB}"
PKGV_gdbserver-dbg = "${STL_VER_GDB}"

FILES_libgcc = "${base_libdir}/libgcc_s.so.1"
FILES_libgcc-dev = "${base_libdir}/libgcc_s.so"
FILES_libstdc++ = "${libdir}/libstdc++.so.*"
FILES_libstdc++-dev = "${includedir}/c++/${PV} \
	${libdir}/libstdc++.so \
	${libdir}/libstdc++.la \
	${libdir}/libsupc++.la"
FILES_libstdc++-staticdev = "${libdir}/libstdc++.a ${libdir}/libsupc++.a"
FILES_linux-libc-headers = "${includedir}/asm* \
	${includedir}/linux \
	${includedir}/mtd \
	${includedir}/rdma \
	${includedir}/scsi \
	${includedir}/sound \
	${includedir}/video \
"
FILES_gdbserver = "${bindir}/gdbserver ${libdir}/bin/sysroot-gdbserver"
FILES_gdbserver-dbg = "${bindir}/.debug/gdbserver"

STL_VER_MAIN ??= ""

python () {
    if not d.getVar("STL_VER_MAIN"):
	raise bb.parse.SkipPackage("External STL toolchain not configured (STL_VER_MAIN not set).")
}

