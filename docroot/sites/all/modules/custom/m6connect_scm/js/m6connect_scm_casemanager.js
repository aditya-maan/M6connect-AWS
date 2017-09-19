Drupal.ajax.prototype.commands.case_status_blur = function(ajax, response, status) {
  var blurCase = false;
  jQuery('.case-expand-item .caseouter').each(function() {
    if(jQuery(this).hasClass('case-active')) {
    blurCase = true;
  }
  });
  if(blurCase) {
    jQuery('.case-active').siblings().addClass('blur-cases');
  }
}



Drupal.ajax.prototype.commands.reloadPage = function(ajax, response, status) {
  // Reloading page.
  location.reload();
}

Drupal.ajax.prototype.commands.changeEvaluateHref = function(ajax, response, status) {
  // Changing evaluate link dynamically.
  if (jQuery('.change-evaluate-href').length > 0 && status === 'success') {
    jQuery('.change-evaluate-href').attr('href', response.arguments.href);
  }
}

Drupal.ajax.prototype.commands.hideShowPcContainer = function(ajax, response, status) {
  // Changing evaluate link dynamically.
  if (status === 'success') {
    if (jQuery('#projects-referenced-scorecard').find('.col-md-3').length == 0) {
      // If this is the last product removd.
      // Hiding product comparasion box if not shown.
      if (!jQuery('#project_scorecard_main_container_2').hasClass('hidden')) {
        // If products are open the not hiding the container else
        // hiding it.
        if (jQuery('.select-product-for-sc').length == 0) {
          jQuery('#project_scorecard_main_container_2').addClass('hidden');
        }
        else {
          jQuery('#projects-referenced-scorecard').html('<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix no-product-found text-center text-muted"><h4>Click Products Below to Add to Library.</h4></div></div>');
        }
      }
      else {
        // If products are open and the comparision library is hidden
        if (jQuery('.select-product-for-sc').length > 0) {
          jQuery('#project_scorecard_main_container_2').removeClass('hidden');
          jQuery('#projects-referenced-scorecard').html('<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix no-product-found text-center text-muted"><h4>Click Products Below to Add to Library.</h4></div></div>');
        }
      }
    }
  }
}


/*
 *  Ajax complete page reload for all scorecard pages...
 */
jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
  var urlajax = ajaxOptions.url;  
  if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="scorecard-number-select"){
    window.location.reload();
  }
});

Drupal.ajax.prototype.commands.groupPostRenderCalculations = function(ajax, response, status) {
  if ((ajax.callback === 'change_audience_callback' || ajax.callback === 'change_menu_item_callback') && status == 'success') {
    // Getting in if we have really triggered it.
    if (jQuery('table.group-raters-table').length > 0) {
      // Going through each table.
      jQuery('table.group-raters-table').each(function(index, el) {
        var table = jQuery(this);
        var rows_count = 0;
        var columns_count = 0;
        var rows_total_total = 0;

        // Getting rows and columns count.
        rows_count = table.find('th').length - 2;
        columns_count = table.find('tbody tr').length - 1;

        if (rows_count > 0 && columns_count > 0) {
          // Calculating rows count first.
          table.find('.row-total-js').each(function(index, el) {
            var ele_parent = jQuery(this).parents('tr');
            var curr_ele = jQuery(this);
            var rows_total = 0;
            ele_parent.find('.row-column-item').each(function(index, el) {
              var row_data = parseInt(jQuery(this).text());
              if (!isNaN(row_data)) {
                rows_total += row_data;
              }
            });
            if (rows_total) {
              curr_ele.find('.form-text').val(parseInt(rows_total));
              rows_total_total += rows_total;
            }
            else {
              curr_ele.find('.form-text').val(0);
            }
          });

          // Total of Total column.
          if (rows_total_total && !isNaN(rows_total_total)) {
            table.find('.column-total-js-total').find('.form-text').val(parseInt(rows_total_total));
          }
          else {
            table.find('.column-total-js-total').find('.form-text').val(0);
          }

          // Trying to get remaining total of columns.
          for (var i = 1; i <= rows_count; i++) {
            var columns_total = 0;
            table.find('tbody tr').each(function(index, el) {
              if (jQuery(this).find('.row-column-item-' + i).length > 0) {
                var col_data = parseInt(jQuery(this).find('.row-column-item-' + i).text());
                if (col_data && !isNaN(col_data)) {
                  columns_total += col_data;
                }
              }
            });
            if (columns_total && !isNaN(columns_total)) {
              table.find('.column-total-js-' + i).find('.form-text').val(parseInt(columns_total));
            }
            else {
              table.find('.column-total-js-' + i).find('.form-text').val(0);
            }
          }
        }
      });
    }

    // Also calculating totals here.
    if (jQuery('.calculate-tables-here').length > 0 && ajax.callback === 'change_menu_item_callback') {
      jQuery('.calculate-tables-here').each(function(index, el) {
        var total_fieldset = 0;
        jQuery(this).find('.column-total-js-total').each(function(index, el) {
          if (jQuery(this).find('.form-text').val()) {
            total_fieldset += parseInt(jQuery(this).find('.form-text').val());
          }
        });

        if (jQuery(this).find('.fieldset-total').length > 0) {
          jQuery(this).find('.fieldset-total').remove();
        }
        if (total_fieldset) {
          var new_html = '<span class="fieldset-total pull-right">Total Score: ' + total_fieldset + '</span>';
          jQuery(this).find('.fieldset-legend').append(new_html);
        }
        else {
          var new_html = '<span class="fieldset-total pull-right">Total Score: 0</span>';
          jQuery(this).find('.fieldset-legend').append(new_html);
        }
      });
    }
  }
}

