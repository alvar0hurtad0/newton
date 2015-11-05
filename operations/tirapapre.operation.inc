<?php
/**
 * tirapapre command callback.
 */
function drush_newton_tirapapre($number = null) 
{
    drush_shell_exec_interactive("drush sql-sync @default.pro @default.pre");
    drush_shell_exec_interactive('drush @default.pre ssh "drush rsync @default.pro:sites/default/files default:sites/default/files"');
    drush_shell_exec_interactive("drush @default.pre cc all");
    drush_shell_exec_interactive("drush @default.pre vset preprocess_css 0 --yes");

    foreach (drush_shell_exec_output() as $line) {
        $out .=$line."\n\r";
    }
    return $out;
}