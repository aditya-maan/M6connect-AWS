<?php
/*
 * Start work for My request slide
 * generating My request form, my request data table to show all records.
 * it also contains the chat feature.  
 */
function scm_my_request_content(){
  global $company;    
  $elements = array();
  $elements['prgram-scm-menu-items'] = array(
    '#markup' => scm_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
    '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
  );
  $elements['scm-my-request-form']= array(
    '#markup' => drupal_render(drupal_get_form('scm_my_request_form')),
    '#prefix' => '<div class="relative row margin-10"><div class="main-scm-common-form col-md-12 padding-10">',
    '#suffix' => '</div>',
  );
  $elements['scm-chatting-container-right'] = array(
    '#markup' => drupal_render(scm_chatting_container()),
    '#prefix' => '<div class="scm_chatting_container-main col-md-7 padding-10" style="display:none;">',
    '#suffix' => '</div></div>',
  );
  $elements['scm-my-request-listing'] = array(      
    '#markup' => get_scm_my_request_table_data(),
    '#prefix' => '<div class="clearfix"><div class="scm-my-request-listing" id="scm-my-request-table">',
    '#suffix' => '</div></div>',
   );
  return $elements;
} 


function scm_my_request_form($form, &$form_state) {
  global $user;   
  global $company;  
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $form_state['triggered_direct_purchase'] = FALSE;
  if (!empty($form_state['triggering_element']['#title']) && $form_state['triggering_element']['#title'] == 'Direct Purchase Only') {
    $form_state['triggered_direct_purchase'] = TRUE;
  }
  if(empty($form_state['add_small_items_storage'])){
    $tempIdentifer = uniqid();
    $form_state['add_small_items_storage'][]  = $tempIdentifer;
  }
  if(empty($form_state['sub_category_fetch_options'])){
    $form_state['sub_category_fetch_options']  = array();
  }
  if(empty($form_state['supply_chain_lead_fetch_options'])){
    $form_state['supply_chain_lead_fetch_options']  = array();
  }
  $form['#attributes']['class'] = array('scm_my_request_form');  
  $getReqNodes = _getting_table_data_call('scm_requests');
  $form['reset-callback'] = array(
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes' => array('class'=> array('form-control','reset-callback')),
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_project_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get-my-requests'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#attributes' => array('class'=> array('form-control get-my-requests')),
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_project_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  /*
   * Getting the value for main-container 2 multi item form
   */
  if(isset($form_state['values'],$form_state['input'],$form_state['triggering_element'],$form_state['triggering_element']['#type'],$form_state['triggering_element']['#name']) && $form_state['triggering_element']['#type']=='select' && $form_state['triggering_element']['#name']=='get-my-requests'){
    $triggeringElement = $form_state['triggering_element'];
    $addItemNode = node_load($triggeringElement['#value']);
    $form_state['add_small_items_storage'] = array();
    $items = field_get_items('node', $addItemNode, 'field_add_item_number');
    foreach ($items as $item) {
      $fc = field_collection_field_get_entity($item);
      $tempIdentifer = uniqid();
      $form_state['add_small_items_storage'][]  = $tempIdentifer;
      $form_state['add_small_items_storage_value'][$tempIdentifer] = array(
        'LIN' =>  isset($fc->field_scm_line_item_number['und'])?$fc->field_scm_line_item_number['und'][0]['value']:'',
        'IMN' =>  isset($fc->field_scm_item_master_number['und'])?$fc->field_scm_item_master_number['und'][0]['value']:'',    
        'NEC' =>  isset($fc->field_line_item_nec['und'])?$fc->field_line_item_nec['und'][0]['value']:'',
        'PUM' =>  isset($fc->field_scm_price_unit_measure_uom['und'])?$fc->field_scm_price_unit_measure_uom['und'][0]['value']:'',    
        'UC' =>   isset($fc->field_scm_uom_converstion['und'])?$fc->field_scm_uom_converstion['und'][0]['value']:'',
        'PUP' =>  isset($fc->field_scm_purchase_uom_price['und'])?$fc->field_scm_purchase_uom_price['und'][0]['value']:'',
        'UP' =>   isset($fc->field_scm_unit_price['und'])?$fc->field_scm_unit_price['und'][0]['value']:'',
        'MCAT' => isset($fc->field_manufacture_catalog_number['und'])?$fc->field_manufacture_catalog_number['und'][0]['value']:'',
        'VCAT' => isset($fc->field_vendor_catalog_number['und'])?$fc->field_vendor_catalog_number['und'][0]['value']:'',
        'ID' =>   isset($fc->field_scm_item_description['und'])?$fc->field_scm_item_description['und'][0]['value']:'',
    );
    }
  } 
  if(isset($form_state['values'],$form_state['input'],$form_state['triggering_element'],$form_state['triggering_element']['#type'],$form_state['triggering_element']['#name']) && $form_state['triggering_element']['#type']=='select' && $form_state['triggering_element']['#name']=='reset-callback'){
     $triggeringElement = $form_state['triggering_element'];
    $addItemNode = node_load($triggeringElement['#value']);
    $form_state['add_small_items_storage'] = array();
    $tempIdentifer = uniqid();
      $form_state['add_small_items_storage'][]  = $tempIdentifer;
  }
  // End for getting the value for main container 2 
  // ==============================================  
  if($form_state['triggering_element']['#name'] =='scm-my-request-category') {    
    $query = db_select('m6connect_scm_settings_categories', 'n');
    $query->fields('n');
    $query->condition('n.companyID', $company->nid, '=');
    $query->condition('n.UID', $user->uid, '=');
    $query->condition('n.id', $form_state['triggering_element']['#value'], '=');
    $resultuser = $query->execute()->fetchObject();
    $subquery = db_select('m6connect_scm_settings_categories', 'n');
    $subquery->fields('n',array('id','title'));
    $subquery->condition('n.parentID', $form_state['triggering_element']['#value'], '=');
    $subquery->condition('n.companyID', $company->nid, '=');
    $subquery->condition('n.UID', $user->uid, '=');
    $subcategoryData = $subquery->execute()->fetchAllKeyed();
    foreach ($subcategoryData as $key => $value) {
      $subcategoryData[$key] = ucwords($value);
    }
    $form_state['sub_category_fetch_options'] = $subcategoryData;
    $form_state['supply_chain_lead_fetch_options'] = $resultuser->userID;
  }
  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')), 
    '#prefix' => '<div class="clearfix"><div id="program_scm_main_container" class="project-detail" style="display:none;" for="closed">',
    '#suffix' => '</div></div>', 
    '#process' => array('project_scm_my_request_container_process'),
  );
  $form['main_containerupper'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('alert-container-section1')),
    '#prefix' => '<div class="clearfix" id="main-class"><div id="alert-container-section1" class="add-new-alert-detail1" style="display:none;" for="closed">',
    '#suffix' => '</div></div>',
    '#process' => array('extrafield_invite_to_m6_process'),
  ); 
  $form['main_container2'] = array(
    '#type' => 'container',
    '#theme' => 'add_item_invite_m6_theme',
    '#attributes' => array('class'=>array('alert-container-section')),
    '#prefix' => '<div class="clearfix" id="main-class"><div id="alert-container-section" class="add-new-alert-detail" style="display:none;" for="closed">', 
    '#suffix' => '</div></div>',
    '#process' => array('add_item_invite_to_m6_process'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#validate' => array('project_scm_my_request_validate'),
    '#submit' => array('project_scm_my_request_submit'),
    '#attributes' => array('class'=>array('scm-my-submit-custom-btn')),
    '#prefix' => '<div class="custom-action-button-div margin-bottom-10" style="display:none;" for="closed">',
  );
  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
    '#suffix' => '</div>',
  );
  return $form;
}

