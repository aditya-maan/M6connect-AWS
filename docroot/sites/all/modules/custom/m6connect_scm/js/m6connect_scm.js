Drupal.ajax.prototype.commands.emojinetexteditorscm = function(ajax, response, status) {
  jQuery(".text-message-smilly").emojioneArea({
   container: ".message-abc-cont",
   hideSource: true,
   useSprite: false,
   saveEmojisAs: "image",
   imageType: "png",
   shortnames: false,
   filtersPosition: "bottom",
   placeholder: 'Enter your message here...',
   });

  var container = jQuery("body").find("#user-messaging-thread-form-container .message-box-main-container"); 
  if(container.length){
    container.animate({scrollTop: container[0].scrollHeight}, "slow"); 
  }
}


Drupal.ajax.prototype.commands.changeMiniMenuActive = function(ajax, response, status) {
  // Changing evaluate link dynamically.
  if (jQuery('.switch-scorecard-menus').length > 0 && status === 'success') {
    var data = response.arguments.data;
    var prev_element = jQuery('.switch-scorecard-menus.active');
    var new_element = jQuery('.switch-scorecard-menus[data="' + data + '"]');

    // Remove active classes from previous element and add to new element.
    if (prev_element) {
      prev_element.removeClass('active');
      prev_element.parent().removeClass('active');
    }

    if (new_element) {
      new_element.addClass('active');
      new_element.parent().addClass('active');
    }
  }
}

Drupal.behaviors.bform = {
  attach : function(context, settings) {
    var events = jQuery('.project-form-search-form-ajax').clone(true).data('events');
    jQuery('.project-form-search-form-ajax').unbind('keyup');
    var typingTimer;
    var doneTypingInterval = 300;

    jQuery('.project-form-search-form-ajax').on('keyup', function (e) {
      clearTimeout(typingTimer);
      if (jQuery(this).val) {
        var trigid = jQuery(this);
        typingTimer = setTimeout(function(){                    
          trigid.triggerHandler('finishedinput');
        }, doneTypingInterval);
      }
    });
  }
};



