// JavaScript Document
jQuery(document).ready(function(e) {	

jQuery('.user-messenger-notification-section .user-notification-outer .button_close_slide').click(function() {
jQuery('.user-messenger-notification-section .dropdown-menu').css( "display", "none" );
});
//     jQuery(document).ready(function() {
//     //var yetVisited = localStorage['get_notification'] = 'yes'; 
    
//     if(localStorage['get_notification']){
//     jQuery('.user-edit-profile-section').addClass( "cccccc" ); 
//     jQuery('.user-edit-profile-section .dropdown-menu').css( "display", "none" );
    
//     // jQuery('.user-messenger-notification-section').addClass( "cccccc" ); 
//     // jQuery('.user-messenger-notification-section .dropdown-menu').css( "display", "none" );
//   }
// });
// 	jQuery('.button_close_slide').click(function() {
//     var yetVisited = localStorage['get_notification'] == 'yes'; 
//   //   if(yetVisited){
//   //   jQuery('.user-messenger-notification-section').hide();
//   //   //alert('test == '.yetVisited);  
//   // }
// });

// 	jQuery(document).ready(function() {
//     var isshow = localStorage.getItem('isshow');
//     if (isshow== null) {
//         localStorage.setItem('isshow', 1);
//         jQuery('.user-edit-profile-section .dropdown-menu-right').show();
//     } else {
//     	jQuery('.user-edit-profile-section .dropdown-menu-right').hide();
//     }

// });
	
  /*jQuery('.nice-menu-main-menu .menu__item .main-menu-link-notification').each(function(index, element) {
    var linkid = jQuery(this).attr('id');
     var count = Drupal.settings.m6connect_common.notification_user[linkid].count
     if(count){
	   jQuery(this).append('<span class="notification-count">'+count+'</span>');  
     }
  });*/
  jQuery('.nice-menu-main-menu .menu-223 a').html('<i class="fa fa-home"></i>'); 
  
  jQuery('body').on('click','table#company-mail-detail-table .user-company-delete-trash-link',function(){
	var comapnyName = jQuery(this).data('cmptitle');
	var comapnynid = jQuery(this).data('cmpnid');
	var useruid = jQuery(this).data('useruid');
	if( jQuery('#revoke-company-access-dialog').length){
	  jQuery('#revoke-company-access-dialog').dialog({
		  autoOpen: false,
		  width: 550,
		  height: 'auto',
		  modal: true,
		  resizable: false,
		  buttons: {
			  'Confirm': function () {
				  jQuery(this).dialog("close");
				  jQuery(this).html('');
				  jQuery.post( '/revoke-company-access/'+comapnynid, { useruid: useruid, js: 1 }).done(function( data ) {
                     if(data.tablehtml!=''){
					   jQuery('table#company-mail-detail-table').replaceWith(data.tablehtml);
					   Drupal.attachBehaviors(jQuery('body'));
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
		  },
	  });
	  
	  jQuery.post('/revoke-company-access-content/'+comapnynid+'/'+useruid).done(function( data ) {
        if(data.popupcontent!=''){
		  jQuery('#revoke-company-access-dialog').html(data.popupcontent);
		  jQuery('#revoke-company-access-dialog').dialog('open');
		}
      });
	  
	}
  });

	jQuery('body').on('click','table#company-mail-detail-table .user-company-edit-email-link',function()
	{
		var comapnyName = jQuery(this).data('cmptitle');
		var comapnynid = jQuery(this).data('cmpnid');
		var useruid = jQuery(this).data('useruid');
		if( jQuery('#edit-company-email-dialog').length){
		  	jQuery('#edit-company-email-dialog').dialog({
				autoOpen: false,
				width: 400,
				height: 'auto',
				modal: true,
				resizable: false,
				buttons: {
					'Confirm': function () {
						/*jQuery(this).dialog("close");
						jQuery(this).html('');*/
						var Email = jQuery("#edit-user-credendial-email-submitted").val();
						if(!isEmail(Email))
						{
							jQuery(".onboarding-login-form-error").html("Please enter valid email address");
							return false;
						}
						var currentElm = this;
						jQuery.post( '/edit-company-email-submit/'+comapnynid, { useruid: useruid, js: 1, email: Email }).done(function( data ) {
		                    if(data.tablehtml == 'Success'){
		                    	jQuery(".listing-row-"+comapnynid+" td.view-user-company-email").html(Email);
								/*jQuery('table#company-mail-detail-table').replaceWith(data.tablehtml);
							   	Drupal.attachBehaviors(jQuery('body'));*/
							   	jQuery(currentElm).dialog("close");
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
				},
		  	});
		  
		  	jQuery.post('/edit-company-email-content/'+comapnynid+'/'+useruid).done(function( data ) {
		        if(data.html!=''){
				  jQuery('#edit-company-email-dialog').html(data.html);
				  jQuery('#edit-company-email-dialog').dialog('open');
				}
	      	});		  
		}
	});
	//primary company select
	jQuery("input[name*='primary_company']").click(function () {
        var primarycomnid = jQuery(this).val();
		jQuery.post( "/primary/company/"+primarycomnid );       
    });
	//hide company name on user profile
	jQuery("input[name*='com_hide_on_profile']").click(function () {
        var hidecomnid = jQuery(this).val();
		var hasaction = '';  
		if($(this).is(':checked')){
		  hasaction = 'checked';
		}else{
		  hasaction = 'unchecked';
		}
		jQuery.post( "/companyname/hideonprofile/"+hasaction+"/"+hidecomnid );       
    });
});

function myDashboadImage() {
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 100);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 500);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 1000);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 1500);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 2000);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 2500);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 3000);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 3500);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 4000);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 4500);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 5000);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 5500);
  setTimeout(function(){ 
  jQuery.fancybox.update();			
  }, 6000);  
}


function isEmail(email) {
  var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;
  return regex.test(email);
}