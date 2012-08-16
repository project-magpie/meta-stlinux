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

1. Clone openembedded-core
     git clone git://git.openembedded.org/openembedded-core oe-core
2. Switch to denzil branch
     cd oe-core
     git checkout remotes/origin/denzil
3. Clone bitbake into the oe-core folder
     git clone git://git.openembedded.org/bitbake bitbake
4. move to top folder
     cd ..
5. source openembedded-core/oe-init-build-env stlinux-build
6. Add meta-stlinux in bblayers.conf
7. Set MACHINE to spark in local.conf
8. bitbake core-image-minimal 


