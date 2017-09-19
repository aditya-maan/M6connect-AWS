<?php
/**
 * @file
 * feature_content_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function feature_content_types_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_basic_info|node|rfp|default';
  $field_group->group_name = 'group_basic_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rfp';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rfp';
  $field_group->data = array(
    'label' => 'Basic Information',
    'weight' => '1',
    'children' => array(
      0 => 'field_rfp_name',
      1 => 'field_rfp_description',
      2 => 'field_rfp_invite_new_pm',
      3 => 'field_new_project_name',
      4 => 'field_reference_number',
      5 => 'field_project_manager',
      6 => 'field_project',
      7 => 'field_rfp_logo',
      8 => 'field_estimated_cost',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-basic-info field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_basic_info|node|rfp|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_classification|node|organization|form';
  $field_group->group_name = 'group_classification';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_company_details';
  $field_group->data = array(
    'label' => 'Business Types',
    'weight' => '12',
    'children' => array(
      0 => 'field_regions',
      1 => 'field_products_service_unspsc',
      2 => 'field_industry_naicss',
      3 => 'field_facilities_construction',
      4 => 'field_timezone',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Business Types',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-classification field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_classification|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_company_details_tab|node|organization|default';
  $field_group->group_name = 'group_company_details_tab';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_company_details';
  $field_group->data = array(
    'label' => 'Public Profile',
    'weight' => '106',
    'children' => array(
      0 => 'field_owner_name',
      1 => 'field_description',
      2 => 'field_service_description',
      3 => 'field_logo',
      4 => 'field_org_phone',
      5 => 'field_website',
      6 => 'field_org_address',
      7 => 'title',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Public Profile',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-company-details-tab field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_company_details_tab|node|organization|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_company_details|node|organization|default';
  $field_group->group_name = 'group_company_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Company Deatils',
    'weight' => '0',
    'children' => array(
      0 => 'group_company_details_tab',
      1 => 'group_diversity_company_grp_tab',
      2 => 'group_co_summary_tab',
      3 => 'group_co_locations',
      4 => 'group_co_classifications_tab',
      5 => 'group_co_user_tab',
      6 => 'group_co_account_tab',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-company-details field-group-htabs',
      ),
    ),
  );
  $export['group_company_details|node|organization|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_company_details|node|organization|form';
  $field_group->group_name = 'group_company_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Company Details',
    'weight' => '0',
    'children' => array(
      0 => 'group_company_summary',
      1 => 'group_public_profile',
      2 => 'group_location',
      3 => 'group_supplier_diversity',
      4 => 'group_classification',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'Company Details',
      'instance_settings' => array(
        'classes' => 'group-company-details field-group-htabs',
      ),
    ),
  );
  $export['group_company_details|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_company_summary|node|organization|form';
  $field_group->group_name = 'group_company_summary';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_company_details';
  $field_group->data = array(
    'label' => 'Company Summary',
    'weight' => '9',
    'children' => array(
      0 => 'field_legal_name',
      1 => 'field_legal_structure',
      2 => 'field_taxpayer_ssn_ein',
      3 => 'field_duns_number',
      4 => 'field_keywords',
      5 => 'field_number_employees',
      6 => 'field_year_founded',
      7 => 'field_incorporated_country',
      8 => 'field_incorporated_state',
      9 => 'field_projects',
      10 => 'group_group',
      11 => 'field_cage_code',
      12 => 'field_annual_revenue',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-company-summary field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_company_summary|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cust_hidden_field|node|organization|form';
  $field_group->group_name = 'group_cust_hidden_field';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Hidden fields',
    'weight' => '2',
    'children' => array(
      0 => 'group_register',
      1 => 'field_dcrednid_23',
      2 => 'field_dcrednid_22',
      3 => 'field_company_type',
      4 => 'field_dcrednid_97',
      5 => 'field_dcrednid_98',
      6 => 'field_dcrednid_99',
      7 => 'field_dcrednid_100',
      8 => 'field_dcrednid_101',
      9 => 'field_dcrednid_102',
      10 => 'field_dcrednid_103',
      11 => 'field_dcrednid_104',
      12 => 'field_dcrednid_105',
      13 => 'field_dcrednid_106',
      14 => 'field_dcrednid_107',
      15 => 'field_dcrednid_108',
      16 => 'field_dcrednid_109',
      17 => 'field_dcrednid_110',
      18 => 'field_dcrednid_112',
      19 => 'field_dcrednid_113',
      20 => 'field_dcrednid_114',
      21 => 'field_business_types',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-cust-hidden-field field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_cust_hidden_field|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_diversity_grp|node|project|default';
  $field_group->group_name = 'group_diversity_grp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_project_details_tab';
  $field_group->data = array(
    'label' => 'Diversity grp',
    'weight' => '5',
    'children' => array(
      0 => 'field_project_diversity_type',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-diversity-grp field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_diversity_grp|node|project|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_document_info|node|rfp|default';
  $field_group->group_name = 'group_document_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rfp';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rfp';
  $field_group->data = array(
    'label' => 'Documents',
    'weight' => '3',
    'children' => array(
      0 => 'field_rfp_documents',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-document-info field-group-htab',
        'id' => '',
      ),
    ),
  );
  $export['group_document_info|node|rfp|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_full_diversity_grp_tab|node|project|full';
  $field_group->group_name = 'group_full_diversity_grp_tab';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'full';
  $field_group->parent_name = 'group_full_pdetails_grp';
  $field_group->data = array(
    'label' => 'Seeking Diversity Suppliers',
    'weight' => '6',
    'children' => array(
      0 => 'field_project_diversity_type',
      1 => 'pro_diversity_help_text',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Seeking Diversity Suppliers',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-full-diversity-grp-tab field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_full_diversity_grp_tab|node|project|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_full_pdetails_grp_tab|node|project|full';
  $field_group->group_name = 'group_full_pdetails_grp_tab';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'full';
  $field_group->parent_name = 'group_full_pdetails_grp';
  $field_group->data = array(
    'label' => 'Project Details',
    'weight' => '5',
    'children' => array(
      0 => 'field_public_description',
      1 => 'field_status',
      2 => 'field_complete_description',
      3 => 'og_group_ref',
      4 => 'field_projects_keywords',
      5 => 'field_images',
      6 => 'field_project_address',
      7 => 'field_project_address_new',
      8 => 'field_pro_bidding_info',
      9 => 'interested_flag_field',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Project Details',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-full-pdetails-grp-tab field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_full_pdetails_grp_tab|node|project|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_full_pdetails_grp|node|project|full';
  $field_group->group_name = 'group_full_pdetails_grp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project Details',
    'weight' => '0',
    'children' => array(
      0 => 'group_full_pdetails_grp_tab',
      1 => 'group_full_diversity_grp_tab',
      2 => 'group_full_int_comp',
      3 => 'group_full_invite_co',
      4 => 'group_full_pro_bid_co',
      5 => 'group_full_pro_rfps',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-full-pdetails-grp field-group-htabs',
      ),
    ),
  );
  $export['group_full_pdetails_grp|node|project|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_location|node|organization|form';
  $field_group->group_name = 'group_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_company_details';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '10',
    'children' => array(
      0 => 'field_org_phone',
      1 => 'field_org_address',
      2 => 'field_company_email',
      3 => 'field_org_fax',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-location field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_location|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_project_details_grp|node|project|default';
  $field_group->group_name = 'group_project_details_grp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_project_details_tab';
  $field_group->data = array(
    'label' => 'project details grp',
    'weight' => '4',
    'children' => array(
      0 => 'field_public_description',
      1 => 'field_status',
      2 => 'field_complete_description',
      3 => 'og_group_ref',
      4 => 'field_project_public',
      5 => 'field_projects_keywords',
      6 => 'field_images',
      7 => 'field_project_address',
      8 => 'field_pro_bidding_info',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'project details grp',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-project-details-grp field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_project_details_grp|node|project|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_project_details_tab|node|project|default';
  $field_group->group_name = 'group_project_details_tab';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'project';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Project Details',
    'weight' => '0',
    'children' => array(
      0 => 'group_project_details_grp',
      1 => 'group_diversity_grp',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-project-details-tab field-group-htabs',
      ),
    ),
  );
  $export['group_project_details_tab|node|project|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_public_profile|node|organization|form';
  $field_group->group_name = 'group_public_profile';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_company_details';
  $field_group->data = array(
    'label' => 'Public Profile',
    'weight' => '8',
    'children' => array(
      0 => 'field_owner_name',
      1 => 'field_description',
      2 => 'field_service_description',
      3 => 'field_logo',
      4 => 'field_website',
      5 => 'title',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-public-profile field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_public_profile|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_rfp|node|rfp|default';
  $field_group->group_name = 'group_rfp';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rfp';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'RFP Display',
    'weight' => '0',
    'children' => array(
      0 => 'group_basic_info',
      1 => 'group_timeline_info',
      2 => 'group_document_info',
      3 => 'group_invited_companies',
      4 => 'group_clarifications_info',
      5 => 'group_proposals_info',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'label' => 'RFP Display',
      'instance_settings' => array(
        'classes' => 'group-rfp field-group-htabs',
      ),
    ),
  );
  $export['group_rfp|node|rfp|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_supplier_diversity|node|organization|form';
  $field_group->group_name = 'group_supplier_diversity';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'organization';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_company_details';
  $field_group->data = array(
    'label' => 'Supplier Diversity',
    'weight' => '11',
    'children' => array(
      0 => 'field_diversity_credentials',
      1 => 'group_diversity_fields',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-supplier-diversity field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_supplier_diversity|node|organization|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_timeline_info|node|rfp|default';
  $field_group->group_name = 'group_timeline_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rfp';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rfp';
  $field_group->data = array(
    'label' => 'Timeline',
    'weight' => '2',
    'children' => array(
      0 => 'field_issued',
      1 => 'field_due',
      2 => 'field_expected_award',
      3 => 'field_expected_start',
      4 => 'field_expected_end',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-timeline-info field-group-fieldset',
      ),
    ),
  );
  $export['group_timeline_info|node|rfp|default'] = $field_group;

  return $export;
}