function change_scm_my_request_project_callback($form,&$form_state) {
  $commands = array();
  $commands[] = ajax_command_invoke('.scm_chatting_container-main','show');
  return array('#type' => 'ajax', '#commands' => $commands);
  // global $company;  
  // $commands = array();
  // $triggeringElement = $form_state['triggering_element'];  
  // if($form_state['triggering_element']['#name']=='get-my-requests') {
  //   if(!empty($triggeringElement['#value'])) {
  //   $myReqNode = node_load($triggeringElement['#value']);  
  //     $storage_project = array(
  //       'scr-number' => !empty($myReqNode->title)?$myReqNode->title:'',
  //       'description' => isset($myReqNode->body['und'])?$myReqNode->body['und'][0]['value']:'',
  //       'request-date' => isset($myReqNode->field_request_date['und'])?$myReqNode->field_request_date['und'][0]['value']:'',
  //       'entity' => isset($myReqNode->field_entity['und'])?$myReqNode->field_entity['und'][0]['value']:'',
  //       'department' => isset($myReqNode->field_department['und'])?$myReqNode->field_department['und'][0]['value']:'',
  //       'department-approver' => isset($myReqNode->field_department_approver['und'])?$myReqNode->field_department_approver['und'][0]['value']:'',
  //       'approver-email' => isset($myReqNode->field_approver_email['und'])?$myReqNode->field_approver_email['und'][0]['value']:'',
  //       'request-type' => isset($myReqNode->field_request_type['und'])?$myReqNode->field_request_type['und'][0]['value']:'',
  //       'request-subtype' => isset($myReqNode->field_request_subtype['und'])?$myReqNode->field_request_subtype['und'][0]['value']:'',
  //       'priority-level' => isset($myReqNode->field_priority_level['und'])?$myReqNode->field_priority_level['und'][0]['value']:'',
  //       'category' => isset($myReqNode->field_category['und'])?$myReqNode->field_category['und'][0]['value']:'',
  //       'sub-category' => isset($myReqNode->field_sub_category['und'])?$myReqNode->field_sub_category['und'][0]['value']:'',   
  //       'supply-chain-lead' => isset($myReqNode->field_supply_chain_lead['und'])?$myReqNode->field_supply_chain_lead['und'][0]['value']:'',
  //       'material-manager' => isset($myReqNode->field_materials_manager['und'])?$myReqNode->field_materials_manager['und'][0]['value']:'',
  //       'project-status' => isset($myReqNode->field_project_status['und'])?$myReqNode->field_project_status['und'][0]['value']:'',    
  //       'requester-first-name' => isset($myReqNode->field_requester_to['und'])?$myReqNode->field_requester_to['und'][0]['value']:'',    
  //       'requester-last-name' => isset($myReqNode->field_requester_from['und'])?$myReqNode->field_requester_from['und'][0]['value']:'',   
  //       'on-behalf-fn' => isset($myReqNode->field_requested_on_behalf_of['und'])?$myReqNode->field_requested_on_behalf_of['und'][0]['value']:'',   
  //       'on-behalf-ln' => isset($myReqNode->field_requested_on_behalf_of_fro['und'])?$myReqNode->field_requested_on_behalf_of_fro['und'][0]['value']:'',
        
  //       'request-attachment' => isset($myReqNode->field_my_request_attachment['und'])?$myReqNode->field_my_request_attachment['und'][0]['value']:'',

  //       'effective_date' => isset($myReqNode->field_scm_effective_date['und'])?$myReqNode->field_scm_effective_date['und'][0]['value']:'',
  //       'closeout_date' => isset($myReqNode->field_scm_closeout_date['und'])?$myReqNode->field_scm_closeout_date['und'][0]['value']:'',
  //       'scm-my-request-closeoutremarks' => isset($myReqNode->field_scm_request_closeoutremark['und'])?$myReqNode->field_scm_request_closeoutremark['und'][0]['value']:'',
  //     );        
  //     $requestDate = $storage_project['request-date']!=''?date('m/d/Y', strtotime($storage_project['request-date'])):'';
  //     $effective_date = $storage_project['effective_date']!=''?date('m/d/Y', strtotime($storage_project['effective_date'])):'';
  //     $closeout_date = $storage_project['closeout_date']!=''?date('m/d/Y', strtotime($storage_project['closeout_date'])):'';
  //     $commands[] = ajax_command_invoke("input.my-request-node-nid", 'val',array($myReqNode->nid));
  //     $commands[] = ajax_command_invoke("input.scr-number", 'val',array($storage_project['scr-number']));
  //     $commands[] = ajax_command_invoke("input.request-date", 'val',array($requestDate)); 
  //     $commands[] = ajax_command_invoke("input.effective_date", 'val',array($effective_date));
  //     $commands[] = ajax_command_invoke("select.scm-my-request-entity", 'val',array($storage_project['entity']));
  //     $commands[] = ajax_command_invoke("textarea.scm-my-request-description", 'val',array($storage_project['description']));
  //     $commands[] = ajax_command_invoke("input.scm-my-request-entity", 'val',array($storage_project['entity']));
  //     $commands[] = ajax_command_invoke("input.scm-department-approver", 'val',array($storage_project['department-approver']));
  //     $commands[] = ajax_command_invoke("input.scm-approver-email", 'val',array($storage_project['approver-email']));
  //     $commands[] = ajax_command_invoke("select.scm-my-request-request-type", 'val',array($storage_project['request-type']));   
  //     $commands[] = ajax_command_invoke("select.scm-my-request-request-subtype", 'val',array($storage_project['request-subtype']));   
  //     $commands[] = ajax_command_invoke("select.scm-my-request-priority-level", 'val',array($storage_project['priority-level'])); 
  //     $commands[] = ajax_command_invoke("input.scm-my-request-supply-chain-lead", 'val',array($storage_project['supply-chain-lead']));
  //     $commands[] = ajax_command_invoke("input.scm-my-request-material-manager", 'val',array($storage_project['material-manager']));
  //     $commands[] = ajax_command_invoke("select.scm-my-request-project-status", 'val',array($storage_project['project-status']));
  //     $commands[] = ajax_command_invoke("input.scm-my-request-requester-first-name", 'val',array($storage_project['requester-first-name']));
  //     $commands[] = ajax_command_invoke("input.scm-my-request-requester-last-name", 'val',array($storage_project['requester-last-name']));    
  //     $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-fn", 'val',array($storage_project['on-behalf-fn']));
  //     $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-ln", 'val',array($storage_project['on-behalf-ln']));
  //     $commands[] = ajax_command_invoke("input.closeout_date", 'val',array($closeout_date));
  //     $commands[] = ajax_command_invoke("textarea.scm-my-request-closeoutremarks", 'val',array($storage_project['scm-my-request-closeoutremarks']));
  //     /*$commands[] = ajax_command_invoke("select.scm-my-request-category", 'val',array($storage_project['category']));
  //     $commands[] = ajax_command_invoke("select.scm-my-request-category", 'trigger',array('change')); */
  //     $commands[] = ajax_command_invoke("select.scm-my-request-sub-category", 'val',array($storage_project['sub-category']));
  //     $resultsfld = get_all_custom_fieldsBY_reqestID($myReqNode->nid);
  //     foreach($resultsfld as $key => $value) {
  //       $subquery= db_select('m6connect_scm_settings_mata_field', 'n');
  //       $subquery->fields('n');
  //       $subquery->condition('n.id', $value->fieldID, '=');
  //       $resultflddata = $subquery->execute()->fetchObject();
  //       if($resultflddata->type == 'select') {
  //         $fldtype = 'select';
  //       }
  //       if($resultflddata->type == 'textfield' || $resultflddata->type =='checkbox') {
  //         $fldtype = 'input';
  //       }
  //       if($resultflddata->type == 'textarea') {
  //         $fldtype = 'textarea';
  //       }
  //       $commands[] = ajax_command_invoke($fldtype.".scm_request_field_".$value->fieldID, 'val',array($value->value)); 
  //     }
  //     $commands[] = ajax_command_html("#scm-my-request-table", get_scm_my_request_table_data());
  //     $commands[] = ajax_command_replace("#alert-container-section", render($form['main_container2']));  
  //   $commands[] = ajax_command_invoke('.scm_chatting_container-main','show');
     
  //   }
  // } 
  // else { 
  //   $commands[] = ajax_command_invoke("input.my-request-node-nid", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scr-number", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.request-date", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-entity", 'val',array(''));
  //   $commands[] = ajax_command_invoke("textarea.scm-my-request-description", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-department-approver", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-entity", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-approver-email", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-request-type", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-request-subtype", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-priority-level", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-category", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-sub-category", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-supply-chain-lead", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-material-manager", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm-my-request-project-status", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requester-first-name", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requester-last-name", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-fn", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-my-request-requested-on-behalf-ln", 'val',array(''));
  //   $commands[] = ajax_command_html("#scm-my-request-table", get_scm_my_request_table_data());
  //   $commands[] = ajax_command_invoke("input.line_item_number", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.line_master_number", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.unit_price", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.purchase_unit_of_measure", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.uom_conversion", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.purchase_uom_conversion", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.add_item_description", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.effective_date", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.closeout_date", 'val',array(''));
  //   $commands[] = ajax_command_invoke("textarea.scm-my-request-closeoutremarks", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_directpurchase", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm_request_company", 'val',array(''));  
  //   $commands[] = ajax_command_invoke("input.scm_request_catalogsnumber", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_contactname", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_contactemail", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_contactphone", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_contractnumber", 'val',array(''));
  //   $commands[] = ajax_command_invoke("select.scm_request_vendor_company", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_vendor_catalog", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_vendor_cname", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_vendor_cemail", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_vendor_cphone", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm_request_vendor_cnumber", 'val',array(''));
  //   $commands[] = ajax_command_invoke("textarea.scm_request_note", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-department-approver", 'val',array(''));
  //   $commands[] = ajax_command_invoke("input.scm-approver-email", 'val',array(''));
  //   $commands[] = ajax_command_invoke('.scm_chatting_container-main','hide');
  //   $commands[] = ajax_command_replace("#alert-container-section", render($form['main_container2']));  
  // }
  // return array('#type' => 'ajax', '#commands' => $commands);
}


