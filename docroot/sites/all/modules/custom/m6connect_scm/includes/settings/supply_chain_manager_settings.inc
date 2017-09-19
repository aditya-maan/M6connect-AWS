<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_configure_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  global $user,$company;
  if(in_array('administrator', array_values($user->roles))) {
    $query = db_select('m6connect_scm_settings_mata_field', 'n');
    $query->fields('n');
    $query->condition('n.companyID', $company->nid, '=');
    $resultmeta = $query->execute()->fetchAll();
    $allfieldarr = json_decode(default_dependent_fielddata(),true);
    if(empty($resultmeta)){
      scm_request_type_settings_meta_formdata_save($allfieldarr);
    }
  }
  $elements = array();
  $requesttab = request_tab_settings();
  $elements['scm-setting-menu-items'] = array(
    '#markup' => scm_setting_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline scm-main-menu">',
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
  $elements['left-container-form']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-6','row','scm-setting-full-item-right','alert-container-section','margin-10')),
  );
  if(in_array('administrator', array_values($user->roles))) {
    $elements['left-container-form']['add-field-setting']= array(
      '#markup' => '<div class="region-top-header-add-field_1" style="display:none">'.drupal_render(drupal_get_form('add_field_for_settings')).'</div>',
      '#prefix' => '<div class="clearfix margin-bottom-10 region-top-header">
              <div class="col-md-12 col-sm-12 col-xs-12 box-actions text-right">
              <a href="javascript:void(0)" title="Add Field" forclick="closeform" class="new-field-link new-record-link"><i class="glyphicon glyphicon-plus"></i> Add Field</a>
              <a href="javascript:void(0)" title="Add Group" forclick="closeform"class="new-group-link new-record-link"><i class="glyphicon glyphicon-plus"></i> Add Group</a>
            </div>',
      '#suffix' => '</div>',
    );
    $elements['left-container-form']['add-group-setting']= array(
      '#markup' => drupal_render(drupal_get_form('add_group_for_settings')),
      '#prefix' => '<div class="clearfix margin-bottom-10 region-top-header-add-field_2" style="display:none">',
      '#suffix' => '</div>',
    );
    $elements['left-container-form']['update-field-group-setting']= array(
      '#markup' => drupal_render(drupal_get_form('add_and_update_fieldssettings')),
      '#prefix' => '<div id="add_and_update_fieldssettings_custom" class="add_and_update_fieldssettings_custom">',
      '#suffix' => '</div>'
    );
  }

  // Flag to allow users to edit the SCR Request Number.
  $allow_edit_flag_form = drupal_get_form('allow_edit_flag_form');
  $elements['main-container']['allow-edit-scr-no-flag'] = array(
    '#markup' => drupal_render($allow_edit_flag_form),
    '#suffix' => '<br/><br/>',
  );
  $elements['main-container']['request-type-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Request Type'),
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
  $elements['main-container']['request-type-fieldset']['request-type-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_request_type_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-type-settings-form-set1">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['request-subtype-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Request Subtype'),
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
  $elements['main-container']['request-subtype-fieldset']['request-subtype-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_request_subtype_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 request-subtype-settings-form-set2">',
    '#suffix' => '</div>',
  );

  $elements['main-container']['scm-setting-NEC-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('NEC'),
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
  $elements['main-container']['scm-setting-NEC-fieldset']['NEC-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_nec_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 UOM-settings-form-set1">',
    '#suffix' => '</div>',
  );

  $elements['main-container']['scm-setting-UOM-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Purchase Unit of Measure'),
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
  $elements['main-container']['scm-setting-UOM-fieldset']['UOM-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_uom_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 UOM-settings-form-set1">',
    '#suffix' => '</div>',
  );
  $elements['main-container']['case-type-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Case Type'),
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
  $elements['main-container']['case-type-fieldset']['case-type-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_case_type_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10 case-type-settings-form-set1">',
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

  // Taking category and subcategory out of the col-md-6.
  $elements['category-sub-category-section'] = array(
    '#type'        => 'fieldset',
    '#title'       => t('Category and Subcategory Section'),
    '#collapsible' => TRUE,
    '#collapsed'   => TRUE,
    '#attributes'  => array('class' => array('collapsible', 'collapsed')),
    '#attached'    => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix'      => '<div class="row col-md-12 margin-bottom-10" >',
    '#suffix'      => '</div>',
  );

  $elements['category-sub-category-section']['category-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_category_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10" id="scm_request_subtype_settings_form_custom">',
    '#suffix' => '</div>',
  );

  return $elements;
}


function scm_nec_settings_form($form, &$form_state) {
  global $user, $company;
  $type = 'nec_settings';
  $setting_render_data = lineitem_data_div_setting_render_data('NEC');;
  $neclistoption = lineitem_data_datafunction('NEC','');
  foreach ($neclistoption as $key => $value) {
    $mainneclistoption[$key] = ucwords($value);    
  }
  $form['main_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="col-sm-12 thumbnail" id="scm_lineitem_nec_settings_main"><div class="col-sm-12 padding-0">',
    '#suffix' => '</div></div>',
  );
  // $form['main_container']['request-lineitem_nec-data'] = array(
  //   '#type' => 'markup',
  //   '#markup' => $setting_render_data,
  //   '#prefix' => '<div id="request_lineitem_nec-data-div-setting_render_data">',
  //   '#suffix' => '</div>',
  // );
  $form['main_container']['get-lineitem_nec-settings-reset'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control get-lineitem_nec-settings-reset')),
    '#ajax' => array(
      'callback'=> 'change_scm_lineitem_nec_settings_callbackreset',
      'wrapper' => 'get-lineitem_nec-settingsIDs',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-editlineitem_nec-settings'] = array(
    '#type' => 'select',
    '#options' => $mainneclistoption,
    '#attributes' => array('class'=> array('form-control get-editlineitem_nec-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_editlineitem_nec_settings_callback',
      'wrapper' => 'scm-nec-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" id="get-lineitem_nec-settingsIDs" style="display:none;"><div class="pull-left form-inline" id="get-editlineitem_nec-settings">',
    '#suffix' => '</div>',
  );
  $form['main_container']['get-dellineitem_nec-settings'] = array(
    '#type' => 'select',
    '#options' => $mainneclistoption,
    '#attributes' => array('class'=> array('form-control get-dellineitem_nec-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_dellineitem_nec_settings_callback',
      'wrapper' => 'scm-nec-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="pull-left form-inline" id="get-dellineitem_nec-settings">',
    '#suffix' => '</div></div>',
  );

  $form['main_container']['lineitem_nec_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class'=>array('lineitem_nec_hidden')),
  );
  $form['main_container']['lineitem_nec_no_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add NEC'),
    '#attributes' => array('class'=>array('lineitem_nec_no_new'),'placeholder' => t('Please enter NEC here')),
    '#required' => TRUE,
  );

  $form['main_container']['lineitem_nec_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add NEC Description'),
    '#attributes' => array('class'=>array('lineitem_nec_new'),'placeholder' => t('Please enter NEC description here')),
    '#required' => TRUE,
  );
  $form['main_container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_lineitem_nec_settings_form_submit_callback',
      'wrapper' => 'scm-nec-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['main_container']['nec-data-table'] = array(
    '#type' => 'markup',
    '#markup' => get_nec_data_tablesetting(),
    '#prefix' => '<div id="get_nec_data-data-div">',
    '#suffix' => '</div>',
  );
  return $form;
}

function change_scm_lineitem_nec_settings_callbackreset($form, &$form_state) {
  $commands = array();
  $commands[] = ajax_command_invoke("input.lineitem_nec_new", 'val',array(''));
  $commands[] = ajax_command_invoke("input.lineitem_nec_no_new", 'val',array(''));
  $commands[] = ajax_command_invoke("input.lineitem_nec_hidden", 'val',array(''));
  $commands[] = ajax_command_html("#get-editlineitem_nec-settings", render($form['main_container']['get-editlineitem_nec-settings']));
  $commands[] = ajax_command_html("#get-dellineitem_nec-settings", render($form['main_container']['get-dellineitem_nec-settings']));
  return array('#type' => 'ajax', '#commands' => $commands);
}




function change_scm_editlineitem_nec_settings_callback($form, &$form_state) {
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-editlineitem_nec-settings'){
    $getnecdata = lineitem_data_datafunction('NEC',$form_state['triggering_element']['#value']);
    $commands[] = ajax_command_invoke("input.lineitem_nec_new", 'val',array($getnecdata->title));
    $commands[] = ajax_command_invoke("input.lineitem_nec_no_new", 'val',array($getnecdata->necno));
    $commands[] = ajax_command_invoke("input.lineitem_nec_hidden", 'val',array($getnecdata->id));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}


function scm_lineitem_nec_settings_form_submit_callback($form, &$form_state) {
  if (form_get_errors()) {
    return $form;
  }
  // if(!is_numeric($form_state['values']['lineitem_nec_no_new'])){
  //   form_set_error('nec_new', t('Add New NEC Number Must Be Numerical Value'));
  //   return $form;
  // }
  if(!empty($form_state['values']['lineitem_nec_hidden'])){
    insert_and_update_lineitem_data($form_state['values'],'NEC','update');
  } else {
    insert_and_update_lineitem_data($form_state['values'],'NEC','add');
  }
  
  $commands = array();
  $commands[] = ajax_command_invoke("input.lineitem_nec_new", 'val',array(''));
  $commands[] = ajax_command_html("#get_nec_data-data-div", get_nec_data_tablesetting());
  $commands[] = ajax_command_html("#get-editlineitem_nec-settings", render($form['main_container']['get-editlineitem_nec-settings']));
    $commands[] = ajax_command_html("#get-dellineitem_nec-settings", render($form['main_container']['get-dellineitem_nec-settings']));
  $commands[] = ajax_command_invoke("select.get-lineitem_nec-settings-reset", 'trigger',array('change'));
  return array('#type' => 'ajax', '#commands' => $commands);
}
function change_scm_dellineitem_nec_settings_callback($form, &$form_state) {
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-dellineitem_nec-settings'){
    db_delete('m6connect_scm_settings_lineitem')->condition('id', $form_state['triggering_element']['#value'], '=')->execute();
    $commands[] = ajax_command_invoke("input.lineitem_nec_new", 'val',array(''));
    $commands[] = ajax_command_invoke("input.lineitem_nec_no_new", 'val',array(''));
    $commands[] = ajax_command_invoke("input.lineitem_nec_hidden", 'val',array(''));
    $commands[] = ajax_command_html("#get-editlineitem_nec-settings", render($form['main_container']['get-editlineitem_nec-settings']));
    $commands[] = ajax_command_html("#get-dellineitem_nec-settings", render($form['main_container']['get-dellineitem_nec-settings']));
    $commands[] = ajax_command_html("#get_nec_data-data-div", get_nec_data_tablesetting());
  }
  $commands[] = ajax_command_invoke("select.get-lineitem_nec-settings-reset", 'trigger',array('change'));
  return array('#type' => 'ajax', '#commands' => $commands);
}

function get_nec_data_tablesetting() {
  $setting_render_data = '<table class="table table-bordered m6connect-custom-table">';
  $setting_render_data .= '<thead><tr>';
  $setting_render_data .=  '<th class="text-left">NEC</th>'; 
  $setting_render_data .=  '<th class="text-left">NEC Description</th>'; 
  $setting_render_data .=  '<th class="text-center">Action</th>'; 
  $setting_render_data .= '</tr></thead><tbody>';
  foreach (lineitem_data_datafunction('NEC','all') as $key => $value) { 
    $setting_render_data .= '<tr>';
    $setting_render_data .=  '<td><div style="max-width: 150px;" class="text-left">'.ucwords($value->necno).'</div></td>'; 
    $setting_render_data .=  '<td ><div style="max-width: 300px;" class="text-left">'.ucwords($value->title).'</div></td>'; 
    $setting_render_data .=  '<td class="text-center">
    <a href="javascript:void(0)" class="edit-NECaction-cat-call" dataedit-NECref="'.$value->id.'"><i class="fa fa-pencil-square-o" aria-hidden="true"></i></a>
    <a href="javascript:void(0)" fortitle="'.ucwords($value->title).'" class="remove-scm-setting-options-NEC" deleteNECref="'.$value->id.'"><i class="fa fa-trash-o" aria-hidden="true"></i></a></td>';  
    $setting_render_data .= '</tr>';
  }
  $setting_render_data .= '</tbody></table>';
  return $setting_render_data;
}

function scm_uom_settings_form($form, &$form_state) {
  global $user, $company;
  $type = 'uom_settings';
  $setting_render_data = lineitem_data_div_setting_render_data('UOM');
  $uomlistoption = lineitem_data_datafunction('UOM');
  foreach ($uomlistoption as $key => $value) {
    $mainuomlistoption[$key] = ucwords($value);    
  }
  $form['main_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="col-sm-12 thumbnail" id="scm_lineitem_uom_settings_main">',
    '#suffix' => '</div>',
  );
  $form['main_container']['request-lineitem_uom-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="request_lineitem_uom-data-div-setting_render_data">',
    '#suffix' => '</div>',
  );

  $form['main_container']['get-lineitem_uom-settings-reset'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control get-lineitem_uom-settings-reset')),
    '#ajax' => array(
      'callback'=> 'change_scm_lineitem_uom_settings_callbackreset',
      'wrapper' => 'get-dellineitem_uom-settingsID',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-dellineitem_uom-settings'] = array(
    '#type' => 'select',
    '#options' => $mainuomlistoption,
    '#attributes' => array('class'=> array('form-control get-dellineitem_uom-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_dellineitem_uom_settings_callback',
      'wrapper' => 'scm-uom-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" id="get-dellineitem_uom-settingsID" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['lineitem_uom_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New UOM'),
    '#attributes' => array('class'=>array('lineitem_uom_new'),'placeholder' => t('Please enter new UOM here')),
    '#required' => TRUE,
  );
  $form['main_container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_lineitem_uom_settings_form_submit_callback',
      'wrapper' => 'scm-uom-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

function scm_lineitem_uom_settings_form_submit_callback($form, &$form_state) {
  if (form_get_errors()) {
    return $form;
  }
  insert_and_update_lineitem_data($form_state['values'],'UOM','add');
  $commands = array();
  $commands[] = ajax_command_invoke("input.lineitem_uom_new", 'val',array(''));
  $commands[] = ajax_command_html("#request_lineitem_uom-data-div-setting_render_data", lineitem_data_div_setting_render_data('UOM'));
  $commands[] = ajax_command_invoke("input.lineitem_uom_new", 'val',array(''));
  $commands[] = ajax_command_html("#get-dellineitem_uom-settingsID", render($form['main_container']['get-dellineitem_uom-settings']));
  $commands[] = ajax_command_invoke("select.get-lineitem_uom-settings-reset", 'trigger',array('change'));
  return array('#type' => 'ajax', '#commands' => $commands);
}


function change_scm_lineitem_uom_settings_callbackreset($form, &$form_state) {
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-lineitem_uom-settings-reset'){
    $commands[] = ajax_command_html("#get-dellineitem_uom-settingsID", render($form['main_container']['get-dellineitem_uom-settings']));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}
function change_scm_dellineitem_uom_settings_callback($form, &$form_state) {
  global $user, $company;
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-dellineitem_uom-settings'){
    db_delete('m6connect_scm_settings_lineitem')->condition('id', $form_state['triggering_element']['#value'], '=')->execute();
    $commands[] = ajax_command_invoke("input.lineitem_uom_new", 'val',array(''));
    $commands[] = ajax_command_html("#request_lineitem_uom-data-div-setting_render_data", lineitem_data_div_setting_render_data('UOM'));
    $commands[] = ajax_command_html("#get-dellineitem_uom-settingsID", render($form['main_container']['get-dellineitem_uom-settings']));
    $commands[] = ajax_command_invoke("select.get-lineitem_uom-settings-reset", 'trigger',array('change'));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function insert_and_update_lineitem_data($new_value,$type,$action='') {
  global $user, $company;
  $setting_insert['uid'] = $user->uid;
  $setting_insert['nid'] = $company->nid;
  $setting_insert['type'] = $type;
  $setting_insert['status'] = 1;
  if($type=='UOM'){
    $setting_insert['title'] = $new_value['lineitem_uom_new'];
  }
  if($type=='NEC'){
    $setting_insert['title'] = $new_value['lineitem_nec_new'];
    $setting_insert['necno'] = $new_value['lineitem_nec_no_new'];
  }
  if($action=='add') {
        $setting_insert['timestamp'] = time();
        db_insert('m6connect_scm_settings_lineitem')->fields($setting_insert)->execute();
  }
  if($action=='update') {
    if($type=='NEC') {
      if(!empty($new_value['lineitem_nec_hidden'])) {
         db_update('m6connect_scm_settings_lineitem')
          ->fields($setting_insert)
          ->condition('id', $new_value['lineitem_nec_hidden'], '=')
          ->execute();  
      }
    }
  }
}

function lineitem_data_div_setting_render_data($typo) {
  global $user, $company;
  $mainuomlistoption = [];
  $type = 'uom_settings';
  $uomlistoption = lineitem_data_datafunction($typo,'');
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
    foreach ($uomlistoption as $keydata => $renderdata) {
      $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . ucwords($renderdata) . ' <span><i fortitle="'.ucwords($renderdata).'" class="fa fa-times remove-scm-setting-options-'.$typo.'" aria-hidden="true" scm-type="'.$type.'" data="' . ucwords($renderdata) .'" deletenecref ="' .$keydata. '"></i></span></div>';
    }
    $setting_render_data .= '</div>';
    return $setting_render_data;
}

function lineitem_data_datafunction($type,$id='') {
  global $user, $company;
  $query = db_select('m6connect_scm_settings_lineitem', 'n');
  $query->condition('n.nid', $company->nid, '=');
  $query->condition('n.type', $type, '=');
  if(!empty($id)){
    if($id=='all'){
      $query->fields('n');
      $uomlistoption = $query->execute()->fetchAll();
    } else {
      $query->fields('n');
      $query->condition('n.id', $id, '=');
      $uomlistoption = $query->execute()->fetchObject();
    }
  } else {
    $query->fields('n',array('id','title'));
    $uomlistoption = $query->execute()->fetchAllKeyed(0,1);
  }
  return $uomlistoption;
}


function add_field_for_settings($form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $form['add-field-form-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('scm-setting-full-item')),
  );
  $form['add-field-form-container']['scm_setting_field_lebel'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#attributes' => array('class'=>array('scm_setting_field_lebel'),'placeholder' => t('Please enter label')),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['add-field-form-container']['scm_setting_field_file_type'] = array(
    '#type' => 'select',
    '#title' => 'Choose Field Type',
    '#options' => array('textfield'=>'Textfield','select'=>'Select','checkbox'=>'Checkbox','textarea'=>'Textarea','company'=>'Company List'),
    '#empty_option' => 'Select Field type',
    '#attributes' => array('class'=> array('form-control scm_setting_field_file_type', 'col-sm-4')),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );

  $form['add-field-form-container']['scm_setting_field_group'] = array(
    '#type' => 'select',
    '#title' => 'Choose Field Group',
    '#options' => scm_settings_grouplist(1),
    '#empty_option' => 'Select Field type',
    '#attributes' => array('class'=> array('form-control scm_setting_field_file_type', 'col-sm-4')),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['add-field-form-container']['scm_setting_field_optionval'] = array(
        '#title' => 'Options',
        '#type' => 'textarea',
        '#rows' => 2,
        '#attributes'=> array('class'=> array('scm_setting_field_optionval margin-0')),
        '#prefix' => '<div class="form-item col-sm-12 margin-0 scm_setting_field_option_container" style="display: none;">',
        '#suffix' => '</div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Field'),
    '#ajax' => array(
      'callback' => 'add_field_for_settings_form_submit_callback',
      'wrapper' => 'add-field-for-settings',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-12 text-right">',
    '#suffix' => '</div>',
  );
  return $form;
}

function add_field_for_settings_form_submit_callback($form, &$form_state){
  if (form_get_errors()) {
    return $form;
  }
  global $user,$company;
  $fvalue = $form_state['values'];
  $commands = array();
  $groupfield_data['Label'] = $fvalue['scm_setting_field_lebel'];
  $groupfield_data['scm_field_key'] = string_to_slug($value['scm_setting_field_lebel']).'_'.$fvalue['scm_setting_field_group'].'_'.$company->nid.'_'.$user->uid;
  $groupfield_data['type'] = $fvalue['scm_setting_field_file_type'];
  $groupfield_data['value'] = $fvalue['scm_setting_field_optionval'];
  $groupfield_data['scm_field_group'] = $fvalue['scm_setting_field_group'];
  $groupfield_data['companyID'] = $company->nid;
  $groupfield_data['scmID'] = $user->uid;
  db_insert('m6connect_scm_settings_mata_field')->fields($groupfield_data)->execute();
  $commands[] = ajax_command_html("#add_and_update_fieldssettings_custom", drupal_render(drupal_get_form('add_and_update_fieldssettings')));  
  return array('#type' => 'ajax', '#commands' => $commands);
}

function add_group_for_settings($form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $form['add-group-form-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('scm-setting-full-item')),
  );
  $form['add-group-form-container']['scm_setting_group_lebel'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#attributes' => array('class'=>array('scm_setting_group_lebel'),'placeholder' => t('Please enter label')),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['add-group-form-container']['scm_setting_group_area_size'] = array(
      '#type' => 'select',
      '#title' => 'Size',
      '#options' => array('12'=>'100%','6'=>'50%','3'=>'25%','4'=>'30%'),
      '#empty_option' => 'Select Size',
      '#attributes' => array('class'=> array('form-control scm_setting_group_area_size', 'col-sm-4')),
      '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4">',
      '#suffix' => '</div>',
      '#disabled' => false,
      '#required' => TRUE,
  );
  $form['add-group-form-container']['scm_setting_group_number_of_values'] = array(
    '#type' => 'select',
    '#title' => 'Label Hidden',
    '#options' => array(0=>'No',1=>'yes'),
    '#empty_option' => 'Label Hidden',
    '#attributes' => array('class'=> array('form-control scm_setting_group_number_of_values', 'col-sm-4')),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4">',
    '#suffix' => '</div>',
    '#disabled' => false,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Group'),
    '#ajax' => array(
      'callback' => 'add_group_for_settings_form_submit_callback',
      'wrapper' => 'add-group-for-settings',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-12 text-right">',
    '#suffix' => '</div>',
  );
  return $form;
}

function add_group_for_settings_form_submit_callback($form, &$form_state) {
  if (form_get_errors()) {
    return $form;
  }
  global $user,$company;
    $fvalue = $form_state['values'];
    $commands = array();
    $groupdata['Label'] = $fvalue['scm_setting_group_lebel'];
    $groupdata['scm_group_key'] = string_to_slug($fvalue['scm_setting_group_lebel']).'_'.$company->nid.'_'.$user->uid;
    $groupdata['value'] = '';
    $groupdata['type'] = 1;
    $groupdata['companyID'] = $company->nid;
    $groupdata['scmID'] = $user->uid;
    $groupdata['size'] = $fvalue['scm_setting_group_area_size'];
    $groupdata['Numberofvalues'] = $fvalue['scm_setting_group_number_of_values'];
    $getgroupID = db_insert('m6connect_scm_settings_meta_group')->fields($groupdata)->execute();
    $commands[] = ajax_command_html("#add_and_update_fieldssettings_custom", drupal_render(drupal_get_form('add_and_update_fieldssettings')));  
    return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_settings_field_delete_callback($form, &$form_state) {
  if($form_state['triggering_element']['#name'] == 'list_of_fields'){
    $commands = array();
    $form_state['triggering_element']['#value'];
    db_delete('m6connect_scm_settings_mata_field')
        ->condition('id', $form_state['triggering_element']['#value'])
        ->execute();
  }
  $commands[] = ajax_command_html("#add_and_update_fieldssettings_custom", drupal_render(drupal_get_form('add_and_update_fieldssettings')));  
  return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_settings_group_delete_callback($form, &$form_state) {
  if($form_state['triggering_element']['#name'] == 'list_of_groups'){
    $commands = array();
    $form_state['triggering_element']['#value'];
    db_delete('m6connect_scm_settings_meta_group')
        ->condition('id', $form_state['triggering_element']['#value'])
        ->execute();
  }
  $commands[] = ajax_command_html("#add_and_update_fieldssettings_custom", drupal_render(drupal_get_form('add_and_update_fieldssettings')));  
  return array('#type' => 'ajax', '#commands' => $commands);
}

function add_and_update_fieldssettings($form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $alldefultfields = _get_allField_scm_settings_matadetails();
  $form['main-group-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','all-field-group-outer-container')),
  );

  $form['list_of_fields'] = array(
    '#type' => 'select',
    '#options' => get_all_field_companybase(),
    '#default_value' => 0,
    '#attributes' => array('class'=> array('form-control list_of_fields')),
    '#ajax' => array(
      'callback' => 'scm_settings_field_delete_callback',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );

  $form['list_of_groups'] = array(
    '#type' => 'select',
    '#options' => get_all_group_companybase(),
    '#default_value' => 0,
    '#attributes' => array('class'=> array('form-control list_of_groups')),
    '#ajax' => array(
      'callback' => 'scm_settings_group_delete_callback',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );
  
  foreach ($alldefultfields as $key => $value) {
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key] = array(
      '#title' => ucwords($value->Label).'<a href="javascript:void(0)" style="float: right;" class="edit-section-group" id="edit-section--'.$key.'"><span class="glyphicon glyphicon-plus-sign"></span></a><a href="javascript:void(0)" style="float: right;display:none;" class="cancle-section-group" id="cancle-section--'.$key.'"><span class="glyphicon glyphicon-minus-sign"></span></a>', 
      '#type' => 'fieldset',
      '#attributes'=> array('class'=> array('workflow-auto','scm-location-region-name')),
      '#prefix' => '<div class="project-details-border edit-section--'.$key.'"><div class="form-item clearfix">',
      '#suffix' => '</div>',
    );
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_id'] = array(
      '#type' => 'hidden',
      '#title' => t('Id'),
      '#default_value' => t($value->id),
      '#parents' => array('sub_group', $key, 'main-group-id'),
      '#attributes' => array('class'=>array('scm_setting_field_lebel')),
    );

    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_type'] = array(
      '#type' => 'hidden',
      '#default_value' => t($value->type),
      '#parents' => array('sub_group', $key, 'main-group-type'),
      '#attributes' => array('class'=>array('scm_setting_field_lebel')),
    );

    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_name'] = array(
      '#type' => 'textfield',
      '#default_value' => t(ucwords($value->Label)),
      '#parents' => array('sub_group', $key, 'main-group-name'),
      '#attributes' => array('class'=>array('scm_setting_field_lebel'),'placeholder' => t('Please enter Label')),
      '#prefix' => '<div class="col-sm-12 field-group-Input margin-0 margin-bottom-15 padding-0" style="display:none;"><div class="col-sm-4 padding-0">',
      '#suffix' => '</div>',
    );
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_formate'] = array(
      '#type' => 'textfield',
      '#default_value' => t($key),
      '#parents' => array('sub_group', $key, 'main-group-formate'),
      '#attributes' => array('class'=> array('form-control group_formate padding-0',)),
      '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-1 padding-right-0">',
      '#suffix' => '</div>',
      '#disabled' => false,
    );
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_number_of_values'] = array(
      '#type' => 'select',
      '#options' => array(0=>'No',1=>'Yes'),
      '#empty_option' => 'Label Hidden',
      '#parents' => array('sub_group', $key, 'main-group-number_of_values'),
      '#default_value' => t($value->Numberofvalues),
      '#attributes' => array('class'=> array('form-control group_number_of_values', 'col-sm-4')),
      '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-4 padding-right-0">',
      '#suffix' => '</div>',
      '#disabled' => false,
    );

    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_area_size'] = array(
      '#type' => 'select',
      '#options' => array('12'=>'100%','6'=>'50%','3'=>'25%','4'=>'30%'),
      '#empty_option' => 'Select Size',
      '#parents' => array('sub_group', $key, 'main-group_area_size'),
      '#default_value' => t($value->size),
      '#attributes' => array('class'=> array('form-control group_area_size', 'col-sm-5')),
      '#prefix' => '<div class="clearfix margin-bottom-10 col-sm-3 padding-right-0">',
      '#suffix' => '</div>',
      '#disabled' => false,
    );
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_delete_single'] = array(
      '#markup' => '',
      '#prefix' => '<div class="delete_groupicon padding-0">',
      '#suffix' => '</div></div>',
    );
    if(count($value->fieldsdata)==0){
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_delete_single']['#markup'] = '<a href="javascript:void(0)" delete_ifref="'.$value->id.'" style="float: right;" class="delete-section-group group_delete_single_formgroup"><span class="glyphicon glyphicon-remove"></span></a>';
    }
    
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container']= array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('col-sm-12','scm-setting-full-item-field', 'thumbnail', 'margin-0', 'padding-10')),
    );
    foreach ($value->fieldsdata as $fkey => $fvalue) {
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_label_text'] = array(
        '#markup' => t(ucwords($fvalue->Label)),
        '#prefix' => '<div class="field-inner-valuefield field-inner-valuefield"><div class="col-sm-6">',
        '#suffix' => '</div>',
      );
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_type_text'] = array(
        '#markup' => t(ucwords($fvalue->type)),
        '#prefix' => '<div class="col-sm-5">',
        '#suffix' => '</div>',
      );
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_type_delete'] = array(
        // '#markup' => '<a href="javascript:void(0)" delete_ifref="'.$fvalue->id.'" style="float: right;" class="delete-section-group field_delete_single_formfield"><span class="glyphicon glyphicon-remove"></span></a>',
        '#prefix' => '<div class="col-sm-1">',
        '#suffix' => '</div></div>',
      );
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_id'] = array(
        '#type' => 'hidden',
        '#default_value' => t($fvalue->id),
        '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_id'),
        '#attributes' => array('class'=>array('scm_setting_field_flId')),
        );

      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_id-parant_relation'] = array(
        '#type' => 'hidden',
        '#default_value' => t($fvalue->relation_parent),
        '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_relation_parent'),
        '#attributes' => array('class'=>array('scm_setting_field_relation_parent')),
        );
      if($fvalue->companyID){
        $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_companyID'] = array(
          '#type' => 'hidden',
          '#default_value' => t($fvalue->companyID),
          '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_companyID'),
          '#attributes' => array('class'=>array('scm_setting_field_companyID')),
        );
      }
      if($fvalue->scmID) {
        $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_scmID'] = array(
          '#type' => 'hidden',
          '#default_value' => t($fvalue->scmID),
          '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_scmID'),
          '#attributes' => array('class'=>array('scm_setting_field_scmID')),
        );
      }
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_label'] = array(
        '#type' => 'textfield',
        '#default_value' => t($fvalue->Label),
        '#attributes' => array('class'=>array('scm_setting_field_label label_id_data_'.$value->id),'placeholder' => t('Please enter Label')),
        '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_label'),
        '#prefix' => '<div class="field-inner-group" style="display:none;"><div class="row"><div class="col-sm-12 padding-0"><div class="col-sm-6">',
        '#suffix' => '</div>',
      );
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_type'] = array(
        '#type' => 'select',
        '#options' => array('textfield'=>'Textfield','select'=>'Select','checkbox'=>'Checkbox','textarea'=>'Textarea','company'=>'Company List'),
        '#empty_option' => 'Select Field type',
        '#default_value' => $fvalue->type,
        '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_type'),
        '#attributes' => array('class'=>array('form-control scm-settings-select-fields-type scm_setting_field_options'), 'dataref' =>array('options_id_data_'.$fvalue->id)),
        '#prefix' => '<div class="col-sm-5">',
        '#suffix' => '</div>', 
      );
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_delete_action'] = array(
        '#markup' => '<a href="javascript:void(0)" delete_ifref="'.$fvalue->id.'" style="float: right;" class="delete-section-group field_delete_single_formfield"><span class="glyphicon glyphicon-remove"></span></a>',
        '#prefix' => '<div class="col-sm-1">',
        '#suffix' => '</div></div>',
      );
      if($fvalue->companyID && $fvalue->scmID){
        $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_type']['#disabled'] = TRUE;
      }
      $displaopt = 'none';
      if($fvalue->type=='select' || $fvalue->type=='checkbox'){
        $displaopt = 'block';
      }
      $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group-fields-container'][$fkey]['group-field'.$fvalue->scm_field_key]['field_detailsoption'] = array(
          '#title' => 'Options',
          '#type' => 'textarea',
          '#default_value' => $fvalue->value,
          '#parents' => array('sub_group', $key, 'main-group-fields', $fkey, 'field_detailsoption'),
          '#rows' => 2,
          '#attributes'=> array('class'=> array('scm_setting_field_optionsdata margin-0')),
          '#prefix' => '<div class="form-item col-sm-12 margin-0 optionsdata_id_data_'.$fvalue->id.'" style="display:'.$displaopt.';">',
          '#suffix' => '</div></div></div>',
      );
    }
    $form['main-group-container'][$key]['main-group-'.$value->scm_group_key]['group_key'] = array(
      '#markup' => '',
      '#suffix' => '</div>',
    );
  }
  $form['main-group-container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#attributes'=> array('class'=> array('scm_setting_field_submitcall')),
    '#ajax' => array(
      'callback' => 'scm_request_type_settings_meta_form_submit_callback',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10 text-right">',
    '#suffix' => '</div>',
  );
  return $form;
}

