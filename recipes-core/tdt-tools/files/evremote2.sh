#!/bin/sh

rm /dev/rc
mknod /dev/rc c 147 1 
/usr/bin/evremote2 10 100 &
