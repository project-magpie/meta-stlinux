SUMMARY = "kernel-based automounter for Linux"
SECTION = "base"
LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://COPYING;md5=0636e73ff0215e8d672dc4c32c317bb3"
PR = "r10.4"

SRC_URI = "${KERNELORG_MIRROR}/linux/daemons/autofs/v4/${BP}.tar.gz \
           file://020_auto_net_path_sortlocale_mountoptions.patch \
           file://037_let_debian_rules_decide_on_CFLAGS.patch \
           file://042_default_auto_master_all_commented_out.patch \
           file://060_non_replicated_ping.patch \
           file://061_multi_parse_fix.patch \
           file://062_fix_memory_leak.patch \
           file://063_misc_fixes.patch \
           file://064_support_options_on_nis_maps.patch \
           file://065_fix_master_map_in_ldap.patch \
           file://066_canonicalise_mount_points.patch \
           file://067_allow_disabling_bind_mounts.patch \
           file://067_ldap_no_first_message.patch \
           file://068_fix_invalid_rpcgen_code.patch \
           file://069_support_spaces_in_smb_share_names.patch \
           file://070_fix_regex_typo.patch \
           file://071_fix_ldap_mounts.patch \
           file://072_fix_auto_net_sort.patch \
           file://073_configurable_locking.patch \
           file://074_auto_smb_cifs.patch \
           file://075_auto_net_escape_hash.patch \
           file://076_ldap_deprecated.patch \
           file://078_locking_fix_1.patch \
           file://079_no_unlink_upstream.patch \
           file://080_auto_smb_probe_credentials.patch \
           file://081_auto_net_showmount_quotes.patch \
           file://082_samples_makefile_typo.patch \
           file://083_clarify_program_map_outputsyntax.patch \
           file://084_init_lsb_header.patch \
           file://085_auto_net_lp111612.patch \
           file://cross.patch \
           file://Makefile.rules-cross.patch \
           file://install.patch \
           file://no-bash.patch \
           file://auto.hotplug \
           file://auto.master \
           file://auto.network \
           file://autofs.default \
           file://autofs.init \
           file://volatiles.99_autofs \
"
SRC_URI[md5sum] = "c092d27caa36c9ac160466ebb4c1cdfa"
SRC_URI[sha256sum] = "d5265d3175c9975604d7e672b18643130f9efe061c9edd55b7a91d003781c395"

S = "${WORKDIR}/${BP}"

inherit autotools update-rc.d

do_configure_prepend () {
        if [ ! -e acinclude.m4 ]; then
                cp aclocal.m4 acinclude.m4
        fi
}
do_install () {
        oe_runmake 'INSTALLROOT=${D}' install
        install -d ${D}${sysconfdir}/default
        install -m 644 ${WORKDIR}/autofs.default ${D}${sysconfdir}/default/autofs
        install -d ${D}${sysconfdir}/init.d
        install -m 755 ${WORKDIR}/autofs.init ${D}${sysconfdir}/init.d/autofs
        install -m 644 ${WORKDIR}/auto.hotplug ${D}${sysconfdir}/auto.hotplug
        install -m 644 ${WORKDIR}/auto.master ${D}${sysconfdir}/auto.master
        install -m 644 ${WORKDIR}/auto.network ${D}${sysconfdir}/auto.network
        install -d ${D}${sysconfdir}/default/volatiles
        install -m 644 ${WORKDIR}/volatiles.99_autofs ${D}${sysconfdir}/default/volatiles/99_autofs
}

RDEPENDS_${PN} = "procps"

INITSCRIPT_NAME = "autofs"
INITSCRIPT_PARAMS = "defaults"

PARALLEL_MAKE = ""

INSANE_SKIP_${PN} = "dev-so"
