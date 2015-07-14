<?php
/**
 * @file
 * wysiwyg_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function wysiwyg_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format editor'.
  $permissions['use text format editor'] = array(
    'name' => 'use text format editor',
    'roles' => array(
      'Editor' => 'Editor',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
