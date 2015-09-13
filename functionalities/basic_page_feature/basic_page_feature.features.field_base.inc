<?php
/**
 * @file
 * basic_page_feature.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function basic_page_feature_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_basic_page_body'
  $field_bases['field_basic_page_body'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_basic_page_body',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'text_with_summary',
  );

  return $field_bases;
}
