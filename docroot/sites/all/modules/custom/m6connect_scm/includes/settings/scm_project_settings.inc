<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_project_configure_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements = array();
  $projecttab = project_tab_settings();
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
function project_tab_settings() {  
  $elements = array();
  $elements['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-5','col-sm-5','col-xs-5','row','scm-setting-full-item','margin-10')),
  );  
  /*$elements['main-container']['project-entity-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Project Entity'),
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
  $elements['main-container']['project-entity-fieldset']['project-entity-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_entity_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['category-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Category'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['category-fieldset']['category-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_category_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['sub-category-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sub Category'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['sub-category-fieldset']['sub-category-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_sub_category_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );*/
  $elements['main-container']['project-type-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Project Type'),
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
  $elements['main-container']['project-type-fieldset']['project-type-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_type_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['project-status-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Project Status'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['project-status-fieldset']['project-status-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_status_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['project-approval-status-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Approval Status'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['project-approval-status-fieldset']['project-approval-status-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_approval_status_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['project-department-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Department'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['project-department-fieldset']['project-department-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_project_department_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['remove-setting-div'] = array(
    '#markup' => '',
    '#prefix' => '<div id="scm-option-remove">',
    '#suffix' => '</div><div class="remove-data-details" style="display:none"><span class="remove-data-details-service"></span><span class="remove-data-details-name"></span></div>',
  );
  return $elements;
}

/*
 *scm request type setting form
 */
function scm_project_type_settings_form($form, &$form_state) {
  $type = 'project_type';
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['project-type-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['project_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new project type'),
    '#attributes' => array('class'=>array('project_type_new'),'placeholder' => t('Please enter new project type here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_type_settings_form_submit_callback',
      'wrapper' => 'scm-project-type-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/*
 * Ajax submit callback for 
 * Submitting project type setting form
 */
function scm_project_type_settings_form_submit_callback($form, &$form_state) { //pre($form_state['values'],1);
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_type';
  $new_value['project_type_new'] = trim($values['project_type_new']);
  if(isset($values['set_add_item']) && !empty($values['set_add_item'])) {
    $new_value['set_add_item'] = $values['set_add_item'];  
  } 
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('project_type_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  //$new_value = strtolower(trim($new_value));
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['project_type_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['project_type_new']) && !empty($values) && !empty($new_value['project_type_new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm project status setting form
 */
function scm_project_status_settings_form($form, &$form_state) {  
  $type = 'project_status';  
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['project-status-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['project_status_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new project status'),
    '#attributes' => array('class'=>array('project_status_new'),'placeholder' => t('Please enter new project status here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_status_settings_form_submit_callback',
      'wrapper' => 'scm-project-status-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/* 
 * Ajax submit callback for project status form
 */
function scm_project_status_settings_form_submit_callback($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_status';
  $new_value['project_status_new'] = trim($values['project_status_new']);
  if(isset($values['set_add_item']) && !empty($values['set_add_item'])) {
    $new_value['set_add_item'] = $values['set_add_item'];  
  } 
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('project_status_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  //$new_value = strtolower(trim($new_value));
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['project_status_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['project_status_new']) && !empty($values) && !empty($new_value['project_status_new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm project approval status setting form
 */
function scm_project_approval_status_settings_form($form, &$form_state) {  
  $type = 'project_approval_status';  
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['project-approval-status-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['project_approval_status_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new approval status'),
    '#attributes' => array('class'=>array('project_approval_status_new'),'placeholder' => t('Please enter new approval status here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_approval_status_settings_form_submit_callback',
      'wrapper' => 'scm-project-approval-status-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/* 
 * Ajax submit callback for project approval status form
 */
function scm_project_approval_status_settings_form_submit_callback($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_approval_status';
  $new_value['project_approval_status_new'] = trim($values['project_approval_status_new']);
  if(isset($values['set_add_item']) && !empty($values['set_add_item'])) {
    $new_value['set_add_item'] = $values['set_add_item'];  
  } 
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('project_approval_status_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  //$new_value = strtolower(trim($new_value));
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['project_approval_status_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['project_approval_status_new']) && !empty($values) && !empty($new_value['project_approval_status_new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm category type setting form
 */
function scm_project_category_settings_form($form, &$form_state) {  
  $type = 'project_category';
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['category-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['category_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new category'),
    '#attributes' => array('class'=>array($type.'_new'),'placeholder' => t('Please enter new category here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_category_settings_form_submit_callback',
      'wrapper' => 'scm-category-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/* 
 * Ajax submit callback for category setting
 */
function scm_project_category_settings_form_submit_callback($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_category';
  $new_value = $values['category_new'];
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('category_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $new_value = trim($new_value);
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value,$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value) && !empty($values) && !empty($new_value) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm project department setting form
 */
function scm_project_department_settings_form($form, &$form_state) {  
  $type = 'project_department';  
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['project-approval-status-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['project_department_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Department'),
    '#attributes' => array('class'=>array('project_department_new'),'placeholder' => t('Please enter new department here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_department_settings_form_submit_callback',
      'wrapper' => 'scm-project-department-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/* 
 * Ajax submit callback for project department form
 */
function scm_project_department_settings_form_submit_callback($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_department';
  $new_value['project_department_new'] = trim($values['project_department_new']);
  if(isset($values['set_add_item']) && !empty($values['set_add_item'])) {
    $new_value['set_add_item'] = $values['set_add_item'];  
  } 
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('project_department_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  //$new_value = strtolower(trim($new_value));
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['project_department_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['project_department_new']) && !empty($values) && !empty($new_value['project_department_new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm category type setting form
 */
function scm_project_entity_settings_form($form, &$form_state) {  
  $type = 'project_entity';
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['project-entity-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['project_entity_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new project entity'),
    '#attributes' => array('class'=>array($type.'_new'),'placeholder' => t('Please enter new project entity here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_entity_settings_form_submit_callback',
      'wrapper' => 'scm-project-entity-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/* 
 * Ajax submit callback for category setting
 */
function scm_project_entity_settings_form_submit_callback($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_entity';
  $new_value = $values['project_entity_new'];
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('project_entity_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $new_value = trim($new_value);
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value,$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value) && !empty($values) && !empty($new_value) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm sub category type setting form
 */
function scm_project_sub_category_settings_form($form, &$form_state) {
  $type = 'project_sub_category';
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  
  $form['sub-category-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['category_maintype_new'] = array(
    '#title' => 'Category',
	  '#type' => 'select',
    '#options' => _get_category_type_from_settings('project'),    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','category_maintype_new')),
    '#empty_option' => 'Select the parent category',	
  );
  $form['sub_category_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new sub category'),
    '#attributes' => array('class'=>array($type.'_new'),'placeholder' => t('Please enter new sub category here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_project_sub_category_settings_form_submit_callback',
      'wrapper' => 'scm-sub-category-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/* 
 * Ajax submit callback for subcategory form
 */
function scm_project_sub_category_settings_form_submit_callback($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $type = 'project_sub_category';
  $parentCat = $values['category_maintype_new'];
  $new_value = $values['sub_category_new'];
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('sub_category_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $new_value = trim($new_value);
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value,$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value) && !empty($values) && !empty($new_value) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value,$parentCat);    
  }
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_invoke('select.category_maintype_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}



