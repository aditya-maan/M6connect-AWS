<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_locations_buildings_configure_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements = array();
  $elements['scm-setting-menu-items'] = array(
    '#markup' => scm_setting_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
    '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
  );

  $elements['request-subtype-fieldset'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_location_buildings_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 main-scm-common-form page-program thumbnail">',
    '#suffix' => '</div>',
  );
  $elements['scm-my-request-listing'] = array(      
    '#markup' => get_scm_location_buildings_settings_table_data(),
    '#prefix' => '<div class="clearfix"><div class="scm-my-request-listing" id="scm-my-request-table">',
    '#suffix' => '</div></div>',
  );
  return $elements;
}

/*
 *scm request type setting form
 */
function scm_location_buildings_settings_form($form, &$form_state) {
  $defaultValues = '';
  $getReqNodes = _getting_table_data_call('scm_setting_location_buildings');
  $form['reset-callback'] = array(
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes' => array('class'=> array('form-control','reset-callback')),
    '#ajax' => array(
      'callback'=> 'change_scm_location_buildings_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get-location-buildings-settings'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#attributes' => array('class'=> array('form-control get-my-requests')),
    '#ajax' => array(
      'callback'=> 'change_scm_location_buildings_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  if($form_state['triggering_element']['#name'] == 'container-cancel-btn'){
    $form_state['input'] = array();
    $form_state['values'] = array();
    $form_state['default_values'] = array();  
  }
  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('id'=>'scm-location-buildings-settings','class'=>array('col-md-12','col-sm-12','col-xs-12','row','project-details-full','program_modify_project_form')),
  );
  $form['main-container']['full-container-inner-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );  
  $form['main-container']['full-container-inner-right'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );
  $form['scm-setting-location-buildings-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-location-buildings-node-nid')),  
  );
  $form['scm-setting-location-region-statehiddan']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-location-region-statehiddan')),  
  );
  $form['main-container']['full-container-inner-left']['scm-location-buildings-name'] = array(
    '#title' => 'Department Name',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-location-buildings-name')),
    '#prefix' => '<div class="project-details-border"><div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-left']['assign_user_department'] = array(
    '#title' => t('Department Approver'),
    '#type'     => 'select',
    '#options' => get_scm_user_database_datasall('Department Approver'),
    '#empty_option' => t('Select User'),
    '#multiple'     => 1,
    '#select2' => array('width'=>'65%'),
    '#attributes' => array('class'=>array('assign-user-department'),'placeholder' => t('Please choose department approver')),
    '#prefix' => '<div class="form-item clearfix"><div class="assign_user-outer-department">',
    '#suffix' => '</div></div>',
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-left']['department_new_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class'=>array('department_new_hidden')),
  );
  $allEntitys = _getting_all_nodewith_title('scm_setting_location_entity');
  $form['main-container']['full-container-inner-left']['scm-location-buildings-Entity'] = array(
    '#type' => 'select',
    '#title' => 'Entity',
    '#options' => $allEntitys,
    '#empty_option' => 'Select Entity',
    '#attributes' => array('class'=> array('form-control scm-location-buildings-Entity')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $allRegions = _getting_all_nodewith_title('scm_setting_location_region');
  $form['main-container']['full-container-inner-left']['scm-location-buildings-Region'] = array(
    '#type' => 'select',
    '#title' => 'Region',
    '#options' => $allRegions,
    '#empty_option' => 'Select Region',
    '#attributes' => array('class'=> array('form-control scm-location-buildings-Region')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-left']['scm-location-buildings-description'] = array(
    '#title' => 'Department Description',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('form-control scm-location-buildings-description resize-textarea-none')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
    '#resizable' => false ,
    '#required' => TRUE,
  );

  // $form['main-container']['full-container-inner-right']['scm-location-buildings-address']= array(
  //   '#title' => t('Address'),
  //   '#type' => 'fieldset',
  //   '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','row','scm-location-buildings-address',)),
  //   '#collapsible' => FALSE,
  //   '#collapsed' => FALSE,  
  // );
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-location-buildings-use-region'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use The Same Address As Region'),
    '#default_value' => 0,
    '#options' => array(0,1),
    '#ajax' => array(
      'callback'=> 'check_copy_existing_region_callback',
      'wrapper' => 'scm-location-buildings-settings-form',
      'effect' => 'fade',
    ), 
    '#attributes' => array('class'=>array('scm-location-buildings-use-region')),
    '#prefix' => '<div class="project-details-border"><div class="form-item clearfix"><label>Address</label><div class="single-right-checkbox-border">',
    '#suffix' => '</div></div>',
  );
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-country'] = array(
    '#type' => 'select',
    '#title' => 'Choose Country',
    '#options' => $countryNamesList1,
    '#empty_option' => 'Select Country',
    '#attributes' => array('class'=> array('form-control scm-buildings-country')),
    '#ajax' => array(
      'callback'=> 'change_country_form_state_callback',
      'wrapper' => 'location_zone_main_container_countries',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="form-item clearfix padding-0 col-sm-12">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-address1'] = array(
    '#title' => 'Address Line 1',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-buildings-address1')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-address2'] = array(
    '#title' => 'Address Line 2',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-buildings-address2')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>', 
  );
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-city'] = array(
    '#title' => 'City',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-buildings-city')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $australian_states = array();
  $none_state = array();
   module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
   $triggeringElement = $form_state['triggering_element']; 
   if($form_state['triggering_element']['#name']=='scm-buildings-country') {
      if(!empty($triggeringElement['#value'])) {
        $australian_states = addressfield_get_administrative_areas($triggeringElement['#value']);
        $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-state']['#options'] = (!empty($australian_states)?$australian_states:$none_state);
      }
  }

  if(!empty($australian_states)){
    $valid = TRUE;
    $noneoption = '- Select State-';
  }else{
    $valid = FALSE;
     $noneoption = '- None-';
  }
  
   $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-state-hide'] = array(
    '#type' => 'hidden',
    '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-buildings-state-hide')),
  );
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-state'] = array(
    '#type' => 'select',
    '#title' => 'Choose State',
    '#attributes' => array('class'=> array('form-control scm-buildings-state')),
    '#options' => (!empty($australian_states)?$australian_states:$none_state),
    '#validate' => TRUE,
    '#empty_option' => t($noneoption),
    '#empty_value' => '',
    '#prefix' => '<div class="form-item clearfix" id="location_zone_main_container_countries">',
    '#suffix' => '</div>',
    '#required' => $valid,
  );
  $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-zipcode'] = array(
    '#title' => 'Zip Code',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-buildings-zipcode')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
    '#required' => TRUE,
  );

  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    //'#validate' => array('project_scm_my_request_validate'),
    '#submit' => array('scm_location_buildings_settings_form_submit_callback'),
    '#attributes' => array('class'=>array('scm-location_buildings_settings-custom-btn')),
    '#prefix' => '<div class="col-sm-12 custom-action-button-div margin-bottom-20" for="closed">',
  );
  $form['cancel'] = array(
    //'#type' => 'markup',
    //'#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
    '#type' => 'button',
    '#value' => 'Cancel',
    '#name' => 'container-cancel-btn',
    '#limit_validation_errors' => array(),
    '#executes_submit_callback' => FALSE,
    '#ajax' => array(
      'callback' => 'container_cancel_callback',
      'wrapper'  => 'scm-location-buildings-settings',     
    ),
    '#suffix' => '</div>',
  );
  
  return $form;
}

