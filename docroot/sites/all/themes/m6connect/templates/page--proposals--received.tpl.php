<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
 if(!user_is_logged_in()) {
  drupal_access_denied();
  drupal_exit();
}
?>
<?php
/* * ***Changed**** */
$CurrCompNid = $_SESSION['company'];
drupal_add_library('system', 'ui.dialog');
if (arg(0) == 'node') {
    $nid = arg(1);
}
global $user;
$logged_user = $user->uid;
$site_url = $GLOBALS['base_url'];
$path = current_path();
$node = node_load($nid);
$content_type = $node->type;
//echo $content_type;
// This function returns Longitude & Latitude from zip code.
function getLnt($zip) {
//$url = "http://maps.googleapis.com/maps/api/geocode/json?address=".urlencode($zip)."&sensor=false";
    $url = "https://maps.googleapis.com/maps/api/geocode/json?address=" . urlencode($zip) . "&key=AIzaSyC86LE_cOCq2I8F6b3OJ207wL19sERnzq8";
    $result_string = file_get_contents($url);
    $result = json_decode($result_string, true);
    $result1[] = $result['results'][0];
    $result2[] = $result1[0]['geometry'];
    $result3[] = $result2[0]['location'];
    return $result3[0];
}
function getDistance($zip1, $zip2) {
    $first_lat = getLnt($zip1);
    $next_lat = getLnt($zip2);
    $lat1 = $first_lat['lat'];
    $lon1 = $first_lat['lng'];
    $lat2 = $next_lat['lat'];
    $lon2 = $next_lat['lng'];
    $theta = $lon1 - $lon2;
    $dist = sin(deg2rad($lat1)) * sin(deg2rad($lat2)) +
            cos(deg2rad($lat1)) * cos(deg2rad($lat2)) *
            cos(deg2rad($theta));
    $dist = acos($dist);
    $dist = rad2deg($dist);
    $miles = $dist * 60 * 1.1515;
    return $miles;
}
?>

<style>
.cust-proposal-view-heading a.sort-link,
.cust-proposal-view-heading a.sort-link:hover{
     text-decoration: none;
     color: #000; 
}
</style>

<div id="page">
  <header class="header" id="header" role="banner">
    <div class="container-fluid"> <?php print render($page['header']); ?>
      <div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?> </div>
    </div>
  </header>
  <div id="navigation">
    <div class="container"><?php print render($page['navigation']); ?></div>
  </div>
  <?php $wrapperClass =''; if(isset($_SESSION['left_block_action']) && $_SESSION['left_block_action']=='open'){ $wrapperClass='active'; } ?>
  <div id="wrapper" class="<?php print $wrapperClass; ?> clearfix">
    <div id="sidebar-wrapper">
      <?php if ($page['left_content']): ?>
      <?php print render($page['left_content']); ?>
      <?php endif; ?>
    </div>
    <div id="page-content-wrapper">
      <div class="page-content inset">
        <div id="main">
          <div class="container-fluid">
            <div class="top_header clearfix">
              <?php if ($page['top_header']): ?>
              <?php print render($page['top_header']); ?>
              <?php endif; ?>
            </div>
            <div id="content" class="column" role="main">
              <div class="box">
                <div class="inner-box">
                  <div class="middle-page">
                    <div class="white-bg">
                      <div class="right_content clearfix">
                        <div class="content_inner_pages"> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?>
                          <?php if ($action_links): ?>
                          <ul class="action-links">
                            <?php print render($action_links); ?>
                          </ul>
                          <?php endif; ?>
                          <!-- content start -->
                          
                          <?php
              						$sortingProposalAmount = 0;
              						$headerSortDefault = array(
              						  'company'=> array('sort'=>'desc','class'=>''),
              						  'name'=> array('sort'=>'desc','class'=>''),
              						  'amount'=> array('sort'=>'desc','class'=>''),
              						  'date'=> array('sort'=>'desc','class'=>''),
              						);
                        $title_search = $defult_search = '';$query_parameters = array();
                        $query_parameters = drupal_get_query_parameters();
            						$defult_seletion = 'date_desc';            						
                        $sort_select = $query_parameters['sel_name'];
                        if (empty($query_parameters['search_proposal']) && (empty($query_parameters['sel_name']))) {
                            $title_search = "order by a.created desc";
                        } else if (!empty($query_parameters['search_proposal']) && (!empty($query_parameters['sel_name']))) 
                        {
            							$defult_seletion = $query_parameters['sel_name'];
            							$defult_search = $query_parameters['search_proposal'];
						              if ($query_parameters['sel_name'] == "name_asc") {
                              $key_sort = "order by a.title asc";
                          } else if ($query_parameters['sel_name'] == "name_desc") {
                              $key_sort = "order by a.title desc";
                          } else if ($query_parameters['sel_name'] == "date_asc") {
                              $key_sort = "order by a.created asc";
                          } else if ($query_parameters['sel_name'] == "date_desc") {
                              $key_sort = "order by a.created desc";
                          } else if ($query_parameters['sel_name'] == "amount_desc") {
            								$key_sort = "order by bid_amount DESC";
            								$sortingProposalAmount = 0;
                          } else if ($query_parameters['sel_name'] == "amount_asc") {
            								$key_sort = "order by bid_amount ASC";
            								$sortingProposalAmount = 99999999999;
                          } else if ($query_parameters['sel_name'] == "company_desc") {
            								$key_sort = "order by proposal_company_title DESC";
                          } else if ($query_parameters['sel_name'] == "company_asc") {
            								$key_sort = "order by proposal_company_title ASC";
                          }
                          $tit_value = $query_parameters['search_proposal'];
                          $title_search = "and a.title LIKE '%$tit_value%' $key_sort";
                        } else if (($query_parameters['search_proposal'] == "") || ($query_parameters['sel_name'] != "")) {
              							$defult_seletion = $query_parameters['sel_name'];
              							$defult_search = $query_parameters['search_proposal'];
                            if ($query_parameters['sel_name'] == "name_asc") {
                                $key_sort = "order by a.title asc";
                            } else if ($query_parameters['sel_name'] == "name_desc") {
                                $key_sort = "order by a.title desc";
                            } else if ($query_parameters['sel_name'] == "date_asc") {
                                $key_sort = "order by a.created asc";
                            } else if ($query_parameters['sel_name'] == "date_desc") {
                                $key_sort = "order by a.created desc";
                            } else if ($query_parameters['sel_name'] == "amount_desc") {
              								$key_sort = "order by bid_amount DESC";
              								$sortingProposalAmount = 0;
                            } else if ($query_parameters['sel_name'] == "amount_asc") {
              								$sortingProposalAmount = 99999999999;
              								$key_sort = "order by bid_amount ASC";
                            } else if ($query_parameters['sel_name'] == "company_desc") {
              								$key_sort = "order by proposal_company_title DESC";
                            } else if ($query_parameters['sel_name'] == "company_asc") {
              								$key_sort = "order by proposal_company_title ASC";
                            }							
                            $title_search = " $key_sort";						
                          }
              						if(!empty($defult_seletion)){
              						  $hederSortkey = explode('_',$defult_seletion);
              						  if(isset($headerSortDefault[$hederSortkey[0]])){
                							if($hederSortkey[1] == 'desc'){
                							  $headerSortDefault[$hederSortkey[0]]['sort'] = 'asc';
                							  $headerSortDefault[$hederSortkey[0]]['class'] = ' fa-caret-down';	
                							}else{
                							  $headerSortDefault[$hederSortkey[0]]['sort'] = 'desc';
                							  $headerSortDefault[$hederSortkey[0]]['class'] = ' fa-caret-up';	
                							}
              						  }	
              						}
						
                        ?>
                        <div class="clearfix margin-bottom-10">
                                      <form name="listSearcFrm" id="seach_award" method="GET" >
                                        <div class="custom-projects-lists-search pull-left">
                                          <input placeholder="Search Proposals" name="search_proposal" id="s" value="<?php print $defult_search; ?>" type="text" class="form-text form-control">
                                   <input type="submit" style="border:0px;" class="search_m6_prop1 form-submit" name="search" id="search" value="Search"  />
                                        </div>
                                        <div class="custom-projects-lists-sorting pull-right">
                                          <select style="display:none;" class="form-select" name="sel_name" id="order_proposal" onchange="if (this.value) window.location.href='?sel_name='+this.value">
                                            <option value="name_asc"<?php if("name_asc"==$defult_seletion){ print " selected='selected'"; }?>> Proposal Name (A-Z)</option>
                                            <option value="name_desc"<?php if("name_desc"==$defult_seletion){ print " selected='selected'"; }?>> Proposal Name (Z-A)</option>
                                            <option value="date_desc"<?php if("date_desc"==$defult_seletion){ print " selected='selected'"; }?>> Created Date (Newest - Oldest)</option>
                                            <option value="date_asc"<?php if("date_asc"==$defult_seletion){ print " selected='selected'"; }?>> Created Date (Oldest - Newest)</option>
                                            <option value="amount_asc"<?php if("amount_asc"==$defult_seletion){ print " selected='selected'"; }?>> Bid Amount (Lowest to Highest)</option>
                                            <option value="amount_desc"<?php if("amount_desc"==$defult_seletion){ print " selected='selected'"; }?>> Bid Amount (Highest to Lowest)</option>
                                            <option value="company_asc"<?php if("company_asc"==$defult_seletion){ print " selected='selected'"; }?>> Company (A-Z)</option>
                                            <option value="company_desc"<?php if("company_desc"==$defult_seletion){ print " selected='selected'"; }?>> Company (Z-A)</option>
                                          </select>
                                       </div>
                                      </form>
                                    <script>
                                      function changeTest(obj) {
                                             document.getElementById("seach_award").submit();
                                      }
                                    </script> 
                       </div>
                          <div class="m6_view_proposal">
                            <div class="m6_main_view clearfix">
                              <div id="proposal-access-dialog"></div>
                              <div class="right_m6_view list_inbox_pro">
                                <div class="cust-proposal-view-heading margin-bottom-10 clearfix">
                                  <div class="clearfix">
                                    <div class="proposal-cust-view-header proposal-header-company pull-left m6_prop1_img text-center"><a href="javascript:void(0);" class="proposal-header-sorting sort-link" data-sort-name="company" data-sort-type="<?php print $headerSortDefault['company']['sort']; ?>"><strong>Company&nbsp;<i class="fa caret-section<?php print $headerSortDefault['company']['class']; ?>" aria-hidden="true"></i></strong></a></div>
                                    <div class="proposal-cust-view-header proposal-header-response pull-left m6_prop1_cont text-center"><a href="javascript:void(0);" class="proposal-header-sorting sort-link" data-sort-name="name" data-sort-type="<?php print $headerSortDefault['name']['sort']; ?>"><strong>In Response To&nbsp;<i class="fa caret-section<?php print $headerSortDefault['name']['class']; ?>" aria-hidden="true"></i></strong></a></div>
                                    <div class="proposal-cust-view-header proposal-header-amount pull-left m6_prop1_amount text-center"><a href="javascript:void(0);" class="proposal-header-sorting sort-link" data-sort-name="amount" data-sort-type="<?php print $headerSortDefault['amount']['sort']; ?>"><strong><strong>Amount&nbsp;<i class="fa caret-section<?php print $headerSortDefault['amount']['class']; ?>" aria-hidden="true"></i></strong></a></div>
                                    <div class="proposal-cust-view-header proposal-header-sdate pull-left m6_prop1_created text-center"><a href="javascript:void(0);" class="proposal-header-sorting sort-link" data-sort-name="date" data-sort-type="<?php print $headerSortDefault['date']['sort']; ?>"><strong><strong>Submited Date&nbsp;<i class="fa caret-section<?php print $headerSortDefault['date']['class']; ?>" aria-hidden="true"></i></strong></a></div>
                                    <div class="proposal-cust-view-header proposal-header-action pull-left m6_actions text-center"><a href="javascript:void(0);" class="sort-link" style="pointer-events:none;"><strong>Action</strong></a></div>
                                  </div>
                                </div>
                                <div class="m6_own_con clearfix">
                                  <div class="m6_own" id="m6_prop1">
                                    
                                    <ul id="content_msg">
                                      <?php //mla.timestamp >:AssessTimestamp
