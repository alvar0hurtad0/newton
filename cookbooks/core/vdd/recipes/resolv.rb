file "/etc/resolvconf/resolv.conf.d/head" do
 content "#resolv.conf modified to add correctly the office DNS 
nameserver 192.168.1.111
"
 action:touch
end

execute "sudo resolvconf -u" do
action:run
end