Drupal.behaviors.m6connect_scm_casemanager = {
  attach: function (context, settings) {
  var getPath = window.location.pathname;
  jQuery('.case-expand-item .caseouter').each(function() {
    if(!jQuery(this).hasClass('case-active')) {
    jQuery(this).addClass('blur-cases blur-cases-sp')
  }
  });
  // scm/thread.
  jQuery('.add-new-team').unbind('click').bind('click', function(event) {
    /* Act on the event */
    event.preventDefault();

    // If we have some data in the name field, then we have to trigger the
    // select element, so that form is empty.
    if (jQuery('input.team-name').val()) {
      // This means, either user is editing a team or tried to make a new team
      // but didn't saved it. So we need to clear it up.
      jQuery('select.change-team').val('none').trigger('change');
      return false;
    }
    jQuery('#new-team-form-element').toggle(500);
  });

  jQuery('.cancel-new-team').unbind('click').bind('click', function(event) {
    /* Act on the event */
    event.preventDefault();
    jQuery('#new-team-form-element').hide(500);
  });

  jQuery('.edit-team').unbind('click').bind('click', function(event) {
    /* Act on the event */
    event.preventDefault();
    var nid = jQuery(this).attr('for');
    if (nid) {
      jQuery('.edit-node-nid-val').val(nid);
      jQuery('select.change-team').val(nid).trigger('change');
      return false;
    }
  });

  jQuery('.see-all-members').unbind('click').bind('click', function(event) {
    /* Act on the event */
    event.preventDefault();
    if (jQuery(this).hasClass('closed')) {
      jQuery(this).parents('.names-list').find('.team-list-extended').show('600');
      jQuery(this).removeClass('closed');
      jQuery(this).text('See Less...');
      jQuery(this).addClass('open');
    }
    else if (jQuery(this).hasClass('open')) {
      jQuery(this).parents('.names-list').find('.team-list-extended').hide('600');
      jQuery(this).removeClass('open');
      jQuery(this).text('See All...');
      jQuery(this).addClass('closed');
    }

    return false;
  });


  // Calculations of group ratings evaluate.
  if (jQuery('.qbuilder-rating').length > 0) {
    jQuery('.qbuilder-rating').each(function(index, el) {
      var weight = parseInt(jQuery(this).parents('tr').find('.qbuilder-weight').val());
      var score = jQuery(this).parents('tr').find('.qbuilder-score');
      var this_val = parseInt(jQuery(this).val());

      var score_val = this_val * weight;
      if (score_val && !isNaN(score_val)) {
        score.val(score_val);
      }
      else {
        score.val('');
      }
    });
  }

  if (getPath.indexOf("/scorecard/evaluate") === 0 ) {
	var getId = getPath.split('/');  
	jQuery('.scorecard-name-title-evaluate').val(getId[3]); 
    jQuery('.scorecard-name-title-evaluate').change(function (e) {
	  var getScoreId = jQuery(this).val();
	  jQuery.post( '/update-status-scorecard/'+getScoreId, function( data ) {
        if(data.result == 1) {
		  window.location.href="/scorecard/evaluate/"+getScoreId;
		}
      });
	});
  }
//Question Builder remove question 
    // if(context == document){
      // jQuery('.remove-add-row-item', context).on( 'mousedown', function ( e ) {
        
      //   if (context == document) {
      //     console.log(jQuery(this).attr('class'));
      //     var unikey2 = jQuery(this).attr('qbunikey2');
      //     console.log(unikey2);
      //     console.log(jQuery(this).parents('.HasDefault').attr('id'));
      //   }
      // });
    // }

    /*
    * scm case manager 
    */
    if(getPath == '/scm/my-casemanager' || getPath == '/scm/buy-change' || getPath == '/scm/patient-care' || getPath == '/scm/preferences'|| getPath == '/scm/resources'|| getPath == '/scm/due-diligence'|| getPath == '/scm/payback') { 
  /*
   * Applying Ui block Please wait
   */
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="op" && ajaxOptions.extraData._triggering_element_value==="Save"){
      jQuery.blockUI({
      baseZ: 2000,
          message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while information are loading...</strong></div>',
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
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="op" && ajaxOptions.extraData._triggering_element_value==="Save"){
      jQuery.unblockUI();
    }
  });

    jQuery('.case-expand-item .caseouter').each(function() {
      if(jQuery(this).hasClass('case-active')) {
        // jQuery(".category-informations-main option:selected").each(function(i) {
        //   if (i > 0) {
        //     var getVal = jQuery(this).val();
        //     if(getVal) {
        //       jQuery('.category-informations-main').trigger('change');
        //     }
        //   }
        //   else {
        //     //jQuery(".category-informations-main-sub").attr('disabled', 'disabled');    
        //   }
        // });        
     }
    });  
    //jQuery(".category-informations-main-sub").attr('disabled', 'disabled');
    //jQuery('.category-informations-main').trigger('change');
    // jQuery('.category-informations-main').change(function (e) {
    //     var mainCat = jQuery(this).val();
    //     jQuery(".category-informations-main-sub option").each(function () {
    // var getVal = jQuery(this).val();
    // var getCat = getVal.split('-');
    //     if (getCat[0] == mainCat) {
    //       jQuery(this).show();
    //       jQuery(".category-informations-main-sub").removeAttr('disabled');
    //     }
    //   else {
    //   if(jQuery(this).val() != '') {
    //     jQuery(this).hide();
    //   }           
    //       //jQuery(this).attr('disabled', 'disabled');
    //     }
    //   });  
    // });
    /*
     * Start work for making case status to active
     */
  jQuery('.case-status-check').change(function() {
      var caseStatus = jQuery(this).prop('checked');
    var caseNid = jQuery(this).attr('for');
    if(caseStatus == false) {
        //jQuery('.case-radio-'+ caseNid).find('input[type="radio"][value="active"]').trigger('click');
    jQuery('.case-radio-'+ caseNid).find('input[type="radio"][value="deactive"]').trigger('click');
      }
    else if(caseStatus == true){
    //jQuery('.case-radio-'+ caseNid).find('input[type="radio"][value="deactive"]').trigger('click');
    jQuery('.case-radio-'+ caseNid).find('input[type="radio"][value="active"]').trigger('click');
      }  
    });
  jQuery('.case-expand-item .caseouter').each(function() {
      var getVal = jQuery(this).find('input[name=case_options]:checked').val();
      if(getVal == 'active') {
        //jQuery(this).find('.case-status-check').bootstrapToggle('off');
    jQuery(this).find('.case-status-check').bootstrapToggle('on');
      } 
      else if(getVal == 'deactive') {
        jQuery(this).find('.case-status-check').bootstrapToggle('off');
    //jQuery(this).find('.case-status-check').bootstrapToggle('on')
      }
    });
  /*** End work for case status ***/
  jQuery('.save-case').each(function() {
      jQuery(this).click(function(e) {
        jQuery(this).parents('.btn-group').siblings('.clearfix').find('.save-case-button').trigger('mousedown');
      });
    });
  jQuery('.save-next-case').each(function() {
      jQuery(this).click(function(e) {
        jQuery(this).parents('.btn-group').siblings('.clearfix').find('.save-next-case-button').trigger('mousedown');
      });
    });
  jQuery('.save-addnew-case').each(function() {
      jQuery(this).click(function(e) {
        jQuery(this).parents('.btn-group').siblings('.clearfix').find('.save-addnew-case-button').trigger('mousedown');
      });
    });
  jQuery('.save-duplicate-case').each(function() {
      jQuery(this).click(function(e) {
        jQuery(this).parents('.btn-group').siblings('.clearfix').find('.save-duplicate-case-button').trigger('mousedown');
      });
    });
      jQuery('.tristate-toggle-button .form-radio').click(function(e){
        var getradioid = jQuery(this).val();     
        var getico = jQuery(this).parents('.tristate-toggle-button').siblings();      
        if(getradioid == 0){
          getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
        }else{
          if (getradioid == 1 && jQuery(this).parents('.tristate-toggle-button').hasClass('dont-make-it-green-on-red')) {
            // do nothing.
            getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
          }
          else {
            getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
          }
        }
      });
      jQuery('.scm-my-request-attachment-link').unbind('click').bind('click',function (e) {
        e.preventDefault();
        jQuery(this).parents('.section-top-parent').find('.scm-my-request-attachment').trigger('click');
      });

      // Handling file icon clicks on payback page.
      jQuery('.scm-my-request-attachment-link-new').unbind('click').bind('click', function(e) {
        e.preventDefault();
        var item_id = jQuery(this).attr('data');
        jQuery('#' + item_id).trigger('click');
      });

      // Trying to trigger add new row for clinicians and physicians.
      // jQuery('.clinicians-container-here', context).once('new-row', function() {
      //   jQuery('.trigger-clinicians-fname').blur(function() {
      //     jQuery(this).parents('.section-top-parent').find('.clinicians-add-new-row-button').trigger('mousedown');
      //   });
      // });

      // jQuery('.physicians-container-here', context).once('new-row', function() {
      //   jQuery('.trigger-physicians-fname').blur(function() {
      //     jQuery(this).parents('.section-top-parent').find('.physicians-add-new-row-button').trigger('mousedown');
      //   });
      // });
      jQuery('.physicians-container-here', context).once('new-row', function() {
        jQuery('.trigger-vendor-fname').blur(function() {
          jQuery(this).parents('.section-top-parent-new').find('.supplier-count-add-new-row-button').trigger('mousedown');
        });
      });
      /*
      //click on conditional field change backgrond color of icon (start)
      jQuery('.tristate-toggle-button input.satisfaction ').each(function() {  
        if(jQuery(this).val() == 2){
          jQuery('.tristate-toggle-button .satisfaction').css('background', '#f10d0d');
        }else if(jQuery(this).val() == 1){
          jQuery('.tristate-toggle-button .satisfaction').css('background', '#4cd964');
        }else if(jQuery(this).val() == 0){
          jQuery('.tristate-toggle-button .satisfaction').css('background', '#fff');
        }
      });
      //click on conditional field change backgrond color of icon (end)
      jQuery('input.satisfaction').click(function(e){        
        //click on conditional field change backgrond color of icon (start)
        var checkedValue = jQuery(this).val();
        if(jQuery(this).val() == 2){
          jQuery('.tristate-toggle-button .satisfaction').css('background', '#f10d0d');
        }else if(jQuery(this).val() == 1){
          jQuery('.tristate-toggle-button .satisfaction').css('background', '#4cd964');
        }else if(jQuery(this).val() == 0){
          jQuery('.tristate-toggle-button .satisfaction').css('background', '#fff');
        }
        //click on conditional field change backgrond color of icon (end)
        //click on conditional field hide parrent block (start)
        jQuery('.tristate-toggle-button .form-item').each(function (e){
          var hasnone = jQuery(this).attr('style');
          if(hasnone == 'display: none;'){
            jQuery(this).parent().parent().show();
          }
          if(hasnone == 'display: block;'){
            jQuery(this).parent().parent().hide();
          }
        });
        //click on conditional field hide parrent block (end)
      });*/
      /*
      //click on conditional field hide parrent block (start)
      jQuery('.tristate-toggle-button .form-item').each(function (e){
        var hasnone = jQuery(this).attr('style');
        if(hasnone == 'display: none;'){
          jQuery(this).parent().parent().show();
        }
        if(hasnone == 'display: block;'){
          jQuery(this).parent().parent().hide();
        }
      });
      //click on conditional field hide parrent block (end)*/
      //click on new case show the add new case (start)
      jQuery('.new-record-link').click(function(e){
        jQuery('.new-case-add').toggle('show');
      });
      jQuery('.case-builder-form-close').click(function(e){
        jQuery('.new-case-add').hide('show');
      });
      //click on new case show the add new case (end)

      jQuery('select.conditional-element').each(function(e){
        var selectedValue = jQuery(this).val();
        var getico = jQuery(this).parents('.selecticon').siblings();
        if(selectedValue){
          getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
        }else{
          getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
        }          
        jQuery(this).change(function(e){
          if(jQuery(this).val()){
          getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
          }else{
            getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
          }
        });
      });


      jQuery('input.conditional-element').each(function(e){
        var checkedValue = jQuery(this).val();
        //console.log(checkedValue);
        jQuery(this).addClass('rvalue-'+checkedValue);
        var getico = jQuery(this).parents('.tristate-toggle-button').siblings();
        if( jQuery(this).is(":checked") ){
          jQuery(this).parent().parent().attr('datavalue',checkedValue);
        }
        if(jQuery(this).is(":checked") && checkedValue ==2){
          jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').show();
          jQuery(this).parents('.conditionstatebase').find('.conditionstate-one').show();
          jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').show();
                    
          jQuery(this).parent().parent().css('background', '#21de41');
          getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
        }else if(jQuery(this).is(":checked") && checkedValue ==1){
          jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').hide();
          jQuery(this).parents('.conditionstatebase').find('.conditionstate-one').hide();
          jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').hide();
          jQuery(this).parent().parent().css('background', '#f10d0d');
          //getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
          if (checkedValue == 1 && jQuery(this).parents('.tristate-toggle-button').hasClass('dont-make-it-green-on-red')) {
            // do nothing.
            getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
          }
          else {
            getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
          }
        }else if(jQuery(this).is(":checked") && checkedValue ==0){
          jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').hide();
          jQuery(this).parents('.conditionstatebase').find('.conditionstate-one').hide();
          jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').hide();
          jQuery(this).parent().parent().css('background', '#fff');
        }
        jQuery(this).click(function(e){
          //jQuery(this).parent().parent().attr('datavalue',checkedValue);
          if(checkedValue ==2){

            jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').show();
            jQuery(this).parents('.conditionstatebase').find('.conditionstate-one').show();
            jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').show();

            jQuery(this).parent().parent().css('background', '#21de41');
          }else if(checkedValue ==1){
            jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').hide();
            jQuery(this).parents('.conditionstatebase').find('.conditionstate-one').hide();
            jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').hide();
            jQuery(this).parent().parent().css('background', '#f10d0d');
          }else if(checkedValue ==0){
            jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').hide();
            jQuery(this).parents('.conditionstatebase').find('.conditionstate-one').hide();
            jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').hide();
      jQuery(this).parents('.conditionstatebase').siblings('.conditionstate-one').find('.rvalue-0').trigger('click');
      jQuery(this).parent().parent().css('background', '#fff');
          }




          /************************tristate st*******************************/
          /*var tval = jQuery(this).parent().parent().attr('datavalue');
          console.log(jQuery(this).val());
          console.log(tval);
          if(jQuery(this).val() == 0){
            if(tval ==0 ){
              //jQuery(this).parent().parent().find('.rvalue-2').trigger('click');
              jQuery(this).parent().parent().attr('datavalue',2);
              console.log(jQuery(this).attr('id'));
              crid =jQuery(this).parent().parent().find('.rvalue-2').attr('id') ;
              console.log(crid);
              jQuery('#'+crid).trigger('click');

            }
            if(tval ==2 ){
              //jQuery(this).parent().parent().find('.rvalue-1').trigger('click');
              jQuery(this).parent().parent().attr('datavalue',1);
              console.log(jQuery(this).attr('id'));
              crid = jQuery(this).parent().parent().find('.rvalue-1').attr('id');
              console.log(crid);
              jQuery('#'+crid).trigger('click');
            }
            if(tval ==1 ){
              //jQuery(this).parent().parent().find('.rvalue-0').trigger('click');
              jQuery(this).parent().parent().attr('datavalue',0);
              console.log(jQuery(this).attr('id'));
              crid = jQuery(this).parent().parent().find('.rvalue-0').attr('id');
              console.log(crid);
              jQuery('#'+crid).trigger('click');
            }
          }*/
          /************************tristate en*******************************/




        });

        //new condition
        var parentstatus = jQuery(this).parents('.tristate-toggle-button').parent().parent().attr('class');  
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstatebase1'){
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').hide();
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').show();
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').show();             
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstatebase1'){             
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').show();
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').hide(); 
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').show();    
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstatebase1'){     
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').hide();   
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').hide();
          jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').hide();   
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').hide();   
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').hide();      
        }
        //conditionstate-onered
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onered'){
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').show();
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onered'){
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').hide();    
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').show();    
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onered'){
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').hide();    
          jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').hide();    
        }
        //conditionstate-redtwo
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-redtwo'){
          jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-redtwo'){
          jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').show();    
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-redtwo'){
          jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').hide();    
        }
        if(jQuery(this).is(":checked") &&jQuery(this).val() ==2 && parentstatus=='conditionstate-onered-twogreen'){
          jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble').show();
          jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble-twogreen').show();
        }else if(jQuery(this).is(":checked") &&jQuery(this).val() ==1 && parentstatus=='conditionstate-onered-twogreen'){
          jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble').show();
          jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble-twogreen').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onered-twogreen'){
          jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble').hide();
          jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble-twogreen').hide();
        }
        //conditionstate-onegreen
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen'){
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').show(); 
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-greentwo').show();     
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen'){
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').show();
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-greentwo').hide();      
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen'){
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').hide();
          jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-greentwo').hide();      
        }
        //conditionstate-greentwo
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-greentwo'){
          jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').show();     
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-greentwo'){
          jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').hide();      
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-greentwo'){         
          jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').hide();      
        }
        //conditionstate-greenthree
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree'){          
          jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').hide();     
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree'){
          jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').show();      
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree'){
          jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').hide();      
        }

        //conditionstate-greenthree-red
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree-red'){
          jQuery(this).parents('.conditionstate-greenthree-red').find('.conditionstate-greenthree-redtwo').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree-red'){
          jQuery(this).parents('.conditionstate-greenthree-red').find('.conditionstate-greenthree-redtwo').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree-red'){
          jQuery(this).parents('.conditionstate-greenthree-red').find('.conditionstate-greenthree-redtwo').hide();
        }

        //conditionstate-onegreen-red
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-red'){
          jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-red'){
          jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-red'){
          jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').hide();
        }

        //conditionstate-greenthree-redtwo
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree-redtwo'){
          jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-redthree').hide();
          jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-green').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree-redtwo'){
          jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-redthree').show();
          jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-green').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree-redtwo'){
          jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-redthree').hide();
          jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-green').hide();
        }

        //conditionstate-onegreen-redtwo
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-redtwo'){
          jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').hide();
          jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-green').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-redtwo'){
          jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').show();
          jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-green').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-redtwo'){
          jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').hide();
          jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-green').hide();
        }

        //conditionstate-greenthree-redthree
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree-redthree'){
          jQuery(this).parents('.conditionstate-greenthree-redthree').find('.conditionstate-greenthree-redfour').hide();  
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree-redthree'){
          jQuery(this).parents('.conditionstate-greenthree-redthree').find('.conditionstate-greenthree-redfour').show(); 
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree-redthree'){
          jQuery(this).parents('.conditionstate-greenthree-redthree').find('.conditionstate-greenthree-redfour').hide(); 
        }

        //conditionstate-onegreen-redthree
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-redthree'){
          jQuery(this).parents('.conditionstate-onegreen-redthree').find('.conditionstate-onegreen-redfour').hide();  
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-redthree'){
          jQuery(this).parents('.conditionstate-onegreen-redthree').find('.conditionstate-onegreen-redfour').show(); 
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-redthree'){
          jQuery(this).parents('.conditionstate-onegreen-redthree').find('.conditionstate-onegreen-redfour').hide(); 
        }

        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-dubble'){
          jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-dubble'){
          jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-dubble'){
          jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').hide();
        }
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-dubble'){
          jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-dubble'){
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-dubble'){
          jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').hide();
        }
        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-dubble-twogreen'){
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-dubble').show();
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-onegreen').show();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-dubble-twogreen'){
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-dubble').show();
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-onegreen').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-dubble-twogreen'){
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-dubble').hide();
          jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-onegreen').hide();
        }
        jQuery(this).click(function(e){
          var parentstatus = jQuery(this).parents('.tristate-toggle-button').parent().parent().attr('class');    
          if(jQuery(this).val() ==2 && parentstatus=='conditionstatebase1'){              
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').hide();
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').show();            
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').show();            
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstatebase1'){               
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').show();
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').hide();      
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').show();      
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstatebase1'){      
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').hide(); 
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').hide(); 
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').hide(); 
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').hide();
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').hide();         



            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onered').find('.rvalue-0').trigger('click');
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').find('.rvalue-0').trigger('click');
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-onegreen').find('.conditionstate-greentwo').find('.rvalue-0').trigger('click');
            jQuery(this).parents('.conditionstatebase1').find('.conditionstate-oneredgreen').find('.rvalue-0').trigger('click');
          }
          //conditionstate-onered
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onered'){
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').show();
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').hide();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onered'){
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').hide();    
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').show();    
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onered'){
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-onered-twogreen').hide();    
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').hide();  
            jQuery(this).parents('.conditionstate-onered').find('.conditionstate-redtwo').find('.rvalue-0').trigger('click');  
          }
          //conditionstate-redtwo
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-redtwo'){
            jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').hide();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-redtwo'){
            jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').show();    
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-redtwo'){
            jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').hide();   
            jQuery(this).parents('.conditionstate-redtwo').find('.conditionstate-threered').find('.rvalue-0').trigger('click');  
          }
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onered-twogreen'){
            jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble').show();
            jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble-twogreen').show();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onered-twogreen'){
            jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble').show();
            jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble-twogreen').hide();
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onered-twogreen'){
            jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble').hide();
            jQuery(this).parents('.conditionstate-onered-twogreen').find('.conditionstate-onered-twogreen-dubble-twogreen').hide();
          }
          //conditionstate-onegreen
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen'){
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').show();
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-greentwo').show();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen'){
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').show();
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-greentwo').hide();      
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen'){
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-onegreen-dubble').hide();
            jQuery(this).parents('.conditionstate-onegreen').find('.conditionstate-greentwo').hide();       
          }
          //conditionstate-greentwo
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-greentwo'){
            jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').show();     
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-greentwo'){
            jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').hide();      
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-greentwo'){
            jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').hide();      
            jQuery(this).parents('.conditionstate-greentwo').find('.conditionstate-greenthree').find('.rvalue-0').trigger('click');
          }
          //conditionstate-greenthree
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree'){          
            jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').hide();     
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree'){
            jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').show();     
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree'){
            jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').hide(); 
            jQuery(this).parents('.conditionstate-greenthree').find('.conditionstate-onered').find('.rvalue-0').trigger('click');     
          }

          //conditionstate-greenthree-red
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree-red'){         
            jQuery(this).parents('.conditionstate-greenthree-red').find('.conditionstate-greenthree-redtwo').hide();     
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree-red'){
            jQuery(this).parents('.conditionstate-greenthree-red').find('.conditionstate-greenthree-redtwo').show();      
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree-red'){
            jQuery(this).parents('.conditionstate-greenthree-red').find('.conditionstate-greenthree-redtwo').hide();      
          }

          //conditionstate-onegreen-red
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-red'){
            jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').hide();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-red'){
            jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').show();
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-red'){
            jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').hide();
            jQuery(this).parents('.conditionstate-onegreen-red').find('.conditionstate-onegreen-redtwo').find('.rvalue-0').trigger('click');
          }

          //conditionstate-greenthree-redtwo
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree-redtwo'){      
            jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-redthree').hide();   
            jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-green').show();     
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree-redtwo'){
            jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-redthree').show();   
            jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-green').hide();     
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree-redtwo'){
            jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-redthree').hide();   
            jQuery(this).parents('.conditionstate-greenthree-redtwo').find('.conditionstate-greenthree-green').hide();     
          }

          //conditionstate-onegreen-redtwo
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-redtwo'){
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').hide();
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-green').show();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-redtwo'){
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').show();
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-green').hide();
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-redtwo'){
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').hide();
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-redthree').find('.rvalue-0').trigger('click');
            jQuery(this).parents('.conditionstate-onegreen-redtwo').find('.conditionstate-onegreen-green').hide();
          }

          //conditionstate-greenthree-redthree
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-greenthree-redthree'){         
            jQuery(this).parents('.conditionstate-greenthree-redthree').find('.conditionstate-greenthree-redfour').hide();  
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-greenthree-redthree'){
            jQuery(this).parents('.conditionstate-greenthree-redthree').find('.conditionstate-greenthree-redfour').show(); 
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-greenthree-redthree'){
            jQuery(this).parents('.conditionstate-greenthree-redthree').find('.conditionstate-greenthree-redfour').hide(); 
          }

          //conditionstate-onegreen-redthree
          if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-redthree'){
            jQuery(this).parents('.conditionstate-onegreen-redthree').find('.conditionstate-onegreen-redfour').hide();  
          }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-redthree'){
            jQuery(this).parents('.conditionstate-onegreen-redthree').find('.conditionstate-onegreen-redfour').show(); 
          }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-redthree'){
            jQuery(this).parents('.conditionstate-onegreen-redthree').find('.conditionstate-onegreen-redfour').hide(); 
          }

          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-dubble'){
            jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').show();      
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-dubble'){
            jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').hide();      
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-dubble'){
            jQuery(this).parents('.conditionstate-onegreen-dubble').find('.conditionstate-onegreen-dubble-twogreen').hide();      
          }
          if(jQuery(this).val() ==2 && parentstatus=='conditionstate-onegreen-dubble-twogreen'){
            jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-dubble').show();
            jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-onegreen').show();
          }else if(jQuery(this).val() ==1 && parentstatus=='conditionstate-onegreen-dubble-twogreen'){
            jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-dubble').show();
            jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-onegreen').hide();
          }else if(jQuery(this).val() ==0 && parentstatus=='conditionstate-onegreen-dubble-twogreen'){
            jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-dubble').hide();
            jQuery(this).parents('.conditionstate-onegreen-dubble-twogreen').find('.conditionstate-onegreen-dubble-twogreen-onegreen').hide();
          }
        });

      });

      //checkbox
      jQuery('input.conditional-element-checkbox').each(function(e){
        var checkedValue = jQuery(this).is(":checked");
        if(checkedValue){
          jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').show();
        }else{
          jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').hide();
        }
        jQuery(this).click(function(e){
          var checkedValue = jQuery(this).is(":checked");
          if(checkedValue){
            jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').show();
          }else{
            jQuery(this).parents('.conditionstate-one').next('.conditionstate-two').hide();
          }
        });
      });
      
      //casemanager tab buy or change subtab 
      jQuery('input.product-capitalcomponentyes').each(function(e){
        var parentstatus = jQuery(this).parents('.tristate-toggle-button').parent().attr('class');
        var parentstatus1 = jQuery(this).parents('.casebuilder-left-section-container').find('.equipment-info').attr('class'); 

        if(jQuery(this).is(":checked") && jQuery(this).val() ==2 && parentstatus.indexOf('product-capitalcomponent-yes')){  
          jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').show();     
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==1 && parentstatus.indexOf('product-capitalcomponent-yes')){               
          jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').hide();
        }else if(jQuery(this).is(":checked") && jQuery(this).val() ==0 && parentstatus.indexOf('product-capitalcomponent-yes')){               
          jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').hide();
        }
        jQuery(this).click(function(e){          
          if(jQuery(this).val() ==2 && parentstatus.indexOf('product-capitalcomponent-yes')){  
           jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').show();     
          }else if(jQuery(this).val() ==1 && parentstatus.indexOf('product-capitalcomponent-yes')){
            jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').hide();
          }else if(jQuery(this).val() ==0 && parentstatus.indexOf('product-capitalcomponent-yes')){
            jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').hide();
            jQuery(this).parents('.casebuilder-left-section-container').find('.product-capitalcomponent-item').find('.rvalue-0').trigger('click'); 
          }
        });
      });

      jQuery('.case-expand').unbind('click').bind('click', function(e) {
        e.preventDefault();
        var casestatus = jQuery(this).attr('case-status');
        if(casestatus == 'close'){
          jQuery(this).attr('case-status','open');
          jQuery(this).parents('.casebuilder-details-left').siblings('.casebuilder-details-right').removeClass('dispaly_none');
          jQuery(this).parents('.casebuilder-details-left').siblings('.casebuilder-details-right').find('.case-collapse').attr('case-comment-status','open');          
        }        
      });

      jQuery('.case-collapse').click(function(e){
        var casecommentstatus = jQuery(this).attr('case-comment-status');
        if(casecommentstatus == 'open'){
          jQuery(this).attr('case-comment-status','close');
          jQuery(this).parents('.casebuilder-details-right').addClass('dispaly_none');
          jQuery(this).parents('.casebuilder-details-right').siblings('.casebuilder-details-left').find('.case-expand').attr('case-status','close');
        }
      });
      jQuery('.casetextareaedit').click(function(e){
        jQuery(this).parent().hide();
        jQuery(this).parent().siblings('.hastextarea').removeClass('dispaly_none');
      });      
      // dubble scroll
      var divwidth = jQuery('.case-expand-item').width();
      jQuery('.case-expand-itemupper').width(divwidth);
      jQuery(".case-expand-widthupper").scroll(function(){
        jQuery(".case-expand-width").scrollLeft(jQuery(".case-expand-widthupper").scrollLeft());
      });
      jQuery(".case-expand-width").scroll(function(){
          jQuery(".case-expand-widthupper").scrollLeft(jQuery(".case-expand-width").scrollLeft());
      }); 



      jQuery('.wirteenicon-change').each(function(e){ 
        var wval = jQuery(this).val();
        var getico = jQuery(this).parents('.tristate-toggle-button').siblings();
        if(wval && wval != ''){
          getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
        }else{
          getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
        }
        jQuery(this).bind("keyup change", function(e) {
          if(jQuery(this).val() && jQuery(this).val() != ''){
            getico.html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');
          }else{
            getico.html('<i class="fa fa-3x fa-question-circle" aria-hidden="true" style="color: #fdc028;"></i>');
          }
        });
      });
      jQuery('.remove-vendor-row-link').unbind('click').bind("click", function(e) {
        e.preventDefault();
        jQuery(this).next('.remove-vendor-row').trigger('mousedown');
      });

  }
  /*
   * Work for Scorecard section
   */ 
   if(getPath == '/scm/select-products') {       
     jQuery('.add-new-item-trigger').unbind('click').bind('click',function (e) {
       e.preventDefault();
     console.log('testing inner');
     jQuery('.product-workflow-action-add-details').trigger('click');
     });
   }
   
   if(getPath == '/scorecard/share' || getPath == '/scm/scorecard/share' ) {       
     jQuery('.edit-share-detail').unbind('click').bind('click',function (e) {
       e.preventDefault();
       var getId = jQuery(this).attr('for');
       jQuery('.project-scorecard-sel-list').val(getId).trigger('change');
     });

     jQuery('.cancel-share-edit-form').unbind('click').bind('click',function (e) {
      e.preventDefault();
      jQuery('#questionbuilder_scorecard_main_container').hide(500);
     });
   }
   
   
  /*
   * Work for Scorecard section
   * work for Quesction Builder
   */ 
  jQuery('.remove-add-row-item-link').unbind('click').bind("click", function(e) {
    e.preventDefault();
    jQuery(this).siblings('.remove-add-row-item').trigger('mousedown');
  });

  jQuery('.item-increase-rating').unbind('click').bind("click", function(e) {
    var qb= jQuery(this).parent().siblings('input').val();
    if(qb <5){
      qb++;
      jQuery(this).parent().siblings('input').val(qb).change();
    }
  });
  jQuery('.item-increase-weight').unbind('click').bind("click", function(e) {
    var qb= jQuery(this).parent().siblings('input').val();
    if(qb <10){
      qb++;
      jQuery(this).parent().siblings('input').val(qb).change();
    }
  });

  jQuery('.item-decrease').unbind('click').bind("click", function(e) {
    var qb= jQuery(this).parent().siblings('input').val();  
   if(qb >0){
      qb--;
      jQuery(this).parent().siblings('input').val(qb).change();
    }
  });
  var tblrows = jQuery(".qbuilder-table tbody tr");
  jQuery(tblrows).each(function() {
    var dinput =jQuery(this).find('.default input').attr('class');
    if(dinput =='NonDefault'){
      jQuery(this).hide();
    }
    else{
      jQuery(this).show();
    }
  });

  getqbselectd_category = function(qbclass) {
    var getcat = [];
    jQuery("."+qbclass+" option:selected").each(function () {
       if (jQuery(this).val()) {
        getcat.push(jQuery(this).val());
      }
    });
    return getcat;
  }
  jQuery('.qbuilder-category-select').on('click',function(e){
    console.log(getPath);
    var AddQuestion = jQuery(this).attr('AddQuestion');
    if(AddQuestion && AddQuestion =='yes' && getPath != '/scorecard/new/question-builder'){
      var content = 'Please save your changes, otherwise your changes will be lost.';
      var parameters =[];
      parameters['type'] = 'button';
      parameters['ID'] = '';
      parameters['selector'] = 'qb-save';
      parameters['trigerselect'] = 'click';
      confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','no');
    }
  });
  jQuery('.qbuilder-category-select').on('change',function(e){
    var defaultNoCat = jQuery(this).attr('qcselect');
    var old = jQuery('.qb-selectcategory1').val();
    var cvalue = jQuery(this).val();
    if(defaultNoCat == 'default-no-cat'){
      jQuery('.qb-selectcategory1').val(cvalue);
      jQuery('.qb-selectcategory1').trigger('change');
    }
       
    if(defaultNoCat == 'default'){
      if(old){
        old.push(cvalue); 
        jQuery('.qb-selectcategory1').val(old);
        jQuery('.qb-selectcategory1').trigger('change');
      }else{
        jQuery('.qb-selectcategory1').val(cvalue);
        jQuery('.qb-selectcategory1').trigger('change');
      }
      
      
    }

    var oldcat = getqbselectd_category('qb-selectcategory1');
    if(jQuery.isNumeric(defaultNoCat)){
      if(oldcat.indexOf(cvalue)=== -1){
        var index = oldcat.indexOf(defaultNoCat);
        if (index >= 0) {
          oldcat.splice( index, 1 );
        }
        oldcat.push(cvalue);   
        jQuery('.qb-selectcategory1').val(oldcat);
        jQuery('.qb-selectcategory1').trigger('change');
      }
    }
  });

  jQuery('.qbuilder-category-select option').each(function(){
    var cvalue = jQuery(this).val();
    var oldcat = getqbselectd_category('qb-selectcategory1');
    //console.log(oldcat);
    if(cvalue){
      // if(oldcat.indexOf(cvalue)===0){
      if(jQuery.inArray(cvalue, oldcat) !== -1){
        jQuery(this).attr('disabled', true);
      } 
    }
  });
  /*jQuery('.qbuilder-table tbody ').append(jQuery('.qbuilder-table tbody tr.NonDefault').sort(function(b,a){
     return b.getAttribute('order')-a.getAttribute('order');
  }));*/
  /*jQuery(window).on('beforeunload', function(){
      return 'Are you sure you want to leave ?';
    });*/

    /**********tristate button start************/
    /*jQuery('.conditional-element').each(function(e){ 
      jQuery(this).click(function(e){  
        var dval1 = jQuery(this).val(); 
        var tval = jQuery(this).parent().parent().attr('datavalue');
        console.log(dval1);
        console.log(tval);
        if(tval ==0 ){
      //jQuery(this).parent().parent().find('.rvalue-2').trigger('click');
      jQuery(this).parent().siblings().find('.rvalue-2').trigger('click');
      jQuery(this).parent().parent().attr('datavalue',2);
      jQuery(this).parent().parent().attr('class');
    }else if(tval ==2 ){
      //jQuery(this).parent().parent().find('.rvalue-1').trigger('click');
      jQuery(this).parent().siblings().find('.rvalue-1').trigger('click');
      jQuery(this).parent().parent().attr('datavalue',1);
      jQuery(this).parent().parent().attr('class');
    }else if(tval ==1 ){
      //jQuery(this).parent().parent().find('.rvalue-0').trigger('click');
      jQuery(this).parent().siblings().find('.rvalue-0').trigger('click');
      jQuery(this).parent().parent().attr('datavalue',0);
      jQuery(this).parent().parent().attr('class');
    }
      });
    });*/
    /**********tristate button end*************/

    // If adding a product when not allowed.
    jQuery('.add-new-product-disabled').unbind('click').bind('click', function(event) {
      /* Act on the event */
      event.preventDefault();
      jQuery('#product-already-added').html('<div class="text-center" style="padding-bottom:25px;"><strong>There are no product categories added for this company. Please ask your company admin to add categories and then try again!</strong></p></div>');
      jQuery('#product-already-added').dialog('open');
    });

    // Selecting products on scorecard page.
    jQuery('.select-product-for-sc').unbind('click').bind('click', function(event) {
      /* Act on the event */
      event.preventDefault();
      var action = jQuery(this).attr('data');
      var id = jQuery(this).attr('id');
      if (action == 'remove') {
        var score_split = id.split('--');
        id = score_split[0];
      }
      var split_id = id.split('-');
      var nid = split_id[0];
      var snid = split_id[1];
      var main_container = document.getElementById('project_scorecard_main_container_2');

      if (jQuery('#' + id + '--scorecard').length > 0 && action == 'add') {
        jQuery('#product-already-added').html('<div class="text-center" style="padding-bottom:25px;"><strong>Selected product is already added. Please select different product.</strong></p></div>');
        jQuery('#product-already-added').dialog('open');
        return false;
      }

      jQuery.ajax({
        url: '/add-scorecard-reference/' + action + '/' + nid + '/' + snid,
        beforeSend: function() {
          if (action == 'add') {
            jQuery('html, body').css('opacity', 0.65);
            jQuery('html, body').animate({
              scrollTop: main_container.scrollHeight}, 500);
          }
        },
        success: function(data) {
          if (data.success == 'Yes') {
            // We got success.
            if (data.method == 'add') {
              if (data.data) {
                // Showing product comparasion box if not shown.
                if (jQuery('#project_scorecard_main_container_2').hasClass('hidden')) {
                  jQuery('#project_scorecard_main_container_2').removeClass('hidden');
                }

                // Removing any No product found dialogues.
                if (jQuery('.no-product-found').length > 0) {
                  jQuery('.no-product-found').parent().remove();
                }

                jQuery('html, body').css('opacity', 1);
                // Attaching our data.
                if (jQuery('#' + id + '--scorecard').length == 0) {
                  jQuery('#projects-referenced-scorecard').prepend(data.data);
                  jQuery('#' + id + '--scorecard').parents('.remove-hide-this-product').parent().hide().fadeIn(2000);

                  if (jQuery('#' + id).find('.col-md-8 .panel-body').length > 0) {
                    // Adding a green check to the product selected.
                    jQuery('.' + id).each(function(index, el) {
                      jQuery(this).find('.col-md-8 .panel-body').prepend('<i class="fa fa-2x fa-check-circle pull-right text-success" aria-hidden="true"></i>');
                    });
                  }
                  Drupal.attachBehaviors();
                }
              }
            }
            else if (data.method == 'remove') {
              var new_id = id + '--scorecard';
              jQuery('#' + new_id).parents('.remove-hide-this-product').hide(400, function() {
                jQuery(this).remove();

                if (jQuery('#projects-referenced-scorecard').find('.col-md-3').length == 0) {
                  // If this is the last product removd.
                  // Hiding product comparasion box if not shown.
                  if (!jQuery('#project_scorecard_main_container_2').hasClass('hidden')) {
                    // If products are open the not hiding the container else
                    // hiding it.
                    if (jQuery('.select-product-for-sc').length == 0) {
                      jQuery('#project_scorecard_main_container_2').addClass('hidden');
                    }
                    else {
                      jQuery('#projects-referenced-scorecard').html('<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix no-product-found text-center text-muted"><h4>Click Products Below to Add to Library.</h4></div></div>');
                    }
                  }
                }

                if (jQuery('#' + id).find('.col-md-8 .panel-body').length > 0) {
                  // Removing the green check sign.
                  jQuery('.' + id).each(function(index, el) {
                    jQuery(this).find('.col-md-8 .panel-body').find('.fa-check-circle').remove();
                  });
                }
              });
            }
          }
        },
        always: function() {
          jQuery('html, body').css('opacity', 1);
        },
        error: function() {
          jQuery('html, body').css('opacity', 1);
        }
      });
    });

    // Changing select-vendor options and button text.
    jQuery('.select-vendor-anchor').unbind('click').bind('click', function(event) {
      /* Act on the event */
      event.preventDefault();
      var href_this = jQuery(this).text();
      var sel_val = jQuery(this).attr('for');

      
      jQuery(this).parents('.toggle-text-here').text(href_this);
      jQuery('#edit-search-criteria').val(sel_val).trigger('change');

      
      /*if(jQuery('.toggle-text-here').text('Products')){
        //jQuery('.sel_cat').css({'pointer-events':'none', 'opacity':'0.4'});
        //jQuery('ul.dropdown-menu li a.sel_cat').addClass('disable_cat');
        jQuery('ul.dropdown-menu li a.sel_cat').hide();
      }*/

    });



    jQuery('.resolve-comment').unbind('click').bind('click', function(event) {
      /* Act on the event */
      event.preventDefault();
      var curr_ele = jQuery(this);
      var cid = jQuery(this).attr('id');

      // We also need to get comment, in case user is approving it at the same
      // time.
      var comment = jQuery(this).parents('.form-item').find('.form-text').val();

      jQuery.ajax({
        url: '/scorecard/resolve-comment/' + cid,
        type: 'POST',
        data: {comment: comment},
      })
      .done(function(data) {
        if (data.status === 'Success') {
          // If data is success
          curr_ele.addClass('comment-resolved');
          curr_ele.removeClass('resolve-comment');

          if (data.output) {
            curr_ele.parents('.media-body').find('.media:last').before(data.output);

            // If we got some data, then we need to clear it from text field
            // also.
            curr_ele.parents('.form-item').find('.form-text').val('');
          }

          // Also if there are no unresolved commments now, but still the
          // red exclaimation sign, then removing it.
          console.log(curr_ele.parents('.fieldset-wrapper').find('.resolve-comment').length);
          console.log(curr_ele.parents('.bid-package-fieldset').find('.fa-exclamation-circle').length);
          if (curr_ele.parents('.fieldset-wrapper').find('.resolve-comment').length == 0) {
            // If all comments are resolved, now checking if this fieldset has
            // the red sign.
            if (curr_ele.parents('.bid-package-fieldset').find('.fa-exclamation-circle').length > 0) {
              curr_ele.parents('.bid-package-fieldset').find('.fa-exclamation-circle').remove();
            }
          }
        }
        if (data.status == 'No comment') {
          jQuery('#decision-dialogue-box').html('<div class="text-center" style="padding-bottom:25px;"><strong>Please provide some commments to mark this as resolved!</strong></p></div>');
          jQuery('#decision-dialogue-box').dialog('open');
        }
      })
      .fail(function() {
        jQuery('#decision-dialogue-box').html('<div class="text-center" style="padding-bottom:25px;"><strong>Some technical error occured, please try again!</strong></p></div>');
        jQuery('#decision-dialogue-box').dialog('open');
      })
      .always(function() {
        //
      });
      
    });

    //question builder row number
    if(getPath == '/scm/scorecard/question-builder'||getPath == '/scorecard/question-builder'||getPath == '/scorecard/new/question-builder') {
      jQuery('.rownumber').text('');
      jQuery('.qbuilder-table tbody').each(function(e){
        var row = jQuery(this).find('tr.HasDefault');
        jQuery(row).each(function(index,value){
          var rownumber1 = index+1;
          var rownumber  = rownumber1+'.';
          //jQuery(this).find('td.trow-inline-link').attr('testnumber',rownumber);
          jQuery(this).find('td.trow-inline-link div.form-type-textfield').before('<div class="rownumber pull-left">' +rownumber + '</div>');
        });
      });
      /*jQuery('.scm-share-submit').unbind('click').bind('click', function(event) {
      //jQuery(document).on( 'click', '.scm-share-submit', function ( e ) {
        if(jQuery('.qb-save')){
          jQuery('.qb-save').trigger('click');
        }
      });*/
    }


    jQuery('.clinicians-subspecialty').blur(function(e){
      var vvalue = jQuery(this).val();
      var lvalue = jQuery(this).val().length;
      if (vvalue && lvalue > 0) {
        jQuery('.clinicians-add-new-row-button').trigger('mousedown');
      }
    });
    jQuery('.physicians-primary-fname').blur(function(e){
      var vvalue = jQuery(this).val();
      var lvalue = jQuery(this).val().length;
      if (vvalue && lvalue > 0) {
        jQuery('.physicians-add-new-row-button').trigger('mousedown');
      }
    });
    jQuery('.facilities-first-name').blur(function(e){
      var vvalue = jQuery(this).val();
      var lvalue = jQuery(this).val().length;
      if (vvalue && lvalue > 0) {
        jQuery('.facilitiescontact-add-new-row-button').trigger('mousedown');
      }
    });
  }
};

