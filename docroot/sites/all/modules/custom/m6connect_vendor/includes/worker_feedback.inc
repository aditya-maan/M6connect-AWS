<?php

/**
 * @file Menu callbacks and dependent functions for Vendor Worker Callback.
 *
 * @info - All helper functions (starting with "_" are in .module file).
 */
function vendor_worker_feedback_content() {
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/m6connect_worker_feedback.js');

  $elements = array();

  $elements['status_msg'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="vwf_status_msg" class="messages--status messages status" style="display:none;"></div>
      <div id="vwf_msg" class="messages--error messages error" style="display:none;"></div>',
  );
  $elements['edit-section'] = array(
    '#markup' => render(drupal_get_form('vendor_worker_feedback_edit_form')),
    '#prefix' => '<div class = "clearfix margin-bottom-10 padding-10"><div class="worker-feedback-m6reach-edit" id="worker-feedback-m6reach-edit-id" style="display:none;">',
    '#suffix' => '</div></div>',
  );
  $elements['notes-section'] = array(
    '#markup' => '<div class = "clearfix margin-bottom-10 padding-10"><div id="notes-table-worker-feedback" style="display:none;"></div></div>',
  );
  $elements['table-section'] = array(
    '#markup' => _get_vendor_worker_feedback_table(),
    '#prefix' => '<div class="clearfix"><div class="table-responsive"><div class="vendor-worker-feedback-table" id="vendor_worker_feedback_table">',
    '#suffix' => '</div></div></div>',
  );

  return $elements;
}

/**
 * Form worker feedback.
 */
function vendor_worker_feedback_edit_form($form, &$form_state) {
  global $user, $company;
  $is_user_vendor_manager = _is_user_vendor_manager($company, $user);

  $form = array();
  $current_worker = '';
  // dpm($form_state);
  // if (!empty($form_state['worker_feedback_default_values'])) {
  //   $current_values = $form_state['worker_feedback_default_values'];
  //   dpm($current_values);
  //   $current_worker = !empty($current_values['current_worker']) ? $current_values['current_worker'] : '';
  //   $current_worker_status = !empty($current_values['current_worker_status']) ? $current_values['current_worker_status'] : '';
  // }

  $form['notes_dialog'] = array(
    '#type' => 'markup',
    '#markup' => '<div id="vwf-like-dislike-processed-dialog" style="display:none;"></div>',
  );

  $form['worker_selector'] = array(
    '#type' => 'select',
    '#title' => t('Workers'),
    '#options' => _get_worker_names(),
    // '#default_value' => $current_worker,
    '#ajax' => array(
      'wrapper' => 'worker-feedback-edit-form-main-container',
      'callback' => 'worker_selector_change_callback',
    ),
    '#attributes' => array('class' => array('worker-selector-select')),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
  );

  $form['main-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix worker-feedback-m6reach-edit margin-bottom-10" id="worker-feedback-edit-form-main-container">',
    '#suffix' => '</div>',
  );

  $form['main-container']['worker_feedback_ratings'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('edit-worker-feedback-ratings')),
    '#process' => array('worker_selector_ratings_container_process'),
    '#prefix' => '<span class="worker-selector-ratings-container padding-10 pull-left col-md-6">',
    '#suffix' => '</span>',
  );

  $worker_feedback_status_options = variable_get('vendor_status', array('-- None --'));

  $worker_feedback_default_value = '';

  $form['main-container']['worker_feedback_status'] = array(
    '#type' => 'select',
    '#options' => $worker_feedback_status_options,
    '#title' => t('Worker Status'),
    // '#default_value' => $current_worker_status,
    '#attributes' => array('class'=> array('form-control')),
    '#prefix' => '<div class="padding-10 pull-left col-md-6 form-inline">',
    '#suffix' => '</div>',
    '#access' => $is_user_vendor_manager,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit Feedback'),
  );
  $form['request_feedback'] = array(
    '#type' => 'button',
    '#value' => t('Request Feedback'),
    '#ajax' => array(
      'callback' => 'request_feedback_callback_worker_feedback',
      'wrapper' => 'vwf_status_msg',
    ),
    '#access' => $is_user_vendor_manager,
  );
  $form['view_feedback'] = array(
    '#type' => 'button',
    '#value' => t('View Notes'),
    '#attributes' => array('class' => array('view-feedback-worker')),
  );
  $form['cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('cancel-button')),
  );

  return $form;
}

