jQuery(document).ready(function ($) {
  //jQuery('.node-insurance_certificates-form .form-field-name-field-submit-to-project .chosen-single span').text('Select Project');	
  //jQuery('.node-insurance_certificates-form .form-field-name-field-submit-to-contract .chosen-single span').text('Select Contract');
  
  jQuery('.form-field-name-field-attach-certificates .description br').each(function(){
    //jQuery("br").remove();
	jQuery(this).replaceWith(' ');
  });
  //jQuery('.form-field-name-field-attach-certificates .description br').replaceWith(' ');
   
  jQuery('.group-insurance-tab ul.horizontal-tabs-list li.horizontal-tab-button a').click(function(){
    var sessionName = jQuery('h1.insurance-cert-title').data('sess');
	var nid = jQuery('h1.insurance-cert-title').data('nid'); //alert(nid);
	if(jQuery(this).closest('li').hasClass('horizontal-tab-button-0')){
	  sessionStorage.setItem(sessionName+'_tab', 'group-ins-cert-info-tab'); 
	}else if(jQuery(this).closest('li').hasClass('horizontal-tab-button-1')){
	  sessionStorage.setItem(sessionName+'_tab', 'group-ins-appr-feedback-tab');  
	  ////////////////////////////
	  jQuery.ajax({
	    type: 'post',
		url: '/change-seened-msg-status/'+nid,
	   	data: 'nid=' + encodeURI(nid),
	   	success: function(msg){
			    	
		}
	  });
	  ///////////////////////////
	}
  });
  if(jQuery('body.node-type-insurance-certificates').find('h1.insurance-cert-title').length){
    var sessionName = jQuery('h1.insurance-cert-title').data('sess');
	var nid = jQuery('h1.insurance-cert-title').data('nid');
	var tabClass = sessionStorage.getItem(sessionName+'_tab');
	if(tabClass!==null){
	  jQuery("."+tabClass).data("horizontalTab").focus();  
	  ////////////////////////////
	  jQuery.ajax({
	    type: 'post',
		url: '/change-seened-msg-status/'+nid,
	   	data: 'nid=' + encodeURI(nid),
	   	success: function(msg){
			    	
		}
	  });
	  /////////////////////////// 
	  
	}
  }
  
  if(Drupal.settings.hasOwnProperty('m6connect_ins_cert') && Drupal.settings.m6connect_ins_cert.hasOwnProperty('insurance_reminder_dialog') && Drupal.settings.m6connect_ins_cert.insurance_reminder_dialog == 1){
	jQuery("#insurance-reminder-dialog").dialog({ 
	  autoOpen: false,
	  width: 500,
	  modal: true,
	  resizable: false,
	  buttons: {
		Ok: function() {
		  var item_id = jQuery(this).find('.data-fc-item-id').text();
	      var routing_id = jQuery(this).find('.data-routing').text();
		  var message = jQuery('.request-approval-reminder-message-text').val();
		  if(message==''){
		    if(!(jQuery('.request-approval-reminder-message').find('.message-required-text').length)){
				  jQuery( '.request-approval-reminder-message label[for="edit-message"]' ).after('<div class="message-required-text" style="color:red;">Please enter Message first</div>');
				}
				return false;
			}
		  var target_form = jQuery('.request_approval_reminder_dialog_form');
		  
		  jQuery.post('/insurance-reminder/'+routing_id+'/'+item_id, { values:target_form.serialize() } ).done(function(data){ //console.log(data);
			if(data.approval_reminder_count>0){
			  jQuery('body').find('.request-approval-reminder-link-button-'+item_id).css('background','#419641');
			  jQuery('.request-approval-reminder-link-'+item_id+' .request-bid-intent-link-count').each(function(index, element) {
				 jQuery(this).addClass('notification-count').text(data.approval_reminder_count);
              });
			  if(data.comment_box.selector!=''){
				jQuery(data.comment_box.selector).html(data.comment_box.html);
				Drupal.attachBehaviors(jQuery('.routing_feedback_message_form'));  
			  }
			}
		  });
		  jQuery( this ).dialog( "close" );
		},
		Cancel: function() {
		  //jQuery( this ).dialog('close');
		  //jQuery( this ).html('');
		  var item_id = jQuery(this).find('.data-fc-item-id').text();
	      var routing_id = jQuery(this).find('.data-routing').text();
		  var message = jQuery('.request-approval-reminder-message-text').val();
		  if(message==''){
		    if(!(jQuery('.request-approval-reminder-message').find('.message-required-text').length)){
				  jQuery( '.request-approval-reminder-message label[for="edit-message"]' ).after('<div class="message-required-text" style="color:red;">Please enter Message first</div>');
				}
				return false;
			}
		  var target_form = jQuery('.request_approval_reminder_dialog_form');
		  
		  jQuery.post('/insurance-reminder-msg/'+routing_id+'/'+item_id, { values:target_form.serialize() } ).done(function(data){ //console.log(data);
			if(data.approval_reminder_count>0){
			  jQuery('body').find('.request-approval-reminder-link-button-'+item_id).css('background','#419641');
			  jQuery('.request-approval-reminder-link-'+item_id+' .request-bid-intent-link-count').each(function(index, element) {
				 jQuery(this).addClass('notification-count').text(data.approval_reminder_count);
              });
			  if(data.comment_box.selector!=''){
				jQuery(data.comment_box.selector).html(data.comment_box.html);
				Drupal.attachBehaviors(jQuery('.routing_feedback_message_form'));  
			  }
			}
		  });
		  jQuery( this ).dialog('close');
		  
		}
	  },
	  open: function() {
		jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	  }
	});
	
	//jQuery('.request-approval-reminder-link').click(function(){
	Drupal.ajax.prototype.commands.insuranceOfNoticeDailog = function (ajax, response, status) {	
		//var item_id = jQuery(this).data('fc');
		//var routing_id = jQuery(this).data('routing');
		var item_id = response.fc_item_id;
		var routing_id = response.node_nid;
		var message = response.message;
		jQuery.post( "/get-insurance-reminder/"+routing_id+'/'+item_id, { js: 1, message:message})
		  .done(function( data ) {
			jQuery("#insurance-reminder-dialog").html(data.html);
			jQuery("#insurance-reminder-dialog").dialog('open');
		});  
		
		return false; 
	//});
	}
	  
  }
  
  if(Drupal.settings.hasOwnProperty('m6connect_ins_cert') && Drupal.settings.m6connect_ins_cert.hasOwnProperty('change_insurance_status_dialog') && Drupal.settings.m6connect_ins_cert.change_insurance_status_dialog == 1){	  
    jQuery("#change-insurance-status-dialog").dialog({ 
	  autoOpen: false,
	  width: 500,
	  modal: true,
	  resizable: false,
	  buttons: {
		Ok: function() {
		  var optionValue=jQuery(this).find('span.feedback_radio_option').data('optionvalue');
		  var optionClass=jQuery(this).find('span.feedback_radio_option').data('optionclass');
		  var optionElemnetName = jQuery(this).find('span.feedback_radio_option').data('optionelemnet');
		  var message = jQuery(this).find('textarea.approval-status-confirmation-message').val();
		  jQuery('.message_'+optionClass).val(message);
		  jQuery('input[name="'+optionElemnetName+'"]').data('selected',optionValue);
		  jQuery('input.'+optionClass).filter('[value="'+optionValue+'"]').attr('checked', 'checked').trigger('change');
		  jQuery( this ).dialog('close');
		  jQuery( this ).html('');
		},
		Cancel: function() {
		  var optionElemnetName = jQuery(this).find('span.feedback_radio_option').data('optionelemnet');
		  var optionSelected = jQuery(this).find('span.feedback_radio_option').data('optionselect');
		  if(optionSelected !==''){
		    jQuery('input[name="'+optionElemnetName+'"]').filter('[value="'+optionSelected+'"]').attr('checked', true);
		  }else{
			jQuery('input[name="'+optionElemnetName+'"]').attr('checked', false);  
		  }
		  jQuery( this ).dialog('close');
		  jQuery( this ).html('');
		}
	  },
	  open: function() {
		jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	  }
	});
	
	jQuery('input.approval_feedback_radio').change(function(e) {
	  var optionClass = jQuery(this).data('id');
	  if(jQuery('input.'+optionClass).length){
		  var optionValue=jQuery(this).val();
		  var optionSelected = jQuery(this).data('selected');
		  var optionElement  = jQuery(this).attr('name'); 
		  jQuery("#change-insurance-status-dialog").html('<div class="text-center"><strong>Send email to insurance certificate submitter indicating your selection?<span class="feedback_radio_option" data-optionvalue="'+optionValue+'" data-optionclass="'+optionClass+'" data-optionselect="'+optionSelected+'" data-optionelemnet="'+optionElement+'" style="display:none;"></span></strong></div><div class="form-item form-type-textarea form-item-message"><label for="edit-message">Message <span class="form-required" title="This field is required.">*</span></label><div class="form-textarea-wrapper resizable"><textarea class="request-approval-reminder-message-text approval-status-confirmation-message form-textarea required" name="message" cols="60" rows="3"></textarea></div></div>');
		  jQuery("#change-insurance-status-dialog").dialog('open');
	  }
    }); 
  }
  
  // insurance access dialog
  jQuery('.individual-insurance-create-link').click(function(){
	if( jQuery('#individual-insurance-create-dialog').length){
	  jQuery('#individual-insurance-create-dialog').dialog({
			autoOpen: true,
			width: 550,
			height: 'auto',
			modal: true,
			resizable: false,
			buttons: {
				'Ok': function () {
					jQuery(this).dialog("close");
					jQuery(this).html('');
				}
			},
			open: function () {
				jQuery('.ui-dialog-titlebar').hide();
			}
	  }).html('<div class="text-center"><strong>Thank you for your interest in the Insurance Certificate manager products.<br></strong></div><br/><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to request additional information or a demo of this product.</strong></span><br/><div class="pricing-info"><br/><span class="pricing-text"><strong>Pricing for this feature is as follows:</strong></span><ul><li>$49 per month for companies with 5 or fewer employees on M6Connect</li><li>$149 per month for companies with 6 to 50 employees on M6Connect</li> <li>Please contact support for companies with more than 50 employees on M6Connect</li></ul></div>');
	}
  });	
	
	if(jQuery('body').hasClass('page-node-add-insurance-certificates') || jQuery('body').hasClass('node-type-insurance-certificates')){
		jQuery('#edit-field-commercial-general-liabili-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
		  jQuery(this).val(format(jQuery(this).val()));
		});
		jQuery('#edit-field-automotive-liability-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
			jQuery(this).val(format(jQuery(this).val()));
		});		
		jQuery('#edit-field-professional-liability-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
			jQuery(this).val(format(jQuery(this).val()));
		});
		jQuery('#edit-field-builders-risk-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
			jQuery(this).val(format(jQuery(this).val()));
		});		
		jQuery('#edit-field-garage-liability-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
			jQuery(this).val(format(jQuery(this).val()));
		});	
		jQuery('#edit-field-excess-liability-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
			jQuery(this).val(format(jQuery(this).val()));
		});
		jQuery('#edit-field-workers-compensation-and-e-und-0-field-coverage-limits-und-0-value').keyup(function (i) {
			jQuery(this).val(format(jQuery(this).val()));
		});
		function format2(n, currency) {
			return currency + " " + n.toFixed().replace(/(\d)(?=(\d{3}))/g, "$1,");
		}
		var format = function (num) {
		var str = num.toString().replace("$", ""), parts = false, output = [], i = 1, formatted = null;
		if (str.indexOf(".") > 0) {
			parts = str.split(".");
			str = parts[0];
		}
		str = str.split("").reverse();
		for (var j = 0, len = str.length; j < len; j++) {
			if (str[j] != ",") {
				output.push(str[j]);
					if (i % 3 == 0 && j < (len - 1)) {
						output.push(",");
					}
					i++;
				}
			}
			formatted = output.reverse().join("");
			//return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));
			return("$" + formatted);
		};
	}
	
	if(jQuery('body').hasClass('page-insurance-certificates') || jQuery('body').hasClass('page-insurance-certificates-archive') || jQuery('body').hasClass('page-insurance-certificates-drafts')){
		jQuery('.movetodraft').click(function(){
			//var node_nid = jQuery(this).data('nid');
			//jQuery("#inscrt-node-"+node_nid).hide();
			jQuery(this).closest('tr').hide();
		});
		jQuery('.movetoarchive').click(function(){
			/*var node_nid = jQuery(this).data('nid');
			jQuery("#inscrt-node-"+node_nid).hide();*/
			jQuery(this).closest('tr').hide();
		});
	}
	
