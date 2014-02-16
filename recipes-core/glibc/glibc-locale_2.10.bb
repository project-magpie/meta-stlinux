INHIBIT_DEFAULT_DEPS = "1"
LICENSE = "GPLv2 & LGPLv2.1"

BPN = "glibc"

do_fetch[noexec] = "1"
do_unpack[noexec] = "1"
do_patch[noexec] = "1"
do_configure[noexec] = "1"
do_compile[noexec] = "1"

# Binary locales are generated at build time if ENABLE_BINARY_LOCALE_GENERATION
# is set. The idea is to avoid running localedef on the target (at first boot)
# to decrease initial boot time and avoid localedef being killed by the OOM
# killer which used to effectively break i18n on machines with < 128MB RAM.

# default to disabled 
ENABLE_BINARY_LOCALE_GENERATION ?= "0"
ENABLE_BINARY_LOCALE_GENERATION_pn-glibc-locale-nativesdk = "0"

#enable locale generation on these arches
# BINARY_LOCALE_ARCHES is a space separated list of regular expressions
BINARY_LOCALE_ARCHES ?= "arm.* i[3-6]86 x86_64 powerpc mips"

# set "1" to use cross-localedef for locale generation
# set "0" for qemu emulation of native localedef for locale generation
LOCALE_GENERATION_WITH_CROSS-LOCALEDEF = "1"

PR = "x32.r0"

PKGSUFFIX = ""
PKGSUFFIX_virtclass-nativesdk = "-nativesdk"

PROVIDES = "virtual/libc-locale${PKGSUFFIX}"

PACKAGES = "localedef${PKGSUFFIX} ${PN}-dbg"

PACKAGES_DYNAMIC = "locale-base-* \
                    eglibc-gconv-*${PKGSUFFIX} eglibc-charmap-*${PKGSUFFIX} eglibc-localedata-* eglibc-binary-localedata-* \
                    glibc-gconv-*${PKGSUFFIX}  glibc-charmap-*${PKGSUFFIX}  glibc-localedata-*  glibc-binary-localedata-*"

# Create a glibc-binaries package
ALLOW_EMPTY_${BPN}-binaries${PKGSUFFIX} = "1"
PACKAGES += "${BPN}-binaries${PKGSUFFIX}"
RRECOMMENDS_${BPN}-binaries${PKGSUFFIX} =  "${@" ".join([p for p in d.getVar('PACKAGES', True).split() if p.find("glibc-binary${PKGSUFFIX}") != -1])}"

# Create a glibc-charmaps package
ALLOW_EMPTY_${BPN}-charmaps${PKGSUFFIX} = "1"
PACKAGES += "${BPN}-charmaps${PKGSUFFIX}"
RRECOMMENDS_${BPN}-charmaps${PKGSUFFIX} =  "${@" ".join([p for p in d.getVar('PACKAGES', True).split() if p.find("glibc-charmap${PKGSUFFIX}") != -1])}"

# Create a glibc-gconvs package
ALLOW_EMPTY_${BPN}-gconvs${PKGSUFFIX} = "1"
PACKAGES += "${BPN}-gconvs${PKGSUFFIX}"
RRECOMMENDS_${BPN}-gconvs${PKGSUFFIX} =  "${@" ".join([p for p in d.getVar('PACKAGES', True).split() if p.find("glibc-gconv${PKGSUFFIX}") != -1])}"

# Create a glibc-localedatas package
ALLOW_EMPTY_${BPN}-localedatas${PKGSUFFIX} = "1"
PACKAGES += "${BPN}-localedatas${PKGSUFFIX}"
RRECOMMENDS_${BPN}-localedatas${PKGSUFFIX} =  "${@" ".join([p for p in d.getVar('PACKAGES', True).split() if p.find("glibc-localedata${PKGSUFFIX}") != -1])}"

DESCRIPTION_localedef = "glibc: compile locale definition files"

# glibc-gconv is dynamically added into PACKAGES, thus
# FILES_glibc-gconv will not be automatically extended in multilib.
# Explicitly add ${MLPREFIX} for FILES_glibc-gconv.
FILES_${MLPREFIX}glibc-gconv = "${libdir}/gconv/*"
FILES_${PN}-dbg += "${libdir}/gconv/.debug/*"
FILES_localedef${PKGSUFFIX} = "${bindir}/localedef"

LOCALETREESRC = "${STAGING_INCDIR}/eglibc-locale-internal-${MULTIMACH_TARGET_SYS}"

do_install () {
	mkdir -p ${D}${bindir} ${D}${datadir} ${D}${libdir}
	if [ -n "$(ls ${LOCALETREESRC}/${bindir})" ]; then
		cp -fpPR ${LOCALETREESRC}/${bindir}/* ${D}${bindir}
	fi
	if [ -e ${LOCALETREESRC}/${libdir}/locale ]; then
		cp -fpPR ${LOCALETREESRC}/${libdir}/locale ${D}${libdir}
	fi
	if [ -e ${LOCALETREESRC}/${libdir}/gconv ]; then
		cp -fpPR ${LOCALETREESRC}/${libdir}/gconv ${D}${libdir}
	fi
	if [ -e ${LOCALETREESRC}/${datadir}/i18n ]; then
		cp -fpPR ${LOCALETREESRC}/${datadir}/i18n ${D}${datadir}
	fi
	if [ -e ${LOCALETREESRC}/${datadir}/locale ]; then
		cp -fpPR ${LOCALETREESRC}/${datadir}/locale ${D}${datadir}
	fi
	cp -fpPR ${LOCALETREESRC}/SUPPORTED ${WORKDIR}
}

inherit libc-package

do_install[depends] += "virtual/libc${PKGSUFFIX}:do_populate_sysroot"

BBCLASSEXTEND = "nativesdk"
