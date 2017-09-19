<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_project_scorecard_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements = array();
  $projecttab = scorecard_tab_settings();
  $elements['scm-setting-menu-items'] = array(
    '#markup' => scm_setting_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
    '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
  );
  $elements['container_tab'] = array(
    '#markup' =>drupal_render($projecttab),
  );
  
  return $elements;
}

/*
 * project tab container for 
 * Generating project setting form
 */
function scorecard_tab_settings() {  
  $elements = array();
  $elements['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','row','scm-setting-full-item','margin-10')),
  );    
  $elements['main-container']['scorecard-category-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Category'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('collapsible')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['scorecard-category-fieldset']['scorecard-category-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_scorecard_category_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );  
  $elements['main-container']['scorecard-question-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Question By Category'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('collapsible', 'collapsed')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $getCatForm = drupal_get_form('scm_scorecard_question_settings_form');
  $elements['main-container']['scorecard-question-fieldset']['scorecard-question-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render($getCatForm),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );  
  $elements['main-container']['remove-setting-div'] = array(
    '#markup' => '',
    '#prefix' => '<div id="scm-option-remove">',
    '#suffix' => '</div><div class="remove-data-details" style="display:none"><span class="remove-data-details-service"></span><span class="remove-data-details-name"></span></div>',
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

/*
 *scm request type setting form
 */
function scm_scorecard_category_settings_form($form, &$form_state) {
  $type = 'scorecard_category';
  $render_data = _get_or_insert_scm_settings($type);
  $form['get-scorecard-cat-settings-reset'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control get-scorecard-cat-settings-reset')),
    '#ajax' => array(
      'callback'=> 'change_scorecard_cat_settings_callback',
      'wrapper' => 'scm-scorecard-question-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div id="scm-project-type-settings-formwrap"><div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
   $form['get-scorecard-cat-delete'] = array(
    '#type' => 'select',
    '#options' => $render_data,
    '#attributes' => array('class'=> array('form-control get-scorecard-cat-delete')),
    '#ajax' => array(
      'callback'=> 'change_scorecard_cat_settings_del_callback',
      'wrapper' => 'scm-scorecard-category-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" id="get-scorecard-cat-deleteID" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );

  $form['scorecard-category-data'] = array(
    '#type' => 'markup',
    '#markup' => rendercat_setting_list($type,$render_data),
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['scorecard-category-new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Category'),
    '#attributes' => array('class'=>array('scorecard-category-new'),'placeholder' => t('Please enter new scorecard category here.')),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_scorecard_category_settings_form_submit_callback',
      'wrapper' => 'scm-scorecard-category-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#suffix' => '</div>',
  );
  return $form;
}

/*
 * Ajax submit callback for 
 * Submitting project type setting form
 */
function scm_scorecard_category_settings_form_submit_callback($form, &$form_state) { 
  if(form_get_errors()){
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'scorecard_category';
  $new_value['scorecard-category-new'] = strtolower(trim($values['scorecard-category-new']));
  if(isset($values['set_add_item']) && !empty($values['set_add_item'])) {
    $new_value['set_add_item'] = $values['set_add_item'];  
  } 
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('scorecard-category-new', t('Please enter cateogry name!'));
  }
  if ($error) {
    return $form;
  }
  //$new_value = strtolower(trim($new_value));
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['scorecard-category-new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['scorecard-category-new']) && !empty($values) && !empty($new_value['scorecard-category-new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $commands = array();
  $commands[] = ajax_command_invoke('.scorecard-category-new', 'val', array(''));
  $commands[] = ajax_command_html("#get-scorecard-cat-deleteID",render($form['get-scorecard-cat-delete']));
  $commands[] = ajax_command_html("#".$type."-data-div", rendercat_setting_list($type,$save_new_setting), array());
  $commands[] = ajax_command_invoke("select.get-scorecard-questio-settings-reset", 'trigger',array('change'));
  $commands[] = ajax_command_invoke("select.get-scorecard-cat-settings-reset", 'trigger',array('change'));
  return array('#type' => 'ajax', '#commands' => $commands);
}


function change_scorecard_cat_settings_callback($form, &$form_state) {
  $commands = array();
  $type = 'scorecard_category';
  $render_data = _get_or_insert_scm_settings($type);
  $commands[] = ajax_command_html("#".$type."-data-div", rendercat_setting_list($type,$render_data), array());
  $commands[] = ajax_command_html("#get-scorecard-cat-deleteID",render($form['get-scorecard-cat-delete']));
  return array('#type' => 'ajax', '#commands' => $commands);
}
function change_scorecard_cat_settings_del_callback($form, &$form_state) {
  $commands = array();
  $type = 'scorecard_category';
  if($form_state['triggering_element']['#name']=='get-scorecard-cat-delete'){
    db_delete('m6connect_scm_category_setting')
    ->condition('id', $form_state['triggering_element']['#value'])
    ->execute();
    $render_data = _get_or_insert_scm_settings($type);
    $commands[] = ajax_command_invoke('.scorecard-category-new', 'val', array(''));
    $commands[] = ajax_command_html("#".$type."-data-div", rendercat_setting_list($type,$render_data), array());
    $commands[] = ajax_command_invoke("select.get-scorecard-questio-settings-reset", 'trigger',array('change'));
    $commands[] = ajax_command_invoke("select.get-scorecard-cat-settings-reset", 'trigger',array('change'));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}




function scm_scorecard_question_settings_form($form, &$form_state) {
  /*
   * Initialize add new product form state
   */
  global $user, $company;
  if(empty($form_state['invite_m6_storage_scorecard'])){
    $tempIdentifer = uniqid();
    $form_state['invite_m6_storage_scorecard'][]  = $tempIdentifer;
  }
  $querydel = db_select('m6connect_scm_scorecard_question', 'n');
  $querydel->fields('n',array('id'));
  $querydel->condition('n.company_nid', $company->nid, '=');
  $delresult = $querydel->execute()->fetchAllKeyed(0,0);
  $form['get-scorecard-questio-settings-reset'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control get-scorecard-questio-settings-reset')),
    '#ajax' => array(
      'callback'=> 'change_scorecard_question_settings_callback',
      'wrapper' => 'scm-scorecard-question-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get-scorecard-questio-settings-delete'] = array(
    '#type' => 'select',
    '#options' => $delresult,
    '#attributes' => array('class'=> array('form-control get-scorecard-questio-settings-delete')),
    '#ajax' => array(
      'callback'=> 'change_scorecard_question_settings_delete_callback',
      'wrapper' => 'scm-scorecard-question-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );

  $form['get-scorecard-questio-settings-edit'] = array(
    '#type' => 'select',
    '#options' => $delresult,
    '#attributes' => array('class'=> array('form-control get-scorecard-questio-settings-edit')),
    '#ajax' => array(
      'callback'=> 'change_scorecard_question_settings_edit_callback',
      'wrapper' => 'scm-scorecard-question-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get_question_conatiner'] = array(
    '#type'       => 'container',
    '#theme'      => 'invite_m6_theme_scorecard_question',
    '#attributes' => array('class'=>array('alert-container-section')),
    '#prefix'     => '<div class="clearfix" id="main-class"><div id="alert-container-section" class="add-new-alert-detail">', 
    '#suffix'     => '</div></div>',
    '#process'    => array('invite_to_m6_process_scorecard_question'),
    // '#prefix' => '<div id="scm-scorecard-question-settings-form-process">',
    // '#suffix' => '</div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Question(s)'),
	'#prefix' => '<div class="margin-top-10">',
	'#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'scm_scorecard_question_form_submit_callback',
      'wrapper' => 'scm-scorecard-question-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['category-data-table-section'] = array(
    '#type' => 'markup',
    '#markup' => drupal_render(get_table_question_setting()),
    '#prefix' => '<div id="get-table-question-setting-data-div" class="clearfix margin-top-10">',
    '#suffix' => '</div>',
  );
  return $form;
}

function scm_scorecard_question_settings_form_submit($form, &$form_state) {
  if(form_get_errors()){
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $alert = $values['alert'];  
  
    $tempIdentifer = uniqid();
    $form_state['invite_m6_storage_scorecard']  = array($tempIdentifer);
    $form_state['rebuild'] = TRUE;
    foreach ($alert as $key => $alert_detail) {
    $milestoneData= array(
      'uid' => $user->uid,
      'company_nid' => $company->nid,
      'category_id' => $alert_detail['scorecard-category'],
      'question' => $alert_detail['scorecard-question'],
    );
    db_insert('m6connect_scm_scorecard_question')->fields($milestoneData)->execute();     
  }
}

function scm_scorecard_question_form_submit_callback($form, &$form_state) {
  if(form_get_errors()){
    return $form;
  }
  global $user, $company;
  $commands = array();
  $commands[] = ajax_command_invoke("input.scorecard-question",'val',array(''));
  $commands[] = ajax_command_invoke("select.scorecard-category",'val',array(''));
  $commands[] = ajax_command_html("#get-table-question-setting-data-div", drupal_render(get_table_question_setting()), array());
   $commands[] = ajax_command_html("#alert-container-section",drupal_render($form['get_question_conatiner']));
  return array('#type' => 'ajax', '#commands' => $commands);
}
function change_scorecard_question_settings_edit_callback($form, &$form_state) {
  $commands = array();
  $type = 'scorecard_category';
  if($form_state['triggering_element']['#name']=='get-scorecard-questio-settings-edit') {
    global $user, $company;
    $query = db_select('m6connect_scm_scorecard_question', 'n');
    $query->fields('n');
    $query->condition('n.id', $form_state['triggering_element']['#value'], '=');
    $query->condition('n.company_nid', $company->nid, '=');
    $result = $query->execute()->fetchObject();
    $commands[] = ajax_command_invoke('input.questionhidden', 'val', array($result->id));
    $commands[] = ajax_command_invoke('input.scorecard-question-update', 'val', array($result->question));
    $commands[] = ajax_command_invoke('select.scorecard-category-update', 'val', array($result->category_id));
    $commands[] = ajax_command_invoke('#updateboxpopup', 'show');
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scorecard_question_settings_delete_callback($form, &$form_state){
  $commands = array();
  $type = 'scorecard_category';
  if($form_state['triggering_element']['#name']=='get-scorecard-questio-settings-delete'){
    db_delete('m6connect_scm_scorecard_question')
    ->condition('id', $form_state['triggering_element']['#value'])
    ->execute();
    $commands[] = ajax_command_html("#get-table-question-setting-data-div", drupal_render(get_table_question_setting()), array());
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}





function change_scorecard_question_settings_callback($form, &$form_state) {
  $commands = array();
  $commands[] = ajax_command_html("#alert-container-section",render($form['get_question_conatiner']));
  return array('#type' => 'ajax', '#commands' => $commands);
}  

function theme_invite_m6_theme_scorecard_question($variables) {
  $element = $variables['form'];
  $storage = $element['#storage'];
  $output = '';
  $header = array('No.','Question', 'Category', '');
  $rowNo = 1;
  foreach ($storage as $key => $uniqId) {
    $rows[] = array(
      'data'=> array(
	    array('data' => drupal_render($element['serial-no'][$uniqId]),'class'=> array('col-md-1')),
        array('data' => drupal_render($element['scorecard-question'][$uniqId]),'class'=> array('col-md-7')),
        array('data' => drupal_render($element['scorecard-category'][$uniqId]),'class'=> array('col-md-3')),
        array('data' => drupal_render($element['remove'][$uniqId]), 'class' => array('workflow-remove-td','col-md-1')),
      ),
    );
  }
  $rows[] = array(
    'data' => array(
      array('data'=>drupal_render($element['workflow_add_new_row']),'colspan' => 4),
    ),
  );

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes'=> array('class'=> array('scm-product-item-table','table','table-hover','m6connect-custom-table','m6connect-table-border'))));
  $output .= drupal_render_children($element);
  return $output;
}

function invite_to_m6_process_scorecard_question($element, &$form_state) {
  global $company;
  $form['#attached']['js'][] = array(
    'data'=>drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js',
    'type'=>'file'
  );
  /*
   * Getting the category for questions
   */
  $query = db_select('m6connect_scm_category_setting','cat');
  $query->fields('cat', array('id','title'));
  $query->condition('cat.type','scorecard','=');
  $query->condition('cat.nid', $company->nid, '=');
  $getCat = $query->execute()->fetchAllKeyed(0,1);
  $storage = $form_state['invite_m6_storage_scorecard'];
  $element['#storage'] = $storage;
  $i = 1;
  foreach ($storage as $key => $uniqId) {	  
    $element['serial-no'][$uniqId] = array( 
	  '#type' => 'textfield',
	  '#value' => $i,
	  '#disabled' => TRUE, 
	  '#attributes' => array('class'=>array('form-control','workflow-auto','serial-no')),
	  '#parents'    => array('alert',$uniqId,'serial-no'),
    );
	$element['scorecard-question'][$uniqId] = array( 
	  '#type' => 'textfield',
	  '#attributes' => array('class'=>array('form-control','workflow-auto','scorecard-question')),
	  '#parents'    => array('alert',$uniqId,'scorecard-question'),
    '#required' => TRUE,
    );
	$element['scorecard-category'][$uniqId] = array( 
	  '#type' => 'select',
	  '#options' => array_map('ucwords', $getCat),
	  '#empty_option' => 'Choose Category',
	  '#attributes' => array('class'=>array('form-control','workflow-auto','scorecard-category')),
	  '#parents'    => array('alert',$uniqId,'scorecard-category'),
    '#required' => TRUE,
    );
	$element['remove'][$uniqId] = array(
      '#type'       => 'submit',
      '#value'      => decode_entities('&#xf014;'),
      '#name'       => $uniqId,	  
      '#attributes' => array('style'=> array('font-family:FontAwesome;'),'class'=>array('alert-container-section', 'workflow-remove-submit')),
      '#parents'    => array('alert', $uniqId, 'remove'),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_question_row_handler'),
      '#ajax' => array(
        'callback' => 'remove_m6_scorecard_row_callback',
        'wrapper' => 'alert-container-section',
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
    );
    if(isset($form_state['po_storage_default_value'][$uniqId])) {
      $stdefault = $form_state['po_storage_default_value'][$uniqId];
      $element['scorecard-question'][$uniqId]['#default_value'] = $stdefault['manufacturerProduct'];
      $element['scorecard-category'][$uniqId]['#default_value'] = $stdefault['productNumber'];      
    }
	$i++;
  }

  $element['workflow_add_new_row'] = array(
    '#type'=>'submit',
    '#value' => 'Add Another Question',
    '#name' => 'workflow_add_new_row',
    '#attributes'=> array('class'=>array('routing-workflow-action','product-workflow-action-add-details'),'title'=>'Add New Detail'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('add_new_row_submit_handler_scorecard'),
    '#ajax' => array(
      'callback' => 'add_new_row_scorecard_action_callback',
      'wrapper' => 'alert-container-section',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
  );  
  return $element;
}

function remove_m6_scorecard_row_callback(&$form, &$form_state) {
  return $form['get_question_conatiner'];
}

function remove_question_row_handler(&$form,&$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];
  if(isset($form_state['invite_m6_storage_scorecard'])){
    foreach ($form_state['invite_m6_storage_scorecard'] as $key => $value) {
      if($form_state['invite_m6_storage_scorecard'][$key] == $identifier){
        unset($form_state['invite_m6_storage_scorecard'][$key]);
        unset($form_state['po_storage_default_value'][$identifier]);
      } 
    }             
  }   
  $form_state['rebuild'] = TRUE;
}
function add_new_row_scorecard_action_callback(&$form, &$form_state) {
  return $form['get_question_conatiner'];
}

function add_new_row_submit_handler_scorecard(&$form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];
  if($triggerElement['#name'] =='workflow_add_new_row'){
    $tempIdentifer = uniqid();
    $form_state['invite_m6_storage_scorecard'][]  = $tempIdentifer;
  }
  
  $form_state['rebuild'] = TRUE;
  return $form;
}

function rendercat_setting_list($type,$render_data){
    $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
    foreach ($render_data as $keyrender => $renderdata) {
      $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . ucwords($renderdata) . ' <span><i class="fa fa-times remove-scm-setting-options" deletedataref="'.$keyrender.'" aria-hidden="true" scm-type="'.$type.'" data="' . ucwords($renderdata) . '" fortitle="' . ucwords($renderdata) . '"></i></span></div>';
    }
    $setting_render_data .= '</div>';
    return $setting_render_data;
}