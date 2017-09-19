<?php

/**
 * Generates the invite type editing form.
 *
 * @param $form
 * @param $form_state
 * @param InviteType $invite_type
 * @param string $op
 * @return array
 */
function invite_type_form($form, &$form_state, $invite_type, $op = 'edit') {
    if ($op == 'clone') {
        $invite_type->label .= ' (cloned)';
        $invite_type->type = '';
    }

    $form['#invite_type'] = $invite_type;

    $invite_sending_controllers = array();
    foreach (module_implements('invite_sending_controller') as $module) {
        $sending_controller = module_invoke($module, 'invite_sending_controller');
        $invite_sending_controllers[$module] = $sending_controller['label'];
    }

    if (empty($invite_sending_controllers)) {
        $form['message'] = array(
            '#markup' => t('Sorry no Invitation Type modules available in the system.'),
        );
        return $form;
    }

    $form['label'] = array(
        '#title' => t('Label'),
        '#type' => 'textfield',
        '#default_value' => $invite_type->label,
        '#description' => t('The human-readable name of this invite type.'),
        '#required' => TRUE,
        '#size' => 30,
    );

    // Machine-readable type name.
    $form['type'] = array(
        '#type' => 'machine_name',
        '#default_value' => isset($invite_type->type) ? $invite_type->type : '',
        '#maxlength' => 32,
        '#disabled' => $invite_type->isLocked() && $op != 'clone',
        '#machine_name' => array(
            'exists' => 'invite_get_types',
            'source' => array('label'),
        ),
        '#description' => t('A unique machine-readable name for this invite type. It must only contain lowercase letters, numbers, and underscores.'),
    );

    $form['description'] = array(
        '#type' => 'textarea',
        '#default_value' => isset($invite_type->description) ? $invite_type->description : '',
        '#description' => t('Description about the invite type.'),
    );

    $form['invite_sending_controller'] = array(
        '#title' => t('Sending method'),
        '#type' => 'checkboxes',
        '#default_value' => $invite_type->invite_sending_controller,
        '#description' => t('Invitation processing plugin.'),
        '#options' => $invite_sending_controllers,
        '#required' => TRUE,
    );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save invite type'),
        '#weight' => 40,
    );

    if (!$invite_type->isLocked() && $op != 'add' && $op != 'clone') {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete invite type'),
            '#weight' => 45,
            '#limit_validation_errors' => array(),
            '#submit' => array('invite_type_form_submit_delete')
        );
    }
    return $form;
}

/**
 * Submit handler for creating/editing invite_type.
 *
 * @param $form
 * @param $form_state
 */
function invite_type_form_submit(&$form, &$form_state) {
    $invite_type = entity_ui_form_submit_build_entity($form, $form_state);
    foreach ($form_state['values']['invite_sending_controller'] as $controller) {
        if (!empty($controller)) {
            $invite_type->invite_sending_controller[] = $controller;
        }
    }
    // Save and go back.
    invite_type_save($invite_type);

    // Redirect user back to list of invite types.
    $form_state['redirect'] = 'admin/structure/invite-types';
}

/**
 * @param $form
 * @param $form_state
 */
function invite_type_form_submit_delete(&$form, &$form_state) {
    $form_state['redirect'] = 'admin/structure/invite-types/' . $form_state['invite_type']->type . '/delete';
}

/**
 * Page to select invite Type to add new invite.
 *
 * @return array
 *   Renderable array
 */
function invite_admin_add_page() {
    $items = array();
    foreach (invite_get_types() as $invite_type_key => $invite_type) {
        $items[] = l(entity_label('invite_type', $invite_type), 'invite/add/' . $invite_type_key);
    }
    return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of invite to create.')));
}

/**
 * Add new invite page callback.
 *
 * @param string $type
 * @return array|mixed
 */
function invite_add($type) {
    $invite_type = invite_get_types($type);

    $invite = entity_create('invite', array('type' => $type));
    drupal_set_title(t('Create @name', array('@name' => entity_label('invite_type', $invite_type))));

    $output = drupal_get_form('invite_form', $invite);

    return $output;
}

function invite_add_multiple($form, &$form_state) {
    $form['field_invitation_multiple_email_address'] = array(
        '#title' => t('E-mail'),
        '#description' => 'Type e-mail addresses of the persons whom you wish invite. Enter email addresses as comma or semicolon seperated values.',
        '#type' => 'textarea',
        '#required' => FALSE,
        '#rows' => 1,
    );
	$form['special_message'] = array(
		  '#title' => t('Special Message'),
		  '#type' => 'textarea',
		  //'#weight' => 1,	  
		  );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => 'Send Invitation',
    );
    return $form;
}

