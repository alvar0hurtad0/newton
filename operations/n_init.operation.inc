<?php
/**
 * n_init command callback.
 */
function drush_newton_n_init() {
  $NEWTON_PATH = '~/.drush/newton';

  $project_name = drush_prompt("What's the name of the project, please (remember customer-project)");
  $profile_name = str_replace('-', '_', $project_name);

  // Creating project structure
  drush_print ('Creating project structure');
  drush_print ('--------------------------');
  drush_shell_exec_interactive('mkdir '.$project_name);
  drush_shell_exec('mkdir '.$project_name.'/makefiles');
  drush_shell_exec('mkdir '.$project_name.'/tests && touch '.$project_name.'/tests/README.txt');
  drush_shell_exec('mkdir '.$project_name.'/patches && touch '.$project_name.'/patches/README.txt');
  drush_shell_exec('mkdir '.$project_name.'/rebuild_info');

  // Copying default makefiles
  drush_print ('Copying default makefiles');
  drush_print ('-------------------------');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/makefiles/default.base.make ' . $project_name . '/makefiles/base.make');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/makefiles/default.devel.make ' . $project_name . '/makefiles/devel.make');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/makefiles/default.contrib.make ' . $project_name . '/makefiles/contrib.make');

  // Building project
  drush_print ('Building project');
  drush_print ('----------------');
  drush_shell_exec_interactive ('drush make ' . $project_name . '/makefiles/base.make ' . $project_name . '/httpdocs');
  drush_shell_exec_interactive ('cd ' . $project_name . '/httpdocs && drush make --no-core ../makefiles/devel.make --yes');

  // Copy gitignore
  drush_print ('Creating gitignore');
  drush_print ('------------------');
  drush_print ('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/.gitignore');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/default.gitignore ' . $project_name . '/.gitignore');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/.gitignore');

  // Copy rebuild info for environment
  drush_print ('Copying rebuild info');
  drush_print ('--------------------');
  drush_shell_exec_interactive('cp ' . $NEWTON_PATH . '/rebuild_info/* ' . $project_name . '/rebuild_info/');

  // Creating instalation profile
  drush_print ('Creating instalation profile');
  drush_print ('----------------------------');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/profiles');
  drush_shell_exec_interactive('cp -r ' . $NEWTON_PATH . '/base.profile ' . $project_name . '/httpdocs/profiles');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/base.profile ' . $project_name . '/httpdocs/profiles/' . $profile_name);
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.info ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.info');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.profile ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.profile');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.install ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.install');

  // sed -i 's/[base.profile]/profile_name/' path_to_profile/profile_name.info
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' .$project_name. '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.install');

  // install profile
  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  drush_print ('Now enter some parameters for the development site, please');
  drush_print ('----------------------------------------------------------');
  $admin_pass = drush_prompt("The admin password (secret password if blank)", $random);
  $site_name = drush_prompt("The name of the website, please (Project Name will be used if blank)",$project_name);
  $site_email = drush_prompt("Sites email (my@example.com if blank)",'my@example.com');
  $database_user = drush_prompt("Database user for THIS project (profile name if blank and should be no longer than 16; if longer, it will be trimmed to 16 characters)",$profile_name);
  $database_user = substr($database_user,0,16);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');

  drush_shell_exec_interactive("cd $project_name/httpdocs && drush site-install $profile_name --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$profile_name");

  // Init repository
  drush_print ('Initializing repository');
  drush_print ('-----------------------');
  drush_shell_exec_interactive ("cd $project_name && git init");

  // copy drush config and build developmet environment
  drush_print ('Initializing drush alias');
  drush_print ('------------------------');
  drush_shell_exec_interactive('cp -r ' . $NEWTON_PATH . '/drush ' . $project_name);
  drush_shell_exec('sed -i \'s/\[project-name\]/' . $project_name . '/\' ' .$project_name. '/drush/aliases/default.aliases.drushrc.php');
  drush_shell_exec_interactive ("cd $project_name/httpdocs && drush rebuild @default.local");

  $subtheme = drush_prompt("Do you want to create an Omega or a Bootstrap Subtheme?",'omega / bootstrap');
  if ($subtheme == 'omega') {
    // Create omega subtheme and set as default
    drush_print ('Creating and setting as default an Omega Subtheme');
    drush_print ('-------------------------------------------------');
    drush_shell_exec_interactive ("cd $project_name/httpdocs && drush omega-subtheme $project_name --destination=profiles/$profile_name/themes/custom --enable --set-default");
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush en $profile_name --yes");
  } else {
    // Create bootstrap subtheme and set as default
    drush_print ('Creating and setting as default a Bootstrap Subtheme');
    drush_print ('----------------------------------------------------');
    drush_shell_exec_interactive ("cp -r $project_name/httpdocs/sites/all/themes/contrib/bootstrap/bootstrap_subtheme $project_name/httpdocs/profiles/$profile_name/themes/custom/$profile_name");
    drush_shell_exec_interactive ('cd ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/themes/custom/' . $profile_name. ' && mv bootstrap_subtheme.info.starterkit ' . $profile_name .'.info');
    drush_shell_exec('cd ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/themes/custom/' . $profile_name . '&& sed -i \'s/Bootstrap Sub-theme/' . $profile_name. '/gi\' ' . $profile_name .'.info');
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush vset theme_default $profile_name");
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush en $profile_name --yes");
  }
  drush_print ('---------------------------');
  drush_print ('- Have a nice Drupal day! -');
  drush_print ('---------------------------');
}
