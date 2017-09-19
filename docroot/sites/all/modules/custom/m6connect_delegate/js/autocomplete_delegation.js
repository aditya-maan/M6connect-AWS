jQuery(document).ready(function(e) {
    jQuery(".delegation-user-entity-username").autocomplete({
	  minLength: 0,
	  delay: 0,
	  source: JSON.parse(Drupal.settings.m6connect_delegate.delegate_autoresult),
	  focus: function( event, ui ) {
        jQuery(".delegation-user-entity-username").val('');
		jQuery(".delegation-user-entity-user-to").val('');
        return false;
      },
	  change: function( event, ui ) {
		if(!ui.item) {
		  jQuery(".delegation-user-entity-user-to").val('');	
		}
		return false;
	  },
      select: function( event, ui ) {
		jQuery(".delegation-user-entity-username").val( ui.item.label );
		jQuery(".delegation-user-entity-user-to").val(ui.item.value);
        return false;
      }
	}).data("ui-autocomplete") ._renderItem = function( ul, item ) {
	  var inner_html = '<a><div class="list_item_container-auto"><label>' + item.label + '</label></div></a>';
      return jQuery( "<li>" )
	    .data("item.autocomplete", item)
        .append( inner_html )
        .appendTo( ul );
    };
});