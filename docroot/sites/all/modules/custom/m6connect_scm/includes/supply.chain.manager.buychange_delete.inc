<?php
/*
 * Supply Chain manager - Case Builder's
 * Buy or change section started
 */ 
function scm_buy_change_content() {
  global $user,$company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  //drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager_del.js');
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
  $elements['scm-buy-change-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_buy_change_form')),
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
    '#markup' => drupal_render(casemanager_buy_change_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements; 
}
/*
 * Initialization of case and comment renderation
 *
 */
function casemanager_buy_change_outer(){
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
  $commentsclass = 'left';
  $statusFlag = FALSE;
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
        '#markup' => drupal_render(drupal_get_form('casemanager_buy_change_left_form',$casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left section-top-parent-new"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    $dispaly_none = 'dispaly_none';
      $elements['case_section_' . $nid]['scm-casebuilder-right']= array(
        '#markup' => drupal_render(drupal_get_form('casemanager_buy_change_right_form',$casedelta)),
        '#prefix' => '<div class="'.$commentsclass.' col-md-8 padding-10 margin-bottom-10 casebuilder-details-right '.$dispaly_none.'"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    }
  $elements['scm-buy-change-end']= array(
      '#markup' => '</div>',
    );
  }
  return $elements; 
}

function casemanager_buy_change_form($form, &$form_state) {
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
    'callback'=> 'buy_change_change_scm_project_scp_callback',
    'wrapper' => 'program_scm_main_container',
    'effect' => 'fade',
  ),
  '#prefix' => '<div class="clearfix"><div class="pull-right next-margin-0 changein-document-btn">',
  '#suffix' => '</div></div>',
  );
  return $form;
}

function casemanager_buy_change_left_form($form, &$form_state,$i) {
  global $company;

  $form_state['case_delta'] = $i;

  if (!isset($form_state['sub_category_fetch_options'])) {
    $form_state['sub_category_fetch_options'] = array();
  }

  if ($form_state['triggering_element']['#name'] == 'category_informations') {
    if (!empty($form_state['triggering_element']['#value'])) {
      $main_cat_id = $form_state['triggering_element']['#value'];
      $sub_categories = _get_all_sub_categories_scm_keyed($main_cat_id);
      $form_state['sub_category_fetch_options'] = $sub_categories;
    }
    else {
      $form_state['sub_category_fetch_options'] = array();
    }
  }

  $form['left_case_section'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container','clearfix','padding-10 ')),
    '#prefix' => '<div id="casebuilder-left-section" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('casebuilder_left_buy_change_section_process'),
  );  
  return $form;
}

function casemanager_buy_change_right_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i;
  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('buy_change_project_manager_comments_process'),
  );
  return $form;
}

