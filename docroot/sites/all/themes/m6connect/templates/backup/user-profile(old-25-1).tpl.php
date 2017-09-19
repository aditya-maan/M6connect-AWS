<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>
<?php if (!(module_exists('jquery_update') && module_exists('m6connect_misc'))) { ?>
  <script src="/sites/all/themes/m6connect/js/jquery1.11.3.min.js"></script>
<?php } ?>
<script src="/sites/all/themes/m6connect/js/bootstrap.min.js"></script>
<script src="/sites/all/themes/m6connect/js/dropdown.js"></script>
<script src="/sites/all/themes/m6connect/js/collapse.js"></script>
  <script type="text/javascript" src="/sites/all/themes/m6connect/js/tab.js"></script>
<?php
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
module_load_include('inc', 'user_relationships', 'user_relationships_ui/user_relationships_ui.pages');
global $user;
$cuser = user_load(arg(1));
$cuser_groups = og_get_groups_by_user($cuser, 'node');
$companyNids = array_values($cuser_groups);
$companyNode = node_load($companyNids[0]);
$job_title_tid = $cuser->field_job_titles['und'][0]['target_id'];
$job_title_term = taxonomy_term_load($job_title_tid);
$job_title_name = $job_title_term->name;
//pre($name,1);
?>

<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
  <header> <?php print render($title_prefix); ?>
    <?php if (!$page && $title): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php if ($display_submitted): ?>
    <p class="submitted"> <?php print $cuser_picture; ?> <?php print $submitted; ?> </p>
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


  <div class='container'>
    <div class="clearfix">
      <div class='col-md-12 col-sm-12 col-xs-12 company-header'>
        <?php
			$profile_cover_img = render(field_view_field('user', $cuser, 'field_user_profile_cover_img', array('label' => 'hidden')));
			if ($profile_cover_img) {
				print $profile_cover_img;
			} else {
				echo '
				<div class="field field-name-field-user-profile-cover-img field-type-image field-label-hidden">
					<div class="field-items">
						<div class="field-item even">
							<img  alt="" src="' . $base_url . '/sites/default/files/airplane_window3-1170x448.jpg" typeof="foaf:Image">
						</div>
					</div>
				</div>';
			}
			?>
        <div class='company-header-stats clearafix'>
          <div class='row'>
            <div class='col-md-3 col-sm-3 col-xs-12 quick-fact-logo'>
              <div class='profile-photo'>
                <?php
				  $profile_photo = render(field_view_field('user', $cuser, 'field_user_profile_photo', array('label' => 'hidden')));
				  if ($profile_photo) {
					  print $profile_photo;
				  } else {
					  echo '<img  alt="" src="' . $base_url . '/sites/default/files/default_profile.jpg" typeof="foaf:Image">';
				  }
				  ?>
              </div>
            </div>
            <div class='col-md-6 col-sm-6 col-xs-12 quick-fact-container'>
              <div class="quick-facts"><?php echo $cuser->realname; ?></div>
              <div class="quick-fact-title">
                <?php
                      echo $companyNode->title;
                      if ($job_title_name) {
                          echo ' - ' . $job_title_name;
                      };
                      ?>
              </div>
            </div>
            <div class='col-md-3 col-sm-3 col-xs-12 quick-fact-container'> 
              <!--<div class='interactions-menu text-center'><a class='connect' href='#' title='Connect with Skanska!'>Connect</a>
                <a class='send-message' href='#' title='Send a Message to Skanska!'>Send Message</a></div>--> 
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class='row'>
      <div class='col-md-3 col-sm-3 col-xs-12'>
        <div class='company-profile-navigation'>
          <ul class="nav nav-tabs profile-navigation-tabs" role="tablist">
            <li class="active"><a href="#Newsfeed" aria-controls="Newsfeed" role="tab" data-toggle="tab">Newsfeed <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <li><a href="#profile" aria-controls="profile" role="tab" data-toggle="tab">Public Profile <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <li><a href="#employees" aria-controls="employees" role="tab" data-toggle="tab">Connections <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
          </ul>
          <h3>Company Information</h3>
          <div class="profile-navigation-map"> <?php print render(field_view_field('node', $companyNode, 'field_logo', array('label' => 'hidden'))); ?>
            <div class="com-info">
              <?php if ($job_title_name) {
                                echo '<strong>Position/Title</strong></br>' . $job_title_name . '</br>';
                } ?>
              <strong><?php echo $companyNode->title; ?></strong><?php print render(field_view_field('node', $companyNode, 'field_org_address', array('label' => 'hidden'))); ?><?php print render(field_view_field('node', $companyNode, 'field_org_phone', array())); ?> <br />
              <?php
				$isadmin = array_intersect(array_keys($user->roles), array(3)); //pre($isadmin);
				if (!empty($isadmin)) {
					$cuid = arg(1);
					$cusername = $cuser->name;
					$mlink = l('Masquerade as  ' . $cusername, 'masquerade/switch/' . $cuid, array('query' => array('token' => drupal_get_token('masquerade/switch/' . $cuid))));
            ?>
              <h3>Masquerade</h3>
              <div class="masquerade-link"><?php print $mlink; ?></div>
              <?php } ?>
            </div>
          </div>
          <!--work-->
          <div id="user_action">
          <?php 
				$block = module_invoke('user_relationship_blocks', 'block_view', 'actions');
				print render($block['content']);
		   ?>
          </div>
          <!--work-->
        </div>
      </div>
      <div class='col-md-6 col-sm-6 col-xs-12'>
        <div class='company-profile-content-area'>
          <div class="tab-content">
            <div role="tabpanel" class="tab-pane fade in active" id="Newsfeed">
              <div class='newsfeed'>
                <h1>Latest News</h1>
                <?php
//					print render(drupal_get_form('statuses_box',$user));
//					$blocknews = module_invoke('views', 'block_view', 'fbss_ur_stream-block_1');             
//					print render($blocknews['content']);
					?>
              </div>
            </div>
                     
            <div role="tabpanel" class="tab-pane fade" id="profile">
              <div class='public-profile'>
                <h1>Public Profile</h1>
                <?php
					print render(field_view_field('user', $cuser, 'field_first_name', array()));
					print render(field_view_field('user', $cuser, 'field_last_name', array()));
					print render(field_view_field('user', $cuser, 'field_phone', array()));
					$company_location = render(field_view_field('node', $companyNode, 'field_comp_locations', array('label' => 'hidden')));
					//pre($company_location,1);
					if ($company_location) {
						print $company_location;
					}
					?>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="employees">
              <div class='employees'>
                <h1>Connections</h1>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class='col-md-3 col-sm-3 col-xs-12'>
        <div class='photo-gallary'>
          <h2>Profile Photos</h2>
          <div class="row">
            <div class="col-sm-4 image-tile"> <?php print render(field_view_field('user', $cuser, 'field_user_profile_photo', array('label' => 'hidden'))); ?> </div>
          </div>
        </div>
        <div class='public-projects'>
          <h2>Professional Certifications</h2>
        </div>
        <div class='public-rfps'>
          <h2>M6 Endorsements</h2>
        </div>
      </div>
    </div>
  </div>
  <?php
//******************************* Node content end *********************************//	
?>
  <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>