/*$sql_node3 = db_query('SELECT a.title,a.nid,a.uid,a.status,a.created,b.entity_id,b.field_proposal_number_value,
c.entity_id,c.field_submit_proposal_in_respons_target_id,
d.entity_id,d.field_field_sub_proposal_pjt_target_id,
e.entity_id,e.field_submit_proposal_member_target_id,
f.entity_id,f.field_submit_proposal_to_company_target_id,
g.entity_id,g.field_proposal_bid_amount_value,
h.entity_id,h.field_proposoal_bid_types_value,
i.entity_id,i.field_proposal_job_location_administrative_area,i.field_proposal_job_location_locality,
j.node_id,j.status,j.award_taker_id,j.award_giver_id,
k.reject_node,k.status,k.reject_taker_id,k.reject_giver_id,
CONVERT(REPLACE(g.field_proposal_bid_amount_value,:ReplaceFrom,:ReplaceTo), DECIMAL(10,2)) bid_amount2,


IF((IFNULL(rcb.field_create_confidential_bid_value,pcb.field_create_confidential_bid_value)) IS NOT NULL,
IF(mla.timestamp IS NULL,:ProposalAmount,CONVERT(REPLACE(g.field_proposal_bid_amount_value,:ReplaceFrom,:ReplaceTo), DECIMAL(10,2)))
,CONVERT(REPLACE(g.field_proposal_bid_amount_value,:ReplaceFrom,:ReplaceTo), DECIMAL(10,2))) bid_amount, 


IF(mla.timestamp IS NULL,0,1) allow_bid_amount_access,
mpcnode.title proposal_company_title
FROM node AS a

LEFT JOIN m6connect_confidential_bids_keys_access_log AS mla on mla.proposal_nid=a.nid AND mla.access_purpose=:AccessPurpose AND mla.timestamp >:AssessTimestamp
LEFT JOIN field_revision_field_proposal_number AS b ON a.nid=b.entity_id 

LEFT JOIN field_data_field_is_proposal_archived AS pa ON a.nid=pa.entity_id 

LEFT JOIN og_membership AS mpog ON mpog.etid=a.nid AND mpog.entity_type=:MPEntityType
LEFT JOIN node AS mpcnode ON mpcnode.nid=mpog.gid

LEFT JOIN field_data_field_submit_proposal_in_respons AS c ON a.nid=c.entity_id 
LEFT JOIN field_data_field_create_confidential_bid AS rcb ON rcb.entity_id=field_submit_proposal_in_respons_target_id


LEFT JOIN field_data_field_field_sub_proposal_pjt AS d ON a.nid=d.entity_id
LEFT JOIN field_data_field_create_confidential_bid AS pcb ON pcb.entity_id=field_field_sub_proposal_pjt_target_id


 
LEFT JOIN field_data_field_submit_proposal_to_company AS f ON a.nid=f.entity_id
LEFT JOIN field_revision_field_submit_proposal_member AS e ON a.nid=e.entity_id
LEFT JOIN field_data_field_proposal_bid_amount AS g ON a.nid=g.entity_id
LEFT JOIN field_data_field_proposoal_bid_types AS h ON a.nid=h.entity_id  
LEFT JOIN field_data_field_proposal_job_location AS i ON a.nid=i.entity_id  
LEFT JOIN proposal_award AS j ON a.nid=j.node_id  
LEFT JOIN proposal_reject AS k ON a.nid=k.reject_node  
WHERE pa.field_is_proposal_archived_value IS NULL and a.status=1 and a.type=:type '.$title_search, array(':type'=>'my_proposal',':ReplaceFrom'=>',',':ReplaceTo'=>'',':MPEntityType'=>'node',':AccessPurpose'=>'amount_access',':AssessTimestamp'=> strtotime('-20 minutes'),':ProposalAmount'=>$sortingProposalAmount));
$sql_node4 = $sql_node3->fetchAll();*/
if (empty(arg(2))) {
  $sql_node4 = _get_eproposal_table_record($title_search,'');
}
else {  
  $sql_node4 = _get_eproposal_table_record($title_search,arg(1));
}
//$sql_node4 = $sql_node3->fetchAll();

