<?php
/*
 * Start work for share after question section
 */
function scm_question_builder_share_content($where = '') {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10 margin-top-10">',
      '#suffix' => '</div>',
    );
  }
  $elements['menu-links'] = array(
    '#markup' => $where == 'new_scorecard' ? scm_scorecard_sub_menu_links_content() : scm_scorecard_dashboard_menu_links_content($where),
    '#prefix' => $where == 'new_scorecard' ? '<div class="clearfix csemanager-sub-menu margin-top-10 margin-bottom-10">' : '<div class="clearfix scm-main-menu margin-bottom-45">',
    '#suffix' => '</div>',
  );
  $elements['project-form']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_share_evaluate_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['share-listing'] = array(
    '#markup' => _get_share_summary_table_data($where),
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="share-summary-listing" id="scorecard-share-information-listing">',
    '#suffix' => '</div></div></div>',
  );
  return $elements; 
}

function _casemanager_share_evaluate_form($form, &$form_state) {
  global $user,$company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  $style = isset($form_state['scorecardId'])?'style="display:none";':'';    
  // Adding hidden Dropdown list for all added scorecard
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->fields('n', array('nid', 'title'));
  $query->condition('om.gid', $company->nid, '=');
  $query->condition('n.type', 'scorecard_share','=');
  $scorecardsList = $query->execute()->fetchAllKeyed(0,1);

  $form['save-scorecard-node'] = array(
    '#type' => 'select',
    '#options' => $scorecardsList,
    '#attributes' => array('class'=> array('form-control project-scorecard-sel-list')),
    '#ajax' => array(
      'callback'=> 'project_scorecard_sel_list_callback',
      'wrapper' => 'questionbuilder_scorecard_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );

  $form['main-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix scm-scorecard"><div id="questionbuilder_scorecard_main_container_main" class="row">',
    '#process' => array('share_main_container_process'),
  );

  $form['main-container2'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix scm-scorecard"><div id="questionbuilder_scorecard_main_container" class="clearfix">',
    '#process' => array('share_user_main_container_process'),
  );

  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }

  $form['actions'] = array(
    '#type' => 'actions',
    '#prefix' => '<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix custom-submit-select-pro-button '.$sharerecommendation.'">',
    '#suffix' => '</div></div></div></div></div></div>',
  );
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#attributes' => array('class'=> array('scm-share-submit')),
    '#value' => 'Share',
    '#submit'=> array('scm_share_submit'),
  );

  if(isset($form_state['scorecardId'])) {
    $form['actions']['reset'] = array(
      '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    );
  }
  else {
    $form['actions']['reset'] = array(
      '#type' => 'markup',
      '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button cancel-share-edit-form">',
    );
  }

  return $form;
}

function project_scorecard_sel_list_callback($form,&$form_state) {
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  if(!empty($triggeringElement['#value']) && $form_state['triggering_element']['#name'] == 'save-scorecard-node'){
    $scoreCard = node_load($triggeringElement['#value']);
  // getting all the shared users and 
  // set it to share with text field
  $userArr = array();
  foreach($scoreCard->field_share_with_user['und'] as $delta => $userId) {
    $userArr[] = $userId['value'];
  }
  foreach($scoreCard->field_share_with_team['und'] as $delta => $userId) {
    $teamArr[] = $userId['value'];
  }
    $storage_project = array(
      'shareWith' => $userArr,
      'shareWithTeam' => $teamArr,
      'message' => isset($scoreCard->field_share_with_message['und'])?$scoreCard->field_share_with_message['und'][0]['value']:'',
      'dueDate' => isset($scoreCard->field_rating_due_date['und']) ? date('Y-m-d', strtotime($scoreCard->field_rating_due_date['und'][0]['value'])) : '',
      'sendEmail' => isset($scoreCard->field_email_notification['und'])?$scoreCard->field_email_notification['und'][0]['value']:'',
    );

    // Adding prefixes to default values to.
    $user_options_default = $team_options_default = array();
    if (!empty($storage_project['shareWith'])) {
      $user_options_default = $storage_project['shareWith'];
      array_walk($user_options_default, 'append_prefix_to_array', 'user');
    }
    if (!empty($storage_project['shareWithTeam'])) {
      $team_options_default = $storage_project['shareWithTeam'];
      array_walk($team_options_default, 'append_prefix_to_array', 'team');
    }

    $share_options_default = array_merge($user_options_default, $team_options_default);

    $commands[] = ajax_command_invoke("select.project_programe_reports_sections", 'val',array($share_options_default)); 
    $commands[] = ajax_command_invoke("select.project_programe_reports_sections", 'trigger',array('change')); 

    $commands[] = ajax_command_invoke("textarea.vendor-message", 'val',array($storage_project['message']));
    $commands[] = ajax_command_invoke("input.vendor-due-date", 'val',array($storage_project['dueDate']));
    $commands[] = ajax_command_invoke("input.node-edit-nid", 'val',array($scoreCard->nid));
  if($storage_project['sendEmail'] == 1){
      $commands[] = ajax_command_invoke('.invoice_reconciled input[type="checkbox"]', 'attr',array('checked', 'true')); 
    }
    else{
      $commands[] = ajax_command_invoke('input[type="checkbox"].invoice_reconciled','removeAttr',array('checked')); 
    }
  }
  else {
    $commands[] = ajax_command_invoke("select.project_programe_reports_sections", 'val',array($userArr));   
    $commands[] = ajax_command_invoke("textarea.vendor-message", 'val',array($storage_project['message']));
    $commands[] = ajax_command_invoke("input.vendor-due-date", 'val',array($storage_project['dueDate']));
    $commands[] = ajax_command_invoke('input[type="checkbox"].invoice_reconciled','removeAttr',array('checked'));     
    $commands[] = ajax_command_invoke("input.node-edit-nid", 'val',array(''));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function share_main_container_process($element, &$form_state) {
  global $company;
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight' => 3,
  );
  $cls = isset($form_state['scorecardId'])?'dispaly_none':'well well-large no-bg';
  $element['main-container']['full-container']['inner-left-one']= array(
    '#type' => 'container',
    //'#attributes' => array('class'=>array('well','well-large','no-bg')),
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-info-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix custom-score-info"><div class="row">',
    '#prefix' => '<div class="'.$cls.'">'
  );
  
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $getAllScoreCards = _fetching_scorecard_information_evaluate('scm_scorecard',$company->nid);
  
  // Getting all the scorecard 
  // with there name and number
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->join('field_data_field_scorecard_name', 'scn','scn.entity_id = n.nid');
  $query->fields('n', array('nid','title'));
  $query->fields('scn', array('field_scorecard_name_value')); 
  $query->condition('n.type','scm_scorecard','=');  
  $query->condition('om.gid', $company->nid, '=');
  $query->orderBy('n.nid', 'DESC');
  $getAllScards = $query->execute()->fetchAll();
  $scardArr = array();
  foreach($getAllScards as $delta => $scrdInfo) {
    $scardArr[$scrdInfo->nid] = $scrdInfo->title.' | '.$scrdInfo->field_scorecard_name_value;  
  }
  
  $scoreCardData = node_load($getNodesNids);
  $ratingDate = strtotime($scoreCardData->field_rating_due_date['und'][0]['value']);
  $awardDate = strtotime($scoreCardData->field_recommendation_to_award_da['und'][0]['value']);
  $element['scorecard-nid-entry'] = array(
    '#type' => 'hidden', 
  '#value' => $getNodesNids,
    '#attributes'=> array('class'=> array('scorecard-nid-entry')),
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-number-select'] = array(
    '#type' => 'select',
    '#options' => $scardArr,
    '#empty_option' => 'Choose scorecard',
  '#default_value' => $getNodesNids,
    '#attributes' => array('class'=> array('form-control scorecard-name-title')),
    '#prefix' => '<div class="col-md-5 col-sm-5 col-xs-12"><div class="clearfix"><p class="blue-and-bold">Select Scorecard</p>',
    '#suffix' => '</div></div>',  
    '#ajax' => array(
      'wrapper' => 'replace-facility-options-here',
      'callback' => '_update_scorecard_based_data_view_share',
    ),
  );
  /*$element['main-container']['full-container']['inner-left-one']['scorecard-number'] = array(
  '#markup' => '<p class="blue-and-bold">Scorecard Number</p><p class="rfp-data-date">'.$scoreCardData->title.'</p>',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );*/
  $element['main-container']['full-container']['inner-left-one']['scorecard-name'] = array(
  '#markup' => '<p class="blue-and-bold">Scorecard Name</p><p class="rfp-data-date">'.$getAllScoreCards[$getNodesNids].'</p>',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );
  /*$element['main-container']['full-container']['inner-left-one']['rating-date'] = array(
  '#markup' => '<p class="blue-and-bold">Rating Due Date</p><p class="rfp-data-date">'.date('m/d/Y',$ratingDate).'</p>',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );*/
  $element['main-container']['full-container']['inner-left-one']['project-name'] = array(
    '#markup' => '<p class="blue-and-bold">Project Name</p><p class="prject-data-name">'.(!empty($scoreCardData->field_project_nid_for_scm['und'][0]['value'])?_get_title_of_node($scoreCardData->field_project_nid_for_scm['und'][0]['value']):'').'</p>',
    '#prefix' => '<div class="col-md-2 col-sm-2 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );
  $element['main-container']['full-container']['inner-left-one']['rfp-name'] = array(
    '#markup' => '<p class="blue-and-bold">RFP Name</p><p class="rfp-data-name">'.(!empty($scoreCardData->field_rfp_nid_for_scm['und'][0]['value'])?_get_title_of_node($scoreCardData->field_rfp_nid_for_scm['und'][0]['value']):'').'</p>',
    '#prefix' => '<div class="col-md-2 col-sm-2 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type' => 'markup',
    '#markup' => '</div></div></div>',
  );
  
  return $element;
}

function share_scorecard_callback($scoreCard, $ajax = TRUE) {
  global $company;
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $getAllScoreCards = _fetching_scorecard_information_evaluate('scm_scorecard',$company->nid);
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'title' => $getAllScoreCards[$getNodesNids],
      'scorecardId' => $scoreCard,
    );
    $output = ctools_modal_form_wrapper('_casemanager_share_evaluate_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }    
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('_casemanager_share_evaluate_form');
  } 
}

function share_user_main_container_process($element, &$form_state) {
  global $company;
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $getAllScoreCards = _fetching_scorecard_information_evaluate('scm_scorecard',$company->nid);
  /****/
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));  
  $query->join('field_data_field_scorecard_reference','sr','sr.entity_id = n.nid');  
  $query->fields('n', array('nid'));
  $query->condition('n.type','scorecard_share','=');  
  $query->condition('om.gid', $company->nid, '=');
  $query->condition('sr.field_scorecard_reference_nid', $getNodesNids, '=');
  $getscore = $query->execute()->fetchField();

  $scoreCard = node_load($getscore);
  // getting all the shared users and 
  // set it to share with text field
  $userArr = $teamArr = array();
  
  foreach($scoreCard->field_share_with_user['und'] as $delta => $userId) {
    $userArr[] = $userId['value'];
  }
  foreach($scoreCard->field_share_with_team['und'] as $delta => $userId) {
    $teamArr[] = $userId['value'];
  }

  $storage_project = array(
    'shareWith' => $userArr,
    'shareWithTeam' => $teamArr,
    'message' => isset($scoreCard->field_share_with_message['und'])?$scoreCard->field_share_with_message['und'][0]['value']:'',
    'dueDate' => isset($scoreCard->field_rating_due_date['und']) ? date('m/d/Y', strtotime($scoreCard->field_rating_due_date['und'][0]['value'])) : '',
    'sendEmail' => isset($scoreCard->field_email_notification['und'])?$scoreCard->field_email_notification['und'][0]['value']:'',
  );
  
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight' => 3,
  );

  $cls2 = isset($form_state['scorecardId'])? '' : 'well well-large';

  $heading = isset($form_state['scorecardId'])?'':'<h4>'.$getAllScoreCards[$getNodesNids].'</h4>';

  $element['main-container']['full-container']['inner-left-one']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array($cls2)),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-info-title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="clearfix">'.$heading.'</div><div class="clearfix"><div class="qbuilder-scorinfo margin-5 clearfix">',
  );

  // Getting all vendor names.
  $getVendorName = _get_user_mappping_by_group_company_nid($company->nid);

  $user_options = $team_options = array();

  // Appending prefix to user names.
  if (!empty($getVendorName)) {
    $options_flipped = array_flip($getVendorName);
    array_walk($options_flipped, 'append_prefix_to_array', 'user');

    $user_options = array_flip($options_flipped);
    unset($options_flipped);
  }

  // Getting all teams of the current scorecard's project.
  $all_teams = _get_all_teams_by_scorecard();

  if (!empty($all_teams)) {
    $options_flipped = array_flip($all_teams);
    array_walk($options_flipped, 'append_prefix_to_array', 'team');

    $team_options = array_flip($options_flipped);
    unset($options_flipped);

    $options = array(
      t('Teams') => $team_options,
      t('Individual Users') => $user_options,
    );
  }
  else {
    $options = array(
      t('Individual Users') => $user_options,
    );
  }

  // Adding prefixes to default values to.
  $user_options_default = $team_options_default = array();
  if (!empty($storage_project['shareWith'])) {
    $user_options_default = $storage_project['shareWith'];
    array_walk($user_options_default, 'append_prefix_to_array', 'user');
  }
  if (!empty($storage_project['shareWithTeam'])) {
    $team_options_default = $storage_project['shareWithTeam'];
    array_walk($team_options_default, 'append_prefix_to_array', 'team');
  }

  $share_options_default = array_merge($user_options_default, $team_options_default);

  $select_prefix = '<div class="input-group-btn text-right"><button type="button" class="btn btn-default">Share With: </button></div>';

  $element['main-container']['full-container']['inner-left-one']['vendor-selections'] = array(
    '#type'       => 'select',
    '#options'    => $options,
    '#select2' => array(
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'   => TRUE,
    '#default_value' => $share_options_default,
    '#attributes' => array('class'=> array('project_programe_reports_sections')),
    '#prefix'     => '<div id="main-container-select-vendor-product-page"><div class="form-group widen-this-choosen-box-share"><div class="input-group">' . $select_prefix,
    '#suffix'     => '</div></div>',
  );

  $element['main-container']['full-container']['inner-left-one']['vendor-message'] = array(
    '#title' => 'Message',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('vendor-message'),'placeholder'=>'Type Message'),
    '#default_value' => isset($storage_project['message'])?strip_tags($storage_project['message']):'',
  );

  $cls3 = isset($form_state['scorecardId'])?'col-md-6 col-sm-6 col-xs-12':'col-md-4 col-sm-4 col-xs-12';
  $scoreCardDate = node_load($getNodesNids)->field_rating_due_date['und'][0]['value'];

  $element['main-container']['full-container']['inner-left-one']['vendor-due-date'] = array(
    '#type'            => 'date_popup',
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#default_value'   => $scoreCardDate,
    '#title'           => 'Due Date',
    '#attributes'      => array('class' => array('form-control', 'vendor-due-date'), 'placeholder' => t('Due Date')),
    '#prefix'          => '<div class="clearfix get-date"><div class="'.$cls3.' form-item padding-0 clearfix relative m6connect_share_date margin-bottom-10">',
    '#suffix'          => '</div></div>',
    '#field_prefix'    => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span>',
  );

  $element['main-container']['full-container']['inner-left-one']['vendor-email-notification'] = array(
    '#type'          =>'checkboxes',
    '#attributes'    => array('class'=> array('invoice_reconciled')),
    '#options'       => array('1' => 'Send Email Notification',),
    '#default_value' => array('1'),  
    '#prefix'        => '<div class="clearfix form-item asset-data-rendration">',
    '#suffix'        => '</div></div></div>',
  );
 
  $element['node_edit_nid'] = array(
    '#type'       =>'hidden',
    '#attributes' => array('class'=> array('node-edit-nid')),
  );

  $element['node_edit_nid2'] = array(
    '#type'  =>'hidden',
    '#value' => isset($getscore) ? $getscore : '',
  );

  return $element;
}

