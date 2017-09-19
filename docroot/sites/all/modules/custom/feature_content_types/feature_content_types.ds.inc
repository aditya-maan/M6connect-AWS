<?php
/**
 * @file
 * feature_content_types.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function feature_content_types_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|organization|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'organization';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'company_account' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'description' => array(
      'weight' => '17',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:22:"node:field_description";}',
        'load_terms' => 0,
      ),
    ),
    'ds_company_name2' => array(
      'weight' => '15',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:8:{s:4:"link";i:0;s:6:"markup";s:4:"none";s:2:"id";s:0:"";s:5:"class";s:0:"";s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:10:"node_title";s:7:"subtype";s:10:"node_title";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_address' => array(
      'weight' => '20',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:20:"addressfield_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:2:{s:19:"use_widget_handlers";i:1;s:15:"format_handlers";a:1:{s:7:"address";s:7:"address";}}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:22:"node:field_org_address";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_annual_revenue' => array(
      'weight' => '26',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:25:"node:field_annual_revenue";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_cage_code' => array(
      'weight' => '24',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:20:"node:field_cage_code";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_diversity_credentials' => array(
      'weight' => '1',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:21:"entityreference_label";s:11:"delta_limit";s:1:"0";s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";i:0;s:18:"formatter_settings";a:3:{s:4:"link";i:0;s:9:"view_mode";s:7:"default";s:5:"links";i:1;}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:32:"node:field_diversity_credentials";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_diversity_credential_list' => array(
      'weight' => '0',
      'label' => 'above',
      'format' => 'default',
    ),
    'ds_co_duns_number' => array(
      'weight' => '22',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:22:"node:field_duns_number";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_email' => array(
      'weight' => '23',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:13:"email_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:24:"node:field_company_email";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_fax' => array(
      'weight' => '25',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:5:"phone";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:18:"node:field_org_fax";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_incorporated_country' => array(
      'weight' => '34',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"list_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:31:"node:field_incorporated_country";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_incorporated_states' => array(
      'weight' => '33',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"list_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:29:"node:field_incorporated_state";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_industry_naics' => array(
      'weight' => '2',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:21:"ds_taxonomy_separator";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:4:{s:33:"taxonomy_term_reference_view_mode";s:4:"full";s:20:"use_content_language";i:1;s:18:"taxonomy_term_link";i:1;s:23:"taxonomy_term_separator";s:2:", ";}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:26:"node:field_industry_naicss";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_keywords' => array(
      'weight' => '32',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:19:"node:field_keywords";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_legal_name' => array(
      'weight' => '27',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:21:"node:field_legal_name";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_legal_structure' => array(
      'weight' => '28',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"list_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:26:"node:field_legal_structure";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_logo' => array(
      'weight' => '14',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:5:"image";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:2:{s:11:"image_style";s:9:"thumbnail";s:10:"image_link";s:0:"";}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:15:"node:field_logo";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_m6_company_types' => array(
      'weight' => '0',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:29:"taxonomy_term_reference_plain";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:3:{s:6:"linked";i:0;s:33:"taxonomy_term_reference_view_mode";s:4:"full";s:20:"use_content_language";i:1;}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:34:"node:field_facilities_construction";}',
        'load_terms' => 1,
      ),
    ),
    'ds_co_number_employees' => array(
      'weight' => '31',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:14:"number_integer";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:2:{s:18:"thousand_separator";s:1:" ";s:13:"prefix_suffix";i:1;}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:27:"node:field_number_employees";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_owner_name' => array(
      'weight' => '16',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:21:"node:field_owner_name";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_phone_number' => array(
      'weight' => '19',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:5:"phone";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:20:"node:field_org_phone";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_prod_services_unspsc' => array(
      'weight' => '3',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:29:"taxonomy_term_reference_plain";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:34:"node:field_products_service_unspsc";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_region' => array(
      'weight' => '1',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:29:"taxonomy_term_reference_plain";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:18:"node:field_regions";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_service_description' => array(
      'weight' => '18',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:12:"text_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:0:{}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:30:"node:field_service_description";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_taxpayer_ssn_ein2' => array(
      'weight' => '30',
      'label' => 'above',
      'format' => 'default',
    ),
    'ds_co_website' => array(
      'weight' => '21',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:11:"url_default";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:2:{s:11:"trim_length";s:2:"80";s:8:"nofollow";i:0;}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:18:"node:field_website";}',
        'load_terms' => 0,
      ),
    ),
    'ds_co_year_founded' => array(
      'weight' => '29',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:14:"number_integer";s:11:"delta_limit";i:0;s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";b:0;s:18:"formatter_settings";a:2:{s:18:"thousand_separator";s:1:" ";s:13:"prefix_suffix";i:1;}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:23:"node:field_year_founded";}',
        'load_terms' => 0,
      ),
    ),
    'locations_address' => array(
      'weight' => '0',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:10:{s:5:"label";s:6:"hidden";s:9:"formatter";s:20:"addressfield_default";s:11:"delta_limit";s:1:"0";s:12:"delta_offset";s:1:"0";s:14:"delta_reversed";i:0;s:18:"formatter_settings";a:2:{s:19:"use_widget_handlers";i:1;s:15:"format_handlers";a:1:{s:7:"address";s:7:"address";}}s:7:"context";s:25:"argument_entity_id:node_1";s:14:"override_title";i:0;s:19:"override_title_text";s:0:"";s:22:"override_title_heading";s:2:"h2";}s:4:"type";s:12:"entity_field";s:7:"subtype";s:22:"node:field_org_address";}',
        'load_terms' => 0,
      ),
    ),
    'members_of_company' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '3',
      'label' => 'above',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => '',
        'class' => '',
      ),
    ),
  );
  $export['node|organization|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|project|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'project';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'bidding_companies_list' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'interested_company_test' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'interested_flag_field' => array(
      'weight' => '5',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'invite_companies' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pro_diversity_help_text' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'pro_rfps_list' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|project|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|rfp|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'rfp';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'invite_companies' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rfp_clarifications_text' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'rfp_proposals_node_view' => array(
      'weight' => '18',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|rfp|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function feature_content_types_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'bidding_companies_list';
  $ds_field->label = 'Bidding companies list';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
global $user;
if($entity->uid == $user->uid) {
  $output = \'\';	
  $nid = $entity->nid;
  $node = node_load($nid);
  $items = field_get_items(\'node\', $node, \'field_pro_bidding_info\');
  $output .= \'<div class="Bidding-fc-list">\';
  foreach ($items as $item) {
	$fc = field_collection_field_get_entity($item); //pre($fc);  
	$itemid = $fc->item_id;
	$output .= \'<div class="form-group"><div class="row">\';
    $output .= \'<div class="col-md-3 col-sm-3 col-xs-12">\';	  
    $output .= \'<label>\'.t(\'Bid Name:\').\'</label>\';
    $output .= \'<div class="Cust-bidfc-data">\';
    $output .= (isset($fc->field_proj_bid_name[\'und\']))? $fc->field_proj_bid_name[\'und\'][0][\'value\']: \'\';
	$output .= \'</div>\';
    $output .= \'</div>\'; 
	
	$output .= \'<div class="col-md-3 col-sm-3 col-xs-12">\';	  
    $output .= \'<label>\'.t(\'Bid Date:\').\'</label>\';
    $output .= \'<div class="Cust-bidfc-data">\';
    $biddateval = (isset($fc->field_proj_bid_date[\'und\']))? $fc->field_proj_bid_date[\'und\'][0][\'value\']: \'\';
	$dtstmp = !empty($biddateval)? strtotime($biddateval): \'\';
	$output .= date("j F Y",$dtstmp);
	$output .= \'</div>\';
    $output .= \'</div>\';
	
	$output .= \'<div class="col-md-3 col-sm-3 col-xs-12">\';	  
    $output .= \'<label>\'.t(\'Start:\').\'</label>\';
    $output .= \'<div class="Cust-bidfc-data">\';
    $biddateval1 = (isset($fc->field_proj_start_date[\'und\']))? $fc->field_proj_start_date[\'und\'][0][\'value\']: \'\';
	$dtstmp1 = !empty($biddateval1)? strtotime($biddateval1): \'\';
	$output .= date("j F Y",$dtstmp1);
	$output .= \'</div>\';
    $output .= \'</div>\';
	
	$output .= \'<div class="col-md-3 col-sm-3 col-xs-12">\';	  
    $output .= \'<label>\'.t(\'Complete:\').\'</label>\';
    $output .= \'<div class="Cust-bidfc-data">\';
    $biddateval2 = (isset($fc->field_proj_complete_date[\'und\']))? $fc->field_proj_complete_date[\'und\'][0][\'value\']: \'\';
	$dtstmp2 = !empty($biddateval2)? strtotime($biddateval2): \'\';
	$output .= date("j F Y",$dtstmp2);
	$output .= \'</div>\';
    $output .= \'</div>\'; 
	
	$output .= \'</div>\'; // .row
	
	$output .= \'<div class="row">\';
	$output .= \'<div class="col-md-12 col-sm-12 col-xs-12">\';	  
    $output .= \'<label>\'.t(\'Bidding Companies:\').\'</label>\';
	$query2 = db_select(\'flagging\', \'f\')->fields(\'f\',array(\'uid\'))->condition(\'entity_id\', $itemid,\'=\');	
		$result2 = $query2->execute();
		while($record2 = $result2->fetchAssoc()) {
		  $uid = $record2[\'uid\'];	
		  $gids = get_user_company_nids($uid); //pre($gids);
		  if(!empty($gids)) {
            foreach($gids as $k => $v) {
			  $gnode = node_load($v);
			  $output .= \'<div class="bid-co-name">\'.$gnode->title.\'</div>\';  	
			}
		  }
		}
	
	$output .= \'</div>\';
	$output .= \'</div></div>\'; // .row .form-group
  }
  $output .= \'</div>\';
  
  echo $output;
}

?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['bidding_companies_list'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'company_account';
  $ds_field->label = 'Company account';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
  global $user;
  $nid = $entity->nid;
  $cnuid = $entity->uid;
  if($user->uid == $cnuid || array_key_exists(3, $user->roles)) {
    $node = node_load($nid);
    $created = $node->created;
    $cdate = date(\'d-m-Y\',$created);
    print \'<div class="com_createdon"><strong>Created on : </strong><span>\'.$cdate.\'</span></div>\';
  }
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['company_account'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'description';
  $ds_field->label = 'Description';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['description'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_address';
  $ds_field->label = 'Address';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_address'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_annual_revenue';
  $ds_field->label = 'Annual revenue';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_annual_revenue'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_cage_code';
  $ds_field->label = 'CAGE Code';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_cage_code'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_diversity_credential_list';
  $ds_field->label = 'Diversity credentials';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
get_node_credential_value($entity);
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['ds_co_diversity_credential_list'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_diversity_credentials';
  $ds_field->label = 'Diversity Credentials';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_diversity_credentials'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_duns_number';
  $ds_field->label = 'DUNS Number';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_duns_number'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_email';
  $ds_field->label = 'Email';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_email'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_fax';
  $ds_field->label = 'Fax';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_fax'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_incorporated_country';
  $ds_field->label = 'Incorporated Country';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_incorporated_country'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_incorporated_states';
  $ds_field->label = 'Incorporated State';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_incorporated_states'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_industry_naics';
  $ds_field->label = 'Industry NAICS';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_industry_naics'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_keywords';
  $ds_field->label = 'Keywords';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_keywords'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_legal_name';
  $ds_field->label = 'Legal Name';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_legal_name'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_legal_structure';
  $ds_field->label = 'Legal Structure';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_legal_structure'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_logo';
  $ds_field->label = 'Logo';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_logo'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_m6_company_types';
  $ds_field->label = 'M6 Company Types';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_m6_company_types'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_number_employees';
  $ds_field->label = 'Number employees';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_number_employees'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_owner_name';
  $ds_field->label = 'Owner name';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_owner_name'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_phone_number';
  $ds_field->label = 'Phone number';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_phone_number'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_prod_services_unspsc';
  $ds_field->label = 'Products & Services UNSPSC';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_prod_services_unspsc'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_region';
  $ds_field->label = 'Region';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_region'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_service_description';
  $ds_field->label = 'Service description';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_service_description'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_taxpayer_ssn_ein';
  $ds_field->label = 'Taxpayer SSN/EIN';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_taxpayer_ssn_ein'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_taxpayer_ssn_ein2';
  $ds_field->label = 'Taxpayer SSN/EIN';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
global $user;
if($user->uid == $entity->uid || array_key_exists(3, $user->roles)){
  if(isset($entity->field_taxpayer_ssn_ein[\'und\'])){
    echo $entity->field_taxpayer_ssn_ein[\'und\'][0][\'value\'];
  }
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['ds_co_taxpayer_ssn_ein2'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_website';
  $ds_field->label = 'Website';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_website'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_co_year_founded';
  $ds_field->label = 'Year founded';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_co_year_founded'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_company_name';
  $ds_field->label = 'Company Name';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
//pre($entity);
if(!empty($entity->title)){
  print $entity->title;
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['ds_company_name'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_company_name2';
  $ds_field->label = 'Company name';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_company_name2'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'ds_pro_bidding_co_list';
  $ds_field->label = 'Bidding companies list2';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['ds_pro_bidding_co_list'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'interested_company_test';
  $ds_field->label = 'interested company test';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
global $user;
$nid = $entity->nid;
$nuid = $entity->uid;

if($user->uid == $nuid || array_key_exists(3, $user->roles)) {
$query = db_select(\'flagging\', \'fl\');
$query->fields(\'fl\',array(\'uid\'));
$query->condition(\'fl.entity_id\', $nid);
$result = $query->execute();
while($record = $result->fetchAssoc()) {
  $userids[] = $record[\'uid\'];
} //pre($userids);
echo \'<div class="cust-diversity-interested-co">\';

foreach($userids as $k => $uid) {
  $cuser = user_load($uid);	
  $user_groups = og_get_groups_by_user($cuser, \'node\');	
  //pre($user_groups);
  foreach($user_groups as $n => $gnid) { 
	$gnode = node_load($gnid);
	echo  \'<div>\'.l($gnode->title, \'node/\'.$gnid).\'</div>\'; 
  }
}

echo \'</div>\';
}

?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['interested_company_test'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'interested_flag_field';
  $ds_field->label = 'Interested flag field';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
$nid = $entity->nid;
print flag_create_link(\'interested\', $nid); 
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['interested_flag_field'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'invite_companies';
  $ds_field->label = 'Invite Companies block';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'block' => 'm6connect_projects|my-project-search',
    'block_render' => '1',
  );
  $export['invite_companies'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'locations_address';
  $ds_field->label = 'Address';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['locations_address'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'members_of_company';
  $ds_field->label = 'members of company';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
  global $user;
  $cnid = $entity->nid;
  $cnuid = $entity->uid;
  if($user->uid == $cnuid || array_key_exists(3, $user->roles)) {
  $gnode = node_load($cnid);
  $gmlist = og_get_group_members_properties($gnode, array(), \'members__\' . OG_STATE_ACTIVE, \'node\');
  //$glist = og_get_group_members_properties(87, array(), \'members__1\', \'node\');	 //print_r($gmlist);
  print \'<div class="cust-group-member-list">\';
  foreach($gmlist as $var => $val) {
    $uid = $val;
    $usr = user_load($uid);//pre($usr);
    $fname = (!empty($usr->field_first_name) && isset($usr->field_first_name[\'und\'][0][\'value\']))?$usr->field_first_name[\'und\'][0][\'value\']:\'\';
     $mname = (!empty($usr->field_middle_name) && isset($usr->field_middle_name[\'und\'][0][\'value\']))?$usr->field_middle_name[\'und\'][0][\'value\']:\'\';
     $lname = (!empty($usr->field_last_name) && isset($usr->field_last_name[\'und\'][0][\'value\']))?$usr->field_last_name[\'und\'][0][\'value\']:\'\';
    $uname = $fname.\' \'.$mname.\' \'.$lname;
    print \'<div class="gm_name">\'.$uname.\'</div>\';
  }
  print \'</div>\';
  }
?>
',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['members_of_company'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'node_edit_link';
  $ds_field->label = 'node edit link';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
if(isset(arg(1)) && is_numeric(arg(1))) {
  $nid = arg(1);
  echo l(\'Edit\',\'node/\'.$nid.\'/edit\');
}
?>',
      'format' => 'php_code',
    ),
    'use_token' => 0,
  );
  $export['node_edit_link'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'pro_diversity_help_text';
  $ds_field->label = 'Diversity Suppliers ';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php 
echo "<strong>Seeking the following Diversity Supplier Types:</strong>";
//echo "Select all";
?>
<?php //<input type = "checkbox" value="All" name="diveditall"> ?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['pro_diversity_help_text'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'pro_rfps_list';
  $ds_field->label = 'RFPs list';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
$output = \'\';
$output .= \'<div class="rfp-associated-with-pro">\';
$nid = $entity->nid;
$query = db_select(\'node\', \'n\');
$query->join(\'field_data_field_project\',\'p\', \'p.entity_id = n.nid\');
$query->fields(\'p\',array(\'entity_id\'));
$query->condition(\'p.field_project_target_id\', $nid,\'=\');
$query->condition(\'n.status\', 1,\'=\');
$result = $query->execute();
while($record = $result->fetchAssoc()) {
  $rfpnid = $record[\'entity_id\'];	
  $rfpnode = node_load($rfpnid);
  $output .= \'<div class="rfp-asso-title">\'.l(t($rfpnode->title),\'node/\'.$rfpnid).\'</div>\';  	
}
$output .= \'</div>\';
echo $output;

?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['pro_rfps_list'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'rfp_clarifications_text';
  $ds_field->label = 'Rfp Clarifications text';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
  echo \'<div style="display:none;">Clarifications</div>\';
?>',
      'format' => 'php_code',
    ),
    'use_token' => 0,
  );
  $export['rfp_clarifications_text'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'rfp_proposals_node_view';
  $ds_field->label = 'RFP Proposals Node View';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
  $node = node_load($nid=31);
  $node_view = node_view($node);
  $rendered_node = drupal_render($node_view);
  echo $rendered_node;
?>',
      'format' => 'php_code',
    ),
    'use_token' => 0,
  );
  $export['rfp_proposals_node_view'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'view_by_permission';
  $ds_field->label = 'view by permission';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = '';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
echo "this is test";
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 1,
  );
  $export['view_by_permission'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function feature_content_types_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|organization|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'organization';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'locations_address',
        1 => 'ds_co_m6_company_types',
        2 => 'members_of_company',
        3 => 'ds_co_diversity_credential_list',
        4 => 'company_account',
        5 => 'group_company_details',
        6 => 'ds_co_diversity_credentials',
        7 => 'ds_co_region',
        8 => 'ds_co_industry_naics',
        9 => 'field_logo',
        10 => 'title',
        11 => 'ds_co_prod_services_unspsc',
        12 => 'field_owner_name',
        13 => 'field_description',
        14 => 'field_service_description',
        15 => 'field_org_phone',
        16 => 'field_org_address',
        17 => 'field_website',
        18 => 'ds_co_logo',
        19 => 'ds_company_name2',
        20 => 'ds_co_owner_name',
        21 => 'description',
        22 => 'ds_co_service_description',
        23 => 'ds_co_phone_number',
        24 => 'ds_co_address',
        25 => 'ds_co_website',
        26 => 'ds_co_duns_number',
        27 => 'ds_co_email',
        28 => 'ds_co_cage_code',
        29 => 'ds_co_fax',
        30 => 'ds_co_annual_revenue',
        31 => 'ds_co_legal_name',
        32 => 'ds_co_legal_structure',
        33 => 'ds_co_year_founded',
        34 => 'ds_co_taxpayer_ssn_ein2',
        35 => 'ds_co_number_employees',
        36 => 'ds_co_keywords',
        37 => 'ds_co_incorporated_states',
        38 => 'ds_co_incorporated_country',
        39 => 'group_company_details_tab',
        40 => 'group_co_summary_tab',
        41 => 'group_diversity_company_grp_tab',
        42 => 'group_co_locations',
        43 => 'group_co_classifications_tab',
        44 => 'group_co_user_tab',
        45 => 'group_co_account_tab',
      ),
    ),
    'fields' => array(
      'locations_address' => 'ds_content',
      'ds_co_m6_company_types' => 'ds_content',
      'members_of_company' => 'ds_content',
      'ds_co_diversity_credential_list' => 'ds_content',
      'company_account' => 'ds_content',
      'group_company_details' => 'ds_content',
      'ds_co_diversity_credentials' => 'ds_content',
      'ds_co_region' => 'ds_content',
      'ds_co_industry_naics' => 'ds_content',
      'field_logo' => 'ds_content',
      'title' => 'ds_content',
      'ds_co_prod_services_unspsc' => 'ds_content',
      'field_owner_name' => 'ds_content',
      'field_description' => 'ds_content',
      'field_service_description' => 'ds_content',
      'field_org_phone' => 'ds_content',
      'field_org_address' => 'ds_content',
      'field_website' => 'ds_content',
      'ds_co_logo' => 'ds_content',
      'ds_company_name2' => 'ds_content',
      'ds_co_owner_name' => 'ds_content',
      'description' => 'ds_content',
      'ds_co_service_description' => 'ds_content',
      'ds_co_phone_number' => 'ds_content',
      'ds_co_address' => 'ds_content',
      'ds_co_website' => 'ds_content',
      'ds_co_duns_number' => 'ds_content',
      'ds_co_email' => 'ds_content',
      'ds_co_cage_code' => 'ds_content',
      'ds_co_fax' => 'ds_content',
      'ds_co_annual_revenue' => 'ds_content',
      'ds_co_legal_name' => 'ds_content',
      'ds_co_legal_structure' => 'ds_content',
      'ds_co_year_founded' => 'ds_content',
      'ds_co_taxpayer_ssn_ein2' => 'ds_content',
      'ds_co_number_employees' => 'ds_content',
      'ds_co_keywords' => 'ds_content',
      'ds_co_incorporated_states' => 'ds_content',
      'ds_co_incorporated_country' => 'ds_content',
      'group_company_details_tab' => 'ds_content',
      'group_co_summary_tab' => 'ds_content',
      'group_diversity_company_grp_tab' => 'ds_content',
      'group_co_locations' => 'ds_content',
      'group_co_classifications_tab' => 'ds_content',
      'group_co_user_tab' => 'ds_content',
      'group_co_account_tab' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|organization|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|project|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'project';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'step_pro_summary',
        1 => 'step_pro_supplier_diversity',
        2 => 'step_pro_invite_companies',
        3 => 'field_project_diversity_type',
        4 => 'step_pro_interested_companies',
        5 => 'path',
        7 => 'field_interested_list_mrk',
        9 => 'field_interested_company_test_',
        10 => 'field_pro_invite_companies',
        11 => 'og_group_ref',
        12 => 'field_rfp_invite_comapnies',
        13 => 'field_project_public',
        14 => 'title',
        15 => 'field_status',
        16 => 'field_public_description',
        17 => 'field_complete_description',
        18 => 'field_pro_bidding_info',
        19 => 'field_images',
        20 => 'field_project_address_new',
        21 => 'field_project_address',
        22 => 'field_projects_keywords',
        24 => '_add_new_step',
      ),
      'hidden' => array(
        6 => 'additional_settings',
        8 => 'field_interested_company_list',
        23 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'step_pro_summary' => 'ds_content',
      'step_pro_supplier_diversity' => 'ds_content',
      'step_pro_invite_companies' => 'ds_content',
      'field_project_diversity_type' => 'ds_content',
      'step_pro_interested_companies' => 'ds_content',
      'path' => 'ds_content',
      'additional_settings' => 'hidden',
      'field_interested_list_mrk' => 'ds_content',
      'field_interested_company_list' => 'hidden',
      'field_interested_company_test_' => 'ds_content',
      'field_pro_invite_companies' => 'ds_content',
      'og_group_ref' => 'ds_content',
      'field_rfp_invite_comapnies' => 'ds_content',
      'field_project_public' => 'ds_content',
      'title' => 'ds_content',
      'field_status' => 'ds_content',
      'field_public_description' => 'ds_content',
      'field_complete_description' => 'ds_content',
      'field_pro_bidding_info' => 'ds_content',
      'field_images' => 'ds_content',
      'field_project_address_new' => 'ds_content',
      'field_project_address' => 'ds_content',
      'field_projects_keywords' => 'ds_content',
      '_add_existing_field' => 'hidden',
      '_add_new_step' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|project|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|project|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'project';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'invite_companies',
        1 => 'interested_company_test',
        2 => 'group_full_pdetails_grp',
        3 => 'pro_diversity_help_text',
        4 => 'pro_rfps_list',
        5 => 'field_project_diversity_type',
        6 => 'bidding_companies_list',
        7 => 'group_full_pdetails_grp_tab',
        8 => 'interested_flag_field',
        9 => 'group_full_diversity_grp_tab',
        10 => 'field_images',
        11 => 'group_full_int_comp',
        12 => 'og_group_ref',
        13 => 'group_full_invite_co',
        14 => 'field_project_address_new',
        15 => 'group_full_pro_bid_co',
        16 => 'field_project_address',
        17 => 'group_full_pro_rfps',
        18 => 'field_public_description',
        19 => 'field_status',
        20 => 'field_complete_description',
        21 => 'field_pro_bidding_info',
        22 => 'field_projects_keywords',
      ),
    ),
    'fields' => array(
      'invite_companies' => 'ds_content',
      'interested_company_test' => 'ds_content',
      'group_full_pdetails_grp' => 'ds_content',
      'pro_diversity_help_text' => 'ds_content',
      'pro_rfps_list' => 'ds_content',
      'field_project_diversity_type' => 'ds_content',
      'bidding_companies_list' => 'ds_content',
      'group_full_pdetails_grp_tab' => 'ds_content',
      'interested_flag_field' => 'ds_content',
      'group_full_diversity_grp_tab' => 'ds_content',
      'field_images' => 'ds_content',
      'group_full_int_comp' => 'ds_content',
      'og_group_ref' => 'ds_content',
      'group_full_invite_co' => 'ds_content',
      'field_project_address_new' => 'ds_content',
      'group_full_pro_bid_co' => 'ds_content',
      'field_project_address' => 'ds_content',
      'group_full_pro_rfps' => 'ds_content',
      'field_public_description' => 'ds_content',
      'field_status' => 'ds_content',
      'field_complete_description' => 'ds_content',
      'field_pro_bidding_info' => 'ds_content',
      'field_projects_keywords' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|project|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|rfp|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'rfp';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_rfp',
        1 => 'rfp_clarifications_text',
        2 => 'group_basic_info',
        3 => 'group_timeline_info',
        4 => 'invite_companies',
        5 => 'field_rfp_logo',
        6 => 'group_document_info',
        7 => 'field_rfp_name',
        8 => 'field_issued',
        9 => 'field_reference_number',
        10 => 'group_invited_companies',
        11 => 'field_due',
        12 => 'field_expected_award',
        13 => 'group_clarifications_info',
        14 => 'field_project_manager',
        15 => 'group_proposals_info',
        16 => 'field_project',
        17 => 'field_expected_start',
        18 => 'field_rfp_description',
        19 => 'field_expected_end',
        20 => 'field_new_project_name',
        21 => 'field_estimated_cost',
        22 => 'field_rfp_invite_new_pm',
        23 => 'rfp_proposals_node_view',
        24 => 'field_rfp_documents',
      ),
    ),
    'fields' => array(
      'group_rfp' => 'ds_content',
      'rfp_clarifications_text' => 'ds_content',
      'group_basic_info' => 'ds_content',
      'group_timeline_info' => 'ds_content',
      'invite_companies' => 'ds_content',
      'field_rfp_logo' => 'ds_content',
      'group_document_info' => 'ds_content',
      'field_rfp_name' => 'ds_content',
      'field_issued' => 'ds_content',
      'field_reference_number' => 'ds_content',
      'group_invited_companies' => 'ds_content',
      'field_due' => 'ds_content',
      'field_expected_award' => 'ds_content',
      'group_clarifications_info' => 'ds_content',
      'field_project_manager' => 'ds_content',
      'group_proposals_info' => 'ds_content',
      'field_project' => 'ds_content',
      'field_expected_start' => 'ds_content',
      'field_rfp_description' => 'ds_content',
      'field_expected_end' => 'ds_content',
      'field_new_project_name' => 'ds_content',
      'field_estimated_cost' => 'ds_content',
      'field_rfp_invite_new_pm' => 'ds_content',
      'rfp_proposals_node_view' => 'ds_content',
      'field_rfp_documents' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|rfp|default'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function feature_content_types_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'members_of_company';
  $ds_view_mode->label = 'members of company';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['members_of_company'] = $ds_view_mode;

  return $export;
}
