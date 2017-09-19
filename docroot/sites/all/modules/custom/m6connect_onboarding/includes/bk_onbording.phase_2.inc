<?php

/********** Start Onboarding Manage Colleagues **********/

function onboarding_manage_colleagues_callback(){
  global $company;
  onboarding_m6id_ctools_popup_style();
  $elements = array();
  $elements = array(
    '#markup' => get_manage_colleagues_content(),
	'#prefix' => '<div class="onboarding-manage-colleagues-section">',
	'#suffix' => '</div>',
  );
  return $elements;	
}

function get_manage_colleagues_content(){
  global $company;
  $rows = array();
  onboarding_message_ctools_popup_style();
  $header = array(
    array('data'=>'M6ID Number', 'class'=> array('text-center')),
	array('data'=>'Employee ID', 'class'=> array('text-center')),
	array('data'=>'First Name', 'class'=> array('text-center')),
	array('data'=>'Last Name', 'class'=> array('text-center')),
	array('data'=>'Email', 'class'=> array('text-center')),
	array('data'=>'Health Screen', 'class'=> array('text-center')),
	array('data'=>'Background Check', 'class'=> array('text-center')),
	array('data'=>'Status', 'class'=> array('text-center')),
	array('data'=>'Message', 'class'=> array('text-center')),
  );
  
  $userDetails = get_onboarding_company_employess_details();
  if($userDetails && is_array($userDetails)){
	foreach($userDetails as $delta => $dataObj){
	  $rows[] = array(
		'data'=>array( 
		  array('data'=> l($dataObj->field_m6id_value,'/user-m6id-info/'.$dataObj->uid.'/'.$company->nid.'/nojs',array('attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-onboarding-m6id-popup-style')))), 'class'=> array('text-center')),
		  array('data'=>drupal_render(drupal_get_form('onboarding_employee_id_form',$dataObj)), 'class'=> array('text-center')),
		  array('data'=>$dataObj->field_first_name_value, 'class'=> array('text-center')),
		  array('data'=>$dataObj->field_last_name_value, 'class'=> array('text-center')),
		  array('data'=>$dataObj->mail, 'class'=> array('text-center')),
		  array('data'=>drupal_render(drupal_get_form('onboarding_health_screen_form',$dataObj)), 'class'=> array('text-center')),
		  array('data'=>drupal_render(drupal_get_form('onboarding_background_check_form',$dataObj)), 'class'=> array('text-center')),
		  array('data'=>drupal_render(drupal_get_form('onboarding_employee_status_form',$dataObj)), 'class'=> array('text-center')),
		  array('data'=>l('<div class="onboarding-msg-icon"><img src="/sites/all/themes/m6connect/images/ins-msg-notify.png"></div>','onboarding-company-messaging/'.$company->nid.'/'.$dataObj->uid.'/nojs', array('html'=>TRUE,'attributes'=> array('class'=> array('ctools-use-modal','ctools-modal-onboarding-message-popup-style')))), 'class'=> array('text-center')),
		)
	  );
	}
  }
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No Onboarding Request Submited yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-colleagues-table','table-hover','table-bordered','text-center'))));	
}

function get_onboarding_company_employess_details($header=array()){
  global $company;
  $query = db_select('users','u');
  $query->join('og_membership','og','og.etid=u.uid AND og.entity_type=:entityType',array(':entityType'=>'user'));
  $query->join('node','n','n.uid=u.uid AND n.type=:nodeType',array(':nodeType'=>'onboarding'));
  $query->join('field_data_field_allow_onboarding_companies','fac','fac.entity_id=n.nid AND fac.field_allow_onboarding_companies_nid=:companyNid',array(':companyNid'=>$company->nid));
  $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=u.uid AND m6id.bundle=:userBundle', array(':userBundle'=>'user'));
  $query->leftjoin('field_data_field_first_name','fname','fname.entity_id=u.uid AND fname.bundle=:userBundle', array(':userBundle'=>'user'));
  $query->leftjoin('field_data_field_last_name','lname','lname.entity_id=u.uid AND lname.bundle=:userBundle', array(':userBundle'=>'user'));
  $query->leftjoin('m6connet_onboarding_colleagues_status','ous','ous.user_uid=u.uid AND ous.company_nid=:companyNid',array(':companyNid'=>$company->nid));
  $query->fields('u',array('uid','mail'));
  $query->fields('n',array('nid'));
  $query->fields('og',array('gid'));
  $query->fields('m6id',array('field_m6id_value'));
  $query->fields('fname',array('field_first_name_value'));
  $query->fields('lname',array('field_last_name_value'));
  $query->fields('ous',array('employee_id','health_screen','background_check','status'));
  $query->condition('og.gid',$company->nid,'=');
  $query->condition('og.state',1,'=');
  if(!empty($header)){
	//$query->extend('TableSort')->orderByHeader($header);  
  }
  $result = $query->execute()->fetchAll();
  return $result;
}

function onboarding_employee_id_form($form,$form_state,$dataObj){
  $form['#attributes'] = array('class'=>'onboarding_employee_id_form');
  
  $form['company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->gid,
  );
  
  $form['user_uid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->uid,
  );
  
  $form['employee_id'] = array(
    '#type' => 'textfield',
	'#title' => 'Employee_Id',
	'#title_display' => 'invisible',
	'#size' => 15,
	'#default_value'=> $dataObj->employee_id,
	'#ajax' => array(
		'callback' => 'modify_onboarding_employess_id_callcack',
		'effect' => 'fade',
		//'progress' => array('type'=> 'throbber', 'message'=> NULL),
	),  
  );
  
  //$form['submit'] = array(
  //  '#type' => 'submit',
//	'#value' => 'Save',
//	'#executes_submit_callback' => FALSE,
//	'#limit_validation_errors' => array(),
//	'#attributes' => array('style'=>'display:none;'),/
//	'#href' => '',
//	'#ajax' => array(
//		'callback' => 'modify_onboarding_employess_id_callcack',
//		'effect' => 'fade',
//		'event' => 'click',
//		'progress' => array('type'=> 'throbber', 'message'=> NULL),
//	), 
 // );
  return $form;
}

function modify_onboarding_employess_id_callcack($form,&$form_state){
  $commands = array();
  $values = $form_state['values'];
  if(isset($values['company_nid'],$values['user_uid'],$values['employee_id']) && !empty($values['company_nid']) && !empty($values['user_uid'])){
    db_merge('m6connet_onboarding_colleagues_status')->key(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid']))->fields(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid'],'employee_id'=>$values['employee_id']))->execute();
  }
  return array('#type' => 'ajax', '#commands' => $commands);	
}

function onboarding_health_screen_form($form,$form_state,$dataObj){
  $form['#attributes'] = array('class'=>'onboarding_health_screen_form');
  
  $form['company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->gid,
  );
  
  $form['user_uid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->uid,
  );
  
  $form['health_screen'] = array(
    '#type' => 'select',
	'#title' => 'Health Check',
	'#title_display' => 'invisible',
	'#options' => array(1=>'Pass',0=>'Fail'),
	'#empty_option' => '- None -',
	'#default_value'=> $dataObj->health_screen, 
	'#ajax' => array(
		'callback' => 'modify_onboarding_health_screen_callcack',
		'effect' => 'fade',
		//'progress' => array('type'=> 'throbber', 'message'=> NULL),
	), 
  );
  return $form;
}

function modify_onboarding_health_screen_callcack($form,&$form_state){
  $commands = array();
  $values = $form_state['values'];
  if(isset($values['company_nid'],$values['user_uid'],$values['health_screen']) && !empty($values['company_nid']) && !empty($values['user_uid'])){
	$values['health_screen'] = is_numeric($values['health_screen'])?$values['health_screen']:NULL;
    db_merge('m6connet_onboarding_colleagues_status')->key(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid']))->fields(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid'],'health_screen'=>$values['health_screen']))->execute();
  }
  return array('#type' => 'ajax', '#commands' => $commands);	
}

function onboarding_background_check_form($form,$form_state,$dataObj){
  $form['#attributes'] = array('class'=>'onboarding_background_check_form');
  
  $form['company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->gid,
  );
  
  $form['user_uid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->uid,
  );
  
  $form['background_check'] = array(
    '#type' => 'select',
	'#title' => 'Background Check',
	'#title_display' => 'invisible',
	'#options' => array(1=>'Pass',0=>'Fail'),
	'#empty_option' => '- None -',
	'#default_value'=> $dataObj->background_check, 
	'#ajax' => array(
		'callback' => 'modify_onboarding_background_check_callcack',
		'effect' => 'fade',
		//'progress' => array('type'=> 'throbber', 'message'=> NULL),
	),
  );
  return $form;
}

function modify_onboarding_background_check_callcack($form,&$form_state){
  $commands = array();
  $values = $form_state['values'];
  if(isset($values['company_nid'],$values['user_uid'],$values['background_check']) && !empty($values['company_nid']) && !empty($values['user_uid'])){
	$values['background_check'] = is_numeric($values['background_check'])?$values['background_check']:NULL;
    db_merge('m6connet_onboarding_colleagues_status')->key(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid']))->fields(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid'],'background_check'=>$values['background_check']))->execute();
  }
  return array('#type' => 'ajax', '#commands' => $commands);	
}