/*	if(jQuery('body').hasClass('page-insurance-certificates')){
	
	  jQuery.ias({
		  container : 'tbody', 
		  item: '.ins-invite-listing',
		  pagination: '.inscert-invite-nav',
		  next: '.inscert-invite-nav a',
		   loader: '<img src="/sites/all/themes/m6connect/images/ajax-loader.gif"/>',
		  triggerPageThreshold:0,
		  trigger: "See More", 		
		});	
	}*/
	
	
// Start work for infinity page       
  /*jQuery(".inscert-invite-data-load-more").bind("click", function(e) {
	e.preventDefault();
	var getProId = jQuery(this).attr('for');  
	var lastRowCommitNid = jQuery(".insurance-mail-invite-detail-table tr").last().attr('for');     
	var totalRecords = jQuery(this).val();
	console.log(lastRowCommitNid);
	console.log(totalRecords);
	  jQuery.post( '/load-more-btn-data/inscert-invite-mail/'+lastRowCommitNid, function( data ) { 
		if(data.tableDate!=''){
		  jQuery(".insurance-mail-invite-detail-table tbody").append(data.tableDate);
		}    
	  });
  });*/	   
});

/*Drupal.behaviors.m6connect_ins_cert = {	
  attach: function (context, settings) {
   jQuery(".inscert-invite-data-load-more").bind("click", function(e) {
	e.preventDefault();
	var getProId = jQuery(this).attr('for');  
	var lastRowCommitNid = jQuery(".insurance-mail-invite-detail-table tr").last().attr('for');     
	var totalRecords = jQuery(this).val();
	console.log(lastRowCommitNid);
	console.log(totalRecords);
	  jQuery.post( '/load-more-btn-data/inscert-invite-mail/'+lastRowCommitNid, function( data ) { 
		if(data.tableDate!=''){
		  jQuery(".insurance-mail-invite-detail-table tbody").append(data.tableDate);
		}    
	  });
  });	   
  }
};*/

