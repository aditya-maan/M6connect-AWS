<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<?php
/*if (arg(0) == 'node') {
  $nid = arg(1);
}
$path = current_path();
$node = node_load($nid);
$content_type = $node->type;
*/?>
<?php global $user; ?>
<?php //if ($user->uid == 0) : ?>

<div id="page">
  <div class="container-fluid">
    <div class="box">
      <div class="inner-box">
        <?php /*?><header class="header" id="header" role="banner">
				<?php if ($logo): ?>
				<a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
				<?php endif; ?>
			</header><?php */?>
        <div id="main">
          <div id="content" class="column frontbox" role="main">
            <div class="white-bg"> <?php print render($page['highlighted']); ?>
              <?php if ($title): ?>
              <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
              <?php endif; ?>
              <?php if ($action_links): ?>
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
              <?php endif; ?>
              <?php print $messages; ?>
              <?php //if ($user->uid == 0) { ?>
              <?php print render($page['content']); ?>
              <?php //} ?>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
<?php //endif; ?>