function project_scm_my_request_container_process($element, &$form_state) {
  global $company, $user;
  $query = db_select('m6connect_scm_settings_categories', 'n');
  $query->fields('n',array('id','title'));
  $query->condition('n.parentID', 0, '=');
  $query->condition('n.companyID', $company->nid, '=');
  $query->condition('n.UID', $user->uid, '=');
  $categoryData = $query->execute()->fetchAllKeyed(0,1);  
  foreach ($categoryData as $key => $value) {
    $categoryData[$key] = ucwords($value);
  }
  if(empty($form_state['sub_category_fetch_options'])) {
    $subcategoryData = array();
  } 
  else {
    $subcategoryData = $form_state['sub_category_fetch_options'];
  }
  if(empty($form_state['supply_chain_lead_fetch_options'])) {
    $supman = array();
  } 
  else {
    $supman = $form_state['supply_chain_lead_fetch_options'];
    foreach (explode('|',$supman) as $ukey => $uvalue) {
      $userdatadb = get_single_userDBbyidcsm($uvalue);
      $userdatadbaa[$ukey] = $userdatadb; 
      //if($userdatadb->is_chain_manager==1){
        $supman_name[$ukey] = $userdatadb->fristname.' '.$userdatadb->lastname;  
      //}
      // if($userdatadb->is_material_manager==1){
      //   $supman_namemat[$ukey] = $userdatadb->fristname.' '.$userdatadb->lastname;  
      // }
    }
    $supman_name = ucwords(implode(',', $supman_name));
    //$supman_namemat = implode(',', $supman_namemat);
  } 
  $currentYear = date('Y');
  $myCounter = variable_get('SCRNumber');
  $makeSr = str_pad($myCounter, 6, "0", STR_PAD_LEFT);  
  $scrNumber = 'SCR-'.$makeSr.'-'.$currentYear;
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full','margin-bottom-10')),
  );
  $element['main-container']['full-container']['full-container-inner-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-5','col-sm-5','col-xs-12','padding-0','project-details-left')),
    '#prefix' => '<div class="row margin-0">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['my-request-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('my-request-node-nid')),  
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scr-number'] = array(
    '#type' => 'textfield',
    '#title' => 'SCR Number',
    '#attributes' => array('class'=> array('form-control scr-number')),
    '#default_value' => isset($defaultValues['scr-number'])?$defaultValues['scr-number']:$scrNumber,
    '#prefix' => '<div class="project-details-border clearfix"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['request-date']= array(
    '#title' => 'Request Date',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#attributes' => array('class'=> array('form-control request-date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#default_value' => isset($defaultValues['request-date'])?$defaultValues['request-date']:date('m/d/Y'),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['effective_date']= array(
    '#title' => 'Effective Date',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#attributes' => array('class'=> array('form-control effective_date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#default_value' => isset($defaultValues['effective_date'])?$defaultValues['effective_date']:date('m/d/Y'),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-entity'] = array(  
    '#title' => 'Entity',
    '#type' => 'select',
    '#options' => array('surgery' => 'Surgery','intensive care' => 'Intensive Care','facilities' => 'Facilities','administration' => 'Administration','clinical' => 'Clinical (General)','emergency department' => 'Emergency Department'),
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-entity')),
    '#empty_option' => 'None',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-department'] = array(  
    '#title' => 'Department',
    '#type' => 'select',
    '#options' => array('surgery' => 'Surgery','intensive care' => 'Intensive Care','facilities' => 'Facilities','administration' => 'Administration','clinical' => 'Clinical (General)','emergency department' => 'Emergency Department'),
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-entity')),
    '#empty_option' => 'None',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-department-approver'] = array(  
    '#title' => 'Department Approver',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-department-approver')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-approver-email'] = array(  
    '#title' => 'Approver Email',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-approver-email')),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-type'] = array(  
    '#title' => 'Request Type',
    '#type' => 'select',
    '#options' => _get_request_type_from_settings(),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-request-type')),
    '#empty_option' => 'Select The Type of Request',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-request-subtype'] = array(  
    '#title' => 'Request Subtype',
    '#type' => 'select',
    '#options' => _get_request_sub_type_from_settings_by_type(),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-request-subtype')),
    '#empty_option' => 'Select Request Subtype',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-priority-level'] = array(  
    '#title' => 'Priority Level',
    '#type' => 'select',
    '#options' => array('critical' => 'Critical','routine' => 'Routine'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-priority-level')),
    '#empty_option' => 'Select Priority',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-category'] = array(  
    '#title' => 'Category',
    '#type' => 'select',
    '#options' => $categoryData,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-category')),
    '#empty_option' => 'Select Category',
    '#ajax' => array(
      'callback'=> 'change_scm_my_request_category_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="category-callbackwrapper clearfix"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-sub-category'] = array(  
    '#title' => 'Subcategory',
    '#type' => 'select',
    '#options' => $subcategoryData,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-sub-category')),
    '#empty_option' => 'Select Subcategory',
    '#prefix' => '<div id="sub-category-container-custom" class="form-item clearfix scm-my-request-sub-category-call">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-supply-chain-lead'] = array(
    '#title' => 'Supply Chain Lead',
    '#type' => 'textfield',
    '#default_value' => $supman_name,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-supply-chain-lead')),
    '#disabled' => TRUE,
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-material-manager'] = array( 
    '#title' => 'Materials Manager',
    '#type' => 'textfield',
    '#default_value' => $supman_namemat,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-material-manager')),
    '#disabled' => TRUE,
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-project-status'] = array(  
    '#title' => 'Project Status',
    '#type' => 'select',
    '#options' => array('active' => 'Active','hold' => 'Hold','terminated' => 'Terminated','completed' => 'Completed'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-project-status')),
    '#empty_option' => 'Select Status',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-first-name'] = array(  
    //'#title' => 'Requester',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requester-first-name')),
    '#prefix' => '<div class="form-item requester clearfix"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Requester</label></div><div class="col-md-6 padding-0"><div class="row margin-5"><div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requester-last-name'] = array(  
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requester-last-name')),
    '#prefix' => '<div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div></div></div></div></div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requested-on-behalf-fn'] = array(  
    //'#title' => 'Requested on Behalf of',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requested-on-behalf-fn')),
    '#prefix' => '<div class="form-item requester clearfix"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Requested on Behalf of</label></div><div class="col-md-6 padding-0"><div class="row margin-5"><div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-requested-on-behalf-ln'] = array(  
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-request-requested-on-behalf-ln')),
    '#prefix' => '<div class="col-md-6 padding-5 form-item"'.$defaultValues['scm-my-request-requested-on-behalf-ln'].'>',
    '#suffix' => '</div></div></div></div></div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['closeout_date']= array(
    '#title' => 'Closeout Date',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#attributes' => array('class'=> array('form-control closeout_date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#default_value' => isset($defaultValues['closeout_date'])?$defaultValues['closeout_date']:date('m/d/Y'),
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-attachment']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[]',
    '#upload_location' => 'public://',  
  '#attributes' => array('id' => 'scm-attachment-upload', 'onchange' => 'javascript:updateList()','class'=> array('scm-my-request-attachment')),
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    //'#attributes' => array('multiple' => 'multiple','class'=> array('scm-my-request-attachment')),    
    '#prefix' => '<div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['attachment_list'] = array(
    '#markup' => '<div id="scm-upload-filelist" style="display:none;"></div>'
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-request-attachment-link']= array(
    '#markup' => '<a href="javascript:void(0);" class="scm-my-request-attachment-link">Click to Browse and Upload Files</a>',
    '#prefix' => '<div class="form-item requester clearfix"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Attachments</label></div>',
    '#suffix' => '</div></div></div>',
  );
  $element['main-container']['full-container']['scm-my-request-description'] = array(
    '#title' => 'Description',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('form-control scm-my-request-description')),
    '#default_value' => isset($defaultValues['scm-my-request-description'])?strip_tags($defaultValues['scm-my-request-description']):'',
    '#prefix' => '<div class="clearfix form-item" id="custom-etc-attach">',
    '#suffix' => '</div>',

  );

  $element['main-container']['full-container']['scm-my-request-closeoutremarks'] = array(
    '#title' => 'Closeout Remarks',
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('form-control scm-my-request-closeoutremarks')),
    '#default_value' => isset($defaultValues['scm-my-request-closeoutremarks'])?strip_tags($defaultValues['scm-my-request-closeoutremarks']):'',
    '#prefix' => '<div class="clearfix form-item" id="custom-etc-attach">',
    '#suffix' => '</div>',

  );
  return $element;
}
function change_scm_my_request_category_callback($form,&$form_state) {  
  $form_state['rebuild'] = TRUE; 
   dpm($form);
  return $form['main-container']['main-container'];  
}

function project_scm_my_request_validate($form, &$form_state) {
  if($_FILES['files']['name'] != '')  {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
      $file = file_save_upload($i, array( 
        'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
      ));
      if ($file) {    
        if ($file = file_move($file, 'private://')) {
          $form_state['values']['scm-my-request-attachment'][$i] = $file;
        } 
      }
    }
  }
}

