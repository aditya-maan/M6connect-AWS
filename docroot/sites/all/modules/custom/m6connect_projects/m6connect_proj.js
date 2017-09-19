jQuery(document).ready(function ($) {
<!--prochat section start -->
	Drupal.ajax.prototype.commands.insertInEmoji = function(ajax, data, status) {
	  var textareaInstance = jQuery(data.selector).attr('id');
	  var mappingKeyValue = textareaInstance.split('text-message-smilly-');
	  var mappingKey = mappingKeyValue[1];
	  //console.log(mappingKey);
	  jQuery(data.selector).emojioneArea({
		 container: ".message-abc-cont-"+mappingKey,
		 hideSource: true,
		 useSprite: false,
		 saveEmojisAs: "image",
		 imageType: "png",
		 shortnames: false,
	  });
	};

	
	jQuery('.prochat_file_attachedform').on('change','input.prochat-file-upload-section-2',function(e){
	  
	  var uploadMaxSize = (20*1024*1024); //in Bytes (2 MB)
	  var attachment = jQuery(this);
	  var attachmentProperty = attachment.prop('files');
	  //console.log(attachmentProperty);
	  //var ext = attachmentProperty.name.split('.').pop().toLowerCase();
	  //console.log(attachmentProperty);
	  //console.log(ext);
	  var errorcount =0;
	  jQuery.each( attachmentProperty, function( key, value ) {
        //console.log(value);
        var ext = value.name.split('.').pop().toLowerCase();
		/*if(jQuery.inArray(ext, ['txt', 'pdf', 'jpg', 'jpeg', 'doc', 'docx', 'rtf', 'xls', 'xlsx', 'gif', 'bmp', 'png']) === -1) {
		  //alert('invalid extension!');
		  jQuery('.chat-action-box-error').html('<span class="change-action-box-error form-item">invalid extension!(Please use "txt pdf jpg jpeg doc docx rtf xls xlsx gif bmp png") </span>');
		  attachment.val('');
		  errorcount++;
		}*/
		if (value.size > uploadMaxSize) {
		  //alert("Large file");
		  jQuery('.chat-action-box-error').html('<span class="change-action-box-error form-item">Large file (File could not exceed 20 MB )</span>');
		  attachment.val('');
		  errorcount++;
		}
	  });
	  if(errorcount===0){
	   //jQuery('.user_messaging_thread_form').find('input[name="attachment-fid_upload_button"]').trigger('mousedown');
	   jQuery('.chat-action-box-error').html('');
	   jQuery(this).parent().find('input.prochat_file_upload_btn').trigger('click');
	  }	  
	});
	//multiple file upload in prochat end
	
	
/*	jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
	  var urlajax = ajaxOptions.url;
	  if((urlajax.indexOf("/file/ajax/attachment-section/prochat_file_upload_section")===0) && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData.hasOwnProperty("_triggering_element_value") && ajaxOptions.extraData._triggering_element_value==="Upload"){
		var lente = jQuery(".prochat-file-upload-section .file");
		if(lente.length >0) {
		  jQuery(".prochat_file_upload_btn").trigger("click");
		}
	  }
	});*/
	/*jQuery('#pd-message-containersection').find('div.emojionearea-upbutton').unbind('click').bind('click',function(e) {
      jQuery('.prochat_file_attachedform').find("input[name='files[prochat_file_upload_section]']").trigger('click'); 
    });*/
    jQuery('#pd-message-containersection').on('click','div.emojionearea-upbutton',function(e) {
      //jQuery('.prochat-file-upload-section .form-file').trigger('click'); 
    });
	
/*	jQuery('.prochat_file_attachedform').on('change','.prochat-file-upload-section input.form-file',function(e){ 
	   var uploadMaxSize = (2*1024*1024); //in Bytes (2 MB)
	   var attachment = jQuery(this);
	   var attachmentProperty = attachment.prop('files')[0];
	   var ext = attachmentProperty.name.split('.').pop().toLowerCase();
	   var errorcount =0;
		  if(jQuery.inArray(ext, ['txt', 'pdf', 'jpg', 'jpeg', 'doc', 'docx', 'rtf', 'xls', 'xlsx', 'gif', 'bmp', 'png']) === -1) {
			//alert('invalid extension!');
			jQuery('.chat-action-box-error').html('<span class="change-action-box-error form-item">invalid extension!</span>');
			attachment.val('');
			errorcount++;
		  }
		  if (attachmentProperty.size > uploadMaxSize) {
			//alert("Large file");
			jQuery('.chat-action-box-error').html('<span class="change-action-box-error form-item">Large file</span>');
			attachment.val('');
			errorcount++;
		  }
	   if(errorcount===0){
		 //jQuery('.user_messaging_thread_form').find('input[name="attachment-fid_upload_button"]').trigger('mousedown');
		 jQuery('.chat-action-box-error').html('');
		 jQuery(this).parent().find('input.form-submit').mousedown();
	   }	  
      
    });*/
/*	jQuery('.pd-message-chat-container').on('keypress','div.emojionearea.text-message-smilly .emojionearea-editor',function (e) {
	  var keycode = (event.keyCode ? event.keyCode : event.which);
	  var mappingKey = jQuery('.pd-message-chat-container').attr('id');
	  if(keycode == 13 && !e.shiftKey){
		jQuery('textarea#text-message-smilly-'+mappingKey).val(jQuery(this).html());	  
		jQuery("input.project_dashboard_chat_send_"+mappingKey).trigger("click");		 
	  }		  
	});*/
	  jQuery('.pd-message-chat-container').find('div.emojionearea-upbutton').unbind('click');
	  jQuery('.pd-message-chat-container').on('click','div.emojionearea-upbutton',function(e) {
		var textareaInstanceparent = jQuery(this).closest('div.emojionearea.text-message-smilly').parent('div').attr('class');
		var mappingKeyValue = textareaInstanceparent.split('message-abc-cont-');
		var mappingKey = mappingKeyValue[1];
		jQuery('form#prochat-file-attached-form-'+mappingKey+' input.prochat-file-upload-section-2').trigger('click'); 
	  });
  jQuery('input.group_admin_assign_option').on('change', function() {
    jQuery('input.group_admin_assign_option').not(this).prop('checked', false);
  });
<!--prochat section end -->	
	
    jQuery('#project-list-search-button').click(function (e) {
        var searchval = jQuery('.pro_search_custom').val();
        jQuery('.form-item-pro-search input').val(searchval);
        jQuery('#cust-project-search-form .proj-submit').click();
    });
    jQuery("input.pro_search_custom").keypress(function (event) {
        if (event.which == 13) {
            event.preventDefault();
            jQuery('#project-list-search-button').trigger('click');
        }
    });
    jQuery("input[name='pro_filter[interested]']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {

//var path = window.location.hostname+'projects?interested=1';
            var path = '/projects?interested=interested';
            window.location.href = path;
        }
    });
    jQuery("input[name='pro_filter[myproject]']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {
            var path = '/projects?myproject=myproject';
            window.location.href = path;
        }
    });
    jQuery("input[name='pro_filter[myinterested]']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {
            var path = '/projects?myinterested=myinterested';
            window.location.href = path;

        }
    });
    jQuery("input[name='pro_filter[draft]']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {
            var path = '/projects?draft=draft';
            window.location.href = path;
        }
    });
    jQuery("input[name='pro_filter[collaboration]']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {
            var path = '/projects?collaboration=collaboration';
            window.location.href = path;
        }
    });
    jQuery("input[name='pro_diversitytype[_none]']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {
            jQuery("#edit-pro-diversitytype .form-checkbox").each(function (i) {
                this.checked = true;
            });
        } else {
            jQuery("#edit-pro-diversitytype .form-checkbox").each(function (i) {
                this.checked = false;
            });
        }
    });
	 jQuery('#project_sorting').change(function(){
		var searchsortingval = jQuery('#project_sorting').val();
        jQuery('.pro-search-project-sorting').val(searchsortingval);
		//jQuery('.cust-project-search-form').submit();
		
		jQuery('.proj-submit').trigger('click');
		//jQuery('#project_sorting').val(searchsortingval).attr("selected", "selected");
		
		 
	});
    //jQuery(".form-item-field-project-diversity-type-und .form-checkboxes").before( "<p>What types of Diversity Suppliers are you seeking?</p>" );
    jQuery("#project-node-form .form-item-field-project-diversity-type-und .form-checkboxes").before("<p><input type='checkbox' value='Select All' name='diveditall'> Select all</p>");
    jQuery("#project-node-form .form-item-field-diversity-program-comment-und-0-value .form-textarea-wrapper").before("<p>Please provide your diversity needs and goals of this project.</p>");
    jQuery('#project-node-form .form-item-field-project-diversity-type-und > label').css('display', 'none');
    jQuery("input[name='diveditall']").click(function () {
        var input = jQuery(this);
        if ((input).is(':checked')) {
            jQuery("#edit-field-project-diversity-type-und .form-checkbox").each(function (i) {
                this.checked = true;
            });
        } else {
            jQuery("#edit-field-project-diversity-type-und .form-checkbox").each(function (i) {
                this.checked = false;
            });
        }
    });
    jQuery("#edit-field-project-address").after("<p>Select region For Public Search</p>");
    jQuery("#invite-form .form-submit").click(function () {
//parent.Lightbox.end(); 
    });
    //jQuery(".group-full-pdetails-grp-tab .field-collection-item-field-pro-bidding-info").before( "<div class='text-right'><input type='checkbox' value='Select bidding' name='bidding'></div>");

    if (Drupal.settings.hasOwnProperty('m6connect_projects') && Drupal.settings.m6connect_projects.hasOwnProperty('custom_pubpic_dialog_js') && Drupal.settings.m6connect_projects.custom_pubpic_dialog_js == 1) {
//if(typeof public_dialog !== "undefined" && public_dialog == 1){ 
        jQuery('#publice-confirm').dialog({
            autoOpen: false,
            width: 400,
            modal: true,
            resizable: false,
            buttons: {
                "Ok": function () {
                    jQuery(this).dialog("close");
                },
                Cancel: function () {
                    jQuery(this).dialog("close");
                    jQuery('input[name="field_project_public[und]"]').attr('checked', false);
                    return false;
                }
            },
            open: function () {
                jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
            }
        });
        jQuery('input[name="field_project_public[und]"]').change(function () {
//alert('sdsd');
            if (jQuery(this).is(':checked')) {
                jQuery('#publice-confirm').dialog('open');
            }
        });
    }

    if (Drupal.settings.hasOwnProperty('m6connect_projects') && Drupal.settings.m6connect_projects.hasOwnProperty('custom_pubpic_dialog_js') && Drupal.settings.m6connect_projects.custom_pubpic_dialog_js == 1) {
//if(typeof public_dialog !== "undefined" && public_dialog == 1){ 
        jQuery('#publice-confirm').dialog({
            autoOpen: false,
            width: 400,
            modal: true,
            resizable: false,
            buttons: {
                "Ok": function () {
                    jQuery(this).dialog("close");
                },
                Cancel: function () {
                    jQuery(this).dialog("close");
                    jQuery('input[name="field_project_public[und]"]').attr('checked', false);
                    jQuery('input[name="field_public[und]"]').attr('checked', false);
                    return false;
                }
            },
            open: function () {
                jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
            }
        });
        jQuery('input[name="field_project_public[und]"]').change(function () {
            if (jQuery(this).is(':checked')) {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#publice-confirm').dialog('open');
            }
        });
        jQuery('input[name="field_public[und]"]').change(function () {
            if (jQuery(this).is(':checked')) {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#publice-confirm').dialog('open');
            }
        });
    }

    jQuery('input[name="pro_search"]').keydown(function (e) {
        if (e.keyCode == 13) {
            jQuery('.proj-submit').click();
        }
    });
    if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('inbox_rfp_delete') && Drupal.settings.m6connect_rfp.inbox_rfp_delete == 1) {
        jQuery('#rfp-inbox-delete-dialog').dialog({
            autoOpen: false,
            width: 400,
            modal: true,
            resizable: false,
            buttons: {
                "Ok": function () {
                    jQuery(this).dialog("close");
                    var rnid = jQuery('#rfp-inbox-delete-dialog').find('.rfp-del-nid').text(); //alert(rnid);
                    jQuery.ajax({
                        type: 'post',
                        url: '/rfpinboxdelete/' + rnid,
                        data: 'nid=' + encodeURI(rnid),
                        success: function (msg) {
                            var path = '/rfps/received';
                            window.location.href = path;
                        }
                    });
                    jQuery('#rfp-inbox-delete-dialog').find('.rfp-del-nid').text('');
                },
                Cancel: function () {
                    jQuery(this).dialog("close");
                    jQuery('#rfp-inbox-delete-dialog').find('.rfp-del-nid').text('');
                    return false;
                }
            },
            open: function () {
                jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
            }
        });
        jQuery('.cust-rfp-inbox-delete').click(function () {
            event.preventDefault();
            var rnid = jQuery(this).attr('rnid');
            var base = jQuery(this).attr('base');
            jQuery('.ui-dialog-titlebar').hide();
            jQuery('#rfp-inbox-delete-dialog').find('.rfp-del-nid').text(rnid);
            jQuery('#rfp-inbox-delete-dialog').dialog('open');
            //return false;
        });
    }

