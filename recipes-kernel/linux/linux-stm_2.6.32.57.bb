require recipes-kernel/linux/linux-stm.inc

PR = "r3"
PV = "${LINUX_VERSION}-stm24-0210"

DESCRIPTION = "Linux kernel from stlinux"

KBRANCH = "stmicro"

KTAG = "stlinux24_0210"
KTAG_spark = "stlinux24_0210"


LINUX_VERSION ?= "2.6.32.57"

SRCREV="7367427b3c1b8965a0f5c960a18c5c802ad2eb8f"
SRC_URI = "git://git.stlinux.com/stm/linux-sh4-2.6.32.y.git;protocol=git;branch=stmicro \
file://${MACHINE}_defconfig \
"


#KERNEL_DEFCONFIG = "mb618_defconfig"

COMPATIBLE_MACHINE = "spark"

# Functionality flags
#KERNEL_FEATURES = "features/netfilter"
#KERNEL_FEATURES_append = " features/taskstats"
PARALLEL_MAKEINST = ""

# CMDLINE for spark
CMDLINE_spark = "console=ttyAMA0,115200 rootfstype=ext4 rootwait"

S = "${WORKDIR}/git"

#do_configure_prepend() {
#	install -m 0644 ${WORKDIR}/${MACHINE}_defconfig ${WORKDIR}/defconfig || die "No default configuration for ${MACHINE} / ${KERNEL_DEFCONFIG} available."
#	oe_machinstall -m 0644 ${WORKDIR}/${MACHINE}_defconfig ${WORKDIR}/defconfig 
#        oe_runmake oldconfig
#}

do_configure() {
	rm -f ${S}/.config || true
   	cp ${WORKDIR}/${MACHINE}_defconfig ${S}/.config
        yes '' | oe_runmake oldconfig
}

do_install_prepend() {
	install -d ${D}/lib/firmware
}