function project_scm_my_request_submit(&$form, &$form_state) {
  // global $user;
  // global $company;
  // $formVal = $form_state['values'];
  // $getTitle = $formVal['scr-number'];
  // $alert = $formVal['alert'];  
  // if(isset($formVal['my-request-node-nid']) && !empty($formVal['my-request-node-nid'])) {
  //   $nodesave = node_load($formVal['my-request-node-nid']);
  //   $nodesave->title = $getTitle; 
  //     $savestatus = 'updated';     
  // } 
  // else {
  //   $nodesave = _node_creation_call('scm_requests',$getTitle);  
  //   $savestatus = 'saved';  
  
  // $currentYear = date('Y');
  // $myCounter = variable_get('SCRNumber');
  // $makeSr = str_pad($myCounter, 6, "0", STR_PAD_LEFT);  
  // $scrNumber = 'SCR-'.$makeSr.'-'.$currentYear;
  
  // $scrctNumber = variable_get('SCRNumber');
  //   variable_set('SCRNumber', $scrctNumber + 1);
  // }  
  // $nodesave->body['und'][0]['value'] = $formVal['scm-my-request-description']; 
  // $nodesave->field_request_date['und'][0]['value'] = $formVal['request-date']; 
  // $nodesave->field_entity['und'][0]['value'] = $formVal['scm-my-request-entity'];
  // $nodesave->field_department['und'][0]['value'] = $formVal['scm-my-request-department'];
  // $nodesave->field_department_approver['und'][0]['value'] = $formVal['scm-my-request-department-approver'];
  // $nodesave->field_approver_email['und'][0]['value'] = $formVal['scm-my-request-approver-email'];
  // $nodesave->field_request_type['und'][0]['value'] = $formVal['scm-my-request-request-type'];
  // $nodesave->field_request_subtype['und'][0]['value'] = $formVal['scm-my-request-request-subtype'];
  // $nodesave->field_priority_level['und'][0]['value'] = $formVal['scm-my-request-priority-level'];
  // $nodesave->field_category['und'][0]['value'] = $formVal['scm-my-request-category'];
  // $nodesave->field_sub_category['und'][0]['value'] = $formVal['scm-my-request-sub-category'];
  // $nodesave->field_supply_chain_lead['und'][0]['value'] = $formVal['scm-my-request-supply-chain-lead'];
  // $nodesave->field_materials_manager['und'][0]['value'] = $formVal['scm-my-request-material-manager'];
  // $nodesave->field_project_status['und'][0]['value'] = $formVal['scm-my-request-project-status'];  
  // $nodesave->field_requester_to['und'][0]['value'] = $formVal['scm-my-request-requester-first-name'];
  // $nodesave->field_requester_from['und'][0]['value'] = $formVal['scm-my-request-requester-last-name'];
  // $nodesave->field_requested_on_behalf_of['und'][0]['value'] = $formVal['scm-my-request-requested-on-behalf-fn'];
  // $nodesave->field_requested_on_behalf_of_fro['und'][0]['value'] = $formVal['scm-my-request-requested-on-behalf-ln'];
  // $nodesave->field_scm_effective_date['und'][0]['value'] = $formVal['effective_date']; 
  // $nodesave->field_scm_closeout_date['und'][0]['value'] = $formVal['closeout_date']; 
  // $nodesave->field_scm_request_closeoutremark['und'][0]['value'] = $formVal['scm-my-request-closeoutremarks']; 
  // $nodesave->field_scm_request_directpurchase['und'][0]['value'] = $formVal['scm_request_directpurchase']; 
  // $nodesave->field_scm_request_company['und'][0]['value'] = $formVal['scm_request_company']; 
  // $nodesave->field_scm_request_catalogsnumber['und'][0]['value'] = $formVal['scm_request_catalogsnumber']; 
  // $nodesave->field_scm_request_contactname['und'][0]['value'] = $formVal['scm_request_contactname']; 
  // $nodesave->field_scm_request_contactemail['und'][0]['value'] = $formVal['scm_request_contactemail']; 
  // $nodesave->field_scm_request_contactphone['und'][0]['value'] = $formVal['scm_request_contactphone']; 
  // $nodesave->field_scm_request_contractnumber['und'][0]['value'] = $formVal['scm_request_contactphone']; 
  // $nodesave->field_scm_request_vendor_company['und'][0]['value'] = $formVal['scm_request_vendor_company']; 
  // $nodesave->field_scm_request_vendor_catalog['und'][0]['value'] = $formVal['scm_request_vendor_catalog']; 
  // $nodesave->field_scm_request_vendor_cname['und'][0]['value'] = $formVal['scm_request_vendor_cname']; 
  // $nodesave->field_scm_request_vendor_cemail['und'][0]['value'] = $formVal['scm_request_vendor_cemail']; 
  // $nodesave->field_scm_request_vendor_cphone['und'][0]['value'] = $formVal['scm_request_vendor_cphone']; 
  // $nodesave->field_scm_request_vendor_cnumber['und'][0]['value'] = $formVal['scm_request_vendor_cnumber']; 
  // $nodesave->field_scm_request_notes['und'][0]['value'] = $formVal['scm_request_note'];
  // foreach($nodesave->field_add_item_number['und'] as $fkey => $fvalue) {
  //   $fvaluenode[] = $fvalue['value'];
  //   unset($nodesave->field_add_item_number['und'][$fkey]);
  // }
  // entity_delete_multiple('field_collection_item', $fvaluenode);
  // node_save($nodesave);
  // $count = 0; 
  // foreach($alert as $key => $alert_detail) {
  //   $field_collection_item = entity_create('field_collection_item', array('field_name' => 'field_add_item_number')); 
  //   $field_collection_item->setHostEntity('node', $nodesave);
  //   $field_collection_item->field_scm_line_item_number[LANGUAGE_NONE][$count]['value'] = $alert_detail['line_item_number'];
  //   $field_collection_item->field_scm_item_master_number[LANGUAGE_NONE][$count]['value'] = $alert_detail['line_master_number'];    
  //   $field_collection_item->field_line_item_nec[LANGUAGE_NONE][$count]['value'] = $alert_detail['nec_number'];
  //   $field_collection_item->field_scm_price_unit_measure_uom[LANGUAGE_NONE][$count]['value'] = $alert_detail['purchase_unit_of_measure'];
  //   $field_collection_item->field_scm_uom_converstion[LANGUAGE_NONE][$count]['value'] = $alert_detail['uom_conversion'];  
  //   $field_collection_item->field_scm_purchase_uom_price[LANGUAGE_NONE][$count]['value'] = $alert_detail['purchase_uom_conversion'];        
  //   $field_collection_item->field_scm_unit_price[LANGUAGE_NONE][$count]['value'] = $alert_detail['price_each']; 
  //   $field_collection_item->field_manufacture_catalog_number[LANGUAGE_NONE][$count]['value'] = $alert_detail['manufacture_catalog_number'];     
  //   $field_collection_item->field_vendor_catalog_number[LANGUAGE_NONE][$count]['value'] = $alert_detail['vendor_catalog'];    
  //   $field_collection_item->field_scm_item_description[LANGUAGE_NONE][$count]['value'] = $alert_detail['add_item_description'];     
  //   $count++;
  // }
  // $field_collection_item->save();
  // if(isset($formVal['scm-my-request-attachment']) && !empty($formVal['scm-my-request-attachment'])) {
  //   foreach ($form_state['values']['scm-my-request-attachment'] as $imgkey => $file) {
  //     if(!isset($nodesave->field_commitment_attachment['und'])){
  //       $nodesave->field_commitment_attachment['und'] = array();
  //     }
  //     $new_file = file_load($file->fid);
  //     $file_arr = (array)$new_file;
  //     $file_arr['display'] = 1;   
  //     $nodesave->field_commitment_attachment['und'][] = $file_arr;
  //   }
  // }
  // foreach($formVal['Allfieldsdata'] as $container) {
  //   foreach ($container as $key => $value) {
  //     if(isset($value) && !empty($value)) {
  //       insert_custom_field_data($key,$nodesave->nid,$value);
  //     }
  //   }
  // }
  
  // drupal_set_message('My Request - '.$getTitle.' has beed '.$savestatus.'.');
}

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
function get_scm_my_request_table_data() {
  $rows = array();
  $header = array(
    array('data'=>'SCR Number','class'=>array('text-center')),
    array('data'=>'Need by Date','class'=>array('text-center')),
    array('data'=>'Request Type','class'=>array('text-center')),
    array('data'=>'Description','class'=>array('text-center')),
    array('data'=>'Requestor','class'=>array('text-center')), 
    array('data'=>'Category','class'=>array('text-center')),
    array('data'=>'Supply Chain Lead','class'=>array('text-center')),
    array('data'=>'Status','class'=>array('text-center')),
    array('data'=>'Action','class'=>array('text-center')),
  );
  $rows[0] = array(
      'data' => array(
      array('data' => l('<span class="commitment-nu-cust">'.'SCR-000004-2017'.'</span>', 'edit/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' =>'' ))),'class' => array('text-left')),
      array('data' => '2017-06-08','class' => array('text-center')),
      array('data' => 'New Product Request-recurring','class' => array('text-center')),
      array('data' => 'This request related to the leboratory','class' => array('text-left')),
      array('data' => 'María-jose','class' => array('text-center')),
      array('data' => 'Radiology<br>Vascular Graft','class' => array('text-center')),
      array('data' => 'Adi Dwivedi','class' => array('text-center')),
      array('data' => 'Archive','class' => array('text-left')),
      array('data' => _get_action_button('0', 'scm_requests'),'class' => array('text-center')),
    ),
  );
  // $getMyReqNodes = _getting_table_data_call('scm_requests');
  // foreach($getMyReqNodes as $values => $ids){ 
  //   $requestNodes = node_load($values); 
  //   $maincat = get_single_catbyid($requestNodes->field_category['und'][0]['value']);
  //   $subcat = get_single_catbyid($requestNodes->field_sub_category['und'][0]['value']);  
  // $rows[] = array(
  //     'data' => array(
  //     array('data' => l('<span class="commitment-nu-cust">'.$requestNodes->title.'</span>', 'edit/'.$values.'/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' => $values))),'class' => array('text-left')),
  //     array('data' => $requestNodes->field_request_date['und'][0]['value'],'class' => array('text-center')),
  //     array('data' => $requestNodes->field_request_type['und'][0]['value'],'class' => array('text-center')),
  //     array('data' => $requestNodes->body['und'][0]['value'],'class' => array('text-left')),
  //     array('data' => $requestNodes->field_requester_to['und'][0]['value'].'<br>'.$requestNodes->field_requester_from['und'][0]['value'],'class' => array('text-center')),
  //     array('data' => $maincat->title.'<br>'.$subcat->title,'class' => array('text-center')),
  //     array('data' => $requestNodes->field_supply_chain_lead['und'][0]['value'],'class' => array('text-center')),
  //     array('data' => $requestNodes->field_project_status['und'][0]['value'],'class' => array('text-left')),
  //     array('data' => _get_action_button($values, 'scm_requests'),'class' => array('text-center')),
  //   ),
  // );
  // }  
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table','table-hover','table-bordered','text-center')))); 
  return $output;      
}

function get_single_catbyid($pvalue){
    $getquery = db_select('m6connect_scm_settings_categories', 'n');
    $getquery->fields('n');
    $getquery->condition('n.id', $pvalue, '=');
    $getresult = $getquery->execute()->fetchObject();
    return $getresult;
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
  if(isset($form_state['values']['get-my-requests']) && !empty($form_state['values']['get-my-requests'])){
    $fieldsdata = get_all_custom_fieldsBY_reqestID($form_state['values']['get-my-requests']);
  }
  $alldefultfields = _get_allField_scm_settings_matadetails();
  foreach($alldefultfields as $key => $value) {
    $vendor_class = $value->Label == 'Vendor' ? 'toggle-this-container' : '';
    $vendor_style = $value->Label == 'Vendor' ? 'display:none;' : '';
    $grouplabel = $value->Label;
    if($value->Numberofvalues==1) {
      $grouplabel = '';
    }
    $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key]= array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('add-custom-dependent-field')),
      '#prefix' => '<div class="clearfix ' . $vendor_class . ' col-md-4" id="main-class-' . $key . '" style="' . $vendor_style . '"><label>'.$grouplabel.'</label><div id="add-custom-dependent-field" class="add-new-alert-detail thumbnail padding-10 clearfix">', 
      '#suffix' => '</div></div>',
    );
    foreach($value->fieldsdata  as $fkey => $fvalue) {
      if($fvalue->type=='company') {
        $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]= array(
          '#type' => 'textfield',
          '#attributes'=> array('class'=> array('form-control vendor','workflow-auto'),'placeholder'=>t($fvalue->Label)),
          '#autocomplete_path' => 'commitment-company/autocomplete',
          // '#ajax' => array(
          //   'callback' => 'commitment_autocomplete_callback',
          //   'event' => 'blur',
          //   'wrapper' => 'workflow-container-section',
          //   'method' => 'replace',
          //   'effect' => 'fade',
          // ),
          '#parents' => array('Allfieldsdata', strtolower($value->Label), $fvalue->id),
          '#prefix' => '<div class="clearfix">', 
          '#suffix' => '</div>',
        );
      } else {
        $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id] = array(
          '#type' => $fvalue->type,
          '#attributes' => array('class'=>array('scm_request_field_'.$fvalue->id,), 'placeholder'=>t($fvalue->Label)),
          '#parents' => array('Allfieldsdata', strtolower($value->Label), $fvalue->id),
          '#prefix' => '<div class="clearfix">', 
          '#suffix' => '</div>',
        );
        if($fvalue->type=='select') {
          $options = array();
          $lines = explode(PHP_EOL, $fvalue->value);
          foreach($lines as $line) {
            $line = explode('|', $line);
            $options[$line[0]] = $line[1];
          }

          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#empty_option'] = 'Select '.$fvalue->Label;
          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#options'] = $options;
          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#default_value'] = 0;
        }

        if($fvalue->type=='checkbox') {
          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#title']=t($fvalue->Label);
          if ($fvalue->Label == 'Direct Purchase Only') {
            $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#attributes'] = array('class'=>array('scm_request_field_'.$fvalue->id, 'toggle-scm-vendor-section'), 'placeholder'=>t($fvalue->Label));
          }
          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#default_value'] = 0;
        }
        if($value->size=='12') {
          unset($element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#title']);
          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#prefix'] = '<div class="clearfix">'; 

          $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#suffix'] = '</div>'; 
        }
        if(isset($fieldsdata[$fvalue->id]) && !empty($fieldsdata[$fvalue->id])) {
          if(isset($fieldsdata[$fvalue->id]) && !empty($fieldsdata[$fvalue->id])) {
            $element['scm-request-request'][$key]['scm-request-'.$value->scm_group_key][$fkey]['scm_request_field_'.$fvalue->id]['#default_value'] = $fieldsdata[$fvalue->id]->value;
          }
        }
      }
    }
  }
  return $element;
}

