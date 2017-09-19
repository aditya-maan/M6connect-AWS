<?php
use Aws\Common\Aws;
use Aws\S3\S3Client;
use Aws\Common\Credentials\Credentials;
global $bucket, $awsAccessKey, $awsSecretKey;
$bucket = 'dev.repo.m6connect.com';
$awsAccessKey = 'AKIAJZCVB5B62KPYTLFA';
$awsSecretKey = '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';
/**
 * @file Handle user's login, register and forgot password on APP.
 */

/**
 * Checking user's login credentials.
 * Returns a JSON object of user projects and other details.
 */
function appuser_login() {
  $output = array(
    'success' => FALSE,
    'message' => t('Either Email/Username or Password not provided.'),
  );

  // If either of the email or password is not received then returning error.]
  if (empty($_REQUEST['email']) || empty($_REQUEST['pass'])) {
    drupal_json_output($output);
    drupal_exit();
  }
  
  $email = $_REQUEST['email'];
  $pass = $_REQUEST['pass'];

  $output['message'] = t('Provided Username and Password does not match any records.');

  $uid = _user_authenticate($email, $pass);
  if (!$uid) {
    // If the user does not authenticate, then return error.
    drupal_json_output($output);
    drupal_exit();
  }

  $user = user_load($uid);
  $firstname = '';
  $middlename = '';
  $lastname = '';
  $picture = '';
  $dob = '';

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

  if (!empty($user->field_date_of_birth['und'][0]['value'])) {
    $dob = $user->field_date_of_birth['und'][0]['value'];
  }
  //$companies_detail = m6connect_misc_get_user_all_companies($uid);
  $currentCompanyId = variable_get('company_set_'.$uid);
  // if empty $currentCompanyId then user not login with any company and it's individual company becomes it's main company
  if(empty($currentCompanyId)){
    $getUserCompany = m6connect_misc_get_user_all_companies(13931);
    $currentCompanyId = $getUserCompany->nid;
  }
  $currCmpNode = node_load($currentCompanyId);
  $cmpLogoUri = $currCmpNode->field_logo['und'][0]['uri'];
  $cmpLogo = '';
  if(!empty($cmpLogoUri)){
    global $bucket, $awsAccessKey, $awsSecretKey;
    $credentials = new Credentials($awsAccessKey, $awsSecretKey);
    $s3Client = S3Client::factory(array(
      'credentials' => $credentials
    ));
    $thumbUrl = str_replace("private:/", "s3fs-private", $cmpLogoUri);
    $cmpLogo = $s3Client->getObjectUrl($bucket, $thumbUrl, '+1day');
  }
  $output = array(
    'success' => TRUE,
    'message' => 'User login successfull!',
    'online' => _get_user_online_status($uid),
    'user_id' => $uid,
    'email' => $user->mail,
    'username' => $user->name,
    'realname' => trim($realname),
    'time_zone' => $user->timezone,
    'user_image' => $picture,
    'dob' => $dob,
    'companyNid' => $currentCompanyId,
    'companyPic' => $cmpLogo,
    'services' => user_services_access_data($uid, $currentCompanyId, 0),
  );

  drupal_json_output($output);
  drupal_exit();
}

/**
 * Function to handle forgot password for user.
 */
function appuser_forgot_password() {
  $output = array(
    'success' => FALSE,
    'message' => t('Email not received.'),
  );
  // If email is not received then returning error.
  if (!isset($_REQUEST['email'])) {
    drupal_json_output($output);
    drupal_exit();
  }

  $mail = $_REQUEST['email'];

  // Trying to load user by email. If user loaded then processing further else
  // returning error.
  $output['message'] = t('Provided Email address does not match in our system.');
  $account = user_load_by_mail($mail);

  if (!$account) {
    drupal_json_output($output);
    drupal_exit();
  }

  // If mail is found, then sending mail.
  $output['message'] = t('Password reset mail sent successfully.');
  $output['success'] = TRUE;
  global $language;

  _user_mail_notify('password_reset', $account, $language);

  drupal_json_output($output);
  drupal_exit();
}

