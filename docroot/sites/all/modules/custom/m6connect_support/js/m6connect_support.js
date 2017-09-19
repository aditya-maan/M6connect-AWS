/*jQuery(document).ready(function(){
	function email_validation_error() {
	  console.log("hello");
	}
});*/
/*(function ($) {
  	$.fn.support_change_email = function(user_id, email) {
  		document.getElementById("support_email_message").innerHTML = '<img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />';
	    var datastring = "change_email=1&user_id="+user_id+"&email="+email;
	    jQuery.ajax({  
	        type: "POST",  
	        url: '/support-ajax-email-change',
	        data: datastring,  
	        success: function(data) {   
	            if(data == 1){
	            	document.getElementById("support_email_message").innerHTML = '<div class="text-success">Email updated successfully</div>';
	            }
	        },        
	    });
  	};
}) (jQuery);*/

jQuery(document)
	.ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    	var urlajax = ajaxOptions.url;
	   	// ajax function for update user email
	    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name === "email_change"){
	    	var user_id = document.getElementById("support_user_id").value;
	    	var email = document.getElementById("support_user_email").value;
	    	if(email){
	    		document.getElementById("support_email_message").innerHTML = '<img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />';
	        	var datastring = "change_email=1&user_id="+user_id+"&email="+email;
			    jQuery.ajax({  
			        type: "POST",  
			        url: '/support-ajax-email-change',
			        data: datastring,  
			        success: function(data) {   
			            if(data == 1){
			            	document.getElementById("support_email_message").innerHTML = '<div class="text-success">Email updated successfully</div>';
			            	setTimeout(function(){
			            		jQuery("span.popups-close").click();
			            	}, 2000);
			            }
			        },
			    });
	    	}        	
        }	    
        // ajax function for update user password
	    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name === "password_change"){        	
	    	var user_id = document.getElementById("support_user_id").value;
	    	var password = document.getElementById("support_user_password").value;
	    	if(password){
	    		var re = /^(?=.*\d)(?=.*[@#\-_$%^&+=§!\?])(?=.*[a-z])(?=.*[A-Z])[0-9A-Za-z@#\-_$%^&+=§!\?]{8,30}$/;	    		
	    		if(password.match(re)){
		    		document.getElementById("support_password_message").innerHTML = '<img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />';
		        	var datastring = "change_password=1&user_id="+user_id+"&password="+password;
				    jQuery.ajax({  
				        type: "POST",  
				        url: '/support-ajax-password-change',
				        data: datastring,  
				        success: function(data) {   
				            if(data == 1){
				            	document.getElementById("support_password_message").innerHTML = '<div class="text-success">Password updated successfully</div>';
				            	setTimeout(function(){
				            		jQuery("span.popups-close").click();
				            	}, 2000);
				            }
				        },
				    });
				}
	    	}        	
        }
    })
    .ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    });

function sortFormSubmit(){
	jQuery("#custom-sorting-form").submit();
}