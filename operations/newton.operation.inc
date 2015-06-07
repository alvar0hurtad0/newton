<?php
/**
 * Newton command callback.
 */
function drush_newton($number = NULL) {
  drush_print ('newton       -> shows this help',2);
  drush_print ('initfeature  -> Create a new task',2);
  drush_print ('endfeature   -> Ends a task',2);
  drush_print ('generate_history  -> Create a file with all data',2);
  drush_print ('capasao      -> shows a log with colors and arrows about the git repository',2);
  drush_print ('n-init       -> kickstart a project',2);
  drush_print ('join2project -> ask about an existing projet to clone the repository and give database',2);
  drush_print ('traepaca     -> give database and files from preproduction environment',2);
  drush_print ('tirapapre    -> put live database and files into preproduction',2);
  drush_print ('n-revert     -> shows features of a given environment and help to revert then',2);
}