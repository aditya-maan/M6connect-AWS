<?php
/**
 * @file
 * m6connect_insurance_certificates_contracts.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function m6connect_insurance_certificates_contracts_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_info|node|insurance_certificates|form';
  $field_group->group_name = 'group_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional Insured Information',
    'weight' => '11',
    'children' => array(
      0 => 'field_location_address',
      1 => 'field_individual_company_name_2',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Additional Insured Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-additional-info field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_additional_info|node|insurance_certificates|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_certificate_information|node|insurance_certificates|form';
  $field_group->group_name = 'group_certificate_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Certificate Information',
    'weight' => '6',
    'children' => array(
      0 => 'field_certificate_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Certificate Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-certificate-information field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_certificate_information|node|insurance_certificates|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_insurance_types|node|insurance_certificates|form';
  $field_group->group_name = 'group_insurance_types';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Types of Insurance',
    'weight' => '8',
    'children' => array(
      0 => 'field_commercial_general_liabili',
      1 => 'field_automotive_liability',
      2 => 'field_professional_liability',
      3 => 'field_builders_risk',
      4 => 'field_garage_liability',
      5 => 'field_excess_liability',
      6 => 'field_workers_compensation_and_e',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-insurance-types field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_insurance_types|node|insurance_certificates|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_insured_information|node|insurance_certificates|form';
  $field_group->group_name = 'group_insured_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Insured Information',
    'weight' => '7',
    'children' => array(
      0 => 'field_individual_company_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Insured Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-insured-information field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_insured_information|node|insurance_certificates|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_insurer_information|node|insurance_certificates|form';
  $field_group->group_name = 'group_insurer_information';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Insurer Information',
    'weight' => '5',
    'children' => array(
      0 => 'field_insurance_company_name',
      1 => 'field_insurance_agent_s_name',
      2 => 'field_phone',
      3 => 'field_email',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Insurer Information',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-insurer-information field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_insurer_information|node|insurance_certificates|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_new_insurance_certificate|node|insurance_certificates|form';
  $field_group->group_name = 'group_new_insurance_certificate';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Submit New Insurance Certificate',
    'weight' => '4',
    'children' => array(
      0 => 'field_submit_to',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Submit New Insurance Certificate',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-new-insurance-certificate field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_new_insurance_certificate|node|insurance_certificates|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_selected_contracts|node|insurance_certificates|form';
  $field_group->group_name = 'group_selected_contracts';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'insurance_certificates';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Selected Project(s)/Contracts',
    'weight' => '10',
    'children' => array(
      0 => 'field_is_company_listed_as_a_cer',
      1 => 'field_address',
      2 => 'field_revision_number',
      3 => 'field_submit_to_project',
      4 => 'field_submit_to_contract',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Selected Project(s)/Contracts',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-selected-contracts field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_selected_contracts|node|insurance_certificates|form'] = $field_group;

  return $export;
}
