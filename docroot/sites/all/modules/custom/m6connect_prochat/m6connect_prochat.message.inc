<?php

/**
 * @file Message Send Callback for m6connect_prochat module.
 */

/**
 * Menu callback for chat/message
 */
function send_message_chat() {
  $output = 0;
  // Collecting information.
  $uid = isset($_REQUEST['sid']) ? $_REQUEST['sid'] : 0;
  $receiver = isset($_REQUEST['rid']) ? $_REQUEST['rid'] : 0;
  $message = isset($_REQUEST['message']) ? $_REQUEST['message'] : 0;
  $is_file = isset($_REQUEST['is_file']) ? $_REQUEST['is_file'] : 0;
  
  if (empty($uid) || empty($receiver) || empty($message)) {
    // If any of the four information is not available, then aborting.
    drupal_json_output($output);
    drupal_exit();
  }

  module_load_include('inc', 'm6connect_prochat', 'm6connect_prochat.rest');
  $user_object = _user_load($uid);
  $name = $user_object->field_first_name['und'][0]['value'] . ' ' . $user_object->field_last_name['und'][0]['value'];

  // Trying to insert a new message record in Database.
  $mid = db_insert('m6connect_chat_app')
    ->fields(array(
      'uid' => $uid,
      'receiver' => $receiver,
      'thread_id' => 0,
      'message' => $message,
      'delivered' => '0',
      'seen' => '0',
      'updated' => REQUEST_TIME,
    ))
    ->execute();
  if (!empty($mid)) {
    $output = array('id' => $mid, 'uid' => $uid, 'name' => $name, 'msg' => $message);
  }
  drupal_json_output($output);
  drupal_exit();
}

/**
 * Menu callback for chat/history.
 */
function get_chat_history() {
  $output = 0;

  // Collecting information.
  $uid = isset($_REQUEST['sid']) ? $_REQUEST['sid'] : 0;
  $receiver = isset($_REQUEST['rid']) ? $_REQUEST['rid'] : 0;
  $index = isset($_REQUEST['index']) ? $_REQUEST['index'] : 0;

  if (empty($uid) || empty($receiver)) {
    // If user id or receiver id is not received then aborting.
    drupal_json_output($output);
    drupal_exit();
  }

  // if $index is 0, then we need to fetch data for today and yesterday.
  // If $index is 1, then 2 days before yesterday, if $index is 2, then 4 days
  // before yesterday and so on.
  $from = strtotime('yesterday');
  if (!empty($index)) {
    // $default = 1;
    // $upto = ($index * 2) + $default;
  }

  $query = db_select('m6connect_chat_app', 'a')
    ->fields('a')
    ->condition(db_or()
      ->condition(db_and()
        ->condition('uid', $uid)
        ->condition('receiver', $receiver))
      ->condition(db_and()
        ->condition('uid', $receiver)
        ->condition('receiver', $uid)))
    ->condition('updated', $from, '>=')
    ->orderBy('updated', 'DESC')
    ->execute();
  if ($query->rowCount() > 0) {
    $output = array();
    $update_delivered = array();
    module_load_include('inc', 'm6connect_prochat', 'm6connect_prochat.rest');
    while ($result = $query->fetchObject()) {
      if ($result->uid == $receiver) {
        // Collecting the messages to mark as delivered.
        $update_delivered[] = $result->id;
      }
      // Need to send the name again.
      $user_object = _user_load($result->uid);
      $name = $user_object->field_first_name['und'][0]['value'] . ' ' . $user_object->field_last_name['und'][0]['value'];

      $file = $result->fid;
      $output[] = array(
        'mid' => $result->id,
        'uid' => $result->uid,
        'name' => $name,
        'message' => !empty($result->message) ? $result->message : $file,
        'is_file' => !empty($result->message) ? 0 : 1,
        'delivered' => $result->delivered,
        'seen' => $result->seen,
        'updated' => $result->updated,
      );
    }
    if (!empty($update_delivered)) {
      // Updating the messages as delivered.
      db_update('m6connect_chat_app')
        ->fields(array(
          'delivered' => 1,
        ))
        ->condition('id', $update_delivered, 'IN')
        ->execute();
    }
  }
  else {
    // We didn't get any messages for the given time period.
    // @todo discuss about this.
  }
  drupal_json_output($output);
  drupal_exit();
}

/**
 * Menu callback for chat/refresh.
 */
