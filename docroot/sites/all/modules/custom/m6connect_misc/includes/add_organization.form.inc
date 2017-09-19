<?php

function new_organization_form_after_build($form,&$form_state){
  //kpr($form);
  return $form;	
}

function add_new_organization_form($form,&$form_state){
  global $user;
  module_load_include('inc', 'hierarchical_select', 'includes/common');
  $InviteJoinComSignup = variable_get('invitejoinsignup');
  //drup_msg($InviteJoinComSignup);
  /*drupal_add_css(drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css');
  drupal_add_js(drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js');
  drupal_add_js(drupal_get_path('module', 'international_phone') . '/js/international_phone.js');*/
  //$form_state['no_cache'] = TRUE;
  //$form['#after_build'][] = 'new_organization_form_after_build';
  $current_path = current_path();  
  if(in_array($current_path,array('new/organization','join/organization'))){
	$form_state['organization_page'] = $current_path;  
  }
  $invitedInNode = is_user_invited_in_node();
  $formMustFill = (($form_state['organization_page'] =='new/organization') && $invitedInNode);
  $registrationForm = ($form_state['organization_page'] =='new/organization')?TRUE:FALSE; 
  if($registrationForm){
	if($formMustFill){
	  $title = '';
	  if(isset($_SESSION['signup_invited_node']) && is_numeric($_SESSION['signup_invited_node'])){
		  $invite_node = node_load($_SESSION['signup_invited_node']);
		  if($invite_node && is_object($invite_node) && in_array($invite_node->type, array('rfp', 'project'))){
			  if($invite_node->title){
				  $title = $invite_node->title;
			  }
		  }
	  }else{
		$title = get_user_invited_in_node_titles();	
	  }
	  $form['#prefix'] = '<div id="message_error"></div>
		<div class="my-form-wrapper new-organization-form-wrapper">
			<div class="new-organigation-heading form-group">
				<h1>Congratulations!</h1>
				<div class="heading-desc1">You have been invited to participate in the <strong>"'.ucwords($title).'"</strong></div>
				<div class="heading-desc"><strong>Create your Company Profile to access the "'.ucwords($title).'"</strong></div>
			</div>';	
	}else{
	  $form['#prefix'] = '<div id="message_error"></div>
		<div class="my-form-wrapper new-organization-form-wrapper">
			<div class="new-organigation-heading form-group">
                <h1>Welcome to M6Connect!</h1>
                <div class="heading-desc"><strong>To access Projects, RFPs Proposals and more, add your Company or Select Your Company from the drop down.</strong></div>
            </div>';
		
	}
    
  }else{
	$form['#prefix'] = '<div id="message_error"></div><div class="my-form-wrapper join-organization-form-wrapper">';  
  }
  $form['#suffix'] = '</div>';

  /*$form['indicates_required'] = array(
    '#markup' => '<div class="required-field-indicator form-group"><span style="color:red;">*</span> Indicates Required Fields</div>',
  );*/
  
  
   $form['organigation_choose_container'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="organigation-choose-section">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container'] = array(
	'#type' => 'container',
	'#prefix' => '<div id="organigation-main-section" class="organigation-main-section clearfix">',
	'#suffix' => '</div>',
  );
  
  
  /*if(empty($form_state['organization_step'])){
	$form_state['organization_step']= 1;
	$form['organigation_main_container']['#access'] = FALSE; 
  }else if($form_state['organization_step']==2){
	$form['organigation_choose_container']['#access']= FALSE; 
	//$form['organigation_choose_container']['organization_email']['#value'] = $form_state['values']['create_company'];
  }*/
  
  $form['organigation_choose_container']['create_company_gpo'] = array(  
	'#type' => 'radios',
	'#title' => 'Is Your Company a GPo',
	'#options' => array(
	   'yes' => t('Yes'),
       'no' => t('No')
	 ),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  $inviteJoinComLabal = '';
  $inviteJoinComDefault = '';
  if(isset($InviteJoinComSignup) && !empty($InviteJoinComSignup)){
    if(isset($InviteJoinComSignup['request-id'],$InviteJoinComSignup['invitejoinrequesterfrom'],$InviteJoinComSignup['invitejoinrequesterto']) && !empty($InviteJoinComSignup['request-id']) && !empty($InviteJoinComSignup['invitejoinrequesterfrom']) && !empty($InviteJoinComSignup['invitejoinrequesterto'])){
      $inviteJoinRequestUser = _get_user_mail_realname_by_uid($InviteJoinComSignup['invitejoinrequesterfrom']);
	  $inviteJoinComLabal = 'you were granted access to '._get_title_of_node($InviteJoinComSignup['request-id']).' by '.$inviteJoinRequestUser['realname'].' at '.$inviteJoinRequestUser['mail'].'. Confirm your email address below and press continue.<br>';	  
	  $form['invite_join_requester_from_com'] = array(
		'#type' => 'hidden',
		'#value' => $InviteJoinComSignup['request-id'],
	  );
	  $form['invite_join_requester_from'] = array(
		'#type' => 'hidden',
		'#value' => $InviteJoinComSignup['invitejoinrequesterfrom'],
	  );
	  $form['invite_join_requester_to'] = array(
		'#type' => 'hidden',
		'#value' => $user->uid,
	  );  
	}
  }
  $inviteJoinComDefault = (isset($InviteJoinComSignup) && !empty($InviteJoinComSignup) && isset($InviteJoinComSignup['request-id']) && !empty($InviteJoinComSignup['request-id'])?$InviteJoinComSignup['request-id']:'');
  $form['organigation_choose_container']['create_company'] = array(  
	'#type' => 'textfield',
	//'#title' => 'Create Your Company Profile',
	'#title' => 'Enter Company Information',
	'#field_prefix' => '<div class="organization-desc1">'.$inviteJoinComLabal.'Company email address</div>',
	'#required' => TRUE,
	'#attributes' => array('placeholder'=>'Enter your company email address'),
	'#element_validate' => array('organization_email_validate'),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_choose_container']['corfirm_company'] = array(  
	'#type' => 'textfield',
	'#title' => 'Confirm Company Information',
	'#title_display' => 'invisible',
	'#field_prefix' => '<div class="organization-desc1">Confirm your company email address</div>',
	//'#required' => TRUE,
	'#attributes' => array('placeholder'=>'Enter your company email address'),
	'#element_validate' => array('organization_email_validate','organization_confirm_email_validate'),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_choose_container']['join_company'] = array(
	'#type' => 'select',
	'#title' => 'Select Your Company',
	'#title_display' => 'invisible',
	'#field_prefix' => '<div class="organization-desc1">Select your company from the drop down or create your company by selecting "Add Your Company".</div>',
	'#empty_option' => 'Add Your Company',
	'#options' => _get_organigation_mapping(),
	'#default_value' => $inviteJoinComDefault,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_choose_container']['organization_action'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="organization-action-section text-center">',
	'#suffix' => '</div>',
  );
  
  
  $form['organigation_choose_container']['organization_action']['submit']= array(
    '#type' => 'submit',
	'#value' => ($registrationForm)?'Complete Signup':'Continue',
	'#executes_submit_callback' => FALSE,
	'#limit_validation_errors' => array(array('create_company'),array('confirm_company')),
	'#prefix' => ($formMustFill)?'<div class="form-group">':'<div class="form-group"><span class="do-it-later-link">'.l('Skip','').'</span>&nbsp;&nbsp;',
	'#suffix' => '</div>',
	'#ajax' => array(
		'callback' => 'organization_complete_signup_submit_handler',
		'effect' => 'fade',
		'method' => 'replace',
		'event' => 'click',
		'wrapper'=>'organigation-main-section',
		'progress' => array('type' => 'throbber','message'=>NULL),
	),
  );
  
  if(!empty($form_state['values'])){
  $form['organigation_main_container']['organigation_detail_container'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-detail-section row margin-5">',
	'#suffix' => '</div>',
  );
  
  if($formMustFill){
    $form['organigation_main_container']['organigation_detail_container']['invited_markup'] = array(
      '#markup' => '<div class="form-group">Because you were invited to participate in a proposal, project or RFP the following information will be required.</div>',
    );
  }
  
  $form['organigation_main_container']['organigation_detail_container']['left'] = array(
  '#type' => 'container',
  '#prefix' => '<div class="organigation-detail-left-section col-md-6 col-sm-12 col-xs-12 padding-5">',
  '#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container']['right'] = array(
  '#type' => 'container',
  '#prefix' => '<div class="organigation-detail-right-section col-md-6 col-sm-12 col-xs-12 padding-5">',
  '#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container2']['left'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-detail-left-section col-md-6 col-sm-12 col-xs-12 padding-5">',
	'#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container2']['right'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-detail-right-section2 col-md-6 col-sm-12 col-xs-12 padding-5">',
	'#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container']['full'] = array(
  '#type' => 'container',
  '#prefix' => '<div class="organigation-detail-full-section col-md-12 col-sm-12 col-xs-12 padding-5">',
  '#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organigation_detail_container']['left']['organization_name']= array(
	'#type'=>'textfield',
	'#title' => 'Company Name (or organization)',
	'#field_prefix' => '<div class="organization-desc">Display name for the M6Connect network</div>',
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organigation_detail_container']['left']['owner_name']= array(
	'#type'=>'textfield',
	'#title' => 'Owners Name',
	'#field_prefix' => '<div class="organization-desc">Name of the parent company or company owner</div>',
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $vocabulary = taxonomy_vocabulary_machine_name_load('facilities_construction');
  $element_info = element_info('hierarchical_select');
  $form['organigation_main_container']['organigation_detail_container']['left']['m6organization_type']= array(
	'#type'=>'hierarchical_select',
	'#title' => 'M6Company Type',
	'#field_prefix' => '<div class="organization-desc">Select the appropriate company type</div>',
	'#default_value' => 0,
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
	'#process' => array_merge($element_info['#process'], array('hs_taxonomy_widget_process')),
	'#config' => array(
      'module' => 'hs_taxonomy',
      'params' => array(
		'vid' => (int) $vocabulary->vid,
		'exclude_tid' => NULL,
		'root_term' => NULL,
		'entity_count_for_node_type' => NULL,
	  ),
    ),
  );
  
  
   $form['organigation_main_container']['organigation_detail_container2']['left']['phone_no']= array(
	'#type'=>'textfield',
	'#title' => 'Mobile Phone Number',
	//'#field_prefix' => '<div class="organization-desc">&nbsp</div>',
	'#required' => TRUE,
	//'#attributes' => array('placeholder'=>'(000) 000 - 0000'),
	'#element_validate' => array('add_international_phone_no_element_validate'),
	'#attributes' => array('class' => array('international_phone-number')),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
	'#attached' => array(
	  'css'=> array(
	    drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css',
	  ),
	  'js'=>array(
	    drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js',
		drupal_get_path('module', 'international_phone') . '/js/international_phone.js'
	  ),
	),
  );
  
  
  $form['organigation_main_container']['organigation_detail_container']['right']['legal_name']= array(
	'#type'=>'textfield',
	'#title' => 'Legal Name',
	'#field_prefix' => '<div class="organization-desc">Company name as it appears on the incorporation documents</div>',
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $field = field_info_field('field_legal_structure');
  $allowed_values = list_allowed_values($field);
  $form['organigation_main_container']['organigation_detail_container']['right']['legal_structure']= array(
	'#type'=>'select',
	'#title' => 'Legal Structure',
	'#field_prefix' => '<div class="organization-desc">The legal structure under which the company was created</div>',
	'#required' => TRUE,
	'#options' => $allowed_values,
	'#empty_option' =>'',
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $DiversityOptions = db_select('node','n')->fields('n',array('nid','title'))->condition('n.type','diversity','=')->condition('n.status',1,'=')->execute()->fetchAllKeyed(0,1);
  $DiversityOptions = array('_none'=>'- None -')+$DiversityOptions;
  
  $form['organigation_main_container']['organigation_detail_container']['right']['diversity_credentials']= array(
	'#type'=>'select',
	'#title' => 'Diversity Credentials',
	'#field_prefix' => '<div class="organization-desc">Hold down CTRL to select multiple credentials</div>',
  '#attributes' => array('class' => array('addcom_diversity_credentials')),
	'#required' => TRUE,
	'#empty_value'=> '',
	'#options' => $DiversityOptions,
	'#multiple' => TRUE,
	'#chosen' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  /******************************************************signup dir*********************************************************************************/

$doptions  = hcfm_nodenid_nodetitle_by_node_type('diversity',0,0);
//pre($doptions ); 

//$form =  array();
  //$form['organigation_main_container']['organigation_detail_container']['diversity_credentials_outer1'] = array(
   // '#markup'=> '<div class="col-md-12 padding-5 addcompany-diversity-credentials-outer">',
 // );
$fieldMapping = array();
            $credentialsMapping = array();
            $credentialsNids = array();
            $credentialsMappingDetail = array();
            
                $field = field_info_field('field_form_fields');
                $allowed_values = list_allowed_values($field);
                if (!empty($allowed_values)) {
                    foreach ($allowed_values as $diversityFieldsName => $diversityFieldsLabel) {
                        $fieldMapping[$diversityFieldsName] = array(
                            'field-info' => field_info_field($diversityFieldsName),
                            'field-instance' => field_info_instance('node', $diversityFieldsName, 'credentials')
                        );
                    }
                }
                
            //drup_msg($field);    
            //drup_msg($allowed_values);
            //drup_msg($fieldMapping);  
foreach ($doptions as $k => $v) {
                $relatedcredNid = '';
                if (isset($credentialsMapping[$k])) {
                    $relatedcredNid = $credentialsMapping[$k];
                }
                $node = node_load($k);
                $wtitle = $node->title;
                $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k] = array(
                    '#type' => 'fieldset',
                    '#title' => $wtitle,
                    '#tree' => TRUE,
                    '#prefix' => '<div class="form-group"><div id="customwrap' . $k . '" class="custwrapcrd org-diversity-wrapper customwrapcrd_' . $k . '">',
                    '#suffix' => '</div></div>',
                    '#weight' => $field_diversity_credentials_weight + 1,
                );
                $form['#step_children']['custwrap' . $k] = 'step_co_supplier_diversity';
                $fields = field_get_items('node', $node, 'field_form_fields');
                foreach ($fields as $var => $val) {
                    $fieldname = $val['value'];
                    $finfo1 = $fieldMapping[$fieldname]['field-info'];
                    $finfo2 = $fieldMapping[$fieldname]['field-instance'];
                    $label = $finfo2['label'];
                    if ($finfo1['type'] == 'list_text') {
                        $defValue = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && $issessionarr[$fn] != 'None') {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            //$defValue = get_field_value('list_text', $fieldname, $relatedcredNid);
                            $defValue = $credentialsMappingDetail[$relatedcredNid]->field_accredited_by_value;
                        }
                        $options = $finfo1['settings']['allowed_values'];
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                            '#type' => 'select',
                            '#title' => $label,
                            '#options' => $options,
                            '#parents' => array('diversity_credendial', $k, $fieldname),
                            '#default_value' => $defValue,
                            '#prefix' => '<div class="form-wrapper2">',
                                //'#suffix' => '</div>', //for grouping 3 box
                        );
                    }
                    if ($finfo1['type'] == 'datetime' || $finfo1['type'] == 'date' || $finfo1['type'] == 'datestamp') {
                        $defValue = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && !empty($issessionarr[$fn])) {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            // $defValue = get_field_value('date', $fieldname, $relatedcredNid);
                            if ($fieldname == 'field_cred_start_date') {
                                $defValue = $credentialsMappingDetail[$relatedcredNid]->field_cred_start_date_value;
                            } else if ($fieldname == 'field_credential_end_date') {
                                $defValue = $credentialsMappingDetail[$relatedcredNid]->field_credential_end_date_value;
                            } else {
                                $defValue = '';
                            }
                        }
                        $dtstmp = !empty($defValue) ? strtotime($defValue) : '';

                        if ($fieldname == 'field_cred_start_date') {

                            $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                                '#type' => 'date_popup',
                                '#title' => $label,
                                '#date_format' => 'm/d/Y',
                                '#parents' => array('diversity_credendial', $k, $fieldname),
                                    //'#default_value' => date('m/d/Y'),
                                    //'#default_value' => date('Y-m-d H:i:s', $dtstmp),
                                    //'#prefix' => '<div class="form-wrapper2 form-wrapper3">', //for grouping 3 box
                                    //'#suffix' => '</div>', //for grouping 3 box
                            );
                            if (!empty($dtstmp)) {
                                $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k]['#default_value'] = date('Y-m-d H:i:s', $dtstmp);
                            }
                        } else if ($fieldname == 'field_credential_end_date') {
                            $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                                '#type' => 'date_popup',
                                '#title' => $label,
                                '#date_format' => 'm/d/Y',
                                '#parents' => array('diversity_credendial', $k, $fieldname),
                                //'#default_value' => date('m/d/Y'),
                                //'#default_value' => date('Y-m-d H:i:s', $dtstmp),
                                //'#prefix' => '<div class="form-wrapper2 form-wrapper3">', //for grouping 3 box
                                '#suffix' => '</div>',
                            );
                            if (!empty($dtstmp)) {
                                $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k]['#default_value'] = date('Y-m-d H:i:s', $dtstmp);
                            }
                        }
                    }

                    if ($finfo1['type'] == 'text_long') {
                        $defValue = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && !empty($issessionarr[$fn])) {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            //$defValue = get_field_value('text_long', $fieldname, $relatedcredNid);
                            $defValue = $credentialsMappingDetail[$relatedcredNid]->field_credential_comments_value;
                        } //pre($defValue); 
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                            '#type' => 'textarea',
                            '#title' => $label,
                            '#default_value' => $defValue,
                            '#parents' => array('diversity_credendial', $k, $fieldname),
                            '#prefix' => '<div class="form-wrapper2 form-wrapper-comment">',
                            '#suffix' => '</div>',
                        );
                    }
                    if ($finfo1['type'] == 'file') {
                        $defValue = $defval = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && !empty($issessionarr[$fn]) && $issessionarr[$fn] != 0) {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            //$defValue = get_field_value('file', $fieldname, $relatedcredNid);
                            $defValue = $credentialsMappingDetail[$relatedcredNid]->field_credential_doc_fid;
                        }

                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k]['markup2' . $k] = array('#markup' => '<div class="form-wrapper2 cust-file-mfiled">');

                        if (!empty($defValue)) {
                            //$file = file_load($defValue); 
                            //$filename = $file->filename;
                            $filename = $credentialsMappingDetail[$relatedcredNid]->filename;
                            $defval = '<img src="/modules/file/icons/text-plain.png" title="text/plain" alt="" class="file-icon">' . $filename;
                            $form['organigation_main_container']['organigation_detail_container']['custwrap' . $k]['markup' . $k] = array('#markup' => $defval);
                        }

                        $fileext = $finfo2['settings']['file_extensions'];
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                            '#type' => 'managed_file',
                            '#title' => $label,
                            '#parents' => array('diversity_credendial', $k, $fieldname),
                            '#upload_location' => 'private://',
                            //'#description' => t('Allowed extensions: txt, doc, pdf, docx, jpg, jpeg, gif, png, bmp, xls, xlsx'),
                            '#upload_validators' => array(
                                'file_validate_extensions' => array($fileext),
                            // Pass the maximum file size in bytes
                            //'file_validate_size' => array(MAX_FILE_SIZE*1024*1024),
                            ),
                                //'#prefix' => '<div class="form-wrapper2"><div class="cust-fdef">'.$defval.'</div>',
                                //'#prefix' => '<div class="form-wrapper2">',
                                //'#suffix' => '</div>',
                        );
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k]['markup3' . $k] = array('#markup' => '</div>');
                    }
                }
            }
