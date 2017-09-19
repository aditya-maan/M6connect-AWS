<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<?php global $user; ?>
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
            <div class="middle-page">
              <div class="box">
                <div class="inner-box">
                <div class="white-bg">
            <div id="content" class="column" role="main">
                  <div class="highlighted"><?php print render($page['highlighted']); ?></div>
                  <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?>
                  <?php /*?><div class="text-center clearfix"> <?php print render($title_prefix); ?>
                    <?php if ($title): ?>
                    <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
                    <?php endif; ?>
                    <?php print render($title_suffix); ?> </div><?php */?>
                 
                  <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links">
                    <?php print render($action_links); ?>
                  </ul>
                  <?php endif; ?>
                   <?php if ($page['content']): ?>
                    <?php print '<div class="cust-proj-cover custom-prochat-page clearfix margin-bottom-10">
					<img src="http://m6connectg9kgomtyk4.devcloud.acquia-sites.com/sites/all/themes/m6connect/images/projects-default-banner.png">
					<div class="custom-prochat-cover-heading">PORTFOLIO</div>
					</div>'; ?> 
                    <?php print render($page['content']); ?>
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
  <div id="non-company-user-dialog"></div>
  <div id="incomplete-company-profile-dialog"></div>
</div>
<?php endif; ?>
