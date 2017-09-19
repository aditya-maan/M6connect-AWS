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
		<div class="container"> <?php print render($page['header']); ?>
			<div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?> </div>
		</div>
	</header>
	<div id="navigation">
		<div class="container"><?php print render($page['navigation']); ?></div>
	</div>
	<div id="main">
		<div class="container-fluid">
			<div id="content" class="column" role="main">
				<div class="box">
					<div class="inner-box"> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?>
						<?php if ($action_links): ?>
						<ul class="action-links">
							<?php print render($action_links); ?>
						</ul>
						<?php endif; ?>
						<?php 
        //print_r($page);
       // print_r($node);
        //print render($content['field_legal_name']);
       if (arg(0) == 'node' && is_numeric(arg(1)) && !arg(2)) {
        print '<div class="all-field-values">';
          print '<div class="field-name-label"><div class="field-label"><h1>'.t("Project Name").'</h1></div>';
          print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_project_name', array('label'=>'hidden'))).'</div>';
          print '</div>';
        print '</div>';  
        
        print '<div class="description-wrapper">';
          print '<div class="field-name-label"><div class="field-label"><h1>'.t("Description").'</h1></div>';
          print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_public_description', array('label'=>'hidden'))).'</div>';
          print '</div>';
                
        print '</div>';
                      
               
        }elseif(arg(0) == 'node' && is_numeric(arg(1)) && arg(2)=='edit') {
          print render($page['content']);  
        }
        
        //print render($page['content']); 
      
      
      ?>
						<?php print $feed_icons; ?> </div>
				</div>
			</div>
		</div>
	</div>
	<div id="footer-message">
		<div class="container"> <?php print render($page['footer']); ?> </div>
	</div>
	<div class="container"><?php print render($page['bottom']); ?> </div>
</div>
