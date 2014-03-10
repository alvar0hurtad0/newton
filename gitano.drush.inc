<?php
/**
 * Implementation of hook_drush_command().
 */
function gitano_drush_command(){
  $items['newton'] = array(
    'description' => 'Shows all newton commands',
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
      'drush traepaca' => 'get all data from production',
    ),
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
  $items['init'] = array(
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
  return $items;
}

/**
 * newton command callback
 */
function drush_gitano_newton($number = NULL) {
  drush_print ('newton       -> shows this help',2);
  drush_print ('capasao      -> shows a log with colors and arrows about the git repository',2);
  drush_print ('init         -> kickstart a project',2);
  drush_print ('join2project -> ask about an existing projet to clone the repository and give database',2);
  drush_print ('traepaca     -> give database and files from preproduction enviroment',2);
  drush_print ('tirapapre    -> put live database and files into preproduction',2);
  drush_print ('n-revert     -> shows features of a given enviroment and help to revert then',2);
}

/**
 * capasao command callback
 */
function drush_gitano_capasao($number = NULL) {
 drush_shell_exec_interactive("git log --graph --color --decorate");
}

/**
 * traepaca command callback
 */
function drush_gitano_traepaca($number = NULL) {
  drush_shell_exec_interactive("drush sql-sync @default.pre default");
  drush_shell_exec_interactive("drush rsync @default.pre:sites/default/files default:sites/default/files");
  drush_shell_exec_interactive("drush cc all");
  drush_shell_exec_interactive("drush vset preprocess_css 0 --yes");

  foreach (drush_shell_exec_output() as $line) {
  	$out .=$line."\n\r"; 
  }
  return $out;
}

/**
 * traepaca command callback
 */
function drush_gitano_tirapapre($number = NULL) {
  drush_shell_exec_interactive("drush sql-sync @default.pro @default.pre");
  drush_shell_exec_interactive("drush rsync @default.pro:sites/default/files @default.pre:sites/default/files");
  drush_shell_exec_interactive("drush @default.pre cc all");
  drush_shell_exec_interactive("drush @default.pre vset preprocess_css 0 --yes");

  foreach (drush_shell_exec_output() as $line) {
    $out .=$line."\n\r"; 
  }
  return $out;
}

/**
 * newtonupdate command callback
 */
function drush_gitano_newtonupdate() {
  drush_shell_exec("cd ~/.drush/newton && git pull");
  drush_shell_exec("drush cc drush");
  foreach (drush_shell_exec_output() as $line) {
  	$out .=$line."\n\r"; 
  }
  return $out;
}

/**
 * init command callback
 */
function drush_gitano_init() {
  $project_name = drush_prompt("What's the name of the project, please");
  print ('I am downloading drupal core, it can take a minute, or two. Be patient please');
  drush_shell_exec_interactive('drush dl drupal --drupal-project-rename="'.$project_name.'" --yes');

  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  print ('Now enter some parameters for the development site, please\n\r');
  $admin_pass = drush_prompt("The admin password (secret password if blank)", $random);
  $site_name = drush_prompt("The name of the website, please (Project Name will be used if blank)",$project_name);
  $site_email = drush_prompt("Sites email (my@example.com if blank)",'my@example.com');
  $database_user = drush_prompt("Database user for THIS project (project name if blank)",$project_name);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');
  
  drush_shell_exec_interactive("cd $project_name && drush site-install minimal --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$project_name");

  drush_shell_exec('mkdir '.$project_name.'/sites/all/modules/contrib');
  drush_shell_exec('mkdir '.$project_name.'/sites/all/modules/custom');
  drush_shell_exec('mkdir '.$project_name.'/sites/all/modules/features');
  include ('init_modules.inc');
  $modules = gitano_init_modules();
  foreach ($modules as $project) {
    drush_shell_exec_interactive("cd $project_name && drush dl $project --yes && drush en $project --yes");
  }
  
}

/**
 * join2project command callback
 */
function drush_gitano_join2project() {
  $git_repository = drush_prompt("What's the URL of remote git repository");
  if ($git_repository ==''){
    return "OMG, if there's no repository there's no project";
  }

  print ('I am cloning the repository into your machine, it can take a bit of time');
  drush_shell_exec_interactive('git clone '.$git_repository);
  $project_name = drush_prompt("What's the directory name");

  $random = substr(str_shuffle("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 0, 7);

  print ('Now enter some parameters for the development site, please\n\r');
  $admin_pass = $random;
  $site_name = ('unnamed');
  $site_email = 'my@example.com';
  $database_user = drush_prompt("Database user for THIS project (directory name if blank)",$project_name);
  $database_user_pw = drush_prompt("Database user PASSWORD for this project (secret password if blank)",$random);
  $database_root = drush_prompt("Database super-user (root if blank)",'root');
  $database_root_pw = drush_prompt("Database super-user password (root if blank)",'root');
  
  drush_shell_exec_interactive("cd $project_name && drush site-install minimal --site-name=$site-name --account-pass=$admin_pass --db-su=$database_root --db-su-pw=$database_root_pw --db-url=mysql://$database_user:$database_user_pw@localhost/local_$project_name");
}

function drush_gitano_enviromentadd(){
  print ('Now be sure you have a PREproduction site. We´re going to confiure it.\n\r');
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

function drush_gitano_deploy($enviroment='pre'){
  switch ($enviroment){
    case 'pre':
      drush_shell_exec_interactive('drush @default.pre ssh "git pull"');
    break;
    case 'pro':
    drush_shell_exec_interactive('drush @default.pro ssh "git pull"');
  }
}

function drush_gitano_n_revert($enviroment=''){
  print('Looking for features, it can take some seconds... \n\r');
  switch ($enviroment){
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
    if ($cont == 0){
      $header = str_split($line);
      for ($i=0;$i < sizeof($header);$i++){
        if (($header[$i] !=' ') && ($lastchar == ' ')){
          $starts[]=$i; 
        }
        $lastchar=$header[$i];
      }
    }
    
    if($cont<10){
        $out =' '.$cont.' - '.$line."\n\r";
      }else{
        $out =$cont.' - '.$line."\n\r";
      }
    $cont ++;
    $featurename = substr($line, $starts[1], $starts[2]-$starts[1]);
    $features[]= trim($featurename);
    printf($out);
  }

  $option = drush_prompt("Enter the name of the feature to revert, please (0 to cancel)",'0',FALSE);
  if($option > 0){
    switch ($enviroment){
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
