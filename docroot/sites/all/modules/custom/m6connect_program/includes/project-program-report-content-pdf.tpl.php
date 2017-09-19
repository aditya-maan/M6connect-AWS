<?php
global $base_url, $theme_path, $company;
setlocale(LC_MONETARY, 'en_US');
$date = date('m/d/Y',time());  
module_load_include('inc','m6connect_program', 'cost.summary');
$reportType = arg(1);
if(is_numeric(arg(2))) { $costProId = array(arg(2)); } else { $costProId = explode(',',check_plain($_GET['proids'])); }
$projectCount = count($costProId);
$allDataArr = array();
// Get final summary first for cost summary
foreach($costProId as $proIdFnl) { 
  $projectIdFnl = $proIdFnl;
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
  $query->condition('pr.field_project_reference_nid', $projectIdFnl, '=');
  $query->condition('om.gid', $company->nid, '=');
  $costCodeFnl = $query->execute()->fetchAll();
  $allDataArr[$projectIdFnl] = $costCodeFnl;
}

// Work for get the summary report for all the projects
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
  $costCodeDesc = get_description_by_cost_code($proVal->field_est_cost_code_value);
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
  $getInvoiceTotal = get_invoice_total_by_cost_code_pdf($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid);
  $totalInvoiceTotal += $getInvoiceTotal;
  // Get commitment total
  $getCommitmentTotal = get_commitment_total_by_cost_code_pdf($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid);
  $totalCommitmentTotal += $getCommitmentTotal;
  // Get total allocated 
  $getTotalAllocated = get_total_allocated_by_cost_code_pdf($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid,$getCommitmentTotal);
  $totalAllocated += $getTotalAllocated;
  // Get etc total
  $getETCTotal = get_etc_total_by_cost_code_pdf($proVal->field_est_cost_code_value,$proVal->field_project_reference_nid);
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

if($reportType == 'costsummary') { if($projectCount > 1) { ?>

<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:100%; text-align:center;"><?php print 'Final Summary Report:'; ?></div>
      <!--<div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>--> 
    </h3>
    <!--<div class="heading" style="background-color:#eee;"> <strong>Project Manager: </strong><span><?php print $projectManager; ?></span> </div>-->
    <table class="under-border" style="width:100%; margin:0;">
      <thead>
        <tr>
          <th width="120" align="left">Cost Code|Description</th>
          <th width="120" align="right">Original Budget </th>
          <th width="120" align="right">Current Budget </th>
          <th width="120" align="right">Committed</th>
          <th width="120" align="right">Spent</th>
          <th width="120" align="right">Total Allocated</th>
          <th width="120" align="right">ETC</th>
          <th width="120" align="right">PFC</th>
        </tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="8"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>
        <?php foreach($getCCcodeArr as $cCodeId => $cCodeVal) { 
		        $getCCcodeArrTotal= array(
	    			'originalBudget' => $getCCcodeArrTotal['originalBudget']+$cCodeVal['originalBudget'],
					'currentBudget' => $getCCcodeArrTotal['currentBudget']+$cCodeVal['currentBudget'],
					'Commitment' => $getCCcodeArrTotal['Commitment']+$cCodeVal['Commitment'],
					'spent' => $getCCcodeArrTotal['spent']+$cCodeVal['spent'],
					'Allocated' => $getCCcodeArrTotal['Allocated']+$cCodeVal['Allocated'],
					'est' => $getCCcodeArrTotal['est']+$cCodeVal['est'],
					'PFC' => $getCCcodeArrTotal['PFC']+$cCodeVal['PFC'],
					'Variance' => $getCCcodeArrTotal['Variance']+$cCodeVal['Variance'],
	  			);
		?>
        <tr>
          <td><?php print $cCodeVal['cost_code']; ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['originalBudget']); ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['currentBudget']); ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['Commitment']); ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['spent']); ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['Allocated']); ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['est']); ?></td>
          <td align="right"><?php print '$'.number_format($cCodeVal['PFC']); ?></td>
        </tr>
        <?php } ?>
      </tbody>
      <tfoot>
        <tr>
          <th align="left">Project Totals
            </td>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['originalBudget']); ?></th>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['currentBudget']); ?></th>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['Commitment']); ?></th>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['spent']); ?></th>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['Allocated']); ?></th>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['est']); ?></th>
          <th align="right"><?php print '$'.number_format($getCCcodeArrTotal['PFC']); ?></th>
        </tr>
      </tfoot>
    </table>
  </div>