function refresh_chat() {
  $output = 0;
  $mid = $_REQUEST['mid'];
  $uid = $_REQUEST['sid'];
  $receiver = $_REQUEST['rid'];
  $new_chat = $_REQUEST['new_chat'];

  if (empty($mid) && empty($new_chat)) {
    // If no message id is received and chat is not new then aborting.
    drupal_json_output($output);
    drupal_exit();
  }
  
  $query = db_select('m6connect_chat_app', 'a')
    ->fields('a')
    ->condition(db_or()
      ->condition(db_and()
        ->condition('uid', $uid)
        ->condition('receiver', $receiver))
      ->condition(db_and()
        ->condition('uid', $receiver)
        ->condition('receiver', $uid)));
  if (!empty($mid)) {
    $query->condition('id', $mid, '>');
  }
  $record = $query->orderBy('updated', 'DESC')->execute();

  if ($record->rowCount() > 0) {
    $output = array();
    module_load_include('inc', 'm6connect_prochat', 'm6connect_prochat.rest');
    while ($result = $record->fetchObject()) {
      if ($result->uid == $receiver) {
        // Collecting the messages to mark as delivered.
        $update_delivered[] = $result->id;
      }
      $file = $result->fid;
      $user_object = _user_load($result->uid);
      $name = $user_object->field_first_name['und'][0]['value'] . ' ' . $user_object->field_last_name['und'][0]['value'];

      $output[] = array(
        'mid' => $result->id,
        'uid' => $result->uid,
        'name' => $name,
        'message' => !empty($result->message) ? $result->message : $file,
        'is_file' => !empty($result->message) ? 0 : 1,
        'delivered' => $result->delivered,
        'seen' => $result->seen,
        'updated' => $result->updated,
      );
    }
    if (!empty($update_delivered)) {
      // Updating the messages as delivered.
      db_update('m6connect_chat_app')
        ->fields(array(
          'delivered' => 1,
        ))
        ->condition('id', $update_delivered, 'IN')
        ->execute();
    }
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * Menu callback for group create.
 */
function prochat_create_group($ajax){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,      
    );
    $output = ctools_modal_form_wrapper('prochat_create_group_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('prochat_create_group_form');
}
function prochat_create_group_form($form, &$form_state, $groupId = ''){
  global $user;global $company;  
  $uid = $user->uid;
  $cmpNid = $company->nid;
  $cmpUserlist[0] = 'Select user';
  $cmpUser = _get_user_names_by_group_company_nid($cmpNid);  
  foreach ($cmpUser as $key => $value) {
    $realName = str_replace(" ", "@", ucwords($value->realname));
    $userName = $realName.'@'.$value->uid;
    $cmpUserlist[$userName] = $value->realname;
  }
  if(empty($groupId)){
    $groupId = $form_state['groupId'];
  }
  $prochatData[0] = 'Select parent group';
  $egrouptype = $egroupname = '';
  if(!empty($groupId)){
    $groupRes = getGroupDataFromGroupId($groupId);
    if(!empty($groupRes)){
      $egrouptype = $groupRes[0]->service_type;
      $egroupname = $groupRes[0]->title;
      $egroupparentid = $groupRes[0]->parent;
      $userID =  array();$umail = '';
      foreach ($groupRes as $key => $value) {
        $userID[] = $value->uid;
        $userEmail[] = $value->email;
      }
      if(!empty(array_filter($userEmail))){
        $umail = implode(",", $userEmail);
      }
      $gtitleData = getGroupByTypeComAuthor($groupId, $egrouptype);
      foreach ($gtitleData as $provalue) {
        $grId = $provalue->id;
        $prochatData[$grId] = $provalue->title;
      }
    }    
  }
  
  if (isset($form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'group_type' && !empty($form_state['triggering_element']['#value'])) {
    $prochatDataValue = get_group_by_type_cid_nid($form_state['triggering_element']['#value'], $user->uid, $company->nid);
    foreach ($prochatDataValue as $provalue) {
      $grId = $provalue->id;
      $prochatData[$grId] = $provalue->title;
    }    
  }
  $form = array();
  $groupOption = array("0" => "Select group type", "Program" => "Program", "Project" => "Project", "Proposal" => "Proposal");
  $form['main-container']= array(
    '#type' => 'container', 
    '#attributes' => array( 'class'=>array('prochat_main_container_overflow', 'margin-bottom-20')), 
    '#prefix' => '<div class="clearfix"><div id="prochat_main_container_overflow" class="prochat-group-popup">',
  );
  $form['groupId'] = array(
    '#type' => 'value',
    '#value' => $groupId,
  );
  $form['main-container']['group_type'] = array(
    '#type' => 'select',
    '#title' => t('Select Group Type'),
    '#options' => $groupOption,
    '#default_value' => $egrouptype,
    '#required' => TRUE,
    '#attributes' => array('class' => array('margin-bottom-20', 'grouptypelisting')),
    /*'#ajax' => array(
      'callback' => 'parent_load_by_type',
      'wrapper' => 'parent-group-list',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array( 'type'=> 'throbber', 'message'=> NULL ),
    ),*/
  );
  $form['main-container']['group_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter Group Name'),    
    '#required' => TRUE,
    '#default_value' => $egroupname,
    '#attributes' => array('class' => array('margin-bottom-20')),        
  );
  $form['main-container']['parent_group'] = array(
    '#type' => 'select',
    '#title' => t('Parent Group'),
    '#options' => $prochatData,
    '#default_value' => $egroupparentid,
    '#attributes' => array('class' => array('parent-group-list margin-bottom-20')),
    '#prefix' => '<div id="parent-group-list">',
    '#suffix' => '</div>',
  );
  $form['main-container']['group_user'] = array(
    '#type' => 'select',
    '#title' => t('Select Group User'),
    '#options' => $cmpUserlist,      
    '#multiple' => TRUE,
    '#default_value' => $userID,
    '#select2' => array(
      'minimumResultsForSearch' => '1',
    ),
    '#attributes' => array('class' => array('margin-bottom-20')),        
  );
  /*$form['main-container']['invite_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Invite User'),
    '#default_value' => $umail,
    '#description' => 'Use , to saperate multiple email',
    '#attributes' => array('placeholder' => 'Enter Email', 'class' => array('margin-top-10')),
  );*/
  $form['authid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => $cmpNid,
  );  
  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array( 'external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('m6connect-prochat-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')) ), 
    '#weight' => 10, 
  );
  $form['submit'] = array(
    '#value' => 'Save',
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'prochat_group_form_submit',
      'wrapper' => 'parent-group-list',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array( 'type'=> 'throbber', 'message'=> NULL ),
    ),
  );

  return $form;
}
// group form ajax submit
function prochat_group_form_submit(&$form, &$form_state){
  $values = $form_state['values'];
  // drupal_add_js(array('m6connect_prochat' => array('addGroupData'=>array($values))),'setting');
  $argument = array('addGroupData'=>array($values));
  $commands = array();
  $commands[] = ajax_command_settings($argument, $merge = TRUE);
  $commands[] = array('command' => 'after_form_js');
  return array('#type' => 'ajax', '#commands' => $commands);
}

/*function prochat_create_group_form_validate(&$form, &$form_state){
  $values = $form_state['values'];
  $authid = $values['authid'];
  $cid = $values['cid'];
  $groupId = $values['groupId'];
  if(!empty($authid) && !empty($cid)){
    if(!empty($groupId)){
      $getGrTitle = db_select('m6connect_prochat_group_data', 'mpgd')
                  ->fields('mpgd', array('title'))
                  ->condition('id', $groupId, '=')
                  ->execute()->fetchAssoc();
      $grTitle = $getGrTitle['title'];      
      if($grTitle != $values['group_name']){
        $getGroup = db_select('m6connect_prochat_group_data', 'mpgd')
                  ->fields('mpgd', array('id'))
                  ->condition('title', $values['group_name'])
                  ->condition('service_type', $values['group_type'])
                  ->condition('author_id', $authid)
                  ->condition('cid', $cid)
                  ->execute()->fetchAssoc();
      }      
    }
    else{  
      $getGroup = db_select('m6connect_prochat_group_data', 'mpgd')
              ->fields('mpgd', array('id'))
              ->condition('title', $values['group_name'])
              ->condition('service_type', $values['group_type'])
              ->condition('author_id', $authid)
              ->condition('cid', $cid)
              ->execute()->fetchAssoc();
    }
    if(!empty($getGroup)){
      form_set_error('group_name', t('This group is already exist.'));
    }    
  }
  // email validation
  if(!empty($values['invite_user'])){
    $invite_user = $values['invite_user'];
    $pos = strpos(",", $invite_user);
    if($pos != flase){
      $emails = explode(",", $invite_user);
      $userEmails = array_unique($emails);
      if(!empty($userEmails)){
        foreach ($userEmails as $value) {
          if(filter_var($value, FILTER_VALIDATE_EMAIL) === false){
            form_set_error('invite_user', t("\"$value\" is not valid email"));
          }
        }
      }
    }
  }
}
function prochat_create_group_form_submit(&$form,  &$form_state){  
  $values = $form_state['values'];
  $authid = $values['authid'];
  $cid = $values['cid'];
  $parent = $values['parent_group'];
  $guser = $values['group_user'];
  $groupId = $values['groupId'];
  $invite_user = $values['invite_user'];
  if(empty($values['parent_group'])){
    $parent = 0;
  }
  if(!empty($groupId)){
    if(!empty($authid) && !empty($cid)){
      $fields = array(
        'title' => addslashes($values['group_name']),
        'parent' => $parent,
        'service_type' => $values['group_type'],
      );
      $group_update = db_update('m6connect_prochat_group_data');
      $group_update->fields($fields);
      $group_update->condition('id', $groupId, '=');
      $group_update->execute();

      if(!empty($guser)){
        $getUser = db_select("m6connect_prochat_group_user", "mpgu")
                  ->fields("mpgu", array('id', 'uid'))
                  ->condition('gid', $groupId, '=')
                  ->execute()->fetchAllKeyed(0,1);        
        $existingDiff = array_diff($getUser, $guser);
        foreach ($existingDiff as $key => $diffvalue) {
          $deleteGrpDetail = db_delete('m6connect_prochat_group_user')
                          ->condition('id', $key, '=')
                          ->execute();
        }
        $newDiff = array_diff($guser, $getUser);
        foreach ($newDiff as $key => $value) {
          $setGrouoUser = db_insert('m6connect_prochat_group_user')
                        ->fields(
                          array(
                            'gid' => $groupId,
                            'uid' => $key,
                            'status' => 1,
                            'timestamp' => time(),
                          )
                        )->execute();
        }
      }
    }
    drupal_set_message('Group updated successfully', 'status');
  }
  else{
    if(!empty($authid) && !empty($cid)){
      $setGroup = db_insert('m6connect_prochat_group_data')
                ->fields(
                  array(
                    'title' => addslashes($values['group_name']),
                    'parent' => $parent,
                    'service_type' => $values['group_type'],
                    'author_id' => $authid,
                    'cid' => $cid,
                    'status' => 1,
                    'timestamp' => time(),
                  )
                )->execute();
      if(!empty($guser)){
        foreach ($guser as $key => $value) {
          $setGrouoUser = db_insert('m6connect_prochat_group_user')
                        ->fields(
                          array(
                            'gid' => $setGroup,
                            'uid' => $key,
                            'status' => 1,
                            'timestamp' => time(),
                          )
                        )->execute();
        }
      }
      if(!empty($invite_user)){
        $pos = strpos(",", $invite_user);
        if($pos != flase){
          $emails = explode(",", $invite_user);
          $userEmails = array_unique($emails);
          if(!empty($userEmails)){
            foreach ($userEmails as $value) {
              $userUid = getUserUidFromEmail(trim($value));
              if(!empty($userUid)){
                $setGrouoUser = db_insert('m6connect_prochat_group_user')
                              ->fields(
                                array(
                                  'gid' => $setGroup,
                                  'uid' => $userUid,
                                  'email' => trim($value),
                                  'status' => 1,
                                  'timestamp' => time(),
                                )
                              )->execute();
              }
              else{
                sendInvitationOnEmail(trim($value), addslashes($values['group_name']));  // function for send invitation
                $setGrouoUser = db_insert('m6connect_prochat_group_user')
                              ->fields(
                                array(
                                  'gid' => $setGroup,
                                  'email' => trim($value),
                                  'status' => 1,
                                  'timestamp' => time(),
                                )
                              )->execute();
              }
            }
          }
        }
      }
      drupal_set_message('Group created successfully', 'status');
    }
  }
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/dashboard');  
  }
}*/
/**
 * Menu callback for get group wise user list.
 */
function prochat_show_group_user_list($groupId = '', $groupName = '', $ajax){
  if ($ajax) {
    if(!empty($groupId)){
      $getGroupUserId = getUserUidByGid($groupId);
      if(!empty($getGroupUserId)){
        $loggedUser = getLoggedinUserId();        
        $data = '<div id="prochat-group-user-list"><hr><h3 class="dashboard-block-account margin-top-10 text-center">'.$groupName.' Member </h3><ul class="list-group margin-top-10">';
        foreach ($getGroupUserId as $key => $userid) {
          $getUserName = _get_user_mail_realname_by_uid($userid);
          if(!empty($getUserName['name'])){
            if(in_array($userid, $loggedUser)){
              $data .= '<li class="list-group-item get-user-popup" data-name="'.$getUserName['name'].'"><span class="prochat-loggedin"></span>'.$getUserName['realname'].'</li>'; 
            }
            else{
              $data .= '<li class="list-group-item get-user-popup" data-name="'.$getUserName['name'].'"><span class="prochat-loggedout"></span>'.$getUserName['realname'].'</li>';
            }
          }
        }
        $data .= '</ul></div>';
        $commands[] = ajax_command_replace('#prochat-group-user-list',$data);        
        print ajax_render($commands);
        drupal_exit(0);
      }
    }
  }
}

function getLoggedinUserId(){
  $result = db_query('SELECT uid FROM {sessions} WHERE uid != 0');
  $getUser = db_select('sessions', 's')
            ->fields('s', array('uid'))
            ->condition('uid', 0, '!=')
            ->execute()->fetchcol();
  return array_unique($getUser);
}
/*
 *  callback for edit group
 */
function edit_prochat_group($groupId = '', $ajax){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'groupId' => $groupId,
    );
    $output = ctools_modal_form_wrapper('prochat_create_group_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('prochat_create_group_form', $groupId);
}








/*
 *  Common function
 */
function parent_load_by_type(&$form, &$form_state) {
  $commands = array();
  $commands[] = ajax_command_replace('#parent-group-list',render($form['main-container']['parent_group']));

  return array('#type' => 'ajax', '#commands' => $commands);
}
function get_group_by_type_cid_nid($type = '', $uid = '', $nid = ''){
  $getGroupData = db_select('m6connect_prochat_group_data', 'mpgd')
                ->fields('mpgd', array('id', 'title'))
                ->condition('service_type', $type)
                ->condition('author_id', $uid)
                ->condition('cid', $nid)
                ->execute()->fetchAll();
  return $getGroupData;
}
function getUserUidByGid($gid){
  $getGroupUserId = db_select('m6connect_prochat_group_user', 'mpgu')
                  ->fields('mpgu', array('id', 'uid'))
                  ->condition('gid', $gid, '=')
                  ->execute()->fetchAllKeyed(0,1);
  return $getGroupUserId;
}
function getGroupByGid($gid){
  $getGroupTitle = db_select('m6connect_prochat_group_data', 'mpgd')
                  ->fields('mpgd', array('title'))
                  ->condition('id', $gid, '=')
                  ->execute()->fetchAssoc();
  return $getGroupTitle;
}
/*
* function for send invitation email on add edit group
*/
function sendInvitationOnEmail($email = '', $groupName = ''){
  global $base_url, $base_path, $user, $company;
  if(!empty($email)){
    $siteText = str_replace(array('http://','https://'), array('',''),$base_url);    
    $emailMessage = 'You are invited in '.$groupName.' group - please login at '.l($siteText, $base_url.$base_path).' to learn more.';    
    $params = array(
      'subject' => 'Invitation',
      'body' => $emailMessage,
      'sender' => $user->mail,
      'language' => language_default(),
      'module' => 'm6connect_misc',
      'key' => 'invite_user_in_group',
    );    
    $return = drupal_mail($params['module'], $params['key'], $email, $params['language'], $params);
  }
}
/*
 * function for get group data
 */
function getGroupDataFromGroupId($groupId = ''){
  $getGroup = db_select("m6connect_prochat_group_data", "mpgd");
  $getGroup->leftJoin("m6connect_prochat_group_user", "mpgu", "mpgu.gid = mpgd.id");
  $getGroup->fields("mpgd", array("title", "service_type", "parent"));
  $getGroup->fields("mpgu", array("uid", "email"));
  $getGroup->condition("mpgd.id", $groupId, '=');
  $groupRes = $getGroup->execute()->fetchAll();
  return $groupRes;
}

function getGroupByTypeComAuthor($groupId = '', $type = ''){
  global $user, $company;
  $getGroup = db_select("m6connect_prochat_group_data", "mpgd")
            ->fields("mpgd", array("id", "title"))
            ->condition("id", $groupId, '!=')
            ->condition('service_type', $type)
            ->condition('author_id', $user->uid)
            ->condition('cid', $company->nid)
            ->execute()->fetchAll();
  return $getGroup;
}
/*
 *  function to get company user username and realname
 */
function _get_user_names_by_group_company_nid($cmpNid) {
  if (is_numeric ( $cmpNid )) {
    $query = db_select ( 'users', 'u' );
    $query->join ( 'og_membership', 'om', 'om.etid=u.uid AND om.entity_type=:entityType', array (':entityType' => 'user'));
    $query->join ( 'realname', 'r', 'om.etid=r.uid' );
    $query->fields ( 'u', array ('uid', 'name') );
    $query->fields ( 'r', array ('realname') );
    $query->condition ( 'om.gid', $cmpNid, '=' );
    return $query->execute ()->fetchAll();
  }
  return array ();
}