//pre($sql_node4,1);
$sql_node = array();
if($sql_node4 && !empty($sql_node4)){
  $sql_node	= json_decode(json_encode($sql_node4), true);
}

for ($f = 0; $f < count($sql_node); $f++) {
    $id = $sql_node[$f]['field_proposal_number_value'];
    $node_pro_id = $sql_node[$f]['nid'];
    $node_owner = $sql_node[$f]['uid'];
    $node_award_id = $sql_node[$f]['node_id'];
    $node_award_taker_id = $sql_node[$f]['award_taker_id'];
    $node_award_giver_id = $sql_node[$f]['award_giver_id'];
	$node_reject_id = $sql_node[$f]['reject_node'];
    $node_reject_taker_id = $sql_node[$f]['reject_taker_id'];
    $node_reject_giver_id = $sql_node[$f]['reject_giver_id'];
	$allow_bid_amount_access = $sql_node[$f]['allow_bid_amount_access'];
	$title = $sql_node[$f]['title'];
    $bit_amount = $sql_node[$f]['field_proposal_bid_amount_value'];
    $bit_type = $sql_node[$f]['field_proposoal_bid_types_value'];
    $city = $sql_node[$f]['field_proposal_job_location_locality'];
    $state = $sql_node[$f]['field_proposal_job_location_administrative_area'];
    $target_id = $sql_node[$f]['field_submit_proposal_in_respons_target_id'];
    $target_id1 = $sql_node[$f]['field_field_sub_proposal_pjt_target_id'];
    $target_id2 = $sql_node[$f]['field_submit_proposal_member_target_id'];
    $target_id3 = $sql_node[$f]['field_submit_proposal_to_company_target_id'];
    $zip_code = $sql_node[$f]['field_proposal_job_location_postal_code'];
    $rr = 0;
	$target_member = '';
    if ($target_id != "") {
        $target_member = $target_id;
    } else if ($target_id1 != "") {
        $target_member = $target_id1;
    } else if ($target_id2 != "") {
        $target_member = $target_id2;
        $rr = 1;
    } else if ($target_id3 != "") {
        $target_member = $target_id3;
    }
	if(!is_numeric($target_member)){
	  continue; 
    }

    /*     * ************ Start Mayank Work ************* */
    $isUpgradeRequired = 1;
    $propoalCmpNode = '';
    $usercmpNid = _get_user_company_nid($node_owner);
    $node_owner_obj = user_load($node_owner);
	
	 /*     * ************ Start brijendra Work ************* */
	//$prop_postfirstname = $node_owner_obj->field_first_name['und'][0]['value'];
  	//$prop_postlastname = $node_owner_obj->field_last_name['und'][0]['value'];
	
	 /*     * ************ end brijendra Work ************* */	 
    if ($usercmpNid && is_numeric($usercmpNid)) {
        $propoalCmpNode = $cmpNode = node_load($usercmpNid);
        $cmp_owner_obj = '';
        if ($cmpNode->uid != $node_owner) {
            $cmp_owner_obj = user_load($cmpNode->uid);
        } else {
            $cmp_owner_obj = $node_owner_obj;
        }
        if (!empty(array_intersect(array_keys($cmp_owner_obj->roles), array(7, 8, 9, 14)))) {
            $isUpgradeRequired = 0;
        }
    }
    /* if($isUpgradeRequired){
      if(!empty(array_intersect(array_keys($node_owner_obj->roles),array(7,8,9,14)))){
      $isUpgradeRequired=0;
      }
      } */
    $requestCmpTitle = '';
    $requestNode = node_load($target_member);
    $requestCmpNid = _get_user_company_nid($requestNode->uid);
    if ($requestCmpNid && is_numeric($requestCmpNid)) {
        $requestCmpNode = node_load($requestCmpNid);
        $requestCmpTitle = $requestCmpNode->title;
    }
    /*     * ************ End Mayank Work ************* */
    if ($isUpgradeRequired && is_numeric($target_member)) {
        $requestNode = node_load($target_member);
        //drupal_set_message($target_member);
        $entityNids = array();
        $cmpNid = _get_user_company_nid($node->uid);
		
        $queryFree = db_select('node', 'n');
        $queryFree->leftJoin('field_data_field_available_for_free', 'aff', 'aff.entity_id = n.nid');
        $queryFree->leftJoin('field_data_field_available_for_free_proj', 'paff', 'paff.entity_id = n.nid');
        $queryFree->fields('n', array('nid', 'type'));
        $queryFree->fields('paff', array('field_available_for_free_proj_value'));
        $queryFree->fields('aff', array('field_available_for_free_value'));
        if ($requestNode->type == 'organization') {
          $entityNids[] = $requestNode->nid;
        } 
		else if ($requestNode->type == 'project') {
          $entityNids[] = $requestNode->nid;
          if ($cmpNid && is_numeric($cmpNid)) {
            $entityNids[] = $cmpNid;
          }
        } 
		else {
          $projectNid = (isset($requestNode->field_project['und']) && !empty($requestNode->field_project['und'][0]['target_id'])) ? $requestNode->field_project['und'][0]['target_id'] : '';
          if ($cmpNid && is_numeric($cmpNid)) {
            $entityNids[] = $cmpNid;
          }
		  if ($projectNid && is_numeric($projectNid)) {
            $entityNids[] = $projectNid;
          }
		}
        if (!empty($entityNids)) {
          $queryFree->condition('n.nid', array_values($entityNids), 'IN');
          $queryFree->orderBy('n.type', 'ASC');
          $resultFree = $queryFree->execute()->fetchAll();
          if ($resultFree && !empty($resultFree)) {
            $freeFlag = 0;
            foreach ($resultFree as $delta => $objResult) {
              if ($objResult->type == 'organization') {
                $freeFlag = ($objResult->field_available_for_free_value) ? $objResult->field_available_for_free_value : $freeFlag;
              } 
			  else {
			    $freeFlag = ($objResult->field_available_for_free_proj_value == 1) ? $objResult->field_available_for_free_proj_value : $freeFlag;
              }
            }
          }
        }
        if ($freeFlag != 1) {
            $isUpgradeRequired = 0;
        }
    }
    /*     * ************ End Mayank Work ************* */

    $com_date = date('m/d/Y g:i A', $sql_node[$f]['created']);
    if ($rr == "1") {
        $userquery = db_select('users','u');
	    $userquery->join('realname','r','r.uid=u.uid');
	    $userquery->fields('u');
	    $userquery->fields('r',array('realname'));
	    $userquery->condition('u.uid',$target_member,'=');
	    $userdetails = $userquery->execute()->fetchAssoc();
	    $valu_fold = array($userdetails);
	    $sub_proposal_for = $valu_fold[0]['realname'];
    } else {
        $nodedetails = db_select('node','n')->fields('n')->condition('n.nid',$target_member)->execute()->fetchAssoc();
	    $valu_fold = array($nodedetails);
        $sub_proposal_for = $valu_fold[0]['title'];
    }

    $userid1 = $valu_fold[0]['uid'];
		$targetNodetype = $valu_fold[0]['type'];
		if($targetNodetype=='organization'){
			$targetNodetype = 'company';																												 
		}
		if($targetNodetype=='rfp'){
			$targetNodetype = 'RFP';																												 
		}

    //if((($userid1 == $logged_user) && ($node_reject_id != $node_pro_id)) || (($userid1 == $logged_user) && ($node_award_id != $node_pro_id))){
    /*     * ***Changed**** */
    $propNode = node_load($node_pro_id);
    $targetNodeNid = $valu_fold[0]['nid'];
    $targetNode = node_load($targetNodeNid);
	$isCredentialRequired = 0;
	if(in_array($targetNode->type,array('rfp','project'))){
	  if(isset($targetNode->field_create_confidential_bid['und']) && $targetNode->field_create_confidential_bid['und'][0]['value']){
		$isCredentialRequired=1;  
	  }
	}
	
		
	
		$submit_pro_to_rfp = $propNode->field_submit_proposal_in_respons['und'][0]['target_id'];
		$submit_pro_to_pjt = $propNode->field_field_sub_proposal_pjt['und'][0]['target_id'];
		$submit_pro_to_com = $propNode->field_submit_proposal_to_company['und'][0]['target_id'];
		
		$proposalSubmitterforNotEmpty = (is_numeric($submit_pro_to_rfp) || is_numeric($submit_pro_to_pjt) || is_numeric($submit_pro_to_com));
		
		$colaborateUsers = '';
		if(isset($submit_pro_to_pjt) && $propNode->field_field_sub_proposal_pjt['und']){	 
		  $accproject = node_load($submit_pro_to_pjt);
		  $colaborateUsers =  m6connect_projects_uids_from_list($accproject);					
		}
		
		$company_admin_rols_access ='';
				if(isset($CurrCompNid)){
					if(isset($submit_pro_to_rfp) && $propNode->field_submit_proposal_in_respons['und']){
						$node_by_com = _get_company_nid_by_group_content($submit_pro_to_rfp);					
					}else if(isset($submit_pro_to_pjt) && $propNode->field_field_sub_proposal_pjt['und']){
						$node_by_com = _get_company_nid_by_group_content($submit_pro_to_pjt);					
					} else if(isset($submit_pro_to_com) && $propNode->field_submit_proposal_to_company['und']){
						$node_by_com = $submit_pro_to_com;					
					}
										
					$company_admin_rols = _get_company_users_by_og_roles($CurrCompNid,'company admin');
						if(($CurrCompNid == $node_by_com) && in_array($user->uid , $company_admin_rols)){			
							$company_admin_rols_access = 1;
						}
				}
				
	if((($node_reject_id!=$node_pro_id) && ($node_award_id != $node_pro_id) && (in_array($CurrCompNid,_get_company_nids_by_proposal_target_node($targetNode))) && $proposalSubmitterforNotEmpty) && ((($userid1 == $logged_user) || (is_proposal_project_collabarated($propNode)) || $company_admin_rols_access)) || in_array($user->uid,$colaborateUsers)){
		
	
				
    /*if ((($userid1 == $logged_user) && ($node_reject_id != $node_pro_id) && ($CurrCompNid == _get_company_nid_by_group_content($targetNode))) || (($userid1 == $logged_user) && ($node_award_id != $node_pro_id) && ($CurrCompNid == _get_company_nid_by_group_content($targetNode))) || ($company_admin_rols_access == TRUE)) {*/
			
        ?>
                                      <?php
                                                        //zip code user location starts

                                                        /*$query_zip = db_select('node', 'zip')
                                                                ->fields('zip', array('vid'));
                                                        $db_or_zip_vid = db_or();
                                                        $db_or_zip_vid->condition(db_and()->condition('zip.type', 'organization', '=')->condition('zip.uid', $node_owner, '='));
                                                        $src_cont_zip_vid = $query_zip->condition($db_or_zip_vid);
                                                        $result_cont_zip_vid = $src_cont_zip_vid->execute()->fetchAll();
                                                        $zip_node = $result_cont_zip_vid[0]->vid;

                                                        $zipCmpNid = 0;
                                                        if ($target_member && is_numeric($target_member)) {
                                                            $targetNode = node_load($target_member);
                                                            $zipCmpNid = _get_user_company_nid($targetNode->uid);
                                                            $zipCmpNid = ($zipCmpNid) ? $zipCmpNid : 0;
                                                        }

                                                        $query_zip_code = db_select('field_data_field_org_address', 'zipfl')
                                                                ->condition('zipfl.entity_id', $zipCmpNid, '=')
                                                                ->fields('zipfl', array('field_org_address_postal_code'));
                                                        $result_zip_final = $query_zip_code->execute()->fetchAll();
                                                        $zip_code_user = $result_zip_final[0]->field_org_address_postal_code;
*/
                                                        //zip code user location ends
                                                        //read msg starts
                                                        $query_status1 = db_select('read_unread_message', 'tes')
                                                                ->fields('tes', array('proposal_id', 'comment_id', 'user_id', 'staus'));
                                                        $db_or_cont_vid = db_or();
                                                        $db_or_cont_vid->condition(db_and()->condition('tes.proposal_id', $id, '=')->condition('tes.user_id', $logged_user, '='));
                                                        //echo '<pre>'; print_r($db_or_cont_vid); echo '</pre>';
                                                        $src_cont_company_vid = $query_status1->condition($db_or_cont_vid);

                                                        $result_status1 = $src_cont_company_vid->execute()->fetchAll();
                                                        //echo '<pre>'; print_r($result_status1); echo '</pre>';
                                                        $read_cmd_id = '';
                                                        foreach ($result_status1 as $item_read) {
                                                            $read_cmd_id .= $item_read->comment_id . '@';
                                                        }
                                                        $read_cmd_id_fin = explode('@', $read_cmd_id);
                                                        // echo '<pre>'; print_r($read_cmd_id_fin); echo '</pre>';
                                                        //read msg ends

                                                        $query_comment = db_select('comment', 'com')
                                                                ->condition('com.nid', $node_pro_id, '=')
                                                                ->fields('com', array('cid', 'uid', 'subject', 'created'));
                                                        $query_comment->orderBy('cid', 'DESC');
                                                        $result_comment = $query_comment->execute();
                                                        $result_comment_count = $query_comment->execute()->fetchAll();
                                                        $sub1 = count($result_comment_count);
                                                        $j = 0;
                                                        foreach ($result_comment_count as $item_read_st) {
                                                            $read_cmd_id_st[$j] = $item_read_st->cid;
                                                            $j++;
                                                        }
                                                        //echo '<pre>'; print_r($read_cmd_id_st); echo '</pre>';	
                                                        $cmb_in = array_intersect($read_cmd_id_st, $read_cmd_id_fin);
                                                        $sub2 = count($cmb_in);
                                                        $unread_msg = $sub1 - $sub2;
                                                        //echo $node_owner;
                                                        //echo $zip_code;
                                                        //logo image starts

                                                        /* $query_logo = db_select('node','logo')
                                                          ->fields('logo',array('nid'));
                                                          $db_or_logo_vid = db_or();
                                                          $db_or_logo_vid->condition(db_and()->condition('logo.type','organization', '=')->condition('logo.uid', $userid1, '='));
                                                          $src_cont_logo_vid =  $query_logo->condition($db_or_logo_vid);
                                                          $result_cont_logo_vid = $src_cont_logo_vid->execute()->fetchAll();
                                                          $logo_node = $result_cont_logo_vid[0]->nid;

                                                          $query_logo_code = db_select('field_data_field_logo','logof1')
                                                          ->condition('logof1.entity_id', $logo_node, '=')
                                                          ->fields('logof1',array('field_logo_fid'));
                                                          $result_logo_final = $query_logo_code->execute()->fetchAll();
                                                          $logo_code_user = $result_logo_final[0]->field_logo_fid;

                                                          $query_logo_image = db_select('file_managed','logoimg')
                                                          ->condition('logoimg.fid', $logo_code_user, '=')
                                                          ->fields('logoimg',array('uri'));
                                                          $result_logo_image = $query_logo_image->execute()->fetchAll();
                                                          $logo_code_uri = $result_logo_image[0]->uri;
                                                          $value=explode("://",$logo_code_uri,2);
                                                          $fimgvalue = image_style_url('thumbnail',$logo_code_uri);
                                                          //print_r($value);
                                                          $logo_path = $value[0];
                                                          $logo_code_img = $value[1];
                                                          //echo $userid1.'---'; echo $logo_node.'---'; echo  $logo_code_user.'----'; echo $logo_code_img.'---';
                                                          //logo image ends */
                                                        ?>
                                      <?php
                                                        //$fimgvalue = '<i class="fa fa-fw fa-building"></i>';
                                                        $submittedByCmpName = $propoalCmpNode->title;
                                                       /* if ($propoalCmpNode && isset($propoalCmpNode->field_logo) && isset($propoalCmpNode->field_logo['und']) && $propoalCmpNode->field_logo['und'][0]['fid']) {
                                                            $fimgvalue = image_style_url('thumbnail', $propoalCmpNode->field_logo['und'][0]['uri']);
                                                            $fimgvalue = '<img src="' . $fimgvalue . '">';
                                                        }*/
                                                        //$cmpNode='';
                                                        //$usercmpNid
																												
																												$SubmitedBycompanyNid =  _get_company_nid_by_group_content($node_pro_id);
																												$SubmitedBycompanyNid_load = node_load($SubmitedBycompanyNid);
																													if (isset($SubmitedBycompanyNid_load->field_logo['und'])) {
																														$fimgvalue = '<img src="' . image_style_url('right_bottom_block_128_128', $SubmitedBycompanyNid_load->field_logo['und'][0]['uri']) . '" style="height:100px; width:100px">';
																													} else {
																														$fimgvalue = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" style="height:100px; width:100px">';
																													}
																												
																												
																												
                                                        $notificationClass = '';
                                                        if (isset($_SESSION['notification_user'])) {
                                                            $notification = $_SESSION['notification_user'];
                                                            if (isset($notification['notification_proposal']['count']) && $notification['notification_proposal']['count'] > 0 && isset($notification['notification_proposal']['receive']) && isset($notification['notification_proposal']['receive']['entity_id']) && !empty($notification['notification_proposal']['receive']['entity_id'])) {
                                                                if (in_array($node_pro_id, $notification['notification_proposal']['receive']['entity_id'])) {
                                                                    $notificationClass = ' notification-highlight';
                                                                }
                                                            }
                                                        }
                                                        ?>
                                      <?php
                                                        $isUpgradeRequiredClass = ($isUpgradeRequired) ? ' membership_required' : '';
                                                        ?>
                                      <li class="proposal-m6-container prop_m6con1 prop_m6con1_<?php print $node_pro_id; ?><?php print $notificationClass; ?><?php print $isUpgradeRequiredClass; ?>" data-entity="<?php print $node_pro_id; ?>">
                                        <div class="m6_prop1_img text-center"> <span class="default_cmp<?php /*?>project-box-clbrte<?php */?>"> 
                                        <?php if($isCredentialRequired){ ?>
                                          <a href="javascript:void(0);" class="proposal-node-access">
                                        <?php }else{ ?>
                                          <a href="/<?php echo drupal_get_path_alias('node/' . $node_pro_id); ?>">
                                        <?php } ?>
                                          <?php 
										      print $fimgvalue;
											  echo '<div>';
														  $submitedBycompanyname =  _get_title_of_node($SubmitedBycompanyNid);
														  if(isset($submitedBycompanyname)){
														  echo $submitedBycompanyname;
														  }else{
														  echo ' '.$submittedByCmpName;
														  }
											  echo '</div>';
										  ?>
                                          </a> 
                                          
                                          </span> <span class="award-img">
                                          <?php
                                                        $awarded = check_proposal_is_awarded($node_pro_id);
                                                        if ($awarded) {
                                                            $award_status = check_proposal_is_awarded($node_pro_id, 'status');
                                                            if ($award_status == 1) {
                                                                echo '<img src="' . $base_url . '/sites/all/themes/m6connect/images/award.jpg">';
                                                            } else {
                                                                echo '<img src="' . $base_url . '/sites/all/themes/m6connect/images/PreliminaryAward.png">';
                                                            }
                                                        }
                                                        ?>
                                          </span></div>
                                        <!--<div class="m6_prop1_number"><span class="proposal-number">PN:<?php echo $id; ?> </span></div>-->
                                        <div class="m6_prop1_cont"> <span class="data-cmpName" style="display:none;"><?php print $requestCmpTitle; ?></span>
                                          <div class="m6_prop1_cont_title"> 
                                            <?php if($isCredentialRequired){ ?>
                                              <a href="javascript:void(0);" class="proposal-node-access">
                                                <span><?php echo $title; ?></span>                                               
                                              </a>
                                              <span class="proposal-number2">&nbsp;PN:<?php echo $id; ?> </span>
                                            <?php }else{ ?>
                                              <a href="/<?php echo drupal_get_path_alias('node/' . $node_pro_id); ?>"> 
                                                <span><?php echo $title; ?></span>                                               
                                              </a>
                                              <span class="proposal-number2">&nbsp;PN:<?php echo $id; ?> </span>
                                            <?php } ?>
                                            <!--<span class="proposal-number">&nbsp;&nbsp;PN:<?php //echo $id; ?> </span> -->
                                          </div>
                                          <div class="search_class_submitted">
                                            <div>
                                              <label>Submitted By: </label>
                                              <?php //echo ' '.$prop_postfirstname;
			
		
		$result = _get_node_company_user_name($node_pro_id);
		$output = (!empty($result['company_title']))? '<span class="submitted-company">'.$result['company_title'].'</span>, '.$result['user_name']:'<span class="submitted-company">'.$result['user_name'].'</span>';
 
 			echo $output;	
																														         /*$submitedBycompanyname =  _get_title_of_node($SubmitedBycompanyNid);
																																			                   
	    if(isset($submitedBycompanyname)){
							
		echo $submitedBycompanyname . ' , ' . $prop_postfirstname.' '.$prop_postlastname;
		}else{ 
		echo ' '.$submittedByCmpName . ' , ' . $prop_postfirstname.' '.$prop_postlastname;
		}*/
																					
	    ?>
                                            </div>
                                            <div>
                                              <label>Submitted For <?php print ucfirst($targetNodetype); ?>: </label>
                                              <?php echo ' '.$sub_proposal_for; ?></div>
                                          </div>
                                          <ul>
                                            <li><img src="/sites/default/files/images/gray_m6.png"><?php echo $city; ?>, <?php echo $state; ?></li>
                                            <li><img src="/sites/default/files/images/fixed_m6.png"><?php echo $bit_type; ?></li>
                                            <!--<li>$<span class="bit_proposal_amt"><?php //echo $bit_amount; ?></span></li>-->
                                          </ul>
                                        </div>
                                        <div class="m6_prop1_amount text-center">
                                          <ul>                                           
                                            <li><span class="bit_proposal_amt" data-entity="<?php echo $node_pro_id; ?>">
                                              <?php if($isCredentialRequired && empty($allow_bid_amount_access)){ ?>
                                                <a href="javascript:void(0);" class="proposal-bid-amount">See Bid Amount</a>
                                              <?php }else{ ?>
                                                <li>$<span class="bit_proposal_amt"><?php echo $bit_amount; ?></span></li>
                                              <?php } ?>
                                            </span></li>
                                          </ul>
                                        </div>
                                        <div class="m6_prop1_created text-center">
                                          <ul>
                                            <li>
                                              <!--<label>Created:</label>-->
                                              <!--<a href="/<?php //echo drupal_get_path_alias('node/' . $node_pro_id); ?>"></a>-->
                                              <span class="date"><?php echo $com_date; ?></span></li>
                                            <!--<li class="created_sp"><img src="/sites/default/files/images/blue_img.png">
                                            <?php
											/*if ($target_id != "") {
															$target_member = $target_id;
													} else if ($target_id1 != "") {
															$target_member = $target_id1;
															$get_summited_to_nid =  _get_company_nid_by_group_content($target_id1);
															$get_summited_to_nid_load = node_load($get_summited_to_nid);
													} else if ($target_id2 != "") {
															$target_member = $target_id2;
															$rr = 1;
															$get_summited_to_nid =  _get_company_nid_by_group_content($target_id2);
															$get_summited_to_nid_load = node_load($get_summited_to_nid);
													} else if ($target_id3 != "") {
														
															$target_member = $target_id3;
															//$get_summited_to_nid =  _get_company_nid_by_group_content($target_id3);
															$get_summited_to_nid_load = node_load($target_id3);
													}
													
													
													
													$company_address1 = render(field_view_field('node', $SubmitedBycompanyNid_load, 'field_org_address', array('label' => 'hidden')));
													$com_address1 = strip_tags($company_address1);
													
													$company_address2 = render(field_view_field('node', $get_summited_to_nid_load, 'field_org_address', array('label' => 'hidden')));
													$com_address2 = strip_tags($company_address2);
													
													
													
													
													$proposal_distent = get_distance_two_point($com_address1, $com_address2, "M");
													
													echo round($proposal_distent, 3);*/
										
					 //   $distance = getDistance($zip_code, $zip_code_user);
					//    echo number_format($distance, 2);
                                           ?>
                                            miles from you</li>-->
                                            <?php if ($unread_msg > 0) { ?>
                                            <li class="un_msg"><a href="/<?php echo drupal_get_path_alias('node/' . $node_pro_id); ?>">(<?php echo $unread_msg; ?>) Unread Messages</a></li>
                                            <?php } ?>
                                          </ul>
                                        </div>
                                        <div class="m6_actions">
                                          <div class="col-xs-12 text-right action">
                                            <?php
										    $cmpcall = in_array($user->uid,_get_company_users_by_group_content($propNode)) ;
                                            $cmpcall2 = in_array($user->uid, m6connect_projects_uids_from_list($propNode));
                                            if($cmpcall && $cmpcall2){
                                            } else {
										    ?>
                                            <div class="cust-prop-bookmark custom-bookmark"> <?php echo flag_create_link('bookmarks', $node_pro_id); ?> </div>
                                            <?php } ?>
                                            <div class="cust-invite-btn custom-favorite">
                                              <?php
																module_load_include('inc', 'flag', 'includes/flag.pages');
																echo flag_create_link('favourite', $node_pro_id);  ?>
                                            </div>
                                            <div class="cust-invite-btn custom-spam">
                                              <?php
																
																																		echo flag_create_link('spam', $node_pro_id);
																																		?>
                                            </div>
                                            <div class="btn-group" style="margin-top:40px;">
                                              <div class="dropdown">
                                                <?php if($isCredentialRequired){ ?>
                                                  <button class="btn btn-success proposal-action-button" type="button">Actions</button>
                                                <?php }else{ ?>
                                                  <button aria-expanded="false" aria-haspopup="true" class="btn btn-success" data-toggle="dropdown" id="dLabel" type="button">Actions</button>
                                                  <ul aria-labelledby="dLabel" class="dropdown-menu dropdown-menu-right" role="menu">
                                                    <li class="text-center"><a href="/<?php echo drupal_get_path_alias('node/' . $node_pro_id); ?>">Open</a></li>
                                                    <?php if ($node_award_id != $node_pro_id) { ?>
                                                      <li class="text-center"><a href="#" class="pro-award" id="award-<?php echo $f; ?>" data="<?php echo $node_owner . "@@" . $node_pro_id . "@@" . $userid1. "@@" . $CurrCompNid; ?>">Award</a></li>
                                                    <?php } ?>
                                                    <li class="text-center"><a href="#" class="pro-reject" id="reject-<?php echo $f; ?>" data="<?php echo $node_owner . "@@" . $node_pro_id . "@@" . $userid1; ?>">Reject</a></li>
                                                    <li class="text-center"><a href="#" class="pro-move-archive" id="move-archive-<?php echo $f; ?>" data="<?php echo $node_owner . "@@" . $node_pro_id . "@@" . $userid1; ?>">Move to Archive</a></li>
                                                    <li class="text-center"><a href="#" class="pro-group-move-archive" id="move-group-archive-<?php echo $node_pro_id; ?>" data="<?php echo $node_owner . "@@" . $node_pro_id . "@@" . $userid1; ?>" data-sutmittype="<?php print ucfirst($targetNodetype); ?>" data-submitfor="<?php print $sub_proposal_for; ?>">Move all "<?php print $sub_proposal_for; ?>" proposals to archive</a></li>
                                                </ul>
                                                <?php } ?>
                                              </div>
                                            </div>
                                          </div>
                                        </div>
                                      </li>
                                      <?php }
} ?>
                                    </ul>
                                    <div class="clearfix text-center" id="view_more"><a href="javascript:" >See More</a></div>
                                  </div>
                                </div>
                              </div>
                            </div>
                            
                            <!--<div id="pagination"></div>--> 
                          </div>
                          
                          <!-- content end --> 
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="footer_content clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4 footer_left">
          <?php if ($page['footer_left']): ?>
          <?php print render($page['footer_left']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_center">
          <?php if ($page['footer_center']): ?>
          <?php print render($page['footer_center']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_right">
          <?php if ($page['footer_right']): ?>
          <?php print render($page['footer_right']); ?>
          <?php endif; ?>
        </div>
      </div>
      <div class="clearfix">
				<?php if ($page['footer_top']): ?>
        <?php print render($page['footer_top']); ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class="footer_message clearfix">
    <div class="container">
      <?php if ($page['footer']): ?>
      <?php print render($page['footer']); ?>
      <?php endif; ?>
    </div>
  </div>

  <div class="container"><?php print render($page['bottom']); ?> </div>
</div>
<div id="proposal_pop_content">
  <div class="overlay"></div>
  <div class="proposal_pop_text">
    <div class="proposal_pop_text_inner">
      <h2 class="pro_required_title" style="font-weight:bold">Proposal </h2>
      <p class="pro_required"></p>
      <button id="current_pop" class="pro_close"  type="button">close</button>
    </div>
  </div>
</div>
<div id="requires_membership_upgrade_dialog"></div>
<?php
            // "Membership Upgrade Required" Dialog box
            /* $is_subcription = is_user_or_company_has_subscription($user->uid);
              $is_subcription = 0;
              $CompNid = _get_user_company_nid();
              $CompName = node_load($CompNid)->title;
              drupal_add_js(array('m6connect_rfp' => array('is_subscription' => $is_subcription)), 'setting');
              drupal_add_js(array('m6connect_rfp' => array('mupgrade_dialog_js' => 1)), 'setting'); */
            ?>
<!--<div id="membership-upgrade-confirm"><div class="text-center"><div class="dialog-heading"><strong>Membership Upgrade Required</strong></div><div class="dialog-description"><br />Your company, <?php //echo $CompName; ?>, agrees that you will upgrade your membership if you receive the Notice of Award email for this work.</div></div></div> --> 
<!--- MemberShip Upgrade Popup end --->

<?php
$query_2 = db_select('users_roles', 'ur')
        ->fields('ur', array('uid', 'rid'));
$db_or = db_or();
$db_or->condition(db_and()->condition('ur.uid', $user->uid, '=')->condition('ur.rid', array(1, 2, 3, 5, 6), 'NOT IN'));
$src_1 = $query_2->condition($db_or);
$result_2 = $src_1->execute();
foreach ($result_2 as $item_2) {
    $user_order_role = $item_2->rid;
}
?>
<link href="<?php echo $site_url; ?>/sites/all/themes/m6connect/css/simplePagination.css" type="text/css" rel="stylesheet"/>
<script src="<?php echo $site_url; ?>/sites/all/themes/m6connect/js/jquery.simplePagination.js"></script> 
<script>

                                                jQuery('#requires_membership_upgrade_dialog', '.page-proposals-received').dialog({
                                                    autoOpen: false,
                                                    width: 550,
                                                    modal: true,
                                                    resizable: false,
                                                    buttons: {
                                                        'Ok': function () {
                                                            jQuery(this).dialog("close");
                                                            var click_node_data = jQuery(this).find('span.click_data').text();
                                                            var membership = jQuery(this).find('span.click_membership').text();
                                                            jQuery.post("/my-proposal/ajax/action/award", {award_data: click_node_data, membership: membership}).done(function (data) {
                                                                //jQuery("#proposal_pop_content").fadeIn();	
                                                                //jQuery(".pro_required").text("Proposal Awarded Successfully");	
                                                                //jQuery(".pro_required_title").text("Proposal Award");			
                                                                //location.reload(); 		
                                                                //console.log(data);
                                                            });
                                                        },
                                                        'Cancel': function () {
                                                            jQuery(this).dialog("close");
                                                        }
                                                    },
                                                    open: function () {
                                                        jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                                                    }
                                                });

                                                $('.m6_view_proposal').on('click',".pro-award",function (e) {

                                                    var click_node_id = $(this).attr("id");
                                                    var click_node_data = $(this).attr("data");
                                                    var split_data = click_node_data.split("@@");
                                                    var node_data_user = split_data[0];
                                                    var node_data_pageID = split_data[1];
													var submitter_comID = split_data[3];
                                                    var container = jQuery(this).closest('.proposal-m6-container');
                                                    var propTitle = container.find('.m6_prop1_cont_title a span').text();
                                                    var membership_required = 0;
                                                    if (jQuery(this).closest('.proposal-m6-container').hasClass('membership_required')) {
                                                        membership_required = 1;
                                                    }
													jQuery()
                                                    var awardingCompany = container.find('.m6_prop1_cont span.data-cmpName').text();
													var submittedCompany = container.find('.default_cmp div').text();
													jQuery.post( '/check-proposal-popup-show/'+submitter_comID, function( data ) { 
													  //console.log(data.status);
													  if(data.status == 0) {
														jQuery('#requires_membership_upgrade_dialog').html('<div class="text-center"><div class="dialog-heading"><strong>Notice of Pending Award</strong></div><div class="dialog-description"><br/>Would you like to email this award to ' + submittedCompany + ' now?</div><span class="click_data" style="display:none;">' + click_node_data + '</span><span class="click_membership" style="display:none;">' + membership_required + '</span></div>');
														jQuery('#requires_membership_upgrade_dialog').dialog('open');
													  }else{
														/*jQuery('#requires_membership_upgrade_dialog').html('<div class="text-center"><div class="dialog-heading"><strong>Notice of Pending Award</strong></div><div class="dialog-description"><br/>A “Notice of Pending Award” will be sent to the selected company(s) - ' + propTitle + ' from ' + awardingCompany + '.  They are required to have a current Gold Membership and click on the green Action button to Accept the Award.  Upon accepting the award they will receive an official “Notice of Award” certificate.</div><span class="click_data" style="display:none;">' + click_node_data + '</span><span class="click_membership" style="display:none;">' + membership_required + '</span></div>');
														jQuery('#requires_membership_upgrade_dialog').dialog('open');*/
													  }
													});
                                                    
														
                                                        return false;
                                                    
                                                });


                                                //$(".pro-reject").click(function () {
												$('.m6_view_proposal').on('click',".pro-reject",function (e) {
                                                    var click_node_reject_id = $(this).attr("id");
                                                    var click_node_reject_data = $(this).attr("data");
                                                    $.ajax({
                                                        type: 'POST',
                                                        /*url: '<?php //echo $site_url;  ?>/sites/all/themes/m6connect/ajax-award.php',*/
                                                        url: '/my-proposal/ajax/action/reject',
                                                        data: {reject_data: click_node_reject_data},
                                                        success: function (response) {
                                                            $(".pro_required").text("Proposal Rejected Successfully");
                                                            $(".pro_required_title").text("Proposal Reject");
                                                            $("#proposal_pop_content").fadeIn();
                                                            location.reload();
                                                        }

                                                    });

                                                });
																								
																								
																											$('.m6_view_proposal').on('click',".pro-award",function (e) {
                                               					var click_node_award_id = $(this).attr("id");
																												var click_node_award_data = $(this).attr("data");
																												$.ajax({
																													type: 'POST',
																													
																													url: '/my-proposal/ajax/action/award',
																													data: {award_data: click_node_award_data},
																													success: function (response) {
																														$(".pro_required").text("Proposal Awarded Successfully");
																														$(".pro_required_title").text("Proposal Award");
																														$("#proposal_pop_content").fadeIn();
																														location.reload();
																													}
																												});

                                                		});
												
												//$(".pro-move-archive").click(function () {
												$('.m6_view_proposal').on('click',".pro-move-archive",function (e) {
                                                    var click_node_reject_id = $(this).attr("id");
                                                    var click_node_reject_data = $(this).attr("data");
                                                    $.ajax({
                                                        type: 'POST',
                                                        /*url: '<?php //echo $site_url;  ?>/sites/all/themes/m6connect/ajax-award.php',*/
                                                        url: '/my-proposal/ajax/action/archive',
                                                        data: {archive_data: click_node_reject_data},
                                                        success: function (response) {
															if(response.archived==1){
                                                              $(".pro_required").text("Proposal Moved to Archived Successfully");
                                                              $(".pro_required_title").text("Proposal Moved");
                                                              $("#proposal_pop_content").fadeIn();
															}
                                                            location.reload();
                                                        }

                                                    });
                                                });
												
												$('.m6_view_proposal').on('click',".pro-group-move-archive",function (e) {
                                                    var click_node_reject_id = $(this).attr("id");
                                                    var click_node_reject_data = $(this).attr("data");
													var submittedType = $(this).data('sutmittype');
													var submittedFor = $(this).data('submitfor');
                                                    $.ajax({
                                                        type: 'POST',
                                                        /*url: '<?php //echo $site_url;  ?>/sites/all/themes/m6connect/ajax-award.php',*/
                                                        url: '/my-proposal/ajax/action/grouparchive',
                                                        data: {grouparchive_data: click_node_reject_data},
                                                        success: function (response) {
															if(response.archived==1){
                                                              $(".pro_required").text("All Proposals related to "+submittedType+" : "+submittedFor+" moved to Archived Successfully");
                                                              $(".pro_required_title").text("Proposal Moved");
                                                              $("#proposal_pop_content").fadeIn();
															}
                                                            location.reload();
                                                        }

                                                    });
                                                });

                                                $(".pro_close").click(function () {
                                                    $("#proposal_pop_content").fadeOut();
                                                });


                                                jQuery(function ($) {

                                                    var items = $("#content_msg li.prop_m6con1");

//                var numItems = items.length;
//				if(numItems <= 10 ) 
//				{
//				document.getElementById("pagination").style.display = "none";
//				}
//                var perPage = 10;
//
//                // only show the first 2 (or "first per_page") items initially
//                items.slice(perPage).hide();

                                                    // now setup pagination
//                                                    $("#pagination").pagination({
//                                                        items: numItems,
//                                                        itemsOnPage: perPage,
//                                                        cssStyle: "light-theme",
//                                                        onPageClick: function (pageNumber) { // this is where the magic happens
//                                                            // someone changed page, lets hide/show lis appropriately
//                                                            var showFrom = perPage * (pageNumber - 1);
//                                                            var showTo = showFrom + perPage;
//
//                                                            items.hide() // first hide everything, then show for the new page
//                                                                    .slice(showFrom, showTo).show();
//                                                        }
//                                                    });


<!-- popup starts -->
                                                    var my_role = "<?php echo $user_order_role; ?>";
                                                    /************** Proposal Upgrade Popup *******************/
                                                    /*if (my_role == 4){
                                                     $("#popup_lock-upgrade").attr("class","pop_title");
                                                     $(".m6_prop1_img a").attr("class","pop_title");
                                                     $(".m6_prop1_cont a").attr("class","pop_title");
                                                     $(".m6_prop1_created a").attr("class","pop_title");
                                                     $(".dropdown ul.dropdown-menu li:first-child a").attr("class","pop_title");
                                                     }
                                                     $(".pop_title").click(function(){
                                                     $("#pop_content").fadeIn();	
                                                     return false;
                                                     });*/
                                                    /*********************************************************/



                                                    $(".pop_close").click(function () {
                                                        $("#pop_content").fadeOut();
                                                    });


                                                    // search start
                                                   /* $("#s").on("keyup click input", function () {
                                                        if (this.value.length > 0) {
                                                            $(".prop_m6con1").show().filter(function () {
                                                                return $(this).find('.search_class').text().toLowerCase().indexOf($("#s").val().toLowerCase()) == -1;

                                                            }).hide();

                                                        }
                                                        else {
                                                            $(".prop_m6con1").show();
                                                        }
                                                    });


                                                    $(".search_m6_prop1").on("click", function () {
                                                        if ($("#s").val().length > 0) {
                                                            $(".prop_m6con1").show().filter(function () {
                                                                return $(this).find('.search_class').text().toLowerCase().indexOf($("#s").val().toLowerCase()) == -1;

                                                            }).hide();

                                                        }
                                                        else {
                                                            $(".prop_m6con1").show();
                                                        }

                                                    });*/




                                                    var $divs = $("li.prop_m6con1");
                                                   /* document.getElementById("order_proposal").onchange = function () {
                                                        if (document.getElementById("order_proposal").value == "name_asc") {
                                                            var alphabeticallyOrderedDivs = $divs.sort(function (a, b) {
                                                                return $(a).find("h4").text() > $(b).find("h4").text();
                                                            });
                                                            $("ul#content_msg").html(alphabeticallyOrderedDivs);
                                                        }

                                                        if (document.getElementById("order_proposal").value == "name_desc") {
                                                            var alphabeticallyOrderedDivs = $divs.sort(function (a, b) {
                                                                return $(a).find("h4").text() < $(b).find("h4").text();
                                                            });
                                                            $("ul#content_msg").html(alphabeticallyOrderedDivs);
                                                        }

                                                        if (document.getElementById("order_proposal").value == "bit_amt_value") {

                                                            var numericallyOrderedDivs = $divs.sort(function (a, b) {
                                                                return $(a).find(".bit_proposal_amt").text().replace(/,/g, '') < $(b).find(".bit_proposal_amt").text().replace(/,/g, '');
                                                            });
                                                            $("ul#content_msg").html(numericallyOrderedDivs);

                                                        }

                                                        if (document.getElementById("order_proposal").value == "date_desc") {
                                                            var numericallyOrderedDivs = $divs.sort(function (a, b) {
                                                                return new Date($(a).find(".date").text()) < new Date($(b).find(".date").text());
                                                            });
                                                            $("ul#content_msg").html(numericallyOrderedDivs);
                                                        }

                                                        if (document.getElementById("order_proposal").value == "date_asc") {
                                                            var numericallyOrderedDivs = $divs.sort(function (a, b) {
                                                                return new Date($(a).find(".date").text()) > new Date($(b).find(".date").text());
                                                            });
                                                            $("ul#content_msg").html(numericallyOrderedDivs);

                                                        }

                                                    };*/
													
													/********************infinite scroll work start**********************/
													
                                                    var i = 0;
                                                    window.currentitems = 0;
                                                    $('#content_msg li.proposal-m6-container').each(function () {
                                                        if (i >= 15) {
                                                            $(this).hide();
															
                                                        }
                                                        i++;
                                                        window.currentitems = 15;
                                                    });


													
                                                    $('#view_more').click(function(){
                                                         var current  =  window.currentitems;  
                                                         current = current + 15;
                                                         
                                                         var k = 1;
                                                         $('#content_msg li.proposal-m6-container').each(function () {
                                                              
                                                             if(current >= k){
                                                                 $(this).show();
																
                                                             }
															 
															 
                                                             k++;
                                                         });
                                                         window.currentitems = current;
													
														if(current > k) 
														{
														document.getElementById("view_more").style.display = "none";
														}
                                                    });


												 var items = $("#content_msg li.prop_m6con1");
												
												var numItems = items.length;
												if(numItems <= 15 ) 
												{
												document.getElementById("view_more").style.display = "none";
												}
												  	
                                                    /********************infinite scroll work end**********************/




                                                });

</script> 

<!--- free plan popup start --->
<div id="pop_content">
  <div class="overlay"></div>
  <!--overlay-->
  <div class="pop_text">
    <div class="pop-main-top"> <a href="#close" class="pop_close"> <img src="/sites/all/themes/m6connect/images/pop_close.png"/></a>
      <h2>Unlock this Feature Today!</h2>
      <div class="m6_pop_log"> <img src="/sites/all/themes/m6connect/images/m6_pop_log.png"/> </div>
    </div>
    <div class="pop_text_inner">
      <p>Unlock the full power of M6Connect and access this content 
        by upgrading to one of our paid subscription levels. Click
        below to choose the subscription that is right for you!</p>
      <div class="m6_pop_list_im">
        <ul class="m6_pop_list">
          <li>View RFPs & Express Interest in Bidding
          <li>
          <li>Create & Send Proposals
          <li>
          <li>Connect with Other Companies
          <li>
          <li>Create & Post Projects
          <li>
          <li>Create & Send Contracts
          <li>
          <li>and Much More!
          <li> <img src="/sites/all/themes/m6connect/images/m6_pop_comp.png" class="compimg"/>
        </ul>
        <div class="m6_pop_upgrade_btn"> <a href="/upgrade-your-membership-subscription"> <img src="/sites/all/themes/m6connect/images/m6_pop_btn.png"/> </a> </div>
      </div>
      <!------m6_pop_list_im---> 
    </div>
    <!--pop text inner--> 
  </div>
  <!--pop text--> 
</div>
<!--pop content--> 

<!--- free plan popup end --->