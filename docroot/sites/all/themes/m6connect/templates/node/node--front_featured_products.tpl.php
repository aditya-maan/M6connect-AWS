<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
 global $base_url;
 
?>

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
    hide($content['comments']);
    hide($content['links']); ?>
  <?php if($node->field_interior_layout['und'][0]['value'] == 01){ ?>
  <div class="interior_images margin-bottom-25">
    <div class="row margin-8">
      <?php
        if(isset($node,$node->field_interior_images['und']) && !empty($node) && !empty($node->field_interior_images['und'])){
				  foreach($node->field_interior_images['und'] as $key =>$value){				
				    $inter = $value['uri'];
				    print '<div class="col-md-4 col-sm-4 padding-8 margin-bottom-15"><img src="'. file_create_url($inter).'" /></div>';
				  }
				}
	    ?>
    </div>
  </div>
  <div class="clearfix">
    <h3>Description</h3>
    <div class="clearfix"> <?php print $node->body['und'][0]['value']; ?> </div>
  </div>
  <?php } if($node->field_interior_layout['und'][0]['value'] == 02){ ?>
  <div class="margin-bottom-25 clearfix">
		<?php
      if(isset($node,$node->field_interior_images['und']) && !empty($node) && !empty($node->field_interior_images['und'])){
        foreach($node->field_interior_images['und'] as $key =>$value){				
          $inter = $value['uri'];
          print '<div class="margin-bottom-15 clearfix"><img src="'. file_create_url($inter).'" /></div>';
        }
      }
    ?>
  </div>
  <div class="clearfix">
    <h3>Description</h3>
    <div class="clearfix"> <?php print $node->body['und'][0]['value']; ?> </div>
  </div>
  <?php } if($node->field_interior_layout['und'][0]['value'] == 03){ ?>
  <div class="row">
    <div class="col-md-7">
			<?php
        if(isset($node,$node->field_interior_images['und']) && !empty($node) && !empty($node->field_interior_images['und'])){
          foreach($node->field_interior_images['und'] as $key =>$value){				
            $inter = $value['uri'];
            print '<div class="clearfix margin-bottom-15"><img src="'. file_create_url($inter).'" /></div>';
          }
        }
      ?> 
    </div>
    <div class="col-md-5">
      <div class="clearfix">
        <h3>Description</h3>
        <div class="clearfix"> <?php print $node->body['und'][0]['value']; ?> </div>
      </div>
    </div>
  </div>
  <?php } if($node->field_interior_layout['und'][0]['value'] == 04){ ?>
  <div class="row">
    <div class="col-md-8">
      <div class="clearfix">
        <h3>Description</h3>
        <div class="clearfix"> <?php print $node->body['und'][0]['value']; ?> </div>
      </div>
    </div>
    <div class="col-md-4">
      <div class="interior_images margin-bottom-25">
				<?php
          if(isset($node,$node->field_interior_images['und']) && !empty($node) && !empty($node->field_interior_images['und'])){
            foreach($node->field_interior_images['und'] as $key =>$value){				
              $inter = $value['uri'];
              print '<div class="clearfix margin-bottom-15"><img src="'. file_create_url($inter).'" /></div>';
            }
          }
        ?> 
      </div>
    </div>
  </div>
  <?php } if($node->field_interior_layout['und'][0]['value'] == 05){ ?>
  <div class="row">
    <div class="col-md-6">
      <div class="clearfix">
        <h3>Description</h3>
        <div class="clearfix"> <?php print $node->body['und'][0]['value']; ?> </div>
      </div>
    </div>
    <div class="col-md-6">
        <div class="row margin-8">
          <?php
						if(isset($node,$node->field_interior_images['und']) && !empty($node) && !empty($node->field_interior_images['und'])){
							foreach($node->field_interior_images['und'] as $key =>$value){				
								$inter = $value['uri'];
								print '<div class="col-md-6 col-sm-6 padding-8 margin-bottom-15"><img src="'. file_create_url($inter).'" /></div>';
							}
						}
					?>
        </div>
    </div>
  </div>
  <?php } if(!$node->field_interior_layout['und'][0]['value']){ ?>
  <div class="margin-bottom-25 clearfix">
		<?php
      if(isset($node,$node->field_interior_images['und']) && !empty($node) && !empty($node->field_interior_images['und'])){
        foreach($node->field_interior_images['und'] as $key =>$value){				
          $inter = $value['uri'];
          print '<div class="margin-bottom-15 clearfix"><img src="'. file_create_url($inter).'" /></div>';
        }
      }
    ?>
  </div>
  <div class="clearfix">
    <h3>Description</h3>
    <div class="clearfix"> <?php print $node->body['und'][0]['value']; ?> </div>
  </div>
  <?php } ?>
  <?php    
			/*print '<pre>';
			print_r($node->field_interior_images);
			print '</pre>';
			die;*/
  ?>
  <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>
