<?php

/**
 * @file
 * Contains the theme's functions to manipulate Drupal's default markup.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728096
 */
/**
 * Override or insert variables into the maintenance page template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("maintenance_page" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_maintenance_page(&$variables, $hook) {
  // When a variable is manipulated or added in preprocess_html or
  // preprocess_page, that same work is probably needed for the maintenance page
  // as well, so we can just re-use those functions to do that work here.
  m6connect_preprocess_html($variables, $hook);
  m6connect_preprocess_page($variables, $hook);
  }
  // */

/**
 * Override or insert variables into the html templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("html" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_html(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');

  // The body tag's classes are controlled by the $classes_array variable. To
  // remove a class from $classes_array, use array_diff().
  //$variables['classes_array'] = array_diff($variables['classes_array'], array('class-to-remove'));
  }
  // */

/**
 * Override or insert variables into the page templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_page(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');
  }
  // */

/**
 * Override or insert variables into the node templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_node(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');

  // Optionally, run node-type-specific preprocess functions, like
  // m6connect_preprocess_node_page() or m6connect_preprocess_node_story().
  $function = __FUNCTION__ . '_' . $variables['node']->type;
  if (function_exists($function)) {
  $function($variables, $hook);
  }
  }
  // */

/**
 * Override or insert variables into the comment templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_comment(&$variables, $hook) {
  $variables['sample_variable'] = t('Lorem ipsum.');
  }
  // */

/**
 * Override or insert variables into the region templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("region" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_region(&$variables, $hook) {
  // Don't use Zen's region--sidebar.tpl.php template for sidebars.
  //if (strpos($variables['region'], 'sidebar_') === 0) {
  //  $variables['theme_hook_suggestions'] = array_diff($variables['theme_hook_suggestions'], array('region__sidebar'));
  //}
  }
  // */

/**
 * Override or insert variables into the block templates.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
  function m6connect_preprocess_block(&$variables, $hook) {
  // Add a count to all the blocks in the region.
  // $variables['classes_array'][] = 'count-' . $variables['block_id'];

  // By default, Zen will use the block--no-wrapper.tpl.php for the main
  // content. This optional bit of code undoes that:
  //if ($variables['block_html_id'] == 'block-system-main') {
  //  $variables['theme_hook_suggestions'] = array_diff($variables['theme_hook_suggestions'], array('block__no_wrapper'));
  //}
  }
  // */
function m6connect_preprocess_privatemsg_view(&$vars) {
    global $user;

    $message = $vars['message'];
    $vars['mid'] = isset($message->mid) ? $message->mid : NULL;
    $vars['message_classes'] = isset($message->classes) ? $message->classes : array();
    $vars['thread_id'] = isset($message->thread_id) ? $message->thread_id : NULL;
    $vars['author_picture'] = theme('user_picture', array('account' => $message->author));
    // Directly address the current user if he is the author.
    if ($user->uid == $message->author->uid) {
        $vars['author_name_link'] = t('You');
    } else {
        $vars['author_name_link'] = privatemsg_recipient_format($message->author);
    }
    $vars['message_timestamp'] = privatemsg_format_date($message->timestamp);

    $message->content = array(
        '#view_mode' => 'message',
        'body' => array(
            '#markup' => check_markup($message->body, $message->format),
            '#weight' => -4,
        ),
    );

    if ($message->has_tokens) {
        // Replace tokens including option to add a notice if the user is not a
        // recipient.
        $message->content['body']['#markup'] = privatemsg_token_replace($message->content['body']['#markup'], array('privatemsg_message' => $message), array('privatemsg-token-notice' => TRUE, 'sanitize' => TRUE));
    }

    // Build fields content.
    field_attach_prepare_view('privatemsg_message', array($vars['mid'] => $message), 'message');
    $message->content += field_attach_view('privatemsg_message', $message, 'message');

    // Render message body.
    $vars['message_body'] = drupal_render($message->content);
    $vars['message_actions'] = array();
    if (isset($vars['mid']) && isset($vars['thread_id']) && privatemsg_user_access('delete privatemsg')) {
        $vars['message_actions'][] = array('title' => t('Delete'), 'href' => 'messages/delete/' . $vars['thread_id'] . '/' . $vars['mid']);
    }
    $vars['message_actions'][] = array('title' => t('Forward'), 'href' => 'messages/new/forword/' . $vars['mid']);

    $vars['message_anchors'][] = 'privatemsg-mid-' . $vars['mid'];
    if (!empty($message->is_new)) {
        $vars['message_anchors'][] = 'new';
        $vars['new'] = drupal_ucfirst(t('new'));
    }

    // call hook_privatemsg_message_view_alter
    drupal_alter('privatemsg_message_view', $vars);

    $vars['message_actions'] = !empty($vars['message_actions']) ? theme('links', array('links' => $vars['message_actions'], 'attributes' => array('class' => array('privatemsg-message-actions', 'links', 'inline')))) : '';

    $vars['anchors'] = '';
    foreach ($vars['message_anchors'] as $anchor) {
        $vars['anchors'] .= '<a name="' . $anchor . '"></a>';
    }
}

