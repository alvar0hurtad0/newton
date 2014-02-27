<?php
/**
 * Implementation of hook_drush_command().
 */
function gitano_drush_command(){
  $items['capasao'] = array(
    'description' => 'Shows a git log --oneline --graph',
    'examples' => array(
      'drush capasao' => 'shows de log',                                                 
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['traepaca'] = array(
    'description' => 'take database and files from production server to actual enviroment',
    'examples' => array(
      'drush traepaca' => 'get all data from production',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * capasao command callback
 */
function drush_gitano_capasao($number = NULL) {
  $result = drush_shell_exec("git log --oneline --graph --color --decorate");
  foreach (drush_shell_exec_output() as $line) {
  	$out .=$line."\n\r"; 
  }
  return $out;
}

/**
 * traepaca command callback
 */
function drush_gitano_traepaca($number = NULL) {
  drush_shell_exec_interactive("drush sql-sync @default.pro default");
  drush_shell_exec_interactive("drush rsync @default.pro:sites/default/files default:sites/default/files");
  drush_shell_exec_interactive("drush cc all");
  drush_shell_exec_interactive("drush vset preprocess_css 0 --yes");

  foreach (drush_shell_exec_output() as $line) {
  	$out .=$line."\n\r"; 
  }
  return $out;
}