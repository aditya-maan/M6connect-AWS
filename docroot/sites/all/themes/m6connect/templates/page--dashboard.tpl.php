<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<?php global $user, $base_url; ?>
<?php if ($user->uid == 0) : ?>

<div id="page">
  <div class="box">
    <header class="header" id="header" role="banner">
      <div class="inner-box">
        <div class="container-fluid">
          <div class="row">
            <div class="col-md-3 col-sm-3 col-xs-12">
              <?php if ($logo): ?>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
              <?php endif; ?>
            </div>
            <div class="col-md-9 col-sm-9 col-xs-12 text-right header-right"> <?php print render($page['header']); ?> </div>
          </div>
        </div>
      </div>
    </header>
    <div id="main">
      <div class="container">
        <div id="content" class="column frontbox" role="main"> <?php print render($page['highlighted']); ?>
          <?php if ($action_links): ?>
          <ul class="action-links">
            <?php print render($action_links); ?>
          </ul>
          <?php endif; ?>
          <?php print $messages; ?>
          <?php if ($user->uid == 0) { ?>
          <?php print render($page['message_login']); ?>
          <?php // print render($page['signup_box']); ?>
          <?php // print render($page['contentlogin']); ?>
          <?php } ?>
        </div>
      </div>
    </div>
  </div>  
</div>
<?php endif; ?>
<?php if ($user->uid != 0) : ?>
<?php drupal_add_library('system', 'ui.dialog'); ?>
<?php
    /**
     * @file
     * Returns the HTML for a single Drupal page.
     *
     * Complete documentation for this file is available online.
     * @see https://drupal.org/node/1728148
     */
    module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
    ctools_include('modal');
    ctools_include('ajax');
//assign_bid_package_ctools_popup_style();
    assign_dashboard_ctools_popup_style();
    ?>
<?php if (!(module_exists('jquery_update') && module_exists('m6connect_misc'))) { ?>
<script src="/sites/all/themes/m6connect/js/jquery1.11.3.min.js"></script>
<?php } ?>
<?php
    global $user, $company;
    module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
//module_load_include('module','m6connect_misc','custom/m6connect_misc/m6connect_misc');
    module_load_include('inc', 'user_relationships', 'user_relationships_ui/user_relationships_ui.pages');
//relationships load
    $relationships = user_relationships_load(array('approved' => $user->uid, 'approved' => FALSE, 'requestee_id' => $user->uid));
    $relation_rows = array();
    foreach ($relationships as $relationship) {
        $requester = user_load($relationship->requester_id);
        $relation_rows[] = array('name' => $requester->realname, 'links' => user_relationships_ui_get_table_row($relationship, $user));
    }
