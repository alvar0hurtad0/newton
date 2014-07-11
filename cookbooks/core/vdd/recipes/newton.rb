directory "/home/vagrant/.drush/newton" do
  owner "vagrant"
  group "vagrant"
  mode "0755"
  action :create
end

directory "/home/vagrant/.drush/newton" do
  owner "vagrant"
  group "vagrant"
  mode "0755"
  action :create
end

git "/home/vagrant/.drush/newton" do
  repository "https://github.com/alvar0hurtad0/newton.git"
  revision "master"
  action :sync
end
