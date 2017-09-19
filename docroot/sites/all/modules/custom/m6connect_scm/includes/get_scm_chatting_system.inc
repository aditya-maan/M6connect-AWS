<?php
function _get_scm_chatting_system() {
  $elements = array();
  $elements['chatting-container'] = array(
    '#markup' => drupal_render(scm_chatting_container()),
    '#prefix' => '<div clsss="row clearfix"><div class="col-md-6"></div><div class="col-md-6">',
    '#suffix' => '</div></div>',
  );
  /*$elements['chatting-container-taskbar'] = array(
    '#markup' => chatting_taskbar_container(),
    '#prefix' => '<div class="chatting-taskbar-container" style="background: #ccc;">',
    '#suffix' => '</div>',
  );*/
  return $elements;
}

function scm_chatting_container() {
  global $user;
  $currentUser = user_load($user->uid);
  // Checking whether the user messaging is accessed on company profile page.
  $_on_company_profile = arg(0) == 'node' && is_numeric(arg(1));

  $elements = array();
  $userinfo = array(); 
  $userOptions = array();
  $userDefaultValue='';
  $userDefaultdataObj = '';
  drupal_add_library('system', 'ui.autocomplete');
  drupal_add_library('system', 'ui.dialog');
  drupal_add_js('sites/all/libraries/emojione/emojionearea.js');
  drupal_add_css('sites/all/libraries/emojione/emojionearea.min.css');
  drupal_add_js(drupal_get_path('module', 'm6connect_company') . '/js/m6messaging.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $userOptions['new_mapping'] = 'new_mapping';
  
  $connectedUsers = array();
  $subQuery = db_select('m6connect_scm_messaging_connect_users','mmcu');
  $subQuery->distinct();
  $subQuery->fields('mmcu',array('mapping_id','leave_timestamp'));
  $subQuery->condition('mmcu.user_uid',$user->uid);
  
  $mainQuery = db_select('m6connect_scm_messaging_connect_users','mmcua');
  $mainQuery->join($subQuery,'smc','smc.mapping_id=mmcua.mapping_id');
  $mainQuery->join('m6connect_scm_messaging_connect','mmc','mmc.mapping_id=smc.mapping_id');
  $mainQuery->join('realname','r','r.uid=mmcua.user_uid');
  $mainQuery->leftjoin ('field_data_field_user_profile_photo', 'ufp', 'ufp.entity_id=mmcua.user_uid' );
  $mainQuery->leftjoin ('file_managed', 'fmu', 'fmu.fid=ufp.field_user_profile_photo_fid');
  $mainQuery->leftjoin('field_data_field_job_titles','jobm','jobm.entity_id=mmcua.user_uid AND jobm.bundle=:JobBundle',array(':JobBundle'=>'user'));
  $mainQuery->leftjoin('taxonomy_term_data','jterm','jterm.tid=jobm.field_job_titles_target_id');
  $mainQuery->fields('mmcua');
  //leave group
  $mainQuery->addField('smc','leave_timestamp','exit_timestamp');
  $mainQuery->fields('r',array('realname'));
  $mainQuery->fields('fmu', array('uri'));
  $mainQuery->addField('jterm','name','job_title');
  $mainQuery->condition('mmcua.user_uid',$user->uid,'!=');
  //leave group
  $mainQuery->isNull('mmcua.leave_timestamp');
  $mainQuery->orderBy('mmc.updated',DESC);
  $mappingusers = $mainQuery->execute()->fetchAll();
  //leave group
  $mainQuery->addField('smc','leave_timestamp','exit_timestamp');
  foreach($mappingusers as $index => $mapping){
    if(!isset($connectedUsers[$mapping->mapping_id])){
      // New group name according to new service messaging system.
      // Function defined in vendor.module.
      $new_group_name = _get_new_group_name_by_mapping_id($mapping->mapping_id, ucwords($mapping->realname));
	  
	  $connectedUsers[$mapping->mapping_id] = array();
      $connectedUsers[$mapping->mapping_id]['show_in_mapping'] =0;
      $connectedUsers[$mapping->mapping_id]['id'] = $mapping->id;
      $connectedUsers[$mapping->mapping_id]['mapping_id'] = $mapping->mapping_id;
      $connectedUsers[$mapping->mapping_id]['mapping_type'] = $mapping->mapping_type;
      $connectedUsers[$mapping->mapping_id]['group_name'] = array();
      //$connectedUsers[$mapping->mapping_id]['group_pic'] = $mapping->uri;
      $defaultUserPicicon = ($mapping->mapping_type=='user')?'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png':'sites/all/themes/m6connect/images/messanger_icons/fa-group-icon.png';
      $connectedUsers[$mapping->mapping_id]['user_pic'] = (!empty($mapping->uri) && $mapping->mapping_type=='user')?theme_image_style(array('style_name'=>'pic_40x40','path'=>$mapping->uri,'attributes'=>array('class'=>array('img-circle')))):theme('image', array('path' => $defaultUserPicicon,'attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;')));
      if(empty($mapping->exit_timestamp)){
        $connectedUsers[$mapping->mapping_id]['all_names'][$currentUser->uid] = ucwords($currentUser->realname);
      }
    }
    $connectedUsers[$mapping->mapping_id]['group_name'][]= !empty($new_group_name) ? $new_group_name : ucwords($mapping->realname);
    $connectedUsers[$mapping->mapping_id]['connected_user'][]= $mapping->user_uid;
    $connectedUsers[$mapping->mapping_id]['job_title'][$mapping->user_uid]= $mapping->job_title;
    $connectedUsers[$mapping->mapping_id]['all_names'][$mapping->user_uid] = ucwords($mapping->realname);
  }
  $connectedUserSettings = array();
  if($connectedUsers && !empty($connectedUsers)){
    foreach($connectedUsers as $mappingidKey => $dataObj){
      $activeClass = '';
      if(empty($userDefaultValue)){
        $userDefaultValue = $mappingidKey; 
        $userDefaultdataObj = (object)$dataObj;
        $activeClass = ' user-active';
      }else if($userDefaultValue==$mappingidKey){
        $userDefaultdataObj = (object)$dataObj; 
        $activeClass = ' user-active';
      }
      $connectedUserSettings[$mappingidKey] = array(
        'group_pic' => $dataObj['user_pic'],
        'group_name' => implode(', ',$dataObj['group_name']),
        'mapping_id' => $mappingidKey,
      );
      $userOptions[$mappingidKey] = $mappingidKey;
      $userinfo[$mappingidKey]  = '<div id="'.$mappingidKey.'" class="msg-connected-user-info msg-connected-user-'.implode('-',$dataObj['connected_user']).' clearfix'.$activeClass.'">';
      $userinfo[$mappingidKey] .= '  <div class="msg-connected-info">';
      $userinfo[$mappingidKey] .= '    <div class="msg-connected-picture msg-connected-user-inner padding-5">';
      $userinfo[$mappingidKey] .= '      <span class="msg-pic">'.$dataObj['user_pic'].'</span>';
      $userinfo[$mappingidKey] .= '    </div>';
      $userinfo[$mappingidKey] .= '    <div class="msg-connected-user-data msg-connected-user-inner padding-5">';
      $userinfo[$mappingidKey] .= '      <div class="msg-connected-user-name">'.implode(', ',$dataObj['group_name']).'</div>';
      $userinfo[$mappingidKey] .= '      <div class="msg-connected-user-desg"></div>';
      $userinfo[$mappingidKey] .= '    </div>';
      $userinfo[$mappingidKey] .= '  </div>';
      $userinfo[$mappingidKey] .= '</div>';
    }
    //drup_msg('in con');
  }else if(empty($userDefaultValue)){
    //drup_msg('out con');
   $userDefaultValue = 'new_mapping';
   $headerDataObj = array(
     'show_in_mapping' =>0,
     'id' => 0,
     'mapping_id' => 'new_mapping',
     'group_name' => array('Add New Recipients'),
     'job_title' => '' ,
     'user_pic' => theme('image', array('path' =>'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;'))),
     'mapping_type' => 'user',
     'no_recipients' =>1,
     'all_names' => array($currentUser->uid => ucwords($currentUser->realname)),
     'connected_user' => array($currentUser->uid),
   );
   $userDefaultdataObj = (object)$headerDataObj;
  }
  $NorecipientActiveClass = ($userDefaultValue == 'new_mapping')?' user-active':'';
  $mappingidKey = 'new_mapping';
  $userinfoNorecipient = array();
  $userinfoNorecipient[$mappingidKey]  = '<div id="'.$mappingidKey.'" class="msg-connected-user-info '.$mappingidKey.' msg-connected-user-0 clearfix'.$NorecipientActiveClass.'">';
  $userinfoNorecipient[$mappingidKey] .= '  <div class="msg-connected-info">';
  $userinfoNorecipient[$mappingidKey] .= '    <div class="msg-connected-picture msg-connected-user-inner padding-5">';
  $userinfoNorecipient[$mappingidKey] .= '      <span class="msg-pic">'.theme('image', array('path' =>'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;'))).'</span>';
  $userinfoNorecipient[$mappingidKey] .= '    </div>';
  $userinfoNorecipient[$mappingidKey] .= '    <div class="msg-connected-user-data msg-connected-user-inner padding-5">';
  $userinfoNorecipient[$mappingidKey] .= '      <div class="msg-connected-user-name">Add New Recipients</div>';
  $userinfoNorecipient[$mappingidKey] .= '      <div class="msg-connected-user-desg">New Message</div>';
  $userinfoNorecipient[$mappingidKey] .= '    </div>';
  $userinfoNorecipient[$mappingidKey] .= '  </div>';
  $userinfoNorecipient[$mappingidKey] .= '</div>';
  $userinfo = array_merge($userinfoNorecipient,$userinfo);
  
  drupal_add_js(array('m6connect_messenger' => array('connectedusers'=>$connectedUserSettings)), 'setting');
  
  $elements['connected-list'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('margin-5','row')),
    '#prefix' => '<div class="user-connected-user m6message-full-overlay clearfix" data-mapping="'.$userDefaultValue.'">',
    '#suffix' => '</div>',
  );
  $elements['connected-list']['left-container'] = array(
    '#type' => 'container',
    '#attributes' => $_on_company_profile ? array('class'=> array('col-md-4','col-sm-4','col-xs-12','padding-5')) : array('class'=> array('col-md-3','col-sm-4','col-xs-12','padding-5','no-taskbar')),
  );
  $elements['connected-list']['right-container'] = array(
    '#type' => 'container',
    '#attributes' => $_on_company_profile ? array('class'=> array('col-md-8','col-sm-8','col-xs-12','padding-5')) : array('class'=> array('col-md-9','col-sm-9','col-xs-12','padding-5','yes-taskbar')),
  );
  
  $elements['connected-list']['left-container']['connected-user-select']= array(
    '#markup' => drupal_render(drupal_get_form('scmchat_user_messaging_thread_switch_form',$userOptions,$userDefaultValue)),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );
  
  $createRecipientLink = '';
  if (!$_on_company_profile) {
    $creteImage = theme('image', array('path' => 'sites/all/themes/m6connect/images/messanger_icons/fa-user-create-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;')));
    $createRecipientLink = l($creteImage,'javascript:void(0);', array(
      'html'=>TRUE,'external'=> TRUE,'attributes'=>array('class'=>array('new-recipient-create-link'),'onclick'=>'jQuery(".msg-connected-user-list div#new_mapping").click();')));
  }
  $elements['connected-list']['left-container']['connected-user-header']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('msg-connected-header-main-container-inner','message-user-heading')),
    '#prefix' => '<div class="msg-connected-header-main-container msg-connected-header-main clearfix">',
    '#suffix' => '</div>',
  );
  $elements['connected-list']['left-container']['connected-user-header']['connected-user-header-markup'] = array(
    '#markup' => '<div class="col-md-8 col-sm-8 col-xs-8 padding-5">
                    <div class="create-messenger-group-text">All Messages</div>
                  </div>
                  <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-right">
                    <div class="create-messenger-group">'.$createRecipientLink.'</div>
                  </div>',
    '#prefix' => '<div class="row margin-5">',
    '#suffix' => '</div>',                    
  );
  /*$elements['connected-list']['left-container']['connected-user-header']= array(
    '#markup' => '<div class="msg-connected-header panel-body">
                <div class="pull-left">Messages</div>
                <div class="pull-right">'.$createRecipientLink.'</div>
                </div>',
     '#prefix' => '<div class="msg-connected-header-main clearfix">',
     '#suffix' => '</div>',         
  );*/
  $elements['connected-list']['left-container']['connected-user-list'] = array(
    '#markup' => implode('',$userinfo),
    '#prefix' => '<div class="msg-connected-user-list clearfix">',
    '#suffix' => '</div>',
  );
  $chattingContainer = drupal_render(drupal_get_form('scmchat_user_messaging_thread_form',$userDefaultdataObj));
  /*$elements['connected-list']['right-container']['chatting-container-taskbar'] = array(
    '#markup' => chatting_taskbar_container($chattingContainer),
    '#prefix' => '<div class="chatting-taskbar-container" style="background: #ccc;">',
    '#suffix' => '</div>',
  );*/
  $elements['connected-list']['right-container']['connected-user-form'] = array(
      //'#markup' => drupal_render(drupal_get_form('user_messaging_thread_form_'.$userDefaultdataObj->id,$userDefaultdataObj)),
    '#markup' => drupal_render(drupal_get_form('scmchat_user_messaging_thread_form',$userDefaultdataObj)),
    '#prefix' => '<div id="user-messaging-thread-form-container">', 
    '#suffix' => '</div>',
  );
  $elements['messenger-dialog'] = array(
    '#markup' => '',
    '#prefix' => '<div id="messenger-dialog" class="messenger-dialog">',
    '#suffix' => '</div>',
  );
  $elements['messenger-confirmation'] = array(
    '#markup' => '',
    '#prefix' => '<div id="messenger-confirmation-dialog" class="messenger-confirmation-dialog">',
    '#suffix' => '</div>',
  );
  return $elements;
}

