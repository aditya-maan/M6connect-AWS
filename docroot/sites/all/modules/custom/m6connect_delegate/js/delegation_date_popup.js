// JavaScript Document
Drupal.behaviors.delegation_date = {
  attach: function (context, settings) {
	jQuery('.delegation-user-entity-startdate').one('focus', function() {
	  jQuery('.delegation-user-entity-startdate').datepicker('option', {
		onClose: function(selected) {
		  jQuery('.delegation-user-entity-enddate').one('focus', function() {
			jQuery('.delegation-user-entity-enddate').datepicker('option', 'minDate', selected);
		  });
		  jQuery('.delegation-user-entity-enddate').datepicker('option', 'minDate', selected);
		}
	  });
	});
  }
};