function onboarding_employee_status_form($form,$form_state,$dataObj){
  $form['#attributes'] = array('class'=>'onboarding_employee_status_form');
  
  $form['company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->gid,
  );
  
  $form['user_uid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->uid,
  );
  
  $form['employee_status'] = array(
    '#type' => 'select',
	'#title' => 'Background Check',
	'#title_display' => 'invisible',
	'#options' => array(1=>'Approve',0=>'Reject',2=>'Pending'),
	'#empty_option' => '- None -',
	'#default_value'=> $dataObj->status, 
	'#ajax' => array(
		'callback' => 'modify_onboarding_employee_status_callcack',
		'effect' => 'fade',
		//'progress' => array('type'=> 'throbber', 'message'=> NULL),
	),
  );
  return $form;
}

function modify_onboarding_employee_status_callcack($form,&$form_state){
  $commands = array();
  $values = $form_state['values'];
  if(isset($values['company_nid'],$values['user_uid'],$values['employee_status']) && !empty($values['company_nid']) && !empty($values['user_uid'])){
    $values['employee_status'] = is_numeric($values['employee_status'])?$values['employee_status']:NULL;
	db_merge('m6connet_onboarding_colleagues_status')->key(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid']))->fields(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid'],'status'=>$values['employee_status']))->execute();
  }
  return array('#type' => 'ajax', '#commands' => $commands);	
}

/********** End Onboarding Manage Colleagues **********/

/********** Start Onboarding Submit_Employees **********/

function onboarding_submit_employees_callback(){
  $element = array();
  ctools_include('ajax');
  ctools_include('modal');
  onboarding_m6id_ctools_popup_style();
  drupal_add_library('system', 'drupal.collapse');
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');
  drupal_add_js('jQuery(document).ready(function () { jQuery("table.onboarding_submit_employeee_table").DataTable({"bPaginate": false,"bLengthChange": false,"bFilter": false,"bInfo": false,"bAutoWidth": false,"order": [],"aoColumnDefs": [{ "bSortable": false, "aTargets": [0,"no-sort"]}]}); });',
    array('type' => 'inline')
  );
  $element['new_request_container'] = array(
    '#type'=> 'container',
	'#attributes' => array('class'=> array('new_request_container_main')),
	'#prefix' => '<div id="new_request_container_main"><div class="onboarding-container-label onboarding-table-label">New Requests From Companies:</div>',
    '#suffix' => '</div>',
  );
  
  $element['request_table_data'] = array(
    '#markup'=> get_onboarding_submitted_request_content(),
	'#prefix' => '<div class="new_request_form_company_section">',
	'#suffix' => '</div>',
  );
  
  $element['new_request_container']['new_request_table'] = array(
    '#markup'=> get_onboarding_new_request_content2(),
	'#prefix' => '<div class="new_request_form_company_section">',
	'#suffix' => '</div>',
  );
  
  $element['accepted_request_container'] = array(
    '#type'=> 'container',
	'#attributes' => array('class'=> array('accepted_request_container_main_container')),
	'#prefix' => '<div id="new_request_container_main"><div class="onboarding-container-label onboarding-table-label">Accepted Requests From Companies:</div>',
    '#suffix' => '</div>',
  );
  
  $accptedCompanies = get_onboarding_accepted_company_request();
  foreach($accptedCompanies as $delta => $dataObj){
	if(empty($dataObj->invite_for_projects)){
	  $dataObj->invite_for_projects =0;
	}
	$element['accepted_request_container']['accepted_request_container_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects] = array(
      '#type'=> 'markup',
	  '#markup' => drupal_render(drupal_get_form('get_accepted_company_submit_employess_form',$dataObj)),
	  '#prefix' => '<div class="accepted_request_content accepted_request_content_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects.'">',
      '#suffix' => '</div>',
    );  
  }
  return $element;	
}

function get_onboarding_submitted_request_content(){
  global $user, $company;
  $rows = array();
  $header = array(
	array('data'=>'Company Id','class'=> array('text-left')),
	array('data'=>'Company','class'=> array('text-left')),
	array('data'=>'Project','class'=> array('text-left')),
	array('data'=>'Status','class'=> array('text-left')),
	array('data'=>'Action','class'=> array('text-center'))
  );
  
  $db_or = db_or();
  $db_or->condition('miuo.requestee_company',$company->nid,'=')->condition('miuo.requester_company',$company->nid,'=');	
  $query = db_select('m6connect_onboarding_invite','miuo');
  $query->join('node','scn', 'scn.nid=miuo.requester_company');
  $query->join('node','rcn', 'rcn.nid=miuo.requestee_company');
  $query->leftjoin('node','cpn', 'cpn.nid=miuo.invite_for_projects');
  $query->distinct();
  $query->fields('miuo',array('requester_company','requestee_company','invite_for_projects','approval_status'));
  $query->addField('scn','title','requester_company_title');
  $query->addField('rcn','title','requestee_company_title');
  $query->addField('cpn','title','requester_project_title');	
  $query->condition('miuo.invite_status',1,'=');
  $query->condition('miuo.requestee_company',$company->nid,'=');	
  $result = $query->execute()->fetchAll();
  if($result && !empty($result)){
	foreach($result as $delta => $dataObj){
	  $nodePath = drupal_lookup_path('alias','node/'.$dataObj->requester_company);
	  $companyLink = l($dataObj->requester_company_title,$nodePath);
	  $approvalStatus = ($dataObj->approval_status==1)?'Approved':($dataObj->approval_status==2)?'Rejected':'Pending';
	  $rows[] = array(
	    'data'=> array(
		  array('data'=>$dataObj->requester_company),
		  array('data'=> $companyLink),
		  array('data'=>$dataObj->requester_project_title),
		  array('data'=>$approvalStatus),
		  array('data'=>get_onboarding_new_request_action_button($dataObj),'class'=> array('text-center')),
		),
		'class' => array('custom-odd'),
	  );
	}
  }
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No M6ID Request','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-new-request-table','table-hover','table-bordered'))));	
}

function get_onboarding_accepted_company_request(){
  global $company;
  $query = db_select('m6connect_onboarding_invite','miuo');
  $query->join('node','rcn', 'rcn.nid=miuo.requestee_company');
  $query->join('node','scn', 'scn.nid=miuo.requester_company');
  $query->leftjoin('node','cpn', 'cpn.nid=miuo.invite_for_projects');
  $query->distinct();
  $query->fields('miuo',array('requestee_company','requester_company','invite_for_projects'));
  $query->addField('scn','title','requester_company_title');
  $query->addField('rcn','title','requestee_company_title');
  $query->addField('cpn','title','requester_project_title');
  $query->condition('miuo.approval_status',1,'=');	
  $query->condition('miuo.invite_status',1,'=');
  $query->condition('miuo.requestee_company',$company->nid,'=');
  $result = $query->execute()->fetchAll();
  if($result && !empty($result)){
	$return = $result;  
  }
  return $return;
}

function get_onboarding_new_request_content2(){
  global $company;
  $snoCount=1;
  $header = array();
  $rows = array();
  $query = db_select('m6connect_onboarding_invite','miuo');
  $query->join('node','scn', 'scn.nid=miuo.requester_company');
  $query->join('node','rcn', 'rcn.nid=miuo.requestee_company');
  $query->leftjoin('node','cpn', 'cpn.nid=miuo.invite_for_projects');
  $query->distinct();
  $query->fields('miuo',array('requester_company','requestee_company','invite_for_projects'));
  $query->addField('scn','title','requester_company_title');
  $query->addField('rcn','title','requestee_company_title');
  $query->addField('cpn','title','requester_project_title');
  $query->condition('miuo.approval_status',0,'=');	
  $query->condition('miuo.invite_status',1,'=');
  $query->condition('miuo.requestee_company',$company->nid,'=');	
  $result = $query->execute()->fetchAll();
  if($result && !empty($result)){
	foreach($result as $delta => $dataObj){
	  $nodePath = drupal_lookup_path('alias','node/'.$dataObj->requester_company);
	  $newRequsetText = 'New Request from '.l($dataObj->requester_company_title,$nodePath);
	  if(!empty($dataObj->invite_for_projects) && !empty($dataObj->requester_project_title)){
		$newRequsetText .= ' for Project - '.$dataObj->requester_project_title;  
	  }
      $action = get_onboarding_new_request_action_button($dataObj);
	  $rows[] = array(
	    'data'=> array(
		  array('data'=>$snoCount++,'class'=> array('text-center')),
		  array('data'=>$newRequsetText,'class'=> array('text-left')),
		  array('data'=>$action,'class'=> array('text-center')),
		),
	  );	
	}
  }
  $header = array(
    array('data'=>'Request No.', 'class'=> array('text-center')),
    array('data'=>'Request', 'class'=> array('text-left')),
	array('data'=>'Action', 'class'=> array('text-center')),
  );
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No M6ID Request Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-new-request-table','table-hover','table-bordered','text-center'))));
}

/*function get_onboarding_new_request_content(){
  global $company;
  $snoCount=1;
  $header = array();
  $rows = array();
  $query = db_select('m6connect_invite_users_onboarding','miuo');
  $query->join('node','n', 'n.nid=miuo.company_nid');
  $query->distinct();
  $query->fields('miuo', array('company_nid'));
  $query->fields('n', array('title'));
  $query->condition('miuo.invited_comp',$company->nid,'=');	
  $query->condition('miuo.approval_status',0,'=');	
  $result = $query->execute()->fetchAll();
  if($result && !empty($result)){
	foreach($result as $delta => $dataObj){
	  $nodePath = drupal_lookup_path('alias','node/'.$dataObj->company_nid);
	  $rows[] = array(
	    'data'=> array(
		  array('data'=>$snoCount++,'class'=> array('text-center')),
		  array('data'=>'New Request from '.l($dataObj->title,$nodePath),'class'=> array('text-left')),
		  array('data'=>get_onboarding_new_request_action_button($dataObj),'class'=> array('text-center')),
		),
	  );	
	}
  }
  $header = array(
    array('data'=>'Request No.', 'class'=> array('text-center')),
    array('data'=>'Request', 'class'=> array('text-left')),
	array('data'=>'Action', 'class'=> array('text-center')),
  );
  return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No Onboarding Request Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-new-request-table','table-hover','table-bordered','text-center'))));
}*/

