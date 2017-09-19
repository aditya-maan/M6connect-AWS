<?php
/**
 * @file
 * Password policy constraint callbacks.
 */

/****************************************************************************/
/* Constraint API                                                           */
/****************************************************************************/

/**
 * Description of the constraint.
 */
function password_policy_constraint_real_name_description() {
  return array('name' => t('Real Name'), 'description' => t("Password must not contain user's first or last name. Put any positive number to enforce this policy."));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_real_name_error($constraint) {
	return t('Password must not contain your first or last name.');
}

/**
 * Password validation.
 */
function password_policy_constraint_real_name_validate($password, $constraint, $account) {
  if (isset($_POST['field_first_name']) && isset($_POST['field_last_name'])) {
    $first_name = $_POST['field_first_name'][LANGUAGE_NONE][0]['value'];
    $last_name = $_POST['field_last_name'][LANGUAGE_NONE][0]['value'];
  }
  else {
    list($first_name, $last_name) = _password_policy_constraint_real_name_get_name($uid);
  }
  $first_name_lowercase = drupal_strtolower($first_name);
  $last_name_lowercase = drupal_strtolower($last_name);
  $password_lowercase = drupal_strtolower($password);
  $contains_first_name = strpos($password_lowercase, $first_name_lowercase) !== FALSE;
  $contains_last_name = strpos($password_lowercase, $last_name_lowercase) !== FALSE;
  return !$contains_first_name && !$contains_last_name;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_real_name_js($constraint, $account) {
  // Add first and last name as JavaScript settings.
  $uid = $account->uid;
  list($first_name, $last_name) = _password_policy_constraint_real_name_get_name($uid);
  $data = array(
    'password_policy' => array(
      'first_name' => $first_name,
      'last_name' => $last_name,
    ),
  );
  drupal_add_js($data, 'setting');

  return <<<JS

    var password_lowercase = value.toLowerCase();

    var firstNameInput = jQuery('#edit-field-first-name input');
    var first_name = '';
    if (firstNameInput.length) {
      first_name = firstNameInput.val();
    }
    else {
      first_name = Drupal.settings.password_policy.first_name;
    }
    var first_name_lowercase = first_name.toLowerCase();

    var lastNameInput = jQuery('#edit-field-last-name input');
    var last_name = '';
    if (lastNameInput.length) {
      last_name = lastNameInput.val();
    }
    else {
      last_name = Drupal.settings.password_policy.last_name;
    }
    var last_name_lowercase = last_name.toLowerCase();

    if (first_name_lowercase != '' && password_lowercase.indexOf(first_name_lowercase) != -1) {
      strength = "low";
      msg.push(translate.constraint_real_name);
    }
    if (last_name_lowercase != '' && password_lowercase.indexOf(last_name_lowercase) != -1) {
      strength = "low";
      msg.push(translate.constraint_real_name);
    }
JS;
}

/**
 * Gets real name for given uid.
 *
 * @param int $uid
 *   User ID.
 *
 * @return array
 *   Array where first element is first name and second element is last name.
 */
function _password_policy_constraint_real_name_get_name($uid) {
  // Anonymous users will not have first and last names set.
  if ($uid == 0) {
    $first_name = '';
    $last_name = '';
  }
  else {
    $user = user_load($uid, TRUE);
    $first_name = $user->field_first_name['und'][0]['value'];
    $last_name = $user->field_last_name['und'][0]['value'];
  }
  return array($first_name, $last_name);
}