Package "rubygems"

Execute "gem install sass" do
    not_if "which sass"
end
Execute "gem install rb-inotify"
