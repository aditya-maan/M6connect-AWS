<?php
/*
 * Start work for Scorecard
 * generating My request form, my request data table to show all records.
 * it also contains the chat feature.  
 */

################################################################################
################################  Menu Callbacks  ##############################
################################################################################

function scm_scorecard_content() {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm.js');
  $elements['scm-casemanager-menu']= array(
    '#markup' => scm_scorecard_sub_menu_links_content(),
    '#prefix' => '<div class="clearfix csemanager-sub-menu-new margin-top-10 margin-bottom-45 scm-product-submenu-sp">',
    '#suffix' => '</div>',
  );

  if (strpos($_SERVER['HTTP_REFERER'], 'scorecard/new/select-products') !== FALSE) {
    // It means we came back from select product page, so we'll need to trigger
    // the active scorecard again, so that it comes prefilled.

    // Getting active scorecard.
    $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');

    $elements['trigger-active-sc'] = array(
      '#markup' => $scorecard_nid,
      '#prefix' => '<div style="display:none;" id="trigger-active-sc-here">',
      '#suffix' => '</div>',
    );
  }

  $elements['project-form']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );

  /*$elements['prgram-project-listing'] = array(
    '#markup' => _get_scorecard_summary_table_data('casemanager'),
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="project-summary-listing" id="scorecard-information-listing">',
    '#suffix' => '</div></div></div>',
  );*/

  return $elements; 
}

function scm_scorecard_select_product_content($where = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-45">',
      '#suffix' => '</div></div>',
    );
  }

  $elements['menu-links'] = array(
    '#markup' => $where == 'new_scorecard' ? scm_scorecard_sub_menu_links_content() : scm_scorecard_dashboard_menu_links_content($where),
    '#prefix' => $where == 'new_scorecard' ? '<div class="clearfix csemanager-sub-menu-new margin-top-10 margin-bottom-45 scm-product-submenu-sp">' : '<div class="clearfix scm-main-menu margin-bottom-45">',
    '#suffix' => '</div>',
  );

  $elements['project-form']= array(
    '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_select_product_form', $where)),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );

  return $elements;
}


function scorecard_share_content($where = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu">',
      '#suffix' => '</div></div>',
    );
  }

  $elements['menu-links'] = array(
    '#markup' => $where == 'new_scorecard' ? scm_scorecard_sub_menu_links_content() : scm_scorecard_dashboard_menu_links_content($where),
    '#prefix' => $where == 'new_scorecard' ? '<div class="clearfix csemanager-sub-menu margin-top-10 margin-bottom-45 scm-product-submenu-sp">' : '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',
  );

  $elements['under_process'] = array(
    '#markup' => t('Under process...'),
  );

  return $elements;
}

function scorecard_evaluate_content($where = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu">',
      '#suffix' => '</div></div>',
    );
  }

  $elements['menu-links'] = array(
    '#markup' => scm_scorecard_dashboard_menu_links_content($where),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',
  );

  $elements['under_process'] = array(
    '#markup' => t('Under process...'),
  );

  return $elements;
}

function scorecard_decision_content($where = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu">',
      '#suffix' => '</div></div>',
    );
  }

  $elements['menu-links'] = array(
    '#markup' => scm_scorecard_dashboard_menu_links_content($where),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',
  );

  $elements['under_process'] = array(
    '#markup' => t('Under process...'),
  );

  return $elements;
}

function scm_closeout_content() {
  $elements['prgram-scm-menu-items'] = array(
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div></div>',
  );

  $elements['prgram-project-listing'] = array(
    '#markup' => '<p><center><h2>Comming Soon</h2></center></p>',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="project-summary-listing" id="scorecard-information-listing">',
    '#suffix' => '</div></div></div>',
   );

  return $elements; 
}

/**
 * Menu callback for add-scorecard-reference/%node/%node.
 */
function add_scorecard_reference($action = 'add', $node, $score_node) {
  $output = array(
    'success' => t('No'),
    'method'  => $action,
    'data'    => array(),
  );

  if (empty($node) || empty($score_node) || !is_object($node) || !is_object($score_node)) {
    drupal_json_output($output);
    drupal_exit();
  }

  global $user, $company;
  // If we have both product node and score node, then saving it's reference.
  if ($action == 'add') {
    // Saving the reference in our custom table.
    // First deleting any previous entry.
    db_delete('scorecard_references')
      ->condition('company_nid', $company->nid)
      ->condition('product_nid', $node->nid)
      ->condition('scorecard_nid', $score_node->nid)
      ->execute();

    // Now creating a new entry.
    db_insert('scorecard_references')
      ->fields(array(
        'uid'           => $user->uid,
        'company_nid'   => $company->nid,
        'product_nid'   => $node->nid,
        'scorecard_nid' => $score_node->nid,
        'created'       => REQUEST_TIME,
      ))
      ->execute();

    $vendor_nid = $node->field_manufacture_reference[LANGUAGE_NONE][0]['nid'];
    $vendor_title = _get_title_of_node($vendor_nid);
    $replace_to = array('-', ' ', '.', '_');
    $vendor_short_name = strtoupper(substr(str_replace($replace_to, '', $vendor_title), 0, 2));

    $output['success'] = t('Yes');

    $description = $sku = t('N.A.');
    $description_title = '';

    $title = $node->title;
    $title_trim = $title;
    if (strlen($title) > 20) {
      $title_trim = substr($title, 0, 19) . '...';
    }

    if (!empty($node->field_description['und'][0]['value'])) {
      $description = substr($node->field_description['und'][0]['value'], 0, 22) . '...';
      if (strlen($node->field_description['und'][0]['value']) > 22) {
        $description_title = $node->field_description['und'][0]['value'];
      }
      else {
        $description = $node->field_description['und'][0]['value'];
      }
    }
    if (!empty($node->field_sku_number['und'][0]['value'])) {
      $sku = $node->field_sku_number['und'][0]['value'];
    }

    $new_data = '<div class="col-md-3 col-sm-3 col-xs-12 remove-hide-this-product margin-bottom-15">
                  <div class="clearfix relative">
                    <div class="row margin-0 sku-items">
                      <div class="col-md-4 sku-item-left">
                        <div class="panel-body sku-item-left-icon"> ' . $vendor_short_name . ' </div>
                      </div>
                      <div class="col-md-8 padding-0 sku-item-right">
                        <div class="panel-body">
                          <span class="pull-right sku-item-right-close">
                            <i class="fa fa-times select-product-for-sc" data="remove" aria-hidden="true" style="color: #000; cursor:pointer;" id="' . $node->nid . '-' . $score_node->nid . '--scorecard"></i>
                          </span>
                          <div title="' . $title . '">' . $title_trim . '</div>
                          <div title="' . $description_title . '">' . $description . '</div>
                          <div>' . $sku . '</div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>';
    $output['data'] = $new_data;
  }

  if ($action == 'remove') {
    db_delete('scorecard_references')
      ->condition('company_nid', $company->nid)
      ->condition('product_nid', $node->nid)
      ->condition('scorecard_nid', $score_node->nid)
      ->execute();
    $output['success'] = t('Yes');
  }

  drupal_json_output($output);
  drupal_exit();
}

/**
 * Menu callback for add-scm-product/%/%ctools_js
 */
function _scm_add_product_callback($scoreCardId, $node_nid, $ajax=TRUE) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $node_title = _get_title_of_node($node_nid);

    $form_state = array(
      'ajax'        => TRUE,
      'title'       => t('Add New Product - ' . $node_title),
      'scoreCardId' => $scoreCardId,
      'node_nid'    => $node_nid,
    );

    $output = ctools_modal_form_wrapper('m6connect_scm_new_product', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('m6connect_scm_new_product', $node_nid);
  }
}

/**
 * Menu callback for node/%node/add-products
 */
function _add_products_to_node($node) {
  // First checking whether the current node has any categories added or not.
  // If not, asking the user to add first.
  $categories = _get_all_categories_by_company($node->nid);
  $elements = array();
  drupal_set_message(t('You are logged in as the administrator of Hy-Vee Construction'), 'status', FALSE);

  if (empty($categories)) {
    $elements['no-categories-found'] = array(
      '#type' => 'markup',
      '#markup' => t('There are no Categories added in your company. You can not add a product without a category, please add at least 1 category to your company.') . '<br/>' . t('To add a category <a href="@link">Click this link.</a>', array('@link' => url('node/' . $node->nid . '/edit', array('query' => array('costep' => 'step_company_categories'))))),
    );
  }
  else {
    $add_product_form = drupal_get_form('m6connect_scm_new_product', $node->nid);
    $elements['add-product-form'] = array(
      '#type' => 'markup',
      '#markup' => render($add_product_form),
    );
  }

  return $elements;
}

/**
 * Menu callback for node/%node/review-products
 */
function _review_products_to_node($node) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  $elements = array();

  $elements['review-table'] = array(
    '#type' => 'markup',
    '#markup' => _get_product_review_table(),
    '#prefix' => '<div id="review-products-table">',
    '#suffix' => '</div>',
  );

  return $elements;
}

/**
 * Menu callback for scm-add-new-vendor/%ctools_js
 */
function _scm_add_vendor_callback($ajax = TRUE) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax' => TRUE,
      'title' => t('Add New Company'),
    );

    $output = ctools_modal_form_wrapper('m6connect_scm_new_vendor', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('m6connect_scm_new_vendor');
  }
}

/**
 * Menu callback for score-card-status/%/%/%ctools_js
 */
function scorecard_status_update($status,$nodeId = 0,$ajax) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $form_state = array(
      'ajax'        => TRUE,
      'scoreStatus' => $status,
      'node_id'     => $nodeId,   
    );

    $output = ctools_modal_form_wrapper('scorecard_status_update_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('scorecard_status_update_form', $nodeId);
}

/**
 * Menu callback for
 *  - approve-deny-product/approve/%node/nojs
 *  - approve-deny-product/deny/%node/nojs
 *  - approve-deny-product/edit/%node/nojs
 */
function _approve_deny_review_products_to_node($action, $product, $ajax = NULL) {
  // This menu callback acts for all three actions.
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    if ($action != 'edit') {
      $form_state = array(
        'ajax'    => TRUE,
        'title'   => t('@action Product - %title', array('@action' => ucwords($action), '%title' => $product->title)),
        'product' => $product,
        'action'  => $action,
      );

      $output = ctools_modal_form_wrapper('approve_deny_review_product_form', $form_state);
    }
    else {
      $form_state = array(
        'ajax'        => TRUE,
        'title'       => t('@action Product - %title', array('@action' => ucwords($action), '%title' => $product->title)),
        'product' => $product,
      );

      $output = ctools_modal_form_wrapper('edit_review_product_form', $form_state);
    }

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    // If form is not served using ajax, then returning the renderable form
    // array.
    if ($action != 'edit') {
      return drupal_get_form('approve_deny_review_product_form', $product, $action);
    }
    else {
      return drupal_get_form('edit_review_product_form', $product);
    }
  }
}

/**
 * Menu callback for scorecard/evaluate/%node
 */
function scorecard_rates_evaluate_content($scorecard_node = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');
  global $user;

  // Unsetting session.
  if (isset($_SESSION['activeScorecardNid'])) {
    unset($_SESSION['activeScorecardNid']);
  }

  $elements['menu-links'] = array(
    '#markup' => scm_scorecard_dashboard_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-45">',
    '#suffix' => '</div>',
  );

  $scorecard_info = _get_scorecard_display_info($scorecard_node);

  $elements['scorecard-info']= array(
    '#markup' => drupal_render($scorecard_info),
    '#prefix' => '<div class="row margin-bottom-10">',
    '#suffix' => '</div><div class="col-md-12"><div class="row"><div class="col-md-12 col-xs-12">',
  );

  if ($user->uid == $scorecard_node->uid) {
    $view_scorecard_of = drupal_get_form('view_scorecard_of_form', $scorecard_node);
    $elements['view-scorecard-of']= array(
      '#markup' => drupal_render($view_scorecard_of),
      '#prefix' => '<div class="clearfix"><div class="pull-right evaluate-select">',
      '#suffix' => '</div></div>',
    );
  }

  $scorecard_form = drupal_get_form('scorecard_rates_evaluate_form', $scorecard_node);
  $elements['rates-evaluate-form']= array(
    '#markup' => drupal_render($scorecard_form),
    '#prefix' => '<div class="clearfix margin-bottom-10" id="form-change-here">',
    '#suffix' => '</div></div></div></div>',
  );

  return $elements;
}

/**
 * Menu callback for scorecard/cancel/%node/%ctools_js
 */
function cancel_scorecard_new($scorecard_node = NULL, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');

    $title = t('Cancel Creating Scorecard');

    $form_state = array(
      'ajax' => TRUE,
      'title' => '<h4 class="asset-popup-title-custom">' . $title . '</h4>',
      'scorecard_node' => $scorecard_node,
    );

    $output = ctools_modal_form_wrapper('cancel_scorecard_new_form', $form_state);

    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  else {
    return drupal_get_form('cancel_scorecard_new_form', $scorecard_node);
  }
}

################################################################################
##############################  End Menu Callbacks  ############################
################################################################################


############################# New Scorecard Form Start #########################

