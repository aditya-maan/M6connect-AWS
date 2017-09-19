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
<div class="cust-rfp-heading">
 <span>
 <a class="report-btn" style="color:#fff; text-decoration:none;" href="/rfp-proposal-report/<?php echo arg(1); ?>">
 <img src="<?php echo $base_url; ?>/sites/all/themes/m6connect/images/icon-news2.png"> PDF Report</a>
 </span>
 </div>

<div class="rfp-proposal-view rfp-clearification-view">
	<div class="cust-rfp-proposal-heading cust-rfp-clearification-heading">
		<div class="clearfix">
			<div class="col-md-2"><strong>Company</strong></div>
			<div class="col-md-2"><strong>Proposal Name</strong></div>
			<div class="col-md-2"><strong>Date Submitted</strong></div>
			<div class="col-md-1"><strong>Bid Amount</strong></div>
			<div class="col-md-2"><strong>Bid Type</strong></div>
            <div class="col-md-3"><strong>Bidder Diversity Type</strong></div>
		</div>
	</div>
	<?php foreach ($rows as $id => $row): ?>
	<div<?php if ($classes_array[$id]) { print ' class="clearfix ' . $classes_array[$id] .'"';  } ?>>
	<?php print $row; ?>
	</div>
	<?php endforeach; ?>
</div>
