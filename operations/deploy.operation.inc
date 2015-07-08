<?php
/**
 * deploy command callback.
 */
function drush_newton_deploy($environment='pre') {
  global $green;
  $merge = drush_prompt("merge before?",'yes');
  if ($merge = 'yes') {
    switch ($environment) {
      case 'pre':
        $previous_branch = 'master';
        break;
      case 'pro':
        $previous_branch = 'pre';
        break;
    }

    drush_print(sprintf($green, dt('git checkout '.$previous_branch)));
    drush_shell_exec_interactive('git checkout '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git pull origin '.$previous_branch)));
    drush_shell_exec_interactive('git pull origin '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git push origin '.$previous_branch)));
    drush_shell_exec_interactive('git push origin '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git checkout @default'.$environment)));
    drush_shell_exec_interactive('git checkout '.$environment);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git pull origin '.$environment)));
    drush_shell_exec_interactive('git pull origin '.$environment);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git merge '.$previous_branch)));
    drush_shell_exec_interactive('git merge '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git push origin '.$environment)));
    drush_shell_exec_interactive('git push origin '.$environment);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git checkout master')));
    drush_shell_exec_interactive('git checkout master');
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }
  }
  drush_shell_exec_interactive('drush @default.'.$environment.' ssh "git pull origin '.$environment.'"');
}