//////////////////////////////////////////////////////
    /*
     jQuery('input[name="co_name"]').keydown(function(e) {
     if (e.keyCode == 13) {
     jQuery('.co-submit').click();
     }
     });*/

    jQuery('.invitees-list-clbrte').on('click', '.remove-invitees-clbrte', function (event) { //alert('tryy');
        event.preventDefault();
        var remove_nid = jQuery(this).attr('id');
        //jQuery(".invitees-list-clbrte #"+remove_nid).parent('.selected-company-clbrte').remove();
        jQuery(".invitees-list-clbrte").find("a#" + remove_nid).closest('.selected-company-clbrte').remove();
        jQuery('.custom-companies-lists-clbrte').find('#nid-' + remove_nid).find('.invite-to-rfp-clbrte').css('display', 'block');
        jQuery('.custom-companies-lists-clbrte').find('#nid-' + remove_nid).find('.added-to-rfp-clbrte').css('display', 'none');
        var nodeid1 = jQuery('.invite_nodeid_hidden_clbrte').val();
        var sess_selected_val1 = jQuery('.invitees-list-clbrte').html();
        sessionStorage.setItem("clbrte_selected_co_email_" + nodeid1, sess_selected_val1); //sess_selected_val1

        sessionStorage.setItem("clbrte_invitelater_" + nodeid1, sess_selected_val1);
        return false;
    });
    //Remove already invited companys
    jQuery('.invited-co-list-clbrte').on('click', '.remove-invite-company-clbrte', function () {
        var parDiv = jQuery(this).closest('div.invited-companies-done-clbrte');
        //var currEle = jQuery(this);
        var cmpNid = jQuery(this).attr('cnid');
        var currNode = jQuery('.invited-co-list-clbrte').attr('rpnid');
        var itemId = jQuery(this).attr('itemid');
        var current_user = Drupal.settings.m6connect_company.user;
        if (current_user == itemId) {
            $("#dialog-confirm").dialog({
                resizable: false,
                width: 400,
                height: 200,
                modal: true,
                buttons: {
                    "Ok": function () {
                        jQuery.post('/clbrte-remove-invited-company/' + currNode + '/' + itemId)
                                .done(function (data) {
                                    if (parDiv.hasClass('company-registered') && data.msg == 1) {
                                        jQuery('#cust-company-listings-clbrte').find('div#nid-' + cmpNid + ' .invite-to-rfp-clbrte').css('display', 'block');
                                        jQuery('#cust-company-listings-clbrte').find('div#nid-' + cmpNid + ' .added-to-rfp-clbrte').css('display', 'none').text(' Added');
                                    }
                                    if (data.msg == 1) {
                                        jQuery('#cont-col-' + itemId).remove();
                                        jQuery('#co_invite_manager_' + cmpNid).find('option[value=' + itemId + ']').html(jQuery('#co_invite_manager_' + cmpNid).find('option[value=' + itemId + ']').attr('data'));
                                    }
                                    window.location.href = window.location.href;
                                });
                        $(this).dialog("close");
                    },
                    Cancel: function () {
                        $(this).dialog("close");
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-titlebar').hide();
                }

            });
        } else {

            jQuery.post('/clbrte-remove-invited-company/' + currNode + '/' + itemId)
                    .done(function (data) {
                        if (parDiv.hasClass('company-registered') && data.msg == 1) {
                            jQuery('#cust-company-listings-clbrte').find('div#nid-' + cmpNid + ' .invite-to-rfp-clbrte').css('display', 'block');
                            jQuery('#cust-company-listings-clbrte').find('div#nid-' + cmpNid + ' .added-to-rfp-clbrte').css('display', 'none').text(' Added');
                        }
                        if (data.msg == 1) {
                            jQuery('#cont-col-' + itemId).remove();
                            jQuery('#co_invite_manager_' + cmpNid).find('option[value=' + itemId + ']').html(jQuery('#co_invite_manager_' + cmpNid).find('option[value=' + itemId + ']').attr('data'));
                        }
                    });
        }

    });
    var nodeid = jQuery('.invite_nodeid_hidden_clbrte').val();
    var is_invitelater = '';
    var is_invitelater = sessionStorage.getItem("clbrte_invitelater_" + nodeid);
    if (is_invitelater != '') {
        jQuery('.invitees-list-clbrte').html(is_invitelater);
        jQuery('.invitees-list-clbrte .remove-invitees-clbrte').each(function (index, element) {
            var removeID = jQuery(this).attr('id');
            jQuery('#cust-company-listings-clbrte').find('#nid-' + removeID + ' a.invite-to-rfp-clbrte').css('display', 'none');
            jQuery('#cust-company-listings-clbrte').find('#nid-' + removeID + ' span.added-to-rfp-clbrte').css('display', 'block').addClass('rfp-added-trigger-clbrte');
        });
    }

//sessionStorage.setItem("clbrte_invitelater_"+nodeid, '');	

//////////////////////////////////////////////////////  
// add description  after Anticipated Bid field
    if (jQuery("body").hasClass('page-node-add-project') || jQuery("body").hasClass('page-node-edit node-type-project')) {
        var tableRef = document.getElementById('field-pro-bidding-info-values').getElementsByTagName('thead')[0];
        var newRow = tableRef.insertRow(tableRef.rows.length);
        var newCell = newRow.insertCell(0);
        var newText = document.createTextNode('These anticipated bids give a prospective bidder the opportunity to express interest by selecting the Intend to Bid indicators for each anticipated bid - generating a bid list for your company to use. Your company is not obligated to send the future RFP to these bidders.')
        newCell.appendChild(newText);
    }

///////////////////////////////////////////////////////
// add bidder feed back report functionality

// Infinite Ajax Scroll configuration
    if (jQuery('body').hasClass('page-projects')) {
        jQuery.ias({
            container: '.project-list-scroll',
            item: '.project-box',
            pagination: '.nav',
            next: '.nav a',
            loader: '<img src="sites/all/themes/m6connect/images/ajax-loader.gif"/>',
            triggerPageThreshold: 0,
            trigger: "See More",
        });
    }

///////////////////////////////////////////////////////
// add js for close all bookmark closed and dont show their bookmark content
    /*
     jQuery('.region-left-content .bookmarkorganizer-container #bookmarkorganizer-user-bookmarks-form .bookmarkorganizer-index-table tr.folder').each(function(index, element) {
     if(jQuery(this).hasClass('open')) {
     jQuery(this).removeClass('open');	
     jQuery(this).addClass('collapsed');
     }
     });
     
     jQuery('.region-left-content .bookmarkorganizer-container #bookmarkorganizer-user-bookmarks-form .bookmarkorganizer-index-table tr.node').each(function(index, element) {
     jQuery(this).css('display','none');	
     });
     */

    if ((jQuery('body').hasClass('page-node-add-project') || jQuery('body').hasClass('node-type-project'))) {
        jQuery('#edit-field-pro-bidding-info-und-0-field-proj-bid-date-und-0-value-datepicker-popup-0').datepicker({minDate: 0});
        jQuery('#edit-field-pro-bidding-info-und-0-field-proj-start-date-und-0-value-datepicker-popup-0').datepicker({minDate: 0});
        jQuery('#edit-field-pro-bidding-info-und-0-field-proj-complete-date-und-0-value-datepicker-popup-0').datepicker({minDate: 0});
    }
	
});
Drupal.behaviors.custom_selection_list = {
    attach: function (context, settings) {
	<!--prochat section start -->	
/*	  if (jQuery('body').hasClass('page-project-dashboard')) {
		//localStorage.removeItem("project-dashboard");
		jQuery(".project-dashboard-project-list .pd-project-list-link").click(function(e) {
		  localStorage.setItem("project-dashboard", "pd-project-list");
		});
		jQuery(".switch-pd-project-list-btn").click(function(e) {
		  localStorage.removeItem("project-dashboard");		
		});  
		var project_dashboard = localStorage.getItem("project-dashboard");
		if(project_dashboard == 'pd-project-list'){
		   //jQuery('.project-dashboard-project-list').css('display','none');
		}	  
      }*/

	  jQuery('input.group_admin_assign_option').on('change', function() {
        jQuery('input.group_admin_assign_option').not(this).prop('checked', false);
      });
	  
	  jQuery('.pd-message-chat-container').on('keypress','div.emojionearea.text-message-smilly .emojionearea-editor',function (e) {
		var keycode = (event.keyCode ? event.keyCode : event.which);		
		if(keycode == 13 && !e.shiftKey){
		  var textareaInstanceparent = jQuery(this).closest('div.emojionearea.text-message-smilly').parent('div').attr('class');
		  var mappingKeyValue = textareaInstanceparent.split('message-abc-cont-');
		  var mappingKey = mappingKeyValue[1];
		  jQuery('textarea#text-message-smilly-'+mappingKey).val(jQuery(this).html());	  
		  jQuery("input.project_dashboard_chat_send_"+mappingKey).trigger("click");		 
		}		  
	  });
	  
	  
/*	  jQuery('#pd-message-containersection').find('div.emojionearea-upbutton').unbind('click').bind('click',function(e) {
        jQuery('.prochat_file_attachedform').find("input[name='files[prochat_file_upload_section]']").trigger('click'); ; 
      });*/
	  //if (jQuery('body').hasClass('page-project-dashboard')) {
		var has_ajx_progress = jQuery("body").find(".ajax-progress"); 
		if(!has_ajx_progress.length){		  		  
		  /*if(jQuery( "#pd-message-containersection" ).hasClass( "pd-message-chat-container" )){
			setTimeout(function(){ 
			  console.log('refresh');
			  jQuery("a.pd-chat-refresh").trigger("click");			
			}, 10000);
		  }*/
	    }
	  //}
	  /*var lente = jQuery(".prochat-file-upload-section .file").length;
		if(lente >0) {
		  jQuery(".prochat_file_upload_btn").trigger("click");
		}*/
	  var container = jQuery("body").find(".pd-message-chat-container #prochat_message_container"); 
		if(container.length){
		  container.animate({scrollTop: container[0].scrollHeight}, "slow"); 
		}
	  jQuery(".custom-main-group-btn").click(function(e) {
		var matches = [];
		jQuery('input:checkbox:checked.create-group-userlist').map(function () {
		//return this.value;
		  matches.push(this.value);	
		});  
		jQuery('.newmemberlists').val(matches);
		//return false;
		jQuery('.custom-sub-group-btn').trigger('click');
	  });
	
	
	  jQuery(".prochat-delete-msg-btn-submit").click(function(e) {
		var prochat_msgdelete = [];
		jQuery('input:checkbox:checked.prochat-delete-message-check').map(function () {
		//return this.value;
		  prochat_msgdelete.push(this.value);	
		});  
		jQuery('.messete_delete_list').val(prochat_msgdelete);
		//return false;
		jQuery('.custom-sub-msgdelete-btn').trigger('click');
	  });
	  
	<!--prochat section end -->
	
        jQuery('.project-select-filter-list .cust-selection-list', context).click(function () { //alert('tsd');
            //base = jQuery('.project-select-filter-list .site_base_url').val();
            //stype = 'projects';
            //qstr = jQuery(this).children('.cust-selection-hidden-val').children('.filter-qstr').text(); 
            sfname = jQuery(this).children('.cust-selection-hidden-val').children('.sfilter-name').text();
            sfval = jQuery(this).children('.cust-selection-hidden-val').children('.sfilter-val').text();
            if (sfname == 'pro_search') {
                jQuery('#cust-project-search-form  #edit-pro-search').val('');
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }
            if (sfname == 'pro_region') {
                jQuery('#cust-project-search-form  #edit-pro-region-hierarchical-select-selects-0').val('none');
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }

            if (sfname == 'pro_diversity') {
                jQuery('#cust-project-search-form  #edit-pro-diversitytype-' + sfval).attr('checked', false);
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }

            if (sfname == 'myproject') {
                jQuery('#cust-project-search-form  #edit-pro-filter-myproject').attr('checked', false);
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }

            if (sfname == 'interested') {
                jQuery('#cust-project-search-form  #edit-pro-filter-interested').attr('checked', false);
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }

            if (sfname == 'draft') {
                jQuery('#cust-project-search-form  #edit-pro-filter-draft').attr('checked', false);
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }
            if (sfname == 'collaboration') {
                jQuery('#cust-project-search-form  #edit-pro-filter-collaboration').attr('checked', false);
                jQuery('#cust-project-search-form  #edit-pro-submit').click();
            }
        });
/////////////////////////////////////////////////////////////////////////////////////////////
        jQuery('.co_invite-manager-clbrte').change(function () {
            if (jQuery(this).find('option[value=""]').is(':selected')) {
                jQuery(this).find('option:selected').attr('selected', false);
            }
            var projectboxAction = jQuery(this).find('.project-box-actions-clbrte');
            var projectBox = jQuery(this).closest('.project-box-clbrte');
            var cmpNid = projectBox.find('.company-nid-clbrte').text(); //company-nid
            if (jQuery('.invitees-list-clbrte').html() != '') {
                var selectval = jQuery(this).val();
                if (selectval == '' || selectval == null || selectval == 'NULL' || selectval == 'null') {
                    selectval = '';
                }
                jQuery('.invitees-list-clbrte').find('.selected-company-clbrte a#' + cmpNid).attr('mngid', selectval);
                var nodeid = jQuery('.invite_nodeid_hidden_clbrte').val();
                var sess_selected_val = jQuery('.invitees-list-clbrte').html();
                sessionStorage.setItem("clbrte_selected_co_email_" + nodeid, sess_selected_val);
                sessionStorage.setItem("clbrte_invitelater_" + nodeid, sess_selected_val);
            }
        });
        jQuery('.added-to-rfp-clbrte').click(function () {
            var nodeType = jQuery('#cust-company-listings-clbrte .current-type').text();
            if (jQuery(this).hasClass('rfp-added-trigger-clbrte')) {
                var linkbox = jQuery(this).closest('.project-box-actions-clbrte');
                var inviterfp = linkbox.find('.invite-to-rfp-clbrte');
                var cmpNid = inviterfp.attr('id');
                var nodeid1 = jQuery('.invite_nodeid_hidden_clbrte').val();
                var rlink = jQuery('.invitees-list-clbrte').find('.selected-company-clbrte a#' + cmpNid);
                rlink.closest('.selected-company-clbrte').remove();
                jQuery(this).css('display', 'none');
                inviterfp.css('display', 'block');
                var sess_selected_val1 = jQuery('.invitees-list-clbrte').html();
                sessionStorage.setItem("clbrte_invitelater_" + nodeid1, sess_selected_val1);
            }
            return false;
        });
        jQuery('.invite-to-rfp-clbrte').click(function (event) {
            event.preventDefault();
            //////////////////////////////////////////////////////////
            if (check_invited_contant_person_clbrte()) {
                return false;
            }
            //////////////////////////////////////////////////////////
            var nid = jQuery(this).attr('id');
            //var selected_company = jQuery(this).parent('.col-sm-3').prev('.company-summary').children('h2').children('a').text();
            var project_box = jQuery(this).closest('div.project-box-clbrte');
            var selected_company = project_box.find('.company-summary-clbrte h2 a.cust-proj-title-clbrte').text();
            var co_manager_id = project_box.find('.invite-proj-managerid-clbrte').text();
            var co_manager_name = project_box.find('.invite-proj-managername-clbrte').text();
            //var co_manager_id = jQuery(this).next().next().next('.invite-proj-managerid').text(); //alert(co_manager_id);
            var selected_company_html = "<div class='selected-company-clbrte' id='" + selected_company + "'><a href='' class='remove-invitees-clbrte' id='" + nid + "' mngid='" + co_manager_id + "'>X</a> <span class='invitees-name-clbrte'>" + selected_company + " - " + co_manager_name + "</span></div>";
            var companies = jQuery('.invitees-list-clbrte').html();
            jQuery('.invitees-list-clbrte').html(companies + selected_company_html);
            jQuery(this).css('display', 'none');
            jQuery(this).next('.added-to-rfp-clbrte').css('display', 'block').addClass('rfp-added-trigger-clbrte');
            var nodeid = jQuery('.invite_nodeid_hidden_clbrte').val();
            var sess_selected_val = jQuery('.invitees-list-clbrte').html();
            sessionStorage.setItem("clbrte_selected_co_email_" + nodeid, sess_selected_val);
            sessionStorage.setItem("clbrte_invitelater_" + nodeid, sess_selected_val);
			jQuery('#colaborate-invite-companies-form input[value="Send Invitations"]').click();
           // var vels = jQuery('#colaborate-invite-companies-form input[value="Send Invitations"]').val();
            /*if (vels == 'Send Invitations') {
                jQuery('#colaborate-invite-companies-form #edit-submit--2').click();
            } else if (vels2 == 'Send Invitations') {
                jQuery('#colaborate-invite-companies-form #edit-submit').click();
            }*/
        });
        jQuery('.add-individual-by-email_clbrte').click(function (event) {
            event.preventDefault();
            if (check_company_email_already_invited_clbrte()) {
                return false;
            }
            if (check_invited_contant_person_clbrte()) {
                return false;
            }
            var emails = jQuery('#edit-companies-by-email-clbrte').val();
            if (emails == '' || emails == null) {
                alert('Sorry, No emails are entered for adding.');
            }
            else {
                //var seperator = ',|;';  //is_rfp_invited_company
                // var email_array = emails.replace(";",",").split(",");  //(/\./g,' ')
                var email_array = emails.replace(/\;|\r\n|\r|\n/g, ",").split(",");
                //var email_array = emails.split(seperator);
                //return false;
            }
            for (i = 0; i < email_array.length; i++) {
                if (email_array[i] == '') {
                    continue;
                }
                var desired = email_array[i].replace(/[^\w]/gi, '')
                var selected_email_html = "<div class='selected-company-clbrte' id='email-" + email_array[i] + "'><a href='' class='remove-invitees-clbrte' id='" + desired + "'>X</a> <span class='invitees-name-clbrte'>" + email_array[i] + "</span></div>";
                var companies = jQuery('.invitees-list-clbrte').html();
                jQuery('.invitees-list-clbrte').html(companies + selected_email_html);
                jQuery('#edit-companies-by-email-clbrte').val('');
            }

            var nodeid = jQuery('.invite_nodeid_hidden').val();
            var sess_selected_val = jQuery('.invitees-list-clbrte').html();
            sessionStorage.setItem("clbrte_selected_co_email_" + nodeid, sess_selected_val);
            sessionStorage.setItem("clbrte_invitelater_" + nodeid, sess_selected_val);
        });
		
        if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('custom_dialog_js')) {
            jQuery('#invite-confirm-clbrte', '#colaborate-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    //"Ok": function() {
                    "Yes, Send Invitations": function () {
                        jQuery(this).dialog("close");
                        var submitthis = jQuery('#colaborate-invite-companies-form .send-invitations-submit_clbrte');
                        var nodeid = jQuery('.invite_nodeid_hidden_clbrte').val();
                        var is_invitelater = '';
                        var is_invitelater = sessionStorage.getItem("clbrte_invitelater_" + nodeid);
                        var html = jQuery('.invitees-list-clbrte').html();
                        var hidden_html = new Array();
                        var hidden_mngr_html = '';
                        var nodeType = jQuery('#cust-company-listings-clbrte .current-type').text();
                        if (html != '' || html != null) {
                            jQuery('.selected-company-clbrte').each(function (index, element) {
                                var id = jQuery(this).children('.remove-invitees-clbrte').attr('id');
                                //if(nodeType == 'rfp'){ //by dev
                                var mngrid = jQuery(this).children('.remove-invitees-clbrte').attr('mngid');
                                if (id) {
                                    hidden_mngr_html += id + '_';
                                    if (mngrid && typeof mngrid !== "undefined") {
                                        hidden_mngr_html += mngrid;
                                    }
                                    hidden_mngr_html += ';';
                                }
                                //}

                                if (isNaN(id)) {
                                    var id = jQuery(this).children('.invitees-name-clbrte').text();
                                }
                                hidden_html.push(id);
                            });
                            if (is_invitelater != '') {
                                sessionStorage.setItem("clbrte_invitelater_" + nodeid, '');
                            }
                        }
                        else {
                            alert("No Companies are selected for Inviting.");
                            event.preventDefault();
                        }
                        jQuery('.companies_hidden_clbrte').val(hidden_html);
                        jQuery('.companies_manager_hidden_clbrte').val(hidden_mngr_html);
                        //alert(jQuery('.companies_hidden').val());
                        //alert(jQuery('.companies_manager_hidden').val());
                        sessionStorage.setItem("clbrte_selected_co_email_" + nodeid, '');
                        jQuery('.invite_js_triggered_clbrte').val('1');
                        jQuery('#colaborate-invite-companies-form .send-invitations-submit_clbrte').trigger('click');
                    },
                    Cancel: function () {
                        jQuery(this).dialog("close");
                        jQuery('.added-to-rfp-clbrte').click();
                        return false;
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });
            jQuery('#reinvite-confirm-clbrte', '#colaborate-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    "Ok": function () {
                        jQuery(this).dialog("close");
                        var submitthis = jQuery('#colaborate-invite-companies-form .resend-invitations-submit_clbrte');
                        var html = jQuery('.invitees-list').html();
                        if (html != '' || html != null) {
                        }
                        else {
                            alert("No Companies are selected for Re-Inviting.");
                            event.preventDefault();
                        }
                        jQuery('.reinvite_js_triggered_clbrte').val('1');
                        jQuery('#colaborate-invite-companies-form .resend-invitations-submit_clbrte').trigger('click');
                    },
                    Cancel: function () {
                        jQuery(this).dialog("close");
                        return false;
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });
            jQuery('#invite-later-dialog-clbrte', '#colaborate-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    Ok: function () {
                        jQuery(this).dialog("close");
                        var html = jQuery('.invitees-list-clbrte').html();
                        var hidden_html = new Array();
                        var sval = jQuery('.invitees-list-clbrte').html();
                        var nodeid = jQuery('.invite_nodeid_hidden_clbrte').val();
                        sessionStorage.setItem("clbrte_invitelater_" + nodeid, sval);
                        sessionStorage.setItem("clbrte_selected_co_email_" + nodeid, '');
                        jQuery('.invite_later_js_triggered_clbrte').val('1');
                        jQuery('#colaborate-invite-companies-form .invite-later-submit_clbrte').trigger('click');
                    }
                }
            });
            jQuery('#co-persion-dialog-clbrte', '#colaborate-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    Ok: function () {
                        jQuery(this).dialog("close");
                    }
                }
            });
            jQuery('#company-already-invited-clbrte', '#colaborate-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    Ok: function () {
                        jQuery(this).dialog("close");
                    }
                }
            });
            jQuery('.ui-dialog-titlebar').hide();
        }

        jQuery('#colaborate-invite-companies-form .send-invitations-submit_clbrte').click(function (event) {
            var emails = jQuery('#edit-companies-by-email-clbrte').val();
            if (!(emails == '' || emails == null)) { //alert('Sorry');
                jQuery('.add-individual-by-email_clbrte').click();
            }
            if (check_invited_contant_person_clbrte()) {
                return false;
            }
            if (jQuery('.invite_js_triggered_clbrte').val() == '0') {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#invite-confirm-clbrte').dialog("open");
                return false;
            }
            jQuery.blockUI({
                baseZ: 2000,
                message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while we are sending your email invitations.</strong></div>',
                css: {
                    border: 'none',
                    fadeIn: 700,
                    fadeOut: 700,
                    opacity: 0.87,
                    color: '#000',
                    padding: '15px',
                    cursor: 'wait',
                    '-webkit-border-radius': '10px',
                    '-moz-border-radius': '10px',
                }
            });
        });
        jQuery('#colaborate-invite-companies-form .resend-invitations-submit').click(function (event) {
            if (jQuery('.reinvite_js_triggered').val() == '0') {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#reinvite-confirm-clbrte').dialog("open");
                return false;
            }
            jQuery.blockUI({
                baseZ: 2000,
                message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while we are sending your email invitations.</strong></div>',
                css: {
                    border: 'none',
                    fadeIn: 700,
                    fadeOut: 700,
                    opacity: 0.87,
                    color: '#000',
                    padding: '15px',
                    cursor: 'wait',
                    '-webkit-border-radius': '10px',
                    '-moz-border-radius': '10px',
                }
            });
        });
        jQuery('#colaborate-invite-companies-form .invite-later-submit').click(function (event) {
            var emails = jQuery('#edit-companies-by-email-clbrte').val();
            if (!(emails == '' || emails == null)) { //alert('Sorry');
                jQuery('.add-individual-by-email_clbrte').click();
            }
            if (check_invited_contant_person_clbrte()) {
                return false;
            }
            if (jQuery('.invite_later_js_triggered_clbrte').val() == '0') {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#invite-later-dialog-clbrte').dialog("open");
                return false;
            }
        });
        jQuery('.co_invite-manager-clbrte').change(function (event) {
            var project_box = jQuery(this).closest('div.project-box-clbrte');
            project_box.find('.invite-proj-managerid-clbrte').text(jQuery(this).val());
            //jQuery(this).next('.invite-proj-managerid').text(jQuery(this).val());
            var names = '';
            project_box.find('.co_invite-manager-clbrte option:selected').each(function () {
                names += (names == '') ? jQuery(this).text() : ', ' + jQuery(this).text();
            });
            project_box.find('.invite-proj-managername-clbrte').text(names);
        });
