<?php
/*
 * Start work for m6connect contract
 * generating m6connect contract form.
 
 */

function contract_initiation() {
	global $user, $company;
	$elements = array();
	$elements['prgram-scm-menu-items'] = array(
		'#markup' => m6connect_contract_list_menu(),
		'#prefix' => '<div class="clearfix csemanager-sub-menu-new margin-top-10 margin-bottom-45 scm-product-submenu-sp">',
    	'#suffix' => '</div>',  
	);

	$elements['contract-form']= array(
		'#markup' => drupal_render(drupal_get_form('_contract_initiation_form')),
		'#prefix' => '<div class="clearfix margin-bottom-10">',
		'#suffix' => '</div>',
	);

	return $elements;
} 


function _contract_initiation_form($form, &$form_state) {
  global $company;
  $externaltemp = array('External', 'Template Contract');
  $form['#attributes']['class'] = array('contract-new-form-custom-class');

  $form['external-template'] = array(
		'#type' 			=> 'radios',
		'#options' 			=> $externaltemp,	
		'#default_value' 	=> '',
		'#required'      	=> TRUE,
		'#title'			=> 'External or Template Contract',
		'#attributes' 		=> array('class'=> array('external-template','form-inline','custom-form-inline-radio')),
		'#prefix'        	=> '<div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        	=> '</div></div></div>',
  );
  
  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix contract-initiation"><div id="contract_initiation_main_container" class="contract-detail clearfix">',  
    '#process' => array('contract_initiation_main_container_process'),
  );
  
  $form['submit']['save_coontract'] = array(
    '#type'  => 'submit',
    '#name'  => 'save_coontract',
    '#value' => 'Save and Continue',
    '#validate' => array('contract_initiation_validate'),
    '#submit'  => array('contract_initiation_submit'),
    '#attributes' => array('class'=>array('scm-my-submit-custom-btn')),
  );

  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('cancel_contract_initiation'),
    '#suffix' => '</div></div>',
    '#limit_validation_errors' => array(),
  );

  return $form;
}


