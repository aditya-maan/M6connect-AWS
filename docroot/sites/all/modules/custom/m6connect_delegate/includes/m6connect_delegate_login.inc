<?php

function delegation_user_access_login($delegationId) {
  global $user;
  $entity = entity_load('delegate_user', array($delegationId));
  foreach ($entity as $vel) {
	  $uids = $vel;
  }
  $currenttime = time();
  if ($uids->status==1  && $uids->uid_to === $user->uid) {
	if ((int) $currenttime > (int) $uids->start_date && (empty($uids->revoke_date) || (int) $currenttime <= (int) $uids->revoke_date)) {
	  
		if(delegation_user_switch_user($uids->uid_from)){
		  $_SESSION['delegated']=1;
		  $entity = $entity[$delegationId];
		  $entity->last_login = time();
		  entity_save('delegate_user', $entity);
		  $new_user =  user_load($uids->uid_from);
		  $msg = theme('status_messages');
		  drupal_set_message(t('You are now delegated as !delegate_as.', array('!delegate_as' => theme('username', array('account' => $new_user)))));
		  drupal_goto('');
		}else{
		  drupal_set_message('You are not authorize for now.','error');
		}
	} else {
		drupal_set_message('You are not authorize for now.','error');
	}
  } else {
	  drupal_set_message('You are not authorize for now.','error');
  }
  drupal_goto('');
  return '';
}




function delegation_user_switch_back() {
  if(delegation_user_switch_back_access_callback()){
	masquerade_switch_back(); 
	if(isset($_SESSION['delegated'])){
	  unset($_SESSION['delegated']);  
    }
	drupal_goto(''); 
  }else{
	drupal_access_denied(); 
  }
}

function delegation_user_switch_user($uid) {
  global $user;
  if (!is_numeric($uid)) {
    drupal_set_message(t('A user id was not correctly passed to the switching function.'));
    watchdog('delegation_user', 'The user id provided to switch users was not numeric.', NULL, WATCHDOG_ERROR);
    return drupal_goto($_SERVER['HTTP_REFERER']);
  }

  $new_user = user_load($uid);

  if (!user_access('delegate_user_access') && !isset($_SESSION['masquerading'])) {
    watchdog('delegation_user', 'This user requires administrative permissions to switch to the user %user.', array('%user' => $new_user->name), WATCHDOG_ERROR);
    return FALSE;
  }

  if ($user->uid == $uid || isset($user->masquerading)) {
    watchdog('delegation_user', 'This user is already %user.', array('%user' => $new_user->name), WATCHDOG_ERROR);
    return FALSE;
  }

  if (variable_get('maintenance_mode', 0) && !user_access('access site in maintenance mode', $new_user)) {
    drupal_set_message(t('It is not possible to delegate in off-line mode as %user does not have the %config-perm permission. Please <a href="@site-maintenance">set the site status</a> to "online" to delegate as %user.', array('%user' => $new_user->name, '%config-perm' => 'use the site in maintenance mode', '@site-maintenance' => url('admin/settings/site-maintenance'))));
    return FALSE;
  }

  // Call logout hooks when switching from original user.
  module_invoke_all('user_logout', $user);
  drupal_session_regenerate();

  $query = db_insert('masquerade');
  $query->fields(array(
    'uid_from' => $user->uid,
    'uid_as' => $new_user->uid,
    'sid' => session_id(),
  ));
  $query->execute();
  // switch user

  watchdog('delegation_user', 'User %user now delegated as %masq_as.', array('%user' => $user->name, '%masq_as' => $new_user->name ? $new_user->name : variable_get('anonymous', t('Anonymous'))), WATCHDOG_INFO);
  //drupal_set_message(t('You are now masquerading as !masq_as.', array('!masq_as' => theme('username', array('account' => $new_user)))));
  $user->masquerading = $new_user->uid;
  $user = $new_user;

  // Call all login hooks when switching to masquerading user.
  $edit = array(); // Passed by reference.
  user_module_invoke('login', $edit, $user);
  $user->delegated = 1;
  return TRUE;
}



