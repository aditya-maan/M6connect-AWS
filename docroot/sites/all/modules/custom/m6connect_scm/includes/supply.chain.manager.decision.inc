<?php
/*
 * Start work for decision  
 */

/**
 * Menu callback for scorecard/resolve-comment/%
 */
function resolve_scorecard_comment($cid = NULL) {
      $return = array(
        'status' => 'Failed',
        'output' => '',
      );

      if (empty($cid)) {
        print drupal_json_output($return);
        exit;
      }

  // If we get an ID, we check whether its comment is already saved or not.
  $count = db_select('m6connect_qbuilder_comments_reply', 'c')
    ->fields('c')
    ->condition('comment_id', $cid)
    ->execute()
    ->rowCount();

  if ($count > 0) {
    // If there are any previous comments, then resolving those.
    db_update('m6connect_qbuilder_comments_reply')
      ->fields(array(
        'resolved' => 1,
      ))
      ->condition('comment_id', $cid)
      ->execute();

    if (empty($_POST['comment'])) {
      // If there is no comment to insert, then our work is done.
      $return['status'] = 'Success';
      print drupal_json_output($return);
      exit;
    }
  }

  if ($count == 0 && empty($_POST['comment'])) {
    // If there are no previous comments, and there is no comment entered by
    // user, then we abort.
    $return['status'] = 'No comment';
    print drupal_json_output($return);
    exit;
  }

  // If we do have a comment, we try to insert it.
  if (!empty($_POST['comment'])) {
    // Even if we have updated previous comments, if we have a comment, we
    // insert it, and also mark it as resolved.
    global $user;

    db_insert('m6connect_qbuilder_comments_reply')
      ->fields(array(
        'uid' => $user->uid,
        'comment_id' => $cid,
        'comment' => check_plain($_POST['comment']),
        'resolved' => 1,
        'created' => REQUEST_TIME,
      ))
      ->execute();

    $account = user_load($user->uid);

    $account_pic =  !empty($account->field_user_profile_photo[LANGUAGE_NONE]['0']['uri']) ? $account->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';

    $account_pic_markup = '<img typeof="foaf:Image" src="' . file_create_url($account_pic) . '" class="img-circle media-object" style="height:40px; width:40px;">';

    $output = '<div class="media">
                <div class="media-left">' . $account_pic_markup . '</div>
                <div class="media-body">
                  <div class="user-reply-comment">' . check_plain($_POST['comment']) . '</div>
                </div>
              </div>';

    $return['status'] = 'Success';
    $return['output'] = $output;

    print drupal_json_output($return);
    exit;
  }

  print drupal_json_output($return);
  exit;
}

/**
 * Menu callback for scorecard/save-comment/%
 */
function save_scorecard_comment($cid = NULL) {
  $return = array(
    'status' => 'Failed',
    'output' => '',
  );

  if (empty($cid) || empty($_POST['comment'])) {
    print drupal_json_output($return);
    exit;
  }

  global $user;

  // Trying to get resolved status.
  $resolved = 0;
  $q = db_select('m6connect_qbuilder_comments_reply', 'c')
    ->fields('c')
    ->condition('comment_id', $cid)
    ->execute();
  
  if ($q->rowCount() > 0) {
    $rows = $q->fetchAll();
    foreach ($rows as $row) {
      $resolved = $row->resolved;
      break;
    }
  }

  db_insert('m6connect_qbuilder_comments_reply')
    ->fields(array(
      'uid' => $user->uid,
      'comment_id' => $cid,
      'comment' => check_plain($_POST['comment']),
      'resolved' => $resolved,
      'created' => REQUEST_TIME,
    ))
    ->execute();

  $account = user_load($user->uid);

  $account_pic =  !empty($account->field_user_profile_photo[LANGUAGE_NONE]['0']['uri']) ? $account->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';

  $account_pic_markup = '<img typeof="foaf:Image" src="' . file_create_url($account_pic) . '" class="img-circle media-object" style="height:40px; width:40px;">';

  $output = '<div class="media">
              <div class="media-left">' . $account_pic_markup . '</div>
              <div class="media-body">
                <div class="user-reply-comment">' . check_plain($_POST['comment']) . '</div>
              </div>
            </div>';

  $return['status'] = 'Success';
  $return['output'] = $output;

  print drupal_json_output($return);
  exit;
}

