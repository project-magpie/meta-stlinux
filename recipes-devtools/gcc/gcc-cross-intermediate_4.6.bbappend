FILESEXTRAPATHS := "${THISDIR}/files"
PRINC := "${@int(PRINC) + 2}"

do_compile_prepend() {
         # On x86_64, glibc-initial stages crti.o to
         # x86_64-oe-linux/lib64/crti.o.
         # When gcc-cross-intermediate tries to build libgcc, it looks
         # for x86_64-oe-linux/lib/../lib64/crti.o.
         # Create the "lib" dir so this shenanigan works.
         install -d ${STAGING_DIR_TARGET}/lib
}
