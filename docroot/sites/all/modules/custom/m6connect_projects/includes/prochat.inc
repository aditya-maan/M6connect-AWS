<?php
/**
 * @file include file
 */

/**
 * Menu callback for prochat
 */
function custom_prochat_section_layout(){
  drupal_add_js('sites/all/libraries/emojione/emojionearea.js');
  drupal_add_css('sites/all/libraries/emojione/emojionearea.min.css');

  $prochat_group_list = prochat_group_list(); 
  $prochat_file_upload = drupal_render(drupal_get_form('prochat_file_attached_form'));

  $prochat_member_chat_new ='';
  $prochat_multiple_screen_layout = '';
  if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
    $prochatRoom_count = count($_SESSION['Prochat'][0]);
    if ($prochatRoom_count > 2) {
      $prochat_multiple_screen_layout = 'prochat-multiple-screen-layout';
    }
    $prosessionValue = array_values($_SESSION['Prochat'][0]);
    $isEven = ($prochatRoom_count % 2 == 0) ? 1 : 0;
    $rowscount = ($isEven==1) ? ($prochatRoom_count / 2) : (($prochatRoom_count - 1) / 2);

    $arr = array();
    $count = 0;
    foreach ($prosessionValue as $delta => $svalue) {
      if ($delta != 0 && $delta % 2 == 0) {
        $count++;
      }
      if (!isset($arr[$count])) {
        $arr[$count] = '';
      }
      $divClass = 'col-md-6 col-sm-6 col-xs-6 padding-5 prochat-multiple-chat';
      if ($rowscount == $count) {
       $divClass = 'col-md-12 col-sm-12 col-xs-12 padding-5 prochat-single-chat';  
      }
      $arr[$count] .= '<div class="'.$divClass.'">'.drupal_render(drupal_get_form('prochat_member_chat_form_'.$svalue ,$svalue)).drupal_render(drupal_get_form('prochat_file_attached_form_'.$svalue ,$svalue)).'</div>';
    }

    $prochat_member_chat_new = '<div class="prochat-screen '.$prochat_multiple_screen_layout.'"><div class="margin-5 row">'.implode('</div><div class="margin-5 row">',$arr).'</div></div>';
  }
  else {
    $prochat_member_chat_new = drupal_render(drupal_get_form('prochat_group_section_form'));
  }

  $output = '';
  $output .= '<div class="row margin-5 middle_content">';
  
    $output .= '<div class="col-md-2 col-sm-12 col-xs-12 padding-5">';
    $output .='<div class="text-center"><h3>Coming Soon! <b>M6drive</b></h3></div>';
    $output .= '<div class="middle_one company-profile-navigation clearfix">
                    <div class="middle_one_top clearfix">
                      <div class="region region-middle-one-top">
             <div style="display:none">'.l('<i class="fa fa-refresh" aria-hidden="true"></i>','/prochat/chat/refresh/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'pd-chat-refresh use-ajax'))).'</div>
             
            </div>
          </div>
          </div>';
  $output .= '</div>';  
  
  $output .= '<div class="col-md-8 col-sm-12 col-xs-12 padding-5 middle-two-main-section">';
    $output .= '<div class="middle_two clearfix">
                    <div class="middle_two_inner">
          
                    </div>
                    <div class="content_inner">   
            
           
              <div class="row margin-5">            
              <div class="padding-5 prochat-chatswitch-error"></div>
              <div class="prochat_project_list col-sm-3 col-md-3 col-xs-3 padding-5">
             '.$prochat_group_list.'
              </div>
              <div class="prochat_member_chat col-sm-9 col-md-9 col-xs-9 padding-5">
             
              '.$prochat_member_chat_new.'
              </div>              
            </div>
          </div>
          
          </div>';
          
  $output .= drupal_render(drupal_get_form('custom_prochat_delete_message_form'));
  $output .= '</div>';
  
  $output .= '<div class="col-md-2 col-sm-12 col-xs-12 padding-5 middle-three-main-section">
                <div class="text-center"><h3>Coming Soon! <b>M6drive</b></h3></div>
                  <div class="middle_three clearfix">
                    <div class="region region-middle-three">
            
                    </div>
          </div>
                </div>';

  $output .= '</div>';
  return $output; 
}

/**
 * Menu callback for prochat/%/%/%ctools_js
 */
function prochat_multiple_section($item, $action, $ajax = FALSE){
  ctools_include('ajax');
  $commands = array();

  if ($item == 'group') {
    if ($action == 'create' && $ajax == TRUE) {
      $group_create = drupal_render(drupal_get_form('prochat_group_section_form'));
      $commands[] = ajax_command_html('.prochat_member_chat', '');
      $commands[] = ajax_command_html('.prochat_member_chat', $group_create);     
    }
  }
  if ($item == 'switch') {
    if ($action == 'clear' && $ajax == TRUE) {
      unset($_SESSION['ProchatSwitch']);
      $ProchatGroupList = prochat_group_list();
      $commands[] = ajax_command_html('.project_dashboard_member_list', '');
      $commands[] = ajax_command_html('.project_dashboard_member_list', $ProchatGroupList);   
    }
  }
  if ($item == 'switch') {
    if ($action == 'home' && $ajax== TRUE) {
      $prochat_member_chat_new = prochat_chat_rendar();
      $commands[] = ajax_command_html('.prochat_member_chat', '');
      $commands[] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
      if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
        foreach ($_SESSION['Prochat'][0] as $key => $mapping_key) {
          $commands[] = mymodule_ajax_command_insertInEmoji('textarea#text-message-smilly-'.$mapping_key);  
        }
      }
    }
  }
  if ($item == 'chat') {
    if ($action == 'refresh' && $ajax== TRUE) {
      if (isset($_SESSION['ProchatSwitch'])) {
        $mapping_key = $_SESSION['ProchatSwitch'];
        $prochat_group_member = prochat_group_member($mapping_key);  
        $prochat_message = get_prochat_message($mapping_key);
      }
      $commands[] = ajax_command_html('#prochat_message_container', $prochat_message);    
    }
  }

  if ($item == 'chatswitch') {
    if (!empty($action) && $ajax== TRUE) {
      if (isset($action)) {
        //assign new session in prochat session
        if (!empty($_SESSION['Prochat'])) {
          $prochatRoom_count = count($_SESSION['Prochat'][0]);
          if ($prochatRoom_count < 4) {
            $hasProchatSession = $_SESSION['Prochat'][0];
            $newProchatSession = array($action => $action);
            $mergeProchatSession = array_merge($hasProchatSession , $newProchatSession);
            $_SESSION['Prochat'] = array(0 => $mergeProchatSession);
            $commands[] = ajax_command_html('.prochat-chatswitch-error','');
          }
          else {
            $commands[] = ajax_command_html('.prochat-chatswitch-error','<span class="change-action-box-error" style="font-size:15px">! Please close one chat screen.</span>');
          }
        }
        else { 
          $_SESSION['Prochat'][] = array($action=>$action);
        }

        //refarsh new prochat session 
        $prochat_member_chat_new = prochat_chat_rendar();
        $commands[] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
        if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
          foreach ($_SESSION['Prochat'][0] as $key => $mapping_key) {
            $commands[] = mymodule_ajax_command_insertInEmoji('textarea#text-message-smilly-'.$mapping_key);
          }
        }
      }
    }
  }
  if ($item == 'chatroomclear') {
    if (!empty($action) && $ajax== TRUE) {
      if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'][0])) {
        $ProchatSessionCount = count($_SESSION['Prochat'][0]);
        if ($ProchatSessionCount == 1) {
          if ($_SESSION['Prochat'][0][$action]) {
            unset($_SESSION['Prochat']);
          }
        }
        else {
        unset($_SESSION['Prochat'][0][$action]);
        }
        //refarsh new prochat session     
        $prochat_member_chat_new = prochat_chat_rendar();
        $commands[] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
        if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
          foreach ($_SESSION['Prochat'][0] as $key=>$mapping_key){
            $commands[] = mymodule_ajax_command_insertInEmoji('textarea#text-message-smilly-'.$mapping_key);
          }
        }
        $commands[] = ajax_command_html('.prochat-chatswitch-error','');
      }
    }
  }
  if ($item == 'groupinvite') {
    if (!empty($action) && $ajax== TRUE) {
      $group_invite = drupal_render(drupal_get_form('prochat_group_section_form','groupinvite',$action));
      $commands[] = ajax_command_html('.prochat_member_chat', $group_invite);
    }
  }
  if ($item == 'groupdelete') {
    if (!empty($action) && $ajax == TRUE) {
      if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'][0])) {
        $ProchatSessionCount = count($_SESSION['Prochat'][0]);
        if ($ProchatSessionCount == 1) {
          if ($_SESSION['Prochat'][0][$action]) {
            unset($_SESSION['Prochat']);
          }
        }
        else {
          unset($_SESSION['Prochat'][0][$action]);
        }
        prochat_group_delete($action);
        $prochat_member_chat_new = prochat_chat_rendar();
        $commands[] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
        $prochat_group_list = prochat_group_list();
        $commands[] = ajax_command_html('.prochat_project_list', $prochat_group_list);
        if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
          foreach ($_SESSION['Prochat'][0] as $key => $mapping_key) {
            $commands[] = mymodule_ajax_command_insertInEmoji('textarea#text-message-smilly-' . $mapping_key);
          }
        } 
      }
    }
  }
  if ($item == 'settings') {
    if ($action == 'deletemsg' && $ajax == TRUE) {
      $commands[] = ajax_command_css('ul.prochat-msgdelete-submit', array('display' => 'block'));
      $commands[] = ajax_command_css('span.delete-msg', array('display' => 'block'));
    }
  }
  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for prochat/groupleave/%/%ctools_js
 */
