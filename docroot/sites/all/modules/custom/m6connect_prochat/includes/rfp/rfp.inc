<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';

/*
 * send default data on rfp creation page
 */
function create_rfp_data() {
  global $user;
  $uid = $user->uid;
  $bidkey = _generate_m6connect_confidential_key('project',$uid,$length=7);
  $output['bidkey'] = $bidkey;
  $output['field_rfp_types'] = field_info_field('field_rfp_types')['settings']['allowed_values'];
  $output['field_project_manager'] = get_Project_ManagerBYGid($gid);
  $output['field_project'] = get_allProjectsByUID($UID);
  $output['field_rfp_document_type'] = field_info_field('field_rfp_document_type')['settings']['allowed_values'];  
  $output['region'] = getvocparentTermData('Region');
  $output['m6_company_types'] = getvocparentTermData('facilities_construction');
  $output['industry_naics'] = getvocparentTermData('industry_naics_1');
  $output['products_services_unspsc'] = getvocparentTermData('products_services_unspsc');
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
 *  function for save new RFP
 */
function save_create_rfp_data(){
  if(isset($_REQUEST['rfp_data']) && !empty($_REQUEST['rfp_data'])){
    $rfpdata = json_decode($_REQUEST['rfp_data']);    
  }  else{
    $output['success'] = FALSE;
    $output['message '] = 'Please provide project data';
  }    
  if(!empty($rfpdata)){    
    $node = new StdClass();
    $node->title = $rfpdata->title;
    $node->type = 'rfp';
    $node->uid = $_REQUEST['user_id'];    
    $node->og_group_ref['und'][0]['target_id'] = $projectdata->companyNid;
    $node->field_rfp_types = $rfpdata->rfptype;
    $node->field_public['und'][0]['value'] = $rfpdata->field_available_for_free_proj;
    $node->field_create_confidential_bid['und'][0]['value'] = $rfpdata->field_create_confidential_bid;
    $node->field_project_manager = $rfpdata->project_manager;
    $node->field_estimated_cost = $rfpdata->estimated_cost;
    $node->field_rfp_description = $rfpdata->rfp_description;
    $node->field_project = $rfpdata->field_project;
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
          $node->field_rfp_logo['und'][0] = (array)$file_new_save;          
        }
      }
    }
    if(!empty($rfpdata['saveaction'])){
      if($rfpdata['saveaction'] == 'draft'){
        $node->status = 0;
      }
    } try {
      node_save($node);
      $nid = $node->nid;     
      $output['success'] = TRUE;
      $output['nid'] = $nid;             
    }
    catch(Exception $e){
      $output['success'] = FALSE;
      $output['message '] = $e;
    }      
  } else {
    $output['success'] = FALSE;
    $output['message '] = 'RFP data can\'t be null';
  }  
  drupal_json_output($output);
  drupal_exit();
}



/*
 *  function for all RFP's by requested company
 */
