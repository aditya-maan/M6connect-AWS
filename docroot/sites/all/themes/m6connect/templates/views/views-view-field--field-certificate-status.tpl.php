<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php
/*
  TODO Load Taxonomy to not use hardcoded TIDs 
  function taxonomy_vocabulary_load($vid) {
  $vocabularies = taxonomy_vocabulary_load_multiple(array($vid));
  return reset($vocabularies);
  }
*/

//print $output; 
//dpm($row, 'field row');
//echo 'start:'.$output.':end';
?>
<!-- Small button group -->
<!--<div class="btn-group div-insurance-cert" id="div-cert-nid-<?php //print $row->nid?>">
  <button type="button" class="btn btn-success btn-md dropdown-toggle" data-toggle="dropdown"
          aria-haspopup="true" aria-expanded="false">
    Action <span class="caret"></span>
  </button>
  <ul class="dropdown-menu">
    <li id="icert-tid-94035-nid-<?php //print $row->nid?>" <?php //echo ($output == 'Sent' ? 'class="active"' : '')?>><a href="#">Sent</a></li>
    <li id="icert-tid-94038-nid-<?php //print $row->nid?>" <?php //echo ($output == 'Approved Certificates' ? 'class="active"' : '')?>><a href="#">Approve</a></li>
    <li id="icert-tid-94039-nid-<?php //print $row->nid?>" <?php //echo ($output == 'Rejected Certificates' ? 'class="active"' : '')?>><a href="#">Reject</a></li>
    <li id="icert-tid-94040-nid-<?php //print $row->nid?>" <?php //echo ($output == 'Resubmit Certificates' ? 'class="active"' : '')?>><a href="#">Resubmit</a></li>
  </ul>
</div> -->

<?php
/*
  TODO Load Taxonomy to not use hardcoded TIDs 
  function taxonomy_vocabulary_load($vid) {
  $vocabularies = taxonomy_vocabulary_load_multiple(array($vid));
  return reset($vocabularies);
  }
*/

//print $output; 
//dpm($row, 'field row');
//echo 'start:'.$output.':end';

//pre($row->nid);
global $user;
$nid = $row->nid;
$node = node_load($nid);
$status = _get_ins_certificate_status($nid, '', TRUE);
$statusname = _get_ins_certificate_status($nid, 'term');
$query = db_select('node', 'n');
$query->condition('nid', $nid, '=');
$query->fields('n', array('uid','status')); 
$result = $query->execute()->fetchAll();
if ($result && is_array($result) && !empty($result) && count($result) > 0) {
  foreach($result as $var=>$val) {
    $nuid = $val->uid;	
	$nstatus = $val->status;	  
  }
}
  
  $isflagged = 0;
  $fid = _get_flag_id_by_flag_name('archive');
  //$fid = 13;
  $query =db_select('flagging', 'fl');
  $query->fields('fl',array('flagging_id'));
  $query->condition('fl.fid',$fid,'=');
  $query->condition('fl.entity_id',$nid,'=');
  $query->condition('fl.uid',$user->uid,'=');
  $isBidding = $query->execute()->rowCount();
  if($isBidding) {
	$isflagged = 1;  
  }
  
