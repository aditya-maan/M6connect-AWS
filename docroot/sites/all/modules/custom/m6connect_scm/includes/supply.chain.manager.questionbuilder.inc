<?php
/*
 * Start work for Question Builder  
 */
function scm_question_builder_content($where =''){
  global $user,$company;  
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
   '#markup' => drupal_render(drupal_get_form('_casemanager_scorecard_questionbuilder_form', $where)),
   '#prefix' => '<div class="clearfix margin-bottom-10">',
   '#suffix' => '</div>',
  );
  $elements['markup-popup'] = array(
    '#markup' => '<div id="conformboxpopup" style="display: none">
            <div class="ui-dialog-content ui-widget-content">
                <p>
                    <label id="lblMessage">
                    </label>
                </p>
            </div>
        </div>',
    '#prefix' => '<div id="conformboxpopup-section">',
    '#suffix' => '</div>',
  ); 
  return $elements; 
}


function _casemanager_scorecard_questionbuilder_form($form, &$form_state, $where) {
  if ($where == 'casemanager') {
    $form['#attributes']['class'] = array('pointer-events-none');
  }

  global $user,$company;  
  $defaultAddnewRow = 50;
  $qbnid ='';
  $qbcatetory_list = scm_scorecard_category_setting(); 
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  $query = db_select('field_data_field_qb_scorecard_referance','qbsr');
  $query->fields('qbsr',array('entity_id'));
  $query->condition('qbsr.field_qb_scorecard_referance_target_id',$getNodesNids);
  $qbnid = $query->execute()->fetchColumn(0);
  $form['active_scorecard_nid'] = array(
    '#type' => 'hidden',
    '#default_value'=>  $getNodesNids,
  );
  $form['question_builder_nid'] = array(
    '#type' => 'hidden',
    '#default_value'=>  $qbnid,
  );
  
  if (!isset($form_state['has_get_node'])) {
    $form_state['has_get_node'] = TRUE;
  }  
  //Lo
  if(isset($qbnid) && !empty($qbnid) && $form_state['has_get_node'] != FALSE){
    $form_state['has_get_node'] = FALSE;
    $node = node_load($qbnid);
    $nodecatcount = count($node->field_question_builder_category['und']);
    foreach($node->field_question_builder_category['und'] as $nkey=>$nvalue){
      $catid =$nvalue['value'];
      $tempIdentifer = uniqid();
      $form_state['question_count0'][$catid] =$tempIdentifer;      
            

      $query = db_select('m6connect_qbuilder_data','squ');    
      $query->fields('squ');    
      $query->condition('squ.category_id',$catid ,'=');
      $query->condition('squ.scorecard_nid', $getNodesNids);
      $query->condition('squ.company_nid',$company->nid,'=');
      $questionListing = $query->execute()->fetchAll();
      if(isset($questionListing) && !empty($questionListing)){
        foreach($questionListing as $qkey=>$qvalue){        
          $tempIdentifer1 = uniqid();
          $form_state['question_count'][$catid][]  = $tempIdentifer1;          
          $form_state['question_default_values'][$catid][$tempIdentifer1] = array(
            'qid' => $qvalue->id,
            'question' => $qvalue->question,
            'weight' => $qvalue->weight ,
            'rating' => $qvalue->rating,
            'score' => $qvalue->score,
            'comments' => $qvalue->comments,
            'hasDefault' => 'HasDefault',
          );               
        }
        $questionCount = count($form_state['question_count'][$catid]);
          for($i = $questionCount+1; $i<= $defaultAddnewRow; $i++) {
            $tempIdentifer3 = uniqid();
            $form_state['question_count'][$catid][] = $tempIdentifer3;
            $form_state['question_default_values'][$catid][$tempIdentifer3] = array(
              'qid' => 0,
              'question' => '',
              'weight' => 0,
              'rating' => 0,
              'score' => 0,
              'comments' => '',
              'hasDefault' => 'NonDefault',
            );
          }
      }
      else{   
          
          for($i = 1; $i<= $defaultAddnewRow; $i++) {
            $tempIdentifer3 = uniqid();
            $form_state['question_count'][$catid][] = $tempIdentifer3;
            $form_state['question_default_values'][$catid][$tempIdentifer3] = array(
              'qid' => 0,
              'question' => '',
              'weight' => 0,
              'rating' => 0,
              'score' => 0,
              'comments' => '',
              'hasDefault' => ($i ==1?'HasDefault':'NonDefault'),
            );
          }
        }
    }
    if(count($qbcatetory_list) > $nodecatcount){
      $form_state['question_count0']['default'] =uniqid();
    }    
  }


  
  

  if (!empty($form_state['triggering_element']['#parents'][0]) && $form_state['triggering_element']['#parents'][0] == 'select_category_ac' ) {    //dpm($form_state,'form_state trigger');
    $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
    $trivalue = $form_state['triggering_element']['#value'];
    $trivaluecount = count($trivalue);
    //drup_msg($trivaluecount);
    $form_state['question_count0'] = array();
    $form_state['question_count'] = array();
    foreach($trivalue as $catid){
      $tempIdentifer = uniqid();
      $form_state['question_count0'][$catid]= $tempIdentifer;       
      if(isset($catid) && !empty($catid)){
        $ListingNode = db_select('m6connect_qbuilder_data','squ');    
        $ListingNode->fields('squ');
        $ListingNode->condition('squ.company_nid',$company->nid,'=');
        $ListingNode->condition('squ.scorecard_nid', $getNodesNids);
        $ListingNode->condition('squ.category_id',$catid ,'=');
        $questionListingNode = $ListingNode->execute()->fetchAll();

        //if (empty($questionListing)) {
          $ListingDefault = db_select('m6connect_scm_scorecard_question','squ');    
          $ListingDefault->fields('squ');    
          $ListingDefault->condition('squ.category_id',$catid,'=');
          $ListingDefault->condition('squ.company_nid',$company->nid,'=');
          $questionListingDefault = $ListingDefault->execute()->fetchAll();
        //}

        if(isset($questionListingNode) && !empty($questionListingNode)){
          $questionListing = $questionListingNode;
        }
        else{
          $questionListing = $questionListingDefault;
        }
        if (!empty($questionListing)) {
          //drup_msg('yes q');
          foreach($questionListing as $qkey=>$qvalue){        
            $tempIdentifer1 = uniqid();
            $form_state['question_count'][$catid][]  = $tempIdentifer1;
            
            $form_state['question_default_values'][$catid][$tempIdentifer1] = array(
              'qid' => (!empty($questionListingNode)?$qvalue->id:0),
              'question' => $qvalue->question,
              'weight' => $qvalue->weight ,
              'rating' => $qvalue->rating,
              'score' => $qvalue->score,
              'comments' => $qvalue->comments,
              'hasDefault' => 'HasDefault',
            );               
          }
          $questionCount = count($form_state['question_count'][$catid]);
          for($i = $questionCount+1; $i<= $defaultAddnewRow; $i++) {
            $tempIdentifer3 = uniqid();
            $form_state['question_count'][$catid][] = $tempIdentifer3;
            $form_state['question_default_values'][$catid][$tempIdentifer3] = array(
              'qid'=>0,
              'question' => '',
              'weight' => 0,
              'rating' => 0,
              'score' => 0,
              'comments' => '',
              'hasDefault' => 'NonDefault',
            );
          }
        }else{   
          //drup_msg('no q');
          for($i = 1; $i<= $defaultAddnewRow; $i++) {
            $tempIdentifer2 = uniqid();
            $form_state['question_count'][$catid][] = $tempIdentifer2;            
            $form_state['question_default_values'][$catid][$tempIdentifer2] = array(
              'qid'=>0,
              'question' => '',
              'weight' => 0,
              'rating' => 0,
              'score' => 0,
              'comments' => '',
              'hasDefault' => ($i ==1?'HasDefault':'NonDefault'),
            );            
          }
        }
      }
    }    
    if(count($qbcatetory_list) > $trivaluecount){      
      $form_state['question_count0']['default'] =uniqid();
    }
    /*else{
      unset($form_state['question_count0']['default']);
    }*/

    //dpm($form_state,'form_state second');
  }

 

  if(empty($form_state['question_count0'])){
    $form_state['question_count0']['default-no-cat'] =uniqid();
  }
  
   
  $form['question_count0'] = array('#type' => 'value', '#value' => $form_state['question_count0']);
  $form['question_count'] = array('#type' => 'value', '#value' => $form_state['question_count']);

  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix scm-scorecard"><div id="questionbuilder_scorecard_main_container" class="clearfix">',  
    '#process' => array('questionbuilder_main_container_process'),
  );  
  $form['main-container-2']= array(
    '#type' => 'container',
    //'#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix scm-scorecard row"><div id="questionbuilder_scorecard_main_container_2" class="clearfix">',  
    '#suffix' => '</div></div>',
    '#process' => array('questionbuilder_main_container2_process'),
  );   

  $getsharerecStatus = get_share_recommendation_status_by_scoreCard();
  $sharerecommendation = '';
  if(isset($getsharerecStatus) && $getsharerecStatus){
    $sharerecommendation = 'pointer-events-none ';
  }
  $form['submit']['save'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
    '#attributes' => array('class'=>array('qb-save')),
    '#submit'=> array('scm_questionbuilder_submit'),
    '#validate' => array('scm_questionbuilder_validate'),
    '#prefix' => '<div class="clearfix custom-submit-select-pro-button '.$sharerecommendation.'">',  
  ); 

  $ListingNode = db_select('m6connect_qbuilder_data','squ');    
  $ListingNode->fields('squ');
  //$ListingNode->condition('squ.uid',$user->uid,'=');
  $ListingNode->condition('squ.company_nid',$company->nid,'=');
  $ListingNode->condition('scorecard_nid', $getNodesNids);
  //$ListingNode->condition('squ.category_id',$catid ,'=');
  $questionCount = $ListingNode->execute()->rowCount();
  $qbShare = '';
  $qbShareUrl = '/share-scorecard/'.$getNodesNids.'/nojs';
  $qbShareClass = 'ctools-modal-assign-dashboard-popup-style ctools-use-modal new-share-scorecard-link';
  /*if($questionCount <=0){
    $qbShare = 'disabled';
    $qbShareUrl = 'javascript:void(0);';
    $qbShareClass ='';
  }*/
  



  $squery =  db_select('field_data_field_scorecard_reference','sref');  
  $squery->leftjoin('field_data_field_share_with_user','swu','swu.entity_id=sref.entity_id');
  $squery->fields('swu',array('field_share_with_user_value'));
  $squery->condition('sref.field_scorecard_reference_nid',$getNodesNids);
  $shareusers =  $squery->execute()->fetchCol();


  $form['submit']['share1'] = array(
    '#type' => 'markup',
    '#markup' => l('<input '.$qbShare.' type="button" value="Share" class="btn btn-success">', $qbShareUrl, array('html' => TRUE, 'external' => TRUE, 'attributes' => array('class' => array($qbShareClass,'sharebtnhidden')))),
    '#prefix' => '<div class="clearfix hidden">',
    '#suffix' => '</div>',
    );
  if(empty($shareusers)){
    if(count(_get_question_builder_data_by_scorecard()) <1){
      $form['submit']['sharebutton'] = array(
        '#type' => 'submit',
        '#value' => 'Share',
        '#name' => 'sharebtnfirst',
        '#attributes' => array('class'=>array('btn bg-success')),
        //'#submit'=> array('scm_questionbuilder_submit'),
        //'#prefix' => '<div class="clearfix custom-submit-select-pro-button">', 

        '#ajax' => array(
          'callback' => 'scm_questionbuilder_submit_callback',
          'wrapper'  => '-casemanager-scorecard-questionbuilder-form',      
          //'effect'   => 'fade',
          // 'method'   => 'replace',
          // 'event'    => 'blur',
        ),
      );
    }else{
    
      $form['submit']['share'] = array(
        '#type' => 'markup',
        '#markup' => l('<input '.$qbShare.' type="button" value="Share" class="btn btn-success">', $qbShareUrl, array('html' => TRUE, 'external' => TRUE, 'attributes' => array('class' => array($qbShareClass)))),
      );
    }
  }else{
    $form['submit']['saveandshareupdate'] = array(
      '#type' => 'submit',
      '#value' => 'Save and Share Update',
      //'#attributes' => array('class'=>array('qb-save')),
      //'#submit'=> array('scm_questionbuilder_submit'),
      //'#validate' => array('scm_questionbuilder_validate'),
      //'#prefix' => '<div class="clearfix custom-submit-select-pro-button">',  
      '#ajax' => array(
          'callback' => 'scm_questionbuilder_submit_callback',
          'wrapper'  => '-casemanager-scorecard-questionbuilder-form',      
          //'effect'   => 'fade',
          // 'method'   => 'replace',
          // 'event'    => 'blur',
        ),
    ); 
  }
  if ($where == 'new_scorecard') {
    $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');
    $form['actions']['reset'] = array(
      '#type'   => 'markup',
      '#markup' => l(t('Cancel'), 'scorecard/cancel/' . $scorecard_nid . '/nojs', array('attributes' => array('class' => array('form-submit', 'cancel-button', 'ctools-use-modal', 'ctools-modal-assign-dashboard-popup-style')))),
    );

    $form['actions']['back'] = array(
      '#type'   => 'markup',
      '#markup' => l(t('Back'), 'scorecard/new/select-products', array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
      '#suffix' => '</div></div></div>',
    );
  }
  else {
    $form['actions']['reset'] = array(
      '#type' => 'markup',
      '#markup' => '<input type="button" value="Cancel" class="form-submit custom-reset-button">',
      '#suffix' => '</div></div></div>',
    );
  }

  return $form;
}

