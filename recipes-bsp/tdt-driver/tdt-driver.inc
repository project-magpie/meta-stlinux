HOMEPAGE = "http://gitorious.org/open-duckbox-project-sh4"
SECTION = "kernel/modules"
RDEPENDS_${PN} = "ustslave"

LICENSE = " GPLv2"
LIC_FILES_CHKSUM = "file://${WORKDIR}/COPYING;md5=751419260aa954499f7abaabaa882bbe"

inherit module

PACKAGES = "${PN} ${PN}-dev"
PACKAGES_DYNAMIC += "kernel-module-*"

SRCREV = "350ce95d04b701b61e91e6aa60d1120a1958ca57"


BINARY_PTI_NP_PATH ?= "/data/pti_np"

# using seifes tdt drivers because this has less overhead
SRC_URI = " \
	git://gitorious.org/neutrino-mp/tdt-driver.git \
        file://0001-player2_191-silence-kmsg-spam.patch \
        file://0002-e2proc-silence-kmsg-spam.patch \
        file://0003-pti-silence-kmsg-spam.patch \
        file://0004-stmfb-silence-kmsg-spam.patch \
        file://0005-frontends-spark_dvbapi5-silence-kmsg-spam.patch \
        file://0006-frontends-spark7162-silence-kmsg-spam.patch \
        file://0001-import-cec-from-pinky-s-git.patch \
        file://0002-aotom-fix-include-file.patch \
        file://0003-aotom-add-VFDGETVERSION-ioctl-to-find-FP-type.patch \
        file://0004-aotom-improve-scrolling-text-code.patch \
        file://0005-aotom-speed-up-softi2c-lowering-CPU-load-of-aotom-dr.patch \
        file://0006-aotom-add-additional-chars-for-VFD-fix-missing-chars.patch \
        file://0007-aotom-register-reboot_notifier-implement-rtc-driver.patch \
        file://aotom_udev.rules \
        file://COPYING \
" 

INC_PR = "r27"

PV = "0.2+git${SRCPV}"

FILES_${PN} = "/etc/udev/rules.d "
FILES = ""

S = "${WORKDIR}/git"

do_configure_prepend () {
	if [ -L include/stmfb ]; then
		rm include/stmfb
	fi
	if [ -L include/player2 ]; then
		rm include/player2
	fi
	if [ -L include/multicom ]; then
		rm include/multicom
	fi
	if [ -L player2 ]; then
                rm player2
        fi
	if [ -L stgfb/stmfb ]; then
                rm stgfb/stmfb
        fi
	if [ -L multicom ]; then
                rm multicom 
        fi
	ln -s ${S}/include/stmfb-3.1_stm24_0102 ${S}/include/stmfb
	ln -s ${S}/include/player2_179 ${S}/include/player2
	ln -s ${S}/multicom-3.2.4/include ${S}/include/multicom
	ln -s ${S}/player2_191 ${S}/player2
	ln -s ${S}/multicom-3.2.4 ${S}/multicom
	ln -s ${S}/stgfb/stmfb-3.1_stm24_0102 ${S}/stgfb/stmfb
	rm -f .config 
        printf "export CONFIG_PLAYER_191=y\nexport CONFIG_MULTICOM324=y\n" > .config
	# disable wireless build
	# sed -i 's/^\(obj-y.*+= wireless\)/# \1/' Makefile
	# disable led and button - it's not for spark
	sed -i 's@^\(obj-y.*+= \(led\|button\)/\)@# \1@' Makefile
}



do_compile() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
                   KERNEL_SRC=${STAGING_KERNEL_DIR}    \
                   KERNEL_VERSION=${KERNEL_VERSION}    \
		   -C ${STAGING_KERNEL_DIR}   \
	           ${@d.getVar('MACHINE',1).upper()}=1 \
                   M=${S} V=1 \
                   ARCH=sh \
		   PLAYER191=player191 \
        	   DRIVER_TOPDIR="${S}" \
	           KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
	           CONFIG_MODULES_PATH="${D}" \
		   CONFIG_PLAYER_191=y \
		   CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
                   modules 
}

