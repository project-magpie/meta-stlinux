HOMEPAGE = "https://www.gitorious.org/open-duckbox-project-sh4/tdt"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"
DEPENDS = "tdt-driver-${MACHINE}"

TDT_TOOL_NAME ?= "${@d.getVar('PN',1).replace('-', '_')}"

PR = "r3"

SRCREV = "f5159041295774ef5bbb338c7f5d831bc2620d03"

SRC_URI = " \
	git://gitorious.org/open-duckbox-project-sh4/tdt.git \
"
SRC_URI_append_ufs910 = " \
	file://tdt-ufc960-tools.patch \
"
SRC_URI_append_ufs912 = " \
	file://tdt-ufc960-tools.patch \
"
SRC_URI_append_ufs913 = " \
	file://tdt-ufc960-tools.patch \
"
SRC_URI_append_ufs922 = " \
	file://tdt-ufc960-tools.patch \
"
SRC_URI_append_ufc960 = " \
	file://tdt-ufc960-tools.patch \
"
PV = "0.1+git${SRCPV}"

S = "${WORKDIR}/git/tdt/cvs/apps/misc/tools"

inherit autotools 

EXTRA_OECONF = "--enable-silent-rules --enable-maintainer-mode --prefix="

do_compile() {
	 oe_runmake  'DESTDIR=${D}' 'SUBDIRS=${TDT_TOOL_NAME}' 
}

do_install() {
	 oe_runmake  'DESTDIR=${D}' 'SUBDIRS=${TDT_TOOL_NAME}' install
}
