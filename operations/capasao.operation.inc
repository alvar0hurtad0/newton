<?php
/**
 * capasao command callback.
 */
function drush_newton_capasao($number = null) 
{
    drush_shell_exec_interactive("git log --graph --pretty=oneline --abbrev-commit --decorate --all $*");
}