do_install() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake KERNEL_PATH=${STAGING_KERNEL_DIR}   \
                   KERNEL_SRC=${STAGING_KERNEL_DIR}    \
                   KERNEL_VERSION=${KERNEL_VERSION}    \
		   -C ${STAGING_KERNEL_DIR}   \
	           ${@d.getVar('MACHINE',1).upper()}=1 \
                   M=${S} V=1 \
                   ARCH=sh \
		   PLAYER191=player191 \
        	   DRIVER_TOPDIR="${S}" \
	           KERNEL_LOCATION="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_BUILD="${STAGING_KERNEL_DIR}" \
	           CONFIG_KERNEL_PATH="${STAGING_KERNEL_DIR}" \
	           CONFIG_MODULES_PATH="${D}" \
		   CONFIG_PLAYER_191=y \
		   CCFLAGSY="-I${STAGING_DIR_HOST}/usr/include" \
		   INSTALL_MOD_PATH=${D} modules_install

        # install header files
	install -d ${D}/${includedir}/linux/dvb
        
	install -m 644 bpamem/bpamem.h ${D}/${includedir}
 	install -m 644 frontcontroller/aotom/aotom_main.h ${D}/${includedir}
 	install -m 644 player2/linux/include/linux/dvb/stm_ioctls.h ${D}/${includedir}/linux/dvb
 	install -m 644 stgfb/stmfb/linux/drivers/video/stmfb.h ${D}/${includedir}/linux

	#install modutils config
	install -d ${D}/${sysconfdir}/modules-load.d
	install -d ${D}/${sysconfdir}/modprobe.d
	install -d ${D}/${sysconfdir}/udev/rules.d/
	
	cp ${WORKDIR}/aotom_udev.rules ${D}/${sysconfdir}/udev/rules.d/32-aotom.rules
 
        # if a custom pti.ko is present, overwrite the tdt one
        if [ -e ${BINARY_PTI_NP_PATH}/pti_${STM_PATCH_STR}.ko ]; then
                echo "Found custom pti.." 
                install -m 644 ${BINARY_PTI_NP_PATH}/pti_${STM_PATCH_STR}.ko ${D}/lib/modules/${KERNEL_VERSION}/extra/pti/
        fi



}

do_install_append_spark7162() {
	find ${D} -name stmcore-display-sti7106.ko | xargs -r rm # we don't have a 7106 chip
}

pkg_postinst_modules () {
if [ -z "$D" ]; then
	depmod -a ${KERNEL_VERSION}
	update-modules || true
fi
}

pkg_postrm_modules () {
update-modules || true
}

autoload_postinst_fragment() {
if [ x"$D" = "x" ]; then
	modprobe %s || true
fi
}


pkg_postinst_kernel-modules-tdt () {
     #!/bin/sh -e
     if [ x"$D" = "x" ]; then
          # Actions to carry out on the device go here
	  depmod -a ${KERNEL_VERSION}
          update-modules || true
     else
          exit 1
     fi
}


