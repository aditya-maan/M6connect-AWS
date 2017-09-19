<?php

/**
 * @file Containes work for SCM Team Tab.
 * by - saurabh bhardwaj
 * timestamp - 1503568571
 */

function scm_team_content() {
  if (!isset($_SESSION['scm_thread_view'])) {
    $_SESSION['scm_thread_view'] = 'grid';
  }

  $elements['prgram-scm-menu-items'] = array(
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10 margin-top-10">',
    '#suffix' => '</div>',
  );

  $project_change_form = drupal_get_form('project_change_form');
  $new_team_form = drupal_get_form('new_team_form');

  $elements['project-change-form-element'] = array(
    '#markup' => drupal_render($project_change_form),
    '#prefix' => '<div class="margin-bottom-20">',
    '#suffix' => '</div>',
  );

  $elements['main-content-pre'] = array(
    '#markup' => '<div class="row">',
  );

  $elements['team-members-listing'] = array(
    '#markup' => _get_teams_listing(FALSE, $_SESSION['scm_thread_view']),
    '#prefix' => '<div class="col-md-6 col-sm-6 col-xs-12 scm-teams-listing-container"><div id="new-team-form-element" class="margin-bottom-45" style="display:none;">' . drupal_render($new_team_form) . '</div><div class="team-members-listing row">',
    '#suffix' => '</div></div>',
  );

  $elements['chat-container'] = array(
    '#markup' => render(user_messaging_callback()),
    '#prefix' => '<div class="col-md-6 col-sm-6 col-xs-12 scm-teams-chatting-container"><div class="team-members-chatting-container">',
    '#suffix' => '</div></div>',
  );

  $elements['main-content-post'] = array(
    '#markup' => '</div>',
  );

  return $elements;
}

function project_change_form() {
  //$getReqNodes = _getting_table_data_call('project_management');
  $getReqNodes = _getting_table_subcat_title('project_management');

  $form['get-scm_projects_scp'] = array(
    '#type'          => 'select',
    '#options'       => $getReqNodes,
    '#empty_option'  => 'Select Project',
    '#default_value' => isset($_SESSION['scm_project_nid']) ? $_SESSION['scm_project_nid'] : '',
    '#attributes'    => array('class'=> array('form-control get-scm_projects_scp')),
    '#ajax'          => array(
      'callback' => 'change_project_team_callback',
      'wrapper'  => 'new-team-form',
      'effect'   => 'fade',
    ),    
    '#prefix'        => '<div class="clearfix select-projects-view-teams"><div class="pull-right next-margin-0">',
    '#suffix'        => '</div></div>',
  );

  $form['team-view-type'] = array(
    '#type'          => 'select',
    '#options'       => array('grid' => t('Grid View'), 'list' => t('List View')),
    '#default_value' => isset($_SESSION['scm_thread_view']) ? $_SESSION['scm_thread_view'] : '',
    '#attributes'    => array('class'=> array('form-control')),
    '#ajax'          => array(
      'callback' => 'change_team_view_callback',
      'wrapper'  => 'new-team-form',
      'effect'   => 'fade',
    ),    
    '#prefix'        => '<div class="pull-right list-grid-view-teams"><div class="next-margin-0">',
    '#suffix'        => '</div></div>',
  );

  return $form;
}

