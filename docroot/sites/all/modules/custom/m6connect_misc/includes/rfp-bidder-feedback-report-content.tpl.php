<?php


  global $base_url, $theme_path;
  $date = date('m/d/Y',time());
  $gid = _get_company_nid_by_group_content($node); 
  $Sendercompany = node_load($gid);	
  $SendercompanyName = $Sendercompany->title;
  /*$cimagepath = '';
  $cimgpath = (isset($Sendercompany->field_logo['und']) && !empty($Sendercompany->field_logo['und'][0]['uri'])) ? $Sendercompany->field_logo['und'][0]['uri'] : 0; 
  if ($cimgpath) {
   
	
	$fids = $Sendercompany->field_logo['und'][0]['fid']; 	
    $result = file_load_multiple(array($fids)); 
    if (is_array($result) && !empty($result)) {
      foreach ($result as $delta => $fileObj) {
        $filname = $fileObj->filename; 
        $objFile = file_copy($fileObj, $destination = 'public://' . $filname, $replace = FILE_EXISTS_RENAME);
        if ($objFile) {
          $newimgobj = (array) $objFile;
		  $newcimgpath = $newimgobj['uri'];
		  $cimagepath = image_style_url('thumbnail', $newcimgpath);
		  $objFile->status = 0;
		  file_save($objFile);
        }
      }
    }
	
  }*/ 
  
  $RfpName = $node->title;
  $AuthorUid = $node->uid;
  $Author = user_load($AuthorUid);
  $ProjectManager = _get_user_full_name($AuthorUid);
  $Phone = (isset($Author->field_phone['und']) && isset($Author->field_phone['und'][0]['value']) && !empty($Author->field_phone['und'][0]['value']))?$Author->field_phone['und'][0]['value']:'';
  $discription = (isset($node->field_rfp_description['und']) && isset($node->field_rfp_description['und'][0]['value']) && !empty($node->field_rfp_description['und'][0]['value']))?$node->field_rfp_description['und'][0]['value']:'';
  $Public = (isset($node->field_public['und']) && isset($node->field_public['und'][0]['value']) && !empty($node->field_public['und'][0]['value']))?$node->field_rfp_description['und'][0]['value']:'';
  $RfpType = ($Public == 1)?'Public':'Private';
  $InvitedBidders = get_invited_companies_or_individuals_list_for_bfeedback_report($node);
  $InvitedBidderslist = implode(', ',$InvitedBidders);
  
 //$userDetailsinfo = get_rfp_bid_feed_back_user_detail($AuthorUid);
  
   //print "<pre>"; print_r($InvitedBidderslist);
  
