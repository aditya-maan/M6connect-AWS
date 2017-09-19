function m6_lessDays(theDate, days) {
    return new Date(theDate.getTime() - days*24*60*60*1000);
}

function m6_compair_dates(theDate1, days) {
  var theDate2 = new Date(theDate1.getTime() - days*24*60*60*1000);
  var currDate = new Date();
  return theDate2.getTime() - currDate.getTime();
}


Drupal.behaviors.jsCountdownTimerRFP = {
	attach: function (context) {
	  if(jQuery('.view-id-rfps').length && jQuery('.rfp-due-date-ticker').length){
	    jQuery('.rfp-due-date-ticker span.rfp-countdown-timer').each(function(index, element) {
		  if(jQuery(this).html()==''){
			var duedate = jQuery(this).closest('.rfp-due-date-ticker').data('duedate');
			var datediff = m6_compair_dates(new Date(duedate),3);
			var borderColor = "#0fa0df";
			var fontColor = "#000000";
			if(datediff <= 0){
			   borderColor = '#a52a2a';
			   fontColor = '#a52a2a';	
			}
			duedate = duedate.replace(/-/g, '/');
			var elementId = jQuery(this).attr('id');
			jQuery('#'+elementId).countdowntimer({
			  dateAndTime : duedate,
			  size : "xs",
			  //tickInterval : 1,
			  borderColor : borderColor,
			  fontColor : fontColor,
              backgroundColor : "#FFFFFF",
			  regexpMatchFormat: "([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2})",
      		  regexpReplaceWith: "$1 Days $2:$3:$4"
			});
		  }
	    });	
	 }
}};

