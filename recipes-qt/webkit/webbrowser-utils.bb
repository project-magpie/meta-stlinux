DESCRIPTION = "arora webbrowser binary"
PACKAGE_ARCH = "${MACHINE_ARCH}"
PV = "0.11.0"
PR = "r1"

require conf/license/license-gplv2.inc

inherit qt4e

DEPENDS = "qtwebkit-e"

SRC_URI = "http://arora.googlecode.com/files/arora-${PV}.tar.gz"
SRC_URI[md5sum] = "64334ce4198861471cad9316d841f0cb"
SRC_URI[sha256sum] = "6f5fef191935ed740aaa61d5f081abb823997abc20a993cbcb74a4d8adcad3b9"

S = "${WORKDIR}/arora-${PV}"

export QT_LIBINFIX

do_configure_prepend() {
	mv arora.pro arora.bak
	tail -n +4 arora.bak > arora.pro
	rm arora.bak
}

do_install() {
	install -d ${D}/${bindir};
	install -m 0755 arora ${D}/${bindir};
}

