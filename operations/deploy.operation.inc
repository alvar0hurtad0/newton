<?php
/**
 * deploy command callback.
 */

  use Symfony\Component\Yaml\Parser;
function drush_newton_deploy($environment='pre') {
  global $green;
  $merge = drush_prompt("merge before?",'yes');
  if ($merge == 'yes') {
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

    drush_print(sprintf($green, dt('git checkout '.$environment)));
    drush_shell_exec_interactive('git checkout '.$environment);
    drush_shell_exec_interactive('cd .'); // fix problems if the directory is new.
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

// get rebuild info and rebuild remote.  
  $site_root = drush_get_context('DRUSH_SELECTED_DRUPAL_ROOT');
  $overrides_path = $site_root . '/../rebuild_info/' . $environment . '_rebuild.yml';
  $overrides_content = @file_get_contents($overrides_path);
  
  if ($overrides_content){
    $yaml = new Parser();
    $configuration_changes = $yaml->parse($overrides_content);

    if (isset($configuration_changes['drupal']['modules']['enable'])) {
      $modules_enable = implode("," , $configuration_changes['drupal']['modules']['enable']);
      drush_shell_exec_interactive ('drush @default.'.$environment.' pm-enable ' . $modules_enable . ' --yes');
    }

    if (isset($configuration_changes['drupal']['modules']['disable'])){
      $modules_disable = implode(", " , $configuration_changes['drupal']['modules']['disable']);
      drush_shell_exec_interactive ('drush @default.'.$environment.' pm-disable ' . $modules_disable . ' --yes');
    }

    if (isset($configuration_changes['drupal']['variables']['set'])){
      foreach ($configuration_changes['drupal']['variables']['set'] as $key => $value) {
        drush_shell_exec_interactive ('drush @default.'.$environment.' vset ' . $key . ' ' . $value );
      }
    }
  }
  drush_shell_exec_interactive('drush @default.'.$environment.' features-revert-all --yes --force');
  drush_shell_exec_interactive('drush @default.'.$environment.' cache-clear all'); 
  drush_shell_exec_interactive('drush @default.'.$environment.' updatedb --yes');
  drush_shell_exec_interactive('drush @default.'.$environment.' cache-clear all');
}
