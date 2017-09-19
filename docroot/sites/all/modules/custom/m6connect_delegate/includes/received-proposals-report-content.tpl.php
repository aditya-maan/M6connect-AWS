<?php

global $user;
$nid= $node->nid;
$logged_user = $user->uid;

 //$node1= node_load($nid);
  //print "<pre>"; print_r($node1); die;

?>

<html>
<head>
<style>
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

.m6_view_con table td h1 {
	color: #1f83bd;
	font-size:16px;
	font-weight: bold;
	margin: 0;
	padding: 0;
}
.m6_view_con table td span {
	color: #1f83bd;
}
.m6_view_con table td label {
	color: #333;
}
.m6_view_con h1 {
	color: #fff;
	font-size: 13px !important;
	font-weight: bold;
	background: #265a7f;
	margin: 0px;
	padding: 10px;
}

.m6_view_con table {
	margin: 0px;
	width: 100%;
	border-collapse: collapse;
	border: 1px solid #bcbcbc;
}
.m6_view_con th {
	color: #000;
	padding: 5px;
	font-size: 12px;
	background:#EAEAEA;
	border:1px solid #CCC;
}
.m6_view_con td {
	color:#0f75bc;
	font-size: 12px;
	padding: 5px;
    background: #F2F2F2;
	border:1px solid #CCC;
}
</style>
</head>
<body>
  
  <div class="m6_view_content clearfix">
  
   <div style="margin-bottom:7px;">
         <?php
		 
           if(!empty($node->field_rfp_logo['und'][0]['uri'])){	      
			$companyLogo = (isset($node->field_rfp_logo['und'][0]['uri'])) ? theme('image_style', array('style_name' => 'thumbnail', 'path' => $node->field_rfp_logo['und'][0]['uri'], 'getsize' => TRUE)) : '';  
			}else{
	         $companyLogo= '<img style="width:100px;" src="'.$base_url.'/sites/all/themes/m6connect/images/default_company_profile.jpg"/>';  
        	} 
			
			?>
     <table>
      <tr>
        <td style="width:230px;"><?php echo $companyLogo; ?></td>
        <td style="width:450px; vertical-align:top;"><h1 style="text-align:center">
            <?php if(!empty($node->title)){ echo $node->title; }?>
          </h1>
         </td>
      </tr>
      </tr>
         <tr>
		    <td colspan="2" style="width:230px; vertical-align:bottom;"><h2 style="margin:0;"> <?php if(!empty($node->title)){ echo $node->title; }?></h2></td>
         </tr>
         
    </table>
    </div> 
   <div class="m6_view_con"> 
<table>
  <thead>
    <tr class="cust-rfp-clearification-heading">
      <th>Company</th>
      <th>Proposal Name</th>
      <th>Date Submitted</th>
      <th>Bid Amount</th>
      <th>Bid Type</th>
      <th>Bidder Diversity Type</th>
      <th>Awarded</th>
    </tr>
  </thead>
  <tbody>
    <?php 
	
	
	  if($node->nid && is_numeric($node->nid)){
	       $received_proposals = get_received_proposals_content_alldata($node->nid);
		   
		  //print "<pre>";  print_r($received_proposals); die;
	   }
	   foreach($received_proposals as $receivedout){  ?>
       
        <?php 
	       $proposalnid = $receivedout->nid;
           $proposalNode = node_load($proposalnid);
		   $proposal_bid_amount = $proposalNode->field_proposal_bid_amount['und'][0]['value'];
		   $proposoal_bid_types= $proposalNode->field_proposoal_bid_types['und'][0]['value'];
		   
		   $CompanyNid = $proposalNode->og_group_ref['und'][0]['target_id'];
		   $CompanyNode = node_load($CompanyNid);
		   
		  //print "<pre>"; print_r($cmpyUser); die;
			
		
		
		 ?>
              <tr class="cus-rfp-clearification">
                <td><?php echo $CompanyNode->title; ?></td>
                <td><?php echo $receivedout->title; ?></td>
                <td><?php echo date('m/d/Y H:i A', $receivedout->created); ?></td>
                <td><?php echo "$".$proposal_bid_amount; ?></td>
                <td><?php echo $proposoal_bid_types ; ?></td>
                <td>
                 <?php
				   $src_div_company_vid = array();														   
				if(is_numeric($CompanyNid)){														   
				$query_diversity_info = db_select('node', 'n');															
				$query_diversity_info->join('field_data_field_diversity_credentials','dc','dc.field_diversity_credentials_target_id=n.nid');
				$query_diversity_info->fields('n',array('title'));
				$query_diversity_info->condition('dc.entity_id', $CompanyNid,'=');	
				$src_div_company_vid = $query_diversity_info->execute()->fetchAll();															
				}
				for($m = 0; $m < count($src_div_company_vid); $m++) {
						  $bidder_type = '<span style="color:#1f83bd;">' . $src_div_company_vid[$m]->title . '</span>';
						   echo $bidder_type;
				}
                ?>
                </td>
                <td>
                 <?php
				//$data->custom_rewarded = 0;
				if( db_table_exists($table='proposal_award')){
  				$awared = db_select('proposal_award', 'pa')->fields('pa', array('node_id'))->condition('pa.node_id',$receivedout->nid, '=')->condition('pa.status',1, '=')->execute()->fetchCol();
				
  				   if(!empty($awared) && in_array($receivedout->nid, $awared)){
					   
  					 //$data->custom_rewarded =1;
 					 print 'Awarded';
  
					}else{
  					 	print '';
					}
				}  
				?>
               </td>
              </tr>
              
     <?php } ?>
  </tbody>
</table>
  </div>
</div>
</body>
</html>
