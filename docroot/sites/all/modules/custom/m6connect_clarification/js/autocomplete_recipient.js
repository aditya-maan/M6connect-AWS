//Drupal.behaviors.autocomplete_recipient = {
//  attach: function (context, settings) {
jQuery(document).ready(function(e) {
    jQuery(".clarification-msg-recipient").autocomplete({
	  minLength: 0,
	  /*source: function( request, response ) {
        jQuery.ajax({
          url: "/get-all-company-ajax",
          dataType: "json",
          data: {
            term: request.term
          },
          success: function( data ) {
            response( data );
          }
        });
	  },*/
	  source: function( request, response ) {
		jQuery.getJSON( "/get-all-company-ajax", {
		  term: request.term,
		  check: jQuery('.clarification-rfp-nid').val(),
		}, response );
	  },
	  change: function(event, ui) {
        if(!ui.item) {
		  //console.log(jQuery(".clarification-msg-recipient").val());
		  jQuery(".clarification-msg-recipient-company").val('');
		  jQuery(".field-recipient-company").val('_none');
		  //console.log(retn);
		  jQuery.post( "/get-all-company-email-ajax", { term: jQuery(".clarification-msg-recipient").val(), check: jQuery('.clarification-rfp-nid').val() })
            .done(function( retn ) {
				//console.log(retn);
			   if(retn.status && retn.cmpnid!=''){
                 jQuery(".clarification-msg-recipient-company").val(retn.cmpnid);
		         jQuery(".field-recipient-company").val(retn.cmpnid);
			   }else{
				 jQuery(".clarification-msg-recipient-company").val('');
		         jQuery(".field-recipient-company").val('_none');  
			   }
            })
			.fail(function( ret ) {
			  jQuery(".clarification-msg-recipient-company").val('');
		      jQuery(".field-recipient-company").val('_none');
			});
		  
		  
		  /*if(!(jQuery('span.recipient-required').length)){
		    jQuery('.form-item-field-choose-a-recipient-und-0-value').prepend('<span style="color:red;" class="recipient-required">* Choose Valid compamy Recipient from autocomplete</span>');
			jQuery('.clarification-msg-recipient').css('border-color','red'); 
		  }*/
		  return false;  
        }else{
		  /*if(jQuery('span.recipient-required').length){
			jQuery('span.recipient-required').remove();  
		  }
		  jQuery('.clarification-msg-recipient').removeAttr('style');*/
		}
      },
	  focus: function( event, ui ) {
        //jQuery(".clarification-msg-recipient").val( ui.item.label );
		jQuery(".clarification-msg-recipient-company").val('');
		jQuery(".field-recipient-company").val('');
		/*if(jQuery('span.recipient-required').length){
		  jQuery('span.recipient-required').remove();  
		}
		jQuery('.clarification-msg-recipient').removeAttr('style');*/
        return false;
      },
      select: function( event, ui ) {
        jQuery(".clarification-msg-recipient").val( ui.item.label );
        jQuery(".clarification-msg-recipient-company").val( ui.item.value );
		jQuery(".field-recipient-company").val( ui.item.value );	
		/*if(jQuery('span.recipient-required').length){
		  jQuery('span.recipient-required').remove();  
		}
		jQuery('.clarification-msg-recipient').removeAttr('style');*/
        return false;
      }     //data( "ui-autocomplete" )                                                  //.autocomplete( "instance" )
	}).data("ui-autocomplete") ._renderItem = function( ul, item ) {
	  var inner_html = '<a><div class="list_item_container-auto"><span class="image">' + item.image + '</span><label>' + item.label + '</label></div></a>';
      return jQuery( "<li>" )
	    .data("item.autocomplete", item)
        .append( inner_html )
        .appendTo( ul );
    };
});
//  }
//}