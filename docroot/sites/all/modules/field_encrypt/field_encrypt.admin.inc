<?php
// $Id$

/**
 * @file
 * Administrative interface for the Field encrypt module.
 */

/**
 * Alter the field settings form.
 */
function _field_encrypt_field_settings_form_alter(&$form, &$form_state, $form_id) {

  // Obtain the field name from form (should really be $form_state,
  // but the Date field doesn't comply).
  $field_name = $form['#field']['field_name'];

  // Try to obtain information about this field.
  $field_info = field_info_field($field_name);
  $field_type_info = field_info_field_types($field_info['type']);

  // If this field type cannot be encrypted, exit here
  #  if ($field_type_info['property_type']!='text') {
  #    return;
  #  }

  $fld_settings =& $field_info['settings'];

  $form_state['field_encrypt'] = array(
    'field_name' => $field_name,
    'field_info' => $field_info,
    'field_type_info' => $field_type_info,
    'encrypt' => isset($fld_settings['field_encrypt']) ? $fld_settings['field_encrypt']['encrypt'] : FALSE,
  );

  $settings =& $form['field']['settings'];

  $settings['field_encrypt'] = array(
    '#type' => 'fieldset',
    '#title' => t('Encrypt this field'),
    '#description' => t('Set up the parameters for encrypting this text field.'),
    '#tree' => TRUE,
    'encrypt' => array(
      '#type' => 'checkbox',
      '#title' => t('Encrypt this field'),
      '#default_value' => $form_state['field_encrypt']['encrypt'],
      '#weight' => 0,
    ),
    '#weight' => -2,
  );

  // Hide the option from non-privileged users,
  // but ensure the values carried through
  if (!user_access(FIELD_ENCRYPT_PERMISSION)) {
    $field_encrypt =& $settings['field_encrypt'];
    $field_encrypt['encrypt']['#type'] = 'value';
    $field_encrypt['encrypt']['#value'] = $field_encrypt['encrypt']['#default_value'];
  }

  // Make sure this file is loaded with this form
  form_load_include($form_state, 'inc', 'field_encrypt', 'field_encrypt.admin');

  // Add a submit handler to deal with the situation where
  // field encryption has been switched on or off.
  $form['#submit'][] = '_field_encrypt_field_settings_submit';
}

function _field_encrypt_field_settings_submit($form, &$form_state) {
  $field_info = $form_state['field_encrypt']['field_info'];
  $old_encrypt = $form_state['field_encrypt']['encrypt'];

  $values =& $form_state['values']['field']['settings']['field_encrypt'];
  $new_encrypt = $values['encrypt'];

  if ($old_encrypt) {
    if (!$new_encrypt) {
      // was encrypted but now unencrypted, so unencrypt it
      module_load_include('inc', 'field_encrypt');
      field_encrypt_un_encrypt($field_info);
    }
  }
  elseif ($new_encrypt) {
    // encryption flag wasn't set, but is now
    module_load_include('inc', 'field_encrypt');
    field_encrypt_do_encrypt($field_info);
  }
}
