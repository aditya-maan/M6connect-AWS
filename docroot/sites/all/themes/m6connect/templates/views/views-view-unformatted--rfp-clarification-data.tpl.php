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
<div class="cust-rfp-heading"><span>Clarifications</span></div>
<div class="rfp-clearification-view">
	<div class="cust-rfp-clearification-heading">
		<div class="clearfix">
            <div class="col-md-1 col-sm-1 col-xs-12"><strong>No#</strong></div>
			<div class="col-md-1 col-sm-1 col-xs-12"><strong>Type</strong></div>
			<div class="col-md-1 col-sm-1 col-xs-12"><strong>Status</strong></div>
			<div class="col-md-4 col-sm-4 col-xs-12"><strong>Subject</strong></div>
			<div class="col-md-2 col-sm-2 col-xs-12"><strong>From</strong></div>
			<div class="col-md-3 col-sm-3 col-xs-12"><strong>Message Date</strong></div>
		</div>
	</div>
	<?php foreach ($rows as $id => $row): ?>
	<?php /*?><div<?php if ($classes_array[$id]) { print ' class="clearfix ' . $classes_array[$id] .'"';  } ?>> <?php */?>
	<?php print $row; ?>
	<?php /*?></div><?php */?>
	<?php endforeach; ?>
</div>