function change_team_view_callback($form, &$form_state) {
  // Change the view type.
  $view_type = !empty($form_state['triggering_element']['#value']) ? $form_state['triggering_element']['#value'] : '';

  $commands = array();
  if (!empty($view_type)) {
    // Saving the current state in SESSION.
    $_SESSION['scm_thread_view'] = $view_type;

    // Getting data to be rendered.
    $data = _get_teams_listing(FALSE, $view_type);

    $commands[] = ajax_command_invoke('.team-members-listing', 'hide');
    $commands[] = ajax_command_html('.team-members-listing', $data);
    $commands[] = ajax_command_invoke('.team-members-listing', 'show', array('500'));
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

function new_team_form($form, &$form_state) {
  global $user, $company;

  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if (!isset($form_state['team_count'])) {
    $form_state['team_count'] = array(uniqid());
  }

  $default_values = array();

  if (!empty($form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'team_members_listing' && !empty($form_state['triggering_element']['#value'])) {
    if ($form_state['triggering_element']['#value'] == 'none') {
      $form_state['input'] = array();
      $form_state['values'] = array();
      $form_state['team_count'] = array(uniqid());
      $default_values = array();
    }
    else {
      if ($node = node_load($form_state['triggering_element']['#value'])) {
        $default_values['nid'] = $node->nid;
        $form_state['input']['name'] = $node->title;
        $default_values['name'] = $node->title;
        $default_values['description'] = strip_tags(html_entity_decode($node->body[LANGUAGE_NONE][0]['value']));
        $form_state['input']['description'] = $default_values['description'];

        // Image.
        if (!empty($node->field_file[LANGUAGE_NONE][0]['fid'])) {
          $default_values['image'] = $node->field_file[LANGUAGE_NONE][0];
        }

        // Team Members.
        if (!empty($node->field_contact_details[LANGUAGE_NONE])) {
          $form_state['team_count'] = array();
          foreach ($node->field_contact_details[LANGUAGE_NONE] as $key => $value) {
            $uniqid = uniqid();
            $form_state['team_count'][] = $uniqid;
            if (is_numeric($value['value'])) {
              $account = user_load($value['value']);
              $uname = $account->name;
            }
            else {
              $uname = $value['value'];
            }
            $default_values['members'][$uniqid] = $uname;
          }
          $form_state['team_count'][] = uniqid();
        }

        $form_state['default_values'] = $default_values;
      }
    }
  }

  $team_listing_options = _get_teams_listing(TRUE);

  $form['team_members_listing'] = array(
    '#type'    => 'select',
    '#options' => array('none' => t('None')) + $team_listing_options,
    '#prefix'  => '<div style="display:none;">',
    '#suffix'  => '</div>',
    '#ajax'    => array(
      'callback' => '_change_team_callback',
      'wrapper'  => 'team-main-container',
    ),
    '#attributes' => array('class' => array('change-team')),
  );

  $form['main-container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="team-main-container">',
    '#suffix' => '</div>',
  );

  $form['main-container']['left-container'] = array(
    '#type'   => 'container',
  );

  $form['main-container']['left-container']['node_nid'] = array(
    '#type' => 'hidden',
    '#default_value' => !empty($default_values['nid']) ? $default_values['nid'] : '',
    '#attributes' => array('class' => 'edit-node-nid-val'),
  );

  $form['main-container']['left-container']['name'] = array(
    '#type'       => 'textfield',
    '#title'      => t('Team Name'),
    '#required'   => TRUE,
    '#attributes' => array('class' => array('team-name')),
    '#default_value' => !empty($default_values['name']) ? $default_values['name'] : '',
  );

  if (!empty($default_values['image'])) {
    // If there is an image, then showing it.
    $img_url = image_style_url('media_thumbnail', $default_values['image']['uri']);
    $image_markup = '<div class="image-markup-outer pull-right">
                      <div class="image-markup pull-left">
                        <img src="' . $img_url . '" />
                      </div>';
    $image_markup .= l('<i class="fa fa-trash-o fa-2x" aria-hidden="true"></i>', 'remove-team-image/' . $default_values['nid'] . '/nojs', array('html' => TRUE, 'attributes' => array('class' => array('ctools-modal-assign-dashboard-popup-style', 'ctools-use-modal'))));

    $image_markup .= '</div>';

    $form['main-container']['left-container']['image_markup'] = array(
      '#type'   => 'markup',
      '#markup' => $image_markup,
    );
  }

  $form['main-container']['left-container']['image'] = array(
    '#type'  => 'file',
    '#title' => t('Image'),
  );

  $form['main-container']['left-container']['description'] = array(
    '#type'          => 'textarea',
    '#title'         => t('Description'),
    '#default_value' => !empty($default_values['description']) ? $default_values['description'] : '',
  );

  $form['main-container']['right-container'] = array(
    '#type'   => 'container',
  );

  $form['main-container']['right-container']['team_members'] = array(
    '#type'    => 'container',
    '#process' => array('team_members_process'),
    '#prefix'  => '<div id="team-members-container"><label>' . t('Team Members') . '</label>',
    '#suffix'  => '</div>',
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type'  => 'submit',
    '#value' => t('Save'),
    '#ajax'  => array(
      'callback' => 'submit_new_team_form_ajax',
      'wrapper'  => 'new-team-form',
    ),
  );

  $form['actions']['reset'] = array(
    '#type'   => 'markup',
    '#markup' => l(t('Cancel'), 'javascript:void(0)', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('class' => array('cancel-button', 'cancel-new-team')))),
  );

  return $form;
}

function team_members_process($elements, &$form_state) {
  $default_values = $form_state['default_values'];

  foreach ($form_state['team_count'] as $key => $uniqid) {
    $elements['member_name'][$uniqid] = array(
      '#type'          => 'textfield',
      '#title'         => t('Team Member Name'),
      '#title_display' => 'invisible',
      '#autocomplete_path' => 'users/scm-autocomplete',
      '#parents'       => array('team_members', $uniqid, 'member_name'),
      '#default_value' => !empty($default_values['members'][$uniqid]) ? $default_values['members'][$uniqid] : '',
    );
  }

  $elements['add_new_markup'] = array(
    '#markup' => '<div class="box-actions text-right"><a href="javascript:void(0);" title="Add new team member" onClick="jQuery(\'.member-name-new-row-button\').trigger(\'mousedown\'); return false;"><i class="glyphicon glyphicon-plus"></i> Add New</a></div>'
  );
  $elements['member_name_add_new_row'] = array(
    '#type'  => 'submit',
    '#value' => 'Add New',
    '#name'  => 'member_name_add_new_row',
    '#attributes'=> array('class'=> array('member-name-new-row-button'), 'title'=>'Add New Physician'),
    "#limit_validation_errors" => array(),
    '#submit'=> array('member_name_add_new_row_submit'),
    '#ajax' => array(
      'callback' => 'member_name_add_new_row_callback',
      'wrapper'  => 'team-members-container',
      'method'   => 'replace',
      'effect'   => 'fade',
      'progress' => array('type'=> 'throbber', 'message'=> NULL),
    ),
    '#prefix' => '<div class="clearfix" style="display:none;">',
    '#suffix' => '</div>',
  );

  return $elements;
}

/**
 * Submit callback for adding a new member.
 */
function member_name_add_new_row_submit($form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];
  if($triggerElement['#name'] =='member_name_add_new_row'){
    $tempIdentifer = uniqid();
    $form_state['team_count'][]  = $tempIdentifer;
    // $form_state['get_node_count2'] = FALSE;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for adding a new member.
 */
function member_name_add_new_row_callback($form, &$form_state) {
  return $form['main-container']['right-container']['team_members'];
}

/**
 * Team changes callback
 */
function _change_team_callback($form, &$form_state) {
  return $form['main-container'];
}

/**
 * Submit handler for new team form.
 */
function submit_new_team_form_ajax($form, &$form_state) {
  if (form_get_errors()) {
    return $form;
  }

  if($_FILES['files']['name'] != '') {
    $fileCount = count($_FILES['files']['name']);
    for ($i = 0; $i < $fileCount; $i++) {
      $file = file_save_upload('image', array(
      'file_validate_extensions' => array('jpg jpeg gif png txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm html csv xls'),
    
      ));
      if ($file) {
        if ($file = file_move($file, 'private://')) {
          $form_state['values']['image'] = $file;
        }
      }
    }
  }

  $values = $form_state['values'];

  if (!empty($values['node_nid'])) {
    $state = 'updated';
    // User is editing a node.
    $node = node_load($values['node_nid']);
    $node->title = $values['name'];
  }
  else {
    $state = 'created';
    $node = _node_creation_call('scm_team', $values['name']);
  }

  $node->field_project_reference[LANGUAGE_NONE][0]['nid'] = $_SESSION['scm_project_nid'];

  $node->body[LANGUAGE_NONE][0]['value'] = $values['description'];

  $node->field_contact_details = array();

  $members = array();
  if (!empty($form_state['team_count'])) {
    foreach($form_state['team_count'] as $key => $value) {
      if (!empty($values['team_members'][$value]['member_name'])) {
        $members[] = $values['team_members'][$value]['member_name'];
      }
    }

    if (!empty($members)) {
      // Filtering out duplicate entries.
      $members = array_unique($members);
      foreach($members as $key => $value) {
        $account = user_load_by_name($value);
        if ($account) {
          $node->field_contact_details[LANGUAGE_NONE][] = array('value' => $account->uid);
        }
      }
    }
  }

  // Handling Files.
  if (!empty($form_state['values']['image']->fid)) {
    $new_file = file_load($form_state['values']['image']->fid);
    $file_arr = (array)$new_file;
    $file_arr['display'] = 1;
    $node->field_file[LANGUAGE_NONE][0] = $file_arr;
  }

  node_save($node);
  if ($node->nid) {
    drupal_set_message(t('Team %title !state successfully.', array('%title' => $node->title, '!state' => $state)), 'status', FALSE);
  }
  else {
    drupal_set_message(t('Some problem occured and data could not be saved. Please try again!'), 'error', FALSE);
  }

  $commands = array();
  $commands[] = ajax_command_remove('#messages-custom');
  $commands[] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
  $commands[] = ajax_command_invoke('#new-team-form-element', 'hide', array(500));
  $commands[] = ajax_command_html('.team-members-listing', _get_teams_listing(FALSE, $_SESSION['scm_thread_view']));

  return array('#type' => 'ajax', '#commands' => $commands);
}

function change_project_team_callback($form, &$form_state) {
  if (!empty($form_state['triggering_element']['#value'])) {
    if (isset($_SESSION['scm_project_nid'])) {
      unset($_SESSION['scm_project_nid']);
    }

    $_SESSION['scm_project_nid'] = $form_state['triggering_element']['#value'];
  }
  else {
    if (isset($_SESSION['scm_project_nid'])) {
      unset($_SESSION['scm_project_nid']);
    }
  }

  $commands = array();
  $commands[] = ctools_ajax_command_redirect('/scm/thread');

  return array('#type' => 'ajax', '#commands' => $commands);
}

function remove_team_image($node, $ajax) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax'  => TRUE,
      'title' => t('Remove image of team - %title', array('%title' => $node->title)),
      'node'  => $node,
    );

    $output = ctools_modal_form_wrapper('remove_team_image_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('remove_team_image_form', $node);
  }
}

function remove_team_image_form($form, &$form_state, $node = NULL) {
  if (empty($form_state['node']) && !empty($node)) {
    $form_state['node'] = $node;
  }

  $node = $form_state['node'];

  $form = array();

  $warning_text = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to remove image from %title?', array('%title' => $node->title,)) . '</p></h4>';
  $warning_text .= '<p>' . t('This action can\'t be undone.') . '</p></div>';

  $form['warning'] = array(
    '#type' => 'markup',
    '#markup' => $warning_text,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
  );

  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click(); return false;"><input type="button" class="btn cancel-button" value="Close"></a>',
  );

  return $form;
}

