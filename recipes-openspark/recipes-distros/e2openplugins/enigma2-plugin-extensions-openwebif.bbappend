MODULE = "OpenWebif"
PRINC = "30"
DEPENDS += "enigma2 python-pyopenssl"
RDEPENDS_${PN} += " python-pyopenssl"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI = "git://github.com/oe-alliance/e2openplugin-${MODULE}.git;protocol=git"

S="${WORKDIR}/git"

python do_package_prepend () {
	boxtypes = [
		('spark', 'unknown.jpg', 'dm_normal.png'),
		('spark7162', 'unknown.jpg', 'dm_normal.png'),
	]
	import os
	top = '${D}${PLUGINPATH}/public/images/'
	for x in boxtypes:
		if x[0] == '${MACHINE}':
			target_box = x[1]
			target_remote = x[2]
			break
	for root, dirs, files in os.walk(top + 'boxes', topdown=False):
		for name in files:
			if target_box != name and name != 'unknown.jpg':
				if target_box == 'ini-3000.jpg':
					if not (name == 'ini-1000.jpg' or name == 'ini-3000.jpg' or name == 'ini-5000.jpg' or name == 'ini-5000sv.jpg' or name == 'ini-7000.jpg'):
						os.remove(os.path.join(root, name))
				else:
					os.remove(os.path.join(root, name))
	for root, dirs, files in os.walk(top + 'remotes', topdown=False):
		for name in files:
			if target_remote != name and name != 'ow_remote.png':
				if target_remote == 'ini-3000.png':
					if not (name == 'ini-1000.png' or name == 'ini-3000.png' or name == 'ini-5000.png' or name == 'miraclebox.png' or name == 'ini-7000.png'):
						os.remove(os.path.join(root, name))
				else:
					os.remove(os.path.join(root, name))
}

python populate_packages_prepend() {
	enigma2_plugindir = bb.data.expand('${libdir}/enigma2/python/Plugins', d)
	do_split_packages(d, enigma2_plugindir, '^(\w+/\w+)/[a-zA-Z0-9_]+.*$', 'enigma2-plugin-%s', '%s', recursive=True, match_path=True, prepend=True, extra_depends="enigma2")
	do_split_packages(d, enigma2_plugindir, '^(\w+/\w+)/.*\.py$', 'enigma2-plugin-%s-src', '%s (source files)', recursive=True, match_path=True, prepend=True)
	do_split_packages(d, enigma2_plugindir, '^(\w+/\w+)/.*\.la$', 'enigma2-plugin-%s-dev', '%s (development)', recursive=True, match_path=True, prepend=True)
	do_split_packages(d, enigma2_plugindir, '^(\w+/\w+)/.*\.a$', 'enigma2-plugin-%s-staticdev', '%s (static development)', recursive=True, match_path=True, prepend=True)
	do_split_packages(d, enigma2_plugindir, '^(\w+/\w+)/(.*/)?\.debug/.*$', 'enigma2-plugin-%s-dbg', '%s (debug)', recursive=True, match_path=True, prepend=True)
	do_split_packages(d, enigma2_plugindir, '^(\w+/\w+)/.*\/.*\.po$', 'enigma2-plugin-%s-po', '%s (translations)', recursive=True, match_path=True, prepend=True)
}
