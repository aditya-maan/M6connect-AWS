<?php
$location = '';
global $user, $company;
$message_type='';
$message_body = '';
$message_no = '';
$rows = array();
$message_documents = '';
set_claification_read_flag_for_company_user($clarificationNode);  

 
/*$cmpNid = _get_user_company_nid($clarificationNode->uid);
$rfpCompanyNid = _get_user_company_nid($rfpNode->uid);;
$rfpownerCompany = in_array($user->uid,_get_current_company_users($rfpNode->uid));
$cmpcall = in_array($user->uid,_get_current_company_users($clarificationNode->uid));*/

$cmpNid = $company->nid;
$currentCompanyUsers =  _get_company_users_by_group_company($company);
$rfpownerCompany = in_array($user->uid,$currentCompanyUsers);
$cmpcall = in_array($user->uid,_get_company_users_by_group_company($clarificationNode));



$cmpQuery = '';
if($cmpNid && !$cmpcall){
  $cmpQuery = $cmpNid; 	
}
if($rfpCompanyNid && !$rfpownerCompany){
  $cmpQuery = $rfpCompanyNid; 		
}
$cmpNode = node_load($cmpNid);

$cmpuser = user_load($cmpNode->uid);
$fullName = _get_user_full_name($clarificationNode->uid);
$location = get_company_location_by_company_nid($cmpNid);
$location = ($location)?$location.' at ':$location;
if(isset($clarificationNode->field_message_type['und']) && !empty($clarificationNode->field_message_type['und'][0]['value'])){
  $message_type =  $clarificationNode->field_message_type['und'][0]['value'];
}
$sentMessageType = $message_type;
if(!$rfpownerCompany){
   $sentMessageType= 'private'; 	
}

if(isset($clarificationNode->field_message_no['und']) && !empty($clarificationNode->field_message_no['und'][0]['value'])){
  //$message_no =  $clarificationNode->field_message_no['und'][0]['value'];	
}
if(isset($clarificationNode->field_clarification_id['und']) && !empty($clarificationNode->field_clarification_id['und'][0]['value'])){
  $year = date('Y', $clarificationNode->created);
  $rfpId = '';
  if(isset($rfpNode->field_reference_number['und']) && !empty($rfpNode->field_reference_number['und'][0]['value'])){
	$rfpId = $rfpNode->field_reference_number['und'][0]['value'];
  }
  $clarificationId = sprintf("%02d",$clarificationNode->field_clarification_id['und'][0]['value']);;
  //$message_no = "$year-$rfpId-$clarificationId";
  $message_no = "$rfpId-$clarificationId";
}

if(isset($clarificationNode->body['und']) && !empty($clarificationNode->body['und'][0]['value'])){
  $message_body =  $clarificationNode->body['und'][0]['value'];	
}

/*$header = array('Document Name', 'Type', 'Uploaded Date');
if(isset($clarificationNode->field_clarification_attachment['und']) && !empty($clarificationNode->field_clarification_attachment['und'])){
  foreach($clarificationNode->field_clarification_attachment['und'] as $delta => $fileObj){
	 $info = pathinfo($fileObj['filename']);
	 $filePath = l($info['filename'],'download-file/'.$fileObj['fid']);  //array('attributes'=> array('target'=>'_blank'))
	 $rows[$fileObj['fid']] = array($filePath, theme_file_icon(array('file'=>(object)$fileObj,'icon_directory'=> NULL)),date('m/d/Y H:i A',$fileObj['timestamp'])); 
  }
}
$message_documents = theme('table', array('header'=>$header,'rows'=>$rows,'attributes'=>array('class'=> array('calrification-document-table','table','table-bordered'), 'id'=> 'calrification-document-table'),'empty'=>'no document uploaded',));*/

$message_documents = drupal_render(drupal_get_form('get_clarification_document_download',$clarificationNode));

$rfpNodeTitle = $rfpNode->title;
if(strlen($rfpNodeTitle)>18){
  $rfpNodeTitle = substr($rfpNodeTitle, 0, 18);	
  $rfpNodeTitle .= '...';	
}

