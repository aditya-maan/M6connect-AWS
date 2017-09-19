<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
<?php
global $user;
$nid= $node->nid;
$logged_user = $user->uid;
$isUserCollabarated = FALSE;
$CurrCompNid = isset($_SESSION['company']) ? $_SESSION['company'] : '';
$company_admin_rols_access ='';
if($CurrCompNid){
	$node_by_com = _get_company_nid_by_group_content($node);
	$company_admin_rols = _get_company_users_by_og_roles($CurrCompNid,'company admin');
	if(($CurrCompNid == $node_by_com) && in_array($user->uid , $company_admin_rols)){			
		$company_admin_rols_access = 1;
	}
}
/*$query_status = db_select('node', 'publish')
        ->condition('publish.nid', $nid, '=')
        ->fields('publish', array('status'));
$result_status = $query_status->execute()->fetchAll();
$published_status = $result_status[0]->status;*/
$published_status = $node->status;
$submitted_for = $node->field_choose_from_the_options_li['und'][0]['value'];
// project details
$submitted_project = $node->field_field_sub_proposal_pjt['und'];
for ($p = 0; $p < count($submitted_project); $p++) {
  $Sub_proposal_project .= $submitted_project[$p]['entity']->title . "@@";
  $Sub_proposal_project_user_id .= $submitted_project[$p]['entity']->uid . "@@";
  $Sub_proposal_project_cont_view .= "<span>" . $submitted_project[$p]['entity']->title . "</span>";
}
$project_user_id_exp = explode("@@", $Sub_proposal_project_user_id);
$project_user_title_exp = explode("@@", $Sub_proposal_project);
$project_key_search = array_search($logged_user, $project_user_id_exp);
$proposal_project_view_user = $project_user_id_exp[$project_key_search];
$proposal_projectTitle_view_user = $project_user_title_exp[$project_key_search];
//member details
$submitted_member = $node->field_submit_proposal_member['und'];
for ($m = 0; $m < count($submitted_member); $m++) {
//$Sub_proposal_member .= $submitted_member[$m]['entity']->title."@@";
    $Sub_proposal_member_user_id .= $submitted_member[$m]['entity']->uid . "@@";
    $Sub_proposal_member .= $node->field_submit_proposal_member['und'][$m]['entity']->field_first_name['und'][0]['value'] . " " . $node->field_submit_proposal_member['und'][$m]['entity']->field_last_name['und'][0]['value'] . "@@";
    $Sub_proposal_member_cont_view .= "<span>" . $node->field_submit_proposal_member['und'][$m]['entity']->field_first_name['und'][0]['value'] . " " . $node->field_submit_proposal_member['und'][$m]['entity']->field_last_name['und'][0]['value'] . "</span>";
}
//echo $Sub_proposal_member;
$member_user_id_exp = explode("@@", $Sub_proposal_member_user_id);
$member_user_title_exp = explode("@@", $Sub_proposal_member);
$member_key_search = array_search($logged_user, $member_user_id_exp);
$proposal_member_view_user = $member_user_id_exp[$member_key_search];
$proposal_memberTitle_view_user = $member_user_title_exp[$member_key_search];

// rfp details
$submitted_rfp_owner = $node->field_submit_proposal_in_respons['und'][0]['entity']->uid;
$submitted_rfp_name = $node->field_submit_proposal_in_respons['und'][0]['entity']->title;

//company details
$submitted_company = $node->field_submit_proposal_to_company['und'];
for ($c = 0; $c < count($submitted_company); $c++) {
    $Sub_proposal_company .= $submitted_company[$c]['entity']->title . "@@";
    $Sub_proposal_company_view_cont .= "<span>" . $submitted_company[$c]['entity']->title . "</span>";
    $Sub_proposal_company_user_id .= $submitted_company[$c]['entity']->uid . "@@";
}
$company_user_id_exp = explode("@@", $Sub_proposal_company_user_id);
$key_search = array_search($logged_user, $company_user_id_exp);
$proposal_view_company_user = $company_user_id_exp[$key_search];

