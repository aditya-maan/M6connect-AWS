<?php

/**
 * Menu callbacks
 */
function scm_scorecard_content_dashboard() {
  $elements = array();

  $elements['prgram-scm-menu-items-dashboard'] = array(
    '#markup' => scm_csemanager_main_menu_links_content('scorecard'),
    '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10 margin-top-10">',
    '#suffix' => '</div></div>',
  );

  $elements['dashboard-project-form']= array(
    '#markup' => drupal_render(drupal_get_form('_project_filter_form')),
    '#prefix' => '<div class="border-outer-dashboard"><div class="clearfix">',
    '#suffix' => '</div>',
  );
  // $elements['prgram-project-listing'] = array(
  //   '#markup' => _get_scorecard_summary_table_data(),
  //   '#prefix' => '<div class="clearfix margin-bottom-10"><div class="project-summary-listing" id="scorecard-information-listing">',
  //   '#suffix' => '</div></div></div>',
  // );

  $elements['prgram-project-listing'] = array(
    '#markup' => _get_project_summary_table_data(),
    '#prefix' => '<div class="clearfix"><div class="project-summary-listing" id="scorecard-information-listing">',
    '#suffix' => '</div></div></div></div>',
  );
  return $elements;
}


function _project_filter_form($form, &$form_state) {
  global $company, $$base_url;
  $path_to_theme = drupal_get_path('theme', 'm6connect');
  
  $cmp_img = $base_url . '/' . $path_to_theme . '/images/scorecard_company_icon_small.png';
  $form['prgram-scm-all-projects-filter'] = array(
    '#type'          => 'select',
    '#title'         => 'Projects',
    '#options' => _load_project_list_with_number(),
    '#empty_option'  => 'All Projects',
    '#attributes'    => array('class' => array('form-control', 'prgram-scm-all-projects','border-radius-4')),
    '#ajax' => array(
      'callback'=> '_project_filter_callback',
      'wrapper' => 'scorecard-information-listing',
      'effect' => 'fade',
    ),
    '#prefix'        => '<div class="clearfix well-2 well-large"><div class="form-item col-sm-6 clearfix">',
  //'#prefix' => '<div class="clearfix well-sp well-large"><div class="form-item col-sm-6 clearfix"><div class="clearfix purple-image"><div class="pull-left"><div class="display-inline-block select-product-display-image img-align-with-select"><img src="' . $cmp_img . '"></div><div class="display-inline-block">',
    //'#suffix'        => '</div></div></div></div></div>',
	'#suffix'        => '</div>',
  );
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->join('field_data_field_m6_service_type','scm_type','scm_type.entity_id = n.nid');
  $query->condition('scm_type.field_m6_service_type_value','scm','=');  
  $query->fields('n', array('nid','title'));
  $query->condition('n.type','project_management','=');
  $query->condition('om.gid', $company->nid, '=');  
  $query->orderBy('n.nid', 'DESC');
  $getMyReqNodes = $query->execute()->fetchAllKeyed(0,1);
  
  $form['search-results'] = array(
    '#markup' => '<div class="col-sm-12"><p><span class="countdatapr">'.count($getMyReqNodes).'</span> Results</p></div>',
  );

  return $form;
}

function _project_filter_callback($form, &$form_state) {
  global $company;
  $commands = array();    
  $triggering_element = $form_state['triggering_element'];
  $commands[] = ajax_command_html("#scorecard-information-listing", _get_project_summary_table_data('','',$triggering_element['#value']));
  return array('#type' => 'ajax','#commands' => $commands);
}

