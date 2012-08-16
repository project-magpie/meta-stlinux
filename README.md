OpenEmbedded BSP Layer - For STLinux sh4 based Set-Top-Boxes 
============================================================

This is the general hardware specific BSP overlay for STLinux based devices.
It should be used with openembedded-core (not old-style org.openembedded.dev).

More information can be found at:


This layer in its entirety depends on:

    URI: git://git.openembedded.org/openembedded-core
    branch: denzil 
    revision: HEAD

    URI: git://git.openembedded.org/meta-openembedded
    branch: denzil 
    revision: HEAD

It is preferred that people raise pull requests using GIThub by forking the appropriate tree:

                   https://github.com/project-magpie/meta-stlinux.git
                   (More info on achieving this can be found at http://help.github.com/send-pull-requests/)


How to use it:

1. source openembedded-core/oe-init-build-env stlinux-build
2. Add meta-stlinux in bblayers.conf
3.  Set MACHINE to spark in local.conf
4. bitbake core-image-minimal 


