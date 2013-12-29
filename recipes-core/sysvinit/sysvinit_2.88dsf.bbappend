FILESEXTRAPATHS := "${THISDIR}/files"

PRINC := "${@int(PRINC) + 5}"

SRC_URI_append = " \
                  file://devinit \
"

# we do not need this, because this cost boottime 
do_install_append() {
        install -d ${D}/bin
        install -m 755 ${WORKDIR}/devinit ${D}/bin
        find  ${D}${sysconfdir}/rc* -name "*bootlogd" -exec rm {} \;
        # AOTOM rtc needs to be in localtime or standby time display will be wrong.
        sed -i -e '/^UTC=yes/{
s/^/# /;
a# *** aotom RTC on SPARK needs hwclock in localtime ***
aUTC=no
}' ${D}${sysconfdir}/default/rcS
}

FILES_${PN} += " \
                /bin \
"
