PRINC := "${@int(PRINC) + 2}"


EXTRA_OECONF_spark += "\
                     --with-boxtype=spark \
                     --with-stb-hal-includes=${STAGING_DIR_HOST}/usr/include/libstbhal/libstbhal \
		     --with-stb-hal-build=${STAGING_DIR_HOST}/usr/lib \
"


EXTRA_OECONF_spark7162 += "\
                     --with-boxtype=spark \
                     --with-stb-hal-includes=${STAGING_DIR_HOST}/usr/include/libstbhal/libstbhal \
		     --with-stb-hal-build=${STAGING_DIR_HOST}/usr/lib \
"
CFLAGS_spark += "-funsigned-char \
"
CFLAGS_spark7162 += "-funsigned-char \
"
