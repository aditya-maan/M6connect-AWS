<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
 //kpr($action_links);
?>

<div id="page">
  <header class="header" id="header" role="banner">
    <div class="container-fluid"> <?php print render($page['header']); ?>
      <div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?> </div>
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
            <div id="content" class="column" role="main">
              <div class="box">
                <div class="inner-box">
                  <div class="highlighted"><?php print render($page['highlighted']); ?></div>
                  <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print render($title_prefix); ?>
                  <?php if ($title): ?>
                  <h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
                  <?php endif; ?>
                  <?php print render($title_suffix); ?> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
                  <?php if ($action_links): ?>
                  <ul class="action-links list-inline">
                    <?php print render($action_links); ?>
                    <li><?php print flag_create_link('gallerylike', $node->nid); ?></li>
                  </ul>
                  <?php endif; ?>
                  <?php if(arg(0) == 'node' && is_numeric(arg(1)) && !arg(2)) {?>
                  <div class="row margin-10">
                    <div class="col-md-9 col-sm-9 col-xs-12 padding-10 margin-bottom-25">
                      <div class="gallery_left_content clearfix">
                        <div class="m6gallery-item-caption"><?php print render(field_view_field('node', $node, 'body', array('label' => 'hidden')));?></div>
                        <?php /////////////////////////////////////////////////////// page content start ////////////////////////////////////////////////////////////   ?>
                        <?php //pre($node,1); 
						 if(isset($node->node_gallery_media['und']) && !empty($node->node_gallery_media['und'])){
						   foreach($node->node_gallery_media['und'] as $k=>$v) {
						     if (isset($node_content) && $node_content['node_gallery_media']) {
				  ?>
                        <div class="cust-galley-items margin-bottom-10 text-center"> <?php print render($node_content['node_gallery_media'][$k]); ?> </div>
                        <?php	   
                             }
						   }
						 }
						 $field_medias_images = field_view_field('node', $node, 'node_gallery_media', array('label'=>'hidden', 'type' => 'file_rendered', 'settings' => array('file_view_mode' => 'node_gallery_file_display')));
						 print drupal_render($field_medias_images);
				  ?>
                        <?php /////////////////////////////////////////////////////// page content end //////////////////////////////////////////////////////////////   ?>
                      </div>
                    </div>
                    <div class="col-md-3 col-sm-3 col-xs-12 padding-10 margin-bottom-25">
                      <div class="gallery_right_content dashboard_third clearfix">
                        <div class="middle_three clearfix">
                          <?php if ($page['middle_three']): ?>
                          <?php print render($page['middle_three']); ?>
                          <?php endif; ?>
                        </div>
                        <?php //print render($page['sidebar_second']);?>
                      </div>
                    </div>
                  </div>
                  <?php 
			} else {
			  print render($page['content']);	
			}
			?>
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