Drupal.behaviors.m6connect_scm = {
  attach: function (context, settings) {
    var getPath = window.location.pathname;
    var parameters = [];

    jQuery('.numbersOnly').keyup(function () { 
      this.value = this.value.replace(/[^0-9\.]/g,'');
    });

    jQuery('.switch-scorecard-menus').unbind('click').bind('click', function(event) {
      /* Act on the event */
      event.preventDefault();

      var data_item = jQuery(this).attr('data');
      jQuery('.casemanager_change_menu_item').val(data_item).trigger('change');
    });


  if (jQuery('.table-cat-scm-settings').length > 0) {
    // Removing the width attribute on category tables, because when a 
    // datatable is rendered hidden, it sets it width as 0px.
    if (jQuery('.table-cat-scm-settings').css('width') != null) {
      jQuery('.table-cat-scm-settings').css('width', '');
    }
  }

  /*
   *  Start working for my request page
   */ 
  if(getPath == '/scm/settings/locations-region' || getPath == '/scm/settings/locations-entity' || 
    getPath == '/scm/settings/locations-buildings' || getPath == '/scm/settings/user-database') {
    jQuery('.edit_scm_requests_detail').unbind('click').bind('click', function (e) { 
      if(getPath == '/scm/settings/locations-region'){
        var nodeClass = 'scm-setting-location-region-node-nid';
      }
      if(getPath == '/scm/settings/locations-entity'){
        var nodeClass = 'scm-setting-location-region-node-nid';
      }
      if(getPath == '/scm/settings/locations-buildings'){
        var nodeClass = 'scm-setting-location-buildings-node-nid';
      }
      if(getPath == '/scm/settings/user-database'){
        var nodeClass = 'scm-setting-user-database-node-nid';
      }
      e.preventDefault();
      var commitmentID = jQuery(this).attr('for');
      console.log(commitmentID);
      jQuery('.get-my-requests').val(commitmentID).trigger('change');
      jQuery('.'+nodeClass).val(commitmentID);
      jQuery('html, body').animate({
            scrollTop: "0px"
         }, 800); 
      }); 

    jQuery('.new-record-link').click(function (e) {
        e.preventDefault();
        jQuery('.reset-callback').trigger('change');
    });
   }


  if(getPath == '/scm/settings') {
    jQuery('.edit-subtypeaction-cat-call').unbind('click').bind('click', function (e) {
      e.preventDefault();
      var eid = jQuery(this).attr('dataedit-subtyperef');
      jQuery('select.get-subtypeedit-settings').val(eid).trigger('change');
    });
    jQuery('.edit-NECaction-cat-call').unbind('click').bind('click', function(event) {
      var editids = jQuery(this).attr('dataedit-necref');
      jQuery('select.get-editlineitem_nec-settings').val(editids).trigger('change');
    });
    jQuery('.edit-depaction-cat-call').unbind('click').bind('click', function (e) {
      e.preventDefault();
      var eid = jQuery(this).attr('dataedit-depref');
      jQuery('select.get-editdepartment-settings').val(eid).trigger('change');
    });
    
    jQuery('.remove-scm-setting-options-subtype').unbind('click').bind('click', function(event) {
      /* Act on the event */
      var cur_ele = jQuery(this);
      var name = jQuery(this).attr('data');
      var iddel = jQuery(this).attr('deletedataref');
      var classes = this.className;
      var classes_split = classes.split(' ');
      var service = jQuery(this).attr('scm-type');
      jQuery('.remove-data-details-service-subtype').text(service);
      jQuery('.remove-data-details-name-subtype').text(name);
      jQuery('#scm-option-remove-subtype').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to remove ' + name + '?</strong></p></div><div class="remove-subtype-ID" style="display:none;">'+iddel+'</div>');
      jQuery('#scm-option-remove-subtype').dialog('open');
    });
    jQuery('#scm-option-remove-subtype').dialog({
       autoOpen: false,
       width: 490,
       modal: true,
       resizable: false,
       buttons: {
         'Yes': function () {
            var service = jQuery('.remove-data-details-service-subtype').text();
            var name = jQuery('.remove-data-details-name-subtype').text();
            var catid = jQuery('.remove-subtype-ID').text();
            jQuery('.get-subtypedelete-settings').val(catid).trigger('change');
            jQuery('.remove-data-details-service-subtype').text('');
            jQuery('.remove-data-details-name-subtype').text('');
            jQuery(this).dialog("close");
          },
          'Cancel': function () {
            jQuery('.remove-data-details-service-subtype').text('');
            jQuery('.remove-data-details-name-subtype').text('');
            jQuery(this).dialog("close");
          }
        },
        open: function () {
          jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
          jQuery('.ui-dialog-titlebar').hide();
        }
    });
  }

  if(getPath == '/propose/settings/scorecard') {
    jQuery(".ui-dialog-titlebar").hide();
  // jQuery('.edit-action-cat-call').unbind('click').bind('click', function (e) {
    
  // });

  jQuery('.scorecard-question-update-Close').unbind('click').bind('click', function (e) {
    jQuery("#updateboxpopup").dialog('close');
  });

    jQuery(".customfiled legend").click(function() {
      if(jQuery(this).find('.fieldset-wrapper').is(":visible")){
        jQuery(this).parent().addClass('collapsed');
        jQuery(this).find('.fieldset-wrapper').hide();
      } if(jQuery(this).find('.fieldset-wrapper').is(":hidden")){
        jQuery(this).parent().removeClass('collapsed');
        jQuery(this).find('.fieldset-wrapper').show();
      }
    });

    

    // jQuery('.edit-action-cat-call').unbind('click').bind('click', function (e) {
    //   jQuery('select.get-scorecard-questio-settings-edit').val(jQuery(this).attr('dataedit-ref')).trigger('change');
    //   getcatform();
    // });
    jQuery('.remove-scm-setting-options').unbind('click').bind('click', function (e) {
        e.preventDefault();
        parameters['type'] = 'cat-scorcat';
        parameters['ID'] = jQuery(this).attr('deletedataref');
        parameters['selector'] = '.get-scorecard-cat-delete';
        parameters['trigerselect'] = 'get-scorecard-cat-delete';
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle');+'?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
      });

    jQuery('.delete-action-cat-call').unbind('click').bind('click', function (e) {
        e.preventDefault();
        parameters['type'] = 'cat-scorquscat';
        parameters['ID'] = jQuery(this).attr('datadelete-ref');
        parameters['selector'] = '.get-scorecard-questio-settings-delete';
        parameters['trigerselect'] = 'get-scorecard-questio-settings-delete';
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle');+'?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
      });    
  }
    
  if(getPath == '/scm/settings'|| getPath == '/scm/settings/project') {
      jQuery('.remove-scm-setting-options').unbind('click').bind('click', function(event) {
        /* Act on the event */
        var cur_ele = jQuery(this);
        var name = jQuery(this).attr('data');
        var classes = this.className;
        var classes_split = classes.split(' ');
        var service = jQuery(this).attr('scm-type');

        jQuery('.remove-data-details-service').text(service);
        jQuery('.remove-data-details-name').text(name);

        jQuery('#scm-option-remove').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to remove ' + name + '?</strong></p></div>');
        jQuery('#scm-option-remove').dialog('open');
      });
      
      jQuery('.edit-section-group').click(function (e) {
        var curnt_id = jQuery(this).attr('id');
        var reqtype_val1 = curnt_id.replace("edit-section--", "");
        jQuery('.'+curnt_id+' .field-group-Input').show();
        jQuery('.'+curnt_id+' .field-inner-group').show();
        jQuery('.'+curnt_id+' .field-inner-valuefield').hide()
        jQuery('#'+curnt_id).hide();
        jQuery('#cancle-section--'+reqtype_val1).show();
      }); 

      jQuery('.cancle-section-group').click(function (e) {
        var curnt_cid = jQuery(this).attr('id');
        var reqtype_val1 = curnt_cid.replace("cancle-section--", "");
        jQuery('.edit-section--'+reqtype_val1+' .field-group-Input').hide();
        jQuery('.edit-section--'+reqtype_val1+' .field-inner-group').hide();
        jQuery('.edit-section--'+reqtype_val1+' .field-inner-valuefield').show();
        jQuery('#'+curnt_cid).hide();
        jQuery('#edit-section--'+reqtype_val1).show();
      }); 
      jQuery('.scm-settings-select-fields-type').change(function () {
        var selectedid = jQuery(this).attr('dataref');
        var selectedval = jQuery(this).attr('value');
        var selected_valid = selectedid.replace("options_id_data_", "");
        if(selectedval=='checkbox' || selectedval=='select') {
          jQuery('.optionsdata_id_data_'+selected_valid).show();
        } else{
          jQuery('.optionsdata_id_data_'+selected_valid).hide();
        }
      });

      jQuery('#add-field-for-settings .scm_setting_field_file_type').change(function () {
        var selectedval = jQuery(this).attr('value');
        if(selectedval=='checkbox' || selectedval=='select') {
          jQuery('.scm_setting_field_option_container').show();
        } else{
          jQuery('.scm_setting_field_option_container').hide();
        }
      });
      jQuery('.field_delete_single_formfield').unbind('click').bind('click', function (e) {
        e.preventDefault();
        var id = jQuery(this).attr('delete_ifref');
        jQuery('select.list_of_fields').val(id).trigger('change');
      });
      jQuery('.group_delete_single_formgroup').unbind('click').bind('click', function (e) {
        e.preventDefault();
        var id = jQuery(this).attr('delete_ifref');
        jQuery('select.list_of_groups').val(id).trigger('change');
      });

      jQuery('.edit-action-cat-call').unbind('click').bind('click', function (e) {
        e.preventDefault();
        var eid = jQuery(this).attr('dataedit-ref');
        console.log(eid);
        jQuery('select.edit-action-cat-call-select').val(eid).trigger('change');
      });

      jQuery('.delete-action-dep-call').unbind('click').bind('click', function (e) {
        e.preventDefault();
        parameters['type'] = 'cat-depsubcat';
        parameters['ID'] = jQuery(this).attr('datadelete-depref');
        parameters['selector'] = '.get-deldepartment-settings';
        parameters['trigerselect'] = 'get-deldepartment-settings';
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle');+'?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
      });

     
      
      jQuery('.delete-action-cat-call').unbind('click').bind('click', function (e) {
        e.preventDefault();
        parameters['type'] = 'cat-subcat';
        parameters['ID'] = jQuery(this).attr('datadelete-ref');
        parameters['selector'] = '.delete-action-cat-call';
        parameters['trigerselect'] = 'delete-action-cat-call-select';
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle');+'?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
      });

      jQuery('.remove-scm-setting-options-NEC').unbind('click').bind('click', function(event) {
        parameters['type'] = 'nec';
        parameters['ID'] = jQuery(this).attr('deletenecref');
        parameters['selector'] = '.remove-scm-setting-options-NEC';
        parameters['trigerselect'] = 'get-dellineitem_nec-settings';
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle');+'?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
      });

      jQuery('.remove-scm-setting-options-UOM').unbind('click').bind('click', function(event) {
        parameters['type'] = 'uom';
        parameters['ID'] = jQuery(this).attr('deletenecref');
        parameters['selector'] = '.remove-scm-setting-options-UOM';
        parameters['trigerselect'] = 'get-dellineitem_uom-settings';
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle');+'?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
    });



      jQuery('a.new-field-link').unbind('click').bind('click', function (e) {
        e.preventDefault();
        if(jQuery(this).attr('forclick')=='closeform'){
          jQuery(this).attr('forclick','openform');
          jQuery('.region-top-header-add-field_1').show()
        } else if(jQuery(this).attr('forclick')=='openform'){
          jQuery(this).attr('forclick','closeform');
          jQuery('.region-top-header-add-field_1').hide();
        }
      });
      jQuery('a.new-group-link').unbind('click').bind('click', function (e) {
        e.preventDefault();
        if(jQuery(this).attr('forclick')=='closeform'){
          jQuery(this).attr('forclick','openform');
          jQuery('.region-top-header-add-field_2').show()
        } else if(jQuery(this).attr('forclick')=='openform'){
          jQuery(this).attr('forclick','closeform');
          jQuery('.region-top-header-add-field_2').hide();
        }
      });

      jQuery('a.remove_catidmarkup').unbind('click').bind('click', function (e) {
        e.preventDefault();
        var did = jQuery(this).attr('cleck_delete-ref');
        var delisds = jQuery('input.category_maincatdelete_ids').val(jQuery('input.category_maincatdelete_ids').val() + did + ', ');
        jQuery(this).closest('.category-data-item').remove();
      });

    }

    var format = function (num) {
          var str = num.toString().replace("$", ""), parts = false, output = [], i = 1, formatted = null;
          str = str.replace("-", ""), parts = false, output = [], i = 1, formatted = null;
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
          if(num.toString().indexOf("-") != -1) {
            return("$-" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));                        
          }
          else {
            return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));  
          }
          
       };


  function ationalllevepage(){
    jQuery('a').click(function (e) {
      var href = jQuery(this).attr('href');
      var  varleaveidsction = false;

      if (!href.match("^#")) {
        if (jQuery(this).attr('target')!=='_blank') {
          if (jQuery(this).hasClass('ctools-use-modal')===false) {
            if (jQuery(this).attr('dataaction')!='triggercall' ) {
              varleaveidsction = true;
              e.preventDefault();
              ShowCustomDialog('Do you want to leave this page without saving?',href,'link');
            }
          }
        }
      }
    });
  }

  if(getPath == '/scm/my-request') {
    jQuery('.workflow-action-actionselect').change(function (e) {
      var currentID = jQuery(this).parent( ".form-type-select" ).parent( ".prant_class_action_additem" ).attr('id');
      jQuery('#'+currentID+' #dLabel').text(jQuery(this).val());
    });

    
    jQuery('input.purchase_uom_conversion').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
      if(jQuery('.uom_conversion').val()!=""){
        var uomcon = jQuery('.uom_conversion').val();
        var upmper = jQuery(this).val().replace('$','').replace(',','');
        var pricecon= (upmper/uomcon).toFixed(2);
        jQuery('#get_price_each_'+jQuery(this).attr('datarow')).text('$'+pricecon);
      }
    });

    jQuery('input.uom_conversion').keyup(function (i) {
      var row = jQuery(this).attr('datarow');
      if(jQuery('input.purchase_uom_conversion[datarow="'+row+'"]').val()!=""){
        var upmper = jQuery('input.purchase_uom_conversion[datarow="'+row+'"]').val().replace('$','').replace(',','');
        var uomcon = jQuery(this).val();
        var pricecon= (upmper/uomcon).toFixed(2);
        jQuery('#get_price_each_'+jQuery(this).attr('datarow')).text('$'+pricecon);
      }
    });

    if(jQuery('.my-request-node-nid').val() !== '') {
      ationalllevepage();
      jQuery('input.price_each').each(function (i) {
        jQuery(this).val(jQuery(this).val()).trigger("keyup");
      });
      jQuery('input.purchase_uom_conversion').each(function (i) {
        jQuery(this).val(jQuery(this).val()).trigger("keyup");
      });
    }

    jQuery('.removdeletefile a').attr('target', '_blank');
    jQuery('input:checkbox.image-remove-update').unbind('click').bind('click',function (e) {
        var getFid = jQuery(this).val();
        var nodeId = jQuery(this).attr('for');
        parameters['type'] = 'attachments';
        parameters['nid'] = nodeId;
        parameters['FID'] = getFid;
        parameters['trigerselect'] = 'scm-my-request-listattch';
        console.log(parameters);
        var content = 'Are you sure you want to remove '+jQuery(this).attr('fortitle')+' ?';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','delete');
        // parameters['trigerselect'] = 'scm-my-request-listattch';   
    });
  }

  if(getPath == '/scm/my-project') {
    if(jQuery('.scm-project-node-nid').val()!=='') {
      ationalllevepage();
    }

    jQuery('.scm-project-title').keyup(function (e) {
      var getTitle = jQuery(this).val();
      //var ProNumber = jQuery('.project_programe_main_pro').val();
      var ProNumber = 0;
      jQuery.post( '/check-title-availablity/'+ getTitle +'/scm-project/'+ProNumber, function( data ) { 
        if(data.access == '0') {
          jQuery('.project-avail-status-title .text-danger').text(data.message);
          jQuery('.project-avail-status-title .text-success').text('');
          jQuery('.custom-submit-project-button input').attr('disabled','disabled');
          jQuery('input.scm-project-checkalready').val('1');
        }
        if(data.access == '1') {
          jQuery('input.scm-project-checkalready').val('');
        jQuery('.project-avail-status-title .text-danger').text('');  
          //jQuery('.project-avail-status .text-success').text(data.message);
        jQuery('.project-avail-status-title .text-success').text('');
        jQuery('.custom-submit-project-button input').removeAttr('disabled');
        }     
      });
    });
  }

  if(getPath == '/scorecard/my-scorecards' || getPath == '/scm/scorecard/my-scorecards' || getPath == '/scorecard/new') {
    
    jQuery('.edit-scorecard', context).click(function (e) {
      e.preventDefault()
      var commitmentID = jQuery(this).attr('for');
      jQuery('.project_scorecard_main_pro').val(commitmentID).trigger('change');
      jQuery('html, body').animate({scrollTop: "0px"}, 800);
    });

  jQuery('.scorecard-name-title-evaluate', context).change(function (e) {
    e.preventDefault()
    var title_value = jQuery(this).val();
    jQuery('.project_scorecard_main_pro').val(title_value).trigger('change');
  });
  
  jQuery('.scorecard-name-title-evaluate').val(jQuery('.project_scorecard_main_pro').val());


    
    // jQuery('.project-form-search-form-ajax').on('keyup', function() {
    //   var valueajax = jQuery(this).val();
    //   jQuery.ajax({
    //          type: 'POST',
    //          url: '/project-form-search-form-ajaxcall',
    //          data: {valueajax : valueajax},
    //          success:function(output) { }
    //        });
    // });
 
  
  }
  
  jQuery('#myInput').on('keyup', function() {
      var value = jQuery(this).val();
      var patt = new RegExp(value, "i");
      var varcnt = 0;
      jQuery('.m6connect-custom-table').find('tbody tr').each(function() {
        if(!(jQuery(this).find('td').text().search(patt) >= 0)) {
          jQuery(this).not('thead').hide();
        }
        if((jQuery(this).find('td').text().search(patt) >= 0)) {
          varcnt++;
          jQuery(this).show();
        }
      });
      console.log(varcnt);
      jQuery('span.countdatapr').text(varcnt);
    });

  function getUrlParameter(name) {
    name = name.replace(/[\[]/, '\\[').replace(/[\]]/, '\\]');
    var regex = new RegExp('[\\?&]' + name + '=([^&#]*)');
    var results = regex.exec(location.search);
    return results === null ? '' : decodeURIComponent(results[1].replace(/\+/g, ' '));
  }

  if(getPath == '/scm/my-request' || getPath == '/scm/my-project' || getPath == '/scm/archive') {
    if(getPath == '/scm/my-project') {
      if(getUrlParameter('pid')!=''){
        jQuery('#program_scm_main_container').attr('for','open');
        jQuery('#program_scm_main_container').attr('data','edit');
        jQuery('#program_scm_main_container').show();
        jQuery('.custom-action-button-div').show(); 
        jQuery('.get-scm_projects_scp').val(getUrlParameter('pid')).trigger('change');
        jQuery('.scm-project-node-nid').val(getUrlParameter('pid'));
      }

    }

    if(jQuery('.messages.error').length) {
         _form_show_hide_calling('closed','my-project');
    }

    if(jQuery('.scm-project-node-nid').val()=='') {
      jQuery(".category-informations-main-sub").attr('disabled', 'disabled');  
    }

    jQuery('.category-informations-main').change(function (e) {
        jQuery('.category-informations-main-sub').val('').change();
        var mainCat = jQuery(this).val();
        jQuery(".category-informations-main-sub option").each(function () {
          var getVal = jQuery(this).val();
          var getCat = getVal.split('-');
        if (getCat[0] == mainCat) {
          jQuery(this).show();
          jQuery(".category-informations-main-sub").removeAttr('disabled');
        } else {
          jQuery(this).hide();
        }
      });  
    });

    jQuery('.toggle-scm-vendor-section').unbind('click').bind('click', function(event) {
      /* Act on the event */
      jQuery('.toggle-this-container').toggle(500);
    });

    jQuery('.vendor_group_default input.same-as-manufacturer_field').on('click',function () {
     if (jQuery('.vendor_group_default input.same-as-manufacturer_field').is(':checked')) {
        jQuery('.vendor_group_default .choose-company_field').val(jQuery('.manufacturer_group_default .choose-company_field').val());
        jQuery('.vendor_group_default .catalog-number_field').val(jQuery('.manufacturer_group_default .catalog-number_field').val());
        jQuery('.vendor_group_default .contact-name_field').val(jQuery('.manufacturer_group_default .contact-name_field').val());
        jQuery('.vendor_group_default .contact-email_field').val(jQuery('.manufacturer_group_default .contact-email_field').val());
        jQuery('.vendor_group_default .contract-number_field').val(jQuery('.manufacturer_group_default .contract-number_field').val());
        jQuery('.vendor_group_default .contact-phone_field').val(jQuery('.manufacturer_group_default .contact-phone_field').val());
        jQuery('.vendor_group_default .choose-company_field_nid').val(jQuery('.manufacturer_group_default .choose-company_field_nid').val());            
      } else {
         jQuery('.vendor_group_default .choose-company_field').val('');
        jQuery('.vendor_group_default .catalog-number_field').val('');
        jQuery('.vendor_group_default .contact-name_field').val('');
        jQuery('.vendor_group_default .contact-email_field').val('');
        jQuery('.vendor_group_default .contract-number_field').val('');
        jQuery('.vendor_group_default .contact-phone_field').val('');
        jQuery('.vendor_group_default .choose-company_field_nid').val('');
      }
    });

    jQuery("div.msg-connected-user-info").unbind('click').bind('click',function(e) {
         refreshMessageFlag = 0;
         var mappindId = jQuery(this).attr("id");
         var currmappinid = jQuery(".connected-user-select.form-select").val();
        if(mappindId!=currmappinid){
           jQuery(".connected-user-select.form-select").val(mappindId).trigger("change");
           jQuery('body').find("div.msg-connected-user-info").removeClass("user-active");
           jQuery('#'+mappindId).addClass("user-active");
        }
        jQuery('body').find("div.msg-connected-user-info").removeClass("user-active");
        if(!jQuery(this).hasClass("user-active")){
           jQuery(this).addClass("user-active");  
        }
    });

    jQuery('.request_maintype_new').change(function () {
      var mainType = jQuery(this).val();
      if (mainType) {
        jQuery('.request_subtype_new').removeAttr('disabled');
      }
      else {
        jQuery('.request_subtype_new').attr('disabled', true);
      }
    });

    // For my request page for image attahment functionality
    jQuery('.scm-my-request-attachment-link').unbind('click').bind('click',function (e) {
      e.preventDefault();
      jQuery('.scm-my-request-attachment').trigger('click');
    });

    jQuery('.custom-reset-button-schedule').click(function (e) {
      var status = jQuery('#program_scm_main_container').attr('for');
      jQuery('#program_scm_main_container').hide(500);
      jQuery('#program_scm_main_container').parents('form').removeClass('scm-my-request-form-border');
      jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').removeClass('margin-top-10');
      jQuery('.custom-action-button-div').hide();
      jQuery('#program_scm_main_container').attr('for', 'closed');
      jQuery('#alert-container-section').hide();
      jQuery('#alert-container-section1').hide();
      jQuery('.scm_chatting_container-main').hide();
    });

    jQuery('.edit_scm_requests_detail').unbind('click').bind('click', function (e) {
      e.preventDefault();
      jQuery('#program_scm_main_container').attr('for','open');
      jQuery('#program_scm_main_container').attr('data','edit');
      jQuery('#program_scm_main_container').show(500);
      jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
      jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
      jQuery('.custom-action-button-div').show();

      var commitmentID = jQuery(this).attr('for');
      
      if(getPath == '/scm/my-request') {
        if (jQuery('.my-request-node-nid').val() != '' ) {
          if (jQuery(this).attr('dataaction') == 'triggercall') {
            e.preventDefault();
            ShowCustomDialog('Do you want to leave this page without saving?','edit_scm_requests_detail','ajax',commitmentID);
          }
        } else {
          jQuery('.get-my-requests').val(commitmentID).trigger('change');
          jQuery('.my-request-node-nid').val(commitmentID);
          jQuery('html, body').animate({scrollTop: "0px"}, 800);
        }
      } else {
          jQuery('.get-my-requests').val(commitmentID).trigger('change');
          jQuery('.my-request-node-nid').val(commitmentID);
          jQuery('html, body').animate({scrollTop: "0px"}, 800);
      }  



      if(getPath == '/scm/my-project') {
        if(jQuery('.scm-project-node-nid').val()!='' ) {
          if(jQuery(this).attr('dataaction')=='triggercall') {
            e.preventDefault();
            ShowCustomDialog('Do you want to leave this page without saving?','edit_scm_requests_detail2','ajax');
          } 
        } else {
          jQuery('.get-scm_projects_scp').val(commitmentID).trigger('change');
          jQuery('.scm-project-node-nid').val(commitmentID);
          jQuery('html, body').animate({scrollTop: "0px"}, 800);
        }
      } else {
          jQuery('.get-scm_projects_scp').val(commitmentID).trigger('change');
          jQuery('.scm-project-node-nid').val(commitmentID);
          jQuery('html, body').animate({scrollTop: "0px"}, 800);
      }
    });

    if (getPath == '/scm/my-request' || getPath == '/scm/archive') {
      var reqtype_val = jQuery('select.scm-my-request-request-type').val();

      if (reqtype_val) {
        var reqtype_val1 = reqtype_val.split("-");

        if (reqtype_val1[1] == 1) {
          jQuery('#alert-container-section').show();
          jQuery('#alert-container-section1').show(); 
          jQuery('#alert-container-section').addClass('show');
          jQuery('#alert-container-section1').addClass('show');
        }
        else {
          jQuery('#alert-container-section').removeClass('show');
          jQuery('#alert-container-section1').removeClass('show');
        }
     }

      jQuery('.scm-my-request-request-type').change(function () {
        var reqtype_val = jQuery(this).val();
        if (reqtype_val) {
          var reqtype_val1 = reqtype_val.split("-");
          if (reqtype_val1[1] == 1) {
            jQuery('#alert-container-section').show();
            jQuery('#alert-container-section1').show();
          }
          else if (reqtype_val1[1] == 0) {
            jQuery('#alert-container-section').hide();
            jQuery('#alert-container-section1').hide();
          }
        }
      });

      jQuery('.m6top-logout-user-forrequester-link').unbind('click').bind('click', function(event) {
        jQuery('select.logout-callback').trigger('change');
      });

      jQuery('.new-record-requester').unbind('click').bind('click', function(event) {
        jQuery('select.reset-callback').trigger('change');
      });
    }

    if (getUrlParameter('new') && getUrlParameter('new')==='open') {
      var status = jQuery('#program_scm_main_container').attr('for');
      _form_show_hide_calling(status,'my-request');
    }

    if(getPath == '/scm/my-project') {
          jQuery('.new-record-link').unbind('click').bind('click', function (e) {
            e.preventDefault();

            if(jQuery('.scm-project-node-nid').val()!='' ) {
              if(jQuery(this).attr('dataaction')=='triggercall') {
                e.preventDefault();
                ShowCustomDialog('Do you want to leave this page without saving?','new-record-link','ajax');
              }  
            } else {
              var status = jQuery('#program_scm_main_container').attr('for');
              _form_show_hide_calling(status,'my-project');
            }
            jQuery('.scm_projects_scp_form').removeClass('scm-my-request-form-border');
            
            //jQuery('#program_scm_main_container').parents('.nbdr').addClass('scm-my-request-form-border');

            if(jQuery('#program_scm_main_container').attr('for')=='closed'){
              jQuery('#program_scm_main_container').parents('.nbdr').removeClass('scm-my-request-form-border');
              jQuery('.nbdr').removeClass('margin-top-20');
            }else{
              jQuery('#program_scm_main_container').parents('.nbdr').addClass('scm-my-request-form-border');
              jQuery('.nbdr').addClass('margin-top-20');
            }

            console.log(jQuery('#program_scm_main_container').attr('for'));

            // var status = jQuery('#scm_projects_scp_form_container').attr('for');           
            // _form_show_hide_calling(status,'my-project');
            
         });
      }

    if(getPath != '/scm/my-project') { 
      jQuery('.new-record-link').unbind('click').bind('click', function (e) {
        e.preventDefault();
        
        if(getPath == '/scm/archive'){
          window.location.href = "/scm/my-request?new=open";
        }

        if (getPath == '/scm/my-request') {
          if (jQuery('.my-request-node-nid').val() != '') {
            if(jQuery(this).attr('dataaction')=='triggercall') {
              e.preventDefault();
              ShowCustomDialog('Do you want to leave this page without saving?','new-record-link','ajax');
            }
          }
          else {
            var status = jQuery('#program_scm_main_container').attr('for');
            _form_show_hide_calling(status,'my-request');
          }
        }
        else {
          var status = jQuery('#program_scm_main_container').attr('for');
          _form_show_hide_calling(status,'my-request');
        }
      });
    }
  }


 jQuery('#scm-option-remove').dialog({
     autoOpen: false,
     width: 490,
     modal: true,
     resizable: false,
     buttons: {
       'Yes': function () {
         var service = jQuery('.remove-data-details-service').text();
         var name = jQuery('.remove-data-details-name').text();
         jQuery('.rating-data-item').each(function(index, el) {
           if (jQuery(this).find('.remove-scm-setting-options').attr('data') == name) {
             // Hide this element.
             jQuery(this).hide(700);
           }
         });
     
     jQuery.ajax({
           type: 'POST',
           url: '/remove-scm-setting-options',
           data: {setting : service, name : name},
           success:function(output) { }
         });
         jQuery('.remove-data-details-service').text('');
         jQuery('.remove-data-details-name').text('');
         jQuery(this).dialog("close");
        },
        'Cancel': function () {
          jQuery('.remove-data-details-service').text('');
          jQuery('.remove-data-details-name').text('');
          jQuery(this).dialog("close");
        }
      },
      open: function () {
        jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
        jQuery('.ui-dialog-titlebar').hide();
      }
    });

   /**
    * scm chatting start
    */
    if(getPath == '/scm/chatting') {
      jQuery(".add-new-member-box").autocomplete({
        minLength: 0,
        source: function( request, response ) {
          jQuery.getJSON( "/scm-user-search-ajax", {
            term: request.term,
            mapping_id: jQuery('input.messaging-mapping-mapping').val(),
          }, response );
        },
        focus: function( event, ui ) {
          return false;
        },
        change: function(event, ui) {
          jQuery(this).val('');
        },
        select: function( event, ui ) {
          var userUid = ui.item.value;
          if(userUid!=''){
            userUid = parseInt(userUid);
            var invitedUser = jQuery('input.add-new-member-users').val();
            var invitedUserArr = [];
            if(invitedUser !=''){
              invitedUserArr = invitedUser.split(",").map(Number);
            }
            if((jQuery.inArray(userUid,invitedUserArr))===-1){
              invitedUserArr.push(userUid);
              invitedUserArr.map(Number);
              invitedUser = invitedUserArr.join();
              jQuery('input.add-new-member-users').val(invitedUser);
              jQuery('.add-new-member-markup').append('<div class="message-invited-sub pull-left label label-success" style="margin-right:10px;font-size: 12px;"><span class="message-invited-username">'+ui.item.label+'</span><span class="message-invited-user-remove">&nbsp;<a href="javascript:void(0);" class="message-invited-user-remove-link" data-useruid="'+userUid+'"><i class="fa fa-times-circle" style="font-size: 14px;color: #ffffff;"></i></a></span></div>');
              jQuery(this).val('');
            }
          }
          return false;
        }
      }).data("ui-autocomplete") ._renderItem = function( ul, item ) {
        var inner_html = '<a><div class="list_item_container-auto"><span class="image">' + item.image + '</span><span><label>' + item.label + '</label></span></div></a>';
        return jQuery( "<li>" ).data("item.autocomplete", item).append( inner_html ).appendTo( ul );
      };
    }
    /*
    * scm chatting end
    */    
    /*
    *change project category get subcategory options
    */  
      // jQuery('.scm-project-subcategory option').each(function(){
      //   if(jQuery(this).text()!='- Select Subcategory -'){
      //       jQuery(this).hide();
      //   }
      // });  
  
      // jQuery('.scm-project-category').change(function(e){
      //   var getCatid = jQuery(this).val();
      //   jQuery('.scm-project-subcategory option').each(function(){
      //     if(jQuery(this).text()!='- Select Subcategory -'){
      //       jQuery(this).hide();
      //     }
      //     var getsubvalue = jQuery(this).attr('value');
      //     if(getsubvalue.indexOf(getCatid+"-") >= 0) {
      //       jQuery(this).show();
      //     }
      //   });
      // });

    // jQuery('select.scm-project-category').each(function(e){
    //   var getCatid = jQuery(this).val();  
    //   if(getCatid){
    //     if(jQuery(this).attr('subcat')){
    //       var subcat = jQuery(this).attr('subcat');
    //       newsubcat = subcat.split(',');
    //       jQuery('.scm-project-subcategory').val(newsubcat).trigger('change');
    //       //jQuery(this).attr('subcat','');
    //     }      
    //   }
    // });
    //   jQuery('select.scm-project-category').change(function(e){   
    //     var getCatid = jQuery(this).val();
    //     console.log(getCatid);
    //     if(getCatid) {    
    //       jQuery.post( '/getprojectdata/project/'+getCatid, function( data ) {           
    //         if(data != 0 && data) {
    //           jQuery('.scm-project-subcategory').empty();
    //           jQuery.each(data,function(key, value) {
    //            var opt = jQuery('<option>');
    //            opt.val(key).text(value);
    //            opt.appendTo('.scm-project-subcategory');
    //           });
    //         }
    //       })
    //     } else {
    //       jQuery('.scm-project-subcategory').empty();
    //     } 
    //   });    


    jQuery('.edit-main-cat-scm').unbind('click').bind('click', function(event) {
      /* Act on the event */
      event.preventDefault();
      var cat_id = jQuery(this).attr('data');
      jQuery('.all-main-cats-select').val(cat_id).trigger('change');
    });
  }
};



