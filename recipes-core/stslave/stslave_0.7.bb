
STLINUX_STSLAVE = "stlinux24-target-stslave-${PV}-24.src.rpm"

SRC_URI[md5sum] = "6a4d3fa8f1b88715a3494ac1afe20ee5"
SRC_URI[sha256sum] = "4a4f0c86626c14ab76651759501a2a7fe4f038eafe8e6e8eaa0c097a1b190d63"

SRC_URI = "${STLINUX_SH_UPD_SRPMS}/${STLINUX_STSLAVE} \
"

LOCALSRC = "\
	    file://${WORKDIR}/stslave-0.7.tar.gz \
	    file://${WORKDIR}/stslave-0.6.udev.patch;patch=1;pnum=1 \
            file://${WORKDIR}/stslave-0.7.fix_dump_and_disc_syst.patch;patch=1;pnum=1 \
            file://${WORKDIR}/stslave-0.7-buildfix.patch;patch=1;pnum=1 \
            file://${WORKDIR}/stslave-fix-getenv.patch;patch=1;pnum=1 \
            file://${WORKDIR}/stslave-0.7-empty_section.patch;patch=1;pnum=1 \
            file://${WORKDIR}/stslave-0.7-new-toolchain-support.patch;patch=1;pnum=1 \
            file://001-stslave-fix-Makefile.patch;patch=1;pnum=1 \
            file://002-stslave-conf.patch;patch=1;pnum=1 \
"



DESCRIPTION = "The Linux stslave command loads an ST2x ST2xx application in the target \
memory and trigger its execution. The program can handle different types of \
target devices (slaves from now on) and different slaves of the same type"

DEPENDS = "binutils"
SECTION = "console/utils"

PR = "r1"

S = "${WORKDIR}/stslave"
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://${S}/main.c;beginline=4;endline=6;md5=42efebf7b210788356068c5ce3c011a4"

python do_unpack () {
    bb.build.exec_func('base_do_unpack', d)
    src_uri = d.getVar('SRC_URI')
    d.setVar('SRC_URI', '${LOCALSRC}')
    bb.build.exec_func('base_do_unpack', d)
    d.setVar('SRC_URI', src_uri)
}

python do_patch () {
    bb.build.exec_func('base_do_patch', d)
    src_uri = d.getVar('SRC_URI')
    d.setVar('SRC_URI', '${LOCALSRC}')
    bb.build.exec_func('base_do_patch', d)
    d.setVar('SRC_URI', src_uri)
}

do_install () {
	install -d ${D}${base_bindir}
	install -m 0644 ${S}/stslave ${D}${base_bindir}
	install -d  ${D}${sysconfdir}
	install -m 0644 ${S}/hotplug_example/stslave.conf ${D}${sysconfdir}
}

