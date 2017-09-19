<?php
/*
 *Supply Chain Manger Settings Container
 */
function scm_user_database_configure_container(){
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements = array();
  $elements['scm-setting-menu-items'] = array(
    '#markup' => scm_setting_menu_links_content(),
    '#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
    '#suffix' => '</div><div class="add-new-record-scm-btn pull-right" id="add-new-record-button-custom"></div></div>',  
  );
  $elements['request-subtype-fieldset'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_user_database_settings_form')),
    '#prefix' => '<div class="row"><div class="col-sm-7 margin-bottom-10 main-scm-common-form"><div class="main-scm-common-form-userdbform thumbnail">', 
    '#suffix' => '</div></div>',
  );
  $elements['request-settings-userdatabase-import'] = array(
    '#type' => 'markup',
    '#markup' => render(drupal_get_form('scm_user_database_import_form')),
    '#prefix' => '<div class="col-sm-5 margin-bottom-10 main-scm-common-form"><div class="scm-user-database-import-form-outer thumbnail"><div class="padding-5 clearfix">',
    '#suffix' => '</div></div></div></div>',
  );
  $elements['scm-my-request-listing'] = array(      
    '#markup' => get_scm_user_database_settings_table_data(),
    '#prefix' => '<div class="clearfix"><div class="scm-my-request-listing" id="scm-my-request-table">',
    '#suffix' => '</div></div>',
  );
  return $elements;
}


function get_scm_user_database_datalist() {
  global $user; 
  global $company;   
  $query = db_select('m6connect_scm_settings_user_database', 'n');
  $query->fields('n', array('id'));
    $query->condition('n.companyID', $company->nid, '=');
    $query->condition('n.userID', $user->uid, '=');
    $result = $query->execute()->fetchAllKeyed(0,0);
  return $result;
}

/*
 *scm request type setting form
 */