function _get_project_summary_table_data($where = '',$pr='',$byProject='') {
  global $company;
  $rows = array();

  $header = array(
    array('data'=>'SCP #','class'=>array('text-center')),
    array('data'=>'Entity','class'=>array('text-center')), 
    array('data'=>'Team','class'=>array('text-center')), 
    array('data'=>'NEC','class'=>array('text-center')), 
    array('data'=>'Subcategory','class'=>array('text-center','col-md-2')),
    array('data'=>'Type','class'=>array('text-center')),
    array('data'=>'Start Date','class'=>array('text-center','col-md-1')),
    array('data'=>'Progress','class'=>array('text-center')),
    array('data'=>'Potential Annual<br>Impact','class'=>array('text-center')),    
    array('data'=>'Realized Annual<br>Savings','class'=>array('text-center')),    
    array('data'=>'Status','class'=>array('text-center')),
  );
  //$getMyReqNodes = _getting_table_data_call('project_management');  
  // Getting all the project id with there title
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->join('field_data_field_m6_service_type','scm_type','scm_type.entity_id = n.nid');
  $query->condition('scm_type.field_m6_service_type_value','scm','=');  
  $query->fields('n', array('nid','title'));
  $query->condition('n.type','project_management','=');
  $query->condition('om.gid', $company->nid, '=');
  if(!empty($byProject)) {
    $query->condition('n.nid', $byProject, '=');
  }
  $query->orderBy('n.nid', 'DESC');
  $getMyReqNodes = $query->execute()->fetchAllKeyed(0,1);
  //$getNodesNids = array_map('ucwords', $getNodesNids);
  
  $ProjectCategoryList = _get_scm_setting_data('project_category');
  $ProjectTypeList = _get_scm_setting_data('project_type');
  $ProjectStatusList = _get_scm_setting_data('project_status');
  $ProjectEntityvalue = '';
  $ProjectApprovalStatusList = _get_scm_setting_data('project_approval_status');
  foreach($getMyReqNodes as $values => $ids){ 
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
    if(isset($requestNodes->field_scm_project_subcategory['und'][0]['value']) && !empty($requestNodes->field_scm_project_subcategory['und'][0]['value'])) {
      $proSubcategorys = explode("-",$requestNodes->field_scm_project_subcategory['und'][0]['value']);
      if(!empty(_get_scm_setting_data('project_settings_category',$proSubcategorys[0]))){
        $ProjectCategoryvalue = _get_scm_setting_data('project_settings_category',$requestNodes->field_scm_project_category['und'][0]['value'])->title;
        if(!empty($proSubcategorys[1]) && !empty(_get_scm_setting_data('project_settings_category',$proSubcategorys[1]))){
          $ProjectSubCategoryvalue = _get_scm_setting_data('project_settings_category',$proSubcategorys[1])->title;
        }
      }
    }
    $subCat = ucwords($ProjectSubCategoryvalue);

    $scp_no = l($requestNodes->field_project_mgmt_number['und'][0]['value'], 'scm-project-view/' . $requestNodes->nid . '/nojs', array('attributes' => array('class' => array('use-ajax'))));

    $rows[] = array(
      'data' => array(
        array('data' => $scp_no,'class' => array('text-center')),
        array('data' => $ProjectEntityvalue,'class' => array('text-left')),
        array('data' => 'Heart & Vascular','class' => array('text-left')),
        array('data' => '5110','class' => array('text-left')),
        array('data' => $subCat,'class' => array('text-center','col-md-2')),    
        array('data' => ucwords($ProjectTypeList[$requestNodes->field_scm_project_project_type['und'][0]['value']]),'class' => array('text-center')),   
        array('data' => date('m/d/Y', $requestNodes->created),'class' => array('text-center','col-md-1')),        
        array('data' => '4-Opportunity Implemented','class' => array('text-left')),
        array('data' => '$264,039.00','class' => array('text-left')),
        array('data' => '$17,000.00','class' => array('text-left')),
        array('data' => '&nbsp;','class' => array('text-center','circle-color-green')), // circle-color-yellow, circle-color-red
      ),
    );
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows,'empty' => t('No Request created yet'), 'attributes' => array('class' => array('table', 'm6connect-custom-table', 'm6connect-custom-program-table', 'm6connect-program-request-table', 'm6init-datatable', 'table-hover','text-center', 'table-bordered', 'margin-0', 'table-dasboard'))));

  return $output;
}

