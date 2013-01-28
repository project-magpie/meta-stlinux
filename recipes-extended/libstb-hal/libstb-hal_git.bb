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
PR = "r5"

PACKAGES += "pic2m2v spark-fp"

RDEPENDS_pic2m2v = "ffmpeg"

SRC_URI = " \
            git://gitorious.org/neutrino-hd/libstb-hal.git;protocol=git \
            file://COPYING.GPL \
"

S = "${WORKDIR}/git"

inherit autotools pkgconfig

CFLAGS_append = "-Wall -W -Wshadow -g -O2 -fno-strict-aliasing -rdynamic -DNEW_LIBCURL"
CFLAGS_spark += "-funsigned-char \
"


LDFLAGS = " -Wl,-rpath-link,${STAGING_DIR_HOST}/usr/lib -L${STAGING_DIR_HOST}/usr/lib"

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

do_install_append () {

	install -d ${D}/${includedir}/libstbhal/libstbhal
	install -d ${D}/${includedir}/libstbhal/common
	install -d ${D}/${includedir}/libstbhal/libspark
	install -d ${D}/${includedir}/libstbhal/libspark/td-compat
	install -d ${D}/${bindir}

	cp ${S}/include/*.h ${D}/${includedir}/libstbhal/libstbhal
	cp ${S}/common/*.h ${D}/${includedir}/libstbhal/common
	cp ${S}/libspark/*.h ${D}/${includedir}/libstbhal/libspark
	cp ${S}/libspark/td-compat/*.h ${D}/${includedir}/libstbhal/libspark/td-compat
	install -m755 ${S}/tools/pic2m2v ${D}/${bindir}
	install -m755 ${S}/tools/spark_fp ${D}/${bindir}
}

FILES_${PN} = "/usr/bin/libstb-hal-test /usr/bin/meta /usr/bin/eplayer3"


FILES_${PN}-dev += "${includedir}/libstbhal/* \
                    ${includedir}/libspark/* \
                    ${includedir}/libspark/td-compat/* \
"

FILES_pic2m2v = "${bindir}/pic2m2v"
FILES_spark-fp = "${bindir}/spark_fp"