function scmchat_user_messaging_thread_switch_form($form,&$form_state,$userOptions= array(),$defaultValue=''){  
  $form['#attributes'] = array('class'=>array('scmchat_user_messaging_thread_switch_form'));
  $form['connected-user-select']= array(
    '#type' => 'select',
    '#options' => $userOptions,
    '#attributes' => array('class'=> array('connected-user-select')),
    '#ajax' => array(
      'callback' => 'scmchat_user_messaging_thread_switch_callback',
    ),
  );
  if(!empty($defaultValue)){
    $form['connected-user-select']['#default_value'] =  $defaultValue; 
  }
  return $form;
}

function scmchat_user_messaging_thread_switch_callback($form,&$form_state){
  global $user;
  $currentUser = user_load($user->uid);
  $commands = array();
  $values = $form_state['values'];
  if(!empty($form_state['values']['connected-user-select']) && $form_state['values']['connected-user-select']!='new_mapping'){
    $connectedUsers = array();
    //leave group - Current User Status
    $subquery=db_select('m6connect_scm_messaging_connect_users','qtp');
    $subquery->addField('qtp','leave_timestamp','exit_timestamp');
    $subquery->condition('qtp.user_uid',$user->uid,'=');
    $subquery->condition('qtp.mapping_id',$form_state['values']['connected-user-select'],'=');
    $userStatusMapping = $subquery->execute()->fetchObject();
     
    $mainQuery = db_select('m6connect_scm_messaging_connect_users','mmcua');
    $mainQuery->join('realname','r','r.uid=mmcua.user_uid');
    $mainQuery->leftjoin ('field_data_field_user_profile_photo', 'ufp', 'ufp.entity_id=mmcua.user_uid' );
    $mainQuery->leftjoin ('file_managed', 'fmu', 'fmu.fid=ufp.field_user_profile_photo_fid');
    $mainQuery->leftjoin('field_data_field_job_titles','jobm','jobm.entity_id=mmcua.user_uid AND jobm.bundle=:JobBundle',array(':JobBundle'=>'user'));
    $mainQuery->leftjoin('taxonomy_term_data','jterm','jterm.tid=jobm.field_job_titles_target_id');
    $mainQuery->fields('mmcua');
    $mainQuery->fields('r',array('realname'));
    $mainQuery->fields('fmu', array('uri'));
    $mainQuery->addField('jterm','name','job_title');
    $mainQuery->condition('mmcua.mapping_id',$form_state['values']['connected-user-select'],'=');
    $mainQuery->condition('mmcua.user_uid',$user->uid,'!=');
    //leave group
    $mainQuery->isNull('mmcua.leave_timestamp');
    $mappingusers = $mainQuery->execute()->fetchAll();
	foreach($mappingusers as $index => $mapping){
      if(!isset($connectedUsers[$mapping->mapping_id])){
        $connectedUsers[$mapping->mapping_id] = array();
        $connectedUsers[$mapping->mapping_id]['id'] = $mapping->id;
        $connectedUsers[$mapping->mapping_id]['mapping_id'] = $mapping->mapping_id;
        $connectedUsers[$mapping->mapping_id]['mapping_type'] = $mapping->mapping_type;
        $connectedUsers[$mapping->mapping_id]['group_name'] = array();
        $defaultUserPicicon = ($mapping->mapping_type=='user')?'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png':'sites/all/themes/m6connect/images/messanger_icons/fa-group-icon.png';
		$connectedUsers[$mapping->mapping_id]['user_pic'] = (!empty($mapping->uri) && $mapping->mapping_type=='user')?theme_image_style(array('style_name'=>'pic_40x40','path'=>$mapping->uri,'attributes'=>array('class'=>array('img-circle')))):theme('image', array('path' => $defaultUserPicicon,'attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;')));
        if(empty($userStatusMapping->exit_timestamp)){
          $connectedUsers[$mapping->mapping_id]['all_names'][$currentUser->uid] = ucwords($currentUser->realname);
        }
      }
      if($mapping->user_uid!=$user->uid){
        $connectedUsers[$mapping->mapping_id]['group_name'][]= ucwords($mapping->realname);
        $connectedUsers[$mapping->mapping_id]['connected_user'][]= $mapping->user_uid;
        $connectedUsers[$mapping->mapping_id]['job_title'][$mapping->user_uid]= $mapping->job_title;
      }
      $connectedUsers[$mapping->mapping_id]['all_names'][$mapping->user_uid] = ucwords($mapping->realname);
    }
    $dataObj = (object)$connectedUsers[$form_state['values']['connected-user-select']];
	$rendermsg  = _scmchat_user_messageing_threads($dataObj);
    $commands[] = ajax_command_css('.new-group-action-container .m6message_group_add_cancel', array('display'=>'inline-block'));
    //leave group 
    if(!array_key_exists($user->uid,$dataObj->all_names)){
      $commands[] = ajax_command_invoke('div.form-textarea-emoji', 'hide' ,array());
    }
	else{
      $commands[] = ajax_command_invoke('div.form-textarea-emoji', 'show' ,array());  
    }
    $commands[] = ajax_command_data('div.user-connected-user.m6message-full-overlay','mapping',$dataObj->mapping_id);
    $commands[] = ajax_command_invoke('.messaging-mapping-mapping','val', array($dataObj->mapping_id));
    $commands[] = ajax_command_html('#messenger-header-user-info',_scmchat_m6messenger_header_markup($dataObj));
    $commands[] = ajax_command_html('.user-message-container .edit-message-container',$rendermsg);
    $commands[] = ajax_command_invoke('.add-new-member-users','val', array(''));
    $commands[] = ajax_command_html('.add-new-member-markup','');
    //$commands[] = ajax_command_html('.m6message-member-markup',implode(', ',$dataObj->all_names));
    $commands[] = array('command'=>'SwitchMessagingCallback');
    $commands[] = ajax_command_invoke('div.m6message-main-container','removeClass',array('opacity02'));
  }
  else if(!empty($form_state['values']['connected-user-select']) && $form_state['values']['connected-user-select']=='new_mapping') {
    $headerDataObj = array(
      'group_name' => array('Add New Recipients'),
      'job_title' => '' ,
      'user_pic' => theme('image', array('path' =>'sites/all/themes/m6connect/images/messanger_icons/fa-user-icon.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;'))),
      'mapping_type' => 'user',
      'no_recipients' =>1,
    );
	$headerDataObj = (object)$headerDataObj;
    $commands[] = ajax_command_css('.new-group-action-container .m6message_group_add_cancel', array('display'=>'none'));  
    $commands[] = ajax_command_invoke('div.form-textarea-emoji', 'hide' ,array());
    $commands[] = ajax_command_data('div.user-connected-user.m6message-full-overlay','mapping','new_mapping');
    $commands[] = ajax_command_invoke('.messaging-mapping-mapping','val', array($form_state['values']['connected-user-select']));
    $commands[] = ajax_command_html('.user-message-container .edit-message-container','');
    $commands[] = ajax_command_invoke('.add-new-member-users','val', array(''));
    $commands[] = ajax_command_html('.add-new-member-markup','');
    //$commands[] = ajax_command_html('.m6message-member-markup','No recipients');
    $commands[] = ajax_command_html('#messenger-header-user-info',_scmchat_m6messenger_header_markup($headerDataObj));
    //$commands[] = ajax_command_invoke('#messenger-header-user-info .m6messenger-confid-link-main','hide',array());
    $commands[] = ajax_command_invoke('.add-new-group-container-section','show', array());
    $commands[] = array('command'=>'SwitchMessagingCallback');  
  }
  $commands[] = ajax_command_invoke('div.user-connected-user.m6message-full-overlay','removeClass',array('opacity02'));
  return array('#type' => 'ajax', '#commands' => $commands);  
}

