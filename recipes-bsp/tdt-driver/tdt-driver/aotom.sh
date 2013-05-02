#!/bin/sh

# fix aotom vfd
rm /dev/vfd
/bin/mknod /dev/vfd c 147 0

