DESCRIPTION = "utility to show an mpeg2/4 iframe on a linuxtv video device"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "PD"
LIC_FILES_CHKSUM = "file://showiframe.c;firstline=1;endline=1;md5=ff82532823be45b3e523e5031819892f"

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
