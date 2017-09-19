<?php
//kpr($rows);
/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
 global $user;
?>
<div class="cust-rfp-heading"><span>Company Users</span></div>
<div class="cmp-people-view rfp-clearification-view">
	<div class="cust-cmp-people-heading cust-rfp-clearification-heading">
		<div class="clearfix">
            <div class="col-md-1"><strong>Admin Support</strong></div>
			<div class="col-md-2"><strong>Full Name</strong></div>
            <div class="col-md-2"><strong>Username</strong></div>
			<div class="col-md-2"><strong>Email</strong></div>
            <div class="col-md-1"><strong>License</strong></div>
			<div class="col-md-2"><strong>Roles</strong></div>
			<div class="col-md-1"><strong>Last Login</strong></div>
			<div class="col-md-1"><strong>Settings</strong></div>
		</div>
	</div>
	<?php foreach ($rows as $id => $row): ?>
	<div<?php if ($classes_array[$id]) { print ' class="clearfix ' . $classes_array[$id] .'"';  } ?>>
	<?php print $row; ?>
	</div>
	<?php endforeach; ?>
</div>
