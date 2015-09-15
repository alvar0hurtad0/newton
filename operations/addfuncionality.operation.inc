<?php
/**
 * addfuncionality command callback.
 */
function drush_newton_addfuncionality() {
  $functionalities_path = '~/.drush/newton/functionalities';

  // List of funcionalities
  $options = array('1' => 'Basic page (A basic content page)',
    );
  
  $profile_name = variable_get('install_profile');
  $project_name = str_replace('_', '-', $profile_name);
  $features_path = WWW . '/' . $project_name . '/httpdocs/';
  $features_path .= variable_get('features_default_export_path');
  drush_print (sprintf(COLOR_MSG_INFO, '[ List of predefined features ]'));
  $code_funcionality = drush_choice($options, dt('Choose the feature to install'));

  switch ($code_funcionality) {
    case 1:
      $feature_name = 'basic_page_feature';
      if (is_dir("$features_path/$feature_name")) {
        drush_print (sprintf(COLOR_MSG_ERROR, $feature_name . ' directory already exits. Aborting installation of new feature...'));
      } else {
        drush_print (sprintf(COLOR_MSG_INFO, '[ Copying functionalities files ]'));
        drush_shell_exec_interactive('cp -r ' . $functionalities_path . '/' . $feature_name . ' ' . $features_path);
        if (create_field_base_if_required($feature_name,$features_path)) {
          drush_shell_exec_interactive('cd ' . WWW . "/" . $project_name .'/httpdocs && drush en ' . $feature_name . ' -y');
          drush_print (sprintf(COLOR_MSG_OK, '[ The ' . $feature_name . ' has been installed and enabled ]'));  
        }
      }
      break;
    default:
      drush_print (sprintf(COLOR_MSG_ERROR, 'You decided to cancel the installation.'));
      return;
  }
}

function create_field_base_if_required($funcionality_name=NULL, $install_path=NULL) {
  if (((!isset($funcionality_name)) || (!isset($install_path)))) {
    return FALSE;
    drush_print(sprintf(COLOR_MSG_ERROR,'There is no information about funcionality name or installation path.'));
  }
  include($install_path . '/' . $funcionality_name .'/' . $funcionality_name . '.features.field_instance.inc');
  $get_field_instances = $funcionality_name . '_field_default_field_instances';
  $field_instances_array = $get_field_instances();
  if (!isset($field_instances_array)) {
    drush_print(sprintf(COLOR_MSG_INFO,'This funcionality have no field_bases.'));
  }
  foreach ($field_instances_array as $key => $value) {
    if (!field_info_field($value['field_name'])) {
      drush_print(sprintf(COLOR_MSG_OK, 'Field base found: ' . $value['field_name']));
      include_once($install_path . '/' . $funcionality_name .'/' .$funcionality_name . '.features.field_base.inc');
      $get_field_bases = $funcionality_name.'_field_default_field_bases';
      $field_bases_array = $get_field_bases();
      drush_print(sprintf(COLOR_MSG_INFO, 'Field base configuration:'));
      drush_print_r($field_bases_array);
      field_create_field($field_bases_array[$value['field_name']]);
      drush_print(sprintf(COLOR_MSG_INFO, 'Field base ' . $value['field_name'] . ' created.'));
    } else {
      drush_print(sprintf(COLOR_MSG_INFO, 'Field base already exists: ' . $value['field_name'] . '. It will not be created again.'));
    }
  }
  return TRUE;
}