function questionbuilder_main_container_process($element, &$form_state) {
 
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

  // Preparing the header for Scorecard information

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
  $getNodesNids = _fetching_scorecard_information_active('scm_scorecard');

  if(isset($getNodesNids) && !empty($getNodesNids) && is_numeric($getNodesNids)) {
  $scoreCardData = node_load($getNodesNids);  
  $ratingDate = strtotime($scoreCardData->field_rating_due_date['und'][0]['value']);
  $awardDate = strtotime($scoreCardData->field_recommendation_to_award_da['und'][0]['value']);

  $element['main-container']['full-container']['inner-left-one']['scorecard-number-select'] = array(
    '#type' => 'select',
    '#options' => $scardArr,
    '#empty_option' => 'Choose scorecard',
    '#disabled' => $disStatus,
    '#default_value' => $getNodesNids,
    '#attributes' => array('class'=> array('form-control scorecard-name-title border-radius-4')),
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
  //dpm($form_state,'$form_state process');
  return $element;
}

function questionbuilder_main_container2_process($element, &$form_state) {
  global $company;
  $projectList = _load_project_list_with_number(); 
  $rfpList = _load_rfp_list_with_number();
  $qbnid = (isset($form_state['values']['question_builder_nid'])&& !empty($form_state['values']['question_builder_nid'])?$form_state['values']['question_builder_nid']:'');
  $qbnode = (isset($qbnid)&& !empty($qbnid) && is_numeric($qbnid)?node_load($qbnid):'');

  $element['main-container']['full-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-12','col-sm-12','col-xs-12','project-details-full-mid')),
    '#weight' => 3,
  );     
  $element['main-container']['full-container']['inner-left-one']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('well','well-large','no-bg')),
  );         
  /*$element['main-container']['full-container']['inner-left-one']['scorecard-info-title-start'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="clearfix"><h4>Question Builder</h4></div><div class="clearfix well well-large"><div class="row">',
  );*/
  /*
   *  preparing the header for Question Builder
   */  

  /*$entity_nids = _getting_table_data_call('scm_setting_location_entity');
  $element['main-container']['full-container']['inner-left-one']['entity-name'] = array(
    '#type' => 'select',
    '#title' => 'Entity',
    '#empty_option' => 'Select Entity Name',
    '#options' => $entity_nids,
    '#attributes' => array('class'=> array('form-control','entity-name'),'placeholder'=>'Entity Name'),
    '#default_value' => isset($defaultValues['entity-name'])?$defaultValues['entity-name']:'',
    '#prefix' => '<div class="col-md-3 col-sm-3 col-xs-12"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );*/
  /*$getNodesNids = _fetching_scorecard_information_active('scm_scorecard');
  if(isset($getNodesNids) && !empty($getNodesNids) && is_numeric($getNodesNids)) {
    $scoreCardData = node_load($getNodesNids);
  }
  $element['main-container']['full-container']['inner-left-one']['project-name'] = array(
    '#type' => 'select',
    '#title' => 'Project Name',
    '#empty_option' => 'Select Project Name | Number',
    '#options' => $projectList,
    '#attributes' => array('class'=> array('form-control','project-name'),'placeholder'=>'Project Name'),
    '#disabled'=>TRUE,
    '#default_value' => isset($scoreCardData->field_project_nid_for_scm['und'][0]['value'])?$scoreCardData->field_project_nid_for_scm['und'][0]['value']:'',
    '#prefix' => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );
  $element['main-container']['full-container']['inner-left-one']['rfp-name'] = array(
    '#type' => 'select',
    '#empty_option' => 'Select RFP Name | Number',
    '#options' => $rfpList,
    '#title' => 'RFP Name',
    '#attributes' => array('class'=> array('form-control','rfp-name'),'placeholder'=>'RFP Name'),
    '#default_value' => isset($scoreCardData->field_rfp_nid_for_scm['und'][0]['value'])?$scoreCardData->field_rfp_nid_for_scm['und'][0]['value']:'',
    '#disabled'=>TRUE,
    '#prefix' => '<div class="col-md-4 col-sm-4 col-xs-12"><div class="form-item clearfix">',
    '#suffix' => '</div></div>',
  );*/
  $element['main-container']['full-container']['inner-left-one']['selection-criteria'] = array(
    '#type' => 'select',
    //'#empty_option' => 'Selection Criteria',
    '#options' => array('company_based'=>'Company Based','product_based'=>'Product Based',),
    '#title' => 'Selection Criteria',
    '#attributes' => array('class'=> array('form-control','selection-criteria','border-radius-4'),'placeholder'=>'Selection Criteria'),
    '#default_value' => isset($qbnode->field_selection_criteria['und'][0]['value'])?$qbnode->field_selection_criteria['und'][0]['value']:'',
    '#prefix' => '<div class="clearfix"><div class="pull-left"><h4>Question Builder</h4></div><div class="pull-right">',
    '#suffix' => '</div></div>',
  );
  /*$element['qb-node'] = array(
    '#type' => 'hidden',    
    '#attributes' => array('class'=> array('question-builder-node')),    
    '#default_value' => isset($defaultValues['qb-node'])?$defaultValues['qb-node']:'',
  );*/
  /*$element['main-container']['full-container']['inner-left-one']['scorecard-title-end'] = array(
    '#type' => 'markup',
    '#markup' => '</div></div>',
  );*/


  $element['main-container']['full-container']['inner-left-one']['question-outer-list'] = array(
    '#type'    => 'container',
    '#process' => array('question_builder_category_question_process'),
    //'#theme'   => 'question_builder_category_process_theme',
    '#prefix' => '<div id="question-outer-listing">',
    '#suffix' => '</div>',
  );
  $qbcategory_defaultvalue = array();

  /*$query = db_select('m6connect_scm_category_setting','cat');
  $query->fields('cat', array('id','title'));
  $query->condition('cat.type','scorecard','=');
  $query->condition('cat.nid',$company->nid,'=');*/
  $qbcatetory_list = scm_scorecard_category_setting(); 

  if(isset($qbnode->field_question_builder_category['und']) && !empty($qbnode->field_question_builder_category['und'])){
     foreach ($qbnode->field_question_builder_category['und'] as $key => $value) {
      $qbcategory_defaultvalue[] =$value['value'];
    }
  }

  $element['main-container']['full-container']['inner-left-one']['select_category_ac'] = array(
    // '#type' => 'textfield',
    // '#autocomplete_path' => 'getcategory/scorecard/autocomplete',
    '#type' => 'select',    
    '#options' => $qbcatetory_list,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#attributes' => array('class'=>array('qb-selectcategory1 border-radius-4'),'placeholder'=>'Select Category'),  
    '#default_value' => $qbcategory_defaultvalue,  
    '#ajax' => array(
      'callback' => 'select_category_data_callback',
      'wrapper'  => 'question-outer-listing',      
      'effect'   => 'fade',
      // 'method'   => 'replace',
      // 'event'    => 'blur',
    ),
    '#prefix' => '<div class="clearfix well well-large hidden"><div class="col-md-6 col-sm-6 col-xs-12"><div class="form-item clearfix">',
    '#suffix' => '</div></div></div>',  
  );  


  return $element;
}



