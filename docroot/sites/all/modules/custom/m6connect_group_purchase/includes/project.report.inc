<?php

// ====================
// End Assets Section
// ====================
// Start Reports Sction
// ====================
function program_project_reports_content(){
  $elements = array();
  $path = $_GET['q'];
  $arguments = explode('/', $path);
  $elements['project-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_modify_project_report_form', $arguments[1])),
  '#prefix' => '<div class="clearfix margin-bottom-10">',
  '#suffix' => '</div>',
  );
  return $elements;
}

function program_modify_project_report_form($form, &$form_state, $proType) {
  global $user;   
  global $company;  
  // Get project list by company
  if ($proType == 'cm') {
    $getProjectByCompany = _project_list_by_company($company->nid, 'project_management', 'cmtrue');
  }
  elseif ($proType == 'cr') {
    $getProjectByCompany = _project_list_by_company($company->nid, 'project_management', 'crtrue');
  }
  else {
    $getProjectByCompany = _project_list_by_company($company->nid, 'project_management', 'cmfalse');
  }
  //$projectListByCom = array('0' => '- None -');
  foreach($getProjectByCompany as $key => $val) {
    $projectListByCom[$key] = $val;
  }

  reset($projectListByCom);
  $default_select_value = key($projectListByCom);
  if (isset($_SESSION['ACTIVEPROJECT'])) {
    if (isset($projectListByCom[$_SESSION['ACTIVEPROJECT']])) {
      $default_select_value = $_SESSION['ACTIVEPROJECT'];
    }
  }

  drupal_add_js(drupal_get_path('module', 'm6connect_program') . '/js/m6connect_program.js');
  $form['select-project'] = array(
    '#type' => 'select',
    '#title'=> 'Choose multiple projects',
    '#options' => $projectListByCom,
    '#chosen' => TRUE,
    '#multiple' => TRUE,
    '#attributes' => array('class'=> array('project_programe_reports_sections')),
    '#ajax' => array(
      'callback'=> 'change_program_project_reports_callback',
      'wrapper' => 'project_program_reports_main_container',
      'effect' => 'fade',
    ),
    '#default_value' => $default_select_value,
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );
  $form['prgram-project-menu-items'] = array(
    '#markup' => program_project_menu_links_content(),
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );  
  $form['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="clearfix"><div id="project_program_reports_main_container" class="project-detail">',  
    '#suffix' => '</div></div>',
    '#process' => array('project_program_reports_main_container'),
  );  
  return $form;
}

