<?php
/**
 * capasao command callback.
 */
function drush_newton_capasao($number = NULL) {
  drush_shell_exec_interactive("git log --graph --color --decorate");
}