function scorecard_decision_content($where = '', $what = 'decision') {
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_scm') . '/js/m6connect_scm_casemanager.js');

  if ($where == 'casemanager') {
    $elements['prgram-scm-menu-items'] = array(
      '#markup' => scm_csemanager_main_menu_links_content(),
      '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10">',
      '#suffix' => '</div></div>',
    );
  }

  $elements['menu-links'] = array(
    '#markup' => scm_scorecard_dashboard_menu_links_content($where),
    '#prefix' => '<div class="clearfix scm-main-menu margin-bottom-10">',
    '#suffix' => '</div>',
  );

  $elements['project-form']= array(
   '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_decision_form', $where, $what)),
   '#prefix' => '<div class="clearfix margin-bottom-10">',
   '#suffix' => '</div>',
  );

  return $elements;
}

function _casemanager_scorecard_decision_form($form, &$form_state, $where, $what) {
  global $user, $company;
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  // 4 menu items are handled by this form alone.
  $process_function = 'decision_main_container2_process';
  $submit_function = 'decision_stakeholder_submit';
  $prefix_id = 'summary-outer-listing';
  $prefix_class = '';
  if ($what == 'stakeholder') {
    $process_function = 'stakeholder_main_container2_process';
    $prefix_id = 'stakeholder-outer-listing';
  }
  if ($what == 'comments') {
    $process_function = 'comments_main_container2_process';
    $submit_function = 'comments_submit';
    $prefix_id = 'comments-outer-listing';
  }
  if ($what == 'justification') {
    $process_function = 'justification_main_container2_process';
    $submit_function = 'justification_submit';
    $prefix_id = 'justification-outer-listing';
    $prefix_class = 'margin-top-10';
  }

  $form['decision-dialogue'] = array(
    '#type'   => 'markup',
    '#markup' => '<div id="decision-dialogue-box" style="display:none;"></div>',
  );

  $form['main-container']= array(
    '#type'       => 'container',
    '#prefix'     => '<div class="clearfix scm-scorecard"><div id="questionbuilder_scorecard_main_container" class="clearfix">',  
    '#suffix'     => '</div></div>',
    '#attributes' => array('class' => array('row')),
    '#process'    => array('decision_main_container_process'),
  );

  $form['main-container2']['full-container'] = array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('well','well-large','no-bg')),
  );

  $form['main-container2']['full-container']['info-start'] = array(
    '#type'   => 'markup',
    '#markup' => '<div class="clearfix well well-large well-margin-0"><h4>' . t('Decision Recommendation') . '</h4></div><div class="clearfix">',
  );

  $form['main-container2']['full-container']['inner-menu']= array(
    '#markup' => _decision_inner_menu(),
    '#prefix' => '<div class="decision-inner-menu scm-main-menu">',
    '#suffix' => '</div>',
  );

  $form['main-container2']['full-container']['content-container'] = array(
    '#type'    => 'container',
    '#process' => array($process_function),
    '#prefix'  => '<div id="' . $prefix_id . '" class="' . $prefix_class . '">',
    '#suffix'  => '</div>',
  );

  $form['main-container2']['full-container']['info-end'] = array(
    '#type'   => 'markup',
    '#markup' => '</div>',
  );
  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }
  $form['submit']['save'] = array(
    '#type'   => 'submit',
    '#value'  => 'Save',
    '#submit' => array($submit_function),
    '#prefix' => '<div class="clearfix custom-submit-select-pro-button '.$sharerecommendation.'">',  
  );
  
  $form['submit']['share'] = array(
    '#type'   => 'markup',
    '#markup' => l('<input type="button" value="Share Recommendation(s)" class="btn btn-success">', url('/share-recommendation/'.$getNodesNids.'/nojs'), array('html' => TRUE, 'external' => TRUE,'attributes'=> array('class'=>array('ctools-modal-assign-dashboard-popup-style ctools-use-modal')))),
  );

  $form['actions']['reset'] = array(
    '#type'   => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button">',
    '#suffix' => '</div>',
  );

  return $form;
}