</div>
<pagebreak suppress="off" />
<?php } } 
foreach($costProId as $proId) { 
  $projectId = $proId;	
  $projectDetails = node_load($projectId);
  if(isset($projectDetails->field_project_mgmt_manager['und'])) {	
    $userData = user_load($projectDetails->field_project_mgmt_manager['und'][0]['value']);
    $projectManager = $userData->field_first_name['und'][0]['value'].' '.$userData->field_last_name['und'][0]['value'];
  }
  else {
    $projectManager = 'None';	
  }	
  
  if(isset($projectDetails->field_project_mgmt_manager['und'])) {
    $userData = user_load($projectDetails->field_project_mgmt_manager['und'][0]['value']);
	if(isset($userData->field_user_profile_photo['und'])) {
	  $profilePic = image_style_url('user_pic_40x40',$userData->field_user_profile_photo['und'][0]['uri']);
	  $managerPic = '<img  src="'.$profilePic.'" alt="" height="40" width="40">'; 
	}
	else {
	  $managerPic = '<img src="/sites/default/files/styles/find_people/public/images_13.png" height="40" width="40">';  
	}
  }  
  $projectNumber = $projectDetails->field_project_mgmt_number['und'][0]['value'];
  $projectName = $projectDetails->title;
  $getCompanyData = $projectDetails->og_group_ref['und'][0]['target_id'];
  if(isset($getCompanyData->field_logo['und'])) {
    $companyLogo = '<img src="'.image_style_url('thumbnail', $getCompanyData->field_logo['und'][0]['uri']).'" height="70" width="70">';	
  }
  else {
    $companyLogo = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" height="70" width="70">';
  }	  
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
  $query->condition('pr.field_project_reference_nid', $projectId, '=');
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
  $query2->condition('pr.field_project_reference_nid', $projectId, '=');        
  $query2->condition('om.gid', $company->nid, '=');
  $amtLineTotal = $query2->execute()->fetchField(); 
  	
  $ccArr = array();
  $ccArrCount = array();
  //$allDataArr[$projectId] = $costCode;
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
	$getInvoiceTotal = get_invoice_total_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId);
	$totalInvoiceTotal += $getInvoiceTotal;
	// Get commitment total
	$getCommitmentTotal = get_commitment_total_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId);
	
	$totalCommitmentTotal += $getCommitmentTotal;
	// Get total allocated 
	$getTotalAllocated = get_total_allocated_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId,$getCommitmentTotal);
	$totalAllocated += $getTotalAllocated;
	// Get etc total
	$getETCTotal = get_etc_total_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId);
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
  // ==== End work for project data ==== //
  if($reportType == 'monthly') {
    $reportTitle = 'Monthly Project Report';    
    $projectStatus = isset($projectDetails->field_project_mgmt_status['und'])?$projectDetails->field_project_mgmt_status['und'][0]['value']:'None';
	if(isset($projectDetails->field_project_mgmt_location['und']) && $projectDetails->field_project_mgmt_location['und'][0]['value'] != '') {
	  $locationID = node_load($projectDetails->field_project_mgmt_location['und'][0]['value']);
	  $getLocation = $locationID->field_org_address['und'][0]['thoroughfare'].' '.$locationID->field_org_address['und'][0]['administrative_area'];
	}
	else {
	  $getLocation = 'None';
	}
    $fundingStatus = isset($projectDetails->field_project_funding_status['und'])?$projectDetails->field_project_funding_status['und'][0]['value']:'None';
	$designStatus = isset($projectDetails->field_project_design_status['und'])?$projectDetails->field_project_design_status['und'][0]['value']:'None';
    $description = isset($projectDetails->body['und'])?$projectDetails->body['und'][0]['value']:'None';  
    $commentData = get_project_manager_comment_by_project($projectId);  
    // Get schedule by project
    $query= db_select('field_data_field_project_reference','pr');	
	$query->join('field_data_field_in_report','sr', 'sr.entity_id = pr.entity_id');
    $query->fields('pr', array('entity_id'));
	$query->condition('sr.field_in_report_value', 1, '=');
    $query->condition('pr.field_project_reference_nid', $projectId, '=');
    $query->condition('pr.bundle','project_schedule','=');
    $getScheduleNodes = $query->execute()->fetchCol(); 	    
	// Get etc by project
    $query= db_select('field_data_field_project_reference','pr');	
	$query->join('field_data_field_in_report','sr', 'sr.entity_id = pr.entity_id');
    $query->fields('pr', array('entity_id'));
	$query->condition('sr.field_in_report_value', 1, '=');
    $query->condition('pr.field_project_reference_nid', $projectId, '=');
    $query->condition('pr.bundle','project_schedule','=');
    $getScheduleNodes = $query->execute()->fetchCol(); 	    
	
	 
  // Get etc by project
	$query = db_select('node','n');     
    $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
    $query->join('field_data_field_etc_amount','ea','ea.entity_id = n.nid');  
    $query->join('field_data_field_etc_operation_done', 'eo', 'eo.entity_id = n.nid');    
	$query->fields('pr', array('entity_id'));
    $query->condition('pr.field_project_reference_nid', $projectId, '=');   
	$query->condition('eo.field_etc_operation_done_value', 'Risk Management', '=');	
    $getETCNodeRisk = $query->execute()->fetchCol(); 

	$query = db_select('node','n');     
    $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
    $query->join('field_data_field_etc_amount','ea','ea.entity_id = n.nid');  
    $query->join('field_data_field_etc_operation_done', 'eo', 'eo.entity_id = n.nid');    
	$query->fields('pr', array('entity_id'));
    $query->condition('pr.field_project_reference_nid', $projectId, '=');   
	$query->condition('eo.field_etc_operation_done_value', 'Scope Change', '=');	
    $getETCNodeScope = $query->execute()->fetchCol();
   // Get general infromation image
   $query= db_select('node','n'); 
   $query->join('field_data_field_group_information','gi','gi.entity_id = n.nid');
   $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
   $query->fields('gi',array('field_group_information_fid'));
   $query->condition('pr.field_project_reference_nid', $projectId, '=');
   $generalInfoImage = $query->execute()->fetchAll();   
   // Get Project Description images image
   $query= db_select('node','n'); 
   $query->join('field_data_field_project_description_images','pd','pd.entity_id = n.nid');
   $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
   $query->fields('pd',array('field_project_description_images_fid'));
   $query->condition('pr.field_project_reference_nid', $projectId, '=');
   $proDescImage = $query->execute()->fetchAll();   
   // Get Project Safety images image
   $query= db_select('node','n'); 
   $query->join('field_data_field_project_safety_images','si','si.entity_id = n.nid');
   $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
   $query->fields('si',array('field_project_safety_images_fid'));
   $query->condition('pr.field_project_reference_nid', $projectId, '=');
   $proSafetyImage = $query->execute()->fetchAll();   
   // Get Project Additional image
   $query= db_select('node','n'); 
   $query->join('field_data_field_project_additional_images','ai','ai.entity_id = n.nid');
   $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
   $query->fields('ai',array('field_project_additional_images_fid'));
   $query->condition('pr.field_project_reference_nid', $projectId, '=');
   $proAdditionalImage = $query->execute()->fetchAll();   
   // Get recent Safety Record
   $query = db_select('node', 'n');   
   $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
   $query->join('field_data_field_start_date','st','st.entity_id = n.nid');
   $query->join('field_data_field_lost_time_accidents','lta','lta.entity_id = n.nid');
   $query->join('field_data_field_hours_this_period','ph','ph.entity_id = n.nid');
   $query->fields('st',array('field_start_date_value'));
   $query->fields('lta',array('field_lost_time_accidents_value'));
   $query->fields('ph',array('field_hours_this_period_value'));
   $query->condition('pr.field_project_reference_nid', $projectId, '=');
   $query->condition('n.type', 'project_safety', '=');
   $query->orderBy('n.created', 'DESC');
   $query->range(0,1);   
   $recentSafety = $query->execute()->fetchAll();
   $getRecentDate = $recentSafety[0]->field_start_date_value != ''?date('m/d/Y', strtotime($recentSafety[0]->field_start_date_value)):0;
   $getRecentLta = $recentSafety[0]->field_lost_time_accidents_value != ''?$recentSafety[0]->field_lost_time_accidents_value:0;
   $getRecentHours = $recentSafety[0]->field_hours_this_period_value != ''?$recentSafety[0]->field_hours_this_period_value:0;
   // Get all safety Records by project
   $query = db_select('node', 'n');   
   $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
   $query->join('field_data_field_start_date','st','st.entity_id = n.nid');
   $query->join('field_data_field_lost_time_accidents','lta','lta.entity_id = n.nid');
   $query->join('field_data_field_hours_this_period','ph','ph.entity_id = n.nid');
   $query->fields('st',array('field_start_date_value'));
   $query->fields('lta',array('field_lost_time_accidents_value'));
   $query->fields('ph',array('field_hours_this_period_value'));
   $query->condition('pr.field_project_reference_nid', $projectId, '=');
   $query->condition('n.type', 'project_safety', '=');
   $allSafety = $query->execute()->fetchAll();
   foreach($allSafety as $safetyKey => $safetyVal) {
     $lta = $safetyVal->field_lost_time_accidents_value;
	 $totalLTA += $safetyVal->field_lost_time_accidents_value;
	 $workingHrs = $safetyVal->field_hours_this_period_value;
	 $totalHours += $safetyVal->field_hours_this_period_value;
   }
      
?>
<div class="page_details">
  <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
    <div style="float:left; width:50%;"><?php print ucfirst($projectDetails->title); ?></div>
    <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
  </h3>
  <div class="headeing">
    <h3 style="margin:0;">General Information</h3>
    <table style="width:100%;">
      <tr>
        <td style="width:200px; vertical-align:top;"><?php foreach($generalInfoImage as $giImageKey => $giImageVal) { 
		      $fileData = file_load($generalInfoImage[$giImageKey]->field_group_information_fid); 
			  $getImage = image_style_url('project_general_images_style',$fileData->uri);
		?>
          <img src="<?php print $getImage; ?>" alt="res" style="margin:5px 0 0 0;" />
          <?php } ?></td>
        <td style="vertical-align:top;"><table style="vertical-align:top;">
            <tr>
              <th align="left" width="120" style="vertical-align:top;">Project Manager:</th>
              <td style="vertical-align:top;"><?php print $projectManager; ?></td>
              <td rowspan="2" style="vertical-align:top; padding:5px 0 0 15px;"><?php print $managerPic; ?></td>
            </tr>
            <tr>
              <th align="left">Location:</th>
              <td><?php print $getLocation; ?></td>
            </tr>
            <tr>
              <th align="left">Project Status:</th>
              <td colspan="2"><?php print $projectStatus; ?></td>
            </tr>
            <tr>
              <th align="left">Funding Status:</th>
              <td colspan="2"><?php print $fundingStatus; ?></td>
            </tr>
            <tr>
              <th align="left">Design Status:</th>
              <td colspan="2"><?php print $designStatus; ?></td>
            </tr>
          </table></td>
      </tr>
    </table>
  </div>
  <div class="clearfix hr"></div>
  <div class="headeing">
    <h3 style="margin:0;">Project Description</h3>
    <table style="width:100%;">
      <tr>
        <td style="vertical-align:top;"><?php foreach($proDescImage as $pdImageKey => $pdImageVal) { 
		      $fileData = file_load($proDescImage[$pdImageKey]->field_project_description_images_fid); 
			  $getImagePD = image_style_url('project_general_images_style',$fileData->uri);
		?>
          <img src="<?php print $getImagePD; ?>" alt="res" style="margin-top:5px; margin-right:15px;" />
          <?php } ?></td>
        <td style="vertical-align:top;"><p style="margin-top:0;"><?php print $description; ?></p></td>
      </tr>
    </table>
  </div>
  <div class="clearfix hr"></div>
  <?php if(!empty($commentData)) { ?>
  <div class="headeing">
    <h3 style="margin:0 0 10px 0;">Project Manager Comments</h3>
    <div class="clearfix">
      <ol style="margin-top:0;">
        <?php foreach($commentData as $commentKey => $commentVal) { ?>
        <li><?php print $commentVal->message; ?></li>
        <?php } ?>
      </ol>
    </div>
  </div>
  <?php } if(count($costCode) > 0) { ?>
  <div class="clearfix hr"></div>
  <div class="headeing">
    <h3 style="margin:0 0 10px 0;">Project Cost Detail</h3>
    <table style="margin:0; width:100%;" class="under-border">
      <thead>
        <tr>
          <th width="120" align="left">Cost Code|Description</th>
          <th width="120" align="right">Original Budget </th>
          <th width="120" align="right">Current Budget </th>
          <th width="120" align="right">Committed</th>
          <th width="120" align="right">Spent</th>
          <th width="120" align="right">Total Allocated</th>
          <th width="120" align="right">ETC</th>
          <th width="120" align="right">PFC</th>
        </tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="8"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>
        <?php foreach($ccArr as $ccKey => $ccVals) { ?>
        <tr>
          <td width="120" align="left"><?php print $ccVals['cost_code']; ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n', $ccVals['originalBudget']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['currentBudget']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['Commitment']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['spent']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['Allocated']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['est']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['PFC']); ?></td>
        </tr>
        <?php 
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
		} ?>
      </tbody>
      <tfoot>
        <tr>
          <th width="120" align="right">Project Totals</th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['originalBudget']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['currentBudget']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['Commitment']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['spent']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['Allocated']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['est']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['PFC']); ?></th>
        </tr>
      </tfoot>
    </table>
  </div>
  <?php  } if(count($getETCNodeScope) > 0) { ?>
  <div class="clearfix hr"></div>
  <div class="heading">
    <h3 style="margin:15px 0 10px 0;">Scope Change</h3>
    <table style="margin:0; width:100%;" class="under-border">
      <thead>
        <tr>
          <th align="left" width="20%">Number</th>
          <th align="left" width="20%">Title</th>
          <th align="left" width="20%">Description</th>
          <th align="left" width="20%">Amount</th>
          <th align="left" width="20%">Reason Code</th>
        </tr>
      </thead>
      <tbody>
        <?php
		foreach($getETCNodeScope as $riskKey => $riskVal) {
          $riskNodeEtc = node_load($riskVal);
		  $operationData = array();
	  	  foreach($riskNodeEtc->field_etc_operation_done['und'] as $delta => $delVal) {
	        $operationData[$delVal['value']] = $delVal['value'];
	      }	
		  if(array_key_exists('In Report',$operationData)) {
		    $etcNumber = isset($riskNodeEtc->field_etc_number_calc['und'])?$riskNodeEtc->field_etc_number_calc['und'][0]['value']:'None';
		    $etcTitle = $riskNodeEtc->title;
		    $etcDesc = $riskNodeEtc->body['und'][0]['value'] != ''?substr($riskNodeEtc->body['und'][0]['value'],0,25):' None';
		    $etcAmount = isset($riskNodeEtc->field_etc_amount['und'])?money_format('%(#1n',$riskNodeEtc->field_etc_amount['und'][0]['value']):'None';
		    $etcReason = $riskNodeEtc->field_etc_reason_code['und'][0]['value'] != ''?ucfirst($riskNodeEtc->field_etc_reason_code['und'][0]['value']):'None';
		?>
        <tr>
          <td width="20%"><strong><?php print $etcNumber; ?></strong></td>
          <td width="20%"><?php print $etcTitle; ?></td>
          <td width="20%"><?php print $etcDesc; ?></td>
          <td width="20%"><?php print $etcAmount; ?></td>
          <td width="20%"><?php print $etcReason; ?></td>
        </tr>
        <?php } } ?>
      </tbody>
    </table>
  </div>
  <?php	} ?>
  <?php if(count($getETCNodeRisk) > 0) { ?>
  <div class="clearfix hr"></div>
  <div class="heading">
    <h3 style="margin:15px 0 10px 0;">Risk</h3>
    <table style="margin:0; width:100%;" class="under-border">
      <thead>
        <tr>
          <th align="left" width="20%">Number</th>
          <th align="left" width="20%">Title</th>
          <th align="left" width="20%">Description</th>
          <th align="left" width="20%">Amount</th>
          <th align="left" width="20%">Reason Code</th>
        </tr>
      </thead>
      <tbody>
        <?php
		foreach($getETCNodeRisk as $riskKey => $riskVal) {
          $riskNodeEtc = node_load($riskVal);
		  $operationData = array();
	  	  foreach($riskNodeEtc->field_etc_operation_done['und'] as $delta => $delVal) {
	        $operationData[$delVal['value']] = $delVal['value'];
	      }	
		  if(array_key_exists('In Report',$operationData)) {
		    $etcNumber = isset($riskNodeEtc->field_etc_number_calc['und'])?$riskNodeEtc->field_etc_number_calc['und'][0]['value']:'None';
		    $etcTitle = $riskNodeEtc->title;
		    $etcDesc = $riskNodeEtc->body['und'][0]['value'] != ''?substr($riskNodeEtc->body['und'][0]['value'],0,25):' None';
		    $etcAmount = isset($riskNodeEtc->field_etc_amount['und'])?money_format('%(#1n',$riskNodeEtc->field_etc_amount['und'][0]['value']):'None';
		    $etcReason = $riskNodeEtc->field_etc_reason_code['und'][0]['value'] != ''?ucfirst($riskNodeEtc->field_etc_reason_code['und'][0]['value']):'None';
		?>
        <tr>
          <td width="20%"><strong><?php print $etcNumber; ?></strong></td>
          <td width="20%"><?php print $etcTitle; ?></td>
          <td width="20%"><?php print $etcDesc; ?></td>
          <td width="20%"><?php print $etcAmount; ?></td>
          <td width="20%"><?php print $etcReason; ?></td>
        </tr>
        <?php } } ?>
      </tbody>
    </table>
  </div>
  <?php	} ?>
  <?php if(count($getScheduleNodes) > 0) { ?>
  <div class="clearfix hr"></div>
  <div class="heading">
    <h3 style="margin:15px 0 10px 0;">Project Schedule</h3>
    <table style="margin:0; width:100%;" class="under-border">
      <thead>
        <tr>
          <th align="left">Milestone Description</th>
          <th align="left">Original Date</th>
          <th align="left">Projected Date</th>
          <th align="left">Actual Date</th>
        </tr>
      </thead>
      <tbody>
        <?php
		foreach($getScheduleNodes as $scheduleId => $scheduleVal) {
          $scheduleDetails = node_load($scheduleVal);	
		  $projectMilstone = isset($scheduleDetails->field_project_milestone['und'])?$scheduleDetails->field_project_milestone['und'][0]['value']:'None';
		  $originalDate = isset($scheduleDetails->field_schedule_original['und'])?date('m/d/Y', strtotime($scheduleDetails->field_schedule_original['und'][0]['value'])):'None';
		  $projectedDate = isset($scheduleDetails->field_schedule_projected['und'])?date('m/d/Y', strtotime($scheduleDetails->field_schedule_projected['und'][0]['value'])):'None';
		  $actualDate = isset($scheduleDetails->field_schedule_actual['und'])?date('m/d/Y', strtotime($scheduleDetails->field_schedule_actual['und'][0]['value'])):'None';	  
	     $outputrows[] = array('','',$projectMilstone, $originalDate, $projectedDate, $actualDate,'','',''); ?>
        <tr>
          <td><strong><?php print $projectMilstone; ?></strong></td>
          <td><?php print $originalDate; ?></td>
          <td><?php print $projectedDate; ?></td>
          <td><?php print $actualDate; ?></td>
        </tr>
        <?php } ?>
      </tbody>
    </table>
  </div>
  <?php } 
  if(count($proSafetyImage) > 0) { ?>
  <div class="clearfix hr"></div>
  <div class="heading">
    <h3 style="margin:15 0 10px 0;">Safety Record</h3>
    <table style="width:100%; margin:0 0 20px 0">
      <tbody>
        <tr>
          <td width="190" style="vertical-align:top;"><?php foreach($proSafetyImage as $siImageKey => $siImageVal) { 
		      $fileData = file_load($proSafetyImage[$siImageKey]->field_project_safety_images_fid); 
			  $getImageSI = image_style_url('project_general_images_style',$fileData->uri);
		  ?>
            <img src="<?php print $getImageSI; ?>" alt="res" /></td>
          <?php } ?>
          <td style="vertical-align:top;"><table style="width:100%;">
              <tbody>
                <tr>
                  <td width="260"><div style="padding:0 5px;">
                      <table width="250" align="center">
                        <thead>
                          <tr>
                            <th colspan="3" align="center" style="padding:0;">Most Recent
                              <hr style="margin:0;" /></th>
                          </tr>
                          <tr>
                            <th align="center" style="border-bottom:1px solid #777; font-size:12px; vertical-align:top;">Safety Period</th>
                            <th align="center" style="border-bottom:1px solid #777; font-size:12px; vertical-align:top;">LTA*</th>
                            <th align="center" style="border-bottom:1px solid #777; font-size:12px; vertical-align:top;">Period Hours</th>
                          </tr>
                        </thead>
                        <tbody>
                          <tr>
                            <td align="center"><?php print $getRecentDate; ?></td>
                            <td align="center"><?php print $getRecentLta; ?></td>
                            <td align="center"><?php print $getRecentHours; ?></td>
                          </tr>
                        </tbody>
                      </table>
                    </div></td>
                  <td width="260"><div style="padding:0 5px;">
                      <table width="250" align="center">
                        <thead>
                          <tr>
                            <th colspan="3" align="center" style="padding:0;">Total
                              <hr style="margin:0;" /></th>
                          </tr>
                          <tr>
                            <th align="center" style="border-bottom:1px solid #777; font-size:12px; vertical-align:top;">LTA</th>
                            <th align="center" style="border-bottom:1px solid #777; font-size:12px; vertical-align:top;">Total Work Hours</th>
                            <th align="center" style="border-bottom:1px solid #777; font-size:12px; vertical-align:top;">Incident Rate**</th>
                          </tr>
                        </thead>
                        <tbody>
                          <tr>
                            <td align="center"><?php print $totalLTA; ?></td>
                            <td align="center"><?php print $totalHours; ?></td>
                            <td align="center"><?php $totalEMR = ($totalLTA * 200000)/$totalHours;  print number_format($totalEMR, 2, '.', ''); ?></td>
                          </tr>
                        </tbody>
                      </table>
                    </div></td>
                </tr>
              </tbody>
            </table></td>
        </tr>
      </tbody>
    </table>
  </div>
  <?php } 
  if(count($proAdditionalImage) > 0) { ?>
  <div class="clearfix hr"></div>
  <div class="heading">
    <h3 style="margin:0 0 10px 0;">Additional Project Photos</h3>
    <table style="width:100%;">
      <tbody>
        <tr>
          <?php foreach($proAdditionalImage as $aiImageKey => $aiImageVal) { 
		      $fileData = file_load($proAdditionalImage[$aiImageKey]->field_project_additional_images_fid); 
			  $getImageAI = image_style_url('project_general_images_style',$fileData->uri);
		  ?>
          <td><img src="<?php print $getImageAI; ?>" alt="res" /></td>
          <?php } ?>
        </tr>
      </tbody>
    </table>
  </div>
  <?php } ?>
