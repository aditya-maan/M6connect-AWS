<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
module_load_include('inc', 'user_relationships', 'user_relationships_ui/user_relationships_ui.pages');
global $user;
$cuser = user_load(arg(1));
$cuser_groups = og_get_groups_by_user($cuser, 'node');
$companyNids = array_values($cuser_groups);
$companyNode = node_load($companyNids[0]);
$job_title_tid = $cuser->field_job_titles['und'][0]['target_id'];
	if(isset($job_title_tid)){
		$job_title_term = taxonomy_term_load($job_title_tid);
		$job_title_name = $job_title_term->name;
	}
?>
<?php if (!(module_exists('jquery_update') && module_exists('m6connect_misc'))) { ?>
<script src="/sites/all/themes/m6connect/js/jquery1.11.3.min.js"></script>
<?php } ?>
<!--<script src="/sites/all/themes/m6connect/js/bootstrap.min.js"></script-->
<?php
if ($user->uid != arg(1)) {
    $loginuserview = 'loginuserview';
}
?>

<div id="page" class="<?php echo $loginuserview; ?>">
  <header class="header" id="header" role="banner">
    <div class="container-fluid">
      <div id="top-navigation" class="row"><?php print render($page['top_navigation']); ?></div>
      <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
      <?php endif; ?>
      <?php if ($site_name || $site_slogan): ?>
      <div class="header__name-and-slogan" id="name-and-slogan">
        <?php if ($site_name): ?>
        <h1 class="header__site-name" id="site-name"> <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="header__site-link" rel="home"><span><?php print $site_name; ?></span></a> </h1>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
        <div class="header__site-slogan" id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>
      </div>
      <?php endif; ?>
      <?php print render($page['header']); ?> </div>
  </header>
  <div id="navigation">
    <div class="container"><?php print render($page['navigation']); ?></div>
  </div>
  <?php $wrapperClass =''; if(isset($_SESSION['left_block_action']) && $_SESSION['left_block_action']=='open'){ $wrapperClass='active'; } ?>
  <div id="wrapper" class="<?php print $wrapperClass; ?> clearfix">
    <div id="sidebar-wrapper">
      <?php if ($page['left_content']): ?>
      <?php print render($page['left_content']); ?>
      <?php endif; ?>
    </div>
    <div id="page-content-wrapper">
      <div class="page-content inset">
        <div id="main">
          <div class="box">
            <div class="inner-box">
              <div class="container-fluid">
                <div class="top_header clearfix">
                  <?php if ($page['top_header']): ?>
                  <?php print render($page['top_header']); ?>
                  <?php endif; ?>
                </div>
                <div id="content" class="column" role="main">
                  <div class="highlighted"><?php print render($page['highlighted']); ?></div>
                  <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                  <?php endif; ?>
                  <?php if ((arg(0) == 'user' && is_numeric(arg(1)) && !(arg(2)))) { ?>
                  <div class="right_content clearfix">
                    <div class="right_content_top clearfix">
                      <div class="company-header relative" id="user-cover-custom-header-wrapper">
                        <?php /* ?>  <img typeof="foaf:Image" src="<?php echo image_style_url('company_cover_1073_394',isset($cuser->field_user_profile_cover_img['und']['0']['uri'])?$cuser->field_user_profile_cover_img['und']['0']['uri']:'public://user-cover-image.png'); ?>" alt=""><?php */ ?>
                        <?php
						  $profile_cover_img = render(field_view_field('user', $cuser, 'field_user_profile_cover_img', array('label' => 'hidden')));
						  if ($profile_cover_img) {
							  print $profile_cover_img;
						  }/*else {
							  print '
								<div class="field field-name-field-user-profile-cover-img field-type-image field-label-hidden">
									<div class="field-items">
										<div class="field-item even">
											<img  alt="" src="' . $base_url . '/sites/default/files/user-cover-image.png" typeof="foaf:Image">
										</div>
									</div>
								</div>';
						  }*/
						  else {
							  print '
								<div class="field field-name-field-user-profile-cover-img field-type-image field-label-hidden">
									<div class="field-items">
										<div class="field-item even">
					<img  alt="" src="' . $base_url.'/sites/all/themes/m6connect/images/default-company-cover-new.jpg" typeof="foaf:Image">
										</div>
									</div>
								</div>';
						  }
						  ?>
                        <!-- start here custom-user-cover-photo-->
                        <?php if ($user->uid == arg(1)) { ?>
                        <div class="custom-user-cover-photo"> <a href="/update-user-cover-photo/nojs" title="Update Cover Photo" class="ctools-use-modal ctools-modal-assign-update-images-crop-popup-style btn btn-success text-white">Update Cover Photo</a> </div>
                        <?php } ?>
                        <!-- End here custom-user-cover-photo--> 
                      </div>
                      <div class="right_content_top_inner">
                        <?php if ($page['right_content']): ?>
                        <?php print render($page['right_content']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
                    <div class="right_content_bottom clearfix">
                      <div class="row margin-5 company-header-stats">
                        <div class="col-md-3 col-sm-3 col-xs-12 padding-5 company_logo user-realname">
                          <div class="quick-fact-container">
                            <div class='company_logo_details text-center'>
                              <div class="user-profile-custom-wrapper">
                                <?php /* ?>   <img typeof="foaf:Image" src="<?php echo image_style_url('user_profile_image_244_220',isset($cuser->field_user_profile_photo['und']['0']['uri'])?$cuser->field_user_profile_photo['und']['0']['uri']:'public://images_13.png'); ?>" alt=""><?php */ ?>
                                <?php //print $rcuser_profile_photo = (isset($cuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'user_profile_image_244_220', 'path' => $cuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : ''; ?>
                                <?php $UserPic = isset($cuser->field_user_profile_photo['und']['0']['uri']) ? $cuser->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png'; ?>
                                <a href="<?php echo file_create_url($UserPic); ?>" class="colorbox"> <img typeof="foaf:Image" src="<?php echo image_style_url('user_profile_image_244_220', $UserPic); ?>" alt=""> </a> 
                                <!--- start here for update Profile photo -->
                                <?php if($user->uid == arg(1)) { ?>
                                <div class="custom-user-profile-photo"> <a href="/change-user-profile-photo/nojs" title="Update Profile Photo" class="ctools-use-modal ctools-modal-assign-dashboard-facebook-popup-style btn btn-success text-white">Update Profile Photo</a> </div>
                                <?php } ?>
                                <!--End here for update Profile photo--> 
                              </div>
                              <div class="quick-facts"><?php echo $cuser->realname; ?></div>
                              <div class="quick-fact-title">
                                <?php
                                   /*if (isset($job_title_name)) {
                                   echo $job_title_name;
                                   };*/
								   if(isset($cuser->field_user_title['und'][0]['value'])) {
									$string_user_job_title = $cuser->field_user_title['und'][0]['value'];																	                                    $user_job_title_string = (strlen($string_user_job_title) > 26) ? substr($string_user_job_title, 0, 23) . '...' : $string_user_job_title;   
                                   //echo $cuser->field_user_title['und'][0]['value'];
								    echo $user_job_title_string;
                                   }
                                 ?>
                              </div>
                            </div>
                          </div>
                        </div>
                        <div class="col-md-9 col-sm-9 col-xs-12 padding-5 company_details">
                          <div class="quick-fact-container">
                            <div class="company_logo_details profile-page-nav">
                              <div class="company_navs clearfix">
                                <?php if ($page['company_navs']): ?>
                                <?php print render($page['company_navs']); ?>
                                <?php endif; ?>
                              </div>
                            </div>
                          </div>
                        </div>
                      </div>
                    </div>
                  </div>
                  <?php } ?>
                  <div class="row margin-5 middle_content">
                    <?php if ((arg(0) == 'user' && is_numeric(arg(1)) && !(arg(2)))) { ?>
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5">
                      <div class="middle_one company-profile-navigation clearfix">
                        <div class="middle_one_top clearfix">
                          <?php if ($page['middle_one_top']): ?>
                          <?php print render($page['middle_one_top']); ?>
                          <?php endif; ?>
                          <?php
							if (arg(0) == 'user' && is_numeric(arg(1)) && empty(arg(2))) {
								$crequestee_id = arg(1);
								$praram = array('approved' => TRUE, 'requestee_id' => $crequestee_id);
  
								$relationships = user_relationships_load($praram);
  
								echo '<div class="user-connection-outer block">';
								echo '<h2 class="block-title">Connections</h2>';
								echo '<div class="row margin-5">';
								$count = 0;
  
								$user_cats = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
								$user_category_nid = array();
								foreach ($user_cats as $user_cat) {
									$user_category_nid[] = $user_cat->nid;
								}
  
  
								foreach ($relationships as $relationship) {
									$job_title_name_con = '';
									$string_job_title = '';
									$relationship->requester_id;
									$rcuser = user_load($relationship->requester_id);
  
									//$job_title_tid = $rcuser->field_job_titles['und'][0]['target_id'];
									/*if(isset($job_title_tid)){
									$job_title_term = taxonomy_term_load($job_title_tid);
									$job_title_name = $job_title_term->name;
									}*/
									//$job_title_tid = $rcuser->field_job_titles['und'][0]['target_id'];
									if(!empty($rcuser->field_user_title['und'][0]['value'])){
									$job_title_name_con = $rcuser->field_user_title['und'][0]['value'];
									}
									$output = ' <div class="col-md-6 col-sm-6 col-xs-12 padding-5 margin-bottom-10 user-connection-inner">';
									$output .= '<a href="/user/' . $rcuser->uid . '">';
									$output .='<div class="section1 clearfix">';
									$rcuser_profile_photo = (isset($rcuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'connection_image_114_94', 'path' => $rcuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : '';
									//$rcuser_profile_photo = render(field_view_field('user', $rcuser, 'field_user_profile_photo', array('label' => 'hidden')));
  
  
									if ($rcuser_profile_photo) {
										$output .= $rcuser_profile_photo;
									} else {
										$output .= '<img class="profile_image_114_94" alt="" src="' . $base_url . '/sites/default/files/default_profile.jpg" typeof="foaf:Image">';
									}
									$output .='</div>';
									$output .= '</a>';
									$output .='<div class="section2 clearfix">';
									$output .= '<div class="clearfix user-conn-fields"><div class="pull-left"><a href="/user/' . $rcuser->uid . '">';
									//$output .= $rcuser->field_first_name['und'][0]['value'];
									$rcuser_realname = $rcuser->realname;
									$output .= (strlen($rcuser_realname) > 17) ? substr($rcuser_realname, 0, 14) . '...' : $rcuser_realname;
									$output .= '</a></div>';
							if(isset($job_title_name_con)){
								$string_job_title = $job_title_name_con;
																												$job_title_term_string = (strlen($string_job_title) > 19) ? substr($string_job_title, 0, 16) . '...' : $string_job_title;
							$output .= '<div class="pull-left you-are-connected">' . $job_title_term_string . '</div>';
								}
  
  
									/************assign category****start**************** */
								  /*  $conn1 = m6connect_misc_get_user_all_companies($rcuser->uid, 'connection_categories');
  
									$connectedUserConnections = array();
									foreach ($conn1 as $conn2) {
										$connectedUserConnections[] = $conn2->nid;
									}
  
									if (count(array_intersect($connectedUserConnections, $user_category_nid)) > 0) {
  
  //                                                            drupal_set_message('<pre>xxcvc' . print_r($user_category_nid, 1) . '</pre>');
										$related_group = array_intersect($connectedUserConnections, $user_category_nid);
										foreach ($related_group as $data) {
											$outputs = node_load($data)->title;
										}
										if ($rcuser->uid != $user->uid) {
																											$assigned_category =(strlen($outputs) > 17) ? substr($outputs, 0, 14) . '...' : $outputs;
											$output .= '<div class="assigned-category">' . $assigned_category . '</div>';
										}
  //                                                           
									} else if ($user->uid == $crequestee_id) {
										$output .= '<div class="assign-category"><a class="use-ajax" href="/assign_connection_category/' . $user->uid . '/' . $rcuser->uid . '/nojs">assign category</a></div>';
									}*/
  
									/** ***********assign category***end***************** */
																								//$output .='</div>';
																								/***connect button***start****/
																								/*if ($user->uid != $crequestee_id) {
										if (!(count(user_relationships_load(array('rtid' => array(5), 'between' => array($rcuser->uid, $user->uid)))) > 0) && ($rcuser->uid != $user->uid)) {
											$output .= '<span class="connection-connect pull-left"><a class="user_relationships_popup_link" href="/relationship/' . $rcuser->uid . '/request/5?destination=user/' . $rcuser->uid . '"><i class="fa fa-arrow-circle-o-right"></i> Connect</a></span>';
										}
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
																											
																										}
																									}
																								
																								
																								
									/****connect button***end**/
																								$output .='</div>';
									$output .='</div>';
  
									$output .='</div>';
									// $output .='</a>';
									if ($count < 6) {
										print $output;
									}
  
  
									$count ++;
								}
  
								if ($count < 6) {
									for ($i = $count; $i < 6; $i++) {
										echo '<div class="col-md-6 col-sm-6 col-xs-12 padding-5 margin-bottom-10 user-connection-inner"><a id="viewmconnections-ucr_all" role="tab"  aria-controls="Add Connection" aria-expanded="true" data-toggle="tab" href="#viewmconnections" class="smile cucr-tab-all" href="#"><div class="section1 clearfix"><i class="fa fa-smile-o fa-5x"></i></div></a><div class="section2 clearfix"><div class="user-conn-fields"><a class="text-center connection-add cucr-tab-all"  href="/find-people">Add Connection </a></div></div></div>';
									}
								}
								echo '</div>';
  
								echo '<div class="clearfix"><div class="more-link"> <a id="viewmconnections-ucr_all" class="cucr-tab-all profile-tab-open out-side" role="tab" href="#viewmconnections" data-toggle="tab" aria-controls="View All Connections" aria-expanded="true">View All Connections</a> </div></div>';
  
								echo '</div>';
							}
							?>
                          <?php print views_embed_view('user_profile_contact_information', 'block'); ?> </div>
                        <div class="middle_one_bottom clearfix">
                          <?php if ($page['middle_one_bottom']): ?>
                          <?php print render($page['middle_one_bottom']); ?>
                          <?php endif; ?>
                          <?php
							$isadmin = array_intersect(array_keys($user->roles), array(3)); //pre($isadmin);
							if (!empty($isadmin)) {
								$cuid = arg(1);
								$cusername = $cuser->name;
								$mlink = l('Masquerade as  ' . $cusername, 'masquerade/switch/' . $cuid, array('query' => array('token' => drupal_get_token('masquerade/switch/' . $cuid))));
								?>
                          <div class="masquerade-section block">
                            <h3>Masquerade</h3>
                            <div class="masquerade-link"><?php print $mlink; ?></div>
                          </div>
                          <?php } ?>
                        </div>
                      </div>
                    </div>
                    <?php } ?>
                    <div class="col-md-6 col-sm-12 col-xs-12 padding-5 middle-two-main-section">
                      <div class="middle_two clearfix">
                        <div class="middle_two_inner">
                          <?php if ($page['middle_two']): ?>
                          <?php print render($page['middle_two']); ?>
                          <?php endif; ?>
                        </div>
                        <div  class="content_inner">
                          <div id="user-feeds">
                            <?php if ($page['content']): ?>
                            <?php
							  $arr = array_keys($page['content']);
  
							  print render($page['content']);
							  ?>
                            <?php endif; ?>
                          </div>
                        </div>
                      </div>
                    </div>
                    <?php if ((arg(0) == 'user' && is_numeric(arg(1)) && !(arg(2)))) { ?>
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5 middle-three-main-section">
                      <div class="middle_three clearfix">
                        <?php if ($page['middle_three']): ?>
                        <?php print render($page['middle_three']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
                    <?php } ?>
                  </div>
                  <div class="bottom_content clearfix">
                    <div class="bottom_content_inner">
                      <?php if ($page['bottom_content']): ?>
                      <?php print render($page['bottom_content']); ?>
                      <?php endif; ?>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="footer_content clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4 footer_left">
          <?php if ($page['footer_left']): ?>
          <?php print render($page['footer_left']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_center">
          <?php if ($page['footer_center']): ?>
          <?php print render($page['footer_center']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_right">
          <?php if ($page['footer_right']): ?>
          <?php print render($page['footer_right']); ?>
          <?php endif; ?>
        </div>
      </div>
      <div class="clearfix">
				<?php if ($page['footer_top']): ?>
        <?php print render($page['footer_top']); ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class="footer_message clearfix">
    <div class="container">
      <?php if ($page['footer']): ?>
      <?php print render($page['footer']); ?>
      <?php endif; ?>
    </div>
  </div>
  <div class="container"><?php print render($page['bottom']); ?> </div>
</div>