jQuery(document).ready(function(e) {
  var getPath = window.location.pathname; 

  jQuery('.new-record-requester').unbind('click').bind('click', function(event) {
        jQuery('select.reset-callback').trigger('change');
      });

  if (jQuery('.table-cat-scm-settings').length > 0) {
    // Removing the width attribute on category tables, because when a 
    // datatable is rendered hidden, it sets it width as 0px.
    if (jQuery('.table-cat-scm-settings').css('width') != null) {
      jQuery('.table-cat-scm-settings').css('width', '');
    }
  }

  if (jQuery('.requesterdata_outer-login').length && jQuery('.my-request-node-nid').val() == '') {
    _form_show_hide_calling('open','my-request');
    jQuery('.scm_chatting_container-main').hide();
  }


  // scm chatting start
  if(getPath == '/scm/my-request') {
    // if (jQuery('.my-request-node-nid').val()) {
    //   jQuery('#program_scm_main_container').attr('for','open'); 
    //   jQuery('#program_scm_main_container').show(500);
    //   jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
    //   jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
    //   jQuery('.custom-action-button-div').show();

    //   var reqtype_val = jQuery('.scm-my-request-request-type').val();
    //   var reqtype_val1 = reqtype_val.split("-");

    //   if(reqtype_val1[1] == 1) {
    //     jQuery('#alert-container-section').show();
    //     jQuery('#alert-container-section1').show();   
    //   }
    //   else if(reqtype_val1[1]==0) {
    //     jQuery('#alert-container-section').hide();
    //     jQuery('#alert-container-section1').hide();  
    //   }

    //   jQuery('select.scm-my-request-entity').trigger('change');
    //   jQuery('select.scm-my-request-department').trigger('change');
    // } 

    if(jQuery('input.userdb-base-request').length && jQuery('input.userdb-base-request').val() != '') {
          jQuery('.get-my-requests').val(jQuery('input.userdb-base-request').val()).trigger('change');
    }
  }

  // Ajax send and complete functions.
    /*
     *  Adding UI block for please wait
     */
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url; 
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData")) {
        var ele_name = ajaxOptions.extraData._triggering_element_name;

        if (ele_name === "get-my-requests"||
          ele_name === "workflow_add_new_row" ||
          ele_name === "remove_lineItem" ||
          ele_name === "reset-callback" ||
          ele_name === "get-location-region-settings" ||
          ele_name === "get-location-entity-settings" ||
          ele_name === "get-location-buildings-settings" ||
          ele_name === "get-user-database-settings" ||
          ele_name === "get-catedit-settings" ||
          ele_name === "get-catdelete-settings" ||
          ele_name === "list_of_fields" ||
          ele_name === "get-scm_projects_scp" ||
          ele_name === "get-subtypeedit-settings" ||
          ele_name === "get-dellineitem_nec-settings" ||
          ele_name === "get-editlineitem_nec-settings" ||
          ele_name === "select-scorecard" ||
          ele_name === "change-menu-item") {
          jQuery.blockUI({
            baseZ: 2000,
            message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while information is loading...</strong></div>',
            css: {
              border: 'none',
              fadeIn: 700,
              fadeOut: 700,
              opacity: 0.96,
              color: '#000',
              padding: '15px',
              cursor: 'wait',
              '-webkit-border-radius': '10px',
              '-moz-border-radius': '10px',
            }
          });
       }
      }
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData")) {
        var ele_name = ajaxOptions.extraData._triggering_element_name;

        if (ele_name.indexOf("Allfieldsdata[Manufacturer]") === 0) {
          // If Same as Manufacturer is choosed, then filling vendor also.
          // In case of edit.
          if (jQuery('.vendor_group_default input.same-as-manufacturer_field').is(':checked')) {
            jQuery('.vendor_group_default .choose-company_field').val(jQuery('.manufacturer_group_default .choose-company_field').val());
            jQuery('.vendor_group_default .catalog-number_field').val(jQuery('.manufacturer_group_default .catalog-number_field').val());
            jQuery('.vendor_group_default .contact-name_field').val(jQuery('.manufacturer_group_default .contact-name_field').val());
            jQuery('.vendor_group_default .contact-email_field').val(jQuery('.manufacturer_group_default .contact-email_field').val());
            jQuery('.vendor_group_default .contract-number_field').val(jQuery('.manufacturer_group_default .contract-number_field').val());
            jQuery('.vendor_group_default .contact-phone_field').val(jQuery('.manufacturer_group_default .contact-phone_field').val());
            jQuery('.vendor_group_default .choose-company_field_nid').val(jQuery('.manufacturer_group_default .choose-company_field_nid').val());
          }
        }

        if (ele_name === "get-my-requests" ||
          ele_name === "workflow_add_new_row" ||
          ele_name === "remove_lineItem" ||
          ele_name === "reset-callback" ||
          ele_name === "get-location-region-settings" ||
          ele_name === "get-location-entity-settings" ||
          ele_name === "get-location-buildings-settings" ||
          ele_name === "get-user-database-settings" ||
          ele_name === "get-catedit-settings" ||
          ele_name === "get-catdelete-settings" ||
          ele_name === "list_of_fields" ||
          ele_name === "get-scm_projects_scp" ||
          ele_name === "get-subtypeedit-settings" ||
          ele_name === "get-dellineitem_nec-settings" ||
          ele_name === "get-editlineitem_nec-settings" ||
          ele_name === "select-scorecard" ||
          ele_name === "change-menu-item") {

          jQuery.unblockUI();
        }

        // Trigger specific actions.
        if (ele_name === "select-scorecard") {
          if (jQuery('.decision-inner-menu').length > 0) {
            // Making summary tab active.
            jQuery('.decision-inner-menu').find('.menu-item:first').addClass('active');
            jQuery('.decision-inner-menu').find('.menu-item:first').find('a').addClass('active');

            // Removing width 0 on table when rendered first time.
            jQuery('#decision-recommendation').find('table').css("width", "");
          }
        }

        if (ele_name === "get-my-requests") {
          if (jQuery('.toggle-scm-vendor-section').length > 0) {
            // if (context == document) {
              jQuery('.scm-my-request-request-type').trigger('change');
              jQuery('.scm-my-request-category').trigger('change');
              var is_checked = jQuery("input.toggle-scm-vendor-section:checked").length;
              if (is_checked > 0) {
                jQuery('.toggle-this-container').show();
              }
            // }
          }
          if (jQuery('.userdb-base-requestID').val() === 'dbuser') {
              jQuery('.custom-action-button-div').hide();
          }
          else {
            jQuery('.custom-action-button-div').show();
          }

          // Triggering chat container.
          jQuery('.trigger-chat-here').trigger('mousedown');
        }

        if (ele_name === "add_edit_cat_action") {
          jQuery('.get-catedit-settings-reset').trigger('change'); 
        }

        if (ele_name === "scm-region-country") {
          var stateval = jQuery('input.scm-setting-location-region-statehiddan').val();
          if (jQuery('input.scm-setting-location-region-statehiddan').val()) {
            jQuery('select.scm-region-state').val(stateval);  
          }
        }

        if (ele_name === "scm-entity-country") {
          var stateval = jQuery('input.scm-setting-location-region-statehiddan').val();
          if (jQuery('input.scm-setting-location-region-statehiddan').val()) {
            jQuery('select.scm-entity-state').val(stateval);  
          }
        }

        if (ele_name === "scm-buildings-country") {
          var stateval = jQuery('input.scm-setting-location-region-statehiddan').val();
          if (jQuery('input.scm-setting-location-region-statehiddan').val()) {
            jQuery('select.scm-buildings-state').val(stateval);
          }
        }

        if (ele_name === "reset-callback") {
          jQuery('#program_scm_main_container').show(500);
          jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
          jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
          jQuery('.custom-action-button-div').show();
        }

        if (ele_name === "scm-my-request-entity" ||
          ele_name === "scm-my-request-department" ||
          ele_name === "scm-my-request-category" ||
          ele_name === "scm-my-request-requester-ref" ||
          ele_name === "scm-my-request-priority-level" ||
          ele_name === "check-triggers" ||
          ele_name === "scm-my-request-request-type") {

          jQuery('#program_scm_main_container').show(500);
          jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
          jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
          if (jQuery('.userdb-base-requestID').val() === 'dbuser') {
            jQuery('.custom-action-button-div').hide();
          }
          else {
            jQuery('.custom-action-button-div').show();
          }
        }

        if (ele_name === "get-my-requests" ||
          ele_name === "reset-callback" ||
          ele_name === "workflow_add_new_row" ||
          ele_name === "scm-my-request-request-type" ||
          ele_name === "remove_lineItem") {

          var reqtype_val = jQuery('.scm-my-request-request-type').val();

          if (jQuery('.userdb-base-requestID').val() === 'dbuser') {
            jQuery('.custom-action-button-div').hide();
          }
          else {
            jQuery('.custom-action-button-div').show();
          }

          if (ele_name === "reset-callback") {
            jQuery('.custom-action-button-div').show();
          }

          if (reqtype_val) {
            var reqtype_val1 = reqtype_val.split("-");
            if (reqtype_val1[1]==1) {
              jQuery('#alert-container-section').show();
              jQuery('#alert-container-section1').show();  
            }
            else if (reqtype_val1[1] == 0) {
              jQuery('#alert-container-section').hide(); 
              jQuery('#alert-container-section1').hide(); 
            }
            else {
              jQuery('#alert-container-section').hide();
              jQuery('#alert-container-section1').hide();
            }
          }
        }
      }
    });
});



