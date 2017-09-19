<?php

/********** Start Onboarding Manage Colleagues **********/

// Start Cost Summary slide (Tab) Section
// ======================================
function program_project_cost_summary_content(){
  global $company;	
  $getEstimateByCompany = _project_list_by_company($company->nid, 'project_management');  	
  reset( $array );
  $firstProject = key( $getEstimateByCompany );	
  if(isset($_SESSION['ACTIVEPROJECT']) && $_SESSION['ACTIVEPROJECT'] != '') {
    $firstProject = $_SESSION['ACTIVEPROJECT'];
  }
  else {
    $firstProject = $firstProject;
  }
  $elements = array();
  $elements['program-cost-summary-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_modify_cost_summary_form')),
	'#prefix' => '<div class="clearfix margin-bottom-10">',
	'#suffix' => '</div>',
  );
  $elements['prgram-project-menu-items'] = array(
    '#markup' => program_project_menu_links_content(),
	'#prefix' => '<div class="clearfix">',
	'#suffix' => '</div>',
  );
  $elements['prgram-project-listing'] = array(    	
    '#markup' => get_project_cost_summary_table_data($firstProject),
	'#prefix' => '<div id="project_program_cost_summary_container"><div class="clearfix"><div class="table-responsive">',
	'#suffix' => '</div></div></div>',
   );	
  return $elements;
}

function program_modify_cost_summary_form($form, &$form_state) {
  global $user;	  
  global $company;  
  drupal_add_js(drupal_get_path('module', 'm6connect_program') . '/js/m6connect_program.js');
  // Get project list by company 
  $getProjectByCompany = _project_list_by_company($company->nid, 'project_management');
  foreach($getProjectByCompany as $key => $val) {
    $projectListByCom[$key] = $val;
  }  
  $form['select-project-cost-summary'] = array(
    '#type'=>'select',
	'#title'=> 'Select Project:',
	'#options' => $projectListByCom,
	//'#empty_option' => ' -None- ',
	'#default_value' => isset($_SESSION['ACTIVEPROJECT'])?$_SESSION['ACTIVEPROJECT']:'',
	'#attributes' => array('class'=> array('form-control project_programe_main_pro')),
	'#ajax' => array(
	  'callback'=> 'change_program_cost_summary_callback',
	  'wrapper' => 'project_program_cost_summary_container_2',
	  'effect' => 'fade',
	),
	'#prefix' => '<div class="clearfix"><div class="pull-left form-inline">',
	'#suffix' => '</div></div>',
  );  
  return $form;
}