function _dashboard_scorecard_form($form, &$form_state) {
  global $company; 
  $form['prgram-scm-all-projects'] = array(
    '#type'          => 'select',
    '#title'         => 'Projects',
    '#options' => _load_project_list_with_number(),
    '#empty_option'  => 'All Projects',
    '#attributes'    => array('class' => array('form-control', 'prgram-scm-all-projects')),
    '#ajax' => array(
      'callback'=> 'change_deshboard_project_table_callback',
      'wrapper' => 'scorecard-information-listing',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',
  );
  return $form;
}

function change_deshboard_project_table_callback($form, &$form_state) {
  global $company;  
  $commands = array();
  if($form_state['triggering_element']['#name']=='prgram-scm-all-projects') {
    $commands[] = ajax_command_html("#scorecard-information-listing",_get_scorecard_summary_table_data('',$form_state['triggering_element']['#value']));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_scorecard_content_my_scorecard($where = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10 margin-top-10">',
      '#suffix' => '</div>',
    );
  }
  else {
    $elements['menu-links'] = array(
      '#markup' => $where == 'new_scorecard' ? scm_scorecard_sub_menu_links_content() : scm_scorecard_dashboard_menu_links_content($where),
      '#prefix' => $where == 'new_scorecard' ? '<div class="clearfix csemanager-sub-menu margin-top-10 margin-bottom-10">' : '<div class="clearfix scm-main-menu margin-bottom-45">',
      '#suffix' => '</div>',
    );
  }

  $rec_content = '<div class="rec-content-outer">
                    <p style="font-size: 22px; font-weight: 700;"> Decision Recommendation </p>
                  </div>
                  <span style="font-size: 16px;">Under Process...</span>';
  $elements['scorecard-summary'] = array(
    '#prefix' => '<div id="my-scorecard-summary" style="display:none;">',
    '#suffix' => '</div><div id="decision-recommendation" style="display:none;">' . $rec_content . '</div>', 
  );

  $elements['project-form']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_form', $where)),
    '#prefix' => '<div class="clearfix sku-items">',
    '#suffix' => '</div>',
  );
  $elements['project-form-search']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_search_form')),
    '#prefix' => '<div class="scm-table-border"><div class="clearfix">',
    '#suffix' => '</div>',
  );
  $elements['prgram-project-listing'] = array(
    '#markup' => _get_scorecard_summary_table_data($where),
    '#prefix' => '<div class="clearfix"><div class="project-summary-listing" id="scorecard-information-listing">',
    '#suffix' => '</div></div></div></div>',
  );

  return $elements;
}

function _casemanager_scorecard_search_form($form, &$form_state) {
  global $company;

  $form['project-form-search-form'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Scorecards',
    '#attributes'    => array('class' => array('form-control', 'project-form-search-form'), 'id' =>'myInput', 'placeholder' => 'Search'),
    '#prefix'        => '<div class="clearfix well-2 well-large"><div class="form-item col-sm-6 clearfix">',
    '#suffix'        => '</div></div>',
  );

  $form['search-results'] = array(
    '#markup' => '<div class="col-sm-12"><p><span class="countdatapr">'.count(_fetching_scorecard_informationdata('scm_scorecard')).'</span> Results</p></div>',
  );

  return $form;
}

// function project_form_search_form_ajaxcall($form, &$form_state) {
//   dpm($form_state);
// }

// function project_form_search_form_ajaxcall($string = '') {
//   dpm($string);
// }

