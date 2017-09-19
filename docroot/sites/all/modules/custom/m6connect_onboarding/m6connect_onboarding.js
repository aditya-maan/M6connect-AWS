jQuery(document).ready(function($){
	
  /*jQuery('.carousel-m6id-top').hide();
      var credentialschck = jQuery("#carousel-m6id-company").hasClass("credentials-slide item active");
  if(credentialschck){
      jQuery('.carousel-m6id-top').show();
  }*/
     
  var base_url = window.location.origin;
  if(jQuery('body').hasClass('page-invite-companies-onboarding')){
	jQuery.ias({
	  container : '.onb-project-list-scroll', 
	  item: '.project-box-onb',
	  pagination: '.nav1',
	  next: '.nav1 a',
	  loader: '<img src="'+base_url+'/sites/all/themes/m6connect/images/ajax-loader.gif"/>',
	  triggerPageThreshold: 0,
	  trigger: "See More", 
	});
  }
  
  if(jQuery('.form-field-name-field-social-security-number input.form-text').length){
    jQuery('.form-field-name-field-social-security-number input.form-text').attr('maxlength',11);
	jQuery('.form-field-name-field-social-security-number input.form-text').blur(function (e) {
	  var text = jQuery(this).val();
	  text = text.replace(/[^0-9]/g,'');
	  //text = text.replace(/-/g, '');
	  text = text.substr(0, 9);
	  text = text.replace(/(\d{3})(\d{2})(\d{4})/, '$1-$2-$3');
	  jQuery(this).val(text);
	});
  }
  
  if(Drupal.settings.hasOwnProperty('m6connect_onboarding') && Drupal.settings.m6connect_onboarding.hasOwnProperty('onboarding_submiting_dialog') && Drupal.settings.m6connect_onboarding.onboarding_submiting_dialog == 1){
	if(jQuery('#onboarding_submiting_dialog').length){
	  jQuery('#onboarding_submiting_dialog').dialog({
		autoOpen: false,
		width: 550,
		modal: true,
		resizable: false,
		buttons: {
		  'Login': function () {
			var target_form = jQuery('.onboarding_confirm_submission_form');
			jQuery.post('/submit_onboarding-confirm-sumission', { values:target_form.serialize() } ).done(function(data){
			  if(data.login_status==1){
				jQuery('.onboarding-login-form-error').hide();
				jQuery('.node-onboarding-form .ob_submiting_node_submit').trigger('click');
				jQuery(this).dialog("close");
			    jQuery(this).html(''); 
			  }else{
				jQuery('.onboarding-login-form-error').show();
				return false;  
			  }
			});
		  },
		  'Cancel': function () {
			jQuery(this).dialog("close");
			jQuery(this).html('');
		  }
		},
		open: function () {
		  jQuery('.ui-dialog-titlebar').hide();
		  jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
		}
	  });
	  
	  /*jQuery('.node-onboarding-form .ob_submiting_node_submit').click(function(ev) {
		console.log(ev);
        if(isNaN(ev.isTrigger)){
		   jQuery.get('/get_onboarding-confirm-sumission-form').done(function(data){ 
		     jQuery('#onboarding_submiting_dialog').html(data.html);
		     jQuery('#onboarding_submiting_dialog').dialog('open');
		   });
		   ev.preventDefault();
		   return false;
		}
      });*/
	}
  }
  
  jQuery('.onboarding-question-help.company-confidential-help-link').click(function(e) {
    if(jQuery('#onboarding-question-own-companies-help').length){
	  jQuery('#onboarding-question-own-companies-help').dialog({
		autoOpen: true,
		width: 550,
		modal: true,
		resizable: false,
		buttons: {
		  'OK': function () {
			jQuery(this).dialog("close");
			jQuery(this).html('');
		  }
		},
		open: function () {
		  jQuery('.ui-dialog-titlebar').hide();
		}
	  }).html('<div><strong>By Checking this box you can hide your company name and their status on M6ID badge.</strong></div>');
	}
	e.preventDefault();
	return false;
  });
  
  jQuery('.onboarding-question-help.own-companies-help-link').click(function(e) {
    if(jQuery('#onboarding-question-own-companies-help').length){
	  jQuery('#onboarding-question-own-companies-help').dialog({
		autoOpen: true,
		width: 550,
		modal: true,
		resizable: false,
		buttons: {
		  'OK': function () {
			jQuery(this).dialog("close");
			jQuery(this).html('');
		  }
		},
		open: function () {
		  jQuery('.ui-dialog-titlebar').hide();
		}
	  }).html('<div><strong>M6ID allows you to electronically request access to a site, facility, project or information related to that particular company. You can check the status of your approval at any time by returning to the M6ID status page. Each company in M6Connect who purchases the M6ID product has an M6ID Manager assigned - this manager is responsible to maintain your information as confidential. In the event that you change companies or no longer wish to share this information then you just simply uncheck the company and they will not have access to your information any more.</strong></div>');
	}
	e.preventDefault();
	return false;
  });
  
  jQuery('.group-ob-submission-container').on('click','.onboarding-question-help.additional-companies-help-link',function(e) {
    if(jQuery('#onboarding-question-additional-companies-help').length){
	  jQuery('#onboarding-question-additional-companies-help').dialog({
		autoOpen: true,
		width: 550,
		modal: true,
		resizable: false,
		buttons: {
		  'OK': function () {
			jQuery(this).dialog("close");
			jQuery(this).html('');
		  }
		},
		open: function () {
		  jQuery('.ui-dialog-titlebar').hide();
		}
	  }).html('<div><strong>The companies you select will be provided access to your M6ID information. You may revoke this information at any time by deleting the company.</strong></div>');
	}
	e.preventDefault();
	return false;
  });
  
  jQuery('.form-field-name-field-onbarding-credentials').on('click','.onboarding-question-help.credentials-type-help-link',function(e) {
    if(jQuery('#onboarding-question-credential-type-help').length){
	  jQuery('#onboarding-question-credential-type-help').dialog({
		autoOpen: true,
		width: 550,
		modal: true,
		resizable: false,
		buttons: {
		  'OK': function () {
			jQuery(this).dialog("close");
			jQuery(this).html('');
		  }
		},
		open: function () {
		  jQuery('.ui-dialog-titlebar').hide();
		}
	  }).html('<div><strong>Providing your credentials allows you to share your licenses, certifications and awards with those you work for. This ensures that you always have access to this information at home or at work.  Simply provide your M6ID to employer(s), construction managers and owners when requested. Consider attaching the following; trade licenses such a medical gas certifications, OSHA Cards, High Lift, etc.</strong></div>');
	}
	e.preventDefault();
	return false;
  });
  
  //user profile view page credination
  if(jQuery('body').hasClass('page-user')){
	if(jQuery('#addcredentials').hasClass('active')){
	  jQuery('.middle-three-main-section').removeClass('col-md-3');
	  jQuery('.middle_three').css('display','none');
	  jQuery('.middle-two-main-section').removeClass('col-md-6');
	  jQuery('.middle-two-main-section').addClass('col-md-9');
	}else{
	  jQuery('.middle-three-main-section').addClass('col-md-3');
	  jQuery('.middle_three').css('display','block');
	}
	jQuery('.add-credentials-tab').click (function (e) {
	  jQuery('.middle-three-main-section').removeClass('col-md-3');
	  jQuery('.middle_three').css('display','none');
	  jQuery('.middle-two-main-section').removeClass('col-md-6');
	  jQuery('.middle-two-main-section').addClass('col-md-9');	
	});
	jQuery('.profile-tab-open').click (function (e) {
	  jQuery('.middle-three-main-section').addClass('col-md-3');
	  jQuery('.middle_three').css('display','block');
	  jQuery('.middle-two-main-section').removeClass('col-md-9');
	  jQuery('.middle-two-main-section').addClass('col-md-6');	
	});
  }
  
});

