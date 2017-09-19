<?php
/**
 * @file include file for projects module
 */

/**
 * Menu callback for projects, projects/cr, projects/cpm
 */
function projects_view() {
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery-ias.min.js');
  global $base_url, $user, $theme_path, $company;
  /*     * ***Changed**** */
  $CuurCompNid = $_SESSION['company'];
  $companyAdminRoleUsers = _get_company_users_by_og_roles($CuurCompNid,'company admin');
  $isCompanyIndividual = is_company_individual_flag($CuurCompNid);
  $userid = $user->uid;
  $pro_search = isset($_REQUEST ['pro_search']) ? $_REQUEST ['pro_search'] : '';
  $pro_sort = isset($_REQUEST ['pro_sort']) ? $_REQUEST ['pro_sort'] : '';
  if($pro_sort == 'name_asc'){
    $selectedsort1 ='selected ="selected"'; 
  }
  elseif($pro_sort == 'name_desc'){
   $selectedsort2 ='selected ="selected"'; 
  }
  elseif($pro_sort == 'date_desc'){
    $selectedsort3 ='selected ="selected"'; 
  }
  elseif($pro_sort == 'date_asc'){
    $selectedsort4 ='selected ="selected"'; 
  }
  $output = '';
  $output .= '<div class="custom-projects-lists">';
  $output .= '<div class="clearfix margin-bottom-10">';
  $output .= '<div class="custom-projects-lists-search pull-left">';   
  $output .= '<input placeholder="Search..." type="text" value="' . $pro_search . '" name="pro_search_custom" size="60" maxlength="128" class="form-text form-controls pro_search_custom" /><input type="button" id="project-list-search-button" name="op" value="Search" class="form-submit">';  
  $output .= '</div>';
  $output .= '<div class="custom-projects-lists-sorting pull-right">';
  $output .= '<select name="project_sort" id="project_sorting" class="form-select">
                <option value="name_asc" '.$selectedsort1.'> Name (A-Z)</option>
                <option value="name_desc" '.$selectedsort2.'>Name (Z-A)</option>
                <option value="date_desc" '.$selectedsort3.'> Bid Date (Newest - Oldest)</option>
                <option value="date_asc" '.$selectedsort4.'> Bid Date (Oldest - Newest)</option>  
              </select>';
  $output .= '</div>';
  $output .= '</div>';
  $output .= '<div class="row margin-5">';
  $output .= '<div class="cust-project-search-form col-md-3 col-sm-12 col-xs-12 padding-5">';
  $output .= drupal_render(drupal_get_form('cust_project_search_form'));
  $output .= '</div>';
  $pro_diversity = isset($_REQUEST ['pro_diversity']) ? $_REQUEST ['pro_diversity'] : '';
  //pre($pro_diversity);
  $pro_div_arr = array(0);
  if (!empty($pro_diversity)) {
    $pro_div_arr = explode(',', $pro_diversity); //pre($pro_div_arr);
  }
  $pro_div_arr = array_filter($pro_div_arr);
  $pro_region = isset($_REQUEST ['pro_region']) ? $_REQUEST ['pro_region'] : '';
  $interested = isset($_REQUEST ['interested']) ? $_REQUEST ['interested'] : '';
  $myproject = isset($_REQUEST ['myproject']) ? $_REQUEST ['myproject'] : '';
  $myinterested = isset($_REQUEST ['myinterested']) ? $_REQUEST ['myinterested'] : '';
  $collaboration = isset($_REQUEST ['collaboration']) ? $_REQUEST ['collaboration'] : '';
  $public = isset($_REQUEST ['public']) ? $_REQUEST ['public'] : '';
  $draft = isset($_REQUEST ['draft']) ? $_REQUEST ['draft'] : '';
  $type = array('project');
  $counter = 0;

  $or = db_or();
  $and = db_and();
  $query = db_select('node', 'n')->extend('PagerDefault');
  //$query->AddExpression('distinct n.nid', 'nid');
  $query->fields('n', array('nid'));
  /*     * ***Changed**** */
  $query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');
  if ($interested) {
    $query->leftJoin('m6connect_flagging', 'mfl', 'mfl.node_id = n.nid');
    if (!empty(arg(1))) {
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->condition('fdfct.field_cm_type_value', arg(1));
    }
    else{
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->isNull('fdfct.field_cm_type_value');
    }
    $query->condition('mfl.company_id', $CuurCompNid);
    $query->condition('mfl.uid', $userid);
  } 
  else if ($myproject) {
    if(in_array($user->uid,$companyAdminRoleUsers)){
      $company_emails_users = db_select('m6connect_og_membership_email', 'om')->fields('om', array('user_uid','company_email'))->condition('om.entity_id', $CuurCompNid, '=')->execute()->fetchAllKeyed(0,1);
      $company_email = array_map('strtolower',array_values($company_emails_users));
      $company_user = array_keys($company_emails_users);
      $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
      $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
      $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
        //Invited Company Access
      $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
      $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
      $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');              
      if (!empty(arg(1))) {
        $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id=n.nid');        
        $query->condition('fdfct.field_cm_type_value', arg(1));
      }
      else {
        $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id=n.nid');        
        $query->isNull('fdfct.field_cm_type_value');
      }
      $query->where('((n.uid IN(:UserUid) and ogm.gid=:ogmid) or (n.status=1 AND (rcne.field_rfp_company_nid_email_value IS NOT NULL) AND ((rcne.field_rfp_company_nid_email_value=:companyNid) or(LOWER(rcne.field_rfp_company_nid_email_value) IN(:companyMail)))))', array(':UserUid' => $company_user, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
    }else{
      $company_email = db_select('m6connect_og_membership_email', 'om')->fields('om', array('company_email'))->condition('om.entity_id', $company->nid, '=')->condition('om.user_uid', $user->uid, '=')->execute()->fetchColumn(0);
      $company_email = (!empty($company_email)) ? $company_email : '';
      $company_email = strtolower($company_email);
      //$company_users = _get_current_company_users($user->uid);
      $company_users = _get_company_users_by_group_company($company);
      //$query->condition('n.uid', $user->uid); //myinterested
      //////////////////////// Not show company user's project, only show user's and colaborated to user's project /////////////
      //$query->condition('n.uid', $company_users, 'IN');  // make it comment to not show company project here
      $userCmpNid = _get_user_company_nid();
      $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
      $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
      $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
      //Invited Company Access
      $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
      $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
      $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
      /* $query->where('((pcne.field_company_nid_mail_value=:companyNid or pcne.field_company_nid_mail_value=:companyMail) and ((pcimu.field_comapny_manager_value IS NULL) or FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0)) or (n.uid=:UserUid)', array(':UserUid' => $user->uid, ':companyMail' => $user->mail, ':companyNid' => $userCmpNid));
      /////////////////////////////////////
      //         * ***Changed****
      $query->where('(ogm.gid=:ogmid)', array(':ogmid' => $CuurCompNid)); */
      // add invited company conditions
      $query->where('((n.uid=:UserUid AND ogm.gid=:ogmid) OR (n.status=1 AND ((pcne.field_company_nid_mail_value=:companyNid OR pcne.field_company_nid_mail_value=:companyMail) AND ((pcimu.field_comapny_manager_value IS NULL) OR FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0))  OR ((rcne.field_rfp_company_nid_email_value=:companyNid) AND FIND_IN_SET(:UserUid,rcimu.field_co_invite_manager_uid_value)>0) OR ((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail) OR ((pcne.field_company_nid_mail_value=:companyNid) AND FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0)))', array(':UserUid' => $user->uid, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
    }
  } 
  else if ($myinterested) {
    $company_users = _get_current_company_users($user->uid);
    //$query->condition('n.uid', $user->uid);myinterested
    $query->Join('flagging', 'fl', 'fl.entity_id = n.nid');
    if (!empty(arg(1))) {
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->condition('fdfct.field_cm_type_value', arg(1));
    }
    else{
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->isNull('fdfct.field_cm_type_value');
    }
    $query->where('(ogm.gid=:ogmid)', array(':ogmid' => $CuurCompNid));
    $query->condition('n.uid', $company_users, 'IN');
  } 
  else if ($collaboration) {
    //$userCmpNid = _get_user_company_nid();
    $userCmpNid = $CuurCompNid;
    $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
    $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
    $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
    if (!empty(arg(1))) {
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->condition('fdfct.field_cm_type_value', arg(1));
    }
    else{
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->isNull('fdfct.field_cm_type_value');
    }
    $query->where('((pcimu.field_comapny_manager_value IS NOT NULL) AND (pcne.field_company_nid_mail_value=:companyNid) AND (FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0))', array(':UserUid' => $user->uid, ':companyNid' => $userCmpNid));
  } 
  else if ($public) {
    $query->leftJoin('field_data_field_project_public', 'pp', 'pp.entity_id=n.nid');
    if (!empty(arg(1))) {      
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->condition('fdfct.field_cm_type_value', arg(1));
    }
    else{
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->isNull('fdfct.field_cm_type_value');
    }
    $query->where('((n.status=1 AND (pp.field_project_public_value=1)))');
  } 
  else {
    if (!empty($pro_search)) {
      $query->leftJoin('field_data_field_public_description', 'pd', 'pd.entity_id = n.nid');
      $query->leftJoin('field_data_field_complete_description', 'cd', 'cd.entity_id = n.nid');
      $query->leftJoin('field_data_field_projects_keywords', 'pk', 'pk.entity_id = n.nid');
      $query->fields('pd');
      $query->fields('cd');
      $query->fields('pk');
      $query->condition(db_or()->condition('title', '%' . db_like($pro_search) . '%', 'LIKE')
        //->condition('pd.field_public_description_value', '%' . db_like($pro_search) . '%', 'LIKE')
        ->condition('cd.field_complete_description_value', '%' . db_like($pro_search) . '%', 'LIKE')
        ->condition('pk.field_projects_keywords_value', '%' . db_like($pro_search) . '%', 'LIKE')
      );      
    }
    /// start for pro_short//////
    if (!empty($pro_sort)) {
      if($pro_sort == 'date_desc'){      
        $query->leftJoin('field_data_field_pro_bidding_info', 'sbi', 'sbi.entity_id = n.nid');  
        $query->leftJoin('field_data_field_proj_bid_date', 'sbd', 'sbd.entity_id =sbi.field_pro_bidding_info_value');
        $query->orderBy('sbd.field_proj_bid_date_value','DESC');
      }
      if($pro_sort == 'date_asc'){
        $query->leftJoin('field_data_field_pro_bidding_info', 'sbi', 'sbi.entity_id = n.nid');  
        $query->leftJoin('field_data_field_proj_bid_date', 'sbd', 'sbd.entity_id =sbi.field_pro_bidding_info_value');   
        $query->orderBy('sbd.field_proj_bid_date_value','ASC');
      }     
      if($pro_sort == 'name_asc'){    
        $query->fields('n', array('title'));
        $query->orderBy('n.title','ASC');
      }
      if($pro_sort == 'name_desc'){   
        $query->fields('n', array('title'));
        $query->orderBy('n.title','DESC');
      } 
    }
    /// start for pro_short//////
    if ($pro_div_arr) { 
      $query->Join('field_data_field_project_diversity_type', 'dt', 'dt.entity_id = n.nid');
      $query->fields('dt');
      $query->condition('dt.field_project_diversity_type_target_id', $pro_div_arr, 'IN');
    }
    if (!empty($pro_region)) {
      $query->Join('field_data_field_project_address', 'pa', 'pa.entity_id = n.nid');
      $query->fields('pa');
      $pro_region_tids = taxonomy_get_children_all($pro_region);
      $rctids = array();
      if (!empty($pro_region_tids)) {
          $rctids[] = $pro_region;
          foreach ($pro_region_tids as $rk => $rv) {
              $rctids[] = $rv->tid;
          }
      } else {
          $rctids[] = $pro_region;
      }
      $query->condition('pa.field_project_address_tid', $rctids, 'IN');
    }
  }
  $query->condition('n.type', $type, 'IN');
  if (!empty(arg(1))) {
    $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
    $query->condition('fdfct.field_cm_type_value', arg(1));
  }
  else {
    $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
    $query->isNull('fdfct.field_cm_type_value');
  }
  if ($draft) {
    if (!empty(arg(1))) {
      $query->join('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->where('(ogm.gid=:ogmid) AND (fdfct.field_cm_type_value = :argument)', array(':ogmid' => $CuurCompNid, ':argument' => arg(1)));
    }
    else{
      $query->leftJoin('field_data_field_cm_type', 'fdfct', 'fdfct.entity_id = n.nid');
      $query->where('(ogm.gid=:ogmid) AND (fdfct.field_cm_type_value IS NULL)', array(':ogmid' => $CuurCompNid));
    }
    $query->condition('n.status', 0, '=');
    $query->condition('n.uid', $user->uid, '=');    
  }
  else {
    $query->condition('n.status', 1, '=');
  }
  if (!$myproject && !$draft && !$collaboration && !$public && !$myinterested && !(isset($user->roles[3]))) {
    $query->leftJoin('field_data_field_project_public', 'pp', 'pp.entity_id=n.nid');
    //Invited Company Access
    $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
    $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
    $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
    //Collabarated Access
    $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
    $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
    $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');    
    if ($isCompanyIndividual) {
      $query->where('(n.uid=:UserUid and ogm.gid=:ogmid) or (pp.field_project_public_value=1 and n.status=1) or
      (n.status=1 and (LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail)) or
      (pcne.field_company_nid_mail_value=:companyMail)', array(':UserUid' => $user->uid, ':ogmid' => $CuurCompNid, ':companyMail' => strtolower($user->mail)));
    } 
    else {
      // if company admin
      if (in_array($user->uid,$companyAdminRoleUsers)) {
        $company_emails_users = db_select('m6connect_og_membership_email', 'om')->fields('om', array('user_uid','company_email'))->condition('om.entity_id', $CuurCompNid, '=')->execute()->fetchAllKeyed(0,1);
        $company_email = array_map('strtolower',array_values($company_emails_users));
        $company_user = array_keys($company_emails_users);
        $query->where('((n.uid IN(:UserUid) and ogm.gid=:ogmid) or (n.status=1 AND (pp.field_project_public_value=1) or ((rcne.field_rfp_company_nid_email_value=:companyNid)) or((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND (LOWER(rcne.field_rfp_company_nid_email_value) IN(:companyMail)))))', array(':UserUid' => $company_user, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
      }
      else {
        $company_email = db_select('m6connect_og_membership_email', 'om')->fields('om', array('company_email'))->condition('om.entity_id', $company->nid, '=')->condition('om.user_uid', $user->uid, '=')->execute()->fetchColumn(0);
        $company_email = (!empty($company_email)) ? $company_email : '';
        $company_email = strtolower($company_email);
        $query->where('((n.uid=:UserUid and ogm.gid=:ogmid) or (n.status=1 AND (pp.field_project_public_value=1) or ((rcne.field_rfp_company_nid_email_value=:companyNid) AND FIND_IN_SET(:UserUid,rcimu.field_co_invite_manager_uid_value)>0) or ((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail) or ((pcne.field_company_nid_mail_value=:companyNid) AND FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0)))', array(':UserUid' => $user->uid, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
      }
    }
  }
  if (empty($pro_sort)){
    $query->orderBy('n.created', 'DESC'); 
  }
  $query->groupBy('n.nid');
  $query->limit(15);

  $result = $query->execute();

  $cpath = current_path();
  $querystring = $_SERVER['QUERY_STRING'];

  $is_search = str_replace('q=projects', '', $querystring);

  if ($interested || $myproject || $collaboration || $public || $myinterested || !empty($pro_diversity) || !empty($pro_search) || !empty($pro_region) || !empty($draft)) {
    $output .= '<div class="col-md-9 col-sm-12 col-xs-12 project-select-filter-list">';
    $output .= '<input type="hidden" class="site_base_url" value="' . $base_url . '">';
    if (!$myproject) {
      //$output .= '<label class="select-title">Your Selections:</label>';
    }
    if ($interested) {
      //$output .= l('Intersted',$base_url.'/projects'); 
      //$output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">Interested</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">interested</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($myproject) {
      //$output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">My Project</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">myproject</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($collaboration) {
        //$output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">Collaboration</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">collaboration</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($public) {
        //$output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">Public</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">public</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($myinterested) {
        //$output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">My Interested</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">myinterested</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($draft) {
       // $output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">Draft</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">draft</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($d) {
      $output .= '<span class="cust-selection-list"><span class="sfilter-label">Filter: <span class="sfilter-value">Draft</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">draft</span><span class="sfilter-val"></span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if (!empty($pro_search)) {
      $output .= '<span class="cust-selection-list"><span class="sfilter-label">Search: <span class="sfilter-value">' . $pro_search . '</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">pro_search</span><span class="sfilter-val">' . $pro_search . '</span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if (!empty($pro_region)) {
      $term = taxonomy_term_load($pro_region);
      $termname = $term->name;
      $output .= '<span class="cust-selection-list"><span class="sfilter-label">Region: <span class="sfilter-value">' . $termname . '</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">pro_region</span><span class="sfilter-val">' . $pro_region . '</span><span class="filter-qstr">' . $querystring . '</span></span></span>';
    }
    if ($pro_div_arr) { //pre($pro_div_arr);
      $output .= '<span class="cust-select-list-dives">Diversity Types:</span>';
      foreach ($pro_div_arr as $k => $v) {
        if ($v != '_none') {
          $dnod = node_load($v);
          $dname = $dnod->title;
          $output .= '<span class="cust-selection-list"><span class="sfilter-label"><span class="sfilter-value">' . $dname . '</span><i class="fa fa-times-circle"></i></span><span class="cust-selection-hidden-val" style="display:none;"><span class="sfilter-name">pro_diversity</span><span class="sfilter-val">' . $v . '</span><span class="filter-qstr">' . $querystring . '</span></span></span>';
        }
      }
    }
    $output .= '</div>';
  }
  ///////////////////////////////////////////////////////
  $output .= '<div class="col-md-9 col-sm-12 col-xs-12 project-list-search-section padding-5">
               <div class="project-contaners">';
         //search bar replace in left 
   //$onchange= 'if (this.value) window.location.href="?project_sort=this.value"';      
  $output .= '<div class="project-list-scroll">';
  while ($record = $result->fetchAssoc()) {
    //while($record = $result->fetchAll()) {  
    $node = node_load($nid = $record['nid']);
    $project_postuser = user_load($node->uid);
    //$project_postfirstname = $project_postuser->field_first_name['und'][0]['value'];
    //$project_postlastname = $project_postuser->field_last_name['und'][0]['value'];    
    $comprealusername = _get_node_company_user_name($node->nid);
    $comprealusernameoutput = (!empty($comprealusername['company_title']))?trim($comprealusername['company_title']).', '.$comprealusername['user_name']:$comprealusername['user_name'];
    $companyp = node_load($node->og_group_ref['und'][0]['target_id']);
    //pre($company);
    $desc = isset($node->field_public_description['und']['0']['value']) ? $node->field_public_description['und']['0']['value'] : '';
    $desc = strip_tags($desc);
    $length_body = strlen($desc);
    if ($length_body > 50) {
      $body = substr($desc, 0, 50) . '...';
    } else {
      $body = $desc;
  }
  $pimagepath = '';
  $pimgpath = (isset($node->field_images['und']) && !empty($node->field_images['und'][0]['uri'])) ? $node->field_images['und'][0]['uri'] : 0;
  if ($pimgpath) {
    $pimagepath = image_style_url('thumbnail', $pimgpath);
  }
  $biddateval = (isset($node->field_pro_bid_date['und'])) ? $node->field_pro_bid_date['und'][0]['value'] : '';
  $dtstmp = !empty($biddateval) ? strtotime($biddateval) : '';
  $biddinginfo = (isset($node->field_pro_bidding_info['und'])) ? $node->field_pro_bidding_info['und'] : '';
  $bdatearr = array();
  if (!empty($biddinginfo)) { //pre($biddinginfo);
    foreach ($biddinginfo as $k => $v) {
      $fcval = $v['value'];
      $query2 = db_select('field_data_field_proj_bid_date', 'b')->fields('b', array('field_proj_bid_date_value'))->condition('entity_id', $fcval, '=');
      $result2 = $query2->execute();
      while ($record2 = $result2->fetchAssoc()) {
        $bd = $record2['field_proj_bid_date_value'];
      }
      $bdatearr[] = strtotime($bd);
    }
  }

        // ************************************************************
        $cls = ($counter % 2 == 0) ? 'odd' : 'odd'; //even
        $output .='<div class="project-box ' . $cls . '">';
        $output .= '<div class="row">';
        $output .='<div class="cust-title col-md-2 col-sm-2 col-xs-12">';
        $output .='<div class="custm-pro-img">'; //new image
        if ($pimgpath) {
            $output .='<img src="' . $pimagepath . '" alt="' . $node->title . '" title="' . $node->title . '" />';
        } else {
            $output .='<img src="/sites/all/themes/m6connect/images/default_project_icon_n.jpg" alt="' . $node->title . '" title="' . $node->title . '" />';
        }
        $output .='</div>';
        $output .='</div>';
        /**/ $output .= '<div class="cust-details col-md-10 col-sm-10 col-xs-12">'; //****new structure
        /**/ $output .= '<div class="row">'; //****new structure
        $output .='<div class="cust-desc col-md-9 col-sm-9 col-xs-12">'; //****new structure
        $output .='<div class="project-title">' . l($node->title, 'node/' . $node->nid, array('attributes' => array('class' => array('cust-proj-title')))) . '</div>';
        $output .='<div class="pro-company-name"><label>Posted By:&nbsp;</label><span>'.$comprealusernameoutput.'</span></div>';
        /**/ $output .='</div>';

        /**/ $output .= '<div class="col-md-3 col-sm-3 col-xs-12">';
        /***project action button start***/
        //global $user;
        //$node = node_load($row->nid);
        if($node->uid == $user->uid){
            $pro_action_btn = '<div class="btn-group">
              <div class="dropdown">
              <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
              <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
                <li>'. l('Open','node/'.$node->nid).'</li>';
                $pro_action_btn .= '<li>'. l('Invite Companies','invite-companies/'.$node->nid).'</li>';
                if($node->status == 1){
                  $pro_action_btn .= '<li>'. l('Unpublish','nodehide/'.$node->nid).'</li>';
                }else{
                  $pro_action_btn .= '<li>'. l('Publish','nodeshow/'.$node->nid).'</li>';
                }
                $pro_action_btn .= '<li>'. l('Delete','customaction/node/'.$node->nid.'/delete/nojs', array('attributes'=> array('id'=>'node-delete-pupup', 'class'=> array('use-ajax', 'ctools-modal-assign-dashboard-popup-style')),'query'=>array('destination'=> current_path()))).'</li>';
                                               
                $pro_action_btn .= '</ul>
                                </div>
                              </div>';
              $output .= $pro_action_btn;       
        }
        /***project action button end***/       
        
        $collabarateUsers = m6connect_projects_uids_from_list($node);
        //$companyUsers = _get_current_company_users($node->uid);
        $companyUsers = _get_company_users_by_group_company($companyp);
        if (in_array($user->uid, $companyUsers) || in_array($user->uid, $collabarateUsers)) {
            
        } else {
            $output .= '<div class="cust-invite-btn">' . flag_create_link('interested', $node->nid) . '</div>';
        }
        /**/ $output .= '</div>';
        /**/ $output .= '</div>';
        /**/ $output .= '<div class="row">';
        /**/ $output .= '<div class="cust-desc col-md-9 col-sm-9 col-xs-12">';
        if (!empty($bdatearr)) {
            $v = '';
            foreach ($bdatearr as $k => $v) {
                //$output .='<div> <strong>Bid Date: </strong>'.date("j F Y H:i P (e)",$v).'</div>'; 
                $vdate = '&nbsp;';
                if (!empty($v)) {
                    $vdate = date("F d, Y h:iA T", $v);
                }
                $output .='<div class="project-bid-date"> <strong>Bid Date: </strong>' . $vdate . '</div>';
            }
        } else {
            //$output .='<div> <strong>Bid Date: </strong>' . date("F d, Y h:iA T", '') . '</div>';

            $output .='<div class="project-bid-date"> <strong>Bid Date: </strong>&nbsp;</div>';
        }
        /**/ $output .='<div class="cust-proj-body">' . $body . '</div>';
        /**/ $output .= '</div>';
        //$output .='<div> <strong>Bid Date: </strong>'.date("j F Y",$dtstmp).'</div>'; 
//////        $output .='<div>' . $body . '</div>';
//////        $output .='</div>';

        /* $output .='<div class="cust-invite-btn col-sm-2 text-right"><div class="checkbox">
          <label for="Interested"><input type="checkbox" name="Interestd" value="Interestd">Interested </label>
          </div></div>'; */
        /**/ $output .= '<div class="col-md-3 col-sm-3 col-xs-12 cust-invite-btn text-left">';
        if (in_array($user->uid, $companyUsers) || in_array($user->uid, $collabarateUsers)) {
            ////$output .='<div class="cust-invite-btn text-left padding-0 col-md-3 col-sm-3 col-xs-12"><div class="cmpy-btn-seprator">';
            //$output .= '<div class="cust-invite-btn">' . flag_create_link('bookmarks', $node->nid) . '</div>';
            ////$output .='</div></div>';
        } else {
            ////$output .='<div class="cust-invite-btn text-left padding-0 col-md-3 col-sm-3 col-xs-12"><div class="cmpy-btn-seprator">'; 
            //$output .= '<div class="cust-invite-btn">'.flag_create_link('interested', $node->nid). '</div>';
            $output .= '<div class="cust-invite-btn">' . flag_create_link('favourite', $node->nid) . '</div>';
            $output .= '<div class="cust-invite-btn">' . flag_create_link('bookmarks', $node->nid) . '</div>';
            $output .= '<div class="cust-invite-btn">' . flag_create_link('spam', $node->nid) . '</div>';
            ////$output .= '</div></div>';
        }
        /**/ $output .= '</div>';

        /**/ $output .= '</div>';
        /**/ $output .= '</div>';
        //$output .='<div class="cust-invite-btn text-right col-md-2 col-sm-3 col-xs-12">' . l(t('<i class="fa fa-bookmark"></i> Bookmark'),'#',array('attributes'=>array('class'=>array('cust-bookmark-flag')),'html'=>true)) . '</div>'; 
        //$output .='<div class="cust-invite-btn text-right col-md-3 col-sm-3 col-xs-12">' . flag_create_link('bookmarks', $node->nid) . '</div>';
        ////$output .='<div class="clear"></div>';
        $output .='</div>';
        $output .='</div>';
        $counter++;
    }
    $output .='<div class="clear"></div>';
    // $output .= theme('pager', array('tags' => NULL));
    if ($counter < 1)
        $output .='<div Class="messages status">' . t('No Results available. Please try later.') . '</div>';

    $output .='</div>'; //<div class="col-md-8 col-sm-8 col-xs-12">
    $output .= '</div>';
    $output .= '</div>';


    $output .='</div>';
    $output .='</div>';

    $next_scroll_page = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next'))));
    if (isset($next_scroll_page)) {
        $output .= '<div class="nav" style="display: none;">' . $next_scroll_page . '</div>';
    }


    return $output;
}

function cust_project_search_form($form, $form_state) {
  $form['#attributes']['class'][] = 'cust-project-search-form';
  $interested = isset($_REQUEST ['interested']) ? $_REQUEST ['interested'] : '';
  if (empty($interested)) {
      $interested = isset($_REQUEST ['myproject']) ? $_REQUEST ['myproject'] : '';
  }
  if (empty($interested)) {
      $interested = isset($_REQUEST ['myinterested']) ? $_REQUEST ['myinterested'] : '';
  }
  if (empty($interested)) {
      $interested = isset($_REQUEST ['draft']) ? $_REQUEST ['draft'] : '';
  }
  if (empty($interested)) {
      $interested = isset($_REQUEST ['collaboration']) ? $_REQUEST ['collaboration'] : '';
  }
  $pro_search = isset($_REQUEST ['pro_search']) ? $_REQUEST ['pro_search'] : '';
  $pro_diversity = isset($_REQUEST ['pro_diversity']) ? $_REQUEST ['pro_diversity'] : ''; //pre($pro_diversity);
  $pro_sort = isset($_REQUEST ['pro_sort']) ? $_REQUEST ['pro_sort'] : ''; 
  $pro_div_arr = array(0);
  if (!empty($pro_diversity)) {
      $pro_div_arr = explode(',', $pro_diversity); //pre($pro_div_arr);
  }
  $pro_region = isset($_REQUEST ['pro_region']) ? $_REQUEST ['pro_region'] : '';
  $form['pro_search'] = array(
    '#type' => 'textfield',
    '#title' => 'Search',
    //'#prefix'=>'<div class="row"><div class="col-md-12 cal-sm-12 col-xs-12">',
    '#default_value' => $pro_search,
    '#attributes' => array('placeholder' => t('Projects Description, Public Description Keywords')),
        //'#prefix'=>'<div class="pro_search_section" style="display:none;">',
        //'#suffix' => '</div>',
  );
  $form['pro_search_project_sorting'] = array(
    '#type' => 'hidden',
    '#title' => 'Search Short',
    //'#prefix'=>'<div class="row"><div class="col-md-12 cal-sm-12 col-xs-12">',
    '#default_value' => $pro_sort,
    '#attributes' => array('placeholder' => t('Search Short'),'class'=>'pro-search-project-sorting'),
    //'#prefix'=>'<div class="pro_search_section" style="display:none;">',
    //'#suffix' => '</div>',
  );
  //$options = array('connections' => 'Connections', 'interested' => 'Interested', 'invited' => 'Invited', 'public' => 'Public', 'all_public' => 'All Public'); 
  $notification = $_SESSION['notification_user'];
  $interestedProjectNotificationCount = '';
  $collabarateProjectNotificationCount = '';
  if (isset($notification['notification_project'])) {
      if (!empty($notification['notification_project']['interest']['count'])) {
          $interestedProjectNotificationCount = '<span class="notification-count">' . $notification['notification_project']['interest']['count'] . '</span>';
      }
      if (!empty($notification['notification_project']['collabarate']['count'])) {
          $collabarateProjectNotificationCount = '<span class="notification-count">' . $notification['notification_project']['collabarate']['count'] . '</span>';
      }
  }

  // Load includes/common.inc from the hierarchical select module.
  module_load_include('inc', 'hierarchical_select', 'includes/common');
  // Load category based in vocabulary machine name
  $voc = 'region';
  $vocabulary = taxonomy_vocabulary_machine_name_load($voc);
  $form['pro_search_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('cust_pro_search_container')),
  );
  $form['pro_search_container']['pro_region'] = array(
      '#title' => t('Region'),
      '#type' => 'hierarchical_select',
      '#config' => array(
          'module' => 'hs_taxonomy',
          'params' => array(
              'vid' => (int) $vocabulary->vid,
              'exclude_tid' => NULL,
              'root_term' => NULL,
              'entity_count_for_node_type' => NULL,
          ),
      ),
      '#default_value' => $pro_region,
          //'#suffix'=>'</div>',
          //'#attributes' => array('class'=> array('col-md-4', 'cal-sm-4', 'col-xs-12', 'cust-pro-shs'))
  );
  hierarchical_select_common_config_apply($form['pro_region'], "taxonomy-$vocabulary->vid");
  $element_info = element_info('hierarchical_select');
  $form['pro_search_container']['pro_region']['#process'] = array_merge($element_info['#process'], array('hs_taxonomy_widget_process'));
  $dtype = array('diversity');
  $query = db_select('node', 'n');
  $query->fields('n', array('nid','title'))
          ->condition('type', $dtype, 'IN');
  $result = $query->execute()->fetchAllKeyed(0,1);
  $diversityArr['_none'] = 'Select All';
  $diversityArr +=$result;
  /*foreach ($result as $row) {
      $dnode = node_load($dnid = $row->nid, $vid = NULL, $reset = FALSE);
      $diversityArr[$dnid] = $dnode->title;
  } //pre($diversityArr); */

  /* $ckall = array('all' => 'All');
    $form['checkall_diversity'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Diversity Suppliers'),
    '#options' => $ckall,
    ); */
  $form['pro_search_container']['pro_diversitytype'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Diversity Types'),
    '#options' => $diversityArr,
    //'#multiple' => 1,
    //'#prefix'=>'<div class="col-md-12 cal-sm-12 col-xs-12">',
    '#default_value' => $pro_div_arr,
  );
  $form['pro_search_container']['pro_reset'] = array(
    '#type' => 'submit',
    '#value' => 'Reset',
    '#prefix' => '<div class="text-right">',
    '#attributes' => array('class' => array('btn', 'btn-primary'))
  );
  $form['pro_search_container']['pro_submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
    '#suffix' => '</div>',
    '#attributes' => array('class' => array('btn', 'btn-primary', 'proj-submit'))
  );
  return $form;
}

function cust_project_search_form_validate($form, $form_state) { //pre($form_state,1);
}

function cust_project_search_form_submit($form, &$form_state) {
    global $base_url;
  //pre($form_state);
  
    if ($form_state['values']['op'] == 'Reset') {
        drupal_goto($base_url . '/projects');
    } else {
        $values = $form_state['values']; //pre($values); 
        $pro_search = $values['pro_search'];
        $pro_short = $values['pro_search_project_sorting'];
        $pro_filter = '';
        //$pro_diversity = (!empty($values['pro_diversitytype']))? ($values['pro_diversitytype'] != '_none')?$values['pro_diversitytype']:'' :'';
        $pro_div = (!empty($values['pro_diversitytype'])) ? $values['pro_diversitytype'] : ''; //pre($pro_div);
        if (!empty($pro_div)) {
            $pro_div = array_filter($pro_div);
            //$pro_div2  = array_shift($pro_div); //pre($pro_div,1);
            $pro_diversity = implode(',', $pro_div); //pre($pro_diversity,1);
        }
        $pro_region = isset($values['pro_region'][0]['tid']) ? $values['pro_region'][0]['tid'] : '';
        if(!empty(arg(1))){
          $url = '/projects/'.arg(1);
        }
        else{
          $url = '/projects';
        }
        $path = $base_url . $url."?pro_search=" . $pro_search . '&pro_filter=' . $pro_filter . '&pro_diversity=' . $pro_diversity . '&pro_region=' . $pro_region. '&pro_sort=' . $pro_short;
        $_SESSION['last_project_search'] = $path;
        drupal_goto($path);
    }
}

/**
 * Menu callback for rfpinboxdelete/%
 */
function rfp_inbox_delete($rfpNid) {
    global $user;
    $user_groups = og_get_groups_by_user($user, 'node');
    if (is_array($user_groups) && count($user_groups) > 0) {
        $user_groups = array_values($user_groups);
        $companyNid = $user_groups[0];
        $companyMail = $user->mail;

        $dbor = db_or()
                ->condition('rcne.field_rfp_company_nid_email_value', $companyNid, '=')
                ->condition('rcne.field_rfp_company_nid_email_value', $companyMail, '=');

        $query = db_select('node', 'n');
        $query->Join('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
        $query->Join('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
        $query->Join('field_data_field_invite_inbox_status', 'iis', 'ric.field_rfp_invite_comapnies_value = iis.entity_id');
        //$query->fields('n',array('nid'))
        $query->fields('ric', array('field_rfp_invite_comapnies_value'))
                ->condition('n.type', 'rfp', '=')
                ->condition('n.nid', $rfpNid, '=')
                ->condition('iis.field_invite_inbox_status_value', 1, '=')
                ->condition($dbor);
        $result = $query->execute()->fetchCol(); //pre($result);
        if ($result && is_array($result) && !empty($result) && count($result) > 0) {
            //return TRUE;
            $fcid = $result[0];
            $fc_item = field_collection_item_load($fcid);
            $fc_wrapper = entity_metadata_wrapper('field_collection_item', $fc_item);
            $fc_wrapper->field_invite_inbox_status->set(0);
            $fc_wrapper->save();
        }
    }


    exit();
}

/**
 * Menu callback for copyproject/%
 */
function copy_project_node($projectnid) { //pre('copy1',1);
  $account = $GLOBALS['user'];
  $original_node = node_load($projectnid);
  $node = clone $original_node;

  //unset($node->field_pro_bidding_info['und']);
  $node->nid = NULL;
  $node->vid = NULL;
  $node->tnid = NULL;
  $node->log = NULL;
  // Also handle modules that attach a UUID to the node.
  $node->uuid = NULL;
  $node->vuuid = NULL;

  // Anyonmymous users don't have a name.
  // @see: drupal_anonymous_user().
  $node->name = isset($account->name) ? $account->name : NULL;
  $node->uid = $account->uid;

  $node->created = NULL;

  $node->path = NULL;
  $node->status = 0;

  $node->title = t('Copy !title', array('!title' => $node->title));

  /*
   * copy logo field
   */
  if (isset($node->field_images['und']) && isset($node->field_images['und'][0]['fid']) && !empty($node->field_images['und'][0]['fid'])) {
      $fids = $node->field_images['und'][0]['fid'];
      $result = file_load_multiple(array($fids));
      if (is_array($result) && !empty($result)) {
          foreach ($result as $delta => $fileObj) {
              $filname = $fileObj->filename;
              $objFile = file_copy($fileObj, $destination = 'private://' . $filname, $replace = FILE_EXISTS_RENAME);
              if ($objFile) {
                  unset($node->field_images['und']);
                  $node->field_images['und'][0] = (array) $objFile;
              }
          }
      }
  }

  /*
   * Update Documents file field
   */
  $DocFielCollid = array();
  if (isset($node->field_rfp_documents['und']) && isset($node->field_rfp_documents['und'][0]['value']) && !empty($node->field_rfp_documents['und'][0]['value'])) {
      $is_documents = 1;
      foreach ($node->field_rfp_documents['und'] as $delta => $item) {
          $DocFielCollid[] = field_collection_item_load($item['value']);
      }
      unset($node->field_rfp_documents['und']);
  }

  node_save($node);
  $rnid = $node->nid;
  $projectPath = 'node/' . $rnid;
  drupal_goto($projectPath);
}

/*
 * Menu callback for peoplebookmark/delete/%/%
 */

function peoplebookmark_delete($confirmed, $uid) {
  global $user;
  $fusername = _get_user_full_name($uid);
  if (!$confirmed) {
    echo '
    <form id="cust-remove-people-bookmark">
      <div class="form-title"><h2>Do you really want to delete bookmark <em class="placeholder">' . $fusername . '</em>?</h2></div>
      <div class="form-content">
        <a href="/peoplebookmark/delete/1/' . $uid . '" id="ok-delete">OK</a>
        <a href="" id="cancel-delete">Cancel</a>
         </div>
    </form>';
  } else {
    $flag = flag_get_flag('people_bookmark');
    if ($flag && $flag->is_flagged($uid)) {
        $flag->flag('unflag', $uid, $user, TRUE);
    }
    echo 1;
  }
}

/**
 * Menu callback for favorite-content-new-people
 */
function _generate_bookmark_fav_block_content_ajax_new_people() { //// new people change
  drupal_json_output(array(
      'html' => favorite_content_generator_people(TRUE),
  ));
}

/**
 * Menu callback for favorite-content-new
 */
function _generate_bookmark_fav_block_content_ajax_new() {
  drupal_json_output(array(
      'html' => _generate_bookmark_fav_block_content_new(),
  ));
}


/**
 * Menu callback for interested-bidders/%node
 */
function project_interested_bidders_tab($entity) {
  global $user,$company;

  $cmpcall = in_array($user->uid, _get_current_company_users($entity->uid));
  $cmpcall2 = in_array($user->uid, loadadinitation_project_user($entity->nid));

  if ($entity->uid == $user->uid || $cmpcall || $cmpcall2) {
    $output = '';
    $nid = $entity->nid;
    $node = $entity;
    $items = field_get_items('node', $node, 'field_pro_bidding_info');
    $output .= '<div class="Bidding-fc-list">';

    $output .= '<div class="form-group"><div class="row-blue-label form-group clearfix">';

    $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
    $output .= '<label>' . t('Anticipated Bid Name:') . '</label>';
    $output .= '</div>';


    $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
    $output .= '<label>' . t('Bid Date:') . '</label>';
    $output .= '</div>';



    $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
    $output .= '<label>' . t('Start:') . '</label>';
    $output .= '</div>';


    $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
    $output .= '<label>' . t('Complete:') . '</label>';
    $output .= '</div>';

    $output .= '</div>';
    $output .= '</div>';



    foreach ($items as $item) {
      $fc = field_collection_field_get_entity($item); //pre($fc);  
      $itemid = $fc->item_id;
      $output .= '<div class="form-group"><div class="row-blue-label form-group clearfix">';
      $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
      //$output .= '<label>' . t('Anticipated Bid Name:') . '</label>';
      $output .= '<div class="Cust-bidfc-data">';
      $output .= (isset($fc->field_proj_bid_name['und'])) ? $fc->field_proj_bid_name['und'][0]['value'] : '';
      $output .= '</div>';
      $output .= '</div>';

      $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
      //  $output .= '<label>' . t('Bid Date:') . '</label>';
      $output .= '<div class="Cust-bidfc-data">';
      $biddateval = (isset($fc->field_proj_bid_date['und'])) ? $fc->field_proj_bid_date['und'][0]['value'] : '';
      $dtstmp = !empty($biddateval) ? strtotime($biddateval) : '';
      $output .= date("j F Y", $dtstmp);
      $output .= '</div>';
      $output .= '</div>';

      $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
      //$output .= '<label>' . t('Start:') . '</label>';
      $output .= '<div class="Cust-bidfc-data">';
      $biddateval1 = (isset($fc->field_proj_start_date['und'])) ? $fc->field_proj_start_date['und'][0]['value'] : '';
      $dtstmp1 = !empty($biddateval1) ? strtotime($biddateval1) : '';
      $output .= date("j F Y", $dtstmp1);
      $output .= '</div>';
      $output .= '</div>';

      $output .= '<div class="col-md-3 col-sm-3 col-xs-12 field-group-div">';
      // $output .= '<label>' . t('Complete:') . '</label>';
      $output .= '<div class="Cust-bidfc-data">';
      $biddateval2 = (isset($fc->field_proj_complete_date['und'])) ? $fc->field_proj_complete_date['und'][0]['value'] : '';
      $dtstmp2 = !empty($biddateval2) ? strtotime($biddateval2) : '';
      $output .= date("j F Y", $dtstmp2);
      $output .= '</div>';
      $output .= '</div>';

      $output .= '</div>'; // .row

      $output .= '<div class="row">';
      $output .= '<div class="col-md-12 col-sm-12 col-xs-12">';
      $output .= '<label>' . t('Bidding Companies:') . '</label>';
      $query2 = db_select('flagging', 'f')->fields('f', array('uid'))->condition('entity_id', $itemid, '=')->condition('entity_type', 'field_collection_item', '=');
      $result2 = $query2->execute();

      while ($record2 = $result2->fetchAssoc()) {
        $counterc = 0;
        $uid = $record2['uid'];
        $gids = _get_user_company_nid($uid);

        if (!empty($gids)) {
          $counterc++;
          $gnode =  _get_title_of_node($gids);
          $output .= '<div class="bid-co-name">' . $gnode . '</div>';
        }
        else {
          if ($counterc == 0) {
            $output .= '<br/>At this time, no companies have selected that they will be bidding on this RFP.';
          }
        }
      }

      $output .= '</div>';
      $output .= '</div></div>'; // .row .form-group
    }
    $output .= '</div>';

    $output .= '<div class="projects-steps-actions">';
    if (isset($_REQUEST['action']) && $_REQUEST['action'] == 'create') {
      $output .= l('<input name="button" type="submit" value="Back" class="form-submit">', '/project-interested-companies/' . arg(1), array('html' => TRUE, 'query' => array('action' => 'create')));
      if (isset($company->field_multi_company_collaboratio['und']) && $company->field_multi_company_collaboratio['und'][0]['value'] == 1) { 
        $output .= l('<input name="button" type="submit" value="Next" class="form-submit">', '/project-collaboration/' . arg(1), array('html' => TRUE, 'query' => array('action' => 'create')));
      }
      else {
        $output .= l('<input name="button" type="submit" value="Next" class="form-submit">', '/project-rfps/' . arg(1), array('html' => TRUE, 'query' => array('action' => 'create')));
      }
    }
    else {
      $output .= l('<input name="button" type="submit" value="Delete" class="form-submit cancel-button">', 'node/' . arg(1) . '/delete', array('html' => TRUE, 'attributes' => array()));
    }
    $output .= '</div>';
  }
  return $output;
}

/**
 * Menu callback for project-collaboration/%node
 */
function project_collaboration_tab($node) {
  $project_collaborat = rfp_find_companies_project();
  return $project_collaborat;
}

/**
 * Menu callback for project-rfps/%node
 */
function project_rfps_tab($node) {
  return views_embed_view('project_s_rfp_tab', 'block');
}

/**
 * Menu callback for project-interested-companies/%node
 */
function project_interested_companies_tab($entity) {  
  global $user, $company;  
  $output = '';
  $CurrCompNid = isset($_SESSION['company']) ? $_SESSION['company'] : '';
  $CompNode = node_load($CurrCompNid);

  $nid = $entity->nid;
  $nuid = $entity->uid;

  $cmpcall = in_array($user->uid, _get_company_users_by_group_company($CompNode));
  $cmpcall2 = in_array($user->uid, loadadinitation_project_user($entity));

  if ($user->uid == $nuid || $cmpcall || $cmpcall2) {
    $query = db_select('flagging', 'fl');
    $query->fields('fl', array('uid'));
    $query->condition('fl.entity_id', $nid);
    $result = $query->execute();

    while ($record = $result->fetchAssoc()) {
      $userids[] = $record['uid'];
    }

    $output = '<div class="cust-diversity-interested-co">';
    $countcompany = 0;
    foreach ($userids as $k => $uid) {
      $cuser = user_load($uid);
      $user_groups = og_get_groups_by_user($cuser, 'node');
      //pre($user_groups);
      foreach ($user_groups as $n => $gnid) {
        $countcompany++;
        $gnode = node_load($gnid);
        $isCompanyIndividual = is_company_individual_flag($gnid);

        if (!$isCompanyIndividual && $gnode->uid == $uid) {
          $comp = '<div>' . l($gnode->title, 'node/' . $gnid) . '</div>';
          break;
        }
        elseif ($isCompanyIndividual && $gnode->uid == $uid) {
          $comp = '<div>' . l($gnode->title, 'node/' . $gnid) . '</div>';
        }
      }
      $output .= $comp;
    }    
    if ($countcompany == 0) {
      $output .= '<div>No one has expressed interest in the project.</div>';
    }
    $output .= '</div>';


    $output .= '<div class="projects-steps-actions">';
    //$output .= $_REQUEST['action'];
    if (isset($_REQUEST['action']) && $_REQUEST['action'] == 'create') {
      $output .= l('<input name="button" type="submit" value="Back" class="form-submit">', '/invite-companies/' . arg(1), array('html' => TRUE, 'query' => array('action' => 'create')));
      $output .= l('<input name="button" type="submit" value="Next" class="form-submit">', '/interested-bidders/' . arg(1), array('html' => TRUE, 'query' => array('action' => 'create')));
    }
    else {
      $output .= l('<input name="button" type="submit" value="Delete" class="form-submit cancel-button">', 'node/' . arg(1) . '/delete', array('html' => TRUE, 'attributes' => array()));
    }
    $output .= '</div>';
  }
  return $output;
}

/**
 * Menu callback for customaction/node/%/delete/%ctools_js
 */
function custom_node_delete_pupup_form($node_nid = FALSE, $action = FALSE, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'node_nid' => $node_nid,
      'action'=> $action
    );

    $output = ctools_modal_form_wrapper('custom_node_delete_pupup_action_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }

    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('custom_node_delete_pupup_action_form', $node_nid,$action);
}

/**
 * Menu callback for
 */
function get_filter_selection_data($type) {
  print $_SERVER['QUERY_STRING'];
  exit;

  $stype = isset($_POST['stype']) ? $_POST['stype'] : 0;
  $qstr = isset($_POST['qstr']) ? $_POST['qstr'] : 0;
  $sfname = isset($_POST['sfname']) ? $_POST['sfname'] : 0;
  $sfval = isset($_POST['sfval']) ? $_POST['sfval'] : 0;
  $slots = '';
  if ((!empty($stype)) && (!empty($qstr)) && (!empty($sfname)) && (!empty($sfval))) {
    //
  }
  exit();
}