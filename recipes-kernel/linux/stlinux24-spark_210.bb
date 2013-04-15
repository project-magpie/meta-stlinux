require linux-stm.inc

# INC_PR is defined in the .inc file if something has change here just increase the number after the dot
PR = "${INC_PR}.12"


DEPENDS += " \
           stlinux24-sh4-stx7111-fdma-firmware \
"

#             file://linux-sh4-strcpy_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \


SRC_URI_append = "\
             file://linux-sh4-linuxdvb_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-sound_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-time_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-init_mm_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-copro_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-squashfs-lzma_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-ext23_as_ext4_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://bpa2_procfs_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-ftdi_sio.c_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-lzma-fix_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-tune_stm24.patch;patch=1 \
             file://linux-sh4-stmmac_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-lmb_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-spark_setup_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
             file://linux-sh4-cifs-unaligned-mem-access-kernel_stm24.patch;patch=1 \
             file://linux-sh4-linux_yaffs2_stm24_${STM_LINUX_PATCH_STR}.patch;patch=1 \
"

#             file://0001-added-pm_power_off-hoock-for-machine_halt.patch;patch=1 \

do_configure () {
	sed -i "s#^\(CONFIG_EXTRA_FIRMWARE_DIR=\).*#\1\"${STAGING_DIR_HOST}/lib/firmware\"#" .config;
        yes '' | oe_runmake oldconfig
}

