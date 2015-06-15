<?php
/**
 * n_init command callback.
 */
function drush_newton_n_init() {
  $NEWTON_PATH = '~/.drush/newton';
  global $green;

  $project_name = drush_prompt("What's the name of the project, please (remember customer-project)");
  $profile_name = ereg_replace('-', '_', $project_name);

  // Creating project structure
  drush_print (sprintf($green, dt('Creating project structure ')));
  drush_shell_exec_interactive('mkdir '.$project_name);
  drush_shell_exec('mkdir '.$project_name.'/makefiles');
  drush_shell_exec('mkdir '.$project_name.'/tests');
  drush_shell_exec('mkdir '.$project_name.'/patches');

  // Copying default makefiles
  drush_print (sprintf($green, dt('Copying default makefiles '.$previous_branch)));
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/makefiles/default.base.make ' . $project_name . '/makefiles/base.make');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/makefiles/default.devel.make ' . $project_name . '/makefiles/devel.make');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/makefiles/default.contrib.make ' . $project_name . '/makefiles/contrib.make');

  // Building project
  drush_print (sprintf($green, dt('Building project ')));
  drush_shell_exec_interactive ('drush make ' . $project_name . '/makefiles/base.make ' . $project_name . '/httpdocs');
  drush_shell_exec_interactive ('cd ' . $project_name . '/httpdocs && drush make --no-core ../makefiles/devel.make --yes');

  // Copy gitignore
  drush_print (sprintf($green, dt('Creating gitignore ')));
  drush_print ('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/.gitignore');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/default.gitignore ' . $project_name . '/.gitignore');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/.gitignore');

  // Creating instalation profile
  drush_print (sprintf($green, dt('Creating instalation profile ')));
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles');
  drush_shell_exec_interactive('cp -r ' . $NEWTON_PATH . '/base.profile ' . $project_name . '/httpdocs/profiles');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/base.profile ' . $project_name . '/httpdocs/profiles/' . $profile_name);
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.info ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.info');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.profile ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.profile');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.install ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.install');

  // sed -i 's/[base.profile]/profile_name/' path_to_profile/profile_name.info
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.install');

  // create profile structure
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles/' . $profile_name . '/modules');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles/' . $profile_name . '/modules/custom');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles/' . $profile_name . '/modules/features');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles/' . $profile_name . '/themes');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles/' . $profile_name . '/themes/custom');

  // install profile
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

  drush_shell_exec_interactive("cd $project_name/httpdocs && drush site-install $profile_name --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$profile_name");
}