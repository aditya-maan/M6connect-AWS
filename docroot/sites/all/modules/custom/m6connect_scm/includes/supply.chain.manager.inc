<?php

/**
 * Start work for My request slide
 * generating My request form, my request data table to show all records.
 * it also contains the chat feature.  
 */
function scm_my_request_content(){
  global $company;
  $elements = array();
  $intranetClass = ''; 
  //print_r($_SESSION);
  if(isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $diplaysection = 'block';
    $intranetClass = 'intranet_user'; 
    $usersdb = get_scm_user_database_by_email($_SESSION['login-mail']);
    $company = node_load($usersdb->companyID);
    $elements['prgram-scm-user-menu-items'] = array(
      '#markup' => scm_user_menu_links_content(),
      '#prefix' => '<div class="clearfix"><div class="">',
      '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
    );
  }
  else {
    $diplaysection = 'none';
  }

  drupal_add_library('system', 'ui.autocomplete');
  drupal_add_library('system', 'ui.dialog');
  drupal_add_js('sites/all/libraries/emojione/emojionearea.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/messaging_socket.js');
  drupal_add_css('sites/all/libraries/emojione/emojionearea.min.css');
  drupal_add_js(drupal_get_path('module', 'm6connect_company') . '/js/' . 'm6messaging.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/m6connect_hcfm.js');


  if (empty($_SESSION['login-mail'])) {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_menu_links_content(),
      '#prefix' => '<div class="clearfix"><div class="pull-left form-inline scm-main-menu-short">',
      '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',
    );
  }

  $elements['scm-my-request-form']= array(
    '#markup' => drupal_render(drupal_get_form('scm_my_request_form')),
    '#prefix' => '<div class="white-bg ' . $intranetClass . '"><div class="relative row margin-10"><div class="main-scm-common-form col-md-12 padding-10">',
    '#suffix' => '</div>',
  );

  $elements['scm-chatting-container-right'] = array(
    '#markup' => drupal_render(scm_chatting_container()),
    '#prefix' => '<div class="scm_chatting_container-main col-md-7 padding-10" style="display:' . $diplaysection . ';">',
    '#suffix' => '</div></div>',
  );

  $elements['scm-form-search']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_scm_search_form')),
    '#prefix' => '<div class="scm-table-border"><div class="clearfix">',
    '#suffix' => '</div>',
  );

  $archive = arg(1) == 'archive' ? 1 : '';

  $elements['scm-my-request-listing'] = array(
    '#markup' => get_scm_my_request_table_data('', $archive),
    '#prefix' => '<div class="clearfix"><div class="scm-my-request-listing" id="scm-my-request-table">',
    '#suffix' => '</div></div></div></div>',
   );

  $elements['markup-popup'] = array(
    '#markup' => '<div id="conformboxpopup" style="display: none">
            <div class="ui-dialog-content ui-widget-content">
                <p>
                    <label id="lblMessage">
                    </label>
                </p>
            </div>
        </div>',
    '#prefix' => '<div id="conformboxpopup-section">',
    '#suffix' => '</div>',
  );

  return $elements;
}

function _casemanager_scm_search_form($form, &$form_state) {
  global $company;

  $pr_type='';

  if (arg(1) == 'my-request') {
      $pr_type = 'my-request';
  }
  else {
    $pr_type = 'archive';
  }

  $form['scm-form-search-form'] = array(
    '#type'          => 'textfield',
    //'#title'         => 'Search',
    '#attributes'    => array('class' => array('form-control', 'project-form-search-form'), 'id' =>'myInput', 'placeholder' => 'Search'),
    '#prefix'        => '<div class="clearfix well-sp well-large"><div class="form-item col-sm-6 clearfix">',
    '#suffix'        => '</div></div>',
  );

  return $form;
}

function scm_user_menu_links_content() {
  $usersdb = get_scm_user_database_by_email($_SESSION['login-mail']);

  if(!empty($usersdb->fristname)){
    $usename = $usersdb->fristname.' '.$usersdb->lastname;
  }

  $html = '<div class="region-top-header requesterdata_outer-login"><div class="box box-with-image"><div class="box-header-main box-header"><div class="box-image-wrapper"> <a href="#"> <img src="/sites/all/themes/m6connect/images/icon-detective.png"></a></div><div class="box-right-entity"><div class="row"><div class="col-md-8 col-sm-6 col-xs-12"><h1>Requester - '.ucwords($usename).'</h1></div><div class="col-md-4 col-sm-6 col-xs-12 box-actions text-right">';
  $html .= '<a href="#" title="New Request" class="new-record-requester new-record-link" dataaction="triggercall"><i class="glyphicon glyphicon-plus"></i> New Request</a>';
  $html .= '<span><a href="javascript:void(0)" title="Log Out" class="m6top-logout-user-forrequester-link"><i class="fa fa-power-off"></i> Log Out</a></span></div></div></div></div></div></div>';

  return $html;
}

function change_checktrigger_callback($form,&$form_state) {
  $commands = array();
  $myReqNode = node_load($form_state['values']['get-my-requests']);

  $commands[] = ajax_command_invoke("select.scm-my-request-request-subtype", 'val',array($myReqNode->field_request_subtype['und'][0]['value']));

  $commands[] = ajax_command_invoke("select.scm-my-request-sub-category", 'trigger',array('change'));

  return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_my_request_form($form, &$form_state) {
  global $user, $company;

  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');

  // Setting Defaults.
  $form_state['triggered_direct_purchase'] = FALSE;
  $form_state['default_subtype_valdata'] = '';

  $diplaysection = 'none';
  $for = 'closed';
  if (isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $diplaysection = 'block';
    $for = 'open';
  }

  if (!empty($form_state['triggering_element']['#title']) && $form_state['triggering_element']['#title'] == 'Direct Purchase Only') {
    $form_state['triggered_direct_purchase'] = TRUE;
  }

  if (!isset($form_state['add_small_items_storage'])) {
    $tempIdentifer = uniqid();
    $form_state['add_small_items_storage'][]  = $tempIdentifer;
  }

  if (!isset($form_state['sub_category_fetch_options'])) {
    $form_state['sub_category_fetch_options']  = array();
  }

  if (!isset($form_state['sub_type_request_fetch_options'])) {
    $form_state['sub_type_request_fetch_options']  = array();
  }

  if (!isset($form_state['supply_chain_lead_fetch_options'])) {
    $form_state['supply_chain_lead_fetch_options']  = array();
  }

  $form['#attributes']['class'] = array('scm_my_request_form');
  $getReqNodes = _getting_table_data_call_request('scm_requests');

  $form_state['frozen_defaults']['style_justification'] = 'display:none;';
  $form_state['frozen_defaults']['justification_required'] = FALSE;

  // Handling Ajax Triggers.

  // Entity Change.
  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#name'] == 'scm-my-request-entity') {
    // Unsetting any previous inputs.
    unset($form_state['input']['scm-my-request-material-manager'], $form_state['values']['scm-my-request-material-manager']);

    if (isset($form_state['default_values']['main_container'])) {
      unset($form_state['default_values']['main_container']);
    }

    // Trying to get material manager for requested entities.
    if ($form_state['triggering_element']['#value']['all'] == 'all') {
      $entities = _getting_table_data_call('scm_setting_location_entity');
    }
    else {
      $entities = $form_state['triggering_element']['#value'];
    }

    foreach ($entities as $k => $v) {
      $entityload = node_load($k);
      if (!empty($entityload->field_entity_materials_manager['und'][0]['value'])) {
        // If we have material managers at least.
        $material_manageruids = explode('|', $entityload->field_entity_materials_manager['und'][0]['value']);

        foreach ($material_manageruids as $key => $value){
          $account = user_load($value);
          if(_is_user_material_manager(FALSE, $account)) {
            $material_managernames[] = _get_user_full_name($account->uid, $account);
          }
        }

        if (!empty($material_managernames)) {
          $materials_user_names = implode(', ', $material_managernames);
          $form_state['default_values']['main_container']['material-manager'] = $materials_user_names;
        }
      }
    }
  }

  // Request Priority Level.
  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#name']=='scm-my-request-priority-level') {
    if ($form_state['triggering_element']['#value'] == 'critical') {
      $form_state['frozen_defaults']['justification_required'] = TRUE;
      $form_state['frozen_defaults']['style_justification'] = 'display:block;'; 
    }
    else {
      $form_state['frozen_defaults']['justification_required'] = FALSE;
      $form_state['frozen_defaults']['style_justification'] = 'display:block;';
    }
  }

  // Edit a request.
  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#name'] == 'get-my-requests') {
    if (!empty($form_state['triggering_element']['#name'])) {
      // If we have a value then proceeding further.
      $diplaysection = 'block';
      $for = 'open';
      _edit_my_request_callback_prepare($form_state);
    }
    else {
      // Reset the form.
      unset($_SESSION['scr_request']);
      $form_state['add_small_items_storage']  = array(uniqid());
      $form_state['sub_category_fetch_options']  = array();
      $form_state['sub_type_request_fetch_options']  = array();
      $form_state['supply_chain_lead_fetch_options']  = array();
      $form_state['frozen_defaults']['style_justification'] = 'display:none;';
      $form_state['frozen_defaults']['justification_required'] = FALSE;

      $form_state['input'] = array();
      $form_state['values'] = array();
    }
  }

  // Reset the form.
  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#name'] == 'reset-callback') {
    unset($_SESSION['scr_request']);
    $form_state['add_small_items_storage']  = array(uniqid());
    $form_state['sub_category_fetch_options']  = array();
    $form_state['sub_type_request_fetch_options']  = array();
    $form_state['supply_chain_lead_fetch_options']  = array();
    $form_state['frozen_defaults']['style_justification'] = 'display:none;';
    $form_state['frozen_defaults']['justification_required'] = FALSE;

    $form_state['input'] = array();
    $form_state['values'] = array();
  }

  // Request Type.
  if ($form_state['triggering_element']['#name']=='scm-my-request-request-type') {
    $requesttypeid = str_replace("-","",$form_state['values']['scm-my-request-request-type']);
    if (strpos($form_state['values']['scm-my-request-request-type'], '-1') !== false) {

      $requesttypeid = str_replace("-1","",$form_state['values']['scm-my-request-request-type']);
    }
    if (!empty(_get_request_sub_type_from_settings_by_typebymailcat($requesttypeid))) {
      $form_state['sub_type_request_fetch_options'] = _get_request_sub_type_from_settings_by_typebymailcat($requesttypeid);
    }
    else {
      //$form_state['sub_type_request_fetch_options'] = array('00'=>'None');
      $form_state['default_subtype_valdata'] = 00;
    }
  }

  // Request Category.
  if ($form_state['triggering_element']['#name'] =='scm-my-request-category') {
    $form_state['default_sub_val'] = '';
    if (!empty($form_state['values']['my-request-node-nid'])) {
      // Getting sub category if any.
      $node_load = node_load($form_state['values']['my-request-node-nid']);
      $form_state['default_sub_val'] = !empty($node_load->field_sub_category['und'][0]['value']) ? $node_load->field_sub_category['und'][0]['value'] : '';
    }

    $main_cat_scl = _get_main_cat_scl($form_state['triggering_element']['#value']);
    $form_state['supply_chain_lead_fetch_options'] = $main_cat_scl;

    $sub_categories_all = _get_all_sub_categories_scm_keyed($form_state['triggering_element']['#value']);
    $form_state['sub_category_fetch_options'] = $sub_categories_all;
  }

  // Sub category. (If SCL of sub is different then main.)
  if ($form_state['triggering_element']['#name'] == 'scm-my-request-sub-category') {
    $main_cat_scl = _get_main_cat_scl($form_state['triggering_element']['#value']);
    $form_state['supply_chain_lead_fetch_options'] = $main_cat_scl;
  }

  // Requester Search.
  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#name'] == 'scm-my-request-requester-ref' && !empty($form_state['triggering_element']['#value'])) {
    // Unsetting the numeric id of the user.
    unset($form_state['input']['scm-my-request-requester-ref'], $form_state['values']['scm-my-request-requester-ref']);
    if (isset($form_state['default_values']['main_container'])) {
      // If the request was edited, then we might have data in this variable,
      // so if we do not clear this variable, it might override changes user
      // did post editing.
      unset($form_state['default_values']['main_container']);
    }

    $user_details = get_scm_user_database_data($form_state['triggering_element']['#value']);

    if (!empty($user_details)) {
      $storage_project = array();
      $storage_project['requester-db-ref'] = $user_details->id;
      $storage_project['requester-first-name'] = $user_details->fristname;
      $storage_project['requester-last-name'] = $user_details->lastname;
      $storage_project['requester-email'] = $user_details->email;

      $form_state['default_values']['main_container'] = $storage_project;
    }
  }

  // Manufacturer and Vendor Triggers.
  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#array_parents'][2] == 'scm-request-request') {
    $cnid = _get_nid_by_title($form_state['triggering_element']['#value']);

    if (isset($form_state['default_values']['main_containerupper_trigger'])) {
      unset($form_state['default_values']['main_containerupper_trigger']);
    }

    $form_state['default_values']['main_containerupper_trigger'] = array();

    if (!empty($cnid) && $cnode = node_load($cnid)) {
      // Getting the desired fields to be changed.
      $all_fields = _get_allField_scm_settings_matadetails();

      // Trying to know which one is triggered, Manufacturer or Vendor.
      $triggered_split = explode('scm-request-', $form_state['triggering_element']['#array_parents'][4]);
      $triggered = $triggered_split[1];

      $triggered_specific = explode('_', $triggered);
      $triggered_specific = $triggered_specific[0];
      if (isset($form_state['input']['Allfieldsdata'][$triggered_specific])) {
        unset($form_state['input']['Allfieldsdata'][$triggered_specific]);
        unset($form_state['values']['Allfieldsdata'][$triggered_specific]);
      }

      foreach ($all_fields as $val) {
        if ($val->scm_group_key == $triggered && !empty($val->fieldsdata)) {
          $triggered_elements = $val->fieldsdata;
          break;
        }
      }

      if (!empty($triggered_elements)) {
        // If we are here, then we need to collect the default values of the
        // fields.
        // The order is as follows.
        // 1. Company Name.
        // 2. Contact Name.
        // 3. Contact Email.
        // 4. Contact Phone.
        // 5. Contract Number.

        // For Manufacturer there are five elements, whereas for vendor there
        // are six, first one is for a checkbox, so we shall skip that.
        $i = count($triggered_elements) == 6 ? 1 : 0;

        // Company Name.
        $form_state['default_values']['main_containerupper_trigger'][$triggered_elements[$i]->id] = $cnode->title;

        // Unsetting NID.
        if (isset($form_state['input']['scm_request_field_' . $triggered_elements[$i]->id . '_nid'])) {
          unset($form_state['input']['scm_request_field_' . $triggered_elements[$i]->id . '_nid']);
          unset($form_state['values']['scm_request_field_' . $triggered_elements[$i]->id . '_nid']);
        }

        // Contact Name.
        $i++;
        $form_state['default_values']['main_containerupper_trigger'][$triggered_elements[$i]->id] = !empty($cnode->field_owner_name[LANGUAGE_NONE][0]['value']) ? $cnode->field_owner_name[LANGUAGE_NONE][0]['value'] : '';

        // Contact Email.
        $i++;
        $form_state['default_values']['main_containerupper_trigger'][$triggered_elements[$i]->id] = !empty($cnode->field_company_email[LANGUAGE_NONE][0]['email']) ? $cnode->field_company_email[LANGUAGE_NONE][0]['email'] : '';

        // Contact Phone.
        $i++;
        $form_state['default_values']['main_containerupper_trigger'][$triggered_elements[$i]->id] = !empty($cnode->field_org_phone[LANGUAGE_NONE][0]['value']) ? $cnode->field_org_phone[LANGUAGE_NONE][0]['value'] : '';

        // Contract Number.
        $i++;
        $form_state['default_values']['main_containerupper_trigger'][$triggered_elements[$i]->id] = !empty($cnode->field_contract_number[LANGUAGE_NONE][0]['value']) ? $cnode->field_contract_number[LANGUAGE_NONE][0]['value'] : '';
      }
    }
  }

  // Start Building Form.
  if (isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $usersdb_val = get_scm_user_database_by_email($_SESSION['login-mail']);
    $company = node_load($usersdb->companyID);

    $rdbref = get_node_byfield_value('field_requestordb_ref', 'scm_requests', $usersdb_val->id, 1);
    if (!empty($rdbref) && in_array($rdbref, array_keys($getReqNodes))) {
      $form['userdb-base-request'] = array(
        '#type'          => 'textfield',
        '#attributes'    => array('class' => array('form-control','userdb-base-request')),
        '#default_value' => $rdbref,
        '#prefix'        => '<div style="display:none;">',
        '#suffix'        => '</div>',
      );
    }

    $form['userdb-base-requestID'] = array(
        '#type'          => 'hidden',
        '#attributes'    => array('class' => array('form-control','userdb-base-requestID')),
        '#default_value' => 'dbuser',
        '#prefix'        => '<div style="display:none;">',
        '#suffix'        => '</div>',
      );
  }

  $form['logout-callback'] = array(
    '#type'       => 'select',
    '#options'    => array(0 => 0, 1 => 1),
    '#attributes' => array('class'=> array('form-control','logout-callback')),
    '#prefix'     => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix'     => '</div></div>',
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_logout_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
  );

  if (!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
    $form['check-triggers'] = array(
      '#type'       => 'select',
      '#options'    => array(0=>0,1=>1),
      '#attributes' => array('class'=> array('form-control','check-triggers')),
      '#prefix'     => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
      '#suffix'     => '</div></div>',
      '#ajax' => array(
        'callback'=> 'change_checktrigger_callback',
        'wrapper' => 'program_scm_main_container',
        'effect' => 'fade',
      ),
    );
  }

  if (arg(1)!='archive') {
    $form['reset-callback'] = array(
      '#type'       => 'select',
      '#options'    => array(0=>0),
      '#attributes' => array('class'=> array('form-control','reset-callback')),
      '#prefix'     => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
      '#suffix'     => '</div></div>',
      '#ajax' => array(
        'callback'=> 'change_scm_my_request_project_callback',
        'wrapper' => 'scr-request-outer-container',
        'effect' => 'fade',
      ),
    );
  }

  $form['get-my-requests'] = array(
    '#type'       => 'select',
    '#options'    => $getReqNodes,
    '#attributes' => array('class'=> array('form-control get-my-requests')),
    '#prefix'     => '<div class="clearfix" style="display:none;">',
    '#suffix'     => '</div>',
    '#ajax' => array(
      'callback' => 'change_scm_my_request_project_callback',
      'wrapper'  => 'scr-request-outer-container',
      'effect'   => 'fade',
    ),
  );

  $form['outer-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="scr-request-outer-container">',
    '#suffix' => '</div>',
  );

  $form['outer-container']['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')), 
    '#prefix' => '<div class="clearfix"><div id="program_scm_main_container" class="project-detail" style="display:'.$diplaysection.';" for="'.$for.'">',
    //'#suffix' => '</div></div>', 
    '#process' => array('project_scm_my_request_container_process'),
  );

  $form['outer-container']['main_containerupper'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('alert-container-section1')),
    '#prefix' => '<div class="clearfix" id="main-class"><div id="alert-container-section1" class="add-new-alert-detail1" style="display:none;" for="closed">',
    '#suffix' => '</div></div>',
    '#process' => array('extrafield_invite_to_m6_process'),
  );

  $form['outer-container']['main_container2'] = array(
    '#type' => 'container',
    '#theme' => 'add_item_invite_m6_theme',
    '#attributes' => array('class'=>array('alert-container-section')),
    '#prefix' => '<div class="clearfix" id="main-class"><div id="alert-container-section" class="add-new-alert-detail" style="display:none;" for="closed">', 
    '#suffix' => '</div></div></div></div>',
    '#process' => array('add_item_invite_to_m6_process'),
  );

  if (arg(1)!='archive') {
    $form['outer-container']['action']['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Save',
      '#validate' => array('project_scm_my_request_validate'),
      '#submit' => array('project_scm_my_request_submit'),
      '#attributes' => array('class'=>array('scm-my-submit-custom-btn')),
      '#prefix' => '<div class="custom-action-button-div12 margin-bottom-10">',
    );
    $form['outer-container']['action']['cancel'] = array(
      '#type' => 'markup',
      '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
      '#suffix' => '</div>',
    );
  }

  $form['areusure'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="dialogss" style="display: none">
            <p>
                <label id="lblMessage1">
                </label>
            </p>
            </div>',
    '#prefix' => '<div class="custom-action-button-divares margin-bottom-10" style="display:none">',
    '#suffix' => '</div>',
  );

  if (!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
    $form['scm-show_all_requests_from_all_users'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show All Requests From All Users'),
      '#default_value' => 0,
      '#options' => array(0,1),
      '#ajax' => array(
        'callback'=> 'show_all_requests_from_all_users_callback',
        'wrapper' => 'scm-my-request-table',
        'effect' => 'fade',
      ),
      '#attributes' => array('class'=>array('scm-show_all_requests_from_all_users')),
      '#prefix' => '<div class="scm-show_all_requests_from_all_usersout"><div class="pull-right">',
      '#suffix' => '</div></div>',
    );
    if(variable_get('setallreq_for__'.$company->nid.'__user__'.$user->uid)=='set'){
      $form['scm-show_all_requests_from_all_users']['#default_value']= 1;
    }
  }

  // Button to trigger chatting screens after editing a request.
  $form['trigger-chat'] = array(
    '#type' => 'button',
    '#value' => t('Trigger Chat'),
    '#name' => 'trigger-chat',
    '#ajax' => array(
      'callback' => 'trigger_chat_scm_request',
      'wrapper' => 'program_scm_main_container',
    ),
    '#attributes' => array('class' => array('trigger-chat-here')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );

  return $form;
}

