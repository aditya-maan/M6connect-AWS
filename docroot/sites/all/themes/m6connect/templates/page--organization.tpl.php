<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
//global $user;
//$node_id=arg(1);
//$nodeobj = node_load($node_id);
//$cuser = user_load($nodeobj->uid);
global $user, $company;
?>
<?php /* if (!(module_exists('jquery_update') && module_exists('m6connect_misc'))) { ?>
<script src="/sites/all/themes/m6connect/js/jquery1.11.3.min.js"></script>
<?php } */ ?>
<!--<script src="/sites/all/themes/m6connect/js/bootstrap.min.js"></script>
<script src="/sites/all/themes/m6connect/js/dropdown.js"></script>
<script src="/sites/all/themes/m6connect/js/collapse.js"></script>
<script type="text/javascript" src="/sites/all/themes/m6connect/js/tab.js"></script>-->
<script type="text/javascript" src="/<?php echo drupal_get_path('module', 'm6connect_delegate') . '/masonry.pkgd.min.js' ?>"></script>

<div id="page">
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
          <div class="container-fluid">
            <div class="top_header clearfix">
              <?php if ($page['top_header']): ?>
              <?php print render($page['top_header']); ?>
              <?php endif; ?>
            </div>
            <div id="content" class="column" role="main">
              <div class="box">
                <div class="inner-box">
                  <div class="highlighted"><?php print render($page['highlighted']); ?></div>
                  <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?>
                  <!-- Printing vendor manager messages, for ex - Invitation sent etc. -->
                  <div id="vendor_status_msg" class="messages--status messages status" style="display:none;"></div>
                  <div id="vendor_error_msg" class="messages--error messages error" style="display:none;"></div>
                  <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                  <?php endif; ?>
                  <div class="right_content clearfix">
                    <div class="right_content_top clearfix">
                      <div class="company-header" id="company-banner-custom-header">
                        <?php
                                          
						  if (isset($node->field_company_profile_cover_img['und'])) {
							  print '<img src="' . image_style_url('company_cover_1073_394', $node->field_company_profile_cover_img['und'][0]['uri']) . '">';
						  } else {
							  $cirtificate = m6connect_company_get_circtficat($node);
							  if ($cirtificate) {
								  print '<img src="/sites/all/themes/m6connect/images/default-company-cover_c.jpg" alt="default-company-cover">';
							  } else {
								  print '<img src="/sites/all/themes/m6connect/images/default-company-cover-new.jpg" alt="default-company-cover">';
							  }
							  //style="width:1073px;height:394px;"
						  }
						  ?>
                        <?php //print render(field_view_field('node', $node, 'field_company_profile_cover_img', array('label' => 'hidden')));  ?>
                           <!--- start here for update company banner -->
                              <?php if($user->uid == $node->uid) { ?>
                              <div class="custom-user-profile-photo custom-user-profile-photo-company">
                                <?php echo l('Update Company banner', 'update-company-banner-photo/'.$node->nid.'/nojs', array('attributes' => array('class' => array('ctools-use-modal ctools-modal-assign-update-images-crop-popup-style btn btn-success text-white'),'title' =>"Update Company banner"))); ?>
                                
                              </div>
                              <?php } ?> 
                              
                              <!--End here for update company banner-->

                      </div>
                      <!-- M6 Ratings -->
                      <?php
                      // $vendor_ratings_options = variable_get('vendor_rating_types', array());
                      if ($node->nid != 505891) {
                        $vendor_ratings_options = _get_vendor_ratings_options($node->nid, 'ratings');
                        $ratings_output = '';
                        $ratings_output = '<div class="company-banner-ratings">';
                        foreach ($vendor_ratings_options as $key => $value) {
                          $ratings_output .= '<div class="toggle-outer-banner relative clearfix toggle-m6reach-rating1"><div class="' . $key . '-outer-banner inner-banner-cp-ratings" style="display:none;"><span class="' . $key . '-data-banner" style="font-weight: 700;">' . $value . ' :</span>';
                          $ratings_output .= '<div id="' . $key . '-option-banner"></div></div><div class="toggle-vendor-rating-banner" data="' . $key . '-outer-banner" style="cursor:pointer;">Toggle</div></div>';
                        }
                        $ratings_output .= '</div>';
                        print $ratings_output;
                      }
                      ?>
                      <div class="right_content_top_inner">
                        <?php if ($page['right_content']): ?>
                        <?php print render($page['right_content']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
                    <div class="right_content_bottom clearfix">
                      <div class="row margin-5 company-header-stats">
                        <div class="col-md-3 col-sm-3 col-xs-12 padding-5 company_logo">
                          <div class="quick-fact-container">
                            <div class='company_logo_details text-center' id="company-logo-custom-header">

                            
                              <?php
							    $CompanyPic = isset($node->field_logo['und']['0']['uri']) ? $node->field_logo['und']['0']['uri'] : '/sites/all/themes/m6connect/images/default_company_profile.jpg';
							  
                                                       /* if (isset($node->field_logo['und'])) {
                                                            print '<img src="' . image_style_url('company_logo', $node->field_logo['und'][0]['uri']) . '">';
                                                        } else {
                                                            print '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" style="width:264px;height:229px;">';
                                                        }*/
														
														
								print '<a href="'.file_create_url($CompanyPic).'" class="colorbox">
                                        <img typeof="foaf:Image" src="'. image_style_url('company_logo', $CompanyPic).'" alt="">
                                       </a>';

                //$orgcompamylogo = render(field_view_field('node', $node, 'field_logo', array('label' => 'hidden')));
                //print  $orgcompamylogo;                      
														
                              ?>
                               <!--- start here for update company logo -->
                              <?php if($user->uid == $node->uid) { ?>
                              <div class="custom-user-profile-photo custom-user-profile-photo-company">
                                <?php echo l('Update Company logo', 'update-company-logo-photo/'.$node->nid.'/nojs', array('attributes' => array('class' => array('ctools-use-modal ctools-modal-assign-dashboard-facebook-popup-style btn btn-success text-white'),'title' =>"Update Company logo"))); ?>
                                
                              </div>
                              <?php } ?> 
                              <!--End here for update company logo-->
                             
                            </div>
                          </div>
                        </div>
                        <div class="col-md-9 col-sm-9 col-xs-12 padding-5 company_details">
                          <div class="quick-fact-container">
                            <div class="company_logo_details">
                              <div class="company_title clearfix">
                                <div class='quick-facts pull-left'> <?php print $node->title; ?></div>
                                <div class="quick-employee pull-right">
                                  <?php
                                   
																																 					  /*if($company->nid == arg(1)) { 																																																																																													
                            if($router_item = menu_get_item('people/member/'.arg(1))) {
                                    if($router_item['access']) {
                                        echo l('User Management', 'people/member/'.arg(1), array('attributes' => array('class' => array('employee-request'))));
                                    }
                            }
               		    }*/
						 $user_og_roles = og_get_user_roles('node', arg(1), $user->uid);
						 //print "<pre>"; print_r($user_og_roles);
 				         if(in_array('company admin', $user_og_roles) && $node->nid != 505891){
						    echo l('User Management', 'people/member/'.arg(1), array('attributes' => array('class' => array('employee-request'))));
                           }
						 else if(in_array('administrator member', $user_og_roles)  && $node->nid != 505891){
						    echo l('User Management', 'people/member/'.arg(1), array('attributes' => array('class' => array('employee-request'))));
                           }
						  
						
                                   ?>
                                  <!-- <a href="people/member"><button class="btn btn-default">Employee Request</button></a>--> 
                                </div>
                              </div>
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
                  <div class="row margin-5 middle_content">
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5">
                      <div class="middle_one company-profile-navigation clearfix">
                        <div class="middle_one_top clearfix">
                          <?php if ($page['middle_one_top']): ?>
                          <?php print render($page['middle_one_top']); ?>
                          <?php endif; ?>
                          <div class="more-link gray-text"> <a href="#location" class="profile-tab-open out-side" aria-controls="location" role="tab" data-toggle="tab">View all Locations</a> </div>
                        </div>
                        <div class="content block clearfix">
                          <div class="company-info">
                            <?php if (render(field_view_field('node', $node, 'field_incorporated_state', array('label' => 'hidden'))) && render(field_view_field('node', $node, 'field_incorporated_country', array('label' => 'hidden')))) { ?>
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"><i class="fa fa-map-marker"></i></div>
                              <div class="pull-right">
                                <?php
                                $org_add = render(field_view_field('node', $node, 'field_incorporated_state', array('label' => 'hidden')));
                                $org_add2 = render(field_view_field('node', $node, 'field_incorporated_country', array('label' => 'hidden')));
                                //echo '<a href="#location" aria-controls="location" role="tab" data-toggle="tab"><i class="fa fa-map-marker"></i>'.$org_add.'</a>';
                                /////
                                $add = $node->field_incorporated_state['und'][0]['value'] . ', ';
                                $add.=$node->field_incorporated_country['und'][0]['value'];
                                print l($add, '', array('html' => TRUE, 'attributes' => array('title' => $org_add, 'class' => 'profile-tab-open out-side', 'aria-controls' => 'location', 'role' => 'tab', 'data-toggle' => 'tab'), 'fragment' => 'location'));
                                /////
                                //echo '<div class="pullleft">';
                                //print l($org_add, '', array('html' => TRUE, 'attributes' => array('title' => $org_add,'aria-controls'=>'location','role'=>'tab','data-toggle'=>'tab'),'fragment' => 'location'));
                                //echo '</div>';
                                // echo '<div class="pullright">'; 
                                //print l($org_add2, '', array('html' => TRUE, 'attributes' => array('title' => $org_add,'aria-controls'=>'location','role'=>'tab','data-toggle'=>'tab'),'fragment' => 'location'));
                                //echo '</div>';
                                ?>
                              </div>
                            </div>
                            <?php } ?>
                            <?php if (!empty(render(field_view_field('node', $node, 'field_facilities_construction', array('label' => 'hidden'))))) { ?>
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"><i class="fa fa-building-o"></i></div>
                              <div class="pull-right"> <?php print render(field_view_field('node', $node, 'field_facilities_construction', array('label' => 'hidden'))); ?></div>
                            </div>
                            <?php } ?>
                            <?php if (!empty(render(field_view_field('node', $node, 'field_website', array('label' => 'hidden'))))) { ?>
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"><i class="fa fa-envelope-o"></i></div>
                              <div class="pull-right"> <?php print render(field_view_field('node', $node, 'field_website', array('label' => 'hidden'))); ?></div>
                            </div>
                            <?php } ?>
                            <?php if (!empty(render(field_view_field('node', $node, 'field_company_email', array('label' => 'hidden'))))) { ?>
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"><i class="fa fa-envelope-o"></i></div>
                              <div class="pull-right"> <?php print render(field_view_field('node', $node, 'field_company_email', array('label' => 'hidden'))); ?></div>
                            </div>
                            <?php } ?>
                            <!--<?php //if (!empty(render(field_view_field('node', $node, 'field_org_phone', array('label' => 'hidden'))))) { ?>
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"> <i class="fa fa-phone"></i></div>
                              <div class="pull-right"><?php //print render(field_view_field('node', $node, 'field_org_phone', array('label' => 'hidden'))); ?> </div>
                            </div>
                            <?php //} ?>-->
                           <?php if (!empty($node->field_org_phone['und'][0]['value'])) { 
                             $phoneNumber = $node->field_org_phone['und'][0]['value'];
		                     $phoneNumberval = get_international_formatPhoneNumber($phoneNumber); ?>	
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"> <i class="fa fa-phone"></i></div>
                              <div class="pull-right"><?php print $phoneNumberval; ?> </div>
                            </div>
                            <?php } ?>
                            
                            <?php if (!empty(render(field_view_field('node', $node, 'field_org_fax', array('label' => 'hidden'))))) { ?>
                            <div class="pull-outer clearfix margin-bottom-10">
                              <div class="pull-left"><i class="fa fa-fax"></i></div>
                              <div class="pull-right"><?php print render(field_view_field('node', $node, 'field_org_fax', array('label' => 'hidden'))); ?></div>
                            </div>
                            <?php } ?>
                          </div>
                          <!-- <a href="#location" aria-controls="location" role="tab" data-toggle="tab">Location(s)</a>-->
                          <div class="pull-right more-link"><a href="#view-more-about" class="profile-tab-open out-side" aria-controls="view-more" role="tab" data-toggle="tab">View More</a></div>
                        </div>
                      </div>
                      <div class="middle_one_bottom clearfix">
                        <?php if ($page['middle_one_bottom']): ?>
                        <?php print render($page['middle_one_bottom']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
                    <div class="col-md-6 col-sm-12 col-xs-12 padding-5">
                      <div class="middle_two clearfix">
                        <div class="middle_two_inner">
                          <?php if ($page['middle_two']): ?>
                          <?php print render($page['middle_two']); ?>
                          <?php endif; ?>
                        </div>
                        <div class="content_inner">
                          <div id="user-feeds">
                            <?php
                            $arr = array_keys($page['content']['system_main']['nodes'][$node->nid]['links']['flag']);
                            unset($page['content']['system_main']['nodes'][$node->nid]['links']['flag']);
                            ?>
                            <?php if ($page['content']): ?>
                            <?php print render($page['content']); ?>
                            <?php endif; ?>
                          </div>
                        </div>
                      </div>
                    </div>
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5">
                      <div class="middle_three clearfix">
                        <?php if ($page['middle_three']): ?>
                        <?php print render($page['middle_three']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
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