function _scmchat_m6messenger_header_markup($dataObj){
  global $user;
  $_on_company_profile = arg(0) == 'node' && is_numeric(arg(1));
  //drup_msg($dataObj);
  $output = '';
  $userNewDetail = array(
    'realname' => implode(', ',$dataObj->group_name),
    'job_title' => ($dataObj->mapping_type=='group')?'':implode(', ',$dataObj->job_title) ,
    'user_pic' => $dataObj->user_pic,
  );
  $isMappingNew = (isset($dataObj->no_recipients))?1:0;
  $configLinkStyle = ($isMappingNew)?'none':'block';
  $output .= '  <div class="row margin-5">';
  $output .= '    <div class="col-md-12 col-sm-12 col-xs-12 padding-5">';
  $output .= '      <div class="message-user-heading-user-info display-inline-block pull-left">';
  $output .= '        <div class="message-user-heading-user-name">'.$userNewDetail['realname'].'</div>';
  $output .= '        <div class="message-user-heading-user-job">'.$userNewDetail['job_title'].'</div>';
  $output .= '      </div>';
  $output .= '		<div class="chatting-icon pull-right">
        			  <a href="javascript:void(0);" class="chatting-volume-up">
          			    <i class="fa fa-volume-up" aria-hidden="true"></i>
                      </a>  
        			  <a href="javascript:void(0);" class="chatting-font-bold">
          			    <i class="capital-fonts fa fa-font" aria-hidden="true"></i>
        			  </a>        
						<a href="javascript:void(0);" class="chatting-envelope">
						  <i class="fa fa-envelope" aria-hidden="true"></i>
						</a>
						<a href="javascript:void(0);" class="chatting-minus">
						  <i class="fa fa-minus-circle" aria-hidden="true"></i>
						</a>
						<a href="javascript:void(0);" class="chatting-remove">
						  <i class="fa fa-times-circle" aria-hidden="true"></i>
						</a>
      </div>';
  /*$output .= '      <div class="message-user-heading-img pull-right"><i class="fa fa-volume-up" aria-hidden="true"></i><i class="fa fa-volume-off" aria-hidden="true" style="display:none;"></i>&nbsp;&nbsp;';
  $output .= '        <i class="capital-fonts fa fa-font" aria-hidden="true"></i>&nbsp;&nbsp;<i class="small-fonts fa fa-font" aria-hidden="true" style="display:none;"></i>&nbsp;&nbsp;';
  $output .=  '         <i class="fa fa-envelope" aria-hidden="true"></i>&nbsp;&nbsp;<i class="fa fa-minus-circle" aria-hidden="true"></i>&nbsp;&nbsp;<i class="fa fa-times-circle" aria-hidden="true"></i>';
  $output .=  '      </div>';*/ 
  $output .= '    </div>';  
  $output .= '  </div>';
  return $output;
}

