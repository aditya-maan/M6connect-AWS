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
  <?php $wrapperClass =''; if(isset($_SESSION['left_block_action']) && $_SESSION['left_block_action']=='open'){ $wrapperClass='active'; } ?>
  <div id="wrapper" class="<?php print $wrapperClass; ?> clearfix">
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
                  <?php print $messages; ?>
                  <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                  <?php endif; ?>
                  <div class="row margin-5 dashboard_content">
                    <div class="col-md-8 col-sm-8 col-xs-12 padding-5 margin-bottom-10">
                      <div class="middle_one company-profile-navigation clearfix">
                        <div class="middle_one_top clearfix">
                          <?php if ($page['middle_one_top']): ?>
                          <?php print render($page['middle_one_top']); ?>
                          <?php endif; ?>
                        </div>
                        <div class="dashboard-content dashboard-block-lightgray">
                          <div class="dashboard-block-content">
                            <?php if ($page['content']): ?>
                            <?php print render($page['content']); ?>
                            <?php endif; ?>
                          </div>
                        </div>
                      </div>
                    </div>
                    <div class="col-md-4 col-sm-4 col-xs-12 padding-5 margin-bottom-10">
                      <div class="middle_three dashboard_third clearfix">
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
<script>
    jQuery('document').ready(function () {
        jQuery('#block-statuses-statuses .view-content').append('<a href="javascript:" onclick="viewmore_personal_more()">view more</a>');
        jQuery('#cutom_statuses_stream_div .view-content').append('<a href="javascript:" onclick="viewmore_copmay_more()">view more</a>');

        window.count = 0;
        window.cmpcount = 0;
        viewmore_personal();
        viewmore_company();


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
    }
    function viewmore_copmay_more() {

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
    }
</script>