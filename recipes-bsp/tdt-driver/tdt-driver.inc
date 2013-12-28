HOMEPAGE = "http://gitorious.org/open-duckbox-project-sh4"
SECTION = "kernel/modules"
RDEPENDS_${PN} = "ustslave"

LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING;md5=751419260aa954499f7abaabaa882bbe"

inherit module

PACKAGES = "${PN} ${PN}-dev"
PACKAGES_DYNAMIC += "kernel-module-*"

SRCREV = "a187619deaf19d8419c3a868b78581fbbc3e7898"


BINARY_PTI_NP_PATH ?= "/data/pti_np"

# using our own tdt drivers because this has less overhead
SRC_URI = " \
        git://github.com/project-magpie/tdt-driver.git \
        file://0001-player2_191-silence-kmsg-spam.patch;apply=yes \
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
        file://tdt-driver-avoid-buildtime.patch \
        file://aotom_udev.rules \
        file://COPYING \
" 
PV = "0.2+git${SRCPV}"

FILES_${PN} = "/etc/udev/rules.d "
FILES = ""

S = "${WORKDIR}/git"

do_configure_prepend () {
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
    ln -s ${S}/include/stmfb-3.1_stm24_0102 ${S}/include/stmfb
    ln -s ${S}/include/player2_179 ${S}/include/player2
    ln -s ${S}/multicom-3.2.4/include ${S}/include/multicom
    ln -s ${S}/player2_191 ${S}/player2
    ln -s ${S}/multicom-3.2.4 ${S}/multicom
    ln -s ${S}/stgfb/stmfb-3.1_stm24_0102 ${S}/stgfb/stmfb
    rm -f .config 
    printf "export CONFIG_PLAYER_191=y\nexport CONFIG_MULTICOM324=y\n" > .config
    # disable wireless build
    # sed -i 's/^\(obj-y.*+= wireless\)/# \1/' Makefile
    # disable led and button - it's not for spark
    #sed -i 's@^\(obj-y.*+= \(led\|button\)/\)@# \1@' Makefile
}



do_compile() {
    unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
    oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
               KERNEL_SRC=${STAGING_KERNEL_DIR}    \
               KERNEL_VERSION=${KERNEL_VERSION}    \
       -C ${STAGING_KERNEL_DIR}   \
           ${@d.getVar('MACHINE',1).upper()}=1 \
               M=${S} V=1 \
               ARCH=sh \
       PLAYER191=player191 \
           DRIVER_TOPDIR="${S}" \
           KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
           CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
           CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
           CONFIG_MODULES_PATH="${D}" \
       CONFIG_PLAYER_191=y \
       CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
       modules 
}

do_install() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
                   KERNEL_SRC=${STAGING_KERNEL_DIR}    \
                   KERNEL_VERSION=${KERNEL_VERSION}    \
           -C ${STAGING_KERNEL_DIR}   \
               ${@d.getVar('MACHINE',1).upper()}=1 \
                   M=${S} V=1 \
                   ARCH=sh \
           PLAYER191=player191 \
               DRIVER_TOPDIR="${S}" \
               KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
               CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
               CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
               CONFIG_MODULES_PATH="${D}" \
           CONFIG_PLAYER_191=y \
           CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
           INSTALL_MOD_PATH=${D} modules_install

        # install header files
    install -d ${D}/${includedir}/linux/dvb
        
    install -m 644 bpamem/bpamem.h ${D}/${includedir}
    install -m 644 frontcontroller/aotom/aotom_main.h ${D}/${includedir}
    install -m 644 player2/linux/include/linux/dvb/stm_ioctls.h ${D}/${includedir}/linux/dvb
    install -m 644 stgfb/stmfb/linux/drivers/video/stmfb.h ${D}/${includedir}/linux

    #install modutils config
    install -d ${D}/${sysconfdir}/modules-load.d
    install -d ${D}/${sysconfdir}/modprobe.d
    install -d ${D}/${sysconfdir}/udev/rules.d/
    
    cp ${WORKDIR}/aotom_udev.rules ${D}/${sysconfdir}/udev/rules.d/32-aotom.rules
 
    # if a custom pti.ko is present, overwrite the tdt one
    if [ -e ${BINARY_PTI_NP_PATH}/pti_${STM_PATCH_STR}.ko ]; then
           echo "Found custom pti.." 
           install -m 644 ${BINARY_PTI_NP_PATH}/pti_${STM_PATCH_STR}.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/pti/
    fi
}

do_install_append_spark7162() {
    find ${D} -name stmcore-display-sti7106.ko | xargs -r rm # we don't have a 7106 chip
}

FILES_${PN}-dev += "${includedir}"

