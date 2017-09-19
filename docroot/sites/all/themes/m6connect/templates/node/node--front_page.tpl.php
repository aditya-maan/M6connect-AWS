<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
?>
<?php if ($user->uid == 0) : ?>

<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
  <header> <?php print render($title_prefix); ?>
    <?php if (!$page && $title): ?>
    <h2<?php print $title_attributes; ?>> <a href="<?php print $node_url; ?>"><?php print $title; ?></a> </h2>
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
    hide($content['links']); ?>
  <?php /*?><div class="project_posting clearfix">
    <div class="container">
      <div class="clearfix featured-front-page">
        <div class="row">
          <div class="col-md-6">
            <h2 class="margin-bottom-25"><?php print $node->field_branding_title['und'][0]['value']; ?></h2>
            <p><?php print $node->field_branding_body['und'][0]['value']; ?></p>
          </div>
          <div class="col-md-6">
            <?php $branding = $node->field_branding_image['und'][0]['uri']; ?>
            <img alt="branding" src="<?php print $branding_image = file_create_url($branding); ?>"> </div>
        </div>
        <div class="clearfix">
          <hr />
        </div>
        <div class="row">
          <div class="col-md-6">
            <?php $technology = $node->field_latest_technology_image['und'][0]['uri']; ?>
            <img alt="technology" src="<?php print $technology_image = file_create_url($technology); ?>"> </div>
          <div class="col-md-6">
            <h2 class="margin-bottom-25"><?php print $node->field_latest_technology_title['und'][0]['value']; ?></h2>
            <p><?php print $node->field_latest_technology_body['und'][0]['value']; ?></p>
          </div>
        </div>
        <div class="clearfix">
          <hr />
        </div>
        <div class="row">
          <div class="col-md-6">
            <h2 class="margin-bottom-25"><?php print $node->field_branding_title['und'][0]['value']; ?></h2>
            <p><?php print $node->field_branding_body['und'][0]['value']; ?></p>
          </div>
          <div class="col-md-6">
            <?php $branding = $node->field_branding_image['und'][0]['uri']; ?>
            <img alt="branding" src="<?php print $branding_image = file_create_url($branding); ?>"> </div>
        </div>
      </div>
    </div>
  </div><?php */?>
  <?php /*?><div class="project_posting clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-6 col-sm-6 project_posting_left margin-bottom-45">
          <div class="project_posting_inner clearfix">
            <div class="clearfix margin-bottom-25 project_posting_img">
              <?php $technology = $node->field_latest_technology_image['und'][0]['uri']; ?>
              <img alt="technology" src="<?php print $technology_image = file_create_url($technology); ?>">
            </div>
            <div class="clearfix project_posting_body">
              <h3><?php print $node->field_latest_technology_title['und'][0]['value']; ?></h3>
              <p><?php print $node->field_latest_technology_body['und'][0]['value']; ?></p>
            </div>
          </div>
        </div>
        <div class="col-md-6 col-sm-6 project_posting_right margin-bottom-45">
          <div class="project_posting_inner clearfix">
            <div class="clearfix margin-bottom-25 project_posting_img">
              <?php $branding = $node->field_branding_image['und'][0]['uri']; ?>
              <img alt="branding" src="<?php print $branding_image = file_create_url($branding); ?>"> </div>
            <div class="clearfix project_posting_body">
              <h3><?php print $node->field_branding_title['und'][0]['value']; ?></h3>
              <p><?php print $node->field_branding_body['und'][0]['value']; ?></p>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div><?php */?>
  <?php /*?><div class="technology clearfix">
    <div class="container">
      	<div class="row margin-0">
  			<?php
  			$result = getProposalFrontBoxQuery($nid);
  			$output = '';
  			if(isset($result) && !empty($result)){
  				foreach($result as $key=>$value){        
  					$fontIcon = '';
  					$techClass = '';
  					if ($key % 4 == 0){
  						$fontIcon = '<i class="fa fa-pencil" aria-hidden="true"></i>';
  						$techClass = 'technology_light';
  					}else if ($key % 4 == 1){
  						$fontIcon = '<i class="fa fa-search" aria-hidden="true"></i>';
  						$techClass = 'technology_dark';
  					}else if ($key % 4 == 2){        
  						$fontIcon = '<i class="fa fa-paint-brush" aria-hidden="true"></i>';
  						$techClass = 'technology_dark';
  					}else if ($key % 4 == 3){
  						$fontIcon = '<i class="fa fa-star-o" aria-hidden="true"></i>';
  						$techClass = 'technology_light';
  					}        
  					if ($key % 2 == 0){
  						print  '<div class="col-md-6 padding-0 '.$techClass.'">
  												 <div class="technology_inner clearfix">
  													 <div class="row margin-5">
  														 <div class="col-md-2 col-sm-2 padding-5 margin-bottom-25">'.$fontIcon.'</div>
  														 <div class="col-md-10 col-sm-10 padding-5">
  															 <h3>'.$value->field_front_box_title_value.'</h3>
  															 <p>'.$value->field_front_box_body_value.'</p>
  														 </div>
  													 </div>
  												 </div>
  											 </div>';        
  					}else{        
  						print  '<div class="col-md-6 padding-0 '.$techClass.'">
  												 <div class="technology_inner clearfix">
  													 <div class="row margin-5">
  														 <div class="col-md-2 col-sm-2 padding-5 margin-bottom-25">'.$fontIcon.'</div>
  														 <div class="col-md-10 col-sm-10 padding-5">
  															 <h3>'.$value->field_front_box_title_value.'</h3>
  															 <p>'.$value->field_front_box_body_value.'</p>
  														 </div>
  													 </div>
  												 </div>
  											 </div>';        
  					}        
  				}
  			}
        ?>
      </div>
    </div>
  </div><?php */?>
  <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>