Drupal.behaviors.custom_selection_list_ob = {
  attach: function (context, settings) {
    
/////////////////////////////////////////////////////////////////////////////////////////////
  jQuery('.co_invite-manager-onb').change(function(){
    if(jQuery(this).find('option[value=""]').is(':selected')){
	   jQuery(this).find('option:selected').attr('selected', false);  
    }
	var projectboxAction = jQuery(this).find('.project-box-actions-onb');
	var projectBox = jQuery(this).closest('.project-box-onb');
	var cmpNid = projectBox.find('.company-nid-onb').text();   //company-nid
	if(jQuery('.invitees-list-onb').html()!=''){
	  var selectval = jQuery(this).val();
	  if(selectval=='' || selectval==null || selectval =='NULL' || selectval=='null'){
		selectval ='';  
	  }
	  jQuery('.invitees-list-onb').find('.selected-company-onb a#'+cmpNid).attr('mngid',selectval);
	  var nodeid = jQuery('.invite_Compnodeid_hidden').val();
	  var sess_selected_val = jQuery('.invitees-list-onb').html();
	  //sessionStorage.setItem("clbrte_selected_co_email_"+nodeid, sess_selected_val);
	  //sessionStorage.setItem("clbrte_invitelater_"+nodeid, sess_selected_val);
	}
  });
  
  jQuery('.added-to-rfp-onb').click(function(){
	var nodeType = jQuery('#cust-company-listings-onb .current-type').text();
	if(jQuery(this).hasClass('rfp-added-trigger-onb')){
	    var linkbox = jQuery(this).closest('.project-box-actions-onb');
	    var inviterfp = linkbox.find('.invite-to-rfp-onb');
	    var cmpNid = inviterfp.attr('id'); 
	    var nodeid1 = jQuery('.invite_Compnodeid_hidden').val();
	    var rlink = jQuery('.invitees-list-onb').find('.selected-company-onb a#'+cmpNid);
	    rlink.closest('.selected-company-onb').remove();
	    jQuery(this).css('display','none');
	    inviterfp.css('display','block');
	    var sess_selected_val1 = jQuery('.invitees-list-onb').html();
        //sessionStorage.setItem("clbrte_invitelater_"+nodeid1, sess_selected_val1);
	}
	return false;
  });
  
  jQuery('.invite-to-rfp-onb').click(function(event) {
    event.preventDefault();
	//////////////////////////////////////////////////////////
	if(check_invited_contant_person_onb()){
	  return false;
	}
	//////////////////////////////////////////////////////////
	var nid = jQuery(this).attr('id');
    //var selected_company = jQuery(this).parent('.col-sm-3').prev('.company-summary').children('h2').children('a').text();
	var project_box =  jQuery(this).closest('div.project-box-onb'); 
	var selected_company = project_box.find('.company-summary-onb h2 a.cust-proj-title-onb').text();
	var co_manager_id = project_box.find('.invite-proj-managerid-onb').text();
	var co_manager_name = project_box.find('.invite-proj-managername-onb').text();
	//var co_manager_id = jQuery(this).next().next().next('.invite-proj-managerid').text(); //alert(co_manager_id);
	var selected_company_html = "<div class='selected-company-onb' id='"+selected_company+"'><a href='' class='remove-invitees-onb remove-invitees' id='"+nid+"' mngid='"+co_manager_id+"'>X</a> <span class='invitees-name-onb invitees-name'>"+selected_company+" - "+co_manager_name+"</span></div>";
    var companies = jQuery('.invitees-list-onb').html();
    jQuery('.invitees-list-onb').html(companies + selected_company_html);	
    jQuery(this).css('display', 'none');
	jQuery(this).next('.added-to-rfp-onb').css('display', 'block').addClass('rfp-added-trigger-onb');
	
	var nodeid = jQuery('.invite_Compnodeid_hidden').val();
	var sess_selected_val = jQuery('.invitees-list-onb').html();
	//sessionStorage.setItem("clbrte_selected_co_email_"+nodeid, sess_selected_val);
	
	//sessionStorage.setItem("clbrte_invitelater_"+nodeid, sess_selected_val);
        //jQuery('#edit-submit--2').click();
  });
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
  jQuery('.co_invite-manager-onb').change(function(event) {
	var project_box = jQuery(this).closest('div.project-box-onb'); //alert('h');//alert(jQuery(this).val());alert(jQuery(this).text());
	project_box.find('.invite-proj-managerid-onb').text(jQuery(this).val());
	//jQuery(this).next('.invite-proj-managerid').text(jQuery(this).val());
	var names='';
	project_box.find('.co_invite-manager-onb option:selected').each(function() {
       names += (names=='')?jQuery(this).text():', '+jQuery(this).text(); 
    });
	project_box.find('.invite-proj-managername-onb').text(names);
  });
  
  jQuery('#onboarding-invite-companies-form .send-invitations-submit_onb').click(function(event) {
	/* var emails = jQuery('#edit-companies-by-email-clbrte').val();
	 if (!(emails == '' || emails == null)) { //alert('Sorry');
       jQuery('.add-individual-by-email_clbrte').click(); 
	 }*/
	 if(check_invited_contant_person_onb()){
	  return false;
	 }
	 if(jQuery('.invite_js_triggered_onb').val() =='0'){
	   jQuery('.ui-dialog-titlebar').hide();
	   jQuery('#invite-confirm-onb').dialog("open");
       return false;
	 }
	 jQuery.blockUI({ 
		baseZ: 2000, 
		message:  '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while we are sending your email invitations.</strong></div>', 
		css: {
		  border: 'none',  
		  fadeIn: 700, 
		  fadeOut: 700,
		  opacity: 0.87, 
		  color: '#000',
		  padding: '15px',
		  cursor:  'wait',
		  '-webkit-border-radius': '10px', 
		  '-moz-border-radius': '10px', 	
		}
	 });
  });
  
  if (Drupal.settings.hasOwnProperty('m6connect_onboarding') && Drupal.settings.m6connect_onboarding.hasOwnProperty('custom_dialog_js') && Drupal.settings.m6connect_onboarding.custom_dialog_js == 1) {
	jQuery('#invite-confirm-onb', '#onboarding-invite-companies-form').dialog({
	  autoOpen: false,
	  width: 400,
	  modal: true,
	  resizable: false,
	  buttons: {
		//"Ok": function() {
		"Yes, Send Invitations": function() {	
		  jQuery( this ).dialog( "close" );
		  var submitthis =jQuery('#onboarding-invite-companies-form .send-invitations-submit_onb');
		  var nodeid = jQuery('.invite_Compnodeid_hidden').val();
		  var is_invitelater = '';
		  var is_invitelater = sessionStorage.getItem("clbrte_invitelater_"+nodeid); 
		  var html = jQuery('.invitees-list-onb').html();
		  var hidden_html = new Array();
		  var hidden_mngr_html='';
		  var nodeType = jQuery('#cust-company-listings-onb .current-type').text();
		  if (html != '' || html != null) {
			jQuery('.selected-company-onb').each(function(index, element) {
			  var id = jQuery(this).children('.remove-invitees-onb').attr('id');
			  //if(nodeType == 'rfp'){ //by dev
			    var mngrid = jQuery(this).children('.remove-invitees-onb').attr('mngid');
			    if(id){
				  hidden_mngr_html += id+'_';
				  if(mngrid && typeof mngrid !== "undefined"){
				    hidden_mngr_html += mngrid;
				  }
				  hidden_mngr_html += ';';
			    }
			  //}
			  
			  if (isNaN(id)) {
				var id = jQuery(this).children('.invitees-name-onb').text(); 
			  }
			  hidden_html.push(id);
			});
			if(is_invitelater != '') {
			  sessionStorage.setItem("clbrte_invitelater_"+nodeid, ''); 
			}
		  }
		  else {
			alert("No Companies are selected for Inviting.");
			event.preventDefault();
		  }
		  jQuery('.companies_hidden_onb').val(hidden_html);
		  jQuery('.companies_manager_hidden_onb').val(hidden_mngr_html);
		  //alert(jQuery('.companies_hidden').val());
		  //alert(jQuery('.companies_manager_hidden').val());
		  sessionStorage.setItem("clbrte_selected_co_email_"+nodeid, '');
		  jQuery('.invite_js_triggered_onb').val('1');
		  jQuery('#onboarding-invite-companies-form .send-invitations-submit_onb').trigger('click');
		},
		Cancel: function() {
		  jQuery( this ).dialog( "close" );
		  return false;
		}
	  },
	  open: function() {
		jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	  }
	});
	
	
	
	
	 
	 jQuery('#co-persion-dialog-onb', '#onboarding-invite-companies-form').dialog({
	  autoOpen: false,
	  width: 400,
	  modal: true,
	  resizable: false,
	  buttons: {
		Ok: function() {
		  jQuery( this ).dialog( "close" );
		}
	  }
	 });
	 
	 jQuery('#company-already-invited-onb', '#onboarding-invite-companies-form').dialog({
	  autoOpen: false,
	  width: 400,
	  modal: true,
	  resizable: false,
	  buttons: {
		Ok: function() {
		  jQuery( this ).dialog( "close" );
		}
	  }
	 });
	 
	 jQuery('.ui-dialog-titlebar').hide();
	
 }
 
 jQuery('.invitees-list-onb').on('click','.remove-invitees-onb',function(event){ //alert('tryy');
	event.preventDefault();
    var remove_nid = jQuery(this).attr('id');
	//jQuery(".invitees-list-onb #"+remove_nid).parent('.selected-company-onb').remove();
	jQuery(".invitees-list-onb").find("a#"+remove_nid).closest('.selected-company-onb').remove();
	jQuery('.cust-company-listings-onb').find('#nid-'+remove_nid).find('.invite-to-rfp-onb').css('display', 'block');
	jQuery('.cust-company-listings-onb').find('#nid-'+remove_nid).find('.added-to-rfp-onb').css('display', 'none');
	  
	var nodeid1 = jQuery('.invite_Compnodeid_hidden').val();
	var sess_selected_val1 = jQuery('.invitees-list-onb').html();
	//sessionStorage.setItem("clbrte_selected_co_email_"+nodeid1, sess_selected_val1);  //sess_selected_val1
	  
	//sessionStorage.setItem("clbrte_invitelater_"+nodeid1, sess_selected_val1);
	return false;	
  });
  
 // user later
  //Remove already invited companys
  jQuery('.invited-co-list-onb').on('click','.remove-invite-company-onb',function(){
	var parDiv = jQuery(this).closest('div.invited-companies-done-onb');
	//var currEle = jQuery(this);
	var cmpNid = jQuery(this).attr('cnid');
	//var currNode = jQuery('.invited-co-list-onb').attr('rpnid');
	var itemId = jQuery(this).attr('itemid');
	jQuery.post( '/onb-remove-invited-company/'+itemId)
     .done(function( data ) {
      if(parDiv.hasClass('company-registered') && data.msg==1){
		jQuery('#cust-company-listings-onb').find('div#nid-'+cmpNid+' .invite-to-rfp-onb').css('display','block');
		jQuery('#cust-company-listings-onb').find('div#nid-'+cmpNid+' .added-to-rfp-onb').css('display','none').text(' Added');  
	  }
	  if(data.msg==1){
		//jQuery('#cont-col-'+itemId).remove();   
        //jQuery('#co_invite_manager_'+cmpNid).find('option[value='+itemId+']').html(jQuery('#co_invite_manager_'+cmpNid).find('option[value='+itemId+']').attr('data'));
		jQuery('#invited-companies-done-'+itemId).remove();
	  }
    });
  });
 
    // Make SSN required field on yes
	/*if($('.personal_information_citizen input[id="edit-field-are-you-a-us-citizen-und-yes"]').is(':checked')) {
	  var label = jQuery('.personal_information_security_number .form-item-field-social-security-number-und-0-value label').text(); 
	  var reqlabel = label + ' <span class="form-required" title="This field is required.">*</span>';
	  jQuery('.personal_information_security_number .form-item-field-social-security-number-und-0-value label').html(reqlabel);	
	}
    
    jQuery('.personal_information_citizen input[id="edit-field-are-you-a-us-citizen-und-yes"]').click(function(){
	  var label = jQuery('.personal_information_security_number .form-item-field-social-security-number-und-0-value label').text(); 
	  var reqlabel = label + ' <span class="form-required" title="This field is required.">*</span>';
	  jQuery('.personal_information_security_number .form-item-field-social-security-number-und-0-value label').html(reqlabel);
    });*/
	
	jQuery('.personal_information_citizen input[id="edit-field-are-you-a-us-citizen-und-no"]').click(function(){
	  if(jQuery('.personal_information_security_number .form-item-field-social-security-number-und-0-value label').find('span').length){ //alert('hi');
		jQuery('.personal_information_security_number .form-item-field-social-security-number-und-0-value label').find('span').remove();  
	  }
    });
	
	// attach field description
	jQuery('.personal_information_license_attach .form-field-name-field-attach-driving-licence .description').text('Upload front and back side of your Drivers license.');
      //jQuery(this).replaceWith(' ');
  //
  if(jQuery('body').hasClass('page-onboarding-projectlist')){    
	jQuery('.onboarding_submit_employeee_check thead tr').each(function(i,e){
      jQuery('th:first',e).html('Select');
	  jQuery('th:first',e).addClass('text-center');
    });
  }
  
  }
}

function check_invited_contant_person_onb(){
  var flag= 0;
  //if(Drupal.settings.m6connect_rfp.current_node_type=='rfp'){
	if(jQuery('.invitees-list-onb').html()!=''){
	  var cmpName='';
	  jQuery('.invitees-list-onb .remove-invitees-onb').each(function(index, element) {
		var removeID = jQuery(this).attr('id');
		if(jQuery(this).attr('mngid')==''){
		  cmpName= jQuery(this).closest('.selected-company-onb').find('.invitees-name-onb').text();
		  flag =1;
		  return false;
		}
	  });
	}
	if(flag==1){
	  jQuery('.ui-dialog-titlebar').hide();
	  jQuery('#co-persion-dialog-clbrte .co-persion-dialog-text').html('<strong>Select Company Contact for company <br>"'+cmpName+'" First</strong>');
	  jQuery('#co-persion-dialog-clbrte').dialog('open');  
	}
  //}
  return flag;	
}
function addVertical(){
		jQuery("#carousel-m6id-company").addClass("vertical");
}
function removeVertical(){
		jQuery("#carousel-m6id-company").removeClass("vertical");
}