//*************end***********
    $user_obj = user_load($user->uid);
    $companies_detail = m6connect_misc_get_user_all_companies($user->uid);
    drupal_add_js(drupal_get_path('module', 'm6connect_dashboard') . '/m6connect_dash.js');
    ?>
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
  <div id="wrapper" class="active clearfix">
    <div id="sidebar-wrapper">
      <?php if ($page['left_content']): ?>
      <?php print render($page['left_content']); ?>
      <?php endif; ?>
    </div>
    <div id="page-content-wrapper">
      <div class="page-content inset">
        <div id="dashboard">
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
                  <div class="text-center clearfix"> <?php print render($title_prefix); ?>
                    <?php if ($title): ?>
                    <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
                    <?php endif; ?>
                    <?php print render($title_suffix); ?> </div>
                  <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                  <?php endif; ?>
                  <div class="row margin-5 dashboard_content">
                    <div class="col-md-6 col-sm-12 col-xs-12 padding-5 margin-bottom-10" id="dashboard-share-panel">
                      <div class="middle_one company-profile-navigation clearfix">
                        <div class="middle_one_top clearfix">
                          <?php if ($page['middle_one_top']): ?>
                          <?php print render($page['middle_one_top']); ?>
                          <?php endif; ?>
                        </div>
                        <div class="middle_one_bottom clearfix">
                          <?php if ($page['middle_one_bottom']): ?>
                          <?php print render($page['middle_one_bottom']); ?>
                          <?php endif; ?>
                        </div>
                        <div class="dashboard-content dashboard-block-lightgray">
                          <div class="dashboard_inner_details"> 
                            <!--<div class="external-link-square"><i class="fa fa-external-link-square"></i>&nbsp;Post To Project </div>-->
                            <div class="company-status-title clearfix">
                              <div class="pull-left company-status-title-inner">Share With Others <span>(</span><span class="user-name">as <?php echo $user_obj->realname ?></span><span>)</span></div>
                              <div class="pull-right"> 
                                <!--<span class="caret pull-right"></span>-->
                                <div class="company-list-contaner share-container">
                                  <div class="dropdown"> <a id="dLabel2" class="btn btn-default" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">My Connections</a>
                                    <ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel2">
                                      <?php
																	$cat_array = array('Clients','Prospects','Sales Associates','Acquaintances','Business Associates','Friends');
                                  $connections = m6connect_misc_get_groups_by_ownerid($user->uid, 'connection_categories');
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
                                  ?>
                                      <li><?php echo l(ucfirst($connection->title), 'switch-dashboard/connection/' . $connection->nid . '/nojs', array('html' => TRUE, 'attributes' => array('title' => $cat_title, 'class' => 'use-ajax'))); ?></li>
                                      <?php } ?>
                                      <li><a href="javascript:" title="People who work for the same company as you"> Colleagues</a>
                                        <ul class="user-companies">
                                          <?php
                                          $user_companys = array();
                                          foreach ($companies_detail as $com) {
                                            if ($com->field_type_of_company_value == 'company') {
                                              $user_companys[] = $com->nid;?>
                                              <li><?php echo l(ucfirst($com->title), 'switch-dashboard/company/' . $com->nid . '/nojs', array('html' => TRUE, 'attributes' => array('title' => $com->title, 'class' => 'use-ajax'))); ?></li>
                                              <?php
                                            }
                                          }?>
                                        </ul>
                                      </li>
                                      <?php /*?>                 <hr/>
                                      <li><a href="javascript:"> Groups</a>
                                          <ul class="user-companies">
                                              <?php
                                              $groups = m6connect_misc_get_user_all_companies($user->uid, 'groups');
                                              foreach ($groups as $group) {
                                                  if ($group->group_access_value == 0) {
                                                      $ops = array('html' => TRUE, 'attributes' => array('title' => $group->title, 'class' => 'use-ajax'));
                                                      ?> 
                                                      <li><?php echo l(ucfirst($group->title), 'switch-dashboard/group/' . $group->nid . '/nojs', $ops); ?></li>
                                                      <?php
                                                  }
                                              }
                                              ?>
                                          </ul>
                                      </li><?php */?>
                                    </ul>
                                  </div>
                                </div>
                              </div>
                            </div>
                            <div class="company-share-with-others">
                              <div class="dashboard-user-feed-pic">
                              <?php $UserPic = isset($user_obj->field_user_profile_photo['und']['0']['uri']) ? $user_obj->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png'; ?> 
                                <a href="<?php echo file_create_url($UserPic); ?>" class="colorbox">
                                  <img typeof="foaf:Image" src="<?php echo image_style_url('dashboard-user-feed-pic-img_52_52', $UserPic); ?>" alt="">
                                </a>
                              </div>
                            </div>
                          </div>
                          <?php if ($page['content']): ?>
                          <?php print render($page['content']); ?>
                          <?php endif; ?>
                        </div>
                      </div>
                    </div>
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5 margin-bottom-10" id="dashboard-feed-panel">
                      <div class="middle_two clearfix">
                        <div class="middle_two_inner">
                          <?php if ($page['middle_two']): ?>
                          <?php print render($page['middle_two']); ?>
                          <?php endif; ?>
                        </div>
                        <div class="dashboard-block-lightgray-contaner">
                          <div class="group_newsfeed">
                            <?php
                            if (isset($_SESSION['deshboard_cid']) && $_SESSION['deshboard_cid'] != "") {
                                $company = node_load($_SESSION['deshboard_cid']);
                            }
                            /* ?>
                              <!--                                                        <div class="company-status-box dashboard-block-lightgray margin-bottom-8">
                              <div class="external-link-square"><i class="fa fa-external-link-square"></i>&nbsp;Post To Project </div>
                              <div class="company-status-title clearfix">
                              <div class="pull-left company-status-title-inner"><?php echo $company->title ?> Share</div>
                              <div class="pull-right">
                              <div class="company-list-contaner1">
                              <div class="dropdown"> <a id="dLabel1" class="company-list" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fa fa-sort-desc"></i></a>
                              <div class="dropdown-menu dropdown-menu-right dashbord-com-dropdown" role="menu" aria-labelledby="dLabel1">
                              <?php
                              print dashboard_share_com_list();
                              /* $result = company_query('list');
                              foreach ($result as $copmanyRows) {
                              //                                                                                 if (!in_array($copmanyRows->nid, $user_companys)) {
                              ?>
                              <li><a href="/dashboard/company/set/<?php echo $copmanyRows->nid; ?>"><?php echo $copmanyRows->title; ?></a></li>
                              <?php
                              // }
                              }
                              ?>
                              </div>
                              </div>
                              </div>
                              </div>
                              </div>
                              <div class="dashboard-block-content">
                              <div class="row margin-5">
                              <div class="mid-tow-profile-block pull-left padding-5">

                              <div class="dashboard-user-feed-pic">
                              <?php
                              if (isset($company->field_logo['und']['0']['uri'])) {
                              $url = image_style_url('dashboard-user-feed-pic-img_52_52', $company->field_logo['und']['0']['uri']);
                              echo '<img typeof="foaf:Image" src="' . $url . '" alt="">';
                              } else {
                              echo '<i class="fa fa-fw fa-building"></i>';
                              }
                              ?>
                              </div>
                              </div>
                              <div class="mid-tow-profile-text pull-left padding-5 companys-feeds">

                              <?php
                              if (in_array($company->nid, $user_companys)) {
                              $sforms = drupal_get_form('statuses_box', $company, 'og');
                              print render($sforms);
                              }
                              ?>
                              </div>
                              </div>
                              </div>
                              </div>--> */
                            ?>
                            <div class="company-status-details">
                              <div id="cutom_statuses_stream_div" class="dashboard-block-lightgray company-feeds-contaner">
                                <div class="company-status-title clearfix">
                                  <div class="company-status-title-inner">M6Connect Feed</div>
                                </div>
                                <div class="dashboard-block-content"> <?php print views_embed_view('feeds_defaults_feed_items', 'block_1', 4891); ?> </div>
                              </div>
                            </div>
                          </div>
                        </div>
                      </div>
                    </div>  
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5 margin-bottom-10" id="dashboard-chating-panel" style="display: none;">
                      <div class="content-bar single-window-chat" id="single-window-chat">
                        <div class="clearfix">
                          <ul class="list-group">
                            <li class="list-group-item">
                              <span class="usr-name">User One</span>
                              <span class="audio-call" id="callBtn" style="margin-left: 20px; cursor: pointer;">
                                <i class="fa fa-phone" aria-hidden="true"></i>
                              </span>
                              <a class="close">×</a>
                            </li>
                          </ul>
                        </div>
                        <div class="clearfix">
                          <div class="user-messages margin-bottom-15 clearfix">
                            <div class="user-msg-input">
                              <div id="messages" class="list-group"></div>
                            </div>
                          </div>
                          <script src="/sites/all/libraries/emojione/emojionearea.js"></script>
                          <link href="/sites/all/libraries/emojione/emojionearea.min.css" rel="stylesheet">
                          <div class="input-group dashboard-chat-input">
                            <input type="hidden" name="chatusername" value="" class="chat-user-name">
                            <!-- <textarea class="form-control input-sp" placeholder="Chat here..." aria-describedby="basic-addon2" rows="2"></textarea> -->
                            <div class="form-textarea text-message-smilly pull-left" role="application">
                              <input type="button" name="audio" style="display: none;">
                              <input type="file" name="attachment[]" id="fileattachment" style="display: none;">
                              <div class="input-sp form-control" contenteditable="true" placeholder="" tabindex="0" dir="ltr" spellcheck="false" autocomplete="off" autocorrect="off" autocapitalize="off"></div>
                            </div>
                            <a href="javascript:void(0);" class="input-group-addon addon-sp" id="basic-addon2"><i class="fa fa-paper-plane" aria-hidden="true"></i></a>
                          </div>
                          <div class="userType"></div>
                          <div class="progress" style="display: none;">
                            <div class="progress-bar" role="progressbar"></div>
                          </div>
                          <a id="single_image" style="display: none;"></a>
                          <!-- <div class="modal" id="callWindow" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
                            <div class="modal-dialog" role="document">
                              <div class="modal-content">                                
                                <div class="modal-body">
                                  <div class="audioCallDiv row">
                                    <div class="col-md-4 callfromCall" style="margin-top: 5%;"></div>
                                    <div class="col-md-4 callphoneIcon">
                                      <img src="<?php //echo $base_url.'/'.path_to_theme().'/images/giphy.gif';?>" style="width: 50%;">
                                    </div>
                                    <div class="col-md-4 calltoCall" style="margin-top: 5%;"></div>
                                  </div>
                                  <div class="callDisconnectBtn" style="text-align: center;">
                                    <button class="disconnectBtn" style="border: 0; background: red;">
                                      <i class="fa fa-phone fa-3x" aria-hidden="true"></i>
                                    </button>
                                  </div>
                                  <div class="callVideo" style="display: none;">
                                    <video id="localVideo" muted="muted" autoplay class="col-md-6"></video>
                                    <video id="remoteVideo" autoplay class="col-md-6"></video>
                                  </div>
                                </div>                                
                              </div>
                            </div>
                          </div> -->                         
                          
                          <!-- <button class="from-call" id="fromCallBtn" data-toggle="modal" data-target="#callWindow" style="display: none;"></button>
                          <button class="answer-call" id="answerCallBtn" data-toggle="modal" data-target="#answerWindow" style="display: none;"></button> -->
                          <!-- <div id="myModal" class="modal fade" role="dialog">
                            <div class="modal-dialog modal-lg">
                              <div class="modal-content">
                                <div class="modal-header">
                                  <button type="button" class="close" data-dismiss="modal">&times;</button>                                  
                                </div>
                                <div class="modal-body"></div>
                              </div>
                            </div>
                          </div> -->
                        </div>
                      </div>
                    </div>                  
                    <div class="col-md-3 col-sm-12 col-xs-12 padding-5 margin-bottom-10" id="dashboard-rigth-panel">
                      <div class="middle_three dashboard_third clearfix">
                        <?php if ($page['middle_three']): ?>
                        <?php print render($page['middle_three']); ?>
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
  <div id="non-company-user-dialog"></div>
  <div id="incomplete-company-profile-dialog"></div>  