/*$form['organigation_main_container']['organigation_detail_container']['diversity_credentials_outer2'] = array(
    '#markup'=> '</div">',
  );*/
//pre($form);
/***************************************************************************************************************************************/

  $form['organigation_main_container']['organigation_detail_container2']['right']['organization_website_url']= array(
	'#type'=>'textfield',
	'#title' => 'Company Website URL',
	'#field_prefix' => '<span class="organization-desc">( www.xyz.com )</span>',
	'#required' => TRUE,
	'#element_validate' => array('url_validate_url'),
	'#attributes' => array('placeholder'=>'www.xyz.com'),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organigation_location_container'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-location-section"><label for="edit-location">Location Information <span class="form-required" title="This field is required.">*</span></label>',
	'#suffix' => '</div>',
  );
  
  $field = field_info_field('field_org_address');
  $instance = field_info_instance('node', 'field_org_address', 'organization');
  $address = addressfield_default_values($field,$instance);
  $handlers = array('address' => 'address',);
  $context = array('mode' => 'form');
  $form['organigation_main_container']['organigation_location_container']['location'] = addressfield_generate($address, $handlers, $context);
  $form['organigation_main_container']['organigation_location_container']['location']['country']['#access'] =FALSE;
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['#attributes']['class'][] = 'row';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['#attributes']['class'][] = 'margin-5';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['thoroughfare']['#prefix'] = '<div class="col-md-6 col-sm-6 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['thoroughfare']['#suffix'] = '</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['premise']['#prefix'] = '<div class="col-md-6 col-sm-6 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['premise']['#suffix'] = '</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['#attributes']['class'][] = 'row';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['#attributes']['class'][] = 'margin-5';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['locality']['#prefix']='<div class="col-md-4 col-sm-4 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['administrative_area']['#prefix']='<div class="col-md-6 col-sm-6 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['postal_code']['#prefix']='<div class="col-md-2 col-sm-2 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['locality']['#suffix']='</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['administrative_area']['#suffix']='</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['postal_code']['#suffix']='</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['administrative_area']['#empty_option'] ='';
  
 
  
  $form['organigation_main_container']['organigation_keyword']= array(
	'#type'=>'textfield',
	'#title' => 'Keyword',
	'#title_display' => 'invisible',
	'#prefix' => '<div class="organigation-keyword-section form-group"><label for="edit-keyword">Increase your M6Connect Presence </label><div class="organization-desc1"><strong>Add Keywords</strong> to help others narrow their search results. Add up to 5 keywords separated by space.<span class="form-required" title="This field is required.">*</span></div>',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organization_logo_contianer']= array(
    '#type' => 'container',
	'#prefix' => '<div class="organigation-logo-section"><label for="edit-logo">Company Logo </label><div class="organization-desc">jpg, jpeg, png file type only. May not exceed 500kb.</div>',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organization_logo_contianer']['organization_logo'] = array(
	'#title' => 'Company Logo',
	'#title_display' => 'invisible',
	'#type' => 'managed_file',
	//'#description' => t('jpg, jpeg, png file type only. May not exceed 500kb.'),
	'#upload_location' => 'private://',
	"#upload_validators"  => array(
	  'file_validate_is_image' => array(),
	  "file_validate_extensions" => array("png gif jpg jpeg"),
		'file_validate_image_resolution_new' => array('229x198', '229x198'),
	),
  );
  
  $form['organigation_main_container']['organization_action2'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organization-action-section pull-right">',
	'#suffix' => '</div>',
  );
  
  /*$form['organigation_main_container']['organization_action2']['do_it_later']= array(
	'#type' => 'markup',
	'#markup' => '<span class="do-it-later-link">'.l('Skip, and do it later','').'</span>&nbsp;&nbsp;',
  );*/
  
  $form['organigation_main_container']['organization_action2']['submit']= array(
	'#type' => 'submit',
	'#value' => 'Continue',
	'#submit' => array('add_new_organization_submit'),
	'#prefix' => ($formMustFill)?'<div class="form-group">':'<div class="clearfix"><span class="do-it-later-link">'.l('Skip, and do it later','').'</span>&nbsp;&nbsp;',
	'#suffix' => '</div>',
  );
  
  }
   
  /*$form['social_network_container'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="social-network-section row">',
	'#suffix' => '</div>',
  );
  
  $form['social_network_container']['left'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="social-network-left-section col-md-6 col-sm-6 col-xs-12">',
	'#suffix' => '</div>',
  );
  $form['social_network_container']['right'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="social-network-right-section col-md-6 col-sm-6 col-xs-12">',
	'#suffix' => '</div>',
  );
  
  $form['social_network_container']['left']['facebook']= array(
    '#type'=>'textfield',
	'#attributes' => array('placeholder'=>'Facebook'),
	'#field_prefix' => '<i class="fa fa-facebook organization-fa-icon"></i>',
  );
  $form['social_network_container']['left']['linkedin']= array(
    '#type'=>'textfield',
	'#attributes' => array('placeholder'=>'Linkedin'),
	'#field_prefix' => '<i class="fa fa-linkedin organization-fa-icon"></i>',
  );
  $form['social_network_container']['left']['behance']= array(
    '#type'=>'textfield',
	'#attributes' => array('placeholder'=>'Behance'),
	'#field_prefix' => '<i class="fa fa-behance organization-fa-icon"></i>',
  );
  $form['social_network_container']['right']['twitter']= array(
    '#type'=>'textfield',
	'#attributes' => array('placeholder'=>'Twitter'),
	'#field_prefix' => '<i class="fa fa-twitter organization-fa-icon"></i>',
  );
  $form['social_network_container']['right']['pinterest']= array(
    '#type'=>'textfield',
	'#attributes' => array('placeholder'=>'Pinterest'),
	'#field_prefix' => '<i class="fa fa-pinterest-p organization-fa-icon"></i>',
  );
  $form['social_network_container']['right']['skype']= array(
    '#type'=>'textfield',
	'#attributes' => array('placeholder'=>'Skype'),
	'#field_prefix' => '<i class="fa fa-skype organization-fa-icon"></i>',
  );*/
  
   /*$field_name = 'field_legal_structure';
$field = field_info_field($field_name);   
$instance = field_info_instance('node', $field_name, 'organization');   
$default_value =  field_get_default_value('node', $node, $field, $instance, $node->language); 

$field = field_info_field('field_legal_structure');
$allowed_values = list_allowed_values($field);*/
  //kpr($form);
	$form['#validate'][] = 'join_new_organization_validate';
  return $form;	
}