/**
 * Ajax callback for worker change.
 */
function worker_selector_change_callback($form, &$form_state) {
  global $user;
  $commands = array();

  $form_state['worker_feedback_default_values'] = array();
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#type'] == 'select' && $form_state['triggering_element']['#name'] == 'worker_selector' && !empty($form_state['triggering_element']['#value'])) {
    // Preparing data for editing.

    if ($account = user_load($form_state['triggering_element']['#value'])) {
      $form_state['worker_feedback_default_values']['current_worker'] = $account->uid;
      // Loading default options.
      $worker_feedback_ratings_options = variable_get('vendor_rating_types', array());
      
      // Getting User's Rating data.
      $worker_ratings = _get_worker_ratings_by_uid($account, TRUE);
      $worker_feedback_ratings_js_data = array();

      foreach ($worker_feedback_ratings_options as $key => $value) {
        $worker_feedback_ratings_js_data[$key] = array('value' => $value, 'rating' => !empty($worker_ratings[$key]) ? $worker_ratings[$key] : 0,);
      }

      $argument = array('worker_feddback_rating_options' => $worker_feedback_ratings_js_data);
      $commands[] = ajax_command_settings($argument, $merge = FALSE);

      $worker_info = _get_worker_info_by_uid($account); // Getting worker info

      if (!empty($worker_info)) {
        $worker_feedback_status = $worker_info['status'];
        $form_state['worker_feedback_default_values']['current_worker_status'] = $worker_feedback_status;

        $commands[] = ajax_command_invoke("select[name=worker_selector]", 'val',array($account->uid));
        $commands[] = ajax_command_invoke("select[name=worker_feedback_status]", 'val',array($worker_feedback_status));


        $data_serialized = $worker_info['data'];
        $data = unserialize($data_serialized);
        foreach ($worker_feedback_ratings_options as $key => $value) {
          if (isset($data[$key])) {
            $commands[] = ajax_command_invoke("input[name=".$key."]", 'val',array($data[$key]));
          }
        }
        
        // Getting notes table.
        $commands[] = ajax_command_html('#notes-table-worker-feedback', _get_worker_notes_table($account));
        $commands[] = ajax_command_invoke('.worker-feedback-m6reach-edit', 'show', array(500));
      }
    }
    else {
      // If user id is wrong or user not loaded.
      $error_msg = t('Could not process due to some error. Please contact Admin.');
      $commands[] = ajax_command_html("#vwf_msg", $error_msg);
      $commands[] = ajax_command_invoke('#vwf_msg', 'show');
    }
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Process callback for worker selector ratings.
 */
function worker_selector_ratings_container_process($element, &$form_state) {
  $worker_feedback_ratings_options = variable_get('vendor_rating_types', array());

  $element['#attached']['css'][] = array(
    'data' => '.worker-selector-ratings-container label {
      position: absolute;
      margin-left: -10px;
      text-align: center;
      margin-top: 20px;
    }
    .edit-worker-feedback-ratings > div {
      padding-bottom: 30px;
      padding-left: 13px;
    }
    .worker-selector-ratings-container .custom-ui-handle-disable {
       margin-left: -0.6em;
       top: -0.3em;
       cursor: default;
       height: 1.2em;
       position: absolute;
       width: 1.2em;
       z-index: 2;
       background: #e6e6e6 url("/sites/all/modules/jquery_update/replace/ui/themes/base/minified/images/ui-bg_glass_75_e6e6e6_1x400.png") repeat-x scroll 50% 50%;
       border: 1px solid #d3d3d3 ;
       color: #555;
       font-weight: 400;
       border-radius: 4px;
       opacity: 0.75;
    }
    .ui-slider .ui-slider-handle {
      cursor: pointer;
    }
    .worker-selector-ratings-container .ui-widget-content {
      background: #fff url(/sites/all/themes/m6connect/images/vendor-bar.jpg) 50% 50% no-repeat;
      background-size: cover;
    }',
    'type' => 'inline',
  );

  foreach ($worker_feedback_ratings_options as $key => $value) {
    $element[$key] = array(
      '#type' => 'hidden',
      '#value' => '0',
      '#prefix' => '<div class = "' . $key . '-outer"><span class = "' . $key . '-data" style="font-weight: 700;">' . $value . ' :</span>',
      '#suffix' => '<div id = "' . $key . '-option"></div></div>',
    );
  }
  
  return $element;
}