/*
 * Submission of share page goes here
 * scm_share_submit
 */
function scm_share_submit(&$form, &$form_state) {
  global $user, $company;

  // Geting all value in a single variable
  $formVal = $form_state['values'];

  // Gathering all the posted data
  $scoreCard = $formVal['scorecard-nid-entry'];   // Scorecard nid
  $vendorTo = $formVal['vendor-selections'];  // Array of selected vendors
  $vendorMessage = $formVal['vendor-message'];    // Message to be sent to selected vendors
  $vendorDueDate = $formVal['vendor-due-date'];   // Duedate for vendor to submited there ratings
  $vendorNotify  = $formVal['vendor-email-notification'][1]; // if value 1 then send mail to selected users with message and due date

  // As the functionality changed (TS=1504008126), now the $vendorTo has values
  // of both teams and users. We need to differentiate teams and users.
  $vendorTo = _clear_prefix_from_senders_list($vendorTo);

  $to_users = $vendorTo['users'];
  $to_teams = $vendorTo['teams'];

  if (empty($to_users) && empty($to_teams)) {
    // If there are no users, then abort.
    drupal_set_message(t('No users selected for sharing. Please select at least one user/team.'), 'warning', FALSE);

    if (!empty($form_state['ajax'])) {
      $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
      $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
      $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    }
  }
  else {
    // Saving the submitted data.
    $scoreCardData = node_load($scoreCard);
    $scoreCardName = $scoreCardData->field_scorecard_name['und'][0]['value'];

    // As we have either of $to_users or $to_teams or both, but we need a single
    // array of users to whom the mail and notification is to be sent. But
    // even before that, if we have previous data present for the current entry
    // then we need to filter out the data.
    $already_sent_users = $already_sent_teams = array();

    if (!empty($formVal['node_edit_nid']) || !empty($formVal['node_edit_nid2'])) {
      if ($formVal['node_edit_nid'] != '') {
       $node_edit_nid = $formVal['node_edit_nid']; 
      }
      else {
        $node_edit_nid = $formVal['node_edit_nid2'];
      }

      $node = node_load($node_edit_nid);

      if (!empty($node->field_share_with_user[LANGUAGE_NONE])) {
        foreach ($node->field_share_with_user[LANGUAGE_NONE] as $key => $value) {
          $already_sent_users[] = $value['value'];
        }
      }

      if (!empty($node->field_share_with_team[LANGUAGE_NONE])) {
        foreach ($node->field_share_with_team[LANGUAGE_NONE] as $key => $value) {
          $already_sent_teams[] = $value['value'];
        }
      }

      $new_users = $to_users;
      $new_teams = $to_teams;

      if (!empty($already_sent_users)) {
        // If we already shared this scorecard with users, then filtering out the
        // new users.
        $new_users = array_diff($to_users, $already_sent_users);

        if (empty($new_users)) {
          // No new users.
          drupal_set_message(t('Scorecard %title is already shared with the selected users. If you want to resend the email/notification, then choose from actions menu.', array('%title' => $scoreCardName)), 'warning', FALSE);
        }
        else {
          $message_already_sent = format_plural(count($already_sent_users), 'Scorecard %scorecard is already shared with 1 user.', 'Scorecard %scorecard is already shared with @count users.', array('%scorecard' => $scoreCardName));

          $message_new_users = format_plural(count($new_users), 'Scorecard %scorecard shared with 1 user successfully.', 'Scorecard %scorecard shared with @count users successfully.', array('%scorecard' => $scoreCardName));

          drupal_set_message($message_already_sent, 'warning', FALSE);
          drupal_set_message($message_new_users, 'status', FALSE);
        }
      }

      if (!empty($already_sent_teams)) {
        // If we already shared this scorecard with users, then filtering out the
        // new users.
        $new_teams = array_diff($to_teams, $already_sent_teams);

        if (empty($new_teams)) {
          // No new users.
          drupal_set_message(t('Scorecard %title is already shared with the selected teams. If you want to resend the email/notification, then choose from actions menu.', array('%title' => $scoreCardName)), 'warning', FALSE);
        }
        else {
          $message_already_sent = format_plural(count($already_sent_teams), 'Scorecard %scorecard is already shared with 1 team.', 'Scorecard %scorecard is already shared with @count teams.', array('%scorecard' => $scoreCardName));

          $message_new_users = format_plural(count($new_users), 'Scorecard %scorecard shared with 1 team successfully.', 'Scorecard %scorecard shared with @count teams successfully.', array('%scorecard' => $scoreCardName));

          drupal_set_message($message_already_sent, 'warning', FALSE);
          drupal_set_message($message_new_users, 'status', FALSE);
        }
      }
    }
    else {
      $new_users = $to_users;
      $new_teams = $to_teams;
      $node = _node_creation_call('scorecard_share', 'SCR-SHARE'.time());
      drupal_set_message('Scorecard ' . $scoreCardName . ' shared successfully.');
    }

    $all_users = array();

    // At this point of code, we have an array of users, and an array of teams.
    // But for further tasks, we shall also be needing a seperate array of all
    // users.

    // If there are any team selected by user.
    if (!empty($new_teams)) {
      $team_users = _get_team_users_multiple($new_teams);

      // We have all team users now, getting all users in one sinle array.
      // The below function also ensures we do not get duplicate entries.
      $team_users_all = array_values(_clear_associative_array_teams($team_users));
    }

    if (!empty($new_users)) {
      $all_users = $new_users;
    }

    if (!empty($team_users_all)) {
      // If there are any team members then merging with users.
      if (!empty($all_users)) {
        $all_users = array_unique(array_merge($all_users, $team_users_all));
      }
      else {
        $all_users = $team_users_all;
      }
    }

    // We also need a list of all already sent users, to send them update email
    // and notification, if there are any.
    $prev_all_users = array();
    if (!empty($already_sent_users)) {
      $prev_all_users = $already_sent_users;
    }

    // Getting team users.
    if (!empty($already_sent_teams)) {
      $already_team_users = _get_team_users_multiple($already_sent_teams);

      // We have all team users now, getting all users in one sinle array.
      // The below function also ensures we do not get duplicate entries.
      $already_team_users_all = array_values(_clear_associative_array_teams($already_team_users));

      if (!empty($already_team_users_all)) {
        // If there are any team members then merging with users.
        if (!empty($prev_all_users)) {
          $prev_all_users = array_unique(array_merge($prev_all_users, $already_team_users_all));
        }
        else {
          $prev_all_users = $already_team_users_all;
        }
      }
    }

    if (!empty($prev_all_users)) {
      // If there are any previous users, then sending them notification and
      // mail.
      if ($vendorNotify == 1) {
        drupal_set_message(t('An update mail has been sent to previous users under scorecard -( %title ), for rating.', array('%title' => $scoreCardName)), 'status', FALSE);

        _mail_for_share_rating($prev_all_users, $scoreCard, $vendorMessage, $vendorDueDate, 1);
      }

      foreach($prev_all_users as $vendorId) {
        // Sending notification to users.
        if (db_table_exists('m6connect_notification')) {
          $m6connect_notification = array(
            'type'         => 'scm',
            'event'        => 'scorecard_share_update',
            'entity_id'    => $scoreCard,
            'company_nid'  => $company->nid,
            'message'      => NULL,
            'request_from' => $user->uid,
            'request_to'   => $vendorId,
            'status'       => 1,
            'timestamp'    => REQUEST_TIME,
          );
          entity_save('m6connect_notification', (object) $m6connect_notification);
        }
      }
    }

    $node->field_scorecard_reference[LANGUAGE_NONE][0]['nid'] = $scoreCard;

    if ($vendorNotify == 1 && !empty($all_users)) {
      // Here, we still need to check whether we have some users or not.
      // Sending mail to vendor 
      drupal_set_message(t('A mail has been sent under scorecard -( %title ), for rating.', array('%title' => $scoreCardName)), 'status', FALSE);

      _mail_for_share_rating($all_users, $scoreCard, $vendorMessage, $vendorDueDate, 0);
    }

    foreach($all_users as $vendorId) {
      // Sending notification to users.
      if (db_table_exists('m6connect_notification')) {
        $m6connect_notification = array(
          'type'         => 'scm',
          'event'        => 'scorecard_share',
          'entity_id'    => $scoreCard,
          'company_nid'  => $company->nid,
          'message'      => NULL,
          'request_from' => $user->uid,
          'request_to'   => $vendorId,
          'status'       => 1,
          'timestamp'    => REQUEST_TIME,
        );
        entity_save('m6connect_notification', (object) $m6connect_notification);
      }
    }

    // We have sent the notification and mail to users, but also need to save
    // the users and teams in node.
    foreach (array('field_share_with_user', 'field_share_with_team') as $key => $value) {
      $data = $value == 'field_share_with_user' ? $new_users : $new_teams;

      foreach ($data as $data_val) {
        $node->{$value}[LANGUAGE_NONE][] = array('value' => $data_val);
      }
    }

    // Saving the message.
    $node->field_share_with_message[LANGUAGE_NONE][0]['value'] = $vendorMessage;

    // Saving the due date.
    if (!empty($vendorDueDate)) {
      $node->field_rating_due_date[LANGUAGE_NONE][0]['value'] = $vendorDueDate;
    }

    // Saving the email notification flag.
    $node->field_email_notification[LANGUAGE_NONE][0]['value'] = $vendorNotify;

    // Saving the node finally.
    node_save($node);

    // Getting active scorecad.
    $active_sc = _fetching_scorecard_information_active('scm_scorecard');

    if (!empty($form_state['ajax'])) {
      // $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
      // $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
      $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
      $form_state['ajax_commands'][] = ctools_ajax_command_redirect('scorecard/evaluate/' . $active_sc);
    }
    else {
      $form_state['redirect'] = 'scorecard/evaluate/' . $active_sc;
    }
  }
}

