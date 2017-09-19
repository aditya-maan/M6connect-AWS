<?php

/**
 * @file Include file for vendor m6reach.
 * All helper functions in .module file.
 */

/**
 * Menu callback for vendor/m6reach.
 */
function vendor_m6reach_content($type = 'm6reach') {
  // Adding jQuery UI JS.
  drupal_add_js('https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js', 'external');

  // Including custom js.
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/m6connect_vendor.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/messaging_socket.js');

  $theme_path = drupal_get_path('theme', 'm6connect');
  $elements = array();
  global $user, $company;
  $account = user_load($user->uid);

  // Making company and user pic divs, so as to use in JS.
  $big_comp_img_src = '<img src="/' . $theme_path . '/images/icon-120.png">';

  $user_pic =  isset($account->field_user_profile_photo[LANGUAGE_NONE]['0']['uri']) ? $account->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';
  $user_pic_markup = '<img typeof="foaf:Image" src="' . image_style_url('user_pic_40x40', $user_pic) . '">';
  $user_pic_markup_big = '<img typeof="foaf:Image" src="' . image_style_url('user_image_default', $user_pic) . '">';
  $company_logo_markup = '<img src="/' . $theme_path . '/images/icon-42.png">';

  // Adding spending and rating tab on preffered page.
  if ($type == 'preferred') {
    $elements['preferred_links'] = array(
      '#type'   => 'markup',
      '#markup' => _get_preferred_tab_links(),
    );
  }

  $elements['company_logo_markup'] = array(
    '#type'   => 'markup',
    '#markup' => $company_logo_markup,
    '#prefix' => '<div style="display:none;" id="m6-vendor-company-logo-tool">',
    '#suffix' => '</div>',
  );
  $elements['user_pic_markup'] = array(
    '#type'   => 'markup',
    '#markup' => $user_pic_markup,
    '#prefix' => '<div style="display:none;" id="vendor-current-user-img-tool">',
    '#suffix' => '</div>',
  );
  $elements['company_logo_markup_big'] = array(
    '#type'   => 'markup',
    '#markup' => $big_comp_img_src,
    '#prefix' => '<div style="display:none;" id="m6-company-logo-tool-big">',
    '#suffix' => '</div>',
  );
  $elements['user_pic_markup_big'] = array(
    '#type'   => 'markup',
    '#markup' => $user_pic_markup_big,
    '#prefix' => '<div style="display:none;" id="current-user-img-tool-big">',
    '#suffix' => '</div>',
  );

  $elements['edit-section'] = array(
    '#markup' => render(drupal_get_form('vendor_m6reach_edit_form', $type)),
    '#prefix' => '<div class = "row"><div class = "col-md-7 margin-bottom-25"><div class="vendor-m6reach-edit vendor-border clearfix" style="display:none;">',
    '#suffix' => '</div></div>',
  );

  $elements['render-form-for-messaging'] = array(
    '#markup' => '',
    '#prefix' => '<div class="col-md-5 margin-bottom-25" id="form-for-messaging-div" style="display:none;"><div class="vendor-m6form-edit vendor-border clearfix">',
    '#suffix' => '</div></div></div>',
  );

  $elements['notes-section'] = array(
    '#markup' => '<div class = "clearfix"><div id="notes-table-vendor" class="clearfix margin-bottom-10" style="display:none;"></div></div>',
  );

  $elements['table-section'] = array(
    '#markup' => _get_vendor_m6reach_table($type),
    '#prefix' => '<div class="clearfix"><div class="table-responsive"><div class="vendor-m6reach-table" id="vendor_m6reach_table">',
    '#suffix' => '</div></div></div>',
  );

  return $elements;
}

/**
 * Menu callback for vendor/preferred/spendings.
 */
function vendor_m6reach_content_spending($type = 'summary') {
  // Adding jQuery UI JS.
  drupal_add_js('https://ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/jquery-ui.min.js', 'external');

  // Including custom js.
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/m6connect_vendor.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/messaging_socket.js');

  $elements = array();

  $elements['preferred_links'] = array(
    '#type'   => 'markup',
    '#markup' => _get_preferred_tab_links(),
  );

  $elements['export_link'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Spending Report'), 'export/vendor-spending', array('attributes' => array('class' => array('form-submit', 'text-white', 'pull-right', 'toggle-vendor-spending-export-form')))),
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );

  // Export form for exporting data.
  $form = drupal_get_form('export_vendor_data_form');
  $elements['export-form'] = array(
    '#markup' => render($form),
    '#prefix' => '<div class="clearfix margin-bottom-10 padding-10"><div class="vendor-spending-edit-export-form" style="display:none;">',
    '#suffix' => '</div></div>',
  );

  // Edit form for details page.
  if ($type == 'detail') {
    $form = drupal_get_form('vendor_spending_edit_form');
    $elements['edit-section'] = array(
      '#markup' => render($form),
      '#prefix' => '<div class = "clearfix margin-bottom-10 padding-10"><div class="vendor-spending-edit" style="display:none;">',
      '#suffix' => '</div></div>',
    );
  }

  $elements['table-section'] = array(
    '#markup' => _get_vendor_preferred_spending_table($type),
    '#prefix' => '<div class="clearfix"><div class="table-responsive"><div class="vendor-preferred-spendings-table" id="vendor_preferred_spendings_table">',
    '#suffix' => '</div></div></div>',
  );
  return $elements;
}

/**
 * M6Vendor Main Form.
 */
function vendor_m6reach_edit_form($form, &$form_state, $type = 'm6reach') {
  global $user, $company;
  $default_vender_value = '';
  $is_user_vendor_manager = _is_user_vendor_manager($company, $user);

  $type_org = $type;
  $type = $type == 'preferred' || 'pending' ? 'm6reach' : $type;
  $form_state['m6reach_type'] = $type;
  if (!empty($form_state['m6reach_default_values'])) {
    $default_values = $form_state['m6reach_default_values'];
    $default_vender_value = $default_values['default_vender_value'];
  }

  $approved = 0;
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#type'] == 'select' && $form_state['triggering_element']['#name'] == 'vendor_node' && !empty($form_state['triggering_element']['#value'])) {
    $vendor_node_trigger = node_load($form_state['triggering_element']['#value']);
    $approved = $vendor_node_trigger->status;
  }

  $form['notes_dialog'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="like-dislike-processed-dialog" style="display:none;"></div>',
  );

  $form['m6reach_type'] = array(
    '#type' => 'hidden',
    '#value' => $type,
  );
  $form['m6reach_type_org'] = array(
    '#type' => 'hidden',
    '#value' => $type_org,
  );

  $cnid = !empty($default_values['cnid']) ? $default_values['cnid'] : '';
  $vnid = !empty($default_values['vnid']) ? $default_values['vnid'] : '';
  $form['cnid'] = array(
    '#type' =>'hidden',
    '#value' => $cnid,
  );
  $form['vnid'] = array(
    '#type' => 'hidden',
    '#value' => $vnid,
  );

  $form['vendor_node'] = array(
    '#type' => 'select',
    '#title' => t('Vendors'),
    '#options' => _get_vendor_names($type_org),
    '#default_value' => $default_vender_value,
    '#ajax' => array(
      'wrapper' => 'vendor-edit-form-main-container',
      'callback' => 'vendor_node_change_callback',
    ),
    '#attributes' => array('class' => array('vendor-node-select')),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
  );

  $form['company-intro'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="vendor-company-intro-outer" class="clearfix margin-bottom-45" style="display:none;">',
    '#suffix' => '</div>',
    '#markup' => '',
  );
  $form['main-container'] = array(
    '#type' => 'container',
    //'#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix vendor-m6reach-edit margin-bottom-15" id="vendor-edit-form-main-container">',
    '#suffix' => '</div>',
  );

  // $form['main-container']['company_markup'] = array(
  //   '#type' => 'markup',
  //   '#markup' => '',
  //   '#prefix' => '<div id="company-markup-m6reach" class="clearfix">',
  //   '#suffix' => '</div><div id="main-container-ratings-pre" class="clearfix">',
  // );

  $form['main-container']['ratings_pre'] = array(
    '#markup' => '<div id="main-container-ratings-pre" class="clearfix">',
  );

  $form['main-container']['vendor_ratings'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('edit-vendor-ratings')),
    '#process' => array('vendor_ratings_container_process_m6reach'),
    '#prefix' => '<div class="form-inline-m6reach clearfix"><div class="vendor-ratings-container clearfix">',
    '#suffix' => '</div></div>',
  );

  $form['main-container']['ratings_post'] = array(
    '#markup' => '</div>',
  );

  $vendor_default_value = '';
  if (!empty($default_values['vendor_node']) && is_object($default_values['vendor_node'])) {
    // If default value is available for vendor status.
    $vendor_default_value = !empty($default_values['vendor_node']->field_vendor_status[LANGUAGE_NONE][0]['value']) ? $default_values['vendor_node']->field_vendor_status[LANGUAGE_NONE][0]['value'] : '';
  }
  $vendor_status_options = variable_get('vendor_status', array('-- None --'));
  $form['main-container']['vendor_status'] = array(
    '#type' => 'select',
    '#options' => $vendor_status_options,
    '#title' => t('Preferred Vendor Status'),
    '#default_value' => $vendor_default_value,
    '#attributes' => array('class'=> array('form-control')),
    '#prefix' => '<div class="padding-10 pull-right pending-invite">',
    // '#suffix' => '</div></div>',
    '#suffix' => '</div>',
    '#access' => $is_user_vendor_manager && $approved,
  );

  // if (!$is_user_vendor_manager) {
  //   // If user is not a vendor manager, then closing a div, because the vendor
  //   // status does not render in that case.
  //   $form['close-div'] = array(
  //     '#markup' => '</div>',
  //   );
  // }

  $form['pre-actions'] = array(
    '#markup' => '<div class="m6reach-submit-button-group pull-left" id="approve-deny-actions">',
  );

  $form['approve_deny_actions'] = array(
    '#type' => 'container',
  );
  if ($approved) {
    $form['approve_deny_actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit Feedback'),
    );

    $form['approve_deny_actions']['request_feedback'] = array(
      '#type' => 'markup',
      '#markup' => l(t('Request Feedback'), 'request-feedback/' . $cnid . '/' . $vnid . '/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-onboarding-message-popup-style', 'form-submit', 'text-white')))),
      '#prefix' => '<div class="m6reach-request-feedback pull-left" id="m6reach-request-feedback">',
      '#suffix' => '</div>',
    );
    $form['approve_deny_actions']['view_feedback'] = array(
      '#type' => 'button',
      '#value' => t('View Notes'),
      '#attributes' => array('class' => array('view-feedback-m6reach')),
    );
  }

  if (!$approved) {
    $form['approve_deny_actions']['approve_preferred'] = array(
      '#type' => 'markup',
      '#markup' => l(t('Approve'), 'approve-deny-vendor/approve/' . $cnid . '/' . $vnid . '/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-onboarding-message-popup-style', 'form-submit', 'text-white')))),
      '#prefix' => '<div class="approve-vendor pull-left" id="approve_vendor_preferred">',
      '#suffix' => '</div>',
    );
    $form['approve_deny_actions']['deny_preferred'] = array(
      '#type' => 'markup',
      '#markup' => l(t('Deny'), 'approve-deny-vendor/deny/' . $cnid . '/' . $vnid . '/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-onboarding-message-popup-style', 'form-submit', 'text-white')))),
      '#prefix' => '<div class="deny-vendor pull-left" id="deny-vendor-preferred">',
      '#suffix' => '</div>',
    );
  }

  $form['approve_deny_actions']['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('cancel-button')),
  );

  $form['post-actions'] = array(
    '#markup' => '</div>',
  );

  return $form;
}