function m6connect_theme(&$existing, $type, $theme, $path) {
    global $user;
    //if(array_key_exists(2, $user->roles) && !array_key_exists(3, $user->roles)){ 
    return array(
        'user_login_block' => array(
            'template' => 'templates/user-login',
            //'arguments' => array('form' => NULL),
            'render element' => 'form',
        ),
        'user_register_form' => array(
            'render element' => 'form',
            'path' => drupal_get_path('theme', 'm6connect') . '/templates',
            'template' => 'user-register',
        //'preprocess functions' => array('m6connect_preprocess_user_register_form'),
        ),
        'user_profile_form' => array(
            'render element' => 'form',
            'path' => drupal_get_path('theme', 'm6connect') . '/templates',
            'template' => 'user-profile-edit',
        ),
        /* 'organization_node_form' => array(
          'arguments' => array(
          'form' => NULL,
          ),
          'template' => 'templates/organization--edit', // this must be the name of the file you created. Our file was title "article--edit.tpl.php" so we use article--edit
          'render element' => 'form',
          ), */

        /* 'clarification_node_form' => array(
          'arguments' => array(
          'form' => NULL,
          ),
          'template' => 'templates/clarification-node-form', // this must be the name of the file you created. Our file was title "article--edit.tpl.php" so we use article--edit
          'render element' => 'form',
          ), */

        // other theme registration code...
        'onboarding_node_form' => array(
            'arguments' => array(
                'form' => NULL,
            ),
            'template' => 'templates/onboarding-edit', // this must be the name of the file you created. Our file was title "article--edit.tpl.php" so we use article--edit
            'render element' => 'form',
        ),
    );
    //}
}

function m6connect_preprocess_user_register_form(&$vars) {
  $vars['form']['group_timezone_container']['timezone']['timezone']['#title'] = 'Time Zone';

    /* 	$args = func_get_args();
      array_shift($args);
      $form_state['build_info']['args'] = $args; */

    //$vars['form'] = drupal_build_form('user_register_form');
    //$vars['form']['actions']['submit']['#value'] = t('Submit');
}

function m6connect_preprocess_html(&$variables, $hook) {
    $status = drupal_get_http_header("status");
    if ($status == '403 Forbidden') {
        $variables['classes_array'][] = 'custom-access-denied';
    }
}

