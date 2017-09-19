<?php
function scm_my_project_content() {
  global $company;    
  $elements = array();
  $elements['scm-my-project-form']= array(
    '#markup' => drupal_render(drupal_get_form('scm_projects_scp_form')),
    '#prefix' => '<div class="clearfix main-scm-common-form">',
    '#suffix' => '</div>',
  );
  $elements['scm-my-project-listing'] = array(      
    '#markup' => get_scm_projects_scp_table_data(),
    '#prefix' => '<div class="clearfix"><div class="scm-my-project-listing" id="scm-my-project-table">',
    '#suffix' => '</div></div>',
  );
  return $elements; 
}

function get_scm_projects_scp_table_data(){
  global $company;
  $rows = array();
  $header = array(
    array('data'=>'Project Number','class'=>array('text-center')),
    array('data'=>'Project Title','class'=>array('text-center')),
    array('data'=>'Category | Subcategory','class'=>array('text-center','col-md-2')),
    array('data'=>'Project Type','class'=>array('text-center')),
    array('data'=>'Project Manager','class'=>array('text-center')),
    array('data'=>'Project Description','class'=>array('text-center','col-md-3')),
    array('data'=>'Entity','class'=>array('text-center')), 
    //array('data'=>'Location','class'=>array('text-center')), 
    
    //array('data'=>'Cost Center/Dept','class'=>array('text-center')),
    array('data'=>'Status','class'=>array('text-center')),
    array('data'=>'Action','class'=>array('text-center')),
  );

  $getMyReqNodes = _getting_table_data_call('project_management');  
  $ProjectCategoryList = _get_scm_setting_data('project_category');
  $ProjectTypeList = _get_scm_setting_data('project_type');
  $projectManager = _get_company_users_list_by_og_roles($company->nid, 'SCM Project Manager');
  $ProjectStatusList = _get_scm_setting_data('project_status');
  $ProjectEntityvalue = '';
  $ProjectApprovalStatusList = _get_scm_setting_data('project_approval_status');

  foreach($getMyReqNodes as $values => $ids) {
    $requestNodes = node_load($values); 
    $ProjectEntityvalue = '';
    $ProjectSubCategoryvalue = '';

    if(isset($requestNodes->field_scm_project_entity['und'][0]['value']) && !empty($requestNodes->field_scm_project_entity['und'][0]['value'])){
      $proEntitys = unserialize($requestNodes->field_scm_project_entity['und'][0]['value']);
      $ProjectEntityList =array();$i=0;
      foreach ($proEntitys as $key => $valent) {
        if(!empty(node_load($valent)->title)){
          $ProjectEntityList[$i] = node_load($valent)->title;
          $i++;
        }
      }
      $ProjectEntityvalue = implode(', ', $ProjectEntityList);
    }

    
    $proSubcategorystext = array();
    $proSubcategorys = '';
    $ProjectCategoryvalue = _get_scm_setting_data('project_settings_category',$requestNodes->field_scm_project_category['und'][0]['value'])->title;
    if(isset($requestNodes->field_scm_project_subcategory['und'][0]['value']) && !empty($requestNodes->field_scm_project_subcategory['und'][0]['value'])) {
      $proSubcategorys = explode("|",$requestNodes->field_scm_project_subcategory['und'][0]['value']);
      foreach ($proSubcategorys as $key => $value) {
        $proSubcategorys = explode("-",$value);
        $ProjectSubCategoryvalue = _get_scm_setting_data('project_settings_category',$proSubcategorys[1])->title;
        $proSubcategorystext[$key] = $ProjectSubCategoryvalue;
      }
      $proSubcategorysval = implode(', ', $proSubcategorystext);
    } 


    // Getting main category and sub category data.
    $main_cat_title = $sub_cats_titles = '';
    if (!empty($requestNodes->field_scm_project_category['und'][0]['value'])) {
      $main_cat = scm_category_load($requestNodes->field_scm_project_category['und'][0]['value']);
      $main_cat_title = ucwords($main_cat->title);
    }

    // Getting all sub categories.
    if (!empty($requestNodes->field_scm_project_subcategory['und'][0]['value'])) {
      $sub_cat_ids = explode('|', $requestNodes->field_scm_project_subcategory['und'][0]['value']);
      $sub_cats_title = array();
      foreach ($sub_cat_ids as $sub_key => $sub_cat_id) {
        $sub_cat = scm_category_load($sub_cat_id);
        $sub_cats_title[] = ucwords($sub_cat->title);
      }
      if (!empty($sub_cats_title) && is_array($sub_cats_title)) {
        $first_sub_cat = $sub_cats_title[0];
        $sub_cats_title = implode(', ', $sub_cats_title);
      }
    }

    $sub_cats = $formVal['scm-project-subcategory1'];
    $sub_cat = array_shift($sub_cats);
    $sub_cat_name = '';
    if (!empty($sub_cat)) {
      $sub_cat_load = scm_category_load($sub_cat);
      if (!empty($sub_cat_load->title)) {
        $sub_cat_name = $sub_cat_load->title . ' | ';
      }
    }

    $rows[] = array(
        'data' => array(
        array('data' => $requestNodes->field_project_mgmt_number['und'][0]['value'],'class' => array('text-center')),
        array('data' => l('<span class="commitment-nu-cust">'.ucwords($requestNodes->title).'</span>', 'edit/'.$values.'/details', array('html' => TRUE, 'external' => TRUE,'attributes' => array('class' => 'edit_scm_requests_detail', 'for' => $values))),'class' => array('text-left')),
        array('data' => $main_cat_title . ' | ' . $sub_cats_title, 'class' => array('text-center','col-md-2')),
        array('data' => ucwords($ProjectTypeList[$requestNodes->field_scm_project_project_type['und'][0]['value']]),'class' => array('text-center')),
        array('data' => ucwords($projectManager[$requestNodes->field_project_mgmt_manager['und'][0]['value']]),'class' => array('text-center')),
        array('data' => $requestNodes->body['und'][0]['value'],'class' => array('text-center','col-md-3')),
        array('data' => $ProjectEntityvalue,'class' => array('text-center')),
        //array('data' => ucwords(_get_title_of_node($requestNodes->field_scm_project_locations['und'][0]['value'])),'class' => array('text-left')),
        
        //array('data' => ucwords($requestNodes->field_project_mgmt_cost_center['und'][0]['value']),'class' => array('text-center')),
        array('data' => ucwords($ProjectStatusList[$requestNodes->field_product_status['und'][0]['value']]),'class' => array('text-center')),
        array('data' => _get_action_button($values, 'project_management'),'class' => array('text-center')),
      ),
    );
  }  
  $output = theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Request created yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-table','m6connect-program-request-table', 'm6init-datatable', 'table-hover','text-center')))); 
  return $output;      
}