/**
 * Ajax callback for request feedback for worker feedback.
 */
function request_feedback_callback_worker_feedback($form, &$form_state) {
  return;
}

/**
 * Submit callback for vendor_worker_feedback_edit_form.
 */
function vendor_worker_feedback_edit_form_submit($form, &$form_state) {
  global $user, $company;

  $data = array();
  $worker = $form_state['values']['worker_selector'];

  if (!empty($worker_feedback_status = $form_state['values']['worker_feedback_status'])) {
    // If the worker feedback status is not empty, then updating it in base table.
    db_update('worker_feedback')
      ->fields(array(
        'status' => $worker_feedback_status,
      ))
      ->condition('uid', $worker)
      ->execute();
  }

  $worker_feedback_ratings_options = variable_get('vendor_rating_types', array());

  // Collecting data to be stored.
  foreach ($worker_feedback_ratings_options as $key => $value) {
    // First getting values from input, and checking if available in values.
    // Values present in $form_state['values'] are treated safer.
    $data[$key] = 0;
    if (!empty($form_state['input'][$key])) {
      $data[$key] = check_plain($form_state['input'][$key]);
    }
    if (!empty($form_state['values'][$key])) {
      $data[$key] = $form_state['values'][$key];
    }
  }

  if (!empty($data)) {
    // If we have data to store.
    $data_serialized = serialize($data);

    // Checking if this worker is being rated for the first time by this author.
    $workers_data = _get_workers_rating_by_individual($worker, $user->uid);
    
    if (!empty($workers_data->id)) {
      // If we have data stored already, then just updating.
      db_update('worker_feedback_ratings')
        ->fields(array(
          'data' => $data_serialized,
          'created' => REQUEST_TIME,
        ))
        ->condition('uid', $worker)
        ->condition('author', $user->uid)
        ->execute();
      drupal_set_message(t('Ratings updated successfully.'));
    }
    else {
      // If no entry is made, then creating a new entry.
      db_insert('worker_feedback_ratings')
        ->fields(array(
          'uid' => $worker,
          'author' => $user->uid,
          'data' => $data_serialized,
          'created' => REQUEST_TIME,
        ))
        ->execute();
      drupal_set_message(t('Ratings saved successfully.'));
    }
  }
}

/**
 * Menu callback for add-worker-vendor/%ctools_js.
 */
function add_worker_vendor_content($ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Add Worker');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
    );
    $output = ctools_modal_form_wrapper('add_worker_vendor_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('add_worker_vendor_form');
  }
}

/**
 * Form to add a new vendor worker.
 */