function organization_email_validate($element, &$form_state, $form){
  $value = $element['#value'];	
  if (!valid_email_address($value)) {
    form_error($element, t('Please enter a valid email address.'));
  }	
}

function organization_confirm_email_validate($element, &$form_state, $form){
  $values = $form_state['values'];
  if($element['#value'] != $values['create_company']){
	form_error($form['organigation_choose_container']['create_company'], 'Company email address must match');  
  }
}

function organization_complete_signup_submit_handler(&$form,&$form_state){
  global $user;
  $values = $form_state['values'];
  //drup_msg($form_state);
 // pre($form_state['values'],1);
  ctools_include('ajax');
  ctools_include('modal');
  $commands = array();
  $commands[] = ajax_command_html('#message_error', '');
  $errors = form_get_errors();
  if(!empty($errors)){
	$commands[] = ajax_command_html('#message_error', theme('status_messages'));
	return array('#type' => 'ajax', '#commands' => $commands);
  }
  
  if(!empty($values['join_company'])){
	$commands[] = ajax_command_html('#message_error', ''); 
	$account = user_load($user->uid);
    $edit['field_user_company']['und'][0]['target_id'] = $values['join_company'];
	$edit['field_organization_mail']['und'][0]['email'] = $values['create_company'];
    user_save($account, $edit);
	if(db_table_exists('m6connect_company_join_request')){
	  db_merge('m6connect_company_join_request')
	  ->key(array('entity_id'=>$values['join_company'],'user_uid'=>$account->uid,'status'=>0))
	  ->fields(array(
	    'entity_id'=>$values['join_company'],
		'user_uid'=>$account->uid,
		'join_email'=>$values['create_company'],
		'timestamp'=>time(),
		'status'=>0,
	  ))->execute();	
	}
	
    $_SESSION['non_company_popup'] = 1;	
	if(isset($values['invite_join_requester_from_com'],$values['invite_join_requester_from'],$values['invite_join_requester_to']) && !empty($values['invite_join_requester_from_com']) && !empty($values['invite_join_requester_from']) && !empty($values['invite_join_requester_to'])){
	  $uservalues = array(
		'entity_type' => 'user',
		'entity' => $account,
		'state' => OG_STATE_ACTIVE,
	  );
	  $og_membership = og_group('node', $values['invite_join_requester_from_com'], $uservalues);
	  $ogrolesk = og_roles('node', 'organization');
      $ogroles = array_flip($ogrolesk);
	  $user_role = $ogrolesk[$ogroles['staff']];
      og_role_grant('node', $values['invite_join_requester_from_com'], $account->uid, $ogroles['staff']);	
	  $_SESSION['company'] = $values['invite_join_requester_from_com'];
	  //drup_msg($values['invite_join_requester_from_com']);
	  //drup_msg($values['invite_join_requester_from']);
	  //drup_msg($values['invite_join_requester_to']);
	  //drup_msg($account);
	  
	}else{
	  join_company_notification_entry($values['join_company']);
	}	
	$commands[] = ctools_ajax_command_redirect('');
  }else{
	  //drup_msg($form_state['values']);
	//$commands[] = ajax_command_html('#message_error', theme('status_messages')); 
	//$commands[] = ajax_command_css('#organigation-main-section', array('display'=>'block'));
	$commands[] = ajax_command_replace("#organigation-main-section", render($form['organigation_main_container']));
    //return $form['organigation_main_container'];
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function add_new_organization_submit(&$form,&$form_state){  //pre($form_state['values'],1);
  global $user;
  $values = $form_state['values'];
  $node = new stdClass();
  $node->type = 'organization';
  node_object_prepare($node);
  $node->field_company_email['und'][0]['email']= $values['create_company'];
  $node->field_company_gpo['und'][0]['value']= $values['create_company_gpo'];

  // When the node is created by the user, storing M6Level as 2 if user is not
  // admin.
  if (!in_array('administrator', $user->roles)) {
    $node->field_m6level[LANGUAGE_NONE][0]['value'] = '2';
  }

  // Although we had set default values for source and service fields, which
  // would be auto inserted in node_object_prepare, as we are not showing this
  // fields to non-admins. But, in case if an admin is creating it, then we need
  // to respect the admin's manual selection. So working on it.
  if (in_array('administrator', $user->roles)) {
    if (isset($values['source'])) {
      $i = 0;
      foreach ($values['source'] as $source) {
        $node->field_m6source[LANGUAGE_NONE][$i]['value'] = $source;
        $i++;
      }
    }
  }

  // Same is the case for service field, but it is accessible to both drupal
  // admin and company admin.
  if (array_key_exists(5, $user->roles) || array_key_exists(3, $user->roles)) {
    if (isset($values['service'])) {
      $node->field_service[LANGUAGE_NONE][0]['value'] = $values['service'];
    }
  }
  
  
  $node->title = $values['organization_name'];
  $node->field_legal_name['und'][0]['value'] = $values['legal_name'];
  $node->field_owner_name['und'][0]['value'] = $values['owner_name'];
  $node->field_legal_structure['und'][0]['value'] = $values['legal_structure'];
  $node->field_org_phone['und'][0]['value'] = $values['phone_no'];
  $node->field_website['und'][0]['value'] = $values['organization_website_url']; 
  $node->field_org_address['und'][0]['thoroughfare'] = $values['thoroughfare'];
  $node->field_org_address['und'][0]['premise'] = $values['premise'];
  $node->field_org_address['und'][0]['locality'] = $values['locality'];
  $node->field_org_address['und'][0]['administrative_area'] = $values['administrative_area']; 
  $node->field_org_address['und'][0]['postal_code'] = $values['postal_code'];
  $node->field_org_address['und'][0]['country'] = $values['country'];
  $node->field_main_location_type['und'][0]['value'] = 'main-location';
  $node->field_keywords['und'][0]['value'] = $values['organigation_keyword'];
  $node->field_show_company_in_search['und'][0]['value'] = 1; 
  $node->field_type_of_company['und'][0]['value'] = 'company';
  $index =0;
  foreach($values['diversity_credentials'] as $delta => $diversityId){
	if(is_numeric($diversityId)){
	  $node->field_diversity_credentials['und'][$index++]['target_id']=$diversityId;
	}
  }
  if(isset($values['m6organization_type'][0]) && !empty($values['m6organization_type'][0]['tid'])){
	$node->field_facilities_construction['und'][0]['tid']= $values['m6organization_type'][0]['tid']; 
  }
  if($values['organization_logo'] != 0){
	$logo = file_load($values['organization_logo']);
	$logo->status = FILE_STATUS_PERMANENT; 
	file_save($logo);
	$logo = (array)$logo;
	$node->field_logo['und'] = array($logo);
	
  }
  node_save($node);
  $_SESSION['company'] = $node->nid;

  // Checking vendor manager requests.
  if (isset($_SESSION['vendor_register'])) {
    if (!empty($_SESSION['vendor_register']['vendor_nid'])) {
      $vnid = $_SESSION['vendor_register']['vendor_nid'];
      
      if ($vendor_node = node_load($vnid)) {
        // Adding the company as it's reference.
        $vendor_node->og_group_ref['und'][0]['target_id'] = $node->nid;
        
        field_attach_presave('node', $vendor_node);
        field_attach_update('node', $vendor_node);
        entity_get_controller('node')->resetCache(array($vendor_node->nid));


        unset($_SESSION['vendor_register']);
        drupal_set_message(t('Thank you for registering.'), 'status', FALSE);
      }
    }
  }
 
 /************************************************************************************************/

  $inserted_diversity_credentials = array();
  if (isset($values) && !empty($values['diversity_credentials'])) {
    foreach ($values['diversity_credentials'] as $dive_cre_key) {
      $credentialNode = new stdClass();
      $credentialNode->type = 'credentials';
      node_object_prepare($credentialNode);
      $credentialNode->language = LANGUAGE_NONE;
      $credentialNode->uid = $user->uid;
      $credentialNode->title = 'Credential-' . uniqid();
      $credentialNode->field_cred_for_diversity['und'][0]['target_id'] = $dive_cre_key;
      $credentialNode->field_cred_for_company['und'][0]['target_id'] = $node->nid;
        /*if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_comments'])) {
          $temp = $values['diversity_credendial'][$dive_cre_key]['field_credential_comments'];
          $credentialNode->field_credential_comments['und'][0]['value'] = $temp;
        } */    
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_cred_start_date'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_cred_start_date'];
        $credentialNode->field_cred_start_date['und'][0] = array(
          'value' => date('Y-m-d H:i:s', strtotime($temp)),
          'timezone' => 'UTC',
          'timezone_db' => 'UTC',
        );
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_end_date'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_credential_end_date'];
        $credentialNode->field_credential_end_date['und'][0] = array(
          'value' => date('Y-m-d H:i:s', strtotime($temp)),
          'timezone' => 'UTC',
          'timezone_db' => 'UTC',
        );
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_comments'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_credential_comments'];
        $credentialNode->field_credential_comments['und'][0]['value'] = $temp;
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_accredited_by'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_accredited_by'];
        $credentialNode->field_accredited_by['und'][0]['value'] = $temp;
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_doc'])) {
        $temp = file_load($values['diversity_credendial'][$dive_cre_key]['field_credential_doc']);
        if ($temp) {
          $temp->status = FILE_STATUS_PERMANENT;
          $temp->display = 1;
          file_save($temp);
          $credentialNode->field_credential_doc['und'][0] = (array) $temp;
        }
      }
      node_save($credentialNode);
      $inserted_diversity_credentials[] = $credentialNode->nid;
    }
  }

  if (!empty($inserted_diversity_credentials)) {
    $temp = array();
    foreach ($inserted_diversity_credentials as $delta33 => $item33) {
      $temp[$delta33] = array('target_id' => $item33);
    }
    $node2 = node_load($node->nid);
    $node2->field_dcrednid_22['und'] = $temp;
    node_save($node2);
  }
  //drup_msg($temp);
  /************************************************************************************************/
  
 /*
  $credentialNode = new stdClass();
                $credentialNode->type = 'credentials';
                node_object_prepare($credentialNode);
                $credentialNode->language = LANGUAGE_NONE;
                $credentialNode->uid = $values['uid'];
                $credentialNode->title = 'Credential-' . uniqid();
                $credentialNode->field_cred_for_diversity['und'][0]['target_id'] = $data11['target_id'];
                $credentialNode->field_cred_for_company['und'][0]['target_id'] = $values['nid'];
                if (!empty($diversity_credentials_values[$data11['target_id']]['field_cred_start_date'])) {
                    $temp = $diversity_credentials_values[$data11['target_id']]['field_cred_start_date'];
                    $credentialNode->field_cred_start_date['und'][0] = array(
                        'value' => date('Y-m-d H:i:s', strtotime($temp)),
                        'timezone' => 'UTC',
                        'timezone_db' => 'UTC',
                    );
                }
                if (!empty($diversity_credentials_values[$data11['target_id']]['field_credential_end_date'])) {
                    $temp = $diversity_credentials_values[$data11['target_id']]['field_credential_end_date'];
                    $credentialNode->field_credential_end_date['und'][0] = array(
                        'value' => date('Y-m-d H:i:s', strtotime($temp)),
                        'timezone' => 'UTC',
                        'timezone_db' => 'UTC',
                    );
                }
                if (!empty($diversity_credentials_values[$data11['target_id']]['field_credential_comments'])) {
                    $temp = $diversity_credentials_values[$data11['target_id']]['field_credential_comments'];
                    $credentialNode->field_credential_comments['und'][0]['value'] = $temp;
                }
                if (!empty($diversity_credentials_values[$data11['target_id']]['field_accredited_by'])) {
                    $temp = $diversity_credentials_values[$data11['target_id']]['field_accredited_by'];
                    $credentialNode->field_accredited_by['und'][0]['value'] = $temp;
                }
                if (!empty($diversity_credentials_values[$data11['target_id']]['field_credential_doc'])) {
                    $temp = file_load($diversity_credentials_values[$data11['target_id']]['field_credential_doc']);
                    if ($temp) {
                        $temp->status = FILE_STATUS_PERMANENT;
                        $temp->display = 1;
                        file_save($temp);
                        $credentialNode->field_credential_doc['und'][0] = (array) $temp;
                    }
                }
                node_save($credentialNode);
                $inserted_diversity_credentials[] = $credentialNode->nid;

*/



  //primary company start
  /*$existing = user_load($user->uid);
  $edit = (array) $existing; 
  $edit['field_primary_company']['und'][0]['value'] = $node->nid;
  user_save($existing, $edit);*/
  //primary comapny end	
  //drup_msg($form_state['values']);

  if (!empty($_SESSION['vendor_register']['cnid'])) {
    drupal_set_message(t('Thank you for registering.'), 'status', FALSE);
    $cnid = $_SESSION['vendor_register']['cnid'];
    unset($_SESSION['vendor_register']); // Unsetting the session variable.
    drupal_goto('node/' . $cnid, array('query' => array('vendor' => 'default')));
    drupal_exit(0);
  }
  else {
    drupal_goto('node/'.$node->nid.'/edit');
    drupal_exit();
  }
}

