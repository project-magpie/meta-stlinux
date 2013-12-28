HOMEPAGE = "http://gitorious.org/open-duckbox-project-sh4"
SECTION = "kernel/modules"
RDEPENDS_${PN} = "ustslave"

LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING;md5=751419260aa954499f7abaabaa882bbe"

inherit module

PACKAGES = "${PN} ${PN}-dev"
# PACKAGES_DYNAMIC += "kernel-module-*"
# without this, tdt-driver package will depend on lots of unavailable kernel-module-*
# (all those modules are in tdt-driver)
KERNEL_MODULES_META_PACKAGE = "None"

SRCREV = "a187619deaf19d8419c3a868b78581fbbc3e7898"


BINARY_PTI_NP_PATH ?= "/data/pti_np"

# using our own tdt drivers because this has less overhead
SRC_URI = " \
        git://github.com/project-magpie/tdt-driver.git \
        file://0001-player2_191-silence-kmsg-spam.patch;apply=no \
        file://0002-e2proc-silence-kmsg-spam.patch \
        file://0003-pti-silence-kmsg-spam.patch \
        file://0004-stmfb-silence-kmsg-spam.patch \
        file://0005-frontends-spark_dvbapi5-silence-kmsg-spam.patch \
        file://0006-frontends-spark7162-silence-kmsg-spam.patch;apply=yes \
        file://0001-import-cec-from-pinky-s-git.patch \
        file://0002-aotom-fix-include-file.patch \
        file://0003-aotom-add-VFDGETVERSION-ioctl-to-find-FP-type.patch \
        file://0004-aotom-improve-scrolling-text-code.patch \
        file://0005-aotom-speed-up-softi2c-lowering-CPU-load-of-aotom-dr.patch \
        file://0006-aotom-add-additional-chars-for-VFD-fix-missing-chars.patch \
        file://0007-aotom-register-reboot_notifier-implement-rtc-driver.patch \
        file://aotom_udev.rules \
        file://COPYING \
" 
PV = "0.2+git${SRCPV}"

FILES_${PN} = "/etc/udev/rules.d "
FILES = ""

S = "${WORKDIR}/git"

do_configure() {
    if [ -L include/stmfb ]; then
        rm include/stmfb
    fi
    if [ -L include/player2 ]; then
        rm include/player2
    fi
    if [ -L include/multicom ]; then
        rm include/multicom
    fi
    if [ -L player2 ]; then
        rm player2
    fi
    if [ -L stgfb/stmfb ]; then
        rm stgfb/stmfb
    fi
    if [ -L multicom ]; then
        rm multicom
    fi
    ln -s stmfb-3.1_stm24_0102 ${S}/include/stmfb
    ln -s player2_179 ${S}/include/player2
    ln -s ../multicom-3.2.4/include ${S}/include/multicom
    ln -s player2_191 ${S}/player2
    ln -s multicom-3.2.4 ${S}/multicom
    ln -s stmfb-3.1_stm24_0102 ${S}/stgfb/stmfb
    rm -f .config
    printf "export CONFIG_PLAYER_191=y\nexport CONFIG_MULTICOM324=y\n" > .config
    # disable wireless build
    # sed -i 's/^\(obj-y.*+= wireless\)/# \1/' Makefile
    # disable useless simu_button
    sed -i 's/^\(obj-y.*+= simu_button\)/# \1/' Makefile
    rm -fr ${WORKDIR}/git-7162
    rm -fr ${WORKDIR}/git-7111
    cp -al ${WORKDIR}/git ${WORKDIR}/git-7162
    cp -al ${WORKDIR}/git ${WORKDIR}/git-7111
}



do_compile() {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	for i in 7162 7111; do
		cd ${WORKDIR}/git-$i
		MACH=SPARK
		if [ $i = 7162 ]; then
			MACH=SPARK7162
		fi
		rm -f ${STAGING_KERNEL_DIR}/.config
		cp ${STAGING_KERNEL_DIR}/.config-$i ${STAGING_KERNEL_DIR}/.config
		touch ${STAGING_KERNEL_DIR}/.config # ensure that it is newer
		# do_make_scripts
		bbnote "make scripts for MACH=$MACH, config=.config-$i"
		make CC="${KERNEL_CC}" LD="${KERNEL_LD}" AR="${KERNEL_AR}" \
			-C ${STAGING_KERNEL_DIR} scripts
		bbnote "oe_runmake in ${WORKDIR}/git-$i MACH=$MACH"
		rm -f ${WORKDIR}/build
		ln -s git-$i ${WORKDIR}/build
		cd ${WORKDIR}/build
		oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
			KERNEL_SRC=${STAGING_KERNEL_DIR}    \
			KERNEL_VERSION=${KERNEL_VERSION}    \
			-C ${STAGING_KERNEL_DIR}   \
			$MACH=1 \
			M=${WORKDIR}/build V=1 \
			ARCH=sh \
			PLAYER191=player191 \
			DRIVER_TOPDIR="${WORKDIR}/git-$i" \
			KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
			CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
			CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
			CONFIG_MODULES_PATH="${D}" \
			CONFIG_PLAYER_191=y \
			CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
			${PARALLEL_MAKE} \
			modules
	done
}