jQuery(document).ready(function(e) {

  // When a form on select-products validate and if user had selected a company
  // then we need to show the product comparision library.
  if (jQuery('#projects-referenced-scorecard').find('.col-md-3').length == 0) {
    // If this is the last product removd.
    // Hiding product comparasion box if not shown.
    if (!jQuery('#project_scorecard_main_container_2').hasClass('hidden')) {
      // If products are open the not hiding the container else
      // hiding it.
      if (jQuery('.select-product-for-sc').length == 0) {
        jQuery('#project_scorecard_main_container_2').addClass('hidden');
      }
      else {
        jQuery('#projects-referenced-scorecard').html('<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix no-product-found text-center text-muted"><h4>Click Products Below to Add to Library.</h4></div></div>');
      }
    }
    else {
      // If products are open and the comparision library is hidden
      if (jQuery('.select-product-for-sc').length > 0) {
        jQuery('#project_scorecard_main_container_2').removeClass('hidden');
        jQuery('#projects-referenced-scorecard').html('<div class="col-md-12 col-sm-12 col-xs-12"><div class="clearfix no-product-found text-center text-muted"><h4>Click Products Below to Add to Library.</h4></div></div>');
      }
    }
  }

  // Triggering active scorecard on add new scorecard page.
  if (jQuery('#trigger-active-sc-here').length > 0) {
    var active_sc_nid = jQuery('#trigger-active-sc-here').text();
    if (active_sc_nid) {
      jQuery('.project_scorecard_main_pro').val(active_sc_nid).trigger('change');
    }
  }

  if (jQuery('table.group-raters-table').length > 0) {
    // Going through each table.
    jQuery('table.group-raters-table').each(function(index, el) {
      var table = jQuery(this);
      var rows_count = 0;
      var columns_count = 0;
      var rows_total_total = 0;

      // Getting rows and columns count.
      rows_count = table.find('th').length - 2;
      columns_count = table.find('tbody tr').length - 1;

      if (rows_count > 0 && columns_count > 0) {
        // Calculating rows count first.
        table.find('.row-total-js').each(function(index, el) {
          var ele_parent = jQuery(this).parents('tr');
          var curr_ele = jQuery(this);
          var rows_total = 0;
          ele_parent.find('.row-column-item').each(function(index, el) {
            var row_data = parseInt(jQuery(this).text());
            if (!isNaN(row_data)) {
              rows_total += row_data;
            }
          });
          if (rows_total) {
            curr_ele.find('.form-text').val(parseInt(rows_total));
            rows_total_total += rows_total;
          }
          else {
            curr_ele.find('.form-text').val(0);
          }
        });

        // Total of Total column.
        if (rows_total_total && !isNaN(rows_total_total)) {
          table.find('.column-total-js-total').find('.form-text').val(parseInt(rows_total_total));
        }
        else {
          table.find('.column-total-js-total').find('.form-text').val(0);
        }

        // Trying to get remaining total of columns.
        for (var i = 1; i <= rows_count; i++) {
          var columns_total = 0;
          table.find('tbody tr').each(function(index, el) {
            if (jQuery(this).find('.row-column-item-' + i).length > 0) {
              var col_data = parseInt(jQuery(this).find('.row-column-item-' + i).text());
              if (col_data && !isNaN(col_data)) {
                columns_total += col_data;
              }
            }
          });
          if (columns_total && !isNaN(columns_total)) {
            table.find('.column-total-js-' + i).find('.form-text').val(parseInt(columns_total));
          }
          else {
            table.find('.column-total-js-' + i).find('.form-text').val(0);
          }
        }
      }
    });
  }

  if (jQuery('.calculate-tables-here').length > 0) {
    jQuery('.calculate-tables-here').each(function(index, el) {
      var total_fieldset = 0;
      jQuery(this).find('.column-total-js-total').each(function(index, el) {
        if (jQuery(this).find('.form-text').val()) {
          total_fieldset += parseInt(jQuery(this).find('.form-text').val());
        }
      });

      if (jQuery(this).find('.fieldset-total').length > 0) {
        jQuery(this).find('.fieldset-total').remove();
      }
      if (total_fieldset) {
        var new_html = '<span class="fieldset-total pull-right">Total Score: ' + total_fieldset + '</span>';
        jQuery(this).find('.fieldset-legend').append(new_html);
      }
      else {
        var new_html = '<span class="fieldset-total pull-right">Total Score: 0</span>';
        jQuery(this).find('.fieldset-legend').append(new_html);
      }
    });
  }

  jQuery(document).on('change', '.qbuilder-rating', function() {
    var weight = parseInt(jQuery(this).parents('tr').find('.qbuilder-weight').val());
    var score = jQuery(this).parents('tr').find('.qbuilder-score');
    var this_val = parseInt(jQuery(this).val());

    var score_val = this_val * weight;
    if (score_val && !isNaN(score_val)) {
      score.val(score_val);
    }
    else {
      score.val(0);
    }
  });

  jQuery(document).on('keydown', '.reply-comment-decision', function(event) {
    /* Act on the event */
    var keycode = (event.keyCode ? event.keyCode : event.which);
    if (keycode == 13) {
      event.preventDefault();
      // If Enter key is pressed.
      var comment = jQuery(this).val();
      if (comment) {
        // If something is typed.
        var curr_ele = jQuery(this);
        var cid = jQuery(this).siblings('.field-suffix').find('.fa-check-circle-o').attr('id');

        if (cid) {
          jQuery.ajax({
            url: '/scorecard/save-comment/' + cid,
            type: 'POST',
            data: {comment: comment},
          })
          .done(function(data) {
            if (data.status === 'Success') {
              // If data is success
              curr_ele.addClass('comment-resolved');
              curr_ele.removeClass('resolve-comment');

              if (data.output) {
                curr_ele.parents('.media-body').find('.media:last').before(data.output);

                // If we got some data, then we need to clear it from text field
                // also.
                curr_ele.val('');
              }
            }
            if (data.status === 'Failed') {
              jQuery('#decision-dialogue-box').html('<div class="text-center" style="padding-bottom:25px;"><strong>Some problem occured at our end. Please reload the page and try again!</strong></p></div>');
              jQuery('#decision-dialogue-box').dialog('open');
            }
          })
          .fail(function() {
            jQuery('#decision-dialogue-box').html('<div class="text-center" style="padding-bottom:25px;"><strong>Some technical error occured, please try again!</strong></p></div>');
            jQuery('#decision-dialogue-box').dialog('open');
          })
          .always(function() {
            //
          });
        }
      }
    }
  });

  var getPath = window.location.pathname;
  if(getPath == '/scm/buy-change') {
    jQuery('.case-expand-item .caseouter').each(function() {
      if(jQuery(this).hasClass('case-active')) {
        // jQuery(".category-informations-main option:selected").each(function(i) {
        //   if (i > 0) {
        //     var getVal = jQuery(this).val();
        //     if(getVal) {
        //       jQuery('.category-informations-main').trigger('change');
        //     }
        //   }
        //   else {
        //     //jQuery(".category-informations-main-sub").attr('disabled', 'disabled');    
        //   }
        // });
     }
    });
  }
  jQuery('.resolved-sort-it').unbind('click');
  jQuery('.report-sort-it').unbind('click');

  jQuery(document).on('click', '.same-as-manufacturer-scorecard-product', function () {
   if (jQuery('.same-as-manufacturer-scorecard-product').is(':checked')) {
      jQuery('.custom-ven-choose-company').val(jQuery('.custom-manu-choose-company').val());
      jQuery('.custom-ven-catalog-number').val(jQuery('.custom-manu-catalog-number').val());
      jQuery('.custom-ven-contact-name').val(jQuery('.custom-manu-contact-name').val());
      jQuery('.custom-ven-contact-email').val(jQuery('.custom-manu-contact-email').val());
      jQuery('.custom-ven-contact-phone').val(jQuery('.custom-manu-contact-phone').val());
      jQuery('.custom-ven-contact-number').val(jQuery('.custom-manu-contact-number').val());
      // jQuery('.vendor_group_default .choose-company_field_nid').val(jQuery('.manufacturer_group_default .choose-company_field_nid').val());
    } else {
       jQuery('.custom-ven-choose-company').val('');
      jQuery('.custom-ven-catalog-number').val('');
      jQuery('.custom-ven-contact-name').val('');
      jQuery('.custom-ven-contact-email').val('');
      jQuery('.custom-ven-contact-phone').val('');
      jQuery('.custom-ven-contact-number').val('');
      // jQuery('.vendor_group_default .choose-company_field_nid').val('');
    }
  });

  // Dialog.
  jQuery('#product-already-added').dialog({
    autoOpen: false,
    width: 490,
    modal: true,
    resizable: false,
    buttons: {
      'Ok': function () {
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

  jQuery('#decision-dialogue-box').dialog({
    autoOpen: false,
    width: 490,
    modal: true,
    resizable: false,
    buttons: {
      'Ok': function () {
        jQuery(this).dialog("close");
      }
    },
    open: function () {
      jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
      jQuery('.ui-dialog-titlebar').hide();
    }
  });

  jQuery(document).on('change', '.scorecard-product-attachment-managed input[type=file]', function() {
    var original_id = jQuery(this).attr('id');
    if (original_id.indexOf('--') > 0) {
      var newid = original_id.split('--');
      var id = newid[0];
    }
    else {
      var id = original_id;
    }
    var input = jQuery('input#' + original_id)[0];
    var new_id = '#' + id + '-id-filelist';

    var uniqid = jQuery(this).parents('.scorecard-product-attachment-managed').attr('data');
    if (id == 'edit-field-attachments-upload') {
      var remove_id = 'field_attachments_remove_button';
    }
    else {
      if (getPath == '/scm/preferences') {
        var remove_id = 'physicians_' + uniqid + '_field_attachments_remove_button';
      }
      else {
        var remove_id = 'alert_' + uniqid + '_field_attachments_remove_button';
      }
    }
    jQuery(new_id).html('');
    jQuery(new_id).append('<div class="filelist-outer"></div>');

    for (var i = 0; i < input.files.length; ++i) { 
      var name_file = input.files.item(i).name;
      var n = name_file.length
      if (n > 36) {
        var name_str_file = name_file.substr(0, 36);
        name_str_file += '...';
      }
      else {
        var name_str_file = name_file;
      }
      jQuery(new_id).find('.filelist-outer').append('<span class="filelist-item" title="' + name_file + '">' + name_str_file + '</span> <i class="fa fa-trash-o text-muted" aria-hidden="true" style=" cursor: pointer;" onclick="jQuery(\'input[name=' + remove_id + ']\').trigger(\'mousedown\'); return false;"></i><br>');
    }
    jQuery(new_id).show(['1000', 'clip']);
  });

  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;    
    if ((urlajax.indexOf("/file/ajax/main-container/full-container/product-container/main_container2") === 0 || urlajax.indexOf("/file/ajax/main-container/field_attachments") === 0 || urlajax.indexOf("/file/ajax/left_case_section/are_physicians_primary_children/field_attachments") === 0) && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_value==="Upload") {
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
    }
    if ((urlajax.indexOf("/file/ajax/main-container/full-container/product-container/main_container2") === 0 || urlajax.indexOf("/file/ajax/main-container/field_attachments") === 0 || urlajax.indexOf("/file/ajax/left_case_section/are_physicians_primary_children/field_attachments") === 0) && ajaxOptions.extraData._triggering_element_value==="Remove") {
      var uniqId = jQuery('input[name=' + ajaxOptions.extraData._triggering_element_name + ']').parents('.scorecard-product-attachment-managed').attr('data');
      if (uniqId == 'unique-attachment-product') {
        var filelist_id = 'edit-field-attachments-upload-id-filelist';
      }
      else {
        if (getPath == '/scm/preferences') {
          var filelist_id = 'edit-physicians-' + uniqId + '-field-attachments-upload-id-filelist';
        }
        else {
          var filelist_id = 'edit-alert-' + uniqId + '-field-attachments-upload-id-filelist';
        }
      }
      jQuery('#' + filelist_id).html('');
      jQuery.blockUI({
        //theme:     true,
        baseZ: 2000,
        message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait removing files...</strong></div>',
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
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name === "workflow_add_new_row" || ajaxOptions.extraData._triggering_element_name === "search-criteria"|| ajaxOptions.extraData._triggering_element_name === "audience" || ajaxOptions.extraData._triggering_element_name === "team_members_listing" || ajaxOptions.extraData._triggering_element_name === "member_name_add_new_row")) {
      jQuery.blockUI({
        //theme:     true,
        baseZ: 2000,
        message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while information is loading...</strong></div>',
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

    var AddQuestion = jQuery('.qbuilder-category-select').attr('AddQuestion');
    if(getPath == '/scorecard/new/question-builder'){
      
      AddQuestion = '';
    }
    if(AddQuestion != 'yes' ){    
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name === "select_category_ac")) {
        jQuery.blockUI({
          //theme:     true,
          baseZ: 2000,
          message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while information is loading...</strong></div>',
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
    }
    /*if (urlajax.indexOf("/share-scorecard/" === 0) && getPath == '/scorecard/new/question-builder') {
      var make_this_active = jQuery('.scm-menu-links').find('li.active').next();
      var current_active = jQuery('.scm-menu-links').find('li.active');
      current_active.removeClass('active');
      current_active.find('.active').removeClass('active');
      make_this_active.addClass('active');
      make_this_active.find('a').addClass('active');
    }*/

    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name === "save-scorecard-node") {
      jQuery('html, body').animate({
           scrollTop: "0px"
       }, 500);
    }

  }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if ((urlajax.indexOf("/file/ajax/main-container/full-container/product-container/main_container2") === 0 || urlajax.indexOf("/file/ajax/main-container/field_attachments") === 0 || urlajax.indexOf("/file/ajax/left_case_section/are_physicians_primary_children/field_attachments") === 0) && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_value==="Upload") {
      jQuery.unblockUI();
    }
    if ((urlajax.indexOf("/file/ajax/main-container/full-container/product-container/main_container2") === 0 || urlajax.indexOf("/file/ajax/main-container/field_attachments") === 0 || urlajax.indexOf("/file/ajax/left_case_section/are_physicians_primary_children/field_attachments") === 0) && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_value==="Remove") {
      jQuery.unblockUI();
    }
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name === "workflow_add_new_row" || ajaxOptions.extraData._triggering_element_name === "search-criteria"|| ajaxOptions.extraData._triggering_element_name === "select_category_ac"|| ajaxOptions.extraData._triggering_element_name === "audience" || ajaxOptions.extraData._triggering_element_name === "team_members_listing" || ajaxOptions.extraData._triggering_element_name === "member_name_add_new_row")) {
      jQuery.unblockUI();

      if (ajaxOptions.extraData._triggering_element_name === "team_members_listing") {
        // Show the team edit form.
        jQuery('html, body').animate({
             scrollTop: "0px"
         }, 500, function() {
          /* stuff to do after animation is complete */
          jQuery('#new-team-form-element').show(500);
        });
      }

      if (ajaxOptions.extraData._triggering_element_name === "search-criteria") {
        // If a search criteria is changed, then all the selected options would
        // have gone, and if any products are listed prior to this, then we need
        // to remove those products also, so for this, we shall be triggering 
        // the search button, so that null values triggered will remove the
        // products.

        // But we need to check first, whether there are any products listed or
        // not.

        if (jQuery('#vendor-base-product-container').find('.panel-default').length > 0) {
          // Triggering it.
          jQuery('.trigger-me-on-product-add').trigger('mousedown');
        }
      }
    }
   
    
   if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name === "save-scorecard-node") {
      // Showing edit form
      jQuery('#questionbuilder_scorecard_main_container').show(500);
    }

    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name === "category_informations") {
      // Showing edit form
      jQuery('.categoriesrealtionarea').each(function(index, el) {
        if (jQuery(this).find('i').length > 1) {
          // Deleting first one.
          jQuery(this).find('i').first().parent().remove();
        }
      });
    }
    //console.log(ajaxOptions);
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name === "sharebtnfirst" && ajaxOptions.extraData._triggering_element_value === "Share") {
      //jQuery('.sharebtnhidden').trigger('change');
    }
  });
  //Question Builder add question
  jQuery(document).on( 'click', '.question-add-row-item-link', function ( e ) {
    //console.log('row add');
/* jQuery('.qbuilder-table tbody ').append(jQuery('.qbuilder-table tbody tr.NonDefault').sort(function(b,a){
       return b.getAttribute('order')-a.getAttribute('order');
    }));*/
   
    jQuery('.qbuilder-category-select').attr('AddQuestion','yes');
   
    var prrid = jQuery(this).parents('.form-wrapper').children('.qbuilder-table').attr('id');
    
    var tblrows =jQuery('#'+prrid +' tbody tr');
    var df = 0;
    tblrows.each(function(index) {
      var tblrow = jQuery(this);
      if(df ==0 ){
        if(tblrow.find('.default input').hasClass('NonDefault')) {
          tblrow.find('.default input').val('HasDefault');
          tblrow.find('.default input').toggleClass('HasDefault').toggleClass('NonDefault');
          tblrow.toggleClass('HasDefault').toggleClass('NonDefault');
          tblrow.show();
          df = 1;
        }
      }            
    });
    //question builder row number
    if(getPath == '/scm/scorecard/question-builder'||getPath == '/scorecard/question-builder'||getPath == '/scorecard/new/question-builder') {
      jQuery('.rownumber').text('');
      jQuery('.qbuilder-table tbody').each(function(e){
        var row = jQuery(this).find('tr.HasDefault');
        jQuery(row).each(function(index,value){
          var rownumber1 = index+1;
          var rownumber  = rownumber1+'.';
          //jQuery(this).find('td.trow-inline-link').attr('testnumber',rownumber);
          jQuery(this).find('td.trow-inline-link div.form-type-textfield').before('<div class="rownumber pull-left">' +rownumber + '</div>');
        });
      });
    }
  });
  //Question Builder add question
  jQuery(document).on( 'click', '.remove-add-row-item-link', function ( e ) {
    var prrid = jQuery(this).parents('.HasDefault').attr('id');
    var mpid = jQuery(this).parents('.qbuilder-table').attr('id');
    var newmpid = jQuery('#'+mpid +' tbody tr').last().attr("id");
    var HasDefaultCount = jQuery('#'+mpid+' tbody tr.HasDefault').length;    
    
    jQuery('.qbuilder-category-select').attr('AddQuestion','yes');
    
  
    if(HasDefaultCount >1){
      jQuery('#'+prrid +' input.cleartext').val('');
      jQuery('#'+prrid +' input.clearnumber').val(0);
      jQuery(this).parents('.HasDefault').hide();
      jQuery(this).parents('.HasDefault').toggleClass('HasDefault').toggleClass('NonDefault');
      jQuery(this).parents('.trow-inline-link').siblings('.default').children().toggleClass('HasDefault').toggleClass('NonDefault');
      jQuery(this).parents('.trow-inline-link').siblings('.default').children().val('NonDefault');
      jQuery(this).parents('.trow-inline-link').parent().insertAfter('#'+newmpid);
    }
    else{
      jQuery('#'+prrid +' input.cleartext').val('');
      jQuery('#'+prrid +' input.clearnumber').val(0);
    }


    //question builder row number
    if(getPath == '/scm/scorecard/question-builder'||getPath == '/scorecard/question-builder'||getPath == '/scorecard/new/question-builder') {
      jQuery('.rownumber').text('');
      jQuery('.qbuilder-table tbody').each(function(e){
        var row = jQuery(this).find('tr.HasDefault');
        jQuery(row).each(function(index,value){
          var rownumber1 = index+1;
          var rownumber  = rownumber1+'.';
          //jQuery(this).find('td.trow-inline-link').attr('testnumber',rownumber);
          jQuery(this).find('td.trow-inline-link div.form-type-textfield').before('<div class="rownumber pull-left">' +rownumber + '</div>');
        });
      });
      jQuery('.rownumber').each(function(e){
        console.log(jQuery(this).text());
        if(!jQuery(this).text()){
          jQuery(this).remove();
        }
      });
      
    }
  });
  jQuery(document).on( 'click', '.remove-add-row-item-link-new', function ( e ) {
    var prrid = jQuery(this).parents('.HasDefault').attr('id');
    jQuery('#'+prrid + ' td.trow-inline-link a.remove-add-row-item-link').trigger('click');  
  });
  
  jQuery(document).on( 'click', '.unselect-current-cat', function ( e ) {
    var cvalue = jQuery(this).attr('qcselect');  
    if(cvalue){  
      jQuery('.selected-category-'+cvalue).val('');
      jQuery('.selected-category-'+cvalue).trigger('change');
    }
  });

  if(getPath == '/scm/scorecard/question-builder') {
    var getcat= jQuery('select.qb-selectcategory :selected').val();
    if(getcat){
      jQuery('select.qb-selectcategory').trigger('change');
    }
    /*jQuery('.qbuilder-table tbody ').append(jQuery('.qbuilder-table tbody tr.NonDefault').sort(function(b,a){
       return b.getAttribute('order')-a.getAttribute('order');
    }));*/
  }

  if (jQuery('#questionbuilder_scorecard_main_container').length > 0 && (getPath == '/scm/scorecard/share' || getPath == '/scorecard/share')) {
    //jQuery('#questionbuilder_scorecard_main_container').hide();
  }
  //remove item in decision justification tab
  var removejustificationitem = [];
  jQuery('.justremove-item').each(function(e){
    jQuery(this).click(function(e){
      var pvalue = jQuery(this).attr('pvalue');
      jQuery('.justification-'+pvalue).hide();
      removejustificationitem.push(pvalue);  
      jQuery('.justification-rowremove').val(removejustificationitem);
    });
  });



  //change in document after click on extrenal link show save popup
  jQuery(document).on( 'click', '.changein-document', function ( e ) {
    jQuery(this).parents('.changein-document-popup').attr('changeindocument','yes');
    jQuery('.toggle-case-status-check div').css('pointer-events', 'none');
    var documentsave = jQuery(this).attr('documentsave');
    console.log(documentsave);
    jQuery(this).parents('.changein-document-popup').attr('documentsave',documentsave);
    changeindocumentresult();
    
  });
  jQuery('.changein-document-btn').on('click',function(e){
    jQuery('.changein-document-popup').each(function (e) {
      var changeindocument = jQuery(this).attr('changeindocument');
      var documentsave = jQuery(this).attr('documentsave');    
      if(changeindocument && changeindocument =='yes' && documentsave){

      //on casemanger tabs change project and change case show save popup
      
        console.log(changeindocument);
        console.log(documentsave);
        var content = 'Please save your changes, otherwise your changes will be lost.';
        var parameters =[];
        parameters['type'] = 'button';
        parameters['ID'] = '';
        parameters['selector'] = documentsave;
        parameters['trigerselect'] = 'mousedown';
        confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','no');
      
      
      }
   });
  });
  //on casemanager tab click on anchor tab(extranal link) show save popup      
  jQuery('a').on('click',function(e){
    var href = jQuery(this).attr('href');
   
    if(href != "javascript:void(0);"){
       console.log(href);
      if(changeindocumentresult()){

      e.preventDefault();
      jQuery('.changein-document-popup').each(function (e) {
        var changeindocument = jQuery(this).attr('changeindocument');
        var documentsave = jQuery(this).attr('documentsave');    
        if(changeindocument && changeindocument =='yes' && documentsave){

        //on casemanger tabs change project and change case show save popup
        
          console.log(changeindocument);
          console.log(documentsave);
          var content = 'Please save your changes, otherwise your changes will be lost.';
          var parameters =[];
          parameters['type'] = 'button';
          parameters['ID'] = '';
          parameters['selector'] = documentsave;
          parameters['trigerselect'] = 'mousedown';
          confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','no');
        
        
        }
     });
    }
    }
  });
    /*  jQuery('a').on('click',function(e){
        var href = jQuery(this).attr('href');
        var  varleaveidsction = false;
        if(!href.match("^#")) {
          if(jQuery(this).attr('target')!=='_blank') {
            console.log('out varleaveidsction');
          if(varleaveidsction){
              console.log('in varleaveidsction');
              //e.preventDefault();
              jQuery('.changein-document-popup').each(function (e) {
                var changeindocument = jQuery(this).attr('changeindocument');
                var documentsave = jQuery(this).attr('documentsave');    
                if(changeindocument && changeindocument =='yes' && documentsave){
                  varleaveidsction = true;
                //on casemanger tabs change project and change case show save popup
                  
                  console.log(changeindocument);
                  console.log(documentsave);
                  var content = 'Please save your changes, otherwise your changes will be lost.';
                  var parameters =[];
                  parameters['type'] = 'button';
                  parameters['ID'] = '';
                  parameters['selector'] = documentsave;
                  parameters['trigerselect'] = 'mousedown';
                  confrom_popupsection('', content, 'OK', 'Cancel',parameters,'conformboxpopup','no');
                  changeFlag = 1;
                
                }
              });
            }
          }
        }
      });*/

});


