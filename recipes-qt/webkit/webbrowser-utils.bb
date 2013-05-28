DESCRIPTION = "arora webbrowser binary"
PACKAGE_ARCH = "${MACHINE_ARCH}"
PV = "0.10.1"
PR = "r5"

require conf/license/license-gplv2.inc

inherit qmake2 

DEPENDS = "qtwebkit-e"

SRCREV = "e310d632e9f6c135c376576d2d466af03fd219ee"
SRC_URI_spark = "git://github.com/Arora/arora.git"
SRC_URI_spark7162 = "git://github.com/Arora/arora.git"

S = "${WORKDIR}/git"

do_install() {
	install -d ${D}/${bindir};
	install -m 0755 arora ${D}/${bindir};
}