do_install() {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
	for i in 7162 7111; do
		cd ${WORKDIR}/git-$i
		MACH=SPARK
		if [ $i = 7162 ]; then
			MACH=SPARK7162
		fi
		rm -f ${STAGING_KERNEL_DIR}/.config
		cp ${STAGING_KERNEL_DIR}/.config-$i ${STAGING_KERNEL_DIR}/.config
		touch ${STAGING_KERNEL_DIR}/.config # ensure that it is newer
		# do_make_scripts
		bbnote "make scripts for MACH=$MACH, config=.config-$i"
		make CC="${KERNEL_CC}" LD="${KERNEL_LD}" AR="${KERNEL_AR}" \
			-C ${STAGING_KERNEL_DIR} scripts
		bbnote "oe_runmake modules_install in ${WORKDIR}/git-$i MACH=$MACH"
		rm -f ${WORKDIR}/build
		ln -s git-$i ${WORKDIR}/build # this avoids binaries differing due to pathnames
		cd ${WORKDIR}/build
		oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
			KERNEL_SRC=${STAGING_KERNEL_DIR}    \
			KERNEL_VERSION=${KERNEL_VERSION}    \
			-C ${STAGING_KERNEL_DIR}   \
			$MACH=1 \
			M=${WORKDIR}/build V=1 \
			ARCH=sh \
			PLAYER191=player191 \
			DRIVER_TOPDIR="${WORKDIR}/git-$i" \
			KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
			CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
			CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
			CONFIG_MODULES_PATH="${D}" \
			CONFIG_PLAYER_191=y \
			CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
			INSTALL_MOD_PATH=${D} modules_install
		mkdir ${D}/lib/modules/$i
		mv ${D}/lib/modules/${KERNEL_VERSION} ${D}/lib/modules/$i
	done
	# $PWD is git-7111
	# install header files
	install -d ${D}/${includedir}/linux/dvb
	install -m 644 bpamem/bpamem.h ${D}/${includedir}
	install -m 644 frontcontroller/aotom/aotom_main.h ${D}/${includedir}
	install -m 644 player2/linux/include/linux/dvb/stm_ioctls.h ${D}/${includedir}/linux/dvb
	install -m 644 stgfb/stmfb/linux/drivers/video/stmfb.h ${D}/${includedir}/linux

	#install modutils config
	# install -d ${D}/${sysconfdir}/modules-load.d
	# install -d ${D}/${sysconfdir}/modprobe.d
	install -d ${D}/${sysconfdir}/udev/rules.d/
	cp ${WORKDIR}/aotom_udev.rules ${D}/${sysconfdir}/udev/rules.d/32-aotom.rules

	# if a custom pti.ko is present, overwrite the tdt one
	#if [ -e ${BINARY_PTI_NP_PATH}/pti_${STM_PATCH_STR}.ko ]; then
	#	echo "Found custom pti.." 
	#	install -m 644 ${BINARY_PTI_NP_PATH}/pti_${STM_PATCH_STR}.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/pti/
	#fi
	find ${D} -name stmcore-display-sti7106.ko | xargs -r rm # we don't have a 7106 chip

	cd ${D}/lib/modules
	for i in `find 7111 -name '*.ko'`; do
		j=7162${i#7111}
		[ -e $j ] || continue
		A="`md5sum < $i`"
		B="`md5sum < $j`"
		[ "$A" = "$B" ] || continue
		bbnote "$i == $j => hardlink"
		rm $j
		ln $i $j # hardlink!
	done
}

MOD7111 = "/lib/modules/7111/${KERNEL_VERSION}/extra"
MOD7162 = "/lib/modules/7162/${KERNEL_VERSION}/extra"
# include all except wireless, so that they can be installed separately
# i2c_spi module (7162) is also not included, it's very special and should
# only be used for testing anyway.
FILES_${PN} += " \
	${MOD7111}/avs		${MOD7162}/avs \
	${MOD7111}/boxtype	${MOD7162}/boxtype \
	${MOD7111}/bpamem	${MOD7162}/bpamem \
	${MOD7111}/cec		${MOD7162}/cec \
	${MOD7111}/compcache	${MOD7162}/compcache \
	${MOD7111}/cpu_frequ	${MOD7162}/cpu_frequ \
	${MOD7111}/e2_proc	${MOD7162}/e2_proc \
	${MOD7111}/frontcontroller ${MOD7162}/frontcontroller \
	${MOD7111}/frontends	${MOD7162}/frontends \
	${MOD7111}/multicom	${MOD7162}/multicom \
	${MOD7111}/player2	${MOD7162}/player2 \
	${MOD7111}/pti		${MOD7162}/pti \
	${MOD7111}/smartcard	${MOD7162}/smartcard \
	${MOD7111}/stgfb	${MOD7162}/stgfb \
	/etc/modules-load.d \
"
pkg_postinst_${PN}() {
#!/bin/sh
# create the default symlink to 7111 module dir or image build will fail.
if ! [ -e $D/lib/modules/${KERNEL_VERSION} ]; then
	ln -s 7111/${KERNEL_VERSION} $D/lib/modules/
fi
if [ -z "$D" ]; then
	depmod -a ${KERNEL_VERSION}
else
	depmodwrapper -a -b $D ${KERNEL_VERSION}
fi
}

FILES_${PN}-dev += "${includedir}"
