<?php

/**
 * @file
 * REST API callback for m6connect_prochat module.
 */


/**
 * Menu callback for all of the APIs callback starts here.
 */
function app_rest_api_callbacks() {
  $output = array();
  $output = array(
    'success' => FALSE,
    'message' => t('User authentication failed.'),
  );

  // If no mode is received, then we do not know what to do, so producing an
  // error.
  if (empty($mode = $_REQUEST['mode'])) {
    $output['message'] = t('Bad request. Please try again!');
    drupal_json_output($output);
    drupal_exit();
  }

  // get private key list for application developer authentication
  $privateKey = getAppDevPrivateKey();
  if((!isset($_REQUEST['private_key'])) || (empty($_REQUEST['private_key'])) || (!in_array($_REQUEST['private_key'], $privateKey))){
    $output['message'] = t('Private key authentication failed');
    drupal_json_output($output);
    drupal_exit();
  }

  // If user is logging in, or registering or requesting for forgot password,
  // then we do not have user_id in such cased, so user authentication starts
  // after these three modes.
  if ($mode == 'user_login') {
    // Adding user authenticate file.
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_auth');
    if (function_exists('appuser_login')) {
      appuser_login();
    }
  }

  if ($mode == 'user_register') {
    // Adding user authenticate file.
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_auth');
    if (function_exists('appuser_register')) {
      appuser_register();
    }
  }

  if ($mode == 'forgot_password') {
    // Adding user authenticate file.
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_auth');
    if (function_exists('appuser_forgot_password')) {
      appuser_forgot_password();
    }
  }

  // User authentication.
  if (empty($_REQUEST['user_id'])) {
    drupal_json_output($output);
    drupal_exit();
  }

  if (!empty($_REQUEST['user_id']) && !user_load($_REQUEST['user_id'])) {
    $output['message'] = t('User not found in our database.');
    drupal_json_output($output);
    drupal_exit();
  }

  // Load current user.
  $account = user_load($_REQUEST['user_id']);

  $output['message'] = t('Desired operation can not be performed. Please contact Admin or try again later.');

  // get user accessable services  
  if ($mode == 'user_services_access_data') {    
    user_services_access_data();
  }
  // Act on adding status.
  if ($mode == 'app_status_add') {
    // Adding status file.
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_status_add')) {
      app_status_add();
    }
  }

  if ($mode == 'app_status_edit') {
    // Adding status file.
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_status_add')) {
      app_status_add();
    }
  }

  if ($mode == 'get_status_list') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('get_status_list')) {
      get_status_list();
    }
  }
  
  if ($mode == 'get_my_connections') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('get_connections_list')) {
      get_connections_list();
    }
  }     
  /**
   * Api for top menu starts
   */
  if ($mode == 'app_find_people') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_find_people')) {
      app_find_people();
    }
  }

  if ($mode == 'app_find_people_dropdown_value') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_find_people_dropdown_value')) {
      app_find_people_dropdown_value();
    }
  }

  if ($mode == 'app_find_people_get_my_connection') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_find_people_get_my_connection')) {
      app_find_people_get_my_connection();
    }
  }

  if ($mode == 'app_companies_data_list') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_companies_data_list')) {
      app_companies_data_list();
    }
  }

  if ($mode == 'app_update_company_flag_status') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_update_company_flag_status')) {
      app_update_company_flag_status();
    }
  }

  if ($mode == 'app_invite_to_m6') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_invite_to_m6')) {
      app_invite_to_m6();
    }
  }

  if ($mode == 'app_top_search_result') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('app_top_search_result')) {
      app_top_search_result();
    }
  }


  /**
   * End api for top menu
   */
  if ($mode == 'get_user_profile') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('user_profile_get')) {
      user_profile_get();
    }
  }
  
  if ($mode == 'user_profile_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('user_profile_data')) {
      user_profile_data();
    }
  }

  if ($mode == 'user_profile_about') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('user_profile_about')) {
      user_profile_about();
    }
  }

  if ($mode == 'user_profile_connection') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('user_profile_connection')) {
      user_profile_connection();
    }
  }

  if ($mode == 'user_profile_photo_tab_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('user_profile_photo_tab_data')) {
      user_profile_photo_tab_data();
    }
  }

  if ($mode == 'app_user_personal_profile_edit') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('app_user_personal_profile_edit')) {
      app_user_personal_profile_edit();
    }
  }

  if ($mode == 'app_user_personal_m6id_edit') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('app_user_personal_m6id_edit')) {
      app_user_personal_m6id_edit();
    }
  }

  if ($mode == 'app_user_personal_member_status') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('app_user_personal_member_status')) {
      app_user_personal_member_status();
    }
  }

  if ($mode == 'app_user_personal_companies') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('app_user_personal_companies')) {
      app_user_personal_companies();
    }
  }

  if ($mode == 'app_user_personal_opt_out_emails') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('app_user_personal_opt_out_emails')) {
      app_user_personal_opt_out_emails();
    }
  }

  if ($mode == 'app_user_personal_opt_out_emails_submit') {
    module_load_include('inc', 'm6connect_prochat', 'includes/user/user_profile');
    if (function_exists('app_user_personal_opt_out_emails_submit')) {
      app_user_personal_opt_out_emails_submit();
    }
  }

  if ($mode == 'save_comment') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('save_feed_comment')) {
      save_feed_comment();
    }
  }

  if ($mode == 'comment_list') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('get_all_comment')) {
      get_all_comment();
    }
  }

  if ($mode == 'edit_status') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('edit_status')) {
      edit_status();
    }
  }

  if ($mode == 'delete_status') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('delete_status')) {
      delete_status();
    }
  }

  if ($mode == 'bumpit_status') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('bumpit_status')) {
      bumpit_status();
    }
  }

  if ($mode == 'connection_spotlight') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('connection_spotlight')) {
      connection_spotlight();
    }
  }

  if ($mode == 'user_notification') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('user_notification')) {
      user_notification();
    }
  }
  /**
 * RFP Api Start
 */
 if ($mode == 'create_rfp_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/rfp/rfp');
    if (function_exists('create_rfp_data')) {
      create_rfp_data();
    }
  }

  if ($mode == 'save_create_rfp_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/rfp/rfp');
    if (function_exists('save_create_rfp_data')) {
      save_create_rfp_data();
    }
  }

  if ($mode == 'send_allrft_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/rfp/rfp');
    if (function_exists('send_allrft_data')) {
      send_allrft_data();
    }
  }

  if ($mode == 'send_single_rft_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/rfp/rfp');
    if (function_exists('send_single_rft_data')) {
      send_single_rft_data();
    }
  }


  /******* RFP Api End**********/

  /*
   * Project Api Start 
   */

  if ($mode == 'create_project_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('create_project_data')) {
      create_project_data();
    }
  }

  if ($mode == 'get_region_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('get_region_data_level')) {
      get_region_data_level();
    }
  }

  if ($mode == 'save_create_project_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('save_create_project_data')) {
      save_create_project_data();
    }
  }

  if ($mode == 'send_project_posting_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('send_project_posting_data')) {
      send_project_posting_data();
    }
  }
  // draft tab data api
  if ($mode == 'send_single_project_draft_summery_tab_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('send_single_project_draft_summery_tab_data')) {
      send_single_project_draft_summery_tab_data();
    }
  }

  if ($mode == 'send_single_project_draft_diversity_tab_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('send_single_project_draft_diversity_tab_data')) {
      send_single_project_draft_diversity_tab_data();
    }
  }

  if ($mode == 'send_single_project_draft_interested_companies_tab_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('send_single_project_draft_interested_companies_tab_data')) {
      send_single_project_draft_interested_companies_tab_data();
    }
  }

  if ($mode == 'send_single_project_draft_interested_bidders_tab_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('send_single_project_draft_interested_bidders_tab_data')) {
      send_single_project_draft_interested_bidders_tab_data();
    }
  }

  if ($mode == 'send_single_project_draft_rfp_tab_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('send_single_project_draft_rfp_tab_data')) {
      send_single_project_draft_rfp_tab_data();
    }
  }

  if($mode == 'get_texonomy_data_level'){
    module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
    if (function_exists('get_texonomy_data_level')) {
      get_texonomy_data_level();
    }  
  }

  /*
   * M6ID api starts
   */
  if($mode == 'm6id_invite_employee'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_invite_employee')) {
      m6id_invite_employee();
    }
  }

  if($mode == 'm6id_app_invite_new_employee_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_app_invite_new_employee_data')) {
      m6id_app_invite_new_employee_data();
    }
  }

  if($mode == 'm6id_app_invite_employee_delete'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_app_invite_employee_delete')) {
      m6id_app_invite_employee_delete();
    }
  }

  if($mode == 'm6id_app_invite_employee_form_submit'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_app_invite_employee_form_submit')) {
      m6id_app_invite_employee_form_submit();
    }
  }

  if($mode == 'm6id_employee_list'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_employee_list')) {
      m6id_employee_list();
    }
  }

  if($mode == 'm6id_manage_colleagues_status_update_api'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_manage_colleagues_status_update_api')) {
      m6id_manage_colleagues_status_update_api();
    }
  }

  if($mode == 'm6id_onboarding_inprocess_by_company'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_inprocess_by_company')) {
      m6id_onboarding_inprocess_by_company();
    }
  }

  if($mode == 'm6id_onboarding_inprocess_by_project'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_inprocess_by_project')) {
      m6id_onboarding_inprocess_by_project();
    }
  }

  if($mode == 'm6id_onboarding_project_invitation'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_project_invitation')) {
      m6id_onboarding_project_invitation();
    }
  }

  if($mode == 'm6id_onboarding_settings'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_settings')) {
      m6id_onboarding_settings();
    }
  }

  if($mode == 'm6id_onboarding_settings_add_new_employee_type'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_settings_add_new_employee_type')) {
      m6id_onboarding_settings_add_new_employee_type();
    }
  }

  if($mode == 'm6id_onboarding_settings_employee_type_delete'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_settings_employee_type_delete')) {
      m6id_onboarding_settings_employee_type_delete();
    }
  }

  if($mode == 'm6id_onboarding_invite_company_autosearch'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_invite_company_autosearch')) {
      m6id_onboarding_invite_company_autosearch();
    }
  }

  if($mode == 'm6id_onboarding_project_invitation_submit_employees_action'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_project_invitation_submit_employees_action')) {
      m6id_onboarding_project_invitation_submit_employees_action();
    }
  }

  if($mode == 'm6id_onboarding_project_invitation_submit_employees_action_submit'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_project_invitation_submit_employees_action_submit')) {
      m6id_onboarding_project_invitation_submit_employees_action_submit();
    }
  }

  if($mode == 'm6id_onboarding_project_invitation_reject_action'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_project_invitation_reject_action')) {
      m6id_onboarding_project_invitation_reject_action();
    }
  }

  if($mode == 'm6id_onboarding_project_invitation_invite_company_action'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_project_invitation_invite_company_action')) {
      m6id_onboarding_project_invitation_invite_company_action();
    }
  }

  if($mode == 'm6id_onboarding_project_invitation_project_open'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_project_invitation_project_open')) {
      m6id_onboarding_project_invitation_project_open();
    }
  }

  if($mode == 'app_node_delete'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('app_node_delete')) {
      app_node_delete();
    }
  }

  if($mode == 'm6id_onboarding_roster_by_company_action_status'){
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_roster_by_company_action_status')) {
      m6id_onboarding_roster_by_company_action_status();
    }
  }

  if($mode == 'm6id_onboarding_roster_by_company_action_view'){
    $output['message'] = 'Test';
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('m6id_onboarding_roster_by_company_action_view')) {
      m6id_onboarding_roster_by_company_action_view();
    }
  }

  if($mode == 'app_m6id_user_m6id_info'){
    $output['message'] = 'Test';
    module_load_include('inc', 'm6connect_prochat', 'includes/m6id/m6id');
    if (function_exists('app_m6id_user_m6id_info')) {
      app_m6id_user_m6id_info();
    }
  }

  /*
   * M6ID api ends
   */

  /*
   * Company api starts
   */

  if ($mode == 'user_company_for_login_left_block') {
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_company_for_login_left_block')) {
      user_company_for_login_left_block();
    }
  }

  if ($mode == 'switch_company') {
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('switch_company')) {
      switch_company();
    }
  }

  if ($mode == 'unsubscribe_company') {
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('unsubscribe_company')) {
      unsubscribe_company();
    }
  }
  
  if($mode == 'invite_company_send_invitation'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('invite_company_send_invitation')) {
      invite_company_send_invitation();
    }
  }

  if($mode == 'invite_company_resend_invitation'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('invite_company_resend_invitation')) {
      invite_company_resend_invitation();
    }  
  }

  if($mode == 'invite_company_later_invitation'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('invite_company_later_invitation')) {
      invite_company_later_invitation();
    }  
  }

  if($mode == 'invite_company_company_list'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('invite_company_company_list')) {
      invite_company_company_list();
    }  
  }

  if($mode == 'invite_company_company_search_form_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('invite_company_company_search_form_data')) {
      invite_company_company_search_form_data();
    }  
  }
  
  if($mode == 'm6connect_company_registration'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('m6connect_company_registration')) {
      m6connect_company_registration();
    }
  }

  if($mode == 'm6connect_app_get_company_listing'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('m6connect_app_get_company_listing')) {
      m6connect_app_get_company_listing();
    }
  }

  if($mode == 'company_profile_node_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_data')) {
      company_profile_node_data();
    }
  }

  if($mode == 'company_profile_node_news_feed_tab_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_news_feed_tab_data')) {
      company_profile_node_news_feed_tab_data();
    }
  }

  if($mode == 'company_profile_node_diversity_tab_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_diversity_tab_data')) {
      company_profile_node_diversity_tab_data();
    }
  }

  if($mode == 'company_profile_node_photo_tab_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_photo_tab_data')) {
      company_profile_node_photo_tab_data();
    }
  }

  if($mode == 'company_profile_node_summary_tab_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_summary_tab_data')) {
      company_profile_node_summary_tab_data();
    }
  }

  if($mode == 'company_profile_node_gpo_tab_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_gpo_tab_data')) {
      company_profile_node_gpo_tab_data();
    }
  }

  if($mode == 'company_profile_node_project_tab_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_project_tab_data')) {
      company_profile_node_project_tab_data();
    }
  }

  if($mode == 'company_profile_node_edit_public_profile'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_edit_public_profile')) {
      company_profile_node_edit_public_profile();
    }
  }

  if($mode == 'company_profile_node_edit_company_summary'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_edit_company_summary')) {
      company_profile_node_edit_company_summary();
    }
  }

  if($mode == 'company_profile_node_edit_location'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_node_edit_location')) {
      company_profile_node_edit_location();
    }
  }
  
  if($mode == 'company_profile_share_news_feed'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('company_profile_share_news_feed')) {
      company_profile_share_news_feed();
    }
  }

  if($mode == 'user_management_my_company_user'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_my_company_user')) {
      user_management_my_company_user();
    }
  }

  if($mode == 'user_management_pending_request'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_pending_request')) {
      user_management_pending_request();
    }
  }

  if($mode == 'user_management_invite_users'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_invite_users')) {
      user_management_invite_users();
    }
  }

  if($mode == 'user_management_invite_users_submit'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_invite_users_submit')) {
      user_management_invite_users_submit();
    }
  }

  if($mode == 'user_management_modify_user_role'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_modify_user_role')) {
      user_management_modify_user_role();
    }
  }

  if($mode == 'user_management_modify_user_role_submit'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_modify_user_role_submit')) {
      user_management_modify_user_role_submit();
    }
  }

  if($mode == 'user_management_update_admin_support_role'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_update_admin_support_role')) {
      user_management_update_admin_support_role();
    }
  }

  if($mode == 'user_management_manage_user_license_data'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_manage_user_license_data')) {
      user_management_manage_user_license_data();
    }
  }

  if($mode == 'user_management_manage_user_license_data_submit'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_manage_user_license_data_submit')) {
      user_management_manage_user_license_data_submit();
    }
  }

  if($mode == 'user_management_get_company_admin_list'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_get_company_admin_list')) {
      user_management_get_company_admin_list();
    }
  }

  if($mode == 'user_management_remove_user'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_remove_user')) {
      user_management_remove_user();
    }
  }

  if($mode == 'user_management_block_unblock_user'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_block_unblock_user')) {
      user_management_block_unblock_user();
    }
  }

  if($mode == 'user_management_accept_request'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_accept_request')) {
      user_management_accept_request();
    }
  }

  if($mode == 'user_management_deny_request'){
    module_load_include('inc', 'm6connect_prochat', 'includes/company/company');
    if (function_exists('user_management_deny_request')) {
      user_management_deny_request();
    }
  }

  /**
   * Api to create notification landing pages get data
   */
  if ($mode == 'user_notification_get_statuses_data') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('user_notification_get_statuses_data')) {
      user_notification_get_statuses_data();
    }
  }

  if ($mode == 'user_notification_edit_statuses_comment') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('user_notification_edit_statuses_comment')) {
      user_notification_edit_statuses_comment();
    }
  }

  if ($mode == 'user_notification_delete_statuses_comment') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('user_notification_delete_statuses_comment')) {
      user_notification_delete_statuses_comment();
    }
  }

  if ($mode == 'user_notification_add_new_statuses_comment') {
    module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');
    if (function_exists('user_notification_add_new_statuses_comment')) {
      user_notification_add_new_statuses_comment();
    }
  }



  drupal_json_output($output);
  drupal_exit();
}