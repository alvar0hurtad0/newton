<?php
/**
 * @file
 * Operation endfeature.
 */

/**
 * Endfeature command callback.
 */
function drush_newton_endfeature() {
  drush_shell_exec('git branch --list');
  $lines = drush_shell_exec_output();
  foreach ($lines as $value) {
    if (preg_match("/  /i", $value) == 0) {
      $id_task = substr($value, 2);
    }
  }
  $position = strpos($id_task, "-");
  $id = '"[#' . substr($id_task, 0, $position) . ']"';
  $description = substr($id_task, $position + 1);
  $time = drush_prompt(
    "How has been the task? 
    1 Expected
    2 Better than expected
    3 Worse than expected"
  );
  switch ($time) {
    case 1:
      // No reason.
      $reason = 1;
      $time_array = array('"how_was"' => $time);
      $reason_array = array('"reason"' => $reason);
      break;

    case 2:
      $time_array = array('"how_was"' => $time);
      $reason = drush_prompt(
        "Why reason?
        1 I found a tool that has helped me
        2 Others"
      );
      $reason_array = array('"reason"' => $reason);
      break;

    case 3:
      $time_array = array('"how_was"' => $time);
      $reason = drush_prompt(
        "Why reason?
        1 Lack of communication with the customer
        2 The task was not well planned
        3 Others"
      );
      $reason_array = array('"reason"' => $reason);
      break;

  }
  $id_array = array('"id"' => $id);
  $data = array_merge($id_array, $time_array, $reason_array);
  $data_json = json_encode($data);
  $reorganize = drush_prompt(
    "Do you want to reorganize commits?
    y Yes
    n No",
    NULL, FALSE
  );
  if ($reorganize == "y") {
    drush_shell_exec_interactive('git rebase -i init-' . $id_task);
  }
  drush_shell_exec_interactive('git checkout master');
  drush_shell_exec_interactive('git merge --no-ff ' . $id_task . ' -m "' . $id . ' ' . $description . '" -m "' . $data_json . '"');
}
