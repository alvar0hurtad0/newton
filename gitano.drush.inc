<?php
/**
 * Implementation of hook_drush_command().
 */
function gitano_drush_command(){
  $items['capasao'] = array(
    'description' => 'Shows a git log --oneline --graph',
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
  $items['gitanoupdate'] = array(
    'description' => 'updates GITANO to the last version',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['init'] = array(
    'description' => 'init a project installing modules, enviroments and repository',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * capasao command callback
 */
function drush_gitano_capasao($number = NULL) {
  $result = drush_shell_exec("git log --oneline --graph --color --decorate");
  foreach (drush_shell_exec_output() as $line) {
  	$out .=$line."\n\r"; 
  }
  return $out;
}

/**
 * traepaca command callback
 */
function drush_gitano_traepaca($number = NULL) {
  drush_shell_exec_interactive("drush sql-sync @default.pro default");
  drush_shell_exec_interactive("drush rsync @default.pro:sites/default/files default:sites/default/files");
  drush_shell_exec_interactive("drush cc all");
  drush_shell_exec_interactive("drush vset preprocess_css 0 --yes");

  foreach (drush_shell_exec_output() as $line) {
  	$out .=$line."\n\r"; 
  }
  return $out;
}

/**
 * gitanoupdate command callback
 */
function drush_gitano_gitanoupdate() {
  drush_shell_exec("cd ~/.drush/gitano");
  drush_shell_exec_interactive("git pull");
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