function decision_main_container_process($element, &$form_state) {
  global $company;
  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight' => 3,
  );     
  $element['main-container']['full-container']['inner-left-one']= array(
    '#type' => 'container',
  );
  $element['main-container']['full-container']['inner-left-one']['scorecard-info-title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="clearfix no-bg well well-large"><div class="qbuilder-scorinfo margin-5 clearfix">',
  );
 
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  if(isset($getNodesNids) && !empty($getNodesNids) && is_numeric($getNodesNids)) {
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
  $element['main-container']['full-container']['inner-left-one']['scorecard-number-select'] = array(
    '#type' => 'select',
    '#options' => $scardArr,
    '#empty_option' => 'Choose scorecard',
	'#default_value' => $getNodesNids,
    '#attributes' => array('class'=> array('form-control scorecard-name-title')),
    '#prefix' => '<div class="col-md-6 col-sm-6 col-xs-12"><div class="clearfix"><p class="blue-and-bold">Select Scorecard</p>',
    '#suffix' => '</div></div>',  
    '#ajax' => array(
      'wrapper' => 'replace-facility-options-here',
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
    
  }
  $element['main-container']['full-container']['inner-left-one']['scorecard-title'] = array(
    '#type' => 'markup',
    '#markup' => '</div></div>',
  );

  return $element;
}

function decision_main_container2_process($elements, &$form_state) {
  $form_called = $form_state['build_info']['form_id'] == '_casemanager_scorecard_decision_form' ? 'decision' : 'casemanager';
  global $company;
  $output  = '';

  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');

  $query = db_select('m6connect_qbuilder_data','qbd');
  $query->leftjoin('m6connect_qbuilder_rating','qbr','qbr.cid=qbd.category_id AND qbd.id=qbr.qid');
  $query->fields('qbd',array('category_id','weight'));
  $query->fields('qbr',array('cid','pid','ratings', 'company_nid'));
  $query->condition('qbd.scorecard_nid',$getNodesNids);
  $query->condition(db_or()->isNotNull('qbr.pid')->isNotNull('qbr.company_nid'));
  // $query->isNotNull('qbr.pid');
  $result = $query->execute()->fetchAll();

  $cat = array();
  $totalrating = array();

  if (!empty($result)) {
    $first_result = $result[0];

    $element = !empty($first_result->pid) ? 'pid' : 'company_nid';
    $table_header = !empty($first_result->pid) ? t('Vendor | Product') : t('Vendor');
    $fetch_function = !empty($first_result->pid) ? '_get_all_products_by_scorecard' : '_get_all_products_companies_by_scorecard';

    if ($form_called == 'decision') {
      $elements['product-or-company'] = array(
        '#type'   => 'value',
        '#value' => $element,
      );
    }

    foreach ($result as $key => $value) {
      $cat[$value->cid] = $value->cid;
      $totalrating[$value->{$element}][$value->cid] += $value->ratings*$value->weight;
    }

    $products = $fetch_function($getNodesNids,1);
    $rows = array();
    $header = array( 
      array('data' => $table_header, 'class' => array('text-center')),    
    );

    foreach ($cat as $pkey=>$pvalue ) {
      $header[] = array('data' => t(_get_question_category_title_by_id($pvalue)), 'class' => array('text-center'));
    }

    $header[] = array('data' => t('Total Score'), 'class' => array('text-center'));

    foreach ($products as $pkey => $pvalue) {
      $rows[$pkey]['data'][$pkey] = array('data' => _get_company_product_name_by_pid($pvalue),'class' => array('text-center'));
      $rows[$pkey]['class'] = array('justification-'.$pvalue);
      
    
      $tscore = '';

      /*foreach ($totalrating[$pvalue] as $ckey => $rvalue) {
        $rows[$pkey]['data'][] = array('data' => (!empty($rvalue)?$rvalue:0),'class' => array('text-center','category-rating'));
        $tscore +=$rvalue;
      }*/
      foreach ($cat as $ckey) {
        $rvalue = (isset($totalrating[$pvalue][$ckey])?$totalrating[$pvalue][$ckey]:0);
        $rows[$pkey]['data'][] = array('data' => $rvalue,'class' => array('text-center','category-rating'));
        $tscore +=$rvalue;
      }
      $removelink = '';
      if ($form_called == 'decision') {
        $removelink = l('<i class="fa fa-trash-o" aria-hidden="true"></i>', 'javascript:void(0);', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('pvalue' => $pvalue, 'class' => array('pull-right', 'justremove-item'))));
      }
      $rows[$pkey]['data'][] = array('data' => $tscore. $removelink,'class' => array('text-center','category-rating-total'));
      
      //  
    }

    $output = theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No Scorecard created yet', 'attributes' => array('class' => array('table', 'm6init-datatable', 'table-hover', 'text-center', 'm6connect-custom-table', 'table-outer-border')), 'id'=>'search-m6id-form'));
  }

  $elements['decision-rating-data'] = array(
    '#type'   => 'markup',
    '#markup' => render($output),
  );
  if ($form_called == 'decision') {
    $elements['justification-remove-item'] = array(
      '#type'       => 'hidden',
      '#attributes' => array('class' => array('justification-rowremove')),
    );
  }
  
  return $elements;
}

