DESCRIPTION = "LIRC is a package that allows you to decode and send infra-red signals of many commonly used remote controls."
DESCRIPTION_append_lirc = " This package contains the lirc daemon, libraries and tools."
DESCRIPTION_append_lirc-exec = " This package contains a daemon that runs programs on IR signals."
DESCRIPTION_append_lirc-remotes = " This package contains some config files for remotes."
DESCRIPTION_append_lirc-nslu2example = " This package contains a working config for RC5 remotes and a modified NSLU2."
SECTION = "console/network"
PRIORITY = "optional"
HOMEPAGE = "http://www.lirc.org"
LICENSE = "GPLv2"
DEPENDS = "virtual/kernel"
DEPENDS_nslu2 = "virtual/kernel lirc-modules"
RDEPENDS_lirc-exec = "lirc"
RDEPENDS_lirc-nslu2example = "lirc lirc-exec"
RRECOMMENDS_${PN} = "lirc-exec "
RRECOMMENDS_${PN}_spark += "kernel-module-uinput"

PR = "${INCPR}.0"

EXTRA_OECONF += "--with-kerneldir=${STAGING_KERNEL_DIR} ${DRIVER}"
EXTRA_OECONF_spark += "--without-x --with-driver=userspace"

inherit autotools module-base update-rc.d
SRC_URI_append = " file://lircd.init \
                   file://lircmd.init \
                   file://lircexec.init \
                 "
SRC_URI_append_nslu2 = " file://lircd.conf_nslu2 \
                         file://lircrc_nslu2 \
                       "

SRC_URI_append_spark += " file://lirc-0.9.0-neutrino-uinput-hack.diff;patch=1 \
			 file://lirc-0.9.0-try_first_last_remote.diff;patch=1 \
			 file://lirc-0.9.0-uinput-repeat-fix.diff;patch=1 \
                         file://lircd_spark.conf \
                         file://lircd_spark.init \
                         file://lircd_spark.conf.09_00_0A \
"

INITSCRIPT_PACKAGES = "lirc lirc-exec"
INITSCRIPT_NAME = "lircd"
INITSCRIPT_PARAMS = "defaults 20"
INITSCRIPT_NAME_lirc-exec = "lircexec"
INITSCRIPT_PARAMS_lirc-exec = "defaults 21"

require lirc-config.inc

EXTRA_OEMAKE = 'SUBDIRS="daemons tools"'

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install ${WORKDIR}/lircd.init ${D}${sysconfdir}/init.d/lircd
	install ${WORKDIR}/lircexec.init ${D}${sysconfdir}/init.d/lircexec
        install -d ${D}${datadir}/lirc/
        cp -pPR ${S}/remotes ${D}${datadir}/lirc/
	rm -rf ${D}/dev
}

do_install_append_nslu2() {
	install -d ${D}${sysconfdir}
	install ${WORKDIR}/lircd.conf_nslu2 ${D}${sysconfdir}/lircd.conf
	install ${WORKDIR}/lircrc_nslu2 ${D}${sysconfdir}/lircrc
}

do_install_append_spark() {

	install -m 0644 ${WORKDIR}/lircd_spark.conf ${D}${sysconfdir}/lircd.conf
        install -m 0644 ${WORKDIR}/lircd_spark.conf.09_00_0A ${D}${sysconfdir}/lircd.conf.09_00_0A
        install -m 0755 ${WORKDIR}/lircd_spark.init ${D}${sysconfdir}/init.d/lircd
        rm -rf  ${D}/bin/pronto2lirc 
}

PACKAGES =+ "lirc-exec lirc-remotes"
PACKAGES_prepend_nslu2 = "lirc-nslu2example "

FILES_${PN}-dbg += "${bindir}/.debug ${sbindir}/.debug"
FILES_${PN}-dev += "${libdir}/liblirc_client.so"
FILES_${PN} = "${bindir} ${sbindir} ${libdir}/lib*.so.* ${sysconfdir} ${exec_prefix}/var"
FILES_lirc-exec = "${bindir}/irexec ${sysconfdir}/init.d/lircexec"
FILES_lirc-remotes = "${datadir}/lirc/remotes"
FILES_lirc-nslu2example = "${sysconfdir}/lircd.conf ${sysconfdir}/lircrc"
CONFFILES_lirc-nslu2example = "${FILES_lirc-nslu2example}"