function get_onboarding_new_request_action_button($dataObj){
  if(empty($dataObj->invite_for_projects)){
	$dataObj->invite_for_projects =0; 
  }
  return '<div class="btn-group">
			<div class="dropdown">
			  <button id="request_action_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects.'" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button>
			  <ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="request_action_'.$dataObj->company_nid.'">
				<li>'.l('Accept','onboarding/invite-request/accept/'.$dataObj->requester_company.'/nojs/'.$dataObj->invite_for_projects, array('attributes'=> array('class'=>array('use-ajax')))).'</li>
				<li>'.l('Reject','onboarding/invite-request/reject/'.$dataObj->requester_company.'/nojs/'.$dataObj->invite_for_projects, array('attributes'=> array('class'=>array('use-ajax')))).'</li>
			  </ul>
			</div>
		  </div>';
}

function onboarding_new_request_action_callback($action,$requesterCompanyNode, $ajax=NULL,$projectid=0){
  global $company;
  $commands = array();
  $validAction = in_array($action, array('accept','reject'));
  $updatedCount = 0;
  
  if($validAction){
	$actionindex = ($action=='accept')?1:2;
	/*$updatedCount = db_update('m6connect_invite_users_onboarding')
	  ->fields(array('approval_status'=>$actionindex))
	  ->condition('company_nid',$requesterCompanyNode->nid,'=') 
	  ->condition('invited_comp',$company->nid,'=') 
	  ->condition('approval_status',0,'=')  
	  ->execute(); */
	  
	  
	  $query = db_update('m6connect_onboarding_invite');
	  $query->fields(array('approval_status'=>1));
	  $query->condition('approval_status',0,'=');	
      $query->condition('invite_status',1,'=');
	  $query->condition('requestee_company',$company->nid,'=');
	  if($projectid!=0){
		$query->condition('invite_for_projects',$projectid,'='); 
	  }else{
		$query->condition('invite_for_projects','');   
	  }
      $updatedCount = $query->execute();
   }
  if($ajax){
	ctools_include('ajax');
	//$commands[] = ajax_command_alert($action);
	if($updatedCount >0 && $validAction){
	  $commands[] = ajax_command_html('.new_request_form_company_section',get_onboarding_new_request_content2());
	  $requester_project_title='';
	  if($projectid!=0 && is_numeric($projectid)){
	    $requester_project_title =  _get_title_of_node($projectid);
	  }
	  $dataObj = (object)array('requester_company'=>$requesterCompanyNode->nid,'requester_company_title'=>$requesterCompanyNode->title,'invite_for_projects'=>$projectid,'requester_project_title'=>$requester_project_title);
	  
	  $commands[] = ajax_command_remove('.accepted_request_container_main_container .accepted_request_content accepted_request_content_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects);
	  $commands[] = ajax_command_append('.accepted_request_container_main_container',accept_company_request_get_data_callback($dataObj));	
	}
	print ajax_render($commands);
    drupal_exit();
  }
  drupal_goto('onboarding/submit-employees');
}

function accept_company_request_get_data_callback($dataObj){
  $elements = array();
  if(empty($dataObj->invite_for_projects)){
	$dataObj->invite_for_projects =0;  
  }
  $elements['accepted_request_container']['accepted_request_container_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects] = array(
	'#type'=> 'markup',
	'#markup' => drupal_render(drupal_get_form('get_accepted_company_submit_employess_form',$dataObj)),
	'#prefix' => '<div class="accepted_request_content accepted_request_content_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects.'">',
	'#suffix' => '</div>',
  );
  return drupal_render($elements);
}

function get_accepted_company_submit_employess_form($form,&$form_state,$dataObj){
  global $company;
  $form = array();
  $form['#action'] = url('onboarding/submit-employees');
  $form['#attributes'] = array('class'=>array('get_accepted_company_submit_employess_form'),'id'=>'get_accepted_company_submit_employess_form_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects);
  $fieldsetTitle = $dataObj->requester_company_title; 
  if($dataObj->invite_for_projects && !empty($dataObj->requester_project_title)){
	$fieldsetTitle .= ' for Project - '.$dataObj->requester_project_title;  
  }
  $form['fieldset_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects] = array(
    '#type' => 'fieldset',
	'#title' => $fieldsetTitle,
	'#attributes' => array('class' => array('collapsible', 'collapsed')),
	'#attached' => array('js' => array('misc/form.js', 'misc/collapse.js')),
	'#collapsible' => TRUE, 
    '#collapsed' => TRUE,
  );
  /*$query->fields('u',array('uid','mail'));
  $query->fields('n',array('nid'));
  $query->fields('og',array('gid'));
  $query->fields('m6id',array('field_m6id_value'));
  $query->fields('fname',array('field_first_name_value'));
  $query->fields('lname',array('field_last_name_value'));
  $query->fields('ous',array('employee_id','health_screen','background_check','status'));*/
  
  $header = array(
    'field_m6id' => array('data'=>'M6ID Number', 'class'=> array('text-center','no-sort')),
	'field_empId' => array('data'=>'Employee ID', 'class'=> array('text-center')),
	'field_fname' => array('data'=>'First Name', 'class'=> array('text-center')),
	'field_lname' => array('data'=>'Last Name', 'class'=> array('text-center')),
	'field_email' => array('data'=>'Email', 'class'=> array('text-center','no-sort')),
	'field_hscreen' => array('data'=>'Health Screen', 'class'=> array('text-center')),
	'field_bcheck' => array('data'=>'Background Check', 'class'=> array('text-center')),
	'field_status' => array('data'=>'Status', 'class'=> array('text-center')),
	'field_action' => array('data'=>'Action', 'class'=> array('text-center','no-sort')),
  );
  
  $options = array();
  $userDetails = get_onboarding_company_employess_details($header);
  $submitedUsersUids = get_onboarding_submmited_user_uids($dataObj->requester_company,$company->nid,$dataObj->invite_for_projects);
  $submitedUser = array();
  foreach($userDetails as $delta => $details){
	$health_screen = (is_numeric($details->health_screen))?($details->health_screen==0)?'Fail':'Pass':'';
	$background_check = (is_numeric($details->background_check))?($details->background_check==0)?'Fail':'Pass':'';
	$statsText = array(1=>'Approve',0=>'Rejected',2=>'Pending');
	$status = '';
	if(is_numeric($details->status) && in_array($details->status, array(0,1,2))){
	  $status = $statsText[$details->status];
	}
	$submitedUser[$details->uid] = FALSE;
	$actionButton = '';
	if(in_array($details->uid,$submitedUsersUids)){
	  $submitedUser[$details->uid] = TRUE;	
	  $actionButton = get_onboarding_submit_employees_action_button($details->uid,$dataObj->requester_company,$dataObj->invite_for_projects);
	}
	$options[$details->uid] = array(  
	  'field_m6id' => array('data'=> l($details->field_m6id_value,'/user-m6id-info/'.$details->uid.'/'.$company->nid.'/nojs',array('attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-onboarding-m6id-popup-style')))), 'class'=> array('text-center')),
	  'field_empId' => array('data'=>$details->employee_id, 'class'=> array('text-center')),
	  'field_fname' => array('data'=>$details->field_first_name_value, 'class'=> array('text-center')),
	  'field_lname' => array('data'=>$details->field_last_name_value, 'class'=> array('text-center')),
	  'field_email' => array('data'=>$details->mail, 'class'=> array('text-center')),
	  'field_hscreen' => array('data'=>$health_screen, 'class'=> array('text-center')),
	  'field_bcheck' => array('data'=>$background_check, 'class'=> array('text-center')),
	  'field_status' => array('data'=>$status, 'class'=> array('text-center')),
	  'field_action' => array('data'=>$actionButton, 'class'=> array('text-center')),
	);
  }
  
  $form['fieldset_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects]['companyusertable'] = array(
    '#type' => 'tableselect',
	'#attributes' => array('class'=> array('table','table-hover','table-bordered','text-center','onboarding_submit_employeee_table','onboarding_submit_employeee_check_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects),), //'m6connect-custom-table'
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Employeee Submitted Onboarding Form yet.'),
	'#js_select' => FALSE,
	'#default_value' => $submitedUser,
  );
  
  $form['fieldset_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects]['requester-company'] = array(
    '#type' => 'value',
	'#value' => $dataObj->requester_company,
  );
  
  $form['fieldset_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects]['requester-project'] = array(
    '#type' => 'value',
	'#value' => $dataObj->invite_for_projects,
  );
  
  if(!empty($options)){
	$form['fieldset_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects]['action-container']= array(
	  '#type' => 'actions',
	  //'#attributes' => array('class'=> array('pull-left')),
	  
	);
	
	$form['fieldset_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects]['action-container']['submit']= array(
	  '#type' => 'submit',
	  '#value' => 'Submit',
	  '#name' => 'submit_'.$dataObj->requester_company.'_'.$dataObj->invite_for_projects,
	  '#ajax' => array(
	    'callback' => 'get_accepted_company_submit_employess_form_submit_handler',
	  ),
	  //'#submit' => array('get_accepted_company_submit_employess_form_submit_handler'),
	);
  }
  return $form;	
}

function get_accepted_company_submit_employess_form_submit_handler(&$form,&$form_state){
  $commands = array();
  ctools_include('ajax');
  ctools_include('modal');
  global $company;
  $values = $form_state['values'];
  $requesterCompany = $values['requester-company'];
  $requesterProject = $values['requester-project'];
  if(empty($requesterProject)){
	$requesterProject=NULL;  
  }
  $submitedUsers = array_values($values['companyusertable']);
  $submitedUsers = array_filter($submitedUsers);
  if(is_numeric($requesterCompany) && is_numeric($company->nid)){
	if(!empty($submitedUsers)){
	  foreach($submitedUsers as $delta => $userUid){
		$fields = array(
		  'requester_company' => $requesterCompany,
		  'requester_project' =>$requesterProject,
		  'requstee_company' => $company->nid,
		  'requstee_user' => $userUid,
		  'requster_status' => 0,
		  'requstee_status' => 1,
		  'submit_timestamp' => time(),
		);
		
		$keys = array(
		  'requester_company' => $requesterCompany,
		  'requstee_company' => $company->nid,
		  'requstee_user' => $userUid,
		  'requester_project' => $requesterProject,
		);
		db_merge('m6connect_onboarding_request')->key($keys)->fields($fields)->execute();
	  }
	}
	$deleteQuert = db_update('m6connect_onboarding_request')
	  ->fields(array('requstee_status'=>0))
      ->condition('requester_company',$requesterCompany,'=')
	  ->condition('requstee_company',$company->nid,'=');
	if(!empty($submitedUsers)){
	  $deleteQuert->condition('requstee_user',$submitedUsers,'NOT IN');
	}
	$deleteQuert->execute();
  }
  $commands[] = ctools_ajax_command_redirect('onboarding/submit-employees');
  return array('#type' => 'ajax', '#commands' => $commands);
}

function get_onboarding_submit_employees_action_button($userUid, $requesterComapnyNid, $projectId){
  $projectId = empty($projectId)?0:$projectId;
  return '<div class="btn-group onboarding-submit-emp-dropdown-'.$userUid.'">
			<div class="dropdown">
			  <button id="request_action_" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button>
			  <ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="request_action_">
				<li>'.l('Revoke',url('onboarding-requestee-action/revoke-access/'.$userUid.'/'.$requesterComapnyNid.'/'.$projectId.'/nojs'), array('external'=>TRUE,'attributes'=> array('class'=>array('use-ajax')))).'</li>
				<li>'.l('Reminder Email',url('onboarding-requestee-action/reminder-mail/'.$userUid.'/'.$requesterComapnyNid.'/'.$projectId.'/nojs'), array('external'=>TRUE,'attributes'=> array('class'=>array('use-ajax')))).'</li>
			  </ul>
			</div>
		  </div>';
}

function get_onboarding_submmited_user_uids($requesterCompany,$requsteeCompany,$requesterProject){
  $query = db_select('m6connect_onboarding_request','mor');	
  $query->fields('mor',array('requstee_user'));
  $query->condition('mor.requester_company',$requesterCompany,'=');
  $query->condition('mor.requstee_company',$requsteeCompany,'=');
  $query->condition('mor.requstee_status',1,'=');
  if($requesterProject){
	$query->condition('mor.requester_project',$requesterProject,'=');  
  }else{
	$query->condition('mor.requester_project',NULL);  
  }
  return $query->execute()->fetchCol();
}


function onboarding_requestee_employeee_action_callback($action,$userUid,$requesterComapny,$projectid,$ajax=NULL){
  global $company;
  ctools_include('ajax');
  $commands = array();
  //print 'Project id => '.$projectid; echo '<br>';
  //print 'userUid => '.$userUid; echo '<br>';
  //print 'requesterComapny => '.$requesterComapny->nid; echo '<br>';
  //print 'requesteeComapny => '.$company->nid; echo '<br>';
  //die;
  if(is_numeric($userUid) && $requesterComapny->type=='organization'){
    if($action == 'revoke-access'){
	 
	  $db_update = db_update('m6connect_onboarding_request')
		  ->fields(array('requstee_status'=>0,'requster_status'=>0))
		  ->condition('requester_company',$requesterComapny->nid,'=')
		  ->condition('requstee_company',$company->nid,'=')
		  ->condition('requstee_user',$userUid,'=');
	  if($projectid && is_numeric($projectid)){
	    $db_update->condition('requester_project',$projectid,'='); 
	  }else{
		$db_update->condition('requester_project',NULL);   
	  }
	  $deleteQuery = $db_update->execute();
	  //drupal_set_message($deleteQuery);
	  if($deleteQuery == 1){
	    $commands[] = ajax_command_invoke('table.onboarding_submit_employeee_check_'.$requesterComapny->nid.'_'.$projectid.' input[value="'.$userUid.'"]','removeAttr',array('checked')); 
		$commands[] = ajax_command_remove('table.onboarding_submit_employeee_check_'.$requesterComapny->nid.'_'.$projectid.' .onboarding-submit-emp-dropdown-'.$userUid);		
	  }
	}else if($action=='reminder-mail'){
	  $commands[] = ajax_command_invoke('table.onboarding_submit_employeee_check_'.$requesterComapny->nid.'_'.$projectid.' div.dropdown','removeClass',array('open'));	
	}
  }
  if($ajax){
	print ajax_render($commands);
    drupal_exit();  
  }else{
	drupal_goto('onboarding/submit-employees');
  }
}

/********** End Onboarding Submit_Employees **********/

/********** Start Onboarding In Process **********/

function onboarding_in_process_callback(){
  $elements = array();
  onboarding_message_ctools_popup_style();
  onboarding_m6id_ctools_popup_style();
  $elements['accepted_request_container'] = array(
    '#type'=> 'container',
	'#attributes' => array('class'=> array('accepted_request_container_main_container')),
	'#prefix' => '<div id="in_process_container_main">',
    '#suffix' => '</div>',
  );
  //'<div id="new_request_container_main"><div class="onboarding-container-label onboarding-table-label">In-Process Companies:</div>
  /*$rows = get_onboarding_in_process_content_rows();
  if(!empty($rows)){
    foreach($rows as $requesterCompanyNid => $dataObj){ 
	  $elements['accepted_request_container']['company_fieldset_'.$requesterCompanyNid] = array(
		'#type' => 'fieldset',
		'#title' => $dataObj['title'],
		'#attributes' => array('class' => array('collapsible', 'collapsed')),
		'#attached' => array('js' => array('misc/form.js', 'misc/collapse.js')),
		'#collapsible' => TRUE, 
		'#collapsed' => TRUE,
	  );
	  $elements['accepted_request_container']['company_fieldset_'.$requesterCompanyNid]['inprocess_data_'.$requesterCompanyNid]= array(
	    '#markup' => theme('table', array('header' => $header, 'rows' => $dataObj['row'], 'empty' => 'No Onboarding Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center')))),
		'#prefix' => '<div class="onboarding-in-process-data">',
		'#suffix' => '</div>'
	  );	
	}
  }else{
	$elements['accepted_request_container']['company_fieldset_container'] = array(
      '#markup' => theme('table', array('header' => $header, 'rows' => array(), 'empty' => 'No Onboarding Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center')))),
	  '#prefix' => '<div class="onboarding-in-process-data">',
	  '#suffix' => '</div>',
    );  
  }*/
  
  $quicktabs = quicktabs_build_quicktabs('onboarding_in_process_tabs');
  $elements['accepted_request_container']['qtmakup'] = array(
    '#markup' => render($quicktabs),
  );
  return $elements;	
}

function onboarding_inprocess_company_tab_content(){
  $elements = array();
  ///////////////////// message notification start //////////////////////////////
  $new_cnt_data = ''; 
  /*$new_count = check_onboarding_message_status();
  if($new_count) {
	$new_cnt_data = '<span class="onboarding-notification-count">'.$new_count.'</span>';  
  }*/
  ///////////////////// message notification end //////////////////////////////
  $header = array(
    array('data'=>'Submitted/ Received', 'class'=> array('text-center')),
    array('data'=>'M6ID Number', 'class'=> array('text-center')),
	array('data'=>'Badge Number', 'class'=> array('text-center')),
	array('data'=>'Project', 'class'=> array('text-center')),
	array('data'=>'Contact Information', 'class'=> array('text-center')),
	array('data'=>'Health Screen', 'class'=> array('text-center')),
	array('data'=>'Background Check', 'class'=> array('text-center')),
	array('data'=>'Action', 'class'=> array('text-center')),
	array('data'=>'Message'.$new_cnt_data, 'class'=> array('text-center ob-message-cls')),
  );
  $rows = get_onboarding_in_process_company_content_rows();
  if(!empty($rows)){
    foreach($rows as $requesterCompanyNid => $dataObj){ 
	  $elements['company_fieldset_'.$requesterCompanyNid] = array(
		'#type' => 'fieldset',
		'#title' => $dataObj['title'],
		'#attributes' => array('class' => array('collapsible', 'collapsed')),
		'#attached' => array('js' => array('misc/form.js', 'misc/collapse.js')),
		'#collapsible' => TRUE, 
		'#collapsed' => TRUE,
	  );
	  $elements['company_fieldset_'.$requesterCompanyNid]['inprocess_data_'.$requesterCompanyNid]= array(
	    '#markup' => theme('table', array('header' => $header, 'rows' => $dataObj['row'], 'empty' => 'No M6ID Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center')))),
		'#prefix' => '<div class="onboarding-in-process-data">',
		'#suffix' => '</div>'
	  );	
	}
  }else{
	$elements['company_fieldset_container'] = array(
      '#markup' => theme('table', array('header' => $header, 'rows' => array(), 'empty' => 'No M6ID Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center')))),
	  '#prefix' => '<div class="onboarding-in-process-data">',
	  '#suffix' => '</div>',
    );  
  }
  return $elements;	
}

