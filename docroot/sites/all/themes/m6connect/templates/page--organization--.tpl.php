<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>

<header class="header" id="header" role="banner">
	<div class="page-width"> <?php print render($page['header']); ?>
		<div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?> </div>
	</div>
</header>
<div id="navigation">
	<div class="page-width"><?php print render($page['navigation']); ?></div>
</div>
<div id="page">
	<div id="main">
		<div id="content" class="column" role="main">
			<div class="box">
				<div class="inner-box"> <a id="main-content"></a>
					<?php if ($title): ?>
					<h1 class="page__title title" id="page-title"><?php print $title; ?></h1>
					<?php endif; ?>
					<?php print render($title_suffix); ?> <?php print $messages; ?> <?php print render($tabs); ?>
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
        print '<div class="field-name-label"><div class="field-label">'.t("Legal Name").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_legal_name', array('label'=>'hidden'))).'</div>';
        print '</div>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Structure").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_structure', array('label'=>'hidden'))).'</div>';
        print '</div>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Incorporation State").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_incorporated_state', array('label'=>'hidden'))).'</div>';
        print '</div>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Year Founded").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_year_founded', array('label'=>'hidden'))).'</div>';
        print '</div>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Number of Employees").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_number_of_employees', array('label'=>'hidden'))).'</div>';
        print '</div>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Phone").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_org_phone', array('label'=>'hidden'))).'</div>';
        print '</div>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Website").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_website', array('label'=>'hidden'))).'</div>';
        print '</div>';
         
        
        print '<div class="field-name-label"><div class="field-label">'.t("Address").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_org_address', array('label'=>'hidden'))).'</div>'; 
        print '</div>';
        print '</div>';
        
        print '<div class="description-wrapper">';
        
        print '<h1>'.t('Description').'</h1>';
        
        print '<div class="field-name-label"><div class="field-label">'.t("Services").'</div>';
        print '<div class="field-name-value">'.render(field_view_field('node', $node, 'field_service_description', array('label'=>'hidden'))).'</div>'; 
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
	<?php print render($page['footer']); ?> </div>
<?php print render($page['bottom']); ?> 