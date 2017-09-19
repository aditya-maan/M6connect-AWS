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
<?php if (!(module_exists('jquery_update') && module_exists('m6connect_misc'))) { ?>
<!--<script src="/sites/all/themes/m6connect/js/jquery1.11.3.min.js"></script>-->
<?php } ?>
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
                  <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                  <?php endif; ?>
                  <div class="right_content clearfix">
                    <div class="right_content_top clearfix">
                      <div class="company-header">
                        <?php
						if (isset($node->field_banner_image['und'])) {
							print '<img src="' . image_style_url('company_cover_1073_394', $node->field_banner_image['und'][0]['uri']) . '">';
						} else {


							print '<img src="/sites/all/themes/m6connect/images/default-company-cover.jpg" alt="default-company-cover">';

							//style="width:1073px;height:394px;"
						}
						?>
                        <?php //print render(field_view_field('node', $node, 'field_company_profile_cover_img', array('label' => 'hidden')));  ?>
                      </div>
                      <div class="right_content_top_inner">
                        <?php if ($page['right_content']): ?>
                        <?php print render($page['right_content']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
                    <div class="right_content_bottom clearfix">
                      <div class="row margin-5 company-header-stats">
                        <div class="col-md-3 col-sm-3 col-xs-12 padding-5 company_logo">
                          <div class="quick-fact-container-groups">
                            <div class="text-left">
                              <div class='quick-facts-groups pull-left'> <?php print $node->title; ?></div>
                            </div>
                          </div>
                        </div>
                        <div class="col-md-9 col-sm-9 col-xs-12 padding-5 company_details">
                          <div class="quick-fact-container">
                            <div class="company_logo_details">
                              <div class="company_title clearfix">
                                <div class="quick-employee pull-right">
                                  <?php
									if ($company->nid == arg(1)) {
										echo l('Employee Request', 'people/member', array('attributes' => array('class' => array('employee-request'))));
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
                        </div>
                      </div>
                      <div class="middle_one_bottom clearfix">
                        <?php if ($page['middle_one_bottom']): ?>
                        <?php print render($page['middle_one_bottom']); ?>
                        <?php endif; ?>
                        <div class="block recent-photos">
                          <h2 class="block-title">Recent Photos</h2>
                          <div class="content">
                            <div class="row margin-5">
                              <?php
							  /////////////////v4/////////////////////
							  $nid = $node->nid;
							  $nid = arg(1);
							  $fids = fn_get_own_shared_images($nid,4);

							  foreach ($fids as $key) {
								  echo '<div class="col-md-6 col-sm-6 col-xs-12 padding-5 margin-bottom-10 grid-item recent-photos-items"><a href="javascript:"  onclick="updateimage(\'/download/attachments/' . $key . '\')"  data-toggle="modal" data-target="#myModal"><img src="/download/attachments/' . $key . '"/ alt="photo" /></a></div>';
							  }
							  ////////////image////////////////            
							  ?>
                            </div>
                            <?php if($fids >=4){ ?>
                            <div class="clearfix text-right more-link"><a href="javascript:" onclick="jQuery('#photo-contaner').click()">View All</a> </div>
                            <?php } ?>
                          </div>
                        </div>
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
                      <div class="page_group_member">
                        <div class="middle_three_top clearfix">
                          <?php if ($page['middle_three_top']): ?>
                          <?php print render($page['middle_three_top']); ?>
                          <?php endif; ?>
                        </div>
                        <div class="middle_three_middle clearfix">
                          <?php if ($page['middle_three_middle']): ?>
                          <div id="member-block"> <?php print render($page['middle_three_middle']); ?> </div>
                          <?php endif; ?>
                        </div>
                        <div class="middle_three_bottom clearfix">
                          <?php if ($page['middle_three_bottom']): ?>
                          <?php print render($page['middle_three_bottom']); ?>
                          <?php endif; ?>
                        </div>
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