function get_onboarding_in_process_company_content_rows(){
  global $company;	
  $rows = array();
  $userDetails = onboarding_in_process_company_user_details();
  if($userDetails && is_array($userDetails)){
	foreach($userDetails as $delta => $dataObj){
	  $health_screen = (is_numeric($dataObj->health_screen))?($dataObj->health_screen==0)?'Fail':'Pass':'';
	  $background_check = (is_numeric($dataObj->background_check))?($dataObj->background_check==0)?'Fail':'Pass':'';	
	  $submiteddata = (isset($company->nid) && $company->nid == $dataObj->requstee_company)? 'Submitted' :'Received';
	  $companyArrayNid = $dataObj->requester_company;
	  $companyArrayTitle = $dataObj->requester_company_title;
	  if($companyArrayNid == $company->nid){
		$companyArrayNid = $dataObj->requstee_company; 
		$companyArrayTitle = $dataObj->requstee_company_title; 
	  }
	  $rows[$companyArrayNid]['row'][] = array(
		'data'=>array( 
		  array('data'=>$submiteddata, 'class'=> array('text-center')),
		  array('data'=> l($dataObj->field_m6id_value,'/user-m6id-info/'.$dataObj->requstee_user.'/'.$dataObj->requstee_company.'/nojs',array('attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-onboarding-m6id-popup-style')))), 'class'=> array('text-center')),
		  array('data'=> ($submiteddata == 'Received')?drupal_render(drupal_get_form('onboarding_badge_form',$dataObj)): $dataObj->badge_number, 'class'=> array('text-center')),
		  array('data'=>$dataObj->requester_project_title, 'class'=> array('text-center')),
		  array('data'=>$dataObj->realname. ' '. $dataObj->field_phone_value. ' '.$dataObj->mail, 'class'=> array('text-center')),
		  array('data'=>$health_screen, 'class'=> array('text-center')),
		  array('data'=>$background_check, 'class'=> array('text-center')),
		  //array('data'=>drupal_render(drupal_get_form('onboarding_inprocess_employee_status_form',$dataObj, $submiteddata)), 'class'=> array('text-center')),
		  array('data'=>get_onboarding_in_process_action_button($dataObj,$company), 'class'=> array('text-center')),
		  array('data'=>l(t('<div class="onboarding-msg-icon"><img src="'.$base_url.'/sites/all/themes/m6connect/images/ins-msg-notify.png" /></div>'),'onboarding-message/'.$dataObj->requester_company.'/'.$dataObj->requstee_company.'/'.$dataObj->requstee_user.'/'.$dataObj->id.'/nojs', array('html' => TRUE,'attributes'=>array('class'=>array('ctools-use-modal','ctools-modal-onboarding-message-popup-style')))), 'class'=> array('text-center')),
		),
		'class'=>array('tr-in-process-'.$dataObj->id),
	  );
	  $rows[$companyArrayNid]['title'] = $companyArrayTitle;	
	}
  }
  
  return $rows;
  
  //return theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No Onboarding Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center'))));	
}