</div>
<pagebreak suppress="off" />
<?php 
  }
  else if($reportType == 'costsummary') { 
    $reportTitle = 'Project Cost Summary Report';	
	//get project cost summary data	
	foreach($costCode as $ccId => $ccVal) {
	  // Get cost code
	  $costCodeDesc = get_description_by_cost_code($ccVal->field_est_cost_code_value);
	  $capitalContigency = $ccVal->field_capital_contingency_value;	
	  if(!isset($ccArr[$ccVal->field_est_cost_code_value])){
	    $ccArr[$ccVal->field_est_cost_code_value]= array(	    
	      'cc' => $ccVal->field_est_cost_code_value,
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
	$getInvoiceTotal = get_invoice_total_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId);
	$totalInvoiceTotal += $getInvoiceTotal;
	// Get commitment total
	$getCommitmentTotal = get_commitment_total_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId);
	
	$totalCommitmentTotal += $getCommitmentTotal;
	// Get total allocated 
	$getTotalAllocated = get_total_allocated_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId,$getCommitmentTotal);
	$totalAllocated += $getTotalAllocated;
	// Get etc total
	$getETCTotal = get_etc_total_by_cost_code_pdf($ccVal->field_est_cost_code_value,$projectId);
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
  $ccArrTotal= array('originalBudget' => 0,'currentBudget' => 0,'Commitment' => 0,'spent' => 0,'Allocated' => 0,'est' => 0,'PFC' => 0,'Variance' => 0); ?>
<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:50%;"><?php print ucfirst($projectDetails->title); ?></div>
      <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
    </h3>
    <div class="heading" style="background-color:#eee;"> <strong>Project Manager: </strong><span><?php print $projectManager; ?></span> </div>
    <table class="under-border" style="width:100%; margin:0;">
      <thead>
        <tr>
          <th width="120" align="left">Cost Code|Description</th>
          <th width="120" align="right">Original Budget </th>
          <th width="120" align="right">Current Budget </th>
          <th width="120" align="right">Committed</th>
          <th width="120" align="right">Spent</th>
          <th width="120" align="right">Total Allocated</th>
          <th width="120" align="right">ETC</th>
          <th width="120" align="right">PFC</th>
          <th width="120" align="right">Variance</th>
        </tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="8"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>
        <?php foreach($ccArr as $ccId => $ccVal) { 
		        $ccArrTotal= array(
	    			'originalBudget' => $ccArrTotal['originalBudget']+$ccVal['originalBudget'],
					'currentBudget' => $ccArrTotal['currentBudget']+$ccVal['currentBudget'],
					'Commitment' => $ccArrTotal['Commitment']+$ccVal['Commitment'],
					'spent' => $ccArrTotal['spent']+$ccVal['spent'],
					'Allocated' => $ccArrTotal['Allocated']+$ccVal['Allocated'],
					'est' => $ccArrTotal['est']+$ccVal['est'],
					'PFC' => $ccArrTotal['PFC']+$ccVal['PFC'],
					'Variance' => $ccArrTotal['Variance']+$ccVal['Variance'],
	  			);
		?>
        <tr>
          <td><?php print $ccVal['cost_code']; ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['originalBudget']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['currentBudget']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['Commitment']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['spent']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['Allocated']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['est']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['PFC']); ?></td>
          <td align="right"><?php print money_format('%(#1n',$ccVal['Variance']); ?></td>
        </tr>
        <?php } ?>
      </tbody>
      <tfoot>
        <tr>
          <th align="left">Project Totals
            </td>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['originalBudget']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['currentBudget']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['Commitment']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['spent']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['Allocated']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['est']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['PFC']); ?></th>
          <th align="right"><?php print money_format('%(#1n',$ccArrTotal['Variance']); ?></th>
        </tr>
      </tfoot>
    </table>
  </div>
