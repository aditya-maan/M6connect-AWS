Drupal.behaviors.custom_cropit = {
  attach: function (context, settings) {
    jQuery('#all_choose_image_custom').unbind('click').bind('click', function(event) {
        /* Act on the event */
        jQuery('#upload_log_ele').find('input[type=file]').trigger('click');
    });

    if (jQuery('.banner_upload_log_ele').length > 0) {
      // Initiating cropit.
      jQuery('#upload_log_ele').cropit({
        width: 945,
        height: 330,
        exportZoom: 1,
        smallImage: 'stretch',
        initialZoom:'image',
        imageBackground: true,
        imageBackgroundBorderWidth: 20,
      });
    }
    else {
      // Initiating cropit.
      jQuery('#upload_log_ele').cropit({
        width: 250,
        height: 275,
        exportZoom: 1,
        smallImage: 'stretch',
        initialZoom:'image',
        imageBackground: true,
        imageBackgroundBorderWidth: 20,
      });
    }

    // Checking input and showing it if any changes are made.
    jQuery(document).on('change', '#upload_log_ele input', function(){
      if (jQuery(this).length > 0) {
        jQuery('.cropit-preview').show();
        jQuery('.old_preview_img').hide();
      }
      else {
        jQuery('.cropit-preview').hide();
      }
    });

    // Custom Submit Handler.
    jQuery('.logo-upload-save-custom').unbind('click').bind('click', function(event) {
      event.preventDefault();
      /* Act on the event */
      var imageData = jQuery('#upload_log_ele').cropit('export');
      jQuery('#cropped-img-data .form-textarea').val(imageData);
      jQuery('.origina-submit-logo').find('input[type=submit]').trigger('click');
    });

    // Trying to remove file via Ajax.
    jQuery('.logo_old_remove').unbind('click').bind('click', function(event) {
      /* Act on the event */
      var current_ele = $(this);
      var classes = this.className;
      var classes_split = classes.split(' ');
      var uid_class = classes_split[4];
      var uid_split = uid_class.split('_');
      var uid = uid_split[1];
      jQuery.ajax({
        url: '/remove-profile-img-from-user-ajax',
        type: 'POST',
        data: {uid: uid},
        beforeSend: function() {
          // setting a timeout
          jQuery.blockUI({
             //theme:     true,
             baseZ: 2000,
             message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while removing old file...</strong></div>',
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
        },
      })
      .done(function() {
        jQuery.unblockUI();
        current_ele.hide(300);
        jQuery('.old_preview_img').hide(300);
      });
    });

    // Trying to remove file via Ajax.
    jQuery('.banner_old_remove').unbind('click').bind('click', function(event) {
      /* Act on the event */
      var current_ele = $(this);
      var classes = this.className;
      var classes_split = classes.split(' ');
      var uid_class = classes_split[4];
      var uid_split = uid_class.split('_');
      var uid = uid_split[1];
      jQuery.ajax({
        url: '/remove-profile-cover-from-user-ajax',
        type: 'POST',
        data: {uid: uid},
        beforeSend: function() {
          // setting a timeout
          jQuery.blockUI({
             //theme:     true,
             baseZ: 2000,
             message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while removing old file...</strong></div>',
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
        },
      })
      .done(function() {
        jQuery.unblockUI();
        current_ele.hide(300);
        jQuery('.old_preview_img').hide(300);
      });
    });

    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if ((urlajax.indexOf("/change-user-profile-photo") === 0 || urlajax.indexOf("/update-user-cover-photo") === 0) && ajaxOptions.hasOwnProperty("extraData")){
        jQuery.blockUI({
          baseZ: 2000,
          message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while your image is uploaded to our secure servers...</strong></div>',
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
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if ((urlajax.indexOf("/change-user-profile-photo") === 0 || urlajax.indexOf("/update-user-cover-photo") === 0) && ajaxOptions.hasOwnProperty("extraData")){
        jQuery.unblockUI();
      }
    });
  }
};