/**
* chatting user search in new recipients
**/
function get_scm_chatting_user_detail_ajax(){
  $users = array();
  $term = (isset($_REQUEST['term']))?trim($_REQUEST['term']):'';
  $mappingID = (isset($_REQUEST['mapping_id']))?trim($_REQUEST['mapping_id']):'';
  if(!empty($mappingID) && !empty($term)){    
    $notShowUserQuery = db_select('users_roles','urd');
    $notShowUserQuery->fields('urd',array('uid'));
    $notShowUserQuery->condition('urd.rid',3,  '=');      
    $query =  db_select('users',  'u');
    $query->join('realname','r','r.uid=u.uid');
    $query->leftjoin('field_data_field_user_profile_photo', 'ufpm', 'ufpm.entity_id=u.uid' );
    $query->leftjoin('file_managed', 'fmum', 'fmum.fid=ufpm.field_user_profile_photo_fid');
    $query->leftjoin('field_data_field_job_titles','jobm','jobm.entity_id=u.uid AND jobm.bundle=:JobBundle',array(':JobBundle'=> 'user'));
    $query->leftjoin('taxonomy_term_data','jtermm','jtermm.tid=jobm.field_job_titles_target_id');
    $query->fields('u', array('uid'));
    $query->fields('r', array('realname'));
    $query->fields('fmum', array('uri'));
    $query->fields('jtermm', array('name'));
    $query->condition('r.realname','%'.db_like($term).'%',  'LIKE');
    //$query->condition('u.uid',$notShowUserQuery,'NOT IN');
    $query->condition('u.status',1);
    $query->orderBy('r.realname',  'ASC');
    $results = $query->execute()->fetchAll();
    if(!empty($results)){
      $jobTitle = !empty($udetail->name)?$udetail->name:'';
      foreach($results as $index => $udetail){
        $users[] = array(
          'label'=> ucwords($udetail->realname), 
          'value'=> $udetail->uid, 
          'image'=> (!empty($udetail->uri))?theme_image_style(array('style_name'=>'pic_40x40','path'=>$udetail->uri,'attributes'=>array('class'=>array('img-circle')))):theme('image', array('path' => 'sites/default/files/images_13_0.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;'))), 
          'job_title' => $jobTitle,
        );  
      }
    }
  }
  drupal_json_output($users);
  drupal_exit();
}

