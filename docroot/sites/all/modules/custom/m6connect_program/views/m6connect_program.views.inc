<?php
/**
 * Implements hook_views_data_alter().
 */
/*function m6connect_program_views_data_alter(&$data) {
  $data['node']['company_address_custom'] = array(
    'field'=> array(
      'title' => 'Company Address Single Line',
	  'help' => 'Company Address Single Line.',
	  'handler'=> 'm6connect_program_handler_company_address_custom',
    )
  );
}*/

function m6connect_program_views_data() {
  $data = array();
  $data['company_details_custom']['table']['group'] = t('M6Company Detail');
  $data['company_details_custom']['table']['join'] = array(
    '#global' => array(),
  );
  
  // Add custom field
  $data['company_details_custom']['company_address_custom'] = array(
    'title' => t('Company Address Single Line'),
    'help' => t('Company Address Single Line.'),
    'field' => array(
      'handler' => 'm6connect_program_handler_company_address_custom',
    ),
  );
  return $data;
}