function question_builder_category_question_process($element, &$form_state) {  
  global $company, $$base_url;
  $path_to_theme = drupal_get_path('theme', 'm6connect');

  $qbcatetory_list = scm_scorecard_category_setting(); 
  //$element['#attributes']['class'] = array( 'well' ,'well-large');
  $defaultrow = array('default','default-no-cat');
  $defaultAdd = array();
  $categorySectonRemove = '';
  foreach ($form_state['question_count0'] as $key => $uniqid) { 
    if(!in_array($key, $defaultrow)){
      $defaultAdd[] = $key;
      $categorySectonRemove = '<div class="pull-right padding-10"><i qcselect='.$key.' class="fa fa-trash-o unselect-current-cat" aria-hidden="true" style="cursor: pointer;"></i></div>';
    }
  }
    foreach ($form_state['question_count0'] as $key => $uniqid) { 
      //if(!in_array($key, $defaultrow)){  
        
      //}
/*      $query1 = db_select('m6connect_scm_category_setting','cat');    
      $query1->fields('cat', array('title')); 
      $query1->condition('cat.id',$key,'=');
      $query1->condition('cat.type','scorecard','=');
      $query1->condition('cat.nid',$company->nid,'=');
      $catobj = $query1->execute()->fetchColumn(0);*/
      
      $element['main-container0'][$key] = array(
        '#type'    => 'container',       
        '#attributes'=> array('class'=>array('scm-bg')),
        //'#prefix' => '<div id="question-listing-rendar-'.$key.'-'.$uniqid.'">',
        '#prefix' => '<div id="question-listing-rendar-'.$key.'">',
        '#suffix' => '</div>',
      );
      $categorySectonRemove = (is_numeric($key)?'<div class="pull-right padding-10"><i qcselect='.$key.' class="fa fa-trash-o unselect-current-cat" aria-hidden="true" style="cursor: pointer;"></i></div>':'');

      $cmp_img = $$base_url . '/' . $path_to_theme . '/images/scorecard_company_icon_small.png';

      $element['main-container0'][$key]['category_select'] = array(
        '#type' => 'select',        
        '#options' => $qbcatetory_list,
        '#attributes'=> array('qcselect' => $key, 'qdefaultadd' => $defaultAdd, 'class' => array('border-radius-4 qbuilder-category-select', 'selected-category-' . $key), 'style' => 'width:400px; padding-left:30px;margin-left:10px;'),
        '#default_value' => $key,
        '#empty_option' => '- Select Category - ',
        '#parents' => array('qbuildercategory', $key, $uniqid, 'category_select'),
        '#prefix' => '<div class="clearfix purple-image"><div class="pull-left"><div class="display-inline-block select-product-display-image img-align-with-select"><img src="' . $cmp_img . '"></div><div class="display-inline-block">',
        '#suffix' => '</div></div>'.$categorySectonRemove.'</div>',
      );

      if(!in_array($key, $defaultrow)){
        
      
      /*$element['main-container0'][$key]['category_change'] = array(
        '#type' => 'select',        
        '#options' => $qbcatetory_list,
        '#default_value' => $key,
        //'#disabled' => TRUE,      
        //'#attributes'=> array('class'=>array( 'well' ,'well-large')),
        '#parents' => array('qbuildercategory', $key, $uniqid, 'category_change'),
        //'#submit' => 'select_category_change_section_submit',
        '#ajax' => array(
          'callback' => 'select_category_change_section_callback',
          'wrapper'  => 'question-listing-rendar-'.$key,      
          'effect'   => 'fade',
          // 'method'   => 'replace',
          // 'event'    => 'blur',
        ),
        '#prefix' => '<div class="row"><div class="col-md-4">',
        '#suffix' => '</div></div>',
      );*/
      $element['main-container0'][$key]['main-container'] = array(
        '#type'    => 'container',
        // '#process' => array('question_builder_category_process'),
        '#theme'   => 'question_builder_category_process_theme',
        //'#prefix' => '<div id="question-listing-rendar-'.$key.'-'.$uniqid.'">',
        //'#suffix' => '</div>',
      );
      
      $question_default_values = $form_state['question_default_values'];
      $qbcount = 1;            
      $element['main-container0'][$key]['main-container']['#storage0'] = $form_state['question_count0'];  
      $element['main-container0'][$key]['main-container']['#storage'] = $form_state['question_count']; 
     /* $questionCount = count($form_state['question_count'][$key]);
      for($i = $questionCount+1; $i<= 50; $i++) {
        $form_state['question_count'][$key][] = uniqid();
      }*/
      foreach ($form_state['question_count'][$key] as $key1 => $value) {
        $element['main-container0'][$key]['main-container']['#directCat1'] = $key;
        $element['main-container0'][$key]['main-container']['qid'][$value] = array(
          '#type' => 'value',
          '#default_value' => !empty($question_default_values[$key][$value]['qid']) ? $question_default_values[$key][$value]['qid'] : 0,
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'qid'),
        );
        $element['main-container0'][$key]['main-container']['question'][$value] = array(
          '#type' => 'textfield',
          '#attributes'=> array('class'=>array('qbuilder-question','cleartext')),
          '#default_value' => !empty($question_default_values[$key][$value]['question']) ? $question_default_values[$key][$value]['question'] : '',
          // '#field_prefix' => $qbcount,
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'question'),          
        );
        
        $element['main-container0'][$key]['main-container']['weight'][$value] = array(
          '#type' => 'textfield',
          '#default_value' => !empty($question_default_values[$key][$value]['weight']) ? $question_default_values[$key][$value]['weight'] : 0,      
          //'#prefix' => '<div class="col-md-2 padding-5 margin-bottom-4">',
          //'#suffix' => '</div>',
          '#attributes'=> array('readonly'=>'readonly','class'=>array('qbuilder-weight','clearnumber')),
          '#field_prefix' => '<i class="fa fa-minus item-decrease item-decrease-item" aria-hidden="true"></i>',
          '#field_suffix' => '<i class="fa fa-plus item-increase-item item-increase-weight" aria-hidden="true"></i>',
          '#maxlength' => 2,
          //'#disabled' => TRUE,
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'weight'),
        );
        
        $element['main-container0'][$key]['main-container']['rating'][$value] = array(
          '#type' => 'textfield',      
          '#default_value' => !empty($question_default_values[$key][$value]['rating']) ? $question_default_values[$key][$value]['rating'] : 0,
          //'#prefix' => '<div class="col-md-2 padding-5 margin-bottom-4">',
          //'#suffix' =>    '</div>',
          '#attributes'=> array('readonly'=>'readonly','class'=>array('qbuilder-rating','clearnumber')),
          '#field_prefix' => '<i class="fa fa-minus item-decrease-item" aria-hidden="true"></i>',
          '#field_suffix' => '<i class="fa fa-plus  item-increase-item " aria-hidden="true"></i>',
          '#maxlength' => 2,
          //'#disabled' => TRUE,
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'rating'),
          );
        $element['main-container0'][$key]['main-container']['score'][$value] = array(
          '#type' => 'textfield',      
          '#default_value' => !empty($question_default_values[$key][$value]['score']) ? $question_default_values[$key][$value]['score'] : 0,
          '#attributes'=> array('readonly'=>'readonly','class'=>array('qbuilder-score','clearnumber')),
          //'#prefix' => '<div class="col-md-2 padding-5 margin-bottom-4">',
          //'#suffix' =>    '</div>',
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'score'),
          );
        $element['main-container0'][$key]['main-container']['comments'][$value] = array(
          '#type' => 'textfield',      
          '#default_value' => !empty($question_default_values[$key][$value]['comments']) ? $question_default_values[$key][$value]['comments'] : '',       
          //'#prefix' => '<div class="col-md-2 padding-5">',
          //'#suffix' =>  '</div>',
          '#attributes'=> array('readonly'=>'readonly','class'=>array('qbuilder-comments','cleartext')),
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'comments'),
          
          '#suffix' => '<div class="clearfix"><div>'.l('<i class="fa fa-trash-o" aria-hidden="true"></i>','javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('remove-add-row-item-link-new')))).'</div></div>',
        );
        $element['main-container0'][$key]['main-container']['remove'][$value] = array(
         /* '#type' => 'button',
          '#value' => 'remove',
          '#name' => 'qbuilder_count_row_remove',         
          "#limit_validation_errors" => array(),
          '#attributes'=> array('qbcatkey'=>$key,'qbunikey1'=>$uniqid,'qbunikey2'=>$value,'class'=>array('qbuilderremove-'.$key.'-'.$uniqid ,'remove-add-row-item', 'workflow-remove-submit','hidden')),*/
          /*'#submit'=> array('remove_qbuilder_count_submit_handler'),
          '#ajax' => array(
            'callback' => 'remove_qbuilder_count_row_callback',
            'wrapper' => 'category-outer-listing',
            'method' => 'replace',
            'effect' => 'fade',
            'progress' => array('type'=> 'throbber', 'message'=> NULL),
          ),*/
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'remove'),
          '#prefix' => '<div class="clearfix hide"><div>'.l('<i class="fa fa-trash-o" aria-hidden="true"></i>','javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('remove-add-row-item-link')))),
          '#suffix' => '</div></div>',
        );
        //$getCls = !empty($question_default_values[$key][$value]['question']) ? 'HasDefault' : 'NonDefault';
        $element['main-container0'][$key]['main-container']['hasDefault'][$value] = array(
          '#type' => 'hidden',      
          '#default_value' => $question_default_values[$key][$value]['hasDefault'],//!empty($question_default_values[$key][$value]['question']) ? 'HasDefault' : 'NonDefault',
          '#attributes' => array('class' => array($question_default_values[$key][$value]['hasDefault'])),
          //'#prefix' => '<div class="col-md-2 padding-5">',
          //'#suffix' =>  '</div>',
          '#parents' => array('qbuilder', $key, $uniqid, $value, 'hasDefault'),
        );
        
        $qbcount++;
      }
      $element['main-container0'][$key]['main-container']['qbuilder_count_add_new_row'] = array(
        '#type' => 'submit',
        '#value' => '+ Add Question',
        '#name' => 'qbuilder_count_add_new_row',
        '#attributes'=> array('class'=>array('qbuilderaddnew-'.$key.'-'.$uniqid ,'qbuilder-count-add-new-row-button','hidden'),'title'=>'Add Question'),
        "#limit_validation_errors" => array(),
        '#parents' => array('qbuilder', $key, $uniqid, 'addnew'),
        '#prefix' => '<div class="text-left padding-10"><div>' . l('+ Add Question','javascript:void(0);',array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('question-add-row-item-link')))),
          '#suffix' => '</div></div>',
      );
    }
    }
  // dpm($form_state,'$form_state2');
  return $element;
}



 function select_category_data_callback($form, &$form_state) {
  return $form['main-container-2']['main-container']['full-container']['inner-left-one']['question-outer-list'];
}