function onboarding_in_process_company_user_details(){
  global $company;
  $query = db_select('m6connect_onboarding_request','mor');
  $query->join('users','u','u.uid=mor.requstee_user');
  $query->join('realname','r','r.uid=u.uid');
  $query->join('node','apr','apr.nid=mor.requester_company');
  $query->join('node','isr','isr.nid=mor.requstee_company');
  $query->leftjoin('node','psr','psr.nid=mor.requester_project');
  $query->leftjoin('field_data_field_phone','fp','fp.entity_id=u.uid AND fp.bundle=:UserBundle', array(':UserBundle'=>'user'));	
  $query->leftjoin('m6connet_onboarding_colleagues_status','ous','ous.user_uid=u.uid AND ous.company_nid=mor.requstee_company');
  $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=u.uid AND m6id.bundle=:userBundle', array(':userBundle'=>'user')); 
  $query->fields('mor');
  $query->fields('u',array('mail'));
  $query->fields('r',array('realname'));
  $query->addField('apr','title','requester_company_title');
  $query->addField('isr','title','requstee_company_title');
  $query->addField('psr','title','requester_project_title');
  $query->fields('fp',array('field_phone_value'));
  $query->fields('ous',array('employee_id','badge_number','health_screen','background_check','status'));
  $query->fields('m6id',array('field_m6id_value'));
  
  $db_or = db_or()->condition('mor.requester_company',$company->nid)->condition('mor.requstee_company',$company->nid);
  $query->condition($db_or);
  $query->condition('mor.requstee_status',1,'=');
  $query->orderBy('mor.requester_company','ASC');
  $result = $query->execute()->fetchAll();
  return $result;
}

function onboarding_inprocess_project_tab_content(){
  $elements = array();
  $header = array(
    array('data'=>'Submitted/ Received', 'class'=> array('text-center')),
    array('data'=>'M6ID Number', 'class'=> array('text-center')),
	array('data'=>'Badge Number', 'class'=> array('text-center')),
	array('data'=>'Company', 'class'=> array('text-center')),
	array('data'=>'Contact Information', 'class'=> array('text-center')),
	array('data'=>'Health Screen', 'class'=> array('text-center')),
	array('data'=>'Background Check', 'class'=> array('text-center')),
	array('data'=>'Action', 'class'=> array('text-center')),
	array('data'=>'Message', 'class'=> array('text-center ob-message-cls')),
  );
  $rows = get_onboarding_in_process_project_content_rows();
  if(!empty($rows)){
    foreach($rows as $requesterCompanyNid => $dataObj){ 
	  $elements['company_fieldset_'.$requesterCompanyNid] = array(
		'#type' => 'fieldset',
		'#title' => $dataObj['title'],
		'#attributes' => array('class' => array('collapsible', 'collapsed')),
		'#attached' => array('js' => array('misc/form.js', 'misc/collapse.js')),
		'#collapsible' => TRUE, 
		'#collapsed' => TRUE,
	  );
	  $elements['company_fieldset_'.$requesterCompanyNid]['inprocess_data_'.$requesterCompanyNid]= array(
	    '#markup' => theme('table', array('header' => $header, 'rows' => $dataObj['row'], 'empty' => 'No M6ID Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center')))),
		'#prefix' => '<div class="onboarding-in-process-data">',
		'#suffix' => '</div>'
	  );	
	}
  }else{
	$elements['company_fieldset_container'] = array(
      '#markup' => theme('table', array('header' => $header, 'rows' => array(), 'empty' => 'No M6ID Request Submited/Received yet','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-onboarding-in-process-table','table-hover','table-bordered','text-center')))),
	  '#prefix' => '<div class="onboarding-in-process-data">',
	  '#suffix' => '</div>',
    );  
  }
  return $elements;		
}

function get_onboarding_in_process_project_content_rows(){
  global $company;	
  $rows = array();
  $userDetails = onboarding_in_process_project_user_details();
  if($userDetails && is_array($userDetails)){
	foreach($userDetails as $delta => $dataObj){
	  $health_screen = (is_numeric($dataObj->health_screen))?($dataObj->health_screen==0)?'Fail':'Pass':'';
	  $background_check = (is_numeric($dataObj->background_check))?($dataObj->background_check==0)?'Fail':'Pass':'';	
	  $submiteddata = (isset($company->nid) && $company->nid == $dataObj->requstee_company)? 'Submitted' :'Received';
	  $companyArrayNid = $dataObj->requester_company;
	  $companyArrayTitle = $dataObj->requester_company_title;
	  $projectArrayNid = $dataObj->requester_project;
	  $projectArrayTitle = $dataObj->requester_project_title;
	  if($companyArrayNid == $company->nid){
		$companyArrayNid = $dataObj->requstee_company; 
		$companyArrayTitle = $dataObj->requstee_company_title; 
	  }
	  $rows[$projectArrayNid]['row'][] = array(
		'data'=>array( 
		  array('data'=>$submiteddata, 'class'=> array('text-center')),
		  array('data'=> l($dataObj->field_m6id_value,'/user-m6id-info/'.$dataObj->requstee_user.'/'.$dataObj->requstee_company.'/nojs',array('attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-onboarding-m6id-popup-style')))), 'class'=> array('text-center')),
		  array('data'=> ($submiteddata == 'Received')?drupal_render(drupal_get_form('onboarding_badge_form',$dataObj)): $dataObj->badge_number, 'class'=> array('text-center')),
		  array('data'=>$companyArrayTitle, 'class'=> array('text-center')),
		  array('data'=>$dataObj->realname. ' '. $dataObj->field_phone_value. ' '.$dataObj->mail, 'class'=> array('text-center')),
		  array('data'=>$health_screen, 'class'=> array('text-center')),
		  array('data'=>$background_check, 'class'=> array('text-center')),
		  array('data'=>get_onboarding_in_process_action_button($dataObj,$company), 'class'=> array('text-center')),
		  array('data'=>l(t('<div class="onboarding-msg-icon"><img src="'.$base_url.'/sites/all/themes/m6connect/images/ins-msg-notify.png" /></div>'),'onboarding-message/'.$dataObj->requester_company.'/'.$dataObj->requstee_company.'/'.$dataObj->requstee_user.'/'.$dataObj->id.'/nojs', array('html' => TRUE,'attributes'=>array('class'=>array('ctools-use-modal','ctools-modal-onboarding-message-popup-style')))), 'class'=> array('text-center')),
		),
		'class'=>array('tr-in-process-'.$dataObj->id),
	  );
	  $rows[$projectArrayNid]['title'] = $projectArrayTitle;	
	}
  }
  
  return $rows;	
}

