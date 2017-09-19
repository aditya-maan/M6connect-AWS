 jQuery(document).ready(function (e) {    
    jQuery('.company-user-bulk-upload-form').on('change','div.csv-file-attachment input[type="file"]',function(e){
	  jQuery('.company-user-bulk-upload-form').find('input[name="csv-fid_upload_button"]').trigger('mousedown');  
    });
  
	Drupal.ajax.prototype.commands.insertInCkeditor = function(ajax, data, status) {
	  var textareaInstance = jQuery(data.selector).attr('id');
      CKEDITOR.instances[textareaInstance].setData(data.arguments);
    };
	
/*	Drupal.ajax.prototype.commands.insertInEmoji = function(ajax, data, status) {
	  jQuery(data.selector).emojioneArea({
					   container: ".message-abc-cont",
					   hideSource: true,
					   useSprite: false,
					   saveEmojisAs: "image",
					   imageType: "png",
					   shortnames: false,
				     });
    };*/
	
    jQuery("a.connected-user-action-btn").click(function() {
	  jQuery('.user-page-connect-category .ctools-dropdown-container-wrapper .ctools-dropdown-container').css('display','none');
	});

    // left panel toggle
    /*jQuery(".menu-toggle-inner").click(function(e) { 
        var left_panel_expanded = jQuery(".menu-toggle-inner").attr("aria-expanded");            
        if(left_panel_expanded == 'false'){
          localStorage.setItem("left-panel-toggle", "in");  
          jQuery('.menu-toggle-inner').attr("aria-expanded", "true");             
        }else if(left_panel_expanded == 'true'){
          localStorage.removeItem("left-panel-toggle");   
          jQuery('.menu-toggle-inner').attr("aria-expanded", "false");       
        }
    });  */  
  
/*   if ($.fancybox.isOpened) {
	 if ($.fancybox.current) {
		$.fancybox.current.height = 500;
	 }
  }
  $.fancybox.reposition();*/
  
  jQuery(window).scroll(function(){
	var sticky = jQuery('.navbar-left-content'),
		scroll = jQuery(window).scrollTop();
  
	if (scroll >= 377) sticky.addClass('navbar-left-content-fixed');	
	else sticky.removeClass('navbar-left-content-fixed');
  });
	
	
	jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
		var urlajax = ajaxOptions.url;
		//console.log(ajaxOptions); 
		if (urlajax.indexOf("/file/ajax/field_logo")==0){
			jQuery(".form-field-name-field-logo").find('.messages--error').remove();
		}
		if (urlajax.indexOf("/file/ajax/field_company_profile_cover_img")==0){
			jQuery(".form-field-name-field-company-profile-cover-img").find('.messages--error').remove();
		}
		if (urlajax.indexOf("/file/ajax/field_user_profile_photo")==0){
			jQuery(".field-name-field-user-profile-photo").find('.messages--error').remove();
		}
		
		if (urlajax.indexOf("/file/ajax/field_user_profile_cover_img")==0){
			jQuery(".field-name-field-user-profile-cover-img").find('.messages--error').remove();
		}
		if (urlajax.indexOf("/file/ajax/organigation_main_container/organization_logo_contianer/organization_logo")==0){
			jQuery(".organigation-logo-section").find('.messages--error').remove();
		}
		
			
	});
	
	
  //if(jQuery('body').hasClass('page-companies')){
	
	  //var base_url_noti = window.location.origin;
    if(Drupal.settings.hasOwnProperty('m6connect_misc') && Drupal.settings.m6connect_misc.hasOwnProperty('user_authorized') && Drupal.settings.m6connect_misc.user_authorized){
	  jQuery.ias({
		container : '.user-notification-outer', 
		item: '.notification-inner',
		pagination: '.notinav',
		next: '.notinav a',
		 loader: '<img src="'+Drupal.settings.m6connect_misc.base_url+'/sites/all/themes/m6connect/images/ajax-loader.gif"/>',
		triggerPageThreshold:0,
		trigger: "See More", 
	   
		
	  });
	  

	}
	
	if(jQuery('body').hasClass('page-node-add-my-proposal')){
	
	  jQuery.ias({
		  container : 'tbody', 
		  item: '.proposal-select-row',
		  pagination: '.page-scroll-btn',
		  next: '.page-scroll-btn a',
		   loader: '<img src="/sites/all/themes/m6connect/images/ajax-loader.gif"/>',
		  triggerPageThreshold:0,
		  trigger: "See More", 		
		});	
	}
	
	if(jQuery('body').hasClass('page-insurance-certificates')){
	
	  jQuery.ias({
		  container : '.page-has-scroll', 
		  item: '.page-scroll',
		  pagination: '.page-scroll-btn',
		  next: '.page-scroll-btn a',
		   loader: '<img src="/sites/all/themes/m6connect/images/ajax-loader.gif"/>',
		  triggerPageThreshold:0,
		  trigger: "See More", 		
		});	
	}
	
	
	if(jQuery('body').hasClass('page-dashboard')){
		jQuery("#dLabel1").click(function() {
			jQuery('.form-item-share-com-list .chosen-container').trigger('mousedown');
			jQuery('.chosen-container').addClass('chosen-container-active chosen-with-drop');
		});
		jQuery("li.active-result").click(function() {
			//jQuery('.company-list-contaner1 .form-item-share-com-list .chosen-single span').css('display','block');
			
		});
		
	}
	
	
  //}


