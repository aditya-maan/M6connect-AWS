<?php
/**
 * @file
 * m6connect_insurance_certificate_review.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function m6connect_insurance_certificate_review_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'insurance_certificate_review';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Insurance Certificate Review';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Individual/Company Name */
  $handler->display->display_options['fields']['field_individual_company_name']['id'] = 'field_individual_company_name';
  $handler->display->display_options['fields']['field_individual_company_name']['table'] = 'field_data_field_individual_company_name';
  $handler->display->display_options['fields']['field_individual_company_name']['field'] = 'field_individual_company_name';
  $handler->display->display_options['fields']['field_individual_company_name']['label'] = 'Submitted By';
  $handler->display->display_options['fields']['field_individual_company_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_individual_company_name']['element_default_classes'] = FALSE;
  /* Field: Content: Insurance Company Name */
  $handler->display->display_options['fields']['field_insurance_company_name']['id'] = 'field_insurance_company_name';
  $handler->display->display_options['fields']['field_insurance_company_name']['table'] = 'field_data_field_insurance_company_name';
  $handler->display->display_options['fields']['field_insurance_company_name']['field'] = 'field_insurance_company_name';
  $handler->display->display_options['fields']['field_insurance_company_name']['label'] = 'Insurance Company Information';
  $handler->display->display_options['fields']['field_insurance_company_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_insurance_company_name']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_insurance_company_name']['element_wrapper_class'] = 'col-md-6';
  $handler->display->display_options['fields']['field_insurance_company_name']['element_default_classes'] = FALSE;
  /* Field: Content: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['label'] = '';
  $handler->display->display_options['fields']['field_email']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_email']['element_label_colon'] = FALSE;
  /* Field: Field: Phone */
  $handler->display->display_options['fields']['field_phone']['id'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['field_phone']['field'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['label'] = '';
  $handler->display->display_options['fields']['field_phone']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_phone']['element_label_colon'] = FALSE;
  /* Field: Content: Insurance Agent's Name */
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['id'] = 'field_insurance_agent_s_name';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['table'] = 'field_data_field_insurance_agent_s_name';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['field'] = 'field_insurance_agent_s_name';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['label'] = 'Insurance Agent Information';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['alter']['text'] = '<p>[field_insurance_agent_s_name]</p>
<p>[field_email]</p>
<p>[field_phone]</p>';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['element_wrapper_class'] = 'col-md-6';
  $handler->display->display_options['fields']['field_insurance_agent_s_name']['element_default_classes'] = FALSE;
  /* Field: Field: Address - Postal code */
  $handler->display->display_options['fields']['field_address_postal_code']['id'] = 'field_address_postal_code';
  $handler->display->display_options['fields']['field_address_postal_code']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address_postal_code']['field'] = 'field_address_postal_code';
  $handler->display->display_options['fields']['field_address_postal_code']['label'] = '';
  $handler->display->display_options['fields']['field_address_postal_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_address_postal_code']['element_label_colon'] = FALSE;
  /* Field: Content: Individual/Company Name */
  $handler->display->display_options['fields']['field_individual_company_name_1']['id'] = 'field_individual_company_name_1';
  $handler->display->display_options['fields']['field_individual_company_name_1']['table'] = 'field_data_field_individual_company_name';
  $handler->display->display_options['fields']['field_individual_company_name_1']['field'] = 'field_individual_company_name';
  $handler->display->display_options['fields']['field_individual_company_name_1']['label'] = 'Additional Insured';
  $handler->display->display_options['fields']['field_individual_company_name_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_individual_company_name_1']['alter']['text'] = '<p>[field_individual_company_name_1]</p>
<p>[field_address_postal_code]</p>';
  $handler->display->display_options['fields']['field_individual_company_name_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_individual_company_name_1']['element_default_classes'] = FALSE;
  /* Field: Content: Commercial General Liability */
  $handler->display->display_options['fields']['field_commercial_general_liabili']['id'] = 'field_commercial_general_liabili';
  $handler->display->display_options['fields']['field_commercial_general_liabili']['table'] = 'field_data_field_commercial_general_liabili';
  $handler->display->display_options['fields']['field_commercial_general_liabili']['field'] = 'field_commercial_general_liabili';
  $handler->display->display_options['fields']['field_commercial_general_liabili']['label'] = '';
  $handler->display->display_options['fields']['field_commercial_general_liabili']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_commercial_general_liabili']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_commercial_general_liabili']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_commercial_general_liabili']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_commercial_general_liabili']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Content: Automotive Liability */
  $handler->display->display_options['fields']['field_automotive_liability']['id'] = 'field_automotive_liability';
  $handler->display->display_options['fields']['field_automotive_liability']['table'] = 'field_data_field_automotive_liability';
  $handler->display->display_options['fields']['field_automotive_liability']['field'] = 'field_automotive_liability';
  $handler->display->display_options['fields']['field_automotive_liability']['label'] = '';
  $handler->display->display_options['fields']['field_automotive_liability']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_automotive_liability']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_automotive_liability']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_automotive_liability']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_automotive_liability']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Content: Professional Liability */
  $handler->display->display_options['fields']['field_professional_liability']['id'] = 'field_professional_liability';
  $handler->display->display_options['fields']['field_professional_liability']['table'] = 'field_data_field_professional_liability';
  $handler->display->display_options['fields']['field_professional_liability']['field'] = 'field_professional_liability';
  $handler->display->display_options['fields']['field_professional_liability']['label'] = '';
  $handler->display->display_options['fields']['field_professional_liability']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_professional_liability']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_professional_liability']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_professional_liability']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_professional_liability']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Content: Builders Risk */
  $handler->display->display_options['fields']['field_builders_risk']['id'] = 'field_builders_risk';
  $handler->display->display_options['fields']['field_builders_risk']['table'] = 'field_data_field_builders_risk';
  $handler->display->display_options['fields']['field_builders_risk']['field'] = 'field_builders_risk';
  $handler->display->display_options['fields']['field_builders_risk']['label'] = '';
  $handler->display->display_options['fields']['field_builders_risk']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_builders_risk']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_builders_risk']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_builders_risk']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_builders_risk']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Content: Garage Liability */
  $handler->display->display_options['fields']['field_garage_liability']['id'] = 'field_garage_liability';
  $handler->display->display_options['fields']['field_garage_liability']['table'] = 'field_data_field_garage_liability';
  $handler->display->display_options['fields']['field_garage_liability']['field'] = 'field_garage_liability';
  $handler->display->display_options['fields']['field_garage_liability']['label'] = '';
  $handler->display->display_options['fields']['field_garage_liability']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_garage_liability']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_garage_liability']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_garage_liability']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Content: Excess Liability */
  $handler->display->display_options['fields']['field_excess_liability']['id'] = 'field_excess_liability';
  $handler->display->display_options['fields']['field_excess_liability']['table'] = 'field_data_field_excess_liability';
  $handler->display->display_options['fields']['field_excess_liability']['field'] = 'field_excess_liability';
  $handler->display->display_options['fields']['field_excess_liability']['label'] = '';
  $handler->display->display_options['fields']['field_excess_liability']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_excess_liability']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_excess_liability']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_excess_liability']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_excess_liability']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Content: Workers Compensation and employers Liability */
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['id'] = 'field_workers_compensation_and_e';
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['table'] = 'field_data_field_workers_compensation_and_e';
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['field'] = 'field_workers_compensation_and_e';
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['label'] = '';
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_workers_compensation_and_e']['settings'] = array(
    'view_mode' => 'full',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<b>Coverage Details</b>