function prochat_groupsection_action_callback($action, $mappingkey, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'groupsection_action' => $action,
      'group_action_mappingkey' => $mappingkey,
      'title' => 'Confirm Leave Group',
    );
    $output = ctools_modal_form_wrapper('prochat_groupsection_action_box_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('prochat_groupsection_action_box_form', $action, $mappingkey);
}

/**
 * Form prochat_groupsection_action_box_form
 */
function prochat_groupsection_action_box_form($form, &$form_state, $action, $mappingkey) {
  global $user;
  if (!$action) {
    $groupsection_action = $form_state['groupsection_action'];
  }
  if (!$mappingkey) {
    $group_action_mappingkey = $form_state['group_action_mappingkey'];
  }

  $form['group_action_key'] = array(
    '#type' => 'hidden',
    '#value' => $group_action_mappingkey, 
  );
  $query = db_select('m6connect_prochat_group','mpg');
  $query->condition('mpg.mapping_key',$group_action_mappingkey,'=');
  $query->fields('mpg',array('group_uid','group_name'));
  $GadminGname = $query->execute()->fetchAllKeyed(0,1);
    
  if (isset($GadminGname) && !empty($GadminGname)) {
    $group_name = array_values($GadminGname);
    if ($GadminGname[$user->uid]) {
      $form['group_leave_message'] = array(
      '#type' => 'markup',
      '#title' => t('Confirm Leave Group'),
      '#markup' => '<div class="prochat-leave-action-msg">
              <p>Are you sure you want to leave this group?</p>
                          <p>'.$group_name[0].' must have at least one Administrator.</p> 
              <p>Please assign another member to be Administrator before leaving the Group.</p>
              </div>',  
      );
      $form['group_leave_member'] = array('#type' => 'value', '#value' => 'admin');
      $form['group_name'] = array('#type' => 'value', '#value' => $group_name[0]);
    }
    else {
      $form['group_leave_message'] = array(
      '#type' => 'markup',
      '#title' => t('Confirm Leave Group'),
      '#markup' => '<div class="prochat-leave-action-msg">
              <p>Are you sure you want to leave this group?</p> 
              <p>Press Confirm to exit and Continue to abort this operation.</p>
              </div>',  
      );
      $form['group_leave_member'] = array('#type' => 'value', '#value' => 'other');
    }
  }
  $form['groupsection_action_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm')
  );
  $form['groupsection_action_cancel']['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('group-delete-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#weight' => 10,
  );
  $form['group_leave_member_uid'] = array('#type' => 'value', '#value' => $user->uid);
  return $form;
}

/**
 * Submit handler for prochat_groupsection_action_box_form
 */
