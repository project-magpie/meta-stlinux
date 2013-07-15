# thoug not actually a bootlogo task, set the correct videomode before showing the bootlogo
cat /etc/videomode > /proc/stb/video/videomode

if [ -e /etc/dropbear/dropbear_rsa_host_key ] ; then
	/usr/bin/showiframe -p /usr/share/bootlogo.mvi &
else 
	/usr/bin/showiframe -p /usr/share/bootlogo_wait.mvi &
fi