function add_items_field_action_callback($element, &$form_state) {
  //dpm($form_state);
}

function add_item_invite_to_m6_process($element, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $storage = $form_state['add_small_items_storage'];
  $element['#storage'] = $storage;
  foreach ($storage as $key => $uniqId) {
    $element['line_item_number'][$uniqId] = array(
      '#type' => 'textfield', 
      '#attributes'=> array('class'=> array('form-control','workflow-auto','line_item_number')),
      '#parents' => array('alert',$uniqId,'line_item_number'),
    );
    $element['line_master_number'][$uniqId] = array(
      '#type' => 'textfield', 
      '#attributes'=> array('class'=> array('form-control','workflow-auto','line_master_number'),'placeholder'=>'Line master number'),
      '#parents' => array('alert',$uniqId,'line_master_number'),
    );
    $element['nec_number'][$uniqId] = array(
      '#type' => 'select', 
    '#options' => array('4027' => '4027|Vascula','4024' => '4024|Implants'),
      '#default_value' => '',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','nec_number')),
      '#parents' => array('alert',$uniqId,'nec_number'),
    );
   $element['purchase_unit_of_measure'][$uniqId] = array(
      '#type' => 'select', 
      '#default_value' => '',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','purchase_unit_of_measure')),
      '#parents' => array('alert',$uniqId,'purchase_unit_of_measure'),
    );  
    $element['uom_conversion'][$uniqId] = array(
      '#type' => 'textfield',   
      '#attributes'=> array('class'=> array('form-control','workflow-auto','uom_conversion')),
      '#parents' => array('alert',$uniqId,'uom_conversion'),
    );  
    $element['purchase_uom_conversion'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','purchase_uom_conversion')),
      '#parents' => array('alert',$uniqId,'purchase_uom_conversion'),
  );
  $element['purchase_uom_conversion'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','purchase_uom_conversion')),
      '#parents' => array('alert',$uniqId,'purchase_uom_conversion'),
  );
  $element['price_each'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','price_each')),
      '#parents' => array('alert',$uniqId,'price_each'),
  );
  $element['manufacture_catalog_number'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','manufacture_catalog_number')),
      '#parents' => array('alert',$uniqId,'manufacture_catalog_number'),
  );
  $element['vendor_catalog'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','vendor_catalog')),
      '#parents' => array('alert',$uniqId,'vendor_catalog'),
  );
  $element['add_item_description'][$uniqId] = array(
      '#type' => 'textfield', 
      '#default_value' => '',     
      '#attributes'=> array('class'=> array('form-control','workflow-auto','add_item_description')),
      '#parents' => array('alert',$uniqId,'add_item_description'),
    );
  $element['remove'][$uniqId] = array(
      '#type' => 'submit',
      '#value' => 'remove_lineItem',
      '#name' => $uniqId,
      '#attributes'=> array('style'=> array('font-family:FontAwesome;'),'class'=>array('alert-container-section', 'workflow-remove-submit')),
      '#parents' => array('alert', $uniqId, 'remove'),
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
        $element['price_each'][$uniqId]['#default_value'] = $stdefault['UP'];
        $element['manufacture_catalog_number'][$uniqId]['#default_value'] = $stdefault['MCAT'];
    $element['vendor_catalog'][$uniqId]['#default_value'] = $stdefault['VCAT'];       
    $element['add_item_description'][$uniqId]['#default_value'] = $stdefault['ID'];       
      }    
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
  return $form['main_container2'];
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
  return $form['main_container2'];
}

function project_scm_add_items_container_process($element, &$form_state) {
  // My Request calculation
  $currentYear = date('Y');
  $myCounter = variable_get('SCRNumberAddItem');
  //$makeSr = str_pad($myCounter, 6, "0", STR_PAD_LEFT);
  $makeSr = str_pad($myCounter + 1, 6, "0", STR_PAD_LEFT);  
  $scrNumberAddItem = 'SCR-'.$makeSr.'-'.$currentYear;
  
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full',)),
  );
  $element['main-container']['full-container']['full-container-inner-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );  
  $element['main-container']['full-container']['full-container-inner-right'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );
  $element['add-item-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('add-item-node-nid')),  
  );
  $element['main-container']['full-container']['full-container-inner-left']['add-item-scr-number'] = array(
    '#type' => 'textfield',
    '#title' => 'SCR Number',
    '#attributes' => array('class'=> array('form-control add-item-scr-number')),
    '#default_value' => isset($defaultValues['add-item-scr-number'])?$defaultValues['add-item-scr-number']:$scrNumberAddItem,
  '#prefix' => '<div class="project-details-border clearfix"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['request-date']= array(
    '#title' => 'Request Date',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#attributes' => array('class'=> array('form-control request-date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#default_value' => isset($defaultValues['request-date'])?$defaultValues['request-date']:'',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['effective-date']= array(
    '#title' => 'Effective Date',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#attributes' => array('class'=> array('form-control effective-date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#default_value' => isset($defaultValues['effective-date'])?$defaultValues['effective-date']:'',
    '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-item-add-item-type'] = array(  
    '#title' => 'Add Item Type',
  '#type' => 'select',
    '#options' => array('add' => 'Add','change' => 'Change','inactivate' => 'Inactivate'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-item-add-item-type')),
    '#empty_option' => 'Select Add Item Type',
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-my-item-entity'] = array(  
    '#title' => 'Entity',
  '#type' => 'select',
    '#options' => array('surgery' => 'Surgery','intensive care' => 'Intensive Care','facilities' => 'Facilities','administration' => 'administration','clinical' => 'Clinical (General)','emergency department' => 'Emergency Department'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-my-item-entity')),
    '#empty_option' => 'None',
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );    
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-item-approver-email'] = array(  
    '#title' => 'Approver Email',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-item-approver-email')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-items-requester-first-name'] = array(
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-requester-first-name')),
  '#prefix' => '<div class="form-item requester clearfix"><div class="row margin-0"><div class="col-md-6 padding-0"><label>Requester</label></div><div class="col-md-6 padding-0"><div class="row margin-5"><div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-items-requester-last-name'] = array(
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-requester-last-name')),
  '#prefix' => '<div class="col-md-6 padding-5 form-item">',
    '#suffix' => '</div></div></div></div></div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-items-materials-manager'] = array(  
    '#title' => 'Materials Manager',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-materials-manager')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-items-master-number'] = array(  
    '#title' => 'Item Master Number',
  '#required' => TRUE,
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-master-number')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-items-nec'] = array(  
    '#title' => 'NEC',
  //'#required' => TRUE,
  '#type' => 'select',
    '#options' => array(),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-nec')),
    '#empty_option' => 'Select NEC Code',
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-left']['scm-add-items-closeout-date'] = array(  
    '#title' => 'Closeout Date',
  '#type' => 'textfield',
  '#disabled' => true,
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-closeout-date')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  ); 
  
  /* Vendor Section left area of the form */
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left']['scm-add-items-company'] = array(  
    '#title' => 'Company',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-company')),
  '#prefix' => '<div class="project-details-border clearfix"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left']['scm-add-items-catalog-no'] = array(  
    '#title' => 'Catalog Number',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-catalog-no')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left']['scm-add-items-contact-name'] = array(  
    '#title' => 'Contact Name',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-name')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left']['scm-add-items-contact-email'] = array(  
    '#title' => 'Contact Email',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-email')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left']['scm-add-items-contact-phone'] = array(  
    '#title' => 'Contact Phone',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-phone')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-left']['scm-add-items-contact-number'] = array(  
    '#title' => 'Contact Number',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-number')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
  /* Vendor Section right area of the form */
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right']['scm-add-items-company-ven'] = array(  
    '#title' => 'Company',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-company-ven')),
  '#prefix' => '<div class="project-details-border clearfix"><div class="form-item clearfix">',
    '#suffix' => '</div>',
  );  
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right']['scm-add-items-catalog-no-ven'] = array(  
    '#title' => 'Catalog Number',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-catalog-no-ven')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right']['scm-add-items-contact-name-ven'] = array(  
    '#title' => 'Contact Name',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-name-ven')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right']['scm-add-items-contact-email-ven'] = array(  
    '#title' => 'Contact Email',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-email-ven')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right']['scm-add-items-contact-phone-ven'] = array(  
    '#title' => 'Contact Phone',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-phone-ven')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['full-container-inner-right-right']['scm-add-items-contact-number-ven']= array(  
    '#title' => 'Contact Number',
  '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-add-items-contact-number-ven')),
  '#prefix' => '<div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
  $element['main-container']['full-container']['full-container-inner-right']['scm-add-items-notes']= array(
    '#type' => 'textarea',
    '#title' => 'Notes',
    '#attributes' => array('class'=> array('form-control','scm-add-items-notes')),
    '#default_value' => isset($defaultValues['scm-add-items-notes'])?strip_tags($defaultValues['scm-add-items-notes']):'',
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div></div>',
  );   
  return $element;
}
  