$message_type_edit = $message_type;
if($message_type=='public'){
  $message_type_edit = 'All Invited Users';	
}

?>

<div class="clarification-msg-main">
	<div class="clarification-header">
		<h3>(<span class="clari-msg-type msg-type-<?php print $message_type; ?>"><?php print ucfirst($message_type_edit); ?></span>) Clarification For RFP <?php print $rfpNodeTitle; ?></h3>
	</div>
    <div class="clari-msg-wrapper">
        <div class="clari-msg-copy-action pull-right">
          <?php	
		    if($rfpNode->uid == $user->uid)	{
			  /*print l('<input type="button" value="Forward" class="btn btn-primary form-submit">',
					  'send-clarification-msg/'.$sentMessageType.'/'.$rfpNode->nid.'/nojs'.$forwardCmpQuery,
					   array(
						 'html'=>TRUE,
						 'attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-clarification-public-form-popup-style')),
						 'query'=> array('event'=>'forward','cnid'=>$clarificationNode->nid),
					   )
					 ).'&nbsp;';*/
			}
			print l('<input type="button" value="Reply" class="btn btn-primary form-submit">',
			        'send-clarification-msg/'.$sentMessageType.'/'.$rfpNode->nid.'/nojs',
					 array(
					   'html'=>TRUE,
					   'attributes'=> array('class'=>array('ctools-use-modal','ctools-modal-clarification-public-form-popup-style')),
					   'query'=> array('attr'=>$cmpQuery,'event'=>'reply','cnid'=>$clarificationNode->nid),
					 )
			       );
		  ?>
        </div>
        <div class="clari-msg-no form-group">
            <label>Message#: <?php print $message_no; ?></label>
        </div>
        <div class="clari-msg-from form-group">
            <label>Message Sent From:</label>
            <div><?php print $fullName; ?>, </div>
            <div><?php print $location; ?><?php print date('m/d/Y H:i A',$clarificationNode->created); ?></div>
        </div>
        <div class="clari-msg-subject form-group">
            <label>Subject:</label>
            <div><?php print $clarificationNode->title; ?></div>
        </div>
        <div class="clari-msg-body form-group">
            <label>Message:</label>
            <div><?php print $message_body; ?></div>
        </div>
        <div class="clari-msg-attachment form-group">
            <label>Attachments:</label>
            <div><?php print $message_documents; ?></div>
        </div>
    </div>
	<div class="clari-msg-action"> 
        <?php if (!is_rfp_expired($rfpNode->nid)) { ?>
        <!--<a href="/send-clarification-msg/<?php //print $sentMessageType.'/'.$rfpNode->nid.'/nojs'.$cmpQuery; ?>" class="ctools-use-modal ctools-modal-clarification-public-form-popup-style">
		<input type="button" value="Send New Message" class="btn btn-primary form-submit">
		</a>--> 
        <?php } ?>    
        <a href="javascript:void(0);" class="" onclick="jQuery('span.popups-close').click();">
		<input type="button" value="Close" class="btn btn-primary form-submit cancel-button">
		</a> </div>
</div>
<script>
if(jQuery('body').find('.clarification-section-<?php echo $clarificationNode->nid; ?> .cus-rfp-clearification').hasClass('unread-msg')){
  var element = jQuery('body').find('.clarification-section-<?php echo $clarificationNode->nid; ?> .cus-rfp-clearification');
  element.removeClass('unread-msg').addClass('read-msg');  //
  element.find('.rfp-clearification-status').html('Read');
}

jQuery('.download-document-section-clarification .download-selected-documents').click(function(e){
  var param= new Array();
	var doc =0;
	jQuery('.clari-msg-attachment input.calrification-document-table.form-checkbox').each(function(index, element) {
      if(jQuery(this).is(':checked')){
		doc++;
		param.push('fids[]=' + jQuery(this).val() || 0);
	  }
    });
	var url = param.join('&');
	if(doc > 0 && url!=''){
	  url = '/all-document-download?'+url;
	  console.log(url);
	  //window.location = '/all-document-download?'+url;	
	  window.location = url;
	}
	
});
</script>
