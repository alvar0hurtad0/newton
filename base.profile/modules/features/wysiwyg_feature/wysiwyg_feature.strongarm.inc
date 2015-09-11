<?php
/**
 * @file
 * wysiwyg_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wysiwyg_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'htmlpurifier_version_ours';
  $strongarm->value = '4.7.0';
  $export['htmlpurifier_version_ours'] = $strongarm;

  return $export;
}
