; This file contains specific contrib projects and patches for your current site
; for more information about insert projects visit: https://www.drupal.org/node/1432374

api = 2
core = 7.x

; +++++ Modules +++++

projects[drupal][type] = core

defaults[projects][subdir] = contrib

projects[views][type] = module
projects[ctools][type] = module
projects[context][type] = module
projects[token][type] = module
projects[pathauto][type] = module
projects[admin_menu][type] = module
projects[google_analytics][type] = module
projects[wysiwyg][type] = module
projects[htmlpurifier][type] = module
projects[imce_wysiwyg][type] = module
projects[imce][type] = module
projects[libraries][type] = module
projects[features][type] = module
projects[transliteration][type] = module
projects[ds][type] = module
projects[strongarm][type] = module
projects[smtp][type] = module
projects[views_bulk_operations][type] = module
projects[admin_views][type] = module

projects[devel][type] = module
projects[fpa][type] = module
projects[stage_file_proxy][type] = module
projects[coffee][type] = module
projects[diff][type] = module
projects[features_diff][type] = module
projects[reroute_email][type] = module
projects[module_filter][type] = module

; +++++ themes +++++

projects[adminimal_theme][type] = theme
projects[omega][type] = theme
projects[bootstrap][type] = theme

; +++++ libraries +++++

libraries[htmlpurifier][download][type] = get
libraries[htmlpurifier][download][url] = http://htmlpurifier.org/releases/htmlpurifier-4.7.0.zip
libraries[htmlpurifier][destination] = libraries
libraries[htmlpurifier][directory_name] = htmlpurifier

libraries[ckeditor][download][type] = get
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.5.3/ckeditor_4.5.3_standard.zip
libraries[ckeditor][directory_name] = ckeditor
libraries[ckeditor][type] = library