function scm_request_type_settings_meta_form_submit_callback($form, &$form_state) {
  global $user,$company;
  $allfieldarr = $form_state['values']['sub_group'];
  scm_request_type_settings_meta_formdata_save($allfieldarr);
}


function scm_department_settings_form($form, &$form_state) {
  global $user, $company;
  $type = 'department';
  $setting_render_data = '';
  $subcatlistoption = array();
  $query = db_select('m6connect_scm_setting_department', 'n');
  $query->fields('n',array('id','title'));
  $query->condition('n.nid', $company->nid, '=');
  $maincatlistoption = $query->execute()->fetchAllKeyed(0,1);
  foreach ($maincatlistoption as $key => $value) {
    $maincatlistoption[$key] = ucwords($value);    
  }
  $form['main_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="col-sm-12 thumbnail" id="scm_department_settings_main"><div class="col-sm-12 padding-0">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-department-settings-reset'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control get-department-settings-reset')),
    '#ajax' => array(
      'callback'=> 'change_scm_department_settings_callbackreset',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-editdepartment-settings'] = array(
    '#type' => 'select',
    '#options' => $maincatlistoption,
    '#attributes' => array('class'=> array('form-control get-editdepartment-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_editdepartment_settings_callback',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" id="get-editdeldepartment-settingsID" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-deldepartment-settings'] = array(
    '#type' => 'select',
    '#options' => $maincatlistoption,
    '#attributes' => array('class'=> array('form-control get-deldepartment-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_deldepartment_settings_callback',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" id="get-deldepartment-settingsID" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['department_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Department'),
    '#attributes' => array('class'=>array('department_new'),'placeholder' => t('Please enter new department here')),
    '#required' => TRUE,
  );
  $form['main_container']['department_new_hidden'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class'=>array('department_new_hidden')),
  );
  $form['main_container']['assign_user_department'] = array(
    '#title' => t('Department Approver'),
    '#type'     => 'select',
    '#options' => get_scm_user_database_datasall('Department Approver'),
    '#empty_option' => t('Select User'),
    '#multiple'     => 1,
    '#select2' => array('width'=>'100%'),
    '#attributes' => array('class'=>array($type.'_new_userinput'),'placeholder' => t('Please choose department approver')),
    '#prefix' => '<div class="assign_user-outer-department">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['main_container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_department_settings_form_submit_callback',
      'wrapper' => 'scm-department-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['main_container']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#ajax' => array(
      'callback'=> 'change_scm_department_settings_callbackreset',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
  );
  $form['main_container']['department-data-table'] = array(
    '#type' => 'markup',
    '#markup' => get_department_data_tablesetting(),
    '#prefix' => '<div id="department-data-div">',
    '#suffix' => '</div>',
  );
  return $form;
}


function change_scm_deldepartment_settings_callback($form, &$form_state) {
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-deldepartment-settings'){
    db_delete('m6connect_scm_setting_department')->condition('id', $form_state['triggering_element']['#value'], '=')->execute();
    $commands[] = ajax_command_invoke("input.department_new", 'val',array(''));
    $commands[] = ajax_command_invoke("input.department_new_hidden", 'val',array(''));
    $commands[] = ajax_command_invoke("select.department_new_userinput", 'val',array(''));
    $commands[] = ajax_command_invoke("select.department_new_userinput", 'trigger',array('change'));
    $commands[] = ajax_command_html("#request_deldepartment-data-div-setting_render_data", '');
    $commands[] = ajax_command_html("#department-data-div", get_department_data_tablesetting());
    $commands[] = ajax_command_html("#get-editdeldepartment-settingsID", render($form['main_container']['get-editdepartment-settings']));
    $commands[] = ajax_command_html("#get-deldepartment-settingsID", render($form['main_container']['get-deldepartment-settings']));
    return array('#type' => 'ajax', '#commands' => $commands);
  }
}

function change_scm_department_settings_callbackreset($form, &$form_state){
  $commands = array();
  $commands[] = ajax_command_invoke("input.department_new", 'val',array(''));
  $commands[] = ajax_command_invoke("input.department_new_hidden", 'val',array(''));
  $commands[] = ajax_command_invoke("select.department_new_userinput", 'val',array(''));
  $commands[] = ajax_command_invoke("select.department_new_userinput", 'trigger',array('change'));
  $commands[] = ajax_command_html("#request_deldepartment-data-div-setting_render_data", '');
  $commands[] = ajax_command_html("#department-data-div", get_department_data_tablesetting());
  $commands[] = ajax_command_html("#get-editdeldepartment-settingsID", render($form['main_container']['get-editdepartment-settings']));
  $commands[] = ajax_command_html("#get-deldepartment-settingsID", render($form['main_container']['get-deldepartment-settings']));
  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_editdepartment_settings_callback($form, &$form_state) {
  $commands = array();
  global $user, $company;
  if($form_state['triggering_element']['#name']=='get-editdepartment-settings'){
    $type = 'department';
    $subquery = db_select('m6connect_scm_setting_department', 'n');
    $subquery->fields('n');
    $subquery->condition('n.id', $form_state['triggering_element']['#value'], '=');
    $subquery->condition('n.nid', $company->nid, '=');
    $resultsubtype = $subquery->execute()->fetchObject();
    $commands[] = ajax_command_invoke("input.department_new", 'val',array($resultsubtype->title));
    $commands[] = ajax_command_invoke("input.department_new_hidden", 'val',array($form_state['triggering_element']['#value']));
    $commands[] = ajax_command_invoke("select.department_new_userinput", 'val',array(explode("|",$resultsubtype->dpapprover)));
    $commands[] = ajax_command_invoke("select.department_new_userinput", 'trigger',array('change'));
    // $commands[] = ajax_command_html("#request_deldepartment-data-div-setting_render_data", get_all_departmentbumainid($form_state['triggering_element']['#value']));
    $commands[] = ajax_command_html("#department-data-div", get_department_data_tablesetting());
  }
   return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_department_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'department';
  $new_value['department_new'] = strtolower(trim($values['department_new']));
  $new_value['assign_user_department'] = implode("|",$values['assign_user_department']);
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('department_new', t('Name Can Not Be Blank!'));
  }
  if ($error) {
    return $form;
  }
  $setting_insert = array (
      'uid' => $user->uid,
      'nid' => $company->nid,
      'title' => $new_value['department_new'],
      'dpapprover' => $new_value['assign_user_department'],
  );
  if(!empty($values['department_new_hidden'])){
      db_update('m6connect_scm_setting_department')
      ->fields($setting_insert)
      ->condition('id', $values['department_new_hidden'], '=')
      ->execute();
  } else {
        $setting_insert['status'] = 1;
        $setting_insert['timestamp'] = time();
        db_insert('m6connect_scm_setting_department')->fields($setting_insert)->execute();
  }
  $commands = array();
  $commands[] = ajax_command_invoke("input.department_new", 'val',array(''));
  $commands[] = ajax_command_invoke("input.department_new_hidden", 'val',array(''));
  $commands[] = ajax_command_invoke("select.department_new_userinput", 'val',array(''));
  $commands[] = ajax_command_invoke("select.department_new_userinput", 'trigger',array('change'));
  $commands[] = ajax_command_html("#request_deldepartment-data-div-setting_render_data", '');
  $commands[] = ajax_command_html("#department-data-div", get_department_data_tablesetting());
  $commands[] = ajax_command_html("#get-editdeldepartment-settingsID", render($form['main_container']['get-editdepartment-settings']));
  $commands[] = ajax_command_html("#get-deldepartment-settingsID", render($form['main_container']['get-deldepartment-settings']));
  $commands[] = ajax_command_invoke("select.get-department-settings-reset", 'trigger',array('change'));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/*
 *scm Case type setting form
 */
function scm_case_type_settings_form($form, &$form_state) {
  $type = 'case_type';
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['case-type-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['case_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Case Type'),
    '#attributes' => array('class'=>array('case_type_new'),'placeholder' => t('Please enter new case type here')),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_case_type_settings_form_submit_callback',
      'wrapper' => 'scm-case-type-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/*
 * Ajax submit callback for 
 * Submitting request type setting form
 */
function scm_case_type_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'case_type';
  $new_value['case_type_new'] = trim($values['case_type_new']);   
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('case_type_new', t('Case type can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['case_type_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['case_type_new']) && !empty($values) && !empty($new_value['case_type_new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }

  $save_new_setting = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  $commands[] = ajax_command_invoke('input.set_item_for_new', 'prop', array('checked',false)); 
  return array('#type' => 'ajax', '#commands' => $commands);
}
/*
 *scm request type setting form
 */
function scm_request_type_settings_form($form, &$form_state) {
  $type = 'request_type';
  $render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
  foreach ($render_data as $renderdata) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $renderdata . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $renderdata . '"></i></span></div>';
  }
  $setting_render_data .= '</div>';
  $form['request-type-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="'.$type.'-data-div">',
    '#suffix' => '</div>',
  );
  $form['request_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add New Request Type'),
    '#attributes' => array('class'=>array('request_type_new'),'placeholder' => t('Please enter new request type here')),
    '#required' => TRUE,
  );

  $form['set_add_item'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add Manufacturer, Vendor, UOM Table'),
    '#default_value' => 0,
    '#options' => array(0,1),
    '#attributes' => array('class'=>array('set_item_for_new')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_request_type_settings_form_submit_callback',
      'wrapper' => 'scm-request-type-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  return $form;
}

/*
 * Ajax submit callback for 
 * Submitting request type setting form
 */
function scm_request_type_settings_form_submit_callback($form, &$form_state) { 
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'request_type';
  $new_value['request_type_new'] = trim($values['request_type_new']);
  if(isset($values['set_add_item']) && !empty($values['set_add_item'])) {
    $new_value['set_add_item'] = $values['set_add_item'];  
  } 
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('request_type_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value['request_type_new'],$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value['request_type_new']) && !empty($values) && !empty($new_value['request_type_new']) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value);    
  }

  $save_new_setting = _get_or_insert_scm_settings($type);
  $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  foreach ($save_new_setting as $save_newsetting) {
    $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . $save_newsetting . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . $save_newsetting . '"></i></span></div>';
  }
  $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  $commands[] = ajax_command_invoke('input.set_item_for_new', 'prop', array('checked',false)); 
  return array('#type' => 'ajax', '#commands' => $commands);
}

/* 
 * Scm request sub type setting form
 */
function scm_request_subtype_settings_form($form, &$form_state) {  
  global $user, $company;
  $type = 'request_subtype';
  $form_state['request_subtype_selected'] = '';
  //$render_data = _get_or_insert_scm_settings($type);
  $setting_render_data = '';

  $subcatlistoption = array();
  $query = db_select('m6connect_scm_request_type_setting', 'n');
  $query->fields('n',array('id','title'));
  $query->condition('n.nid', $company->nid, '=');
  $maincatlistoption = $query->execute()->fetchAllKeyed(0,1);
  foreach ($maincatlistoption as $key => $value) {
    $maincatlistoption[$key] = ucwords($value);
        $mainquery = db_select('m6connect_scm_request_subtype_setting', 'n');
        $mainquery->fields('n',array('id','title'));
        $mainquery->condition('n.main_type', $key, '=');
        $mainquery->condition('n.nid', $company->nid, '=');
        $resultmainsub = $mainquery->execute()->fetchAllKeyed(0,1);
        foreach ($resultmainsub as $subkey => $subvalue) {
          $subcatlistoption[$subkey] = $subvalue;
        }
  }
  $form['main_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="col-sm-12 thumbnail" id="scm_request_subtype_settings_main"><div class="col-sm-12 padding-0">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-subtypeedit-settings-reset'] = array(
    '#type' => 'select',
    '#options' => array(0=>0,1=>1),
    '#attributes' => array('class'=> array('form-control get-subtypeedit-settings-reset')),
    '#ajax' => array(
      'callback'=> 'change_scm_subtypeedit_settings_callbackreset',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-subtypeedit-settings'] = array(
    '#type' => 'select',
    '#options' => $maincatlistoption,
    '#attributes' => array('class'=> array('form-control get-subtypeedit-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_subtypeedit_settings_callback',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['get-subtypedelete-settings'] = array(
    '#type' => 'select',
    '#options' => $subcatlistoption,
    '#attributes' => array('class'=> array('form-control get-subtypedelete-settings')),
    '#ajax' => array(
      'callback'=> 'change_scm_subtypedelete_settings_callback',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" id="get-subtypedelete-settingsID" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main_container']['request-subtype-data'] = array(
    '#type' => 'markup',
    '#markup' => $setting_render_data,
    '#prefix' => '<div id="request_subtype-data-div-setting_render_data">',
    '#suffix' => '</div>',
  );
  $form['main_container']['request_maintype_new'] = array(
    '#title' => 'Request Type',
    '#type' => 'select',
    '#options' => $maincatlistoption,    
    '#attributes'=> array('class'=> array('form-control','workflow-auto','request_maintype_new')),
    '#empty_option' => 'Select the type of request',  
    '#required' => TRUE,
  );
  $form['main_container']['request_subtype_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add Request Subtype'),
    '#attributes' => array('class'=>array('request_subtype_new'),'placeholder' => t('Please enter request subtype here')),
    '#required' => TRUE,
  );
  $form['main_container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'scm_request_subtype_settings_form_submit_callback',
      'wrapper' => 'scm-request-subtype-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['main_container']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#ajax' => array(
      'callback'=> 'change_scm_subtypeedit_settings_callbackreset',
      'wrapper' => 'scm-request-subtype-settings-form',
      'effect' => 'fade',
    ),
  );
  $form['main_container']['subcategory-data-table'] = array(
    '#type' => 'markup',
    '#markup' => get_subcategory_data_tablesetting(),
    '#prefix' => '<div id="subtypecat-data-div">',
    '#suffix' => '</div>',
  );
  return $form;
}


function change_scm_subtypedelete_settings_callback($form, &$form_state) {
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-subtypedelete-settings'){
    db_delete('m6connect_scm_request_subtype_setting')->condition('id', $form_state['triggering_element']['#value'], '=')->execute();
     $commands[] = ajax_command_html("#request_subtype-data-div-setting_render_data", get_all_subtypebumainid($form_state['values']['request_maintype_new']));
    $commands[] = ajax_command_html("#subtypecat-data-div", get_subcategory_data_tablesetting());
  }
   return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_subtypeedit_settings_callback($form, &$form_state) {
  $commands = array();
  if($form_state['triggering_element']['#name']=='get-subtypeedit-settings'){
    $commands[] = ajax_command_invoke("select.request_maintype_new", 'val',array($form_state['triggering_element']['#value']));
    $commands[] = ajax_command_invoke("select.request_maintype_new", 'css',array('pointer-events','none'));
    $commands[] = ajax_command_html("#request_subtype-data-div-setting_render_data", get_all_subtypebumainid($form_state['triggering_element']['#value']));
    $commands[] = ajax_command_html("#subtypecat-data-div", get_subcategory_data_tablesetting());
  }
   return array('#type' => 'ajax', '#commands' => $commands);
}

 function get_department_data_tablesetting() {
    $setting_render_data = '<table class="table table-bordered m6connect-custom-table">';
    $setting_render_data .= '<thead><tr>';
    $setting_render_data .=  '<th class="text-left">Department</th>'; 
    $setting_render_data .=  '<th class="text-left">Department Approver</th>'; 
    $setting_render_data .=  '<th class="text-center">Action</th>'; 
    $setting_render_data .= '</tr></thead><tbody>';
    foreach (get_all_departments() as $key => $value) { 
      foreach($value['depapproval'] as $key => $val){
        $userss[$key] = user_load($val)->realname;
      }
      $setting_render_data .= '<tr>';
      $setting_render_data .=  '<td><div style="max-width: 150px;" class="text-left">'.ucwords($value['maincat']['title']).'</div></td>'; 
      $setting_render_data .=  '<td ><div style="max-width: 300px;" class="text-left">'.ucwords(implode(",",$userss)).'</div></td>'; 
      $setting_render_data .=  '<td class="text-center">
      <a href="javascript:void(0)" class="edit-depaction-cat-call" dataedit-depref="'.$value['maincat']['id'].'"><i class="fa fa-pencil-square-o" aria-hidden="true"></i></a>
      <a href="javascript:void(0)" class="delete-action-dep-call" fortitle="'.ucwords($value['maincat']['title']).'" datadelete-depref="'.$value['maincat']['id'].'"><i class="fa fa-trash-o" aria-hidden="true"></i></a></td>';  
      $setting_render_data .= '</tr>';
    }
    $setting_render_data .= '</tbody></table>';
    return $setting_render_data;
  }

  function get_subcategory_data_tablesetting() {
    $setting_render_data = '<table class="table table-bordered m6connect-custom-table">';
    $setting_render_data .= '<thead><tr>';
    $setting_render_data .=  '<th class="text-left">Request Type</th>'; 
    $setting_render_data .=  '<th class="text-left">Request Subtype</th>'; 
    $setting_render_data .=  '<th class="text-center">Action</th>'; 
    $setting_render_data .= '</tr></thead><tbody>';
    foreach (get_all_subtype() as $key => $value) { 
      $setting_render_data .= '<tr>';
      $setting_render_data .=  '<td><div style="max-width: 150px;" class="text-left">'.ucwords($value['maincat']['title']).'</div></td>';
      $setting_render_data .=  '<td ><div style="max-width: 300px;" class="text-left">'.implode(",",array_map('ucwords', $value['subcat'])).'</div></td>';
      $setting_render_data .=  '<td class="text-center">
      <a href="javascript:void(0)" class="edit-subtypeaction-cat-call" dataedit-subtyperef="'.$value['maincat']['id'].'"><i class="fa fa-pencil-square-o" aria-hidden="true"></i></a></td>';  
      $setting_render_data .= '</tr>';
    }
    $setting_render_data .= '</tbody></table>';
    return $setting_render_data;
  }
  
  function get_all_subtypebumainid($mainid){
    global $user, $company;
    $type = 'request_subtype';
    $subquery = db_select('m6connect_scm_request_subtype_setting', 'n');
    $subquery->fields('n',array('id','title'));
    $subquery->condition('n.main_type', $mainid, '=');
    $subquery->condition('n.nid', $company->nid, '=');
    $resultsubtype = $subquery->execute()->fetchAllKeyed(0,1);
    $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
    foreach ($resultsubtype as $keydata => $renderdata) {
      $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . ucwords($renderdata) . ' <span><i class="fa fa-times remove-scm-setting-options-subtype" aria-hidden="true" scm-type="'.$type.'" data="' . ucwords($renderdata) .'" deletedataref ="' .$keydata. '"></i></span></div>';
    }
    $setting_render_data .= '</div>';
    return $setting_render_data;
  }

  function get_all_departmentbumainid($mainid){
    global $user, $company;
    $type = 'department';
    $subquery = db_select('m6connect_scm_setting_department', 'n');
    $subquery->fields('n',array('id','title'));
    $subquery->condition('n.id', $mainid, '=');
    $subquery->condition('n.nid', $company->nid, '=');
    $resultsubtype = $subquery->execute()->fetchAllKeyed(0,1);
    $setting_render_data = '<div class="'.$type.'-data-outer clearfix">';
    foreach ($resultsubtype as $keydata => $renderdata) {
      $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . ucwords($renderdata) . ' <span><i class="fa fa-times remove-scm-setting-options-subtype" aria-hidden="true" scm-type="'.$type.'" data="' . ucwords($renderdata) .'" dpdeletedataref ="' .$keydata. '"></i></span></div>';
    }
    $setting_render_data .= '</div>';
    return $setting_render_data;
  }



  function get_all_subtype($mainid=''){
    global $user, $company;
    if(!empty($mainid)){
        $subquery = db_select('m6connect_scm_request_subtype_setting', 'n');
        $subquery->fields('n',array('id','title'));
        $subquery->condition('n.main_type', $mainid, '=');
        $subquery->condition('n.nid', $company->nid, '=');
        $resultsubtype = $subquery->execute()->fetchObject();
    } else {
      $query = db_select('m6connect_scm_request_type_setting', 'n');
      $query->fields('n');
      $query->condition('n.nid', $company->nid, '=');
      $result = $query->execute()->fetchAll();
      foreach ($result as $mainkey => $mainvalue) {
        $mainquery = db_select('m6connect_scm_request_subtype_setting', 'n');
        $mainquery->fields('n',array('id','title'));
        $mainquery->condition('n.main_type', $mainvalue->id, '=');
        $mainquery->condition('n.nid', $company->nid, '=');
        $resultmain = $mainquery->execute()->fetchAllKeyed(0,1);

        $datass[$mainkey]['maincat']['id'] = $mainvalue->id;
        $datass[$mainkey]['maincat']['title'] = $mainvalue->title;
        $datass[$mainkey]['subcat'] = $resultmain;
      }
    }
    return $datass;
  }

  function get_all_departments($mainid=''){
    global $user, $company;
    if(!empty($mainid)){
        $subquery = db_select('m6connect_scm_setting_department', 'n');
        $subquery->fields('n',array('id','title'));
        $subquery->condition('n.main_type', $mainid, '=');
        $subquery->condition('n.nid', $company->nid, '=');
        $datass = $subquery->execute()->fetchObject();
    } else {
      $query = db_select('m6connect_scm_setting_department', 'n');
      $query->fields('n');
      $query->condition('n.nid', $company->nid, '=');
      $result = $query->execute()->fetchAll();
      foreach ($result as $mainkey => $mainvalue) {
        $datass[$mainkey]['maincat']['id'] = $mainvalue->id;
        $datass[$mainkey]['maincat']['title'] = $mainvalue->title;
        $datass[$mainkey]['depapproval'] = explode('|', $mainvalue->dpapprover);
      }
    }
    return $datass;
  }

/* 
 * Ajax submit callback for request subtype form
 */
function scm_request_subtype_settings_form_submit_callback($form, &$form_state) {
  if (form_get_errors()) {
    return $form;
  }
  global $user, $company;
  $values = $form_state['values'];
  $type = 'request_subtype';
  $mainType = explode("-",$values['request_maintype_new'])[0];
  $new_value = $values['request_subtype_new'];
  $error = FALSE;
  if (empty($new_value)) {
    $error = TRUE;
    form_set_error('request_subtype_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }
  $new_value = strtolower(trim($new_value));
  $save_action = TRUE;
  $save_new_setting = _get_or_insert_scm_settings($type);
  if(in_array($new_value,$save_new_setting)){
    $save_action = FALSE;
  }
  if(isset($values,$new_value) && !empty($values) && !empty($new_value) && $save_action){
    $save_new_setting = _get_or_insert_scm_settings($type,$new_value,$mainType);    
  }
  // $setting_render_data = '<div id="'.$type.'-data-div"><div class="'.$type.'-data-outer clearfix">';
  // foreach ($save_new_setting as $save_newsetting) {
  //   $setting_render_data .= '<div class="'.$type.'-data-item rating-data-item display-inline-block">' . ucwords($save_newsetting) . ' <span><i class="fa fa-times remove-scm-setting-options" aria-hidden="true" scm-type="'.$type.'" data="' . ucwords($save_newsetting) . '"></i></span></div>';
  // }
  // $setting_render_data .= '</div></div>';
  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_invoke('select.request_maintype_new', 'val', array(''));
  $commands[] = ajax_command_html("#request_subtype-data-div-setting_render_data", '');
  //$commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  $commands[] = ajax_command_html("#subtypecat-data-div", get_subcategory_data_tablesetting());
  $commands[] = ajax_command_invoke("select.get-subtypeedit-settings-reset", 'trigger',array('change'));
  $commands[] = ajax_command_html("#get-subtypedelete-settingsID", render($form['main_container']['get-subtypedelete-settings']));
  $commands[] = ajax_command_invoke("select.request_maintype_new", 'css',array('pointer-events',''));
  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_scm_subtypeedit_settings_callbackreset($form, &$form_state){

  $commands = array();
  $commands[] = ajax_command_invoke('.'.$type.'_new', 'val', array(''));
  $commands[] = ajax_command_invoke('select.request_maintype_new', 'val', array(''));
  $commands[] = ajax_command_html("#request_subtype-data-div-setting_render_data", '');
  //$commands[] = ajax_command_replace("#".$type."-data-div", $setting_render_data, array());
  $commands[] = ajax_command_invoke("select.request_maintype_new", 'css',array('pointer-events',''));
  $commands[] = ajax_command_html("#subtypecat-data-div", get_subcategory_data_tablesetting());
  $commands[] = ajax_command_html("#get-subtypedelete-settingsID", render($form['main_container']['get-subtypedelete-settings']));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * SCM category type setting form
 */
function scm_category_settings_form($form, &$form_state) {
  global $user, $company;

  // Preform Building process.
  if (!isset($form_state['scl_count'])) {
    // We are not adding a row for a sub category, rather we are adding a row
    // for a unique Supply Chain Lead. Means under a supply chain lead there
    // can be several sub categories.
    $form_state['scl_count'][] = uniqid();
  }

  // Cancel button handling.
  if (!empty($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Cancel') {
    $form_state['input'] = array();
    $form_state['values'] = array();
    $form_state['default_values'] = array();
    $form_state['scl_count'] = array(uniqid());
  }

  // Submit button handling.
  if (!empty($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Save') {
    // If a save is triggered, then saving the form values.
    _save_category_form_values($form_state);

    // After saving, clearing the form.
    $form_state['input'] = array();
    $form_state['values'] = array();
    $form_state['default_values'] = array();
    $form_state['scl_count'] = array(uniqid());
  }

  // Handling editing of a category.
  if (!empty($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#name'] == 'all-categories') {
    // Unsetting the counter and default values, if any.
    unset($form_state['scl_count'], $form_state['default_values']);

    $main_cat_id = $form_state['triggering_element']['#value'];

    // First we get main category details, then its sub categories, separated
    // by supply chain leads.
    $main_cat_load = scm_category_load($main_cat_id);

    if (!empty($main_cat_load)) {
      $form_state['default_values']['main_cat_id'] = $form_state['input']['main-category-id'] = $main_cat_id;
      $form_state['default_values']['main_cat_name'] = $form_state['input']['main-category-name'] = $main_cat_load->title;
      $form_state['default_values']['main_cat_scl'] = $form_state['input']['main-category-scl'] = $main_cat_load->scl;
    }

    // Now handling all sub categories.
    $sub_cats_diff = _get_all_sub_categories_scm_grouped_by_scl($main_cat_id);

    if (!empty($sub_cats_diff)) {
      foreach ($sub_cats_diff as $sub_cat_scl => $sub_cat_name) {
        $uniqid = uniqid();
        $form_state['scl_count'][] = $uniqid;
        $form_state['default_values']['sub_cats'][$uniqid]['scl'] = $sub_cat_scl;

        $sub_cats_concatinated = array();
        foreach ($sub_cat_name as $key1 => $value1) {
          $sub_cats_concatinated[] = $value1;
        }

        $sub_cats_concatinated = implode(PHP_EOL, $sub_cats_concatinated);
        $form_state['default_values']['sub_cats'][$uniqid]['name'] = $sub_cats_concatinated;
      }
    }
  }

  $form['outer-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="main-container-table-div">',
    '#suffix' => '</div>',
  );

  $form['outer-container']['all-categories'] = array(
    '#type'       => 'select',
    '#title'      => t('All main categories.'),
    '#options'    => array('none' => t('None')) + _get_all_main_categories_scm(),
    '#prefix'     => '<div style="display:none;">',
    '#suffix'     => '</div>',
    '#attributes' => array('class' => array('all-main-cats-select')),
    '#ajax'       => array(
      'wrapper'  => 'category-form-main-container',
      'callback' => 'change_main_category_scm_settings',
    ),
  );

  // Main container, holding everything.
  $form['outer-container']['main-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="category-form-main-container">',
    '#suffix' => '</div>',
    '#weight' => 1,
  );

  // Main category container, it holds main category and SCL of main category.
  $form['outer-container']['main-container']['main-category'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="row">',
    '#suffix' => '</div>',
  );

  // We need this, when we are editing an entry.
  $form['outer-container']['main-container']['main-category']['main-category-id'] = array(
    '#type'          => 'hidden',
    '#default_value' => !empty($form_state['default_values']['main_cat_id']) ? $form_state['default_values']['main_cat_id'] : '',
  );

  // Name of main category.
  $form['outer-container']['main-container']['main-category']['main-category-name'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Category Name'),
    '#attributes'    => array('placeholder' => t('Please enter new category here.')),
    '#required'      => TRUE,
    '#prefix'        => '<div class="col-md-6">',
    '#suffix'        => '</div>',
    '#default_value' => !empty($form_state['default_values']['main_cat_name']) ? $form_state['default_values']['main_cat_name'] : '',
  );

  // Supply chain lead of main category.
  $form['outer-container']['main-container']['main-category']['main-category-scl'] = array(
    '#type'       => 'select',
    '#title'      => t('Supply Chain Lead'),
    '#options'    => get_scm_user_database_datasall('Supply Chain Lead'),
    '#multiple'   => FALSE,
    '#select2'    => array('width'=>'100%', 'placeholder' => t('Please choose supply chain lead')),
    '#attributes' => array('placeholder' => t('Please choose supply chain lead')),
    '#required'   => TRUE,
    '#prefix'     => '<div class="col-md-6">',
    '#suffix'     => '</div>',
  );

  if (!empty($form_state['default_values']['main_cat_scl'])) {
    $form['outer-container']['main-container']['main-category']['main-category-scl']['#default_value'] = $form_state['default_values']['main_cat_scl'];
  }

  // Now handling sub categories.
  // Sub categories can be added unlimited.
  $form['outer-container']['main-container']['sub-category'] = array(
    '#type'    => 'container',
    '#process' => array('scm_sub_category_process'),
    '#prefix'  => '<div id="category-form-sub-container" class="row">',
    '#suffix'  => '</div>',
    '#theme'   => 'scm_sub_cat_container_theme',
  );

  $form['outer-container']['category-listing'] = array(
    '#type' => 'markup',
    '#markup' => _get_category_listing_scm(),
    '#prefix' => '<div id="cat-listing-div" class="margin-bottom-10">',
    '#suffix' => '</div>',
    '#weight' => 3,
  );

  $form['outer-container']['actions'] = array(
    '#type' => 'actions',
    '#prefix' => '<div class="margin-bottom-10">',
    '#suffix' => '</div>',
    '#weight' => 2,
  );

  $form['outer-container']['actions']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save'),
    '#executes_submit_callback' => FALSE,
    '#ajax'  => array(
      'callback' => 'submit_category_form_ajax',
      'wrapper'  => 'main-container-table-div',
    ),
  );

  $form['outer-container']['actions']['cancel'] = array(
    '#type'  => 'submit',
    '#value' => t('Cancel'),
    '#limit_validation_errors' => array(),
    '#executes_submit_callback' => FALSE,
    '#ajax'  => array(
      'callback' => 'cancel_category_form_ajax',
      'wrapper'  => 'category-form-main-container',
    ),
  );

  return $form;
}

/**
 * Submit handler for scm_category_settings_form
 */
function scm_category_settings_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for change main category.
 */
function change_main_category_scm_settings($form, &$form_state) {
  return $form['outer-container']['main-container'];
}

/**
 * Ajax callback for cancel button.
 */
function cancel_category_form_ajax($form, &$form_state) {
  return $form['outer-container']['main-container'];
}

/**
 * Ajax callback for submit button.
 */
function submit_category_form_ajax($form, &$form_state) {
  return $form['outer-container'];
}

/**
 * Helper function to save category form data.
 */
function _save_category_form_values($form_state) {
  $values = $form_state['values'];

  global $user, $company;

  // First of all, updating the main category details in db.
  $main_cat_name = $values['main-category-name'];
  $main_cat_scl = $values['main-category-scl'];

  // Getting new categories and grouping these by SCL.
  $sub_cat_name_with_scl = array();

  if (!empty($form_state['scl_count'])) {
    foreach ($form_state['scl_count'] as $key => $value) {
      if (!empty(trim($values['sub-categories'][$value]['name']))) {
        // If we have something.
        // We have a text area, and each line of textarea means a sub category
        // , so getting to it.
        if (empty($values['sub-categories'][$value]['scl'])) {
          // If the value of supply chain lead is not given by user, then
          // treating it as the main supply chain lead.
          $scl_sub = $main_cat_scl;
        }
        else {
          $scl_sub = $values['sub-categories'][$value]['scl'];
        }

        if (!empty($sub_cat_name_with_scl[$scl_sub])) {
          $sub_cat_name_with_scl[$scl_sub] += explode(PHP_EOL, trim($values['sub-categories'][$value]['name']));
        }
        else {
          $sub_cat_name_with_scl[$scl_sub] = explode(PHP_EOL, trim($values['sub-categories'][$value]['name']));
        }
      }
    }
  }

  // We need to judge whether its update case or new case.
  if (!empty($values['main-category-id'])) {
    // Its update case.
    $main_cat_id = $values['main-category-id'];

    db_update('m6connect_scm_settings_categories')
      ->fields(array(
        'title'   => $main_cat_name,
        'scl'     => $main_cat_scl,
        'company' => $company->nid,
        'uid'     => $user->uid,
        'created' => REQUEST_TIME,
      ))
      ->condition('id', $main_cat_id)
      ->execute();

    // Now we need to update the sub categories of the main category.
    // For this, we first judge, what sub categories are removed, added new, or
    // updated.

    // Fetching all sub categories grouped by SCL.
    $old_sub_cats = _get_all_sub_categories_scm_grouped_by_scl($main_cat_id);

    // We have old and new sub categories grouped by SCL.
    // Now we check for every SCL, whether there are any changes.

    // First we shall be filtering out the values that are to be removed from DB.
    $delete_sub_ids = array();
    foreach ($old_sub_cats as $old_scl_id => $old_scl_cat) {
      if (!isset($sub_cat_name_with_scl[$old_scl_id])) {
        // This is the case, when either the whole sub category is removed, or
        // its SCL has been changed.
        // We shall be deleting all of these values from DB.
        $delete_ids = array_keys($old_scl_cat);
        $delete_sub_ids = array_merge($delete_sub_ids, $delete_ids);
      }
      else {
        // We have some values in new array, now filtering out which values
        // has to be deleted.
        $deleted_values = array_diff($old_scl_cat, $sub_cat_name_with_scl[$old_scl_id]);
        if (!empty($deleted_values)) {
          $deleted_values = array_keys($deleted_values);

          // Merging with any previous values.
          $delete_sub_ids = array_merge($delete_sub_ids, $deleted_values);
        }
      }
    }

    // Getting new values which are to be inserted in DB.
    $new_sub_ids = array();
    foreach ($sub_cat_name_with_scl as $new_scl_id => $new_scl_cat) {
      if (!isset($old_sub_cats[$new_scl_id])) {
        // This is the case, when a new SCL is added, or old is changed with
        // this new one.
        // We shall be inserting all sub categories of this SCL.
        $new_sub_ids[$new_scl_id] = $new_scl_cat;
      }
      else {
        // If it is the old SCL, then getting new values from it.
        $new_added_values = array_diff($new_scl_cat, $old_sub_cats[$new_scl_id]);
        if (!empty($new_added_values)) {
          $new_sub_ids[$new_scl_id] = $new_added_values;
        }
      }
    }

    // Deleting or adding any new sub categories.
    if (!empty($delete_sub_ids) && is_array($delete_sub_ids)) {
      db_delete('m6connect_scm_settings_categories')
        ->condition('id', $delete_sub_ids, 'IN')
        ->execute();
    }

    if (!empty($new_sub_ids)) {
      foreach ($new_sub_ids as $key => $value) {
        foreach ($value as $sub_cat_name) {
          db_insert('m6connect_scm_settings_categories')
            ->fields(array(
              'title'   => $sub_cat_name,
              'parent'  => $main_cat_id,
              'scl'     => $key,
              'company' => $company->nid,
              'uid'     => $user->uid,
              'created' => REQUEST_TIME,
            ))
            ->execute();
        }
      }
    }
  }
  else {
    $main_cat_auto_id = db_insert('m6connect_scm_settings_categories')
      ->fields(array(
        'title'   => $main_cat_name,
        'parent'  => 0,
        'scl'     => $main_cat_scl,
        'company' => $company->nid,
        'uid'     => $user->uid,
        'created' => REQUEST_TIME,
      ))
      ->execute();

    // Getting sub categories, if any.
    if (!empty($sub_cat_name_with_scl) && $main_cat_auto_id) {
      // We inserted the main category, now we need to insert, sub categories.
      foreach ($sub_cat_name_with_scl as $key => $value) {
        foreach ($value as $sub_cat_name) {
          db_insert('m6connect_scm_settings_categories')
            ->fields(array(
              'title'   => $sub_cat_name,
              'parent'  => $main_cat_auto_id,
              'scl'     => $key,
              'company' => $company->nid,
              'uid'     => $user->uid,
              'created' => REQUEST_TIME,
            ))
            ->execute();
        }
      }
    }
  }
}

/**
 * Process function for category - sub category form.
 */
function scm_sub_category_process($elements, &$form_state) {
  $scl_count = $form_state['scl_count'];

  if (empty($scl_count)) {
    $form_state['scl_count'][] = uniqid();
    $scl_count = $form_state['scl_count'];
  }

  $elements['#storage'] = $form_state['scl_count'];

  foreach ($scl_count as $uniqid) {
    $elements['sub-categories'][$uniqid] = array(
      '#type'          => 'textarea',
      '#title'         => t('Subcategories'),
      '#description'   => t('You can add multiple sub categories in this field.') . '<br/>' . t('Separate each sub category with a new line.'),
      '#parents'       => array('sub-categories', $uniqid, 'name'),
      '#prefix'        => '<div class="col-md-6">',
      '#suffix'        => '</div>',
      '#default_value' => !empty($form_state['default_values']['sub_cats'][$uniqid]['name']) ? $form_state['default_values']['sub_cats'][$uniqid]['name'] : '',
    );

    // Sub categories can have their own supply chain leads.
    $elements['sub-categories-scl'][$uniqid] = array(
      '#type'          => 'select',
      '#title'         => t('Supply Chain Lead'),
      '#options'       => array('' => '') + get_scm_user_database_datasall('Supply Chain Lead'),
      '#multiple'      => FALSE,
      '#select2'       => array('width'=>'100%', 'placeholder' => t('Please choose supply chain lead')),
      '#attributes'    => array('placeholder' => t('Please choose supply chain lead')),
      '#parents'       => array('sub-categories', $uniqid, 'scl'),
      '#prefix'        => '<div class="col-md-6">',
      '#suffix'        => '</div>',
    );
    if (!empty($form_state['default_values']['sub_cats'][$uniqid]['scl'])) {
      $elements['sub-categories-scl'][$uniqid]['#default_value'] = $form_state['default_values']['sub_cats'][$uniqid]['scl'];
    }
  }

  // Add new button.
  $elements['add_new_markup'] = array(
    '#markup' => '<div class="col-md-12 box-actions text-right"><a href="javascript:void(0);" title="Add new team member" onClick="jQuery(\'.sub-cat-add-new-button\').trigger(\'mousedown\'); return false;"><i class="glyphicon glyphicon-plus"></i> Add New Subcategory</a></div>'
  );
  $elements['sub_cat_add_new'] = array(
    '#type'                    => 'submit',
    '#value'                   => 'Add New',
    '#name'                    => 'sub_cat_add_new',
    '#attributes'              => array('class'=> array('sub-cat-add-new-button'), 'title'=>'Add New Subcategory'),
    "#limit_validation_errors" => array(),
    '#submit'                  => array('sub_cat_add_new_submit'),
    '#ajax'                    => array(
      'callback' => 'sub_cat_add_new_callback',
      'wrapper'  => 'category-form-sub-container',
      'method'   => 'replace',
      'effect'   => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
  );

  return $elements;
}

/**
 * Theme function for sub-category container.
 */
function theme_scm_sub_cat_container_theme($variables) {
  $elements = $variables['element'];

  $storage = $elements['#storage'];
  $output = '';

  // Rendering elements.
  foreach ($storage as $uniqid) {
    $output .= '<div class="row margin-0">';
    $output .= drupal_render($elements['sub-categories'][$uniqid]);
    $output .= drupal_render($elements['sub-categories-scl'][$uniqid]);
    $output .= '</div>';
  }

  $output .= drupal_render_children($elements);

  return $output;
}

/**
 * Ajax callback for adding a new sub category.
 */
function sub_cat_add_new_callback($form, &$form_state) {
  return $form['outer-container']['main-container']['sub-category'];
}

/**
 * Submit handler for adding a new sub category.
 */
function sub_cat_add_new_submit($form, &$form_state) {
  $form_state['scl_count'][] = uniqid();
  $form_state['rebuild'] = TRUE;
}

/**
 * Helper function to get category listing.
 */
function _get_category_listing_scm() {
  $header = array(
    array('data' => t('Category'), 'class' => array('text-left', 'col-md-3')),
    array('data' => t('Supply Chain Lead<br/>(Main Category)'), 'class' => array('text-left', 'col-md-2')),
    array('data' => t('Sub Categories'), 'class' => array('text-left', 'col-md-7')),
    // array('data' => t('Supply Chain Lead<br/>(Subcategory)'), 'class' => array('text-left', 'col-md-2')),
    // array('data' => t('Action'), 'class' => array('text-center', 'col-md-1')),
  );

  $rows = array();

  $all_categories = _get_all_main_categories_scm();

  if (!empty($all_categories)) {
    foreach ($all_categories as $main_cat_id => $main_cat_name) {
      $sub_cats_concatinated_final = '';
      // Getting main category SCL Name.
      $main_cat_scl = _get_main_cat_scl($main_cat_id);
      $main_cat_scl_name = ucwords(_get_user_full_name($main_cat_scl));
      // For each main category, more than one row can be created.
      // Getting all sub categories.
      $sub_cats_diff = _get_all_sub_categories_scm_grouped_by_scl($main_cat_id);

      if (!empty($sub_cats_diff)) {
        // Making a different row, for each.
        foreach ($sub_cats_diff as $scl_sub_id => $sub_cats) {
          // Getting sub category SCL Name.
          $sub_cat_scl_name = ucwords(_get_user_full_name($scl_sub_id));

          $sub_cats_concatinated = array();
          foreach ($sub_cats as $key1 => $value1) {
            $sub_cats_concatinated[] = $value1;
          }

          // Preparing actions.
          $action = '<a href="javascript:void(0)" title="Edit this category" class="edit-main-cat-scm" data="' . $main_cat_id. '"><i class="fa fa-pencil-square-o" aria-hidden="true"></i></a>&nbsp' . 
          l('<i class="fa fa-trash-o" aria-hidden="true"></i>', 'scm-cat-delete/' . $main_cat_id. '/' . $scl_sub_id . '/nojs', array('html' => TRUE, 'attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-assign-dashboard-popup-style'))));

          $title = $sub_cat_scl_name . $action;
          // $sub_cats_concatinated = implode(', ', $sub_cats_concatinated);
          $sub_cats_concatinated_final .= theme_item_list(array('items' => $sub_cats_concatinated, 'type' => 'ul', 'title' => $title));
        }

        if (empty($sub_cats_concatinated_final)) {
          $sub_cats_concatinated_final = t('No subcategories added!');
        }

        $rows[] = array(
          array('data' => $main_cat_name),
          array('data' => $main_cat_scl_name),
          array('data' => $sub_cats_concatinated_final),
          // array('data' => $sub_cat_scl_name),
          // array('data' => $action),
        );
      }
    }
  }

  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No content yet!'), 'attributes' => array('class' => array('table', 'm6connect-custom-table', 'm6connect-table-border', 'm6init-datatable', 'table-cat-scm-settings', 'scm-setting-table', 'table-full-width', 'margin-top-10'))));
}

/**
 * Menu callback for scm-cat-delete/%/%/%ctools_js
 */
function scm_cat_delete($main_cat_id = NULL, $scl_id = NULL, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax'        => TRUE,
      'title'       => t('Remove Categories.'),
      'main_cat_id' => $main_cat_id,
      'scl_id'      => $scl_id,
    );

    $output = ctools_modal_form_wrapper('scm_cat_delete_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('scm_cat_delete_form', $main_cat_id, $scl_id);
  }
}

/**
 * Form to delete category.
 */
function scm_cat_delete_form($form, &$form_state, $main_cat_id = NULL, $scl_id = NULL) {
  if (empty($form_state['main_cat_id']) && !empty($main_cat_id)) {
    $form_state['main_cat_id'] = $main_cat_id;
  }
  if (empty($form_state['scl_id']) && !empty($scl_id)) {
    $form_state['scl_id'] = $scl_id;
  }

  $warning_text = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to delete the sub categories for this Supply Chain Lead?') . '</p></h4>';
  $warning_text .= '<p>' . t('This action can\'t be undone.') . '</p></div>';

  $form['warning'] = array(
    '#type' => 'markup',
    '#markup' => $warning_text,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
  );

  if ($form_state['ajax']) {
    $form['cancel'] = array(
      '#type' => 'markup',
      '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click(); return false;"><input type="button" class="btn cancel-button" value="Close"></a>',
    );
  }

  return $form;
}

/**
 * Submit handler for scm_cat_delete_form
 */
function scm_cat_delete_form_submit($form, &$form_state) {
  if (!empty($form_state['main_cat_id']) && !empty($form_state['scl_id'])) {
    // We have main category id, and scl id of the sub categories.
    // We shall be deleting all the sub categories under the requested SCL, for
    // the given parent id.
    db_delete('m6connect_scm_settings_categories')
      ->condition('scl', $form_state['scl_id'])
      ->condition('parent', $form_state['main_cat_id'])
      ->execute();

    // After deleting, we need to update the table also.

    if ($form_state['ajax']) {
      $form_state['ajax_commands'][] = ajax_command_html('#cat-listing-div', _get_category_listing_scm());
    }
  }

  if ($form_state['ajax']) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

function get_all_cat(){
  global $user, $company;
  $query = db_select('m6connect_scm_settings_categories', 'n');
  $query->fields('n');
  $query->condition('n.parentID', 0, '=');
  $query->condition('n.companyID', $company->nid, '=');
  //$query->condition('n.UID', $user->uid, '=');
  $result = $query->execute()->fetchAll();
  foreach ($result as $mainkey => $mainvalue) {
    $mainquery = db_select('m6connect_scm_settings_categories', 'n');
    $mainquery->fields('n');
    $mainquery->condition('n.parentID', $mainvalue->id, '=');
    $mainquery->condition('n.companyID', $company->nid, '=');
    //$mainquery->condition('n.UID', $user->uid, '=');
    $resultmain = $mainquery->execute()->fetchAll();

    $datass[$mainkey]['maincat']['id'] = $mainvalue->id;
    $datass[$mainkey]['maincat']['title'] = $mainvalue->title;
    $datass[$mainkey]['userids'] = explode('|',$mainvalue->userID);
    foreach(explode('|',$mainvalue->userID) as $ukey => $uvalue) {
      // $userdatadb = get_single_userDBbyid($uvalue);
      $userdatadb = user_load($uvalue);
      $datass[$mainkey]['user'][$uvalue] = $userdatadb->realname;
    }
    foreach ($resultmain as $pkey => $pvalue) {
      $datass[$mainkey]['subcat'][$pvalue->id] = $pvalue->title;
    }
  }
  return $datass;
}

function get_single_userDBbyid($userid){
  $getquery = db_select('m6connect_scm_settings_user_database', 'n');
  $getquery->fields('n');
  $getquery->condition('n.id', $userid, '=');
  $getresult = $getquery->execute()->fetchObject();
  return $getresult;
}

function get_single_cat($name,$parid){
  global $user, $company;
  $query = db_select('m6connect_scm_settings_categories', 'n');
    $query->fields('n');
    $query->condition('n.name', $name, '=');
    $query->condition('n.parentID', $parid, '=');
    $query->condition('n.companyID', $company->nid, '=');
    //$query->condition('n.UID', $user->uid, '=');
    $result = $query->execute()->fetchObject();
    return $result;
}

function cat_sub_cat_invite_to_m6_process($element, &$form_state) {
  // Get all approved Cost code
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $storage = $form_state['cat_sub_cat_storage_value'];    
  $element['#storage'] = $storage;
  foreach ($storage as $key => $uniqId) {    
  $element['setting_category'][$uniqId] = array(
      '#type' => 'textfield',
      '#attributes'=> array('class'=> array('form-control vendor','workflow-auto','setting_category'),'placeholder'=>'Enter the category name'),
      '#autocomplete_path' => 'category-data/autocomplete',
      '#ajax' => array(
        'callback' => 'category_data_autocomplete_callback',
        'event' => 'blur',
        'wrapper' => 'workflow-container-section',
        'method' => 'replace',
        'effect' => 'fade',
      ), 
    '#parents' => array('alert',$uniqId,'setting_category'),
      '#prefix' => '<div class="clearfix form-item">',
      '#suffix' => '</div>',
    );
  $element['setting_sub_category'][$uniqId] = array(
      '#type' => 'textfield', 
    '#autocomplete_path' => 'sub-category-data/autocomplete',
      '#attributes'=> array('class'=> array('form-control','workflow-auto','setting_sub_category'),'placeholder'=>'Enter Subcategory'),
      '#parents' => array('alert',$uniqId,'line_master_number'),
    );
  $element['remove'][$uniqId] = array(
      '#type' => 'submit',
      '#value' => 'remove_setting_cat',
      '#name' => $uniqId,
      '#attributes'=> array('style'=> array('font-family:FontAwesome;'),'class'=>array('alert-container-section', 'workflow-remove-submit')),
      '#parents' => array('alert', $uniqId, 'remove'),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_cat_sub_cat_m6_row_handler'),
        '#ajax' => array(
          'callback' => 'remove_cat_subcat_row_callback',
          'wrapper' => 'alert-container-section',
          'method' => 'replace',
          'effect' => 'fade',
          'progress' => array('type'=> 'throbber', 'message'=> NULL),
        ),
      '#prefix' => '<div><i class="fa fa-trash-o get-removed" aria-hidden="true" style="font-size:24px; cursor:pointer;"></i>',
      '#suffix' => '</div>',    
      );

      if(isset($form_state['cat_sub_cat_storage_value'][$uniqId])) {
        $stdefault = $form_state['cat_sub_cat_storage_value'][$uniqId];
        $element['setting_category'][$uniqId]['#default_value'] = $stdefault['LIN'];
        $element['setting_sub_category'][$uniqId]['#default_value'] = $stdefault['IMN'];    
      }    
    }
  $element['workflow_add_new_row'] = array(
      '#type'=>'submit',
      '#value' => 'Add New',
      '#name' => 'workflow_add_new_row',
      '#attributes'=> array('class'=>array('routing-workflow-action','commitment-workflow-action-add-po-details'),'title'=>'Add New Row'),
      "#limit_validation_errors" => array(),
      '#submit'=> array('cat_sub_cat_submit_handler_invite_m6'),
      '#ajax' => array(
        'callback' => 'cat_sub_cat_row_invite_m6_action_callback',
        'wrapper' => 'alert-container-section',
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
    );
  return $element;
}

function category_data_autocomplete_callback($form,&$form_state) {
  global $company;
  $commands = array();  
  $categoryListing = _get_scm_setting_data_calling('category');
  $companyListing = array_flip($companyListing);
  $triggering_element = $form_state['triggering_element'];
  $identifer = $triggering_element['#parents'][1];
  
  // Check for categoty
  // First check if category exists in the sytem
  // if form state contains category id then its from system
  if(!empty($form_state['values']['category_id'])) {
    // if has company nid then we need to load vendor number by company nid
    $getCatId = $form_state['values']['category_id'];
      // Get vendor number from the system 
    // which are already added for this vendor
    $query = db_select('node','n');
    $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));    
    $query->join('field_data_field_vendor_number','vn', 'vn.entity_id = n.nid');
    $query->join('field_data_field_vendor','fv', 'fv.entity_id = n.nid');
    $query->fields('vn', array('field_vendor_number_value'));
    $query->condition('om.gid', $company->nid, '=');
    $query->condition('fv.field_vendor_value', $getVenodrName, '=');
    $getVendorNumber = $query->execute()->fetchField();
    if(!empty($getVendorNumber)) {
      $commands[] = ajax_command_invoke("input.vendor_number", 'val',array($getVendorNumber));
    }
  }
  else {
    // if has company nid then we need to load vendor number by company nid
  $getVenodrName = $triggering_element['#value'];
    // Get vendor number from the system 
  // which are already added for this vendor
  $query = db_select('node','n');
    $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));    
    $query->join('field_data_field_vendor_number','vn', 'vn.entity_id = n.nid');
  $query->join('field_data_field_vendor','fv', 'fv.entity_id = n.nid');
    $query->fields('vn', array('field_vendor_number_value'));
    $query->condition('om.gid', $company->nid, '=');
    $query->condition('fv.field_vendor_value', $getVenodrName, '=');
    $getVendorNumber = $query->execute()->fetchField();
  if(!empty($getVendorNumber)) {
    $commands[] = ajax_command_invoke("input.vendor_number", 'val',array($getVendorNumber));
  }
  }
  
  $companyNid='';
  if(isset($companyListing[$triggering_element['#value']])){
    $companyNid = $companyListing[$triggering_element['#value']];
    if(is_numeric($companyNid)) {
      $getCompanyDetails = node_load($companyNid);
      if(isset($getCompanyDetails->field_logo['und'])) {
        $companyLogo = '<img src="'.image_style_url('thumbnail', $getCompanyDetails->field_logo['und'][0]['uri']).'">'; 
      }
      else {
        $companyLogo = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" style="height:100px; width:66px;">';
      }
      $commands[] = ajax_command_html(".company-details-by-email", '<label>&nbsp;</label>'.$companyLogo.'<strong>&nbsp;&nbsp;&nbsp;'.$getCompanyDetails->title.'</strong>');  
      $commands[] = ajax_command_invoke("input.company_nid", 'val',array($companyNid));
      $commands[] = ajax_command_invoke("input.outside_company", 'val',array('no'));
    }
    else {
      $commands[] = ajax_command_html(".company-details-by-email", '<label>&nbsp;</label><strong>'.$triggering_element['#value'].'</strong>');  
      $commands[] = ajax_command_invoke("input.company_nid", 'val',array($triggering_element['#value']));
      $commands[] = ajax_command_invoke("input.outside_company", 'val',array('yes'));
    }
  }  
  else {
    $commands[] = ajax_command_html(".company-details-by-email", '<label>&nbsp;</label><strong>'.$triggering_element['#value'].'</strong>');  
    $commands[] = ajax_command_invoke("input.company_nid", 'val',array($triggering_element['#value']));
    $commands[] = ajax_command_invoke("input.outside_company", 'val',array('yes'));
  }  
  return array('#type' => 'ajax','#commands' => $commands);
}

function scm_settings_grouplist($default){
  global $user,$company;
  $querys = db_select('m6connect_scm_settings_meta_group','n');
  $querys->fields('n', array('id', 'Label'));
  $querys->condition('n.companyID', $company->nid, '=');
  $querys->condition('n.scmID', $user->uid, '=');
  $querys->condition('n.type', $default, '=');
  $getallgroup = $querys->execute()->fetchAllKeyed(0,1);
  return $getallgroup;
}

function gettablexatsetting() {
  $setting_render_data = '<table class="table table-bordered m6connect-custom-table">';
  $setting_render_data .= '<thead><tr>';
  $setting_render_data .=  '<th class="text-left col-md-2">Category</th>'; 
  $setting_render_data .=  '<th class="text-left col-md-8">Subcategory </th>'; 
  $setting_render_data .=  '<th class="text-left col-md-2">Category Leader</th>';
  $setting_render_data .=  '<th class="text-center col-md-2">Action</th>'; 
  $setting_render_data .= '</tr></thead><tbody>';
  foreach (get_all_cat() as $key => $value) { 
    $setting_render_data .= '<tr>';
    $setting_render_data .=  '<td><div  class="text-left">'.ucwords($value['maincat']['title']).'</div></td>'; 
    $setting_render_data .=  '<td ><div  class="text-left">'.ucwords(implode(",",$value['subcat'])).'</div></td>'; 
    $setting_render_data .=  '<td ><div  class="text-left">'.ucwords(implode(",",$value['user'])).'</div></td>';
    $setting_render_data .=  '<td class="text-center">
    <a href="javascript:void(0)" class="edit-action-cat-call" dataedit-ref="'.$value['maincat']['id'].'"><i class="fa fa-pencil-square-o" aria-hidden="true"></i></a>
    <a href="javascript:void(0)" fortitle="'.$value['maincat']['title'].'" class="delete-action-cat-call" datadelete-ref="'.$value['maincat']['id'].'"><i class="fa fa-trash-o" aria-hidden="true"></a></i></td>';  
    $setting_render_data .= '</tr>';
  }
  $setting_render_data .= '</tbody></table>';
  return $setting_render_data;
}

function scm_request_type_settings_meta_formdata_save($allfieldarr) {
  global $user,$company;
  $commands = array();
  foreach ($allfieldarr as $key => $value) {
    $groupdata['Label'] = $value['main-group-name'];
    $groupdata['scm_group_key'] = string_to_slug($value['main-group-name']).'_'.$company->nid.'_'.$user->uid;
    $groupdata['value'] = '';
    $groupdata['type'] = 1;
    $groupdata['companyID'] = $company->nid;
    $groupdata['scmID'] = $user->uid;
    $groupdata['formate'] = $value['main-group-formate'];
    $groupdata['size'] = $value['main-group_area_size'];
    if(isset($value['main-group_default_name']) && !empty($value['main-group_default_name'])){
      $groupdata['default_name'] = $value['main-group_default_name'];
    }
    if(isset($value['main-group_required']) && !empty($value['main-group_required'])){
      $groupdata['required_state'] = $value['main-group_required'];
    }
    $groupdata['Numberofvalues'] = $value['main-group-number_of_values'];
    if($value['main-group-type']==1){
      db_update('m6connect_scm_settings_meta_group')
                                ->fields($groupdata)
                                ->condition('id', $value['main-group-id'], '=')
                                ->execute();
      $getgroupID = $value['main-group-id'];                          
    } else {
      $getgroupID = db_insert('m6connect_scm_settings_meta_group')->fields($groupdata)->execute();
    }
    foreach ($value['main-group-fields'] as $fkey => $fvalue) {
      $groupfield_data['Label'] = $fvalue['field_label'];
      $groupfield_data['scm_field_key'] = string_to_slug($value['field_label']).'_'.$getgroupID['id'].'_'.$company->nid.'_'.$user->uid;
      $groupfield_data['type'] = $fvalue['field_type'];
      $groupfield_data['value'] = $fvalue['field_detailsoption'];
      if(isset($fvalue['field_relation_parent']) && !empty($fvalue['field_relation_parent'])) {
        $groupfield_data['relation_parent'] = $fvalue['field_relation_parent'];  
      }
      if(isset($fvalue['name-default']) && !empty($fvalue['name-default'])) {
        $groupfield_data['name_default'] = $fvalue['name-default'];  
      }
      $groupfield_data['scm_field_group'] = $getgroupID;
      $groupfield_data['scm_field_order'] = $fkey;
      $groupfield_data['companyID'] = $company->nid;
      $groupfield_data['scmID'] = $user->uid;
      if(isset($fvalue['field_companyID']) && !empty($fvalue['field_companyID']) && isset($fvalue['field_scmID']) && !empty($fvalue['field_scmID'])) {
        $getgroupfielddataID = db_update('m6connect_scm_settings_mata_field')
                                ->fields($groupfield_data)
                                ->condition('id', $fvalue['field_id'], '=')
                                ->execute();
      } else {
        $getgroupfielddataID = db_insert('m6connect_scm_settings_mata_field')->fields($groupfield_data)->execute();
      }
    }
  }
  $commands[] = ajax_command_html("#add_and_update_fieldssettings_custom", drupal_render(drupal_get_form('add_and_update_fieldssettings')));  
  return array('#type' => 'ajax', '#commands' => $commands);
}

function get_all_field_companybase() {
  global $user,$company;
  $query = db_select('m6connect_scm_settings_mata_field', 'n');
  $query->fields('n',array('id','Label'));
  $query->condition('n.companyID', $company->nid, '=');
  $query->condition('n.scmID', $user->uid, '=');
  $resultmeta = $query->execute()->fetchAllKeyed(0,1);
  return $resultmeta;
}

function get_all_group_companybase() {
  global $user,$company;
  $query = db_select('m6connect_scm_settings_meta_group', 'n');
  $query->fields('n',array('id','Label'));
  $query->condition('n.companyID', $company->nid, '=');
  $query->condition('n.scmID', $user->uid, '=');
  $resultmeta = $query->execute()->fetchAllKeyed(0,1);
  return $resultmeta;
}  

function default_dependent_fielddata() {
  $field_data = '[{"main-group-id":"1","main-group-type":"0","main-group-name":"Manufacturer","main-group-formate":"0","main-group-number_of_values":"","main-group_area_size":4,"main-group-fields":[{"field_id":"1","field_relation_parent":"1","field_label":"Choose Company","field_type":"company","field_detailsoption":"","name-default":"choose-company"},{"field_id":"3","field_relation_parent":"3","field_label":"Contact Name","field_type":"textfield","field_detailsoption":"","name-default":"contact-name"},{"field_id":"4","field_relation_parent":"4","field_label":"Contact Email","field_type":"textfield","field_detailsoption":"","name-default":"contact-email"},{"field_id":"5","field_relation_parent":"","field_label":"Contact Phone","field_type":"textfield","field_detailsoption":"","name-default":"contact-phone"},{"field_id":"6","field_relation_parent":"5","field_label":"Contract Number","field_type":"textfield","field_detailsoption":"","name-default":"contract-number"}],"main-group_default_name":"manufacturer_group_default","main-group_required":"1"},{"main-group-id":"2","main-group-type":"0","main-group-name":"Vendor","main-group-formate":"1","main-group-number_of_values":"","main-group_area_size":4,"main-group-fields":[{"field_id":"7","field_relation_parent":"","field_label":"Same as Manufacturer","field_type":"checkbox","field_detailsoption":"1:Same as Manufacturer","name-default":"same-as-manufacturer"},{"field_id":"8","field_relation_parent":"1","field_label":"Choose Company","field_type":"company","field_detailsoption":"","name-default":"choose-company"},{"field_id":"10","field_relation_parent":"3","field_label":"Contact Name","field_type":"textfield","field_detailsoption":"","name-default":"contact-name"},{"field_id":"11","field_relation_parent":"4","field_label":"Contact Email","field_type":"textfield","field_detailsoption":"","name-default":"contact-email"},{"field_id":"12","field_relation_parent":"5","field_label":"Contact Phone","field_type":"textfield","field_detailsoption":"","name-default":"contact-phone"},{"field_id":"13","field_relation_parent":"6","field_label":"Contract Number","field_type":"textfield","field_detailsoption":"","name-default":"contract-number"}],"main-group_default_name":"vendor_group_default","main-group_required":"1"},{"main-group-id":"4","main-group-type":"0","main-group-name":"Notes","main-group-formate":"2","main-group-number_of_values":"","main-group_area_size":4,"main-group-fields":[{"field_id":"21","field_relation_parent":"","field_label":"Note","field_type":"textarea","field_detailsoption":"","name-default":"note"}],"main-group_default_name":"others_group_default","main-group_required":"-1"}]';
  return $field_data;
}

function allow_edit_flag_form($form, &$form_state) {
  global $company;

  if (!empty($form_state['triggering_element']['#name']) && $form_state['triggering_element']['#name'] == 'allow-flag') {
    // Saving the value.
    $edit_flag_val = variable_get('edit_flag_val', array());

    $edit_flag_val[$company->nid] = $form_state['triggering_element']['#value'];
    variable_set('edit_flag_val', $edit_flag_val);
  }

  // Getting previous value, if any.
  $default_edit_flag_val = variable_get('edit_flag_val', array());

  $form['allow-flag'] = array(
    '#type'  => 'checkbox',
    '#title' => t('Allow Users to Edit SCR Request Number.'),
    '#description' => t('If checked, this flag will allow the users (non-admin) to edit any SCR request number and change it.'),
    '#ajax' => array(
      'callback' => 'set_allow_flag_value_callback',
      'wrapper' => 'allow-flag-container',
    ),
    '#prefix' => '<div id="allow-flag-container">',
    '#suffix' => '</div>',
  );

  if (!empty($default_edit_flag_val[$company->nid])) {
    $form['allow-flag']['#default_value'] = $default_edit_flag_val[$company->nid];
  }

  return $form;
}

function set_allow_flag_value_callback($form, &$form_state) {
  return $form['allow-flag'];
}