/*
 * Add new button work
 */
function _form_show_hide_calling(status,redirect) {
  if(status == 'open' && jQuery('#program_scm_main_container').attr('data') == 'edit') {
    jQuery('#program_scm_main_container').removeAttr('data'); 
    jQuery('.reset-callback').trigger('change'); 
    jQuery('#alert-container-section').show(500);
    jQuery('#program_scm_main_container').show(500);
    jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
    jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
    jQuery('.custom-action-button-div').show(500);
  }
  else if(status == 'closed' && jQuery('#program_scm_main_container').attr('data') == 'edit') {  
    jQuery('#program_scm_main_container').removeAttr('data'); 
    jQuery('.reset-callback').trigger('change');
    jQuery('#program_scm_main_container').show(500);
    jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
    jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
    jQuery('.custom-action-button-div').show(500);
  }
  else if(status == 'closed') {
    jQuery('#program_scm_main_container').attr('for','open'); 
    jQuery('#program_scm_main_container').show(500);
    jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
    jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
    jQuery('.custom-action-button-div').show(500);

    
  }
  else if(status == 'open') {
    jQuery('#program_scm_main_container').hide(500);
    jQuery('#program_scm_main_container').parents('form').removeClass('scm-my-request-form-border');
    jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').removeClass('margin-top-10');
    jQuery('#program_scm_main_container').attr('for','closed'); 
    jQuery('#alert-container-section').hide(500);
    jQuery('#alert-container-section1').hide(500);
    jQuery('.custom-action-button-div').hide(500);
  }
  else if(status == 'open' && jQuery('#program_scm_main_container').attr('data') == 'edit') { 
    jQuery('#program_scm_main_container').removeAttr('data'); 
    jQuery('.reset-callback').trigger('change');
    jQuery('#program_scm_main_container').show(500);
    jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
    jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
    jQuery('.custom-action-button-div').show(500);
  }
  else if(jQuery( "#program_scm_main_container" ).attr('data') == 'edit') {
    jQuery('.reset-callback').trigger('change');
    jQuery('#program_scm_main_container').show(500);
    jQuery('.scm-show_all_requests_from_all_usersout').find('.pull-right').addClass('margin-top-10');
    jQuery('#program_scm_main_container').parents('form').addClass('scm-my-request-form-border');
    jQuery('#program_scm_main_container').attr('for','open');
    jQuery('.custom-action-button-div').show(500);
  }
}