</div>
<!-- code for audio and video call -->

<div class="audio-call-window" style="display: none;">
  <div id="callWindow" style="display: none;">
    <div class="audioCallDiv row">
      <!-- <div class="col-md-4 callfromCall" style="margin-top: 5%;"></div> -->
      <div class="col-md-5 callphoneIcon">
        <div class="videodiv" style="background: #000; border: 1px solid #fff;">
          <video id="localVideo" muted="muted" autoplay style="width: 100%; min-height: 525px;"></video>
        </div>
        <div class="callfromCall margin-top-10 text-white"></div>
      </div>
      <div class="col-md-2 callphoneIcon text-center relative" style="top: 220px;">
        <img src="<?php echo $base_url.'/'.path_to_theme().'/images/giphy.gif';?>" style="width: 50%;">
      </div>
      <div class="col-md-5 callphoneIcon">
        <div class="videodiv clearfix" style="background: #000; border: 1px solid #fff;">
          <video id="remoteVideo" autoplay style="width: 100%; min-height: 525px;"></video>
        </div>
        <div class="callfromCall margin-top-10 text-white clearfix"></div>
      </div>
      <!-- <div class="col-md-4 calltoCall" style="margin-top: 5%;"></div> -->
    </div>
    <div class="callDisconnectBtn text-center">
      <button class="acceptBtn text-white" style="border: 0; background: green; padding: 6px 10px;">
        <i class="fa fa-phone fa-2x" aria-hidden="true"></i>
      </button>
      <button class="disconnectBtn text-white" style="border: 0; background: red; padding: 6px 10px;">
        <i class="fa fa-phone fa-2x" aria-hidden="true"></i>
      </button>
    </div>
    <!-- <div class="callVideo">
      <video id="localVideo" muted="muted" autoplay class="col-md-6"></video>
      <video id="remoteVideo" autoplay class="col-md-6"></video>
    </div> -->
  </div>

  <div id="answerWindow" style="display: none;">
    <div class="audioAnswerDiv row">
      <div class="fromCall margin-top-10 text-white clearfix"></div>
      <div class="col-md-4 phoneIcon">
        <img src="<?php echo $base_url.'/'.path_to_theme().'/images/giphy.gif';?>" style="width: 50%;">
      </div>
      <div class="toCall margin-top-10 text-white clearfix"></div>
    </div>
    <div class="callDisconnectBtn text-center">
      <button class="acceptBtn text-white" style="border: 0; background: green; padding: 6px 10px;">
        <i class="fa fa-phone fa-2x" aria-hidden="true"></i>
      </button>
      <button class="disconnectBtn text-white" style="border: 0; background: red; padding: 6px 10px;">
        <i class="fa fa-phone fa-2x" aria-hidden="true"></i>
      </button>
    </div>                              
    <div class="answerVideo clearfix">
      <video id="localVideo1" muted="muted" autoplay class="col-md-6"></video>
      <video id="remoteVideo1" autoplay class="col-md-6"></video>
    </div>
    <div class="callDisconnectBtn text-center">
      <button class="disconnectBtn text-white" style="border: 0; background: red; padding: 10px;">
        <i class="fa fa-phone fa-2x" aria-hidden="true"></i>
      </button>
    </div>

  </div>
