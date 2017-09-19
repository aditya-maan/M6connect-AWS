<?php
function scm_my_reporting_content() {    
  /*global $user,$company;  
  $query = db_select('m6connect_scm_casemanager_label_management','cmlm');
  $query->fields('cmlm',array('value'));
  $query->condition('cmlm.nid',$company->nid);
  $caselabel = $query->execute()->fetchColumn(0); 
  $_SESSION['scm_label_object'] = ''; 
  $_SESSION['scm_label_object'] = (isset($caselabel) && !empty($caselabel)?unserialize($caselabel):'');
  $elements['scm-reporting-outer-menu']= array(
    '#markup' => drupal_render(drupal_get_form('scm_reporting_top_form')),
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );*/
  $elements['prgram-scm-menu-items'] = array(
    //'#markup' => scm_menu_links_content(),
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',    
  );
  $elements['prgram-project-listing'] = array(
    '#markup' => '<center><h2>Coming Soon</h2></center>',
    '#prefix' => '<div class="clearfix margin-bottom-10"><div class="project-summary-listing" id="scorecard-information-listing">',
    '#suffix' => '</div></div></div>',
   );
  return $elements; 
}




function scm_reporting_top_form($form, &$form_state) {
  $getReqNodes = _getting_table_data_call('project_management');
  
  $form['prgram-scm-menu-items'] = array(
    //'#markup' => scm_menu_links_content(),
    '#markup' => scm_csemanager_main_menu_links_content(),
    '#prefix' => '<div class="clearfix scm-main-menu">',
    '#suffix' => '</div>',    
  );
  $form['scm-casemanager-menu']= array(
    '#markup' => '<ul class="list-unstyled list-inline custom-list scm-menu-links clearfix">
                    <li class="menu-item"><a href="#">Charter</a></li>
                    <li class="menu-item"><a href="#">SBAR</a></li>
                    <li class="menu-item"><a href="#">Updates</a></li>
                    <li class="menu-item"><a href="#">Reports</a></li>                    
                  </ul>',
    '#prefix' => '<div class="clearfix margin-bottom-10 csemanager-sub-menu">',
    '#suffix' => '</div>',
  );
  $form['get-scm_projects_scp'] = array(
    '#type' => 'select',
    '#options' => $getReqNodes,
    '#empty_option' => 'Select Project',
    '#default_value' => isset($_SESSION['scm_project_nid'])?array($_SESSION['scm_project_nid']=>$_SESSION['scm_project_nid']):'',
    '#attributes' => array('class'=> array('form-control get-scm_projects_scp')),
    '#ajax' => array(
      'callback'=> 'change_scm_project_scp_callback',
      'wrapper' => 'program_scm_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix"><div class="pull-right">',
    '#suffix' => '</div></div>',
  );
  /*$form['scm_casebuilder_case_name'] = array(
    '#title'=> 'Case Title',
    '#type' => 'textfield',
  '#required' => TRUE, 
    '#prefix' => '<div class="new-case-add" style="display:none"><div class="row margin-10"><div class="col-md-4">',
    '#suffix' => '</div></div>',
  );
  $form['scm_casebuilder_case_description'] = array(        
    '#type' => 'textarea',    
    '#title'=> 'Case Description',
    '#prefix' => '<div class="row margin-10"><div class="col-md-6">',
    '#suffix' => '</div></div>',
  );
 $form['submit'] = array(
  '#type' => 'submit',   
  '#value' => t('Save'),
  '#attributes' => array('class'=> array('margin-bottom-15')),
  '#ajax' => array(
      'callback' => 'casemanager_case_builder_form_submit_callback',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<a href="javascript:void(0);" class="case-builder-form-close"><input type="button" class="btn cancel-button" value="Cancel"></a>',
    '#suffix' => '</div>',
  );*/

  return $form;
}
