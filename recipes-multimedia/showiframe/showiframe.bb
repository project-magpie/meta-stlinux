DESCRIPTION = "utility to show an mpeg2/4 iframe on a linuxtv video device"
SECTION = "base"
PRIORITY = "optional"

PV = "1.3"
PR = "r1"

SRC_URI = "file://showiframe.c"

S = "${WORKDIR}"

do_compile() {
	${CC} -o showiframe showiframe.c -D__sh__
}

do_install() {
	install -d ${D}/${bindir}/
	install -m 0755 ${S}/showiframe ${D}/${bindir}/
}