function remove_team_image_form_submit($form, &$form_state) {
  if (!empty($form_state['node'])) {
    $node = $form_state['node'];
    $node->field_file[LANGUAGE_NONE] = array();
    field_attach_presave('node', $node);
    field_attach_update('node', $node);
    entity_get_controller('node')->resetCache(array($node->nid));
  }

  if ($form_state['ajax']) {
    $form_state['ajax_commands'][] = ajax_command_invoke('.image-markup-outer', 'hide', array(500));
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

function remove_team_member($node, $key, $ajax) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax'  => TRUE,
      //'title' => t('Remove member from team - %title', array('%title' => $node->title)),
      'node'  => $node,
      'key'   => $key,
    );

    $output = ctools_modal_form_wrapper('remove_team_member_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('remove_team_member_form', $node, $key);
  }
}

function remove_team_member_form($form, &$form_state, $node = NULL, $key = NULL) {
  if (empty($form_state['node']) && !empty($node)) {
    $form_state['node'] = $node;
  }

  if (empty($form_state['key']) && !empty($key)) {
    $form_state['key'] = $key;
  }

  $node = $form_state['node'];
  $key = $form_state['key'];

  $form = array();

  $warning_text = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to remove member from %title?', array('%title' => $node->title,)) . '</p></h4>';
  $warning_text .= '<p>' . t('This action can\'t be undone.') . '</p></div>';

  $form['warning'] = array(
    '#type' => 'markup',
    '#markup' => $warning_text,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
  );

  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click(); return false;"><input type="button" class="btn cancel-button" value="Close"></a>',
  );

  return $form;
}

