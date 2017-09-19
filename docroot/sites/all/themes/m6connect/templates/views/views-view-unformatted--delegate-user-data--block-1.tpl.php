<?php
//kpr($rows);
/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>

<h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="cust-view-heading cust-rfp-heading"><span>Granted Access</span></div>
<div class="cust-view-section rfp-clearification-view">
	<div class="cust-view-header cust-rfp-clearification-heading">
		<div class="clearfix">
			<div class="col-md-3 col-sm-3 col-xs-12"><strong>Name</strong></div>
			<div class="col-md-3 col-sm-3 col-xs-12"><strong>Email Address</strong></div>
			<div class="col-md-2 col-sm-2 col-xs-12"><strong>Last Login</strong></div>
            <div class="col-md-2 col-sm-2 col-xs-12"><strong>Expires</strong></div>
			<div class="col-md-2 col-sm-2 col-xs-12"><strong>Actions</strong></div>
		</div>
	</div>
	<?php foreach ($rows as $id => $row): ?>
	<div<?php if ($classes_array[$id]) { print ' class="clearfix ' . $classes_array[$id] .'"';  } ?>>
	<?php print $row; ?>
	</div>
	<?php endforeach; ?>
</div>