function _get_organigation_mapping($userUid = null){
  global $user;
  $account = user_load($user->uid);
  if(!empty($userUid)){
  	$account = user_load($userUid);
  }
  $group = og_get_groups_by_user($account, $group_type = 'node');
  $query = db_select('node', 'n');
  $query->fields('n', array('nid', 'title'));
  $query->condition('type', 'organization', '=');
  //************************** Start (Not Show Company When they are Inctive) **************************/
  // $ic_or = db_or();
  // $query->leftJoin('field_data_field_company_inactive', 'ic', 'ic.entity_id = n.nid');
  // $ic_or->isNull('ic.field_company_inactive_value')->condition('ic.field_company_inactive_value',0);
  // $query->condition($ic_or);
  //*************************** End (Not Show Company When they are Inctive) ***************************/
  //************************** Start (Show Company When show company active) **************************/
  $query->leftJoin('field_data_field_show_company_in_search', 'isa', 'isa.entity_id = n.nid');
  $query->condition('isa.field_show_company_in_search_value', 1, '=');
  //*************************** End (Show Company When show company active) ***************************/
  //************************** Start (Not Show Company When they are not company type) **************************/
  $query->leftJoin('field_data_field_type_of_company', 'tc', 'tc.entity_id = n.nid');
  $query->condition('tc.field_type_of_company_value', 'company', '=');
  if(is_array($group) && !empty($group)){
	$query->condition('n.nid', array_values($group), 'NOT IN');  
  }
  $query->orderBy('n.title', 'ASC');//ORDER BY title
  $result = $query->execute()->fetchAllKeyed(0,1);
  return $result;
}


