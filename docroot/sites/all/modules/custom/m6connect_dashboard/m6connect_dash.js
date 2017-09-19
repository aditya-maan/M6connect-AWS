if(typeof jq1113 !='undefined'){
  jq1113(document).ready(function(e) {    	     
	jq1113("#menu-toggle").click(function(e) {
	  e.preventDefault();
	  jq1113("#wrapper").toggleClass("active");
	});
	
	jq1113("#menu-toggle-inner").click(function(e) {
	  e.preventDefault();
	  jq1113("#wrapper").toggleClass("active");
	});
	
	jq1113('[data-toggle="tooltip"]').tooltip();
	
	jq1113('[data-toggle="popover"]').popover({
	  html: 'true',
	  //template: '<div class="popover" role="tooltip"><div class="arrow"></div><div class="close-popover text-right"><i class="fa fa-times popover-close" aria-hidden="true"></i></div><h3 class="popover-title"></h3><div class="popover-content"></div></div>'
	  template: '<div class="popover popover-gray-cust" role="tooltip"><div class="arrow"></div><h3 class="popover-title"></h3><div class="popover-content"></div></div>'
	});  			
	jq1113("a.open-popup-help-link").click(function(e) {
	  jq1113(this).toggleClass('popover-active');
	  if(jQuery(this).hasClass('popover-active')){
		jq1113('[data-toggle="popover"]').popover('show');
		jq1113('.custom-toggle-popover').popover('show'); 
		jq1113(this).prop('title', 'Close page help');
	  }else{
		jq1113('[data-toggle="popover"]').popover('hide'); 
		jq1113('.custom-toggle-popover').popover('hide');
		jq1113(this).prop('title', 'Open page help');
	  }
	  //jq1113('[data-toggle="popover"]').popover('toggle');
    });
	
	
	jq1113(document).on("click", ".popover .popover-close" , function(e){
		e.preventDefault();
        jq1113(this).parents(".popover").popover('hide');
    });
	
	jq1113('[data-toggle="popover"]').on('hidden.bs.popover', function () {
      if(!(jQuery('div.popover[role="tooltip"]').length)){
		if(jQuery('a.open-popup-help-link').hasClass('popover-active')){
		  jq1113('a.open-popup-help-link').toggleClass('popover-active');  
	    }  
	  }
    });
	
	if(typeof CKEDITOR !='undefined'){
	  CKEDITOR.on('instanceReady', function(evt){ 
		jq1113('.text-format-wrapper span.cke_skin_kama').each(function(index, element) {
		  "use strict";
		  var mainElem = jq1113(this).closest('.text-format-wrapper').find('textarea');
		  if(mainElem.data('ckeditor')=='popover'){
			jq1113(this).addClass('custom-toggle-popover');
			jq1113(this).popover({
			  //template	: '<div class="popover" role="tooltip"><div class="arrow"></div><div class="close-popover text-right"><i class="fa fa-times popover-close" aria-hidden="true"></i></div><h3 class="popover-title"></h3><div class="popover-content"></div></div>',
			  template	: '<div class="popover" role="tooltip"><div class="arrow"></div><h3 class="popover-title"></h3><div class="popover-content"></div></div>',
			  trigger	:mainElem.data('trigger'),
			  placement	:mainElem.data('placement'),
			  content	:mainElem.data('content'), 	
			}); 
		  }
		});
	  });
	}
  
  
	//rfp input focus
	jQuery('input.stanford-datepicker.form-text,input.stanford-timepicker.form-text').on('focus', function(){
	  jq1113(this).closest('.form-type-date-popup').find('[data-toggle="popover"]').popover('show');
	});
	jQuery('input.stanford-datepicker.form-text,input.stanford-timepicker.form-text').on('blur', function(){
	  jq1113(this).closest('.form-type-date-popup').find('[data-toggle="popover"]').popover('hide');
	});
  
	jQuery('textarea[name="companies_by_email"]').one('focus', function(){
	  jq1113(this).closest('.invite-companies-blocks').find('[data-toggle="popover"]').popover('show');
	});
	jQuery('textarea[name="companies_by_email"]').one('blur', function(){
	  jq1113(this).closest('.invite-companies-blocks').find('[data-toggle="popover"]').popover('hide');
	});
	
	jQuery('.rfp-bidder-fb-section tbody a').hover(function() {
	  jq1113(this).closest('.request-bid-intent-link-section a').find('[data-toggle="popover"]').popover('show');
    });
    jQuery('.rfp-bidder-fb-section tbody a').mouseout(function() {
	  jq1113(this).closest('.request-bid-intent-link-section a').find('[data-toggle="popover"]').popover('hide');	
    });
	jQuery('textarea.bid_package_name').focus(function(e) {    
      jq1113(this).closest('.rfp_add_bid_package').find('[data-toggle="popover"]').popover('show');
    });
    jQuery('textarea.bid_package_name').focusout(function(e) {
      jq1113(this).closest('.rfp_add_bid_package').find('[data-toggle="popover"]').popover('hide');
    });
	/*if(typeof CKEDITOR =='object'){
	  for ( var ckinstance in CKEDITOR.instances ){
		if(jQuery('textarea#'+ckinstance).hasClass('textarea-ckeditor-popover')){
		  CKEDITOR.instances[ckinstance].on('focus', function(){
			jq1113('.form-type-textarea').find('[data-toggle="popover"]').popover('show');
			jq1113('.form-type-textarea').find('.popover').removeClass('popover-gray-cust');		
		  });
		  CKEDITOR.instances[ckinstance].on('blur', function(){        
			jq1113('.form-type-textarea').find('[data-toggle="popover"]').popover('hide'); 
			jq1113('.form-type-textarea').find('.popover').addClass('popover-gray-cust');	       
		  });
		}
	  }
	}*/
	
	//Start new code popover for project using//   
	
	jQuery('input[name="next"]').on('hover', function(){
	 jq1113(this).closest('.form-actions').find('[data-toggle="popover"]').popover('show');
	 //jq1113(this).closest('.form-actions').find('.popover').addClass('edit-cust-draft-tooltip');
	});
	jQuery('input[name="next"]').on('mouseout', function(){
	 jq1113(this).closest('.form-actions').find('[data-toggle="popover"]').popover('hide');
     //jq1113(this).closest('.form-actions').find('.popover').removeClass('edit-cust-draft-tooltip');	
	});
	jQuery('#edit-cust-draft').on('hover', function(){
	 jq1113(this).closest('.form-actions').find('[data-toggle="popover"]').popover('show');
	 jq1113(this).closest('.form-actions').find('.popover').addClass('edit-cust-draft-tooltip');	
	});
	jQuery('#edit-cust-draft').on('mouseout', function(){
	 jq1113(this).closest('.form-actions').find('[data-toggle="popover"]').popover('hide');
     jq1113(this).closest('.form-actions').find('.popover').removeClass('edit-cust-draft-tooltip');	
	});
	
	//End code popover for project using//
	//start for proposl popover content here//
	
	//end for proposl popover content here
	
	//Start new code for rfp popover custom//
	

	//END code for rfp popover custom//
	Drupal.ajax.prototype.commands.InitializeCyclePugin = function(ajax, response, status) {
      if(jq1113('.m6-cycle-slider').length){
		 jq1113('.m6-cycle-slider').cycle(); 
	  }
    };
    
  });   
}