/**
 * Helper function to send review mail for products.
 */
function _mail_for_share_rating($vendorTo, $scoreCard, $vendorMessage, $vendorDueDate, $update = 0) {
  // We shall be sending the mail to all company admins of the given company.
  global $user, $base_url;
  $user_name = _get_user_full_name($user->uid);
  $userData = user_load($user->uid);
  $message = '';
  
  // Getting all users whom to send mail.
  $to_users = $vendorTo;

  // Getting scorecard details
  $scorecardData = node_load($scoreCard);
  $scoreCardName = $scoreCardData->field_scorecard_name['und'][0]['value'];

  // Preparing message links.
  $link = url('scorecard/evaluate/' . $scoreCard, array('absolute' => TRUE));
  $click_link = t('<a href="@link">Click here</a>', array('@link' => $link));
  $mailto = t('<a href="@mail_url">@mail</a>', array('@mail_url' => 'mailto:' . variable_get('site_mail', 'support@m6connect.com'), '@mail' => variable_get('site_mail', 'support@m6connect.com')));

  // Preparing message body.
  if ($update) {
    $message = 'Hello,<br/>';
    $message .= t('%user has updated the Scorecard @no. To view the updates and submit your ratings, please click the link below.', array('%user' => $user_name, '@no' => $scoreCardName));
    $message .= '<br/><br/>';
    $message .= $click_link;
    $message .= '<br/><br/>';

    $message .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connet') . '</strong><br/>(' . $mailto . ')';
  }
  else {
    $message = 'Hello,<br/>';
    $message .= t('You have been invited by %user ', array('%user' => $user_name, '@no' => $scoreCardName)) . ' to complete a Scorecard via M6connect.<br/><br/>';
    $message .= 'To complete and share your rating, please click the kink below. New to M6connect? Sign up at <a href="'.$base_url.'/register">www.M6Connect.com</a>.<br/><br/>';
    $message .= $click_link . '<br/><br/>';
    $message .= t('Here is personal note from %user ', array('%user' => $user_name)).'.<br/><br/>';
    $message .= $vendorMessage.'<br/><br/>';
    $message .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connet') . '</strong><br/>(' . $mailto . ')';
  }

  // M6Support Mail.
  $sender_mail = variable_get('site_mail', 'support@m6connect.com');

  $params = array(
    'subject'  => 'Question(s) shared on ' . variable_get('site_name', 'M6Connect') . ': Please rate the question(s).',
    'body'     => $message,
    'sender'   => $sender_mail,
    'language' => language_default(),
    'module'   => 'm6connect_misc',
    'key'      => 'commitment_mail___invite_2_m6_notify',
    'build'    => TRUE,
  );

  $mail_to_list = array();

  foreach ($to_users as $uid) {
    $account = user_load($uid);
    $mail_to_list[] = $account->mail;
  }

  if (!empty($mail_to_list)) {
    // Sending mail.
    $mail_sent = drupal_mail($params['module'], $params['key'], implode(', ', $mail_to_list), $params['language'], $params);
  }
}