/**
 * Ajax callback for vendor_m6reach_edit_form.
 */
function vendor_node_change_callback($form, &$form_state) {
  global $user, $company;
  $commands = array();

  // Getting type and original type.
  $type = !empty($form_state['values']['m6reach_type']) ? $form_state['values']['m6reach_type'] : (!empty($form_state['m6reach_type']) ? $form_state['m6reach_type'] : 'm6reach');
  $type_org = !empty($form_state['values']['m6reach_type_org']) ? $form_state['values']['m6reach_type_org'] : 'm6reach';

  // If a trigger occured.
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#type'] == 'select' && $form_state['triggering_element']['#name'] == 'vendor_node' && !empty($form_state['triggering_element']['#value'])) {

    $form_state['m6reach_default_values'] = array();
    $vnid = $form_state['triggering_element']['#value'];
    $vendor_node = node_load($vnid);
    $approved = $vendor_node->status;

    $cnid = _get_company_nid_by_vendor($vendor_node);
    $vendor_status = !empty($vendor_node->field_vendor_status[LANGUAGE_NONE][0]['value']) ? $vendor_node->field_vendor_status[LANGUAGE_NONE][0]['value'] : '';

    if (!$cnid) {
      // If company NID is not received.
      drupal_set_message(t('Could not process due to some error. Please contact Admin.'), 'error', FALSE);
      $commands[] = ajax_command_remove('#messages-custom');
      $commands[] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    }
    else {
      $cnid_org = $cnid;
      if ($type_org == 'pending') {
        if (!empty($vendor_node->field_requestor_company[LANGUAGE_NONE][0]['target_id'])) {
          $cnid = $vendor_node->field_requestor_company[LANGUAGE_NONE][0]['target_id'];
        }
      }
      $form_state['cnid'] = $cnid;
      $cnode = node_load($cnid);

      // Trying to get company markup, to show to user.
      $company_intro = '';
      $company_intro .= '<div class="vendor-company-intro clearfix">';
      $only_address = _get_vendor_company_details($cnode, TRUE);
      $company_intro .= '<h5 class="text-center text-white">' . $cnode->title . ' <span>(' . $only_address . ')</span></h5>';
      
      $company_intro .= '<p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa.</p>';
      $company_intro .= '<p>Lorem ipsum dolor sit amet, consectetuer adipiscing elit.</p>';
      $company_intro .= '</div>';
      // $vendor_ratings_options = variable_get('vendor_rating_types', array());
      $vendor_ratings_options = _get_vendor_ratings_options($cnid, 'ratings');
      $commands[] = ajax_command_html('#vendor-company-intro-outer', $company_intro);
      $commands[] = ajax_command_invoke('#vendor-company-intro-outer', 'show');
      // $vendor_attributes_options = _get_vendor_ratings_options($company->nid, 'attributes');

      // Merging all the options.
      // $vendor_ratings_options += $vendor_attributes_options;
      
      // Adding drupal settings data in the ajax callback only.
      // $vendor_ratings = _get_vendor_ratings($vendor_node, $type, TRUE);
      $vendor_ratings = _get_vendor_ratings($cnode, $type, TRUE, TRUE);
      $vendor_ratings_js_data = array();

      foreach ($vendor_ratings_options as $key => $value) {
        $vendor_ratings_js_data[$key] = array('value' => $value, 'rating' => !empty($vendor_ratings[$key]) ? $vendor_ratings[$key] : 0,);
      }

      // Adding current ratings to JS.
      $argument = array('m6reach_vendor_rating_options' => $vendor_ratings_js_data);
      $commands[] = ajax_command_settings($argument, $merge = TRUE);

      $vendor_ratings_otf_data = _get_ratings_attributes_otf($cnode, 'ratings', $vendor_node);
      $vendor_attributes_otf_data = _get_ratings_attributes_otf($cnode, 'attributes', $vendor_node);

      $rating_attributes_otf_js_data = array();
      $rating_attributes_otf_js_data['ratings'] = $vendor_ratings_otf_data;
      $rating_attributes_otf_js_data['attributes'] = $vendor_attributes_otf_data;
      $argument = array('rating_attributes_otf_js_data' => $rating_attributes_otf_js_data);
      $commands[] = ajax_command_settings($argument, $merge = TRUE);

      if ($approved) {
        // We need user's ratings on only m6reach page, as on preferred, the
        // vendor is still need to be approved, so logically no ratings would
        // have been made yet.
        $result = _get_m6reach_form_data($cnid, $user->uid, $vnid, $form_state['m6reach_type'], FALSE);
      }

      $commands[] = ajax_command_invoke("input[name=cnid]", 'val',array($cnid));
      $commands[] = ajax_command_invoke("input[name=vnid]", 'val',array($vnid));
      $commands[] = ajax_command_invoke("select[name=vendor_node]", 'val',array($vnid));

      $commands[] = ajax_command_html('#main-container-ratings-pre', render($form['main-container']['vendor_ratings']));
      if (!empty($vendor_status)) {
        $commands[] = ajax_command_invoke("select[name=vendor_status]", 'val',array($vendor_status));
      }

      if (!empty($result) && $type_org == 'm6reach') {
        $data_serialized = $result['data'];
        $attr_data_serialized = $result['attributes'];
        $data = unserialize($data_serialized);

        if (!empty($attr_data_serialized)) {
          $attr_data = unserialize($attr_data_serialized);
          $data += $attr_data;
        }

        foreach ($vendor_ratings_options as $key => $value) {
          if (isset($data[$key])) {
            // $commands[] = ajax_command_invoke("select[name=" . $key . "][value=" . $data[$key] . "]", 'prop', array(array('checked' => TRUE)));
            $commands[] = ajax_command_invoke("input[name=".$key."]", 'val',array($data[$key]));
          }
        }
      }

      // Getting notes table, if we are on m6reach page, and not on preferred.
      if ($approved) {
        $commands[] = ajax_command_html('#notes-table-vendor', vendor_notes_table($cnid, $vendor_node));
      }

      // Preparing user messaging form.
      $user_msg_form = drupal_get_form('vendor_manager_messaging_form', $cnode, $vendor_node, $form_type);
      $commands[] = ajax_command_html('#form-for-messaging-div', render($user_msg_form));

      // Showing edit form.
      $commands[] = ajax_command_invoke('.vendor-m6reach-edit', 'show', array(500));
      $commands[] = ajax_command_invoke('#form-for-messaging-div', 'show');

      // Again initialising data tables.
      $commands[] = array('command'=>'initializeDataTables');

      // Approve deny buttons.
      $commands[] = ajax_command_html('#approve-deny-actions', render($form['approve_deny_actions']));
      if (!$approved) {
        $approve_preferred = array(
          '#type' => 'markup',
          '#markup' => l(t('Approve'), 'approve-deny-vendor/approve/' . $cnid_org . '/' . $vnid . '/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-assign-dashboard-popup-style', 'form-submit', 'text-white')))),
        );
        $deny_preferred = array(
          '#type' => 'markup',
          '#markup' => l(t('Deny'), 'approve-deny-vendor/deny/' . $cnid_org . '/' . $vnid . '/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-assign-dashboard-popup-style', 'form-submit', 'text-white')))),
        );
        $commands[] = ajax_command_html('#approve_vendor_preferred', render($approve_preferred));
        $commands[] = ajax_command_html('#deny-vendor-preferred', render($deny_preferred));
      }
      if ($approved) {
        $request_feedback = array(
          '#type' => 'markup',
          '#markup' => l(t('Request Feedback'), 'request-feedback/' . $cnid . '/' . $vnid . '/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-onboarding-message-popup-style', 'form-submit', 'text-white')))),
          '#prefix' => '<div class="m6reach-request-feedback pull-left" id="m6reach-request-feedback">',
          '#suffix' => '</div>',
        );
        $commands[] = ajax_command_replace("#m6reach-request-feedback", render($request_feedback));
      }
    }
  }

  $form_state['rebuild'] = FALSE;
  return array('#type' => 'ajax', '#commands' => $commands);
}


/**
 * Process main form container.
 */
function vendor_ratings_container_process($element, &$form_state) {
  global $company;
  // $vendor_ratings_options = variable_get('vendor_rating_types', array());
  if (empty($form_state['cnid'])) {
    // When the process is called from the vendor manager page, then form_state
    // does not contain cnid. Getting here, if not available.
    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#type'] == 'select' && $form_state['triggering_element']['#name'] == 'vendor_node' && !empty($form_state['triggering_element']['#value'])) {
      $vnid = $form_state['triggering_element']['#value'];
      $vendor_node = node_load($vnid);
      $cnid = _get_company_nid_by_vendor($vendor_node);
      if (!empty($cnid)) {
        $form_state['cnid'] = $cnid;
      }
    }
  }
  $vendor_ratings_options = _get_vendor_ratings_options($form_state['cnid'], 'ratings');

  // We only get attributes(for now) when we are on company page, and the user
  // who is viewing the company, has questions added in his company.
  // For ex- "User A" of "company B" is rating "company C" profile, and if the
  // vendor manager of "company B" has added any attributes, then those
  // attributes shall be visible on the "company C" page also.
  if (_show_attributes_options()) {
    $vendor_attributes_options = _get_vendor_ratings_options($company->nid, 'attributes');
  }

  // $vendor_ratings_js_data = $vendor_ratings_options;

  $default_values = array();
  if (!empty($form_state['m6reach_user_ratings'])) {
    // If default values are available.
    $default_values = $form_state['m6reach_user_ratings'];
  }

  if (!empty($form_state['include_m6rank_inc']) && $form_state['include_m6rank_inc']) {
    // We need to add an option of M6Rank beneath the available options.
    $vendor_ratings_options['m6rank_inc'] = t('M6 Rank');
  }

  foreach ($vendor_ratings_options as $key => $value) {
    $element[$key] = array(
      '#type' => 'hidden',
      '#value' => '0',
      '#prefix' => '<div class="toggle-outer relative clearfix"><div class="' . $key . '-outer" style="display:none;"><span class="' . $key . '-data" style="font-weight: 700;">' . $value . ' :</span>',
      '#suffix' => '<div id="' . $key . '-option"></div></div></div>',
    );

    // <div class="toggle-vendor-rating" data="' . $key . '-outer" style="cursor:pointer;">Toggle</div>
    // Trying to set default values, if user had already rated.
    // This is used when the form is shown on company profile page, and not on
    // vendor manager page. Because on vendor manager it is handled in ajax
    // callback.
    // @see vendor_node_change_callback().
    if (!empty($default_values)) {
      if (array_key_exists($key, $default_values)) {
        $element[$key]['#value'] = $default_values[$key];
      }
    }
  }

  if (_show_attributes_options() && !empty($vendor_attributes_options)) {
    $element['attributes_info'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="attributes-info-text"><p>' . t('Additional Feedback For Your Company.') . '</p></div><br/>'
    );

    foreach ($vendor_attributes_options as $key => $value) {
      $element[$key] = array(
        '#type' => 'hidden',
        '#value' => '0',
        '#prefix' => '<div class="toggle-outer relative clearfix"><div class="' . $key . '-outer inner-banner-cp-ratings" style="display:none;"><span class="' . $key . '-data" style="font-weight: 700;">' . $value . ' :</span>',
        '#suffix' => '<div id="' . $key . '-option"></div></div></div>',
      );

      // <div class="toggle-vendor-rating" data="' . $key . '-outer" style="cursor:pointer;">Toggle</div>
      // Trying to set default values, if user had already rated.
      // This is used when the form is shown on company profile page, and not on
      // vendor manager page. Because on vendor manager it is handled in ajax
      // callback.
      // @see vendor_node_change_callback().
      if (!empty($default_values)) {
        if (array_key_exists($key, $default_values)) {
          $element[$key]['#value'] = $default_values[$key];
        }
      }
    }
  }

  return $element;
}

