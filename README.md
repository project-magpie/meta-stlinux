OpenEmbedded BSP Layer - For STLinux sh4 based Set-Top-Boxes 
============================================================

This is the general hardware specific BSP overlay for STLinux based devices.
It should be used with openembedded-core (not old-style org.openembedded.dev).


This layer in its entirety depends on:

    URI: git://git.openembedded.org/openembedded-core
    branch: denzil 
    revision: HEAD

It is preferred that people raise pull requests using GIThub by forking the appropriate tree:

                   https://github.com/project-magpie/meta-stlinux.git
                   (More info on achieving this can be found at http://help.github.com/send-pull-requests/)


How to use it:
--------------

Clone openembedded-core:

    git clone git://git.openembedded.org/openembedded-core oe-core

Switch to denzil branch:

    cd oe-core
    git checkout -b denzil remotes/origin/denzil

Clone bitbake into the oe-core folder:

    git clone git://git.openembedded.org/bitbake bitbake
    git checkout -b f8bf449 f8bf449

Move to top folder:

    cd ..
Initialize the build environment:

    source openembedded-core/oe-init-build-env stlinux-build

Add meta-stlinux in bblayers.conf and set MACHINE to spark in local.conf

Run bitbake: 

    bitbake core-image-minimal 