function _get_share_summary_table_data() {
  global $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }
  $rows = array();

  $header = array(
    array('data'=>'Scorecard Name','class'=>array('text-center', 'col-md-2')),
    array('data'=>'Share With','class'=>array('text-center', 'col-md-2')),
    array('data'=>'Message','class'=>array('text-center', 'col-md-4')),
    array('data'=>'Due Date','class'=>array('text-center', 'col-md-2')),
    array('data'=>'Send Email','class'=>array('text-center', 'col-md-1')), 
    array('data'=>'Action','class'=>array('text-center', 'col-md-1')), 
  );

  if ($where == 'casemanager') {
    unset($header[5]);
  }
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));  
 $query->join('field_data_field_scorecard_reference','sr','sr.entity_id = n.nid');  
 $query->fields('n', array('nid'));
  $query->condition('n.type','scorecard_share','=');  
 $query->condition('om.gid', $company->nid, '=');
  $query->condition('sr.field_scorecard_reference_nid', $getNodesNids, '=');
  $getScrd = $query->execute()->fetchField();
  
  $query = db_select('node','n'); 
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->fields('n', array('nid','title'));
  $query->condition('om.gid', $company->nid, '=');
  $query->condition('n.nid', $getScrd, '=');        
  $query->condition('n.type', 'scorecard_share', '=');        
  $sharedData = $query->execute()->fetchAllKeyed(0,1);

  foreach($sharedData as $shareId => $shareTitle) {
    $shareNode = node_load($shareId);
    // == Scorecard name
  
    $scoreCardName = node_load($shareNode->field_scorecard_reference['und'][0]['nid']);
    $scoreCardNameFNL = $scoreCardName->field_scorecard_name['und'][0]['value'];

    // get all the share with users
    $userArr = array();

    foreach($shareNode->field_share_with_user[LANGUAGE_NONE] as $delta => $userId) {
      $getUserData = _get_user_mail_realname_by_uid($userId['value']);  
      $userArr[] = $getUserData['realname']; 
    }

    $shareMessage = isset($shareNode->field_share_with_message[LANGUAGE_NONE])?substr($shareNode->field_share_with_message[LANGUAGE_NONE][0]['value'],0,50):'No message';
    $dueDate = isset($shareNode->field_rating_due_date[LANGUAGE_NONE]) ? date('m/d/Y',strtotime($shareNode->field_rating_due_date[LANGUAGE_NONE][0]['value'])) : '';

    $date_class = '';
    if (!empty($dueDate)) {
      if (strtotime($shareNode->field_rating_due_date[LANGUAGE_NONE][0]['value']) < strtotime('today midnight')) {
        $date_class = 'form-required';
      }
    }

    $sendMail = ($shareNode->field_email_notification[LANGUAGE_NONE][0]['value'] == 1)?'Yes':'No'; 

    // Action button dropdown list goes here
    $action = '<div class="project-action '.$sharerecommendation.'">
                <div class="btn-group">
                  <div class="dropdown">
                    <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> <i class="fa fa-cog" aria-hidden="true"></i>&nbsp;<i class="fa fa-caret-down" aria-hidden="true"></i></button>
                    <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
                      <li>'.l('Edit', 'edit/'.$shareId,array('attributes' => array('class' => 'edit-share-detail', 'for' => $shareId))).'</li>
                      <li>'.l('Resend Notification', 'resend-notification/'.$shareId.'/nojs', array('attributes' => array('class' => array('use-ajax'),'id'=>'resend-notification'))).'</li>
                      <li>'.l('Delete', url('deletenode/nojs/'.$shareId), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE, 'attributes'=> array('class'=>array('ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ).'</li>
                    </ul>
                  </div>
                </div>
              </div>';

    if ($where == 'casemanager') {
      $rows[] = array(
        'data' => array(
          array('data' => $scoreCardNameFNL,'class' => array('text-center')),
          array('data' => implode(',',$userArr),'class' => array('text-center')),
          array('data' => $shareMessage,'class' => array('text-center')),
          array('data' => $dueDate,'class' => array('text-center', $date_class)),
          array('data' => $sendMail,'class' => array('text-center')),
        ),
      );
    }
    else {
      $rows[] = array(
        'data' => array(
          array('data' => $scoreCardNameFNL,'class' => array('text-center')),
          array('data' => implode(',',$userArr),'class' => array('text-center')),
          array('data' => $shareMessage,'class' => array('text-center')),
          array('data' => $dueDate,'class' => array('text-center', $date_class)),
          array('data' => $sendMail,'class' => array('text-center')), 
          array('data' => $action,'class' => array('text-center')), 
        ),
      );
    }
  }

  $output = theme('table', array('header' => $header,'rows' => $rows,'empty' => t('No Scorecard shared yet!'), 'attributes' => array('class' => array('table', 'm6connect-custom-table', 'm6connect-scorecard-share-table', 'table-hover', 'text-center', 'm6init-datatable'))));

  return $output;
}


