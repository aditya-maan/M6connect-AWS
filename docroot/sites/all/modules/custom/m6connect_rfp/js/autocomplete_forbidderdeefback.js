////source: JSON.parse(Drupal.settings.m6connect_rfp.rfp_tellus),
//jQuery(document).ready(function(e) {
Drupal.behaviors.m6connect_rfp_autocomplete_text = {
    attach: function () {
	jQuery(".bidder_feedback_message_msg").each(function(index, element) {
        
    
    jQuery(this).autocomplete({
	 
	  minLength: 0,
	  delay: 0,
	  source: ["Definitely bidding","Need more time","Don't think we will be considered", "Not a fair bid effort", "Job is too big","Job is too small","Not something we do","Would like to but just too busy","Too busy"],
	  focus: function( event, ui ) {
        //jQuery(".bidder_feedback_message_msg").val('');
		jQuery(this).val('');
        return false;
      },
	  change: function( event, ui ) {
		if(!ui.item) {
//		  jQuery(".delegation-user-entity-user-to").val('');	
		}
		return false;
	  },
      select: function( event, ui ) {
		jQuery(this).val( ui.item.label );
        return false;
      }
	}).focus(function(){            
         jQuery(this).data("ui-autocomplete").search(jQuery(this).val());
    }).data("ui-autocomplete") ._renderItem = function( ul, item ) {
	  var inner_html = '<a><div class="list_item_container-auto"><label>' + item.label + '</label></div></a>';
      return jQuery( "<li>" )
	    .data("item.autocomplete", item)
        .append( inner_html )
        .appendTo( ul );
    };
	});
}};
//});