<?php
/**
 * @file
 * Operation capasao.
 */

/**
 * Capasao command callback.
 */
function drush_newton_capasao() {
  drush_shell_exec_interactive("git log --graph --pretty=oneline --abbrev-commit --decorate --all $*");
}