updateList = function() {
  var input = document.getElementById('scm-attachment-upload');
  var output = document.getElementById('scm-upload-filelist');
  // Clearing previous files if any.
  //jQuery('#scm-upload-filelist').append('<div class="filelist-outer"></div>');
  var htmlss = '';
  console.log(input.files.length);
  // output.innerHTML = '<div class="filelist-outer">';
  for (var i = 0; i < input.files.length; ++i) {
    htmlss += '<div class="filelist-item">' + input.files.item(i).name + '</div>';
    //jQuery('.filelist-outer').append('<div class="filelist-item">' + input.files.item(i).name + '</div>');
  }
  jQuery('.filelist-outer').html(htmlss);
  jQuery('#scm-upload-filelist').show(['1000', 'clip']);
}

function getUrlParameter(sParam) {
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
}

function ShowCustomDialog(msg,href,action,other=null) {          
  ShowDialogBox('',msg,'Ok','Close', 'GoToAssetList',null,href,action,other);
}

function ShowDialogBox(title, content, btn1text, btn2text, functionText, parameterList, href, action, other = null) {
  var btn1css;
  var btn2css;

  if (btn1text == '') {
      btn1css = "hidecss";
  }
  else {
    btn1css = "showcss";
  }

  if (btn2text == '') {
    btn2css = "hidecss";
  }
  else {
    btn2css = "showcss";
  }

  jQuery("#lblMessage1").html(content);
  jQuery(".ui-dialog-titlebar").hide();
  jQuery("#dialogss").dialog({
    resizable: false,
    //title: title,
    modal: true,
    width: '400px',
    height: 'auto',
    bgiframe: false,
    hide: { effect: 'scale', duration: 400 },
    buttons:[{
      text: btn1text,
      "class": btn1css,
      click: function () {
        if(action == 'link') {
          window.open(href, "_self");
        }

        if (action == 'ajax') {
          if (href == 'new-record-link') {
            var status = jQuery('#program_scm_main_container').attr('for');
            _form_show_hide_calling(status,'my-request');

            if (window.location.pathname=='/scm/my-project') {
              jQuery('.reset-callback').trigger('chnage');
            }
          }

          if (href == 'edit_scm_requests_detail') {
            if (other) {
              var commitmentID = other;
              jQuery('.get-my-requests').val(commitmentID).trigger('change');
              jQuery('.my-request-node-nid').val(commitmentID);
              jQuery('html, body').animate({scrollTop: "0px"}, 800);
            }
            else {
              var commitmentID = jQuery('.'+href).attr('for');
              jQuery('.get-my-requests').val(commitmentID).trigger('change');
              jQuery('.my-request-node-nid').val(commitmentID);
              jQuery('html, body').animate({scrollTop: "0px"}, 800);
            }
          }

          if (href == 'edit_scm_requests_detail2') {
            var commitmentID = jQuery('.edit_scm_requests_detail').attr('for');
            jQuery('.get-scm_projects_scp').val(commitmentID).trigger('change');
            jQuery('.scm-project-node-nid').val(commitmentID);
            jQuery('html, body').animate({scrollTop: "0px"}, 800);
          }
        }
        jQuery("#dialogss").dialog('close');
      }
    },
    {
      text: btn2text,
      "class": btn2css,
      click: function () {
          jQuery("#dialogss").dialog('close');
      }
    }]
  });
}