function trigger_chat_scm_request($form, &$form_state) {
  $commands[] = ajax_command_html('.scm_chatting_container-main', render(scm_chatting_container()));
  $commands[] = ajax_command_invoke('.scm_chatting_container-main','show');
  $commands[] = array('command' => 'emojinetexteditorscm');

  return array('#type' => 'ajax', '#commands' => $commands);
}

function show_all_requests_from_all_users_callback($form,&$form_state) {
  global $user, $company;
  $commands[] = '';

  if ($form_state['triggering_element']['#name']=='scm-show_all_requests_from_all_users') {
    if ($form_state['triggering_element']['#value'] == 1) {
      variable_set('setallreq_for__'.$company->nid.'__user__'.$user->uid, 'set');
      $commands[] = ajax_command_invoke("#scm-my-request-table", get_scm_my_request_table_data('',1));
    }
    else {
      variable_set('setallreq_for__'.$company->nid.'__user__'.$user->uid, '');
      $commands[] = ajax_command_invoke("#scm-my-request-table", get_scm_my_request_table_data('',0));
    }
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_my_request_logout_callback($form,&$form_state) {
  unset($_SESSION['login-mail']);
  $commands[] = '';
  $commands[] = ctools_ajax_command_redirect('scm/user-request-login', 0, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_my_request_project_callback($form,&$form_state) {
  return $form['outer-container'];

  /*if ($form_state['triggering_element']['#name']=='get-my-requests') {
    if (!empty($triggeringElement['#value'])) {

      $commands[] = ajax_command_invoke('.attachmentshtmlouterclass', 'addClass', array('thumbnail'));
      $commands[] = ajax_command_html("#scm-upload-filelist", '<div class="image-preview">'.implode('', $attachmentshtml).'</div>');
      $commands[] = ajax_command_html(".filelist-outer", '');
      $commands[] = ajax_command_invoke('#scm-upload-filelist', 'show'); 
      $requestDate = $storage_project['request-date']!=''?date('m/d/Y', $myReqNode->created):'';
      $effective_date = $storage_project['effective_date']!=''?date('m/d/Y', strtotime($storage_project['effective_date'])):'';
      $closeout_date = $storage_project['closeout_date']!=''?date('m/d/Y', strtotime($storage_project['closeout_date'])):'';
      $commands[] = ajax_command_invoke("input.my-request-node-nid", 'val',array($myReqNode->nid));
      $commands[] = ajax_command_invoke("input.scr-number", 'val',array($storage_project['scr-number']));
      $commands[] = ajax_command_invoke("input.request-date", 'val',array($requestDate)); 
      $commands[] = ajax_command_invoke("input.effective_date", 'val',array($effective_date));
      $commands[] = ajax_command_invoke("select.scm-my-request-entity", 'val',array(explode(', ',$storage_project['entity'])));
      $commands[] = ajax_command_invoke("select.scm-my-request-entity", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("select.scm-my-request-category", 'val',array($storage_project['category']));
      $commands[] = ajax_command_invoke("select.scm-my-request-category", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("select.scm-my-request-sub-category", 'val',array($storage_project['sub-category']));
      $commands[] = ajax_command_invoke("select.scm-my-request-sub-category", 'trigger',array('change'));

      $usernames = array();
      $commands[] = ajax_command_invoke("input.scm-my-request-supply-chain-lead", 'val',array(implode(', ', $usernames)));
      $commands[] = ajax_command_invoke("select.scm-my-request-department", 'val',array($storage_project['department']));
      $commands[] = ajax_command_invoke("textarea.scm-my-request-description", 'val',array($storage_project['description']));
      $commands[] = ajax_command_invoke("input.scm-department-approver", 'val',array($storage_project['department-approver']));
      $commands[] = ajax_command_invoke("select.scm-my-request-department", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.scm-approver-email", 'val',array($storage_project['approver-email']));
      $commands[] = ajax_command_invoke("select.scm-my-request-request-type", 'val',array($storage_project['request-type']));
      $commands[] = ajax_command_invoke("select.scm-my-request-request-type", 'trigger',array('change'));   
      $commands[] = ajax_command_invoke("select.scm-my-request-request-subtype", 'val',array($storage_project['request-subtype']));   
      $commands[] = ajax_command_invoke("select.scm-my-request-priority-level", 'val',array($storage_project['priority-level']));
      
      $commands[] = ajax_command_invoke("input.scm-my-request-priority-frozen-field",'val',array($storage_project['priority-frozen'])); 
      $commands[] = ajax_command_invoke("select.scm-my-request-priority-level", 'trigger',array('change'));

      $commands[] = ajax_command_invoke("select.check-triggers", 'trigger',array('change'));
      
      
      if(!empty($storage_project['priority-level'])){
        $commands[] = ajax_command_invoke('.form-itemfieldpop','show');
      }
      $commands[] = ajax_command_invoke("input.scm-my-request-supply-chain-lead-id", 'val',array($storage_project['supply-chain-lead']));
      $commands[] = ajax_command_invoke("input.scm-my-request-material-manager-id", 'val',array($storage_project['material-manager']));
      $commands[] = ajax_command_invoke("select.scm-my-request-project-status", 'val',array($storage_project['project-status']));
      if(!empty($myReqNode->field_requestordb_ref['und'])){
        $query = db_select('m6connect_scm_settings_user_database', 'n');
        $query->fields('n');
        $query->condition('n.UUID', $myReqNode->field_requestordb_ref['und'][0]['value'], '=');
        $result = $query->execute()->fetchObject();
         $commands[] = ajax_command_invoke("input.scm-my-request-requesterIDhidden", 'val',array($myReqNode->field_requestordb_ref['und'][0]['value']));
        $commands[] = ajax_command_invoke("input.scm-my-request-requester-ref", 'val',array($result->fristname. ' ' .$result->lastname));
        $commands[] = ajax_command_invoke("input.scm-my-request-requester-first-name", 'val',array($result->fristname));
        $commands[] = ajax_command_invoke("input.scm-my-request-requester-last-name", 'val',array($result->lastname));
      }
      $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-fn", 'val',array($storage_project['on-behalf-fn']));
      $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-ln", 'val',array($storage_project['on-behalf-ln']));
      $commands[] = ajax_command_invoke("input.closeout_date", 'val',array($closeout_date));
      $commands[] = ajax_command_invoke("textarea.scm-my-request-closeoutremarks", 'val',array($storage_project['scm-my-request-closeoutremarks']));
      if(!empty($storage_project['sub-category'])) {
        drupal_add_js(array('m6connect_scm' => array('getSubCategory' => $storage_project['sub-category'])), array('type' => 'setting'));
      }
      $resultsfld = get_all_custom_fieldsBY_reqestID($myReqNode->nid);
      foreach($resultsfld as $key => $value) {
        $subquery= db_select('m6connect_scm_settings_mata_field', 'n');
        $subquery->fields('n');
        $subquery->condition('n.id', $value->fieldID, '=');
        $resultflddata = $subquery->execute()->fetchObject();
        if($resultflddata->type == 'select') {
          $fldtype = 'select';
          $commands[] = ajax_command_invoke($fldtype.".scm_request_field_".$value->fieldID, 'val',array($value->value));
        }
        if($resultflddata->type == 'textfield' || $resultflddata->type =='checkbox') {
          $fldtype = 'input';
          $commands[] = ajax_command_invoke($fldtype.".scm_request_field_".$value->fieldID, 'val',array($value->value));
        }
        if($resultflddata->type == 'textarea') {
          $fldtype = 'textarea';
          $commands[] = ajax_command_invoke($fldtype.".scm_request_field_".$value->fieldID, 'val',array($value->value));
        }
        if ($resultflddata->type == 'checkbox' && $value->value == 1) {
          $commands[] = ajax_command_invoke($fldtype.".scm_request_field_".$value->fieldID, 'prop',array('checked', true));
        }
        if($resultflddata->type == 'company') {
          if ($node = node_load($value->value)) {
            $commands[] = ajax_command_invoke("input.scm_request_field_".$value->fieldID, 'val',array($node->title));
            $commands[] = ajax_command_invoke("input.scm_request_field_".$value->fieldID."_nid", 'val',array($node->nid));
          }
        }
      }
      if($myReqNode->status==0) {
        $archive = 1;
      }
      $commands[] = ajax_command_html("#scm-my-request-table", get_scm_my_request_table_data($archive));
      $commands[] = ajax_command_replace("#alert-container-section", render($form['main_container2']));
      $commands[] = ajax_command_html('.scm_chatting_container-main', render(scm_chatting_container()));
      $commands[] = ajax_command_invoke('.scm_chatting_container-main','show');
      $commands[] = array('command' => 'emojinetexteditorscm');
    }
  } 
  else {
    $commands[] = ajax_command_invoke("input.my-request-node-nid", 'val',array(''));
    $currentYear = date('Y');
    $myCounter = variable_get('SCRNumber');
    $makeSr = str_pad($myCounter, 6, "0", STR_PAD_LEFT);  
    $scrNumber = 'SCR-'.$makeSr.'-'.$currentYear;
    $commands[] = ajax_command_invoke("input.scr-number", 'val',array($scrNumber));
    $commands[] = ajax_command_invoke("input.request-date", 'val',array(date('m/d/Y')));
    $commands[] = ajax_command_invoke("select.scm-my-request-entity", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm-my-request-description", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-department-approver", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-entity", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-approver-email", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-request-type", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-department", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-request-subtype", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-priority-level", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-category", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-my-request-sub-category", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-supply-chain-lead", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-supply-chain-lead-id", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-material-manager", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-material-manager-id", 'val',array(''));
    $commands[] = ajax_command_invoke('.scm-my-request-priority-frozen-field', 'val',array(''));
    if(!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
      $commands[] = ajax_command_invoke("input.scm-my-request-requester-first-name", 'val',array(''));
      $commands[] = ajax_command_invoke("input.scm-my-request-requester-last-name", 'val',array(''));
    }
    if(isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
      $commands[] = ajax_command_invoke("select.scm-my-request-project-status", 'val',array('active'));
    } else {
      $commands[] = ajax_command_invoke("select.scm-my-request-project-status", 'val',array(''));
    }
    
    $commands[] = ajax_command_html(".filelist-outer", '');
    $commands[] = ajax_command_html("#scm-upload-filelist", '');
    $commands[] = ajax_command_invoke('#scm-upload-filelist', 'hide'); 
    $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-fn", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-ln", 'val',array(''));
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_my_request_table_data());
    $commands[] = ajax_command_invoke("input.line_item_number", 'val',array(''));
    $commands[] = ajax_command_invoke("input.line_master_number", 'val',array(''));
    $commands[] = ajax_command_invoke("input.unit_price", 'val',array(''));
    $commands[] = ajax_command_invoke("select.purchase_unit_of_measure", 'val',array(''));
    $commands[] = ajax_command_invoke("input.uom_conversion", 'val',array(''));
    $commands[] = ajax_command_invoke("input.purchase_uom_conversion", 'val',array(''));
    $commands[] = ajax_command_invoke("input.add_item_description", 'val',array(''));
    $commands[] = ajax_command_invoke("input.effective_date", 'val',array(''));
    $commands[] = ajax_command_invoke("input.closeout_date", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm-my-request-closeoutremarks", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_directpurchase", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm_request_company", 'val',array(''));  
    $commands[] = ajax_command_invoke("input.scm_request_catalogsnumber", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_contactname", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_contactemail", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_contactphone", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_contractnumber", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm_request_vendor_company", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_vendor_catalog", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_vendor_cname", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_vendor_cemail", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_vendor_cphone", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm_request_vendor_cnumber", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm_request_note", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-department-approver", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-approver-email", 'val',array(''));
    $commands[] = ajax_command_invoke('.scm_chatting_container-main','hide');
    if(isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
        //$commands[] = ajax_command_css('.custom-action-button-div', array('display' => 'block'));
        $commands[] = ajax_command_invoke(".custom-action-button-div", 'show');
      // $commands[] = ajax_command_invoke('#program_scm_main_container', 'attr', array('for','open'));
      // $commands[] = ajax_command_invoke('.custom-action-button-div', addClass, array('display-block'));
      
      }
    $commands[] = ajax_command_replace("#alert-container-section", render($form['main_container2']));  
  }

  return array('#type' => 'ajax', '#commands' => $commands);*/
}

function get_single_userDBbyidcsm($userid) {
  $getquery = db_select('m6connect_scm_settings_user_database', 'n');
  $getquery->fields('n');
  $getquery->condition('n.id', $userid, '=');
  $getresult = $getquery->execute()->fetchObject();
  return $getresult;
}

function project_scm_my_request_container_process($element, &$form_state) {
  global $user, $company;

  if (isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $usersdb = get_scm_user_database_by_email($_SESSION['login-mail']);
    if($usersdb->companyID) {
      $company = node_load($usersdb->companyID);
    }
  }

  $default_values = array();
  if (!empty($form_state['default_values']['main_container'])) {
    $default_values = $form_state['default_values']['main_container'];
  }

  $subcatdatallset = $form_state['sub_type_request_fetch_options'];

  if (!empty($form_state['default_values']['select_options']['request_subtype'])) {
    $subcatdatallset = $form_state['default_values']['select_options']['request_subtype'];
  }
  $categoryData = _get_all_main_categories_scm();
  $categoryData = array_map('ucwords', $categoryData);

  $subcategoryData = array();
  if (!empty($form_state['sub_category_fetch_options'])) {
    $subcategoryData = $form_state['sub_category_fetch_options'];
  }

  $supman = NULL;
  if (!empty($form_state['supply_chain_lead_fetch_options'])) {
    $supman = $form_state['supply_chain_lead_fetch_options'];
  }

  $currentYear = date('Y');
  $myCounter = variable_get('SCRNumber');
  $makeSr = str_pad($myCounter, 6, "0", STR_PAD_LEFT);  
  $scrNumber = 'SCR-'.$makeSr.'-'.$currentYear;

  $entity_option = _getting_table_data_call('scm_setting_location_entity');
  $entity_opt_selectAll = array();

  if (count($entity_option) > 0) {
    $entity_opt_selectAll = array('all' => 'All');
  }

  $entity_all_options = $entity_opt_selectAll + $entity_option;

  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full')),
  );

  $element['main-container']['full-container']['full-container-inner-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-5','col-sm-5','col-xs-12','padding-0','project-details-left')),
    '#prefix' => '<div class="row margin-0">',
    '#suffix' => '</div>',
  );

  $element['main-container']['full-container']['my-request-node-nid'] = array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('my-request-node-nid')),
  );

  if (!empty($default_values)) {
    $element['main-container']['full-container']['my-request-node-nid']['#value'] = $default_values['scr-id'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scr-number'] = array(
    '#type' => 'textfield',
    '#title' => 'SCR Number',
    '#attributes' => array('class'=> array('form-control scr-number')),
    '#default_value' => !empty($default_values['scr-number']) ? $default_values['scr-number'] : $scrNumber,
    '#prefix' => '<div class="project-details-border clearfix"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  // Checking if user can edit the SCR number or not.
  $default_edit_flag_val = variable_get('edit_flag_val', array());
  if (empty($default_edit_flag_val[$company->nid])) {
    $element['main-container']['full-container']['full-container-inner-left']['scr-number']['#disabled'] = TRUE;
  }

  $element['main-container']['full-container']['full-container-inner-left']['request-date']= array(
    '#title' => 'Request Date',
    '#type' => 'textfield',
    '#attributes' => array('class'=> array('form-control request-date'),'autocomplete' => 'off'),
    '#default_value' => !empty($default_values['request-date']) ? $default_values['request-date'] : date('m/d/Y'),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => TRUE,
  );

  $element['main-container']['full-container']['full-container-inner-left']['effective_date']= array(
    '#title' => 'Anticipated Completion Date',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',
    '#attributes' => array('class'=> array('form-control effective_date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#default_value' => !empty($default_values['effective_date']) ? $default_values['effective_date'] : date('m/d/Y'),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-entity'] = array(  
    '#title' => 'Entity',
    '#attributes' => array(
      'class'=> array(
        'form-control',
        'workflow-auto',
        'scm-my-request-entity',
        'clear-data',
        'as-asset-region-d',
        'hcfm-normal-selectallfield',
        'hcfmdash-region-list',
        'dash_asset_region_list',
        'margin-left-220',
      )
    ),
    '#type' => 'select',
    '#options' => $entity_all_options,
    '#empty_option' => 'None',
    // '#validate' => TRUE,
    '#required' => TRUE,

    '#select2' => array(
      'width' => '50%',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_entity_callback',
      'wrapper' => 'program_scm_main_container-entymanager',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="my-request-entity form-item clearfix dash-form-field hcfm-dash-form-outer margin-bottom-10">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['entity'])) {
    $entity_diff = array_diff($default_values['entity'], array_keys($entity_all_options));
    if (!empty($entity_diff)) {
      // It means there are some options selected in old node, which are not
      // available now.
      // Removing those options.
      $default_values['entity'] = array_diff($entity_diff, $default_values['entity']);
    }
  }
  if (!empty($default_values['entity'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-entity']['#default_value'] = drupal_map_assoc($default_values['entity']);
  }

  $depquery = db_select('m6connect_scm_setting_department', 'n');
  $depquery->fields('n',array('id','title'));
  $depquery->condition('n.nid', $company->nid, '=');
  $departmentData = $depquery->execute()->fetchAllKeyed(0,1);
  $departmentData = array_map('ucwords', $departmentData);

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-department'] = array(  
    '#title' => 'Department',
    '#type' => 'select',
    '#options' => $departmentData,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-department')),
    '#empty_option' => 'None',
    '#ajax' => array(
      'callback'=> 'show_department_callback',
      'wrapper' => 'categoriesrealtionarea-depa',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['department']) && in_array($default_values['department'], array_keys($departmentData))) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-department']['#default_value'] = $default_values['department'];

    $dprquery = db_select('m6connect_scm_setting_department', 'n');
    $dprquery->fields('n');
    $dprquery->condition('n.id', $default_values['department'], '=');
    $dprquery->condition('n.nid', $company->nid, '=');
    $dprData = $dprquery->execute()->fetchObject();

    foreach(explode('|', $dprData->dpapprover) as $key => $val) {
        $userss[$key] = user_load($val)->realname;
        $usersmail[$key] = user_load($val)->mail;
    }

    $default_values['department-approver'] = implode(', ', $userss);
    $default_values['approver-email'] = implode(', ', $usersmail);
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-department-approver'] = array(  
    '#title' => 'Department Approver',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-department-approver')),
    '#prefix' => '<div id="categoriesrealtionarea-depa"><div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => TRUE,
  );

  if (!empty($default_values['department-approver'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-department-approver']['#default_value'] = $default_values['department-approver'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-approver-email'] = array(  
    '#title' => 'Approver Email',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-approver-email')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
    '#disabled' => TRUE,
  );

  if (!empty($default_values['approver-email'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-approver-email']['#default_value'] = $default_values['approver-email'];
  }

  $request_type_options = _get_request_type_from_settings();
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-type'] = array(  
    '#title' => 'Request Type',
    '#type' => 'select',
    '#options' => $request_type_options,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-request-type')),
    '#empty_option' => 'Select The Type of Request',
    // '#validate' => TRUE,
    '#required' => TRUE,
    '#ajax' => array(
      'callback'=> 'add_to_item_master_callback',
      'wrapper' => 'categoriesrealtionarea-subtype',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['request-type']) && !empty($request_type_options) && in_array($default_values['request-type'], array_keys($request_type_options))) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-type']['#default_value'] = $default_values['request-type'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-subtype'] = array(  
    '#title' => 'Request Subtype',
    '#type' => 'select',
    '#options' => $subcatdatallset,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-request-subtype')),
    '#empty_option' => 'Select Request Subtype',
    // '#validate' => TRUE,
    '#required' => TRUE,
    '#default_value' => !empty($form_state['default_subtype_valdata']) ? $form_state['default_subtype_valdata'] : '00',
    '#prefix' => '<div class="form-item clearfix" id="categoriesrealtionarea-subtype">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['request-subtype']) && !empty($subcatdatallset) && in_array($default_values['request-subtype'], array_keys($subcatdatallset))) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-subtype']['#default_value'] = $default_values['request-subtype'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-level'] = array(  
    '#title' => 'Priority Level',
    '#type' => 'select',
    '#options' => array('critical' => 'Critical','routine' => 'Routine'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-priority-level')),
    '#empty_option' => 'Select Priority',
    '#ajax' => array(
      'callback'=> 'request_priority_frozen_field_callback',
      'wrapper' => 'scm-justification-div',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['priority-level'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-level']['#default_value'] = $default_values['priority-level'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-frozen-field'] = array(
    '#title' => 'Justification',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto pull-right','scm-my-request-priority-frozen-field')),
    '#prefix' => '<div id="scm-justification-div"><div class="form-item form-itemfieldpop clearfix" style="' . $form_state['frozen_defaults']['style_justification'] . '">',
    '#suffix' => '</div></div>',
    '#required' => $form_state['frozen_defaults']['justification_required'],
  );

  if (!empty($default_values['priority-frozen'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-frozen-field']['#default_value'] = $default_values['priority-frozen'];
  }

  if (arg(1) != 'archive') {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-category'] = array(  
      '#title' => 'Category',
      '#type' => 'select',
      '#options' => $categoryData,
      '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-category')),
      '#empty_option' => 'Select Category',
      // '#validate' => TRUE,
      '#required' => TRUE,
      '#ajax' => array(
        'callback'=> 'change_scm_my_request_category_callback',
        'wrapper' => 'categoriesrealtionarea',
        'effect' => 'fade',
      ),
      '#prefix' => '<div class="category-callbackwrapper clearfix"><div class="form-item clearfix">',
      '#suffix' => '</div></div>',
    );
  }

  if (arg(1) == 'archive') {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-category'] = array(
      '#title' => 'Category',
      '#type' => 'select',
      '#options' => $categoryData,
      '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-category')),
      '#empty_option' => 'Select Category',
      '#disabled' => TRUE,
      '#prefix' => '<div class="category-callbackwrapper clearfix"><div class="form-item clearfix">',
      '#suffix' => '</div></div>',
    );
  }

  if (!empty($default_values['category']) && in_array($default_values['category'], array_keys($categoryData))) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-category']['#default_value'] = $default_values['category'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea']['scm-my-request-sub-category'] = array(
    '#title' => 'Subcategory',
    '#type' => 'select',
    '#options' => $subcategoryData,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-sub-category')),
    '#empty_option' => 'Select Subcategory',
    '#required' => TRUE,
    '#prefix' => '<div id="categoriesrealtionarea"><div id="sub-category-container-custom" class="form-item clearfix scm-my-request-sub-category-call">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_category_callback',
      'wrapper' => 'scm-request-scl-details',
      'effect' => 'fade',
    ),
  );

  if (!empty($form_state['default_sub_val'])) {
    $element['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea']['scm-my-request-sub-category']['#default_value'] = $form_state['default_sub_val'];
  }

  if (!empty($default_values['sub-category']) && in_array($default_values['sub-category'], array_keys($subcategoryData))) {
    $element['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea']['scm-my-request-sub-category']['#default_value'] = $default_values['sub-category'];
  }

  $scl_name = '';
  if (!empty($supman)) {
    $scl_name = _get_user_full_name($supman);
  }

  // SCL Name.
  $element['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea']['scl-details']['scm-my-request-supply-chain-lead'] = array(
    '#title' => 'Supply Chain Lead',
    '#type' => 'textfield',
    '#default_value' => $scl_name,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-supply-chain-lead')),
    // '#validate' => TRUE,
    '#disabled' => TRUE,
    '#prefix' => '<div id="scm-request-scl-details"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  // SCL UID.
  $element['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea']['scl-details']['scm-my-request-supply-chain-lead-id'] = array(
    '#type' => 'hidden',
    '#value' => $supman,
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div></div>',
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-material-manager'] = array( 
    '#title' => 'Materials Manager',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-material-manager')),
    '#disabled' => TRUE,
    '#prefix' => '<div class="form-item clearfix" id="program_scm_main_container-entymanager">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['material-manager'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-material-manager']['#default_value'] = $default_values['material-manager'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-project-status'] = array(  
    '#title' => 'Request Status',
    '#type' => 'select',
    '#options' => array('active' => 'Active','hold' => 'Hold','terminated' => 'Terminated','completed' => 'Completed'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-project-status')),
    '#empty_option' => 'Select Status',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['project-status'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-project-status']['#default_value'] = $default_values['project-status'];
  }

  if(isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-project-status']['#default_value'] = 'active';
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-project-status']['#disabled'] = TRUE;
  }

  $requesterfname = $requesterlname = $requesteremail = $requesterid = '';

  if (isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $resultusers = get_scm_user_database_by_email($_SESSION['login-mail']);
    $requesterfname = $resultusers->fristname;
    $requesterlname = $resultusers->lastname;
    $requesteremail = $resultusers->email;
    $requesterid = $resultusers->id;
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="scm-my-request-requester-outer">',
    '#suffix' => '</div>',
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requesterIDhidden'] = array(
    '#type' => 'hidden',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requesterIDhidden')),
  );

  if (!empty($requesterid)) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requesterIDhidden']['#value'] = $requesterid;
  }

  if(!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requester-ref'] = array(
      '#title'             => 'Requester Search',
      '#type'              => 'textfield',
      '#attributes'        => array('class' => array('form-control','workflow-auto', 'scm-my-request-requester-ref'),'placeholder'=>t('Requester')),
      '#autocomplete_path' => 'userdb-data/autocomplete',
      '#ajax'              => array(
        'callback' => 'scm_my_request_searchdbuser_callback',
        'event'    => 'blur',
        'wrapper'  => 'scm-my-request-requester-outer',
        'method'   => 'replace',
        'effect'   => 'fade',
      ),
      '#prefix' => '<div class="form-item clearfix">',
      '#suffix' => '</div>',
    );

    if (!empty($default_values['requester-db-ref'])) {
      $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requesterIDhidden']['#value'] = $default_values['requester-db-ref'];

      $requester_data = get_scm_user_database_data($default_values['requester-db-ref']);

      $requester_name = '';
      if (!empty($storage_project['requester-first-name']) && !empty($storage_project['requester-last-name'])) {
        $requester_name = $storage_project['requester-first-name'] . ' ' . $storage_project['requester-last-name'];
        $requesterfname = $storage_project['requester-first-name'];
        $requesterlname = $storage_project['requester-last-name'];

        if (!empty($storage_project['requester-email'])) {
          $requesteremail = $storage_project['requester-email'];
        }
        else {
          $requesteremail = $requester_data->email;
        }
      }

      if (empty($requester_name)) {
        // We get the request details from $storage_project, but in case
        // if we do not have then we come here.
        if (!empty($requester_data->fristname)) {
          $requester_name .= $requester_data->fristname;
          $requesterfname = $requester_data->fristname;
        }

        if (!empty($requester_name) && !empty($requester_data->lastname)) {
          $requester_name .= ' ' . $requester_data->lastname;
          $requesterlname = $requester_data->lastname;
        }
        elseif (!empty($requester_data->lastname)) {
          $requester_name .= $requester_data->lastname;
          $requesterlname = $requester_data->lastname;
        }

        if (!empty($requester_data->email)) {
          $requesteremail = $requester_data->email;
        }
      }

      if (!empty($requester_name)) {
        $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requester-ref']['#default_value'] = $requester_name;
      }
    }
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requester-first-name'] = array(  
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requester-first-name')),
    '#default_value' => $requesterfname,
    '#prefix' => '<div class="form-item requester clearfix" id="user-databseids"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Requester</label></div><div class="col-md-6 padding-0"><div class="row margin-5"><div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div>',
    '#disabled' => TRUE,
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container']['scm-my-request-requester-last-name'] = array(  
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requester-last-name')),
    '#default_value' => $requesterlname,
    '#prefix' => '<div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div><span class="padding-5 pull-right"><a href="mailto:'.$requesteremail.'">'.$requesteremail.'</a></span></div></div></div></div>',
    '#disabled' => TRUE,
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requested-on-behalf-fn'] = array(  
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requested-on-behalf-fn')),
    '#prefix' => '<div class="form-item requester clearfix"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Requested on Behalf of</label></div><div class="col-md-6 padding-0"><div class="row margin-5"><div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['on-behalf-fn'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requested-on-behalf-fn']['#default_value'] = $default_values['on-behalf-fn'];
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requested-on-behalf-ln'] = array(  
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requested-on-behalf-ln')),
    '#prefix' => '<div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div></div></div></div></div>',
  );

  if (!empty($default_values['on-behalf-ln'])) {
    $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requested-on-behalf-ln']['#default_value'] = $default_values['on-behalf-ln'];
  }

  if (!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
    $element['main-container']['full-container']['full-container-inner-left']['closeout_date'] = array(
      '#title' => 'Closeout Date',
      '#type' => 'date_popup',
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '-3:+3',  
      '#attributes' => array('class'=> array('form-control closeout_date'),'autocomplete' => 'off'),
      '#pre_render' => array('m6connect_programe_date_prerender'),
      '#prefix' => '<div class="form-item clearfix">',
      '#suffix' => '</div>',
      '#disabled' => TRUE,
    );

    if (!empty($default_values['closeout_date'])) {
      $element['main-container']['full-container']['full-container-inner-left']['closeout_date']['#default_value'] = $default_values['closeout_date'];
    }
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-attachment']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[]',
    '#upload_location' => 'public://',  
    '#attributes' => array('multiple' => 'multiple','id' => 'scm-attachment-upload', 'onchange' => 'javascript:updateList()','class'=> array('scm-my-request-attachment')),
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-listattch'] = array(  
    '#title' => 'listattachments',
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-listattch')),
    '#empty_option' => 'Select Attachments',
    // '#validate' => TRUE,
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_attachment_callback',
      'wrapper' => 'scm-upload-filelist',
      'effect' => 'fade',
    ),

    '#prefix' => '<div id="listattachmentsselectlist" style="display:none;">',
    '#suffix' => '</div>',
  );

  $element['main-container']['full-container']['full-container-inner-left']['attachment_list'] = array(
    '#markup' => '',
  );

  $upload_list_style = 'display:none;';
  $upload_list_content = '';

  if (!empty($default_values['attachmentshtml'])) {
    $upload_list_content .= '<div class="image-preview">';
    $upload_list_content .= implode('', $default_values['attachmentshtml']);
    $upload_list_content .= '</div>';

    $upload_list_style = 'display:block;';
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-attachment-link']= array(
    '#markup' => '<div id="listattachmentsmarkup" class="col-md-6 padding-0 margin-top-10"><a href="javascript:void(0);" class="scm-my-request-attachment-link">Click to Browse and Upload Files</a> </div><div class="col-sm-12 attachmentshtmlouterclass"><div id="scm-upload-filelist" class="col-sm-12" style="' . $upload_list_style . '">' . $upload_list_content . '</div><div class="filelist-outer"></div></div>',
    '#prefix' => '<div class="form-item requester clearfix"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Attachments</label></div>',
    '#suffix' => '</div></div></div>',
  );

  $element['main-container']['full-container']['scm-my-request-description'] = array(
    '#title' => 'Description',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('form-control scm-my-request-description')),
    '#prefix' => '<div class="clearfix form-item">',
    '#suffix' => '</div>',
  );

  if (!empty($default_values['description'])) {
    $element['main-container']['full-container']['scm-my-request-description']['#default_value'] = $default_values['description'];
  }

  if (!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
    $element['main-container']['full-container']['scm-my-request-closeoutremarks'] = array(
      '#title' => 'Closeout Remarks',
      '#type' => 'textarea',
      '#attributes'=> array('class'=> array('form-control scm-my-request-closeoutremarks')),
      '#default_value' => isset($defaultValues['scm-my-request-closeoutremarks'])?strip_tags($defaultValues['scm-my-request-closeoutremarks']):'',
      '#prefix' => '<div class="clearfix form-item">',
      '#suffix' => '</div>',
    );

    if (!empty($default_values['scm-my-request-closeoutremarks'])) {
      $element['main-container']['full-container']['scm-my-request-closeoutremarks']['#default_value'] = $default_values['scm-my-request-closeoutremarks'];
    }
  }

  return $element;
}

