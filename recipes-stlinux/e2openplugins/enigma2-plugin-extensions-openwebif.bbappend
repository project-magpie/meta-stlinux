python do_package_prepend () {
	boxtypes = [
		('spark', 'spark.jpg', 'spark.png'),
		('spark7162', 'spark7162.jpg', 'spark.png'),
	]
	for x in boxtypes:
		if x[0] == '${MACHINE}':
			target_box = x[1]
			target_remote = x[2]
			break
}