/*      $('#viewmconnections-ucr_all').click(function(){
        $('#ucr_all').addClass("active in");       
    });
*/



    jQuery(".form-item-add-company").hide();

    jQuery(".add-new-link").click(function () {

        jQuery(".form-item-og-user-node-und-0-default").hide();

        jQuery(this).hide();

        jQuery(".form-item-add-company").show();

    });

    //jQuery('.form-checkbox').click(function() {
    /*jQuery("input[name*='field_diversity_credentials']").click(function() {	
     var input = jQuery(this);
     var id = input.attr('id');	//alert(id);
     if((input).is(':checked')) {
     //alert('chked');	
     }
     });*/


    jQuery(".custwrapcrd, .dneedscustwrapcrd").css('display', 'none');
    jQuery("#edit-field-diversity-credential").css('display', 'none');

    jQuery("#edit-field-dcrednid-22").css('display', 'none');
    jQuery("#edit-field-dcrednid-23").css('display', 'none');

    jQuery("#edit-field-diversity-credentials-und	.form-checkbox").each(function (i) { //alert('vv'); 
        if (jQuery(this).is(':checked')) {
            var vl = jQuery(this).val();
            jQuery(".customwrapcrd_" + vl).css('display', 'block');
        }
    });
    jQuery("#edit-field-diversity-needs-und .form-checkbox").each(function (i) { //alert('vv'); 
        if (jQuery(this).is(':checked')) {
            var vl = jQuery(this).val();
            jQuery(".dneedscustomwrapcrd_" + vl).css('display', 'block');
        }
    });

    jQuery("input[name*='field_diversity_credentials']").click(function () {
        var input = jQuery(this);
        //var id = input.attr('id');	alert(id);
        var id = input.val();	//alert(v);
        if ((input).is(':checked')) {
            //alert('chked');
            jQuery(".customwrapcrd_" + id).css('display', 'block');
        } else {
            jQuery(".customwrapcrd_" + id).css('display', 'none');
        }
    });
    /*************** login user add company click on diversity **** start ************/ 
      
      jQuery(document).on('change', 'select.addcom_diversity_credentials', function(e) {  
        var diversity_cre_val = jQuery(this).val();    
        if (diversity_cre_val) {
          jQuery(diversity_cre_val).each(function(index, element) {        
            jQuery(".form-group .customwrapcrd_" + element).css('display', 'block');
          });
        }else{
          jQuery(".form-group .custwrapcrd, .dneedscustwrapcrd").css('display', 'none');
        }
      });
    /*************** login user add company click on diversity **** end ************/
    jQuery("input[name*='field_diversity_needs']").click(function () {
        var input = jQuery(this);
        //var id = input.attr('id');	alert(id);
        var id = input.val();	//alert(v);
        if ((input).is(':checked')) {
            //alert('chked');
            jQuery(".dneedscustomwrapcrd_" + id).css('display', 'block');
        } else {
            jQuery(".dneedscustomwrapcrd_" + id).css('display', 'none');
        }
    });

    jQuery('#edit-field-annual-revenue-und-0-value').keyup(function (i) {
        //var text = jQuery(this).val(); //alert(text);
        jQuery(this).val(format(jQuery(this).val())); //alert(text);
        //text = text.replace(/-/g, '');
        //text = text.replace("$", '');
        //alert(text);
        //var amt =  format2(parseFloat(text), "$");
        //var amt = format(text); 
        //jQuery(this).val(text.replace(/(\d{2})(\d{3})(\d{3})/, '$ $1,$2,$3.00'));
    });

    jQuery('input[name="field_number_of_employees[und][0][value]"] ').keyup(function (i) {
        var formated = format(jQuery(this).val());
        formated = formated.replace("$", "");
        jQuery(this).val(formated); //alert(text);
    });

    jQuery('#edit-field-org-phone-und-0-value').blur(function (i) {
        //return text.replace(/(\d{3})(\d{3})(\d{4})/, '($1)-$2-$3');
        var text = jQuery(this).val();
        text = text.replace(/-/g, '');
        ///jQuery(this).val(text.replace(/(\d{3})(\d{3})(\d{4})/, '($1)-$2-$3'));
		jQuery(this).val(text.replace(/(\d{3})(\d{3})(\d{4})/, '$1$2$3'));
    });

    jQuery('#edit-field-org-fax-und-0-value').blur(function (i) {
        //return text.replace(/(\d{3})(\d{3})(\d{4})/, '($1)-$2-$3');
        var text = jQuery(this).val();
        text = text.replace(/-/g, '');
        //jQuery(this).val(text.replace(/(\d{3})(\d{3})(\d{4})/, '($1)-$2-$3'));
		jQuery(this).val(text.replace(/(\d{3})(\d{3})(\d{4})/, '$1$2$3'));
    });

    /*jQuery('#edit-field-phone-und-0-value').blur(function (i) {
        //return text.replace(/(\d{3})(\d{3})(\d{4})/, '($1)-$2-$3');
        var text = jQuery(this).val();
        text = text.replace(/-/g, '');
        jQuery(this).val(text.replace(/(\d{3})(\d{3})(\d{4})/, '($1)-$2-$3'));
    });*/


    jQuery('#edit-field-estimated-cost-und-0-value').keyup(function (i) {
        jQuery(this).val(format(jQuery(this).val())); //alert(text);
    });

    function format2(n, currency) {
        //return currency + " " + n.toFixed(2).replace(/(\d)(?=(\d{3})+\.)/g, "$1,");
        return currency + " " + n.toFixed().replace(/(\d)(?=(\d{3}))/g, "$1,");
        //return currency + " " + n.formatMoney(0,"$");

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
        return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));
    };

    jQuery('.form-type-date-popup .date-padding div:nth-child(1) .date-clear').keyup(function (i) { //alert('jkl');
        if (jQuery(this).val().length == 2) {
            jQuery(this).val(jQuery(this).val() + "/");
        } else if (jQuery(this).val().length == 5) {
            jQuery(this).val(jQuery(this).val() + "/");
        }
    });
    jQuery('.form-type-date-popup .date-padding div:nth-child(1) .date-clear').focus(function (i) {
        jQuery(this).parent().parent().children('.derr').remove();
        jQuery(this).parent().parent().children('.dterr').remove();

    });
    jQuery('.form-type-date-popup .date-padding div:nth-child(1) .date-clear').blur(function (i) { //alert('blur');
        if (jQuery(this).val().length > 1) {
            if (jQuery(this).val().length < 10) {
                jQuery(this).parent().parent().append('<div class="derr" style="color:red">Please enter a valid date format</div>');
            } else if (jQuery(this).val().length == 10) {
                //jQuery(this).parent().parent().children('.derr').html('');	
                jQuery(this).parent().parent().children('.derr').remove();
            } else if (jQuery(this).val().length > 10) {
                jQuery(this).parent().parent().append('<div class="derr" style="color:red">Please enter a valid date format</div>');
            }

            //if($(this).parent().next().length > 1) {	//alert('dfdd');
            if (jQuery(this).parent().next().length) { //alert('dfdd'); 
                if (jQuery(this).parent().next().find('.date-clear').val().length < 1) {
                    jQuery(this).parent().parent().children('.dterr').remove();
                    jQuery(this).parent().parent().append('<div class="dterr" style="color:red">Please enter the time</div>');

                } else {
                    jQuery(this).parent().parent().children('.dterr').remove();
                }
            }
        } else if (jQuery(this).parent().next('.form-item').length) {
            if (jQuery(this).parent().next().find('.date-clear').val().length > 1) {
                jQuery(this).parent().parent().append('<div class="derr" style="color:red">Please enter the date</div>');
            }
        }
    });

    jQuery('.form-type-date-popup .date-padding div:nth-child(1) .date-clear').change(function (i) {  //alert('change');
        if (jQuery(this).val().length > 1) {
            jQuery(this).parent().parent().children('.derr').remove();
        }
        if (jQuery(this).parent().next('.form-item').length) {
            if (jQuery(this).parent().next().find('.date-clear').val().length < 1) {
                if (jQuery(this).val().length > 1) {
                    //jQuery(this).parent().parent().children('.derr').remove();
                    jQuery(this).parent().parent().append('<div class="dterr" style="color:red">Please enter the time</div>');
                }
            } else {
                //jQuery(this).parent().parent().children('.derr').remove();	
                jQuery(this).parent().parent().children('.dterr').remove();
            }
        }
    });

    jQuery('.form-type-date-popup .date-padding div:nth-child(2) .date-clear').blur(function (i) { //alert('op');
        if (jQuery(this).val().length > 1) {
            if (jQuery(this).parent().parent().prev().find('.date-clear').length && jQuery(this).parent().parent().prev().find('.date-clear').val().length < 1) {
                jQuery(this).parent().parent().parent().append('<div class="derr" style="color:red">Please enter the date</div>');
            } else {
                if (jQuery(this).parent().parent().prev().find('.date-clear').length && jQuery(this).parent().parent().prev().find('.date-clear').val().length < 10) {
                    jQuery(this).parent().parent().parent().append('<div class="derr" style="color:red">Please enter a valid date format</div>');
                } else if (jQuery(this).parent().parent().prev().find('.date-clear').length && jQuery(this).parent().parent().prev().find('.date-clear').val().length > 10) {
                    jQuery(this).parent().parent().parent().append('<div class="derr" style="color:red">Please enter a valid date format</div>');
                }
            }
        } else {
            if (jQuery(this).parent().parent().prev().find('.date-clear').length && jQuery(this).parent().parent().prev().find('.date-clear').val().length > 1) {
                jQuery(this).parent().parent().parent().append('<div class="dterr" style="color:red">Please enter the time</div>');

                if (jQuery(this).parent().parent().prev().find('.date-clear').val().length < 10) {
                    jQuery(this).parent().parent().parent().append('<div class="derr" style="color:red">Please enter a valid date format</div>');
                } else if (jQuery(this).parent().parent().prev().find('.date-clear').val().length > 10) {
                    jQuery(this).parent().parent().parent().append('<div class="derr" style="color:red">Please enter a valid date format</div>');
                }
            }
        }
    });

    jQuery('.form-type-date-popup .date-padding div:nth-child(2) .date-clear').focus(function (i) {
        jQuery(this).parent().parent().parent().children('.dterr').remove();
        jQuery(this).parent().parent().parent().children('.derr').remove();
    });

    jQuery('.user-profile-custom-wrapper #edit-privatemsg .fieldset-wrapper').before('<label>Private messages</label>');

    jQuery('.page-user-register .field-name-field-add-new-company label').css('display', 'none');
    jQuery('.page-user-register .field-name-field-add-new-company').css('display', 'none');
    jQuery('.page-user-register .field-name-field-user-company .chosen-search input[type="text"]').focus(function (i) {
        jQuery('.page-user-register .field-name-field-add-new-company').css('display', 'none');
    });
    jQuery('.page-user-register .field-name-field-user-company .chosen-search input[type="text"]').keyup(function (e) { //alert('jkl');
        var value = jQuery(this).val(); //alert(value);
        jQuery('.page-user-register .field-name-field-add-new-company input[type="text"]').val(value);
        if (e.keyCode == 13) { //alert('dsf');
            jQuery(this).blur();
            jQuery('#edit_field_user_company_und_chosen').removeClass('chosen-with-drop');
            jQuery(this).val('');
        }
    });
    jQuery('.page-user-register .field-name-field-user-company .chosen-search input[type="text"]').blur(function (i) {
        if (jQuery(this).val().length > 1) {
            var c = jQuery('#edit_field_user_company_und_chosen ul.chosen-results li').attr('class'); //alert(c);
            if (c == 'no-results') {
                jQuery('.page-user-register .field-name-field-user-company .add-existing-company-field .chosen-single span').text('Add Your Company'); //alert(t);
                jQuery("#edit-field-user-company-und option:selected").each(function () {
                    jQuery(this).removeAttr("selected");
                });
            }
            jQuery('.page-user-register .field-name-field-add-new-company').css('display', 'block');
        }

    });