function scm_projects_scp_form($form, &$form_state) {
  global $user,$company; 
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $form['#attributes']['class'] = array('scm_projects_scp_form');  
  
  // $getReqNodes = _getting_table_data_call('project_management');

  $getReqNodes = _getting_table_subcat_title('project_management');

  if (!isset($form_state['sub_category_fetch_options'])) {
    $form_state['sub_category_fetch_options'] = array();
  }

  if ($form_state['triggering_element']['#name'] == 'scm-project-category') {
    $main_cat_id = $form_state['triggering_element']['#value'];
    if (!empty($main_cat_id)) {
      $sub_categories_all = _get_all_sub_categories_scm_keyed($main_cat_id);
      $form_state['sub_category_fetch_options'] = $sub_categories_all;
    }
    else {
      $form_state['sub_category_fetch_options'] = array();
    }
  }
  
 
  $form['check-triggers'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control','check-triggers')),
    '#ajax' => array(
      'callback'=> 'change_checktrigger_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );

  $form['reset-callback'] = array(
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes' => array('class'=> array('form-control','reset-callback')),
    '#ajax' => array(
      'callback'=> 'change_scm_project_scp_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['prgram-scm-menu-items'] = array(   
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10 margin-top-10">',
    '#suffix' => '</div>',    
  );
  $form['get-scm_projects_scp'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    //'#options' => $project_title,
    '#empty_option' => 'Select Project',
    '#attributes' => array('class'=> array('form-control get-scm_projects_scp')),
    '#ajax' => array(
      'callback'=> 'change_scm_project_scp_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),    
    '#prefix' => '<div class="clearfix"><div class="pull-right next-margin-0">',
    '#suffix' => '</div></div>',
  );

  if (!empty($_SESSION['scm_project_nid']) && is_numeric($_SESSION['scm_project_nid'])) {
    $form['get-scm_projects_scp']['#default_value'] = $_SESSION['scm_project_nid'];
  }

  $form['main-container']= array(
    '#type' => 'container',
  '#attributes' => array('class'=>array('row')), 
    '#prefix' => '<div class="clearfix margin-bottom-20 nbdr"><div id="program_scm_main_container" style="display:none;" class="margin-top-5 project-detail" for="closed">',
    '#suffix' => '</div>', 
    '#process' => array('scm_projects_scp_form_container_process'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
   // '#validate' => array('scm_projects_scp_form_validate'),
  '#submit' => array('scm_projects_scp_form_submit'),
    '#attributes' => array('class'=>array('scm-my-submit-custom-btn')),
    '#prefix' => '<div class="margin-top-10 custom-action-button-div" style="display:none;" for="closed">',
  );
  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
  '#suffix' => '</div></div>',
  );
  return $form;
}

function change_checktrigger_callback($form,&$form_state) {
  $commands = array();
  $myReqNode = node_load($form_state['values']['get-scm_projects_scp']);

  
  if(!empty($myReqNode->field_scm_project_subcategory['und'][0]['value'])) {
        $commands[] = ajax_command_invoke("select.scm-project-subcategory1", 'val',array(explode('|', $myReqNode->field_scm_project_subcategory['und'][0]['value'])));  

        $commands[] = ajax_command_invoke("select.scm-project-subcategory1", 'trigger',array('change'));
      }

      return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_project_scp_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];  

  $currentYear = date('Y');
  $myCounter = variable_get('SCPNumber');
  $makeSr = str_pad($myCounter+1, 6, "0", STR_PAD_LEFT);  
  $projectNumber = 'SCP-'.$makeSr.'-'.$currentYear;

  if($form_state['triggering_element']['#name']=='get-scm_projects_scp') {
    if(!empty($triggeringElement['#value'])) {
      $_SESSION['scm_project_nid'] = $triggeringElement['#value'];
      $myReqNode = node_load($triggeringElement['#value']);   
      $ProjectEntityvalue = '';
      $ProjectSubCategoryvalue = '';
        if(isset($myReqNode->field_scm_project_entity['und'][0]['value']) && !empty($myReqNode->field_scm_project_entity['und'][0]['value'])){
          $proEntitys = unserialize($myReqNode->field_scm_project_entity['und'][0]['value']);
          $ent=0;
          foreach($proEntitys as $valent){
            $ProjectEntityvalue[$ent] = $valent;
            $ent++;
          }
          // $ProjectEntityList = _get_scm_setting_data('project_entity',$proEntitys);
          // $ProjectEntityvalue = array_keys($ProjectEntityList);
        }
        if(isset($myReqNode->field_scm_project_subcategory['und'][0]['value']) && !empty($myReqNode->field_scm_project_subcategory['und'][0]['value'])){
          $proSubcategorys = unserialize($myReqNode->field_scm_project_subcategory['und'][0]['value']);
            if (is_array($proSubcategorys)) {
              $ProjectSubCategoryList = _get_scm_setting_data('project_sub_category',$proSubcategorys);
            } else {
              $ProjectSubCategoryList = _get_scm_setting_data('project_sub_category');
            }
          $ProjectSubCategoryvalue = array_keys($ProjectSubCategoryList);
        }
        $project_department = '';
        if(isset($myReqNode->field_scm_project_department['und'])) {
          $project_department = explode('|',$myReqNode->field_scm_project_department['und'][0]['value']);
        }
      
      $storage_project = array(
        'scm-project-title' => !empty($myReqNode->title)?$myReqNode->title:'',
        'scm-project-project_description' => isset($myReqNode->body['und'])?$myReqNode->body['und'][0]['value']:'',
        'scm-project-number' => isset($myReqNode->field_project_mgmt_number['und'])?$myReqNode->field_project_mgmt_number['und'][0]['value']:'',
        'scm-project-entity' => $ProjectEntityvalue,
        'scm-project-location' => isset($myReqNode->field_scm_project_locations['und'])?$myReqNode->field_scm_project_locations['und'][0]['value']:'',
        'scm-project-category' => isset($myReqNode->field_scm_project_category['und'])?$myReqNode->field_scm_project_category['und'][0]['value']:'',
        //'scm-project-subcategory' => $ProjectSubCategoryvalue,
        'scm-project-subcategoryselect' => isset($myReqNode->field_scm_project_subcategory['und'])?$myReqNode->field_scm_project_subcategory['und'][0]['value']:'',
        'scm-project-cost_center_dept' => isset($myReqNode->field_project_mgmt_cost_center['und'])?$myReqNode->field_project_mgmt_cost_center['und'][0]['value']:'',
        'scm-project-department' => $project_department,
        'scm-project-project_type' => isset($myReqNode->field_scm_project_project_type['und'])?$myReqNode->field_scm_project_project_type['und'][0]['value']:'',
        'scm-project-project_manager' => isset($myReqNode->field_project_mgmt_manager['und'])?$myReqNode->field_project_mgmt_manager['und'][0]['value']:'',
        'scm-project-project_status' => isset($myReqNode->field_product_status['und'])?$myReqNode->field_product_status['und'][0]['value']:'',
        'scm-project-approval_status' => isset($myReqNode->field_scm_project_approvalstatus['und'])?$myReqNode->field_scm_project_approvalstatus['und'][0]['value']:'',
      );
      $commands[] = ajax_command_invoke("select.scm-project-category", 'val',array($storage_project['scm-project-category']));
      $commands[] = ajax_command_invoke("select.scm-project-category", 'attr',array('subcat',$storage_project['scm-project-subcategory']));
      $commands[] = ajax_command_invoke("select.scm-project-category",  'trigger',array('change'));
      $commands[] = ajax_command_invoke("#program_scm_main_container",  'show');
      $commands[] = ajax_command_invoke("#program_scm_main_container",  'attr',array('for','open'));
      $commands[] = ajax_command_invoke(".custom-action-button-div",  'show');
      $commands[] = ajax_command_invoke(".custom-action-button-div",  'attr',array('for','open'));

      $commands[] = ajax_command_invoke("input.scm-project-node-nid", 'val',array($myReqNode->nid));
      $commands[] = ajax_command_invoke("input.scm-project-title", 'val',array($storage_project['scm-project-title']));
      $commands[] = ajax_command_invoke("textarea.scm-project-project_description", 'val',array($storage_project['scm-project-project_description']));
      $commands[] = ajax_command_invoke("input.scm-project-number", 'val',array($storage_project['scm-project-number']));
      $commands[] = ajax_command_invoke("select.scm-project-entity", 'val',array($storage_project['scm-project-entity']));
      $commands[] = ajax_command_invoke("select.scm-project-entity", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("select.check-triggers", 'trigger',array('change'));

      $commands[] = ajax_command_invoke("select.scm-project-location", 'val',array($storage_project['scm-project-location']));      
      $commands[] = ajax_command_invoke("select.scm-project-subcategory1",  'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.scm-project-cost_center_dept", 'val',array($storage_project['scm-project-cost_center_dept']));
      $commands[] = ajax_command_invoke("select.scm-project-department", 'val',array($storage_project['scm-project-department']));
      $commands[] = ajax_command_invoke("select.scm-project-department", 'trigger',array('change'));

      $commands[] = ajax_command_invoke("select.scm-project-project_type", 'val',array($storage_project['scm-project-project_type']));
      $commands[] = ajax_command_invoke("select.scm-project-project_manager", 'val',array($storage_project['scm-project-project_manager']));
      $commands[] = ajax_command_invoke("select.scm-project-project_status", 'val',array($storage_project['scm-project-project_status']));
      $commands[] = ajax_command_invoke("select.scm-project-approval_status", 'val',array($storage_project['scm-project-approval_status']));
      $commands[] = ajax_command_html("#scm-my-project-table", get_scm_projects_scp_table_data());

    } else {
      $commands[] = ajax_command_invoke("input.scm-project-node-nid", 'val',array(''));
      $commands[] = ajax_command_invoke("input.scm-project-title", 'val',array(''));
      $commands[] = ajax_command_invoke("textarea.scm-project-project_description", 'val',array(''));
      $commands[] = ajax_command_invoke("input.scm-project-number", 'val',array($projectNumber));
      $commands[] = ajax_command_invoke("select.scm-project-entity", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-entity", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("select.scm-project-location", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-category", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-subcategory1", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-subcategory1", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.scm-project-cost_center_dept", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-department", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-department", 'trigger',array('change'));      
      $commands[] = ajax_command_invoke("select.scm-project-project_type", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-project_manager", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-project_status", 'val',array(''));
      $commands[] = ajax_command_invoke("select.scm-project-approval_status", 'val',array(''));
      $commands[] = ajax_command_html("#scm-my-project-table", get_scm_projects_scp_table_data());
    } 
  } else {
    $commands[] = ajax_command_invoke("input.scm-project-node-nid", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-project-title", 'val',array(''));
    $commands[] = ajax_command_invoke("textarea.scm-project-project_description", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-project-number", 'val',array($projectNumber));
    $commands[] = ajax_command_invoke("select.scm-project-entity", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-entity", 'trigger',array('change'));
    $commands[] = ajax_command_invoke("select.scm-project-location", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-category", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-subcategory1", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-subcategory1", 'trigger',array('change'));
    $commands[] = ajax_command_invoke("input.scm-project-cost_center_dept", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-department", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-department", 'trigger',array('change'));      
    $commands[] = ajax_command_invoke("select.scm-project-project_type", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-project_manager", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-project_status", 'val',array(''));
    $commands[] = ajax_command_invoke("select.scm-project-approval_status", 'val',array(''));
    $commands[] = ajax_command_html("#scm-my-project-table", get_scm_projects_scp_table_data());
  } 

  return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_projects_scp_form_submit(&$form, &$form_state) { 
  global $user;
  global $company;
  $formVal = $form_state['values'];

  $sub_cats = $formVal['scm-project-subcategory1'];
  $sub_cat = array_shift($sub_cats);
  $sub_cat_name = '';
  if (!empty($sub_cat)) {
    $sub_cat_load = scm_category_load($sub_cat);
    if (!empty($sub_cat_load->title)) {
      $sub_cat_name = $sub_cat_load->title . ' | ';
    }
  }

  $getTitle = $sub_cat_name . $formVal['scm-project-number'];
 
  if(isset($formVal['scm-project-checkalready']) && !empty($formVal['scm-project-checkalready'])){
    if($formVal['scm-project-checkalready']==1){
      form_set_error('title_error', t('Project Title Already Exists'));
      return $form;
    }
  }
  /*
   * Check form submission for new node
    * or an existing one
   */
  $project_category_list = _get_scm_setting_data('project_category');  
  $project_type_list = _get_scm_setting_data('project_type');
  $project_status_list = _get_scm_setting_data('project_status');
  $project_approval_status_list = _get_scm_setting_data('project_approval_status');
  if(isset($formVal['scm-project-node-nid']) && !empty($formVal['scm-project-node-nid'])) {
    $myRequestNode = node_load($formVal['scm-project-node-nid']);
    $myRequestNode->title = $getTitle;
    //$myRequestNode->title = $getTitle;  
    $myRequestNode->body['und'][0]['value'] = $formVal['scm-project-project_description']; 
    //$myRequestNode->field_project_mgmt_number['und'][0]['value'] = $formVal['scm-project-number']; 
    $myRequestNode->field_scm_project_entity['und'][0]['value'] = serialize($formVal['scm-project-entity']);
    $myRequestNode->field_scm_project_locations['und'][0]['value'] = $formVal['scm-project-location'];
    $myRequestNode->field_scm_project_category['und'][0]['value'] = $formVal['scm-project-category'];
    $myRequestNode->field_scm_project_subcategory['und'][0]['value'] = implode("|",$formVal['scm-project-subcategory1']);
    $myRequestNode->field_project_mgmt_cost_center['und'][0]['value'] = $formVal['scm-project-cost_center_dept'];
    $myRequestNode->field_scm_project_department['und'][0]['value'] = implode("|",$formVal['scm-project-department']);
    $myRequestNode->field_scm_project_project_type['und'][0]['value'] = $formVal['scm-project-project_type'];
    $myRequestNode->field_project_mgmt_manager['und'][0]['value'] = $formVal['scm-project-project_manager'];
    $myRequestNode->field_product_status['und'][0]['value'] = $formVal['scm-project-project_status'];
    $myRequestNode->field_scm_project_approvalstatus['und'][0]['value'] = $formVal['scm-project-approval_status'];
    $myRequestNode->field_m6_service_type['und'][0]['value'] = 'scm';  
    node_save($myRequestNode);
    drupal_set_message('My Request - '.$getTitle.' has been updated.');
  } else {
    $crateNode = _node_creation_call('project_management',$getTitle);   

    $currentYear = date('Y');
    $myCounter   = variable_get('SCPNumber');
    $makeSr      = str_pad($myCounter, 6, "0", STR_PAD_LEFT);
    $scrNumber   = 'SCP-' . $makeSr . '-' . $currentYear;
    $scrctNumber = variable_get('SCPNumber');
    variable_set('SCPNumber', $scrctNumber + 1);

    $crateNode->body['und'][0]['value'] = $formVal['scm-project-project_description']; 
    $crateNode->field_project_mgmt_number['und'][0]['value'] = $formVal['scm-project-number']; 
    $crateNode->field_scm_project_entity['und'][0]['value'] = serialize($formVal['scm-project-entity']);
    $crateNode->field_scm_project_locations['und'][0]['value'] = $formVal['scm-project-location'];
    $crateNode->field_scm_project_category['und'][0]['value'] = $formVal['scm-project-category'];
    $crateNode->field_scm_project_subcategory['und'][0]['value'] = implode("|",$formVal['scm-project-subcategory1']);
    $crateNode->field_project_mgmt_cost_center['und'][0]['value'] = $formVal['scm-project-cost_center_dept'];
    $crateNode->field_scm_project_department['und'][0]['value'] = implode("|",$formVal['scm-project-department']);
    $crateNode->field_scm_project_project_type['und'][0]['value'] = $formVal['scm-project-project_type'];
    $crateNode->field_project_mgmt_manager['und'][0]['value'] = $formVal['scm-project-project_manager'];
    $crateNode->field_product_status['und'][0]['value'] = $formVal['scm-project-project_status'];
    $crateNode->field_scm_project_approvalstatus['und'][0]['value'] = $formVal['scm-project-approval_status'];
    $crateNode->field_m6_service_type['und'][0]['value'] = 'scm';  
    node_save($crateNode);
  drupal_set_message('My Request - '.$getTitle.' has beed saved.');
  }
}

function scm_projects_scp_form_container_process($element, &$form_state) {
  global $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $currentYear = date('Y');
  $myCounter = variable_get('SCPNumber');
  $makeSr = str_pad($myCounter+1, 6, "0", STR_PAD_LEFT);  
  $projectNumber = 'SCP-'.$makeSr.'-'.$currentYear;
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','margin-top-10','project-details-full',)),
  );
  $element['main-container']['full-container']['full-container-inner-left'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-left','margin-bottom-10')),
  );  
  $element['main-container']['full-container']['full-container-inner-right'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','project-details-right','margin-bottom-10')),
  );
  $element['areusure'] = array(
        '#type' => 'markup',
        '#markup' => '<div id="dialogss" title="Alert message" style="display: none">
            <div class="ui-dialog-content ui-widget-content">
                <p>
                    <label id="lblMessage1">
                    </label>
                </p>
            </div>
        </div>',
        '#prefix' => '<div class="custom-action-button-div margin-bottom-10" style="display:none">',
        '#suffix' => '</div>',
    );
  $element['scm-project-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-project-node-nid')),  
  );

  $element['main-container']['full-container']['full-container-inner-left']['scm-project-number'] = array(
    '#type' => 'textfield',
    '#title' => 'Project Number',
    '#attributes' => array('class'=> array('form-control scm-project-number')),
    '#prefix' => '<div class="project-details-border scm-common-form-standard-width"><div class="clearfix form-item">',
    '#suffix' => '</div>',
    '#default_value' => isset($defaultValues['scm-project-number'])?$defaultValues['scm-project-number']:$projectNumber,
    '#field_suffix' => '<div class="pull-right project-avail-status"><span class="text-danger"></span><span class="text-success"></span></div>',
    '#disabled' => TRUE,
  );
  /*$element['main-container']['full-container']['full-container-inner-left']['scm-project-title'] = array(
    '#type'=>'textfield',
    '#title'=> 'Project Title',
    '#attributes' => array('class'=> array('form-control scm-project-title')),
    '#default_value' => isset($defaultValues['scm-project-title'])?$defaultValues['scm-project-title']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>', 
    '#field_suffix' => '<div class="pull-right project-avail-status-title"><span class="text-danger"></span><span class="text-success"></span></div>',
    '#required' => TRUE,
  );*/

  $element['main-container']['full-container']['full-container-inner-left']['scm-project-checkalready'] = array(
    '#type'=>'hidden',
    '#attributes' => array('class'=> array('form-control scm-project-checkalready')),
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>', 
  );
  $project_entity_list = _getting_table_data_call('scm_setting_location_entity');
  $element['main-container']['full-container']['full-container-inner-left']['scm-project-entity'] = array(
    '#type' => 'select',
    '#title' => 'Choose Entity',
    '#options' => $project_entity_list,
    '#empty_option' => '- Select Entity Type -',
    '#select2' => array(
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#attributes' => array('class'=> array('form-control scm-project-entity')),
    '#default_value' => isset($defaultValues['scm-project-entity'])?$defaultValues['scm-project-entity']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );

  $categoryData = _get_all_main_categories_scm();
  $categoryData = array_map('ucwords', $categoryData);
  // get sub category data from settings

  
  $element['main-container']['full-container']['full-container-inner-left']['scm-project-category'] = array(
    '#type' => 'select',
    '#title' => 'Choose Category',
    '#options' => $categoryData,
    '#empty_option' => '- Select Category -',
    '#ajax' => array(
        'callback'=> 'change_sc_project_category_callback',
        'wrapper' => 'categoriesrealtionarea',
        'effect' => 'fade',
      ),
    '#attributes' => array('class'=> array('form-control scm-project-category','category-informations-main')),
    '#default_value' => isset($defaultValues['scm-project-category'])?$defaultValues['scm-project-category']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>',
    '#required' => TRUE,
  );

  $project_sub_category_list = _get_scm_setting_data('project_sub_category');
  
  $subcategoryData = $form_state['sub_category_fetch_options'];

  if (!empty($subcategoryData)) {
    $subcategoryData = array_map('ucwords', $subcategoryData);
  }

  $element['main-container']['full-container']['full-container-inner-left']['scm-project-subcategory1'] = array(
    '#type' => 'select',
    '#title' => 'Choose Subcategory',
    '#options' => $subcategoryData,
    '#select2' => array(
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#required' => TRUE,
    '#empty_option' => '- Select Subcategory -',
    '#attributes' => array('class'=> array('form-control','scm-project-subcategory1','category-informations-main-sub1')),
    '#prefix' => '<div id="categoriesrealtionarea"><div class="clearfix form-item">',  
    '#suffix' => '</div></div>',
  );
  /*$element['main-container']['full-container']['full-container-inner-left']['scm-project-cost_center_dept'] = array(
    '#type'=>'textfield',
    '#title'=> 'Cost Center/Dept',
    '#attributes' => array('class'=> array('form-control scm-project-cost_center_dept')),
    '#default_value' => isset($defaultValues['scm-project-cost_center_dept'])?$defaultValues['scm-project-cost_center_dept']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>',
  );*/



  $project_department_list = _get_scm_setting_data('project_department');
  $element['main-container']['full-container']['full-container-inner-left']['scm-project-department'] = array(
    '#type'=>'select',
    '#title'=> 'Department',
    '#options' => $project_department_list,
    '#empty_option' => '- Select Department -',
    '#select2' => array(
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#attributes' => array('class'=> array('form-control scm-project-department')),
    '#default_value' => isset($defaultValues['scm-project-department'])?$defaultValues['scm-project-department']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div></div>', 
  );


 // $project_type_list = _get_scm_setting_data('project_type');
  /*$element['main-container']['full-container']['full-container-inner-right']['scm-project-project_type'] = array(
    '#type' => 'select',
    '#title' => 'Project Type',
    '#options' => $project_type_list,
    '#empty_option' => '- Select Project Type -',
    '#attributes' => array('class'=> array('form-control scm-project-project_type')),
    '#default_value' => isset($defaultValues['scm-project-project_type'])?$defaultValues['scm-project-project_type']:'',
    '#prefix' => '<div class="project-details-border scm-common-form-standard-width"><div class="clearfix form-item">',  
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );*/
  $projectManager = _get_company_users_list_by_og_roles($company->nid, 'SCM Project Manager');
  $element['main-container']['full-container']['full-container-inner-right']['scm-project-project_manager'] = array(
    '#type' => 'select',
    '#title' => 'Project Manager',
    '#options' => array_map('ucwords', $projectManager),
    '#empty_option' => '- Select Project Manager -',
    '#attributes' => array('class'=> array('form-control scm-project-project_manager')),
    '#default_value' => isset($defaultValues['scm-project-project_manager'])?$defaultValues['scm-project-project_manager']:'',
    '#prefix' => '<div class="project-details-border scm-common-form-standard-width"><div class="clearfix form-item">',  
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $project_status_list = _get_scm_setting_data('project_status');
  $element['main-container']['full-container']['full-container-inner-right']['scm-project-project_status'] = array(
    '#type' => 'select',
    '#title' => 'Project Status',
    '#options' => $project_status_list,
    '#empty_option' => '- Select Project Status -',
    '#attributes' => array('class'=> array('form-control scm-project-project_status')),
    '#default_value' => isset($defaultValues['scm-project-project_status'])?$defaultValues['scm-project-project_status']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $project_approval_status_list = _get_scm_setting_data('project_approval_status');
  $element['main-container']['full-container']['full-container-inner-right']['scm-project-approval_status'] = array(
    '#type' => 'select',
    '#title' => 'Approval Status',
    '#options' => $project_approval_status_list,
    '#empty_option' => '- Select Approval Status -',
    '#attributes' => array('class'=> array('form-control scm-project-approval_status')),
    '#default_value' => isset($defaultValues['scm-project-approval_status'])?$defaultValues['scm-project-approval_status']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div></div>',
    '#disabled' => false,
    '#required' => TRUE,
  );

  $element['main-container']['full-container']['full-container-inner-right']['scm-project-project_description'] = array(
    '#type'=>'textarea',
    '#title'=> 'Project Description',
    '#attributes' => array('class'=> array('form-control scm-project-project_description')),
    '#default_value' => isset($defaultValues['scm-project-project_description'])?$defaultValues['scm-project-project_description']:'',
    '#prefix' => '<div class="clearfix form-item">',  
    '#suffix' => '</div>', 
  );
  return $element;
}
function change_sc_project_category_callback($form, &$form_state) {
  return $form['main-container']['main-container']['full-container']['full-container-inner-left']['scm-project-subcategory1'];
}
/*
 * Supply Chain manager - Case Builder's
 * Patient care section started
 */ 
function scm_patient_care_content() {
  global $user,$company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  /*
   *  Getting dynamic label value form setting page
   */  
  $query = db_select('m6connect_scm_casemanager_label_management','cmlm');
  $query->fields('cmlm',array('value'));
  $query->condition('cmlm.nid',$company->nid);
  $caselabel = $query->execute()->fetchColumn(0); 

  $_SESSION['scm_label_object'] = ''; 
  $_SESSION['scm_label_object'] = (isset($caselabel) && !empty($caselabel)?unserialize($caselabel):'');
  /*
   *  Getting the menu's and submenu for 
   *  Case manager
   */
  $elements['scm-patient-care-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_patient_care_change_form')),
    '#prefix' => '<div class="clearfix main-scm-casebuilder-form">',
    '#suffix' => '</div>',
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
  /*
   * Rendring case's and project manger comment
   * Section
   **/
  $elements['scm-casebuilder-outer']= array(
    '#markup' => drupal_render(casemanager_patient_care_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements; 
}
/*
 * Initialization of case and comment renderation
 *
 */
function casemanager_patient_care_outer() {
  global $user, $company;  
  $defaultProjectNid = (isset($_SESSION['scm_project_nid']) && !empty($_SESSION['scm_project_nid'])?$_SESSION['scm_project_nid']:'');
  if(isset($defaultProjectNid) && !empty($defaultProjectNid)){
    $casenid = _get_scmcase_nids_by_referpronid($defaultProjectNid);
    $casecount = count($casenid);
    $caseswidth = $casecount *400 + 10;
    $elements['scm-buy-change-start']= array(
      '#markup' => '<div class="row margin-10 relative case-expand-item margin-top-10" style="width:'.$caseswidth.'px" open-status="">',
    );  
  $caseStsArr = array();
  foreach($casenid as $key=>$nid){
    $caseNodeData = node_load($nid);
    if(empty($caseNodeData->field_case_status['und'][0]['value'])) {
      $caseStsArr[$nid] = 'blank';  
    }
    else {
      $caseStsArr[$nid] = $caseNodeData->field_case_status['und'][0]['value'];
    }
  }
    $casesr = 0;
    $dispaly_none = '';
  $caseStatusCls = '';
    $commentsclass = 'center';
    foreach($casenid as $key=>$nid){
      $casesr++;
    $caseNodeData = node_load($nid);
    if(in_array('active', $caseStsArr)) {
      if($caseNodeData->field_case_status['und'][0]['value'] == 'active') {
      $caseStatusCls = 'case-active';
    }
    else {
      $caseStatusCls = 'blur-cases blur-cases-sp';
    }
    }
    $cStatus = (isset($caseNodeData->field_case_status['und'][0]['value']) && $caseNodeData->field_case_status['und'][0]['value'] == 'active'?'active':'deactive');
    $csDesc = !empty($caseNodeData->field_case_builder_description['und'][0]['value']) ? $caseNodeData->field_case_builder_description['und'][0]['value'] : '<br/>';
    $casedelta = array('sr'=>$casesr,'refernid'=>$nid,'refertitle'=>_get_title_of_node($nid),'caseStatus' => $cStatus, 'caseDesc' => $csDesc);
      $elements['case_section_' . $nid] = array(
        '#type' => 'container',
        '#attributes' => array('class'=> array('changein-document-popup','caseouter','case_'.$casesr, 'case-continer-'.$nid, $caseStatusCls) ,'original-pos'=>'case_'.$casesr,'updated-pos'=>''),
      );
      $elements['case_section_' . $nid]['scm-buy-change-left']= array(
        '#markup' => drupal_render(drupal_get_form('casemanager_patient_care_left_form',$casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
      $dispaly_none = 'dispaly_none';
      $elements['case_section_' . $nid]['scm-casebuilder-right']= array(
        '#markup' => drupal_render(drupal_get_form('casemanager_patient_care_right_form',$casedelta)),
        '#prefix' => '<div class="'.$commentsclass.' col-md-8 padding-10 margin-bottom-10 casebuilder-details-right '.$dispaly_none.'"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    }
  
    $elements['scm-patient-care-change-end']= array(
      '#markup' => '</div>',
    );
  }
  return $elements; 
}

function casemanager_patient_care_change_form($form, &$form_state) {
  $getReqNodes = _getting_table_data_call('project_management');
  
  $form['prgram-scm-menu-items'] = array(
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',    
  );
  $form['scm-casemanager-menu']= array(
    '#markup' => scm_csemanager_sub_menu_links_content(),
    '#prefix' => '<div class="clearfix margin-bottom-10 csemanager-sub-menu">',
    '#suffix' => '</div>',
  );
  $form['get-scm_projects_scp'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#empty_option' => 'Select Project',
    '#default_value' => isset($_SESSION['scm_project_nid'])?array($_SESSION['scm_project_nid']=>$_SESSION['scm_project_nid']):'',
    '#attributes' => array('class'=> array('form-control get-scm_projects_scp')),
    '#ajax' => array(
      'callback'=> 'patient_care_change_scm_project_scp_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix"><div class="pull-right next-margin-0 changein-document-btn">',
    '#suffix' => '</div></div>',
  );
  return $form;
}

function casemanager_patient_care_left_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i;
  $form['left_case_section'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container','clearfix','padding-10 ')),
    '#prefix' => '<div id="casebuilder-left-section" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('casebuilder_left_patient_care_section_process'),
  );
  return $form;
}

function casebuilder_left_patient_care_section_process($elements, &$form_state) {
  /*
   * Get reference case nid form form state 
   * And assign it to form reference field
   */
  $elements['refercase_nid'] = array(
    '#type' => 'value',
    '#value' => $form_state['case_delta']['refernid'],
  );
  $elements['refercase_title'] = array(
    '#type' => 'value',
    '#value' => $form_state['case_delta']['refertitle'],
  ); 
  $getCaseStatus = $form_state['case_delta']['caseStatus'];
  $getCaseDesc = $form_state['case_delta']['caseDesc'];
  $case = '';
  if(isset($form_state['case_delta']['refernid']) && !empty($form_state['case_delta']['refernid'])){
    $query2 = db_select('field_data_field_case_reference','caser');
    $query2->fields('caser',array('entity_id'));
    $query2->condition('caser.bundle','patient_care');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
    $case = node_load($nodenid);
  }
  $hasecase = (isset($case, $case->nid) && !empty($case->nid)?'case-expand':'notcasefound');
  
  $changeindocument = 'changein-document';
  
  $changeindocumentdata = (isset($case, $case->nid) && !empty($case->nid)?'document-save-'.$case->nid:'document-save-new');

  $notcasefound = (isset($case, $case->nid) && !empty($case->nid)?"":'data-trigger="hover" data-toggle="popover"  data-placement="bottom" data-content="Please Save First"');
  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );
  $casetitle = (strlen($form_state['case_delta']['refertitle']) > 26) ? substr($form_state['case_delta']['refertitle'], 0, 23) . '...' : $form_state['case_delta']['refertitle'];
  $caseStatusBtn = '<input id="case-toogle-check-cust" class="case-status-check" type="checkbox" checked data-toggle="toggle" data-on="Active" data-off="Inactive" data-onstyle="success" data-offstyle="danger" for="'.$form_state['case_delta']['refernid'].'">';
  $elements['case_progress_by_section_title'] = array(
    //'#markup' => '<div class="clearfix margin-bottom-10 case-section-title margin-top-10"><div class="pull-left">Case '.$form_state['case_delta']['sr'].': '.$casetitle.'</div><div class="pull-right toggle-case-status-check">'.$caseStatusBtn.'<i class="fa fa-comments-o ' .$hasecase.'" aria-hidden="true" case-status="close" style="cursor: pointer;" '.$notcasefound.'></i></div><div class="notcasefound dispaly_none">Please save first</div></div>',   
  '#markup' => '<div class="clearfix margin-bottom-10 case-section-title case-section-title-sp margin-top-10"><div class="pull-left fixed-case-title fixed-case-title">Case '.$form_state['case_delta']['sr'].': '.$casetitle.'</div><div class="pull-right toggle-case-status-check changein-document-btn">'.$caseStatusBtn.'<i class="fa fa-comments-o ' .$hasecase.'" aria-hidden="true" case-status="close" style="cursor: pointer;" '.$notcasefound.'></i></div><div class="notcasefound dispaly_none">please save first</div></div>',   
  );
  $caseDefaultVal = isset($getCaseStatus)?'active':'deactive';  
  $style_options = array('active' => 'active', 'deactive' => 'deactive');
  $elements['case_options'] = array(
    '#type' => 'radios',
    '#options' => $style_options,
    '#ajax' => array(
      'callback' => '_updating_case_status_callback',
      'wrapper' => 'alert-container-section',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
     ),
   '#default_value' => $form_state['case_delta']['caseStatus'],
     '#attributes' => array('class'=> array('case-category-radio','form-inline','custom-form-inline-radio')),
     '#prefix' => '<div class="clearfix margin-bottom-10 spread-options-custom case-radio-'.$form_state['case_delta']['refernid'].'" style="display:none;">', 
     '#suffix' => '</div>',
  );
  /*
   * First textarea for attention
   */
   $casetextareaedit = '<i class="pull-right fa fa-pencil casetextareaedit" aria-hidden="true" style="cursor: pointer;"></i>';
  // $textarea1 = (isset($case, $case->field_patient_care_description['und'],$case->field_patient_care_description['und'][0]['value']) && !empty($case->field_patient_care_description['und'][0]['value'])?'dispaly_none':'');
  
  // $textareavalue1 = (isset($case, $case->field_patient_care_description['und'],$case->field_patient_care_description['und'][0]['value']) && !empty($case->field_patient_care_description['und'][0]['value'])?$case->field_patient_care_description['und'][0]['value'].$casetextareaedit:'');
  // $elements['patient_care_subtitle'] = array(        
  //   '#type' => 'textarea',
  //   '#attributes'=> array('placeholder'=> 'Enter case description here.'),
  //   '#default_value' => (isset($case, $case->field_patient_care_description['und'],$case->field_patient_care_description['und'][0]['value']) && !empty($case->field_patient_care_description['und'][0]['value'])?$case->field_patient_care_description['und'][0]['value']:''),    
  //   '#prefix' => '<div class="clearfix margin-bottom-10">
  //                   <div class="clearfix margin-bottom-10 section-title margin-10 bluebgtitle">
  //                     Something <strong>needs your attention</strong>
  //                   </div>
  //                   <div class="hastextareavalue">
  //                     '.$textareavalue1.'
  //                   </div>
  //                   <div class="hastextarea '.$textarea1.'">',
  //   '#suffix' =>    '</div>
  //                 </div>',
  // );  
  $textarea_label = !empty($_SESSION['scm_label_object']['case_builder']['description']) ? $_SESSION['scm_label_object']['case_builder']['description'] : t('Description');
  $elements['case_description'] = array(
    '#type'   => 'markup',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="clearfix margin-bottom-10 section-title margin-10 dashboard-block-heading"> Description</div><div class="hastextareavalue">',
    '#markup' => $getCaseDesc,
    '#suffix' => '</div></div>',
  );
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['patient_satisfaction'] = array(
    '#type' => 'radios',
    '#title' => t('Does it impact Patient Satisfaction?'),
    '#default_value' => (isset($case, $case->field_patient_satisfaction['und'],$case->field_patient_satisfaction['und'][0]['value']) && !empty($case->field_patient_satisfaction['und'][0]['value'])?$case->field_patient_satisfaction['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),        
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="clearfix '.$changeindocument.'">
                    <div class="conditionstatebase1">
                      <div class="clearfix">
                        <div class="pull-left tristate-icon">
                          <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                        </div>
                        <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>        '</div>
                      </div>',
  );
  /*
   * Fields comes when satisfaction gree (true)
   */
  $elements['infection_implications'] = array(
    '#type' => 'radios',
    '#title' => 'Are there Infection Implications?',
    '#default_value' => (isset($case, $case->field_infection_implications['und'],$case->field_infection_implications['und'][0]['value']) && !empty($case->field_infection_implications['und'][0]['value'])?$case->field_infection_implications['und'][0]['value']:0),
    '#options' => $active,        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onered">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>      '</div>
                    </div>',
  );
 $elements['infection_implications_prevention_review'] = array(
    '#type' => 'radios',
    '#title' => 'Did Infection Prevention review?',
    '#default_value' => (isset($case, $case->field_infection_prevention['und'],$case->field_infection_prevention['und'][0]['value']) && !empty($case->field_infection_prevention['und'][0]['value'])?$case->field_infection_prevention['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onered-twogreen">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>      '</div>
                    </div>
                  ',
  );
  $textarea2 = (isset($case, $case->field_prevention_review_descript['und'],$case->field_prevention_review_descript['und'][0]['value']) && !empty($case->field_prevention_review_descript['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue2 = (isset($case, $case->field_prevention_review_descript['und'],$case->field_prevention_review_descript['und'][0]['value']) && !empty($case->field_prevention_review_descript['und'][0]['value'])?$case->field_prevention_review_descript['und'][0]['value'].$casetextareaedit:'');
  $elements['review_explain'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_prevention_review_descript['und'],$case->field_prevention_review_descript['und'][0]['value']) && !empty($case->field_prevention_review_descript['und'][0]['value'])?$case->field_prevention_review_descript['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Explain the Approval or why Endorsement is not needed.'),
    '#prefix' => '<div class="conditionstate-onered-twogreen-dubble">
                    <div class="clearfix">
                      <div class="tristate-toggle-button pull-right icon-shiftup-outer padding-5">
                        <div class="hastextareavalue">'.$textareavalue2.'</div>
                        <div class="hastextarea '.$textarea2.'">',
    '#suffix' =>        '</div>
                      </div>
                    </div>
                  </div>
            ',
  );
  $infection_prevention_doc = 'infection_prevention_doc'; 
  $elements['infection_prevention_doc']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $infection_prevention_doc . '][]',
    '#upload_location' => 'public://',
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$infection_prevention_doc . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$infection_prevention_doc . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="conditionstate-onered-twogreen-dubble-twogreen"><div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );

  $previousfilelist = '';
  $filelist = array();

  if (!empty($case->field_infection_prevention_doc['und'])) {
    foreach ($case->field_infection_prevention_doc['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_infection_prevention_doc/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['infection_prevention_doc_document_link']= array(
    '#markup' => '<label>Attach Documentation of Infection Prevention Approval</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $infection_prevention_doc . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $infection_prevention_doc . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '<div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign. '
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>     '</div>
                    </div>
                  </div>
                </div>
              </div>
                ',
  );

  /*
   * Fields comes when satisfaction red (FALSE)
   */
  $elements['outcomes_quantified'] = array(
    '#type' => 'radios',
    '#title' => 'Can Outcomes be quantified?',
    '#default_value' => (isset($case, $case->field_patient_care_outcomes['und'],$case->field_patient_care_outcomes['und'][0]['value']) && !empty($case->field_patient_care_outcomes['und'][0]['value'])?$case->field_patient_care_outcomes['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen section-top-parent">
                    <div class="conditionstate-greentwo">
                      <div class="clearfix">
                        <div class="pull-left tristate-icon">
                          <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                        </div>
                        <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>      ' </div>
                      </div>',
  ); 
  $advisor_document_patient = 'advisor_document_patient'; 
  $elements['advisor_document_patient']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $advisor_document_patient . '][]',
    '#upload_location' => 'public://',
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$advisor_document_patient . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$advisor_document_patient . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
 
  $previousfilelist = '';
  if(isset($case,$case->field_quality_advisor['und']) && !empty($case->field_quality_advisor['und'])){
    $filelist = array();
    foreach ($case->field_quality_advisor['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_quality_advisor/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['approval_document_link']= array(
    '#markup' => '<label>Attach Quality Outcome Documentation</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $advisor_document_patient . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $advisor_document_patient . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '<div class="conditionstate-greenthree">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign. '
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>     '</div>
                    </div>
                  </div>
                </div>
                  ',
  );  
  $elements['outcomes_quantified_infection_implications'] = array(
    '#type' => 'radios',
    '#title' => 'Are there Infection Implications?',
    '#default_value' => (isset($case, $case->field_infection_implications_2['und'],$case->field_infection_implications_2['und'][0]['value']) && !empty($case->field_infection_implications_2['und'][0]['value'])?$case->field_infection_implications_2['und'][0]['value']:0),
    '#options' => $active,        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen-dubble">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>      '</div>
                    </div>

                 ',
  );
  $elements['outcomes_quantified_infection_implications_prevention_review'] = array(
    '#type' => 'radios',
    '#title' => 'Did Infection Prevention review?',
    '#default_value' => (isset($case, $case->field_infection_prevention_2['und'],$case->field_infection_prevention_2['und'][0]['value']) && !empty($case->field_infection_prevention_2['und'][0]['value'])?$case->field_infection_prevention_2['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen-dubble-twogreen">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>      '</div>
                    </div>
                  ',
  );
  $textarea3 = (isset($case, $case->field_implications_review_descri['und'],$case->field_implications_review_descri['und'][0]['value']) && !empty($case->field_implications_review_descri['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue3 = (isset($case, $case->field_implications_review_descri['und'],$case->field_implications_review_descri['und'][0]['value']) && !empty($case->field_implications_review_descri['und'][0]['value'])?$case->field_implications_review_descri['und'][0]['value'].$casetextareaedit:'');

  $elements['outcomes_quantified_infection_implications_prevention_review_explain'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_implications_review_descri['und'],$case->field_implications_review_descri['und'][0]['value']) && !empty($case->field_implications_review_descri['und'][0]['value'])?$case->field_implications_review_descri['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Explain the Approval or why Endorsement is not needed.'),
    // conditionstate-onegreen-dubble-twogreen-green
    '#prefix' => '<div class="conditionstate-onegreen-dubble-twogreen-dubble">
                    <div class="clearfix">
                      <div class="tristate-toggle-button pull-right icon-shiftup-outer padding-5">
                        <div class="hastextareavalue">'.$textareavalue3.'</div>
                        <div class="hastextarea '.$textarea3.'">',
    '#suffix' =>        '</div>
                      </div>
                    </div>',
  );

  $infection_prevention_doc_2 = 'infection_prevention_doc_2'; 
  $elements['infection_prevention_doc_2']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $infection_prevention_doc_2 . '][]',
    '#upload_location' => 'public://',
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$infection_prevention_doc_2 . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$infection_prevention_doc_2 . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="conditionstate-onegreen-dubble-twogreen-onegreen"><div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );

  $previousfilelist = '';
  $filelist = array();

  if (!empty($case->field_infection_prevention_doc_2['und'])) {
    foreach ($case->field_infection_prevention_doc_2['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_infection_prevention_doc_2/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['infection_prevention_doc_2_document_link']= array(
    '#markup' => '<label>Attach Documentation of Infection Prevention Approval</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $infection_prevention_doc_2 . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $infection_prevention_doc_2 . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '<div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign. '
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>     '</div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>',
  );
  /*
   * Established standard section  goes here
   */
  
  /*$elements['left_section_delete'] = array(
    '#type' => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/'.$case->nid), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
    '#prefix' => '<div class="clearfix margin-bottom-10 margin-top-10">',   
  );
  $elements['left_section_cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit">',    
  );
  $elements['left_section_save_and_addnew_case'] = array(
    '#type' => 'button',
    '#title' => 'left_section',
    '#value' => t('Save'),
    '#ajax' => array(
        'callback' => 'patient_care_save_and_addnew_case_submit_callback',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    '#attributes' => array('class'=>array('save-addnew-case-button')),
    //'#prefix' => '<div class="clearfix" style="display:none">',
    '#suffix' => '</div>',
   );
*/
  // Delete save and next section.
  $elements['left_section_delete'] = array(
    '#type'   => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/'.$form_state['case_delta']['refernid']), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
    '#prefix' => '<div class="clearfix margin-bottom-10 margin-top-10 case-button-outer">',
  );
  $elements['left_section_cancel'] = array(
    '#type'   => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit">',
  );
 
  $elements['left_section_save_and_next'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#name'       => 'save_next_submit',
    '#value'      => t('Save and Next'),
    '#ajax'       => array(
        'callback' => 'patient_care_case_submit_callback',
        'method'   => 'replace',
        'effect'   => 'fade',
      ),
    '#attributes' => array('class'=>array('save-next-case-button')),
    '#prefix'     => '<div class="clearfix" style="display:none">',
    '#suffix'     => '</div>',
  );
  $elements['left_section_save_and_duplicate_case'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#name'       => 'save_duplicate_submit',
    '#value'      => t('Save and Duplicate Case'),
    '#ajax'       => array(
      'callback' => 'patient_care_case_submit_callback',
      'method'   => 'replace',
      'effect'   => 'fade',
    ),
    '#attributes' => array('class'=>array('save-duplicate-case-button')),
    '#prefix'     => '<div class="clearfix" style="display:none">',
    '#suffix'     => '</div>',
   );
  
  $elements['left_section_save'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#name'       => 'save_submit',
    '#value'      => t('Save'),
    '#ajax'       => array(
        'callback' => 'patient_care_case_submit_callback',
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type' => 'none'),
      ),
    '#attributes' => array('documentsave'=>$changeindocumentdata,'class'=>array('btn', 'btn-primary','margin-0',$changeindocumentdata)),
    '#prefix'     => '<div class="btn-group">',
    '#suffix'     => '<button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <span class="caret"></span>
                      <span class="sr-only">Toggle Dropdown</span>
                    </button>
                    <ul class="dropdown-menu">
                      <li><a href="javascript:void(0);" class="save-next-case">Save and Next</a></li>
                      <li><a href="javascript:void(0);" class="save-duplicate-case">Save and Duplicate Case</a></li>
                    </ul>
                  </div>
                </div>',
  );
  return $elements;
}

function casemanager_patient_care_left_form_validate($form, &$form_state) {
  /*if($_FILES['files']['name'] != '')  {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
      $file = file_save_upload($i, array( 
        'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
      ));
      if ($file) {    
        if ($file = file_move($file, 'public://')) {
          $form_state['values']['advisor_document_patient'][$i] = $file;
        } 
      }
    }
  }*/
}

function casemanager_patient_care_right_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i;
  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('patient_care_project_manager_comments_process'),
  );
  return $form;
}

function patient_care_project_manager_comments_process($elements, &$form_state) {
  if(isset($form_state['case_delta'],$form_state['case_delta']['refernid']) && !empty($form_state['case_delta']['refernid']))
  global $user,$company;
  $defaultProjectNid = '';
  $defaultProjectNid = $_SESSION['scm_project_nid'];
  $elements['refercase_nid'] = array(
    '#type' => 'value',
    '#value' => $form_state['case_delta']['refernid'],
  );
  $elements['refercase_title'] = array(
    '#type' => 'value',
    '#value' => $form_state['case_delta']['refertitle'],
  ); 
  $case = '';
  if(isset($form_state['case_delta']['refernid']) && !empty($form_state['case_delta']['refernid'])){
    $query2 = db_select('field_data_field_case_reference','caser');
    $query2->fields('caser',array('entity_id'));
    $query2->condition('caser.bundle','patient_care');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
  $case = node_load($nodenid);
  }
  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );
  $elements['project_manager_inner_menu'] = array(   
    /*'#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><div class="display-inline-block">Project Manager Comments </br><small>' . $form_state['case_delta']['refertitle'] . '</small></div>
      <div class="pull-right"><div class="dropdown open"> <button id="dLabel" class="btn btn-success replace-my-text-here-for-sorting" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true"> Sort <span class="caret"></span></button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel"><li><a href="javascript:void(0);" onclick="javascript:sortcolumns(\'resolved\')">Resolved</a></li><li><a href="javascript:void(0);" onclick="javascript:sortcolumns(\'report\')">Report</a></li></ul></div></div>
      </div>', */
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><div class="display-inline-block">Project Manager Comments </br><small>' . $form_state['case_delta']['refertitle'] . '</small></div></div>',

  );
  $getComment = _get_previous_comment_by_case($form_state['case_delta']['refernid']);
  $elements['project_manager_title'] = array(
    '#markup' => '<div class="project-manager-comment-render-class" id="project-manager-comment-render-' . $form_state['case_delta']['refernid'] . '">'.$getComment.'</div><div class="projectmanagetr-comment-list">',
  );
  $uniqueCommentId = md5($company->nid.'-'.time());
  $elements['unique_comment_id'] = array(
    '#type' => 'hidden',
    '#default_value' => $uniqueCommentId,
    '#attributes' => array('class' => array('unique-comment-id')),
  );
  $elements['comment_edit'] = array(
    '#type' => 'hidden',
    '#default_value' => 0,
    '#attributes' => array('class' => array('case-comment-edit')),
  );
  $elements['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('case-comment-section-inner','margin-bottom-10')),
  );
  $elements['project_manager_comments']['intro'] = array(
    '#markup' => '<div class="form-inline"><div class="form-group"><strong><div id="custom-date-update">'.date('l F d, Y',strtotime("today")).'</div></strong></div>',
  );
  $elements['project_manager_comments']['comments_date'] = array(
    '#type' => 'value',
    '#value' => strtotime(date('l F d, Y',strtotime("today"))),
  '#attributes' => array('class' => array('case-builder-date')),
  );
  $elements['project_manager_comments']['resolved'] = array(
    '#type' =>'checkbox',
    '#title' => t('Resolved'),
    '#attributes' => array('class' => array('case-builder-resolved')),
  '#prefix' => '<div class="pull-right"><div class="form-group padding-5">',
  '#suffix' =>'</div>',
  );
  $elements['project_manager_comments']['report'] = array(
    '#type' =>'checkbox',
    '#title' => t('Report'),
  '#attributes' => array('class' => array('case-builder-report')),
  '#prefix' => '<div class="form-group">',
  '#suffix' =>'</div></div></div>',
  );
  $elements['project_manager_comments']['comments'] = array(        
    '#type' => 'textarea',
  '#attributes' => array('class' => array('custom-project-comment')),
  '#default_value' => (isset($case->field_case_comment['und'])&& !empty($case->field_case_comment['und'])?$case->field_case_comment['und'][$i]['value']:''),
  );
  $elements['project_manager_comments' . $i]['submit'] = array(
    '#type' => 'submit',
    '#name' => 'case_comment_' . $i,
    '#value' => t('Save'),
    '#ajax' => array(
      'callback' => 'patient_care_project_manager_comment_submit_callback',
      'wrapper' => 'scm-sub-category-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $elements['project_manager_comments' . $i]['cancel'] = array(
      '#type' => 'markup',
      '#markup' => '<a href="javascript:void(0);" class="case-collapse" aria-hidden="true" case-comment-status="close"><input type="button" class="btn cancel-button" value="Close"></a>',
    );
  $elements['markup_end'] = array(
    '#suffix' => '</div>',    
  );
  return $elements;
}

function patient_care_project_manager_comment_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  if($values['comment_edit'] == 0) {
    $Todaystrtotime = strtotime(date('l F d, Y',strtotime("today")));
    $Tomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+1 days")));
    $dayafterTomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+2 days")));
    if(isset($values,$form_state['triggering_element']['#name']) && !empty($values['comments']) && !empty($values['refercase_nid'])){
      $case = node_load($values['refercase_nid']);
      $case->field_case_unique_id['und'][] = array('value' => $values['unique_comment_id']);
      $case->field_case_comment['und'][] = array('value' => $values['comments']);
      $case->field_case_comment_date['und'][] = array('value' => $values['comments_date']);
      $case->field_case_resolved_value['und'][] = array('value' => $values['resolved']);
      $case->field_case_report_value['und'][] = array('value' => $values['report']);
      node_save($case);
    }
  }
  else {
    $Todaystrtotime = strtotime(date('l F d, Y',strtotime("today")));
    $Tomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+1 days")));
    $dayafterTomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+2 days")));
    if(!empty($values['comments']) && !empty($values['refercase_nid'])){
      $case = node_load($values['refercase_nid']);
      foreach($case->field_case_comment['und'] as $caseDelta => $casVal) {      
        if($case->field_case_unique_id['und'][$caseDelta]['value'] == $values['unique_comment_id']) {
          $case->field_case_comment['und'][$caseDelta]['value'] = $values['comments'];
          $case->field_case_resolved_value['und'][$caseDelta]['value'] = $values['resolved'];
          $case->field_case_report_value['und'][$caseDelta]['value'] = $values['report'];
        }
      }
      node_save($case);
    } 
  }
  $uniqueCommentId = md5($company->nid.'-'.time());
  $commands[] = ajax_command_invoke("input.unique-comment-id", 'val',array($uniqueCommentId));
  $commands[] = ajax_command_invoke("textarea.custom-project-comment", 'val',array(''));
  $commands[] = ajax_command_invoke("input.case-comment-edit", 'val',array('0'));  
  $commands[] = ajax_command_invoke('.case-builder-report', 'prop',array('checked', false));
  $commands[] = ajax_command_invoke('.case-builder-resolved', 'prop',array('checked', false));
  $commands[] = ajax_command_html('#project-manager-comment-render-' . $values['refercase_nid'], _get_previous_comment_by_case($values['refercase_nid']));
  return array('#type' => 'ajax', '#commands' => $commands);
}


function patient_care_change_scm_project_scp_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  if($form_state['triggering_element']['#name']=='get-scm_projects_scp') {
    if(!empty($triggeringElement['#value'])) {
      $_SESSION['scm_project_nid'] = $triggeringElement['#value'];
      $caserender = casemanager_patient_care_outer();
      $commands[] = ajax_command_replace("#main-scm-casebuilder-outer", '<div id="main-scm-casebuilder-outer">'.render($caserender).'</div>');
      $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
    } 
  else {
    unset($_SESSION['scm_project_nid']);
    $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
  }
  }
  $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
  return array('#type' => 'ajax', '#commands' => $commands);
}

function patient_care_case_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  if ($_FILES['files']['name'] != '') {
    $fileCount = count($_FILES['files']['name']);
    $main_arr = array(
      'name'     => $_FILES['files']['name'],
      'type'     => $_FILES['files']['type'],
      'tmp_name' => $_FILES['files']['tmp_name'],
      'error'    => $_FILES['files']['error'],
      'size'     => $_FILES['files']['size'],
    );
    unset($_FILES);
    $i = 1;
    foreach ($main_arr['name'] as $key => $value) {
      if (!empty($value)) {
        foreach ($value as $key1 => $value1) {
          if (!empty($value1)) {
            $_FILES['files']['name'][$key . '__' . $i] = $main_arr['name'][$key][$key1];
            $_FILES['files']['type'][$key . '__' . $i] = $main_arr['type'][$key][$key1];
            $_FILES['files']['tmp_name'][$key . '__' . $i] = $main_arr['tmp_name'][$key][$key1];
            $_FILES['files']['error'][$key . '__' . $i] = $main_arr['error'][$key][$key1];
            $_FILES['files']['size'][$key . '__' . $i] = $main_arr['size'][$key][$key1];
            $i++;
          }
        }
      }
    }

    foreach ($_FILES['files']['name'] as $key => $value) {
      $file = file_save_upload($key, array(
        'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
      ));
      if ($file) {
        if ($file = file_move($file, 'public://')) {
          $key = explode('__', $key);
          $form_state['values'][$key[0]][] = $file;
        }
      }
    }
  }
  if(isset($values,$values['refercase_nid']) && !empty($values['refercase_nid'])){
    if(isset($values,$values['case_nid']) && !empty($values['case_nid'])){
      $case = node_load($values['case_nid']);
    }else{
      $case = _node_creation_call('patient_care',$values['refercase_title']);
    }
    $case->field_project_reference['und'][0]['nid'] = $_SESSION['scm_project_nid']; 
    $case->field_case_reference['und'][0]['nid'] = $values['refercase_nid']; 
    $case->field_patient_care_description['und'][0]['value'] = $values['patient_care_subtitle']; 

    $case->field_patient_satisfaction['und'][0]['value'] = $values['patient_satisfaction']; 
     
      $case->field_infection_implications['und'][0]['value'] = $values['infection_implications']; 
      $case->field_infection_prevention['und'][0]['value'] = $values['infection_implications_prevention_review'];
      $case->field_prevention_review_descript['und'][0]['value'] = $values['review_explain']; 


      $case->field_patient_care_outcomes['und'][0]['value'] = $values['outcomes_quantified'];

      $case->field_infection_implications_2['und'][0]['value'] = $values['outcomes_quantified_infection_implications']; 
      $case->field_infection_prevention_2['und'][0]['value'] = $values['outcomes_quantified_infection_implications_prevention_review']; 
      $case->field_implications_review_descri['und'][0]['value'] = $values['outcomes_quantified_infection_implications_prevention_review_explain']; 


    // Handling any files present.
    $files_arr = array(
      'field_quality_advisor' => 'advisor_document_patient',
      'field_infection_prevention_doc' => 'infection_prevention_doc',
      'field_infection_prevention_doc_2' => 'infection_prevention_doc_2',
    );

    foreach ($files_arr as $node_element => $file_element) {
      if (!empty($form_state['values'][$file_element])) {
        foreach ($form_state['values'][$file_element] as $imgkey3 => $file3) {
          $new_file3 = NULL;
          if (!empty($file3->fid) && $new_file3 = file_load($file3->fid)) {
            $file_arr3 = (array)$new_file3;
            $file_arr3['display'] = 1;
            $case->{$node_element}[LANGUAGE_NONE][] = $file_arr3;
          }
        }
      }
    }

    node_save($case);

    $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
  }

  switch ($form_state['triggering_element']['#name']) {
    case 'save_submit':
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
      break;

    case 'save_next_submit':
      // Redirecting user to next tab.
      $commands[] = ctools_ajax_command_redirect('/scm/preferences');
      break;

    case 'save_duplicate_submit':
      // Case duplicate
      _case_manager_case_duplicate($values['refercase_nid']);
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
      break;
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}
