<?php
require_once("../../../default/settings.php");
$dbObject 	=  new dbconn;

if(isset($_REQUEST['award_data'])){
$awardData = $_REQUEST['award_data'];
$explode_data = explode("@@",$awardData);
$award_taker = $explode_data[0];
$award_page = $explode_data[1];
$award_giver = $explode_data[2];
$sql_insert_award =  $dbObject->action_query("INSERT INTO proposal_award (award_taker_id, award_giver_id, node_id, status) VALUES ($award_taker, $award_giver, $award_page, 1)");
}

if(isset($_REQUEST['reject_data'])){
$rejectData = $_REQUEST['reject_data'];
$explode_Reject_data = explode("@@",$rejectData);
$reject_taker = $explode_Reject_data[0];
$reject_page = $explode_Reject_data[1];
$reject_giver = $explode_Reject_data[2];
$sql_insert_reject =  $dbObject->action_query("INSERT INTO proposal_reject (reject_taker_id, reject_giver_id, reject_node, status) VALUES ($reject_taker, $reject_giver, $reject_page, 1)");
}

?>