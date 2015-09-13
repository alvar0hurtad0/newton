<?php
/**
 * addfuncionality command callback.
 */
function drush_newton_addfuncionality() {
  $functionalities_path = '~/.drush/newton/functionalities';
  // Color schema for messages
  $msg_colors = array(
    'info' => '%s',
    'error'  => '%s',
    'ok' => '%s');
  $msg_colors['error'] = "\033[31;40m\033[1m%s\033[0m";
  $msg_colors['info'] = "\033[1;33;40m\033[1m%s\033[0m";
  $msg_colors['ok'] = "\033[1;32;40m\033[1m%s\033[0m";
  // List of funcionalities
  $options = array('1' => 'Basic page (A basic content page)',
    );

  $project_name = drush_prompt("What's the name of the project where you want to install new functionalities? (remember customer-project)");
  if (!is_dir($project_name)) {
    drush_print(sprintf($msg_colors['error'],'I cannot find the directory. Aborting installation of new features...'));
    return;
  }
  $profile_name = str_replace('-', '_', $project_name);
  $features_path = "/var/www/$project_name/httpdocs/profiles/$profile_name/modules/features";
  drush_print (sprintf($msg_colors['info'], 'Projects features path: ' . $features_path));
  drush_print (sprintf($msg_colors['ok'], '[ List of predefined features ]'));
  $code_funcionality = drush_choice($options, dt('Choose the feature to install'));

  switch ($code_funcionality) {
    case 1:
      if (is_dir("$features_path/basic_page_feature")) {
        drush_print (sprintf($msg_colors['error'], 'basic_page_feature directory already exits. Aborting installation of new feature...'));
      } else {
        drush_print (sprintf($msg_colors['info'], '[ Copying functionalities files ]'));
        drush_shell_exec_interactive('cp -r ' . $functionalities_path . '/basic_page_feature ' . $features_path);
        // Download dependencies with feature.make if necessary
        drush_shell_exec_interactive("cd $project_name/httpdocs && drush en basic_page_feature -y");
  	    drush_print (sprintf($msg_colors['ok'], 'The Basic page feature has been installed and enabled.'));
  	  }
  	  break;
    default:
      drush_print (sprintf($msg_colors['error'], 'You decided to cancel the installation.'));
      return;
  }
}
