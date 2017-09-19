<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';
/*
 *  function for company registration
 */
module_load_include('inc', 'm6connect_misc', 'includes/add_organization.form');
module_load_include('inc', 'm6connect_prochat', 'includes/projectposting/project');
module_load_include('inc', 'm6connect_prochat', 'includes/dashboard/status/app_status');

/*
 * function for send all company data for login in left block
 */
function user_company_for_login_left_block($uid = '', $onpageRequest = 0){
  if(empty($uid)){
    $uid = $_REQUEST['user_id'];
  }  
  $list_company = m6connect_misc_get_user_all_companies($uid);
  if(!empty($list_company)){
    $data = $returnval = '';
    $output['current_loggedin_company'] = _get_title_of_node(variable_get('company_set_'.$uid));
    $outputData = array();
    foreach ($list_company as $key => $value) {
      $outputData[$key]['title'] = $value->title;
      $outputData[$key]['nid'] = $value->nid;
      $outputData[$key]['field_type_of_company_value'] = $value->field_type_of_company_value;
      $outputData[$key]['field_main_location_grp_target_id'] = $value->field_main_location_grp_target_id;
      $outputData[$key]['group_access_value'] = $value->group_access_value;
      $company = node_load($value->nid);
      $companyUsers = og_get_group_members_properties($company, array(), 'members__' . OG_STATE_ACTIVE, 'node');
      if (is_array($companyUsers) && count($companyUsers) > 0) {
        $grpMembers = count($companyUsers);
        $grpMemberRoles = array();
        foreach ($companyUsers as $k => $v) {
          $grpMemberRoles[$v] = og_get_user_roles('node', $value->nid, $v);
        }
        if ($company->uid == $uid) {
          if ($grpMembers == '1') {
            $returnval = 1;
          } else {
            $returnval = 2;
          }
        } else {
          $MemberRole = $grpMemberRoles[$uid];
          if (!in_array('administrator member', $MemberRole) && $grpMembers > 1) {
            $returnval = 3;
          } else {
            $returnval = 4;
          }
        }
      }
      //$returnval = unsubscribe_m6connect_user($value->nid);
      $outputData[$key]['return'] = $returnval;
      if($returnval == 1){
        $outputData[$key]['returnMsg'] = 'You are the only member of '.$value->title.'. Press Continue to disable this Company\'s account. Press Cancel to keep the Company active.';
      }
      if($returnval == 2){
        $outputData[$key]['returnMsg'] = $value->title.' must have at least one Administrator. Please assign another member to be Administrator before leaving the Company.';
      }
      if($returnval == 3){
        $outputData[$key]['returnMsg'] = 'Are you sure you want to leave the '.$value->title.'. Press Yes to leave the Company. Press No to Stay in the Company.';
      }
      if($returnval == 4){
        $outputData[$key]['returnMsg'] = '';
      }
    }
    $output['data'] = $outputData;
    $output['success'] = TRUE;
    $output['message'] = 'Record found';
  }
  else{
    $error = "No company found for this user";
    $output['data'] = $error;
    $output['success'] = FALSE;
  }
  if(empty($onpageRequest)){
    drupal_json_output($output);
    drupal_exit();
  }
}
/*
 * function for switch company
 */
function switch_company(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $cid = $_REQUEST['companyNid'];
    $uid = $_REQUEST['user_id'];
    variable_set('company_set_'.$uid, $cid);
    $output['success'] = TRUE;
    $output['services'] = user_services_access_data($uid, $cid, 0);
  }
  else{
    $error = "Company id can't be empty";
    $output['data'] = $error;
    $output['success'] = FALSE;
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for disable user from og
 */
function unsubscribe_company(){  
  $output1 = array();$returnval = '';
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $cid = $_REQUEST['companyNid'];
    $uid = $_REQUEST['user_id'];
    db_update('users')
    ->fields(array('login' => REQUEST_TIME))
    ->condition('uid', $uid)
    ->execute();
    drupal_session_regenerate();
    $user = user_load($uid);   
    $list_company_output = m6connect_prochat_get_user_one_company($uid, $cid);    
    og_ungroup('node', $cid, 'user', $uid);
    user_company_for_login_left_block($uid, 1);        
    $output1['success'] = TRUE;
  }
  else{
    $output1['success'] = FALSE;
    $output1['data'] = "Company id can't be empty";    
  }
  drupal_json_output($output1);
  drupal_exit();
}
/*
 *  api for send invitation on invite companies
 */