</div>
<?php }
  else if($reportType == 'costdetail') { 
    $reportTitle = 'Project Cost Detail Report';
	$query= db_select('node','n'); 
    $query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
    $query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
    $query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');  
    $query->join('field_data_field_project_estimate_amount','ea','ea.entity_id = enode.nid');    
    $query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');
    $query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
    $query->fields('cc',array('field_est_cost_code_value'));
    $query->fields('ea',array('field_project_estimate_amount_value'));
    $query->condition('es.field_project_estimate_status_value', 'approved', '=');
	$query->orderBy('es.field_project_estimate_status_value', 'ASC');
    $query->condition('pr.field_project_reference_nid', $projectId, '=');        
    $costCode = $query->execute()->fetchAll(); ?>
<div class="project-reposrt">
  <div class="page_details">
    <h3 style="background: #eee; float:left; width:100%; height:20px;">
      <div style="float:left; width:45%; padding:10px;"><?php print ucfirst($projectDetails->title); ?></div>
      <div style="float:right; width:45%; padding:10px; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
    </h3>
    <div class="heading" style="background-color:#eee;"> <strong>Project Manager: </strong><span><?php print $projectManager; ?></span> </div>
    <table class="under-border" style="width:100%; margin:0;">
      <thead>
        <tr>
          <th width="120" align="left">Cost Code|Description</th>
          <th width="120" align="right">Original Budget </th>
          <th width="120" align="right">Current Budget </th>
          <th width="120" align="right">Committed</th>
          <th width="120" align="right">Spent</th>
          <th width="120" align="right">Total Allocated</th>
          <th width="120" align="right">ETC</th>
          <th width="120" align="right">PFC</th>
        </tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="8"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>
        <?php foreach($ccArr as $ccKey => $ccVals) { ?>
        <tr>
          <td width="120" align="left"><?php print $ccVals['cost_code']; ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n', $ccVals['originalBudget']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['currentBudget']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['Commitment']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['spent']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['Allocated']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['est']); ?></td>
          <td width="120" align="right"><?php print money_format('%(#1n',$ccVals['PFC']); ?></td>
        </tr>
        <?php 
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
		} ?>
      </tbody>
      <tfoot>
        <tr>
          <th width="120" align="right">Project Totals</th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['originalBudget']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['currentBudget']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['Commitment']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['spent']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['Allocated']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['est']); ?></th>
          <th width="120" align="right"><?php print money_format('%(#1n',$ccArrTotal['PFC']); ?></th>
        </tr>
      </tfoot>
    </table>
  </div>
</div>
<pagebreak suppress="off" />
<?php
      $queryCommit= db_select('node','n'); 
      $queryCommit->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
      $queryCommit->join('node','enode','enode.nid=er.field_estimate_reference_nid');
      $queryCommit->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');      
      $queryCommit->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');
      $queryCommit->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
      $queryCommit->fields('cc',array('field_est_cost_code_value'));
      $queryCommit->condition('es.field_project_estimate_status_value', 'approved', '=');
      $queryCommit->condition('pr.field_project_reference_nid', $projectId, '=');        
      $queryCommit->orderBy('cc.field_est_cost_code_value', 'ASC');
      $queryCommit->groupBy('cc.field_est_cost_code_value');
      $costCodeCoomit = $queryCommit->execute()->fetchCol();  
     ?>
<div class="page_details" style="float:left; width:100%; padding:0;">
  <h3 style="background: #eee; float:left; width:100%; height:20px;">
    <div style="float:left; width:45%; padding:10px;"><?php print ucfirst($projectDetails->title); ?></div>
    <div style="float:right; width:45%; padding:10px; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
  </h3>
  <div class="heading" style="background-color:#eee; float:left; width:100%;">
    <div style="float:left; width:80%; padding:10px;"><strong>Project Manager: </strong><span><?php print $projectManager; ?></span></div>
  </div>
  <div style="float:left; width:100%;">
    <?php 
	foreach($costCodeCoomit as $ccKey => $ccValData) { 
	  $query2 = db_select('node','n');
                    $query2->join('field_data_field_commitment_ws_code','cc','cc.entity_id = n.nid');
                    $query2->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
                    $query2->fields('n',array('nid'));
                    $query2->condition('cc.field_commitment_ws_code_value', $ccValData, '=');
                    $query2->condition('pr.field_project_reference_nid', $projectId, '=');
                    $query2->condition('n.type', 'project_commitement', '=');	
                    $getCommit = $query2->execute()->fetchCol();
					if(!empty($getCommit)) {    
	?>
    <div style="float:left; width:100%; font-size:12px;">
      <div style="float:left; width:15%; padding:0;"><strong style="padding-right:5px;"><?php print $ccValData; ?></strong></div>
      <div style="float:left; width:85%; padding:0;">
        <table class="under-border" style="width:100%; margin:0;">
          <thead>
            <tr>
              <th width="120" style="text-align:left; padding:5px;">Commitment Number</th>
              <th width="120" style="text-align:left; padding:5px;">Vendor</th>
              <th width="120" style="text-align:left; padding:5px;">Description</th>
              <th width="120" style="text-align:left; padding:5px;">Date</th>
              <th width="120" style="text-align:left; padding:5px;">Commited Amount</th>
              <th width="120" style="text-align:left; padding:5px;">Invoiced Against</th>
              <th width="120" style="text-align:left; padding:5px;">Commitment Balance</th>
            </tr>
            <tr>
              <td style="margin:0; width:100%; padding:0;" colspan="7"><div class="clearfix hr"></div></td>
            </tr>
          </thead>
          <tbody>
            <?php                     	
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
                    ?>
            <tr>
              <td style="text-align:left; padding:5px;"><?php print $commitNode->field_commitment_number_calculat['und'][0]['value'];?></td>
              <td style="text-align:left; padding:5px;"><?php print $coomitVendoer!=''?$coomitVendoer:'None'; ?></td>
              <td style="text-align:left; padding:5px;"><?php print $commitNode->field_commitment_item_descriptio['und'][0]['value']!=''?strip_tags($commitNode->field_commitment_item_descriptio['und'][0]['value']):'None';?></td>
              <td style="text-align:left; padding:5px;"><?php print $date = date('m/d/Y', $commitNode->created);?></td>
              <td style="text-align:left; padding:5px;"><?php print '$'.number_format($commitAmt,2);?></td>
              <td style="text-align:left; padding:5px;"><?php print '$'.number_format($getTotalSpendingAmt,2);?></td>
              <td style="text-align:left; padding:5px;"><?php print '$'.number_format($commitBalance,2);?></td>
            </tr>
            <tr>
              <td colspan="2">&nbsp;</td>
              <td colspan="5" style="text-align:left; padding:0; width:100%;"><?php 
                          $query2 = db_select('node','n');
                          $query2->join('field_data_field_invoice_commitment','ic','ic.entity_id = n.nid');
                          $query2->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
                          $query2->fields('n',array('nid'));
                          $query2->condition('ic.field_invoice_commitment_nid', $commitNode->nid, '=');
                          $query2->condition('pr.field_project_reference_nid', $projectId, '=');
                          $query2->condition('n.type', 'project_spending', '=');	
                          $getInv = $query2->execute()->fetchCol();	
                          if(!empty($getInv)) {
                        ?>
                <table class="under-border" style="width:100%; margin:0;">
                  <thead>
                    <tr>
                      <th colspan="4" style="text-align:left; padding:5px;">Invoice Number</th>
                    </tr>
                    <tr>
                      <td colspan="4" style="margin:0; width:100%; padding:0;"><div class="clearfix hr"></div></td>
                    </tr>
                  </thead>
                  <tbody>
                    <?php
                        foreach($getInv as $invKey => $invId) {
                         $invNode = node_load($invId);
                         $invNumber = isset($invNode->field_invoice_number_cal['und'])?$invNode->field_invoice_number_cal['und'][0]['value']:'None';
                         $invDate = isset($invNode->field_invoice_date['und'])?date('m/d/Y',strtotime($invNode->field_invoice_date['und'][0]['value'])):'None';
                         $invAmt = isset($invNode->field_invoice_amount['und'])?'$'.number_format($invNode->field_invoice_amount['und'][0]['value'],2):'$0.00';
                        ?>
                    <tr>
                      <td colspan="4" style="margin:0; width:100%; padding:0;"><div class="clearfix hr"></div></td>
                    </tr>
                    <tr>
                      <td width="120" style="text-align:left; padding:5px;"><?php print $invNumber; ?></td>
                      <td width="120" style="text-align:left; padding:5px;"><?php print $invDate; ?></td>
                      <td>&nbsp;</td>
                      <td width="120" style="text-align:left; padding:5px;"><?php print $invAmt; ?></td>
                    </tr>
                    <?php } ?>
                  </tbody>
                </table></td>
            </tr>
            <?php }} ?>
          </tbody>
        </table>
      </div>
    </div>
    <?php } }?>
  </div>