function select_category_change_section_callback($form, &$form_state) {
  //dpm($form_state,'form_state new cat change');
  $catid = $form_state['triggering_element']['#value'];
  $oldcatid = $form_state['triggering_element']['#default_value'];
  /* $_SESSION['question_newcatchange'] =$form_state;

        $_SESSION['question_newcatchange2'] =$form_state;
        $form_state['rebuild'] = TRUE;
        $_SESSION['question_newcatchange3'] =$form_state;*/
    
  return $form;
}

/*function select_category_change_section_submit($form, &$form_state) {
  global $company;
  //$_SESSION['question_newcatchange1'] =$form_state;
  $defaultAddnewRow = 50;
  $catid = $form_state['triggering_element']['#value'];
  $form_state['question_count0'][$catid] = array();
  $form_state['question_count'][$catid] = array();
  $form_state['question_default_values'][$catid] = array();
  $ListingDefault = db_select('m6connect_scm_scorecard_question','squ');    
  $ListingDefault->fields('squ');    
  $ListingDefault->condition('squ.category_id',$catid,'=');
  $ListingDefault->condition('squ.company_nid',$company->nid,'=');
  $questionListingDefault = $ListingDefault->execute()->fetchAll();
  if(isset($questionListing) && !empty($questionListing)){
          foreach($questionListing as $qkey=>$qvalue){        
            $tempIdentifer1 = uniqid();
            $form_state['question_count'][$catid][]  = $tempIdentifer1;
            
            $form_state['question_default_values'][$catid][$tempIdentifer1] = array(
              'question' => $qvalue->question,
              'weight' => $qvalue->weight ,
              'rating' => $qvalue->rating,
              'score' => $qvalue->score,
              'comments' => $qvalue->comments,
              'hasDefault' => 'HasDefault',
            );               
          }
          $questionCount = count($form_state['question_count'][$catid]);
          for($i = $questionCount+1; $i<= $defaultAddnewRow; $i++) {
            $tempIdentifer3 = uniqid();
            $form_state['question_count'][$catid][] = $tempIdentifer3;
            $form_state['question_default_values'][$catid][$catid][$tempIdentifer3] = array(
              'question' => '',
              'weight' => 0,
              'rating' => 0,
              'score' => 0,
              'comments' => '',
              'hasDefault' => 'NonDefault',
            );
          }
        }else{   
          for($i = 1; $i<= $defaultAddnewRow; $i++) {
            $tempIdentifer2 = uniqid();
            $form_state['question_count'][$catid][] = $tempIdentifer2;
            $form_state['question_default_values'][$catid][$catid][$tempIdentifer2] = array(
              'question' => '',
              'weight' => 0,
              'rating' => 0,
              'score' => 0,
              'comments' => '',
              'hasDefault' => 'NonDefault',
            );
          }
        }
        //$_SESSION['question_newcatchange2'] =$form_state;
        //$form_state['rebuild'] = TRUE;
        //$_SESSION['question_newcatchange3'] =$form_state;
}*/




