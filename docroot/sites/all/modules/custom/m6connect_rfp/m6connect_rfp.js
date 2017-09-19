var attachmentsFlag = 0;
var elementObj = '';
var hide_rfp_document_popup = 0;
var attachmentclick = 0;
Drupal.behaviors.m6connect_rfp = {
    attach: function () {



        //Change Password Short Massage  
        if (Drupal.settings.hasOwnProperty('password') && Drupal.settings.password.hasOwnProperty('tooShort')) {
            Drupal.settings.password.tooShort = 'Make it at least 8 characters';
        }

        // Remove "Button" class from Document "Browse" button in RFP node edit/add  
        if (jQuery('body').find('.node-rfp-form .droppable-browse-button').hasClass('button')) {
            var browEle = jQuery('body').find('.node-rfp-form .droppable-browse-button');
            browEle.removeClass('button');
            browEle.text('click Browse to upload files');
        }
        // Remove "Button" class from Document "Browse" button in Project node edit/add  	

        if (jQuery('body').find('.node-project-form .droppable-browse-button').hasClass('button')) {
            var browEle = jQuery('body').find('.node-project-form .droppable-browse-button');
            browEle.removeClass('button');
            browEle.text('click Browse to upload files');
        }

        if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('accept_award_membershpip_dialog') && Drupal.settings.m6connect_rfp.accept_award_membershpip_dialog == 1) {
            jQuery('#accept-award-membershpip-dialog').dialog({
                autoOpen: false,
                width: 550,
                modal: true,
                resizable: false,
                buttons: {
                    'Ok': function () {
                        jQuery(this).dialog("close");
                        window.location = '/upgrade-your-membership-subscription';
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });

            jQuery('.accept-award-memebership-required').click(function (e) {
                jQuery('#accept-award-membershpip-dialog').html('<div class="text-center"><strong>In order to Accept this Award you must have a paid M6 membership. Please purchase the membership and then you can accept the Award.</strong></div>');
                jQuery('#accept-award-membershpip-dialog').dialog('open');
            });
        }

        if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('request_intent_dialog') && Drupal.settings.m6connect_rfp.request_intent_dialog == 1) {
            jQuery("#request_to_intent_dialog").dialog({
                autoOpen: false,
                width: 500,
                modal: true,
                resizable: false,
                buttons: {
                    Ok: function () {
                        var item_id = jQuery(this).find('.data-fc-item-id').text();
                        var rfp_id = jQuery(this).find('.data-rfp-id').text();
                        var message = jQuery('.request-bid-intent-message-text').val();
                        if (message == '') {
                            if (!(jQuery('.request-bid-intent-message').find('.message-required-text').length)) {
                                jQuery('.request-bid-intent-message label[for="edit-message"]').after('<div class="message-required-text" style="color:red;">Please enter Message first</div>');
                            }
                            return false;
                        }
                        var target_form = jQuery('.request_bid_intent_dialog_form');

                        jQuery.post('/request-to-intent/' + rfp_id + '/' + item_id, {values: target_form.serialize()}).done(function (data) {
                            if (data.intent_bid_count > 0) {
                                jQuery('body').find('.request-bid-intent-link-button-' + item_id).css('background', '#419641');
                                jQuery('.request-bid-intent-link-' + item_id + ' .request-bid-intent-link-count').each(function (index, element) {
                                    jQuery(this).addClass('notification-count').text(data.intent_bid_count);
                                });
                            }
							if(data.replacemessage.hasOwnProperty('selector')){
							  jQuery(data.replacemessage.selector).html(data.replacemessage.html);
							  Drupal.attachBehaviors(jQuery('body'));	
							}
                        });
                        jQuery(this).dialog("close");
                    },
                    Cancel: function () {
                        jQuery(this).dialog('close');
                        jQuery(this).html('');
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });

        }

        jQuery('.request-bid-intent-link').click(function () {
            var invitedBidder = jQuery(this).attr('data-invited-bidder');
            var item_id = jQuery(this).attr('data-fc');
            var rfp_id = jQuery(this).attr('data-rfp');
			var package_id = jQuery(this).attr('data-package');
			var bidder_id = jQuery(this).attr('data-bidder-id');
            /*jQuery("#request_to_intent_dialog").html('<div class="text-center"><strong>Would you like to send an Intent to Bid Request to '+invitedBidder+'? By selecting OK an email will be sent to this bidder requesting them to login to M6 and indicate their Intent to Bid on this RFP.</strong><span class="data-fc-item-id" style="display:none;">'+item_id+'</span><span class="data-rfp-id" style="display:none;">'+rfp_id+'</span></div>');*/
            jQuery.post("/get-request-to-intent/" + rfp_id + '/' + item_id, {js: 1, 'invited-bidder': invitedBidder,package_id:package_id,bidder_id:bidder_id})
                    .done(function (data) {
                        jQuery("#request_to_intent_dialog").html(data.html);
                        jQuery("#request_to_intent_dialog").dialog('open');
                    });

            return false;
        });


        if ((jQuery('body').hasClass('page-rfps-sent') || jQuery('body').hasClass('page-rfps-expired')) && (jQuery('body').find('.company-list .views-row').length > 0)) {

            jQuery('#rfp-award-notice-dialog').dialog({
                autoOpen: false,
                width: 550,
                modal: true,
                resizable: false,
                buttons: {
                    Ok: function () {
                        jQuery(this).dialog("close");
                        var click_node_data = jQuery(this).find('span.click_data').text();
                        var data_nid = jQuery(this).find('span.data_nid').text();
                        jQuery.post("/rfp/ajax/action/award", {award_data: click_node_data, data_nid: data_nid}).done(function (data) {
                            //console.log(data);		
                        });
                    },
                    'Cancel': {
                        click: function () {
                            jQuery(this).dialog("close");
                        },
                        text: 'Cancel',
                        class: 'cancelButtonClass',
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });
        }

        if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('purchase_membershpip_flag') && Drupal.settings.m6connect_rfp.purchase_membershpip_flag == 1) {
            jQuery('#purchase-membershpip-dialog', '.view-rfps').dialog({
                autoOpen: false,
                width: 550,
                modal: true,
                resizable: false,
                buttons: {
                    "Agree": function () {
                        var data_nid = jQuery(this).find('span.data-id').text();
                        var hidepopup = 0;
                        if (jQuery('#hide-rfp-access-popup').is(':checked')) {
                            hidepopup = 1;
                        }
                        jQuery.post('/agreed-membership-payment/' + data_nid, {hide_popup: hidepopup}).done(function (data) {
                            if (data.status == 1) {
                                window.location = data.path;
                            }
                        });
                        jQuery(this).dialog("close");

                        jQuery(this).html('');
                        return false;
                    },
                    /*"Disagree": function() {
                     jQuery( this ).dialog( "close" );
                     jQuery( this ).html('');
                     return false;
                     }*/
                },
                /*open: function() {
                 jQuery('.ui-dialog-buttonpane').find('button:contains("Disagree")').addClass('cancelButtonClass');
                 }*/
            });
        }
        /////////////////////////////////////
        /*if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('agreed_membership_payment_popup_flag') && Drupal.settings.m6connect_rfp.agreed_membership_payment_popup_flag == 1) {
            var data_nid = Drupal.settings.m6connect_rfp.agreed_membership_nid;
            jQuery('#purchase-membershpip-dialog').html('<div><div class="text-center form-group"><strong>Pay Upon Award</strong></div><div class="text-center form-group"><strong>By opening this RFP your company agrees that upon Award, should you be successful in the bid effort, you will purchase an M6Connect Gold Membership. Be sure to include the cost of the Gold Membership in your bid.</strong></div><div class="form-element"><input type="checkbox" value="1" id="hide-rfp-access-popup" /><strong>&nbsp;&nbsp;Do not show in the future.</strong></div><span class="data-id" style="display:none;">' + data_nid + '</span></div>');
            jQuery('#purchase-membershpip-dialog').dialog('open');
        }*/
        /////////////////////////////////////
        if (jQuery("body").hasClass('node-type-rfp') || jQuery("body").hasClass('node-type-project')) {
            jQuery("#dialog-rfp-project-node-view").dialog({
                autoOpen: false,
                width: 500,
                modal: true,
                resizable: false,
                buttons: {
                    "Send": function () {
                        var nodeId = jQuery('#dialog-rfp-project-node-id').text();
                        var message = jQuery('.notification-message-text').val();
                        if (message == '') {
                            if (!(jQuery('.choose-notification-message').find('.message-required-text').length)) {
                                jQuery('label[for="edit-message"]').after('<div class="message-required-text" style="color:red;"><strong>Please enter Message first</strong></div>');
                            }
                            return false;
                        }
                        var target_form = jQuery('.send-notification-invited-companies-form');
                        jQuery.post("/send-notification-update/ajax/" + nodeId, {values: target_form.serialize(), js: 1})
                                .done(function (data) {
                                    //console.log(data); 
                                });
                        jQuery(this).dialog("close");
                        return false;
                    },
                    "Cancel": function () {
                        jQuery(this).dialog("close");
                        return false;
                    },
                    "Yes": function () {
                        jQuery('.choose-notification-message').show();
                        jQuery('.ui-dialog-buttonpane').find('button:contains("Send")').show();
                        jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').show();
                        jQuery('.ui-dialog-buttonpane').find('button:contains("Yes")').hide();
                        jQuery('.ui-dialog-buttonpane').find('button:contains("No")').hide();
                        return false;
                    },
                    "No": function () {
                        jQuery(this).dialog("close");
                        return false;
                    },
                },
                open: function () {
                    jQuery('.choose-notification-message').hide();
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Send")').hide();
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').hide().addClass('cancelButtonClass');
                    jQuery('.ui-dialog-buttonpane').find('button:contains("No")').addClass('cancelButtonClass');
                }
            });
            jQuery('.ui-dialog-titlebar').hide();

            ///////////////////////////////////////////////////////
            /*var nodeId = jQuery('#dialog-rfp-project-node-id').text();
             jQuery.post( "/send-notification-update/"+nodeId, { js: 1})
             .done(function( data ) {
             console.log(data);
             jQuery("#dialog-rfp-project-node-view").html(data.html);
             jQuery("#dialog-rfp-project-node-view").dialog('open');
             }); 
             */
            //////////////////////////////////////////////////////  
        }
        // thank you invite dialog

        if (jQuery("body").hasClass('node-type-rfp') || jQuery("body").hasClass('page-invite-companies')) {
            jQuery("#dialog-thnakyou-invited").dialog({
                autoOpen: false,
                width: 700,
                modal: true,
                resizable: false,
                buttons: {
                    "Ok": function () {
                        jQuery(this).dialog("close");
                        //return false;
                    }
                    /*"Cancel": function() {
                     jQuery( this ).dialog( "close" );
                     //return false;
                     }*/
                }
            });
        }
//jQuery( document ).ready(function() {
        /*jQuery('#edit-field-reference-number-und-0-value').change(function() {
         var v = jQuery("#edit-field-reference-number-und-0-value").val();
         var currentYear = (new Date).getFullYear();
         if (/^\d{6}$/.test(v)) {
         jQuery("#edit-field-reference-number-und-0-value").val(v+'-'+currentYear);
         } else {
         alert("RFP Number/Reference must be in (xxxxxx) format with digits only.");
         jQuery("#edit-field-reference-number-und-0-value").val('');
         }
         });*/

        /*jQuery('.rpf-exposed-filter .exposed_sort_by_select').change(function(){
         jQuery('.rpf-exposed-filter .exposed_filter_submit_bt').click();
         });*/


        /*jQuery('.added-to-rfp').each(function(index, element) {
         jQuery(this).css('display', 'none');
         });*/

        jQuery('.co_invite-manager').change(function () {
            if (jQuery(this).find('option[value=""]').is(':selected')) {
                jQuery(this).find('option:selected').attr('selected', false);
            }
            var projectboxAction = jQuery(this).find('.project-box-actions');
            var projectBox = jQuery(this).closest('.project-box');
            var cmpNid = projectBox.find('.company-nid').text();   //company-nid
            if (jQuery('.invitees-list').html() != '') {
                var selectval = jQuery(this).val();
                if (selectval == '' || selectval == null || selectval == 'NULL' || selectval == 'null') {
                    selectval = '';
                }
                jQuery('.invitees-list').find('.selected-company a#' + cmpNid).attr('mngid', selectval);
                var nodeid = jQuery('.invite_nodeid_hidden').val();
                var sess_selected_val = jQuery('.invitees-list').html();
                sessionStorage.setItem("selected_co_email_" + nodeid, sess_selected_val);
                sessionStorage.setItem("invitelater_" + nodeid, sess_selected_val);
            }

        });

        jQuery('.added-to-rfp').click(function () {
            var nodeType = jQuery('#cust-company-listings .current-type').text();
            if (jQuery(this).hasClass('rfp-added-trigger')) {
                var linkbox = jQuery(this).closest('.project-box-actions');
                var inviterfp = linkbox.find('.invite-to-rfp');
                var cmpNid = inviterfp.attr('id');
                var nodeid1 = jQuery('.invite_nodeid_hidden').val();
                var rlink = jQuery('.invitees-list').find('.selected-company a#' + cmpNid);
                rlink.closest('.selected-company').remove();
                jQuery(this).css('display', 'none');
                inviterfp.css('display', 'block');
                var sess_selected_val1 = jQuery('.invitees-list').html();
                sessionStorage.setItem("invitelater_" + nodeid1, sess_selected_val1);
            }
            return false;
        });

        jQuery('.invite-to-rfp').click(function (event) {
            event.preventDefault();
            //////////////////////////////////////////////////////////
            if (check_invited_contant_person()) {
                return false;
            }
            //////////////////////////////////////////////////////////
            var nid = jQuery(this).attr('id');
            //var selected_company = jQuery(this).parent('.col-sm-3').prev('.company-summary').children('h2').children('a').text();
            var project_box = jQuery(this).closest('div.project-box');
            var selected_company = project_box.find('.company-summary h2 a.cust-proj-title').text();
            var co_manager_id = project_box.find('.invite-proj-managerid').text();
			if(co_manager_id == '') {
			  jQuery('#invite-rfp-popup-dialog .invite-rfp-popup-dialog-text').html('Oops, first you need to select the person(s) you would like to invite. <br>Hold down the Ctrl key to select or deselect invitees.');
              jQuery('#invite-rfp-popup-dialog').dialog('open');
			  return false;
			}
            var co_manager_name = project_box.find('.invite-proj-managername').text();
            //var co_manager_id = jQuery(this).next().next().next('.invite-proj-managerid').text(); //alert(co_manager_id);
            var selected_company_html = "<div class='selected-company' id='" + selected_company + "'><a href='' class='remove-invitees' id='" + nid + "' mngid='" + co_manager_id + "'>[X]</a> <span class='invitees-name'>" + selected_company + " - " + co_manager_name + "</span></div>";
            var companies = jQuery('.invitees-list').html();
            jQuery('.invitees-list').html(companies + selected_company_html);
            jQuery(this).css('display', 'none');
            jQuery(this).next('.added-to-rfp').css('display', 'block').addClass('rfp-added-trigger');

            var nodeid = jQuery('.invite_nodeid_hidden').val();
            var sess_selected_val = jQuery('.invitees-list').html();
            sessionStorage.setItem("selected_co_email_" + nodeid, sess_selected_val);

            sessionStorage.setItem("invitelater_" + nodeid, sess_selected_val);
            /*
             jQuery('.remove-invitees').click(function(event) {
             event.preventDefault();
             var remove_nid = jQuery(this).attr('id');
             jQuery(".invitees-list #"+remove_nid).parent('.selected-company').remove();
             //jQuery('#nid-'+remove_nid).children('.invite-to-rfp').css('display', 'block');
             //jQuery('#nid-'+remove_nid).children('.added-to-rfp').css('display', 'none');
             jQuery('#nid-'+remove_nid).find('.invite-to-rfp').css('display', 'block');
             jQuery('#nid-'+remove_nid).find('.added-to-rfp').css('display', 'none');
             
             var nodeid1 = jQuery('.invite_nodeid_hidden').val();
             var sess_selected_val1 = jQuery('.invitees-list').html();
             sessionStorage.setItem("selected_co_email_"+nodeid1, sess_selected_val1);
             
             sessionStorage.setItem("invitelater_"+nodeid, sess_selected_val1);
             return false;
             }); */
        });

        jQuery('.add-individual-by-email').click(function (event) {
            event.preventDefault();
            if (check_company_email_already_invited()) {
                return false;
            }
            if (check_invited_contant_person()) {
                return false;
            }
            var emails = jQuery('#edit-companies-by-email').val();

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
                var desired = email_array[i].replace(/[^\w]/gi, '');
                var selected_email_html = "<div class='selected-company' id='email-" + email_array[i] + "'><a href='' class='remove-invitees' id='" + desired + "'>[X]</a> <span class='invitees-name'>" + email_array[i] + "</span></div>";
                var companies = jQuery('.invitees-list').html();
                jQuery('.invitees-list').html(companies + selected_email_html);
                jQuery('#edit-companies-by-email').val('');
            }

            var nodeid = jQuery('.invite_nodeid_hidden').val();
            var sess_selected_val = jQuery('.invitees-list').html();
            sessionStorage.setItem("selected_co_email_" + nodeid, sess_selected_val);

            sessionStorage.setItem("invitelater_" + nodeid, sess_selected_val);

            /*jQuery('.remove-invitees').click(function(event) {
             event.preventDefault();
             var remove_nid = jQuery(this).attr('id');
             jQuery(".invitees-list #"+remove_nid).parent('.selected-company').remove();
             jQuery('#nid-'+remove_nid).children('.invite-to-rfp').css('display', 'block');
             jQuery('#nid-'+remove_nid).children('.added-to-rfp').css('display', 'none');
             
             var nodeid2 = jQuery('.invite_nodeid_hidden').val();
             var sess_selected_val2 = jQuery('.invitees-list').html();
             sessionStorage.setItem("selected_co_email_"+nodeid2, sess_selected_val2);
             
             sessionStorage.setItem("invitelater_"+nodeid, sess_selected_val2);
             return false;
             }); */
        });
        if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('custom_dialog_js') && Drupal.settings.m6connect_rfp.custom_dialog_js) {
            jQuery('#invite-confirm', '#rfp-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    "Ok": function () {
                        jQuery(this).dialog("close");
                        var submitthis = jQuery('#rfp-invite-companies-form .send-invitations-submit');
                        var nodeid = jQuery('.invite_nodeid_hidden').val();
                        var is_invitelater = '';
                        var is_invitelater = sessionStorage.getItem("invitelater_" + nodeid);
                        var html = jQuery('.invitees-list').html();
                        var hidden_html = new Array();
                        var hidden_mngr_html = '';
                        var nodeType = jQuery('#cust-company-listings .current-type').text();
                        if (html != '' || html != null) {
                            jQuery('.selected-company').each(function (index, element) {
                                var id = jQuery(this).children('.remove-invitees').attr('id');
                                //if(nodeType == 'rfp'){ //by dev
                                var mngrid = jQuery(this).children('.remove-invitees').attr('mngid');
                                if (id) {
                                    hidden_mngr_html += id + '_';
                                    if (mngrid && typeof mngrid !== "undefined") {
                                        hidden_mngr_html += mngrid;
                                    }
                                    hidden_mngr_html += ';';
                                }
                                //}

                                if (isNaN(id)) {
                                    var id = jQuery(this).children('.invitees-name').text();
                                }
                                hidden_html.push(id);
                            });
                            if (is_invitelater != '') {
                                sessionStorage.setItem("invitelater_" + nodeid, '');
                            }
                        }
                        else {
                            alert("No Companies are selected for Inviting.");
                            event.preventDefault();
                        }
                        jQuery('.companies_hidden').val(hidden_html);
                        jQuery('.companies_manager_hidden').val(hidden_mngr_html);
                        //alert(jQuery('.companies_hidden').val());
                        //alert(jQuery('.companies_manager_hidden').val());
                        sessionStorage.setItem("selected_co_email_" + nodeid, '');
                        jQuery('.invite_js_triggered').val('1');
                        jQuery('#rfp-invite-companies-form .send-invitations-submit').trigger('click');
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

            jQuery('#reinvite-confirm', '#rfp-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    "Ok": function () {
                        jQuery(this).dialog("close");
                        var submitthis = jQuery('#rfp-invite-companies-form .resend-invitations-submit');
                        var html = jQuery('.invitees-list').html();
                        if (html != '' || html != null) {
                        }
                        else {
                            alert("No Companies are selected for Re-Inviting.");
                            event.preventDefault();
                        }
                        jQuery('.reinvite_js_triggered').val('1');
                        jQuery('#rfp-invite-companies-form .resend-invitations-submit').trigger('click');
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

            jQuery('#invite-later-dialog', '#rfp-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    Ok: function () {
                        jQuery(this).dialog("close");
                        var html = jQuery('.invitees-list').html();
                        var hidden_html = new Array();
                        var sval = jQuery('.invitees-list').html();
                        var nodeid = jQuery('.invite_nodeid_hidden').val();
                        sessionStorage.setItem("invitelater_" + nodeid, sval);
                        sessionStorage.setItem("selected_co_email_" + nodeid, '');
                        jQuery('.invite_later_js_triggered').val('1');
                        jQuery('#rfp-invite-companies-form .invite-later-submit').trigger('click');
                    }
                }
            });

            jQuery('#co-persion-dialog', '#rfp-invite-companies-form').dialog({
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
			
			jQuery('#invite-rfp-popup-dialog', '#rfp-invite-companies-form').dialog({
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

            jQuery('#company-already-invited', '#rfp-invite-companies-form').dialog({
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

            jQuery('#remove-invite-company-dialog', '#rfp-invite-companies-form').dialog({
                autoOpen: false,
                width: 400,
                modal: true,
                resizable: false,
                buttons: {
                    "Delete": function () {
                        var currNode = jQuery(this).find('span.remove-currnode').text();
                        var cmpNid = jQuery(this).find('span.remove-cmpnid').text();
                        var itemId = jQuery(this).find('span.remove-item-id').text();
                        var parDiv = jQuery('#invited-companies-done-' + itemId);
                        jQuery.post('/remove-invited-company/' + currNode + '/' + itemId).done(function (data) {
                            if (parDiv.hasClass('company-registered') && data.msg == 1) {
                                jQuery('#cust-company-listings').find('div#nid-' + cmpNid + ' .invite-to-rfp').css('display', 'block');
                                jQuery('#cust-company-listings').find('div#nid-' + cmpNid + ' .added-to-rfp').css('display', 'none').text(' Added');
                            }
                            if (data.msg == 1) {
                                parDiv.remove();
                            }
                        });
                        jQuery(this).dialog("close");
                        jQuery(this).html('');
                        return false;
                    },
                    "Cancel": function () {
                        jQuery(this).dialog("close");
                        jQuery(this).html('');
                        return false;
                    }
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });

            jQuery('.ui-dialog-titlebar').hide();

        }
        /*
         if(Drupal.settings.hasOwnProperty('m6connect_projects') && Drupal.settings.m6connect_projects.hasOwnProperty('cust_service_agrmnt_dialog_js') && Drupal.settings.m6connect_projects.cust_service_agrmnt_dialog_js == 1){
         //if(typeof public_dialog !== "undefined" && public_dialog == 1){ 
         jQuery('#service-agrmnt-pops').dialog({
         autoOpen: false,
         width: 400,
         modal: true,
         resizable: false,
         buttons: {
         "Ok": function() {
         jQuery( this ).dialog( "close" );
         },
         Cancel: function() {
         jQuery( this ).dialog( "close" );
         }
         },
         open: function() {
         jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
         }
         });
         jQuery("#user-login-form .form-submit").click(function (event) {
         var checked = jQuery(".term-condi-chkbx").is(':checked'); //alert(a);
         if (!checked) {
         //alert('You need to must check Service Agreement checkbox');
         jQuery('.ui-dialog-titlebar').hide();
         jQuery('#service-agrmnt-pops').dialog('open');
         event.preventDefault();
         }
         }); 
         } */

        jQuery('#rfp-invite-companies-form .send-invitations-submit').click(function (event) {
            var emails = jQuery('#edit-companies-by-email').val();
            if (!(emails == '' || emails == null)) { //alert('Sorry');
                jQuery('.add-individual-by-email').click();
            }
            if (check_invited_contant_person()) {
                return false;
            }
            if (jQuery('.invite_js_triggered').val() == '0') {
                jQuery('.ui-dialog-titlebar').hide();
                if(!check_company_email_already_invited()) 
                {
                    jQuery('#invite-confirm').dialog("open");
                }                   
                //jQuery('#invite-confirm').dialog("open");           
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


            //return false;
            //var pop_msg = confirm("Are you sure you want to send out this RFP?");
            //if (pop_msg != true){
            //  event.preventDefault();
            //  return false;  
            //}


            /*var nodeid = jQuery('.invite_nodeid_hidden').val();
             var is_invitelater = '';
             var is_invitelater = sessionStorage.getItem("invitelater_"+nodeid); 
             var html = jQuery('.invitees-list').html();
             var hidden_html = new Array();
             var hidden_mngr_html='';
             if (html != '' || html != null) {
             jQuery('.selected-company').each(function(index, element) {
             var id = jQuery(this).children('.remove-invitees').attr('id');
             var mngrid = jQuery(this).children('.remove-invitees').attr('mngid');
             if(id){
             hidden_mngr_html += id+'_';
             if(mngrid){
             hidden_mngr_html += mngrid;
             }
             hidden_mngr_html += ';';
             }
             
             if (isNaN(id)) {
             var id = jQuery(this).children('.invitees-name').text(); 
             }
             hidden_html.push(id);
             });
             if(is_invitelater != '') {
             sessionStorage.setItem("invitelater_"+nodeid, ''); 
             }
             }
             else {
             alert("No Companies are selected for Inviting.");
             event.preventDefault();
             }
             jQuery('.companies_hidden').val(hidden_html);
             jQuery('.companies_manager_hidden').val(hidden_mngr_html);
             
             sessionStorage.setItem("selected_co_email_"+nodeid, '');*/


        });

        jQuery('#rfp-invite-companies-form .resend-invitations-submit').click(function (event) {
            if (jQuery('.reinvite_js_triggered').val() == '0') {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#reinvite-confirm').dialog("open");
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

            //return false;
            //var pop_msg = confirm("Are you sure you want to send out this RFP?");
            //if (pop_msg != true){
            //  event.preventDefault();
            //  return false;  
            //}


            /*var nodeid = jQuery('.invite_nodeid_hidden').val();
             var is_invitelater = '';
             var is_invitelater = sessionStorage.getItem("invitelater_"+nodeid); 
             var html = jQuery('.invitees-list').html();
             var hidden_html = new Array();
             var hidden_mngr_html='';
             if (html != '' || html != null) {
             jQuery('.selected-company').each(function(index, element) {
             var id = jQuery(this).children('.remove-invitees').attr('id');
             var mngrid = jQuery(this).children('.remove-invitees').attr('mngid');
             if(id){
             hidden_mngr_html += id+'_';
             if(mngrid){
             hidden_mngr_html += mngrid;
             }
             hidden_mngr_html += ';';
             }
             
             if (isNaN(id)) {
             var id = jQuery(this).children('.invitees-name').text(); 
             }
             hidden_html.push(id);
             });
             if(is_invitelater != '') {
             sessionStorage.setItem("invitelater_"+nodeid, ''); 
             }
             }
             else {
             alert("No Companies are selected for Inviting.");
             event.preventDefault();
             }
             jQuery('.companies_hidden').val(hidden_html);
             jQuery('.companies_manager_hidden').val(hidden_mngr_html);
             
             sessionStorage.setItem("selected_co_email_"+nodeid, '');*/


        });



        /*if(Drupal.settings.m6connect_rfp.later_js_popup){
         jQuery('.ui-dialog-titlebar').hide();
         jQuery('#invite-later-dialog').dialog('open'); 
         }*/

        jQuery('#rfp-invite-companies-form .invite-later-submit').click(function (event) {
            var emails = jQuery('#edit-companies-by-email').val();
            if (!(emails == '' || emails == null)) { //alert('Sorry');
                jQuery('.add-individual-by-email').click();
            }
            if (check_invited_contant_person()) {
                return false;
            }
            if (jQuery('.invite_later_js_triggered').val() == '0') {
                jQuery('.ui-dialog-titlebar').hide();
                jQuery('#invite-later-dialog').dialog("open");
                return false;
            }

            //var html = jQuery('.invitees-list').html();
            //var hidden_html = new Array();
            //var sval = jQuery('.invitees-list').html();
            //var nodeid = jQuery('.invite_nodeid_hidden').val();
            //sessionStorage.setItem("invitelater_"+nodeid, sval);
            //sessionStorage.setItem("selected_co_email_"+nodeid, '');
            //alert('Saved as Draft');

        });

        /*jQuery('#rfp-company-search-form #edit-co-submit').click(function(event) {
         var html = jQuery('.invitees-list').html();
         if (html != '' || html != null) {
         jQuery('.selected-company').each(function(index, element) {
         var id = jQuery(this).children('.remove-invitees').attr('id');
         if (isNaN(id)) {
         var id = jQuery(this).children('.invitees-name').text(); 
         }
         existing_companies.push(id);		
         });
         }
         }); */

        jQuery('.co_invite-manager').change(function (event) {
            var project_box = jQuery(this).closest('div.project-box');
            project_box.find('.invite-proj-managerid').text(jQuery(this).val());
            //jQuery(this).next('.invite-proj-managerid').text(jQuery(this).val());
            var names = '';
            project_box.find('.co_invite-manager option:selected').each(function () {
                names += (names == '') ? jQuery(this).text() : ', ' + jQuery(this).text();
            });
            project_box.find('.invite-proj-managername').text(names);
        });

        /////////////////////Filter Clear ////////////////////////////////////////////////
        jQuery('.company-select-filter-list .cust-selection-list').click(function () { //alert('tsd');
            //base = jQuery('.project-select-filter-list .site_base_url').val();
            //stype = 'projects';
            //qstr = jQuery(this).children('.cust-selection-hidden-val').children('.filter-qstr').text(); 
            //sfname = jQuery(this).children('.cust-selection-hidden-val').children('.sfilter-name').text();
            //sfval = jQuery(this).children('.cust-selection-hidden-val').children('.sfilter-val').text();
            sfname = jQuery(this).find('.sfilter-name').text();
            sfval = jQuery(this).find('.sfilter-val').text();
            if (sfname == 'co_name') {
                jQuery('#rfp-company-search-form  #edit-co-name').val('');
                jQuery('#rfp-company-search-form  #edit-co-submit').click();
            }
            if (sfname == 'co_facilities') {
                jQuery('#rfp-company-search-form  #edit-co-facilities-hierarchical-select-selects-0').val('none');
                jQuery('#rfp-company-search-form  #edit-co-submit').click();
            }

            if (sfname == 'co_region') {
                jQuery('#rfp-company-search-form  #edit-co-region-hierarchical-select-selects-0').val('none');
                jQuery('#rfp-company-search-form  #edit-co-submit').click();
            }

            if (sfname == 'co_industries') {
                jQuery('#rfp-company-search-form  #edit-co-industries-hierarchical-select-selects-0').val('none');
                jQuery('#rfp-company-search-form  #edit-co-submit').click();
            }

            if (sfname == 'co_pservices') {
                jQuery('#rfp-company-search-form  #edit-co-pservices-hierarchical-select-selects-0').val('none');
                jQuery('#rfp-company-search-form  #edit-co-submit').click();
            }

            if (sfname == 'co_diversity') {
                jQuery('#rfp-company-search-form  #edit-co-diversitytype-' + sfval).attr('checked', false);
                jQuery('#rfp-company-search-form  #edit-co-submit').click();
            }
        });
        //////////////////////////////////////////////////////////////////////////////////

//});

        ///////////////////////// Membership Upgrade Requirement start //////////////////////
        if (Drupal.settings.m6connect_rfp.mupgrade_dialog_js) {
            jQuery('#membership-upgrade-confirm').dialog({
                autoOpen: false,
                width: 550,
                modal: true,
                resizable: false,
                buttons: {
                    "Agree": function () {
                        jQuery(this).dialog("close");
                        if(jQuery(this).find('span.proposal-popup').length){
                          jQuery('.form-field-name-field-footer-buttton input[value="Submit eProposal"]').trigger('click');
                          return;
                        }
                        var agreeduser = 0;
                        var rfpnodenid = 0;
                        agreeduser = jQuery('.download-document-section .rfpNode-nid-hidden input[class="agreeduser-uid"]').val();
                        rfpnodenid = jQuery('.download-document-section .rfpNode-nid-hidden input[class="rfpNode-nid"]').val();
                        if (agreeduser > 0 && rfpnodenid > 0) {
                            //url1 = '/agreeduser/' + rfpnodenid + '/' + agreeduser;
                            //window.location = url1;
                            var hidepopup = 0;
                            if (jQuery('#hide-mupgrade-access-popup').is(':checked')) {
                                hidepopup = 1;
                            }
                            jQuery.ajax({
                                type: 'post',
                                url: '/agreeduser/' + rfpnodenid + '/' + agreeduser + '/' + hidepopup,
                                data: 'rfpnodenid=' + encodeURI(rfpnodenid) + '&agreeduser=' + encodeURI(agreeduser) + '&hidepopup=' + encodeURI(hidepopup),
                                success: function (msg) {
                                    if (hidepopup == 1) {
                                        hide_rfp_document_popup = 1;
                                    }
                                }
                            });
                        }
                        var param = new Array();
                        var doc = 0;
                        jQuery('table.document-view-rfp input.document-view-rfp.form-checkbox').each(function (index, element) {
                            if (jQuery(this).is(':checked')) {
                                doc++;
                                param.push('fids[]=' + jQuery(this).val() || 0);
                            }
                        });
                        var url = param.join('&');
                        if (doc > 0 && url != '') {
                            url = '/all-document-download?' + url;
                            window.location = url;
							jQuery.blockUI({
							  baseZ: 2000,
							  message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while your documents download. This may take a few minutes.</strong></div>',
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
						  setTimeout(jQuery.unblockUI, 8000);
                        }
                    }/*, 
                     Cancel: function() {
                     jQuery( this ).dialog( "close" );
                     return false;
                     }*/
                },
                open: function () {
                    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
                }
            });
        }

        ///////////////////////// Membership Upgrade Requirement End ////////////////////////
        /* // Popup on Project RFP node edit for copy button
         jQuery('.ProjectWithRFP').click(function() {  
         var data = jQuery(this).attr('data');//alert(data);alert('df');
         copy_project(data);
         event.preventDefault();
         });
         
         jQuery('.DocumentsWithRFP').click(function() {  
         var data = jQuery(this).attr('data');//alert(data);alert('df');
         copy_rfps(data);
         event.preventDefault();
         });
         */
    }};

jQuery(document).ready(function () {

    ///////////////////////////////////////////////////
	var getPath = window.location.pathname; 
	var getUrlParameter = function getUrlParameter(sParam) {
	var sPageURL = decodeURIComponent(window.location.search.substring(1)),
	sURLVariables = sPageURL.split('&'),
	sParameterName,
	i;
	for (i = 0; i < sURLVariables.length; i++) {
	 sParameterName = sURLVariables[i].split('=');
	 if (sParameterName[0] === sParam) {
	   return sParameterName[1] === undefined ? true : sParameterName[1];
	 }
	}
	};
	var invitejoinrequesterfromcom = '';
	var invitejoinrequesterfrom = '';
	var invitejoinrequesterto = '';
	if(getUrlParameter('company')){
	  var invitejoinrequesterfromcom = getUrlParameter('company');
	}else if(getUrlParameter('request-id')){
	  var invitejoinrequesterfromcom = getUrlParameter('request-id');
	}else{
	  var invitejoinrequesterfromcom = '';
	}
	if(getUrlParameter('invitejoinrequesterfrom')){
	  var invitejoinrequesterfrom = getUrlParameter('invitejoinrequesterfrom');
	}
	if(getUrlParameter('invitejoinrequesterto')){
	  var invitejoinrequesterto = getUrlParameter('invitejoinrequesterto');
	}
    
	
	
	//console.log(invitejoinrequesterfromcom);
	//console.log(invitejoinrequesterfrom);
	//console.log(invitejoinrequesterto);
	
	if(invitejoinrequesterfromcom && invitejoinrequesterfrom && invitejoinrequesterto){
	  sessionStorage.setItem("invitejoinrequesterfromcomNew",invitejoinrequesterfromcom);
	  sessionStorage.setItem("invitejoinrequesterfromNew", invitejoinrequesterfrom);
	  sessionStorage.setItem("invitejoinrequestertoNew", invitejoinrequesterto);
	}
	
	
    var ev = new jQuery.Event('customRemovedClass');
    orig = jQuery.fn.removeClass;
    jQuery.fn.removeClass = function () {
        jQuery(this).trigger(ev, arguments);
        return orig.apply(this, arguments);
    }

    var ev1 = new jQuery.Event('customAddClass');
    orig1 = jQuery.fn.addClass;
    jQuery.fn.addClass = function () {
        jQuery(this).trigger(ev1, arguments);
        return orig1.apply(this, arguments);
    }

    //Start Bidder Feedback tab refresh should redirect to Bidder Feedback tab.
    if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('rfp_node_nid') && Drupal.settings.m6connect_rfp.rfp_node_nid) {
        var activefeedbackArr = [];
        var nodeid = parseInt(Drupal.settings.m6connect_rfp.rfp_node_nid);
        //Drupal.settings.m6connect_rfp.hasOwnProperty('referer_empty') && Drupal.settings.m6connect_rfp.referer_empty==1 && 
        if (Drupal.settings.m6connect_rfp.hasOwnProperty('rfp_node_active_tab')) {
            var activeTab = Drupal.settings.m6connect_rfp.rfp_node_active_tab;
            var activeContent = jQuery('div.horizontal-tabs-panes fieldset.horizontal-tabs-pane').eq(activeTab);
            var feedbackactiveTab = Drupal.settings.m6connect_rfp.rfp_feedback_active_tab;
            if (activeContent.hasClass('group-bidder-feedback')) {
                if (feedbackactiveTab != '') {
                    activefeedbackArr = feedbackactiveTab.split(',');
                    jQuery.each(activefeedbackArr, function (index, value) {
                        jQuery('#cust-bidder-fb-lists fieldset.collapse-processed').eq(value).removeClass('collapsed');
                    });
                }
                activeContent.data("horizontalTab").focus();
                jQuery.post("/set-rfp-active-tab/" + nodeid, {pos: activeTab, feedbacktab: feedbackactiveTab});
            }
        }

        if (Drupal.settings.m6connect_rfp.hasOwnProperty('edit_rfp_feedback') && Drupal.settings.m6connect_rfp.hasOwnProperty('rfp_feedback_active_tab') && Drupal.settings.m6connect_rfp.edit_rfp_feedback == 1) {
            var nodeid = parseInt(Drupal.settings.m6connect_rfp.rfp_node_nid);
            var feedbackactiveTab = Drupal.settings.m6connect_rfp.rfp_feedback_active_tab;
            if (feedbackactiveTab != '' && feedbackactiveTab != null) {
                activefeedbackArr = feedbackactiveTab.split(',');
                jQuery.each(activefeedbackArr, function (index, value) {
                    jQuery('#cust-bidder-fb-lists fieldset.collapse-processed').eq(value).removeClass('collapsed');
                });
            }
            jQuery.post("/set-rfp-active-tab/" + nodeid, {pos: '', feedbacktab: activefeedbackArr.toString()});
        }

        jQuery('ul.horizontal-tabs-list li.horizontal-tab-button a').click(function () {
            var nodeid = parseInt(Drupal.settings.m6connect_rfp.rfp_node_nid);
            var listitem = jQuery(this).closest('li');
            var nodeid = parseInt(Drupal.settings.m6connect_rfp.rfp_node_nid);
            var index = jQuery('ul.horizontal-tabs-list li.horizontal-tab-button').index(listitem);
            jQuery.post("/set-rfp-active-tab/" + nodeid, {pos: index});
        });

        jQuery('#cust-bidder-fb-lists fieldset.bid-package-fieldset').on('customRemovedClass', function (evx, removedClasses) {
            if (removedClasses == 'collapsed') {
                var nodeid = parseInt(Drupal.settings.m6connect_rfp.rfp_node_nid);
                var addpos = jQuery('#cust-bidder-fb-lists fieldset').index(jQuery(this));
                if (jQuery.inArray(addpos, activefeedbackArr) == -1) {
                    activefeedbackArr.push(addpos);
                    jQuery.post("/set-rfp-active-tab/" + nodeid, {feedbacktab: activefeedbackArr.toString()});                    
                }
            }
        });

        jQuery('#cust-bidder-fb-lists fieldset.bid-package-fieldset').on('customAddClass', function (evx, newClasses) {
            if (newClasses == 'collapsed') {
                var nodeid = parseInt(Drupal.settings.m6connect_rfp.rfp_node_nid);
                var removepos = jQuery('#cust-bidder-fb-lists fieldset').index(jQuery(this));
                activefeedbackArr.splice(jQuery.inArray(removepos, activefeedbackArr), 1);
                jQuery.post("/set-rfp-active-tab/" + nodeid, {feedbacktab: activefeedbackArr.toString()});
                console.log('customAddClass  ' + activefeedbackArr.toString());
            }
        });
    }
    //End Bidder Feedback tab refresh should redirect to Bidder Feedback tab.
    ///////////////////////////////////////////////////

    if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('redirect_to_invite') && Drupal.settings.m6connect_rfp.redirect_to_invite == 1) {
//	 jQuery(".group-invited-companies").data("horizontalTab").focus(); 
    }

    if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('attachment_popup') && Drupal.settings.m6connect_rfp.attachment_popup == 1) {
        jQuery('#attachment-popup').dialog({
            autoOpen: false,
            width: 600,
            modal: true,
            stack: false,
            resizable: false,
            buttons: {
                'Save Now': function () {
                    jQuery(this).dialog("close");
                    jQuery('.custom-attach-document-submit').click();
                },
                'Ignore & Continue': function () {
                    jQuery(this).dialog("close");
                    attachmentsFlag = 0;
                    /*if(jQuery('body').find('.unsaved-attachment-trigger-click').length){
                     jQuery('body').find('.unsaved-attachment-trigger-click').click(); 	
                     }*/
                    if (elementObj != '') {
                        elementObj[0].click();
                    }
                }
            },
            open: function () {
                jQuery('.ui-dialog-buttonpane').find('button:contains("Ignore & Continue")').addClass('cancelButtonClass').addClass('ignore-continue');
                jQuery('.ui-dialog').css("zIndex", 2002);
                jQuery(".ui-widget-overlay").css("zIndex", 2000);
                //jQuery(".ui-widget-overlay").css("zIndex", 2000).css("opacity", 0.87).css('background-color','rgb(0, 0, 0)');
            },
            create: function (event, ui) {
                jQuery(event.target).parent().css('position', 'fixed');
            },
        });
    }
    jQuery('.ui-dialog-titlebar').hide();
    /*
     var cusr = jQuery("#user-login-form input[name='name']").val(); //alert(cusr);
     jQuery('.cust-term-cond-error').css('display', 'none');
     var chk = jQuery(".term-condi-chkbx").is(':checked');
     if(jQuery.cookie(cusr)) {
     if(!chk) {
     jQuery(".term-condi-chkbx").attr('checked',true);
     }	  
     }
     
     jQuery("#user-login-form input[name='name'], #user-login-form input[name='pass']").blur(function() {
     var cuser = jQuery("#user-login-form input[name='name']").val(); //alert(cuser);
     var check = jQuery(".term-condi-chkbx").is(':checked');
     if(jQuery.cookie(cuser)) {	  
     //var data=jQuery.cookie(cuser);  //alert(data); alert('dfsft');
     if(!check) {
     jQuery(".term-condi-chkbx").attr('checked',true);
     }
     } else {
     jQuery(".term-condi-chkbx").attr('checked',false);	
     }
     });  
     
     jQuery("#user-login-form .form-submit").click(function (event) {
     var user = jQuery("#user-login-form input[name='name']").val(); //alert(user); 
     var checked = jQuery(".term-condi-chkbx").is(':checked'); //alert(a);
     if(!checked) {
     if(jQuery.cookie(user)) {
     jQuery(".term-condi-chkbx").attr('checked',true);  
     } else {
     jQuery('.cust-term-cond-error').css('display', 'block');
     event.preventDefault();
     }
     } else {
     //var cookiename='serviceagrmnt';
     var cookiename= user;
     if(jQuery.cookie(cookiename)){
     //jQuery.cookie('serviceagrmnt',(parseInt(jQuery.cookie('serviceagrmnt')) + 1));
     } else {
     //jQuery.cookie('serviceagrmnt',user);
     jQuery.cookie(user, 1);
     }
     }
     });	
     */
    //---------------
    if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('updated_rfp_project') && Drupal.settings.m6connect_rfp.updated_rfp_project == 1) {
        var nodeId = jQuery('#dialog-rfp-project-node-id').text();
        jQuery.post("/send-notification-update/" + nodeId, {js: 1})
                .done(function (data) {
                    jQuery("#dialog-rfp-project-node-view").html(data.html);
                    jQuery("#dialog-rfp-project-node-view").dialog('open');
                });
    }
    //---------------
    // thankyou rfp invited dialog
    if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('invite_send_thanks') && Drupal.settings.m6connect_rfp.invite_send_thanks == 1) {
        var nodeId = jQuery('#dialog-thnakyou-invited-node-id').text();
        var NoInvited = Drupal.settings.m6connect_rfp.NoOfInvitation;
        //var dhtml = '<div class="text-center"><strong><div>Thank you for registering your RFP with M6Connect.</div><div>To increase your possibility of getting the best response, we suggest you invite as many bidders as possible. You have invited ('+ NoInvited +').</div><div>That is pretty good.</div><div>All users of M6Connect get free access to RFPs, but those you award the RFP must agree to pay for a Gold M6Connect membership.</div></strong></div>';
        var dhtml = '<div class="text-center"><strong><div>Thank you for announcing your RFP on M6Connect.  Your invited bidders receive free access to RFPs including the bid documents. When you are ready to award you can acknowledge the award through M6Connect by selecting the Action “Award” button and a formal “Notice of Award” notification will be sent via email.</div></strong></div>';

        jQuery("#dialog-thnakyou-invited").html(dhtml);
        jQuery("#dialog-thnakyou-invited").dialog('open');
    }

    //------------------
    /*jQuery("#user-register-form .form-submit").click(function (event) {
     var checked = jQuery(".field-name-field-service-agreement input[type='checkbox']").is(':checked'); //alert(a);
     if(!checked) {
     jQuery(".form-item-field-service-agreement-und").before('<div class="cust-term-cond-error" style="color:red;">You must select that you agree with the Service Agreement before accessing the system</div>');
     event.preventDefault();	
     }
     });*/
    ////////////////////////////////////////////////	
    if (jQuery("body").hasClass('front')) {
        jQuery("#non-company-user-dialog").dialog({
            autoOpen: false,
            width: 800,
            modal: true,
            resizable: false,
            buttons: {
                "Close": function () {
                    jQuery(this).dialog("close");
                    return false;
                }
            },
            open: function () {
                jQuery('.ui-dialog-buttonpane').find('button:contains("Close")').addClass('cancelButtonClass');
            }
        });
        jQuery('.ui-dialog-titlebar').hide();

        /*jQuery("#incomplete-company-profile-dialog").dialog({
            autoOpen: false,
            width: 400,
            modal: true,
            resizable: false,
            buttons: {
                "Close": function () {
                    jQuery(this).dialog("close");
                    window.location = '/node/add/organization';
                    //return false;
                }
            },
            open: function () {
                jQuery('.ui-dialog-buttonpane').find('button:contains("Close")').addClass('cancelButtonClass');
            }
        });*/
		
		
		if (Drupal.settings.hasOwnProperty('m6connect_misc') && Drupal.settings.m6connect_misc.hasOwnProperty('m6id_company_popup') && Drupal.settings.m6connect_misc.m6id_company_popup == 1) {
		  var m6id_uid = Drupal.settings.m6connect_misc.m6id_company_uid;
	      jQuery("#incomplete-company-profile-dialog").dialog({
			autoOpen: false,
			width: 500,
			modal: true,
			resizable: false,
			buttons: {
			  "Ok": function () {
				  jQuery(this).dialog("close");
				  window.location = '/user/'+m6id_uid+'/m6id-info';
			  },
			  "Close": function () {
				  jQuery(this).dialog("close");
			  }
			},
			open: function () {
				jQuery('.ui-dialog-buttonpane').find('button:contains("Close")').addClass('cancelButtonClass');
			}
		 });
	     jQuery("#incomplete-company-profile-dialog").html("<div class='text-center'><strong>You have been added as a member of company '" + Drupal.settings.m6connect_misc.m6id_company_title + "'. Select Ok to complete your M6ID Profile now?</strong></div>");
	     jQuery("#incomplete-company-profile-dialog").dialog('open');
	   }
		
		

        jQuery('.ui-dialog-titlebar').hide();
    }
    jQuery("#company-join-msz").dialog({
        autoOpen: false,
        width: 400,
        modal: true,
        resizable: false,
        buttons: {
            "Ok": function () {
                jQuery(this).dialog("close");
            }
        },
        open: function () {
            jQuery('.ui-dialog-buttonpane').find('button:contains("Close")').addClass('cancelButtonClass');
        }
    });
	
	
    if(!(sessionStorage.getItem("invitejoinrequesterfromcomNew") && sessionStorage.getItem("invitejoinrequesterfromNew") && sessionStorage.getItem("invitejoinrequestertoNew"))){
	//if(!(invitejoinrequesterfromcom && invitejoinrequesterfrom && invitejoinrequesterto)){
      if (Drupal.settings.hasOwnProperty('m6connect_misc') && Drupal.settings.m6connect_misc.hasOwnProperty('non_company_popup') && Drupal.settings.m6connect_misc.non_company_popup == 1) {
        jQuery("#non-company-user-dialog").html("<div class='text-center'><strong>Thank you for joining M6Connect! During the registration process, you indicated that you would like to join '" + Drupal.settings.m6connect_misc.company_name + "'. To gain access to this organization's information, your request to join must be approved by the company administrator. In order to complete this process, please contact site administrator: <a href='mailto:"+Drupal.settings.m6connect_misc.company_mail+"'>" + Drupal.settings.m6connect_misc.company_mail +"</a></strong></div>");
		jQuery("#non-company-user-dialog").dialog('open');
      }    
    }
	else if((sessionStorage.getItem("invitejoinrequesterfromcomNew") && sessionStorage.getItem("invitejoinrequesterfromNew") && sessionStorage.getItem("invitejoinrequestertoNew"))){
		if(getPath == '/dashboard'){
		  sessionStorage.removeItem('invitejoinrequesterfromcomNew');
		  sessionStorage.removeItem('invitejoinrequesterfromNew');
		  sessionStorage.removeItem('invitejoinrequestertoNew');
		}
		//console.log('sessin');
		//console.log(sessionStorage.getItem("invitejoinrequesterfromcomNew"));
		//console.log(sessionStorage.getItem("invitejoinrequesterfromNew"));
		//console.log(sessionStorage.getItem("invitejoinrequestertoNew"));
		
	}else {
	  //alert('company grant '+invitejoinrequesterfromcom+ ' by user '+invitejoinrequesterfrom + 'to user ' + invitejoinrequesterto);
	  
	}

    if (Drupal.settings.hasOwnProperty('m6connect_company') && Drupal.settings.m6connect_company.hasOwnProperty('incomplete_company_profile') && Drupal.settings.m6connect_company.incomplete_company_profile == 1) {
        jQuery("#incomplete-company-profile-dialog").html('<div class="text-center"><strong>M6Connect during a previous session without successfully completing the company profile</strong></div>');
        jQuery("#incomplete-company-profile-dialog").dialog('open');
    }
    if (Drupal.settings.hasOwnProperty('m6connect_company') && Drupal.settings.m6connect_company.hasOwnProperty('request_sent') && Drupal.settings.m6connect_company.request_sent == 1) {
        debugger;
        jQuery("#company-join-msz").html('<div class="text-center"><strong>Join as Employee Request has been sent to the account admin</strong></div>');
        jQuery("#company-join-msz").dialog('open');
        jQuery(".ui-dialog-titlebar").hide();
    }

    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
        var urlajax = ajaxOptions.url;
        //console.log(ajaxOptions); 

        if ((urlajax.indexOf("/file/ajax/field_rfp_documents") == 0 || urlajax.indexOf("/file/ajax/field_clarification_attachment") == 0 || urlajax.indexOf("/file/ajax/field_images/") == 0 || urlajax.indexOf("/file/ajax/field_user_profile_photo/") == 0 || urlajax.indexOf("/file/ajax/field_logo/") == 0 || urlajax.indexOf("/file/ajax/field_company_profile_cover_img/") == 0 || urlajax.indexOf("/file/ajax/field_user_profile_cover_img/") == 0 || urlajax.indexOf("/file/ajax/organigation_main_container/organization_logo_contianer/organization_logo/") == 0|| urlajax.indexOf("/file/ajax/custwrap") == 0 || urlajax.indexOf("/file/ajax/field_rfp_logo/") == 0 || urlajax.indexOf("/file/ajax/field_proposal_document_picture") == 0 || urlajax.indexOf("/file/ajax/field_image_upload/") == 0 || urlajax.indexOf("/file/ajax/dneedscustwrap") == 0) && (ajaxOptions.hasOwnProperty('extraData') && ((ajaxOptions.extraData.hasOwnProperty('ajax_iframe_upload') && ajaxOptions.extraData.ajax_iframe_upload == 1) || (ajaxOptions.extraData.hasOwnProperty('_triggering_element_value') && ajaxOptions.extraData._triggering_element_value == 'Upload')))) {
            jQuery.blockUI({
                //theme:     true,
                baseZ: 2000,
                message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while your files are being securely uploaded to our servers</strong></div>',
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
            if ((urlajax.indexOf("/file/ajax/field_rfp_documents") == 0)) {
                attachmentsFlag = 1;
            }
        }
        if ((urlajax.indexOf("/my-proposal/ajax/action/award") == 0) || (urlajax.indexOf("/rfp/ajax/action/award") == 0)) {
            jQuery.blockUI({
                baseZ: 2000,
                message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while we are sending email.</strong></div>',
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
        }
    }).ajaxError(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxSuccess(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
        //console.log(ajaxOptions);
        var urlajax = ajaxOptions.url;
        if ((urlajax.indexOf("/file/ajax/field_rfp_documents") == 0 || urlajax.indexOf("/file/ajax/field_clarification_attachment") == 0 || urlajax.indexOf("/file/ajax/field_images/") == 0 || urlajax.indexOf("/file/ajax/field_user_profile_photo/") == 0 || urlajax.indexOf("/file/ajax/field_logo/") == 0 || urlajax.indexOf("/file/ajax/field_company_profile_cover_img/") == 0 || urlajax.indexOf("/file/ajax/field_user_profile_cover_img/") == 0 || urlajax.indexOf("/file/ajax/organigation_main_container/organization_logo_contianer/organization_logo/") == 0 ||  urlajax.indexOf("/file/ajax/custwrap") == 0 || urlajax.indexOf("/file/ajax/field_rfp_logo/") == 0 || urlajax.indexOf("/file/ajax/field_proposal_document_picture") == 0 || urlajax.indexOf("/file/ajax/field_image_upload/") == 0 || urlajax.indexOf("/file/ajax/dneedscustwrap") == 0) && (ajaxOptions.hasOwnProperty('extraData') && ((ajaxOptions.extraData.hasOwnProperty('ajax_iframe_upload') && ajaxOptions.extraData.ajax_iframe_upload == 1) || (ajaxOptions.extraData.hasOwnProperty('_triggering_element_value') && ajaxOptions.extraData._triggering_element_value == 'Upload')))) {
            jQuery.unblockUI();
        }
        if ((urlajax.indexOf("/my-proposal/ajax/action/award") == 0) || (urlajax.indexOf("/rfp/ajax/action/award") == 0)) {
            jQuery.unblockUI();
        }
        //Infinite scroll (see more link) in RFP/Project/Company, Attach behaviors to newly added items
        if (jQuery('body').find('div.custom-companies-lists').length > 0 && urlajax.indexOf("page=") != -1) {
            Drupal.attachBehaviors(jQuery('div.custom-companies-lists'));
        }
    });

    /*window.onbeforeunload = function () {
     if(attachmentsFlag==1){
     attachmentsFlag =0;	
     alert('dfgfdggfgfg');
     return false;  
     }
     }*/

    jQuery('.download-document-section .download-selected-documents').click(function (e) {
        //////////////// Subscription user popup start ///////////////////////////
        var docSelected = 0
        jQuery('table.document-view-rfp input.document-view-rfp.form-checkbox').each(function (index, element) {
            if (jQuery(this).is(':checked')) {
                docSelected++;
            }
        });
        if (Drupal.settings.hasOwnProperty('m6connect_rfp') && Drupal.settings.m6connect_rfp.hasOwnProperty('not_available_free') && Drupal.settings.m6connect_rfp.not_available_free == 1 && hide_rfp_document_popup == 0 && docSelected > 0) {
            jQuery('#membership-upgrade-confirm').dialog("open");
            return false;
        }
        //////////////// Subscription user popup end ///////////////////////////
        var param = new Array();
        var doc = 0;
        jQuery('table.document-view-rfp input.document-view-rfp.form-checkbox').each(function (index, element) {
            if (jQuery(this).is(':checked')) {
                doc++;
                param.push('fids[]=' + jQuery(this).val() || 0);
            }
        });
        var url = param.join('&');
        if (doc > 0 && url != '') {
            url = '/all-document-download?' + url;
            //console.log(url);
            //window.location = '/all-document-download?'+url;	
            window.location = url;
			jQuery.blockUI({
                baseZ: 2000,
                message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while your documents download. This may take a few minutes.</strong></div>',
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
			setTimeout(jQuery.unblockUI, 8000);
        }
    });
    //////////////// Subscription user popup for proposal node form start ///////////////////////////
    /*jQuery('.node-my_proposal-form .form-field-name-field-choose-from-the-options-li input[name="field_choose_from_the_options_li[und]"]').click(function (e) {
        if (Drupal.settings.m6connect_rfp.is_subscription == 0) {
            var CompName = jQuery('.node-my_proposal-form .proposal_company_name').val();
            jQuery('#membership-upgrade-confirm').html('<div class="text-center"><div class="dialog-heading"><strong>Membership Upgrade Required</strong></div><div class="dialog-description"><br />Your company, ' + CompName + ', agrees that you will upgrade to a Gold membership if you win this bid effort.  If you win you will receive a “Notice of Preliminary Award” email requiring you to upgrade.</div></div>');
            jQuery('#membership-upgrade-confirm').dialog("open");
            //return false;
        }
    });*/
    
    
    
    jQuery('.form-field-name-field-footer-buttton input[value="Submit eProposal"]').click(function (ev) {
    	if(isNaN(ev.isTrigger)){
    		var selectedvalue = '';
    		var submittedFor = jQuery('input[name="field_choose_from_the_options_li[und]"]:checked').val();
    		if((submittedFor == 'Submit Proposal in Response to a RFP' &&  jQuery('.form-field-name-field-submit-proposal-in-respons input.form-checkbox').length)|| (submittedFor == 'Submit Proposal in Response to a Project' || jQuery('.form-field-name-field-field-sub-proposal-pjt input.form-checkbox').length ) || (submittedFor == 'Submit Proposal to a company' || jQuery('.form-field-name-field-submit-proposal-to-company input.form-checkbox').length )){
    		  var CompName = jQuery('.node-my_proposal-form .proposal_company_name').val();
    		  if(submittedFor == 'Submit Proposal in Response to a RFP'){
    			  selectedvalue = jQuery('.form-field-name-field-submit-proposal-in-respons input[name="field_submit_proposal_in_respons[und][0][target_id]"]').val();  
    		  }else if(submittedFor == 'Submit Proposal in Response to a Project'){
    			  selectedvalue = jQuery('.form-field-name-field-field-sub-proposal-pjt input[name="field_field_sub_proposal_pjt[und][0][target_id]"]').val();
    		  }else{
				  selectedvalue = jQuery('.form-field-name-field-submit-proposal-to-company input[name="field_submit_proposal_to_company[und][0][target_id]"]').val();
			  }
    		}
    		if(selectedvalue){
    		  ev.preventDefault();
  			  jQuery.post( "/check-proposal-popup-show/"+selectedvalue).done(function( data ) {
  			    if(data.status ==1){
  			    	jQuery('#membership-upgrade-confirm').html('<span class="proposal-popup" style="display:none;"></span><div class="text-center"><div class="dialog-heading"><strong>Membership Upgrade Required</strong></div><div class="dialog-description"><br />Your company, ' + CompName + ', agrees that you will upgrade to a Gold membership if you win this bid effort.  If you win you will receive a “Notice of Preliminary Award” email requiring you to upgrade.</div></div>');
  		            jQuery('#membership-upgrade-confirm').dialog("open");
  		 		    ev.preventDefault();
  		 		    return false;
  			    }else{
  			    	jQuery('.form-field-name-field-footer-buttton input[value="Submit eProposal"]').trigger('click');
  			    }
  			  });
  		   }
 		 }
    });
   
    //////////////// Subscription user popupfor proposal node form end ///////////////////////////

    //////////////// Subscription user popup for proposal award start ///////////////////////////
    /*$( ".pro-award" ).click(function(e) {
     if(Drupal.settings.m6connect_rfp.is_subscription==0){ 
     jQuery('#membership-upgrade-confirm').dialog("open");
     return false;
     }  
     }); */
    //////////////// Subscription user popup for proposal award end ///////////////////////////

    jQuery('input[name="co_name"]').keydown(function (e) {
        if (e.keyCode == 13) {
            jQuery('.co-submit').click();
        }
    });

    jQuery('.invitees-list').on('click', '.remove-invitees', function () {
        event.preventDefault();
        var remove_nid = jQuery(this).attr('id');
        jQuery(".invitees-list #" + remove_nid).parent('.selected-company').remove();
        jQuery('#nid-' + remove_nid).find('.invite-to-rfp').css('display', 'block');
        jQuery('#nid-' + remove_nid).find('.added-to-rfp').css('display', 'none');

        var nodeid1 = jQuery('.invite_nodeid_hidden').val();
        var sess_selected_val1 = jQuery('.invitees-list').html();
        sessionStorage.setItem("selected_co_email_" + nodeid1, sess_selected_val1);  //sess_selected_val1

        sessionStorage.setItem("invitelater_" + nodeid1, sess_selected_val1);
        return false;
    });

    //Remove already invited companys
    jQuery('.invited-co-list').on('click', '.remove-invite-company', function () {
        var parDiv = jQuery(this).closest('div.invited-companies-done');
        //var currEle = jQuery(this);
        var cmpNid = jQuery(this).attr('cnid');
        var currNode = jQuery('.invited-co-list').attr('rpnid');
        var itemId = jQuery(this).attr('itemid');
        if (jQuery(this).hasClass('fc-awarded')) {
            jQuery('#remove-invite-company-dialog').html('<div class="text-center"><strong>Seleted Company/Individual is Awared. Are you want to remove this invited Company/Individual</strong></div><span style="display:none;" class="remove-currnode">' + currNode + '</span><span style="display:none;" class="remove-item-id">' + itemId + '</span><span style="display:none;" class="remove-cmpnid">' + cmpNid + '</span>');
            jQuery('#remove-invite-company-dialog').dialog('open');
            return false;
        }
        jQuery.post('/remove-invited-company/' + currNode + '/' + itemId)
                .done(function (data) {
                    if (parDiv.hasClass('company-registered') && data.msg == 1) {
                        jQuery('#cust-company-listings').find('div#nid-' + cmpNid + ' .invite-to-rfp').css('display', 'block');
                        jQuery('#cust-company-listings').find('div#nid-' + cmpNid + ' .added-to-rfp').css('display', 'none').text(' Added');
                    }
                    if (data.msg == 1) {
                        parDiv.remove();
                    }
                });
    });

    var nodeid = jQuery('.invite_nodeid_hidden').val();
    var is_invitelater = '';
    var is_invitelater = sessionStorage.getItem("invitelater_" + nodeid);
    if (is_invitelater != '') {
        jQuery('.invitees-list').html(is_invitelater);
        jQuery('.invitees-list .remove-invitees').each(function (index, element) {
            var removeID = jQuery(this).attr('id');
            jQuery('#cust-company-listings').find('#nid-' + removeID + ' a.invite-to-rfp').css('display', 'none');
            jQuery('#cust-company-listings').find('#nid-' + removeID + ' span.added-to-rfp').css('display', 'block').addClass('rfp-added-trigger');
        });
    }

    Drupal.ajax.prototype.commands.awardOfNoticeDailog = function (ajax, response, status) {
        //console.log(response);
        var rfpTitle = response.rfpTitle;
        var click_node_data = response.values;
        var data_nid = response.data_nid;
        var awardingCompanyTitle = response.awardingCompanyTitle
        jQuery('#rfp-award-notice-dialog').html('<div class="text-center"><div class="dialog-heading"><strong>Notice of Pending Award</strong></div><div class="dialog-description"><br/>A “Notice of Pending Award” will be sent to the selected company(s) - ' + rfpTitle + ' from ' + awardingCompanyTitle + '.  They are required to have a current Gold Membership and click on the green Action button to Accept the Award.  Upon accepting the award they will receive an official “Notice of Award” certificate.</div><span class="click_data" style="display:none;">' + click_node_data + '</span><span class="data_nid" style="display:none;">' + data_nid + '</span></div>');
        jQuery('#rfp-award-notice-dialog').dialog('open');
    }
    Drupal.ajax.prototype.commands.add_from_elements = function (ajax, response, status) {
        //jQuery(response.selector).animate({ scrollTop: jQuery(response.selector)[0].scrollHeight },-1000);
//    jQuery(response.selector).nanoScroller({destroy: true});

        Drupal.attachBehaviors(jQuery('#block-statuses-statuses'));
        jQuery('#block-statuses-statuses .statuses-form-self-update textarea.form-textarea').focus();
        jQuery('#dLabel2').click();
    }
    Drupal.ajax.prototype.commands.add_from_elements_fb = function (ajax, response, status) {

        Drupal.attachBehaviors(jQuery('#content'));
    }


    $(".cust-countnull").click(function () {

        // alert('test');
        var url = "/custcountnull";
        jQuery.ajax({
            type: 'post',
            url: '/custcountnull',
            success: function (msg) {
                jQuery(".notification-count").css('display', 'none');
            }
        });

    });

});

function check_invited_contant_person() {
    var flag = 0;
    //if(Drupal.settings.m6connect_rfp.current_node_type=='rfp'){
    if (jQuery('.invitees-list').html() != '') {
        var cmpName = '';
        jQuery('.invitees-list .remove-invitees').each(function (index, element) {
            var removeID = jQuery(this).attr('id');
            if (jQuery(this).attr('mngid') == '') {
                cmpName = jQuery(this).closest('.selected-company').find('.invitees-name').text();
                flag = 1;
                return false;
            }
        });
    }
    if (flag == 1) {
        jQuery('.ui-dialog-titlebar').hide();
        jQuery('#co-persion-dialog .co-persion-dialog-text').html('<strong>Select Company Contact for company <br>"' + cmpName + '" First</strong>');
        jQuery('#co-persion-dialog').dialog('open');
    }
    //}
    return flag;
}

function check_company_email_already_invited() {
    var flag = 0;
    var addEmail = jQuery('textarea[name="companies_by_email"]').val();
    var emailIdArray = addEmail.split(',');
    var cmpNamesInvited = '';
    var cmpNamesPending = '';
    var msg = '';
    jQuery('.invited-co-list .company-not-registered').each(function (index, element) {
        var emailId = jQuery(this).find('.invited-companies-name').text();
        if (jQuery.inArray(emailId, emailIdArray) != -1) {
            cmpNamesInvited = (cmpNamesInvited == '') ? emailId : ', ' + emailId;
            flag = 1;
        }
    });
    jQuery('.invitees-list .selected-company').each(function (index, element) {
        var emailId = jQuery(this).find('.invitees-name').text();
        if (jQuery.inArray(emailId, emailIdArray) != -1) {
            cmpNamesPending = (cmpNamesPending == '') ? emailId : ', ' + emailId;
            flag = 1;
        }
    });
    if (flag == 1) {
        jQuery('.ui-dialog-titlebar').hide();
        if (cmpNamesInvited != '') {
            msg = cmpNamesInvited + " has already been invited.";
			jQuery('#company-already-invited .company-already-invited-text').html('<div class="form-group"><strong>' + msg + '</strong></div>'); // remove double quote
        }
        if (cmpNamesPending != '') {
            cmpNamesPending += " already in Pending Invitation";
            msg += (msg == '') ? cmpNamesPending : "<br> And " + cmpNamesPending;
			jQuery('#company-already-invited .company-already-invited-text').html('<strong>' + msg + '"</strong>'); 
        }
        //jQuery('#company-already-invited .company-already-invited-text').html('<strong>' + msg + '"</strong>');
        jQuery('#company-already-invited').dialog('open');
    }
    return flag;
}

/*jQuery(window).on('beforeunload', function(e) {
 alert(attachmentsFlag);
 if(attachmentsFlag==1) {
 return 'You have unsaved stuff. Are you sure to leave?';
 }
 });*/

Drupal.behaviors.m6connect_attachments = {
    attach: function (context) {
        /*window.onbeforeunload = function(e) { 
         if(attachmentsFlag==1) {
         console.log(e);
         //e.preventDefault();
         //return cancelEvent(e);
         //return false;
         //return 'You currently have unsaved changes. You have uploaded a document however you have not saved the page.';
         }
         }; */
        jQuery("a:not(.droppable-browse-button), button, input[type='submit']:not(.node-edit-protection-processed)").each(function () {
            jQuery(this).click(function (e) {
                if (attachmentsFlag == 1) {
                    elementObj = jQuery(this);
                    jQuery(this).addClass('unsaved-attachment-trigger-click');
                    elementObj = jQuery(this);
                    jQuery('#attachment-popup').dialog('open');
                    return false;
                }
            });
        });



    }
}

function copy_project(id) {
    jQuery("#dialog-confirm-copyrelatedrfp").dialog({
        resizable: false,
        width: 300,
        modal: true,
        buttons: {
            "Yes": function () {
                var url = "/copyproject/" + id;
                jQuery.ajax({
                    type: 'post',
                    url: '/copyproject/' + id + '?rfpsalso=1',
                    data: 'id=' + encodeURI(id),
                    success: function (msg) {
                        window.location = '/node/' + msg;
                    }
                });
                jQuery(this).dialog("close");
            },
            "No": function () {
                var url = "/copyproject/" + id;
                jQuery.ajax({
                    type: 'post',
                    url: '/copyproject/' + id + '?rfpsalso=2',
                    data: 'id=' + encodeURI(id),
                    success: function (msg) {
                        window.location = '/node/' + msg;
                    }
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


function copy_rfps(id) {
    jQuery("#dialog-confirm-copydocumentrfp").dialog({
        resizable: false,
        width: 300,
        modal: true,
        buttons: {
            "Yes": function () {
                var url = "/copyrfp/" + id;
                jQuery.ajax({
                    type: 'post',
                    url: '/copyrfp/' + id + '?documentsalso=1',
                    data: 'id=' + encodeURI(id),
                    success: function (msg) {
                        window.location = '/node/' + msg;
                    }
                });
                jQuery(this).dialog("close");
            },
            "No": function () {
                var url = "/copyrfp/" + id;
                jQuery.ajax({
                    type: 'post',
                    url: '/copyrfp/' + id + '?documentsalso=2',
                    data: 'id=' + encodeURI(id),
                    success: function (msg) {
                        window.location = '/node/' + msg;
                    }
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

//cust-countnull

jQuery(document).ready(function($){
  if ((jQuery('body').hasClass('node-type-rfp') || jQuery('body').hasClass('page-node-add-rfp'))){
	  jQuery('#edit-field-issued-und-0-value-datepicker-popup-0').datepicker({ minDate: 0 });
	  jQuery('#edit-field-due-und-0-value-datepicker-popup-0').datepicker({ minDate: 0 });
	  jQuery('#edit-field-expected-award-und-0-value-datepicker-popup-0').datepicker({ minDate: 0 })
	  jQuery('#edit-field-expected-start-und-0-value-datepicker-popup-0').datepicker({ minDate: 0 })
	  jQuery('#edit-field-expected-end-und-0-value-datepicker-popup-0').datepicker({ minDate: 0 })
  }
  
  jQuery('#user-menu-nav.user-profile-tab-area li.user-onboarding-tab').on('customRemovedClass', function (evx, removedClasses) {
	if (removedClasses == 'active'){
	  jQuery('.middle-three-main-section').show();
	  if(jQuery('.middle-two-main-section').hasClass('col-md-9')){
		jQuery('.middle-two-main-section').removeClass('col-md-9').addClass('col-md-6');
	  }
	  if(jQuery('.middle-three-main-section').hasClass('col-md-12')){
		jQuery('.middle-three-main-section').removeClass('col-md-12').addClass('col-md-3');
	  }
	}
  });
  
  jQuery('#user-menu-nav.user-profile-tab-area li.user-onboarding-tab').on('customAddClass', function (evx, addedClasses) {
	if (addedClasses == 'active'){
	  jQuery('.middle-three-main-section').hide();
	  if(jQuery('.middle-two-main-section').hasClass('col-md-6')){
		jQuery('.middle-two-main-section').removeClass('col-md-6').addClass('col-md-9');
	  }
	  if(jQuery('.middle-three-main-section').hasClass('col-md-3')){
		jQuery('.middle-three-main-section').removeClass('col-md-3').addClass('col-md-12');
	  }
	}
  });

  // create click function for send sms dynamically
    jQuery('.cust-bidder-fb-content').on('click','.request-by-sms-link',function () {
        var invitedBidder = jQuery(this).attr('data-invited-bidder');
        var item_id = jQuery(this).attr('data-fc');
        var rfp_id = jQuery(this).attr('data-rfp');
        var package_id = jQuery(this).attr('data-package');
        var bidder_id = jQuery(this).attr('data-bidder-id');
        var phoneNo = jQuery(this).attr('data-bidder-phone');            
        /*jQuery("#request_to_intent_dialog").html('<div class="text-center"><strong>Would you like to send an Intent to Bid Request to '+invitedBidder+'? By selecting OK an email will be sent to this bidder requesting them to login to M6 and indicate their Intent to Bid on this RFP.</strong><span class="data-fc-item-id" style="display:none;">'+item_id+'</span><span class="data-rfp-id" style="display:none;">'+rfp_id+'</span></div>');*/
        jQuery.post("/send-request-by-sms/" + rfp_id + '/' + item_id, {js: 1, 'invited-bidder': invitedBidder, 'phoneNo' : phoneNo, 'package_id' : package_id, 'bidder_id' : bidder_id})
                .done(function (data) {
                    console.log(data.html);
                    // jQuery("#request_to_intent_dialog").html(data.html);
                    // jQuery("#request_to_intent_dialog").dialog('open');
                });

        return false;
    });

});