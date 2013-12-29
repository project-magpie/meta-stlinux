OE-Alliance BSP Layer - For STLinux sh4 based Set-Top-Boxes 
============================================================

This is the general hardware specific BSP overlay for STLinux based devices.
It should be used with oe-alliance.


How to use it 
-----------------------------------

## Clone oe-alliance build environment
    git clone git://github.com/DvbMedia/build-enviroment.git OEA

## Move to top folder
    cd OEA

## Update
    make update
    
## Initialize the build environment 
    MACHINE=spark7162 DISTRO=<distroname> make init

## create image: 
    MACHINE=spark7162 DISTRO=<distroname> make image

Prerequisite
------------

For the coprocessor firmware loading you have to provide the coprocessor firmware. Put the files either in the folder /data/stslave_fw/${MACHINE} or overwrite the variable  "BINARY_STSLAVE_FW_PATH" in your conf/local.conf file. These files are audio.elf and video.elf. For spark this looks like this: 
-   /data/stslave_fw/spark/video.elf
-   /data/stslave_fw/spark/audio.elf

These files can be extracted from a alternative image and are not part of this repository.
