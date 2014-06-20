require linux-stm.inc

# INC_PR is defined in the .inc file if something has change here just increase the number after the dot
PR = "${INC_PR}.14"

PV = "${LINUX_VERSION}-stm24-0214"
SRCREV = "${AUTOREV}"

DEPENDS += " \
           stlinux24-sh4-stx7105-fdma-firmware \
"
