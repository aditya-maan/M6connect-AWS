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
  <div class="user-signup">
    <div class="inner-box">
      <header class="header" id="header" role="banner">
        <div class="container-fluid">
          <div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?></div>
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
      <?php $wrapperClass =''; if(isset($_SESSION['left_block_action']) && $_SESSION['left_block_action']=='open'){ $wrapperClass='active'; } ?>
  <div id="wrapper" class="<?php print $wrapperClass; ?> clearfix">
        <div id="sidebar-wrapper">
          <?php if ($page['left_content']): ?>
          <?php print render($page['left_content']); ?>
          <?php endif; ?>
        </div>
        <div id="page-content-wrapper">
          <div class="page-content inset">
            <div id="main-signup">
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
                      <div class="row margin-5">
                        <div class="col-md-8 col-sm-8 col-xs-12 padding-5">
                          <div class="new-organization-signup join-organization">
                            <?php if ($page['content']): ?>
                            <?php print render($page['content']); ?>
                            <?php endif; ?>
                          </div>
                        </div>
                        <div class="col-md-4 col-sm-4 col-xs-12 padding-5">
                          <div class="middle_three dashboard_third clearfix">
                            <?php if ($page['middle_three']): ?>
                            <?php  print render($page['middle_three']); ?>
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
    </div>
  </div>
</div>