function invite_add_multiple_submit($form, &$form_state) {
    $multi_array = array();
    $multi_list = $form['field_invitation_multiple_email_address']['#value'];
    $multi_list = preg_replace("/[\n]/", ",", $multi_list); /* For detect new line */
    $multi_list = str_replace(" ", "", $multi_list);
    $multi_list = str_replace(";", ",", $multi_list);
    $multi_array = explode(",", $multi_list);
    $multi_array = array_filter($multi_array);
    global $user;
    $site_name = variable_get('site_name', "Default site name");
    global $base_url;
    $expiry = date("Y-m-d H:i:s");
    $expiry = date(strtotime("$expiry +1 day"));
    $no_mail_id = count($multi_array);
    $no_valid_id = '';
    $multi_array = array_map('trim', $multi_array);
    $cid = _get_user_company_nid($user->uid);
	$SpecialMessage = (isset($form_state['values']['special_message'])?$form_state['values']['special_message']:'');
    foreach ($multi_array as $multi) {
        $valid = valid_email_address($multi);
		
        if ($valid) {
            $invite_data = array('user' => $user->uid,
                'site_name' => $site_name,
                'base_url' => $base_url,
                'expiry' => $expiry,
                'email' => $multi,
				'special_message'=>$SpecialMessage
            );
            $db_insert = array(
                'bundle' => 'organization',
                'entity_id' => $cid,
                'invited_by' => $user->uid,
                'emails' => serialize($invite_data),
                'invited_timestamp' => time(),
                'send_mail_timestamp' => NULL,
                'Status' => 0,
            );
            $returnedId = db_insert('invite_users_rfp_project')->fields($db_insert)->execute();
//      $invite_data = save_multiple_invites($user, $site_name, $base_url, $expiry, $multi);
//      send_multiple_invites($user, $invite_data, $multi);
            $no_valid_id = $no_valid_id + 1;
        }
    }
    drupal_set_message(t('Sent Invitations to ' . $no_valid_id . ' users, out of ' . $no_mail_id . ' users!'));
}

function save_multiple_invites($user, $site_name, $base_url, $expiry, $multi, $SpecialMsg= FALSE) {
    global $base_url;
    $uname = $user->realname;
    try {
        $reg_code = generate_accept_code();
		$special_msg_send = '';
		if($SpecialMsg){
		  $special_msg_send = '<p>'.$SpecialMsg.'</p></br>';
		}
        $data = array(
            'subject' => $uname . ' has sent you an invite!',
            'message' => $special_msg_send.'<p>' . $uname . ' has invited you to join ' . l(t($site_name), $base_url) . '.</p><br />
  
<p>To become a member of ' . $site_name . ', click the link below or paste it into the address bar of your browser.</p><br />

' . $base_url . '/invite/accept/' . $reg_code . '<br /><br /> ',
        );
        $invite_save = db_insert('invite')
                        ->fields(array(
                            'reg_code' => $reg_code,
                            'type' => 'invite_by_email',
                            'uid' => $user->uid,
                            'invitee' => 0,
                            'created' => REQUEST_TIME,
                            'expiry' => $expiry,
                            'joined' => 0,
                            'canceled' => 0,
                            'data' => serialize($data),
                        ))->execute();
        if ($invite_save) {
            db_insert('field_data_field_invitation_email_address')
                    ->fields(array(
                        'entity_type' => 'invite',
                        'bundle' => 'invite_by_email',
                        'deleted' => 0,
                        'entity_id' => $invite_save,
                        'revision_id' => $invite_save,
                        'language' => 'und',
                        'delta' => $invite_save,
                        'field_invitation_email_address_value' => $multi,
                        'field_invitation_email_address_format' => null,
                    ))->execute();
            return $data;
        } else {
            return FALSE;
        }
    } catch (Exception $ex) {
        drupal_set_message(t('karthikdb_insert failed. Message = %message, query= %query', array('%message' => $ex->getMessage(), '%query' => $ex->query_string)), 'error');
    }
}

function send_multiple_invites($user, $invite_data, $multi) {
    $message = $invite_data['message'];
    $message = wordwrap($message, 70);
    $params['body'] = $message;
    $params['subject'] = $invite_data['subject'];
    $params['header'] = "From: $user->mail\n";
    //mail($multi, $invite_data['subject'], $message, "From: $user->mail\n");
    $mail = drupal_mail('invite', 'company-invite', $multi, 'en', $params);   
}