<?php endif; ?>
<?php if ($user->uid != 0) : ?>
<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
  <header> <?php print render($title_prefix); ?>
    <?php if (!$page && $title): ?>
    <h2<?php print $title_attributes; ?>> <a href="<?php print $node_url; ?>"><?php print $title; ?></a> </h2>
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
    hide($content['links']); ?>
    <?php /*?><div class="project_posting clearfix">
    <div class="container">
      <div class="clearfix featured-front-page">
        <div class="row">
          <div class="col-md-6">
            <h2 class="margin-bottom-25"><?php print $node->field_branding_title['und'][0]['value']; ?></h2>
            <p><?php print $node->field_branding_body['und'][0]['value']; ?></p>
          </div>
          <div class="col-md-6">
            <?php $branding = $node->field_branding_image['und'][0]['uri']; ?>
            <img alt="branding" src="<?php print $branding_image = file_create_url($branding); ?>"> </div>
        </div>
        <div class="clearfix">
          <hr />
        </div>
        <div class="row">
          <div class="col-md-6">
            <?php $technology = $node->field_latest_technology_image['und'][0]['uri']; ?>
            <img alt="technology" src="<?php print $technology_image = file_create_url($technology); ?>"> </div>
          <div class="col-md-6">
            <h2 class="margin-bottom-25"><?php print $node->field_latest_technology_title['und'][0]['value']; ?></h2>
            <p><?php print $node->field_latest_technology_body['und'][0]['value']; ?></p>
          </div>
        </div>
        <div class="clearfix">
          <hr />
        </div>
        <div class="row">
          <div class="col-md-6">
            <h2 class="margin-bottom-25"><?php print $node->field_branding_title['und'][0]['value']; ?></h2>
            <p><?php print $node->field_branding_body['und'][0]['value']; ?></p>
          </div>
          <div class="col-md-6">
            <?php $branding = $node->field_branding_image['und'][0]['uri']; ?>
            <img alt="branding" src="<?php print $branding_image = file_create_url($branding); ?>"> </div>
        </div>
      </div>
    </div>
  </div><?php */?>
  <?php /*?><div class="project_posting clearfix">
    <div class="row">
      <div class="col-md-6 col-sm-6 project_posting_left margin-bottom-45">
        <div class="project_posting_inner clearfix">
          <div class="clearfix margin-bottom-25 project_posting_img">
            <?php $technology = $node->field_latest_technology_image['und'][0]['uri']; ?>
            <img alt="technology" src="<?php print $technology_image = file_create_url($technology); ?>"> </div>
          <div class="clearfix project_posting_body">
            <h3><?php print $node->field_latest_technology_title['und'][0]['value']; ?></h3>
            <p><?php print $node->field_latest_technology_body['und'][0]['value']; ?></p>
          </div>
        </div>
      </div>
      <div class="col-md-6 col-sm-6 project_posting_right margin-bottom-45">
        <div class="project_posting_inner clearfix">
          <div class="clearfix margin-bottom-25 project_posting_img">
            <?php $branding = $node->field_branding_image['und'][0]['uri']; ?>
            <img alt="branding" src="<?php print $branding_image = file_create_url($branding); ?>"> </div>
          <div class="clearfix project_posting_body">
            <h3><?php print $node->field_branding_title['und'][0]['value']; ?></h3>
            <p><?php print $node->field_branding_body['und'][0]['value']; ?></p>
          </div>
        </div>
      </div>
    </div>
  </div><?php */?>
  <?php /*?><div class="technology clearfix">
    	<div class="row margin-0">
			  <?php
       	$result = getProposalFrontBoxQuery($nid);
			  $output = '';
  			if(isset($result) && !empty($result)){
  				foreach($result as $key=>$value){        
  					$fontIcon = '';
  					$techClass = '';
  					if ($key % 4 == 0){
  						$fontIcon = '<i class="fa fa-pencil" aria-hidden="true"></i>';
  						$techClass = 'technology_light';
  					}else if ($key % 4 == 1){
  						$fontIcon = '<i class="fa fa-search" aria-hidden="true"></i>';
  						$techClass = 'technology_dark';
  					}else if ($key % 4 == 2){        
  						$fontIcon = '<i class="fa fa-paint-brush" aria-hidden="true"></i>';
  						$techClass = 'technology_dark';
  					}else if ($key % 4 == 3){
  						$fontIcon = '<i class="fa fa-star-o" aria-hidden="true"></i>';
  						$techClass = 'technology_light';
  					}        
  					if ($key % 2 == 0){
  						print  '<div class="col-md-6 padding-0 '.$techClass.'">
  												 <div class="technology_inner clearfix">
  													 <div class="row margin-5">
  														 <div class="col-md-2 col-sm-2 padding-5 margin-bottom-25">'.$fontIcon.'</div>
  														 <div class="col-md-10 col-sm-10 padding-5">
  															 <h3>'.$value->field_front_box_title_value.'</h3>
  															 <p>'.$value->field_front_box_body_value.'</p>
  														 </div>
  													 </div>
  												 </div>
  											 </div>';        
  					}else{        
  						print  '<div class="col-md-6 padding-0 '.$techClass.'">
  												 <div class="technology_inner clearfix">
  													 <div class="row margin-5">
  														 <div class="col-md-2 col-sm-2 padding-5 margin-bottom-25">'.$fontIcon.'</div>
  														 <div class="col-md-10 col-sm-10 padding-5">
  															 <h3>'.$value->field_front_box_title_value.'</h3>
  															 <p>'.$value->field_front_box_body_value.'</p>
  														 </div>
  													 </div>
  												 </div>
  											 </div>';        
  					}        
  				}
  			}
        ?>
      </div>
    </div><?php */?>
  <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>
<?php endif; ?>
