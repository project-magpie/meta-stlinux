require recipes-kernel/linux/linux-stm.inc

STM_PATCH_STR = "0210"
PR = "r9"
PV = "${LINUX_VERSION}-stm24-${STM_PATCH_STR}"

DESCRIPTION = "Linux kernel from stlinux"

KBRANCH = "stmicro"

KTAG = "stlinux24_0210"
KTAG_spark = "stlinux24_0210"


LINUX_VERSION ?= "2.6.32.57"

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-stm:"

SRCREV="7367427b3c1b8965a0f5c960a18c5c802ad2eb8f"
SRC_URI = "git://git.stlinux.com/stm/linux-sh4-2.6.32.y.git;protocol=git;branch=stmicro \
file://linux-sh4-linuxdvb_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-sound_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-time_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-init_mm_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-copro_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-squashfs-lzma_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-ext23_as_ext4_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://bpa2_procfs_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-ftdi_sio.c_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-lzma-fix_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-tune_stm24.patch;patch=1 \
file://linux-sh4-stmmac_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-lmb_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-spark_setup_stm24_${STM_PATCH_STR}_multi_yaffs2.patch;patch=1 \
file://linux-sh4-cifs-unaligned-mem-access-kernel_stm24.patch;patch=1 \
file://linux-sh4-linux_yaffs2_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://linux-sh4-lirc_stm24_${STM_PATCH_STR}.patch;patch=1 \
file://0001-added-pm_power_off-hoock-for-machine_halt.patch;patch=1 \
file://${MACHINE}_defconfig \
file://st-coprocessor.h \
"


COMPATIBLE_MACHINE = "spark|spark7162"

PARALLEL_MAKEINST = ""

# CMDLINE for spark
CMDLINE_spark = "console=ttyAMA0,115200 rootfstype=ext4 rootwait"

S = "${WORKDIR}/git"

do_configure() {
	rm -f ${S}/.config || true
   	cp ${WORKDIR}/${MACHINE}_defconfig ${S}/.config
        yes '' | oe_runmake oldconfig
}

do_install_append() {
	kerneldir=${D}${KERNEL_SRC_PATH}
	if [ -f include/linux/bounds.h ]; then
		mkdir -p $kerneldir/include/linux
                cp include/linux/bounds.h $kerneldir/include/linux/bounds.h
        fi
        if [ -f include/asm-sh/machtypes.h ]; then
		mkdir -p $kerneldir/include/asm-sh
		cp include/asm-sh/machtypes.h $kerneldir/include/asm-sh
	fi
	install -d ${D}${includedir}/linux	
   	install -m 644 ${WORKDIR}/st-coprocessor.h ${D}${includedir}/linux
}


FILES_kernel-dev += "${includedir}/linux"