function _casemanager_scorecard_form($form, &$form_state) {
  global $company;
  $getScoreCardlist = array();
  $getScoreCard = _fetching_scorecard_information('scm_scorecard');
  foreach ($getScoreCard as $key => $value) {
     $getScoreCardlist[$value] = $value; 
  }
  $form['#attributes']['class'] = array('scorecard-new-form-custom-class');
  $form['select-scorecard'] = array(
    '#type'=>'select',
    '#options' => array('' => 'Select Scorecard') + $getScoreCardlist,
    '#attributes' => array('class'=> array('form-control', 'project_scorecard_main_pro')),
    '#ajax' => array(
      'callback'=> 'change_scorecard_callback',
      'wrapper' => 'scorecard_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );

  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix scm-scorecard"><div id="project_scorecard_main_container" class="project-detail clearfix">',  
    '#process' => array('project_scorecard_main_container_process'),
  );

  $form['submit']['save_continue'] = array(
    '#type'  => 'submit',
    '#name'  => 'save_and_continue',
    '#value' => 'Save and Continue',
    '#ajax'  => array(
      'callback' => 'scm_scorecard_submit',
      'wrapper' => '-casemanager-scorecard-form',
    ),
  );

  $form['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#submit' => array('cancel_scorecard_new_builder'),
    '#suffix' => '</div></div>',
    '#limit_validation_errors' => array(),
  );

  return $form;
}

function cancel_scorecard_new_builder($form, &$form_state) {
  // Do nothing, let the page reload.
  drupal_goto('scorecard/my-scorecards');
}

/**
 * Ajax callback for changing current active scorecard.
 */
function change_scorecard_callback($form,&$form_state) {
  global $company;
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];  

  if ($form_state['triggering_element']['#name']=='select-scorecard') {
    if (!empty($triggeringElement['#value'])) {
      $myCounter = variable_get('SCORECARDNO');
      $makeSr = str_pad($myCounter + 1, 6, "0", STR_PAD_LEFT);
      $cardNumber = 'SCO' . $makeSr . '-' . date('Y');
      $cardNode = node_load($triggeringElement['#value']);

      $storage_project = array(
        'cardNumber'    => $cardNode->title,
        'cardName'      => isset($cardNode->field_scorecard_name['und'])?$cardNode->field_scorecard_name['und'][0]['value']:'',
        'ratingDueDate' => isset($cardNode->field_rating_due_date['und'])?$cardNode->field_rating_due_date['und'][0]['value']:'',
        'projectNid'    => isset($cardNode->field_project_nid_for_scm['und'])?$cardNode->field_project_nid_for_scm['und'][0]['value']:'',
        'rfpNid'        => isset($cardNode->field_rfp_nid_for_scm['und'])?$cardNode->field_rfp_nid_for_scm['und'][0]['value']:'',
        'awardDate'     => isset($cardNode->field_recommendation_to_award_da['und'])?$cardNode->field_recommendation_to_award_da['und'][0]['value']:'',
      );

      $ratingDate = $storage_project['ratingDueDate']!=''?date('m/d/Y', strtotime($storage_project['ratingDueDate'])):'';
      $awardDate = $storage_project['awardDate']!=''?date('m/d/Y', strtotime($storage_project['awardDate'])):'';

      $commands[] = ajax_command_invoke("input.scorecard-number", 'val',array($storage_project['cardNumber']));
      $commands[] = ajax_command_invoke("select.project-name", 'val',array($storage_project['projectNid']));
	  $commands[] = ajax_command_invoke("select.project-name", 'trigger', array('change'));
      $commands[] = ajax_command_invoke("input.scorecard-name", 'val',array($storage_project['cardName']));
      $commands[] = ajax_command_invoke("select.rfp-name", 'val',array($storage_project['rfpNid']));
	  $commands[] = ajax_command_invoke("select.rfp-name", 'trigger', array('change'));
      $commands[] = ajax_command_invoke("input.rating-date", 'val',array($ratingDate));
      $commands[] = ajax_command_invoke("input.recommendation-award-date", 'val',array($awardDate));
    }
  }
  else {
    $commands[] = ajax_command_invoke("input.scorecard-number", 'val', array(''));
    $commands[] = ajax_command_invoke("select.project-name", 'val', array(''));
    $commands[] = ajax_command_invoke("input.scorecard-name", 'val', array(''));
    $commands[] = ajax_command_invoke("select.rfp-name", 'val', array(''));
    $commands[] = ajax_command_invoke("input.rating-date", 'val', array(''));
    $commands[] = ajax_command_invoke("input.recommendation-award-date", 'val', array(''));
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Main container process for scorecard form.
 */
function project_scorecard_main_container_process($element, &$form_state) {
  global $company;

  // Getting the project and RFP list by company
  $projectList = _load_project_list_with_number();
  $rfpList = _load_rfp_list_with_number();

  // Scorecard Number calculation
  $currentYear = date('Y');
  $myCounter = variable_get('SCORECARDNUMBER');
  $makeSr = str_pad($myCounter + 1, 6, "0", STR_PAD_LEFT);
  $scoreCard = 'SCO ' . $makeSr . '-' . $currentYear;

  $element['main-container']['full-container']= array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'project-details-full-mid')),
    '#weight'     => 3,
  );

  $element['main-container']['full-container']['inner-left-one']= array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('well', 'well-large', 'no-bg')),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix"><h4>Create New Scorecard</h4></div>',
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-number'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Scorecard Number',
    '#attributes'    => array('class' => array('form-control', 'scorecard-number'), 'placeholder' => 'Scorecard Number'),
    '#default_value' => isset($defaultValues['scorecard-number']) ? $defaultValues['scorecard-number'] : $scoreCard,
    '#prefix'        => '<div class="clearfix well well-large"><div class="row"><div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $element['main-container']['full-container']['inner-left-one']['project-name'] = array(
    '#type'          => 'select',
    '#title'         => 'Project Name',
    '#empty_option'  => 'Select Project Name | Number',
    '#options'       => $projectList,
    '#attributes'    => array('class' => array('form-control', 'project-name'), 'placeholder' => 'Project Name'),
    '#default_value' => isset($defaultValues['project-name']) ? $defaultValues['project-name'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
    '#select2'       => array(
      'width' => '350',
      'minimumResultsForSearch' => '5',
    ),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-name'] = array(
    '#type'          => 'textfield',
    '#title'         => 'Scorecard Name',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('form-control', 'scorecard-name'), 'placeholder' => 'Scorecard Name'),
    '#default_value' => isset($defaultValues['scorecard-name']) ? $defaultValues['scorecard-name'] : '',
    '#prefix'        => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
    '#suffix'        => '</div>',  
  );
  $element['main-container']['full-container']['inner-left-one']['rfp-name'] = array(
    '#type'          => 'select',
    '#empty_option'  => 'Select RFP Name | Number',
    '#options'       => $rfpList,
    '#title'         => 'RFP Name',
    '#attributes'    => array('class' => array('form-control', 'rfp-name'), 'placeholder' => 'RFP Name'),
    '#default_value' => isset($defaultValues['rfp-name']) ? $defaultValues['rfp-name'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
    '#select2'       => array(
      'width' => '350',
      'minimumResultsForSearch' => '5',
    ),
  );

  $element['main-container']['full-container']['inner-left-one']['rating-date'] = array(
    '#type'            => 'date_popup',
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#title'           => 'Rating Due Date',
    '#required'        => TRUE,
    '#attributes'      => array('class' => array('form-control', 'rating-date'), 'placeholder' => 'Rating Due Date'),
    '#default_value'   => isset($defaultValues['rating-date']) ? $defaultValues['rating-date'] : '',
    '#prefix'          => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix relative m6connect_programe_date">',
    '#suffix'          => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span></div>',
  );

  $element['main-container']['full-container']['inner-left-one']['recommendation-award-date'] = array(
    '#type'            => 'date_popup',
    '#date_format'     => 'm/d/Y',
    '#date_year_range' => '-3:+3',
    '#pre_render'      => array('m6connect_programe_date_prerender'),
    '#title'           => 'Recommendation to Award Date',
    '#attributes'      => array('class' => array('form-control', 'recommendation-award-date'), 'placeholder' => 'Recommendation to Award Date'),
    '#default_value'   => isset($defaultValues['recommendation-award-date'])?$defaultValues['recommendation-award-date']:'',
    '#prefix'          => '<div class="form-item clearfix relative m6connect_programe_date">',
    '#suffix'          => '<span class="input-group-addon"><span class="glyphicon glyphicon-calendar"></span></span></div></div></div></div>',
  );

  return $element;
}

/**
 * Submit handler for new scorecard form.
 */
function scm_scorecard_submit($form, &$form_state) {
  if (form_get_errors()) {
    // If there are errors on the return.
    return $form;
  }

  global $user, $company; 
  $formVal = $form_state['values'];
  $getTitle = $formVal['scorecard-number'];

  if (!empty($formVal['select-scorecard'])) {
    // We are in edit.
    $crateNode = node_load($formVal['select-scorecard']);
    $crateNode->field_scorecard_name['und'][0]['value'] = $formVal['scorecard-name']; 
    $crateNode->field_rating_due_date['und'][0]['value'] = $formVal['rating-date'];
    $crateNode->field_project_nid_for_scm['und'][0]['value'] = $formVal['project-name'];
    $crateNode->field_rfp_nid_for_scm['und'][0]['value'] = $formVal['rfp-name'];
    $crateNode->field_recommendation_to_award_da['und'][0]['value'] = $formVal['recommendation-award-date'];

    drupal_set_message('Scorecard - ' . $getTitle . ' updated successfully.');
  }
  else {
    $crateNode = _node_creation_call('scm_scorecard', $getTitle);
    $crateNode->field_scorecard_name['und'][0]['value'] = $formVal['scorecard-name']; 
    $crateNode->field_rating_due_date['und'][0]['value'] = $formVal['rating-date'];
    $crateNode->field_project_nid_for_scm['und'][0]['value'] = $formVal['project-name'];
    $crateNode->field_rfp_nid_for_scm['und'][0]['value'] = $formVal['rfp-name'];
    $crateNode->field_recommendation_to_award_da['und'][0]['value'] = $formVal['recommendation-award-date'];

    // Increasing the counter.
    $myCounter = variable_get('SCORECARDNUMBER');
    variable_set('SCORECARDNUMBER', $myCounter + 1);

    drupal_set_message('Scorecard - ' . $getTitle . ' saved successfully.');
  }

  node_save($crateNode);

  // Making this scorecard as the current scorecard.
  _make_scorecard_active($crateNode);

  if ($form_state['triggering_element']['#name'] == 'save_and_continue') {
    $commands = array();
    $_SESSION['activeScorecardNid'] = $crateNode->nid;
    $commands[] = ctools_ajax_command_redirect('scorecard/new/select-products');
    return array('#type' => 'ajax', '#commands' => $commands);
  }
}

############################# New Scorecard Form End ###########################


############################ Select Product Start ##############################

function _casemanager_scorecard_select_product_form($form, &$form_state, $where) {
  global $company;

  if ($where == 'casemanager') {
    $form['#attributes']['class'] = array('pointer-events-none');
  }

  // Handling Ajax triggers.
  if (!empty($form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'search-criteria' && !empty($form_state['triggering_element']['#value'])) {
    // Handling search criteria trigger.
    if (!empty($form_state['new_search_vendor_options'])) {
      $form_state['new_search_vendor_options'] = array();
    }

    // Getting new search vendor options according to the criteria requested.
    $form_state['new_search_vendor_options'] = _get_search_vendor_options($form_state['triggering_element']['#value']);

    if ($form_state['triggering_element']['#value'] == 'companies') {
      $form_state['add_new_company_class'] = '';
    }
    else {
      $form_state['add_new_company_class'] = 'hidden';
    }
  }

  if (!isset($form_state['add_new_company_class'])) {
    $form_state['add_new_company_class'] = 'hidden';
  }

  // Scorecard Information.
  $form['main-container']= array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix'     => '<div class="clearfix scm-scorecard"><div id="project_scorecard_main_container" class="project-detail clearfix">',  
    '#process'    => array('project_select_product_main_container_process'),
  );

  // Compare Products Container.

  // If no products, then hide this container.
  $cont_class = '';
  $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');
  $getProducts = _get_all_products_by_scorecard($scorecard_nid);
  if (empty($getProducts)) {
    $cont_class = 'hidden';
  }

  $form['main-container-2']= array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix'     => '<div class="clearfix scm-scorecard"><div id="project_scorecard_main_container_2" class="project-detail clearfix ' . $cont_class . '">',
    '#suffix'     => '</div></div>',
    '#process'    => array('project_add_product_main_container_process'),
  );

  // Search Vendor Container.
  $form['main-container-3']= array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix'     => '<div class="clearfix scm-scorecard"><div id="project_scorecard_main_container_3" class="project-detail clearfix">',
    '#process'    => array('project_add_vendor_main_container_process'),
    '#suffix'     => '</div></div>',
  );

  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }
  if ($where != 'new_scorecard') {
    // Save Button
    $form['submit']['save'] = array(
      '#type'     => 'submit',
      '#value'    => 'Save',
      '#submit'   => array('scm_product_submit'),
      '#validate' => array('scm_product_validate'),
      '#prefix'   => '<div class="clearfix custom-submit-select-pro-button '.$sharerecommendation.'">',  
    );
  }

  // Save and Continue Button
  $form['submit']['save_continue'] = array(
    '#type'     => 'submit',
    '#value'    => 'Save and Continue',
    '#submit'   => array('scm_select_pro_submit_save_continue'),
    '#validate' => array('scm_product_validate'),
  );

  if ($where == 'new_scorecard') {
    // Cancel Button.
    $form['actions']['reset'] = array(
      '#type'   => 'markup',
      '#markup' => l(t('Cancel'), 'scorecard/cancel/' . $scorecard_nid . '/nojs', array('attributes' => array('class' => array('form-submit', 'cancel-button', 'ctools-use-modal', 'ctools-modal-assign-dashboard-popup-style')))),
    );

    // Back Button.
    $form['actions']['back'] = array(
      '#type'   => 'markup',
      '#markup' => l(t('Back'), 'scorecard/new', array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
      '#suffix' => '</div></div></div>',
    );
  }
  else {
    // Cancel Button.
    $form['actions']['back'] = array(
      '#type'   => 'markup',
      '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button">',
      '#suffix' => '</div></div></div>',
    );
  }

  return $form;
}

/**
 * Process function for main-container.
 */
function project_select_product_main_container_process($element, &$form_state) {
  global $company;

  $element['main-container']['full-container']= array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight'     => 3,
  );

  $element['main-container']['full-container']['inner-left-one']= array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('margin-bottom-45')),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-info-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix custom-score-info"><div class="row">',
    '#prefix' => '<div class="well well-large no-bg">'
  );
  

  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
 
  $scoreCardData = node_load($getNodesNids);
  $ratingDate = strtotime($scoreCardData->field_rating_due_date['und'][0]['value']);
  $awardDate = strtotime($scoreCardData->field_recommendation_to_award_da['und'][0]['value']);

  // Getting all the scorecard 
  // with there name and number
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->join('field_data_field_scorecard_name', 'scn','scn.entity_id = n.nid');
  $query->fields('n', array('nid','title'));
  $query->fields('scn', array('field_scorecard_name_value')); 
  $query->condition('n.type','scm_scorecard','=');  
  $query->condition('om.gid', $company->nid, '=');
  $query->orderBy('n.nid', 'DESC');
  $getAllScards = $query->execute()->fetchAll();
  $scardArr = array();
  foreach($getAllScards as $delta => $scrdInfo) {
    $scardArr[$scrdInfo->nid] = $scrdInfo->title.' | '.$scrdInfo->field_scorecard_name_value;
  }

  $disStatus = arg(1) == 'new' ? TRUE : FALSE;
  $prefixText = arg(1) == 'new' ? 'Scorecard': 'Select Scorecard'; 
  $element['main-container']['full-container']['inner-left-one']['scorecard-number-select'] = array(
    '#type'          => 'select',
    '#options'       => $scardArr,
    '#empty_option'  => 'Choose scorecard',
    '#default_value' => $getNodesNids,
    '#disabled'      => $disStatus,
    '#attributes'    => array('class'=> array('form-control scorecard-name-title')),
    '#prefix'        => '<div class="col-md-6 col-sm-6 col-xs-12"><div class="clearfix"><p class="blue-and-bold">'.$prefixText.'</p>',
    '#suffix'        => '</div></div>',  
    '#ajax'          => array(
      'wrapper'  => 'replace-facility-options-here',
      'callback' => '_update_scorecard_based_data_view_share',
    ),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-name'] = array(
  '#markup' => '<p class="blue-and-bold">Rating Due Date</p><p class="rfp-data-date">'.date('m/d/Y', $ratingDate).'</p>',
    '#prefix' => '<div class="col-md-2 col-sm-2 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );

  $element['main-container']['full-container']['inner-left-one']['project-name'] = array(
    '#markup' => '<p class="blue-and-bold">Project Name</p><p class="prject-data-name">'.(!empty($scoreCardData->field_project_nid_for_scm['und'][0]['value'])?_get_title_of_node($scoreCardData->field_project_nid_for_scm['und'][0]['value']):'').'</p>',
    '#prefix' => '<div class="col-md-2 col-sm-2 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );

  $element['main-container']['full-container']['inner-left-one']['rfp-name'] = array(
    '#markup' => '<p class="blue-and-bold">RFP Name</p><p class="rfp-data-name">'.(!empty($scoreCardData->field_rfp_nid_for_scm['und'][0]['value'])?_get_title_of_node($scoreCardData->field_rfp_nid_for_scm['und'][0]['value']):'').'</p>',
    '#prefix' => '<div class="col-md-2 col-sm-2 col-xs-12"><div class="clearfix">',
    '#suffix' => '</div></div>',  
  );
  
  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type'   => 'markup',
    '#markup' => '</div></div></div>',
  );

  // Getting all vendor names.
  $getVendorName = _get_search_vendor_options('categories');

  // Creating select box for providing search options.
  $element['main-container']['full-container']['inner-left-one']['search-criteria'] = array(
    '#type' => 'select',
    '#options' => array('all' => t('All'), 'products' => t('Products'), 'companies' => t('Companies'),'categories' => t('Categories'),),
    '#ajax' => array(
      'callback' => 'change_search_criteria_callback',
      'wrapper' => 'main-container-select-vendor-product-page',
    ),
    '#field_prefix' => '',
    '#field_suffix' => '</div></div>',
    '#prefix' => '<div class="clearfix"><div style="display:none;">',
    '#suffix' => '</div>',
  );

  $search_criteria_text = t('Categories');
  if (!empty($form_state['values']['search-criteria'])) {
    $search_criteria_text = ucwords($form_state['values']['search-criteria']);
  }
  elseif (!empty($form_state['input']['search-criteria'])) {
    $search_criteria_text = ucwords(check_plain($form_state['input']['search-criteria']));
    if ($search_criteria_text == 'companies') {
      $form_state['add_new_company_class'] = '';
    }
  }

  $select_prefix = '<div class="input-group-btn text-right">
        <button type="button" class="btn btn-default dropdown-toggle toggle-text-here" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">' . $search_criteria_text. ' <span class="caret"></span></button>
        <ul class="dropdown-menu">
          <li><a href="javascript:void(0)" class="select-vendor-anchor" for="categories">Categories</a></li>
          <li><a href="javascript:void(0)" class="select-vendor-anchor" for="products">Products</a></li>
          <li><a href="javascript:void(0)" class="select-vendor-anchor" for="companies">Companies</a></li>
          <li><a href="javascript:void(0)" class="select-vendor-anchor" for="all">All</a></li>
        </ul>
      </div>';

  $element['main-container']['full-container']['inner-left-one']['select-vendor']['vendor-selections'] = array(
    '#type'       => 'select',
    '#options'    => !empty($form_state['new_search_vendor_options']) ? $form_state['new_search_vendor_options'] : $getVendorName,
    // '#chosen'     => TRUE,
    '#multiple'   => TRUE,
    '#attributes' => array('class'=> array('project_programe_reports_sections'), 'placeholder' => t('Search Products, Companies, & Categories'), 'onChange' => 'jQuery(".trigger-me-on-product-add").trigger("mousedown"); return false;'),
    '#prefix'     => '<div id="main-container-select-vendor-product-page" class="form-inline text-center margin-bottom-45"><div class="form-group padding-5 widen-this-choosen-box"><div class="input-group">' . $select_prefix,
    '#suffix'     => '</div></div>',
    '#validated'  => TRUE,
    '#select2'    => array(
      'width' => 500,
      'minimumResultsForSearch' => 5,
      'containerCssClass' => 'custom-select2-class',
    ),
  );

  $element['main-container']['full-container']['inner-left-one']['select-vendor']['select-vendor-submit'] = array(
    '#type' => 'button',
    '#value' => t('Search'),
    '#executes_submit_callback' => FALSE,
    '#ajax' => array(
      'callback' => 'change_search_vendor_callback',
      'wrapper'  => 'project_scorecard_main_container_3',
      'effect'   => 'fade',
      'progress' => array(
        'type' => 'throbber',
        'message' => NULL,
      ),
    ),
    '#attributes' => array('class' => array('trigger-me-on-product-add', 'hidden')),
    '#prefix' => '<div class="form-group padding-5">',
    '#suffix' => '</div><div class="form-group padding-5"><a href="/scm-add-new-vendor/nojs" class="ctools-use-modal ctools-modal-assign-asset-category-popup-style invite-directto-m6 form-submit cancel-button"> + Add New Company</a></div></div></div>',
  );

  return $element;
}

