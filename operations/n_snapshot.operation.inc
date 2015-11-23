<?php
/**
 * @file
 * Operation n-snapshot.
 */

/**
 * N-snapshot command callback.
 */
function drush_newton_n_snapshot($environment = '') {
  drush_shell_exec('git log --pretty=format:"%H" -n1');
  $printed = drush_shell_exec_output();
  $commit_id = $printed[0];

  drush_shell_exec('git config --get remote.origin.url');
  $printed = drush_shell_exec_output();
  $remote_url = $printed[0];
  $remote_url_array = explode('/', $remote_url);
  $repo_name = $remote_url_array[count($remote_url_array) - 1];

  if ($environment == '') {
    drush_shell_exec('cd ~/.drush && mkdir cache');
    drush_shell_exec('cd ~/.drush/cache && mkdir newton');
    drush_shell_exec('cd ~/.drush/cache/newton && mkdir snapshot');
    drush_shell_exec('cd ~/.drush/cache/newton/snapshot && mkdir ' . $repo_name);
    drush_shell_exec_interactive('drush sql-dump --result-file=~/.drush/cache/newton/snapshot/' . $repo_name . '/' . $commit_id);
  }
  else {
    drush_shell_exec('drush @default.' . $environment . ' ssh "cd ~/.drush && mkdir cache"');
    drush_shell_exec('drush @default.' . $environment . ' ssh "cd ~/.drush/cache && mkdir newton"');
    drush_shell_exec('drush @default.' . $environment . ' ssh "cd ~/.drush/cache/newton && mkdir snapshot"');
    drush_shell_exec('drush @default.' . $environment . ' ssh "cd ~/.drush/cache/newton/snapshot && mkdir ' . $repo_name . '"');
    drush_shell_exec_interactive('drush @default.' . $environment . ' ssh "drush sql-dump --result-file=~/.drush/cache/newton/snapshot/' . $repo_name . '/' . $commit_id . '"');
  }
}
