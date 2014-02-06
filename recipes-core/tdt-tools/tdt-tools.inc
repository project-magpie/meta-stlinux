HOMEPAGE = "https://www.gitorious.org/open-duckbox-project-sh4/tdt"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"
DEPENDS = "tdt-driver"

PR = "r10"

#SRCREV = "f5159041295774ef5bbb338c7f5d831bc2620d03"
SRCREV = "${AUTOREV}"

SRC_URI = " \
        git://github.com/sklnet/tdt-tools.git;protocol=git \
"

PV = "0.5+git${SRCPV}"

S = "${WORKDIR}/git"

inherit autotools 

EXTRA_OECONF = "--enable-silent-rules --enable-maintainer-mode --prefix="

do_configure() {
	./autogen.sh
	oe_runconf
}

do_compile() {
	 oe_runmake  'DESTDIR=${D}' 'SUBDIRS=${@d.getVar('PN',1).replace('-', '_')}' 
}

do_install() {
	 oe_runmake  'DESTDIR=${D}' 'SUBDIRS=${@d.getVar('PN',1).replace('-', '_')}' install
}
