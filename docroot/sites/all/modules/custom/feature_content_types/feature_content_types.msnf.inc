<?php
/**
 * @file
 * feature_content_types.msnf.inc
 */

/**
 * Implements hook_msnf_step_info().
 */
function feature_content_types_msnf_step_info() {
  $export = array();

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_basic_information|node|rfp';
  $msnf->step_name = 'step_basic_information';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'rfp';
  $msnf->data = array(
    'label' => 'Basic Information',
    'weight' => '0',
    'children' => array(
      0 => 'field_rfp_name',
      1 => 'field_rfp_description',
      2 => 'field_public',
      3 => 'field_rfp_invite_new_pm',
      4 => 'field_new_project_name',
      5 => 'field_reference_number',
      6 => 'field_project_manager',
      7 => 'field_project',
      8 => 'field_new_project_check',
      9 => 'field_rfp_logo',
      10 => 'field_estimated_cost',
      11 => 'title',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'label' => 'Basic Information',
      'instance_settings' => array(
        'skip_non_required' => 0,
        'hide_if_empty' => 0,
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_basic_information|node|rfp'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_invite_companies|node|rfp';
  $msnf->step_name = 'step_invite_companies';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'rfp';
  $msnf->data = array(
    'label' => 'Invite Companies',
    'weight' => '3',
    'children' => array(
      0 => 'field_rpf_companies',
      1 => 'field_add_companies_by_email',
      2 => 'field_rpf_region',
      3 => 'field_rpf_facilities_construct',
      4 => 'field_rpf_industry_naics',
      5 => 'field_rfp_prdcts_services_unspsc',
      6 => 'field_rfp_economic_inclusion',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_invite_companies|node|rfp'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_pro_interested_companies|node|project';
  $msnf->step_name = 'step_pro_interested_companies';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'project';
  $msnf->data = array(
    'label' => 'Interested companies',
    'weight' => '4',
    'children' => array(
      0 => 'field_interested_list_mrk',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_pro_interested_companies|node|project'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_pro_invite_companies|node|project';
  $msnf->step_name = 'step_pro_invite_companies';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'project';
  $msnf->data = array(
    'label' => 'Invite Companies',
    'weight' => '2',
    'children' => array(
      0 => 'field_pro_invite_companies',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_pro_invite_companies|node|project'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_pro_summary|node|project';
  $msnf->step_name = 'step_pro_summary';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'project';
  $msnf->data = array(
    'label' => 'Summary',
    'weight' => '0',
    'children' => array(
      0 => 'field_public_description',
      1 => 'field_status',
      2 => 'field_complete_description',
      3 => 'field_project_public',
      4 => 'field_projects_keywords',
      5 => 'field_images',
      6 => 'field_project_address',
      7 => 'field_project_address_new',
      8 => 'field_pro_bidding_info',
      9 => 'title',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_pro_summary|node|project'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_pro_supplier_diversity|node|project';
  $msnf->step_name = 'step_pro_supplier_diversity';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'project';
  $msnf->data = array(
    'label' => 'Supplier diversity',
    'weight' => '1',
    'children' => array(
      0 => 'field_project_diversity_type',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_pro_supplier_diversity|node|project'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_rpf_documents|node|rfp';
  $msnf->step_name = 'step_rpf_documents';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'rfp';
  $msnf->data = array(
    'label' => 'Documents',
    'weight' => '2',
    'children' => array(
      0 => 'field_rfp_documents',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_rpf_documents|node|rfp'] = $msnf;

  $msnf = new stdClass();
  $msnf->disabled = FALSE; /* Edit this to true to make a default msnf disabled initially */
  $msnf->api_version = 1;
  $msnf->identifier = 'step_timeline|node|rfp';
  $msnf->step_name = 'step_timeline';
  $msnf->entity_type = 'node';
  $msnf->bundle = 'rfp';
  $msnf->data = array(
    'label' => 'Timeline',
    'weight' => '1',
    'children' => array(
      0 => 'field_issued',
      1 => 'field_due',
      2 => 'field_expected_award',
      3 => 'field_expected_start',
      4 => 'field_expected_end',
    ),
    'format_type' => 'default',
    'format_settings' => array(
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'classes' => '',
        'skip_non_required' => 1,
        'hide_if_empty' => 0,
        'buttons' => array(
          'previous' => 'Back',
          'next' => 'Next',
          'skip' => 'Skip next step',
        ),
      ),
    ),
  );
  $export['step_timeline|node|rfp'] = $msnf;

  return $export;
}
