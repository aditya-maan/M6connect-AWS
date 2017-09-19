<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<div id="page">
  <div class="front_top_header clearfix">
    <div class="container">
      <?php if ($page['top_header']): ?>
      <?php print render($page['top_header']); ?>
      <?php endif; ?>
    </div>
  </div>
  <header class="header front_header clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4">
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
          <?php print render($page['header_logo']); ?> </div>
        <div class="col-md-8 text-right"> <?php print render($page['header']); ?> </div>
      </div>
    </div>
  </header>
  <div class="page_slider clearfix margin-bottom-45">
    <div class="clearfix">
      <?php if ($page['slider']): ?>
      <?php print render($page['slider']); ?>
      <?php endif; ?>
    </div>
  </div>
  <div class="project_posting clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-6 project_posting_left">
          <div class="project_posting_inner clearfix">
            <?php if ($page['project_posting_left']): ?>
            <?php print render($page['project_posting_left']); ?>
            <?php endif; ?>
          </div>
        </div>
        <div class="col-md-6 project_posting_right">
          <div class="project_posting_inner clearfix">
            <?php if ($page['project_posting_right']): ?>
            <?php print render($page['project_posting_right']); ?>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div id="preface" class="clearfix technology <?php if(!$page['preface']) { print 'dispaly_none'; } else { print 'preface'; } ?>">
    <div class="container"><?php print render($page['preface']); ?></div>
  </div>
  <div id="main">
    <div class="container">
      <div id="content" class="column clearfix" role="main">
        <div class="box clearfix">
          <div class="inner-box clearfix"> <?php print render($page['highlighted']); ?> <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
            <?php if ($action_links): ?>
            <ul class="action-links">
              <?php print render($action_links); ?>
            </ul>
            <?php endif; ?>
            <?php print render($page['content']); ?> </div>
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
