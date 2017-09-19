<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';
/**
 * @file Handle user's profile api, get and update on APP.
 */

/**
 * Returns a JSON object of user profile data as personal and company details.
 **/
function user_profile_get() {
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if (!$account->uid) {
    // If the user does not authenticate, then return error.
    drupal_json_output($output);
    drupal_exit();
  }
  $user_personal_data = array(); 
  $user_contact_data = array();
  $user_company_data = array();
  $firstname = $middlename = $lastname = $picture = $dob = $user_address = $user_job_title = $PrimaryComName = $user_job_comp = $user_email = $UserFacebook = $UserTwitter = $UserLinkedin = $UserBehance = $coverImage = '';  
  if (!empty($account->field_first_name['und'][0]['value'])) {
    $firstname = $account->field_first_name['und'][0]['value'];
  }
  if (!empty($account->field_middle_name['und'][0]['value'])) {
    $middlename = $account->field_middle_name['und'][0]['value'] . ' ';
  }
  if (!empty($account->field_last_name['und'][0]['value'])) {
    $lastname = $account->field_last_name['und'][0]['value'];
  }
  $realname = $firstname . ' ' . $middlename . $lastname;
  if (!empty($account->field_user_profile_photo['und'][0]['uri'])) {
    $picture = file_create_url($account->field_user_profile_photo['und'][0]['uri']);
  }
  if (!empty($account->field_user_profile_cover_img['und'][0]['uri'])) {
    $coverImage = file_create_url($account->field_user_profile_cover_img['und'][0]['uri']);
  }
  if (!empty($account->field_date_of_birth['und'][0]['value'])) {
    $dob = date('Y-m-d', strtotime($account->field_date_of_birth['und'][0]['value']) );
  }  
  if (!empty($account->field_address['und'][0]['administrative_area'])) {
	  $user_address = $account->field_address['und'][0]['locality'].', '.$account->field_address['und'][0]['administrative_area'];
  }
  if(!empty($account->field_user_title['und'][0]['value'])){
    $user_job_title = $account->field_user_title['und'][0]['value'];
  }
  $PrimaryComNId = (isset($account->field_primary_company['und'][0]['value']) ? $account->field_primary_company['und'][0]['value']: '') ;
  if($PrimaryComNId){
  	$PrimaryComName = _get_title_of_node($PrimaryComNId);
    $PrimaryComNameN = (strlen($PrimaryComName) > 26) ? substr($PrimaryComName, 0, 23) . '...' : $PrimaryComName;
    $user_job_comp = $user_job_title.', '.$PrimaryComNameN;
  }else{
  	print $user_job_comp = $string_jobtitle_name;  
  }  
  if($account->mail){
    $user_email = (strlen($account->mail) > 26) ? substr($account->mail, 0, 23) . '...' : $account->mail;
  }
  if (!empty($account->field_phone['und'][0]['value'])) {
    $phoneNumber = $account->field_phone['und'][0]['value'];
	  $phoneNumberval = get_international_formatPhoneNumber($phoneNumber);		
    if (isset($account->field_hide_phone_number['und']) && empty($account->field_hide_phone_number['und'][0]['value'])) {
	    $UserPhoneNumber = (strlen($phoneNumberval) > 26) ? substr($phoneNumberval, 0, 23) . '...' : $phoneNumberval;
	  }	  
  }
  if (!empty($account->field_facebook_url['und'][0]['value'])) {
    $user_facebook = $account->field_facebook_url['und'][0]['value']; 
    $str_user_facebook = str_replace(array('http://','https://'), '', $user_facebook);
	  $UserFacebook = (strlen($str_user_facebook) > 26) ? substr($str_user_facebook, 0, 23) . '...' : $str_user_facebook;
  }
  if (!empty($account->field_twitter_url['und'][0]['value'])) {
    $user_twitter = $account->field_twitter_url['und'][0]['value']; 
    $str_user_twitter = str_replace(array('http://','https://'), '', $user_twitter);
	  $UserTwitter = (strlen($str_user_twitter) > 26) ? substr($str_user_twitter, 0, 23) . '...' : $str_user_twitter; 
  }
  if (!empty($account->field_linkedin_url['und'][0]['value'])) {
    $user_linkedin = $account->field_linkedin_url['und'][0]['value']; 
    $str_user_linkedin= str_replace(array('http://','https://'), '', $user_linkedin);
	  $UserLinkedin = (strlen($str_user_linkedin) > 26) ? substr($str_user_linkedin, 0, 23) . '...' : $str_user_linkedin; 
  }
  if (!empty($account->field_behance_url['und'][0]['value'])) {
    $user_behance = $account->field_behance_url['und'][0]['value']; 
    $str_user_behance = str_replace(array('http://','https://'), '', $user_behance);
    $UserBehance = (strlen($str_user_behance) > 26) ? substr($str_user_behance, 0, 23) . '...' : $str_user_behance; 
  }
  
  $user_personal_data['user_id'] = $account->uid; 
  $user_personal_data['realname'] = trim($realname);
  $user_personal_data['user_image'] = $picture;
  $user_personal_data['cover_image'] = $coverImage;
  $user_personal_data['dob'] = $dob;
  $user_personal_data['user_address'] = $user_address;
  $user_personal_data['user_job_title'] = $user_job_comp;
  
  $user_contact_data['user_email'] = $user_email;
  $user_contact_data['user_phone'] = $UserPhoneNumber;
  $user_contact_data['user_facebook'] = $UserFacebook;
  $user_contact_data['user_twitter'] = $UserTwitter;
  $user_contact_data['user_linkedin'] = $UserLinkedin;
  $user_contact_data['user_behance'] = $UserBehance;
  $user_detail = _get_companies_details_by_user_uid($account->uid);
  $hidecom = _get_company_hide_on_userprofile($account->uid);
  $userComp = array();$i = 0;
  foreach($user_detail as $userDetail){
    if(!in_array($userDetail->nid,$hidecom)){
      $userComp[$i]['nid'] = $userComp[$i]['img'] = $userComp[$i]['title'] = $userComp[$i]['email'] = '';       
      if (isset($userDetail->uri)) 
      {
        $userComp[$i]['img'] = image_style_url('pic_20x20', $userDetail->uri);
      }
      $userComp[$i]['title'] = $userDetail->title;
      $userComp[$i]['nid'] = $userDetail->nid;
      $userComp[$i]['email'] = $userDetail->company_email;      
      $i++;
    }
  }
  $user_contact_data['user_company'] = $userComp;
  // crediantal data
  $onBoardingNid = get_user_onboarding_nid($account->uid); 
  $creViewMore = user_Profile_credentials_viewmore($onBoardingNid);
  $node = node_load($onBoardingNid);
  $items = field_get_items('node', $node, 'field_onbarding_credentials');  
  $data = array();$i = 0;
  foreach($items as $item) { 
    $fcid = $item['value'];
    $fcvalue = field_collection_field_get_entity($item);
    $data[$i]['value'] = $fcvalue->field_title_name_of_credential['und'][0]['value'];
    $i++;
  }
  $user_contact_data['credentials'] = $data;
  // connection filter category
  $conCategory = array();
  $connections = m6connect_misc_get_groups_by_ownerid(2, 'connection_categories');
  foreach ($connections as $key => $value) {
    $conCategory[$key]['id'] = $value->nid;
    $conCategory[$key]['value'] = $value->title;
  }
  $user_contact_data['connection_filter'] = $conCategory;
  // connection details (name, photo, connected, bookmarks)
  $relationships = user_relationships_load(array('approved' => $account->uid, 'approved' => TRUE, 'requestee_id' => $account->uid));  
  $i = 0;$connUser = array();
  foreach ($relationships as $relationship) {
    $relationship->requester_id;
    $rcuser = user_load($relationship->requester_id);
    $job_title_tid = isset($rcuser->field_job_titles['und'][0]) ? $rcuser->field_job_titles['und'][0]['target_id'] : '';
    $job_title_name = '';
    if ($job_title_tid != '') {
      $job_title_term = taxonomy_term_load($job_title_tid);
      $job_title_name = $job_title_term->name;
    }
    $connUser[$i]['photo'] = (isset($rcuser->field_user_profile_photo['und'])) ? image_style_url('connection_image_all_152_120', $rcuser->field_user_profile_photo['und'][0]['uri']) : '';    
    $connUser[$i]['uid'] = $rcuser->uid;
    $connUser[$i]['name'] = $rcuser->realname;
    $status_btn = connection_member_status_button($account->uid,$rcuser->uid);
    if($account->uid != $rcuser->uid ){
      if(isset($status_btn['button']) && $status_btn['button'] == 'Connect'){
        $connUser[$i]['connectlabel'] = 'Connect';
      }
      else if($user->uid == $rcuser->uid){
        $connUser[$i]['connectlabel'] = 'You are connected'; 
      }
      else{
        $connUser[$i]['connectlabel'] = $status_btn['button'];
      }
    }
    $flag = flag_get_flag('people_bookmark');
    $connUser[$i]['bookmark'] = '';
    if ($flag && $flag->is_flagged($rcuser->uid)) {
      $connUser[$i]['bookmark'] = 'Bookmarked';
    }
    $i++;
  }
  $user_contact_data['connection_user'] = $connUser;

  $user_company_data = get_companies_list($account->uid);
  // user profile strength
  $weight = profile_strenght($account->uid);
  $user_contact_data['profile_strength'] = $weight;
  // user skill set
  $query = db_select('m6connect_user_skill_set', 'uss');
  $query->fields('uss',array('Id','skill_uid','skill_title','skill_year','skill_rating'));
  $query->condition('uss.skill_uid', $account->uid);
  $result = $query->execute()->fetchAll();
  $user_contact_data['skillset']['title'] = $result[0]->skill_title;
  $user_contact_data['skillset']['year'] = $result[0]->skill_year;
  $user_contact_data['skillset']['rating'] = $result[0]->skill_rating;
   
  $output = array(
    'success' => TRUE,
    'message' => 'User Profile Get successfull!',
    //'online' => _get_user_online_status($uid),
    'personal' => $user_personal_data,
    'contact_info' => $user_contact_data,
    'company_info' =>$user_company_data,     
  );

  drupal_json_output($output);
  drupal_exit();
}
// api for user profile images and profile strength
function user_profile_data(){
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if (!$account->uid) {
    // If the user does not authenticate, then return error.
    drupal_json_output($output);
    drupal_exit();
  }
  $user_personal_data = array(); 
  $user_contact_data = array();
  $user_company_data = array();
  $firstname = $middlename = $lastname = $picture = $dob = $user_address = $user_job_title = $PrimaryComName = $user_job_comp = $user_email = $UserFacebook = $UserTwitter = $UserLinkedin = $UserBehance = $coverImage = '';  
  if (!empty($account->field_first_name['und'][0]['value'])) {
    $firstname = $account->field_first_name['und'][0]['value'];
  }
  if (!empty($account->field_middle_name['und'][0]['value'])) {
    $middlename = $account->field_middle_name['und'][0]['value'] . ' ';
  }
  if (!empty($account->field_last_name['und'][0]['value'])) {
    $lastname = $account->field_last_name['und'][0]['value'];
  }
  $realname = $firstname . ' ' . $middlename . $lastname;
  if (!empty($account->field_user_profile_photo['und'][0]['uri'])) {
    $picture = file_create_url($account->field_user_profile_photo['und'][0]['uri']);
  }
  if (!empty($account->field_user_profile_cover_img['und'][0]['uri'])) {
    $coverImage = file_create_url($account->field_user_profile_cover_img['und'][0]['uri']);
  }    
  if (!empty($account->field_address['und'][0]['administrative_area'])) {
    $user_address = $account->field_address['und'][0]['locality'].', '.$account->field_address['und'][0]['administrative_area'];
  }
  if(!empty($account->field_user_title['und'][0]['value'])){
    $user_job_title = $account->field_user_title['und'][0]['value'];
  }
  $PrimaryComNId = (isset($account->field_primary_company['und'][0]['value']) ? $account->field_primary_company['und'][0]['value']: '') ;
  if($PrimaryComNId){
    $PrimaryComName = _get_title_of_node($PrimaryComNId);
    $PrimaryComNameN = (strlen($PrimaryComName) > 26) ? substr($PrimaryComName, 0, 23) . '...' : $PrimaryComName;
    $user_job_comp = $user_job_title.', '.$PrimaryComNameN;
  }else{
    print $user_job_comp = $string_jobtitle_name;  
  }  
  
  $user_personal_data['user_id'] = $account->uid; 
  $user_personal_data['realname'] = trim($realname);
  $user_personal_data['user_image'] = $picture;
  $user_personal_data['cover_image'] = $coverImage;
  $user_personal_data['user_address'] = $user_address;
  $user_personal_data['user_job_title'] = $user_job_comp;
  // connection details (name, photo, connected, bookmarks)
  $relationships = user_relationships_load(array('approved' => $account->uid, 'approved' => TRUE, 'requestee_id' => $account->uid));
  $user_company_data = get_companies_list($account->uid);
  // user profile strength
  $weight = profile_strenght($account->uid);
  $user_personal_data['profile_strength'] = $weight;  
   
  $output = array(
    'success' => TRUE,
    'message' => 'User Profile Get successfull!',    
    'data' => $user_personal_data     
  );

  drupal_json_output($output);
  drupal_exit();
}
// api for user profile about data
function user_profile_about(){
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if (!$account->uid) {
    // If the user does not authenticate, then return error.
    drupal_json_output($output);
    drupal_exit();
  }
  $user_personal_data = array(); 
  $user_contact_data = array();
  $user_company_data = array();
  $dob = $user_address = $user_job_title = $PrimaryComName = $user_job_comp = $user_email = $UserFacebook = $UserTwitter = $UserLinkedin = $UserBehance = $coverImage = '';
  if (!empty($account->field_address['und'][0]['administrative_area'])) {
    $user_address = $account->field_address['und'][0]['locality'].', '.$account->field_address['und'][0]['administrative_area'];
  }
  if(!empty($account->field_user_title['und'][0]['value'])){
    $user_job_title = $account->field_user_title['und'][0]['value'];
  }
  if (!empty($account->field_date_of_birth['und'][0]['value'])) {
    $dob = date('Y-m-d', strtotime($account->field_date_of_birth['und'][0]['value']) );
  }
  $PrimaryComNId = (isset($account->field_primary_company['und'][0]['value']) ? $account->field_primary_company['und'][0]['value']: '') ;
  if($PrimaryComNId){
    $PrimaryComName = _get_title_of_node($PrimaryComNId);
    $PrimaryComNameN = (strlen($PrimaryComName) > 26) ? substr($PrimaryComName, 0, 23) . '...' : $PrimaryComName;
    $user_job_comp = $user_job_title.', '.$PrimaryComNameN;
  }else{
    print $user_job_comp = $string_jobtitle_name;  
  }  
  if($account->mail){
    $user_email = (strlen($account->mail) > 26) ? substr($account->mail, 0, 23) . '...' : $account->mail;
  }
  if (!empty($account->field_phone['und'][0]['value'])) {
    $phoneNumber = $account->field_phone['und'][0]['value'];
    $phoneNumberval = get_international_formatPhoneNumber($phoneNumber);    
    if (isset($account->field_hide_phone_number['und']) && empty($account->field_hide_phone_number['und'][0]['value'])) {
      $UserPhoneNumber = (strlen($phoneNumberval) > 26) ? substr($phoneNumberval, 0, 23) . '...' : $phoneNumberval;
    }   
  }
  if (!empty($account->field_facebook_url['und'][0]['value'])) {
    $user_facebook = $account->field_facebook_url['und'][0]['value']; 
    $str_user_facebook = str_replace(array('http://','https://'), '', $user_facebook);
    $UserFacebook = (strlen($str_user_facebook) > 26) ? substr($str_user_facebook, 0, 23) . '...' : $str_user_facebook;
  }
  if (!empty($account->field_twitter_url['und'][0]['value'])) {
    $user_twitter = $account->field_twitter_url['und'][0]['value']; 
    $str_user_twitter = str_replace(array('http://','https://'), '', $user_twitter);
    $UserTwitter = (strlen($str_user_twitter) > 26) ? substr($str_user_twitter, 0, 23) . '...' : $str_user_twitter; 
  }
  if (!empty($account->field_linkedin_url['und'][0]['value'])) {
    $user_linkedin = $account->field_linkedin_url['und'][0]['value']; 
    $str_user_linkedin= str_replace(array('http://','https://'), '', $user_linkedin);
    $UserLinkedin = (strlen($str_user_linkedin) > 26) ? substr($str_user_linkedin, 0, 23) . '...' : $str_user_linkedin; 
  }
  if (!empty($account->field_behance_url['und'][0]['value'])) {
    $user_behance = $account->field_behance_url['und'][0]['value']; 
    $str_user_behance = str_replace(array('http://','https://'), '', $user_behance);
    $UserBehance = (strlen($str_user_behance) > 26) ? substr($str_user_behance, 0, 23) . '...' : $str_user_behance; 
  }
  
  $user_personal_data['user_id'] = $account->uid; 
  $user_personal_data['dob'] = $dob;
  $user_personal_data['user_address'] = $user_address;
  $user_personal_data['user_job_title'] = $user_job_comp;

  $user_contact_data['user_email'] = $user_email;
  $user_contact_data['user_phone'] = $UserPhoneNumber;
  $user_contact_data['user_facebook'] = $UserFacebook;
  $user_contact_data['user_twitter'] = $UserTwitter;
  $user_contact_data['user_linkedin'] = $UserLinkedin;
  $user_contact_data['user_behance'] = $UserBehance;
  // crediantal data
  $onBoardingNid = get_user_onboarding_nid($account->uid); 
  $creViewMore = user_Profile_credentials_viewmore($onBoardingNid);
  $node = node_load($onBoardingNid);
  $items = field_get_items('node', $node, 'field_onbarding_credentials');  
  $data = array();$i = 0;
  foreach($items as $item) { 
    $fcid = $item['value'];
    $fcvalue = field_collection_field_get_entity($item);
    $data[$i]['value'] = $fcvalue->field_title_name_of_credential['und'][0]['value'];
    $i++;
  }
  $user_contact_data['credentials'] = $data;
  
  $user_company_data = get_companies_list($account->uid);
  
  $output = array(
    'success' => TRUE,
    'message' => 'User Profile About Get successfull!',
    //'online' => _get_user_online_status($uid),
    'personal' => $user_personal_data,
    'contact_info' => $user_contact_data,
    'company_info' => $user_company_data,
    'connection' => user_profile_connection(1),
  );

  drupal_json_output($output);
  drupal_exit();
}
// api for user profile connection data
function user_profile_connection($app = ''){
  if (empty($account)) {
    $account = user_load($_REQUEST['user_id']);
  }
  $output = array(
    'success' => false,
    'message' => t('Could not process the request!'),
  );
  if (!$account->uid) {
    // If the user does not authenticate, then return error.
    drupal_json_output($output);
    drupal_exit();
  }
  // connection details (name, photo, connected, bookmarks)
  $relationships = user_relationships_load(array('approved' => $account->uid, 'approved' => TRUE, 'requestee_id' => $account->uid));  
  $i = 0;$connUser = array();
  foreach ($relationships as $relationship) {
    $relationship->requester_id;
    $rcuser = user_load($relationship->requester_id);
    $job_title_tid = isset($rcuser->field_job_titles['und'][0]) ? $rcuser->field_job_titles['und'][0]['target_id'] : '';
    $job_title_name = '';
    if ($job_title_tid != '') {
      $job_title_term = taxonomy_term_load($job_title_tid);
      $job_title_name = $job_title_term->name;
    }
    $connUser[$i]['photo'] = (isset($rcuser->field_user_profile_photo['und'])) ? image_style_url('connection_image_all_152_120', $rcuser->field_user_profile_photo['und'][0]['uri']) : '';    
    $connUser[$i]['uid'] = $rcuser->uid;
    $connUser[$i]['name'] = $rcuser->realname;
    $status_btn = connection_member_status_button($account->uid,$rcuser->uid);
    if($account->uid != $rcuser->uid ){
      if(isset($status_btn['button']) && $status_btn['button'] == 'Connect'){
        $connUser[$i]['connectlabel'] = 'Connect';
      }
      else if($user->uid == $rcuser->uid){
        $connUser[$i]['connectlabel'] = 'You are connected'; 
      }
      else{
        $connUser[$i]['connectlabel'] = $status_btn['button'];
      }
    }
    $flag = flag_get_flag('people_bookmark');
    $connUser[$i]['bookmark'] = '';
    if ($flag && $flag->is_flagged($rcuser->uid)) {
      $connUser[$i]['bookmark'] = 'Bookmarked';
    }
    $i++;
  }
  $output = array(
    'success' => TRUE,
    'message' => 'User Profile Connection Get successfull!',
    'data' => $connUser,     
  );
  if(!empty($app)){
    return $connUser;
  }
  drupal_json_output($output);
  drupal_exit();
}

