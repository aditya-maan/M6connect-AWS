jQuery(document).ready(function(e){
  //Start Proposal Bid Confidential Work
  if(jQuery('#proposal-access-dialog').length){
	jQuery('#proposal-access-dialog').dialog({
	  autoOpen: false,
	  width: 350,
	  modal: true,
	  resizable: false,
	  buttons: {
		'Cancel': function () {
		  jQuery(this).dialog('close');
		  jQuery(this).html('');
		},
		'Get': function () {
		  var dialogElement = jQuery(this);
		  jQuery(this).find('.proposal-error-message').html('');
		  var prop_nid = jQuery(this).data('proposal');
		  var purpose = jQuery(this).data('purpose');
		  var access_key = jQuery(this).find('input.proposal-bid-key').val();
		  if(access_key=='' || access_key.length < 7 || access_key.length > 7){
			jQuery(this).find('.proposal-error-message').html('Invalid Key');
			return false;	
		  }
		  jQuery.post( "/access-proposal-amount/"+prop_nid,{access_key:access_key,access_purpose:purpose}).done(function(data) {
			if(data.invalid_access==1){
			  dialogElement.find('.proposal-error-message').html('Invalid Key');
			  return false;	
			}else{
			  if(purpose=='amount_access'){
				jQuery('li.prop_m6con1_'+prop_nid).find('span.bit_proposal_amt').html(data.prposal_amt);
				dialogElement.dialog('close');
				dialogElement.html('');
			  }else if(purpose=='node_access' && data.proposal_path!=''){
				window.location.href= data.proposal_path;	
				dialogElement.dialog('close');
				dialogElement.html('');
			  }else if(purpose=='action_access'){
				jQuery('li.prop_m6con1_'+prop_nid).find('.m6_actions button.proposal-action-button').replaceWith(data.proposal_action);
				Drupal.attachBehaviors(jQuery('#content_msg'));
				dialogElement.dialog('close');
				dialogElement.html('');	
			  }
			}
		  });	
		  return false;
		},
	  },
	  open: function () {
		jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
		jQuery('.ui-dialog-titlebar').hide();
	  }
	});
	
	 if (Drupal.settings.hasOwnProperty('m6connect_proposal') && Drupal.settings.m6connect_proposal.hasOwnProperty('need_authorization') && Drupal.settings.m6connect_proposal.need_authorization.hasOwnProperty('entity_id') && Drupal.settings.m6connect_proposal.need_authorization.entity_id) {
		var prop_nid = Drupal.settings.m6connect_proposal.need_authorization.entity_id;
		var prop_title = Drupal.settings.m6connect_proposal.need_authorization.entity_title;
	    jQuery('#proposal-access-dialog').data('proposal',prop_nid);
	    jQuery('#proposal-access-dialog').data('purpose','node_access');
	    jQuery('#proposal-access-dialog').html('<div class="text-left"><strong>Enter Bid Key to access Proposal: '+prop_title+'</strong><br/><span class="proposal-error-message" style="color:red;"></span><div><input data-proposal="'+prop_nid+'" type="text" name="proposal-bid-key" class="proposal-bid-key" placeholder="Enter Bid Key" style="width:100%;"/></div></div>');
	    jQuery('#proposal-access-dialog').dialog('open');
	}
	
	jQuery('#content_msg').on('click','span.bit_proposal_amt a.proposal-bid-amount',function(e) {
	  var prop_nid = jQuery(this).closest('span.bit_proposal_amt').data('entity');
	  jQuery('#proposal-access-dialog').data('proposal',prop_nid);
	  jQuery('#proposal-access-dialog').data('purpose','amount_access');
	  jQuery('#proposal-access-dialog').html('<div class="text-left"><strong>Enter Bid Key</strong><br/><span class="proposal-error-message" style="color:red;"></span><div><input data-proposal="'+prop_nid+'" type="text" name="proposal-bid-key" class="proposal-bid-key" placeholder="Enter Bid Key" style="width:100%;"/></div></div>');
	  jQuery('#proposal-access-dialog').dialog('open');
	  return false;
	});
	 
	jQuery('#content_msg').on('click','.m6_prop1_cont_title a.proposal-node-access, .m6_prop1_img a.proposal-node-access',function(e) {
	  var prop_nid = jQuery(this).closest('li.proposal-m6-container').data('entity');
	  jQuery('#proposal-access-dialog').data('proposal',prop_nid);
	  jQuery('#proposal-access-dialog').data('purpose','node_access');
	  jQuery('#proposal-access-dialog').html('<div class="text-left"><strong>Enter Bid Key</strong><br/><span class="proposal-error-message" style="color:red;"></span><div><input data-proposal="'+prop_nid+'" type="text" name="proposal-bid-key" class="proposal-bid-key" placeholder="Enter Bid Key" style="width:100%;"/></div></div>');
	  jQuery('#proposal-access-dialog').dialog('open');
	  return false;
	});
	
	jQuery('#content_msg').on('click','.m6_actions button.proposal-action-button',function(e) {
	  var prop_nid = jQuery(this).closest('li.proposal-m6-container').data('entity');
	  jQuery('#proposal-access-dialog').data('proposal',prop_nid);
	  jQuery('#proposal-access-dialog').data('purpose','action_access');
	  jQuery('#proposal-access-dialog').html('<div class="text-left"><strong>Enter Bid Key</strong><br/><span class="proposal-error-message" style="color:red;"></span><div><input data-proposal="'+prop_nid+'" type="text" name="proposal-bid-key" class="proposal-bid-key" placeholder="Enter Bid Key" style="width:100%;"/></div></div>');
	  jQuery('#proposal-access-dialog').dialog('open');
	  return false;
	});
  }
  
  jQuery('.cust-proposal-view-heading a.proposal-header-sorting').click(function(e) {
	'use strict';
	e.preventDefault();
	var sortName = jQuery(this).data('sort-name');
	var sortType = jQuery(this).data('sort-type');
	if(sortType=='desc'){ 
	  jQuery('.cust-proposal-view-heading').find('a.proposal-header-sorting .caret-section').removeClass('fa-caret-up fa-caret-down');
	  jQuery(this).find('.caret-section').addClass('fa-caret-down');  
	  jQuery(this).data('sort-type','asc');
	}else{
	  jQuery('.cust-proposal-view-heading').find('a.proposal-header-sorting .caret-section').removeClass('fa-caret-up fa-caret-down');
	  jQuery(this).find('.caret-section').addClass('fa-caret-up');      
	  jQuery(this).data('sort-type','desc');
	}
	jQuery('select#order_proposal').val(sortName+'_'+sortType).trigger('change');
	return false;
  });
   
  //End Proposal Bid Confidential Work	
	
  /*	
	$('#edit-field-organization-type-und').bind('change', function (e) { 
    if( $('#edit-field-organization-type-und').val() == 'governmental') {
     // $('#reason').show();
     // $("#reason").css({ display: "inline-block" });
      $('.form-field-name-field-incorporated-country').hide();
    }
    else if( $('#status').val() == 'Accepted') {
      $('#reason').hide();
      $('#decision').show();
    }         
  }).trigger('change');*/
	
  
  /*jQuery("input[name='pro_filter[interested]']").click(function() {	
    var input = jQuery(this);
	if((input).is(':checked')) {
	 
	  //var path = window.location.hostname+'projects?interested=1';
	  var path = '/projects?interested=interested';
	  window.location.href = path; 	
	} 
  });*/
  
  jQuery('input[name="co_name"]').keydown(function(e) {
    if (e.keyCode == 13) {
      jQuery('.co-submit').click();
    }
  });
  
  jQuery("input[name='co_diversitytype[_none]']").click(function() {	
    var input = jQuery(this);
	if((input).is(':checked')) {
	  
	  jQuery("#edit-co-diversitytype .form-checkbox").each(function(i){
		this.checked = true;
	  });
	} else {
	  jQuery("#edit-co-diversitytype .form-checkbox").each(function(i){
		this.checked = false;
	  });	
	}
  });
  
  //var ln = jQuery('.node-organization-form .field-name-field-location-name').find("label").text(); //alert(ln); alert('dsf');
  //jQuery('.node-organization-form .field-name-field-location-name').find("label").text();
  /*
  var arr = [ ".node-organization-form .field-name-field-location-name", ".node-organization-form .field-name-field-location-type", ".node-organization-form .field-name-field-location-phone-number", ".node-organization-form .field-name-field-location-m6-company-types", ".node-organization-form .field-name-field-location-industry-naics", ".node-organization-form .field-name-field-location-products-services", ".node-organization-form .field-name-field-location-psc-codes", ".node-organization-form .field-name-field-location-business-desc" ];
  jQuery.each( arr, function( i, val ) {
    var l = jQuery(val).find("label").text(); //alert(l);
    jQuery(val).find("label").append('<span class="cust-req" style="color:red">*</span>');
  });
  var addarr =["field-location-address-und-0-country","field-location-address-und-0-thoroughfare", "field-location-address-und-0-locality", "field-location-address-und-0-administrative-area", "field-location-address-und-0-postal-code"];
  jQuery.each( addarr, function( i, val ) {
    var l = jQuery('.node-organization-form .field-name-field-location-address [class$=' + val + ']').find("label").text(); //alert(l);
    jQuery('.node-organization-form .field-name-field-location-address [class$=' + val + ']').find("label").append('<span class="cust-req" style="color:red">*</span>');
  });
  */
  // Infinite Ajax Scroll configuration
/* if(jQuery('body').hasClass('page-companies')){

	jQuery.ias({
	  container : '#cust-company-listings', 
	  item: '.company-item',
	  pagination: '.nav',
	  next: '.nav a',
	  loader: '<img src="sites/all/themes/m6connect/images/ajax-loader.gif"/>',
	  triggerPageThreshold: 0,
	  trigger: "See More", 
	});
	
  }*/
  // diversiry needs comment box show/hide
/*  var ischecked = 0;
  jQuery(".node-organization-form .form-field-name-field-diversity-needs .form-checkbox").each(function(i){
    //jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'none'); 
	if(jQuery(this).is(':checked')) { 
	  ischecked = 1;
	}
  });
  if(ischecked){
	jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'block');   
  } else {
	jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'none');   
  }
  jQuery(".node-organization-form .form-field-name-field-diversity-needs .form-checkbox").click(function() {
	if(jQuery(this).is(':checked')) {  
	  jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'block'); 
	} else {
	  var checked = 0;
	  jQuery(".node-organization-form .form-field-name-field-diversity-needs .form-checkbox").each(function(i){
		if(jQuery(this).is(':checked')) { 
	      checked = 1;
	    }	
	  });
	  if(!checked) {
	    jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'none'); 
	  }
	}
  });*/
  
  ///// location tab 
  if(jQuery('body').hasClass('node-type-organization')){
	 
	jQuery('.company-location-outer').each(function(index, element) {
	  var FieldSetTitle = '';	  
	  var LocationType = jQuery('select[name="field_company_locations[und]['+index+'][field_location_type_list][und]"] option:selected').text();
	  var LocationRegion = jQuery('select[name="field_company_locations[und]['+index+'][field_regions_only][und]"] option:selected').text();
	  var LocationName = jQuery('input[name="field_company_locations[und]['+index+'][field_com_location_name][und][0][value]"]').val();
	  var LocationAddress = jQuery('input[name="field_company_locations[und]['+index+'][field_location_address][und][0][thoroughfare]"]').val();	  
	  if(LocationType && LocationRegion && LocationAddress){
		if(LocationName){  
		  FieldSetTitle = LocationType+' '+ LocationRegion+' - '+ LocationName;
		}
		else{
		  FieldSetTitle = LocationType+' '+ LocationRegion;
		}
		jQuery('.fieldset-title').get(index).lastChild.nodeValue = FieldSetTitle;	
	  }    
	});
	jQuery('.group-business-location-group').each(function(index, element) {
	  var FieldSetTitle = '';
	  var LocationType = jQuery('select[name="field_company_business_location[und]['+index+'][field_location_type_list][und]"] option:selected').text();
	  var LocationRegion = jQuery('select[name="field_company_business_location[und]['+index+'][field_regions_only][und]"] option:selected').text();
	  var LocationName = jQuery('input[name="field_company_business_location[und]['+index+'][field_com_location_name][und][0][value]"]').val();	 	  	  
	  if(LocationType && LocationRegion && LocationType != '- None -' && LocationRegion != '- None -'){
		if(LocationName){  
		  FieldSetTitle = LocationType+' '+ LocationRegion+' - '+ LocationName;
		}
		else{
		  FieldSetTitle = LocationType+' '+ LocationRegion;
		}	
		jQuery('.fieldset-title').get(index).lastChild.nodeValue = FieldSetTitle;	
	  }    
	});
  }
  
});
Drupal.behaviors.m6connect_company = {
    attach: function () {
	  //location
	  if(jQuery('body').hasClass('node-type-organization')){
		jQuery('.company-location-outer').each(function(index, element) {		  
		  var FieldSetTitle = '';
		  var LocationType = jQuery('select[name="field_company_locations[und]['+index+'][field_location_type_list][und]"] option:selected').text();
		  var LocationRegion = jQuery('select[name="field_company_locations[und]['+index+'][field_regions_only][und]"] option:selected').text();
		  var LocationAddress = jQuery('input[name="field_company_locations[und]['+index+'][field_location_address][und][0][thoroughfare]"]').val();	  
		  if(LocationType && LocationRegion && LocationAddress){
			FieldSetTitle = LocationType+' '+ LocationRegion;
			jQuery(this).find('legend span.fieldset-legend a.fieldset-title').html(FieldSetTitle);		
		  }    
		});
		jQuery('.group-business-location-group').each(function(index, element) {
		  var FieldSetTitle = '';
		  var LocationType = jQuery('select[name="field_company_business_location[und]['+index+'][field_location_type_list][und]"] option:selected').text();
		  var LocationRegion = jQuery('select[name="field_company_business_location[und]['+index+'][field_regions_only][und]"] option:selected').text();	  	  
		  if(LocationType && LocationRegion && LocationType != '- None -' && LocationRegion != '- None -'){
			FieldSetTitle = LocationType+' '+ LocationRegion;		
			jQuery(this).find('legend span.fieldset-legend a.fieldset-title').html(FieldSetTitle);	
		  }    
		});
	  }
	  
	}
}