jQuery(document).ready(function () {
	
   if(jQuery(".user-messenger-notification-section").length){
	  jQuery(".user-messenger-notification-section").hover(            
		function() {
			jQuery('.dropdown-menu', this).stop( true, true ).fadeIn("fast");
			jQuery(this).toggleClass('open');
			//jQuery('span', this).toggleClass("caret caret-up");                
		},
		function() {
			jQuery('.dropdown-menu', this).stop( true, true ).fadeOut("fast");
			jQuery(this).toggleClass('open');
		   // jQuery('span', this).toggleClass("caret caret-up");                
		}
	  );
	}
     
   jQuery('a.custom-m6connect-message-link').click(function(e) {
     e.preventDefault();
     window.location.href = '/user-messaging';    
   });
   jQuery('input.select-roster-employee-checkbox').change(function () {
     jQuery(this).closest('table.m6connect-onboarding-in-process-table').find("input:checkbox").prop('checked', jQuery(this).prop("checked"));
   });
   
   jQuery(".menu-toggle-inner").click(function(e) { 
     'use strict';
     var id = jQuery(this).attr('id');
     var left_bar = '';
     if(id === 'menu-toggle'){
	   left_bar = 'open';
     }else{
	   left_bar = 'close'; 
     }
     jQuery.post( '/set-left-block-action', { left_bar_action: left_bar});
   });


    replace_page_feeds_icon();

    //show/hide Diversity Needs comment
    /* jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'none'); 
     // jQuery('.node-organization-form .form-field-name-field-diversity-needs').
     jQuery(".node-organization-form .form-field-name-field-diversity-needs").each(function(i){
     //this.checked = true;
     });*/

    /*jQuery('li.fbss-comments-edit-delete a').each(function(index, element) {
     if(!jQuery(this).hasClass('ctools-modal-assign-bid-package-popup-style')){
     jQuery(this).addClass('ctools-modal-assign-bid-package-popup-style');
     }
     });*/
    /*
     jQuery('li.fbss-comments-edit-delete a').each(function(index, element) {
     if(!jQuery(this).hasClass('ctools-modal-assign-dashboard-popup-style')){
     jQuery(this).addClass('ctools-modal-assign-dashboard-popup-style');
     }
     }); */
	 
	 jQuery('a.insurance-none-accessible').click(function(ev){
    	  if( jQuery('#insurance-access-dialog').length){
    		jQuery('#insurance-access-dialog').dialog({
    		  autoOpen: true,
    		  width: 550,
    		  modal: true,
    		  resizable: false,
    		  buttons: {
    			'Ok': function () {
    			  jQuery(this).dialog("close");
    			  jQuery(this).html('');
    			},
    		  },
    		  open: function () {
    		    jQuery('.ui-dialog-titlebar').hide();
    			jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
    		  },
    	    }).html('<div class="text-center"><strong>Thank you for your interest in Insurance Certificates.<br></strong></div><br><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to use Insurance Certificates.</strong></span><br><div class="pricing-info"><br><span class="pricing-text"><strong>Pricing for this feature is as follows:</strong></span><ul><li>$59 per month per individual</li><li>Please contact support for companies with more than 50 employees on M6Connect</li></ul></div>');
    		ev.preventDefault();
    		return false;
    	  }
     });
	 
	 jQuery('a.routing-none-accessible').click(function(ev){
    	  if( jQuery('#routing-access-dialog').length){
    		jQuery('#routing-access-dialog').dialog({
    		  autoOpen: true,
    		  width: 550,
    		  modal: true,
    		  resizable: false,
    		  buttons: {
    			'Ok': function () {
    			  jQuery(this).dialog("close");
    			  jQuery(this).html('');
    			},
    		  },
    		  open: function () {
    		    jQuery('.ui-dialog-titlebar').hide();
    			jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
    		  },
    	    }).html('<div class="text-center"><strong>Thank you for your interest in Routing Slip.<br></strong></div><br/><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to use Routing Slip services.</strong></span>');
    		ev.preventDefault();
    		return false;
    	  }
    }); 
	 
    jQuery('a.onboarding-none-accessible').click(function(ev){
    	  if( jQuery('#onboarding-access-dialog').length){
    		jQuery('#onboarding-access-dialog').dialog({
    		  autoOpen: true,
    		  width: 550,
    		  modal: true,
    		  resizable: false,
    		  buttons: {
    			'Ok': function () {
    			  jQuery(this).dialog("close");
    			  jQuery(this).html('');
    			},
    		  },
    		  open: function () {
    		    jQuery('.ui-dialog-titlebar').hide();
    			jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
    		  },
    	    }).html('<div class="text-center"><strong>Thank you for your interest in M6ID.<br></strong></div><br><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to use M6ID.</strong></span><br><div class="pricing-info"><br><span class="pricing-text"><strong>Pricing for this feature is as follows:</strong></span><ul><li>$29 per month per individual</li><li>Please contact support for companies with more than 50 employees on M6Connect</li></ul></div>');
    		ev.preventDefault();
    		return false;
    	  }
    });
	
	jQuery('a.none-cost-manager').click(function(ev){
    	  if( jQuery('#cost-manager-access-dialog').length){
    		jQuery('#cost-manager-access-dialog').dialog({
    		  autoOpen: true,
    		  width: 550,
    		  modal: true,
    		  resizable: false,
    		  buttons: {
    			'Ok': function () {
    			  jQuery(this).dialog("close");
    			  jQuery(this).html('');
    			},
    		  },
    		  open: function () {
    		    jQuery('.ui-dialog-titlebar').hide();
    			jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
    		  },
    	    }).html('<div class="text-center"><strong>Thank you for your interest in Cost Manager.<br></strong></div><br/><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to use Cost Manager services.</strong></span>');
    		ev.preventDefault();
    		return false;
    	  }
    });
	
    jQuery('a.none-scm-manager').click(function(ev){
        if( jQuery('#scm-manager-access-dialog').length){
        jQuery('#scm-manager-access-dialog').dialog({
          autoOpen: true,
          width: 550,
          modal: true,
          resizable: false,
          buttons: {
          'Ok': function () {
            jQuery(this).dialog("close");
            jQuery(this).html('');
          },
          },
          open: function () {
            jQuery('.ui-dialog-titlebar').hide();
          jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
          },
          }).html('<div class="text-center"><strong>Thank you for your interest in Supply Chain Manager.<br></strong></div><br/><span><strong>Please contact M6Connect Sales at <a href="mailto:sales@m6connect.com">sales@m6connect.com</a> to utilize Supply Chain services.</strong></span>');
        ev.preventDefault();
        return false;
        }
    });
  
  jQuery('a.none-scorecard-manager').click(function(ev){
        if( jQuery('#scorecard-manager-access-dialog').length){
        jQuery('#scorecard-manager-access-dialog').dialog({
          autoOpen: true,
          width: 550,
          modal: true,
          resizable: false,
          buttons: {
          'Ok': function () {
            jQuery(this).dialog("close");
            jQuery(this).html('');
          },
          },
          open: function () {
            jQuery('.ui-dialog-titlebar').hide();
          jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
          },
          }).html('<div class="text-center"><strong>Thank you for your interest in Scorecard.<br></strong></div><br/><span><strong>Please contact M6Connect Sales at <a href="mailto:sales@m6connect.com">sales@m6connect.com</a> to utilize Scorecard services.</strong></span>');
        ev.preventDefault();
        return false;
        }
    });
	jQuery('a.onboarding-none-m6id-site-manager').click(function(ev){
		  var adminemail = jQuery(this).data("email");
		  if(adminemail){
			adminemail = '<a href="mailto:'+adminemail+'">'+adminemail+'</a>';  
		  }
		  var popmsg = '<div class="text-center"><strong>To use this service contact your company admin '+adminemail+'. Request assignment of M6ID Manager or Site Manager role.</strong></div>'; 
    	  if( jQuery('#onboarding-access-dialog').length){
    		jQuery('#onboarding-access-dialog').dialog({
    		  autoOpen: true,
    		  width: 550,
    		  modal: true,
    		  resizable: false,
    		  buttons: {
    			'Ok': function () {
    			  jQuery(this).dialog("close");
    			  jQuery(this).html('');
    			},
    		  },
    		  open: function () {
    		    jQuery('.ui-dialog-titlebar').hide();
    			jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
    		  },
    	    }).html(popmsg);
    		ev.preventDefault();
    		return false;
    	  }
    });

    // pop for alert in left panel. If company or individual not purchased alert service then open dialog
    jQuery('a.alert-none-accessible').click(function(ev){
        var mainElement = jQuery(this);
          if( jQuery('#alert-access-dialog').length){
            jQuery('#alert-access-dialog').dialog({
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
              },
              open: function () {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
              },
            }).html('<div class="text-center"><strong>Thank you for your interest in Alerts.<br></strong></div><br/><span><strong>Please contact M6Connect Support at <a href="mailto:support@m6connect.com">support@m6connect.com</a> to send Alerts.</strong></span><br/><div class="pricing-info"><br/><span class="pricing-text"><strong>Pricing for this feature is as follows:</strong></span><ul><li>$25 per month for individual accounts</li><li>$125 per month for companies with less than 50 employees on M6Connect</li><li>Please contact support for companies with more than 50 employees on M6Connect</li></ul></div>');
            ev.preventDefault();
            return false;
          }
    });

    jQuery('a.alert-myservice-none-accessible').click(function(ev){
        var mainElement = jQuery(this);
        var company_title = mainElement.attr('data-company');
        var company_email = mainElement.attr('data-email');
        var company_nid = mainElement.attr('data-nid');
          if( jQuery('#alert-access-dialog').length){
            jQuery('#alert-access-dialog').dialog({
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
              },
              open: function () {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
              },
            }).html('<div class="text-center"><strong>Please contact your company administrator and request Alert Manager access - they can change your user settings on the <a href="/node/'+company_nid+'">'+company_title+'</a> page under User Management. Your company administrator is: <a href="mailto:'+company_email+'">'+company_email+'</a></li></ul></div>');
            ev.preventDefault();
            return false;
          }
    });
   /*jQuery('.border-box').hide();
  jQuery('.go-pro-chat').click(function (e) {
    jQuery('.border-box').toggle();  
  });*/
  /*jQuery('.get-user-popup').click(function (e) {
     jQuery('.single-window-chat').toggle();
  	 jQuery('.usr-name').text(jQuery(this).text());
  	 jQuery('#messages').css('list-style-type','none');
  	 jQuery('#messages').css('margin','0');
  	 jQuery('#messages').css('padding','0');
  	 jQuery('#messages li').css('padding','5px 10px');
  	 jQuery('#messages li:nth-child(odd)').css('background','#eee');	
  });
  jQuery('.single-window-chat .close').click(function (e) {
    jQuery('.single-window-chat').hide();
  });
  jQuery('.addon-sp').click(function (e) {
	  var getMsg = jQuery('.input-sp').val();  
    var socket = io('http://52.24.154.41:8080');
    socket.on('chat message', function(msg){
      console.log(msg);
	  jQuery('.user-msg-input #messages').append(jQuery('<li>').text(msg));
	  jQuery('.input-sp').val('');  
    });
    msgval(getMsg);
    function msgval(data_msg){
	    socket.emit('chat message', data_msg);
	  }
  });*/
  jQuery('.dashboard-link-hover').hover(mouseIn);
  jQuery('.custum-projects-link-hover').mouseleave(mouseOut);  
  
  function mouseIn(e) { 
    var getService = jQuery(this).attr('data');	
	jQuery('ul.dashboard-block-list li a').each(function(e) {
      if(jQuery(this).attr('data') != getService) {
	    jQuery(this).siblings('.custum-projects-link-hover').hide();  
	  }
	  else {
	    jQuery(this).siblings('.custum-projects-link-hover-'+getService).show('slow');   
	  }
    });    
  }

  function mouseOut(e) { 
    jQuery('.custum-projects-link-hover').hide();
    var getData = jQuery(this).siblings('.dashboard-link-hover').attr('data');
	jQuery(this).hide('slow'); 
  }
  
});




