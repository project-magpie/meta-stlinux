FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}/${MACHINE}:"

PRINC := "${@int(PRINC) + 1}"

SRC_URI += " \
     file://fw_env.config \
"

do_install_append() {
        install -d ${D}${sysconfdir}
        install -m 0644 ${WORKDIR}/fw_env.config  ${D}${sysconfdir}
}

