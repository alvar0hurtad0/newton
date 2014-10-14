Package "rubygems"

Execute "gem install bundler" do
    not_if "which bundler"
end
Execute "gem install rb-inotify"