function m6connect_preprocess_page(&$variables) { //pre($variables,1);
    global $user;
    drupal_add_library('system', 'drupal.ajax');
    drupal_add_library('system', 'drupal.form');
    if (arg(0) == 'user' && is_numeric(arg(1)) && !empty(arg(2)) && arg(2) == 'edit') {
        drupal_set_title('Personal Profile');
    }

    if (current_path() == 'dashboard' && user_is_logged_in()) {
        $variables['theme_hook_suggestions'][] = 'page__dashboard';
    }

    if (isset($variables['node']->type) && $variables['node']->type == 'organization' && arg(0) == 'node' && is_numeric(arg(1)) && empty(arg(2))) {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
    }
    if (isset($variables['node']->type) && $variables['node']->type == 'groups' && arg(0) == 'node' && is_numeric(arg(1)) && empty(arg(2))) {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
    }
    if (isset($variables['node']->type) && in_array($variables['node']->type, array('organization', 'rfp', 'project')) && arg(0) == 'node' && is_numeric(arg(1)) && arg(2) == 'edit') {
        $variables['theme_hook_suggestions'][] = 'page__node__edit__' . $variables['node']->type;
    }
    //if (isset($variables['node']->type) && $variables['node']->type == 'insurance_certificates' && arg(0) == 'node' && is_numeric(arg(1)) && empty(arg(2))) {
    if (isset($variables['node']->type) && $variables['node']->type == 'insurance_certificates' && arg(0) == 'node' && is_numeric(arg(1))) {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
    }
    if (isset($variables['node']->type) && $variables['node']->type == 'contract' && arg(0) == 'node' && is_numeric(arg(1))) {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
    }
    if (arg(0) == 'insurance-feedback' && is_numeric(arg(1)) && empty(arg(2))) {
        $variables['theme_hook_suggestions'][] = 'page__insurance__feedback';
    }
    if (isset($variables['node']->type) && $variables['node']->type == 'front_page' && arg(0) == 'node' && is_numeric(arg(1))) {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
    }
    if (isset($variables['node']->type) && $variables['node']->type == 'front_featured_products' && arg(0) == 'node' && is_numeric(arg(1))) {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
    }
    if (isset($variables['node']->type) && $variables['node']->type == 'page' && arg(0) == 'node' && is_numeric(arg(1))) {
	   $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
   }

    //$views_page = views_get_page_view(); pre($views_page);
    if (($views_page = views_get_page_view()) && in_array($views_page->name, array("insurance_certificates", "insurance_contracts"))) {
        //$variables['theme_hook_suggestions'][] = 'page__views__insurance';
    }

    if (arg(0) == 'user' && is_numeric(arg(1)) && empty(arg(2))) {
        $variables['theme_hook_suggestions'][] = 'page__user__view';
    }


    $status = drupal_get_http_header("status");
    if (array_key_exists(2, $user->roles) && !array_key_exists(3, $user->roles)) {
        if (isset($variables['node']->type)) {
            $nodetype = $variables['node']->type;
            if ($nodetype == 'organization') {

                $to_be_removed = array('node/%/group', 'node/%/view');
                foreach ($variables['tabs'] as $group_key => $tab_group) {
                    if (is_array($tab_group)) {
                        foreach ($tab_group as $key => $tab) {
                            if (isset($tab['#link']['path']) && in_array($tab['#link']['path'], $to_be_removed)) {
                                unset($variables['tabs'][$group_key][$key]);
                            }
                        }
                    }
                }
            }
        }
    }
    if (arg(0) == 'sendinvite' && !arg(1)) {
        $variables['theme_hook_suggestions'][] = 'page__sendinvite';
    }
    if ($status == '403 Forbidden') {
        $variables['theme_hook_suggestions'][] = 'page__403';
        drupal_set_title(' Login or Register');
    }

    if (arg(0) == 'node' && arg(1) == 'add' && arg(2) == 'organization') {
        $variables['theme_hook_suggestions'][] = 'page__node__add__organization';
    }


    if (isset($variables['node']->type) && $variables['node']->type == 'node_gallery_item') {
        $variables['theme_hook_suggestions'][] = 'page__' . $variables['node']->type;
        $variables['node_content'] = & $variables['page']['content']['system_main']['nodes'][arg(1)];
    }

    if (arg(0) == 'proposals' && !empty(arg(1)) && !empty(arg(2))) {
      $variables['theme_hook_suggestions'][] = 'page__proposals__' . arg(2);
    }
}

function m6connect_preprocess_user_login_block(&$variables) {

    $variables['form']['actions']['submit']['#value'] = t('Submit');
    $variables['form']['links']['#markup'] = '<div class="item-list"><class="last"><a href="/user/password" title="Request new password via e-mail.">Forgot your password?</a></div>';
    $variables['form']['name']['#title'] = t('Email');
    $variables['form']['name']['#attributes']['placeholder'] = t('Your email address');
    $variables['form']['pass']['#attributes']['placeholder'] = t('Your password');

    $variables['rendered'] = drupal_render_children($variables['form']);
}