/**
 * Menu callback for appuser/register.
 */
function appuser_register() {
  $output = array(
    'success' => FALSE,
    'message' => t('Registration failed due to Inappropriate data.'),
  );

  if (empty($_REQUEST['dob']) || empty($_REQUEST['email']) || empty($_REQUEST['first_name']) || empty($_REQUEST['last_name']) || empty($_REQUEST['gender']) || empty($_REQUEST['mobile_code']) || empty($_REQUEST['mobile_number']) || empty($_REQUEST['pass'])) {
    // If any of the above info is not available, then returning error.
    drupal_json_output($output);
    drupal_exit();
  }

  $user_exists = user_load_by_mail($_REQUEST['email']);
  if ($user_exists) {
    $output['message'] = t('The e-mail address !mail is already registered with M6Connect.', array('!mail' => $_REQUEST['email']));
    drupal_json_output($output);
    drupal_exit();
  }

  if (!valid_email_address($_REQUEST['email'])) {
    $output['message'] = t('The e-mail address !mail is not valid.', array('!mail' => $_REQUEST['email']));
    drupal_json_output($output);
    drupal_exit();
  }

  // If all the validations are passed, then proceeding further.
  $output['message'] = t('Some problem occured in creating new user. Please try again.');
  $mobile = trim($_REQUEST['mobile_code']) . trim($_REQUEST['mobile_number']);
  if (strpos($mobile, '+') === FALSE) {
    $mobile = '+' . $mobile;
  }
  $dob = $_REQUEST['dob'];
  $dob_timestamp = strtotime($dob);
  $dob_rss = date('Y-m-d H:i:s', $dob_timestamp);


  $fields = array(
    'name' => $_REQUEST['email'],
    'mail' => $_REQUEST['email'],
    'pass' => $_REQUEST['pass'],
    'status' => 1,
    'init' => $_REQUEST['email'],
    'roles' => array(
      DRUPAL_AUTHENTICATED_RID => 'authenticated user',
      4 => 'Free Company Membership',
    ),
    'field_first_name' => array(
      'und' => array(
        0 => array(
          'value' => $_REQUEST['first_name'],
        ),
      ),
    ),
    'field_last_name' => array(
      'und' => array(
        0 => array(
          'value' => $_REQUEST['last_name'],
        ),
      ),
    ),
    'field_gender' => array(
      'und' => array(
        0 => array(
          'value' => $_REQUEST['gender'],
        ),
      ),
    ),
    'field_phone' => array(
      'und' => array(
        0 => array(
          'value' => $mobile,
        ),
      ),
    ),
    'field_date_of_birth' => array(
      'und' => array(
        0 => array(
          'value' => $dob_rss,
        ),
      ),
    ),
  );

  if (!empty($_REQUEST['middle_name'])) {
    $fields['field_middle_name']['und'][0]['value'] = $_REQUEST['middle_name'];
  }
  if (!empty($_REQUEST['time_zone'])) {
    $fields['timezone'] = $_REQUEST['time_zone'];
  }

  //the first parameter is NULL so a new user is created
  $account = user_save(NULL, $fields);
  if ($account->uid) {
    // If account is saved successfully.
    $output['success'] = TRUE;
    $output['message'] = t('Account created successfully.');
    // Changing the username based on uid and mail.
    $mail = $account->mail;
    $mail_exploded = explode('@', $mail);
    $mail_part = $mail_exploded[0];
    $new_user_name = $mail_part . '_' . $account->uid;
    $edit = array('name' => $new_user_name);
    $account_new = user_save($account, $edit);
    // create individual company - og group
    $newnode_name_o1 = $account->field_first_name['und'][0]['value'];
    $newnode_name_o2 = $account->field_last_name['und'][0]['value'];
    $node = new stdClass();
    $node->type = 'organization';
    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;
    $node->title = $newnode_name_o1 . ' ' . $newnode_name_o2;
    $node->field_company_email['und'][0]['email'] = $account->mail;
    $node->field_type_of_company['und'][0]['value'] = 'individual';
    $node->field_show_company_in_search['und'][0]['value'] = 0;
    $node->field_owner_name['und'][0]['value'] = $newnode_name_o1 . ' ' . $newnode_name_o2;
    $node->uid = $account->uid;
    $node = node_submit($node);
    node_save($node);

    og_group('node', $node->nid, array(
      "entity type" => "user",
      "entity" => $account,
      "membership type" => OG_MEMBERSHIP_TYPE_DEFAULT,
    ));
    // Assign M6ID Company
    $userEmail = trim($account->mail);
    $userEmail = strtolower($userEmail);
    $m6idQuerry = db_select('m6connect_onboarding_invited_employee','moie');
    $m6idQuerry->join('node','cnode','cnode.nid=moie.company_nid');
    $m6idQuerry->fields('moie');
    $m6idQuerry->addField('cnode','title','company_title');
    $m6idQuerry->condition('moie.user_uid',0);
    $m6idQuerry->where('LOWER(TRIM(moie.email))=:userEmail', array(':userEmail'=>$userEmail));
    $m6idInvited = $m6idQuerry->execute()->fetchAll();
    if(!empty($m6idInvited)){
      $_SESSION['m6id_new_company_join_flag'] = 1;
      drupal_register_shutdown_function('update_user_m6id_merbership', $account->uid,$m6idInvited);
    }
    /*     * ***************Connection Category create ***start************ */
    $new_categorys = array('Family','Friends', 'Business Accociates', 'Acquaintances', 'Clients', 'Prospects', 'Sales Associates');
    foreach ($new_categorys as $nc_value) {
      $node = new stdClass();
      $node->type = 'connection_categories';
      node_object_prepare($node);
      $node->language = LANGUAGE_NONE;
      $node->title = $nc_value;
      $node->field_default_category['und'][0]['value'] = 1;
      $node = node_submit($node);
      $node->uid = $account->uid;
      $node->status = 1;
      node_save($node);
    }
    /** ***************connection category create ***end************ */
  }
  drupal_json_output($output);
  drupal_exit();
}