function onboarding_in_process_project_user_details(){
  global $company;
  $query = db_select('m6connect_onboarding_request','mor');
  $query->join('users','u','u.uid=mor.requstee_user');
  $query->join('realname','r','r.uid=u.uid');
  $query->join('node','apr','apr.nid=mor.requester_company');
  $query->join('node','isr','isr.nid=mor.requstee_company');
  $query->join('node','psr','psr.nid=mor.requester_project');
  $query->leftjoin('field_data_field_phone','fp','fp.entity_id=u.uid AND fp.bundle=:UserBundle', array(':UserBundle'=>'user'));	
  $query->leftjoin('m6connet_onboarding_colleagues_status','ous','ous.user_uid=u.uid AND ous.company_nid=mor.requstee_company');
  $query->leftjoin('field_data_field_m6id','m6id','m6id.entity_id=u.uid AND m6id.bundle=:userBundle', array(':userBundle'=>'user')); 
  $query->fields('mor');
  $query->fields('u',array('mail'));
  $query->fields('r',array('realname'));
  $query->addField('apr','title','requester_company_title');
  $query->addField('isr','title','requstee_company_title');
  $query->addField('psr','title','requester_project_title');
  $query->fields('fp',array('field_phone_value'));
  $query->fields('ous',array('employee_id','badge_number','health_screen','background_check','status'));
  $query->fields('m6id',array('field_m6id_value'));
  
  $db_or = db_or()->condition('mor.requester_company',$company->nid)->condition('mor.requstee_company',$company->nid);
  $query->condition($db_or);
  $query->condition('mor.requstee_status',1,'=');
  $query->orderBy('mor.requester_company','ASC');
  $result = $query->execute()->fetchAll();
  return $result;
}

function get_onboarding_in_process_action_button($dataObj,$company){
  $action  = '<div class="btn-group onboarding-in-process-dropdown-'.$dataObj->id.'"><div class="dropdown">';
  if($company->nid == $dataObj->requstee_company){
	$action .= '<button id="request_action_'.$dataObj->id.'" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button>';
    $action .= '<ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="request_action_'.$dataObj->id.'">';
	$class = array(0=> array('use-ajax','revoke-access'),1=> array('use-ajax','submit-access'));
	if(is_numeric($dataObj->requstee_status)){
	  $class[$dataObj->requstee_status][] = 'access-active';
	}
    $action .= '<li>'.l('Revoke',url('onboarding-inprocess-action/revoke-access/'.$dataObj->id.'/nojs'), array('attributes'=> array('class'=>$class[0]))).'</li>';
	$action .= '<li>'.l('Submit',url('onboarding-inprocess-action/submit-access/'.$dataObj->id.'/nojs'), array('attributes'=> array('class'=>$class[1]))).'</li>'; 
	$action .= '<li>'.l('View Details','user-m6id-detail-info/'.$dataObj->requstee_user.'/nojs', array('attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-assign-dashboard-popup-style')))).'</li>'; 
	$action .= '</ul>';
  }else{
	$class = array(1=> array('use-ajax','approve-access'),2=> array('use-ajax','reject-access'),3=> array('use-ajax','pending-access'));
	$linkName = array(1=> 'Approve',2=> 'Reject',3=>'Pending');
	$actionStatusClass = array(1=> 'btn btn-success',2=> 'btn btn-danger',3=>'btn btn-warning');
	$actionButtonClass = '';
	if(is_numeric($dataObj->requster_status)){
	  $class[$dataObj->requster_status][] = 'access-active';
	  $actionButtonClass = $actionStatusClass[$dataObj->requster_status]; 
	}
	if(empty($actionButtonClass)){
	  $actionButtonClass = 'btn btn-primary';	
	}
	$action .= '<button id="request_action_'.$dataObj->id.'" class="'.$actionButtonClass.'" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button>';
    $action .= '<ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="request_action_'.$dataObj->id.'">';
	$action .= '<li>'.l($linkName[1],url('onboarding-inprocess-action/approve-access/'.$dataObj->id.'/nojs'), array('attributes'=> array('class'=>$class[1]))).'</li>';
	$action .= '<li>'.l($linkName[2],url('onboarding-inprocess-action/reject-access/'.$dataObj->id.'/nojs'), array('attributes'=> array('class'=>$class[2]))).'</li>';
	$action .= '<li>'.l($linkName[3],url('onboarding-inprocess-action/pending-access/'.$dataObj->id.'/nojs'), array('attributes'=> array('class'=>$class[3]))).'</li>'; 
	$action .= '<li>'.l('View Details','user-m6id-detail-info/'.$dataObj->requstee_user.'/nojs', array('attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-assign-dashboard-popup-style')))).'</li>';
	$action .= '</ul>';  
  }
  $action .= '</div></div>';
  return $action;
}

function onboarding_inprocess_action_callback($action,$dataId,$ajax=NULL){
  global $company;
  $commands = array();
  $insideUpdate= 0;
  $requestObj = '';
  if(in_array($action,array('revoke-access','submit-access','approve-access','reject-access','pending-access')) && is_numeric($dataId)){
	$requestObj = db_select('m6connect_onboarding_request','mor')->fields('mor')->condition('mor.id',$dataId,'=')->execute()->fetchObject();
	if($requestObj && is_object($requestObj)){
	  $updateFields =array();
	  switch($action){
		case 'revoke-access':
		  $updateFields= array('requstee_status'=>0,'requster_status'=>0);
		  break;
		case 'submit-access':
		  $updateFields= array('requstee_status'=>1);
		  break;
		case 'approve-access':
		  $updateFields= array('requster_status'=>1);
		  break;
		case 'reject-access':
		  $updateFields= array('requster_status'=>2);
		  break;
		case 'pending-access':
		  $updateFields= array('requster_status'=>3);
		  break;  
	  }
	  if(!empty($updateFields)){
		db_update('m6connect_onboarding_request')->fields($updateFields)->condition('id',$dataId,'=')->execute();
		$insideUpdate =1;  
	  }
	}
  }
  if($ajax){
	ctools_include('ajax');
	$commands[] = ajax_command_invoke('table.m6connect-onboarding-in-process-table div.dropdown','removeClass',array('open'));
	if($insideUpdate){
	  if($action!='revoke-access'){
	    $commands[] = ajax_command_invoke('.onboarding-in-process-dropdown-'.$dataId.' ul.dropdown-menu li a','removeClass',array('access-active'));
	    $commands[] = ajax_command_invoke('.onboarding-in-process-dropdown-'.$dataId.' ul.dropdown-menu li a.'.$action,'addClass',array('access-active'));
		if(in_array($action, array('approve-access','reject-access','pending-access'))){
		  $actionStatusClass = array(1=> 'btn-success',2=> 'btn-danger',3=>'btn-warning');
		  $class = $actionStatusClass[$updateFields['requster_status']];
		  $commands[] = ajax_command_invoke('.onboarding-in-process-dropdown-'.$dataId.' div.dropdown button','removeAttr',array('class'));
		  $commands[] = ajax_command_invoke('.onboarding-in-process-dropdown-'.$dataId.' div.dropdown button','addClass',array('btn'));
		  $commands[] = ajax_command_invoke('.onboarding-in-process-dropdown-'.$dataId.' div.dropdown button','addClass',array($class));
		}
	  }else{
		 $commands[] = ajax_command_remove('table.m6connect-onboarding-in-process-table tr.tr-in-process-'.$dataId); 
	  }
	}
	print ajax_render($commands);
    drupal_exit();  
  }
  drupal_goto('onboarding/in-process');  	
}

function onboarding_badge_form($form,$form_state,$dataObj){
  $form['#attributes'] = array('class'=>'onboarding_badge_form');
  
  $form['company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->requstee_company,
  );
  
  $form['user_uid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->requstee_user,
  );
  
  $form['badge'] = array(
    '#type' => 'textfield',
	'#title' => 'Badge',
	'#title_display' => 'invisible',
	'#size' => 15,
	'#default_value'=> $dataObj->badge_number,
	'#ajax' => array(
		'callback' => 'modify_onboarding_badge_callcack',
		'effect' => 'fade',
		//'progress' => array('type'=> 'throbber', 'message'=> NULL),
	),  
  );
  
  return $form;
}