updateList = function() {
  var input = document.getElementById('scm-attachment-upload');
  var output = document.getElementById('scm-upload-filelist');
  // Clearing previous files if any.
  jQuery('#scm-upload-filelist').html('');
  jQuery('#scm-upload-filelist').append('<div class="filelist-outer"></div>');
  // output.innerHTML = '<div class="filelist-outer">';
  for (var i = 0; i < input.files.length; ++i) {
    jQuery('.filelist-outer').append('<span class="filelist-item">' + input.files.item(i).name + '</span>');
  }
  jQuery('#scm-upload-filelist').show(['1000', 'clip']);
}



changeindocumentresult = function (){
  var testing = '';
  var testing1 = '';
  jQuery('.changein-document-popup').each(function (e) {
    var changeindocument = jQuery(this).attr('changeindocument');
    var documentsave = jQuery(this).attr('documentsave');    
    if(changeindocument && changeindocument =='yes' && documentsave){      
      testing1 = true;
    }
  });
  if(testing1){
    testing = true;
  }else{
    testing = false;
  }
  return testing;
}


updateListNew = function (id) {
  var idd = id + '-id';
  var input = document.getElementById(idd);
  var new_id = '#' + id + '-id-filelist';

  jQuery(new_id).parents('.tristate-toggle-button').prev().html('<i class="fa fa-3x fa-check-circle" aria-hidden="true" style="color: #0b6b10;"></i>');

  // Clearing previous files if any.
  jQuery(new_id).html('');
  jQuery(new_id).append('<div class="filelist-outer"></div>');

  for (var i = 0; i < input.files.length; ++i) {
    var img_src = window.URL.createObjectURL(input.files[i]);
    var content = '<a href="' + img_src + '" target="_blank">' + input.files.item(i).name + '</a>';
    // content += '<a href="javascript:void(0)" class="pull-right remove-file-upload" data="' + idd + '" for="' + i + '"><i class="fa fa-trash-o" aria-hidden="true"></i></a>';
    jQuery(new_id).find('.filelist-outer').append('<span class="filelist-item">' + content + '</span><br>');
  }
  jQuery(new_id).show(['1000', 'clip']);
}

