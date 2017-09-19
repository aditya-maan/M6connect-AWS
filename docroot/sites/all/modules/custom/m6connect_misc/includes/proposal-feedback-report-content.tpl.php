<?php

global $user;
$nid= $node->nid;
$logged_user = $user->uid;

$proposal_number = $node->field_proposal_number['und'][0]['value'];
$scope_of_work = $node->field_proposal_scope_of_work['und'][0]['value'];
$Proposal_bid_amount = $node->field_proposal_bid_amount['und'][0]['value'];
$Proposoal_bid_types = $node->field_proposoal_bid_types['und'][0]['value'];
$proposal_submitted_for = $node->field_choose_from_the_options_li['und'][0]['value'];

$propos_add_althoroughfare = $node->field_proposal_job_location['und'][0]['thoroughfare'];
$propos_add_locality = $node->field_proposal_job_location['und'][0]['locality'];
$propos_add_adminis = $node->field_proposal_job_location['und'][0]['administrative_area'];
$propos_add_postalcode = $node->field_proposal_job_location['und'][0]['postal_code'];
						   
						  
						  

//////////////// For Customer Information ///////////////

$submitedForContentNid = '';
$submitedForContentNode = '';
$submitedForContentType = '';
$submittedToCompany ='';
$fieldmapping = array(
	'Submit Proposal in Response to a RFP'=> array('field'=>'field_submit_proposal_in_respons','type'=>'rfp'),
	'Submit Proposal in Response to a Project'=> array('field'=>'field_field_sub_proposal_pjt','type'=>'project'),
	'Submit Proposal to a company'=> array('field'=>'field_submit_proposal_to_company','type'=>'organization'),
);

if(array_key_exists($proposal_submitted_for,$fieldmapping)){
  if(isset($node->{$fieldmapping[$proposal_submitted_for]['field']}['und']) && !empty($node->{$fieldmapping[$proposal_submitted_for]['field']}['und'][0]['target_id'])){
    $submitedForContentNid = $node->{$fieldmapping[$proposal_submitted_for]['field']}['und'][0]['target_id'];
	$submitedForContentNode = node_load($submitedForContentNid);
	$submitedForContentType = $fieldmapping[$proposal_submitted_for]['type'];
	if($submitedForContentType == 'organization'){
	  $submittedToCompany = $submitedForContentNode;
	}else{
	  $submittedCompanyNid = _get_company_nid_by_group_content($submitedForContentNode);
	  if($submittedCompanyNid){
		$submittedToCompany = node_load($submittedCompanyNid);
		//print "<pre>"; print_r($submittedToCompany); die;
	  }
	}
  }
}
//////////////// End Customer  Information ///////////////

//////////////// For company Information ///////////////
$CompanyNid  = _get_company_nid_by_group_content($node);
$node_by_com = node_load($CompanyNid);

//print "<pre>"; print_r($node_by_com); die;

$Comaddress_thoroughfare = $node_by_com->field_org_address['und'][0]['thoroughfare'];
$Comlocality = $node_by_com->field_org_address['und'][0]['locality'];
$Comadministrative_area = $node_by_com->field_org_address['und'][0]['administrative_area'];
$Compostal_code = $node_by_com->field_org_address['und'][0]['postal_code'];

$Comuserinfo = user_load($node_by_com->uid);

//print "<pre>"; print_r($comuserinfo); 

///////////////end company Information///////////////////
 

 ?>
