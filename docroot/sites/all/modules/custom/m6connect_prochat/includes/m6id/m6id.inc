<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';
module_load_include('inc', 'm6connect_onboarding', 'includes/onbording.phase');
/*
 *  function for invite employee on m6id
 */
function m6id_invite_employee(){
  $user_id = $_REQUEST['user_id'];
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $query = db_select('users','u');
    $query->join('og_membership','og','og.etid=u.uid AND og.entity_type=:entityType',array(':entityType'=>'user'));
    $query->join('m6connect_og_membership_email','ogm','og.etid=ogm.user_uid AND ogm.entity_id=og.gid');
    $query->leftjoin('node','n','n.uid=u.uid AND n.type=:nodeType',array(':nodeType'=>'onboarding'));
    $query->leftjoin('field_data_field_first_name','fn','fn.entity_id=u.uid AND fn.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('field_data_field_last_name','ln','ln.entity_id=u.uid AND ln.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('field_data_field_phone','ph','ph.entity_id=u.uid AND ph.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->fields('u',array('uid'));
    $query->addField('ogm','company_email','email');
    $query->addField('fn','field_first_name_value','fname');
    $query->addField('ln','field_last_name_value','lname');
    $query->addField('ph','field_phone_value','phone');
    $query->condition('og.gid',$company_id,'=');
    $query->condition('og.state',1,'=');
    $query->isNull('n.nid');
    $result = $query->execute()->fetchAll();
    $mainData = array();
    if(!empty($result)){
      foreach ($result as $key => $value) {
        $mainData[$key]['uid'] = $value->uid;
        $mainData[$key]['email'] = $value->email;
        $mainData[$key]['first_name'] = $value->fname;
        $mainData[$key]['last_name'] = $value->lname;
        $mainData[$key]['phone'] = $value->phone;
      }
      if(!empty($mainData)){
        $output['success'] = TRUE;
        $output['message'] = 'Record found';
        $output['data'] = $mainData;
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Record not found';    
      }
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  function for user data from email on new invite employee
 */
function m6id_app_invite_new_employee_data(){
  if(isset($_REQUEST['email']) && !empty($_REQUEST['email'])){
    $email = $_REQUEST['email'];
    $user = user_load_by_mail($_REQUEST['email']);
    $mainData = array();
    if(!empty($user)){      
      $mainData['uid'] = $user->uid;
      $mainData['phone'] = $user->field_phone['und'][0]['value'];
      $mainData['fname'] = $user->field_first_name['und'][0]['value'];
      $mainData['lname'] = $user->field_last_name['und'][0]['value'];
      $output['success'] = TRUE;
      $output['message'] = 'Record found';
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'User not found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Email can\'t be empty';
  }  
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  function for delete row from invite employee m6id
 */
function m6id_app_invite_employee_delete(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $delete_user_id = $_REQUEST['delete_user_id'];
    $deleted = array();
    $selectData = db_select('m6connect_og_membership_email', 'm')
                ->fields("m", array('id'))
                ->condition('user_uid',$delete_user_id,'=')
                ->condition('entity_id',$company_id,'=')
                ->execute()->fetchAssoc();
    if(!empty($selectData)){
      $deleted = db_delete('m6connect_og_membership_email')
              ->condition('user_uid',$delete_user_id,'=')
              ->condition('entity_id',$company_id,'=')
              ->execute();
      if(!empty($deleted)){
        $output['success'] = TRUE;
        $output['message'] = 'Data has been deleted';
        $output['data'] = $deleted;
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'User not exist';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Email can\'t be empty';
  }  
  drupal_json_output($output);
  drupal_exit();
}
/*
 *  function for save and email invite new employee
 */
/*function m6id_app_invite_employee_form_submit(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    global $base_url,$base_path;
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $user = user_load($user_id);
    if(isset($_REQUEST['invite_data']) && !empty($_REQUEST['invite_data'])){
      $inviteData = json_decode($_REQUEST['invite_data']);
      drupal_json_output($inviteData);
      drupal_exit();
      $company = node_load($company_id);
      $currentUserName = db_select('realname','r')
                        ->fields('r',array('realname'))
                        ->condition('r.uid',$user_id)->execute()->fetchField();
      $currentUserName = ucwords($currentUserName);
      $currentCompanyName = ucwords($company->title);
      $signupLink = l('sign in',$base_url.$base_path,array('external'=>TRUE));
      $paramsTemp = array(
        'sender' => $user->mail,
        'language' => language_default(),
        'module' => 'm6connect_misc',
        'key' => 'm6id_mail___m6id_invite_employee_notify',
        'build' => TRUE,
      );
      $message = '<p>[M6ID:Invitee_Name],</p><p>Please [M6ID:Signup] to M6Connect and join [M6ID:InviterCompanyName]. This system will be used for onboarding with the respective clients that we commonly work for – it will save us time in safety training and jobsite orientations going forward.<br/><br/>Once you have signed in, navigate to the personal profile and complete the M6ID information - click on the pencil next to your name underneath the accounts section on the left menu and you&apos;ll find the M6ID section there. We will use this information to share with the companies we do work with - this streamlines the onboarding process for new projects.</p><p>Sincerely,<br />[M6ID:InviterName]<br />[M6ID:InviterCompanyName]</p>';
      $ogrolesk = og_roles('node', 'organization'); 
      foreach($inviteData as $key => $dataValues){
        if(!empty($dataValues->new_record)){
          if(!empty($dataValues->uid)){
            $rowUser = user_load($dataValues->uid);
            $membership = og_group('node', $company_id, array(
              'entity type' => 'user',
              'entity' => $rowUser,
              'state' => OG_STATE_ACTIVE,
            ));
            if(isset($membership->id) && is_numeric($membership->id)){
              if(($staffRollId = array_search('staff',$ogrolesk))!==FALSE){
                og_role_grant('node', $company_id, $rowUser->uid, $staffRollId);
              }   
              if(db_table_exists('m6connect_company_join_request')){
                db_merge('m6connect_company_join_request')
                ->key(array('entity_id'=>$values['join_company'],'user_uid'=>$rowUser->uid,'status'=>0))
                ->fields(array(
                  'entity_id'=>$company_id,
                  'user_uid'=>$rowUser->uid,
                  'join_email'=>$dataValues->email,
                  'timestamp'=>time(),
                  'status'=>1,
                ))->execute(); 
              }
            }
          }
          else{
            db_merge('m6connect_onboarding_invited_employee')
            ->key(array(
              'email' => $dataValues->email,
              'company_nid' => $company_id,
            ))
            ->fields(array(
              'email' => $dataValues->email,
              'phone' => $dataValues->phone,
              'country_code' => $dataValues->phone_code,
              'first_name' => $dataValues->fname,
              'last_name' => $dataValues->lname,
              'user_uid' => is_numeric($dataValues->uid)?$dataValues->uid:0,
              'company_nid' => $company_id,
              'requester_user' => $user_id,
            ))->execute();
          }
          //Mail
          $subject = '[M6ID:InviterName] has requested you to Join M6Connect';
          $params = $paramsTemp;
          $replace = array(
            '[M6ID:Invitee_Name]' => ucfirst($dataValues->fname).' '.ucfirst($dataValues->lname),
            '[M6ID:InviterName]' => $currentUserName,
            '[M6ID:InviterCompanyName]' => $currentCompanyName,
            '[M6ID:Signup]' => $signupLink,
          );
          $params['subject'] = str_replace(array_keys($replace),array_values($replace),$subject);
          $params['body'] = str_replace(array_keys($replace),array_values($replace),$message);
          drupal_mail($params['module'], $params['key'], $dataValues['email'], $params['language'], $params);
          //notification
          if (isset($dataValues) && $dataValues->uid && db_table_exists('m6connect_notification'))
          {         
            $m6connect_notification = array(
              'type' => 'm6id',
              'event' => 'invite',
              'entity_id' => 0,
              'company_nid' => 0,
              'message' => Null,
              'request_from' => $user->uid,
              'request_to' => $dataValues->uid,
              'status' => 1,
              'timestamp' => time(),
            );
            entity_save('m6connect_notification', (object) $m6connect_notification);
          } 
          $phone_message = $currentUserName.' has requested that you signup on M6ID at m6connect.com. This will simplify your onboarding process at the companies you work for.  Please login and complete the M6ID section in your personal profile. Click on the pencil next to your name underneath the accounts section on the left menu and you\'ll find the M6ID section there.';
    
          $phoneCode = '+'.$dataValues->phone_code;
          $phoneNumber = str_replace($phoneCode,'',$dataValues->phone);
          m6connect_alert_twilio_send($phoneNumber, $phone_message, $phoneCode);

        }
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Employee data is required';
    }    
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}*/

function m6id_app_invite_employee_form_submit(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    global $base_url,$base_path;
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $user = user_load($user_id);
    if(isset($_REQUEST['email']) && !empty($_REQUEST['email'])){
      $email = $uid = $first_name = $last_name = $phone = $phone_code = '';
      $email = $_REQUEST['email'];
      $uid = $_REQUEST['uid'];
      $first_name = $_REQUEST['first_name'];
      $last_name = $_REQUEST['last_name'];
      $phone = $_REQUEST['phone'];
      // get country code from phone no
      $phCode = trim(get_international_formatPhoneNumber($phone));
      if(strpos($phCode, '(') == TRUE){
        $pCode = explode("(", $phCode);
        $phone_code = $pCode[0];
      }
      $company = node_load($company_id);
      $currentUserName = db_select('realname','r')
                        ->fields('r',array('realname'))
                        ->condition('r.uid',$user_id)->execute()->fetchField();
      $currentUserName = ucwords($currentUserName);
      $currentCompanyName = ucwords($company->title);
      $signupLink = l('sign in',$base_url.$base_path,array('external'=>TRUE));
      $paramsTemp = array(
        'sender' => $user->mail,
        'language' => language_default(),
        'module' => 'm6connect_misc',
        'key' => 'm6id_mail___m6id_invite_employee_notify',
        'build' => TRUE,
      );
      $message = '<p>[M6ID:Invitee_Name],</p><p>Please [M6ID:Signup] to M6Connect and join [M6ID:InviterCompanyName]. This system will be used for onboarding with the respective clients that we commonly work for – it will save us time in safety training and jobsite orientations going forward.<br/><br/>Once you have signed in, navigate to the personal profile and complete the M6ID information - click on the pencil next to your name underneath the accounts section on the left menu and you&apos;ll find the M6ID section there. We will use this information to share with the companies we do work with - this streamlines the onboarding process for new projects.</p><p>Sincerely,<br />[M6ID:InviterName]<br />[M6ID:InviterCompanyName]</p>';
      $ogrolesk = og_roles('node', 'organization');
      if(!empty($uid)){
        $rowUser = user_load($uid);
        $membership = og_group('node', $company_id, array(
          'entity type' => 'user',
          'entity' => $rowUser,
          'state' => OG_STATE_ACTIVE,
        ));
        if(isset($membership->id) && is_numeric($membership->id)){
          if(($staffRollId = array_search('staff',$ogrolesk))!==FALSE){
            og_role_grant('node', $company_id, $rowUser->uid, $staffRollId);
          }   
          if(db_table_exists('m6connect_company_join_request')){
            db_merge('m6connect_company_join_request')
            ->key(array('entity_id'=>$values['join_company'],'user_uid'=>$rowUser->uid,'status'=>0))
            ->fields(array(
              'entity_id'=>$company_id,
              'user_uid'=>$rowUser->uid,
              'join_email'=>$email,
              'timestamp'=>time(),
              'status'=>1,
            ))->execute(); 
          }
        }
      }
      else{
        db_merge('m6connect_onboarding_invited_employee')
        ->key(array(
          'email' => $email,
          'company_nid' => $company_id,
        ))
        ->fields(array(
          'email' => $email,
          'phone' => $phone,
          'country_code' => $phone_code,
          'first_name' => $first_name,
          'last_name' => $last_name,
          'user_uid' => is_numeric($uid)?$uid:0,
          'company_nid' => $company_id,
          'requester_user' => $user_id,
        ))->execute();
      }
      //Mail
      $subject = '[M6ID:InviterName] has requested you to Join M6Connect';
      $params = $paramsTemp;
      $replace = array(
        '[M6ID:Invitee_Name]' => ucfirst($first_name).' '.ucfirst($last_name),
        '[M6ID:InviterName]' => $currentUserName,
        '[M6ID:InviterCompanyName]' => $currentCompanyName,
        '[M6ID:Signup]' => $signupLink,
      );
      $params['subject'] = str_replace(array_keys($replace),array_values($replace),$subject);
      $params['body'] = str_replace(array_keys($replace),array_values($replace),$message);
      drupal_mail($params['module'], $params['key'], $email, $params['language'], $params);
      //notification
      if (!empty($uid) && db_table_exists('m6connect_notification'))
      {        
        $m6connect_notification = array(
          'type' => 'm6id',
          'event' => 'invite',
          'entity_id' => 0,
          'company_nid' => 0,
          'message' => Null,
          'request_from' => $user->uid,
          'request_to' => $uid,
          'status' => 1,
          'timestamp' => time(),
        );
        entity_save('m6connect_notification', (object) $m6connect_notification);
      } 
      $phone_message = $currentUserName.' has requested that you signup on M6ID at m6connect.com. This will simplify your onboarding process at the companies you work for.  Please login and complete the M6ID section in your personal profile. Click on the pencil next to your name underneath the accounts section on the left menu and you\'ll find the M6ID section there.';

      //$phoneCode = '+'.$phone_code;
      if(!empty($phone_code)){
        $phoneNumber = str_replace($phone_code,'',$phone);
        m6connect_alert_twilio_send($phoneNumber, $phone_message, $phone_code);
      }
      $output['success'] = TRUE;
      $output['message'] = 'Invitation send succesfully';
      $output['data'] = 1;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Employee data is required';
    }    
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for manage employee list on m6id
 */
function m6id_employee_list(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    // query for get onboarding company employee detail    
    $m6id_employee = get_onboarding_company_employess_details($company_id);
    // query for get onboarding invited company employee detail
    $m6id_invited_employee = get_onboarding_invited_company_employess_details($company_id);
    if(!empty($m6id_employee) && !empty($m6id_invited_employee)){
      $result = $m6id_employee;
      if(is_array($m6id_employee)){
        if(!empty($m6id_invited_employee)){
          $result = array_merge($m6id_employee, $m6id_invited_employee);
        }        
      }
    }
    $mainData = array();
    if(!empty($result)){      
      // set employee type dropdown data
      $mainData['EmployeeType'] = getM6idEmployeeTypeData($company_id);
      // health screen option
      $mainData['health_screen'] = getArrayValues(array(1=>'Pass',0=>'Fail'));
      $mainData['background_check'] = getArrayValues(array(1=>'Pass',0=>'Fail'));
      $mainData['status'] = getArrayValues(array(1=>'Approve',0=>'Reject',2=>'Pending'));
      // loop on main query object
      $empData = array();
      foreach ($result as $key => $value) {
        $empData[$key]['uid'] = (!empty($value->uid) ? $value->uid : '');
        if(!empty($value->nid)){
          $empData[$key]['m6id_number'] = (!empty($value->field_m6id_value) ? $value->field_m6id_value : '');  
        }
        else{
          $empData[$key]['m6id_number'] = 'M6ID Not Completed';
        }        
        $empData[$key]['badge_id'] = (!empty($value->employee_id) ? $value->employee_id : '');
        $empData[$key]['employee_type'] = (!empty($value->employee_type) ? $value->employee_type : '');
        $empData[$key]['first_name'] = (!empty($value->field_first_name_value) ? $value->field_first_name_value : '');
        $empData[$key]['last_name'] = (!empty($value->field_last_name_value) ? $value->field_last_name_value : '');
        $empData[$key]['email'] = (!empty($value->mail) ? $value->mail : '');
        $empData[$key]['health_screen'] = $value->health_screen != null ? $value->health_screen : '';
        $empData[$key]['background_check'] = $value->background_check != null ? $value->background_check : '';
        $empData[$key]['status'] = $value->status != null ? $value->status : '';
        if(!isset($value->invited_employee_id)){
          $empData[$key]['message_status'] = 'message';
        }else{
          $empData[$key]['message_status'] = 'delete';
        }
      }
      $mainData['employee_data'] = array_values($empData);
      $output['success'] = TRUE;
      $output['message'] = 'Record found';
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Data not found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function to update values for badge id, employee type, health screen, background check, status
 */
function m6id_manage_colleagues_status_update_api(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $uid = $_REQUEST['uid'];
    $updateFields = $res_data = array();
    if(isset($_REQUEST['employee_id'])){
      $updateFields['employee_id'] = $_REQUEST['employee_id'];
    }
    if(isset($_REQUEST['employee_type'])){
      $updateFields['employee_type'] = $_REQUEST['employee_type'];
    }
    if(isset($_REQUEST['health_screen'])){
      $updateFields['health_screen'] = $_REQUEST['health_screen'];
    }
    if(isset($_REQUEST['background_check'])){
      $updateFields['background_check'] = $_REQUEST['background_check'];
    }
    if(isset($_REQUEST['status'])){
      $updateFields['status'] = $_REQUEST['status'];
    }
    if(!empty($updateFields)){
      $update_colleague = db_update('m6connect_onboarding_colleagues_status');
      foreach ($updateFields as $key => $value) {
        $update_colleague->fields($updateFields);
      }
      $update_colleague->condition('company_nid', $company_id);
      $update_colleague->condition('user_uid', $uid);
      $res_data = $update_colleague->execute();
      if(!empty($res_data)){
        $output['success'] = TRUE;
        $output['message'] = 'Employee status has been updated';
        $output['data'] = $res_data;  
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Data already updated';
        $output['data'] = 0;
      }   
    }    
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Please specify employee status name';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for onboarding inprocess content by company
 */
function m6id_onboarding_inprocess_by_company(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $userDetails = onboarding_in_process_company_user_details($company_id);
    $mainData = $empData = $cmpWiseEmpData = array();
    if(!empty($userDetails)){      
      $mainData['EmployeeType'] = getM6idEmployeeTypeData($company_id);
      $mainData['action_btn_data'] = getArrayValues(array(1 => 'Approve', 2 => 'Reject', 3 =>'Pending'));
      foreach($userDetails as $delta => $dataObj){        
        $companyArrayNid = $dataObj->requester_company;
        $companyArrayTitle = $dataObj->requester_company_title;
        if($companyArrayNid == $company_id){
          $companyArrayNid = $dataObj->requstee_company;
          $companyArrayTitle = $dataObj->requstee_company_title;
        }
        $empData['id'] = $dataObj->id;
        $empData['companyId'] = $companyArrayNid;
        $empData['title'] = $companyArrayTitle;
        $empData['m6id_number'] = $dataObj->field_m6id_value;
        $empData['requstee_user'] = $dataObj->requstee_user;
        $empData['employee_type'] = (!empty($dataObj->employee_type) ? $dataObj->employee_type : '');
        $empData['badge_number'] = (!empty($dataObj->badge_number) ? $dataObj->badge_number : '');
        $empData['project_title'] = (!empty($dataObj->requester_project_title) ? $dataObj->requester_project_title : '');
        $empData['realname'] = (!empty($dataObj->realname) ? $dataObj->realname : '');
        $empData['field_phone_value'] = (!empty($dataObj->field_phone_value) ? $dataObj->field_phone_value : '');
        $empData['email'] = (!empty($dataObj->mail) ? $dataObj->mail : '');
        $empData['action_status'] = (!empty($dataObj->requster_status) ? $dataObj->requster_status : '');
        $empData['message_status'] = (!empty($dataObj->message_count) ? 'unread' : 'read');
        $empData['health_screen'] = (is_numeric($dataObj->health_screen))?($dataObj->health_screen==0)?'Fail':'Pass':'';
        $empData['background_check'] = (is_numeric($dataObj->background_check))?($dataObj->background_check==0)?'Fail':'Pass':'';
        $empData['submiteddata'] = (isset($company_id) && $company_id == $dataObj->requstee_company)? 'Submitted' :'Received';
        $cmpWiseEmpData[$companyArrayNid][] = $empData;
      }
      $mainData['employee_data'] = array_values($cmpWiseEmpData);
    }
    if(!empty($mainData)){
      $output['success'] = TRUE;
      $output['message'] = 'Record found';
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'No Record found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for onboarding inprocess content by project
 */
function m6id_onboarding_inprocess_by_project(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $query = db_select('node','n');
    $query->join('og_membership','og','og.etid=n.nid');
    $query->fields('n',array('nid','title'));
    $query->condition('n.type','onboarding_project');
    $query->condition('og.entity_type','node');
    $query->condition('og.group_type','node');
    $query->condition('og.gid',$company_id);
    $onboardingProject = $query->execute()->fetchAllKeyed(0,1);
    $mainData = $empData = array();
    $mainData['EmployeeType'] = getM6idEmployeeTypeData($company_id);
    foreach($onboardingProject as $projectId => $projectName){
      $projectWiseEmpData[$projectId] = array('title' => $projectName, 'data' => array(), 'invited_worker' => array());
    }
    $userDetails = onboarding_in_process_project_user_details($company_id);
    if(!empty($userDetails) && is_array($userDetails)){
      foreach($userDetails as $delta => $dataObj){
        $companyArrayNid = $dataObj->requester_company;
        $companyArrayTitle = $dataObj->requester_company_title;
        $projectArrayNid = $dataObj->requester_project;
        $projectArrayTitle = $dataObj->requester_project_title;
        if($companyArrayNid == $company_id){
          $companyArrayNid = $dataObj->requstee_company;
          $companyArrayTitle = $dataObj->requstee_company_title;
        }        
        $empData['id'] = $dataObj->id;
        $empData['companyId'] = $companyArrayNid;
        $empData['projectId'] = $projectArrayNid;
        $empData['m6id_number'] = $dataObj->field_m6id_value;
        $empData['employee_type'] = (!empty($dataObj->employee_type) ? $dataObj->employee_type : '');
        $empData['badge_number'] = (!empty($dataObj->badge_number) ? $dataObj->badge_number : '');
        $empData['project_title'] = (!empty($dataObj->requester_project_title) ? $dataObj->requester_project_title : '');
        $empData['realname'] = (!empty($dataObj->realname) ? $dataObj->realname : '');
        $empData['field_phone_value'] = (!empty($dataObj->field_phone_value) ? $dataObj->field_phone_value : '');
        $empData['email'] = (!empty($dataObj->mail) ? $dataObj->mail : '');
        $empData['action_status'] = (!empty($dataObj->requster_status) ? $dataObj->requster_status : '');
        $empData['message_status'] = (!empty($dataObj->message_count) ? 'unread' : 'read');
        $empData['health_screen'] = (is_numeric($dataObj->health_screen))?($dataObj->health_screen==0)?'Fail':'Pass':'';
        $empData['background_check'] = (is_numeric($dataObj->background_check))?($dataObj->background_check==0)?'Fail':'Pass':'';
        $empData['submiteddata'] = (isset($company_id) && $company_id == $dataObj->requstee_company)? 'Submitted' :'Received';
        if(!empty($empData)){
          $projectWiseEmpData[$projectArrayNid]['data'][] = $empData;  
        }
        else{
          $projectWiseEmpData[$projectArrayNid] = array('data' => array());
        }
      }      
      $projectNids = array_keys($projectWiseEmpData);      
      // get projects invited workers
      $query = db_select('m6connect_onboarding_project_worker','mopw');
      $query->leftjoin('users','u','LOWER(TRIM(u.mail)) = LOWER(TRIM(mopw.worker_email))');
      $query->leftjoin('node','n','n.uid=u.uid AND n.type=:nodeType',array(':nodeType'=>'onboarding'));
      $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=u.uid AND m6id.bundle=:userBundle', array(':userBundle'=>'user'));  
      $query->fields('mopw');
      $query->fields('m6id',array('field_m6id_value'));
      $query->addField('n','nid','onboarding_nid');
      $query->fields('u','uid');
      $query->condition('mopw.requester_project',$projectNids,'IN');
      $query->condition('mopw.requester_company',$company_id,'=');  
      $projectWorkerLog = $query->execute()->fetchAll();
      $invitedWorkerData = $projectLog = array();
      foreach($projectWorkerLog as $delta => $resultData){
        $m6idTab = 'Not Signed Up';
        if(!empty($resultData->field_m6id_value)){
          $m6idTab = $resultData->field_m6id_value;
          if(empty($resultData->onboarding_nid)){
            $m6idTab .= 'M6ID Not Complete';  
          }
        }        
        $invitedWorkerData['m6id_number'] = $m6idTab;
        $invitedWorkerData['employee_type'] = (!empty($resultData->employee_type) ? $resultData->employee_type : '');
        $invitedWorkerData['badge_number'] = (!empty($resultData->badge_number) ? $resultData->badge_number : '');
        $invitedWorkerData['email'] = (!empty($resultData->worker_email) ? $resultData->worker_email : '');
        $invitedWorkerData['phone'] = (!empty($resultData->worker_phone) ? $resultData->worker_phone : '');
        $invitedWorkerData['first_name'] = (!empty($resultData->worker_fname) ? $resultData->worker_fname : '');
        $invitedWorkerData['last_name'] = (!empty($resultData->worker_lname) ? $resultData->worker_lname : '');
        $invitedWorkerData['remove_worker_id'] = $resultData->id;
        if(!empty($invitedWorkerData)){
          $projectWiseEmpData[$resultData->requester_project]['invited_worker'][] = $invitedWorkerData;
        }
        else{
          $projectWiseEmpData[$resultData->requester_project] = array('invited_worker' => array());
        }
      }
      
      $mainData['employee_data'] = array_values($projectWiseEmpData);
    }
    $output['success'] = TRUE;
    $output['message'] = 'Record found';
    $output['data'] = $mainData;
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for onboarding project invitaion
 */
function m6id_onboarding_project_invitation(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $data = db_query("SELECT DISTINCT node.nid AS nid, node.uid AS node_uid, og_membership_node.gid AS og_membership_node_gid, node.created AS node_created, node.title AS node_title, (flagging_node.uid IS NOT NULL) AS flagging_flagged FROM {node} node INNER JOIN {og_membership} og_membership_node ON node.nid = og_membership_node.etid AND og_membership_node.entity_type = 'node' LEFT JOIN {flagging} flagging_node ON node.nid = flagging_node.entity_id AND (flagging_node.fid = '16' AND flagging_node.uid = ".$user_id.") LEFT JOIN {field_data_field_m6id_project_invited_comp} field_data_field_m6id_project_invited_comp ON node.nid = field_data_field_m6id_project_invited_comp.entity_id AND (field_data_field_m6id_project_invited_comp.entity_type = 'node' AND field_data_field_m6id_project_invited_comp.deleted = '0') WHERE (( (og_membership_node.gid = ".$company_id." ) OR (field_data_field_m6id_project_invited_comp.field_m6id_project_invited_comp_target_id = ".$company_id." ) )AND(( (node.status = '1') AND (node.type IN  ('onboarding_project')) ))) ORDER BY node_created DESC");
    $result = $data->fetchAll();
    if(!empty($result)){
      $mainData = array();
      foreach ($result as $key => $value) {
        $mainData[$key]['nid'] = (!empty($value->nid) ? $value->nid : '');
        $mainData[$key]['title'] = (!empty($value->node_title) ? $value->node_title : '');
        $nodeUser = $nodeCmp = '';
        $nodeUser = _get_user_uid_name_mapping(array($value->node_uid));
        $nodeCmp = _get_title_of_node($value->og_membership_node_gid);
        $mainData[$key]['posted_by'] = $nodeUser[$value->node_uid].' - '.$nodeCmp;
        $mainData[$key]['posted_on'] = (!empty($value->node_created) ? date('F d, Y H:i A T', $value->node_created) :'');
        $mainData[$key]['requester_company'] = (!empty($value->og_membership_node_gid) ? $value->og_membership_node_gid :'');

        $btnName = 'Action';
        if($value->og_membership_node_gid != $company_id){
          $submitCount = db_select('m6connect_onboarding_request','mor')->fields('mor',array('requstee_user'))->condition('mor.requester_project',$value->nid)->condition('mor.requester_company',$value->og_membership_node_gid)->condition('mor.requstee_company',$company_id)->execute()->rowCount();
          $btnName = (!empty($submitCount))?'Submitted':'Received';          
        }
        $mainData[$key]['status'] = $btnName;
      }
      $output['success'] = TRUE;
      $output['message'] = 'Record found';
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Data not found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}

function m6id_onboarding_settings(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $onbordingSetting = db_select('m6connect_onboarding_employee_types','et');
    $onbordingSetting->fields('et');
    $onbordingSetting->condition('company_nid',$company_id);
    $onbordingSetting->orderBy('default_status', 'DESC');
    $onbordingSetting->orderBy('id', 'DESC');
    $data = $onbordingSetting->execute()->fetchAll();
    $mainData = array();
    if(!empty($data)){
      foreach ($data as $key => $value) {
        $mainData[$key]['id'] = $value->id;
        $mainData[$key]['employee_type'] = $value->employee_type;
        $mainData[$key]['default_status'] = $value->default_status;
      }
      $output['success'] = TRUE;
      $output['message'] = 'Record found';
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'No data found';
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
 * function to save new employee type in company
 */
function m6id_onboarding_settings_add_new_employee_type(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    if(isset($_REQUEST['type']) && !empty($_REQUEST['type'])){
      $type = $_REQUEST['type'];
      db_insert('m6connect_onboarding_employee_types')
      ->fields(array(
        'company_nid' => $company_id,
        'employee_type' => $type,
        'default_status' => 0
      ))
      ->execute();
      $output['success'] = TRUE;
      $output['message'] = 'Type added successfully';
      $output['data'] = 1;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Employee type can\'t be empty';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
function m6id_onboarding_settings_employee_type_delete(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    if(isset($_REQUEST['type_id']) && !empty($_REQUEST['type_id'])){
      $typeId = $_REQUEST['type_id'];
      db_delete('m6connect_onboarding_employee_types')->condition('company_nid',$company_id)->condition('id',$typeId)->execute();
      $output['success'] = TRUE;
      $output['message'] = 'Employee type deleted successfully';
      $output['data'] = 1;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Employee type id can\'t be empty';
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
 * function for Submit employees action on Submitted / Received button on m6id project invitation
 */
function m6id_onboarding_project_invitation_submit_employees_action(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    if(isset($_REQUEST['nid']) && $_REQUEST['nid']){
      $project_nid = $_REQUEST['nid'];
      $user_id = $_REQUEST['user_id'];
      $mainData = array();
      if(!empty($node = node_load($project_nid)) && is_object($node) && $node->type =='onboarding_project'){
        $query = db_select('og_membership','og');
        $query->join('m6connect_og_membership_email','oge','og.gid=oge.entity_id AND oge.user_uid=og.etid');
        $query->leftjoin('node','n','n.uid=og.etid AND n.type=:nodeType',array(':nodeType'=>'onboarding'));
        $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=og.etid AND m6id.bundle=:userBundle', array(':userBundle'=>'user'));
        $query->leftjoin('realname','r','r.uid=og.etid');
        $query->leftjoin('m6connect_onboarding_request','mor','mor.requstee_user=og.etid AND mor.requstee_company=:companyNid AND mor.requester_project=:ProjectNid',array(':companyNid'=>$company_id,':ProjectNid'=>$project_nid));
        $query->leftjoin('field_data_field_last_name','lname','lname.entity_id=og.etid AND lname.bundle=:userBundle', array(':userBundle'=>'user'));
        $query->leftjoin('m6connect_onboarding_colleagues_status','ous','ous.user_uid=og.etid AND ous.company_nid=:companyNid',array(':companyNid'=>$company_id));        
        $query->fields('oge',array('user_uid','company_email'));
        $query->fields('mor',array('requstee_user'));
        $query->fields('m6id',array('field_m6id_value'));
        $query->fields('r',array('realname'));
        $query->fields('ous',array('employee_id','health_screen','background_check','status'));
        $query->fields('n',array('nid'));
        $query->addExpression('IFNULL(n.nid,99999999999)','onboarding_nid');
        $query->condition('og.gid',$company_id,'=');
        $query->condition('og.entity_type','user','=');
        $query->condition('og.state',1,'=');        
        $query->orderBy('onboarding_nid');
        $result = $query->execute()->fetchAll();
        $approval_status = array(0=>'Rejected', 1=>'Approved', 2=>'Pending');
        foreach ($result as $key => $value) {
          $mainData[$key]['checked'] = !empty($value->requstee_user) ? '1' : '0';
          $mainData[$key]['m6id_number'] = (!empty($value->field_m6id_value) ? $value->field_m6id_value : '');
          $mainData[$key]['employee_id'] = (!empty($value->employee_id) ? $value->employee_id : '');
          $mainData[$key]['name'] = (!empty($value->realname) ? $value->realname : '');
          $mainData[$key]['email'] = (!empty($value->company_email) ? $value->company_email : '');
          $mainData[$key]['m6id_status'] = (!empty($value->nid) ? 'Completed' : 'Not Completed');
          $mainData[$key]['approval_status'] = (!empty($value->status) ? $approval_status[$value->status] : '');          
        }
        $output['success'] = TRUE;
        $output['message'] = 'Record found';
        $output['data'] = $mainData;
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Node id is wronge';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Node id can\'t be empty';
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
 *function for Submit employees action on Submitted / Received button on m6id project invitation submit
 */
function m6id_onboarding_project_invitation_submit_employees_action_submit(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    if(isset($_REQUEST['nid']) && $_REQUEST['nid']){
      $project_nid = $_REQUEST['nid'];
      $user_id = $_REQUEST['user_id'];
      $mainData = array();
      $node = node_load($project_nid);
      if(!empty($node) && is_object($node) && $node->type =='onboarding_project'){
        if(isset($_REQUEST['selected_employee_ids']) && !empty($_REQUEST['selected_employee_ids'])){
          // validate submit data
          $selected_employee_ids = json_decode($_REQUEST['selected_employee_ids']);
          $empIdsArr = array();
          foreach ($selected_employee_ids as $key => $value) {
            $empIdsArr[$key] = $value->id;
          }
          if(count($empIdsArr) < 1){
            $output['success'] = FALSE;
            $output['message'] = 'Please Select at least one';
            drupal_json_output($output);
            drupal_exit();
          }
          else{
            $EmployeeStatus = _get_user_m6id_employee_status_by_comid($company_id);
            $ApprovedCount= 0;
            foreach($EmployeeStatus as $ukey => $svalue){ 
              if(in_array($ukey,$empIdsArr) && $svalue != 1){
                ++$ApprovedCount;
              }
            }
            if($ApprovedCount > 0){
              $output['success'] = FALSE;
              $output['message'] = 'Employee must be in Approve status in order to submit.';
              drupal_json_output($output);
              drupal_exit();
            }
          }
          // code for save data
          if((is_numeric($project_nid)) && (isset($_REQUEST['requester_company'])) && (is_numeric($_REQUEST['requester_company']))){
            $requester_company = $_REQUEST['requester_company'];
            $notCpmpletedUserData = isset($_REQUEST['not_completed_user']) ? json_decode($_REQUEST['not_completed_user']) : '';
            $notCpmpletedUser = array();
            if(!empty($notCpmpletedUserData)){
              foreach ($notCpmpletedUserData as $key => $value) {
                $notCpmpletedUser[$key] = $value->id;
              }
            }
            $insert = db_insert('m6connect_onboarding_request')->fields(array('requester_company', 'requester_project', 'requstee_company', 'requstee_user','requster_status','requstee_status','submit_timestamp','request_id','request_type'));
            foreach($selected_employee_ids as $empId => $isSubmited){
              if($isSubmited){
                if(!in_array($empId, $empIdsArr) && !in_array($empId, $notCpmpletedUser)){
                  $insert->values(array(
                    'requester_company' => $requester_company,
                    'requester_project' => $project_nid,
                    'requstee_company' => $company_id,
                    'requstee_user' => $empId,
                    'requster_status' => 0,
                    'requstee_status' => 1,
                    'submit_timestamp' => time(),
                    'request_id' => NULL,
                    'request_type' => 'project_invite',
                  ));
                  $newEmployees[] = $empId;                  
                }     
              }
              else if(in_array($empId,$values['default_submitted'])){
                $revovedEmployee[] = $empId;   
              }
            }
            if(!empty($newEmployees)){
              $insert->execute();
            }
            if(!empty($revovedEmployee)){
              db_delete('m6connect_onboarding_request')->condition('requstee_user',$revovedEmployee,'IN')->condition('requester_project',$project_nid)->condition('requester_company',$requester_company)->condition('requstee_company',$company_id)->condition('request_type','project_invite')->execute();
            }
            $output['success'] = TRUE;
            $output['message'] = 'Employees submitted successfully';
          }
          else{
            $output['success'] = FALSE;
            $output['message'] = 'Requester Company id can\'t be null';
          }
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = 'Please Select at least one';
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Node id is wronge';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Node id can\'t be empty';
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
 * function for reject action on Submitted / Received button on m6id project invitation
 */
function m6id_onboarding_project_invitation_reject_action(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    if(isset($_REQUEST['nid']) && $_REQUEST['nid']){
      $project_nid = $_REQUEST['nid'];
      $user_id = $_REQUEST['user_id'];
      $mainData = array();
      //$node = node_load($project_nid);
      if(!empty($node = node_load($project_nid)) && is_object($node) && $node->type =='onboarding_project'){
        $requeter_company = _get_company_nid_by_group_content($project_nid);
        if(!empty($requeter_company)){
          if(isset($node->field_m6id_project_invited_comp['und']) && !empty($node->field_m6id_project_invited_comp['und'])){
            foreach($node->field_m6id_project_invited_comp['und'] as $index => $item){
              if($item['target_id'] == $company_id){
                unset($node->field_m6id_project_invited_comp['und'][$index]);
                $removeFlag = 1;
                break;
              }
            }
          }
          if($removeFlag){
            $node->field_m6id_project_invited_comp['und'] = array_values($node->field_m6id_project_invited_comp['und']);
            node_save($node);  
            db_delete('m6connect_onboarding_request')->condition('requester_project',$node->nid)->condition('requester_company',$requeter_company)->condition('requstee_company',$company_id)->condition('request_type','project_invite')->execute();
            $output['success'] = TRUE;
            $output['message'] = 'Project invitation rejected successfully';
            $output['data'] = 1;
          }
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = 'Node id is wronge';
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Node id is wronge';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Node id can\'t be empty';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
function m6id_onboarding_project_invitation_invite_company_action(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $company_id = $_REQUEST['companyNid'];
    $company = node_load($company_id);
    if(isset($_REQUEST['nid']) && $_REQUEST['nid']){
      global $base_url;
      $nid = $_REQUEST['nid'];
      $user_id = $_REQUEST['user_id'];
      $node = node_load($nid);
      if(!empty($node) && is_object($node) && $node->type =='onboarding_project'){
        $companyusersdetail = _get_user_mail_realname_by_uid($user_id);
        $companyusersmail = $companyusersdetail['mail'];
        $companyusersfullname = $companyusersdetail['realname'];
        $mailSubject = 'M6ID Invitation for the [Onboarding:InvitedManagerTitle] Project';
        $mailBody = '[Onboarding:InvitedManagerName],<p>Your company has been invited to use M6Connect&apos;s M6ID service for the [Onboarding:InvitedManagerTitle] project. This is a requirement of your contract and will simplify the onboarding process for your workers.</p><p>You have been setup as an M6ID Manager for your company. Please sign in to <a href="'.$base_url.'">M6Connect</a> and navigate to M6ID located on the left menu under My Services. M6ID will be used for onboarding your workers (employees and subcontractors, consultants, labor, etc) – it will save us time in safety training and jobsite orientations going forward.</p><p><b>Step 1 - Manage Employees Section</b></p><p>You will need to invite all of your workers to M6ID and assist them in the signup process.</p><p>A. Under the M6ID tab, select the Manage Employees section.</p><p>B. Navigate to the + Invite Employees section and click on it and you will receive a popup to invite your employees.</p><p>C. In the popup, add the employees information or select them from the list by checking the check box(s) on the left side to invite them to project. They will receive an email, text or both depending on the information you provide.</p><p><b>Step 2 - Worker Signup Process</b></p><p>You will need to ensure your workers utilize the following steps for signup.</p><p>A. Login to <a href="'.$base_url.'">M6Connect.com</a> and join your company during the signup process. Your company administrator will need to approve the request to join your company. The administrator will be emailed each time a worker signs up and will need to grant them access.</p><p>B. Workers will need to complete all of the required fields in their M6ID profile. They may do so by clicking on the pencil next to their name underneath the Account Management section in the left hand menu.</p><p><b>Step 3 -  Submit Workers to Project(s)</b></p><p>A. Once workers have signed in and completed their M6ID profile you may then submit them projects.</p><p>B. To submit, navigate to the Project Invitations tab and then select the green Actions button drop Submit Employees.</p><p>C.Select the check boxes in the popup for those employees you wish to submit.</p><p>D.Step 3 must be completed before workers can be admitted on the project location.</p>
          <p>Thank you for your efforts in making the onboarding process go smoother. This new process will save your team and ours a significant amount of time during this startup process. If you have questions feel free to contact me '.$companyusersmail.' or you may contact support@m6connect.com.<p><br/><p>Sincerely,</p><p>'.$companyusersfullname.'</p><p>'.$company->title.'</p>';
        $mail_params = array(
          'subject' => $mailSubject,
          'body' => $mailBody,
          'language' => language_default(),
          'module' => 'm6connect_misc',
          'key' => 'm6id_mail___m6id_company_email_invite',
          'build' => TRUE,
        );
        if(isset($_REQUEST['invite_company']) && !empty($_REQUEST['invite_company'])){
          $inviteCompany = json_decode($_REQUEST['invite_company']);
          $project_invited_company_default = isset($node->project_company_default_invited)?$node->project_company_default_invited:array();
          $project_invited_email_default = isset($node->project_invited_email_default)?$node->project_invited_email_default:array();
          $new_invited_companies = $inviteOnlyOnce = array();$inside = 0;
          foreach ($inviteCompany as $key => $value) {
            if(!empty($value->company_name) && !empty($value->company_nid) && is_numeric($value->company_nid)){
              if(!in_array($value->company_nid, $inviteOnlyOnce) && !in_array($value->company_nid, $project_invited_company_default)){
                $node->field_m6id_project_invited_comp['und'][] = array('target_id'=>$value->company_nid);
                $inside = 1;
                $comapnyManageres =  _get_company_users_email_by_onboarding_roles($value->company_nid, array('M6ID Manager','Site Manager','administrator member','company admin'));         
                $sendToManagers = array();
                if(isset($comapnyManageres['Site Manager']) && !empty($comapnyManageres['Site Manager'])){
                  $sendToManagers = $comapnyManageres['Site Manager'];
                }else if(isset($comapnyManageres['M6ID Manager']) && !empty($comapnyManageres['M6ID Manager'])){
                  $sendToManagers = $comapnyManageres['M6ID Manager'];
                }else if(isset($comapnyManageres['company admin']) && !empty($comapnyManageres['company admin'])){
                  $sendToManagers = $comapnyManageres['company admin'];
                }else if(isset($comapnyManageres['administrator member']) && !empty($comapnyManageres['administrator member'])){
                  $sendToManagers = $comapnyManageres['administrator member'];  
                }
                if(!empty($sendToManagers)){
                  foreach($sendToManagers as $index => $mgrDetail){                     
                    $replace = $mail_replace;
                    $params = $mail_params;
                    $replace['[Onboarding:InvitedManagerName]'] = ucwords($mgrDetail->realname);
                    $replace['[Onboarding:InvitedManagerTitle]'] = ucwords($node->title);
                    $params['subject'] =  str_replace(array_keys($replace),array_values($replace),$params['subject']);
                    $params['body'] =  str_replace(array_keys($replace),array_values($replace),$params['body']);
                    $mailarray[] = drupal_mail($params['module'], $params['key'], $mgrDetail->company_email, $params['language'], $params); 
                    if (db_table_exists('m6connect_notification')) {          
                      $m6connect_notification = array(
                        'type' => 'm6id',
                        'event' => 'project_invitations',
                        'entity_id' => $nid,
                        'company_nid' => $value->company_nid,
                        'message' => NULL,
                        'request_from' => $user_id,
                        'request_to' => $mgrDetail->uid,
                        'status' => 1,
                        'timestamp' => time(),
                      );
                      entity_save('m6connect_notification', (object) $m6connect_notification);
                    }
                  }
                }
              }
            }
          }
        }
        if(!empty($_REQUEST['invited_email'])){
          $inviteOnlyOnce = array();
          $usersfulldetails = '';
          $inviteEmail = json_decode($_REQUEST['invited_email']);
          foreach ($inviteEmail as $key => $value) {
            if(!empty($value->email_address)  && valid_email_address($value->email_address)){
              if(!in_array($value->email_address, $inviteOnlyOnce) && !in_array($value->email_address, $project_invited_email_default)){
                $node->field_m6id_project_invited_email['und'][] = array('value'=>$value->email_address);
                $usersfulldetails = _get_user_details_by_og_email($value->email_address);
                if(empty($usersfulldetails)) {
                  $userName = $value->email_address;
                }else{
                  $userName = ucwords($usersfulldetails->realname);
                }
                $inside = 1; 
                $replace = $mail_replace;
                $params = $mail_params;
                $replace['[Onboarding:InvitedManagerName]'] = $userName;
                $replace['[Onboarding:InvitedManagerTitle]'] = ucwords($node->title);
                $params['subject'] =  str_replace(array_keys($replace),array_values($replace),$params['subject']);
                $params['body'] =  str_replace(array_keys($replace),array_values($replace),$params['body']);
                $mailarray[] = drupal_mail($params['module'], $params['key'], $value->email_address, $params['language'], $params);
              }
            }
          }
        }
        node_save($node);
        if(!empty($_REQUEST['invite_company']) && !empty($_REQUEST['invited_email'])){
          $output['success'] = TRUE;
          $output['message'] = 'Company and user invited successfully';
          $output['data'] = 1;
        }
        else if(!empty($_REQUEST['invite_company']) && empty($_REQUEST['invited_email'])){
          $output['success'] = TRUE;
          $output['message'] = 'Company invited successfully';
          $output['data'] = 1;
        }
        else if(!empty($_REQUEST['invited_email']) && empty($_REQUEST['invite_company'])){
          $output['success'] = TRUE;
          $output['message'] = 'Company invited successfully';
          $output['data'] = 1;
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = 'Please enter company name or email';
          $output['data'] = 1;
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Node id is wronge';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Node id can\'t be empty';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}
// company autosearch
function m6id_onboarding_invite_company_autosearch(){
  if(isset($_REQUEST['text']) && !empty($_REQUEST['text'])){
    $q = $_REQUEST['text'];
    $comppanyListing = _get_all_organigation_mapping();
    $matchedOwner = preg_grep("/^{$q}/i",array_values($comppanyListing));
    if(!empty($matchedOwner)){
      $mainData = array();$i=0;
      foreach ($matchedOwner as $key => $value) {
        $mainData[$i]['id'] = $key;
        $mainData[$i]['value'] = $value;
        $i++;
      }
      $output['success'] = TRUE;
      $output['message'] = 'Data found';
      $output['data'] = $mainData;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Data not found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Search string can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}

function m6id_onboarding_project_invitation_project_open(){
  if(isset($_REQUEST['nid']) && !empty($_REQUEST['nid'])){
    $nid = $_REQUEST['nid'];
    $node = node_load($nid);
    $mainData = array();
    if(!empty($node)){
      $mainData['project_number'] = isset($node->field_project_number_cal['und']) ? $node->field_project_number_cal['und'][0]['value'] : '';
      $invited = $node->field_m6id_project_invited_comp['und'];
      if(!empty($invited)){
        $invitedCmp = array();
        foreach ($invited as $key => $value) {
          $invitedCmp[$key] = $value['target_id'];
        }
        if(!empty($invitedCmp)){
          $inviteEntity = entity_load('node', $invitedCmp);
          if(!empty($inviteEntity)){
            $invitedData = array();$i=0;
            foreach ($inviteEntity as $key => $value) {
              $inviteData[$i]['company_id'] = $value->nid;
              $inviteData[$i]['name'] = isset($value->field_owner_name['und']) ? $value->field_owner_name['und'][0]['value'] : '';
              $inviteData[$i]['company'] = (!empty($value->title) ? $value->title : '');
              $inviteData[$i]['email'] = isset($value->field_company_email['und']) ? $value->field_company_email['und'][0]['email'] : '';
              $i++;
            }
            $mainData['companyData'] = $inviteData;
            $output['success'] = TRUE;
            $output['message'] = 'Data found';
            $output['data'] = $mainData;
          }
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Invited company data not found';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Data not found';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Nid can\'t be empty';
  }
  drupal_json_output($output);
  drupal_exit();
}

/*
 *  Global node delete function
 */
function app_node_delete(){
  if(isset($_REQUEST['nid']) && $_REQUEST['nid']){
    $nid = $_REQUEST['nid'];
    if($nid != 645){
      $user_id = $_REQUEST['user_id'];
      $node = node_load($nid);
      if(!empty($node)){
        if($node->uid == $user_id){
          node_delete($nid);
          $output['success'] = TRUE;
          $output['message'] = 'Data deleted successfully';
          $output['data'] = 1;
        }
        else{
          $companyId = $node->og_group_ref['und'][0]['target_id'];
          if(!empty($companyId)){
            $companyUser = _get_user_mappping_by_group_company_nid($companyId);
            if(!empty($companyUser)){
              $allUser = array();$i=0;
              foreach ($companyUser as $key => $value) {
                $allUser[$i] = $key;
                $i++;
              }
              if(!empty($allUser)){
                if(!empty(in_array($user_id, $allUser))){
                  $user = user_load($user_id);
                  $user_roles = $user->roles;
                  if((in_array('administrator', $user_roles)) || (in_array('Company Admin', $user_roles))){
                    node_delete($nid);
                    $output['success'] = TRUE;
                    $output['message'] = 'Data deleted successfully';
                    $output['data'] = 1;
                  }
                  else{
                    $output['success'] = FALSE;
                    $output['message'] = 'You are not authorize user for this action';
                  }
                }
                else{
                  $output['success'] = FALSE;
                  $output['message'] = 'You are not authorize user for this action';
                }
              }
              else{
                $output['success'] = FALSE;
                $output['message'] = 'You are not authorize user for this action';
              }
            }
          }
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Data not found';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Please change nid';
    }    
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Nid can\'t be null';
  }
  drupal_json_output($output);
  drupal_exit();
}

function m6id_onboarding_roster_by_company_action_status(){
  if(isset($_REQUEST['id']) && !empty($_REQUEST['id'])){
    $dataId = $_REQUEST['id'];
    if(isset($_REQUEST['status']) && !empty($_REQUEST['status'])){
      $status = $_REQUEST['status'];
      $dataStatus = '';
      $dataStatus = array('requster_status' => $status);      
      db_update('m6connect_onboarding_request')->fields($dataStatus)->condition('id',$dataId,'=')->execute();
      $output['success'] = TRUE;
      $output['message'] = 'Data updated successfully';
      $output['data'] = 1;
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Status can\'t be null';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Data id can\'t be null';
  }
  drupal_json_output($output);
  drupal_exit();
}

function m6id_onboarding_roster_by_company_action_view(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    $companyNid = $_REQUEST['companyNid'];
    if(isset($_REQUEST['requstee_user']) && !empty($_REQUEST['requstee_user'])){
      global $bucket, $awsAccessKey, $awsSecretKey;
      $credentials = new Credentials($awsAccessKey, $awsSecretKey);
      $s3Client = S3Client::factory(array(
        'credentials' => $credentials
      ));
      $requsteeUserId = $_REQUEST['requstee_user'];
      $ob_nid = get_user_onboarding_nid($requsteeUserId);
      $mainData = $finelData = array();
      if(!empty($ob_nid)){
        $node = node_load($ob_nid);
        if(!empty($node)){
          $m6user = user_load($node->uid);
          $mainData['nid'] = $node->nid;
          $mainData['m6id'] = isset($m6user->field_m6id['und']) ? $m6user->field_m6id['und'][0]['value'] : '';
          $mainData['first_name'] = isset($m6user->field_first_name['und']) ? $m6user->field_first_name['und']['0']['value'] : '';
          $mainData['middle_name_name'] = isset($m6user->field_middle_name['und']) ? $m6user->field_middle_name['und']['0']['value'] : '';
          $mainData['last_name'] = isset($m6user->field_last_name['und']) ? $m6user->field_last_name['und']['0']['value'] : '';
          $mainData['dob'] = isset($m6user->field_date_of_birth['und']) ? date("j F, Y", strtotime($m6user->field_date_of_birth['und']['0']['value'])) : '';
          $mainData['photo'] = isset($m6user->field_user_profile_photo['und']) ? file_create_url($m6user->field_user_profile_photo['und'][0]['uri']) : '';
          $mainData['mobile_phone_number'] = isset($m6user->field_phone['und']) ? get_international_formatPhoneNumber($m6user->field_phone['und']['0']['value']) : '';
          $mainData['work_phone_number'] = isset($m6user->field_mobile_phone['und']) ? get_international_formatPhoneNumber($m6user->field_mobile_phone['und']['0']['value']) : '';
          $mainData['alt_phone_number'] = isset($m6user->field_alt_phone['und']) ? get_international_formatPhoneNumber($m6user->field_alt_phone['und']['0']['value']) : '';
          if(!empty($m6user->field_job_titles['und'])){
            $tid = $m6user->field_job_titles['und']['0']['target_id'];
            $term = taxonomy_term_load($tid);
            $name = $term->name;
          }          
          $mainData['job_title'] = (!empty($name)) ? $name : '';
          $mainData['address1'] = isset($m6user->field_address['und']) ? $m6user->field_address['und']['0']['thoroughfare'] : '';
          $mainData['address2'] = isset($m6user->field_address['und']) ? $m6user->field_address['und']['0']['premise'] : ''; 
          $mainData['city'] = isset($m6user->field_address['und']) ? $m6user->field_address['und']['0']['locality'] : ''; 
          $mainData['state'] = isset($m6user->field_address['und']) ? $m6user->field_address['und']['0']['administrative_area'] : ''; 
          $mainData['postal_code'] = isset($m6user->field_address['und']) ? $m6user->field_address['und']['0']['postal_code'] : ''; 
          $mainData['country'] = isset($m6user->field_address['und']) ? $m6user->field_address['und']['0']['country'] : '';

          $mainData['us_citizen'] = isset($node->field_are_you_a_us_citizen['und']) ? $node->field_are_you_a_us_citizen['und']['0']['value'] : '';
          $mainData['personal_email'] = isset($m6user->field_organization_mail['und']) ? $m6user->field_organization_mail['und']['0']['email'] : '';
          $mainData['work_email'] = isset($m6user->field_confirm_your_email_address['und']) ? $m6user->field_confirm_your_email_address['und']['0']['email'] : '';
          $mainData['home_phone_number'] = isset($m6user->field_home_phone['und']) ? get_international_formatPhoneNumber($m6user->field_home_phone['und']['0']['value']) : '';
          $mainData['cellular_phone_number'] = isset($m6user->field_cellular_phone['und']) ? get_international_formatPhoneNumber($m6user->field_cellular_phone['und']['0']['value']) : '';
          if(isset($node->field_facilities_construction['und']) && !empty($node->field_facilities_construction['und'])){
            $facilities_construction = $node->field_facilities_construction['und']; 
            foreach($facilities_construction as $facilitiesval){ 
              $factid = $facilitiesval['tid'];
              $facterm = taxonomy_term_load($factid);
              $facname = $facterm->name;
            }
          }
          $mainData['trade_category'] = (!empty($facname) ? $facname : '');
          $mainData['drivers_license_number'] = isset($node->field_drivers_license_number['und']) ? $node->field_drivers_license_number['und'][0]['value'] : '';
          $mainData['country_of_issuance'] = isset($node->field_drivers_license_issuance['und']) ? $node->field_drivers_license_issuance['und'][0]['country'] : '';
          $mainData['state_of_issuance'] = isset($node->field_drivers_license_issuance['und']) ? $node->field_drivers_license_issuance['und'][0]['administrative_area'] : '';
          $mainData['driving_license'] = $mainData['driving_license_filename'] = '';
          if(isset($node->field_attach_driving_licence['und'])){
            foreach($node->field_attach_driving_licence['und'] as $attach_driving){      
              $driving_fid = $attach_driving['fid'];
              $drivingfile = file_load($driving_fid);
              $drivinguri = $drivingfile->uri;
              $drivingtypechk = $drivingfile->type;
              if($drivinguri){ 
                if($drivingtypechk == 'image'){
                  $drivingfileImg = str_replace("private:/", "s3fs-private", $drivingfile->uri);
                  $mainData['driving_license'] = $s3Client->getObjectUrl($bucket, $drivingfileImg, '+1day');
                }
                if($drivingtypechk == 'document'){
                  $drivingimages = file_create_url($drivinguri);
                  $mainData['driving_license_filename'] = $drivingfile->filename;
                  $mainData['driving_license'] = $drivingimages;
                }
              }
            }
          }
          $mainData['company_name'] = isset($node->field_vehicle_insurance_statemen['und']) ? $node->field_vehicle_insurance_statemen['und'][0]['value'] : '';
          $mainData['policy_expiration_date'] = isset($node->field_policy_expiration_date['und']) ? date("F j, Y", $node->field_policy_expiration_date['und']['0']['value']) : '';
          $mainData['vehicle_license_plate_number'] = isset($node->field_vehicle_license_plate_numb['und']) ? $node->field_vehicle_license_plate_numb['und']['0']['value'] : '';
          $mainData['vehicle_image'] = $mainData['vehicle_image_filename'] = '';
          foreach($node->field_attach_copy['und'] as $attach_vehicle){
            $vehicle_fid = $attach_vehicle['fid'];
            $vehiclefile = file_load($vehicle_fid);
            $vehicleuri =  $vehiclefile->uri;
            $vehicletypechk =  $vehiclefile->type;
            if($vehicleuri){ 
              if($vehicletypechk == 'image'){  
                $mainData['vehicle_image'] = file_create_url($vehiclefile->uri);
              }
              if($vehicletypechk == 'document'){
                $vehicledocument = file_create_url($vehicleuri);
                $mainData['vehicle_image_filename'] = $vehiclefile->filename;
                $mainData['vehicle_image'] = $vehicledocument;
              }
            }
          }

          $mainData['emergency_first_name'] = isset($node->field_emergency_first_name['und']) ? $node->field_emergency_first_name['und']['0']['value'] : '';
          $mainData['emergency_middle_name'] = isset($node->field_emergency_middle_name['und']) ? $node->field_emergency_middle_name['und']['0']['value'] : '';
          $mainData['emergency_last_name'] = isset($node->field_emergency_last_name['und']) ? $node->field_emergency_last_name['und']['0']['value'] : '';
          if(!empty($node->field_emergency_phone_number['und']['0']['value'])){  
            $emergencyphone = $node->field_emergency_phone_number['und']['0']['value'];  
            $mainData['emergency_cellular_phone_number'] = get_international_formatPhoneNumber($emergencyphone);         
          }
          $items = field_get_items('node', $node, 'field_onbarding_credentials');
          $credentialData = array();
          foreach ($items as $key => $item) {
            $fcvalue = field_collection_field_get_entity($item);
            $credentialData[$key]['credential_type'] = isset($fcvalue->field_ob_credential_type['und']) ? $fcvalue->field_ob_credential_type['und'][0]['value'] : '';
            $credentialData[$key]['name_of_credential'] = isset($fcvalue->field_title_name_of_credential['und']) ? $fcvalue->field_title_name_of_credential['und'][0]['value'] : '';
            $credentialData[$key]['received_presented_by'] = isset($fcvalue->field_received_presented_by['und']) ? $fcvalue->field_received_presented_by['und'][0]['value'] : '';
            $credentialData[$key]['received'] = isset($fcvalue->field_ob_received['und']) ? date("F j, Y", $fcvalue->field_ob_received['und'][0]['value']) : '';
            $credentialData[$key]['expires'] = isset($fcvalue->field_ob_expires['und']) ? date("F j, Y", $fcvalue->field_ob_expires['und'][0]['value']) : '';
            $credentialData[$key]['attached_image'] = '';
            if(isset($fcvalue->field_ob_attach_image['und']) && !empty($fcvalue->field_ob_attach_image['und'][0]['uri'])){ 
              if($fcvalue->field_ob_attach_image['und'][0]['type'] == 'image'){
                $credentialData[$key]['attached_image'] = file_create_url($fcvalue->field_ob_attach_image['und']['0']['uri']);
              }
              if($fcvalue->field_ob_attach_image['und'][0]['type'] == 'document'){
                $obfilename = $fcvalue->field_ob_attach_image['und'][0]['filename']; 
                $credentialData[$key]['attached_image'] = file_create_url($fcvalue->field_ob_attach_image['und']['0']['uri']);
              }
            }
          }
          $mainData['credential'] = $credentialData;
          //$mainData['status'] = appGetUserM6idStatus($m6user);
          $finelData['profile'] = $mainData;
          $finelData['status'] = appGetUserM6idStatus($m6user);
          $output['success'] = TRUE;
          $output['message'] = 'Record found';
          $output['data'] = $finelData;
        }
        else{
          $output['success'] = FALSE;
          $output['message'] = 'Data not found for this requestee';
        }
      }
      else{
        $output['success'] = FALSE;
        $output['message'] = 'Data not found for this requestee';
      }
    }
    else{
      $output['success'] = FALSE;
      $output['message'] = 'Requstee user can\'t be null';
    }
  }
  else{
    $output['success'] = FALSE;
    $output['message'] = 'Company id can\'t be null';
  }
  drupal_json_output($output);
  drupal_exit();
}
/*
 * function for display user m6id info
 */
function app_m6id_user_m6id_info(){
  if(isset($_REQUEST['companyNid']) && !empty($_REQUEST['companyNid'])){
    global $bucket, $awsAccessKey, $awsSecretKey;
    $credentials = new Credentials($awsAccessKey, $awsSecretKey);
    $s3Client = S3Client::factory(array(
      'credentials' => $credentials
    ));
    $company_id = $_REQUEST['companyNid'];
    $user_id = $_REQUEST['user_id'];
    $requestUser = user_load($user_id);
    $CheckForCompany = node_load($company_id);
    $mainData = array();
    if(!empty($requestUser)){      
      $user_picture = (isset($requestUser->field_user_profile_photo['und']) ? file_create_url($requestUser->field_user_profile_photo[LANGUAGE_NONE][0]['uri']) : '');
      $jobtitletid = (isset($requestUser->field_job_titles['und']) &&  isset($requestUser->field_job_titles['und']['0']['target_id']) && !empty($requestUser->field_job_titles['und']['0']['target_id'])) ? $requestUser->field_job_titles['und']['0']['target_id'] : '';
      $designation = '';
      if(!empty($jobtitletid)) {
        $jobterm = taxonomy_term_load($jobtitletid);
        $designation = $jobterm->name;
      }
      $checkCompanyDetail = array(
        'nid' => $CheckForCompany->nid,
        'title' => $CheckForCompany->title,
        'logo' => (isset($CheckForCompany->field_logo['und']) && !empty($CheckForCompany->field_logo['und'][0]['uri'])) ? $CheckForCompany->field_logo['und'][0]['uri'] : '',
        'type' => $CheckForCompany->field_type_of_company['und'][0]['value'],
      );
      $ob_nid = get_user_onboarding_nid($requestUser->uid);
      $onboardingnode = node_load($ob_nid);
      $m6idcredentials = $onboardingnode->field_onbarding_credentials['und'][0]['value'];
      $query = db_select('node','cnode');
      $query->join('og_membership','og','og.gid=cnode.nid AND og.entity_type=:EntityType AND og.group_type=:GroupType',array(':EntityType'=>'user',':GroupType'=>'node'));
      $query->join('field_data_field_type_of_company','ind','ind.entity_id=cnode.nid');
      $query->leftjoin('m6connect_onboarding_colleagues_status','ocs','ocs.company_nid=cnode.nid AND ocs.user_uid=:UserUid', array('UserUid'=>$requestUser->uid));
      $query->leftjoin('m6connect_onboarding_employee_types','oet','oet.id=ocs.employee_type');
      $query->leftjoin('field_data_field_logo','flo','flo.entity_id=cnode.nid');
      $query->leftjoin('file_managed','fm','fm.fid=field_logo_fid');
      $query->fields('cnode',array('nid','title'));
      $query->fields('ocs',array('status'));
      $query->fields('fm',array('uri'));
      $query->fields('oet',array('employee_type'));
      $query->fields('ocs',array('employee_id'));
      $query->condition('og.etid',$requestUser->uid);
      $query->condition ( 'ind.field_type_of_company_value','company','=');
      if($print){
        $query->condition ( 'cnode.nid',$CheckForCompany->nid,'=');
      }
      $query->orderBy('cnode.nid');
      $result = $query->execute()->fetchAll();
      if($result && !empty($result) && is_numeric($ob_nid)){
        $statusValues = array(0=>'Rejected',1=>'Approved',2=>'Pending');
        $companyData = $verticalData = array();$i = 0;
        foreach($result as $delta => $dataObj){
          $companyData[$i]['m6id'] = $requestUser->field_m6id['und'][0]['value'];
          $companyData[$i]['type_title'] = '';
          $companyData[$i]['user_title'] = ucwords($requestUser->realname);
          $companyData[$i]['user_picture'] = $user_picture;
          $companyData[$i]['designation'] = $designation;
          $companyData[$i]['requestee_companyname'] = ucwords($dataObj->title);
          $companyData[$i]['status'] = (isset($statusValues[$dataObj->status])) ? $statusValues[$dataObj->status]:'Pending';
          if($CheckForCompany->nid == $dataObj->nid){
            $checkCompanyDetail['status'] = 'Pending';
            if(is_numeric($dataObj->status) && in_array($dataObj->status, array(0,1,2))){
              $checkCompanyDetail['status'] = $statusValues[$dataObj->status];  
            }  
          }
          $companyLogo = '';
          if(!empty($dataObj->uri)){
            $bannerUrl = str_replace("private:/", "s3fs-private", $dataObj->uri);
            $companyLogo = $s3Client->getObjectUrl($bucket, $bannerUrl, '+1day');
          }
          $companyData[$i]['companyLogo'] = $companyLogo;
          $companyData[$i]['employee_type'] = ($dataObj->employee_type) ? $dataObj->employee_type : 'EMPLOYEE';
          $companyData[$i]['requester_companyname'] = ucwords($dataObj->title);
          $companyData[$i]['badgeId'] = (!empty($dataObj->employee_id) ? $dataObj->employee_id : '');
          $companyData[$i]['credential'] = '';
          $companyData[$i]['ob_expires'] = '';
          $companyData[$i]['presentedby'] = '';
          $companyData[$i]['rating'] = '';
          $i++;
        }
        // this function used to more slider data
        $bedgeSlide = appOnboarding_user_roster_badge_slide($requestUser->uid);
        $statusClasses = array(0=>'bg-warning',1=>'bg-success',3=>'bg-warning',2=>'bg-danger');
        $statusTexts = array(0=>'Pending',1=>'Approved',2=>'Rejected',3=>'Pending');
        $slideNumber = 1;
        if(!empty($bedgeSlide)){
          foreach ($bedgeSlide as $key => $dataObj) {
            $companyData[$i]['m6id'] = $requestUser->field_m6id['und'][0]['value'];
            $companyData[$i]['type_title'] = '';
            $companyData[$i]['user_title'] = ucwords($requestUser->realname);
            $companyData[$i]['user_picture'] = $user_picture;
            $companyData[$i]['designation'] = $designation;
            $companyData[$i]['requestee_companyname'] = ucwords($dataObj->requestee_company_title);
            $companyData[$i]['status'] = $statusTexts[$dataObj->requster_status];
            $companyLogo = '';
            if(!empty($dataObj->company_uri)){
              $bannerUrl = str_replace("private:/", "s3fs-private", $dataObj->company_uri);
              $companyLogo = $s3Client->getObjectUrl($bucket, $bannerUrl, '+1day');
            }
            $companyData[$i]['companyLogo'] = $companyLogo;
            $companyData[$i]['employeeType'] = (!empty($dataObj->employee_type_name))?$dataObj->employee_type_name:'EMPLOYEE';
            $companyData[$i]['requester_companyname'] = ucwords($dataObj->requester_company_title);
            $companyData[$i]['badgeId'] = '';
            $companyData[$i]['credential'] = '';
            $companyData[$i]['ob_expires'] = '';
            $companyData[$i]['presentedby'] = '';
            $companyData[$i]['rating'] = '';
            $i++;
          }
        }
        $mainData['companyData'] = $companyData;
        $j = 0;
        // vertical slider data starts
        $verticalCredentialData = appOnboarding_user_profile_m6id_credentials($requestUser,$mainData['designation']);
        if(!empty($verticalCredentialData)){
          foreach ($verticalCredentialData as $key => $credata) {
            $verticalData[$j]['m6id'] = $requestUser->field_m6id['und'][0]['value'];
            $verticalData[$j]['type_title'] = 'Credentials';
            $verticalData[$j]['user_title'] = ucwords($requestUser->realname);
            $companyLogo = '';
            if(!empty($credata->uri)){
              $bannerUrl = str_replace("private:/", "s3fs-private", $credata->uri);
              $companyLogo = $s3Client->getObjectUrl($bucket, $bannerUrl, '+1day');
            }            
            $verticalData[$j]['user_picture'] = $companyLogo;
            $verticalData[$j]['designation'] = $designation;            
            $credential = $credata->field_title_name_of_credential_value;            
            $Presentedby = $credata->field_received_presented_by_value;
            if(!empty($credential)){        
              $verticalData[$j]['status'] = (strlen($credential) > 30) ? substr($credential, 0, 27) . '...' : $credential;
            }
            $verticalData[$j]['ob_expires'] = date('m/d/Y', $credata->field_ob_expires_value);
            if(!empty($Presentedby)){         
              $verticalData[$j]['presentedby'] = (strlen($Presentedby) > 30) ? substr($Presentedby, 0, 27) . '...' : $Presentedby;
            }
            $verticalData[$j]['requestee_companyname'] = '';
            $verticalData[$j]['companyLogo'] = '';
            $verticalData[$j]['employeeType'] = '';
            $verticalData[$j]['requester_companyname'] = '';
            $verticalData[$j]['badgeId'] = '';
            $verticalData[$j]['rating'] = '';
            $j++;
          }
        }
        
        //vertical slider skillset data
        $skillData = array();
        $skillquery = db_select('m6connect_user_skill_set', 'ssd');
        $skillquery->fields('ssd',array('Id','skill_uid','skill_title','skill_year','skill_rating'));
        $skillquery->condition('ssd.skill_uid', $requestUser->uid);
        $skillrecord = $skillquery->execute()->fetchAll();
        if(!empty($skillrecord)){
          $skillRecord = array();$k = 0;
          foreach($skillrecord as $skillresult) {
            $verticalData[$j]['m6id'] = $requestUser->field_m6id['und'][0]['value'];
            $verticalData[$j]['type_title'] = 'Skill sets';
            $verticalData[$j]['user_title'] = ucwords($requestUser->realname);
            $verticalData[$j]['user_picture'] = $user_picture;
            $verticalData[$j]['designation'] = $designation;
            if($skillresult->skill_year){
              $verticalData[$j]['ob_expires'] = $skillresult->skill_year.'yrs';
            }
            if(!empty($skillresult->skill_title)){
              $string_skill_title = $skillresult->skill_title;
              $verticalData[$j]['status'] = (strlen($string_skill_title) > 30) ? substr($string_skill_title, 0, 27) . '...' : $string_skill_title;
            }
            if(!empty($skillresult->skill_rating)){
              $verticalData[$j]['rating'] = $skillresult->skill_rating;           
            }
            $verticalData[$j]['requestee_companyname'] = '';
            $verticalData[$j]['companyLogo'] = '';
            $verticalData[$j]['employeeType'] = '';
            $verticalData[$j]['requester_companyname'] = '';
            $verticalData[$j]['badgeId'] = '';
            $j++;
          }          
        }
        $mainData['credentialData'] = $verticalData;
      }
      if(!empty($result) && empty($ob_nid)){
        $userCompanyData = array();
        if($checkCompanyDetail['type'] =='company'){
          $userCompanyData['userCompanyName'] = $checkCompanyDetail['title'];
          $userCompanyData['companyName'] = $checkCompanyDetail['title'];
          $userCompanyData['companyId'] = $checkCompanyDetail['nid'];
          $userCompanyData['logo'] = $checkCompanyDetail['logo'];
        }
        else{
          $userCompanyData['companyName'] = 'Individual';
        }
      }
      else if(empty($result) && empty($ob_nid)){
        $userCompanyData['companyName'] = 'No Company';
      }
      else{
        $userCompanyData['companyName'] = 'No Company';
      }
      $mainData['userCompanyData'] = $userCompanyData;
    } 
    $output['success'] = TRUE;
    $output['message'] = 'Record found';
    $output['data'] = $mainData;   
  }
  drupal_json_output($output);
  drupal_exit();
}



/************** Helper functions ****************/

/*function m6app_get_onboarding_company_employess_details($company_id = null){
  if(!empty($company_id)){
    $query = db_select('users','u');
    $query->join('og_membership','og','og.etid=u.uid AND og.entity_type=:entityType',array(':entityType'=>'user'));
    $query->join('m6connect_og_membership_email','ogm','ogm.user_uid=u.uid AND og.gid=ogm.entity_id');
    $query->leftjoin('node','n','n.uid=u.uid AND n.type=:nodeType',array(':nodeType'=>'onboarding'));
    $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=u.uid AND m6id.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('field_data_field_first_name','fname','fname.entity_id=u.uid AND fname.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('field_data_field_last_name','lname','lname.entity_id=u.uid AND lname.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('m6connect_onboarding_colleagues_status','ous','ous.user_uid=u.uid AND ous.company_nid=:companyNid',array(':companyNid'=>$company_id));
    $query->fields('u',array('uid'));
    $query->addField('ogm','company_email','mail');
    $query->fields('n',array('nid'));
    $query->fields('og',array('gid'));
    $query->fields('m6id',array('field_m6id_value'));
    $query->fields('fname',array('field_first_name_value'));
    $query->fields('lname',array('field_last_name_value'));
    $query->fields('ous',array('employee_id','employee_type','health_screen','background_check','status','authorize','auth_mail_sent','auth_mail_timestamp'));
    $query->condition('og.gid',$company_id,'=');
    $query->condition('og.state',1,'=');    
    $result = $query->execute()->fetchAll();
    if(!empty($result)){
      $resData = array();
      $resData = $result;
      return $resData;
    }
    else{
      return array();
    }
  }
  else{
    return array();
  }
}

function m6app_get_onboarding_invited_company_employess_details($company_id = null){
  if(!empty($company_id)){
    $query = db_select('m6connect_onboarding_invited_employee','moie');
    $query->leftjoin('users','u','u.uid=moie.user_uid OR LOWER(TRIM(u.mail))=LOWER(TRIM(moie.email))');
    $query->leftjoin('node','n','n.uid=u.uid AND n.uid!=0 AND n.type=:nodeType',array(':nodeType'=>'onboarding'));
    $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=u.uid AND m6id.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('field_data_field_first_name','fname','fname.entity_id=u.uid AND fname.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->leftjoin('field_data_field_last_name','lname','lname.entity_id=u.uid AND lname.bundle=:userBundle', array(':userBundle'=>'user'));
    $query->fields('u',array('uid'));
    $query->addField('moie','email','mail');
    $query->fields('n',array('nid'));
    $query->fields('moie',array('employee_id','employee_type','health_screen','background_check','status'));
    $query->addField('moie','company_nid','gid');
    $query->addField('moie','id','invited_employee_id');
    $query->fields('m6id',array('field_m6id_value'));
    $query->addExpression('IFNULL(fname.field_first_name_value,moie.first_name)','field_first_name_value');
    $query->addExpression('IFNULL(lname.field_last_name_value,moie.last_name)','field_last_name_value');
    $query->condition('moie.company_nid',$company_id);
    $query->condition('moie.user_uid',0);
    $result = $query->execute()->fetchAll();
    if(!empty($result)){
      $resData = array();
      $resData = $result;
      return $resData;
    }
    else{
      return array();
    }
  }
  else{
    return array();
  }
}*/

function getM6idEmployeeTypeData($company_id){
  $empType = db_select('m6connect_onboarding_employee_types','et');
  $empType->fields('et',array('id', 'employee_type'));
  $empType->condition('company_nid',$company_id);
  $options = $empType->execute()->fetchAllKeyed(0,1);
  $i = 0;$data = array();$data = '';
  foreach ($options as $key => $value) {
    $data[$i]['id'] = $key;
    $data[$i]['value'] = $value;
    $i++;
  }
  return $data;
}

function appGetUserM6idStatus($cuser = ''){
  global $bucket, $awsAccessKey, $awsSecretKey;
  $mainData = array();
  if(!empty($cuser)){
    $query = db_select('node','cnode');
    $query->join('og_membership','og','og.gid=cnode.nid AND og.entity_type=:EntityType AND og.group_type=:GroupType',array(':EntityType'=>'user',':GroupType'=>'node'));
    $query->join('field_data_field_type_of_company','ind','ind.entity_id=cnode.nid');
    $query->leftjoin('m6connect_onboarding_colleagues_status','ocs','ocs.company_nid=cnode.nid AND ocs.user_uid=:UserUid', array(':UserUid'=>$cuser->uid));
    $query->leftjoin('field_data_field_logo','flo','flo.entity_id=cnode.nid');
    $query->leftjoin('file_managed','fm','fm.fid=field_logo_fid');
    $query->fields('cnode',array('nid','title'));
    $query->fields('ocs',array('status','authorize','auth_mail_sent'));
    $query->fields('fm',array('uri'));
    $query->condition('og.etid',$cuser->uid);
    $query->condition ( 'ind.field_type_of_company_value','company','=');
    $query->orderBy('cnode.nid');  
    $result = $query->execute()->fetchAll();
    $i=0;
    $credentials = new Credentials($awsAccessKey, $awsSecretKey);
    $s3Client = S3Client::factory(array(
      'credentials' => $credentials
    ));
    foreach($result as $cmpName => $dataObj){
      $statusText= 'Pending';
      $sts = -1;
      if(!empty($dataObj->uri)){
        $bannerUrl = str_replace("private:/", "s3fs-private", $dataObj->uri);
        $bannerImgUrl = $s3Client->getObjectUrl($bucket, $bannerUrl, '+1day');  
      }      
      $mainData[$i]['companyLogo'] = (!empty($bannerImgUrl) ? $bannerImgUrl : '');
      if(is_numeric($dataObj->status)){
        if($dataObj->status == 1){
          $statusText = 'Approved'; 
        }
        else if($dataObj->status == 2){
          $statusText = 'Pending';  
        }
        else{
          $statusText = 'Rejected'; 
        }
        $sts = $dataObj->status;
      }
      $actionbutton = '';
      $mainData[$i]['company_title'] = (!empty($dataObj->title) ? $dataObj->title : '');
      $mainData[$i]['status'] = (!empty($statusText) ? $statusText : '');
      $i++;
    }
  }
  return $mainData;
}
function appOnboarding_user_roster_badge_slide($userUid = ''){
  $query = db_select('m6connect_onboarding_request','mos');
  $query->join('field_data_field_m6id','m6id','m6id.entity_id=mos.requstee_user AND m6id.bundle=:M6IDBundle', array(':M6IDBundle'=> 'user'));
  $query->join('realname','rname','rname.uid=mos.requstee_user');
  $query->join('node','rnode','rnode.nid=mos.requester_company');
  $query->join('node','snode','snode.nid=mos.requstee_company');
  $query->join('node','pnode','pnode.nid=mos.requester_project');
  $query->leftjoin('m6connect_onboarding_employee_types','oet','oet.id=mos.employee_type');
  $query->leftjoin('field_data_field_user_profile_photo','pf','pf.entity_id=mos.requstee_user AND pf.bundle=:PFBundle', array(':PFBundle'=> 'user'));
  $query->leftjoin('field_data_field_logo','cl','cl.entity_id=mos.requester_company AND cl.entity_type=:CLEntityType',array(':CLEntityType'=>'node'));
  $query->leftjoin('file_managed','pfile','pfile.fid=pf.field_user_profile_photo_fid');
  $query->leftjoin('file_managed','clfile','clfile.fid= cl.field_logo_fid');
  $query->leftjoin('field_data_field_job_titles','job','job.entity_id=mos.requstee_user AND job.bundle=:JobBundle', array(':JobBundle'=> 'user'));
  $query->leftjoin('taxonomy_term_data','jterm','jterm.tid=job.field_job_titles_target_id');
  $query->distinct();
  $query->fields('mos', array('id','requster_status'));
  $query->addExpression('MIN(mos.id)', 'request_id');
  $query->addField('rname','realname','user_name');
  $query->addField('m6id','field_m6id_value','user_m6id');
  $query->addField('rnode','title','requester_company_title');
  $query->addField('snode','title','requestee_company_title');
  $query->addField('pnode','title','requester_project_title');
  $query->addField('jterm','name','user_job_title');
  $query->addField('pfile','uri','user_uri');
  $query->addField('clfile','uri','company_uri');
  $query->addField('oet','employee_type','employee_type_name');
  $query->condition('mos.requstee_user', $userUid); 
  $query->groupBy('requester_company');
  $result  = $query->execute()->fetchAll();
  return $result;
}
function appOnboarding_user_profile_m6id_credentials($user,$jobtitle){
  $credentialdata = array();
  $m6id = $user->field_m6id['und'][0]['value'];
  $m6Nid = get_user_onboarding_nid($user->uid);
  $query = db_select('field_data_field_onbarding_credentials','foc');
  $query->leftjoin('field_data_field_title_name_of_credential','ftnc','ftnc.entity_id = foc.field_onbarding_credentials_value');
  $query->leftjoin('field_data_field_ob_credential_type','fobt','fobt.entity_id = foc.field_onbarding_credentials_value');
  $query->leftjoin('field_data_field_ob_expires','exd','exd.entity_id = foc.field_onbarding_credentials_value');
  $query->leftjoin('field_data_field_ob_attach_image','obi','obi.entity_id = foc.field_onbarding_credentials_value');
  $query->leftjoin('field_data_field_received_presented_by','rpb','rpb.entity_id = foc.field_onbarding_credentials_value');
  $query->leftjoin('file_managed','fm','fm.fid=obi.field_ob_attach_image_fid');
  $query->fields('foc',array('field_onbarding_credentials_value'));
  $query->fields('ftnc',array('field_title_name_of_credential_value'));
  $query->fields('fobt',array('field_ob_credential_type_value'));
  $query->fields('exd',array('field_ob_expires_value'));
  $query->fields('obi',array('field_ob_attach_image_fid'));
  $query->fields('rpb',array('field_received_presented_by_value'));
  $query->addField('fm','uri');
  $query->condition('foc.entity_id',$m6Nid,'=');
  $result = $query->execute()->fetchAll();
  return $result;
}
?>