/* 
Main container process form
****/
function contract_initiation_main_container_process($element, &$form_state) {

	drupal_add_js(drupal_get_path('module', 'm6connect_contract') . '/js/m6connect_contract.js');

	global $company;

	$default_values = array();
	if (!empty($form_state['default_values']['main_container'])) {
		$default_values = $form_state['default_values']['main_container'];
	}

	$contractentitylist = array('shc' => 'SHC', 'sgh' => 'SGH', 'scmg' => 'SCMG', 'smh' => 'SMH', 'scv' => 'SCV', 'shp' => 'SHP', 'smb' => 'SMB', 'scor' => 'SCOR', 'sharpcare' => 'SharpCare', 'smv' => 'SMV', 'srs' => 'SRS');

	$element['main-container']['full-container']['contract-initiation-node-nid'] = array(
		'#type' => 'hidden',
		'#title_display' => 'invisible',
		'#attributes' => array('class'=> array('my-request-node-nid')),
	);

	if (!empty($default_values)) {
		$element['main-container']['full-container']['my-request-node-nid']['#value'] = !empty($_SESSION['contract_initiation']) ? $_SESSION['contract_initiation'] : '';
	}

	$element['main-container']['full-container']= array(
		'#type'       => 'container',
		'#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'project-details-full-mid no-bg')),
		'#weight'     => 2,
	);

	$element['main-container']['full-container']['top-container']= array(
		'#type'       => 'container',
		'#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'top-container')),
		'#weight'     => 3,
	);
	$element['main-container']['full-container']['top-container']['contract-initiation-title'] = array(
		'#type'   => 'markup',
		'#markup' => '<div class="row"><div class="col-md-6 col-sm-6 col-xs-12"><h4>Add External Contract</h4></div></div>',
	);

	$element['main-container']['full-container']['top-container']['contract-initiation-name'] = array(
		'#type'          => 'textfield',
		'#title'         => 'Name',
		'#required'      => TRUE,
		'#attributes'    => array('class' => array('form-control', 'contract-name'), 'placeholder' => 'Type Contract Name'),
		'#default_value' => '',
		'#prefix'        => '<div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-initiation-party'] = array(
		'#type'          => 'textfield',
		'#title'         => 'Contracting Party',
		'#required'      => TRUE,
		'#attributes'    => array('class' => array('form-control', 'contract-party'), 'placeholder' => 'Vendor Name'),
		'#default_value' => '',
		'#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-type'] = array(
		'#type'          => 'select',
		'#title'         => 'Contract Type',
		'#required'      => TRUE,
		'#empty_option'  => 'Select Contract Type',
		'#options'       => getContractOptions('m6connect_contract_type_setting'),
		'#attributes'    => array('class' => array('form-control', 'contract-type'), 'placeholder' => 'Select Contract Type'),
		'#default_value' => '',
		'#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-category'] = array(
		'#type'          => 'select',
		'#title'         => 'Select Category',
		'#required'      => TRUE,
		'#empty_option'  => 'Select Category',
		'#options'       => getContractOptions('m6connect_contract_category_setting'),
		'#attributes'    => array('class' => array('form-control', 'contract-category'), 'placeholder' => 'Select Category'),
		'#default_value' => '',
		'#prefix'        => '<div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-product-service'] = array(
		'#type'          => 'select',
		'#title'         => 'Product or Service',
		'#required'      => TRUE,
		'#empty_option'  => 'Select Product or Service',
		'#options'       => getContractOptions('m6connect_contract_products_services_setting'),
		'#attributes'    => array('class' => array('form-control', 'contract-product-service'), 'placeholder' => 'Select Product or Service'),
		'#default_value' => '',
		'#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-document-type'] = array(
		'#type'          => 'select',
		'#title'         => 'Document Type',
		'#required'      => TRUE,
		'#empty_option'  => 'Select Document Type',
		'#options'       => getContractOptions('m6connect_contract_document_type_setting'),
		'#attributes'    => array('class' => array('form-control', 'contract-document-type'), 'placeholder' => 'Select Document Type'),
		'#default_value' => '',
		'#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-version-number'] = array(
		'#type'          => 'textfield',
		'#title'         => 'Contract Version Number',
		'#required'      => TRUE,
		'#attributes'    => array('class' => array('form-control', 'contract-version-number'), 'placeholder' => 'CON-2017-V.1'),
		'#default_value' => '',
		'#prefix'        => '<div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div>',
	);
	$element['main-container']['full-container']['top-container']['contract-effort'] = array(
		'#type'          => 'select',
		'#title'         => 'Effort',
		'#required'      => TRUE,
		'#empty_option'  => 'Select Effort',
		'#options'       => getContractOptions('m6connect_contract_effort_setting'),
		'#attributes'    => array('class' => array('form-control', 'contract-effort'), 'placeholder' => 'Select Effort'),
		'#default_value' => '',
		'#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div></div>',
	);
	$element['main-container']['full-container']['middle-container']= array(
		'#type'       => 'container',
		'#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'middle-container', 'hide')),
		'#weight'     => 4,
	);
	$element['main-container']['full-container']['middle-container']['field_contract_i_upload_contract'] = array(
		'#title'			=> 'Upload Contract',
    	'#type' 			=> 'dragndrop_upload',
        '#name' 			=> 'files[field_contract_i_upload_contract][]',
    	'#upload_location' 	=> 'public://',  
    	'#attributes' 		=> array('multiple' => 'multiple','id' => 'contract-attachment-upload1', 'class'=> array('scm-my-request-attachment')),
    	'#prefix'        	=> '<div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        	=> '</div></div>',
	);
	$element['main-container']['full-container']['middle-container']['field_contract_upload_attachment'] = array(
		'#title'			=> 'Upload Attachments',
		'#type' 			=> 'dragndrop_upload',
        '#name' 			=> 'files[field_contract_upload_attachment][]',
    	'#upload_location' => 'public://',  
    	'#attributes' => array('multiple' => 'multiple','id' => 'contract-attachment-upload2', 'class'=> array('scm-my-request-attachment')),
		'#prefix'        	=> '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        	=> '</div></div></div>',
	);
	$element['main-container']['full-container']['bottom-container']= array(
		'#type'       		=> 'container',
		'#attributes' 		=> array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'bottom-container')),
		'#weight'     		=> 5,
	);
	$element['main-container']['full-container']['bottom-container']['contract-entities'] = array(
		'#type' 			=> 'checkboxes',
		'#options' 			=> $contractentitylist,	
		'#default_value' 	=> '',
		'#checkall' => TRUE,
		'#title'			=> 'Entity(s) (check all that apply)',
		'#attributes' 		=> array('class'=> array('contract-entities','form-inline','custom-form-inline-radio')),
		'#prefix'        	=> '<div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        	=> '</div></div></div>',
	);
	$element['main-container']['full-container']['bottom-container']['contract-description'] = array(
		'#type'          => 'textarea', 
		'#title'		 => 'Contract Description',
		'#default_value' => '',
		'#attributes'    => array('class'=> array('form-control','workflow-auto','contract-description'),'style' => 'min-height:auto;'),
		'#rows'          => 3,
		'#resizable'     => FALSE,
		'#prefix'        => '<div class="row"><div class="col-md-12 col-sm-12 col-xs-12"><div class="form-item clearfix">',
		'#suffix'        => '</div></div></div></div></div>',
    );

	return $element;
}

/**
 * Validate handler for scm_my_request_form.
 */