</div>
<pagebreak suppress="off" />
<?php }
  else if($reportType == 'commitment') {
	global $company;  
    $reportTitle = 'Project Commitment Report';	
	$query= db_select('node','n'); 
	$query->join('field_data_field_estimate_reference','er','er.entity_id = n.nid');
	$query->join('node','enode','enode.nid=er.field_estimate_reference_nid');
	$query->join('field_data_field_project_estimate_status','es','es.entity_id = enode.nid');      
	$query->join('field_data_field_project_reference','pr','enode.nid=pr.entity_id');
	$query->leftjoin('field_data_field_est_cost_code','cc','cc.entity_id=n.nid');
	$query->fields('cc',array('field_est_cost_code_value'));
	$query->condition('es.field_project_estimate_status_value', 'approved', '=');
	$query->condition('pr.field_project_reference_nid', $projectId, '=');        	
	$query->groupBy('cc.field_est_cost_code_value');
	$query->orderBy('cc.field_est_cost_code_value', 'ASC');
	$costCodeCoomit = $query->execute()->fetchCol(); ?>
<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:50%;"><?php print ucfirst($projectDetails->title); ?></div>
      <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
    </h3>
    <div class="heading" style="margin: 0 0 40px 0;"> <strong>Project Manager:&nbsp;</strong><span><?php print $projectManager; ?></span> </div>
    <?php 
	foreach($costCodeCoomit as $ccKey => $ccVal) { 
	  $query= db_select('node','n');
	  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));    
	  $query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');
	  $query->join('field_data_field_commitment_ws_code','cc','cc.entity_id = n.nid');
	  $query->fields('n', array('nid'));
	  $query->condition('cc.field_commitment_ws_code_value', $ccVal, '=');
	  $query->condition('pr.field_project_reference_nid', $projectId, '=');
	  $query->condition('om.gid', $company->nid, '=');
	  $query->condition('pr.bundle','project_commitement','=');
	  $getCommitmentNodes = $query->execute()->fetchCol();
	  if(!empty($getCommitmentNodes)) {
	?>
    <table class="thead_border under-border" style="width:100%; margin:0 0 20px 0;">
      <thead>
        <tr>
          <th style="width:20%" align="left">Cost Code | Description</th>
          <th style="width:10%" align="left">Commitment <br />
            Number</th>
          <th style="width:10%" align="left">Vendor</th>
          <th style="width:20%" align="left">Description</th>
          <th align="left">Date</th>
          <th align="left">Amount</th>
          <!--<th>Change Orders</th>
          <th>Invoiced Against</th>-->
          <th align="right">Invoiced <br />
            Against</th>
          <th align="right">Variance</th>
        </tr>
      </thead>
      <tbody>
        <?php 	  
	  //if(empty($getCommitmentNodes)) { continue; }
	  $totalCommitAmt = 0;
	  $totalInvoice = 0;	
	  foreach($getCommitmentNodes as $commitNodeKey => $comitNodeVal) { 
	    $commitmentNode = node_load($comitNodeVal);			  
		$commitNumber = isset($commitmentNode->field_commitment_number_calculat['und'])?$commitmentNode->field_commitment_number_calculat['und'][0]['value']:'None';
		$coomitVendoer = isset($commitmentNode->field_vendor['und'])?$commitmentNode->field_vendor['und'][0]['value']:'None';
		$totalCommit = isset($commitmentNode->field_total_commit_clone['und'])?$commitmentNode->field_total_commit_clone['und'][0]['value']:'';
		if($coomitVendoer != 'None' && is_numeric($coomitVendoer)) {
		  $coomitVendoer = node_load($coomitVendoer)->title;
		}
		else {
		  $coomitVendoer = $coomitVendoer;
		}
		$commitDesc = isset($commitmentNode->body['und'])?$commitmentNode->body['und'][0]['value']:'None';
		$commitDate = date('m/d/Y', $commitmentNode->created);
		if(isset($commitmentNode->field_commitment_po_final_total['und'])) {
		  if($commitmentNode->field_commitment_po_final_total['und'][0]['value'] != '') {
		    $commitAmt = $commitmentNode->field_commitment_po_final_total['und'][0]['value'];
		  }
		  else {
		    $commitAmt = 0;
		  }
		}
		else {
		  $commitAmt = 0;
		}		
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
		$varianceAmt = $commitAmt - $invoiceAgainst;
		$totalVar += $varianceAmt; 
    ?>
        <tr>
          <td><?php print get_description_by_cost_code($ccVal); ?></td>
          <?php if($totalCommit != '') { ?>
          <td><?php print $commitNumber.' - '.$totalCommit; ?></td>
          <?php }  else { ?>
          <td><?php print $commitNumber; ?></td>
          <?php } ?>
          <td><?php print $coomitVendoer; ?></td>
          <td><?php print substr($commitDesc,0,25); ?></td>
          <td><?php print $commitDate; ?></td>
          <td align="right"><?php print '$'.number_format($commitAmt,2); ?></td>
          <td align="right"><?php print '$'.number_format($invoiceAgainst,2); ?></td>
          <td align="right"><?php print '$'.number_format($varianceAmt,2); ?></td>
        </tr>
        <?php } 
		  $finalTotalInvoice += $totalInvoice; 
		  $finalTotalCommit += $totalCommitAmt;
		  $finalTotalVar += $totalVar;
		?>
      </tbody>
      <tfoot>
        <tr>
          <th align="left">&nbsp;</th>
          <th align="left">&nbsp;</th>
          <th align="left">&nbsp;</th>
          <th align="left">&nbsp;</th>
          <th align="left">Total</th>
          <th align="right"><?php print '$'.number_format($totalCommitAmt,2); ?></th>
          <th align="right"><?php print '$'.number_format($totalInvoice,2); ?></th>
          <th align="right"><?php print '$'.number_format($totalVar,2); ?></th>
        </tr>
      </tfoot>
    </table>
    <?php } }?>
    <table class="thead_border under-border" style="width:100%; margin:0 0 20px 0;">
      <tr>
        <th style="width:20%" align="left">&nbsp;</th>
        <th style="width:10%" align="left">&nbsp;</th>
        <th style="width:10%" align="left">&nbsp;</th>
        <th style="width:20%" align="left">&nbsp;</th>
        <th align="left">Total</th>
        <th align="right"><?php print '$'.number_format($finalTotalCommit,2); ?></th>
        <th align="right"><?php print '$'.number_format($finalTotalInvoice,2); ?></th>
        <th align="right"><?php print '$'.number_format($finalTotalVar,2); ?></th>
      </tr>
    </table>
  </div>
</div>
<pagebreak suppress="off" />
<?php }
  else if($reportType == 'safety') {
	global $company;  
    $reportTitle = 'Project Safety Report';	
	$query = db_select('node','n');
    $query->join('field_data_field_project_reference','pr','pr.entity_id = n.nid');
    $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));  
    $query->fields('n',array('nid'));
    $query->condition('om.gid', $company->nid, '=');
    $query->condition('pr.field_project_reference_nid', $projectId, '=');
    $query->condition('n.type', 'project_safety', '=');
    $getSafetyNodes = $query->execute()->fetchCol();
	?>
<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:50%;"><?php print ucfirst($projectDetails->title); ?></div>
      <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
    </h3>
    <div class="heading" style="margin: 0 0 40px 0;"> <strong>Project Manager:&nbsp;</strong><span><?php print $projectManager; ?></span> </div>
    <?php if(!empty($getSafetyNodes)) { ?>
    <table class="thead_border under-border" style="width:100%; margin:0 0 20px 0;">
      <thead>
        <tr>
          <th style="width:10%" align="left">Period Start</th>
          <th style="width:10%" align="left">Period End</th>
          <th style="width:15%" align="left">Lost Time Accidents</th>
          <th style="width:10%" align="left">Minor</th>
          <th style="width:10%" align="left">Hours</th>
          <th style="width:35%" align="left">Comment</th>
        </tr>
      </thead>
      <tbody>
        <?php 	  
	  foreach($getSafetyNodes as $saftyId => $saftyVal){
	    $safetyNode = node_load($saftyVal);
	    $startDate = isset($safetyNode->field_start_date['und'])?date('m/d/Y', strtotime($safetyNode->field_start_date['und'][0]['value'])):'None';
	    $endDate = isset($safetyNode->field_end_date['und'])?date('m/d/Y', strtotime($safetyNode->field_end_date['und'][0]['value'])):'None';
	    $ltAccidents = isset($safetyNode->field_lost_time_accidents['und'])?$safetyNode->field_lost_time_accidents['und'][0]['value']:'None';
	    $totalLTA += $ltAccidents;
	    $minor = isset($safetyNode->field_minor['und'])?$safetyNode->field_minor['und'][0]['value']:'None';
	    $hours = isset($safetyNode->field_hours_this_period['und'])?number_format($safetyNode->field_hours_this_period['und'][0]['value']):'None';
	    $safteyComment = isset($safetyNode->body['und'])?$safetyNode->body['und'][0]['value']:'None';
	    $totalHour += $hours;		
	  ?>
        <tr>
          <td><?php print $startDate; ?></td>
          <td><?php print $endDate; ?></td>
          <td><?php print $ltAccidents; ?></td>
          <td><?php print $minor; ?></td>
          <td><?php print $hours; ?></td>
          <td><?php print substr($safteyComment,0,100).'...'; ?></td>
        </tr>
        <?php } $totalEMR = ($totalLTA * 200000)/$totalHour; ?>
      </tbody>
      <tfoot>
        <tr>
          <th align="left">&nbsp;</th>
          <th align="left">Incident Rate:</th>
          <th align="left"><?php print round($totalEMR, 2); ?></th>
          <th align="left">Total Hours Worked:</th>
          <th align="left"><?php print $totalHour; ?></th>
          <th align="left">&nbsp;</th>
        </tr>
        <!--<tr>
          <th align="left">&nbsp;</th>
          <th align="left">&nbsp;</th>
          <th align="left">Incident Rate:</th>
          <th align="left"><?php print round($totalEMR, 2); ?></th>
          <th align="left">&nbsp;</th>
          <th align="left">&nbsp;</th>
        </tr>-->
      </tfoot>
    </table>
    <?php  } else { ?>
    <h2>No data found</h2>
    <?php }?>
  </div>