function scm_user_database_settings_form($form, &$form_state) {
  $defaultValues = '';
  $getReqNodes = get_scm_user_database_datalist();
  $form['reset-callback'] = array(
    '#type' => 'select',
    '#options' => array(0=>0),
    '#attributes' => array('class'=> array('form-control','reset-callback')),
    '#ajax' => array(
      'callback'=> 'change_scm_user_database_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['get-user-database-settings'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#attributes' => array('class'=> array('form-control get-my-requests')),
    '#ajax' => array(
      'callback'=> 'change_scm_user_database_settings_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );
  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('form-control-main-container-scm-user-database padding-5')),
  );
  $form['scm-setting-user-database-node-nid']= array(
    '#type' => 'hidden',
    '#title_display' => 'invisible',
    '#attributes' => array('class'=> array('scm-setting-user-database-node-nid')),  
  );
  $form['main-container']['scm-user-database-fname'] = array(
    '#title' => 'First Name',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-user-database-fname')),
    '#prefix' => '<div class="project-details-border clearfix"><div class="row"><div class="col-md-6 col-sm-6 col-xs-12">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['main-container']['scm-user-database-lname'] = array(
    '#title' => 'Last Name',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-user-database-lname')),
    '#prefix' => '<div class="col-md-6 col-sm-6 col-xs-12">',
    '#suffix' => '</div></div>',
  );
  $form['main-container']['scm-user-database-email'] = array(
    '#title' => 'Email',
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control','workflow-auto','scm-user-database-email')),
    '#prefix' => '<div class="scm-user-database-email-userdb margin-top-10 clearfix">',
    '#suffix' => '</div>',
    '#required' => TRUE,
  );
  $form['main-container']['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    //'#validate' => array('project_scm_my_request_validate'),
    '#submit' => array('scm_user_database_settings_form_submit_callback'),
    '#attributes' => array('class'=>array('scm-user_database_settings-custom-btn')),
    '#prefix' => '<div class="custom-action-button-div margin-top-10 clearfix" for="closed">',
  );
  $form['main-container']['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button-schedule">',
    '#suffix' => '</div></div>',
  );
  return $form;
}

/*
 * Ajax submit callback for 
 * Submitting request type setting form
 */
function scm_user_database_settings_form_submit_callback($form, &$form_state) { //pre($form_state['values'],1);
  if(form_get_errors()) {
    return $form;
  }
  $login_mail = $form_state['values']['scm-user-database-email'];
  if(!valid_email_address($login_mail)){
     form_set_error('User Email','Invalid Email Address Formate');
    return $form;
  } 
  global $user; 
  global $company;   
  $formVal = $form_state['values'];

    $chkquery = db_select('m6connect_scm_settings_user_database', 'n');
    $chkquery->fields('n', array('id'));
    $chkquery->condition('n.companyID', $company->nid, '=');
    $chkquery->condition('n.email', $formVal['scm-user-database-email'], '=');
    $chkqueryresult = $chkquery->execute()->fetchObject();

  if(!empty($chkqueryresult)){  
     form_set_error('Check Email','User Already Exist');
    return $form;
  }  
  
  $userdata['fristname'] = $formVal['scm-user-database-fname'];
  $userdata['lastname'] = $formVal['scm-user-database-lname'];
  $userdata['email'] = $formVal['scm-user-database-email'];
  $userdata['companyID'] = $company->nid;
  $userdata['userID'] = $user->uid;
  $userdata['updated'] = time();
  if(isset($formVal['scm-setting-user-database-node-nid']) && !empty($formVal['scm-setting-user-database-node-nid'])) {
   $userdata['id'] = $formVal['scm-setting-user-database-node-nid'];
    $savestatus = 'updated';
  } else {
    $userdata['created'] = time(); 
    $savestatus = 'save';
  }  
  insert_update_scm_user_database_settings($userdata);
  drupal_set_message('User - '.$userdata['fristname'].' '.$userdata['lastname'].' has been '.$savestatus.'.');
}
 
function insert_update_scm_user_database_settings($userdata) {
  if(!empty(user_load_by_mail($userdata['email']))) {
       $userdata['UUID'] = user_load_by_mail($userdata['email'])->uid;
    } else {
      $new_user = array(
        'name' => $userdata['fristname'].' '.$userdata['lastname'],
        'mail' => $userdata['email'],
        'status' => 0,
        'init' => $userdata['email'],
        'roles' => array(
          DRUPAL_AUTHENTICATED_RID => 'authenticated user',
        ),
      );
      $accuser = user_save('', $new_user);
      $userdata['UUID'] = $accuser->uid;
    }
  if($userdata['id']) {
    // if(!empty(user_load_by_mail($userdata['email']))) {
    //    $userdata['UUID'] = user_load_by_mail($userdata['email'])->uid;
    // }
    db_update('m6connect_scm_settings_user_database')
    ->fields($userdata)
    ->condition('id', $userdata['id'], '=')
    ->execute();
  } else  {
    
    $inserted_db = db_insert('m6connect_scm_settings_user_database')->fields($userdata)->execute();
  }
}





function change_scm_user_database_settings_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element']; 
  if($form_state['triggering_element']['#name']=='get-user-database-settings') {
    if(!empty($triggeringElement['#value'])) {
    $myReqNode = get_scm_user_database_data($triggeringElement['#value']);  
    $storage_project = array(
      'scm-user-database-fname' => isset($myReqNode->fristname)?$myReqNode->fristname:'',
      'scm-user-database-lname' => isset($myReqNode->lastname)?$myReqNode->lastname:'',
      'scm-user-database-email' => isset($myReqNode->email)?$myReqNode->email:'',
    );        
    $commands[] = ajax_command_invoke("input.scm-setting-user-database-node-nid", 'val',array($myReqNode->id));
    $commands[] = ajax_command_invoke("input.scm-user-database-fname", 'val',array($storage_project['scm-user-database-fname']));
    $commands[] = ajax_command_invoke("input.scm-user-database-lname", 'val',array($storage_project['scm-user-database-lname']));
    $commands[] = ajax_command_invoke("input.scm-user-database-email", 'val',array($storage_project['scm-user-database-email']));
    $commands[] = ajax_command_invoke("input.scm-user-database-ischainmanager", 'val',array($myReqNode->is_chain_manager));
    if($myReqNode->is_chain_manager==1){
      $commands[] = ajax_command_invoke("input.scm-user-database-ischainmanager", 'attr',array('checked', 'true'));
    }
    if($myReqNode->is_material_manager){
      $commands[] = ajax_command_invoke("input.scm-user-database-ismatarialmanager", 'val',array($myReqNode->is_material_manager));
      $commands[] = ajax_command_invoke("input.scm-user-database-ismatarialmanager", 'attr',array('checked', 'true'));
    }
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_user_database_settings_table_data());  
    }
    $commands[] = ajax_command_invoke("select.scm-user-database-category", 'val',array($myReqNode->category));
  } else {
    $commands[] = ajax_command_invoke("input.scm-setting-user-database-node-nid", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-user-database-fname", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-user-database-lname", 'val',array(''));
    $commands[] = ajax_command_invoke("input.scm-user-database-email", 'val',array(''));
    $commands[] = ajax_command_html("#scm-my-request-table", get_scm_user_database_settings_table_data()); 
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}


