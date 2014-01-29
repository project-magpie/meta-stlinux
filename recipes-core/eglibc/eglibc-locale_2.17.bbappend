#
# we need this until this patch is applied: http://lists.openembedded.org/pipermail/openembedded-core/2013-November/085826.html
#
do_install_append () {
    # look for empty directory and remove it
    # Otherwise an QA Error is spawned
    if [ "$(ls -A ${D}${localedir})" ]; then
         echo "The directory ${D}${localedir} is not Empty"
    else
        rm -r ${D}${localedir}
    fi
}