function join_new_organization_form($form,&$form_state){
  
  global $user;
  //$form_state['no_cache'] = TRUE;
  module_load_include('inc', 'hierarchical_select', 'includes/common');
  
  /*drupal_add_css(drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css');
  drupal_add_js(drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js');
  drupal_add_js(drupal_get_path('module', 'international_phone') . '/js/international_phone.js');*/
  
  $form_state['organization_page'] = 'join/organization';  
  $form['#prefix'] = '<div id="message_error"></div><div class="my-form-wrapper join-organization-form-wrapper">';  
  $form['#suffix'] = '</div>';

  /*$form['indicates_required'] = array(
    '#markup' => '<div class="required-field-indicator form-group"><span style="color:red;">*</span> Indicates Required Fields</div>',
  );*/
  
  if(empty($form_state['cancel_request'])){
	if(isset($_REQUEST['cancel']) && !empty($_REQUEST['cancel'])){
	  $form_state['cancel_request'] = $_REQUEST['cancel'];	
	}else{
	  $form_state['cancel_request'] = '';
	}
  }
  
  $joinCompanyDefault = '';
  if(isset($_REQUEST['company']) && is_numeric($_REQUEST['company'])){
	$joinCompanyDefault= $_REQUEST['company']; 
  }
  
  $form['organigation_choose_container'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="organigation-choose-section">',
	'#suffix' => '</div>',
  );
  
  /*if(empty($form_state['organization_step'])){
	$form_state['organization_step']= 1;
	$form['organigation_main_container']['#access'] = FALSE; 
  }else if($form_state['organization_step']==2){
	$form['organigation_choose_container']['#access']= FALSE; 
	//$form['organigation_choose_container']['organization_email']['#value'] = $form_state['values']['create_company'];
  }*/
  
  // Checking if the user creating the company is drupal admin.
  // If so, then showing the Source field.
  // Functionality added Dec 30, 2016 by SB
  if (in_array('administrator', $user->roles)) {
    $form['organigation_choose_container']['source'] = array(
      '#type' => 'textfield',
      '#title' => t('Source of Company'),
      '#prefix' => '<div class="form-group">',
      '#suffix' => '</div>',
      '#default_value' => 'M6Connect user',
    );
  }

  // Checking if the user creating the company is either drupal admin or
  // company admin. If so, then showing the Service field.
  // Functionality added Dec 30, 2016 by SB
  if ((array_key_exists(5, $user->roles) || array_key_exists(3, $user->roles)) && !array_key_exists('company', $_GET)) {
    $form['organigation_choose_container']['service'] = array(
      '#type' => 'select',
      '#title' => t('Type of Service Company Provides'),
      '#options' => array(
        'Unknown' => 'Unknown',
        'Residential/Consumer' => 'Residential/Consumer',
        'Commercial' => 'Commercial',
        'N/A' => 'N/A',
      ),
      '#prefix' => '<div class="form-group">',
      '#suffix' => '</div>',
      '#default_value' => 'Commercial',
    );
  }
  $form['organigation_choose_container']['create_company_gpo'] = array(  
	'#type' => 'radios',
	'#title' => 'Is Your Company a GPo',
	'#options' => array(
	   'yes' => t('Yes'),
       'no' => t('No')  
	 ),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $inviteJoinComLabal = '';
  if(isset($_REQUEST['invitejoinrequesterfrom']) && !empty($_REQUEST['invitejoinrequesterfrom'])){
	$inviteJoinRequestUser = _get_user_mail_realname_by_uid($_REQUEST['invitejoinrequesterfrom']);
	$inviteJoinComLabal = 'you were granted access to '._get_title_of_node($_REQUEST['company']).' by '.$inviteJoinRequestUser['realname'].' at '.$inviteJoinRequestUser['mail'].'. Confirm your email address below and press continue.<br>';
  }
  $form['organigation_choose_container']['create_company'] = array(  
	'#type' => 'textfield',
	//'#title' => 'Create Your Company Profile',
	'#title' => 'Enter Company Information',
	'#field_prefix' => '<div class="organization-desc1">'.$inviteJoinComLabal.'Company email address</div>',
	'#required' => TRUE,
	'#attributes' => array('placeholder'=>'Enter your company email address'),
	'#element_validate' => array('organization_email_validate'),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_choose_container']['corfirm_company'] = array(  
	'#type' => 'textfield',
	'#title' => 'Confirm Company Information',
	'#title_display' => 'invisible',
	'#field_prefix' => '<div class="organization-desc1">Confirm your Company email address</div>',
	'#required' => TRUE,
	'#attributes' => array('placeholder'=>'Enter your company email address'),
	'#element_validate' => array('organization_email_validate','organization_confirm_email_validate'),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  
  
  $form['organigation_choose_container']['join_company'] = array(
	'#type' => 'select',
	'#title' => 'Select Your Company',
	'#title_display' => 'invisible',
	'#field_prefix' => '<div class="organization-desc1">Select your company from the drop down or create your company by selecting "Add Your Company".</div>',
	'#empty_option' => 'Add Your Company',
	'#attributes' => array('class'=> array('join-company-drop-down')),
	'#options' => _get_organigation_mapping(),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
	'#default_value'=> $joinCompanyDefault,
	'#chosen' => TRUE,
  );
	
	
  
  $form['organigation_choose_container']['organization_action'] = array(
    '#type' => 'container',
	'#prefix' => '<div class="organization-action-section text-center">',
	'#suffix' => '</div>',
  );
  
  if(isset($_REQUEST['invitejoinrequesterfrom'],$_REQUEST['invitejoinrequesterto'] ) && !empty($_REQUEST['invitejoinrequesterfrom']) && !empty($_REQUEST['invitejoinrequesterto']) && (isset($_REQUEST['company']) && !empty($_REQUEST['company']) || isset($_REQUEST['request-id']) && !empty($_REQUEST['request-id']))){
	$form['invite_join_requester_from_com'] = array(
	  '#type' => 'hidden',
	  '#value' => (isset($_REQUEST['company']) && !empty($_REQUEST['company'])?$_REQUEST['company']:$_REQUEST['request-id']),
	);
	$form['invite_join_requester_from'] = array(
	  '#type' => 'hidden',
	  '#value' => $_REQUEST['invitejoinrequesterfrom'],
	);
	$form['invite_join_requester_to'] = array(
	  '#type' => 'hidden',
	  '#value' => $_REQUEST['invitejoinrequesterto'],
	);
  }
  $form['organigation_choose_container']['organization_action']['submit1']= array(
    '#type' => 'submit',
	'#value' => 'Continue',
	//'#executes_submit_callback' => FALSE,
	'#name' => 'continue',
	'#limit_validation_errors' => array(array('create_company'),array('confirm_company')),
	'#prefix' => '<div class="form-group"><span class="do-it-later-link">'.l('Cancel',$form_state['cancel_request']).'</span>&nbsp;&nbsp;',
	'#suffix' => '</div>',
	'#submit' => array('choose_container_submit_handler'),
	//'#after_build' => array('organization_action_submit_after_build'),
	/*'#ajax' => array(
		'callback' => 'organization_complete_signup_submit_handler',
		'effect' => 'fade',
		'method' => 'replace',
		'event' => 'click',
		'wrapper'=>'organigation-main-section',
		'progress' => array('type' => 'throbber','message'=>NULL),
	),*/
  );
  
  $form['organigation_main_container'] = array(
	'#type' => 'container',
	'#prefix' => '<div id="organigation-main-section" class="organigation-main-section clearfix">',
	'#suffix' => '</div>',
	'#states' => array(
      'visible' => array('select.join-company-drop-down' => array('value' => '')),
    ),
  );
  
  if(!empty($form_state['values'])){
  $form['organigation_main_container']['organigation_detail_container'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-detail-section row margin-5">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organigation_detail_container']['left'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-detail-left-section col-md-6 col-sm-12 col-xs-12 padding-5">',
	'#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container']['right'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-detail-right-section col-md-6 col-sm-12 col-xs-12 padding-5">',
	'#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container2']['left'] = array(
  '#type' => 'container',
  '#prefix' => '<div class="organigation-detail-left-section col-md-6 col-sm-12 col-xs-12 padding-5">',
  '#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container2']['right'] = array(
  '#type' => 'container',
  '#prefix' => '<div class="organigation-detail-right-section2 col-md-6 col-sm-12 col-xs-12 padding-5">',
  '#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container']['full'] = array(
  '#type' => 'container',
  '#prefix' => '<div class="organigation-detail-full-section col-md-12 col-sm-12 col-xs-12 padding-5">',
  '#suffix' => '</div>',
  );
  $form['organigation_main_container']['organigation_detail_container']['left']['organization_name']= array(
	'#type'=>'textfield',
	'#title' => 'Company Name (or organization)',
	'#field_prefix' => '<div class="organization-desc">Display name for the M6Connect network</div>',
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organigation_detail_container']['left']['owner_name']= array(
	'#type'=>'textfield',
	'#title' => 'Owners Name',
	'#field_prefix' => '<div class="organization-desc">Name of the parent company or company owner</div>',
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $vocabulary = taxonomy_vocabulary_machine_name_load('facilities_construction');
  $element_info = element_info('hierarchical_select');
  $form['organigation_main_container']['organigation_detail_container']['left']['m6organization_type']= array(
	'#type'=>'hierarchical_select',
	'#title' => 'M6Company Type',
	'#field_prefix' => '<div class="organization-desc">Select the appropriate company type</div>',
	'#default_value' => 0,
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
	'#process' => array_merge($element_info['#process'], array('hs_taxonomy_widget_process')),
	'#config' => array(
      'module' => 'hs_taxonomy',         
      'params' => array(
		'vid' => (int) $vocabulary->vid,
		'exclude_tid' => NULL,
		'root_term' => NULL,
		'entity_count_for_node_type' => NULL,
	  ),
    ),
  );
  
  
   $form['organigation_main_container']['organigation_detail_container2']['left']['phone_no']= array(
	'#type'=>'textfield',
	'#title' => 'Mobile Phone Number',
	'#required' => TRUE,
	//'#attributes' => array('placeholder'=>'(000) 000 - 0000'),
	'#element_validate' => array('international_phone_no_element_validate'),
	'#attributes' => array('class' => array('international_phone-number')),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
	'#attached' => array(
	  'css'=> array(
	    drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css',
	  ),
	  'js'=>array(
	    drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js',
		drupal_get_path('module', 'international_phone') . '/js/international_phone.js'
	  ),
	),
  );
  
  
  $form['organigation_main_container']['organigation_detail_container']['right']['legal_name']= array(
	'#type'=>'textfield',
	'#title' => 'Legal Name',
	'#field_prefix' => '<div class="organization-desc">Company name as it appears on the incorporation documents</div>',
	'#required' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $field = field_info_field('field_legal_structure');
  $allowed_values = list_allowed_values($field);
  $form['organigation_main_container']['organigation_detail_container']['right']['legal_structure']= array(
	'#type'=>'select',
	'#title' => 'Legal Structure',
	'#field_prefix' => '<div class="organization-desc">The legal structure under which the company was created</div>',
	'#required' => TRUE,
	'#options' => $allowed_values,
	'#empty_option' =>'',
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $DiversityOptions = db_select('node','n')->fields('n',array('nid','title'))->condition('n.type','diversity','=')->condition('n.status',1,'=')->execute()->fetchAllKeyed(0,1);
  
  $DiversityOptions = array('_none'=>'- None -')+$DiversityOptions;
  
  $form['organigation_main_container']['organigation_detail_container']['right']['diversity_credentials']= array(
	'#type'=>'select',
	'#title' => 'Diversity Credentials',
	'#field_prefix' => '<div class="organization-desc">Hold down CTRL to select multiple credentials</div>',
  '#attributes' => array('class' => array('addcom_diversity_credentials')),
	'#required' => TRUE,
	'#empty_value'=> '',
	'#options' => $DiversityOptions,
	'#multiple' => TRUE,
	'#chosen' => TRUE,
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );

/******************************************************signup dir*********************************************************************************/
$doptions  = hcfm_nodenid_nodetitle_by_node_type('diversity',0,0);
//pre($doptions ); 

//$form =  array();
  //$form['organigation_main_container']['organigation_detail_container']['diversity_credentials_outer1'] = array(
   // '#markup'=> '<div class="col-md-12 padding-5 addcompany-diversity-credentials-outer">',
 // );
$fieldMapping = array();
            $credentialsMapping = array();
            $credentialsNids = array();
            $credentialsMappingDetail = array();
            
                $field = field_info_field('field_form_fields');
                $allowed_values = list_allowed_values($field);
                if (!empty($allowed_values)) {
                    foreach ($allowed_values as $diversityFieldsName => $diversityFieldsLabel) {
                        $fieldMapping[$diversityFieldsName] = array(
                            'field-info' => field_info_field($diversityFieldsName),
                            'field-instance' => field_info_instance('node', $diversityFieldsName, 'credentials')
                        );
                    }
                }
                
            //drup_msg($field);    
            //drup_msg($allowed_values);
            //drup_msg($fieldMapping);  
foreach ($doptions as $k => $v) {
                $relatedcredNid = '';
                if (isset($credentialsMapping[$k])) {
                    $relatedcredNid = $credentialsMapping[$k];
                }
                $node = node_load($k);
                $wtitle = $node->title;
                $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k] = array(
                    '#type' => 'fieldset',
                    '#title' => $wtitle,
                    '#tree' => TRUE,
                    '#prefix' => '<div class="form-group"><div id="customwrap' . $k . '" class="custwrapcrd org-diversity-wrapper customwrapcrd_' . $k . '">',
                    '#suffix' => '</div></div>',
                    '#weight' => $field_diversity_credentials_weight + 1,
                );
                $form['#step_children']['custwrap' . $k] = 'step_co_supplier_diversity';
                $fields = field_get_items('node', $node, 'field_form_fields');
                foreach ($fields as $var => $val) {
                    $fieldname = $val['value'];
                    $finfo1 = $fieldMapping[$fieldname]['field-info'];
                    $finfo2 = $fieldMapping[$fieldname]['field-instance'];
                    $label = $finfo2['label'];
                    if ($finfo1['type'] == 'list_text') {
                        $defValue = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && $issessionarr[$fn] != 'None') {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            //$defValue = get_field_value('list_text', $fieldname, $relatedcredNid);
                            $defValue = $credentialsMappingDetail[$relatedcredNid]->field_accredited_by_value;
                        }
                        $options = $finfo1['settings']['allowed_values'];
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                            '#type' => 'select',
                            '#title' => $label,
                            '#options' => $options,
                            '#parents' => array('diversity_credendial', $k, $fieldname),
                            '#default_value' => $defValue,
                            '#prefix' => '<div class="form-wrapper2">',
                                //'#suffix' => '</div>', //for grouping 3 box
                        );
                    }
                    if ($finfo1['type'] == 'datetime' || $finfo1['type'] == 'date' || $finfo1['type'] == 'datestamp') {
                        $defValue = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && !empty($issessionarr[$fn])) {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            // $defValue = get_field_value('date', $fieldname, $relatedcredNid);
                            if ($fieldname == 'field_cred_start_date') {
                                $defValue = $credentialsMappingDetail[$relatedcredNid]->field_cred_start_date_value;
                            } else if ($fieldname == 'field_credential_end_date') {
                                $defValue = $credentialsMappingDetail[$relatedcredNid]->field_credential_end_date_value;
                            } else {
                                $defValue = '';
                            }
                        }
                        $dtstmp = !empty($defValue) ? strtotime($defValue) : '';

                        if ($fieldname == 'field_cred_start_date') {

                            $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                                '#type' => 'date_popup',
                                '#title' => $label,
                                '#date_format' => 'm/d/Y',
                                '#parents' => array('diversity_credendial', $k, $fieldname),
                                    //'#default_value' => date('m/d/Y'),
                                    //'#default_value' => date('Y-m-d H:i:s', $dtstmp),
                                    //'#prefix' => '<div class="form-wrapper2 form-wrapper3">', //for grouping 3 box
                                    //'#suffix' => '</div>', //for grouping 3 box
                            );
                            if (!empty($dtstmp)) {
                                $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k]['#default_value'] = date('Y-m-d H:i:s', $dtstmp);
                            }
                        } else if ($fieldname == 'field_credential_end_date') {
                            $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                                '#type' => 'date_popup',
                                '#title' => $label,
                                '#date_format' => 'm/d/Y',
                                '#parents' => array('diversity_credendial', $k, $fieldname),
                                //'#default_value' => date('m/d/Y'),
                                //'#default_value' => date('Y-m-d H:i:s', $dtstmp),
                                //'#prefix' => '<div class="form-wrapper2 form-wrapper3">', //for grouping 3 box
                                '#suffix' => '</div>',
                            );
                            if (!empty($dtstmp)) {
                                $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k]['#default_value'] = date('Y-m-d H:i:s', $dtstmp);
                            }
                        }
                    }

                    if ($finfo1['type'] == 'text_long') {
                        $defValue = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && !empty($issessionarr[$fn])) {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            //$defValue = get_field_value('text_long', $fieldname, $relatedcredNid);
                            $defValue = $credentialsMappingDetail[$relatedcredNid]->field_credential_comments_value;
                        } //pre($defValue); 
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                            '#type' => 'textarea',
                            '#title' => $label,
                            '#default_value' => $defValue,
                            '#parents' => array('diversity_credendial', $k, $fieldname),
                            '#prefix' => '<div class="form-wrapper2 form-wrapper-comment">',
                            '#suffix' => '</div>',
                        );
                    }
                    if ($finfo1['type'] == 'file') {
                        $defValue = $defval = '';
                        $fn = $fieldname . $k;
                        if (!empty($issessionarr) && isset($issessionarr[$fn]) && !empty($issessionarr[$fn]) && $issessionarr[$fn] != 0) {
                            $defValue = $issessionarr[$fn];
                        } else if ($relatedcredNid && is_numeric($relatedcredNid)) {
                            //$defValue = get_field_value('file', $fieldname, $relatedcredNid);
                            $defValue = $credentialsMappingDetail[$relatedcredNid]->field_credential_doc_fid;
                        }

                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k]['markup2' . $k] = array('#markup' => '<div class="form-wrapper2 cust-file-mfiled">');

                        if (!empty($defValue)) {
                            //$file = file_load($defValue); 
                            //$filename = $file->filename;
                            $filename = $credentialsMappingDetail[$relatedcredNid]->filename;
                            $defval = '<img src="/modules/file/icons/text-plain.png" title="text/plain" alt="" class="file-icon">' . $filename;
                            $form['organigation_main_container']['organigation_detail_container']['custwrap' . $k]['markup' . $k] = array('#markup' => $defval);
                        }

                        $fileext = $finfo2['settings']['file_extensions'];
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k][$fieldname . $k] = array(
                            '#type' => 'managed_file',
                            '#title' => $label,
                            '#parents' => array('diversity_credendial', $k, $fieldname),
                            '#upload_location' => 'private://',
                            //'#description' => t('Allowed extensions: txt, doc, pdf, docx, jpg, jpeg, gif, png, bmp, xls, xlsx'),
                            '#upload_validators' => array(
                                'file_validate_extensions' => array($fileext),
                            // Pass the maximum file size in bytes
                            //'file_validate_size' => array(MAX_FILE_SIZE*1024*1024),
                            ),
                                //'#prefix' => '<div class="form-wrapper2"><div class="cust-fdef">'.$defval.'</div>',
                                //'#prefix' => '<div class="form-wrapper2">',
                                //'#suffix' => '</div>',
                        );
                        $form['organigation_main_container']['organigation_detail_container']['full']['custwrap' . $k]['markup3' . $k] = array('#markup' => '</div>');
                    }
                }
            }
