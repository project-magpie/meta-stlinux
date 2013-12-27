SUMMARY = "Asynchronous I/O library"
DESCRIPTION = "Asynchronous input/output library that uses the kernels native interface"
HOMEPAGE = "http://lse.sourceforge.net/io/aio.html"

LICENSE = "LGPLv2.1+"
LIC_FILES_CHKSUM = "file://COPYING;md5=d8045f3b8f929c1cb29a1e3fd737b499"

PR = "r3"

SRC_URI = "${DEBIAN_MIRROR}/main/liba/libaio/libaio_${PV}.orig.tar.gz \
	file://00_arches.patch \
	file://00_arches_sh.patch \
	file://00_arches_sparc64.patch \
	file://01_link_libgcc.patch \
	file://02_libdevdir.patch \
	file://03_man_errors.patch \
	file://03_man_escape_backslash.patch \
	file://04_check_waitpid_return.patch \
	file://04_no_Werror.patch \
	file://05_build-flags.patch \
	file://libaio-0.3.109-cross-install.patch \
	file://toolchain.patch \
"

SRC_URI[md5sum] = "435a5b16ca6198eaf01155263d855756"
SRC_URI[sha256sum] = "bf4a457253cbaab215aea75cb6e18dc8d95bbd507e9920661ff9bdd288c8778d"

EXTRA_OEMAKE =+ "prefix=${prefix} includedir=${includedir} libdir=${libdir}"

do_configure () {
    sed -i 's#LINK_FLAGS=.*#LINK_FLAGS=$(LDFLAGS)#' src/Makefile
}

do_install () {
    oe_runmake install DESTDIR=${D}
}