/**
 * Process function for main-container-2.
 */
function project_add_product_main_container_process($element, &$form_state) {
  global $company;

  $get_active_score_card = _fetching_scorecard_information_active('scm_scorecard');
  $getProducts = array();

  $element['main-container']['full-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight' => 3,
  );

  $element['main-container']['full-container']['inner-left-one']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('clearfix')),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-prodcut-title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="panel panel-primary"><div class="panel-heading">Product Comparision Library </div><div class="panel-body product-comparision-library-outer"><div class="clearfix product-comparision-library"><div id="projects-referenced-scorecard" class="row">',
  );

  $getProducts = _get_all_products_by_scorecard($get_active_score_card);

  if(!empty($getProducts)) {
  $i = 1;
    foreach($getProducts as $productKey => $productVal) {
      $prodData = node_load($productVal);
      $vendor_nid = $prodData->field_manufacture_reference[LANGUAGE_NONE][0]['nid'];
      $vendor_title = _get_title_of_node($vendor_nid);
      $replace_to = array('-', ' ', '.', '_');
      $vendor_short_name = strtoupper(substr(str_replace($replace_to, '', $vendor_title), 0, 2));
      $description = $sku = t('N.A.');
      $description_title = '';

      $title = $prodData->title;
      $title_trim = $title;
      if (strlen($title) > 20) {
        $title_trim = substr($title, 0, 19) . '...';
      }


      if (!empty($prodData->field_description['und'][0]['value'])) {
        $description_title = $prodData->field_description['und'][0]['value'];
        if (strlen($prodData->field_description['und'][0]['value']) > 22) {
          $description = substr($prodData->field_description['und'][0]['value'], 0, 22) . '...';
        }
        else {
          $description = $prodData->field_description['und'][0]['value'];
        }
      }
      if (!empty($prodData->field_sku_number['und'][0]['value'])) {
        $sku = $prodData->field_sku_number['und'][0]['value'];
      }
      $markup = '<div class="col-md-3 col-sm-3 col-xs-12 remove-hide-this-product margin-bottom-15">
                  <div class="clearfix relative">
                    <div class="row margin-0 sku-items">
                      <div class="col-md-4 sku-item-left">
                        <div class="panel-body sku-item-left-icon"> ' . $vendor_short_name . ' </div>
                      </div>
                      <div class="col-md-8 padding-0 sku-item-right">
                        <div class="panel-body">
                          <span class="pull-right sku-item-right-close">
                            <i class="fa fa-times select-product-for-sc" data="remove" aria-hidden="true" style="color: #000; cursor:pointer;" id="' . $productVal . '-' . $get_active_score_card . '--scorecard"></i>
                          </span>
                          <div title="' . $title . '">' . $title_trim . '</div>
                          <div title="' . $description_title . '">' . $description . '</div>
                          <div>' . $sku . '</div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>';

      $element['main-container']['full-container']['inner-left-one']['select-product'.$i] = array(
        '#markup' => $markup,
      );

      $i++;
    }
  }
  else {
    $element['main-container']['full-container']['inner-left-one']['select-product'] = array(
      '#markup' => '<h4>Click Products Below to Add to Library.</h4>',
      '#prefix' => '<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix no-product-found text-center text-muted">',
      '#suffix' => '</div></div>',
    );
  }

  $element['main-container']['full-container']['inner-left-one']['end-select-product'] = array(
  '#type' => 'markup',
  '#markup' => '</div></div></div></div>',
  );

  return $element;
}

/**
 * Process for main-container-3
 */
function project_add_vendor_main_container_process($element, &$form_state) {
  global $company;

  $getProducts = array();

  $element['main-container']['full-container'] = array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'project-details-full-mid')),
    '#weight'     => 3,
  );

  $element['main-container']['full-container']['inner-left-one']= array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('clearfix')),
  );

  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div style="display:none;"><div id="product-already-added"></div></div>',
  );

  // Rendering vendor data based on vendor autocomplete...
  $element['main-container']['full-container']['inner-left-one']['vendor-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix">',
  );

  $element['main-container']['full-container']['inner-left-one']['select-product'] = array(
    '#markup' => !empty($form_state['values']['vendor-selections']) ? vendor_base_product_callback($form_state['values']['vendor-selections']) : vendor_base_product_callback(),
    //'#markup' => '',
    '#prefix' => '<div id="vendor-base-product-container">',
    '#suffix' => '</div>',
  );
  

  $element['main-container']['full-container']['inner-left-one']['end-vendor-title'] = array(
    '#type'   => 'markup',
    '#markup' => '</div>',
  );

  return $element;
}

/**
 * Ajax callback for ['main-container']['full-container']['inner-left-one']['search-criteria']
 */
function change_search_criteria_callback($form, &$form_state) {
  return $form['main-container']['main-container']['full-container']['inner-left-one']['select-vendor'];
}

/**
 * Ajax callback for ['main-container']['full-container']['inner-left-one']['select-vendor']
 */
function change_search_vendor_callback($form,&$form_state) {
  global $company;
  $values = $form_state['values']['vendor-selections'];
  $search_crit = $form_state['values']['search-criteria'];
  $commands = array();
 
  if(!empty($values)){
    
     $commands[] = ajax_command_html("#vendor-base-product-container", vendor_base_product_callback($values));

  }
  else {
    $commands[] = ajax_command_html("#vendor-base-product-container", vendor_base_product_callback());
  }
  $commands[] = array('command' => 'hideShowPcContainer');
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Validate handler for _casemanager_scorecard_select_product_form
 * For both - Save AND Save and continue.
 */
function scm_product_validate($form, &$form_state) {
  // If user has not selected any product for the current scorecard, then 
  // show error.
  $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');
  if (count(_get_all_products_by_scorecard($scorecard_nid)) == 0) {
    // Setting the default criteria.
    $form_state['new_search_vendor_options'] = _get_search_vendor_options($form_state['triggering_element']['#value']);
    form_set_error('', t('Please select at least one product to proceed!'));
  }
}

/**
 * Submit handler for _casemanager_scorecard_select_product_form
 * Save Only.
 */
function scm_product_submit($form, &$form_state) {
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $node = !empty($getNodesNids[0]) ? node_load($getNodesNids[0]) : NULL;
  if ($node) {
    drupal_set_message(t('Scorecard %title saved successfully.', array('%title' => $node->title)), 'status', FALSE);
  }
  else {
    drupal_set_message(t('Scorecard saved successfully.'), 'status', FALSE);
  }
}

/**
 * Submit handler for _casemanager_scorecard_select_product_form
 * Save and Continue.
 */
function scm_select_pro_submit_save_continue($form, &$form_state) {
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $node = !empty($getNodesNids[0]) ? node_load($getNodesNids[0]) : NULL;

  if ($node) {
    drupal_set_message(t('Scorecard %title saved successfully.', array('%title' => $node->title)), 'status', FALSE);
  }
  else {
    drupal_set_message(t('Scorecard saved successfully.'), 'status', FALSE);
  }

  // Redirecting to next tab.
  // We have multiple urls of this page and next page, so redirecting to the
  // current url's format only.
  $form_state['no_redirect'] = FALSE;
  $current_path = current_path();
  $redirect_path = str_replace('select-products', 'question-builder', $current_path);
  $form_state['redirect'] = $redirect_path;
}

############################ Select Product Ends ###############################


############################## Add New Product #################################

/**
 * Form used to add a new product on Select Product page in scorecards.
 */
function m6connect_scm_new_product($form, &$form_state, $node_nid = NULL) {
  if (empty($form_state['node_nid']) && !empty($node_nid)) {
    $form_state['node_nid'] = $node_nid;
  }

  $form['#attributes']['class'] = array('main-addnew-prouct-popup');

  $form['#attached']['js'][] = array(
    'data' => drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js',
    'type' => 'file',
  );

  $form['main-container']['full-container']= array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('col-md-12', 'col-sm-12', 'col-xs-12', 'project-details-full-mid')),
    '#weight'     => 3,
  );

  $form['main-container']['full-container']['inner-left-one']= array(
    '#type'       => 'container',
    '#attributes' => array('class' => array('clearfix')),
  );
  
  // Initialize add new product form state
  if (empty($form_state['invite_m6_storage'])) {
    $tempIdentifer = uniqid();
    $form_state['invite_m6_storage'][]  = $tempIdentifer;
  }

  $form['main-container']['full-container']['inner-left-one']['scorecard_id'] = array(
    '#type'  => 'hidden',
    '#value' => $form_state['scoreCardId'],
  );

  $form['main-container']['full-container']['inner-left-one']['node_nid'] = array(
    '#type'  => 'hidden',
    '#value' => $form_state['node_nid'],
  );

  $form['main-container']['full-container']['product-container']['pre_container_div'] = array(
    '#markup' => '<div id="main-product-container" class="row">',
  );

  $form['main-container']['full-container']['product-container']['main_container2'] = array(
    '#type'       => 'container',
    '#theme'      => 'invite_m6_theme_scorecard',
    '#attributes' => array('class' => array('alert-container-section')),
    '#prefix'     => '<div id="alert-container-section" class="add-new-alert-detail">',
    '#suffix'     => '</div></div>',
    '#process'    => array('invite_to_m6_process_scorecard'),
  );

  $form['actions']['submit'] = array(
    '#type'       => 'submit',
    '#submit'     => array('_scm_add_product_submit'),
    '#value'      => 'Add Product',
    '#attributes' => array('class' => array('custom_scm_add_product_submit_call')), 
    '#prefix' => '<div class="clearfix margin-top-10">',
  );

  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix'     => '</div>',
  );

  return $form;
}

/**
 * Process function for ['main-container']['full-container']['product-container']['main_container2']
 */