function stakeholder_main_container2_process($elements, &$form_state) {
  $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');

  if (empty($scorecard_nid)) {
    $output = t('No active scorecard found!');
  }
  else {
    $scorecard_node = node_load($scorecard_nid);
    $output = _get_group_ratings_content_evaluate($scorecard_node,1);
  }
  $elements['decision-rating-data'] = array(
    '#type'   => 'markup',
    '#markup' => $output,
  );

  return $elements;
}

function comments_main_container2_process($elements, &$form_state) {
  $form_called = $form_state['build_info']['form_id'] == '_casemanager_scorecard_decision_form' ? 'decision' : 'casemanager';

  $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');
  $scorecard_node = node_load($scorecard_nid);

  if (empty($scorecard_node)) {
    // If no active scorecard found, then abort.
    $elements['no-scorecard-found'] = array(
      '#type' => 'markup',
      '#markup' => t('No active scorecard found!'),
    );

    return $elements;
  }

  // Getting question builder node.
  $question_builder_node = _get_question_builder_node_by_scorecard($scorecard_node);

  // We need to judge that whether rating was requested on company basis or
  // product basis. If company basis is requested, only one set of questions
  // will be shown to rater, else each product of that company will be asked
  // with a question set.
  $criteria = 'company_based';
  if (!empty($question_builder_node->field_selection_criteria[LANGUAGE_NONE][0]['value'])) {
    $criteria = $question_builder_node->field_selection_criteria[LANGUAGE_NONE][0]['value'];
  }

  // If criteria is product based, then we need products associated with the
  // current scorecard's company.
  $products = $companies = array();
  if ($criteria == 'product_based') {
    // Getting all products.

    // If products are to be get by this scorecard reference, then use below
    // function else getting all products of the scorecard's company.
    $products = _get_all_products_by_scorecard($scorecard_node->nid,1);

    // Else use this if want to get all products of scorecard's company.
    // $products = _get_all_products_by_vendor($scorecard_node->og_group_ref[LANGUAGE_NONE][0]['target_id']);
  }
  elseif ($criteria == 'company_based') {
    // If a company based criteria is choosed, then we need to get all companies
    // of the products for this scorecard.
    $companies = _get_all_products_companies_by_scorecard($scorecard_node->nid,1);
    if ($form_called == 'decision') {
      $form_state['companies'] = $companies;
    }
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

  if (empty($questions)) {
    $elements['no-comments-found'] = array(
      '#type' => 'markup',
      '#markup' => t('No comments found from users!!'),
    );

    return $elements;
  }

  // Getting comments of users question wise.
  _get_all_users_comments_scorecard($questions, $criteria, $products, $companies);

  $elements = array();
  $datas = $criteria == 'product_based' ? $products : $companies;
  $p = 0;
  $all_empty = TRUE;
  foreach ($datas as $data) {
    $no_comments = FALSE;
    foreach ($questions as $key => $value) {
      if (!empty($value)) {
        foreach ($value as $key1 => $value1) {
          if (!empty($value1)) {
            if (empty($value1->defaults[$data])) {
              $no_comments = TRUE;
            }
            else {
              $all_empty = FALSE;
            }
          }
        }
      }
    }

    // If there are no comments, then skip.
    if ($no_comments) {
      continue;
    }

    $p++;
    // Getting node title by its id.
    $node_title = _get_title_of_node($data);

    // Product Fieldset.
    $prod_fieldset = 'node-' . $data;

    // Saving essential data for theme function.
    $elements[$prod_fieldset] = array(
      '#type' => 'fieldset',
      '#title' => $node_title,
      '#collapsed' => $p == 1 ? FALSE : TRUE,
      '#collapsible' => TRUE,
      '#attributes' => $p == 1 ? array('class' => array('collapsible', 'bid-package-fieldset', 'fieldsetbigtitle')) : array('class' => array('collapsible', 'collapsed', 'bid-package-fieldset', 'fieldsetbigtitle')),
      '#attached' => array(
        'library' => array(
          array('system', 'drupal.collapse'),
        ),
      ),
      '#prefix' => '<div class="clearfix comment-reply-fieldset">',
      '#suffix' => '</div>',
    );

    $c = 0;
    foreach ($questions as $category => $qset) {
      $question_count = 0;
      $all_resolved = TRUE;
      foreach ($qset as $count_key => $count_value) {
        $question_count += count($count_value->defaults[$data]);

        foreach ($count_value->{'defaults'}[$data] as $res_key => $res_value) {
          $temp_arr = $res_value;
          $temp_shift = array_shift($temp_arr);
          if (empty($temp_shift['resolved'])) {
            $all_resolved = FALSE;
          }
        }
      }
      $c++;
      $category_title = _get_question_category_title_by_id($category);

      $cat_fieldset = 'category-fieldset-' . $category;

      $resolved_icon = '';
      if (!$all_resolved) {
        $resolved_icon = '<i class="fa fa-exclamation-circle" aria-hidden="true"></i>   ';
      }
      $cat_fieldset_title = $resolved_icon . ' (' . $question_count . ') ' . $category_title;

      $elements[$prod_fieldset][$cat_fieldset] = array(
        '#type' => 'fieldset',
        '#title' => $cat_fieldset_title,
        '#collapsed' => $c == 1 ? FALSE : TRUE,
        '#collapsible' => TRUE,
        '#attributes' => $c == 1 && $p == 1 ? array('class' => array('collapsible', 'bid-package-fieldset', 'fieldsetmediumtitle')) : array('class' => array('collapsible', 'collapsed', 'bid-package-fieldset', 'fieldsetmediumtitle')),
        '#attached' => array(
          'library' => array(
            array('system', 'drupal.collapse'),
          ),
        ),
        '#prefix' => '<div class="clearfix">',
        '#suffix' => '</div>',
      );

      // Category Container.
      $cat_container = 'category-container-' . $category;
      $elements[$prod_fieldset][$cat_fieldset][$cat_container] = array(
        '#type'  => 'container',
        '#theme' => 'raters_comments_container_theme',
      );

      // Saving essential data for theme function.
      $elements[$prod_fieldset][$cat_fieldset][$cat_container]['#storage'] = array(
        'scorecard_node'        => $scorecard_node,
        'question_builder_node' => $question_builder_node,
        'criteria'              => $criteria,
        'products'              => $products,
        'companies'             => $companies,
        'categories'            => $categories,
        'questions'             => $questions,
        'form_called'           => $form_called,
      );

      // Now each category has questions, generating them.
      if (empty($qset)) {
        // If by any means, we do not have questions.
        $elements[$prod_fieldset][$cat_fieldset][$cat_fieldset][$cat_container]['no_questions'] = array(
          '#type'   => 'markup',
          '#markup' => t('There are no questions/comments in this category.'),
        );
      }
      else {
        $i = 0;
        $atleast_one_comment = FALSE;
        foreach ($qset as $qdata) {
          $i++;

          $elements[$prod_fieldset][$cat_fieldset][$cat_container][$qdata->id]['question'] = array(
            '#type'   => 'markup',
            '#markup' => $qdata->question,
          );

          foreach ($qdata->{'defaults'}[$data] as $user_id => $user_meta) {
            $comment_meta = array_shift($user_meta);
            $cid = $comment_meta['cid'];
            $comment = $comment_meta['comments'];
            $reply = !empty($comment_meta['reply']) ? $comment_meta['reply'] : '';

            if (!empty($comment_meta['resolved'])) {
              if ($form_called == 'casemanager') {
                $fprefix = '<div class="media-left">';
                $fprefix .= '<i class="fa fa-2x fa-check-circle-o comment-resolved pointer-events-none" aria-hidden="true" id="' . $cid . '"></i>';
                $fprefix .= '</div>';
                $fprefix .= '<div class="media-body"><h4>' . t('Resolved') . '</h4></div>';
              }
              else {
                $fprefix = '<i class="fa fa-2x fa-check-circle-o comment-resolved" aria-hidden="true" id="' . $cid . '"></i>';
              }
            }
            else {
              if ($form_called == 'casemanager') {
                $fprefix = '<div class="media-left">';
                $fprefix .= '<i class="fa fa-2x fa-check-circle-o resolve-comment pointer-events-none" aria-hidden="true" id="' . $cid . '"></i>';
                $fprefix .= '</div>';
                $fprefix .= '<div class="media-body"><h4>' . t('Not Resolved') . '</h4></div>';
              }
              else {
                $fprefix = '<i class="fa fa-2x fa-check-circle-o resolve-comment" aria-hidden="true" id="' . $cid . '"></i>';
              }
            }

            $elements[$prod_fieldset][$cat_fieldset][$cat_container][$qdata->id]['user_comment_' . $user_id] = array(
              '#type' => 'container',
            );

            $elements[$prod_fieldset][$cat_fieldset][$cat_container][$qdata->id]['user_comment_' . $user_id]['#element_storage'] = array(
              'rater_uid' => $user_id,
              'reply'     => $reply,
            );

            $elements[$prod_fieldset][$cat_fieldset][$cat_container][$qdata->id]['user_comment_' . $user_id]['comment'] = array(
              '#type'   => 'markup',
              '#markup' => $comment,
            );

            if ($form_called == 'decision') {
              $elements[$prod_fieldset][$cat_fieldset][$cat_container][$qdata->id]['user_comment_' . $user_id]['reply'] = array(
                '#type'          => 'textfield',
                '#title'         => t('Reply'),
                '#title_display' => 'invisible',
                '#attributes'    => array('placeholder' => t('Write a response'), 'class' => array('reply-comment-decision')),
                '#maxlength'     => 4096,
                '#field_suffix'  => $fprefix,
                '#prefix'        => '<div id="cr-' . $user_id . '">',
                '#suffix'        => '</div>',
                '#parents'       => array('qdata', $cid, 'reply'),
              );
            }
            else {
              $elements[$prod_fieldset][$cat_fieldset][$cat_container][$qdata->id]['user_comment_' . $user_id]['reply'] = array(
                '#type'          => 'markup',
                '#markup'        => $fprefix,
                '#prefix'        => '<div id="cr-' . $user_id . '" class="media">',
                '#suffix'        => '</div>',
              );
            }
          }
        }
      }
    }
  }

  if ($all_empty) {
    // There are no comments for this scorecard.
    $elements = array();
    $elements['no_comments_found'] = array(
      '#type' => 'markup',
      '#markup' => t('No comments found from users!'),
    );
    return $elements;
  }

  return $elements;
}

function theme_raters_comments_container_theme($variables) {
  global $user, $base_url;

  $current_user = user_load($user->uid);

  // Preparing User's Pic.
  $user_pic =  !empty($current_user->field_user_profile_photo[LANGUAGE_NONE]['0']['uri']) ? $current_user->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';

  $user_pic_markup = '<img typeof="foaf:Image" src="' . file_create_url($user_pic) . '" class="img-circle media-object" style="height:40px; width:40px;">';

  // Getting user's name.
  $user_name = _get_user_full_name($current_user->uid, $current_user);

  $elements = $variables['element'];

  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }

  $output = '<div class="outer-container">';

  foreach ($elements as $key => $value) {
    if (strrpos($key, '#') === 0) {
      continue;
    }

    if (strpos($key, 'no_comments_found') === 0) {
      $output .= '<div class="clearfix text-center text-muted">
                    <h4>' . drupal_render($value) . '</h4>
                  </div>';
      break; // If there are no comments, then exit the loop.
    }
    else {
      // Dealing with each question.
      $output .= '<div class=container-item>';

      $output .= '<div class="main-question">';
      // Render question.
      if (!empty($value['question'])) {
        $output .= '<h4 class="margin-bottom-10">' . drupal_render($value['question']) . '</h4>';
      }

      $output .= '<div class="clearfix comment-item margin-bottom-10">';

      // Now rendering comments and reply textfields.
      foreach ($value as $qkey => $qdata) {
        if ($qkey == 'question') {
          // Skip the question as we already rendered it.
          continue;
        }

        if (strpos($qkey, '#') === 0) {
          continue;
        }

        // Rater's Account.
        $account = user_load($qdata['#element_storage']['rater_uid']);

        // Preparing Rater's Pic.
        $rater_pic =  !empty($account->field_user_profile_photo[LANGUAGE_NONE]['0']['uri']) ? $account->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';

        $rater_pic_markup = '<img typeof="foaf:Image" src="' . file_create_url($rater_pic) . '" class="img-circle media-object" style="height:40px; width:40px;">';

        // Getting user's name.
        $rater_name = _get_user_full_name($account->uid, $account);

        $output .= '<div class="well well-large no-bg '.$sharerecommendation.'">';
        $output .= '<div class="media-list">';
        $output .= '<div class="media">';

        // Rater's Image.
        $output .= '<div class="media-left">';
        $output .= $rater_pic_markup;
        $output .= '</div>';

        $output .= '<div class="media-body">';

        // Rater's Name.
        $output .= '<h5 class="media-heading">' . $rater_name . '</h5>';

        // Render rater's comment.
        $output .= '<div class="comment-markup">';
        $output .= drupal_render($qdata['comment']);
        $output .= '</div>'; // End comment-markup

        // Replyer's Section.

        // First render any previous replies of user.
        $prev_reply = $qdata['#element_storage']['reply'];
        if (!empty($prev_reply)) {
          // Right now only one user can reply to threads.
          foreach ($prev_reply as $prev_reply_uid => $prev_replies) {
            // Preparing User's Pic.
            $prev_user = user_load($prev_reply_uid);

            $prev_user_pic =  !empty($prev_user->field_user_profile_photo[LANGUAGE_NONE]['0']['uri']) ? $prev_user->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';

            $prev_user_pic_markup = '<img typeof="foaf:Image" src="' . file_create_url($prev_user_pic) . '" class="img-circle media-object" style="height:40px; width:40px;">';

            // Getting user's name.
            $prev_user_name = _get_user_full_name($prev_user->uid, $prev_user);

            foreach ($prev_replies as $prev_reply_data) {
              $output .= '<div class="media">';

              $output .= '<div class="media-left">';
              $output .= $prev_user_pic_markup;
              $output .= '</div>';

              $output .= '<div class="media-body">';

              // Render user's replies.
              $output .= '<div class="user-reply-comment">';
              $output .= $prev_reply_data;
              $output .= '</div>';

              $output .= '</div>';

              $output .= '</div>';
            }
          }
        }
        $output .= '<div class="media">';

        $output .= '<div class="media-left">';
        $output .= $user_pic_markup;
        $output .= '</div>';

        $output .= '<div class="media-body">';

        // Render user's reply textfield.
        $output .= '<div class="user-reply-item">';
        $output .= drupal_render($qdata['reply']);
        $output .= '</div>'; // End user-reply-item

        $output .= '</div>';

        $output .= '</div>';

        $output .= '</div>'; // End media-body
        $output .= '</div></div></div>'; // End media; media-list; well well-large no-bg

      }
      $output .= '</div>'; // End clearfix comment-item
      $output .= '</div>'; // End main-question

      $output .= '</div>'; // End container-item
    }
  }

  $output .= '</div>'; // End outer-container

  // $output .= drupal_render_children($elements);

  return $output;
}


