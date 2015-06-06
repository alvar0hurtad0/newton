<?php
/**
 * generate_history command callback
 */
function drush_newton_generate_history ($format='json') {
  $file=drush_prompt("What's the filename?");
  drush_shell_exec('git log --grep="^\[#"');
  $lines=drush_shell_exec_output();
  foreach ($lines as $value)  {
    if (preg_match("/^    \{/i", $value)) {
      $string.=substr($value,4).", ";
    } 
  }
  $string='['.substr($string,0,strlen($string)-2).']';  
  if ($format=='csv') { 
    $decode=json_decode($string,true);
    $fp = fopen($file, "w");
    $firstLine= false;
    foreach ($decode as $line)
    {
      if (empty($firstLine)) {
        $firstLine=array_keys($line);
        fputcsv($fp, $firstLine);
        $firstLine=array_flip($firstLine);
      }
      fputcsv($fp,array_merge($firstLine,$line));
    }
    fclose($fp);
  }
  else {
    $string=substr($string,0,strlen($string));
    $fp=fopen($file,"w");
    fwrite ($fp,$string);
    fclose($fp);
  }
}