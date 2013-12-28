require linux-stm.inc

# INC_PR is defined in the .inc file if something has change here just increase the number after the dot
PR = "${INC_PR}.16"

PV = "${LINUX_VERSION}-stm24-0211"
#SRCREV = "3bce06ff873fb5098c8cd21f1d0e8d62c00a4903"
SRCREV = "${AUTOREV}"

DEPENDS += " \
	stlinux24-sh4-stx7111-fdma-firmware \
	stlinux24-sh4-stx7105-fdma-firmware \
"
