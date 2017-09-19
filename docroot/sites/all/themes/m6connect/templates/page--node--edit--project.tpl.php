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
  <header class="header" id="header" role="banner">
    <div class="container-fluid"> <?php print render($page['header']); ?>
      <div id="top-navigation" class="row"><?php print render($page['top_navigation']); ?></div>
    </div>
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
                  <div class="white-bg">
                    <div class="right_content clearfix">
                      <div class="content_inner_pages">
                        <div class="highlighted"><?php print render($page['highlighted']); ?></div>
                        <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print render($title_prefix); ?>
                        <?php if ($title): ?>
                        <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
                        <?php endif; ?>
                        <?php print render($tabs); ?> <?php print render($page['help']); ?>
                        <?php if ($action_links): ?>
                        <ul class="action-links">
                          <?php print render($action_links); ?>
                        </ul>
                        <?php endif; ?>
                        <?php print render($title_suffix); ?> <?php print $messages; ?> <?php print render($page['content']); ?> </div>
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
