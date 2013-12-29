#!/bin/sh
#
# (C) 2013 Stefan Seyfried, License: WTFPLv2
#
# for "multiarch" SPARK images, we need to do some runtime setup
# early during boot.
# this script does:
# * find out if it is running on spark7111 or spark7162
# * create symlink /lib/modules/<sparkversion>/<kernel> -> /lib/modules/<kernel>
# * create appropriate /lib/firmware/component.fw symlink
#
[ x$1 = xstart ] || exit 0

read a b BOARD < /proc/cpuinfo
read KVER < /proc/sys/kernel/osrelease

# find out what we want
if test "$BOARD" = hdk7105 ; then
	WANTFW=component_7105_hdk7105.fw # firmware file
	WANT=7162	# modules dir
else
	WANTFW=component_7111_mb618.fw
	WANT=7111
fi
# firmware...
FWFILE=`readlink -f /lib/firmware/component.fw`
case "$FWFILE" in
	*/$WANTFW) ;;	# already correct, do nothing
	*)	echo "changing component.fw symlink to $WANTFW"
		rm -f /lib/firmware/component.fw
		ln -s $WANTFW /lib/firmware/component.fw ;;
esac

CURRLINK=`readlink -f /lib/modules/${KVER}`
case $CURRLINK in
	/lib/modules/$WANT/*)
		exit 0 ;;	# also correct -> get out
	*)	;;
esac

printf "changing module symlink to $WANT/${KVER}... "
rm -f /lib/modules/$KVER
ln -s $WANT/$KVER /lib/modules/
printf "updating module dependencies... "
depmod -a
echo "done."
