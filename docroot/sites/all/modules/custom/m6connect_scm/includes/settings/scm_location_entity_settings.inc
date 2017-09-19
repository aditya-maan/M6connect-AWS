<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_locations_entity_configure_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements = array();
  $elements['scm-setting-menu-items'] = array(
    '#markup' => scm_setting_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
    '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
  );
  $elements['request-subtype-fieldset'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_location_entity_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 main-scm-common-form page-program thumbnail">',
    '#suffix' => '</div>',
  );
  $elements['scm-my-request-listing'] = array(      
    '#markup' => get_scm_location_entity_settings_table_data(),
    '#prefix' => '<div class="clearfix"><div class="scm-my-request-listing" id="scm-my-request-table">',
    '#suffix' => '</div></div>',
  );
  return $elements;
}

/*
 *scm request type setting form
 */
function scm_location_entity_settings_form($form, &$form_state) {
  $defaultValues = '';
  $getReqNodes = _getting_table_data_call('scm_setting_location_entity');
  $form['reset-callback'] = array(
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes' => array('class'=> array('form-control','reset-callback')),
    '#ajax' => array(
      'callback'=> 'change_scm_location_entity_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get-location-entity-settings'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#attributes' => array('class'=> array('form-control get-my-requests')),
    '#ajax' => array(
      'callback'=> 'change_scm_location_entity_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','row','project-details-full','program_modify_project_form')),
  );
  $form['main-container']['full-container-inner-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );  
  $form['main-container']['full-container-inner-right'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );
  $form['scm-setting-location-entity-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-location-entity-node-nid')),  
  );
  $form['scm-setting-location-region-statehiddan']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-location-region-statehiddan')),  
  );
  $form['main-container']['full-container-inner-left']['scm-location-entity-name'] = array(
    '#title' => 'Entity Name',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-location-entity-name')),
    '#prefix' => '<div class="project-details-border"><div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $allRegions = _getting_all_nodewith_title('scm_setting_location_region');
  $form['main-container']['full-container-inner-left']['scm-location-entity-Region'] = array(
    '#type' => 'select',
    '#title' => 'Region',
    '#options' => array_map('ucfirst', $allRegions),
    '#empty_option' => 'Select Region',
    '#attributes' => array('class'=> array('form-control scm-location-entity-Region')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-left']['scm-location-entity-description'] = array(
    '#title' => 'Entity Description',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('form-control scm-location-entity-description resize-textarea-none')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#resizable' => false ,
    '#required' => TRUE,
  );
  // $form['main-container']['full-container-inner-left']['scm-location-entity-materials-manager'] = array(
  //   '#title' => 'Materials Manager',
  //   '#type' => 'textfield',
  //   '#attributes'=> array('class'=> array('form-control scm-location-entity-materials-manager','workflow-auto'),'placeholder'=>t('Materials Manager')),
  //   '#autocomplete_path' => 'getall-users-company/autocomplete',
  //   '#ajax' => array(
  //     'callback' => 'scm_location_entity_autocomplete_callback',
  //     'event' => 'blur',
  //     'wrapper' => 'scm-location-entity-settings-form',
  //     'method' => 'replace',
  //     'effect' => 'fade',
  //   ),
  //   '#prefix' => '<div class="form-item clearfix">', 
  //   '#suffix' => '</div></div>',
  //   '#required' => TRUE,
  // );
  // $form['main-container']['full-container-inner-left']['scm-location-entity-materials-manager-id'] = array(
  //   '#type' => 'hidden',
  //   '#default_value' => '0',
  //   '#attributes' => array('class' => array('scm-location-entity-materials-manager-id')),
  // );

  $form['main-container']['full-container-inner-left']['scm-location-entity-materials-manager'] = array(
    '#title' => 'Materials Manager',
    '#type' => 'select',
    '#options' => getall_users_company_matarialmanager(),
    '#empty_option' => t('Select User'),
    '#multiple'     => 1,
    '#select2' => array('width'=>'65%'),
    '#attributes'=> array('class'=> array('form-control scm-location-entity-materials-manager','workflow-auto'),'placeholder'=>t('Materials Manager')),
    '#prefix' => '<div class="form-item clearfix">', 
    '#suffix' => '</div>',
    '#required' => TRUE,
  );



  $form['main-container']['full-container-inner-left']['scm-entity-contectorid'] = array(
    '#title' => 'ID',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-contectorid')),
    '#prefix' => '<div class="contact_details_entity"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-left']['scm-entity-contact'] = array(
    '#title' => 'Contact',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-contact')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-left']['scm-entity-contact-phone'] = array(
    '#title' => 'Contact Phone',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-contact-phone')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-left']['scm-entity-contact-email-address'] = array(
    '#title' => 'Contact Email Address',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-contact-email-address')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div></div>',
  );



  // $form['main-container']['full-container-inner-right']['scm-location-entity-address']= array(
  //   '#markup' => t('Address'),
  //   '#type' => 'markup',
  //   '#attributes' => array('class'=>array('scm-location-entity-address')),
  //   '#prefix' => '<div class="project-details-border">',
  // );
  $form['main-container']['full-container-inner-right']['scm-location-entity-use-region'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use The Region Address As The Entity Address'),
    '#default_value' => 0,
    '#options' => array(0,1),
    '#ajax' => array(
      'callback'=> 'check_copy_existing_region_callback',
      'wrapper' => 'scm-location-entity-settings-form',
      'effect' => 'fade',
    ),
    '#attributes' => array('class'=>array('scm-location-entity-use-region')),
    '#prefix' => '<div class="project-details-border"><div class="form-item clearfix"><label>Address</label><div class="single-right-checkbox-border">',
    '#suffix' => '</div></div>',
  );
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;
  $form['main-container']['full-container-inner-right']['scm-entity-country'] = array(
    '#type' => 'select',
    '#title' => 'Choose Country',
    '#options' => $countryNamesList1,
    '#empty_option' => 'Select Country',
    '#attributes' => array('class'=> array('form-control scm-entity-country')),
    '#ajax' => array(
      'callback'=> 'change_country_form_state_callback',
      'wrapper' => 'location_zone_main_container_countries',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-right']['scm-entity-address1'] = array(
    '#title' => 'Address Line 1',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-address1')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-right']['scm-entity-address2'] = array(
    '#title' => 'Address Line 2',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-address2')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>', 
  );
  $form['main-container']['full-container-inner-right']['scm-entity-city'] = array(
    '#title' => 'City',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-city')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $australian_states = array();
  $none_state = array();
   module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
   $triggeringElement = $form_state['triggering_element']; 
   if($form_state['triggering_element']['#name']=='scm-entity-country') {
      if(!empty($triggeringElement['#value'])) {
        $australian_states = addressfield_get_administrative_areas($triggeringElement['#value']);
        $form['main-container']['full-container-inner-right']['scm-location-entity-address']['scm-entity-state']['#options'] = (!empty($australian_states)?$australian_states:$none_state);
      }
  }

  if(!empty($australian_states)){
    $valid = TRUE;
    $noneoption = '- Select State-';
  }else{
    $valid = FALSE;
     $noneoption = '- None-';
  }

  $form['main-container']['full-container-inner-right']['scm-location-entity-address']['scm-entity-state'] = array(
    '#type' => 'select',
    '#title' => 'Choose State',
    '#attributes' => array('class'=> array('form-control scm-entity-state')),
    '#options' => (!empty($australian_states)?$australian_states:$none_state),
    '#validate' => TRUE,
    '#empty_option' => t($noneoption),
    '#empty_value' => '',
    '#prefix' => '<div class="form-item clearfix" id="location_zone_main_container_countries">',
    '#suffix' => '</div>',
    '#required' => $valid,
  );
  $form['main-container']['full-container-inner-right']['scm-entity-state-hide'] = array(
    '#type' => 'hidden',
    '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-state-hide')),
  );
  $form['main-container']['full-container-inner-right']['scm-entity-zipcode'] = array(
    '#title' => 'Zip Code',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-entity-zipcode')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
    '#required' => TRUE,
  );

  /*$form['main-container']['full-container-inner-right']['department_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Department Name'),
    '#attributes' => array('class'=>array('form-control','department-name'),'placeholder' => t('Please enter department here')),
    '#required' => TRUE,
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-right']['assign_user_department'] = array(
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

  $form['main-container']['full-container-inner-right']['department_new_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class'=>array('department_new_hidden')),
  );
*/





  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    //'#validate' => array('project_scm_my_request_validate'),
    '#submit' => array('scm_location_entity_settings_form_submit_callback'),
    '#attributes' => array('class'=>array('scm-location_entity_settings-custom-btn')),
    '#prefix' => '<div class="col-sm-12 custom-action-button-div margin-bottom-20" for="closed">',
  );
  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
    '#suffix' => '</div>',
  );
  return $form;
}