</div>
<pagebreak suppress="off" />
<?php  }
  else if($reportType == 'estimate') { 
    $reportTitle = 'Budget Estimate Report';
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
    $query->condition('pr.field_project_reference_nid', $projectId, '=');        
    $estimateData = $query->execute()->fetchAll(); ?>
<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:50%;"><?php print ucfirst($projectDetails->title); ?></div>
      <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
    </h3>
    <div class="heading" style="background: #E3EFFC; padding:2px 10px; border:1px solid #CCC; margin:0 0 20px 0;">Capital</div>
    <?php foreach($estimateData as $estKey => $estVal) { $mainTotal += $estVal->field_est_line_item_amt_value; ?>
    <table class="thead_border" style="width:100%; margin:0 0 20px 0;">
      <thead>
        <tr>
          <th align="left">Cost Code|Description</th>
          <th align="right">Line Item Cost</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td align="left"><strong><?php print get_description_by_cost_code($estVal->field_est_cost_code_value); ?></strong></td>
          <td align="right"><strong><?php print '$'.number_format($estVal->field_est_line_item_amt_value); ?></strong></td>
        </tr>
      </tbody>
      <tfoot>
        <tr>
          <td colspan="2"><hr></td>
        </tr>
        <tr>
          <td><?php print get_description_by_cost_code($estVal->field_est_cost_code_value); ?></td>
          <td align="right"><?php print '$'.number_format($estVal->field_est_line_item_amt_value); ?></td>
        </tr>
      </tfoot>
    </table>
    <?php } ?>
    <table class="thead_border" style="width:100%; margin:0 0 20px 0;">
      <tfoot>
        <tr style="background: #E3EFFC; padding:2px 10px; border:1px solid #CCC;">
          <td>Capital Total:</td>
          <td align="right"><?php print '$'.number_format($mainTotal); ?></td>
        </tr>
      </tfoot>
    </table>
    <table class="thead_border" style="width:100%;">
      <tr style="background: #E3EFFC; padding:2px 10px; border:1px solid #000;">
        <th style="text-align:left;">Total:
          </td>
        <td align="right"><?php print '$'.number_format($mainTotal); ?></td>
      </tr>
    </table>
  </div>
</div>
<pagebreak suppress="off" />
<?php } 
  else if ($reportType == 'asset') {
    $reportTitle = 'Project Assets Report';
    $projectName = $projectDetails->title;
    $projectNumber = $projectDetails->field_project_mgmt_number['und'][0]['value'];
	$projectLocID = _get_company_region_address($company);
	$header_arr = array('New Asset<br/>Number', 'Company', 'Dept', 'Project Number', 'AssetClass', 'Location', 'Asset Description', 'Description 2', 'Serial #', 'Model No #', 'Vendor Number', 'Vendor Name', 'Acquisition<br/>Date', 'Acquisition<br/>Cost', 'Quantity');
 ?>
<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:50%; text-align:left;"><?php print $projectName; ?></div>
      <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectNumber); ?></div>
    </h3>
    <table class="under-border" style="width:100%; margin:0;">
      <thead>
        <tr>
          <?php
            foreach ($header_arr as $key => $value) {
              print '<th width="100px" align="left">' . $value . '</th>';
            }
           ?>
        </tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="8"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>
        <?php
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
        $totalAssetVal = 0;
        foreach ($getAssetData as $assetKey => $assetVal) {
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
          $row_arr = array($assetNumber, $company->title, '', $projectNumber, !empty($assetClassName) ? $assetClassName : '', $projectLocID, $assetDesc, '', $assetSerial, $assetModel, '', $asset_vendor_name, '', $assetAcqCost, $assetQuan);
          $i = 1;
          print '<tr>';
          foreach ($row_arr as $key => $value) {
            if ($key == 13) {
              print '<td align="right">$' . number_format($value) . '</td>';
            }
            else if ($key == 14) {
              print '<td align="center">' . $value . '</td>';
            }
            else {
              print '<td>' . $value . '</td>';
            }
          }
          print '</tr>';
        }
      } ?>
      </tbody>
      <tfoot>
        <tr>
          <th align="left">Total</th>
          <th colspan="13" align="right"><?php print '$'.number_format($totalAssetVal); ?></th>
          <!-- <th colspan="5" align="right"></th> --> 
        </tr>
      </tfoot>
    </table>
  </div>
</div>
<?php } 
  else if ($reportType == 'asset-spend') {
    // Getting all the assets list by global company and 
	// by selected project
	$query = db_select('node','n');     
    $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');    
    $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
    $query->fields('n',array('nid'));
    $query->condition('n.type', 'program_assets', '=');
    $query->condition('om.gid', $company->nid, '=');
    $query->condition('pr.field_project_reference_nid', $projectId, '=');  
    $getAssetData = $query->execute()->fetchCol();
	
	$loadProData = node_load($projectId); ?>
	<div class="project-reposrt">
  <div class="page_details">
    <h3 style="padding:10px; background: #eee; width:100%; height:20px;">
      <div style="float:left; width:50%;"><?php print ucfirst($projectDetails->title); ?></div>
      <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectDetails->field_project_mgmt_number['und'][0]['value']); ?></div>
    </h3>
    <div class="heading" style="background-color:#eee;"> <strong>Project Manager: </strong><span><?php print $projectManager; ?></span></div>
    <?php  
	if(!empty($getAssetData)) {
	  foreach($getAssetData as $assetKey => $assetNid) {	    
	    $nodeDetails = node_load($assetNid);		
		$city = ''; $state = ''; $addressType = '';
		module_load_include('inc', 'addressfield', 'addressfield.administrative_areas');
		if(isset($loadProData->field_project_location_facility['und'])) {
		  $addressType = 'Faciltiy';  
		  $getFacitiy = $loadProData->field_project_location_facility['und'][0]['target_id'];
		  $getFaciltiyData = node_load($getFacitiy);
		  $country = $getFaciltiyData->field_facility_address['und'][0]['country'];
		  $stateListing = addressfield_get_administrative_areas($country);
		  $city = $getFaciltiyData->field_facility_address['und'][0]['locality'];
		  $state = $stateListing[$getFaciltiyData->field_facility_address['und'][0]['administrative_area']];
		}
		else if(isset($loadProData->field_project_location_site['und'])) {
		  $addressType = 'Site';
		  $getFacitiy = $loadProData->field_project_location_site['und'][0]['target_id'];
		  $getFaciltiyData = node_load($getFacitiy);
		  $country = $getFaciltiyData->field_facility_address['und'][0]['country'];
		  $stateListing = addressfield_get_administrative_areas($country);
		  $city = $getFaciltiyData->field_facility_address['und'][0]['locality'];
		  $state = $stateListing[$getFaciltiyData->field_facility_address['und'][0]['administrative_area']];
		}
		else if(isset($loadProData->field_project_location_region['und'])) {
		  $addressType = 'Region';  
		  $getFacitiy = $loadProData->field_project_location_region['und'][0]['target_id'];
		  $getFaciltiyData = node_load($getFacitiy);
		  $country = $getFaciltiyData->field_facility_address['und'][0]['country'];
		  $stateListing = addressfield_get_administrative_areas($country);
		  $city = $getFaciltiyData->field_facility_address['und'][0]['locality'];
		  $state = $stateListing[$getFaciltiyData->field_facility_address['und'][0]['administrative_area']];
		}
		$assetImgThumb = '';
		$makeDefault = ($nodeDetails->field_make_defaults['und'][0]['value'] != '')?$nodeDetails->field_make_defaults['und'][0]['value']:'';
		$acquisitionDate = ($nodeDetails->field_acquisition_date['und'][0]['value'] != '')?date('m/d/Y', strtotime($nodeDetails->field_acquisition_date['und'][0]['value'])):'';
		$sinNumber = ($nodeDetails->field_project_asset_sin_number['und'][0]['value'] != '')?$nodeDetails->field_project_asset_sin_number['und'][0]['value']:'';
		$serialNumber = ($nodeDetails->field_asset_pin_number['und'][0]['value'] != '')?$nodeDetails->field_asset_pin_number['und'][0]['value']:'';
		if(isset($nodeDetails->field_system_asset_attachment['und'])) {
		  foreach($nodeDetails->field_system_asset_attachment['und'] as $addKey => $addVal) {
			if(!empty($makeDefault)) {
			  if($makeDefault == $addVal['fid']) {
			    $assetImgThumb = '<img src="'.image_style_url('thumbnail',$addVal['uri']).'">';
			  }
		    }
		    else {
			  $assetImgThumb = '<img src="'.image_style_url('thumbnail',$nodeDetails->field_system_asset_attachment['und'][0]['uri']).'">';
		    }
		  } 
		}
		else {
		  $assetImgThumb = '';
		}
		$query = db_select('node','n');
		$query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
		$query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');
		$query->fields('n', array('nid'));
		$query->condition('pr.field_project_reference_nid', $projectId, '=');
		$query->join('field_data_field_asset_description_spending','ad','n.nid=ad.entity_id');
		$query->condition('ad.field_asset_description_spending_value', '%' . db_like($assetNid) . '%', 'LIKE');
		$query->condition('n.type','project_spending','=');
		$query->condition('om.gid', $company->nid, '=');
		$totalSpend = $query->execute()->rowCount();
		// Getting acuasition cost
		$assetAcqCost = 0;
		if (isset($nodeDetails->field_asset_cost['und'][0]['value'])) {
			$assetAcqCost += $nodeDetails->field_asset_cost['und'][0]['value'];
		  }
		if (isset($nodeDetails->field_asset_installation['und'][0]['value'])) {
			$assetAcqCost += $nodeDetails->field_asset_installation['und'][0]['value'];
		  }
		if (isset($nodeDetails->field_asset_outside_consultant['und'][0]['value'])) {
			$assetAcqCost += $nodeDetails->field_asset_outside_consultant['und'][0]['value'];
		}
		if (isset($nodeDetails->field_asset_internal_charge['und'][0]['value'])) {
			$assetAcqCost += $nodeDetails->field_asset_internal_charge['und'][0]['value'];
		}
		?>
    <div class="associated-overflow" style="margin-bottom:10px; float:left; width:100%;">      
      <div style="margin-bottom:10px; float:left; width:600px;"><?php print $assetImgThumb; ?></div>
      <div class="row" style="margin-bottom:10px; float:left; width:600px;">
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Asset Name: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $nodeDetails->title; ?></div>
        <div class="col-md-2" style="float:left; width:100px;">
          <label>SIN #: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $sinNumber; ?></div>
      </div>
      <div class="row" style="margin-bottom:10px; float:left; width:600px;">
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Acquisition Cost: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print '$'.number_format($assetAcqCost,2); ?></div>
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Serial #: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $serialNumber; ?></div>
      </div>
      <?php if(!empty($addressType)) { 
		     $city = $city!= ''?$city.', ':'';
			 $state = $state!= ''?$state:'';
		   ?>
      <div class="row" style="margin-bottom:10px; float:left; width:600px;">
        <div class="col-md-2" style="float:left; width:100px;">
          <label><?php print $addressType; ?> </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $city.' '.$state; ?></div>
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Quantity: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $totalSpend; ?></div>
      </div>
      <?php } else { ?>
      <div class="row" style="margin-bottom:10px; float:left; width:600px;">
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Adress: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;">None</div>
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Quantity: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $totalSpend; ?></div>
      </div>
      <?php } ?>
      <div class="row" style="margin-bottom:10px; float:left; width:600px;">
        <div class="col-md-2" style="float:left; width:100px;">
          <label>City: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;">Test City</div>
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Acquisition Date: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print $acquisitionDate; ?></div>
      </div>
      <div class="row" style="margin-bottom:10px; float:left; width:600px;">
        <div class="col-md-2" style="float:left; width:100px;"></div>
        <div class="col-md-3" style="float:left; width:200px;"></div>
        <div class="col-md-2" style="float:left; width:100px;">
          <label>Project Name: </label>
        </div>
        <div class="col-md-3" style="float:left; width:200px;"><?php print _get_title_of_node($proId); ?></div>
      </div>
      <h3 style="padding:10px; background: #eee; width:100%; height:20px;">Associated Spending For - <?php print $nodeDetails->title; ?></h3>
      <div class="spending_details_by_asset" style="margin-bottom:10px; float:left; width:100%;">
        <style>
.spending_details_by_asset table{width:100%;border-collapse: collapse;} .spending_details_by_asset table tr td, .spending_details_by_asset table tr th{padding:8px; border:1px solid #CCC;} .spending_details_by_asset table tr th{background:#265a7f; color:#FFF;}
</style>
        <?php print _get_spending_details_by_asset_pdf($nodeDetails->nid,$projectId); ?></div>
    </div><pagebreak suppress="off" />
    <?php  } ?>
  </div>
</div>
<?php } 
  }
} 
if ($reportType == 'spending-forecast') {
    // First creating Summary of each project.
    $cur_year = date('Y');
    $summary_header = array(t('Project'), t('Previous Year Total'), $cur_year . ' ' . t('Spending'), t('Future Year Total'), t('Spent To Date'), t('PFC'));
    ?>
<div class="project-reposrt">
<div class="page_details">
<h3 style="padding:10px; background: #eee; width:100%; height:20px;">
  <div style="float:left; width:50%; text-align:left;">Summary</div>
  <!-- <div style="float:right; width:50%; text-align:right;"><?php print ucfirst($projectNumber); ?></div>  --> 
</h3>
<table class="under-border" style="width:100%; margin:0;">
  <thead>
    <tr>
      <?php
           foreach ($summary_header as $key => $value) {
             print '<th width="200px" align="center">' . $value . '</th>';
           }
          ?>
    </tr>
    <tr>
      <td style="margin:0; width:100%;" colspan="8"><div class="clearfix hr"></div></td>
    </tr>
  </thead>
  <tbody>
    <?php
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
    print '<tr>';
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
        if ($i == 0) {
          print '<td align="center">' . $summary_row[$i] . '</td>';
        }
        else {
          print '<td align="center">$ ' . number_format($summary_row[$i]) . '</td>';
        }
      }
    }
    else {
      // Just showing that no forecast available.
      print '<td align="center">' . $pSTitle . '</td>';
      print '<td align="center" colspan = "5"><strong>' . t('No Spending Forecast Found!') . '</strong></td>';
    }
    print '</tr>';
  }
  ?>
  </tbody>
