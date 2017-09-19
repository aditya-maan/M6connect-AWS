jQuery(document).ready(function(e) {
	Drupal.ajax.prototype.commands.console_log = function(ajax, data, status) {
      console.log(data.var1);
    };
	
	Drupal.ajax.prototype.commands.checkbox_action = function(ajax, data, status) {
      jQuery(data.selector).prop('checked',data.action);
    };
	
	Drupal.ajax.prototype.commands.insertInCkeditor = function(ajax, data, status) {
	  var textareaInstance = jQuery(data.selector).attr('id');
      CKEDITOR.instances[textareaInstance].setData(data.arguments);
    };
	
	jQuery('input.workflow-order').live('blur',function(){
	   var inputvalue = jQuery(this).val();  
	   jQuery(this).val(inputvalue.replace(/[^0-9]/g,''));
	});
	
	if (Drupal.settings.hasOwnProperty('m6connect_routing') && Drupal.settings.m6connect_routing.hasOwnProperty('routing_type_select') && Drupal.settings.m6connect_routing.routing_type_select) {
		if(jQuery('body').find('select[name="routing-type"]').length){
		  jQuery('select[name="routing-type"]').val(Drupal.settings.m6connect_routing.routing_type_select);
		  jQuery('select[name="routing-type"]').trigger('change');
		}
	}
	
	if (Drupal.settings.hasOwnProperty('m6connect_routing') && Drupal.settings.m6connect_routing.hasOwnProperty('routing_save_dialog') && Drupal.settings.m6connect_routing.routing_save_dialog == 1) {
	  jQuery('#routing-dialog-container').dialog({
		  autoOpen: false,
		  width: 490,
		  modal: true,
		  resizable: false,
		  buttons: {
			  'Send': function () {
				  var triggerElement = jQuery(this).find('span.trigger-element-class').text();
				  if(triggerElement!=''){
				    jQuery(triggerElement).trigger('click');
				  }
				  jQuery(this).dialog("close");
				  jQuery('#routing-dialog-container').html('');
			  },
			  'Cancel': function () {
				  jQuery(this).dialog("close");
				  jQuery('#routing-dialog-container').html('');
			  }
		  },
		  open: function () {
			  jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
			  jQuery('.ui-dialog-titlebar').hide();
		  }
	  });
	  
	  jQuery('.routing-slip-node-save').click(function(ev){
		 if(isNaN(ev.isTrigger)){
		   jQuery('#routing-dialog-container').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to send out this routing slip?</strong></div><span class="trigger-element-class" style="display:none;">.routing-slip-node-save</span>');
		   
		   jQuery('#routing-dialog-container').dialog('open');
		   ev.preventDefault();
		   return false;
		 }
	  });
	  
	  jQuery('.routing-type-node-delete').click(function(ev){
		 if(isNaN(ev.isTrigger)){
		   jQuery('#routing-dialog-container').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you would like to delete this routing template?</strong></div><span class="trigger-element-class" style="display:none;">.routing-type-node-delete</span>');
		   jQuery('#routing-dialog-container').dialog('open');
		   ev.preventDefault();
		   return false;
		 }
	  });
	}
	if (Drupal.settings.hasOwnProperty('m6connect_routing') && Drupal.settings.m6connect_routing.hasOwnProperty('routing_type_save_dialog') && Drupal.settings.m6connect_routing.routing_type_save_dialog == 1) {
	  var routingTypeSaveData= Drupal.settings.m6connect_routing.routing_type_save_data;
	  jQuery('#routing-type-dialog-container').dialog({
		  autoOpen: true,
		  width: 550,
		  modal: true,
		  resizable: false,
		  buttons: {
			  'Ok': function () {
				  jQuery(this).dialog("close");
				  jQuery(this).html('');
			  }
		  },
		  open: function () {
			  jQuery(this).html('<div class="text-center"><strong>'+routingTypeSaveData+'</strong></div>');
			  jQuery('.ui-dialog-titlebar').hide();
		  }
	  });
	}
});


