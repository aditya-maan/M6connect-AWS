//var Drupal = Drupal || { 'settings': {}, 'behaviors': {}, 'locale': {} };
//jQuery(document).ready(function(ev) {
  var resultCountInOneRequest =30;
  var bidderfeedbackFullyloaded = 0;
  var bidderfeedbackStartFrom= 1;
  var bidderajaxstart =0;
  var bidderfeedbackEndTo = bidderfeedbackStartFrom+resultCountInOneRequest; 
//jQuery(window).bind("load", function() {
//  "use strict";s
Drupal.behaviors.m6connect_rfp_bidder_fb = {
    attach: function () {
		
	  /*if(Drupal.settings.hasOwnProperty('m6connect_rfp') && (Drupal.settings.m6connect_rfp.hasOwnProperty('rfp_node_active_tab') && Drupal.settings.m6connect_rfp.rfp_node_active_tab==7) || (Drupal.settings.m6connect_rfp.hasOwnProperty('edit_rfp_feedback') &&  Drupal.settings.m6connect_rfp.edit_rfp_feedback==1)){
		 bidderajaxstart =1;
		 fisrt_call_rfp_bidder_feedback(); 
	  }*/
	  if(Drupal.settings.hasOwnProperty('m6connect_rfp') && (Drupal.settings.m6connect_rfp.hasOwnProperty('bidder_feedback_admin') && Drupal.settings.m6connect_rfp.bidder_feedback_admin==1)){
		var rfpBiddertabIndex = jQuery('.horizontal-tabs-panes fieldset').index(jQuery('fieldset.group-bidder-feedback'));
		if((Drupal.settings.m6connect_rfp.hasOwnProperty('rfp_node_active_tab') && Drupal.settings.m6connect_rfp.rfp_node_active_tab==rfpBiddertabIndex) || (Drupal.settings.m6connect_rfp.hasOwnProperty('edit_rfp_feedback') &&  Drupal.settings.m6connect_rfp.edit_rfp_feedback==1)){
		   bidderajaxstart =1;
		   fisrt_call_rfp_bidder_feedback();	
		}
		
		jQuery('.horizontal-tabs-list .horizontal-tab-button-'+rfpBiddertabIndex+' a').one('click',function(e) {
		  if(bidderajaxstart ==0){
            fisrt_call_rfp_bidder_feedback(); 
		  }
        });
		  
	  }
	  
	  /*jQuery('.horizontal-tabs-list .horizontal-tab-button-7 a').one('click',function(e) {
		if(bidderajaxstart ==0){
          fisrt_call_rfp_bidder_feedback(); 
		}
      });*/
}};

(function($){
  /**
   * Add an extra function to the Drupal ajax object
   * which allows us to trigger an ajax response without
   * an element that triggers it.
   */
  Drupal.ajax.prototype.specifiedResponse = function() {
    var ajax = this;
    if (ajax.ajaxing) {  // Do not perform another ajax command if one is already in progress.
      return false;
    }
    try {
      $.ajax(ajax.options);
    }
    catch (err) {
      //alert('An error occurred while attempting to process ' + ajax.options.url);
      return false;
    }
    return false;
  };
  
  Drupal.ajax.prototype.commands.bidderFeedbackTableUpdate = function (ajax, response, status) {
	var htmldata = response.tableData;
	var rowCount = response.rowCount;
	var entity_id = response.entity_id;
	if(!jQuery.isEmptyObject(htmldata)){
	  $.each(htmldata, function(selector, tabledata) {
		if($('#'+selector+' tbody tr td').hasClass('empty')){
		  $('#'+selector+' tbody tr').remove();	
		}
		$('#'+selector).append(tabledata);
		Drupal.attachBehaviors($('body'));
	  });
	  bidderfeedbackStartFrom = bidderfeedbackEndTo;
	  bidderfeedbackEndTo = bidderfeedbackStartFrom+resultCountInOneRequest;
	  rfp_bidder_feedback_ajax_callback(entity_id,bidderfeedbackStartFrom,resultCountInOneRequest);
	}else{
	  $('#cust-bidder-fb-lists').unblock();
	  
	  
	  var poprowCount = $('.cust-bidder-fb-content table tr').length;
	  
	  $('.cust-bidder-fb-content table').each(function(index, element) {
		  
        if($(this).find('tr').not(':first').length > 0 && !$(this).find('tr td').hasClass('empty')){
			
		 // $(this).find("tr th").eq(1).append('<div class="popover_m6notes"><span data-toggle="popover" data-trigger="manual" data-placement="top" data-content="These notes are private and cannot be seen by invited bidders. They can be seen by Company Administrators and those you have collaborated with."></span></div>');
		  
		  //$(this).find("tr th").eq(2).append('<span data-toggle="popover" data-trigger="manual" data-placement="top" data-content="Bid confidence is self assigned and invitees comment see you selections"></span>');
		  $(this).find("tr td .request-bid-intent-link").eq(0).append('<span data-toggle="popover" data-trigger="manual" data-placement="right" data-content="Selecting this button generates a popup box to write a special email/message to the Invitee(s)."></span>');
		  
		  $(this).find("tr td .request-by-sms-link").eq(0).append('<div class="text-center"data-toggle="popover" data-trigger="manual" data-placement="bottom" data-content="Selecting this button generates a popup box to write a special text message to the Invitee(s)."></div>');
		  
		  //$(this).find("tr .views-field-php").eq(0).append('<span data-toggle="popover" data-trigger="manual" data-placement="top" data-content="If, Comapny name exits then the company has logged in to M6."></span>');	
		  
		  return false;
		}
		
      });
	  
	  
	   
	  jq1113('[data-toggle="popover"]').popover({
	    html: 'true',
	    template: '<div class="popover" role="tooltip"><div class="arrow"></div><div class="close-popover text-right"><i class="fa fa-times popover-close" aria-hidden="true"></i></div><h3 class="popover-title"></h3><div class="popover-content"></div></div>'
	});
	  //$.unblockUI();
	}
  };


})(jQuery);

function rfp_bidder_feedback_ajax_callback(entity_id,bidderfeedbackStartFrom,resultCountInOneRequest){
  var custom_settings = {};
  custom_settings.url = '/load-bidder-feedback2/'+entity_id+'/'+bidderfeedbackStartFrom+'/'+resultCountInOneRequest;
  custom_settings.event = 'onload';
  custom_settings.keypress = false;
  custom_settings.prevent = false;
  Drupal.ajax['custom_ajax_action'] = new Drupal.ajax(null, jQuery(document.body), custom_settings);
  Drupal.ajax['custom_ajax_action'].specifiedResponse();  	
}

function fisrt_call_rfp_bidder_feedback(){
  jQuery('#cust-bidder-fb-lists').once('cust-bidder-fb-lists', function() {
	  jQuery('#cust-bidder-fb-lists').block({
		//jQuery.blockUI({
			baseZ: 2000,
			message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait</strong></div>',
			css: {
				border: 'none',
				fadeIn: 700,
				fadeOut: 700,
				opacity: 0.87,
				color: '#000',
				padding: '15px',
				width: '20%',
				cursor: 'wait',
				'-webkit-border-radius': '10px',
				'-moz-border-radius': '10px',
			}
		});
	  var entity_id = Drupal.settings.m6connect_rfp.entity_id;
	  rfp_bidder_feedback_ajax_callback(entity_id,bidderfeedbackStartFrom,resultCountInOneRequest);
  });	
}
