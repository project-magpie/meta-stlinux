DESCRIPTION = "Handle your EPG on enigma2 from various sources (opentv, mhw, xmltv, custom sources)"
HOMEPAGE = "https://github.com/E2OpenPlugins/e2openplugin-CrossEPG"

do_install_spark() {
        export TARGET_ARCH=sh4
        oe_runmake 'D=${D}' install
}

do_install_spark7162() {
        export TARGET_ARCH=sh4
	oe_runmake 'D=${D}' install
}