//    jQuery("#user-login-form .form-submit").click(function (event) {
//        var checked = jQuery(".term-condi-chkbx").is(':checked'); //alert(a);
//        if (!checked) {
//            alert('You need to must check Service Agreement checkbox');
//            event.preventDefault();
//        }
//    });

    /*jQuery('#uc-coupon-form input[name="code"]').blur(function (i) {
     if (jQuery(this).val().length > 1) { //alert('blur');
     jQuery('#uc-coupon-form input[name="uc-coupon-apply"]').click(); 	
     }
     }); */
    jQuery('#uc-cart-view-form input[name="op"]').click(function (i) {
        if (jQuery('#uc-coupon-form input[name="code"]').val().length > 1) { //alert('not empty');
            jQuery('#uc-coupon-form input[name="uc-coupon-apply"]').click();
            return false;
        }
    });



	jQuery(".user-notification-outer .ctools-dropdown-link").click(function(){
    // get the scollTop (distance scrolled from top)
			var scrollTop = $(window).scrollTop();
			// get the top offset of the dropdown (distance from top of the page)
			var topOffset = $(".user-notification-outer .ctools-dropdown").offset().top;
			// calculate the dropdown offset relative to window position
			var relativeOffset = topOffset-scrollTop;
			// get the window height
			//var windowHeight = $(window).height();
			var windowHeight = $('.user-edit-profile-section .dropdown-menu').height();
			// if the relative offset is greater than half the window height,
			// reverse the dropdown.
			//if(relativeOffset > windowHeight/2){
			if(relativeOffset > 250){
					jQuery(".user-notification-outer .ctools-dropdown-container").addClass("reverse-bottom-down");
			}
			else{
					jQuery(".user-notification-outer .ctools-dropdown-container").removeClass("reverse-bottom-down");
			}
	});

    // left panel expanded start    
    //account-tab
    jQuery("#account-tab").click(function(e) { 
        var account_expanded = document.getElementById("account-tab").getAttribute("aria-expanded");      
        if(account_expanded == 'false'){
          localStorage.setItem("account-tab", "in");               
        }else if(account_expanded == 'true'){
          localStorage.removeItem("account-tab");          
        }
    });
    var account_tab = localStorage.getItem("account-tab");    
    if(account_tab == 'in'){
        jQuery('#account-tab').attr("aria-expanded", "true");
        jQuery('#left_content_data_fifth').addClass("in");
    }else if(account_tab == null){
        jQuery('#account-tab').attr("aria-expanded", "false");
        jQuery('#left_content_data_fifth').removeClass("in");
    }
    //services-tab
    jQuery("#services-tab").click(function(e) {   
        var services_expanded = document.getElementById("services-tab").getAttribute("aria-expanded");      
        if(services_expanded == 'false'){
          localStorage.setItem("services-tab", "in");             
        }else if(services_expanded == 'true'){
          localStorage.removeItem("services-tab");            
        }
    });
    var services_tab = localStorage.getItem("services-tab");
    if(services_tab == 'in'){
        jQuery('#services-tab').attr("aria-expanded", "true");
        jQuery('#left_content_data_one').addClass("in");
    }else if(services_tab == null){
        jQuery('#services-tab').attr("aria-expanded", "false");
        jQuery('#left_content_data_one').removeClass("in");
    }
	// connection tab
	jQuery("#connection-tab").click(function(e) {	
	    var connection_expanded = document.getElementById("connection-tab").getAttribute("aria-expanded");		
		if(connection_expanded == 'false'){
		  localStorage.setItem("connection-tab", "in");				
		}else if(connection_expanded == 'true'){
		  localStorage.removeItem("connection-tab");			
		}
    });
	var connection_tab = localStorage.getItem("connection-tab");
	if(connection_tab == 'in'){
        jQuery('#connection-tab').attr("aria-expanded", "true");
		jQuery('#left_content_data_two').addClass("in");
	}else{
        jQuery('#connection-tab').attr("aria-expanded", "false");
		jQuery('#left_content_data_two').removeClass("in");
	}
    //favorite tab
    jQuery("#favorite-tab").click(function(e) {   
        var favorite_expanded = document.getElementById("favorite-tab").getAttribute("aria-expanded");        
        if(favorite_expanded == 'false'){
          localStorage.setItem("favorite-tab", "in");             
        }else if(favorite_expanded == 'true'){
          localStorage.removeItem("favorite-tab");            
        }
    });
    var favorite_tab = localStorage.getItem("favorite-tab");
    if(favorite_tab == 'in'){
        jQuery('#favorite-tab').attr("aria-expanded", "true");
        jQuery('#left_content_data_three').addClass("in");
    }else{
        jQuery('#favorite-tab').attr("aria-expanded", "false");
        jQuery('#left_content_data_three').removeClass("in");
    }
    //bookmark tab
    jQuery("#bookmark-tab").click(function(e) {   
        var bookmark_expanded = document.getElementById("bookmark-tab").getAttribute("aria-expanded");        
        if(bookmark_expanded == 'false'){
          localStorage.setItem("bookmark-tab", "in");             
        }else if(bookmark_expanded == 'true'){
          localStorage.removeItem("bookmark-tab");            
        }        
    });
    var bookmark_tab = localStorage.getItem("bookmark-tab");    
    if(bookmark_tab == 'in'){
        jQuery('#bookmark-tab').attr("aria-expanded", "true");
        jQuery('#left_content_data_four').addClass("in");
    }else{
        jQuery('#bookmark-tab').attr("aria-expanded", "false");
        jQuery('#left_content_data_four').removeClass("in");
    }
	//left panel expanded end 
	
	//profile edit page
	if(jQuery('body').hasClass('page-user-edit')){
	  //var profile_edit_tab = '';	
	  var profile_edit_tab = localStorage.getItem("profile-edit-tab");
	  if(profile_edit_tab == ''){
		localStorage.setItem("profile-edit-tab", "user_profile_edit");  
	  }
	  jQuery(".profile-profile-tab").click(function(e) {
		localStorage.setItem("profile-edit-tab", "user_profile_edit");
	  });
	  jQuery(".profile-m6id-tab").click(function(e) {
		localStorage.setItem("profile-edit-tab", "user_member_m6id");
	  });
	  jQuery(".profile-member-tab").click(function(e) {
		localStorage.setItem("profile-edit-tab", "user_member_status");
	  });
	  jQuery(".profile-companies-tab").click(function(e) {
		localStorage.setItem("profile-edit-tab", "user_delegate_access");
	  });	
	  
	  if(profile_edit_tab){
		 jq1113('#user-profiles-edit-tab a[href="#'+profile_edit_tab+'"]').tab('show');
	  }
	    
	}
	else {
      localStorage.removeItem("profile-edit-tab");
	}
  
  
  //check-user-availability
  var continueSignup = sessionStorage.getItem('continueSignup');
  
 
	
  if (jQuery("body").hasClass('page-user-register') && !(jQuery("body").hasClass('continueYesLink'))){
	
	//var continueSignup = 1;
	
	jQuery('.form-item-field-first-name-und-0-value input').change(function (e) { 
	  getUfname = 'none';
	  getUlname = 'none';
	  getUdob = 'none';
	  getUgender = 'none';
	  getUphone = 'none';	
	  var DobMonth = jQuery('.form-item-field-date-of-birth-und-0-value-month .date-month :selected').val();
	  var DobDay = jQuery('.form-item-field-date-of-birth-und-0-value-day .date-day :selected').val();
	  var DobYear = jQuery('.form-item-field-date-of-birth-und-0-value-year .date-year :selected').val();	
	  var getUfname = jQuery('.form-item-field-first-name-und-0-value input').val();	
	  var getUlname = jQuery('.form-item-field-last-name-und-0-value input').val();	
	  var getUgender = jQuery('.form-item-field-gender-und input[name="field_gender[und]"]:checked').val();
	  var getUphone = jQuery('.form-item-field-phone-und-0-value input').val();		  
	  var getUphoneArr = getUphone .split('+');
	  
	  if(getUfname == '') {
	    getUfname = 'none';
	  }	
	  if(getUlname == '') {
	    getUlname = 'none';
	  }
	  if(parseInt(DobMonth) && parseInt(DobDay) && parseInt(DobYear)){
//		  1986-05-06 00:00:00
		getUdob = DobYear +'-'+ DobMonth + '-'+ DobDay +' 00:00:00';
	  }else{
		getUdob = 'none';
	  }
	  if(!getUgender){
		getUgender ='none';	
	  }
	  if(getUphoneArr && getUphone && getUphone > 9 ){
		getUphone = getUphoneArr[1];
	  }else{
		getUphone ='none';
	  }
	  if(continueSignup != 'Yes'){
		jQuery.post( '/check-user-availability/'+ getUfname +'/'+ getUlname +'/'+ getUdob +'/'+ getUgender +'/'+ getUphone, function( data ) {
		  //alert(data.dataHtml);	    
		  if(data.dataHtml != '0'){
			jQuery('#avaiblity-continer-dialog').html(data.dataHtml);
			Drupal.attachBehaviors(jQuery('body'));
			jQuery('#avaiblity-continer-dialog').dialog('open');
		  }
		});
	  }
	});
	jQuery('.form-item-field-last-name-und-0-value input').change(function (e) { 
	  getUfname = 'none';
	  getUlname = 'none';
	  getUdob = 'none';
	  getUgender = 'none';
	  getUphone = 'none';	
	  var DobMonth = jQuery('.form-item-field-date-of-birth-und-0-value-month .date-month :selected').val();
	  var DobDay = jQuery('.form-item-field-date-of-birth-und-0-value-day .date-day :selected').val();
	  var DobYear = jQuery('.form-item-field-date-of-birth-und-0-value-year .date-year :selected').val();	
	  var getUfname = jQuery('.form-item-field-first-name-und-0-value input').val();	
	  var getUlname = jQuery('.form-item-field-last-name-und-0-value input').val();	
	  var getUgender = jQuery('.form-item-field-gender-und input[name="field_gender[und]"]:checked').val();
	  var getUphone = jQuery('.form-item-field-phone-und-0-value input').val();	
	  var getUphoneArr = getUphone .split('+');
	  if(getUfname == '') {
	    getUfname = 'none';
	  }
	  if(getUlname == '') {
	    getUlname = 'none';
	  }	
	  if(parseInt(DobMonth) && parseInt(DobDay) && parseInt(DobYear)){
		getUdob = DobYear +'-'+ DobMonth + '-'+ DobDay +' 00:00:00';
	  }else{
		getUdob = 'none';
	  }
	  if(!getUgender){
		getUgender ='none';	
	  }
	  if(getUphoneArr && getUphone && getUphone > 9 ){
		getUphone = getUphoneArr[1];
	  }else{
		getUphone ='none';
	  }	
	  if(continueSignup != 'Yes'){
		jQuery.post( '/check-user-availability/'+ getUfname +'/'+ getUlname +'/'+ getUdob +'/'+ getUgender +'/'+ getUphone, function( data ) {
			//alert(data.dataHtml);
		  if(data.dataHtml != '0'){
			jQuery('#avaiblity-continer-dialog').html(data.dataHtml);
			Drupal.attachBehaviors(jQuery('body'));
			jQuery('#avaiblity-continer-dialog').dialog('open');
		  }	    
		});
	  }
	});
	jQuery('.form-item-field-date-of-birth-und-0-value').change(function (e) { 
	  getUfname = 'none';
	  getUlname = 'none';
	  getUdob = 'none';
	  getUgender = 'none';
	  getUphone = 'none';	
	  var DobMonth = jQuery('.form-item-field-date-of-birth-und-0-value-month .date-month :selected').val();
	  var DobDay = jQuery('.form-item-field-date-of-birth-und-0-value-day .date-day :selected').val();
	  var DobYear = jQuery('.form-item-field-date-of-birth-und-0-value-year .date-year :selected').val();	
	  var getUfname = jQuery('.form-item-field-first-name-und-0-value input').val();	
	  var getUlname = jQuery('.form-item-field-last-name-und-0-value input').val();	
	  var getUgender = jQuery('.form-item-field-gender-und input[name="field_gender[und]"]:checked').val();
	  var getUphone = jQuery('.form-item-field-phone-und-0-value input').val();	
	  var getUphoneArr = getUphone .split('+');
	  if(getUfname == '') {
	    getUfname = 'none';
	  }
	  if(getUlname == '') {
	    getUlname = 'none';
	  }	
	  if(parseInt(DobMonth) && parseInt(DobDay) && parseInt(DobYear)){
		getUdob = DobYear +'-'+ DobMonth + '-'+ DobDay +' 00:00:00';
	  }else{
		getUdob = 'none';
	  }
	  if(!getUgender){
		getUgender ='none';	
	  }
	  if(getUphoneArr && getUphone && getUphone > 9 ){
		getUphone = getUphoneArr[1];
	  }else{
		getUphone ='none';
	  }	
	  jQuery.post( '/check-user-availability/'+ getUfname +'/'+ getUlname +'/'+ getUdob +'/'+ getUgender +'/'+ getUphone, function( data ) {
		  //alert(data.dataHtml);
		if(data.dataHtml != 0){
	      jQuery('#avaiblity-continer-dialog').html(data.dataHtml);
		  Drupal.attachBehaviors(jQuery('body'));
          jQuery('#avaiblity-continer-dialog').dialog('open');
		}
	  });
	});
	jQuery('.form-item-field-gender-und .form-radios input').unbind('click').bind('click',function(e) { 
	  getUfname = 'none';
	  getUlname = 'none';
	  getUdob = 'none';
	  getUgender = 'none';
	  getUphone = 'none';	
	  var DobMonth = jQuery('.form-item-field-date-of-birth-und-0-value-month .date-month :selected').val();
	  var DobDay = jQuery('.form-item-field-date-of-birth-und-0-value-day .date-day :selected').val();
	  var DobYear = jQuery('.form-item-field-date-of-birth-und-0-value-year .date-year :selected').val();	
	  var getUfname = jQuery('.form-item-field-first-name-und-0-value input').val();	
	  var getUlname = jQuery('.form-item-field-last-name-und-0-value input').val();	
	  var getUgender = jQuery('.form-item-field-gender-und input[name="field_gender[und]"]:checked').val();
	  var getUphone = jQuery('.form-item-field-phone-und-0-value input').val();
	  var getUphoneArr = getUphone .split('+');
	  if(getUfname == '') {
	    getUfname = 'none';
	  }
	  if(getUlname == '') {
	    getUlname = 'none';
	  }	
	  if(parseInt(DobMonth) && parseInt(DobDay) && parseInt(DobYear)){
		getUdob = DobYear +'-'+ DobMonth + '-'+ DobDay +' 00:00:00';
	  }else{
		getUdob = 'none';
	  }
	  if(!getUgender){
		getUgender ='none';	
	  }
	  if(getUphoneArr && getUphone && getUphone > 9 ){
		getUphone = getUphoneArr[1];
	  }else{
		getUphone ='none';
	  }	
	  if(continueSignup != 'Yes'){
		jQuery.post( '/check-user-availability/'+ getUfname +'/'+ getUlname +'/'+ getUdob +'/'+ getUgender +'/'+ getUphone, function( data ) {	
		//alert(data.dataHtml);
		  if(data.dataHtml != 0){
			jQuery('#avaiblity-continer-dialog').html(data.dataHtml);
			Drupal.attachBehaviors(jQuery('body'));
			jQuery('#avaiblity-continer-dialog').dialog('open');
		  }    
		});
	  }
	});
	jQuery('.form-item-field-phone-und-0-value input').change(function (e) { 
	  getUfname = 'none';
	  getUlname = 'none';
	  getUdob = 'none';
	  getUgender = 'none';
	  getUphone = 'none';	
	  var DobMonth = jQuery('.form-item-field-date-of-birth-und-0-value-month .date-month :selected').val();
	  var DobDay = jQuery('.form-item-field-date-of-birth-und-0-value-day .date-day :selected').val();
	  var DobYear = jQuery('.form-item-field-date-of-birth-und-0-value-year .date-year :selected').val();	
	  var getUfname = jQuery('.form-item-field-first-name-und-0-value input').val();	
	  var getUlname = jQuery('.form-item-field-last-name-und-0-value input').val();	
	  var getUgender = jQuery('.form-item-field-gender-und input[name="field_gender[und]"]:checked').val();
	  var getUphone = jQuery('.form-item-field-phone-und-0-value input').val();	
      var getUphoneArr = getUphone .split('+');
	  if(getUfname == '') {
	    getUfname = 'none';
	  }	
	  if(getUlname == '') {
	    getUlname = 'none';
	  }	
	  if(parseInt(DobMonth) && parseInt(DobDay) && parseInt(DobYear)){
		getUdob = DobYear +'-'+ DobMonth + '-'+ DobDay +' 00:00:00';
	  }else{
		getUdob = 'none';
	  }
	  if(!getUgender){
		getUgender ='none';	
	  }
	  if(getUphoneArr && getUphone && getUphone > 9 ){
		getUphone = getUphoneArr[1];
	  }else{
		getUphone ='none';
	  }	
	  if(continueSignup != 'Yes'){
		jQuery.post( '/check-user-availability/'+ getUfname +'/'+ getUlname +'/'+ getUdob +'/'+ getUgender +'/'+ getUphone, function( data ) {
			//alert(data.dataHtml);
		  if(data.dataHtml != 0){
			jQuery('#avaiblity-continer-dialog').html(data.dataHtml);
			Drupal.attachBehaviors(jQuery('body'));
			jQuery('#avaiblity-continer-dialog').dialog('open');
		  }	    
		});
	  }
	});   
  }
 