function resend_notification_callback($cardId, $ajax = NULL) {
  ctools_include('ajax');

  $commands = array();
  $loadScorecard = node_load($cardId);
  $vendorMessage = $loadScorecard->field_share_with_message['und'][0]['value'];
  $vendorDueDate = $loadScorecard->field_rating_due_date['und'][0]['value'];
  
  $scoreCardData = node_load($loadScorecard->field_scorecard_reference['und'][0]['nid']);
  $scoreCardName = $scoreCardData->field_scorecard_name['und'][0]['value'];
  $vendorArr = array();
  $to_users = $to_teams = array();

  foreach ($loadScorecard->field_share_with_user['und'] as $delta => $values) {
    $to_users[] = $values['value'];
  }

  foreach ($loadScorecard->field_share_with_team['und'] as $delta => $values) {
    $to_teams[] = $values['value'];
  }

  if (!empty($to_users) || !empty($to_teams)) {
    $loadScorecard->field_email_notification['und'][0]['value'] = 1;
    node_save($loadScorecard);

    $html = t('A mail has been sent under scorecard -( %title ), for rating.', array('%title' => $scoreCardName));
    drupal_set_message(t($html), 'status', FALSE);

    $team_users = _get_team_users_multiple($to_teams);
    $team_users_all = array_values(_clear_associative_array_teams($team_users));
    $all_users = array_unique(array_merge($to_users, $team_users_all));

    _mail_for_share_rating($all_users, $scoreCardData->nid, $vendorMessage, $vendorDueDate);
  }
  else {
    drupal_set_message(t('No users or teams found for current scorecard. Please update your scorecard sharing details.'), 'warning', FALSE);
  }

  $commands[] = ajax_command_remove('#messages-custom');
  $commands[] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');

  print ajax_render($commands);
  exit;
}

