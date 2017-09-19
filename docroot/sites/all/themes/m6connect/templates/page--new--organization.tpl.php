<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<?php global $user, $company, $base_url; ?>
<?php
$site_url = $GLOBALS['base_url'];
$path = current_path();
?>

<div id="page">
  <header class="header front_header clearfix">
    <div class="container-fluid">
      <div class="row">
        <div class="col-md-4 text-center">
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
        <div class="col-md-8 text-right user-login-header"> <?php print render($page['header']); ?> </div>
      </div>
    </div>
  </header>
  <?php if ($page['slider']): ?>
  <div class="page_slider clearfix relative">
    <div class="clearfix"> <?php print render($page['slider']); ?> </div>
  </div>
  <?php endif; ?>
  <div class="clearfix user-organization-page new-user-organization-page">
    <div class="user-login-page relative clearfix">
      <div class="user-login-page-flex user-login-page-img">
        <div class="col-md-4 padding-0 relative user-login-page-left">
          <?php if ($page['preface']): ?>
          <div class="user-sign-in-content user-sign-up-content text-white clearfix">
            <div class="preface_inner"><?php print render($page['preface']); ?> </div>
          </div>
          <?php endif; ?>
        </div>
        <div class="col-md-8 padding-0 relative user-login-page-right">
          <div class="row">
            <div class="col-md-8 col-md-offset-2">
              <div class="user-page-organization clearfix margin-bottom-45"> <a id="main-content"></a> <?php print $messages; ?> <?php print render($page['help']); ?>
                <?php if ($action_links): ?>
                <ul class="action-links">
                  <?php print render($action_links); ?>
                </ul>
                <?php endif; ?>
                <?php print render($page['register']); ?> <?php print render($page['content']); ?> </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