Drupal.behaviors.m6connect_ins_cert = {
  attach: function () {
    jQuery('.node-insurance_certificates-form .form-field-name-field-submit-to input[type="text"]').blur(function() {
	  jQuery('.node-insurance_certificates-form .form-field-name-field-submit-to-user-list').css('display', 'none');
	  jQuery('.node-insurance_certificates-form .form-field-name-field-associate-to-project').css('display', 'none');
	});
	jQuery('.node-insurance_certificates-form .form-field-name-field-submit-to-user-list .form-select').change(function() {
	  //jQuery('.node-insurance_certificates-form .form-field-name-field-submit-to input[type="text"]').blur();
	});
	
	jQuery('.form-field-name-field-attach-certificates .description br').each(function(){
      jQuery(this).replaceWith(' ');
    });

	jQuery(".inscert-invite-data-load-more").bind("click", function(e) {
	  e.preventDefault();	  
	  var lastRowCommitNid = jQuery(".insurance-mail-invite-detail-table tr").last().attr('for');     
	  var nextCount = jQuery('.insurance-mail-invite-detail-table tbody tr').length + 10;
	  var totalrow = jQuery(this).data('totalrow');
		if(nextCount) {
		  jQuery.post( '/load-more-btn-data/inscert-invite-mail/'+lastRowCommitNid+'/'+nextCount, function( data ) { 
			if(data.tableDate!=''){
			  jQuery(".insurance-mail-invite-detail-table tbody").append(data.tableDate);
			  if(totalrow < nextCount){
				jQuery("a.inscert-invite-data-load-more").hide(); 			
			  }
			}    
		  });
		}
	});
  }
}
  

/*
///////////////////////// This code for removing node(id) from entity reference autocomplete field /////////////////////////
Drupal.behaviors.damnId = {
  attach: function (context, settings){
        // Get the entity reference input
        $eref = jQuery('#edit-field-submit-to-und-0-target-id', context);
        if($eref.val()){
          // If field has value on page load, change it.
          var val = $eref.val();
          var match = val.match(/\((.*?)\)$/);
          $eref.data('real-value', val);
          $eref.val(val.replace(match[0], ''));
        }
        // Listen for the autocompleteSelect event
        $eref.once().on('autocompleteSelect', function(e, node){
          var val = jQuery(node).data('autocompleteValue');
          var match = val.match(/\((.*?)\)$/);
          // Put the value with id into data storage
          $eref.data('real-value', val);
          // Set the value without the id
          $eref.val(val.replace(match[0], ''));
        }).closest('form').submit(function(e){
          // On form submit, set the value back to the stored value with id
          $eref.val($eref.data('real-value'));
        });
  }
};
*/