function get_scm_add_items_table_data(){
  $rows = array();
  $header = array(
    array('data'=>'SCR Number','class'=>array('text-center')),
    array('data'=>'Effective Date','class'=>array('text-center')),
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
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table','table-hover','table-bordered','text-center')))); 
  return $output;      
}

function scm_chatting_container() {
  global $user; global $company; 
  $currentUser = user_load($user->uid);
  $elements = array();
  $userinfo = array(); 
  $userOptions = array();
  $userDefaultValue='';
  $userDefaultdataObj = '';
  drupal_add_js('sites/all/libraries/emojione/emojionearea.js');
  drupal_add_css('sites/all/libraries/emojione/emojionearea.min.css');
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/scm_chatmessaging.js');
  drupal_add_js(array('m6connect_messenger' => array('connectedusers'=>$connectedUserSettings)), 'setting');
  $userOptions['new_mapping'] = 'new_mapping';
  $connectedUsers = array();
  //$NorecipientActiveClass = ($userDefaultValue == 'new_mapping')?' user-active':'';
  $mappingidKey = 'new_mapping';
  $connectedUserSettings = array(); 
  $connectedUsersdb = Scm_current_user_by_company();

  
  if($connectedUsersdb && !empty($connectedUsersdb)){
    foreach($connectedUsersdb as $mappingidKey => $dataObj){
    if($mappingidKey === 0){ $user_active = 'user-active'; } 
    else { $user_active = ''; }
      $mappingidKey = $dataObj->mapping_id;
      $dataObjuser_pic = theme('image', array('path' =>'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:25px;height:25px;')));
      $userinfo[$mappingidKey]  = '<div id="'.$mappingidKey.'" class="msg-connected-user-info msg-connected-user clearfix '.$user_active.'">';
      $userinfo[$mappingidKey] .= '  <div class="msg-connected-info">';
      $userinfo[$mappingidKey] .= '    <div class="msg-connected-picture msg-connected-user-inner padding-0">';
      $userinfo[$mappingidKey] .= '      <span class="msg-pic">'.$dataObjuser_pic.'</span>';
      $userinfo[$mappingidKey] .= '    </div>';
      $userinfo[$mappingidKey] .= '    <div class="msg-connected-user-data msg-connected-user-inner padding-5">';
      $userinfo[$mappingidKey] .= '      <div class="msg-connected-user-name">'.$dataObj->fristname.' '.$dataObj->lastname.'</div>';
      $userinfo[$mappingidKey] .= '      <div class="msg-connected-user-desg"></div>';
      $userinfo[$mappingidKey] .= '    </div>';
      $userinfo[$mappingidKey] .= '  </div>';
      $userinfo[$mappingidKey] .= '</div>';
      $userOptions[$mappingidKey] = $mappingidKey;
    }
  } 
  else {
    $userDefaultValue = 'new_mapping';
    $headerDataObj = array(
      'show_in_mapping' =>0,
      'id' => 0,
      'mapping_id' => 'new_mapping',
      'group_name' => array('Add New Recipients'),
      'job_title' => '' ,
      'user_pic' => theme('image', array('path' =>'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;'))),
      'mapping_type' => 'user',
      'no_recipients' =>1,
      'all_names' => array($currentUser->uid => ucwords($currentUser->realname)),
      'connected_user' => array($currentUser->uid),
    );
    $userDefaultdataObj = (object)$headerDataObj;
  }
  $dfusertquery = db_select('m6connect_scm_settings_user_database', 'n');
  $dfusertquery->join('m6connect_scm_messaging_connect_users', 'uc', 'n.id = uc.user_uid'); 
  $dfusertquery->fields('n');
  $dfusertquery->fields('uc');
  $dfusertquery->condition('n.companyID', $company->nid, '=');
  $dfusertquery->condition('n.userID', $user->uid, '=');
  $dfusertquery->condition('uc.service', 'scm', '=');
  $dfusertquery->condition('n.id', $connectedUsersdb[0]->user_uid, '=');
  $userDefaultdataObj = $dfusertquery->execute()->fetchObject();
  $userDefaultValue = $userDefaultdataObj->mapping_id;
  $elements['connected-list'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('margin-0','row', 'connected-list-container-outer')),
    '#prefix' => '<div class="user-connected-user m6message-full-overlay clearfix user_messaging_thread_form" data-mapping="'.$userDefaultValue.'">',
    '#suffix' => '</div>',
  );
  $elements['connected-list']['left-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('col-md-3','col-sm-3','col-xs-12','padding-0')),
  );
  $elements['connected-list']['right-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('col-md-9','col-sm-9','col-xs-12','padding-0')),
  );
  $elements['connected-list']['left-container']['connected-user-select']= array(
    '#markup' => drupal_render(drupal_get_form('scmchat_user_messaging_thread_switch_form',$userOptions,$userDefaultValue)),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );
  $createRecipientLink = '';
  if (!$_on_company_profile) {
    $creteImage = theme('image', array('path' => 'sites/all/themes/m6connect/images/messanger_icons/fa-user-create-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:35px;height:35px;')));
    $createRecipientLink = $creteImage;
  }
  $elements['connected-list']['left-container']['connected-user-header']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('msg-connected-header-main-container-inner','message-user-heading')),
    '#prefix' => '<div class="msg-connected-header-main-containerscm msg-connected-header-main clearfix">',
    '#suffix' => '</div>',
  );
  $elements['connected-list']['left-container']['connected-user-header']['connected-user-header-markup'] = array(
    '#markup' => '<div class="col-md-9 col-sm-9 col-xs-9 padding-5">
                    <div class="create-messenger-group-text">'._get_user_full_name($user->uid).'</div>
                  </div>
                  <div class="col-md-3 col-sm-3 col-xs-3 padding-5 text-right">
                    <div class="create-messenger-group">'.$createRecipientLink.'</div>
                  </div>',
          
    '#prefix' => '<div class="row margin-5">',
    '#suffix' => '</div>',                    
  );
  $elements['connected-list']['left-container']['connected-user-list'] = array(
    '#markup' => implode('',$userinfo),
    '#prefix' => '<div class="msg-connected-user-list-req clearfix">',
    '#suffix' => '</div>',
  );
  $elements['connected-list']['right-container']['connected-user-form'] = array(
    '#markup' => drupal_render(drupal_get_form('scmchat_user_messaging_thread_form',$userDefaultdataObj)),
    '#prefix' => '<div id="user-messaging-thread-form-container">', 
    '#suffix' => '</div>',
  );
  $elements['messenger-dialog'] = array(
    '#markup' => '',
    '#prefix' => '<div id="messenger-dialog" class="messenger-dialog">',
    '#suffix' => '</div>',
  );
  $elements['messenger-confirmation'] = array(
    '#markup' => '',
    '#prefix' => '<div id="messenger-confirmation-dialog" class="messenger-confirmation-dialog">',
    '#suffix' => '</div>',
  );
  return $elements;
}

function scmchat_user_messaging_thread_switch_form($form,&$form_state,$userOptions= array(),$defaultValue='') {  
  $form['#attributes'] = array('class'=>array('scmchat_user_messaging_thread_switch_form'));
  $form['connected-user-select']= array(
    '#type' => 'select',
    '#options' => $userOptions,
    '#attributes' => array('class'=> array('connected-user-select')),
    '#ajax' => array(
      'callback'=> 'scmchat_user_messaging_thread_switch_callback',
      'wrapper' => 'scm_request_subtype_settings_main',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="thumbnail padding-10 clearfix" id="scmchat_user_messaging_thread_switch_frm">',
    '#suffix' => '</div>',
  );
  if(!empty($defaultValue)){
    $form['connected-user-select']['#default_value'] =  $defaultValue; 
  }
  return $form;
}

function scmchat_user_messaging_thread_switch_callback($form,&$form_state){
  global $company, $user;
  $currentUser = user_load($user->uid);
  $commands = array();
  $values = $form_state['values'];
  if(!empty($form_state['values']['connected-user-select']) && $form_state['values']['connected-user-select']!='new_mapping'){
    $connectedUsers = array();
    $dfusertquery = db_select('m6connect_scm_settings_user_database', 'n');
    $dfusertquery->join('m6connect_scm_messaging_connect_users', 'uc', 'n.id = uc.user_uid'); 
    $dfusertquery->fields('n');
    $dfusertquery->fields('uc');
    $dfusertquery->condition('n.companyID', $company->nid, '=');
    $dfusertquery->condition('n.userID', $user->uid, '=');
    $dfusertquery->condition('uc.service', 'scm', '=');
    $dfusertquery->condition('uc.mapping_id', $form_state['values']['connected-user-select'], '=');
    $dataObj = $dfusertquery->execute()->fetchObject();
    $rendermsg  = _scmchat_user_messageing_threads($dataObj);
    $commands[] = ajax_command_css('.new-group-action-container .m6message_group_add_cancel', array('display'=>'inline-block'));
    if(!array_key_exists($user->uid,$dataObj->all_names)){
      $commands[] = ajax_command_invoke('div.form-textarea-emoji', 'show' ,array());
    } else{
      $commands[] = ajax_command_invoke('div.form-textarea-emoji', 'show' ,array());  
    }
    $commands[] = ajax_command_data('div.user-connected-user.m6message-full-overlay','mapping',$dataObj->mapping_id);
    $commands[] = ajax_command_invoke('.messaging-mapping-mapping','val', array($dataObj->mapping_id));
    $commands[] = ajax_command_html('#messenger-header-user-info',_scmchat_m6messenger_header_markup($dataObj));
    $commands[] = ajax_command_html('.user-message-container .edit-message-container',$rendermsg);
    $commands[] = ajax_command_invoke('.add-new-member-users','val', array(''));
    $commands[] = ajax_command_html('.add-new-member-markup','');
    //$commands[] = ajax_command_html('.m6message-member-markup',implode(', ',$dataObj->all_names));
    $commands[] = array('command'=>'SwitchMessagingCallback');
    $commands[] = ajax_command_invoke('div.m6message-main-container','removeClass',array('opacity02'));
  }
  $commands[] = ajax_command_invoke('div.user-connected-user.m6message-full-overlay','removeClass',array('opacity02'));
  return array('#type' => 'ajax', '#commands' => $commands);  
}

function scmchat_user_messaging_thread_form($form,&$form_state,$dataObj){
  global $user;
  $form['#attributes'] = array('class'=>array('scmchat_user_messaging_thread_form')); //dropzone
  $form['#attached']['js'][] = array(
    'data' => 'jQuery(document).ready(function(e) { 
                 // setTimeout(refreshMessageContent, 10000);
           var container = jQuery("body").find("#scm-chatuser-messaging-thread-form-container .edit-message-container .message-box-main-container"); 
                 if(container.length){
                   container.animate({scrollTop: container[0].scrollHeight}, "slow");  
                 }
               });',
    'type' => 'inline',
  );
  $form['#attached']['css'][] = array(
    'data' => 'div.message-post-message img.emojioneemoji{ width:50px; }
           .msg-connected-user-info.new_mapping{ display:none; }
               .msg-connected-user-info.new_mapping.user-active{ display:block; }',
    'type' => 'inline',
  ) ;
  $form['scmchat-header']= array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('message-user-heading','clearfix')),
    '#prefix' => '<div id="messenger-container-message-header" class="messenger-header-container-req">',
    '#suffix' => '</div>',
  );
  $form['scmchat-header']['scmchat-header-markup'] = array(
    '#markup' => _scmchat_m6messenger_header_markup($dataObj),
    '#prefix' => '<div id="messenger-header-user-info" class="messenger-header-user-info">',
    '#suffix' => '</div>',
  );
  $form['scmchat-header']['forword_container'] = array(
    '#type' => 'actions',
    '#attributes' => array('class'=>array('message-forword-container-section','clearfix'),'style'=>'margin-top:10px;display:none;'),
  );
  $form['scmchat-header']['forword_container']['forword_save']= array(
    '#type' => 'markup',
    '#markup' => '<div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-left">'.l('<input type="button" class="form-submit" value="Cancel" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-forword-cancel-link')))).'</div>
          <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-center">'.l('<input type="button" class="form-submit" value="0 Selected" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-forword-selected-link')))).'</div>
          <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-right">'.l('<input type="button" class="form-submit" value="Forward" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-forword-next-link')))).'</div>',
    '#prefix' => '<div class="row margin-5">',
    '#suffix' => '</div>',
  );
  $form['scmchat-header']['delete_container'] = array(
    '#type' => 'actions',
    '#attributes' => array('class'=>array('message-delete-container-section','clearfix'),'style'=>'margin-top:10px;display:none;'),
  );
  $form['scmchat-header']['delete_container']['delete_save']= array(
    '#type' => 'markup',
    '#markup' => '<div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-left">'.l('<input type="button" class="form-submit" value="Cancel" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-delete-cancel-link')))).'</div>
          <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-center">'.l('<input type="button" class="form-submit" value="0 Selected" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-deleted-selected-link')))).'</div>
          <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-right">'.l('<input type="button" class="form-submit" value="Delete Selected" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-delete-next-link')))).'</div>',
    '#prefix' => '<div class="row margin-5">',
    '#suffix' => '</div>',
  );
  $form['scmchat-main'] = array(
    '#type' => 'container',
    '#attributes' =>  array('class' => array('scmchat-main-container')),
  );
  $form['scmchat-main']['message-container'] =  array(
    '#type' => 'container',
    '#attributes' =>  array('class' => array('edit-message-container')),
    '#prefix' => '<div class="user-message-container user-message-container-req">',
    '#suffix' => '</div>',
  );  
  $form['scmchat-main']['message-container']['message-list'] =  array(
    '#markup' => _scmchat_user_messageing_threads($dataObj),
  );
  $form['scmchat-main']['mapping-id'] = array(
    '#type' => 'hidden',
    '#default_value' => $dataObj->mapping_id,
    '#attributes' => array('class'=>array('messaging-mapping-mapping')),
  );

  $empjitextareaStyle = (isset($dataObj->mapping_id))?'block':'none' ; 
  $form['scmchat-main']['message-box']= array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#attributes' => array('class'=> array('text-message-smilly')),
    '#attached'=> array(
      'js' =>  array(
        array(
          'data'=>'jQuery(document).ready(function() {
                     jQuery(".text-message-smilly").emojioneArea({
                     container: ".message-abc-cont",
                   hideSource: true,
                   useSprite: false,
                   saveEmojisAs: "image",
                   imageType: "png",
                   shortnames: false,
                   filtersPosition: "bottom",
                     });
           });',
          'type' =>'inline'
        ),
      ),
    ),
    //'#prefix' => '<div class="margin-bottom-10 form-textarea-emoji">',
    '#prefix' => '<div class="margin-0 form-textarea-emoji" style="display:'.$empjitextareaStyle.';pointer-events: none;opacity: .5;">',
    '#suffix' => '<div class="message-abc-cont"></div></div>',
  );
  $form['scmchat-main']['attachment-section']= array(
    '#type' => 'container',
    '#attributes' => array('style'=>'display:none;'),
    '#prefix' => '<div id="attachment-fid-section">',
    '#suffix' => '</div>',
  );
  $form['scmchat-main']['attachment-section']['attachment-fid'] = array(
    '#type' => 'file',
    '#name' => 'files[]',
    '#attributes' => array('class'=> array('emoji-file-attachment')),
    '#title' => t('Choose a file'),
    '#title_display' => 'invisible',
    '#size' => 22, 
  );
  $form['scmchat-main']['attachment-section']['upload-attachment'] = array(
    '#type' => 'submit',   
    '#value' => 'Upload Attachment',
    '#attributes' => array('class' => array('scmchat_attachment_send')),
    '#submit' => array('new_thread_attachment_submit_handler'),
    '#limit_validation_errors' => array(array('attachment-fid'),array('mapping-id')),
    '#ajax' => array(
      'callback' => 'new_thread_attachment_callback',
      'effect' => 'fade',
    ),
  );
  $form['scmchat-main']['submit'] = array(
    '#type' => 'submit',   
    '#value' => 'Send',
    '#attributes' => array('class' => array('scmchat_message_send'),'style'=>'display:none;'),
    '#submit' => array('scmchat_new_thread_message_submit_handler'),
    '#limit_validation_errors' => array(array('message-box'),array('mapping-id')),
    '#ajax' => array(
      'callback' => 'scmchat_new_thread_message_callback',
      'effect' => 'fade',
      'progress' => array('type' => 'none'),
    ),
  );
  return $form;
}

