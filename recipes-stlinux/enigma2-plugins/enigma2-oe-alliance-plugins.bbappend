DESCRIPTION = "Additional plugins for Enigma2"
MAINTAINER = "oe-alliance team"
PACKAGE_ARCH = "${MACHINE_ARCH}"

# Remove dependencies that cannot be built for sh4
RDEPENDS_enigma2-plugin-systemplugins-vfdcontrol_spark = ""
RDEPENDS_enigma2-plugin-systemplugins-vfdcontrol_spark7162 = ""
RDEPENDS_enigma2-plugin-extensions-webbrowser_spark = ""
RDEPENDS_enigma2-plugin-extensions-webbrowser_spark7162 = ""
RDEPENDS_enigma2-plugin-extensions-hbbtv_spark = ""
RDEPENDS_enigma2-plugin-extensions-hbbtv_spark7162 = ""

DEPENDS_spark = "enigma2 \
	${@base_contains("MACHINE_FEATURES", "blindscan-dvbc", "virtual/blindscan-dvbc" , "", d)} \
	${@base_contains("MACHINE_FEATURES", "blindscan-dvbs", "virtual/blindscan-dvbs" , "", d)} \
	python-dnspython python-beautifulsoup python-lxml python-simplejson python-pyamf \
        djmount \
        librtmp \
        minidlna \
        hddtemp \
        ppp \
        usbmodeswitch \
        usbmodeswitch-data \
        wvdial \
        wvstreams \
        usbutils \
        gmp \
        tslib \
        mpfr \
	"

DEPENDS_spark7162 = "enigma2 \
        ${@base_contains("MACHINE_FEATURES", "blindscan-dvbc", "virtual/blindscan-dvbc" , "", d)} \
        ${@base_contains("MACHINE_FEATURES", "blindscan-dvbs", "virtual/blindscan-dvbs" , "", d)} \
        python-dnspython python-beautifulsoup python-lxml python-simplejson python-pyamf \
        djmount \
        librtmp \
        minidlna \
        hddtemp \
        ppp \
        usbmodeswitch \
        usbmodeswitch-data \
        wvdial \
        wvstreams \
        usbutils \
        gmp \
        tslib \
        mpfr \
        "

SRC_URI_spark="git://github.com/sklnet/oe-alliance-plugins.git;protocol=git"
SRC_URI_spark7162="git://github.com/sklnet/oe-alliance-plugins.git;protocol=git"