/**
 * Process main form container on M6Reach page.
 */
function vendor_ratings_container_process_m6reach($element, &$form_state) {
  global $company;
  // $vendor_ratings_options = variable_get('vendor_rating_types', array());
  if (empty($form_state['cnid'])) {
    // When the process is called from the vendor manager page, then form_state
    // does not contain cnid. Getting here, if not available.
    if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#type'] == 'select' && $form_state['triggering_element']['#name'] == 'vendor_node' && !empty($form_state['triggering_element']['#value'])) {
      $vnid = $form_state['triggering_element']['#value'];
      $vendor_node = node_load($vnid);
      $cnid = _get_company_nid_by_vendor($vendor_node);
      if (!empty($cnid)) {
        $form_state['cnid'] = $cnid;
      }
    }
  }

  $vendor_ratings_options = _get_vendor_ratings_options($form_state['cnid'], 'ratings');
  if (!empty($vendor_ratings_options)) {
    foreach ($vendor_ratings_options as $key => $value) {
      $element[$key] = array(
        '#type' => 'hidden',
        '#default_value' => '0',
        // '#prefix' => '<div class="toggle-outer relative clearfix"><div class="' . $key . '-outer" style="display:none;"><span class="' . $key . '-data" style="font-weight: 700;">' . $value . ' :</span>',
        '#prefix' => '<div class="toggle-outer relative clearfix toggle-m6reach-rating"><div class="' . $key . '-outer"><span class="' . $key . '-data">' . $value . ' :</span>',
        '#suffix' => '<div id="' . $key . '-option"></div></div></div>',
        // '#suffix' => '<div id="' . $key . '-option"></div></div><div class="toggle-vendor-rating" data="' . $key . '-outer" style="cursor:pointer;">Toggle</div></div>',
      );
    }
  }

  return $element;
}

/**
 * Submit handler for vendor_m6reach_edit_form AND rating_node_form_vendor.
 */
function vendor_m6reach_edit_form_submit($form, $form_state) {
  global $user, $company;

  // $vendor_ratings_options = variable_get('vendor_rating_types', array());
  $vendor_ratings_options = _get_vendor_ratings_options($form_state['cnid'], 'ratings');
  $vendor_attributes_options = _get_vendor_ratings_options($company->nid, 'attributes');

  $data = array();
  $attr_data = array();

  // Checking if the form was submitted by the user whom company admin invited
  // directly to rate his company. If so, we need to store the data differently.
  $args = $form_state['build_info']['args'];
  $approved = 1;

  $company_page = in_array('company_page', $args);
  if (!empty($_GET['vendor']) && is_numeric($_GET['vendor']) && $vnode = node_load($_GET['vendor'])) {
    $company_page = FALSE;
  }
  // if (in_array('anonymous', $args)) {
  //   // If user is anonymous.
  //   $approved = 0;
  // }

  // Checking if user has already rated.
  // $already_rated = in_array('rated', $args);
  // if ($already_rated) {
  //   $approved = 1;

  //   if (in_array('anonymous', $args)) {
  //     // Checking if user is anonymous, then ratings are approved or not.
  //     $approved = in_array('approved', $args) ? 1 : 0;
  //   }
  // }

  // if (in_array('vendor_default', $args) || in_array('anonymous', $args)) {
  if ($company_page) {
    // If the form was submiited by such user.
    $cnid = $form_state['values']['cnid'];
    if (empty($cnid)) {
      $cnid = check_plain($form_state['input']['cnid']);
    }

    // Preparing rating data.
    foreach ($vendor_ratings_options as $key => $value) {
      // Latest and updated values will be found in input only.
      if (!empty($form_state['input'][$key]) && check_plain($form_state['input'][$key]) != 'm6rank_inc') {
        $data[$key] = check_plain($form_state['input'][$key]);
      }
    }

    // Preparing attribute data, if any.
    if (!empty($vendor_attributes_options)) {
      foreach ($vendor_attributes_options as $key => $value) {
        // Latest and updated values will be found in input only.
        if (!empty($form_state['input'][$key]) && check_plain($form_state['input'][$key]) != 'm6rank_inc') {
          $attr_data[$key] = check_plain($form_state['input'][$key]);
        }
      }
    }

    if (!empty($data)) {
      // If we have some data to save.
      $data_serialized = serialize($data);
      // In this case vnid will always be 0.
      $query = _get_m6reach_form_data($cnid, $user->uid, 0, 'm6reach');
      if (!empty($query)) {
        // If there is already data present, then this means that this particular
        // user had made a rating for this vendor.
        // So just updating its data.
        // We are not updating 'approved' field here, so as to keep the approved
        // field in control of company admin only.
        $id = $query['id'];

        $fields = array(
          'data' => $data_serialized,
          'created' => REQUEST_TIME,
        );
        if (!empty($attr_data)) {
          $attr_data_serialized = serialize($attr_data);
          $fields['attributes'] = $attr_data_serialized;
        }

        db_update('m6reach_ratings')
          ->fields($fields)
          ->condition('id', $id)
          ->execute();
        drupal_set_message(t('Ratings updated successfully.'));
      }
      else {
        // Note: vnid in this case is always 0.
        $fields = array(
          'cnid'     => $cnid,
          'uid'      => $user->uid,
          'vnid'     => 0,
          'type'     => 'm6reach',
          'data'     => $data_serialized,
          'created'  => REQUEST_TIME,
          'approved' => $approved,
        );

        if (!empty($attr_data)) {
          $attr_data_serialized = serialize($attr_data);
          $fields['attributes'] = $attr_data_serialized;
        }

        $rating_id = db_insert('m6reach_ratings')
          ->fields($fields)
          ->execute();

        // if ($approved == 0) {
        //   // If the user is not invited, then these ratings will be saved as
        //   // unapproved. So sending a notification and email to company admin,
        //   // that a user has made a rating, so that admin can review, and
        //   // approve/disapprove it.
        //   _send_unapproved_notification_mail('ratings', $cnid, $rating_id, TRUE);
        // }
        // else {
        _send_ratings_notes_notification('ratings', $cnid, 0, $rating_id);
        // }
        drupal_set_message(t('Ratings saved successfully.'));
      }

      // Updating the invite table.
      db_update('m6reach_company_invites')
        ->fields(array(
          'rated' => 1,
        ))
        ->condition(db_or()->condition('uid', $user->uid)->condition('email', $user->mail))
        ->condition('company', $cnid)
        ->execute();
    }
  }
  else {
    $type = $form_state['values']['m6reach_type'];
    $vnid = $form_state['values']['vnid'];
    if (empty($cnid)) {
      $cnid = check_plain($form_state['input']['cnid']);
    }
    if (empty($vnid)) {
      $vnid = check_plain($form_state['input']['vnid']);
    }

    if (empty($vnid) && !empty($vnode)) {
      $vnid = $vnode->nid;
    }

    foreach ($vendor_ratings_options as $key => $value) {
      // Latest and updated values will be found in input only.
      if (!empty($form_state['input'][$key])) {
        $data[$key] = check_plain($form_state['input'][$key]);
      }
    }

    // Preparing attribute data, if any.
    if (!empty($vendor_attributes_options)) {
      foreach ($vendor_attributes_options as $key => $value) {
        // Latest and updated values will be found in input only.
        if (!empty($form_state['input'][$key]) && check_plain($form_state['input'][$key]) != 'm6rank_inc') {
          $attr_data[$key] = check_plain($form_state['input'][$key]);
        }
      }
    }

    if (!empty($form_state['values']['vendor_status'])) {
      // If there is some value in vendor, then this means that the form was
      // submitted by a vendor manager, and we need to update this in the node.
      $vendor_node = node_load($vnid);

      if ($vendor_node->field_vendor_status[LANGUAGE_NONE][0]['value'] != $form_state['values']['vendor_status']) {
        // Updating field, only when values are changed.
        $vendor_node->field_vendor_status[LANGUAGE_NONE][0]['value'] = $form_state['values']['vendor_status'];

        field_attach_presave('node', $vendor_node);
        field_attach_update('node', $vendor_node);
        entity_get_controller('node')->resetCache(array($vendor_node->nid));
      }
    }

    if (!empty($data)) {
      // If we have some data to save.
      $data_serialized = serialize($data);
      $query = _get_m6reach_form_data($cnid, $user->uid, $vnid, $type);
      if (!empty($query)) {
        // If there is already data present, then this means that this particular
        // user had made a rating for this vendor.
        // So just updating its data.
        $id = $query['id'];

        $fields = array(
          'data' => $data_serialized,
          'created' => REQUEST_TIME,
        );

        if (empty($query['vnid']) && !empty($vnid)) {
          // In case, if the past ratings were made directly from company page,
          // we have to update the vendor nid this time.
          $fields['vnid'] = $vnid;
        }

        if (!empty($attr_data)) {
          $attr_data_serialized = serialize($attr_data);
          $fields['attributes'] = $attr_data_serialized;
        }

        db_update('m6reach_ratings')
          ->fields($fields)
          ->condition('id', $id)
          ->execute();
          drupal_set_message(t('Ratings updated successfully.'));
      }
      else {
        $fields = array(
          'cnid'     => $cnid,
          'uid'      => $user->uid,
          'vnid'     => $vnid,
          'type'     => $type,
          'data'     => $data_serialized,
          'created'  => REQUEST_TIME,
          'approved' => $approved,
        );

        if (!empty($attr_data)) {
          $attr_data_serialized = serialize($attr_data);
          $fields['attributes'] = $attr_data_serialized;
        }
        $id = db_insert('m6reach_ratings')
          ->fields($fields)
          ->execute();
        drupal_set_message(t('Ratings saved successfully.'));
      }

      // Sending notification to vendor manager and company admin.
      _send_ratings_notes_notification('ratings', $cnid, $vnid, $id);
    }

    if (!empty($_GET['vendor']) && $_GET['vendor'] != 'default' && arg(0) == 'node') {
      // If we are on company page, then updating the invite table.
      db_update('m6reach_invites')
        ->fields(array(
          'rated' => 1,
        ))
        ->condition('uid', $user->uid)
        ->condition('company', $cnid)
        ->condition('vendor', $vnid)
        ->execute();
    }
  }
  // Cleaning any notifications generated.
  if (arg(0) == 'node') {
    // These notifications are those, which users receive when a company admin
    // requests them to rate his company.
    _clean_vendor_notifications();

    // Removing query arguments.
    // $form_state['redirect'] = array(current_path());
    drupal_goto(current_path());
    drupal_exit();
  }
}

