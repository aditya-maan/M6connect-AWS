<?php
function scm_my_casemanager_content() {
  global $user,$company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  $query = db_select('m6connect_scm_casemanager_label_management','cmlm');
  $query->fields('cmlm',array('value'));
  //$query->condition('cmlm.uid',$user->uid);
  $query->condition('cmlm.nid',$company->nid);
  $caselabel = $query->execute()->fetchColumn(0); 

  $_SESSION['scm_label_object'] = ''; 
  $_SESSION['scm_label_object'] = (isset($caselabel) && !empty($caselabel)?unserialize($caselabel):'');

  $elements['scm-casebuilder-outer-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_case_builder_form')),
    '#prefix' => '<div class="clearfix main-scm-casebuilder-menu changein-casemanager-popup">',
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
  $elements['scm-casebuilder-outer']= array(
    '#markup' => drupal_render(casemanager_builder_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements; 
}


/**
 * Menu item for scm/preferences.
 */
function scm_preferences_content() {
  global $user, $company;

  // Adding Preferences JS file.
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  $elements['scm-preferences-outer-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_case_builder_form')),
    '#prefix' => '<div class="clearfix main-scm-casebuilder-menu">',
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
  $elements['scm-preferences-outer']= array(
    '#markup' => drupal_render(preferences_builder_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements;
}

/**
 * Menu callback for scm/resources.
 */
function scm_resources_content() {
  global $user, $company;
  // Adding Preferences JS file.
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  $elements['scm-resources-outer-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_case_builder_form')),
    '#prefix' => '<div class="clearfix main-scm-casebuilder-menu">',
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
  $elements['scm-resources-outer']= array(
    '#markup' => drupal_render(resources_builder_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements;
}

/**
 * Menu callback for scm/payback.
 */
function scm_payback_content() {
  // return 'Under construction..';
  global $user, $company;

  // Adding Preferences JS file.
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  $elements['scm-resources-outer-menu']= array(
    '#markup' => drupal_render(drupal_get_form('casemanager_case_builder_form')),
    '#prefix' => '<div class="clearfix main-scm-casebuilder-menu">',
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
  $elements['scm-resources-outer']= array(
    '#markup' => drupal_render(payback_builder_outer()),
    '#prefix' => '<div class="case-expand-widthupper" style="overflow: auto;"><div class="case-expand-itemupper" style="height:10px;"></div></div><div id="main-scm-casebuilder-outer" class="case-expand-width">',
    '#suffix' => '</div>',
  );
  return $elements;
}

function casemanager_builder_outer() {
  global $user, $company;  
  $defaultProjectNid = (isset($_SESSION['scm_project_nid']) && !empty($_SESSION['scm_project_nid'])?$_SESSION['scm_project_nid']:'');
  
  if(isset($defaultProjectNid) && !empty($defaultProjectNid)){
    $casenid = _get_scmcase_nids_by_referpronid($defaultProjectNid);
    $casecount = count($casenid);
    $caseswidth = ($casecount * 400) + 10;
    $elements['scm-casebuilder-start']= array(
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
      $caseStatusCls = 'blur-cases';
    }
    }
      $casedelta = array('sr'=>$casesr,'nid'=>$nid);
      $elements['case_section_' . $nid] = array(
        '#type' => 'container',
        '#attributes' => array('class'=> array('changein-document-popup','caseouter','case_'.$casesr,'case-continer-'.$nid, $caseStatusCls) ,'original-pos'=>'case_'.$casesr,'updated-pos'=>''),
      );
      $elements['case_section_' . $nid]['scm-casebuilder-left']= array(
        '#markup' => drupal_render(drupal_get_form('casemanager_case_builder_left_form',$casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );

  //if($casesr != 1){
    $dispaly_none = 'dispaly_none';
  //}
      $elements['case_section_' . $nid]['scm-casebuilder-right']= array(
        '#markup' => drupal_render(drupal_get_form('casemanager_case_builder_right_form',$casedelta)),
        '#prefix' => '<div class="'.$commentsclass.' col-md-8 padding-10 margin-bottom-10 casebuilder-details-right '.$dispaly_none.'"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    }
  
    $elements['scm-casebuilder-end']= array(
      '#markup' => '</div>',
    );
  }
  return $elements; 
}

function casemanager_case_builder_form($form, &$form_state) {
 // $getReqNodes = _getting_table_data_call('project_management');
   $getReqNodes = _getting_table_subcat_title('project_management');
  
  $form['prgram-scm-menu-items'] = array(
    //'#markup' => scm_menu_links_content(),
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10 margin-top-10">',
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
    '#attributes' => array('class'=> array('form-control' , 'get-scm_projects_scp')),
    '#ajax' => array(
      'callback'=> 'change_scm_project_scp_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix"><div class="pull-right next-margin-0 changein-document-btn">',
    '#suffix' => '</div></div>',
  );
  $form['scm_casebuilder_case_name'] = array(
    '#title'=> 'Case Title',
    '#type' => 'textfield',
    '#required' => TRUE, 
    '#prefix' => '<div class="new-case-add" style="display:none"><div class="row margin-10"><div class="col-md-4">',
    '#suffix' => '</div></div>',
  );
  $getCaseType = _get_category_type_from_settings('case_type');
  $form['scm_casebuilder_case_type'] = array(
    '#title' => 'Case Type',
    '#type' => 'select',
    '#options' => $getCaseType,    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','request_casetype_new')),
    '#empty_option' => 'Select the case type',
	'#prefix' => '<div class="row margin-10"><div class="col-md-4">',
    '#suffix' => '</div></div>',
  );
  $form['scm_casebuilder_case_description'] = array(        
    '#type' => 'textarea',    
    '#title'=> 'Case Description',
    '#prefix' => '<div class="row margin-10"><div class="col-md-6">',
    '#suffix' => '</div></div>',
  );
 $form['submit'] = array(
  '#type' => 'submit',   
  '#value' => t('Save'),
  '#attributes' => array('class'=> array('margin-bottom-15')),
  '#ajax' => array(
      'callback' => 'casemanager_case_builder_form_submit_callback',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="case-builder-form-close"><input type="button" class="btn cancel-button" value="Cancel"></a>',
    '#suffix' => '</div>',
  );

  return $form;
}

function casemanager_case_builder_left_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i;
  $form['left_case_section'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container','clearfix','padding-10 ')),
    '#prefix' => '<div id="casebuilder-left-section" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('casebuilder_left_section_process'),
  );
  return $form;
}

function casemanager_case_builder_right_form($form, &$form_state,$i) {
  $form_state['case_delta'] = $i;
  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('project_manager_comments_process'),
  );
  return $form;
}



function casebuilder_left_section_process($elements, &$form_state){
  if(isset($form_state['case_delta'],$form_state['case_delta']['nid']) && !empty($form_state['case_delta']['nid']))
  $case = node_load($form_state['case_delta']['nid']);

  // Preparing project details.
  $project_no = 0;
  $project_type = 0;
  $project_cat = 0;
  $project_subcat = 0;
  if (!empty($_SESSION['scm_project_nid']) && $pnode = node_load($_SESSION['scm_project_nid'])) {
    // Project Number.
    if (!empty($pnode->field_project_mgmt_number[LANGUAGE_NONE][0]['value'])) {
      $project_no = $pnode->field_project_mgmt_number[LANGUAGE_NONE][0]['value'];
    }

    // Project Type.
    if (!empty($pnode->field_scm_project_project_type[LANGUAGE_NONE][0]['value'])) {
      $project_types = _get_scm_setting_data('project_type');
      if (!empty($project_types[$pnode->field_scm_project_project_type[LANGUAGE_NONE][0]['value']])) {
        $project_type = $project_types[$pnode->field_scm_project_project_type[LANGUAGE_NONE][0]['value']];
      }
    }

    // Project Category.
    if (!empty($pnode->field_scm_project_category[LANGUAGE_NONE][0]['value'])) {
      $project_cat = _get_scm_setting_data('project_settings_category', $pnode->field_scm_project_category[LANGUAGE_NONE][0]['value'])->title;
    }

    // Project Sub Category.
    if (!empty($pnode->field_scm_project_subcategory[LANGUAGE_NONE][0]['value'])) {
      $subcat = $pnode->field_scm_project_subcategory[LANGUAGE_NONE][0]['value'];
      /*$subcat_exp = explode('-', $subcat);
      $project_subcat = _get_scm_setting_data('project_settings_category', $subcat_exp[1])->title;*/
      $subcat_exp1 = explode('|', $subcat);
      $project_subcat1 = array();
      foreach($subcat_exp1 as $key=>$value){
        $subcat_exp = explode('-', $value);
        $project_subcat1[] = _get_scm_setting_data('project_settings_category', $subcat_exp[1])->title;
      }
      $project_subcat = implode(',', $project_subcat1);
    }
  }

  $pdetails = array($project_type,$project_subcat,date("Y"));
  $pdetails = array_filter($pdetails);
  $project_details = implode(' - ', $pdetails);
  $project_details_trimmed = $project_details;
  if (strlen($project_details) > 29) {
    $project_details_trimmed = substr($project_details, 0, 29) . '...';
  }

  $casetitle = (strlen($case->title) > 26) ? substr($case->title, 0, 23) . '...' : $case->title;
  $changeindocument = 'changein-document';
  
  $changeindocumentdata = (isset($case, $case->nid) && !empty($case->nid)?'document-save-'.$case->nid:'document-save-new');

  $caseStatusBtn = '<input id="case-toogle-check-cust" class="case-status-check" type="checkbox" checked data-toggle="toggle" data-on="Active" data-off="Inactive" data-onstyle="success" data-offstyle="danger" for="'.$case->nid.'">';

  $elements['case_progress_by_section_title'] = array(
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title margin-top-10 relative"><div class="fixed-case-title">Case ' . $form_state['case_delta']['sr'] . ': ' . $casetitle . '</div>
    <span class="pull-left" title="' . $project_details . '">' . $project_details_trimmed . '</span>
    <div class="pull-right toggle-case-status-check case-builder-case-title changein-document-btn">' . $caseStatusBtn . '<i class="fa fa-comments-o case-expand" aria-hidden="true" case-status="close" style="cursor: pointer;"></i></div></div>',
  );

  $caseDefaultVal = (isset($case, $case->field_case_status['und'],$case->field_case_status['und'][0]['value']) && ($case->field_case_status['und'][0]['value'] == 'active')?'active':'deactive');
  
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
   '#default_value' => $caseDefaultVal,
     '#attributes' => array('class'=> array('case-category-radio','form-inline','custom-form-inline-radio')),
     '#prefix' => '<div class="clearfix margin-bottom-10 spread-options-custom case-radio-'.$case->nid.'" style="display:none;">', 
     '#suffix' => '</div>',
  );
  $elements['case_progress_by_section'] = array(
    '#markup' => case_progress_by_section_container($case),
  );
 /* $elements['case_status_section'] = array(
    '#markup' => case_status_container(),   
  );*/


  $casetextareaedit = '<i class="pull-right fa fa-pencil casetextareaedit" aria-hidden="true" style="cursor: pointer;"></i>';
  $textarea1 = (isset($case, $case->field_case_builder_description['und'],$case->field_case_builder_description['und'][0]['value']) && !empty($case->field_case_builder_description['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue1 = (isset($case, $case->field_case_builder_description['und'],$case->field_case_builder_description['und'][0]['value']) && !empty($case->field_case_builder_description['und'][0]['value'])?$case->field_case_builder_description['und'][0]['value'].$casetextareaedit:'');


  $elements['case_description'] = array(        
    '#type' => 'textarea',
    '#default_value' => (isset($case, $case->field_case_builder_description,$case->field_case_builder_description['und'][0]['value']) && !empty($case->field_case_builder_description['und'][0]['value'])?$case->field_case_builder_description['und'][0]['value']:''),
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">'.(isset($_SESSION['scm_label_object']['case_builder'])&& !empty($_SESSION['scm_label_object']['case_builder']['description'])?$_SESSION['scm_label_object']['case_builder']['description']:'Description').'</div><div class="hastextareavalue">'.$textareavalue1.'</div><div class="hastextarea '.$textarea1.'">',
    '#suffix' => '</div></div>',
  );

  $textarea2 = (isset($case, $case->field_casebuilder_closeoutremark['und'],$case->field_casebuilder_closeoutremark['und'][0]['value']) && !empty($case->field_casebuilder_closeoutremark['und'][0]['value'])?'dispaly_none':'');
  
  $textareavalue2 = (isset($case, $case->field_casebuilder_closeoutremark['und'],$case->field_casebuilder_closeoutremark['und'][0]['value']) && !empty($case->field_casebuilder_closeoutremark['und'][0]['value'])?$case->field_casebuilder_closeoutremark['und'][0]['value'].$casetextareaedit:'');

  $elements['case_closeout_remarks'] = array(        
    '#type' => 'textarea',
    '#default_value' => (isset($case, $case->field_casebuilder_closeoutremark, $case->field_casebuilder_closeoutremark['und'][0]['value']) && !empty($case->field_casebuilder_closeoutremark['und'][0]['value'])?$case->field_casebuilder_closeoutremark['und'][0]['value']:''),
    '#prefix' => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">'.(isset($_SESSION['scm_label_object']['case_builder'])&& !empty($_SESSION['scm_label_object']['case_builder']['remarks'])?$_SESSION['scm_label_object']['case_builder']['remarks']:'Case Closeout Remarks').'</div><div class="hastextareavalue">'.$textareavalue2.'</div><div class="hastextarea '.$textarea2.'">',
    '#suffix' => '</div></div>',
  );


  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => $form_state['case_delta']['nid'],
  );
  $elements['left_section_delete'] = array(
    '#type' => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/'.$form_state['case_delta']['nid']), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
    '#prefix' => '<div class="clearfix margin-bottom-10 case-button-outer">',   
  );
  $elements['left_section_cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit">',    
  );
  $elements['left_section_save_and_next'] = array(
    '#type' => 'button',
    '#title' => 'left_section',
    '#value' => t('Save and Next'),
    '#ajax' => array(
        'callback' => 'case_build_save_and_next_submit_callback',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    '#attributes' => array('class'=>array('save-next-case-button')),
    '#prefix' => '<div class="clearfix" style="display:none">',
    '#suffix' => '</div>',
   );
  $elements['left_section_save_and_addnew_case'] = array(
    '#type' => 'button',
    '#title' => 'left_section',
    '#value' => t('Save and Add New Case'),
    '#ajax' => array(
        'callback' => 'case_build_save_and_addnew_case_submit_callback',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    '#attributes' => array('class'=>array('save-addnew-case-button')),
    '#prefix' => '<div class="clearfix" style="display:none">',
    '#suffix' => '</div>',
   );
  $elements['left_section_save_and_duplicate_case'] = array(
    '#type' => 'button',
    '#title' => 'left_section',
    '#value' => t('Save and Duplicate Case'),
    '#ajax' => array(
        'callback' => 'case_build_save_and_duplicate_case_submit_callback',
        'method' => 'replace',
        'effect' => 'fade',
      ),
    '#attributes' => array('class'=>array('save-duplicate-case-button')),
    '#prefix' => '<div class="clearfix" style="display:none">',
    '#suffix' => '</div>',
   );

  /*$elements['case_action_button'] = array(
    '#markup' => '<div class="btn-group">                    
                    <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> 
                      Save &nbsp;
                      <span class="caret"></span>                     
                    </button> 
                    <ul class="dropdown-menu dropdown-menu-right">
                    
                      <li><a href="javascript:void(0);" class="save-next-case">Save and Next</a></li>
                      <li><a href="javascript:void(0);" class="save-addnew-case">Save and Add New Case</a></li>
                      <li><a href="javascript:void(0);" class="save-duplicate-case">Save and Duplicate Case</a></li>                      
                    </ul>
                  </div></div>',
  );*/
  $elements['left_section_save'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#value'      => t('Save'),
    '#ajax'       => array(
        'callback' => 'case_build_save_case_submit_callback',
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type' => 'none'),
      ),
    '#attributes' => array('documentsave'=>$changeindocumentdata,'class'=>array('btn', 'btn-primary','margin-0',$changeindocumentdata)),
    //'#prefix'     => '<div class="clearfix" style="display:none">',
    //'#suffix'     => '</div>',
    '#prefix'     => '<div class="btn-group">',
    '#suffix'     => '<button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                      <span class="caret"></span>
                      <span class="sr-only">Toggle Dropdown</span>
                    </button>
                    <ul class="dropdown-menu">
                      <li><a href="javascript:void(0);" class="save-next-case">Save and Next</a></li>
                      <li><a href="javascript:void(0);" class="save-addnew-case">Save and Add New Case</a></li>
                      <li><a href="javascript:void(0);" class="save-duplicate-case">Save and Duplicate Case</a></li>
                    </ul>
                  </div>
                </div>',
  );
  
  return $elements;
}

function case_progress_by_section_container($node = NULL) {
  if (empty($node) || empty($node->nid)) {
    return '';
  }

  global $user, $company;
  $output = '';

  $deltatitle = array(
    'buy_or_change'  => 'Buy or Change',
    'patient_care'   => 'Patient Care',
    'preferences'    => 'Preferences',
    'resources'      => 'Resources',
    'due_diligence'  => 'Due Diligence',
    'pay_back'       => 'Pay Back',
    // 'case_selection' => 'Case Selection',
  );
  $deltaColor = array(
    'buy_or_change'  => '#0099ff',
    'patient_care'   => '#ff5a31',
    'preferences'    => '#996600',
    'resources'      => '#9933ff',
    'due_diligence'  => '#ff9122',
    'pay_back'       => '#5cb85c',
    // 'case_selection' => '#ffcc33',
  );

  // Getting delta values.
  $deltavalue = _get_delta_values_based_on_case($node);
  $case_per = array_sum($deltavalue) / count($deltavalue);

  $case_per = round($case_per, 0, PHP_ROUND_HALF_DOWN);
  $output .=  '<div class="clearfix margin-bottom-10">';
  $output .=    '<div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">
              ' . (isset($_SESSION['scm_label_object']['case_builder']) && !empty($_SESSION['scm_label_object']['case_builder']['progresstitle'])? $_SESSION['scm_label_object']['case_builder']['progresstitle'] : 'Case Progress by Section') . '
                </div>';
               
  foreach ($deltatitle as $key => $value) {
    $lowerper = '';
    if($deltavalue[$key] <=15){
      $lowerper = 'lowerper';
    }
    $output .=  '<div class="row margin-10 margin-bottom-10">
                  <div class="caseprogress-title col-md-5 padding-10">'.$value.'</div>
                  <div class="caseprogress-datacolor col-md-7 padding-10">
                    <div class="progress margin-0">
                      <div class="progress-bar" style="background:'.$deltaColor[$key].'; width:'.$deltavalue[$key].'%;" role="progressbar" aria-valuenow="45" aria-valuemin="0" aria-valuemax="100">
                        <span class="'.$lowerper.'">'.$deltavalue[$key].'%</span>
                      </div>
                    </div>
                  </div>
                </div>';
   
  }
  $lowerper1 = '';
  if($case_per <=15){
    $lowerper1 = 'lowerper';
  }  
  $output .=  '<div class="row margin-10 panel-body scm-casecomplete-outer">
                <div class="caseprogress-title col-md-5 padding-10">Case % Complete</div>
                <div class="caseprogress-datacolor col-md-7 padding-10">
                  <div class="progress margin-0">
                    <div class="progress-bar scm-casecomplete-color" style="width:' . $case_per . '%;" role="progressbar" aria-valuenow="45" aria-valuemin="0" aria-valuemax="100">
                      <span class="'.$lowerper1.'">' . $case_per . '%</span>
                    </div>
                  </div>
                </div>
              </div>';
  
  $output .= '</div>';
  return $output;
}

function case_status_container(){
  $output = '';
  $output .=  '<div class="clearfix margin-bottom-10">';
  $output .=    '<div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">'.(isset($_SESSION['scm_label_object']['case_builder'])&& !empty($_SESSION['scm_label_object']['case_builder']['status'])?$_SESSION['scm_label_object']['case_builder']['status']:'Case Status').'</div>';
  $output .=      '<div class="case-status-datils">';
  $output .=        '<div>Terminated by Infection Prevention</div>';                 
  $output .=      '</div>';
  $output .= '</div>';
  return $output;
}

function project_manager_comments_process($elements, &$form_state){
  if(isset($form_state['case_delta'],$form_state['case_delta']['nid']) && !empty($form_state['case_delta']['nid']))
  global $user,$company;
  $defaultProjectNid = '';
  $defaultProjectNid = $_SESSION['scm_project_nid'];
  $case = node_load($form_state['case_delta']['nid']);
  $elements['project_manager_inner_menu'] = array(
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><div class="display-inline-block">Project Manager Comments </br><small>' . $case->title . '</small></div></div>',
  );
  $getComment = _get_previous_comment_by_case($form_state['case_delta']['nid']);
  $elements['project_manager_title'] = array(
    '#markup' => '<div class="project-manager-comment-render-class" id="project-manager-comment-render-' . $form_state['case_delta']['nid'] . '">'.$getComment.'</div><div class="projectmanagetr-comment-list">',
  );
  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => $form_state['case_delta']['nid'],
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
      'callback' => 'project_manager_comment_submit_callback',
      'wrapper' => 'scm-sub-category-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $elements['project_manager_comments' . $i]['cancel'] = array(
      '#type' => 'markup',
      '#markup' => '<a href="javascript:void(0);" class="case-collapse" aria-hidden="true" case-comment-status="close"><input type="button" class="btn cancel-button" value="Close"></a>',
    );
  /*$elements['project_manager_comments' . $i]['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit">',    
  );*/
  $elements['markup_end'] = array(
    '#suffix' => '</div>',    
  );
  return $elements;
}


function project_manager_comment_submit_callback($form,&$form_state){ //pre($form_state['values'],1);
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  if($values['comment_edit'] == 0) {
    $Todaystrtotime = strtotime(date('l F d, Y',strtotime("today")));
    $Tomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+1 days")));
    $dayafterTomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+2 days")));
    if(isset($values,$form_state['triggering_element']['#name']) && !empty($values['comments']) && !empty($values['case_nid'])){
      $case = node_load($values['case_nid']);
    $case->field_case_unique_id['und'][] = array('value' => $values['unique_comment_id']);
    $case->field_case_comment['und'][] = array('value' => $values['comments']);
    $case->field_case_comment_date['und'][] = array('value' => $values['comments_date']);
    $case->field_case_resolved_value['und'][] = array('value' => $values['resolved']);
      $case->field_case_report_value['und'][] = array('value' => $values['report']);
    node_save($case);
  }
  }
  else {
    if(!empty($values['comments']) && !empty($values['case_nid'])){
      $case = node_load($values['case_nid']);
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
  $commands[] = ajax_command_html('#project-manager-comment-render-' . $values['case_nid'], _get_previous_comment_by_case($values['case_nid']));
  return array('#type' => 'ajax', '#commands' => $commands);
}

function casemanager_case_builder_form_submit_callback($form,&$form_state){
  global $user,$company;
  $commands = array();
  $values = $form_state['values']; 
  if(isset($values,$values['scm_casebuilder_case_name'],$values['get-scm_projects_scp']) && !empty($values['get-scm_projects_scp'])&& !empty($values['scm_casebuilder_case_name'])){
    $crateNode = _node_creation_call('case_builder',$values['scm_casebuilder_case_name']); 
    $crateNode->field_case_builder_description['und'][0]['value'] = $values['scm_casebuilder_case_description'];  
	$crateNode->field_case_type['und'][0]['value'] = $values['scm_casebuilder_case_type'];
    $crateNode->field_project_reference['und'][0]['nid'] = $values['get-scm_projects_scp']; 
    $activeCaseNid = _get_active_case_by_project($values['get-scm_projects_scp']);
    if(!empty($activeCaseNid)) {
      $getActiveCase = node_load($activeCaseNid); 
      $getActiveCase->field_case_status['und'][0]['value'] = '';
      field_attach_update('node', $getActiveCase);        
      node_save($getActiveCase);
     /* 
      * And save latest case in active status
      */
     $crateNode->field_case_status['und'][0]['value'] = 'active'; 
     node_save($crateNode);   
    } 
    else {
      $crateNode->field_case_status['und'][0]['value'] = 'active'; 
      node_save($crateNode);
    } 
    $commands[] = ctools_ajax_command_redirect('/scm/my-casemanager');
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_project_scp_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  if($form_state['triggering_element']['#name']=='get-scm_projects_scp') {
    if(!empty($triggeringElement['#value'])) {
      $_SESSION['scm_project_nid'] = $triggeringElement['#value'];
      $caserender = casemanager_builder_outer();
      $commands[] = ajax_command_replace("#main-scm-casebuilder-outer", '<div id="main-scm-casebuilder-outer">'.render($caserender).'</div>');
      $commands[] = ctools_ajax_command_redirect('/scm/my-casemanager');
    }
  else {
    unset($_SESSION['scm_project_nid']);
    $commands[] = ctools_ajax_command_redirect('/scm/my-casemanager');
  } 
  }
  $commands[] = ctools_ajax_command_redirect('/scm/my-casemanager');
  return array('#type' => 'ajax', '#commands' => $commands);
}

function case_build_save_case_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  
  if(isset($values,$values['case_nid']) && !empty($values['case_nid'])){
    $case = node_load($values['case_nid']);
    $case->field_case_builder_description['und'][0]['value'] = $values['case_description'];  
    $case->field_casebuilder_closeoutremark['und'][0]['value'] = $values['case_closeout_remarks'];  
    node_save($case);
    
    $commands[] = ctools_ajax_command_redirect('/scm/my-casemanager');
  }
  //drup_msg($values);
  //drupal_goto('/scm/buy-change');
   
  return array('#type' => 'ajax', '#commands' => $commands);
}

function case_build_save_and_next_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  
  if(isset($values,$values['case_nid']) && !empty($values['case_nid'])){
    $case = node_load($values['case_nid']);
    $case->field_case_builder_description['und'][0]['value'] = $values['case_description'];  
    $case->field_casebuilder_closeoutremark['und'][0]['value'] = $values['case_closeout_remarks'];  
    node_save($case);
    
    $commands[] = ctools_ajax_command_redirect('/scm/buy-change');
  }
  //drup_msg($values);
  //drupal_goto('/scm/buy-change');
   
  return array('#type' => 'ajax', '#commands' => $commands);
}

function case_build_save_and_addnew_case_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  if(isset($values,$values['case_nid']) && !empty($values['case_nid'])){
    $case = node_load($values['case_nid']);
    $case->field_case_builder_description['und'][0]['value'] = $values['case_description'];  
    $case->field_casebuilder_closeoutremark['und'][0]['value'] = $values['case_closeout_remarks'];  
    node_save($case);    
  $commands[] = ajax_command_css('.new-case-add', array('display' => 'block'));
    //$commands[] = ctools_ajax_command_redirect('/scm/buy-change');
  }
  
  return array('#type' => 'ajax', '#commands' => $commands);
}

function case_build_save_and_duplicate_case_submit_callback($form,&$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  if(isset($values,$values['case_nid']) && !empty($values['case_nid'])){
    $case = node_load($values['case_nid']);
    $case->field_case_builder_description['und'][0]['value'] = $values['case_description'];  
    $case->field_casebuilder_closeoutremark['und'][0]['value'] = $values['case_closeout_remarks'];  
    node_save($case);
    //case duplicate in all tab 
    _case_manager_case_duplicate($case->nid);
    $commands[] = ctools_ajax_command_redirect('/scm/my-casemanager');
  }  
  return array('#type' => 'ajax', '#commands' => $commands);
}


function case_manager_label_management_form($form,$form_state){
  global $user,$company;
  $query = db_select('m6connect_scm_casemanager_label_management','cmlm');
  $query->fields('cmlm',array('value'));
  //$query->condition('cmlm.uid',$user->uid);
  $query->condition('cmlm.nid',$company->nid);
  $deltavalue = $query->execute()->fetchColumn(0);  
  $delta = '';
  $delta = (isset($deltavalue) && !empty($deltavalue)?unserialize($deltavalue):'');
  $form['case_builder'] = array(
    '#type' => 'fieldset',
    '#title' => t('Case Builder'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $form['case_builder']['progresstitle'] = array(
    '#type' => 'textfield',
    '#default_value' => (isset($delta['case_builder'])&& !empty($delta['case_builder']['progresstitle'])?$delta['case_builder']['progresstitle']:'Case Progress by Section'),
   // '#title' => t('Label Title'),    
    '#parents' => array('case_builder','progresstitle'),
    '#prefix' => '<div class="row"><div class="col-md-4">',
    '#suffix' => '</div><div class="col-md-2"><div class="form-item">Markup</div></div></div>',
  );
  
  $form['case_builder']['status']= array(
    '#type' => 'textfield',
    '#default_value' => (isset($delta['case_builder'])&& !empty($delta['case_builder']['status'])?$delta['case_builder']['status']:'Case Status'),
    //'#title' => t('Status Label'),    
    '#parents' => array('case_builder','status'),
    '#prefix' => '<div class="row"><div class="col-md-4">',
    '#suffix' => '</div><div class="col-md-2"><div class="form-item">Markup</div></div></div>',
  );
  $form['case_builder']['description'] = array(
    '#type' => 'textfield',
    '#default_value' => (isset($delta['case_builder'])&& !empty($delta['case_builder']['description'])?$delta['case_builder']['description']:'Description'),
    //'#title' => t('Description label'),    
    '#parents' => array('case_builder','description'),
    '#prefix' => '<div class="row"><div class="col-md-4">',
    '#suffix' => '</div><div class="col-md-2"><div class="form-item">Textarea</div></div></div>',
  );
  $form['case_builder']['remarks'] = array(
    '#type' => 'textfield',
    '#default_value' => (isset($delta['case_builder'])&& !empty($delta['case_builder']['remarks'])?$delta['case_builder']['remarks']:'Case Closeout Remarks'),
   // '#title' => t('Remarks'),    
    '#parents' => array('case_builder','remarks'),
    '#prefix' => '<div class="row"><div class="col-md-4">',
    '#suffix' => '</div><div class="col-md-2"><div class="form-item">Textarea</div></div></div>',
  );
  $form['submit'] = array(
   '#type' => 'submit',
   '#value' => t('Save'),
   
  );

  return $form;
}

function case_manager_label_management_form_submit($form,&$form_state){
  global $user,$company;
  $values = $form_state['values'];
  if(isset($values) && !empty($values) && !empty($values['case_builder'])){
    $deltavalue =  array('case_builder'=>$values['case_builder']);
    db_merge('m6connect_scm_casemanager_label_management')
    ->key(array('uid' => $user->uid, 'nid' => $company->nid))
    ->fields(array(
      'uid' => $user->uid,
      'nid' => $company->nid,
      'type' => 'case_builder',
      'value' => serialize($deltavalue),
      'status' => 1,
      'timestamp' => time(),
    ))
    ->execute();
    drupal_set_message('Update Successfully');
  }

}

############ Preference section starts ###################
/**
 * Function to get content for preferences page.
 */
function preferences_builder_outer() {
  global $user, $company;
  $defaultProjectNid = isset($_SESSION['scm_project_nid']) && !empty($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '';
  if (!empty($defaultProjectNid)) {
    $casenid = _get_scmcase_nids_by_referpronid($defaultProjectNid);
    $casecount = count($casenid);
    $caseswidth = $casecount *400 + 10;
    $elements['scm-casebuilder-start']= array(
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
    foreach ($casenid as $key => $nid) {
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
    $elements['preference_section_' . $nid] = array(
        '#type' => 'container',
    '#attributes' => array('class'=> array('changein-document-popup','caseouter','case_'.$casesr, 'case-continer-'.$nid, $caseStatusCls) ,'original-pos'=>'case_'.$casesr,'updated-pos'=>''),
      );
      $elements['preference_section_' . $nid]['scm-preference-left'] = array(
        '#markup' => drupal_render(drupal_get_form('casemanager_preference_left_form', $casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left section-top-parent"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );

      $dispaly_none = 'dispaly_none';

      $elements['preference_section_' . $nid]['scm-preference-right'] = array(
        '#markup' => drupal_render(drupal_get_form('casemanager_preference_right_form', $casedelta)),
        '#prefix' => '<div class="' . $commentsclass . ' col-md-8 padding-10 margin-bottom-10 casebuilder-details-right ' . $dispaly_none . '"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    }  
    $elements['scm-casebuilder-end']= array(
      '#markup' => '</div>',
    );
  }
  return $elements; 
}

/**
 * Function to get left content of preference page.
 */
function casemanager_preference_left_form($form, &$form_state, $i) {
  $form_state['case_delta'] = $i;
  if (!isset($form_state['get_node_count'])) {
    $form_state['get_node_count'] = TRUE;
  }
  if (!isset($form_state['get_node_count2'])) {
    $form_state['get_node_count2'] = TRUE;
  }
  

  if(isset($i['refernid']) && !empty($i['refernid'])){
    $query2 = db_select('field_data_field_case_reference','caser');
    $query2->fields('caser',array('entity_id'));
    $query2->condition('caser.bundle','preferences');
    $query2->condition('caser.field_case_reference_nid',$i['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
    $caseload = node_load($nodenid);  

    if (!empty($caseload->field_select_subspecialty['und']) && $form_state['get_node_count'] != FALSE) {
      $form_state['clinicians_count'] = array();
      $form_state['clinicians_default_values'] = array();
      foreach ($caseload->field_select_subspecialty['und'] as $clkey => $clvalue) {
        $tempIdentifer = uniqid();
        $form_state['clinicians_default_values'][$tempIdentifer] = array(
          /*'fname_lname'   => $clvalue['value'],
          'primary_lname' => $caseload->field_preferences_last_name['und'][$clkey]['value'],
          'primary_email' => $caseload->field_nonphysicianclinicianemail['und'][$clkey]['value'],*/
          'subspecialty'  => $caseload->field_select_subspecialty['und'][$clkey]['value'],
        );
        
          $form_state['clinicians_count'][]  = $tempIdentifer;
        
      }
      $tempIdentifer = uniqid();
      $form_state['clinicians_count'][]  = $tempIdentifer;
      $form_state['get_node_count'] = FALSE;
    }

    if (!empty($caseload->field_physicians_fc[LANGUAGE_NONE]) && $form_state['get_node_count2'] != FALSE) {
      // If there is any previous data, then getting it.
      $form_state['physicians_count'] = array();
      $form_state['physicians_default_values'] = array();

      foreach ($caseload->field_physicians_fc[LANGUAGE_NONE] as $key => $value) {
        if (!empty($value['value'])) {
          // Increasing the count.
          $tempIdentifer = uniqid();
          $form_state['physicians_count'][]  = $tempIdentifer;

          // Loading Field collection item.
          $fc_item = field_collection_item_load($value['value']);
          if(!empty($fc_item->field_attachments[LANGUAGE_NONE])){
            foreach ($fc_item->field_attachments[LANGUAGE_NONE] as $fakey => $favalue) {
              $form_state['filedcollectonfilerow_remove'][$favalue['fid']] = $value['value'];
            }
          }
          $form_state['physicians_default_values'][$tempIdentifer] = array(
            'fname_lname'    => $fc_item->field_physicians_first_name[LANGUAGE_NONE][0]['value'],
            'primary_lname'  => $fc_item->field_physicians_last_name[LANGUAGE_NONE][0]['value'],
            'subspecialty'   => $fc_item->field_physicians_select_sub[LANGUAGE_NONE][0]['value'],
            'primary_email'  => $fc_item->field_physicians_email[LANGUAGE_NONE][0]['value'],
            'physicians_url' => $fc_item->field_physicians_url[LANGUAGE_NONE][0]['value'],
            'attachments'    => $fc_item->field_attachments[LANGUAGE_NONE],
          );
        }
      }

      $tempIdentifer = uniqid();
      $form_state['physicians_count'][]  = $tempIdentifer;
      $form_state['get_node_count2'] = FALSE;
    }
  }

  if (empty($form_state['clinicians_count'])) {
    $tempIdentifer = uniqid();
    $form_state['clinicians_count'][]  = $tempIdentifer;
  }
  if (empty($form_state['physicians_count'])) {
    $tempIdentifer = uniqid();
    $form_state['physicians_count'][] = $tempIdentifer;
  }
  
  $form['left_case_section'] = array(
    '#type'       => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container', 'clearfix', 'padding-10')),
    '#prefix'     => '<div id="preference-left-section" class="clearfix">',
    '#suffix'     => '</div>',
    '#process'    => array('preference_left_section_process'),
  );

  return $form;
}

function preference_left_section_process($elements, &$form_state) {
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
  
  if (isset($form_state['case_delta']['refernid']) && !empty($form_state['case_delta']['refernid'])) {
    $query2 = db_select('field_data_field_case_reference','caser');
    $query2->fields('caser',array('entity_id'));
    $query2->condition('caser.bundle','preferences');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
    $case = node_load($nodenid);
  }

  $hasecase = (isset($case, $case->nid) && !empty($case->nid) ? 'case-expand' : 'notcasefound');
  $changeindocument = 'changein-document';  
  $changeindocumentdata = (isset($case, $case->nid) && !empty($case->nid)?'document-save-'.$case->nid:'document-save-new');
  $notcasefound = (isset($case, $case->nid) && !empty($case->nid)?"":'data-trigger="hover" data-toggle="popover"  data-placement="bottom" data-content="Please Save First"');

  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );

  $form_state['case_delta']['case_nid'] = !empty($case->nid) ? $case->nid : '';
  
  $casetitle = (strlen($form_state['case_delta']['refertitle']) > 26) ? substr($form_state['case_delta']['refertitle'], 0, 23) . '...' : $form_state['case_delta']['refertitle'];
  $caseStatusBtn = '<input id="case-toogle-check-cust" class="case-status-check" type="checkbox" checked data-toggle="toggle" data-on="Active" data-off="Inactive" data-onstyle="success" data-offstyle="danger" for="'.$form_state['case_delta']['refernid'].'">';
  $elements['case_progress_by_section_title'] = array(
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title case-section-title-sp margin-top-10"><div class="pull-left fixed-case-title" title="'. $form_state['case_delta']['refertitle'] . '">Case ' . $form_state['case_delta']['sr'] . ': ' . $casetitle . '</div><div class="pull-right toggle-case-status-check changein-document-btn">'.$caseStatusBtn.'<i class="fa fa-comments-o '.$hasecase.'" aria-hidden="true" case-status="close" style="cursor: pointer;" '.$notcasefound.'></i></div></div>',
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
  $textarea_label = !empty($_SESSION['scm_label_object']['case_builder']['description']) ? $_SESSION['scm_label_object']['case_builder']['description'] : t('Description');

  $elements['case_description'] = array(
    '#type'   => 'markup',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">' . $textarea_label . '</div><div class="hastextareavalue">',
    '#markup' => $getCaseDesc,
    '#suffix' => '</div></div>',
  );

  $elements['case_nid'] = array(
    '#type'  => 'value',
    '#value' => $form_state['case_delta']['case_nid'],
  );

  // Preference exclusive fields.
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));

  // Non-Physician Clinicians
  $elements['are_clinicians_primary'] = array(
    '#type'          => 'radios',
    '#title'         => t('Are Clinicians the primary user group?'),
    '#default_value' => !empty($case->field_preferences_non_physician['und'][0]['value']) ? $case->field_preferences_non_physician['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('clinicians','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Non-Physician Clinicians</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $elements['are_clinicians_primary_children'] = array(
    '#type'    => 'container',
    '#process' => array('are_clinicians_primary_children_process'),
    '#theme'   => 'are_clinicians_primary_children_theme',
    '#prefix' => '<div id="are-clinicians-primary-children-edit-' . $form_state['case_delta']['refernid'] . '" class="conditionstate-one clinicians-container-here tristate-toggle-button pull-right">',
    '#suffix' => '</div>'
  );

  $elements['are_clinicians_primary_suffix'] = array(
    '#markup' => '</div>',
  );

  // Physicians
  $elements['are_physicians_primary'] = array(
    '#type'          => 'radios',
    '#title'         => t('Are Physicians the primary user group?'),
    '#default_value' => !empty($case->field_physicians['und'][0]['value']) ? $case->field_physicians['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('physicians','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="clearfix '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Physicians</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $elements['are_physicians_primary_children'] = array(
    '#type'    => 'container',
    '#process' => array('are_physicians_primary_children_process'),
    '#theme'   => 'are_physicians_primary_children_theme',
    '#prefix'  => '<div id="are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'] . '" class="conditionstate-one physicians-container-here tristate-toggle-button pull-right">',
    '#suffix'  => '</div>'
  );

  $elements['are_physicians_primary_suffix'] = array(
    '#markup' => '</div>',
  );

  $elements['is_this_for_a_new_physican'] = array(
    '#type'          => 'radios',
    '#title'         => t('Is this for a New Physician?'),
    '#default_value' => !empty($case->field_physicians_new_physician['und'][0]['value']) ? $case->field_physicians_new_physician['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('a_new_physican','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="'.$changeindocument.' clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $elements['is_the_physican_credentialed'] = array(
    '#type'          => 'radios',
    '#title'         => t('Is the physician(s) Credentialed?'),
    '#default_value' => !empty($case->field_physicians_credentialed['und'][0]['value']) ? $case->field_physicians_credentialed['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('physican_credentialed','conditional-element')),
    '#prefix'        => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right dont-make-it-green-on-red">',
    '#suffix'        => '</div></div>',
  );

  $elements['field_credentialed_documents']= array(
   '#type'            => 'file',
   '#title'           => 'Attachment',
   '#name'            => 'files[field_credentialed_documents][]',
   '#upload_location' => 'public://',
   
   '#attributes'      => array('multiple' => 'multiple','id' => 'scm-attachment-upload-field_credentialed_documents-' . $form_state['case_delta']['refernid'] . '-id', 'onchange' => 'javascript:updateListNew("scm-attachment-upload-field_credentialed_documents-' . $form_state['case_delta']['refernid'] .'")','class'=> array('scm-my-request-attachment','conditional-element')),
   '#description'     => t('Use CTRL + Click to choose multiple attachments.'),
   //'#attributes'    => array('multiple' => 'multiple','class'=> array('scm-my-request-attachment')),    
   '#prefix'          => '<div class="clearfix form-item" style="display:none;">',
   '#suffix'          => '</div>',
  );

  $previousfilelist = '';
  if (!empty($case->field_credentialed_documents['und'])) {
    $filelist = array();
    foreach ($case->field_credentialed_documents['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_credentialed_documents/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }

  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }

  $elements['approval_document_link_cre']= array(
    '#markup' => '<label>Attach Hayes Literature White Papers
    documentation.</label><a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="scm-attachment-upload-field_credentialed_documents-' . $form_state['case_delta']['refernid'] . '-id"><i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i></a><div class="previous-file-list">' . $previousfilelist . '</div><div id="scm-attachment-upload-field_credentialed_documents-' . $form_state['case_delta']['refernid'] . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="pull-left tristate-icon">' . $upload_sign. '</div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['is_this_part_another_project'] = array(
    '#type'          => 'radios',
    '#title'         => 'Does it improve Employee Satisfaction?',
    '#default_value' => !empty($case->field_employee_satisifaction['und'][0]['value']) ? $case->field_employee_satisifaction['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('another_project','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Employee Benefits</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $textarea5 = !empty($case->field_benefits_employee_sat['und'][0]['value']) ? 'dispaly_none' : '';
  $textareavalue5 = !empty($case->field_benefits_employee_sat['und'][0]['value']) ? $case->field_benefits_employee_sat['und'][0]['value'] . $casetextareaedit : '';

  $elements['describe_emp_satisfaction'] = array(
    '#type'          => 'textarea',
    '#default_value' => !empty($case->field_benefits_employee_sat['und'][0]['value']) ? $case->field_benefits_employee_sat['und'][0]['value'] : '',
    '#attributes'    => array('class'=>array('describe_emp_satisfaction','conditional-element'), 'placeholder' => 'Describe how this improves employee satisfaction..'),
    '#prefix'        => '<div class="clearfix proceeding-received conditionstate-one"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue">' . $textareavalue5 . '</div><div class="hastextarea ' . $textarea5 . '">',
    '#suffix'        => '</div></div></div>',
  );

  $elements['field_preferences_documentation']= array(
   '#type'            => 'file',
   '#title'           => 'Attachment',
   '#name'            => 'files[field_preferences_documentation][]',
   '#upload_location' => 'public://',
   
   '#attributes'      => array('multiple' => 'multiple','id' => 'scm-attachment-upload-field_preferences_documentation-' . $form_state['case_delta']['refernid'] . '-id', 'onchange' => 'javascript:updateListNew("scm-attachment-upload-field_preferences_documentation-' . $form_state['case_delta']['refernid'] .'")','class'=> array('scm-my-request-attachment','conditional-element')),
   '#description'     => t('Use CTRL + Click to choose multiple attachments.'),
   //'#attributes'    => array('multiple' => 'multiple','class'=> array('scm-my-request-attachment')),    
   '#prefix'          => '<div class="clearfix form-item" style="display:none;">',
   '#suffix'          => '</div>',
  );

  $previousfilelist = '';
  if (!empty($case->field_preferences_documentation['und'])) {
    $filelist = array();
    foreach ($case->field_preferences_documentation['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_preferences_documentation/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }

  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }

  $elements['approval_document_link']= array(
    '#markup' => '<label>Attach Supporting Documentation.</label><a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="scm-attachment-upload-field_preferences_documentation-' . $form_state['case_delta']['refernid'] . '-id"><i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i></a><div class="previous-file-list">' . $previousfilelist . '</div><div id="scm-attachment-upload-field_preferences_documentation-' . $form_state['case_delta']['refernid'] . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon">' . $upload_sign. '</div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['is_this_part_another_project_suffix'] = array(
    '#markup' => '</div>',
  );

  // Delete save and next section.
  $elements['left_section_delete'] = array(
    '#type'   => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/' . $form_state['case_delta']['refernid']), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
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
        'callback' => 'preferences_save_submit_callback',
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
      'callback' => 'preferences_save_submit_callback',
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
        'callback' => 'preferences_save_submit_callback',
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

/**
 * Function to get right content of preference page.
 */
function casemanager_preference_right_form($form, &$form_state, $i) {
  $form_state['case_delta'] = $i;

  // This variable shall be used to fetch correct data for the respective tab.
  $form_state['on_tab'] = 'preferences';

  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('project_manager_comments_process_secondary'),
  );
  return $form;
}

/**
 * Process function to get right comments form.
 */
function project_manager_comments_process_secondary($elements, &$form_state) {
  if(isset($form_state['case_delta'], $form_state['case_delta']['refernid']) && !empty($form_state['case_delta']['refernid'])) {
    global $user, $company;

    $defaultProjectNid = '';
    $defaultProjectNid = $_SESSION['scm_project_nid'];

    $elements['refercase_nid'] = array(
      '#type'  => 'value',
      '#value' => $form_state['case_delta']['refernid'],
    );
    $elements['refercase_title'] = array(
      '#type'  => 'value',
      '#value' => $form_state['case_delta']['refertitle'],
    );

    $case = '';

    if (!empty($form_state['case_delta']['refernid'])) {
      $query2 = db_select('field_data_field_case_reference', 'caser');
      $query2->fields('caser', array('entity_id'));
      $query2->condition('caser.bundle', $form_state['on_tab']);
      $query2->condition('caser.field_case_reference_nid', $form_state['case_delta']['refernid']);
      $nodenid = $query2->execute()->fetchColumn(0);
      $case = node_load($nodenid);
    }

    $elements['case_nid'] = array(
      '#type'  => 'value',
      '#value' => !empty($case->nid) ? $case->nid : '',
    );

    $elements['project_manager_inner_menu'] = array(
      // '#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><i class="pull-right fa fa-times case-collapse" aria-hidden="true" case-comment-status="close" style="cursor: pointer; display:none;"></i><div class="display-inline-block">Project Manager Comments </br><small>' . $form_state['case_delta']['refertitle'] . '</small></div>
      // <div class="pull-right"><div class="dropdown open"> <button id="dLabel" class="btn btn-success replace-my-text-here-for-sorting" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="true"> Sort <span class="caret"></span></button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel"><li><a href="javascript:void(0);">Coming soon</a></li><li><a href="javascript:void(0);" onclick="javascript:sortcolumns(\'resolved\')">Resolved</a></li><li><a href="javascript:void(0);" onclick="javascript:sortcolumns(\'report\')">Report</a></li></ul></div></div>
      // </div>',
      '#markup' => '<div class="clearfix margin-bottom-10 case-section-title text-center"><div class="display-inline-block">Project Manager Comments </br><small>' . $form_state['case_delta']['refertitle'] . '</small></div></div>',
    );
	$caseIds = $form_state['on_tab'] == 'preferences' || $form_state['on_tab'] == 'resources' || $form_state['on_tab'] == 'pay_back'?$form_state['case_delta']['refernid']:$case->nid;
	  
	
    $getComment = _get_previous_comment_by_case($caseIds);
    $elements['project_manager_title'] = array(
      '#markup' => '<div class="project-manager-comment-render-class" id="project-manager-comment-render-' . $caseIds . '">'.$getComment.'</div><div class="projectmanagetr-comment-list">',
    );

    $uniqueCommentId = md5($company->nid.'-'.time());
    $elements['unique_comment_id'] = array(
      '#type'          => 'hidden',
      '#default_value' => $uniqueCommentId,
      '#attributes'    => array('class' => array('unique-comment-id')),
    );

    $elements['comment_edit'] = array(
      '#type'          => 'hidden',
      '#default_value' => 0,
      '#attributes'    => array('class' => array('case-comment-edit')),
    );
    $elements['project_manager_comments'] = array(
      '#type'       => 'container',
      '#attributes' => array('class' => array('case-comment-section-inner','margin-bottom-10')),
    );
    $elements['project_manager_comments']['intro'] = array(
      '#markup' => '<div class="form-inline"><div class="form-group"><strong><div id="custom-date-update">'.date('l F d, Y',strtotime("today")).'</div></strong></div>',
    );
    $elements['project_manager_comments']['comments_date'] = array(
      '#type'       => 'value',
      '#value'      => strtotime(date('l F d, Y',strtotime("today"))),
      '#attributes' => array('class' => array('case-builder-date')),
    );
    $elements['project_manager_comments']['resolved'] = array(
      '#type'       =>'checkbox',
      '#title'      => t('Resolved'),
      '#attributes' => array('class' => array('case-builder-resolved')),
      '#prefix'     => '<div class="pull-right"><div class="form-group padding-5">',
      '#suffix'     =>'</div>',
    );
    $elements['project_manager_comments']['report'] = array(
      '#type'       =>'checkbox',
      '#title'      => t('Report'),
      '#attributes' => array('class' => array('case-builder-report')),
      '#prefix'     => '<div class="form-group">',
      '#suffix'     =>'</div></div></div>',
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
        'callback' => 'project_manager_comments_process_secondary_submit_callback',
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
  }
  return $elements;
}

/**
 * Ajax submit callback for right comment form.
 */
function project_manager_comments_process_secondary_submit_callback($form, &$form_state) {
  global $user,$company;
  $commands = array();
  $values = $form_state['values'];
  $caseIds = $form_state['on_tab'] == 'preferences' || $form_state['on_tab'] == 'resources' || $form_state['on_tab'] == 'pay_back'?$values['refercase_nid']:$values['case_nid'];
  if ($values['comment_edit'] == 0) {
    $Todaystrtotime = strtotime(date('l F d, Y',strtotime("today")));
    $Tomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+1 days")));
    $dayafterTomorrowstrtotime = strtotime(date('l F d, Y',strtotime("+2 days")));
    if (isset($values,$form_state['triggering_element']['#name']) && !empty($values['comments']) && !empty($values['case_nid'])){
      $case = node_load($caseIds);
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
    if (!empty($values['comments']) && !empty($values['case_nid'])) {
      $case = node_load($caseIds);
      foreach ($case->field_case_comment['und'] as $caseDelta => $casVal) {
        if ($case->field_case_unique_id['und'][$caseDelta]['value'] == $values['unique_comment_id']) {
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
  $commands[] = ajax_command_html('#project-manager-comment-render-' . $caseIds, _get_previous_comment_by_case($caseIds));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Submit callback for adding a new clinician on preferences.
 */
function clinicians_add_new_row_submit($form, &$form_state) {

  
  $triggerElement = $form_state['triggering_element'];

  if ($triggerElement['#name'] =='clinicians_add_new_row') {
    $tempIdentifer = uniqid();
    $form_state['clinicians_count'][]  = $tempIdentifer;
    $form_state['get_node_count'] = FALSE;
  }

  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for adding a new physician on preferences.
 */
function clinicians_add_new_row_callback($form, &$form_state) {
  return $form['left_case_section']['are_clinicians_primary_children'];
}

/**
 * Submit callback for remove clinician on preferences.
 */
function remove_clinicians_count_submit_handler($form, &$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];

  if(isset($form_state['clinicians_count'])){
    foreach ($form_state['clinicians_count'] as $key => $value) {
      if($form_state['clinicians_count'][$key] == $identifier) {
        unset($form_state['clinicians_count'][$key]);
        if (array_key_exists($identifier, $form_state['clinicians_default_values'])) {
          unset($form_state['clinicians_default_values'][$identifier]);
        }
      } 
    }
    $form_state['get_node_count'] = FALSE;
  }

  // We need to check that we atleast have a blank set for user.
  $clinicians_count = $form_state['clinicians_count'];
  $last_pc = end($clinicians_count);

  if (!empty($form_state['input']['physicians'][$last_pc]['clinicians_primary_fname_lname'])) {
    $form_state['clinicians_count'][] = uniqid();
  }

  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for remove physician on preferences.
 */
function remove_clinicians_count_row_callback($form, &$form_state) {
  return $form['left_case_section']['are_clinicians_primary_children'];
}

/**
 * Submit callback for adding a new physician on preferences.
 */
function physicians_add_new_row_submit($form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];
  if ($triggerElement['#name'] =='physicians_add_new_row') {
    // We only add a new row, when the last row is not empty.
    $physicians_count = $form_state['physicians_count'];
    $last_pc = end($physicians_count);

    if (!empty($form_state['input']['physicians'][$last_pc]['physicians_primary_fname_lname'])) {
      $form_state['physicians_count'][] = uniqid();
    }

    $form_state['get_node_count2'] = FALSE;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for remove clinician on preferences.
 */
function remove_physicians_count_row_callback($form, &$form_state) {
  return $form['left_case_section']['are_physicians_primary_children'];
}

/**
 * Submit callback for remove physician on preferences.
 */
function remove_physicians_count_submit_handler($form, &$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];

  if (isset($form_state['physicians_count'])) {
    foreach ($form_state['physicians_count'] as $key => $value) {
      if ($form_state['physicians_count'][$key] == $identifier) {
        unset($form_state['physicians_count'][$key]);
        if (array_key_exists($identifier, $form_state['physicians_default_values'])) {
          unset($form_state['physicians_default_values'][$identifier]);
        }
      }
    }
    $form_state['get_node_count2'] = FALSE;
  }

  // We need to check that we atleast have a blank set for user.
  $physicians_count = $form_state['physicians_count'];
  $last_pc = end($physicians_count);

  if (!empty($form_state['input']['physicians'][$last_pc]['physicians_primary_fname_lname'])) {
    $form_state['physicians_count'][] = uniqid();
  }

  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for adding a new clinician on preferences.
 */
function physicians_add_new_row_callback($form, &$form_state) {
  return $form['left_case_section']['are_physicians_primary_children'];
}

function are_clinicians_primary_children_process($elements, &$form_state) {
  // Storing count in elements, so as to use it in theme function.
  $elements['#storage_clinicians'] = $form_state['clinicians_count'];

  // Getting default values.
  $clinicians_default_values = $form_state['clinicians_default_values'];
 

  foreach ($form_state['clinicians_count'] as $key => $uniqid) {
    $elements['clinicians_subspecialty'][$uniqid] = array(
      '#type'          => 'textfield',
      '#title'         => t('Subspecialty'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($clinicians_default_values[$uniqid]['subspecialty']) ? $clinicians_default_values[$uniqid]['subspecialty'] : '',
      '#attributes'    => array('class' => array('clinicians-subspecialty','clinicians', 'conditional-element', 'trigger-clinicians-fname'), 'placeholder' => t('Subspecialty')),
      '#prefix'        => '<div class="row margin-5"><div class="col-md-10 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix'        => '</div>',
      '#parents'       => array('clinicians', $uniqid, 'clinicians_subspecialty'),
    );
    //'#attributes'    => array('class' => array('clinicians-subspecialty','clinicians', 'conditional-element', 'trigger-clinicians-fname'), 'placeholder' => t('Subspecialty'), 'onblur' => 'jQuery(this).parents(\'.section-top-parent\').find(\'.clinicians-add-new-row-button\').trigger(\'mousedown\'); return false;'),
    /*
    $elements['clinicians_primary_lname'][$uniqid] = array(
      '#type'          => 'textfield',
      '#title'         => t('First Name Last Name'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($clinicians_default_values[$uniqid]['primary_lname']) ? $clinicians_default_values[$uniqid]['primary_lname'] : '',
      '#attributes'    => array('class' => array('clinicians', 'conditional-element', 'trigger-clinicians-lname'), 'placeholder' => t('Last Name')),
      '#prefix'        => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix'        => '</div>',
      '#parents'       => array('clinicians', $uniqid, 'clinicians_primary_lname'),
    );
    $elements['clinicians_primary_email'][$uniqid] = array(
      '#type'          => 'textfield',
      '#title'         => t('First Name Last Name'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($clinicians_default_values[$uniqid]['primary_email']) ? $clinicians_default_values[$uniqid]['primary_email'] : '',
      '#attributes'    => array('class' => array('clinicians', 'conditional-element'), 'placeholder' => 'Email Address'),
      '#prefix'        => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix'        => '</div>',
      '#parents'       => array('clinicians', $uniqid, 'clinicians_primary_email'),
    );
    $elements['clinicians_subspecialty'][$uniqid] = array(      
      '#type'          => 'textfield',
      '#title'         => t('Subspecialty'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($clinicians_default_values[$uniqid]['subspecialty']) ? $clinicians_default_values[$uniqid]['subspecialty'] : '',
      '#attributes'    => array('class' => array('clinicians', 'conditional-element'), 'placeholder' => 'Subspecialty'),
      '#prefix'        => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix'        => '</div></div>',
      '#parents'       => array('clinicians', $uniqid, 'clinicians_subspecialty'),
    );
    */
    //'jQuery(this).parents(\'.section-top-parent\').find(\'.clinicians-add-new-row-button\').trigger(\'mousedown\'); return false;'

    // $add_new_link = l(t('Add New Clinician'), 'javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('padding-right-5'), 'onclick' => 'jQuery(this).parents(\'.section-top-parent\').find(\'.clinicians-add-new-row-button\').trigger(\'mousedown\'); return false;')));
    $delete_link = l(decode_entities('&#xf014;'), 'javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('remove-vendor-row-link'), 'style' => 'font-family:FontAwesome;')));

    $elements['remove'][$uniqid] = array(
      '#type' => 'submit',
      '#value' => 'remove_clinicians',
      '#name'   => $uniqId,
      '#attributes'=> array('class'=>array('remove-vendor-row', 'workflow-clinicians-submit', 'hidden')),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_clinicians_count_submit_handler'),
      '#ajax' => array(
        'callback' => 'remove_clinicians_count_row_callback',
        'wrapper' => 'are-clinicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array('type'=> 'throbber', 'message' => NULL),
      ),
      '#parents' => array('clinicians', $uniqid, 'remove'),
      '#prefix' => '<div class="clearfix margin-top-10"><div class="pull-left">' . $delete_link,
      '#suffix' => '</div></div></div>',
    );
  }
  // Adding a add new button for the above section.
  $elements['clinicians_add_new_row'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    '#name' => 'clinicians_add_new_row',
    '#attributes'=> array('class' => array('clinicians-add-new-row-button'), 'title' => 'Add New Clinician'),
    "#limit_validation_errors" => array(),
    '#submit' => array('clinicians_add_new_row_submit'),
    '#ajax' => array(
      'callback' => 'clinicians_add_new_row_callback',
      'wrapper' => 'are-clinicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
  );

  return $elements;
}

function are_physicians_primary_children_process($elements, &$form_state) {
  // Storing count in elements, so as to use it in theme function.
  $elements['#storage_physicians'] = $form_state['physicians_count'];

  $physicians_default_values = $form_state['physicians_default_values'];

  $i = 0;
  $count = count($form_state['physicians_count']);
  foreach ($form_state['physicians_count'] as $key => $uniqid) {
    $i++;
    $border_beneath = $i != $count ? 'border-beneath' : '';
    $elements['physicians_primary_fname_lname'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('First Name Last Name'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($physicians_default_values[$uniqid]['fname_lname']) ? $physicians_default_values[$uniqid]['fname_lname'] : '',
      '#attributes' => array('class' => array('physicians-primary-fname','physicians', 'conditional-element', 'trigger-physicians-fname'), 'placeholder' => t('First Name')),
      '#prefix' => $i == 1 ? '<div class="row margin-5"><div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">' : '<div class="row margin-5 margin-top-10"><div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix' => '</div>',
      '#parents' => array('physicians', $uniqid, 'physicians_primary_fname_lname'),
    );
    //'#attributes' => array('class' => array('physicians', 'conditional-element', 'trigger-physicians-fname'), 'placeholder' => t('First Name'), 'onblur' => 'jQuery(this).parents(\'.section-top-parent\').find(\'.physicians-add-new-row-button\').trigger(\'mousedown\'); return false;'),
    $elements['physicians_primary_lname'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('Last Name'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($physicians_default_values[$uniqid]['primary_lname']) ? $physicians_default_values[$uniqid]['primary_lname'] : '',
      '#attributes' => array('class' => array('physicians', 'conditional-element', 'trigger-physicians-lname'), 'placeholder' => t('Last Name')),
      '#prefix' => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix' => '</div>',
      '#parents' => array('physicians', $uniqid, 'physicians_primary_lname'),
    );
    $elements['physicians_subspecialty'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('Subspecialty'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($physicians_default_values[$uniqid]['subspecialty']) ? $physicians_default_values[$uniqid]['subspecialty'] : '',
      '#attributes'    => array('class' => array('clinicians', 'conditional-element'), 'placeholder' => 'Subspecialty'),
      '#prefix' => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix' => '</div>',
      '#parents' => array('physicians', $uniqid, 'physicians_subspecialty'),
    );
    $elements['physicians_primary_email'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('Physicians Email'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($physicians_default_values[$uniqid]['primary_email']) ? $physicians_default_values[$uniqid]['primary_email'] : '',
      '#attributes' => array('class' => array('physicians', 'conditional-element'), 'placeholder' => 'Email Address'),
      '#prefix' => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
      '#suffix' => '</div>',
      '#parents' => array('physicians', $uniqid, 'physicians_primary_email'),
    );
    $elements['field_physicians_url'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('Physician URL'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($physicians_default_values[$uniqid]['physicians_url']) ? $physicians_default_values[$uniqid]['physicians_url'] : '',
      '#attributes' => array('class' => array('physicians', 'conditional-element'), 'placeholder' => 'https://openpaymentsdata.cms.gov/'),
      '#prefix' => '<div class="col-md-12 padding-5 conditionstate-one conditionstate-one-alligned">',
      '#suffix' => '</div>',
      '#parents' => array('physicians', $uniqid, 'field_physicians_url'),
    );

    // Attachments.

    /*$file_upload_list = '<div id="edit-physicians-' . $uniqid . '-field-attachments-upload-id-filelist"></div>';
    // When adding a new element we get a fid of the previous field if any file
    // was uploaded.
    // Please note: Currently we are only allowing a single file to upload.
    $prev_file = NULL;
    $default_prev_file = FALSE;

    if (!empty($form_state['input']['physicians'][$uniqid]['field_attachments']['fid'])) {
      // If a new row is being added.
      $prev_file = file_load(check_plain($form_state['input']['physicians'][$uniqid]['field_attachments']['fid']));
    }

    if (!empty($physicians_default_values[$uniqid]['attachments'])) {
      // If the form is being rendered first time, and we had previously saved
      // any file.
      $prev_file = file_load($physicians_default_values[$uniqid]['attachments']);
      $default_prev_file = TRUE;
    }

    if (!empty($prev_file)) {
      // This means that we need to show the file name to user.
      $filename = $prev_file->filename;
      $file_url = file_create_url($prev_file->uri);
      $filename_str = strlen($filename) > 36 ? substr($filename, 0, 36) : $filename;
      $file_link = l($filename_str, $file_url, array('attributes' => array('target'=>'_blank', 'title' => $filename), 'external' => TRUE));

      $file_upload_list = '<div id="edit-physicians-' . $uniqid . '-field-attachments-upload-id-filelist">';
      $file_upload_list .= '<div class="filelist-outer">';
      // $file_upload_list .= '<span class="filelist-item" title="' . $filename . '">' . $filename_str . '</span>';
      $file_upload_list .= '<span class="filelist-item">' . $file_link . '</span>';
      $file_upload_list .= ' <i class="fa fa-trash-o text-muted" aria-hidden="true" style="cursor:pointer" onclick="jQuery(\'input[name=physicians_' . $uniqid . '_field_attachments_remove_button]\').trigger(\'mousedown\'); return false;"></i>';
      $file_upload_list .= '<br>';
      $file_upload_list .= '</div></div>';
    }

    $elements['field_attachments'][$uniqid] = array(
      '#type'            => 'managed_file',
      '#upload_location' => 'public://',
      '#attributes'      => array('class'=> array('scorecard-product-attachment-managed', $uniqid), 'data' => $uniqid),
      '#theme'           => 'custom_file_managed_theme_scorecard',
      '#parents'         => array('physicians', $uniqid, 'field_attachments'),
    );

    // Providing default value, if a file is available.
    if (!empty($prev_file->fid) && $default_prev_file) {
      $elements['field_attachments'][$uniqid]['#default_value'] = $prev_file->fid;
    }

    $elements['field_attachments_markup'][$uniqid] = array(
      '#type'   => 'markup',
      '#markup' => '<label class="text-right">Attach Findings.</label><a href="javascript:void(0);" class="pull-right margin-top-5" data="scorecard-product-attachment-' . $uniqid . '-id" onclick="jQuery(\'.' . $uniqid . ' input[type=file]\').trigger(\'click\'); return false;"><i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i></a>' . $file_upload_list,
      '#prefix' => '<div class="col-md-12 padding-5 conditionstate-one conditionstate-one-alligned label-right">',
      '#suffix' => '</div></div>',
    );*/





    /*******************************attachement***************************************/
    $elements['physiciansfieldattachments'][$uniqid] = array(
     '#type'            => 'file',
     '#title'           => 'Attachment',
     '#name'            => 'files['.$uniqid.'][]',
     '#upload_location' => 'public://',
     
     '#attributes'      => array('multiple' => 'multiple','id' => 'scm-attachment-upload-field_credentialed_documents-field-attachments-'.$uniqid . '-id', 'onchange' => 'javascript:updateListNew("scm-attachment-upload-field_credentialed_documents-field-attachments-'.$uniqid .'")','class'=> array('scm-my-request-attachment','conditional-element')),
     '#description'     => t('Use CTRL + Click to choose multiplee attachments.'),
     //'#attributes'    => array('multiple' => 'multiple','class'=> array('scm-my-request-attachment')), 
     '#parents'         => array('physicians', $uniqid, 'field_attachments'),   
     '#prefix'          => '<div class="clearfix form-item" style="display:none;">',
     '#suffix'          => '</div>',
    );
    $elements[$uniqid] = array(
      '#type'            => 'value',
      //'#parents'         => array('physicians', $uniqid, 'field_attachments2'),
    );
  $previousfilelist = '';
  if (!empty($physicians_default_values[$uniqid]['attachments'])) {
    $filelist = array();
    foreach ($physicians_default_values[$uniqid]['attachments'] as $key => $value) {
      $elements['physiciansfieldattachments'][$uniqid]['#default_value'][] = file_load($value['fid']);
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/filedcollectonfilerow_remove/'.$form_state['case_delta']['case_nid'].'/field_attachments-'.$form_state['filedcollectonfilerow_remove'][$value['fid']].'-'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }

  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }

  $elements['field_attachments_markup'][$uniqid] = array(
      '#type'   => 'markup',
      '#markup' => '<label class="text-right">Attach Findings.</label><a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="scm-attachment-upload-field_credentialed_documents-field-attachments-'.$uniqid . '-id"><i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i></a><div class="previous-file-list">' . $previousfilelist . '</div><div id="scm-attachment-upload-field_credentialed_documents-field-attachments-'.$uniqid . '-id-filelist" style="display:none;"></div>',
      '#prefix' => '<div class="col-md-12 padding-5 conditionstate-one conditionstate-one-alligned label-right">',
      '#suffix' => '</div></div>',
    );
          /**********************************************************************/

    // $add_new_link = l(t('Add New Physician'), 'javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('padding-right-5'), 'onclick' => 'jQuery(this).parents(\'.section-top-parent\').find(\'.physicians-add-new-row-button\').trigger(\'mousedown\'); return false;')));
    $delete_link = l(decode_entities('&#xf014;'), 'javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('remove-vendor-row-link'), 'style' => 'font-family:FontAwesome;')));

    $elements['remove'][$uniqid] = array(
      '#type' => 'submit',
      '#value' => 'remove_physicians',
      '#name' => $uniqid,
      '#attributes'=> array('class'=>array('remove-vendor-row', 'workflow-physicians-submit','hidden')),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_physicians_count_submit_handler'),
      '#ajax' => array(
        'callback' => 'remove_physicians_count_row_callback',
        'wrapper'  => 'are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
      '#parents' => array('physicians', $uniqid, 'remove'),
      '#prefix' => '<div class="clearfix margin-top-10 margin-bottom-10 ' . $border_beneath .'"><div class="pull-left">' . $delete_link,
      '#suffix' => '</div><div class="clearfix text-right open-payments-window"><a href="https://openpaymentsdata.cms.gov" onclick="window.open(\'https://openpaymentsdata.cms.gov\', \'newwindow\', \'width=800,height=600\'); return false;">Open Payments Search</a></div>
        </div>',
    );
  }

  // Adding a add new button for the above section.
  $elements['physicians_add_new_row'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    '#name' => 'physicians_add_new_row',
    '#attributes'=> array('class'=>array('physicians-add-new-row-button'),'title'=>'Add New Physician'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('physicians_add_new_row_submit'),
    '#ajax' => array(
      'callback' => 'physicians_add_new_row_callback',
      'wrapper' => 'are-physicians-primary-children-edit-' . $form_state['case_delta']['refernid'],
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
  );

  return $elements;
}

function preferences_save_submit_callback($form,&$form_state) {
   
  // return;
  global $user, $company;
  $commands = array();

  if ($_FILES['files']['name'] != '' ) {
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
        
          if(!empty($form_state['physicians_count']) && !empty($form_state['values']['physicians'])){
   
            if(in_array($key[0],$form_state['physicians_count'])){
              $form_state['values']['physicians'][$key[0]]['field_attachments'][] = $file;
              
            }
          }
        }
      }
    }
  }
  $values = $form_state['values'];


  if (!empty($values['case_nid'])) {
    // This is the case when we are updating an old node.
    $node = node_load($values['case_nid']);
  }
  else {
    // This is the case when a new node is to be created.
    $node = _node_creation_call('preferences', $values['refercase_title']);
  }

  // As now we have a node, proceding further.

  // Saving references.
  $node->field_project_reference[LANGUAGE_NONE][0]['nid'] = !empty($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '';
  $node->field_case_reference[LANGUAGE_NONE][0]['nid'] = !empty($values['refercase_nid']) ? $values['refercase_nid'] : '';

  // Initial description.
  $node->field_preferences_subtitle[LANGUAGE_NONE][0]['value'] = $values['case_description'];

  // Clinicians.
  $node->field_preferences_non_physician[LANGUAGE_NONE][0]['value'] = !empty($values['are_clinicians_primary']) ? $values['are_clinicians_primary'] : 0;
  if (!empty($values['clinicians'])) {
    /*if (!empty($node->field_non_physician_first_name[LANGUAGE_NONE])) {
      unset($node->field_non_physician_first_name[LANGUAGE_NONE]);
    }*/
    $clinicianscount = 0;
    $node->field_select_subspecialty[LANGUAGE_NONE] = '';
    foreach ($values['clinicians'] as $key => $value) {
      if (!empty($value['clinicians_subspecialty'])) {
  /*      $node->field_non_physician_first_name[LANGUAGE_NONE][$clinicianscount]['value'] = !empty($value['clinicians_primary_fname_lname']) ? $value['clinicians_primary_fname_lname'] : '';
        $node->field_preferences_last_name[LANGUAGE_NONE][$clinicianscount]['value'] = !empty($value['clinicians_primary_lname']) ? $value['clinicians_primary_lname'] : '';*/
        
        $node->field_select_subspecialty[LANGUAGE_NONE][$clinicianscount]['value'] = !empty($value['clinicians_subspecialty']) ? $value['clinicians_subspecialty'] : '';
        /*$node->field_nonphysicianclinicianemail[LANGUAGE_NONE][$clinicianscount]['value'] = !empty($value['clinicians_primary_email']) ? $value['clinicians_primary_email'] : '';*/
        $clinicianscount++;
      }
    }
  }
  
  // Physicians.
  $node->field_physicians[LANGUAGE_NONE][0]['value'] = !empty($values['are_physicians_primary']) ? $values['are_physicians_primary'] : 0;

  if (!empty($values['physicians'])) {
    if (!empty($node->field_physicians_fc[LANGUAGE_NONE])) {
      $old_fc_ids = array();
      foreach ($node->field_physicians_fc[LANGUAGE_NONE] as $key => $value) {
        $old_fc_ids[] = $value['value'];
        unset($node->field_physicians_fc[LANGUAGE_NONE][$key]);
      }

      // Deleting the old field collection items.
      entity_delete_multiple('field_collection_item', $fvaluenode);
    }

    $count = 0;
    foreach ($values['physicians'] as $physician) {
      if (!empty($physician['physicians_primary_fname_lname'])) {
        $fc_item = entity_create('field_collection_item', array('field_name' => 'field_physicians_fc'));
        $fc_item->setHostEntity('node', $node);
        
        $fc_item->field_physicians_first_name[LANGUAGE_NONE][0]['value'] = $physician['physicians_primary_fname_lname'];
        $fc_item->field_physicians_last_name[LANGUAGE_NONE][0]['value'] = $physician['physicians_primary_lname'];
        $fc_item->field_physicians_select_sub[LANGUAGE_NONE][0]['value'] = $physician['physicians_subspecialty'];
        $fc_item->field_physicians_email[LANGUAGE_NONE][0]['value'] = $physician['physicians_primary_email'];
        $fc_item->field_physicians_url[LANGUAGE_NONE][0]['value'] = $physician['field_physicians_url'];

        // Handling files if any present.
        if (!empty($physician['field_attachments'])) {
          foreach($physician['field_attachments'] as $fakey=>$favalue){
            
          $file = file_load($favalue->fid);
          $file->status = FILE_STATUS_PERMANENT;
          file_save($file);
          $product_file = (array) $file;
          $product_file['display'] = 1;
          $fc_item->field_attachments[LANGUAGE_NONE][] = $product_file;
        }
        }
        $fc_item->save();
      }
    }
  }

  // Other fields.
  $node->field_physicians_new_physician[LANGUAGE_NONE][0]['value'] = !empty($values['is_this_for_a_new_physican']) ? $values['is_this_for_a_new_physican'] : 0;
  $node->field_physicians_credentialed[LANGUAGE_NONE][0]['value'] = !empty($values['is_the_physican_credentialed']) ? $values['is_the_physican_credentialed'] : 0;

  // Employee satisfaction.
  $node->field_employee_satisifaction[LANGUAGE_NONE][0]['value'] = !empty($values['is_this_part_another_project']) ? $values['is_this_part_another_project'] : 0;
  $node->field_benefits_employee_sat[LANGUAGE_NONE][0]['value'] = !empty($values['describe_emp_satisfaction']) ? $values['describe_emp_satisfaction'] : '';

  // Handling files.
  if (!isset($node->field_preferences_documentation[LANGUAGE_NONE])) {
    $node->field_preferences_documentation[LANGUAGE_NONE] = array();
  }
  if (!empty($values['field_preferences_documentation'])) {
    foreach ($values['field_preferences_documentation'] as $imgkey => $file) {
      $new_file = file_load($file->fid);
      $file_arr = (array)$new_file;
      $file_arr['display'] = 1;
      $node->field_preferences_documentation[LANGUAGE_NONE][] = $file_arr;
    }
  }
  if (!isset($node->field_credentialed_documents[LANGUAGE_NONE])) {
        $node->field_credentialed_documents[LANGUAGE_NONE] = array();
      }
  if (!empty($values['field_credentialed_documents'])) {
    foreach ($values['field_credentialed_documents'] as $imgkey => $file) {
      $new_file = file_load($file->fid);
      $file_arr = (array)$new_file;
      $file_arr['display'] = 1;
      $node->field_credentialed_documents[LANGUAGE_NONE][] = $file_arr;
    }
  }

  // Finally saving the node.
  node_save($node);

  switch ($form_state['triggering_element']['#name']) {
    case 'save_submit':
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/preferences');
      break;

    case 'save_next_submit':
      // Redirecting user to next tab.
      $commands[] = ctools_ajax_command_redirect('/scm/resources');
      break;

    case 'save_duplicate_submit':
      // Case duplicate
      _case_manager_case_duplicate($values['refercase_nid']);
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/preferences');
      break;
  }
  

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Theme process for preference clinicians.
 */
function theme_are_clinicians_primary_children_theme($variables) {
  $element = $variables['form'];
  $storage = $element['#storage_clinicians'];
  $output = '';

  $header = $rows = array();
  foreach ($storage as $key => $uniqid) {
    
    $output .= drupal_render($element['clinicians_subspecialty'][$uniqid]);
    /*$output .= drupal_render($element['clinicians_primary_lname'][$uniqid]);
    $output .= drupal_render($element['clinicians_primary_email'][$uniqid]);
    $output .= drupal_render($element['clinicians_subspecialty'][$uniqid]);*/
    $output .= drupal_render($element['remove'][$uniqid]);
  
  }

  $output .= drupal_render_children($element);
  return $output;
}

/**
 * Theme process for preference clinicians.
 */
function theme_are_physicians_primary_children_theme($variables) {
  $element = $variables['form'];
  $storage = $element['#storage_physicians'];
  $output = '';

  foreach ($storage as $key => $uniqid) { 
    $output .= drupal_render($element['physicians_primary_fname_lname'][$uniqid]);
    $output .= drupal_render($element['physicians_primary_lname'][$uniqid]);
    $output .= drupal_render($element['physicians_primary_email'][$uniqid]);
    $output .= drupal_render($element['physicians_subspecialty'][$uniqid]);
    $output .= drupal_render($element['field_physicians_url'][$uniqid]);
    $output .= '<div class="hidden">' . drupal_render($element['field_attachments'][$uniqid]) . '</div>';
    $output .= drupal_render($element['field_attachments_markup'][$uniqid]);
    $output .= drupal_render($element['remove'][$uniqid]);
  }

  $output .= drupal_render_children($element);
  return $output;
}

################# Preferences section ends #####################


################ Resources section starts ######################
/**
 * Function to get content for resources page.
 */
function resources_builder_outer() {
  global $user, $company;
  $defaultProjectNid = isset($_SESSION['scm_project_nid']) && !empty($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '';
  if (!empty($defaultProjectNid)) {
    $casenid = _get_scmcase_nids_by_referpronid($defaultProjectNid);
    $casecount = count($casenid);
    $caseswidth = $casecount *400 + 10;
    $elements['scm-casebuilder-start']= array(
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
    foreach ($casenid as $key => $nid) {
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
    $elements['resources_section_' . $nid] = array(
        '#type' => 'container',
    '#attributes' => array('class'=> array('changein-document-popup','caseouter','case_'.$casesr, 'case-continer-'.$nid, $caseStatusCls) ,'original-pos'=>'case_'.$casesr,'updated-pos'=>''),
      );
      $elements['resources_section_' . $nid]['scm-resources-left'] = array(
        '#markup' => drupal_render(drupal_get_form('casemanager_resources_left_form', $casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left section-top-parent"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );

      $dispaly_none = 'dispaly_none';

      $elements['resources_section_' . $nid]['scm-resources-right'] = array(
        '#markup' => drupal_render(drupal_get_form('casemanager_resources_right_form', $casedelta)),
        '#prefix' => '<div class="' . $commentsclass . ' col-md-8 padding-10 margin-bottom-10 casebuilder-details-right ' . $dispaly_none . '"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    }
  
    $elements['scm-casebuilder-end']= array(
      '#markup' => '</div>',
    );
  }
  return $elements;
}

/**
 * Function to get left form for resources page.
 */
function casemanager_resources_left_form($form, &$form_state, $i) {
  $form_state['case_delta'] = $i;
  if (empty($form_state['clinicians_count'])) {
    $form_state['clinicians_count'] = 0;
  }
  if (empty($form_state['physicians_count'])) {
    $form_state['physicians_count'] = 0;
  }
  if (!isset($form_state['get_node_count'])) {
    $form_state['get_node_count'] = TRUE;
  }

  if (!isset($form_state['get_node_count2'])) {
    $form_state['get_node_count2'] = TRUE;
  }

  if(isset($i['refernid']) && !empty($i['refernid'])){
    $query2 = db_select('field_data_field_case_reference','caser');
    $query2->fields('caser',array('entity_id'));
    $query2->condition('caser.bundle','resources');
    $query2->condition('caser.field_case_reference_nid',$i['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
    $caseload = node_load($nodenid);  

    

    if (!empty($caseload->field_facilities_first_name[LANGUAGE_NONE]) && $form_state['get_node_count2'] != FALSE) {
      // If there is any previous data, then getting it.
      $form_state['contacts_count'] = array();
      $form_state['contacts_default_values'] = array();

      foreach ($caseload->field_facilities_first_name[LANGUAGE_NONE] as $clkey => $clvalue) {         
          $tempIdentifer = uniqid();
          $form_state['contacts_count'][]  = $tempIdentifer;
          $form_state['contacts_default_values'][$tempIdentifer] = array(
            'fcfname'  => $caseload->field_facilities_first_name['und'][$clkey]['value'],
            'fclname'  => $caseload->field_facilities_last_name['und'][$clkey]['value'],
            'fcmail'  => $caseload->field_facilities_email_address['und'][$clkey]['value'],
          );
       
      }

      $tempIdentifer = uniqid();
      $form_state['contacts_count'][]  = $tempIdentifer;
      $form_state['get_node_count2'] = FALSE;
    }
  }


  if (empty($form_state['contacts_count'])) {
    $tempIdentifer = uniqid();
    $form_state['contacts_count'][]  = $tempIdentifer;
  }
  $form['left_case_section'] = array(
    '#type'       => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container', 'clearfix', 'padding-10')),
    '#prefix'     => '<div id="preference-left-section" class="clearfix">',
    // '#prefix'     => '<div class="preference-left-section clearfix">',
    '#suffix'     => '</div>',
    '#process'    => array('resources_left_section_process'),
  );
 
  return $form;
}

/**
 * Function to get right content of preference page.
 */
function casemanager_resources_right_form($form, &$form_state, $i) {
  $form_state['case_delta'] = $i;

  // This variable shall be used to fetch correct data for the respective tab.
  $form_state['on_tab'] = 'resources';

 

  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('project_manager_comments_process_secondary'),
  );
  return $form;
}

/**
 * Process function for resources left form.
 */
function resources_left_section_process($elements, &$form_state) {
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
    $query2->condition('caser.bundle','resources');
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
  $form_state['case_delta']['case_nid'] = !empty($case->nid) ? $case->nid : '';

  $casetitle = (strlen($form_state['case_delta']['refertitle']) > 26) ? substr($form_state['case_delta']['refertitle'], 0, 23) . '...' : $form_state['case_delta']['refertitle'];
  
  $caseStatusBtn = '<input id="case-toogle-check-cust" class="case-status-check" type="checkbox" checked data-toggle="toggle" data-on="Active" data-off="Inactive" data-onstyle="success" data-offstyle="danger" for="'.$form_state['case_delta']['refernid'].'">';
  
  $elements['case_progress_by_section_title'] = array(
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title case-section-title-sp margin-top-10"><div class="pull-left fixed-case-title" title="'. $form_state['case_delta']['refertitle'] . '">Case ' . $form_state['case_delta']['sr'] . ': ' . $casetitle . '</div><div class="pull-right toggle-case-status-check changein-document-btn">'.$caseStatusBtn.'<i class="fa fa-comments-o '.$hasecase.'" aria-hidden="true" case-status="close" style="cursor: pointer;" '.$notcasefound.'></i></div></div>',
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
 //  $textarea1 = !empty($case->field_resources_subtitle['und'][0]['value']) ? 'dispaly_none' : '';
  
 //  $textareavalue1 = !empty($case->field_resources_subtitle['und'][0]['value']) ? $case->field_resources_subtitle['und'][0]['value'] . $casetextareaedit : '';

 //  $textarea_label = !empty($_SESSION['scm_label_object']['case_builder']['description']) ? $_SESSION['scm_label_object']['case_builder']['description'] : t('Description');
 //  $elements['case_description'] = array(
 //    '#type'          => 'textarea',
  // '#attributes'=> array('placeholder'=> 'Enter case description here.'),
 //    '#default_value' => !empty($case->field_resources_subtitle['und'][0]['value']) ? $case->field_resources_subtitle['und'][0]['value'] : '',
 //    '#prefix'        => '<div class="clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">' . $textarea_label . '</div><div class="hastextareavalue">' . $textareavalue1 . '</div><div class="hastextarea ' . $textarea1 . '">',
 //    '#suffix'        => '</div></div>',
 //  );
  $textarea_label = !empty($_SESSION['scm_label_object']['case_builder']['description']) ? $_SESSION['scm_label_object']['case_builder']['description'] : t('Description');
  $elements['case_description'] = array(
    '#type'          => 'markup',
    '#prefix'        => '<div class="clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">' . $textarea_label . '</div><div class="hastextareavalue">',
    '#markup' => $getCaseDesc,
    '#suffix'        => '</div></div>',
  );
  $elements['case_nid'] = array(
    '#type'  => 'value',
    '#value' => $form_state['case_delta']['case_nid'],
  );

  // Resources exclusive fields.
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));

  $elements['are_there_facility_impacts'] = array(
    '#type'          => 'radios',
    '#title'         => t('Are there Facility Impacts?'),
    '#default_value' => !empty($case->field_resources_facility_impacts['und'][0]['value']) ? $case->field_resources_facility_impacts['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('clinicians','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Facilities</div>
      <div class="clearfix margin-bottom-10"><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $textarea2 = !empty($case->field_facilities_impacted['und'][0]['value']) ? 'dispaly_none' : '';
  
  $textareavalue2 = !empty($case->field_facilities_impacted['und'][0]['value']) ? $case->field_facilities_impacted['und'][0]['value'] . $casetextareaedit : '';

  $elements['facilities_impacted'] = array(
    '#type'          => 'textarea',
    '#default_value' => !empty($case->field_facilities_impacted['und'][0]['value']) ? $case->field_facilities_impacted['und'][0]['value'] : '',
    '#attributes'    => array('class'=>array('describe_emp_satisfaction','conditional-element'), 'placeholder' => 'Describe what will be impacted.'),
    '#prefix'        => '<div class="clearfix proceeding-received conditionstate-one margin-bottom-10"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue clearfix">' . $textareavalue2 . '</div><div class="hastextarea clearfix ' . $textarea2 . '">',
    '#suffix'        => '</div></div></div>',
  );

  // $elements['facilities_contact'] = array(
  //   '#type'          => 'textfield',
  //   '#title'         => t('Facilities Contact'),
  //   '#title_display' => 'invisible',
  //   '#default_value' => !empty($case->field_facilities_contact['und'][0]['value']) ? $case->field_facilities_contact['und'][0]['value'] : '',
  //   '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('Provide the name(s) of your facilities contact')),
  //   '#prefix'        => '<div class="clearfix conditionstate-one">',
  //   '#suffix'        => '</div>',
  // );
$elements['facilities_contact_prefix'] = array(
  '#markup' => '<div class="clearfix conditionstate-one"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Contact(s)</div>',
);

$elements['facilities_contact_children'] = array(
    '#type'    => 'container',
    '#process' => array('facilities_contact_children_process'),
    '#theme'   => 'facilities_contact_children_theme',
    '#prefix'  => '<div id="facilities-contact-children-edit-' . $form_state['case_delta']['refernid'] . '" class="facilities-contact-children">',
    '#suffix'  => '</div>'
  );









/*  $elements['facilities_first_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Facilities First Name'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_facilities_first_name['und'][0]['value']) ? $case->field_facilities_first_name['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('First Name')),
    '#prefix'        => '<div class="clearfix conditionstate-one"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Contact(s)</div>
    <div class="clearfix"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right"><div class="row margin-5 conditionstate-one conditionstate-one-alligned"><div class="col-md-6 padding-5 margin-bottom-4">',
    '#suffix'        => '</div>',
  );





  $elements['facilities_last_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Facilities Last Name'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_facilities_last_name['und'][0]['value']) ? $case->field_facilities_last_name['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('Last Name')),
    '#prefix'        => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one-alligned">',
    '#suffix'        => '</div></div>',
  );
  $elements['facilities_email'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Facilities Email Address'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_facilities_email_address['und'][0]['value']) ? $case->field_facilities_email_address['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('Email Address')),
    '#prefix'        => '<div class="clearfix conditionstate-one">',
    '#suffix'        => '</div></div></div></div>',
  );*/

  $elements['are_there_facility_impacts_suffix'] = array(
    '#markup' => '</div></div></div>',
  );

  $elements['is_there_an_it_component'] = array(
    '#type'          => 'radios',
    '#title'         => t('Is There An IT Component?'),
    '#default_value' => !empty($case->field_it_component['und'][0]['value']) ? $case->field_it_component['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('it','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">Information Technology</div><div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $textarea3 = !empty($case->field_resources_affect_it['und'][0]['value']) ? 'dispaly_none' : '';
  
  $textareavalue3 = !empty($case->field_resources_affect_it['und'][0]['value']) ? $case->field_resources_affect_it['und'][0]['value'] . $casetextareaedit : '';

  $elements['it_affected'] = array(
    '#type'          => 'textarea',
    '#default_value' => !empty($case->field_resources_affect_it['und'][0]['value']) ? $case->field_resources_affect_it['und'][0]['value'] : '',
    '#attributes'    => array('class'=>array('describe_emp_satisfaction','conditional-element'), 'placeholder' => 'Describe what will be impacted.'),
    '#prefix'        => '<div class="clearfix proceeding-received conditionstate-one"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="clearfix margin-bottom-4"><div class="hastextareavalue clearfix">' . $textareavalue3 . '</div><div class="hastextarea clearfix ' . $textarea3 . '">',
    '#suffix'        => '</div></div>',
  );

  $elements['it_contact'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Facilities Contact'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_contact['und'][0]['value']) ? $case->field_contact['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('it', 'conditional-element'), 'placeholder' => t('Provide the name(s) of your facilities contact')),
    '#prefix'        => '<div class="clearfix margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div></div></div>',
  );
  /*$elements['it_first_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('IT First Name'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_it_firstname['und'][0]['value']) ? $case->field_it_firstname['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('it', 'conditional-element'), 'placeholder' => t('First Name')),
    '#prefix'        => '<div class="row margin-5 conditionstate-one conditionstate-one-alligned"><div class="col-md-6 padding-5 margin-bottom-4">',
    '#suffix'        => '</div>',
  );
  $elements['it_last_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('IT Last Name'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_it_last_name['und'][0]['value']) ? $case->field_it_last_name['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('it', 'conditional-element'), 'placeholder' => t('Last Name')),
    '#prefix'        => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one-alligned">',
    '#suffix'        => '</div></div>',
  );*/
  /*$elements['it_email'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Facilities Email Address'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_it_email_address['und'][0]['value']) ? $case->field_it_email_address['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('it', 'conditional-element'), 'placeholder' => t('Email Address')),
    '#prefix'        => '<div class="clearfix conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div>',
  );*/

  $elements['governance_approved'] = array(
    '#type' => 'radios',
    '#title' => t('Has IT Governance Approved?'),
    '#default_value' => !empty($case->field_governance_approved['und'][0]['value']) ? $case->field_governance_approved['und'][0]['value'] : 0,
    '#options' => $active,
    
    '#attributes' => array('class'=>array('component','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right dont-make-it-green-on-red">',
    '#suffix' => '</div></div>',
  );

  $textarea4 = !empty($case->field_it_approval_status['und'][0]['value']) ? 'dispaly_none' : '';
  
  $textareavalue4 = !empty($case->field_it_approval_status['und'][0]['value']) ? $case->field_it_approval_status['und'][0]['value'] . $casetextareaedit : '';

  $elements['approval_status'] = array(
    '#type' => 'textarea',
    '#default_value' => !empty($case->field_it_approval_status['und'][0]['value']) ? $case->field_it_approval_status['und'][0]['value'] : '',
    '#attributes' => array('class'=>array('component','conditional-element'), 'placeholder' => 'Describe the projects affected and approvals received.'),
    '#prefix' => '<div class="clearfix proceeding-received conditionstate-two" style="display:none"><div class="pull-left tristate-icon"></div><div class="tristate-toggle-button pull-right icon-shiftup-outer"><div class="hastextareavalue clearfix">'.$textareavalue4.'</div><div class="hastextarea clearfix '.$textarea4.'">',
    '#suffix' => '</div></div></div>',
  );

  $elements['field_attach_it_approval_meeting']= array(
   '#type'            => 'file',
   '#title'           => 'Attachment',
   '#name'            => 'files[field_attach_it_approval_meeting][]',
   '#upload_location' => 'public://',
   
   '#attributes'      => array('multiple' => 'multiple','id' => 'scm-attachment-upload-field_attach_it_approval_meeting-' . $form_state['case_delta']['refernid'] . '-id', 'onchange' => 'javascript:updateListNew("scm-attachment-upload-field_attach_it_approval_meeting-' . $form_state['case_delta']['refernid'] .'")','class'=> array('scm-my-request-attachment','conditional-element')),
   '#description'     => t('Use CTRL + Click to choose multiple attachments.'),
   //'#attributes'    => array('multiple' => 'multiple','class'=> array('scm-my-request-attachment')),    
   '#prefix'          => '<div class="clearfix form-item" style="display:none;">',
   '#suffix'          => '</div>',
  );

  $previousfilelist = '';
  if (!empty($case->field_attach_it_approval_meeting['und'])) {
    $filelist = array();
    foreach ($case->field_attach_it_approval_meeting['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_attach_it_approval_meeting/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }

  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }

  $elements['approval_meeting_document']= array(
    '#markup' => '<label>Attach IT Approval Meeting Minutes
    documentation.</label><a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="scm-attachment-upload-field_attach_it_approval_meeting-' . $form_state['case_delta']['refernid'] . '-id"><i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i></a><div class="previous-file-list">' . $previousfilelist . '</div><div id="scm-attachment-upload-field_attach_it_approval_meeting-' . $form_state['case_delta']['refernid'] . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '<div class="clearfix conditionstate-two"><div class="pull-left tristate-icon">' . $upload_sign. '</div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
  );

  $elements['is_there_an_it_component_suffix'] = array(
    '#markup' => '</div>',
  );

  // Delete save and next section.
  $elements['left_section_delete'] = array(
    '#type'   => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/' . $form_state['case_delta']['refernid']), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
    '#prefix' => '<div class="clearfix margin-bottom-10 case-button-outer">',
  );
  $elements['left_section_cancel'] = array(
    '#type'   => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit">',
  );


  
  /*$elements['left_section_save'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#value'      => t('Save'),
    '#ajax'       => array(
        'callback' => 'resources_save_submit_callback',
        'method'   => 'replace',
        'effect'   => 'fade',
      ),
    '#attributes' => array('class'=>array('save-case-button')),
    '#prefix'     => '<div class="clearfix" style="display:none">',
    '#suffix'     => '</div>',
   );*/
  $elements['left_section_save_and_next'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#name'       => 'save_next_submit',
    '#value'      => t('Save and Next'),
    '#ajax'       => array(
        'callback' => 'resources_save_submit_callback',
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
      'callback' => 'resources_save_submit_callback',
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
        'callback' => 'resources_save_submit_callback',
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

/**
 * Ajax submit callback for resources_left_section_process.
 */
function resources_save_submit_callback($form, &$form_state) {
  global $user, $company;
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

  if (!empty($values['case_nid'])) {
    // This is the case when we are updating an old node.
    $node = node_load($values['case_nid']);
  }
  else {
    // This is the case when a new node is to be created.
    $node = _node_creation_call('resources', $values['refercase_title']);
  }

  // As now we have a node, proceding further.

  // Saving references.
  $node->field_project_reference[LANGUAGE_NONE][0]['nid'] = !empty($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '';
  $node->field_case_reference[LANGUAGE_NONE][0]['nid'] = !empty($values['refercase_nid']) ? $values['refercase_nid'] : '';

  // Initial description.
  $node->field_resources_subtitle[LANGUAGE_NONE][0]['value'] = $values['case_description'];

  // Facilities.
  $node->field_resources_facility_impacts[LANGUAGE_NONE][0]['value'] = !empty($values['are_there_facility_impacts']) ? $values['are_there_facility_impacts'] : 0;
  $node->field_facilities_impacted[LANGUAGE_NONE][0]['value'] = !empty($values['facilities_impacted']) ? $values['facilities_impacted'] : '';
  $node->field_facilities_contact[LANGUAGE_NONE][0]['value'] = !empty($values['facilities_contact']) ? $values['facilities_contact'] : '';
 /* $node->field_facilities_first_name[LANGUAGE_NONE][0]['value'] = !empty($values['facilities_first_name']) ? $values['facilities_first_name'] : '';
  $node->field_facilities_last_name[LANGUAGE_NONE][0]['value'] = !empty($values['facilities_last_name']) ? $values['facilities_last_name'] : '';
  $node->field_facilities_email_address[LANGUAGE_NONE][0]['value'] = !empty($values['facilities_email']) ? $values['facilities_email'] : '';*/

  if($values['are_there_facility_impacts'] !=2){
    $node->field_facilities_first_name[LANGUAGE_NONE] = '';
    $node->field_facilities_last_name[LANGUAGE_NONE] = '';
    $node->field_facilities_email_address[LANGUAGE_NONE] = '';
  }

   if (!empty($values['facilitiescontact'])) {
    $facilitiescontact = 0;
    $node->field_facilities_first_name[LANGUAGE_NONE] = '';
    $node->field_facilities_last_name[LANGUAGE_NONE] = '';
    $node->field_facilities_email_address[LANGUAGE_NONE] = '';
    foreach ($values['facilitiescontact'] as $key => $value) {
      if (!empty($value['facilities_first_name'])) {        
        $node->field_facilities_first_name[LANGUAGE_NONE][$facilitiescontact]['value'] = !empty($value['facilities_first_name']) ? $value['facilities_first_name'] : '';
        $node->field_facilities_last_name[LANGUAGE_NONE][$facilitiescontact]['value'] = !empty($value['facilities_last_name']) ? $value['facilities_last_name'] : '';
        $node->field_facilities_email_address[LANGUAGE_NONE][$facilitiescontact]['value'] = !empty($value['facilities_email']) ? $value['facilities_email'] : '';        
        $facilitiescontact++;
      }
    }
  }

  // Information Technology.
  $node->field_it_component[LANGUAGE_NONE][0]['value'] = !empty($values['is_there_an_it_component']) ? $values['is_there_an_it_component'] : 0;
  $node->field_resources_affect_it[LANGUAGE_NONE][0]['value'] = !empty($values['it_affected']) ? $values['it_affected'] : '';
  $node->field_contact[LANGUAGE_NONE][0]['value'] = !empty($values['it_contact']) ? $values['it_contact'] : '';
  /*$node->field_it_firstname[LANGUAGE_NONE][0]['value'] = !empty($values['it_first_name']) ? $values['it_first_name'] : '';
  $node->field_it_last_name[LANGUAGE_NONE][0]['value'] = !empty($values['it_last_name']) ? $values['it_last_name'] : '';
  $node->field_it_email_address[LANGUAGE_NONE][0]['value'] = !empty($values['it_email']) ? $values['it_email'] : '';*/
  $node->field_governance_approved[LANGUAGE_NONE][0]['value'] = !empty($values['governance_approved']) ? $values['governance_approved'] : 0;
  $node->field_it_approval_status[LANGUAGE_NONE][0]['value'] = !empty($values['approval_status']) ? $values['approval_status'] : '';

  // Saving files.
  /*$files_arr = array('field_attach_it_approval_meeting');

  // First handling files.
  foreach ($files_arr as $key => $value) {
    if (!empty($values[$value])) {  
      $new_file = file_load($values[$value]->fid);
      $file_arr = (array)$new_file;
      $file_arr['display'] = 1;
      $node->{$value}[LANGUAGE_NONE][0] = $file_arr;
    }
  }*/
  if(!isset($node->field_attach_it_approval_meeting['und'])){
      $node->field_attach_it_approval_meeting['und'] = array();
    }
    foreach ($form_state['values']['field_attach_it_approval_meeting'] as $imgkey3 => $file3) {      
      $new_file3 = file_load($file3->fid);
      $file_arr3 = (array)$new_file3;
      $file_arr3['display'] = 1;          
      $node->field_attach_it_approval_meeting['und'][] = $file_arr3;
    }

  // Finally saving the node.
  node_save($node);

  switch ($form_state['triggering_element']['#name']) {
    case 'save_submit':
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/resources');
      break;

    case 'save_next_submit':
      // Redirecting user to next tab.
      $commands[] = ctools_ajax_command_redirect('/scm/due-diligence');
      break;

    case 'save_duplicate_submit':
      // Case duplicate
      _case_manager_case_duplicate($values['refercase_nid']);
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/resources');
      break;
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

################## Resources section ends #########################




################## Payback section starts #########################
/**
 * Function to get content for preferences page.
 */
function payback_builder_outer() {
  global $user, $company;

  $defaultProjectNid = isset($_SESSION['scm_project_nid']) && !empty($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '';
  if (!empty($defaultProjectNid)) {
    $casenid = _get_scmcase_nids_by_referpronid($defaultProjectNid);
    $casecount = count($casenid);
    $caseswidth = $casecount *400 + 10;
    $elements['scm-casebuilder-start']= array(
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

    foreach ($casenid as $key => $nid) {
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
    $elements['payback_section_' . $nid] = array(
        '#type' => 'container',
    '#attributes' => array('class'=> array('changein-document-popup','caseouter','case_'.$casesr, 'case-continer-'.$nid, $caseStatusCls) ,'original-pos'=>'case_'.$casesr,'updated-pos'=>''),
      );
      $elements['payback_section_' . $nid]['scm-payback-left'] = array(
        '#markup' => drupal_render(drupal_get_form('casemanager_payback_left_form', $casedelta)),
        '#prefix' => '<div class="col-md-4 padding-10 margin-bottom-45 casebuilder-details-left section-top-parent"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );

      $dispaly_none = 'dispaly_none';

      $elements['payback_section_' . $nid]['scm-payback-right'] = array(
        '#markup' => drupal_render(drupal_get_form('casemanager_payback_right_form', $casedelta)),
        '#prefix' => '<div class="' . $commentsclass . ' col-md-8 padding-10 margin-bottom-10 casebuilder-details-right ' . $dispaly_none . '"><div class="clearfix main-scm-casebuilder-form">',
        '#suffix' => '</div></div>',
      );
    }
    $elements['scm-casebuilder-end']= array(
      '#markup' => '</div>',
    );
  }
  
  return $elements;
}

/**
 * Function to get left content of preference page.
 */
function casemanager_payback_left_form($form, &$form_state, $i) {
  $form_state['case_delta'] = $i;
  $form['left_case_section'] = array(
    '#type'       => 'container',
    '#attributes' => array('class'=> array('casebuilder-left-section-container', 'clearfix', 'padding-10')),
    '#prefix'     => '<div id="payback-left-section" class="clearfix">',
    // '#prefix'     => '<div class="preference-left-section clearfix">',
    '#suffix'     => '</div>',
    '#process'    => array('payback_left_section_process'),
  );
  return $form;
}

function payback_left_section_process($elements, &$form_state) {
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
    $query2->condition('caser.bundle','pay_back');
    $query2->condition('caser.field_case_reference_nid',$form_state['case_delta']['refernid']);
    $nodenid = $query2->execute()->fetchColumn(0);
    $case = node_load($nodenid);
    
  }
  
  $hasecase = (isset($case, $case->nid) && !empty($case->nid)?'case-expand':'notcasefound');
  $notcasefound = (isset($case, $case->nid) && !empty($case->nid)?"":'data-trigger="hover" data-toggle="popover"  data-placement="bottom" data-content="Please Save First"');


  $elements['case_nid'] = array(
    '#type' => 'value',
    '#value' => (isset($case, $case->nid) && !empty($case->nid)?$case->nid:''),
  );

  $form_state['case_delta']['case_nid'] = !empty($case->nid) ? $case->nid : '';
  $changeindocument = 'changein-document';  
  $changeindocumentdata = (isset($case, $case->nid) && !empty($case->nid)?'document-save-'.$case->nid:'document-save-new');
  $casetitle = (strlen($form_state['case_delta']['refertitle']) > 26) ? substr($form_state['case_delta']['refertitle'], 0, 23) . '...' : $form_state['case_delta']['refertitle'];
  $caseStatusBtn = '<input id="case-toogle-check-cust" class="case-status-check" type="checkbox" checked data-toggle="toggle" data-on="Active" data-off="Inactive" data-onstyle="success" data-offstyle="danger" for="'.$form_state['case_delta']['refernid'].'">';
  $elements['case_progress_by_section_title'] = array(
    '#markup' => '<div class="clearfix margin-bottom-10 case-section-title case-section-title-sp margin-top-10"><div class="pull-left fixed-case-title" title="'. $form_state['case_delta']['refertitle'] . '">Case ' . $form_state['case_delta']['sr'] . ': ' . $casetitle . '</div><div class="pull-right toggle-case-status-check changein-document-btn">'.$caseStatusBtn.'<i class="fa fa-comments-o '.$hasecase.'" aria-hidden="true" case-status="close" style="cursor: pointer;" '.$notcasefound.'></i></div></div>',
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

  $textarea_label = !empty($_SESSION['scm_label_object']['case_builder']['description']) ? $_SESSION['scm_label_object']['case_builder']['description'] : t('Description');
  $elements['case_description'] = array(
    '#type'   => 'markup',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">' . $textarea_label . '</div><div class="hastextareavalue">',
    '#markup' => $getCaseDesc,
    '#suffix' => '</div></div>',
  );

  $elements['case_nid'] = array(
    '#type'  => 'value',
    '#value' => $form_state['case_delta']['case_nid'],
  );

  // Preference exclusive fields.
  $active = array(1 => t('Green'), 0 => t('Normal'), 2 => t('Red'));

  // Non-Physician Clinicians
  $elements['field_cost_savings_dollars'] = array(
    '#type'          => 'radios',
    '#title'         => t('Will annual expenses exceed 3 million dollars for this case?'),
    '#default_value' => !empty($case->field_cost_savings_dollars['und'][0]['value']) ? $case->field_cost_savings_dollars['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('clinicians','conditional-element')),
    '#prefix'        => '<div documentsave="'.$changeindocumentdata.'" class="clearfix margin-bottom-10 '.$changeindocument.'"><div class="clearfix dashboard-block-heading margin-bottom-10 section-title margin-10">
Cost Savings</div><div class="clearfix"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );

  $elements['field_unspsc_commodity'] = array(
    '#type'          => 'radios',
    '#title'         => t('Has a UNSPSC commodity code been assigned?'),
    '#default_value' => !empty($case->field_unspsc_commodity['und'][0]['value']) ? $case->field_unspsc_commodity['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('a_new_physican','conditional-element')),
    '#prefix'        => '<div class="clearfix"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );
  $elements['field_acquisition_cost'] = array(
    '#type'          => 'radios',
    '#title'         => t('Can the acquisition cost/standardization impact be quantified?'),
    '#default_value' => !empty($case->field_acquisition_cost['und'][0]['value']) ? $case->field_acquisition_cost['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('a_new_physican','conditional-element')),
    '#prefix'        => '<div class="clearfix"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );
  $elements['field_revenue_reimbursement'] = array(
    '#type'          => 'radios',
    '#title'         => t('Are there revenue/reimbursement implications?'),
    '#default_value' => !empty($case->field_revenue_reimbursement['und'][0]['value']) ? $case->field_revenue_reimbursement['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('a_new_physican','conditional-element')),
    '#prefix'        => '<div class="clearfix conditionstatebase"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix'        => '</div></div>',
  );
  $elements['field_identify_payers'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix textfield-type-label"><label>' . t('Identify the Payers') . '</label></div>',
    '#prefix' => '<div class="clearfix conditionstate-one"><div class="clearfix"><div class="tristate-toggle-button pull-right"><div class="clearfix conditionstate-one-alligned">',
    '#suffix' => '</div>',
  );
  $elements['field_pay_back_cost_savings_city'] = array(
    '#type'          => 'textfield',
    '#title'         => t('City'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_pay_back_cost_savings_city['und'][0]['value']) ? $case->field_pay_back_cost_savings_city['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('City')),
    '#prefix'        => '<div class="clearfix margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div>',
  );
  $elements['field_pay_back_costsavingsstate'] = array(
    '#type'          => 'textfield',
    '#title'         => t('State'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_pay_back_costsavingsstate['und'][0]['value']) ? $case->field_pay_back_costsavingsstate['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('State')),
    '#prefix'        => '<div class="clearfix margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div>',
  );
  $elements['field_payer_company_name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Payer Company Name'),
    '#title_display' => 'invisible',
    '#default_value' => !empty($case->field_payer_company_name['und'][0]['value']) ? $case->field_payer_company_name['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element'), 'placeholder' => t('Payer Company Name')),
    '#prefix'        => '<div class="clearfix margin-bottom-4 conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div>',
  );
  $elements['field_drg_codes'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Provide DRG codes.'),
    '#default_value' => !empty($case->field_drg_codes['und'][0]['value']) ? $case->field_drg_codes['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element')),
    '#prefix'        => '<div class="clearfix conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div>',
  );
  $elements['field_cpt_codes'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Provide CPT codes.'),
    '#default_value' => !empty($case->field_cpt_codes['und'][0]['value']) ? $case->field_cpt_codes['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element')),
    '#prefix'        => '<div class="clearfix conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div>',
  );
  $elements['field_hcpcs_codes'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Provide HCPCS codes.'),
    '#default_value' => !empty($case->field_hcpcs_codes['und'][0]['value']) ? $case->field_hcpcs_codes['und'][0]['value'] : '',
    '#attributes'    => array('class' => array('facilities', 'conditional-element')),
    '#prefix'        => '<div class="clearfix conditionstate-one conditionstate-one-alligned">',
    '#suffix'        => '</div></div></div>',
  );

  $field_revenuereimbursement_file = 'field_revenuereimbursement_file';
  $elements['field_revenuereimbursement_file']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $field_revenuereimbursement_file . '][]',
    '#upload_location' => 'public://',   
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$field_revenuereimbursement_file . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$field_revenuereimbursement_file . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#prefix' => '<div class="clearfix te">
                    <div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $previousfilelist = '';
  if(isset($case,$case->field_revenuereimbursement_file['und']) && !empty($case->field_revenuereimbursement_file['und'])){
    $filelist = array();
    foreach ($case->field_revenuereimbursement_file['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_revenuereimbursement_file/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['field_revenuereimbursement_file_link']= array(
    '#markup' => '<label>Revenue/reimbursement attachment</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $field_revenuereimbursement_file . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $field_revenuereimbursement_file . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign . '</div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>
                </div>
              </div>',
  );





  $files_arr = array(
    'field_epsi'                    => '',
    'field_pay_qualityadvisor'      => '',
    'field_contribution_margin_pro' => '',
    'field_payer_mix_report'        => '',
    'field_spend_report'            => '',
    'field_pay_spend_report'        => '',
    'field_spend_report_documents'  => '',
    'field_utilization_report'      => '',
  );
  foreach ($files_arr as $key => $value) {
    if (!empty($case->{$key}['und'])) {
      $filelist = array();
      foreach ($case->{$key}['und'] as $key1 => $value1) {
        $file_url = file_create_url($value1['uri']);
        //$filelist[] = l($value1['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE));
        $filelist[] = '<div class="clearfix filefid-'.$value1['fid'].'">'.l($value1['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/' . $key . '/'.$case->nid.'/'.$key1.'/'.$value1['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
      }
      $files_arr[$key] = !empty($filelist) ? implode('', $filelist) : '';
    }
  }

  $labels_array = array(
    'field_epsi'                    => t('Attach EPSI documents.'),
    'field_pay_qualityadvisor'      => t('Attach QualityAdvisor documents.'),
    'field_contribution_margin_pro' => t('Attach Contribution Margin Pro Forma documents.'),
    'field_payer_mix_report'        => t('Attach Payer Mix Report documents.'),
    'field_pay_back_use'            => t('Does every Entity Use it?'),
    'field_spend_report'            => t('Attach Spend Report documents for these entities.'),
    'field_department_one'          => t('Is this used in more than 1 (one) department?'),
    'field_pay_spend_report'        => t('Attach Spend Report documents associated with these departments.'),
    'field_continuum_care'          => t('Is it used across the continuum of care?'),
    'field_spend_report_documents'  => t('Attach Spend Report documents.'),
    'field_utilization_improvement' => t('Can utilization improvement opportunity be quantified?'),
    'field_utilization_report'      => t('Attach Utilization Report documents.')
  );

  $fields_array = array_keys($labels_array);

  for ($i = 0; $i <= 10; $i++) {
    if (in_array($i, array(4,6,8, 10))) {
      // 4 fields are radio fields.
      $elements[$fields_array[$i]] = array(
        '#type'          => 'radios',
        '#title'         => $labels_array[$fields_array[$i]],
        '#default_value' => !empty($case->{$fields_array[$i]}['und'][0]['value']) ? $case->{$fields_array[$i]}['und'][0]['value'] : 0,
        '#options'       => $active,
        '#attributes'    => array('class'=>array('a_new_physican','conditional-element')),
        '#prefix'        => '<div class="clearfix"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
        '#suffix'        => '</div></div>',
      );
    }
    else {
      // 7 fields are file fields.

      // Changing upload sign, if a file already exists.
      $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
      if (!empty($files_arr[$fields_array[$i]])) {
        $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
      }

      $elements[$fields_array[$i]]= array(
       '#type'            => 'file',
       '#title'           => 'Attachment',
       '#name'            => 'files[' . $fields_array[$i] . '][]',
       '#upload_location' => 'public://',
       
       '#attributes'      => array('multiple' => 'multiple', 'id' => $form_state['case_delta']['refernid'] . '-' .$fields_array[$i] . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$fields_array[$i] . '")','class'=> array('scm-my-request-attachment','conditional-element')),
       '#prefix'          => '<div class="clearfix form-item" style="display:none;">',
       '#suffix'          => '</div>',
      );

      $elements[$fields_array[$i] . '_link']= array(
        '#markup' => '<label>' . $labels_array[$fields_array[$i]] . '</label><a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $fields_array[$i] . '-id"><i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i></a>
        <div class="previous-file-list">' . $files_arr[$fields_array[$i]] . '</div>
        <div id="'.$form_state['case_delta']['refernid'] . '-' . $fields_array[$i] . '-id-filelist" style="display:none;"></div>',
        '#prefix' => '<div class="clearfix"><div class="pull-left tristate-icon">' . $upload_sign. '</div><div class="tristate-toggle-button pull-right">',
        '#suffix' => '</div></div>',
      );
    }
  }

  
  //new add start
  $elements['doesit_have_udi'] = array(
    '#type'          => 'radios',
    '#title'         => t('Does it have UDI?'),
    '#default_value' => !empty($case->field_does_it_have_udi['und'][0]['value']) ? $case->field_does_it_have_udi['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('conditional-element')),
    '#prefix' => '<div class="clearfix"><div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
    
  );  

  $field_doesit_have_udi_file = 'field_doesit_have_udi_file';
  $elements['field_doesit_have_udi_file']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $field_doesit_have_udi_file . '][]',
    '#upload_location' => 'public://',   
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$field_doesit_have_udi_file . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$field_doesit_have_udi_file . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-two">
                    <div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $previousfilelist = '';
  if(isset($case,$case->field_doesit_have_udi_file['und']) && !empty($case->field_doesit_have_udi_file['und'])){
    $filelist = array();
    foreach ($case->field_doesit_have_udi_file['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_doesit_have_udi_file/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['field_doesit_have_udi_file_link']= array(
    '#markup' => '<label>Upload attachment</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $field_doesit_have_udi_file . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $field_doesit_have_udi_file . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign . '</div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>
                </div>
              </div>',
  );
  $elements['doesit_have_gtin'] = array(
    '#type'          => 'radios',
    '#title'         => t('Does it have GTIN?'),
    '#default_value' => !empty($case->field_does_it_have_gtin['und'][0]['value']) ? $case->field_does_it_have_gtin['und'][0]['value'] : 0,
    '#options'       => $active,
    '#attributes'    => array('class'=>array('conditional-element')),
    '#prefix' => '<div class="clearfix"><div class="clearfix conditionstate-one"><div class="pull-left tristate-icon"><i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i></div><div class="tristate-toggle-button pull-right">',
    '#suffix' => '</div></div>',
    
  );  

  $field_doesit_have_gtin_file = 'field_doesit_have_gtin_file';
  $elements['field_doesit_have_gtin_file']= array(
    '#type' => 'file',
    '#title' => 'Attachment',
    '#name' => 'files[' . $field_doesit_have_gtin_file . '][]',
    '#upload_location' => 'public://',   
    '#attributes'      => array('multiple' => 'multiple','id' => $form_state['case_delta']['refernid'] . '-' .$field_doesit_have_gtin_file . '-id', 'onchange' => 'javascript:updateListNew("' . $form_state['case_delta']['refernid'] . '-' .$field_doesit_have_gtin_file . '")','class'=> array('scm-my-request-attachment','conditional-element')),
    '#prefix' => '<div class="clearfix conditionstate-two">
                    <div class="clearfix form-item" style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $previousfilelist = '';
  if(isset($case,$case->field_doesit_have_gtin_file['und']) && !empty($case->field_doesit_have_gtin_file['und'])){
    $filelist = array();
    foreach ($case->field_doesit_have_gtin_file['und'] as $key => $value) {
      $file_url = file_create_url($value['uri']);
      $filelist[] = '<div class="clearfix filefid-'.$value['fid'].'">'.l($value['filename'], $file_url, array('attributes' => array('target'=>'_blank'), 'external' => TRUE)).l('<i class="fa fa-trash-o text-muted" aria-hidden="true"></i>', '/filerowremove/field_doesit_have_gtin_file/'.$case->nid.'/'.$key.'/'.$value['fid'].'/nojs', array('external'=>TRUE,'html' => TRUE,'attributes' => array('class'=>array('pull-right','use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'</div>';
    }
    $previousfilelist = (isset($filelist) && !empty($filelist))?implode('', $filelist):'';
  }
  // Changing upload sign, if a file already exists.
  $upload_sign = '<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028 ;"></i>';
  if (!empty($previousfilelist)) {
    $upload_sign = '<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>';
  }
  $elements['field_doesit_have_gtin_file_link']= array(
    '#markup' => '<label>Upload attachment</label>
                  <a href="javascript:void(0);" class="pull-right scm-my-request-attachment-link-new" data="' . $form_state['case_delta']['refernid'] . '-' . $field_doesit_have_gtin_file . '-id">
                    <i class="fa fa-2x fa-upload text-muted" aria-hidden="true"></i>
                  </a>
                  <div class="previous-file-list">'.$previousfilelist.'</div>
                  <div id="'.$form_state['case_delta']['refernid'] . '-' . $field_doesit_have_gtin_file . '-id-filelist" style="display:none;"></div>',
    '#prefix' => '
                    <div class="clearfix">
                      <div class="pull-left tristate-icon">' . $upload_sign . '</div>
                      <div class="tristate-toggle-button pull-right">',
    '#suffix' =>    '</div>
                  </div>
                </div>
              </div>',
  );
  //new add check box end
  $elements['field_cost_savings_dollars_suffix'] = array(
    '#markup' => '</div>',
  );
  // Delete save and next section.
  $elements['left_section_delete'] = array(
    '#type'   => 'markup',
    '#markup' => l('<input type="button" value="Delete" class="form-submit">', url('deletenode/nojs/' . $form_state['case_delta']['refernid']), array('query'=>array('redirect_node_url'=>current_path()), 'external'=>TRUE,'html' => TRUE, 'attributes'=> array('class'=>array('ctools-modal-assign-dashboard-popup-style ctools-use-modal'))) ), 
    '#prefix' => '<div class="clearfix margin-bottom-10 case-button-outer">',
  );
  $elements['left_section_cancel'] = array(
    '#type'   => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit">',
  );

  $elements['left_section_save_and_duplicate_case'] = array(
    '#type'       => 'button',
    '#title'      => 'left_section',
    '#name'       => 'save_duplicate_submit',
    '#value'      => t('Save and Duplicate Case'),
    '#ajax'       => array(
      'callback' => 'payback_case_submit_callback',
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
        'callback' => 'payback_case_submit_callback',
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
                      <li><a href="javascript:void(0);" class="save-duplicate-case">Save and Duplicate Case</a></li>
                    </ul>
                  </div>
                  </div>
                ',
  );

  return $elements;
}

/**
 * Function to get right content of preference page.
 */
function casemanager_payback_right_form($form, &$form_state, $i) {
  $form_state['case_delta'] = $i;

  // This variable shall be used to fetch correct data for the respective tab.
  $form_state['on_tab'] = 'pay_back';

  $form['project_manager_comments'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('project-manager-comments-container','clearfix','padding-10')),
    '#prefix' => '<div id="project-manager-comments-container" class="clearfix">',
    '#suffix' => '</div>',
    '#process' => array('project_manager_comments_process_secondary'),
  );
  return $form;
}

/**
 * Ajax submit callback for payback left form.
 */
function payback_case_submit_callback($form, &$form_state) { 
  // Cleaning form_state.
  form_state_values_clean($form_state);

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

  if (!empty($values['case_nid'])) {
    // This is the case when we are updating an old node.
    $node = node_load($values['case_nid']);
  }
  else {
    // This is the case when a new node is to be created.
    $node = _node_creation_call('pay_back', $values['refercase_title']);
  }

  // As now we have a node, proceding further.

  // Saving references.
  $node->field_project_reference[LANGUAGE_NONE][0]['nid'] = !empty($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '';
  $node->field_case_reference[LANGUAGE_NONE][0]['nid'] = !empty($values['refercase_nid']) ? $values['refercase_nid'] : '';
  // Initial description.
  $node->field_pay_back_subtitle[LANGUAGE_NONE][0]['value'] = $values['case_description'];
  $node->field_does_it_have_udi[LANGUAGE_NONE][0]['value'] = $values['doesit_have_udi'];
  $node->field_does_it_have_gtin[LANGUAGE_NONE][0]['value'] = $values['doesit_have_gtin'];

  unset($values['refercase_nid'], $values['refercase_title'], $values['case_nid'], $values['case_description']);
 
  $files_arr = array('field_revenuereimbursement_file','field_epsi','field_pay_qualityadvisor','field_contribution_margin_pro', 'field_payer_mix_report', 'field_spend_report', 'field_pay_spend_report', 'field_spend_report_documents', 'field_utilization_report','field_doesit_have_udi_file','field_doesit_have_gtin_file');

  
  // First handling files.
  foreach ($files_arr as $key => $value) {
    if (!empty($values[$value])) {
      foreach ($values[$value] as $key1 => $value1) {
        $new_file = file_load($value1->fid);
        $file_arr = (array)$new_file;
        $file_arr['display'] = 1;
        $node->{$value}[LANGUAGE_NONE][] = $file_arr;
      }
    }
    // unsetting the element.

    unset($values[$value]);
  }
  if(!$values['doesit_have_udi']){
    $node->field_doesit_have_udi_file = '';
  } 
  if(!$values['doesit_have_gtin']){
    $node->field_doesit_have_gtin_file = '';
  }

  // Now saving other fields.
  foreach ($values as $key => $value) {
    $textfields = array('field_identify_payers', 'field_pay_back_cost_savings_city', 'field_pay_back_costsavingsstate', 'field_payer_company_name', 'field_drg_codes', 'field_cpt_codes', 'field_hcpcs_codes');

    $empty_val = in_array($key, $textfields) ? '' : 0;
    $node->{$key}[LANGUAGE_NONE][0]['value'] = !empty($value) ? $value : $empty_val;
  }

  // Finally saving the node.
  node_save($node);


  switch ($form_state['triggering_element']['#name']) {
    case 'save_submit':
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/payback');
      break;

    case 'save_duplicate_submit':
      // Case duplicate
    
      _case_manager_case_duplicate($form_state['case_delta']['refernid']);
      // Redirecting user on same tab.
      $commands[] = ctools_ajax_command_redirect('/scm/payback');
      break;
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}


function facilities_contact_children_process($elements, &$form_state) {
  // Storing count in elements, so as to use it in theme function.
  $elements['#storage_contacts'] = $form_state['contacts_count'];
  $contacts_default_values = $form_state['contacts_default_values'];
  foreach ($form_state['contacts_count'] as $key => $uniqid) {  
    $elements['facilities_first_name'][$uniqid] = array(
      '#type' => 'textfield',
      '#title'         => t('Facilities First Name'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($contacts_default_values[$uniqid]['fcfname']) ? $contacts_default_values[$uniqid]['fcfname'] : '',
      '#attributes' => array('class' => array('facilities-first-name'), 'placeholder' => t('First Name')),      
      '#parents' => array('facilitiescontact', $uniqid, 'facilities_first_name'),
      '#prefix' => '<div class="tristate-toggle-button pull-right"><div class="row margin-5 conditionstate-one conditionstate-one-alligned"><div class="col-md-6 padding-5 margin-bottom-4">',
      '#suffix'        => '</div>',
    );
    $elements['facilities_last_name'][$uniqid] = array(
      '#type' => 'textfield',
      '#title'         => t('Facilities Last Name'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($contacts_default_values[$uniqid]['fclname']) ? $contacts_default_values[$uniqid]['fclname'] : '',
      '#attributes' => array('class' => array('facilities-last-name'), 'placeholder' => t('Last Name')),      
      '#parents' => array('facilitiescontact', $uniqid, 'facilities_last_name'),
      '#prefix'        => '<div class="col-md-6 padding-5 margin-bottom-4 conditionstate-one-alligned">',
      '#suffix'        => '</div></div>',
    );
    $elements['facilities_email'][$uniqid] = array(
      '#type' => 'textfield',
      '#title'         => t('Facilities Email Address'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($contacts_default_values[$uniqid]['fcmail']) ? $contacts_default_values[$uniqid]['fcmail'] : '',
      '#attributes' => array('class' => array('facilities-mail-address'), 'placeholder' => t('Email Address')),      
      '#parents' => array('facilitiescontact', $uniqid, 'facilities_email'),
      '#prefix'        => '<div class="clearfix conditionstate-one">',
    '#suffix'        => '</div>',
    );
    $delete_link = l(decode_entities('&#xf014;'), 'javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('remove-vendor-row-link'), 'style' => 'font-family:FontAwesome;')));
    $elements['remove'][$uniqid] = array(
      '#type' => 'submit',
      '#value' => 'remove_facilitiescontact',
      '#name' => $uniqid,
      '#attributes'=> array('class'=>array('remove-vendor-row', 'workflow-physicians-submit','hidden')),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_contacts_count_submit_handler'),
      '#ajax' => array(
        'callback' => 'remove_contacts_count_row_callback',
        'wrapper'  => 'facilities-contact-children-edit-' . $form_state['case_delta']['refernid'],
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
      '#parents' => array('facilitiescontact', $uniqid, 'remove'),
      '#prefix' => '<div class="clearfix margin-top-10 margin-bottom-10"><div class="pull-left">' . $delete_link,
      '#suffix' => '</div></div></div>',
    );
  }
  // Adding a add new button for the above section.
  $elements['facilitiescontact_add_new_row'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    '#name' => 'facilitiescontact_add_new_row',
    '#attributes'=> array('class'=>array('facilitiescontact-add-new-row-button'),'title'=>'Add New Contact'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('facilitiescontact_add_new_row_submit'),
    '#ajax' => array(
      'callback' => 'facilitiescontact_add_new_row_callback',
      'wrapper' => 'facilities-contact-children-edit-' . $form_state['case_delta']['refernid'],
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="clearfix hidden">',
    '#suffix' => '</div>',
  );

  return $elements;
}


/**
 * Theme process for resources Contact(s).
 */
function theme_facilities_contact_children_theme($variables) {
  $element = $variables['form'];
  $storage = $element['#storage_contacts'];
  $output = '';

  foreach ($storage as $key => $uniqid) { 
    $output .= drupal_render($element['facilities_first_name'][$uniqid]);
    $output .= drupal_render($element['facilities_last_name'][$uniqid]);
    $output .= drupal_render($element['facilities_email'][$uniqid]);   
    $output .= drupal_render($element['remove'][$uniqid]);
  }

  $output .= drupal_render_children($element);
  return $output;
}

/**
 * Ajax callback for adding a new resources Contact(s).
 */
function facilitiescontact_add_new_row_callback($form, &$form_state) {
  return $form['left_case_section']['facilities_contact_children'];
}

/**
 * Submit callback for adding a new resources Contact(s).
 */
function facilitiescontact_add_new_row_submit($form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];
  if($triggerElement['#name'] =='facilitiescontact_add_new_row'){
    $tempIdentifer = uniqid();
    $form_state['contacts_count'][]  = $tempIdentifer;
    $form_state['get_node_count2'] = FALSE;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for remove resources Contact(s).
 */
function remove_contacts_count_row_callback($form, &$form_state) {
  return $form['left_case_section']['facilities_contact_children'];
}

/**
 * Submit callback for remove resources Contact(s).
 */
function remove_contacts_count_submit_handler($form, &$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];

  if (isset($form_state['contacts_count'])) {
    foreach ($form_state['contacts_count'] as $key => $value) {
      if ($form_state['contacts_count'][$key] == $identifier) {
        unset($form_state['contacts_count'][$key]);
        if (array_key_exists($identifier, $form_state['contacts_default_values'])) {
          unset($form_state['contacts_default_values'][$identifier]);
        }
      }
    }
    $form_state['get_node_count2'] = FALSE;
  }

  // We need to check that we atleast have a blank set for user.
  $physicians_count = $form_state['contacts_count'];
  $last_pc = end($physicians_count);

  if (!empty($form_state['input']['facilitiescontact'][$last_pc]['contacts_default_values'])) {
    $form_state['contacts_count'][] = uniqid();
  }

  $form_state['rebuild'] = TRUE;
}