function replace_page_feeds_icon() {
    /************* Replacet comment work from icon on company profile page ***************/
    //var ct = jQuery('.newsfeed .fbss-comments-show-comment-form a.fbss-comments-show-comment-form-link').text();alert(ct);
//    jQuery('.news-item .fbss-comments-show-comment-form a.fbss-comments-show-comment-form-link').text('');
//    jQuery('.news-item .fbss-comments-show-comment-form a.fbss-comments-show-comment-form-link').html('<i class="fa fa-comment">');

    jQuery('.news-item .statuses-links .statuses-edit a').text('');
    jQuery('.news-item .statuses-links .statuses-delete a').text('');
    jQuery('.statuses-item .statuses-created a.statuses-repost').text('');
    jQuery('.news-item .statuses-links .statuses-edit a').html('<i class="fa fa-edit">');
    jQuery('.news-item .statuses-links .statuses-delete a').html('<i class="fa fa-trash">');
    jQuery('.statuses-item .statuses-created a.statuses-repost').html('<i class="fa fa-share-alt"></i> share');

    jQuery('.news-item .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-edit-link a').text('');
    jQuery('.news-item .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-delete-link a').text('');
    jQuery('.news-item .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-edit-link a').html('<i class="fa fa-edit">');
    jQuery('.news-item .comment-box .fbss-comments ul.fbss-comments-links .fbss-comments-delete-link a').html('<i class="fa fa-trash">');


    //show/hide Diversity Needs comment
    /* jQuery('.node-organization-form .form-field-name-field-diversity-needs-comment').css('display', 'none'); 
     // jQuery('.node-organization-form .form-field-name-field-diversity-needs').
     jQuery(".node-organization-form .form-field-name-field-diversity-needs").each(function(i){
     //this.checked = true;
     });*/
    jQuery('.content .statuses-links .statuses-edit a').text('');
    jQuery('.content .statuses-links .statuses-edit a').html('<i class="fa fa-edit">');
    jQuery('.content .statuses-links .statuses-delete a').text('');
    jQuery('.content .statuses-links .statuses-delete a').html('<i class="fa fa-trash">');
//	 jQuery('.content .statuses-comments a.fbss-comments-show-comment-form-link').text('');
//	 jQuery('.content .statuses-comments a.fbss-comments-show-comment-form-link').html('<i class="fa fa-comment">');
//	 jQuery('#cutom_statuses_stream_div .comment-box a.fbss-comments-show-comment-form-link').text('');
//	 jQuery('#cutom_statuses_stream_div .comment-box a.fbss-comments-show-comment-form-link').html('<i class="fa fa-comment">');

    /*jQuery('li.fbss-comments-edit-delete a').each(function(index, element) {
     if(!jQuery(this).hasClass('ctools-modal-assign-bid-package-popup-style')){
     jQuery(this).addClass('ctools-modal-assign-bid-package-popup-style');
     }
     });*/
    jQuery('.fbss-comments-edit-delete').find('a').addClass('ctools-modal-assign-dashboard-popup-style');

    jQuery('.cust-dash-post-share').find('a').addClass('ctools-modal-assign-dashboard-popup-style');
    jQuery('[id^=like-comment-text-]').each(function () {
        jQuery(this).append(jQuery(this).next());
        jQuery(this).append(jQuery(this).next());
    });
    jQuery('.remove_link').each(function () {
        jQuery(this).parent().html('<span class="btn btn-primary connection-info">Connected</span>');
    });
    jQuery('.find-people-connect').each(function () {
        jQuery(this).find('a').each(function () {
            if (jQuery(this).html() == 'pending requests') {
                jQuery(this).parent().html('<span class="btn btn-primary connection-info">Request Sent</span>');
            }
        });
    });
    jQuery('.group-members').each(function () {
        jQuery(this).find('a').each(function () {
            if (jQuery(this).html() == 'pending requests') {
                jQuery(this).parent().html('<span class="btn btn-primary connection-info">Pending</span>');
            }
        });
    });
}

