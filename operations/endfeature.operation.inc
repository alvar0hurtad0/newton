<?php
/**
 * endfeature command callback.
 */
function drush_newton_endfeature () {
  drush_shell_exec('git branch --list');
  $lines=drush_shell_exec_output();
  foreach ($lines as $value)  {
    if (preg_match("/  /i", $value)==0) {
      $idTask=substr($value,2);
    }
  }
  $position=strpos($idTask,"-");
  $id='"[#'.substr($idTask,0,$position).']"';
  $description=substr($idTask,$position+1);
  $time=drush_prompt("How has been the task? 
  1 Expected
  2 Better than expected
  3 Worse than expected
  ");
  switch ($time) {
    case 1:
      $reason=1;//No reason
      $timeArray=array('"how_was"' => $time);
      $reasonArray=array('"reason"' => $reason);
      break;
    case 2:
      $timeArray=array('"how_was"' => $time);
      $reason=drush_prompt("Why reason?
      1 I found a tool that has helped me
      2 Others
      ");
      $reasonArray=array('"reason"' => $reason);
      break;    
    case 3:
      $timeArray=array('"how_was"' => $time);
      $reason=drush_prompt("Why reason?
      1 Lack of communication with the customer
      2 The task was not well planned
      3 Others
      ");      
      $reasonArray=array('"reason"' => $reason);
      break;
  }
  $idArray=array('"id"' => $id);
  $data=array_merge ($idArray, $timeArray, $reasonArray);  
  $dataJson=json_encode($data);
  $reorganize=drush_prompt("Do you want to reorganize commits?
  y Yes
  n No
  ",null,false);
  if ($reorganize=="y") {
    drush_shell_exec_interactive('git rebase -i init-'.$idTask);
  }
  drush_shell_exec_interactive('git checkout master');
  drush_shell_exec_interactive('git merge --no-ff '.$idTask.' -m "'.$id.' '.$description.'" -m "'.$dataJson.'"');
}