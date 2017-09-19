jQuery(document).ready(function() {
	
	jQuery('.group-routing-tabs ul.horizontal-tabs-list li.horizontal-tab-button a').click(function(){
	   var sessionName = jQuery('h1.routing-slip-title').data('sess');
	   if(jQuery(this).closest('li').hasClass('horizontal-tab-button-0')){
		  sessionStorage.setItem(sessionName+'_tab', 'group-add-documents'); 
	   }else if(jQuery(this).closest('li').hasClass('horizontal-tab-button-1')){
		  sessionStorage.setItem(sessionName+'_tab', 'group-approval-feedback');  
	   }
	});
	if(jQuery('body.node-type-routing-slip').find('h1.routing-slip-title').length){
	  var sessionName = jQuery('h1.routing-slip-title').data('sess');
	  var tabClass = sessionStorage.getItem(sessionName+'_tab');
	  if(tabClass!==null){
		jQuery("."+tabClass).data("horizontalTab").focus();  
	  }
	}

	jQuery('.individual-routing-create-link').click(function(){
	if( jQuery('#individual-routing-create-dialog').length){
	  jQuery('#individual-routing-create-dialog').dialog({
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
	  }).html('<div class="text-center"><strong>Thank you for your interest in Routing Slip.<br></strong></div><br/><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to send routing slips.</strong></span><br/><div class="pricing-info"><br/><span class="pricing-text"><strong>Pricing for this feature is as follows:</strong></span><ul><li>$25 per month for individuals</li><li>$250 per month for companies with 5 or fewer employees on M6Connect</li><li>$2,500 per month for companies with 6 to 50 employees on M6Connect</li> <li>Please contact support for companies with more than 50 employees on M6Connect</li></ul></div>');
	}
  });
  
  jQuery('div.view-routing-slip-center').on('click','.routing-slip-approved',function(ev){
	var mainElement = jQuery(this);
	if(!jQuery(this).hasClass('approve-processed')){
	  if( jQuery('#approve-link-dialog').length){
		jQuery('#approve-link-dialog').dialog({
		  autoOpen: true,
		  width: 550,
		  modal: true,
		  resizable: false,
		  buttons: {
			'Ok': function () {
			  window.location = mainElement.attr('href');
			  jQuery(this).dialog("close");
			  jQuery(this).html('');
			},
			'Cancel': function () {
			  jQuery(this).dialog("close");
			  jQuery(this).html('');
			}
		  },
		  open: function () {
		    jQuery('.ui-dialog-titlebar').hide();
			jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
			mainElement.addClass('approve-processed');
		  },close: function(){
			mainElement.removeClass('approve-processed'); 
		  }
	    }).html('<div class="text-center"><strong>By approving this Routing Slip prior to all approvers and notified users having completed their work, then the Routing Slip will no longer allow them to make comments or change their approval status.  You may proceed with this approval without their approval - select ok to continue</strong></div>');
		ev.preventDefault();
		return false;
	  }
	}
  });
  
  jQuery('.invited-co-list').on('click','.remove-routing-invited-company',function(){
	var parDiv = jQuery(this).closest('div.invited-companies-done');
	//var currEle = jQuery(this);
	var cmpNid = jQuery(this).attr('cnid');
	var currNode = jQuery('.invited-co-list').attr('rpnid');
	var itemId = jQuery(this).attr('itemid');
	jQuery.post( '/remove-routing-invited-company/'+currNode+'/'+itemId)
     .done(function( data ) {
      if(parDiv.hasClass('company-registered') && data.msg==1){
		jQuery('#cust-company-listings').find('div#nid-'+cmpNid+' .invite-to-rfp').css('display','block');
		jQuery('#cust-company-listings').find('div#nid-'+cmpNid+' .added-to-rfp').css('display','none').text(' Added');  
	  }
	  if(data.msg==1){
		parDiv.remove();  
	  }
    });
  });
  
  
  if(Drupal.settings.hasOwnProperty('m6connect_routing') && Drupal.settings.m6connect_routing.hasOwnProperty('invite_approvers_active') && Drupal.settings.m6connect_routing.invite_approvers_active == 1){
	jQuery(".group-invite-approvers").data("horizontalTab").focus();  
  }
  
  if(Drupal.settings.hasOwnProperty('m6connect_routing') && Drupal.settings.m6connect_routing.hasOwnProperty('request_approval_reminder_dialog') && Drupal.settings.m6connect_routing.request_approval_reminder_dialog == 1){
	jQuery("#request-approval-reminder-dialog").dialog({ 
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
		  
		  jQuery.post('/request-approval-reminder/'+routing_id+'/'+item_id, { values:target_form.serialize() } ).done(function(data){
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
		  jQuery( this ).dialog('close');
		  jQuery( this ).html('');
		}
	  },
	  open: function() {
		jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	  }
	});
	
	  jQuery('.request-approval-reminder-link').click(function(){
		var item_id = jQuery(this).data('fc');
		var routing_id = jQuery(this).data('routing');
		jQuery.post( "/get-request-approval-reminder/"+routing_id+'/'+item_id, { js: 1})
		  .done(function( data ) {
			jQuery("#request-approval-reminder-dialog").html(data.html);
			jQuery("#request-approval-reminder-dialog").dialog('open');
		});  
		
		return false; 
	}); 
	  
  }
  
  if(Drupal.settings.hasOwnProperty('m6connect_routing') && Drupal.settings.m6connect_routing.hasOwnProperty('change_approver_status_dialog') && Drupal.settings.m6connect_routing.change_approver_status_dialog == 1){
	  jQuery('input.approval_feedback_radio').change(function() {	  
		  var optionValue = jQuery(this).val();
			if(optionValue == 1){
				jQuery("#change-approver-status-dialog").dialog({ 		
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
						console.log(optionClass);
						jQuery('.message_'+optionClass).val(message);
						jQuery('.trigger_'+optionClass).val('');
						jQuery('.trigger_'+optionClass).val('send_email');
						jQuery('input[name="'+optionElemnetName+'"]').data('selected',optionValue);
						jQuery('input.'+optionClass).filter('[value="'+optionValue+'"]').attr('checked', 'checked').trigger('change');
						jQuery( this ).dialog('close');
						jQuery( this ).html('');
					},
					Cancel: function() {
						/*var optionElemnetName = jQuery(this).find('span.feedback_radio_option').data('optionelemnet');
						var optionSelected = jQuery(this).find('span.feedback_radio_option').data('optionselect');
						if(optionSelected !==''){
							jQuery('input[name="'+optionElemnetName+'"]').filter('[value="'+optionSelected+'"]').attr('checked', true);
						}else{
						jQuery('input[name="'+optionElemnetName+'"]').attr('checked', false);  
						}
						jQuery( this ).dialog('close');
						jQuery( this ).html('');*/
						
						var optionValue=jQuery(this).find('span.feedback_radio_option').data('optionvalue');
						var optionClass=jQuery(this).find('span.feedback_radio_option').data('optionclass');
						var optionElemnetName = jQuery(this).find('span.feedback_radio_option').data('optionelemnet');
						var message = jQuery(this).find('textarea.approval-status-confirmation-message').val();
						console.log(optionClass);
						jQuery('.message_'+optionClass).val(message);
						jQuery('.trigger_'+optionClass).val('');
						jQuery('.trigger_'+optionClass).val('not_send_email');
						jQuery('input[name="'+optionElemnetName+'"]').data('selected',optionValue);
						jQuery('input.'+optionClass).filter('[value="'+optionValue+'"]').attr('checked', 'checked').trigger('change');
						jQuery( this ).dialog('close');
						jQuery( this ).html('');
					}
					},
					open: function() {
						jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
						jQuery('div.ui-dialog-titlebar').hide();
					}
				});
			}else{
				jQuery("#change-approver-status-dialog").dialog({ 
		
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
						if(message==''){
		    if(!(jQuery('.request-approval-reminder-message-text').find('.message-required-text').length)){					
					$("#approval-status-confirmation").addClass("error");
				}
				return false;
			}
						console.log(optionClass);
						jQuery('.message_'+optionClass).val(message);
						jQuery('.trigger_'+optionClass).val('');
						jQuery('.trigger_'+optionClass).val('send_email');
						jQuery('input[name="'+optionElemnetName+'"]').data('selected',optionValue);
						jQuery('input.'+optionClass).filter('[value="'+optionValue+'"]').attr('checked', 'checked').trigger('change');
						jQuery( this ).dialog('close');
						jQuery( this ).html('');
					},
					
					},
					open: function() {
					  jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
					  jQuery('div.ui-dialog-titlebar').hide();
					}
				});
			}			
		});
    
	
	jQuery('input.approval_feedback_radio').change(function() {
	  var optionClass = jQuery(this).data('id');
	  if(jQuery('input.'+optionClass).length){
		  var optionValue=jQuery(this).val();
		  var optionSelected = jQuery(this).data('selected');
		  var optionElement  = jQuery(this).attr('name'); 
		  /*jQuery("#change-approver-status-dialog").html('<div class="text-center"><strong>Send email to routing slip issuer indicating your selection?<span class="feedback_radio_option" data-optionvalue="'+optionValue+'" data-optionclass="'+optionClass+'" data-optionselect="'+optionSelected+'" data-optionelemnet="'+optionElement+'" style="display:none;"></span></strong></div><div class="form-item form-type-textarea form-item-message"><label for="edit-message">Message <span class="form-required" title="This field is required.">*</span></label><div class="form-textarea-wrapper resizable"><textarea class="request-approval-reminder-message-text approval-status-confirmation-message form-textarea required" name="message" cols="60" rows="3"></textarea></div></div>');*/
			if(optionValue == 1){
				jQuery("#change-approver-status-dialog").html('<div class="text-center"><strong>Send email to routing slip issuer indicating your selection? Press Cancel if you do not want to send a email.<span class="feedback_radio_option" data-optionvalue="'+optionValue+'" data-optionclass="'+optionClass+'" data-optionselect="'+optionSelected+'" data-optionelemnet="'+optionElement+'" style="display:none;"></span></strong></div><div class="form-item form-type-textarea form-item-message"><label for="edit-message">Message</label><div class="form-textarea-wrapper resizable"><textarea class="request-approval-reminder-message-text approval-status-confirmation-message form-textarea required" name="message" cols="60" rows="3" placeholder="You may enter a special message to the issuer if you would like to"></textarea></div></div>');
				jQuery("#change-approver-status-dialog").dialog('open');
			} else{
				jQuery("#change-approver-status-dialog").html('<div class="text-center"><strong>Send email to routing slip issuer indicating your selection?<span class="feedback_radio_option" data-optionvalue="'+optionValue+'" data-optionclass="'+optionClass+'" data-optionselect="'+optionSelected+'" data-optionelemnet="'+optionElement+'" style="display:none;"></span></strong></div><div class="form-item form-type-textarea form-item-message"><label for="edit-message">Message</label><span class="form-required" title="This field is required.">*</span><div class="form-textarea-wrapper resizable"><textarea id="approval-status-confirmation" class="request-approval-reminder-message-text approval-status-confirmation-message form-textarea required" name="message" cols="60" rows="3" placeholder="You are required to provide a reason for selecting Rejected or Not Sure Yet" required="required"></textarea></div></div>');
				jQuery("#change-approver-status-dialog").dialog('open');
				
			}			
	  }
    }); 
  }
  
  if(jQuery('body').hasClass('page-node-add-routing-slip')){
		jQuery('#edit-field-approval-neededby-und-0-value-datepicker-popup-0').datepicker({ minDate: 0 });		
	}
	
	/*$.datepicker._gotoToday = function (id) {
var inst = this._getInst($(id)[0]),
  $dp = inst.dpDiv;
this._base_gotoToday(id);
var tp_inst = this._get(inst, 'timepicker');
var now = new time();
var now_utc = new Date(now.getUTCFullYear(), now.getUTCMonth(), now.getUTCDate(), now.getUTCHours(), now.getUTCMinutes(), now.getUTCSeconds());
this._setTime(inst, now_utc);
$('.ui-datepicker-today', $dp).click();
  };*/
});