/**
 * Function to generate form for vendor spending.
 */
function vendor_spending_edit_form($form, &$form_state) {
  global $user, $company;
  if (empty($form_state['vendor_invoices_storage'])) {
    // If this element is empty, then creating one.
    $form_state['vendor_invoices_storage'] = array();
    $form_state['vendor_invoices_storage'][] = uniqid();
  }

  $hide_select_vendor = FALSE;
  if (!empty($form_state['triggering_element']) && $form_state['triggering_element']['#type'] == 'select') {
    $form_state['default_values'] = array();
    // If someone has changed a vendor, or editing a vendor.
    $tr_el = $form_state['triggering_element'];

    $vnid = !empty($tr_el['#value']) ? $tr_el['#value'] : '';
    $form_state['default_values']['vnid'] = $vnid;

    // These all 4 values are common in case of adding new or editing old.
    if ($vnode = node_load($vnid)) {
      if (!empty($vnode->field_regions[LANGUAGE_NONE][0]['tid'])) {
        $form_state['default_values']['region_of_work'] = $vnode->field_regions[LANGUAGE_NONE][0]['tid'];
      }
      if (!empty($vnode->field_pl_name[LANGUAGE_NONE][0]['value'])) {
        $form_state['default_values']['pl_name'] = $vnode->field_pl_name[LANGUAGE_NONE][0]['value'];
      }
      if (!empty($vnode->field_account_unit_desc[LANGUAGE_NONE][0]['value'])) {
        $form_state['default_values']['account_unit_desc'] = $vnode->field_account_unit_desc[LANGUAGE_NONE][0]['value'];
      }
      if (!empty($vnode->field_account_desc[LANGUAGE_NONE][0]['value'])) {
        $form_state['default_values']['account_desc'] = $vnode->field_account_desc[LANGUAGE_NONE][0]['value'];
      }
    }

    $form_state['vendor_invoices_storage'] = array();
    $form_state['vendor_invoices_storage'][] = uniqid();

    if ($tr_el['#name'] == 'vendor_spending_node_edit') {
      // If someone is editing then we don't want the user to change the vendor
      // again.
      $hide_select_vendor = TRUE;

      // Getting invoices in case of edit.
      if (!empty($vnode->field_invoice_amount[LANGUAGE_NONE])) {
        $form_state['vendor_invoices_storage'] = array();
        $count = count($vnode->field_invoice_amount[LANGUAGE_NONE]);
        for ($i = 0; $i < $count; $i++) { 
        // foreach ($vnode->field_vendor_spending_invoices[LANGUAGE_NONE] as $key => $value) {
          $uniqid = uniqid();
          $form_state['vendor_invoices_storage'][] = $uniqid; // Adding a row.
          // $fc_item = field_collection_item_load($value['value']);
          $form_state['default_values']['invoices'][$uniqid]['invoice_date'] = !empty($vnode->field_invoice_date[LANGUAGE_NONE][$i]['value']) ? $vnode->field_invoice_date[LANGUAGE_NONE][$i]['value'] : '';
          $form_state['default_values']['invoices'][$uniqid]['invoice_number'] = !empty($vnode->field_invoice_number_cal[LANGUAGE_NONE][$i]['value']) ? $vnode->field_invoice_number_cal[LANGUAGE_NONE][$i]['value'] : '';
          $form_state['default_values']['invoices'][$uniqid]['invoice_description'] = !empty($vnode->field_invoice_description[LANGUAGE_NONE][$i]['value']) ? $vnode->field_invoice_description[LANGUAGE_NONE][$i]['value'] : '';
          $form_state['default_values']['invoices'][$uniqid]['invoice_amount'] = !empty($vnode->field_invoice_amount[LANGUAGE_NONE][$i]['value']) ? $vnode->field_invoice_amount[LANGUAGE_NONE][$i]['value'] : '';
          $form_state['default_values']['invoices'][$uniqid]['amount_type'] = !empty($vnode->field_invoice_amount_type[LANGUAGE_NONE][$i]['value']) ? $vnode->field_invoice_amount_type[LANGUAGE_NONE][$i]['value'] : '';
        }
      }
    }
  }

  $form['vendor_spending_node_edit'] = array(
    '#type' => 'select',
    '#title' => t('Vendors'),
    '#options' => _get_vendor_names_spending(),
    '#default_value' => !empty($form_state['default_values']['vnid']) ? $form_state['default_values']['vnid'] : '',
    '#attributes' => array('class' => array('vendor-spending-node-select')),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'vendor_spending_vendor_callback',
      'wrapper' => 'vendor-spending-edit-form-main-container',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['company-intro'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="vendor-spending-company-intro-outer" style="display:none;">',
    '#suffix' => '</div>',
    '#markup' => '',
  );

  $form['main-container-pre'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="clearfix margin-bottom-10">',
  );
  $form['main-container'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'vendor-spending-edit-form-main-container'),
  );

  $form['main-container']['vnid'] = array(
    '#type' => 'hidden',
    '#value' => !empty($form_state['default_values']['vnid']) ? $form_state['default_values']['vnid'] : '',
  );
  $form['main-container']['reset_invoices'] = array(
    '#type' => 'hidden',
    '#value' => $hide_select_vendor ? 'Yes' : 'No',
  );

  $form['main-container']['main-prefix'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="main-prefix-left-vendor-spending row"><div class="col-md-6"><div class="field-item">',
  );
  // Region of field.
  // module_load_include('inc', 'field_ui', 'field_ui.admin');
  // $field = field_info_field('field_regions');
  // $instance = field_info_instance('node', 'field_regions', 'vendor');
  // $region_of_work = field_ui_default_value_widget($field, $instance, $form, $form_state);
  // // Reducing weight for region of work.
  // $region_of_work['field_regions']['#weight'] = 0;
  // $region_of_work['field_regions'][LANGUAGE_NONE][0]['tid']['#default_value'] = !empty($form_state['default_values']['pl_name']) ? $form_state['default_values']['pl_name'] : NULL;
  // dpm($region_of_work);
  // $form['main-container']['region_of_work'] = $region_of_work['field_regions']['und'][0]['tid'];
  // $form['main-container']['region_of_work']['#default_value'] = !empty($form_state['default_values']['region_of_work']) ? $form_state['default_values']['region_of_work'] : '';
  // $form['main-container']['region_of_work']['#title'] = t('Region of Work');

  $hide_class = $hide_select_vendor ? ' hidden' : '';


  $form['main-container']['select_vendor'] = array(
    '#type'    => 'select',
    '#title'   => t('Select Vendor'),
    '#options' => array('none' => '--Select an option--') + _get_vendor_names_spending('end_user'),
    '#default_value' => !empty($form_state['default_values']['vnid']) ? $form_state['default_values']['vnid'] : '',
    '#select2' => array(
      'width' => '350',
      'minimumResultsForSearch' => '5',
    ),
    '#attributes' => array('class' => array('vendor-select-vendor-trigger-me')),
    '#prefix'  => '<div class="clearfix form-item select-vendor-spending' . $hide_class . '">',
    '#suffix'  => '</div>',
    // '#required' => TRUE,
    '#ajax' => array(
      'callback' => 'vendor_spending_vendor_callback',
      'wrapper' => 'vendor-spending-edit-form-main-container',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    // '#access' => !$hide_select_vendor,
  );
  $form['main-container']['pl_name'] = array(
    '#type'  => 'textfield',
    '#title' => t('Site'),
    '#prefix' => '</div>',
    '#suffix' => '</div>',
    '#value' => !empty($form_state['default_values']['pl_name']) ? $form_state['default_values']['pl_name'] : '',
  );
  $form['main-container']['account_unit_desc'] = array(
    '#type'  => 'textfield',
    '#title' => t('Accounting Unit Description'),
    '#prefix' => '<div class="col-md-6">',
    '#value' => !empty($form_state['default_values']['account_unit_desc']) ? $form_state['default_values']['account_unit_desc'] : '',
  );
  $form['main-container']['account_desc'] = array(
    '#type'  => 'textfield',
    '#title' => t('Account Description'),
    '#suffix' => '</div></div>',
    '#value' => !empty($form_state['default_values']['account_desc']) ? $form_state['default_values']['account_desc'] : '',
  );
  $form['main-container']['invoices'] = array(
    '#type'    => 'container',
    '#process' => array('vendor_spending_invoices_process'),
    '#theme'   => 'vendor_spending_invoices_theme',
    '#prefix' => '<div id="vendor-spending-invoices-edit">',
    '#suffix' => '</div>',
  );
  $form['main-container-post'] = array(
    '#type' => 'markup',
    '#markup' => '</div>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('cancel-button-vendor-spending')),
  );

  return $form;
}


/**
 * Container process for vendor spending edit form.
 */
function vendor_spending_invoices_process($element, &$form_state) {
  $storage = $form_state['vendor_invoices_storage'];
  $element['#storage'] = $storage;

  // Creating fields.
  foreach ($storage as $key => $uniqId) {
    $element['invoice_date'][$uniqId] = array(
      '#title' => t('Invoice Date'),
      '#title_display' => 'invisible',
      '#type' => 'date_popup',
      '#date_format' => 'm/d/Y',
      '#date_year_range' => '-3:+3',
      '#attributes' => array('class'=> array('form-control entered_date'),'autocomplete' => 'off'),
      '#pre_render' => array('m6connect_programe_date_prerender'),
      '#prefix' => '<div class="clearfix form-item">',
      '#suffix' => '</div>',
      '#parents' => array('invoices', $uniqId, 'invoice_date'),
      '#default_value' => !empty($form_state['default_values']['invoices'][$uniqId]['invoice_date']) ? $form_state['default_values']['invoices'][$uniqId]['invoice_date'] : '',
    );
    $element['invoice_number'][$uniqId] = array(
      '#title' => t('Invoice Number'),
      '#type' => 'textfield',
      '#title_display' => 'invisible',
      '#parents' => array('invoices', $uniqId, 'invoice_number'),
      '#default_value' => !empty($form_state['default_values']['invoices'][$uniqId]['invoice_number']) ? $form_state['default_values']['invoices'][$uniqId]['invoice_number'] : '',
    );
    $element['invoice_description'][$uniqId] = array(
      '#title' => t('Invoice Description'),
      '#type' => 'textfield',
      '#title_display' => 'invisible',
      '#parents' => array('invoices', $uniqId, 'invoice_description'),
      '#default_value' => !empty($form_state['default_values']['invoices'][$uniqId]['invoice_description']) ? $form_state['default_values']['invoices'][$uniqId]['invoice_description'] : '',
    );
    $element['invoice_amount'][$uniqId] = array(
      '#title' => t('Invoice Amount'),
      '#type' => 'textfield',
      '#attributes' => array('class' => array('edit-vendor-spending-invoice-amt')),
      '#parents' => array('invoices', $uniqId, 'invoice_amount'),
      '#title_display' => 'invisible',
      '#default_value' => !empty($form_state['default_values']['invoices'][$uniqId]['invoice_amount']) ? $form_state['default_values']['invoices'][$uniqId]['invoice_amount'] : '',
    );
    $element['amount_type'][$uniqId] = array(
      '#title' => t('Type of Amount?'),
      '#type' => 'radios',
      '#options' => array(0 => t('Expense'), 1 => t('Capital')),
      '#required' => TRUE,
      '#attributes' => array('class'=> array('form-inline')),
      '#parents' => array('invoices', $uniqId, 'amount_type'),
      '#title_display' => 'invisible',
      '#after_build' => array('_m6connct_program_options_after_build'),
      // '#default_value' => !empty($form_state['default_values']['invoices'][$uniqId]['amount_type']) ? $form_state['default_values']['invoices'][$uniqId]['amount_type'] : '',
    );
    if (isset($form_state['default_values']['invoices'][$uniqId]['amount_type'])) {
      $element['amount_type'][$uniqId]['#default_value'] = $form_state['default_values']['invoices'][$uniqId]['amount_type'];
    }
  }

  // Add new button.
  $element['invoices_add_new_row'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    '#name' => 'invoices_add_new_row',
    '#attributes'=> array('class'=>array('invoices-add-new-row-button'),'title'=>'Add New Invoice'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('invoices_add_new_row_submit'),
    '#ajax' => array(
      'callback' => 'invoices_add_new_row_callback',
      'wrapper' => 'vendor-spending-invoices-edit',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="table-footer-custom clearfix margin-bottom-10" style="display:block;">',
    '#suffix' => '</div>',
  );
  return $element;
}

/**
 * Submit handler for adding new row for invoices.
 */
function invoices_add_new_row_submit($form, &$form_state) {
  $form_state['vendor_invoices_storage'][] = uniqid();
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for adding new row for invoices.
 */
function invoices_add_new_row_callback(&$form, &$form_state) {
  return $form['main-container']['invoices'];
}

/**
 * Container theme process for spending edit form.
 */
function theme_vendor_spending_invoices_theme($variables) {
  $element = $variables['form'];
  $storage = $element['#storage'];

  $output = '';

  $header= array(
    array('data'=>'Invoice Date','class'=>array('spending-invoice-date-edit', 'col-md-2')),
    array('data'=>'Invoice Number','class'=>array('spending-invoice-number-edit', 'col-md-2')),
    array('data'=>'Invoice Description','class'=>array('spending-invoice-number-edit', 'col-md-4')),
    array('data'=>'Invoice Amount','class'=>array('spending-invoice-amount-edit', 'col-md-2')),
    array('data'=>'Amount Type','class'=>array('spending-invoice-amount-type-edit', 'col-md-2')),
  );

  $rows = array();
  $i = 1;
  foreach ($storage as $key => $uniqId) {
    $rows[] = array(
      array('data' => drupal_render($element['invoice_date'][$uniqId])),
      array('data' => drupal_render($element['invoice_number'][$uniqId])),
      array('data' => drupal_render($element['invoice_description'][$uniqId])),
      array('data' => drupal_render($element['invoice_amount'][$uniqId])),
      array('data' => drupal_render($element['amount_type'][$uniqId])),
      // 'id' => array('vendor-spending-invoice-list-' . $i),
    );
    $i++;
  }

  $output .= '<div class="margin-bottom-10 clearfix">';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes'=> array('class'=> array('vendor-spending-edit-main-table','table','table-hover','m6connect-custom-table','m6connect-table-border'))));
  $output .= '</div>';
  $output .= drupal_render_children($element);
  return $output;
}

/**
 * Submit handler for vendor_spending_edit_form.
 */
function vendor_spending_edit_form_submit($form, &$form_state) {
  // dpm($form_state);
  // return;
  if (!empty($form_state['input']['vnid']) && is_numeric($form_state['input']['vnid'])) {
    $vnid = $form_state['input']['vnid'];
    $vnode = node_load($vnid);

    $reset_invoices = FALSE;
    if ($form_state['input']['reset_invoices'] == 'Yes') {
      $reset_invoices = TRUE;
    }

    $save_other = FALSE;
    if (!empty($form_state['input']['pl_name']) && check_plain($form_state['input']['pl_name']) != $form_state['values']['pl_name']) {
      $vnode->field_pl_name[LANGUAGE_NONE][0]['value'] = $form_state['input']['pl_name'];
      $save_other = TRUE;
    }
    if (!empty($form_state['input']['account_unit_desc']) && $form_state['input']['account_unit_desc'] != $form_state['values']['account_unit_desc']) {
      $vnode->field_account_unit_desc[LANGUAGE_NONE][0]['value'] = $form_state['input']['account_unit_desc'];
      $save_other = TRUE;
    }
    if (!empty($form_state['input']['account_desc']) && $form_state['input']['account_desc'] != $form_state['values']['account_desc']) {
      $vnode->field_account_desc[LANGUAGE_NONE][0]['value'] = $form_state['input']['account_desc'];
      $save_other = TRUE;
    }

    if ($save_other) {
      field_attach_presave('node', $vnode);
      field_attach_update('node', $vnode);
      entity_get_controller('node')->resetCache(array($vnode->nid));
    }

    // Trying to create a field collection item for invoices.
    if (!empty($form_state['values']['invoices'])) {
      // Saving invoices
      _save_vendor_spending_invoices($form_state['values']['invoices'], $vnid, $reset_invoices);
    }

    drupal_set_message(t('Invoices added/updated successfully.'));
  }
  else {
    drupal_set_message(t('Some problem occured, please try again later!'), 'error');
  }
}

/**
 * Helper function to save vendor spending invoices.
 */
function _save_vendor_spending_invoices($data, $vnid, $reset_invoices) {
  $vnode = node_load($vnid);
  if ($reset_invoices) {
    $i = 0;
    foreach ($data as $key => $invoice) {
      $vnode->field_invoice_date[LANGUAGE_NONE][$i] = array('value' => !empty($invoice['invoice_date']) ? date('Y-m-d H:i:s', strtotime($invoice['invoice_date'])) : '');
      $vnode->field_invoice_number_cal[LANGUAGE_NONE][$i] = array('value' => !empty($invoice['invoice_number']) ? $invoice['invoice_number'] : '');
      $vnode->field_invoice_description[LANGUAGE_NONE][$i] = array('value' => !empty($invoice['invoice_description']) ? $invoice['invoice_description'] : ''); // Blank for now in case of import.
      $vnode->field_invoice_amount[LANGUAGE_NONE][$i] = array('value' => !empty($invoice['invoice_amount']) ? str_replace(',', '', str_replace("$", "", $invoice['invoice_amount'])) : '');
      $vnode->field_invoice_amount_type[LANGUAGE_NONE][$i] = array('value' => $invoice['amount_type']); // 0 = Expense, 1 = Capital.
      $i++;
    }
  }
  else {
    foreach ($data as $key => $invoice) {
      $vnode->field_invoice_date[LANGUAGE_NONE][] = array('value' => !empty($invoice['invoice_date']) ? date('Y-m-d H:i:s', strtotime($invoice['invoice_date'])) : '');
      $vnode->field_invoice_number_cal[LANGUAGE_NONE][] = array('value' => !empty($invoice['invoice_number']) ? $invoice['invoice_number'] : '');
      $vnode->field_invoice_description[LANGUAGE_NONE][] = array('value' => !empty($invoice['invoice_description']) ? $invoice['invoice_description'] : ''); // Blank for now in case of import.
      $vnode->field_invoice_amount[LANGUAGE_NONE][] = array('value' => !empty($invoice['invoice_amount']) ? str_replace(',', '', str_replace("$", "", $invoice['invoice_amount'])) : '');
      $vnode->field_invoice_amount_type[LANGUAGE_NONE][] = array('value' => $invoice['amount_type']); // 0 = Expense, 1 = Capital.
    }
  }
  field_attach_presave('node', $vnode);
  field_attach_update('node', $vnode);
  entity_get_controller('node')->resetCache(array($vnode->nid));
}

/**
 * Ajax callback for vendor spending edit form.
 */
function vendor_spending_vendor_callback($form, &$form_state) {
  return $form['main-container'];
}

/**
 * Menu callback for vendor/dashboard.
 */
function vendor_m6reach_dashboard() {
  $elements['status_msg'] = array(
    '#type'   => 'markup',
    '#markup' => '<div id="vendor_status_msg" class="messages--status messages status" style="display:none;"></div>
      <div id   ="vendor_error_msg" class="messages--error messages error" style="display:none;"></div>',
  );

  $elements['table-section'] = array(
    '#markup' => _get_vendor_dashboard_content(),
    '#prefix' => '<div class="clearfix"><div class="table-responsive"><div class="vendor-m6reach-table" id="vendor_m6reach_table">',
    '#suffix' => '</div></div></div>',
  );

  return $elements;
}

/**
 * Menu callback for add-minority-vendor/%/nojs.
 */
function add_minority_vendor($type = 'm6reach', $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Invite Vendors');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
      'm6reach_type' => $type,
    );
    $output = ctools_modal_form_wrapper('add_minority_vendor_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('add_minority_vendor_form');
  }
}

/**
 * Form for adding minority vendor.
 */
function add_minority_vendor_form($form, &$form_state) {
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
 * Submit handler for the form add_minority_vendor_form.
 */
function add_minority_vendor_form_submit($form, &$form_state) {
  global $user, $base_url, $company;
  $account = user_load($user->uid);

  $vmname = _get_user_full_name($account->uid, $account);

  $m6reach_type = !empty($form_state['m6reach_type']) ? $form_state['m6reach_type'] : 'm6reach';

  $vnid = $form_state['values']['company'];
  $inviteToM6 = $form_state['values']['invite_to_m6'];

  if ($vnid == 0 && $inviteToM6 != '') {
    // If user wants to invite by Email.
    $getEmails = $form_state['values']['invite_to_m6'];
    $getEmails = explode(',', $getEmails);
    if (!empty($getEmails)) {
      foreach ($getEmails as $getEmail) {
        $vendor_counter = variable_get('vendor_counter', 1);
        $makeSr = sprintf('%08d', $vendor_counter);
        $vendor_number = $makeSr . '-' . date('Y');

        // Trying to create a new node of type vendor.
        $node = new stdClass();
        $node->type = 'vendor';
        $node->title = $vendor_number;
        $node->uid = $account->uid;
        $node->field_m6number[LANGUAGE_NONE][0]['value'] = $vendor_number;
        $node->field_vendor_status[LANGUAGE_NONE][0]['value'] = 'pending_-_invited';
        $node->field_vendor_type[LANGUAGE_NONE][0]['value'] = $m6reach_type == 'm6reach' || 'preferred' || 'pending' ? t('m6reach') : $m6reach_type;
        $node->status = 0;
        $node->field_outside_company_vendor[LANGUAGE_NONE][0]['value'] = $getEmail;
        node_save($node);
        $vendor_counter++;
        variable_set('vendor_counter', $vendor_counter);

        if ($new_nid = $node->nid) {
          // Making a link for the user registration.
          $query_data = array(
            'vendor_nid' => $new_nid,
            'vendor_uid' => $account->uid,
          );
          // $plain_url = $_plain_url . '?' . http_build_query($query_data);
          $link = url('user/register', array('query' => $query_data, 'absolute' => TRUE,));
          $click_link = t('<a href="@link">Click here</a>', array('@link' => $link,));
          $mailto = t('<a href="@mail_url">@mail</a>', array('@mail_url' => 'mailto:' . variable_get('site_mail', 'support@m6connect.com'), '@mail' => variable_get('site_mail', 'info@m6connect.com')));

          $message = 'Hello,<br/>';
          $message .= $vmname . ' has invited you on M6Connect to join as a Minority Vendor.<br/>';
          $message .= 'To join, please click on the link below.<br/><br/>';
          $message .= $click_link . '<br/><br/>';
          $message .= '<p>If the link is not clickable then copy paste this URL in the browser.<br/>';
          $message .= '<p>' . $link . '<p><br/><br/>';
          $message .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connect') . '</strong><br/>(' . $mailto . ')';

          $params = array(
            'subject' => 'Invitation to join as Minority Vendor - M6connect',
            'body' => $message,
            'sender' => $account->mail,
            'language' => language_default(),
            'module' => 'm6connect_misc',
            'key' => 'commitment_mail___invite_2_m6_notify',
            'build' => TRUE,
          );

          // Sending mail
          drupal_mail($params['module'], $params['key'], $getEmail, $params['language'], $params);
        }
      }
    }

    $form_state['ajax_commands'][] = ajax_command_html("#vendor_m6reach_table", _get_vendor_m6reach_table($m6reach_type));
    $form_state['ajax_commands'][] = ajax_command_invoke("#vendor_m6reach_table", 'removeClass', array('add-m6reach-datatables-processed'));
    $form_state['ajax_commands'][] = array('command'=>'initializeDataTables');

    // Showing message.
    drupal_set_message(t('Vendor invited successfully.'), 'status', FALSE);
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  elseif($vnid != 0 && $inviteToM6 == '') {
    $vendor_counter = variable_get('vendor_counter', 1);
    // $makeSr = str_pad($vendor_counter, 6, "0", STR_PAD_LEFT);
    $makeSr = sprintf('%08d', $vendor_counter);
    // $vendor_number = 'VENDOR-' . $makeSr . '-' . date('Y');
    $vendor_number = $makeSr . '-' . date('Y');

    // Trying to create a new node of type vendor.
    $node = new stdClass();
    $node->type = 'vendor';
    $node->title = $vendor_number;
    $node->uid = $account->uid;
    $node->field_m6number[LANGUAGE_NONE][0]['value'] = $vendor_number;
    $node->field_vendor_status[LANGUAGE_NONE][0]['value'] = 'pending_-_invited';
    $node->field_vendor_type[LANGUAGE_NONE][0]['value'] = $m6reach_type == 'm6reach' || 'preferred' ? t('m6reach') : $m6reach_type;
    $node->field_requestor_company[LANGUAGE_NONE][0]['target_id'] = $company->nid;
    $node->status = 0;
    // If user is adding a company as vendor.
    $node->og_group_ref[LANGUAGE_NONE][0]['target_id'] = $vnid;
    node_save($node);
    $vendor_counter++;
    variable_set('vendor_counter', $vendor_counter);

    $form_state['ajax_commands'][] = ajax_command_html("#vendor_m6reach_table", _get_vendor_m6reach_table($m6reach_type));
    $form_state['ajax_commands'][] = ajax_command_invoke("#vendor_m6reach_table", 'removeClass', array('add-m6reach-datatables-processed'));
    $form_state['ajax_commands'][] = array('command'=>'initializeDataTables');

    $form_state['ajax_commands'][] = array('command' => 'destroy_slider_m6reach');
    $form_state['ajax_commands'][] = ajax_command_replace('#vendor-m6reach-edit-form', render(drupal_get_form('vendor_m6reach_edit_form')));

    // Showing message.
    drupal_set_message(t('Vendor invited successfully.'), 'status', FALSE);
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');

    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  elseif ($vnid == 0 && $inviteToM6 == '') {
    // Else showing error!
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_page_error", '<div class="messages--error messages error"><h2 class="element-invisible">Error message</h2>Please fill either Company or Email field!</div>');
  }
}

/**
 * Menu callback for remove-vendor.
 */
function remove_vendor_ajax($node, $ajax = NUll) {
  if (!empty($ajax)) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'node' => $node,
    );

    $output = ctools_modal_form_wrapper('remove_vendor_ajax_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('remove_vendor_ajax_form', $node);
}

/**
 * Form to delete a vendor node.
 */
function remove_vendor_ajax_form($form, &$form_state, $node = NULL) {
  if (empty($form_state['node'])) {
    if (!empty($node) && is_object($node)) {
      $node = $node;
      $form_state['node'] = $node;
    }
  }
  else {
    $node = $form_state['node'];
  }

  $form = array();

  $delete = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to delete vendor: @title?', array('@title' => $node->title,)) . '</p></h4>';
  $delete .= '<p>' . t('All the related ratings, notes and likes will also be deleted.') . '</p></div>';

  $form['warning'] = array(
    '#type' => 'markup',
    '#markup' => $delete,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
  );
  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click(); return false;"><input type="button" class="btn cancel-button" value="Close"></a>',
  );

  return $form;
}

/**
 * Submit handler for remove_vendor_ajax_form.
 */
function remove_vendor_ajax_form_submit($form, &$form_state) {
  $node = $form_state['node'];
  $commands = array();

  if (is_object($node) && !empty($node->nid)) {
    // Getting the type of vendor manager. (m6reach, worker_feedback, ratings).
    $m6reach_type = 'm6reach';

    if (!$node->status) {
      $m6reach_type = 'pending';
    }

    if ($node->status) {
      $m6reach_type = 'preferred';
    }

    if (!empty($node->og_group_ref[LANGUAGE_NONE][0]['target_id'])) {
      // If we have og group reference for this, then loading it and checking
      // diversity.
      $og_node = node_load($node->og_group_ref[LANGUAGE_NONE][0]['target_id']);
      if (!empty($og_node->field_diversity_credentials[LANGUAGE_NONE][0]['target_id'])) {
        $m6reach_type = 'm6reach';
      }
    }

    // Deleting notes, ratings and likes data before deleting the node.

    // Deleting ratings.
    db_delete('m6reach_ratings')
      ->condition('vnid', $node->nid)
      ->execute();

    $notes = array();
    $notes = db_select('m6reach_notes', 'n')
      ->fields('n', array('id'))
      ->condition('vnid', $node->nid)
      ->execute()
      ->fetchCol();

    if (!empty($notes)) {
      // If there are notes on a node, then only there will likes.
      // First deleting likes and then notes.
      db_delete('m6reach_likes')
        ->condition('note_id', $notes)
        ->execute();

      // After deleting likes deleting notes.
      db_delete('m6reach_notes')
        ->condition('id', $notes)
        ->execute();
    }

    // After we have deleted all the related content, then deleting the node
    // itself.
    node_delete($node->nid);
  }

  // Showing message.
  drupal_set_message(t('Vendor @title deleted successfully.', array('@title' => $node->title)), 'status', FALSE);
  $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
  $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');

  $form_state['ajax_commands'][] = ajax_command_html('#vendor_m6reach_table', _get_vendor_m6reach_table($m6reach_type));

  $form_state['ajax_commands'][] = array('command'=>'initializeDataTables');
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for vendor-manager-messaging/%node/%user/%ctools_js.
 */
function vendor_manager_messaging($company_node, $node, $account, $ajax = NULL) {
  if (!empty($ajax)) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'company_node' => $company_node,
      'vendor_node' => $node,
      'vendor_user' => $account,
    );

    $output = ctools_modal_form_wrapper('vendor_manager_messaging_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('vendor_manager_messaging_form', $company_node, $node, $account);
}

/**
 * Function to build form for vendor manager messaging system.
 */
// @todo, send message to company admin, from vendor manager.
function vendor_manager_messaging_form($form, &$form_state, $company_node = NULL, $vendor_node = NULL, $form_type = NULL) {
  global $company, $user;
  $vendor_user = user_load($user->uid);

  if (empty($form_state['company_node'])) {
    $form_state['company_node'] = !empty($company_node) ? $company_node : NULL;
  }
  if (empty($form_state['vendor_user'])) {
    $form_state['vendor_user'] = !empty($vendor_user) ? $vendor_user : NULL;
  }
  if (empty($form_state['vendor_node'])) {
    $form_state['vendor_node'] = !empty($vendor_node) ? $vendor_node : NULL;
  }

  // $vendor_manager_ids = _get_company_users_by_og_roles($company->nid,'Vendor Manager');
  $company_admins = _get_company_users_by_og_roles_with_status($company_node->nid, 'company admin', 1);
  $is_company_admin_available = !empty($company_admins);

  if (empty($form_state['company_admins'])) {
    $form_state['company_admins'] = $company_admins;
  }

  $form = array();

  $form['#attributes'] = array('class' => array('vendor-manager-messaging-form'));

  $form['main_container'] = array(
    '#type' => 'container',
    '#attributes'=> array('class'=> array('appr-feedback-notes-block')),
  );
  $form['main_container']['heading'] = array(
    '#type' => 'markup',
    '#markup'=> '<div class="ins-feed-notes-title clearfix"><div class="ins-notes-title clearfix text-center text-white">Vendor Messenger</div></div>',
  );

  $ca_user_links = array();
  if ($is_company_admin_available) {
    foreach ($company_admins as $key => $value) {
      $fullname = _get_user_full_name($value);
      $ca_user_links[] = l($fullname, 'user/' . $value);
    }
  }

  if (!$is_company_admin_available) {
    $form['main_container']['left-manager-section'] = array(
      '#type' => 'markup',
      '#markup' => $is_company_admin_available ? '<div class="clearfix margin-bottom-10"><div class="ins-feed-submitter col-sm-6 padding-0">
        <div class="ins-feed-sub-title"><span class="sub-title">Company Admin - ' .implode(',&nbsp;', $ca_user_links) . '</span></div></div>' : '<div class="clearfix margin-bottom-10"><div class="ins-feed-submitter col-sm-6 padding-0">
        <div class="ins-feed-sub-title"><span class="sub-title">' . t('No Admin available for this company!') . '</span></div></div>',
    );
  }

  if ($is_company_admin_available) {
    $tousernames = '';
    // Showing message box to user, when there is company admin available for
    // the desired company.

    // Preparing JS data.
    $tousernames = _prepare_from_to_usernames_socket($company_admins);


    $form['vendor_nid_ms'] = array(
      '#type'  => 'hidden',
      '#value' => $vendor_node->nid,
    );
    $form['vendor_cuser_ms'] = array(
      '#type'  => 'hidden',
      '#value' => $vendor_user->uid,
    );
    $form['company_node_ms'] = array(
      '#type'  => 'hidden',
      '#value' => $company_node->nid,
    );
    $form['tofromnames'] = array(
      '#prefix' => '<div style="display:none;">',
      '#suffix' => '</div>',
      '#type' => 'textarea',
      '#attributes' => array('class' => array('m6messaging-tofromnames')),
      '#default_value' => $tousernames,
    );

    $form['main_container']['message_container']= array(
      '#type' => 'container',
      //'#attributes'=> array('class'=> array('col-sm-12','margin-bottom-10')),
    );

    $form['main_container']['message_container']['message-list'] = array(
      '#markup' => _get_vendor_manager_message_content($company_admins, $vendor_user, $vendor_node),
      '#prefix' => '<div id="onboarding_company_internal_container" class="clearfix">',
      '#suffix' => '</div>',
    );

    // Canned messages.
    $form['main_container']['message_container']['canned_msg'] = array(
      '#type' => 'markup',
      '#markup' => _get_canned_msg_markup(),
    );

    $form['main_container']['message_container']['message'] = array(
      '#type' => 'textarea',
      '#title' => 'Message',
      '#title_display' => 'invisible',
      '#attributes' => array('placeholder' => 'Please provide comments', 'id' => 'approval_feedback_message', 'class' => array('approval_feedback_message_msg','bidder_feedback_message_msg', 'onkeypress' => array('if(event.keyCode==13){this.form.submit();}'))),
      '#prefix' => '<div class="bidder_feedback_message_msg_submit">',
      '#rows' => 3,
      '#cols' => 20,
      '#resizable' => FALSE,
    );

    // File attachments in user messaging.
    $form['main_container']['message_container']['attachments'] = array(
      '#type' => 'file',
      '#title' => t('Attachments'),
      '#name' => 'files[]',
      '#upload_location' => 'public://',
      '#attributes' => array('id' => 'vendor-messaging-upload', 'onchange' => 'javascript:updateList()'),
      '#prefix' => '<div class="clearfix form-item" style="display:none;">',
      '#suffix' => '</div>',
    );
    $form['main_container']['message_container']['attachments_list'] = array(
      '#markup' => '<div id="vendor-messaging-upload-filelist" style="display:none;"></div>'
    );

    // Send message button in user messaging.
    $form['main_container']['message_container']['add'] = array(
      '#type' => 'markup',
      '#markup' => '<i class="fa fa-arrow-right fa-1-5x add_new_approval_feedback_message" aria-hidden="true"></i>',
      // '#value' => t('Send'),
      // '#value' => '<i class="fa fa-arrow-right fa-1-5x" aria-hidden="true"></i>',
      // '#attributes' => array('class' => array('add_new_approval_feedback_message','add_new_bidder_feedback_message')),
      '#executes_submit_callback' => FALSE,
      '#limit_validation_errors' => array(),
      '#prefix' => '<div class="add-canned-msg-div pull-right" id="add-canned-msg-button"><i class="fa fa-comments fa-1-5x add-canned-msg-link" aria-hidden="true"></i></div><div id="vendor-attach-fa"><i class="fa fa-paperclip fa-1-5x" aria-hidden="true"></i></div><div id="vendor-message-button-send" class="vendor-message-button-send-div">',
      '#suffix' => '</div><i class="fa fa-spinner fa-spin vendor-message-spinner fa-1-5x" aria-hidden="true" style="display:none;"></i></div>',
    );

    // Canned messages button in user messaging.
    // $form['main_container']['message_container']['add_canned'] = array(
    //   '#type' => 'markup',
    //   '#markup' => l(t('Canned Messages'), 'javascript:void(0)', array('attributes' => array('class' => array('form-submit', 'text-white', 'add-canned-msg-link')), 'external' => TRUE, 'html' => TRUE)),
    //   '#prefix' => '<div class="add-canned-msg-div pull-right" id="add-canned-msg-button">',
    //   '#suffix' => '</div>',
    // );
  }

  return $form;
}

/**
 * Submit handler for vendor manager message form.
 * Note: Message sending is now handled by AJAX (jQuery).
 * @see m6connect_vendor.js
 * Changed: May 23.
 */
/*function add_new_vendor_manager_message($form, &$form_state) {
  global $user, $company;

  $commands = array();
  $output = '';

  $company_admins = $form_state['company_admins'];

  $account = $form_state['vendor_user'];
  if (empty($account)) {
    $account = user_load($user->uid);
  }

  $vendor_node = $form_state['vendor_node'];

  $message = trim($form_state['values']['message']);

  if (!empty($message) && is_object($account) && is_object($vendor_node) && !empty($company_admins)) {
    $user_type = 'user';

    // Getting type of vendor.
    $type = !empty($vendor_node->field_vendor_type['und'][0]['value']) ? $vendor_node->field_vendor_type['und'][0]['value'] : 'm6reach';

    // Checking if the sender is vendor manager or company admin.
    if (in_array($account->uid, $company_admins)) {
      // Do nothing for now as we are not certain how to deliver a message from
      // a company admin from the vendor manager section to desired VM.
    }
    else {
      // If the user is not company admin, then user is sending the message
      // to company admins. So we need to send the message to every company
      // admin.

      // The approach for delivering message (by keeping the main user messaging
      // system in context) is that, we check if a user has a mapping id with
      // the desired company admin and for respective vendor node. If yes, then
      // using that mapping_id else generating new.
      // Then updating the mapping id in the main user messaging system, and
      // saving messages in the user messaging only, and nowhere else.

      foreach ($company_admins as $receiver) {
        // Getting mapping id for each user.
        $mapping_id = _get_mapping_id_service_messaging($type, $account->uid, $receiver, $vendor_node->nid);
        $mapping_id_updated = _update_mapping_id_user_messaging($mapping_id, $account->uid, $receiver);

        if ($mapping_id_updated) {
          // If the mapping_id is updated in the user messaging table, then
          // proceeding further and sending the message to desired user.
          _send_message_to_user_messaging($mapping_id, $account->uid, $message);
        }
      }
    }

    $output = _get_vendor_manager_message_content($company_admins, $account, $vendor_node);
    $commands[] = ajax_command_invoke('.approval_feedback_message_msg','val', array(''));
    $commands[] = ajax_command_html('#onboarding_company_internal_container', $output);
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}*/

/**
 * Menu callback for request-feedback/nojs.
 */
function request_feedback_m6reach($company, $vendor, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Request Feedback from Users</h4>',
      'company_node' => $company,
      'vendor_node' => $vendor,
    );
    $output = ctools_modal_form_wrapper('request_feedback_vendor_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('request_feedback_vendor_form', $company_node, $vendor_node);
  }
}

/**
 * Form for request feedback from users.
 */
function request_feedback_vendor_form($form, &$form_state, $company_node, $vendor_node) {
  $form = array();
  if (empty($form_state['company_node'])) {
    $form_state['company_node'] = !empty($company_node) ? $company_node : '';
  }
  if (empty($form_state['vendor_node'])) {
    $form_state['vendor_node'] = !empty($vendor_node) ? $vendor_node : '';
  }
  
  // Getting all users of current company, and making a list of those users
  // with predefined options.
  global $user, $company;
  $user_options = _get_user_options_for_request_feedback($company);

  $form['style-mark'] = array(
    '#prefix' => '<div class="form-horizontal">',
  );

  if (empty($user_options)) {
    // If there are no users, then showing a message.
    $no_users = '<div class="group-action-status"><h4><p>' . t('There are no active users in the @title except you!', array('@title' => $company->title,)) . '</p></h4>';
    $no_users .= '<p>' . t('Please invite some users to get feedback from them.') . '</p></div>';
    $form['no_users_notice'] = array(
      '#type' => 'markup',
      '#markup' => $no_users,
    );
  }
  else {
    // If there are users, then we need to make a select field for each user.
    $user_select_options = drupal_map_assoc(array('Not Required', 'Preferred', 'Required',));

    foreach ($user_options as $uid => $name) {
      $form[$uid . '_markup'] = array(
        '#markup' => '<label class="user-option-name col-sm-4 control-label">' . ucwords($name) . '</label>',
        '#prefix' => '<div class="user-option-item form-group">',
      );

      $form[$uid] = array(
        '#type' => 'select',
        '#title' => t('Select Preference'),
        '#title_display' => 'invisible',
        // '#attributes' => array('class' => array('form-control')),
        '#options' => $user_select_options,
        '#prefix' => '<div class="user-option-preference col-sm-8">',
        '#suffix' => '</div></div>',
        '#parents' => array('users', $uid),
      );
    }

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Request Feedback'),
    );
  }

  $form['close'] = array(
    '#type' => 'markup',
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Submit handler for request_feedback_vendor_form.
 */
function request_feedback_vendor_form_submit($form, &$form_state) {
  global $user;
  $user_name = _get_user_full_name($user->uid);
  $users = $form_state['values']['users'];
  $users = array_diff($users, array('Not Required'));

  // Getting list of all users who have rated for the current company.
  $already_rated_users = _get_rated_invited_users($form_state['company_node'], $form_state['vendor_node'], 1);
  $already_invited_users = _get_rated_invited_users($form_state['company_node'], $form_state['vendor_node'], 0);
  
  $status_msg = t('No users selected as Preferred or Required. No request sent.');
  $update_table_data = array();
  $remind_users = array();
  if (!empty($users)) {
    // Preparing message content.
    $query_data = array(
      'vendor' => $form_state['vendor_node']->nid,
    );

    $link = url('node/' . $company->nid, array('query' => $query_data, 'absolute' => TRUE,));
    $click_link = t('<a href="@link">Click here</a>', array('@link' => $link,));
    $mailto = t('<a href="@mail_url">@mail</a>', array('@mail_url' => 'mailto:' . variable_get('site_mail', 'support@m6connect.com'), '@mail' => variable_get('site_mail', 'info@m6connect.com')));

    // Body of the mail to be sent.
    $message = 'Hello,<br/>';
    $message .= $user_name . ' has requested you to provide feedback for his company (' . ucwords($company->title) . ').<br/>';
    $message .= 'To provide feedback, please click on the link below.<br/><br/>';
    $message .= $click_link . '<br/><br/>';
    $message .= '<p>If the link is not clickable then copy paste this URL in the browser.<br/>';
    $message .= '<p>' . $link . '<p><br/><br/>';
    $message .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connect') . '</strong><br/>(' . $mailto . ')';

    foreach ($users as $uid => $preference) {
      // Sending mail to each user.
      if (in_array($uid, $already_rated_users)) {
        // If this user has already rated then skipping.
        continue;
      }
      if (in_array($uid, $already_invited_users)) {
        // If this user has been already invited but has not rated yet.
        // then reminding the user again, and skipping.
        $remind_users[] = $uid;
        continue;
      }

      $update_table_data[] = $uid;

      $account = user_load($uid);

      $params = array(
        'subject' => 'Request to give ratings - M6Connect',
        'body' => $message,
        'sender' => $user->mail,
        'language' => language_default(),
        'module' => 'm6connect_misc',
        'key' => 'commitment_mail___invite_2_m6_notify',
        'build' => TRUE,
      );
      drupal_mail($params['module'], $params['key'], $account->mail, $params['language'], $params);

      // Trying to send a notification to the user.
      $m6connect_notification = array (
        'type' => 'vendor_manager_request',
        'event' => 'feedback',
        'entity_id' => $form_state['company_node']->nid,
        'company_nid' => $form_state['vendor_node']->nid,
        'message' => 'vendor',
        'request_from' => $user->uid,
        'request_to' => $account->uid,
        'status' => 1,
        'timestamp' => REQUEST_TIME,
      );
      entity_save('m6connect_notification', (object)$m6connect_notification);
    }

    $status_msg = t('Email successfully sent to requested users.');
    if (empty($update_table_data) && empty($remind_users)) {
      $status_msg = t('No users found.');
    }
    elseif (empty($update_table_data) && !empty($remind_users)) {
      $status_msg = t('Selected users were already requested to provide feedback, reminder email and notifications sent.');
    }
  }

  if (!empty($update_table_data)) {
    // If there are any users to update data.
    // Updating the user invitation log entry.
    _update_m6reach_vendor_invites_data($update_table_data, $form_state['company_node'], $form_state['vendor_node']);
  }
  if (!empty($remind_users)) {
    // If there are any users whom reminder is to sent.
    _remind_m6reach_invitation_again($remind_users, $form_state['company_node'], $form_state['vendor_node']);
  }

  // Showing message.
  drupal_set_message($status_msg, 'status', FALSE);
  $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
  $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');

  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for export/vendor-spendings/%ctools_js
 */
function export_vendor_data($ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Spending Report');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
      'm6reach_type' => $type,
    );
    $output = ctools_modal_form_wrapper('export_vendor_data_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('export_vendor_data_form');
  }
}

/**
 * Form for exporting form data.
 */
function export_vendor_data_form($form, &$form_state) {
  // Give user option to export by region and date.
  $options = _get_region_options_vendor_spending_export('options');
  $form['region'] = array(
    '#type' => 'select',
    '#options' => array('all' => 'All') + $options,
    '#title' => t('Select Region'),
  );

  $form['date_range_start'] = array(
    '#title' => t('Start Date'),
    '#title_display' => 'before',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',
    '#attributes' => array('class'=> array('form-control entered_date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#prefix' => '<div class="clearfix form-item"><div class="date-prefix-desc"><p>Select a date range from below, or choose an option</p></div>',
    '#suffix' => '</div>',
  );
  $form['date_range_stop'] = array(
    '#title' => t('End Date'),
    '#title_display' => 'before',
    '#type' => 'date_popup',
    '#date_format' => 'm/d/Y',
    '#date_year_range' => '-3:+3',
    '#attributes' => array('class'=> array('form-control entered_date'),'autocomplete' => 'off'),
    '#pre_render' => array('m6connect_programe_date_prerender'),
    '#suffix' => '<div class="date-suffix-desc"><p>OR</p></div>',
  );
  $form['date_ranges'] = array(
    '#type' => 'select',
    '#options' => array(
      'all' => t('All'),
      'current_month' => t('Current Month'),
      'current_year' => t('Current Year'),
      'last_month' => t('Last Month'),
      'last_year' => t('Last Year'),
    ),
    '#title' => t('Select a fixed range'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Generate Report'),
  );

  if ($form_state['ajax']) {
    $form['close'] = array(
      '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
      '#suffix' => '</div></div>',
    );
  }
  else {
    $form['cancel'] = array(
      '#type' => 'button',
      '#value' => t('Cancel'),
      '#attributes' => array('class' => array('cancel-exporting-data')),
    );
  }

  return $form;
}

/**
 * Submit handler for export_vendor_data_form
 */
function export_vendor_data_form_submit($form, &$form_state) {
  // Collecting info on filtering the reports.
  $start = !empty($form_state['values']['date_range_start']) ? $form_state['values']['date_range_start'] : '';
  $end = !empty($form_state['values']['date_range_stop']) ? $form_state['values']['date_range_stop'] : '';
  $date_ranges = $form_state['values']['date_ranges'];
  $region = !empty($form_state['values']['region']) && $form_state['values']['region'] != 'all' ? $form_state['values']['region'] : '';

  // We have given users two options, either select start and end date, or
  // select a date range.
  // We have to decide the priority for this.
  // So for now, untill client clears, we are giving first prioriry to start and
  // end dates, and then date ranges.
  $date_ranges_options = _get_date_ranges_start_end_options($start, $end);
  if (empty($date_ranges_options['start'])) {
    // If we do not have start and end date, then we try to get start and end
    // date options from range.
    $date_ranges_options = _get_date_ranges_options($date_ranges);
  }

  $nodes = _get_region_options_vendor_spending_export('options', $region, $date_ranges_options['start'], $date_ranges_options['end']);

  // Now preparing report header variables.
  $by_region = 'All Regions';
  if ($region != 'all' && !empty($region)) {
    $region_taxo = taxonomy_term_load($region);
    $by_region = ucwords($region_taxo->name);
  }

  $by_time = 'All';
  if (!empty($date_ranges_options['start'])) {
    $by_time = 'From ' . date('m-d-Y', $date_ranges_options['start']) . ' to ' . date('m-d-Y', $date_ranges_options['end']);
  }

  global $user, $base_url, $base_path, $company;

  if (isset($company->field_logo[LANGUAGE_NONE])) {
    $companyLogo = '<img src="'.image_style_url('user_photo_tab_162', $company->field_logo[LANGUAGE_NONE][0]['uri']).'">';
  }
  else {
    $companyLogo = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" height="70" width="70">';
  }

  // Preparing content.
  $content = theme('vendor_spending_export_pdf', array('nodes' => $nodes));

  // Including mpdf library
  include_once(libraries_get_path('mpdf') . '/mpdf.php'); 
  $mpdf = new mPDF('c', 'A4-L');

    $reportTitle = t('Diversity Spend Report');

    $pdf_header = '<div class="page_header"><table style="margin:0; width:100%;"><tr><td width="200">' . $companyLogo . '</td><td width="300" align="center" style="vertical-align:top;"><h2>' . ucwords($reportTitle) . '</h2></td><td width="200"><p style="margin:0;">&nbsp;</p></td></tr></table></div>';

    // Regions in header
    $pdf_header .= '<div class="region-outer" style="float:left;width:100%;">
      <div class="region-label" style="float:left;width:80px;">By Region:</div>
      <div class="region-content" style="float:left;width:220px;">' . $by_region . '</div>
      </div>';

    // Timeframe in header
    $pdf_header .= '<div style="float:left;width:100%;margin-bottom:25px;">
      <div class="timeframe-outer" style="float:left;width:70%;">
        <div class="timeframe-label" style="float:left;width:80px;">Timeframe:</div>
        <div class="timeframe-content" style="float:left;width:220px;">' . $by_time . '</div>
      </div>';

    // Report date.
    $pdf_header .= '<div class="report-date-outer" style="float:left;width:30%;text-align: right;">
      <div class="report-date-content" style="float:right;width:100px; padding-left:10px;">'.date("m-d-Y").'</div>
      <div class="report-date-label" style="float:right;width:80px;">Report Date:</div>
      </div></div>';

    $mpdf->SetHTMLHeader($pdf_header);

    // if($type == 'costsummary') { $addFooter = '<pagebreak suppress="off" />'; } else { $addFooter = ''; }
    $addFooter = '';
    $mpdf->SetHTMLFooter('<div class="page_footer" style="float:left; width:100%;"><div style="float:left; width:100%;"><hr style="height:1px; border:none; border-bottom:1px solid #CCC;"></div><div style="float:left; width:100%; clear:both;"><div style="float:left; width:33.33%; text-align:left;"><img src="/sites/all/themes/m6connect/images/bidder_report_footer.png" alt="res" width="100" /></div><div style="float:left; width:33.33%; text-align:center;">Page {PAGENO} of {nb}</div><div style="float:left; width:33.33%; text-align:right;">' . date("l, F d, Y") . '</div></div></div>'.$addFooter);

    $mpdf->setAutoTopMargin = 'stretch';
    $mpdf->setAutoBottomMargin = 'stretch';
    $mpdf->WriteHTML($content);

    // Saving content to the file.
    // Deleting any file with the same name.
    // file_unmanaged_delete('public://vendor-spend-report.pdf');
    $tt = time();
    // $file_content = $mpdf->Output('public://vendor-spend-report' . $tt . '.pdf', 'F');
    // $form_state['redirect'] = file_create_url('public://vendor-spend-report' . $tt . '.pdf');
    $mpdf->Output('vendor-spend-report.pdf', 'D');
    drupal_exit();

    // Dismissing the command and redirecting.
    // $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    // $form_state['ajax_commands'][] = ctools_ajax_command_redirect(file_create_url('public://vendor-spend-report'.$tt.'.pdf'), 0, array(), TRUE);
}

/**
 * Test pdf menu callback
 */
function vendor_testpdf() {
  global $user, $company;
  $nodes = _get_region_options_vendor_spending_export('options');
  $companyLogo = _get_vendor_company_details($company, FALSE, TRUE, 'check_user_ava_150_150');

  // Preparing content.
  $content = theme('vendor_spending_export_pdf', array('nodes' => $nodes));

  $by_region = 'All Regions';
  $by_time = 'From 06-01-2017 to 06-19-2017';

  // Including mpdf library
  include_once(libraries_get_path('mpdf') . '/mpdf.php'); 
  $mpdf = new mPDF('c', 'A4-L');

  $reportTitle = t('Diversity Spend Report');

  $pdf_header = '<div class="page_header"><table style="margin:0; width:100%;"><tr><td width="200">' . $companyLogo . '</td><td width="300" align="center" style="vertical-align:top;"><h2>' . ucwords($reportTitle) . '</h2></td><td width="200"><p style="margin:0;">&nbsp;</p></td></tr></table></div>';

  // Regions in header
  $pdf_header .= '<div class="region-outer" style="float:left;width:100%;">
    <div class="region-label" style="float:left;width:80px;">By Region:</div>
    <div class="region-content" style="float:left;width:220px;">' . $by_region . '</div>
    </div>';

  // Timeframe in header
  $pdf_header .= '<div style="float:left;width:100%;margin-bottom:25px;">
		<div class="timeframe-outer" style="float:left;width:70%;">
    	<div class="timeframe-label" style="float:left;width:80px;">Timeframe:</div>
    	<div class="timeframe-content" style="float:left;width:220px;">' . $by_time . '</div>
    </div>';

  // Report date.
  $pdf_header .= '<div class="report-date-outer" style="float:left;width:30%;text-align: right;">
    <div class="report-date-content" style="float:right;width:100px; padding-left:10px;">'.date("m-d-Y").'</div>
    <div class="report-date-label" style="float:right;width:80px;">Report Date:</div>
    </div></div>';

  $mpdf->SetHTMLHeader($pdf_header);

  // if($type == 'costsummary') { $addFooter = '<pagebreak suppress="off" />'; } else { $addFooter = ''; }
  $mpdf->SetHTMLFooter('<div class="page_footer" style="float:left; width:100%;"><div style="float:left; width:100%;"><hr style="height:1px; border:none; border-bottom:1px solid #CCC;"></div><div style="float:left; width:100%; clear:both;"><div style="float:left; width:33.33%; text-align:left;"><img src="/sites/all/themes/m6connect/images/bidder_report_footer.png" alt="res" width="100" /></div><div style="float:left; width:33.33%; text-align:center;">Page {PAGENO} of {nb}</div><div style="float:left; width:33.33%; text-align:right;">' . date("l, F d, Y") . '</div></div></div>');

  $mpdf->setAutoTopMargin = 'stretch';  
  $mpdf->setAutoBottomMargin = 'stretch'; 
  $mpdf->WriteHTML($content);
  $file_content = $mpdf->Output('report.pdf', 'D');
  return 'Hi, testing it.';
}