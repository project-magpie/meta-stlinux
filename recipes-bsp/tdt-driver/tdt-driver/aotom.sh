#!/bin/sh

# Create aotom device if not present
if ! [ -e /dev/vfd ] ; then
	/bin/mknod /dev/vfd c 147 0
fi