function invite_company_send_invitation(){
  if(isset($_REQUEST['invitedEmail']) && !empty($_REQUEST['invitedEmail'])){    
    if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
      $current_node = node_load($_REQUEST['nid']);
      $companies_array = json_decode($_REQUEST['invitedEmail']);
      $uid = $_REQUEST['user_id'];
      $invalid_mail = array();
      foreach ($companies_array as $key => $value) {         
        if (!is_numeric($value)) {
          if (!valid_email_address($value)) {
            $invalid_mail[] = $value;
            continue;
          }
        }
        $invitedCompanyNidsEmail = array();
        $invitedCompanyNidsEmail[$value] = '';
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
        if (is_numeric($value)) {
          $grp = node_load($value);
          if ($grp->type == 'organization') {
            $grpuid = $grp->uid;
            $_SESSION['cust_invite_msg_' . $grpuid] = $value;
          }
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
        _cron_invite_users_rfp_project();
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
/*
 *  api for resend invitation on invite companies
 */
function invite_company_resend_invitation(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $current_node = node_load($_REQUEST['nid']);
    $uid = $_REQUEST['user_id'];
    $nodeUser = user_load($uid);
    $mailAttr = _get_mail_variables($mailKey = 'project_mail___user_invite_project', $type = 'project', $current_node, $other = array());
    $i = 0;    
    $emptyCmpyMailto = $companyOwner = '';
    foreach ($current_node->field_rfp_invite_comapnies['und'] as $key => $value) {
      $item = field_collection_item_load($value);
      if (isset($item->field_rfp_company_nid_email['und']) && !empty($item->field_rfp_company_nid_email['und'][0]['value'])) {
        $to = array();
        $is_ok = 1;
        $invited_companies = $item->field_rfp_company_nid_email['und'][0]['value'];
        if (is_numeric($invited_companies)) {
          $companyNode = node_load($invited_companies);
          $cmpUsrObj = user_load($companyNode->uid);
          $companyOwner = $companyNode->field_owner_name['und'][0]['value'];
          $to[] = $cmpUsrObj->mail;
        } else {
          $to[] = $invited_companies;
          $companyOwner = $invited_companies;
        }
        if (isset($item->field_co_invite_manager_uid['und']) && !empty($item->field_co_invite_manager_uid['und'][0]['value'])) {
          $cmpMngr = explode(',', $item->field_co_invite_manager_uid['und'][0]['value']);
          foreach ($cmpMngr as $cmpMngrindex => $cmpMngrUid) {
            $cmpUserObj = user_load($cmpMngrUid);
            $to[] = $cmpUserObj->mail;
          }
        }
        $params = $mailAttr;
        $replace = array('[PROJECT:InvitedCompanyOwnerName]' => $companyOwner,);
        $params['body'] = str_replace(array_keys($replace), array_values($replace), $params['body']);
        $mail = drupal_mail($params['module'], $params['key'], implode(',', $to), $params['language'], $params, $nodeUser->mail);
        if ($mail['result']) {
          $mailAttr['bcc'] = '';
          $i++;
          $output['success'] = TRUE;
          $output['data'] = "Invitation sent successfully";
        } else {
          $invalid_mail[] = "Invalid email's ".implode(',', $to);
          $output['success'] = FALSE;
          $output['data'] = "Nid can't be empty";
        }
      }
    }    
    if ($current_node->status == 0) {
      $current_node->status = 1;
    }
    node_save($current_node);
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  api for later invitation on invite companies
 */
function invite_company_later_invitation(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $output['success'] = TRUE;
    $output['data'] = 'The organizations that you have selected have been saved however, the invitations have not been sent at this time.';
  }
  else{
    $output['success'] = FALSE;
    $output['data'] = "Nid can't be empty";
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  api for company list on invite companies
 */
function invite_company_company_list(){
  module_load_include($type = 'inc', $module = 'bookmarkorganizer', $name = 'bookmarkorganizer');
  $starts = 0;
  if(isset($_REQUEST['start_range']) && !empty($_REQUEST['start_range'])){
    $starts = $_REQUEST['start_range'];
  }
  // left side filter
  $co_name = isset($_REQUEST ['co_name']) ? $_REQUEST ['co_name'] : '';
  $co_filter = isset($_REQUEST ['co_filter']) ? $_REQUEST ['co_filter'] : '';
  $co_facilities = isset($_REQUEST ['co_facilities']) ? $_REQUEST ['co_facilities'] : '';
  $co_region = isset($_REQUEST ['co_region']) ? $_REQUEST ['co_region'] : '';
  $co_industries = isset($_REQUEST ['co_industries']) ? $_REQUEST ['co_industries'] : '';
  $co_pservices = isset($_REQUEST ['co_pservices']) ? $_REQUEST ['co_pservices'] : '';
  $co_diversity = isset($_REQUEST ['co_diversity']) ? $_REQUEST ['co_diversity'] : '';
  $co_div_arr = array();
  if (!empty($co_diversity)) {
    $co_div_arr = explode(',', $co_diversity);
  }
  $co_div_arr = array_filter($co_div_arr);
  $user_id = $_REQUEST['user_id'];
  $type = array('organization');  
  $ic_or = db_or();
  $or = db_or();
  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->condition('type', $type, 'IN');
  $ic_or = db_or();
  $query->leftJoin('field_data_field_company_inactive', 'ic', 'ic.entity_id = n.nid');
  $ic_or->condition('ic.field_company_inactive_value', 1, '!=')->condition('ic.field_company_inactive_value', NULL);
  $query->condition($ic_or);
  $query->leftJoin('field_data_field_show_company_in_search', 'isa', 'isa.entity_id = n.nid');
  $query->condition('isa.field_show_company_in_search_value', 1, '=');
  $query->leftJoin('field_data_field_type_of_company', 'tc', 'tc.entity_id = n.nid');
  $query->condition('tc.field_type_of_company_value', 'company', '=');
  if (!empty($co_name)) {
    $query->leftJoin('field_data_field_keywords', 'k', 'k.entity_id = n.nid');
    $query->leftJoin('field_data_field_description', 'd', 'd.entity_id = n.nid');
    $query->fields('k');
    $query->fields('d');
    $or->condition('n.title', '%' . db_like($co_name) . '%', 'LIKE');
    $or->condition('k.field_keywords_value', '%' . db_like($co_name) . '%', 'LIKE');
    $or->condition('d.field_description_value', '%' . db_like($co_name) . '%', 'LIKE');
    $query->condition($or);
  }
  if (!empty($co_facilities)) {
    $query->Join('field_data_field_facilities_construction', 'cf', 'cf.entity_id = n.nid');
    $query->fields('cf');
    $co_facilities_tids = taxonomy_get_children_all($co_facilities);
    $fctids = array();
    if (!empty($co_facilities_tids)) {
      $rctids[] = $co_facilities;
      foreach ($co_facilities_tids as $fk => $fv) {
        $fctids[] = $fv->tid;
      }
    } else {
      $fctids[] = $co_facilities;
    }
    $query->condition('cf.field_facilities_construction_tid', $fctids, 'IN');
  }
  if (!empty($co_region)) {
    $query->Join('field_data_field_regions', 'cr', 'cr.entity_id = n.nid');
    $query->fields('cr');
    $query->leftjoin('field_data_field_org_address', 'oa', 'oa.entity_id = n.nid');
    $region_or = db_or();
    $region_term = taxonomy_term_load($co_region);
    $region_or->condition('oa.field_org_address_locality', db_like($region_term->name), 'LIKE');
    $co_region_tids = taxonomy_get_children_all($co_region);
    $rctids = array();
    if (!empty($co_region_tids)) {
      $rctids[] = $co_region;
      foreach ($co_region_tids as $rk => $rv) {
        $rctids[] = $rv->tid;
        $region_or->condition('oa.field_org_address_locality', db_like($rv->name), 'LIKE');
      }
    } else {
      $rctids[] = $co_region;
    }
    $region_or->condition('cr.field_regions_tid', $rctids, 'IN');
    $query->condition($region_or);
  }
  if (!empty($co_industries)) {
    $query->Join('field_data_field_industry_naicss', 'ci', 'ci.entity_id = n.nid');
    $query->fields('ci');
    $co_industries_tids = taxonomy_get_children_all($co_industries);
    $ictids = array();
    if (!empty($co_industries_tids)) {
      $ictids[] = $co_industries;
      foreach ($co_industries_tids as $ik => $iv) {
        $ictids[] = $iv->tid;
      }
    } else {
      $ictids[] = $co_industries;
    }
    $query->condition('ci.field_industry_naicss_tid', $ictids, 'IN');
  }
  if (!empty($co_pservices)) {
    $query->Join('field_data_field_products_service_unspsc', 'cp', 'cp.entity_id = n.nid');
    $query->fields('cp');
    $co_pservices_tids = taxonomy_get_children_all($co_pservices);
    $sctids = array();
    if (!empty($co_pservices_tids)) {
      $sctids[] = $co_pservices;
      foreach ($co_pservices_tids as $sk => $sv) {
          $sctids[] = $sv->tid;
      }
    } else {
      $sctids[] = $co_pservices;
    }
    $query->condition('cp.field_products_service_unspsc_tid', $sctids, 'IN');
  }
  if ($co_div_arr) {
    $query->Join('field_data_field_diversity_credentials', 'dt', 'dt.entity_id = n.nid');
    $query->fields('dt');
    $query->condition('dt.field_diversity_credentials_target_id', $co_div_arr, 'IN');
  }
  $query->orderBy('created', 'DESC');
  $query->groupBy('n.nid');
  $query->range($starts, 10);
  $result = $query->execute()->fetchAll();
  if(!empty($result)){
    $mainData = array();
    $bookmarkflag = flag_get_flag('bookmarks');
    foreach ($result as $key => $value) {
      $node = node_load($value->nid);
      $desc = isset($node->field_description['und']['0']['value']) ? $node->field_description['und']['0']['value'] : '';        
      $com_city = isset($node->field_org_address['und']['0']['locality']) ? $node->field_org_address['und']['0']['locality'] : '';
      $administrative_area = isset($node->field_org_address['und']['0']['administrative_area']) ? $node->field_org_address['und']['0']['administrative_area'] : '';       
      if(isset($node->field_org_address['und']) && !empty($node->field_org_address['und']['0']['administrative_area'])){
        $field = field_info_field('field_org_address');
        $instance = field_info_instance('node', 'field_org_address', 'organization');
        $address = addressfield_default_values($field,$instance);
        $handlers = array('address' => 'address',);
        $context = array('mode' => 'form');
        $data = addressfield_generate($address, $handlers, $context);         
        $com_state = $data['locality_block']['administrative_area']['#options'][$administrative_area];        
      }
      if(!empty($com_city)){
        $com_city_state = $com_city;
      }
      if(!empty($com_city_state) && !empty($com_state)){
        $com_city_state = $com_city_state.', '.$com_state;  
      }
      else if(!empty($com_state)){
        $com_city_state = $com_state;
      }
      $desc = strip_tags($desc);
      $length_body = strlen($desc);      
      $pimagepath = '';
      $pimgpath = (isset($node->field_logo['und']) && !empty($node->field_logo['und'][0]['uri'])) ? $node->field_logo['und'][0]['uri'] : 0;
      if ($pimgpath) {
        $pimagepath = image_style_url('thumbnail', $pimgpath);        
      }
      $mainData[$key]['nid'] = $value->nid;
      $mainData[$key]['image'] = $pimagepath;
      $mainData[$key]['title'] = $node->title;
      $mainData[$key]['about_company'] = (!empty($body) ? $body : '');
      $mainData[$key]['company_city_state'] = (!empty($com_city_state) ? $com_city_state : '');
      $gmlist = og_get_group_members_properties($node, array(), 'members__' . OG_STATE_ACTIVE, 'node');
      $userUidNameMapping = _get_user_uid_name_mapping(array_values($gmlist));
      $person = array();$i = 0;
      foreach ($userUidNameMapping as $invitedUid => $invitedName) {
        $person[$i]['userid'] = $invitedUid;
        $person[$i]['name'] = $invitedName;
        $i++;
      }
      $mainData[$key]['contact_person'] = $person;
      $diversityImage = get_diversity_image_by_comapny_nid($value->nid, 1);
      $mainData[$key]['certificate_image'] = (!empty($diversityImage) ? $diversityImage['image'] : '');
      $companies_detail = m6connect_misc_get_user_all_companies($user_id);
      $set_follow = TRUE;
      foreach ($companies_detail as $dkey => $dval) {
        if ($dval->nid == $value->nid) {
          $set_follow = FALSE;
        }
      }
      $fav = '';$foll = '';$book = '';
      if ($set_follow) {
        $fav = 'Favorite';$foll = 'Follow';$book = 'Bookmark';
        $favData = flag_create_link('favourite', $value->nid);
        if(!empty($favData)){
          $favdatas = explode('rel="nofollow">', $favData);
          $newfav = explode('</a>', $favdatas[1]);
          $fav = ucfirst($newfav[0]);
        }
        $follData = flag_create_link('follow_company', $value->nid);
        if(!empty($follData)){
          $folldatas = explode('rel="nofollow">', $follData);
          $newfoll = explode('</a>', $folldatas[1]);
          $foll = ucfirst($newfoll[0]);
        }
        $bookData = flag_create_link('bookmarks', $value->nid);
        if(!empty($bookData)){
          $bookdatas = explode('rel="nofollow">', $bookData);
          $newbook = explode('</a>', $bookdatas[1]);
          $book = ucfirst($newbook[0]);
        }
      }
      $mainData[$key]['favorite'] = $fav;
      $mainData[$key]['follow'] = $foll;
      $mainData[$key]['bookmark'] = $book;
    }
    $output['success'] = TRUE;
    $output['data'] = $mainData;
    $output['message'] = 'Record found';
  }
  else{
    $output['success'] = FALSE;
    $output['data'] = 'No company found';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  api for company search form data on invite companies
 */
function invite_company_company_search_form_data(){
  $mainData = array();
  $mainData['facilities_construction'] = get_first_level_taxonomy_data('facilities_construction');
  $mainData['region'] = get_first_level_taxonomy_data('Region');
  $mainData['industry_naics_1'] = get_first_level_taxonomy_data('industry_naics_1');
  $mainData['test_vocab_10'] = get_first_level_taxonomy_data('test_vocab_10');
  $dtype = array('diversity');
  $query = db_select('node', 'n');
  $query->fields('n', array('nid', 'title'))
          ->condition('type', $dtype, 'IN')
          ->condition('status', '1');
  $result = $query->execute()->fetchAll();
  $diversityData = array();
  foreach ($result as $row => $resData) {
    $diversity[$row]['id'] = $resData->nid;
    $diversity[$row]['value'] = $resData->title;
  } 
  $mainData['diversity'] = $diversity;
  if(!empty($mainData)){
    $output['success'] = TRUE;
    $output['data'] = $mainData;
    $output['message'] = 'Record found';
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'No data found';
  }  
  drupal_json_output($output);
  drupal_exit();
}

/*
 * organization type (company profile) node data api
 */
function company_profile_node_data(){  
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    global $bucket, $awsAccessKey, $awsSecretKey;
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];
    $orgNode = node_load($nid);
    
    if(!empty($orgNode)){
      $mainData = array();      
      $credentials = new Credentials($awsAccessKey, $awsSecretKey);
      $s3Client = S3Client::factory(array(
        'credentials' => $credentials
      ));
      $mainData['title'] = $orgNode->title;
      $mainData['location'] = $orgNode->field_incorporated_state['und'][0]['value'].' , '.$orgNode->field_incorporated_country['und'][0]['value'];
      $fc = taxonomy_term_load($orgNode->field_facilities_construction['und'][0]['tid']);
      $mainData['facilities_construction'] = $fc->name;
      $mainData['website'] = (!empty($orgNode->field_website['und'][0]['value']) ? $orgNode->field_website['und'][0]['value'] : '');
      $mainData['email'] = (!empty($orgNode->field_company_email['und'][0]['email']) ? $orgNode->field_company_email['und'][0]['email'] : '');
      $mainData['phone'] = (!empty($orgNode->field_org_phone['und'][0]['value']) ? $orgNode->field_org_phone['und'][0]['value'] : '');
      $mainData['fax'] = (!empty($orgNode->field_field_org_fax['und'][0]['value']) ? $orgNode->field_field_org_fax['und'][0]['value'] : '');
      $mainData['facebook'] = isset($orgNode->field_facebook['und']) ? $orgNode->field_facebook['und'][0]['value'] : '';
      $mainData['twitter'] = isset($orgNode->field_twitter['und']) ? $orgNode->field_twitter['und'][0]['value'] : '';
      $mainData['instagram'] = isset($orgNode->field_instagram['und']) ? $orgNode->field_instagram['und'][0]['value'] : '';
      $mainData['skype'] = isset($orgNode->field_skype['und']) ? $orgNode->field_skype['und'][0]['value'] : '';
      $mainData['linkdin'] = isset($orgNode->field_linkdin['und']) ? $orgNode->field_linkdin['und'][0]['value'] : '';
      $thumbnailUrl = $bannerImgUrl = '';
      if(!empty($orgNode->field_logo['und'][0]['uri'])){
        $thumbUrl = str_replace("private:/", "s3fs-private", $orgNode->field_logo['und'][0]['uri']);
        $thumbnailUrl = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');          
      }
      $mainData['logo'] = $thumbnailUrl;  
      if(!empty($orgNode->field_company_profile_cover_img['und'][0]['uri'])){
        $bannerUrl = str_replace("private:/", "s3fs-private", $orgNode->field_company_profile_cover_img['und'][0]['uri']);
        $bannerImgUrl = $s3Client->getObjectUrl($bucket, $bannerUrl, '+1day');
      }
      $mainData['cover_image'] = $bannerImgUrl;
      $mainData['owner_name'] = (!empty($orgNode->field_owner_name['und'][0]['value']) ? $orgNode->field_owner_name['und'][0]['value'] : '');
      $mainData['legal_structure'] = (!empty($orgNode->field_legal_structure['und'][0]['value']) ? $orgNode->field_legal_structure['und'][0]['value'] : '');
      $mainData['legal_name'] = (!empty($orgNode->field_legal_name['und'][0]['value']) ? $orgNode->field_legal_name['und'][0]['value'] : '');
      $mainData['company_description'] = (!empty($orgNode->field_description['und'][0]['value']) ? $orgNode->field_description['und'][0]['value'] : '');
      $mainData['company_tagline'] = (!empty($orgNode->field_company_tagline['und'][0]['value']) ? $orgNode->field_company_tagline['und'][0]['value'] : '');
      $mainData['annual_revenue'] = (!empty($orgNode->field_annual_revenue['und'][0]['value']) ? $orgNode->field_annual_revenue['und'][0]['value'] : '');
      $mainData['year_founded'] = (!empty($orgNode->field_year_founded['und'][0]['value']) ? $orgNode->field_year_founded['und'][0]['value'] : '');
      $mainData['number_of_employees'] = (!empty($orgNode->field_number_of_employees['und'][0]['value']) ? $orgNode->field_number_of_employees['und'][0]['value'] : '');
      $mainData['address'] = $orgNode->field_org_address['und'][0]['thoroughfare'].' '.$orgNode->field_org_address['und'][0]['locality'].' , '.$orgNode->field_org_address['und'][0]['administrative_area'].' '.$orgNode->field_org_address['und'][0]['postal_code'].' '.$orgNode->field_org_address['und'][0]['country'];
      $mainData['company_profile_strength'] = profile_strength_company_weight($uid);
      $cmpEmpData = getCompanyEmployeeList($nid);
      $eData = array();
      foreach ($cmpEmpData as $key => $empData) {
        $eData[$key]['uid'] = $empData->uid;
        $eData[$key]['name'] = (!empty($empData->realname) ? $empData->realname : '');        
        $eData[$key]['image'] = (!empty($empData->uri) ? file_create_url($empData->uri) : '');
      }
      $mainData['employee_list'] = $eData;
      $output['success'] = TRUE;
      $output['data'] = $mainData;
      $output['message'] = 'Record found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_news_feed_tab_data(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];
    $results['feeds'] = _get_status_data_prepared(NULL, NULL, $nid);
    if(!empty($results)){
      $output['success'] = TRUE;
      $output['message'] = t('Record found.');
      $output['data'] = $results;
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_diversity_tab_data(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];
    $orgNode = node_load($nid);
    $mainData = array();
    $output['success'] = FALSE;
    $output['message'] = "No data found";
    if(!empty($orgNode)){      
      $diversity = $orgNode->field_diversity_credentials['und'];
      $divNid = array();
      if(!empty($diversity)){
        foreach ($diversity as $key => $diversity_value) {
          $divNid[$key] = $diversity_value['target_id'];
        }
      }
      $diversityNodeTitle = getNodeTitleFromNids($divNid);
      if(!empty($diversityNodeTitle)){
        $diversityTitle = array();$i = 0;
        foreach ($diversityNodeTitle as $key => $divvalue) {
          $diversityTitle[$i]['id'] = $key;
          $diversityTitle[$i]['value'] = $divvalue;
          $i++;
        }
      }
      if(!empty($diversityTitle)){
        $mainData['diversityTab'] = $diversityTitle;  
      }      
      if(!empty($mainData)){
        $output['success'] = TRUE;
        $output['data'] = $mainData;
        $output['message'] = 'Record found';  
      }      
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_photo_tab_data(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    global $bucket, $awsAccessKey, $awsSecretKey;
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];
    $orgNode = node_load($nid);
    $node_photo = fn_get_own_shared_images($nid);
    if(!empty($node_photo)){
      $mainData = $nodeImg = array();
      foreach ($node_photo as $key => $value) {
        $nodeImg[$key]['id'] = $value;
        $imgpath = file_load($value);
        //$imgPath = file_create_url($imgpath->uri);
        if(!empty($imgpath)){
          $credentials = new Credentials($awsAccessKey, $awsSecretKey);
          $s3Client = S3Client::factory(array(
            'credentials' => $credentials
          ));
          $thumbUrl = str_replace("private:/", "s3fs-private", $imgpath->uri);
          $nodeImg[$key]['value'] = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
        }
      }      
      $output['success'] = TRUE;
      $output['data'] = $nodeImg;
      $output['message'] = 'Record found';
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "No data found";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_summary_tab_data(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    global $bucket, $awsAccessKey, $awsSecretKey;
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];
    $node = node_load($nid);
    $mainData = array();
    if(!empty($node)){
      $mainData['owner_name'] = (!empty($node->field_owner_name['und'][0]['value']) ? $node->field_owner_name['und'][0]['value'] : '');
      $des = '';
      if(!empty($node->field_description['und'])){
        $des1 = str_replace("\r", "", strip_tags($node->field_description['und'][0]['value']));
        $des = str_replace("\n", "", $des1);
      }
      $mainData['description'] = $des;
      $mainData['company_tagline'] = (!empty($node->field_company_tagline['und'][0]['value']) ? $node->field_company_tagline['und'][0]['value'] : '');
      $mainData['legal_structure'] = (!empty($node->field_legal_structure['und'][0]['value']) ? $node->field_legal_structure['und'][0]['value'] : '');
      $mainData['legal_name'] = (!empty($node->field_legal_name['und'][0]['value']) ? $node->field_legal_name['und'][0]['value'] : '');
      $mainData['annual_revenue'] = (!empty($node->field_annual_revenue['und'][0]['value']) ? $node->field_annual_revenue['und'][0]['value'] : '');
      $mainData['year_founded'] = (!empty($node->field_year_founded['und'][0]['value']) ? $node->field_year_founded['und'][0]['value'] : '');
      $mainData['number_of_employees'] = (!empty($node->field_number_of_employees['und'][0]['value']) ? $node->field_number_of_employees['und'][0]['value'] : '');
      $mainData['phone'] = (!empty($node->field_org_phone['und'][0]['value']) ? $node->field_org_phone['und'][0]['value'] : '');
      $thoroughfare = $area = $postal = $country = '';
      $thoroughfare = $node->field_org_address['und'][0]['thoroughfare'];
      $area = $node->field_org_address['und'][0]['administrative_area'];
      $postal = $node->field_org_address['und'][0]['postal_code'];
      $country = $node->field_org_address['und'][0]['country'];
      $mainData['address'] = $thoroughfare.' , '.$area.' '.$postal.' '.$country;

      $output['success'] = TRUE;
      $output['data'] = $mainData;
      $output['message'] = 'Record found';
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "No data found";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_gpo_tab_data(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];
    $node = node_load($nid);
    $mainData = $taxData = array();
    if(!empty($node)){      
      $data = db_select('taxonomy_term_data', 't');
      $data->leftjoin('taxonomy_term_hierarchy', 'tth', 'tth.tid = t.tid');
      $data->fields('t', array('tid', 'name'));
      $data->condition('t.vid', 6, '=');
      $data->condition('tth.parent', 0, '=');
      $result = $data->execute()->fetchAllKeyed(0,1);
      $i = 0;$taxData['name'] = 'products_services_unspsc';
      foreach ($result as $key => $value) {
        $taxData['data'][$i]['id'] = $key;
        $taxData['data'][$i]['value'] = $value;
        $i++;
      }      
      $output['success'] = TRUE;
      $output['data'] = $taxData;
      $output['message'] = 'Record found';
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "No data found";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_project_tab_data(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $uid = $_REQUEST['user_id'];
    $nid = $_REQUEST['nid'];    
    $mainData = $projectData = array();
    $cpmListData = getCompanyProjectList($nid);
    $pData = array();
    foreach ($cpmListData as $key => $proData) {
      $pData[$key]['nid'] = $proData->nid;
      $pData[$key]['title'] = (!empty($proData->title) ? $proData->title : '');
      $pData[$key]['keyword'] = (!empty($proData->field_projects_keywords_value) ? $proData->field_projects_keywords_value : '');        
      if(!empty($proData->field_project_address_new_thoroughfare)){
        $city = $proData->field_project_address_new_thoroughfare;
      }
      if(!empty($proData->field_project_address_new_administrative_area)){
        $state = $proData->field_project_address_new_administrative_area;
      }
      $add = '';
      if(!empty($city) && !empty($state)){
        $add = $city.', '.$state;
      }
      else if(!empty($city)){
        $add = $city;
      }
      else{
        $add = $state;
      }
      $pData[$key]['address'] = (!empty($add) ? $add : '');
      if(!empty($proData->uri)){
        $pData[$key]['uri'] = file_create_url($proData->uri);  
      }
      else{
        $pData[$key]['uri'] = '';
      }
    }
    $mainData['project_list'] = $pData;
    $output['success'] = TRUE;
    $output['data'] = $mainData;
    $output['message'] = 'Record found';
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Node id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

function m6connect_company_registration(){
  $user_id = $_REQUEST['user_id'];
  $mainData = array();  
  $mainData['source'] = 'M6Connect user';
  $mainData['service'] = getArrayValues(array('Unknown' => 'Unknown', 'Residential/Consumer' => 'Residential/Consumer', 'Commercial' => 'Commercial', 'N/A' => 'N/A'));
  $mainData['create_company_gpo'] = getArrayValues(array('yes' => t('Yes'), 'no' => t('No')));
  $mainData['create_company'] = '';  
  $mainData['join_company'] = getArrayValues(_get_organigation_mapping($user_id));
  $mainData['organization_name'] = '';
  $mainData['owner_name'] = '';
  $mainData['m6organization_type'] = get_first_level_taxonomy_data('facilities_construction');
  $mainData['legal_name'] = '';
  $field = field_info_field('field_legal_structure');
  $allowed_values = list_allowed_values($field);
  $mainData['legal_structure'] = getArrayValues($allowed_values);
  $DiversityOptions = db_select('node','n')->fields('n',array('nid','title'))->condition('n.type','diversity','=')->condition('n.status',1,'=')->execute()->fetchAllKeyed(0,1);
  $DiversityOptions = array('_none'=>'- None -')+$DiversityOptions;
  $mainData['diversity_credentials'] = getArrayValues($DiversityOptions);
  $mainData['diversity_credentials'][]['field_accredited_by'] = getArrayValues(array('None' => 'None', 'Federal Government' => 'Federal Government', 'State Government' => 'State Government', 'Port Authority NY/NJ' => 'Port Authority NY/NJ', 'City' => 'City', 'Country' => 'Country', 'Other' => 'Other'));
  $mainData['diversity_credentials'][]['field_cred_start_date']['date'] = '';
  $mainData['diversity_credentials'][]['field_credential_end_date']['date'] = '';
  $mainData['diversity_credentials'][]['field_credential_comments'] = '';
  $mainData['diversity_credentials'][]['field_credential_doc'] = '';  
  $mainData['phone_no'] = '';
  $mainData['organization_website_url'] = '';
  $mainData['thoroughfare'] = '';
  $mainData['premise'] = '';
  $mainData['locality'] = '';
  module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
  $states = addressfield_get_administrative_areas('US');
  $mainData['administrative_area'] = getArrayValues($states);
  $mainData['postal_code'] = '';
  $mainData['organigation_keyword'] = '';
  $mainData['postal_code'] = '';
  $mainData['files[organization_logo]'] = '';
  
  
  $output = array(
    'success' => TRUE,
    'message' => 'Create new company data',
    'data' => $mainData,
  );

  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for get company listing
 */
function m6connect_app_get_company_listing(){
  $user_id = $_REQUEST['user_id'];
  $type = array('organization');
  $query = db_select('node', 'n');
  $query->fields('n', array('nid'));
  $query->condition('type', $type, 'IN');
  $ic_or = db_or();
  $query->leftJoin('field_data_field_company_inactive', 'ic', 'ic.entity_id = n.nid');
  $ic_or->condition('ic.field_company_inactive_value', 1, '!=')->condition('ic.field_company_inactive_value', NULL);
  $query->condition($ic_or);
  $query->leftJoin('field_data_field_show_company_in_search', 'isa', 'isa.entity_id = n.nid');
  $is_or = db_or();
  $query->condition('isa.field_show_company_in_search_value', 1, '=');
  $query->leftJoin('field_data_field_type_of_company', 'tc', 'tc.entity_id = n.nid');
  $query->condition('tc.field_type_of_company_value', 'company', '=');
  $query->orderBy('created', 'DESC');
  $query->groupBy('n.nid');
  $query->range($starts, 10);
  $result = $query->execute()->fetchAll();
  $bookmarkflag = flag_get_flag('bookmarks');
  $mainData = array();
  if(!empty($result)){
    foreach ($result as $key => $record) {
      $mainData[$key]['nid'] = $record->nid;
      $node = node_load($record->nid, $vid = NULL, $reset = FALSE);
      $cirtificate = m6connect_company_get_circtficat($node);
      $mainData[$key]['title'] = $node->title;
      //$mainData[$key]['dcredetials'] = isset($node->field_diversity_credentials['und']) ? $node->field_diversity_credentials['und'] : '';
      $desc = isset($node->field_description['und']['0']['value']) ? $node->field_description['und']['0']['value'] : '';
      $desc = strip_tags($desc);
      $length_body = strlen($desc);
      if ($length_body > 50) {
        $mainData[$key]['description'] = substr($desc, 0, 50) . '...';
      } else {
        $mainData[$key]['description'] = $desc;
      }    
      if(isset($node->field_company_tagline['und']['0']) && !empty($node->field_company_tagline['und']['0']['value'])){
        $mainData[$key]['companytag'] = $node->field_company_tagline['und']['0']['value'];
      }
      $pimagepath = '';
      $pimgpath = (isset($node->field_logo['und']) && !empty($node->field_logo['und'][0]['uri'])) ? $node->field_logo['und'][0]['uri'] : 0;
      $mainData[$key]['image'] = (!empty($pimgpath) ? image_style_url('thumbnail', $pimgpath) : '');    
      if(isset($node->field_org_address['und'][0])) {
        if(!empty($node->field_org_address['und'][0]['locality'])) {
          $facity = $node->field_org_address['und'][0]['locality'];
        }
        if(!empty($node->field_org_address['und'][0]['administrative_area'])) {
          $fastate = ', '.$node->field_org_address['und'][0]['administrative_area'];
        }
        $mainData[$key]['address'] = $facity.$fastate;
      }
      $est = '';
      if (isset($node->field_year_founded['und'])) {
        $est = $node->field_year_founded['und'][0]['value'];
      }
      $mainData[$key]['year_founded'] = (!empty($est)) ? $est : '';
      $arev = '';
      if (isset($node->field_annual_revenue['und'])) {
        $arev = $node->field_annual_revenue['und'][0]['value'];
      }
      $mainData[$key]['annual_revenue'] = (!empty($arev)) ? $arev : '';
      $diverImage = '';
      $diverImage = get_diversity_image_by_comapny_nid($node->nid, 1);
      $mainData[$key]['diversityImage'] = (!empty($diverImage) ? $diverImage['image'] : '');
      $companies_detail = m6connect_misc_get_user_all_companies($user_id);
      $set_follow = TRUE;
      foreach ($companies_detail as $val) {
        if ($val->nid == $node->nid) {
          $set_follow = FALSE;
        }
      }
      if(!empty($set_follow)) {
        $mainData[$key]['favourite'] = (!empty(flag_create_link('favourite', $node->nid)) ? flag_create_link('favourite', $node->nid) : '');
        $mainData[$key]['follow_company'] = (!empty(flag_create_link('follow_company', $node->nid)) ? flag_create_link('favourite', $node->nid) : '');
        $mainData[$key]['bookmarks'] = (!empty(flag_create_link('bookmarks', $node->nid)) ? flag_create_link('favourite', $node->nid) : '');
      }
    }
    $output['success'] = TRUE;
    $output['message'] = t('Record found.');
    $output['data'] = $mainData;
  }
  else{
    $output['success'] = false; 
    $output['message'] = t('No company found');
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_edit_public_profile(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user = user_load($_REQUEST['user_id']);
    $node = node_load($company_id);    
    if(!empty($node)){
      $mainData = array();
      $mainData['title'] = $node->title;          
      $mainData['company_profile_photo'] = (isset($node->field_logo['und'][0]['uri']) ? file_create_url($node->field_logo['und'][0]['uri']) : '');
      $mainData['owner_name'] = (isset($node->field_owner_name['und']) ? $node->field_owner_name['und'][0]['value'] : '');      
      $mainData['company_email'] = (isset($node->field_company_email['und']) ? $node->field_company_email['und'][0]['email'] : '');
      $mainData['description'] = (isset($node->field_description['und']) ? $node->field_description['und'][0]['value'] : '');
      $mainData['url'] = (isset($node->field_website['und']) ? $node->field_website['und'][0]['value'] : '');
      $mainData['company_profile_cover_img'] = (isset($node->field_company_profile_cover_img['und'][0]['uri']) ? file_create_url($node->field_logo['und'][0]['uri']) : '');
      $mainData['fb_url'] = (isset($node->field_facebook['und']) ? $node->field_facebook['und'][0]['value'] : '');
      $mainData['company_gpo'] = (isset($node->field_company_gpo['und']) ? $node->field_company_gpo['und'][0]['value'] : '');
      $mainData['company_tagline'] = (isset($node->field_company_tagline['und']) ? $node->field_company_tagline['und'][0]['value'] : '');
      $mainData['skype_url'] = (isset($node->field_skype['und']) ? $node->field_skype['und'][0]['value'] : '');
      $mainData['linkdin_url'] = (isset($node->field_linkdin['und']) ? $node->field_linkdin['und'][0]['value'] : '');
      $mainData['company_type'] = (isset($node->field_organization_type['und']) ? $node->field_organization_type['und'][0]['value'] : '');
      $mainData['twitter_url'] = (isset($node->field_twitter['und']) ? $node->field_twitter['und'][0]['value'] : '');
      $mainData['instagram_url'] = (isset($node->field_instagram['und']) ? $node->field_instagram['und'][0]['value'] : '');
      $mainData['is_admin'] = 0;
      if(isset($user) && !empty($user->roles) &&  in_array('administrator', $user->roles)){
        $mainData['is_admin'] = 1;
      }
      $mainData['source'] = (isset($node->field_source_['und']) ? $node->field_source_['und'][0]['value'] : '');
      $mainData['service'] = (isset($node->field_service['und']) ? $node->field_service['und'][0]['value'] : '');
      $mainData['phone_verified'] = (isset($node->field_phone_verified['und']) ? $node->field_phone_verified['und'][0]['value'] : '');
      $mainData['field_in_person_verified'] = (isset($node->field_in_person_verified['und']) ? $node->field_in_person_verified['und'][0]['value'] : '');
      $mainData['field_company_inactive'] = (isset($node->field_company_inactive['und']) ? $node->field_company_inactive['und'][0]['value'] : '');
      $mainData['field_available_for_free'] = (isset($node->field_available_for_free['und']) ? $node->field_available_for_free['und'][0]['value'] : '');
      // check user role. if user is administrator then following fields will be displayed
      $getUserRole = og_get_user_roles('node', $company_id, $_REQUEST['user_id']);
      if(in_array('administrator member', $getUserRole)){
        $mainData['allow_capital_project_manager'] = (isset($node->field_allow_capital_projects_man['und']) ? $node->field_allow_capital_projects_man['und'][0]['value'] : '');
        $mainData['allow_insurance_certificate'] = (isset($node->field_allow_ins_certi_access['und']) ? $node->field_allow_ins_certi_access['und'][0]['value'] : '');
        $mainData['allow_onboarding'] = (isset($node->field_allow_onboarding_access['und']) ? $node->field_allow_onboarding_access['und'][0]['value'] : '');
        $mainData['multi_company_collaboration'] = (isset($node->field_multi_company_collaboratio['und']) ? $node->field_multi_company_collaboratio['und'][0]['value'] : '');
        $mainData['allow_m6alert'] = (isset($node->field_allow_m6alert['und']) ? $node->field_allow_m6alert['und'][0]['value'] : '');
        $mainData['allow_cost_manager'] = (isset($node->field_allow_cost_manager['und']) ? $node->field_allow_cost_manager['und'][0]['value'] : '');
        $mainData['allow_construction_manager'] = (isset($node->field_allow_construction_manager['und']) ? $node->field_allow_construction_manager['und'][0]['value'] : '');
        $mainData['allow_vendor_manager'] = (isset($node->field_allow_vendor_manager['und']) ? $node->field_allow_vendor_manager['und'][0]['value'] : '');
        $mainData['allow_routing_slip'] = (isset($node->field_allow_routing_slip_access['und']) ? $node->field_allow_routing_slip_access['und'][0]['value'] : '');
      }      

      $output['success'] = TRUE;
      $output['message'] = t('Record found.');
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = false; 
      $output['message'] = t('No data found');
    }
  }
  else{
    $output['success'] = false; 
    $output['message'] = t("Company id can't be empty");
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_edit_company_summary(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user = user_load($_REQUEST['user_id']);
    $node = node_load($company_id);    
    if(!empty($node)){
      $mainData = array();
      $mainData['legal_structure_data'] = getArrayValues(array("Individual/sole proprietor or single member LLC" => "Individual/sole proprietor or single member LLC", "C Corporation" => "C Corporation", "S Corporation" => "S Corporation", "LTD" => "LTD", "Partnership" => "Partnership", "Limited Liability Company" => "Limited Liability Company", "Not for Profit" => "Not for Profit", "Non-Profit" => "Non-Profit", "Other" => "Other"));

      $mainData['incorporated_state_data'] = getArrayValues(array("None" => "None", "Alabama" => "Alabama", "Alaska" => "Alaska", "Arizona" => "Arizona", "Arkansas" => "Arkansas", "California" => "California", "Colorado" => "Colorado", "Connecticut" => "Connecticut", "Delaware" => "Delaware", "Florida" => "Florida", "Georgia" => "Georgia", "Hawaii" => "Hawaii", "Idaho" => "Idaho", "Illinois" => "Illinois", "Indiana" => "Indiana", "Iowa" => "Iowa", "Kansas" => "Kansas", "Kentucky" => "Kentucky", "Louisiana" => "Louisiana", "Maine" => "Maine", "Maryland" => "Maryland", "Massachusetts" => "Massachusetts", "Michigan" => "Michigan", "Minnesota" => "Minnesota", "Mississippi" => "Mississippi", "Missouri" => "Missouri", "Montana" => "Montana", "Nebraska" => "Nebraska", "Nevada" => "Nevada", "New Hampshire" => "New Hampshire", "New Jersey" => "New Jersey", "New Mexico" => "New Mexico", "New York" => "New York", "North Carolina" => "North Carolina", "North Dakota" => "North Dakota", "Ohio" => "Ohio", "Oklahoma" => "Oklahoma", "Oregon" => "Oregon", "Pennsylvania" => "Pennsylvania", "Rhode Island" => "Rhode Island", "South Carolina" => "South Carolina", "South Dakota" => "South Dakota", "Tennessee" => "Tennessee", "Texas" => "Texas", "Utah" => "Utah", "Vermont" => "Vermont", "Virginia" => "Virginia", "Washington" => "Washington", "West Virginia" => "West Virginia", "Wisconsin" => "Wisconsin", "Wyoming" => "Wyoming"));

      $mainData['incorporated_country_data'] = getArrayValues(array("Afghanistan" => "Afghanistan", "Akrotiri" => "Akrotiri", "Albania" => "Albania", "Algeria" => "Algeria", "American Samoa" => "American Samoa", "Andorra" => "Andorra", "Angola" => "Angola", "Anguilla" => "Anguilla", "Antarctica" => "Antarctica", "Antigua and Barbuda" => "Antigua and Barbuda", "Argentina" => "Argentina", "Armenia" => "Armenia", "Aruba" => "Aruba", "Ashmore and Cartier Islands" => "Ashmore and Cartier Islands", "Australia" => "Australia", "Austria" => "Austria", "Azerbaijan" => "Azerbaijan", "Bahamas, The" => "Bahamas, The", "Bahrain" => "Bahrain", "Bangladesh" => "Bangladesh", "Barbados" => "Barbados", "Bassas da India" => "Bassas da India", "Belarus" => "Belarus", "Belgium" => "Belgium", "Belize" => "Belize", "Benin" => "Benin", "Bermuda" => "Bermuda", "Bhutan" => "Bhutan", "Bolivia" => "Bolivia", "Bosnia and Herzegovina" => "Bosnia and Herzegovina", "Botswana" => "Botswana", "Bouvet Island" => "Bouvet Island", "Brazil" => "Brazil", "British Indian Ocean Territory" => "British Indian Ocean Territory", "British Virgin Islands" => "British Virgin Islands", "Brunei" => "Brunei", "Bulgaria" => "Bulgaria", "Burkina Faso" => "Burkina Faso", "Burma" => "Burma", "Burundi" => "Burundi", "Cambodia" => "Cambodia", "Cameroon" => "Cameroon", "Canada" => "Canada", "Cape Verde" => "Cape Verde", "Cayman Islands" => "Cayman Islands", "Central African Republic" => "Central African Republic", "Chad" => "Chad", "Chile" => "Chile", "China" => "China", "Christmas Island" => "Christmas Island", "Clipperton Island" => "Clipperton Island", "Cocos (Keeling) Islands" => "Cocos (Keeling) Islands", "Colombia" => "Colombia", "Comoros" => "Comoros", "Congo, Democratic Republic of the" => "Congo, Democratic Republic of the", "Congo, Republic of the" => "Congo, Republic of the", "Cook Islands" => "Cook Islands", "Coral Sea Islands" => "Coral Sea Islands", "Costa Rica" => "Costa Rica", "Cote d'Ivoire" => "Cote d'Ivoire", "Croatia" => "Croatia", "Cuba" => "Cuba", "Cyprus" => "Cyprus", "Czech Republic" => "Czech Republic", "Denmark" => "Denmark", "Dhekelia" => "Dhekelia", "Djibouti" => "Djibouti", "Dominica" => "Dominica", "Dominican Republic" => "Dominican Republic", "Ecuador" => "Ecuador", "Egypt" => "Egypt", "El Salvador" => "El Salvador", "Equatorial Guinea" => "Equatorial Guinea", "Eritrea" => "Eritrea", "Estonia" => "Estonia", "Ethiopia" => "Ethiopia", "Europa Island" => "Europa Island", "Falkland Islands (Islas Malvinas)" => "Falkland Islands (Islas Malvinas)", "Faroe Islands" => "Faroe Islands", "Fiji" => "Fiji", "Finland" => "Finland", "France" => "France", "French Guiana" => "French Guiana", "French Polynesia" => "French Polynesia", "French Southern and Antarctic Lands" => "French Southern and Antarctic Lands", "Gabon" => "Gabon", "Gambia, The" => "Gambia, The", "Gaza Strip" => "Gaza Strip", "Georgia" => "Georgia", "Germany" => "Germany", "Ghana" => "Ghana", "Gibraltar" => "Gibraltar", "Glorioso Islands" => "Glorioso Islands", "Greece" => "Greece", "Greenland" => "Greenland", "Grenada" => "Grenada", "Guadeloupe" => "Guadeloupe", "Guam" => "Guam", "Guatemala" => "Guatemala", "Guernsey" => "Guernsey", "Guinea" => "Guinea", "Guinea-Bissau" => "Guinea-Bissau", "Guyana" => "Guyana", "Haiti" => "Haiti", "Heard Island and McDonald Islands" => "Heard Island and McDonald Islands", "Holy See (Vatican City)" => "Holy See (Vatican City)", "Honduras" => "Honduras", "Hong Kong" => "Hong Kong", "Hungary" => "Hungary", "Iceland" => "Iceland", "India" => "India", "Indonesia" => "Indonesia", "Iran" => "Iran", "Iraq" => "Iraq", "Ireland" => "Ireland", "Isle of Man" => "Isle of Man", "Israel" => "Israel", "Italy" => "Italy", "Jamaica" => "Jamaica", "Jan Mayen" => "Jan Mayen", "Japan" => "Japan", "Jersey" => "Jersey", "Jordan" => "Jordan", "Juan de Nova Island" => "Juan de Nova Island", "Kazakhstan" => "Kazakhstan", "Kenya" => "Kenya", "Kiribati" => "Kiribati", "Korea, North" => "Korea, North", "Korea, South" => "Korea, South", "Kuwait" => "Kuwait", "Kyrgyzstan" => "Kyrgyzstan", "Laos" => "Laos", "Latvia" => "Latvia", "Lebanon" => "Lebanon", "Lesotho" => "Lesotho", "Liberia" => "Liberia", "Libya" => "Libya", "Liechtenstein" => "Liechtenstein", "Lithuania" => "Lithuania", "Luxembourg" => "Luxembourg", "Macau" => "Macau", "Macedonia" => "Macedonia", "Madagascar" => "Madagascar", "Malawi" => "Malawi", "Malaysia" => "Malaysia", "Maldives" => "Maldives", "Mali" => "Mali", "Malta" => "Malta", "Marshall Islands" => "Marshall Islands", "Martinique" => "Martinique", "Mauritania" => "Mauritania", "Mauritius" => "Mauritius", "Mayotte" => "Mayotte", "Mexico" => "Mexico", "Micronesia, Federated States of" => "Micronesia, Federated States of", "Moldova" => "Moldova", "Monaco" => "Monaco", "Mongolia" => "Mongolia", "Montserrat" => "Montserrat", "Morocco" => "Morocco", "Mozambique" => "Mozambique", "Namibia" => "Namibia", "Nauru" => "Nauru", "Navassa Island" => "Navassa Island", "Nepal" => "Nepal", "Netherlands" => "Netherlands", "Netherlands Antilles" => "Netherlands Antilles", "New Caledonia" => "New Caledonia", "New Zealand" => "New Zealand", "Nicaragua" => "Nicaragua", "Niger" => "Niger", "Nigeria" => "Nigeria", "Niue" => "Niue", "Norfolk Island" => "Norfolk Island", "Northern Mariana Islands" => "Northern Mariana Islands", "Norway" => "Norway", "Oman" => "Oman", "Pakistan" => "Pakistan", "Palau" => "Palau", "Panama" => "Panama", "Papua New Guinea" => "Papua New Guinea", "Paracel Islands" => "Paracel Islands", "Paraguay" => "Paraguay", "Peru" => "Peru", "Philippines" => "Philippines", "Pitcairn Islands" => "Pitcairn Islands", "Poland" => "Poland", "Portugal" => "Portugal", "Puerto Rico" => "Puerto Rico", "Qatar" => "Qatar", "Reunion" => "Reunion", "Romania" => "Romania", "Russia" => "Russia", "Rwanda" => "Rwanda", "Saint Helena" => "Saint Helena", "Saint Kitts and Nevis" => "Saint Kitts and Nevis", "Saint Lucia" => "Saint Lucia", "Saint Pierre and Miquelon" => "Saint Pierre and Miquelon", "Saint Vincent and the Grenadines" => "Saint Vincent and the Grenadines", "Samoa" => "Samoa", "San Marino" => "San Marino", "Sao Tome and Principe" => "Sao Tome and Principe", "Saudi Arabia" => "Saudi Arabia", "Senegal" => "Senegal", "Serbia and Montenegro" => "Serbia and Montenegro", "Seychelles" => "Seychelles", "Sierra Leone" => "Sierra Leone", "Singapore" => "Singapore", "Slovakia" => "Slovakia", "Slovenia" => "Slovenia", "Solomon Islands" => "Solomon Islands", "Somalia" => "Somalia", "South Africa" => "South Africa", "South Georgia and the South Sandwich Islands" => "South Georgia and the South Sandwich Islands", "Spain" => "Spain", "Spratly Islands" => "Spratly Islands", "Sri Lanka" => "Sri Lanka", "Sudan" => "Sudan", "Suriname" => "Suriname", "Svalbard" => "Svalbard", "Swaziland" => "Swaziland", "Sweden" => "Sweden", "Switzerland" => "Switzerland", "Syria" => "Syria", "Taiwan" => "Taiwan", "Tajikistan" => "Tajikistan", "Tanzania" => "Tanzania", "Thailand" => "Thailand", "Timor-Leste" => "Timor-Leste", "Togo" => "Togo", "Tokelau" => "Tokelau", "Tonga" => "Tonga", "Trinidad and Tobago" => "Trinidad and Tobago", "Tromelin Island" => "Tromelin Island", "Tunisia" => "Tunisia", "Turkey" => "Turkey", "Turkmenistan" => "Turkmenistan", "Turks and Caicos Islands" => "Turks and Caicos Islands", "Tuvalu" => "Tuvalu", "Uganda" => "Uganda", "Ukraine" => "Ukraine", "United Arab Emirates" => "United Arab Emirates", "United Kingdom" => "United Kingdom", "United States" => "United States", "Uruguay" => "Uruguay", "Uzbekistan" => "Uzbekistan", "Vanuatu" => "Vanuatu", "Venezuela" => "Venezuela", "Vietnam" => "Vietnam", "Virgin Islands" => "Virgin Islands", "Wake Island" => "Wake Island", "Wallis and Futuna" => "Wallis and Futuna", "West Bank" => "West Bank", "Western Sahara" => "Western Sahara", "Yemen" => "Yemen", "Zambia" => "Zambia", "Zimbabwe" => "Zimbabwe"));

      $mainData['bondable_data'] = getArrayValues("yes|Yes", "no|No", "not_certain|Not Certain");

      $mainData['legal_name'] = (isset($node->field_legal_name['und']) ? $node->field_legal_name['und'][0]['value'] : '');
      $mainData['legal_structure'] = (isset($node->field_legal_structure['und']) ? $node->field_legal_structure['und'][0]['value'] : '');
      $mainData['incorporated_state'] = (isset($node->field_incorporated_state['und']) ? $node->field_incorporated_state['und'][0]['value'] : '');
      $mainData['incorporated_country'] = (isset($node->field_incorporated_country['und']) ? $node->field_incorporated_country['und'][0]['value'] : '');
      $mainData['taxpayer_ssn_ein'] = (isset($node->field_taxpayer_ssn_ein['und']) ? $node->field_taxpayer_ssn_ein['und'][0]['value'] : '');
      $mainData['duns_number'] = (isset($node->field_duns_number['und']) ? $node->field_duns_number['und'][0]['value'] : '');
      $mainData['keywords'] = (isset($node->field_keywords['und']) ? $node->field_keywords['und'][0]['value'] : '');
      $mainData['number_of_employees'] = (isset($node->field_number_of_employees['und']) ? $node->field_number_of_employees['und'][0]['value'] : '');
      $mainData['annual_revenue'] = (isset($node->field_annual_revenue['und']) ? $node->field_annual_revenue['und'][0]['value'] : '');
      $mainData['year_founded'] = (isset($node->field_year_founded['und']) ? $node->field_year_founded['und'][0]['value'] : '');
      $mainData['timezone'] = (isset($node->field_timezone['und']) ? $node->field_timezone['und'][0]['value'] : '');
      $mainData['bondable'] = (isset($node->field_bondable_['und']) ? $node->field_bondable_['und'][0]['value'] : '');
      $mainData['bond_amount_per_project'] = (isset($node->field_bond_amount_per_project['und']) ? $node->field_bond_amount_per_project['und'][0]['value'] : '');
      $mainData['total_bond_amount'] = (isset($node->field_total_bond_amount['und']) ? $node->field_total_bond_amount['und'][0]['value'] : '');
      $mainData['average_annual_revenue_for'] = (isset($node->field_average_annual_revenue_for['und']) ? $node->field_average_annual_revenue_for['und'][0]['value'] : '');


      $output['success'] = TRUE;
      $output['message'] = t('Record found.');
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = false; 
      $output['message'] = t('No data found');
    }
  }
  else{
    $output['success'] = false; 
    $output['message'] = t("Company id can't be empty");
  }
  drupal_json_output($output);
  drupal_exit();
}

function company_profile_node_edit_location(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user = user_load($_REQUEST['user_id']);
    $node = node_load($company_id);
    // default message
    $output['success'] = FALSE;
    $output['message'] = t('No data found.');
    if(!empty($node)){
      $mainData = array();
      $location = $node->field_company_locations['und'];
      if(!empty($location)){
        foreach ($location as $key => $value) {
          //$mainData[$key] = field_collection_item_load($value['value']);
          $mainData[$key] = $value['value'];
        }
        $output['success'] = TRUE;
        $output['message'] = t('Record found.');
        $output['data'] = $mainData;
      }
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for news feed share on company profile
 */
function company_profile_share_news_feed(){
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
  if (!empty($_REQUEST['message'])) {
    $output['success'] = FALSE;
    $output['message'] = t('Status could not be saved.');
    $type = 'og';      
    $recipient = $account;
    if(!empty($_REQUEST['nid'])){
      $recipient_id = $_REQUEST['nid'];
      $recipient = node_load($recipient_id);
    }
    // Getting message.
    $message = $_REQUEST['message'];
    if(isset($_REQUEST['s_id']) && !empty($_REQUEST['s_id'])){
      $statusId = $_REQUEST['s_id'];
      $loadStatus = statuses_load($statusId);
      $account = user_load($loadStatus->sender);
      $recipient = node_load($loadStatus->recipient);
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
        $status_data = _get_status_data_prepared($account, $status->sid, $recipient_id);
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
        $status_data = _get_status_data_prepared($account, $status->sid, $recipient_id);
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
          if (!empty($output['status']) && !empty($output['status'][0]['status_id'])) {
            // If we have status along with this image, then we have status id
            // of it.
            // Trying to save a record of image.
            db_insert('fbsmp')
              ->fields(array(
                'sid' => $output['status'][0]['status_id'],
                'type' => 'photo',
                'data' => $data,
              ))
              ->execute();
            // Getting status data again.              
            $status_data = _get_status_data_prepared($account, $output['status'][0]['status_id'], $recipient_id);
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
            $blank_status = statuses_save_status($account, $type, $message, $account, $options);
            if (!empty($blank_status->sid)) {
              // It means a blank status has been created for this image.
              $status_data = _get_status_data_prepared($account, $blank_status->sid, $recipient_id);
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
 * function for get my company user list with role
 */
function user_management_my_company_user(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $searchStr = '';
    $sortStr = "users_created DESC";
    //$user = user_load($user_id);
    if(isset($_REQUEST['search_data']) && !empty($_REQUEST['search_data'])){
      $searchData = $_REQUEST['search_data'];
      $searchStr = "AND (CONCAT_WS(' ', users.mail, ' ', users.name) LIKE '%".$searchData."%')";
    }
    if(isset($_REQUEST['sort_data']) && !empty($_REQUEST['sort_data'])){
      $sortData = $_REQUEST['sort_data'];
      if($sortData == 'name'){
        $sortStr = "users_name ASC";
      }
    }
    $data = db_query("SELECT DISTINCT users.uid AS uid, og_membership.id AS og_membership_id, users.mail AS users_mail, users.login AS users_login, og_membership_users.group_type AS og_membership_users_group_type, og_membership.gid AS og_membership_gid, users.name AS users_name, og_membership.state AS og_membership_state, users.created AS users_created, 'user' AS field_data_field_licensed_user_entity_type, 'user' AS field_data_field_last_name_user_entity_type, 'user' AS field_data_field_first_name_user_entity_type FROM {users} users LEFT JOIN {og_membership} og_membership_users ON users.uid = og_membership_users.etid AND og_membership_users.entity_type = 'user' LEFT JOIN {og_membership} og_membership ON users.uid = og_membership.etid AND (og_membership.entity_type = 'user' AND og_membership.entity_type = 'user') WHERE (( (og_membership.gid = ".$company_id." ) )AND(( (users.status <> '0') ".$searchStr." ))) ORDER BY ".$sortStr);  
    $result = $data->fetchAll();
    $mainData = array();
    if(!empty($result)){
      foreach ($result as $key => $value) {
        $mainData[$key]['uid'] = $value->uid;
        $mainData[$key]['og_membership_id'] = $value->og_membership_id;
        $mainData[$key]['og_membership_state'] = $value->og_membership_state;
        $mainData[$key]['block_text'] = '';
        // block or unblock text
        if($value->og_membership_state == 1){
          $mainData[$key]['block_text'] = 'block';
        }
        else if($value->og_membership_state == 3){
          $mainData[$key]['block_text'] = 'unblock';
        }
        // load og membership to get request value
        $ogLoad = og_membership_load($value->og_membership_id);
        $requestMsg = '';
        if(isset($ogLoad->og_membership_request['und']) && !empty($ogLoad->og_membership_request['und'])){
          $requestMsg = $ogLoad->og_membership_request['und'][0]['value'];
        }
        $mainData[$key]['request_message'] = $requestMsg;
        $cmpUser = user_load($value->uid);
        $fullName = (isset($cmpUser->field_first_name['und']))?$cmpUser->field_first_name['und'][0]['value']:'';
        $mname = (isset($cmpUser->field_middle_name['und']))?$cmpUser->field_middle_name['und'][0]['value']:'';
        $lname = (isset($cmpUser->field_last_name['und']))?$cmpUser->field_last_name['und'][0]['value']:'';
        $fullName .= !empty($mname)?' '.$mname:'';
        $fullName .= !empty($lname)?' '.$lname:'';
        $mainData[$key]['full_name'] = ucwords($fullName);
        $mainData[$key]['user_name'] = $value->users_name;
        $mainData[$key]['user_email'] = $value->users_mail;
        $mainData[$key]['last_login'] = date('Y-m-d H:i:s', $value->users_login);
        $mainData[$key]['license'] = (isset($cmpUser->field_licensed['und']) && !empty($cmpUser->field_licensed['und'][0]['value'])) ? 'yes' : 'no';
        // get user roles
        $currentUserOgRoles = og_get_user_roles('node',$company_id,$value->uid);
        /*if(($key = array_search("member", $currentUserOgRoles)) !== false){
          unset($currentUserOgRoles[$key]);
        }*/
        $mainData[$key]['is_admin'] = $mainData[$key]['is_admin_selected'] = FALSE;
        if(in_array('company admin', $currentUserOgRoles)){
          $mainData[$key]['is_admin'] = TRUE;
        }
        if(in_array('Company Admin Support', $currentUserOgRoles)){ 
          $mainData[$key]['is_admin_selected'] = TRUE;
        }
        $userRole = (!empty($currentUserOgRoles) ? implode(",", $currentUserOgRoles) : '');
        $mainData[$key]['roles'] = $userRole;
      }
      $output['success'] = TRUE;
      $output['message'] = t('Record found.');
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('No data found.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for get pending request people list
 */
function user_management_pending_request(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $searchStr = '';
    $sortStr = "users_created DESC";
    //$user = user_load($user_id);
    if(isset($_REQUEST['search_data']) && !empty($_REQUEST['search_data'])){
      $searchData = $_REQUEST['search_data'];
      $searchStr = "AND( (CONCAT_WS(' ', field_data_field_address.field_address_name_line, ' ', users.mail) LIKE '%".$searchData."%'))";      
    }
    if(isset($_REQUEST['sort_data']) && !empty($_REQUEST['sort_data'])){
      $sortData = $_REQUEST['sort_data'];
      if($sortData == 'name'){
        $sortStr = "users_name ASC";
      }
    }
    $data = db_query("SELECT users.uid AS uid, users.login AS users_login, users.name AS users_name, field_data_field_address.field_address_name_line AS field_data_field_address_field_address_name_line, users.mail AS users_mail, users.created AS users_created FROM {users} users LEFT JOIN {field_data_field_user_company} field_data_field_user_company ON users.uid = field_data_field_user_company.entity_id AND (field_data_field_user_company.entity_type = 'user' AND field_data_field_user_company.deleted = '0') LEFT JOIN {field_data_field_address} field_data_field_address ON users.uid = field_data_field_address.entity_id AND (field_data_field_address.entity_type = 'user' AND field_data_field_address.deleted = '0') WHERE (( (field_data_field_user_company.field_user_company_target_id = ".$company_id." ) )AND(( (users.status <> '0') ".$searchStr." ))) ORDER BY ".$sortStr);    
    $result = $data->fetchAll();
    $mainData = array();
    if(!empty($result)){
      foreach ($result as $key => $value) {
        $mainData[$key]['uid'] = $value->uid;
        $cmpUser = user_load($value->uid);
        $fullName = (isset($cmpUser->field_first_name['und']))?$cmpUser->field_first_name['und'][0]['value']:'';
        $mname = (isset($cmpUser->field_middle_name['und']))?$cmpUser->field_middle_name['und'][0]['value']:'';
        $lname = (isset($cmpUser->field_last_name['und']))?$cmpUser->field_last_name['und'][0]['value']:'';
        $fullName .= !empty($mname)?' '.$mname:'';
        $fullName .= !empty($lname)?' '.$lname:'';
        $mainData[$key]['full_name'] = ucwords($fullName);
        $mainData[$key]['user_name'] = $value->users_name;
        $mainData[$key]['user_email'] = $value->users_mail;
        $mainData[$key]['last_login'] = date('Y-m-d H:i:s', $value->users_login);
        $mainData[$key]['phone'] = (isset($cmpUser->field_phone['und']) && !empty($cmpUser->field_phone['und'][0]['value'])) ? $cmpUser->field_phone['und'][0]['value'] : '';
      }
      $output['success'] = TRUE;
      $output['message'] = t('Record found.');
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('No data found.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}

function user_management_invite_users(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $company = node_load($company_id);
    $user_id = $_REQUEST['user_id'];
    $user = user_load($user_id);
    $userRoles = $user->roles;
    $userRoleskey = array_keys($userRoles);
    $rolesArray = array(7, 8, 9, 4);
    $userplan = array_intersect($rolesArray, $userRoleskey);
    foreach ($userplan as $key => $value) {
      $planid = $value;
    }
    $arr = explode(' ',trim($userRoles[$planid]));
    $membershipLevel = $arr[0];
    $mainData = $defaultRole = array();
    $mainData['company'] = $company->title;
    $mainData['membership_level'] = $membershipLevel;
    // get default role
    $indexarray = array(5, 12, 41, 46);
    $userRoles = user_roles();
    for ($i = 0; $i < count($indexarray); $i++) {
      $defaultRole[$i]['id'] = $indexarray[$i];
      $defaultRole[$i]['value'] = $userRoles[$indexarray[$i]];
    }
    $mainData['default_role'] = $defaultRole;

    $output['success'] = TRUE;
    $output['message'] = t('Record found.');
    $output['data'] = $mainData;   
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/** 
 * function for invite user form submit
 */
function user_management_invite_users_submit(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    //$company = node_load($company_id);
    $user_id = $_REQUEST['user_id'];
    $user = user_load($user_id);
    if(isset($_REQUEST['email']) && !empty($_REQUEST['email'])){
      $email = $_REQUEST['email'];
      $roleid = $_REQUEST['roleid'];
      $mailkey = 'company_mail___invite_user_by_company';
      $params = _get_mail_variables($mailkey, $type = 'company', $user, $other = array('email' => $email,'company_nid' => $company_id, 'user_id' => $user_id));
      $to = $email;
      $return = drupal_mail($params['module'], $params['key'], $to, $params['language'], $params);
      if (is_numeric($company_id) && $node = node_load($company_id)) {
        if (isset($node->field_m6level[LANGUAGE_NONE][0]['value'])) {
          if ($node->field_m6level[LANGUAGE_NONE][0]['value'] < 5) {
            $node->field_m6level[LANGUAGE_NONE][0]['value'] = 5;
            node_save($node);
          }
        }
        else {
          $node->field_m6level[LANGUAGE_NONE][0]['value'] = 5;
          node_save($node);
        }
      }
      $output['success'] = TRUE;
      $output['message'] = t('User invited successfully.');      
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('Email can\'t be null.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for modify user role content
 */
function user_management_modify_user_role(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    if(!empty($_REQUEST['uid']) && !empty($_REQUEST['uid'])){
      $company = node_load($company_id);
      $uid = $_REQUEST['uid'];
      $mainData = array();
      $mainData['fullname'] = _get_user_full_name($uid);
      // role description data
      $CompanyAdminDescription = 'The Corporate administrator role has the ability to create administrator accounts and has the ability to add/remove/modify all aspects of the company.';
      $StaffDescription = 'The staff role only has access to the specific items or sections that they have been given access to.';
      $InsuranceManagerDescription='The Insurance Certificates Manager role has the ability to review and respond to all Insurance Certificates either sent or received by members of the company.  Staff members have the ability to send and receive Insurance Certificates and they only have access to those that they have sent or received.';
      $M6IDManagerDescription = 'The M6ID Manager has access to approve employees for respective access levels on behalf of the company.  Site Managers and general Staff members do not have access to this feature for their respective peers.';
      $SiteManagerDescription = 'The Site Manager role works independently of the M6ID Manager and has the ability to create M6ID projects and approve respective contract workers for those projects they create.  The M6ID Manager has access to all M6ID Projects.';
      $AlertManagerDescription = 'The Alert Manager has the ability to create alert templates, groups and send group texts.';
      $vendor_manager_description = t('Allow Vendor Manager');
      $supply_chain_lead_description = t('Allow Supply Chain Lead.');
      $material_manager_description = t('Allow Material Manager');
      if(isset($_SESSION['CURRENTPROJECT'])) {
        $getProjectStatus = $_SESSION['CURRENTPROJECT'];
        $projectTitle = $getProjectStatus == 'CM'?'Cost Manager':'Capital Project Manger'; 
      }
      else {
        $projectTitle = 'Cost Manager';
      }
      $ProgramManagerDescription = 'The Program Manager can see and make changes to projects in '.$projectTitle.'. This includes projects where he/she isn&apos;t the project manager.'; 
      $ProjectManagerDescription = 'The Project Manager role has the capability to manage projects on '.$projectTitle.'. He/she does not have the right review other projects where he/she is not the Project Manager.';

      $ogrolesk = og_roles('node', 'organization');
      $ogroles = array_flip($ogrolesk);
      $og_roles_id_summary = array($ogroles['company admin']=>$CompanyAdminDescription,$ogroles['staff']=>$StaffDescription,$ogroles['Insurance Certificate Manager']=>$InsuranceManagerDescription,$ogroles['M6ID Manager']=>$M6IDManagerDescription,$ogroles['Site Manager']=>$SiteManagerDescription,$ogroles['Alert Manager']=>$AlertManagerDescription,$ogroles['Program manager']=>$ProgramManagerDescription,$ogroles['project manager']=>$ProjectManagerDescription, $ogroles['Vendor Manager'] => $vendor_manager_description, $ogroles['Supply Chain Lead'] => $supply_chain_lead_description, $ogroles['Material Manager'] => $material_manager_description);
    
      $og_roles_id_popover = array($ogroles['company admin']=>'',$ogroles['staff']=>'',$ogroles['Insurance Certificate Manager']=>'',$ogroles['M6ID Manager']=>'',$ogroles['Site Manager']=>'',$ogroles['Alert Manager']=>'', $ogroles['Vendor Manager']=>'',$ogroles['Supply Chain Lead']=>'',$ogroles['Material Manager']=>'');
    
      $InsCertAccess = isset($company->field_allow_ins_certi_access['und'])?$company->field_allow_ins_certi_access['und'][0]['value']:'';
      $M6IDAccess = isset($company->field_allow_onboarding_access['und'])?$company->field_allow_onboarding_access['und'][0]['value']:'';
      $AlertAccess = isset($company->field_allow_m6alert['und'])?$company->field_allow_m6alert['und'][0]['value']:'';
      $CostAccess = isset($company->field_allow_cost_manager['und'])?$company->field_allow_cost_manager['und'][0]['value']:'';
      $vendor_access = isset($company->field_allow_vendor_manager['und']) ? $company->field_allow_vendor_manager['und'][0]['value'] : '0';
      $supplyChainLeadAccess = isset($company->field_allow_supply_chain_lead['und']) ? $company->field_allow_supply_chain_lead['und'][0]['value'] : '0';
      $materialManagerAcess = isset($company->field_allow_material_manager['und']) ? $company->field_allow_material_manager['und'][0]['value'] : '0';
      $RoleOverPopup = "Your company needs to purchase this product prior to use. Contact <a href='mailto:sales@m6connect.com'>sales@m6connect.com</a>";

      $og_roles_id_popover[$ogroles['Insurance Certificate Manager']] = $og_roles_id_popover[$ogroles['M6ID Manager']] = $og_roles_id_popover[$ogroles['Site Manager']] = $og_roles_id_popover[$ogroles['Alert Manager']] = $og_roles_id_popover[$ogroles['Program manager']] = $og_roles_id_popover[$ogroles['project manager']] = $og_roles_id_popover[$ogroles['Vendor Manager']] = $og_roles_id_popover[$ogroles['Supply Chain Lead']] = $og_roles_id_popover[$ogroles['Material Manager']] = '';
      
      if(empty($InsCertAccess)){
        $og_roles_id_popover[$ogroles['Insurance Certificate Manager']] = $RoleOverPopup;
      }
      if(empty($M6IDAccess)){
        $og_roles_id_popover[$ogroles['M6ID Manager']] = $RoleOverPopup;
        $og_roles_id_popover[$ogroles['Site Manager']] = $RoleOverPopup;
      }
      if(empty($AlertAccess)){
        $og_roles_id_popover[$ogroles['Alert Manager']] = $RoleOverPopup;
      }
      if(empty($CostAccess)){
        $og_roles_id_popover[$ogroles['Program manager']] = $RoleOverPopup;
        $og_roles_id_popover[$ogroles['project manager']] = $RoleOverPopup;
      }
      if(empty($vendor_access)){
        $og_roles_id_popover[$ogroles['Vendor Manager']] = $RoleOverPopup;
      }
      if(empty($supplyChainLeadAccess)){
        $og_roles_id_popover[$ogroles['Supply Chain Lead']] = $RoleOverPopup;
      }
      if(empty($materialManagerAcess)){
        $og_roles_id_popover[$ogroles['Material Manager']] = $RoleOverPopup;
      }
      $roleData = array();$i=0;
      $currentUserOgRoles = array_keys(og_get_user_roles('node',$company_id,$uid));
      foreach ($og_roles_id_summary as $OgRoleKey => $OgRoleSummary) {
        $selected = $access = 0;
        if(empty($og_roles_id_popover[$OgRoleKey])){
          $access = 1;
        }
        if(in_array($OgRoleKey, $currentUserOgRoles)){
          $selected = 1;
        }
        $roleData[$i]['access'] = $access;
        $roleData[$i]['selected'] = $selected;
        $roleData[$i]['role_id'] = $OgRoleKey;
        $roleData[$i]['role'] = ucwords($ogrolesk[$OgRoleKey]);
        $roleData[$i]['desc'] = $OgRoleSummary;
        $i++;
      }
      $mainData['success'] = TRUE;
      $mainData['message'] = t('Record found');
      $mainData['roleData'] = $roleData;
      drupal_json_output($mainData);
      drupal_exit();      
    }
  }
}
/**
 * function for update user role in user management section
 */
function user_management_modify_user_role_submit(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(!empty($_REQUEST['uid']) && !empty($_REQUEST['uid'])){
      $uid = $_REQUEST['uid'];
      if(isset($_REQUEST['newrols']) && !empty($_REQUEST['newrols'])){
        $fullname = _get_user_full_name($uid);
        $ogrolesk = og_roles('node', 'organization');
        $ogroles = array_flip($ogrolesk);
        $user_gid = $company_id;
        $user_og_roles = og_get_user_roles('node', $user_gid, $uid);
        $cmpReletedRoles = array($ogroles['company admin'], $ogroles['staff'],$ogroles['Insurance Certificate Manager'],$ogroles['M6ID Manager'],$ogroles['Site Manager'],$ogroles['Alert Manager'],$ogroles['Program manager'],$ogroles['project manager'], $ogroles['Vendor Manager'], $ogroles['Supply Chain Lead'], $ogroles['Material Manager'], $ogroles['Department Approver']);
        $roleData = array();
        $dataRole = json_decode($_REQUEST['newrols']);
        foreach ($dataRole as $key => $value) {
          $applyUserRoles[$key] = $value->role_id;
        }
        foreach ($cmpReletedRoles as $delta => $roleId) {
          if (in_array($roleId, $applyUserRoles)) {
            if (!isset($user_og_roles[$roleId])) {
              og_role_grant('node', $company_id, $uid, $roleId);
            }
          } else {
            if (isset($user_og_roles[$roleId])) {                
              og_role_revoke('node', $company_id, $uid, $roleId);
            }
          }
        }
        $output['success'] = TRUE;
        $output['message'] = t('Roles has been updated.');
      } 
      else{
        $output['success'] = FALSE;
        $output['message'] = t('Role ids can\'t be null.');
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('Uid can\'t be null.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for updating admim support role for user
 */
function user_management_update_admin_support_role(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    //$user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['uid']) && !empty($_REQUEST['uid'])){
      $uid = $_REQUEST['uid'];
      $currentUserOgRoles = array_values(og_get_user_roles('node',$company_id,$uid));
      if(in_array('company admin', $currentUserOgRoles)){
        $ogrolesk = og_roles('node', 'organization');
        $ogroles = array_flip($ogrolesk);
        $roleId = $ogroles['Company Admin Support'];
        if(isset($roleId)){ 
          og_role_grant('node', $company_id, $uid, $roleId);
          $query= db_select('og_membership','og');
          $query->join('og_users_roles','ogur','ogur.uid=og.etid AND ogur.gid=og.gid AND ogur.group_type=:GroupType',array(':GroupType'=>'node'));
          $query->fields('og', array('etid'));
          $query->condition('og.gid',$company_id,'=');
          $query->condition('og.entity_type','user','=');
          $query->condition('ogur.rid',$ogroles['Company Admin Support'],'=');
          $query->condition('og.etid',$uid,'!=');
          $companyAdminSupportUsers  = $query->execute()->fetchCol();
          if(!empty($companyAdminSupportUsers)){
            foreach($companyAdminSupportUsers as $delta => $userUidToRemove){
              og_role_revoke('node', $company_id, $userUidToRemove, $roleId); 
            }
          }
        }
        $output['success'] = TRUE;
        $output['message'] = t('Role updated successfully.');
        $output['data'] = 1;
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = t('User not allow for this action.');
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('User uid can\'t be null.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for send user license data
 */
function user_management_manage_user_license_data(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $mainData = array();
    $query = db_query('SELECT lp.user_id AS owner_id,lp.key_id AS key_id,lp.purchased_date AS purchased_date,la.is_active as is_active, lm.license_key AS l_key, lm.valid_from AS valid_from, lm.valid_till AS valid_till, la.assign_by AS assign_by, la.assign_to AS assign_to, lm.product_id as product_id FROM license_purchased AS lp JOIN license_master AS lm ON(lp.key_id=lm.id) LEFT JOIN license_assign AS la ON(lp.key_id=la.key_id and la.is_active=1) where lp.user_id = ' . $user_id . ' and lp.cid = ' . $company_id . ';');
    $i = array();
    $default_key = 0;
    $disabled = array();
    $total_license;
    foreach ($query as $row) {
      $total_license[$row->key_id] = $row;
      if (is_numeric($row->assign_to) && $row->is_active == 1) {
        $i[$row->key_id] = $row->assign_to;
      }
    }
    $og_nodes = $company_id;
    $select_member_query = "SELECT DISTINCT users.uid AS uid, users.mail AS users_mail,la.is_active as is_active, last_name.field_last_name_value AS last_name_value, first_name.field_first_name_value AS first_name_value, users.login AS users_login, users.name AS users_name, users.created AS users_created, 'user' AS field_data_field_licensed_user_entity_type, 'user' AS field_data_field_last_name_user_entity_type, 'user' AS field_data_field_first_name_user_entity_type, la.assign_to as assign_to FROM users users LEFT JOIN og_membership og_membership ON (users.uid = og_membership.etid AND og_membership.entity_type = 'user') LEFT JOIN field_data_field_last_name AS last_name ON (users.uid=last_name.entity_id) LEFT JOIN field_data_field_first_name AS first_name ON (users.uid=first_name.entity_id) LEFT JOIN license_assign AS la ON (la.assign_to=users.uid) WHERE (( (og_membership.gid = '" . $og_nodes . "' ) )AND(( (users.status <> '0') ))) ORDER BY users_created DESC, is_active asc;";
      $select_memeber_result = db_query($select_member_query);
      $existing_user_data = $licenseData = array();$j = 0;
      $mainData['total_license'] = count($total_license);
      $mainData['available_license'] = (count($total_license) - (count($i)));
      foreach ($select_memeber_result as $select_memeber_row) {
        $existing_user = 'No';
        if (is_numeric($select_memeber_row->assign_to) && $select_memeber_row->is_active == 1) {
          $existing_user = 'Yes';
          //$existing_user_data[] = $select_memeber_row->assign_to;
        }
        $licenseData[$j]['uid'] = $select_memeber_row->uid;
        $licenseData[$j]['existing_user'] = $existing_user;
        $licenseData[$j]['first_name'] = $select_memeber_row->first_name_value;
        $licenseData[$j]['last_name'] = $select_memeber_row->last_name_value;
        $j++;
      }
      $mainData['licenseData'] = $licenseData;
      $output['success'] = TRUE;
      $output['message'] = t('Record found.');
      $output['data'] = $mainData;
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for submit user license data
 */
function user_management_manage_user_license_data_submit(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['selected_uids']) && !empty($_REQUEST['selected_uids'])){
      $selected_uids = json_decode($_REQUEST['selected_uids']);
      $uids = array();
      foreach ($selected_uids as $key => $value) {
        $uids[$key] = $value->uid;
      }
      // query to get license data from user id and company id
      $query = db_query('SELECT lp.user_id AS owner_id, lp.key_id AS key_id, lp.purchased_date AS purchased_date,la.is_active as is_active, lm.license_key AS l_key, lm.valid_from AS valid_from, lm.valid_till AS valid_till, la.assign_by AS assign_by, la.assign_to AS assign_to, lm.product_id as product_id FROM license_purchased AS lp JOIN license_master AS lm ON(lp.key_id=lm.id) LEFT JOIN license_assign AS la ON(lp.key_id=la.key_id) where lp.user_id = ' . $user_id . ' and lp.cid = '.$company_id.' ;');
      $i = $default_key = 0;
      $disabled = $existing_user_license = $key_id_data = $total_license = $old_user = $need_delete = $new_user = array();
      foreach ($query as $row) {
        $total_license[$row->key_id] = $row;
        if (is_numeric($row->assign_to) && $row->is_active == 1) {
          $existing_user_license[$row->assign_to] = $row->assign_to;
          $key_id_data[$row->assign_to] = $row->key_id;
          $i++;
        }
        else {
          $key_id_data[] = $row->key_id;
        }
      }
      if (count($total_license) < count($uids)) {
        $output['success'] = FALSE;
        $output['message'] = t('You must have available licenses to assign. Uncheck current license holder first or upgrade and add additional licenses.');
      }
      else{
        foreach ($uids as $userkey => $uservalue) {
          if (in_array($uservalue, $existing_user_license)) {
            $old_user[$userkey] = $uservalue;
            unset($existing_user_license[$userkey]);
          } else {
            $new_user[$userkey] = $uservalue;
          }
        }
        foreach ($old_user as $k => $v) {
          unset($key_id_data[$v]);
        }
        $new_key_id_data = array_values($key_id_data);
        $need_delete = $existing_user_license;
        $i = 0;
        if (count($need_delete) > 0) {
          foreach ($need_delete as $old_key => $old_value) {
            $num_updated = db_update('license_assign') // Table name no longer needs {}
                        ->fields(array(
                          'deactivate_date' => time(),
                          'is_active' => 0,
                          'assign_by' => $user_id,
                        ))
                        ->condition('assign_to', $old_value, '=')
                        ->execute();
            $account = user_load($old_value); // Loading account
            $edit = array(
              'field_licensed' => array(
                'und' => array(
                  0 => array(
                    'value' => 0,
                  ),
                ),
              ),
            );
            user_save($account, $edit);
          }
        }
        if (count($new_user) > 0) {
          foreach ($new_user as $key => $value) {
            $store_datas = db_insert('license_assign')
                      ->fields(array('assign_by', 'assign_to', 'key_id', 'assign_date', 'cid'))
                      ->values(array(
                        'assign_by' => $user_id,
                        'assign_to' => $value,
                        'key_id' => $new_key_id_data[$i],
                        'assign_date' => time(),
                        'cid' => $company_nid
                      ))
                      ->execute();
            $i++;
            $account = user_load($value); // Loading account
            $edit = array(
              'field_licensed' => array(
                'und' => array(
                  0 => array(
                    'value' => 1,
                  ),
                ),
              ),
            );
            user_save($account, $edit);
          }
        }
        $output['success'] = TRUE;
        $output['message'] = t('Data updated successfully.');
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('Selected uids can\'t be null.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 *  function to send admin list by company nid
 */
function user_management_get_company_admin_list(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $adminData = array();$i=0;
    $data = _get_company_admin_list($company_id, 1);
    foreach ($data as $key => $value) {
      $adminData[$i]['uid'] = $key;
      $adminData[$i]['name'] = $value;
      $i++;
    }
    $output['success'] = TRUE;
    $output['message'] = t('Record found.');
    $output['data'] = $adminData;
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for remove user from company in user management
 */
function user_management_remove_user(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['removed_user_id']) && !empty($_REQUEST['removed_user_id'])){
      $removed_user_id = $_REQUEST['removed_user_id'];
      $assign_id = '';
      if(isset($_REQUEST['assign_id']) && !empty($_REQUEST['assign_id'])){
        $assign_id = $_REQUEST['assign_id'];
      }
      $status = m6connect_misc_invite_user_remove('remove', $removed_user_id, $company_id, $assign_id, 'app');
      if(!empty($status)){
        $output['success'] = TRUE;
        $output['message'] = t('User removed successfully.');
        $output['data'] = 1;
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('User id for remove can\'t be null.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for block user from company in user management
 */
function user_management_block_unblock_user(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['blocked_user_id']) && !empty($_REQUEST['blocked_user_id'])){
      $blockedUserId = $_REQUEST['blocked_user_id'];
      if(isset($_REQUEST['og_membership_id']) && !empty($_REQUEST['og_membership_id'])){
        $memberShipId = $_REQUEST['og_membership_id'];
        if(isset($_REQUEST['status']) && !empty($_REQUEST['status'])){
          $status = $_REQUEST['status'];
          $og_roles = og_get_user_roles('node', $company_id, $blockedUserId);
          if($status == 'block'){
            foreach (array_keys($og_roles) as $rid) {
              og_role_revoke('node', $company_id, $blockedUserId, $rid);
            }
          }
          else{
            foreach (array_keys($og_roles) as $rid) {
              og_role_grant('node', $company_id, $blockedUserId, $rid);
            }
          }
          $output['success'] = TRUE;
          $output['message'] = t('The membership has been updated.');
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = t('Membership state can\'t be null.');
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = t('Membership id can\'t be null.');
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = t('User id for update membership can\'t be null.');
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for accept request in user management pending request
 */
function user_management_accept_request(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['accepty_user_id']) && !empty($_REQUEST['accepty_user_id'])){
      $accepty_user_id = $_REQUEST['accepty_user_id'];
      $invite = m6connect_misc_invite('accept', $accepty_user_id, $company_id, 1);
      if(!empty($invite)){
        $output['success'] = TRUE;
        $output['message'] = t('Accepted.');
        $output['data'] = $invite;
      }
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
/**
 * function for deny request in user management pending request
 */
function user_management_deny_request(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['deny_user_id']) && !empty($_REQUEST['deny_user_id'])){
      $deny_user_id = $_REQUEST['deny_user_id'];
      $deny = m6connect_misc_invite('deny', $deny_user_id, $company_id, 1);
      if(!empty($deny)){
        $output['success'] = TRUE;
        $output['message'] = t('Denied.');
        $output['data'] = 1;
      }
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = t('Company nid can\'t be null.');
  }
  drupal_json_output($output);
  drupal_exit();
}
?>