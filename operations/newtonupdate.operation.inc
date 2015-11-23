<?php
/**
 * @file
 * Operation newtonupdate.
 */

/**
 * Newtonupdate command callback.
 */
function drush_newton_newtonupdate() {
  drush_shell_exec("cd ~/.drush/newton && git pull");
  drush_shell_exec("drush cc drush");
  foreach (drush_shell_exec_output() as $line) {
    $out .= $line . "\n\r";
  }
  return $out;
}
