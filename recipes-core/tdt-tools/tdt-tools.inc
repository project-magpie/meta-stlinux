HOMEPAGE = "https://www.gitorious.org/open-duckbox-project-sh4/tdt"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"
DEPENDS = "tdt-driver"

PR = "r5"

#SRCREV = "f5159041295774ef5bbb338c7f5d831bc2620d03"
SRCREV = "${AUTOREV}"

SRC_URI = " \
	git://gitorious.org/open-duckbox-project-sh4/tdt.git \
"
#SRC_URI = " \
#	git://gitorious.org/~max10/open-duckbox-sh4/max-tdt.git;brach=enigma2 \
#	file://configure.max.patch;patch=1 \
#"
PV = "0.5+git${SRCPV}"

S = "${WORKDIR}/git/tdt/cvs/apps/misc/tools"

inherit autotools 

EXTRA_OECONF = "--enable-silent-rules --enable-maintainer-mode --prefix="

do_patch_append () {
        os.symlink("${WORKDIR}/git/tdt/cvs/driver/include/stmfb-3.1_stm24_0104","${WORKDIR}/git/tdt/cvs/driver/include/stmfb")
        os.symlink("${WORKDIR}/git/tdt/cvs/driver/include/player2_179","${WORKDIR}/git/tdt/cvs/driver/include/player2")
        os.symlink("${WORKDIR}/git/tdt/cvs/driver/multicom-3.2.4/include","${WORKDIR}/git/tdt/cvs/driver/include/multicom")
}

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