function request_priority_frozen_field_callback($form,&$form_state) {
  return $form['outer-container']['main-container']['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-frozen-field'];
  if($form_state['triggering_element']['#name']=='scm-my-request-priority-level') {
   // $mrkuptext = '';
    //watchdog('testing the trigger', print_r($form_state['triggering_element']['#value'], 1));
    if($form_state['triggering_element']['#value'] == 'critical') {
      $form['main-container']['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-frozen-field']['#required'] = TRUE;
      //$mrkuptext = '1 day from the day submitted';
      $commands[] = ajax_command_replace('#program_scm_main_container',render($form['main-container']['main-container'])); 
         
    }
    else {
      $form['main-container']['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-frozen-field']['#required'] = FALSE;
      //$mrkuptext = '7 business days from the day submitted';
      $commands[] = ajax_command_replace('#program_scm_main_container',render($form['main-container']['main-container'])); 
    } 
    
  }
  
  //$commands[] = ajax_command_invoke('.scm-my-request-priority-frozen-field', 'val',array($mrkuptext));

  $commands[] = ajax_command_invoke('.form-itemfieldpop','show');
  return array('#type' => 'ajax', '#commands' => $commands);
  
}

function change_scm_my_request_category_archive_callback($form,&$form_state) {
  if($form_state['triggering_element']['#name']=='scm-my-request-category') {
      $requestdeft = node_load($form_state['values']['my-request-node-nid']);
  }
}

