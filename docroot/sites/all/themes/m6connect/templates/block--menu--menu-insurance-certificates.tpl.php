<?php
/**
 * @file
 * Returns the HTML for a block.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728246
 */
?>
<?php
//dpm($content);
$path = current_path();
?>
<div id="<?php print $block_html_id; ?>" class="rfp-clearification-center <?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="block-inner">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>><?php print $title; ?></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <!--<div class="content"><?php //print $content; ?></div>-->
    <ul class="menu nav navbar-nav navbar-right">
<!--      <li class="menu__item is-active-trail is-leaf first leaf active-trail">
        <a href="/insurance-certificates" title="" class="menu__link is-active-trail active-trail active">Approval Queue</a>
      </li>
      <li class="menu__item is-leaf leaf">
        <a href="/insurance-certificates/my-insurance-certificates" class="menu__link">My Insurance Certificates</a>
      </li>-->
      <!--<li class="menu__item is-leaf last leaf">
        <a href="/insurance-certificates/contracts" class="menu__link">Contracts</a>
      </li>-->
    </ul>
  </div>
</div>
