FILESEXTRAPATHS := "${THISDIR}/files"
SRC_URI_append = " \
        file://0020-webkit-disable-the-fuse-ld-gold-flag.patch;patch=1 \
	file://qt-embedded-4.8.0-st200.patch;patch=1 \
	file://qt-embedded-4.8.0-sh4.patch;patch=1 \
	file://qt-embedded-4.8.0-armvX.patch;patch=1 \
	file://qt-embedded-4.8.0-mmap.patch;patch=1 \
	file://qt-embedded-4.8.0-add_SRC_OVER_rule.patch;patch=1 \
	file://qt-embedded-4.8.0-add_window_console_message_from_javaScript.patch;patch=1 \
	file://qt-embedded-4.8.0-reset_CacheLoadControlAttribute_to_default.patch;patch=1 \
	file://qt-embedded-4.8.0-adds_for_webkit_jit.patch;patch=1 \
	file://qt-embedded-4.8.0-directfb-enable-QT_NO_DIRECTFB_PREALLOCATED-QT_DIREC.patch;patch=1 \
	file://qt-embedded-4.8.0-imagedecoderqt-Use-DirectFB-to-load-single-frame-ima.patch;patch=1 \
	file://qt-embedded-4.8.0-st231_disable_fno-stack-protector.patch;patch=1 \
	file://qt-embedded-4.8.0-Accelerate_QtWebKit_animated_images.patch;patch=1 \
"