function add_worker_vendor_form($form, &$form_state) {
  $options = _get_worker_names_all();
  $form['error_set'] = array(
    '#markup' => '<div id="worker_feedback_page_error"></div>',
  );
  
  $form['worker'] = array(
    '#type' => 'select',
    '#title' => t('Worker Name'),
    '#options' => $options,
    '#select2' => array(
      // 'width' => '300',
      'placeholder' => 'Type names to filter...',
      'allowClear'   => TRUE,
      'minimumResultsForSearch' => '5',
    ),
    '#attributes' => array('class' => array('margin-bottom-10')),
    '#required' => TRUE,
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add Worker'),
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
 * Submit handler for add_worker_vendor_form.
 */
function add_worker_vendor_form_submit($form, &$form_state) {
  // Saving new worker.
  global $user;

  // Although we had already checked that already added users are not shown
  // again in options, but checking here again.
  $added_users = _get_users_added_as_workers();
  $worker = $form_state['values']['worker'];
  $worker_name = _get_user_full_name($worker);

  if (in_array($worker, $added_users)) {
    // Getting worker info. (Author, Created, etc).
    $worker_info = _get_worker_info_by_uid($worker);

    $message = 'User is already added as worker!';
    if (!empty($worker_info)) {
      $author = user_load($worker_info['author']);
      $author_name = _get_user_full_name($author->uid);
      $when = date('m/d/Y', $worker_info['created']);

      // Creating message to show error.
      $message = t('@worker is already added as worker by %author on %when!', array('@worker' => $worker_name, '%author' => $author_name, '%when' => $when));
    }

    $form_state['ajax_commands'][] = ajax_command_html("#worker_feedback_page_error", $message);
  }
  else {
    db_insert('worker_feedback')
      ->fields(array(
        'uid' => $worker,
        'author' => $user->uid,
        'created' => REQUEST_TIME,
      ))
      ->execute();

    // Success. Getting table, and setting status message.
    $form_state['ajax_commands'][] = ajax_command_html("#vwf_status_msg", t('%worker successfully added as worker.', array('%worker' => $worker_name)));
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_worker_feedback_table", _get_vendor_worker_feedback_table());
    $form_state['ajax_commands'][] = ajax_command_invoke('#vwf_status_msg', 'show');
    $form_state['ajax_commands'][] = array('command' => 'destroy_slider_vendor');
    $form_state['ajax_commands'][] = ajax_command_replace('#vendor-worker-feedback-edit-form', render(drupal_get_form('vendor_worker_feedback_edit_form')));
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Menu callback for adding a note in worker feedback.
 */
function add_new_note_worker($uid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Add a note</h4>',
      'uid' => $uid,
    );
    $output = ctools_modal_form_wrapper('add_new_note_worker_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('add_new_note_worker_form');
  }
}

/**
 * Function to show form to add a new note in worker feedback.
 */
function add_new_note_worker_form($form, &$form_state) {
  $form = array();
  $form['note'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    '#rows' => 5,
    '#cols' => 10,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add note'),
  );
  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div></div>',
  );

  return $form;
}

/**
 * Submit handler for add_new_note_worker_form.
 */
function add_new_note_worker_form_submit($form, &$form_state) {
  global $user;

  $uid = $form_state['uid'];
  $vendor_note_counter = variable_get('vendor_note_counter', 1);
  $makeSr = str_pad($vendor_note_counter, 6, "0", STR_PAD_LEFT);
  $note_number = 'NOTE-' . $makeSr . '-' . date('Y');

  $note = $form_state['values']['note'];

  db_insert('worker_feedback_notes')
    ->fields(array(
      'uid' => $uid,
      'author' => $user->uid,
      'note_number' => $note_number,
      'note' => $note,
      'created' => REQUEST_TIME,
    ))
    ->execute();

  $vendor_note_counter++;
  variable_set('vendor_note_counter', $vendor_note_counter);

  $form_state['ajax_commands'][] = ajax_command_html("#vwf_status_msg", t('Note added successfully.'));
  $form_state['ajax_commands'][] = ajax_command_invoke("#vwf_status_msg", 'show');
  $form_state['ajax_commands'][] = ajax_command_html("#notes-table-worker-feedback", _get_worker_notes_table($uid));
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for vendor-manager-messaging/%node/%user/%ctools_js.
 */
function worker_feedback_messaging($account, $ajax = NULL) {
  if (!empty($ajax)) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'account' => $account,
    );

    $output = ctools_modal_form_wrapper('worker_feedback_messaging_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('worker_feedback_messaging_form', $account);
}

/**
 * Function to build form for vendor manager messaging system.
 */
function worker_feedback_messaging_form($form, &$form_state, $account) {
  global $user;

  if (empty($form_state['account'])) {
    $form_state['account'] = !empty($account) ? $account : NULL;
  }

  if (!empty($form_state['account']) && is_object($form_state['account'])) {
    $account = $form_state['account'];
  }

  $form = array();

  $form['main_container'] = array(
    '#type' => 'container',
    '#attributes'=> array('class'=> array('appr-feedback-notes-block','row')),
  );
  $form['main_container']['heading'] = array(
    '#type' => 'markup',
    '#markup'=> '<div class="ins-feed-notes-title col-sm-12"><span class="ins-notes-title clearfix text-center">Vendor Message</span></div>',
  );

  $vm_user_links = array();
  if (!empty($account)) {
    $fullname = _get_user_full_name($account->uid);
    $vm_user_links[] = l($fullname, 'user/' . $account->uid);
  }

  $form['main_container']['left-manager-section'] = array(
    '#type' => 'markup',
    '#markup'=> '<div class="col-md-12 margin-bottom-10"><div class="ins-feed-submitter col-sm-6 padding-0">
      <div class="ins-feed-sub-title"><span class="sub-title">' .implode(',&nbsp;', $vm_user_links) . '</span></div>
      </div>',
  );
  
  $form['main_container']['right-user-section'] = array(
    '#type' => 'markup',
    '#markup'=> '<div class="ins-feed-approver col-sm-6 padding-0">
      <div class="ins-feed-sub-title"><span class="sub-title">' . l(_get_user_full_name($user->uid), 'user/' . $user->uid) . '</span></div>
      </div></div>',
  );

  $form['main_container']['message_container']= array(
    '#type' => 'container',
    '#attributes'=> array('class'=> array('col-sm-12','margin-bottom-10')),
  );

  $form['main_container']['message_container']['message-list'] = array(
    '#markup' => _get_worker_feedback_message_content($user),
    '#prefix' => '<div id="onboarding_company_internal_container">',
    '#suffix' => '</div>',
  );

  $form['main_container']['message_container']['message'] = array(
    '#type' => 'textfield',
    '#title' => 'Message',
    '#title_display' => 'invisible',
    '#attributes' => array('placeholder' => 'Please provide comments', 'id' => 'approval_feedback_message', 'class' => array('approval_feedback_message_msg','bidder_feedback_message_msg', 'onkeypress' => array('if(event.keyCode==13){this.form.submit();}'))),
    '#prefix' => '<div class="bidder_feedback_message_msg_submit">',
    '#maxlength' => 198,
  );

  $form['main_container']['message_container']['add'] = array(
    '#type' => 'submit',
    '#value' => 'Add',
    '#attributes' => array('class' => array('add_new_approval_feedback_message','add_new_bidder_feedback_message')),
    '#executes_submit_callback' => FALSE,
    '#limit_validation_errors' => array(),
    '#href' => '',
    '#ajax' => array(
      'callback' => 'add_new_worker_feedback_message',
      'effect' => 'fade',
      'event' => 'click',
      'progress' => array('type' => 'none'),
    ),
    '#prefix' => '<div id="bidder-feedback-message-button" class="approval_feedback-message-button">',
    '#suffix' => '</div></div>',
  );

  if(isset($form_state['ajax']) && $form_state['ajax']) {
    $form['action-container'] = array(
      '#type' => 'actions',
      '#attributes' => array('class'=> array('pull-right')),
    );
    
    $form['action-container']['cancel-button'] = array(
      '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click();"><input type="button" class="btn cancel-button" value="Close"></a>',
    );
  }

  return $form;
}

/**
 * Submit handler for vendor manager message form.
 */
function add_new_worker_feedback_message($form, &$form_state) {
  global $user, $company;

  $commands = array();
  $output = '';

  $vendor_manager_ids = $form_state['vendor_manager_ids'];

  $account = $form_state['account'];
  if (empty($account)) {
    $account = user_load($user->uid);
  }

  $message = trim($form_state['values']['message']);

  if (!empty($message) && is_object($account)) {
    $user_type = 'user';

    $type = 'worker_feedback';

    // The approach for delivering message (by keeping the main user messaging
    // system in context) is that, we check if a user has a mapping id with the
    // desired receiver. If yes, then using that mapping_id else generating new.
    // Then updating the mapping id in the main user messaging system, and
    // saving messages in the user messaging only, and nowhere else.

    // Getting mapping id for current conversation.
    $mapping_id = _get_mapping_id_service_messaging($type, $user->uid, $account->uid);
    $mapping_id_updated = _update_mapping_id_user_messaging($mapping_id, $user->uid, $account->uid);

    if ($mapping_id_updated) {
      // If the mapping_id is updated in the user messaging table, then
      // proceeding further and sending the message to desired user.
      _send_message_to_user_messaging($mapping_id, $user->uid, $message);
    }

    $output = _get_worker_feedback_message_content($user);
    $commands[] = ajax_command_invoke('.approval_feedback_message_msg','val', array(''));
    $commands[] = ajax_command_html('#onboarding_company_internal_container', $output);
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Helper function to remove worker feedback and its associated content.
 */
function remove_worker_feedback_ajax($account, $ajax = NULL) {
  if (!empty($ajax)) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'account' => $account,
    );

    $output = ctools_modal_form_wrapper('remove_worker_feedback_ajax_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('remove_worker_feedback_ajax_form', $account);
}

/**
 * Form to display for worker feedback removal.
 */
function remove_worker_feedback_ajax_form($form, &$form_state, $account) {
  if (empty($form_state['account'])) {
    if (!empty($account)) {
      $account = $account;
      $form_state['account'] = $account;
    }
  }
  else {
    $account = $form_state['account'];
  }

  $form = array();

  $delete = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to delete worker feedback of @title?', array('@title' => _get_user_full_name($account->uid),)) . '</p></h4>';
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
    '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click();"><input type="button" class="btn cancel-button" value="Close"></a>',
  );

  return $form;
}

/**
 * Submit handler for remove_worker_feedback_ajax_form
 */
function remove_worker_feedback_ajax_form_submit($form, &$form_state) {
  $account = $form_state['account'];

  if (is_object($account)) {
    // First of all getting note ids from notes table, so as to delete the likes
    // for this account.
    $query = db_select('worker_feedback_notes', 'n')
      ->fields('n')
      ->condition('uid', $account->uid)
      ->execute()
      ->fetchAll();

    $notes = array();

    if (!empty($query)) {
      foreach ($query as $key => $value) {
        $notes[] = $value->id;
      }
    }

    // Now deleting the account's content from all tables of worker feedback.

    // Deleting from worker feedback.
    db_delete('worker_feedback')
      ->condition('uid', $account->uid)
      ->execute();

    // Deleting from worker feedback ratings.
    db_delete('worker_feedback_ratings')
      ->condition('uid', $account->uid)
      ->execute();

    if (!empty($notes)) {
      // If there are notes, then only there shall be likes.
      db_delete('worker_feedback_notes')
        ->condition('uid', $account->uid)
        ->execute();

      // Deleting likes.
      db_delete('worker_feedback_likes')
        ->condition('note_id', $notes)
        ->execute();
    }
  }
  $form_state['ajax_commands'][] = ajax_command_html("#vendor_worker_feedback_table", _get_vendor_worker_feedback_table());
  $form_state['ajax_commands'][] = ajax_command_html('#vwf_status_msg', t('Worker Feedback of @title deleted successfully.', array('@title' => _get_user_full_name($account->uid))));
  $form_state['ajax_commands'][] = ajax_command_invoke('#vwf_status_msg', 'show');
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}