function m6connect_form_alter(&$form, &$form_state, $form_id) {//drup_msg($form_id); 
    global $user;
    if ($form_id == 'user_login') { //drup_msg($form);//pre($form);
	    $form['name']['#attributes'] = array('class'=>array('user-login-field')); 
        $form['actions']['submit']['#value'] = 'SUBMIT';
/*         if(!isset($form_state['ajax'])){
          drupal_set_message('<pre>'.print_r($form,1).'</pre>');
		   pre($form);$form['name']['#value']
          }*/ 
		  
		$email_auto = '';
		//if($_POST['name']){
		///  $email_auto = $_POST['name'];
		//}else 
		if (isset($form_state['input']) && !empty($form_state['input']['name']) && !filter_var($form_state['input']['name'], FILTER_VALIDATE_EMAIL) === false) {
		  $email_auto = $form_state['input']['name']; 
		}
        $form['#attributes']['class'][] = 'user-login-form';
        $form['links']['#markup'] = '<div class="item-list">
	<ul><li class="first">' . l('Forgot Password?', 'user/password', array('query' => array ('name' => $email_auto),'#attributes' => array('title' => 'Forgot Password?'))) . '</li></ul></div>';
    }
    if ($form_id == 'rfp_node_form') { //kpr($form);
        $steps = array('step_basic_information', 'step_timeline', 'step_rfp_proposals', 'step_rpf_documents');
        if (in_array($form_state['storage']['step'], $steps)) {
            if (isset($form['nid']) && !empty($form['nid']['#value'])) {
                $rfpNode = node_load($form['nid']['#value']);
                $form['actions']['cancel'] = array(
                    '#type' => 'submit',
                    '#value' => 'Cancel',
                    '#submit' => array('custom_cancel_submit_hander_callback'),
                    '#attributes' => array('class' => array('rfp-edit-cancel-submit')),
                    '#weight' => 9,
                );

                if ((isset($rfpNode->field_parent_rfp_id['und']) && !empty($rfpNode->field_parent_rfp_id['und'][0]['value'])) && ((!isset($rfpNode->field_is_forwarded_rfp_submitted['und'])) || (isset($rfpNode->field_is_forwarded_rfp_submitted['und']) && $rfpNode->field_is_forwarded_rfp_submitted['und'][0]['value'] == 0))) {
                    if (isset($form['actions']['delete'])) {
                        $form['actions']['delete']['#access'] = FALSE;
                    }
                    if (isset($form['actions']['cancel'])) {
                        $form['actions']['cancel']['#access'] = FALSE;
                    }
                    if (isset($form['actions']['skip'])) {
                        $form['actions']['skip']['#access'] = FALSE;
                    }
                    $form['forward_rfp_flag'] = array(
                        '#type' => 'value',
                        '#value' => 1,
                    );
                    $form['#step_children']['forward-rfp-flag'] = 'step_basic_information';
                } else {
                    if (isset($form['actions']['delete'])) {
                        $form['actions']['delete']['#access'] = TRUE;
                    }
                    if (isset($form['actions']['previous'])) {
                        $form['actions']['previous']['#access'] = FALSE;
                    }
                    if (isset($form['actions']['skip'])) {
                        $form['actions']['skip']['#access'] = FALSE;
                    }

                    if ($form_state['storage']['step'] == 'step_rpf_documents') {
                        if (isset($form['actions']['submit'])) {
                            $form['actions']['submit']['#access'] = TRUE;
                        }
                        //$form['actions']['submit']['#submit'][] = 'custom_rfp_submit_handler_callback'; }
                        if (isset($form['actions']['next'])) {
                            $form['actions']['next']['#access'] = FALSE;
                        }
                    } else if ($form_state['storage']['step'] == 'step_rfp_proposals') {
                        if (isset($form['actions']['submit'])) {
                            $form['actions']['submit']['#access'] = FALSE;
                        }
                        if (isset($form['actions']['next'])) {
                            $form['actions']['next']['#access'] = FALSE;
                        }
                        if (isset($form['actions']['delete'])) {
                            $form['actions']['delete']['#access'] = FALSE;
                        }
                        if (isset($form['actions']['cancel'])) {
                            $form['actions']['cancel']['#access'] = FALSE;
                        }
                    } else {
                        //if(isset($form['actions']['submit'])) { $form['actions']['submit']['#access'] = FALSE; }
                        //if(isset($form['actions']['next'])) { $form['actions']['next']['#access'] = TRUE;  $form['actions']['next']['#value'] = 'Save'; }
                        if (isset($form['actions']['next'])) {
                            $form['actions']['next']['#access'] = FALSE;
                        }
                    }
                }
            } else if (!isset($form['nid']) || empty($form['nid']['#value'])) {
                $form['actions']['submit']['#value'] = 'Save as Draft';
                if ($form_state['storage']['step'] == 'step_rpf_documents') {
                    $form['actions']['next2'] = array(
                        '#type' => 'submit',
                        '#value' => 'Save as Draft',
                        '#submit' => array('node_form_submit'),
                    );
                    $form['actions']['submit']['#value'] = 'Next';
                    $form['actions']['submit']['#submit'][] = 'custom_rfp_node_add_submit';
                    $form['actions']['previous']['#weight'] = 4;
                    $form['actions']['next2']['#weight'] = 5;
                    $form['actions']['submit']['#weight'] = 6;
                }
            }
        }
		//kpr($form);
		foreach($form['field_rfp_documents']['und'] as $index => $collArr){
		  if(is_numeric($index)){
		    foreach($collArr['field_rfp_document']['und'] as $delta => $fieldArr){
			  if(is_numeric($index) && isset($fieldArr['#upload_location'])){
			    $form['field_rfp_documents']['und'][$index]['field_rfp_document']['und'][$delta]['#upload_location'] = 'public://tmp'; 
			  }
		    }
		  }
		}
    }
    if ($form_id == 'clarification_msg_form') {
        
    }
    if ($form_id == 'project_node_form' || $form_id == 'rfp_node_form') {
        //kpr($form);
        $form['actions']['submit']['#attributes']['alt'] = $form['actions']['submit']['#value'];
        $form['actions']['submit']['#attributes']['title'] = $form['actions']['submit']['#value'];
        $form['actions']['next']['#attributes']['alt'] = $form['actions']['next']['#value'];
        $form['actions']['next']['#attributes']['title'] = $form['actions']['next']['#value'];
        $form['actions']['previous']['#attributes']['alt'] = $form['actions']['previous']['#value'];
        $form['actions']['previous']['#attributes']['title'] = $form['actions']['previous']['#value'];
        $form['actions']['delete']['#attributes']['alt'] = $form['actions']['delete']['#value'];
        $form['actions']['delete']['#attributes']['title'] = $form['actions']['delete']['#value'];
        $form['actions']['cancel']['#attributes']['alt'] = $form['actions']['cancel']['#value'];
        $form['actions']['cancel']['#attributes']['title'] = $form['actions']['cancel']['#value'];
    }
    if ($form_id == 'user_pass'){
      $form['name']['#attributes'] = array('class'=>array('user-pass-reset-field')); 
	}
    if (in_array($form_id, array('user_pass', 'user_login')) && isset($form_state['ajax']) && $form_state['ajax'] == 1) {
		
        $form['headed-login-container'] = array(
            '#type' => 'container',
            '#weight' => -10,
        );
        $form['headed-login-container']['login-markup'] = array(
            '#markup' => '<div class="login-markup-close-icon"><a href="javascript:void(0);" onclick="jQuery(\'span.popups-close\').click();"><i class="fa fa-times-circle"></i></a></div>
<div class="login-markup-header-image"><img src="/sites/all/themes/m6connect/images/m6-login-logo.png" class="login-header-image" /></div>
<div class="login-markup-header-text">Access Records. Contact Clients. Stay Organized. Be Successful.</div>',
            '#prefix' => '<div class="login-markup-header">',
            '#suffix' => '</div>',
        );
    }	
    //Hide next button for filling company profile in two step
    if ($form_id == 'organization_node_form') {
        if (arg(0) == 'node' && arg(1) == 'add') {
            if ($form_state['storage']['step'] == 'step_co_public_profile') {
                //if(isset($form['actions']['next'])) { $form['actions']['next']['#access'] = FALSE; }
                /* $form['actions']['cancel'] = array(
                  '#type'=> 'button',
                  '#value' => 'Cancel',
                  '#submit' => array('organization_custom_cancel_submit'),
                  '#attributes' => array('class'=> array('organization-edit-cancel-submit')),
                  '#weight' => 9,
                  ); */
                $form['actions']['organization_cancel'] = array(
                    '#markup' => '<span class="org-cancel-spn">' . l('cancel', '/', array('attributes' => array('class' => array('org-cancel-btn', 'btn', 'btn-primary', 'form-submit')))) . '</span>',
                    '#weight' => 100,
                );
            }
        }
    }

    //Change upload_location
    $formFieldMapping = array(
        'organization_node_form' => array(
            'field_logo', 'field_company_profile_cover_img',
        ),
        'user_profile_form' => array(
            'field_profile_photo', 'field_user_profile_photo', 'field_user_profile_cover_img',
        ),
        'project_node_form' => array(
            'field_images', 'field_project_cover_image',
        ),
        'rfp_node_form' => array(
            'field_rfp_logo',
        ),
        'insurance_certificates_node_form' => array(
            'field_attach_certificates'
        ),
    );

    if (array_key_exists($form_id, $formFieldMapping)) {
        foreach ($formFieldMapping[$form_id] as $delta => $fieldName) {
            if (isset($form[$fieldName], $form[$fieldName]['und'])) {
                foreach ($form[$fieldName]['und'] as $delta => $fieldArr) {
                    if (is_numeric($delta) && isset($form[$fieldName]['und'][$delta]['#upload_location'])) {
                        $form[$fieldName]['und'][$delta]['#upload_location'] = 'public://tmp';
                    }
                }
            }
        }
    } 

    if(($form_id == 'alert_archive_search_form') || ($form_id == 'alert_sent_message_search_form')) { 
      $form['#prefix'] = '<div class="m6alert-list-message-div">';
      $form['#suffix'] = '</div>';
    } 
	if($form_id == 'search_form'){
      $form['#attributes']['style'] = 'display:none;';
    }
	
	if($form_id == 'prochat_member_chat_form'){//kpr($form);
	  //$form['project_dashboard_chat_new']['#attributes']['onkeypress'][]='if(event.keyCode==13){this.form.submit();}';	
	}
	if($form_id == 'user_register_form'){//drup_msg($form['account']);   
	  $form['check_ava_user']= array(
	    '#markup' => '',
		'#prefix' => '<div id="avaiblity-continer-dialog">',
		'#suffix' => '</div>',	  
	  );  
	}
	
	if ($form_id == 'user_login'){
     $form['actions']['submit']['#value' ] = t('Sign In');  //change button text here
  }
}

