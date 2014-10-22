<?php

/**
 * Implementation of hook_drush_command().
 */
function newton_drush_command() {
  $items['newton'] = array(
    'description' => 'Shows all newton commands',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['initfeature']= array(
    'description' => 'Create a new task',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['endfeature'] = array(
    'description' => 'Ends a task',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['capasao'] = array(
    'description' => 'Shows a git log --reverse --oneline --graph',
    'examples' => array(
      'drush capasao' => 'shows de log',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['traepaca'] = array(
    'description' => 'take database and files from production server to actual enviroment',
    'examples' => array(
      'drush traepaca' => 'get all data from preproduction or other enviroment',
    ),
    'arguments' => array(
      'enviroment' => 'The enviroment indicator',
    ),
    'required-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['tirapapre'] = array(
    'description' => 'take database and files from production server to actual enviroment',
    'examples' => array(
      'drush traepaca' => 'get all data from production',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['newtonupdate'] = array(
    'description' => 'updates NEWTON to the last version',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['n-init'] = array(
    'description' => 'init a project installing modules, enviroments and repository',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['join2project'] = array(
    'description' => 'ask about cuestions for joining existing project',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['deploy'] = array(
    'description' => 'ask about cuestions for joining existing project',
    'arguments' => array(
      'enviroment' => 'The enviroment indicator',
    ),
    'required-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['n-revert'] = array(
    'description' => 'shows all overriden features on the portal and ask about revert then',
    'arguments' => array(
      'enviroment' => 'The enviroment indicator',
    ),
    'required-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['n-serialized-features'] = array(
    'description' => 'shows all overriden features on the portal and ask about revert then',
    'required-arguments' => FALSE,
    'drupal dependencies' => array('features'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['n-snapshot'] = array(
    'description' => 'takes a snapshot of current database associated to the current commit id',
    'required-arguments' => FALSE,
        'arguments' => array(
      'enviroment' => 'The enviroment indicator',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'aliases' => array('foto', 'afoto'),
  );
  $items['n-rollback'] = array(
    'description' => 'rollback the project to a concrete commit ID including database',
    'required-arguments' => FALSE,
        'arguments' => array(
      'enviroment' => 'The enviroment indicator',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'aliases' => array('marchaatras', 'patras'),
  );
  return $items;
}

/**
 * Newton command callback.
 */
function drush_newton($number = NULL) {
  drush_print ('newton       -> shows this help',2);
  drush_print ('initfeature  -> Create a new task',2);
  drush_print ('endfeature   -> Ends a task',2);
  drush_print ('capasao      -> shows a log with colors and arrows about the git repository',2);
  drush_print ('n-init       -> kickstart a project',2);
  drush_print ('join2project -> ask about an existing projet to clone the repository and give database',2);
  drush_print ('traepaca     -> give database and files from preproduction enviroment',2);
  drush_print ('tirapapre    -> put live database and files into preproduction',2);
  drush_print ('n-revert     -> shows features of a given enviroment and help to revert then',2);
}

/**
 * initfeature command callback.
 */
function drush_newton_initfeature () {
  $id=drush_prompt("What's the ID of de Task?");
  $description=drush_prompt("What's the description of the task?");
  $description=mb_substr($description,0,50);
  $characters=array(" :",": ",":","- ", " -","-"," ");
  $description=str_replace($characters,"_",$description);
  $idTask=$id."-".$description;
  drush_shell_exec_interactive('git checkout -b '.$idTask);
}

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
  $id="#[".substr($idTask,0,$position)."]";
  $time=drush_prompt("How has been the task? 
  1 Expected
  2 Better than expected
  3 Worse than expected");
  switch ($time) {
    case 1:
      $time=1;
      $reason=6;
      $timeArray=array("how_was" => $time);
      $reasonArray=array("reason" => $reason);
      break;
    case 2:
      $timeArray=array("how_was" => $time);
      $reason=drush_prompt("Why reason?
      1 I found a tool that has helped me
      2 Others");
      switch ($reason) {
        case 1:
          $reasonArray=array("reason" => $reason);
          break;
        case 2:
          $reasonArray=array("reason" => $reason);
          break;
      }
      break;
    case 3:
      $timeArray=array("how_was" => $time);
      $reason=drush_prompt("Why reason?
      3 Lack of communication with the customer
      4 The task was not well planned
      5 Others");
      switch ($reason) {
        case 3:
          $reasonArray=array("reason" => $reason);
          break; 
        case 4:
          $reasonArray=array("reason" => $reason);
          break;
        case 5:
          $reasonArray=array("reason" => $reason);
          break;    
      }
      break;
  }
  $idArray=array("id" => $id);
  $data=array ($idArray, $timeArray, $reasonArray);  
  $dataJson=json_encode($data);
  print_r($dataJson);
  drush_shell_exec_interactive('git checkout master');
  drush_shell_exec_interactive('git merge --no-ff '.$idTask.' -m "'.$idTask.'" -m "'.$dataJson.'"');
}

/**
 * capasao command callback.
 */
function drush_newton_capasao($number = NULL) {
  drush_shell_exec_interactive("git log --graph --color --decorate");
}

/**
 * traepaca command callback.
 */
function drush_newton_traepaca($env = 'pre') {
  drush_shell_exec_interactive("drush sql-drop");
  drush_shell_exec_interactive("drush sql-sync @default.".$env." default -v");
  drush_shell_exec_interactive("drush rsync @default.".$env.":sites/default/files default:sites/default/files");
  drush_shell_exec_interactive("drush cc all");
  drush_shell_exec_interactive("drush vset preprocess_css 0 --yes");

  foreach (drush_shell_exec_output() as $line) {
    $out .=$line."\n\r";
  }
  return $out;
}

/**
 * tirapapre command callback.
 */
function drush_newton_tirapapre($number = NULL) {
  drush_shell_exec_interactive("drush sql-sync @default.pro @default.pre");
  drush_shell_exec_interactive('drush @default.pre ssh "drush rsync @default.pro:sites/default/files default:sites/default/files"');
  drush_shell_exec_interactive("drush @default.pre cc all");
  drush_shell_exec_interactive("drush @default.pre vset preprocess_css 0 --yes");

  foreach (drush_shell_exec_output() as $line) {
    $out .=$line."\n\r";
  }
  return $out;
}

/**
 * newtonupdate command callback.
 */
function drush_newton_newtonupdate() {
  drush_shell_exec("cd ~/.drush/newton && git pull");
  drush_shell_exec("drush cc drush");
  foreach (drush_shell_exec_output() as $line) {
    $out .=$line."\n\r";
  }
  return $out;
}

/**
 * n_init command callback.
 */
function drush_newton_n_init() {
  $project_name = drush_prompt("What's the name of the project, please");
  drush_print ('I am downloading drupal core, it can take a minute, or two. Be patient please');
  drush_shell_exec_interactive('drush dl drupal --drupal-project-rename="'.$project_name.'" --yes');

  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  drush_print ('Now enter some parameters for the development site, please');
  $admin_pass = drush_prompt("The admin password (secret password if blank)", $random);
  $site_name = drush_prompt("The name of the website, please (Project Name will be used if blank)",$project_name);
  $site_email = drush_prompt("Sites email (my@example.com if blank)",'my@example.com');
  $database_user = drush_prompt("Database user for THIS project (project name if blank)",$project_name);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');

  drush_shell_exec_interactive("cd $project_name/httpdocs && drush site-install minimal --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$project_name");

  drush_shell_exec('mkdir '.$project_name.'/httpdocs/sites/all/modules/contrib');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/sites/all/modules/custom');
  drush_shell_exec('mkdir '.$project_name.'/httpdocs/sites/all/modules/features');
  include ('init_modules.inc');
  $modules = gitano_init_modules();
  foreach ($modules as $project) {
    drush_shell_exec_interactive("cd $project_name && drush dl $project --yes && drush en $project --yes");
  }
}

/**
 * join2project command callback.
 */
function drush_newton_join2project() {
  $git_repository = drush_prompt("What's the URL of remote git repository");

  $pieces=explode('/',$git_repository);
  $size=sizeof($pieces);
  $last=$pieces[$size -1 ];
  $pieces_last=explode('.',$last);
  $project_name = $pieces_last[0];

  $project_name = drush_prompt("What's the project name", $project_name);
  drush_print ('I am cloning the repository into your machine, it can take a bit of time');
  drush_shell_exec_interactive('git clone '.$git_repository.' '.$project_name);

  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  drush_print ('Now enter some parameters for the development site, please\n\r');
  $admin_pass = $random;
  $site_name = ('unnamed');
  $site_email = 'my@example.com';
  $database_user = substr (drush_prompt("Database user for THIS project (directory name if blank)",$project_name), 0, 16);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');

  drush_shell_exec_interactive("cd ".$project_name."/httpdocs && drush site-install minimal --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$project_name");
  $synchronize = drush_prompt("synchronize from pre?",'yes');
  if ($synchronize == 'yes') {
    drush_shell_exec_interactive("cd ".$project_name."/httpdocs && drush traepaca");
  }
}

/**
 * enviromentadd command callback.
 */
function drush_newton_enviromentadd() {
  drush_print ('Now be sure you have a PREproduction site. We´re going to confiure it.\n\r');
  drush_shell_exec('mkdir '.$project_name.'/sites/all/drush');
  $pre_uri = drush_prompt("The uri");
  $pre_root = drush_prompt("The absolute path to drupal on system");
  $pre_remote_host = drush_prompt("The host where the drupal is installed");
  $pre_remote_user = drush_prompt("The the user to access on preproduction site");
  drush_shell_exec('echo "<?php" > '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "$aliases[\'pre\'] = array (" >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "\'uri\' => \''.$pre_uri.'\'," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "\'root\' => \''.$pre_root.'\'," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "\'remote-host\' => \''.$pre_remote_host.'\',"  >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "\'remote-user\' => \''.$pre_remote_user.'\',"  >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "\'command-specific\' => array(" >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "     \'sql-sync\' => array(" >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "         \'no-cache\' => TRUE," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "     )," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "     \'rsync\' => array (" >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "        \'delete\' => TRUE," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "         \'exclude-paths\' => \'/\'," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo "     )," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');
  drush_shell_exec('echo " )," >> '.$project_name.'/sites/all/drush/default.aliases.drushrc.php');

}

/**
 * deploy command callback.
 */
function drush_newton_deploy($enviroment='pre') {
  $green = "\033[0;33;40m\033[1m[%s]\033[0m";
  $merge = drush_prompt("merge before?",'yes');
  if ($merge = 'yes') {
    switch ($enviroment) {
      case 'pre':
        $previous_branch = 'master';
        break;
      case 'pro':
        $previous_branch = 'pre';
        break;
    }

    drush_print(sprintf($green, dt('git checkout '.$previous_branch)));
    drush_shell_exec_interactive('git checkout '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git pull origin '.$previous_branch)));
    drush_shell_exec_interactive('git pull origin '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git push origin '.$previous_branch)));
    drush_shell_exec_interactive('git push origin '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git checkout '.$enviroment)));
    drush_shell_exec_interactive('git checkout '.$enviroment);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git pull origin '.$enviroment)));
    drush_shell_exec_interactive('git pull origin '.$enviroment);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git merge '.$previous_branch)));
    drush_shell_exec_interactive('git merge '.$previous_branch);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git push origin '.$enviroment)));
    drush_shell_exec_interactive('git push origin '.$enviroment);
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }

    drush_print(sprintf($green, dt('git checkout master')));
    drush_shell_exec_interactive('git checkout master');
    $continue = drush_prompt("continue?????", 'yes');
    if ($continue != "yes") {
      return;
    }
  }
  drush_shell_exec_interactive('drush @default.'.$enviroment.' ssh "git pull origin '.$enviroment.'"');
}

function drush_newton_n_revert($enviroment='') {
  drush_print('Looking for features, it can take some seconds... \n\r');
  switch ($enviroment) {
    case 'pre':
      drush_shell_exec('drush @default.pre features --status=enabled');
      break;
    case 'pro':
      drush_shell_exec('drush @default.pro features --status=enabled');
      break;
    default:
      drush_shell_exec('drush features --status=enabled');
  }
  $cont=0;
  $features = array();
  $starts= array();

  $lastchar=' ';
  foreach (drush_shell_exec_output() as $line) {
    if ($cont == 0) {
      $header = str_split($line);
      for ($i=0;$i < sizeof($header);$i++) {
        if (($header[$i] !=' ') && ($lastchar == ' ')) {
          $starts[]=$i;
        }
        $lastchar=$header[$i];
      }
    }

    if ($cont<10) {
      $out =' '.$cont.' - '.$line."\n\r";
    }
    else{
      $out =$cont.' - '.$line."\n\r";
    }
    $cont ++;
    $featurename = substr($line, $starts[1], $starts[2]-$starts[1]);
    $features[]= trim($featurename);
    printf($out);
  }

  $option = drush_prompt("Enter the name of the feature to revert, please (0 to cancel)",'0',FALSE);
  if ($option > 0) {
    switch ($enviroment) {
      case 'pre':
        drush_shell_exec_interactive('drush @default.pre fr '.$features[$option]);
        break;
      case 'pro':
        drush_shell_exec_interactive('drush @default.pro fr '.$features[$option]);
        break;
      default:
        drush_shell_exec_interactive('drush  fr '.$features[$option]);
    }
  }
}

/**
 * n-snapshot command callback.
 */
function drush_newton_n_snapshot ($enviroment='') {
  drush_shell_exec('git log --pretty=format:"%H" -n1');
  $printed = drush_shell_exec_output();
  $commit_id = $printed[0];

  drush_shell_exec('git config --get remote.origin.url');
  $printed = drush_shell_exec_output();
  $remote_url = $printed[0];
  $remote_url_array=explode('/',$remote_url);
  $repo_name = $remote_url_array[sizeof($remote_url_array)-1];

  if ($enviroment=='') {
    drush_shell_exec('cd ~/.drush && mkdir cache');
    drush_shell_exec('cd ~/.drush/cache && mkdir newton');
    drush_shell_exec('cd ~/.drush/cache/newton && mkdir snapshot');
    drush_shell_exec('cd ~/.drush/cache/newton/snapshot && mkdir '.$repo_name);
    drush_shell_exec_interactive('drush sql-dump --result-file=~/.drush/cache/newton/snapshot/'.$repo_name.'/'.$commit_id);
  }
  else {
    drush_shell_exec('drush @default.'.$enviroment.' ssh "cd ~/.drush && mkdir cache"');
    drush_shell_exec('drush @default.'.$enviroment.' ssh "cd ~/.drush/cache && mkdir newton"');
    drush_shell_exec('drush @default.'.$enviroment.' ssh "cd ~/.drush/cache/newton && mkdir snapshot"');
    drush_shell_exec('drush @default.'.$enviroment.' ssh "cd ~/.drush/cache/newton/snapshot && mkdir '.$repo_name.'"');
    drush_shell_exec_interactive('drush @default.'.$enviroment.' ssh "drush sql-dump --result-file=~/.drush/cache/newton/snapshot/'.$repo_name.'/'.$commit_id.'"');
  }
}

/**
 * n-rollback command callback.
 */
function drush_newton_n_rollback ($enviroment='') {
  drush_shell_exec('git log --pretty=format:"%H" -n1');
  $printed = drush_shell_exec_output();
  $commit_id = $printed[0];

  drush_shell_exec('git config --get remote.origin.url');
  $printed = drush_shell_exec_output();
  $remote_url = $printed[0];
  $remote_url_array=explode('/',$remote_url);
  $repo_name = $remote_url_array[sizeof($remote_url_array)-1];

  $cont=0;
  if ($enviroment=='') {
    drush_shell_exec('cd ~/.drush/cache/newton/snapshot/'.$repo_name.' && ls');
    $printed = drush_shell_exec_output();
    foreach ($printed as $item) {
      drush_shell_exec('git log --pretty="%H %cd %s" '.$item.' -n1');
      $commit_info = drush_shell_exec_output();
      drush_print(($cont+1).' - '.$commit_info[0],2);
      $cont++;
    }
    $option = drush_prompt("Enter the number of snapshot to rollback, please (0 to cancel)",'0',TRUE);
    drush_shell_exec_interactive ('git checkout '.$printed[$option-1]);
    drush_shell_exec('echo ~');
    $user_home = drush_shell_exec_output();
    drush_shell_exec_interactive ('drush sql-query --file="'.$user_home[0].'/.drush/cache/newton/snapshot/'.$repo_name.'/'.$printed[$option-1].'"');
  }
  else {
    drush_shell_exec('drush @default.'.$enviroment.' ssh "cd ~/.drush/cache/newton/snapshot/'.$repo_name.' && ls"');
    $printed = drush_shell_exec_output();
    foreach ($printed as $item) {
      drush_shell_exec('git log --pretty="%H %cd %s" '.$item.' -n1');
      $commit_info = drush_shell_exec_output();
      drush_print(($cont+1).' - '.$commit_info[0],2);
      $cont++;
    }
    $option = drush_prompt("Enter the number of snapshot to rollback, please (0 to cancel)",'0',TRUE);
    drush_shell_exec_interactive('drush @default.'.$enviroment.' ssh "git checkout '.$printed[$option-1].'"');
    drush_shell_exec('drush @default.'.$enviroment.' ssh "echo ~"');
    $user_home = drush_shell_exec_output();
    foreach($user_home as $item) {
     if ($item[0]=='/') {
       $remote_home = $item;
      }
    }
    drush_shell_exec_interactive('drush @default.'.$enviroment.' ssh "drush sql-query --file='.$remote_home.'/.drush/cache/newton/snapshot/'.$repo_name.'/'.$printed[$option-1].'"');
  }
}