function user_profile_photo_tab_data(){
  global $bucket, $awsAccessKey, $awsSecretKey;
  $user_id = $_REQUEST['user_id'];
  $fids = fn_get_own_shared_images($user_id);
  $mainData = array();$i=0;
  if(!empty($fids)){
    $credentials = new Credentials($awsAccessKey, $awsSecretKey);
    $s3Client = S3Client::factory(array(
      'credentials' => $credentials
    ));
    foreach ($fids as $key) {
      $share_photo = file_load($key);
      if(!empty($share_photo->uri)){
        $share_photo_url = image_style_url('user_photo_tab_162',$share_photo->uri);
        $thumbUrl = str_replace("private:/", "s3fs-private", $share_photo->uri);
        $thumbnailUrl = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
        $mainData[$i]['id'] = $key;
        $mainData[$i]['value'] = $thumbnailUrl;
        $i++;
      }      
    }
    $output = array(
      'success' => TRUE,
      'message' => 'Record found',    
      'data' => $mainData     
    );
  } 
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'No data found'
    );
  } 
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for user profile edit
 */
function app_user_personal_profile_edit(){
  $user_id = $_REQUEST['user_id'];
  $user = user_load($user_id);
  $company_id = isset($_REQUEST['companyNid']) ? $_REQUEST['companyNid'] : '';
  $mainData = array();
  if(!empty($user)){
    $mainData['first_name'] = isset($user->field_first_name['und']) ? $user->field_first_name['und'][0]['value'] : '';
    $mainData['middle_name'] = isset($user->field_middle_name['und']) ? $user->field_middle_name['und'][0]['value'] : '';
    $mainData['last_name'] = isset($user->field_last_name['und']) ? $user->field_last_name['und'][0]['value'] : '';
    $mainData['dob'] = isset($user->field_date_of_birth['und']) ? $user->field_date_of_birth['und'][0]['value'] : '';
    $mainData['gender'] = isset($user->field_gender['und']) ? $user->field_gender['und'][0]['value'] : '';
    $mainData['phone_number'] = isset($user->field_phone['und']) ? $user->field_phone['und'][0]['value'] : '';
    $mainData['work_phone_number'] = isset($user->field_mobile_phone['und']) ? $user->field_mobile_phone['und'][0]['value'] : '';
    $mainData['profile_photo'] = isset($user->field_user_profile_photo['und']) ? file_create_url($user->field_user_profile_photo['und'][0]['uri']) : '';
    $mainData['profile_cover_image'] = isset($user->field_user_profile_cover_img['und']) ? file_create_url($user->field_user_profile_cover_img['und'][0]['uri']) : '';    
    $mainData['automatically_receive_mail'] = isset($user->field_automatically_receive_mail['und']) ? $user->field_automatically_receive_mail['und'][0]['value'] : '';
    $mainData['receive_insurance_certificcate'] = isset($user->field_receive_insurance_certific['und']) ? $user->field_receive_insurance_certific['und'][0]['value'] : '';
    $pmsg = 0;
    $getDisable = db_select('pm_disable', 'p')
                ->fields('p', array('uid'))
                ->condition('uid', $user_id, '=')
                ->execute()->fetchCol();
    if(empty($getDisable)){
      $pmsg = 1;
    }
    $mainData['enable_private_message'] = $pmsg;
    $emailNotify = 0;
    $getEmailNotify = db_select('pm_email_notify', 'p')
                    ->fields('p', array("email_notify_is_enabled"))
                    ->condition('user_id', $user_id, '=')
                    ->execute()->fetchCol();
    if(!empty($getEmailNotify)){
      $emailNotify = 1;
    }
    $mainData['enable_private_message'] = $pmsg;
    $timezoneData = '';
    if(!empty($user->timezone)){
      date_default_timezone_set($user->timezone);
      $timezoneData = $user->timezone.' '.date('l F d, Y - H:i P');
    }
    $mainData['timezone'] = $timezoneData;
    $mainData['email'] = isset($user->mail) ? $user->mail : '';
    $address = '';
    if(isset($user->field_address['und'])){
      $address = $user->field_address['und'][0];
      $mainData['country'] = (!empty($address['country']) ? $address['country'] : '');
      $mainData['address1'] = (!empty($address['thoroughfare']) ? $address['thoroughfare'] : '');
      $mainData['address2'] = (!empty($address['premise']) ? $address['premise'] : '');
      $mainData['city'] = (!empty($address['locality']) ? $address['locality'] : '');
      $mainData['state'] = (!empty($address['administrative_area']) ? $address['administrative_area'] : '');
      $mainData['postal_code'] = (!empty($address['postal_code']) ? $address['postal_code'] : '');
    }
    $mainData['alternate_phone'] = isset($user->field_alt_phone['und']) ? $user->field_alt_phone['und'][0]['value'] : '';
    $mainData['fax'] = isset($user->field_fax['und']) ? $user->field_fax['und'][0]['value'] : '';
    $mainData['facebook_url'] = isset($user->field_facebook_url['und']) ? $user->field_facebook_url['und'][0]['value'] : '';
    $mainData['linkedin_url'] = isset($user->field_linkedin_url['und']) ? $user->field_linkedin_url['und'][0]['value'] : '';
    $mainData['twitter_url'] = isset($user->field_twitter_url['und']) ? $user->field_twitter_url['und'][0]['value'] : '';
    $mainData['yammer_url'] = isset($user->field_behance_url['und']) ? $user->field_behance_url['und'][0]['value'] : '';
    // check user role. if user is administrator then following fields will be displayed
    if(!empty($company_id)){
      $getUserRole = og_get_user_roles('node', $company_id, $user_id);
      if(in_array('administrator member', $getUserRole)){
        $mainData['allow_routing_slip_access'] = isset($user->field_allow_routing_slip_access['und']) ? $user->field_allow_routing_slip_access['und'][0]['value'] : '';
        $mainData['allow_onboarding_access'] = isset($user->field_allow_onboarding_access['und']) ? $user->field_allow_onboarding_access['und'][0]['value'] : '';
        $mainData['allow_m6alert_access'] = isset($user->field_allow_m6alert['und']) ? $user->field_allow_m6alert['und'][0]['value'] : '';
        $mainData['personal_m6drive_space'] = isset($user->field_personal_m6drive_space['und']) ? $user->field_personal_m6drive_space['und'][0]['value'] : '';
        $mainData['m6id'] = isset($user->field_m6id['und']) ? $user->field_m6id['und'][0]['value'] : '';
        $mainData['user_status'] = $user->status;
        $roleAry = user_roles();
        $roleData = array();
        if(!empty($roleAry)){          
          unset($roleAry[1]);
          $i=0;
          foreach ($roleAry as $key => $value) {
            $roleData[$i]['id'] = $key;
            $roleData[$i]['value'] = $value;
            $i++;
          }
        }
        $mainData['role_list'] = $roleData;
        $userRoleList = $user->roles;
        $userRoles = array();
        if(!empty($userRoleList)){
          $i = 0;
          foreach ($userRoleList as $key => $value) {
            $userRoles[$i]['id'] = $key;
            $userRoles[$i]['value'] = $value;
            $i++;
          }
        }        
        $mainData['user_role'] = $userRoles;
      }  
    }

    $output = array(
      'success' => TRUE,
      'message' => 'Record found',
      'data' => $mainData,     
    );
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'User not exist with this user id',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for user edit m6id api
 */
function app_user_personal_m6id_edit(){
  $mainData = array();
  $ob_nid = get_user_onboarding_nid($_REQUEST['user_id']);
  if(!empty($ob_nid)){
    $node = node_load($ob_nid);
    if(!empty($node)){
      $mainData['facilities_construction'] = get_first_level_taxonomy_data('facilities_construction');
      include_once DRUPAL_ROOT . '/includes/locale.inc';
      $countryList = country_get_list();
      $countryListData = array();$i=0;
      foreach ($countryList as $key => $value) {
        $countryListData[$i]['id'] = $key;
        $countryListData[$i]['value'] = $value;
        $i++;
      }
      $mainData['country_list'] = $countryListData;
      $country_of_issuance = isset($node->field_drivers_license_issuance['und']) ? $node->field_drivers_license_issuance['und'][0]['country'] : '';
      $issueStates = $issueStatesData = array();
      if(!empty($country_of_issuance)){
        module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
        $issueStates = addressfield_get_administrative_areas($country_of_issuance);
        if(!empty($issueStates)){
          $i=0;
          foreach ($issueStates as $key => $value) {
            $issueStatesData[$i]['id'] = $key;
            $issueStatesData[$i]['value'] = $value;
            $i++;
          }
        }
      }      
      $mainData['state_list'] = $issueStatesData;

      $output = array(
        'success' => TRUE,
        'message' => 'Record found',
        'data' => $mainData,
      );
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Data not found for this user';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Data not found for this user';
  }
  
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for user edit membership status
 */
function app_user_personal_member_status(){
  $currentUser = user_load($_REQUEST['user_id']);
  if(!empty($currentUser)){
    $mainData = array();
    $user_roles = $currentUser->roles; 
    $user_order_product='';    
    $expirePlans = '';                          
    if(isset($user_roles[7])){
      $user_order_product = $user_roles[7];
    }
    else if(isset($user_roles[8])){
      $user_order_product = $user_roles[8];
    }
    else if(isset($user_roles[9])){
      $user_order_product = $user_roles[9];
    }else if(isset($user_roles[14])){
      $user_order_product = $user_roles[14];
    }else if(isset($user_roles[4])){
      $user_order_product = "Free Plan";
    }else{
      $user_order_product = "Free Plan";
    }
    $mainData['current_plan'] = $user_order_product;
    if($user_order_product != "Free Plan"){
      $can_account = $currentUser;
      $rebill_expiration = array();
      $last_pg_field = field_get_items('user', $can_account, 'usr_last_pg');
      $last_pg =  $last_pg_field[0]['value'];
      if($last_pg == 'bluepay'){
        $bluepay_field = field_get_items('user', $can_account, 'user_bluepay_rec_cancel_status');
        $rebill_cancel_status = $bluepay_field[0]['value'];
        $bluepay_field2 = field_get_items('user', $can_account, 'user_bluepay_rec_expiration');
        $rebill_expiration = explode(" ",$bluepay_field2[0]['value']);
      }elseif($last_pg == 'authorizenet'){
        $authnet_field = field_get_items('user', $can_account, 'user_authorizenet_rc_cncl_stat');
        $rebill_cancel_status = $authnet_field[0]['value'];
        $authnet_field2 = field_get_items('user', $can_account, 'user_authorizenet_rec_expiration');
        $rebill_expiration = explode(" ",$authnet_field2[0]['value']);
      }
      $expirePlans = '';
      if($rebill_cancel_status == '1'){
        $expirePlans = $rebill_expiration[0];
      }
    }
    $mainData['expire_plan'] = $expirePlans;
    $query_payment = db_select('uc_orders', 'uco');
    $query_payment->join('uc_order_products','ucop','ucop.order_id=uco.order_id');
    $query_payment->fields('uco', array('order_id','uid','order_status','order_total','created','modified'));
    $query_payment->fields('ucop', array('title'));
    $query_payment->condition('uco.uid',  $currentUser->uid, '=');
    $result_payment = $query_payment->execute()->fetchAll();
    $paymentRows = array();
    if(!empty($result_payment)){
      foreach($result_payment as $delta => $item_payment){
        $created_date = date('m/d/Y', $item_payment->created);
        $modified_date = date('m/d/Y', $item_payment->modified);
        $modified_date = (!empty($modified_date))?$modified_date:$created_date;
        $paymentRows[$delta]['date'] = $modified_date;
        $paymentRows[$delta]['order'] = $item_payment->order_id;
        $paymentRows[$delta]['membership_plan'] = $item_payment->title;
        $paymentRows[$delta]['total'] = substr($item_payment->order_total, 0, -3);
        $paymentRows[$delta]['status'] = $item_payment->order_status;
      }
    }
    $mainData['payment_history'] = $paymentRows;
    
    $output = array(
      'success' => TRUE,
      'message' => 'Record found',
      'data' => $mainData,     
    );
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'User not exist with this user id',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for user edit companies tab data
 */
function app_user_personal_companies(){
  $currentUser = user_load($_REQUEST['user_id']);
  if(!empty($currentUser)){
    $mainData = array();
    $mainData['responsibility'] = isset($currentUser->field_responsibilities['und']) ? $currentUser->field_responsibilities['und'][0]['value'] : '';
    $mainData['title'] = isset($currentUser->field_user_title['und']) ? $currentUser->field_user_title['und'][0]['value'] : '';
    $mainData['job_title'] = isset($currentUser->field_job_titles['und']) ? taxonomy_term_load($currentUser->field_job_titles['und'][0]['target_id'])->name : '';
    // get company email data from user id
    $query = db_select ( 'm6connect_og_membership_email', 'ome' );
    $query->join ( 'node', 'n', 'n.nid=ome.entity_id' );
    $query->fields ( 'n', array ('nid','title') );
    $query->fields ( 'ome', array ('company_email') );
    $query->condition ( 'ome.user_uid', $currentUser->uid, '=' );
    $query->condition ( 'ome.company_type', 'company', '=' );
    $query->orderBy ( 'title', 'ASC' );
    $result = $query->execute ()->fetchAllAssoc ( 'nid' );
    $userCmpData = array();
    if(!empty($result)){
      $i = 0;
      foreach ($result as $key => $value) {
        $userCmpData[$i]['nid'] = $value->nid;
        $userCmpData[$i]['company_name'] = $value->title;
        $userCmpData[$i]['company_email'] = $value->company_email;
        $userCmpData[$i]['selected'] = 0;
        $PrimaryCompany = _get_user_primary_company($currentUser->uid);
        if(!empty($PrimaryCompany)){
          if($PrimaryCompany == $value->nid){  
            $userCmpData[$i]['selected'] = 1;
          }
        }
        $userCmpData[$i]['hide_on_profile'] = 0;
        $CompanyNameHideOnProfile = _get_company_hide_on_userprofile($currentUser->uid);
        if(!empty($CompanyNameHideOnProfile) && isset($CompanyNameHideOnProfile)){
          if(in_array($value->nid,$CompanyNameHideOnProfile)){ 
            $userCmpData[$i]['hide_on_profile'] = 1;
          }
        }
        $i++;
      }
    }
    $mainData['company_emails'] = $userCmpData;
    // delegate access data
    $delegateDataQry = db_query("SELECT m6connect_user_delegate.id AS id, m6connect_user_delegate.uid_from AS m6connect_user_delegate_uid_from, m6connect_user_delegate.uid_to AS m6connect_user_delegate_uid_to, users_m6connect_user_delegate.name AS users_m6connect_user_delegate_name, users_m6connect_user_delegate.uid AS users_m6connect_user_delegate_uid, users_m6connect_user_delegate.mail AS users_m6connect_user_delegate_mail, m6connect_user_delegate.last_login AS m6connect_user_delegate_last_login, m6connect_user_delegate.id AS m6connect_user_delegate_id FROM {m6connect_user_delegate} m6connect_user_delegate INNER JOIN {users} users_m6connect_user_delegate ON m6connect_user_delegate.uid_to = users_m6connect_user_delegate.uid WHERE (( (m6connect_user_delegate.uid_from = ".$currentUser->uid." ) )AND(( (m6connect_user_delegate.status != ".$currentUser->uid.") ))) ORDER BY m6connect_user_delegate_id DESC");
    $delegateDataRes = $delegateDataQry->fetchAll();
    $delegateData = array();
    if(!empty($delegateDataRes)){
      foreach ($delegateDataRes as $key => $value) {
        $delegateData[$key]['access_id'] = $value->id;
        $delegateData[$key]['name'] = _get_user_mail_realname_by_uid($value->m6connect_user_delegate_uid_to)['realname'];
        $delegateData[$key]['email'] = $value->users_m6connect_user_delegate_mail;
      }
    }
    $mainData['delegate_access'] = $delegateData;
    // granted access data
    $grantedDataQry = db_query("SELECT m6connect_user_delegate.id AS id, m6connect_user_delegate.uid_from AS m6connect_user_delegate_uid_from, m6connect_user_delegate.uid_to AS m6connect_user_delegate_uid_to, m6connect_user_delegate.revoke_date AS m6connect_user_delegate_revoke_date, m6connect_user_delegate.last_login AS m6connect_user_delegate_last_login, m6connect_user_delegate.id AS m6connect_user_delegate_id, name AS name, uid AS uid, mail AS mail FROM {m6connect_user_delegate} m6connect_user_delegate INNER JOIN {users} users_m6connect_user_delegate ON m6connect_user_delegate.uid_from = users_m6connect_user_delegate.uid WHERE (( (m6connect_user_delegate.uid_to = ".$currentUser->uid." ) )AND(( (m6connect_user_delegate.status = '1') ))) ORDER BY m6connect_user_delegate_id DESC");
    $grantedDataRes = $grantedDataQry->fetchAll();
    $grantedData = array();
    if(!empty($grantedDataRes)){
      foreach ($grantedDataRes as $key => $value) {
        $grantedData[$key]['access_id'] = $value->id;
        $grantedData[$key]['name'] = _get_user_mail_realname_by_uid($value->uid)['realname'];
        $grantedData[$key]['email'] = $value->mail;
        $grantedData[$key]['expires'] = date('m/d/Y', $value->m6connect_user_delegate_revoke_date);
      }
    }
    $mainData['granted_access'] = $grantedData;

    $output = array(
      'success' => TRUE,
      'message' => 'Record found',
      'data' => $mainData,     
    );
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'User not exist with this user id',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}
function getAllEmailOptions(){
  $options = array(
    'company_mail___invite_user_by_company' => 'Invite User By User Management of Company',
    'connection_request_connect' => 'Connection Request/Approved Notification',
    'project_mail___user_invite_project' => 'Project - Invite Notification',
    'project_mail___invite_user_project_updated' => 'Project - Update Notification',
    'project_mail___show_interest_in_project' => 'Project - Show Interest Notification',
    'project_mail___interested_bidding_project' => 'Project - Interested in Bidding Notify',
    'project_mail___collaborate_user_invite_project' => 'Project - Collaborated User Invite Noification' ,
    'rfp_mail___user_invite_rfp' => 'RFP - Invite Notification',
    'rfp_mail___invite_user_rfp_updated' => 'RFP - Update Notification',
    'rfp_mail___awarded_proposal_notify' => 'RFP - Award Notification',
    'rfp_mail___request_to_intent_notify' => 'RFP - Request to Intent Notify',
    'clarification_mail___owner_public_clarification_msg' => 'Clarification - Public Message by Owner Notification',
    'clarification_mail___owner_private_clarification_msg' => 'Clarification - Private Message by Owner Notifification',
    'clarification_mail___users_private_clarification_msg' => 'Clarification - Private Message by Invited User Notification',
    'proposal_mail___insert_communuication_message' => 'Proposal - New Message Notification',
    'proposal_mail___awarded_proposal_membership_notify' => 'Proposal - Awarded Proposal Membership Notification',
    'proposal_mail___awarded_proposal_notify' => 'Proposal - Awarded Proposal Notification',
    'proposal_mail___proposal_submission_confirmation' => 'Proposal - Submission Confirmation Notification',
    'insurance_mail___approval_reminder_notify' => 'Insurance Certificate - Approval Reminder Notification',
    'insurance_certificates_invite' => 'Insurance Certificate Invite Notification',
    'routing_mail___routing_status_notify' => 'Routing Slip - Status Change Notification',
    'routing_mail___approval_invite_notify' => 'Routing Slip - Approver Invite Notification',
    'routing_mail___approval_reminder_notify' => 'Routing Slip -  Approval Reminder Notification',
    'routing_mail___approved_status_notify' => 'Routing Slip - Approved Status Notification',
    'routing_mail___approver_update_approval_notify' => 'Routing Slip - Approver Changes Approval Status Notification',
    'messenger_new_message_email' => 'Messenger - New Message Notification',
    'm6id_mail___m6id_invite_employee_notify' => 'M6ID - Invite Employee Notification',
    'm6id_mail___m6id_invite_worker_to_project_notify' => 'M6ID - Invite Worker To Project Notification',
    'onboarding_mail___invite_company_users' => 'M6ID - Invite Companies To Project',
    'hcfm_mail___invite_user_by_company' => 'Invite User By HCFM User Management of Company',
  );
  return $options;
}
/**
 * function for user edit opt out emails
 */
function app_user_personal_opt_out_emails(){
  $currentUser = user_load($_REQUEST['user_id']);
  if(!empty($currentUser)){
    $options = getAllEmailOptions();
    $emailOptions = $defaultEmailOptions = $mainData = array();$i = 0;
    foreach ($options as $key => $value) {
      $emailOptions[$i]['id'] = $key;
      $emailOptions[$i]['value'] = $value;
      $i++;
    }
    $mainData['email_options'] = $emailOptions;
    $userDefaultOptions = db_select('m6connect_opt_out_emails','mooe')->fields('mooe', array('email_key'))->condition('mooe.user_uid', $currentUser->uid)->execute()->fetchCol();
    if(!empty($userDefaultOptions)){
      foreach ($userDefaultOptions as $key => $value) {
        $defaultEmailOptions[$key]['value'] = $value;
      }
    }
    $mainData['default_email_options'] = $defaultEmailOptions;

    $output = array(
      'success' => TRUE,
      'message' => 'Record found',
      'data' => $mainData,     
    );
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'User not exist with this user id',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for user edit opt out emails submit
 */
function app_user_personal_opt_out_emails_submit(){
  $currentUser = user_load($_REQUEST['user_id']);
  if(!empty($currentUser)){
    if(isset($_REQUEST['opt_out_emails_data']) && !empty($_REQUEST['opt_out_emails_data'])){
      $optOutEmailsData = json_decode($_REQUEST['opt_out_emails_data']);
      $optData = array();$i = 0;
      foreach ($optOutEmailsData as $key => $value) {
        $optData[$i] = $key;
        $i++;
      }
      // get default keys
      $userDefaultOptions = db_select('m6connect_opt_out_emails','mooe')->fields('mooe', array('email_key'))->condition('mooe.user_uid', $currentUser->uid)->execute()->fetchCol();

      $options = getAllEmailOptions();
      $allmailKeys = array_keys($options);


      // work on submit from app

    }
    else{
      $output = array(
        'success' => FALSE,
        'message' => 'Opt out email data can\'t be empty',
      );
    }
  }
  else{
    $output = array(
      'success' => FALSE,
      'message' => 'User not exist with this user id',
    );
  }
  drupal_json_output($output);
  drupal_exit();
}












/**********************************************************
**************** Helper functions *************************
**********************************************************/
// Please make helper functions in this section and main function above it.

 //Function for Getting companies list by uid 
function get_companies_list($user_id) {
  //Getting companies list by uid    
  if(!empty($user_id)) {
    $account = user_load($user_id);   
  }
  //$companies_detail = m6connect_misc_get_user_all_companies($account->uid);
  $companies_detail = m6connect_misc_get_user_all_companies($account->uid);
  //removing user's default(individual) company. 
  $companies_result_list = array();
  $conpanies_list = array();
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
  return $companies_result_list;
}
 