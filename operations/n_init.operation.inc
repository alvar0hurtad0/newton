<?php
/**
 * @file
 * Operation file n_init.operation.
 */

/**
 * Implements n_init command callback.
 */
function drush_newton_n_init() {

  drush_print(sprintf(COLOR_MSG_OK, '-------------------------------'));
  drush_print(sprintf(COLOR_MSG_OK, '- Create a new Drupal project -'));
  drush_print(sprintf(COLOR_MSG_OK, '-------------------------------'));

  $project_name = drush_prompt("What's the name of the project, please (remember customer-project)");
  $profile_name = str_replace('-', '_', $project_name);

  // Creating project structure.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Creating project structure ]'));
  drush_shell_exec_interactive('mkdir ' . $project_name);
  drush_shell_exec('mkdir ' . $project_name . '/makefiles');
  drush_shell_exec('mkdir ' . $project_name . '/tests && touch ' . $project_name . '/tests/README.txt');
  drush_shell_exec('mkdir ' . $project_name . '/patches && touch ' . $project_name . '/patches/README.txt');
  drush_shell_exec('mkdir ' . $project_name . '/rebuild_info');

  // Copying default makefiles.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Copying default makefile ]'));
  drush_shell_exec_interactive('cp ' . NEWTON_PATH . '/d7_bolierplate/makefiles/default.contrib.make ' . $project_name . '/makefiles/contrib.make');

  // Building project.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Building project ]'));
  drush_shell_exec_interactive('drush make ' . $project_name . '/makefiles/contrib.make ' . $project_name . '/httpdocs');

  // Copy gitignore.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Creating gitignore ]'));
  drush_print('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' . $project_name . '/.gitignore');
  drush_shell_exec_interactive('cp ' . NEWTON_PATH . '/d7_bolierplate/default.gitignore ' . $project_name . '/.gitignore');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' . $project_name . '/.gitignore');

  // Copy rebuild info for environment.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Copying rebuild info ]'));
  drush_shell_exec_interactive('cp ' . NEWTON_PATH . '/d7_bolierplate/rebuild_info/* ' . $project_name . '/rebuild_info/');

  // Creating instalation profile.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Creating instalation profile ]'));
  drush_shell_exec('mkdir -p ' . $project_name . '/httpdocs/profiles/' . $profile_name);
  drush_shell_exec_interactive('cp -r ' . NEWTON_PATH . '/d7_bolierplate/base.profile/* ' . $project_name . '/httpdocs/profiles/' . $profile_name);
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.info ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.info');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.profile ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.profile');
  drush_shell_exec('mv ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/base.profile.install ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.install');

  // Sed -i 's/[base.profile]/profile_name/' path_to_profile/profile_name.info.
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/' . $profile_name . '.install');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/display_modes_feature/display_modes_feature.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/field_bases_feature/field_bases_feature.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/image_styles_feature/image_styles_feature.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/path_features/path_features.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/roles_permissions_feature/roles_permissions_feature.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/sitewide_feature/sitewide_feature.info');
  drush_shell_exec('sed -i \'s/\[base.profile\]/' . $profile_name . '/gi\' ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/modules/features/wysiwyg_feature/wysiwyg_feature.info');

  // Install profile.
  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  drush_print(sprintf(COLOR_MSG_INFO, '[ Now enter some parameters for the development site, please ]'));
  $admin_pass = drush_prompt("The admin password (secret password if blank)", $random);
  $site_name = drush_prompt("The name of the website, please (Project Name will be used if blank)", $project_name);
  $site_email = drush_prompt("Sites email (my@example.com if blank)", 'my@example.com');
  $database_user = drush_prompt("Database user for THIS project (profile name if blank and should be no longer than 16; if longer, it will be trimmed to 16 characters)", $profile_name);
  $database_user = substr($database_user, 0, 16);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)", $random);
  $database_root = drush_prompt("Database super-user (root if blank)", 'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)", 'root');

  drush_shell_exec_interactive("cd $project_name/httpdocs && drush site-install $profile_name --site-name=$site_name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$profile_name");

  // Init repository.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Initializing repository ]'));
  drush_shell_exec_interactive("cd $project_name && git init");

  // Copy drush config and build developmet environment.
  drush_print(sprintf(COLOR_MSG_INFO, '[ Initializing drush alias ]'));
  drush_shell_exec_interactive('cp -r ' . NEWTON_PATH . '/d7_bolierplate/drush ' . $project_name);
  drush_shell_exec('sed -i \'s/\[project-name\]/' . $project_name . '/\' ' . $project_name . '/drush/aliases/default.aliases.drushrc.php');
  drush_shell_exec_interactive("cd $project_name/httpdocs && drush rebuild @default.local");

  $subtheme = drush_prompt("Do you want to create an Omega or a Bootstrap Subtheme?", 'omega / bootstrap');
  if ($subtheme == 'omega') {
    // Create omega subtheme and set as default.
    drush_print(sprintf(COLOR_MSG_INFO, '[ Creating and setting as default an Omega Subtheme ]'));
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush omega-subtheme $project_name --destination=profiles/$profile_name/themes/custom --enable --set-default");
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush en $profile_name --yes");
  }
  else {
    // Create bootstrap subtheme and set as default.
    drush_print(sprintf(COLOR_MSG_INFO, '[ Creating and setting as default a Bootstrap Subtheme ]'));
    drush_shell_exec_interactive("cp -r $project_name/httpdocs/sites/all/themes/contrib/bootstrap/bootstrap_subtheme $project_name/httpdocs/profiles/$profile_name/themes/custom/$profile_name");
    drush_shell_exec_interactive('cd ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/themes/custom/' . $profile_name . ' && mv bootstrap_subtheme.info.starterkit ' . $profile_name . '.info');
    drush_shell_exec('cd ' . $project_name . '/httpdocs/profiles/' . $profile_name . '/themes/custom/' . $profile_name . '&& sed -i \'s/Bootstrap Sub-theme/' . $profile_name . '/gi\' ' . $profile_name . '.info');
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush vset theme_default $profile_name");
    drush_shell_exec_interactive("cd $project_name/httpdocs && drush en $profile_name --yes");
  }
  drush_print(sprintf(COLOR_MSG_OK, '---------------------------'));
  drush_print(sprintf(COLOR_MSG_OK, '- Have a nice Drupal day! -'));
  drush_print(sprintf(COLOR_MSG_OK, '---------------------------'));
}