function scmchat_user_messaging_thread_form($form,&$form_state,$dataObj){
  global $user;
  $form['#attributes'] = array('class'=>array('scmchat_user_messaging_thread_form')); //dropzone
  $form['#attached']['js'][] = array(
    'data' => 'jQuery(document).ready(function(e) { 
                 setTimeout(refreshMessageContent, 10000);
			     var container = jQuery("body").find("#scm-chatuser-messaging-thread-form-container .edit-message-container .message-box-main-container"); 
                 if(container.length){
                   container.animate({scrollTop: container[0].scrollHeight}, "slow");  
                 }
               });',
    'type' => 'inline',
  );
  $form['#attached']['css'][] = array(
    'data' => 'div.message-post-message img.emojioneemoji{ width:50px; }
    		   .msg-connected-user-info.new_mapping{ display:none; }
               .msg-connected-user-info.new_mapping.user-active{ display:block; }',
    'type' => 'inline',
  );
  /*$form['reresh-link']= array(
    '#type' => 'submit',   
    '#value' => 'Refresh',
    '#attributes' => array('class' => array('m6messaging-refresh-submit')),
    '#executes_submit_callback' => FALSE,
  '#limit_validation_errors' => array(array('mapping-id')),
    '#ajax' => array(
      'callback' => 'refresh_scmchat_user_messageing_threads_callback',
      'progress' => array('type' => 'none'),
    ),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );*/
  
  $form['scmchat-header']= array(
    '#type' => 'container',
    '#attributes' => array('class'=> array('message-user-heading','clearfix')),
    '#prefix' => '<div id="messenger-container-message-header" class="messenger-header-container">',
    '#suffix' => '</div>',
  );
  $form['scmchat-header']['scmchat-header-markup'] = array(
    '#markup' => _scmchat_m6messenger_header_markup($dataObj),
    '#prefix' => '<div id="messenger-header-user-info" class="messenger-header-user-info">',
    '#suffix' => '</div>',
  );
  $group_container = (isset($dataObj->no_recipients))?'block':'none';
  $form['scmchat-header']['group_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('add-new-group-container-section'),'style'=>'display:'.$group_container.';'),
  );
  
  /*$form['scmchat-header']['group_container']['member_markup'] = array(
    '#markup' => implode(', ',$dataObj->all_names),
  '#prefix' => '<div class="scmchat-member-markup clearfix">',
  '#suffix' => '</div>',
  );*/
  
  $form['scmchat-header']['group_container']['add_new_member_markup'] = array(
    '#markup' => '',
    '#prefix' => '<div class="add-new-member-markup clearfix">', //style="margin-top:10px;"
    '#suffix' => '</div>',
  );
  $form['scmchat-header']['group_container']['add_new_member_box'] = array(
    '#type' => 'textfield',
    '#attributes' => array('class'=>array('add-new-member-box'),'placeholder'=> 'Add New Recipients'),
    '#prefix' => '<div class="margin-bottom-10">',
    '#suffix' => '</div>',
  );
  
  $form['scmchat-header']['group_container']['new-message-box']= array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#attributes' => array('class'=> array('text-message-smilly-new'),'style'=>'display:none;'),
    '#attached'=> array(
      'js' =>  array(
        array(
          'data'=>'jQuery(document).ready(function() {
                     jQuery(".text-message-smilly-new").emojioneArea({
             		   container: ".new-message-box-inner",
             		   hideSource: true,
             		   useSprite: false,
             	       saveEmojisAs: "image",
             		   imageType: "png",
             		   shortnames: false,
             		   filtersPosition: "bottom",
             		 });
           		   });',
        'type' =>'inline'
      ),
    ),
    'css' => array(
      array(
        'data'=>'.new-message-box-inner .emojionearea-upbutton,
        		 .new-message-box-inner .emojionearea-sendbutton{
                   display:none;   
                 }',
      			 'type' => 'inline'
        ),
      )
    ),
    '#prefix' => '<div class="margin-bottom-10 form-textarea-emoji-new">',
    '#suffix' => '<div class="new-message-box-inner"></div></div>',
  );
  $form['scmchat-header']['group_container']['add_new_member_users'] = array(
    '#type' => 'hidden',
    '#attributes' => array('class'=>array('add-new-member-users')),
  );
  $form['scmchat-header']['group_container']['gaction_container'] =  array(
    '#type' => 'actions',
    '#attributes' => array('class'=> array('pull-right')),
    '#prefix' => '<div class="new-group-action-container clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $cancelLinlStyle = (isset($dataObj->no_recipients))?'none':'inline-block';
  $form['scmchat-header']['group_container']['gaction_container']['gaction_save'] = array(
    '#type' => 'submit',   
    '#value' => 'Done',
    '#attributes' => array('class' => array('scmchat_group_add_done'),'style'=>'display:none;'),
    '#submit' => array('scmchat_add_message_group_member_submit_handler'),
    '#limit_validation_errors' => array(array('add_new_member_users'),array('mapping-id'),array('new-message-box')),
    '#ajax' => array(
      'callback' => 'scmchat_add_message_group_member_callback',
      'effect' => 'fade',
    ),
    '#prefix' => l('<input type="button" class="form-submit" value="Send" />','javascript:void(0);', array('html'=>TRUE,'external'=>TRUE, 'attributes'=> array('class'=>array('scmchat_group_add_group'),'onclick'=>'jQuery("input.scmchat_group_add_done").trigger("mousedown");'))), 
    '#suffix' => l('<input type="button" class="form-submit" value="Cancel" />','javascript:void(0);', array('html'=>TRUE,'external'=>TRUE, 'attributes'=> array('class'=>array('scmchat_group_add_cancel'),'style'=>'display:'.$cancelLinlStyle.';'))),
  );
  $form['scmchat-header']['forword_container'] = array(
    '#type' => 'actions',
    '#attributes' => array('class'=>array('message-forword-container-section','clearfix'),'style'=>'margin-top:10px;display:none;'),
  );
  $form['scmchat-header']['forword_container']['forword_save']= array(
    '#type' => 'markup',
    '#markup' => '<div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-left">'.l('<input type="button" class="form-submit" value="Cancel" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-forword-cancel-link')))).'</div>
				  <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-center">'.l('<input type="button" class="form-submit" value="0 Selected" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-forword-selected-link')))).'</div>
				  <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-right">'.l('<input type="button" class="form-submit" value="Forward" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-forword-next-link')))).'</div>',
	'#prefix' => '<div class="row margin-5">',
    '#suffix' => '</div>',
  );
  $form['scmchat-header']['delete_container'] = array(
    '#type' => 'actions',
    '#attributes' => array('class'=>array('message-delete-container-section','clearfix'),'style'=>'margin-top:10px;display:none;'),
  );
  $form['scmchat-header']['delete_container']['delete_save']= array(
    '#type' => 'markup',
    '#markup' => '<div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-left">'.l('<input type="button" class="form-submit" value="Cancel" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-delete-cancel-link')))).'</div>
				  <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-center">'.l('<input type="button" class="form-submit" value="0 Selected" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-deleted-selected-link')))).'</div>
				  <div class="col-md-4 col-sm-4 col-xs-4 padding-5 text-right">'.l('<input type="button" class="form-submit" value="Delete Selected" />','javascript:void(0);',array('external'=>TRUE,'html'=>TRUE,'attributes'=>array('class'=>array('message-delete-next-link')))).'</div>',
    '#prefix' => '<div class="row margin-5">',
    '#suffix' => '</div>',
  );
  $form['scmchat-main'] = array(
    '#type' => 'container',
    '#attributes' =>  array('class' => array('scmchat-main-container')),
  );
  $form['scmchat-main']['message-container'] =  array(
    '#type' => 'container',
    '#attributes' =>  array('class' => array('edit-message-container')),
    '#prefix' => '<div class="user-message-container">',
    '#suffix' => '</div>',
  );
  //drup_msg($dataObj);
  //drup_msg(_scmchat_user_messageing_threads($dataObj));
  
  $form['scmchat-main']['message-container']['message-list'] =  array(
    '#markup' => _scmchat_user_messageing_threads($dataObj),
  );
  $form['scmchat-main']['mapping-id'] = array(
    '#type' => 'hidden',
    '#default_value' => $dataObj->mapping_id,
    '#attributes' => array('class'=>array('messaging-mapping-mapping')),
  );
  $isMappingNew = (isset($dataObj->no_recipients))?1:0; 
  $empjitextareaStyle = (isset($dataObj->no_recipients))?'none':'block' ; 
  //leave group
  if($isMappingNew==0 && !array_key_exists($user->uid,$dataObj->all_names)){
    $empjitextareaStyle = 'none'; 
  }
  $form['scmchat-main']['message-box']= array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#attributes' => array('class'=> array('text-message-smilly'),'style'=>'display:none; '),
    '#attached'=> array(
      'js' =>  array(
        array(
          'data'=>'jQuery(document).ready(function() {
                     jQuery(".text-message-smilly").emojioneArea({
             	       container: ".message-abc-cont",
             		   hideSource: true,
             		   useSprite: false,
             		   saveEmojisAs: "image",
             		   imageType: "png",
             	 	   shortnames: false,
             		   filtersPosition: "bottom",
                     });
				   });',
          'type' =>'inline'
        ),
      ),
    ),
    '#prefix' => '<div class="margin-bottom-10 form-textarea-emoji" style="display:'.$empjitextareaStyle.'">',
    '#suffix' => '<div class="message-abc-cont"></div></div>',
  );
  $form['scmchat-main']['attachment-section']= array(
    '#type' => 'container',
    '#attributes' => array('style'=>'display:none;'),
    '#prefix' => '<div id="attachment-fid-section">',
    '#suffix' => '</div>',
  );
  $form['scmchat-main']['attachment-section']['attachment-fid'] = array(
    '#type' => 'file',
    '#name' => 'files[]',
    '#attributes' => array('class'=> array('emoji-file-attachment')),
    '#title' => t('Choose a file'),
    '#title_display' => 'invisible',
    '#size' => 22, 
  );
  $form['scmchat-main']['attachment-section']['upload-attachment'] = array(
    '#type' => 'submit',   
    '#value' => 'Upload Attachment',
    '#attributes' => array('class' => array('scmchat_attachment_send')),
    '#submit' => array('new_thread_attachment_submit_handler'),
    '#limit_validation_errors' => array(array('attachment-fid'),array('mapping-id')),
    '#ajax' => array(
      'callback' => 'new_thread_attachment_callback',
      'effect' => 'fade',
    ),
  );
  $form['scmchat-main']['submit'] = array(
    '#type' => 'submit',   
    '#value' => 'Send',
    '#attributes' => array('class' => array('scmchat_message_send'),'style'=>'display:none;'),
    '#submit' => array('scmchat_new_thread_message_submit_handler'),
    '#limit_validation_errors' => array(array('message-box'),array('mapping-id')),
    '#ajax' => array(
      'callback' => 'scmchat_new_thread_message_callback',
      'effect' => 'fade',
      'progress' => array('type' => 'none'),
    ),
  );
  return $form;
}

function scmchat_new_thread_message_submit_handler(&$form,&$form_state){
  global $user;
  $form_state['insertMessage'] = '';
  $values = $form_state['values'];
  $message  = _messenger_message_filter($values['message-box']);
  if(!empty($message) && !empty($values['mapping-id'])){
    $time = time();
    $insertId = db_insert('m6connect_scm_messaging_connect_message')->fields(array(
      'mapping_id' => $values['mapping-id'],
      'author_uid' => $user->uid,
      'message_text' => $message,
      'attachment' => 0,
      'render_state' =>1,
      'timestamp' => $time,
      'seen_by' => $user->uid,
    ))->execute(); 
    if($insertId){
      $mainClass = 'm6-messaging-message message-submitted clearfix text-right padding-5';
      $messageOutput  ='<div id="m6-messaging-message-'.$insertId.'" class="message-row margin-bottom-10 '.$mainClass.'">';
      $messageOutput .='  <div  class="clearfix">';
      $messageOutput .='    <div  class="message-post-message display-inline-block">'.$message.'</div>';
      $messageOutput .='  </div>';
      $messageOutput .='  <span class="message-post-time text-left clearfix">'.date('h:i A').'</span>';
      $messageOutput .='    <input type="checkbox" name="message_forword[]" class="messenger-message-forword-checkbox" value="'.$insertId.'">';
      $messageOutput .='</div>';
      $dataOne = date('m-d-Y');
      $date = date('m/d/Y');
      $dateDiv ='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10">'.$date.'</div></div>'; 
      $insert = array();
      $insert[] = array(
        'message' => $messageOutput,
        'date_div_class' => '.message-box.message-date-'.$dataOne,
        'data_div' => $dateDiv,
        'action' => 'insert',
      );
      $form_state['insertMessage'] = $insert;
    }
  }
}

