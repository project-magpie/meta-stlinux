#
# Configuration to use external STLinux toolchain
#

EXTERNAL_TOOLCHAIN ?= "${STAGING_DIR_TARGET}"

TOOLCHAIN_PATH_ADD = "${EXTERNAL_TOOLCHAIN}/bin:"
PATH =. "${TOOLCHAIN_PATH_ADD}"

STL_TARGET_SYS_sh4 ?= "sh4-linux"
STL_TARGET_SYS = "${TARGET_SYS}"

TARGET_PREFIX = "${STL_TARGET_SYS}-"

PREFERRED_PROVIDER_linux-libc-headers = "external-stlinux-toolchain"
PREFERRED_PROVIDER_linux-libc-headers-dev = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}gcc = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}gcc-initial = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}gcc-intermediate = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}g++ = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}binutils = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}libc-for-gcc = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/${TARGET_PREFIX}compilerlibs = "external-stlinux-toolchain"
PREFERRED_PROVIDER_libgcc = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/libc = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/libintl = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/libiconv = "external-stlinux-toolchain"
PREFERRED_PROVIDER_glibc-thread-db = "external-stlinux-toolchain"
PREFERRED_PROVIDER_virtual/linux-libc-headers = "external-stlinux-toolchain"
PREFERRED_PROVIDER_gdbserver ??= "external-stlinux-toolchain"

# No need to re-compile the locale files
GLIBC_INTERNAL_USE_BINARY_LOCALE = "precompiled"
ENABLE_BINARY_LOCALE_GENERATION = ""

TOOLCHAIN_OPTIONS = " --sysroot=${STAGING_DIR_HOST}"

# Point to the appropriate multilib sysroot from the external toolchain, whose
# files will be extracted into the OE sysroot
def exttc_run(d, cmd):
    try:
        return bb.process.run(cmd, shell=True, env={'PATH': d.getVar('PATH', True)})[0].rstrip()
    except (OSError, bb.process.CmdError):
        return ''

EXTERNAL_TOOLCHAIN_SYSROOT_CMD = "${TARGET_PREFIX}gcc ${TARGET_CC_ARCH} -print-sysroot"
EXTERNAL_TOOLCHAIN_SYSROOT ??= "${@exttc_run(d, EXTERNAL_TOOLCHAIN_SYSROOT_CMD)}"

# These bits are here temporarily to sidestep the need to use a separate set
# of tune files to pass the appropriate multilib selection arguments to the
# stlinux toolchain, as is needed to extract the sysroot content.
TUNE_CCARGS_append_x86 = " -msgxx-glibc"

def csl_multilib_arg(d):
    argument = d.getVarFlag('STL_MULTILIB_ARGS', d.getVar('DEFAULTTUNE', True) or '')
    if argument:
        return argument
    else:
        return ''

EXTERNAL_TOOLCHAIN_SYSROOT_CMD += "${@csl_multilib_arg(d)}"


# Unfortunately, the STL ia32 toolchain has non-prefixed binaries in its
# bindir (e.g. gcc, ld). To avoid this messing up our build, we avoid adding
# this bindir to our PATH, and instead add symlinks to the prefixed binaries
# to our staging toolchain bindir.

python toolchain_metadata_setup () {
    if not isinstance(e, bb.event.ConfigParsed):
        return

    d = e.data

    l = d.createCopy()
    l.finalize()
    if os.path.exists(bb.data.expand('${EXTERNAL_TOOLCHAIN}/bin/gcc', l)):
        d.setVar('TOOLCHAIN_PATH_ADD', '')
}
addhandler toolchain_metadata_setup

python toolchain_setup () {
    if not isinstance(e, bb.event.BuildStarted):
        return

    d = e.data

    if not d.getVar('TOOLCHAIN_PATH_ADD', True):
        populate_toolchain_links(d)
}
addhandler toolchain_setup

def populate_toolchain_links(d):
    import errno
    from glob import glob

    d = d.createCopy()
    d.finalize()

    pattern = d.expand('${EXTERNAL_TOOLCHAIN}/bin/${TARGET_PREFIX}*')
    files = glob(pattern)
    if not files:
        bb.fatal("Unable to populate toolchain binary symlinks in %s" % pattern)

    bindir = d.getVar('STAGING_BINDIR_TOOLCHAIN', True)
    bb.mkdirhier(bindir)
    for f in files:
        base = os.path.basename(f)
        newpath = os.path.join(bindir, base)
        try:
            os.symlink(f, newpath)
        except OSError as exc:
            if exc.errno == errno.EEXIST:
                break
            bb.fatal("Unable to populate toolchain binary symlink for %s: %s" % (newpath, exc))

#require conf/distro/include/csl-versions.inc