function generate_accept_code() {
    do {
        $reg_code = user_password(10);
        $result = (bool) db_query_range('SELECT reg_code FROM {invite} WHERE reg_code = :regcode', 0, 1, array(':regcode' => $reg_code))->fetchField();
    } while ($result);
    return $reg_code;
}

/**
 * Invite Form.
 *
 * @param $form
 * @param $form_state
 * @param Invite $invite
 * @return array
 */
function invite_form($form, &$form_state, $invite) {
    $form['#entity'] = $form_state['invite'] = $invite;

    $form['uid'] = array(
        '#type' => 'value',
        '#value' => $invite->uid,
    );

    field_attach_form('invite', $invite, $form, $form_state);

    $submit = array();
    if (!empty($form['#submit'])) {
        $submit += $form['#submit'];
    }

    $form['actions'] = array(
        '#weight' => 100,
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save invite'),
        '#submit' => $submit + array('invite_form_submit'),
    );

    // Show Delete button if we edit invite.
    $invite_id = entity_id('invite', $invite);
    if (!empty($invite_id) && invite_access('edit', $invite)) {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete'),
            '#submit' => array('invite_form_submit_delete'),
        );
    }

    $form['#validate'][] = 'invite_form_validate';

    return $form;
}

/**
 * Validates invitation form.
 *
 * @param $form
 * @param $form_state
 */
function invite_form_validate($form, &$form_state) {
    
}

/**
 * Invite creation submit handler.
 *
 * @param $form
 * @param $form_state
 */
function invite_form_submit($form, &$form_state) {
    $invite = $form_state['invite'];

    entity_form_submit_build_entity('invite', $invite, $form, $form_state);

    if (invite_save($invite)) {
        $invite_uri = entity_uri('invite', $invite);
        $form_state['redirect'] = $invite_uri['path'];
    }
}

/**
 * Invite delete form handler
 *
 * @param $form
 * @param $form_state
 */
function invite_form_submit_delete($form, &$form_state) {
    $invite = $form_state['invite'];
    $invite_uri = entity_uri('invite', $invite);
    $form_state['redirect'] = $invite_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 *
 * @param $form
 * @param $form_state
 * @param Invite $invite
 * @return array
 */
function invite_delete_form($form, &$form_state, $invite) {
    $form_state['invite'] = $invite;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['invite_type_id'] = array('#type' => 'value', '#value' => entity_id('invite', $invite));
    $invite_uri = entity_uri('invite', $invite);
    return confirm_form($form, t('Are you sure you want to delete invite %title?', array('%title' => entity_label('invite', $invite))), $invite_uri['path'], t('This action cannot be undone.'), t('Delete'), t('Cancel')
    );
}

/**
 * Delete form submit handler.
 *
 * @param $form
 * @param $form_state
 */
function invite_delete_form_submit($form, &$form_state) {
    $invite = $form_state['invite'];
    invite_delete($invite);

    drupal_set_message(t('invite %title deleted.', array('%title' => entity_label('invite', $invite))));

    $form_state['redirect'] = '<front>';
}

/**
 * Invite module settings form.
 *
 * @return array
 */
function invite_settings_form() {
    $form = array();

    $form['invite_default_expiry_time'] = array(
        '#type' => 'select',
        '#title' => t('Invitation expiry'),
        '#default_value' => variable_get('invite_default_expiry_time', 30),
        '#options' => drupal_map_assoc(array(1, 3, 7, 14, 30, 60, 365)),
        '#description' => t('Set the expiry period for user invitations, in days.'),
        '#multiple' => FALSE,
        '#required' => TRUE,
    );

    $form['invite_registration_path'] = array(
        '#type' => 'textfield',
        '#title' => t('Path to registration page'),
        '#default_value' => variable_get('invite_registration_path', 'user/register'),
        '#description' => t('Path to the registration page for invited users. Useful when using the <em>Assign from Path</em> option of <a href="@url">Auto Assign Roles</a> module.', array('@url' => 'http://drupal.org/project/autoassignrole')),
    );

    $form['invite_require_approval'] = array(
        '#type' => 'checkbox',
        '#title' => t('Require administrator approval for invitees'),
        '#default_value' => variable_get('invite_require_approval', FALSE),
        '#description' => t('Accounts that have been created with an invitation will require administrator approval.'),
    );

    return system_settings_form($form);
}

/**
 * Migration form.
 *
 * @return array
 */
function invite_migrate_form() {
    $form = array();
    $migration_possible = TRUE;

    // Check prerequisites.
    $available_types = array(
        'none' => '- Please select -',
    );
    $invite_types = invite_get_types();
    foreach ($invite_types as $name => $type) {
        if ($type->invite_sending_controller == 'invite_by_email') {
            $available_types[$name] = $type->label;
        }
    }

    if (!module_exists('invite_by_email')) {
        drupal_set_message(t('You should enable Invite by e-mail module.'), 'error');
        $migration_possible = FALSE;
    }

    if (!module_exists('invite_notifications')) {
        drupal_set_message(t('You should enable Invite Notifications module.'), 'error');
        $migration_possible = FALSE;
    }

    if ($migration_possible) {
        $form['type'] = array(
            '#title' => t('Choose type'),
            '#description' => t('Select an Invite type which will be used to import old invites.'),
            '#type' => 'select',
            '#options' => $available_types,
            '#default_value' => 'none',
        );

        $form['drop_old_tables'] = array(
            '#title' => t('Drop old tables'),
            '#description' => t('Drop tables from Invite 2.x module after migration is completed.'),
            '#type' => 'checkbox',
            '#default_value' => TRUE,
        );

        $form['actions'] = array(
            '#type' => 'actions'
        );

        $form['actions']['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Migrate'),
        );
    } else {
        $form['message'] = array(
            '#markup' => t('Migration is impossible, please fix errors mentioned above.'),
        );
    }

    return $form;
}

