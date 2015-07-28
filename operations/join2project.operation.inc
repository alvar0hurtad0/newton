<?php
/**
 * join2project command callback.
 */
function drush_newton_join2project($url=NULL) {
  if ($url == NULL){
    $git_repository = drush_prompt("What's the URL of remote git repository");
  }
  else{
    $git_repository= $url;
  }

  $pieces=explode('/',$git_repository);
  $size=sizeof($pieces);
  $last=$pieces[$size -1 ];
  $pieces_last=explode('.',$last);
  $project_name = $pieces_last[0];
  $profile_name = str_replace('-', '_', $project_name);

  //Must check if directory exits before clone the repository
  if (is_dir($project_name)) {
    exit('The directory is not empty. Aborting project creation...');
  } else {
    drush_print('I am cloning the repository into your machine, it can take a bit of time');
    drush_shell_exec_interactive('git clone ' . $git_repository . ' ' . $project_name);
  }

  // Check if project is based on makefiles
  if (is_dir("$project_name/makefiles")) {
    drush_print('Building project based on makefiles');
    drush_shell_exec_interactive('cd ' . $project_name . '/httpdocs && drush make ../makefiles/base.make --yes');
    drush_shell_exec_interactive('cd ' . $project_name . '/httpdocs && drush make --no-core ../makefiles/contrib.make --yes');
    drush_shell_exec_interactive('cd ' . $project_name . '/httpdocs && drush make --no-core ../makefiles/devel.make --yes');
  } else {
    drush_print('Building project without makefiles');
    $old_site = TRUE;
  }

  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  drush_print ('Now enter some parameters for the development site, please');
  $admin_pass = drush_prompt("The admin password (secret password if blank)", $random);
  $site_name = drush_prompt("The name of the website, please (Project Name will be used if blank)",$project_name);
  $site_email = drush_prompt("Sites email (my@example.com if blank)",'my@example.com');
  $database_user = drush_prompt("Database user for THIS project (profile name if blank and should be no longer than 16; if longer, it will be trimmed to 16 characters)",$profile_name);
  $database_user = substr($database_user,0,16);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');

  if ($old_site) {
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush site-install minimal --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$profile_name");
  } else {
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush site-install $profile_name --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$profile_name");
  }

  $synchronize = drush_prompt("Synchronize from pre?",'yes');
  if ($synchronize == 'yes') {
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush traepaca");
  }
  drush_shell_exec_interactive ("cd $project_name/httpdocs && drush rebuild @default.local");
}
