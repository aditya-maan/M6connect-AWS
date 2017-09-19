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
      <div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?> </div>
    </div>
  </header>
  <div id="navigation">
    <div class="container"><?php print render($page['navigation']); ?></div>
  </div>
  <div id="main">
    <div class="container-fluid">
      <div class="box">
        <div class="inner-box">
          <div id="content" class="column" role="main"> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?>
            <?php if ($action_links): ?>
            <ul class="action-links">
              <?php print render($action_links); ?>
            </ul>
            <?php endif; ?>
            <?php  //print render($page['content']);   ?>
            <?php /////////////////////////////////////////////////////// page content start ////////////////////////////////////////////////////////////   ?>
            <?php //pre($node,1); 
			 if(isset($node->node_gallery['cover_item']) && !empty($node->node_gallery['cover_item'])){
			   $galleryItemNid = $node->node_gallery['cover_item'];	 
			   $galleryItemNode = node_load($galleryItemNid);
			   //$node = node_load($nid);
			   $node_view = node_view($galleryItemNode, 'full');
			   $rendered_node = drupal_render($node_view);
			   echo $rendered_node;
			 }
			 ?>
            <?php /////////////////////////////////////////////////////// page content end //////////////////////////////////////////////////////////////   ?>
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
