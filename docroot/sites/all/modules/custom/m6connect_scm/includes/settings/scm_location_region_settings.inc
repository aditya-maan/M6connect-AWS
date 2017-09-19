<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_locations_region_configure_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements = array();
  $elements['scm-setting-menu-items'] = array(
    '#markup' => scm_setting_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline scm-main-menu">',
    '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
  );

  $elements['request-subtype-fieldset'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_location_region_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 main-scm-common-form page-program thumbnail">',
    '#suffix' => '</div>',
  );
  $elements['scm-my-request-listing'] = array(      
    '#markup' => get_scm_location_region_settings_table_data(),
    '#prefix' => '<div class="clearfix"><div class="scm-my-request-listing" id="scm-my-request-table">',
    '#suffix' => '</div></div>',
  );
  return $elements;
}

/*
 *scm request type setting form
 */
function scm_location_region_settings_form($form, &$form_state) {
  $defaultValues = '';
  $getReqNodes = _getting_table_data_call('scm_setting_location_region');
  $form['reset-callback'] = array(
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes' => array('class'=> array('form-control','reset-callback')),
    '#ajax' => array(
      'callback'=> 'change_scm_location_region_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get-location-region-settings'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#attributes' => array('class'=> array('form-control get-my-requests')),
    '#ajax' => array(
      'callback'=> 'change_scm_location_region_settings_callback',
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
  $form['scm-setting-location-region-statehiddan']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-location-region-statehiddan')),  
  );
  $form['scm-setting-location-region-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-location-region-node-nid')),  
  );
  $form['main-container']['full-container-inner-left']['scm-location-region-name'] = array(
    '#title' => 'Region Name',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-location-region-name')),
    '#prefix' => '<div class="project-details-border"><div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
   $form['main-container']['full-container-inner-left']['scm-location-region-description'] = array(
    '#title' => 'Region Description',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('form-control scm-location-region-description resize-textarea-none')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
    '#resizable' => false ,
    '#required' => TRUE,
  );
   
   
  $form['main-container']['full-container-inner-right']['scm-location-region-address']= array(
    '#title' => t('Address'),
    '#type' => 'fieldset',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','row','scm-location-region-address',)),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,  
  );
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;
  $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-country'] = array(
    '#type' => 'select',
    '#title' => 'Choose Country',
    '#options' => $countryNamesList1,
    '#empty_option' => 'Select Country',
    '#attributes' => array('class'=> array('form-control scm-region-country')),
    '#ajax' => array(
      'callback'=> 'change_country_form_state_callback',
      'wrapper' => 'location_zone_main_container_countries',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="project-details-border"><div class="form-item clearfix">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-address1'] = array(
    '#title' => 'Address Line 1',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-region-address1')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-address2'] = array(
    '#title' => 'Address Line 2',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-region-address2')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>', 
  );
  $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-city'] = array(
    '#title' => 'City',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-region-city')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $australian_states = array();
  $none_state = array();
   module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
   $triggeringElement = $form_state['triggering_element']; 
   if($form_state['triggering_element']['#name']=='scm-region-country') {
      if(!empty($triggeringElement['#value'])) {
        $australian_states = addressfield_get_administrative_areas($triggeringElement['#value']);
         $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-state']['#options'] = (!empty($australian_states)?$australian_states:$none_state);
      }
  }
  
  if(!empty($australian_states)){
    $valid = TRUE;
    $noneoption = '- Select State-';
  }else{
    $valid = FALSE;
     $noneoption = '- None-';
  }

  $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-state'] = array(
    '#type' => 'select',  
    '#title' => t('Choose State'),
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-region-state')),
    '#options' => (!empty($australian_states)?$australian_states:$none_state),    
    '#validate' => TRUE,
    '#empty_option' => t($noneoption),
    '#empty_value' => '',
    '#prefix' => '<div class="form-item clearfix" id="location_zone_main_container_countries">',
    '#suffix' => '</div>',
    '#required' => $valid,
  );
  $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-zipcode'] = array(
    '#title' => 'Zip Code',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-region-zipcode')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
 
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    //'#validate' => array('project_scm_my_request_validate'),
    '#submit' => array('scm_location_region_settings_form_submit_callback'),
    '#attributes' => array('class'=>array('scm-location_region_settings-custom-btn')),
    '#prefix' => '<div class="col-sm-12 custom-action-button-div margin-bottom-20" for="closed">',
  );
  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
    '#suffix' => '</div>',
  );
  return $form;
}

  function change_country_form_state_callback($form, &$form_state) {
    $form_state['rebuild'] = TRUE;
    return $form['main-container']['full-container-inner-right']['scm-location-region-address']['scm-region-state'];
  }  