function send_allrft_data(){
  global $base_url, $bucket, $awsAccessKey, $awsSecretKey;
  if(isset($_REQUEST['company_id']) && !empty($_REQUEST['company_id'])){
    if(isset($_REQUEST['ACTION']) && !empty($_REQUEST['ACTION'])) {
      if($_REQUEST['ACTION'] == 'public') {
        $result = get_publicrfpbyGID($_REQUEST['company_id'], $_REQUEST['user_id']);
      } elseif($_REQUEST['ACTION'] == 'draft'){
        $result = get_DraftrfpbyGID($_REQUEST['company_id'], $_REQUEST['user_id']);
      } elseif($_REQUEST['ACTION'] == 'expired'){
        $result = get_expiredrfpbyGID($_REQUEST['company_id'], $_REQUEST['user_id']);
      } else {
        $result = get_allrfpbyGID($_REQUEST['company_id'], $_REQUEST['user_id'],$_REQUEST['ACTION']);  
      }
    } else {
      $output['success'] = FALSE;
      $output['message'] = "Please select data selector";
    }
    if(!empty($result)){ 
      $output['success'] = TRUE;
      $output['message'] = "Record found";
      $output['rfpDATA'] = $result;
    } else{
      $output['success'] = FALSE;
      $output['message'] = "No data found";
    }
  } else{
    $output['success'] = FALSE;
    $output['message'] = "Company id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

/*
 *  function for Single RFP data
 */
function send_single_rft_data() {
  global $base_url, $bucket, $awsAccessKey, $awsSecretKey;
  if(isset($_REQUEST['rfp_id']) && !empty($_REQUEST['rfp_id'])){
    $rfpnode = node_load($_REQUEST['rfp_id']);
    $outputrfp['nid'] = $rfpnode->nid;
    $outputrfp['created'] = $rfpnode->created;
    $outputrfp['updated'] = $rfpnode->changed;
    $outputrfp['summary_information'] = get_rfp_singleSummary_information($rfpnode);  
    $outputrfp['timeline'] = get_rfp_singleTimeline($rfpnode);
    $outputrfp['documents'] = get_rfp_singledocument($rfpnode);
    $outputrfp['bid_packages'] = get_rfp_singlebid_packages($_REQUEST['rfp_id']);
    $outputrfp['Proposals'] = get_rfp_singleProposal_data($_REQUEST['rfp_id']);
    $outputrfp['BidderFeedback'] = get_rfp_singleBidderFeedback($_REQUEST['rfp_id']);
    $outputrfp['InviteCompanies'] = getinvite_rfp($rfpnode);
    if(!empty($outputrfp)){ 
      $output['success'] = TRUE;
      $output['message'] = "Record found";
      $output['rfpsingleDATA'] = $outputrfp;
    } else {
      $output['success'] = FALSE;
      $output['message'] = "No data found";
    }
  } else {
    $output['success'] = FALSE;
    $output['message'] = "Company id should not be null";
  }
  drupal_json_output($output);
  drupal_exit();
}

/*
 * Common function for get data
 */

function get_Project_ManagerBYGid($gid) {
  $gePmanager = db_query("SELECT users.name AS users_name, users.uid AS uid, og_membership_users.created AS og_membership_users_created
  FROM 
  {users} users
  INNER JOIN {og_membership} og_membership_users ON users.uid = og_membership_users.etid AND og_membership_users.entity_type = 'user'
  WHERE (( (og_membership_users.gid = '".$gid."' ) )AND(( (users.status <> '0') AND (og_membership_users.state IN  ('1')) )))
  ORDER BY og_membership_users_created DESC
  ")->fetchAll();  
  return $gePmanager;
}


function get_allProjectsByUID($UID) {
  $i=0;
  foreach(og_get_groups_by_user(user_load($UID))['node'] as $value){
   $arr[$i] = $value;
   $i++;
  }
  $getallproject = db_query("SELECT node_og_membership.title AS node_og_membership_title, node_og_membership.nid AS node_og_membership_nid, node.title AS node_title, node.nid AS nid, node.created AS node_created
  FROM 
  {node} node
  LEFT JOIN {og_membership} og_membership_node ON node.nid = og_membership_node.etid AND og_membership_node.entity_type = 'node'
  LEFT JOIN {node} node_og_membership ON og_membership_node.gid = node_og_membership.nid AND og_membership_node.group_type = 'node'
  WHERE (( (og_membership_node.gid IN(".implode(',',$arr).") ) )AND(( (node.status = '1') AND (og_membership_node.state IN  ('1')) AND (og_membership_node.group_type IN  ('node')) AND (node.type IN  ('project')) ))) ORDER BY node_created DESC, node_title ASC")->fetchAll();
  foreach($getallproject as $key => $valmem){
    $getallprojectlist[$valmem->nid] = $valmem->node_title;
  }
  return $getallprojectlist;
}

function getRFPdataFilterfields($node,$key,$row) {
  global $bucket, $awsAccessKey, $awsSecretKey;
  $getall = $row;
  $getall->due = date("h:iA T",strtotime($node->field_due['und'][0]['value']));
  $getall->rfp_description = $node->field_rfp_description['und'][0]['value'];
  $getall->rfp_logo['fid'] = $node->field_rfp_logo['und'][0]['fid'];   
  $getall->rfp_logo['uri'] = $node->field_rfp_logo['und'][0]['uri'];
  if($node->field_rfp_logo['und'][0]['uri']) {
    $credentials = new Credentials($awsAccessKey, $awsSecretKey);
    $s3Client = S3Client::factory(array(
      'credentials' => $credentials
    ));
    $thumbUrl = str_replace("private:/", "s3fs-private", $node->field_rfp_logo['und'][0]['uri']);
    $thumbnailUrl = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
    $getall->rfp_logo['url'] = $thumbnailUrl; 
  }
  return $getall; 
}

function get_allrfpbyGID($GID, $uid, $action) {
  global $base_url;
  $arr = db_query("SELECT node.nid AS nid, node.title AS node_title, node.uid AS node_uid, node.created AS node_created, 'node' AS field_data_field_reference_number_node_entity_type, 'node' AS field_data_field_due_node_entity_type, 'node' AS field_data_field_rfp_description_node_entity_type, 'node' AS field_data_field_rfp_logo_node_entity_type
    FROM 
    {node} node
    LEFT JOIN {field_data_field_cm_type} field_data_field_cm_type ON node.nid = field_data_field_cm_type.entity_id AND (field_data_field_cm_type.entity_type = 'node' AND field_data_field_cm_type.deleted = '0')
    WHERE (( (node.type IN  ('rfp')) AND (node.status = '1') AND (field_data_field_cm_type.field_cm_type_value IS NULL ) ))")->fetchAll();
    $company = node_load($GID);
    $user = user_load($uid);
    foreach($arr as $key => $row){
      $row->node_created = date("F d, Y h:iA T",$row->node_created);
      $node = node_load($row->nid);
      if($action == 'all') {
        $nodeBelongToCurrentCompany = (is_numeric($company->nid) && $company->nid == _get_company_nid_by_group_content($node));
        $cmpcall = in_array($user->uid,_get_company_users_by_group_content($node)) ;
        $cmpcall2 = in_array($user->uid, m6connect_projects_uids_from_list($node));
        if((($nodeBelongToCurrentCompany && $cmpcall) || $cmpcall2) && (!(is_rfp_expired($row->nid)))){
          $getall[$key] = getRFPdataFilterfields($node,$key,$row);    
        }
        if((is_rfp_invited_company($row->nid,'rfp',TRUE)) && !(is_rfp_expired($row->nid))){
          $getall[$key] = getRFPdataFilterfields($node,$key,$row);
        }
      } elseif($action == 'received') {
        if(((is_rfp_invited_company($row->nid,'rfp',TRUE)) && !(is_rfp_expired($row->nid)))) {
           $getall[$key] = getRFPdataFilterfields($node,$key,$row);
        }   
      } elseif($action == 'sent') {
        $nodeBelongToCurrentCompany = (is_numeric($company->nid) && $company->nid == _get_company_nid_by_group_content($node));
        $cmpcall = in_array($user->uid,_get_company_users_by_group_content($node)) ;
        $cmpcall2 = in_array($user->uid, m6connect_projects_uids_from_list($node));
        if((($nodeBelongToCurrentCompany && $cmpcall) || $cmpcall2) && (!(is_rfp_expired($row->nid)))){
            $getall[$key] = getRFPdataFilterfields($node,$key,$row);
        }
      } elseif($action == 'bidding') {
        $is_public = (isset($node->field_public['und']) && $node->field_public['und'][0]['value']==1)?1:0;
        if(($is_public || (is_rfp_invited_company($row->nid,'rfp',TRUE))) && !(is_rfp_expired($row->nid))){
          if((is_rfp_bidding_flag_set($row->nid)!=0)) {
            $getall[$key] = getRFPdataFilterfields($node,$key,$row);
          }
        }
      } 
    }
  foreach($getall as $keyr => $valuerfp){
    $result = _get_node_company_user_name($valuerfp->nid);
    $posted = (!empty($result['company_title']))?$result['company_title'].', '.$result['user_name']:$result['user_name'];
    $valuerfp->PostedBy = $posted;
    //$valuerfp->action1 = create_rfp_biddind_flag_link($valuerfp->nid);
  }
  return $getall;
}


function get_publicrfpbyGID($GID, $uid) {
  global $base_url;
  $arr = db_query("SELECT node.title AS node_title, node.nid AS nid, node.uid AS node_uid, node.created AS node_created, 'node' AS field_data_field_reference_number_node_entity_type, 'node' AS field_data_field_project_node_entity_type, 'node' AS field_data_field_due_node_entity_type, 'node' AS field_data_field_rfp_logo_node_entity_type, 'node' AS field_data_field_rfp_description_node_entity_type
FROM 
{node} node
INNER JOIN {field_data_field_public} field_data_field_public ON node.nid = field_data_field_public.entity_id AND (field_data_field_public.entity_type = 'node' AND field_data_field_public.deleted = '0')
LEFT JOIN {field_data_field_cm_type} field_data_field_cm_type ON node.nid = field_data_field_cm_type.entity_id AND (field_data_field_cm_type.entity_type = 'node' AND field_data_field_cm_type.deleted = '0')
WHERE (( (node.type IN  ('rfp')) AND (field_data_field_public.field_public_value = '1') AND (node.status = '1') AND (field_data_field_cm_type.field_cm_type_value IS NULL ) ))")->fetchAll();
    $company = node_load($GID);
    $user = user_load($uid);
    foreach($arr as $key => $row){
      $row->node_created = date("F d, Y h:iA T",$row->node_created);
      $node = node_load($row->nid);
      if((!(is_rfp_expired($row->nid)))){
        $getall[$key] = getRFPdataFilterfields($node,$key,$row);
      }  
    }
  foreach($getall as $keyr => $valuerfp){
    $result = _get_node_company_user_name($valuerfp->nid);
    $posted = (!empty($result['company_title']))?$result['company_title'].', '.$result['user_name']:$result['user_name'];
    $valuerfp->PostedBy = $posted;
    //$valuerfp->action1 = create_rfp_biddind_flag_link($valuerfp->nid);
  }
  return $getall;
}

function get_DraftrfpbyGID($GID, $uid) {
  global $base_url;
  $arr = db_query("SELECT node.title AS node_title, node.nid AS nid, node.uid AS node_uid, node.created AS node_created, 'node' AS field_data_field_reference_number_node_entity_type, 'node' AS field_data_field_project_node_entity_type, 'node' AS field_data_field_due_node_entity_type, 'node' AS field_data_field_rfp_description_node_entity_type, 'node' AS field_data_field_rfp_logo_node_entity_type
FROM 
{node} node
LEFT JOIN {field_data_field_cm_type} field_data_field_cm_type ON node.nid = field_data_field_cm_type.entity_id AND (field_data_field_cm_type.entity_type = 'node' AND field_data_field_cm_type.deleted = '0')
WHERE (( (node.type IN  ('rfp')) AND (node.status = '0') AND (field_data_field_cm_type.field_cm_type_value IS NULL ) ))")->fetchAll();
    $company = node_load($GID);
    $user = user_load($uid);
    foreach($arr as $key => $row){
      $row->node_created = date("F d, Y h:iA T",$row->node_created);
      $node = node_load($row->nid);
      $nodeCompanyNid = _get_company_nid_by_group_content($node);
      $nodeBelongToCurrentCompany = (is_numeric($company->nid) && ($company->nid ==$nodeCompanyNid));
      if($nodeBelongToCurrentCompany){
        $getall[$key] = getRFPdataFilterfields($node,$key,$row);
      } 
    }
    foreach($getall as $keyr => $valuerfp){
      $result = _get_node_company_user_name($valuerfp->nid);
      $posted = (!empty($result['company_title']))?$result['company_title'].', '.$result['user_name']:$result['user_name'];
      $valuerfp->PostedBy = $posted;
      //$valuerfp->action1 = create_rfp_biddind_flag_link($valuerfp->nid);
    }
    return $getall;
}

function get_expiredrfpbyGID($GID, $uid) {
  global $base_url;
  $arr = db_query("SELECT node.nid AS nid, node.title AS node_title, node.uid AS node_uid, node.created AS node_created, 'node' AS field_data_field_reference_number_node_entity_type, 'node' AS field_data_field_project_node_entity_type, 'node' AS field_data_field_due_node_entity_type, 'node' AS field_data_field_rfp_description_node_entity_type, 'node' AS field_data_field_rfp_logo_node_entity_type
FROM 
{node} node
LEFT JOIN {field_data_field_cm_type} field_data_field_cm_type ON node.nid = field_data_field_cm_type.entity_id AND (field_data_field_cm_type.entity_type = 'node' AND field_data_field_cm_type.deleted = '0')
WHERE (( (node.type IN  ('rfp')) AND (field_data_field_cm_type.field_cm_type_value IS NULL ) ))")->fetchAll();
    $company = node_load($GID);
    $user = user_load($uid);
    foreach($arr as $key => $row){
      $row->node_created = date("F d, Y h:iA T",$row->node_created);
      $node = node_load($row->nid);

      $nodeStatus = $node->status;
      $nodeBelongToCurrentCompany = (is_numeric($company->nid) && $company->nid == _get_company_nid_by_group_content($node));
      $isNodePublic = (isset($node->field_public['und']) && $node->field_public['und'][0]['value']==1)?1:0;
      $isNodeInvited = is_rfp_invited_company($row->nid);
      $nodeCompanyNid = _get_company_nid_by_group_content($node);
      $isNodeCollabarated = in_array($user->uid, m6connect_projects_uids_from_list($node));
      $nodeBelongToCurrentCompany = (is_numeric($company->nid) && ($company->nid ==$nodeCompanyNid));
      if(is_rfp_expired($row->nid) && $nodeStatus){
        if($isNodePublic || $nodeBelongToCurrentCompany || $isNodeInvited || $isNodeCollabarated){
          $getall[$key] = getRFPdataFilterfields($node,$key,$row);   
        }
      }
    }
    foreach($getall as $keyr => $valuerfp){
      $result = _get_node_company_user_name($valuerfp->nid);
      $posted = (!empty($result['company_title']))?$result['company_title'].', '.$result['user_name']:$result['user_name'];
      $valuerfp->PostedBy = $posted;
      //$valuerfp->action1 = create_rfp_biddind_flag_link($valuerfp->nid);
    }
    return $getall;
}




function get_rfp_singleSummary_information($rfpnode) {
  global $bucket, $awsAccessKey, $awsSecretKey;
  $single_rfpdata = [];
  $single_rfpdata['title'] = $rfpnode->nid;
  $result = _get_node_company_user_name($rfpnode->nid);
  $single_rfpdata['user'] = $result;
  $single_rfpdata['rfp_description'] = $rfpnode->field_rfp_description['und'][0]['value'];
  $single_rfpdata['estimated_cost'] = $rfpnode->field_estimated_cost['und'][0]['value'];
  $single_rfpdata['rfp_types'] = $rfpnode->field_rfp_types['und'][0]['value'];
  $single_rfpdata['rfp_number'] = $rfpnode->field_reference_number['und'][0]['value'];
  $single_rfpdata['rfp_public'] = $rfpnode->field_public['und'][0]['value'];
  $single_rfpdata['rfp_create_confidential_bid'] = $rfpnode->field_create_confidential_bid['und'][0]['value'];
  if(!empty($rfpnode->field_project_manager)) {
    $single_rfpdata['rfp_project_manager']['pmid'] = $rfpnode->field_project_manager['und'][0]['target_id'];
    $single_rfpdata['rfp_project_manager']['pm_name'] = _get_user_mail_realname_by_uid($rfpnode->field_project_manager['und'][0]['target_id'])['realname'];
  }
  if(!empty($rfpnode->field_project)) {
    $single_rfpdata['rfp_project']['projectnid'] = $rfpnode->field_project['und'][0]['target_id'];
    $single_rfpdata['rfp_project']['project_name'] = node_load($rfpnode->field_project['und'][0]['target_id'])->title;
  }
  $thumbnailUrl = '';      
  if(!empty($rfpnode->field_rfp_logo)){
    $credentials = new Credentials($awsAccessKey, $awsSecretKey);
    $s3Client = S3Client::factory(array(
      'credentials' => $credentials
    ));
    $thumbUrl = str_replace("private:/", "s3fs-private", $rfpnode->field_rfp_logo['und'][0]['uri']);
    $thumbnailUrl = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
    $single_rfpdata['rfp_logo']['fid'] = $rfpnode->field_rfp_logo['und'][0]['fid'];
    $single_rfpdata['rfp_logo']['thumbnail'] = $thumbnailUrl;
  }    
  return $single_rfpdata;
}

function get_rfp_singleTimeline($rfpnode) {
  $rfp_timeline = [];
  $rfp_timeline['rfp_issued'] = $rfpnode->field_issued['und'][0]['value'];
  $rfp_timeline['rfp_due'] = $rfpnode->field_due['und'][0]['value'];
  $rfp_timeline['rfp_expected_award'] = $rfpnode->field_expected_award['und'][0]['value'];
  $rfp_timeline['rfp_expected_start'] = $rfpnode->field_expected_start['und'][0]['value'];
  $rfp_timeline['rfp_expected_end'] = $rfpnode->field_expected_end['und'][0]['value'];
  $rfp_timeline['rfp_extend_due_date'] = $rfpnode->field_extend_due_date['und'][0]['value'];
  $rfp_timeline['rfp_extend_by'] = $rfpnode->field_extend_by['und'][0]['value'];
  return $rfp_timeline;
}

function get_rfp_singledocument($rfpnode) {
  global $bucket, $awsAccessKey, $awsSecretKey;
  $rfp_doc = []; 
  foreach($rfpnode->field_rfp_documents['und'] as $keydoc => $valuedoc) {
    $docload = entity_load_single('field_collection_item',$valuedoc['value']);
    $rfp_doc[$keydoc]['rfp_document_type'] = $docload->field_rfp_document_type['und'][0]['value'];
    $rfp_doc[$keydoc]['rfp_doc_comments'] = $docload->field_rfp_comments['und'][0]['value'];
    foreach($docload->field_rfp_document['und'] as $keyuploads => $valueuploads){
      $rfp_doc[$keydoc]['rfp_doc_uploadss'][$keyuploads]['filename'] = $valueuploads['filename'];
      $credentials = new Credentials($awsAccessKey, $awsSecretKey);
      $s3Client = S3Client::factory(array(
        'credentials' => $credentials
      ));
      $thumbUrl = str_replace("private:/", "s3fs-private", $valueuploads['uri']);
      $thumbnailUrl = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
      $rfp_doc[$keydoc]['rfp_doc_uploadss'][$keyuploads]['url'] = $thumbnailUrl;
    }
  return $rfp_doc;
  }
}

function get_rfp_singlebid_packages($rfpid) {
  $bid_package = []; 
  $query = db_select('m6connect_bid_packages', 'mbp');
  $query->fields('mbp', array('bid_package_id', 'entity_id', 'bid_package_name'))
        ->condition('entity_id', $rfpid, '=')
        ->condition('status', 1, '=');
  $result = $query->execute()->fetchAll();
  if ($result && !empty($result)) {
    foreach ($result as $delta => $packageinfo) {
      $bid_package[$delta]['bidID'] = $packageinfo->bid_package_id;
      $bid_package[$delta]['bidname'] = $packageinfo->bid_package_name;
    }
  }
  return $bid_package;
}


function get_rfp_singleProposal_data($rfpid) {
  $arr_erp_propos = db_query("SELECT node.nid AS nid, node.uid AS node_uid, node.title AS node_title, node.created AS node_created
  FROM 
  {node} node
  LEFT JOIN {users} users_node ON node.uid = users_node.uid
  LEFT JOIN {field_data_field_submit_proposal_in_respons} field_data_field_submit_proposal_in_respons ON node.nid = field_data_field_submit_proposal_in_respons.entity_id AND (field_data_field_submit_proposal_in_respons.entity_type = 'node' AND field_data_field_submit_proposal_in_respons.deleted = '0')
  WHERE (( (field_data_field_submit_proposal_in_respons.field_submit_proposal_in_respons_target_id = '".$rfpid."' ) )AND(( (node.status = '1') AND (node.type IN  ('my_proposal')) )))")->fetchAll();
  foreach($arr as $key => $value){
    $pronode = node_load($value->nid);
    $cmpNid = _get_company_nid_by_group_content($pronode);
    $value->cmpname = _get_title_of_node($cmpNid);
    $value->username = _get_user_mail_realname_by_uid($value->node_uid)['realname'];
    $value->createddate = date("F d, Y h:iA T",$value->node_created);
    $value->proposoal_bid_types = $pronode->field_proposoal_bid_types['und'][0]['value'];
    $value->proposal_bid_amount = $pronode->field_proposal_bid_amount['und'][0]['value'];
    $value->bidder_diversity_type = _get_comppany_diversity_names($cmpNid);
  }
  return $arr_erp_propos;
}



function get_rfp_singleBidderFeedback($entity_id) {
    $return = array();
    $query = db_select('m6connect_rfp_bidder_feedback', 'mrbf');
    $query->leftJoin('m6connect_bid_package_invitess', 'mbpi', 'mbpi.rfp_invite_fc_itemid=mrbf.rfp_invite_fc_itemid');
    $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.field_rfp_invite_comapnies_value=mrbf.rfp_invite_fc_itemid');
    $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
    $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
    $query->distinct();
    $query->fields('mbpi', array('bid_package_invites_id'));
    $query->addExpression('IFNULL(mbpi.bid_package_id,0)', 'bid_package_id');
    $query->fields('mrbf', array('bidder_feedback_id', 'rfp_invite_fc_itemid', 'request_bid_intent_count'));
    $query->fields('rcne', array('field_rfp_company_nid_email_value'));
    $query->fields('rcimu', array('field_co_invite_manager_uid_value'));
    $query->condition('mrbf.entity_id', $entity_id, '=');
    $query->condition('ric.entity_id', $entity_id, '=');
    $query->condition('mrbf.status', 1, '=');
    $query->isNotNull('rcne.field_rfp_company_nid_email_value');
    $query->orderBy('rcne.field_rfp_company_nid_email_value', 'ASC');
    $query->orderBy('mbpi.bid_package_id', 'ASC');
    //$query->range($startFrom, $endTo);
    $result = $query->execute()->fetchAll();
    $invitedFieldCollectionpackageMapping = array();
    $companyNodeDetail = array();
    $userAllDetail = array();
    $masterUserDetailsinfo = array();
    $mastrMailLoadDetails = array();
    $managerUids = array();
    if ($result && !empty($result)) {   
    $rowcount = 0;  
        foreach ($result as $delta => $dataObj) {
            if (empty($dataObj->bid_package_id)) {
                $dataObj->bid_package_id = 0;
            }
            $companyNidorEmail = '';
            $invitedBidder = '';
            $CompanyNid = '';
            $companyInfo = '';
            $userDetailsinfo = array();
            $userphone = array();
            $userDetails = array();
            $bidStatus = array();
            $userbidding = array();
            $userNobidding = array();
            $userNoresponse = array();
            if (is_numeric($dataObj->field_rfp_company_nid_email_value)) {
                $CompanyNid = $dataObj->field_rfp_company_nid_email_value;
                $managerUids = explode(',', $dataObj->field_co_invite_manager_uid_value);
                $managerUids = array_filter(array_values($managerUids));
                $managerUids = array_unique(array_values($managerUids));
            } else if (in_array($dataObj->field_rfp_company_nid_email_value, array_keys($mastrMailLoadDetails))) {
                $mailField = $dataObj->field_rfp_company_nid_email_value;
                $managerUids = array($mastrMailLoadDetails[$mailField]['uid']);
                $CompanyNid = $mastrMailLoadDetails[$mailField]['CompanyNid'];
            } else{
              $company_mail = trim($dataObj->field_rfp_company_nid_email_value);
              $emailUserDetail = _get_comapny_details_by_og_email($company_mail);
              if($emailUserDetail && !empty($emailUserDetail)){
                 $managerUids = array($emailUserDetail['user_uid']);
                 $userCompanyNid = $emailUserDetail['entity_id'];
                 if ($userCompanyNid && is_numeric($userCompanyNid)) {
                    $CompanyNid = $userCompanyNid;
                 }
                 $mastrMailLoadDetails[$dataObj->field_rfp_company_nid_email_value] = array('uid' => $emailUserDetail['user_uid'], 'CompanyNid' => $CompanyNid);  
              }
            }
            if ($dataObj->bid_package_id == 0 && !empty($bid_packages2)) {

            }
            if ($CompanyNid) {
                $companyNidorEmail = $CompanyNid;
                if (!isset($companyNodeDetail[$CompanyNid])) {
                    $CompanyNode = node_load($CompanyNid);
                    $companyNodeDetail[$CompanyNode->nid] = array('nid' => $CompanyNode->nid, 'title' => '', 'image' => '');
                    if($CompanyNode->field_type_of_company['und'][0]['value']=='company'){
                      $companyLogo = (isset($CompanyNode->field_logo['und'])) ? $CompanyNode->field_logo['und'] : '';
                      $companyNodeDetail[$CompanyNode->nid] = array('nid' => $CompanyNode->nid, 'title' => $CompanyNode->title, 'image' => $companyLogo);
                    }
                }
                $companyInfo = $companyNodeDetail[$CompanyNid];
                $invitedBidder = $companyInfo['title'];
                if (!empty($managerUids)) {
                    $bidStatus = get_rfp_bidding_flags_status($entity_id, array_values($managerUids), $dataObj->bid_package_id);
                    $masterUserDetailsinfo = array();
                    $userDetailsinfo = get_rfp_bid_feed_back_user_detail(array_values($managerUids), $masterUserDetailsinfo,$CompanyNid);
                    $checked = array('bidding' => '', 'not_bidding' => '', 'not_sure' => '');
                    if (!empty($userDetailsinfo)) {
                        foreach ($userDetailsinfo as $delta => $userObj) {
                            $phoneNumberval = get_international_formatPhoneNumber($userObj['phone']);
                            $userDetails['username'] = $userObj['name']; 
                            $userDetails['usermail'] = $userObj['mail'];
                            $userphone[] =$phoneNumberval;

                            $checked = array(0 => '', 1 => '', 2 => '');
                            $defaultValue = (isset($bidStatus[$userObj['uid']][$dataObj->bid_package_id])) ? $bidStatus[$userObj['uid']][$dataObj->bid_package_id] : '';
                            if (isset($checked[$defaultValue])) {
                                $checked[$defaultValue] = 'checked="checked"';
                            }
                            $userbidding[] = $checked[1];
                            $userNobidding[] = $checked[0];
                            $userNoresponse[] = $checked[2];
                        }
                    }
                }
            } else {
                $companyNidorEmail = $dataObj->field_rfp_company_nid_email_value;
                $companyInfo = array('nid' => '', 'title' => '', 'image' => '');
                $invitedBidder = $dataObj->field_rfp_company_nid_email_value;
                $userphone[] = '<div class="bidder_feedback_phone_section"><div class="bidder_feedback_phone"></div><div class="bidder_feedback_blank">&nbsp;</div></div>';
                $userDetails[] = '<div class="bidder-fb-invitee-name">' . $dataObj->field_rfp_company_nid_email_value . '</div><div class="bidder-fb-invitee-email bidder_feedback_blank"></div>';
                $userbidding[] = '';
                $userNobidding[] = '';
                $userNoresponse[] = '';
            }
            
            
            $companyTab['title'] = $companyInfo['title'];
            $companyTab['image']['fid'] = $companyInfo['image'][0]['fid'];
            $companyTab['image']['uri'] = $companyInfo['image'][0]['uri'];
            $diversityImage ='';
            if($companyInfo['nid'] && is_numeric($companyInfo['nid'])){
              $diversityImage = get_diversity_imageDatabyComapnyid($companyInfo['nid']);
              $companyTab['diversityImage'] = $diversityImage;
            }
            $m6notesTab = '';
            $m6notesTab = get_bidder_feedback_message($dataObj->bidder_feedback_id, $dataObj->bid_package_id, '', $msgpackageStatus = 1);

            $inputButtonStyle = ($dataObj->request_bid_intent_count) ? 'style="background:#419641;"' : '';
            $spanNotificationStyle = ($dataObj->request_bid_intent_count) ? ' notification-count' : '';
            $request_bid_intent_count = ($dataObj->request_bid_intent_count) ? $dataObj->request_bid_intent_count : '';
            $userPhoneNo = implode('', $userphone);
            $mainPhoneNo = str_replace( array( '-', ' ', '(' , ')', '&nbsp;'), '', strip_tags($userPhoneNo));
            $bidConfideceTab['count'] = $dataObj->request_bid_intent_count;
            $bidConfideceTab['rfp_invite_fc_itemid'] = $dataObj->rfp_invite_fc_itemid;
            $bidConfideceTab['bidder_feedback_id'] = $dataObj->bidder_feedback_id;
            $bidConfideceTab['bid_package_id'] = $dataObj->bid_package_id;
            $bidConfideceTab['mainPhoneNo'] = $mainPhoneNo;
            $bidConfideceTab['options'] = array('' => '-- None --', 'High' => 'High', 'Medium' => 'Medium', 'Low' => 'Low','Bidding'=>'Bidding','Not Bidding'=>'Not Bidding');

            $inviteeTab = $userDetails;
            $phoneTab = $userphone;
            $biddingTab = $userbidding;
            $notbiddingTab = $userNobidding;
            $notsurebiddingTab = $userNoresponse;


            $return[$dataObj->bid_package_id]['pkgdetails'] = get_bid_packageByid($rfpid);

            $return[$dataObj->bid_package_id]['row'][] = array(
                'data' => array(
                    array('companyTab' => $companyTab),
                    array('m6notesTab' => $m6notesTab),
                    array('bidConfideceTab' => $bidConfideceTab),
                    array('inviteeTab' => $inviteeTab),
                    array('phoneTab' => $phoneTab),
                    array('biddingTab' => $biddingTab),
                    array('notbiddingTab' => $notbiddingTab),
                    array('notsurebiddingTab' => $notsurebiddingTab),
                ),
                'companyNidorEmail' => $companyNidorEmail,
            );
        $popover++;
        $rowcount++;
        }
    }
    return $return;
}


function get_bid_packageByid($rfpid) {
  $bid_package = []; 
  $query = db_select('m6connect_bid_packages', 'mbp');
  $query->fields('mbp', array('bid_package_id', 'entity_id', 'bid_package_name'))
        ->condition('bid_package_id', $rfpid, '=')
        ->condition('status', 1, '=');
  $result = $query->execute()->fetchAll();
  if ($result && !empty($result)) {
    foreach ($result as $delta => $packageinfo) {
      $bid_package['bidID'] = $packageinfo->bid_package_id;
      $bid_package['bidname'] = $packageinfo->bid_package_name;
    }
  } else if($rfpid==0){
      $bid_package['bidID'] = 0;
      $bid_package['bidname'] = 'Unassigned Bidder(s)';
  }
  return $bid_package;
}

function get_diversity_imageDatabyComapnyid($cmpNid){
  $diversityImage='';
  $diversityCount = db_select('field_data_field_diversity_credentials','dc')->fields('dc', array('field_diversity_credentials_target_id'))->condition('dc.entity_id',$cmpNid)->condition('dc.bundle','organization')->execute()->rowCount();
  if($diversityCount){
    $query = db_select('node','n');
    $query->join('field_data_field_dcrednid_22','fd22','fd22.entity_id=n.nid');
    $query->join('node','credentials','credentials.nid=fd22.field_dcrednid_22_target_id');
    $query->join('field_data_field_credential_doc','fcd','fcd.entity_id=credentials.nid');
    $query->fields('credentials',array('nid'));
    $query->condition('n.type','organization');
    $query->condition('n.nid',$cmpNid);
    $count = $query->execute()->rowCount();
    if($count >0){    
       $diversityImage = 1;  
    }else{
       $diversityImage = 0;   
    }
  }
  return $diversityImage;
}



function getvocparentTermData($vname){
$vocload = taxonomy_vocabulary_machine_name_load($vname);
  $terms = taxonomy_get_tree($vocload->vid, 0, 1, 1);
  $regionTermData = array();
  if(!empty($terms)){
    $j = 0;
    foreach ($terms as $regionData) {
      $regionTermData[$j]['id'] = $regionData->tid;
      $regionTermData[$j]['value'] = $regionData->name;
      $j++;
    }
  }
  return $regionTermData;  
}

function getTermByparentData($ptid){

  $terms = taxonomy_get_children($ptid);
  $regionTermData = array();
  if(!empty($terms)){
    $j = 0;
    foreach ($terms as $regionData) {
      $regionTermData[$j]['id'] = $regionData->tid;
      $regionTermData[$j]['value'] = $regionData->name;
      $j++;
    }
  }
  return $regionTermData;  
}

function getinvite_rfp($node){
$query = db_select('field_data_field_rfp_invite_comapnies', 'ric');
    $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
    $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
    $query->leftJoin('node', 'n', 'n.nid = rcne.field_rfp_company_nid_email_value');
    $query->fields('ric', array('field_rfp_invite_comapnies_value'));
    $query->fields('rcne', array('field_rfp_company_nid_email_value'));
    $query->fields('rcimu', array('field_co_invite_manager_uid_value'));
    $query->fields('n', array('title'));
    $query->condition('ric.entity_id', $node->nid, '=');
    $query->isNotNull('rcne.field_rfp_company_nid_email_value');
    $result = $query->execute()->fetchAll();
    return $result;
}



?>