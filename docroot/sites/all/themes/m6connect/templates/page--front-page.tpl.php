<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
global $base_path;
?>
<?php global $user; ?>
<?php if ($user->uid == 0) : ?>

<div id="page">
  <header class="header front_header clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4 col-sm-4 col-xs-12 logo-txt"><?php print render($page['header_logo']); ?>
        <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
      <?php endif; ?></div>
        <div class="col-md-8 col-sm-8 col-xs-12 text-right"> <?php print render($page['header']); ?> </div>
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
  <div class="clearfix white-bg">
		<?php if ($page['preface']): ?>
    <div class="clearfix margin-bottom-45">
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
              <div class="clearfix margin-bottom-45">
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

</div>
<?php endif; ?>
