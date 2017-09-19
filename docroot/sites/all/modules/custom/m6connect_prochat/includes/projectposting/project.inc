<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';

/*
 * send default data on project creation page
 */
function create_project_data()
{
  global $user;
  $uid = $user->uid;
  module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
  $output['available_for_free'] = available_for_free_post_award_list();
  $bidkey = _generate_m6connect_confidential_key('project',$uid,$length=7);
  $output['bidkey'] = $bidkey;
  $output['field_status'] = get_status_field_list();  
  $output['field_project_type'] = get_project_type_field_list();  
  $states = addressfield_get_administrative_areas('US');
  $stateData = array();$i = 0;
  foreach ($states as $key => $value) {
    $stateData[$i]['id'] = $key;
    $stateData[$i]['value'] = $value;
    $i++;
  }
  $output['states'] = $stateData;
  $region = taxonomy_vocabulary_machine_name_load('Region');
  $regionTerm = taxonomy_get_tree($region->vid, 0, 1, 1);
  $regionTermData = array();
  if(!empty($regionTerm)){
    $j = 0;
    foreach ($regionTerm as $regionData) {
      $regionTermData[$j]['id'] = $regionData->tid;
      $regionTermData[$j]['value'] = $regionData->name;
      $j++;
    }
  }  
  $output['region'] = $regionTermData;
  $getDiversityNode = getNodeTitleNidFromType('diversity');
  $divNode = array();$k = 0;
  foreach ($getDiversityNode as $key => $value) {
    $divNode[$k]['nid'] = $key;
    $divNode[$k]['title'] = $value;
    $k++;
  }
  $output['diversitynode'] = $divNode;
  $output['success'] = TRUE;
  drupal_json_output($output);
  drupal_exit();
}
/*
 * get level wise region data
 */
