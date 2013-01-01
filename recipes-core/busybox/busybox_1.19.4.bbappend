# Disable any hwclock support because none known machine based on the stlinux has a real time clock.
# The newer BACKFILL mechanism is not availabel on denzil so this crude but it works.

do_configure_prepend () {
   sed -i 's/CONFIG_HWCLOCK=y/CONFIG_HWCLOCK=n/' ${WORKDIR}/defconfig 
}