</table>
<!-- End Creating Summary -->

<h3 style="padding:10px; background: #eee; width:100%; height:20px;">
  <div style="float:left; width:50%; text-align:left;">Details</div>
</h3>
<?php
 // Working on detailed report.

 foreach ($last_forecast_arr as $key => $forecast) {
  if (empty($forecast)) {
    continue;
  }

  $projectSpending = node_load($key);
  $pSTitle = $projectSpending->title;
  $currentQuarter = _get_current_quarter(date('n'));

  print '<h5 style="padding:10px; background: #eee; width:100%; height:20px;">
          <div style="float:left; width:50%; text-align:left;">' . $pSTitle . '</div>
          <div style="float:right; width:50%; text-align:right;">Commitment Forecast</div>
        </h5>';
  print '<table class="under-border" style="width:100%; margin:0;">
      <thead><tr>';

  $detail_header = array(
    t('Commitment Number'),
    t('Company Name'),
    t('Amount'),
    t('Total Spent'),
    t('Previous Years'),
    date('Y') . '<br/>' . t('Quarter 1'),
    date('Y') . '<br/>' . t('Quarter 2'),
    date('Y') . '<br/>' . t('Quarter 3'),
    date('Y') . '<br/>' . t('Quarter 4'),
    date('Y') . '<br/>' . t('Spending'),
    t('Future Years'),
    t('Variance'),
  );

  $i = 0;
  foreach ($detail_header as $d_key => $d_val) {
    if ($currentQuarter == 'firstQuarter') {
      if ($i == 5) {
        print '<th width="150px" align="center" colspan="2">' . date('Y') . ' ' . t('Quarter 1') . '</th>';
      }
      else {
		if ($i < 2) {
			print '<th width="100px" align="left">' . $d_val . '</th>';
		}
		else {
			print '<th width="100px" align="right">' . $d_val . '</th>';
		}
      }
    }
    elseif ($currentQuarter == 'secondQuarter') {
      if ($i == 6) {
        print '<th width="150px" align="center" colspan="2">' . date('Y') . ' ' . t('Quarter 2') . '</th>';
      }
      else {
        if ($i < 2) {
			print '<th width="100px" align="left">' . $d_val . '</th>';
		}
		else {
			print '<th width="100px" align="right">' . $d_val . '</th>';
		}
      }
    }
    elseif ($currentQuarter == 'thirdQuarter') {
      if ($i == 7) {
        print '<th width="150px" align="center" colspan="2">' . date('Y') . ' ' . t('Quarter 3') . '</th>';
      }
      else {
        if ($i < 2) {
			print '<th width="100px" align="left">' . $d_val . '</th>';
		}
		else {
			print '<th width="100px" align="right">' . $d_val . '</th>';
		}
      }
    }
    else if($currentQuarter == 'fourthQuarter') {
      if ($i == 8) {
        print '<th width="150px" align="center" colspan="2">' . date('Y') . ' ' . t('Quarter 4') . '</th>';
      }
      else {
        if ($i < 2) {
			print '<th width="100px" align="left">' . $d_val . '</th>';
		}
		else {
			print '<th width="100px" align="right">' . $d_val . '</th>';
		}
      }
    }
    $i++;
  } // Finished making header for each project.

  print '</tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="12"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>'; // Starting tbody.


  $query= db_select('node','n');
  $query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');   
  $query->fields('n', array('nid'));
  $query->condition('pr.field_project_reference_nid', $key, '=');
  $query->condition('pr.bundle','project_commitement','=');
  $getCommitmentNodes = $query->execute()->fetchCol();
  $detail_row_total = array();
  foreach($getCommitmentNodes as $commitKey => $commitVal) {
    print '<tr>';
	
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

    // $i = 0;

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
      if ($i > 1) {
        print '<td align="right">$' . number_format($detail_row[$i]) . '</td>';
      }
      else {
        print '<td align="left">' . $detail_row[$i] . '</td>';
      }
    }
    print '</tr>';
  }

  print '</tbody>';

  // Generating total of commitment forecast.
  $detail_row_total_extra = array_values($detail_row_total);
  $detail_row_total_1 = array('none', 'none1');

  $detail_row_total_1 = array_merge($detail_row_total_1, $detail_row_total_extra);
  print '<tfoot>
          <tr><th>&nbsp;</th>';

  for ($i = 1; $i <= count($detail_row) - 1; $i++) {
    if ($i == 1) {
      print '<th align="left">Total</th>';
    }
	elseif ($i == 0) {
		print '<th align="left">&nbsp;</th>';
	}
    else {
      print '<th align="right">$ ' . number_format($detail_row_total_1[$i]) . '</th>';
    }
  }

  print '</tr></tfoot>
        </table>';

  // Generating ETC Forecasts.
  print '<h5 style="padding:10px; background: #eee; width:100%; height:20px;">
          <div style="float:left; width:50%; text-align:left;">' . $pSTitle . '</div>
          <div style="float:right; width:50%; text-align:right;">ETC Forecast</div>
        </h5>';
  print '<table class="under-border" style="width:100%; margin:0;">
      <thead><tr>';

  $detail_header_etc = array(
    t('ETC Number'),
    t('Amount'),
    t('Total Spent'),
    t('Previous Years'),
    date('Y') . '<br/>' . t('Quarter 1'),
    date('Y') . '<br/>' . t('Quarter 2'),
    date('Y') . '<br/>' . t('Quarter 3'),
    date('Y') . '<br/>' . t('Quarter 4'),
    date('Y') . '<br/>' . t('Spending'),
    t('Future Years'),
    t('Variance'),
  );

  for ($i = 0; $i <= count($detail_header_etc) - 1; $i++) {
	  if ($i == 0) {
		  print '<th width="110px" align="left">' . $detail_header_etc[$i] . '</th>';
	  }
	  else {
		  print '<th width="110px" align="right">' . $detail_header_etc[$i] . '</th>';
	  }
  } // Finished making header for each project.

  print '</tr>
        <tr>
          <td style="margin:0; width:100%;" colspan="12"><div class="clearfix hr"></div></td>
        </tr>
      </thead>
      <tbody>'; // Starting tbody.

  $query = db_select('node','n');
  $query->join('field_data_field_project_reference','pr','n.nid=pr.entity_id');
  $query->join('field_data_field_etc_amount','ea','ea.entity_id = n.nid');  
  $query->join('field_data_field_etc_operation_done', 'eo', 'eo.entity_id = n.nid');
  $query->fields('n', array('nid'));
  $query->condition('pr.field_project_reference_nid', $key, '=');
  $query->condition('eo.field_etc_operation_done_value', 'In ETC', '=');
  $getEtcIds = $query->execute()->fetchCol();
  $detail_row_etc_total = array();
  foreach($getEtcIds as $etcKey => $etcVal) {
    print '<tr>';
    $getEtcData = node_load($etcVal);
    $etcNumber = $getEtcData->field_etc_number_calc['und'][0]['value'];
    $etcAmt = $getEtcData->field_etc_amount['und'][0]['value'] != '' ? $getEtcData->field_etc_amount['und'][0]['value'] : 0;
    $etcTtoal += $etcAmt;
    // Get quarter value for etc
    $defaultAmt = 0;
    $getFutureAmt = 0;
    $getVarienceAmt = 0;
    
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
    $detail_row_etc_total['etcAmt'] += $etcAmt;
    $detail_row_etc_total['total_spend'] += 0;
    $detail_row_etc_total['prev_year'] += 0;
    $detail_row_etc_total['getPrevQuarterOne'] += $getPrevQuarterOne;
    $detail_row_etc_total['getPrevQuarterTwo'] += $getPrevQuarterTwo;
    $detail_row_etc_total['getPrevQuarterThree'] += $getPrevQuarterThree;
    $detail_row_etc_total['getPrevQuarterFour'] += $getPrevQuarterFour;
    $detail_row_etc_total['getCurrentYearAmt'] += $getCurrentYearAmt;
    $detail_row_etc_total['getFutureAmt'] += $getFutureAmt;
    $detail_row_etc_total['getVarienceAmt'] += $getVarienceAmt;


    for ($i = 0; $i <= count($detail_row_etc) - 1; $i++) {
      if ($i == 0) {
        print '<td align="left">' . $detail_row_etc[$i] . '</td>';
      }
      else {
        print '<td align="right">$' . number_format($detail_row_etc[$i]) . '</td>';
      }
    }
    print '</tr>';
  }



  print '</tbody>';

  // Generating total of commitment forecast.
  $detail_row_etc_total_extra = array_values($detail_row_etc_total);
  $detail_row_etc_total_1 = array('none2');
  $detail_row_etc_total_1 = array_merge($detail_row_etc_total_1, $detail_row_etc_total_extra);
  print '<tfoot>
          <tr><th align="left">Total</th>';

  for ($i = 1; $i <= count($detail_row_etc) - 1; $i++) {
    print '<th align="right">$ ' . $detail_row_etc_total_1[$i] . '</th>';
  }

  print '</tr></tfoot>
        </table>';

 }

 print '</div>
        </div>';
}
?>
<style>
/*@page {
        margin-top: 150px; 
}*/
body {font-family: "pdf_font";}
body {
	margin: 0;
	padding: 0;
}
.page_header {
	padding: 15px;
	background: #E3EFFC;
	margin-bottom:15px;
}
.page_details {
	margin-top:126px;
	padding: 10px;
	background: #FFF;
}
table {
	border-collapse: collapse;
}
tr, td, th {
	padding: 3px;
	border-collapse: collapse;
}
.table_border, .table_border tr, .table_border td, .table_border th {
	border: 1px solid #000;
}
.thead_border th {
	border-bottom: 1px solid #000;
}
.under-border thead th{
	padding:5px 0;
	border-bottom:0.5px solid #CCC;
}
.under-border tfoot th{
	padding:5px 0;
	border-top: 0.5px solid #CCC;
}
.clearfix {
	display:table;
	width:100%;
	clear:both;
}
.clearfix:after, .clearfix:before {
	content: "";
	clear: both;
	width: 100%;
	display: table;
}