function prochat_groupsection_action_box_form_submit($form, &$form_state) {
  global $user;
  $values = $form_state['values'];
  if(isset($values['groupsection_action_submit']) && $values['groupsection_action_submit'] == 'Confirm'){
    if(isset($values['group_leave_member']) && $values['group_leave_member'] == 'other'){
      db_delete('m6connect_prochat_group_mapping')
        ->condition('mapping_key', $values['group_action_key'] , '=')
        ->condition('group_users', $values['group_leave_member_uid'] , '=')
        ->execute();
      if(isset($_SESSION['Prochat'])&& !empty($_SESSION['Prochat'][0])){
        $ProchatSessionCount = count($_SESSION['Prochat'][0]);
        if($ProchatSessionCount == 1){
          if($_SESSION['Prochat'][0][$values['group_action_key']]){
            unset($_SESSION['Prochat']);
          }         
        }else{
          unset($_SESSION['Prochat'][0][$values['group_action_key']]);
        }     
      }
    }
  }
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    if (isset($values['groupsection_action_submit']) && $values['groupsection_action_submit'] == 'Confirm') {
      if (isset($values['group_leave_member']) && $values['group_leave_member'] == 'other') {
        $prochat_member_chat_new = prochat_chat_rendar();
        $form_state['ajax_commands'][] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
        $prochat_group_list = prochat_group_list();
        $form_state['ajax_commands'][] = ajax_command_html('.prochat_project_list', $prochat_group_list);
        $form_state['ajax_commands'][] = mymodule_ajax_command_insertInEmoji('textarea#text-message-smilly-'.$values['group_action_key']);
      }
      if (isset($values['group_leave_member']) && $values['group_leave_member'] == 'admin') {
        $group_admin_assign = drupal_render(drupal_get_form('prochat_group_admin_assign_form',$values['group_name'],$values['group_action_key'],$values['group_leave_member_uid']));
        $form_state['ajax_commands'][] = ajax_command_html('.prochat_member_chat', $group_admin_assign);
      }
    }
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Helper function to get form for rendering.
 */
function prochat_group_admin_assign_form($form,&$form_state,$group_name,$action_key,$leave_member_uid) {
  $form['action_box_error']= array(
    '#markup' => '<div class="action-box-error"></div>',  
  );

  $form['prochat_group_admin_assign_header']= array(
    '#markup' => '<div class="switch-pd-project-list clearfix"><div class="pull-left">'.
      l('<i class="fa fa-ellipsis-h" aria-hidden="true"></i>','/prochat/switch/home/nojs', array('html'=>TRUE, 'attributes'=>array('class'=>'switch-home-pd-project-list-btn use-ajax'))).
      '</div><div class="pull-right">'.
      l('<i class="fa fa-pencil-square-o" aria-hidden="true"></i>','/prochat/group/create/nojs',array('html'=>TRUE, 'attributes'=>array('title'=>'Create Group','class'=>'switch-pd-project-list-btn use-ajax'))).'</div></div>', 
  );
  $form['group_admin_group_name'] = array(
    '#type' => 'value',
    '#value' => $group_name,
  );
  $form['group_admin_action_key'] = array(
    '#type' => 'value',
    '#value' => $action_key,
  );
  $form['group_admin_leave_member_uid'] = array(
    '#type' => 'value',
    '#value' => $leave_member_uid,
  );
  $form['prochat_group_admin_assign_header2']= array(
    '#markup' => '<div class="switch-pd-project-list clearfix"><div class="pull-left" style="color:#fff">'.$group_name.' group admin assign</div></div>', 
  );
  $form['prochat_group_admin_assign'] = array(
    '#type' => 'submit',
    '#value' => decode_entities('&#xf061;'),
    '#executes_submit_callback' => FALSE,
    '#attributes'=> array('style'=> array('font-family:FontAwesome;')),
    '#ajax' => array(
      'callback' => 'prochat_group_admin_assign_callback',
      'effect' => 'fade',
      'event' => 'click',
      'progress' => array('type' => 'none'),
    ),
  );

  $form['prochat_group_user_image_name'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array(
        'prochat_group_user_image_name pd-member-list-outer pd-project-list-outer-list',
        'id' => array('prochat_group_admin_assign')
      ),
    ),
    '#theme' => 'prochat_message_section_checkbox'
  );
  
  $userquery = db_select('m6connect_prochat_group_mapping','pgm');
  $userquery->leftjoin('field_data_field_user_profile_photo','fupp','fupp.entity_id=pgm.group_users');
  $userquery->leftjoin('file_managed','fm','fm.fid=fupp.field_user_profile_photo_fid');
  $userquery->leftjoin('realname','rel','rel.uid=pgm.group_users');  
  $userquery->fields('rel',array('realname'));
  $userquery->fields('pgm',array('group_users'));
  $userquery->fields('fm',array('uri')); 
  $userquery->condition('pgm.mapping_key',$action_key ,'=');
  $userquery->condition('pgm.group_users',$leave_member_uid ,'<>');
  $users_list = $userquery->execute()->fetchAll();

  foreach($users_list as $key=>$UserData){
    if ($UserData->uri) {
      $uimagepath = image_style_url('routing_company_logo', $UserData->uri);  
      $user_photo_url ='<img class="img-circle" src="' . $uimagepath . '" alt="' . $UserData->realname . '" title="' . $UserData->realname . '" />';
    }
    else {
      $user_photo_url ='<img class="img-circle" style="width:38px" src="/sites/default/files/styles/user_pic_40x40/public/images_13.png" alt="' . $UserData->realname . '" title="' . $UserData->realname . '" />';
    }
    $form['prochat_group_user_image_name']['chat-users'][$UserData->group_users]['prochat_group_user_image_'.$UserData->group_users] = array(
      '#markup' => $user_photo_url,
      '#prefix' => '<div class="prochat_group_user_image">',
      '#suffix' => '</div>',
    );

    $form['prochat_group_user_image_name']['chat-users'][$UserData->group_users]['prochat_user_'.$UserData->group_users] = array(
      '#type' => 'checkbox',
      '#title' => $UserData->realname,
      '#attributes' => array('title'=>  $UserData->realname,'class'=>array('group_admin_assign_option')),
      '#parents' => array('prochat_users',$UserData->group_users),
    );
  }

  return $form;
}

/**
 * Ajax callback for prochat_group_admin_assign_form
 */