function change_country_form_state_callback($form, &$form_state) {
    $form_state['rebuild'] = TRUE;
    return $form['main-container']['full-container-inner-right']['scm-location-buildings-address']['scm-buildings-state'];
}

function container_cancel_callback($form, &$form_state) {
    //$form_state['rebuild'] = TRUE;
  return $form['main-container'];
}

function check_copy_existing_region_callback($form, &$form_state) {
  $commands = array();
  if(!empty($form_state['values']['scm-location-buildings-Region'])){
    $regionid = $form_state['values']['scm-location-buildings-Region'];
    $regionselected = node_load($regionid);
    $commands[] = ajax_command_invoke('select.scm-buildings-country', 'val', array($regionselected->field_scm_setting_country['und'][0]['value']));
    $commands[] = ajax_command_invoke("select.scm-buildings-country", 'trigger',array('change'));
    $commands[] = ajax_command_invoke('input.scm-buildings-address1', 'val', array($regionselected->field_scm_setting_adress_line_1['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-buildings-address2', 'val', array($regionselected->field_scm_setting_adress_line_2['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-buildings-city', 'val', array($regionselected->field_scm_setting_city['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-buildings-zipcode', 'val', array($regionselected->field_scm_setting_zip_code['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-buildings-state-hide', 'val', array($regionselected->field_scm_setting_state['und'][0]['value']));
  } else {
    form_set_error('Please Select Region');
     $commands[] = ajax_command_invoke('input.scm-location-buildings-use-region', 'prop',array('checked', false));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}  
/*
 * Ajax submit callback for 
 * Submitting request type setting form
 */
function scm_location_buildings_settings_form_submit_callback($form, &$form_state) {
  global $user,$company;

  $formVal = $form_state['values'];
  $getTitle = $formVal['scm-location-buildings-name'];
  
  // Check form submission for new node

  if (isset($formVal['scm-setting-location-buildings-node-nid']) && !empty($formVal['scm-setting-location-buildings-node-nid'])) {
    $nodesave = node_load($formVal['scm-setting-location-buildings-node-nid']);
    $nodesave->title = $getTitle;
    $savestatus = 'updated';
  }
  else {
    $nodesave = _node_creation_call('scm_setting_location_buildings',$getTitle);  
    $savestatus = 'saved';
  }

  $nodesave->body['und'][0]['value'] = $formVal['scm-location-buildings-description'];
  $nodesave->field_scm_building_entity['und'][0]['value'] = $formVal['scm-location-buildings-Entity']; 
  $nodesave->field_scm_building_region['und'][0]['value'] = $formVal['scm-location-buildings-Region'];  
  $nodesave->field_scm_building_country['und'][0]['value'] = $formVal['scm-buildings-country']; 
  $nodesave->field_scm_building_address_1['und'][0]['value'] = $formVal['scm-buildings-address1'];
  $nodesave->field_scm_building_address_2['und'][0]['value'] = $formVal['scm-buildings-address2'];
  $nodesave->field_scm_building_city['und'][0]['value'] = $formVal['scm-buildings-city'];
  $nodesave->field_scm_building_state['und'][0]['value'] = $formVal['scm-buildings-state'];
  $nodesave->field_scm_building_zip_code['und'][0]['value'] = $formVal['scm-buildings-zipcode'];
  node_save($nodesave);

  $setting_insert = array (
    'uid'        => $user->uid,
    'nid'        => $company->nid,
    'entity_nid' => $nodesave->nid,
    'title'      => $formVal['scm-location-buildings-name'],
    'dpapprover' => implode("|", $formVal['assign_user_department']),
  );

  if (!empty($formVal['scm-setting-location-buildings-node-nid'])) {
    // If in case, th
    $q = db_select('m6connect_scm_setting_department', 'd')
      ->fields('d')
      ->condition('entity_nid', $formVal['scm-setting-location-buildings-node-nid'])
      ->execute()
      ->rowCount();

    if ($q > 0) {
      db_update('m6connect_scm_setting_department')
        ->fields($setting_insert)
        ->condition('entity_nid', $formVal['scm-setting-location-buildings-node-nid'], '=')
        ->execute();
    }
    else {
      $setting_insert['status'] = 1;
      $setting_insert['timestamp'] = REQUEST_TIME;
      db_insert('m6connect_scm_setting_department')->fields($setting_insert)->execute();
    }
  }
  else {
    $setting_insert['status'] = 1;
    $setting_insert['timestamp'] = REQUEST_TIME;
    db_insert('m6connect_scm_setting_department')->fields($setting_insert)->execute();
  }

  drupal_set_message('Department - '.$getTitle.' has been '.$savestatus.'.');
}
 

function get_scm_location_buildings_settings_table_data(){
  $rows = array();
  $header = array(
    array('data'=>'Department Name','class'=>array('text-center')),
    array('data'=>'Department Description','class'=>array('text-center')),
    array('data'=>'Address','class'=>array('text-center')),
    array('data'=>'City','class'=>array('text-center')),
    array('data'=>'State','class'=>array('text-center')), 
    array('data'=>'Zipcode','class'=>array('text-center')),
    array('data'=>'Action','class'=>array('text-center')),
  );
  $getMyReqNodes = _getting_table_data_call('scm_setting_location_buildings');
  foreach($getMyReqNodes as $ids => $values){ 
    $requestNodes = node_load($ids);  
    $countrystate = _get_name_by_country_state($requestNodes->field_scm_building_country['und'][0]['value'],$requestNodes->field_scm_building_state['und'][0]['value']);
    $rows[] = array(
      'data' => array(
        array('data' => l('<span class="commitment-nu-cust">'.$requestNodes->title.'</span>', 'edit/'.$values.'/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' => $values))),'class' => array('text-center')),
        array('data' => $requestNodes->body['und'][0]['value'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_building_address_1['und'][0]['value'].' '.$requestNodes->field_scm_building_address_2['und'][0]['value'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_building_city['und'][0]['value'],'class' => array('text-center')),
        array('data' => $countrystate['state'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_building_zip_code['und'][0]['value'],'class' => array('text-center')),
        array('data' => _get_action_button($ids, 'scm_setting_location_region'),'class' => array('text-center')),
    ),
  );
  }  
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table','table-hover','table-bordered','text-center')))); 
  return $output;      
}



function change_scm_location_buildings_settings_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element']; 
  if($form_state['triggering_element']['#name']=='get-location-buildings-settings') {
    if(!empty($triggeringElement['#value'])) {
    $myReqNode = node_load($triggeringElement['#value']);  
    $storage_project = array(
      'scm-location-buildings-name' => !empty($myReqNode->title)?$myReqNode->title:'',
      'scm-location-buildings-description' => isset($myReqNode->body['und'])?$myReqNode->body['und'][0]['value']:'',
      'scm-location-buildings-Entity' => isset($myReqNode->field_scm_building_entity['und'])?$myReqNode->field_scm_building_entity['und'][0]['value']:'',
      'scm-location-buildings-Region' => isset($myReqNode->field_scm_building_region['und'])?$myReqNode->field_scm_building_region['und'][0]['value']:'',
      'scm-buildings-country' => isset($myReqNode->field_scm_building_country['und'])?$myReqNode->field_scm_building_country['und'][0]['value']:'',
      'scm-buildings-address1' => isset($myReqNode->field_scm_building_address_1['und'])?$myReqNode->field_scm_building_address_2['und'][0]['value']:'',
      'scm-buildings-address2' => isset($myReqNode->field_scm_entiy_address_line_2['und'])?$myReqNode->field_scm_entiy_address_line_2['und'][0]['value']:'',
      'scm-buildings-city' => isset($myReqNode->field_scm_building_city['und'])?$myReqNode->field_scm_building_city['und'][0]['value']:'',
      'scm-buildings-state' => isset($myReqNode->field_scm_building_state['und'])?$myReqNode->field_scm_building_state['und'][0]['value']:'',
      'scm-buildings-zipcode' => isset($myReqNode->field_scm_building_zip_code['und'])?$myReqNode->field_scm_building_zip_code['und'][0]['value']:'',
    );        
    $commands[] = ajax_command_invoke("input.scm-setting-location-buildings-node-nid", 'val',array($myReqNode->nid));
    $commands[] = ajax_command_invoke("input.scm-location-buildings-name", 'val',array($storage_project['scm-location-buildings-name']));
    $commands[] = ajax_command_invoke("textarea.scm-location-buildings-description", 'val',array($storage_project['scm-location-buildings-description'])); 
    $commands[] = ajax_command_invoke("select.scm-location-buildings-Entity", 'val',array($storage_project['scm-location-buildings-Entity']));
    $commands[] = ajax_command_invoke("select.scm-location-buildings-Region", 'val',array($storage_project['scm-location-buildings-Region']));
    $commands[] = ajax_command_invoke("select.scm-buildings-country", 'val',array($storage_project['scm-buildings-country']));
    $commands[] = ajax_command_invoke("select.scm-buildings-country", 'trigger',array('change'));  
    $commands[] = ajax_command_invoke("input.scm-buildings-address1", 'val',array($storage_project['scm-buildings-address1'])); 
    $commands[] = ajax_command_invoke("input.scm-buildings-address2", 'val',array($storage_project['scm-buildings-address2'])); 
    $commands[] = ajax_command_invoke("input.scm-buildings-city", 'val',array($storage_project['scm-buildings-city'])); 
    $commands[] = ajax_command_invoke("input.scm-setting-location-region-statehiddan", 'val',array($storage_project['scm-buildings-state']));
    $commands[] = ajax_command_invoke("select.scm-buildings-state", 'val',array($storage_project['scm-buildings-state'])); 
    $commands[] = ajax_command_invoke("input.scm-buildings-zipcode", 'val',array($storage_project['scm-buildings-zipcode'])); 
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_location_buildings_settings_table_data()); 


    $subquery = db_select('m6connect_scm_setting_department', 'n');
    $subquery->fields('n');
    $subquery->condition('n.entity_nid', $triggeringElement['#value'], '=');
    $subquery->condition('n.nid', $company->nid, '=');
    $resultsubtype = $subquery->execute()->fetchObject();

    //$commands[] = ajax_command_invoke("input.department_new_hidden", 'val',array($myReqNode->nid));
        
    //$commands[] = ajax_command_invoke("input.department-name", 'val',array($resultsubtype->title));

      
    $commands[] = ajax_command_invoke("select.assign-user-department", 'val',array(explode("|",$resultsubtype->dpapprover)));
    $commands[] = ajax_command_invoke("select.assign-user-department", 'trigger',array('change'));



    }
  } else {
    $commands[] = ajax_command_invoke("input.scm-setting-location-buildings-node-nid", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-location-buildings-name", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm-location-buildings-description", 'val',array('')); 
    $commands[] = ajax_command_invoke("select.scm-buildings-country", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-buildings-address1", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-buildings-address2", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-buildings-city", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-setting-location-region-statehiddan", 'val',array('')); 
    $commands[] = ajax_command_invoke("select.scm-buildings-state", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-buildings-zipcode", 'val',array('')); 
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_location_buildings_settings_table_data()); 
  } 
  return array('#type' => 'ajax', '#commands' => $commands);
}