function contract_initiation_validate($form, &$form_state) {
  if(form_get_errors()){
    form_set_error('', t('Please fill all the required fields.'));
    return;
  }

}


/**
 * Submit handler for contract_initiation_form.
 */


function contract_initiation_submit($form, &$form_state) {

  	$form_values    = $form_state['values'];

	if (isset($form_values['contract-initiation-node-nid']) && !empty($form_values['contract-initiation-node-nid'])) {
		$nodesave = node_load($form_values['contract-initiation-node-nid']);
		$savestatus = 'updated';
	} else {
		$currentYear = date('Y');
		$myCounter   = variable_get('CONTRACTNumber');
		$makeSr      = str_pad($myCounter, 6, "0", STR_PAD_LEFT);
		$contractNumber   = 'CONTRACT-' . $makeSr . '-' . $currentYear;
		$contrNumber = variable_get('CONTRACTNumber');
		variable_set('CONTRACTNumber', $contrNumber + 1);
		$getTitle = $contractNumber;
		$initiationNew = 'initiationNew';
		$nodesave = _node_creation_call('contract_initiation',$getTitle);
		$savestatus = 'saved';
	}

    $nodesave->field_contract_initiation_name['und'][0]['value']		= $form_values['contract-initiation-name'];
    $nodesave->field_contract_initi_party['und'][0]['value']			= $form_values['contract-initiation-party'];
    $nodesave->field_contract_initiation_type['und'][0]['value']        = $form_values['contract-type'];
    $nodesave->field_contract_initi_category['und'][0]['value']        	= $form_values['contract-category'];
    $nodesave->field_contract_product_service['und'][0]['value']       	= $form_values['contract-product-service'];
    $nodesave->field_contract_document_type['und'][0]['value']     		= $form_values['contract-document-type'];
    $nodesave->field_contract_initiation_v_num['und'][0]['value']       = $form_values['contract-version-number'];
    $nodesave->field_contract_initiation_effort['und'][0]['value']      = $form_values['contract-effort'];
	
	if(!empty($nodesave->field_contract_initiation_entity['und'])){
		$nodesave->field_contract_initiation_entity['und']='';
	}

	foreach ($form_values['contract-entities'] as $k => $v) {
		if($v!=''){
			$nodesave->field_contract_initiation_entity['und'][]['value']  	= $v;
		}
	}

    $nodesave->field_contract_initiation_desc['und'][0]['value']        = $form_values['contract-description'];

	if ($_FILES['files']['name'] != '') {
		$fileCount = count($_FILES['files']['name']);
		$main_arr = array(
			'name'     => $_FILES['files']['name'],
			'type'     => $_FILES['files']['type'],
			'tmp_name' => $_FILES['files']['tmp_name'],
			'error'    => $_FILES['files']['error'],
			'size'     => $_FILES['files']['size'],
		);
		unset($_FILES);
		$i = 1;
		foreach ($main_arr['name'] as $key => $value) {
			if (!empty($value)) {
				foreach ($value as $key1 => $value1) {
					if (!empty($value1)) {
						$_FILES['files']['name'][$key . '__' . $i] = $main_arr['name'][$key][$key1];
						$_FILES['files']['type'][$key . '__' . $i] = $main_arr['type'][$key][$key1];
						$_FILES['files']['tmp_name'][$key . '__' . $i] = $main_arr['tmp_name'][$key][$key1];
						$_FILES['files']['error'][$key . '__' . $i] = $main_arr['error'][$key][$key1];
						$_FILES['files']['size'][$key . '__' . $i] = $main_arr['size'][$key][$key1];
						$i++;
					}
				}
			}
		}

		foreach ($_FILES['files']['name'] as $key => $value) {
			$file = file_save_upload($key, array(
			'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
			));
			if ($file) {
				if ($file = file_move($file, 'public://')) {
					$key = explode('__', $key);
					$form_state['values'][$key[0]][] = $file;
				}
			}
		}
	}

	$files_arr = array(
      'field_contract_i_upload_contract' => 'field_contract_i_upload_contract',
      'field_contract_upload_attachment' => 'field_contract_upload_attachment',
    );

    foreach ($files_arr as $node_element => $file_element) {
      if (!empty($form_state['values'][$file_element])) {
        foreach ($form_state['values'][$file_element] as $imgkey3 => $file3) {
          $new_file3 = NULL;
          if (!empty($file3->fid) && $new_file3 = file_load($file3->fid)) {
            $file_arr3 = (array)$new_file3;
            $file_arr3['display'] = 1;
            $nodesave->{$node_element}[LANGUAGE_NONE][] = $file_arr3;
          }
        }
      }
    }
  
   node_save($nodesave);

   drupal_set_message(t('Contract Initiation %title saved successfully.', array('%title' => $getTitle)), 'status', FALSE);
  
}