/*  jQuery('span.continueYesLink').click(function(){
		  sessionStorage.setItem('continueSignup', 'Yes');
		  console.log('yes2');
  })*/
  if (jQuery("body").hasClass('page-user-register') && !(jQuery("body").hasClass('continueYesLink'))){
  jQuery('#avaiblity-continer-dialog').dialog({
    autoOpen: false,
    width: 490,
    modal: true,
    resizable: false,
    buttons: {
      'Continue with new signup': function () {    
        jQuery(this).dialog("close");        
		 //jQuery('.ui-dialog-buttonpane').find('span:contains("Continue with new signup")').addClass('continueYesLink');
		 //jQuery('.ui-dialog-buttonpane').find('.ui-button-text').addClass('continueYesLink');
		 jQuery("body").addClass('continueYesLink');
		  sessionStorage.setItem('continueSignup', 'Yes');
		  console.log('yes');
		  jQuery('#avaiblity-continer-dialog').removeClass('check-user-availabil');
		  jQuery("body").remove('#avaiblity-continer-dialog');
		  document.getElementById("avaiblity-continer-dialog").remove();
      },
    },
    open: function () {
      jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
      jQuery('.ui-dialog-titlebar').hide();
    }
  });
  }
    
    
    /*jQuery(window).on('beforeunload', function(){
      return 'Are you sure you want to leave?';
    });*/  
});