function prochat_group_admin_assign_callback($form,&$form_state) {
  $commands = array();
  $values = $form_state['values'];
  $newAdminUid = array();
  foreach ($values['prochat_users'] as $ProUserUid=>$SelectUserValue) {
    if (!empty($values['prochat_users'][$ProUserUid])) {
      $newAdminUid[] =$ProUserUid;
    }
  }
  if (!empty($newAdminUid)) {
    db_update('m6connect_prochat_group')
      ->fields(array('group_uid' => $newAdminUid[0]))
      ->condition ('mapping_key', $values['group_admin_action_key'], '=')
      ->execute();

    db_delete('m6connect_prochat_group_mapping')
      ->condition('mapping_key', $values['group_admin_action_key'] , '=')
      ->condition('group_users', $values['group_admin_leave_member_uid'] , '=')
      ->execute();
    if (isset($_SESSION['Prochat'])&& !empty($_SESSION['Prochat'][0])) {
      $ProchatSessionCount = count($_SESSION['Prochat'][0]);
      if ($ProchatSessionCount == 1) {
        if ($_SESSION['Prochat'][0][$values['group_admin_action_key']]) {
          unset($_SESSION['Prochat']);
        }
      }
      else{
        unset($_SESSION['Prochat'][0][$values['group_admin_action_key']]);
      }
    }
    $prochat_member_chat_new = prochat_chat_rendar();
    $commands[] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
    $prochat_group_list = prochat_group_list();
    $commands[] = ajax_command_html('.prochat_project_list', $prochat_group_list);
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function prochat_group_section_form($form, &$form_state, $group_action = 'groupcreate', $mapping_key = FALSE){
  $form['#attributes']['class'] = 'prochat_group_section_form';  
  $form['action_box_error']= array(
    '#markup' => '<div class="action-box-error"></div>',  
  );
  $form['prochat_group_create_header']= array(
    '#markup' => '<div class="switch-pd-project-list clearfix"><div class="pull-left">'.
    l('<i class="fa fa-ellipsis-h" aria-hidden="true"></i>','/prochat/switch/home/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'switch-home-pd-project-list-btn use-ajax'))).
      '</div><div class="pull-right">'.
    l('<i class="fa fa-pencil-square-o" aria-hidden="true"></i>','/prochat/group/create/nojs',array('html'=>TRUE, 'attributes'=>array('title'=>'Create Group','class'=>'switch-pd-project-list-btn use-ajax'))).'</div></div>', 
  );

  if( $group_action == 'groupcreate') {
    $form['prochat_group_name'] = array(
      '#type' => 'textfield', 
      '#title' => 'Group Name',
      '#attributes' => array('class' => array('prochat-group-name'),'placeholder'=>array('Project Title')), 
      '#title_display' => 'invisible',
      '#prefix' => '<div class="form-inline prochat-field-btn">',  
    );
  }
  else{
    $form['prochat_group_member_invite']= array(
      '#markup' => '<div class="prochat-group-info form-item">Group Invite</div>',
      '#prefix' => '<div class="form-inline prochat-field-btn">', 
    );
  }
  
  $form['prochat-save-btn-submit'] = array(
    '#markup' =>  l('<input type="button" value="'.decode_entities('&#xf061;').'" class="form-submit custom-commit-submit" />', 'javascript:void(0);', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('style'=> array('font-family:FontAwesome;'),'class' => array('custom-main-group-btn')))),
    '#suffix' => '</div>',
  );
  $form['prochat_group_create'] = array(
    '#type' => 'submit',
    '#value' => decode_entities('&#xf061;'),
    '#executes_submit_callback' => FALSE,
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
    '#attributes'=> array('class'=>array('group-section-' . $group_action, 'custom-sub-group-btn'), 'style'=> array('font-family:FontAwesome;')),
    '#ajax' => array(
      'callback' => 'prochat_group_section_callback',
      'effect' => 'fade',
      'event' => 'click',
      'progress' => array('type' => 'none'),
    ),
  );

  $form['prochat_group_action'] = array('#type' => 'value', '#value' => $group_action);
  $form['prochat_group_invite_key'] = array('#type' => 'value', '#value' => $mapping_key);
  $AllUsersList = views_embed_view('prochat_member','page');
  $form['prochat_group_user_pager_list_user'] = array(
    '#markup' => $AllUsersList,
    '#prefix' => '<div class="prochat_group_user_pager pd-member-list-outer">',
    '#suffix' => '</div>',
  );
  $form['prochat_user_member_list'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class' => array('newmemberlists')),   
  );

  return $form;
}

/**
 * Submit ajax callback for prochat_group_section_form.
 */
function prochat_group_section_callback($form, &$form_state) {
  $commands = array();
  global $user;
  $values = $form_state['values'];

  if ($values['prochat_group_action'] == 'groupcreate') {
    if (isset($values['prochat_user_member_list']) && !empty($values['prochat_user_member_list'])) {
      $new_group_invite_users =  explode(',', $values['prochat_user_member_list']);
    }
    $SelectedUser = $new_group_invite_users;
    $AllSelectUser = $new_group_invite_users;

    if (!empty($SelectedUser) && !empty($values['prochat_group_name'])) {
      $query1 =db_select('m6connect_prochat_group','mpg');
      $query1->condition('mpg.group_name',$values['prochat_group_name'],'=');
      $query1->fields('mpg', array('group_name'));    
      $groupname = $query1->execute()->fetchCol();
      if (!empty($groupname)) {
        $commands[] = ajax_command_html('.action-box-error','<span class="change-action-box-error">* Group name already exists.</span>');
      }
      else {
        unset($_SESSION['Prochat']);
        $mapping_key = md5($user->uid . time() . $values['prochat_group_name']);
        $_SESSION['Prochat'][] = array($mapping_key => $mapping_key);
        if (db_table_exists('m6connect_prochat_group')) {
          $groupid = db_insert('m6connect_prochat_group')
            ->fields(array('mapping_key', 'group_uid', 'group_name', 'status', 'timestamp'))
            ->values(array(
              'mapping_key' => $mapping_key, 
              'group_uid' => $user->uid,
              'group_name' => $values['prochat_group_name'],
              'status' => 1,
              'timestamp' => time(), 
            ))
            ->execute();
        }
        array_push($AllSelectUser, $user->uid);
        foreach ($AllSelectUser as $SelectedUid) {
          if (db_table_exists('m6connect_prochat_group_mapping')) {
            $groupmapid = db_insert('m6connect_prochat_group_mapping')
              ->fields(array('mapping_key', 'group_users'))
              ->values(array(
                'mapping_key' => $mapping_key, 
                'group_users' => $SelectedUid,
              ))
              ->execute();
          }
        }
        $prochat_member_chat_new = prochat_chat_rendar();
        $commands[] = ajax_command_html('.prochat_member_chat', $prochat_member_chat_new);
        $prochat_group_list = prochat_group_list();
        $commands[] = ajax_command_html('.prochat_project_list', $prochat_group_list);
        if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
          foreach ($_SESSION['Prochat'][0] as $key=>$mapping_key){
            $commands[] = mymodule_ajax_command_insertInEmoji('textarea#text-message-smilly-'.$mapping_key);
          }
        }
      }
    }
    elseif (empty($values['prochat_group_name'])) {
      $commands[] = ajax_command_html('.action-box-error','<span class="change-action-box-error">* Please type group name.</span>');
    }
    else {
    $commands[] = ajax_command_html('.action-box-error','<span class="change-action-box-error">* At least one user is required to create a project.</span>');
    }
  }

  if ($values['prochat_group_action'] == 'groupinvite') {
    if (isset($values['prochat_user_member_list']) && !empty($values['prochat_user_member_list'])) {
      $new_invite_users =  explode(',', $values['prochat_user_member_list']);
    }
    $SelectedInviteUser = $new_invite_users;

    if (!empty($SelectedInviteUser)) {
      foreach ($SelectedInviteUser as $SelectedInviteUid) {
        if (db_table_exists('m6connect_prochat_group_mapping')) {
          $groupid = db_insert('m6connect_prochat_group_mapping')
            ->fields(array('mapping_key', 'group_users'))
            ->values(array(
              'mapping_key' => $values['prochat_group_invite_key'], 
              'group_users' => $SelectedInviteUid,   
            ))
            ->execute();
        }

        if (db_table_exists('m6connect_notification')) {
          $m6connect_notification = array(
            'type' => 'prochat',
            'event' => 'invite',
            'entity_id' => 0,
            'company_nid' => 0,
            'message' => NULL,
            'request_from' => $user->uid,
            'request_to' => $SelectedInviteUid,
            'status' => 1,
            'timestamp' => time(),
          );
          entity_save('m6connect_notification', (object) $m6connect_notification);
        }
      }
      $prochat_group_member = prochat_group_member($values['prochat_group_invite_key']);
      $prochat_member_chat = drupal_render(drupal_get_form('prochat_member_chat_form' ,$values['prochat_group_invite_key']));
      $commands[] = ajax_command_html('.project-dashboard-project-list-outer', '');
      $commands[] = ajax_command_html('.project_dashboard_member_list_chat .project_dashboard_member_list', $prochat_group_member);
      $commands[] = ajax_command_html('.project_dashboard_member_list_chat .project_dashboard_member_chat', $prochat_member_chat);
    }
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Helper function to get prochat group list.
 */
function prochat_group_list() {
  global $user;
  $output = '';
  $query = db_select('m6connect_prochat_group_mapping','mpgm');
  $query->join('m6connect_prochat_group','mpg','mpg.mapping_key=mpgm.mapping_key');
  $query->condition('mpgm.group_users',$user->uid,'=');
  $query->fields('mpg',array('id','mapping_key','group_name'));
  $result = $query->execute()->fetchAll();
  $output .= '<div class="switch-pd-project-list clearfix"><div class="pull-left"  style="color:#fff;"> Project List' . '</div><div class="pull-right">' . l('<i class="fa fa-pencil-square-o" aria-hidden="true"></i>', '/prochat/group/create/nojs', array('html' => TRUE, 'attributes' => array('title' =>'Create Group','class' => 'switch-pd-project-list-btn use-ajax'))) . '</div></div>';

  if (isset($result) && !empty($result)) {
    $output .= '<div class="pd-member-list-outer pd-project-list-outer clearfix dashboard-block-content">';
    $output .= '<ul class="list-unstyled dashboard-block-list">';
    foreach ($result as $delta) {
      $output .= '<li class="pd-project-'.$delta->id.'">';

      
      $Pd_pimage_name = '<i class="fa fa-users"></i>'.'&nbsp;'.$delta->group_name;
      $output .= l($Pd_pimage_name,'/prochat/chatswitch/'.$delta->mapping_key.'/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'pd-project-list-link use-ajax')));
      $output .= '</li>';   
    }
    $output .= '<ul>';
    $output .= '</div>';
  }
  return $output;
}

/**
 * Menu callback for prochat/chatdeletemsg/%/%/%ctools_js
 */
function prochat_multiple_section_two($item, $action, $data, $ajax = FALSE) {
  ctools_include('ajax');
  $commands = array();
  if ($item == 'chatdeletemsg') {
    if (!empty($action) && is_numeric($data) && $ajax== TRUE) {
      $prochat_message_delete = prochat_chat_delete_message($action,$data);
      $prochat_message = get_prochat_message($action);
      $commands[] = ajax_command_html('.prochat_message_container_'.$action, $prochat_message); 
    }
  }
  print ajax_render($commands);
  exit;
}

/**
 * Function to get form.
 */
function prochat_chat_delete_message($mappingKey, $messageId) {
  global $user;
  if (isset($messageId)  && !empty($messageId) && isset($mappingKey) && !empty($mappingKey)) {
    $query = db_select('m6connect_prochat_message', 'pdm');
    $query->fields('pdm', array('fid'));
    $query->condition('pdm.id', $messageId, '=');
    $query->condition('pdm.fid', '', '!=');
    $messagesFid = $query->execute()->fetchColumn(0);
    if ($messagesFid) {
      $file = file_load($messagesFid);
      file_delete($file);
    }
    db_delete('m6connect_prochat_message')
      ->condition('id', $messageId, '=')
      ->condition('mapping_key', $mappingKey, '=')
      ->condition('sender', $user->uid, '=')
      ->execute();
  }
}

/**
 * Helper function to render prochat.
 */
function prochat_chat_rendar() {
  // Refresh new prochat session 
  $prochat_member_chat_new = '';
  $prochat_multiple_screen_layout = '';
  if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'])) {
    $prochatRoom_count = count($_SESSION['Prochat'][0]);
    if ($prochatRoom_count > 2) {
      $prochat_multiple_screen_layout = 'prochat-multiple-screen-layout';
    }
    $prosessionValue = array_values($_SESSION['Prochat'][0]);
    $isEven = ($prochatRoom_count % 2 == 0) ? 1 : 0;
    $rowscount = ($isEven == 1) ? ($prochatRoom_count / 2) : (($prochatRoom_count - 1) / 2);
    $arr = array();
    $count = 0;
    foreach ($prosessionValue as $delta => $svalue) {
      if ($delta != 0 && $delta % 2 == 0) {
        $count++;
      }
      if (!isset($arr[$count])) {
        $arr[$count] = '';
      }
      $divClass = 'col-md-6 col-sm-6 col-xs-6 padding-5 prochat-multiple-chat';
      if ($rowscount==$count) {
        $divClass = 'col-md-12 col-sm-12 col-xs-12 padding-5 prochat-single-chat';  
      }

    $arr[$count] .= '<div class="' . $divClass . '">' . drupal_render(drupal_get_form('prochat_member_chat_form_' . $svalue, $svalue)) . drupal_render(drupal_get_form('prochat_file_attached_form_' . $svalue, $svalue)) . '</div>';
    }

    $prochat_member_chat_new = '<div class="prochat-screen '.$prochat_multiple_screen_layout.'"><div class="margin-5 row">'.implode('</div><div class="margin-5 row">',$arr).'</div></div>';
  }
  else {
    $prochat_member_chat_new = drupal_render(drupal_get_form('prochat_group_section_form'));
  }

  return $prochat_member_chat_new;
}

/**
 * Helper function to delete prochat group.
 */
function prochat_group_delete($mapping_key) {
  if (isset($mapping_key) && !empty($mapping_key)) {
    db_delete('m6connect_prochat_group')
      ->condition('mapping_key', $mapping_key,'=')
      ->execute();
    db_delete('m6connect_prochat_group_mapping')
      ->condition('mapping_key', $mapping_key,'=')
      ->execute();
    db_delete('m6connect_prochat_message')  
      ->condition('mapping_key', $mapping_key,'=')
      ->execute();
  }
}

/**
 * Function to generate form
 */
function prochat_member_chat_form($form, $form_state, $mapping_key = FALSE) {
  global $user;
  $form = array();
  $form['#attributes'] = array('class' => array('project_dashboard_member_chat_form', 'margin-bottom-10'));
  $form['#prefix'] = '<div id="' . $mapping_key . '" class="pd-message-chat-container pd-message-containersection-new-' . $mapping_key . '">';
  $form['#suffix'] = '</div>';

  $query = db_select('m6connect_prochat_group','mpg');
  $query->condition('mpg.mapping_key',$mapping_key ,'=');
  $query->fields('mpg',array('group_uid','group_name'));
  $group_data = $query->execute()->fetchAllKeyed();
  $GroupName = key(array_flip($group_data));
  $GroupAdmin = key($group_data);

  if (isset($_SESSION['Prochat']) && !empty($_SESSION['Prochat'][0])) {
    $ProchatSessionCount = count($_SESSION['Prochat'][0]);
    if ($ProchatSessionCount > 1) {
      $chatroomclear = l('<i class="fa fa-times" aria-hidden="true"></i>','/prochat/chatroomclear/'.$mapping_key.'/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'prochat-chatroomclear use-ajax')));  
    }
  }

  $GroupOption = '<div class="dropdown prochat-group-option">';
  $GroupOption .= l('<i class="fa fa-chevron-down" aria-hidden="true"></i>', 'javascript:void(0);', array('html' => TRUE, 'external' => true, 'attributes' => array('class' => array('prochat-group-option-btn'), 'title' => 'Group Option', 'id' => 'prochat-group-option-list', 'data-target' => '#', 'data-toggle' => 'dropdown', 'role' => 'button', 'aria-haspopup' => 'true', 'aria-expanded' => 'false')));

  $GroupOption .= '<ul class="dropdown-menu dropdown-menu-right" aria-labelledby="prochat-group-option-list">';
  if ($user->uid == $GroupAdmin) {
    $GroupOption .= '<li>';
    $GroupOption .= l('Invite','/prochat/groupinvite/'.$mapping_key.'/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'prochat-groupinvite  use-ajax')));
    $GroupOption .= '</li>';
    $GroupOption .= '<li style="display:none">';
    $GroupOption .= l('Group Delete','/prochat/groupdelete/'.$mapping_key.'/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'prochat-groupdelete  use-ajax')));
    $GroupOption .= '</li>';
  }
  $GroupOption .= '<li>';
  $GroupOption .= l('Leave','/prochat/groupleave/'.$mapping_key.'/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'prochat-groupleave ctools-modal-assign-dashboard-popup-style ctools-use-modal use-ajax')));
  $GroupOption .= '</li>';
  
  $GroupOption .= '<li style="display:none">';
  $GroupOption .= l('Delete','/prochat/settings/deletemsg/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'prochat-delete-msg-btn use-ajax')));
  $GroupOption .= '<ul class="list-unstyled prochat-msgdelete-submit" style="display:none">
    <li>
    <a class="prochat-delete-msg-btn-submit" href="javascript:void(0);">Submit</a>
    </li>
    </ul>';

  $GroupOption .= '</li>';
  $GroupOption .= '</ul>';
  $GroupOption .= '</div>';
  
  $form['switch_pd_project_list_to'] = array(
    '#markup' => '<div class="switch-pd-project-list clearfix">
      <div class="row margin-5">
      <div class="col-sm-2 col-md-2 col-xs-2 padding-5">
      ' . prochat_group_member($mapping_key) . '
      </div>
      <div class="text-center col-sm-8 col-md-8 col-xs-8 padding-5">
      <span style="color:#fff">' . $GroupName . '</span>
      ' . $chatroomclear . '
      </div>
      <div class="col-sm-2 col-md-2 col-xs-2 padding-5 text-right">
      ' . $GroupOption . '
      </div>
      </div>
      </div>',
  );

  $form['project_dashboard_message_list'] = array(
    '#markup' => get_prochat_message($mapping_key),
    '#prefix' => '<div id="prochat_message_container" class="pd-member-list-outer clearfix prochat_message_container_' . $mapping_key . '">',
    '#suffix' => '</div>',
  );
  $form['project_dashboard_project_entityid'] = array(
    '#type' => 'value',
    '#value' => $mapping_key,
  );
  $form['chat_action_box_error']= array(
    '#markup' => '<div class="chat-action-box-error form-item"></div>', 
  );
  $form['project_dashboard_chat_new_' . $mapping_key]= array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#attributes' => array('class'=> array('text-message-smilly'),'id'=>'text-message-smilly-'.$mapping_key),
    '#attached'=> array(
      'js' =>  array(
        array(
          'data' => 'jQuery(document).ready(function() {
             jQuery("textarea#text-message-smilly-'.$mapping_key.'").emojioneArea({
               container: ".message-abc-cont-'.$mapping_key.'",
               hideSource: true,
               useSprite: false,
               saveEmojisAs: "image",
               imageType: "png",
               shortnames: false,
             });
           });',
          'type' =>'inline'
        ),
      ),
    ),
    '#prefix' => '<div class="margin-bottom-10">',
    '#suffix' => '<div class="message-abc-cont-'.$mapping_key.'"></div></div>',
  );
  
  $form['prochat_chat_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Send',
    '#attributes' => array('class' => array('project_dashboard_chat_send_' . $mapping_key)),
    '#submit' => array('prochat_new_thread_message_submit_handler'),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'prochat_new_thread_message_callback',
      'effect' => 'fade',
      'event' => 'click',
      'progress' => array('type' => 'none'),
    ),
  );

  return $form;
}

/**
 * Ajax submit callback for prochat_member_chat_form
 */
function prochat_new_thread_message_callback(&$form, &$form_state) {
  global $user;
  $values = $form_state['values'];
  $mapping_key = $values['project_dashboard_project_entityid'];
  $commands = array();
  if (!empty($form_state['insertMessage'])) {
    $commands[] = array('command'=>'M6MessagingRefresh', 'insert_data' => $form_state['insertMessage']);
    $form_state['insertMessage'] = '';
  }
  $commands[] = ajax_command_html('div.emojionearea.text-message-smilly div.emojionearea-editor', '');
  $commands[] = ajax_command_invoke('textarea.text-message-smilly', 'val', array(''));
  
  $prochat_message = get_prochat_message($mapping_key);
  $commands[] = ajax_command_html('.prochat_message_container_' . $mapping_key, $prochat_message);

  return array('#type' => 'ajax', '#commands' => $commands);  
}

/**
 * Submit handler for prochat_member_chat_form
 */
function prochat_new_thread_message_submit_handler(&$form, &$form_state) {
  global $user;
  $form_state['insertMessage'] = '';
  $values = $form_state['values'];
  $mapping_key = $values['project_dashboard_project_entityid'];
  $message = trim(strip_tags($values['project_dashboard_chat_new_' . $mapping_key], '<img>'));
  $message = nl2br($message);

  $dom = new DOMDocument();
  @$dom->loadHTML($message);
  $imgtags = $dom->getElementsByTagName('img');
  foreach ($imgtags as $imgtag) {
    $class = $imgtag->getAttribute('class');
    if ($class == 'emojioneemoji') {
      $imgtag->removeAttribute('alt');
    }
  }
  $message = $dom->saveHTML();
  if (!empty($message) && !empty($mapping_key)) {
    $time = time();
    if (db_table_exists('m6connect_prochat_message')) {
      $insertId = db_insert('m6connect_prochat_message')
        ->fields(array('mapping_key', 'sender', 'message', 'status', 'timestamp'))
        ->values(array(
          'mapping_key' => $mapping_key, 
          'sender' => $user->uid,
          'message' => $message,
          'status' => 1,
          'timestamp' => REQUEST_TIME,
        ))
        ->execute();
    }
  }
}

/**
 * Function to generate form.
 */
function custom_prochat_delete_message_form($form, &$form_state) {
  $form['#prefix'] = '<div class="custom_delete_message_section1" style="display:none;">';
  $form['#suffix'] = '</div>';
  $form['prochat_messete_delete_submit'] = array(
    '#type' => 'submit',
    '#value' => 'submit',
    '#executes_submit_callback' => FALSE,
    '#prefix' => '<div style="display:none;">', 
    '#suffix' => '</div>',
    '#attributes'=> array('class' => array('custom-sub-msgdelete-btn')),
    '#ajax' => array(
      'callback' => 'prochat_messege_delete_callback',
      'effect' => 'fade',
      'event' => 'click',
      'progress' => array('type' => 'none'),
    ),
  );
  $form['prochat_messete_delete_list'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class' => array('messete_delete_list')),    
  );
  $form['prochat_messete_delete_key'] = array('#type' => 'value', '#value' => $_SESSION['ProchatSwitch']);
  return $form;
}

/**
 * Ajax Submit handler for custom_prochat_delete_message_form
 */
function prochat_messege_delete_callback($form, &$form_state) {
  $commands = array();
  global $user;
  $values = $form_state['values'];
  if (isset($values['prochat_messete_delete_list']) && !empty($values['prochat_messete_delete_list']) && isset($values['prochat_messete_delete_key'])) {
    $delete_msg_id =  explode(',', $values['prochat_messete_delete_list']);
    db_delete('m6connect_prochat_message')
      ->condition('id', $delete_msg_id, 'IN')
      ->condition('mapping_key', $values['prochat_messete_delete_key'])
      ->condition('sender', $user->uid)
      ->execute();
    $prochat_message = get_prochat_message($_SESSION['ProchatSwitch']);
    $commands[] = ajax_command_html('#prochat_message_container', $prochat_message);
    $commands[] = ajax_command_css('ul.prochat-msgdelete-submit', array('display' => 'none'));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Function to generate form
 */
function prochat_file_attached_form($form, &$form_state, $mapping_key) {
  $form['#prefix'] = '<div id="prochat-file-message-container"  style="display:none" class="prochat-file-message-container">';
  $form['#suffix'] = '</div>';
  $form['#attributes'] = array('class'=>array('prochat_file_attachedform'));
  $form['attachment-section'] = array(
    '#type' => 'container',
    '#attributes' => array(  
      'id' => array('attachment-fid-section')  
    ),
  );
  $form['project_dashboard_project_entityid'] = array(
    '#type' => 'value',
    '#value' => $mapping_key,
  );
  $form['prochat_file_upload_submit'] = array(
    '#type' => 'submit',
    '#value' => 'submit',
    '#executes_submit_callback' => FALSE,
    '#attributes'=> array('class'=>array('prochat_file_upload_btn')),
    '#ajax' => array(
      'callback' => 'prochat_file_attached_callback',
      'effect' => 'fade',
      'event' => 'click',
      'progress' => array('type' => 'none'),
    ),
  );
  $form['prochat_file_upload_section_two'] = array(
    '#name' => 'files[]',
    '#type' => 'file',
    '#title' => t('Choose a file'),
    '#attributes' => array('class'=> array('prochat-file-upload-section-2'),'multiple'=>TRUE),
    '#title_display' => 'invisible',
    '#size' => 22,
    '#theme_wrappers' => array(),
    '#upload_validators' => array(
      'file_validate_extensions' => array('txt pdf jpg jpeg doc docx rtf xls xlsx dwg dxf mpp mpx mspdi xml mpd mpxj pp mdb sdef tiff rif gif bmp png ppm pgm pbm pnm bpg cgm svg tar'),
    ),
  );
  return $form;
}

/**
 * Validate handler for prochat_file_attached_form
 */
function prochat_file_attached_form_validate($form, &$form_state) {
  if ($_FILES['files']['name'][0] != '') {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
        $file = file_save_upload($i, array(
        'file_validate_extensions' => array('txt pdf jpg jpeg doc docx rtf xls xlsx dwg dxf mpp mpx mspdi xml mpd mpxj pp mdb sdef tiff rif gif bmp png ppm pgm pbm pnm bpg cgm svg tar zip exe tz csv'),
        ));
      if ($file) {
        if ($file = file_move($file, 'public://prochatimage')) {
          $form_state['values']['prochat_file_upload_section_two'][$i] = $file;
        }
      }
    }
  }
}

/**
 * Ajax submit handler for prochat_file_attached_form
 */
function prochat_file_attached_callback($form, &$form_state) {
  global $user;
  $commands = array();
  $values = $form_state['values'];
  if (isset($values['prochat_file_upload_section_two']) && !empty($values['prochat_file_upload_section_two'])) {
    foreach ($values['prochat_file_upload_section_two'] as $key => $FidData) {
      if (isset($FidData->fid)) {
        $fileObj = file_load($FidData->fid);
        $url = image_style_url('pic_60x60',$fileObj->uri);
        $create_url = file_create_url($fileObj->uri);
        if ($fileObj->filemime == 'image/jpeg' || $fileObj->filemime == 'image/png'|| $fileObj->filemime == 'image/jpg'|| $fileObj->filemime == 'image/gif'|| $fileObj->filemime == 'image/x-ms-bmp') {
          $upload_file = '<a href="'.$create_url.'" target="_blank"><img src="'.$url.'"></a>';
        }
        elseif ($fileObj->filemime == 'text/plain') {
          $upload_file = '<a href="'.$create_url.'" target="_blank"><i class="fa fa-file-text fa-3x" aria-hidden="true"></i></a>';
        }
        elseif($fileObj->filemime == 'application/pdf') {
          $upload_file = '<a href="'.$create_url.'" target="_blank"><i class="fa fa-file-pdf-o fa-3x" aria-hidden="true"></i></a>';
        }
        elseif ($fileObj->filemime == 'application/msword' || $fileObj->filemime == 'application/rtf'|| $fileObj->filemime == 'application/vnd.openxmlformats-officedocument.wordprocessingml.document') {
          $upload_file = '<a href="' . $create_url . '" target="_blank"><i class="fa fa-file-word-o fa-3x" aria-hidden="true"></i></a>';
        }
        elseif ($fileObj->filemime == 'application/vnd.ms-excel' || $fileObj->filemime == 'application/vnd.openxmlformats-officedocument.spreadsheetml.sheet') {
          $upload_file = '<a href="'.$create_url.'" target="_blank"><i class="fa fa-file-excel-o fa-3x" aria-hidden="true"></i></a>';
        }
        elseif ($fileObj->filemime == 'application/x-tar' || $fileObj->filemime == 'application/zip') {
          $upload_file = '<a href="'.$create_url.'" target="_blank"><i class="fa fa-file-archive-o fa-3x" aria-hidden="true"></i></a>';
        }
        else {
          $upload_file = '<a href="'.$create_url.'" target="_blank"><i class="fa fa-file-o fa-3x" aria-hidden="true"></i></a>';
        }
        $insertFileData= array(
          'filename' => $fileObj->filename,
          'filemime' => $fileObj->filemime,
          'uri' => $fileObj->uri,
          'filesize' => $fileObj->filesize
        );
        $insertId = db_insert('m6connect_prochat_message')
          ->fields(array('mapping_key', 'sender', 'message', 'fid', 'filedata', 'status', 'timestamp'))
          ->values(array(
            'mapping_key' => $values['project_dashboard_project_entityid'], 
            'sender' => $user->uid,
            'message' => $upload_file,
            'fid' => $FidData->fid,
            'filedata' => serialize($insertFileData),
            'status' => 1,
            'timestamp' => time(), 
            ))
          ->execute();
      }
    }
    $commands[] = ajax_command_invoke('.prochat-file-upload-section-2', 'val' ,array(''));
    $prochat_message = get_prochat_message($values['project_dashboard_project_entityid']);
    $commands[] = ajax_command_html('.prochat_message_container_'.$values['project_dashboard_project_entityid'], $prochat_message);
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Helper function to get prochat message.
 */
function get_prochat_message($mapping_key) {
  global $user;
  $currentDate = date("m-d-Y");
  $query = db_select('m6connect_prochat_message', 'pdm');
  $query ->leftjoin('field_data_field_user_profile_photo','fupp','fupp.entity_id=pdm.sender');
  $query ->leftjoin('file_managed','fm','fm.fid=fupp.field_user_profile_photo_fid');
  $query->addExpression('DATE_FORMAT(FROM_UNIXTIME(pdm.timestamp), :Format)','timestamp_date',array(':Format'=>'%m/%d/%Y'));
  $query ->leftjoin('realname','rel','rel.uid=pdm.sender');
  $query->fields('pdm');
  $query ->fields('rel',array('realname'));
  $query ->fields('fm',array('uri'));
  $query->condition('pdm.mapping_key',$mapping_key,'='); 
  $query->orderBy('pdm.timestamp',ASC);
  $messagesObj = $query->execute()->fetchAll();
  
  $messageFiltered = array();
  foreach($messagesObj as $delta => $messageData){
    $date_object = new DateObject($messageData->timestamp, new DateTimeZone('UTC'));
    $date_object->setTimezone(new DateTimeZone(drupal_get_user_timezone()));
    $messageData->timestamp_time = date_format_date($date_object, 'custom', 'h:i A');
    $messageFiltered[$messageData->timestamp_date][] = $messageData;  
  }

  $output = '';
  $output .= '<div class="pd_message_list">';
  foreach ($messageFiltered as $date => $messages) {
    $dataOne = date('m-d-Y',strtotime($date));
    $msg_date_time = '';
    if ($currentDate == $dataOne) {
      $msg_date_time = 'Today'; 
    }
    else{
      $msg_date_time =  $dataOne;
    }
    $output .='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10"><span class="display-inline-block prochat-date-outer">'.$msg_date_time.'</span></div>'; 
    foreach ($messages as $key => $msgObj) {
      $date_object = new DateObject($msgObj->timestamp, new DateTimeZone('UTC'));
      $date_object->setTimezone(new DateTimeZone(drupal_get_user_timezone()));
      $messagetime = date_format_date($date_object, 'custom', 'h:i A');
      $messagedate = date_format_date($date_object, 'custom', 'Y-m-d');

      $msgreader_image= ''; 
      $delete_msg = '';
      $msg_name = '';
      $chatMessaeOption = '';
      $msg_bg = '';
      $MessageOutput = '';

      if ($msgObj->uri) {
        $uimagepath = image_style_url('routing_company_logo',$msgObj->uri);  
        $user_photo_url ='<img class="img-circle" src="' . $uimagepath . '" alt="' . $msgObj->realname . '" title="' . $msgObj->realname . '" />';
      }
      else {
        $user_photo_url ='<img class="img-circle" style="width:38px" src="/sites/default/files/styles/user_pic_40x40/public/images_13.png" alt="'.$msgObj->realname.'" title="'.$msgObj->realname.'" />';
      }
      if ($user->uid == $msgObj->sender) {
        $alignclass = 'pd-msg-writer row margin-5 margin-bottom-10';
        $msg_outer_col = '<div class="pd-chat-uimage col-md-2 padding-5"></div><div class="msg-outer col-md-10 text-right padding-5">';
        $delete_msg = '<span style="display:none" class="prochat-delete-message-'.$msgObj->sender.' delete-msg"><input class="prochat-delete-message-check" type="checkbox" value="'.$msgObj->id.'">';
        $chatMessaeOption = '<div class="prochat-chatmessage-option">'.l('<i class="fa fa-times" style="color:#333;" aria-hidden="true"></i>','/prochat/chatdeletemsg/'.$mapping_key.'/'.$msgObj->id.'/nojs',array('html'=>TRUE, 'attributes'=>array('class'=>'chat-message-delete-btn use-ajax'))).'</div>';
      }
      else {
        $alignclass = 'pd-msg-reader row margin-5 margin-bottom-10';
        $msg_outer_col = '<div class="msg-outer col-md-10 padding-5">';
        $msg_name = $msgObj->realname;
        $msgreader_image = '<div class="pd-chat-uimage col-md-2 padding-5">
                   '.$user_photo_url.'
                  </div>';
      }
      if (empty($msgObj->fid)) {
        $msg_bg = 'pd-chat-msg-bg';
        $MessageOutput = $msgObj->message.$chatMessaeOption; 
      }
      else {
        $MsgFileType = array('image/jpeg','image/png','image/jpg','image/gif','image/x-ms-bmp');
        $MsgFileData = unserialize($msgObj->filedata);
        if (in_array($MsgFileData['filemime'], $MsgFileType)) {
          $MessageOutput = $msgObj->message.$chatMessaeOption;
        }
        else {
          $MessageOutput = '<div class="clearfix">
            <div class="pull-left padding-left-5 text-right" style="color:#000">
            <div style="margin-bottom: 5px;">'.$MsgFileData['filename'].'</div>
            <div style="margin-bottom: 5px;">'.FileSizeConvert($MsgFileData['filesize']).'</div>
            <div>sent</div>
            </div>
            <div class="pull-right" style="padding: 10px;text-align: right;background: #FFF;border-radius: 5px;">
            ' . $msgObj->message.$chatMessaeOption . '
            </div>
            </div>';
        }
      }
      $output .= '<div class="' . $alignclass . '">
        ' . $msgreader_image . '
        ' . $msg_outer_col . '
        <div class="pd-chat-uname clearfix">
        ' . $msg_name . '
        <span class="pd-chat-time">
        ' . $messagetime . '
        </span>
        ' . $delete_msg . '
        </div>
        <div class="pd-chat-msg clearfix emojioneemoji-width-30 '.$msg_bg.'">
        ' . $MessageOutput . '
        </div>
        </div>
        </div>';
    }
    $output .= '</div>';
  }
  $output .= '</div>';
  return $output;
}

/**
 * Helper function for prochat group member
 */
function prochat_group_member($mapping_key) {
  $output = '';
  $userquery = db_select('m6connect_prochat_group_mapping','pgm');
  $userquery->leftjoin('field_data_field_user_profile_photo','fupp','fupp.entity_id=pgm.group_users');
  $userquery->leftjoin('file_managed','fm','fm.fid=fupp.field_user_profile_photo_fid');
  $userquery->leftjoin('realname','rel','rel.uid=pgm.group_users');  
  $userquery->fields('rel',array('realname'));
  $userquery->fields('pgm',array('group_users'));
  $userquery->fields('fm',array('uri')); 
  $userquery->condition('pgm.mapping_key',$mapping_key ,'=');
  $userquerydata = $userquery->execute()->fetchAll();  
  
  $query = db_select('m6connect_prochat_group','mpg');
  $query->condition('mpg.mapping_key',$mapping_key ,'=');
  $query->fields('mpg',array('group_uid','group_name'));  
  $group_data = $query->execute()->fetchAllKeyed();  
  $GroupName = array_values($group_data);
  $GroupAdmin = key($group_data);
  
  $output = '<div class="dropdown prochat-group-member">';
  $output .= l('<i class="fa fa-chevron-down" aria-hidden="true"></i>', 'javascript:void(0);', array('html' => TRUE, 'external' => true, 'attributes' => array('class' => array('prochat-group-member-btn'), 'title' => 'Group Member', 'id' => 'prochat-group-member-list', 'data-target' => '#', 'data-toggle' => 'dropdown', 'role' => 'button', 'aria-haspopup' => 'true', 'aria-expanded' => 'false')));

  $output .= '<ul class="dropdown-menu" style="width:245px" aria-labelledby="prochat-group-member-list">';
  foreach ($userquerydata as $key=>$userdata) {
    $output .= '<li class="margin-bottom-10 pd-member-'.$userdata->group_users.'">';
    if ($userdata->uri) {
      $uimagepath = image_style_url('routing_company_logo',$userdata->uri);  
      $user_photo_url ='<img class="img-circle" src="' . $uimagepath . '" alt="' . $userdata->realname . '" title="' . $userdata->realname . '" />';
    }
    else {
      $user_photo_url ='<img class="img-circle" style="width:38px" src="/sites/default/files/styles/user_pic_40x40/public/images_13.png" alt="'.$userdata->realname.'" title="'.$userdata->realname.'" />';
    }
    if ($GroupAdmin == $userdata->group_users) {
      $groupuRealname = $userdata->realname.' (Admin)';
    }
    else {
      $groupuRealname = $userdata->realname;
    }

    $Pd_uimage_name = $user_photo_url.'&nbsp;'.$groupuRealname;
    $output .= l($Pd_uimage_name,'/user/'.$userdata->group_users.'',array('html'=>TRUE, 'attributes'=>array('class'=>'project-dashboard-member')));
    $output .= '</li>';
  }
  $output .= '<ul>';
  $output .= '</div>';

  return $output;
}