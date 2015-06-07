<?php
/**
 * join2project command callback.
 */
function drush_newton_join2project($url=NULL) {
  if ($url==NULL){
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

  $project_name = drush_prompt("What's the project name", $project_name);
  $profile_name = ereg_replace('-', '_', $project_name);
  $profile_name = drush_prompt("What's the project name", $profile_name);

  drush_print ('I am cloning the repository into your machine, it can take a bit of time');
  drush_shell_exec_interactive('git clone '.$git_repository.' '.$project_name);

  // Building project
  drush_print (sprintf($green, dt('Building project ')));
  drush_shell_exec_interactive ('drush make ' . $project_name . '/makefiles/base.make ' . $project_name . '/httpdocs');
  drush_shell_exec_interactive ('cd ' . $project_name . '/httpdocs && drush make --no-core ../makefiles/contrib.make --yes');
  drush_shell_exec_interactive ('cd ' . $project_name . '/httpdocs && drush make --no-core ../makefiles/devel.make --yes');


  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  drush_print ('Now enter some parameters for the development site, please\n\r');
  $admin_pass = $random;
  $site_name = ('unnamed');
  $site_email = 'my@example.com';
  $database_user = substr (drush_prompt("Database user for THIS project (directory name if blank)",$project_name), 0, 16);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');

  drush_shell_exec_interactive("cd ".$project_name."/httpdocs && drush site-install $profile_name --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$project_name");
}