function casebuilder_left_buy_change_section_process($elements, &$form_state) {
  global $company;

  $categoryData = _get_all_main_categories_scm();
  $categoryData = array_map('ucwords', $categoryData);

  $subcategoryData = array();
  if (!empty($form_state['sub_category_fetch_options'])) {
    $subcategoryData = array_map('ucwords', $form_state['sub_category_fetch_options']);
  }

  /* Getting the main case id */
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
    $query2->condition('caser.bundle','buy_or_change');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
  $case = node_load($nodenid);
  }

  if (!empty($case->field_case_category_info_new['und'][0]['value'])) {
    $main_cat_id = $case->field_case_category_info_new['und'][0]['value'];
    $sub_categories = _get_all_sub_categories_scm_keyed($main_cat_id);
    $subcategoryData = $sub_categories;
  }

  $hasecase = (isset($case, $case->nid) && !empty($case->nid)?'case-expand':'notcasefound');
  $notcasefound = (isset($case, $case->nid) && !empty($case->nid)?"":'data-trigger="hover" data-toggle="popover"  data-placement="bottom" data-content="Please Save First"');
  $changeindocument = 'changein-document';  
  $changeindocumentdata = (isset($case, $case->nid) && !empty($case->nid)?'document-save-'.$case->nid:'document-save-new');
  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );
  $casetitle = (strlen($form_state['case_delta']['refertitle']) > 26) ? substr($form_state['case_delta']['refertitle'], 0, 23) . '...' : $form_state['case_delta']['refertitle'];
  $caseStatusBtn = '<input id="case-toogle-check-cust" class="case-status-check" type="checkbox" checked data-toggle="toggle" data-on="Active" data-off="Inactive" data-onstyle="success" data-offstyle="danger" for="'.$form_state['case_delta']['refernid'].'">';
  $elements['case_progress_by_section_title'] = array(
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
  $casetextareaedit = '<i class="pull-right fa fa-pencil casetextareaedit" aria-hidden="true" style="cursor: pointer;"></i>';
  // 
  // $textarea1 = (isset($case, $case->field_buy_or_change_description['und'],$case->field_buy_or_change_description['und'][0]['value']) && !empty($case->field_buy_or_change_description['und'][0]['value'])?'dispaly_none':'');  
  // $textareavalue1 = (isset($case, $case->field_buy_or_change_description['und'],$case->field_buy_or_change_description['und'][0]['value']) && !empty($case->field_buy_or_change_description['und'][0]['value'])?$case->field_buy_or_change_description['und'][0]['value'].$casetextareaedit:'');
  // $elements['buy_change_subtitle'] = array(        
  //   '#type' => 'textarea',
  //   '#attributes'=> array('placeholder'=> 'Enter case description here.'),
  //   '#default_value' => (isset($case, $case->field_buy_or_change_description['und'],$case->field_buy_or_change_description['und'][0]['value']) && !empty($case->field_buy_or_change_description['und'][0]['value'])?$case->field_buy_or_change_description['und'][0]['value']:''),
  //   '#prefix' => '<div class="clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Description</div><div class="hastextareavalue">'.$textareavalue1.'</div><div class="hastextarea '.$textarea1.'">',
  //   '#suffix' => '</div></div>',
  // );
  $textarea_label = !empty($_SESSION['scm_label_object']['case_builder']['description']) ? $_SESSION['scm_label_object']['case_builder']['description'] : t('Description');
  $elements['case_description'] = array(
    '#type'   => 'markup',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">' . $textarea_label . '</div><div class="hastextareavalue">',
    '#markup' => $getCaseDesc,
    '#suffix' => '</div></div>',
  );
  /*
   * Category information 
   * Section goes here
   */
  $catInfoArr = array(
    'Cardiac Rhythm Management Devices' => 'Cardiac Rhythm Management Devices',
    'Cardiovascular Lead Extraction Products' => 'Cardiovascular Lead Extraction Products',
    'Coronary Stents Non-Drug Eluting' => 'Coronary Stents Non-Drug Eluting',
    'Diagnostic and Interventional Cardiology' => 'Diagnostic and Interventional Cardiology',
    'Drug Eluting Coronary Stents' => 'Drug Eluting Coronary Stents',
    'Electrophysiology Products' => 'Electrophysiology Products',
    'ECG Electrodes, Cables, Lead Wires and Defibrillator Pads' => 'ECG Electrodes, Cables, Lead Wires and Defibrillator Pads',
    'External Defibrillators and Related Products' => 'External Defibrillators and Related Products',
    'Heart Valve Products' => 'Heart Valve Products',
    'Hemostasis and Compression Products' => 'Hemostasis and Compression Products',
    'Intra-Aortic Balloon Catheters and Pumps' => 'Intra-Aortic Balloon Catheters and Pumps',
    'Invasive Cardiology Equipment' => 'Invasive Cardiology Equipment',
    'Non-Invasive Cardiology Equipment' => 'Non-Invasive Cardiology Equipment',
    'Open Heart Disposable Supplies' => 'Open Heart Disposable Supplies',
    'Peripheral and Biliary Stents' => 'Peripheral and Biliary Stents',
    'Thrombectomy Products' => 'Thrombectomy Products',
    'Vascular Closure Devices' => 'Vascular Closure Devices',
    'Vascular Grafts' => 'Vascular Grafts',
    'Vena Cava Filters' => 'Vena Cava Filters',
  );  
  $elements['category_informations'] = array(  
    '#type' => 'select',
    '#options' => $categoryData,
    '#attributes' => array('class'=> array('form-control','reset-callback','conditional-element','category-informations-main')),    
    '#empty_option' => 'Select Category(s)',
    '#default_value' => (isset($case, $case->field_case_category_info_new['und'],$case->field_case_category_info_new['und'][0]['value']) && !empty($case->field_case_category_info_new['und'][0]['value'])?$case->field_case_category_info_new['und'][0]['value']:0),
    '#validate' => TRUE,
    '#required' => TRUE,
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Category Information</div><div class="clearfix"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div>
    <div class="selecticon tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
    '#ajax' => array(
      'callback'=> 'change_sc_project_category_callback',
      'wrapper' => 'categoriesrealtionarea-' . $form_state['case_delta']['refernid'],
    ),
  );
  $elements['sub_category_informations'] = array(
    '#type' => 'select',
    '#options' => $subcategoryData,
  //'#disabled' => TRUE,
    '#empty_option' => 'Select Subcategory(s)',
    '#default_value' => (isset($case, $case->field_case_sub_category_info['und'],$case->field_case_sub_category_info['und'][0]['value']) && !empty($case->field_case_sub_category_info['und'][0]['value'])?$case->field_case_sub_category_info['und'][0]['value']:0),
    '#attributes' => array('class'=> array('form-control','reset-callback','conditional-element','category-informations-main-sub')),    
    '#prefix' => '<div id="categoriesrealtionarea-' . $form_state['case_delta']['refernid'] .'" class="clearfix conditionstate-one categoriesrealtionarea"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="selecticon tristate-toggle-button pull-right">',
    '#suffix' => '</div></div></div>',
  );
    
  /*
   * Product information 
   * Section  goes here
   */
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['is_this_a_product'] = array(
    '#type' => 'radios',
    '#title' => t('Is this a Product?'),
    '#default_value' => (isset($case, $case->field_case_product_info_product['und'],$case->field_case_product_info_product['und'][0]['value']) && !empty($case->field_case_product_info_product['und'][0]['value'])?$case->field_case_product_info_product['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),        
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix section-top-parent margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Product Information</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['capital_component'] = array(
    '#type' => 'radios',
    '#title' => 'Has Capital Component?',
    '#default_value' => (isset($case, $case->field_product_info_capital['und'],$case->field_product_info_capital['und'][0]['value']) && !empty($case->field_product_info_capital['und'][0]['value'])?$case->field_product_info_capital['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element','product-capitalcomponentyes')),
    '#prefix' => '<div class="clearfix conditionstate-one product-capitalcomponent-yes"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['buy_change_pharmaceutical'] = array(
    '#type' => 'radios',
    '#title' => 'Is this a Pharmaceutical?',
    '#default_value' => (isset($case, $case->field_case_product_info_pharmace['und'],$case->field_case_product_info_pharmace['und'][0]['value']) && !empty($case->field_case_product_info_pharmace['und'][0]['value'])?$case->field_case_product_info_pharmace['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['buy_change_reprocessed'] = array(
    '#type' => 'radios',
    '#title' => 'Can this be Reprocessed?',
    '#default_value' => (isset($case, $case->field_case_product_info_reproces['und'],$case->field_case_product_info_reproces['und'][0]['value']) && !empty($case->field_case_product_info_reproces['und'][0]['value'])?$case->field_case_product_info_reproces['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $textarea2 = (isset($case, $case->field_describe_products_consider['und'],$case->field_describe_products_consider['und'][0]['value']) && !empty($case->field_describe_products_consider['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue2 = (isset($case, $case->field_describe_products_consider['und'],$case->field_describe_products_consider['und'][0]['value']) && !empty($case->field_describe_products_consider['und'][0]['value'])?$case->field_describe_products_consider['und'][0]['value'].$casetextareaedit:'');
  $elements['product_consideration'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_describe_products_consider['und'],$case->field_describe_products_consider['und'][0]['value']) && !empty($case->field_describe_products_consider['und'][0]['value'])?$case->field_describe_products_consider['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Describe the products under consideration.'),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue">'.$textareavalue2.'</div><div class="hastextarea '.$textarea2.'">',
    '#suffix' => '</div></div></div></div>',
  );
  /*
   * Equipment information 
   * Section  goes here
   */
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['is_this_a_equipment'] = array(
    '#type' => 'radios',
    '#title' => t('Is this Equipment?'),
    '#default_value' => (isset($case, $case->field_case_equipment_info['und'],$case->field_case_equipment_info['und'][0]['value']) && !empty($case->field_case_equipment_info['und'][0]['value'])?$case->field_case_equipment_info['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),       
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix margin-bottom-10 equipment Info"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Equipment Information</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['capital_dollars'] = array(
    '#type' => 'radios',
    '#title' => 'Does this require Capital Dollars?',
    '#default_value' => (isset($case, $case->field_case_equipment_capital_dol['und'],$case->field_case_equipment_capital_dol['und'][0]['value']) && !empty($case->field_case_equipment_capital_dol['und'][0]['value'])?$case->field_case_equipment_capital_dol['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['budget_for_fiscal'] = array(
    '#type' => 'radios',
    '#title' => 'Is it Budgeted for this fiscal year?',
    '#default_value' => (isset($case, $case->field_case_equipment_info_budget['und'],$case->field_case_equipment_info_budget['und'][0]['value']) && !empty($case->field_case_equipment_info_budget['und'][0]['value'])?$case->field_case_equipment_info_budget['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-two"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['sale_service_agreement'] = array(
    '#type' => 'radios',
    '#title' => 'Has a Point of Sale Service Agreement been presented?',
    '#default_value' => (isset($case, $case->field_equipment_info_point_sale['und'],$case->field_equipment_info_point_sale['und'][0]['value']) && !empty($case->field_equipment_info_point_sale['und'][0]['value'])?$case->field_equipment_info_point_sale['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['consumable_component'] = array(
    '#type' => 'radios',
    '#title' => 'Is there a Consumable Component?',
    '#default_value' => (isset($case, $case->field_equipment_info_consumable['und'],$case->field_equipment_info_consumable['und'][0]['value']) && !empty($case->field_equipment_info_consumable['und'][0]['value'])?$case->field_equipment_info_consumable['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['store_phi'] = array(
    '#type' => 'radios',
    '#title' => 'Will this equipment Store PHI?',
    '#default_value' => (isset($case, $case->field_equipment_info_store_phi['und'],$case->field_equipment_info_store_phi['und'][0]['value']) && !empty($case->field_equipment_info_store_phi['und'][0]['value'])?$case->field_equipment_info_store_phi['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['does_product_have_nann_requirement'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have NANN-National Association of Neonatal Nurses requirement?',
    '#default_value' => !empty($case->field_does_product_have_nann['und'][0]['value']) ? $case->field_does_product_have_nann['und'][0]['value'] : 0,
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_awhonn'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have AWHONN-Association of Women’s Health, Obstetrics and Neonatal Nurses requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_awhonn['und'],$case->field_does_product_have_awhonn['und'][0]['value']) && !empty($case->field_does_product_have_awhonn['und'][0]['value'])?$case->field_does_product_have_awhonn['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_aap'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have AAP-American Academy of Pediatrics requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_aap['und'],$case->field_does_product_have_aap['und'][0]['value']) && !empty($case->field_does_product_have_aap['und'][0]['value'])?$case->field_does_product_have_aap['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_aorn'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have AORN – Association of Operating Room Nurses requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_aorn['und'],$case->field_does_product_have_aorn['und'][0]['value']) && !empty($case->field_does_product_have_aorn['und'][0]['value'])?$case->field_does_product_have_aorn['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_aami'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have AAMI – Association for the Advancement of Medical Instrumentation requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_aami['und'],$case->field_does_product_have_aami['und'][0]['value']) && !empty($case->field_does_product_have_aami['und'][0]['value'])?$case->field_does_product_have_aami['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_jcaho'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have JCAHO – Joint Commission requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_jcaho['und'],$case->field_does_product_have_jcaho['und'][0]['value']) && !empty($case->field_does_product_have_jcaho['und'][0]['value'])?$case->field_does_product_have_jcaho['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_aatb'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have AATB – American Association of Tissue Banks requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_aatb['und'],$case->field_does_product_have_aatb['und'][0]['value']) && !empty($case->field_does_product_have_aatb['und'][0]['value'])?$case->field_does_product_have_aatb['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_acr'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have ACR – American College of Radiology requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_acr['und'],$case->field_does_product_have_acr['und'][0]['value']) && !empty($case->field_does_product_have_acr['und'][0]['value'])?$case->field_does_product_have_acr['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_cms'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have CMS – Centers for Medicare and Medicaid Services requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_cms['und'],$case->field_does_product_have_cms['und'][0]['value']) && !empty($case->field_does_product_have_cms['und'][0]['value'])?$case->field_does_product_have_cms['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_asge'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have ASGE –American Society for Gastrointestinal Endoscopy requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_asge['und'],$case->field_does_product_have_asge['und'][0]['value']) && !empty($case->field_does_product_have_asge['und'][0]['value'])?$case->field_does_product_have_asge['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_abem'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have ABEM -American Board of Emergency Medicine requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_abem['und'],$case->field_does_product_have_abem['und'][0]['value']) && !empty($case->field_does_product_have_abem['und'][0]['value'])?$case->field_does_product_have_abem['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_ama'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have AMA – American Medical Association requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_ama['und'],$case->field_does_product_have_ama['und'][0]['value']) && !empty($case->field_does_product_have_ama['und'][0]['value'])?$case->field_does_product_have_ama['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_apwca'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have APWCA – American Professional Wound Care Association requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_apwca['und'],$case->field_does_product_have_apwca['und'][0]['value']) && !empty($case->field_does_product_have_apwca['und'][0]['value'])?$case->field_does_product_have_apwca['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_asahq'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have ASAHQ – American Society of Anesthesiologists requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_asahq['und'],$case->field_does_product_have_asahq['und'][0]['value']) && !empty($case->field_does_product_have_asahq['und'][0]['value'])?$case->field_does_product_have_asahq['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_asco'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have ASCO – American Society of Clinical Oncology requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_asco['und'],$case->field_does_product_have_asco['und'][0]['value']) && !empty($case->field_does_product_have_asco['und'][0]['value'])?$case->field_does_product_have_asco['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['does_product_have_acla'] = array(
    '#type' => 'radios',
    '#title' => 'Does this product have ACLA – American Clinical Laboratory Association requirement?',
    '#default_value' => (isset($case, $case->field_does_product_have_acla['und'],$case->field_does_product_have_acla['und'][0]['value']) && !empty($case->field_does_product_have_acla['und'][0]['value'])?$case->field_does_product_have_acla['und'][0]['value']:0),
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );








  $textarea3 = (isset($case, $case->field_describe_the_equipment['und'],$case->field_describe_the_equipment['und'][0]['value']) && !empty($case->field_describe_the_equipment['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue3 = (isset($case, $case->field_describe_the_equipment['und'],$case->field_describe_the_equipment['und'][0]['value']) && !empty($case->field_describe_the_equipment['und'][0]['value'])?$case->field_describe_the_equipment['und'][0]['value'].$casetextareaedit:'');
  $elements['describe_equipment'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_describe_the_equipment['und'],$case->field_describe_the_equipment['und'][0]['value']) && !empty($case->field_describe_the_equipment['und'][0]['value'])?$case->field_describe_the_equipment['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Describe the products under consideration.'),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue">'.$textareavalue3.'</div><div class="hastextarea '.$textarea3.'">',
    '#suffix' => '</div></div></div>',
  );
    $elements['compliance_approved'] = array(
      '#type' => 'radios',
      '#title' => 'Has Compliance Approved?',
      '#default_value' => (isset($case, $case->field_compliance_approved['und'],$case->field_compliance_approved['und'][0]['value']) && !empty($case->field_compliance_approved['und'][0]['value'])?$case->field_compliance_approved['und'][0]['value']:0),
      '#options' => $active,
      
      '#attributes' => array('class'=>array('component','conditional-element')),
      '#prefix' => '<div class="clearfix product-capitalcomponent-item"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
      '#suffix' => '</div></div>',
    );  
    $approval_document = 'approval_document'; 
    $elements['approval_document']= array(
      '#type' => 'file',
      '#title' => 'Attachment',
      '#name' => 'files['.$approval_document.'][]',
      '#upload_location' => 'public://',  
       
      '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$approval_document . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$approval_document . '")','class'=> array('scm-my-request-attachment','conditional-element')),
      '#description' => t('Use CTRL + Click to choose multiple attachments.'),
      //'#attributes' => array('multiple' => 'multiple','class'=> array('scm-my-request-attachment')),    
      '#prefix' => '<div class="clearfix form-item" style="display:none;">',
      '#suffix' => '</div>',
    );
    $elements['attachment_list'] = array(
      '#markup' => ''
    );

    $previousfilelist = '';
    if(isset($case,$case->field_info_compliance_approval['und']) && !empty($case->field_info_compliance_approval['und'])){
      $filelist = array();
      foreach ($case->field_info_compliance_approval['und'] as $key => $value) {
        $file_url = file_create_url($value['uri']);
  $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o" aria-hidden="true"></i>', '/filerowremove/field_info_compliance_approval/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
      }
      $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';

    }

    // Changing upload sign, if a file already exists.
    $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
    if (!empty($previousfilelist)) {
      $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
    }


    $elements['approval_document_link']= array(
      '#markup' => '<label>Attach Compliance Approval
        documentation.</label>
                    <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $approval_document . '-id">
                      <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                    </a>
                    <div class="previous-file-list">'.$previousfilelist.'</div>
                    <div id="'.$form_state['case_delta']['refernid'] . '-' . $approval_document . '-id-filelist" style="display:none;"></div>',
      '#prefix' => '<div class="clearfix"><div class="pull-left tristate-icon">' . $upload_sign . '</div><div class="tristate-toggle-button pull-right">',
      '#suffix' => '</div></div></div>',
    );
  /*
   * Service Information
   * Section  goes here
   */
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['is_this_a_service'] = array(
    '#type' => 'radios',
    '#title' => t('Is this a Service?'),
    '#default_value' => (isset($case, $case->field_service_info_service['und'],$case->field_service_info_service['und'][0]['value']) && !empty($case->field_service_info_service['und'][0]['value'])?$case->field_service_info_service['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),       
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.'
    clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Service Information</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $textarea4 = (isset($case, $case->field_services_considered['und'],$case->field_services_considered['und'][0]['value']) && !empty($case->field_services_considered['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue4 = (isset($case, $case->field_services_considered['und'],$case->field_services_considered['und'][0]['value']) && !empty($case->field_services_considered['und'][0]['value'])?$case->field_services_considered['und'][0]['value'].$casetextareaedit:'');
  $elements['describe_service'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_services_considered['und'],$case->field_services_considered['und'][0]['value']) && !empty($case->field_services_considered['und'][0]['value'])?$case->field_services_considered['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Describe the Services being considered.'),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue">'.$textareavalue4.'</div><div class="hastextarea '.$textarea4.'">',
    '#suffix' => '</div></div></div></div>',
  );
  /*
   * Patient Care
   * Section  goes here
   */
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['patient_care'] = array(
    '#type' => 'radios',
    '#title' => t('Does it impact Patient Care?'),
    '#default_value' => (isset($case, $case->field_buy_or_change_patient_care['und'],$case->field_buy_or_change_patient_care['und'][0]['value']) && !empty($case->field_buy_or_change_patient_care['und'][0]['value'])?$case->field_buy_or_change_patient_care['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),       
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Patient Care</div><div class="clearfix"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div></div>',
  );

  /*
   * Project/Case Overlaps
   * Section  goes here
   */
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['is_this_part_another_project'] = array(
    '#type' => 'radios',
    '#title' => 'Is it a part of or does it affect other projects or initiatives (SCM, Transformation Office, etc)?',
    '#default_value' => (isset($case, $case->field_projectcaseoverlapsproject['und'],$case->field_projectcaseoverlapsproject['und'][0]['value']) && !empty($case->field_projectcaseoverlapsproject['und'][0]['value'])?$case->field_projectcaseoverlapsproject['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),       
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix "><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Project/Case Overlaps</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $elements['approval_proceeding_received'] = array(
    '#type' => 'radios',
    '#title' => 'Seek Management Approval before proceeding.  Approval Received?',
    '#default_value' => (isset($case, $case->field_management_approval['und'],$case->field_management_approval['und'][0]['value']) && !empty($case->field_management_approval['und'][0]['value'])?$case->field_management_approval['und'][0]['value']:0),
    '#options' => $active,   
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one anotherproject-one" style="display:none"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );
  $textarea5 = (isset($case, $case->field_projects_affected_approval['und'],$case->field_projects_affected_approval['und'][0]['value']) && !empty($case->field_projects_affected_approval['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue5 = (isset($case, $case->field_projects_affected_approval['und'],$case->field_projects_affected_approval['und'][0]['value']) && !empty($case->field_projects_affected_approval['und'][0]['value'])?$case->field_projects_affected_approval['und'][0]['value'].$casetextareaedit:'');
  $elements['describe_another_project'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_projects_affected_approval['und'],$case->field_projects_affected_approval['und'][0]['value']) && !empty($case->field_projects_affected_approval['und'][0]['value'])?$case->field_projects_affected_approval['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Describe the projects affected and approvals received.'),
    '#prefix' => '<div class="clearfix margin-bottom-10 proceeding-received conditionstate-two" style="display:none"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue">'.$textareavalue5.'</div><div class="hastextarea '.$textarea5.'">',
    '#suffix' => '</div></div></div></div>', // adding an extra closing div, because commented the below code.
  );

  // Established standard section from patient care.
  // Moving to buy or change. Change requested July 31, 2017.

  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['standard_established'] = array(
    '#type' => 'radios',
    '#title' => t('Has a standard already been Established?'),
    '#default_value' => (isset($case, $case->field_established_standard['und'],$case->field_established_standard['und'][0]['value']) && !empty($case->field_established_standard['und'][0]['value'])?$case->field_established_standard['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),       
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="clearfix '.$changeindocument.'">
                    <div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">
                      Standardization
                    </div>
                    <div class="clearfix conditionstatebase">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right padding-5">',
    '#suffix' =>      '</div>
                    </div>
                  </div>',
  );

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
        'callback' => 'buy_change_save_case_submit_callback',
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
      'callback' => 'buy_change_save_case_submit_callback',
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
        'callback' => 'buy_change_save_case_submit_callback',
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type' => 'none'),
      ),
    '#attributes' => array('documentsave'=>$changeindocumentdata, 'class'=>array('btn', 'btn-primary','margin-0',$changeindocumentdata)),
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

function change_sc_project_category_callback($form, &$elements) {
  return $form['left_case_section']['sub_category_informations'];
}

function casemanager_buy_change_left_form_validate($form, &$form_state) {
  /*if($_FILES['files']['name'] != '')  {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
      $file = file_save_upload($i, array( 
        'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
      ));
      if ($file) {    
        if ($file = file_move($file, 'public://')) {
          $form_state['values']['approval_document'][$i] = $file;
        } 
      }
    }
  }*/
}

function buy_change_project_manager_comments_process($elements, &$form_state){
  if(isset($form_state['case_delta'],$form_state['case_delta']['refernid']) && !empty($form_state['case_delta']['refernid']))
  global $user,$company;
  $defaultProjectNid = '';
  $defaultProjectNid = $_SESSION['scm_project_nid'];
  //$case = node_load($form_state['case_delta']['nid']);
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
    $query2->condition('caser.bundle','buy_or_change');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
  $case = node_load($nodenid);
  }
  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );
  $elements['project_manager_inner_menu'] = array(
    /*'#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><i class="pull-right fa fa-times case-collapse" aria-hidden="true" case-comment-status="close" style="cursor: pointer;"></i><div class="display-inline-block">Project Manager Comments </br><small>'.$form_state['case_delta']['refertitle'].'</small></div>

    <div class="pull-right"><div class="dropdown open"> <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true"> Short <span class="caret"></span></button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel"><li><a href="javascript:void(0);">Coming soon</a></li><li><a href="javascript:void(0);">Resolved</a></li><li><a href="javascript:void(0);">Report</a></li></ul></div></div>




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
    //'#parents' => array('case_comment',$i,'comments_date'),
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
      'callback' => 'buy_change_project_manager_comment_submit_callback',
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

function buy_change_project_manager_comment_submit_callback($form,&$form_state){ 
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

function buy_change_change_scm_project_scp_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  if($form_state['triggering_element']['#name']=='get-scm_projects_scp') {
    if(!empty($triggeringElement['#value'])) {
      $_SESSION['scm_project_nid'] = $triggeringElement['#value'];
      $caserender = casemanager_buy_change_outer();
      $commands[] = ajax_command_replace("#main-scm-casebuilder-outer", '<div id="main-scm-casebuilder-outer">'.render($caserender).'</div>');
      $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
    }
  else {
    unset($_SESSION['scm_project_nid']);
    $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
  } 
  }
  $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
  return array('#type' => 'ajax', '#commands' => $commands);
}

function buy_change_save_case_submit_callback($form,&$form_state) { 
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
      $case = _node_creation_call('buy_or_change',$values['refercase_title']);
    }
    $case->field_project_reference['und'][0]['nid'] = $_SESSION['scm_project_nid']; 
    $case->field_case_reference['und'][0]['nid'] = $values['refercase_nid']; 
    $case->field_buy_or_change_description['und'][0]['value'] = $values['buy_change_subtitle']; 
    $case->field_case_category_info_new['und'][0]['value'] = $values['category_informations']; 
  $case->field_case_sub_category_info['und'][0]['value'] = $values['sub_category_informations']; 
    $case->field_case_product_info_product['und'][0]['value'] = $values['is_this_a_product']; 
    /**/$case->field_product_info_capital['und'][0]['value'] = $values['capital_component']; 
    /**/$case->field_compliance_approved['und'][0]['value'] = $values['compliance_approved']; 
    /**///$case->field_info_compliance_approval['und'][0]['value'] = $values['case_nid']; 
    /**/$case->field_case_product_info_pharmace['und'][0]['value'] = $values['buy_change_pharmaceutical']; 
    /**/$case->field_case_product_info_reproces['und'][0]['value'] = $values['buy_change_reprocessed']; 
    /**/$case->field_describe_products_consider['und'][0]['value'] = $values['product_consideration']; 
    $case->field_case_equipment_info['und'][0]['value'] = $values['is_this_a_equipment']; 
    /**/$case->field_case_equipment_capital_dol['und'][0]['value'] = $values['capital_dollars']; 
    /**/$case->field_equipment_info_point_sale['und'][0]['value'] = $values['sale_service_agreement']; 
    /**/$case->field_case_equipment_info_budget['und'][0]['value'] = $values['budget_for_fiscal']; 
    /**/$case->field_equipment_info_consumable['und'][0]['value'] = $values['consumable_component']; 
    /**/$case->field_equipment_info_store_phi['und'][0]['value'] = $values['store_phi']; 

     
    /**/$case->field_does_product_have_awhonn['und'][0]['value'] = $values['does_product_have_awhonn']; 
    /**/$case->field_does_product_have_aap['und'][0]['value'] = $values['does_product_have_aap']; 
    /**/$case->field_does_product_have_aorn['und'][0]['value'] = $values['does_product_have_aorn']; 
    /**/$case->field_does_product_have_aami['und'][0]['value'] = $values['does_product_have_aami']; 
    /**/$case->field_does_product_have_jcaho['und'][0]['value'] = $values['does_product_have_jcaho']; 
    /**/$case->field_does_product_have_aatb['und'][0]['value'] = $values['does_product_have_aatb']; 
    /**/$case->field_does_product_have_acr['und'][0]['value'] = $values['does_product_have_acr']; 
    /**/$case->field_does_product_have_cms['und'][0]['value'] = $values['does_product_have_cms']; 
    /**/$case->field_does_product_have_asge['und'][0]['value'] = $values['does_product_have_asge']; 
    /**/$case->field_does_product_have_abem['und'][0]['value'] = $values['does_product_have_abem']; 
    /**/$case->field_does_product_have_ama['und'][0]['value'] = $values['does_product_have_ama']; 
    /**/$case->field_does_product_have_apwca['und'][0]['value'] = $values['does_product_have_apwca']; 
    /**/$case->field_does_product_have_asahq['und'][0]['value'] = $values['does_product_have_asahq']; 
    /**/$case->field_does_product_have_asco['und'][0]['value'] = $values['does_product_have_asco']; 
    /**/$case->field_does_product_have_acla['und'][0]['value'] = $values['does_product_have_acla']; 
    /**/$case->field_does_product_have_nann['und'][0]['value'] = $values['does_product_have_nann_requirement'];

    
    /**/$case->field_describe_the_equipment['und'][0]['value'] = $values['describe_equipment']; 
    $case->field_service_info_service['und'][0]['value'] = $values['is_this_a_service']; 
    /**/$case->field_services_considered['und'][0]['value'] = $values['describe_service']; 
    $case->field_buy_or_change_patient_care['und'][0]['value'] = $values['patient_care']; 
    $case->field_projectcaseoverlapsproject['und'][0]['value'] = $values['is_this_part_another_project']; 
    /**/$case->field_management_approval['und'][0]['value'] = $values['approval_proceeding_received']; 
    /**//**/$case->field_projects_affected_approval['und'][0]['value'] = $values['describe_another_project'];
    $case->field_established_standard['und'][0]['value'] = $values['standard_established']; 
    $case->field_project_case_affect['und'][0]['value'] = $values['affect_projects_initiatives']; 

     if(!isset($case->field_info_compliance_approval['und'])){
        $case->field_info_compliance_approval['und'] = array();
      }
    foreach ($form_state['values']['approval_document'] as $imgkey3 => $file3) {
      
      $new_file3 = file_load($file3->fid);
      $file_arr3 = (array)$new_file3;
      $file_arr3['display'] = 1;          
      $case->field_info_compliance_approval['und'][] = $file_arr3;
    } 
    node_save($case);
    
    $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
  }

  switch ($form_state['triggering_element']['#name']) {
    case 'save_submit':
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
      break;

    case 'save_next_submit':
      // Redirecting user to next tab.
      $commands[] = ctools_ajax_command_redirect('/scm/patient-care');
      break;

    case 'save_duplicate_submit':
      // Case duplicate
      _case_manager_case_duplicate($values['refercase_nid']);
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
      break;
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/*
 * users Request container for 
 * Login, Generating request and chat form
 */

function scm_user_request_container() {
  if(isset($_SESSION['login-mail']) && !empty($_SESSION['login-mail'])){
    unset($_SESSION['login-mail']);
  }
  $elements = array();
  $elements['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12 col-xs-12 scm-user-request-main-container')),
  );
  $elements['main-container']['login-container']= array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_user_request_login_form')),
    '#attributes' => array('class'=>array('scm-user-request-login')),
    '#prefix' => '<div class="margin-bottom-10 col-md-7 col-md-offset-3 col-xs-12 scm-user-request-login-container">',
    '#suffix' => '</div>',
  );
 return $elements;
}

function scm_user_request_login_form($form,&$form_state) {
  $form['login-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('scm-user-request-login-container')),
  );

  $form['login-container']['login-container-markup']= array(
    '#type' => 'markup',
    '#markup' => '<h3 class="margin-bottom-20 margin-top-10">Supply Chain Request</h3>',
    '#attributes' => array('class'=>array('scm-user-request-login-markupupper')),
  );
  $form['login-container']['request_login-email-or-employeeID'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Address'),
    '#attributes' => array('class'=>array('scm-user-request-login-emailaddress'),'placeholder' => t('Please enter Email Address')),
    '#prefix' => '<div class="clearfix scm-user-request-login-forminner-container"><div class="clearfix margin-bottom-25 scm-user-request-login-emailaddress-container"><span>Please enter your Employee ID or email address to submit your request:</span>',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['login-container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#ajax' => array(
      'callback' => 'scm_user_request_login_form_submit_callback',
      'wrapper' => 'scm-user-request-login-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10 text-center"><div class="scm-user-request-login-submit display-inline-block">',
    '#suffix' => '</div>',
  );
  $form['login-container']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#ajax' => array(
      'callback' => 'scm_user_request_login_form_cancel_callback',
      'wrapper' => 'scm-user-request-login-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="cancelbtncatset display-inline-block">',
    '#suffix' => '</div></div></div>',
  );
  return $form;
} 

function scm_user_request_login_form_submit_callback($form, &$form_state){
  $_SESSION['login-mail'] = '';
  if (form_get_errors()) {
    return $form;
  }
  $login_mail = $form_state['values']['request_login-email-or-employeeID'];
  if(!valid_email_address($login_mail)){
    form_set_error('login Email','Invalid Email Address Format');
    return $form;
  } 
  if(!empty(get_scm_user_database_by_email($login_mail))){
    get_scm_user_database_by_email($login_mail);
    $_SESSION['login-mail'] = get_scm_user_database_by_email($login_mail)->email;
    $username = get_scm_user_database_by_email($login_mail)->fristname.' '.get_scm_user_database_by_email($login_mail)->lastname;
    drupal_set_message(t('Login Successful '.$username));
    // $form_state['redirect'] = 'scm/my-request';
    $commands[] = '';
    $commands[] = ctools_ajax_command_redirect('scm/my-request', 0, array());
    return array('#type' => 'ajax', '#commands' => $commands);
  } else {
    form_set_error('login Email check','Email address not exist please contact your Supply Chain Manager');
    return $form;
  }


}

function scm_user_request_login_form_cancel_callback($form, &$form_state){
    $commands[] ='';
    $commands[] = ajax_command_invoke("input.scm-user-request-login-emailaddress", 'val',array(''));
    return array('#type' => 'ajax', '#commands' => $commands);
}

// function scm_user_request_request_form($form,&$form_state) {
//   $form['login-container']= array(
//     '#type' => 'container',
//     '#attributes' => array('class'=>array('scm-user-request-login-container')),
//   );
//   $form['login-container']['request-log-out'] = array(
//     '#type' => 'submit',
//     '#value' => t('logout'),
//     '#ajax' => array(
//       'callback' => 'scm_user_request_login_form_logout_callback',
//       'wrapper' => 'scm-user-request-request-form',
//       'method' => 'replace',
//       'effect' => 'fade',
//     ),
//     '#prefix' => '<div class="cancelbtncatset display-inline-block">',
//     '#suffix' => '</div></div></div>',
//   );

//   $form['login-container']['request_login-email-or-employeeID'] = array(
//     '#type' => 'textfield',
//     '#title' => t('Email Address'),
//     '#attributes' => array('class'=>array('scm-user-request-login-emailaddress'),'placeholder' => t('Please enter Email Addres')),
//     '#prefix' => '<div class="clearfix scm-user-request-login-forminner-container"><div class="margin-bottom-25 scm-user-request-login-emailaddress-container"><span>Please enter your Employee ID or email address to submit your request:</span>',
//     '#suffix' => '</div>',
//     '#required' => TRUE,
//   );
//   return $form;
// } 

function scm_user_request_login_form_logout_callback($form, &$form_state) {
  unset($_SESSION['login-mail']);
}



/********************************************due_diligence start*************************************************/

/*
 * Supply Chain manager - Case Builder's
 * Due Diligence section started
 */ 
function scm_due_diligence_content() {
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
  $elements['scm-due-diligence-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_due_diligence_change_form')),
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
    '#markup' => drupal_render(casemanager_due_diligence_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements; 
}

/*
 * Initialization of case and comment renderation
 *
 */
function casemanager_due_diligence_outer() {
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
        '#markup' => drupal_render(drupal_get_form('casemanager_due_diligence_left_form',$casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
      $dispaly_none = 'dispaly_none';
      $elements['case_section_' . $nid]['scm-casebuilder-right']= array(
        '#markup' => drupal_render(drupal_get_form('casemanager_due_diligence_right_form',$casedelta)),
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

function casemanager_due_diligence_change_form($form, &$form_state) {
  $getReqNodes = _getting_table_subcat_title('project_management');
  
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
      'callback'=> 'due_diligence_change_scm_project_scp_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix"><div class="pull-right next-margin-0 changein-document-btn">',
    '#suffix' => '</div></div>',
  );
  return $form;
}

function casemanager_due_diligence_left_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i; 
  if (!isset($form_state['get_node_count'])) {
    $form_state['get_node_count'] = TRUE;
  }
  if(isset($i['refernid']) && !empty($i['refernid'])){  
    //drup_msg('has refernid');
    $query2 = db_select('field_data_field_case_reference','caser');
    $query2->fields('caser',array('entity_id'));
    $query2->condition('caser.bundle','due_diligence');
    $query2->condition('caser.field_case_reference_nid',$i['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
    $caseload = node_load($nodenid );
    if (!empty($caseload->field_vendor_name['und']) && !empty($caseload->field_vendor_name['und'][0]['value']) && $form_state['get_node_count'] != FALSE) {
      
      foreach ($caseload->field_vendor_name['und'] as $clkey => $clvalue) {
        $tempIdentifer = uniqid();
        $form_state['supplier_default_values'][$tempIdentifer] = array(
          'vendor_name' => $clvalue['value'],
        );

        $form_state['supplier_count'][]  = $tempIdentifer;
      }

      $tempIdentifer = uniqid();
      $form_state['supplier_count'][]  = $tempIdentifer;
      $form_state['get_node_count'] = FALSE;
    }
  }

  if (!empty($form_state['triggering_element']['#parents'][2]) && $form_state['triggering_element']['#parents'][2] == 'vendor_name') {

    $val = $form_state['triggering_element']['#value'];
    if(isset($val) && !empty($val)){    
      $nid = _get_nid_by_title($val);
      if(isset($nid) && !empty($nid) && is_numeric($nid)){
        $refernid = $form_state['values']['refercase_nid'];      
        $node  = node_load($nid);
        $user = user_load($node->uid);
        $vfirst = (isset($user,$user->field_first_name['und']) && !empty($user->field_first_name['und'][0]['value'])?$user->field_first_name['und'][0]['value']:'');
        $vlast = (isset($user,$user->field_last_name['und']) && !empty($user->field_last_name['und'][0]['value'])?$user->field_last_name['und'][0]['value']:'');
        $vmail = (isset($node,$node->field_company_email['und']) && !empty($node->field_company_email['und'][0]['email'])?$node->field_company_email['und'][0]['email']:'');     
        $form_state['supplier_default_values'][$form_state['triggering_element']['#parents'][1]] = array(
          'vendor_name' => $val,
        );

        // We only add a new row, if we do not have one.
        $supplier_count = $form_state['supplier_count'];
        $last_sc = end($supplier_count);

        if (!empty($form_state['input']['supplier'][$last_sc]['vendor_name'])) {
          $form_state['supplier_count'][] = uniqid();
        }

        $form_state['get_node_count'] = FALSE;
      }
    }else{
      $form_state['supplier_default_values'][$form_state['triggering_element']['#parents'][1]] = array(
        'vendor_name' => '',
        /*'first_name' => '',
        'last_name' => '',
        'vendor_email' => '',*/
      );
    }
  }

  if (empty($form_state['supplier_count'])) {
    //$form_state['supplier_count'] = 0;
    //drup_msg('has empty');
    $tempIdentifer = uniqid();
    $form_state['supplier_count'][]  = $tempIdentifer;
  }  
  $form['left_case_section'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container','clearfix','padding-10 ')),
    '#prefix' => '<div id="casebuilder-left-section" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('casebuilder_left_due_diligence_section_process'),
  );  
  //dpm($form_state,'$form_state');
  return $form;
  
}

function casebuilder_left_due_diligence_section_process($elements, &$form_state) {
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
    $query2->condition('caser.bundle','due_diligence');
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
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title case-section-title-sp margin-top-10">
                    <div class="pull-left fixed-case-title fixed-case-title">Case '.$form_state['case_delta']['sr'].': '.$casetitle.'</div>
                    <div class="pull-right toggle-case-status-check changein-document-btn">'.$caseStatusBtn.'
                      <i class="fa fa-comments-o ' .$hasecase.'" aria-hidden="true" case-status="close" style="cursor: pointer;" '.$notcasefound.'></i>
                    </div>
                    <div class="notcasefound dispaly_none">Please save first</div>
                  </div>',   
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
  $casetextareaedit = '<i class="pull-right fa fa-pencil casetextareaedit" aria-hidden="true" style="cursor: pointer;"></i>';
  
  $terminate_case_value =(isset($case, $case->field_terminate_case['und'],$case->field_terminate_case['und'][0]['value']) && !empty($case->field_terminate_case['und'][0]['value'])?$case->field_terminate_case['und'][0]['value']:0);
  $terminate_case_class1 = '';
  $caseheadertitle = '';
  if($terminate_case_value ==2){
    $terminate_case_class1 = 'bluebgtitle redbgtitle';
    $caseheadertitle = 'This case is terminated';
  }
  $elements['case_description'] = array(
    '#type'   => 'markup',
    '#prefix' => '<div class="clearfix margin-bottom-10">
                    <div class="clearfix section-title margin-10 '.$terminate_case_class1.'">
                      '.$caseheadertitle.'
                    </div>
                    <div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Description</div>
                    <div class="hastextareavalue">',
    '#markup' => $getCaseDesc,
    '#suffix' => '</div></div>',
  );
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));
  $elements['one_supplier'] = array(
    '#type' => 'radios',
    '#title' => t('Is there more than one supplier in the market?'),
    '#default_value' => (isset($case, $case->field_one_supplier['und'],$case->field_one_supplier['und'][0]['value']) && !empty($case->field_one_supplier['und'][0]['value'])?$case->field_one_supplier['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('satisfaction','conditional-element')),        
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'">
                    <div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">
                      Supplier Information
                    </div>                  
                    <div class="conditionstatebase1">
                      <div class="clearfix">
                        <div class="pull-left tristate-icon">
                          <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                        </div>
                        <div class="tristate-toggle-button pull-right">',
    '#suffix' =>        '</div>
                      </div>
                    ',
  );
  
  $elements['thr_one_supplier'] = array(
    '#type' => 'radios',
    '#title' => 'Does THR use more than one Supplier?',
    '#default_value' => (isset($case, $case->field_thr_one_supplier['und'],$case->field_thr_one_supplier['und'][0]['value']) && !empty($case->field_thr_one_supplier['und'][0]['value'])?$case->field_thr_one_supplier['und'][0]['value']:0),
    '#options' => $active,        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                  ',
  );
  $supporting_documentation = 'supporting_documentation';
  $elements['supporting_documentation']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $supporting_documentation . '][]',
    '#upload_location' => 'public://',
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$supporting_documentation . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$supporting_documentation . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    //'#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="conditionstate-greentwo">
                  <div class="clearfix section-top-parent">
                    <div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $previousfilelist = '';
  if(isset($case,$case->field_market_share['und']) && !empty($case->field_market_share['und'])){
    $filelist = array();
    foreach ($case->field_market_share['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o" aria-hidden="true"></i>', '/filerowremove/field_market_share/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['supporting_documentation_link']= array(
    '#markup' => '<label>Provide market share supporting documentation.</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $supporting_documentation . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $supporting_documentation . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign . '
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>
                </div>
                ',
  );
  $elements['suppliers_considering']= array(
    '#type' => 'textfield',
    '#title' => 'How many suppliers are you considering?',
    '#default_value' => (isset($case, $case->field_supplier_considering['und'],$case->field_supplier_considering['und'][0]['value']) && !empty($case->field_supplier_considering['und'][0]['value'])?$case->field_supplier_considering['und'][0]['value']:''),
    '#attributes'=> array('class'=>array('pull-right','wirteenicon-change'),'style' => 'width:50px;'),
    
    '#prefix' => '<div class="clearfix">
                    <div class="pull-left tristate-icon">
                      <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                    </div>
                    <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>',
  );
  $elements['suppliers_considering_count'] = array(
    '#type'    => 'container',
    '#process' => array('suppliers_considering_count_children_process'),
    '#theme'   => 'suppliers_considering_count_children_theme',
    '#prefix' => '<div id="are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'] . '" class="conditionstate-one physicians-container-here">',
    '#suffix' => '</div>'
  );

  
  $elements['are_clinicians_primary_suffix'] = array(
    '#markup' => '</div></div></div>',
  );

  $elements['does_every_entity_useit'] = array(
    '#type' => 'radios',
    '#title' => 'Does every Entity Use it?',
    '#default_value' => (isset($case, $case->field_does_every_entity_useit['und'],$case->field_does_every_entity_useit['und'][0]['value']) && !empty($case->field_does_every_entity_useit['und'][0]['value'])?$case->field_does_every_entity_useit['und'][0]['value']:0),
    '#options' => $active,        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstatebase1">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                  
                  ',
  );
  $textarea33 = (isset($case, $case->field_does_everyentity_useit_des['und'],$case->field_does_everyentity_useit_des['und'][0]['value']) && !empty($case->field_does_everyentity_useit_des['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue33 = (isset($case, $case->field_does_everyentity_useit_des['und'],$case->field_does_everyentity_useit_des['und'][0]['value']) && !empty($case->field_does_everyentity_useit_des['und'][0]['value'])?$case->field_does_everyentity_useit_des['und'][0]['value'].$casetextareaedit:'');
  
  $elements['does_every_entity_useit_decribe'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_does_everyentity_useit_des['und'],$case->field_does_everyentity_useit_des['und'][0]['value']) && !empty($case->field_does_everyentity_useit_des['und'][0]['value'])?$case->field_does_everyentity_useit_des['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Enter description.'),
    '#prefix' => '<div class="conditionstate-oneredgreen">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        &nbsp;
                      </div>
                      <div class="tristate-toggle-button pull-right icon-shiftup-outer">
                        <div class="hastextareavalue">'.$textareavalue33.'</div>
                        <div class="hastextarea '.$textarea33.'">',
    '#suffix' =>        '</div>
                      </div>
                    </div>
                  </div>
                </div>
              
            ',
  );
  $elements['one_supplier_suffix'] = array(
    '#markup' => '</div>',
  );
  /*
   * Regulatory section  goes here
   */
  // Removed an option and changed classes on Aug 01, 2017.
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));

  $elements['equipment_requires_fda_approval'] = array(
    '#type' => 'radios',
    '#title' => 'Is this an FDA regulated product?',
    '#default_value' => (isset($case, $case->field_fda_approval['und'],$case->field_fda_approval['und'][0]['value']) && !empty($case->field_fda_approval['und'][0]['value'])?$case->field_fda_approval['und'][0]['value']:0),
    '#options' => $active,
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'">
                    <div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">
                      Regulatory
                    </div>
                    <div class="conditionstatebase1">
                      <div class="clearfix">
                        <div class="pull-left tristate-icon">
                          <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                        </div>
                        <div class="tristate-toggle-button pull-right">',
    '#suffix' => '      </div>
                      </div>',
  );

//fda_approved start
  $elements['fda_approved'] = array(
    '#type' => 'radios',
    '#title' => 'Is this in process/approved through the FDA Premarket Approval process?',
    '#default_value' => (isset($case, $case->field_fda_approved['und'],$case->field_fda_approved['und'][0]['value']) && !empty($case->field_fda_approved['und'][0]['value'])?$case->field_fda_approved['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen">
                  <div class="conditionstate-onegreen-red">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                  
                 ',
  );




$elements['anticipate_approval'] = array(
    '#type' => 'radios',
    '#title' => 'Do you Anticipate Approval?',
    '#default_value' => (isset($case, $case->field_anticipate_approval['und'],$case->field_anticipate_approval['und'][0]['value']) && !empty($case->field_anticipate_approval['und'][0]['value'])?$case->field_anticipate_approval['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen-redtwo">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                    
                 ',
  );
  $terminate_case_value =(isset($case, $case->field_terminate_case['und'],$case->field_terminate_case['und'][0]['value']) && !empty($case->field_terminate_case['und'][0]['value'])?$case->field_terminate_case['und'][0]['value']:0);
  $terminate_case_class = '';
  if($terminate_case_value ==2){
    $terminate_case_class = 'redbgtitle';
  }else{
    $terminate_case_class = 'terminate-case';
  }
  $elements['terminate_case'] = array(
    '#type' => 'radios',
    '#title' => 'Would you like to Terminate this Case?',
    '#default_value' => $terminate_case_value,
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen-redthree">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right '.$terminate_case_class.'">',
    '#suffix' =>      '</div>
                    </div>
                    
                 ',
  );


  $textarea3 = (isset($case, $case->field_associated_fda_approval['und'],$case->field_associated_fda_approval['und'][0]['value']) && !empty($case->field_associated_fda_approval['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue3 = (isset($case, $case->field_associated_fda_approval['und'],$case->field_associated_fda_approval['und'][0]['value']) && !empty($case->field_associated_fda_approval['und'][0]['value'])?$case->field_associated_fda_approval['und'][0]['value'].$casetextareaedit:'');

  $elements['decribe_fda_approval'] = array(
    '#type' => 'textarea',    
    '#default_value' => (isset($case, $case->field_associated_fda_approval['und'],$case->field_associated_fda_approval['und'][0]['value']) && !empty($case->field_associated_fda_approval['und'][0]['value'])?$case->field_associated_fda_approval['und'][0]['value']:''),
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Decribe the current issues associated with FDA Approval'),
    '#prefix' => '<div class="conditionstate-onegreen-redfour">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        &nbsp;
                      </div>
                      <div class="tristate-toggle-button pull-right icon-shiftup-outer">
                        <div class="hastextareavalue">'.$textareavalue3.'</div>
                        <div class="hastextarea '.$textarea3.'">',
    '#suffix' =>        '</div>
                      </div>
                    </div>
                  </div>
                </div>
              
            ',
  );


  $elements['anticipated_approval_date'] = array(
    '#title' => 'Provide Anticipated Approval date? <i class="fa fa-2x fa-calendar pull-right anticipated-approvaldate-link" aria-hidden="true" style="
    color: #000;
"></i>',
    '#default_value' => (isset($case, $case->field_anticipated_approval_date['und'],$case->field_anticipated_approval_date['und'][0]['value']) && !empty($case->field_anticipated_approval_date['und'][0]['value'])?$case->field_anticipated_approval_date['und'][0]['value']:''),
    '#attributes' => array('class'=>array('anticipated-approval-date')),
    '#type' => 'date_popup',
    '#date_format' => 'm-d-Y',
    '#date_label_position' => '',    
    '#size' => 33,
    '#prefix' => '<div class="conditionstate-onegreen-green">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        &nbsp;
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                  </div>
                  </div>  
                 </div>
                </div>
              
            ',
  );
  //fda_approved end



  $elements['equipment_requires_fda_approval_process'] = array(
    '#type' => 'radios',
    '#title' => 'Is this equipment in the FDA Premarket Approval process?',
    '#default_value' => (isset($case, $case->field_fda_premarket_approval['und'],$case->field_fda_premarket_approval['und'][0]['value']) && !empty($case->field_fda_premarket_approval['und'][0]['value'])?$case->field_fda_premarket_approval['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="conditionstate-onegreen">
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                    <div class="clearfix text-right open-payments-window"><a href="https://www.accessdata.fda.gov/scripts/cdrh/cfdocs/cfPMA/pma.cfm" onclick="window.open(\'https://www.accessdata.fda.gov/scripts/cdrh/cfdocs/cfPMA/pma.cfm\', \'newwindow\', \'width=600,height=400\'); return false;">Premarket Approval (PMA) Database Search</a></div>
                 ',
  );
  $attach_fda_pma_report = 'attach_fda_pma_report';
  $elements['attach_fda_pma_report']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $attach_fda_pma_report . '][]',
    '#upload_location' => 'public://',
    //'#multiple' => TRUE,     
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$attach_fda_pma_report . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$attach_fda_pma_report . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    //'#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="clearfix section-top-parent">
                    <div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $previousfilelist = '';
  if(isset($case,$case->field_attach_fda_pma_report['und']) && !empty($case->field_attach_fda_pma_report['und'])){
    $filelist = array();
    foreach ($case->field_attach_fda_pma_report['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o" aria-hidden="true"></i>', '/filerowremove/field_attach_fda_pma_report/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['attach_fda_pma_report_link']= array(
    '#markup' => '<label>Attach FDA PMA Report.</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $attach_fda_pma_report . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $attach_fda_pma_report . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign . '
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>
                </div>
                ',
  );

$elements['premarket_notification_process'] = array(
    '#type' => 'radios',
    '#title' => 'Is this equipment in the FDA 510K Premarket Notification process?',
    '#default_value' => (isset($case, $case->field_fda_premarket_notification['und'],$case->field_fda_premarket_notification['und'][0]['value']) && !empty($case->field_fda_premarket_notification['und'][0]['value'])?$case->field_fda_premarket_notification['und'][0]['value']:0),
    '#options' => $active,
        
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">
                        <i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>      '</div>
                    </div>
                    <div class="clearfix text-right open-payments-window"><a href="https://www.accessdata.fda.gov/scripts/cdrh/cfdocs/cfPMN/pmn.cfm" onclick="window.open(\'https://www.accessdata.fda.gov/scripts/cdrh/cfdocs/cfPMN/pmn.cfm\', \'newwindow\', \'width=600,height=400\'); return false;">510K Premarket Notification Database Search</a></div>
                 ',
  );
  $attach_fda_510k_report = 'attach_fda_510k_report';
  $elements['attach_fda_510k_report']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $attach_fda_510k_report . '][]',
    '#upload_location' => 'public://',
    //'#multiple' => TRUE,
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$attach_fda_510k_report . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$attach_fda_510k_report . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#prefix' => '<div class="clearfix section-top-parent">
                    <div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $previousfilelist = '';
  if(isset($case,$case->field_attach_fda_510k_report['und']) && !empty($case->field_attach_fda_510k_report['und'])){
    $filelist = array();
    foreach ($case->field_attach_fda_510k_report['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o" aria-hidden="true"></i>', '/filerowremove/field_attach_fda_510k_report/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }

  $elements['attach_fda_510k_report_link']= array(
    '#markup' => '<label>Is this in process/approved through the FDA 510K process?</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $attach_fda_510k_report . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $attach_fda_510k_report . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign . '
                      </div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>
                </div>
                </div></div></div>',
  );



  
   // Delete save and next section.
  $elements['left_section_delete'] = array(
    '#type'   => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/'.$form_state['case_delta']['refernid']), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
    '#prefix' => '<div class="clearfix margin-bottom-10 case-button-outer">',
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
        'callback' => 'due_diligence_save_case_submit_callback',
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
      'callback' => 'due_diligence_save_case_submit_callback',
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
        'callback' => 'due_diligence_save_case_submit_callback',
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type' => 'none'),
      ),
    '#attributes' => array('documentsave'=>$changeindocumentdata, 'class'=>array('btn', 'btn-primary','margin-0',$changeindocumentdata)),
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

function casemanager_due_diligence_left_form_validate($form, &$form_state) {
/*  if($_FILES['files']['name'] != '')  {
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

   // First handling files.
  
}

function casemanager_due_diligence_right_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i;
  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('due_diligence_project_manager_comments_process'),
  );
  return $form;
}

function due_diligence_project_manager_comments_process($elements, &$form_state) {
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
    $query2->condition('caser.bundle','due_diligence');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
  $case = node_load($nodenid);
  }
  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );
  $elements['project_manager_inner_menu'] = array(
   /* '#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><i class="pull-right fa fa-times case-collapse" aria-hidden="true" case-comment-status="close" style="cursor: pointer;"></i><div class="display-inline-block">Project Manager Comments </br><small>'.$form_state['case_delta']['refertitle'].'</small></div><div class="pull-right"><div class="dropdown open"> <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true"> Short <span class="caret"></span></button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel"><li><a href="javascript:void(0);">Coming soon</a></li><li><a href="javascript:void(0);">Resolved</a></li><li><a href="javascript:void(0);">Report</a></li></ul></div></div></div>', */
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
      'callback' => 'due_diligence_project_manager_comment_submit_callback',
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

function due_diligence_project_manager_comment_submit_callback($form,&$form_state) {
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


function due_diligence_change_scm_project_scp_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  if($form_state['triggering_element']['#name']=='get-scm_projects_scp') {
    if(!empty($triggeringElement['#value'])) {
      $_SESSION['scm_project_nid'] = $triggeringElement['#value'];
      $caserender = casemanager_due_diligence_outer();
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

function due_diligence_save_case_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array(); 
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
  $values = $form_state['values'];
  if (isset($values,$values['refercase_nid']) && !empty($values['refercase_nid'])) {
    if (isset($values,$values['case_nid']) && !empty($values['case_nid'])) {
      $case = node_load($values['case_nid']);
    }
    else {
      $case = _node_creation_call('due_diligence',$values['refercase_title']);
    }
    $case->field_project_reference['und'][0]['nid'] = $_SESSION['scm_project_nid']; 
    $case->field_case_reference['und'][0]['nid'] = $values['refercase_nid']; 
    $case->field_due_diligence_subtitle['und'][0]['value'] = $values['due_diligence_subtitle']; 
    $case->field_one_supplier['und'][0]['value'] = $values['one_supplier'];
    $case->field_thr_one_supplier['und'][0]['value'] = $values['thr_one_supplier'];   

    $case->field_does_every_entity_useit['und'][0]['value'] = $values['does_every_entity_useit'];
    $case->field_does_everyentity_useit_des['und'][0]['value'] = $values['does_every_entity_useit_decribe'];
    if (isset($values['supplier']) & !empty($values['supplier'])) {
      $case->field_vendor_name='';
      $case->field_supplier_info_first_name='';
      $case->field_due_last_name='';
      $case->field_supplier_email_address='';
      $suppliercount = 0;
      foreach($values['supplier'] as $skey =>$svalue){
        if(isset($svalue['vendor_name']) && !empty($svalue['vendor_name'])){  
          $case->field_vendor_name['und'][$suppliercount]['value'] = $svalue['vendor_name'];     
          /*$case->field_supplier_info_first_name['und'][$suppliercount]['value'] = $svalue['vendor_firstname']; 
          $case->field_due_last_name['und'][$suppliercount]['value'] = $svalue['vendor_lastname']; 
          $case->field_supplier_email_address['und'][$suppliercount]['value'] = $svalue['vendor_email'];*/ 
          $suppliercount++;
        }
      }
    }
    $case->field_supplier_considering['und'][0]['value'] = $values['suppliers_considering']; 
    $case->field_fda_approval['und'][0]['value'] = $values['equipment_requires_fda_approval']; 
    $case->field_fda_premarket_approval['und'][0]['value'] = $values['equipment_requires_fda_approval_process'];     
    $case->field_fda_premarket_notification['und'][0]['value'] = $values['premarket_notification_process'];    
    $case->field_fda_approved['und'][0]['value'] = $values['fda_approved']; 
    $case->field_anticipate_approval['und'][0]['value'] = $values['anticipate_approval']; 
    $case->field_terminate_case['und'][0]['value'] = $values['terminate_case']; 

    if ($values['terminate_case'] == 2) {
      $case->field_associated_fda_approval['und'][0]['value'] = ''; 
    }
    else {
      $case->field_associated_fda_approval['und'][0]['value'] = $values['decribe_fda_approval'];
    }

    $case->field_anticipated_approval_date['und'][0]['value'] = $values['anticipated_approval_date'];

    if (!isset($case->field_market_share['und'])) {
      $case->field_market_share['und'] = array();
    }
    foreach ($form_state['values']['supporting_documentation'] as $imgkey1 => $file1) {      
      $new_file1 = file_load($file1->fid);
      $file_arr1 = (array)$new_file1;
      $file_arr1['display'] = 1;        
      $case->field_market_share['und'][] = $file_arr1;
      drup_msg($file_arr1);
    }
    if(!isset($case->field_attach_fda_pma_report['und'])){
      $case->field_attach_fda_pma_report['und'] = array();
    }   
    foreach ($form_state['values']['attach_fda_pma_report'] as $imgkey2 => $file2) {      
      $new_file2 = file_load($file2->fid);
      $file_arr2 = (array)$new_file2;
      $file_arr2['display'] = 1;         
      $case->field_attach_fda_pma_report['und'][] = $file_arr2;
    }
    if(!isset($case->field_attach_fda_510k_report['und'])){
      $case->field_attach_fda_510k_report['und'] = array();
    }
    foreach ($form_state['values']['attach_fda_510k_report'] as $imgkey3 => $file3) {      
      $new_file3 = file_load($file3->fid);
      $file_arr3 = (array)$new_file3;
      $file_arr3['display'] = 1;          
      $case->field_attach_fda_510k_report['und'][] = $file_arr3;
    }
    node_save($case);
  }

  switch ($form_state['triggering_element']['#name']) {
    case 'save_submit':
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/due-diligence');
      break;

    case 'save_next_submit':
      // Redirecting user to next tab.
      $commands[] = ctools_ajax_command_redirect('/scm/payback');
      break;

    case 'save_duplicate_submit':
      // Case duplicate
      _case_manager_case_duplicate($values['refercase_nid']);
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/due-diligence');
      break;
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function suppliers_considering_count_children_process($elements, &$form_state) {
  $elements['#storage'] = $form_state['supplier_count'];  
  $supplier_default_values = $form_state['supplier_default_values'];
  foreach ($form_state['supplier_count'] as $key => $uniqid) { 
    $elements['vendor_name'][$uniqid] = array(
      '#type' => 'textfield',
      '#attributes'=> array('placeholder'=> "Vendor Name"),
      '#autocomplete_path' => 'scmvander-company/autocomplete',
      '#default_value' => !empty($supplier_default_values[$uniqid]['vendor_name']) ? $supplier_default_values[$uniqid]['vendor_name'] : '',
      '#ajax' => array(
        'callback' => 'scmvander_autocomplete_callback',
        'event' => 'blur',
        'wrapper' => 'are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
        'method' => 'replace',
        'effect' => 'fade',
      ),
      '#submit' => 'scmvander_autocomplete_callback_submit',
      '#prefix' => '<div class="clearfix">
                    <div class="duediligence-vendor-details tristate-toggle-button pull-right">
                      <div class="row margin-5">
                        <div class="col-md-12 padding-5 margin-bottom-4">',
    '#suffix' =>        '</div></div>
                </div>
              </div>',
    '#parents' => array('supplier', $uniqid, 'vendor_name'),
    );
 /* $elements['vendor_firstname'][$uniqid] = array(
      '#type' => 'textfield',
      '#default_value' => !empty($supplier_default_values[$uniqid]['first_name']) ? $supplier_default_values[$uniqid]['first_name'] : '',
      '#attributes'=> array('class'=>array($form_state['case_delta']['refernid'].'_vendor_firstname'),'placeholder'=> "First Name"),
      '#disabled' => TRUE,
      '#prefix' => '<div class="col-md-6 padding-5 margin-bottom-4">',
      '#suffix' => '</div>',
    '#parents' => array('supplier', $uniqid, 'vendor_firstname'),
    );
  $elements['vendor_lastname'][$uniqid] = array(
      '#type' => 'textfield',      
      '#default_value' => !empty($supplier_default_values[$uniqid]['last_name']) ? $supplier_default_values[$uniqid]['last_name'] : '',
      '#attributes'=> array('class'=>array($form_state['case_delta']['refernid'].'_vendor_lastname'),'placeholder'=> "Last Name"),
      '#disabled' => TRUE,
      '#prefix' => '<div class="col-md-6 padding-5 margin-bottom-4">',
      '#suffix' =>    '</div>',
    '#parents' => array('supplier', $uniqid, 'vendor_lastname'),
    );*/
/*  $elements['vendor_email'][$uniqid] = array(
      '#type' => 'textfield',      
      '#default_value' => !empty($supplier_default_values[$uniqid]['vendor_email']) ? $supplier_default_values[$uniqid]['vendor_email'] : '',
      '#attributes'=> array('class'=>array($form_state['case_delta']['refernid'].'_vendor_email'),'placeholder'=> "Email Address"),
      '#disabled' => TRUE,
     '#prefix' => '<div class="col-md-12 padding-5">',
    '#suffix' =>  '</div>
                  
        
          
            ',
    '#parents' => array('supplier', $uniqid, 'vendor_email'),
    );*/
    $elements['remove'][$uniqid] = array(
      '#type' => 'submit',
      '#value' => 'remove_vendor',
      '#name' => 'remove' . $uniqid,
      '#attributes'=> array('class'=>array('remove-vendor-row', 'workflow-remove-submit','hidden')),
      '#parents' => array('supplier', $uniqid, 'remove'),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_supplier_count_submit_handler'),
      '#ajax' => array(
        'callback' => 'remove_supplier_count_row_callback',
        'wrapper' => 'are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
      '#parents' => array('supplier', $uniqid, 'remove'),
      '#prefix' => '<div class="clearfix"><div class="pull-left tristate-icon"> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div><div class="pull-left">'.l('Delete','javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('remove-vendor-row-link')))),
      '#suffix' => '</div><div class="pull-right">
          '.l('+Invite New Vendor','add-scm-vendor/duediligence/nojs',array('html' => TRUE, 'attributes' => array('class' => array('add-project', 'ctools-use-modal', 'ctools-modal-assign-dashboard-popup-style')))).'
          </div>
        </div>',
    );
  }
  // Adding a add new button for the above section.
  $elements['supplier_count_add_new_row'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    '#name' => 'supplier_count_add_new_row',
    '#attributes'=> array('class'=>array('supplier-count-add-new-row-button'),'title'=>'Add New Physician'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('supplier_count_add_new_row_submit'),
    '#ajax' => array(
      'callback' => 'supplier_count_add_new_row_callback',
      'wrapper' => 'are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10" style="display:none;">',
    '#suffix' => '</div>',
  );

  return $elements;
}


function supplier_count_add_new_row_submit($form, &$form_state) {
  // We only add a new row, if there is no blank row.
  $supplier_count = $form_state['supplier_count'];
  $last_sc = end($supplier_count);

  if (!empty($form_state['input']['supplier'][$last_sc]['vendor_name'])) {
    $form_state['supplier_count'][] = uniqid();
  }

  $form_state['get_node_count'] = FALSE;
  $form_state['rebuild'] = TRUE;
}


function supplier_count_add_new_row_callback($form, &$form_state) {
  return $form['left_case_section']['suppliers_considering_count'];
}

function theme_suppliers_considering_count_children_theme($variables) {
  $element = $variables['form'];
  $storage = $element['#storage'];
  $output = '';
  foreach ($storage as $key => $uniqid) { 
    $output .= drupal_render($element['vendor_name'][$uniqid]);
    /*$output .= drupal_render($element['vendor_firstname'][$uniqid]);
    $output .= drupal_render($element['vendor_lastname'][$uniqid]);
    $output .= drupal_render($element['vendor_email'][$uniqid]);*/
    $output .= drupal_render($element['remove'][$uniqid]);
  }
  $output .= drupal_render_children($element);
  return $output;
}


function remove_supplier_count_row_callback($form, &$form_state) {  
  return $form['left_case_section']['suppliers_considering_count'];
}

function remove_supplier_count_submit_handler($form, &$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];
  if(isset($form_state['supplier_count'])){
    foreach ($form_state['supplier_count'] as $key => $value) {
      if($form_state['supplier_count'][$key] == $identifier && array_key_exists($identifier, $form_state['supplier_default_values'])){    
        unset($form_state['supplier_count'][$key]);
        unset($form_state['supplier_default_values'][$identifier]);   
      } 
    }
    $form_state['get_node_count'] = FALSE;
  }
  $form_state['rebuild'] = TRUE;
}


/**
 * Menu callback for add-scm-vendor/%/nojs.
 */
function add_scm_vendor($type = 'duediligence', $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Invite Vendors');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
      'vendor_type' => $type,
    );
    $output = ctools_modal_form_wrapper('add_scm_vendor_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('add_scm_vendor_form');
  }
}

/**
 * Form for adding minority vendor.
 */
function add_scm_vendor_form($form, &$form_state) {
  $options = _get_company_names();
  $form['error_set'] = array(
    '#markup' => '<div id="vendor_page_error"></div>',
  );
  
  $form['company'] = array(
    '#type' => 'select',
    '#title' => t('Vendor Name'),
    '#options' => $options,
    '#select2' => array(
      // 'width' => '300',
      'placeholder' => 'Type names to filter...',
      'allowClear'   => TRUE,
      'minimumResultsForSearch' => '5',
    ),
    '#attributes' => array('class' => array('margin-bottom-10')),
    //'#required' => TRUE,
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div><br><div><strong>OR</strong></div>',
  );
  $form['invite_to_m6'] = array(
    '#type' => 'textarea',
    '#title' => 'Invite to M6 by E-mail',
    '#attributes' => array('class'=> array('form-control invite_to_m6')),
    '#prefix' => '<div class="clearfix form-item invite-m6">',  
    '#element_validate' => array('vendor_multiple_email_validate'),
    '#suffix' => '</div>',
    '#description' => t('Seperate multiple emails by comma(,).'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Vendor'),
    '#attributes' => array('class' => array('margin-bottom-10')),
    '#prefix' => '<div class="clearfix">',
  );
  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div></div>',
  );

  return $form;
}

/**
 * Submit handler for the form add_scm_vendor_form.
 */
function add_scm_vendor_form_submit($form, &$form_state) { dpm($form_state) ;
  global $user, $base_url, $company;
  $account = user_load($user->uid);

  $vmname = _get_user_full_name($account->uid, $account);
  $vendor_type = !empty($form_state['vendor_type']) ? $form_state['vendor_type'] : '';
  $vnid = $form_state['values']['company'];
  $inviteToM6 = $form_state['values']['invite_to_m6'];
  if ($vnid == 0 && $inviteToM6 != '') {
    // If user wants to invite by Email.
    $getEmails = $form_state['values']['invite_to_m6'];
    $getEmails = explode(',', $getEmails);
    if (!empty($getEmails)) {
      foreach ($getEmails as $getEmail) {
        

        
          $query_data = array(
            'vendor_nid' => $company->nid,
            'vendor_uid' => $account->uid,
          );
          // $plain_url = $_plain_url . '?' . http_build_query($query_data);
          $link = url('user/register', array('query' => $query_data, 'absolute' => TRUE,));
          $click_link = t('<a href="@link">'.$link.'</a>', array('@link' => $link,));
          

          $message = 'Hello,<br/>';
          $message .= $company->title . ' has invited you to join M6Connect as a Supply Chain Vendor. To join, please click on the link below.<br/><br/>';          
          $message .= $click_link . '<br/><br/>';
          $message .= 'Team,<br/>M6Connect';

          

          $params = array(
            'subject' => 'Invitation to join as SCM Vendor - M6connect',
            'body' => $message,
            'sender' => $account->mail,
            'language' => language_default(),
            'module' => 'm6connect_misc',
            'key' => 'scmduediligence_mail___invite_2_m6_notify',
            'build' => TRUE,
          );

          if($getemailbyuser = user_load_by_mail($getEmail)){
            if (db_table_exists('m6connect_notification') && $user->uid !=$getemailbyuser->uid ) {
              $m6connect_notification = array(
                'type'         => 'scm',
                'event'        => 'invitevendor',
                'entity_id'    => 0 ,
                'company_nid'  => $company->nid,
                'message'      => NULL,
                'request_from' => $user->uid,
                'request_to'   => $getemailbyuser->uid,
                'status'       => 1,
                'timestamp'    => time(),
              );
              entity_save('m6connect_notification', (object) $m6connect_notification);
            }
          }

          // Sending mail
          
      }
      

      $dmail =drupal_mail($params['module'], $params['key'], implode(', ', $getEmails), $params['language'], $params);
      


    }

    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  elseif($vnid != 0 && $inviteToM6 == '') {
    if($getcadmin = _get_company_users_by_og_roles($vnid,'Company Admin')){
      if(!empty($getcadmin)){
         foreach ($getcadmin as $getcuid) {
          
          $getcuser = user_load($getcuid);
        $getEmail =  $getcuser->mail;
          $query_data = array(
            'vendor_nid' => $company->nid,
            'vendor_uid' => $account->uid,
          );
          // $plain_url = $_plain_url . '?' . http_build_query($query_data);
          $link = url('user/register', array('query' => $query_data, 'absolute' => TRUE,));
          $click_link = t('<a href="@link">'.$link.'</a>', array('@link' => $link,));
          

          $message = 'Hello,<br/>';
          $message .= $company->title . ' has invited you to join M6Connect as a Supply Chain Vendor. To join, please click on the link below.<br/><br/>';          
          $message .= $click_link . '<br/><br/>';
          $message .= 'Team,<br/>M6Connect';
          

          $params = array(
            'subject' => 'Invitation to join as SCM Vendor - M6connect',
            'body' => $message,
            'sender' => $account->mail,
            'language' => language_default(),
            'module' => 'm6connect_misc',
            'key' => 'scmduediligence_mail___invite_2_m6_notify',
            'build' => TRUE,
          );

          // Sending mail
          if (db_table_exists('m6connect_notification') && $user->uid !=$getcuid ) {
            $m6connect_notification = array(
              'type'         => 'scm',
              'event'        => 'invitevendor',
              'entity_id'    => 0 ,
              'company_nid'  => $company->nid,
              'message'      => NULL,
              'request_from' => $user->uid,
              'request_to'   => $getcuid,
              'status'       => 1,
              'timestamp'    => time(),
            );
            entity_save('m6connect_notification', (object) $m6connect_notification);
          }
          $dmail =drupal_mail($params['module'], $params['key'], $getEmail, $params['language'], $params);
       
      }
      }
    }
    
    
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }elseif ($vnid == 0 && $inviteToM6 == ''||$vnid != 0 && $inviteToM6 != '') {
    // Else showing error!
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_page_error", '<div class="messages--error messages error"><h2 class="element-invisible">Error message</h2>Please fill either Company or Email field!</div>');
  }
  
}