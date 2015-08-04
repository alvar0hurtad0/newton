<?php
/**
 * n-rebuild command callback.
 */
function drush_newton_n_rebuild () {
  $make_base = drush_get_option('make-base');
  $make_contrib = drush_get_option('make-contrib');
  $make_devel = drush_get_option('make-devel');
  $make_all = drush_get_option('make-all');

  $path_to_drupal = drush_get_context('DRUSH_DRUPAL_CORE');

  if ($make_base || $make_all) {
    drush_print ('Downloading core and base modules');
    drush_shell_cd_and_exec ($path_to_drupal, 'drush make ../makefiles/base.make --yes');
    $output = drush_shell_exec_output ();
    foreach ($output as $line) {
      drush_print ($line);
    }
  }
  if ($make_contrib || $make_all) {
    drush_print ('Downloading contrib modules, themes, libraries and patches');
    drush_shell_cd_and_exec ($path_to_drupal, 'drush make ../makefiles/contrib.make --no-core --yes');

    $output = drush_shell_exec_output ();
    foreach ($output as $line) {
      drush_print ($line);
    }
  }
  if ($make_devel || $make_all) {
    drush_print ('Downloading development modules');
    drush_shell_cd_and_exec ($path_to_drupal, 'drush make ../makefiles/contrib.make --no-core --yes');
    $output = drush_shell_exec_output ();
    foreach ($output as $line) {
      drush_print ($line);
    }
  }
  drush_shell_exec_interactive ('drush registry-rebuild');
  drush_shell_exec_interactive ('drush updb --yes');
  drush_shell_exec_interactive ('drush rebuild @default.local');
}