function change_scm_my_request_attachment_callback($form,&$form_state) {
  if($form_state['triggering_element']['#name']=='scm-my-request-listattch') {
    $myReqNode = node_load($form_state['values']['get-my-requests']);
    $attachmentshtml = '';
    foreach ($myReqNode->field_my_request_attachment['und'] as $addKey => $addVal) {
      $getFid = $addVal['fid'];
      $attachmentshtml[] = '<p id="getfileID_'.$getFid.'"><label class="checkbox removdeletefile"><i class="fa fa-times padding-5" style="float:left; cursor:pointer;"></i><input type="checkbox" checked="checked"  class="image-remove-update sr-only" value="'.$getFid.'" for="'.$myReqNode->nid.'" fortitle="'.$addVal['filename'].'">'.l($addVal['filename'], file_create_url($addVal['uri'])).'</label></p>';
    }

    $commands[] = ajax_command_invoke('.attachmentshtmlouterclass', 'addClass', array('thumbnail'));
    $commands[] = ajax_command_replace("#scm-upload-filelist", '<div class="image-preview">'.implode('', $attachmentshtml).'</div>');
    $commands[] = ajax_command_invoke('#scm-upload-filelist', 'show');
  }
}

function scm_my_request_searchdbuser_callback($form,&$form_state) {
  return $form['outer-container']['main-container']['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-container'];
  // global $company;
  // $commands = array();
  // if($form_state['triggering_element']['#name']=='scm-my-request-requester-ref') {
  //   $form_state['triggering_element']['#value'];
  //   $get_userdb = get_scm_user_database_data($form_state['triggering_element']['#value']);
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requesterIDhidden", 'val',array($get_userdb->id));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requester-ref", 'val', array($get_userdb->fristname.' '.$get_userdb->lastname));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requester-first-name", 'val',array($get_userdb->fristname));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requester-last-name", 'val',array($get_userdb->lastname));
  // }
  // return array('#type' => 'ajax', '#commands' => $commands);
}

