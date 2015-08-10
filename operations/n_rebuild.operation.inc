<?php
/**
 * n-rebuild command callback.
 */
function drush_newton_n_rebuild () {
  $make_base = drush_get_option('make-base');
  $make_contrib = drush_get_option('make-contrib');
  $make_devel = drush_get_option('make-devel');
  $make_all = drush_get_option('make-all');
  $reinstall = drush_get_option('reinstall');
  $yes_to_all = drush_get_option('yes');


  $path_to_drupal = drush_get_context('DRUSH_DRUPAL_CORE');

  if ($yes_to_all) {
    $extra_options = '--yes';
  }
  if ($make_base || $make_all) {
    drush_print ('Downloading core and base modules');
    drush_shell_cd_and_exec ($path_to_drupal, 'drush make ../makefiles/base.make '. $extra_options);
    $output = drush_shell_exec_output ();
    foreach ($output as $line) {
      drush_print ($line);
    }
  }
  if ($make_contrib || $make_all) {
    drush_print ('Downloading contrib modules, themes, libraries and patches');
    drush_shell_cd_and_exec ($path_to_drupal, 'drush make ../makefiles/contrib.make --no-core '. $extra_options);

    $output = drush_shell_exec_output ();
    foreach ($output as $line) {
      drush_print ($line);
    }
  }
  if ($make_devel || $make_all) {
    drush_print ('Downloading development modules');
    drush_shell_cd_and_exec ($path_to_drupal, 'drush make ../makefiles/contrib.make --no-core '.$extra_options);
    $output = drush_shell_exec_output ();
    foreach ($output as $line) {
      drush_print ($line);
    }
  }

  if ($reinstall) {
    $current_profile = variable_get ('install_profile');
    drush_shell_exec_interactive ("drush site-install $current_profile ".$extra_options);
  }
  else {
    drush_shell_exec_interactive ('drush registry-rebuild '.$extra_options);
  }
  
  drush_shell_exec_interactive ('drush updb '.$extra_options);
  drush_shell_exec_interactive ('drush features-revert-all '.$extra_options);
  drush_shell_exec_interactive ('drush rebuild @default.local '.$extra_options);
}