function _get_all_users_comments_scorecard(&$questions, $criteria = '', $products = array(), $companies = array()) {
  if (empty($questions)) {
    return;
  }

  $datas = $criteria == 'product_based' ? $products : $companies;
  $element = $criteria == 'product_based' ? 'pid' : 'company_nid';

  // Get all categories and question IDs.
  $cats = array();
  $ques = array();
  foreach ($questions as $category => $qdata) {
    $cats[$category] = $category;
    foreach ($qdata as $key => $value) {
      $ques[$value->id] = $value->id;
    }
  }

  if (empty($ques)) {
    // If we do not have any question IDs then abort.
    return;
  }

  $query = db_select('m6connect_qbuilder_comments', 'c');
  $query->leftJoin('m6connect_qbuilder_comments_reply', 'r', 'c.id=r.comment_id');
  $query->fields('c', array('qid', 'pid', 'company_nid', 'comments', 'uid', 'id'));
  $query->fields('r', array('resolved', 'comment'));
  $query->addField('r', 'uid', 'reply_uid');
  $query->condition('c.qid', $ques);
  $query->condition('c.cid', $cats);

  if ($criteria == 'company_based') {
    $query->isNull('c.pid');
    $query->isNotNull('c.company_nid');
  }
  else {
    $query->isNull('c.company_nid');
    $query->isNotNull('c.pid');
  }

  $results = $query->execute()->fetchAll();

  if (empty($results)) {
    return;
  }

  foreach ($results as $result) {
    foreach ($datas as $data) {
      foreach ($questions as $category => $qdata) {
        $cats[$category] = $category;
        foreach ($qdata as $key => $value) {
          if ($result->qid == $value->id && $result->{$element} == $data && !empty($result->comments)) {
            $questions[$category][$key]->{'defaults'}[$data][$result->uid][$result->id]['cid'] = $result->id;
            $questions[$category][$key]->{'defaults'}[$data][$result->uid][$result->id]['comments'] = $result->comments;
            $questions[$category][$key]->{'defaults'}[$data][$result->uid][$result->id]['resolved'] = $result->resolved;
            // $questions[$category][$key]->{'defaults'}[$data][$result->uid][$result->id] = array(
            //   'cid'      => $result->id,
            //   'comments' => $result->comments,
            //   'resolved' => $result->resolved,
            // );
            if (!empty($result->reply_uid) && $result->comment) {
              $questions[$category][$key]->{'defaults'}[$data][$result->uid][$result->id]['reply'][$result->reply_uid][] = $result->comment;
            }
          }
        }
      }
    }
  }
}