?>
<!-- Small button group -->
<div class="btn-group div-insurance-cert" id="div-cert-nid-<?php print $row->nid?>">
  <button type="button" class="btn btn-success btn-md dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
    <?php echo ($output == 'Sent' ? 'Sent' : 'Action')?> <span class="caret"></span>
  </button>
  <ul class="dropdown-menu">
    
    <li class="open">
      <?php print l('Open','node/'.$row->nid); ?>
    </li>
    <?php 
	  $Drafttid = _get_term_id_by_term_name('Draft');
	  $Rejectedtid = _get_term_id_by_term_name('Rejected');
	  $Pendingtid = _get_term_id_by_term_name('Pending');
	  $Approvedtid = _get_term_id_by_term_name('Approved');
	  $Submittedtid = _get_term_id_by_term_name('Submitted');
	  $Deletedtid = _get_term_id_by_term_name('Deleted');
	  $Archivetid = _get_term_id_by_term_name('Archive');
	  $Resubmittid = _get_term_id_by_term_name('Resubmit Certificates');
		$publish = _get_term_id_by_term_name('Publish');
	  
	  if($user->uid == $nuid){ ?>
      
		<?php if($status && in_array($statusname, array('Submitted','Approved')) && $nstatus == '1') { ?>  
          <li id="icert-tid-<?php print $Drafttid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Drafted' ? 'class="active"' : '')?>>
            <a href="#" data-nid="<?php print $row->nid?>" class="movetodraft"><?php echo ($output == 'Drafted' ? 'Drafted' : 'Move to Draft')?></a>
          </li>
        <?php } ?>
        <?php if($status && in_array($statusname, array('Approved','Rejected','Pending'))) { ?>  
          <li id="icert-tid-<?php print $Resubmittid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Resubmitted' ? 'class="active"' : '')?>>
            <a href="#"><?php echo ($output == 'Resubmitted' ? 'Resubmitted' : 'Resubmit')?></a>
          </li>
        <?php } ?>   
        <?php if($status && in_array($statusname, array('Submitted','Approved','Rejected','Pending'))) { ?>  
          <li id="icert-tid-<?php print $Deletedtid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Deleted' ? 'class="active"' : '')?>>
            <a href="#"><?php echo ($output == 'Deleted' ? 'Deleted' : 'Delete')?></a>
          </li>
        <?php } ?>     
        <?php if($status && in_array($statusname, array('Submitted','Approved','Rejected','Pending')) && $nstatus == '0') { ?>  
          <li id="icert-tid-<?php print $publish?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Publish' ? 'class="active"' : '')?>>
            <a href="#"  data-nid="<?php print $row->nid?>" class="movetoarchive"><?php echo ($output == 'Publish' ? 'Publish' : 'Publish')?></a>
          </li>
        <?php } ?>
        <?php if($status && in_array($statusname, array('Submitted','Approved','Rejected','Pending')) && !$isflagged) { ?>  
          <li id="icert-tid-<?php print $Archivetid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Archived' ? 'class="active"' : '')?>>
            <a href="#" data-nid="<?php print $row->nid?>" class="movetoarchive"><?php echo ($output == 'Archived' ? 'Archived' : 'Move to Archive')?></a>
          </li>
        <?php } ?> 
         
    <?php } else { ?>
    
        <?php if($status && in_array($statusname, array('Submitted','Approved','Pending'))) { //'Rejected',?>  
          <li id="icert-tid-<?php print $Rejectedtid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Rejected' ? 'class="active"' : '')?>>
            <a href="#"><?php echo ($output == 'Rejected' ? 'Rejected' : 'Reject')?></a>
          </li>
        <?php } ?>
        <?php if($status && in_array($statusname, array('Submitted','Approved'))) {?>  
          <li id="icert-tid-<?php print $Pendingtid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Pending' ? 'class="active"' : '')?>>
            <a href="#"><?php echo ($output == 'Pending' ? 'Pending' : 'Move to Pending')?></a>
          </li>
        <?php } ?>
        <?php if($status && in_array($statusname, array('Submitted','Rejected','Pending'))) { //'Approved',?>  
          <li id="icert-tid-<?php print $Approvedtid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Approved' ? 'class="active"' : '')?>>
            <a href="#"><?php echo ($output == 'Approved' ? 'Approved' : 'Approve')?></a>
          </li>
        <?php } ?>
        <?php if($status && in_array($statusname, array('Submitted', 'Approved','Rejected','Pending'))) { ?>  
          <li id="icert-tid-<?php print $Deletedtid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Deleted' ? 'class="active"' : '')?>>
            <a href="#"><?php echo ($output == 'Deleted' ? 'Deleted' : 'Delete')?></a>
          </li>
        <?php } ?>
        <?php if($status && in_array($statusname, array('Submitted','Approved','Rejected','Pending')) && !$isflagged) { ?>  
          <li id="icert-tid-<?php print $Archivetid?>-nid-<?php print $row->nid?>" <?php echo ($output == 'Archived' ? 'class="active"' : '')?>>
            <a href="#" class="movetoarchive"><?php echo ($output == 'Archived' ? 'Archived' : 'Move to Archive')?></a>
          </li>
        <?php } ?>        
    
    <?php } ?>
    
  </ul>
</div>

<?php /*
if(in_array(_is_user_submiiter_receiver($node),array('submitter','receiver'))) {
  $submitToUserId = insurance_certificate_submited_for($nid,'user');
  if($user->uid == $submitToUserId) {
	$otheruserid = $node->uid; 
  } else {
	$otheruserid = $submitToUserId;  
  }
  $isnew = check_insurance_unread_message($nid, $user->uid, $otheruserid);
  if($isnew) {
?>
<div class="ins-notifiy-msg-icon btn-group"><img src="<?php print $base_url.'/sites/all/themes/m6connect/images/ins-msg-notify.png'?>" /></div>
<?php	  
  }
}
*/?>
<!--<?php //var_dump($row); ?>-->
