mkdir /Volumes/tmp
ssh-add
vagrant up
/usr/local/bin/sshfs vagrant@192.168.44.44:/var/www/ /Volumes/tmp -ovolname=vagrant,reconnect -ocache=no -onolocalcaches