/**
 * Create a direct relationship link
 */
function m6connect_user_relationships_request_relationship_direct_link($variables) {
    $relate_to = $variables['relate_to'];
    $relationship_type = $variables['relationship_type'];
    //safety, revert to  a generic link
    if (!isset($relationship_type)) {
        return theme('user_relationships_request_relationship_link', array('relate_to' => $relate_to));
    }
    return l(
            t("<i class='fa fa-arrow-circle-o-right'></i> Connect", array('%name' => format_username($relate_to)) + user_relationships_type_translations($relationship_type)), "relationship/{$relate_to->uid}/request/{$relationship_type->rtid}", array(
        'query' => drupal_get_destination(),
        'html' => TRUE,
        'attributes' => array('class' => array('user_relationships_popup_link', 'connect', 'btn', 'btn-primary', 'pull-right')),
            )
    );
}

/**
 * Remove relationship link
 */
function m6connect_user_relationships_remove_link($variables) {
    $uid = $variables['uid'];
    $rid = $variables['rid'];
    return l(
            t('Remove'), "user/{$uid}/relationships/{$rid}/remove", array(
        'title' => array('title' => t('Remove')),
        'query' => drupal_get_destination(),
        'attributes' => array('class' => array('user_relationships_popup_link', 'remove_link')),
            )
    );
}

