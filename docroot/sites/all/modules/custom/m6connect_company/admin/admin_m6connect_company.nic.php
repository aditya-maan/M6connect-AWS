<?php

function m6connect_company_my_sub_company_users() {
    
}

/*
  This function use to get users main company and sub companies
 * @arr
 * 
 *  */

function m6connect_company_get_main_sub_company($uid = '', $type = 'main', $main_company_id = 0) {
    global $user;
    if (!is_numeric($uid)) {
        $uid = $user->uid;
    }
    $query = db_select('node', 'n');
    $query->fields('n.nid');
    $query->condition('n.type', 'organization', '=');
    $query->condition('n.uid', $uid, '=');
    $query->leftJoin('field_data_field_main_location_grp', 'field_main_location_grp', 'field_main_location_grp.entity_id=n.nid');
    if ($type == 'main') {
        $query->condition('field_main_location_grp.field_main_location_grp_target_id', array('_none', NULL), 'in');
    } else {
        if ($main_company_id != 0) {
            $query->condition('field_main_location_grp.field_main_location_grp_target_id', $main_company_id, '=');
        }
    }
    $query->execute()->fetchAll();
    
    return $sub_company_nids;
}
?>