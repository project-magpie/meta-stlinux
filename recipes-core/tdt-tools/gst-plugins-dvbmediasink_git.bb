DESCRIPTION = "TDT gstreamer dvbmediasink plugin"
SECTION = "multimedia"
PRIORITY = "optional"
DEPENDS = "gstreamer gst-plugins-base libdca"
LICENSE = "proprietary"

PROVIDES = "gst-plugin-dvbmediasink"

require tdt-tools.inc

PV = "0.10.1+git${SRCPV}"
PR = "r0"

FILES_${PN} = "${libdir}/gstreamer-0.10/*.so*"
FILES_${PN}-dev += "${libdir}/gstreamer-0.10/*.la ${libdir}/gstreamer-0.10/*.a"
FILES_${PN}-dbg += "${libdir}/gstreamer-0.10/.debug"