/**
 * Returns HTML for an image field widget.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render element representing the image field widget.
 *
 * @ingroup themeable
 */
function m6connect_image_widget($variables) {
    $element = $variables['element']; //pre($element);
    $exts = $element['#upload_validators']['file_validate_extensions'][0]; //pre($exts);
    $output = '';
    $output .= '<div class="image-widget form-managed-file clearfix">';

    if (isset($element['preview'])) {
        $output .= '<div class="image-preview">';
        $output .= drupal_render($element['preview']);
        $output .= '</div>';
    }

    $output .= '<div class="image-widget-data">';
    if ($element['fid']['#value'] != 0) {
        $element['filename']['#markup'] .= ' <span class="file-size">(' . format_size($element['#file']->filesize) . ')</span> ';
    }
    /*    if ($variables['element']['#entity']->type == 'rfp') {
      $output .= ' <span class="cust-img-extension pull-right"> <span class="cust-ext-label">Allowed file types: </span><strong>' . $exts . '</strong></span>';
      } */
    $output .= drupal_render_children($element);
    $output .= '</div>';
    $output .= '</div>';

    return $output;
}

/**
 * Returns HTML for a group of file upload widgets.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render element representing the widgets.
 *
 * @ingroup themeable
 */
function m6connect_file_widget_multiple($variables) {
    global $company;
		
    //pre($company->title);pre($variables);
    //pre('dfds',1);
    $element = $variables['element'];
    $_SESSION['file-check_custom'] = $element;
    // Special ID and classes for draggable tables.
    $weight_class = $element['#id'] . '-weight';
    $table_id = $element['#id'] . '-table';

    // Build up a table of applicable fields.
    $headers = array();
    $headers[] = t('File Information');
    if ($element['#display_field']) {
        $headers[] = array(
            'data' => t('Display'),
            'class' => array('checkbox'),
        );
    }
    $headers[] = t('Weight');
    if ($variables['element']['#field_name'] == 'field_proposal_document_picture' || $variables['element']['#field_name'] == 'field_image_upload') {
        $headers[] = t('Type');
        $headers[] = t('Uploaded Date');
    }
    // Insurance certificate
    if ($variables['element']['#field_name'] == 'field_attach_certificates') {
        //$headers[] = t('Company');	
    }
    if ($variables['element']['#field_name'] == 'field_routing_document_file') {
        $headers[] = '';
    } else {
        $headers[] = t('Operations');
    }

    // Get our list of widgets in order (needed when the form comes back after
    // preview or failed validation).
    $widgets = array();
    foreach (element_children($element) as $key) {
        $widgets[] = &$element[$key];
    }
    usort($widgets, '_field_sort_items_value_helper');

    $rows = array();
    foreach ($widgets as $key => &$widget) {
        // Save the uploading row for last.
        if ($widget['#file'] == FALSE) {
            $widget['#title'] = $element['#file_upload_title'];
            $widget['#description'] = $element['#file_upload_description'];
            continue;
        }

        // Delay rendering of the buttons, so that they can be rendered later in the
        // "operations" column.
        $operations_elements = array();
        foreach (element_children($widget) as $sub_key) {
            if (isset($widget[$sub_key]['#type']) && $widget[$sub_key]['#type'] == 'submit') {
                hide($widget[$sub_key]);
                $operations_elements[] = &$widget[$sub_key];
            }
        }

        // Delay rendering of the "Display" option and the weight selector, so that
        // each can be rendered later in its own column.
        if ($element['#display_field']) {
            hide($widget['display']);
        }
        hide($widget['_weight']);

        // Render everything else together in a column, without the normal wrappers.
        $widget['#theme_wrappers'] = array();
        $information = drupal_render($widget);
		
		if (isset($variables['element']['#field_name']) && 
		  in_array($variables['element']['#field_name'], array('field_attach_driving_licence','field_attach_copy'))){
			if(isset($widget['#file'],$widget['#file']->fid) && $widget['#file']->type == 'image' &&  !empty($widget['#file']->uri)){
			  $style_name = ($variables['element']['#field_name']=='field_attach_copy')?'pic_50x50':'pic_350x150';
			  $information1 = theme('image_style', array('style_name' => $style_name, 'path' =>$widget['#file']->uri, 'getsize' => TRUE));
			  $information = $information1.$information; 	
			}
		}

        // Render the previously hidden elements, using render() instead of
        // drupal_render(), to undo the earlier hide().
        $operations = '';
        foreach ($operations_elements as $operation_element) {
            $operations .= render($operation_element);
        }
        $display = '';
        if ($element['#display_field']) {
            unset($widget['display']['#title']);
            $display = array(
                'data' => render($widget['display']),
                'class' => array('checkbox'),
            );
        }
        $widget['_weight']['#attributes']['class'] = array($weight_class);
        $weight = render($widget['_weight']);
				$update_date='';
				if ($variables['element']['#field_name'] == 'field_proposal_document_picture'){
          $update_date = date("m/d/Y h:i A");	
					$upload_type = 'test';				
				}else{
				  $update_date = date("d/m/Y g:i A");
				}
				// Arrange the row with all of the rendered columns.
        $row = array();
        $row[] = $information;
        if ($element['#display_field']) {
            $row[] = $display;
        }
        $row[] = $weight;
        if ($variables['element']['#field_name'] == 'field_proposal_document_picture' || $variables['element']['#field_name'] == 'field_image_upload') {
            $file_mime = explode('/',file_get_mimetype($widget['#file']->uri));
						$file_mime = (isset($file_mime[1]))?$file_mime[1]:'';
						$row[] = '<img src="'.file_icon_url($widget['#file']).'"/>';						
            $row[] = $update_date;
						
        }
				
        // Insurance certificate
        if ($variables['element']['#field_name'] == 'field_attach_certificates') {
            //$row[] = $company->title; 	
        }
        $row[] = $operations;
        $rows[] = array(
            'data' => $row,
            'class' => isset($widget['#attributes']['class']) ? array_merge($widget['#attributes']['class'], array('draggable')) : array('draggable'),
        );
    }

    drupal_add_tabledrag($table_id, 'order', 'sibling', $weight_class);

    $output = '';
    $output = empty($rows) ? '' : theme('table', array('sticky'=>FALSE,'header' => $headers, 'rows' => $rows, 'attributes' => array('id' => $table_id)));
    $output .= drupal_render_children($element);
    return $output;
}

