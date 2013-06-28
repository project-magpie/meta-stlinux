DESCRIPTION = "utility to show an mpeg2/4 iframe on a linuxtv video device"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "PD"
LIC_FILES_CHKSUM = "file://showiframe.c;firstline=1;endline=1;md5=09a0d9c2fb98bb5fe6a1de568344c2f2"

PV = "1.3"
PR = "r1"

SRC_URI = "file://showiframe.c"

S = "${WORKDIR}"

do_compile() {
	${CC} -o showiframe showiframe.c
}

do_install() {
	install -d ${D}/${bindir}/
	install -m 0755 ${S}/showiframe ${D}/${bindir}/
}