/**
 * Implements validation for migration form.
 *
 * @param $form
 * @param $form_state
 */
function invite_migrate_form_validate($form, &$form_state) {
    if ($form_state['values']['type'] == 'none') {
        form_set_error('type', t('Please choose an Invite type.'));
    } else {
        // TODO: add field mapping to the form.
        $needed_fields = array(
            'field_invitation_email_address',
            'field_invitation_email_subject',
            'field_invitation_email_body',
        );
        $verified_fields = 0;
        foreach (field_info_instances('invite', 'invite_by_email') as $field_name => $field) {
            if (in_array($field_name, $needed_fields)) {
                $verified_fields++;
            }
        }
        if ($verified_fields != count($needed_fields)) {
            form_set_error('type', t('This content type couldn\'t be used.'));
        }
    }
}

/**
 * Implements submit handler for migration.
 *
 * @param $form
 * @param $form_state
 */
function invite_migrate_form_submit($form, &$form_state) {
    if ($form_state['values']['submit'] == t('Migrate')) {
        $batch = array(
            'title' => t('Migrating'),
            'operations' => array(
                array('invite_migrate_process', array($form_state['values'])),
            ),
            'file' => drupal_get_path('module', 'invite') . '/includes/invite.admin.inc'
        );
        batch_set($batch);
        batch_process();
    }
}

function invite_migrate_process($values, &$context) {
    $query = db_select('invite_2x', 'i2x')
            ->fields('i2x');
    if (empty($context['sandbox'])) {
        $context['sandbox']['progress'] = 0;
        $context['sandbox']['max'] = $query->countQuery()->execute()->fetchField();
    }
    $limit = 20;
    variable_set('invite_migration_in_progress', TRUE);
    $result = $query->range($context['sandbox']['progress'], $limit)->execute();
    foreach ($result as $record) {
        $invite_data = array(
            'type' => $values['type'],
            'reg_code' => $record->reg_code,
            'uid' => $record->uid,
            'invitee' => $record->invitee,
            'created' => $record->created,
            'expiry' => $record->expiry,
            'joined' => $record->joined,
            'canceled' => $record->canceled,
            'data' => $record->data,
        );
        $invite = new Invite($invite_data);
        $invite->field_invitation_email_address[LANGUAGE_NONE][0]['value'] = $record->email;
        $data = unserialize($record->data);
        $invite->field_invitation_email_subject[LANGUAGE_NONE][0]['value'] = $data['subject'];
        $invite->field_invitation_email_body[LANGUAGE_NONE][0]['value'] = $data['message'];
        $invite->sendNotification = FALSE;
        $invite->save();

        $context['sandbox']['progress'] ++;
    }
    variable_del('invite_migration_in_progress');
    if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
        $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
    } else {
        if ($values['drop_old_tables']) {
            db_drop_table('invite_2x');
            db_drop_table('invite_notifications_2x');
        }
    }
}