/////////////////////////////////////////////////////////////////////////////////////////////
        // hide bid flag for self

        if (Drupal.settings.hasOwnProperty('m6connect_projects') && Drupal.settings.m6connect_projects.hasOwnProperty('pnode_bidflag_hide') && Drupal.settings.m6connect_projects.pnode_bidflag_hide == 1) {
            jQuery('.node-type-project .field-name-field-pro-bidding-info ul.links').empty();
        }

        // wide width for invite and collaborate tab

        jQuery('.project-profile-nav ul').on('click', 'li', function (event) {
            if (jQuery(this).hasClass('cust-pro-invite-tab') || jQuery(this).hasClass('cust-pro-collaborate-tab')) {
                jQuery('#pro-mid-column').removeClass('col-md-6');
                jQuery('#pro-mid-column').addClass('col-md-9');
                jQuery('#pro-right-column').css('display', 'none');
            } else {
                if (jQuery('#pro-mid-column').hasClass('col-md-9')) {
                    jQuery('#pro-mid-column').removeClass('col-md-9');
                    jQuery('#pro-mid-column').addClass('col-md-g');
                }
                jQuery('#pro-right-column').css('display', 'block');
            }
        });
        // when click on invite page pager, invite tab should be stay

        if (Drupal.settings.hasOwnProperty('m6connect_projects') && Drupal.settings.m6connect_projects.hasOwnProperty('project_page_invite_tab') && Drupal.settings.m6connect_projects.project_page_invite_tab == 1) {
            jQuery('#pro-mid-column .tab-pane').each(function () {
                if (jQuery(this).hasClass('in')) {
                    jQuery(this).removeClass('in');
                }
                if (jQuery(this).hasClass('active')) {
                    jQuery(this).removeClass('active');
                }
            });
            jQuery('.project-profile-nav ul li').each(function () {
                if (jQuery(this).hasClass('active')) {
                    jQuery(this).removeClass('active');
                }
            });
            jQuery('#pro-mid-column').removeClass('col-md-6');
            jQuery('#pro-mid-column').addClass('col-md-9');
            jQuery('#pro-right-column').css('display', 'none');
            jQuery('#invcomp').addClass('in active');
            jQuery('.cust-pro-invite-tab').addClass('active');
        }
		

        ////////////////////////////////////////////////////////////////////////////////////////
    }
}

