<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';
/**
 * @file
 * REST API callback for status.
 */

/**
 * Menu callback for app/status/add.
 */
function app_status_add() {
  $output = array();
  // Loading user, if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  if (empty($_REQUEST['message']) && empty($_REQUEST['image_upload'])) {
    // If no image or status recieved.
    $output['message'] = t('No content to store.');
    drupal_json_output($output);
    drupal_exit();
  }
  // check type
  $type = 'user';
  if (!empty($_REQUEST['type'])) {
    $type = $_REQUEST['type'];
    if($type == 'company'){
      $type = 'og';
    }
  }
  // check recipient
  $recipient = $account;
  if(!empty($_REQUEST['recipient_id'])){
    $recipient_id = $_REQUEST['recipient_id'];
    $recipient = node_load($recipient_id);
  }
  // If we have status to save.
  $output = array();
  if (!empty($_REQUEST['message'])) {
    $output['success'] = FALSE;
    $output['message'] = t('Status could not be saved.');    
    // Getting message.
    $message = $_REQUEST['message'];
    if(isset($_REQUEST['s_id']) && !empty($_REQUEST['s_id'])){
      $statusId = $_REQUEST['s_id'];
      $type = 'user';
      $loadStatus = statuses_load($statusId);
      $account = user_load($loadStatus->sender);
      if($loadStatus->type == 'user'){
        $recipient = user_load($loadStatus->recipient);
      }
      else{
        $recipient = node_load($loadStatus->recipient); 
      }      
      $status = statuses_save_status($recipient, $type, $message, $account, array());      
      if ($status->sid) {
        // get sharer post file
        $getFile = db_select('fbsmp')
                ->fields('fbsmp')
                ->condition('sid', $statusId, '=')
                ->execute()->fetchAssoc();
        if(!empty($getFile)){
          // save file to new post
          db_insert('fbsmp')
            ->fields(array(
              'sid' => $status->sid,
              'type' => $getFile['type'],
              'data' => $getFile['data'],
            ))
            ->execute();
        }
        $status_data = _get_status_data_prepared($account, $status->sid);
        $output['success'] = TRUE;
        $output['message'] = t('Status Saved successfully.');
        $output['status'] = $status_data;        
      }
    }
    else{
      // Trying to save new status.
      // @see statuses.module.
      $status = statuses_save_status($recipient, $type, $message, $account, array());
      if ($status->sid) {  
        $status_data = _get_status_data_prepared($account);        
        $output['success'] = TRUE;
        $output['message'] = t('Status Saved successfully.');
        $output['status'] = $status_data;
      }
    }    
  }
  // If there is an image, then handling it.
  if (!empty($_REQUEST['image_upload']) && $_REQUEST['image_upload'] == 'image_upload') {
    if (!empty($_FILES['file']['name'])) {
      // If file is not uploaded, producing error.
      $array = array();
      $array['name']['upload'] = $_FILES['file']['name'];
      $array['type']['upload'] = $_FILES['file']['type'];
      $array['tmp_name']['upload'] = $_FILES['file']['tmp_name'];
      $array['error']['upload'] = $_FILES['file']['error'];
      $array['size']['upload'] = $_FILES['file']['size'];
      $_FILES['files'] = $array;
      $file = file_save_upload('upload', array('file_validate_extensions' => array('png gif jpg jpeg')), 'private://app_uploads/');
      // Loading file again, and making it permanent.
      if ($file && $file_new = file_load($file->fid)) {
        $file_new->status = 1;
        if ($file_new_save = file_save($file_new)) {
          $new_uri = $file_new_save->uri;
          $new_full_url = file_create_url($new_uri);
          $unser_data = array('fid' => $file->fid);
          $data = serialize($unser_data);          
          if (!empty($status) && !empty($status->sid)) {
            // If we have status along with this image, then we have status id
            // of it.
            // Trying to save a record of image.
            db_insert('fbsmp')
              ->fields(array(
                'sid' => $status->sid,
                'type' => 'photo',
                'data' => $data,
              ))
              ->execute();
            // Getting status data again.
            $status_data = _get_status_data_prepared($account);
            $output['status'] = $status_data;
          }
          else {
            // If we have only image to upload, then also we need to save a blank
            // message in the DB.
            $options = array('discard blank statuses' => FALSE, 'discard duplicates' => FALSE,);
            if (empty($type)) {
              $type = !empty($_REQUEST['type']) ? $_REQUEST['type'] : 'user';
            }
            $message = '';
            $blank_status = statuses_save_status($recipient, $type, $message, $account, $options);
            if (!empty($blank_status->sid)) {
              // It means a blank status has been created for this image.
              $status_data = _get_status_data_prepared($account);
              // Trying to save a record of image.
              db_insert('fbsmp')
                ->fields(array(
                  'sid' => $blank_status->sid,
                  'type' => 'photo',
                  'data' => $data,
                ))
                ->execute();
              $output['success'] = TRUE;
              $output['message'] = t('Status Saved successfully.');
              $output['status'] = $status_data;
            }
          }
        }
      }
    }
  }

  drupal_json_output($output);
  drupal_exit();
}

/**
 * Function to return Status list, for a user.
 */
function get_status_list() {
  // Loading user if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }

  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );

  $starts = 0;
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $starts = $_REQUEST['start_range'];
  }

  $results['feeds'] = _get_status_data_prepared($account, $starts);

  // connection spotlight for suggestion
  $results['suggestion'] = connection_spotlight(1, $starts);

  if (empty($results)) {
    if (!empty($_REQUEST['status_id']) && $_REQUEST['status_id'] < 0) {
      $output['message'] = t('No statuses posted yet.');
    }
    if (!empty($_REQUEST['status_id']) && $_REQUEST['status_id'] > 0) {
      $output['message'] = t('No more content available.');
    }
  }
  else if((count($results['feeds']) < 1) && (count($results['suggestion']) < 1)){
    $output['success'] = FALSE;
    $output['message'] = t('No more content available.');
  }
  else {
    $output['success'] = TRUE;
    $output['message'] = t('Data retrieved successfully.');
    $output['data'] = $results;
  }

  drupal_json_output($output);
  drupal_exit();
}

/**
 * 
 * function for returning list of connections on the basis of user id 
 * 
 * */  
function get_connections_list() {
  // Loading user if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );  
  $connection_list = array();
  $connections = array();
  $companies_detail = array();
  $conpanies_list = array();
  $connections_result_list = array();
  $connetion_arr = array();  
  //Getting connection categories of user.    
  $connections = m6connect_misc_get_groups_by_ownerid($account->uid, 'connection_categories'); 
  foreach($connections as  $connection) {
    $connetion_arr['title'] = $connection->title;
    $connetion_arr['connection_id'] = $connection->nid;
    $connetion_arr['field_type_of_company_value'] = 'user';
    if (!empty($connection->field_type_of_company_value )) {
      $connetion_arr['field_type_of_company_value'] = $connection->field_type_of_company_value ; 
    }      
    if (!empty( $connection->field_main_location_grp_target_id )) {
      $connetion_arr['field_main_location_grp_target_id'] = $connection->field_main_location_grp_target_id ;     
    }    
    if (!empty($connection->group_access_value )) {
      $connetion_arr['group_access_value'] = $connection->group_access_value ;     
    }    
    $connections_result_list[] = $connetion_arr;    
  }  
  //Getting companies list by uid    
  $companies_detail = m6connect_misc_get_user_all_companies($account->uid);
  
  //removing user's default(individual) company. 
  $companies_result_list = array();
  foreach($companies_detail as $company) {
    if ($company->field_type_of_company_value == "company") {
      $conpanies_list['title'] = $company->title; 
      $conpanies_list['connection_id'] = $company->nid ;
      
       // Removing null fields
      if (!empty($company->field_type_of_company_value )) {
        $conpanies_list['field_type_of_company_value'] = $company->field_type_of_company_value; 
      }
      
      if (!empty($company->field_main_location_grp_target_id)) {
        $conpanies_list['field_main_location_grp_target_id'] = $company->field_main_location_grp_target_id ;     
      }
      
      if (!empty($company->group_access_value )) {
        $conpanies_list['group_access_value'] = $company->group_access_value ;     
      }
      
    }
    $companies_result_list[] = $conpanies_list;
  }
    
  if (empty($connections_result_list) && empty($companies_result_list)) {
    $output['success'] = false; 
    $output['message'] = t('No connections found, try again later'); 
  } 
  else {
    $connection_list['groups'] = $connections_result_list;
    $connection_list['colleague'] = $companies_result_list; 
    
    $output['success'] = TRUE;
    $output['message'] = t('Connections retrieved successfully.');
    $output['data'] = $connection_list;   
  }      
  drupal_json_output($output);
  drupal_exit();
}
/**
 * 
 * function for save feed comment on dashboard 
 * 
 * */