function modify_onboarding_badge_callcack($form,&$form_state){
  $commands = array();
  $values = $form_state['values'];
  if(isset($values['company_nid'],$values['user_uid'],$values['badge']) && !empty($values['company_nid']) && !empty($values['user_uid'])){
    db_merge('m6connet_onboarding_colleagues_status')->key(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid']))->fields(array('company_nid'=>$values['company_nid'],'user_uid'=>$values['user_uid'],'badge_number'=>$values['badge']))->execute();
  }
  return array('#type' => 'ajax', '#commands' => $commands);	
}

function onboarding_inprocess_employee_status_form($form,$form_state,$dataObj, $issubmitted){
  $form['#attributes'] = array('class'=>'onboarding_inprocess_employee_status_form');
  
  $form['requester_company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->requester_company,
  );
  
  $form['company_nid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->requstee_company,
  );
  
  $form['user_uid'] = array(
    '#type' => 'value',
	'#value' => $dataObj->requstee_user,
  );
  
  $form['submitted'] = array(
    '#type' => 'value',
	'#value' => $issubmitted,
  );
  
  $options = array();
  $defvalue = '';
  if($issubmitted == 'Received') {
    $options = array(3=>'Approve',2=>'Reject',4=>'Pending'); 
	$defvalue = $dataObj->requstee_status;
  } elseif ($issubmitted == 'Submitted') {
    $options = array(0=>'Revoke',1=>'Submit');
	$defvalue = $dataObj->requster_status;  
  } 
  
  $form['employee_status'] = array(
    '#type' => 'select',
	'#title' => 'Background Check',
	'#title_display' => 'invisible',
	'#options' => $options,
	'#empty_option' => '- None -',
	'#default_value'=> $defvalue, 
	'#ajax' => array(
		'callback' => 'modify_onboarding_inprocess_employee_status_callcack',
		'effect' => 'fade',
	),
  );
  return $form;
}

function modify_onboarding_inprocess_employee_status_callcack($form,&$form_state){
  $commands = array();
  $values = $form_state['values'];
  
  if(isset($values['requester_company_nid'],$values['company_nid'],$values['user_uid'],$values['employee_status'],$values['submitted']) && !empty($values['requester_company_nid']) && !empty($values['company_nid']) && !empty($values['user_uid'])){
	$requesterCompany = $values['requester_company_nid'];
    $requesteeCompany = $values['company_nid'];
    $requesteeUser = $values['user_uid'];
    $requestStatus = $values['employee_status'];
    $issubmitted = $values['submitted'];  
    
	$query = db_update('m6connect_onboarding_request');
	if($issubmitted == 'Received') {
	  $query->fields(array('requstee_status'=>$requestStatus));
	} elseif ($issubmitted == 'Submitted') {
	  $query->fields(array('requster_status'=>$requestStatus));	
	}
    $query->condition('requester_company',$requesterCompany,'=');
	$query->condition('requstee_company',$requesteeCompany,'=');
	$query->condition('requstee_user',$requesteeUser,'=');
	$update = $query->execute();
  }
  return array('#type' => 'ajax', '#commands' => $commands);	
}

/************************* Start Message System  ********************************/

function onboarding_feedback_content_callback($requester_comp_nid, $requestee_comp_nid, $requestee_user_id, $request_id,$ajax=NULL){
  $elements = onboarding_feedback_content($requester_comp_nid, $requestee_comp_nid, $requestee_user_id, $request_id);
  if($ajax){
	ctools_include('ajax');
    ctools_include('modal');
    $output = array();
	$popup_content = '<div class="onboarding-message-popup">'.drupal_render($elements).'<div class="onboarding-message-popup-close pull-right"><a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click();"><input type="button" class="btn cancel-button" value="Close"></a></div></div>'; 
    $output[] = ctools_modal_command_display('', $popup_content);
    print ajax_render($output);
    drupal_exit();
  }
  return $elements;
}

function onboarding_feedback_content($requester_comp_nid, $requestee_comp_nid, $requestee_user_id, $request_id){ 
  global $user,$company;	
  $elements = array();
  $currentuserLink = '';
  $usertype == 0;
  $submiteddata = '';
  $requestee_master_comp_dtl = array();
  $requester_master_comp_dtl = array();
  drupal_add_library('system', 'ui.dialog'); 
  
  if(isset($company->nid) && $company->nid == $requester_comp_nid) {
    $submiteddata = 'Submitted';
	$usertype = 1;
  } elseif (isset($company->nid) && $company->nid == $requestee_comp_nid) {
    $submiteddata = 'Received';
	$usertype = 2;	
  } 
  $newmsgform = drupal_render(drupal_get_form('common_onboarding_feedback_message_form',$request_id,$usertype));
  $requestee_comp_dtl = get_ins_cert_company_details_by_nid($requestee_comp_nid,$requestee_master_comp_dtl);
  $requester_comp_dtl = get_ins_cert_company_details_by_nid($requester_comp_nid,$requester_master_comp_dtl);  
  if(!$requestee_comp_dtl){
	$requestee_comp_dtl = array('nid' => '', 'title' => '', 'image' => '');
  }
  if(!$requester_comp_dtl){
	$requester_comp_dtl = array('nid' => '', 'title' => '', 'image' => '');
  }
  $requestee_user_detail = '<span class="m6-note-cmp-img">'.$requestee_comp_dtl['image'] . '</span> '.$requestee_comp_dtl['title'];
  $requester_user_detail = '<span class="m6-note-cmp-img">'.$requester_comp_dtl['image'] . '</span> '.$requester_comp_dtl['title'];	
  
  $regardingCompany =  $requestee_comp_dtl['title'];
  $requesteeUser = user_load($requestee_user_id);
  if($requesteeUser && is_object($requesteeUser)){
	$regardingCompany .= ', '.ucwords($requesteeUser->realname);  
  }
  
  $requestee_manager_detail = _get_company_users_with_role_by_onboarding_roles($requestee_comp_nid,array('M6ID Manager','Site Manager'));
  $requesteeuserLink = array();
  $requesteemorethan3 = 0;
  if($requestee_manager_detail && !empty($requestee_manager_detail)){
	foreach($requestee_manager_detail as $delta => $dataObj){
	  if($delta==3){
		$requesteemorethan3 =1;
		break;  
	  }
	  $requesteeuserLink[] = l(ucwords($dataObj->realname).'('.$dataObj->ogroles.')','user/'.$dataObj->uid);
	}  
  }
  
  $requester_manager_detail = _get_company_users_with_role_by_onboarding_roles($requester_comp_nid,array('M6ID Manager','Site Manager'));
  $requesteruserLink = array();
  $requestermorethan3 = 0;
  if($requester_manager_detail && !empty($requester_manager_detail)){
	if($delta==3){
	  $requestermorethan3 =1;
	  break;  
	}
	foreach($requester_manager_detail as $delta => $dataObj){
	  $requesteruserLink[] = l(ucwords($dataObj->realname).'('.$dataObj->ogroles.')','user/'.$dataObj->uid);
	}   
  }
  
  $userShortRole = '';
  $currentUser = user_load($user->uid);
  $currentUserRoles = og_get_user_roles('node', $company->nid, $user->uid);
  $curretUserOBRoles = array();
  if(in_array('Site Manager',$currentUserRoles)){
    $curretUserOBRoles[] = 'SM'; 
  }
  if(in_array('M6ID Manager',$currentUserRoles)){
    $curretUserOBRoles[] = 'MM'; 
  }
  if(!empty($curretUserOBRoles)){
	$userShortRole = '('.implode(',',$curretUserOBRoles).')';  
  }
  $currentuserLink = l(ucwords($currentUser->realname.$userShortRole),'user/'.$currentUser->uid);
  
  if($submiteddata == 'Submitted'){
	$requestee_user_detail .=', <span>' . implode('</span>,&nbsp;<span>',$requesteeuserLink).'</span>';
	$requester_user_detail .= ', <span>'.$currentuserLink.'</span>';  
	if($requesteemorethan3){
	  $requestee_user_detail .= '&nbsp...';
	}
  }else{
	 $requestee_user_detail .= ', <span>'.$currentuserLink.'</span>'; ;
	 $requester_user_detail .=', <span>' . implode('</span>,&nbsp;<span>',$requesteruserLink).'</span>'; 
	 if($requestermorethan3){
	  $requester_user_detail .= '&nbsp...';
	} 
  }
  
  if($submiteddata == 'Submitted') { 	 
  $elements['onboarding_msg'] = array(
    '#markup' => '<div class="appr-feedback-notes-block row">
	                 <div class="ins-feed-notes-title col-sm-12">
					   <div class="ins-notes-title clearfix">
					      <span class="pull-left">M6ID Message</span> 
						  <span class="pull-right">Regarding '.$regardingCompany.'</span>
					   </div>
					 </div>
					 
					 <!--<div class="ins-feed-submitter col-sm-6 padding-5">
                       <div class="ins-feed-sub-title"><span class="sub-title">Submitter</span></div>
                     </div>
                     <div class="ins-feed-approver col-sm-6 padding-5">
                       <div class="ins-feed-sub-title"><span class="sub-title">Receiver</span></div>
                     </div>-->
					 
					 <div class="col-sm-12 margin-bottom-10">
					   <div class="ins-feed-sub-rec-outer-blk clearfix">
					    						 
					     <div class="ins-feed-submitter col-sm-6 padding-0">
					       <div class="ins-sub-detail">
					         <div class="ins-feed-sub-details">'.$requestee_user_detail.'</div>
					         
					       </div>
					       
					     </div> 
					 
					     <div class="ins-feed-approver col-sm-6 padding-0">
					       <div class="ins-appr-detail">
					         <div class="ins-feed-sub-details">'.$requester_user_detail.'</div>
					         
					       </div>
					       
					     </div> 
						 
					   </div>
					 </div>
					 
					 <div class="col-sm-12 margin-bottom-10">'.$newmsgform.'</div>
					
				   </div>'
   );	   
  } elseif($submiteddata == 'Received') { //pre('bbb');
    $elements['onboarding_msg'] = array(
     '#markup' => '<div class="appr-feedback-notes-block row">
	                 <div class="ins-feed-notes-title col-sm-12">
					   <div class="ins-notes-title clearfix">
					      <span class="pull-left">M6ID Message</span> 
						  <span class="pull-right">Regarding '.$regardingCompany.'</span>
					   </div>
					 </div>
					 
					 <!--<div class="ins-feed-submitter col-sm-6 padding-5">
                       <div class="ins-feed-sub-title"><span class="sub-title">Receiver</span></div>
                     </div>
                     <div class="ins-feed-approver col-sm-6 padding-5">
                       <div class="ins-feed-sub-title"><span class="sub-title">Submitter</span></div>
                     </div>-->
					 
					 <div class="col-sm-12 margin-bottom-10">
					   <div class="ins-feed-sub-rec-outer-blk clearfix">
					    						 
					     <div class="ins-feed-submitter col-sm-6 padding-0">
					       <div class="ins-sub-detail">
					         <div class="ins-feed-sub-details">'.$requester_user_detail.'</div>
					         
					       </div>
					       
					     </div> 
					 
					     <div class="ins-feed-approver col-sm-6 padding-0">
					       <div class="ins-appr-detail">
					         <div class="ins-feed-sub-details">'.$requestee_user_detail.'</div>
					         
					       </div>
					       
					     </div> 
						 
					   </div>
					 </div>
					 
					 <div class="col-sm-12 margin-bottom-10">'.$newmsgform.'</div>
					
				   </div>'
     );
  }
  $elements['request_to_intent_dialog'] = array(
    '#markup' => '',
    '#prefix' => '<div id="insurance-reminder-dialog">',
    '#suffix' => '</div>',
  ); 
	
  $elements['change_approver_status_dialog'] = array(
    '#markup' => '',
    '#prefix' => '<div id="change-insurance-status-dialog">',
    '#suffix' => '</div>',
  );
  return $elements; 
}

function common_onboarding_feedback_message_form($form, $form_state,$request_id,$usertype) {
    global $user;
		
    $form = array();
    $form['#attributes'] = array('class' => array('routing_feedback_message_form','rfp_bidder_feedback_message_form'), 'id' => 'routing_feedback_message_form_' . $request_id.'_'.$usertype);

    $form['message-list'] = array(
        '#markup' => get_onboarding_feedback_message_common($request_id,$usertype),
		'#prefix' => '<div id="approval_feedback_message_container_' . $request_id . '_' . $usertype . '">',
        '#suffix' => '</div>',
    );
	
	if($usertype == '1' || $usertype == '2'){		
	  $form['message'] = array(
		  '#type' => 'textfield',
		  '#title' => 'Message',
		  '#title_display' => 'invisible',                                 //here
		  '#attributes' => array('placeholder' => 'Please provide comments', 'id' => 'approval_feedback_message_' . $request_id . '_' . $usertype, 'class' => array('approval_feedback_message_msg','bidder_feedback_message_msg', 'onkeypress' => array('if(event.keyCode==13){this.form.submit();}'))),
		  '#prefix' => '<div>',
		  '#suffix' => '</div>',
		  '#maxlength' => 198,
	  );
	  $form['request_id']= array(
		'#type' => 'value',
		'#value'=> $request_id,
	  );
	  $form['user_type']= array(
		'#type' => 'value',
		'#value'=> $usertype,
	  );
	  
	  $form['add'] = array(
		  '#type' => 'submit',
		  '#value' => 'Add',
		  '#attributes' => array('class' => array('add_new_approval_feedback_message','add_new_bidder_feedback_message')),
		  '#executes_submit_callback' => FALSE,
		  '#limit_validation_errors' => array(),
		  '#href' => '',
		  '#ajax' => array(
			  'callback' => 'add_new_onboarding_feedback_message',
			  'effect' => 'fade',
			  'event' => 'click',
			  'progress' => array('type' => 'none'),
		  ),
		  '#prefix' => '<div id="bidder-feedback-message-button" class="approval_feedback-message-button">',
		  '#suffix' => '</div>',
	  );
	}
    return $form;
}

function add_new_onboarding_feedback_message(&$form,&$form_state){
  global $user;
  $commands = array();
  $output = '';
  $values = $form_state['values'];
  $message = trim($values['message']);
  if (!empty($message) && !empty($values['request_id']) && !empty($values['user_type'])) {
	
	$approval_message= array(
	 'request_id' => $values['request_id'],
	 'user_uid' => $user->uid,
	 'user_type' => $values['user_type'],
	 'message' => $message,
	 'timestamp' => time(),
	);
	$id = db_insert('m6connect_onboarding_feedback_message')->fields($approval_message)->execute();
	
	$output = get_onboarding_feedback_message_common($values['request_id'],$values['user_type']);
	$commands[] = ajax_command_invoke('#approval_feedback_message_'.$values['request_id'].'_'.$values['user_type'],'val', array(''));
    $commands[] = ajax_command_html('#approval_feedback_message_container_'.$values['request_id']. '_' .$values['user_type'], $output);
	//$commands[] = array("command" => 'insuranceOfNoticeDailog', 'message'=> $message,'request_id' => $values['user_type']);
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function get_onboarding_feedback_message_common($requestid,$usertype = 0){
  global $user;
  ctools_include('ajax');
  ctools_include('modal');
  if($usertype == '1' || $usertype == '2') {
	$curruserclass = 'cuser-is-submitter-approver';  
  } else {
	$curruserclass = 'cuser-not-submitter-approver';  
  }
  $output = '<div class="bidder-feedback-msg-list '.$curruserclass.' clearfix">';
  if (db_table_exists('m6connect_onboarding_feedback_message')) {
	  $query = db_select('m6connect_onboarding_feedback_message', 'rfm');
	  $query->join('realname', 'r', 'r.uid=rfm.user_uid');
	  $query->fields('rfm', array('id', 'message','message_prefix', 'timestamp','user_uid','user_type'));
	  $query->fields('r', array('realname'));
	  $query->condition('rfm.request_id', $requestid, '=');
	  $query->orderBy('rfm.timestamp', 'ASC');
	  $result = $query->execute()->fetchAll();
	  if ($result && !empty($result)) {
		foreach ($result as $delta => $msgObj) {
		  $messagePrifix =$msgObj->message_prefix;
		  if(!empty($messagePrifix)){
			$messagePrifix = ' '.$messagePrifix;  
		  }
		  if($usertype == '1' || $usertype == '2') {
			  if($usertype == $msgObj->user_type) {	
				$alignclass = 'feedback-msg-writer';
			  } else {
				$alignclass = 'feedback-msg-reader'; 
			  }
			//}
		    $output .= '<div class="bidder-feedback-msg routing-feedback-msg-' . $msgObj->id . ' clearfix '.$alignclass.'">';
		  } else { 
			if($msgObj->user_type == '2') {
			  $alignclass = 'feedback-msg-writer';	
			} elseif($msgObj->user_type == '1'){
			  $alignclass = 'feedback-msg-reader';
			}
			//dsm($alignclass);  
			$output .= '<div class="bidder-feedback-msg routing-feedback-msg-' . $msgObj->id . ' clearfix '.$alignclass.'">';
		  }
		  
		  $output .= '<div class="bidder-feedback-msg-attr pull-left">';
		  $user_obj = user_load($msgObj->user_uid);
		  $imgpath = isset($user_obj->field_user_profile_photo['und']['0']['uri'])?$user_obj->field_user_profile_photo['und']['0']['uri']:'public://default_images/images_13_0_0.png';
		  $imgurl =  image_style_url('user_pic_40x40',$imgpath);
		  $userimg = '<img src="'.$imgurl.'">';

		  $output .= '<span class="bidder-feedback-msg-time"><span class="msg-aut-img">'.$userimg.'</span></span>';
		  $output .= '<span class="bidder-feedback-msg-msg"><strong>' .$msgObj->realname. '</strong> '.date('m/d/Y h:i A', $msgObj->timestamp) . ' '.$messagePrifix.' - ' . $msgObj->message . '</span>';
		  $output .= '</div>';
          if($user->uid == $msgObj->user_uid){	  
		    $output .= '<div class="bidder-feedback-msg-delete">'; //new design

			$output .= l('<i class="fa fa-times-circle"></i>', '', array('html' => TRUE, 'attributes' => array('class' => array('bidder-feedback-msg-delete-link', 'use-ajax'))));
		    $output .= '</div>';
		  }
		  $output .= '</div>';
		}
	  }
  }
  $output .= '</div>';
  return $output;	
}

function get_om_sm_by_company_id($cid){
  $return = $om_uids = $sm_uids = array();	
  $companyNode = node_load($cid);	
  $group_roles = og_roles('node', 'organization');	
  $om_rid = $sm_rid = '';
  foreach($group_roles as $grid=> $grole){
	if($grole == 'M6ID Manager') {
	  $om_rid = $grid;	
	} elseif($grole == 'Site Manager') {
	  $om_rid = $grid;	
	}
  }
  $companyUsers = og_get_group_members_properties($companyNode, array(), 'members__' . OG_STATE_ACTIVE, 'node');
  foreach($companyUsers as $k => $cuid) {
	$userroles = og_get_user_roles('node', $cid, $cuid);
	if(in_array('M6ID Manager', $userroles)) {
	  $om_uids[] = $cuid;
	}
	if(in_array('Site Manager', $userroles)) {
	  $sm_uids[] = $cuid;
	}
  }
  if(isset($om_uids) && !empty($om_uids) && count($om_uids)>0) {
    $return['om'] = $om_uids;
  }
  if(isset($sm_uids) && !empty($sm_uids) && count($sm_uids)>0) {
    $return['sm'] = $sm_uids;
  }
  return $return;
}

/************************* End Message System  ********************************/

/********** End Onboarding In Process **********/


