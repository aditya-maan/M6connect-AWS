<?php

/**
 * Menu callback for vendor/settings.
 */
function vendor_m6reach_settings() {
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/m6connect_vendor.js');
  
  $elements = array();
  global $user;
  // $elements['top_menu_links'] = array(
  //   '#markup' => vendor_manager_menu_links(),
  // );
  // $elements['settings-links'] = array(
  //   '#markup' => _get_vendor_settings_links(),
  //   '#prefix' => '<div class="clearfix">',
  //   '#suffix' => '</div>',
  // );
  // Ratings Types.
  $elements['ratings-types-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Rating Types'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('collapsible', 'bid-package-fieldset', 'fieldsetbigtitle')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['ratings-types-fieldset']['ratings-types-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('m6reach_ratings_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );

  // Attributes Types.
  $elements['attributes-types-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Attributes Types'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed', 'fieldsetbigtitle')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['attributes-types-fieldset']['attributes-types-settings-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('m6reach_attributes_settings_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );

  // Showing vendor status fieldset to only M6 Admins.
  if (in_array('administrator', $user->roles)) {
    $elements['vendor-status-fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Vendor Status'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array('class' => array('collapsible', 'collapsed', 'fieldsetbigtitle')),
      '#attached' => array(
        'library' => array(
          array('system', 'drupal.collapse'),
        ),
      ),
      '#prefix' => '<div class="clearfix margin-bottom-10">',
      '#suffix' => '</div>',
    );
    $elements['vendor-status-fieldset']['vendor-status-settings-form'] = array(
      '#type' => 'markup',
      '#markup' => render(drupal_get_form('m6reach_vendor_status_settings_form')),
      '#prefix' => '<div class="clearfix">',
      '#suffix' => '</div>',
    );
  }

  // Canned Messages.
  $elements['canned-msg-fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Canned Messages/Responses'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attributes' => array('class' => array('collapsible', 'collapsed', 'fieldsetbigtitle')),
    '#attached' => array(
      'library' => array(
        array('system', 'drupal.collapse'),
      ),
    ),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $elements['canned-msg-fieldset']['canned-msg-form'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('canned_msg_settings_form')),
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );

  // Helper div to store deleting element info.
  $elements['remove-setting-div'] = array(
    '#markup' => '',
    '#prefix' => '<div id="m6reach-service-remove">',
    '#suffix' => '</div><div class="remove-data-details" style="display:none"><span class="remove-data-details-service"></span><span class="remove-data-details-name"></span></div>',
  );
  return $elements;
}

/**
 * Function to return m6reach settings form.
 */
function m6reach_ratings_settings_form($form, &$form_state) {
  $ratings_types = _get_m6reach_ratings_types('ratings');

  $ratings_data = '<div class="ratings-data-outer clearfix">';
  foreach ($ratings_types as $ratings_type) {
    $ratings_data .= '<div class="rating-data-item display-inline-block">' . $ratings_type . ' <span><i class="fa fa-times remove-m6reach-options rating" aria-hidden="true" data="' . $ratings_type . '"></i></span></div>';
  }
  $ratings_data .= '</div>';
  
  $form['ratings-types-data'] = array(
    '#type' => 'markup',
    '#markup' => $ratings_data,
    '#prefix' => '<div id="rating-type-data-div">',
    '#suffix' => '</div>',
  );
  $form['rating_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new rating type'),
    '#attributes' => array('placeholder' => t('Please enter new Rating type here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'm6reach_ratings_settings_form_submit_callback',
      'wrapper' => 'm6reach-ratings-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * Ajax submit callback for m6reach_ratings_settings_form.
 */
function m6reach_ratings_settings_form_submit_callback($form, &$form_state) {
  $error = FALSE;
  if (empty(trim($form_state['values']['rating_type_new']))) {
    $error = TRUE;
    form_set_error('rating_type_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }

  $rating_type_new = array();

  $form_state['values']['rating_type_new'] = trim($form_state['values']['rating_type_new']);

  $new_rating = strtolower(str_replace(' ', '_', $form_state['values']['rating_type_new']));
  $rating_type_new[$new_rating] = $form_state['values']['rating_type_new'];

  $save_new_rating = _save_new_rating_attribute('ratings', $rating_type_new);

  $ratings_data = '<div id="rating-type-data-div"><div class="ratings-data-outer clearfix">';
  foreach ($save_new_rating as $rating_type) {
    $ratings_data .= '<div class="rating-data-item display-inline-block">' . $rating_type . ' <span><i class="fa fa-times remove-m6reach-options rating" aria-hidden="true" data="' . $rating_type . '"></i></span></div>';
  }
  $ratings_data .= '</div></div>';

  $commands = array();
  $commands[] = ajax_command_invoke('#edit-rating-type-new', 'val', array(''));
  $commands[] = ajax_command_replace('#rating-type-data-div', $ratings_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Function to return m6reach attributes form.
 */
function m6reach_attributes_settings_form($form, &$form_state) {
  $ratings_types = _get_m6reach_ratings_types('attributes');

  $ratings_data = '<div class="ratings-data-outer clearfix">';
  if (!empty($ratings_types)) {
    foreach ($ratings_types as $ratings_type) {
      $ratings_data .= '<div class="rating-data-item display-inline-block">' . $ratings_type . ' <span><i class="fa fa-times remove-m6reach-options attributes" aria-hidden="true" data="' . $ratings_type . '"></i></span></div>';
    }
  }
  else {
    $ratings_data .= '<p>' . t('No attributes added yet!') .' </p>';
  }
  $ratings_data .= '</div>';
  
  $form['attributes-types-data'] = array(
    '#type' => 'markup',
    '#markup' => $ratings_data,
    '#prefix' => '<div id="attribute-type-data-div">',
    '#suffix' => '</div>',
  );
  $form['attribute_type_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new attribute type'),
    '#attributes' => array('placeholder' => t('Please enter new Attribute type here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'm6reach_attributes_settings_form_submit_callback',
      'wrapper' => 'm6reach-attributes-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * Ajax submit callback for m6reach_attributes_settings_form
 */
function m6reach_attributes_settings_form_submit_callback($form, &$form_state) {
  $error = FALSE;
  if (empty(trim($form_state['values']['attribute_type_new']))) {
    $error = TRUE;
    form_set_error('attribute_type_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }

  $attribute_type_new = array();

  $form_state['values']['attribute_type_new'] = trim($form_state['values']['attribute_type_new']);

  $new_rating = strtolower(str_replace(' ', '_', $form_state['values']['attribute_type_new']));
  $attribute_type_new[$new_rating] = $form_state['values']['attribute_type_new'];

  $save_new_rating = _save_new_rating_attribute('attributes', $attribute_type_new);

  $ratings_data = '<div id="attribute-type-data-div"><div class="ratings-data-outer clearfix">';
  foreach ($save_new_rating as $rating_type) {
    $ratings_data .= '<div class="rating-data-item display-inline-block">' . $rating_type . ' <span><i class="fa fa-times remove-m6reach-options attributes" aria-hidden="true" data="' . $rating_type . '"></i></span></div>';
  }
  $ratings_data .= '</div></div>';

  $commands = array();
  $commands[] = ajax_command_invoke('#edit-attribute-type-new', 'val', array(''));
  $commands[] = ajax_command_replace('#attribute-type-data-div', $ratings_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Function to return m6reach settings form.
 */
function m6reach_vendor_status_settings_form($form, &$form_state) {
  $vendor_status_arr = variable_get('vendor_status', array());

  $vendor_status_data = '<div class="ratings-data-outer clearfix">';
  if (!empty($vendor_status_arr)) {
    foreach ($vendor_status_arr as $vendor_status_ele) {
      $vendor_status_data .= '<div class="rating-data-item display-inline-block">' . $vendor_status_ele . ' <span><i class="fa fa-times remove-m6reach-options vendor" aria-hidden="true" data="' . $vendor_status_ele . '"></i></span></div>';
    }
  }
  else {
    $vendor_status_data .= '<p>' . t('No vendor status yet!') . '</p>';
  }
  $vendor_status_data .= '</div>';
  
  $form['vendor-status-data'] = array(
    '#type' => 'markup',
    '#markup' => $vendor_status_data,
    '#prefix' => '<div id="vendor-status-data-div">',
    '#suffix' => '</div>',
  );
  $form['vendor_status_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new vendor status'),
    '#attributes' => array('placeholder' => t('Please enter new Vendor Status here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'm6reach_vendor_status_settings_form_submit_callback',
      'wrapper' => 'm6reach-vendor-status-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * Function to return canned message form.
 */
function canned_msg_settings_form($form, &$form_state) {
  $canned_msg = _get_m6reach_canned_msg();

  $canned_msg_data = '<div class="ratings-data-outer clearfix">';
  if (!empty($canned_msg)) {
    foreach ($canned_msg as $msg) {
      $canned_msg_data .= '<div class="rating-data-item display-inline-block">' . $msg . ' <span><i class="fa fa-times remove-m6reach-options canned" aria-hidden="true" data="' . $msg . '"></i></span></div>';
    }
  }
  else {
    $canned_msg_data .= '<p>' . t('No canned messages added yet!') . '</p>';
  }
  $canned_msg_data .= '</div>';
  
  $form['canned-msg-data'] = array(
    '#type' => 'markup',
    '#markup' => $canned_msg_data,
    '#prefix' => '<div id="canned-msgs-data-div">',
    '#suffix' => '</div>',
  );
  $form['canned_msg_new'] = array(
    '#type' => 'textfield',
    '#title' => t('Add new canned message'),
    '#attributes' => array('placeholder' => t('Please enter new message here.')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'canned_msg_settings_form_submit_callback',
      'wrapper' => 'canned-msg-settings-form',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  return $form;
}

/**
 * Ajax Submit handler for canned_msg_settings_form
 */
function canned_msg_settings_form_submit_callback($form, &$form_state) {
  $error = FALSE;
  if (empty(trim($form_state['values']['canned_msg_new']))) {
    $error = TRUE;
    form_set_error('canned_msg_new', t('Message can not be blank!'));
  }
  if ($error) {
    return $form;
  }

  global $company, $user;

  $old_messages = _get_m6reach_canned_msg();
  $new_messages  = array(trim($form_state['values']['canned_msg_new']));
  if (!empty($old_messages)) {
    $new_messages = array_values(array_unique(array_merge($old_messages, $new_messages)));
  }

  if (!empty($new_messages)) {
    // Inserting record, if new messages are available.
    // If $old_messages is empty, then also there may be an entry in the table
    // for the current company holding other values.
    // So, first checking that.
    $query = db_select('m6reach_ratings_attributes_type', 'c')
      ->fields('c')
      ->condition('nid', $company->nid)
      ->execute()
      ->rowCount();

    if ($query > 0) {
      db_update('m6reach_ratings_attributes_type')
        ->fields(array(
          'canned_msg' => serialize($new_messages),
          'updated' => REQUEST_TIME,
        ))
        ->condition('nid', $company->nid)
        ->execute();
    }
    else {
      db_insert('m6reach_ratings_attributes_type')
        ->fields(array(
          'uid' => $user->uid,
          'canned_msg' => serialize($new_messages),
          'updated' => REQUEST_TIME,
        ))
        ->execute();
    }
  }

  $canned_msg_data = '<div id="canned-msgs-data-div"><div class="ratings-data-outer clearfix">';
  foreach ($new_messages as $msg) {
    $canned_msg_data .= '<div class="rating-data-item display-inline-block">' . $msg . ' <span><i class="fa fa-times remove-m6reach-options canned" aria-hidden="true" data="' . $msg . '"></i></span></div>';
  }
  $canned_msg_data .= '</div></div>';

  $commands = array();
  $commands[] = ajax_command_invoke('#edit-canned-msg-new', 'val', array(''));
  $commands[] = ajax_command_replace('#canned-msgs-data-div', $canned_msg_data);
  return array('#type' => 'ajax', '#commands' => $commands);

}

/**
 * Ajax submit callback for m6reach_ratings_settings_form.
 */
function m6reach_vendor_status_settings_form_submit_callback($form, &$form_state) {
  $error = FALSE;
  if (empty(trim($form_state['values']['vendor_status_new']))) {
    $error = TRUE;
    form_set_error('vendor_status_new', t('Name can not be blank!'));
  }
  if ($error) {
    return $form;
  }

  $vendor_status_arr = variable_get('vendor_status', array());

  $form_state['values']['vendor_status_new'] = trim($form_state['values']['vendor_status_new']);

  $vendor_new = strtolower(str_replace(' ', '_', $form_state['values']['vendor_status_new']));
  $vendor_status_arr[$vendor_new] = $form_state['values']['vendor_status_new'];

  variable_set('vendor_status', $vendor_status_arr);

  $vendor_status_data = '<div id="vendor-status-data-div"><div class="ratings-data-outer clearfix">';
  foreach ($vendor_status_arr as $rating_type) {
    $vendor_status_data .= '<div class="rating-data-item display-inline-block">' . $rating_type . ' <span><i class="fa fa-times remove-m6reach-options vendor" aria-hidden="true" data="' . $rating_type . '"></i></span></div>';
  }
  $vendor_status_data .= '</div></div>';

  $commands = array();
  $commands[] = ajax_command_invoke('#edit-vendor-status-new', 'val', array(''));
  $commands[] = ajax_command_replace('#vendor-status-data-div', $vendor_status_data, array());
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Function to remove m6reach options by ajax.
 */
function remove_m6reach_options_ajax() {
  if (isset($_POST['setting']) && isset($_POST['name'])) {
    $name = strtolower(str_replace(' ', '_', $_POST['name']));
    $deleted = FALSE;

    if ($_POST['setting'] == 'rating') {
      $deleted = _delete_rating_attribute('ratings', $name);
    }
    elseif ($_POST['setting'] == 'attributes') {
      $deleted = _delete_rating_attribute('attributes', $name);
    }
    elseif ($_POST['setting'] == 'vendor') {
      $data = variable_get('vendor_status', array());
      if (!empty($data)) {
        if (isset($data[$name])) {
          unset($data[$name]);
          variable_set('vendor_status', $data);
          $deleted = TRUE;
        }
      }
    }
    elseif ($_POST['setting'] == 'canned') {
      // If canned message is to be deleted.
      $deleted = _delete_canned_msg($_POST['name']);
    }
    if ($deleted) {
      print 'Success';
      exit();
    }
  }

  print 'Failure';
  exit();
}