updateListScorecard = function (id) {
  var idd = id + '-id';
  var input = document.getElementById(idd);
  var new_id = '#' + id + '-id-filelist';

  // Clearing previous files if any.
  jQuery(new_id).html('');
  jQuery(new_id).append('<div class="filelist-outer"></div>');

  for (var i = 0; i < input.files.length; ++i) {
    var name_file = input.files.item(i).name;
    var n = name_file.length
    if (n > 12) {
      var name_str_file = name_file.substr(0, 12);
      name_str_file += '...';
    }
    else {
      var name_str_file = name_file;
    }
    jQuery(new_id).find('.filelist-outer').append('<span class="filelist-item" title="' + name_file + '">' + name_str_file + '</span><br>');
  }
  jQuery(new_id).show(['1000', 'clip']);
}

// Sorting columns in project manager comments.
sortcolumns = function(column) {
  var new_sort = column;
  new_sort = new_sort.toLowerCase().replace(/\b[a-z]/g, function(letter) {
      return letter.toUpperCase();
  });

  jQuery('.replace-my-text-here-for-sorting').html(new_sort + ' <span class="caret"></span>');
  jQuery('.' + column + '-sort-it-instead').click();
}

filter_vendors = function(element, id) {
  // var find_in = jQuery('#' + id);
  var value = jQuery(element).val();
  if (value) {
    jQuery('#' + id + " .vendor-title-search").each(function() {
      if (jQuery(this).text().search(value) > -1) {
          jQuery(this).parents('.remove-hide-this-product').show(400);
      }
      else {
          jQuery(this).parents('.remove-hide-this-product').hide(400);
      }
    });
  }
  else {
    jQuery('#' + id + " .vendor-title-search").parents('.remove-hide-this-product').show(400);
  }
}

open_payments_site = function(pageURL, w, h) {
  var left = (screen.width/2)-(w/2);
  var top = (screen.height/2)-(h/2);
  window.open(pageURL, 'toolbar=no, location=no, directories=no, status=no, menubar=no, copyhistory=no, width='+w+', height='+h+', top='+top+', left='+left);
  return false;
}

function confrom_popupsection(title, content, btn1text, btn2text, parameters ,id,action) {
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
                }else{
                  action_trigger_data(parameters['type'],parameters['ID'],parameters['selector'],parameters['trigerselect']);
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
           }],
    open: function () {
      jQuery('.ui-dialog-titlebar').hide();
    }
  });
}   

function action_trigger_data(type,ID,selector,trigerselect) {
  if(type =='button'){
    if(trigerselect == 'mousedown'){
      jQuery('.'+selector).trigger('mousedown');
    }
    if(trigerselect == 'click'){
      jQuery('.'+selector).trigger('click');
    }
  }
  else{
    jQuery('select.'+trigerselect).val(ID).trigger('change');
  }
}