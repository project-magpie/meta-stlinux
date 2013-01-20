SUMMARY = "Library to abstract STB hardware. Supports Tripledragon, AZbox ME and Fulan Spark boxes right now."
DESCRIPTION = "Library to abstract STB hardware."
HOMEPAGE = "https://gitorious.org/neutrino-hd/libstb-hal"
SECTION = "libs"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING.GPL;md5=751419260aa954499f7abaabaa882bbe \
"

DEPENDS = "tdt-driver libass ffmpeg"

SRCREV = "393f5452f46bd370c8c191ba6c9b8710b3b653bd"
PV = "0.0+git${SRCPV}"
PR = "r0"

SRC_URI = " \
            git://gitorious.org/neutrino-hd/libstb-hal.git;protocol=git \
            file://COPYING.GPL \
"

S = "${WORKDIR}/git"

inherit autotools pkgconfig

EXTRA_OECONF += "\
                     --enable-maintainer-mode \
                     --with-target=cdk \
                     --enable-silent-rules \
"

EXTRA_OECONF_spark += "\
                     --with-boxtype=spark \
"
EXTRA_OECONF_spark7162 += "\
                     --with-boxtype=spark \
"
