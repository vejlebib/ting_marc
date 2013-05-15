<?php
/**
 * @file
 * ting_marc.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function ting_marc_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer ting_marc settings.
  $permissions['administer ting_marc settings'] = array(
    'name' => 'administer ting_marc settings',
    'roles' => array(
      0 => 'administrator',
      1 => 'local administrator',
    ),
    'module' => 'ting_marc',
  );

  return $permissions;
}