function m6connect_preprocess_node(&$variables) {
    
}

function m6connect_preprocess_flag(&$variables) {
    $flag = flag_get_flag('people_bookmark');
    if ($flag && $variables['flag']->fid == $flag->fid && $variables['flag']->name == 'people_bookmark') {
        $variables['flag_classes_array'][] = 'send-message btn btn-primary';
    }
}

function m6connect_preprocess_views_view_table(&$vars) {
    $viewNameApplyTableClass = array(
        'm6rfp_for_proposal',
        'm6project_for_proposal',
        'm6companies'
    );
    if (in_array($vars['view']->name, $viewNameApplyTableClass)) {
        $vars['classes_array'][] = 'm6connect-custom-table';
    }
}

function m6connect_preprocess_views_view_fields__og_members_admin(&$vars) {

    //drupal_set_message('<pre>' . print_r($vars, 1) . '</pre>');
}

function m6connect_preprocess_status_messages(&$variables) {
	$error_display = $_SESSION['messages'];	
	if(isset($error_display) && !empty($error_display['error'])){
		$message = $error_display['error'][0];
		if(strpos($message,'The file is <em class="placeholder">')!==FALSE && strpos($message,'</em> exceeding the maximum file size of <em class="placeholder">5 MB</em>.')!==FALSE){
			$error_value = explode('</em>',$message);
			$_SESSION['messages']['error'][0] = $error_value[0].' could not be uploaded. File could not exceed <em class="placeholder">5 MB</em>.';							
		}
	}
}

function m6connect_form_search_block_form_alter(&$form, &$form_state, $form_id) {
  if(arg(0)=='search' && arg(1)=='node' && !empty(arg(2))){
	$search_default_value = arg(2);
	$form['search_block_form']['#default_value'] = $search_default_value; 
  }
} 

function m6connect_preprocess_search_results(&$variables) {
  $variables['search_results'] = '';
  if (!empty($variables['module'])) {
    $variables['module'] = check_plain($variables['module']);
  }
  foreach ($variables['results'] as $result) {  
	if(isset($result['node']->field_type_of_company['und'])) {
	  if($result['node']->field_type_of_company['und'][0]['value'] == 'individual') {
	    continue;
	  }
	}
    $variables['search_results'] .= theme('search_result', array('result' => $result, 'module' => $variables['module']));	    
  }  
  $variables['pager'] = theme('pager', array('tags' => NULL));
  $variables['theme_hook_suggestions'][] = 'search_results__' . $variables['module'];
}