python populate_packages_prepend () {
	def extract_modinfo(file):
		import tempfile, re
		tempfile.tempdir = d.getVar("WORKDIR", True)
		tf = tempfile.mkstemp()
		tmpfile = tf[1]
		cmd = "PATH=\"%s\" %sobjcopy -j .modinfo -O binary %s %s" % (d.getVar("PATH", True), d.getVar("HOST_PREFIX", True) or "", file, tmpfile)
		os.system(cmd)
		f = open(tmpfile)
		l = f.read().split("\000")
		f.close()
		os.close(tf[0])
		os.unlink(tmpfile)
		exp = re.compile("([^=]+)=(.*)")
		vals = {}
		for i in l:
			m = exp.match(i)
			if not m:
				continue
			vals[m.group(1)] = m.group(2)
		return vals
	
	def parse_depmod():
		import re

		dvar = d.getVar('PKGD', True)
		if not dvar:
			bb.error("PKGD not defined")
			return

		kernelver = d.getVar('KERNEL_VERSION', True)
		kernelver_stripped = kernelver
		m = re.match('^(.*-hh.*)[\.\+].*$', kernelver)
		if m:
			kernelver_stripped = m.group(1)
		path = d.getVar("PATH", True)
		host_prefix = d.getVar("HOST_PREFIX", True) or ""

		cmd = "PATH=\"%s\" %sdepmod -n -a -r -b %s -F %s/boot/System.map-%s %s" % (path, host_prefix, dvar, dvar, kernelver, kernelver_stripped)
		f = os.popen(cmd, 'r')

		deps = {}
		pattern0 = "^(.*\.k?o):..*$"
		pattern1 = "^(.*\.k?o):\s*(.*\.k?o)\s*$"
		pattern2 = "^(.*\.k?o):\s*(.*\.k?o)\s*\\\$"
		pattern3 = "^\t(.*\.k?o)\s*\\\$"
		pattern4 = "^\t(.*\.k?o)\s*$"

		line = f.readline()
		while line:
			if not re.match(pattern0, line):
				line = f.readline()
				continue
			m1 = re.match(pattern1, line)
			if m1:
				deps[m1.group(1)] = m1.group(2).split()
			else:
				m2 = re.match(pattern2, line)
				if m2:
					deps[m2.group(1)] = m2.group(2).split()
					line = f.readline()
					m3 = re.match(pattern3, line)
					while m3:
						deps[m2.group(1)].extend(m3.group(1).split())
						line = f.readline()
						m3 = re.match(pattern3, line)
					m4 = re.match(pattern4, line)
					deps[m2.group(1)].extend(m4.group(1).split())
			line = f.readline()
		f.close()
		return deps
	
	def get_dependencies(file, pattern, format):
                # file no longer includes PKGD
		file = file.replace(d.getVar('PKGD', True) or '', '', 1)
                # instead is prefixed with /lib/modules/${KERNEL_VERSION}
                file = file.replace("/lib/modules/%s/" % d.getVar('KERNEL_VERSION', True) or '', '', 1)

		if module_deps.has_key(file):
			import re
			dependencies = []
			for i in module_deps[file]:
				m = re.match(pattern, os.path.basename(i))
				if not m:
					continue
				on = legitimize_package_name(m.group(1))
				dependency_pkg = format % on
				dependencies.append(dependency_pkg)
			return dependencies
		return []

	def frob_metadata(file, pkg, pattern, format, basename):
		import re
		vals = extract_modinfo(file)

		dvar = d.getVar('PKGD', True)

		# If autoloading is requested, output /etc/modules-load.d/<name>.conf and append
		# appropriate modprobe commands to the postinst
		autoload = d.getVar('module_autoload_%s' % basename, True)
		if autoload:
			name = '%s/etc/modules-load.d/%s.conf' % (dvar, basename)
			f = open(name, 'w')
			for m in autoload.split():
				f.write('%s\n' % m)
			f.close()
			postinst = d.getVar('pkg_postinst_%s' % pkg, True)
			if not postinst:
				bb.fatal("pkg_postinst_%s not defined" % pkg)
			postinst += d.getVar('autoload_postinst_fragment', True) % autoload
			d.setVar('pkg_postinst_%s' % pkg, postinst)

		# Write out any modconf fragment
		modconf = d.getVar('module_conf_%s' % basename, True)
		if modconf:
			name = '%s/etc/modprobe.d/%s.conf' % (dvar, basename)
			f = open(name, 'w')
			f.write("%s\n" % modconf)
			f.close()

		files = d.getVar('FILES_%s' % pkg, True)
		files = "%s /etc/modules-load.d/%s.conf /etc/modprobe.d/%s.conf" % (files, basename, basename)
		d.setVar('FILES_%s' % pkg, files)

		if vals.has_key("description"):
			old_desc = d.getVar('DESCRIPTION_' + pkg, True) or ""
			d.setVar('DESCRIPTION_' + pkg, old_desc + "; " + vals["description"])

		rdepends_str = d.getVar('RDEPENDS_' + pkg, True)
		if rdepends_str:
			rdepends = rdepends_str.split()
		else:
			rdepends = []
		rdepends.extend(get_dependencies(file, pattern, format))
		d.setVar('RDEPENDS_' + pkg, ' '.join(rdepends))

	module_deps = parse_depmod()
	module_regex = '^(.*)\.k?o$'
	module_pattern = 'kernel-module-%s'
        postinst = d.getVar('pkg_postinst_modules', True)
        postrm = d.getVar('pkg_postrm_modules', True)

	do_split_packages(d, root='/lib/modules', file_regex=module_regex, output_pattern=module_pattern, description='%s kernel module', postinst=postinst, postrm=postrm, recursive=True, hook=frob_metadata, extra_depends='update-modules kernel-%s' % d.getVar("KERNEL_VERSION", True))

	# If modules-load.d and modprobe.d are empty at this point, remove them to
	# avoid warnings. removedirs only raises an OSError if an empty
	# directory cannot be removed.
	dvar = d.getVar('PKGD', True)
	for dir in ["%s/etc/modprobe.d" % (dvar), "%s/etc/modules-load.d" % (dvar), "%s/etc" % (dvar)]:
		if len(os.listdir(dir)) == 0:
			os.rmdir(dir)

	import re
	metapkg = "kernel-modules-tdt"
	d.setVar('ALLOW_EMPTY_' + metapkg, "1")
	d.setVar('FILES_' + metapkg, "")
	blacklist = [ 'tdt-driver-dev', 'kernel-image', 'kernel-base', 'kernel-vmlinux', 'perf', 'perf-dbg' ]
	for l in module_deps.values():
		for i in l:
			pkg = module_pattern % legitimize_package_name(re.match(module_regex, os.path.basename(i)).group(1))
			blacklist.append(pkg)
	metapkg_rdepends = []
	packages = d.getVar('PACKAGES', True).split()
	for pkg in packages[1:]:
		if not pkg in blacklist and not pkg in metapkg_rdepends:
			metapkg_rdepends.append(pkg)
	d.setVar('RDEPENDS_' + metapkg, ' '.join(metapkg_rdepends))
	d.setVar('DESCRIPTION_' + metapkg, 'Kernel modules meta package')
	packages.append(metapkg)
	d.setVar('PACKAGES', ' '.join(packages))
}


do_populate_packages_append () {
        echo "-------------------------------------------------------------------------------------------------------------"
        echo "-------------------------------------------------------------------------------------------------------------"
	echo ${PACKAGES}

}

FILES_${PN}-dev += "${includedir}"

