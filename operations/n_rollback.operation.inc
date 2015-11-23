<?php
/**
 * @file
 * Operation n-rollback.
 */

/**
 * N-rollback command callback.
 */
function drush_newton_n_rollback($environment = '') {
  drush_shell_exec('git log --pretty=format:"%H" -n1');
  $printed = drush_shell_exec_output();
  $commit_id = $printed[0];

  drush_shell_exec('git config --get remote.origin.url');
  $printed = drush_shell_exec_output();
  $remote_url = $printed[0];
  $remote_url_array = explode('/', $remote_url);
  $repo_name = $remote_url_array[count($remote_url_array) - 1];

  $cont = 0;
  if ($environment == '') {
    drush_shell_exec('cd ~/.drush/cache/newton/snapshot/' . $repo_name . ' && ls');
    $printed = drush_shell_exec_output();
    foreach ($printed as $item) {
      drush_shell_exec('git log --pretty="%H %cd %s" ' . $item . ' -n1');
      $commit_info = drush_shell_exec_output();
      drush_print(($cont + 1) . ' - ' . $commit_info[0], 2);
      $cont++;
    }
    $option = drush_prompt("Enter the number of snapshot to rollback, please (0 to cancel)", '0', TRUE);
    drush_shell_exec_interactive('git checkout ' . $printed[$option - 1]);
    drush_shell_exec('echo ~');
    $user_home = drush_shell_exec_output();
    drush_shell_exec_interactive('drush sql-query --file="' . $user_home[0] . '/.drush/cache/newton/snapshot/' . $repo_name . '/' . $printed[$option - 1] . '"');
  }
  else {
    drush_shell_exec('drush @default.' . $environment . ' ssh "cd ~/.drush/cache/newton/snapshot/' . $repo_name . ' && ls"');
    $printed = drush_shell_exec_output();
    foreach ($printed as $item) {
      drush_shell_exec('git log --pretty="%H %cd %s" ' . $item . ' -n1');
      $commit_info = drush_shell_exec_output();
      drush_print(($cont + 1) . ' - ' . $commit_info[0], 2);
      $cont++;
    }
    $option = drush_prompt("Enter the number of snapshot to rollback, please (0 to cancel)", '0', TRUE);
    drush_shell_exec_interactive('drush @default.' . $environment . ' ssh "git checkout ' . $printed[$option - 1] . '"');
    drush_shell_exec('drush @default.' . $environment . ' ssh "echo ~"');
    $user_home = drush_shell_exec_output();
    foreach ($user_home as $item) {
      if ($item[0] == '/') {
        $remote_home = $item;
      }
    }
    drush_shell_exec_interactive('drush @default.' . $environment . ' ssh "drush sql-query --file=' . $remote_home . '/.drush/cache/newton/snapshot/' . $repo_name . '/' . $printed[$option - 1] . '"');
  }
}