</div>


<!-- end audio and video call -->
<script>
        jQuery('document').ready(function () {
            if (jQuery('#block-statuses-statuses .view-content .views-row').length > 10) {
//                jQuery('#block-statuses-statuses .view-content').append('<a href="javascript:" onclick="viewmore_personal_more(this)">view more</a>');
            }
            if (jQuery('#cutom_statuses_stream_div .view-content .views-row').length > 10) {
                //jQuery('#cutom_statuses_stream_div .view-content').append('<a href="javascript:" onclick="viewmore_copmay_more(this)">view more</a>');
            }

            window.count = 0;
            window.cmpcount = 0;
            viewmore_personal();
            viewmore_company();

            // for emoji on prochat
            jQuery(".input-sp").emojioneArea({
              /*container: ".input-sp",
              hideSource: true,*/
              useSprite: false,
              saveEmojisAs: "image",
              imageType: "png",
              shortnames: false,
            });
            jQuery("a#single_image").fancybox();
        });
        function viewmore_personal() {

            var currrent_num = window.count + 10;
            var counter = 0;
            jQuery('#block-statuses-statuses .view-content .views-row').each(function () {
                if (counter >= currrent_num) {
                    jQuery(this).hide();

                } else {
                    window.count = window.count + 1;
                }
                counter = counter + 1;

            });
        }
        function viewmore_company() {

            var currrent_num = window.cmpcount + 10;
            var counter = 0;
            jQuery('#cutom_statuses_stream_div .view-content .views-row').each(function () {
                if (counter >= currrent_num) {
                    jQuery(this).hide();

                } else {
                    window.cmpcount = window.cmpcount + 1;
                }
                counter = counter + 1;

            });
        }
        function viewmore_personal_more() {

            var currrent_num = window.count + 10;
            var counter = 0;
            jQuery('#block-statuses-statuses .view-content .views-row').each(function () {
                if (counter < currrent_num) {
                    if (jQuery(this).css('display') == 'none') {
                        jQuery(this).show();
                        window.count = window.count + 1;
                    }
                }

                counter = counter + 1;

            });
            if (currrent_num >= counter) {
                jQuery(this).hide();
            }
        }
        function viewmore_copmay_more(el) {

            var currrent_num = window.cmpcount + 10;
            var counter = 0;
            jQuery('#cutom_statuses_stream_div .view-content .views-row').each(function () {
                if (counter < currrent_num) {
                    if (jQuery(this).css('display') == 'none') {
                        jQuery(this).show();
                        window.cmpcount = window.cmpcount + 1;
                    }
                }

                counter = counter + 1;

            });
            if (currrent_num >= counter) {
                jQuery(el).hide();
            }
        }
    </script>
<?php endif; ?>
