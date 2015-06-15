; This file contains most usual projects for all sites in production environments
; please copy default.base.make to base.make to add your own base modules

api = 2
core = 7.x

projects[drupal][type] = core

projects[views][subdir] = "contrib"
projects[ctools][subdir] = "contrib"
projects[token][subdir] = "contrib"
projects[pathauto][subdir] = "contrib"
projects[admin_menu][subdir] = "contrib"
projects[google_analytics][subdir] = "contrib"
projects[wysiwyg][subdir] = "contrib"
projects[features][subdir] = "contrib"
projects[transliteration][subdir] = "contrib"
projects[ds][subdir] = "contrib"
projects[strongarm][subdir] = "contrib"
projects[smtp][subdir] = "contrib"
projects[admin_views][subdir] = "contrib"
projects[adminimal_theme][subdir] = "contrib"
projects[omega][subdir] = "contrib"