function show_department_callback($form,&$form_state) {
  global $company;
    $commands = array();
    if($form_state['triggering_element']['#name']=='scm-my-request-department'){

      $subquery = db_select('m6connect_scm_setting_department', 'n');
      $subquery->fields('n');
      $subquery->condition('n.id', $form_state['triggering_element']['#value'], '=');
      $subquery->condition('n.nid', $company->nid, '=');
      $resultsubtype = $subquery->execute()->fetchObject();
    foreach(explode('|', $resultsubtype->dpapprover) as $key => $val) {
        $userss[$key] = user_load($val)->realname;
        $usersmail[$key] = user_load($val)->mail;
    }
    $commands[] = ajax_command_invoke("input.scm-department-approver", 'val',array(implode(",",$userss)));
    $commands[] = ajax_command_invoke("input.scm-approver-email", 'val',array(implode(",",$usersmail)));
    }
    return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_my_request_category_callback($form,&$form_state) {
  // $form_state['rebuild'] = TRUE;
  if ($form_state['triggering_element']['#name'] == 'scm-my-request-sub-category') {
    // If sub category is changed, then replacing this one. scm-my-request-sub-category
    return $form['outer-container']['main-container']['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea']['scl-details'];
  }
  else {
    // If main category is changed.
    return $form['outer-container']['main-container']['main-container']['full-container']['full-container-inner-left']['categoriesrealtionarea'];
  }
}

function add_to_item_master_callback($form,&$form_state) {
  //dpm($form_state);
  $triggeringElement = $form_state['triggering_element'];
  if(!empty($triggeringElement['#value']) && $triggeringElement['#value'] != 0 && $triggeringElement['#name'] == 'scm-my-request-request-type'){
    $reqType = explode('-',$triggeringElement['#value']);
    
    if(!empty($reqType[1])) {
      $form_state['add-to-item-custom'] = 'TRUE';
    } else {
      $form_state['add-to-item-custom'] = 'FALSE';
    }
  }
  
  $form_state['rebuild'] = TRUE; 
  //$form_state['add-to-item-custom'] =
 //dpm($form_state,'$form_state call');
  
    //pre($form_state['triggering_element']);
     //pre($form_state['add-to-item-custom']);
  
  return $form['outer-container']['main-container']['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-subtype'];

  

}

function change_scm_my_request_entity_callback($form,&$form_state) {
  return $form['outer-container']['main-container']['main-container']['full-container']['full-container-inner-left']['scm-my-request-material-manager'];
  $commands = array();
  $matarial_managernames_new = array();

  if($form_state['triggering_element']['#name']=='scm-my-request-entity'){
    
    $entityids = $form_state['triggering_element']['#value'];
    $entityids2 = _getting_table_data_call('scm_setting_location_entity');
 
    if(!empty($entityids) && $form_state['triggering_element']['#value']['all']!='all'){

      foreach($entityids as $entityid){
        $entityload = node_load($entityid);
        $matarial_manageruids = explode('|', $entityload->field_entity_materials_manager['und'][0]['value']);
       
        foreach ($matarial_manageruids as $key => $value){
          $useload= user_load($value);
          if(_is_user_material_manager(FALSE, $useload)){
            $matarial_managernames_new[] = $useload->realname;
          }
        }
      }
    }else{
      foreach($entityids2 as $k => $v){
        $entityload = node_load($k);
        $matarial_manageruids = explode('|', $entityload->field_entity_materials_manager['und'][0]['value']);
       
        foreach ($matarial_manageruids as $key => $value){
          $useload= user_load($value);
          if(_is_user_material_manager(FALSE, $useload)){
            $matarial_managernames_new[] = $useload->realname;
          }
        }
      }
    }



    $euser = array(implode(', ', $matarial_managernames_new));
   // $commands[] = ajax_command_invoke('.custom-action-button-div', 'attr', array('for','closed'));
   // $commands[] = ajax_command_invoke('#program_scm_main_container', 'attr', array('for','closed'));
    //$commands[] = ajax_command_invoke('.custom-action-button-div', addClass, array('display-block'));
    $commands[] = ajax_command_invoke('input.scm-my-request-material-manager', 'val', $euser);
    //$commands[] = ajax_command_invoke('input.scm-my-request-material-manager-id', 'val', array($entityload->field_entity_materials_manager['und'][0]['value']));
    }

  return array('#type' => 'ajax', '#commands' => $commands);
  
  
}

/**
 * Validate handler for scm_my_request_form.
 */
function project_scm_my_request_validate($form, &$form_state) {
  if(form_get_errors()){
    form_set_error('', t('Please fill all the required fields.'));
    return;
  }
  
  
  if($_FILES['files']['name'] != '')  {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
      $file = file_save_upload($i, array( 
        'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
      ));
      if($file) {    
        if ($file = file_move($file, 'private://')) {
          $form_state['values']['scm-my-request-attachment'][$i] = $file;
        } 
      }
    }
  }


}

/**
 * Submit handler for scm_my_request_form.
 */
