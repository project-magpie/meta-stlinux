#!/bin/sh

# fix aotom vfd
#rm /dev/vfd
if ! [ -e /dev/vfd ] ; then
	/bin/mknod /dev/vfd c 147 0
fi

if ! [ -e /dev/rtc0 ] ; then
	/bin/mknod /dev/rtc0 c 10 135 
	ln -s /dev/rtc0 /dev/rtc
fi