<html>
<head>
<style>
@page {
        margin-top: 130px; 
}
body {
	margin: 0;
	padding: 0;
	font-size: 13px;
	line-height: 1.42857143;
	color: #333;
	font-family: "pdf_font";
}
a {
	color: #0f75bc;
	text-decoration: none;
}
.pull-left {
	float: left;
}
.pull-right {
	float: right;
}
.clearfix {
	float: left;
	width: 100%;
}
.text-right {
	text-align: right;
}
.left_m6_view {
	float: left;
	width: 200px;
	padding-right: 10px;
}
.right_m6_view {
	float: left;
	width: 470px;
}
.m6_own_con .m6_own {
	float: left;
	width: 230px;
	padding-right: 10px;
}
.m6_own_con .m6_scope {
	float: left;
	width: 100%;
	padding: 0 0 20px 0;
	margin: 0;
}
.m6_top_drywa_title {
	background: #265a7f;
	padding: 5px 10px;
	text-align: center;
}
.m6_top_drywa_title h3 {
	color: #e0e0e0;
	font-size: 20px;
	margin: 0;
}
.m6_top_drywall {
	background: #e1e1e1;
	padding: 4px 10px;
	border: 1px solid #cccccc;
}
.m6_top_drywall h6 {
	color: #333333;
	font-size: 14px;
	margin: 0px;
	text-transform: capitalize;
}
.m6_view_content {
	padding: 10px;
	border: 1px solid #CCC;
}
.m6_view_content table td h1 {
	color: #1f83bd;
	font-size:16px;
	font-weight: bold;
	margin: 0;
	padding: 0;
}
.m6_view_content table td span {
	color: #1f83bd;
}
.m6_view_content table td label {
	color: #333;
}
.m6_own_con h1 {
	color: #fff;
	font-size: 13px !important;
	font-weight: bold;
	background: #265a7f;
	margin: 0px;
	padding: 10px;
}
.m6_own_con .m6_border {
	border: 1px solid #CCC;
	padding: 10px;
}
.m6_own_con .m6_own_info {
	padding: 0;
	margin: 0;
	list-style: none;
}
.m6_own_con .m6_own_info li {
	margin-bottom: 10px;
}
.m6_own_con .m6_own_info li label {
	color: #333;
	font-size: 14px;
}
.m6_own_con .m6_own_info li span {
	color: #333;
	font-size: 14px;
	word-wrap: break-word;
}
.m6_own_con table {
	margin: 0px;
	width: 100%;
	border-collapse: collapse;
	border: 1px solid #bcbcbc;
}
.m6_own_con th {
	color: #333333;
	padding: 10px;
	font-size: 13px;
	font-weight: bold;
	background: #f3f3f3;
	border: 1px solid #bcbcbc;
	border-bottom: 2px solid #d5d5d5;
}
.m6_own_con td {
	color: #1f83bd;
	font-weight: bold;
	font-size: 12px;
	padding: 10px;
	border: 1px solid #d5d5d5;
}
.m6_down_sel {
	color: #fff;
	background: #265a7f;
	padding: 10px 20px;
}
</style>
</head>
<body>
<div class="m6_main_view clearfix">
 
  <div class="clearfix" style="">  <!--margin:0 0 0px 0;-->    
  <div class="left_m6_view">
      <div class="m6_top_drywa_title clearfix">
        <h3># <?php print($proposal_number); ?></h3>
      </div>
      <div class="m6_top_drywall clearfix">
        <h6><?php print $node->title; ?></h6>
      </div>
      <div class="m6_view_content clearfix">
        <table>
          <tr>
            <td colspan="2">
              <label><strong>Bid Amount:</strong></label>
              <span style="color: #1f83bd;font-size:18px;font-weight: bold;"><?php if(!empty($Proposal_bid_amount)){ print "$" . $Proposal_bid_amount; } ?></span>
            </td>
          </tr>
          <tr>
            <td width="150"><label><strong>Bidder Diversity Type:</strong></label></td>
            <td><?php 
		       $diversityImages = get_diversity_image_by_comapny_nid($CompanyNid);
			   echo $diversityImages;
			 ?></td>
          <tr>
            <td colspan="2"><div class="clearfix">
                <?php
				$src_div_company_vid = array();														   
				if(is_numeric($CompanyNid)){														   
				$query_diversity_info = db_select('node', 'n');															
				$query_diversity_info->join('field_data_field_diversity_credentials','dc','dc.field_diversity_credentials_target_id=n.nid');
				$query_diversity_info->fields('n',array('title'));
				$query_diversity_info->condition('dc.entity_id',$CompanyNid,'=');	
				$src_div_company_vid = $query_diversity_info->execute()->fetchAll();															
				}
				for($m = 0; $m < count($src_div_company_vid); $m++) {
						  $bidder_type = '<span style="color:#1f83bd;">' . $src_div_company_vid[$m]->title . '</span>';
						  echo $bidder_type;
				}
               ?>
              </div></td>
          </tr>
          <tr>
            <td colspan="2"><label><strong>Bid Type:</strong></label>
              <span style="color:#1f83bd;">
              <?php  if(!empty($Proposoal_bid_types)){ echo "(".$Proposoal_bid_types.")"; }?>
              </span></td>
          </tr>
          <tr>
            <td colspan="2"><label><strong>Submitted For:</strong></label>
              <span style="color:#1f83bd;"><?php echo $proposal_submitted_for; ?></span></td>
          </tr>
          <?php if($submitedForContentType == 'rfp'){ ?>
          <tr>
            <td colspan="2"><label><strong>RFP:</strong></label>
              <span style="color:#1f83bd;"> <?php echo $submitedForContentNode->title; ?> </span></td>
          </tr>
          <?php } ?>
          <?php if($submitedForContentType == 'project'){ ?>
          <tr>
            <td colspan="2"><label><strong>Project:</strong></label>
              <span style="color:#1f83bd;"> <?php echo $submitedForContentNode->title; ?> </span></td>
          </tr>
          <?php } ?>
          <?php if($submitedForContentType == 'organization'){ ?>
          <tr>
            <td colspan="2"><label><strong>Company:</strong></label>
              <span style="color:#1f83bd;"> <?php echo $submitedForContentNode->title; ?> </span></td>
          </tr>
          <?php } ?>
          <tr>
            <td><label><strong>Job Location:</strong></label>
              <div id="view_map"> <span id="addr-pro"></span>
                <?php 
			  
			  if(!empty($propos_add_althoroughfare)){
			  $proposaddres1 = $propos_add_althoroughfare;
			  }
			  $proposaddres2 = $propos_add_locality.' '.$propos_add_adminis.' '.$propos_add_postalcode;
			
			 ?>
                <span style="color:#1f83bd;" id="addr-pro-state"><?php echo $proposaddres1; ?></span> <span style="color:#1f83bd;" id="addr-pro-country"><?php echo $proposaddres2; ?></span> </div></td>
          </tr>
        </table>
      </div>
      <div class="m6_view_map clearfix" id="map_dis"> </div>
    </div>
    <div class="right_m6_view">
      <div class="clearfix m6_own_con clearfix">
        <div class="clearfix">
          <div class="m6_own">
            <?php
		    $submittedUserInfo = user_load($submittedToCompany->uid);
			 //print "<pre>"; print_r($submittedUserInfo); die;
		 ?>
            <div class="clearfix">
              <h1>Customer Company</h1>
            </div>
            <div class="m6_border">
              <ul class="m6_own_info clearfix">
                <li class="clearfix">&nbsp;</li>
                <li class="clearfix">
                  <label><strong>Name:</strong></label>
                  <span>
                  <?php if(!empty($submittedToCompany->title)){echo $submittedToCompany->title; }?>
                  </span> </li>
                <li class="clearfix">
                  <label><strong>Address:</strong></label>
                  <?php
			 if(!empty($submittedToCompany->field_org_address['und'][0])){
			  $address1 = $submittedToCompany->field_org_address['und'][0]['thoroughfare'];
			 }
			?>
                  <span><?php echo $address1; ?></span></li>
                <li class="clearfix">
                  <label><strong>City, State, Zip:</strong></label>
                  <?php
			  $sub_locality = $submittedToCompany->field_org_address['und'][0]['locality'];
			  $sub_administrative_area = $submittedToCompany->field_org_address['und'][0]['administrative_area'];
			  $sub_postal_code =$submittedToCompany->field_org_address['und'][0]['postal_code'];
			 
			  $address2 = $sub_locality.' '.$sub_administrative_area.' '.$sub_postal_code;
			?>
                  <span><?php echo  $address2; ?></span></li>
                <li class="clearfix">
                  <label><strong>Phone:</strong></label>
                  <span>
                  <?php if(!empty($submittedUserInfo->field_phone['und'][0])){echo  $submittedUserInfo->field_phone['und'][0]['value'];} ?>
                  </span></li>
                <li class="clearfix">
                  <label><strong>Email:</strong></label>
                  <span style="word-break:break-all; font-size:12px; word-wrap:break-word;"><?php echo $submittedUserInfo->mail; ?></span></li>
                <!--<?php //if($submitedForContentType == 'rfp'){ ?>
              <li class="clearfix">
                <label><strong>RFP</strong></label>
                <span> <?php //echo $submitedForContentNode->title; ?> </span> </li>
               <?php //} ?>
               <?php //if($submitedForContentType == 'project'){ ?>
              <li class="clearfix">
                <label><strong>Project</strong></label>
                <span>
                <?php //echo $submitedForContentNode->title; ?>
                </span> </li>
                <?php //} ?>
              <?php //if($submitedForContentType == 'organization'){ ?>
              <li class="clearfix">
                <label><strong>Company</strong></label>
                <span>
                <?php //echo $submitedForContentNode->title; ?>
                </span> </li>
               <?php //} ?>-->
              </ul>
            </div>
          </div>
          <div class="m6_own" style="margin-right:0; padding-right:0;">
            <div class="clearfix">
              <h1>Submitting Company</h1>
            </div>
            <div class="m6_border">
              <ul class="m6_own_info clearfix">
                <li class="clearfix">&nbsp;</li>
                <li class="clearfix">
                  <label><strong>Name:</strong></label>
                  <span> <?php echo $node_by_com->title; ?> </span></li>
                <li class="clearfix">
                  <label><strong>Address:</strong></label>
                  <span>
                  <?php if(!empty($Comaddress_thoroughfare)){  echo $Comaddress_thoroughfare; } ?>
                  </span></li>
                <li class="clearfix">
                  <label><strong>City, State Zip:</strong></label>
                  <span><?php echo $Comlocality.' '.$Comadministrative_area.' '.$Compostal_code; ?></span></li>
                <li class="clearfix">
                  <label><strong>Phone:</strong></label>
                  <span><?php echo $Comuserinfo->field_phone['und'][0]['value']; ?></span></li>
                <li class="clearfix">
                  <label><strong>Email:</strong></label>
                  <span style="word-break:break-all; font-size:12px; word-wrap:break-word;"><?php echo $Comuserinfo->mail; ?></span></li>
              </ul>
            </div>
          </div>
        </div>
        <div class="clearfix"><br>
        </div>
        <div class="m6_scope clearfix">
          <div class="clearfix">
            <h1>Description</h1>
          </div>
          <div class="doc_det m6_prop_tab clearfix">
            <div class="m6_border">
              <ul class="m6_own_info">
                <li><?php echo nl2br($scope_of_work); ?></li>
              </ul>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="m6_own_con">
    <div class="m6_scope clearfix">
      <div class="clearfix">
        <h1>Proposal Documents</h1>
      </div>
      <div class="doc_det m6_prop_tab clearfix">
        <div id="page-wrap1_viewprop">
          <table cellpadding="0" cellspacing="0" border="0">
            <!--<thead>
                <tr>
                  <th>Select</th>
                  <th>Document Name</th>
                  <th style="text-align:center;">Type</th>
                  <th>Uploaded Date</th>
                </tr>
              </thead>-->
            <tbody>
              <!--<tr>
                  <td colspan="4" style="text-align:center;">No Proposal Document</td>
                </tr>-->
              <?php
					$time = $node->field_proposal_document_picture['und'];
					$count_docu = count($time);
					if($count_docu == '0') {
						echo '<tr>
								<td colspan="4" style="text-align:center;">No Proposal Document</td>
								</tr>';
					} else {
						
						echo '<thead>
                				<tr>
                  				<th>Select</th>
                  				<th>Document Name</th>
                  				<th style="text-align:center;">Type</th>
                 				<th>Uploaded Date</th>
                				</tr>
              				</thead>';
						$file_data = '';
							for ($c = 0; $c < count($time); $c++) { //pre($time,1);
								$det_time = $time[$c]['timestamp'];
								$det_name = $time[$c]['filename'];
								$det_mine = $time[$c]['filemime'];
								$det_fid = $time[$c]['fid'];

								switch($det_mine){
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
							<td>
							<input name="chk[]" class="down_valu" value="' . $det_name . '" type="checkbox" id="download_' . $c . '" data="'.$det_fid.'"/>
							</td>
							<td><a class="down_url">' . $det_name . '</a></td>
							<td align="center"><img src ="/modules/file/icons/' . $img_src . '.png"></td>
							<td><span>' . date('m/d/Y g:i A', $det_time) . '</span></td>            
						</tr>';
									 //$file_data.= "'" . $det_name . "',";

									//echo $det_mine;
								    }
								       //$file_data = substr_replace($file_data, "", -1);
							    }
							?>
            </tbody>
          </table>
        </div>
      </div>
    </div>
    <div class="m6_scope clearfix">
      <div class="clearfix">
        <h1>Proposal Communications</h1>
      </div>
      <div class="clearfix">
        <table>
          <!--<thead>
            <tr>
              <th>Id</th>
              <th>Status</th>
              <th>Subject</th>
              <th>From</th>
              <th>Message Date</th>
            </tr>
          </thead>-->
          <tbody>
            <?php
                        //read msg starts
						$query_status1 = db_select('read_unread_message', 'tes')
								->condition('tes.user_id', $logged_user, '=')
								->fields('tes', array('proposal_id', 'comment_id', 'user_id', 'staus'));
						$result_status1 = $query_status1->execute();
						$i = 0;
						foreach ($result_status1 as $item_read) {
							$read_cmd_id[$i] = $item_read->comment_id;
							$i++;
						}
						//echo '<pre>'; print_r($read_cmd_id); echo '</pre>';
						//read msg ends


						$query_comment = db_select('comment', 'com')
										->condition('com.nid', $nid, '=')
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

						$cmb_in = array_intersect($read_cmd_id_st, $read_cmd_id);
						$sub2 = count($cmb_in);
						$unread_msg = $sub1 - $sub2;
						//echo 'Unread msg = '.$unread_msg;


				 if (count($result_comment_count) == 0) {  
						  echo '<tr>
								<td style="text-align:center;" colspan="5">No Proposal Communication</td>
								</tr>';
					 } else { 
						
					echo "<thead>
            				<tr>
              				<th>Id</th>
              				<th>Status</th>
              				<th>Subject</th>
              				<th>From</th>
              				<th>Message Date</th>
            				</tr>
          				 </thead>";
						
							$i = 1;
				  	foreach ($result_comment as $item_comment) {
					  	$query_commenter_lname = db_select('field_revision_field_last_name', 'lname')
							  					->condition('lname.entity_id', $item_comment->uid, '=')
							  					->fields('lname', array('field_last_name_value'));
					  $result_commenter_lname = $query_commenter_lname->execute();


					  foreach ($result_commenter_lname as $item_commenter_lname) {
						  $commenter_lname = $item_commenter_lname->field_last_name_value;
						  $query_commenter_fname = db_select('field_revision_field_first_name', 'fname')
								  ->condition('fname.entity_id', $item_comment->uid, '=')
								  ->fields('fname', array('field_first_name_value'));
						  $result_commenter_fname = $query_commenter_fname->execute();


						  foreach ($result_commenter_fname as $item_commenter_fname) {
							  $commenter_fname = $item_commenter_fname->field_first_name_value;
							  $com_id = $item_comment->cid;
							  $com_msg = $item_comment->subject;
							  $com_name = $commenter_fname . " " . $commenter_lname;
							  $com_date = date('m/d/Y g:i A', $item_comment->created);
							  $comts_id = $i . '-' . $proposal_number . '-' . date('Y', $item_comment->created);
							  $user_id = $user->uid;

							  $show_msg = "'" . $com_id . "','" . $proposal_number . "','" . $user_id . "'";
							  ?>
            <tr>
              <td><span><?php echo $comts_id; ?></span></td>
              <td><span>
                <?php
						if (in_array($com_id, $read_cmd_id)) {
								echo "read";
						} else {
								 echo 'unread';
						}
						?>
                </span></td>
              <td><span><?php echo $com_msg; ?></span></td>
              <td><span><?php echo $com_name; ?></span></td>
              <td><span><?php echo $com_date; ?></span></td>
            </tr>
            <?php }
					  } $i++;
				  }
			}  ?>
          </tbody>
        </table>
      </div>
    </div>
  </div>
</div>
</body>
</html>