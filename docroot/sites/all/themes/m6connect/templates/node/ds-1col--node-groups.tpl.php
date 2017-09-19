<?php
/**
 * @file
 * Display Suite 1 column template.
 */
/*
  ?>
  <<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php print $ds_content; ?>
  </<?php print $ds_content_wrapper ?>>

  <?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
  <?php endif; ?>
 */
?>

<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
module_load_include('inc', 'og', 'og_ui/og_ui.admin');
//global $user;
//$node_id=arg(1);
//$nodeobj = node_load($node_id);
//$cuser = user_load($nodeobj->uid);
?>

<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
        <header> <?php print render($title_prefix); ?>
            <?php if (!$page && $title): ?>
                <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
            <?php endif; ?>
            <?php print render($title_suffix); ?>
            <?php if ($display_submitted): ?>
                <p class="submitted"> <?php print $user_picture; ?> <?php print $submitted; ?> </p>
            <?php endif; ?>
            <?php if ($unpublished): ?>
                <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
            <?php endif; ?>
        </header>
    <?php endif; ?>
    <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
//    print render($content);
//******************************* Node content start *********************************//
    ?>
    <div class='company-page'>
        <div class='company-profile-content-area'>
            <div class="tab-content">
                <div role="tabpanel" class="tab-pane fade in active" id="Newsfeed">
                    <div class='newsfeed'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="profile">
                    <div class='public-profile'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="summary">
                <div class='company-summary'>
            <div class="view_all_emp">
            <div class="post-heading">Members</div>
              <div class="dashboard-block-content">
                  <div class="user-connection-outer row margin-5" id="userblock">
                  <?php print render(og_ui_admin_account_custom('node', arg(1))); ?>
                </div>
              </div>
            </div>
          </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="diversity">
                    <div class='diversity-summary'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="location">
                    <div class='locations'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="businessTypes">
                    <div class='business-types'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="employees">
                    <div class='employees'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="view_all_emp">
                    <div class='view_all_emp'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="view_all_pro">
                    <div class='view_all_pro'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="view_all_rfp">
                    <div class='view_all_rfp'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="view-more-about">
                    <div class='view-more-about'>

                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="tab-photos">
                    <div class='tab-photos'>
                        <div class="post-heading">Photos</div>
                        <div class="dashboard-block-content">
                            <div class="user-connection-outer row margin-5 grid js-masonry">

                                <?php
/////////////////v4/////////////////////
                                $nid = $node->nid;
                                $nid = arg(1);
                                $fids = fn_get_own_shared_images($nid);

                                foreach ($fids as $key) {
                                    echo '<div class="grid-item"><a href="javascript:"  onclick="updateimage(\'/download/attachments/' . $key . '\')"  data-toggle="modal" data-target="#myModal"><img src="/download/attachments/' . $key . '"/ alt="photo" /></a></div>';
                                }
////////////image////////////////
                                ?>

                            </div>
                        </div>
                    </div>
                </div>
                <div role="tabpanel" class="tab-pane fade" id="tab-files">
                    <div class='tab-files'>
                        <div class="post-heading clearfix">Files <span class="pull-right"><?php
                        $options = array();
                        $options['attributes']['class'][] = 'use-ajax btn btn-primary btn-add-files';
                        echo l('Add File', 'add/group-files/' . arg(1) . '/nojs', $options);
                        ?></span></div>
                        <div class="dashboard-block-content">
                        
                        <div id="group-files">
                            <?php
                            print render(m6connect_dashboard_get_file_view(arg(1)));
                            ?>
                        </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>

    <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>

<script>
    jQuery('document').ready(function () {
        //fews feed show
        jQuery('.profile-tab-open').click(function () {
            //debugger;
            if (this.classList[1] == "out-side") {
                jQuery('#middle-content-nav li').each(function () {
                    jQuery(this).removeClass('active');
                });
            }
            jQuery('#block-statuses-statuses').hide();
        });
        jQuery('#newsfeed-open').click(function () {
            jQuery('#user-feeds .tab-pane').each(function () {
                jQuery(this).removeClass('active');
                jQuery(this).removeClass('in');
            });
            jQuery('#block-statuses-statuses').show();
        });
        grid = jQuery('.grid').masonry({
            // specify itemSelector so stamps do get laid out
            itemSelector: '.grid-item',
            columnWidth: 172
        });
        jQuery('#photo-contaner').click(function () {
            setTimeout(function () {
                grid.masonry();
            }, 200);
        });
        jQuery('#user-Notification').click(function () {
            setTimeout(function () {
//                jQuery('#user-Notification').parent().toggleClass('open');
            }, 200);

        });
<?php
$groups = og_get_groups_by_user();
if (in_array(arg(1), $groups['node'])) {
    ?>
            jQuery('#block-statuses-statuses').prepend('<div class="company-status-title company-status-title-inner">Share With Others </div>');
    <?php
} else {
    ?>
            jQuery('#block-statuses-statuses').prepend('<div class="company-status-title company-status-title-inner">News Feeds </div>');

    <?php
}
?>
        jQuery('#statuses-box--2').prepend('<div class="user-profile-share-image"><?php print $rcuser_profile_photo = (isset($cuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'dashboard-user-feed-pic-img_52_52', 'path' => $cuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : ''; ?></div>');
        var htm = jQuery('#share-connection').html();
        jQuery('#block-statuses-statuses').prepend(htm);
        jQuery('#share-connection').html('');
        jQuery('#block-statuses-statuses').css('position', 'relative');
        jQuery('#block-statuses-statuses .share-container').css('position', 'absolute');
        jQuery('#block-statuses-statuses .share-container').css('top', '97px');
        jQuery('#block-statuses-statuses .share-container').css('left', '360px');
        jQuery(".dropdownF").dropdown();

    });
    function updateimage(path) {
        jQuery('#model-img').attr('src', '');
        jQuery('#model-img').attr('src', path);
    }
</script>

