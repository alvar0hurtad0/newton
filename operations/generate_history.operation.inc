<?php
/**
 * @file
 * Operation generate-history.
 */

/**
 * Generate_history command callback.
 */
function drush_newton_generate_history($format = 'json') {
  $file = drush_prompt("What's the filename?");
  drush_shell_exec('git log --grep="^\[#"');
  $lines = drush_shell_exec_output();
  foreach ($lines as $value) {
    if (preg_match("/^    \{/i", $value)) {
      $string .= substr($value, 4) . ", ";
    }
  }
  $string = '[' . substr($string, 0, strlen($string) - 2) . ']';
  if ($format == 'csv') {
    $decode = json_decode($string, TRUE);
    $fp = fopen($file, "w");
    $first_line = FALSE;
    foreach ($decode as $line) {
      if (empty($first_line)) {
        $first_line = array_keys($line);
        fputcsv($fp, $first_line);
        $first_line = array_flip($first_line);
      }
      fputcsv($fp, array_merge($first_line, $line));
    }
    fclose($fp);
  }
  else {
    $string = substr($string, 0, strlen($string));
    $fp = fopen($file, "w");
    fwrite($fp, $string);
    fclose($fp);
  }
}