function scmchat_new_thread_message_callback(&$form,&$form_state){
  global $user;
  $commands = array();
  if(!empty($form_state['insertMessage'])){
  $commands[] = array('command'=>'M6MessagingRefresh','insert_data'=>$form_state['insertMessage']);  
  $form_state['insertMessage']='';
  }
  $commands[] = ajax_command_html('div.emojionearea.text-message-smilly div.emojionearea-editor','');
  $commands[] = ajax_command_invoke('textarea.text-message-smilly','val',array(''));
  return array('#type' => 'ajax', '#commands' => $commands);  
}

function _scmchat_user_messageing_threads($dataObj){
  global $user;
  $userNewDetail = array();
  $output = '';
  
  if(isset($dataObj->no_recipients)){
    return $output;  
  }
  $userNewDetail = array(
  'realname' => implode(', ',$dataObj->group_name),
  'job_title' => ($dataObj->mapping_type=='group')?'':implode(', ',$dataObj->job_title) ,
  'user_pic' => $dataObj->user_pic,
  );
  
  //pre($dataObj,1); 
  //leave group
  $subquery=db_select('m6connect_scm_messaging_connect_users','qtp');
  $subquery->addExpression('IFNULL(qtp.leave_timestamp,:CurrentTime)','exit_timestamp',array(':CurrentTime'=>time()));
  $subquery->fields('qtp', array('mapping_id','join_timestamp'));
  $subquery->condition('qtp.user_uid',$user->uid,'=');
  
  $query = db_select('m6connect_scm_messaging_connect_message','mmcm');
  //leave group
  $query->join($subquery,'mql','mql.mapping_id=mmcm.mapping_id');
  $query->join('m6connect_scm_messaging_connect_users','mmcu','mmcm.mapping_id=mmcu.mapping_id AND mmcu.user_uid=:UserUid', array(':UserUid'=>$user->uid));
  $query->join('realname','r','r.uid=mmcm.author_uid');
  $query->leftjoin ('field_data_field_user_profile_photo', 'ufp', 'ufp.entity_id=mmcm.author_uid' );
  $query->leftjoin ('file_managed', 'fmu', 'fmu.fid=ufp.field_user_profile_photo_fid');
  $query->leftjoin ('file_managed', 'fmat', 'fmat.fid=mmcm.attachment');
  $query->addExpression('DATE_FORMAT(FROM_UNIXTIME(mmcm.timestamp), :Format)','timestamp_date',array(':Format'=>'%m/%d/%Y'));
  $query->addExpression('IF(FIND_IN_SET(:userUid,mmcm.seen_by)>0,0,1)','not_found',array(':userUid'=>$user->uid));
  $query->fields('mmcm');
  $query->addField('fmu','uri','user_pic_uri');
  $query->fields('r', array('realname'));
  $query->addField('fmat','uri','attach_uri');
  $query->addField('fmat','filemime','attach_filemime');
  $query->addField('fmat','filename','attach_filename');
  //$query->fields('fmu', array('uri'));
  $query->condition('mmcm.mapping_id',$dataObj->mapping_id);
  $query->condition('mmcm.render_state',2,'!=');
  $query->condition('mmcm.render_state',2,'!=');
  $query->orderBy('mmcm.timestamp',ASC);
  //$query->where('(mmcm.timestamp>mmcu.clear_conversation_timestamp)');
  //leave group
  $query->where('(mmcm.timestamp>mmcu.clear_conversation_timestamp) AND (mmcm.timestamp<=mql.exit_timestamp)'); //(mmcm.timestamp>mql.join_timestamp)
  $messagesObj = $query->execute()->fetchAll();
  $messageFiltered = array();
  
  foreach($messagesObj as $delta => $messageData){
  $date_object = new DateObject($messageData->timestamp, new DateTimeZone('UTC'));
    $date_object->setTimezone(new DateTimeZone(drupal_get_user_timezone()));
  $messageData->timestamp_time = date_format_date($date_object, 'custom', 'h:i A');
  $messageFiltered[$messageData->timestamp_date][] = $messageData;
  if($messageData->not_found){
    $seenBy = explode(',',$messageData->seen_by);
    $seenBy[] = $user->uid;
    db_update('m6connect_scm_messaging_connect_message')->fields(array('seen_by'=>implode(',',$seenBy)))->condition('id',$messageData->id)->execute();
  }
  }
  //<i class="fa fa-user-plus" aria-hidden="true"></i>  <i class="glyphicon glyphicon-plus"></i>
  /*$output .= '<div class="message-user-heading margin-bottom-10 clearfix">';
  $output .= '  <div class="row margin-5">';
  $output .= '    <div class="col-md-10 col-sm-10 col-xs-10 padding-5">';
  $output .= '      <div class="message-user-heading-img display-inline-block">'.$userNewDetail['user_pic'].'</div>';
  $output .= '      <div class="message-user-heading-user-info display-inline-block">';
  $output .= '        <div class="message-user-heading-user-name">'.$userNewDetail['realname'].'</div>';
  $output .= '        <div class="message-user-heading-user-job">'.$userNewDetail['job_title'].'</div>';
  $output .= '      </div>';
  $output .= '    </div>';
  $output .= '    <div class="col-md-2 col-sm-2 col-xs-2 padding-5 text-right">';
  $output .= '      <div class="message-user-heading-user-add display-inline-block">';
  $output .= '      '.l('<i class="fa fa-user-plus" aria-hidden="true"></i>','javascript:void(0);', array('html'=>TRUE,'external'=> TRUE, 'attributes'=> array('class'=> array('m6id-mapping-user-add','m6id-mapping-user-setting'))));
  $output .= '      </div>';
  $output .= '      <div class="dropdown messenger-user-config-section display-inline-block">';
  $output .= '        '.l('<i class="fa fa-ellipsis-h" aria-hidden="true"></i></i>','javascript:void(0);', array('html'=>TRUE,'external'=> TRUE, 'attributes'=> array('class'=> array('m6id-mapping-user-config','m6id-mapping-user-setting'),'id'=>'messenger-configure','data-target' => '#','data-toggle' => 'dropdown','role' => 'button','aria-haspopup' => 'true','aria-expanded' => 'false')));
  $output .= '        <ul class="dropdown-menu dropdown-menu-right" aria-labelledby="messenger-configure">';
  $output .= '          <li>'.l('Delete Conversation','javascript:void(0);', array('external'=>TRUE)).'</li>';
  $output .= '          <li>'.l('Exit Group','javascript:void(0);', array('external'=>TRUE)).'</li>';
  $output .= '        </ul>';
  $output .= '      </div>';
  $output .= '    </div>';
  $output .= '  </div>';
  $output .= '</div>';*/
 
  $output .= '<div class="message-box-main-container">';
  foreach($messageFiltered as $date => $messages){
  $dataOne = date('m-d-Y',strtotime($date));
  $output .='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10">'.$date.'</div>';  
  foreach($messages as $delta => $message){
    $messageUserPic  = '';
    $messageUserRealname  = '';
    $mainClass = 'm6-messaging-message message-submitted clearfix text-right padding-5';
    if($user->uid != $message->author_uid){
    $mainClass = 'm6-messaging-message message-received clearfix text-left text-left padding-5';
    //$messageUserPic  = (!empty($message->user_pic_uri))?theme_image_style(array('style_name'=>'pic_40x40','path'=>$dataObj->user_pic_uri,'attributes'=>array('class'=>array('img-circle')))):theme('image', array('path' => 'sites/default/files/images_13_0.png','attributes'=> array('class'=> array('img-circle'),'style'=>'width:40px;height:40px;')));
      $messageUserRealname = ucwords($message->realname);
    }
    $message_text = $message->message_text;
    if(empty($message->message_text)){
    if(empty($message->attachment)){
      continue; 
    }
    $message_text = get_m6message_attachment_box($message->attachment,$message->attach_uri,$message->attach_filename,$message->attach_filemime);
    }
    $output .='<div id="m6-messaging-message-'.$message->id.'" class="message-row margin-bottom-10 '.$mainClass.'">';
      $output .='    <div class="clearfix">';
    $output .='      <div class="message-post-user-realname">'.ucwords($messageUserRealname).'</div>';
    $output .='      <div class="message-post-message display-inline-block">'.$message_text.'</div>';
    $output .='    </div>';
    $output .='    <span class="message-post-time text-left clearfix">'.$message->timestamp_time.'</span>';
    $output .='    <input type="checkbox" name="message_forword[]" class="messenger-message-forword-checkbox" value="'.$message->id.'" style="display: none;">';
    if($user->uid == $message->author_uid){
      $output .='<input type="checkbox" name="message_delete[]" class="messenger-message-delete-checkbox" value="'.$message->id.'" style="display: none;">';
    }
      $output .='</div>'; 
  }
  $output .='</div>'; 
  }
  $output .= '</div>';
  return $output;
} 