/*$form['organigation_main_container']['organigation_detail_container']['diversity_credentials_outer2'] = array(
    '#markup'=> '</div">',
  );*/
//pre($form);
/***************************************************************************************************************************************/





  
  $form['organigation_main_container']['organigation_detail_container2']['right']['organization_website_url']= array(
	'#type'=>'textfield',
	'#title' => 'Company Website URL',
	'#field_prefix' => '<span class="organization-desc">( www.xyz.com )</span>',
	'#required' => TRUE,
	'#element_validate' => array('url_validate_url'),
	'#attributes' => array('placeholder'=>'www.xyz.com'),
	'#prefix' => '<div class="form-group">',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organigation_location_container'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organigation-location-section"><label for="edit-location">Location Information <span class="form-required" title="This field is required.">*</span></label>',
	'#suffix' => '</div>',
  );
  
  $field = field_info_field('field_org_address');
  $instance = field_info_instance('node', 'field_org_address', 'organization');
  $address = addressfield_default_values($field,$instance);
  $handlers = array('address' => 'address',);
  $context = array('mode' => 'form');
  $form['organigation_main_container']['organigation_location_container']['location'] = addressfield_generate($address, $handlers, $context);
  $form['organigation_main_container']['organigation_location_container']['location']['country']['#access'] =FALSE;
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['#attributes']['class'][] = 'row';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['#attributes']['class'][] = 'margin-5';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['thoroughfare']['#prefix'] = '<div class="col-md-6 col-sm-6 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['thoroughfare']['#suffix'] = '</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['premise']['#prefix'] = '<div class="col-md-6 col-sm-6 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['street_block']['premise']['#suffix'] = '</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['#attributes']['class'][] = 'row';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['#attributes']['class'][] = 'margin-5';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['locality']['#prefix']='<div class="col-md-4 col-sm-4 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['administrative_area']['#prefix']='<div class="col-md-6 col-sm-6 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['postal_code']['#prefix']='<div class="col-md-2 col-sm-2 col-xs-12 padding-5 form-group">';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['locality']['#suffix']='</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['administrative_area']['#suffix']='</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['postal_code']['#suffix']='</div>';
  $form['organigation_main_container']['organigation_location_container']['location']['locality_block']['administrative_area']['#empty_option'] ='';
  
 
  
  $form['organigation_main_container']['organigation_keyword']= array(
	'#type'=>'textfield',
	'#title' => 'Keyword',
	'#title_display' => 'invisible',
	'#prefix' => '<div class="organigation-keyword-section form-group"><label for="edit-keyword">Increase your M6Connect Presence </label><div class="organization-desc1"><strong>Add Keywords</strong> to help others narrow their search results. Add up to 5 keywords separated by space.<span class="form-required" title="This field is required.">*</span></div>',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organization_logo_contianer']= array(
    '#type' => 'container',
	'#prefix' => '<div class="organigation-logo-section"><label for="edit-logo">Company Logo </label><div class="organization-desc">jpg, jpeg, png file type only. May not exceed 500kb.</div>',
	'#suffix' => '</div>',
  );
  
  $form['organigation_main_container']['organization_logo_contianer']['organization_logo'] = array(
	'#title' => 'Company Logo',
	'#title_display' => 'invisible',
	'#type' => 'managed_file',
	//'#description' => t('jpg, jpeg, png file type only. May not exceed 500kb.'),
	'#upload_location' => 'private://',
	"#upload_validators"  => array(
	  'file_validate_is_image' => array(),
	  "file_validate_extensions" => array("png gif jpg jpeg"),
		'file_validate_image_resolution_new' => array('229x198', '229x198'),
	),
  );
  
  $form['organization_action2'] = array(
	'#type' => 'container',
	'#prefix' => '<div class="organization-action-section pull-right">',
	'#suffix' => '</div>',
  );
  
   $form['organigation_main_container']['organization_action2']['submit2']= array(
	'#type' => 'submit',
	'#value' => 'Continue',
	'#name' => 'complete_company',
	'#submit' => array('join_new_organization_submit'),
	'#prefix' => '<div class="organization-action-section pull-right"><div class="form-group"><span class="do-it-later-link">'.l('Cancel',$form_state['cancel_request']).'</span>&nbsp;&nbsp;',
	'#suffix' => '</div></div>',
  );
  
  }
	$form['#validate'][] = 'join_new_organization_validate';
  return $form;	
}