function _casemanager_scorecard_form($form, &$form_state, $where = '') {
  global $company;

  $form_state['where'] = $where;

  $getScoreCard = _fetching_scorecard_informationdata('scm_scorecard');


  foreach ($getScoreCard as $key => $value) {
     $getScoreCardlist[$value] = $value; 
  }

  $form['select-scorecard'] = array(
    '#type'       =>'select',
    '#options'    => $getScoreCardlist,
    '#attributes' => array('class'=> array('form-control', 'project_scorecard_main_pro')),
    '#ajax'       => array(
      'callback' => 'change_scorecard_callback',
      'wrapper'  => 'project_scorecard_main_container',
      'effect'   => 'fade',
    ),
    '#prefix'     => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix'     => '</div></div>',
  );

  if ($where == 'casemanager') {
    $change_item_list = array(
      'summary'            => t('Summary'),
      'stakeholderratings' => t('Stakeholder Ratings'),
      'comments'           => t('Comments'),
      'justification'      => t('Justification'),
    );

    $form['change-menu-item'] = array(
      '#type'       =>'select',
      '#options'    => $change_item_list,
      '#attributes' => array('class'=> array('form-control', 'casemanager_change_menu_item')),
      '#ajax'       => array(
        'callback' => 'change_menu_item_callback',
        'wrapper'  => 'project_scorecard_main_container',
        'effect'   => 'fade',
      ),
      '#prefix'     => '<div class="clearfix" style="display:none;">',
      '#suffix'     => '</div>',
    );
  }

  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }

  if ($where != 'casemanager') {
    $form['main-container']= array(
      '#type'       => 'container',
      '#attributes' => array('class'=>array('row')),
      '#prefix'     => '<div class="clearfix scm-scorecard"><div id="project_scorecard_main_container" style="display:none;" class="project-detail clearfix">',  
      '#process'    => array('project_scorecard_main_container_process'),
    );
  }

  if ($where != 'casemanager') {
    $form['submit']['save'] = array(
      '#type'     => 'submit',
      '#value'    => 'Save',
      '#name'     => 'save-submit',
      '#submit'   => array('scm_scorecard_submit'),
      '#prefix'   => '<div class="clearfix custom-submit-scorecard-button margin-bottom-15">',
    );
    $form['submit']['save_continue'] = array(
      '#type'     => 'submit',
      '#value'    => 'Save and Continue',
      '#name'     => 'save-continue-submit',
      '#submit'   => array('scm_scorecard_submit'),
    );

    $form['actions']['reset'] = array(
      '#type'     => 'markup',
      '#markup'   => '<input type="button" value="Cancel" class="form-submit custom-reset-button" onclick="jQuery(\'#project_scorecard_main_container\').hide(500); return false;">',
      '#suffix'   => '</div></div>',
    );
  }
  return $form;
}

function project_scorecard_main_container_process($element, &$form_state) {
  global $company;

  // Getting the project and RFP list by company
  $projectList = _load_project_list_with_number(); 
  $rfpList = _load_rfp_list_with_number();

  // Scorecard Number calculation
  $currentYear = date('Y');
  $myCounter = variable_get('SCORECARDNUMBER');
  $makeSr = str_pad($myCounter + 1, 6, "0", STR_PAD_LEFT);
  $scoreCard = 'SCO ' . $makeSr . '-' . $currentYear;

  $element['main-container']['full-container']= array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'project-details-full-mid')),
    '#weight'     => 3,
  );
  $element['main-container']['full-container']['inner-left-one']= array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('well', 'well-large', 'no-bg')),
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix"><h4 class="header_title_data">Create New Scorecard</h4></div>',
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-selected-nid'] = array(
    '#type'          => 'hidden',
    '#attributes'    => array('class' => array('form-control', 'scorecard-selected-nid')),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-number'] = array(
    '#type'          => 'textfield',
    '#disabled'      => !empty($form_state['where']) && $form_state['where'] == 'casemanager' ? TRUE : FALSE,
    '#title'         => 'Scorecard Number',
    '#attributes'    => array('class' => array('form-control', 'scorecard-number'), 'placeholder' => 'Scorecard Number'),
    '#default_value' => isset($defaultValues['scorecard-number']) ? $defaultValues['scorecard-number'] : $scoreCard,
    '#prefix'        => '<div class="clearfix well well-large"><div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );
  $element['main-container']['full-container']['inner-left-one']['project-name'] = array(
    '#type'          => 'select',
    '#disabled'      => !empty($form_state['where']) && $form_state['where'] == 'casemanager' ? TRUE : FALSE,
    '#title'         => 'Project Name',
    '#empty_option'  => 'Select Project Name | Number',
    '#options'       => $projectList,
    '#attributes'    => array('class' => array('form-control', 'project-name'), 'placeholder' => 'Project Name'),
    '#default_value' => isset($defaultValues['project-name']) ? $defaultValues['project-name'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
    '#select2'       => array(
      // 'width' => '350',
      'minimumResultsForSearch' => '5',
    ),
  );

   $element['main-container']['full-container']['inner-left-one']['scorecard-name'] = array(
    '#type'          => 'textfield',
    '#disabled'      => !empty($form_state['where']) && $form_state['where'] == 'casemanager' ? TRUE : FALSE,
    '#title'         => 'Scorecard Name',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('form-control', 'scorecard-name'), 'placeholder' => 'Scorecard Name'),
    '#default_value' => isset($defaultValues['scorecard-name']) ? $defaultValues['scorecard-name'] : '',
    '#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
    '#suffix'        => '</div>',  
  );
  $element['main-container']['full-container']['inner-left-one']['rfp-name'] = array(
    '#type'          => 'select',
    '#disabled'      => !empty($form_state['where']) && $form_state['where'] == 'casemanager' ? TRUE : FALSE,
    '#empty_option'  => 'Select RFP Name | Number',
    '#options'       => $rfpList,
    '#title'         => 'RFP Name',
    '#attributes'    => array('class' => array('form-control', 'rfp-name'), 'placeholder' => 'RFP Name'),
    '#default_value' => isset($defaultValues['rfp-name']) ? $defaultValues['rfp-name'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
    '#select2'       => array(
      // 'width' => '350',
      'minimumResultsForSearch' => '5',
    ),
  );
  $element['main-container']['full-container']['inner-left-one']['rating-date'] = array(
    '#type'            => 'date_popup',
    '#disabled'        => !empty($form_state['where']) && $form_state['where'] == 'casemanager' ? TRUE : FALSE,
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#title'           => 'Rating Due Date',
    '#required'        => TRUE,
    '#attributes'      => array('class' => array('form-control', 'rating-date'), 'placeholder' => 'Rating Due Date'),
    '#default_value'   => isset($defaultValues['rating-date']) ? $defaultValues['rating-date'] : '',
    '#prefix'          => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix relative m6connect_programe_date">',
    '#suffix'          => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span></div>',
  );
  $element['main-container']['full-container']['inner-left-one']['recommendation-award-date'] = array(
    '#type'            => 'date_popup',
    '#disabled'        => !empty($form_state['where']) && $form_state['where'] == 'casemanager' ? TRUE : FALSE,
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#title'           => 'Recommendation to Award Date',
    '#attributes'      => array('class' => array('form-control', 'recommendation-award-date'), 'placeholder' => 'Recommendation to Award Date'),
    '#default_value'   => isset($defaultValues['recommendation-award-date'])?$defaultValues['recommendation-award-date']:'',
    '#prefix'          => '<div class="form-item clearfix relative m6connect_programe_date">',
    '#suffix'          => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span></div></div></div></div>',
  );
  return $element;
}