/*
 * Start work for evaluate  
 */
function scm_question_builder_evaluate_content(){
  global $user,$company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  $elements['project-form']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_evaluate_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  return $elements; 
}

function _casemanager_scorecard_evaluate_form($form, &$form_state) {
  global $user,$company;   
  
  //evaluate_m6_storage_value
  if(empty($form_state['evaluate_m6_storage'])){
    $tempIdentifer = uniqid();
    $form_state['evaluate_m6_storage'][]  = $tempIdentifer;
  }
  $form['scm-casemanager-menu']= array(
    '#markup' => scm_scorecard_sub_menu_links_content(),
    '#prefix' => '<div class="clearfix csemanager-sub-menu margin-top-10 margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $form['main-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix scm-scorecard"><div id="questionbuilder_scorecard_main_container" class="clearfix">',  
    '#process' => array('evaluate_main_container_process'),
  );  
  $form['main_container2'] = array(
    '#type' => 'container',
    '#theme' => 'evalaute_m6_theme',
    '#attributes' => array('class'=>array('alert-container-section')),
    '#prefix' => '<div class="clearfix" id="main-class"><div id="alert-container-section" class="add-new-alert-detail">', 
    '#suffix' => '</div></div>',
    '#process' => array('evaluate_category_question_process'),
  );
  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }

  $form['submit']['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#submit'=> array('scm_evaluate_submit'),    
    '#prefix' => '<div class="clearfix custom-submit-select-pro-button '.$sharerecommendation.'">',  
  ); 
  $form['submit']['share'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Share" class="btn btn-success">',    
  );
  $form['actions']['reset'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button">',
    '#suffix' => '</div></div></div>',
  );
  return $form;
}