?>
<style>
* {
	box-sizing: border-box;
	-webkit-box-sizing: border-box;
	-moz-box-sizing: border-box;
	-o-box-sizing: border-box;
	-ms-box-sizing: border-box;
}
table {
	width: 100%;
}
td, th, .padding {
	padding: 5px;
}
th {
	text-align: left;
}
table, tr, td, th {
	border-collapse: collapse;
	word-break: break-all;
}
.full {
	float: left;
	width: 100%;
}
.notification-count {
	float: right;
	width: 22px;
	height: 22px;
	color: #FFF;
	text-align: center;
	font-size: 10px;
	line-height: 22px;
	background-color: brown;
	vertical-align: top;
	border: none;
}
.request-bid-intent-image {
	float: right;
	width: 126px;
	height: 22px;
	color: #FFF;
	text-align: center;
	font-size: 13px;
	line-height: 22px;
	background: #419641;
}
img {
	max-width: 100%;
}
.m6_view_content th {
	color: #000;
	padding: 5px;
	font-size: 12px;
	border-bottom: 1px solid #CCC;
}
</style>
<div style="width:660px; float:left;"> 
  <!--<table class="full" style="border:none; margin-bottom:20px;">
    <tr>
      <td style="width:25%;"><?php //if(!empty($cimagepath)){ ?>
        <img src="<?php //echo $cimagepath;?>" alt="company logo"> <strong>
        <?php //} else { //echo $SendercompanyName;	} ?>
        </strong></td>
      <td style="width:50%; vertical-align:top; text-align:center;"><h2 style="margin:0 0 10px 0;">Bidder Feedback Report</h2>
        <br>
        <strong><?php //echo $RfpName;?></strong></td>
      <td style="width:25%;">&nbsp;</td>
    </tr>
  </table>--> 
  <!--<table class="full" style="margin-bottom:20px;">
    <?php /*?><?php 
	  if (isset($node->field_project['und'][0]) && !empty($node->field_project['und'][0]['target_id'])) {
	    $Related_Proj_Nid = $node->field_project['und'][0]['target_id'];
        $Related_Proj_Node = node_load($Related_Proj_Nid); 
	    $Related_Proj_Name = $Related_Proj_Node->title;
	?><?php */?>
    <tr>
      <th style="text-align:left; vertical-align:top; width:15%;">Project:</th>
      <td style="vertical-align:top;"><?php //echo $Related_Proj_Name;?></td>
    </tr>
    <?php /*?><?php } ?><?php */?>
    <tr>
      <th style="text-align:left; vertical-align:top; width:15%;">Report Date:</th>
      <td style="vertical-align:top;"><?php //echo $date;?></td>
    </tr>
  </table>-->
  <table style="border-bottom:1px solid #000; margin:0px; width:660px; float:left;">
    <tr>
      <th>RFP:</th>
      <td><?php echo $RfpName;?></td>
      <th>Project Manager:</th>
      <td><?php echo $ProjectManager;?></td>
      <th>Phone:</th>
      <td><?php
	  
	  if(!empty($Phone)){
	   $PhoneNumber = get_international_formatPhoneNumber($Phone);
	   echo $PhoneNumber;
	  }
	   ?>
       </td>
    </tr>
  </table>
  <table style="border-bottom:1px solid #000; margin:0px; width:660px; float:left;">
    <tr>
      <th style="vertical-align:top; width:25%;">RFP Description:</th>
      <td style="vertical-align:top;"><?php echo $discription;?></td>
    </tr>
  </table>
  <table style="border-bottom:1px solid #000; margin:0px; width:660px; float:left;">
    <tr>
      <th style="vertical-align:top; width:25%;">RFP Type:</th>
      <td style="vertical-align:top;"><?php echo $RfpType;?></td>
    </tr>
    <tr>
      <th style="vertical-align:top; width:25%;">Invited Bidders: </th>
      <td style="vertical-align:top;"><?php echo $InvitedBidderslist;?></td>
    </tr>
  </table>
  <div style="width:660px; float:left;">
    <div class="full" style="margin:0 0 10px 0;"><strong>Bid Packages:</strong></div>
    <?php 
	  $bid_packages = get_bidder_feedback_content_data($node->nid);
	  
	  $BidPackagesexist = (!empty($bid_packages))?1:0;
	  $msgpackageStatus = ($BidPackagesexist)?2:0;
	  $info = get_bidder_feedback_table_data_for_report($node->nid,$msgpackageStatus);
	  if(!empty($bid_packages)){
		foreach($bid_packages as $package_id => $package_name){	
		  $rows = (isset($info[$package_id]['rows']))?$info[$package_id]['rows']:array(); 
		  if(count($rows)>0){
	?>
    <div style="margin:0 0 10px 0; width:660px; float:left;">
      <div style="margin:0 0 10px 0; background:#EEE; padding:10px; width:640px; float:left;">
        <div style="float:left; width:50%;"><strong><?php echo $package_name;?></strong></div>
      </div>
      <div style="width:660px; float:left;">
        <?php
             $i = 0;
             foreach($rows as $k=> $data) {
        ?>
        <div class="<?php echo $oddevencla;?>" style="border-bottom:1px solid #000; width:660px; float:left;">
          <table align="left" style="width:660px; float:left;">
            <tr>
              <td width="280" style="vertical-align:top; word-break:break-all;"><?php 
                   $defaultcompanyLogo = '';
				   if($data['company_type'] == 'company'){
					 $defaultcompanyLogo = '<img src="'.$base_url.'/sites/all/themes/m6connect/images/default_company_profile.jpg" width="40" height="40" style="display:inline-block; vertical-align:top;" />';  
				   }
                  ?>
                <?php if(!empty($data['companyLogo'])){ ?>
                <img src="<?php echo $data['companyLogo'] ;?>" alt="logo" width="40" height="40" style="display:inline-block; vertical-align:top;" />
                <?php }else{ ?>
                <?php echo  $defaultcompanyLogo; ?>
                <?php } ?>
                <span style="display:inline-block; vertical-align:top;">
                <?php 
                     if($data['company_type'] == 'company'){
                      if(!empty($data['companyName'])) { echo $data['companyName']; } 
                     }
                    ?>
                </span>
              </td>
              <td width="50" style="vertical-align:top;"><?php if(!empty($data['companyImages'])){ ?>
                <?php echo $data['companyImages'] ;?>
                <?php } ?></td>
              <td width="300" style="vertical-align:top; word-break:break-all;"><?php
				  $src_div_company_vid = array();														   
				  if(is_numeric($data['companyNid'])){														   
				  $query_diversity_info = db_select('node', 'n');															
				  $query_diversity_info->join('field_data_field_diversity_credentials','dc','dc.field_diversity_credentials_target_id=n.nid');
				  $query_diversity_info->fields('n',array('title'));
				  $query_diversity_info->condition('dc.entity_id',$data['companyNid'],'=');	
				  $src_div_company_vid = $query_diversity_info->execute()->fetchAll();															
				  }
				  for($m = 0; $m < count($src_div_company_vid); $m++) {
					  $bidder_type = $src_div_company_vid[$m]->title;
					  if($bidder_type){
						echo '<div>' . $bidder_type . '</div>';
					  }
				  }
                ?>
              </td>
            </tr>
          </table>
          <table align="left" style="width:660px; float:left;">
            <thead>
              <tr>
                <th>&nbsp;</th>
                <th>&nbsp;</th>
                <th>&nbsp;</th>
                <th align="right">Bidding</th>
                <th align="right">Not Bidding</th>
                <th align="right">Not Sure Yet</th>
              </tr>
            </thead>
            <tbody>
              <?php 
			  //print "<pre>"; print_r($data['allUserDetailInvitee']); 
			  foreach($data['allUserDetailInvitee'] as $userDetailsinfo){ ?>
              <?php 
                 $Inviteeuserphone = $userDetailsinfo['phone'];
				 $InviteePhoneNumber = '';
				 if(!empty($Inviteeuserphone)){
	  			 $InviteePhoneNumber = get_international_formatPhoneNumber($Inviteeuserphone);
	  			 }
                 $Inviteeusername = $userDetailsinfo['name'];
                 $Inviteeusermail = $userDetailsinfo['mail'];
                 $Inviteeuseruid = $userDetailsinfo['uid'];
                 $Inviteeuserprofileuri = $userDetailsinfo['profile_uri'];
				 $UserProfilePhoto = '<img style="width:40px;" src="'.$base_url.'/sites/all/themes/m6connect/images/default_userpdf.png" />';	   
				 if(!empty($Inviteeuserprofileuri)){	      
				   $UserProfilePhoto = theme('image_style', array('style_name' => 'pic_40x40', 'path' => $Inviteeuserprofileuri, 'getsize' => TRUE));
				 }
					?>
              <tr>
                <td width="50" style="width:50px; vertical-align:top;"><?php echo $UserProfilePhoto; ?></td>
                <td width="180" style="width:180px; vertical-align:top; word-break:break-all;">
                  <div class="Invitee_username" style="word-break:break-all;">
				  <?php  
				    $userpartsname = str_split($Inviteeusername, 20);
					print implode('<br/>',$userpartsname);
				  ?></div>
                  <div class="Inviteeuser_mail" style="word-break:break-all;">
				  <?php 
					$userpartsmail = str_split($Inviteeusermail, 20);
					print implode('<br/>',$userpartsmail);
				    ?>
                  </div>
                </td>
                <td width="100" style="width:100px; vertical-align:top; word-break:break-all;"><?php echo $InviteePhoneNumber; ?></td>
                <td width="90" style="width:90px; vertical-align:top; text-align:right"><label>
                    <input type="checkbox" <?php echo $data['Checked'][1]?>>
                  </label></td>
                <td width="90" style="width:90px; vertical-align:top; text-align:right"><label>
                    <input type="checkbox" <?php echo $data['Checked'][0]?>>
                  </label></td>
                <td width="90" style="width:90px; vertical-align:top; text-align:right"><label>
                    <input type="checkbox" <?php echo $data['Checked'][2]?>>
                  </label></td>
              </tr>
              <?php  } ?>
            </tbody>
          </table>
          <div style="width:660px; float:left;">
            <div style="width:300px; float:left; padding:5px 0;">&nbsp;</div>
            <div style="width:360px; float:left; padding:5px 0;">
              <?php if(!empty($data['request_bid_intent_count']) && $data['request_bid_intent_count']>0){ ?>
              <div class="full" style="height:22px; padding:5px 0;">
                <div class="notification-count"><?php echo $data['request_bid_intent_count'];?></div>
                <div class="request-bid-intent-image">Request Bid Intent</div>
              </div>
              <?php } ?>
              <?php if(is_array($data['notes']) && count($data['notes'])>0) { 
                  $j = 1;
                  foreach($data['notes'] as $n=>$notes) { ?>
              <div class="full" style="border-bottom:1px solid #CCC; padding:5px 0;"><?php echo $notes;?></div>
              <?php if($j == 1) {?>
              <?php } else {?>
              <div class="full" style="border-bottom:1px solid #CCC; padding:5px 0;"><?php echo $notes;?></div>
              <?php } $j++; } } ?>
            </div>
          </div>
        </div>
        <?php
			$i++;
		  }
		?>
      </div>
    </div>
    <?php
		  }
		}
	  }
	  ?>
  </div>
  
  <!------------- start For Proposal Listing here ---->
  
  <div class="m6_view_content" style="width:660px; float:left;">
    <table class="full">
      <thead>
        <tr>
          <th colspan="3" align="center"><h2 style="margin:0;"><?php echo $RfpName; ?></h2></th>
        </tr>
        <tr class="cust-rfp-clearification-heading">
          <th>Proposal Name</th>
          <th>Date Submitted</th>
          <th>Bid Amount</th>
        </tr>
      </thead>
      <tbody>
        <?php 
	  if($node->nid && is_numeric($node->nid)){
	       $received_proposals = get_received_proposals_content_alldata($node->nid);
	   }
	   foreach($received_proposals as $receivedout){  ?>
        <?php 
	       $proposalnid = $receivedout->nid;
           $proposalNode = node_load($proposalnid);
		   //$proposal_bid_amount = $proposalNode->field_proposal_bid_amount['und'][0]['value'];
		   //$proposoal_bid_types= $proposalNode->field_proposoal_bid_types['und'][0]['value'];
		   
		    $proposal_bid_amount = $receivedout->field_proposal_bid_amount_value;
		    $proposoal_bid_types= $receivedout->field_proposoal_bid_types_value;
		   
		   $CompanyNid = $proposalNode->og_group_ref['und'][0]['target_id'];
		   $CompanyNode = node_load($CompanyNid);
		 ?>
        <tr class="cus-rfp-clearification">
          <td><?php echo $receivedout->title; ?></td>
          <td><?php echo date('m/d/Y H:i A', $receivedout->created); ?></td>
          <td><?php echo "$".$proposal_bid_amount; ?></td>
        </tr>
        <?php } ?>
      </tbody>
    </table>
  </div>
  
  <!------------- start For Proposal Listing here ----> 
  
</div>