//jQuery( document ).ready(function() {});


function check_invited_contant_person_clbrte() {
    var flag = 0;
    //if(Drupal.settings.m6connect_rfp.current_node_type=='rfp'){
    if (jQuery('.invitees-list-clbrte').html() != '') {
        var cmpName = '';
        jQuery('.invitees-list-clbrte .remove-invitees-clbrte').each(function (index, element) {
            var removeID = jQuery(this).attr('id');
            if (jQuery(this).attr('mngid') == '') {
                cmpName = jQuery(this).closest('.selected-company-clbrte').find('.invitees-name-clbrte').text();
                flag = 1;
                return false;
            }
        });
    }
    if (flag == 1) {
        jQuery('.ui-dialog-titlebar').hide();
        jQuery('#co-persion-dialog-clbrte .co-persion-dialog-text').html('<strong>Select Company Contact for company <br>"' + cmpName + '" First</strong>');
        jQuery('#co-persion-dialog-clbrte').dialog('open');
    }
//}
    return flag;
}

function check_company_email_already_invited_clbrte() {
    var flag = 0;
    var addEmail = jQuery('textarea[name="companies_by_email_clbrte"]').val();
    var emailIdArray = addEmail.split(',');
    var cmpNamesInvited = '';
    var cmpNamesPending = '';
    var msg = '';
    jQuery('.invited-co-list-clbrte .company-not-registered').each(function (index, element) {
        var emailId = jQuery(this).find('.invited-companies-name-clbrte').text();
        if (jQuery.inArray(emailId, emailIdArray) != -1) {
            cmpNamesInvited = (cmpNamesInvited == '') ? emailId : ', ' + emailId;
            flag = 1;
        }
    });
    jQuery('.invitees-list-clbrte .selected-company-clbrte').each(function (index, element) {
        var emailId = jQuery(this).find('.invitees-name-clbrte').text();
        if (jQuery.inArray(emailId, emailIdArray) != -1) {
            cmpNamesPending = (cmpNamesPending == '') ? emailId : ', ' + emailId;
            flag = 1;
        }
    });
    if (flag == 1) {
        jQuery('.ui-dialog-titlebar').hide();
        if (cmpNamesInvited != '') {
            msg = cmpNamesInvited + " has already been invited.";
            jQuery('#company-already-invited-clbrte .company-already-invited-text').html('<div class="form-group"><strong>' + msg + '</strong></div>');
        }
        if (cmpNamesPending != '') {
            cmpNamesPending += " already in Pending Invitation";
            msg += (msg == '') ? cmpNamesPending : "<br> And " + cmpNamesPending;
            jQuery('#company-already-invited-clbrte .company-already-invited-text').html('<strong>' + msg + '"</strong>');
        }
//jQuery('#company-already-invited-clbrte .company-already-invited-text').html('<strong>'+msg+'"</strong>');
        jQuery('#company-already-invited-clbrte').dialog('open');
    }
    return flag;
}

///////////////////// bidder feedback report /////////////////////////////
Drupal.behaviors.bidder_feedback_report = {
    attach: function (context, settings) {
        jQuery('.bfeedback-report-btn .report-btn').click(function () { //alert('hi');  
//var nodeid = jQuery(this).closest('.project-box');
            var rfpBox = jQuery(this).closest('.bfeedback-report-btn');
            var rfpNid = rfpBox.find('.bidder-feedback-nid').val(); //alert(rfpNid); 
            //var id = 1504;  
            window.location = '/rfpfeedbackreport/' + rfpNid;
            /*jQuery.ajax({
             type: 'post',
             url: '/rfpfeedbackreport/' + rfpNid,
             data: 'id=' + encodeURI(rfpNid),
             success: function(msg){
             //window.location  = '/node/'+msg;  
             }
             })*/
        });
		  
    }
}

/*function ProjectDashboardRefresh() {
  setTimeout(function(){ 
   jQuery("a.pd-chat-refresh").trigger("click");			
  }, 5000);
 
}*/