// other fields
      $proposal_number = $node->field_proposal_number['und'][0]['value'];
      $scope_of_work = $node->field_proposal_scope_of_work['und'][0]['value'];
      $Proposal_bid_amount = $node->field_proposal_bid_amount['und'][0]['value'];
      $Proposoal_bid_types = $node->field_proposoal_bid_types['und'][0]['value'];

      $contractor_id = $node->uid;                           
      $result_contractor_addr = getProposalContractAddr($contractor_id);
      $result_contractor = getProposalContractorName($contractor_id);
      foreach ($result_contractor as $item_contractor) {
          $contractor_name_split = explode("_", $item_contractor->name);
          $contractor_name = strtoupper($contractor_name_split[0]);
          $contractor_email = $item_contractor->mail;
      }      
      $result_contractor_phone = getProposalContractorPhone($contractor_id);
      $contractor_phone_num = $result_contractor_phone[0]->field_phone_value;
      for ($s = 0; $s < count($submitted_member); $s++) {
          $Sub_proposal_mem = $submitted_member[$s]['entity']->title;
      }
      if (($logged_user == $submitted_rfp_owner) || ($logged_user == $proposal_view_company_user ) || ($logged_user == $proposal_project_view_user) || ($logged_user == $proposal_member_view_user) || ($logged_user == $contractor_id) || (in_array('administrator', $user->roles)) || ($company_admin_rols_access == TRUE) || is_proposal_project_collabarated($node)) { // For proposal seen by admin

        if ($submitted_rfp_owner != "") {
            $Submit_rfp_store_value = $submitted_rfp_owner;
        } else if ($proposal_view_company_user != "") {
            $Submit_rfp_store_value = $proposal_view_company_user;
        } else if ($proposal_project_view_user != "") {
            $Submit_rfp_store_value = $proposal_project_view_user;
        } else if ($proposal_member_view_user != "") {
            $Submit_rfp_store_value = $proposal_member_view_user;
        //}
	      } else if(in_array('administrator', $user->roles)){ // For proposal seen by admin
		    $Submit_rfp_store_value = $logged_user;	
			}                                
      $result_owner = getProposalOwnerName($Submit_rfp_store_value);
      foreach ($result_owner as $item_owner) {
          $owner_name_split = explode("_", $item_owner->name);
          $owner_name = strtoupper($owner_name_split[0]);
          $owner_email = $item_owner->mail;
      }                                
      $result_owner_phone = getProposalOwnerPhone($Submit_rfp_store_value);
      $owner_phone_num = $result_owner_phone[0]->field_phone_value;
      $result_owner_company = getProposalOwnerCompanyTitle($Submit_rfp_store_value);
      $owner_company = $result_owner_company[0]->title;
      // owner company info                                
      $result_owner_company_vid = getProposalOwnerCompanyVid($Submit_rfp_store_value);
      $owner_company_vid = $result_owner_company_vid[0]->vid;
      //$bidder_type = $src_div_company_vid[0]->title;
      // user company diversity info ends                                
      $result_owner_addr = getProposalOwnerAddress($owner_company_vid);
      $result_owner_city = $result_owner_addr[0]->field_org_address_locality;
      $result_owner_state = $result_owner_addr[0]->field_org_address_administrative_area;
      $result_owner_zip = $result_owner_addr[0]->field_org_address_postal_code;
      $result_owner_address = $result_owner_addr[0]->field_org_address_thoroughfare;

      // contractor company info                                
      $result_cont_company_vid = getProposalContractorVid($contractor_id);
      $cont_company_vid = $result_cont_company_vid[0]->vid;
      $cont_company_vid =   _get_user_company_nid($contractor_id);
      $result_cont_addr = getProposalContractorComAddr($cont_company_vid);
      $result_cont_city = $result_cont_addr[0]->field_org_address_locality;
      $result_cont_state = $result_cont_addr[0]->field_org_address_administrative_area;
      $result_cont_zip = $result_cont_addr[0]->field_org_address_postal_code;
      $result_cont_address = $result_cont_addr[0]->field_org_address_thoroughfare;
      ?>
        <!-- <div class="bfeedback-report-btn form-group text-right">
                    <a href="/proposalsummary/<?php //echo $nid; ?>">
                    <img src="<?php //echo $base_url; ?>/sites/all/themes/m6connect/images/icon-news2.png"> PDF Report          	</a>
                </div>-->
        <div class="view_my_proposal"> 
          <!--<div class="head_creat_prop">  
         <div class="left_cre_prop">
          <a href="#"><img src="/sites/all/themes/m6connect/images/log_creat_prop.png"/></a> 
      <?php if ($published_status == 0) { ?> <h1>Draft</h1>  <?php } ?>	  
         </div>     
      </div>
    <div class="box box-with-image"></div>-->
  <div class="m6_view_proposal">
    <?php if(($node->uid == $user->uid || $company_admin_rols_access == TRUE) && $published_status == 0){?>
    <div class="pull-right"> <?php print l('<input type="button" class="form-submit" value="Edit"/>','node/'.$node->nid.'/edit', array('html'=>TRUE));?> </div>
    <?php } ?>
    <div class="m6_main_view row margin-5">
      <div class="left_m6_view col-md-4 col-sm-4 col-xs-12 padding-5">
      <div class="left_m6_view_content clearfix">
        <div class="m6_top_drywall">
          <h3># <?php print($proposal_number); ?></h3>
          <h6><?php print $title; ?></h6>
        </div>
        <?php
		  if ($Proposal_bid_amount != '') {
			  $pro_bid_amt = "$" . $Proposal_bid_amount;
		  }
		  if ($Proposoal_bid_types != '') {
			  $bid_type = "(" . $Proposoal_bid_types . ")";
		  }
		  ?>
        <div class="m6_view_content">
          <ul>
            <li>
              <label>Bid Amount:</label>
              <h1> <?php print $pro_bid_amt; ?></h1>
            </li>
            <li class="bidder-type">
              <label>Bidder Diversity Type:</label>
              <?php
      				// user company diversity info
      				/*$query_diversity_info = db_select('node', 'diver')
      						->fields('diver', array('title'));
      				$db_div_owner_vid = db_or();
      				$db_div_owner_vid->condition(db_and()->condition('diver.type', 'diversity', '=')->condition('diver.uid', $logged_user, '='));
      				$src_diver_company_vid = $query_diversity_info->condition($db_div_owner_vid);
      				$src_div_company_vid = $src_diver_company_vid->execute()->fetchAll();*/
      				$src_div_company_vid = array();
      				if(is_numeric($node_by_com)){    			 
          			  $src_div_company_vid = getProposalDiversityInfo($node_by_com);
      				}
      				for ($m = 0; $m < count($src_div_company_vid); $m++) {
      					$bidder_type = '<span>' . $src_div_company_vid[$m]->title . '</span>';
      					echo $bidder_type;
      				}
      				?>
            </li>
            <li>
              <label>Bid Type:</label>
              <span><?php echo $bid_type; ?></span></li>
            <li class="m6_sub_add">
              <div class="clearfix">
                <div class="pull-left">
                  <label>Submitted For: </label>
                </div>
                <div class="pull-right">
                  <?php 
				          if(proposal_reassign_proposal_access_callback($node)){ 
                    print l('Reassign','/reassign/'.$nid.'/proposal', array('attributes'=>array('style'=>'text-decoration: underline;'))); 
                  } 
				        ?>
                </div>
              </div>
              <span><?php print $submitted_for; ?></span> </li>
            <?php if ($submitted_rfp_name != "") { ?>
            <li class="m6_sub_add">
              <label>RFP:</label>
              <span><?php echo $submitted_rfp_name; ?></span></li>
            <?php } ?>
            <?php if ($Sub_proposal_project_cont_view != "") { ?>
            <li class="m6_sub_add">
              <label>Project:</label>
              <?php echo $Sub_proposal_project_cont_view; ?></li>
            <?php } ?>
            <?php if ($Sub_proposal_member_cont_view != "") { ?>
            <li class="m6_sub_add">
              <label>Individual Member:</label>
              <?php echo $Sub_proposal_member_cont_view; ?></li>
            <?php } ?>
            <?php if ($Sub_proposal_company_view_cont != "") { ?>
            <li class="m6_sub_add">
              <label>Organization:</label>
              <span><?php echo $Sub_proposal_company_view_cont; ?></span></li>
            <?php } ?>
            <li class="m6_sub_add">
              <label>Job Location:</label>
              <div id="view_map" class="display-inline-block"> <span id="addr-pro"></span> 
                <!--<span id="addr-pro-city"></span>--> 
                <?php print render(field_view_field('node', $node, 'field_proposal_job_location')); ?> <span id="addr-pro-state"></span> <span id="addr-pro-country"></span> </div>
            </li>
          </ul>
        </div>
        <div class="m6_view_map" id="map_dis">
          <?php 
				    /*$result_owner_full_addr = '';
					//drup_msg($result_owner_addr);
				    if(!empty($result_owner_addr)){
					  $result_owner_full_addr_map = array(
						trim($result_owner_addr[0]->field_org_address_thoroughfare),
						trim($result_owner_addr[0]->field_org_address_premise),
						trim($result_owner_addr[0]->field_org_address_locality),
						trim($result_owner_addr[0]->field_org_address_administrative_area),
						trim($result_owner_addr[0]->field_org_address_country),
						trim($result_owner_addr[0]->field_org_address_postal_code),
					  );
					  $result_owner_full_addr_map = array_filter($result_owner_full_addr_map);
					  $result_owner_full_addr = implode(', ',$result_owner_full_addr_map);
				    } 
					print '<iframe width="238" height="238" frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="https://maps.google.com/maps?&amp;q='.rawurlencode($result_owner_full_addr).'&amp;output=embed"></iframe>';*/
				  ?>
        </div>
        </div>
      </div>
      <?php
		$owner_addr = $result_owner_city . " " . $result_owner_state . " " . $result_owner_zip;
		if (trim($owner_addr) == "") {
			$owner_addr = "-";
		}
		if (trim($result_owner_address) == "") {
			$result_owner_address = "-";
		}
		?>
      <div class="right_m6_view col-md-8 col-sm-8 col-xs-12 padding-5">
        <div class="m6_own_con clearfix">
          <div class="m6_own m6_scope clearfix margin-bottom-20">
            <div class="row margin-5">
              <div class="m6_own_left col-md-6 col-sm-6 col-xs-12 padding-5">
                <div class="clearfix">
                  <h1>Customer Company </h1>
                </div>
                <div class="clearfix">
                  <ul class="m6_own_info">
                    <li>
                      <label>Name:</label>
                      <span><?php echo $owner_company; ?></span></li>
                    <li>
                      <label>Address:</label>
                      <span><?php echo $result_owner_address; ?></span></li>
                    <li>
                      <label>City, State, Zip:</label>
                      <span><?php echo $owner_addr; ?></span></li>
                    <li>
                      <label>Phone:</label>
                      <span><?php 
					  if(!empty($owner_phone_num)){
					  $owner_phone_num_val = get_international_formatPhoneNumber($owner_phone_num);
					  echo $owner_phone_num_val; 
					  }
					  ?>
                      </span></li>
                    <li>
                      <label>Email:</label>
                      <span><?php echo $owner_email; ?></span></li>
                    <?php if ($submitted_rfp_name != "") { ?>
                    <?php /*?><li>
                        <label>RFP:</label>
                        <span><?php echo $submitted_rfp_name; ?></span></li><?php */?>
                    <?php } ?>
                    <?php if ($proposal_project_view_user != "") { ?>
                    <li>
                      <label>Project:</label>
                      <span><?php echo $proposal_projectTitle_view_user; ?></span></li>
                    <?php } ?>
                    <?php if ($proposal_member_view_user != "") { ?>
                    <li>
                      <label>Individual Member:</label>
                      <span><?php echo $proposal_memberTitle_view_user; ?></span></li>
                    <?php } ?>
                    <?php if ($proposal_view_user != "") { ?>
                    <li>
                      <label>Company:</label>
                      <span><?php echo $owner_company; ?></span></li>
                    <?php } ?>
                  </ul>
                </div>
              </div>
              <?php
				$contractor_addr = $result_cont_city . " " . $result_cont_state . " " . $result_cont_zip;
				if (trim($contractor_addr) == "") {
					$contractor_addr = "-";
				}
				if (trim($result_cont_address == "")) {
					$result_cont_address = "-";
				}
				$cmpTitle = '';
				$cmpNid = _get_user_company_nid($node->uid);
				if($cmpNid && is_numeric($cmpNid)){
				  $cmpNode = node_load($cmpNid);
				  $cmpTitle = $cmpNode->title;
				}
				?>
              <div class="m6_own_right col-md-6 col-sm-6 col-xs-12 padding-5">
                <div class="clearfix">
                  <h1>Submitting Company</h1>
                </div>
                <div class="clearfix">
                  <ul class="m6_own_info">
                    <li>
                      <label>Name:</label>
                      <span><?php echo  $cmpTitle; ?></span></li>
                    <li>
                      <label>Address:</label>
                      <span><?php echo $result_cont_address; ?></span></li>
                    <li>
                      <label>City, State, Zip:</label>
                      <span><?php echo $contractor_addr; ?></span></li>
                    <li>
                      <label>Phone:</label>
                      <span>
					  <?php 
					  	if(!empty($contractor_phone_num)){
						$contractor_phone_num_val = get_international_formatPhoneNumber($contractor_phone_num);
					 	echo $contractor_phone_num_val; 
						}
					  ?>
                      </span></li>
                    <li>
                      <label>Email:</label>
                      <span><?php echo $contractor_email; ?></span></li>
                  </ul>
                </div>
              </div>
            </div>
          </div>
          <div class="m6_own m6_scope clearfix margin-bottom-20">
            <div class="clearfix">
              <h1>Description</h1>
            </div>
            <div class="clearfix">
              <ul class="m6_own_info">
                <li><?php echo nl2br($scope_of_work); ?></li>
              </ul>
            </div>
          </div>
          <div class="m6_own m6_scope clearfix margin-bottom-20">
          <div class="clearfix">
            <h1>eProposal Documents</h1>
            </div>
            <div class="doc_det m6_prop_tab clearfix margin-bottom-20">
              <div id="page-wrap1_viewprop">
                <table>
                  <thead>
                    <tr>
                      <th>Select</th>
                      <th>Document Name</th>
                      <th style="text-align:center;">Type</th>
                      <th>Uploaded Date</th>
                    </tr>
                  </thead>
                  <tbody>
                    <?php
					  $time = $node->field_proposal_document_picture['und'];
					  $count_docu = count($time);
					  if ($count_docu == '0') {
						  echo '<tr>
					  <td colspan="4" style="text-align:center;">No eProposal Document</td>
					  </tr>';
					  } else {
						  $file_data = '';
						  for ($c = 0; $c < count($time); $c++) { //pre($time,1);
							  $det_time = $time[$c]['timestamp'];
							  $det_name = $time[$c]['filename'];
							  $det_mine = $time[$c]['filemime'];
							  $det_fid = $time[$c]['fid'];
  
							  switch ($det_mine) {
								  case "image/jpeg":
								  case "image/jpg":
								  case "image/png":
								  case "image/gif":
								  case "image/tif":
									  $img_src = "image-x-generic";
									  break;
								  case "application/pdf":
									  $img_src = "application-pdf";
									  break;
								  case "text/plain":
									  $img_src = "text-plain";
									  break;
								  case "application/msword":
								  case "application/vnd.ms-word.document.macroEnabled.12":
								  case "application/vnd.oasis.opendocument.text":
								  case "application/vnd.oasis.opendocument.text-template":
								  case "application/vnd.oasis.opendocument.text-master":
								  case "application/vnd.oasis.opendocument.text-web":
								  case "application/vnd.openxmlformats-officedocument.wordprocessingml.document":
								  case "application/vnd.stardivision.writer":
								  case "application/vnd.sun.xml.writer":
								  case "application/vnd.sun.xml.writer.template":
								  case "application/vnd.sun.xml.writer.global":
								  case "application/vnd.wordperfect":
								  case "application/x-abiword":
								  case "application/x-applix-word":
								  case "application/x-kword":
								  case "application/x-kword-crypt":
									  $img_src = "x-office-document";
									  break;
								  // Spreadsheet document types.
								  case "application/vnd.ms-excel":
								  case "application/vnd.ms-excel.sheet.macroEnabled.12":
								  case "application/vnd.oasis.opendocument.spreadsheet":
								  case "application/vnd.oasis.opendocument.spreadsheet-template":
								  case "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet":
								  case "application/vnd.stardivision.calc":
								  case "application/vnd.sun.xml.calc":
								  case "application/vnd.sun.xml.calc.template":
								  case "application/vnd.lotus-1-2-3":
								  case "application/x-applix-spreadsheet":
								  case "application/x-gnumeric":
								  case "application/x-kspread":
								  case "application/x-kspread-crypt":
									  $img_src = "x-office-spreadsheet";
									  break;
  
								  // Presentation document types.
								  case "application/vnd.ms-powerpoint":
								  case "application/vnd.ms-powerpoint.presentation.macroEnabled.12":
								  case "application/vnd.oasis.opendocument.presentation":
								  case "application/vnd.oasis.opendocument.presentation-template":
								  case "application/vnd.openxmlformats-officedocument.presentationml.presentation":
								  case "application/vnd.stardivision.impress":
								  case "application/vnd.sun.xml.impress":
								  case "application/vnd.sun.xml.impress.template":
								  case "application/x-kpresenter":
									  $img_src = "x-office-presentation";
									  break;
  
								  // Compressed archive types.
								  case "application/zip":
								  case "application/x-zip":
								  case "application/stuffit":
								  case "application/x-stuffit":
								  case "application/x-7z-compressed":
								  case "application/x-ace":
								  case "application/x-arj":
								  case "application/x-bzip":
								  case "application/x-bzip-compressed-tar":
								  case "application/x-compress":
								  case "application/x-compressed-tar":
								  case "application/x-cpio-compressed":
								  case "application/x-deb":
								  case "application/x-gzip":
								  case "application/x-java-archive":
								  case "application/x-lha":
								  case "application/x-lhz":
								  case "application/x-lzop":
								  case "application/x-rar":
								  case "application/x-rpm":
								  case "application/x-tzo":
								  case "application/x-tar":
								  case "application/x-tarz":
								  case "application/x-tgz":
									  $img_src = "package-x-generic";
									  break;
  
								  // Script file types.
								  case "application/ecmascript":
								  case "application/javascript":
								  case "application/mathematica":
								  case "application/vnd.mozilla.xul+xml":
								  case "application/x-asp":
								  case "application/x-awk":
								  case "application/x-cgi":
								  case "application/x-csh":
								  case "application/x-m4":
								  case "application/x-perl":
								  case "application/x-php":
								  case "application/x-ruby":
								  case "application/x-shellscript":
								  case "text/vnd.wap.wmlscript":
								  case "text/x-emacs-lisp":
								  case "text/x-haskell":
								  case "text/x-literate-haskell":
								  case "text/x-lua":
								  case "text/x-makefile":
								  case "text/x-matlab":
								  case "text/x-python":
								  case "text/x-sql":
								  case "text/x-tcl":
									  $img_src = "text-x-script";
									  break;
								  // HTML aliases.
								  case "application/xhtml+xml":
									  $img_src = "text-html";
									  break;
								  // Executable types.
								  case "application/x-macbinary":
								  case "application/x-ms-dos-executable":
								  case "application/x-pef-executable":
									  $img_src = "application-x-executable";
									  break;
								  default:
									  $img_src = "application-octet-stream";
							  }
                             echo '<tr>
						  <td><input name="chk[]" class="down_valu" value="' . $det_name . '" type="checkbox" id="download_' . $c . '" data="'.$det_fid.'"/></td>
						  <td class="proposal_down_url"><a class="down_url">' . $det_name . '</a></td>
						  <td align="center"><img src ="/modules/file/icons/' . $img_src . '.png"></td>
						  <td><span>' . date('m/d/Y g:i A', $det_time) . '</span></td>            
						  </tr>';
						  $file_data.= "'" . $det_name . "',";

						  //echo $det_mine;
					  }
					  $file_data = substr_replace($file_data, "", -1);
				  }
				  ?>
                  </tbody>
                </table>
              </div>
            </div>
            <?php if ($count_docu > 0) { ?>
            <div class="m6_download clearfix">
              <button id="download-sel" class="m6_down_sel pull-left" >Download Selected Documents</button>
              <button id="download-btn" class="m6_down_sel pull-left" >Download All Documents</button>
              <div id="down_all_test" style="display:none;"></div>
            </div>
            <?php }else{ ?>
            <span id="download-sel" class="m6_down_sel"></span>
            <?php }?>
          </div>
          <script src="/sites/all/themes/m6connect/js/browser.js"></script> 
          <script>
			var url_dess = [];
			var value_des = [];

			$('#download-btn').click(function () {

				$lend = $('#page-wrap1_viewprop input:checkbox').length;
				var param= new Array();
				var doc =0;
				for (var i = 0; i < $lend; i++)
				{
					var idss = $("#download_" + i).val();
					url_dess[i] = idss;
					//value_des[i] = idss.substring(idss.lastIndexOf('/') + 1);
					//var fids = $("#download_" + i).attr('data');
					doc++;
					param.push('fids[]=' + $("#download_" + i).attr('data') || 0);
				}
				var url = param.join('&');
				if(doc > 0 && url!=''){
				  url = '/all-document-download?'+url;
				  window.location = url;
				} 

				/*$.ajax({
					type: 'POST',
					url: '<?php echo $site_url; ?>/sites/default/download_all.php',
					data: {url_down: url_dess},
					dataType: "html",
					success: function (content) {
						$('#down_all_test').html('<iframe src="' + content + '"></iframe>');  // replace								   
					}
				});*/
			});

			$('#page-wrap1_viewprop .down_valu').click(function () {
				if ($('#page-wrap1_viewprop input:checkbox:checked').length == 0)
				{
					$('.m6_own_con #download-sel').css('display', 'none');
				}
				if ($('#page-wrap1_viewprop input:checkbox:checked').length > 0)
				{
					$('.m6_own_con #download-sel').css('display', 'block');
				}
			});

			document.querySelector('#download-sel').addEventListener('click', function (e) {
				var chkArray = [];
				// look for all checkboes that have a class 'chk' attached to it and check if it was checked 
				var i = 0;
				$(".down_valu:checked").each(function () {
					//chkArray.push($(this).val());
					chkArray.push('fids[]=' + $(this).attr('data') || 0);        
					i = i + 1;
				});
				var url = chkArray.join('&');
				if(i >= 0 && url!=''){
				  url = '/all-document-download?'+url;
				  window.location = url;
				} 

				/*if(i == '0')
				 {
				 $("#proposal_pop_content").fadeIn();
				 $(".pro_required_title").text("Proposal Documents");
				 $(".pro_required").text("Please select at least one of the checkbox");
				 }*/
				 
				 
				/*
				if (i == '1')
				{ alert('hh');
					getValueUsingClass();
					var files = e.target.dataset.files.split(',');
					multiDownload(files);
				}
				if (i > 1)
				{
					$.ajax({
						type: 'POST',
						url: '<?php echo $site_url; ?>/sites/default/download_all.php',
						data: {url_down: chkArray},
						dataType: "html",
						success: function (content) {
							$('#down_all_test').html('<iframe src="' + content + '"></iframe>');  // replace								   
						}
					});
				}
				*/

			});

			function getValueUsingClass() {
				// declare an checkbox array 
				var chkArray1 = [];
				var chk = [];
				// look for all checkboes that have a class 'chk' attached to it and check if it was checked 
				$(".down_valu:checked").each(function () {
					chkArray1.push('<?php echo $site_url; ?>/sites/default/files/' + $(this).val());
				});
				// we join the array separated by the comma 
				var selected;
				selected = chkArray1.join(',');
				// check if there is selected checkboxes, by default the length is 1 as it contains one single comma 
				if (selected.length > 1) {
					$("#download-sel").attr('data-files', selected);
				}
			}

		</script>
          <div class="m6_own m6_scope clearfix">
          <div class="clearfix">
            <h1>eProposal Communications</h1>
            </div>
            <div class="doc_det m6_prop_tab clearfix margin-bottom-20">
              <table>
                <thead>
                  <tr>
                    <th>Id</th>
                    <th>Status</th>
                    <th>Subject</th>
                    <th>From</th>
                    <th>Message Date</th>
                  </tr>
                </thead>
                <tbody>
                  <?php
      					  //read msg starts					  
      					  $result_status1 = proposalReadUnreadMsg($logged_user);
      					  $i = 0;
      					  foreach ($result_status1 as $item_read) {
      						  $read_cmd_id[$i] = $item_read->comment_id;
      						  $i++;
      					  }
      					  //echo '<pre>'; print_r($read_cmd_id); echo '</pre>';
      					  //read msg ends					  
      					  $result_comment_count = proposalComment($nid);
      					  $sub1 = count($result_comment_count);
      					  $j = 0;
      					  foreach ($result_comment_count as $item_read_st) {
      						  $read_cmd_id_st[$j] = $item_read_st->cid;
      						  $j++;
      					  }
      					  $cmb_in = array_intersect($read_cmd_id_st, $read_cmd_id);
      					  $sub2 = count($cmb_in);
      					  $unread_msg = $sub1 - $sub2;
      					  //echo 'Unread msg = '.$unread_msg;
      					  if (count($result_comment_count) == 0) {
      						  echo '<tr>
      					  <td style="text-align:center;" colspan="5">No eProposal Communication</td>
      					  </tr>';
      					  } else {
      					    $i = 1;
        						foreach ($result_comment as $item_comment) {
        						  $result_commenter_lname = getProposalCommenterLastName($item_comment->uid);
        						  foreach ($result_commenter_lname as $item_commenter_lname) {
        							  $commenter_lname = $item_commenter_lname->field_last_name_value;								 
        							  $result_commenter_fname = getProposalCommenterFirstName($item_comment->uid);
        							  foreach ($result_commenter_fname as $item_commenter_fname) {
        								  $commenter_fname = $item_commenter_fname->field_first_name_value;
        								  $com_id = $item_comment->cid;
        								  $com_msg = $item_comment->subject;
        								  $com_name = $commenter_fname . " " . $commenter_lname;
        								  $com_date = date('m/d/Y g:i A', $item_comment->created);
        								  $comts_id = date('Y', $item_comment->created) . '-' . $proposal_number . '-' . $i;
        								  $user_id = $user->uid;
        								  $show_msg = "'" . $com_id . "','" . $proposal_number . "','" . $user_id . "'";
        								  ?>
                          <tr onclick="javascript:showmsg(<?php echo $show_msg; ?>);" class="<?php
                            if (in_array($com_id, $read_cmd_id)) {echo 'read';} else {echo 'unread';}
        				           ?>">
                            <td class="m6_unread"><a href="#" class="view_new_message"><span><?php echo $comts_id; ?></span></a></td>
                            <td class="m6_unread"><a href="#" class="view_new_message"><span>
                              <?php
                  						if (in_array($com_id, $read_cmd_id)) {
                  							echo "read";
                  						} else {
                  							echo 'unread';
                  						}
                  						?>
                              </span></a></td>
                            <td class="m6_unread"><a href="#" class="view_new_message"><span><?php echo $com_msg; ?></span></a></td>
                            <td class="m6_unread"><a href="#" class="view_new_message"><span><?php echo $com_name; ?></span></a></td>
                            <td class="m6_unread"><a href="#" class="view_new_message"><span><?php echo $com_date; ?></span></a></td>
                          </tr>
                          <?php
        						    }
        					    } $i++;
      					    }
      				    }
      				  ?>
                </tbody>
              </table>
            </div>
            <div class="m6_download clearfix"> <a href="#" class="m6_down_sel proposal_send_click"  data="<?php print($proposal_number); ?>" id="send_my_new_message">Send New Message</a> </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div id="create_new_prop_pop_content" class="view_new_message_popup">
    <div class="overlay"></div>
    <div class="create_pop_text" id="view_pop_text"> 
      <script>
		function showmsg($cid, $pro_no, $us_id)
		{
			//alert($cid); alert($pro_no); alert($us_id);
			document.getElementById("proposal_msg_no").innerHTML = "View Message For Proposal " + $pro_no;
			var current_cmdid = $cid;
			var current_proid = $pro_no;
			var current_userid = $us_id;

			$.post( '/proposal_comment_view/'+current_proid+'/'+current_cmdid).done(function( data ) {
			  $('#proposal_msg_text').html(data.output);
			});

		}
	</script>
      <div class="create_new_pop_inner1">
        <h2 id="proposal_msg_no"></h2>
        <div id="proposal_msg_text"></div>
        <div class="create_new_btn_last" id="send_new_message"> 
          <a class="cancel_create">Close</a> </div>
      </div>
    </div>
  </div>
</div>
<?php } ?>
<?php hide($content['comments']); print render($content['comments']); ?>
</div>
