DESCRIPTION = "gstreamer libxtrend plugin"
LICENSE = "CLOSED"
SECTION = "multimedia"
PRIORITY = "optional"

PRINC = "1"

do_install_append_spark() {
# we don't have a libxtrend plugin for sh4, thus we remove the mipsel lib
        rm ${D}${libdir}/gstreamer-0.10/libgstxt.so
}

do_install_append_spark7162() {
# we don't have a libxtrend plugin for sh4, thus we remove mipsel lib
        rm ${D}${libdir}/gstreamer-0.10/libgstxt.so
}

