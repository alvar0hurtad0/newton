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