Drupal.behaviors.custom_co_selection_list = {
  attach: function (context, settings) {
	  
    jQuery('.company-select-filter-list .cust-selection-list',context).click(function(){ //alert('tsd');
	  //base = jQuery('.project-select-filter-list .site_base_url').val();
	  //stype = 'projects';
	  //qstr = jQuery(this).children('.cust-selection-hidden-val').children('.filter-qstr').text(); 
	  sfname = jQuery(this).children('.cust-selection-hidden-val').children('.sfilter-name').text();
	  sfval = jQuery(this).children('.cust-selection-hidden-val').children('.sfilter-val').text();
	  if(sfname == 'co_name'){
		jQuery('#cust-company-search-form  #edit-co-name').val('');
		jQuery('#cust-company-search-form  #edit-co-submit').click();
	  }
	  if(sfname == 'co_facilities'){
		jQuery('#cust-company-search-form  #edit-co-facilities-hierarchical-select-selects-0').val('none');
		jQuery('#cust-company-search-form  #edit-co-submit').click();  
	  }
	  
	  if(sfname == 'co_region'){
		jQuery('#cust-company-search-form  #edit-co-region-hierarchical-select-selects-0').val('none');
		jQuery('#cust-company-search-form  #edit-co-submit').click();  
	  }
	  
	  if(sfname == 'co_industries'){
		jQuery('#cust-company-search-form  #edit-co-industries-hierarchical-select-selects-0').val('none');
		jQuery('#cust-company-search-form  #edit-co-submit').click();  
	  }
	  
	  if(sfname == 'co_pservices'){
		jQuery('#cust-company-search-form  #edit-co-pservices-hierarchical-select-selects-0').val('none');
		jQuery('#cust-company-search-form  #edit-co-submit').click();  
	  }
	  
	  if(sfname == 'co_diversity'){
		jQuery('#cust-company-search-form  #edit-co-diversitytype-'+sfval).attr('checked', false);
		jQuery('#cust-company-search-form  #edit-co-submit').click();  
	  }
	});
  }
}

