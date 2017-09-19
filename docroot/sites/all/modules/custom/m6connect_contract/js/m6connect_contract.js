Drupal.behaviors.showEXTERNALFORM = {
    attach: function (context, settings) {
        jQuery(".external-template", context).change(function(){
          if(this.value==1){
            jQuery('.middle-container').removeClass('hide');
            jQuery('.middle-container').addClass('display');
          }
          if(this.value==0){
            jQuery('.middle-container').addClass('hide');
            jQuery('.middle-container').removeClass('display');
          }
        })
        
     }


  };



Drupal.behaviors.m6connect_initiation = {
  attach: function (context, settings) {
    var getPath = window.location.pathname;
    var parameters = [];


  if(getPath == '/contract-manager/settings'){
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
      
     /* jQuery('.edit-section-group').click(function (e) {
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
      });*/

      /*jQuery('.delete-action-dep-call').unbind('click').bind('click', function (e) {
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
      });*/

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
         //console.log('service='+service+'====name='+name);
         jQuery('.rating-data-item').each(function(index, el) {
           if (jQuery(this).find('.remove-scm-setting-options').attr('data') == name) {
             // Hide this element.
             jQuery(this).hide(700);
           }
         });
     
     jQuery.ajax({
           type: 'POST',
           url: '/remove-contract-setting-options',
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


  }
};    