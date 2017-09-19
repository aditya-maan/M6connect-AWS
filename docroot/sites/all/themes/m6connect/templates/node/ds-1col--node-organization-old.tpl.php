<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
 module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
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
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script> 
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script> 
  <script type="text/javascript" src="/sites/all/themes/m6connect/js/tab.js"></script>
  <div class='company-page container'>
    <div class="clearfix company-header">
      <div class='col-md-12 col-sm-12 col-xs-12 company-header'> <?php print render(field_view_field('node', $node, 'field_company_profile_cover_img', array('label' => 'hidden'))); ?>
        <div class='company-header-stats clearafix'>
          <div class='row'>
            <div class='col-md-3 col-sm-3 col-xs-12 quick-fact-logo'>
              <div class='profile-photo'><?php print render(field_view_field('node', $node, 'field_logo', array('label' => 'hidden'))); ?></div>
            </div>
            <div class='col-md-6 col-sm-6 col-xs-12 quick-fact-container'><span class='quick-facts'><?php echo print $node->title; ?></span> </div>
            <div class='col-md-3 col-sm-3 col-xs-12 quick-fact-container'> 
              <!--<div class='interactions-menu text-center'><a class='connect' href='#' title='Connect with Skanska!'>Connect</a><a class='send-message' href='#' title='Send a Message to Skanska!'>Send Message</a></div>--> 
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
          <li ><a href="#profile" aria-controls="profile" role="tab" data-toggle="tab">Public Profile <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
          <li><a href="#summary" aria-controls="summary" role="tab" data-toggle="tab">Company Summary <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
          <li><a href="#diversity" aria-controls="diversity" role="tab" data-toggle="tab">Supplier Diversity <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
          <li><a href="#location" aria-controls="location" role="tab" data-toggle="tab">Location(s) <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
          <li><a href="#businessTypes" aria-controls="businessTypes" role="tab" data-toggle="tab">Business Types <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
          <!--<li><a href="#employees" aria-controls="employees" role="tab" data-toggle="tab">Employees <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>-->
        </ul>
        <h3>Employees</h3>
        <?php
                    $block_employee = module_invoke('views', 'block_view', 'people_invite_listing-block_1');
                    print render($block_employee['content']);
                    ?>
        <div class="profile-navigation-map">
          <?php
                        $block = module_invoke('addressfield_staticmap', 'block_view', 'addressfield_staticmap');
                        print render($block['content']);
                        ?>
          <div class="com-info"> <strong><?php print $node->title; ?></strong> <?php print render(field_view_field('node', $node, 'field_org_address', array('label' => 'hidden'))); ?>
            <div class="left-social-icons row text-center">
              <div class="col-md-3">
                <?php
                            //print render(field_view_field('node', $node, 'field_facebook', array('label' => 'hidden'))); 
                            if (isset($node->field_facebook['und']) && isset($node->field_facebook['und'][0]['value']) && !empty($node->field_facebook['und'][0]['value'])) {
                                $flink = $node->field_facebook['und'][0]['value'];
                                echo l('<i class="fa fa-facebook-square"></i>', $flink, array('html' => true));
                            }
                            ?>
              </div>
              <div class="col-md-3">
                <?php
                            //print render(field_view_field('node', $node, 'field_twitter', array('label' => 'hidden'))); 
                            if (isset($node->field_twitter['und']) && isset($node->field_twitter['und'][0]['value']) && !empty($node->field_twitter['und'][0]['value'])) {
                                $tlink = $node->field_twitter['und'][0]['value'];
                                echo l('<i class="fa fa-twitter"></i>', $tlink, array('html' => true));
                            }
                            ?>
              </div>
              <div class="col-md-3">
                <?php
                            //print render(field_view_field('node', $node, 'field_instagram', array('label' => 'hidden'))); 
                            if (isset($node->field_instagram['und']) && isset($node->field_instagram['und'][0]['value']) && !empty($node->field_instagram['und'][0]['value'])) {
							  $ilink = $node->field_instagram['und'][0]['value'];
							  echo l('<i class="fa fa-instagram"></i>', $ilink, array('html' => true));
                            }
                            ?>
              </div>
            </div>
            <?php print render(field_view_field('node', $node, 'field_website', array('label' => 'hidden'))); ?> <?php print render(field_view_field('node', $node, 'field_org_phone', array('label' => 'hidden'))); ?> <?php print render(field_view_field('node', $node, 'field_company_email', array('label' => 'hidden'))); ?> </div>
        </div>
      </div>
    </div>
    <div class='col-md-6 col-sm-6 col-xs-12'>
      <div class='company-profile-content-area'>
        <div class="tab-content">
          <div role="tabpanel" class="tab-pane fade in active" id="Newsfeed">
            <div class='newsfeed'>
              <h1>Newsfeed</h1>
              <div class="group_newsfeed">
              <?php
				  //print render(drupal_get_form('statuses_box'));
				  print render(drupal_get_form('statuses_box', ''));
				  $blocknews = module_invoke('views', 'block_view', 'fbss_ur_stream-block_2');
				  print render($blocknews['content']);
				  ?>
                  </div>
            </div>
          </div>
          <div role="tabpanel" class="tab-pane fade" id="profile">
            <div class='public-profile'>
              <h1><?php print $node->title; ?></h1>
              <?php print render(field_view_field('node', $node, 'field_description', array())); ?> <?php print render(field_view_field('node', $node, 'step_co_public_profile', array())); ?> </div>
          </div>
          <div role="tabpanel" class="tab-pane fade" id="summary">
            <div class='company-summary'>
              <h1>Company Summary</h1>
              <?php
				  print render(field_view_field('node', $node, 'field_owner_name', array()));
				  print render(field_view_field('node', $node, 'field_description', array()));
				  print render(field_view_field('node', $node, 'field_legal_structure', array()));
				  print render(field_view_field('node', $node, 'field_legal_name', array()));
				  print render(field_view_field('node', $node, 'field_year_founded', array()));
				  print render(field_view_field('node', $node, 'field_annual_revenue', array()));
				  print render(field_view_field('node', $node, 'field_number_of_employees', array()));
				  print render(field_view_field('node', $node, 'field_org_phone', array()));
				  print render(field_view_field('node', $node, 'field_org_address', array()));
				  print render(field_view_field('node', $node, 'field_website', array()));
				  ?>
            </div>
          </div>
          <div role="tabpanel" class="tab-pane fade" id="diversity">
            <div class='diversity-summary'>
              <h1>Supplier Diversity</h1>
              <?php print render(field_view_field('node', $node, 'field_diversity_program', array())); ?> <?php print render(field_view_field('node', $node, 'field_diversity_credentials', array())); ?> </div>
          </div>
          <div role="tabpanel" class="tab-pane fade" id="location">
            <div class='locations'>
              <h1>Locations</h1>
              <?php
				  print render(field_view_field('node', $node, 'field_comp_locations', array()));
				  ?>
            </div>
          </div>
          <div role="tabpanel" class="tab-pane fade" id="businessTypes">
            <div class='businessTypes'>
              <h1>Business Types</h1>
              <?php
				  print render(field_view_field('node', $node, 'field_facilities_construction', array()));
				  print render(field_view_field('node', $node, 'field_regions', array()));
				  print render(field_view_field('node', $node, 'field_industry_naicss', array()));
				  print render(field_view_field('node', $node, 'field_products_service_unspsc', array()));
				  ?>
            </div>
          </div>
          <div role="tabpanel" class="tab-pane fade" id="employees">
            <div class='employees'>
              <h1>Employees</h1>
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class='col-md-3 col-sm-3 col-xs-12'>
      <div class='photo-gallary'>
        <h2>Project Photos</h2>
        <?php
			$block_photo_project = module_invoke('views', 'block_view', 'public_posted_projects-block_3');
			print render($block_photo_project['content']);
			?>
      </div>
      <div class='public-projects'>
        <h2>Public Projects</h2>
        <?php
			$block_public_project = module_invoke('views', 'block_view', 'public_posted_projects-block_1');
			print render($block_public_project['content']);
			?>
      </div>
      <div class='public-rfps'>
        <h2>Public Posted RFPs</h2>
        <?php
			$block_rfp_project = module_invoke('views', 'block_view', 'public_posted_projects-block_2');
			print render($block_rfp_project['content']);
			?>
      </div>
    </div>
  </div>
  </div>
  <?php
    //print render(field_view_field('node', $node, 'field_logo', array('label'=>'hidden')));	
    //print render(field_view_field('node', $node, 'field_company_profile_cover_img', array('label'=>'hidden')));
    //print render(field_view_field('node', $node, 'field_number_of_employees', array()));
    //print render(field_view_field('node', $node, 'step_co_public_profile', array()));
    //echo "<h1><b>company summary</b></h1></br>";
    //print $node->title;
    //print render(field_view_field('node', $node, 'field_owner_name', array()));
    //print render(field_view_field('node', $node, 'field_description', array()));
    //print render(field_view_field('node', $node, 'field_legal_structure', array()));
    //print render(field_view_field('node', $node, 'field_legal_name', array()));
    //print render(field_view_field('node', $node, 'field_year_founded', array()));
    //print render(field_view_field('node', $node, 'field_annual_revenue', array()));
    //print render(field_view_field('node', $node, 'field_number_of_employees', array()));
    //print render(field_view_field('node', $node, 'field_org_phone', array()));
    //print render(field_view_field('node', $node, 'field_org_address', array()));
    //print render(field_view_field('node', $node, 'field_website', array()));
    //echo "<h1><b>Supplier diversity</b></h1></br>";
    //print render(field_view_field('node', $node, 'field_diversity_program', array('label'=>'hidden')));
    //echo "<h1><b>Location </b></h1></br>";
    //print render(field_view_field('node', $node, 'step_co_location', array()));
    //print render(field_view_field('node', $node, 'field-location-name', array()));
    //print render(field_view_field('node', $node, 'field_comp_locations', array()));
    //echo "<h1><b>Business types </b></h1></br>";
    //print render(field_view_field('node', $node, 'field_facilities_construction', array()));
    //print render(field_view_field('node', $node, 'field_regions', array()));
    //print render(field_view_field('node', $node, 'field_industry_naicss', array()));
    //print render(field_view_field('node', $node, 'field_products_service_unspsc', array()));
//******************************* Node content end *********************************//	
    ?>
  <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>