function choose_container_submit_handler(&$form,&$form_state){
  global $user;
  //drup_msg($form_state);
  $values = $form_state['input'];
  if(!empty($values['join_company'])){
	$account = user_load($user->uid);
    $edit['field_user_company']['und'][0]['target_id'] = $values['join_company'];
	$edit['field_organization_mail']['und'][0]['email'] = $values['create_company'];
	//$values['create_company']
    user_save($account, $edit);
	if(db_table_exists('m6connect_company_join_request')){
	  db_merge('m6connect_company_join_request')
	  ->key(array('entity_id'=>$values['join_company'],'user_uid'=>$account->uid,'status'=>0))
	  ->fields(array(
	    'entity_id'=>$values['join_company'],
		'user_uid'=>$account->uid,
		'join_email'=>$values['create_company'],
		'timestamp'=>time(),
		'status'=>0,
	  ))->execute();	
	}
	
    $_SESSION['non_company_popup'] = 1;
	if(isset($values['invite_join_requester_from_com'],$values['invite_join_requester_from'],$values['invite_join_requester_to']) && !empty($values['invite_join_requester_from_com']) && !empty($values['invite_join_requester_from']) && !empty($values['invite_join_requester_to'])){
	  $uservalues = array(
		'entity_type' => 'user',
		'entity' => $account,
		'state' => OG_STATE_ACTIVE,
	  );
	  $og_membership = og_group('node', $values['invite_join_requester_from_com'], $uservalues);
	  $ogrolesk = og_roles('node', 'organization');
      $ogroles = array_flip($ogrolesk);
	  $user_role = $ogrolesk[$ogroles['staff']];
      og_role_grant('node', $values['invite_join_requester_from_com'], $account->uid, $ogroles['staff']);	
	  $_SESSION['company'] = $values['invite_join_requester_from_com'];
	  //drup_msg($values['invite_join_requester_from_com']);
	  //drup_msg($values['invite_join_requester_from']);
	  //drup_msg($values['invite_join_requester_to']);
	  //drup_msg($account);
	  
	}else{
	  join_company_notification_entry($values['join_company']);
	}
	drupal_goto('dashboard');
	//$form_state['redirect'] ='dashboard';
  }else{
	$form_state['join_organization_step'] =2;
	$form_state['rebuild'] =TRUE;  
  }
}

