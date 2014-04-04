git "/home/vagrant/.drush" do
  repository "https://github.com/alvar0hurtad0/newton.git"
  revision "master"
  action :sync
end