function company_join_accept_pending_request(uid, id, companyNid) {
 	var url1 = "/notification/people/join/accept/"+uid+"/"+id+"/"+companyNid;
	jQuery.ajax({
			type: 'post',
			url: url1,
			success: function (msg) {
				if(msg == 'done'){
					jQuery('.notification-'+id).remove();
				}
			}
	});

}



function accept_pending_request(uid, name, companynid) {
    var url = "/people/invite/accept/"+uid+"/"+companynid;
	
	//alert(url);
    jQuery.post(url, function (data) {
        jQuery('#user-full-name-success').html(name);
       jQuery('#user-roll-success').html(data);
        jQuery("#dialog-message").dialog({
            modal: true,
            resizable: false,
            width: 400,
            buttons: {
                Ok: function () {
                    jQuery.post('/people/invite/acceptapprove/' + uid +'/' + companynid);
                    //console.log(uid);
                    //console.log(companynid);
                    
                    jQuery(this).dialog("close");
                    window.location.href = window.location.href;
                }
            }
        });
        jQuery('.ui-dialog-titlebar').hide();
    });
	

}
function deny_pending_request(uid, name, companynid) {
    jQuery('#user-full-name').html(name);
    jQuery("#dialog-confirm-dney").dialog({
        resizable: false,
        height: 300,
        modal: true,
        buttons: {
            "Confirm": function () {
                var url = "/people/invite/deny/"+uid+"/"+companynid;
                jQuery.post(url, function (data) {
                    window.location.href = window.location.href;
                });
                jQuery(this).dialog("close");
            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();

}

function manage_user_roles(uid, name, existingroles, companynid) {
    // make all checkboxes unchecked first
    jQuery('#assignroletomembers input:checkbox').removeAttr('checked');
    var roles = existingroles.split(',');
    var len = roles.length;
    var lds = '';
    for (var i = 0; i < len; i++) {
        ids = '#newroles_' + roles[i].trim();
        jQuery(ids).attr('checked', 'checked');
    }
    // if first checked then remove checked from second
    jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(0).click(function(){
        jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(1).removeAttr('checked');
    });
    // if second checked then remove checked from first
    jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(1).click(function(){
        jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(0).removeAttr('checked');
    });

    jQuery('#member-full-name').html(name);
    jQuery("#role-asign-form").dialog({
        resizable: false,
        height: 600,
        width: 600,
        modal: true,
        buttons: {
            "Save": function () {
                var url = "/people/invite/role/"+uid+"/"+companynid;
                var dilog = this;
                jQuery.post(url, jQuery('#assignroletomembers').serialize(), function (data) {
                    jQuery(dilog).dialog("close");
                    window.location.href = window.location.href;
                });

            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();
}
function manage_permission(uid) {

}
function remove_user(uid, name, companynid) {
    jQuery.post( '/get-company-admin/'+ companynid, function( data ) { 
	  jQuery('.company-admin-cust-class').empty();
       jQuery.each(data,function(key, value) {
       var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.company-admin-cust-class');
     });
     jQuery(".company-admin-cust-class").prepend("<option value selected='selected'>- None -</option>");
	});
    jQuery('#user-full-name').html(name);
	jQuery('#user-full-name-sel').html(name);	
    jQuery("#dialog-confirm-remove").dialog({
        resizable: false,
        //height: 300,
		width:490,
        modal: true,
        buttons: {
            "Confirm": function () {
				var companyAdmin = jQuery('.company-admin-cust-class').val();
                //var url = "/people/invite/remove/"+uid+"/"+companynid;		
				var url = "/companyr/user/remove/"+uid+"/"+companynid+"/"+companyAdmin;						
                jQuery.post(url, function(data) {	
                  window.location.reload();	
                });
                jQuery(this).dialog("close");
            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();
}
function company_admin_support_role(uid, name, companynid){

	/* var url = "/assign/companyadminrole/"+uid+"/"+companynid;
	  jQuery.post(url, function(data) {	
		//window.location.reload();	
	 });*/
	 /*var url1 = "/assign/companyadminrole/"+uid+"/"+companynid;
	 var param = {};		 
	  param['uid'] = uid; 
	  param['uid'] = companynid;   
	  jQuery.ajax({
				url:url1,
				type:'POST',
				data:param,
			    success:function(result){ 
				//alert(url);
				//jQuery('.company-admin-support').html(result); 	
			     }
				 
      });*/
	  
	  jQuery.post("/assign/companyadminrole/"+uid+"/"+companynid).done(function( data ) {
        jQuery('div.cust-people-box').each(function(index, element) {
          var useruid = jQuery(this).data('useruid');
		  var userroles = jQuery(this).find('.cust-people-user-roles').html();
		  var roleArr = userroles.split(', ');
		  var position = roleArr.indexOf('Company Admin Support');
		  if(position!=-1 && useruid!=uid) {
		    roleArr.splice(position, 1);
			userroles = roleArr.join(', ');
			jQuery(this).find('.cust-people-user-roles').html(userroles);
		  }
		  if(position==-1 && useruid==uid){
			roleArr.push('Company Admin Support');
			userroles = roleArr.join(', ');
			jQuery(this).find('.cust-people-user-roles').html(userroles);
		  }
        });
      });
		
               
	
}
///////// new code /////////////
function remove_user1(uid, name, companynid) {

    jQuery('#user-full-name').html(name);
    jQuery("#dialog-confirm-remove").dialog({
        resizable: false,
        height: 300,
        modal: true,
        buttons: {
            "Confirm": function () {
                var url = "/people1/invite/remove/"+uid+"/"+companynid;
				// alert(url);
                jQuery.post(url, function(data) {	
                  window.location.reload();	
                });
                jQuery(this).dialog("close");
            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();
}

function manage_user_roles1(uid, name, existingroles, companynid) {
    // make all checkboxes unchecked first
    jQuery('#assignroletomembers input:checkbox').removeAttr('checked');
    var roles = existingroles.split(',');
    var len = roles.length;
    var lds = '';
    for (var i = 0; i < len; i++) {
        ids = '#newroles_' + roles[i].trim();
        jQuery(ids).attr('checked', 'checked');
    }
    // if first checked then remove checked from second
    jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(0).click(function(){
        jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(1).removeAttr('checked');
    });
    // if second checked then remove checked from first
    jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(1).click(function(){
        jQuery('#assignroletomembers').find('input[type="checkbox"]').eq(0).removeAttr('checked');
    });

    jQuery('#member-full-name').html(name);
    jQuery("#role-asign-form").dialog({
        resizable: false,
        height: 600,
        width: 600,
        modal: true,
        buttons: {
            "Save": function () {
                var url = "/people1/invite/role/"+uid+"/"+companynid;
				//alert(url);
                var dilog = this;
                jQuery.post(url, jQuery('#assignroletomembers').serialize(), function (data) {
                    jQuery(dilog).dialog("close");
                    window.location.href = window.location.href;
                });

            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();
}
///// accept pending request /////////////
function accept_pending_request1(uid, name, companynid) {
    var url = "/people1/invite/accept/"+uid+"/"+companynid;
	
	//alert(url);
    jQuery.post(url, function (data) {
        jQuery('#user-full-name-success').html(name);
       jQuery('#user-roll-success').html(data);
        jQuery("#dialog-message").dialog({
            modal: true,
            resizable: false,
            width: 400,
            buttons: {
                Ok: function () {
                    jQuery(this).dialog("close");
                    window.location.href = window.location.href;
                }
            }
        });
        jQuery('.ui-dialog-titlebar').hide();
    });
}
///// accept pending request /////////////
function deny_pending_request1(uid, name, companynid) {
    jQuery('#user-full-name').html(name);
    jQuery("#dialog-confirm-dney").dialog({
        resizable: false,
        height: 300,
        modal: true,
        buttons: {
            "Confirm": function () {
                var url = "/people1/invite/deny/"+uid+"/"+companynid;
                jQuery.post(url, function (data) {
                    window.location.href = window.location.href;
                });
                jQuery(this).dialog("close");
            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();

}

///// end new code /////////////
function assignrole() {

}
function forword_rfp(id) {

    jQuery("#dialog-confirm-remove").dialog({
        resizable: false,
        height: 300,
        modal: true,
        buttons: {
            "Confirm": function () {
                var url = "/rfp/forward/" + id;
                if (jQuery('#title_rfp').val().trim() == '') {
                    jQuery('#title_rfp').css('border', '1px solid red');
                    return false;
                }
                if (jQuery('#title_rfp').val().trim() == jQuery('#old_title').val().trim()) {
                    jQuery('#title_rfp').css('border', '1px solid red');
                    jQuery('#title_rfp').attr('title', 'Name Should not be same as old RFP');
                    return false;
                }
                jQuery.post(url, jQuery("#rfp_forward_form").serialize(), function (data) {
                    window.location.href = data;

                });
                jQuery(this).dialog("close");
            },
            Cancel: function () {
                jQuery(this).dialog("close");
            }
        }
    });
    jQuery('.ui-dialog-titlebar').hide();
}
function add_lincese() {
    alert("testing");
}


Drupal.behaviors.m6connect_misc = {
    attach: function () {
          var addcom_diver_cred =  jQuery('select.addcom_diversity_credentials').val();
          if(!addcom_diver_cred){    
            jQuery(".form-group .custwrapcrd, .dneedscustwrapcrd").css('display', 'none'); 
          }
		//user check avability
		jQuery('.user-availabil-link').click(function(){
		  jQuery('#avaiblity-continer-dialog').dialog('close');	
		  var UserEmail = $(this).attr("data-email");
		  console.log(UserEmail);
		  sessionStorage.setItem('avauser', UserEmail);
		});
		if(sessionStorage.getItem('avauser') && sessionStorage.getItem('avauser') != null){
		  var avauser = sessionStorage.getItem('avauser');
		  jQuery('.user-login-form .form-item-name input.user-login-field').val(avauser);
		}
		/*jQuery('span.continueYesLink').click(function(){
		  sessionStorage.setItem('continueSignup', 'Yes');
		  console.log('yes');
		});*/
		
		
		//user pass reset auto populate email (start
		var hasUserLogin = jQuery('body').find('.user-login-form');		
		var userpassreset = localStorage.getItem("user-passreset-mail");
		if(hasUserLogin){
		  jQuery("input.user-login-field").blur(function (event) {
			var UserLoginValue = jQuery('input.user-login-field').val();	
			var atpos = UserLoginValue.indexOf("@");
			var dotpos = UserLoginValue.lastIndexOf(".");
			if (!(atpos<1 || dotpos<atpos+2 || dotpos+2>=UserLoginValue.length)) {
			  localStorage.setItem("user-passreset-mail", UserLoginValue);			   	          
			}
		  });
		}		
		if(userpassreset){
		  jQuery('input.user-pass-reset-field').val(userpassreset);
		  localStorage.removeItem("user-passreset-mail");	
		}
		//user pass reset auto populate email (end
		
        //var output;  
        jQuery('.org-ungrp-link').click(function (event) {
            /*var gid = jQuery(this).find('.org-unsub-nid').text();
            var title = jQuery(this).find('.org-unsub-title').text();*/
			var gid = jQuery(this).data('nid');
            var title = jQuery(this).data('title');
            var url = "/m6connect/unsubscribe/" + gid;
            jQuery.ajax({
                type: 'post',
                url: '/m6connect/unsubscribe/' + gid,
                data: 'gid=' + encodeURI(gid),
                success: function (msg) { //alert(msg); 
                    $html = '';
                    if (msg == '1') {
                        //$html = '<div class="text-center"><div class="dialog-heading"><strong>Unsubscribe</strong></div><div class="dialog-description">'+a+'</div>';
                        $html = "<div class='text-center'><div class='dialog-description'>You are the only member of " + title + ". Press Continue to disable this Company's account. Press Cancel to keep the Company active.</div><span class='data-comp-id' style='display:none;'>" + gid + "</span></div>";
                        jQuery('#org-unsubscribe-dialog1').html($html);
                        jQuery('#org-unsubscribe-dialog1').dialog("open");
                    } else if (msg == '2') {
                        $html = "<div class='text-center'><div class='dialog-description'>" + title + " must have at least one Administrator. Please assign another member to be Administrator before leaving the Company.</div>";
                        jQuery('#org-unsubscribe-dialog2').html($html);
                        jQuery('#org-unsubscribe-dialog2').dialog("open");
                    } else if (msg == '3') {
                        $html = "<div class='text-center'><div class='dialog-description'>Are you sure you want to leave the " + title + ". Press Yes to leave the Company. Press No to Stay in the Company.</div><span class='data-comp-id' style='display:none;'>" + gid + "</span></div>";
                        jQuery('#org-unsubscribe-dialog3').html($html);
                        jQuery('#org-unsubscribe-dialog3').dialog("open");
                    } else if (msg == '4') {
                        jQuery('#org-unsubscribe-dialog4').dialog("open");
                    }


                }
            });
            //console.log(output);
            //var a =jQuery(this).find('.org-unsub-title').text();//alert(a); 
            //jQuery('.ui-dialog-titlebar').hide();

            //return false;	
        });
if(Drupal.settings.is_loggedin_user){
        jQuery("#org-unsubscribe-dialog1").dialog({
            autoOpen: false,
            width: 500,
            modal: true,
            resizable: false,
            buttons: {
                "Continue": function () {
                    jQuery(this).dialog("close");
                    var gid = jQuery(this).find('span.data-comp-id').text();
                    var url = "/m6group/unsubscribe/" + gid;
                    jQuery.ajax({
                        type: 'post',
                        url: '/m6group/unsubscribe/' + gid,
                        data: 'gid=' + encodeURI(gid),
                        success: function (msg) {
                        }
                    });


                    //return false;
                },
                "Cancel": function () {
                    jQuery(this).dialog("close");
                    return false;
                }

            }

        });

        jQuery("#org-unsubscribe-dialog2").dialog({
            autoOpen: false,
            width: 500,
            modal: true,
            resizable: false,
            buttons: {
                "Ok": function () {
                    jQuery(this).dialog("close");
                    return false;
                },
            }
        });
        jQuery("#org-unsubscribe-dialog3").dialog({
            autoOpen: false,
            width: 500,
            modal: true,
            resizable: false,
            buttons: {
                "Yes": function () {
                    var gid = jQuery(this).find('span.data-comp-id').text();
                    var url = "/m6group/unsubscribe/" + gid;
                    jQuery.ajax({
                        type: 'post',
                        url: '/m6group/unsubscribe/' + gid,
                        data: 'gid=' + encodeURI(gid),
                        success: function (msg) {
                        }
                    });
                    jQuery(this).dialog("close");
                    //return false;
                },
                "No": function () {
                    jQuery(this).dialog("close");
                    return false;
                }

            }

        });
        jQuery("#org-unsubscribe-dialog4").dialog({
            autoOpen: false,
            width: 500,
            modal: true,
            resizable: false,
            buttons: {
                "Continue": function () {
                    jQuery(this).dialog("close");
                    return false;
                },
                "Cancel": function () {
                    jQuery(this).dialog("close");
                    return false;
                }

            }

        });

        jQuery('.ui-dialog-titlebar').hide();
		
}
    
    }
}