function evaluate_main_container_process($element, &$form_state) {
  global $company;
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight' => 3,
  );     
  $element['main-container']['full-container']['inner-left-one']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('well','well-large','no-bg')),
  );         
  $element['main-container']['full-container']['inner-left-one']['scorecard-info-title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="clearfix"><h4>Scorecard Information</h4></div><div class="clearfix well well-large"><div class="qbuilder-scorinfo margin-5 clearfix">',
  );  
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $getAllScoreCards = _fetching_scorecard_information_evaluate('scm_scorecard');
  $scoreCardData = node_load($getNodesNids);
  $ratingDate = strtotime($scoreCardData->field_rating_due_date['und'][0]['value']);
  $awardDate = strtotime($scoreCardData->field_recommendation_to_award_da['und'][0]['value']);
  $element['scorecard-nid-entry'] = array(
    '#type' => 'hidden', 
    '#attributes'=> array('class'=> array('scorecard-nid-entry')),
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-number'] = array(
    '#type' => 'select',
    '#title' => 'Select Scorecard',
    '#options' => $getAllScoreCards,
    '#empty_option' => 'Choose scorecard',
  '#default_value' => $getNodesNids,
    '#attributes' => array('class'=> array('form-control scorecard-name-title')),
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12 qbuilder-item"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',
    '#ajax' => array(
      'wrapper' => 'replace-facility-options-here',
      'callback' => '_update_scorecard_based_data_view',
    ),
  );
  $element['main-container']['full-container']['inner-left-one']['rating-date'] = array(
  '#markup' => '<p class="blue-and-bold">Rating Due Date</p><p class="rfp-data-date">'.date('m/d/Y',$ratingDate).'</p>',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12 qbuilder-item"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',  
  );
  $element['main-container']['full-container']['inner-left-one']['project-name'] = array(
    '#markup' => '<p class="blue-and-bold">Project Name</p><p class="prject-data-name">'.(!empty($scoreCardData->field_project_nid_for_scm['und'][0]['value'])?_get_title_of_node($scoreCardData->field_project_nid_for_scm['und'][0]['value']):'').'</p>',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12 qbuilder-item"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
  $element['main-container']['full-container']['inner-left-one']['rfp-name'] = array(
    '#markup' => '<p class="blue-and-bold">RFP Name</p><p class="rfp-data-name">'.(!empty($scoreCardData->field_rfp_nid_for_scm['und'][0]['value'])?_get_title_of_node($scoreCardData->field_rfp_nid_for_scm['und'][0]['value']):'').'</p>',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12 qbuilder-item"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type' => 'markup',
    '#markup' => '</div></div>',
  );
  return $element;
}

/*
 * Fetching selected scorecard related data
 */
function _update_scorecard_based_data_view($form,&$form_state) {
  $commands = array();
  $triggering_element = $form_state['triggering_element'];
  $scorecardNid = $triggering_element['#value'];
  $scorecardData = node_load($scorecardNid);
  $ratingDueDate = isset($scorecardData->field_rating_due_date['und'])?date('m/d/Y', strtotime($scorecardData->field_rating_due_date['und'][0]['value'])):'';
  $projectName = isset($scorecardData->field_project_nid_for_scm['und'])?node_load($scorecardData->field_project_nid_for_scm['und'][0]['value'])->title:'';
  $rfpName = isset($scorecardData->field_rfp_nid_for_scm['und'])?node_load($scorecardData->field_rfp_nid_for_scm['und'][0]['value'])->title:'';    
  $commands[] = ajax_command_html(".rfp-data-date", $ratingDueDate);
  $commands[] = ajax_command_html(".prject-data-name", $projectName);
  $commands[] = ajax_command_html(".rfp-data-name", $rfpName);  
  // Putting a hidden entry of choosed scorecard
  $commands[] = ajax_command_invoke(".scorecard-nid-entry", 'val',array($scorecardNid));
  // Getting the Company for seclected scorecard
  $companyId = $scorecardData->og_group_ref['und'][0]['target_id'];
  $getListQuestion = _getting_list_of_question($companyId);
  $commands[] = ajax_command_replace("#alert-container-section", render($form['main_container2']));
  return array('#type' => 'ajax','#commands' => $commands);
}

