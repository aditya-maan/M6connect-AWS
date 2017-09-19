<?php
/**
 * Start work for m6connect contract
 * generating m6connect contract form, my request data table to show all records.
 * it also contains the chat feature.  
 */

function contract_thread() {
  $elements = array();

  $elements['prgram-scm-menu-items'] = array(
        '#markup' => m6connect_contract_list_menu(),
        '#prefix' => '<div class="clearfix csemanager-sub-menu-new margin-top-10 margin-bottom-45 scm-product-submenu-sp">',
        '#suffix' => '</div>',  
    );

  // Contact Thread Form.
  $contact_thread_form = drupal_get_form('contact_thread_form');
  $elements['contact-thread-form'] = array(
    '#type'       => 'markup',
    '#markup'     => drupal_render($contact_thread_form),
  );

  return $elements;
}

function contact_thread_form($form, &$form_state) {
  if (!isset($form_state['contact_count'])) {
    $form_state['contact_count'][] = uniqid();
  }

  foreach ($form_state['contact_count'] as $uniqid) {
    if (!isset($form_state['phone_number_count__' . $uniqid])) {
      $form_state['phone_number_count__' . $uniqid][] = uniqid();
    }

    if (!isset($form_state['email_address_count__' . $uniqid])) {
      $form_state['email_address_count__' . $uniqid][] = uniqid();
    }
  }

  // check Primary Contact yes/no
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#parents'][2] == 'contact_type' && !empty($form_state['triggering_element']['#value'])) {
    $uniqid_ct        = $form_state['triggering_element']['#parents'][1];
    $contact_type_val = $form_state['triggering_element']['#value'];
    $data             = _check_primary_contact($contact_type_val);
    $form_state['contact_type_option'][$uniqid_ct] = $data; 
  }
  // check Primary Contact yes/no end

  $form['form-label-title'] = array(
    '#type'       => 'markup',
    '#markup'     => '<h4>' . t('Add Contact(s)') . '</h4>',
    '#prefix'     => '<div class="contract-thread-form-head">',
    '#suffix'     => '</div>',
  );

  $form['outer-container'] = array(
    '#type'       => 'container',
    '#process'    => array('form_outer_container_process'),
    '#prefix'     => '<div id="main-outer-container-div" class="no-bg well well-large contract-thread">',
    '#suffix'     => '</div>',
    '#theme'      => 'outer_container_theme',
  );

  // Form Actions.
  // Submit Button
  $form['actions']['submit'] = array(
    '#type'       => 'submit',
    '#value'      => t('Save and Continue'),
  );

  // Back Button.
  $form['actions']['back'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Back'), 'contract-manager/initiation/new', array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  );
  
  // Cancel Button.
  $form['actions']['reset'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Cancel'), '#' , array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  );
 
  return $form;
}

function theme_outer_container_theme($variables) {
  // dpm($variables, '$variables');
  $storage    = $variables['element']['storage'];
  $elements   = $variables['element']['main-container'];

  $output     = '';
  foreach ($storage as $uniqid) {
    $output .= drupal_render($elements[$uniqid]['first-container']);
    $output .= drupal_render($elements[$uniqid]['second-container']);
    $output .= drupal_render($elements[$uniqid]['third-container']);
    $output .= drupal_render($elements[$uniqid]['notes']);
  }

  $output   .= drupal_render($elements['contact_add_new_row']);

  return $output;
}

function form_outer_container_process($elements, &$form_state) {
  $elements['#storage'] = $form_state['contact_count'];

  foreach ($form_state['contact_count'] as $uniqid) {
    $elements['main-container'][$uniqid] = array(
      '#type'           => 'container',
      '#attributes'     => array('class' => array('clearfix')),
    );

    $elements['main-container'][$uniqid]['first-container'] = array(
      '#type' => 'container',
      '#prefix'        => '<div class="col-md-4">',
      '#suffix'        => '</div>',
      '#attributes' => array('class' => array('contract-thread-fc')),
    );

    $elements['main-container'][$uniqid]['first-container']['first-name'] = array(
      '#type'          => 'textfield',
      '#title'         => 'First Name',
      '#attributes'    => array('placeholder' => 'First Name'),
      '#parents'       => array('contact', $uniqid, 'first_name'),
      '#required' => TRUE,
    );

    $elements['main-container'][$uniqid]['first-container']['contact-role'] = array(
      '#type'          => 'textfield',
      '#title'         => 'Contact Role',
      '#attributes'    => array('placeholder' => 'Contact Role'),
      '#parents'       => array('contact', $uniqid, 'contact_role'),
      '#required' => TRUE,
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

    $elements['main-container'][$uniqid]['first-container']['phone-number-container'] = array(
      '#type'     => 'container',
      '#prefix'   => '<div id="phone-number-container-div-' . $uniqid . '">',
      '#suffix'   => '</div>',
    );

    foreach ($form_state['phone_number_count__' . $uniqid] as $uniqid_phone) {
      $elements['main-container'][$uniqid]['first-container']['phone-number-container']['phone'][$uniqid_phone] = array(
        '#type'           => 'textfield',
        '#title'          => 'Phone #',
        '#attributes'     => array( 'class'=> array('form-control','workflow-auto', 'international_phone-number'),'placeholder'=>'Phone Number', 'uni_id' => $uniqId ),
        '#parents'        => array('contact', $uniqid, 'phone_number', $uniqid_phone),
        '#required'       => TRUE,
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

      $elements['main-container'][$uniqid]['second-container']['phone_code'] = array(
        '#type'           => 'hidden',  
        '#default_value'  => '', 
        '#attributes'     => array('class' => array('edit-alert-'.$uniqId.'-phone-code')),
        '#parents'        => array( 'alert',$uniqId,'phone_code' ), 
      );
    }

    $elements['main-container'][$uniqid]['first-container']['phone-number-container']['add_new_markup'] = array(
      '#markup' => '<div class="box-actions text-left"><a href="javascript:void(0);" title="Add Phone Number" onClick="jQuery(\'.phone-new-row-button-' . $uniqid . '\').trigger(\'mousedown\'); return false;"><i class="glyphicon glyphicon-plus"></i> Add New</a></div>'
    );


    $elements['main-container'][$uniqid]['first-container']['phone-number-container']['phone_add_new_row'] = array(
      '#type'                       => 'submit',
      '#value'                      => 'Add New',
      '#name'                       => 'phone_add_new_row__' . $uniqid,
      '#attributes'                 => array('class' => array('phone-new-row-button-' . $uniqid), 'title' => 'Add New Phone'),
      "#limit_validation_errors"    => array(),
      '#submit'                     => array('contract_thread_add_new_row_submit'),
      '#ajax'                       => array(
        'callback' => 'contract_thread_add_new_row_callback',
        'wrapper'  => 'phone-number-container-div-' . $uniqid,
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
      '#prefix' => '<div class="clearfix" style="display:none;">',
      '#suffix' => '</div>',
    );
    // Phone Number Field Ends.

    // Email Field Starts.
    $elements['main-container'][$uniqid]['first-container']['email-address-container'] = array(
      '#type'   => 'container',
      '#prefix' => '<div id="email-address-container-div-' . $uniqid . '">',
      '#suffix' => '</div>',
    );
    
    foreach ($form_state['email_address_count__' . $uniqid] as $uniqid_email) {
      $elements['main-container'][$uniqid]['first-container']['email-address-container']['email'][$uniqid_email] = array(
        '#type'          => 'textfield',
        '#title'         => 'Email Address',
        '#attributes'    => array('placeholder' => t('Email Address')),
        '#parents'       => array('contact', $uniqid, 'email', $uniqid_email),
        '#required'      => TRUE,
      ); 
    }

    $elements['main-container'][$uniqid]['first-container']['email-address-container']['add_new_markup'] = array(
      '#markup' => '<div class="box-actions text-left"><a href="javascript:void(0);" title="Add Phone Number" onClick="jQuery(\'.email-new-row-button-' . $uniqid . '\').trigger(\'mousedown\'); return false;"><i class="glyphicon glyphicon-plus"></i> Add New</a></div>'
    );
    $elements['main-container'][$uniqid]['first-container']['email-address-container']['email_add_new_row'] = array(
      '#type'  => 'submit',
      '#value' => 'Add New',
      '#name'  => 'email_add_new_row__' . $uniqid,
      '#attributes'=> array('class'=> array('email-new-row-button-' . $uniqid), 'title' => t('Add New Email Address')),
      "#limit_validation_errors" => array(),
      '#submit'=> array('contract_thread_add_new_row_submit'),
      '#ajax' => array(
        'callback' => 'contract_thread_add_new_row_callback',
        'wrapper'  => 'email-address-container-div-'.$uniqid,
        'method'   => 'replace',
        'effect'   => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
      '#prefix'    => '<div class="clearfix" style="display:none;">',
      '#suffix'    => '</div>',
    );

    // Email Field Ends.
    // First Container Ends.

    // Second Container.
    $elements['main-container'][$uniqid]['second-container'] = array(
      '#type'         => 'container',
      '#prefix'       => '<div class="col-md-4 contract-thrd-sp">',
      '#suffix'       => '</div>',
      '#attributes'   => array('class' => array('contract-thread-fc')),
    );

    $elements['main-container'][$uniqid]['second-container']['contact-last-name'] = array(
      '#type'         => 'textfield',
      '#title'        => 'Contact Last Name',
      '#attributes'   => array('placeholder' => 'Last Name'),
      '#parents'      => array('contact', $uniqid, 'contact_last_name'),
      '#required'     => TRUE,
    );

    $elements['main-container'][$uniqid]['second-container']['contact-title'] = array(
      '#type'         => 'textfield',
      '#title'        => 'Contact Title',
      '#attributes'   => array('placeholder' => 'Contact Title'),
      '#parents'      => array('contact', $uniqid, 'contact_title'),
    );

    $option = drupal_map_assoc(array( t('Cell'), t('Office'), t('other')));
    $elements['main-container'][$uniqid]['second-container']['phone-type'] = array(
      '#type'         => 'select',
      '#title'        => 'Phone # Type',
      '#options'      => array('' => 'Select Phone # Type') + $option,
      '#parents'      => array('contact', $uniqid, 'phone_type'),
    );

  
    $elements['main-container'][$uniqid]['second-container']['email-address-type'] = array(
      '#type'         => 'select',
      '#title'        => 'Email Address Type',
      '#options'      => array('' => 'Select Email Address Type') + $option,
      '#parents'      => array('contact', $uniqid, 'email_address_type'),
    );
    // Second container end    

    // Third Container Starts.
    $options          = drupal_map_assoc(array(t('Internal Contacts'), t('Monitoring')));
    $elements['main-container'][$uniqid]['third-container'] = array(
      '#type'         => 'container',
      '#prefix'       => '<div class="col-md-4">',
      '#suffix'       => '</div>',
      '#attributes'   => array('class' => array('contract-thread-fc')),
    );

    $contact_type_option = drupal_map_assoc(array( t('Internal Contacts'), t('Monitoring'), t('Maintenance'), t('Support'), t('Financial'), t('General')));
    $elements['main-container'][$uniqid]['third-container']['contact-type'] = array(
      '#type'         => 'select',
      '#title'        => 'Contact Type',
      '#options'      => array('' => 'Select contact Type') + $contact_type_option,
      '#parents'      => array('contact', $uniqid, 'contact_type'),
      '#ajax'         => array(
        'wrapper'     => 'primary-contact-radios-' . $uniqid,
        'callback'    => 'contract_thread_add_new_row_callback',
      ),
      '#required' => TRUE,
    );


    $active = array(0 => t('Yes'), 1 => t('No'));

    $elements['main-container'][$uniqid]['third-container']['primary-contact'] = array(
      '#type'     => 'radios',
      '#title'    => 'Primary Contact',
      '#options'  => $active,
      '#parents'  => array('contact', $uniqid, 'primary_contact'),
      '#prefix'   => '<div id="primary-contact-radios-' . $uniqid . '" class="contract-thrd">',
      '#suffix'   => '</div>',
      '#required' => TRUE,
    );

    if (isset($form_state['contact_type_option'][$uniqid])) {
      $elements['main-container'][$uniqid]['third-container']['primary-contact']['#disabled'] = $form_state['contact_type_option'][$uniqid];
      unset($form_state['contact_type_option'][$uniqid]);
    }
    else {
      $elements['main-container'][$uniqid]['third-container']['primary-contact']['#disabled'] = FALSE;
    }

    $elements['main-container'][$uniqid]['notes'] = array(
      '#type' => 'textarea',
      '#title'         => 'Notes',
      '#attributes'    => array('placeholder' => 'Type Notes'),
      '#prefix'        => '<div class="col-md-12 margin-bottom-25 contract-thrd-sp-form">',
      '#suffix'        => '</div>',
      '#parents'       => array('contact', $uniqid, 'notes'),
    );
  }

  // Add new Form.
  $elements['contact_add_new_row'] = array(
    '#type'       => 'submit',
    '#value'      => t('Add Contact'),
    '#name'       => 'contact_add_new_row',
    '#attributes' => array('class'=> array('contact-new-row-button')),
    '#submit'     => array('contract_thread_add_new_row_submit'),
    '#ajax'       => array(
      'callback'  => 'contract_thread_add_new_row_callback',
      'wrapper'   => 'main-outer-container-div',
      'method'    => 'replace',
      'effect'    => 'fade',
      'progress'  => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix'     => '<div class="clearfix margin-top-10 padding-10">',
    '#suffix'     => '</div>',
    '#limit_validation_errors' => array(),
  );

  return $elements;
}



function contract_thread_add_new_row_submit($form, &$form_state) {
  if (strpos($form_state['triggering_element']['#name'], 'phone_add_new_row') === 0) {
    $uniqid_exp = explode('__', $form_state['triggering_element']['#name']);
    $uniqid     = $uniqid_exp[1];
    $form_state['phone_number_count__' . $uniqid][] = uniqid();
  }

  if (strpos($form_state['triggering_element']['#name'], 'email_add_new_row') === 0) {
    $uniqid_exp = explode('__', $form_state['triggering_element']['#name']);
    $uniqid     = $uniqid_exp[1];
    $form_state['email_address_count__' . $uniqid][] = uniqid();
  }

  if ($form_state['triggering_element']['#name'] == 'contact_add_new_row') {
    $uniqid                         = uniqid();
    $form_state['contact_count'][]  = $uniqid;

    if (!isset($form_state['phone_number_count__' . $uniqid])) {
      $form_state['phone_number_count__' . $uniqid][] = uniqid();
    }

    if (!isset($form_state['email_address_count__' . $uniqid])) {
      $form_state['email_address_count__' . $uniqid][] = uniqid();
    }
  }

  $form_state['rebuild'] = TRUE;
}

function contract_thread_add_new_row_callback($form, &$form_state) {
  if (strpos($form_state['triggering_element']['#name'], 'phone_add_new_row') === 0) {
    $uniqid_exp = explode('__', $form_state['triggering_element']['#name']);
    $uniqid = $uniqid_exp[1];
    return $form['outer-container']['main-container'][$uniqid]['first-container']['phone-number-container'];
  }

  if (strpos($form_state['triggering_element']['#name'], 'email_add_new_row') === 0) {
    $uniqid_exp = explode('__', $form_state['triggering_element']['#name']);
    $uniqid = $uniqid_exp[1];
    return $form['outer-container']['main-container'][$uniqid]['first-container']['email-address-container'];
  }

  if ($form_state['triggering_element']['#parents'][2] == 'contact_type') {
    $uniqid = $form_state['triggering_element']['#parents'][1];
    return $form['outer-container']['main-container'][$uniqid]['third-container']['primary-contact'];
  }    

  if ($form_state['triggering_element']['#name'] == 'contact_add_new_row') {
   return $form['outer-container'];
  }
}

function contact_thread_form_submit($form, &$form_state) {
  $form_values    = $form_state['values']['contact'];

  foreach ($form_values as $key => $value) {
    $first_name   = $value['first_name'];
    $contact_role = $value['contact_role'];
    $phone_numer  = array();

    // Getting all phone numbers.
    if (!empty($value['phone_number'])) {
      foreach ($value['phone_number'] as $phn_value) {
        if (!empty($phn_value)) {
          $phone_number[] = array('value' => $phn_value);
        }
      }
    }

    // Getting all emails.
    if (!empty($value['email'])) {
      foreach ($value['email'] as $email_value) {
        if (!empty($email_value)) {
          $email[] = array('value' => $email_value);
        }
      }
    }

    // Contract threads save
    $contact_last_name  = $value['contact_last_name'];
    $contact_title      = $value['contact_title'];
    $phone_type         = $value['phone_type'];
    $email_address_type = $value['email_address_type'];
    $contact_type       = $value['contact_type'];
    $primary_contact    = $value['primary_contact'];
    $notes              = $value['notes'];
    $getTitle           = $first_name . ' ' . $contact_last_name;

    $node = _node_creation_call('contract_thread', $getTitle);
    $node->field_contact_first_name[LANGUAGE_NONE][0]['value']  = $first_name;
    $node->field_contact_last_name[LANGUAGE_NONE][0]['value']   = $contact_last_name;
    $node->field_contact_type[LANGUAGE_NONE][0]['value']        = $contact_type;
    $node->field_contact_role[LANGUAGE_NONE][0]['value']        = $contact_role;
    $node->field_contact_title[LANGUAGE_NONE][0]['value']       = $contact_title;
    $node->field_primary_contact[LANGUAGE_NONE][0]['value']     = $primary_contact;
    $node->field_phone_[LANGUAGE_NONE]                          = $phone_number;
    $node->field_phone_type[LANGUAGE_NONE][0]['value']          = $phone_type;
    $node->field_email_address[LANGUAGE_NONE]                   = $email;
    $node->field_email_address_type[LANGUAGE_NONE][0]['value']  = $email_address_type;
    $node->body[LANGUAGE_NONE][0]['value']                      = $notes;
  
    node_save($node);
    drupal_set_message(t('Contact %title saved successfully.', array('%title' => $getTitle)), 'status', FALSE);
  }
}

function _check_primary_contact($contact_type_val) {
  global $company;
  $output = FALSE;
  $query  = db_select('field_data_field_contact_type', 'fct');
  $query->leftjoin('field_data_field_primary_contact', 'fpc', 'fpc.entity_id = fct.entity_id');
  $query->leftjoin('og_membership', 'og', 'og.etid = fct.entity_id');
  $query->condition('fct.bundle','contract_thread');
  $query->condition('og.gid', $company->nid);
  $query->condition('fpc.field_primary_contact_value',1);
  $query->condition('fct.field_contact_type_value',$contact_type_val);
  $query->fields('fpc',array('field_primary_contact_value'));
  $result = $query->execute()->rowCount();
  if(!empty($result) && $result > 0){
    $output = TRUE;
  }
  return $output;
}

function contact_thread_form_validate($form, &$form_state) {
  foreach ($form_state['values']['contact'] as $mainkey => $main_values) {
    foreach ($main_values['email'] as $key => $mail) {
      if (!valid_email_address($mail)) {
        form_set_error('contact]['.$mainkey.'][email]['.$key, t('The email address appears to be invalid.'));
      }
    } 
  }
}