function project_program_reports_main_container($element, &$form_state) { 
  $element['left-container']= array(
    '#type' => 'container',
  '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','project-details-left')),
  );  
  $element['right-container']= array(
    '#type' => 'container',
  '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','project-details-right')),
  );
  $element['left-container']['project-title'] = array(
    '#markup' => generate_report_links_callback(),
  '#prefix' => '<div id="project-report-links-pdf">',
  '#suffix' => '</div>',
  );
  $element['right-container']['project-description'] = array(
    '#markup' => '<iframe src="" style="display:none;"></iframe>',
  '#prefix' => '<div id="project-pdf-data-render-section">',
  '#suffix' => '</div>',
  );  
  return $element;
}
function change_program_project_reports_callback($form,&$form_state) {
  global $company;  
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  // drup_msg($triggeringElement['#value']);
  if(!empty($triggeringElement['#value']) && $triggeringElement['#value'] != 0){   
  $commands[] = ajax_command_html("#project-report-links-pdf", generate_report_links_callback($triggeringElement['#value']));
  $commands[] = ajax_command_html("#project-pdf-data-render-section", '');
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function load_project_pdf_data_callback($type,$proId, $ajax = NULL) {    
  ctools_include('ajax');
  $commands = array();
  $commands[] = ajax_command_html('#project-pdf-data-render-section', '<div class="report-loader2 text-center" style="position: absolute; width: 100%; top:134px;"><img src="/sites/all/themes/m6connect/images/page-loading.gif" style="width:125px;"></div><iframe src="/load-project-pdf-data/'.$type.'/'.$proId.'?proids='.$_GET['proids'].'" height="600" width="100%" onload="hideProgress()"></iframe>');  
  print ajax_render($commands);
  exit;   
}

function project_programe_report_pdf($type, $proid) { 
  global $user, $base_url, $base_path;
  $query_parameters = array();
  $query_parameters = drupal_get_query_parameters();
  if(is_numeric(arg(2))) { $costProId = array(arg(2)); } else { $costProId = explode(',',$query_parameters['proids']); }
  $node = node_load($costProId[0]);
  if($type == 'monthly') { $reportTitle = 'Monthly Project Report'; } 
  else if($type == 'costsummary') { $reportTitle = 'Project Cost Summary Report'; }
  else if($type == 'costdetail') { $reportTitle = 'Project Cost Detail Report'; }
  else if($type == 'commitment') { $reportTitle = 'Project Commitment Report'; }
  else if($type == 'safety') { $reportTitle = 'Project Safety Report'; }  
  else if($type == 'estimate') { $reportTitle = 'Budget Estimate Report'; }   
  else if($type == 'asset') { $reportTitle = 'Project Assets Report'; }
  else if($type == 'spending-forecast') { $reportTitle = 'Project Spending Forecast'; }
  $projectNumber = $node->field_project_mgmt_number['und'][0]['value'];
  $projectName = $node->title;
  $getCompanyData = node_load($node->og_group_ref['und'][0]['target_id']);  
  if(isset($getCompanyData->field_logo['und'])) {
    $fileObj = file_load($getCompanyData->field_logo['und'][0]['fid']);
  $objFile = file_copy($fileObj, $destination = 'public://'. $filname, $replace = FILE_EXISTS_RENAME);
  $objFile->status = 0;
  file_save($objFile);
  $companyLogo = '<img src="'.image_style_url('thumbnail', $objFile->uri).'" height="85" width="85">';
  }
  else {
    $companyLogo = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" height="85" width="85">';
  }   
  $content = theme('project_program_report_content_pdf');
  include_once(libraries_get_path('mpdf') . '/mpdf.php'); 
  $mpdf = new mPDF('c', 'A4-L');
  
  $mpdf->SetHTMLHeader('<div class="page_header" style="padding:10px; background: #eee;"><table style="margin:0; width:100%;"><tr><td width="150">'.$companyLogo.'</td><td align="center" width="300" style="vertical-align:top;"><h2>'.ucwords($reportTitle).'</h2><h2>&nbsp;</h2></td><td width="150" align="right" style="vertical-align:bottom"><p style="margin:0;">&nbsp;</p></td></tr></table></div>');
      
  $mpdf->SetHTMLFooter('<div class="page_footer" style="float:left; width:100%;"><div style="float:left; width:100%;"><hr style="height:1px; border:none; border-bottom:1px solid #CCC;"></div><div style="float:left; width:100%; clear:both;"><div style="float:left; width:33.33%; text-align:left;"><img src="/sites/all/themes/m6connect/images/bidder_report_footer.png" alt="res" width="100" /></div><div style="float:left; width:33.33%; text-align:center;">Page {PAGENO} of {nb}</div><div style="float:left; width:33.33%; text-align:right;">'.date("l, F d, Y").'</div></div></div>');
  $mpdf->setAutoTopMargin = 'stretch';  
  $mpdf->setAutoBottomMargin = 'stretch'; 
  $mpdf->WriteHTML($content);
  $file_content = $mpdf->Output('report.pdf', 'I');
  //print $content;
} 

function generate_report_links_callback($proID) {  
  global $company;
  $project = implode(',',$proID);
  $tt = count(explode(',',$project));
  
  $content = '<div class="text-left">';
 // $content .= drupal_render(drupal_get_form('get_project_by_company_form'));
  if(is_array($proID)) {
  if($tt > 1) {
      $content .= '<p><a href="/load-project-pdf/monthly/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Monthly Report test</a> 
            <a href="/load-project-pdf/monthly/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
            
         </p>            
         <p><a href="/load-project-pdf/costsummary/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Cost Summary</a>
          <a href="/load-project-pdf/costsummary/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
          
           </p>
         <p><a href="/load-project-pdf/costdetail/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Cost Details</a>
          <a href="/load-project-pdf/costdetail/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
          <a href="/project-report-excel/costdetail/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/commitment/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Commitment</a>
           <a href="/load-project-pdf/commitment/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/commitment/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
          </p>
        <p><a href="/load-project-pdf/safety/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Safety Report</a>
           <a href="/load-project-pdf/safety/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/safety/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/estimate/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Budget Estimate</a>
           <a href="/load-project-pdf/estimate/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/estimate/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/asset/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Asset Reports</a>
           <a href="/load-project-pdf/asset/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/asset/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/spending-forecast/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Spending Forecasts</a>
           <a href="/load-project-pdf/spending-forecast/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/spending-forecast/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        </div>';
    }else{  
     $content .= '<p><a href="/load-project-pdf/monthly/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Monthly Report test</a> 
            <a href="/load-project-pdf/monthly/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
            <a href="/project-report-excel/monthly/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
         </p>            
         <p><a href="/load-project-pdf/costsummary/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Cost Summary</a>
          <a href="/load-project-pdf/costsummary/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
          <a href="/project-report-excel/costsummary/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
           </p>
         <p><a href="/load-project-pdf/costdetail/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Cost Details</a>
          <a href="/load-project-pdf/costdetail/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
          <a href="/project-report-excel/costdetail/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/commitment/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Commitment</a>
           <a href="/load-project-pdf/commitment/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/commitment/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
          </p>
        <p><a href="/load-project-pdf/safety/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Safety Report</a>
           <a href="/load-project-pdf/estimate/safety/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/safety/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/estimate/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Budget Estimate</a>
           <a href="/load-project-pdf/estimate/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/estimate/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/asset/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Asset Reports</a>
           <a href="/load-project-pdf/asset/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/asset/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        <p><a href="/load-project-pdf/spending-forecast/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading">Project Spending Forecasts</a>
           <a href="/load-project-pdf/spending-forecast/costmanager/nojs?proids='.$project.'" class="use-ajax report-loading"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="/project-report-excel/spending-forecast/costmanager?proids='.$project.'"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
        </p>
        </div>';
   }
  }
  else {
    $content = '<div class="text-left">
          <p><a href="#" class="no-data">Monthly Report</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
          </p>
          <p><a href="#" class="no-data">Project Cost Summary</a>
            <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
            <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
          </p>
          <p><a href="#" class="no-data">Project Cost Details</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
          </p>
          <p><a href="#" class="no-data">Project Commitment</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
          </p>
          <p><a href="#" class="no-data">Project Safety</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
           </p>
          <p><a href="#" class="no-data">Budget Estimate</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
           </p>
          <p><a href="#" class="no-data">Project Asset Reports</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
           </p>
           <p><a href="#" class="no-data">Project Spending Forecasts</a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/pdf_icon.png"></a>
           <a href="#" class="no-data"><img src="/sites/all/themes/m6connect/images/excel.png"></a>
           </p>
         </div>
         <div id="report-nodata-dialog"></div>';  
  }
  return $content;
}

function get_project_by_company_form($form,&$form_state) {
  global $company;    
  $getEstimateByCompany = _project_list_by_company($company->nid, 'project_management');
  $form['select-estimate'] = array(
    '#type' => 'select',
    '#title'=> 'Select Multiple Projects',
  '#options' => $getEstimateByCompany,
  '#chosen' => TRUE,
  '#attributes' => array('class'=> array('form-control cost-manager-report')),
  '#ajax' => array(
    //'callback'=> 'cost_manager_report_callback',
    'callback'=> 'change_program_project_reports_callback',   
    'effect' => 'fade',
  ),
  '#multiple' => TRUE,
  );  
  return $form; 
}
// ===============================
// Excel report work section start
function project_programe_report_excel($type,$getProID) {
  global $base_url;
  global $company;
  setlocale(LC_MONETARY, 'en_US');
  $XLSRowNo = $XLSColNo = 1;
  include_once DRUPAL_ROOT . '/sites/all/libraries/PHPExcel/Classes/PHPExcel.php';
  if(is_numeric(arg(2))) { $costProId = array(arg(2)); } else { $costProId = explode(',',$_GET['proids']); }  
  $_excelexport_objPHPExcel = new PHPExcel ();
  $_excelexport_objPHPExcel->createSheet ( NULL, 0 );
  $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 );  
  $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
  $nextReport = 1;
  $allDataArr = array();
  if($type == 'costsummary') {
    foreach($costProId as $proIDFnl) {
      $query= db_select('node','n'); 
      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
      $query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
      $query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');  
      $query->join('field_data_field_project_estimate_amount','ea','ea.entity_id = enode.nid');    
      $query->join('field_data_field_capital_contingency','ecc','ecc.entity_id = enode.nid');        
      $query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');  
      $query->leftjoin('field_data_field_est_line_item_amt','la','n.nid=la.entity_id');  
      $query->leftjoin('field_data_field_conigency_percentage','cp','n.nid=cp.entity_id');  
      $query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
      $query->fields('cc',array('entity_id'));
      $query->fields('la',array('field_est_line_item_amt_value'));
      $query->fields('cp',array('field_conigency_percentage_value'));
      $query->fields('cc',array('field_est_cost_code_value'));
      $query->fields('ea',array('field_project_estimate_amount_value'));  
      $query->fields('ecc',array('field_capital_contingency_value'));  
      $query->fields('er',array('field_estimate_reference_nid'));  
      $query->fields('pr',array('field_project_reference_nid'));  
      $query->condition('es.field_project_estimate_status_value', 'approved', '=');
      $query->orderBy('cc.field_est_cost_code_value', 'ASC');
      $query->condition('pr.field_project_reference_nid', $proIDFnl, '=');
      $query->condition('om.gid', $company->nid, '=');
      $costCodeFnl = $query->execute()->fetchAll();
      $allDataArr[$proIDFnl] = $costCodeFnl;    
    }
    // ===========================
    // Gerenating final summary report
    $costSummaryArr = array();
    foreach ($allDataArr as $k => $subArray) {
      foreach ($subArray as $id => $value) {
        $costSummaryArr[] = $value;
      }
    }
    $getCCcodeArr = array();
    $getCCcodeArrCount = array();
    $i = 0;
    foreach($costSummaryArr as $dataPriId => $proVal) {
      // Get cost code
    $query2= db_select('node','n'); 
    $query2->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
    $query2->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
    $query2->join('node','enode','enode.nid=er.field_estimate_reference_nid');
    $query2->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');      
    $query2->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');  
    $query2->leftjoin('field_data_field_est_line_item_amt','la','n.nid=la.entity_id');  
    $query2->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
    $query2->addExpression('SUM(la.field_est_line_item_amt_value)');
    $query2->condition('es.field_project_estimate_status_value', 'approved', '=');
    $query2->orderBy('cc.field_est_cost_code_value', 'ASC');
    $query2->condition('pr.field_project_reference_nid', $proVal->field_project_reference_nid, '=');        
    $query2->condition('om.gid', $company->nid, '=');
    $amtLineTotal = $query2->execute()->fetchField();
    $costCodeDesc = get_description_by_cost_code_mod($proVal->field_est_cost_code_value);
    $capitalContigency = $proVal->field_capital_contingency_value;
    if(!isset($getCCcodeArr[$proVal->field_est_cost_code_value])){
      $getCCcodeArr[$proVal->field_est_cost_code_value]= array(     
      'cc' => $proVal->field_est_cost_code_value,
      'cost_code' => $costCodeDesc,
      'originalBudget' => 0,
      'currentBudget' => 0,
      'Commitment' => 0,
      'spent' => 0,
      'Allocated' => 0,
      'est' => 0,
      'PFC' => 0,
      'Variance' => 0,
      );
      $getCCcodeArrCount[$proVal->field_est_cost_code_value] = 0; 
    }   
    if($proVal->field_est_line_item_amt_value != '') {
      $originalBudget = $proVal->field_est_line_item_amt_value;
    }
    else if($proVal->field_conigency_percentage_value != '') {
      $percent = ($amtLineTotal * $proVal->field_conigency_percentage_value)/100;     
      $originalBudget = $percent;
    }
    $totalOriginalBudget += $originalBudget;
    $currentBudget = $originalBudget;
    $totalcurrentBudget += $currentBudget;
    // Get invoice total
    $getInvoiceTotal = get_invoice_total_by_cost_code($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid);
    $totalInvoiceTotal += $getInvoiceTotal;
    // Get commitment total
    $getCommitmentTotal = get_commitment_total_by_cost_code($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid);
    $totalCommitmentTotal += $getCommitmentTotal;
    // Get total allocated 
    $getTotalAllocated = get_total_allocated_by_cost_code($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid,$getCommitmentTotal);
    $totalAllocated += $getTotalAllocated;
    // Get etc total
    $getETCTotal = get_etc_total_by_cost_code($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid);
    $etcTotal += $getETCTotal;
    // Get Project final cost
    $projectFinalCost = $getTotalAllocated + $getETCTotal;
    $totalFinalCost += $projectFinalCost;
    // Variance
    $varience = $originalBudget - $projectFinalCost;
    $totalVariance += $varience;      
    $getCCcodeArr[$proVal->field_est_cost_code_value]['cc'] = $proVal->field_est_cost_code_value; 
    $getCCcodeArr[$proVal->field_est_cost_code_value]['originalBudget'] += $originalBudget; 
    $getCCcodeArr[$proVal->field_est_cost_code_value]['currentBudget'] += $currentBudget;
    $getCCcodeArr[$proVal->field_est_cost_code_value]['Commitment'] += $getCommitmentTotal;
    $getCCcodeArr[$proVal->field_est_cost_code_value]['spent'] += $getInvoiceTotal;
    $getCCcodeArr[$proVal->field_est_cost_code_value]['Allocated'] += $getTotalAllocated;
    $getCCcodeArr[$proVal->field_est_cost_code_value]['est'] += $getETCTotal;
    $getCCcodeArr[$proVal->field_est_cost_code_value]['PFC'] += $projectFinalCost;
    $getCCcodeArr[$proVal->field_est_cost_code_value]['Variance'] += $varience;
    $getCCcodeArrCount[$proVal->field_est_cost_code_value]++;       
    $i++;
    }
    $getCCcodeArrTotal = array('originalBudget' => 0,'currentBudget' => 0,'Commitment' => 0,'spent' => 0,'Allocated' => 0,'est' => 0,'PFC' => 0,'Variance' => 0);
    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('E'.$XLSRowNo.':F'.$XLSRowNo);
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B1:I3')->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Final Summary Report' ) );
    $XLSRowNo++; $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
    // Cost Code table start here
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Cost Code Description' ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Original Budget' ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Current Budget' ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Committed' ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Spending To Date' ) ); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'Total Allocated' ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( 'Estimate to Complete' ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( 'PFC' ) );
    $XLSRowNo++;
    foreach($getCCcodeArr as $cCodeId => $cCodeVal) {
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $cCodeVal['cost_code'] ) );   
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $cCodeVal['originalBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $cCodeVal['currentBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $cCodeVal['Commitment'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $cCodeVal['spent'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $cCodeVal['Allocated'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $cCodeVal['est'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $cCodeVal['PFC'] ) );
      $XLSRowNo++;
      $getCCcodeArrTotal = array(
      'originalBudget' => $getCCcodeArrTotal['originalBudget']+$cCodeVal['originalBudget'],
      'currentBudget' => $getCCcodeArrTotal['currentBudget']+$cCodeVal['originalBudget'],
      'Commitment' => $getCCcodeArrTotal['Commitment']+$cCodeVal['Commitment'],
      'spent' => $getCCcodeArrTotal['spent']+$cCodeVal['spent'],
      'Allocated' => $getCCcodeArrTotal['Allocated']+$cCodeVal['Allocated'],
      'est' => $getCCcodeArrTotal['est']+$cCodeVal['est'],
      'PFC' => $getCCcodeArrTotal['PFC']+$cCodeVal['PFC'],
      'Variance' => $getCCcodeArrTotal['Variance']+$cCodeVal['Variance'],
      );
    }
    $XLSRowNo++;
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B' . ($XLSRowNo - 1).':I'.($XLSRowNo - 1))->applyFromArray($BStyle);
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Total' ) );
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $getCCcodeArrTotal['originalBudget'] ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $getCCcodeArrTotal['originalBudget'] ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $getCCcodeArrTotal['Commitment'] ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode (  $getCCcodeArrTotal['spent'] ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $getCCcodeArrTotal['Allocated'] ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $getCCcodeArrTotal['est'] ) );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $getCCcodeArrTotal['PFC'] ) );
    $XLSRowNo++; $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
  }
  $checkFirst = 1;
  foreach($costProId as $proID) {
    $projectDetails = node_load($proID);
    $projectName = $projectDetails->title;
    $projectNumber = $projectDetails->field_project_mgmt_number['und'][0]['value'];
    if(isset($projectDetails->field_project_mgmt_manager['und'])) { 
      $userData = user_load($projectDetails->field_project_mgmt_manager['und'][0]['value']);
      $projectManager = ucwords(_get_user_realname($userData->uid));
      $managerPic = image_style_url('user_pic_40x40',$userData->field_user_profile_photo['und'][0]['uri']);
      $pmGDType = ($userData->field_user_profile_photo['und'][0]['filemime'] == 'image/jpeg')?'jpg':'png';
    }
    else {
      $projectManager = 'None';
      $managerPic == '/sites/default/files/styles/find_people/public/images_13.png';
      $pmGDType = 'png';
    }     
    if(isset($projectDetails->field_project_mgmt_location['und']) && $projectDetails->field_project_mgmt_location['und'][0]['value'] != '') {
      $locationID = node_load($projectDetails->field_project_mgmt_location['und'][0]['value']);
      $getLocation = $locationID->field_org_address['und'][0]['thoroughfare'].' '.$locationID->field_org_address['und'][0]['administrative_area'];
    }
    else {
      $getLocation = 'None';
    }
    $getCompanyData = node_load($projectDetails->og_group_ref['und'][0]['target_id']);  
    if(isset($getCompanyData->field_logo['und'])) {   
      $companyLogo = image_style_url('thumbnail', $getCompanyData->field_logo['und'][0]['uri']);  
      $gdImageType = ($getCompanyData->field_logo['und'][0]['filemime'] == 'image/jpeg')?'jpeg':'png';
    }
    else {
      $companyLogo = $base_url.'/sites/all/themes/m6connect/images/default_company_profile.jpg';
      $gdImageType = 'jpeg';
    }   
    $costCode = _get_report_costcode_data($proID);  
    // final summary report
    // Get cost code by and budget amount by project    
    $query= db_select('node','n'); 
    $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
    $query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
    $query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
    $query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');  
    $query->join('field_data_field_project_estimate_amount','ea','ea.entity_id = enode.nid');    
    $query->join('field_data_field_capital_contingency','ecc','ecc.entity_id = enode.nid');        
    $query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');  
    $query->leftjoin('field_data_field_est_line_item_amt','la','n.nid=la.entity_id');  
    $query->leftjoin('field_data_field_conigency_percentage','cp','n.nid=cp.entity_id');  
    $query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
    $query->fields('cc',array('entity_id'));
    $query->fields('la',array('field_est_line_item_amt_value'));
    $query->fields('cp',array('field_conigency_percentage_value'));
    $query->fields('cc',array('field_est_cost_code_value'));
    $query->fields('ea',array('field_project_estimate_amount_value'));  
    $query->fields('ecc',array('field_capital_contingency_value'));  
    $query->fields('er',array('field_estimate_reference_nid'));  
    $query->fields('pr',array('field_project_reference_nid'));  
    $query->condition('es.field_project_estimate_status_value', 'approved', '=');
    $query->orderBy('cc.field_est_cost_code_value', 'ASC');
    $query->condition('pr.field_project_reference_nid', $proID, '=');
    $query->condition('om.gid', $company->nid, '=');
    $costCodeFinal = $query->execute()->fetchAll();
    $allDataArr[$proID] = $costCodeFinal; 
    $ccArrTotal= array('originalBudget' => 0,'currentBudget' => 0,'Commitment' => 0,'spent' => 0,'Allocated' => 0,'est' => 0,'PFC' => 0,'Variance' => 0);
    // ===============================
    // Initialise Excel monthly Report
    // ===============================    
    if($type == 'monthly') {
      $XLSRowNo = ($nextReport == 0)?$XLSRowNo:$nextReport; 
      //$_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $proID ) );
      $reportTitle = 'Monthly Project Report';    
      $projectStatus = isset($projectDetails->field_project_mgmt_status['und'])?$projectDetails->field_project_mgmt_status['und'][0]['value']:'None';
      $fundingStatus = isset($projectDetails->field_project_funding_status['und'])?$projectDetails->field_project_funding_status['und'][0]['value']:'None';
      $description = isset($projectDetails->body['und'])?strip_tags($projectDetails->body['und'][0]['value']):'None';
      $designStatus = isset($projectDetails->field_project_design_status['und'])?$projectDetails->field_project_design_status['und'][0]['value']:'None';
      $commentData = get_project_manager_comment_by_project($proID);
      $getScheduleNodes = _get_sechedule_data_by_project($proID);
      $generalInfoImage = _get_general_image_data_by_project($proID);
      $proDescImage = _get_project_description_image_data_by_project($proID);
      $proSafetyImage = _get_safety_image_data_by_project($proID);
      $proAdditionalImage = _get_additional_image_data_by_project($proID);
      $recentSafety = _get_recent_safety_data_by_project($proID);
      $allSafety = _get_all_safety_data_by_project($proID);
      $getRecentDate = $recentSafety[0]->field_start_date_value != ''?date('m/d/Y', strtotime($recentSafety[0]->field_start_date_value)):0;
      $getRecentLta = $recentSafety[0]->field_lost_time_accidents_value != ''?$recentSafety[0]->field_lost_time_accidents_value:0;
      $getRecentHours = $recentSafety[0]->field_hours_this_period_value != ''?$recentSafety[0]->field_hours_this_period_value:0;
      foreach($allSafety as $safetyKey => $safetyVal) {
        $lta = $safetyVal->field_lost_time_accidents_value;
        $totalLTA += $safetyVal->field_lost_time_accidents_value;
        $workingHrs = $safetyVal->field_hours_this_period_value;
        $totalHours += $safetyVal->field_hours_this_period_value;
      }
      // ==================================
      // Excel work for Monthly report start      
      // Calling compay Logo and set into excel
      $gdImage = ($gdImageType == 'jpeg')?imagecreatefromjpeg ( $companyLogo ):imagecreatefrompng ( $companyLogo );
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 62 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      // Comapy logo calling process ends
      // ********************************
      $endData = $XLSRowNo+3;
      $rowFills = 'B'.$XLSRowNo.':H'.$endData;   
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo+1), utf8_encode ( 'Monthly Project Report' ) ); 
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
      // == Setting Report title, Project Name, Number == //
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( ucwords($projectName) ) );
      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('G'.$XLSRowNo.':H'.$XLSRowNo);
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $projectNumber ) );       
      $XLSRowNo++; $XLSRowNo++;
      // =====================================
      // Setting up general information section
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'General Information' ) );
      $XLSRowNo++; $XLSRowNo++;
      $col = 1;
      foreach($generalInfoImage as $giImageKey => $giImageVal) { 
      $fileData = file_load($generalInfoImage[$giImageKey]->field_group_information_fid); 
      $getImage = image_style_url('project_general_images_style',$fileData->uri);
      if($fileData->filemime == 'image/jpeg'){ $gdImage = imagecreatefromjpeg($getImage); }
      else { $gdImage = imagecreatefrompng($getImage); }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );    
      $colindex = ($col == 1)?excelgeneratorurl_get_colindex ( $col ):excelgeneratorurl_get_colindex ( $col );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      $col++;
      }       
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Project Manager:' ) ); 
      $colindex = excelgeneratorurl_get_colindex ( $col+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( $projectManager ) );  
      // Project manager image
      $gdImage = ($pmGDType == 'jpg')?imagecreatefromjpeg ( $managerPic ):imagecreatefrompng ( $managerPic );
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 32 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( 'E' . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      $XLSRowNo++;  
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Location:' ) );
      $colindex = excelgeneratorurl_get_colindex ( $col+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( $getLocation ) );
      $XLSRowNo++;  
      $colindex = excelgeneratorurl_get_colindex ( $col );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Project Status:' ) );
      $colindex = excelgeneratorurl_get_colindex ( $col+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( $projectStatus ) );
      $XLSRowNo++;      
      $colindex = excelgeneratorurl_get_colindex ( $col );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Funding Status:' ) );
      $colindex = excelgeneratorurl_get_colindex ( $col+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( $fundingStatus ) );
      $XLSRowNo++;
      $colindex = excelgeneratorurl_get_colindex ( $col );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Design Status:' ) );
      $colindex = excelgeneratorurl_get_colindex ( $col+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( $designStatus ) );
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
      // End Setting up general information
      // **********************************
      // Start Project description and project comment section
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );     
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Description' ) );
      $XLSRowNo++; $XLSRowNo++;
      $col1 = 1;
      foreach($proDescImage as $pdImageKey => $pdImageVal) { 
      $fileData = file_load($proDescImage[$pdImageKey]->field_project_description_images_fid); 
      $getImagePD = image_style_url('project_general_images_style',$fileData->uri);
      $gdImage1 = ($fileData->filemime == 'image/jpeg')?imagecreatefromjpeg($getImagePD):imagecreatefrompng($getImagePD);   
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage1 );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );    
      $colindex = ($col1 == 1)?excelgeneratorurl_get_colindex ( $col1 ):excelgeneratorurl_get_colindex ( $col1 );   
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      $col1++;
      }
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col1 );   
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( $description ) );       
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++; $XLSRowNo++; 
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );   
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Manager Comments' ) );
      $XLSRowNo++; $XLSRowNo++;
      $srNo = 1;
      foreach($commentData as $commentKey => $commentVal) {
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $srNo.' '.$commentVal->message ) );
      $XLSRowNo++;
      $srNo ++;
      }
      $XLSRowNo++; $XLSRowNo++;
      // End description and project comment
      // ***********************************
      // Project cost details and Cost summary table section
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Cost Detail' ) );
      $XLSRowNo++; $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Cost Code' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Current Budget' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Committed' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Spent' ) );  
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Total Allocated' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'ETC' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( 'PFC' ) );
      $XLSRowNo++;
      foreach($costCode as $ccId => $ccVal) {
      // Get cost code
       
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $ccVal['cost_code'] ) );        
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':H'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');        
      //$_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':H'.($XLSRowNo))->getNumberFormat()->setFormatCode('_("$"* #,##0.00_);_("$"* \(#,##0.00\);_("$"* "-"??_);_(@_)');    
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( intval($ccVal['originalBudget']) ) );
      //$_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( '$'.number_format($currentBudget) ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( intval($ccVal['Commitment']) ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $ccVal['spent'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $ccVal['Allocated'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $ccVal['est'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $ccVal['PFC'] ) );
      $XLSRowNo++;
      $ccArrTotal= array(
          'originalBudget' => $ccArrTotal['originalBudget']+$ccVal['originalBudget'],
          'currentBudget' => $ccArrTotal['currentBudget']+$ccVal['originalBudget'],
          'Commitment' => $ccArrTotal['Commitment']+$ccVal['Commitment'],
          'spent' => $ccArrTotal['spent']+$ccVal['spent'],
          'Allocated' => $ccArrTotal['Allocated']+$ccVal['Allocated'],
          'est' => $ccArrTotal['est']+$ccVal['est'],
          'PFC' => $ccArrTotal['PFC']+$ccVal['PFC'],
          'Variance' => $ccArrTotal['Variance']+$ccVal['Variance'],
        );
      }
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Totals' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':H'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $ccArrTotal['originalBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $ccArrTotal['Commitment'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $ccArrTotal['spent'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $ccArrTotal['Allocated'] ) ); 
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $ccArrTotal['est'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $ccArrTotal['PFC'] ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':I'.$XLSRowNo.'')->applyFromArray($BStyle);
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
      
      // == Project cost details and Cost summary table section
      // ================================
      // Project sechedule table section begain
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Schedule' ) );
      $XLSRowNo++; $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Milestone Description' ) );  
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Original Date' ) );  
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Projected Date' ) ); 
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Actual Date' ) );
      $XLSRowNo++;
      foreach($getScheduleNodes as $scheduleId => $scheduleVal) {
      $scheduleDetails = node_load($scheduleVal);
      $projectMilstone = isset($scheduleDetails->field_project_milestone['und'])?$scheduleDetails->field_project_milestone['und'][0]['value']:'None';
      $originalDate = isset($scheduleDetails->field_schedule_original['und'])?date('m/d/Y', strtotime($scheduleDetails->field_schedule_original['und'][0]['value'])):'None';
      $projectedDate = isset($scheduleDetails->field_schedule_projected['und'])?date('m/d/Y', strtotime($scheduleDetails->field_schedule_projected['und'][0]['value'])):'None';
      $actualDate = isset($scheduleDetails->field_schedule_actual['und'])?date('m/d/Y', strtotime($scheduleDetails->field_schedule_actual['und'][0]['value'])):'None';    
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $projectMilstone ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $originalDate ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $projectedDate ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $actualDate ) );
      $XLSRowNo++;
      } 
      $XLSRowNo++;  
      // Project sechedule table section
      // ===============================
      // Retrive safety data for monthly report
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Safety Record' ) );
      $XLSRowNo++; $XLSRowNo++;
      $col2 = 1;
      foreach($proSafetyImage as $siImageKey => $siImageVal) {
      $fileData = file_load($proSafetyImage[$siImageKey]->field_project_safety_images_fid); 
      $getImageSI = image_style_url('project_general_images_style',$fileData->uri);
      if($fileData->filemime == 'image/jpeg'){ $gdImage = imagecreatefromjpeg($getImageSI); }
      else { $gdImage = imagecreatefrompng($getImageSI); }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      if($col2 == 1) { $colindex = excelgeneratorurl_get_colindex ( $col2 ); }
      else { $colindex = excelgeneratorurl_get_colindex ( $col2 ); }    
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      $col2++;
      } 
      $XLSRowNo++;  
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col2 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Most Recent' ) );  
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col2+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Total' ) );
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col2 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Safety Period LTA * Period Hours' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $colindex = excelgeneratorurl_get_colindex ( $col2+1 );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'LTA   Total Work Hours   EMR**' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $XLSRowNo++;
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $getRecentDate.'  '.$getRecentLta.'  '.$getRecentHours  ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $totalLTA.'  '.$totalHours.' 0.00 ' ) );
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
      // End work for safety data for manthly report
      // ===========================================
      // Retirving additonal project photos
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'. ($XLSRowNo - 1).':H'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Additional Project Photos' ) );
      $XLSRowNo++;
      $XLSRowNo++;
      $col4 = 1;
      foreach($proAdditionalImage as $aiImageKey => $aiImageVal) {
      $fileData = file_load($proAdditionalImage[$aiImageKey]->field_project_additional_images_fid);
      $getImageAI = image_style_url('project_general_images_style',$fileData->uri);
      if($fileData->filemime == 'image/jpeg'){ $gdImage = imagecreatefromjpeg($getImageAI); }
      else { $gdImage = imagecreatefrompng($getImageAI); }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      if($col4 == 1) { $colindex = excelgeneratorurl_get_colindex ( $col4 ); }
      else { $colindex = excelgeneratorurl_get_colindex ( $col4 ); }    
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      $col4++;
      }     
      // End work for additional project photos
      // ======================================
      // == End of monthly report For excel     
    } 
    else if($type == 'costsummary') {
      if($checkFirst == 1) {  
          $XLSRowNo = ($nextReport == 0)?$XLSRowNo:$nextReport+$XLSRowNo;    
      }
      else {
        $XLSRowNo = ($nextReport == 0)?$XLSRowNo:$nextReport;
      }
      $reportTitle = 'Project Cost Summary Report';
      // ===== Excel Work for cost summary ==== //
      if($gdImageType == 'jpeg') {
      $gdImage = imagecreatefromjpeg ( $companyLogo );
      }
      else {
      $gdImage = imagecreatefrompng ( $companyLogo );
      }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 62 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      //$XLSRowNo++; $XLSRowNo++;   
      $endData = $XLSRowNo+3;
      $rowFills = 'B'.$XLSRowNo.':I'.$endData;      
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      
      //$_excelexport_objPHPExcel->getActiveSheet()->getStyle('B1:I4')->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      //$_excelexport_objPHPExcel->getActiveSheet()->getStyle('B6:I6')->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('E'.$XLSRowNo.':F'.$XLSRowNo);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E'.$XLSRowNo, utf8_encode ( $reportTitle ) );
      $XLSRowNo++; $XLSRowNo++;$XLSRowNo++;$XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo+1) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo+1), utf8_encode ( $projectName ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo+1) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo+1), utf8_encode ( $projectNumber ) );
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Project Manager: '.$projectManager ) );
      $XLSRowNo++;$XLSRowNo++; $XLSRowNo++;$XLSRowNo++;
      // Cost Code table start here
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Cost Code Description' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Original Budget' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Current Budget' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Committed' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Spending To Date' ) ); 
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'Total Allocated' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( 'Estimate to Complete' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( 'PFC' ) );
      $XLSRowNo++;
      foreach($costCode as $ccId => $ccVal) {
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $ccVal['cost_code'] ) );    
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $ccVal['originalBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $ccVal['currentBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $ccVal['Commitment'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $ccVal['spent'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $ccVal['Allocated'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $ccVal['est'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $ccVal['PFC'] ) );
      $XLSRowNo++;
      $ccArrTotal= array(
        'originalBudget' => $ccArrTotal['originalBudget']+$ccVal['originalBudget'],
        'currentBudget' => $ccArrTotal['currentBudget']+$ccVal['originalBudget'],
        'Commitment' => $ccArrTotal['Commitment']+$ccVal['Commitment'],
        'spent' => $ccArrTotal['spent']+$ccVal['spent'],
        'Allocated' => $ccArrTotal['Allocated']+$ccVal['Allocated'],
        'est' => $ccArrTotal['est']+$ccVal['est'],
        'PFC' => $ccArrTotal['PFC']+$ccVal['PFC'],
        'Variance' => $ccArrTotal['Variance']+$ccVal['Variance'],
        );
      }
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B' . ($XLSRowNo - 1).':I'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Total' ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $ccArrTotal['originalBudget'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $ccArrTotal['originalBudget'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $ccArrTotal['Commitment'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode (  $ccArrTotal['spent'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $ccArrTotal['Allocated'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $ccArrTotal['est'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $ccArrTotal['PFC'] ) );
      $XLSRowNo++;    
    }
    else if($type == 'costdetail') {
      $XLSRowNo = ($nextReport == 0)?$XLSRowNo:$nextReport; 
      $reportTitle = 'Project Cost Detail Report';
      // ===== Excel Work for cost summary ==== //
      if($gdImageType == 'jpeg') {
      $gdImage = imagecreatefromjpeg ( $companyLogo );
      }
      else {
      $gdImage = imagecreatefrompng ( $companyLogo );
      }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 62 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      //$XLSRowNo++; $XLSRowNo++;
      $endData = $XLSRowNo+3;
      $rowFills = 'B'.$XLSRowNo.':I'.$endData;      
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('E'.$XLSRowNo.':F'.$XLSRowNo);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E'.$XLSRowNo, utf8_encode ( $reportTitle ) );
      $XLSRowNo++; $XLSRowNo++;$XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo+1) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo+1), utf8_encode ( $projectName ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo+1) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo+1), utf8_encode ( $projectNumber ) );
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Project Manager: '.$projectManager ) );
      $XLSRowNo++;$XLSRowNo++; $XLSRowNo++;
      // Cost Code table start here
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Cost Code Description' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Original Budget' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Current Budget' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Committed' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Spending To Date' ) ); 
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'Total Allocated' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( 'Estimate to Complete' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( 'PFC' ) );
      $XLSRowNo++;
      foreach($costCode as $ccId => $ccVal) {
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $ccVal['cost_code'] ) );    
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $ccVal['originalBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $ccVal['currentBudget'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $ccVal['Commitment'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $ccVal['spent'] ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $ccVal['Allocated'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $ccVal['est'] ) );      
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $ccVal['PFC'] ) );
      $XLSRowNo++;
      $ccArrTotal= array(
        'originalBudget' => $ccArrTotal['originalBudget']+$ccVal['originalBudget'],
        'currentBudget' => $ccArrTotal['currentBudget']+$ccVal['originalBudget'],
        'Commitment' => $ccArrTotal['Commitment']+$ccVal['Commitment'],
        'spent' => $ccArrTotal['spent']+$ccVal['spent'],
        'Allocated' => $ccArrTotal['Allocated']+$ccVal['Allocated'],
        'est' => $ccArrTotal['est']+$ccVal['est'],
        'PFC' => $ccArrTotal['PFC']+$ccVal['PFC'],
        'Variance' => $ccArrTotal['Variance']+$ccVal['Variance'],
        );
      }
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B' . ($XLSRowNo - 1).':I'.($XLSRowNo - 1))->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Project Total' ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $ccArrTotal['originalBudget'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $ccArrTotal['originalBudget'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $ccArrTotal['Commitment'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode (  $ccArrTotal['spent'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $ccArrTotal['Allocated'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $ccArrTotal['est'] ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $ccArrTotal['PFC'] ) );
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;  
      
      $queryCommit= db_select('node','n'); 
        $queryCommit->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
        $queryCommit->join('node','enode','enode.nid=er.field_estimate_reference_nid');
        $queryCommit->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');      
        $queryCommit->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');
        $queryCommit->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
        $queryCommit->fields('cc',array('field_est_cost_code_value'));
        $queryCommit->condition('es.field_project_estimate_status_value', 'approved', '=');
        $queryCommit->condition('pr.field_project_reference_nid', $proID, '=');        
        $queryCommit->orderBy('cc.field_est_cost_code_value', 'ASC');
        $queryCommit->groupBy('cc.field_est_cost_code_value');
        $costCodeCoomit = $queryCommit->execute()->fetchCol();   
      foreach($costCodeCoomit as $ccKey => $ccValData) { 
        $query2 = db_select('node','n');
          $query2->join('field_data_field_commitment_ws_code','cc','cc.entity_id = n.nid');
          $query2->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
          $query2->fields('n',array('nid'));
          $query2->condition('cc.field_commitment_ws_code_value', $ccValData, '=');
          $query2->condition('pr.field_project_reference_nid', $proID, '=');
          $query2->condition('n.type', 'project_commitement', '='); 
          $getCommit = $query2->execute()->fetchCol();
      if(!empty($getCommit)) {
        $XLSRowNo++;
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B' . ($XLSRowNo - 1).':I'.($XLSRowNo - 1))->applyFromArray($BStyle);
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $ccValData ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Commitment Number' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Vendor' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Description' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode (  'Date' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'Commited Amount' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( 'Invoiced Against' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'I' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( 'Commitment Balance' ) );
        $XLSRowNo++;
        foreach($getCommit as $key => $comitId) {
          $commitNode = node_load($comitId);
        $coomitVendoer = isset($commitNode->field_vendor['und'])?$commitNode->field_vendor['und'][0]['value']:'None';
        if($coomitVendoer != 'None' && is_numeric($coomitVendoer)) {
          $coomitVendoer = node_load($coomitVendoer)->title;
        }
        else {
          $coomitVendoer = $coomitVendoer;
        }
        // Get invoice spending amount
        $query3= db_select('node','n'); 
        $query3->join('field_data_field_invoice_commitment','ic','ic.entity_id = n.nid');
        $query3->join('field_data_field_invoice_amount','ia','ia.entity_id = n.nid');
        $query3->addExpression('SUM(ia.field_invoice_amount_value)','finalTotal');
        $query3->condition('n.type','project_spending','=');
        $query3->condition('ic.field_invoice_commitment_nid',$commitNode->nid,'=');
        $query3->groupBy('ic.field_invoice_commitment_nid');
        $getTotalSpendingAmt = $query3->execute()->fetchField();        
        $commitAmt = $commitNode->field_commitment_po_final_total['und'][0]['value'];
        $commitBalance = ($commitAmt - $getTotalSpendingAmt);
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $commitNode->field_commitment_number_calculat['und'][0]['value'] ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $coomitVendoer!=''?$coomitVendoer:'None' ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $commitNode->field_commitment_item_descriptio['und'][0]['value']!=''?strip_tags($commitNode->field_commitment_item_descriptio['und'][0]['value']):'None' ) );     
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode (  $date = date('m/d/Y', $commitNode->created) ) );
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':I'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $commitAmt ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $getTotalSpendingAmt ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'I' . ($XLSRowNo), utf8_encode ( $commitBalance ) );
        $XLSRowNo++;
        $query2 = db_select('node','n');
        $query2->join('field_data_field_invoice_commitment','ic','ic.entity_id = n.nid');
              $query2->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
              $query2->fields('n',array('nid'));
              $query2->condition('ic.field_invoice_commitment_nid', $commitNode->nid, '=');
              $query2->condition('pr.field_project_reference_nid', $proID, '=');
              $query2->condition('n.type', 'project_spending', '=');  
              $getInv = $query2->execute()->fetchCol(); 
              if(!empty($getInv)) {
          $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
            $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Invoice Number' ) );
          $XLSRowNo++;
          foreach($getInv as $invKey => $invId) {
              $invNode = node_load($invId);
          $invNumber = isset($invNode->field_invoice_number_cal['und'])?$invNode->field_invoice_number_cal['und'][0]['value']:'None';
          $invDate = isset($invNode->field_invoice_date['und'])?date('m/d/Y',strtotime($invNode->field_invoice_date['und'][0]['value'])):'None';
          $invAmt = isset($invNode->field_invoice_amount['und'])?'$'.number_format($invNode->field_invoice_amount['und'][0]['value'],2):'$0.00';
          
              $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $invNumber ) );           
              $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $invDate ) );           
              $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $invAmt ) );
          $XLSRowNo++;
          }
        }
        }
      }
      }
    }
    else if($type == 'commitment') {
      $XLSRowNo = ($nextReport == 0)?$XLSRowNo:$nextReport; 
      $reportTitle = 'Project Commitment Report';   
      $query= db_select('node','n'); 
      $query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
      $query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
      $query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');      
      $query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');
      $query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
      $query->fields('cc',array('field_est_cost_code_value'));
      $query->condition('es.field_project_estimate_status_value', 'approved', '=');
      $query->condition('pr.field_project_reference_nid', $proID, '=');        
      $query->orderBy('cc.field_est_cost_code_value', 'ASC');
      $query->groupBy('cc.field_est_cost_code_value');
      $costCodeCoomit = $query->execute()->fetchCol();
      // ==============
      $XLSRowNo++;
      if($gdImageType == 'jpeg') {
      $gdImage = imagecreatefromjpeg ( $companyLogo );
      }
      else {
      $gdImage = imagecreatefrompng ( $companyLogo );
      }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 62 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      //$XLSRowNo++; $XLSRowNo++;   
      $endData = $XLSRowNo+3;
      $rowFills = 'B'.$XLSRowNo.':H'.$endData;      
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D'.$XLSRowNo )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D'.$XLSRowNo, utf8_encode ($reportTitle) );
      $XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( ucfirst($projectName) ) );  
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ($projectNumber) );
      /*$XLSRowNo++;$XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Project Manager: '.$projectManager ) );  */
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;  
      $finalTotalInvoice = 0;
      $finalTotalCommit = 0;
      foreach($costCodeCoomit as $ccKey => $ccVal) {
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      //$_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $ccVal ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Cost code | Description' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Commitment Number' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Vendor' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Description' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Date' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'Amount' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'H' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( 'Invoiced Against' ) );
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':H'.$XLSRowNo)->applyFromArray($BStyle);
      $query= db_select('node','n');    
      $query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');
      $query->join('field_data_field_cost_code','cc','cc.entity_id = n.nid');
      $query->fields('n', array('nid'));
      $query->condition('cc.field_cost_code_value', $ccVal, '=');
      $query->condition('pr.field_project_reference_nid', $proID, '=');
      $query->condition('pr.bundle','project_commitement','=');
      $getCommitmentNodes = $query->execute()->fetchCol();
      $XLSRowNo++;
      $totalCommitAmt = 0;
      $totalInvoice = 0;
      foreach($getCommitmentNodes as $commitNodeKey => $comitNodeVal) { 
        $commitmentNode = node_load($comitNodeVal);       
        $commitNumber = isset($commitmentNode->field_commitment_number_calculat['und'])?$commitmentNode->field_commitment_number_calculat['und'][0]['value']:'None';
        $coomitVendoer = isset($commitmentNode->field_vendor['und'])?$commitmentNode->field_vendor['und'][0]['value']:'None';
        if($coomitVendoer != 'None' && is_numeric($coomitVendoer)) {
        $coomitVendoer = node_load($coomitVendoer)->title;
        }
        else {
        $coomitVendoer = $coomitVendoer;
        }
        $commitDesc = isset($commitmentNode->body['und'])?$commitmentNode->body['und'][0]['value']:'None';
        $commitDate = date('m/d/Y', $commitmentNode->created);
        $commitAmt = isset($commitmentNode->field_commitment_po_final_total['und'])?$commitmentNode->field_commitment_po_final_total['und'][0]['value']:'$0';
        $totalCommitAmt += $commitAmt;
        $changeOrder = '$0.00';
        // Get invoice Against by commitment
        $query= db_select('node','n'); 
        $query->join('field_data_field_invoice_commitment','ic','ic.entity_id = n.nid');
        $query->join('field_data_field_invoice_amount','ia','ia.entity_id = n.nid');
        $query->addExpression('SUM(ia.field_invoice_amount_value)','finalTotal');
        $query->condition('n.type','project_spending','=');
        $query->condition('ic.field_invoice_commitment_nid',$commitmentNode->nid,'=');
        $query->groupBy('ic.field_invoice_commitment_nid');
        $getTotalSpending = $query->execute()->fetchField();
        $invoiceAgainst = $getTotalSpending!= ''?$getTotalSpending:'0.00';      
        $totalInvoice += $invoiceAgainst;     
        $ccdesc = get_description_by_cost_code_mod($commitmentNode->field_cost_code['und'][0]['value']);    
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $ccdesc ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $commitNumber ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $coomitVendoer ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $commitDesc ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $commitDate ) );
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':G'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $commitAmt ) );
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':H'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $invoiceAgainst ) );
        $XLSRowNo++;
      }
      $finalTotalInvoice += $totalInvoice; 
      $finalTotalCommit += $totalCommitAmt;
      $XLSRowNo++;
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN),'top' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':H'.$XLSRowNo)->applyFromArray($BStyle);   
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Total' ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':G'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $totalCommitAmt ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':H'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $totalInvoice ) );
      $XLSRowNo++; $XLSRowNo++;
      } 
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN),'top' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':H'.$XLSRowNo)->applyFromArray($BStyle);
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':H'.$XLSRowNo)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Total' ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':G'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( $finalTotalCommit ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('G' . ($XLSRowNo).':H'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode ( $finalTotalInvoice ) );
      $XLSRowNo++;      
    }
    else if($type == 'safety') {
      global $company;
      $XLSRowNo = ($nextReport == 0)?$XLSRowNo:$nextReport; 
      $reportTitle = 'Project Safety Report';   
      $query = db_select('node','n');
        $query->join('field_data_field_project_reference','pr','pr.entity_id = n.nid');
        $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));  
        $query->fields('n',array('nid'));
        $query->condition('om.gid', $company->nid, '=');
        $query->condition('pr.field_project_reference_nid', $proID, '=');
        $query->condition('n.type', 'project_safety', '=');
        $getSafetyNodes = $query->execute()->fetchCol();
      // ==============
      $XLSRowNo++;
      if($gdImageType == 'jpeg') {
      $gdImage = imagecreatefromjpeg ( $companyLogo );
      }
      else {
      $gdImage = imagecreatefrompng ( $companyLogo );
      }
      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 62 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      //$XLSRowNo++; $XLSRowNo++;   
      $endData = $XLSRowNo+3;
      $rowFills = 'B'.$XLSRowNo.':G'.$endData;      
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D'.$XLSRowNo )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D'.$XLSRowNo, utf8_encode ($reportTitle) );
      $XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( ucfirst($projectName) ) );  
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ($projectNumber) );
      $XLSRowNo++; $XLSRowNo++; $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Start Date' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'End Date' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'D' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Lost Time Accidents' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'E' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( 'Minor' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'F' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( 'Hours' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'G' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( 'Comment' ) );
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':G'.$XLSRowNo)->applyFromArray($BStyle);
      if(!empty($getSafetyNodes)) {
        foreach($getSafetyNodes as $saftyId => $saftyVal){
        $safetyNode = node_load($saftyVal);
          $startDate = isset($safetyNode->field_start_date['und'])?date('m/d/Y', strtotime($safetyNode->field_start_date['und'][0]['value'])):'None';
          $endDate = isset($safetyNode->field_end_date['und'])?date('m/d/Y', strtotime($safetyNode->field_end_date['und'][0]['value'])):'None';
          $ltAccidents = isset($safetyNode->field_lost_time_accidents['und'])?$safetyNode->field_lost_time_accidents['und'][0]['value']:'None';
          $totalLTA += $ltAccidents;
          $minor = isset($safetyNode->field_minor['und'])?$safetyNode->field_minor['und'][0]['value']:'None';
          $hours = isset($safetyNode->field_hours_this_period['und'])?$safetyNode->field_hours_this_period['und'][0]['value']:'None';
          $safteyComment = isset($safetyNode->body['und'])?$safetyNode->body['und'][0]['value']:'None';
          $totalHour += $hours;
        $XLSRowNo++;    
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $startDate ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $endDate ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( $ltAccidents ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $minor ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'F' . ($XLSRowNo), utf8_encode ( $hours ) );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'G' . ($XLSRowNo), utf8_encode ( substr(strip_tags($safteyComment),0,100).'...' ) );
        $XLSRowNo++;
      }   
      $XLSRowNo++;
      $totalEMR = ($totalLTA * 200000)/$totalHour;
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN),'top' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':G'.$XLSRowNo)->applyFromArray($BStyle);   
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Total Hours Worked:' ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( $totalHour ) );
      $XLSRowNo++; $XLSRowNo++;
      $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN),'top' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN))); 
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':G'.$XLSRowNo)->applyFromArray($BStyle);   
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D' . ($XLSRowNo), utf8_encode ( 'Incident Rate:' ) );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'E' . ($XLSRowNo), utf8_encode ( round($totalEMR, 2) ) );
      }
      $XLSRowNo++;      
    } 
    else if($type == 'estimate') {
      $XLSRowNo = ($nextReport == 0) ? $XLSRowNo : $nextReport;
      $reportTitle = 'Budget Estimate Report';
      $projectNumber = $projectDetails->field_project_mgmt_number['und'][0]['value'];
      $projectName = $projectDetails->title;
      $query= db_select('node','n'); 
      $query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
      $query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
      $query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');  
      $query->join('field_data_field_project_estimate_amount','ea','ea.entity_id = enode.nid');    
      $query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');
      $query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
      $query->leftjoin('field_data_field_est_line_item_amt','la','la.entity_id=n.nid'); 
      $query->fields('cc',array('field_est_cost_code_value'));
      $query->fields('ea',array('field_project_estimate_amount_value'));
      $query->fields('la',array('field_est_line_item_amt_value'));
      $query->condition('es.field_project_estimate_status_value', 'approved', '=');
      $query->condition('pr.field_project_reference_nid', $proID, '=');        
      $estimateData = $query->execute()->fetchAll();
      // =========================
      // Excel work start here for 
      // Estimate report
      // =========================
      if($gdImageType == 'jpeg') {
        $gdImage = imagecreatefromjpeg ( $companyLogo );
      }
      else {
        $gdImage = imagecreatefrompng ( $companyLogo );
      }

      $objDrawing = new PHPExcel_Worksheet_MemoryDrawing ();
      $objDrawing->setName ( 'Sample image' );
      $objDrawing->setDescription ( 'Sample image' );
      $objDrawing->setImageResource ( $gdImage );
      $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      $objDrawing->setHeight ( 62 );
      $colindex = excelgeneratorurl_get_colindex ( 1 );
      $objDrawing->setCoordinates ( $colindex . ($XLSRowNo) );  
      $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      //$XLSRowNo++;$XLSRowNo++;
      $endData = $XLSRowNo+3;
      $rowFills = 'B'.$XLSRowNo.':D'.$endData;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C'.$XLSRowNo, utf8_encode ( $reportTitle ) );
      $XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B'.$XLSRowNo, utf8_encode ( $projectName ) );   
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D'.$XLSRowNo, utf8_encode ( $projectNumber ) ); 
      $XLSRowNo++; $XLSRowNo++; 
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindex . ($XLSRowNo), utf8_encode ( 'Capital' ) );
      $XLSRowNo++; $XLSRowNo++;

      foreach($estimateData as $estKey => $estVal) {
        $XLSRowNo++;
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Cost Code | Description' ) );
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( 'Line Item Cost' ) );
        $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B'.$XLSRowNo.':D'.$XLSRowNo)->applyFromArray($BStyle);
        $XLSRowNo++;       
        $mainTotal += $estVal->field_est_line_item_amt_value;       
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( get_description_by_cost_code_mod($estVal->field_est_cost_code_value) ) );
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':C'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $estVal->field_est_line_item_amt_value ) );
        $XLSRowNo++;
      }

      $XLSRowNo++;
      $XLSRowNo++;
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Capital Total' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':C'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $mainTotal ) );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B' . ($XLSRowNo).':D' . ($XLSRowNo))->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $XLSRowNo++;
      $XLSRowNo++;
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'B' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( 'Total' ) );
      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'C' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C' . ($XLSRowNo).':C'.($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($XLSRowNo), utf8_encode ( $mainTotal ) );
      
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B' . ($XLSRowNo).':D' . ($XLSRowNo))->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');   
    }
    elseif ($type == 'asset') {
      // If asset type report is requested.
      $XLSRowNo = ($nextReport == 0) ? $XLSRowNo : $nextReport;

      $reportTitle = t('PROJECT CLOSE OUT/ ASSET CAPITALIZATION REQUEST FORM');
      $projectName = $projectDetails->title;
      $projectNumber = $projectDetails->field_project_mgmt_number['und'][0]['value'];
      $date_of_request = date('d/m/Y');

      $projectLocID = _get_company_region_address($company);
      $arr_index = $XLSRowNo + 1;
      $projectDetailsArr = array($arr_index => t('Site/Location'));
      $projectDetailsArr[] = t('Date of Request');
      $projectDetailsArr[] = t('Project Number');
      $projectDetailsArr[] = t('Project Name');
      $projectDetailsArr[] = t('Closeout Requestor');
      $projectDetailsArr[] = t('Contact Phone Number');
      $projectDetailsArr[] = t('Closeout Total');

      $projectDetailsArr2 = array($arr_index => $projectLocID);
      $projectDetailsArr2[] = $date_of_request;
      $projectDetailsArr2[] = $projectNumber;
      $projectDetailsArr2[] = $projectName;
      $projectDetailsArr2[] = t('Name Here');
      $projectDetailsArr2[] = t('Contact Phone Number Here');
      $projectDetailsArr2[] = t('Closeout Total Here');

      // if($gdImageType == 'jpeg') {
      //   $gdImage = imagecreatefromjpeg ( $companyLogo );
      // }
      // else {
      //   $gdImage = imagecreatefrompng ( $companyLogo );
      // }

      // $objDrawing = new PHPExcel_Worksheet_MemoryDrawing();
      // $objDrawing->setName ( 'Sample image' );
      // $objDrawing->setDescription ( 'Sample image' );
      // $objDrawing->setImageResource ( $gdImage );
      // $objDrawing->setRenderingFunction ( PHPExcel_Worksheet_MemoryDrawing::RENDERING_JPEG );
      // $objDrawing->setMimeType ( PHPExcel_Worksheet_MemoryDrawing::MIMETYPE_DEFAULT );
      // $objDrawing->setHeight ( 62 );
      // $colindex = excelgeneratorurl_get_colindex( 1 );
      // $objDrawing->setCoordinates( $colindex . ($XLSRowNo) );
      // $objDrawing->setWorksheet ( $_excelexport_objPHPExcel->getActiveSheet () );
      // //$XLSRowNo++;$XLSRowNo++;
      // $endData = $XLSRowNo+3;
      // $rowFills = 'B'.$XLSRowNo.':M'.$endData;
      // $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      // $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindex . ($XLSRowNo) )->getFont ()->setBold ( true );
      // $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C'.$XLSRowNo, utf8_encode ( $reportTitle ) );

      // $XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;$XLSRowNo++;

      // $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B'.$XLSRowNo, utf8_encode ( $projectName ) );
      // $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'D'.$XLSRowNo, utf8_encode ( $projectNumber ) );

      // $XLSRowNo++; $XLSRowNo++;

      $rowFills = 'A'.$XLSRowNo.':T'.$XLSRowNo;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':T'.$XLSRowNo); // Merging A1:T1

      $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,)); // Applying borders
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':S'.($XLSRowNo))->applyFromArray($BStyle);

      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode($reportTitle));

      // Setting Project Details AB4 - AB10, CD4 - CD10. //FFFF99
      for ($i = $arr_index; $i < $arr_index + 7; $i++) {
        $rowFills = 'A'.$i.':B'.$i;
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FFFF99');

        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_RIGHT,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($i).':B'.($i))->applyFromArray($BStyle);

        $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$i.':B'.$i); // Merging A1:B1
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($i) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($i), utf8_encode($projectDetailsArr[$i]));

        $rowFills = 'C'.$i.':E'.$i;
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FFFF99');

        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('C'. ($i).':E'.($i))->applyFromArray($BStyle);

        $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('C'.$i.':E'.$i); // Merging C1:E1
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'C' . ($i), utf8_encode($projectDetailsArr2[$i]));
      }

      // $XLSRowNo here is 1. Making it 4.
      $XLSRowNo += 3;

      // Merging H3:P3, H4:P4, H5:P5.
      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('H'.$XLSRowNo.':P'.$XLSRowNo); // Merging H3:P3
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode(t('Required - All items with Required in yellow have to be filled in with valid information')));

      $XLSRowNo++; // Row No 5

      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('H'.$XLSRowNo.':P'.$XLSRowNo); // Merging H3:P3
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode(t('GFS - All items with NASS in yellow are items that NASS Fixed Assets will complete when the form is received')));

      $XLSRowNo++; // Row No 6

      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('H'.$XLSRowNo.':P'.$XLSRowNo); // Merging H3:P3
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'H' . ($XLSRowNo), utf8_encode(t('Optional - All items labeled optional are there for the sites to be able to provide as much information as needed to accurately track assets.')));

      $XLSRowNo += 4; // Row No 10;

      $header_arr = array('New Asset Number', 'Company', 'Dept', 'Project Number', 'AssetClass', 'Location', 'Asset Description', 'Description 2', 'Serial #', 'Model No #', 'Vendor Number', 'Vendor Name', 'Acquisition Date', 'Acquisition Cost', 'Quantity', 'GL Account Code', 'State', 'County', 'City');

      for ($i = 0; $i < 19 ; $i++) {
        $colindexx = excelgeneratorurl_get_colindex ($i);

        if ($i == 0) {
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('C0C0C0');
        }
        else {
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');
        }

        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $header_arr[$i] ) );
      }


      // Getting Assets by project ID.
      $query = db_select('node','n');
      $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');    
      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->fields('n',array('nid'));
      $query->condition('n.type', 'program_assets', '=');
      $query->condition('om.gid', $company->nid, '=');
      $query->condition('pr.field_project_reference_nid', $projectDetails->nid, '=');
      $getAssetData = $query->execute()->fetchCol();
      if (!empty($getAssetData)) {
        // If we have some assets to work on.
        $totalAssetVal = 0;
        foreach ($getAssetData as $assetKey => $assetVal) {
          $XLSRowNo++;
          $assetData = node_load($assetVal);

          $assetNumber = !empty($assetData->field_system_asset_number['und'][0]['value']) ? $assetData->field_system_asset_number['und'][0]['value'] : '';
          $dept = ''; // Find
          $assetClass = $assetData->field_system_asset_type['und'][0]['value']; // Asset Class ID.
          if (!empty($assetClass)) {
            $ass_cat_query = db_select('m6connect_project_asset_category', 'c')
              ->fields('c', array('category_type'))
              ->condition('id', $assetClass)
              ->execute()
              ->fetchField();
            if (!empty($ass_cat_query)) {
              // Asset Class Name.
              $assetClassName = $ass_cat_query;
            }
          }
          
          $assetDesc = $assetData->field_project_asset_sin_number['und'][0]['value']; // Asset SIN Number/Desc
          $assetSerial = $assetData->field_asset_pin_number['und'][0]['value']; // Asset Serial Number.
          $assetModel = $assetData->field_asset_model_no['und'][0]['value']; // Asset Model Number.
          // Asset Vendor Name.
          $asset_vendor_id = isset($assetData->field_asset_vendor['und'][0]['value']) ? $assetData->field_asset_vendor['und'][0]['value'] : '';
          $asset_vendor_name = '';
          if (!empty($asset_vendor_id) && is_numeric($asset_vendor_id) && $asset_vendor_node = node_load($asset_vendor_id)) {
            $asset_vendor_name = $asset_vendor_node->title;
          }
          elseif (!empty($asset_vendor_id) && !is_numeric($asset_vendor_id) && is_string($asset_vendor_id)) {
            $asset_vendor_name = $asset_vendor_id;
          }

          $assetAcqDate = '';
          $assetAcqCost = 0;
          if (isset($assetData->field_asset_cost['und'][0]['value'])) {
            $assetAcqCost += $assetData->field_asset_cost['und'][0]['value'];
          }
          if (isset($assetData->field_asset_installation['und'][0]['value'])) {
            $assetAcqCost += $assetData->field_asset_installation['und'][0]['value'];
          }
          if (isset($assetData->field_asset_outside_consultant['und'][0]['value'])) {
            $assetAcqCost += $assetData->field_asset_outside_consultant['und'][0]['value'];
          }
          if (isset($assetData->field_asset_internal_charge['und'][0]['value'])) {
            $assetAcqCost += $assetData->field_asset_internal_charge['und'][0]['value'];
          }
          $totalAssetVal += $assetAcqCost;

          $assetQuan = 1; // Confirm.
          $row_arr = array($assetNumber, $company->title, '', $projectNumber, !empty($assetClassName) ? $assetClassName : '', $projectLocID, $assetDesc, '', $assetSerial, $assetModel, '', $asset_vendor_name, '', $assetAcqCost, $assetQuan, '',  '', '', '', );

          for ($i = 0; $i < 19 ; $i++) {
            $colindexx = excelgeneratorurl_get_colindex ($i);
            if ($i == 13) {
              $_excelexport_objPHPExcel->getActiveSheet()->getStyle($colindexx . ($XLSRowNo).':' . $colindexx .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');

              $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_RIGHT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
              $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);
            }
            elseif ($i == 14) {
              $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
              $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);
            }
            elseif ($i == 0) {
              $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');

              $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
              $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);
            }
            else {
              $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
              $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);
            }
            $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $row_arr[$i] ) );
          }
          
          // $XLSRowNo++;
        }
        // Total Asset Value.
        $XLSRowNo += 2;

        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'M' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'M' . ($XLSRowNo), utf8_encode ( 'Total' ));

        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'N' . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle('N' . ($XLSRowNo).':N' .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'N' . ($XLSRowNo), utf8_encode ( $totalAssetVal ));
      }
    }

      $nextReport = $XLSRowNo + 7;
    //$_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( $nextReport ) );
      $checkFirst++;
  }
  if($type == 'monthly') {
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )));
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(50);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(40);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' );
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="MonthlyReport.xlsx"' ); 
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );  
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
  }
  if($type == 'costsummary') {
    $XLSRowNo++; $XLSRowNo++;   
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="ProjectCostSummaryReport.xlsx"' );  
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );  
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B8:I8')->applyFromArray($BStyle);    
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('I')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' );
  }
  else if($type == 'commitment') {
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="ProjectCommitmentReport.xlsx"' ); 
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )));
    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('D2:E2');
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' ); 
  }
  else if($type == 'safety') {
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="ProjectSafetyReport.xlsx"' ); 
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )));
    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('D2:G2');
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' ); 
  }
  else if($type == 'costdetail') {
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="ProjectCostDetailReport.xlsx"' ); 
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );  
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('B8:I8')->applyFromArray($BStyle);
    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('E1:F1'); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(20);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('I')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' );
  }
  else if($type == 'estimate') {
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="BudgetEstimateReport.xlsx"' );  
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
    //$_excelexport_objPHPExcel->getActiveSheet()->getStyle('B7:D7')->applyFromArray($BStyle);    
    
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(50);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(40);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(20); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' );
  }
  elseif ($type == 'asset') {
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="ProjectAssetReports.xlsx"' );  
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
    //$_excelexport_objPHPExcel->getActiveSheet()->getStyle('B7:D7')->applyFromArray($BStyle);    
    
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(25);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(15);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(40); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(25); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('I')->setWidth(40); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('R')->setWidth(10); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('S')->setWidth(10); 
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('T')->setWidth(10); 
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->save ( 'php://output' );
  }

  // Generating Reports for Project Spending Forecasts.
  if ($type == 'spending-forecast') {
    $XLSRowNo = 1;
    // In Spending forecast, we need to generate summary of all projects on
    // Page 1 and then detailed description of each project from Page 2.
    $reportTitle = t('Project Spending Forecasts');

    // Creating Report Title.
    $rowFills = 'A'.$XLSRowNo.':H'.$XLSRowNo;
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');
    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':H'.$XLSRowNo); // Merging A1:T1

    $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER,)); // Applying borders
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':H'.($XLSRowNo))->applyFromArray($BStyle);

    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode($reportTitle));

    $XLSRowNo += 2; // Row 3;

    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':F'.$XLSRowNo); // Merging A1:T1

    $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT,)); // Applying borders
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':F'.($XLSRowNo))->applyFromArray($BStyle);

    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode(t('Summary')));

    $XLSRowNo += 2; // Row 5;


    $cyr_year = date('Y');
    $summary_header = array(t('Project'), t('Previous Year Total'), $cyr_year . ' ' . t('Spending'), t('Future Year Total'), t('Spent To Date'), t('PFC'));

    for ($i = 0; $i <= count($summary_header) - 1; $i++) {
      $colindexx = excelgeneratorurl_get_colindex ($i);
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');

      $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $summary_header[$i] ) );
    }

    $XLSRowNo++; // Row 3;

    $last_forecast_arr = array(); // For Summary
    $last_forecast_arr_commit = array(); // For details
    $last_forecast_arr_etc = array(); // For details
    foreach($costProId as $proID) {
      // Trying to get Forecast details.
      $query = db_select('m6connect_spending_forecast','sf');
      $query->distinct('sf.forecast_name');
      $query->fields('sf', array('forecast_name'));
      $query->condition('sf.project_id', $proID);
      $getForecastName = $query->execute()->fetchCol();

      if (!empty($getForecastName)) {
        $last_forecast_arr[$proID] = $getForecastName[count($getForecastName) - 1];
      }
      else {
        $last_forecast_arr[$proID] = NULL;
      }
    }

    foreach ($last_forecast_arr as $key => $forecast) {
      $projectSpending = node_load($key);
      $pSTitle = $projectSpending->title;

      if (!empty($forecast)) {
        $query= db_select('node','n');
        $query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');   
        $query->fields('n', array('nid'));
        $query->condition('pr.field_project_reference_nid', $key, '=');
        $query->condition('pr.bundle','project_commitement','=');
        $getCommitmentNodes = $query->execute()->fetchCol();

        $getCurrentYearAmt = 0;
        $getFutureAmt = 0;
        $getVarienceAmt = 0;
        $finalPreviousYearTotal = 0;

        foreach($getCommitmentNodes as $commitKey => $commitVal) {
          $getCommitData = node_load($commitVal);

          $query = db_select('m6connect_spending_forecast', 'sf');
          $query->fields('sf', array('quarter_one_amount','quarter_two_amount', 'quarter_three_amount','quarter_four_text_amount','quarter_four_amount','current_year_spending_amount','future_year_amout','variance_amount'));
          $query->condition('sf.forecast_name', $forecast, '=');
          $query->condition('sf.project_id', $key, '=');
          $query->condition('sf.commitment_id', $getCommitData->nid, '=');
          $forecastData = $query->execute()->fetchAll();

          $getCurrentYearAmt += $forecastData[0]->current_year_spending_amount;
          $getFutureAmt += $forecastData[0]->future_year_amout;
          $getVarienceAmt += $forecastData[0]->variance_amount;
          $getPreviousYearTotal = _get_previous_year_spending_total($key,$getCommitData->nid);
          $finalPreviousYearTotal += $getPreviousYearTotal;
        }

        $query= db_select('node','n'); 
        $query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
        $query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
        $query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');  
        $query->join('field_data_field_project_estimate_amount','ea','ea.entity_id = enode.nid');    
        $query->join('field_data_field_capital_contingency','ecc','ecc.entity_id = enode.nid');      
        $query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');  
        $query->leftjoin('field_data_field_est_line_item_amt','la','n.nid=la.entity_id');
        $query->leftjoin('field_data_field_conigency_percentage','cp','n.nid=cp.entity_id');  
        $query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
        $query->fields('cc',array('entity_id'));
        $query->fields('la',array('field_est_line_item_amt_value'));
        $query->fields('cp',array('field_conigency_percentage_value'));
        $query->fields('cc',array('field_est_cost_code_value'));
        $query->fields('ea',array('field_project_estimate_amount_value'));  
        $query->fields('ecc',array('field_capital_contingency_value'));  
        $query->fields('er',array('field_estimate_reference_nid'));  
        $query->condition('es.field_project_estimate_status_value', 'approved', '=');
        $query->orderBy('cc.field_est_cost_code_value', 'ASC');
        $query->condition('pr.field_project_reference_nid', $key, '=');
        $costCode = $query->execute()->fetchAll();  
        $ccArr = array();
        $ccArrCount = array();

        $totalFinalCost = 0;
        $totalInvoiceTotal = 0;

        module_load_include('inc', 'm6connect_program', 'includes/cost.summary');
        foreach($costCode as $ccId => $ccVal) {
          // Get cost code
          // $getCcDes = db_select('node','n'); 
          // $getCcDes->join('field_data_field_manager_cost_code','mcc','mcc.entity_id = n.nid'); 
          // $getCcDes->join('field_data_field_cost_code_description','ccd','ccd.entity_id = n.nid');    
          // $getCcDes->fields('ccd',array('field_cost_code_description_value'));
          // $getCcDes->condition('mcc.field_manager_cost_code_value',$ccVal->field_est_cost_code_value, '=');
          // $costCodeDes = $getCcDes->execute()->fetchField();        
          // $costCode = $ccVal->field_est_cost_code_value.'|'.$costCodeDes; 
            // Get Original budget 
          $capitalContigency = $ccVal->field_capital_contingency_value; 
          if (!isset($ccArr[$ccVal->field_est_cost_code_value])) {
            $ccArr[$ccVal->field_est_cost_code_value]= array(
              // 'cc' => $ccVal->field_est_cost_code_value,
              // 'cost_code' => $ccVal->field_est_cost_code_value.'|'.$costCodeDes,
              'originalBudget' => 0,
              'currentBudget' => 0,
              'Commitment' => 0,
              'spent' => 0,
              'Allocated' => 0,
              'est' => 0,
              'PFC' => 0,
              'Variance' => 0,
            );
            $ccArrCount[$ccVal->field_est_cost_code_value] = 0; 
          }   
          if ($ccVal->field_est_line_item_amt_value != '') {
            $originalBudget = $ccVal->field_est_line_item_amt_value;
          }
          elseif ($ccVal->field_conigency_percentage_value != '') {
            $percent = ($ccVal->field_project_estimate_amount_value * $ccVal->field_conigency_percentage_value)/100;      
            $originalBudget = $percent;
          }
          $totalOriginalBudget += $originalBudget;
          $currentBudget = $originalBudget;
          $totalcurrentBudget += $currentBudget;
            // Get invoice total
          $getInvoiceTotal = get_invoice_total_by_cost_code_inc($ccVal->field_est_cost_code_value,$proId);
          $totalInvoiceTotal += $getInvoiceTotal;
          // Get commitment total
          $getCommitmentTotal = get_commitment_total_by_cost_code_inc($ccVal->field_est_cost_code_value,$proId);
          
          $totalCommitmentTotal += $getCommitmentTotal;
          // Get total allocated 
          $getTotalAllocated = get_total_allocated_by_cost_code_inc($ccVal->field_est_cost_code_value,$proId,$getCommitmentTotal);
          $totalAllocated += $getTotalAllocated;
          // Get etc total
          $getETCTotal = get_etc_total_by_cost_code_inc($ccVal->field_est_cost_code_value,$proId);
          $etcTotal += $getETCTotal;
          // Get Project final cost
          $projectFinalCost = $getTotalAllocated + $getETCTotal;
          $totalFinalCost += $projectFinalCost;
          // Variance
          $varience = $originalBudget - $projectFinalCost;
          $totalVariance += $varience;      
            $ccArr[$ccVal->field_est_cost_code_value]['cc'] = $ccVal->field_est_cost_code_value;  
          $ccArr[$ccVal->field_est_cost_code_value]['originalBudget'] += $originalBudget; 
          $ccArr[$ccVal->field_est_cost_code_value]['currentBudget'] += $currentBudget;
          $ccArr[$ccVal->field_est_cost_code_value]['Commitment'] = $getCommitmentTotal;
          $ccArr[$ccVal->field_est_cost_code_value]['spent'] = $getInvoiceTotal;
          $ccArr[$ccVal->field_est_cost_code_value]['Allocated'] = $getTotalAllocated;
          $ccArr[$ccVal->field_est_cost_code_value]['est'] = $getETCTotal;
          $ccArr[$ccVal->field_est_cost_code_value]['PFC'] = $projectFinalCost;
          $ccArr[$ccVal->field_est_cost_code_value]['Variance'] = $varience;
          $ccArrCount[$ccVal->field_est_cost_code_value]++;
        }

        $summary_row = array($pSTitle, $finalPreviousYearTotal, $getCurrentYearAmt, $getFutureAmt, $totalInvoiceTotal, $projectFinalCost);

        for ($i = 0; $i <= count($summary_row) - 1; $i++) {
          $colindexx = excelgeneratorurl_get_colindex ($i);

          $_excelexport_objPHPExcel->getActiveSheet()->getStyle($colindexx . ($XLSRowNo).':' . $colindexx .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');

          $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $summary_row[$i] ) );
        }
      }
      else {
        // Just showing that no forecast available.
        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( 'A' . ($XLSRowNo))->applyFromArray($BStyle);
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode ( $pSTitle ) );

        $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('B'.$XLSRowNo.':F'.$XLSRowNo);
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( 'B' . ($XLSRowNo))->applyFromArray($BStyle);
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( t('No spending forecast found!') ) );
      }

      $XLSRowNo++;
    }

    $XLSRowNo += 2;

    // Generating detailed reports.
    $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':L'.$XLSRowNo); // Merging A1:T1

    $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT,)); // Applying borders
    $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':M'.($XLSRowNo))->applyFromArray($BStyle);

    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
    $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode(t('Details')));

    $XLSRowNo += 2;

    foreach ($last_forecast_arr as $key => $forecast) {
      if (empty($forecast)) {
        continue;
      }
      $projectSpending = node_load($key);
      $pSTitle = $projectSpending->title;

      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':M'.$XLSRowNo); // Merging A1:T1

      $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT,)); // Applying borders
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':M'.($XLSRowNo))->applyFromArray($BStyle);

      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode($pSTitle));

      $XLSRowNo++;


      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':M'.$XLSRowNo); // Merging A1:T1

      $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT,)); // Applying borders
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':M'.($XLSRowNo))->applyFromArray($BStyle);

      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode(t('Commitment Forecast')));

      $XLSRowNo++;

      // Making header.
      $detail_header = array(
        t('Commitment Number'),
        t('Company Name'),
        t('Amount'),
        t('Total Spent'),
        t('Previous Years'),
        date('Y') . ' ' . t('Quarter 1'),
        date('Y') . ' ' . t('Quarter 2'),
        date('Y') . ' ' . t('Quarter 3'),
        date('Y') . ' ' . t('Quarter 4'),
        date('Y') . ' ' . t('Spending'),
        t('Future Years'),
        t('Variance'),
      );

      $currentQuarter = _get_current_quarter(date('n'));
      $i = 0;
      foreach ($detail_header as $d_key => $d_val) {
        $colindexx = excelgeneratorurl_get_colindex ($i);
        if ($currentQuarter == 'firstQuarter') {
          if ($i == 5) {
            $i++;
            $nextcolindexx = excelgeneratorurl_get_colindex ($i);
            $_excelexport_objPHPExcel->getActiveSheet()->mergeCells($colindexx . $XLSRowNo . ':' . $nextcolindexx . $XLSRowNo);
          }
        }
        if ($currentQuarter == 'secondQuarter') {
          if ($i == 6) {
            $i++;
            $nextcolindexx = excelgeneratorurl_get_colindex ($i);
            $_excelexport_objPHPExcel->getActiveSheet()->mergeCells($colindexx . $XLSRowNo . ':' . $nextcolindexx . $XLSRowNo);
          }
        }
        if ($currentQuarter == 'thirdQuarter') {
          if ($i == 7) {
            $i++;
            $nextcolindexx = excelgeneratorurl_get_colindex ($i);
            $_excelexport_objPHPExcel->getActiveSheet()->mergeCells($colindexx . $XLSRowNo . ':' . $nextcolindexx . $XLSRowNo);
          }
        }
        if ($currentQuarter == 'fourthQuarter') {
          if ($i == 8) {
            $i++;
            $nextcolindexx = excelgeneratorurl_get_colindex ($i);
            $_excelexport_objPHPExcel->getActiveSheet()->mergeCells($colindexx . $XLSRowNo . ':' . $nextcolindexx . $XLSRowNo);
          }
        }
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');
        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $d_val ) );
        $i++;
      } // Finished making header for each project.

      $XLSRowNo++;
      $sum_start = $XLSRowNo; // Used to start the sum from here.
      // Now getting data and filling in.

      $query= db_select('node','n');
      $query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');   
      $query->fields('n', array('nid'));
      $query->condition('pr.field_project_reference_nid', $key, '=');
      $query->condition('pr.bundle','project_commitement','=');
      $getCommitmentNodes = $query->execute()->fetchCol();
      foreach($getCommitmentNodes as $commitKey => $commitVal) {
        $getCommitData = node_load($commitVal);
        $getCurrentYearAmt = 0;
        $getFutureAmt = 0;
        $getVarienceAmt = 0;

        if (!empty($forecast)) {
          $query = db_select('m6connect_spending_forecast', 'sf');
          $query->fields('sf', array('quarter_one_amount','quarter_two_amount', 'quarter_three_amount','quarter_four_text_amount','quarter_four_amount','current_year_spending_amount','future_year_amout','variance_amount'));
          $query->condition('sf.forecast_name', $forecast, '=');
          $query->condition('sf.project_id', $key, '=');
          $query->condition('sf.commitment_id', $getCommitData->nid, '=');
          $forecastData = $query->execute()->fetchAll();
          $getCurrentYearAmt = !empty($forecastData[0]->current_year_spending_amount) ? $forecastData[0]->current_year_spending_amount : 0;
          $getFutureAmt = !empty($forecastData[0]->future_year_amout) ? $forecastData[0]->future_year_amout : 0;
          $getVarienceAmt = !empty($forecastData[0]->variance_amount) ? $forecastData[0]->variance_amount : 0;
        }

        $commitNumber = $getCommitData->field_commitment_number_calculat['und'][0]['value'];

        if (isset($getCommitData->field_vendor['und']) && is_numeric($getCommitData->field_vendor['und'][0]['value'])) {
          $companyName = node_load($getCommitData->field_vendor['und'][0]['value'])->title;
        }
        else {
          $companyName = $getCommitData->field_vendor['und'][0]['value'];
        }

        $commitAmt = $getCommitData->field_commitment_po_final_total['und'][0]['value'] != '' ? $getCommitData->field_commitment_po_final_total['und'][0]['value'] : 0;
        // Get invoice spending amount
        $query= db_select('node','n'); 
        $query->join('field_data_field_invoice_commitment','ic','ic.entity_id = n.nid');
        $query->join('field_data_field_invoice_amount','ia','ia.entity_id = n.nid');
        $query->addExpression('SUM(ia.field_invoice_amount_value)','finalTotal');
        $query->condition('n.type','project_spending','=');
        $query->condition('ic.field_invoice_commitment_nid',$getCommitData->nid,'=');
        $query->groupBy('ic.field_invoice_commitment_nid');
        $getTotalSpending = $query->execute()->fetchField();
        $invoice = $getTotalSpending != '' ? $getTotalSpending : 0;
        $subtotalInv += $invoice;
        $subTotalCommitment += $getCommitData->field_commitment_po_final_total['und'][0]['value'];
        // Get quarter value for etc
        $defaultAmt = 0;
        $$quarterOneCol = '';
        $quarterTwoCol = '';
        $quarterThreeCol = '';
        $quarterFourCol = ''; 
        
        $getPrevQuarterOne = 0;  
        $getPrevQuarterTwo = 0;
        $getPrevQuarterThree = 0;
        $getPrevQuarterFour = 0;
        $getPrevQuarterFourText = 0;

          
        if ($currentQuarter == 'firstQuarter') {
          if (!empty($forecastData)) {
            $getPrevQuarterOne = $forecastData[0]->quarter_one_amount;
            $getPrevQuarterTwo = $forecastData[0]->quarter_two_amount;
            $getPrevQuarterThree = $forecastData[0]->quarter_three_amount;
            $getPrevQuarterFour = $forecastData[0]->quarter_four_amount;
          } 
          $startDateOneQuarter = date('Y').'-01-01 00:00:00';
          $startDateTwoQuarter = date('Y').'-04-01 00:00:00';
          $startDateThirdQuarter = date('Y').'-07-01 00:00:00';
          $startDateFourthQuarter = date('Y').'-10-01 00:00:00';

          $getCurrentquarter = $getPrevQuarterOne;

          $getPrevQuarterOneTot = _get_spending_total_by_quarter($startDateOneQuarter,date('Y').'-03-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterTwoTot = _get_spending_total_by_quarter($startDateTwoQuarter,date('Y').'-06-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterThreeTot = _get_spending_total_by_quarter($startDateThirdQuarter,date('Y').'-09-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterFourTot = _get_spending_total_by_quarter($startDateFourthQuarter,date('Y').'12-31 00:00:00',$key,$getCommitData->nid, TRUE);
        }

        if ($currentQuarter == 'secondQuarter') {
          if (!empty($forecastData)) {
            $getPrevQuarterOne = $forecastData[0]->quarter_one_amount;
            $getPrevQuarterTwo = $forecastData[0]->quarter_two_amount;
            $getPrevQuarterThree = $forecastData[0]->quarter_three_amount;
            $getPrevQuarterFour = $forecastData[0]->quarter_four_amount;
          }
          $startDateOneQuarter = date('Y').'-01-01 00:00:00';
          $startDateTwoQuarter = date('Y').'-04-01 00:00:00';
          $startDateThirdQuarter = date('Y').'-07-01 00:00:00';
          $startDateFourthQuarter = date('Y').'-10-01 00:00:00';

          $getCurrentquarter = $getPrevQuarterTwo;


          $getPrevQuarterOneTot = _get_spending_total_by_quarter($startDateOneQuarter,date('Y').'-03-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterTwoTot = _get_spending_total_by_quarter($startDateTwoQuarter,date('Y').'-06-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterThreeTot = _get_spending_total_by_quarter($startDateThirdQuarter,date('Y').'-09-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterFourTot = _get_spending_total_by_quarter($startDateFourthQuarter,date('Y').'12-31 00:00:00',$key,$getCommitData->nid, TRUE);
        }

        if ($currentQuarter == 'thirdQuarter') {
          if (!empty($forecastData)) {
            $getPrevQuarterOne = $forecastData[0]->quarter_one_amount;
            $getPrevQuarterTwo = $forecastData[0]->quarter_two_amount;
            $getPrevQuarterThree = $forecastData[0]->quarter_three_amount;
            $getPrevQuarterFour = $forecastData[0]->quarter_four_amount;
          } 
          $startDateOneQuarter = date('Y').'-01-01 00:00:00';
          $startDateTwoQuarter = date('Y').'-04-01 00:00:00';
          $startDateThirdQuarter = date('Y').'-07-01 00:00:00';
          $startDateFourthQuarter = date('Y').'-10-01 00:00:00';

          $getCurrentquarter = $getPrevQuarterThree;
          
          $getPrevQuarterOneTot = _get_spending_total_by_quarter($startDateOneQuarter,date('Y').'-03-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterTwoTot = _get_spending_total_by_quarter($startDateTwoQuarter,date('Y').'-06-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterThreeTot = _get_spending_total_by_quarter($startDateThirdQuarter,date('Y').'-09-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterFourTot = _get_spending_total_by_quarter($startDateFourthQuarter,date('Y').'12-31 00:00:00',$key,$getCommitData->nid, TRUE);
        }

        if ($currentQuarter == 'fourthQuarter') {
          if (!empty($forecastData)) {
            $getPrevQuarterOne = $forecastData[0]->quarter_one_amount;
            $getPrevQuarterTwo = $forecastData[0]->quarter_two_amount;
              $getPrevQuarterThree = $forecastData[0]->quarter_three_amount;
            $getPrevQuarterFour = $forecastData[0]->quarter_four_amount;
            $getPrevQuarterFourText = $forecastData[0]->quarter_four_text_amount;
          }
          $startDateOneQuarter = date('Y').'-01-01 00:00:00';
          $startDateTwoQuarter = date('Y').'-04-01 00:00:00';
          $startDateThirdQuarter = date('Y').'-07-01 00:00:00';
          $startDateFourthQuarter = date('Y').'-10-01 00:00:00';

          $getCurrentquarter = $startDateFourthQuarter;
          
          $getPrevQuarterOneTot = _get_spending_total_by_quarter($startDateOneQuarter,date('Y').'-03-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterTwoTot = _get_spending_total_by_quarter($startDateTwoQuarter,date('Y').'-06-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterThreeTot = _get_spending_total_by_quarter($startDateThirdQuarter,date('Y').'-09-31 00:00:00',$key,$getCommitData->nid, TRUE);
          $getPrevQuarterFourTot = _get_spending_total_by_quarter($startDateFourthQuarter,date('Y').'12-31 00:00:00',$key,$getCommitData->nid, TRUE);
        }

        $getPreviousYearTotal = _get_previous_year_spending_total($key,$getCommitData->nid);
        $finalPreviousYearTotal += $getPreviousYearTotal;

        $i = 0;

        if ($currentQuarter == 'firstQuarter') {
          $detail_row = array(
            $commitNumber,
            $companyName != '' ? ucwords($companyName) : t('None'),
            $commitAmt,
            $invoice,
            $getPreviousYearTotal,
            $getCurrentquarter,
            $getPrevQuarterOneTot,
            $getPrevQuarterTwoTot,
            $getPrevQuarterThreeTot,
            $getPrevQuarterFourTot,
            $getCurrentYearAmt,
            $getFutureAmt,
            $getVarienceAmt,
          );
          $detail_row_total['commitAmt'] += $commitAmt;
          $detail_row_total['invoice'] += $invoice;
          $detail_row_total['getPreviousYearTotal'] += $getPreviousYearTotal;
          $detail_row_total['getCurrentquarter'] += $getCurrentquarter;
          $detail_row_total['getPrevQuarterOne'] += $getPrevQuarterOneTot;
          $detail_row_total['getPrevQuarterTwo'] += $getPrevQuarterTwoTot;
          $detail_row_total['getPrevQuarterThree'] += $getPrevQuarterThreeTot;
          $detail_row_total['getPrevQuarterFour'] += $getPrevQuarterFourTot;
          $detail_row_total['getCurrentYearAmt'] += $getCurrentYearAmt;
          $detail_row_total['getFutureAmt'] += $getFutureAmt;
          $detail_row_total['getVarienceAmt'] += $getVarienceAmt;
        }
        if ($currentQuarter == 'secondQuarter') {
          $detail_row = array(
            $commitNumber,
            $companyName != '' ? ucwords($companyName) : t('None'),
            $commitAmt,
            $invoice,
            $getPreviousYearTotal,
            $getPrevQuarterOneTot,
            $getCurrentquarter,
            $getPrevQuarterTwoTot,
            $getPrevQuarterThreeTot,
            $getPrevQuarterFourTot,
            $getCurrentYearAmt,
            $getFutureAmt,
            $getVarienceAmt,
          );
          $detail_row_total['commitAmt'] += $commitAmt;
          $detail_row_total['invoice'] += $invoice;
          $detail_row_total['getPreviousYearTotal'] += $getPreviousYearTotal;
          $detail_row_total['getPrevQuarterOne'] += $getPrevQuarterOneTot;
          $detail_row_total['getCurrentquarter'] += $getCurrentquarter;
          $detail_row_total['getPrevQuarterTwo'] += $getPrevQuarterTwoTot;
          $detail_row_total['getPrevQuarterThree'] += $getPrevQuarterThreeTot;
          $detail_row_total['getPrevQuarterFour'] += $getPrevQuarterFourTot;
          $detail_row_total['getCurrentYearAmt'] += $getCurrentYearAmt;
          $detail_row_total['getFutureAmt'] += $getFutureAmt;
          $detail_row_total['getVarienceAmt'] += $getVarienceAmt;
        }
        if ($currentQuarter == 'thirdQuarter') {
          $detail_row = array(
            $commitNumber,
            $companyName != '' ? ucwords($companyName) : t('None'),
            $commitAmt,
            $invoice,
            $getPreviousYearTotal,
            $getPrevQuarterOneTot,
            $getPrevQuarterTwoTot,
            $getCurrentquarter,
            $getPrevQuarterThreeTot,
            $getPrevQuarterFourTot,
            $getCurrentYearAmt,
            $getFutureAmt,
            $getVarienceAmt,
          );
          $detail_row_total['commitAmt'] += $commitAmt;
          $detail_row_total['invoice'] += $invoice;
          $detail_row_total['getPreviousYearTotal'] += $getPreviousYearTotal;
          $detail_row_total['getPrevQuarterOne'] += $getPrevQuarterOneTot;
          $detail_row_total['getPrevQuarterTwo'] += $getPrevQuarterTwoTot;
          $detail_row_total['getCurrentquarter'] += $getCurrentquarter;
          $detail_row_total['getPrevQuarterThree'] += $getPrevQuarterThreeTot;
          $detail_row_total['getPrevQuarterFour'] += $getPrevQuarterFourTot;
          $detail_row_total['getCurrentYearAmt'] += $getCurrentYearAmt;
          $detail_row_total['getFutureAmt'] += $getFutureAmt;
          $detail_row_total['getVarienceAmt'] += $getVarienceAmt;
        }
        if ($currentQuarter == 'fourthQuarter') {
          $detail_row = array(
            $commitNumber,
            $companyName != '' ? ucwords($companyName) : t('None'),
            $commitAmt,
            $invoice,
            $getPreviousYearTotal,
            $getPrevQuarterOneTot,
            $getPrevQuarterTwoTot,
            $getPrevQuarterThreeTot,
            $getCurrentquarter,
            $getPrevQuarterFourTot,
            $getCurrentYearAmt,
            $getFutureAmt,
            $getVarienceAmt,
          );
          $detail_row_total['commitAmt'] += $commitAmt;
          $detail_row_total['invoice'] += $invoice;
          $detail_row_total['getPreviousYearTotal'] += $getPreviousYearTotal;
          $detail_row_total['getPrevQuarterOne'] += $getPrevQuarterOneTot;
          $detail_row_total['getPrevQuarterTwo'] += $getPrevQuarterTwoTot;
          $detail_row_total['getPrevQuarterThree'] += $getPrevQuarterThreeTot;
          $detail_row_total['getCurrentquarter'] += $getCurrentquarter;
          $detail_row_total['getPrevQuarterFour'] += $getPrevQuarterFourTot;
          $detail_row_total['getCurrentYearAmt'] += $getCurrentYearAmt;
          $detail_row_total['getFutureAmt'] += $getFutureAmt;
          $detail_row_total['getVarienceAmt'] += $getVarienceAmt;
        }


        for ($i = 0; $i <= count($detail_row) - 1; $i++) {
          $colindexx = excelgeneratorurl_get_colindex ($i);
          // $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');
          $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_RIGHT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders

          $_excelexport_objPHPExcel->getActiveSheet()->getStyle($colindexx . ($XLSRowNo).':' . $colindexx .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');

          $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

          // $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $detail_row[$i] ) );
        }

        $XLSRowNo++;
      }

      $sum_end = $XLSRowNo - 1; // Used to end the sum here.

      // Generating total for the Commitments.

      $rowFills = 'A'.$XLSRowNo.':M'.$XLSRowNo;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');

      $detail_row_total_extra = array_values($detail_row_total);
      $detail_row_total = array('none', 'none');

      $detail_row_total = array_merge($detail_row_total, $detail_row_total_extra);

      for ($i = 0; $i <= count($detail_row) - 1; $i++) {
        $colindexx = excelgeneratorurl_get_colindex ($i);
        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_RIGHT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );

        if ($i == 1) {
          continue;
        }
        if ($i == 0) {
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( t('Total') ) );
        }
        else {
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle($colindexx . ($XLSRowNo).':' . $colindexx .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $detail_row_total[$i] ) );
        }
      }

      $XLSRowNo += 2;

      // Generating ETC reports from here.
      $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('A'.$XLSRowNo.':K'.$XLSRowNo);

      $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_LEFT,)); // Applying borders
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle('A'. ($XLSRowNo).':K'.($XLSRowNo))->applyFromArray($BStyle);

      $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A' . ($XLSRowNo) )->getFont ()->setBold ( true );
      $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode(t('ETC Forecast')));

      $XLSRowNo++;


      // Creating header.
      $detail_header_etc = array(
        t('ETC Number'),
        t('Amount'),
        t('Total Spent'),
        t('Previous Years'),
        date('Y') . ' ' . t('Quarter 1'),
        date('Y') . ' ' . t('Quarter 2'),
        date('Y') . ' ' . t('Quarter 3'),
        date('Y') . ' ' . t('Quarter 4'),
        date('Y') . ' ' . t('Spending'),
        t('Future Years'),
        t('Variance'),
      );

      for ($i = 0; $i <= count($detail_header_etc) - 1; $i++) {
        $colindexx = excelgeneratorurl_get_colindex ($i);
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');
        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );
        $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $detail_header_etc[$i] ) );
      } // Finished making header for each project.

      $XLSRowNo++;
      $sum_start = $XLSRowNo; // Used to start the sum from here.

      $query = db_select('node','n');
      $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
      $query->join('field_data_field_etc_amount','ea','ea.entity_id = n.nid');  
      $query->join('field_data_field_etc_operation_done', 'eo', 'eo.entity_id = n.nid');
      $query->fields('n', array('nid'));
      $query->condition('pr.field_project_reference_nid', $key, '=');
      $query->condition('eo.field_etc_operation_done_value', 'In ETC', '=');
      $getEtcIds = $query->execute()->fetchCol();
      foreach($getEtcIds as $etcKey => $etcVal) {
        $getEtcData = node_load($etcVal);
        $etcNumber = $getEtcData->field_etc_number_calc['und'][0]['value'];
        $etcAmt = $getEtcData->field_etc_amount['und'][0]['value'] != '' ? $getEtcData->field_etc_amount['und'][0]['value'] : 0;
        $etcTtoal += $etcAmt;
        // Get quarter value for etc
        $defaultAmt = 0;
        $getFutureAmt = 0;
        $getVarienceAmt = 0;
        if (!empty($forecast)) {
          $query = db_select('m6connect_spending_forecast', 'sf');
          $query->fields('sf', array('quarter_one_amount','quarter_two_amount', 'quarter_three_amount','quarter_four_text_amount','quarter_four_amount','current_year_spending_amount','future_year_amout','variance_amount'));
          $query->condition('sf.forecast_name', $forecast, '=');
          $query->condition('sf.project_id', $key, '=');
          $query->condition('sf.commitment_id', $getEtcData->nid, '=');
          $forecastData = $query->execute()->fetchAll();
          
          $getPrevQuarterOne = $forecastData[0]->quarter_one_amount;
          $getPrevQuarterTwo = $forecastData[0]->quarter_two_amount;
          $getPrevQuarterThree = $forecastData[0]->quarter_three_amount;
          $getPrevQuarterFour = $forecastData[0]->quarter_four_amount;
                
          $getCurrentYearAmt = !empty($forecastData[0]->current_year_spending_amount) ? $forecastData[0]->current_year_spending_amount : 0;
          $getFutureAmt = !empty($forecastData[0]->future_year_amout) ? $forecastData[0]->future_year_amout : 0;
          $getVarienceAmt = !empty($forecastData[0]->variance_amount) ? $forecastData[0]->variance_amount : 0;

          $detail_row_etc = array(
            $etcNumber,
            $etcAmt,
            0,
            0,
            $getPrevQuarterOne,
            $getPrevQuarterTwo,
            $getPrevQuarterThree,
            $getPrevQuarterFour,
            $getCurrentYearAmt,
            $getFutureAmt,
            $getVarienceAmt,
          );

          for ($i = 0; $i <= count($detail_row_etc) - 1; $i++) {
            $colindexx = excelgeneratorurl_get_colindex ($i);
            // $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo) )->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('FCF305');
            $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_RIGHT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders

            $_excelexport_objPHPExcel->getActiveSheet()->getStyle($colindexx . ($XLSRowNo).':' . $colindexx .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');

            $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);

            // $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );
            $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( $detail_row_etc[$i] ) );
          }
        }
        else {
          // No data avialable.
          $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_CENTER, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle( 'A' . ($XLSRowNo))->applyFromArray($BStyle);
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'A' . ($XLSRowNo), utf8_encode ( $etcNumber ) );

          $_excelexport_objPHPExcel->getActiveSheet()->mergeCells('B'.$XLSRowNo.':L'.$XLSRowNo);
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle( 'B' . ($XLSRowNo))->applyFromArray($BStyle);
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( 'B' . ($XLSRowNo), utf8_encode ( t('No ETC Forecast found!') ) );
        }
        $XLSRowNo++;
      }
      $sum_end = $XLSRowNo - 1; // Used to end the sum here.

      $rowFills = 'A'.$XLSRowNo.':K'.$XLSRowNo;
      $_excelexport_objPHPExcel->getActiveSheet()->getStyle($rowFills)->getFill()->setFillType(PHPExcel_Style_Fill::FILL_SOLID)->getStartColor()->setARGB('E3E3E3');

      for ($i = 0; $i <= count($detail_row_etc) - 1; $i++) {
        $colindexx = excelgeneratorurl_get_colindex ($i);
        $BStyle = array('borders' => array( 'allborders' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN )), 'alignment' => array('horizontal' => PHPExcel_Style_Alignment::HORIZONTAL_RIGHT, 'vertical' => PHPExcel_Style_Alignment::VERTICAL_BOTTOM,)); // Applying borders
        $_excelexport_objPHPExcel->getActiveSheet()->getStyle( $colindexx . ($XLSRowNo))->applyFromArray($BStyle);
        $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( $colindexx . ($XLSRowNo) )->getFont ()->setBold ( true );

        if ($i == 0) {
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), utf8_encode ( t('Total') ) );
        }
        else {
          $_excelexport_objPHPExcel->getActiveSheet()->getStyle($colindexx . ($XLSRowNo).':' . $colindexx .($XLSRowNo))->getNumberFormat()->setFormatCode('$#,##0_-');
          $_excelexport_objPHPExcel->setActiveSheetIndex ( 0 )->setCellValue ( $colindexx . ($XLSRowNo), '=SUM(' . $colindexx . $sum_start . ':' . $colindexx . $sum_end . ')' );
        }
      }

      $XLSRowNo += 4;
    }


    // Generating output.
    header ( 'Content-Type: application/vnd.openxmlformats-officedocument.spreadsheetml.sheet' );
    header ( 'Content-Disposition: attachment;filename="projectSpendingForecast.xlsx"' );  
    header ( 'Cache-Control: max-age=0' );
    header ( 'Cache-Control: max-age=1' );
    header ( 'Expires: Mon, 26 Jul 1997 05:00:00 GMT' );
    header ( 'Last-Modified: ' . gmdate ( 'D, d M Y H:i:s' ) . ' GMT' );
    header ( 'Cache-Control: cache, must-revalidate' );
    header ( 'Pragma: public' );
    $BStyle = array('borders' => array( 'bottom' => array( 'style' => PHPExcel_Style_Border::BORDER_THIN ))); 
    //$_excelexport_objPHPExcel->getActiveSheet()->getStyle('B7:D7')->applyFromArray($BStyle);    
    
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setWrapText ( true );
    $_excelexport_objPHPExcel->getActiveSheet ()->getStyle ( 'A1:Z500' )->getAlignment ()->setVertical ( PHPExcel_Style_Alignment::VERTICAL_TOP );
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('A')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('B')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('C')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('D')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('E')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('F')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('G')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('H')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('I')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('J')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('K')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('L')->setWidth(30);
    $_excelexport_objPHPExcel->getActiveSheet()->getColumnDimension('M')->setWidth(30);
    $obj_writer = PHPExcel_IOFactory::createWriter ( $_excelexport_objPHPExcel, 'Excel2007' );
    $obj_writer->setPreCalculateFormulas(true);
    $obj_writer->save ( 'php://output' );
  } // endif $type == 'spending-forecast'
}
// Excel section work ends here
// End Reports Sction
// =============================