function theme_question_builder_category_process_theme($variables) {
  $element = $variables['form'];    
  $storage0 = $element['#storage0']; 
  $storage = $element['#storage']; 
  //dpm($element, 'element theme process');
  $storageQuestion = $element['question'];     
  $output = '';
  $header = array('Question', 'Weight', 'Rating','Score', 'Comments');
  $rowNo = 1;
    foreach ($storageQuestion as $uniqid => $uniqid1) {
      if(in_array($uniqid,$storage[$element['#directCat1']])){
        $rows[] = array(
        'data'=> array(          
          array('data'=>drupal_render($element['qid'][$uniqid]),'class'=> array('hidden')),
          array('data'=>drupal_render($element['question'][$uniqid]).drupal_render($element['remove'][$uniqid]),'class'=> array('col-md-4','trow-inline-link')),
          //array('data'=>drupal_render(),'class'=> array('col-md-1')),
          array('data'=>drupal_render($element['weight'][$uniqid]),'class'=> array('col-md-1','trow-inline')),
          array('data'=>drupal_render($element['rating'][$uniqid]),'class'=> array('col-md-1','trow-inline','trow-inline-color')),
          array('data'=>drupal_render($element['score'][$uniqid]),'class'=> array('col-md-1')),
          array('data'=>drupal_render($element['comments'][$uniqid]),'class'=> array('col-md-4','trow-inline-link-new')),
          array('data'=>drupal_render($element['hasDefault'][$uniqid]),'class'=> array('default','hidden')),
        ),     
        'id' => array('addquestionbuildertablelist-'.$rowNo.'-'.$element['#directCat1'].'-'.$uniqid), 
        'class'=>array($element['hasDefault'][$uniqid]['#default_value']),
        );
        $rowNo++;
      }
    }
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes'=> array('id'=>'qbtable-'.$element['#directCat1'],'class'=> array('table','table-hover','qbuilder-table'))));
  $output .= drupal_render_children($element);
  return $output;
}