function project_scm_my_request_submit(&$form, &$form_state) {
  // dpm($form_state, '$form_state'); return;
  global $user, $company;
  $formVal  = $form_state['values'];
  $getTitle = $formVal['scr-number'];
  $alert    = $formVal['alert'];  
  $screquestNew = '';
  if (isset($formVal['my-request-node-nid']) && !empty($formVal['my-request-node-nid'])) {
    $nodesave = node_load($formVal['my-request-node-nid']);
    //$nodesave->title = $getTitle;
    $savestatus = 'updated';
    if(!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
      $nodesave->field_project_status['und'][0]['value']         = $formVal['scm-my-request-project-status'];
    }
  }
  else {
    $screquestNew = 'screquestNew';
    $nodesave = _node_creation_call('scm_requests',$getTitle);
    $savestatus = 'saved';
    $currentYear = date('Y');
    $myCounter   = variable_get('SCRNumber');
    $makeSr      = str_pad($myCounter, 6, "0", STR_PAD_LEFT);
    $scrNumber   = 'SCR-' . $makeSr . '-' . $currentYear;
    $scrctNumber = variable_get('SCRNumber');
    variable_set('SCRNumber', $scrctNumber + 1);

    if(isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
      $nodesave->field_project_status['und'][0]['value']         = 'active'; 
    } else {
      $nodesave->field_project_status['und'][0]['value']         = $formVal['scm-my-request-project-status'];
    }
  }

  $nodesave->body['und'][0]['value']                             = $formVal['scm-my-request-description']; 
  $nodesave->field_request_date['und'][0]['value']               = $formVal['request-date']; 
  $nodesave->field_entity['und'][0]['value']                     = implode(', ', $formVal['scm-my-request-entity']);
  $nodesave->field_department['und'][0]['value']                 = $formVal['scm-my-request-department'];

  $dprquery = db_select('m6connect_scm_setting_department', 'n');
  $dprquery->fields('n');
  $dprquery->condition('n.id', $formVal['scm-my-request-department'], '=');
  $dprquery->condition('n.nid', $company->nid, '=');
  $dprData = $dprquery->execute()->fetchObject();

  $nodesave->field_department_approver_ref['und'][0]['value'] = $dprData->dpapprover;

  $nodesave->field_department_approver['und'][0]['value']        = $formVal['scm-my-request-department-approver'];
  $nodesave->field_approver_email['und'][0]['value']             = $formVal['scm-my-request-approver-email'];
  $nodesave->field_request_type['und'][0]['value']               = $formVal['scm-my-request-request-type'];
  $nodesave->field_request_subtype['und'][0]['value']            = $formVal['scm-my-request-request-subtype'];
  $nodesave->field_priority_level['und'][0]['value']             = $formVal['scm-my-request-priority-level'];
  $nodesave->field_priority_frozen['und'][0]['value']            = $formVal['scm-my-request-priority-frozen-field'];
  $nodesave->field_category['und'][0]['value']                   = $formVal['scm-my-request-category'];
  $nodesave->field_sub_category['und'][0]['value']               = $formVal['scm-my-request-sub-category'];

  $nodesave->field_supply_chain_lead_ref['und'][0]['value']      = $formVal['scm-my-request-supply-chain-lead-id'];

  if (!empty($formVal['scm-my-request-entity']['all'])) {
    $entities = _getting_table_data_call('scm_setting_location_entity');
  }
  else {
    $entities = $formVal['scm-my-request-entity'];
  }

  $material_manageruids = array();
  foreach ($entities as $k => $v) {
    $entityload = node_load($k);
    if (!empty($entityload->field_entity_materials_manager['und'][0]['value'])) {
      // If we have material managers at least.
      $material_manageruids += explode('|', $entityload->field_entity_materials_manager['und'][0]['value']);
    }
  }

  $nodesave->field_materials_manager_ref['und'][0]['value']      = implode('|', $material_manageruids);
   
  $nodesave->field_requester_to['und'][0]['value']               = $formVal['scm-my-request-requester-first-name'];
  $nodesave->field_requester_from['und'][0]['value']             = $formVal['scm-my-request-requester-last-name'];
  $nodesave->field_requested_on_behalf_of['und'][0]['value']     = $formVal['scm-my-request-requested-on-behalf-fn'];
  $nodesave->field_requested_on_behalf_of_fro['und'][0]['value'] = $formVal['scm-my-request-requested-on-behalf-ln'];
  $nodesave->field_scm_effective_date['und'][0]['value']         = $formVal['effective_date'];

  if(!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
    if($formVal['scm-my-request-project-status'] == 'completed') {
      $nodesave->field_scm_closeout_date['und'][0]['value']          = date('m/d/Y');
    }
    $nodesave->field_scm_request_closeoutremark['und'][0]['value'] = $formVal['scm-my-request-closeoutremarks']; 
  }
  
  $nodesave->field_scm_request_directpurchase['und'][0]['value'] = $formVal['scm_request_directpurchase']; 
  $nodesave->field_scm_request_company['und'][0]['value']        = $formVal['scm_request_company']; 
  $nodesave->field_scm_request_catalogsnumber['und'][0]['value'] = $formVal['scm_request_catalogsnumber']; 
  $nodesave->field_scm_request_contactname['und'][0]['value']    = $formVal['scm_request_contactname']; 
  $nodesave->field_scm_request_contactemail['und'][0]['value']   = $formVal['scm_request_contactemail']; 
  $nodesave->field_scm_request_contactphone['und'][0]['value']   = $formVal['scm_request_contactphone']; 
  $nodesave->field_scm_request_contractnumber['und'][0]['value'] = $formVal['scm_request_contactphone']; 
  $nodesave->field_scm_request_vendor_company['und'][0]['value'] = $formVal['scm_request_vendor_company']; 
  $nodesave->field_scm_request_vendor_catalog['und'][0]['value'] = $formVal['scm_request_vendor_catalog']; 
  $nodesave->field_scm_request_vendor_cname['und'][0]['value']   = $formVal['scm_request_vendor_cname']; 
  $nodesave->field_scm_request_vendor_cemail['und'][0]['value']  = $formVal['scm_request_vendor_cemail']; 
  $nodesave->field_scm_request_vendor_cphone['und'][0]['value']  = $formVal['scm_request_vendor_cphone']; 
  $nodesave->field_scm_request_vendor_cnumber['und'][0]['value'] = $formVal['scm_request_vendor_cnumber']; 
  $nodesave->field_scm_request_notes['und'][0]['value']          = $formVal['scm_request_note'];
  $nodesave->og_group_ref['und'][0]['target_id']                 = $company->nid;


  if (isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])) {
    $resultusersref = get_scm_user_database_by_email($_SESSION['login-mail']);
    $nodesave->field_requestordb_ref['und'][0]['value'] = $resultusersref->id;
  }
  else {
    $nodesave->field_requestordb_ref['und'][0]['value'] = $formVal['scm-my-request-requesterIDhidden'];
  }

  if (isset($nodesave->field_add_item_number['und'])) {
    foreach ($nodesave->field_add_item_number['und'] as $fkey => $fvalue) {
      $fvaluenode[] = $fvalue['value'];
      unset($nodesave->field_add_item_number['und'][$fkey]);
    }
    entity_delete_multiple('field_collection_item', $fvaluenode);
  }

  $count = 0;
  foreach ($alert as $key => $alert_detail) {
    $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_add_item_number')); 
    $field_collection_item->setHostEntity('node', $nodesave);
    $field_collection_item->field_scm_line_item_number[LANGUAGE_NONE][$count]['value']       = $alert_detail['line_item_number'];
    $field_collection_item->field_scm_item_master_number[LANGUAGE_NONE][$count]['value']     = $alert_detail['line_master_number'];
    $field_collection_item->field_line_item_nec[LANGUAGE_NONE][$count]['value']              = $alert_detail['nec_number'];
    $field_collection_item->field_scm_price_unit_measure_uom[LANGUAGE_NONE][$count]['value'] = $alert_detail['purchase_unit_of_measure'];
    $field_collection_item->field_scm_uom_converstion[LANGUAGE_NONE][$count]['value']        = $alert_detail['uom_conversion'];  
    $field_collection_item->field_scm_purchase_uom_price[LANGUAGE_NONE][$count]['value']     = str_replace(',','',str_replace("$","",$alert_detail['purchase_uom_conversion']));        
    $field_collection_item->field_scm_unit_price[LANGUAGE_NONE][$count]['value']             = str_replace(',','',str_replace("$","",$alert_detail['price_each']));

    $field_collection_item->field_manufacture_catalog_number[LANGUAGE_NONE][$count]['value'] = $alert_detail['manufacture_catalog_number'];     
    $field_collection_item->field_vendor_catalog_number[LANGUAGE_NONE][$count]['value']      = $alert_detail['vendor_catalog'];    
    $field_collection_item->field_scm_item_description[LANGUAGE_NONE][$count]['value']       = $alert_detail['add_item_description'];
    $field_collection_item->field_item_action[LANGUAGE_NONE][$count]['value']       = $alert_detail['remove'];
    $count++;
  }

  $field_collection_item->save();

  if (isset($formVal['scm-my-request-attachment']) && !empty($formVal['scm-my-request-attachment'])) {
    foreach ($form_state['values']['scm-my-request-attachment'] as $imgkey => $file) {
      if (!isset($nodesave->field_my_request_attachment['und'])) {
        $nodesave->field_my_request_attachment['und'] = array();
      }
      $new_file = file_load($file->fid);
      $file_arr = (array)$new_file;
      $file_arr['display'] = 1;
      $nodesave->field_my_request_attachment['und'][] = $file_arr;
    }
  }

  if (strpos($form_state['values']['scm-my-request-request-type'], '-1') !== false) {
        $required_state = TRUE;
  }

  foreach ($formVal['Allfieldsdata'] as $container) {
    foreach ($container as $key => $value) {
      $nid_element = 'scm_request_field_' . $key . '_nid';
      if (!empty($form_state['values'][$nid_element])) {
        insert_custom_field_data($key, $nodesave->nid, $form_state['values'][$nid_element]);
        continue;
      }
      if (isset($value) && !empty($value)) {
        insert_custom_field_data($key, $nodesave->nid, $value);
      }
    }
  }

  node_save($nodesave);

  if(!empty($screquestNew) && $screquestNew =='screquestNew' && $screqustcompay = $nodesave->og_group_ref[LANGUAGE_NONE][0]['target_id']) {
    $scComAdmins = _get_company_users_by_og_roles($screqustcompay,'Company Admin');
    if(!empty($scComAdmins)){
      foreach ($scComAdmins as $cakey => $cauid) {
        if (db_table_exists('m6connect_notification')) {
          $m6connect_notification = array(
            'type'         => 'scm',
            'event'        => 'screqust',
            'entity_id'    => $nodesave->nid ,
            'company_nid'  => $screqustcompay,
            'message'      => NULL,
            'request_from' => ((!empty($resultusersref->UUID) && $nodesave->uid ==0)?$resultusersref->UUID:$user->uid),
            'request_to'   => $cauid,
            'status'       => 1,
            'timestamp'    => time(),
          );
          entity_save('m6connect_notification', (object) $m6connect_notification);
        }
        $message = 'Hello,<br/>';
        $message .= $nodesave->title.' SC Request created.';

        $mail_to = _get_user_mail_realname_by_uid($cauid);
        $params = array(
          'subject' => $nodesave->title.' SC Request created.',
          'body' => $message,
          'sender' => ((!empty($resultusersref->UUID) && $nodesave->uid ==0)?$resultusersref->email:$user->mail),
          'language' => language_default(),
          'module' => 'm6connect_misc',
          'key' => 'screqust_mail___invite_2_m6_notify',
          'build' => TRUE,
        );



        $mail_sent = drupal_mail($params['module'], $params['key'], $mail_to['mail'], $params['language'], $params);
      }
    }
    //dpm($_SESSION['login-mail'],'login-mail');
    //dpm($resultusersref,'resultusersref');
    //dpm($nodesave,'$nodesave');  
    //dpm($form_state,'$form_state');
  }

  $current_uid = !empty($resultusersref->UUID) ? $resultusersref->UUID : $user->uid;

  // Updating the user chats mapping ids.
  // Defined in m6connect_scm.module.
  _update_scm_chat_data($nodesave);

  drupal_set_message('My Request - ' . $nodesave->title . ' has been ' . $savestatus . '.');
}

/**
 * Helper function to save data in custom tables.
 * Invoked from project_scm_my_request_submit
 */
function insert_custom_field_data($fieldID,$requestID,$value) {
  $query = db_select('m6connect_scm_settings_field_data', 'n');
  $query->fields('n');
  $query->condition('n.fieldID', $fieldID, '=');
  $query->condition('n.requestID', $requestID, '=');
  $resultmeta = $query->execute()->fetchObject();
  if(!empty($resultmeta)){
    $fieldsdata['fieldID'] = $fieldID;
    $fieldsdata['requestID'] = $requestID;
    $fieldsdata['value'] = $value;
    db_update('m6connect_scm_settings_field_data')
                                ->fields($fieldsdata)
                                ->condition('id', $resultmeta->id, '=')
                                ->execute();
  } else if(empty($resultmeta)) {
    db_insert('m6connect_scm_settings_field_data')->fields(array(
      'fieldID' => $fieldID,
      'requestID' => $requestID,
      'value' => $value,
    ))->execute();
  }
}

function get_all_custom_fieldsBY_reqestID($reqestID) {
    $query = db_select('m6connect_scm_settings_field_data', 'n');
    $query->fields('n');
    $query->condition('n.requestID', $reqestID, '=');
    $resultmeta = $query->execute()->fetchAll();
    foreach ($resultmeta as $key => $value) {
      $results[$value->id] = $value;
    }
    return $results;
}

function extrafield_invite_to_m6_process($element, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');

  if (isset($form_state['triggering_element']['#name']) && !empty($form_state['triggering_element']['#name'] == 'get-my-requests')) {
    $fieldsdata = get_all_custom_fieldsBY_reqestID($form_state['triggering_element']['#value']);
  }

  $default_values = array();
  if (!empty($form_state['default_values']['main_containerupper'])) {
    $default_values = $form_state['default_values']['main_containerupper'];
  }

  if (!empty($form_state['default_values']['main_containerupper_trigger'])) {
    $default_values_triggered = $form_state['default_values']['main_containerupper_trigger'];
  }

  $alldefultfields = _get_allField_scm_settings_matadetails();

  foreach ($alldefultfields as $key => $value) {
    $grouplabel = $value->Label;
    if ($value->Numberofvalues==1) {
      $grouplabel = '';
    }

    $required_state_html = '';
    $required_state = FALSE;

    if ($value->required_state == 1) {
      if (strpos($form_state['values']['scm-my-request-request-type'], '-1') !== false) {
        $required_state = TRUE;
      }
      else {
        $required_state = FALSE;
      }

      $required_state_html = '&nbsp;<span class="form-required" title="This field is required.">*</span>';     
    }

    if($value->required_state == 0) {
        $required_state = FALSE;
    }
    if ($grouplabel == 'notes') {
      $required_state_html = '';
    }

    $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key]= array(
      '#type'       => 'container',
      '#attributes' => array('class' => array('add-custom-dependent-field', $value->default_name)),
      '#prefix'     => '<div class="clearfix col-md-4" id="main-class-' . $key . '"><label>'.$grouplabel.'</label>' . $required_state_html . '<div id="add-custom-dependent-field' . $key . '" class="add-new-alert-detail thumbnail padding-10 clearfix">',
      '#suffix'     => '</div></div>',
    );

    foreach ($value->fieldsdata  as $fkey => $fvalue) {
      if ($fvalue->type == 'company') {
        $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]= array(
          '#type' => 'textfield',
          '#attributes'=> array('class' => array('form-control', 'vendor', 'workflow-auto', strtolower($value->Label) . '_group_fileds', 'scm_request_field_' . $fvalue->id, $fvalue->name_default . '_field'), 'placeholder' => t($fvalue->Label)),
          '#autocomplete_path' => 'commitment-company/autocomplete',
          '#ajax' => array(
            'callback' => 'scm_my_request_autocomplete_callback',
            'event'    => 'blur',
            'wrapper'  => 'main-class-' . $key,
            'method'   => 'replace',
            'effect'   => 'fade',
          ),
          '#parents'  => array('Allfieldsdata', strtolower($value->Label), $fvalue->id),
          '#prefix'   => '<div class="clearfix ' . $fvalue->name_default . '_field_set">',
          '#suffix'   => '</div>',
          '#required' => $required_state,
        );

        $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id . '_nid'] = array(
          '#type'          => 'hidden',
          '#default_value' => '0',
          '#attributes'    => array('class' => array('scm_request_field_' . $fvalue->id . '_nid', $fvalue->name_default . '_field_nid', strtolower($value->Label) . '_group_fileds')),
        );

        // Default Values when editing a request.
        if (!empty($form_state['triggering_element']['#value'])) {
          $new_field_id = _get_id_by_fieldid($fvalue->id, $form_state['triggering_element']['#value']);
          if (!empty($default_values[$new_field_id]->{'value'})) {
            $node_title = _get_node_title_by_nid($default_values[$new_field_id]->{'value'});
            $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#default_value'] = $node_title;

            $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id . '_nid']['#default_value'] = $default_values[$new_field_id]->{'value'};
          }
        }

        // Default Values when changing a company.
        if (isset($default_values_triggered)) {
          $comp_nid = _get_nid_by_title($default_values_triggered[$fvalue->id]);
          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#default_value'] = $default_values_triggered[$fvalue->id];

          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id . '_nid']['#default_value'] = $comp_nid;
        }
      }
      else {
        $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id] = array(
          '#type' => $fvalue->type,
          '#attributes' => array('class'=>array('scm_request_field_'.$fvalue->id, strtolower($value->Label).'_group_fileds',$fvalue->name_default . '_field'), 'placeholder'=>t($fvalue->Label)),
          '#parents' => array('Allfieldsdata', strtolower($value->Label), $fvalue->id),
          '#prefix' => '<div class="clearfix '.$fvalue->name_default . '_field_set">', 
          '#suffix' => '</div>',
          '#required' => $required_state,
        );

        if($fvalue->type=='select') {
          $options = array();
          $lines = explode(PHP_EOL, $fvalue->value);
          foreach($lines as $line) {
            $line = explode('|', $line);
            $options[$line[0]] = $line[1];
          }

          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#empty_option'] = 'Select ' . $fvalue->Label;
          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#options'] = $options;
          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#default_value'] = 0;
        }

        if($fvalue->type == 'checkbox') {
          if($fvalue->name_default == 'same-as-manufacturer'){
            $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#required'] = FALSE;
          }

          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#title']=t($fvalue->Label);

          if ($fvalue->Label == 'Direct Purchase Only') {
            $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#attributes'] = array('class'=>array('scm_request_field_' . $fvalue->id, strtolower($value->Label) . '_group_fileds', 'toggle-scm-vendor-section'), 'placeholder' => t($fvalue->Label));
          }

          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#default_value'] = 0;
        }

        if($value->size == '12') {
          unset($element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#title']);
          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#prefix'] = '<div class="clearfix">'; 

          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#suffix'] = '</div>'; 
        }

        // Default Values when editing a request.
        if (!empty($form_state['triggering_element']['#value'])) {
          $new_field_id = _get_id_by_fieldid($fvalue->id, $form_state['triggering_element']['#value']);
          if (!empty($default_values[$new_field_id]->{'value'})) {
            $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#default_value'] = $default_values[$new_field_id]->{'value'};
          }
        }

        // Default Values when changing a company.
        if (isset($default_values_triggered)) {
          $element['scm-request-request'][$key]['scm-request-' . $value->scm_group_key][$fkey]['scm_request_field_' . $fvalue->id]['#default_value'] = $default_values_triggered[$fvalue->id];
        }
      }
    }
  }
  return $element;
}