function remove_team_member_form_submit($form, &$form_state) {
  if (!empty($form_state['node']) && isset($form_state['key'])) {
    $node = $form_state['node'];
    $key = $form_state['key'];
    unset($node->field_contact_details[LANGUAGE_NONE][$key]);
    field_attach_presave('node', $node);
    field_attach_update('node', $node);
    entity_get_controller('node')->resetCache(array($node->nid));

    if ($form_state['ajax']) {
      $form_state['ajax_commands'][] = ajax_command_html('.team-members-listing', _get_teams_listing(FALSE, $_SESSION['scm_thread_view']));
    }
  }

  if ($form_state['ajax']) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Menu callback
 */
function scm_export_reports($type = '', $node = NULL) {
  if (!empty($type) && !empty($node)) {
    global $user, $base_url, $base_path, $company;

    $path_to_theme = drupal_get_path('theme', 'm6connect');

    if (isset($company->field_logo[LANGUAGE_NONE])) {
      $companyLogo = '<img src="'.image_style_url('pic_76x76', $company->field_logo[LANGUAGE_NONE][0]['uri']).'">';
    }
    else {
      $companyLogo = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" height="70" width="70">';
    }

    // Preparing content.
    $content = theme('scorecard_export_pdf', array('node' => $node));

    // Including mpdf library
    include_once(libraries_get_path('mpdf') . '/mpdf.php'); 
    $mpdf = new mPDF('c', 'A4-L');

    $reportTitle = t('Scorecard Reports');

    $pdf_header = '<div class="page_header"><table style="margin:0; width:100%;"><tr><td width="200">' . $companyLogo . '</td><td width="300" align="center" style="vertical-align:top;"><h2>' . ucwords($reportTitle) . '</h2></td><td width="200"><p style="margin:0;">&nbsp;</p></td></tr></table></div>';

    $mpdf->SetHTMLHeader($pdf_header);

    $mpdf->SetHTMLFooter('<div class="page_footer" style="float:left; width:100%;"><div style="float:left; width:100%;"><hr style="height:1px; border:none; border-bottom:1px solid #CCC;"></div><div style="float:left; width:100%; clear:both;"><div style="float:left; width:33.33%; text-align:left;"><img src="/sites/all/themes/m6connect/images/bidder_report_footer.png" alt="res" width="100" /></div><div style="float:left; width:33.33%; text-align:center;">Page {PAGENO} of {nb}</div><div style="float:left; width:33.33%; text-align:right;">' . date("l, F d, Y") . '</div></div></div>');

    $mpdf->setAutoTopMargin = 'stretch';
    $mpdf->setAutoBottomMargin = 'stretch';

    // Getting custom and style css.

    $css_all = '';
    foreach (drupal_add_css() as $key => $value) {
      if (strpos($key, 'sites/all/themes/m6connect/') !== 0) {
        // We do not want any module or library css.
        continue;
      }

      $css_all .= file_get_contents($base_url . '/' . $value['data']);
    }

    $css_all .= file_get_contents('https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css');
    $mpdf->WriteHTML($css_all, 1);
    // $mpdf->WriteHTML($stylesheets_custom, 1);
    $mpdf->WriteHTML($content, 2);


    print $mpdf->Output('Scorecard-report-m6connect.pdf', 'D');
    drupal_exit();
  }
  else {
    // If we do not have sufficient information, then set an error message, and
    // redirect the user to reports page.
    drupal_set_message(t('Something unusal happened, and your request could not be processed. There might be a technical problem. Please try again later.'), 'error', FALSE);
    drupal_goto('scm/my-reporting');
  }
}