function scm_questionbuilder_submit($form, &$form_state) {  
  // dpm($form_state,'$form_state form save');
  //pre($form_state,1);
  global $user,$company;
  $values = $form_state['values'];
  $hsaCatQue = FALSE;
  if(isset($values['question_builder_nid']) && !empty($values['question_builder_nid'])){
    $qbnode = node_load($values['question_builder_nid']);
    drupal_set_message('Question Builder has been updated.');
  }
  else{
    $qbnode = _node_creation_call('question_builder','qusetion-'.time());
    drupal_set_message('Question Builder has been created.');
  }
  //$qbnode->field_select_entity['und'][0]['value'] = $values['entity-name']; 
  $qbnode->field_qb_scorecard_referance['und'][0]['target_id'] = $values['active_scorecard_nid'];
  $qbnode->field_select_project['und'][0]['value'] = $values['project-name']; 
  $qbnode->field_select_rfp['und'][0]['value'] = $values['rfp-name']; 
  $qbnode->field_selection_criteria['und'][0]['value'] = $values['selection-criteria'];
  $qbnode->field_question_builder_category = '';
  if(isset($values['select_category_ac']) && !empty($values['select_category_ac'])){   
    foreach($values['select_category_ac'] as $catvalue){
      $qbnode->field_question_builder_category['und'][]['value'] = $catvalue;
    }    
  }else{
    $qbnode->field_question_builder_category = '';
    $delrow = db_select('m6connect_qbuilder_data','qbdata');
    //$delrow->condition('qbdata.uid',$user->uid);
    $delrow->condition('qbdata.company_nid', $company->nid);
    $delrow->condition('qbdata.scorecard_nid', $values['active_scorecard_nid']);
    $delrow->fields('qbdata',array('id'));
    $oldcatkey = $delrow->execute()->fetchCol();
    // dpm($oldcatkey,'$oldcatkey');
    if(isset($oldcatkey) && !empty($oldcatkey)){
      db_delete('m6connect_qbuilder_data')
      ->condition('company_nid', $company->nid)
      ->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('id', $oldcatkey,'IN')
      ->execute();
      db_delete('m6connect_qbuilder_rating')
      //->condition('company_nid', $company->nid)
      //->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('qid', $oldcatkey,'IN')
      ->execute();
      db_delete('m6connect_qbuilder_comments')
      //->condition('company_nid', $company->nid)
      //->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('qid', $oldcatkey,'IN')
      ->execute();
    }
  }
  if(!empty($values['question_builder_nid'])){
    $hget_qcat = db_select('m6connect_qbuilder_data','qbd');
    $hget_qcat->fields('qbd',array('id','category_id'));
    $hget_qcat->condition('qbd.company_nid',$company->nid);
    $hget_qcat->condition('qbd.scorecard_nid',$values['active_scorecard_nid']);
    $hget_qcat->condition('qbd.qbuilder_nid',$values['question_builder_nid']);
    $get_qcat =  $hget_qcat->execute()->fetchAllKeyed();
    if(!empty($get_qcat)){
      $finaldel= array_diff($get_qcat,$values['select_category_ac']);      
      if(!empty($finaldel)){
        $finaldelKeys = array_keys($finaldel);
        db_delete('m6connect_qbuilder_data')
        ->condition('company_nid', $company->nid)
        ->condition('scorecard_nid', $values['active_scorecard_nid'])
        ->condition('id', $finaldelKeys,'IN')
        ->execute();
        db_delete('m6connect_qbuilder_rating')        
        ->condition('qid', $finaldelKeys,'IN')
        ->execute();
        db_delete('m6connect_qbuilder_comments')        
        ->condition('qid', $finaldelKeys,'IN')
        ->execute();
      }
    }    
  }











  node_save($qbnode);

  if(isset($form_state['question_count0'],$values['qbuilder']) && !empty($form_state['question_count0'])&& !empty($values['qbuilder'])){
    $hsaCatQue = TRUE;
    //delete old question row from category in table 

    /*$delrow = db_select('m6connect_qbuilder_data','qbdata');
    //$delrow->condition('qbdata.uid',$user->uid);
    $delrow->condition('qbdata.company_nid', $company->nid);
    $delrow->condition('qbdata.scorecard_nid', $values['active_scorecard_nid']);
    $delrow->fields('qbdata',array('id'));
    $oldcatkey = $delrow->execute()->fetchCol();
    if(isset($oldcatkey) && !empty($oldcatkey)){
      db_delete('m6connect_qbuilder_data')
      ->condition('company_nid', $company->nid)
      ->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('id', $oldcatkey,'IN')
      ->execute();
      db_delete('m6connect_qbuilder_rating')
      //->condition('company_nid', $company->nid)
      //->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('qid', $oldcatkey,'IN')
      ->execute();
      db_delete('m6connect_qbuilder_comments')
      //->condition('company_nid', $company->nid)
      //->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('qid', $oldcatkey,'IN')
      ->execute();
    }*/
    //add new question from category id in table
    foreach($form_state['question_count0'] as $catkey=>$firstunikey){
      $qbcount = 0;
      foreach ($values['qbuilder'][$catkey][$firstunikey] as $secondkey => $univalue) {
        if($secondkey != 'addnew'){
          if($univalue['hasDefault'] =='HasDefault'){            
            if(!empty($univalue['question'])){             
              
              db_merge('m6connect_qbuilder_data')
              ->key(array('id' =>$univalue['qid']))
              ->fields(array(
                'uid' => $user->uid,
                'company_nid' => $company->nid,
                'scorecard_nid' => $values['active_scorecard_nid'],
                'qbuilder_nid' => $qbnode->nid,
                'category_id' => $catkey,
                'delta' => $qbcount,
                'question' => $univalue['question'],
                'weight' => $univalue['weight'],
                'rating' => 0,
                'score' => 0,
                'comments' => '',
                'status' => 1,
                'timestamp' => time(),
              ))
              ->execute();
              $qbcount++;
            }
          }
          else if($univalue['hasDefault'] =='NonDefault' && $univalue['qid'] != '0'){
            //drup_msg('else no');
            //drup_msg($univalue['qid']);
            db_delete('m6connect_qbuilder_data')
            ->condition('company_nid', $company->nid)
            ->condition('scorecard_nid', $values['active_scorecard_nid'])
            ->condition('id', $univalue['qid'],'=')
            ->execute();
          }
        }
      }
    }

  }


   //$_SESSION['question_form_state'] = $form_state;
   
}
function scm_questionbuilder_submit_callback($form, &$form_state) { //dpm($form_state,'$form_state');
  if (empty($form_state['values']['select_category_ac'])) {
    form_set_error('', t('Please select at least one category and question to proceed!'));  
    return $form;
  }
  $commands = array();
  global $user,$company;

  $values = $form_state['values'];
  $hsaCatQue = FALSE;
  if(isset($values['question_builder_nid']) && !empty($values['question_builder_nid'])){
    $qbnode = node_load($values['question_builder_nid']);
    //drupal_set_message('Question Builder has been updated.');
  }
  else{
    $qbnode = _node_creation_call('question_builder','qusetion-'.time());
    //drupal_set_message('Question Builder has been created.');
  }
  //$qbnode->field_select_entity['und'][0]['value'] = $values['entity-name']; 
  $qbnode->field_qb_scorecard_referance['und'][0]['target_id'] = $values['active_scorecard_nid'];
  $qbnode->field_select_project['und'][0]['value'] = $values['project-name']; 
  $qbnode->field_select_rfp['und'][0]['value'] = $values['rfp-name']; 
  $qbnode->field_selection_criteria['und'][0]['value'] = $values['selection-criteria'];
  $qbnode->field_question_builder_category = '';
  if(isset($values['select_category_ac']) && !empty($values['select_category_ac'])){   
    foreach($values['select_category_ac'] as $catvalue){
      $qbnode->field_question_builder_category['und'][]['value'] = $catvalue;
    }    
  }else{
    $qbnode->field_question_builder_category = '';
    $delrow = db_select('m6connect_qbuilder_data','qbdata');
    //$delrow->condition('qbdata.uid',$user->uid);
    $delrow->condition('qbdata.company_nid', $company->nid);
    $delrow->condition('qbdata.scorecard_nid', $values['active_scorecard_nid']);
    $delrow->fields('qbdata',array('id'));
    $oldcatkey = $delrow->execute()->fetchCol();
    //dpm($oldcatkey,'$oldcatkey');
    if(isset($oldcatkey) && !empty($oldcatkey)){
      db_delete('m6connect_qbuilder_data')
      ->condition('company_nid', $company->nid)
      ->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('id', $oldcatkey,'IN')
      ->execute();
      db_delete('m6connect_qbuilder_rating')
      //->condition('company_nid', $company->nid)
      //->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('qid', $oldcatkey,'IN')
      ->execute();
      db_delete('m6connect_qbuilder_comments')
      //->condition('company_nid', $company->nid)
      //->condition('scorecard_nid', $values['active_scorecard_nid'])
      ->condition('qid', $oldcatkey,'IN')
      ->execute();
    }
  }

  if(!empty($values['question_builder_nid'])){
    $hget_qcat = db_select('m6connect_qbuilder_data','qbd');
    $hget_qcat->fields('qbd',array('id','category_id'));
    $hget_qcat->condition('qbd.company_nid',$company->nid);
    $hget_qcat->condition('qbd.scorecard_nid',$values['active_scorecard_nid']);
    $hget_qcat->condition('qbd.qbuilder_nid',$values['question_builder_nid']);
    $get_qcat =  $hget_qcat->execute()->fetchAllKeyed();
    if(!empty($get_qcat)){
      $finaldel= array_diff($get_qcat,$values['select_category_ac']);      
      if(!empty($finaldel)){
        $finaldelKeys = array_keys($finaldel);
        db_delete('m6connect_qbuilder_data')
        ->condition('company_nid', $company->nid)
        ->condition('scorecard_nid', $values['active_scorecard_nid'])
        ->condition('id', $finaldelKeys,'IN')
        ->execute();
        db_delete('m6connect_qbuilder_rating')        
        ->condition('qid', $finaldelKeys,'IN')
        ->execute();
        db_delete('m6connect_qbuilder_comments')        
        ->condition('qid', $finaldelKeys,'IN')
        ->execute();
      }
    }    
  }
  node_save($qbnode);

  if(isset($form_state['question_count0'],$values['qbuilder']) && !empty($form_state['question_count0'])&& !empty($values['qbuilder'])){   
    $hsaCatQue =TRUE;
    //add new question from category id in table
    foreach($form_state['question_count0'] as $catkey=>$firstunikey){
      $qbcount = 0;
      foreach ($values['qbuilder'][$catkey][$firstunikey] as $secondkey => $univalue) {
        if($secondkey != 'addnew'){
          if($univalue['hasDefault'] =='HasDefault'){            
            if(!empty($univalue['question'])){             
              
              db_merge('m6connect_qbuilder_data')
              ->key(array('id' =>$univalue['qid']))
              ->fields(array(
                'uid' => $user->uid,
                'company_nid' => $company->nid,
                'scorecard_nid' => $values['active_scorecard_nid'],
                'qbuilder_nid' => $qbnode->nid,
                'category_id' => $catkey,
                'delta' => $qbcount,
                'question' => $univalue['question'],
                'weight' => $univalue['weight'],
                'rating' => 0,
                'score' => 0,
                'comments' => '',
                'status' => 1,
                'timestamp' => time(),
              ))
              ->execute();
              $qbcount++;
            }
          }
          else if($univalue['hasDefault'] =='NonDefault' && $univalue['qid'] != '0'){
            //drup_msg('else no');
            //drup_msg($univalue['qid']);
            db_delete('m6connect_qbuilder_data')
            ->condition('company_nid', $company->nid)
            ->condition('scorecard_nid', $values['active_scorecard_nid'])
            ->condition('id', $univalue['qid'],'=')
            ->execute();
          }
        }
      }
    }

    if(isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == 'Save and Share Update' && $hsaCatQue){
     $commands[] = ajax_command_invoke(".sharebtnhidden", 'trigger',array('click'));
     /* $squery =  db_select('field_data_field_scorecard_reference','sref');  
      $squery->leftjoin('field_data_field_share_with_user','swu','swu.entity_id=sref.entity_id');
      $squery->fields('swu',array('field_share_with_user_value'));
      $squery->condition('sref.field_scorecard_reference_nid',$values['active_scorecard_nid']);
      $shareusers =  $squery->execute()->fetchCol();

      //dpm($shareusers);
      foreach($shareusers as $shkey=>$shuser){
        if (db_table_exists('m6connect_notification')) {
          $m6connect_notification = array(
            'type'         => 'scm',
            'event'        => 'scorecard_share_update',
            'entity_id'    => $values['active_scorecard_nid'] ,
            'company_nid'  => $company->nid,
            'message'      => NULL,
            'request_from' => $user->uid,
            'request_to'   => $shuser,
            'status'       => 1,
            'timestamp'    => time(),
          );
          entity_save('m6connect_notification', (object) $m6connect_notification);
        }
      }*/
    }
  }
  if (empty($form_state['values']['select_category_ac'])) {
    form_set_error('', t('Please select at least one category and question to proceed!'));
  }else if (!empty($form_state['values']['select_category_ac'])) {
    $commands[] = ajax_command_invoke(".sharebtnhidden", 'trigger',array('click'));
    
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function scm_questionbuilder_validate($form, &$form_state) {  
  if (empty($form_state['values']['select_category_ac'])) {
    form_set_error('', t('Please select at least one category and question to proceed!'));
  }
}