<?php

/**
 * Menu callback for thumbs-note/%
 */
function thumbs_up_down_notes($action) {
  if (!empty($_POST['note_id'])) {
    global $user;

    $note_id = $_POST['note_id'];
    $where = 'm6reach';
    $where = !empty($_POST['where']) ? $_POST['where'] : $where; // m6reach or worker_feedback.
    $table = $where . '_likes';

    $fields = array(
      'uid' => $user->uid,
      'note_id' => $note_id,
      'created' => REQUEST_TIME,
    );

    if ($action == 'like') {
      $fields['thumbs_up'] = 1;
      $up_down = 'up';
      $up_down_opp = 'down';
    }
    else {
      $fields['thumbs_down'] = 1;
      $up_down = 'down';
      $up_down_opp = 'up';
    }

    $count = _get_thumbs_count($where, $up_down, $note_id, $user);
    if ($count) {
      // Although we are doing client side validation, that a user does not like
      // already liked note, or dislike. Doing a validation once more here. 
      print 'processed';
      drupal_exit();
    }

    // If a user is liking or disliking, then we need to make sure that we remove
    // the action's opposite entry.
    // For ex - If a user is liking then removing disliking entry, and vice versa.
    db_delete($table)
      ->condition('uid', $user->uid)
      ->condition('note_id', $note_id)
      ->condition('thumbs_' . $up_down_opp, 1)
      ->execute();

    db_insert($table)
      ->fields($fields)
      ->execute();

    $return = array();
    $new_count_up = db_select($table, 'l')
    ->fields('l')
    ->condition('note_id', $note_id)
    ->condition('thumbs_up', 1)
    ->execute()
    ->rowCount();

    $new_count_down = db_select($table, 'l')
    ->fields('l')
    ->condition('note_id', $note_id)
    ->condition('thumbs_down', 1)
    ->execute()
    ->rowCount();

    $return = array(
      'up_count' => $new_count_up,
      'down_count' => $new_count_down,
    );

    // @todo for worker_feedback.
    if ($where == 'm6reach') {
      $return['vendor_data'] = array();
      $vendor_nid = _get_node_id_by_note_id($note_id);
      if ($vendor_nid) {
        $return['vendor_data']['nid'] = $vendor_nid;
        $node = node_load($vendor_nid);
        $new_notes_vendor = _get_notes_for_vendor($node, TRUE);
        if (!empty($new_notes_vendor)) {
          $return['vendor_data']['data'] = $new_notes_vendor;
        }
      }
    }

    if ($where == 'worker_feedback') {
      $return['worker_data'] = array();
      $worker_uid = _get_worker_uid_by_note_id($note_id);
      if ($worker_uid) {
        $return['worker_data']['uid'] = $worker_uid;
        $new_notes_worker = _get_notes_for_worker($worker_uid, TRUE);
        if (!empty($new_notes_worker)) {
          $return['worker_data']['data'] = $new_notes_worker;
        }
      }
    }

    print drupal_json_output($return);
    drupal_exit();
  }
  print 'failed';
  drupal_exit();
}

/**
 * Menu callback for service-message-remove/%/%ctools_js.
 */
function service_message_remove($id, $ajax = NULL) {
  global $user;
  $commands = array();
  if ($ajax) {
    ctools_include('ajax');
    if (empty($id)) {
      // If no ID to delete.
      print ajax_render($commands);
      drupal_exit();
    }

    $deleted = db_select('m6connect_messaging_connect_message', 'm')
      ->fields('m', array('deleted_from'))
      ->condition('id', $id)
      ->execute()
      ->fetchField();

    if (!empty($deleted)) {
      $deleted_users = explode(',', $deleted);
      $deleted_users[] = $user->uid;
      $deleted_users = implode(',', $deleted_users);
    }
    else {
      $deleted_users = $user->uid;
    }

    // Now updating again in DB.
    db_update('m6connect_messaging_connect_message')
      ->fields(array('deleted_from' => $deleted_users))
      ->condition('id', $id)
      ->execute();

    $selector = '.routing-feedback-msg-' . $id;
    $commands[] = array(
      'command' => 'removeMessage',
      'remove_ele' => $selector,
    );
    print ajax_render($commands);
    drupal_exit();
  }
}

/**
 * Menu callback for edit-node/%/%ctools_js
 */
function edit_note_vendor($note_id, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Edit Note</h4>',
      'note_id' => $note_id,
    );
    $output = ctools_modal_form_wrapper('edit_note_vendor_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('edit_note_vendor_form', $note_id);
  }
}

/**
 * Form to show note edit.
 */