function scmchat_insert_message_ajax_callback(){
  global $user,$company;
  $values = array();
  $insert = array();
  parse_str($_REQUEST['formDataValues'], $values);
  $message  = _messenger_message_filter($values['message-box']);
  if(!empty($message) && !empty($values['mapping-id'])){
    $time = time();
    $insertId = db_insert('m6connect_scm_messaging_connect_message')->fields(array(
    'mapping_id' => $values['mapping-id'],
    'author_uid' => $user->uid,
    'message_text' => $message,
    'attachment' => 0,
    'render_state' =>1,
    'timestamp' => $time,
    'seen_by' => $user->uid,
  ))->execute(); 
  
  //m6id message insert start 
  $query = db_select('m6connect_scm_messaging_connect_users' ,'mmc');
  $query->fields('mmc',array('user_uid'));
  $query->condition('mmc.mapping_id',$values['mapping-id'],'=');
  $query->condition('mmc.user_uid',$user->uid,'<>');
  $mapping_gid = $query->execute()->fetchColumn(0); 
  $user_type = 'company_user';
    $onboardingManagerUids = _get_company_users_by_og_roles($company->nid,'M6ID Manager');
  if(in_array($user->uid,$onboardingManagerUids)){
    $user_type = 'ob_manager';    
  } 
  $approval_message= array(
    'request_from' => $user->uid,
    'request_to' => $mapping_gid,
    'message' => strip_tags($message, '<>'), 
    'company_nid' => $company->nid,
    'user_type' => $user_type,
    'message_prefix' => NULL,
    'timestamp' => time(),
  );  
    $m6id = db_insert('m6connect_onboarding_inter_company_message')->fields($approval_message)->execute(); 
  //m6id message insert end 
  if($insertId){
    $mainClass = 'm6-messaging-message message-submitted clearfix text-right padding-5';
    $messageOutput  ='<div id="m6-messaging-message-'.$insertId.'" class="message-row margin-bottom-10 '.$mainClass.'">';
      $messageOutput .='  <div  class="clearfix">';
    $messageOutput .='    <div  class="message-post-message display-inline-block">'.$message.'</div>';
    $messageOutput .='  </div>';
    $messageOutput .='  <span class="message-post-time text-left clearfix">'.date('h:i A').'</span>';
    $messageOutput .='    <input type="checkbox" name="message_forword[]" class="messenger-message-forword-checkbox" value="'.$insertId.'">';
    $messageOutput .='    <input type="checkbox" name="message_delete[]" class="messenger-message-delete-checkbox" value="'.$insertId.'">';
      $messageOutput .='</div>';
    $dataOne = date('m-d-Y');
    $date = date('m/d/Y');
    $dateDiv ='<div class="message-box message-date-'.$dataOne.'"><div class="message-date-data text-center margin-bottom-10">'.$date.'</div></div>'; 
    $insert = array();
    $insert[] = array(
      'message' => $messageOutput,
      'date_div_class' => '.message-box.message-date-'.$dataOne,
      'data_div' => $dateDiv,
        'action' => 'insert',
    );
    db_update('m6connect_scm_messaging_connect')->fields(array('updated'=>time()))->condition('mapping_id',$values['mapping-id'])->execute();
  }
  }
  drupal_json_output(array('callback'=>'M6MessagingRefresh','insert'=>$insert,'values'=>$values));
  drupal_exit();
}

