<?php
/**
 * traepaca command callback.
 */
function drush_newton_traepaca($env = 'pre') {
  drush_shell_exec_interactive("drush sql-drop");
  drush_shell_exec_interactive("drush sql-sync @default.".$env." default -v");
  drush_shell_exec_interactive("drush rebuild @default.local --yes");
  
  foreach (drush_shell_exec_output() as $line) {
    $out .=$line."\n\r";
  }
  return $out;
}