/**
 * Submit handlers.
 */
function decision_stakeholder_submit($form, &$form_state) { //dpm($form_state,'$form_state');
  global $user,$company;
  $values = $form_state['values'];
  if(!empty($values['scorecard-number-select'])){
    $removeitem = (!empty($values['justification-remove-item'])?explode(',',$values['justification-remove-item']):'');
    
    if(isset($removeitem) && !empty($removeitem)){
      if($values['product-or-company'] == 'pid'){
         db_update('scorecard_references')->fields(array('status'=>0))
        ->condition('product_nid', $removeitem, 'IN')
        ->condition('company_nid', $company->nid, '=')
        ->execute();
      }
      if($values['product-or-company'] == 'company_nid'){
        $query = db_select('field_data_field_manufacture_reference','sr');
        $query->fields('sr',array('entity_id'));
        $query->condition('sr.field_manufacture_reference_nid',$removeitem,'IN');
        $getPidByCompanynid = $query->execute()->fetchCol();

         db_update('scorecard_references')->fields(array('status'=>0))
        ->condition('product_nid', $getPidByCompanynid, 'IN')
        ->condition('company_nid', $company->nid, '=')
        ->execute();
      }
    }
  }
}

function comments_submit($form, &$form_state) {
  global $user;

  if (!empty($form_state['values']['qdata'])) {
    $datas = $form_state['values']['qdata'];

    $cids = array_keys($datas);

    // We shall get any previous entries for the given comment ids.
    // Because if we have previous entries then we shall update the previous
    // entries and not remove these.
    $prev_data = db_select('m6connect_qbuilder_comments_reply', 'r')
      ->fields('r', array('comment_id', 'id'))
      ->condition('comment_id', $cids)
      ->execute()
      ->fetchAllKeyed();

    if (!empty($prev_data)) {
      // If we have some entries, then filtering these out.
      $new_cids = array_diff_key($datas, $prev_data);
      $datas = $new_cids;
    }

    $fields = array('uid', 'comment_id', 'comment', 'resolved', 'created');
    $values = array();
    foreach ($datas as $key => $value) {
      if (!empty($value['reply'])) {
        $values[] = array(
          'uid'        => $user->uid,
          'comment_id' => $key,
          'comment'    => $value['reply'],
          'resolved'   => 0,
          'created'    => REQUEST_TIME,
        );
      }
    }

    $query = db_insert('m6connect_qbuilder_comments_reply');
    $query->fields($fields);
    foreach ($values as $record) {
      $query->values($record);
    }
    $query->execute();
  }

  drupal_set_message(t('Data updated successfully.'), 'status', FALSE);
}
