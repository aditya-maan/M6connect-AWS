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
  <header class="header" id="header" role="banner">
    <div class="container">
      <div id="top-navigation" class="row">
        <div class="col-md-3"> <?php print render($page['header_logo']); ?> </div>
        <div class="col-md-9"> <?php print render($page['top_navigation']); ?> </div>
      </div>
    </div>
  </header>
  <?php if ($page['slider']): ?>
  <div class="page_slider clearfix relative">
    <div class="clearfix"> <?php print render($page['slider']); ?> </div>
  </div>
  <?php endif; ?>
  <?php if ($page['content_bottom_full']): ?>
  <div class="content_bottom_full clearfix relative">
    <div class="clearfix"><?php print render($page['content_bottom_full']); ?></div>
  </div>
  <?php endif; ?>
  <div id="dashboard" class="white-bg padding-0 clearfix">
    <div class="container">
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
    </div>
  </div>
  <div class="clearfix white-bg padding-0">
    <?php if ($page['preface']): ?>
    <div class="preface_inner"><?php print render($page['preface']); ?> </div>
    <?php endif; ?>
    <div class="our_team_inner">
      <div class="container"><?php print render($page['out_team']); ?> </div>
    </div>
    <div class="bottom_content_inner">
      <div class="container">
        <div class="row">
          <div class="col-md-6"></div>
          <div class="col-md-6"><?php print render($page['bottom_content']); ?> </div>
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
        <div class="col-md-8 footer_right">
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
</div>
<?php endif; ?>
<?php if ($user->uid != 0) : ?>
<div id="page">
  <header class="header" id="header" role="banner">
    <div class="container">
      <div id="top-navigation" class="row">
        <div class="col-md-3"> <?php print render($page['header_logo']); ?> </div>
        <div class="col-md-9"> <?php print render($page['top_navigation']); ?> </div>
      </div>
    </div>
  </header>
  <?php if ($page['slider']): ?>
  <div class="page_slider clearfix relative">
    <div class="clearfix"> <?php print render($page['slider']); ?> </div>
  </div>
  <?php endif; ?>
  <?php if ($page['content_bottom_full']): ?>
  <div class="content_bottom_full clearfix relative">
    <div class="clearfix"><?php print render($page['content_bottom_full']); ?></div>
  </div>
  <?php endif; ?>
  <div id="dashboard" class="white-bg padding-0 clearfix">
    <div class="container">
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
    </div>
  </div>
  <div class="clearfix white-bg padding-0">
    <?php if ($page['preface']): ?>
    <div class="preface_inner"><?php print render($page['preface']); ?> </div>
    <?php endif; ?>
    <div class="our_team_inner">
      <div class="container"><?php print render($page['out_team']); ?> </div>
    </div>
    <div class="bottom_content_inner">
      <div class="container">
        <div class="row">
          <div class="col-md-6"></div>
          <div class="col-md-6"><?php print render($page['bottom_content']); ?> </div>
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
        <div class="col-md-8 footer_right">
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
</div>
<?php endif; ?>
