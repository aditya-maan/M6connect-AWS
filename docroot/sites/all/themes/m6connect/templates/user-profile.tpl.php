<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>

<script type="text/javascript" src="/<?php echo drupal_get_path('module', 'm6connect_delegate') . '/masonry.pkgd.min.js' ?>"></script>
<?php
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
module_load_include('inc', 'user_relationships', 'user_relationships_ui/user_relationships_ui.pages');
global $user, $base_url;
$cuser = user_load(arg(1));
$cuser_groups = og_get_groups_by_user($cuser, 'node');
$companyNids = array_values($cuser_groups);
$companyNode = node_load($companyNids[0]);
$job_title_tid = $cuser->field_job_titles['und'][0]['target_id'];

	if(isset($job_title_tid)){
		$job_title_term = taxonomy_term_load($job_title_tid);
		$job_title_name = $job_title_term->name;
	}
//pre($name,1);
?>
<?php /* ?><article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>><?php */ ?>
<?php if (isset($title_prefix) || isset($title_suffix) || isset($display_submitted) || isset($unpublished) || !isset($page) && isset($title)): ?>

<header> <?php print render($title_prefix); ?>
  <?php if (!$page && $title): ?>
  <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($display_submitted): ?>
  <p class="submitted"> <?php print $cuser_picture; ?> <?php print $submitted; ?> </p>
  <?php endif; ?>
  <?php if ($unpublished): ?>
  <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
  <?php endif; ?>
</header>
<?php endif; ?>
<?php
// We hide the comments and links now so that we can render them later.
hide($content['comments']);
hide($content['links']);
//    print render($content);
//******************************* Node content start *********************************//
?>
<!-----------friends button on share/newsfeed--start----- -->

<div class="company-list-contaner share-container userprofilepage">
  <div class="dropdown"> <a id="dLabel2" class="btn btn-default" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">My Connections</a>
    <ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel2">
      <?php
            $connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
            foreach ($connections as $connection) {
                ?>
      <li><?php echo l(ucfirst($connection->title), 'switch-dashboard/connection/' . $connection->nid . '/nojs', array('html' => TRUE, 'attributes' => array('title' => $connection->title, 'class' => 'use-ajax'))); ?></li>
      <?php }
            ?>
      <li><a href="javascript:"> Colleagues</a>
        <ul class="user-companies">
          <?php
                    $user_companys = array();
                    $companies_detail1 = m6connect_misc_get_user_all_companies($user->uid);
                    foreach ($companies_detail1 as $com) {
                        if ($com->field_type_of_company_value == 'company') {
                            $user_companys[] = $com->nid;
                            ?>
          <li><?php echo l(ucfirst($com->title), 'switch-dashboard/company/' . $com->nid . '/nojs', array('html' => TRUE, 'attributes' => array('title' => $com->title, 'class' => 'use-ajax'))); ?></li>
          <?php
                        }
                    }
                    ?>
        </ul>
      </li>
      <?php /*?>      <hr/>
      <li><a href="javascript:"> Groups</a>
        <ul class="user-companies">
          <?php
                    $groups = m6connect_misc_get_user_all_companies($user->uid, 'groups');
                    foreach ($groups as $group) {
                        if ($group->group_access_value == 0) {
                            ?>
          <li><?php echo l(ucfirst($group->title), 'switch-dashboard/group/' . $group->nid . '/nojs', array('html' => TRUE, 'attributes' => array('title' => $group->title, 'class' => 'use-ajax'))); ?></li>
          <?php
                        }
                    }
                    ?>
        </ul>
      </li><?php */?>
    </ul>
  </div>
</div>

<!----------- friends button on share/newsfeed--end----- -->