function join_new_organization_validate($form, &$form_state) {
	$legal_structure = $form_state['values']['legal_structure'];
	$state = $form_state['values']['administrative_area'];
	$organization_name = $form_state['values']['organization_name'];
	$has_count_values = exist_company_state_legal_structure($legal_structure,$state,$organization_name);
	if(!empty($has_count_values)){
		form_set_error('time', $organization_name.' is already registered with same Legal Structure and State. Please register your company with different name .');
    }
    //****************************check organization title name*******//
    if(!empty($organization_name)){
	     $query = db_select('node', 'n');
	     $query->fields('n',array('nid','title'));
	     $query->condition('n.type', 'organization'); 
	     $query->condition('n.title', $organization_name);      
	     $CompanyTitle = $query->execute()->fetchObject();
	     //echo $organization_name;
	     //print "<pre>"; print_r($CompanyTitle); die;
	     if($organization_name == $CompanyTitle->title){
		form_set_error('organization_name', ''.$organization_name.' is already registered. Please register your company with different name.');
	    }
    }
     //****************************End check organization title name*****//
    
}


function join_new_organization_submit(&$form,&$form_state){ 
  global $user;
  $values = $form_state['values'];
  $node = new stdClass();
  $node->type = 'organization';
  node_object_prepare($node);

  // When the node is created by the user, storing M6Level as 2 if user is not
  // admin.
  $node->field_m6level[LANGUAGE_NONE][0]['value'] = '2';

  // Although we had set default values for source and service fields, which
  // would be auto inserted in node_object_prepare, as we are not showing this
  // fields to non-admins. But, in case if an admin is creating it, then we need
  // to respect the admin's manual selection. So working on it.
  /*if (in_array('administrator', $user->roles)) {
    if (isset($values['source'])) {
      $node->field_source_[LANGUAGE_NONE][$i]['value'] = $source;
    }
  }*/

  if (in_array('administrator', $user->roles)) {
    if (isset($values['source'])) {
      $i = 0;
      foreach ($values['source'] as $source) {
        $node->field_m6source[LANGUAGE_NONE][$i]['value'] = $source;
        $i++;
      }
    }
  }
  // Same is the case for service field, but it is accessible to both drupal
  // admin and company admin.
  if (array_key_exists(5, $user->roles) || array_key_exists(3, $user->roles)) {
    if (isset($values['service'])) {
      $node->field_service[LANGUAGE_NONE][0]['value'] = $values['service'];
    }
  }
  
  $node->field_company_email['und'][0]['email']= $values['create_company'];
  $node->field_company_gpo['und'][0]['value']= $values['create_company_gpo'];
  $node->title = $values['organization_name'];
  $node->field_legal_name['und'][0]['value'] = $values['legal_name'];
  $node->field_owner_name['und'][0]['value'] = $values['owner_name'];
  $node->field_legal_structure['und'][0]['value'] = $values['legal_structure'];
  $node->field_org_phone['und'][0]['value'] = $values['phone_no'];
  $node->field_website['und'][0]['value'] = $values['organization_website_url']; 
  $node->field_org_address['und'][0]['thoroughfare'] = $values['thoroughfare'];
  $node->field_org_address['und'][0]['premise'] = $values['premise'];
  $node->field_org_address['und'][0]['locality'] = $values['locality'];
  $node->field_org_address['und'][0]['administrative_area'] = $values['administrative_area']; 
  $node->field_org_address['und'][0]['postal_code'] = $values['postal_code'];
  $node->field_org_address['und'][0]['country'] = $values['country']; 
  $node->field_main_location_type['und'][0]['value'] = 'main-location';
  $node->field_keywords['und'][0]['value'] = $values['organigation_keyword'];
  $node->field_show_company_in_search['und'][0]['value'] = 1; 
  $node->field_type_of_company['und'][0]['value'] = 'company';
  $index =0;
  foreach($values['diversity_credentials'] as $delta => $diversityId){
	if(is_numeric($diversityId)){
	  $node->field_diversity_credentials['und'][$index++]['target_id']=$diversityId;
	}
  }
  if(isset($values['m6organization_type'][0]) && !empty($values['m6organization_type'][0]['tid'])){
	$node->field_facilities_construction['und'][0]['tid']= $values['m6organization_type'][0]['tid']; 
  }
  if($values['organization_logo'] != 0){
	$logo = file_load($values['organization_logo']);
	$logo->status = FILE_STATUS_PERMANENT; 
	file_save($logo);
	$logo = (array)$logo;
	$node->field_logo['und'] = array($logo);
	
  }
  node_save($node);

/************************************************************************************************/

  $inserted_diversity_credentials = array();
  if (isset($values) && !empty($values['diversity_credentials'])) {
    foreach ($values['diversity_credentials'] as $dive_cre_key) {
      $credentialNode = new stdClass();
      $credentialNode->type = 'credentials';
      node_object_prepare($credentialNode);
      $credentialNode->language = LANGUAGE_NONE;
      $credentialNode->uid = $user->uid;
      $credentialNode->title = 'Credential-' . uniqid();
      $credentialNode->field_cred_for_diversity['und'][0]['target_id'] = $dive_cre_key;
      $credentialNode->field_cred_for_company['und'][0]['target_id'] = $node->nid;
        /*if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_comments'])) {
          $temp = $values['diversity_credendial'][$dive_cre_key]['field_credential_comments'];
          $credentialNode->field_credential_comments['und'][0]['value'] = $temp;
        } */    
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_cred_start_date'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_cred_start_date'];
        $credentialNode->field_cred_start_date['und'][0] = array(
          'value' => date('Y-m-d H:i:s', strtotime($temp)),
          'timezone' => 'UTC',
          'timezone_db' => 'UTC',
        );
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_end_date'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_credential_end_date'];
        $credentialNode->field_credential_end_date['und'][0] = array(
          'value' => date('Y-m-d H:i:s', strtotime($temp)),
          'timezone' => 'UTC',
          'timezone_db' => 'UTC',
        );
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_comments'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_credential_comments'];
        $credentialNode->field_credential_comments['und'][0]['value'] = $temp;
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_accredited_by'])) {
        $temp = $values['diversity_credendial'][$dive_cre_key]['field_accredited_by'];
        $credentialNode->field_accredited_by['und'][0]['value'] = $temp;
      }
      if (!empty($values['diversity_credendial'][$dive_cre_key]['field_credential_doc'])) {
        $temp = file_load($values['diversity_credendial'][$dive_cre_key]['field_credential_doc']);
        if ($temp) {
          $temp->status = FILE_STATUS_PERMANENT;
          $temp->display = 1;
          file_save($temp);
          $credentialNode->field_credential_doc['und'][0] = (array) $temp;
        }
      }
      node_save($credentialNode);
      $inserted_diversity_credentials[] = $credentialNode->nid;
    }
  }

  if (!empty($inserted_diversity_credentials)) {
    $temp = array();
    foreach ($inserted_diversity_credentials as $delta33 => $item33) {
      $temp[$delta33] = array('target_id' => $item33);
    }
    $node2 = node_load($node->nid);
    $node2->field_dcrednid_22['und'] = $temp;
    node_save($node2);
  }
  //drup_msg($temp);
  /************************************************************************************************/
  
  drupal_goto('node/'.$node->nid.'/edit');
}
function international_phone_no_element_validate($element, &$form_state, $form){
	
	if(strlen($element['#value']) < 10) {
     form_error($element, t('Please enter valid Phone Number'));
   }
	
}
function add_international_phone_no_element_validate($element, &$form_state, $form){
	if(strlen($element['#value']) < 10) {
     form_error($element, t('Please enter valid Phone Number'));
   }
}