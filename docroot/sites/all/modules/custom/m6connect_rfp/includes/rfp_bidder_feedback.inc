<?php
function _get_bidder_feed_back_content($id){
  $entity_id = 1164;
  $query = db_select('m6connect_rfp_bidder_feedback', 'mrbf');
    //$query->Join('m6connect_bid_package_invitess', 'mbpi', 'mbpi.rfp_invite_fc_itemid=mrbf.rfp_invite_fc_itemid');
    $query->leftJoin('m6connect_bid_package_invitess', 'mbpi', 'mbpi.rfp_invite_fc_itemid=mrbf.rfp_invite_fc_itemid');
	//$query->leftJoin('m6connect_bid_packages', 'mbp', 'mbpi.bid_package_id=mbp.bid_package_id');
    $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.field_rfp_invite_comapnies_value=mrbf.rfp_invite_fc_itemid');
    $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
    $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
    $query->fields('mbpi', array('bid_package_id', 'bid_package_invites_id'));
    $query->fields('mrbf', array('bidder_feedback_id', 'rfp_invite_fc_itemid','request_bid_intent_count'));
    $query->fields('rcne', array('field_rfp_company_nid_email_value'));
    $query->fields('rcimu', array('field_co_invite_manager_uid_value'));
    $query->condition('mrbf.entity_id', $entity_id, '=');
	//$query->condition('mbp.status', 0, '!=');
    $query->condition('ric.entity_id', $entity_id, '=');
    $query->condition('mrbf.status', 1, '=');
    $query->isNotNull('rcne.field_rfp_company_nid_email_value');
    //$query->condition('mbpi.bid_package_id',$package_id,'=');
    $query->orderBy('mbpi.bid_package_id', 'ASC');
    $result = $query->execute()->fetchAll();
	
	return 'hello';	
}
