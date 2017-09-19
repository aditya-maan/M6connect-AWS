<?php
/**
 * @file
 * m6connect_insurance_certificates_contracts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function m6connect_insurance_certificates_contracts_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function m6connect_insurance_certificates_contracts_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function m6connect_insurance_certificates_contracts_node_info() {
  $items = array(
    'contract' => array(
      'name' => t('Contract'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'insurance_certificates' => array(
      'name' => t('Insurance Certificates'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