function confrom_popupsection(title, content, btn1text, btn2text, parameters ,id,action) {
  console.log(parameters);
  var btn1css;
  var btn2css;
  if (btn1text == '') {
      btn1css = "hidecss";
  } else {
      btn1css = "showcss";
  }

  if (btn2text == '') {
      btn2css = "hidecss";
  } else {
      btn2css = "showcss";
  }
  if(title===''){
    jQuery(".ui-dialog-titlebar").hide();
  }
  

  jQuery("#lblMessage").html(content);

  jQuery("#"+id).dialog({
    resizable: false,
    title: '',
    modal: true,
    width: '400px',
    height: 'auto',
    bgiframe: false,
    hide: { effect: 'scale', duration: 400 },
    buttons:[{
              text: btn1text,
              "class": btn1css,
              click: function () {
                if(action=='delete'){
                  if(parameters['type']=='attachments'){
                    jQuery.post( '/update-image-reove/'+parameters['FID']+'/'+parameters['nid'], function( data ) {
                      jQuery("#getfileID_"+parameters['FID']).remove(); 
                      jQuery('select.'+parameters['trigerselect']).trigger('change');
                    });
                  } else {
                    action_trigger_data(parameters['type'],parameters['ID'],parameters['selector'],parameters['trigerselect']);  
                  }
                }          
                jQuery("#"+id).dialog('close');
              }
            },
            {
              text: btn2text,
              "class": btn2css,
              click: function () {
                  jQuery("#"+id).dialog('close');
              }
           }]
  });
}   

function action_trigger_data(type,ID,selector,trigerselect) {
        jQuery('select.'+trigerselect).val(ID).trigger('change');
      }


      function getcatform(){
      jQuery(".ui-dialog-titlebar").hide();
      jQuery("#updateboxpopup").dialog({
      resizable: false,
      title: '',
      modal: true,
      width: '400px',
      height: 'auto',
      bgiframe: false,
      hide: { effect: 'scale', duration: 400 },
      buttons:[
      // {
      //           text: 'btn1text',
      //           "class": 'btn1css',
      //           click: function () {        
      //             jQuery("#"+id).dialog('close');
      //           }
      //         },
              // {
              //   text: 'cancle',
              //   "class": 'btn2css',
              //   click: function () {
              //       jQuery("#updateboxpopup").dialog('close');
              //   }
             //}
             ]
      });
    } 

    