function _get_id_by_fieldid($id = '', $nid = '') {
  if (empty($id) || empty($nid)) {
    return NULL;
  }

  return db_select('m6connect_scm_settings_field_data', 'fid')
    ->fields('fid', array('id'))
    ->condition('fieldID', $id)
    ->condition('requestID', $nid)
    ->execute()
    ->fetchField();
}

function lineitem_data_datafunctionall($type, $id='') {
  global $user, $company;
  $query = db_select('m6connect_scm_settings_lineitem', 'n');
  $query->condition('n.nid', $company->nid, '=');
  $query->condition('n.type', $type, '=');
  if(!empty($id)){
    if($id=='all'){
      $query->fields('n');
      $uomlistoption = $query->execute()->fetchAll();
    } else {
      $query->fields('n');
      $query->condition('n.id', $id, '=');
      $uomlistoption = $query->execute()->fetchObject();
    }
  } else {
    $query->fields('n',array('id','title'));
    $uomlistoption = $query->execute()->fetchAllKeyed(0,1);
  }
  return $uomlistoption;
}

function add_item_invite_to_m6_process($element, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $storage = $form_state['add_small_items_storage'];
  $element['#storage'] = $storage;
  $allnecaa = array();
  if(!empty(lineitem_data_datafunctionall('NEC','all'))){
    $allnec = lineitem_data_datafunctionall('NEC','all');
    foreach($allnec as $neckey => $necval){
      $allnecaa[$necval->id] = $necval->necno.'|'.$necval->title;
    }
  }
  if (strpos($form_state['values']['scm-my-request-request-type'], '-1') !== false) {
    $required_state = TRUE;
  } else {
    $required_state = FALSE;
  } 
  $row = 0;
  foreach ($storage as $key => $uniqId) {
    $key++;
    $element['line_item_number'][$uniqId] = array(
      '#type' => 'textfield', 
      '#attributes'=> array('class'=> array('form-control','workflow-auto','line_item_number','numbersOnly'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'line_item_number'),
      '#default_value' => $key,
    );
    $element['line_master_number'][$uniqId] = array(
      '#type' => 'textfield', 
      '#attributes'=> array('class'=> array('form-control','workflow-auto','line_master_number','numbersOnly'),'datarow'=>array($row),'placeholder'=>'Line master number'),
      '#parents' => array('alert',$uniqId,'line_master_number'),
    );
    $element['nec_number'][$uniqId] = array(
      '#type' => 'select',
      '#options' => $allnecaa,
      '#default_value' => '',
      '#empty_option'=>'Select NEC Code',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','nec_number'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'nec_number'),
    );
    $element['purchase_unit_of_measure'][$uniqId] = array(
      '#type' => 'select', 
      '#options' => lineitem_data_datafunctionall('UOM'),
      '#empty_option'=>'Select',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','purchase_unit_of_measure'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'purchase_unit_of_measure'),
      '#required' => $required_state,
    );  
    $element['uom_conversion'][$uniqId] = array(
      '#type' => 'textfield',   
      '#attributes'=> array('class'=> array('form-control','workflow-auto','uom_conversion','numbersOnly'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'uom_conversion'),
      '#required' => $required_state,
    );  
    $element['purchase_uom_conversion'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','purchase_uom_conversion','numbersOnly'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'purchase_uom_conversion'),
      '#required' => $required_state,
    );

    $newunitprice = str_replace('$', '', $form_state['input']['alert'][$uniqId]['purchase_uom_conversion'])/$form_state['input']['alert'][$uniqId]['uom_conversion'];
    $element['price_each'][$uniqId] = array(
      '#type' => 'markup', 
      '#markup' => '$'.number_format((float)$newunitprice, 2, '.', ''),
      '#attributes'=> array('class'=> array('form-control','workflow-auto','price_each')),
      '#parents' => array('alert',$uniqId,'price_each'),
      '#prefix' => '<div id="get_price_each_'.$row.'">',
      '#suffix' => '</div>',
    );
    $element['manufacture_catalog_number'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','manufacture_catalog_number'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'manufacture_catalog_number'),
      '#required' => $required_state,
    );
    $element['vendor_catalog'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','vendor_catalog'),'datarow'=>array($row)),
      '#parents' => array('alert',$uniqId,'vendor_catalog'),
    );
    $element['add_item_description'][$uniqId] = array(
        '#type' => 'textfield', 
        '#default_value' => '',     
        '#attributes'=> array('class'=> array('form-control','workflow-auto','add_item_description'),'datarow'=>array($row)),
        '#parents' => array('alert',$uniqId,'add_item_description'),
    );
    $actiontext = 'Actions';
    if(!empty($stdefault['ACTION'])) {
      $actiontext = ucwords($stdefault['ACTION']);
    }
    $element['remove'][$uniqId]['1'] = array(
      '#type' => 'select',
      '#options' => array('approved'=>'Approved','denied'=>'Denied','pending'=>'Pending'),
      '#default_value' => '',
      //'#empty_option'=>'Action',
      '#attributes'=> array('style'=> array('position: absolute;top: 0;opacity: 0;'),'class'=>array('alert-container-section', 'workflow-action','workflow-action-actionselect')),
      '#parents' => array('alert',$uniqId,'remove'),
       '#prefix' => '<div style="position: relative;" class="prant_class_action_additem" id="idadd_'.$uniqId.'"><button id="dLabel" class="btn btn-success get-actiondata" type="button" aria-haspopup="true" aria-expanded="false" style="float: left;width: 57px;padding: 5px;font-size: 13px;text-transform: capitalize;"> '.$actiontext.'</button>',
      '#suffix' => '</div>',
    );
//<i class="fa fa-trash-o get-removed" aria-hidden="true" style="font-size:24px; cursor:pointer;"></i>
    $element['remove'][$uniqId]['2'] = array(
      '#type' => 'submit',
      '#value' => 'remove_lineItem',
      '#name' => $uniqId,
      '#attributes'=> array('style'=> array('font-family:FontAwesome;'),'class'=>array('alert-container-section', 'workflow-remove-submit')),
      '#parents' => array('alert2', $uniqId, 'remove'),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_add_items_m6_row_handler'),
        '#ajax' => array(
          'callback' => 'remove_add_items_row_callback',
          'wrapper' => 'alert-container-section',
          'method' => 'replace',
          'effect' => 'fade',
          'progress' => array('type'=> 'throbber', 'message'=> NULL),
        ),
      '#prefix' => '<div><i class="fa fa-trash-o get-removed" aria-hidden="true" style="font-size:24px; cursor:pointer;"></i>',
      '#suffix' => '</div>',    
    );
    if(isset($form_state['add_small_items_storage_value'][$uniqId])) {
      $stdefault = $form_state['add_small_items_storage_value'][$uniqId];
      $element['line_item_number'][$uniqId]['#default_value'] = $stdefault['LIN'];
      $element['line_master_number'][$uniqId]['#default_value'] = $stdefault['IMN'];
      $element['nec_number'][$uniqId]['#default_value'] = $stdefault['NEC'];
      $element['purchase_unit_of_measure'][$uniqId]['#default_value'] = $stdefault['PUM'];
      $element['uom_conversion'][$uniqId]['#default_value'] = $stdefault['UC'];
      $element['purchase_uom_conversion'][$uniqId]['#default_value'] = $stdefault['PUP'];
      $element['price_each'][$uniqId]['#markup'] = '$'.number_format((float)$stdefault['UP'], 2, '.', '');
      $element['manufacture_catalog_number'][$uniqId]['#default_value'] = $stdefault['MCAT'];
      $element['vendor_catalog'][$uniqId]['#default_value'] = $stdefault['VCAT'];       
      $element['add_item_description'][$uniqId]['#default_value'] = $stdefault['ID'];
      $element['remove'][$uniqId]['#default_value'] = $stdefault['ACTION'];         
    }
    $row++;    
  } 
  $element['workflow_add_new_row'] = array(
    '#type'=>'submit',
    '#value' => 'Add New',
    '#name' => 'workflow_add_new_row',
    '#attributes'=> array('class'=>array('routing-workflow-action','commitment-workflow-action-add-po-details'),'title'=>'Add New Detail'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('add_items_row_submit_handler_invite_m6'),
    '#ajax' => array(
      'callback' => 'add_items_row_invite_m6_action_callback',
      'wrapper' => 'alert-container-section',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
  );
  return $element;
}

function remove_add_items_row_callback(&$form, &$form_state) {
  return $form['outer-container']['main_container2'];
}

function remove_add_items_m6_row_handler(&$form,&$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];
  if(isset($form_state['add_small_items_storage'])){
    foreach ($form_state['add_small_items_storage'] as $key => $value) {
      if($form_state['add_small_items_storage'][$key] == $identifier){
        unset($form_state['add_small_items_storage'][$key]);
        unset($form_state['po_storage_default_value'][$identifier]);
      } 
    }             
  }   
  $form_state['rebuild'] = TRUE;
}

function add_items_row_submit_handler_invite_m6(&$form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];
  if($triggerElement['#name'] =='workflow_add_new_row'){
    $tempIdentifer = uniqid();
    $form_state['add_small_items_storage'][]  = $tempIdentifer;
  }
  $form_state['rebuild'] = TRUE;
}

function add_items_row_invite_m6_action_callback(&$form, &$form_state) {
  return $form['outer-container']['main_container2'];
}

function get_scm_add_items_table_data() {
  $rows = array();
  $header = array(
    array('data'=>'SCR Number','class'=>array('text-center')),
    array('data'=>'Due Date','class'=>array('text-center')),
    array('data'=>'Add Item Type','class'=>array('text-center')),
    array('data'=>'Description','class'=>array('text-center')),
    array('data'=>'Requestor','class'=>array('text-center')), 
    array('data'=>'Category','class'=>array('text-center')),
    array('data'=>'Project Manager','class'=>array('text-center')),
    array('data'=>'Status','class'=>array('text-center')),
    array('data'=>'Action','class'=>array('text-center')),
  );
  $getItemsNodes = _getting_table_data_call('scm_add_items');
  foreach($getItemsNodes as $ids => $values){ 
    $itemsNodes = node_load($values);  
  $rows[] = array(
      'data' => array(
      array('data' => l('<span class="commitment-nu-cust">'.$itemsNodes->title.'</span>', 'edit/'.$values.'/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' => $values))),'class' => array('text-left')),
      array('data' => $itemsNodes->field_item_effective_date['und'][0]['value'],'class' => array('text-center')),
        array('data' => $requestNodes->field_add_item_type['und'][0]['value'],'class' => array('text-center')),
      array('data' => $requestNodes->body['und'][0]['value'],'class' => array('text-left')),
        array('data' => $requestNodes->field_requester_to['und'][0]['value'].'<br>'.$requestNodes->field_requester_from['und'][0]['value'],'class' => array('text-center')),
        array('data' => 'None','class' => array('text-center')),
        array('data' => 'None','class' => array('text-center')),
        array('data' => 'Active','class' => array('text-left')),
        array('data' => _get_action_button($values, 'scm_add_items'),'class' => array('text-center')),
      ),
    );
  }  
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table','table-hover','table-bordered','text-center', 'm6init-datatable')))); 
  return $output;      
}

/**
 * Function to get container for chatting in SCM.
 */
function scm_chatting_container() {
  return user_messaging_callback();
}

/*****
Common Functions
*****/
function scm_current_user_by_company() {
  global $user, $company;
  $query = db_select('m6connect_scm_settings_user_database', 'n');
  $query->join('m6connect_scm_messaging_connect_users', 'uc', 'n.id = uc.user_uid');
  $query->fields('n');
  $query->fields('uc');
  $query->condition('n.companyID', $company->nid, '=');
  $query->condition('n.userID', $user->uid, '=');
  $query->condition('uc.service', 'scm', '=');
  $result = $query->execute()->fetchAll();
  return $result;
}

/**
 * Autocompletet ajax callback.
 */