function save_feed_comment(){
  // Loading user if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if(isset($_REQUEST['status_id']) && !empty($_REQUEST['status_id'])){
    $sid = $_REQUEST['status_id'];
    if(isset($_REQUEST['comment']) && !empty($_REQUEST['comment'])){
      $comment = $_REQUEST['comment'];
      $data = fbss_comments_save_comment($sid, $comment, $_REQUEST['user_id']);
      if(!empty($data)){
        $output['success'] = TRUE;
        $output['message'] = t('Comment saved successfully.');
        $output['data'] = $data;
      }
      else{
        $output['success'] = false; 
        $output['message'] = t('Failed to save comment');
      }
    }
    else{
      $output['success'] = false; 
      $output['message'] = t('Comment should not be blank');
    }
  }
  else{
    $output['success'] = false; 
    $output['message'] = t('Status id should not be blank');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * 
 * function for get all feed comment from status id on dashboard 
 * 
 * */
function get_all_comment(){
  // Loading user if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if(isset($_REQUEST['status_id']) && !empty($_REQUEST['status_id'])){
    $sid = $_REQUEST['status_id'];
    $comList = db_select('fbss_comments', 'fc')
              ->fields('fc')
              ->condition('sid', $sid, '=')
              ->execute()->fetchAll();
    if(!empty($comList)){
      $data = array();
      foreach ($comList as $key => $value) {
        $user = user_load($value->uid);
        if (!empty($user->field_first_name['und'][0]['value'])) {
          $firstname = $user->field_first_name['und'][0]['value'];
        }
        if (!empty($user->field_middle_name['und'][0]['value'])) {
          $middlename = $user->field_middle_name['und'][0]['value'] . ' ';
        }
        if (!empty($user->field_last_name['und'][0]['value'])) {
          $lastname = $user->field_last_name['und'][0]['value'];
        }
        $realname = $firstname . ' ' . $middlename . $lastname;
        if (!empty($user->field_user_profile_photo['und'][0]['uri'])) {
          $picture = file_create_url($user->field_user_profile_photo['und'][0]['uri']);
        }
        $data[$key]['name'] = ucwords($realname);
        $data[$key]['pic'] = $picture;
        $data[$key]['user_id'] = $value->uid;
        $data[$key]['comment_date'] = date('Y-m-d H:i:s', $value->created);
        $data[$key]['comment'] = $value->comment;
      }
      $output['success'] = TRUE;
      $output['message'] = t('Comment list');
      $output['data'] = array($data);
    }
    else{
      $output['success'] = false; 
      $output['message'] = t('No comment');
    }
  }
  else{
    $output['success'] = false; 
    $output['message'] = t('Status id should not be blank');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * 
 * function for edit status from status id on dashboard 
 * 
 * */
function edit_status(){
  // Loading user if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if(isset($_REQUEST['status_id']) && !empty($_REQUEST['status_id'])){
    $sid = $_REQUEST['status_id'];
    if(isset($_REQUEST['message']) && !empty($_REQUEST['message'])){
      $status = statuses_edit_status(statuses_load($sid), $_REQUEST['message']);
      if(!empty($status)){
        $output['success'] = TRUE;
        $output['message'] = t('Status successfully updated.');
        $output['data'] = $status->message;
      }
      else{
        $output['success'] = false; 
        $output['message'] = t('Failed to update status');
      }
    }
    else{
      $output['success'] = false; 
      $output['message'] = t('Message should not be blank');
    }
  }
  else{
    $output['success'] = false; 
    $output['message'] = t('Status id should not be blank');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * 
 * function for delete status from status id on dashboard 
 * 
 * */
function delete_status(){
  // Loading user if not loaded.
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if(isset($_REQUEST['status_id']) && !empty($_REQUEST['status_id'])){
    $sid = $_REQUEST['status_id'];
    statuses_delete_status($sid);
    $output['success'] = TRUE;
    $output['message'] = t('Status successfully deleted.');
    $output['data'] = 1;
  }
  else{
    $output['success'] = false; 
    $output['message'] = t('Status id should not be blank');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * 
 * function for bumpit status from status id on dashboard 
 * 
 * */
function bumpit_status(){
  // Loading user if not loaded.
  $uid = $_REQUEST['user_id'];
  if (empty($account)) {    
    $account = user_load($uid);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if(isset($_REQUEST['status_id']) && !empty($_REQUEST['status_id'])){
    $sid = $_REQUEST['status_id'];    
    $commads = array();
    $statuses = statuses_load($sid);
    if(isset($_REQUEST['action']) && !empty($_REQUEST['action'])){
      $action = $_REQUEST['action'];
      switch ($action) {
        case 'like':
          $db_insert = array(
            'sid' => $sid,
            'uid' => $uid,
            'created' => time(),
          );
          $result = db_insert('fb_likes')->fields($db_insert)->execute();
          $out_put = m6connect_dashboard_get_like_link($uid, $sid);
          /** **notification*** */
          $m6connect_notification_table_exist = db_table_exists('m6connect_notification');
          if ($m6connect_notification_table_exist) {
            $m6connect_notification = array(
              'type' => 'bumpit_status',
              'event' => $statuses->type,
              'entity_id' => $sid,
              'company_nid' => '',
              'message' => 'like',
              'request_from' => $uid,
              'request_to' => $statuses->sender,
              'status' => 1,
              'timestamp' => time(),
            );
            entity_save('m6connect_notification', (object) $m6connect_notification);
          }
          $output['success'] = TRUE;
          $output['message'] = t('Bumpit Successfully.');
          $output['data'] = 'bumpit';
          /** **notification*** */
          break;
        case 'unlike':
          $num_deleted = db_delete('fb_likes')
                  ->condition('sid', $sid)
                  ->condition('uid', $uid)
                  ->execute();
          $out_put = m6connect_dashboard_get_like_link($uid, $sid);
            /** **notification*** */
          $m6connect_notification_table_exist = db_table_exists('m6connect_notification');
          if ($m6connect_notification_table_exist) {
            $m6connect_notification = array(
                'type' => 'bumpit_status',
                'event' => $statuses->type,
                'entity_id' => $sid,
                'company_nid' => '',
                'message' => 'unlike',
                'request_from' => $uid,
                'request_to' => $statuses->sender,
                'status' => 1,
                'timestamp' => time(),
            );
            entity_save('m6connect_notification', (object) $m6connect_notification);
          }
          $output['success'] = TRUE;
          $output['message'] = t('Unbumpit Successfully.');
          $output['data'] = 'unbumpit';
          /** **notification*** */
          break;
        default:
          break;
      }
    }
    else{
      $output['success'] = false; 
      $output['message'] = t('Action should not be blank');
    }
  }
  else{
    $output['success'] = false; 
    $output['message'] = t('Status id should not be blank');
  }
  drupal_json_output($output);
  drupal_exit();
}
/** 
 * function for connection spotlight api on dashboard  
 */
function connection_spotlight($inside = null, $starts = 0){
  $uid = $_REQUEST['user_id'];  
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $starts = $_REQUEST['start_range'];
  }
  $getConData = db_select('node', 'n');
  $getConData->leftJoin('field_data_field_keywords', 'fdfk', 'fdfk.entity_id = n.nid');
  $getConData->leftJoin('users', 'u', 'u.uid = n.uid'); 
  $getConData->leftjoin('realname','r','r.uid = n.uid');
  $getConData->leftJoin('field_data_field_job_titles', 'fdfjt', 'fdfjt.entity_id = n.uid');  
  $getConData->leftjoin('field_data_field_user_profile_photo', 'ufp', 'ufp.entity_id = n.uid');
  $getConData->leftjoin('file_managed', 'fmu', 'fmu.fid = ufp.field_user_profile_photo_fid');
  $getConData->fields('n', array('uid'));
  $getConData->fields('u', array('created'));
  $getConData->fields('r', array('realname'));
  $getConData->fields('fmu', array('uri'));
  $getConData->fields('fdfjt', array('field_job_titles_target_id'));
  $getConData->fields('fdfk', array('field_keywords_value'));
  $getConData->condition('n.type', 'organization', '=');
  $getConData->range($starts, 10);
  $result = $getConData->execute()->fetchAll();
  $mainData = array();
  if(!empty($result)){        
    foreach ($result as $key => $value) {
      $mainData[$key]['name'] = $value->realname;
      $mainData[$key]['keyword'] = !empty($value->field_keywords_value) ? $value->field_keywords_value : '';
      $mainData[$key]['created'] = date('F j, Y', strtotime($value->created));
      $mainData[$key]['photo'] = '';
      if(!empty($value->uri)){
        $mainData[$key]['photo'] = file_create_url($value->uri);  
      }
      $jobtitle = '';
      if(!empty($value->field_job_titles_target_id)){
        $term = taxonomy_term_load($value->field_job_titles_target_id);
        $jobtitle = $term->name;
      }      
      $mainData[$key]['jobtitle'] = $jobtitle;
    }    
  }
  if(!empty($inside)){
    return $mainData;
  }
  else{
    $output['success'] = TRUE;
    $output['message'] = 'Record found';
    $output['connection'] = $mainData;
    drupal_json_output($output);
    drupal_exit();
  }  
}
/**
 * 
 * function for user notification
 * 
 * */ 
function user_notification(){
  $uid = $_REQUEST['user_id'];
  $user = user_load($uid);
  $starts = 0;
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $starts = $_REQUEST['start_range'];
  }
  $usrco = _get_user_companies($user);
  $m6_noti_query = db_select('m6connect_notification', 'm6noti');
  $m6_noti_query->leftjoin('node', 'entity_node','entity_node.nid = m6noti.entity_id');
  $m6_noti_query->leftjoin('node', 'company_node','company_node.nid = m6noti.company_nid');
  $m6_noti_query->leftjoin('field_data_field_user_profile_photo', 'req_user_photo','req_user_photo.entity_id = m6noti.request_from');
  $m6_noti_query->leftjoin('file_managed', 'req_user_photo_file','req_user_photo_file.fid = req_user_photo.field_user_profile_photo_fid');
  $m6_noti_query->leftjoin('realname', 'reqfrom_user_realname','reqfrom_user_realname.uid = m6noti.request_from');
  $m6_noti_query->leftjoin('realname', 'reqto_user_realname','reqto_user_realname.uid = m6noti.request_to');
  $m6_noti_query->leftjoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = m6noti.entity_id');  
  $m6_noti_query->fields('m6noti');
  $m6_noti_query->addField('entity_node','nid','entity_node_nid');
  $m6_noti_query->addField('entity_node','type','entity_node_type');
  $m6_noti_query->addField('entity_node','title','entity_node_title');
  $m6_noti_query->addField('company_node','title','company_node_title');
  $m6_noti_query->addField('req_user_photo_file','uri','user_profile_photo_uri');
  $m6_noti_query->addField('reqfrom_user_realname','realname','reqfrom_realname');
  $m6_noti_query->addField('reqto_user_realname','realname','reqto_realname');
  $m6_noti_query->addField('fdfct','field_cm_type_value','fdfct_cm_type');
  $m6_noti_query->condition('m6noti.request_to', $uid);
  $m6_noti_query->condition('m6noti.status', 1);
  $m6_noti_query->orderBy('m6noti.status', "DESC");
  $m6_noti_query->orderBy('m6noti.timestamp', "DESC");
  $m6_noti_query->extend('PagerDefault');
  $m6_noti_query->range($starts, 10);
  $m6_noti = $m6_noti_query->execute()->fetchAll();
  if(!empty($m6_noti)){
    $notification_data = array();
    $i = 0;
    foreach ($m6_noti as $m6_noti_data) {
      if (isset($m6_noti_data->entity_id) && $m6_noti_data->entity_id != '') {
        $is_node = $is_people = 0;
        $unread = 'unread';
        $notification_count0 ++;      
        $request_from_user = user_load($m6_noti_data->request_from);
        $has_user_image = (!empty($m6_noti_data->user_profile_photo_uri) ? image_style_url('dashboard-user-feed-pic-img_52_52', $m6_noti_data->user_profile_photo_uri) : '');
        $noti_target_url = '';
        $notification_data[$i]['profile_type'] = '';
        $notification_data[$i]['entity_id'] = '';
        $notification_data[$i]['message'] = '';
        $notification_data[$i]['time'] = '';
        $notification_data[$i]['image'] = '';
        $notification_data[$i]['remove_url'] = '';
        if (($m6_noti_data->type == 'people' || $m6_noti_data->type == 'company_status') && $m6_noti_data->event == 'join') {
          //$noti_target_url = 'type=people&status=pending&company_id='.$m6_noti_data->company_nid;
          $notification_data[$i]['profile_type'] = 'people-pending';
          $notification_data[$i]['entity_id'] = $m6_noti_data->company_nid;
          $is_people = 1;
        }
        elseif ($m6_noti_data->event == 'feedback' && $m6_noti_data->type == 'vendor_manager_request') {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
        }
        elseif ($m6_noti_data->event == 'feedback-reminder' && $m6_noti_data->type == 'vendor_manager_request') {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
        }
        elseif ($m6_noti_data->event == 'feedback' && $m6_noti_data->type == 'company_admin_request') {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
        }
        elseif ($m6_noti_data->event == 'feedback-reminder' && $m6_noti_data->type == 'company_admin_request') {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
        }
        elseif (($m6_noti_data->event == 'note' || $m6_noti_data->event == 'ratings') && $m6_noti_data->type == 'company_rating_request') {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
        }
        elseif (($m6_noti_data->event == 'notes' || $m6_noti_data->event == 'ratings') && ($m6_noti_data->type == 'company_notes' || $m6_noti_data->type == 'vendor_notes')) {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
        }
        elseif ($m6_noti_data->type == 'share_status' && $m6_noti_data->event == 'og' && $m6_noti_data->entity_id == 0) {
          //$noti_target_url = 'type=dashboard';
          $notification_data[$i]['profile_type'] = 'dashboard';
        }
        elseif (($m6_noti_data->type == 'share_comment' || $m6_noti_data->type == 'share_status') && $m6_noti_data->event == 'og' || $m6_noti_data->event == 'user') {
          //$noti_target_url = 'type=statuses&entity_id='.$m6_noti_data->entity_id;
          $notification_data[$i]['profile_type'] = 'statuses';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_id;
        }
        elseif ($m6_noti_data->type == 'share_status' && $m6_noti_data->event == 'user' && $m6_noti_data->company_nid == 0) {
          $noti_target_url = 'type=user&request='.$m6_noti_data->request_to;
          $notification_data[$i]['profile_type'] = 'user';
          $notification_data[$i]['entity_id'] = $m6_noti_data->request_to;
        }
        elseif ($m6_noti_data->type == 'bumpit_status' && ($m6_noti_data->event == 'og' || $m6_noti_data->event == 'user')) {
          //$noti_target_url = 'type=statuses&entity_id='.$m6_noti_data->entity_id;
          $notification_data[$i]['profile_type'] = 'statuses';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_id;
        }
        elseif ($m6_noti_data->type == 'relationship' && $m6_noti_data->event == 'request') {
          //$noti_target_url = 'type=user&request='.$m6_noti_data->request_from;
          $notification_data[$i]['profile_type'] = 'user';
          $notification_data[$i]['entity_id'] = $m6_noti_data->request_from;
        }
        elseif ($m6_noti_data->type == 'user' && ($m6_noti_data->event == 'bookmark' || $m6_noti_data->event == 'unbookmark')) {
          //$noti_target_url = 'type=user&request='.$m6_noti_data->entity_id;
          $notification_data[$i]['profile_type'] = 'user';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_id;
        }
        elseif ($m6_noti_data->type == 'private_message' && $m6_noti_data->event == 'message_sent')
        {
          //$noti_target_url = 'type=messages_view&entity_id='.$m6_noti_data->entity_id;
          $notification_data[$i]['profile_type'] = 'messages_view';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_id;
        }
        elseif ($m6_noti_data->type == 'prochat' && $m6_noti_data->event == 'invite') {
          //$noti_target_url = 'type=prochat';
          $notification_data[$i]['profile_type'] = 'prochat';
        }
        elseif ($m6_noti_data->type == 'm6id' && $m6_noti_data->event == 'project_invitations') {
          //$noti_target_url = 'type=onboarding_projectlist';
          $notification_data[$i]['profile_type'] = 'onboarding_projectlist';
        }
        elseif ($m6_noti_data->type == 'm6id' && $m6_noti_data->event == 'project_submit_employee')
        {
          //$noti_target_url = 'type=onboarding_in-process';
          $notification_data[$i]['profile_type'] = 'onboarding_in-process';
        }
        elseif ($m6_noti_data->type == 'relationship' && $m6_noti_data->event == 'request') {
          //$noti_target_url = 'type=user&request='.$m6_noti_data->request_from;
          $notification_data[$i]['profile_type'] = 'user';
          $notification_data[$i]['entity_id'] = $m6_noti_data->request_from;
        }
        elseif ($m6_noti_data->type == 'relationship' && $m6_noti_data->event == 'approve') {
          //$noti_target_url = 'type=user&request='.$m6_noti_data->request_from;
          $notification_data[$i]['profile_type'] = 'user';
          $notification_data[$i]['entity_id'] = $m6_noti_data->request_from;
        }
        elseif (isset($m6_noti_data->entity_node_nid) && is_numeric($m6_noti_data->entity_node_nid)) {
          //$noti_target_url = 'type=node&nid='.$m6_noti_data->entity_node_nid;
          $notification_data[$i]['profile_type'] = 'node';
          $notification_data[$i]['entity_id'] = $m6_noti_data->entity_node_nid;
          $is_node = 1;
        }
            
        $notification_data[$i]['image'] = $has_user_image;
        $output2 = notification_message($m6_noti_data, $m6_noti_data->type, $m6_noti_data->event, $m6_noti_data->request_to, $m6_noti_data->request_from, $m6_noti_data->entity_id, $m6_noti_data->company_nid, $m6_noti_data->message);
        $notification_data[$i]['time'] = format_interval((time() - $m6_noti_data->timestamp), 1);
        $company_nid = $m6_noti_data->company_nid;
        if ($is_node) {
          $gopath = '';
          if (!in_array($m6_noti_data->entity_node_type, array('organization'))) {
            if (isset($company_nid) && $company_nid != '') {
              if (in_array($company_nid, $usrco)) {
                //$gopath = 'type=switch&company_id='.$company_nid;
                $notification_data[$i]['profile_type'] = 'switch';
                $notification_data[$i]['entity_id'] = $company_nid;
                $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
                //$notification_data[$i]['url'] = $gopath;
              }
            }
            else {
              //$gopath = $noti_target_url;
              $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
              //$notification_data[$i]['url'] = $gopath;
            }
          } else {
            //$gopath = $noti_target_url;
            $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
            //$notification_data[$i]['url'] = $gopath;
          }
        }
        elseif ($is_people) {
          if (isset($company_nid) && $company_nid != '') {
            if (($m6_noti_data->type == 'company_status') && $m6_noti_data->event == 'join') {
              $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
              //$notification_data[$i]['url'] = $noti_target_url;           
            }
            else {
              if (in_array($company_nid, $usrco)) {
                //$gopath = 'type=switch&company_id='.$company_nid.'&destination=' . $noti_target_url;
                $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
                //$notification_data[$i]['url'] = $gopath;
              }
            }
          }
          else {
            //$gopath = $noti_target_url;
            $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
            //$notification_data[$i]['url'] = $gopath;
          }
        }
        elseif ($m6_noti_data->type == 'vendor_manager_request' || $m6_noti_data->type == 'company_admin_request' || $m6_noti_data->type == 'company_rating_request' || $m6_noti_data->type == 'company_notes' || $m6_noti_data->type == 'company_ratings' || $m6_noti_data->type == 'vendor_notes' || $m6_noti_data->type == 'vendor_ratings') {
            $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
            //$notification_data[$i]['url'] = $noti_target_url;
         }
        else {
          //$gopath = $noti_target_url;
          $notification_data[$i]['message'] = (!empty($output2) ? $output2 : '');
          //$notification_data[$i]['url'] = $gopath;
        }
        if (($m6_noti_data->type == 'relationship') && ($m6_noti_data->event == 'request')) {
          $notification_data[$i]['message'] = connect_category_action_box($m6_noti_data->entity_id, $m6_noti_data->request_to, $m6_noti_data->request_from, $m6_noti_data->id);
        }
        elseif (($m6_noti_data->type == 'company_status') && $m6_noti_data->event == 'join') {
          $notification_data[$i]['remove_url'] = 'notification_remove=1&notification_id='.$m6_noti_data->id;
        }
        else {          
          $notification_data[$i]['remove_url'] = 'notification_remove=1&notification_id='.$m6_noti_data->id;         
        }        
      }
      $i++;
    }
    $output = array(
      'success' => TRUE,
      'message' => 'Notification Get successfull!',
      'data' => array_values($notification_data),
    );
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'Notification Not found',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for find people in top menu
 */
function app_find_people(){
  $user_id = $_REQUEST['user_id'];
  $start_range = 0;$mainData = $resData = array();
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $start_range = $_REQUEST['start_range'];
  }
  $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, field_data_field_last_name_field_last_name_value ASC, users_name ASC";
  if(isset($_REQUEST['sort_data']) && !empty($_REQUEST['sort_data'])){
    $sortData = $_REQUEST['sort_data'];
    if($sortData == 'state'){
      $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, users_name ASC, field_data_field_address_field_address_administrative_area ASC";
    }
    if($sortData == 'city'){
      $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, users_name ASC, field_data_field_address_field_address_locality ASC";
    }
  }
  $searchStr = '';
  if(isset($_REQUEST['search_data']) && !empty($_REQUEST['search_data'])){
    $searchData = $_REQUEST['search_data'];
    $searchStr = "AND (CONCAT_WS(' ', users.name, ' ', field_data_field_address.field_address_locality, ' ', field_data_field_address.field_address_administrative_area) LIKE '%".$searchData."%')";  
  }
  $data = db_query("SELECT users.uid AS uid, users.name AS users_name, field_data_field_user_profile_photo.field_user_profile_photo_fid AS fid, field_data_field_address.field_address_locality AS field_data_field_address_field_address_locality, field_data_field_address.field_address_administrative_area AS field_data_field_address_field_address_administrative_area, field_data_field_address.field_address_country AS field_data_field_address_field_address_country, flagging_users.entity_id AS flagging_users_entity_id, field_data_field_user_company_name.field_user_company_name_value AS field_data_field_user_company_name_field_user_company_name_v, field_data_field_last_name.field_last_name_value AS field_data_field_last_name_field_last_name_value, 'user' AS field_data_field_user_profile_photo_user_entity_type, 'user' AS field_data_field_primary_company_user_entity_type, 'user' AS field_data_field_job_titles_user_entity_type, 'user' AS field_data_field_user_title_user_entity_type, 'user' AS field_data_field_first_name_user_entity_type, 'user' AS field_data_field_last_name_user_entity_type FROM {users} users 
    LEFT JOIN {flagging} flagging_users ON users.uid = flagging_users.entity_id AND (flagging_users.fid = '11' AND flagging_users.uid = ".$user_id.") 
    LEFT JOIN {users_roles} users_roles ON users.uid = users_roles.uid AND users_roles.rid = '5' 
    LEFT JOIN {field_data_field_user_profile_photo} field_data_field_user_profile_photo ON users.uid = field_data_field_user_profile_photo.entity_id 
    LEFT JOIN {field_data_field_address} field_data_field_address ON users.uid = field_data_field_address.entity_id AND (field_data_field_address.entity_type = 'user' AND field_data_field_address.deleted = '0')
    LEFT JOIN {field_data_field_user_company_name} field_data_field_user_company_name ON users.uid = field_data_field_user_company_name.entity_id AND (field_data_field_user_company_name.entity_type = 'user' AND field_data_field_user_company_name.deleted = '0') 
    LEFT JOIN {field_data_field_last_name} field_data_field_last_name ON users.uid = field_data_field_last_name.entity_id AND (field_data_field_last_name.entity_type = 'user' AND field_data_field_last_name.deleted = '0') WHERE (( (users.status <> '0') ".$searchStr." AND (users_roles.rid IS NULL ) )) ORDER BY ".$sortStr." LIMIT ".$start_range.", 15");
  $result = $data->fetchAll();
  if(!empty($result)){
    foreach ($result as $key => $value) {
      $userData = db_select('users', 'u');
      $userData->leftJoin('realname', 'r', 'r.uid = u.uid');
      $userData->leftJoin("field_data_field_user_profile_photo", "fdfupp", "fdfupp.entity_id = u.uid");
      $userData->leftjoin('file_managed', 'fmu', 'fmu.fid = fdfupp.field_user_profile_photo_fid');
      $userData->leftJoin("field_data_field_address", "fdfa", "fdfa.entity_id = u.uid");
      $userData->leftJoin("field_data_field_primary_company", "fdfpc", "fdfpc.entity_id = u.uid");
      $userData->fields('u', array("uid", "name"));
      $userData->fields('r', array("realname"));
      $userData->fields('fmu', array('uri'));
      $userData->fields('fdfpc', array('field_primary_company_value'));
      $userData->fields('fdfa', array("field_address_country", "field_address_administrative_area", "field_address_locality"));
      $userData->condition('u.uid', $value->uid, '=');
      $innerResult = $userData->execute()->fetchAll();
      foreach ($innerResult as $uids => $resvalue) {
        $mycuserid = $resvalue->uid;
        $userName = '';
        $userName = $resvalue->name;
        if(empty($userName) && !empty($resvalue->realname)){
          $userName = $resvalue->realname;
        }
        $resData[$key]['uid'] = $resvalue->uid;
        $resData[$key]['name'] = $userName;
        $resData[$key]['image'] = (!empty($resvalue->uri) ? file_create_url($resvalue->uri) : '');
        $resData[$key]['company_name'] = '';
        $PrimaryComNId = (!empty($resvalue->field_primary_company_value) ? $resvalue->field_primary_company_value : '');
        if(!empty($PrimaryComNId)){
          $resData[$key]['company_name'] = _get_title_of_node($PrimaryComNId);
        }
        $resData[$key]['city'] = (!empty($resvalue->field_address_locality) ? $resvalue->field_address_locality : '');
        $resData[$key]['state'] = (!empty($resvalue->field_address_administrative_area) ? $resvalue->field_address_administrative_area : '');
        $Cat_OgId = _get_relationship_group($user_id,$resvalue->uid);
        $resData[$key]['connection'] = array_keys($Cat_OgId);
        $status_btn = connection_member_status_button($user_id,$mycuserid);
        $resData[$key]['button'] = $status_btn['button'];
      }
    }
    $mainData['people_data'] = (!empty($resData) ? $resData : '');
    $groupListing = m6connect_misc_get_groups_by_ownerid($user_id, 'connection_categories');
    if(!empty($groupListing)){
      $groupData = array();
      foreach ($groupListing as $key => $value) {
        $groupData[$key]['id'] = $value->nid;
        $groupData[$key]['value'] = $value->title;
      }
      $defaultGroupData = array(
                            array("id" => "find-people", "value" => "Public"),
                            array("id" => "my-connections", "value" => "My Connections")
                          );
      $mainData['group_listing'] = array_merge($defaultGroupData, $groupData);
    } 
    $output = array(
      'success' => TRUE,
      'message' => 'Data found',
      'data' => $mainData,
    );
  }  
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for find people dropdown value data in top menu
 */
function app_find_people_dropdown_value(){
  $user_id = $_REQUEST['user_id'];
  $start_range = 0;$mainData = $resData = array();
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $start_range = $_REQUEST['start_range'];
  }
  $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, field_data_field_last_name_field_last_name_value ASC, users_name ASC";
  if(isset($_REQUEST['sort_data']) && !empty($_REQUEST['sort_data'])){
    $sortData = $_REQUEST['sort_data'];
    if($sortData == 'state'){
      $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, users_name ASC, field_data_field_address_field_address_administrative_area ASC";
    }
    if($sortData == 'city'){
      $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, users_name ASC, field_data_field_address_field_address_locality ASC";
    }
  }
  $searchStr = '';
  if(isset($_REQUEST['search_data']) && !empty($_REQUEST['search_data'])){
    $searchData = $_REQUEST['search_data'];
    $searchStr = "AND (CONCAT_WS(' ', users.name, ' ', field_data_field_first_name.field_first_name_value, ' ', field_data_field_last_name.field_last_name_value) LIKE '%".$searchData."%')";      
  }
  if(isset($_REQUEST['dropdown_id']) && !empty($_REQUEST['dropdown_id'])){
    $dropdown_id = $_REQUEST['dropdown_id'];
    $data = db_query("SELECT users.uid AS uid, users.name AS users_name, field_data_field_address.field_address_locality AS field_data_field_address_field_address_locality, field_data_field_address.field_address_administrative_area AS field_data_field_address_field_address_administrative_area, field_data_field_address.field_address_country AS field_data_field_address_field_address_country, flagging_users.entity_id AS flagging_users_entity_id, field_data_field_user_company_name.field_user_company_name_value AS field_data_field_user_company_name_field_user_company_name_v, field_data_field_last_name.field_last_name_value AS field_data_field_last_name_field_last_name_value, 'user' AS field_data_field_user_profile_photo_user_entity_type, 'user' AS field_data_field_primary_company_user_entity_type, 'user' AS field_data_field_job_titles_user_entity_type, 'user' AS field_data_field_user_title_user_entity_type, 'user' AS field_data_field_first_name_user_entity_type, 'user' AS field_data_field_last_name_user_entity_type FROM {users} users LEFT JOIN {flagging} flagging_users ON users.uid = flagging_users.entity_id AND (flagging_users.fid = '11' AND flagging_users.uid = '2') LEFT JOIN {field_data_field_address} field_data_field_address ON users.uid = field_data_field_address.entity_id AND (field_data_field_address.entity_type = 'user' AND field_data_field_address.deleted = '0') LEFT JOIN {field_data_field_first_name} field_data_field_first_name ON users.uid = field_data_field_first_name.entity_id AND (field_data_field_first_name.entity_type = 'user' AND field_data_field_first_name.deleted = '0') LEFT JOIN {field_data_field_last_name} field_data_field_last_name ON users.uid = field_data_field_last_name.entity_id AND (field_data_field_last_name.entity_type = 'user' AND field_data_field_last_name.deleted = '0') LEFT JOIN {og_membership} og_membership ON users.uid = og_membership.etid AND (og_membership.entity_type = 'user' AND og_membership.entity_type = 'user') LEFT JOIN {field_data_field_user_company_name} field_data_field_user_company_name ON users.uid = field_data_field_user_company_name.entity_id AND (field_data_field_user_company_name.entity_type = 'user' AND field_data_field_user_company_name.deleted = '0') WHERE (( (og_membership.gid = ".$dropdown_id." ) )AND(( (users.status <> '0') ".$searchStr." AND( (users.uid <> ".$user_id.") )))) ORDER BY field_data_field_user_company_name_field_user_company_name_v ASC, field_data_field_last_name_field_last_name_value ASC, users_name ASC");
    $result = $data->fetchAll();
    if(!empty($result)){
      foreach ($result as $key => $value) {
        $userData = db_select('users', 'u');
        $userData->leftJoin('realname', 'r', 'r.uid = u.uid');
        $userData->leftJoin("field_data_field_user_profile_photo", "fdfupp", "fdfupp.entity_id = u.uid");
        $userData->leftjoin('file_managed', 'fmu', 'fmu.fid = fdfupp.field_user_profile_photo_fid');
        $userData->leftJoin("field_data_field_address", "fdfa", "fdfa.entity_id = u.uid");
        $userData->leftJoin("field_data_field_primary_company", "fdfpc", "fdfpc.entity_id = u.uid");
        $userData->fields('u', array("uid"));
        $userData->fields('r', array("realname"));
        $userData->fields('fmu', array('uri'));
        $userData->fields('fdfpc', array('field_primary_company_value'));
        $userData->fields('fdfa', array("field_address_country", "field_address_administrative_area", "field_address_locality"));
        $userData->condition('u.uid', $value->uid, '=');
        $innerResult = $userData->execute()->fetchAll();
        foreach ($innerResult as $uids => $resvalue) {
          $resData[$key]['uid'] = $resvalue->uid;
          $resData[$key]['name'] = $resvalue->realname;
          $resData[$key]['image'] = (!empty($resvalue->uri) ? file_create_url($resvalue->uri) : '');
          $resData[$key]['company_name'] = '';
          $PrimaryComNId = (!empty($resvalue->field_primary_company_value) ? $resvalue->field_primary_company_value : '');
          if(!empty($PrimaryComNId)){
            $resData[$key]['company_name'] = _get_title_of_node($PrimaryComNId);
          }
          $resData[$key]['city'] = (!empty($resvalue->field_address_locality) ? $resvalue->field_address_locality : '');
          $resData[$key]['state'] = (!empty($resvalue->field_address_administrative_area) ? $resvalue->field_address_administrative_area : '');
          $Cat_OgId = _get_relationship_group($user_id,$resvalue->uid);
          $resData[$key]['connection'] = array_keys($Cat_OgId);
          $status_btn = connection_member_status_button($user_id,$resvalue->uid);
          $resData[$key]['button'] = $status_btn['button'];
        }
      }
      $mainData['people_data'] = (!empty($resData) ? $resData : '');
      $groupListing = m6connect_misc_get_groups_by_ownerid($user_id, 'connection_categories');
      if(!empty($groupListing)){
        $groupData = array();
        foreach ($groupListing as $key => $value) {
          $groupData[$key]['id'] = $value->nid;
          $groupData[$key]['value'] = $value->title;
        }
        $defaultGroupData = array(
                              array("id" => "find-people", "value" => "Public"), array("id" => "my-connections", "value" => "My Connections"));
        $mainData['group_listing'] = array_merge($defaultGroupData, $groupData);
      } 
      $output = array(
        'success' => TRUE,
        'message' => 'Data found',
        'data' => $mainData,
      );
    }
    else{
      $output = array(
        'success' => FALSE,
        'message' => 'Data not found in this category',
      );
    }
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'Dropdown id can\'t be null',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for my connection value in find people dropdown
 */
function app_find_people_get_my_connection(){
  $user_id = $_REQUEST['user_id'];
  $start_range = 0;$mainData = $resData = array();
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $start_range = $_REQUEST['start_range'];
  }
  $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, field_data_field_last_name_field_last_name_value ASC, users_name ASC";
  if(isset($_REQUEST['sort_data']) && !empty($_REQUEST['sort_data'])){
    $sortData = $_REQUEST['sort_data'];
    if($sortData == 'state'){
      $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, users_name ASC, field_data_field_address_field_address_administrative_area ASC";
    }
    if($sortData == 'city'){
      $sortStr = "field_data_field_user_company_name_field_user_company_name_v ASC, users_name ASC, field_data_field_address_field_address_locality ASC";
    }
  }
  $searchStr = '';
  if(isset($_REQUEST['search_data']) && !empty($_REQUEST['search_data'])){
    $searchData = $_REQUEST['search_data'];
    $searchStr = "AND (CONCAT_WS(' ', users.name, ' ', field_data_field_address.field_address_locality, ' ', field_data_field_address.field_address_administrative_area) LIKE '%".$searchData."%')";  
  }
  $data = db_query("SELECT users.uid AS uid, users.name AS users_name, field_data_field_address.field_address_locality AS field_data_field_address_field_address_locality, field_data_field_address.field_address_administrative_area AS field_data_field_address_field_address_administrative_area, field_data_field_address.field_address_country AS field_data_field_address_field_address_country, flagging_users.entity_id AS flagging_users_entity_id, field_data_field_user_company_name.field_user_company_name_value AS field_data_field_user_company_name_field_user_company_name_v, field_data_field_last_name.field_last_name_value AS field_data_field_last_name_field_last_name_value, 'user' AS field_data_field_user_profile_photo_user_entity_type, 'user' AS field_data_field_primary_company_user_entity_type, 'user' AS field_data_field_job_titles_user_entity_type, 'user' AS field_data_field_user_title_user_entity_type, 'user' AS field_data_field_first_name_user_entity_type, 'user' AS field_data_field_last_name_user_entity_type FROM {users} users LEFT JOIN {flagging} flagging_users ON users.uid = flagging_users.entity_id AND (flagging_users.fid = '11' AND flagging_users.uid = ".$user_id.") LEFT JOIN {user_relationships} user_relationships ON users.uid = user_relationships.requestee_id LEFT JOIN {field_data_field_address} field_data_field_address ON users.uid = field_data_field_address.entity_id AND (field_data_field_address.entity_type = 'user' AND field_data_field_address.deleted = '0')LEFT JOIN {field_data_field_user_company_name} field_data_field_user_company_name ON users.uid = field_data_field_user_company_name.entity_id AND (field_data_field_user_company_name.entity_type = 'user' AND field_data_field_user_company_name.deleted = '0') LEFT JOIN {field_data_field_last_name} field_data_field_last_name ON users.uid = field_data_field_last_name.entity_id AND (field_data_field_last_name.entity_type = 'user' AND field_data_field_last_name.deleted = '0') WHERE (( (users.status <> '0') ".$searchStr." AND (user_relationships.approved = '1') )AND( ((user_relationships.requester_id = 2 OR user_relationships.requestee_id = 2)) )) ORDER BY ".$sortStr);
  $result = $data->fetchAll();
  if(!empty($result)){
    $i = 0;
    foreach ($result as $key => $value) {
      if($value->uid == $user_id){
        continue;
      }
      $userData = db_select('users', 'u');
      $userData->leftJoin('realname', 'r', 'r.uid = u.uid');
      $userData->leftJoin("field_data_field_user_profile_photo", "fdfupp", "fdfupp.entity_id = u.uid");
      $userData->leftjoin('file_managed', 'fmu', 'fmu.fid = fdfupp.field_user_profile_photo_fid');
      $userData->leftJoin("field_data_field_address", "fdfa", "fdfa.entity_id = u.uid");
      $userData->leftJoin("field_data_field_primary_company", "fdfpc", "fdfpc.entity_id = u.uid");
      $userData->leftJoin("field_data_field_user_title", "fdfut", "fdfut.entity_id = u.uid");
      $userData->fields('u', array("uid"));
      $userData->fields('r', array("realname"));
      $userData->fields('fdfut', array("field_user_title_value"));
      $userData->fields('fmu', array('uri'));
      $userData->fields('fdfpc', array('field_primary_company_value'));
      $userData->fields('fdfa', array("field_address_country", "field_address_administrative_area", "field_address_locality"));
      $userData->condition('u.uid', $value->uid, '=');
      $innerResult = $userData->execute()->fetchAll();
      foreach ($innerResult as $uids => $resvalue) {
        $resData[$i]['uid'] = $resvalue->uid;
        $resData[$i]['name'] = $resvalue->realname;
        $resData[$i]['user_title'] = (!empty($resvalue->field_user_title_value) ? $resvalue->field_user_title_value : '');
        $resData[$i]['image'] = (!empty($resvalue->uri) ? file_create_url($resvalue->uri) : '');
        $resData[$i]['company_name'] = '';
        $PrimaryComNId = (!empty($resvalue->field_primary_company_value) ? $resvalue->field_primary_company_value : '');
        if(!empty($PrimaryComNId)){
          $resData[$i]['company_name'] = _get_title_of_node($PrimaryComNId);
        }
        $resData[$i]['city'] = (!empty($resvalue->field_address_locality) ? $resvalue->field_address_locality : '');
        $resData[$i]['state'] = (!empty($resvalue->field_address_administrative_area) ? $resvalue->field_address_administrative_area : '');
        $Cat_OgId = _get_relationship_group($user_id,$resvalue->uid);
        $resData[$i]['connection'] = array_keys($Cat_OgId);
        $status_btn = connection_member_status_button($user_id,$resvalue->uid);
        $resData[$key]['button'] = $status_btn['button'];
      }
      $i++;
    }
    $mainData['people_data'] = (!empty($resData) ? $resData : '');
    $groupListing = m6connect_misc_get_groups_by_ownerid($user_id, 'connection_categories');
    if(!empty($groupListing)){
      $groupData = array();
      foreach ($groupListing as $key => $value) {
        $groupData[$key]['id'] = $value->nid;
        $groupData[$key]['value'] = $value->title;
      }
      $defaultGroupData = array(
                            array("id" => "find-people", "value" => "Public"), array("id" => "my-connections", "value" => "My Connections"));
      $mainData['group_listing'] = array_merge($defaultGroupData, $groupData);
    } 
    $output = array(
      'success' => TRUE,
      'message' => 'Data found',
      'data' => $mainData,
    );
  }  
  drupal_json_output($output);
  drupal_exit();
}
/** 
 *function for get top menu companies data
 */
function app_companies_data_list(){
  $result = company_query()->fetchAll();
  if(!empty($result)){
    $mainData = array();
    foreach ($result as $key => $value) {
      $node = node_load($value->nid);
      $cirtificate = m6connect_company_get_circtficat($node);
    }
  }
  drupal_json_output($result);
  drupal_exit();
}
/**
 * function to update status in company list - favorite, follow, bookmark
 **/
function app_update_company_flag_status(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['flag_name']) && !empty($_REQUEST['flag_name'])){
      $flagName = $_REQUEST['flag_name'];
      if(isset($_REQUEST['flag_status']) && !empty($_REQUEST['flag_status'])){
        $flagStatus = $_REQUEST['flag_status'];
        $fid = $flaggingId = '';
        // get fid from flag table
        $getFid = db_select('flag', 'f')
                ->fields('f', array("fid"))
                ->condition('name', $flagName, '=')
                ->execute()->fetchAssoc();
        if(!empty($getFid)){
          $fid = $getFid['fid'];
          // get flagging id from flagging table to check is there any entry for nid
          $getFlaggingId = db_select('flagging', 'fl')
                        ->fields('fl', array("flagging_id"))
                        ->condition('fid', $fid, '=')
                        ->condition('entity_id', $company_id, '=')
                        ->execute()->fetchAssoc();
          if(!empty($getFlaggingId)){
            $flaggingId = $getFlaggingId['flagging_id'];
          }
          // insert into flagging table
          if(($flagStatus == 'flag')){
            if(empty($flaggingId)){
              db_insert('flagging')
              ->fields(array(
                'fid' => $fid,
                'entity_type' => 'node',
                'entity_id' => $company_id,
                'uid' => $user_id,
                'sid' => 0,
                'timestamp' => time()
              ))
              ->execute();
              $output['success'] = TRUE;
              $output['message'] = 'Action successfully updated';
              $output['data'] = 1;
            }
            else{
              $output['success'] = FALSE;
              $output['message'] = 'Action already exist';
            }
          }          
          // delete from flagging table
          if(($flagStatus == 'unflag')){
            if(!empty($flaggingId)){
              $deleted = db_delete('flagging')
                      ->condition('fid',$fid,'=')
                      ->condition('entity_id',$company_id,'=')
                      ->condition('uid',$user_id,'=')
                      ->execute();
              $output['success'] = TRUE;
              $output['message'] = 'Action successfully updated';
              $output['data'] = 1;
            }
            else{
              $output['success'] = FALSE;
              $output['message'] = 'Action already exist';
            }
          }
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = 'Wronge flag name';
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Flag status can\'t be empty';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Flag name can\'t be empty';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * invite to m6 in top menu function
 */
function app_invite_to_m6(){
  if(isset($_REQUEST['invited_email']) && !empty($_REQUEST['invited_email'])){    
    if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
      global $base_url, $base_path;
      $companies_array = array();
      $current_node = node_load($_REQUEST['nid']);
      $invitedEmails = $_REQUEST['invited_email'];
      if(strpos(",", $invitedEmails) == TRUE){
        $companies_array = explode(",", json_decode($_REQUEST['invited_email']));
      }
      $companies_array[] = $invitedEmails;      
      $uid = $_REQUEST['user_id'];
      $invalid_mail = array();$specialMsg = '';
      if(isset($_REQUEST['special_message']) && !empty($_REQUEST['special_message'])){
        $specialMsg = $_REQUEST['special_message'];
      }      
      $i = 0;
      foreach ($companies_array as $key => $value) {        
        if (!is_numeric($value)) {
          if (empty(valid_email_address($value))) {
            $invalid_mail[$key] = $value;            
            continue;
          }
          else{
            /*$inviteEmail[$i] = $value;
            $i++;*/
            // serilize data array
            $invitedCompanyNidsEmail = array(
              'user' => $uid,
              'site_name' => "M6connect",
              'base_url' => $base_url,
              'expiry' => time(),
              'email' => $value,
              'special_message' => $specialMsg
            );
            // field data array
            $db_insert = array(
              'bundle' => $current_node->type,
              'entity_id' => $current_node->nid,
              'invited_by' => $uid,
              'emails' => serialize($invitedCompanyNidsEmail),
              'invited_timestamp' => time(),
              'send_mail_timestamp' => NULL,
              'Status' => 0,
            );
            $returnedId = db_insert('invite_users_rfp_project')->fields($db_insert)->execute();
          }
        }
        else{
          $invalid_mail[$key] = $value;
        }
      }
      if (!empty($invalid_mail)) {
        $invalid_rowmail = implode(',', $invalid_mail);
        $output['success'] = FALSE;
        $output['data'] = "Invalid email's ".$invalid_rowmail;
      }
      else{        
        if ($current_node->status == 0) {
          $current_node->status = 1;
        }
        node_save($current_node);
        //_cron_invite_users_rfp_project();
        $output['success'] = TRUE;
        $output['data'] = "Invitation sent successfully";
      }      
    }
    else{
      $output['success'] = FALSE;
      $output['data'] = "Nid can't be empty";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['data'] = "Email can't be empty";    
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * top search result api
 */
function app_top_search_result(){
  if(isset($_REQUEST['search_data']) && !empty($_REQUEST['search_data'])){
    global $user;
    $user_id = $_REQUEST['user_id'];
    $user = user_load($user_id);
    $searchData = $_REQUEST['search_data'];    
    $result = search_data($searchData, 'node');
    $searchResData = $result['#results'];    
    $mainData = array();
    if(!empty($searchResData)){
      foreach($searchResData as $key => $value){
        $mainData[$key]['nid'] = $value['node']->nid;
        $mainData[$key]['uid'] = $value['node']->uid;
        $mainData[$key]['user'] = strip_tags($value['user']);
        $mainData[$key]['date'] = date("Y-m-d H:i:s", $value['date']);
        $mainData[$key]['title'] = $value['title'];
        //'/\n/', '/\r/', '/\t/', '/\s+/'
        $mainData[$key]['snippet'] = strip_tags(preg_replace(array('/\s\s+/'), '', $value['snippet']));
      }
      $output['success'] = TRUE;
      $output['message'] = "Record found";
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "No search result found";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Search data can't be empty";
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function to get statuses node data for user notification
 */
function user_notification_get_statuses_data(){
  if(isset($_REQUEST['entity_id']) && !empty($_REQUEST['entity_id'])){
    global $base_url, $bucket, $awsAccessKey, $awsSecretKey;
    $entity_id = $_REQUEST['entity_id'];
    $statuses = statuses_load($entity_id);
    $mainData = array();
    if(!empty($statuses)){
      $mainData['sender'] = _get_user_mail_realname_by_uid($statuses->sender)['realname'];
      $mainData['recipient'] = _get_title_of_node($statuses->recipient);
      $mainData['message'] = (!empty($statuses->message) ? $statuses->message : '');
      $mainData['date'] = (!empty($statuses->created) ? date("Y-m-d H:i", $statuses->created) : '');
      $getImgData = db_select('fbsmp', 'f')
                  ->fields('f', array("data"))
                  ->condition('sid', $entity_id, '=')
                  ->execute()->fetchAssoc();
      $imgData = '';
      if(!empty($getImgData)){
        $file = file_load(unserialize($getImgData['data'])['fid']);
        if(!empty($file->uri)){
          $credentials = new Credentials($awsAccessKey, $awsSecretKey);
          $s3Client = S3Client::factory(array(
            'credentials' => $credentials
          ));
          $thumbUrl = str_replace("private:/", "s3fs-private", $file->uri);
          $imgData = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
        } 
      }
      $mainData['image'] = $imgData;
      // get comment data from sid
      $commentData = fbss_comments_get_comments($entity_id, TRUE);
      $comments = array();
      if(!empty($commentData)){
        foreach ($commentData as $key => $value) {
          $comments[$key]['comment_id'] = $value->cid;
          $comments[$key]['author_name'] = _get_user_mail_realname_by_uid($value->uid)['realname'];
          $comments[$key]['author_photo'] = _get_user_profile_photo_by_uid($value->uid);
          $comments[$key]['comment'] = $value->comment;
          $comments[$key]['created'] = date("Y-m-d H:i", $value->created);
        }
      }
      $mainData['comments'] = $comments;

      if(!empty($mainData)){
        $output['success'] = TRUE;
        $output['message'] = t('Record found');
        $output['data'] = $mainData;
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('Status data not found.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Entity id can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/** 
 * finction to edit comment from cid
 */
function user_notification_edit_statuses_comment(){
  if(isset($_REQUEST['comment_id']) && !empty($_REQUEST['comment_id'])){
    $cid = $_REQUEST['comment_id'];
    if(isset($_REQUEST['comment']) && !empty($_REQUEST['comment'])){
      $comment = array("comment" => $_REQUEST['comment']);
      db_update('fbss_comments')->fields($comment)->condition('cid',$cid,'=')->execute();
      $mainData['comment_id'] = $cid;
      $mainData['comment'] = $_REQUEST['comment'];
      $output['success'] = TRUE;
      $output['message'] = 'Comment updated successfully';
      $output['data'] = $mainData;
    } 
    else{
      $output['success'] = FALSE;
      $output['message'] = "Comment can't be empty";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Comment id can't be empty";
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function to delete comment from cid
 */
function user_notification_delete_statuses_comment(){
  if(isset($_REQUEST['comment_id']) && !empty($_REQUEST['comment_id'])){
    $cid = $_REQUEST['comment_id'];
    db_delete('fbss_comments')
            ->condition('cid', $cid)
            ->execute();
    $output['success'] = TRUE;
    $output['message'] = 'Comment deleted successfully';
    $output['data'] = 1;
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Comment id can't be empty";
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * funtion to add new comment
 */
function user_notification_add_new_statuses_comment(){
  if(isset($_REQUEST['entity_id']) && !empty($_REQUEST['entity_id'])){
    $sid = $_REQUEST['entity_id'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['comment']) && !empty($_REQUEST['comment'])){
      $comment = $_REQUEST['comment'];
      $saveComment = db_insert('fbss_comments')
                    ->fields(array(
                      'sid' => $sid,
                      'uid' => $user_id,
                      'created' => time(),
                      'comment' => $comment,
                    ))
                    ->execute();
      $output['success'] = TRUE;
      $output['message'] = 'Comment saved successfully';
      $output['data'] = 1;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "Comment can't be empty";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Entity id can't be empty";
  }
  drupal_json_output($output);
  drupal_exit();
}




















/**********************************************************
**************** Helper functions *************************
**********************************************************/
// Please make helper functions in this section and main function above it.

/**
 * Function to return og_data of a user.
 * User's organic groups, and other user's in those groups.
 *
 * @param $account
 *  User object.
 *
 * @return An array of ids (both group and user ids).
 */
function _get_og_data_by_user($account) {
  $return = array();
  $data = og_get_entity_groups('user', $account, array(OG_STATE_ACTIVE));
  if (!empty($data['node'])) {
    $return = array_values($data['node']);
    $return = drupal_map_assoc($return);
  }
  if (!isset($return[$account->uid])) {
    $return[$account->uid] = $account->uid;
  }
  return $return;
}

/**
 * Get status data prepared.
 * @param $account
 *   User account object.
 * @param $sid (optional)
 *   If sid is provided, then data is fetched for that
 *   particular status.
 *
 * @return Associative array with keys as sid, and data as values.
 */
function _get_status_data_prepared($account, $sid = NULL, $nid = NULL, $starts = 0) {
  global $base_url, $bucket, $awsAccessKey, $awsSecretKey;
  if (empty($account)) {
    if (!empty($_REQUEST['user_id'])) {
      $account = user_load($_REQUEST['user_id']);
    }
  }
  $return = array();
  if (empty($sid) && empty($nid)) {
    $og_data = _get_og_data_by_user($account);
  }
  // Trying to get status list for the current account.
  $query = db_select('statuses', 'st');
  // Joining image if available.
  $query->leftJoin('fbsmp', 'fb', 'fb.sid=st.sid');
  // Joining users table.
  $query->leftJoin('users', 'u', 'u.uid=st.sender');
  // Joining First name and last name table.
  $query->leftJoin('field_data_field_first_name', 'fn', 'fn.entity_id=st.sender AND fn.entity_type=:user', array(':user' => 'user'));
  $query->leftJoin('field_data_field_last_name', 'ln', 'ln.entity_id=st.sender AND ln.entity_type=:user', array(':user' => 'user'));
  //Joining user profile pic 
  $query->leftJoin('field_data_field_user_profile_photo', 'up', 'up.entity_id=st.sender');
  //$query->condition('up.entity_type', 'user');
  // Conditions
  $query->condition('st.type', array('user', 'og'));
  // If status_id is provided in api request so getting statuses greater then
  // the request status_id.
  if (isset($_REQUEST['status_id']) && $_REQUEST['status_id'] > 0) {
    $query->condition('st.sid', $_REQUEST['status_id'], '<');
  }
  // If limit is provided in the api request, then limiting content.
  if (isset($_REQUEST['limit']) && $_REQUEST['limit'] > 0) {
    $query->range(0, $_REQUEST['limit']);
  }
  // Status id should not be null.
  $query->isNotNull('st.sid');
  // If $sid is provided, then filtering with the status_id.
  if (!empty($sid)) {
    $query->condition('st.sid', $sid);
  }
  if(!empty($nid)){
    $query->condition('st.recipient', $nid);
  }
  else {
    $query->condition('st.recipient', $og_data);
  }
  // Fields
  $query->fields('st');
  $query->fields('fb', array('data'));
  $query->fields('u', array('uid', 'name'));
  $query->fields('up',array('field_user_profile_photo_fid'));
  $query->fields('fn',array('field_first_name_value'));
  $query->fields('ln',array('field_last_name_value'));
  $query->orderBy('st.created', 'DESC');
  $query->range($starts, 10);
  $results = $query->execute()->fetchAll();    
  if (!empty($results)) {
    // If there are any status, then proceeding.
    foreach ($results as $status) {
      $datas = array();
      // Preparing data.
      $fname = !empty($status->field_first_name_value) ? $status->field_first_name_value : NULL;
      $lname = !empty($status->field_last_name_value) ? $status->field_last_name_value : NULL;
      $name = ucwords($fname . ' ' . $lname);
      if (empty($fname) && empty($lname)) {
        $name = ucwords($status->name);
      }
      $image = '';
      $user_image = '';
      if (!empty($status->data)) {
        $unser_data = unserialize($status->data);
        if (!empty($unser_data['fid'])) {
          $file = file_load($unser_data['fid']);
          //$image = file_create_url($file->uri);
          if(!empty($file->uri)){
            $credentials = new Credentials($awsAccessKey, $awsSecretKey);
            $s3Client = S3Client::factory(array(
              'credentials' => $credentials
            ));
            $thumbUrl = str_replace("private:/", "s3fs-private", $file->uri);
            $image = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
          }          
        }
      }
      if (!empty($status->field_user_profile_photo_fid) && $user_file = file_load($status->field_user_profile_photo_fid)) {
        $user_image = file_create_url($user_file->uri);
      }
      // Trying to get comments and bump counts.
      $comment_bumps = _get_post_bumpit_comment_count($status->sid);
      $comment_count = $comment_bumps['comment_count'];
      $bumpit_count = $comment_bumps['bumpit_count'];
      $datas['status_id'] = $status->sid;
      $datas['name'] = $name;
      $datas['created'] = date('Y-m-d H:i:s', $status->created);
      $datas['message'] = $status->message;
      $datas['image'] = $image;
      $datas['user_image'] = $user_image;
      $datas['comment_count'] = $comment_count;
      $datas['bumpit_count'] = $bumpit_count;
      $bum = getFeedLike($account->uid, $status->sid);
      $userBumpit = 'unlike';
      if(!empty($bum)){
        $userBumpit = 'like';
      }
      $datas['user_bumpit'] = $userBumpit;
      // get all comment
      $comList = '';$comments = array();
      $comList = getAllCommentBySid($status->sid);
      if(!empty($comList)){        
        foreach ($comList as $key => $value) {
          $user = user_load($value->uid);
          if (!empty($user->field_first_name['und'][0]['value'])) {
            $firstname = $user->field_first_name['und'][0]['value'];
          }
          if (!empty($user->field_middle_name['und'][0]['value'])) {
            $middlename = $user->field_middle_name['und'][0]['value'] . ' ';
          }
          if (!empty($user->field_last_name['und'][0]['value'])) {
            $lastname = $user->field_last_name['und'][0]['value'];
          }
          $realname = $firstname . ' ' . $middlename . $lastname;
          if (!empty($user->field_user_profile_photo['und'][0]['uri'])) {
            $picture = file_create_url($user->field_user_profile_photo['und'][0]['uri']);
          }
          $comments[$key]['name'] = ucwords($realname);
          $comments[$key]['pic'] = $picture;
          $comments[$key]['user_id'] = $value->uid;
          $comments[$key]['comment_date'] = date('Y-m-d H:i:s', $value->created);
          $comments[$key]['comment'] = $value->comment;
        }        
      }
      $datas['comment'] = $comments;
      if (!isset($return[$status->sid])) {
        $return[$status->sid] = $datas;
      }
    }
    $return = array_values($return);    
  }
  return $return;
}
/*
 *  get all comment from status id
 */
function getAllCommentBySid($sid = ''){
  $comList = db_select('fbss_comments', 'fc')
            ->fields('fc')
            ->condition('sid', $sid, '=')
            ->execute()->fetchAll();
  return $comList;
}
function getFeedLike($uid = 0, $sid = ''){
  $query = db_select ( 'fb_likes', 'fl' )->fields ( 'fl' );
  $query->condition ( 'fl.uid', $uid, '=' );
  $query->condition ( 'fl.sid', $sid, '=' );
  $bumpit_count = $query->execute ()->rowCount ();
  return $bumpit_count;
}