/*
 * Ajax submit callback for 
 * Submitting request type setting form
 */
function scm_location_region_settings_form_submit_callback($form, &$form_state) { //pre($form_state['values'],1);
  global $user; 
  global $company;    
  $formVal = $form_state['values'];
  $getTitle = $formVal['scm-location-region-name'];
  /*
   * Check form submission for new node
    * or an existing one
   */
  if(isset($formVal['scm-setting-location-region-node-nid']) && !empty($formVal['scm-setting-location-region-node-nid'])) {
    $nodesave = node_load($formVal['scm-setting-location-region-node-nid']);
    $nodesave->title = $getTitle; 
    $savestatus = 'updated';
  } else {
    $nodesave = _node_creation_call('scm_setting_location_region',$getTitle);  
    $savestatus = 'saved';  
  }  
  $nodesave->body['und'][0]['value'] = $formVal['scm-location-region-description']; 
  $nodesave->field_scm_setting_country['und'][0]['value'] = $formVal['scm-region-country']; 
  $nodesave->field_scm_setting_adress_line_1['und'][0]['value'] = $formVal['scm-region-address1'];
  $nodesave->field_scm_setting_adress_line_2['und'][0]['value'] = $formVal['scm-region-address2'];
  $nodesave->field_scm_setting_city['und'][0]['value'] = $formVal['scm-region-city'];
  $nodesave->field_scm_setting_state['und'][0]['value'] = $formVal['scm-region-state'];
  $nodesave->field_scm_setting_zip_code['und'][0]['value'] = $formVal['scm-region-zipcode'];
  node_save($nodesave);
  drupal_set_message('Region - '.$getTitle.' has been '.$savestatus.'.');
}
 

function get_scm_location_region_settings_table_data(){
  $rows = array();
  $header = array(
    array('data'=>'Region Name','class'=>array('text-center')),
    array('data'=>'Region Description','class'=>array('text-center')),
    array('data'=>'Address','class'=>array('text-center')),
    array('data'=>'City','class'=>array('text-center')),
    array('data'=>'State','class'=>array('text-center')), 
    array('data'=>'Zipcode','class'=>array('text-center')),
    array('data'=>'Action','class'=>array('text-center')),
  );
  $getMyReqNodes = _getting_table_data_call('scm_setting_location_region');
  foreach($getMyReqNodes as $ids => $values){ 
    $requestNodes = node_load($ids);  
    $countrystate = _get_name_by_country_state($requestNodes->field_scm_setting_country['und'][0]['value'],$requestNodes->field_scm_setting_state['und'][0]['value']);
  $rows[] = array(
      'data' => array(
        array('data' => l('<span class="commitment-nu-cust">'.$requestNodes->title.'</span>', 'edit/'.$values.'/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' => $values))),'class' => array('text-center')),
        array('data' => $requestNodes->body['und'][0]['value'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_setting_adress_line_1['und'][0]['value'].' '.$requestNodes->field_scm_setting_adress_line_2['und'][0]['value'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_setting_city['und'][0]['value'],'class' => array('text-center')),
        array('data' => $countrystate['state'],'class' => array('text-center')),
        array('data' => $requestNodes->field_scm_setting_zip_code['und'][0]['value'],'class' => array('text-center')),
        array('data' => _get_action_button($ids, 'scm_setting_location_region'),'class' => array('text-center')),
    ),
  );
  }  
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table','table-hover','table-bordered','text-center')))); 
  return $output;      
}