function scm_my_request_autocomplete_callback($form, &$form_state) {
  // We have to return this element.
  $return_element = '';
  if (!empty($form_state['triggering_element']['#array_parents'])) {
    $return_key = $form_state['triggering_element']['#array_parents'][3];
    $return_element = $form_state['triggering_element']['#array_parents'][4];
  }

  if (!empty($return_element) && isset($form['outer-container']['main_containerupper']['scm-request-request'][$return_key][$return_element])) {
    return $form['outer-container']['main_containerupper']['scm-request-request'][$return_key][$return_element];
  }
  return;
  // $commands = array();
  
  // if (!empty($form_state['triggering_element']['#value'])) {
  //   $nid = _get_nid_by_title($form_state['triggering_element']['#value']);
  //   if (!empty($nid)) {
  //     $input_array = $form_state['triggering_element']['#array_parents'];
  //     if (!empty($input_array)) {
  //       $input_element = end($input_array);
  //       $input_element .= '_nid';
  //     }
  //     $sectiontr = '';
  //     if( strpos( $input_array[3], '-manufacturer_' ) !== false ){
  //       $sectiontr = 'manufacturer';
        
  //     } elseif( strpos( $input_array[3], '-vendor_' ) !== false ) {
  //       $sectiontr = 'vendor';
  //     }
  //     $companyload = node_load($nid);
  //     $commands[] = ajax_command_invoke('.'.$sectiontr.'_group_fileds.contact-name_field', 'val', array($companyload->field_owner_name['und'][0]['value']));
  //     $commands[] = ajax_command_invoke('.'.$sectiontr.'_group_fileds.contact-email_field', 'val', array($companyload->field_company_email['und'][0]['email']));
  //     $commands[] = ajax_command_invoke('.'.$sectiontr.'_group_fileds.contact-phone_field', 'val', array($companyload->field_org_phone['und'][0]['value']));
  //     $commands[] = ajax_command_invoke('.'.$sectiontr.'_group_fileds.contract-number_field', 'val', array($companyload->field_contract_number['und'][0]['value']));

  //     $commands[] = ajax_command_invoke('input[name="'. $input_element . '"]', 'val', array($nid));
  //   }
  // }
  // return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Helper function to prepare form_state when editing a request.
 */
function _edit_my_request_callback_prepare(&$form_state) {
  global $base_url;
  $form_state['input'] = array();
  // Setting the new request number in session.
  unset($_SESSION['scr_request']);
  $_SESSION['scr_request'] = $form_state['triggering_element']['#value'];

  // Getting the node.
  $node = node_load($form_state['triggering_element']['#value']);

  // Preparing data for main_container2.
  $form_state['add_small_items_storage'] = array();
  $items = field_get_items('node', $node, 'field_add_item_number');

  foreach ($items as $item) {
    $fc = field_collection_field_get_entity($item);

    $unitprice = $fc->field_scm_purchase_uom_price['und'][0]['value']/$fc->field_scm_uom_converstion['und'][0]['value'];
    $tempIdentifer = uniqid();
    $form_state['add_small_items_storage'][]  = $tempIdentifer;
    $form_state['add_small_items_storage_value'][$tempIdentifer] = array(
      'LIN'    =>  isset($fc->field_scm_line_item_number['und'])?$fc->field_scm_line_item_number['und'][0]['value']:'',
      'IMN'    =>  isset($fc->field_scm_item_master_number['und'])?$fc->field_scm_item_master_number['und'][0]['value']:'',    
      'NEC'    =>  isset($fc->field_line_item_nec['und'])?$fc->field_line_item_nec['und'][0]['value']:'',
      'PUM'    =>  isset($fc->field_scm_price_unit_measure_uom['und'])?$fc->field_scm_price_unit_measure_uom['und'][0]['value']:'',    
      'UC'     =>   isset($fc->field_scm_uom_converstion['und'])?$fc->field_scm_uom_converstion['und'][0]['value']:'',
      'PUP'    =>  isset($fc->field_scm_purchase_uom_price['und'])?$fc->field_scm_purchase_uom_price['und'][0]['value']:'',
      'UP'     =>   $unitprice,
      'MCAT'   => isset($fc->field_manufacture_catalog_number['und'])?$fc->field_manufacture_catalog_number['und'][0]['value']:'',
      'VCAT'   => isset($fc->field_vendor_catalog_number['und'])?$fc->field_vendor_catalog_number['und'][0]['value']:'',
      'ID'     =>   isset($fc->field_scm_item_description['und'])?$fc->field_scm_item_description['und'][0]['value']:'',
      'ACTION' =>   isset($fc->field_item_action['und'])?$fc->field_item_action['und'][0]['value']:'',
    );
  }

  // Preparing data for main-container
  $storage_project = array(
    'scr-id' => $node->nid,
    'scr-number' => $node->title,
    'description' => !empty($node->body['und'][0]['value']) ? $node->body['und'][0]['value']: '',
    'request-date' => !empty($node->field_request_date['und'][0]['value']) ? $node->field_request_date['und'][0]['value'] : '',
    'entity' => !empty($node->field_entity['und'][0]['value']) ? $node->field_entity['und'][0]['value'] : '',
    'department' => !empty($node->field_department['und'][0]['value']) ? $node->field_department['und'][0]['value'] : '',
    'department-approver' => !empty($node->field_department_approver['und'][0]['value']) ? $node->field_department_approver['und'][0]['value'] : '',
    'approver-email' => !empty($node->field_approver_email['und'][0]['value']) ? $node->field_approver_email['und'][0]['value'] : '',
    'request-type' => !empty($node->field_request_type['und'][0]['value']) ? $node->field_request_type['und'][0]['value'] : '',
    'request-subtype' => !empty($node->field_request_subtype['und'][0]['value']) ? $node->field_request_subtype['und'][0]['value'] : '',
    'priority-level' => !empty($node->field_priority_level['und'][0]['value']) ? $node->field_priority_level['und'][0]['value'] : '',
    'priority-frozen' => !empty($node->field_priority_frozen['und'][0]['value']) ? $node->field_priority_frozen['und'][0]['value'] : '',
    'category' => !empty($node->field_category['und'][0]['value']) ? $node->field_category['und'][0]['value'] : '',
    'sub-category' => !empty($node->field_sub_category['und'][0]['value']) ? $node->field_sub_category['und'][0]['value'] : '',
    'supply-chain-lead' => !empty($node->field_supply_chain_lead['und'][0]['value']) ? $node->field_supply_chain_lead['und'][0]['value'] : '',
    'material-manager' => !empty($node->field_materials_manager_ref['und'][0]['value']) ? $node->field_materials_manager_ref['und'][0]['value'] : '',
    'project-status' => !empty($node->field_project_status['und'][0]['value']) ? $node->field_project_status['und'][0]['value'] : '',
    'requester-db-ref' => !empty($node->field_requestordb_ref['und'][0]['value']) ? $node->field_requestordb_ref['und'][0]['value'] : '',
    'requester-first-name' => !empty($node->field_requester_to['und'][0]['value']) ? $node->field_requester_to['und'][0]['value'] : '',
    'requester-last-name' => !empty($node->field_requester_from['und'][0]['value']) ? $node->field_requester_from['und'][0]['value'] : '',
    'on-behalf-fn' => !empty($node->field_requested_on_behalf_of['und'][0]['value']) ? $node->field_requested_on_behalf_of['und'][0]['value'] : '',   
    'on-behalf-ln' => !empty($node->field_requested_on_behalf_of_fro['und'][0]['value']) ? $node->field_requested_on_behalf_of_fro['und'][0]['value'] : '',
    'effective_date' => !empty($node->field_scm_effective_date['und'][0]['value']) ? $node->field_scm_effective_date['und'][0]['value'] : '',
    'closeout_date' => !empty($node->field_scm_closeout_date['und'][0]['value']) ? $node->field_scm_closeout_date['und'][0]['value'] : '',
    'scm-my-request-closeoutremarks' => !empty($node->field_scm_request_closeoutremark['und'][0]['value']) ? $node->field_scm_request_closeoutremark['und'][0]['value'] : '',
  );

  $fileModuleIconPath = $base_url . '/' . drupal_get_path('module','file').'/icons/';
  $fileIconPath = array(
    'image'    => $fileModuleIconPath . 'image-x-generic.png',
    'pdf'      => $fileModuleIconPath . 'application-pdf.png',
    'document' => $fileModuleIconPath . 'x-office-document.png',
    'text'     => $fileModuleIconPath . 'text-plain.png',
  );

  // Preparing attachments.
  $attachmentshtml = '';

  if (!empty($node->field_my_request_attachment['und'])) {
    foreach ($node->field_my_request_attachment['und'] as $addKey => $addVal) {
      $getFid = $addVal['fid'];
      $filetype= $addVal['type'];
      if (isset(explode('/', $addVal['filemime'])[1]) && explode('/', $addVal['filemime'])[1] == 'pdf') {
        $filetype= explode('/',$addVal['filemime'])[1];
      }

      $deletelink ='' ;
      if(!isset($_SESSION['login-mail']) && empty($_SESSION['login-mail'])) {
        $deletelink = '<i class="fa fa-times padding-5" style="cursor:pointer;"></i>';
        $delete_checkbox = '<input type="checkbox" checked="checked"  class="image-remove-update sr-only" value="'.$getFid.'" for="'.$node->nid.'" fortitle="'.$addVal['filename'].'">';
      }
      $attachmentshtml[] = '<p id="getfileID_'.$getFid.'" class="text-left"><label class="checkbox removdeletefile">'.$deletelink.'<span><img src="'.$fileIconPath[$filetype].'"></span>'.$delete_checkbox.l($addVal['filename'], file_create_url($addVal['uri'])).'</label></p>';
    }
  }

  $storage_project['attachmentshtml'] = $attachmentshtml;

  // Getting options for select boxes which are dependent.
  $form_state['default_values']['select_options'] = array();

  // Getting options for Request SubType based on Request.
  $form_state['default_values']['select_options']['request_subtype'] = array();
  if (!empty($storage_project['request-type'])) {
    $reqType = explode('-', $storage_project['request-type']);
    
    if(!empty($reqType[1])) {
      $form_state['add-to-item-custom'] = 'TRUE';
    } else {
      $form_state['add-to-item-custom'] = 'FALSE';
    }

    // Getting subtype options.
    $requesttypeid = str_replace("-", "", $storage_project['request-type']);

    if (strpos($storage_project['request-type'], '-1') !== false) {
      $requesttypeid = str_replace("-1","",$storage_project['request-type']);
    }

    $request_sub_options = _get_request_sub_type_from_settings_by_typebymailcat($requesttypeid);
    if (!empty($request_sub_options)) {
      $form_state['default_values']['select_options']['request_subtype'] = $request_sub_options;
    }
  }

  // Getting Justification text field settings.
  $form_state['frozen_defaults']['style_justification'] = 'display:none;';
  $form_state['frozen_defaults']['justification_required'] = FALSE;
  
  if (!empty($storage_project['priority-level'])) {
    if ($storage_project['priority-level'] == 'critical') {
      $form_state['frozen_defaults']['justification_required'] = TRUE;
      $form_state['frozen_defaults']['style_justification'] = 'display:block;'; 
    }
    else {
      $form_state['frozen_defaults']['justification_required'] = FALSE;
      $form_state['frozen_defaults']['style_justification'] = 'display:block;';
    }
  }

  // Getting subcategories.
  $form_state['sub_category_fetch_options'] = $form_state['default_sub_val'] = array();
  if (!empty($storage_project['category'])) {
    $sub_categories_all = _get_all_sub_categories_scm_keyed($storage_project['category']);
    $form_state['sub_category_fetch_options'] = $sub_categories_all;
  }

  // Getting Supply Chain Lead.
  $form_state['supply_chain_lead_fetch_options'] = '';
  // Checking if we have a supply chain lead, if yes, then fine, else checking
  // categories.
  if (!empty($storage_project['supply-chain-lead'])) {
    $form_state['supply_chain_lead_fetch_options'] = $storage_project['supply-chain-lead'];
  }

  // If we do not have a SCL, then first checking if a sub category is 
  // available, first preference is sub category, then main category.
  if (!empty($storage_project['sub-category'])) {
    $scl_uid = _get_main_cat_scl($storage_project['sub-category']);
    if (!empty($scl_uid)) {
      $form_state['supply_chain_lead_fetch_options'] = $scl_uid;
    }
  }

  // If we do not have a sub category, but have main category.
  if (!empty($storage_project['category'])) {
    $scl_uid = _get_main_cat_scl($storage_project['category']);
    if (!empty($scl_uid)) {
      $form_state['supply_chain_lead_fetch_options'] = $scl_uid;
    }
  }

  // Preparing material managers.
  // If material manager is not available and we have an entity then getting
  // material managers.
  if (empty($storage_project['material-manager']) && !empty($storage_project['entity'])) {
    // If all entities are selected, then dealing it that way.
    if ($storage_project['entity'] == 'all') {
      $entities = _getting_table_data_call('scm_setting_location_entity');
    }
    else {
      $entities = explode(', ', $storage_project['entity']);
    }

    foreach ($entities as $k => $v) {
      $entityload = node_load($k);
      if (!empty($entityload->field_entity_materials_manager['und'][0]['value'])) {
        // If we have material managers at least.
        $material_manageruids = explode('|', $entityload->field_entity_materials_manager['und'][0]['value']);

        foreach ($material_manageruids as $key => $value){
          $account = user_load($value);
          if(_is_user_material_manager(FALSE, $account)) {
            $material_managernames[] = _get_user_full_name($account->uid, $account);
          }
        }

        if (!empty($material_managernames)) {
          $materials_user_names = implode(', ', $material_managernames);
          $storage_project['material-manager'] = $materials_user_names;
        }
      }
    }
  }
  // And if material manager is available, then setting it.
  if (!empty($storage_project['material-manager'])) {
    $material_manageruids = explode('|', $storage_project['material-manager']);
    foreach ($material_manageruids as $key => $value){
      $account = user_load($value);
      if(_is_user_material_manager(FALSE, $account)) {
        $material_managernames[] = _get_user_full_name($account->uid, $account);
      }
    }

    if (!empty($material_managernames)) {
      $materials_user_names = implode(', ', $material_managernames);
      $storage_project['material-manager'] = $materials_user_names;
    }
  }


  // We have imploded data of several fields, making them in array.

  // Entity.
  if (!empty($storage_project['entity'])) {
    $storage_project['entity'] = explode(', ', $storage_project['entity']);
  }

  // Setting default values for main-container in form_state.
  $form_state['default_values']['main_container'] = $storage_project;

  // Preparing data for main_containerupper.
  $d = get_all_custom_fieldsBY_reqestID($node->nid);
  if (!empty($d)) {
    $form_state['default_values']['main_containerupper'] = $d;
  }
}