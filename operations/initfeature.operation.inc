<?php
/**
 * @file
 * Operation initfeature.
 */

/**
 * Initfeature command callback.
 */
function drush_newton_initfeature() {
  $id = drush_prompt("What's the ID of de Task?", NULL, FALSE);
  if ($id == NULL) {
    $id = 0;
  }
  $description = drush_prompt("What's the description of the task?");
  $description = mb_substr($description, 0, 50);
  $characters = array(" :", ": ", ":", "- ", " -", "-", " ");
  $description = str_replace($characters, "_", $description);
  $id_task = $id . "-" . $description;
  drush_shell_exec_interactive('git checkout -b ' . $id_task);
  drush_shell_exec_interactive('git tag init-' . $id_task);
}