.hr {
	background:#CCC;
	height:1px;
	width:100%;
	margin:5px 0;
}

</style>
<?php 
function get_invoice_total_by_cost_code_pdf($costCode, $proId) {
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

function get_commitment_total_by_cost_code_pdf($costCode, $proId) {
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

function get_etc_total_by_cost_code_pdf($costCode, $proId) {
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

function get_total_allocated_by_cost_code_pdf($costCode, $proId,$getCommitmentAmt) {
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
  //return $getCommitmentAmt + $getPoBal;
  return (intval($getCommitmentAmt) + intval($getPoBal));
}

function get_description_by_cost_code($costCode = 0) {
  if($costCode != '') {	
    $getCcDes = db_select('node','n'); 
    $getCcDes->join('field_data_field_manager_cost_code','mcc','mcc.entity_id = n.nid'); 
    $getCcDes->join('field_data_field_cost_code_description','ccd','ccd.entity_id = n.nid'); 	  
    $getCcDes->fields('ccd',array('field_cost_code_description_value'));
    $getCcDes->condition('mcc.field_manager_cost_code_value',$costCode, '=');
    $costCodeDes = $getCcDes->execute()->fetchField();	    
	return $costCode.' | '.$costCodeDes;
  }
  else {
    return 'None';
  }
}

function _get_spending_details_by_asset_pdf($assetId,$projectId) {
  // Get spending data by asset id and showing all the thing on edit.
  global $company;
  $query = db_select('node','n');
  $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
  $query->join('field_data_field_project_reference','pr', 'pr.entity_id = n.nid');
  $query->fields('n', array('nid'));
  $query->condition('pr.field_project_reference_nid', $projectId, '=');
  $query->join('field_data_field_asset_description_spending','ad','n.nid=ad.entity_id');
  $query->condition('ad.field_asset_description_spending_value', '%' . db_like($assetId) . '%', 'LIKE');
  $query->condition('n.type','project_spending','=');
  $query->condition('om.gid', $company->nid, '=');
  $query->orderBy('n.nid', 'DESC');
  $getSpendingNodes = $query->execute()->fetchCol();
  $rows = array(); 
  $header = array( 
    array('data'=>'Commitment Number','class'=>array('text-left')),
    array('data'=>'Invoice Number','class'=>array('text-left','col-md-1')),
    array('data'=>'Vendor Name','class'=>array('text-left')),
    array('data'=>'Vendor #','class'=>array('text-left')),
    array('data'=>'Invoice Amount','class'=>array('text-left')),
    array('data'=>'Amount Allocated','class'=>array('text-left')),
    array('data'=>'Percentage %','class'=>array('text-center','no-sort')),
  );
  $getTotalAmount = 0;
  if($getSpendingNodes && !empty($getSpendingNodes)) {
    foreach($getSpendingNodes as $spendingId => $spendingVal){
      $spendingNode = node_load($spendingVal);  
      $invoiceNumber = isset($spendingNode->field_invoice_number_cal['und'])?$spendingNode->field_invoice_number_cal['und'][0]['value']:'None';
      $invoiceAmount = isset($spendingNode->field_invoice_amount['und'])?'$'.number_format($spendingNode->field_invoice_amount['und'][0]['value'],2):'$0.00';
      $commitmentNid = isset($spendingNode->field_invoice_commitment['und'])?$spendingNode->field_invoice_commitment['und'][0]['nid']:'';
      $venoderName = 'None';
      $vendorNumber = 'None';
      if(!empty($commitmentNid)) {
        $getCommitData = node_load($commitmentNid);
        $commitNumber = $getCommitData->field_commitment_number_calculat['und'][0]['value']!=''?$getCommitData->field_commitment_number_calculat['und'][0]['value']:'None';
        if($getCommitData->field_vendor['und'][0]['value'] != '' && is_numeric($getCommitData->field_vendor['und'][0]['value'])) {
          $venoderName = node_load($getCommitData->field_vendor['und'][0]['value'])->title;
        }
        else {
          $venoderName = $getCommitData->field_vendor['und'][0]['value'];
        }   
        $vendorNumber = ($spendingNode->field_vendor_number['und'][0]['value']!='')?$spendingNode->field_vendor_number['und'][0]['value']:'None';
      }
      $getTotalAmount = 0;
      if($spendingNode->field_has_asset['und'][0]['value'] == 'TRUE') {
        //Checking if amount remain in split section
        if($spendingNode->field_asset_type['und'][0]['value'] == 'Split') {
          foreach ($spendingNode->field_asset_category_split['und'] as $delta => $assetNid) { 
            $assetCost += $spendingNode->field_asset_cost['und'][$delta]['value'];  
            $assetInst += $spendingNode->field_asset_installation['und'][$delta]['value'];
            $assetConst += $spendingNode->field_asset_outside_consultant['und'][$delta]['value'];
            $assetInterCharge += $spendingNode->field_asset_internal_charge['und'][$delta]['value'];
      	  }
          $getTotalAmount = $assetCost +  $assetInst + $assetConst + $assetInterCharge;
          $finalTotalAmt += $getTotalAmount;
        }
        else if($spendingNode->field_asset_type['und'][0]['value'] == 'Spread'){      
          foreach($spendingNode->field_asset_description_spending['und'] as $nidsKey => $loadData) {
            $assetDesc_split = explode('-',$loadData['value']);
            if ($assetDesc_split[0] == $assetId) {
              $assetNodeNid = $assetDesc_split[0];
              $getTotalAmount = db_select('m6connect_spending_spread_calculations', 's')
              ->fields('s', array('amount'))
              ->condition('spending_nid', $spendingNode->nid)
              ->condition('asset_nid', $assetNodeNid)
              ->execute()
              ->fetchField();
              $finalTotalAmt += $getTotalAmount;
            }
          }     
        }   
      }
      $percentageRemain = $getTotalAmount/$spendingNode->field_invoice_amount['und'][0]['value']*100; 
      $finalPer = 100 - $percentageRemain;
      $rows[] = array(
        'data' => array(  
          array('data' => $commitNumber,'class' => array('text-left')),
          array('data' => substr($invoiceNumber,0,15).'...','class' => array('text-left','col-md-1')),
          array('data' => $venoderName,'class' => array('text-left')),
          array('data' => $vendorNumber,'class' => array('text-left')),
          array('data' => $invoiceAmount,'class' => array('text-right')),     
          array('data' => '$'.number_format($getTotalAmount,2),'class' => array('text-right')),     
          array('data' => number_format($percentageRemain,2).'%','class' => array('text-left')),      
        ),
      );      
    }
    $rows[] = array(
      'data' => array(  
        array('data' => '&nbsp;'),
        array('data' => '&nbsp;','class' => array('text-left','col-md-1')),
        array('data' => '&nbsp;'),
        array('data' => '&nbsp;'),
        array('data' => 'Total','class' => array('text-right')),      
        array('data' => '$'.number_format($finalTotalAmt,2),'class' => array('text-right')),      
        array('data' => '&nbsp;'),
      ),
	);  
  }
  return theme('table', array('header'=>$header,'rows'=>$rows,'empty'=>'No Record Found','attributes'=>array('class'=>array('table','m6connect-custom-table','m6connect-custom-program-manager-spending-based-asset-table','m6connect-program-spending-based-asset-table','table-hover','table-bordered','text-center'))));
}
?>
