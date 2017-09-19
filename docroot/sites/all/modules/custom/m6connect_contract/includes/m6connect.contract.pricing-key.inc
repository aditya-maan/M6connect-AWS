<?php
/**
 * Start work for m6connect contract
 * generating m6connect contract form, my request data table to show all records.
 * it also contains the chat feature.  
 */

function pricing_key() {
  $elements = array();

  $elements['prgram-scm-menu-items'] = array(
    '#markup' => m6connect_contract_list_menu(),
    '#prefix' => '<div class="clearfix csemanager-sub-menu-new margin-top-10 margin-bottom-45 scm-product-submenu-sp">',
    '#suffix' => '</div>',  
  );

  // Contact Pricing&Details Form.
  $contract_pricingkey_form = drupal_get_form('contract_pricingkey_form');
  $elements['contact-pricing-form'] = array(
    '#type'       => 'markup',
    '#markup'     => drupal_render($contract_pricingkey_form),
  );

  return $elements;
}

function contract_pricingkey_form($form, &$form_state) {
  if (!isset($form_state['date_count'])) {
    $form_state['date_count'] = array(uniqid());
  }

  if (!isset($form_state['notification_count'])) {
    $form_state['notification_count'] = array(uniqid());
  }

  $form['form-label-title'] = array(
    '#type'       => 'markup',
    '#markup'     => '<h4>' . t('Pricing') . '</h4>',
    '#prefix'     => '<div>',
    '#suffix'     => '</div>',
  );

  /*$form['pricing-container'] = array(
    '#type'       => 'container',
    '#process'    => array('pricing_form_outer_container_process'),
    '#prefix'     => '<div class="no-bg well well-large">',
    '#suffix'     => '</div>',
  );*/

  $form['key-dates'] = array(
    '#type'       => 'container',
    '#process'    => array('keydates_form_outer_container_process'),
    '#prefix'     => '<h4>Key Dates</h4><div class="no-bg well well-large">',
    '#suffix'     => '</div>',
  );

  /*$form['notification'] = array(
    '#type'       => 'container',
    '#process'    => array('notification_form_outer_container_process'),
    '#prefix'     => '<h4>Notification(s)</h4><div class="no-bg well well-large">',
    '#suffix'     => '</div>',
  );*/
 /* $form['notification'] = array(
    '#type'         => 'container',
    '#prefix'     => '<h4>Notification(s)</h4><div id="notification-container-div" class="no-bg well well-large contract-thread">',
    '#suffix'     => '</div>',
    '#theme'      => 'notification_container_theme',
    '#process'    => array('notification_form_outer_container_process'),
  );*/


  // Form Actions.
  // Save and Continue Button
  $form['actions']['submit'] = array(
    '#type'       => 'submit',
    '#value'      => t('Save and Continue'),
  );

  // Back Button.
  $form['actions']['back'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Back'), 'contract-manager/thread/new', array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  );
  
  // Cancel Button.
  $form['actions']['reset'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Cancel'), '#' , array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  );
 
  return $form;
}

function pricing_form_outer_container_process($elements, &$form_state) {
  $elements['pricing-main-container'] = array(
    '#type'           => 'container',
    '#attributes'     => array('class' => array('clearfix')),
  );

  // First Container Start
  $elements['pricing-main-container']['first-container'] = array(
    '#type' => 'container',
    '#prefix'        => '<div class="col-md-2">',
    '#suffix'        => '</div>',
    '#attributes' => array('class' => array('')),
  );

  $elements['pricing-main-container']['first-container']['purchase-price'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Purchase Price',
    '#attributes'    => array('placeholder' => '$0.00'),
  //  '#required' => TRUE,
  );

  $elements['pricing-main-container']['first-container']['implementation-costs'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Implementation Costs',
    '#attributes'    => array('placeholder' => '$0.00'),
  //  '#required' => TRUE,
  );
  // First Container Ends.

  // Second Container Start
  $elements['pricing-main-container']['second-container'] = array(
    '#type' => 'container',
    '#prefix'        => '<div class="col-md-2">',
    '#suffix'        => '</div>',
    '#attributes' => array('class' => array('')),
  );
  // Second Container End

  // Third Container Start.
  $elements['pricing-main-container']['third-container'] = array(
    '#type'         => 'container',
    '#prefix'       => '<div class="col-md-4">',
    '#suffix'       => '</div>',
    '#attributes'   => array('class' => array('')),
  );

  $elements['pricing-main-container']['third-container']['ireoccuring-costs'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Reoccuring Costs',
    '#attributes'    => array('placeholder' => '$0.00'),
    '#prefix'       => '<div class="col-md-6">',
    '#suffix'       => '</div><div class="col-md-6"></div>',
    //'#required' => TRUE,
  );
   
   
  $option = drupal_map_assoc(array( t('0'), t('1'), t('2')));
  $elements['pricing-main-container']['third-container']['implementation-cost-frequency'] = array(
    '#type'         => 'select',
    '#title'        => 'Implementation Cost Frequency',
    '#options'      => array('' => 'Select Frequency') + $option,
    '#prefix'       => '<div class="col-md-12">',
    '#suffix'       => '</div>',
  );
  // Third container end  
  
  // Fourth Container Starts.
  $elements['pricing-main-container']['fourth-container'] = array(
    '#type'         => 'container',
    '#prefix'       => '<div class="col-md-4">',
    '#suffix'       => '</div>',
    '#attributes'   => array('class' => array('')),
  );

  $option1 = drupal_map_assoc(array( t('0'), t('1'), t('2')));
  $elements['pricing-main-container']['fourth-container']['reoccuring-cost-frequency'] = array(
    '#type'         => 'select',
    '#title'        => 'Reoccuring Cost Frequency',
    '#options'      => array('' => 'Select Frequency') + $option1,
  );

  $option1 = drupal_map_assoc(array( t('0'), t('1'), t('2')));
  $elements['pricing-main-container']['fourth-container']['implementation-cost-term'] = array(
    '#type'         => 'select',
    '#title'        => 'Implementation Cost Term',
    '#options'      => array('' => 'Select Term') + $option1,
  ); 
  // Fourth Container End. 

  return $elements;
}

// Key Dates Conatiner Process Start
function keydates_form_outer_container_process($elements, &$form_state) {
  $elements['key-main-container'] = array(
    '#type'           => 'container',
    '#attributes'     => array('class' => array('clearfix')),
  );

  // First Container Start
  $elements['key-main-container']['first-container'] = array(
    '#type' => 'container',
    '#prefix'        => '<div class="col-md-2">',
    '#suffix'        => '</div>',
    '#attributes' => array('class' => array('')),
  );

  $elements['key-main-container']['first-container']['conclusion-due-date'] = array(
    '#type'            => 'date_popup',
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#title'           => 'Conclusion Due Date',
    '#attributes'      => array('class' => array('form-control', 'vendor-due-date'), 'placeholder' => t('mm/dd/yyyy')),
    '#prefix'          => '<div class="clearfix get-date dates-desc-sp"><div class="form-item padding-0 clearfix relative m6connect_share_date margin-bottom-10">',
    '#suffix'          => '</div></div>',
    '#field_suffix'    => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span>',
  ); 
  // First Container Ends.

  // Second Container.
  $elements['key-main-container']['second-container'] = array(
    '#type'         => 'container',
    '#prefix'       => '<div class="col-md-2 dates-cal-chk">',
    '#suffix'       => '</div>',
    '#attributes'   => array('class' => array('')),
  );

  $elements['key-main-container']['second-container']['due-status-lights'] = array(
    '#type' => 'checkbox',
    '#title' => t('Status Lights'),
  );
  // Second container end  
  
  // Third Container Starts.
  $elements['key-main-container']['third-container'] = array(
    '#type'         => 'container',
    '#prefix'       => '<div class="col-md-2">',
    '#suffix'       => '</div>',
    '#attributes'   => array('class' => array('')),
  );
  $elements['key-main-container']['third-container']['renewal-review-date'] = array(
    '#type'            => 'date_popup',
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',  
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#title'           => 'Renewal Review Date',
    '#attributes'      => array('class' => array('form-control', 'vendor-due-date'), 'placeholder' => t('mm/dd/yyyy')),
    '#prefix'          => '<div class="clearfix get-date dates-desc-sp"><div class="form-item padding-0 clearfix relative m6connect_share_date margin-bottom-10">',
    '#suffix'          => '</div></div>',
    '#field_suffix'    => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span>',
  );  
  // Third Container Starts End. 

  // Fourth Container.
  $elements['key-main-container']['fourth-container'] = array(
    '#type'         => 'container',
    '#prefix'       => '<div class="col-md-2 dates-cal-chk">',
    '#suffix'       => '</div>',
    '#attributes'   => array('class' => array('')),
  );
  $elements['key-main-container']['fourth-container']['review-status-lights'] = array(
    '#type' => 'checkbox',
    '#title' => t('Status Lights'),
  );
  // Fourth Container end

  // Fifth Container Start
  $elements['key-main-container-key'] = array(
    '#type'         => 'container',
    '#prefix'     => '<div id="main-outer-container-div" class="no-bg well well-large contract-thread">',
    '#suffix'     => '</div>',
    '#theme'      => 'outer_container_theme',
    '#process'    => array('key_date_name_form'),
  );
  // Fifth Container End
 
  return $elements;
}
// Key Dates Contanier Process End

// Key Date Name Contanier Process Start
function key_date_name_form($elements, &$form_state) {
  $elements['#storage'] = $form_state['date_count'];
  foreach ($form_state['date_count'] as $uniqid) {
    $elements[$uniqid]['key-date-name'] = array(
      '#type'          => 'textfield',
      '#title'         => 'Key Date Name',
      '#attributes'    => array('placeholder' => '$0.00'),
      '#parents' => array('key_dates', $uniqid, 'key-date-name'),
      '#prefix'     => '<div class="row"><div class="col-md-4">',
      '#suffix'     => '</div>',
    ); 

    $elements[$uniqid]['conclusion-due-date'] = array(
      '#type'            => 'date_popup',
      '#date_format'     => 'm/d/Y',
      '#date_year_range' => '-3:+3',  
      '#pre_render'      => array('m6connect_programe_date_prerender'),
      '#title'           => 'Date',
      '#attributes'      => array('class' => array('form-control', 'vendor-due-date'), 'placeholder' => t('mm/dd/yyyy')),
      '#prefix'          => '<div class="clearfix get-date-sp dates-desc-sp col-md-2"><div class="form-item padding-0 clearfix relative m6connect_share_date margin-bottom-10">',
      '#suffix'          => '</div></div>',
      '#field_suffix'    => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span>',
      '#parents' => array('key_dates', $uniqid, 'conclusion-due-date'),
    );

    $elements[$uniqid]['date-status-lights'] = array(
      '#type' => 'checkbox',
      '#title' => t('Status Lights'),
      '#parents' => array('key_dates', $uniqid, 'date-status-lights'),
      '#prefix'     => '<div class="col-md-2 dates-cal-chk">',
      '#suffix'     => '</div><div class="col-md-4"></div></div>',
    );
    // Third Container End
  }

  $elements['datekey_new_row'] = array(
    '#type'       => 'submit',
    '#value'      => t('Add Key Date'),
    '#name'       => 'datekey_new_row',
    '#attributes' => array('class'=> array('contact-new-row-button')),
    '#submit'     => array('key_date_new_row_callback_submit'),
    '#ajax'       => array(
      'callback'  => 'key_date_new_row_callback',
      'wrapper'   => 'main-outer-container-div',
      'method'    => 'replace',
      'effect'    => 'fade',
      'progress'  => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix'     => '<div class="row padding-10"><div class="col-md-12">',
    '#suffix'     => '</div></div>',
  );
  return $elements;
}
// Key Date Name Conatiner End

// Notification Contanier Start
function notification_form_outer_container_process($elements, &$form_state) {
  $elements['#storage'] = $form_state['notification_count'];

  foreach ($form_state['notification_count'] as $uniqid) {

    // First Container Start
    $elements[$uniqid]['first-container'] = array(
      '#type' => 'container',
      '#prefix'        => '<div class="col-md-4">',
      '#suffix'        => '</div>',
      '#attributes' => array('class' => array('')),
    );

    $elements[$uniqid]['first-container']['who-to-notify'] = array(
      '#type'          => 'textfield',
      '#title'         => 'Who to Notify',
      '#attributes'    => array('placeholder' => 'Contact Name'),
      '#parents' => array('notification_count', $uniqid, 'who-to-notify'),
    );

    $elements[$uniqid]['first-container']['notification-date'] = array(
      '#type'            => 'date_popup',
      '#date_format'     => 'm/d/Y',
      '#date_year_range' => '-3:+3',  
      '#pre_render'      => array('m6connect_programe_date_prerender'),
      '#title'           => 'Notification Date',
      '#attributes'      => array('class' => array('form-control', 'vendor-due-date'), 'placeholder' => t('mm/dd/yyyy')),
      '#prefix'          => '<div class="clearfix get-date dates-desc-sp"><div class="form-item padding-0 clearfix relative m6connect_share_date margin-bottom-10">',
      '#suffix'          => '</div></div>',
      '#field_suffix'    => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span>',
      '#parents' => array('notification_count', $uniqid, 'notification-date'),
    ); 

    $elements[$uniqid]['first-container']['notification-name'] = array(
      '#type'          => 'textfield',
      '#title'         => 'Notification Name',
      '#attributes'    => array('placeholder' => 'Notification Name'),
      '#parents' => array('notification_count', $uniqid, 'notification-name'),
    );
    // First Container Ends.

    // Second Container Start
    $elements[$uniqid]['second-container'] = array(
      '#type' => 'container',
      '#prefix'        => '<div class="col-md-4">',
      '#suffix'        => '</div>',
      '#attributes' => array('class' => array('')),
    );

    drupal_add_js('jQuery(document).ready(function () {
      jQuery(".new_alert_form_submit").click(function(event){
        var phone_id = [];
      jQuery(".international_phone-number").each(function(){
        var unique_id = jQuery(this).attr("uni_id");
        var cun_code = jQuery(this).closest(".intl-tel-input").find(".selected-flag").attr("title");
        jQuery(".edit-alert-"+unique_id+"-phone-code").val(cun_code);
      });
      });     
    });',  'inline');

    $elements[$uniqid]['second-container']['phone'] = array(
      '#type'           => 'textfield',
      '#title'          => 'Phone #',
      '#parents' => array('notification_count', $uniqid, 'phone'),
      '#attributes'     => array( 'class'=> array('form-control','workflow-auto', 'international_phone-number'),'placeholder'=>'Phone Number'),
     // '#required'       => TRUE,
      '#attached'       => array(
          'css'     => array(
            drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css',
          ),
          'js'      =>array(
            drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js',
            drupal_get_path('module', 'international_phone') . '/js/international_phone.js'
          ),
        ), 
      ); 
    $elements[$uniqid]['second-container']['phone_code'] = array(
      '#type'           => 'hidden',  
      '#default_value'  => '', 
    );

    $recurring_option = drupal_map_assoc(array( t('Hourly'), t('daily'), t('Weekly'), t('Monthly'), t('Half-Yearly'), t('Yearly')));
    $elements['second-container']['recurring'][$uniqid] = array(
      '#type'         => 'select',
      '#title'        => 'Recurring',
      '#options'      => array('' => 'Select Recurring') + $recurring_option,
      '#parents' => array('notification_count', $uniqid, 'recurring'),
    );
    
    $type_option = drupal_map_assoc(array( t('Email'), t('Text')));
    $elements[$uniqid]['second-container']['notification-template'] = array(
      '#type'         => 'select',
      '#title'        => 'Notification Template',
      '#options'      => array('' => 'Select Notification Template') + $type_option,
      '#parents' => array('notification_count', $uniqid, 'notification-template'),
    );
    // Second Container End

    // Third Container Start.
    $elements[$uniqid]['third-container'] = array(
      '#type' => 'container',
      '#prefix'        => '<div class="col-md-4">',
      '#suffix'        => '</div>',
      '#attributes' => array('class' => array('')),
    );

    $elements[$uniqid]['third-container']['email-address'] = array(
      '#type'          => 'textfield',
      '#title'         => 'Email Address',
      '#attributes'    => array('placeholder' => t('Email Address')),
      '#parents' => array('notification_count', $uniqid, 'email-address'),
    ); 

    $notification_type = drupal_map_assoc(array( t('0'), t('1')));
    $elements[$uniqid]['third-container']['notification-type'] = array(
      '#type'         => 'select',
      '#title'        => 'Notification Method',
      '#options'      => array('' => 'Select Notification Method') + $notification_type,
      '#parents' => array('notification_count', $uniqid, 'notification-type'),
    );

    $elements[$uniqid]['third-container']['notification-subject'] = array(
      '#type'          => 'textfield',
      '#title'         => 'Notification Subject',
      '#attributes'    => array('placeholder' => 'Subject'),
      '#disabled'      => TRUE,
      '#parents' => array('notification_count', $uniqid, 'notification-subject'),
    );
     
    // Third container end 

    $elements[$uniqid]['notification-message'] = array(
      '#type' => 'textarea',
      '#title'         => 'Notification Message',
      '#attributes'    => array('placeholder' => 'Type Notification Message'),
      '#prefix'        => '<div class="row margin-0 margin-bottom-25"><div class="col-md-12">',
      '#suffix'        => '</div></div>',
      '#parents' => array('notification_count', $uniqid, 'notification-message'),

    ); 
  }

  // Fourth Container Start.
  $elements['notification-actions'] = array(
    '#type'       => 'actions',
    '#prefix'     => '<div class="col-md-12">',
    '#suffix'     => '</div>',
    '#attributes' => array('class' => array('')),
  );

  // Add Notification Button
  $elements['notification-actions']['notification_new_row'] = array(
    '#type'       => 'submit',
    '#value'      => t('Add Notification'),
    '#name'       => 'notification_new_row',
    '#attributes' => array('class'=> array('contact-new-row-button')),
    '#submit'     => array('key_date_new_row_callback_submit'),
    '#ajax'       => array(
      'callback'  => 'key_date_new_row_callback',
      'wrapper'   => 'main-outer-container-div',
      'method'    => 'replace',
      'effect'    => 'fade',
      'progress'  => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix'     => '<div class="row padding-10"><div class="col-md-12">',
    '#suffix'     => '</div></div>',
  );

 /* $elements['notification-main-container']['notification-actions']['add-notification'] = array(
    '#type'       => 'submit',
    '#value'      => t('Add Notification'),
  );*/

  // Add Notification & Save Template
  $elements['notification-actions']['notification-and-template'] = array(
    '#type'       => 'submit',
    '#value'      => t('Add Notification & Save Template'),
  );

  //Cancel
  $elements['notification-actions']['reset'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Cancel'), '#' , array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  );
  // Fourth Container End.

  
  return $elements;
}
// Notification Contanier Process End

// Outer Contanier Theme Start
function theme_outer_container_theme($variables) {
  // dpm($variables, '$variables');
  $elements   = $variables['element'];
  $storage    = $elements['storage'];

  $output     = '';

  foreach ($storage as $uniqid) {
    $output .= '<div class="outer">';
    $output .= drupal_render($elements[$uniqid]['key-date-name']);
    $output .= drupal_render($elements[$uniqid]['conclusion-due-date']);
    $output .= drupal_render($elements[$uniqid]['date-status-lights']);
    $output .= '</div>';
  }
  $output   .= drupal_render($elements['datekey_new_row']);

  return $output;
}
// Outer Contanier Theme End

// Notification Theme Start
function theme_notification_container_theme($variables) {
  //dpm($variables, '$variables');
  $elements   = $variables['element'];
  $storage    = $elements['storage'];

  $output     = '';

  foreach ($storage as $uniqid) {
    $output .= '<div class="outer">';
    $output .= drupal_render($elements[$uniqid]['who-to-notify']);
    $output .= '</div>';
  }
  $output   .= drupal_render($elements['first-container']['who-to-notify']['datekey_new_row']);
 // dpm($output);
  return $output;
}
// Notification Theme End

// Key Date Submit Callback Function Start
function key_date_new_row_callback_submit($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'datekey_new_row') {
    $uniqid = uniqid();
    $form_state['date_count'][] = $uniqid;
  }

  if ($form_state['triggering_element']['#name'] == 'notification_new_row') {
    $uniqid = uniqid();
    $form_state['date_count'][] = $uniqid;
  }
  

  $form_state['rebuild'] = TRUE;
}
// Key Date Callback Function End

// Key Date New Row Callback Start
function key_date_new_row_callback($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'datekey_new_row') {
   return $form['key-dates']['key-main-container-key'];
  }

  if ($form_state['triggering_element']['#name'] == 'notification_new_row') {
   return $form['notification']['notification-main-container'];
  }
}
// Key Date New Row Callback End

function contract_pricingkey_form_submit($form,&$form_state) {
  dpm($form_state);
}