Drupal.behaviors.custom_dash_share = {
    attach: function (context, settings) {
        replace_page_feeds_icon();
		jq1113('.node-onboarding-form .form-type-managed-file label').hide();
		jq1113('.node-onboarding-form .form-type-managed-file .description').hide();
		jq1113('.node-onboarding-form .image-widget-data .file').hide();
		jq1113('.node-onboarding-form .image-widget-data .file-size').hide();
		
		jQuery('.m6id-popup-print-icon').on('click',function(){
		  var containerClass = '.m6id-batch-info-popup';
		  if(!jQuery(this).closest(containerClass)){
			containerClass = '.m6id-profile-detail-page';  
		  }
		  var container = jQuery(this).closest(containerClass).find('.m6id-profile-detail-data');
		  var carousel = container.find('#carousel-m6id-company');
		  if(carousel.length){
			 carousel.find('.item.active .m6id-popup-print-link').trigger('click');
		  }else{
			 container.find('.m6id-popup-print-link').trigger('click'); 
		  }
		});	
		
		jQuery('.m6id-popup-print-link').on('click',function(){
		  var screenWidth = screen.width;
		  var screenHeight = screen.height;
		  var form = jQuery(document.createElement('form'));
		  if(jQuery(this).hasClass('m6id-popup-emp-print')){
			var empId = jQuery(this).data('empid');
			//console.log(empId);  
            jQuery(form).attr("action", "/m6id-employee-badge-print");
            jQuery(form).attr("method", "POST");
			jQuery(form).attr("target", "m6id_employee_popup");
			jQuery(form).attr("onsubmit", "window.open('about:blank','m6id_employee_popup','location=0,status=0,scrollbars=0,menubar=0,resizable=0,titlebar=0,toolbar=0,width="+screenWidth+",height="+screenHeight+"');");
            var textarea = jQuery("<textarea>").attr("name", "print_selected").val(empId);
            jQuery(form).append(jQuery(textarea));
			//var input = jQuery("<input>").attr("name", "print_type").val('avery_5361');
			//jQuery(form).append(jQuery(input));
            jQuery(form).submit();    
		  }else if(jQuery(this).hasClass('m6id-popup-roster-print')){ 
		    var rosterId = jQuery(this).data('roster');  
            jQuery(form).attr("action", "/roster-m6id-print");
            jQuery(form).attr("method", "POST");
			jQuery(form).attr("target", "m6id_roster_popup");
			jQuery(form).attr("onsubmit", "window.open('about:blank','m6id_roster_popup','location=0,status=0,scrollbars=0,menubar=0,resizable=0,titlebar=0,toolbar=0,width="+screenWidth+",height="+screenHeight+"');");
            var textarea1 = jQuery("<textarea>").attr("name", "print_selected").val(rosterId);
            jQuery(form).append(jQuery(textarea1));
			//var input = jQuery("<input>").attr("name", "print_type").val('avery_5361');
			//jQuery(form).append(jQuery(input));
            jQuery(form).submit();  
		  }else{
			//var targetUrl = jQuery(this).data('url');  //,width="+screen.width+",height=".screen.height
			//window.open(targetUrl, "m6idpopup", "location=0,status=0,scrollbars=0,menubar=0,resizable=0,titlebar=0,toolbar=0,width="+screenWidth+",height="+screenHeight);  
		  }
		});
		
		jQuery('.m6id-popup-bulk-print').on('click',function(){
		  var print_type = jQuery(this).data('print-type');
		  var checkboxTable = jQuery(this).closest('fieldset.m6id-roster-invitees').find('table.m6connect-onboarding-in-process-table');
		  var selected = []; 
		  var screenWidth = screen.width;
		  var screenHeight = screen.height;
		  checkboxTable.find('input[type="checkbox"]:checked').each(function(index, element) {
             selected.push(jQuery(this).val());
          });
		  if(selected.length){
			var form = jQuery(document.createElement('form'));
            jQuery(form).attr("action", "/roster-m6id-print");
            jQuery(form).attr("method", "POST");
			jQuery(form).attr("target", "m6id_roster_popup");
			jQuery(form).attr("onsubmit", "window.open('about:blank','m6id_roster_popup','location=0,status=0,scrollbars=0,menubar=0,resizable=0,titlebar=0,toolbar=0,width="+screenWidth+",height="+screenHeight+"');");
            var textarea = jQuery("<textarea>").attr("name", "print_selected").val(selected.join());
            jQuery(form).append(jQuery(textarea));
			var input = jQuery("<input>").attr("name", "print_type").val(print_type);
			jQuery(form).append(jQuery(input));
            jQuery(form).submit();  
		  }
		});
		
		///
		   //jQuery('.carousel-m6id-top').hide();
	
	var flagCount = 0;
	jq1113('#carousel-m6id-company').bind('slide.bs.carousel', function (e) {
	  var tt = jq1113('#carousel-m6id-company').find(".carousel-inner .active").next().attr('id');	
	  
	    if(tt == 'vertical-slider') {
		    jq1113('#carousel-m6id-company').addClass('verticalSlider-cust');
			jq1113('.custom-arrow-vertical-top').show();
		}
		else {
		  jq1113('#carousel-m6id-company').removeClass('verticalSlider-cust');
		  jq1113('.custom-arrow-vertical-top').hide();
		}			  
    });	
	
	jq1113('.carousel-control i.fa-angle-left').click(function (e) {
	  var prev = jq1113('#carousel-m6id-company').find(".carousel-inner .active").prev().attr('id');	
	    if(prev == 'vertical-slider') {
		    jq1113('#carousel-m6id-company').addClass('verticalSlider-cust');
			jq1113('.custom-arrow-vertical-top').show();
		}
		else {
		  jq1113('#carousel-m6id-company').removeClass('verticalSlider-cust');
		  jq1113('.custom-arrow-vertical-top').hide();
		}
	});
	
	/*jq1113('#carousel-m6id-company').on('slide.bs.carousel', function () {	  
    });*/
	/*jq1113('#carousel-m6id-company').bind('slid', function (e) {
      var getvertical = jq1113(e.target).find(".active").attr('id');
	  alert(getvertical);
	  if(getvertical == 'vertical-slider') {
		  alert('in');
	      jq1113('#carousel-m6id-company').addClass('verticalSlider-cust');
		  jq1113('.custom-arrow-vertical-top').show();
	  }
	  else {
	    jq1113('#carousel-m6id-company').removeClass('verticalSlider-cust');
		jq1113('.custom-arrow-vertical-top').hide();
	  }
      
    });*/
	jq1113('.custom-arrow-vertical-top i').click(function (e) {
	  e.preventDefault();
	  var getButtonVal = jq1113(this).attr('id');
	  if(getButtonVal == 'prev') {
	    jq1113('.custom-arrow-vertical .prev a').trigger('click');
	  }
	  else {
	    jq1113('.custom-arrow-vertical .next a').trigger('click');
	  }
	});
	
	//jq1113('.tooltip').tooltipster();	 	
	 var tooltipissuedate = jQuery('<span class="tooltip-main-custom padding-5"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_issue_date">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_issue_date"><p>Estimated issue date for the RFP (Bid packages).</p></span></div></i></span>');	
    jQuery(".field-name-field-proj-rpf-issue-date .fieldset-legend").append(tooltipissuedate);
	
	//Bid Due Date
    var tooltipbidduedate = jQuery('<span class="tooltip-main-custom padding-5"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_bid_due_date">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_bid_due_date"><p>Estimated Bid Due date for the RFP.</p></span></div></i></span>');
    jQuery(".field-name-field-proj-bid-date .fieldset-legend").append(tooltipbidduedate);
    
    //Work Start Date
	var tooltipstartdate = jQuery('<span class="tooltip-main-custom padding-5"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_start_date">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_start_date"><p>Estimated  date when work is expected to begin.</p></span></div></i></span>');
    jQuery(".field-name-field-proj-start-date .fieldset-legend").append(tooltipstartdate);
    
   //Work Completion Date
	var tooltipcompletedate = jQuery('<span class="tooltip-main-custom padding-5"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_complete_date">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_complete_date"><p>Estimated  date when work is to be completed.</p></span></div></i></span>'); 
   jQuery(".field-name-field-proj-complete-date .fieldset-legend").append(tooltipcompletedate);
   
   //Rfp Expected Awardd date

   var tooltiprfpexpawarddate = jQuery('<span class="tooltip-main-custom"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_rfp_estimatedddate">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_rfp_estimatedddate"><p>This is just an estimated award time-<br/>your company is not bound for this<br/> date.</p></span></div></i></span>');
 jQuery(".form-field-name-field-expected-award .fieldset-legend").append(tooltiprfpexpawarddate);
 
 //Rfp Expected Start date
   var tooltiprfpstartdate = jQuery('<span class="tooltip-main-custom"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_rfp_expectedstart">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_rfp_expectedstart"><p>The anticipated date your company<br/> estimates the work can begin.</p></span></div></i></span>');
 jQuery(".form-field-name-field-expected-start .fieldset-legend").append(tooltiprfpstartdate);
 
 //Rfp Expected expected end
  var tooltiprfpexpectedend = jQuery('<span class="tooltip-main-custom"><i class="fa fa-question-circle custom-tooltip" aria-hidden="true"><span class="tooltip" data-tooltip-content="#tooltip_rfp_expectedend">&nbsp;</span><div class="tooltip_templates"><span id="tooltip_rfp_expectedend"><p>The anticipated date your company<br/> estimates the work should be<br/> completed.</p></span></div></i></span>');
 jQuery(".form-field-name-field-expected-end  .fieldset-legend").append(tooltiprfpexpectedend);
 
   jq1113('.tooltip').tooltipster({
       contentCloning: true
     });
	
      /*var getSlider = jQuery(".dashboard-block-darkgray #carousel-m6id-company .carousel-inner .item");
			   getSlider.each(function (index) {
			    if(jQuery(this).hasClass('vertical-m6-slider')) {
				  if(jQuery(this).hasClass('active')) {
					
				    jQuery('#carousel-m6id-company').addClass('verticalSlider-cust');					
				  }	   
				}
				else {
				  jQuery('#carousel-m6id-company').removeClass('verticalSlider-cust');				  
				}
  			    
			   });*/

        // Binding click event on upload button.
        // on page /update-company-logo-photo/%/nojs.

        // Initializing the Crop Plugin on the Above Page.
        // jQuery('.image-editor').cropit({
        //   //
        //   imageBackground: true,
        //   imageBackgroundBorderSize: 100,
        //   width: 299,
        //   height: 200,
        // });
      }
};