function change_scorecard_callback($form, &$form_state) {
  global $company;
  $commands = array();

  if($form_state['triggering_element']['#name']=='select-scorecard') {
    if(!empty($form_state['triggering_element']['#value'])) {
      $cardNode = node_load($form_state['triggering_element']['#value']);
      // Active current scorecard.
      _make_scorecard_active($cardNode);      
      if ($form_state['where'] == 'casemanager') {
        // Showing scorecard summary.        
        $commands[] = ajax_command_html('#my-scorecard-summary', render(_get_scorecard_display_info($cardNode)));
        $commands[] = ajax_command_invoke('#my-scorecard-summary', 'show', array('600'));

        // We need to show scorecard decision content, without editing features.
        $decision_content = array();
        $decision_content['content-header'] = array(
          '#markup' => '<p style="font-size: 22px; font-weight: 700;"> Decision Recommendation </p>',
        );
        $decision_content['inner-menu'] = array(
          '#prefix' => '<div class="decision-inner-menu scm-main-menu">',
          '#suffix' => '</div>',
          '#markup' => _decision_inner_menu($form_state['where']),
        );

        // If this is the first time, then we shall show summary.
        module_load_include('inc', 'm6connect_scm', 'includes/supply.chain.manager.decision');
        $b_arr = array();
        $decision_content['decision'] = array(
          '#markup' => render(decision_main_container2_process(array(), $b_arr)),
        );

        $decision_html = render($decision_content);

        $commands[] = ajax_command_html('#decision-recommendation', $decision_html);
        $commands[] = ajax_command_invoke('#decision-recommendation', 'show', array('600'));
      }
      else {
        $triggeringElement = $form_state['triggering_element'];
        if(!empty($triggeringElement['#value'])) {
          $myCounter = variable_get('SCORECARDNO'); 
          $makeSr = str_pad($myCounter + 1, 6, "0", STR_PAD_LEFT);
          $cardNumber = 'SCO'.$makeSr.'-'.date('Y');

          $storage_project = array(
            'cardNumber'  => $cardNode->title,
              'cardName'      => isset($cardNode->field_scorecard_name['und'])?$cardNode->field_scorecard_name['und'][0]['value']:'',
          'ratingDueDate' => isset($cardNode->field_rating_due_date['und'])?$cardNode->field_rating_due_date['und'][0]['value']:'',
          'projectNid'  => isset($cardNode->field_project_nid_for_scm['und'])?$cardNode->field_project_nid_for_scm['und'][0]['value']:'',
          'rfpNid'    => isset($cardNode->field_rfp_nid_for_scm['und'])?$cardNode->field_rfp_nid_for_scm['und'][0]['value']:'',
          'awardDate'   => isset($cardNode->field_recommendation_to_award_da['und'])?$cardNode->field_recommendation_to_award_da['und'][0]['value']:'',
            );        
          $ratingDate = $storage_project['ratingDueDate']!=''?date('m/d/Y', strtotime($storage_project['ratingDueDate'])):'';
          $awardDate = $storage_project['awardDate']!=''?date('m/d/Y', strtotime($storage_project['awardDate'])):'';

          
          


          if(!empty($cardNode->field_scorecard_state['und'][0]['value']) && $cardNode->field_scorecard_state['und'][0]['value'] == 'Complete'){
            $commands[] = ajax_command_css('.custom-submit-scorecard-button', array('pointer-events' => 'none'));      
          }else{
            $commands[] = ajax_command_css('.custom-submit-scorecard-button', array('pointer-events' => 'all'));
          }
          $commands[] = ajax_command_invoke("input.scorecard-selected-nid", 'val',array($triggeringElement['#value']));
          $commands[] = ajax_command_invoke("input.scorecard-number", 'val',array($storage_project['cardNumber']));
          $commands[] = ajax_command_invoke("select.project-name", 'val',array($storage_project['projectNid']));
          $commands[] = ajax_command_invoke("select.project-name", 'trigger',array('change'));    
          $commands[] = ajax_command_invoke("input.scorecard-name", 'val',array($storage_project['cardName']));
          $commands[] = ajax_command_invoke("select.rfp-name", 'val',array($storage_project['rfpNid']));
          $commands[] = ajax_command_invoke("select.rfp-name", 'trigger',array('change')); 
          $commands[] = ajax_command_invoke("input.rating-date", 'val',array($ratingDate));
          $commands[] = ajax_command_invoke("input.recommendation-award-date", 'val',array($awardDate));
          $commands[] = ajax_command_invoke("#project_scorecard_main_container", 'show');  

          $status_text = $form_state['where'] == 'casemanager' ? t('View Scorecard') : t('Update Scorecard');
          $commands[] = ajax_command_invoke(".header_title_data", 'text', array($status_text));
          
          // Need to change the evaluate href on the go.
          $eval_url = url('scorecard/evaluate/' . $cardNode->nid, array('absolute' => TRUE));
          $commands[] = array('command' => 'changeEvaluateHref', 'arguments' => array('href' => $eval_url));
        }
      }
    }
    else {
      $commands[] = ajax_command_invoke("input.scorecard-selected-nid", 'val',array(''));
      $commands[] = ajax_command_invoke("input.scorecard-number", 'val',array(''));
      $commands[] = ajax_command_invoke("select.project-name", 'val',array(''));    
      $commands[] = ajax_command_invoke("input.scorecard-name", 'val',array(''));
      $commands[] = ajax_command_invoke("select.rfp-name", 'val',array(''));
      $commands[] = ajax_command_invoke("input.rating-date", 'val',array(''));
      $commands[] = ajax_command_invoke("input.recommendation-award-date", 'val',array(''));  
    }
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
function scm_scorecard_submit(&$form, &$form_state) { 
  global $user, $company; 
  $formVal = $form_state['values'];
  $getTitle = $formVal['scorecard-number'];
  if(!empty($formVal['scorecard-selected-nid'])){
    $crateNode = node_load($formVal['scorecard-selected-nid']);
    $statusform = 'updated';
  } else {
    $crateNode = _node_creation_call('scm_scorecard',$getTitle);
    $statusform = 'saved';
  }
  $crateNode->field_scorecard_name['und'][0]['value'] = $formVal['scorecard-name']; 
  $crateNode->field_rating_due_date['und'][0]['value'] = $formVal['rating-date'];
  $crateNode->field_project_nid_for_scm['und'][0]['value'] = $formVal['project-name'];
  $crateNode->field_rfp_nid_for_scm['und'][0]['value'] = $formVal['rfp-name'];
  $crateNode->field_recommendation_to_award_da['und'][0]['value'] = $formVal['recommendation-award-date']; 
  $myCounter = variable_get('SCORECARDNUMBER'); 
  variable_set('SCORECARDNUMBER',$myCounter+1);
  node_save($crateNode);
  if($form_state['triggering_element']['#name'] == 'save-continue-submit') {
    $getNodesNids = _fetching_scorecard_informationdata('scm_scorecard');
    foreach($getNodesNids as $nidkey => $nidvalue) {
      $activenode_load = node_load($nidvalue);
      if(!empty($formVal['scorecard-selected-nid']) && $formVal['scorecard-selected-nid']==$nidvalue) {
        $activenode_load->field_scorecard_status['und'][0]['value'] = 'Active';
      } else {
        $activenode_load->field_scorecard_status['und'][0]['value'] = 'Deactive';
      }
      node_save($activenode_load);
    }
    $form_state['redirect'] = 'scorecard/select-products';
  }
  drupal_set_message('Scorecard - '.$getTitle.' has been '.$statusform.' successfully.');
  
}

function change_menu_item_callback($form, &$form_state) {
  $commands = array();

  if ($form_state['triggering_element']['#name'] == 'change-menu-item' && !empty($form_state['triggering_element']['#value'])) {
    $value = $form_state['triggering_element']['#value'];

    $decision_content = array();
    $decision_content['content-header'] = array(
      '#markup' => '<p style="font-size: 22px; font-weight: 700;"> Decision Recommendation </p>',
    );
    $decision_content['inner-menu'] = array(
      '#prefix' => '<div class="decision-inner-menu scm-main-menu">',
      '#suffix' => '</div>',
      '#markup' => _decision_inner_menu($form_state['where']),
    );

    if ($value == 'summary') {
      module_load_include('inc', 'm6connect_scm', 'includes/supply.chain.manager.decision');
      $b_arr = array();
      $decision_content['decision'] = array(
        '#markup' => render(decision_main_container2_process(array(), $b_arr)),
      );
    }

    if ($value == 'stakeholderratings') {
      $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');
      $scorecard_node = node_load($scorecard_nid);
      $decision_content['decision'] = array(
        '#markup' => _get_group_ratings_content_evaluate($scorecard_node),
      );
    }

    if ($value == 'comments') {
      module_load_include('inc', 'm6connect_scm', 'includes/supply.chain.manager.decision');
      $decision_content['decision'] = array(
        '#markup' => render(comments_main_container2_process(array(), $form_state)),
      );
    }

    if ($value == 'justification') {
      $decision_content['decision'] = array(
        '#markup' => render(justification_main_container2_process(array(), $form_state)),
      );
    }

    $decision_html = render($decision_content);

    $commands[] = ajax_command_html('#decision-recommendation', $decision_html);
    $commands[] = ajax_command_invoke('#decision-recommendation', 'show', array('600'));

    if ($value == 'stakeholderratings') {
      $commands[] = array('command' => 'groupPostRenderCalculations');
    }

    $commands[] = array('command' => 'changeMiniMenuActive', 'arguments' => array('data' => $value));
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Menu callback for scm-project-view/%node/%ctools_js
 *
 * This function redirects the user to casemanager when user clicks on the
 * project while on dashboard.
 */
function redirect_user_to_casemanager($node = NULL, $ajax = NULL) {
  if (!empty($node->nid) && $node->type == 'project_management') {
    // Making this project as active.
    if (isset($_SESSION['scm_project_nid'])) {
      unset($_SESSION['scm_project_nid']);
    }

    $_SESSION['scm_project_nid'] = $node->nid;
  }

  // We need to redirect the user to CaseManager.
  if (!empty($ajax)) {
    ctools_include('ajax');

    $commands = array();
    $commands[] = ctools_ajax_command_redirect('scm/my-casemanager');

    print ajax_render($commands);
    drupal_exit();
  }

  drupal_goto('scm/my-casemanager');
}