function edit_note_vendor_form($form, &$form_state, $note_id) {
  global $user, $company;
  if (empty($form_state['note_id'])) {
    $form_state['note_id'] = !empty($note_id) ? $note_id : '';
  }

  $note_id = $form_state['note_id'];
  $note_data = _get_note_data_by_id($note_id);
  if (empty($note_data)) {
    $no_data = '<div class="group-action-status"><h4><p>' . t('The note you want to edit is not found in our system. Either try again, or contact admin for further assistance.') . '</p></h4></div>';

    $form['note-found'] = array(
      '#type' => 'markup',
      '#markup' => $no_data,
    );
  }
  else {
    // If note is found.
    $form['note'] = array(
      '#type' => 'textarea',
      '#title' => t('Note'),
      '#rows' => 5,
      '#cols' => 10,
      '#required' => TRUE,
      '#default_value' => $note_data->note,
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save note'),
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
 * Submit handler for edit_note_vendor_form
 */
function edit_note_vendor_form_submit($form, &$form_state) {
  if (!empty($form_state['note_id'])) {
    db_update('m6reach_notes')
      ->fields(array(
        'note' => $form_state['values']['note'],
        'created' => REQUEST_TIME,
      ))
      ->condition('id', $form_state['note_id'])
      ->execute();

    $vnode = _get_node_id_by_note_id($form_state['note_id']);
    if (!empty($vnode)) {
      $form_state['ajax_commands'][] = ajax_command_html("#notes-table-vendor", vendor_notes_table($vnode));
    }
  }

  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for remove-note/%/%ctools_js.
 */
function remove_note_vendor($note_id, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Remove Note</h4>',
      'note_id' => $note_id,
    );
    $output = ctools_modal_form_wrapper('remove_note_vendor_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('remove_note_vendor_form', $note_id);
  }
}

/**
 * Form to show to remove note.
 */
function remove_note_vendor_form($form, &$form_state, $note_id) {global $user, $company;
  if (empty($form_state['note_id'])) {
    $form_state['note_id'] = !empty($note_id) ? $note_id : '';
  }

  $note_id = $form_state['note_id'];
  $note_data = _get_note_data_by_id($note_id);
  if (empty($note_data)) {
    $no_data = '<div class="group-action-status"><h4><p>' . t('The note you want to delete is not found in our system. Either try again, or contact admin for further assistance.') . '</p></h4>';

    $form['note-found'] = array(
      '#type' => 'markup',
      '#markup' => $no_data,
    );
  }
  else {
    // If note is found.
    $delete = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to delete the note: %title?', array('%title' => $note_data->note_number)) . '</p></h4>';
    $delete .= '<p>' . t('This action can\'t be undone!') . '</p></div>';

    $form['note-found'] = array(
      '#type' => 'markup',
      '#markup' => $delete,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Confirm'),
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
 * Submit handler for remove_note_vendor_form.
 */
function remove_note_vendor_form_submit($form, &$form_state) {
  if (!empty($form_state['note_id'])) {
    $vnode = _get_node_id_by_note_id($form_state['note_id']);

    db_delete('m6reach_notes')
      ->condition('id', $form_state['note_id'])
      ->execute();

    if (!empty($vnode)) {
      $form_state['ajax_commands'][] = ajax_command_html("#notes-table-vendor", vendor_notes_table($vnode));
    }
  }

  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for request-feedback-company/%/%ctools_js
 */
function request_feedback_company($node, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Request feedback for %title', array('%title' => $node->title));

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
      'node' => $node,
    );
    $output = ctools_modal_form_wrapper('request_feedback_company_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('request_feedback_company_form', $node);
  }
}

/**
 * Form for request feedback from company profile page by company admin.
 */
function request_feedback_company_form($form, &$form_state, $node) {
  // If form is not requested using ctools modal.
  if (empty($form_state['node'])) {
    $form_state['node'] = !empty($node) ? $node : '';
  }

  if (empty($form_state['company_count'])) {
    $unique_identifier = uniqid();
    $form_state['company_count'][] = $unique_identifier;
  }

  if (!empty($form_state['triggering_element']) && !empty($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#type'] == 'select') {
    // If we have company to proceed.
    $company = $form_state['triggering_element']['#value'];
    $company_node = node_load($company);
    if ($company_node) {
      $user_options = _get_user_options_for_request_feedback($company_node);

      // Getting unique id.
      $unique_identifier = NULL;
      if (!empty($form_state['triggering_element']['#parents'][1])) {
        $unique_identifier = $form_state['triggering_element']['#parents'][1];
      }

      if (empty($unique_identifier)) {
        // If unique identifier not found, then searching once again.
        if (!empty($form_state['triggering_element']['#array_parents'][1])) {
          $unique_identifier = $form_state['triggering_element']['#array_parents'][1];
        }
      }

      if (!empty($unique_identifier)) {
        $form_state['employee_options'][$unique_identifier] = $user_options;
      }
    }
  }

  $form['error_set'] = array(
    '#markup' => '<div id="vendor_page_error"></div>',
  );

  $form['container-div'] = array(
    '#markup' => '<div id="replace-container-here">',
  );

  $form['company-main-container'] = array(
    '#type' => 'container',
    '#attributes'=> array('class'=> array('row',)),
    '#prefix' => '<div id="company-main-container">',
    '#suffix' => '</div><br>',
    '#process' => array('company_main_container_process'),
    '#theme' => 'company_container_theme',
  );

  $form['container-close-div'] = array(
    '#markup' => '</div>',
  );

  $form['or_mark'] = array(
    '#type' => 'markup',
    '#markup' => '<div><strong>OR</strong></div>',
  );

  $form['invite_to_m6'] = array(
    '#type' => 'textfield',
    '#title' => 'Invite to M6 by E-mail',
    '#attributes' => array('class'=> array('form-control invite_to_m6'),'type'=> array('email')),
    '#prefix' => '<div class="clearfix form-item invite-m6">',  
    '#element_validate' => array('project_ecommitment_email_validate'),
    '#suffix' => '</div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Request Feedback'),
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
 * Process handler for request_feedback_company_form.
 */
function company_main_container_process($element, &$form_state) {
  $items = $form_state['company_count'];
  $options = _get_company_names();

  $element['#comp_items'] = $items;

  foreach ($items as $item) {
    $element['company'][$item] = array(
      '#type' => 'select',
      '#title' => t('Company Name'),
      '#title_display' => 'invisible',
      '#options' => $options,
      '#select2' => array(
        'width' => '250',
        'placeholder' => 'Type names to filter...',
        'allowClear'   => TRUE,
        'minimumResultsForSearch' => '5',
      ),
      '#attributes' => array('class' => array('margin-bottom-10')),
      '#ajax' => array(
        'callback' => '_get_company_employee',
        'wrapper' => 'company-main-container',
      ),
      '#prefix' => '<div class="clearfix pull-left">',
      '#suffix' => '</div>',
      '#parents' => array('companies',$item,'company'),
    );
    $element['employee'][$item] = array(
      '#type' => 'select',
      '#title' => t('Employee'),
      '#options' => !empty($form_state['employee_options'][$item]) ? $form_state['employee_options'][$item] : array(),
      '#title_display' => 'invisible',
      '#multiple' => TRUE,
      '#select2' => array(
        'width' => '250',
        'placeholder' => 'Type names to filter...',
        'allowClear'   => TRUE,
        'minimumResultsForSearch' => '5',
      ),
      '#attributes' => array('class' => array('margin-bottom-10')),
      '#prefix' => '<div class="clearfix pull-right">',
      '#suffix' => '</div>',
      '#parents' => array('companies',$item,'employee'),
    );
  }

  $element['add_new_company'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    "#limit_validation_errors" => array(),
    '#submit'=> array('add_new_company_sub'),
    '#ajax' => array(
      'callback' => 'add_new_company_callback',
      'wrapper' => 'company-main-container',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#attributes' => array('class' => array('margin-bottom-10')),
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );

  return $element;
}

/**
 * Ajax callback for getting new row.
 */
function add_new_company_callback($form, &$form_state) {
  return $form['company-main-container'];
}

/**
 * Submit callback for getting new row.
 */
function add_new_company_sub($form, &$form_state) {
  $unique_identifier = uniqid();
  $form_state['company_count'][] = $unique_identifier;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for getting company employee.
 */
function _get_company_employee($form, &$form_state) {
  $form_state['employee_options'] = array();
  $form_state['rebuild'] = TRUE;
  $commands = array();
  $commands[] = ajax_command_html('#replace-container-here', render($form['company-main-container']));
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Theme process for company-main-container
 */
function theme_company_container_theme($variables) {
  $element = $variables['form'];
  $comp_items = $element['#comp_items'];

  $output = '';
  $output .= '<div class="company-container-theme-output">';
  $output .= '<label class="company-title-header">' . t('Company') . '</label>';
  $output .= '<label class="employee-title-header">' . t('Employee') . '</label>';
  foreach ($comp_items as $item) {
    $output .= '<div class="company-container-theme-item clearfix">';
    $output .= render($element['company'][$item]);
    $output .= render($element['employee'][$item]);
    $output .= '</div>';
  }

  $output .= '<div class="company-container-theme-add-new">';
  $output .= render($element['add_new_company']);
  $output .= '</div>';
  $output .= '</div>';
  $output .= drupal_render_children($element);
  return $output;
}
/**
 * Submit handler for request_feedback_company_form.
 */
function request_feedback_company_form_submit($form, &$form_state) {
  // Getting the list of companies to invited.
  $companies_invited = $form_state['values']['companies'];
  $invite_by_mail = $form_state['values']['invite_to_m6'];

  // Current user and company.
  global $user, $company, $base_url;
  $user_name = _get_user_full_name($user->uid);

  // Getting list of all users who have rated for the current company.
  $already_rated_users = _get_rated_invited_users($company, NULL, 1);
  $already_invited_users = _get_rated_invited_users($company, NULL, 0);

  $query_data = array(
    'vendor' => 'default',
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
  $message .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connet') . '</strong><br/>(' . $mailto . ')';

  $query_data = array(
    'vendor' => 'default',
    'cnid' => $company->nid,
  );
  $link = url('user/register', array('query' => $query_data, 'absolute' => TRUE,));
  $click_link = t('<a href="@link">Click here</a>', array('@link' => $link,));

  $message2 = 'Hello,<br/>';
  $message2 .= $user_name . ' has requested you to provide feedback for his company (' . ucwords($company->title) . ').<br/>';
  $message2 .= 'To provide feedback, please click on the link below.<br/><br/>';
  $message2 .= $click_link . '<br/><br/>';
  $message2 .= '<p>If the link is not clickable then copy paste this URL in the browser.<br/>';
  $message2 .= '<p>' . $link . '<p><br/><br/>';
  $message2 .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connet') . '</strong><br/>(' . $mailto . ')';

  $params = array(
    'subject' => 'Request to rate company on ' . variable_get('site_name', 'M6Connet'),
    'body' => $message,
    'sender' => $user->mail,
    'language' => language_default(),
    'module' => 'm6connect_misc',
    'key' => 'commitment_mail___invite_2_m6_notify',
    'build' => TRUE,
  );

  $update_table_data = array();
  if (!empty($companies_invited)) {
    // If the request is submitted to just invite companies.
    // Here we are just sending the invitation to the company admin of the
    // requested company.
    $remind_users = array();
    foreach ($companies_invited as $company_invited) {
      $company_users = array();
      if (!empty($company_invited['employee'])) {
        $company_users = $company_invited['employee'];
      }
      //$company_admins = _get_company_users_by_og_roles_with_status($company_invited, 'company admin', 1);
      // There may be more than one company admin for a company.
      // Sending mail to every admin of the company.
      foreach ($company_users as $key => $value) {
        // Sending mail to each user.
        if (in_array($value, $already_rated_users)) {
          // If this user has already rated then skipping.
          continue;
        }
        if (in_array($value, $already_invited_users)) {
          // If this user has been already invited but has not rated yet.
          // then reminding the user again, and skipping.
          $remind_users[] = $value;
          continue;
        }
        $account = user_load($value);
        $update_table_data[] = $value;
        drupal_mail($params['module'], $params['key'], $account->mail, $params['language'], $params);

        // Sending notification to the user.
        $m6connect_notification = array (
          'type' => 'company_admin_request',
          'event' => 'feedback',
          'entity_id' => $company->nid,
          'company_nid' => 0,
          'message' => 'vendor',
          'request_from' => $user->uid,
          'request_to' => $account->uid,
          'status' => 1,
          'timestamp' => REQUEST_TIME,
        );
        entity_save('m6connect_notification', (object)$m6connect_notification);
      }
    }
    $message = t('Email successfully sent to employees for the requested companies.');
    if (empty($update_table_data) && empty($remind_users)) {
      $message = t('No eligible users found for the given companies.');
    }
    elseif (empty($update_table_data) && !empty($remind_users)) {
      $message = t('Selected users were already requested to provide feedback, reminder email and notifications sent.');
    }
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_status_msg", $message);
    $form_state['ajax_commands'][] = ajax_command_invoke('#vendor_status_msg', 'show');
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  if (!empty($invite_by_mail)) {
    $invite_by_mail = trim($invite_by_mail); // Removing white spaces.
    $params['body'] = $message2; // Changing the body for the outside user.
    drupal_mail($params['module'], $params['key'], $invite_by_mail, $params['language'], $params);
    $update_table_data[] = $invite_by_mail;

    $form_state['ajax_commands'][] = ajax_command_html("#vendor_status_msg", t('Email successfully sent to %mail requesting feedback.', array('%mail' => $invite_by_mail)));
    $form_state['ajax_commands'][] = ajax_command_invoke('#vendor_status_msg', 'show');
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  if (empty($companies_invited) && empty($invite_by_mail)) {
    // Else showing error!
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_page_error", '<div class="messages--error messages error"><h2 class="element-invisible">Error message</h2>Please fill either Company or Email field!</div>');
    $form_state['ajax_commands'][] = ajax_command_invoke('#vendor_page_error', 'show');
  }

  if (!empty($update_table_data)) {
    // If we have send invitations then updating invites in table.
    _update_m6reach_company_invites_data($update_table_data);
  }

  if (!empty($remind_users)) {
    // If we have some users to remind about, then reminding again.
    _remind_m6reach_invitation_again($remind_users);
  }
}

/**
 * Menu callback for add-note/%/nojs.
 */
function add_new_note_vendor($cnid = 0, $vnid = 0, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Add a note</h4>',
      'cnid' => $cnid,
      'vnid' => $vnid,
    );
    $output = ctools_modal_form_wrapper('add_new_note_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('add_new_note_form');
  }
}

/**
 * Form to add a new note for vendor.
 */
function add_new_note_form($form, &$form_state) {
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
 * Submit handler for the form add_new_note_form.
 */
function add_new_note_form_submit($form, &$form_state) {
  global $user;

  $vnid = !empty($form_state['vnid']) ? $form_state['vnid'] : 0;
  $cnid = !empty($form_state['cnid']) ? $form_state['cnid'] : 0;

  $vendor_note_counter = variable_get('vendor_note_counter', 1);
  $makeSr = str_pad($vendor_note_counter, 6, "0", STR_PAD_LEFT);
  $note_number = 'NOTE-' . $makeSr . '-' . date('Y');

  $note = $form_state['values']['note'];

  if (!empty($cnid)) {
    // If we have a company nid then only we proceed with data insertion.
    $message = t('Note added successfully.');
    $approved = 1;
    if (empty($vnid)) {
      // If we do not have a vendor nid, then we need to check if the current
      // user was requested to rate or not. If not, then we can not mark it
      // approved untill company admin approves this note.

      // First checking whether the user was invited.
      // $query = db_select('m6reach_company_invites', 'ci')
      //   ->fields('ci')
      //   ->condition(db_or()->condition('uid', $user->uid)->condition('email', $user->mail))
      //   ->condition('company', $cnid)
      //   ->execute()
      //   ->rowCount();
      // if ($query == 0) {
      //   // If user was not invited.
      //   $approved = 0;
      // } Functionality removed wef 15th May.
    }
    $note_id = db_insert('m6reach_notes')
      ->fields(array(
        'uid' => $user->uid,
        'cnid' => $cnid,
        'vnid' => $vnid,
        'note_number' => $note_number,
        'note' => $note,
        'created' => REQUEST_TIME,
        'approved' => $approved,
      ))
      ->execute();

    // if ($approved == 0 && $note_id) {
    //   // If the user is not invited, then this note will be saved as unapproved.
    //   // So sending a notification and email to company admin, that a user has
    //   // made a note, so that admin can review, and approve/disapprove it.
    //   _send_unapproved_notification_mail('note', $cnid, $note_id);
    //   $message = t('Note added successfully and has been sent for review. Once approved, it shall be visible in the notes table.');
    // }
    // else {
      _send_ratings_notes_notification('notes', $cnid, $vnid, $note_id);
    // }

    $vendor_note_counter++;
    variable_set('vendor_note_counter', $vendor_note_counter);

    $form_state['ajax_commands'][] = ajax_command_html("#vendor_status_msg", $message);
    $form_state['ajax_commands'][] = ajax_command_invoke("#vendor_status_msg", 'show');
    $form_state['ajax_commands'][] = ajax_command_html("#notes-table-vendor", vendor_notes_table($cnid, $vnid));
  }
  else {
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_error_msg", t('Note could not be added due to some problem. Please try again later or contact admin.'));
    $form_state['ajax_commands'][] = ajax_command_invoke("#vendor_error_msg", 'show');
  }

  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for approve-m6reach/%node/%/%/%ctools_js
 */
function approve_m6reach_ratings_notes($type = NULL, $node = NULL, $item_id = NULL, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Approve ' . ucwords($type) . '</h4>',
      'type' => $type,
      'item_id' => $item_id,
      'node' => $node,
    );
    $output = ctools_modal_form_wrapper('approve_m6reach_ratings_notes_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('approve_m6reach_ratings_notes_form', $node, $type, $item_id);
  }
}

/**
 * Function to generate form for approve ratings/notes.
 */
function approve_m6reach_ratings_notes_form($form, &$form_state, $node = NULL, $type = NULL, $item_id = NULL) {
  if (empty($form_state['type'])) {
    $form_state['type'] = !empty($type) ? $type : NULL;
  }
  if (empty($form_state['item_id'])) {
    $form_state['item_id'] = !empty($item_id) ? $item_id : NULL;
  }
  if (empty($form_state['node'])) {
    $form_state['node'] = !empty($node) ? $node : NULL;
  }

  $form_state['action'] = 'approve';

  $approve = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to approve this %type?', array('%type' => substr(ucwords($form_state['type']), 0, -1))) . '</p></h4>';
  $approve .= '<p>' . t('This action can\'t be undone!') . '</p></div>';

  $form['warnign'] = array(
    '#type' => 'markup',
    '#markup' => $approve,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Approve'),
    '#submit' => array('approve_delete_m6reach_notes_ratings'),
  );

  if ($form_state['ajax']) {
    $form['close'] = array(
    '#type' => 'markup',
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div>',
  );
  }

  return $form;
}

/**
 * Menu callback for delete-m6reach/%node/%/%/%ctools_js
 */
function delete_m6reach_ratings_notes($type = NULL, $node = NULL, $item_id = NULL, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">Deny ' . ucwords($type) . '</h4>',
      'type' => $type,
      'item_id' => $item_id,
      'node' => $node,
    );
    $output = ctools_modal_form_wrapper('delete_m6reach_ratings_notes_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('delete_m6reach_ratings_notes_form', $node, $type, $item_id);
  }
}

/**
 * Function to generate form for delete ratings/notes.
 */
function delete_m6reach_ratings_notes_form($form, &$form_state, $node = NULL, $type = NULL, $item_id = NULL) {
  if (empty($form_state['type'])) {
    $form_state['type'] = !empty($type) ? $type : NULL;
  }
  if (empty($form_state['item_id'])) {
    $form_state['item_id'] = !empty($item_id) ? $item_id : NULL;
  }
  if (empty($form_state['node'])) {
    $form_state['node'] = !empty($node) ? $node : NULL;
  }

  $form_state['action'] = 'delete';

  $delete = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to deny this %type?', array('%type' => substr(ucwords($form_state['type']), 0, -1))) . '</p></h4>';
  $delete .= '<p>' . t('This action can\'t be undone!') . '</p></div>';

  $form['warnign'] = array(
    '#type' => 'markup',
    '#markup' => $delete,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm'),
    '#submit' => array('approve_delete_m6reach_notes_ratings'),
  );

  if ($form_state['ajax']) {
    $form['close'] = array(
    '#type' => 'markup',
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div>',
  );
  }

  return $form;
}

/**
 * Submit handler for approve/delete m6reach ratings/notes.
 */
function approve_delete_m6reach_notes_ratings($form, &$form_state) {
  $action = $form_state['action'];
  $type = $form_state['type'];
  $item_id = $form_state['item_id'];
  $node = $form_state['node'];

  $st_msg = t('Could not perform requested operation due to some problem. Please contact site admin.');
  if (!empty($action) && !empty($type) && !empty($item_id) && !empty($node)) {
    // If we have enough data to proceed.

    // Getting table in which actions are to be performed.
    $table = $type == 'ratings' ? 'm6reach_ratings' : 'm6reach_notes';

    // Getting update table function name.
    $update_table_func = $type == 'ratings' ? '_get_pending_ratings' : '_get_pending_notes';

    // In either case, we need uid, cnid, and vnid of the item, so as to
    // update the notification table.
    $query = db_select($table, 'd');
    $query->fields('d', array('uid', 'cnid', 'vnid'));
    $query->condition('id', $item_id);
    $data = $query->execute()->fetchObject();

    if ($action == 'approve') {
      // If we need to approve ratings or notes.
      $approved = 1;
    }
    if ($action == 'delete') {
      // If we are to disapprove ratings or notes.
      $approved = 2;
    }

    // Updating records.
    db_update($table)
      ->fields(array('approved' => $approved))
      ->condition('id', $item_id)
      ->execute();

    // We also need to clear the notifications sent for approving notes|ratings.
    _clear_ratings_notes_approve_notifications($type, $data);

    $form_state['ajax_commands'][] = ajax_command_html("#approved-listing-table-" . strtolower($type), $update_table_func($node, 1));
    $form_state['ajax_commands'][] = ajax_command_html("#denied-listing-table-" . strtolower($type), $update_table_func($node, 2));
    $form_state['ajax_commands'][] = ajax_command_html("#waiting-listing-table-" . strtolower($type), $update_table_func($node, 0));

    // Preparing status message.
    $st_msg = t('!type %action successfully.', array('!type' => $type, '%action' => $action == 'approve' ? 'approved' : 'deleted'));
  }

  if ($form_state['ajax']) {
    $form_state['ajax_commands'][] = ajax_command_html("#vendor_status_msg", $st_msg);
    $form_state['ajax_commands'][] = ajax_command_invoke("#vendor_status_msg", 'show');

    // Trying to update notifications.
    $form_state['ajax_commands'][] = ajax_command_html('#block-m6connect-common-toprightheaderblock .content', right_m6topheaderblock());

    // Dismissing modal
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  else {
    drupal_set_message($st_msg, 'status');
  }
}

/**
 * Menu callback for 
 */
function become_vendor_company($node, $company_node, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Become a Vendor for %title', array('%title' => $node->title));

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
      'node' => $node,
      'company_node' => $company_node,
    );

    $output = ctools_modal_form_wrapper('become_vendor_company_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('become_vendor_company_form', $node, $company_node);
  }
}

/**
 * Function to get form to become a company vendor.
 */
function become_vendor_company_form($form, &$form_state, $node = NULL, $company_node = NULL) {
  // Trying to initiate storage array.
  if (empty($form_state['contact_email_storage'])) {
    $form_state['contact_email_storage'] = array();
    $form_state['contact_email_storage'][] = uniqid();
  }
  $node = !empty($node) ? $node : (!empty($form_state['node']) ? $form_state['node'] : NULL);

  // Adding JS
  drupal_add_js(drupal_get_path('module', 'm6connect_vendor') . '/js/company_page.js');

  $form['status_msg'] = array(
    '#type'   => 'markup',
    '#markup' => '<div id="vendor_common_status_msg" class="messages--status messages status" style="display:none;"></div>
      <div id   ="vendor_common_error_msg" class="messages--error messages error" style="display:none;"></div>',
  );

  $form['contact-email-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('contact-email-container')),
    '#process' => array('contact_email_container_process'),
    '#prefix' => '<div id="contact-email-section" class="form-inline form-inline-become-vendor margin-bottom-45"><label>' . t('Who would you like to receive your request?') . '</label>',
    '#suffix' => '</div>',
  );

  $form['contact_email_attachments'] = array(
    '#type' => 'file',
    '#title' => t('Attach Company Literature'),
    '#name' => 'files[]',
    '#upload_location' => 'public://',
    '#description' => t('Use CTRL + Click to choose multiple attachments.'),
    '#attributes' => array('multiple' => 'multiple'),
    '#prefix' => '<div class="clearfix form-item">',
    '#suffix' => '</div>',
  );

  $form['area_of_work'] = array(
    '#type' => 'select',
    '#title' => t('Select Region of Work'),
    '#options' => _get_area_of_work_options($node),
    // '#required' => TRUE,
  );

  $form['department'] = array(
    '#type' => 'select',
    '#title' => t('Select Department'),
    '#options' => _get_department_options($node),
    // '#required' => TRUE,
  );

  $form['special_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Special Message'),
    '#attributes' => array('placeholder' => t('Describe the type of work your company is interested in.')),
    '#rows' => '3',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send Request'),
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
 * Process function for become_vendor_company_form
 */
function contact_email_container_process($element, &$form_state) {
  $storage = $form_state['contact_email_storage'];
  $element['#storage'] = $storage;

  $i = 1;

  foreach ($storage as $uniqid) {
    $element['container-' . $uniqid] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-inline')),
    );
    $element['container-' . $uniqid]['first_name'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('First Name'),
      '#required' => $i == 1,
      '#title_display' => 'invisible',
      '#attributes' => array('placeholder' => $i == 1 ? t('First Name (Required)') : t('First Name (Optional)'), 'class' => array('contact-email-first-name-text')),
      '#parents' => array('email_contact', $uniqid, 'first_name'),
    );
    $element['container-' . $uniqid]['last_name'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('Last Name'),
      '#required' => $i == 1,
      '#title_display' => 'invisible',
      '#attributes' => array('placeholder' => $i == 1 ? t('Last Name (Required)') : t('Last Name (Optional)'), 'class' => array('contact-email-last-name-text')),
      '#parents' => array('email_contact', $uniqid, 'last_name'),
    );
    $element['container-' . $uniqid]['email'][$uniqid] = array(
      '#type' => 'textfield',
      '#title' => t('Email'),
      '#required' => $i == 1,
      '#title_display' => 'invisible',
      '#element_validate' => array('project_ecommitment_email_validate'),
      '#attributes' => array('placeholder' => $i == 1 ? t('Email (Required)') : t('Email (Optional)'), 'class' => array('contact-email-email-text')),
      '#parents' => array('email_contact', $uniqid, 'email'),
    );
    $i++;
  }

  $element['contact_email_add_new_row'] = array(
    '#type' => 'submit',
    '#value' => 'Add New',
    '#name' => 'contact_email_add_new_row',
    '#limit_validation_errors' => array(),
    '#submit'=> array('contact_email_add_new_submit'),
    '#attributes' => array('class' => array('contact-email-add-new-custom')),
    '#ajax' => array(
      'callback' => 'contact_email_add_new_callback_ajax',
      'wrapper' => 'contact-email-section',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );

  return $element;
}

/**
 * Submit handler for adding new row contact email
 */
function contact_email_add_new_submit($form, &$form_state) {
  if (count($form_state['contact_email_storage']) < 3) {
    $form_state['contact_email_storage'][] = uniqid();
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax handler for adding new row contact email
 */
function contact_email_add_new_callback_ajax($form, &$form_state) {
  return $form['contact-email-container'];
}

/**
 * Submit handler for become_vendor_company_form
 */
function become_vendor_company_form_submit($form, &$form_state) {
  global $user;
  $org_node = $form_state['node'];
  $company_node = $form_state['company_node'];

  // Adding files in form_state.
  if (!empty($_FILES['files']['name'])) {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
      $file = file_save_upload($i, array(
        'file_validate_extensions' => array(
          'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'
        )
      ));
      if ($file) {
        if ($file = file_move($file, 'private://')) {
          $form_state['values']['contact_email_attachments'][$i] = $file;
        }
      }
    }
  }

  // We shall be saving the vendor manager/company admin of current_node as one
  // of the creators of this node, so as to easy the filteration while
  // displaying the vendors to its vendor managers.
  // Trying to get vendor manager first, if no vendor managers available, then
  // getting company admin, and in case, no admin is available, then getting
  // list of users, and taking any one randomly.
  // And saving the current user in requestor field in vendor node, for future
  // references.

  // First getting vendor manager.
  $author = $user->uid;
  $vendor_managers = _get_company_users_by_og_roles_with_status($org_node->nid, 'Vendor Manager', 1);

  if (!empty($vendor_managers[0]) && is_numeric($vendor_managers[0])) {
    $author = $vendor_managers[0];
  }
  else {
    // If vendor manager is not available, then getting company admin.
    $company_admins = _get_company_users_by_og_roles_with_status($org_node->nid, 'company admin', 1);
    if (!empty($company_admins[0]) && is_numeric($company_admins[0])) {
      $author = $company_admins[0];
    }
    else {
      // If none of the vendor manager or company admin is available, then
      // getting any random user of the company.
      $company_users = _get_user_mappping_by_group_company_nid($org_node->nid);
      if (!empty($company_users)) {
        $company_users = array_keys($company_users);
        if (!empty($company_users[0]) && is_numeric($company_users[0])) {
          $author = $company_users[0];
        }
      }
    }
  }

  // Getting vendor number.
  $vendor_counter = variable_get('vendor_counter', 1);
  $makeSr = sprintf('%08d', $vendor_counter);
  $vendor_number = $makeSr . '-' . date('Y');

  // Trying to create a new node.
  // Basics.
  $node = new stdClass();
  $node->type = 'vendor';
  $node->title = $vendor_number;
  $node->uid = $author;
  // Untill vendor is approved, it is unpublished.
  $node->status = 0;

  // Saving special message.
  $node->body[LANGUAGE_NONE][0]['value'] = $form_state['values']['special_message'];

  // Saving other fields.
  $node->field_m6number[LANGUAGE_NONE][0]['value'] = $vendor_number;
  $node->field_vendor_status[LANGUAGE_NONE][0]['value'] = 'pending_-_invited';
  $node->field_vendor_type[LANGUAGE_NONE][0]['value'] = 'm6reach';

  // Saving contact details.
  $user_data = array();
  if (!empty($form_state['values']['email_contact'])) {
    foreach ($form_state['values']['email_contact'] as $uniqid => $data) {
      $user_data[] = array(
        'first_name' => $data['first_name'],
        'last_name'  => $data['last_name'],
        'email'      => $data['email'],
      );
    }
  }
  if (!empty($user_data)) {
    $node->field_primary_contacts_email[LANGUAGE_NONE][0]['value'] = serialize($user_data);
  }

  // Saving attachments.
  if (!empty($form_state['values']['contact_email_attachments'])) {
    foreach ($form_state['values']['contact_email_attachments'] as $key => $file) {
      $new_file = file_load($file->fid);
      $file_arr = (array)$new_file;
      $file_arr['display'] = 1;
      $node->field_attachments[LANGUAGE_NONE][$key] = $file_arr;
    }
  }

  // Saving the requestor.
  $node->field_requestor[LANGUAGE_NONE][0]['value'] = $user->uid;

  // Some essential data.
  $node->og_group_ref[LANGUAGE_NONE][0]['target_id'] = $company_node->nid;

  // Saving area of work, and department.
  if (!empty($form_state['values']['area_of_work'])) {
    $node->field_regions[LANGUAGE_NONE][0]['tid'] = $form_state['values']['area_of_work'];
  }

  // Saving the node finally.
  node_save($node);

  if ($node->nid) {
    // If new vendor node is saved.
    $vendor_counter++;
    variable_set('vendor_counter', $vendor_counter);
    $form_state['ajax_commands'][] = ajax_command_html('#vendor_status_msg', t('Request sent to @title successfully.', array('@title' => $org_node->title)));
    $form_state['ajax_commands'][] = ajax_command_invoke('#vendor_status_msg', 'show');
  }
  else {
    $form_state['ajax_commands'][] = ajax_command_html('#vendor_error_msg', t('Request could not be sent, please contact admin for more information.'));
    $form_state['ajax_commands'][] = ajax_command_invoke('#vendor_error_msg', 'show');
  }

  // Closing the form.
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for 
 * 1. acknowledge-vendor/%node/%node/%ctools_js
 * 2. request-info-vendor/%node/%node/%ctools_js
 */
function acknowledge_vendor_request_additional_info_vendor($og_node = NULL, $vendor_node = NULL, $ajax = NULL, $form_type = NULL) {
  $form_function = $form_type . '_form';
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    // $title = $form_type == 'acknowledge_vendor' ? t('Acknowledge Receipt for %title', array('%title' => $og_node->title)) : t('Request Additional Info for %title', array('%title' => $og_node->title));

    // $form_state = array(
    //   'ajax' => TRUE,
    //   'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
    //   'og_node' => $og_node,
    //   'vendor_node' => $vendor_node,
    // );

    // $output = ctools_modal_form_wrapper($form_function, $form_state);

    // if (!empty($form_state['ajax_commands'])) {
    //   $output = $form_state['ajax_commands'];
    // }

    // print ajax_render($output);
    // drupal_exit();

    // Before we were showing this form in modal, but now showing on page itself.
    // Functionality changed - May 24.

    // Including m6reach inc file.
    module_load_include('inc', 'm6connect_vendor', '/includes/m6reach');

    // Showing ratings form also, but with m6rank only.
    $ratings_form = drupal_get_form('vendor_m6reach_edit_form', 'm6reach', 'preferred');

    $form = drupal_get_form('vendor_manager_messaging_form', $og_node, $vendor_node, $form_type);
    $commands = array();
    // $commands[] = ajax_command_html("#company-markup-for-messaging-div", _get_company_markup($og_node));
    $commands[] = ajax_command_html('#form-for-messaging-div', render($form));
    $commands[] = ajax_command_html('#notes-table-vendor', vendor_notes_table($og_node, $vendor_node));
    // $commands[] = ajax_command_invoke("#company-markup-for-messaging-div", 'show', array(500));
    $commands[] = ajax_command_invoke("#form-for-messaging-div", 'show');
    print ajax_render($commands);
    drupal_exit();
  }
  else {
    return drupal_get_form($form_function, $og_node, $vendor_node);
  }
}

/**
 * Form to return function for acknowledge vendor.
 */
/*function acknowledge_vendor_form($form, &$form_state, $og_node = NULL, $vendor_node = NULL) {
  $form['intro'] = array(
    '#markup' => t('Hi'),
  );

  return $form;
}

*
 * Form to return function for requesting additional information for vendor.
 
function request_additional_info_vendor_form($form, &$form_state, $og_node = NULL, $vendor_node = NULL) {
  $form['intro'] = array(
    '#markup' => t('Hi'),
  );

  return $form;
}*/

/**
 * Menu callback for inserting message in VM Chat.
 */
function vendor_insert_message_ajax() {
  $values = array();
  $insert = array();
  $files = array();

  // Getting the values from the submitted form.
  $values = $_POST;
  $files = $_FILES;

  if (!empty($values) && !empty($files)) {
    global $user;
    // If we have values to proceed.
    $company_nid = !empty($values['company_node_ms']) ? $values['company_node_ms'] : NULL;
    $vendor_uid = !empty($values['vendor_cuser_ms']) ? $values['vendor_cuser_ms'] : NULL;
    $vendor_nid = !empty($values['vendor_nid_ms']) ? $values['vendor_nid_ms'] : NULL;
    $message = !empty($values['message']) ? $values['message'] : NULL;

    $last_insert_id = NULL;

    if (!empty($company_nid) && !empty($vendor_uid) && !empty($vendor_nid)) {
      // If we have all the values.

      $type = 'm6reach'; // Always for now.

      $userimg = _get_message_user_image($vendor_uid);
      $username = _get_user_full_name($vendor_uid);
      $output = '';

      // Getting company admins.
      $company_admins = _get_company_users_by_og_roles_with_status($company_nid, 'company admin', 1);

      // Filtering out, current user, if any.
      $company_admins = array_diff($company_admins, array($user->uid));

      // Trying to send message to all the company admins.
      // If the user is not company admin, then user is sending the message
      // to company admins. So we need to send the message to every company
      // admin.

      // The approach for delivering message (by keeping the main user messaging
      // system in context) is that, we check if a user has a mapping id with
      // the desired company admins and for respective vendor node. If yes, then
      // using that mapping_id else generating new.
      // Then updating the mapping id in the main user messaging system, and
      // saving messages in the user messaging only, and nowhere else.
      // PS = If message is to be sent to more than 1 company admin, then
      // mapping type used is group, user otherwise.

      // Getting mapping id for each user.
      $mapping_id = _get_mapping_id_service_messaging($type, $vendor_uid, $company_admins, $vendor_nid);

      // Updating mapping id in user messaging tables, if not updated.
      $mapping_id_updated = _update_mapping_id_user_messaging($mapping_id, $vendor_uid, $company_admins);

      if ($mapping_id_updated) {
        // If the mapping_id is updated in the user messaging table, then
        // proceeding further and sending the message to desired user.
        if (!empty($message)) {
          $message_sent = TRUE;
          $last_insert_id = _send_message_to_user_messaging($mapping_id, $vendor_uid, $message);
        }
      }

      if (!empty($last_insert_id)) {
        $output .= '<div class="bidder-feedback-msg routing-feedback-msg-' . $last_insert_id . ' clearfix feedback-msg-writer" id="' . $last_insert_id . '">';
        $output .= '<div class="bidder-feedback-msg-attr pull-left">';

        $output .= '<span class="bidder-feedback-msg-time"><span class="msg-aut-img">' . $userimg . '</span></span>';
        $output .= '<span class="bidder-feedback-msg-msg"><strong>' . $username . '</strong> - </span><span class="bidder-feedback-msg-content">' . $message . '</span><p class="message-post-time text-right clearfix">' . date('h:i A', REQUEST_TIME) . '</p>';
        $output .= '</div>';

        $output .= '<div class="bidder-feedback-msg-delete">';
        $output .= l('<i class="fa fa-times-circle"></i>', 'service-message-remove/' . $last_insert_id . '/nojs', array('html' => TRUE, 'attributes' => array('class' => array('bidder-feedback-msg-delete-link', 'use-ajax'))));
        $output .= '</div>';
        $output .= '</div>';
      }

      if (!empty($files['files']['name'][0])) {
        // If we have any attachment to save.
        $file = file_save_upload('0', array(
          'file_validate_extensions' => array(
            'jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls rar zip'
          )
        ));
        if ($file) {
          // If file is moved to temp directory, then moving to Amazon S3.
          if ($file_new = file_move($file, 'private://')) {
            // If moved successfully, then saving the fid.
            $fid = $file_new->fid;
            $last_insert_id_attachment = _send_message_to_user_messaging($mapping_id, $vendor_uid, NULL, $fid);

            if (!empty($last_insert_id_attachment)) {
              // If a message is sent to more then 1 users, then also we need the
              // last insert id, and when the compiler comes out of foreach loop
              // we shall have the id of the message sent last.

              // Defined in m6_drive module.
              // $filename = $file_new->filename;
              // $file_url = file_create_url($file_new->uri);
              // $fileicondrive = _get_file_icon_m6drive($file_new->filemime, TRUE);
              // if($fileicondrive) {
              //   $message_img_html = $fileicondrive;
              // }
              // else {
              //   $img_url = image_style_url('pic_40x40', $file_new->uri);
              //   $message_img_html = '<img src="' . $img_url . '" />';
              // }
              // $message_img_html = '<a href="' . $file_url . '">' . $message_img_html . '</a>';
              // $message_img_html = $filename . $message_img_html;
              $message_img_html = get_m6message_attachment_box($file_new->fid, $file_new->uri, $file_new->filename, $file_new->filemime);
              // $result['message'] = $message_img_html;

              $output .= '<div class="bidder-feedback-msg routing-feedback-msg-' . $last_insert_id_attachment . ' clearfix feedback-msg-writer" id="' . $last_insert_id_attachment . '">';
              $output .= '<div class="bidder-feedback-msg-attr pull-left">';

              $output .= '<span class="bidder-feedback-msg-time"><span class="msg-aut-img">' . $userimg . '</span></span>';
              $output .= '<span class="bidder-feedback-msg-msg"><strong>' . $username . '</strong> - </span><span class="bidder-feedback-msg-content">' . $message_img_html . '</span><p class="message-post-time text-right clearfix">' . date('h:i A', REQUEST_TIME) . '</p>';
              $output .= '</div>';

              $output .= '<div class="bidder-feedback-msg-delete">';
              $output .= l('<i class="fa fa-times-circle"></i>', 'service-message-remove/' . $last_insert_id_attachment . '/nojs', array('html' => TRUE, 'attributes' => array('class' => array('bidder-feedback-msg-delete-link', 'use-ajax'))));
              $output .= '</div>';
              $output .= '</div>';
            }
          }
        }
      }

      if ($last_insert_id || $last_insert_id_attachment) {
        drupal_json_output(array('success' => 'Yes', 'insert' => $output));
        drupal_exit();
      }
    }
  }

  // If no data is received, abort.
  drupal_json_output(array('success' => 'No', 'insert' => $insert));
  drupal_exit();
}

/**
 * Menu callback for vendor-refresh-message.
 */
function vendor_refresh_message_ajax() {
  if (empty($_POST['id'])) {
    drupal_json_output(array('success' => 'No', 'insert' => $insert));
    drupal_exit();
  }

  $mapping_id = db_select('m6connect_messaging_connect_message', 'm')
    ->fields('m', array('mapping_id'))
    ->condition('id', $_POST['id'])
    ->execute()
    ->fetchField();

  if (!empty($mapping_id)) {
    global $user;
    $output = '';
    $query = db_select('m6connect_messaging_connect_message', 'm')
      ->fields('m')
      ->condition('mapping_id', $mapping_id)
      ->condition('id', $_POST['id'], '>')
      ->execute()
      ->fetchAll();

    if (!empty($query)) {
      foreach ($query as $result_obj) {
        $result = (array) $result_obj;
        if (empty($result['message_text']) && empty($result['attachment'])) {
          continue;
        }
        if ($result['author_uid'] == $user->uid) {
          continue;
        }
        if (empty($result['message_text']) && !empty($result['attachment'])) {
          // This is an attachment.
          $file = file_load($result['attachment']);
          // $file_url = file_create_url($file->uri);
          // $filename = $file->filename;
          // $fileicondrive = _get_file_icon_m6drive($file->filemime, TRUE);
          // if($fileicondrive) {
          //   $message_img_html = $fileicondrive;
          // }
          // else {
          //   $img_url = image_style_url('pic_40x40', $file->uri);
          //   $message_img_html = '<img src="' . $img_url . '" />';
          // }
          // $message_img_html = '<a href="' . $file_url . '">' . $message_img_html . '</a>';
          // $message_img_html = $filename . $message_img_html;
          $message_img_html = get_m6message_attachment_box($file->fid, $file->uri, $file->filename, $file->filemime);
          $result['message_text'] = $message_img_html;
        }
        // Checking if the sender is vendor manager.
        $alignclass = 'feedback-msg-reader';

        // Getting user image of sender and receiver.
        $userimg = _get_message_user_image($result['author_uid']);
        $result['realname'] = _get_user_full_name($result['author_uid']);

        $output .= '<div class="bidder-feedback-msg routing-feedback-msg-' . $result['id'] . ' clearfix ' . $alignclass . '" id="' . $result['id'] . '">';
        $output .= '<div class="bidder-feedback-msg-attr pull-left">';

        $output .= '<span class="bidder-feedback-msg-time"><span class="msg-aut-img">' . $userimg . '</span></span>';
        $output .= '<span class="bidder-feedback-msg-msg"><strong>' . $result['realname'] . '</strong> - </span><span class="bidder-feedback-msg-content">' . $result['message_text'] . '</span><p class="message-post-time text-right clearfix">' . date('h:i A', $result['timestamp']) . '</p>';
        $output .= '</div>';

        // if ($user->uid == $result['sender']) {
        //   $output .= '<div class="bidder-feedback-msg-delete">';
        //   $output .= l('<i class="fa fa-times-circle"></i>', 'service-message-remove/' . $result['id'] . '/nojs', array('html' => TRUE, 'attributes' => array('class' => array('bidder-feedback-msg-delete-link', 'use-ajax'))));
        //   $output .= '</div>';
        // }
        $output .= '</div>';
      }

      drupal_json_output(array('success' => 'Yes', 'insert' => $output));
      drupal_exit();
    }
  }

  drupal_json_output(array('success' => 'No', 'insert' => $insert));
  drupal_exit();
}

/**
 * Menu callback for approve-deny-vendor/%/%node/%node/%ctools_js
 */
function approve_deny_vendor_callback($action, $og_node, $vendor_node, $ajax = NULL) {
  if (!empty($ajax)) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'action_to_do' => $action,
      'og_node' => $og_node,
      'vendor_node' => $vendor_node,
    );

    $output = ctools_modal_form_wrapper('approve_deny_vendor_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('approve_deny_vendor_form', $action, $og_node, $vendor_node);
}

/**
 * Form to approve|deny vendor.
 */
function approve_deny_vendor_form($form, &$form_state, $action_to_do = NULL, $og_node = NULL, $vendor_node = NULL) {
  if (empty($form_state['og_node'])) {
    if (!empty($og_node) && is_object($og_node)) {
      $og_node = $og_node;
      $form_state['og_node'] = $og_node;
    }
  }
  else {
    $og_node = $form_state['og_node'];
  }

  if (empty($form_state['vendor_node'])) {
    if (!empty($vendor_node) && is_object($vendor_node)) {
      $vendor_node = $vendor_node;
      $form_state['vendor_node'] = $vendor_node;
    }
  }
  else {
    $vendor_node = $form_state['vendor_node'];
  }

  if (!empty($form_state['action_to_do'])) {
    $action_to_do = $form_state['action_to_do'];
  }

  if (empty($form_state['action_to_do']) && !empty($action_to_do)) {
    $form_state['action_to_do'] = $action_to_do;
  }

  $form = array();

  $delete = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to @action vendor: %title?', array('@action' => $action_to_do, '%title' => $og_node->title,)) . '</p></h4>';

  if ($action_to_do == 'deny') {
    $delete .= '<p>' . t('If you deny, this vendor will be removed permanently from your preferred list.') . '</p>';
  }
  $delete .= '</div>';

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

function approve_deny_vendor_form_submit($form, &$form_state) {
  $vendor_node = $form_state['vendor_node'];
  $action_to_do = $form_state['action_to_do'];
  $og_node = $form_state['og_node'];

  if ($action_to_do == 'approve') {
    $vendor_node->status = 1;
    node_save($vendor_node);
    $message = t('Vendor %title approved successfully.', array('%title' => $og_node->title));
  }
  elseif ($action_to_do == 'deny') {
    node_delete($vendor_node->nid);
    $message = t('Vendor %title denied/removed successfully.', array('%title' => $og_node->title));
  }

  // Showing message.
  drupal_set_message($message, 'status', FALSE);
  $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
  $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');

  // Refreshing table.
  $form_state['ajax_commands'][] = ajax_command_html('#vendor_m6reach_table', _get_vendor_m6reach_table('pending'));
  $form_state['ajax_commands'][] = array('command'=>'initializeDataTables');
  $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
}

/**
 * Menu callback for vendor/import.
 */
function import_vendor_csv() {
  $form = drupal_get_form('vendor_import_form');

  $mod_path = drupal_get_path('module', 'm6connect_vendor');

  $output = '<div class="clearfix">' . l(t('Download Sample Here'), $mod_path . '/includes/sample import.csv', array('attributes' => array('class' => array('form-submit', 'text-white')))) . '</div><br/><br/>';
  $output .= "<p>This tool will attempt to import CSV data";
  $output .= drupal_render($form);
  
  return $output;
}

/**
 * Function to generate form for importing csv data of vendors.
 */
function vendor_import_form() {
  $form['#attributes'] = array(
    'enctype' => 'multipart/form-data'
  );
  
  $form['amount_type'] = array(
    '#title' => t('Type of Amount?'),
    '#type' => 'radios',
    '#options' => array(0 => t('Expense'), 1 => t('Capital')),
    '#description' => t('Select the type of Invoice Amount to be saved as.'),
    '#required' => TRUE,
    '#attributes' => array('class'=> array('form-inline')),
  );
  $form['csvupload'] = array( 
    '#title' => t('CSV File'),
    '#type'  => 'file',
    '#description' => ($max_size = parse_size(ini_get('upload_max_filesize'))) ? t('Due to server restrictions, the <strong>maximum upload file size is !max_size</strong>. Files that exceed this size will be disregarded.', array('!max_size' => format_size($max_size))) : '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Commence Import'),
  );
  $form['#validate'] = array(
    'vendor_import_validate_fileupload',
  );
  return $form ;
}

/**
 * Validate function for vendor_import_form
 */
function vendor_import_validate_fileupload(&$form, &$form_state) {
  $validators = array(
    'file_validate_extensions' => array( 'csv' ),
  );
  if ( $file = file_save_upload('csvupload', $validators, "public://", FILE_EXISTS_REPLACE) ) {
    $form_state['values']['csvupload'] = $file->destination;
  }
  else {
    form_set_error('csvupload', t('Unable to copy upload file to !dest', array('!dest' => $destination)));
  }
}

/**
 * Submit handler for vendor_import_form
 */
function vendor_import_form_submit(&$form, &$form_state) {
  // dpm($form_state, 'form_state');
  // return;
  if (isset($form_state['values']['csvupload'])) {
    $batch = array(
      'title' => t('Importing CSV ...'),
      'operations' => array(),
      'init_message' => t('Commencing'),
      'progress_message' => t('Processed @current out of @total.'),
      'error_message' => t('An error occurred during processing'),
      'finished' => 'vendor_import_finished',
    );
    if ($handle = fopen($form_state['values']['csvupload'], 'r')) {
      $batch['operations'][] = array('_vendor_import_remember_filename', array($form_state['values']['csvupload']));
      $batch['operations'][] = array('_vendor_import_remember_amount_type', array($form_state['values']['amount_type']));
      $line_count = 1;
      $first = TRUE;
      while ($line = fgetcsv($handle)) {
        // dpm($line, 'line');
        // $data[$line[4]][] = $line;
        if (!$first) {
          $batch['operations'][] = array('_import_vendors', array($line));
        }
        $first = FALSE;
      }
      fclose($handle);
    }
    batch_set($batch);
  }
  else {
    // If we do not have a file, then showing warning.
    drupal_set_message(t('No file found for uploading, please try again!'), 'warning', FALSE);
  }
}