[field_commercial_general_liabili]
[field_automotive_liability]
[field_professional_liability]
[field_builders_risk]
[field_garage_liability]
[field_excess_liability]
[field_workers_compensation_and_e]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'insurance_certificates' => 'insurance_certificates',
  );

  /* Display: Submitted Insurance Certificate Block */
  $handler = $view->new_display('block', 'Submitted Insurance Certificate Block', 'block_1');

  /* Display: Contract Insurance Requirements */
  $handler = $view->new_display('block', 'Contract Insurance Requirements', 'block_2');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Submit to Project */
  $handler->display->display_options['fields']['field_submit_to_project']['id'] = 'field_submit_to_project';
  $handler->display->display_options['fields']['field_submit_to_project']['table'] = 'field_data_field_submit_to_project';
  $handler->display->display_options['fields']['field_submit_to_project']['field'] = 'field_submit_to_project';
  $handler->display->display_options['fields']['field_submit_to_project']['label'] = 'Project(s)';
  $handler->display->display_options['fields']['field_submit_to_project']['alter']['path'] = '/insurance-contract/%1';
  $handler->display->display_options['fields']['field_submit_to_project']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['field_submit_to_project']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_submit_to_project']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Associate to Contract */
  $handler->display->display_options['fields']['field_submit_to_contract']['id'] = 'field_submit_to_contract';
  $handler->display->display_options['fields']['field_submit_to_contract']['table'] = 'field_data_field_submit_to_contract';
  $handler->display->display_options['fields']['field_submit_to_contract']['field'] = 'field_submit_to_contract';
  $handler->display->display_options['fields']['field_submit_to_contract']['label'] = 'Contract(s)';
  $handler->display->display_options['fields']['field_submit_to_contract']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_submit_to_contract']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Insurance Requirements';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: File Upload */
  $handler->display->display_options['fields']['field_file_upload']['id'] = 'field_file_upload';
  $handler->display->display_options['fields']['field_file_upload']['table'] = 'field_data_field_file_upload';
  $handler->display->display_options['fields']['field_file_upload']['field'] = 'field_file_upload';
  $handler->display->display_options['fields']['field_file_upload']['label'] = 'File';
  $handler->display->display_options['fields']['field_file_upload']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_file_upload']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_file_upload']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_file_upload']['settings'] = array(
    'text' => 'Download File',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content revision: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node_revision';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $export['insurance_certificate_review'] = $view;

  return $export;
}
