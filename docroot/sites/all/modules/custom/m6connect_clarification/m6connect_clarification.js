/*var ev = new jQuery.Event('remove'),
orig = jQuery.fn.remove;
jQuery.fn.remove = function() {
  jQuery(this).trigger(ev);
  return orig.apply(this, arguments);
}*/
Drupal.behaviors.m6connect_clarification = {
  attach: function (context, settings) {
	if(jQuery('body').find('.node-clarification-form .droppable-browse-button').hasClass('button')){
	   var browEle = jQuery('body').find('.node-clarification-form .droppable-browse-button');
	   browEle.removeClass('button');
	   
	   jQuery('body').find('.node-clarification-form div.droppable-message>span').html('<i class="fa fa-cloud-upload"></i>Drag and Drop Files Here to Upload'); 
	   jQuery('body').find('.node-clarification-form div.droppable-standard-upload>span').html('or Click');
	   jQuery('body').find('.node-clarification-form div.droppable-standard-upload').append('<span> to upload files</span>');
	   jQuery('body').find('.node-clarification-form .droppable-browse-button').text('Browse');
	}
	
	jQuery('.clarification-msg-submit').click(function(event){
	  jQuery(".clarification-msg-recipient").blur();
	  if(jQuery(".clarification-msg-recipient").length){
		if(jQuery('.clarification-msg-recipient-company').val()==''){ 
		  if(!(jQuery('span.recipient-required').length)){
		    jQuery('.form-item-field-choose-a-recipient-und-0-value').prepend('<span style="color:red;" class="recipient-required">* Choose Valid compamy Recipient from autocomplete</span>');
			jQuery('.clarification-msg-recipient').css('border-color','red'); 
		  }
		  jQuery('.clarification-msg-recipient').focus();
		  event.preventDefault();
		  return false; 
		}
	  }
	});
  } 
};

jQuery(document).ready(function($){
  /*jQuery('.tabingblocknav li a').each(function(i){
    var is_active = jQuery(this).parent('li').hasClass('active'); 
    var tabid= jQuery(this).attr('href');
    if(is_active){
      jQuery(tabid).show();
    }else{
	  jQuery(tabid).hide();
    }
  });
  jQuery('.tabingblocknav li a').click(function(){ 
    var is_active = jQuery(this).parent('li').hasClass('active'); 
	//if(is_active)return false;
	var tabid= jQuery(this).attr('href'); 
	jQuery('.tabingblocknav li.active').removeClass('active');
	jQuery(this).parent('li').addClass('active');
	jQuery('.tabingblock').hide();
	jQuery(tabid).show();
	return false;
  });*/	
  
  jQuery('#clarification-msg-success-dialog', '.cust-clarication-content').dialog({
	  autoOpen: false,
	  width: 320,
	  minHeight: 100, 
	  height: 100,
	  modal: true,
	  resizable: false,
	  buttons: {
		'Okay': function() {
		  jQuery( this ).dialog( "close" );
		}
	  }
	});
  
  Drupal.ajax.prototype.commands.clarificationViewRefresh = function(ajax, response, status) {
	var view_dom_obj = Drupal.settings.views.ajaxViews;
	var ajax_path = Drupal.settings.views.ajax_path;
	for (var obj in view_dom_obj) {
	  if (view_dom_obj.hasOwnProperty(obj)) {
		jQuery.get( ajax_path,view_dom_obj[obj])
		  .done(function( data ) {
			jQuery(data[2]['selector']).replaceWith(data[2]['data']);
			Drupal.attachBehaviors(jQuery(data[2]['selector']));
		});
	  }
	}
  }	
  
  Drupal.ajax.prototype.commands.openSuccessdialog = function(ajax, response, status) {
	jQuery('.ui-dialog-titlebar').hide();
	jQuery('#clarification-msg-success-dialog').dialog('open');
  }	 
});