function change_program_cost_summary_callback($form,&$form_state){
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];
  if(!empty($triggeringElement['#value']) && $triggeringElement['#value'] != 0 && $triggeringElement['#name'] == 'select-project-cost-summary'){
	if((isset($_SESSION['ACTIVEPROJECT']) && $_SESSION['ACTIVEPROJECT']!=$triggeringElement['#value']) || (!isset($_SESSION['ACTIVEPROJECT'])) || (empty($_SESSION['ACTIVEPROJECT']))){
	  $_SESSION['ACTIVEPROJECT'] = $triggeringElement['#value'];
	}  
    $commands[] = ajax_command_html("#project_program_cost_summary_container", get_project_cost_summary_table_data($triggeringElement['#value']));	
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function get_project_cost_summary_table_data($proId = 0) {
  global $company;  
  drupal_add_library('system', 'ui.resizable');
  /*drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');
  drupal_add_js('jQuery(document).ready(function () { jQuery("table.m6connect-program-cost-summary-main-table").DataTable({"bPaginate": false,"bLengthChange": false,"bFilter": false,"bInfo": false,"bAutoWidth": false,"order": [],"aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}]}); });',
    array('type' => 'inline')
  );*/
  setlocale(LC_MONETARY, 'en_US');
  $rows = array();
  $header = array(
	array('data'=>'Cost Code','class'=>array('text-center')),
	array('data'=>'Original Budget','class'=>array('text-center')),
	array('data'=>'Budget Adjustment','class'=>array('text-center')),
	array('data'=>'Current Budget','class'=>array('text-center'), 'title' => array('Current Budget = Original Budget + Budget Adjustment')),
	array('data'=>'Total Commitments','class'=>array('text-center')),
	array('data'=>'Total Spend','class'=>array('text-center')),	
	array('data'=>'Total Allocated','class'=>array('text-center'),'title' => array('Includes Overspent Commitments')),
	array('data'=>'Estimate to Commit','class'=>array('text-center'), 'title' => array('Includes future commitments, risks and pending changes.')),
	array('data'=>'Projected Final Cost','class'=>array('text-center'), 'title' => array('Projected Final Cost = Total Allocated + Estimate to Commit')),
	array('data'=>'Variance','class'=>array('text-center'), 'title' => array('Variance = Current Budget - Projected Final Cost')),
  );
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
  $query->condition('es.field_project_estimate_status_value', 'approved', '=');
  $query->orderBy('cc.field_est_cost_code_value', 'ASC');
  $query->condition('pr.field_project_reference_nid', $proId, '=');
  $query->condition('om.gid', $company->nid, '=');
  $costCode = $query->execute()->fetchAll();	
  
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
  $query2->condition('pr.field_project_reference_nid', $proId, '=');        
  $query2->condition('om.gid', $company->nid, '=');
  $amtLineTotal = $query2->execute()->fetchField(); 
  $ccArr = array();
  $ccArrCount = array();
  foreach($costCode as $ccId => $ccVal) {	
    // Get cost code
	$getCcDes = db_select('node','n'); 
	$getCcDes->join('field_data_field_manager_cost_code','mcc','mcc.entity_id = n.nid'); 
    $getCcDes->join('field_data_field_cost_code_description','ccd','ccd.entity_id = n.nid'); 	  
	$getCcDes->fields('ccd',array('field_cost_code_description_value'));
	$getCcDes->condition('mcc.field_manager_cost_code_value',$ccVal->field_est_cost_code_value, '=');
	$costCodeDes = $getCcDes->execute()->fetchField();	    	
	$costCode = $ccVal->field_est_cost_code_value.'|'.$costCodeDes;	
    // Get Original budget
	$capitalContigency = $ccVal->field_capital_contingency_value;	
	if(!isset($ccArr[$ccVal->field_est_cost_code_value])){
	  $ccArr[$ccVal->field_est_cost_code_value]= array(	    
	    'cost_code' => $ccVal->field_est_cost_code_value.'|'.$costCodeDes,
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
	if($ccVal->field_est_line_item_amt_value != '') {
	  $originalBudget = $ccVal->field_est_line_item_amt_value;
	}
	else if($ccVal->field_conigency_percentage_value != '') {
	  $percent = ($amtLineTotal * $ccVal->field_conigency_percentage_value)/100;
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
	
	$ccArr[$ccVal->field_est_cost_code_value]['originalBudget'] += $originalBudget;	
	$ccArr[$ccVal->field_est_cost_code_value]['currentBudget'] += $currentBudget;
	$ccArr[$ccVal->field_est_cost_code_value]['Commitment'] = $getCommitmentTotal;
	$ccArr[$ccVal->field_est_cost_code_value]['spent'] = $getInvoiceTotal;
	$ccArr[$ccVal->field_est_cost_code_value]['Allocated'] = $getTotalAllocated;
	$ccArr[$ccVal->field_est_cost_code_value]['est'] = $getETCTotal;
	$ccArr[$ccVal->field_est_cost_code_value]['PFC'] = $projectFinalCost;
	$ccArr[$ccVal->field_est_cost_code_value]['Variance'] = $varience;
  } 
  $ccArrTotal= array('originalBudget' => 0,'currentBudget' => 0,'Commitment' => 0,'spent' => 0,'Allocated' => 0,'est' => 0,'PFC' => 0,'Variance' => 0);
  foreach($ccArr as $ccKey => $ccVals) {
    $rows[] = array(
	'data' => array(array('data'=>$ccVals['cost_code'],'class'=>array('text-left')),'$'.number_format($ccVals['originalBudget']),'$0','$'.number_format($ccVals['currentBudget']),'$'.number_format($ccVals['Commitment']),'$'.number_format($ccVals['spent']),'$'.number_format($ccVals['Allocated']),'$'.number_format($ccVals['est']),'$'.number_format($ccVals['PFC']),'$'.number_format($ccVals['Variance'])),	
	'class' => array('text-right'),
	);
	
	$ccArrTotal= array(
	    'originalBudget' => $ccArrTotal['originalBudget']+$ccVals['originalBudget'],
		'currentBudget' => $ccArrTotal['currentBudget']+$ccVals['currentBudget'],
		'Commitment' => $ccArrTotal['Commitment']+$ccVals['Commitment'],
		'spent' => $ccArrTotal['spent']+$ccVals['spent'],
		'Allocated' => $ccArrTotal['Allocated']+$ccVals['Allocated'],
		'est' => $ccArrTotal['est']+$ccVals['est'],
		'PFC' => $ccArrTotal['PFC']+$ccVals['PFC'],
		'Variance' => $ccArrTotal['Variance']+$ccVals['Variance'],
	  );
  }  
  $rows[] = array(
    'data' => array('<strong>Total</strong>','<strong>$'.number_format($ccArrTotal['originalBudget']).'</strong>','<strong>$0</strong>','<strong>$'.number_format($ccArrTotal['currentBudget']).'</strong>','<strong>$'.number_format($ccArrTotal['Commitment']).'</strong>','<strong>$'.number_format($ccArrTotal['spent']).'</strong>','<strong>$'.number_format($ccArrTotal['Allocated']).'</strong>','<strong>$'.number_format($ccArrTotal['est']).'</strong>','<strong>$'.number_format($ccArrTotal['PFC']).'</strong>','<strong>$'.number_format($ccArrTotal['Variance']).'</strong>'),	
  'class' => array('custom-odd', 'text-right'),
  'style' => 'border-top-style: double;border-color: #ccc;',        
  );
  return theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Cost Summary created yet','attributes'=>array('class'=>array('table','m6connect-custom-program-table','m6connect-program-cost-summary-main-table','table-header-border','table-hover','text-center'))));	
}


function get_invoice_total_by_cost_code_inc($costCode, $proId) {
  $getCC = explode('-', $costCode);
  $query= db_select('node','n');     
  $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
  $query->join('field_data_field_invoice_cost_code','icc','icc.entity_id=n.nid');
  $query->join('field_data_field_invoice_amount','ea','ea.entity_id = n.nid');  
  $query->addExpression('SUM(ea.field_invoice_amount_value)','finalTotal');
  //$query->condition('icc.field_invoice_cost_code_value', $getCC[0], '=');
  $query->condition('icc.field_invoice_cost_code_value', $costCode, '=');  
  $query->condition('pr.field_project_reference_nid', $proId, '=');
  $query->groupBy('icc.field_invoice_cost_code_value');
  $getTotalInvoiceAmt = $query->execute()->fetchField(); 
  return $getTotalInvoiceAmt;
}

function get_commitment_total_by_cost_code_inc($costCode, $proId) {
  /*$query = db_select('node','n');     
  $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
  $query->join('field_data_field_cost_code','icc','icc.entity_id=n.nid');
  $query->join('field_data_field_commitment_po_final_total','ft','ft.entity_id = n.nid');  
  $query->addExpression('SUM(ft.field_commitment_po_final_total_value)','finalTotal');
  $query->condition('icc.field_cost_code_value', $costCode, '=');
  $query->condition('pr.field_project_reference_nid', $proId, '=');
  $query->groupBy('icc.field_cost_code_value');
  $getTotalCommitemtnAmt = $query->execute()->fetchField(); */
  //$getCC = explode('-', $costCode);
  $query = db_select('node','n');     
  $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
  $query->join('field_data_field_commitment_ws_code','icc','icc.entity_id=n.nid');
  $query->join('field_data_field_commitment_po_final_total','ft','ft.entity_id = n.nid');  
  $query->addExpression('SUM(ft.field_commitment_po_final_total_value)','finalTotal');
  $query->condition('icc.field_commitment_ws_code_value', $costCode, '=');
  $query->condition('pr.field_project_reference_nid', $proId, '=');
  $query->groupBy('icc.field_commitment_ws_code_value');
  $getTotalCommitemtnAmt = $query->execute()->fetchField(); 
  return $getTotalCommitemtnAmt;
}

function get_etc_total_by_cost_code_inc($costCode, $proId) {
  //$getCC = explode('-', $costCode);	
  $query = db_select('node','n');     
  $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
  $query->join('field_data_field_etc_cost_code','ecc','ecc.entity_id=n.nid');
  $query->join('field_data_field_etc_amount','ea','ea.entity_id = n.nid');  
  $query->join('field_data_field_etc_operation_done', 'eo', 'eo.entity_id = n.nid');
  $query->addExpression('SUM(ea.field_etc_amount_value)','finalTotal');
  $query->condition('ecc.field_etc_cost_code_value', $costCode, '=');
  $query->condition('pr.field_project_reference_nid', $proId, '=');
  $query->condition('eo.field_etc_operation_done_value', 'In ETC', '=');
  $query->groupBy('ecc.field_etc_cost_code_value');
  $getTotalEtcAmt = $query->execute()->fetchField(); 
  return $getTotalEtcAmt;
}

function get_total_allocated_by_cost_code_inc($costCode, $proId,$getCommitmentAmt) { 
  //$getCC = explode('-', $costCode);	
  $query = db_select('node','n'); 
  $query->join('field_data_field_cost_code','ccc','ccc.entity_id = n.nid');
  $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
  $query->join('field_data_field_commitment_po_final_total','cpt','n.nid=cpt.entity_id');
  $query->fields('n', array('nid'));
  $query->fields('cpt', array('field_commitment_po_final_total_value'));
  $query->condition('ccc.field_cost_code_value', $costCode, '=');
  $query->condition('pr.field_project_reference_nid', $proId, '=');
  $commitmentNode = $query->execute()->fetchAll();
  $getPoBal = 0;
  foreach($commitmentNode as $commitKey => $commitVal) {
    // Get invoice against
    $query= db_select('node','n'); 
    $query->join('field_data_field_invoice_commitment','ic','ic.entity_id = n.nid');
    $query->join('field_data_field_invoice_amount','ia','ia.entity_id = n.nid');
    $query->addExpression('SUM(ia.field_invoice_amount_value)','finalTotal');
    $query->condition('n.type','project_spending','=');
    $query->condition('ic.field_invoice_commitment_nid',$commitVal->nid,'=');
    $query->groupBy('ic.field_invoice_commitment_nid');
    $getTotalSpending = $query->execute()->fetchField();	
    $getCommitemntTotal = $commitVal->field_commitment_po_final_total_value;  
    if($getCommitemntTotal < $getTotalSpending) {
      $getPoBal += intval($getTotalSpending) - intval($getCommitemntTotal);
    }    
  }
  return (intval($getCommitmentAmt) + intval($getPoBal));
}
// ====================================
// End Cost Summary Slide (Tab) Section
// ====================================