/**
* chatting user search in new recipients
**/
function get_scm_chatting_user_detail_ajax(){
  $users = array();
  $term = (isset($_REQUEST['term']))?trim($_REQUEST['term']):'';
  $mappingID = (isset($_REQUEST['mapping_id']))?trim($_REQUEST['mapping_id']):'';
  if(!empty($mappingID) && !empty($term)){    
    $notShowUserQuery = db_select('users_roles','urd');
    $notShowUserQuery->fields('urd',array('uid'));
    $notShowUserQuery->condition('urd.rid',3,  '=');      
    $query =  db_select('users',  'u');
    $query->join('realname','r','r.uid=u.uid');
    $query->leftjoin('field_data_field_user_profile_photo', 'ufpm', 'ufpm.entity_id=u.uid' );
    $query->leftjoin('file_managed', 'fmum', 'fmum.fid=ufpm.field_user_profile_photo_fid');
    $query->leftjoin('field_data_field_job_titles','jobm','jobm.entity_id=u.uid AND jobm.bundle=:JobBundle',array(':JobBundle'=> 'user'));
    $query->leftjoin('taxonomy_term_data','jtermm','jtermm.tid=jobm.field_job_titles_target_id');
    $query->fields('u', array('uid'));
    $query->fields('r', array('realname'));
    $query->fields('fmum', array('uri'));
    $query->fields('jtermm', array('name'));
    $query->condition('r.realname','%'.db_like($term).'%',  'LIKE');
    //$query->condition('u.uid',$notShowUserQuery,'NOT IN');
    $query->condition('u.status',1);
    $query->orderBy('r.realname',  'ASC');
    $results = $query->execute()->fetchAll();
    if(!empty($results)){
      $jobTitle = !empty($udetail->name)?$udetail->name:'';
      foreach($results as $index => $udetail){
        $users[] = array(
          'label'=> ucwords($udetail->realname), 
          'value'=> $udetail->uid, 
          'image'=> (!empty($udetail->uri))?theme_image_style(array('style_name'=>'pic_40x40','path'=>$udetail->uri,'attributes'=>array('class'=>array('img-circle')))):theme('image', array('path' => 'sites/default/files/images_13_0.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:25px;height:25px;'))), 
          'job_title' => $jobTitle,
        );  
      }
    }
  }
  drupal_json_output($users);
  drupal_exit();
}



function scmchat_new_thread_message_submit_handler(&$form,&$form_state){
  global $user;
  $form_state['insertMessage'] = '';
  $values = $form_state['values'];
   if(user_is_logged_in()){
    if(_is_user_company_admin()) {

    }
   } else {

   }
  $message  = _messenger_message_filter($values['message-box']);
  if(!empty($message) && !empty($values['mapping-id'])){
    $time = time();
    $insertId = db_insert('m6connect_scm_messaging_connect_message')->fields(array(
      'mapping_id' => $values['mapping-id'],
      'author_uid' => $user->uid,
      'message_text' => $message,
      'attachment' => 0,
      'render_state' =>1,
      'timestamp' => $time,
      'seen_by' => $user->uid,
    ))->execute(); 
    if($insertId){
      $mainClass = 'm6-messaging-message message-submitted clearfix text-right padding-5';
      $messageOutput  ='<div id="m6-messaging-message-'.$insertId.'" class="message-row margin-bottom-10 '.$mainClass.'">';
      $messageOutput .='  <div  class="clearfix">';
      $messageOutput .='    <div  class="message-post-message display-inline-block">'.$message.'</div>';
      $messageOutput .='  </div>';
      $messageOutput .='  <span class="message-post-time text-left clearfix">'.date('h:i A').'</span>';
      $messageOutput .='    <input type="checkbox" name="message_forword[]" class="messenger-message-forword-checkbox" value="'.$insertId.'">';
      $messageOutput .='</div>';
      $dataOne = date('m-d-Y');
      $date = date('m/d/Y');
      $dateDiv ='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10">'.$date.'</div></div>'; 
      $insert = array();
      $insert[] = array(
        'message' => $messageOutput,
        'date_div_class' => '.message-box.message-date-'.$dataOne,
        'data_div' => $dateDiv,
        'action' => 'insert',
      );
      $form_state['insertMessage'] = $insert;
    }
  }
}

function scmchat_new_thread_message_callback(&$form,&$form_state){
  global $user;
  $commands = array();
  if(!empty($form_state['insertMessage'])){
  $commands[] = array('command'=>'M6MessagingRefresh','insert_data'=>$form_state['insertMessage']);  
  $form_state['insertMessage']='';
  }
  $commands[] = ajax_command_html('div.emojionearea.text-message-smilly div.emojionearea-editor','');
  $commands[] = ajax_command_invoke('textarea.text-message-smilly','val',array(''));
  return array('#type' => 'ajax', '#commands' => $commands);  
}