function change_scm_location_region_settings_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element']; 
  if($form_state['triggering_element']['#name']=='get-location-region-settings') {
    if(!empty($triggeringElement['#value'])) {
      $myReqNode = node_load($triggeringElement['#value']);  

      $australian_states = addressfield_get_administrative_areas($myReqNode->field_scm_setting_country['und'][0]['value']);
      
      $form['main-container']['full-container-inner-left']['scm-location-region-address']['scm-region-state'] = array(
    '#type' => 'select',  
    '#title' => t('State'),
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-region-state')),
    '#options' => $australian_states,
    '#validate' => TRUE,
    '#empty_option' => t('- Select -'),
    '#prefix' => '<div class="form-item clearfix" id="location_zone_main_container_countries">',
    '#suffix' => '</div>',
  );
      $storage_project = array(
        'scm-location-region-name' => !empty($myReqNode->title)?$myReqNode->title:'',
        'scm-location-region-description' => isset($myReqNode->body['und'])?$myReqNode->body['und'][0]['value']:'',
        'scm-region-country' => isset($myReqNode->field_scm_setting_country['und'])?$myReqNode->field_scm_setting_country['und'][0]['value']:'',
        'scm-region-address1' => isset($myReqNode->field_scm_setting_adress_line_1['und'])?$myReqNode->field_scm_setting_adress_line_1['und'][0]['value']:'',
        'scm-region-address2' => isset($myReqNode->field_scm_setting_adress_line_2['und'])?$myReqNode->field_scm_setting_adress_line_2['und'][0]['value']:'',
        'scm-region-city' => isset($myReqNode->field_scm_setting_city['und'])?$myReqNode->field_scm_setting_city['und'][0]['value']:'',
        'scm-region-state' => isset($myReqNode->field_scm_setting_state['und'])?$myReqNode->field_scm_setting_state['und'][0]['value']:'',
        'scm-region-zipcode' => isset($myReqNode->field_scm_setting_zip_code['und'])?$myReqNode->field_scm_setting_zip_code['und'][0]['value']:'',
      );        
      $commands[] = ajax_command_invoke("input.scm-setting-location-region-node-nid", 'val',array($myReqNode->nid));
      $commands[] = ajax_command_invoke("input.scm-location-region-name", 'val',array($storage_project['scm-location-region-name']));
      $commands[] = ajax_command_invoke("textarea.scm-location-region-description", 'val',array($storage_project['scm-location-region-description'])); 
      $commands[] = ajax_command_invoke("select.scm-region-country", 'val',array($storage_project['scm-region-country'])); 
      $commands[] = ajax_command_invoke("select.scm-region-country", 'trigger',array('change')); 
      $commands[] = ajax_command_invoke("input.scm-region-address1", 'val',array($storage_project['scm-region-address1'])); 
      $commands[] = ajax_command_invoke("input.scm-region-address2", 'val',array($storage_project['scm-region-address2'])); 
      $commands[] = ajax_command_invoke("input.scm-region-city", 'val',array($storage_project['scm-region-city'])); 
      $commands[] = ajax_command_invoke("input.scm-setting-location-region-statehiddan", 'val',array($storage_project['scm-region-state']));
      $commands[] = ajax_command_invoke("select.scm-region-state", 'val',array($storage_project['scm-region-state'])); 
      $commands[] = ajax_command_invoke("input.scm-region-zipcode", 'val',array($storage_project['scm-region-zipcode'])); 
      $commands[] = ajax_command_html("#scm-my-request-table", get_scm_location_region_settings_table_data());  
    }
  } else {
    $commands[] = ajax_command_invoke("input.scm-setting-location-region-node-nid", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-location-region-name", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm-location-region-description", 'val',array('')); 
    $commands[] = ajax_command_invoke("select.scm-region-country", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-region-address1", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-region-address2", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-region-city", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-setting-location-region-statehiddan", 'val',array('')); 
    $commands[] = ajax_command_invoke("select.scm-region-state", 'val',array('')); 
    $commands[] = ajax_command_invoke("input.scm-region-zipcode", 'val',array('')); 
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_location_region_settings_table_data()); 
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
