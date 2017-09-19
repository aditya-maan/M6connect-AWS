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
    <ul class="nav nav-pills nav-stacked">
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/drafts') { print ' active'; } ?>"><a href="/insurance-certificates/drafts" class="menu__link">Draft Items</a></li>-->
      <li class="rfp-li-links<?php if($path == 'insurance-certificates/my-insurance-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/my-insurance-certificates" class="menu__link">My Insurance Certificates</a></li>


      <li class="rfp-li-links<?php if($path == 'insurance-certificates') { print ' active'; } ?>"><a href="/insurance-certificates" class="menu__link">Manage Certificates</a></li>
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/rejected-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/rejected-certificates" class="menu__link">Rejected Certificates</a></li>-->
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/resubmit-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/resubmit-certificates" class="menu__link">Resubmit Certificates</a></li>
      <li class="rfp-li-links<?php //if($path == 'insurance-certificates/approved-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/approved-certificates" class="menu__link">Approved Certificates</a></li>-->

      <li class="rfp-li-links<?php if($path == 'insurance-certificates/contracts') { print ' active'; } ?>"><a href="/insurance-certificates/contracts" class="menu__link">Contracts</a></li>
      <li class="rfp-li-links<?php if($path == 'insurance-certificates/archived') { print ' active'; } ?>"><a href="/insurance-certificates/archive" class="menu__link">Archived</a></li>


      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/draft-items') { print ' active'; } ?>"><a href="/insurance-certificates/draft-items" class="menu__link">Draft Items</a></li>-->
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/received') { print ' active'; } ?>"><a href="/insurance-certificates/received" class="menu__link">Received</a></li>-->
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/sent-items') { print ' active'; } ?>"><a href="/insurance-certificates/sent-items" class="menu__link is-active-trail active-trail active">Sent Items</a></li>-->
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/rejected-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/rejected-certificates" class="menu__link">Expired Certificate</a></li>-->
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/approved-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/approved-certificates" class="menu__link">Approved Certificates</a></li>-->
      <!--<li class="rfp-li-links<?php //if($path == 'insurance-certificates/resubmit-certificates') { print ' active'; } ?>"><a href="/insurance-certificates/resubmit-certificates" class="menu__link">Resubmit Certificate</a></li>-->
    </ul>
  </div>
</div>