/**********************************************************
**************** Helper functions *************************
**********************************************************/
// Please make helper functions in this section and main function above it.

/**
 * Helper function to check user authentication.
 */
function _user_authenticate($email, $password, &$output) {
  $uid = FALSE;
  if (!empty($email) && strlen(trim($password)) > 0) {
    $account = user_load_by_name($email);
    if (!$account) {
      $account = user_load_by_mail($email);
    }
    if ($account) {
      require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
      if (user_check_password($password, $account)) {
        // Successful authentication.
        $uid = $account->uid;

        // Update user to new password scheme if needed.
        if (user_needs_new_hash($account)) {
          user_save($account, array('pass' => $password));
        }
      }
    }
  }
  return $uid;
}

/**
 * Helper function to get user online status statically.
 */
function _get_user_online_status($uid) {
  $users = &drupal_static(__FUNCTION__);
  if (!isset($users)) {
    $users = array();

    $interval = REQUEST_TIME - variable_get('user_block_seconds_online', 900);

    $query = db_select('sessions', 's')
      ->fields('s')
      ->condition('uid', $uid)
      ->condition('timestamp', $interval, '>')
      ->execute()
      ->rowCount();
    $users[$uid] = $query > 0 ? 1 : 0;
  }
  if (!isset($users[$uid])) {
    $interval = REQUEST_TIME - variable_get('user_block_seconds_online', 900);

    $query = db_select('sessions', 's')
      ->fields('s')
      ->condition('uid', $uid)
      ->condition('timestamp', $interval, '>')
      ->execute()
      ->rowCount();
    $users[$uid] = $query > 0 ? 1 : 0;
  }

  return $users[$uid];
}