function get_region_data_level(){
  if(isset($_REQUEST['region_id']) && !empty($_REQUEST['region_id'])){
    $regionId = $_REQUEST['region_id'];
    $region = taxonomy_vocabulary_machine_name_load('Region');
    $regionTerm = taxonomy_get_tree($region->vid, $regionId, 1, 1);
    $regionTermData = array();
    if(!empty($regionTerm)){
      $j = 0;
      foreach ($regionTerm as $regionData) {
        $regionTermData[$j]['id'] = $regionData->tid;
        $regionTermData[$j]['value'] = $regionData->name;
        $j++;
      }
      $output['success'] = TRUE;
      $output['region'] = $regionTermData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "Data not found";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Region id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  function for save new project
 */
function save_create_project_data(){
  if(isset($_REQUEST['project_data']) && !empty($_REQUEST['project_data'])){
    $projectdata = json_decode($_REQUEST['project_data']);    
  }
  else{
    $output['success'] = FALSE;
    $output['message '] = 'Please provide project data';
  }    
  if(!empty($projectdata)){    
    $node = new StdClass();
    $node->title = $projectdata->title;
    $node->type = 'project';
    $node->uid = $_REQUEST['user_id'];    
    $node->og_group_ref['und'][0]['target_id'] = $projectdata->companyNid;
    $node->field_available_for_free_proj['und'][0]['value'] = $projectdata->field_available_for_free_proj;
    $node->field_project_public['und'][0]['value'] = $projectdata->field_project_public;
    $node->field_create_confidential_bid['und'][0]['value'] = $projectdata->field_create_confidential_bid;
    //$node->title = $projectdata['title'];    
    $node->field_status['und'][0]['value'] = $projectdata->field_status;
    $node->field_complete_description['und'][0]['value'] = $projectdata->field_complete_description;
    $node->field_projects_keywords['und'][0]['value'] = $projectdata->field_projects_keywords;
    $node->field_project_type['und'][0]['value'] = $projectdata->field_project_type;
    $node->field_project_machine_name['und'][0]['value'] = $projectdata->field_project_machine_name;
    $addressData = $projectdata->field_project_address_new[0];
    $node->field_project_address_new['und'][0]['country'] = 'US';
    $node->field_project_address_new['und'][0]['thoroughfare'] = $addressData->field_project_address_new_thoroughfare;
    $node->field_project_address_new['und'][0]['premise'] = $addressData->field_project_address_new_premise;
    $node->field_project_address_new['und'][0]['locality'] = $addressData->field_project_address_new_locality;
    $node->field_project_address_new['und'][0]['administrative_area'] = $addressData->field_project_address_new_administrative_area;
    $node->field_project_address_new['und'][0]['postal_code'] = $addressData->field_project_address_new_postal_code;
    $regionData = $projectdata->field_project_address[0];
    $node->field_project_address['und'][0]['tid'] = $regionData->region2;
    $biddingInfo = $projectdata->field_pro_bidding_info;
    foreach ($biddingInfo as $key => $infovalue) {
      $fc_item = entity_create('field_collection_item', array('field_name' => 'field_pro_bidding_info'));                    
      $fc_item->setHostEntity('node', $node);
      $fc_item->field_proj_bid_name['und'][0]['value'] = $infovalue->field_proj_bid_name;
      $fc_item->field_proj_rpf_issue_date['und'][0]['value'] = $infovalue->field_proj_rpf_issue_date.' '.$infovalue->field_proj_rpf_issue_time;        
      $fc_item->field_proj_bid_date['und'][0]['value'] = $infovalue->field_proj_bid_date.' '.$infovalue->field_proj_bid_time;        
      $fc_item->field_proj_start_date['und'][0]['value'] = $infovalue->field_proj_start_date.' '.$infovalue->field_proj_start_time;        
      $fc_item->field_proj_complete_date['und'][0]['value'] = $infovalue->field_proj_complete_date.' '.$infovalue->field_proj_complete_time;        
      $fc_item->save();
      $itemId = $fc_item->item_id;
      $node->field_pro_bidding_info['und'][$key]['value'] = $itemId;
    }
    if(!empty($_FILES)){
      if(isset($_FILES['field_images']) && !empty($_FILES['field_images'])){
        $array = array();
        $array['name']['upload'] = $_FILES['field_images']['name'];
        $array['type']['upload'] = $_FILES['field_images']['type'];
        $array['tmp_name']['upload'] = $_FILES['field_images']['tmp_name'];
        $array['error']['upload'] = $_FILES['field_images']['error'];
        $array['size']['upload'] = $_FILES['field_images']['size'];
        $_FILES['files'] = $array;
        $file = file_save_upload('upload', array('file_validate_extensions' => array('png gif jpg jpeg')), 'public://');
        // Loading file again, and making it permanent.
        if ($file) {
          $file->status = 1;
          $file_new_save = file_save($file);
          $node->field_images['und'][0] = (array)$file_new_save;          
        }
      }
      /*if(isset($_FILES['field_project_cover_image']) && !empty($_FILES['field_project_cover_image'])){      
      }*/
      if(!empty($projectdata['saveaction'])){
        if($projectdata['saveaction'] == 'draft'){
          $node->status = 0;
        }
      }
    }
    try{
      node_save($node);
      $nid = $node->nid;
      // insert project bid key
      //db_insert('m6connect_confidential_bids_keys')->fields(array('entity_id'=>$nid,'confid_value'=>$projectdata['bid_key']))->execute();      
      $output['success'] = TRUE;
      $output['nid'] = $nid;             
    }
    catch(Exception $e){
      $output['success'] = FALSE;
      $output['message '] = $e;
    }      
  }
  else{
    $output['success'] = FALSE;
    $output['message '] = 'Project data can\'t be null';
  }  
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for sent saved project data
 */
function send_project_posting_data(){
  global $base_url, $bucket, $awsAccessKey, $awsSecretKey;
  if(isset($_REQUEST['company_id']) && !empty($_REQUEST['company_id'])){    
    $user_id = $_REQUEST['user_id'];
    $company = node_load($_REQUEST['company_id']);
    $user = user_load($_REQUEST['user_id']);
    $CuurCompNid = $_REQUEST['company_id'];
    $companyAdminRoleUsers = _get_company_users_by_og_roles($CuurCompNid,'company admin');
    $isCompanyIndividual = is_company_individual_flag($CuurCompNid);    
    $pro_search = isset($_REQUEST ['pro_search']) ? $_REQUEST ['pro_search'] : '';
    $pro_sort = isset($_REQUEST ['pro_sort']) ? $_REQUEST ['pro_sort'] : '';
    $pro_diversity = isset($_REQUEST ['pro_diversity']) ? $_REQUEST ['pro_diversity'] : '';
    $pro_div_arr = array(0);
    if (!empty($pro_diversity)) {
      $pro_div_arr = explode(',', $pro_diversity);
    }
    $pro_div_arr = array_filter($pro_div_arr);
    $pro_region = isset($_REQUEST ['pro_region']) ? $_REQUEST ['pro_region'] : '';
    if(isset($_REQUEST['pro_data'])){
      $public = $interested = $myinterested = $draft = $collaboration =  '';
      if($_REQUEST['pro_data'] == 'myproject'){
        $myproject = 'myproject'  ;
      }
      if($_REQUEST['pro_data'] == 'public'){
        $public = 'public'  ;
      }
      if($_REQUEST['pro_data'] == 'interested'){
        $interested = 'interested'  ;
      }
      if($_REQUEST['pro_data'] == 'myinterested'){
        $myinterested = 'myinterested'  ;
      }
      if($_REQUEST['pro_data'] == 'draft'){
        $draft = 'draft'  ;
      }
      if($_REQUEST['pro_data'] == 'collaboration'){
        $collaboration = 'collaboration'  ;
      }     
    }    
    $type = array('project');
    $counter = 0;
    $or = db_or();
    $and = db_and();
    $query = db_select('node', 'n')->extend('PagerDefault');  
    $query->fields('n', array('nid'));
    $query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
    if ($myproject) {
      if(in_array($user_id,$companyAdminRoleUsers)){
        $company_emails_users = db_select('m6connect_og_membership_email', 'om')->fields('om', array('user_uid','company_email'))->condition('om.entity_id', $CuurCompNid, '=')->execute()->fetchAllKeyed(0,1);        
        $company_email = array_map('strtolower',array_values($company_emails_users));
        $company_user = array_keys($company_emails_users);
        $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
        $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
        $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
          //Invited Company Access
        $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
        $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
        $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
        $query->where('((n.uid IN(:UserUid) and ogm.gid=:ogmid) or (n.status=1 AND (rcne.field_rfp_company_nid_email_value IS NOT NULL) AND ((rcne.field_rfp_company_nid_email_value=:companyNid) or(LOWER(rcne.field_rfp_company_nid_email_value) IN(:companyMail)))))', array(':UserUid' => $company_user, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
      }else{
        $company_email = db_select('m6connect_og_membership_email', 'om')->fields('om', array('company_email'))->condition('om.entity_id', $CuurCompNid, '=')->condition('om.user_uid', $user_id, '=')->execute()->fetchColumn(0);        
        $company_email = (!empty($company_email)) ? $company_email : '';
        $company_email = strtolower($company_email);
        $company_users = _get_company_users_by_group_company($company);
        $userCmpNid = _get_user_company_nid();
        $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
        $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
        $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
        //Invited Company Access
        $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
        $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
        $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');      
        $query->where('((n.uid=:UserUid AND ogm.gid=:ogmid) OR (n.status=1 AND ((pcne.field_company_nid_mail_value=:companyNid OR pcne.field_company_nid_mail_value=:companyMail) AND ((pcimu.field_comapny_manager_value IS NULL) OR FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0))  OR ((rcne.field_rfp_company_nid_email_value=:companyNid) AND FIND_IN_SET(:UserUid,rcimu.field_co_invite_manager_uid_value)>0) OR ((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail) OR ((pcne.field_company_nid_mail_value=:companyNid) AND FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0)))', array(':UserUid' => $user_id, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
      }
    }
    else if ($public) {
      $query->leftJoin('field_data_field_project_public', 'pp', 'pp.entity_id=n.nid');
      $query->where('((n.status=1 AND (pp.field_project_public_value=1)))');
    }
    else if ($interested) {
      $query->leftJoin('m6connect_flagging', 'mfl', 'mfl.node_id = n.nid');      
      $query->condition('mfl.company_id', $CuurCompNid);
      $query->condition('mfl.uid', $user_id);
    }
    else if ($myinterested) {
      $company_users = _get_current_company_users($user_id);      
      $query->Join('flagging', 'fl', 'fl.entity_id = n.nid');      
      $query->where('(ogm.gid=:ogmid)', array(':ogmid' => $CuurCompNid));
      $query->condition('n.uid', $company_users, 'IN');
    }
    else if ($collaboration) {
      $userCmpNid = $CuurCompNid;
      $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
      $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
      $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');      
      $query->where('((pcimu.field_comapny_manager_value IS NOT NULL) AND (pcne.field_company_nid_mail_value=:companyNid) AND (FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0))', array(':UserUid' => $user_id, ':companyNid' => $userCmpNid));
    }
    else {
      if (!empty($pro_search)) {
        $query->leftJoin('field_data_field_public_description', 'pd', 'pd.entity_id = n.nid');
        $query->leftJoin('field_data_field_complete_description', 'cd', 'cd.entity_id = n.nid');
        $query->leftJoin('field_data_field_projects_keywords', 'pk', 'pk.entity_id = n.nid');
        $query->fields('pd');
        $query->fields('cd');
        $query->fields('pk');
        $query->condition(db_or()->condition('title', '%' . db_like($pro_search) . '%', 'LIKE')
          ->condition('cd.field_complete_description_value', '%' . db_like($pro_search) . '%', 'LIKE')
          ->condition('pk.field_projects_keywords_value', '%' . db_like($pro_search) . '%', 'LIKE')
        );      
      }      
      if (!empty($pro_sort)) {
        if($pro_sort == 'date_desc'){      
          $query->leftJoin('field_data_field_pro_bidding_info', 'sbi', 'sbi.entity_id = n.nid');  
          $query->leftJoin('field_data_field_proj_bid_date', 'sbd', 'sbd.entity_id =sbi.field_pro_bidding_info_value');
          $query->orderBy('sbd.field_proj_bid_date_value','DESC');
        }
        if($pro_sort == 'date_asc'){
          $query->leftJoin('field_data_field_pro_bidding_info', 'sbi', 'sbi.entity_id = n.nid');  
          $query->leftJoin('field_data_field_proj_bid_date', 'sbd', 'sbd.entity_id =sbi.field_pro_bidding_info_value');   
          $query->orderBy('sbd.field_proj_bid_date_value','ASC');
        }     
        if($pro_sort == 'name_asc'){    
          $query->fields('n', array('title'));
          $query->orderBy('n.title','ASC');
        }
        if($pro_sort == 'name_desc'){   
          $query->fields('n', array('title'));
          $query->orderBy('n.title','DESC');
        } 
      }
      if ($pro_div_arr) { 
        $query->Join('field_data_field_project_diversity_type', 'dt', 'dt.entity_id = n.nid');
        $query->fields('dt');
        $query->condition('dt.field_project_diversity_type_target_id', $pro_div_arr, 'IN');
      }
      if (!empty($pro_region)) {
        $query->Join('field_data_field_project_address', 'pa', 'pa.entity_id = n.nid');
        $query->fields('pa');
        $pro_region_tids = taxonomy_get_children_all($pro_region);
        $rctids = array();
        if (!empty($pro_region_tids)) {
            $rctids[] = $pro_region;
            foreach ($pro_region_tids as $rk => $rv) {
                $rctids[] = $rv->tid;
            }
        } else {
            $rctids[] = $pro_region;
        }
        $query->condition('pa.field_project_address_tid', $rctids, 'IN');
      }
    }
    if ($draft) {
      $query->condition('n.status', 0, '=');
      $query->condition('n.uid', $user_id, '=');    
    }
    else{
      $query->condition('n.status', 1, '=');
    }
    /*if (!$myproject && !$draft && !$collaboration && !$public && !$myinterested && !(isset($user->roles[3]))) {
      $query->leftJoin('field_data_field_project_public', 'pp', 'pp.entity_id=n.nid');
      //Invited Company Access
      $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
      $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
      $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
      //Collabarated Access
      $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
      $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
      $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');    
      if ($isCompanyIndividual) {
        $query->where('(n.uid=:UserUid and ogm.gid=:ogmid) or (pp.field_project_public_value=1 and n.status=1) or
        (n.status=1 and (LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail)) or
        (pcne.field_company_nid_mail_value=:companyMail)', array(':UserUid' => $user->uid, ':ogmid' => $CuurCompNid, ':companyMail' => strtolower($user->mail)));
      } 
      else {
        // if company admin
        if(in_array($user->uid,$companyAdminRoleUsers)){        
          $company_emails_users = db_select('m6connect_og_membership_email', 'om')->fields('om', array('user_uid','company_email'))->condition('om.entity_id', $CuurCompNid, '=')->execute()->fetchAllKeyed(0,1);
          $company_email = array_map('strtolower',array_values($company_emails_users));
          $company_user = array_keys($company_emails_users);
          $query->where('((n.uid IN(:UserUid) and ogm.gid=:ogmid) or (n.status=1 AND (pp.field_project_public_value=1) or ((rcne.field_rfp_company_nid_email_value=:companyNid)) or((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND (LOWER(rcne.field_rfp_company_nid_email_value) IN(:companyMail)))))', array(':UserUid' => $company_user, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
        }
        else{
          $company_email = db_select('m6connect_og_membership_email', 'om')->fields('om', array('company_email'))->condition('om.entity_id', $company->nid, '=')->condition('om.user_uid', $user->uid, '=')->execute()->fetchColumn(0);
          $company_email = (!empty($company_email)) ? $company_email : '';
          $company_email = strtolower($company_email);
          $query->where('((n.uid=:UserUid and ogm.gid=:ogmid) or (n.status=1 AND (pp.field_project_public_value=1) or ((rcne.field_rfp_company_nid_email_value=:companyNid) AND FIND_IN_SET(:UserUid,rcimu.field_co_invite_manager_uid_value)>0) or ((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail) or ((pcne.field_company_nid_mail_value=:companyNid) AND FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0)))', array(':UserUid' => $user->uid, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
        }
      }
    }*/
    $query->condition('n.type', $type, 'IN');
    if (empty($pro_sort)){
      $query->orderBy('n.created', 'DESC');
    }
    $query->groupBy('n.nid');
    //$query->limit(15);
    $result = $query->execute()->fetchAll();
    $output['projectdata'] = $result;
    if(!empty($result)){
      $output = $nodeOutput = $mainData = array();    
      foreach ($result as $key => $nodeValue) {
        $nodeData = db_select('node', 'n');
        $nodeData->leftJoin('field_data_field_images', 'fdfi', 'fdfi.entity_id = n.nid');
        $nodeData->leftjoin ('file_managed', 'fm', 'fm.fid = fdfi.field_images_fid');        
        $nodeData->leftJoin('field_data_field_pro_bidding_info', 'fdfpbi', 'fdfpbi.entity_id = n.nid');
        $nodeData->leftJoin('field_data_field_proj_bid_date', 'fdfpbd', 'fdfpbi.field_pro_bidding_info_value = fdfpbd.entity_id');
        $nodeData->fields("fm", array('uri'));
        $nodeData->fields("fdfpbd", array('field_proj_bid_date_value'));
        $nodeData->fields('n', array('title'));
        $nodeData->condition('n.nid', $nodeValue->nid, '=');
        $nodeDataRes = $nodeData->execute()->fetchAssoc();      
        $thumbnailUrl = '';      
        if(!empty($nodeDataRes['uri'])){          
          $credentials = new Credentials($awsAccessKey, $awsSecretKey);
          $s3Client = S3Client::factory(array(
            'credentials' => $credentials
          ));
          $thumbUrl = str_replace("private:/", "s3fs-private", $nodeDataRes['uri']);
          $thumbnailUrl = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');          
        }      
        $mainData[$key]['thumbnail'] = $thumbnailUrl;
        $mainData[$key]['field_proj_bid_date_value'] = date("F d, Y h:iA T",$nodeDataRes['field_proj_bid_date_value']);
        $mainData[$key]['nid'] = $nodeValue->nid;
        $mainData[$key]['title'] = $nodeDataRes['title'];
        $comprealusername = _get_node_company_user_name($nodeValue->nid);
        $mainData[$key]['company_title'] = $comprealusername['company_title'];
        $mainData[$key]['user_name'] = $comprealusername['user_name'];      
        $mainData[$key]['action']['Open'] = 'nodeOpen/'.$nodeValue->nid;
        $mainData[$key]['action']['Invite Companies'] = 'invite-companies/'.$nodeValue->nid;
        $mainData[$key]['action']['Publish'] = 'nodeShow/'.$nodeValue->nid;
        $mainData[$key]['action']['Delete'] = 'nodedelete/node/'.$nodeValue->nid;
      }
      $output['success'] = TRUE;
      $output['message'] = "Record found";
      $output['projectdata'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "No data found";
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Company id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for send single project draft summary tab data
 */
function send_single_project_draft_summery_tab_data(){
  if(isset($_REQUEST['draftNid']) && !empty($_REQUEST['draftNid'])){
    $draftNid = $_REQUEST['draftNid'];
    if(!empty($draftNid)){
      $getDraftData = db_select('node', 'n');
      $getDraftData->leftJoin('og_membership', 'om', 'om.etid = n.nid');
      $getDraftData->leftJoin('field_data_field_images', 'fdfi', 'fdfi.entity_id = n.nid');
      $getDraftData->leftjoin ('file_managed', 'fm', 'fm.fid = fdfi.field_images_fid');
      $getDraftData->leftJoin('field_data_field_project_cover_image', 'fdfpci', 'fdfpci.entity_id = n.nid');
      $getDraftData->leftjoin ('file_managed', 'fma', 'fma.fid = fdfpci.field_project_cover_image_fid');
      $getDraftData->leftJoin('field_data_field_project_number', 'fdfpn', 'fdfpn.entity_id = n.nid');
      $getDraftData->leftJoin('field_data_field_project_address_new', 'fpan', 'fpan.entity_id = n.nid');
      $getDraftData->leftJoin('field_data_field_complete_description', 'fdfcd', 'fdfcd.entity_id = n.nid');      
      $getDraftData->fields('n', array('nid', 'title'));
      $getDraftData->fields('om', array('gid'));
      $getDraftData->fields("fm", array('uri'));
      $getDraftData->addField("fma", 'uri', 'bannerimage');
      $getDraftData->fields('fdfpn', array('field_project_number_value'));
      $getDraftData->fields('fpan', array('field_project_address_new_thoroughfare', 'field_project_address_new_locality', 'field_project_address_new_administrative_area', '
        field_project_address_new_postal_code'));
      $getDraftData->fields('fdfcd', array('field_complete_description_value'));
      $getDraftData->condition('n.nid', $draftNid, '=');
      $result = $getDraftData->execute()->fetchAll();
      if(!empty($result)){
        foreach ($result as $key => $value) {
          $output['message'] = 'Record found';
          $output['success'] = TRUE;
          $output['project'] = $value->field_project_number_value;
          $output['posted_by'] = _get_title_of_node($value->gid);
          $output['project_address'] = $value->field_project_address_new_thoroughfare.' '.$value->field_project_address_new_locality.' , '.$value->field_project_address_new_administrative_area.' '.$value->field_project_address_new_postal_code;
          $output['status'] = 'Active';
          $desc = '';
          if(!empty($value->field_complete_description_value)){
            $desc = $value->field_complete_description_value;
          }
          $output['description'] = $desc;
          if(!empty($value->field_proj_bid_name_value)){
            $bidName = $value->field_proj_bid_name_value;
          }          
        }                
      }
      // query for bid info data
      $getBidInfoData = db_select('node', 'n');
      $getBidInfoData->leftJoin('field_data_field_pro_bidding_info', 'fdfpbi', 'fdfpbi.entity_id = n.nid');
      $getBidInfoData->fields('fdfpbi', array('field_pro_bidding_info_value'));
      $getBidInfoData->condition('n.nid', $draftNid, '=');
      $result1 = $getBidInfoData->execute()->fetchAll();
      $bidInfoData = '';
      if(!empty($result1)){
        $bidInfoData = array();
        foreach ($result1 as $num => $bidvalue) {
          $a = field_collection_item_load($bidvalue->field_pro_bidding_info_value);
          $bidName = $bidDueDate = $projectStartDate = $projectCompleteDate = $bidRfpDate = '';
          if(!empty($a->field_proj_bid_name['und'][0]['value'])){
            $bidName = $a->field_proj_bid_name['und'][0]['value'];  
          }
          if(!empty($a->field_proj_bid_date['und'][0]['value'])){
            $bidDueDate = $a->field_proj_bid_date['und'][0]['value'];  
          }
          if(!empty($a->field_proj_start_date['und'][0]['value'])){
            $projectStartDate = $a->field_proj_start_date['und'][0]['value'];  
          }
          if(!empty($a->field_proj_complete_date['und'][0]['value'])){
            $projectCompleteDate = $a->field_proj_complete_date['und'][0]['value'];  
          }
          if(!empty($a->field_proj_rpf_issue_date['und'][0]['value'])){
            $bidRfpDate = $a->field_proj_rpf_issue_date['und'][0]['value'];  
          }
          $bidInfoData[$num]['anticipated_bid_name'] = $bidName;
          $bidInfoData[$num]['rfp_issue_date'] = $bidRfpDate;
          $bidInfoData[$num]['bid_due_date'] = $bidDueDate;
          $bidInfoData[$num]['work_start_date'] = $projectStartDate;
          $bidInfoData[$num]['work_completion_date'] = $projectCompleteDate;
        }
      }
      $output['bid_info'] = $bidInfoData;
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = "Draft nid should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for send single project draft diversity tab data
 */
function send_single_project_draft_diversity_tab_data(){
  if(isset($_REQUEST['draftNid']) && !empty($_REQUEST['draftNid'])){
    $draftNid = $_REQUEST['draftNid'];
    if(!empty($draftNid)){
      $getDraftData = db_select('node', 'n');
      $getDraftData->leftjoin('field_data_field_project_diversity_type', 'fdfpdt', 'fdfpdt.entity_id = n.nid');
      $getDraftData->fields('fdfpdt', array('field_project_diversity_type_target_id'));
      $getDraftData->condition('n.nid', $draftNid, '=');
      $result = $getDraftData->execute()->fetchAll();
      $title = '';
      if(!empty($result)){
        $title = array();$i = 0;
        foreach ($result as $key => $value) {
          $titleData = getNodeTitleFromNids($value);
          foreach ($titleData as $nid => $nodeTitle) {
            $title[$key]['id'] = $nid;
            $title[$key]['value'] = $nodeTitle;
          }
          $i++;
        }
        $output['success'] = TRUE;
        $output['message'] = 'Record found';
        $output['diversity'] = $title;
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "Draft nid should not be null";
    }
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for send single project draft interested companies tab data
 */
function send_single_project_draft_interested_companies_tab_data(){
  if(isset($_REQUEST['draftNid']) && !empty($_REQUEST['draftNid'])){
    $draftNid = $_REQUEST['draftNid'];
    if(!empty($draftNid)){
      $user_id = $_REQUEST['user_id'];
      $query = db_select('flagging', 'fl');
      $query->DISTINCT();
      $query->fields('fl', array('uid'));
      $query->condition('fl.entity_id', $draftNid);
      $result = $query->execute();
      while ($record = $result->fetchAssoc()) {
        $userids[] = $record['uid'];
      }
      $countcompany = 0;
      if(!empty($userids)){        
        $output['success'] = TRUE;
        $output['message'] = 'Record found';
        $mainData = array();
        foreach ($userids as $k => $uid) {
          $cuser = user_load($uid);
          $user_groups = og_get_groups_by_user($cuser, 'node');
          foreach ($user_groups as $n => $gnid) {            
            $gnode = node_load($gnid);
            $isCompanyIndividual = is_company_individual_flag($gnid);
            if (!$isCompanyIndividual && $gnode->uid == $uid) {
              $mainData[$countcompany]['id'] = $gnid;
              $mainData[$countcompany]['value'] = $gnode->title;
              break;
            }
            elseif ($isCompanyIndividual && $gnode->uid == $uid) {
              $mainData[$countcompany]['id'] = $gnid;
              $mainData[$countcompany]['value'] = $gnode->title;
            }
          }
          $countcompany++;
        }
        $output['interested_companies'] = $mainData;
      }
      if(empty($countcompany)){
        $output['success'] = FALSE;
        $output['message'] = 'No one has expressed interest in the project.';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "Draft nid should not be null";
    }
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for send single project draft interested bidders tab data
 */
function send_single_project_draft_interested_bidders_tab_data(){
  if(isset($_REQUEST['draftNid']) && !empty($_REQUEST['draftNid'])){
    $draftNid = $_REQUEST['draftNid'];
    if(!empty($draftNid)){
      $user_id = $_REQUEST['user_id'];
      $draftNode = node_load($draftNid);
      $cmpcall = in_array($user_id, _get_current_company_users($draftNode->uid));
      $cmpcall2 = in_array($user_id, loadadinitation_project_user($draftNode->nid));
      if ($draftNode->uid == $user_id || $cmpcall || $cmpcall2) {        
        $items = field_get_items('node', $draftNode, 'field_pro_bidding_info');
        if(!empty($items)){
          $output['success'] = TRUE;
          $output['message'] = 'Record found';
          $mainData = array();
          foreach ($items as $key => $item) {
            $fc = field_collection_field_get_entity($item);
            $itemid = $fc->item_id;
            $mainData[$key]['bid_name'] = (isset($fc->field_proj_bid_name['und'])) ? $fc->field_proj_bid_name['und'][0]['value'] : '';
            $mainData[$key]['bid_date'] = (isset($fc->field_proj_bid_date['und'])) ? date("j F Y", strtotime($fc->field_proj_bid_date['und'][0]['value'])) : '';
            $mainData[$key]['bid_start_date'] = (isset($fc->field_proj_start_date['und'])) ? date("j F Y", strtotime($fc->field_proj_start_date['und'][0]['value'])) : '';
            $mainData[$key]['bid_complete_date'] = (isset($fc->field_proj_complete_date['und'])) ? date("j F Y", strtotime($fc->field_proj_complete_date['und'][0]['value'])) : '';

            $bidCmp = db_select('flagging', 'f')->fields('f', array('uid'))->condition('entity_id', $itemid, '=')->condition('entity_type', 'field_collection_item', '=')->execute()->fetchAll();
            if(!empty($bidCmp)){
              foreach ($bidCmp as $num => $bidCmpValue) {
                $uid = $bidCmpValue->uid;
                $gids = _get_user_company_nid($uid);
                if(!empty($gids)){
                  $mainData[$key]['bidding_companies'] = _get_title_of_node($gids);
                }
              }              
            }
            else{
              $mainData[$key]['bidding_companies'] = '';
            }
          }
          $output['interested_bidders'] = $mainData;
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = 'No data found.';
        }
      }
    }    
    else{
      $output['success'] = FALSE;
      $output['message'] = "Draft nid should not be null";
    }
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for send single project draft rfp tab data
 */
function send_single_project_draft_rfp_tab_data(){
  if(isset($_REQUEST['draftNid']) && !empty($_REQUEST['draftNid'])){
    $draftNid = $_REQUEST['draftNid'];
    if(!empty($draftNid)){
      $user_id = $_REQUEST['user_id'];
      $project = menu_get_object();
      $allowed_uids = m6connect_projects_uids_from_list($project);
      $rfpQuery = db_select('field_data_field_project', 'fp');
      $rfpQuery->leftjoin('node', 'n','n.nid=fp.entity_id');
      $rfpQuery->fields('fp', array('entity_id'));
      $rfpQuery->fields('n', array('title'));
      $rfpQuery->condition('fp.field_project_target_id', $draftNid);
      $rfpQuery->condition('n.status', 1);
      $RFPlinsting = $rfpQuery->execute()->fetchAllKeyed(0,1);
      $mainData = array();
      if($project->uid == $user_id || in_array($user_id,$allowed_uids)){
        if(!empty($RFPlinsting)){
          $i = 0;
          $output['success'] = TRUE;
          $output['message'] = 'Record found';
          foreach($RFPlinsting as $rfpNid => $rfpTitle){
            $mainData[$i]['title'] = $rfpTitle;
            $i++;
          }
          $output['rfp'] = $mainData;
        }else{
         $output['success'] = FALSE;  
         $output['message'] = 'No RFP found';
        }
      }else if(!empty($RFPlinsting)){
        $invited = is_rpf_tab_accessible_in_projects($RFPlinsting);
        $output['success'] = TRUE;
        $output['message'] = 'Record found';$i = 0;
        foreach($RFPlinsting as $rfpNid => $rfpTitle){
          if(in_array($rfpNid,$invited)){
            $mainData[$i]['title'] = $rfpTitle;
            $i++;  
          }
        }
        $output['rfp'] = $mainData;
      }else{
        $output['success'] = FALSE;  
        $output['message'] = 'No RFP found';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = "Draft nid should not be null";
    }
  }
  drupal_json_output($output);
  drupal_exit();
}






/*
 *  Common function
 */
function available_for_free_post_award_list(){  
  $data = db_select("field_config", "fc")
        ->fields("fc", array("data"))
        ->condition("field_name", "field_available_for_free_proj", "=")
        ->execute()->fetchField();
  $available = unserialize($data);
  $availableData = array();
  foreach ($available['settings']['allowed_values'] as $key => $value) {
    $availableData[$key]['id'] = $key;
    $availableData[$key]['value'] = $value;
  }
  return $availableData;
}
function get_status_field_list(){  
  $data = db_select("field_config", "fc")
        ->fields("fc", array("data"))
        ->condition("field_name", "field_status", "=")
        ->execute()->fetchField();
  $statusList = unserialize($data);
  $statusListData = array();$i = 0;
  foreach ($statusList['settings']['allowed_values'] as $key => $value) {
    $statusListData[$i]['id'] = $key;
    $statusListData[$i]['value'] = $value;
    $i++;
  }
  return $statusListData;
}
function get_project_type_field_list(){  
  $data = db_select("field_config", "fc")
        ->fields("fc", array("data"))
        ->condition("field_name", "field_project_type", "=")
        ->execute()->fetchField();  
  $projectList = unserialize($data);
  $projectListData = array();$i = 0;
  foreach ($projectList['settings']['allowed_values'] as $key => $value) {
    $projectListData[$i]['id'] = $key;
    $projectListData[$i]['value'] = $value;
    $i++;
  }
  return $projectListData;
}

function getRegionTopParent($tid = 0, $regionTopTid = array()){
  if(!empty($tid)){
    $regionTopTid[] = $tid;
    $getr = db_select('taxonomy_term_hierarchy', 'tth')
          ->fields('tth', array('parent'))
          ->condition('tid', $tid, '=')
          ->execute()->fetchAssoc();
    if(!empty($getr['parent'])){
      $regionTopTid = getRegionTopParent($getr['parent'], $regionTopTid);      
    }
  }
  return $regionTopTid;
}
function m6connect_prochat_get_user_one_company($uid, $nid, $type = 'organization', $access = 0) {
  $output = array();
  if(!empty($uid) && !empty($nid)){    
    $currUser = user_load($uid);
    $user_groups = og_get_groups_by_user($currUser, 'node');
    $query = db_select('node', 'n');
    $query->fields('n', array('title'));
    $query->fields('n', array('nid'));
    $query->fields('tc', array('field_type_of_company_value'));
    $query->fields('ml', array('field_main_location_grp_target_id'));
    $query->fields('ga', array('group_access_value'));
    $query->leftJoin('field_data_field_type_of_company', 'tc', 'tc.entity_id = n.nid');
    $query->leftJoin('field_data_field_main_location_grp', 'ml', 'ml.entity_id = n.nid');
    $query->leftJoin('field_data_group_access', 'ga', "ga.entity_id = n.nid and ga.bundle='groups'");
    if (count($user_groups) > 0) {
      $query->condition('n.nid', $user_groups, 'in');
    }
    $query->condition('n.type', $type, '=');
    $query->condition('n.nid', $nid, '=');  
    $result = $query->execute()->fetchAll();
    if(!empty($result)){
      $output['success'] = TRUE;
      $output['data'] = $result;
    }
    else{
      $output['success'] = FALSE;
      $output['data'] = 'You are not member of this company';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['data'] = 'User id or Company id should not be empaty';
  }
  return $output;
}

?>