function scm_user_database_import_form($form, &$form_state) {

  $mod_path = drupal_get_path('module', 'm6connect_scm');
  $htmp_filetext = '<div class="clearfix">' . l(t('Download Sample Here'), $mod_path . '/includes/settings/sample user name import.csv', array('attributes' => array('class' => array('form-submit', 'text-white')))) . '</div><br/>';
  $htmp_filetext .= "<p>This tool will attempt to import CSV data";

  $form['get_impoert_file'] = array(
    '#markup' => $htmp_filetext,
  );

  $form['#attributes'] = array(
    'enctype' => 'multipart/form-data'
  );
  
  $form['scm-user-db-csvupload'] = array( 
    '#title' => t('CSV File'),
    '#type'  => 'file',
    '#description' => ($max_size = parse_size(ini_get('upload_max_filesize'))) ? t('Due to server restrictions, the <strong>maximum upload file size is !max_size</strong>. Files that exceed this size will be disregarded.', array('!max_size' => format_size($max_size))) : '',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Start Import'),
  );
  $form['#validate'] = array(
    'scm_userdatabase_setting_import_validate_fileupload',
  );
  return $form ;
}

function scm_userdatabase_setting_import_validate_fileupload(&$form, &$form_state) {

  $validators = array(
    'file_validate_extensions' => array( 'csv' ),
  );
  if ( $file = file_save_upload('scm-user-db-csvupload', $validators, "public://", FILE_EXISTS_REPLACE) ) {
    $form_state['values']['scm-user-db-csvupload'] = $file->destination;       
  }
  else {
    form_set_error('scm-user-db-csvupload', t('Unable to copy upload file to !dest', array('!dest' => $destination)));
  }
}

function scm_user_database_import_form_submit(&$form, &$form_state) {
  if (isset($form_state['values']['scm-user-db-csvupload'])) {
    $batch = array(
      'title' => t('Importing CSV ...'),
      'operations' => array(),
      'init_message' => t('Commencing'),
      'progress_message' => t('Processed @current out of @total.'),
      'error_message' => t('An error occurred during processing'),
      'finished' => 'scm_user_database_import_finished',
    );
    if ($handle = fopen($form_state['values']['scm-user-db-csvupload'], 'r')) {
      $batch['operations'][] = array('_scm_user_database_import_remember_filename', array($form_state['values']['csvupload'])) ;
      $line_count = 1;
      $first = 'none';
      while ($line = fgetcsv($handle)) {
         if ($first=='start') {
          $batch['operations'][] = array('_scm_user_database_import', array($line));
          }
         $first = 'start';
      }
      fclose($handle);
    }
    batch_set($batch);
  }
  else {
    // If we do not have a file, then showing warning.
    drupal_set_message(t('No file found for uploading, please try again!'), 'warning', FALSE);
  }
}

