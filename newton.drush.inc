<?php

/**
 * Implementation of hook_drush_command()
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
  $items['generate_history']=array(
    'description' => 'Creates a file with statistical data on the task in json',
    'arguments' => array ('csv' => 'If the filetype you want to use is csv'
    ),
    'required-arguments' => FALSE,
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
    'description' => 'take database and files from production server to actual environment',
    'examples' => array(
      'drush traepaca' => 'get all data from preproduction or other environment',
    ),
    'arguments' => array(
      'environment' => 'The environment indicator',
    ),
    'required-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['tirapapre'] = array(
    'description' => 'take database and files from production server to actual environment',
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
    'description' => 'init a project installing modules, environments and repository',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['join2project'] = array(
    'description' => 'ask about cuestions for joining existing project',
    'arguments' => array (
      'URL' => 'The URL indicator',
    ),
    'options' => array (
      'confirm' => 'Ask confirmation on every step',
    ),
    'requiered-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['deploy'] = array(
    'description' => 'ask about cuestions for joining existing project',
    'arguments' => array(
      'environment' => 'The environment indicator',
    ),
    'required-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  $items['n-revert'] = array(
    'description' => 'shows all overriden features on the portal and ask about revert then',
    'arguments' => array(
      'environment' => 'The environment indicator',
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
      'environment' => 'The environment indicator',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'aliases' => array('foto', 'afoto'),
  );
  $items['n-rollback'] = array(
    'description' => 'rollback the project to a concrete commit ID including database',
    'required-arguments' => FALSE,
    'arguments' => array(
      'environment' => 'The environment indicator',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'aliases' => array('marchaatras', 'patras'),
  );
  $items['n-rebuild'] = array(
    'description' => 'rebuilds project and makefiles if required',
    'required-arguments' => FALSE,
    'options' => array(
      'make-base' => 'Download core and run base.make',
      'make-contrib' => 'Run contrib.make',
      'make-devel' => 'Run devel.make',
      'make-all' => 'Download core and run all makefiles',
      'reinstall' => 'Reinstall the current profile',
      'yes' => 'Yes to all in operations'
    ),
  );
  $items['addfuncionality'] = array(
    'description' => 'add basic funcionalities based on developed features',
    'required-arguments' => FALSE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

include ('includes/constants.includes.inc');
include ('operations/newton.operation.inc');
include ('operations/initfeature.operation.inc');
include ('operations/endfeature.operation.inc');
include ('operations/generate_history.operation.inc');
include ('operations/n_init.operation.inc');
include ('operations/deploy.operation.inc');
include ('operations/capasao.operation.inc');
include ('operations/join2project.operation.inc');
include ('operations/traepaca.operation.inc');
include ('operations/tirapapre.operation.inc');
include ('operations/newtonupdate.operation.inc');
include ('operations/n_revert.operation.inc');
include ('operations/n_rollback.operation.inc');
include ('operations/n_snapshot.operation.inc');
include ('operations/n_rebuild.operation.inc');
include ('operations/addfuncionality.operation.inc');