function _scmchat_user_messageing_threads($dataObj){
  global $user;
  $userNewDetail = array();
  $output = '';
  $userNewDetail = array(
    'realname' =>  $dataObj->fristname.' '.$dataObj->lastname,
    'job_title' => 'Supply chain management',
  );
  $subqueryms=db_select('m6connect_scm_messaging_connect_message','qtp');
  $subqueryms->fields('qtp');
  $subqueryms->condition('qtp.author_uid',$user->uid,'=');
  $subqueryms->condition('qtp.deleted_from','-1','=');
  $subqueryms->condition('qtp.mapping_id',$dataObj->mapping_id,'=');
  $messagesObj = $subqueryms->execute()->fetchAll();
  $messageFiltered = array();
  foreach($messagesObj as $delta => $messageData){
    $date_object = new DateObject($messageData->timestamp, new DateTimeZone('UTC'));
    $date_object->setTimezone(new DateTimeZone(drupal_get_user_timezone()));
    $messageData->timestamp_time = date_format_date($date_object, 'custom', 'h:i A');
    $messageFiltered[$messageData->timestamp_date][] = $messageData;
    if($messageData->not_found){
      $seenBy = explode(',',$messageData->seen_by);
      $seenBy[] = $user->uid;
      db_update('m6connect_scm_messaging_connect_message')->fields(array('seen_by'=>implode(',',$seenBy)))->condition('id',$messageData->id)->execute();
    }
  }
 
  $output .= '<div class="message-box-main-container">';
  foreach($messageFiltered as $date => $messages){
    $dataOne = date('m-d-Y',strtotime($date));
    $output .='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10">'.$date.'</div>';  
    foreach($messages as $delta => $message){
      $messageUserPic  = '';
      $messageUserRealname  = '';
      $mainClass = 'm6-messaging-message message-submitted clearfix text-right padding-5';
      if($user->uid != $message->author_uid){
      $mainClass = 'm6-messaging-message message-received clearfix text-left text-left padding-5';
        $messageUserRealname = ucwords($message->realname);
      }
      $message_text = $message->message_text;
      if(empty($message->message_text)){
      if(empty($message->attachment)){
        continue; 
      }
      $message_text = get_m6message_attachment_box($message->attachment,$message->attach_uri,$message->attach_filename,$message->attach_filemime);
      }
      $output .='<div id="m6-messaging-message-'.$message->id.'" class="message-row margin-bottom-10 '.$mainClass.'">';
        $output .='    <div class="clearfix">';
      $output .='      <div class="message-post-user-realname">'.ucwords($messageUserRealname).'</div>';
      $output .='      <div class="message-post-message bidder-feedback-msg-content display-inline-block">'.$message_text.'</div>';
      $output .='    </div>';
      $output .='    <span class="message-post-time text-left clearfix">'.$message->timestamp_time.'</span>';
      $output .='    <input type="checkbox" name="message_forword[]" class="messenger-message-forword-checkbox" value="'.$message->id.'" style="display: none;">';
      if($user->uid == $message->author_uid){
        $output .='<input type="checkbox" name="message_delete[]" class="messenger-message-delete-checkbox" value="'.$message->id.'" style="display: none;">';
      }
        $output .='</div>'; 
    }
    $output .='</div>'; 
  }
  $output .= '</div>';
  return $output;
} 


function _scmchat_m6messenger_header_markup($dataObj){
  global $user;
  $output = '';
  $userNewDetail = array(
    'realname' =>  $dataObj->fristname.' '.$dataObj->lastname,
    'job_title' => 'Requester - '.$dataObj->fristname.' '.$dataObj->lastname,
    //'user_pic' => $dataObj->user_pic,
  );
  $output .= '  <div class="row margin-5">';
  $output .= '    <div class="col-md-12 col-sm-12 col-xs-12 padding-5">';
  $output .= '      <div class="message-user-heading-user-info display-inline-block pull-left">';
  //$output .= '        <div class="message-user-heading-user-name">'.$userNewDetail['realname'].'</div>';
  $output .= '        <div class="message-user-heading-user-job">'.$userNewDetail['job_title'].'</div>';
  $output .= '      </div>';
  $output .= '    <div class="chatting-icon pull-right">
                <a href="javascript:void(0);" class="chatting-volume-up">
                    <i class="fa fa-volume-up" aria-hidden="true"></i>
                      </a>  
                <a href="javascript:void(0);" class="chatting-font-bold">
                    <i class="capital-fonts fa fa-font" aria-hidden="true"></i>
                </a>        
            <a href="javascript:void(0);" class="chatting-envelope">
              <i class="fa fa-envelope" aria-hidden="true"></i>
            </a>
            
      </div>';
  $output .= '    </div>';  
  $output .= '  </div>';
  return $output;
}
function scmchat_insert_message_ajax_callback(){
  global $user,$company;
  $values = array();
  $insert = array();
  parse_str($_REQUEST['formDataValues'], $values);
  $message  = _messenger_message_filter($values['message-box']);
  if(!empty($message) && !empty($values['mapping-id'])){
    $time = time();
    $insertId = db_insert('m6connect_scm_messaging_connect_message')->fields(array(
    'mapping_id' => $values['mapping-id'],
    'author_uid' => $user->uid,
    'message_text' => $message,
    'attachment' => 0,
    'render_state' =>1,
    'timestamp' => $time,
    'seen_by' => $user->uid,
  ))->execute(); 
  
  //m6id message insert start 
  $query = db_select('m6connect_scm_messaging_connect_users' ,'mmc');
  $query->fields('mmc',array('user_uid'));
  $query->condition('mmc.mapping_id',$values['mapping-id'],'=');
  $query->condition('mmc.user_uid',$user->uid,'<>');
  $mapping_gid = $query->execute()->fetchColumn(0); 
  $user_type = 'company_user';
    $onboardingManagerUids = _get_company_users_by_og_roles($company->nid,'M6ID Manager');
  if(in_array($user->uid,$onboardingManagerUids)){
    $user_type = 'ob_manager';    
  } 
  $approval_message= array(
    'request_from' => $user->uid,
    'request_to' => $mapping_gid,
    'message' => strip_tags($message, '<>'), 
    'company_nid' => $company->nid,
    'user_type' => $user_type,
    'message_prefix' => NULL,
    'timestamp' => time(),
  );  
    $m6id = db_insert('m6connect_onboarding_inter_company_message')->fields($approval_message)->execute(); 
  //m6id message insert end 
  if($insertId){
    $mainClass = 'm6-messaging-message message-submitted clearfix text-right padding-5';
    $messageOutput  ='<div id="m6-messaging-message-'.$insertId.'" class="message-row margin-bottom-10 '.$mainClass.'">';
      $messageOutput .='  <div  class="clearfix">';
    $messageOutput .='    <div  class="message-post-message bidder-feedback-msg-content display-inline-block">'.$message.'</div>';
    $messageOutput .='  </div>';
    $messageOutput .='  <span class="message-post-time text-left clearfix">'.date('h:i A').'</span>';
    $messageOutput .='    <input type="checkbox" name="message_forword[]" class="messenger-message-forword-checkbox" value="'.$insertId.'">';
    $messageOutput .='    <input type="checkbox" name="message_delete[]" class="messenger-message-delete-checkbox" value="'.$insertId.'">';
      $messageOutput .='</div>';
    $dataOne = date('m-d-Y');
    $date = date('m/d/Y');
    $dateDiv ='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10">'.$date.'</div></div>'; 
    $insert = array();
    $insert[] = array(
      'message' => $messageOutput,
      'date_div_class' => '.message-box.message-date-'.$dataOne,
      'data_div' => $dateDiv,
        'action' => 'insert',
    );
    db_update('m6connect_scm_messaging_connect')->fields(array('updated'=>time()))->condition('mapping_id',$values['mapping-id'])->execute();
  }
  }
  drupal_json_output(array('callback'=>'M6MessagingRefresh','insert'=>$insert,'values'=>$values));
  drupal_exit();
}
function scmchat_connect_callback($connectWithUser){
  global $user;
  $db_and1 = db_and()->condition('mmc.created_by',$user->uid)->condition('mmc.mapping_gid',$connectWithUser->uid);
  $db_and2 = db_and()->condition('mmc.mapping_gid',$user->uid)->condition('mmc.created_by',$connectWithUser->uid);
  $db_or = db_or()->condition($db_and1)->condition($db_and2);
  $query = db_select('m6connect_scm_messaging_connect','mmc');
  $query->fields('mmc',array('mapping_id'));
  $query->condition('mmc.mapping_group','user');
  $query->condition($db_or);
  $mappingId = $query->execute()->fetchField();
  //drup_msg($query->__toString());
  if(!$mappingId){
  $mappingId = md5($user->uid.'-'.$connectWithUser->uid.'-'.time());
  db_insert('m6connect_scm_messaging_connect')->fields(array(
      'mapping_id' => $mappingId,
    'created_by' => $user->uid,
    'mapping_group' => 'user',
    'mapping_gid' => $connectWithUser->uid,
    'timestamp' => time(),
    'updated' => time(),
  ))->execute();
  $currentTime = time();
  db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$mappingId,'user_uid'=>$user->uid))
     ->fields(array('mapping_id'=>$mappingId,'user_uid'=>$user->uid,'mapping_type'=>'user','status'=>1,'join_timestamp'=>$currentTime))->execute();
    db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$mappingId,'user_uid'=>$connectWithUser->uid))
     ->fields(array('mapping_id'=>$mappingId,'user_uid'=>$connectWithUser->uid,'mapping_type'=>'user','status'=>1,'join_timestamp'=>$currentTime))->execute();    
  }
  //return $mappingId;
  //drupal_goto('user-messaging',array('query' => array('thread' => $mappingId)));
  db_update('m6connect_scm_messaging_connect')->fields(array('updated'=>time()))->condition('mapping_id',$mappingId)->execute();
  drupal_goto('user-messaging');
}
function chatting_taskbar_container($chattingContainer){
  $output = '
    <div class="chatting-header" style="background: #fff;padding: 5px 0 25px 0;">
      <div class="chatting-icon pull-right">
        <a href="javascript:void(0);" class="chatting-volume-up">
          <i class="fa fa-volume-up" aria-hidden="true"></i>
        </a>  
        <a href="javascript:void(0);" class="chatting-font-bold">
          <i class="capital-fonts fa fa-font" aria-hidden="true"></i>
        </a>        
        <a href="javascript:void(0);" class="chatting-envelope">
          <i class="fa fa-envelope" aria-hidden="true"></i>
        </a>
        <a href="javascript:void(0);" class="chatting-minus">
          <i class="fa fa-minus-circle" aria-hidden="true"></i>
        </a>
        <a href="javascript:void(0);" class="chatting-remove">
          <i class="fa fa-times-circle" aria-hidden="true"></i>
        </a>
      </div>
    </div>
  ';
  $output .= drupal_render(scm_chatting_container());//'<div id="user-messaging-thread-form-container">'.$chattingContainer.'</div>';
  return $output;
}

/*****
Common Functions
*****/
function Scm_current_user_by_company(){
  global $user,$company;
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

function get_single_userDBbyidcsm($userid){
  $getquery = db_select('m6connect_scm_settings_user_database', 'n');
  $getquery->fields('n');
  $getquery->condition('n.id', $userid, '=');
  $getresult = $getquery->execute()->fetchObject();
  return $getresult;
}