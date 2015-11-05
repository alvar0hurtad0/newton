<?php
/**
 * initfeature command callback.
 */
function drush_newton_initfeature() 
{
    $id=drush_prompt("What's the ID of de Task?", null, false);
    if($id==null) {
        $id=0;
    }
    $description=drush_prompt("What's the description of the task?");
    $description=mb_substr($description, 0, 50);
    $characters=array(" :",": ",":","- ", " -","-"," ");
    $description=str_replace($characters, "_", $description);
    $idTask=$id."-".$description;
    drush_shell_exec_interactive('git checkout -b '.$idTask);
    drush_shell_exec_interactive('git tag init-'.$idTask);
}