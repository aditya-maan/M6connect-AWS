<?php
/*
 * Start work for m6connect contract
 * generating m6connect contract form.
 
 */

function contract_manager_configure_container() {
  drupal_add_js(drupal_get_path('module', 'm6connect_contract') . '/js/m6connect_contract.js');
	global $user, $company;
	
	$elements = array();
	$requesttab = request_tab_settings();
	$elements['contract-setting-menu-items'] = array(
		'#markup' => contract_setting_menu_links_content(),
		'#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
		'#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
	);
	$elements['container_tab'] = array(
	'#markup' =>drupal_render($requesttab),
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
 * Request tab container for 
 * Generating request setting form
 */
function request_tab_settings() { 
  global $user; 
  $elements = array();
  $container_Class = 6;
  if(!in_array('administrator', array_values($user->roles))) {
    $container_Class = 12;
  }
  $elements['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-'.$container_Class,'col-sm-'.$container_Class,'col-xs-'.$container_Class,'row','scm-setting-full-item-left','margin-10')),
  );
 
  $elements['main-container']['contract-type-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contract Type'),
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
  $elements['main-container']['contract-type-fieldset']['contract-type-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('contract_type_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-type-settings-form-set1">',
    '#suffix' => '</div>',
  );

  

  $elements['main-container']['contract-category-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Category'),
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
  $elements['main-container']['contract-category-fieldset']['contract-category-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('contract_category_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-type-settings-form-set1">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['contract-products-services-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Products or Services'),
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
  $elements['main-container']['contract-products-services-fieldset']['contract-products-services-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('contract_products_services_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-type-settings-form-set1">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['contract-document-type-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Document Type'),
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
  $elements['main-container']['contract-document-type-fieldset']['contract-document-type-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('contract_document_type_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-type-settings-form-set1">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['contract-effort-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Effort'),
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
  $elements['main-container']['contract-effort-fieldset']['contract-effort-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('contract_effort_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-type-settings-form-set1">',
    '#suffix' => '</div>',
  );

  $elements['main-container']['remove-setting-div'] = array(
    '#markup' => '',
    '#prefix' => '<div id="scm-option-remove">',
    '#suffix' => '</div><div class="remove-data-details" style="display:none"><span class="remove-data-details-service"></span><span class="remove-data-details-name"></span></div>',
  );

  $elements['main-container']['remove-setting-divdepartmant'] = array(
    '#markup' => '',
    '#prefix' => '<div id="scm-option-remove-divdepartmant">',
    '#suffix' => '</div><div class="remove-data-details" style="display:none"><span class="remove-data-details-service-departmant"></span><span class="remove-data-details-name-departmant"></span></div>',
  );

  $elements['main-container']['remove-setting-subtype'] = array(
    '#markup' => '',
    '#prefix' => '<div id="scm-option-remove-subtype">',
    '#suffix' => '</div><div class="remove-data-details" style="display:none"><span class="remove-data-details-service-subtype"></span><span class="remove-data-details-name-subtype"></span></div>',
  );
  
  return $elements;
}

/*
 *contract manager contract type setting form
 */

function contract_type_settings_form($form, &$form_state) {
  $type = 'contract_type';
  $render_data = _get_or_insert_contract_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['contract-type-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['contract_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Contract Type'),
    '#attributes' => array('class'=>array('contract_type_new'),'placeholder' => t('Please enter new contract type here')),
    '#required' => TRUE,
    '#default_value' => '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'contract_type_settings_form_submit_callback',
      'wrapper' => 'contract-type-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/*
 *contract manager category setting form
 */

function contract_category_settings_form($form, &$form_state) {
  $type = 'contract_category';
  $render_data = _get_or_insert_contract_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['contract-category-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['contract_category_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Category'),
    '#attributes' => array('class'=>array('contract_category_new'),'placeholder' => t('Please enter new category here')),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'contract_category_settings_form_submit_callback',
      'wrapper' => 'contract-category-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}


/*
 *contract manager products or services setting form
 */

function contract_products_services_settings_form($form, &$form_state) {
  $type = 'contract_products_services';
  $render_data = _get_or_insert_contract_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['contract-products-services-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['contract_products_services_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Product or Service'),
    '#attributes' => array('class'=>array('contract_products_services_new'),'placeholder' => t('Please enter new product or service here')),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'contract_products_services_settings_form_submit_callback',
      'wrapper' => 'contract-products-services-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/*
 *contract manager document type setting form
 */

function contract_document_type_settings_form($form, &$form_state) {
  $type = 'document_type';
  $render_data = _get_or_insert_contract_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['contract-document-type-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['contract_document_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Document Type'),
    '#attributes' => array('class'=>array('document_type_new'),'placeholder' => t('Please enter new document type here')),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'contract_document_type_settings_form_submit_callback',
      'wrapper' => 'contract-document-type-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/*
 *contract manager document type setting form
 */

function contract_effort_settings_form($form, &$form_state) {
  $type = 'effort';
  $render_data = _get_or_insert_contract_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['contract-effort-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['contract_effort_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Effort'),
    '#attributes' => array('class'=>array('effort_new'),'placeholder' => t('Please enter new effort here')),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'contract_effort_settings_form_submit_callback',
      'wrapper' => 'contract-effort-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}


/*
 * Ajax submit callback for 
 * Submitting contract type in contract manager setting form
 */
function contract_type_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'contract_type';
  $new_value['contract_type_new'] = trim($values['contract_type_new']);
  
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('contract_type_new', t('Contract type can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_contract_settings($type);
  if(in_array($new_value['contract_type_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($new_value['contract_type_new']) && !empty($values) && !empty($new_value['contract_type_new']) && $save_action){
    $save_new_setting = _get_or_insert_contract_settings($type,$new_value);    
  }

  $save_new_setting = _get_or_insert_contract_settings($type);
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  //$commands[] = ajax_command_invoke('.request_type_new', 'val', array(''));
  
  return array('#type' => 'ajax', '#commands' => $commands);
}


/*
 * Ajax submit callback for 
 * Submitting contract category in contract manager setting form
 */
function contract_category_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'contract_category';
  $new_value['contract_category_new'] = trim($values['contract_category_new']);
  
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('contract_category_new', t('Category can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_contract_settings($type);
  if(in_array($new_value['contract_category_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($new_value['contract_category_new']) && !empty($values) && !empty($new_value['contract_category_new']) && $save_action){
    $save_new_setting = _get_or_insert_contract_settings($type,$new_value);    
  }

  //$save_new_setting = _get_or_insert_contract_settings($type);
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
 * Ajax submit callback for 
 * Submitting contract products or services in contract manager setting form
 */
function contract_products_services_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'contract_products_services';
  $new_value['contract_products_services_new'] = trim($values['contract_products_services_new']);
  
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('contract_products_services_new', t('Product or Service can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_contract_settings($type);
  if(in_array($new_value['contract_products_services_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($new_value['contract_products_services_new']) && !empty($values) && !empty($new_value['contract_products_services_new']) && $save_action){
    $save_new_setting = _get_or_insert_contract_settings($type,$new_value);    
  }

  //$save_new_setting = _get_or_insert_contract_settings($type);
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
 * Ajax submit callback for 
 * Submitting contract document type in contract manager setting form
 */
function contract_document_type_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'document_type';
  $new_value['contract_document_type_new'] = trim($values['contract_document_type_new']);
  
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('contract_document_type_new', t('Document type can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_contract_settings($type);
  if(in_array($new_value['contract_products_services_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($new_value['contract_document_type_new']) && !empty($values) && !empty($new_value['contract_document_type_new']) && $save_action){
    $save_new_setting = _get_or_insert_contract_settings($type,$new_value);    
  }

  //$save_new_setting = _get_or_insert_contract_settings($type);
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
 * Ajax submit callback for 
 * Submitting contract document type in contract manager setting form
 */
function contract_effort_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'effort';
  $new_value['contract_effort_new'] = trim($values['contract_effort_new']);
  
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('contract_effort_new', t('Effort can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_contract_settings($type);
  if(in_array($new_value['contract_effort_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($new_value['contract_effort_new']) && !empty($values) && !empty($new_value['contract_effort_new']) && $save_action){
    $save_new_setting = _get_or_insert_contract_settings($type,$new_value);    
  }

  //$save_new_setting = _get_or_insert_contract_settings($type);
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