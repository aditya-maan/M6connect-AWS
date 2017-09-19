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
  <header class="header front_header clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4"> <?php print render($page['header_logo']); ?> </div>
        <div class="col-md-8 text-right"> <?php print render($page['header']); ?> </div>
      </div>
    </div>
  </header>
  <?php if ($page['slider']): ?>
  <div class="page_slider clearfix relative">
    <div class="clearfix"> <?php print render($page['slider']); ?> </div>
  </div>
  <?php endif; ?>
  <div id="main">
    <div id="content" class="column clearfix" role="main">
      <div class="box clearfix">
        <div class="inner-box clearfix">
	        <div class="white-bg">
  	        <div class="front_data_tabs clearfix"> <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
            <?php if ($action_links): ?>
            <ul class="action-links">
              <?php print render($action_links); ?>
            </ul>
            <?php endif; ?>
            <div class="clearfix margin-bottom-45"> <?php print render($page['content']); ?> </div>
          </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="clearfix white-bg">
		<?php if ($page['preface']): ?>
    <div id="preface" class="clearfix margin-bottom-45">
      <div class="preface_inner"><?php print render($page['preface']); ?> </div>
    </div>
    <?php endif; ?>
    <?php if ($page['out_team']): ?>
    <div class="clearfix out_team margin-bottom-45">
      <div class="out_team_inner clearfix">
        <div class="container"> <?php print render($page['out_team']); ?> </div>
      </div>
    </div>
    <?php endif; ?>
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
</div>
<?php endif; ?>
<?php if ($user->uid != 0) : ?>
<?php drupal_add_library('system', 'ui.dialog'); ?>
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
  <div id="preface" class="<?php if(!$page['preface']) { print 'dispaly_none'; } else { print 'preface'; } ?>">
    <div class="container-fluid"><?php print render($page['preface']); ?></div>
  </div>
  <div id="main">
    <div class="container">
      <div id="content" class="column" role="main">
        <div class="box">
          <div class="inner-box"> <?php print render($page['highlighted']); ?> <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
            <?php if ($action_links): ?>
            <ul class="action-links">
              <?php print render($action_links); ?>
            </ul>
            <?php endif; ?>
            <?php print render($page['content']); ?></div>
        </div>
      </div>
      <?php
      // Render the sidebars to see if there's anything in them.
      $sidebar_first  = render($page['sidebar_first']);
      $sidebar_second = render($page['sidebar_second']);
    ?>
      <?php if ($sidebar_first || $sidebar_second): ?>
      <aside class="sidebars"> <?php print $sidebar_first; ?> <?php print $sidebar_second; ?> </aside>
      <?php endif; ?>
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
  <!--<div class="text-center"> <strong>Thank you for joining M6Connect! During the registration process, you indicated that you would like to join a company that already exists within the website. To gain access to this company's information, your request to join must be approved by the company administrator. In order to complete this process, please contact M6Connect Customer Support at support@m6connect.com</strong> </div>--> 
</div>
<?php endif; ?>
