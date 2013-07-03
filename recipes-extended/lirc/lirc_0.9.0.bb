DESCRIPTION = "LIRC is a package that allows you to decode and send infra-red signals of many commonly used remote controls."
DESCRIPTION_append_lirc = " This package contains the lirc daemon, libraries and tools."
DESCRIPTION_append_lirc-exec = " This package contains a daemon that runs programs on IR signals."
DESCRIPTION_append_lirc-remotes = " This package contains some config files for remotes."
SECTION = "console/network"
PRIORITY = "optional"
HOMEPAGE = "http://www.lirc.org"
LICENSE = "GPLv2"
DEPENDS = "virtual/kernel"
RDEPENDS_lirc-exec = "lirc evremote2"
RRECOMMENDS_${PN} = "lirc-exec"

PR = "${INCPR}.2"

EXTRA_OECONF += "--with-kerneldir=${STAGING_KERNEL_DIR} ${DRIVER} --without-x --with-driver=userspace "

inherit autotools module-base update-rc.d
SRC_URI_append = " file://lircd.init \
                   file://lircmd.init \
                   file://lircexec.init \
                 "

SPARK_GEN_SRC_URI += "file://lirc-0.9.0-try_first_last_remote.diff;patch=1 \
                      file://lirc-0.9.0-uinput-repeat-fix.diff;patch=1 \
"

SRC_URI_append_spark += "${SPARK_GEN_SRC_URI} \
			file://lircd_spark.conf \
"

SRC_URI_append_spark7162 += "${SPARK_GEN_SRC_URI} \
			file://lircd_spark7162.conf \
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
        rm -rf  ${D}/bin/pronto2lirc 
}


do_install_append_spark() {
	install -m 0644 ${WORKDIR}/lircd_spark.conf ${D}${sysconfdir}/lircd.conf
}

do_install_append_spark7162() {
	install -m 0644 ${WORKDIR}/lircd_spark7162.conf ${D}${sysconfdir}/lircd.conf
}

PACKAGES =+ "lirc-exec lirc-remotes"

FILES_${PN}-dbg += "${bindir}/.debug ${sbindir}/.debug"
FILES_${PN}-dev += "${libdir}/liblirc_client.so"
FILES_${PN} = "${bindir} ${sbindir} ${libdir}/lib*.so.* ${sysconfdir} ${exec_prefix}/var"
FILES_lirc-exec = "${bindir}/irexec ${sysconfdir}/init.d/lircexec"
FILES_lirc-remotes = "${datadir}/lirc/remotes"