function invite_to_m6_process_scorecard($element, &$form_state) {
  global $company;

  $storage = $form_state['invite_m6_storage'];
  $element['#storage'] = $storage;

  // Getting company categories options.
  // Start here.

  $company_categories_options = array();

  $company_categories_all = _get_all_categories_by_company($form_state['node_nid']);

  if (!empty($company_categories_all)) {
    foreach ($company_categories_all as $key => $value) {
      $company_categories_options[$value->field_category_value] = $value->field_category_value;
    }
  }

  $m6_cat_options = _get_m6_product_categories();

  foreach ($storage as $key => $uniqId) {
    $field_required = FALSE;
    if (empty($form_state['input']['alert'])) {
      $field_required = TRUE;
    }

    if (!empty($form_state['input']['alert'][$uniqId]['product-number'])) {
      $field_required = TRUE;
    }

    if (!empty($form_state['input']['alert']) && count($form_state['input']['alert']) == 1) {
      $datas = array_values($form_state['input']['alert']);
      if (empty($datas[0]['product-number'])) {
        $field_required = TRUE;
      }
    }

    $element['company-category'][$uniqId] = array(
      '#type'          => 'select',
      '#options'       => $company_categories_options,
      '#attributes'    => array('class' => array('form-control', 'project-name'), 'placeholder' => 'Choose Company Category'),
      '#prefix'        => '<div class="form-item clearfix">',
      '#suffix'        => '</div></div>',
      '#select2'       => array(
        'width' => '170',
        'minimumResultsForSearch' => '5',
      ),
      '#multiple'      => TRUE,
      '#parents'       => array('alert', $uniqId, 'company-category'),
    );

    $element['m6-product-category'][$uniqId] = array(
      '#type'          => 'select',
      '#options'       => $m6_cat_options,
      '#attributes'    => array('class' => array('form-control', 'project-name'), 'placeholder' => 'M6 Product Category'),
      '#prefix'        => '<div class="form-item clearfix">',
      '#suffix'        => '</div></div>',
      '#select2'       => array(
        'width' => '170',
        'minimumResultsForSearch' => '5',
      ),
      '#multiple'      => TRUE,
      '#required'      => $field_required,
      '#parents'       => array('alert', $uniqId, 'm6-product-category'),
    );

    $element['product-number'][$uniqId] = array(
      '#type'       => 'textfield', 
      '#attributes' => array('class'=> array('form-control','workflow-auto','product-number'), 'onblur' => 'jQuery(\'.product-workflow-action-add-details\').trigger(\'mousedown\'); return false;'),
      '#parents'    => array('alert', $uniqId, 'product-number'),
    );

    $element['catelog-number'][$uniqId] = array(
      '#type'       => 'textfield', 
      '#attributes' => array('class'=> array('form-control','workflow-auto','catelog-number')),
      '#parents'    => array('alert', $uniqId, 'catelog-number'),
    );

    $element['sku-product'][$uniqId] = array(
      '#type'          => 'textfield', 
      '#default_value' => '',
      '#attributes'    => array('class'=> array('form-control','workflow-auto','sku-product')),
      '#parents'       => array('alert', $uniqId, 'sku-product'),
    );

    $element['product-name'][$uniqId] = array(
      '#type'          => 'textfield', 
      '#default_value' => '',
      '#attributes'    => array('class'=> array('form-control','workflow-auto','product-name')),
      '#parents'       => array('alert', $uniqId, 'product-name'),
    );

    $element['url-product'][$uniqId] = array(
      '#type'          => 'textfield', 
      '#default_value' => '',
      '#attributes'    => array('class'=> array('form-control','workflow-auto','url-product'), 'placeholder' => t('Enter Product\'s URL')),
      '#parents'       => array('alert', $uniqId, 'url-product'),
    );

    $element['description-product'][$uniqId] = array(
      '#type'          => 'textarea', 
      '#default_value' => '',
      '#attributes'    => array('class'=> array('form-control','workflow-auto','description-product'), 'style' => 'min-height:auto;'),
      '#parents'       => array('alert', $uniqId, 'description-product'),
      '#rows'          => 3,
      '#resizable'     => FALSE,
    );

    $file_upload_list = '<div id="edit-alert-' . $uniqId . '-field-attachments-upload-id-filelist"></div>';
    // When adding a new element we get a fid of the previous field if any file
    // was uploaded.
    // Please note: Currently we are only allowing a single file to upload.
    if (!empty($form_state['input']['alert'][$uniqId]['field_attachments']['fid']) && $prev_file = file_load(check_plain($form_state['input']['alert'][$uniqId]['field_attachments']['fid']))) {
      // This means that we need to show the file name to user.
      $filename = $prev_file->filename;
      $filename_str = strlen($filename) > 36 ? substr($filename, 0, 36) : $filename;

      $file_upload_list = '<div id="edit-alert-' . $uniqId . '-field-attachments-upload-id-filelist">';
      $file_upload_list .= '<div class="filelist-outer">';
      $file_upload_list .= '<span class="filelist-item" title="' . $filename . '">' . $filename_str . '</span>';
      $file_upload_list .= '<i class="fa fa-times" aria-hidden="true" style="color: #000; cursor:pointer" onclick="jQuery(\'input[name=alert_' . $uniqId . '_field_attachments_remove_button]\').trigger(\'mousedown\'); return false;"></i>';
      $file_upload_list .= '<br>';
      $file_upload_list .= '</div></div>';
    }

    $element['field_attachments'][$uniqId] = array(
      '#type'            => 'managed_file',
      '#upload_location' => 'public://',
      '#attributes'      => array('class'=> array('scorecard-product-attachment-managed', $uniqId), 'data' => $uniqId),
      '#parents'         => array('alert', $uniqId, 'field_attachments'),
      '#theme'           => 'custom_file_managed_theme_scorecard',
    );

    $element['field_attachments_markup'][$uniqId] = array(
      '#type' => 'markup',
      '#markup' => '<a href="javascript:void(0);" class="pull-left" data="scorecard-product-attachment-' . $uniqId . '-id" onclick="jQuery(\'.' . $uniqId . ' input[type=file]\').trigger(\'click\'); return false;"><i class="fa fa-2x fa-upload" aria-hidden="true" style="color: #000;"></i></a>' . $file_upload_list,
    );

    $element['remove'][$uniqId] = array(
      '#type'       => 'submit',
      '#value'      => decode_entities('&#xf014;'),
      '#name'       => $uniqId,   
      '#attributes' => array('style'=> array('font-family:FontAwesome;'),'class'=>array('alert-container-section', 'workflow-remove-submit')),
      '#parents'    => array('alert', $uniqId, 'remove'),
      "#limit_validation_errors" => array(),
      '#submit'=> array('remove_product_row_handler'),
      '#ajax' => array(
        'callback' => 'remove_m6_product_row_callback',
        'wrapper' => 'alert-container-section',
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
    );
  }

  $element['workflow_add_new_row'] = array(
    '#type'                    =>'submit',
    '#value'                   => 'Add Another Product',
    '#name'                    => 'workflow_add_new_row',
    '#attributes'              => array('class'=>array('routing-workflow-action','product-workflow-action-add-details'),'title'=>'Add New Detail'),
    '#prefix'                  => '<div style="display:none;">',
    '#suffix'                  => '</div>',
    "#limit_validation_errors" => array(),
    '#submit'                  => array('add_new_row_submit_handler_product'),
    '#ajax'                    => array(
      'callback' => 'add_new_row_product_action_callback',
      'wrapper'  => 'alert-container-section',
      'method'   => 'replace',
      'effect'   => 'fade',
    'progress'                 => array('type'=> 'throbber', 'message'=> NULL),
    ),
  );

  return $element;
}

/**
 * Ajax callback for ['remove'][$uniqId]
 */
function remove_m6_product_row_callback(&$form, &$form_state) {
  return $form['main-container']['full-container']['product-container']['main_container2'];
}

/**
 * Submit handler for ['remove'][$uniqId]
 */
function remove_product_row_handler(&$form,&$form_state) {
  $triggering_element = $form_state['triggering_element'];
  $identifier = $triggering_element['#parents'][1];
  if(isset($form_state['invite_m6_storage'])){
    foreach ($form_state['invite_m6_storage'] as $key => $value) {
      if($form_state['invite_m6_storage'][$key] == $identifier){
        unset($form_state['invite_m6_storage'][$key]);
        unset($form_state['po_storage_default_value'][$identifier]);
      } 
    }             
  }   
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for m6connect_scm_new_product
 */
function _scm_add_product_submit($form, &$form_state) {
  // dpm($form_state, '$form_state');
  // return;

  global $user, $company;
  $formVal = $form_state['values'];

  $products_added = 0;
  $send_review_mail = FALSE;

  if (!empty($form_state['node_nid'])) {
    $manufacturer = $form_state['node_nid'];
    $manufacturer_node = node_load($form_state['node_nid']);
    $is_user_admin = _is_user_company_admin($manufacturer_node);

    if (!$is_user_admin) {
      $send_review_mail = TRUE;
    }
  }

  if (empty($manufacturer)) {
    drupal_set_message(t('Product could not be added. No Manufacturer found.'), 'error', FALSE);
  }
  else {
    if (!empty($form_state['values']['alert'])) {
      // If there are more products, adding these one by one.
      foreach ($form_state['values']['alert'] as $uniqId => $alert_values) {
        if (!empty($alert_values['product-number'])) {
          $node = _node_creation_call('scorecard_products', $alert_values['product-number']);

          // Checking whether the user is admin of the current company or not.
          
          if (!$is_user_admin) {
            // If current user is not the company admin then not publishing
            // the nodes, and saving it for review.
            $node->status = 0;
          }

          $node->field_catalog_number_product[LANGUAGE_NONE][0]['value'] = $alert_values['catelog-number'];
          $node->field_sku_number[LANGUAGE_NONE][0]['value'] = $alert_values['sku-product'];
          $node->field_description[LANGUAGE_NONE][0]['value'] = $alert_values['description-product'];
          $node->field_product_url[LANGUAGE_NONE][0]['value'] = $alert_values['url-product'];
          $node->field_product_name[LANGUAGE_NONE][0]['value'] = $alert_values['product-name'];
          $node->field_manufacture_reference[LANGUAGE_NONE][0]['nid'] = $manufacturer;

          $i = 0;
          foreach ($alert_values['m6-product-category'] as $key => $value) {
            $node->field_m6_product_category['und'][$i] = array('tid' => $value);
            $i++;
          }

          $i = 0;
          foreach ($alert_values['company-category'] as $key => $value) {
            $node->field_category['und'][$i] = array('value' => $value);
            $i++;
          }

          if (!empty($alert_values['field_attachments'])) {
            // Saving any files present.
            $file = file_load($alert_values['field_attachments']);
            $file->status = FILE_STATUS_PERMANENT;
            file_save($file);
            $node_file = (array) $file;
            $node_file['display'] = 1;
            $node->field_attachments[LANGUAGE_NONE] = array($node_file);
          }

          // Saving node finally.
          node_save($node);
          if ($node->nid) {
            $products_added++;
          }
        }
      }
    }
    if (!empty($products_added)) {
      $message = format_plural($products_added, '1 product added successfully.', '@count products added successfully.');
      drupal_set_message($message, 'status', FALSE);
      if ($send_review_mail) {
        drupal_set_message(t('As you are not company admin of the %title, your added product(s) are sent for review to the company admin. Once company admin approves, your product(s) shall be visible in the list.', array('%title' => $manufacturer_node->title)), 'warning', FALSE);
        _mail_products_review_mail($manufacturer_node, $products_added);
      }
    }
    else {
      drupal_set_message(t('No products added. Make sure you have entered product details!'), 'warning', FALSE);
    }
  }

  if (!empty($form_state['ajax'])) {
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    $form_state['ajax_commands'][] = ajax_command_invoke('.trigger-me-on-product-add', 'trigger', array('mousedown'));
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  else {
    if (arg(0) == 'node' && is_numeric(arg(1))) {
      $form_state['redirect'] = 'node/' . arg(1);
    }
    else {
      $form_state['redirect'] = current_path();
    }
  }
}

/**
 * Ajax callback for ['workflow_add_new_row'].
 */
function add_new_row_product_action_callback(&$form, &$form_state) {
  return $form['main-container']['full-container']['product-container']['main_container2'];
}

/**
 * Submit handler for ['workflow_add_new_row']
 */
function add_new_row_submit_handler_product(&$form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];

  if ($triggerElement['#name'] == 'workflow_add_new_row') {
    $tempIdentifer = uniqid();
    $form_state['invite_m6_storage'][]  = $tempIdentifer;
  }

  $form_state['rebuild'] = TRUE;
}

############################ End Add New Product ###############################


############################### Add New Vendor #################################

function m6connect_scm_new_vendor($form,&$form_state) {
  $form['main-container']['full-container']['inner-left-one']['manuf-section-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="row company-section-start-new-vendor"><div class="col-md-4 col-sm-4 col-xs-12"><div class="main-manuf-title"><label>Manufacturer</label></div>'
  );

  $form['main-container']['full-container']['inner-left-one']['manu-choose-company'] = array(
    '#type'       => 'textfield', 
    '#attributes' => array('class'=> array('product-manufactur-section', 'custom-manu-choose-company'),'placeholder'=>'Enter Company'),
    '#prefix'     => '<div class="form-item clearfix">',
    '#suffix'     => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['manu-catalog-number'] = array(
    '#type'          => 'textfield',
    '#attributes'    => array('class' => array('form-control', 'custom-manu-catalog-number'), 'placeholder' => 'Catalog Number'),
    '#default_value' => isset($defaultValues['catalog-number']) ? $defaultValues['catalog-number'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['manu-contact-name'] = array(
    '#type'          => 'textfield',
    '#attributes'    => array('class' => array('form-control', 'custom-manu-contact-name'), 'placeholder' => 'Contact Name'),
    '#default_value' => isset($defaultValues['manu-contact-name']) ? $defaultValues['manu-contact-name'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['manu-contact-email'] = array(
    '#type'          => 'textfield',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('form-control', 'custom-manu-contact-email'), 'placeholder' => 'Contact Email'),
    //'#default_value' => isset($defaultValues['manu-contact-email']) ? $defaultValues['manu-contact-email'] : '',
    '#element_validate' => array('m6connect_scm_email_element_validate'),
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['manu-contact-phone'] = array(
    '#type'          => 'textfield',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('form-control', 'custom-manu-contact-phone', 'international_phone-number'), 'placeholder' => 'Contact Phone'),
    //'#default_value' => isset($defaultValues['manu-contact-phone']) ? $defaultValues['manu-contact-phone'] : '',
    '#attached' => array(
              'css'=> array(
                drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css',
              ),
              'js'=>array(
                drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js',
                drupal_get_path('module', 'international_phone') . '/js/international_phone.js',
                //drupal_get_path('module', 'international_phone') . '/js/utils.js'
              ),
          ), 
    '#element_validate' => array('m6connect_scm_contact_element_validate'),
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['manu-contact-number'] = array(
    '#type'          => 'textfield',
    '#attributes'    => array('class' => array('form-control', 'custom-manu-contact-number'), 'placeholder' => 'Contact Number'),
    '#default_value' => isset($defaultValues['manu-contact-number']) ? $defaultValues['manu-contact-number'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-section-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="main-ven-title"><label>Vendor</label>'
  );

  $form['main-container']['full-container']['inner-left-one']['ven-section-same-as-manufacturer'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Same as Manufacturer'),
    '#attributes'    => array('class' => array('same-as-manufacturer-scorecard-product')),
    '#title_display' => 'after',
    '#prefix'        => '<div class="pull-right">',
    '#suffix'        => '</div></div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-choose-company'] = array(
    '#type'       => 'textfield', 
    '#attributes' => array('class' => array('product-manufactur-section', 'custom-ven-choose-company'),'placeholder' => 'Enter Company'),
    '#prefix'     => '<div class="form-item clearfix">',
    '#suffix'     => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-catalog-number'] = array(
    '#type'          => 'textfield',
    '#attributes'    => array('class' => array('form-control', 'custom-ven-catalog-number'), 'placeholder' => 'Catalog Number'),
    '#default_value' => isset($defaultValues['ven-catalog-number']) ? $defaultValues['ven-catalog-number'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-contact-name'] = array(
    '#type'          => 'textfield',
    '#attributes'    => array('class' => array('form-control', 'custom-ven-contact-name'), 'placeholder' => 'Contact Name'),
    '#default_value' => isset($defaultValues['ven-contact-name']) ? $defaultValues['ven-contact-name'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-contact-email'] = array(
    '#type'          => 'textfield',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('form-control', 'custom-ven-contact-email'), 'placeholder' => 'Contact Email'),
    '#element_validate' => array('m6connect_scm_email_element_validate'),
    //'#default_value' => isset($defaultValues['ven-contact-email']) ? $defaultValues['ven-contact-email'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-contact-phone'] = array(
    '#type'          => 'textfield',
    '#required'      => TRUE,
    '#attributes'    => array('class' => array('form-control', 'custom-ven-contact-phone','international_phone-number'), 'placeholder' => 'Contact Phone'),
    //'#default_value' => isset($defaultValues['ven-contact-phone']) ? $defaultValues['ven-contact-phone'] : '',
    '#attached' => array(
              'css'=> array(
                drupal_get_path('module', 'international_phone') . '/css/intlTelInput.css',
              ),
              'js'=>array(
                drupal_get_path('module', 'international_phone') . '/js/intlTelInput.js',
                drupal_get_path('module', 'international_phone') . '/js/international_phone.js'
              ),
          ), 
    '#element_validate' => array('m6connect_scm_contact_element_validate'),
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div>',
  );

  $form['main-container']['full-container']['inner-left-one']['ven-contact-number'] = array(
    '#type'          => 'textfield',
    '#attributes'    => array('class' => array('form-control', 'custom-ven-contact-number'), 'placeholder' => 'Contact Number'),
    '#default_value' => isset($defaultValues['ven-contact-number']) ? $defaultValues['ven-contact-number'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
  );

  $form['main-container']['full-container']['inner-left-one']['notes-title'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="main-manuf-title"><label>Notes</label></div>'
  );

  $form['main-container']['full-container']['inner-left-one']['both-notes'] = array(
    '#type'          => 'textarea',
    '#attributes'    => array('class' => array('form-control', 'both-notes'), 'placeholder' => 'Type Notes'),
    '#default_value' => isset($defaultValues['both-notes']) ? $defaultValues['both-notes'] : '',
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div></div></div>',
    '#rows'          => 13,
    '#resizable'     => FALSE,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('_scm_add_vendor_submit'),
    '#value' => t('Add Company'),
    '#attributes' => array('class'=> array('custom_scm_add_vendor_submit_call')), 
    '#prefix' => '<div class="clearfix">',
  );

  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div>',
  );

  return $form;
}

function m6connect_scm_email_element_validate($element, &$form_state, $form) {
  $value = $element['#value'];
  
  if (!valid_email_address($element['#value'])) {
     form_error($element, t('Please enter a valid email address.'));
   }
}

function m6connect_scm_contact_element_validate($element, &$form_state, $form){
  $value = $element['#value'];
  
  $valid_number = preg_match( '/^(\+\s*)?(?=([.,\s()-]*\d){8})([\d(][\d.,\s()-]*)([[:alpha:]#][^\d]*\d.*)?$/', $element['#value'], $matches ) && preg_match( '/\d{2}/', $element['#value'] );
  $valid_number2 = get_international_formatPhone($element['#value']);
  if ( !$valid_number || !$valid_number2 ) {
    form_error($element, t('Please enter a valid phone number.'));
  }
 
}

function get_international_formatPhone($phoneNumber) {
  
    $phoneNumber = preg_replace('/[^0-9]/','',$phoneNumber);
    if(strlen($phoneNumber) > 10) {
        $countryCode = substr($phoneNumber, 0, strlen($phoneNumber)-10);
        $areaCode = substr($phoneNumber, -10, 3);
        $nextThree = substr($phoneNumber, -7, 3);
        $lastFour = substr($phoneNumber, -4, 4);

        $phoneNumber = '+'.$countryCode.' ('.$areaCode.') '.$nextThree.'-'.$lastFour;
    }
    else if(strlen($phoneNumber) == 10) {
        $areaCode = substr($phoneNumber, 0, 3);
        $nextThree = substr($phoneNumber, 3, 3);
        $lastFour = substr($phoneNumber, 6, 4);

        $phoneNumber = '('.$areaCode.') '.$nextThree.'-'.$lastFour;
    }
    else if(strlen($phoneNumber) == 7) {
        $nextThree = substr($phoneNumber, 0, 3);
        $lastFour = substr($phoneNumber, 3, 4);

        $phoneNumber = $nextThree.'-'.$lastFour;
    }

    return $phoneNumber;
}

function _scm_add_vendor_submit(&$form, &$form_state) {
  // dpm($form_state);
  // return;
  global $user; 
  if (!empty($form_state['values']['manu-choose-company'])) {
    $company_type = 'manufacturer';
    if (!empty($form_state['values']['ven-section-same-as-manufacturer'])) {
      $company_type = 'both';
    }

    $url = '';
    $url .= "https://www.";
    $url .= str_replace(' ', '', strtolower($form_state['values']['manu-choose-company']));
    $url .= ".com";

    $company_title = $form_state['values']['manu-choose-company'];
    $catalog_number = $form_state['values']['manu-catalog-number'];
    $contact_name = $form_state['values']['manu-contact-name'];
    $contact_email = $form_state['values']['manu-contact-email'];
    $contact_phone = $form_state['values']['manu-contact-phone'];
    $contact_number = $form_state['values']['manu-contact-number'];
    $desc = $form_state['values']['both-notes'];
    

    $node = _node_creation_call('organization', $company_title);
    $node->field_owner_name[LANGUAGE_NONE][0]['value'] = $contact_name;
    $node->field_company_email[LANGUAGE_NONE][0]['email']= $contact_email;
    $node->field_org_phone[LANGUAGE_NONE][0]['value'] = get_international_formatPhone($contact_phone);
    $node->field_catalog_number_product[LANGUAGE_NONE][0]['value'] = $catalog_number;
    $node->field_contract_number‎[LANGUAGE_NONE][0]['value'] = $contact_number;
    $node->field_company_type_vendor[LANGUAGE_NONE][0]['value'] = $company_type;
    $node->field_description[LANGUAGE_NONE][0]['value'] = $desc;
    $node->field_website[LANGUAGE_NONE][0]['value'] = $url;
    node_save($node);
    $manufacturer = $node->nid;
    if ($manufacturer) {
      drupal_set_message(t('Manufacturer created successfully.'), 'status', FALSE);
    }

    if (!empty($form_state['values']['ven-choose-company']) && $company_type == 'manufacturer') {
      $company_title = $form_state['values']['ven-choose-company'];
      $catalog_number = $form_state['values']['ven-catalog-number'];
      $contact_name = $form_state['values']['ven-contact-name'];
      $contact_email = $form_state['values']['ven-contact-email'];
      $contact_phone = $form_state['values']['ven-contact-phone'];
      $contact_number = $form_state['values']['ven-contact-number'];

      $node = _node_creation_call('organization', $company_title);
      $node->field_owner_name[LANGUAGE_NONE][0]['value'] = $contact_name;
      $node->field_company_email[LANGUAGE_NONE][0]['email'] = $contact_email;
      $node->field_org_phone[LANGUAGE_NONE][0]['value'] = get_international_formatPhone($contact_phone);
      $node->field_catalog_number_product[LANGUAGE_NONE][0]['value'] = $catalog_number;
      $node->field_contract_number‎[LANGUAGE_NONE][0]['value'] = $contact_number;
      $node->field_company_type_vendor[LANGUAGE_NONE][0]['value'] = 'vendor';
      $node->field_description[LANGUAGE_NONE][0]['value'] = $desc;
      $node->field_website[LANGUAGE_NONE][0]['value'] = $url;
      node_save($node);
    }
  }

  if (empty($manufacturer)) {
    drupal_set_message(t('Manufacturer could not be created due to some problem, please try again.'), 'warning', FALSE);
  }

  if (!empty($form_state['ajax'])) {
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    $form_state['ajax_commands'][] = ajax_command_invoke('#edit-search-criteria', 'trigger', array('change'));
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
  else {
    $form_state['redirect'] = 'scm/select-products'; 
  }
}

############################# End Add New Vendor ###############################


############################# Scorecard Status Update ##########################

function scorecard_status_update_form($form, &$form_state, $nodeId = 0) {
  $nodeData = node_load($form_state['node_id']);
  $scoreStatus = $form_state['scoreStatus'];
  $statusOperation = $scoreStatus == 'active' ? 'Activate' : 'Deactivate';

  $form['node_action_title'] = array(
    '#type'   => 'markup',
    '#title'  => t('status'),
    '#markup' => '<div class="group-action-status"><h4>Are you sure you want to ' . $statusOperation . ' ( ' . t(ucwords($nodeData->field_scorecard_name['und'][0]['value'])) . '  ) Scorecard?</h4><p>Other Scorecards wil be deactivated automatically !</p></div><br>',
  );

  $form['node_id'] = array(
    '#type'  => 'hidden',
    '#value' => $nodeData->nid,
  );

  $form['score_status'] = array(
    '#type'  => 'hidden',
    '#value' => $statusOperation, 
  );

  $form['submit_action_dgroup'] = array(
    '#type'  => 'submit',
    '#value' => t('Make Active')
  );

  $form['submit_action_cancel']['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('group-delete-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#weight' => 10,
  );

  return $form;
}

/**
 * Submit handler for scorecard_status_update_form
 */
function scorecard_status_update_form_submit($form, &$form_state) {
  return;
  global $company;
  $form_values = $form_state['values'];
  $nodeId = $form_state['node_id'];
  $nodeDetail = node_load($nodeId);
  $status = $form_state['scoreStatus'];

  if($status == 'active') {
    $nodeDetail->field_scorecard_status['und'][0]['value'] = 'Active';
  }
  else {
    $nodeDetail->field_scorecard_status['und'][0]['value'] = '';
  }

  $getAllScoreCard = _fetching_scorecard_information('scm_scorecard');

  foreach ($getAllScoreCard as $delta => $nids) {
    if ($nids == $nodeId) {
      continue;
    }
    $otherCards = node_load($nids);
    $otherCards->field_scorecard_status['und'][0]['value'] = '';
    field_attach_update('node', $otherCards);
    node_save($otherCards);
  }

  field_attach_update('node', $nodeDetail);
  node_save($nodeDetail);

  if (!empty($form_state['ajax'])) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] = ctools_ajax_command_redirect('scm/scorecard');
  }
  else {
    $form_state['redirect'] = 'scm/select-products'; 
  }
}

function sc_change_search_vendor_callback($form, &$form_state) {
  $commands = array();
  if (!empty($form_state['triggering_element']['#value'])) {
    $nid = _get_nid_by_title($form_state['triggering_element']['#value']);
    if (!empty($nid)) {
      $input_array = $form_state['triggering_element']['#array_parents'];
      if (!empty($input_array)) {
        $input_element = end($input_array);
        $input_element .= '_nid';
      }
      $commands[] = ajax_command_invoke('input[name="'. $input_element . '"]', 'val', array($nid));
    }
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

########################## End Scorecard stauts update #########################


########################## Approve/Deny product review #########################

function approve_deny_review_product_form($form, &$form_state, $product = NULL, $action = NULL) {
  if (empty($form_state['product']) && !empty($product)) {
    $form_state['product'] = $product;
  }
  if (!empty($form_state['product']) && empty($product)) {
    $product = $form_state['product'];
  }

  if (empty($form_state['action']) && !empty($action)) {
    $form_state['action'] = $action;
  }
  if (!empty($form_state['action']) && empty($action)) {
    $action = $form_state['action'];
  }

  $form = array();

  $warning_text = '<div class="group-action-status"><h4><p>' . t('Are you sure you want to @action: %title?', array('@action' => ucwords($action), '%title' => $product->title,)) . '</p></h4>';
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

function approve_deny_review_product_form_submit($form, &$form_state) {
  $action = $form_state['action'];
  $product = $form_state['product'];

  $action_taken = $action == 'approve' ? t('Approved') : t('Denied');


  if ($action == 'approve') {
    $product->status = 1;
    node_save($product);
  }
  else {
    node_delete($product->nid);
  }

  drupal_set_message(t('%title @action_taken successfully.', array('%title' => $product->title, '@action_taken' => $action_taken)), 'status', FALSE);

  if (!empty($form_state['ajax'])) {
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    $form_state['ajax_commands'][] = ajax_command_html('#review-products-table', _get_product_review_table());
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

######################## End Approve/Deny product review #######################


############################## Edit product review #############################
function edit_review_product_form($form, &$form_state, $product = NULL) {
  if (empty($form_state['product']) && !empty($product)) {
    $form_state['product'] = $product;
  }
  if (!empty($form_state['product']) && empty($product)) {
    $product = $form_state['product'];
  }

  // Loading defaults.
  $defaults = array(
    'company-category' => '',
    'm6-product-category' => '',
    'product-number' => $product->title,
    'catelog-number' => !empty($product->field_catalog_number_product[LANGUAGE_NONE][0]['value']) ? $product->field_catalog_number_product[LANGUAGE_NONE][0]['value'] : '',
    'sku-product' => !empty($product->field_sku_number[LANGUAGE_NONE][0]['value']) ? $product->field_sku_number[LANGUAGE_NONE][0]['value'] : '',
    'url-product' => !empty($product->field_product_url[LANGUAGE_NONE][0]['value']) ? $product->field_product_url[LANGUAGE_NONE][0]['value'] : '',
    'description-product' => !empty($product->field_description[LANGUAGE_NONE][0]['value']) ? $product->field_description[LANGUAGE_NONE][0]['value'] : '',
    'product-name' => !empty($product->field_product_name[LANGUAGE_NONE][0]['value']) ? $product->field_product_name[LANGUAGE_NONE][0]['value'] : '',
  );
  // Company category.
  if (!empty($product->field_category[LANGUAGE_NONE])) {
    foreach ($product->field_category[LANGUAGE_NONE] as $key => $value) {
      $defaults['company-category'][] = $value['value'];
    }
  }

  // M6 Product category.
  if (!empty($product->field_m6_product_category[LANGUAGE_NONE])) {
    foreach ($product->field_m6_product_category[LANGUAGE_NONE] as $key => $value) {
      $defaults['m6-product-category'][] = $value['tid'];
    }
  }


  // Getting Company and M6 Product categories.
  $company_categories_options = array();

  // Getting manufacturer company.
  $manu_nid = $product->field_manufacture_reference['und'][0]['nid'];

  $company_categories_all = _get_all_categories_by_company($manu_nid);

  if (!empty($company_categories_all)) {
    foreach ($company_categories_all as $key => $value) {
      $company_categories_options[$value->field_category_value] = $value->field_category_value;
    }
  }

  $m6_cat_options = _get_m6_product_categories();

  // Preparing form.
  $form['main-container'] = array(
    '#type' => 'container',
    '#theme' => 'edit_product_form',
  );

  $form['main-container']['company-category'] = array(
    '#type'          => 'select',
    '#options'       => $company_categories_options,
    '#attributes'    => array('class' => array('form-control', 'project-name'), 'placeholder' => 'Choose Company Category'),
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
    '#select2'       => array(
      'width' => '170',
      'minimumResultsForSearch' => '5',
    ),
    '#multiple'      => TRUE,
    '#default_value' => $defaults['company-category'],
  );

  $form['main-container']['m6-product-category'] = array(
    '#type'          => 'select',
    '#options'       => $m6_cat_options,
    '#attributes'    => array('class' => array('form-control', 'project-name'), 'placeholder' => 'M6 Product Category'),
    '#prefix'        => '<div class="form-item clearfix">',
    '#suffix'        => '</div></div>',
    '#select2'       => array(
      'width' => '170',
      'minimumResultsForSearch' => '5',
    ),
    '#multiple'      => TRUE,
    '#required'      => TRUE,
    '#default_value' => $defaults['m6-product-category'],
  );

  $form['main-container']['product-number'] = array(
    '#type'       => 'textfield', 
    '#attributes' => array('class'=> array('form-control','workflow-auto','product-number')),
    '#default_value' => $defaults['product-number'],
  );

  $form['main-container']['catelog-number'] = array(
    '#type'       => 'textfield', 
    '#attributes' => array('class'=> array('form-control','workflow-auto','catelog-number')),
    '#default_value' => $defaults['catelog-number'],
  );

  $form['main-container']['sku-product'] = array(
    '#type'          => 'textfield', 
    '#default_value' => '',
    '#attributes'    => array('class'=> array('form-control','workflow-auto','sku-product')),
    '#default_value' => $defaults['sku-product'],
  );

  $form['main-container']['product-name'] = array(
    '#type'          => 'textfield', 
    '#default_value' => '',
    '#attributes'    => array('class'=> array('form-control','workflow-auto','product-name')),
    '#default_value' => $defaults['product-name'],
  );

  $form['main-container']['url-product'] = array(
    '#type'          => 'textfield', 
    '#default_value' => '',
    '#attributes'    => array('class'=> array('form-control','workflow-auto','url-product'), 'placeholder' => t('Enter Product\'s URL')),
    '#default_value' => $defaults['url-product'],
  );

  $form['main-container']['description-product'] = array(
    '#type'          => 'textarea', 
    '#default_value' => '',
    '#attributes'    => array('class'=> array('form-control','workflow-auto','description-product'), 'style' => 'min-height:auto;'),
    '#rows'          => 3,
    '#resizable'     => FALSE,
    '#default_value' => $defaults['description-product'],
  );

  $file_upload_list = '<div id="edit-alert-' . $uniqId . '-field-attachments-upload-id-filelist"></div>';
  // When adding a new element we get a fid of the previous field if any file
  // was uploaded.
  // Please note: Currently we are only allowing a single file to upload.
  if (!empty($product->field_attachments[LANGUAGE_NONE][0]['fid']) && $prev_file = file_load($product->field_attachments[LANGUAGE_NONE][0]['fid'])) {
    // This means that we need to show the file name to user.
    $filename = $prev_file->filename;
    $filename_str = strlen($filename) > 36 ? substr($filename, 0, 36) : $filename;

    $file_upload_list = '<div id="edit-field-attachments-upload-id-filelist">';
    $file_upload_list .= '<div class="filelist-outer">';
    $file_upload_list .= '<span class="filelist-item" title="' . $filename . '">' . $filename_str . '</span>';
    $file_upload_list .= '<i class="fa fa-times" aria-hidden="true" style="color: #000; cursor:pointer" onclick="jQuery(\'input[name=field_attachments_remove_button]\').trigger(\'mousedown\'); return false;"></i>';
    $file_upload_list .= '<br>';
    $file_upload_list .= '</div></div>';
  }

  $form['main-container']['field_attachments'] = array(
    '#type'            => 'managed_file',
    '#upload_location' => 'public://',
    '#attributes'      => array('class'=> array('scorecard-product-attachment-managed'), 'data' => 'unique-attachment-product'),
    '#theme'           => 'custom_file_managed_theme_scorecard',
  );

  // Providing default value, if a file is available.
  if (!empty($product->field_attachments[LANGUAGE_NONE][0]['fid'])) {
    $form['main-container']['field_attachments']['#default_value'] = $product->field_attachments[LANGUAGE_NONE][0]['fid'];
  }

  $form['main-container']['field_attachments_markup'] = array(
    '#type'   => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="pull-left" data="scorecard-product-attachment-' . $uniqId . '-id" onclick="jQuery(\'.scorecard-product-attachment-managed input[type=file]\').trigger(\'click\'); return false;"><i class="fa fa-2x fa-upload" aria-hidden="true" style="color: #000;"></i></a>' . $file_upload_list,
  );

  $form['actions']['submit'] = array(
    '#type'       => 'submit',
    '#submit'     => array('_scm_edit_product_submit'),
    '#value'      => t('Save'),
    '#attributes' => array('class' => array('custom_scm_add_product_submit_call')),
    '#prefix'     => '<div class="clearfix margin-top-10">',
  );

  $form['actions']['submit_approve'] = array(
    '#type'       => 'submit',
    '#submit'     => array('_scm_edit_approve_product_submit'),
    '#value'      => t('Save and Approve'),
    '#attributes' => array('class' => array('custom_scm_add_product_submit_call')),
  );

  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#suffix' => '</div>',
  );

  return $form;
}

/**
 * Submit handler for edit_review_product_form
 */
function _scm_edit_product_submit($form, &$form_state) {
  global $user, $company;
  $formVal = $form_state['values'];

  if (!empty($form_state['product'])) {
    $product = $form_state['product'];

    $product->title = $formVal['product-number'];
    $product->field_catalog_number_product[LANGUAGE_NONE][0]['value'] = $formVal['catelog-number'];
    $product->field_sku_number[LANGUAGE_NONE][0]['value'] = $formVal['sku-product'];
    $product->field_description[LANGUAGE_NONE][0]['value'] = $formVal['description-product'];
    $product->field_product_url[LANGUAGE_NONE][0]['value'] = $formVal['url-product'];
    $product->field_product_name[LANGUAGE_NONE][0]['value'] = $alert_values['product-name'];

    $i = 0;
    foreach ($formVal['m6-product-category'] as $key => $value) {
      $product->field_m6_product_category['und'][$i] = array('tid' => $value);
      $i++;
    }

    $i = 0;
    foreach ($formVal['company-category'] as $key => $value) {
      $product->field_category['und'][$i] = array('value' => $value);
      $i++;
    }

    if (!empty($formVal['field_attachments'])) {
      // Saving any files present.
      $file = file_load($formVal['field_attachments']);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      $product_file = (array) $file;
      $product_file['display'] = 1;
      $product->field_attachments[LANGUAGE_NONE] = array($product_file);
    }

    // Saving node finally.
    node_save($product);

    drupal_set_message(t('Product %title updated successfully.', array('%title' => $product->title)), 'status', FALSE);
  }
  else {
    drupal_set_message(t('Product could not be updated due to some problem. Please try again later, or contact admin if the problem persists.'), 'error', FALSE);
  }

  if (!empty($form_state['ajax'])) {
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    $form_state['ajax_commands'][] = ajax_command_html('#review-products-table', _get_product_review_table());
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

function _scm_edit_approve_product_submit($form, &$form_state) {
  global $user, $company;
  $formVal = $form_state['values'];

  if (!empty($form_state['product'])) {
    $product = $form_state['product'];

    $product->title = $formVal['product-number'];
    $product->field_catalog_number_product[LANGUAGE_NONE][0]['value'] = $formVal['catelog-number'];
    $product->field_sku_number[LANGUAGE_NONE][0]['value'] = $formVal['sku-product'];
    $product->field_description[LANGUAGE_NONE][0]['value'] = $formVal['description-product'];
    $product->field_product_url[LANGUAGE_NONE][0]['value'] = $formVal['url-product'];
    $product->field_product_name[LANGUAGE_NONE][0]['value'] = $alert_values['product-name'];

    $i = 0;
    foreach ($formVal['m6-product-category'] as $key => $value) {
      $product->field_m6_product_category['und'][$i] = array('tid' => $value);
      $i++;
    }

    $i = 0;
    foreach ($formVal['company-category'] as $key => $value) {
      $product->field_category['und'][$i] = array('value' => $value);
      $i++;
    }

    if (!empty($formVal['field_attachments'])) {
      // Saving any files present.
      $file = file_load($formVal['field_attachments']);
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      $product_file = (array) $file;
      $product_file['display'] = 1;
      $product->field_attachments[LANGUAGE_NONE] = array($product_file);
    }

    // Publishing the node.
    $product->status = 1;

    // Saving node finally.
    node_save($product);

    drupal_set_message(t('Product %title updated and approved successfully.', array('%title' => $product->title)), 'status', FALSE);
  }
  else {
    drupal_set_message(t('Product could not be updated due to some problem. Please try again later, or contact admin if the problem persists.'), 'error', FALSE);
  }

  if (!empty($form_state['ajax'])) {
    $form_state['ajax_commands'][] = ajax_command_remove('#messages-custom');
    $form_state['ajax_commands'][] = ajax_command_prepend('#content', '<div id="messages-custom">' . theme('status_messages') . '</div>');
    $form_state['ajax_commands'][] = ajax_command_html('#review-products-table', _get_product_review_table());
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}


############################# Raters Scorecard Evaluate ########################

/**
 * Function to return form for rater's scorecard evaluate.
 */
function scorecard_rates_evaluate_form($form, &$form_state, $scorecard_node = NULL) {
  // Saving scorecard node in form_state for later uses.
  if (!empty($scorecard_node)) {
    $form_state['scorecard_node'] = $form['#storage']['scorecard_node'] = $scorecard_node;
  }

  // If the author of the scorecard is viewing this form, then we need to show
  // him weight and score too.
  global $user;
  $form_state['is_user_author'] = $form['#storage']['is_user_author'] = $user->uid == $scorecard_node->uid;

  // Getting question builder node.
  $question_builder_node = _get_question_builder_node_by_scorecard($scorecard_node);
  $form_state['question_builder_node'] = $form['#storage']['question_builder_node'] = $question_builder_node;

  // We need to judge that whether rating was requested on company basis or
  // product basis. If company basis is requested, only one set of questions
  // will be shown to rater, else each product of that company will be asked
  // with a question set.
  $criteria = 'company_based';
  if (!empty($question_builder_node->field_selection_criteria[LANGUAGE_NONE][0]['value'])) {
    $criteria = $question_builder_node->field_selection_criteria[LANGUAGE_NONE][0]['value'];
  }
  $form_state['criteria'] = $form['#storage']['criteria'] = $criteria;

  // If criteria is product based, then we need products associated with the
  // current scorecard's company.
  $products = $companies = array();
  if ($criteria == 'product_based') {
    // Getting all products.

    // If products are to be get by this scorecard reference, then use below
    // function else getting all products of the scorecard's company.
    $products = _get_all_products_by_scorecard($scorecard_node->nid);

    // Else use this if want to get all products of scorecard's company.
    // $products = _get_all_products_by_vendor($scorecard_node->og_group_ref[LANGUAGE_NONE][0]['target_id']);
    $form_state['products'] = $form['#storage']['products'] = $products;
  }
  elseif ($criteria == 'company_based') {
    // If a company based criteria is choosed, then we need to get all companies
    // of the products for this scorecard.
    $companies = _get_all_products_companies_by_scorecard($scorecard_node->nid);
    $form_state['companies'] = $form['#storage']['companies'] = $companies;
  }

  // Collecting necessary information for the current scorecard questionbuilder.
  // Like categories and questions.
  $categories = array();
  if (!empty($question_builder_node->field_question_builder_category[LANGUAGE_NONE])) {
    foreach ($question_builder_node->field_question_builder_category[LANGUAGE_NONE] as $key => $value) {
      $categories[$value['value']] = $value['value'];
    }
  }

  // Getting questions by category, questionbuilder, and scorecard.
  $questions = _get_questions_for_questionbuilder_raters($categories, $question_builder_node, $scorecard_node);

  // Trying to get previously rated and answered questions for the current
  // scorecard.
  _get_previous_ratings_comments($questions, $criteria, $products, $companies);

  // Saving questions and categories in form_state and form so that we can 
  // access these in process and theme functions.
  $form_state['categories'] = $form['#storage']['categories'] = $categories;
  $form_state['questions'] = $form['#storage']['questions'] = $questions;

  // Trying to create a form.
  $form['main-container'] = array(
    '#type'    => 'container',
    '#process' => array('process_main_cotainer_raters_evaluate'),
    '#prefix'  => $criteria == 'company_based' ? '<div id="company-based-main-container" class="content-border margin-bottom-20 evaluateouter">' : '<div id="product-based-main-container" class="content-border margin-bottom-20 evaluateouter">',
    '#suffix'  => '</div>',
  );
  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }

  $form['actions'] = array(
    '#type'   => 'actions',
    '#prefix' => '<div class="row custom-submit-scorecard-button scorecard-button-el-sp '.$sharerecommendation.'">',
    '#suffix' => '</div>',
  );

  $form['actions']['save'] = array(
    '#type'   => 'submit',
    '#name'   => 'save_only',
    '#value'  => t('Save'),
    '#submit' => array('_save_raters_evaluate_data'),
  );

  $form['actions']['save_submit'] = array(
    '#type'   => 'submit',
    '#name'   => 'save_submit',
    '#value'  => t('Save and Submit Ratings'),
    '#submit' => array('_save_raters_evaluate_data'),
  );

  $form['actions']['cancel'] = array(
    '#type'   => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button">',
  );

  return $form;
}

/**
 * Process function.
 * Product and Company based.
 */
function process_main_cotainer_raters_evaluate($elements, &$form_state) {
  // For product based, we shall be showing the same question set for all of
  // the products.
  // For this we shall be using fieldsets, for each product.

  // If user is author of the scorecard.
  $is_user_author = $form_state['is_user_author'];

  $datas = $form_state['criteria'] == 'product_based' ? $form_state['products'] : $form_state['companies'];

  $p = 0;
  foreach ($datas as $data) {
    $p++;
    // Getting node title by its id.
    $node_title = _get_title_of_node($data);

    // Node Fieldset.
    $prod_fieldset = 'node-' . $data;

    // Saving essential data for theme function.
    $elements[$prod_fieldset] = array(
      '#type' => 'fieldset',
      '#title' => $node_title,
      '#collapsed' => $p == 1 ? FALSE : TRUE,
      '#collapsible' => TRUE,
      '#attributes' => $p == 1 ? array('class' => array('collapsible', 'fieldsetbigtitle')) : array('class' => array('collapsible', 'collapsed', 'fieldsetbigtitle')),
      '#attached' => array(
        'library' => array(
          array('system', 'drupal.collapse'),
        ),
      ),
      '#prefix' => '<div class="clearfix margin-top-10 margin-bottom-15">',
      '#suffix' => '</div>',
    );

    // Showing questions now.
    foreach ($form_state['questions'] as $category => $qset) {
      $category_title = _get_question_category_title_by_id($category);

      // Category Container.
      $cat_container = 'category-container-' . $category;
      $elements[$prod_fieldset][$cat_container] = array(
        '#type'  => 'container',
        '#theme' => 'raters_evaluate_container_theme',
      );

      $elements[$prod_fieldset][$cat_container]['#storage'] = array(
        'scorecard_node'        => $form_state['scorecard_node'],
        'is_user_author'        => $form_state['is_user_author'],
        'question_builder_node' => $form_state['question_builder_node'],
        'criteria'              => $form_state['criteria'],
        'products'              => $form_state['products'],
        'categories'            => $form_state['categories'],
        'questions'             => $form_state['questions'],
        'companies'             => $form_state['companies'],
      );

      // Title of the category.
      $elements[$prod_fieldset][$cat_container]['cat_title_' . $category] = array(
        '#type'   => 'markup',
        '#markup' => $category_title,
      );

      // Now each category has questions, generating them.
      if (empty($qset)) {
        // If by any means, we do not have questions.
        $elements[$prod_fieldset][$cat_container]['no_questions'] = array(
          '#type'   => 'markup',
          '#markup' => t('There are no questions in this category.'),
        );
      }
      else {
        $i = 0;
        foreach ($qset as $qdata) {
          $i++;
          $elements[$prod_fieldset][$cat_container][$qdata->id]['question_id'] = array(
            '#type'    => 'value',
            '#value'   => $qdata->id,
            '#parents' => array('qdata', $data, $category, $qdata->id, 'question_id'),
          );

          $elements[$prod_fieldset][$cat_container][$qdata->id]['sr_no'] = array(
            '#type'   => 'markup',
            '#markup' => $i . '.',
          );

          $elements[$prod_fieldset][$cat_container][$qdata->id]['question'] = array(
            '#type'   => 'markup',
            '#markup' => $qdata->question,
          );

          $elements[$prod_fieldset][$cat_container][$qdata->id]['ratings'] = array(
            '#type'          => 'textfield',
            '#title'         => t('Ratings'),
            '#title_display' => 'invisible',
            '#attributes'    => array('readonly' => 'readonly', 'class' => array('qbuilder-rating', 'clearnumber')),
            '#field_prefix'  => '<i class="fa fa-minus item-decrease item-decrease-item" aria-hidden="true"></i>',
            '#field_suffix'  => '<i class="fa fa-plus item-increase item-increase-item item-increase-rating" aria-hidden="true"></i>',
            '#maxlength'     => 2,
            '#default_value' => 0,
            '#parents'       => array('qdata', $data, $category, $qdata->id, 'ratings'),
          );

          if ($is_user_author) {
            $elements[$prod_fieldset][$cat_container][$qdata->id]['weight'] = array(
              '#type'          => 'textfield',
              '#title'         => t('Weight'),
              '#title_display' => 'invisible',
              '#attributes'    => array('readonly' => 'readonly', 'class' => array('qbuilder-weight', 'clearnumber')),
              '#field_prefix'  => '<i class="fa fa-minus item-decrease item-decrease-item" aria-hidden="true"></i>',
              '#field_suffix'  => '<i class="fa fa-plus item-increase item-increase-item item-increase-rating" aria-hidden="true"></i>',
              '#maxlength'     => 2,
              '#default_value' => $qdata->weight,
              '#parents'       => array('qdata', $data, $category, $qdata->id, 'weight'),
              '#prefix' => '<div class="pointer-events-none" style="cursor: not-allowed;">',
              '#suffix' => '</div>',
            );

            $elements[$prod_fieldset][$cat_container][$qdata->id]['score'] = array(
              '#type'          => 'textfield',
              '#title'         => t('Weight'),
              '#title_display' => 'invisible',
              '#attributes'    => array('readonly' => 'readonly', 'class' => array('qbuilder-score', 'clearnumber')),
              '#maxlength'     => 2,
              '#parents'       => array('qdata', $data, $category, $qdata->id, 'score'),
              '#prefix' => '<div class="pointer-events-none" style="cursor: not-allowed;">',
              '#suffix' => '</div>',
            );
          }

          $elements[$prod_fieldset][$cat_container][$qdata->id]['comments'] = array(
            '#type'          => 'textfield',
            '#title'         => t('comments'),
            '#title_display' => 'invisible',
            //'#attributes'    => array('readonly' => 'readonly', 'class' => array('qbuilder-score', 'clearnumber')),
            '#parents'       => array('qdata', $data, $category, $qdata->id, 'comments'),
            '#maxlength'     => 4096,
          );

          if (!empty($qdata->{'defaults'}[$data])) {
            // It means we have some default values.
            if (!empty($qdata->{'defaults'}[$data]['ratings'])) {
              $elements[$prod_fieldset][$cat_container][$qdata->id]['ratings']['#default_value'] = $qdata->{'defaults'}[$data]['ratings'];
            }
            if (!empty($qdata->{'defaults'}[$data]['comments'])) {
              $elements[$prod_fieldset][$cat_container][$qdata->id]['comments']['#default_value'] = $qdata->{'defaults'}[$data]['comments'];
            }
          }
        }
      }
    }
  }

  return $elements;
}

/**
 * Submit handler.
 */
function _save_raters_evaluate_data($form, &$form_state) {
  global $user, $company;

  // Judging whether to just save or save and submit the data.
  $status = $form_state['triggering_element']['#name'] == 'save_only' ? 0 : 1;

  // Judging criteria.
  $criteria = $form_state['criteria'];

  // Preparing data to save.
  $data_ratings = array();
  $data_comments = array();

  // Delete arrays.
  $delete_qids = array();
  $delete_pids = array();

  $element = $criteria == 'product_based' ? 'pid' : 'company_nid';

  $fields_ratings = array('uid', 'qid', 'cid', $element, 'ratings', 'status', 'created');
  $fields_comments = array('uid', 'qid', 'cid', $element, 'comments', 'status', 'created');

  if (!empty($form_state['values']['qdata'])) {
    // Delete product ids.
    $delete_ele_ids[] = array_keys($form_state['values']['qdata']);

    foreach ($form_state['values']['qdata'] as $data => $category) {
      foreach ($category as $cat => $questions) {
        foreach ($questions as $question) {
          $datas = array(
            'uid'     => $user->uid,
            'qid'     => $question['question_id'],
            'cid'     => $cat,
            $element  => $data,
            'status'  => $status,
            'created' => REQUEST_TIME,
          );

          // We need to delete the datas before we save new.
          // We shall be deleting all the entries and saving new ones.
          $delete_qids[] = $question['question_id'];

          if (!empty($question['ratings'])) {
            $datas_ratings = $datas + array('ratings' => $question['ratings']);
            $data_ratings[] = $datas_ratings;
          }

          if (!empty($question['comments'])) {
            $datas_comments = $datas + array('comments' => $question['comments']);
            $data_comments[] = $datas_comments;
          }
        }
      }
    }
  }

  // Saving data.
  if (empty($data_ratings) && empty($data_comments)) {
    $messages = array('message' => t('No ratings provided.'), 'type' => 'warning');
  }
  else {
    $messages = array('message' => t('Ratings @status successfully.', array('@status' => $status == 0 ? 'saved' : 'saved and submitted')), 'type' => 'status',);

    // First deleting data from table, and then saving new ones.
    foreach (array('m6connect_qbuilder_rating', 'm6connect_qbuilder_comments') as $table) {
      $query = db_delete($table);
      $query->condition('qid', $delete_qids);
      $query->condition('uid', $user->uid);
      $query->condition($element, $delete_ele_ids);
      $query->execute();
    }

    foreach (array('m6connect_qbuilder_rating', 'm6connect_qbuilder_comments') as $table) {
      $fields = $table == 'm6connect_qbuilder_rating' ? $fields_ratings : $fields_comments;
      $data = $table == 'm6connect_qbuilder_rating' ? $data_ratings : $data_comments;

      if (!empty($fields)) {
        $query = db_insert($table);
        $query->fields($fields);
        foreach ($data as $record) {
          $query->values($record);
        }
        $query->execute();
      }
    }
  }

  // Showing status to users.
  drupal_set_message($messages['message'], $messages['type'], FALSE);

  // Sending mail and notification to scorecard owner, if user is submitting
  // the ratings.
  if ($status) {
    $scorecard_node = $form_state['scorecard_node'];
    // Sending the notification.
    if (db_table_exists('m6connect_notification')) {
      $m6connect_notification = array(
        'type'         => 'scm',
        'event'        => 'ratings_submitted',
        'entity_id'    => $scorecard_node->nid,
        'company_nid'  => $company->nid,
        'message'      => NULL,
        'request_from' => $user->uid,
        'request_to'   => $scorecard_node->uid,
        'status'       => 1,
        'timestamp'    => REQUEST_TIME,
      );
      entity_save('m6connect_notification', (object) $m6connect_notification);
    }

    // Sending the mail.
    _send_ratings_submitted_mail($scorecard_node);
  }
}

/**
 * Helper function to send ratings submitted mail.
 */
function _send_ratings_submitted_mail($scorecard_node = NULL) {
  if (!empty($scorecard_node->nid)) {
    global $user, $base_url;
    $user_name = _get_user_full_name($user->uid);

    $to_user = user_load($scorecard_node->uid);

    $scorecard_name = $scorecard_node->field_scorecard_name[LANGUAGE_NONE][0]['value'];

    // Preparing message links.
    $link = url('scorecard/evaluate/' . $scorecard_node->nid, array('absolute' => TRUE));
    $click_link = t('<a href="@link">Click here</a>', array('@link' => $link));
    $mailto = t('<a href="@mail_url">@mail</a>', array('@mail_url' => 'mailto:' . variable_get('site_mail', 'support@m6connect.com'), '@mail' => variable_get('site_mail', 'support@m6connect.com')));

    // Preparing message body.
    $message = 'Hello,<br/>';
    $message .= t('%user has submitted ratings for Scorecard @no. To evaluate and make decision, please click the link below.', array('%user' => $user_name, '@no' => $scorecard_name));
    $message .= '<br/><br/>';
    $message .= $click_link;
    $message .= '<br/><br/>';

    $message .= 'Team,<br/><strong>' . variable_get('site_name', 'M6Connet') . '</strong><br/>(' . $mailto . ')';

    // M6Support Mail.
    $sender_mail = variable_get('site_mail', 'support@m6connect.com');

    $params = array(
      'subject'  => t('!name shared an update to scorecard @score_name', array('!name' => $user_name, '@score_name' => $scorecard_name)),
      'body'     => $message,
      'sender'   => $sender_mail,
      'language' => language_default(),
      'module'   => 'm6connect_misc',
      'key'      => 'commitment_mail___invite_2_m6_notify',
      'build'    => TRUE,
    );

    // Sending mail.
    $mail_sent = drupal_mail($params['module'], $params['key'], $to_user->mail, $params['language'], $params);
  }
}

########################### End Raters Scorecard Evaluate ######################


############################## View Scorecard of Form ##########################

/**
 * Function to generate form for view scorecard information.
 */
function view_scorecard_of_form($form, &$form_state, $scorecard_node) {
  $form_state['scorecard_node'] = $scorecard_node;
  $form['audience'] = array(
    '#type'          => 'select',
    '#title'         => t('Select Audience'),
    '#title_display' => 'invisible',
    '#options'       => array('self' => t('My Ratings'), 'group' => t('Group Ratings'),),
    '#ajax'          => array(
      'callback' => 'change_audience_callback',
      'wrapper'  => 'form-change-here',
    ),
  );

  return $form;
}

/**
 * Ajax callback.
 */
function change_audience_callback($form, &$form_state) {
  $trigger = $form_state['triggering_element']['#value'];
  $commands = array();

  if ($trigger == 'self') {
    $scorecard_form = drupal_get_form('scorecard_rates_evaluate_form', $form_state['scorecard_node']);
    $content = drupal_render($scorecard_form);
    $commands[] = ajax_command_html('#form-change-here', $content);
  }
  else {
    $content = '<div class="content-border-sp evaluateouter-sp">'._get_group_ratings_content_evaluate($form_state['scorecard_node']).'</div>';
    $commands[] = ajax_command_html('#form-change-here', $content);

    // Doing after render calculations by JS.
    $commands[] = array('command' => 'groupPostRenderCalculations');
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}

############################ End View Scorecard of Form ########################


############################ Cancel creating scorecard #########################

function cancel_scorecard_new_form($form, &$form_state, $scorecard_node = NULL) {
  if (!empty($form_state['scorecard_node']) && empty($scorecard_node)) {
    $scorecard_node = $form_state['scorecard_node'];
  }

  if (empty($form_state['scorecard_node']) && !empty($scorecard_node)) {
    $form_state['scorecard_node'] = $scorecard_node;
  }

  $delete = '<div class="group-action-status"><h5><p>' . t('Are you sure you want to cancel creating scorecard?') . '</p></h5>';
  $delete .= '<p>' . t('All your work for this scorecard will be lost, and this scorecard will also be deleted.') . '</p></div>';

  $form['warning'] = array(
    '#type' => 'markup',
    '#markup' => $delete,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
  );
  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="ob-msg-popup-close-link" onclick="jQuery(&quot;span.popups-close&quot;).click(); return false;"><input type="button" class="btn cancel-button" value="Cancel"></a>',
  );

  return $form;
}

/**
 * Submit handler
 */
function cancel_scorecard_new_form_submit($form, &$form_state) {
  $scorecard_node = $form_state['scorecard_node'];

  node_delete($scorecard_node->nid);
  drupal_set_message(t('Scorecard deleted successfully.'), 'warning', FALSE);

  $form_state['ajax_commands'][] = ctools_ajax_command_redirect('scorecard/new');
}
########################## End Cancel creating scorecard########################



################################################################################
###############################  Theme Functions ###############################
################################################################################

function theme_invite_m6_theme_scorecard($variables) {
  $element = $variables['form'];
  $storage = $element['#storage'];
  $output = '';

  $header = array('Company Category', 'M6 Product Category<span class="form-required padding-5">*</span>', 'Product Number', 'Catalog Number', 'SKU Number');
  $rowNo = 1;

  foreach ($storage as $key => $uniqId) {
    $temp_out = '<div><div class="clearfix margin-bottom-10">' . drupal_render($element['url-product'][$uniqId]) . '</div><div class="clearfix"><div class="pull-left">' . drupal_render($element['field_attachments_markup'][$uniqId]) . '</div><div class="pull-right">' . drupal_render($element['remove'][$uniqId]) . '</div></div></div>';

    $rows[] = array(
      'data'=> array(
        array('data' => drupal_render($element['company-category'][$uniqId])),
        array('data' => drupal_render($element['m6-product-category'][$uniqId])),
        array('data' => drupal_render($element['product-number'][$uniqId])),
        array('data' => drupal_render($element['catelog-number'][$uniqId])),
        array('data' => drupal_render($element['sku-product'][$uniqId])),
      ),
    );

    $rows[] = array(
      'data' => array(
        array('data' => '<label>' . t('Product Name') . '</label>' . drupal_render($element['product-name'][$uniqId]), 'colspan' => 5),
      ),
    );

    $rows[] = array(
      'data' => array(
        // array('data' => '<div class="col-md-2 padding-left-0"><label class="pull-right">' . t('Description') . '</label></div><div class="col-md-10 padding-0">' . drupal_render($element['description-product'][$uniqId]) . '</div>', 'colspan' => 3),
        array('data' => '<label>' . t('Description') . '</label>' . drupal_render($element['description-product'][$uniqId]), 'colspan' => 3),
        array('data' => '<label>' . t('Product URL') . '</label><span class="hidden">' . drupal_render($element['field_attachments'][$uniqId]). '</span>' . $temp_out, 'colspan' => 2),
      ),
    );
  }
  $rows[] = array(
    'data' => array(
      array('data' => drupal_render($element['workflow_add_new_row']), 'class' => 'hidden'),
    ),
  );

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes'=> array('class'=> array('scm-product-item-table','table','table-hover','m6connect-custom-table','m6connect-table-border', 'scorecard-add-product-table'))));
  $output .= drupal_render_children($element);
  $output .= '<br/>';

  return $output;
}

function theme_edit_product_form($variables) {
  $element = $variables['form'];

  $header = array('Company Category<span class="form-required padding-5">*</span>', 'M6 Product Category<span class="form-required padding-5">*</span>', 'Product Number', 'Catalog Number', 'SKU Number');

  $rows = array();

  $temp_out = '<div><div class="clearfix margin-bottom-10">' . drupal_render($element['url-product']) . '</div><div class="clearfix"><div class="pull-left">' . drupal_render($element['field_attachments_markup']) . '</div><div class="pull-right">' . drupal_render($element['remove']) . '</div></div></div>';

  $rows[] = array(
    'data'=> array(
      array('data' => drupal_render($element['company-category'])),
      array('data' => drupal_render($element['m6-product-category'])),
      array('data' => drupal_render($element['product-number'])),
      array('data' => drupal_render($element['catelog-number'])),
      array('data' => drupal_render($element['sku-product'])),
    ),
  );

  $rows[] = array(
    'data' => array(
      array('data' => '<label>' . t('Product Name') . '</label>' . drupal_render($element['product-name']), 'colspan' => 5),
    ),
  );

  $rows[] = array(
    'data' => array(
      // array('data' => '<div class="col-md-2 padding-left-0"><label class="pull-right">' . t('Description') . '</label></div><div class="col-md-10 padding-0">' . drupal_render($element['description-product']) . '</div>', 'colspan' => 3),
      array('data' => '<label>' . t('Description') . '</label>' . drupal_render($element['description-product']), 'colspan' => 3),
      array('data' => '<label>' . t('Product URL') . '</label><span class="hidden">' . drupal_render($element['field_attachments']). '</span>' . $temp_out, 'colspan' => 2),
    ),
  );

  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes'=> array('class'=> array('scm-product-item-table','table','table-hover','m6connect-custom-table','m6connect-table-border', 'scorecard-add-product-table'))));
  $output .= drupal_render_children($element);
  $output .= '<br/>';

  return $output;
}

/**
 * Theme function for rater's page.
 */
function theme_raters_evaluate_container_theme($variables) {
  $elements = $variables['form'];
  global $base_url;
  $is_user_author = $elements['#storage']['is_user_author'];

  // Preparing image.
  $path_to_theme = drupal_get_path('theme', 'm6connect');
  $img_src = $base_url . '/' . $path_to_theme . '/images/scorecard_company_icon_small.png';

  // Preparing table headers.
  if ($is_user_author) {
    $header = array(
      array('data' => t('Question'), 'class' => array('col-md-4')),
      array('data' => t('Weight'), 'class' => array('col-md-1')),
      array('data' => t('Ratings'), 'class' => array('col-md-1')),
      array('data' => t('Score'), 'class' => array('col-md-1')),
      array('data' => t('Comments'), 'class' => array('col-md-5')),
    );  }
  else {
    $header = array(
      array('data' => t('Question'), 'class' => array('col-md-4')),
      array('data' => t('Ratings'), 'class' => array('col-md-1')),
      array('data' => t('Comments'), 'class' => array('col-md-6')),
    );
  }
  $rows = array();
  $output = '';
  $show_table = TRUE;

  foreach ($elements as $key => $value) {
    if (strrpos($key, '#') === 0) {
      continue;
    }

    if (strpos($key, 'no_questions') === 0) {
      $show_table = FALSE;
      $output .= '<div class="clearfix text-center text-muted">
                    <h4>' . drupal_render($value) . '</h4>
                  </div>';
      break; // If there are no questions, then exit the loop.
    }
    else {
      if (strpos($key, 'cat_title') === 0) {
        $output .= '<div class="clearfix purple-image">
                    <div class="display-inline-block select-product-display-image padding-right-10">
                      <img src="' . $img_src . '">
                    </div>
                    <h4 class="display-inline-block">' . drupal_render($value) . '</h4>
                  </div>';
      }
      else {
        $commanetClass = (empty($value['comments']['#value'])?'trow-inline-link-new':'trow-inline-link-new-2');
        if ($is_user_author) {
          $rows[] = array(
            array('data' => drupal_render($value['question_id']), 'class' => array('hidden')),
            array('data' => drupal_render($value['sr_no']) . ' ' . drupal_render($value['question'])),
            array('data' => drupal_render($value['weight']), 'class' => array('trow-inline'), 'style' => 'cursor:not-allowed;'),
            array('data' => drupal_render($value['ratings']), 'class' => array('trow-inline')),
            array('data' => drupal_render($value['score']), 'class' => array('trow-inline', 'trow-inline-score'), 'style' => 'cursor:not-allowed;'),
            array('data' => drupal_render($value['comments']), 'class' => array($commanetClass)),
          );
        }
        else {
          $rows[] = array(
            array('data' => drupal_render($value['question_id']), 'class' => array('hidden')),
            array('data' => drupal_render($value['sr_no']) . ' ' . drupal_render($value['question'])),
            array('data' => drupal_render($value['ratings']), 'class' => array('trow-inline')),
            array('data' => drupal_render($value['comments']), 'class' => array($commanetClass)),
          );
        }
      }
    }
  }

  if ($show_table) {
    $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('table', 'table-hover', 'qbuilder-table'))));
  }

  // $output .= drupal_render_children($elements);

  return $output;
}


################################################################################
#############################  End Theme Functions #############################
################################################################################

################################################################################
###############################  Helper Functions ##############################
################################################################################

/**
 * Return products on basis of vendors.
 */
function vendor_base_product_callback($vendorArr = array()) {
  global $company, $base_url;
  $path_to_theme = path_to_theme();

  // Getting current active scorecard.
  $get_active_score_card = _fetching_scorecard_information_active('scm_scorecard');
  $all_products_scorecard = _get_all_products_by_scorecard($get_active_score_card);

  // Differentiating between companies and products.
  $companies = $products = $categories_all = array();
  foreach ($vendorArr as $key => $value) {
    if (strpos($value, 'cat__') === 0) {
      // If we have category, then dealing it the other way.
      $categories_all[] = str_replace('cat__', '', $value);
    }
    else {
      // Else it is either company, or product.
      $node_type = _get_type_of_node($value);
      if ($node_type == 'organization') {
        $companies[] = $value;
      }
      elseif ($node_type == 'scorecard_products') {
        $products[] = $value;
      }
    }
  }

  $content = '';
  $content .= '<div class="clearfix">';

  if (!empty($companies)) {
    foreach ($companies as $venKey => $vendorNid) {
      $vendor_title = _get_title_of_node($vendorNid);

      $vendor_node = node_load($vendorNid);

      $vendor_title_id = strtolower(str_replace(' ', '-', $vendor_title));
      $replace_to = array('-', ' ', '.', '_');
      $vendor_short_name = strtoupper(substr(str_replace($replace_to, '', $vendor_title), 0, 2));
      $content .= '<div class="panel panel-default" id="panel-content-' . $vendor_title_id .'">';

      $search_box = '<div class="input-group btn-format-bg"><input type="text" class="form-control" onkeyup="filter_vendors(this, \'panel-content-' . $vendor_title_id .'\');" placeholder="Search ' . $vendor_title . ' Products" /><span class="input-group-btn">
        <button class="btn btn-default" type="button"><i class="fa fa-search" aria-hidden="true"></i></button></span></div>';

      $company_image_path = $base_url . '/' . $path_to_theme . '/images/scorecard_company_icon_small.png';

      $company_image = '<div class="clearfix purple-image"><div class="display-inline-block select-product-display-image padding-right-10"><img src="' . $company_image_path . '" /></div>';

      $add_new_product_link = '';

      // $categories = _get_all_categories_by_company($vendor_node->nid);
      // if (!empty($categories)) {
      //   $add_new_product_link = '<a href="/add-scm-product/' . $get_active_score_card . '/' . $vendorNid . '/nojs" class="ctools-use-modal ctools-modal-assign-asset-category-popup-style add-new-product"> + Add New Product</a>';
      // }
      // else {
      //   $add_new_product_link = '<a href="javascript:void(0)" class="add-new-product add-new-product-disabled"> + Add New Product</a>';
      // }

      $add_new_product_link = '<a href="/add-scm-product/' . $get_active_score_card . '/' . $vendorNid . '/nojs" class="ctools-use-modal ctools-modal-assign-asset-category-popup-style add-new-product"> + Add New Product</a>';

      $content .= '<div class="panel-body"><div class="row"><div class="col-md-6 col-sm-6 col-xs-12 margin-bottom-10">' . $company_image . '<h4 class="display-inline-block">' . $vendor_title . '</h4></div></div><div class="col-md-3 col-sm-3 col-xs-12 margin-bottom-10 text-right">' . $add_new_product_link . '</div><div class="col-md-3 col-sm-3 col-xs-12 margin-bottom-10">' . $search_box . '</div></div>';

      $content .= '<div class="row">';

      // Trying to get all products associated with this vendor/company.

      $all_products = _get_all_products_by_vendor($vendorNid);

      if (!empty($all_products)) {
        foreach ($all_products as $key => $nid) {
          $node = node_load($nid);
          $description = $sku = 'N.A.';
          $description_title = '';

          $title = $node->title;
          $title_trim = $title;
          if (strlen($title) > 20) {
            $title_trim = substr($title, 0, 18) . '...';
          }

          if (!empty($node->field_description['und'][0]['value'])) {
            $description = substr($node->field_description['und'][0]['value'], 0, 18) . '...';
            if (strlen($node->field_description['und'][0]['value']) > 18) {
              $description_title = $node->field_description['und'][0]['value'];
            }
            else {
              $description = $node->field_description['und'][0]['value'];
            }
          }
          if (!empty($node->field_sku_number['und'][0]['value'])) {
            $sku = $node->field_sku_number['und'][0]['value'];
          }

          $green_check = '';
          if (!empty($all_products_scorecard) && in_array($nid, $all_products_scorecard)) {
            $green_check = '<i class="fa fa-2x fa-check-circle pull-right text-success" aria-hidden="true"></i>';
          }

          $content .= '<div class="col-md-3 col-sm-3 col-xs-12 remove-hide-this-product margin-bottom-15">
                        <div id="' . $node->nid . '-' . $get_active_score_card . '" class="select-product-for-sc ' . $node->nid . '-' . $get_active_score_card . '" style="cursor:pointer;" data="add">
                        <div class="clearfix relative">
                          <div class="row margin-0 sku-items">
                            <div class="col-md-4 sku-item-left">
                              <div class="panel-body sku-item-left-icon"> ' . $vendor_short_name . ' </div>
                            </div>
                            <div class="col-md-8 padding-0 sku-item-right">
                              <div class="panel-body">
                                ' . $green_check . '
                                <div class="vendor-title-search" title="' . $title . '">' . $title_trim . '</div>
                                <div title="' . $description_title . '">' . $description . '</div>
                                <div>' . $sku . '</div>
                              </div>
                            </div>
                          </div>
                        </div>
                        </div>
                      </div>';
        }
      }
      else {
        $content .= '<h3 class="text-center text-muted">No Products Yet!</h3>';
      }

      $content .= '</div></div></div>';
    }
  }

  if (!empty($categories_all)) {
    foreach ($categories_all as $key => $category) {
      // If we have a string category, then it is Company product category else it
      // is M6Product Category.
      $type = is_numeric($category) ? 'M6' : 'company';

      $vendor_title = _get_title_of_category($category, $type);

      $vendor_title_id = strtolower(str_replace(' ', '-', $vendor_title));
      $replace_to = array('-', ' ', '.', '_');
      $vendor_short_name = strtoupper(substr(str_replace($replace_to, '', $vendor_title), 0, 2));
      $content .= '<div class="panel panel-default" id="panel-content-' . $vendor_title_id .'">';

      $search_box = '<div class="input-group btn-format-bg"><input type="text" class="form-control" onkeyup="filter_vendors(this, \'panel-content-' . $vendor_title_id .'\');" placeholder="Search ' . $vendor_title . ' Products" /><span class="input-group-btn">
        <button class="btn btn-default" type="button"><i class="fa fa-search" aria-hidden="true"></i></button></span></div>';


      $company_image_path = $base_url . '/' . $path_to_theme . '/images/scorecard_company_icon_small.png';

      $company_image = '<div class="clearfix blue-image"><div class="display-inline-block select-product-display-image padding-right-10"><img src="' . $company_image_path . '" /></div>';

      $content .= '<div class="panel-body"><div class="row"><div class="col-md-9 col-sm-9 col-xs-12 margin-bottom-10">' . $company_image . '<h4 class="display-inline-block">' . $vendor_title . '</h4></div></div><div class="col-md-3 col-sm-3 col-xs-12 margin-bottom-10">' . $search_box . '</div></div>';

      $content .= '<div class="row">';

      $all_products = _get_products_by_category_type($category, $type);

      if (!empty($all_products)) {
        foreach ($all_products as $key => $nid) {
          $node = node_load($nid);

          // Getting title of company.
          $vendor_nid = $node->field_manufacture_reference['und'][0]['nid'];
          $vendor_title = _get_title_of_node($vendor_nid);

          $replace_to = array('-', ' ', '.', '_');
          $vendor_short_name = strtoupper(substr(str_replace($replace_to, '', $vendor_title), 0, 2));

          $vendor_title_trim = $vendor_title;
          if (strlen($vendor_title) > 18) {
            $vendor_title_trim = substr($vendor_title, 0, 18) . '...';
          }

          $description = $sku = 'N.A.';
          $description_title = '';

          $title = $node->title;
          $title_trim = $title;
          if (strlen($title) > 18) {
            $title_trim = substr($title, 0, 18) . '...';
          }

          if (!empty($node->field_description['und'][0]['value'])) {
            $description = substr($node->field_description['und'][0]['value'], 0, 18) . '...';
            if (strlen($node->field_description['und'][0]['value']) > 18) {
              $description_title = $node->field_description['und'][0]['value'];
            }
            else {
              $description = $node->field_description['und'][0]['value'];
            }
          }
          if (!empty($node->field_sku_number['und'][0]['value'])) {
            $sku = $node->field_sku_number['und'][0]['value'];
          }

          $green_check = '';
          if (!empty($all_products_scorecard) && in_array($nid, $all_products_scorecard)) {
            $green_check = '<i class="fa fa-2x fa-check-circle pull-right text-success" aria-hidden="true"></i>';
          }

          $content .= '<div class="col-md-3 col-sm-3 col-xs-12 remove-hide-this-product margin-bottom-15">
                        <div id="' . $node->nid . '-' . $get_active_score_card . '" class="select-product-for-sc ' . $node->nid . '-' . $get_active_score_card . '" style="cursor:pointer;" data="add">
                        <div class="clearfix relative">
                          <div class="row margin-0 sku-items">
                            <div class="col-md-4 sku-item-left">
                              <div class="panel-body sku-item-left-icon"> ' . $vendor_short_name . ' </div>
                            </div>
                            <div class="col-md-8 padding-0 sku-item-right">
                              <div class="panel-body">
                                ' . $green_check . '
                                <div class="vendor-title-search" title="' . $title . '">' . $title_trim . '</div>
                                <div title="' . $vendor_title. '">' . $vendor_title_trim . '</div>
                                <div title="' . $description_title . '">' . $description . '</div>
                                <div>' . $sku . '</div>
                              </div>
                            </div>
                          </div>
                        </div>
                        </div>
                      </div>';
        }
      }
      else {
        $content .= '<h3 class="text-center text-muted">No Products Yet!</h3>';
      }

      $content .= '</div></div></div>';
    }
    $cat_content = $content;
  }

  if (!empty($products)) {
    $titles = '';
    $titles_arr = array();
    foreach ($products as $key => $value) {
      $titles_arr[] = _get_title_of_node($value);
    }
    $titles = implode(', ', $titles_arr);
    $titles_trim = $titles;
    if (strlen($titles) > 90) {
      $titles_trim = substr($titles, 0, 90) . '...';
    }

    $vendor_title_id = 'products';

    $content .= '<div class="panel panel-default" id="panel-content-' . $vendor_title_id .'">';

    $search_box = '<div class="input-group btn-format-bg"><input type="text" class="form-control" onkeyup="filter_vendors(this, \'panel-content-' . $vendor_title_id .'\');" placeholder="Search Products" /><span class="input-group-btn">
        <button class="btn btn-default" type="button"><i class="fa fa-search" aria-hidden="true"></i></button></span></div>';

    $company_image_path = $base_url . '/' . $path_to_theme . '/images/scorecard_company_icon_small.png';


    $company_image = '<div class="clearfix orange-image"><div class="display-inline-block select-product-display-image padding-right-10"><img src="' . $company_image_path . '" /></div>';

    $add_new_product_link = '';

    $content .= '<div class="panel-body"><div class="row"><div class="col-md-9 col-sm-9 col-xs-12 margin-bottom-10" title = "' . $titles . '">' . $company_image . '<h4 class="display-inline-block">Products</h4>: ' . $titles_trim . '</div></div><div class="col-md-3 col-sm-3 col-xs-12 margin-bottom-10">' . $search_box . '</div></div>';

    $content .= '<div class="row">';

    foreach ($products as $venKey => $vendorNid) {
      $node = node_load($vendorNid);
      // Getting title of company.
      $vendor_nid = $node->field_manufacture_reference['und'][0]['nid'];
      $vendor_title = _get_title_of_node($vendor_nid);

      $replace_to = array('-', ' ', '.', '_');
      $vendor_short_name = strtoupper(substr(str_replace($replace_to, '', $vendor_title), 0, 2));

      $vendor_title_trim = $vendor_title;
      if (strlen($vendor_title) > 18) {
        $vendor_title_trim = substr($vendor_title, 0, 18) . '...';
      }

      $description = $sku = 'N.A.';
      $description_title = '';

      $title = $node->title;
      $title_trim = $title;
      if (strlen($title) > 18) {
        $title_trim = substr($title, 0, 18) . '...';
      }

      if (!empty($node->field_description['und'][0]['value'])) {
        $description = substr($node->field_description['und'][0]['value'], 0, 18) . '...';
        if (strlen($node->field_description['und'][0]['value']) > 18) {
          $description_title = $node->field_description['und'][0]['value'];
        }
        else {
          $description = $node->field_description['und'][0]['value'];
        }
      }
      if (!empty($node->field_sku_number['und'][0]['value'])) {
        $sku = $node->field_sku_number['und'][0]['value'];
      }

      $green_check = '';
      if (!empty($all_products_scorecard) && in_array($vendorNid, $all_products_scorecard)) {
        $green_check = '<i class="fa fa-2x fa-check-circle pull-right text-success" aria-hidden="true"></i>';
      }

      $content .= '<div class="col-md-3 col-sm-3 col-xs-12 remove-hide-this-product margin-bottom-15">
                    <div id="' . $node->nid . '-' . $get_active_score_card . '" class="select-product-for-sc ' . $node->nid . '-' . $get_active_score_card . '" style="cursor:pointer;" data="add">
                    <div class="clearfix relative">
                      <div class="row margin-0 sku-items">
                        <div class="col-md-4 sku-item-left">
                          <div class="panel-body sku-item-left-icon"> ' . $vendor_short_name . ' </div>
                        </div>
                        <div class="col-md-8 padding-0 sku-item-right">
                          <div class="panel-body">
                            ' . $green_check . '
                            <div class="vendor-title-search" title="' . $title . '">' . $title_trim . '</div>
                            <div title="' . $vendor_title. '">' . $vendor_title_trim . '</div>
                            <div title="' . $description_title . '">' . $description . '</div>
                            <div>' . $sku . '</div>
                          </div>
                        </div>
                      </div>
                    </div>
                    </div>
                  </div>';
    }

    $content .= '</div></div></div>';
  }

  $content .= '</div>';

  return $content;
}

/**
 * Helper function to get search options according to criteria.
 */
function _get_search_vendor_options($criteria = 'all') {
  if ($criteria == 'companies') {
    // Returning all companies.
    return _get_all_organigation_mapping();
  }

  $products = db_select('node', 'n')
    ->fields('n', array('nid', 'title'))
    ->condition('type', 'scorecard_products')
    ->condition('status', 1)
    ->orderBy('created', 'DESC')
    ->execute()
    ->fetchAllKeyed();

  if (!empty($products)) {
    $products = _array_walk_products_for_company_titles($products);
  }

  if ($criteria == 'products') {
    // Getting all products.
    return $products;
  }

  $categories = _get_all_product_categories_for_listing();

  if ($criteria == 'categories') {
    // Getting all products.
    return $categories;
  }

  if ($criteria == 'all') {
    return array(
      t('Products') => $products,
      t('Categories') => $categories,
      t('Companies') => _get_all_organigation_mapping(),
    );
  }

  return array();
}

/**
 * Helper function to get previous ratings and comments.
 */
function _get_previous_ratings_comments(&$questions, $criteria = '', $products = array(), $companies = array()) {
  // As questions are required, if we do not get these then aborting.
  if (empty($questions)) {
    return;
  }

  if (empty($products) && empty($companies)) {
    return;
  }

  global $user;

  // Our results will be dependent on criteria.
  // If we do not get a criteria then judging it by products.
  if (empty($criteria)) {
    $criteria = !empty($products) ? 'product_based' : 'company_based';
  }

  $datas = $criteria == 'product_based' ? $products : $companies;
  $element = $criteria == 'product_based' ? 'pid' : 'company_nid';

  // Trying to get data.

  // Get all categories and question IDs.
  $cats = array();
  $ques = array();
  foreach ($questions as $category => $qdata) {
    $cats[$category] = $category;
    foreach ($qdata as $key => $value) {
      $ques[$value->id] = $value->id;
    }
  }

  $query = db_select('m6connect_qbuilder_rating', 'r');
  $query->leftJoin('m6connect_qbuilder_comments', 'c', 'r.qid=c.qid AND r.uid=c.uid');
  $query->fields('r', array('ratings', 'qid', 'pid', 'company_nid'));
  $query->fields('c', array('comments'));
  $query->condition('r.uid', $user->uid);
  $query->condition('r.qid', $ques);
  $query->condition('r.cid', $cats);

  if ($criteria == 'company_based') {
    $query->isNull('r.pid');
    $query->isNotNull('r.company_nid');
  }
  else {
    $query->isNull('r.company_nid');
    $query->isNotNull('r.pid');
  }

  $results = $query->execute()->fetchAll();

  if (!empty($results)) {
    foreach ($results as $result) {
      foreach ($datas as $data) {
        foreach ($questions as $category => $qdata) {
          $cats[$category] = $category;
          foreach ($qdata as $key => $value) {
            if ($result->qid == $value->id && $result->{$element} == $data) {
              $questions[$category][$key]->{'defaults'}[$data] = array(
                'ratings'  => $result->ratings,
                'comments' => $result->comments,
              );
            }
          }
        }
      }
    }
  }
}

/**
 * Helper function to get products array with company titles.
 */
function _array_walk_products_for_company_titles($products = array()) {
  if (empty($products)) {
    return $products;
  }

  foreach ($products as $key => &$value) {
    $company_nid = _get_company_nid_of_product($key);
    $company_title = _get_title_of_node($company_nid);
    if (!empty($company_title)) {
      $value .= ' | ' . ucwords($company_title);
    }
  }

  return $products;
}

/**
 * Helper function to get company nid of product (SCM).
 */
function _get_company_nid_of_product($product_nid = NULL) {
  if (empty($product_nid)) {
    return '';
  }

  return db_select('field_data_field_manufacture_reference', 'p')
    ->fields('p', array('field_manufacture_reference_nid'))
    ->condition('entity_id', $product_nid)
    ->condition('bundle', 'scorecard_products')
    ->execute()
    ->fetchField();
}


################################################################################
#############################  End Helper Functions ############################
################################################################################
