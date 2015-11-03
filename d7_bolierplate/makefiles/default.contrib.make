; This file contains specific contrib projects and patches for your current site
; for more information about insert projects visit: https://www.drupal.org/node/1432374

api = 2
core = 7.x

; +++++ Modules +++++

projects[drupal][type] = core

defaults[projects][subdir] = contrib

projects[] = views
projects[] = ctools
projects[] = context
projects[] = token
projects[] = pathauto
projects[] = admin_menu
projects[] = google_analytics
projects[] = wysiwyg
projects[] = htmlpurifier
projects[] = imce_wysiwyg
projects[] = imce
projects[] = libraries
projects[] = features
projects[] = transliteration
projects[] = ds
projects[] = strongarm
projects[] = smtp
projects[] = views_bulk_operations
projects[] = admin_views

projects[] = devel
projects[] = fpa
projects[] = stage_file_proxy
projects[] = coffee
projects[] = diff
projects[] = features_diff
projects[] = reroute_email
projects[] = module_filter

; +++++ themes +++++

projects[] = adminimal_theme
projects[] = omega

; +++++ libraries +++++

libraries[htmlpurifier][download] = get
libraries[htmlpurifier][download][url] = http://htmlpurifier.org/releases/htmlpurifier-4.7.0.zip
libraries[htmlpurifier][destination] = libraries
libraries[htmlpurifier][directory_name] = htmlpurifier

libraries[ckeditor][download] = get
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.5.3/ckeditor_4.5.3_standard.zip
libraries[ckeditor][directory_name] = ckeditor
libraries[ckeditor] = library