Drupal.behaviors.custom_location_requred = {
  attach: function (context, settings) {
	//////////////////////////////////////////////
    //jQuery(context).once(localBehavior, function () {	
	  var arr = [ ".node-organization-form .field-name-field-location-name", ".node-organization-form .field-name-field-location-type", ".node-organization-form .field-name-field-location-phone-number", ".node-organization-form .field-name-field-location-m6-company-types", ".node-organization-form .field-name-field-location-industry-naics", ".node-organization-form .field-name-field-location-products-services", ".node-organization-form .field-name-field-location-psc-codes", ".node-organization-form .field-name-field-location-business-desc", ".node-organization-form .field-name-field-location-parent-locations" ];
      jQuery.each( arr, function( i, val ) {
        var l = jQuery(val).find("label").text(); //alert(l);
		if(jQuery(val).find("label").find("span").length ==0 ){
          //jQuery(val).find("label").append('<span class="cust-req" style="color:red">*</span>');
		}
      });
      var addarr =["field-location-address-und-0-country","field-location-address-und-0-thoroughfare", "field-location-address-und-0-locality", "field-location-address-und-0-administrative-area", "field-location-address-und-0-postal-code"];
      jQuery.each( addarr, function( i, val ) {
        var l = jQuery('.node-organization-form .field-name-field-location-address [class$=' + val + ']').find("label").text(); //alert(l);
		if(jQuery('.node-organization-form .field-name-field-location-address [class$=' + val + ']').find("label").find("span").length ==0 ){
          //jQuery('.node-organization-form .field-name-field-location-address [class$=' + val + ']').find("label").append('<span class="cust-req" style="color:red">*</span>');
		}
      });
   // });
   /************* Replacet comment work from icon on company profile page ***************/
   //var ct = jQuery('.newsfeed .fbss-comments-show-comment-form a.fbss-comments-show-comment-form-link').text();alert(ct);
   jQuery('.newsfeed .fbss-comments-show-comment-form a.fbss-comments-show-comment-form-link').text('');
   jQuery('.newsfeed .fbss-comments-show-comment-form a.fbss-comments-show-comment-form-link').html('<i class="fa fa-comment">');

   jQuery('.newsfeed .statuses-links .statuses-edit a').text('');
   jQuery('.newsfeed .statuses-links .statuses-delete a').text('');
   jQuery('.newsfeed .statuses-links a.statuses-repost').text('');
   jQuery('.newsfeed .statuses-links .statuses-edit a').html('<i class="fa fa-edit">');
   jQuery('.newsfeed .statuses-links .statuses-delete a').html('<i class="fa fa-trash">');
   jQuery('.newsfeed .statuses-links a.statuses-repost').html('<i class="fa fa-share">');

   jQuery('.newsfeed .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-edit-link a').text('');
   jQuery('.newsfeed .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-delete-link a').text('');
   jQuery('.newsfeed .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-edit-link a').html('<i class="fa fa-edit">');
   jQuery('.newsfeed .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-delete-link a').html('<i class="fa fa-trash">');
   
   
   //show/hide Diversity Needs comment
  /* jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'none'); 
  // jQuery('.node-organization-form .form-field-name-field-diversity-needs').
    jQuery(".node-organization-form .form-field-name-field-diversity-needs").each(function(i){
		//this.checked = true;
	});*/
  }
}