function evaluate_category_question_process($element, &$form_state){   
  $storage = $form_state['evaluate_m6_storage'];    
  $element['#storage'] = $storage;
  foreach ($storage as $key => $uniqId) {  
    $element['category_name'][$uniqId] = array(
      '#type' => 'hidden', 
      '#value'=> $category,
    '#attributes'=> array('class'=> array('category_name')),
    );
  $element['questions'][$uniqId] = array(
    '#type' => 'markup',
    '#markup' => '<p>Question shown here?</p>',
  );
    $element['question_weight'][$uniqId] = array(
      '#type' => 'textfield', 
      '#attributes'=> array('class'=>array('question_weight','qbuilder-weight','clearnumber')),
    '#field_prefix' => '<i class="fa fa-minus item-decrease item-decrease-item" aria-hidden="true"></i>',
      '#field_suffix' => '<i class="fa fa-plus item-increase item-increase-item" aria-hidden="true"></i>',
      '#maxlength' => 2,
    );
    $element['question_rating'][$uniqId] = array(
      '#type' => 'textfield', 
    '#attributes'=> array('class'=>array('qbuilder-rating','clearnumber','question_rating')),
    '#field_prefix' => '<i class="fa fa-minus item-decrease item-decrease-item" aria-hidden="true"></i>',
    '#field_suffix' => '<i class="fa fa-plus item-increase item-increase-item" aria-hidden="true"></i>',
    '#maxlength' => 2,
    '#parents' => array('qbuilder', $key, $uniqid, $value, 'rating'),
    );
    $element['question_score'][$uniqId] = array(
      '#type' => 'textfield',      
      '#attributes'=> array('class'=>array('qbuilder-score','clearnumber','question_score')),
    '#parents' => array('qbuilder', $key, $uniqid, $value, 'score'),
    );
    $element['question_comments'][$uniqId] = array(
      '#type' => 'textfield',      
      '#default_value' => !empty($question_default_values[$key][$value]['comments']) ? $question_default_values[$key][$value]['comments'] : '',
    '#attributes'=> array('class'=>array('qbuilder-comments','cleartext','question_comments')),
    '#parents' => array('qbuilder', $key, $uniqid, $value, 'comments'),
    );
    if(isset($form_state['evaluate_m6_storage_value'][$uniqId])) {
      $stdefault = $form_state['evaluate_m6_storage_value'][$uniqId];
      $element['category_name'][$uniqId]['#default_value'] = $stdefault['categoryName'];
      $element['questions'][$uniqId]['#default_value'] = $stdefault['questions'];
      $element['question_weight'][$uniqId]['#default_value'] = $stdefault['questionWeight'];
      $element['question_rating'][$uniqId]['#default_value'] = $stdefault['questionRating'];
      $element['question_score'][$uniqId]['#default_value'] = $stdefault['questionScore'];   
      $element['question_comments'][$uniqId]['#default_value'] = $stdefault['questionComments'];
    }    
  }  
  $element['waight_total'][$catID] = array(
    '#type' => 'textfield',      
    '#default_value' => '150',
  '#attributes'=> array('class'=>array('cleartext','waight_total')),
  '#parents' => array('qbuilder', $key, $uniqid, $value, 'waight_total'),
  );
  $element['score_total'][$catID] = array(
    '#type' => 'textfield',      
    '#default_value' => '150',
  '#attributes'=> array('class'=>array('cleartext','score_total')),
  '#parents' => array('qbuilder', $key, $uniqid, $value, 'score_total'),
  );
  return $element;
}

function theme_evalaute_m6_theme($variables) {  
  $element = $variables['form'];
  $storage = $element['#storage'];
  $output = '';
  $header = array('Category Name', 'Weight', 'Rating','Score', 'Comments');
  $rowNo = 1;
  foreach ($storage as $key => $uniqId) {
    $rows[] = array(
      'data'=> array(
        array('data'=>drupal_render($element['questions'][$uniqId])),
        array('data'=>drupal_render($element['question_weight'][$uniqId])),
        array('data'=>drupal_render($element['question_rating'][$uniqId])),
        array('data'=>drupal_render($element['question_score'][$uniqId])),
        array('data'=>drupal_render($element['question_comments'][$uniqId])),   
      ),
    );
    $rows[] = array(
      'data'=> array(
        array('data'=> '<strong>Total</strong>','colspan' => 1),
        array('data'=> drupal_render($element['waight_total'][$uniqId]),'colspan' => 2),
      array('data'=> drupal_render($element['score_total'][$uniqId]),'colspan' => 2),
      ),   
    );
    $rowNo++;
  }  
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes'=> array('class'=> array('project-mgmt-po-item-table','table','table-hover','m6connect-custom-table','m6connect-table-border'))));
  $output .= drupal_render_children($element);
  return $output;
}

function _getting_list_of_question($cnid) {
  $query = db_select('m6connect_qbuilder_data','qb');
  $query->fields('qb', array('category_id','question'));
  $query->condition('qb.company_nid', $cnid, '=');
  $returnResult = $query->execute()->fetchAll();
  $updateResult = array();
  foreach($returnResult as $delta => $question) {
  if($question->category_id == '') { continue; }   
    $updateResult[$question->category_id][] = array(
    'question' => $question->question,    
  );
  }
  return $updateResult;
}

function append_prefix_to_array(&$item, $key, $prefix) {
  $item = $prefix . '_' . $item;
}

function _clear_prefix_from_senders_list($input = NULL) {
  $return = array(
    'teams' => array(),
    'users' => array(),
  );

  if (empty($input) || !is_array($input)) {
    return $return;
  }

  foreach ($input as $key => $value) {
    if (strpos($value, '_') !== FALSE) {
      $explode = explode('_', $value);
      switch ($explode[0]) {
        case 'team':
          $return['teams'][$explode[1]] = $explode[1];
          break;

        case 'user':
          $return['users'][$explode[1]] = $explode[1];
          break;
      }
    }
  }

  return $return;
}