function scmchat_add_message_group_member_submit_handler(&$form,&$form_state){
  global $user, $company;
  $values = $form_state['values'];
  $form_state['new_message_group'] = '';
  $currentTime = time();
  if(!empty($values['add_new_member_users']) && !empty($values['mapping-id']) && $values['mapping-id']!='new_mapping'){
  $mappingId = $values['mapping-id'];
  $invitedUser  = explode(',',$values['add_new_member_users']);
  $invitedUser = array_map('trim',$invitedUser);
  $invitedUser = array_filter($invitedUser);
  $invitedUser = array_unique($invitedUser);
  if(!empty($invitedUser)){
    $mapping = db_select('m6connect_scm_messaging_connect','mmc')->fields('mmc')->condition('mmc.mapping_id',$values['mapping-id'])->execute()->fetchObject();  

    $mappingQuery = db_select('m6connect_scm_messaging_connect_users','mmcu');
    $mappingQuery->fields('mmcu',array('mapping_type'));
    $mappingQuery->addExpression('GROUP_CONCAT(distinct mmcu.user_uid  separator \',\')', 'user_uids');
    $mappingQuery->condition('mmcu.mapping_id',$values['mapping-id']);
    $mappingQuery->groupBy('mmcu.mapping_id');
    //leave group
    $mappingQuery->isNull('mmcu.leave_timestamp');
    $mapping = $mappingQuery->execute()->fetchObject();
    $mappingUsers = explode(',',$mapping->user_uids);
    if($mapping->mapping_type=='user'){
    $checkUser = $mappingUsers;
    $checkUser = array_merge($checkUser,$invitedUser);
    $checkUser = array_unique($checkUser);
    $groupUserCount = count($checkUser);
    if($groupUserCount>2){
      $groupQuery1 = db_select('m6connect_scm_messaging_connect_users','mmcu');
      $groupQuery1->fields('mmcu',array('mapping_id'));
      $groupQuery1->addExpression('count(mmcu.user_uid)','ucount');
      $groupQuery1->condition('mmcu.mapping_type','group');
      $groupQuery1->condition('mmcu.user_uid',$checkUser,'IN');
      $groupQuery1->groupBy('mmcu.mapping_id');
      $groupQuery1->havingCondition('ucount', $groupUserCount);
      $group = $groupQuery1->execute()->fetchAllKeyed(0,1);
      if(!empty($group)){
      $mappingId = key($group);  
      }else{
      $userkey = implode('-',$mappingUsers);
      $mappingId = md5($userkey.'-'.$currentTime);
          db_insert('m6connect_scm_messaging_connect')->fields(array(
              'mapping_id' => $mappingId,
            'created_by' => $user->uid,
            'mapping_group' => 'group',
            'mapping_gid' => $user->uid,
            'timestamp' => $currentTime,
        'updated' => $currentTime,
          ))->execute();
      }
      foreach($checkUser as $delta => $userUid){
      if($values['mapping-id']==$mappingId && in_array($userUid,$mappingUsers)){
        continue; 
      }
      //leave group
        db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$mappingId,'user_uid'=>$userUid))
           ->fields(array('mapping_id'=>$mappingId,'user_uid'=>$userUid,'mapping_type'=>'group','status'=>1,'join_timestamp'=>$currentTime,'leave_timestamp'=>NULL))->execute();  
      }
      $form_state['new_message_group']= $mappingId;
    }
    }else{
    foreach($invitedUser as $delta => $userUid){
      if(in_array($userUid,$mappingUsers)){
        continue; 
      }
      //leave group
        db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$values['mapping-id'],'user_uid'=>$userUid))
           ->fields(array('mapping_id'=>$values['mapping-id'],'user_uid'=>$userUid,'mapping_type'=>'group','status'=>1,'join_timestamp'=>$currentTime,'leave_timestamp'=>NULL))->execute(); 
    }
    $form_state['new_message_group']= $values['mapping-id'];  
    }
  }
  }else if(!empty($values['add_new_member_users']) && !empty($values['mapping-id']) && $values['mapping-id']=='new_mapping'){
   $mappingId ='';
   $invitedUser  = explode(',',$values['add_new_member_users']);
   $invitedUser = array_map('trim',$invitedUser);
   $invitedUser[] = $user->uid;
   $invitedUser = array_filter($invitedUser);
   $invitedUser = array_unique($invitedUser); 
   $invitedCount = count($invitedUser);
   $mapping_group = ($invitedCount==2)?'user':'group';
   if($invitedCount >= 2){
     $groupQuery1 = db_select('m6connect_scm_messaging_connect_users','mmcu');
     $groupQuery1->fields('mmcu',array('mapping_id'));
     $groupQuery1->addExpression('count(mmcu.user_uid)','ucount');
     $groupQuery1->condition('mmcu.mapping_type',$mapping_group);
     $groupQuery1->condition('mmcu.user_uid',$invitedUser,'IN');
     //leave group
       $groupQuery1->isNull('mmcu.leave_timestamp');
     $groupQuery1->groupBy('mmcu.mapping_id');
     $groupQuery1->havingCondition('ucount', $invitedCount); 
     $group = $groupQuery1->execute()->fetchAllKeyed(0,1);
     if(!empty($group)){
       $mappingId = key($group);
     $form_state['new_message_group']= $mappingId;   
     }else{
     $userkey = implode('-',$invitedUser);
     $mappingIdNew = md5($userkey.'-'.$currentTime);
     $mapping_group = ($invitedCount==2)?'user':'group';
       $insertID = db_insert('m6connect_scm_messaging_connect')->fields(array(
       'mapping_id' => $mappingIdNew,
       'created_by' => $user->uid,
       'mapping_group' => $mapping_group,
       'mapping_gid' => $user->uid,
       'timestamp' => $currentTime,
       'updated' => $currentTime,
     ))->execute();
     if($insertID && is_numeric($insertID)){
       $mappingId = $mappingIdNew;
       $form_state['new_message_group']= $mappingId;
       foreach($invitedUser as $delta => $inviteUserUid){
       //db_insert('m6connect_scm_messaging_connect_users')->fields(array('mapping_id'=>$mappingId,'user_uid'=>$inviteUserUid,'mapping_type'=>$mapping_group,'status'=>1,'join_timestamp'=>$currentTime))->execute(); 
       //leave group
        db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$mappingId,'user_uid'=>$inviteUserUid))
           ->fields(array('mapping_id'=>$mappingId,'user_uid'=>$inviteUserUid,'mapping_type'=>$mapping_group,'status'=>1,'join_timestamp'=>$currentTime,'leave_timestamp'=>NULL))->execute();  
       }
     }
     }
     if(!empty($mappingId) && !empty($values['new-message-box'])){
     $message  = _messenger_message_filter($values['new-message-box']);
     if(!empty($message)){
       $insertId = db_insert('m6connect_scm_messaging_connect_message')->fields(array(
       'mapping_id' => $mappingId,
       'author_uid' => $user->uid,
       'message_text' => $message,
       'attachment' => 0,
       'render_state' =>1,
       'timestamp' => $currentTime,
       'seen_by' => $user->uid,
      ))->execute();
     }
     }
   }
  }
}

function scmchat_add_message_group_member_callback($form,&$form_state){
  ctools_include('ajax');
  ctools_include('modal');
  $commands = array();
  if(!empty($form_state['new_message_group'])){
  db_update('m6connect_scm_messaging_connect')->fields(array('updated'=>time()))->condition('mapping_id',$form_state['new_message_group'])->execute();
  $commands[] = ctools_ajax_command_redirect('scm/chatting', 0);
  //array('query'=> array('thread'=>$form_state['new_message_group']))  
  }else{
  $commands[] = ajax_command_invoke('div.m6message-main-container','removeClass',array('opacity02'));  
  }
  
  return array('#type' => 'ajax', '#commands' => $commands);    
}

function scmchat_connect_callback($connectWithUser){
  global $user;
  $db_and1 = db_and()->condition('mmc.created_by',$user->uid)->condition('mmc.mapping_gid',$connectWithUser->uid);
  $db_and2 = db_and()->condition('mmc.mapping_gid',$user->uid)->condition('mmc.created_by',$connectWithUser->uid);
  $db_or = db_or()->condition($db_and1)->condition($db_and2);
  $query = db_select('m6connect_scm_messaging_connect','mmc');
  $query->fields('mmc',array('mapping_id'));
  $query->condition('mmc.mapping_group','user');
  $query->condition($db_or);
  $mappingId = $query->execute()->fetchField();
  //drup_msg($query->__toString());
  if(!$mappingId){
  $mappingId = md5($user->uid.'-'.$connectWithUser->uid.'-'.time());
  db_insert('m6connect_scm_messaging_connect')->fields(array(
      'mapping_id' => $mappingId,
    'created_by' => $user->uid,
    'mapping_group' => 'user',
    'mapping_gid' => $connectWithUser->uid,
    'timestamp' => time(),
    'updated' => time(),
  ))->execute();
  $currentTime = time();
  db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$mappingId,'user_uid'=>$user->uid))
     ->fields(array('mapping_id'=>$mappingId,'user_uid'=>$user->uid,'mapping_type'=>'user','status'=>1,'join_timestamp'=>$currentTime))->execute();
    db_merge('m6connect_scm_messaging_connect_users')->key(array('mapping_id'=>$mappingId,'user_uid'=>$connectWithUser->uid))
     ->fields(array('mapping_id'=>$mappingId,'user_uid'=>$connectWithUser->uid,'mapping_type'=>'user','status'=>1,'join_timestamp'=>$currentTime))->execute();    
  }
  //return $mappingId;
  //drupal_goto('user-messaging',array('query' => array('thread' => $mappingId)));
  db_update('m6connect_scm_messaging_connect')->fields(array('updated'=>time()))->condition('mapping_id',$mappingId)->execute();
  drupal_goto('user-messaging');
}

function chatting_taskbar_container($chattingContainer){
  $output = '
    <div class="chatting-header" style="background: #fff;padding: 5px 0 25px 0;">
      <div class="chatting-icon pull-right">
        <a href="javascript:void(0);" class="chatting-volume-up">
          <i class="fa fa-volume-up" aria-hidden="true"></i>
        </a>  
        <a href="javascript:void(0);" class="chatting-font-bold">
          <i class="capital-fonts fa fa-font" aria-hidden="true"></i>
        </a>        
        <a href="javascript:void(0);" class="chatting-envelope">
          <i class="fa fa-envelope" aria-hidden="true"></i>
        </a>
        <a href="javascript:void(0);" class="chatting-minus">
          <i class="fa fa-minus-circle" aria-hidden="true"></i>
        </a>
        <a href="javascript:void(0);" class="chatting-remove">
          <i class="fa fa-times-circle" aria-hidden="true"></i>
        </a>
      </div>
    </div>
  ';
  $output .= drupal_render(scm_chatting_container());//'<div id="user-messaging-thread-form-container">'.$chattingContainer.'</div>';
  return $output;
}