<div class='company-page'>
  <div class='company-profile-content-area2 clearfix'>
    <div class="tab-content">
      <div role="tabpanel" class="tab-pane fade" id="photos">
        <div class='photos'>
          <div class="post-heading clearfix">Photos</div>
          <div class="dashboard-block-content">
            <div class="user-connection-outer row margin-5 grid js-masonry">
              <?php
			$cid = arg(1);
			$fids = fn_get_own_shared_images($cid);
			foreach ($fids as $key) {
              $share_photo = file_load($key);
			  $share_photo_url = image_style_url('user_photo_tab_162',$share_photo->uri);
			  
				//echo '<div class="grid-item"><a href="javascript:"  data-toggle="modal" data-target="#myModal" onclick="updateimage(\'/download/attachments/' . $key . '\')" ><img src="/download/attachments/' . $key . '" alt="photo" /></a></div>';
				echo '<div class="grid-item"><a href="javascript:"  data-toggle="modal" data-target="#myModal" onclick="updateimage(\'/download/attachments/' . $key . '\')" ><img src="' . $share_photo_url . '" alt="photo" /></a></div>';
			}
			?>
            </div>
          </div>
        </div>
      </div>
      <div role="tabpanel" class="tab-pane fade" id="resume">
        <div class='resume'>
          <div class="post-heading clearfix">Coming soon!</div>
          <!-- <div class="dashboard-block-content"> Resume </div> -->
        </div>
      </div>
      <div role="tabpanel" class="tab-pane fade" id="portfolio">
        <div class='portfolio'>
          <div class="post-heading clearfix">Coming soon!</div>
          <!-- <div class="dashboard-block-content"> portfolio </div> -->
        </div>
      </div>
      <?php
      // Preparing first name.
      $u_user = user_load(arg(1));
      $u_name = $u_user->name;
      $u_name = ucfirst($u_name);
      if (!empty($u_user->field_first_name['und'][0]['value'])) {
        $u_name = $u_user->field_first_name['und'][0]['value'];
        $u_name = ucfirst($u_name);
      }
      ?>
      <div role="tabpanel" class="tab-pane fade" id="friends">
        <div class='friends'>
          <div class="post-heading clearfix"><?php print $u_name; ?> needs to send a friend request.</div>
          <!-- <div class="dashboard-block-content"> Friends </div> -->
        </div>
      </div>
      
       <div role="tabpanel" class="tab-pane fade" id="skillset">
        <div class="skillset">
          <!-- <div class="post-heading clearfix">skill</div> -->
          <div class="dashboard-block-content">
          <?php 
		  
		    $profileaddskillset = drupal_get_form('add_your_skill_custom_form');
			//$profileaddskillset = module_invoke('m6connect_delegate', 'block_view', 'personal-profile-add-skill-set');
			print render($profileaddskillset); 
		  ?>
          </div>
        </div>
      </div>
      
      <div role="tabpanel" class="tab-pane fade" id="viewmoreabout">
        <div class='viewmoreabout company-profile-content-area'>
          <div class="post-heading clearfix">About
            <?php
			  if (arg(0) == 'user' && is_numeric(arg(1)) && !arg(2)) {
				  if ($user->uid == arg(1)) {
					  print '<div class="pull-right"><a role="tab" href="#viewmoreaboutedit" data-toggle="tab" aria-controls="View More" aria-expanded="true"><i class="fa fa-cog"></i></a></div>';
				  }
			  }
			  ?>
          </div>
          <div class="dashboard-block-content block-block-68 about-view">
            <?php
			  if (arg(0) == 'user' && is_numeric(arg(1)) && empty(arg(2))) {
				  $cuser1 = user_load(arg(1));
				  // pre($cuser1,1);
				  $field_address = field_view_field('user', $cuser1, 'field_address', array('label' => 'hidden'));
				  $user_address = render($field_address);
				  if (!empty($cuser1->field_address['und'][0]['administrative_area'])) {
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-map-marker"></i></div><div class="pull-right"><div class="field">Lives in ' . $cuser1->field_address['und'][0]['locality'] . ', ' . $cuser1->field_address['und'][0]['administrative_area'] . '</div></div></div>';
				  }
				  //$field_job_titles = field_view_field('user', $cuser1, 'field_job_titles', array('label' => 'hidden'));
				  //$user_job_titles = render($field_job_titles);
				  $user_job_titles = $cuser1->field_user_title['und'][0]['value'];

				  /*if (!empty($cuser1->field_job_titles['und'])) {
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-briefcase"></i></div><div class="pull-left">' . $user_job_titles . '</div></div>';
				  }*/
				  if (!empty($cuser1->field_user_title['und'][0]['value'])) {
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-briefcase"></i></div><div class="pull-right"><div class="field">' . $user_job_titles . '</div></div></div>';
				  }
				  
				  $field_user_company_name = field_view_field('user', $cuser1, 'field_user_company_name', array('label' => 'hidden'));
				  $user_company_name = render($field_user_company_name);

				  if (!empty($cuser1->field_user_company_name['und'][0]['value'])) {

					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-building-o"></i></div><div class="pull-right">' . $user_company_name . '</div></div>';
				  }
				  $field_user_qualification = field_view_field('user', $cuser1, 'field_user_qualification', array('label' => 'hidden'));
				  $user_qualification = render($field_user_qualification);
				  if (!empty($cuser1->field_user_qualification['und'][0]['value'])) {
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-university"></i></div><div class="pull-right">' . $user_qualification . '</div></div>';
				  }
				  $field_date_of_birth = field_view_field('user', $cuser1, 'field_date_of_birth', array('label' => 'hidden'));
				  $user_dob = render($field_date_of_birth);
				  if (!empty($cuser1->field_date_of_birth['und'][0]['value'])) {
					  $date1 = $cuser1->field_date_of_birth['und'][0]['value'];
					  $date2 = date('l j F Y');
					  $diff = abs(strtotime($date2) - strtotime($date1));
					  $years = floor($diff / (365 * 60 * 60 * 24));

					  $dob_day = array("Monday, ", "Tuesday, ", "Wednesday, ", "Thrusday, ", "Friday, ", "Saturday, ", "Sunday, ");
					  $user_dob_new = str_replace($dob_day, "", $user_dob);
if(isset($cuser1->field_hide_date_of_birth['und']) && empty($cuser1->field_hide_date_of_birth['und'][0]['value'])){
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-calendar"></i></div><div class="pull-right">' . $user_dob_new . '(' . $years . ' years old)</div></div>';
				  }
				  }
			  }
			  ?>
          </div>
        </div>
      </div>
      <div role="tabpanel" class="tab-pane fade" id="viewmoreaboutedit">
        <div class='viewmoreaboutedit'>
          <div class="post-heading clearfix margin-top-10 padding-5" style="border-bottom:1px solid #888;"><strong>About</strong><p>Add some basic information about yourself to help increase your visibility</p></div>
          <div class="dashboard-block-content about-view">
            <?php
		  if (arg(0) == 'user' && is_numeric(arg(1)) && !arg(2)) {
			  if ($user->uid == arg(1)) {
				  $custom_profile_about_edit_form = drupal_get_form('custom_profile_about_edit_form');
				  print drupal_render($custom_profile_about_edit_form);
			  }
		  }
		  ?>
          </div>
        </div>
      </div>
      <div role="tabpanel" class="tab-pane fade" id="viewmoreinfo">
        <div class='viewmoreinfo company-profile-content-area'>
          <div class="post-heading clearfix">Contact Information
            <?php
			if (arg(0) == 'user' && is_numeric(arg(1)) && !arg(2)) {
				if ($user->uid == arg(1)) {
					print '<div class="pull-right"><a role="tab" href="#viewmoreinfoedit" data-toggle="tab" aria-controls="View More" aria-expanded="true"><i class="fa fa-cog"></i></a></div>';
				}
			}
			?>
          </div>
          <div class="dashboard-block-content about-view block-block-68">
            <?php
			  if (arg(0) == 'user' && is_numeric(arg(1)) && empty(arg(2))) {
				  $cuser1 = user_load(arg(1));
				  if ($cuser1->mail) {
					  print '<div class="pull-outer clearfix margin-bottom-10"><div style="width: 12%;float: left!important;">Personal:</div><div class="pull-right"><div class="field"><a href="mailto:' . $cuser1->mail . '">' . $cuser1->mail . '</a></div></div></div>';
				  }
				  $field_phone = field_view_field('user', $cuser1, 'field_phone', array('label' => 'hidden'));
				  $user_phone = render($field_phone);
				  if (!empty($cuser1->field_phone['und'][0]['value'])) {
					$phoneNumber = $cuser1->field_phone['und'][0]['value'];
					$phoneNumberval = get_international_formatPhoneNumber($phoneNumber);
				    if(isset($cuser1->field_hide_phone_number['und']) && empty($cuser1->field_hide_phone_number['und'][0]['value'])){
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-phone"></i></div><div class="pull-right"><div class="field"><a href="tel:' .  $phoneNumberval . '">' .  $phoneNumberval . '</a></div></div></div>';
				     }
			     }
				  $field_facebook_url = field_view_field('user', $cuser1, 'field_facebook_url', array('label' => 'hidden'));
				  $user_facebook = render($field_facebook_url);
				  if (!empty($cuser1->field_facebook_url['und'][0]['value'])) {
					  $str_user_facebook = str_replace("http://", "", $user_facebook);
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-facebook-official"></i></div><div class="pull-right">' . $str_user_facebook . '</div></div>';
				  }
				  $field_twitter_url = field_view_field('user', $cuser1, 'field_twitter_url', array('label' => 'hidden'));
				  $user_twitter = render($field_twitter_url);
				  if (!empty($cuser1->field_twitter_url['und'][0]['value'])) {
					  $str_user_twitter = str_replace("http://", "", $user_twitter);
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-twitter"></i></div><div class="pull-right">' . $str_user_twitter . '</div></div>';
				  }
				  $field_linkedin_url = field_view_field('user', $cuser1, 'field_linkedin_url', array('label' => 'hidden'));
				  $user_linkedin = render($field_linkedin_url);
				  if (!empty($cuser1->field_linkedin_url['und'][0]['value'])) {
					  $str_user_linkedin = str_replace("http://", "", $user_linkedin);
					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-linkedin"></i></div><div class="pull-right">' . $str_user_linkedin . '</div></div>';
				  }
				  $field_behance_url = field_view_field('user', $cuser1, 'field_behance_url', array('label' => 'hidden'));
				  $user_behance = render($field_behance_url);

				  if (!empty($cuser1->field_behance_url['und'][0]['value'])) {
					  $str_user_behance = str_replace("http://", "", $user_behance);

					  print '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left"><i class="fa fa-behance"></i></div><div class="pull-right">' . $str_user_behance . '</div></div>';
				  }

				  $user_detail = _get_companies_details_by_user_uid($cuser1->uid);
				  $hidecom = _get_company_hide_on_userprofile($cuser1->uid);
				  
				  //drup_msg($user_detail);
				  
			    foreach($user_detail as $userDetail){
				  if(!in_array($userDetail->nid,$hidecom)){	
					  echo '<div class="pull-outer clearfix margin-bottom-10"><div class="pull-left">';
					  if (isset($userDetail->uri)) 
					  {
						echo '<img src="' . image_style_url('pic_20x20', $userDetail->uri) . '">';
					  }
					  else
					  {
						echo '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" style="width:20px;height:20px;">';
					  }
					  echo '</div><div class="pull-right"><div class="field">'.l($userDetail->title, 'node/'.$userDetail->nid).'|<a href="mailto:'.$userDetail->company_email.'">'.$userDetail->company_email.'</a></div></div></div>';
				  }
			    }
			  }
			  ?>
          </div>
        </div>
      </div>
      <!-- For start viemore cres -->
       <div role="tabpanel" class="tab-pane fade" id="viewmorecres">
        <div class='viewmorecres'>
          <div class="post-heading clearfix">Credentials</div>
            <div class="dashboard-block-content moreinfo-view">
            <?php
			 $userProfileUid = arg(1);
			 $onBoardingNid = get_user_onboarding_nid($userProfileUid); 
			 $creViewMore = user_Profile_credentials_viewmore($onBoardingNid);
			 print $creViewMore; 
			 ?>
	 
            </div>
        </div>
      </div>
      <!--For viemore cres End here -->
      <!-- start add new Credentials -->
      <div role="tabpanel" class="tab-pane fade" id="addcredentials">
        <div class='addcredentials'>          
          <div class="dashboard-block-content moreinfo-view">
          <?php
          if (arg(0) == 'user' && is_numeric(arg(1)) && !arg(2)) {
			if($user->uid == arg(1)){ 
			  $currentUser = $cuser;
			  $currentTab = 'm6id-info';
			  $contentCredentials = '';
			  module_load_include('inc', 'node', 'node.pages');
			  $m6id_node = (object) array(
				'uid' => $currentUser->uid,
				'name' => (isset($currentUser->name) ? $currentUser->name : ''),
				'type' => 'onboarding',
				'language' => LANGUAGE_NONE,
			  );
			  node_object_prepare($m6id_node);
			  $m6id_node->uid = $currentUser->uid;
				if($obnid = get_user_onboarding_nid($currentUser->uid)){
				  $m6id_node = node_load($obnid);	
				}
			  $m6id_node->user_profile_credental =1;	
			  $m6idform = drupal_get_form('onboarding_node_form', $m6id_node);
			  $contentCredentials =  drupal_render($m6idform);
			  print $contentCredentials;
			}
		  }           
          ?>   
          </div>
        </div>
      </div>
      <!-- add new Credentials End here -->
      <div role="tabpanel" class="tab-pane fade" id="viewmoreinfoedit">
        <div class='viewmoreinfoedit'>
          <div class="post-heading clearfix">Contact Information</div>
          <div class="dashboard-block-content moreinfo-view">
            <?php
			  if (arg(0) == 'user' && is_numeric(arg(1)) && !arg(2)) {
				  if ($user->uid == arg(1)) {
					  $custom_profile_contact_information_edit_form = drupal_get_form('custom_profile_contact_information_edit_form');
					  print drupal_render($custom_profile_contact_information_edit_form);
				  }
			  }
			  ?>
          </div>
        </div>
      </div>
      <div role="tabpanel" class="tab-pane fade" id="viewmconnections" >
        <div class="viewmconnections-section-middle">
          <div class="post-heading clearfix">
            <div class="row margin-5">
              <div class="col-sm-3 col-xs-3 padding-5 block-title">Connections</div>
              <div class="col-sm-8 col-xs-8 padding-5 connection-search">
                <?php
				$custom_connections_search_form = drupal_get_form('custom_connections_search_form');
				print drupal_render($custom_connections_search_form);
				?>
              </div>
              <div id="newsfeed-open1" title="Close" class="col-sm-1 col-xs-1 padding-5 connection-close text-center">X</div>
            </div>
          </div>
          <?php $connections = m6connect_misc_get_groups_by_ownerid(arg(1), 'connection_categories'); ?>
          <div class="dashboard-block-content">
            <div class="clearfix nav-tabs">
              <div class="form-inline margin-bottom-10">
                <div class="form-group user-connection-filter">
                  <?php
                  //$connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
                  $connections_filter = '<select class="form-control connction-catg-filter">';
                  $connections_filter .=	'<option selected value="#ucr_all">All</option>';
                    foreach ($connections as $connection) {										
                      $connections_filter .=	'<option '.$selected.' value="#ucrc_tab_'.$connection->nid.'">'.ucfirst($connection->title).'</option>';
                    }
                  $connections_filter .=	'<option '.$companymembers.' value="#ucr_colleagues">Company Members</option>';
                  $connections_filter .= '</select>';									
                  print '<label>Filter:</label> '.$connections_filter;								
                  ?>
                  <ul role="tablist" class="nav nav-tabs" style="display:none;">
                    <li class="connection-filter">Filter: </li>
                    <li class="active"><a role="tab" href="#ucr_all" data-toggle="tab" aria-controls="Newsfeed">All</a></li>
                    <?php
                    foreach ($connections as $connection) {
                      echo '<li><a role="tab" href="#ucrc_tab_' . $connection->nid . '" data-toggle="tab" aria-controls="' . $connection->title . '">' . $connection->title . '</a></li>';
                    }
                    ?>
                    <li><a role="tab" href="#ucr_colleagues" data-toggle="tab" aria-controls="photos">Colleagues</a></li>
                  </ul>
                </div>
              </div>
            </div>
            <div class="tab-content">
              <div role="tabpanel" class="myall-tab tab-pane fade active in" id="ucr_all" >
                <div class="viewmconnections1">
                  <?php
					if (arg(0) == 'user' && is_numeric(arg(1)) && empty(arg(2))) {
						$crequestee_id = arg(1);

						$relationships = user_relationships_load(array('approved' => $user->uid, 'approved' => TRUE, 'requestee_id' => $crequestee_id));

						$user_cats = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
						$user_category_nid = array();
						foreach ($user_cats as $user_cat) {
							$user_category_nid[] = $user_cat->nid;
						}
						//$result = array();
						echo '<div class="user-connection-outer row margin-5">';
						$count = 1;
						foreach ($relationships as $relationship) {
							$relationship->requester_id;
							$rcuser = user_load($relationship->requester_id);
							//$relationship_action = user_relationships_ui_get_table_row($relationship, arg(1));
							//$relationships = user_relationships_load(array('approved' => $user->uid, 'approved' => FALSE, 'requestee_id' => $crequestee_id));

							$job_title_tid = isset($rcuser->field_job_titles['und'][0]) ? $rcuser->field_job_titles['und'][0]['target_id'] : '';
							$job_title_name = '';
							if ($job_title_tid != '') {
								$job_title_term = taxonomy_term_load($job_title_tid);
								$job_title_name = $job_title_term->name;
							}


							$output = ' <div class="col-md-4 col-sm-4 col-xs-12 padding-5 margin-bottom-10 user-connection-inner">';
							$output .= '<a href="/user/' . $rcuser->uid . '">';
							$output .='<div class="section1 clearfix">';
							$rcuser_profile_photo = (isset($rcuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'connection_image_all_152_120', 'path' => $rcuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : '';
							if ($rcuser_profile_photo) {
								$output .= $rcuser_profile_photo;
							} else {
								$output .= '<img class="profile_image_152_120" alt="" src="' . $base_url . '/sites/default/files/default_profile.jpg" typeof="foaf:Image">';
							}
							$output .='</div>';
							$output .='</a>';
							$output .='<div class="section2 clearfix">';
							$output .= '<a href="/user/' . $rcuser->uid . '">';
							$output .= $rcuser->realname . '<br>';
							$output .='</a>';
							/*  * ***********assign category***start***************** */
							/*$conn1 = m6connect_misc_get_user_all_companies($rcuser->uid, 'connection_categories');
							$connectedUserConnections = array();
							foreach ($conn1 as $conn2) {
								$connectedUserConnections[] = $conn2->nid;
							}
							if (count(array_intersect($connectedUserConnections, $user_category_nid)) > 0) {//
								$related_group = array_intersect($connectedUserConnections, $user_category_nid);
								foreach ($related_group as $data) {
									$outputs = node_load($data)->title;
								}
								if ($rcuser->uid != $user->uid) {
									$output .= '<div class="assigned-category">' . $outputs . '</div>';
								}
								//                                                         
							} else if ($user->uid == $crequestee_id) {
								$output .= '<div class="assign-category"><a class="use-ajax" href="/assign_connection_category/' . $user->uid . '/' . $rcuser->uid . '/nojs">assign category</a></div>';
							}
							*/ /*     ***********assign category***end***************** */
							$output .= '<div class="connection-overflow clearfix">';
							/** ********************connect button***strt************ */
							//$cms_value = connection_member_status($rcuser->uid);
							/*$cms_value = connection_member_status_button($user->uid,$rcuser->uid);
							if($cms_value['button'] == 'Connect'){
							 $output .= '<span class="connection-connect pull-left"><a class="user_relationships_popup_link" href="/relationship/' . $rcuser->uid . '/request/5?destination=user/' . $rcuser->uid . '"><i class="fa fa-arrow-circle-o-right"></i> Connect</a></span>';

							}else if( $user->uid == $rcuser->uid){
								$output .= '<span class="you-connected"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
							}else{
								$output .= '<span class="you-connected"><i class="fa fa-arrow-circle-o-right"></i> '.$cms_value['button'].'</span>';
							}*/			
							$myuserid = $user->uid;
							$mycuserid = $rcuser->uid;
							$status_btn = connection_member_status_button($myuserid,$mycuserid);
							
							if($myuserid != $mycuserid ){
								if(isset($status_btn['button']) && $status_btn['button'] == 'Connect'){
								 	$links = array();
									$connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
									$cat_array = array('Clients','Prospects','Sales Associates','Acquaintances','Business Associates','Friends');
									foreach ($connections as $connection) {
										$cat_title ='';
										if(in_array($connection->title,$cat_array)){
											
											if($connection->title=='Clients'){
												$cat_title = 'People that you consider a client or are current clients';
											}
											if($connection->title=='Prospects'){
												$cat_title = 'People you are pursing for business';
											}
											if($connection->title=='Sales Associates'){
												$cat_title = 'People who are pursuing you for business';
											}
											if($connection->title=='Acquaintances'){
												$cat_title = 'General people you meet';
											}
											if($connection->title=='Business Associates'){
												$cat_title = 'People you commonly work with';
											}
											if($connection->title=='Friends'){
												$cat_title = 'Friends & Family';
											}
										}else{
											$cat_title = $connection->title;
										}
										
										$links[] = array('title' => ucfirst($connection->title), 'href' => 'connect/category/'.$connection->nid.'/request/'.$myuserid.'/'.$mycuserid.'/nojs','attributes' => array('class'=>array('title'=>$cat_title,'use-ajax')));
									}			
									$connect_category_connect ='<i class="fa fa-arrow-circle-o-right"></i> Connect';
							 
									$user_connect_btn= theme('m6_ctools_dropdown', array('main_title' => $connect_category_connect, 'links' => $links,'image'=>1));
									$output .= '<span class="user-page-cat-connect connection-connect pull-left">'.$user_connect_btn.'</span>';	
									
								}else if($user->uid == $rcuser->uid){
									$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
								}else{
									$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> '.$status_btn['button'].'</span>';
								}										
							}															
							/** ********************connect button***end************ */
							/*                                             * ********************bookmar button***start************ */
							$flag = flag_get_flag('people_bookmark');

							if ($flag && $flag->is_flagged($rcuser->uid)) {
								$output .= '<span class="connection-bookmarked pull-left"><i class="fa fa-bookmark"></i> Bookmarked</span>';
							} else {

								$output .= '<span class="connection-bookmark pull-left"><span class="cust-people-bkmrk">' . flag_create_link('people_bookmark', $rcuser->uid) . '</span></span>';
							}


							/*                                             * ********************bookmar button***end************ */


							$output .= '</div>';



							$output .='</div>';

							$output .='</div>';


							print $output;



							$count ++;
						}

						echo '</div>';
					}
					?>
                </div>
              </div>
              <?php
				foreach ($connections as $connection_with) {
					$connection_groups = m6connect_misc_get_company_users_by_cnid($connection_with->nid);
					echo '<div role="tabpanel" class="tab-pane fade cnnections' . $connection_with->nid . '" id="ucrc_tab_' . $connection_with->nid . '" >';
					echo '<div class="user-connection-outer row viewm' . $connection_with->nid . '">';


					if (in_array($user->uid, $connection_groups)) {

						$cuser_connections = array_diff($connection_groups, array($user->uid));

						foreach ($cuser_connections as $cuser_connection) {



							$rcuser = user_load($cuser_connection);
							//$relationship_action = user_relationships_ui_get_table_row($relationship, arg(1));



							$job_title_tid = $rcuser->field_job_titles['und'][0]['target_id'];
								if(isset($job_title_tid)){
									$job_title_term = taxonomy_term_load($job_title_tid);
									$job_title_name = $job_title_term->name;
								}

							$output = ' <div class="user-connection-inner margin-bottom-10 margin-top-10 col-md-4 col-sm-4 col-xs-12">';
							$output .= '<a href="/user/' . $rcuser->uid . '">';
							$output .='<div class="section1">';
							$rcuser_profile_photo = (isset($rcuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'connection_image_all_152_120', 'path' => $rcuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : '';
							if ($rcuser_profile_photo) {
								$output .= $rcuser_profile_photo;
							} else {
								$output .= '<img class="profile_image_152_120" alt="" src="' . $base_url . '/sites/default/files/default_profile.jpg" typeof="foaf:Image">';
							}
							$output .='</div>';
							$output .='</a>';
							$output .='<div class="section2">';
							$output .= '<a href="/user/' . $rcuser->uid . '">';
							$output .= $rcuser->realname . '<br>';
							$output .='</a>';



							$output .= '<div class="connection-overflow clearfix">';
							/** ********************connect button***strt************ */
							//$cms_value = connection_member_status($rcuser->uid);
							/*$cms_value = connection_member_status_button($user->uid,$rcuser->uid);
																			
						if($cms_value['button'] == 'Connect'){
							 $output .= '<span class="connection-connect pull-left"><a class="user_relationships_popup_link" href="/relationship/' . $rcuser->uid . '/request/5?destination=user/' . $rcuser->uid . '"><i class="fa fa-arrow-circle-o-right"></i> Connect</a></span>';

						}else if( $user->uid == $rcuser->uid){
							$output .= '<span class="you-connected"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
						}else{
							$output .= '<span class="you-connected"><i class="fa fa-arrow-circle-o-right"></i> '.$cms_value['button'].'</span>';
						}*/

																							
								$myuserid = $user->uid;
								$mycuserid = $rcuser->uid;
								$status_btn = connection_member_status_button($myuserid,$mycuserid);
								
									if($myuserid != $mycuserid ){
										if(isset($status_btn['button']) && $status_btn['button'] == 'Connect'){
																																							 
										 $links = array();
											$connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
											$cat_array = array('Clients','Prospects','Sales Associates','Acquaintances','Business Associates','Friends');
												foreach ($connections as $connection) {
													$cat_title ='';
															if(in_array($connection->title,$cat_array)){
																
																if($connection->title=='Clients'){
																	$cat_title = 'People that you consider a client or are current clients';
																}
																if($connection->title=='Prospects'){
																	$cat_title = 'People you are pursing for business';
																}
																if($connection->title=='Sales Associates'){
																	$cat_title = 'People who are pursuing you for business';
																}
																if($connection->title=='Acquaintances'){
																	$cat_title = 'General people you meet';
																}
																if($connection->title=='Business Associates'){
																	$cat_title = 'People you commonly work with';
																}
																if($connection->title=='Friends'){
																	$cat_title = 'Friends & Family';
																}
															}else{
																$cat_title = $connection->title;
															}
													
													$links[] = array('title' => ucfirst($connection->title), 'href' => 'connect/category/'.$connection->nid.'/request/'.$myuserid.'/'.$mycuserid.'/nojs','attributes' => array('class'=>array('title'=>$cat_title,'use-ajax')));	
														 
												}			
											$connect_category_connect ='<i class="fa fa-arrow-circle-o-right"></i> Connect';
									 
											$user_connect_btn= theme('m6_ctools_dropdown', array('main_title' => $connect_category_connect, 'links' => $links,'image'=>1));
											$output .= '<span class="user-page-cat-connect connection-connect pull-left">'.$user_connect_btn.'</span>';	
											
										}else if( $myuserid == $mycuserid){
											$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
										}else{
											$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> '.$status_btn['button'].'</span>';
										}
										
									}															
			
							/** ********************connect button***end************ */
							/*                                         * ********************bookmar button***start************ */
							$flag = flag_get_flag('people_bookmark');

							if ($flag && $flag->is_flagged($rcuser->uid)) {
								$output .= '<span class="connection-bookmarked pull-left"><i class="fa fa-bookmark"></i> Bookmarked</span>';
							} else {

								$output .= '<span class="connection-bookmark pull-left"><span class="cust-people-bkmrk">' . flag_create_link('people_bookmark', $rcuser->uid) . '</span></span>';
							}


							/*                                         * ********************bookmar button***end************ */


							$output .= '</div>';

							$output .='</div>';

							$output .='</div>';


							print $output;



							$count ++;
						}
					}




					echo '</div>';
					echo '</div>';
				}
				?>
              <div role="tabpanel" class="tab-pane fade" id="ucr_colleagues" >
                <div class='ucr_colleagues_all'>
                  <ul role="tablist" class="nav nav-tabs">
                    <li class="active"><a role="tab" href="#ucr_c_all" data-toggle="tab" aria-controls="Newsfeed">All</a></li>
                    <?php
					  $companies_detail = m6connect_misc_get_user_all_companies(arg(1));
					  foreach ($companies_detail as $company) {
						  if ($company->field_type_of_company_value == 'company') {
							  echo ' <li><a role="tab" href="#ucr_c_' . $company->nid . '" data-toggle="tab" aria-controls="' . $company->title . '">' . $company->title . '</a></li>';
						  }
					  }
					  ?>
                  </ul>
                  <div class="tab-content">
                    <div role="tabpanel" class="myall-tab tab-pane fade active in" id="ucr_c_all" >
                      <div class="user-connection-outer row viewm'.$connection_with->nid.'">
                        <div class='ucr_c_all'>
                          <?php
							  foreach ($companies_detail as $companies_detail_with) {
								  $connection_groups = m6connect_misc_get_company_users_by_cnid($companies_detail_with->nid);


								  if (in_array($user->uid, $connection_groups)) {

									  $cuser_connections = array_diff($connection_groups, array($user->uid));

									  foreach ($cuser_connections as $cuser_connection) {



										  $rcuser = user_load($cuser_connection);
//                                                                $relationship_action = user_relationships_ui_get_table_row($relationship, arg(1));



										  $job_title_tid = $rcuser->field_job_titles['und'][0]['target_id'];
												if(isset($job_title_tid)){
													$job_title_term = taxonomy_term_load($job_title_tid);
													$job_title_name = $job_title_term->name;
												}

										  $output = ' <div class="user-connection-inner margin-bottom-10  margin-top-10 col-md-4 col-sm-4 col-xs-12">';
										  $output .= '<a href="/user/' . $rcuser->uid . '">';
										  $output .='<div class="section1">';
										  $rcuser_profile_photo = (isset($rcuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'connection_image_all_152_120', 'path' => $rcuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : '';
										  if ($rcuser_profile_photo) {
											  $output .= $rcuser_profile_photo;
										  } else {
											  $output .= '<img class="profile_image_152_120" alt="" src="' . $base_url . '/sites/default/files/default_profile.jpg" typeof="foaf:Image">';
										  }
										  $output .='</div>';
										  $output .='</a>';
										  $output .='<div class="section2">';
										  $output .= '<a href="/user/' . $rcuser->uid . '">';
										  $output .= $rcuser->realname . '<br>';
										  $output .='</a>';


										  $output .= '<div class="connection-overflow clearfix">';
										  /** ********************connect button***strt************ */
										  //$cms_value = connection_member_status($rcuser->uid);

								$myuserid = $user->uid;
								$mycuserid = $rcuser->uid;
								$status_btn = connection_member_status_button($myuserid,$mycuserid);
								
									if($myuserid != $mycuserid ){
										if(isset($status_btn['button']) && $status_btn['button'] == 'Connect'){
																																							 
										 $links = array();
											$connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
											$cat_array = array('Clients','Prospects','Sales Associates','Acquaintances','Business Associates','Friends');
												foreach ($connections as $connection) {
													$cat_title ='';
															if(in_array($connection->title,$cat_array)){
																
																if($connection->title=='Clients'){
																	$cat_title = 'People that you consider a client or are current clients';
																}
																if($connection->title=='Prospects'){
																	$cat_title = 'People you are pursing for business';
																}
																if($connection->title=='Sales Associates'){
																	$cat_title = 'People who are pursuing you for business';
																}
																if($connection->title=='Acquaintances'){
																	$cat_title = 'General people you meet';
																}
																if($connection->title=='Business Associates'){
																	$cat_title = 'People you commonly work with';
																}
																if($connection->title=='Friends'){
																	$cat_title = 'Friends & Family';
																}
															}else{
																$cat_title = $connection->title;
															}
													
													$links[] = array('title' => ucfirst($connection->title), 'href' => 'connect/category/'.$connection->nid.'/request/'.$myuserid.'/'.$mycuserid.'/nojs','attributes' => array('class'=>array('title'=>$cat_title,'use-ajax')));	
														 
												}			
											$connect_category_connect ='<i class="fa fa-arrow-circle-o-right"></i> Connect';
									 
											$user_connect_btn= theme('m6_ctools_dropdown', array('main_title' => $connect_category_connect, 'links' => $links,'image'=>1));
											$output .= '<span class="user-page-cat-connect connection-connect pull-left">'.$user_connect_btn.'</span>';	
											
										}else if( $myuserid == $mycuserid){
											$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
										}else{
											$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> '.$status_btn['button'].'</span>';
										}
										
									}															
			
										  /** ********************connect button***end************ */
										  /*                                                                 * ********************bookmar button***start************ */
										  $flag = flag_get_flag('people_bookmark');

										  if ($flag && $flag->is_flagged($rcuser->uid)) {
											  $output .= '<span class="connection-bookmarked pull-left"><i class="fa fa-bookmark"></i> Bookmarked</span>';
										  } else {

											  $output .= '<span class="connection-bookmark pull-left"><span class="cust-people-bkmrk">' . flag_create_link('people_bookmark', $rcuser->uid) . '</span></span>';
										  }


										  /*                                                                 * ********************bookmar button***end************ */


										  $output .= '</div>';


										  $output .='</div>';

										  $output .='</div>';


										  print $output;



										  $count ++;
									  }
								  }
							  }
							  ?>
                        </div>
                      </div>
                    </div>
                    <?php
					  foreach ($companies_detail as $companies_detail_with) {
						  $connection_groups = m6connect_misc_get_company_users_by_cnid($companies_detail_with->nid);
						  echo '<div role="tabpanel" class="tab-pane fade cnnections' . $companies_detail_with->nid . '" id="ucr_c_' . $companies_detail_with->nid . '" >';
						  echo '<div class="user-connection-outer row viewmc' . $companies_detail_with->nid . '">';


						  if (in_array($user->uid, $connection_groups)) {

							  $cuser_connections = array_diff($connection_groups, array($user->uid));

							  foreach ($cuser_connections as $cuser_connection) {



								  $rcuser = user_load($cuser_connection);
//                                                    $relationship_action = user_relationships_ui_get_table_row($relationship, arg(1));



								  $job_title_tid = $rcuser->field_job_titles['und'][0]['target_id'];
								 								if(isset($job_title_tid)){
									$job_title_term = taxonomy_term_load($job_title_tid);
									$job_title_name = $job_title_term->name;
								}

								  $output = ' <div class="user-connection-inner margin-bottom-10  margin-top-10 col-md-4 col-sm-4 col-xs-12">';
								  $output .= '<a href="/user/' . $rcuser->uid . '">';
								  $output .='<div class="section1">';
								  $rcuser_profile_photo = (isset($rcuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'connection_image_all_152_120', 'path' => $rcuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : '';
								  if ($rcuser_profile_photo) {
									  $output .= $rcuser_profile_photo;
								  } else {
									  $output .= '<img class="profile_image_152_120" alt="" src="' . $base_url . '/sites/default/files/default_profile.jpg" typeof="foaf:Image">';
								  }
								  $output .='</div>';
								  $output .='</a>';
								  $output .='<div class="section2">';
								  $output .= '<a href="/user/' . $rcuser->uid . '">';
								  $output .= $rcuser->realname . '<br>';
								  $output .='</a>';

								  $output .= '<div class="connection-overflow clearfix">';
								  /** ********************connect button***strt************ */
								  //$cms_value = connection_member_status($rcuser->uid);
								/*													  $cms_value = connection_member_status_button($user->uid,$rcuser->uid);
																	  
								  if($cms_value['button'] == 'Connect'){
								   $output .= '<span class="connection-connect pull-left"><a class="user_relationships_popup_link" href="/relationship/' . $rcuser->uid . '/request/5?destination=user/' . $rcuser->uid . '"><i class="fa fa-arrow-circle-o-right"></i> Connect</a></span>';

								  }else if( $user->uid == $rcuser->uid){
								  	$output .= '<span class="you-connected"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
								  }else{
									  $output .= '<span class="you-connected"><i class="fa fa-arrow-circle-o-right"></i> '.$cms_value['button'].'</span>';
								  }*/
																							
								$myuserid = $user->uid;
								$mycuserid = $rcuser->uid;
								$status_btn = connection_member_status_button($myuserid,$mycuserid);
								
									if($myuserid != $mycuserid ){
										if(isset($status_btn['button']) && $status_btn['button'] == 'Connect'){
																																							 
										 $links = array();
											$connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
											$cat_array = array('Clients','Prospects','Sales Associates','Acquaintances','Business Associates','Friends');
												foreach ($connections as $connection) {
													$cat_title ='';
													if(in_array($connection->title,$cat_array)){
														
														if($connection->title=='Clients'){
															$cat_title = 'People that you consider a client or are current clients';
														}
														if($connection->title=='Prospects'){
															$cat_title = 'People you are pursing for business';
														}
														if($connection->title=='Sales Associates'){
															$cat_title = 'People who are pursuing you for business';
														}
														if($connection->title=='Acquaintances'){
															$cat_title = 'General people you meet';
														}
														if($connection->title=='Business Associates'){
															$cat_title = 'People you commonly work with';
														}
														if($connection->title=='Friends'){
															$cat_title = 'Friends & Family';
														}
													}else{
														$cat_title = $connection->title;
													}
													
													$links[] = array('title' => ucfirst($connection->title), 'href' => 'connect/category/'.$connection->nid.'/request/'.$myuserid.'/'.$mycuserid.'/nojs','attributes' => array('class'=>array('title'=>$cat_title,'use-ajax')));	
														 
												}			
											$connect_category_connect ='<i class="fa fa-arrow-circle-o-right"></i> Connect';
									 
											$user_connect_btn= theme('m6_ctools_dropdown', array('main_title' => $connect_category_connect, 'links' => $links,'image'=>1));
											$output .= '<span class="user-page-cat-connect connection-connect pull-left">'.$user_connect_btn.'</span>';	
											
										}else if( $myuserid == $mycuserid){
											$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> You are connected</span>';
										}else{
											$output .= '<span class="you-connected pull-left"><i class="fa fa-arrow-circle-o-right"></i> '.$status_btn['button'].'</span>';
										}
										
									}															
			


								  /** ********************connect button***end************ */
								  /*                                                     * ********************bookmar button***start************ */
								  $flag = flag_get_flag('people_bookmark');

								  if ($flag && $flag->is_flagged($rcuser->uid)) {
									  $output .= '<span class="connection-bookmarked pull-left"><i class="fa fa-bookmark"></i> Bookmarked</span>';
								  } else {

									  $output .= '<span class="connection-bookmark pull-left"><span class="cust-people-bkmrk">' . flag_create_link('people_bookmark', $rcuser->uid) . '</span></span>';
								  }


								  /*                                                     * ********************bookmar button***end************ */


								  $output .= '</div>';

								  $output .='</div>';

								  $output .='</div>';


								  print $output;



								  $count ++;
							  }
						  }




						  echo '</div>';
						  echo '</div>';
					  }
					  ?>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
      <!----------------------------- Onboarding content start ---------------------------->
      <?php $cuid = $cuser->uid; $ob_nid = get_user_onboarding_nid($cuid); ?>
       <div role="tabpanel" class="tab-pane fade" id="viewonboarding">
        <div class='viewonboarding'>
          <!--<div class="post-heading clearfix">M6ID</div>-->
          <div class="dashboard-block-content onboarding-view">
           <?php 
		    if($ob_nid && $user->uid == $cuid) {
			   $node = node_load($ob_nid);
			   $elements = node_view($node, 'full');
			   print drupal_render($elements);
			   
			}
			else{ 
             //$Nom6idblock = module_invoke('m6connect_delegate', 'block_view', 'user-nom6id-Profile-view');
               //print render($Nom6idblock['content']);
			   $m6idblock = user_m6id_Profile_content($cuid);
			   print $m6idblock;
			}
           ?>
          </div>
        </div>
      </div>
      <!----------------------------- Onboarding content end ------------------------------> 
    </div>
  </div>
</div>
<!-- Modal -->
<div class="modal fade" id="myModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Shared Images</h4>
      </div>
      <div class="modal-body">
        <div class="user-connection-outer-photos text-center"> <img src="" id="model-img"  alt="photo" /> </div>
      </div>
    </div>
  </div>
</div>
<?php
//******************************* Node content end *********************************//	
?>
<?php print render($content['links']); ?> <?php print render($content['comments']); ?> 
<!--</article>--> 
<script>
    var grid = ''
    jQuery('document').ready(function () {
				jQuery('.connction-catg-filter').change(function(e) {
					var selected = jQuery(this).val();
  				jQuery('a[href="'+selected+'"]').click();
				});
			
			
			
        if (jQuery('body').hasClass('page-user')) {
            jQuery("a.flag-action").attr('title', 'Bookmark');
        }

        jQuery('#edit-field-date-of-birth-edit-datepicker-popup-0').datepicker();
        //fews feed show
        jQuery('.profile-tab-open').click(function () {

            jQuery('#block-statuses-statuses').hide();
            jQuery('.userprofilepage').hide();

            if (this.classList[1] == "out-side") {
                jQuery('#user-menu-nav li').each(function () {
                    jQuery(this).removeClass('active');
                });

            }


            jQuery('#ucr_all').addClass('active in');
            jQuery('#ucr_c_all').addClass('active in');

        });







        jQuery('#newsfeed-open').click(function () {
            jQuery('#user-feeds .tab-pane').each(function () {
                jQuery(this).removeClass('active');
                jQuery(this).removeClass('in');
            });
            jQuery('#block-statuses-statuses').show();
            jQuery('.userprofilepage').show();
        });

        jQuery('#newsfeed-open1').click(function () {
            jQuery('#user-feeds .tab-pane').each(function () {
                jQuery(this).removeClass('active');
                jQuery(this).removeClass('in');
            });
            jQuery('#block-statuses-statuses').show();
            jQuery('.userprofilepage').show();
        });


        jQuery('#block-statuses-statuses').prepend('<div class="company-status-title company-status-title-inner">Share With Others </div>');
        grid = jQuery('.grid').masonry({
            // specify itemSelector so stamps do get laid out
            itemSelector: '.grid-item',
            columnWidth: 172
        });
        jQuery('#photo-contaner').click(function () {
            setTimeout(function () {
                grid.masonry();
            }, 200);
        });

        var htm = jQuery('#share-connection').html();
        jQuery('#block-statuses-statuses').prepend(htm);
        jQuery('#share-connection').html('');
        jQuery('#block-statuses-statuses').css('position', 'relative');
        jQuery('#block-statuses-statuses .share-container').css('position', 'absolute');
        jQuery('#block-statuses-statuses .share-container').css('top', '97px');
        jQuery('#block-statuses-statuses .share-container').css('left', '360px');
		
		
		
		
		
		
	    jQuery('.add-credentials-tab').click(function () {
		  jQuery('#block-statuses-statuses').hide();
		  jQuery('.userprofilepage').hide();		  
        });	
		

    });
    function updateimage(path) {
        jQuery('#model-img').attr('src', '');
        jQuery('#model-img').attr('src', path);
    }
</script>