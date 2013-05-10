require tdt-tools.inc

DESCRIPTION = "A tool for spark remotes"

SRC_URI_append = "file://evremote2.sh \
"

LDFLAGS += "-lpthread -lrt"

do_install_append () {
        install -d ${D}/${sysconfdir}/init.d
        install -d ${D}/${sysconfdir}/rc3.d
        install -m 0755 ${WORKDIR}/evremote2.sh ${D}${sysconfdir}/init.d
        ln -sf ../init.d/evremote2.sh ${D}${sysconfdir}/rc3.d/S30evremote2
}

