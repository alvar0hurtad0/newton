; This file contains most usual projects for all sites in production environments
; please copy default.base.make to base.make to add your own base modules

api = 2
core = 7.x

; +++++ Modules +++++

projects[drupal][type] = core

projects[views][subdir] = "contrib"
projects[views][version] = "3.x"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.x"

projects[context][subdir] = "contrib"
projects[context][version] = "3.x"

projects[token][subdir] = "contrib"
projects[token][version] = "1.x"

projects[pathauto][subdir] = "contrib"
projects[pathauto][version] = "1.x"

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.0-rc4"

projects[google_analytics][subdir] = "contrib"
projects[google_analytics][version] = "1.x"

projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg][version] = "2.x"

projects[htmlpurifier][subdir] = "contrib"

projects[imce_wysiwyg][subdir] = "contrib"
projects[imce_wysiwyg][version] = "1.x"

projects[imce][subdir] = "contrib"
projects[imce][version] = "1.x"

projects[libraries][subdir] = "contrib"
projects[libraries][version] = "2.x"

projects[features][subdir] = "contrib"
projects[features][version] = "2.x"

projects[transliteration][subdir] = "contrib"
projects[transliteration][version] = "3.x"

projects[ds][subdir] = "contrib"
projects[ds][version] = "2.x"

projects[strongarm][subdir] = "contrib"
projects[strongarm][version] = "2.x"

projects[smtp][subdir] = "contrib"
projects[smtp][version] = "1.x"

projects[views_bulk_operations][subdir] = "contrib"
projects[views_bulk_operations] = "3.x"

projects[admin_views][subdir] = "contrib"
projects[adminimal_theme][subdir] = "contrib"

projects[omega][subdir] = "contrib"

; +++++ libraries +++++

libraries[htmlpurifier][download][type] = "get"
libraries[htmlpurifier][download][url] = "http://htmlpurifier.org/releases/htmlpurifier-4.6.0.tar.gz"
libraries[htmlpurifier][destination] = "libraries"
libraries[htmlpurifier][directory_name] = "htmlpurifier"


