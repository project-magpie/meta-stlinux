require glibc.inc

SRCREV = "3e94272e370a13e6e1754fde578b2c44165ebcaa"
PV = "2.10"

DEPENDS += "gperf-native"
PR = "r2"
PR_append = "+git${SRCPV}"
FILESPATHPKG =. "glibc-git:"

GLIBC_BRANCH = "stlinux2.4-glibc-2.10.2-34"
GLIBC_PORTS_VER = "2.10.2"

SRC_URI = " \
	   git://git.stlinux.com/stm/glibc.git;protocol=git;branch=${GLIBC_BRANCH} \
           file://etc/ld.so.conf \
	   file://generate-supported.mk \
           file://fallocate64-backport.patch;patch=1 \
	   file://glibc-ports-${GLIBC_PORTS_VER}.tar.bz2 \
           file://execvpe.patch;patch=1 \
	   "
SRC_URI[md5sum] = "05c85905b43021a81318c3aa81718019"
SRC_URI[sha256sum] = "3691677a855fd5caf4c90ff922c132a7d2b966279a342733860b0c9084a155d9"
LIC_FILES_CHKSUM = "file://LICENSES;md5=07a394b26e0902b9ffdec03765209770 \
      file://COPYING;md5=393a5ca445f6965873eca0259a17f833 \
      file://posix/rxspencer/COPYRIGHT;md5=dc5485bb394a13b2332ec1c785f5d83a \
      file://COPYING.LIB;md5=bbb461211a33b134d42ed5ee802b37ff "

#SRC_URI_append_virtclass-nativesdk = " file://ld-search-order.patch"

S = "${WORKDIR}/git"
B = "${WORKDIR}/build-${TARGET_SYS}"

PACKAGES_DYNAMIC = "libc6*"
RPROVIDES_${PN}-dev = "libc6-dev virtual-libc-dev"
RDEPENDS_${PN}-dev = "linux-libc-headers-dev"
PROVIDES_${PN}-dbg = "glibc-dbg"

# the -isystem in bitbake.conf screws up glibc do_stage
BUILD_CPPFLAGS = "-I${STAGING_INCDIR_NATIVE}"
TARGET_CPPFLAGS = "-I${STAGING_DIR_TARGET}${layout_includedir}"

GLIBC_ADDONS ?= "ports,nptl,libidn"

GLIBC_BROKEN_LOCALES = " _ER _ET so_ET yn_ER sid_ET tr_TR mn_MN gez_ET gez_ER bn_BD te_IN wae_CH es_CR.ISO-8859-1"

FILESPATH = "${@base_set_filespath([ '${FILE_DIRNAME}/files' ], d)}"

#
# For now, we will skip building of a gcc package if it is a uclibc one
# and our build is not a uclibc one, and we skip a glibc one if our build
# is a uclibc build.
#
# See the note in gcc/gcc_3.4.0.oe
#

python __anonymous () {
    import bb, re
    uc_os = (re.match('.*uclibc$', bb.data.getVar('TARGET_OS', d, 1)) != None)
    if uc_os:
        raise bb.parse.SkipPackage("incompatible with target %s" %
                                   bb.data.getVar('TARGET_OS', d, 1))
}

# We need this for nativesdk
export libc_cv_slibdir = "${base_libdir}"
export libc_cv_forced_unwind = "yes"
export libc_cv_c_cleanup = "yes"
export ac_cv_header_cpuid_h = "yes"
export libc_cv_ctors_header = "yes"
export libc_cv_gcc_builtin_expect = "yes"

EXTRA_OECONF = "--enable-kernel=${OLDEST_KERNEL} \
                --without-cvs --disable-profile --disable-debug --without-gd \
                --enable-clocale=gnu \
                --enable-add-ons=${GLIBC_ADDONS},ports \
                --with-headers=${STAGING_INCDIR} \
                --without-selinux \
                ${GLIBC_EXTRA_OECONF}"

EXTRA_OECONF += "${@get_libc_fpu_setting(bb, d)}"

do_unpack_append() {
	bb.build.exec_func('do_move_ports', d)
}

do_move_ports() {
        if test -d ${WORKDIR}/glibc-ports-${GLIBC_PORTS_VER} ; then
	    rm -rf ${S}/ports
            mv ${WORKDIR}/glibc-ports-${GLIBC_PORTS_VER} ${S}/ports
	fi
}

do_configure () {

	echo ${WORKDIR}
# /var/db was not included to FHS
	sed -i s:/var/db/nscd:/var/run/nscd: ${S}/nscd/nscd.h
# override this function to avoid the autoconf/automake/aclocal/autoheader
# calls for now
# don't pass CPPFLAGS into configure, since it upsets the kernel-headers
# version check and doesn't really help with anything
        if [ -z "`which rpcgen`" ]; then
                echo "rpcgen not found.  Install glibc-devel."
                exit 1
        fi
        (cd ${S} && gnu-configize) || die "failure in running gnu-configize"
        find ${S} -name "configure" | xargs touch
        CPPFLAGS="" oe_runconf
}

rpcsvc = "bootparam_prot.x nlm_prot.x rstat.x \
	  yppasswd.x klm_prot.x rex.x sm_inter.x mount.x \
	  rusers.x spray.x nfs_prot.x rquota.x key_prot.x"

do_compile () {
	# -Wl,-rpath-link <staging>/lib in LDFLAGS can cause breakage if another glibc is in staging
	unset LDFLAGS
	base_do_compile
	(
		cd ${S}/sunrpc/rpcsvc
		for r in ${rpcsvc}; do
			h=`echo $r|sed -e's,\.x$,.h,'`
			rpcgen -h $r -o $h || bbwarn "unable to generate header for $r"
		done
	)
	echo "Adjust ldd script"
	[ -z "${RTLDLIST}" ] && return
	sed -i ${B}/elf/ldd -e 's#^\(RTLDLIST=\)"\(.*\)"$#\1\2#'
	sed -i ${B}/elf/ldd -e 's#^\(RTLDLIST=\)\(.*\)$#\1"${RTLDLIST} \2"#'

}

require glibc-package.inc

BBCLASSEXTEND = "nativesdk"