function getall_users_company_matarialmanager(){
  global $company;  
  $matches = array();
  $userList = _get_company_users_by_og_roles($company->nid,'Material Manager');
  foreach ($userList as $key => $value) {
    $matches[$value] = user_load($value)->realname; 
  }
  return $matches;
}

function check_copy_existing_region_callback($form, &$form_state) {
  $commands = array();
  if(!empty($form_state['values']['scm-location-entity-Region'])){
    $regionid = $form_state['values']['scm-location-entity-Region'];
    $regionselected = node_load($regionid);
    $commands[] = ajax_command_invoke('select.scm-entity-country', 'val', array($regionselected->field_scm_setting_country['und'][0]['value']));
    $commands[] = ajax_command_invoke("select.scm-entity-country", 'trigger',array('change'));
    $commands[] = ajax_command_invoke('input.scm-entity-address1', 'val', array($regionselected->field_scm_setting_adress_line_1['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-entity-address2', 'val', array($regionselected->field_scm_setting_adress_line_2['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-entity-city', 'val', array($regionselected->field_scm_setting_city['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-entity-zipcode', 'val', array($regionselected->field_scm_setting_zip_code['und'][0]['value']));
    $commands[] = ajax_command_invoke('select.scm-entity-state', 'val', array($regionselected->field_scm_setting_state['und'][0]['value']));
    $commands[] = ajax_command_invoke('input.scm-entity-state-hide', 'val', array($regionselected->field_scm_setting_state['und'][0]['value']));
  } else {
    form_set_error('Please Select Region');
    $commands[] = ajax_command_invoke('input.scm-location-entity-use-region', 'prop',array('checked', false));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
/**
 * Autocompletet ajax callback.
 */
// function scm_location_entity_autocomplete_callback($form, &$form_state) {
//   $commands = array();
//   if (!empty($form_state['triggering_element']['#value'])) {
//     $uid = $form_state['triggering_element']['#value'];
//     if (!empty($uid)) {
//       $commands[] = ajax_command_invoke('input.scm-location-entity-materials-manager-id', 'val', array($uid));
//       $commands[] = ajax_command_invoke('input.scm-location-entity-materials-manager', 'val', array(user_load($uid)->realname));
//     }
//   }
//   return array('#type' => 'ajax', '#commands' => $commands);
// }
function change_country_form_state_callback($form, &$form_state) {
      $form_state['rebuild'] = TRUE;
      return $form['main-container']['full-container-inner-right']['scm-location-entity-address']['scm-entity-state'];  
}  
/*
 * Ajax submit callback for 
 * Submitting request type setting form
 */
function scm_location_entity_settings_form_submit_callback($form, &$form_state) { 
  global $user; 
  global $company;    
  $formVal = $form_state['values'];
  $getTitle = $formVal['scm-location-entity-name'];
  /*
   * Check form submission for new node
    * or an existing one
   */
  if(isset($formVal['scm-setting-location-entity-node-nid']) && !empty($formVal['scm-setting-location-entity-node-nid'])) {
    $nodesave = node_load($formVal['scm-setting-location-entity-node-nid']);
    $nodesave->title = $getTitle; 
    $savestatus = 'updated';
  } else {
    $nodesave = _node_creation_call('scm_setting_location_entity',$getTitle);  
    $savestatus = 'saved';  
  }  
  $nodesave->body['und'][0]['value'] = $formVal['scm-location-entity-description'];
  $nodesave->field_scm_entiy_region['und'][0]['value'] = $formVal['scm-location-entity-Region'];  
  $nodesave->field_scm_entiy_country['und'][0]['value'] = $formVal['scm-entity-country']; 
  $nodesave->field_scm_entiy_address_line_1['und'][0]['value'] = $formVal['scm-entity-address1'];
  $nodesave->field_scm_entiy_address_line_2['und'][0]['value'] = $formVal['scm-entity-address2'];
  $nodesave->field_scm_entiy_city['und'][0]['value'] = $formVal['scm-entity-city'];
  $nodesave->field_scm_entiy_state['und'][0]['value'] = $formVal['scm-entity-state'];
  $nodesave->field_scm_entiy_zip_code['und'][0]['value'] = $formVal['scm-entity-zipcode'];
  $nodesave->field_entity_materials_manager['und'][0]['value']=implode("|",$formVal['scm-location-entity-materials-manager']);
  $nodesave->og_group_ref['und'][0]['target_id'] =  $company->nid;
  $nodesave->field_use_the_region_address['und'][0]['value'] = $formVal['scm-location-entity-use-region'];
  $nodesave->field_contact_id['und'][0]['value'] = $formVal['scm-entity-contectorid'];
  $nodesave->field_contact_details['und'][0]['value'] = $formVal['scm-entity-contact'];
  $nodesave->field_contact_phone['und'][0]['value'] = $formVal['scm-entity-contact-phone'];
  $nodesave->field_contact_email_address['und'][0]['value'] = $formVal['scm-entity-contact-email-address'];
  //$nodesave->field_department_name['und'][0]['value']=$formVal['department_name'];
  //$nodesave->field_entity_department_approver['und'][0]['value']=implode("|",$formVal['assign_user_department']);


  node_save($nodesave);

   /*$setting_insert = array (
    'uid' => $user->uid,
    'nid' => $company->nid,
    'entity_nid' => $nodesave->nid,      
    'title' => $formVal['department_name'],
    'dpapprover' => implode("|",$formVal['assign_user_department']),
  );
  if(!empty($formVal['department_new_hidden'])){
    db_update('m6connect_scm_setting_department')
    ->fields($setting_insert)
    ->condition('entity_nid', $formVal['department_new_hidden'], '=')
    ->execute();
  } else {
    $setting_insert['status'] = 1;
    $setting_insert['timestamp'] = time();
    db_insert('m6connect_scm_setting_department')->fields($setting_insert)->execute();
  }*/

   
  drupal_set_message('Entity - '.$getTitle.' has been '.$savestatus.'.');
}
 

function get_scm_location_entity_settings_table_data(){
  $rows = array();
  $header = array(
    array('data'=>'Entity Name','class'=>array('text-center')),
    array('data'=>'Entity Description','class'=>array('text-center')),
    array('data'=>'Address','class'=>array('text-center')),
    array('data'=>'City','class'=>array('text-center')),
    array('data'=>'State','class'=>array('text-center')), 
    array('data'=>'Zipcode','class'=>array('text-center')),
    array('data'=>'Action','class'=>array('text-center')),
  );
  $getMyReqNodes = _getting_table_data_call('scm_setting_location_entity');
  foreach($getMyReqNodes as $ids => $values){ 
    $requestNodes = node_load($ids);  
    $countrystate = _get_name_by_country_state($requestNodes->field_scm_entiy_country['und'][0]['value'],$requestNodes->field_scm_entiy_state['und'][0]['value']);
  $rows[] = array(
      'data' => array(
        array('data' => l('<span class="commitment-nu-cust">'.$requestNodes->title.'</span>', 'edit/'.$values.'/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' => $values))),'class' => array('text-left')),
        array('data' => $requestNodes->body['und'][0]['value'],'class' => array('text-left')),
        array('data' => $requestNodes->field_scm_entiy_address_line_1['und'][0]['value'].' '.$requestNodes->field_scm_entiy_address_line_2['und'][0]['value'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_entiy_city['und'][0]['value'],'class' => array('text-center')),
        array('data' => $countrystate['state'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_entiy_zip_code['und'][0]['value'],'class' => array('text-center')),
        array('data' => _get_action_button($ids, 'scm_setting_location_region'),'class' => array('text-center')),
    ),
  );
  }  
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table','table-hover','table-bordered','text-center')))); 
  return $output;      
}



function change_scm_location_entity_settings_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element']; 
  if($form_state['triggering_element']['#name']=='get-location-entity-settings') {
    if(!empty($triggeringElement['#value'])) {
      $myReqNode = node_load($triggeringElement['#value']);  
      $storage_project = array(
        'scm-location-entity-name' => !empty($myReqNode->title)?$myReqNode->title:'',
        'scm-location-entity-description' => isset($myReqNode->body['und'])?$myReqNode->body['und'][0]['value']:'',
        'scm-location-entity-Region' => isset($myReqNode->field_scm_entiy_region['und'])?$myReqNode->field_scm_entiy_region['und'][0]['value']:'',
        'scm-entity-country' => isset($myReqNode->field_scm_entiy_country['und'])?$myReqNode->field_scm_entiy_country['und'][0]['value']:'',
        'scm-entity-address1' => isset($myReqNode->field_scm_entiy_address_line_1['und'])?$myReqNode->field_scm_entiy_address_line_1['und'][0]['value']:'',
        'scm-entity-address2' => isset($myReqNode->field_scm_entiy_address_line_2['und'])?$myReqNode->field_scm_entiy_address_line_2['und'][0]['value']:'',
        'scm-entity-city' => isset($myReqNode->field_scm_entiy_city['und'])?$myReqNode->field_scm_entiy_city['und'][0]['value']:'',
        'scm-entity-state' => isset($myReqNode->field_scm_entiy_state['und'])?$myReqNode->field_scm_entiy_state['und'][0]['value']:'',
        'scm-entity-zipcode' => isset($myReqNode->field_scm_entiy_zip_code['und'])?$myReqNode->field_scm_entiy_zip_code['und'][0]['value']:'',
      );        
      $commands[] = ajax_command_invoke("input.scm-setting-location-entity-node-nid", 'val',array($myReqNode->nid));
      $commands[] = ajax_command_invoke("input.scm-location-entity-name", 'val',array($storage_project['scm-location-entity-name']));
      $commands[] = ajax_command_invoke("textarea.scm-location-entity-description", 'val',array($storage_project['scm-location-entity-description'])); 
      $commands[] = ajax_command_invoke("select.scm-location-entity-Region", 'val',array($storage_project['scm-location-entity-Region']));
      $commands[] = ajax_command_invoke("select.scm-entity-country", 'val',array($storage_project['scm-entity-country'])); 
      $commands[] = ajax_command_invoke("select.scm-entity-country", 'trigger',array('change')); 
      $commands[] = ajax_command_invoke("input.scm-entity-address1", 'val',array($storage_project['scm-entity-address1'])); 
      $commands[] = ajax_command_invoke("input.scm-entity-address2", 'val',array($storage_project['scm-entity-address2'])); 
      $commands[] = ajax_command_invoke("input.scm-entity-city", 'val',array($storage_project['scm-entity-city'])); 
      $commands[] = ajax_command_invoke("input.scm-setting-location-region-statehiddan", 'val',array($storage_project['scm-entity-state']));
      $commands[] = ajax_command_invoke("select.scm-entity-state", 'val',array($storage_project['scm-entity-state'])); 
      $commands[] = ajax_command_invoke("input.scm-entity-zipcode", 'val',array($storage_project['scm-entity-zipcode']));
      if($myReqNode->field_use_the_region_address['und'][0]['value'] == 1) {
        $commands[] = ajax_command_invoke('input.scm-location-entity-use-region', 'prop',array('checked', true));
      }
      $usergetload = explode('|', $myReqNode->field_entity_materials_manager['und'][0]['value']);
      $commands[] = ajax_command_invoke("select.scm-location-entity-materials-manager", 'val',array($usergetload));
      $commands[] = ajax_command_invoke("select.scm-location-entity-materials-manager", 'trigger',array('change')); 

      if(isset($myReqNode->field_contact_id['und'])) {
        $commands[] = ajax_command_invoke("input.scm-entity-contectorid", 'val',array($myReqNode->field_contact_id['und'][0]['value'])); 
      }
      if(isset($myReqNode->field_contact_details['und'])) {
        $commands[] = ajax_command_invoke("input.scm-entity-contact", 'val',array($myReqNode->field_contact_details['und'][0]['value'])); 
      }
      if(isset($myReqNode->field_contact_phone['und'])) {
        $commands[] = ajax_command_invoke("input.scm-entity-contact-phone", 'val',array($myReqNode->field_contact_phone['und'][0]['value'])); 
      }
      if(isset($myReqNode->field_contact_email_address['und'])) {
        $commands[] = ajax_command_invoke("input.scm-entity-contact-email-address", 'val',array($myReqNode->field_contact_email_address['und'][0]['value'])); 
      }

    /*$subquery = db_select('m6connect_scm_setting_department', 'n');
    $subquery->fields('n');
    $subquery->condition('n.entity_nid', $myReqNode->nid, '=');
    $subquery->condition('n.nid', $company->nid, '=');
    $resultsubtype = $subquery->execute()->fetchObject();

    $commands[] = ajax_command_invoke("input.department_new_hidden", 'val',array($myReqNode->nid));
        
      $commands[] = ajax_command_invoke("input.department-name", 'val',array($resultsubtype->title));

      
      $commands[] = ajax_command_invoke("select.assign-user-department", 'val',array(explode("|",$resultsubtype->dpapprover)));
      $commands[] = ajax_command_invoke("select.assign-user-department", 'trigger',array('change')); */

     

      $commands[] = ajax_command_html("#scm-my-request-table", get_scm_location_entity_settings_table_data());  
    }
  } else {
    $commands[] = ajax_command_invoke("input.scm-setting-location-entity-node-nid", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-location-entity-name", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm-location-entity-description", 'val',array('')); 
    $commands[] = ajax_command_invoke("select.scm-entity-country", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-entity-address1", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-entity-address2", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-entity-city", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-setting-location-region-statehiddan", 'val',array('')); 
    $commands[] = ajax_command_invoke("select.scm-entity-state", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-entity-zipcode", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-location-entity-materials-manager-id", 'val',array(''));  
    $commands[] = ajax_command_invoke("input.scm-location-entity-materials-manager", 'val',array('')); 
    ajax_command_invoke("input.scm-entity-contectorid", 'val',array(''));
    ajax_command_invoke("input.scm-entity-contact", 'val',array(''));
    ajax_command_invoke("input.scm-entity-contact-phone", 'val',array(''));
    ajax_command_invoke("input.scm-entity-contact-email-address", 'val',array(''));
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_location_entity_settings_table_data()); 
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
