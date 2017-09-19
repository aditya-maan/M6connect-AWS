Drupal.behaviors.m6connect_program_spending = {
  attach: function (context, settings) {
    // Working for pager
    jQuery('.respread-button-custom').hide();
    var getPagerId = jQuery('.datatable_page_id').val();
    if(getPagerId) {
      if(jQuery('.page_number_id').val() != 'drop') {
        jQuery('.page-range-'+getPagerId).css('background-color','#eee');
        jQuery('.page-range-'+getPagerId).css('pointer-events','none'); 
      }   
    }
    jQuery('.get-removed').unbind('click').bind('click',function () {
      jQuery(this).siblings('.workflow-remove-submit').trigger('mousedown');
    });
  
  jQuery('.respread-button-custom').unbind('click').bind('click',function (e) {
      e.preventDefault();
      jQuery('.new-asset-value-header').show();
      jQuery('.new-asset-value-row-spread').removeClass('hidden');
      jQuery('.new_asset_val_total').show();
    });

    jQuery('.asset_cost').trigger('keyup');
    jQuery('.asset_installation').trigger('keyup');
    jQuery('.asset_outside_consultants').trigger('keyup');
    jQuery('.asset_internal_charges').trigger('keyup');
    jQuery('.asset_percentage').trigger('keyup');    
    
  // Column resizer for all cost manager table
    jQuery("table.m6connect-custom-program-table th").resizable({
      handles: "e",
      minHeight: jQuery("table.m6connect-custom-program-table th:first").height(),
      maxHeight: jQuery("table.m6connect-custom-program-table th:first").height(),
      minWidth: 40,
      resize: function (event, ui) {
        var sizerID = "#" + jQuery(event.target).attr("id") + "-sizer";
        jQuery(sizerID).width(ui.size.width);
      }
    });

    jQuery('#edit-invoice-amount').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
      // If the key up is done when a spread asset spending is being edited, then
      // we need to trigger a change for select box asset_description.
      // So first judging if we have to do this.
      var getNidEdeit = jQuery('.project_spending_nid').val();
      if (getNidEdeit) {
        var getCheckedtAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
        if (getCheckedtAsset == 'Spread') {
          var getcheckedyes_no = jQuery('.spread-category-radio input[type=radio]:checked').val();
          if (getcheckedyes_no == 'Yes') {
            if (context == document) {
              change_spending_auto_spread();
            }
          }
        }
        else {
          jQuery('.asset_description').trigger('change');
        }
      }
    });

    jQuery('#edit-invoice-amount-spending').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
      // If the key up is done when a spread asset spending is being edited, then
      // we need to trigger a change for select box asset_description.
      // So first judging if we have to do this.
      var getNidEdeit = jQuery('.project_spending_nid').val();
      if (getNidEdeit) {
        var getCheckedtAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
        if (getCheckedtAsset == 'Spread') {
          var getcheckedyes_no = jQuery('.spread-category-radio input[type=radio]:checked').val();
          if (getcheckedyes_no == 'Yes') {
            if (context == document) {
              change_spending_auto_spread();
            }
          }
        }
        else {
          jQuery('.asset_description').trigger('change');
        }
      }
    });
    jQuery('#edit-etc-amount').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.form-type-textfield .unit_cost').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.form-type-textfield .po_total').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    }); 
    jQuery('#edit-line-item-amt-contgency').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.po_amt_discount').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.po_amt_sales_tax_amt').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.po_amt_other_cost').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.po_amt_discount_sh').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });     
    jQuery('.commit-amt-quarter-three').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.etc-amt-quarter-three').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.etc-amt-quarter-fourth').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.etc-amt-current-year').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.etc-beyond-year').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.commit-amt-quarter-fourth').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.commit-beyond-year').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.asset_cost').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.asset_installation').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.asset_outside_consultants').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.asset_internal_charges').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    jQuery('.field_est_line_item_amt').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });  
    jQuery('.get_current_asset_value').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });  
    jQuery('.new_asset_value').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
    
    function format2(n, currency) {
      return currency + " " + n.toFixed().replace(/(\d)(?=(\d{3}))/g, "$1,");
    }
    var format = function (num) {
      if (!num || num === "0" || num === 0) {
        return "$";
      }
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
        return("$-" + formatted + ((parts) ? "." + parts[1].substr(1, 2) : ""));
      }
      else {
        return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));
      }
    };
    // ==========================
    // End work for adding $ sign
    // Start work for adding % sign
    (function($) {
      $.fn.setCursorPosition = function(pos) {
        if ($(this).get(0).setSelectionRange) {
          $(this).get(0).setSelectionRange(pos, pos);
        } 
        else if ($(this).get(0).createTextRange) {
          var range = $(this).get(0).createTextRange();
          range.collapse(true);
          range.moveEnd('character', pos);
          range.moveStart('character', pos);
          range.select();
        }
      }
    }(jQuery));
    jQuery("#edit-capital-contingency").keyup(function() {
      if (jQuery(this).val().split('').pop() !== '%') {
        jQuery(this).val($(this).val() + "%");
        jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });
    jQuery("#edit-line-item-per-contgency").keyup(function() {
      if (jQuery(this).val().split('').pop() !== '%') {
        jQuery(this).val($(this).val() + "%");
        jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });
    jQuery(".po_amt_sales_tax_per").keyup(function() {
      if (jQuery(this).val().split('').pop() !== '%') {
        jQuery(this).val($(this).val() + "%");
        jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });
    jQuery(".field_conigency_percentage").keyup(function() {
      if (jQuery(this).val().split('').pop() !== '%') {
        jQuery(this).val($(this).val() + "%");
        jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });
    jQuery(".asset_percentage").keyup(function() {
      if (jQuery(this).val().split('').pop() !== '%') {
        jQuery(this).val($(this).val() + "%");
        jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });
  setTimeout(function() {
      jQuery(".messages--status").remove()
    }, 20000);
  jQuery('.rest-all-filter-spending .resesting').click(function (e) {
      jQuery('.new-record-reset-setting-btn').trigger('click');
    });
    jQuery('.resesting').click(function (e) {
    jQuery('.new-record-reset-setting-btn').trigger('click');
    });
  jQuery('.edit-spending-detail', context).click(function (e) {
      jQuery('.project_spending_main_cust').attr('for','open');
      jQuery('.project_spending_main_cust').attr('data','edit');      
      jQuery('.project_spending_main_cust').show();
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.custom-submit-reset').show();
      jQuery('#split-edit-value').remove();
      e.preventDefault();
      var spentID = jQuery(this).attr('for');
      var spentUrlID = getUrlParameter('sid');
      if(spentUrlID) { 
        if(spentID == spentUrlID) {
          jQuery('.project_spending_nid').val(spentID);  
        }  
        else {
          var proId = jQuery('.project-program-spending-sel').val();  
          window.location.href="/program/spending?pid="+proId+'&sid='+spentID;
        }
      }
      else {    
        jQuery('.project-program-sel-spending').val(spentID).trigger('change');
        jQuery('.project_spending_nid').val(spentID);      
      }
      jQuery('html, body').animate({
        scrollTop: "0px"
      }, 800);    
    });
    // get budget id from query string.
    var spendingId = getUrlParameter('sid');
    if(!isNaN(spendingId)) { 
      jQuery('.project-program-sel-spending').val(spendingId).trigger('change');
      jQuery('.project_spending_main_cust').attr('for','open');
      jQuery('.project_spending_main_cust').attr('data2','querystring');
      jQuery('.project_spending_main_cust').show();
      jQuery('.project_spending_nid').val(spendingId);
    } 
    jQuery('.fa-times-filter').unbind('click').bind('click',function () {
      var tt = jQuery(this).attr('id');
      jQuery('#'+tt).trigger('click');
    });
  jQuery('.pager-load-more-to').change(function (e) { 
      var getPager = jQuery(this).val();
      jQuery('.datatable_page_id').val(getPager);
      jQuery('.page_number_id').val('drop');    
      if(getPager) {
        jQuery('.page-range-'+getPager).trigger('click');
      }
    });
  jQuery('.asset-based-load-more-to').change(function (e) { 
      var getPager = jQuery(this).val();
      if(getPager) {
        jQuery('.asset-data-'+getPager).trigger('click');
      }  
    });
  jQuery('body .filter-sort').unbind('click').bind('click',function () {
      var getId = jQuery(this).attr('id');    
      var getstatus = jQuery('body').find('.'+getId).attr('data');
      if(getstatus == 'hiddenCus') {
        jQuery('body').find('.'+getId).show();
        jQuery('body').find('.rest-all-filter-spending').show();
        jQuery('body').find('.'+getId).attr('data', 'showCus');  
        jQuery('body').find('.'+getId+'-def').hide();   
      }
      else if(getstatus == 'showCus') {
        jQuery('body').find('.'+getId).hide();
        jQuery('body').find('.rest-all-filter-spending').hide();
        jQuery('body').find('.'+getId).attr('data', 'hiddenCus');  
        if(jQuery('.'+getId+' form select').val()) {
          jQuery('body').find('.'+getId+'-def').show();
        }
      }
    }); 
    jQuery('.invoice_number').change(function (e) {
      var getNumber = jQuery(this).val();
      var ProNumber = jQuery('.project-program-spending-sel').val();
      jQuery.post( '/check-project-availablity/'+ getNumber +'/spending/'+ProNumber, function( data ) { 
        if(data.access == 0) {
          jQuery('.project-avail-status .text-danger').text(data.message);
          jQuery('.project-avail-status .text-success').text('');
        }
        if(data.access == 1) {
          jQuery('.project-avail-status .text-danger').text('');  
          jQuery('.project-avail-status .text-success').text('');
        }     
      });
    });
    jQuery("input:checkbox.invoice-recon-update").click(function() {
      var getSpendingNode = jQuery(this).attr('for');
      var status = jQuery(this).val();
      jQuery.post( '/update-spending-status/'+getSpendingNode+'/'+status, function( data ) { 
        if(data.status == 'update') {
          jQuery('.project-program-spending-sel').trigger('change');
        }
      });
    });
    
    jQuery('input:checkbox.image-remove-update').unbind('click').bind('click',function () {
      var getFid = jQuery(this).val();
      var nodeId = jQuery(this).attr('for');
      jQuery('#file-remove-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to remove this attachement?</strong><input type="hidden" class="file-remove-data" value="/update-image-reove/'+getFid+'/'+nodeId+'" /></p></div>');
      jQuery('#file-remove-dialog').dialog('open');
    });

    jQuery('.upload_minus').unbind('click').bind('click',function () {
      jQuery(this).parents('.image-preview-item').find('input:checkbox.image-remove-update').trigger('click');
    });

    jQuery('.custom-reset-button').click(function (e) {
      jQuery('.project_spending_main_cust').hide();
      jQuery('.custom-submit-reset').hide();
      jQuery('#project_spending_main_container').attr('for', 'closed');
    });    
    jQuery('.filter-custom-range').unbind('click').bind('click',function () {
      var getProId = jQuery(this).attr('for');  
      var lastRowCommitNid = jQuery(".m6connect-program-commitment-table tr").last().attr('for');       
      var totalRecords = jQuery(this).val();
      var startingRange = jQuery('.commitment-data-load-more-from').val();
      var endRange = jQuery('.commitment-data-load-more-to').val();
      jQuery.post( '/load-more-data/spending/'+ getProId +'/'+startingRange+'/'+endRange, function( data ) { 
        if(data.tableDate!=''){
          jQuery(".prgram-spenidng-cus-listing-table tbody").html(data.tableDate);
          Drupal.attachBehaviors(jQuery('body'));
        }     
      });
    });
    jQuery('.invoice_amount').blur(function (e) {
      if(context == document) {
        // If the key up is done when a spread asset spending is being edited, then
        // we need to trigger a change for select box asset_description.
        // So first judging if we have to do this.
        var getNidEdeit = jQuery('.project_spending_nid').val();
        if (getNidEdeit) {
          var getCheckedtAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
          if (getCheckedtAsset == 'Spread') {
            var getcheckedyes_no = jQuery('.spread-category-radio input[type=radio]:checked').val();
            if (getcheckedyes_no == 'Yes') {
              if (context == document) {
                change_spending_auto_spread();
              }
            }
          }
          else {
            jQuery('.asset_description').trigger('change');
          }
        }
      }
    });
    // =============================================  POPUP FOR SPLIT AND SPREAD ============================= //  
   jQuery('.custom-add-asset-button').unbind('click').bind('click',function (e) {
     e.preventDefault();
     var getInvAmt = jQuery('.invoice_amount').val();
     if(getInvAmt != '') { 
       jQuery('.adding-new-assets-amount').text(getInvAmt);
       jQuery('.main-aset-container').show();
       jQuery('#custom-form-inline-radio').show();
       jQuery('.asset-data-rendration').hide();
     }
     else {
       e.preventDefault();
       jQuery('#nothingin-amt-field-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>To use this feature, please enter amount first.<br> Amount cannot be blank.</strong></p></div>');
       jQuery('#nothingin-amt-field-dialog').dialog('open');    
     }
   });
   jQuery('.custom-clearall-first').unbind('click').bind('click',function (e) {
     e.preventDefault();
     jQuery('#clear-split-spread').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to delete all and respread or split?</strong></p></div>');
     jQuery('#clear-split-spread').dialog('open');         
   });
   
   // When add to asset is converted to Green
   jQuery('.custom-add-asset-button-success').unbind('click').bind('click',function (e) {
     var getNidEdeit = jQuery('.project_spending_nid').val();
     if(getNidEdeit) {
       e.preventDefault();
       var getInvAmt = jQuery('.invoice_amount').val();
       if(getInvAmt != '') { 
         jQuery('.adding-new-assets-amount').text(getInvAmt);
         jQuery('.main-aset-container').show();
         jQuery('#custom-form-inline-radio').show();
         jQuery('.asset-data-rendration').hide();
         jQuery('.get-total-section').hide();
       }
       else {
         e.preventDefault();
         jQuery('#nothingin-amt-field-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>To use this feature, please enter amount first.<br> Amount cannot be blank.</strong></p></div>');
         jQuery('#nothingin-amt-field-dialog').dialog('open');    
       }
     }
   });
   
   // By default hiding Split spread and Spread's Yes or No radio
   // Also hiding complete form for split spread
   jQuery('.main-aset-container').hide();
   jQuery('#custom-form-inline-radio').hide();
   jQuery('.spread-options-custom').hide();
   jQuery('#main-class-assets').hide();
   jQuery('#adding-new-assets-amount').hide();
   jQuery('.main-asset-custom-btn').hide();  
   // Performing action when clicking on Split and spread radio
   jQuery('.asset-category-radio').unbind('click').bind('click', function (e) {
     if(jQuery(this).is(":checked")) {
       var getCatVal = jQuery(this).val();
       if(getCatVal == 'Split') {
         // If a split is triggered, then we need to check if the split table
         // is empty. If not, then triggering the respective element.
         var row_count = jQuery('.project-assetes-main-table > tbody > tr').length;
         if (row_count > 3) {
           // If the table is not empty.
           jQuery('.reset-split-table-trigger').trigger('mousedown');
         }
         else {
           // If table is empty.
           jQuery('.main-aset-container').show();
           jQuery('#main-class-assets').show();
           jQuery('.asset-category-header-split').show();
           jQuery('.asset-category-header-spread').hide();
           jQuery('.spread-options-custom').hide();
           jQuery('#adding-new-assets-amount').show();
           jQuery('.asset-cost-total-var').show();
           jQuery('#asset-form-title-custom').show();
           jQuery('#asset-form-title-custom strong').text('Add to Asset(s) - Split - apply invoice to the respective category(s).');
           jQuery('.main-asset-custom-btn').show();  
           jQuery('.get-total-section').hide();
         }
       }
       if(getCatVal == 'Spread') {
         jQuery('.main-aset-container').show();
         jQuery('#main-class-assets').hide();
         jQuery('.spread-options-custom').show();
         jQuery('.asset-category-header-split').hide();
         jQuery('.asset-category-header-spread').show();
         jQuery('#adding-new-assets-amount').show();
         jQuery('.asset-cost-total-var').hide();
         jQuery('#asset-form-title-custom').show();
         jQuery('#asset-form-title-custom strong').text('Add to Asset(s) - Spread - apply invoice to the respective category(s).');
         jQuery('.main-asset-custom-btn').show();   
         jQuery('.get-total-section').hide();
       } 
     }
   });
   jQuery('.main-asset-custom-btn input').unbind('click').bind('click', function (e) {
     jQuery('.asset-data-rendration').show();
     jQuery('#main-class-assets').hide();
     jQuery('.main-aset-container').hide();
     jQuery('#asset-form-title-custom').hide();
     jQuery('#custom-form-inline-radio').hide();
     jQuery('#adding-new-assets-amount').hide();
     jQuery('.spread-options-custom').hide();
     jQuery('.main-asset-custom-btn').hide();
     jQuery('.get-total-section').show();
     var getButtonVal = jQuery(this).val();
     if(getButtonVal == 'Confirm') {
       jQuery('.custom-add-asset-button-success').show();
       jQuery('.custom-add-asset-button').hide();   
     }
     else {
       jQuery('.custom-add-asset-button-success').hide();
       jQuery('.custom-add-asset-button').show();   
     }
   });
   var tblrows = jQuery(".project-assetes-main-table tbody tr");       
   tblrows.once().each(function (index) {
     var tblrow = jQuery(this);
     // Triggering new row
     jQuery('.asset_category_all_split').change(function () {
       jQuery('.assets-workflow-action-add-new-assets').trigger('mousedown');     
     });
     jQuery('.asset_category_all_spread').change(function () {         
       jQuery('.assets-workflow-action-add-new-assets').trigger('mousedown');    
     });
     // Work for tool tip on split popup
     tblrow.find('.asset_cost_tool_tip_hover').hover(function () {
       var text = tblrow.find('.asset_cost_tool_tip').text();
       if(text) {
         jQuery('.asset_cost_tool_tip_new').text('Previous value ' + text);
       }
     }, function () {
       var text = tblrow.find('.asset_cost_tool_tip').text();
       if(text) {
         jQuery('.asset_cost_tool_tip_new').text('Previous value ' + text);
       }
     });
     tblrow.find('.asset_installation_tool_tip_hover').hover(function () {
       var text = tblrow.find('.asset_installation_tool_tip').text();
       if(text) {
         jQuery('.asset_installation_tool_tip_new').text('Previous value ' + text);
       }
     }, function () {
       var text = tblrow.find('.asset_installation_tool_tip').text();
       if(text) {
         jQuery('.asset_installation_tool_tip_new').text('Previous value ' + text);
       }
     });
     
     tblrow.find('.asset_outside_tool_tip_hover').hover(function () {
       var text = tblrow.find('.asset_outside_tool_tip').text();
       if(text) {
         jQuery('.asset_outside_tool_tip_new').text('Previous value ' + text);
       }
     }, function () {
       var text = tblrow.find('.asset_outside_tool_tip').text();
       if(text) {
         jQuery('.asset_outside_tool_tip_new').text('Previous value ' + text);
       }
     });
     
     tblrow.find('.asset_internal_tool_tip_hover').hover(function () {
       var text = tblrow.find('.asset_internal_tool_tip').text();
       if(text) {
         jQuery('.asset_internal_tool_tip_new').text('Previous value ' + text);
       }
     }, function () {
       var text = tblrow.find('.asset_internal_tool_tip').text();
       if(text) {
         jQuery('.asset_internal_tool_tip_new').text('Previous value ' + text);
       }
     });
     // End work for tool tip
     // Start work for get the current asset value on change of asset name
     tblrow.find('.asset_description').once().change(function (e) {
    if(context == document) {
      var getAsset = tblrow.find('.asset_description').val();
      tblrow.find('.asset_node_nid').val(getAsset);
      if(getAsset) {
        var getInvAmt = jQuery('.invoice_amount').val();
        var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');
        var updatedAsset = getAsset.split('-'); 
        jQuery.post( '/get-current-asset/'+invAmtFnl+'/'+updatedAsset[0], function( data ) {
          var calCurrAssetVal = 0.00;
          if (data.CurrentAsseVal) {
            calCurrAssetVal = data.CurrentAsseVal;
          }
      tblrow.find('.get_current_asset_value').val(format(calCurrAssetVal));
          tblrow.find('.get_current_asset_value_hidden').val(calCurrAssetVal);
          jQuery('.asset_node_nid').val(invAmtFnl);
          var getCheckedtAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
          if (getCheckedtAsset == 'Spread') {
            change_spending_auto_spread();
          }
          else if(getCheckedtAsset == 'Split') {
            tblrow.find('.asset_cost_tool_tip').text(format(data.AssetCost));
            tblrow.find('.asset_installation_tool_tip').text(format(data.AssetInstallation));
            tblrow.find('.asset_outside_tool_tip').text(format(data.AssetConsu));
            tblrow.find('.asset_internal_tool_tip').text(format(data.AssetInterCharge));
          }
        }).done(function() {
          jQuery('.asset_cost').trigger('keyup');
          jQuery('.asset_installation').trigger('keyup');
          jQuery('.asset_outside_consultants').trigger('keyup');
          jQuery('.asset_internal_charges').trigger('keyup');
        });
      }
      else {
        tblrow.find('.get_current_asset_value').val(0);
        tblrow.find('.get_current_asset_value_hidden').val(0);
      }
   }
  });
    // Work for split section Asset Cost, Installation, Outside Consultant,Internal Charge    
    jQuery('.asset_cost').keyup(function (e) {
      // Showing new asset value for the current row.
      if (e.keyCode) {
        jQuery(this).parents('td').siblings('.new-asset-value-row-split').removeClass('hidden');
        jQuery('.new-asset-value-header').show();
    }
    var getInvAmt = jQuery('.invoice_amount').val();
      var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');
      var getAssetCost = tblrow.find(".asset_cost").val();    
      var getAssetInst = tblrow.find(".asset_installation").val();
      var getAssetCons = tblrow.find(".asset_outside_consultants").val();
      var getAssetIntChange = tblrow.find(".asset_internal_charges").val();
      getAssetCost = (getAssetCost)?getAssetCost.replace(/[^\d\.\-]/g, ''):0;
      getAssetInst = (getAssetInst)?getAssetInst.replace(/[^\d\.\-]/g, ''):0;
      getAssetCons = (getAssetCons)?getAssetCons.replace(/[^\d\.\-]/g, ''):0;
      getAssetIntChange = (getAssetIntChange)?getAssetIntChange.replace(/[^\d\.\-]/g, ''):0;
      if (!getAssetCost) {
        getAssetCost = 0;
      }
      if (!getAssetInst) {
        getAssetInst = 0;
      }
      if (!getAssetCons) {
        getAssetCons = 0;
      }
      if (!getAssetIntChange) {
        getAssetIntChange = 0;
      }
      var subTotal = parseFloat(getAssetCost) + parseFloat(getAssetInst) + parseFloat(getAssetCons) + parseFloat(getAssetIntChange);
      var currentAssetVal = tblrow.find(".get_current_asset_value_hidden").val();
      if(currentAssetVal) {
        var currentAsstAmt = currentAssetVal.replace(/[^\d\.\-]/g, '');
        currentAsstAmt = parseFloat(currentAsstAmt) + parseFloat(subTotal);
        tblrow.find(".new_asset_value").val(format(currentAsstAmt));
      }
      else {
        subTotal = (subTotal)?subTotal:0;
        tblrow.find(".new_asset_value").val(format(subTotal));
      }
      // Calculating subtotal asset Cost Column Calculation
      var grandTotalCost = 0;
      jQuery(".asset_cost").each(function () {
        var getstvalAmt = jQuery(this).val();
        if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCost += isNaN(stvalAmt) ? 0 : stvalAmt; }
        else { grandTotalCost = 0; }
      });
      var grandTotalCost_format = format(grandTotalCost);
      if (grandTotalCost_format == '$') {
        grandTotalCost_format = '$0.00';
      }
      else {
        // grandTotalCost_format = grandTotalCost_format.toFixed(2);
      }
      jQuery('.asset_cost_total').text(grandTotalCost_format);
      // Asset Installation Column Calculation
      var grandTotalInst = 0;
      jQuery(".asset_installation").each(function () {
        var getstvalAmt = jQuery(this).val();
        if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInst += isNaN(stvalAmt) ? 0 : stvalAmt; }
        else { grandTotalInst = 0; }
      });
      var grandTotalInst_format = format(grandTotalInst);
      if (grandTotalInst_format == '$') {
        grandTotalInst_format = '$0.00';
      }
      else {
        // grandTotalInst_format = grandTotalInst_format.toFixed(2);
      }
      jQuery('.asset_installation_total').text(grandTotalInst_format);
      // Asset Consultants Column Calculation
      var grandTotalCons = 0;
      jQuery(".asset_outside_consultants").each(function () {
        var getstvalAmt = jQuery(this).val();
        if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCons += isNaN(stvalAmt) ? 0 : stvalAmt; }
        else { grandTotalCons = 0; }
      });
      var grandTotalCons_format = format(grandTotalCons);
      if (grandTotalCons_format == '$') {
        grandTotalCons_format = '$0.00';
      }
      else {
        // grandTotalCons_format = grandTotalCons_format.toFixed(2);
      }
      jQuery('.asset_consultant_total').text(grandTotalCons_format);
      // Asset Internal charge Column Calculation
      var grandTotalInt = 0;
      jQuery(".asset_internal_charges").each(function () {
        var getstvalAmt = jQuery(this).val();
        if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInt += isNaN(stvalAmt) ? 0 : stvalAmt; }
        else { grandTotalInt = 0; }
      });
      var grandTotalInt_format = format(grandTotalInt);
      if (grandTotalInt_format == '$') {
        grandTotalInt_format = '$0.00';
      }
      jQuery('.asset_internal_charge_total').text(grandTotalInt_format);
      //Asset Percentage Calculation
      var grandTotalPer = 0;
      jQuery(".asset_percentage").each(function () {
        getStval = jQuery(this).val();
        if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotalPer += isNaN(stval) ? 0 : stval; }
        else { grandTotalPer = 0; }
      });
      jQuery('.percentage-remain-count').text(grandTotalPer.toFixed(2) +'%');    
      //Asset Current asset value Calculation
      var granCurrentAsset = 0;
      jQuery(".get_current_asset_value").each(function () {
        var getstvalAmt = jQuery(this).val();
        if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); granCurrentAsset += isNaN(stvalAmt) ? 0 : stvalAmt; }
        else { granCurrentAsset = 0; }
      });
      var granCurrentAsset_format = format(granCurrentAsset);
      if (granCurrentAsset_format == '$') {
        granCurrentAsset_format = '$0.00';
      }
      jQuery('.current_asset_val_total').text(format(granCurrentAsset_format));
      //Asset New asset value calculation
      var granNewAsset = 0;
      var getCheckedtAssetType = jQuery(".asset-category-radio input[type='radio']:checked").val();
      if (getCheckedtAssetType == 'Split') {
        jQuery(".new_asset_value").each(function () {    
          var getstvalAmtNew = jQuery(this).val();
          if(getstvalAmtNew) { 
            var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
            granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
          }
          else { granNewAsset = 0; }
        });
      }
      else if (getCheckedtAssetType == 'Spread') {
        jQuery(".new_asset_value_spread").each(function () {
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
          granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
        else { granNewAsset = 0; }
      });
    }
    jQuery('.new_asset_val_total').text(format(granNewAsset));  
    // Calculating Main Varience
    var getAllSubtotal = (invAmtFnl) -(grandTotalInt + grandTotalCons + grandTotalInst + grandTotalCost);
    var getAllSubtotal_format = format(getAllSubtotal);
    if (getAllSubtotal_format == '$') {
      getAllSubtotal_format = '$0.00';
    }
    else {
      // getAllSubtotal_format = getAllSubtotal_format.toFixed(2);
    }
    var finalVarience = (getAllSubtotal < 0 )?'<span>Amount exceeds the <br />maximum invoice Amount.</span>':'<span>Amount <br />Remaining: '+ getAllSubtotal_format +'</span>';
    jQuery('.asset-cost-total-var').html(finalVarience);
    if(getAllSubtotal < 0) {
      jQuery(".custom-confirm-button").attr('disabled','disabled');  
    }
    else {
      jQuery(".custom-confirm-button").removeAttr('disabled');  
    }
    var grandTotal = 0;
    jQuery(".asset_percentage").each(function () {
      var getStval = jQuery(this).val();
      if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotal += isNaN(stval) ? 0 : stval; }
      else { grandTotal = 0; }
    });
    jQuery('.percentage-remain-count-varience').text(100 - grandTotal.toFixed(2) +'%');
  });
  jQuery('.asset_installation').keyup(function () { 
    var getInvAmt = jQuery('.invoice_amount').val();
    var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');
    var getAssetCost = tblrow.find(".asset_cost").val();    
    var getAssetInst = tblrow.find(".asset_installation").val();
    var getAssetCons = tblrow.find(".asset_outside_consultants").val();
    var getAssetIntChange = tblrow.find(".asset_internal_charges").val();
    getAssetCost = (getAssetCost)?getAssetCost.replace(/[^\d\.\-]/g, ''):0;
    getAssetInst = (getAssetInst)?getAssetInst.replace(/[^\d\.\-]/g, ''):0;
    getAssetCons = (getAssetCons)?getAssetCons.replace(/[^\d\.\-]/g, ''):0;
    getAssetIntChange = (getAssetIntChange)?getAssetIntChange.replace(/[^\d\.\-]/g, ''):0;
    if (!getAssetCost) {
      getAssetCost = 0;
    }
    if (!getAssetInst) {
      getAssetInst = 0;
    }
    if (!getAssetCons) {
      getAssetCons = 0;
    }
    if (!getAssetIntChange) {
      getAssetIntChange = 0;
    }
    var subTotal = parseFloat(getAssetCost) + parseFloat(getAssetInst) + parseFloat(getAssetCons) + parseFloat(getAssetIntChange);
    var currentAssetVal = tblrow.find(".get_current_asset_value_hidden").val();
    if(currentAssetVal) {
      var currentAsstAmt = currentAssetVal.replace(/[^\d\.\-]/g, '');
      currentAsstAmt = parseFloat(currentAsstAmt) + parseFloat(subTotal);
      tblrow.find(".new_asset_value").val(format(currentAsstAmt));
    }
    else {
    subTotal = (subTotal)?subTotal:0;
      tblrow.find(".new_asset_value").val(format(subTotal));
    }
    var calculatePer = (subTotal/invAmtFnl*100);      
    tblrow.find(".asset_percentage").val(calculatePer.toFixed(2));    
    // Calculating subtotal asset Cost Column Calculation
    var grandTotalCost = 0;
    jQuery(".asset_cost").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCost += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { grandTotalCost = 0; }
    });
    var grandTotalCost_format = format(grandTotalCost);
    if (grandTotalCost_format == '$') {
      grandTotalCost_format = '$0.00';
    }
    else {
      // grandTotalCost_format = grandTotalCost_format.toFixed(2);
    }
    jQuery('.asset_cost_total').text(grandTotalCost_format);
  // Asset Installation Column Calculation
    var grandTotalInst = 0;
    jQuery(".asset_installation").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInst += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { grandTotalInst = 0; }
    });
    var grandTotalInst_format = format(grandTotalInst);
    if (grandTotalInst_format == '$') {
      grandTotalInst_format = '$0.00';
    }
    else {
      // grandTotalInst_format = grandTotalInst_format.toFixed(2);
    }
    jQuery('.asset_installation_total').text(grandTotalInst_format);
  // Asset Consultants Column Calculation
    var grandTotalCons = 0;
    jQuery(".asset_outside_consultants").each(function () {
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCons += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { grandTotalCons = 0; }
    });        
    var grandTotalCons_format = format(grandTotalCons);
    if (grandTotalCons_format == '$') {
      grandTotalCons_format = '$0.00';
    }
    else {
      // grandTotalCons_format = grandTotalCons_format.toFixed(2);
    }
    jQuery('.asset_consultant_total').text(grandTotalCons_format);
  // Asset Internal charge Column Calculation
    var grandTotalInt = 0;
    jQuery(".asset_internal_charges").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInt += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { grandTotalInt = 0; }
    });
    var grandTotalInt_format = format(grandTotalInt);
      if (grandTotalInt_format == '$') {
        grandTotalInt_format = '$0.00';
      }
      jQuery('.asset_internal_charge_total').text(grandTotalInt_format);
  var grandTotalPer = 0;
    jQuery(".asset_percentage").each(function () {
      getStval = jQuery(this).val();
      if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotalPer += isNaN(stval) ? 0 : stval; }
      else { grandTotalPer = 0; }
    });
  jQuery('.percentage-remain-count').text(grandTotalPer.toFixed(2) +'%');
      
    // Calculating Main Varience
    var getAllSubtotal = (invAmtFnl) -(grandTotalInt + grandTotalCons + grandTotalInst + grandTotalCost);
    var getAllSubtotal_format = format(getAllSubtotal);
    if (getAllSubtotal_format == '$') {
      getAllSubtotal_format = '$0.00';
    }
    else {
      // getAllSubtotal_format = getAllSubtotal_format.toFixed(2);
    }
    var finalVarience = (getAllSubtotal < 0 )?'<span>Amount exceeds the<br /> maximum invoice Amount.</span>':'<span>Amount <br />Remaining: '+ getAllSubtotal_format +'</span>';
  jQuery('.asset-cost-total-var').html(finalVarience);
    if(getAllSubtotal < 0) {
      jQuery(".custom-confirm-button").attr('disabled','disabled');  
    }    
    
  var grandTotal = 0;
    jQuery(".asset_percentage").each(function () {
      var getStval = jQuery(this).val();
      if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotal += isNaN(stval) ? 0 : stval; }
      else { grandTotal = 0; }
    });
    jQuery('.percentage-remain-count-varience').text(100 - grandTotal.toFixed(2) +'%');
    
  var granCurrentAsset = 0;
    jQuery(".get_current_asset_value").each(function () {   
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); granCurrentAsset += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { granCurrentAsset = 0; }
    });
    
    var granCurrentAsset_format = format(granCurrentAsset);
    if (granCurrentAsset_format == '$') {
      granCurrentAsset_format = '$0.00';
    }
    jQuery('.current_asset_val_total').text(format(granCurrentAsset_format));

    var granNewAsset = 0;
    var getCheckedtAssetType = jQuery(".asset-category-radio input[type='radio']:checked").val();
    if (getCheckedtAssetType == 'Split') {
      jQuery(".new_asset_value").each(function () {    
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
          granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
      else { granNewAsset = 0; }
    });
    }
    else if (getCheckedtAssetType == 'Spread') {
      jQuery(".new_asset_value_spread").each(function () {    
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
          granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
      else { granNewAsset = 0; }
      });
    }
    jQuery('.new_asset_val_total').text(format(granNewAsset));
  }); 
  jQuery('.asset_outside_consultants').keyup(function () {
    var getInvAmt = jQuery('.invoice_amount').val();
    var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');
    var getAssetCost = tblrow.find(".asset_cost").val();    
    var getAssetInst = tblrow.find(".asset_installation").val();
    var getAssetCons = tblrow.find(".asset_outside_consultants").val();
    var getAssetIntChange = tblrow.find(".asset_internal_charges").val();
    getAssetCost = (getAssetCost)?getAssetCost.replace(/[^\d\.\-]/g, ''):0;
    getAssetInst = (getAssetInst)?getAssetInst.replace(/[^\d\.\-]/g, ''):0;
    getAssetCons = (getAssetCons)?getAssetCons.replace(/[^\d\.\-]/g, ''):0;
    getAssetIntChange = (getAssetIntChange)?getAssetIntChange.replace(/[^\d\.\-]/g, ''):0;
    if (!getAssetCost) {
      getAssetCost = 0;
    }
    if (!getAssetInst) {
      getAssetInst = 0;
    }
    if (!getAssetCons) {
      getAssetCons = 0;
    }
    if (!getAssetIntChange) {
      getAssetIntChange = 0;
    }
    var subTotal = parseFloat(getAssetCost) + parseFloat(getAssetInst) + parseFloat(getAssetCons) + parseFloat(getAssetIntChange);
    var currentAssetVal = tblrow.find(".get_current_asset_value_hidden").val();
    if(currentAssetVal) {
      var currentAsstAmt = currentAssetVal.replace(/[^\d\.\-]/g, '');
      currentAsstAmt = parseFloat(currentAsstAmt) + parseFloat(subTotal);
      //tblrow.find(".get_current_asset_value").val(currentAsstAmt);
      tblrow.find(".new_asset_value").val(format(currentAsstAmt));
    }
    else {
    subTotal = (subTotal)?subTotal:0;
      tblrow.find(".new_asset_value").val(format(subTotal));
    }
    var calculatePer = (subTotal/invAmtFnl*100);      
     tblrow.find(".asset_percentage").val(calculatePer);
    // ================
    // Calculating subtotal   
    // Asset Cost Column Calculation
    var grandTotalCost = 0;
    jQuery(".asset_cost").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCost += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { grandTotalCost = 0; }
    });
    var grandTotalCost_format = format(grandTotalCost);
    if (grandTotalCost_format == '$') {
      grandTotalCost_format = '$0.00';
    }
    else {
      // grandTotalCost_format = grandTotalCost_format.toFixed(2);
    }
    jQuery('.asset_cost_total').text(grandTotalCost_format);
    // Asset Installation Column Calculation
    var grandTotalInst = 0;
    jQuery(".asset_installation").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInst += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { grandTotalInst = 0; }
        });
        var grandTotalInst_format = format(grandTotalInst);
        if (grandTotalInst_format == '$') {
          grandTotalInst_format = '$0.00';
        }
        else {
          // grandTotalInst_format = grandTotalInst_format.toFixed(2);
        }
        jQuery('.asset_installation_total').text(grandTotalInst_format);
    // Asset Consultants Column Calculation
    var grandTotalCons = 0;
    jQuery(".asset_outside_consultants").each(function () {
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCons += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { grandTotalCons = 0; }
        });        
    var grandTotalCons_format = format(grandTotalCons);
    if (grandTotalCons_format == '$') {
      grandTotalCons_format = '$0.00';
    }
    else {
      // grandTotalCons_format = grandTotalCons_format.toFixed(2);
    }
    jQuery('.asset_consultant_total').text(grandTotalCons_format);
    // Asset Internal charge Column Calculation
    var grandTotalInt = 0;
    jQuery(".asset_internal_charges").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInt += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { grandTotalInt = 0; }
        });
      var grandTotalInt_format = format(grandTotalInt);
      if (grandTotalInt_format == '$') {
        grandTotalInt_format = '$0.00';
      }
      jQuery('.asset_internal_charge_total').text(grandTotalInt_format);
    
    var grandTotalPer = 0;
      jQuery(".asset_percentage").each(function () {
    getStval = jQuery(this).val();
    if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotalPer += isNaN(stval) ? 0 : stval; }
    else { grandTotalPer = 0; }
      });
      jQuery('.percentage-remain-count').text(grandTotalPer.toFixed(2) +'%');
    // ===========================
    // Calculating Main Varience
    var getAllSubtotal = (invAmtFnl) -(grandTotalInt + grandTotalCons + grandTotalInst + grandTotalCost);
    var getAllSubtotal_format = format(getAllSubtotal);
    if (getAllSubtotal_format == '$') {
      getAllSubtotal_format = '$0.00';
    }
    else {
      // getAllSubtotal_format = getAllSubtotal_format.toFixed(2);
    }
    //var finalVarience = (getAllSubtotal < 0 )?'<span class="text-danger" title="Amount exceeded from split: '+ format(getAllSubtotal) +'">'+ format(getAllSubtotal) +'</span>':'<span class="text-success" title="Amount remaining to split: '+ format(getAllSubtotal) +'">'+ format(getAllSubtotal) +'</span>';
    var finalVarience = (getAllSubtotal < 0 )?'<span>Amount exceeds the<br> maximum invoice Amount.</span>':'<span>Amount <br>Remaining: '+ getAllSubtotal_format +'</span>';
    jQuery('.asset-cost-total-var').html(finalVarience);
    if(getAllSubtotal < 0) {
      jQuery(".custom-confirm-button").attr('disabled','disabled');  
    }
    var grandTotal = 0;
      jQuery(".asset_percentage").each(function () {
    var getStval = jQuery(this).val();
    if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotal += isNaN(stval) ? 0 : stval; }
    else { grandTotal = 0; }
      });
      jQuery('.percentage-remain-count-varience').text(100 - grandTotal.toFixed(2) +'%');
    var granCurrentAsset = 0;
    jQuery(".get_current_asset_value").each(function () {   
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); granCurrentAsset += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { granCurrentAsset = 0; }
        });
    var granCurrentAsset_format = format(granCurrentAsset);
    if (granCurrentAsset_format == '$') {
      granCurrentAsset_format = '$0.00';
    }
    jQuery('.current_asset_val_total').text(format(granCurrentAsset_format));
    var granNewAsset = 0;
    var getCheckedtAssetType = jQuery(".asset-category-radio input[type='radio']:checked").val();
    if (getCheckedtAssetType == 'Split') {
      jQuery(".new_asset_value").each(function () {    
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
        granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
        else { granNewAsset = 0; }

          });
    }
    else if (getCheckedtAssetType == 'Spread') {
      jQuery(".new_asset_value_spread").each(function () {    
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
        granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
        else { granNewAsset = 0; }

          });
    }
    jQuery('.new_asset_val_total').text(format(granNewAsset));
    // ================================
  });
    jQuery('.asset_internal_charges').keyup(function () {
        var getInvAmt = jQuery('.invoice_amount').val();
      var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');
      
    var getAssetCost = tblrow.find(".asset_cost").val();    
    var getAssetInst = tblrow.find(".asset_installation").val();
    var getAssetCons = tblrow.find(".asset_outside_consultants").val();
    var getAssetIntChange = tblrow.find(".asset_internal_charges").val();
    getAssetCost = (getAssetCost)?getAssetCost.replace(/[^\d\.\-]/g, ''):0;
    getAssetInst = (getAssetInst)?getAssetInst.replace(/[^\d\.\-]/g, ''):0;
    getAssetCons = (getAssetCons)?getAssetCons.replace(/[^\d\.\-]/g, ''):0;
    getAssetIntChange = (getAssetIntChange)?getAssetIntChange.replace(/[^\d\.\-]/g, ''):0;

    if (!getAssetCost) {
      getAssetCost = 0;
    }
    if (!getAssetInst) {
      getAssetInst = 0;
    }
    if (!getAssetCons) {
      getAssetCons = 0;
    }
    if (!getAssetIntChange) {
      getAssetIntChange = 0;
    }
    
    var subTotal = parseFloat(getAssetCost) + parseFloat(getAssetInst) + parseFloat(getAssetCons) + parseFloat(getAssetIntChange);
    
    var currentAssetVal = tblrow.find(".get_current_asset_value_hidden").val();
    if(currentAssetVal) {
      var currentAsstAmt = currentAssetVal.replace(/[^\d\.\-]/g, '');
      currentAsstAmt = parseFloat(currentAsstAmt) + parseFloat(subTotal);
      //tblrow.find(".get_current_asset_value").val(currentAsstAmt);
      tblrow.find(".new_asset_value").val(format(currentAsstAmt));
      }
    else {
      subTotal = (subTotal)?subTotal:0;
      tblrow.find(".new_asset_value").val(format(subTotal));
    }
      var calculatePer = (subTotal/invAmtFnl*100);      
        tblrow.find(".asset_percentage").val(calculatePer.toFixed(2));
    // ================
      // Calculating subtotal   
      // Asset Cost Column Calculation
    var grandTotalCost = 0;
        jQuery(".asset_cost").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCost += isNaN(stvalAmt) ? 0 : stvalAmt; }
      else { grandTotalCost = 0; }
        });
      var grandTotalCost_format = format(grandTotalCost);
      if (grandTotalCost_format == '$') {
        grandTotalCost_format = '$0.00';
      }
      else {
        // grandTotalCost_format = grandTotalCost_format.toFixed(2);
      }
      jQuery('.asset_cost_total').text(grandTotalCost_format);
    // Asset Installation Column Calculation
    var grandTotalInst = 0;
    jQuery(".asset_installation").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInst += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { grandTotalInst = 0; }
        });
        var grandTotalInst_format = format(grandTotalInst);
        if (grandTotalInst_format == '$') {
          grandTotalInst_format = '$0.00';
        }
        else {
          // grandTotalInst_format = grandTotalInst_format.toFixed(2);
        }
        jQuery('.asset_installation_total').text(grandTotalInst_format);
    // Asset Consultants Column Calculation
    var grandTotalCons = 0;
    jQuery(".asset_outside_consultants").each(function () {
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalCons += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { grandTotalCons = 0; }
        });        
    var grandTotalCons_format = format(grandTotalCons);
    if (grandTotalCons_format == '$') {
      grandTotalCons_format = '$0.00';
    }
    else {
      // grandTotalCons_format = grandTotalCons_format.toFixed(2);
    }
    jQuery('.asset_consultant_total').text(grandTotalCons_format);
    // Asset Internal charge Column Calculation
    var grandTotalInt = 0;
    jQuery(".asset_internal_charges").each(function () {    
      var getstvalAmt = jQuery(this).val();
      if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); grandTotalInt += isNaN(stvalAmt) ? 0 : stvalAmt; }
          else { grandTotalInt = 0; }
        });
      var grandTotalInt_format = format(grandTotalInt);
      if (grandTotalInt_format == '$') {
        grandTotalInt_format = '$0.00';
      }
      jQuery('.asset_internal_charge_total').text(grandTotalInt_format);
    
    var grandTotalPer = 0;
      jQuery(".asset_percentage").each(function () {
    getStval = jQuery(this).val();
    if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotalPer += isNaN(stval) ? 0 : stval; }
    else { grandTotalPer = 0; }
      });
      jQuery('.percentage-remain-count').text(grandTotalPer.toFixed(2) +'%');
    // ===========================
    // Calculating Main Varience
    var getAllSubtotal = (invAmtFnl) -(grandTotalInt + grandTotalCons + grandTotalInst + grandTotalCost);
    var getAllSubtotal_format = format(getAllSubtotal);
    if (getAllSubtotal_format == '$') {
      getAllSubtotal_format = '$0.00';
    }
    else {
      // getAllSubtotal_format = getAllSubtotal_format.toFixed(2);
    }
    //var finalVarience = (getAllSubtotal < 0 )?'<span class="text-danger" title="Amount exceeded from split: '+ format(getAllSubtotal) +'">'+ format(getAllSubtotal) +'</span>':'<span class="text-success" title="Amount remaining to split: '+ format(getAllSubtotal) +'">'+ format(getAllSubtotal) +'</span>';
    var finalVarience = (getAllSubtotal < 0 )?'<span>Amount exceeds the<br> maximum invoice Amount.</span>':'<span> Amount <br>Remaining: '+ getAllSubtotal_format +'</span>';
      jQuery('.asset-cost-total-var').html(finalVarience);
    if(getAllSubtotal < 0) {
      jQuery(".custom-confirm-button").attr('disabled','disabled');  
    }
    
    var grandTotal = 0;
      jQuery(".asset_percentage").each(function () {
    var getStval = jQuery(this).val();
    if(getStval) { var stval = parseFloat(getStval.replace(/[^\d\.\-]/g, '')); grandTotal += isNaN(stval) ? 0 : stval; }
    else { grandTotal = 0; }
      });
      jQuery('.percentage-remain-count-varience').text(100 - grandTotal.toFixed(2) +'%');
    var granCurrentAsset = 0;
    jQuery(".get_current_asset_value").each(function () {   
      var getstvalAmt = jQuery(this).val();
    if(getstvalAmt) { var stvalAmt = parseFloat(getstvalAmt.replace(/[^\d\.\-]/g, '')); granCurrentAsset += isNaN(stvalAmt) ? 0 : stvalAmt; }
        else { granCurrentAsset = 0; }
      });
    var granCurrentAsset_format = format(granCurrentAsset);
    if (granCurrentAsset_format == '$') {
      granCurrentAsset_format = '$0.00';
    }
    else {
      // granCurrentAsset_format = granCurrentAsset_format.toFixed(2);
    }
    jQuery('.current_asset_val_total').text(format(granCurrentAsset_format));
    var granNewAsset = 0;
    var getCheckedtAssetType = jQuery(".asset-category-radio input[type='radio']:checked").val();
    if (getCheckedtAssetType == 'Split') {
      jQuery(".new_asset_value").each(function () {    
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
        granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
        else { granNewAsset = 0; }

          });
    }
    else if (getCheckedtAssetType == 'Spread') {
      jQuery(".new_asset_value_spread").each(function () {    
        var getstvalAmtNew = jQuery(this).val();
        if(getstvalAmtNew) { 
          var stvalAmt = parseFloat(getstvalAmtNew.replace(/[^\d\.\-]/g, '')); 
        granNewAsset += isNaN(stvalAmt) ? 0 : stvalAmt; 
        }
        else { granNewAsset = 0; }

          });
    }
    var granNewAsset_format = format(granNewAsset);
    if (granNewAsset_format == '$') {
      granNewAsset_format = '$0.00';
    }
    else {
      // granNewAsset_format = granNewAsset_format.toFixed(2);
    }
    jQuery('.new_asset_val_total').text(granNewAsset_format);
    // ================================
  });
    });
  // Apply remove functionatly for split and spread  
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_value==="remove_asset") {
      jQuery.blockUI({
        baseZ: 2000,
        message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait...</strong></div>',
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
  }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_value==="remove_asset") {
      var tblrows = jQuery(".project-assetes-main-table tbody tr");

      var is_split = false;
      var is_spread = false;
      var is_blank = false;
      var getMainAsset = '';

      tblrows.each(function (index) {
        var tblrow = jQuery(this);
        var getCategory = tblrow.find(".asset_category_all_split").val();
        var getCategorySpread = tblrow.find(".asset_category_all_spread").val();
        if(getCategory) {
          is_split = true;
          is_blank = false;
          tblrow.find(".asset_description option").each(function () {
            var getVal = jQuery(this).val();
            var getCat = getVal.split('-');
            if (getCat[1] == getCategory) {
              jQuery(this).show();
              tblrow.find(".asset_description").removeAttr('disabled');
            }
            else {
              jQuery(this).hide();
              jQuery(this).attr('disabled', 'disabled');
            }
          });
          if (context == document) {
            tblrow.find(".asset_description").trigger('change');
          }
        }
        else if(getCategorySpread) {
          is_spread = true;
          is_blank = false;
          tblrow.find(".asset_description option").each(function () {
            var getVal = jQuery(this).val();
            var getCat = getVal.split('-');
            if (getCat[1] == getCategorySpread) {
              jQuery(this).show();
              tblrow.find(".asset_description").removeAttr('disabled');
            }
            else {
              jQuery(this).hide();
              jQuery(this).attr('disabled', 'disabled');
            }
          });
        }
        else {
          tblrow.find(".asset_description").attr('disabled','disabled');
          is_blank = true;
        }
      });

      if (is_blank) {
        // Hiding asset success button and show add to asset button.
        if (!is_split && !is_spread) {
          jQuery('.custom-add-asset-button-success').hide();
          jQuery('.custom-add-asset-button').show();
        }

        getMainAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
        if (getMainAsset == 'Split') {
          is_split = true;
        }
        if (getMainAsset == 'Spread') {
          is_spread = true;
        }
      }

      if (is_split) {
        // If the spending is split, then showing split forms.
        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        jQuery('.asset-category-header-split').show();
        jQuery('.asset-category-header-spread').hide();
        jQuery('#adding-new-assets-amount').show();
        jQuery('.main-asset-custom-btn').show();
      }

      if (is_spread) {
        // If the spending is spread, then showing spread forms.
        if (context == document) {
          change_spending_auto_spread();
        }
        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        jQuery('.spread-options-custom').show();
        jQuery('.asset-category-header-split').hide();
        jQuery('.asset-category-header-spread').show();
        jQuery('#adding-new-assets-amount').show();
        jQuery('.main-asset-custom-btn').show();
      }

      //jQuery.unblockUI(); //Unblocking UI.
    }

    if (urlajax.indexOf("/get-next-page-data") === 0) {
      var getPagerId = jQuery('.datatable_page_id').val();
      if(getPagerId) {
        if (jQuery('.page_number_id').val() != 'drop') {
          jQuery('.item-list ul li a').each(function(index, element) {
            jQuery(this).css('background-color','#fff');
            jQuery(this).css('pointer-events','auto');
          });
          jQuery('.page-range-'+getPagerId).css('background-color','#eee');
          jQuery('.page-range-'+getPagerId).css('pointer-events','none'); 
        }
        jQuery("html, body").animate({ scrollTop: "0px" });  
      }
    }
  });

  // Applying form reset after clear all work completed
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/clear-asset-data/") === 0){ }
  if (urlajax.indexOf("/get-total-number-of-data/") === 0 || urlajax.indexOf("/get-asset-based-data/") === 0){ 
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
  }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/clear-asset-data/") === 0){ 
    //jQuery('.project-program-sel-spending').trigger('change');
    }
  if (urlajax.indexOf("/get-total-number-of-data/") === 0 || urlajax.indexOf("/get-asset-based-data/") === 0){ 
    //jQuery.unblockUI();
    }
  
  if (urlajax.indexOf("/get-next-page-data/") === 0){ 
    var rowcount = jQuery('.dataTables_wrapper').length;
      var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
      if(rowcount == 0 && rowCountTable > 2) {
        jQuery('table.m6connect-custom-program-table').DataTable({
        //"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
        "bPaginate": false,
    "paging": false,
        "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
        "searching": false,
         //"dom": 'Rfrtlip',
        });
      }
    } 
  });
  // Apply calculation after add new button work completed
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="workflow_add_new_row"){
      //
    }
  }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="workflow_add_new_row") {
      var tblrows = jQuery(".project-assetes-main-table tbody tr");

      var is_split = false;
      var is_spread = false;

      tblrows.each(function (index) {
        var tblrow = jQuery(this);
        var getCategory = tblrow.find(".asset_category_all_split").val();
        var getCategorySpread = tblrow.find(".asset_category_all_spread").val();

        if (getCategory) {
          is_split = true;
          tblrow.find(".asset_description option").each(function () {
          var getVal = jQuery(this).val();
          var getCat = getVal.split('-');
          if (getCat[1] == getCategory) {
            jQuery(this).show();
            tblrow.find(".asset_description").removeAttr('disabled');
          }
          else {
            jQuery(this).hide();
            jQuery(this).attr('disabled', 'disabled');
          }
          });

          if (context == document) {
            tblrow.find(".asset_description").trigger('change');
          }
        }
        else if (getCategorySpread) {
          is_spread = true;
          tblrow.find(".asset_description option").each(function () {
            var getVal = jQuery(this).val();
            var getCat = getVal.split('-');

            if (getCat[1] == getCategorySpread) {
              jQuery(this).show();
              tblrow.find(".asset_description").removeAttr('disabled');             
            }
            else {
              jQuery(this).hide();
              jQuery(this).attr('disabled', 'disabled');
            }
          });
        }
        else {
          // tblrow.find(".asset_description").attr('disabled','disabled');  
          tblrow.find(".asset_description").attr('disabled','disabled');  
        }
      });

      if (is_split) {
        // If the spending is split, then showing split forms.
        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        jQuery('.asset-category-header-split').show();
        jQuery('.asset-category-header-spread').hide();
        jQuery('#adding-new-assets-amount').show();
        jQuery('.main-asset-custom-btn').show();
      }

      if (is_spread) {
        // If the spending is spread, then showing spread forms.
        if (context == document) {
          change_spending_auto_spread();
        }

        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        jQuery('.spread-options-custom').show();
        jQuery('.asset-category-header-split').hide();
        jQuery('.asset-category-header-spread').show();
        jQuery('#adding-new-assets-amount').show();
        jQuery('.main-asset-custom-btn').show();
      }
    }
  });

  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get-spending"){
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
  }).ajaxComplete(function(event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;  
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get-spending") {
  // Hiding new asset values.
    jQuery('.new-asset-value-header').hide();
    jQuery('.new-asset-value-row-split').addClass('hidden');
    jQuery('.new-asset-value-row-spread').addClass('hidden');
    jQuery('.new_asset_val_total').hide();
  //jQuery.unblockUI();
  if(jQuery('.invoice-number-filter select').val()) {
    jQuery('.invoice-number-filter select').trigger('change');
    }
  if(jQuery('.cost-code-name-filter select').val()) {
      jQuery('.cost-code-name-filter select').trigger('change');
  }
  if(jQuery('.commitment-type-filter select').val()) {
      jQuery('.commitment-type-filter select').trigger('change');
    }
  if(jQuery('.vendor-name-filter select').val()) {
      jQuery('.vendor-name-filter select').trigger('change');
    }
  var rowcount = jQuery('.dataTables_wrapper').length;
    var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
    if(rowcount == 0 && rowCountTable > 2) {
      jQuery('table.m6connect-custom-program-table').DataTable({
      "bPaginate": false,
        "paging": false,
        "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
        "searching": false,
         //"dom": 'Rfrtlip',
      });
    }
  var getPagerId = jQuery('.datatable_page_id').val();
    if(getPagerId) {
      if(jQuery('.page_number_id').val() != 'drop') { 
        jQuery('.page-range-'+getPagerId).trigger('click');
        jQuery('.page-range-'+getPagerId).css('background-color','#eee');
        jQuery('.page-range-'+getPagerId).css('pointer-events','none');
      }
    else {
        jQuery('.pager-load-more-to').val(getPagerId).trigger('change');
      }
    }
    if (jQuery('#split-edit-value').text() == 'Split') {
      // If this element has type split than this means we are dealing with
      // editing the split asset.
      // Hiding the add asset button and showing the success button.
      jQuery('.custom-add-asset-button-success').show();
      jQuery('.custom-add-asset-button').hide();
    jQuery('#edit-asset-category').find('input[type="radio"][value="Split"]').attr('checked', 'checked');
    jQuery('#main-class-assets').show();
    jQuery('.asset-category-header-split').show();
    jQuery('.asset-category-header-spread').hide();
    jQuery('#adding-new-assets-amount').show();
    jQuery('.main-asset-custom-btn').show();
    if (context == document && !jQuery('#split-edit-value').hasClass('processed')) {
        jQuery('.asset_description').trigger('change'); // To get current asset values.
        jQuery('#split-edit-value').addClass('processed');
      }
    jQuery('.asset_cost').trigger('keyup');
      jQuery('.asset_installation').trigger('keyup');
      jQuery('.asset_outside_consultants').trigger('keyup');
      jQuery('.asset_internal_charges').trigger('keyup');
    }
  if (jQuery('#split-edit-value').text() == 'Spread') {
      // If this element has type Spread than we are dealing with Spread asset,
      // with Spread option as No.
      jQuery('.custom-add-asset-button-success').show();
        jQuery('.custom-add-asset-button').hide();

        jQuery('#edit-asset-category').find('input[type="radio"][value="Spread"]').attr('checked', 'checked');
        jQuery('#edit-spread-options').find('input[type="radio"][value="No"]').attr('checked', 'checked');
        jQuery('#main-class-assets').show();
        jQuery('.asset-category-header-split').hide();
        jQuery('.asset-category-header-spread').show();
        jQuery('#adding-new-assets-amount').show();
        jQuery('.main-asset-custom-btn').show();
        jQuery('.respread-button-custom').show();

        if (context == document) {
          jQuery('.asset_description').trigger('change'); // To get current asset values.
        }
      }
      if (jQuery('#split-edit-value').text() == 'Spread_YES') {
        // This is the case when a spread node is being edited with spread option
        // set to yes.
        jQuery('.custom-add-asset-button-success').show();
        jQuery('.custom-add-asset-button').hide();
        jQuery('#edit-asset-category').find('input[type="radio"][value="Spread"]').attr('checked', 'checked');
        // jQuery('#edit-spread-options').find('input[type="radio"][value="Yes"]').attr('checked', 'checked');
        jQuery('#edit-spread-options').find('input[type="radio"][value="Yes"]').trigger('click');
        jQuery('.custom-add-asset-button-success').trigger('click');
        jQuery('#custom-form-inline-radio').hide();
        jQuery('.spread-options-custom').hide();
        jQuery('.respread-button-custom').hide();
      }
  }
  });
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="spread_options") {
      var getCheckedtAsset = jQuery(".spread-category-radio input[type='radio']:checked").val();
      if(getCheckedtAsset == 'Yes') {
        jQuery('.asset-loader2').show();
        jQuery('#main-class-assets').hide();
      }
    }
  }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="spread_options") {
      var getCheckedtAsset = jQuery(".spread-category-radio input[type='radio']:checked").val();
      if(getCheckedtAsset == 'Yes') {
        jQuery('.asset-loader2').hide();
        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        if(context == document) {
          change_spending_auto_spread();
          var getInvAmt = jQuery('.invoice_amount').val();
          var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');
          jQuery('.asset_node_nid').val(invAmtFnl);
        }
        jQuery('.main-asset-custom-btn').show();
      }
      var getMainAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
      if(getMainAsset == 'Spread') {
        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        jQuery('.spread-options-custom').show();
        jQuery('.asset-category-header-split').hide();
        jQuery('.asset-category-header-spread').show();
        jQuery('.main-asset-custom-btn').show();
        jQuery('.asset-cost-total-var').hide();
      }
      if(getMainAsset == 'Split') {
        jQuery('.asset-cost-total-var').show();
        jQuery('.main-aset-container').show();
        jQuery('#main-class-assets').show();
        jQuery('.asset-category-header-split').show();
        jQuery('.asset-category-header-spread').hide(); 
        jQuery('.main-asset-custom-btn').show();
      }

      // Hiding new asset value for now.
      var getNidEdeit = jQuery('.project_spending_nid').val();
      if (getNidEdeit) {
        jQuery('.new-asset-value-header').hide();
        jQuery('.new-asset-value-row-split').addClass('hidden');
        jQuery('.new-asset-value-row-spread').addClass('hidden');
        jQuery('.new_asset_val_total').hide();
        jQuery('.respread-button-custom').show();
      }
    }
  });
  
  jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-assets") {
      // var getVal = jQuery('.asset_description').val();
      var tblrows = jQuery(".project-assetes-main-table tbody tr");
      tblrows.each(function (index) {
        var tblrow = jQuery(this);
        var getCategory = tblrow.find(".asset_category_all_split").val();
        var getCategorySpread = tblrow.find(".asset_category_all_spread").val();
        
        if (getCategory) {
          tblrow.find(".asset_description option").each(function () {
            var getVal = jQuery(this).val();
            var getCat = getVal.split('-');
          
            if(getCat[1] == getCategory) {
              jQuery(this).show();
            tblrow.find(".asset_description").removeAttr('disabled');
            }
            else {
              jQuery(this).hide();
              jQuery(this).attr('disabled', 'disabled');
            }
          });
          jQuery('.main-aset-container').show();
          jQuery('#main-class-assets').show();
          jQuery('.asset-category-header-split').show();
          jQuery('.asset-category-header-spread').hide();
          jQuery('#adding-new-assets-amount').show();
          jQuery('.main-asset-custom-btn').show();

          if (context == document) {
            tblrow.find(".asset_description").trigger('change');
          }
        }
        else if(getCategorySpread) {
          tblrow.find(".asset_description option").each(function () {
            var getVal = jQuery(this).val();
            var getCat = getVal.split('-');
            if(getCat[1] == getCategorySpread) {
              jQuery(this).show();
              tblrow.find(".asset_description").removeAttr('disabled');             
            }
            else {
              jQuery(this).hide();
              jQuery(this).attr('disabled', 'disabled');
            }
          });
          tblrow.find(".asset_description").each(function () {
            var getVal = jQuery(this).val();
            if(getVal) {
              var getSpread = tblrow.find(".spread_amount").val();
              if(getSpread) {
                if (context == document) {
                  jQuery(this).trigger('change');
                }
              }
            }
          });
          jQuery('.main-aset-container').show();
          jQuery('#main-class-assets').show();
          jQuery('.spread-options-custom').show();
          jQuery('.asset-category-header-split').hide();
          jQuery('.asset-category-header-spread').show();
          jQuery('#adding-new-assets-amount').show(); 
          jQuery('.main-asset-custom-btn').show();    
        }
        else {
          tblrow.find(".asset_description").attr('disabled','disabled');  
        }
      });
    }
  });
  // Apply calculation after completing ajax for get current asset val
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/get-current-asset") === 0){  }
      }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
          var urlajax = ajaxOptions.url;
          if (urlajax.indexOf("/get-current-asset") === 0){
        var tblrows = jQuery(".project-assetes-main-table tbody tr");       
          tblrows.each(function (index) {  
            var tblrow = jQuery(this);
        var getCheckedtAsset = jQuery(".asset-category-radio input[type='radio']:checked").val();
        if(getCheckedtAsset == 'Split') {
          if(tblrow.find('.asset_description').val()) {
          jQuery(this).trigger('change');
          var grandCurrent = 0;
              jQuery(".get_current_asset_value").each(function () {
              var getVal = jQuery(this).val();  
                    var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
                  grandCurrent += isNaN(stval) ? 0 : stval;
                });
          var granCurrentAsset_format = format(grandCurrent);
          if (granCurrentAsset_format == '$') {
            granCurrentAsset_format = '$0.00';
          }
          jQuery('.current_asset_val_total').text(format(granCurrentAsset_format));
          var grandNewAsset = 0;
              jQuery(".new_asset_value").each(function () {
              var getVal = jQuery(this).val();  
                    var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
                  grandNewAsset += isNaN(stval) ? 0 : stval;
                });
          var granNewAsset_format = format(grandNewAsset);
          if (granNewAsset_format == '$') {
            granNewAsset_format = '$0.00';
          }
          else {
            // granNewAsset_format = granNewAsset_format.toFixed(2);
          }
          jQuery('.new_asset_val_total').text(granNewAsset_format);
        }
        }
        jQuery(".spread_amount").each(function () {
          var getInvAmt = jQuery('.invoice_amount').val();
              var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');  
          var getCurrentAssetVal = tblrow.find('.get_current_asset_value').val();
          if(getCurrentAssetVal) {
            getCurrentAssetVal = getCurrentAssetVal.replace(/[^\d\.\-]/g, '');    
          }
          else {
            getCurrentAssetVal = 0.00;
          }
          var getToatalCurrentAsset = jQuery('.current_asset_val_total').text();
          if(getToatalCurrentAsset) { 
            getToatalCurrentAsset = parseFloat(getToatalCurrentAsset.replace(/[^\d\.\-]/g, '')); 
          }
          else {
            getToatalCurrentAsset = 0.00;
          }
          var newSpreadAmt = (getCurrentAssetVal/getToatalCurrentAsset)*invAmtFnl;
          if (!newSpreadAmt) { newSpreadAmt = 0; }
          tblrow.find('.spread_amount').val(format(newSpreadAmt));
          jQuery('.total_current_asset_val').val(getToatalCurrentAsset);
          var newSpreadAmt = parseFloat(getCurrentAssetVal) + parseFloat(newSpreadAmt);
          if(!newSpreadAmt){ newSpreadAmt = 0; } 
            tblrow.find('.new_asset_value_spread').val(format(newSpreadAmt));
          });       
        });
        }
        });  
   
   
  // =============================================   POPUP END FOR SPLIT AND SPREAD ========================= //  
     jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
        var urlajax = ajaxOptions.url;
        if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-spending"){
    jQuery.blockUI({
      //theme:     true,
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
   }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
          var urlajax = ajaxOptions.url;
          if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-spending"){            
            //jQuery.unblockUI();
            if(jQuery('.invoice-number-filter select').val()) {
        jQuery('.invoice-number-filter select').trigger('change');
      }
      if(jQuery('.cost-code-name-filter select').val()) {
              jQuery('.cost-code-name-filter select').trigger('change');        
      }
      if(jQuery('.commitment-type-filter select').val()) {
            jQuery('.commitment-type-filter select').trigger('change');
      }
      if(jQuery('.vendor-name-filter select').val()) {
            jQuery('.vendor-name-filter select').trigger('change');       
      }
            var rowcount = jQuery('.dataTables_wrapper').length;
          var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
          if(rowcount == 0 && rowCountTable > 2) {
            jQuery('table.m6connect-custom-program-table').DataTable({
              //"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
              "bPaginate": false,
          "paging": false,
                "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
              "searching": false,
        });
          }
      }
        });
  // =============================================   POPUP END FOR SPLIT AND SPREAD ========================= //  
  jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name==="select-invoice-number" || ajaxOptions.extraData._triggering_element_name==="select-cost-code" || ajaxOptions.extraData._triggering_element_name==="select-commitment-type" || ajaxOptions.extraData._triggering_element_name==="select-company-name")){
          var rowcount = jQuery('.dataTables_wrapper').length;
      var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
          if(rowcount == 0 && rowCountTable > 2) {
            jQuery('table.m6connect-custom-program-table').DataTable({
            //"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
            "bPaginate": false,
      "paging": false,
            "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
            "searching": false,
             ////"dom": 'Rfrtlip',
            });
          }
      var getPagerId = jQuery('.datatable_page_id').val();
        if(getPagerId) {
          if(jQuery('.page_number_id').val() != 'drop') { 
        jQuery('.page-range-'+getPagerId).trigger('click');
          jQuery('.page-range-'+getPagerId).css('background-color','#eee');
          jQuery('.page-range-'+getPagerId).css('pointer-events','none');
      }
      else {
          jQuery('.pager-load-more-to').val(getPagerId).trigger('change');
        }
        }
      
      if(jQuery('.invoice-number-filter select').val()) {
        jQuery('.invoice-number-filter').attr('data','showCus');
      //jQuery('.invoice-number-filter').show();
      jQuery('body').find('.invoice-number-filter-def').show();
      }
      if(jQuery('.cost-code-name-filter select').val()) {
        jQuery('.cost-code-name-filter').attr('data','showCus');
      //jQuery('.cost-code-name-filter').show();
      jQuery('body').find('.cost-code-name-filter-def').show();
      }
      if(jQuery('.commitment-type-filter select').val()) {
        jQuery('.commitment-type-filter').attr('data','showCus');
      //jQuery('.commitment-type-filter').show();
      jQuery('body').find('.commitment-type-filter-def').show();
      }
      if(jQuery('.vendor-name-filter select').val()) {
        jQuery('.vendor-name-filter').attr('data','showCus');
      //jQuery('.vendor-name-filter').show();
      jQuery('body').find('.vendor-name-filter-def').show();
      }
    }
    if (urlajax.indexOf("/reseting/spending/ajax") === 0) {
      var rowcount = jQuery('.dataTables_wrapper').length;
      var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
        if(rowcount == 0 && rowCountTable > 2) {
        jQuery('table.m6connect-custom-program-table').DataTable({
        //"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
        "bPaginate": false,
    "paging": false,
        "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
        "searching": false,
        //"dom": 'Rfrtlip',
          });
      }
      var getPagerId = jQuery('.datatable_page_id').val();
    if(getPagerId) {
      if(jQuery('.page_number_id').val() != 'drop') { 
      jQuery('.page-range-'+getPagerId).trigger('click');
      jQuery('.page-range-'+getPagerId).css('background-color','#eee');
      jQuery('.page-range-'+getPagerId).css('pointer-events','none');
      }
    else {
      jQuery('.pager-load-more-to').val(getPagerId).trigger('change');
    }
    }
  }
  });

  // Clearing the split table.
  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="reset_split_table_trigger") {
      // Blocking UI.
      jQuery.blockUI({
        //theme:     true,
        baseZ: 2000,
        message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait...</strong></div>',
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
  }).ajaxComplete(function(event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="reset_split_table_trigger") {
      //jQuery.unblockUI(); //Unblocking UI.
      jQuery('.main-aset-container').show();
      jQuery('#main-class-assets').show();
      jQuery('.asset-category-header-split').show();
      jQuery('.asset-category-header-spread').hide();
      jQuery('.spread-options-custom').hide();
      jQuery('#adding-new-assets-amount').show();
      jQuery('.asset-cost-total-var').show();
      jQuery('#asset-form-title-custom').show();
      jQuery('#asset-form-title-custom strong').text('Add to Asset(s) - Split - this allows the user to self define the applicable invoice amounts to the respective assets.');
      jQuery('.main-asset-custom-btn').show();  
      jQuery('.get-total-section').hide();
      jQuery('input:radio[name=asset_category_sub][value=Split]').attr('checked', true);
    }
  });
  jQuery(document).ajaxStop(function () {
    setTimeout(function() {
      jQuery.unblockUI();
    }, 2000);
    
    }); 
  
}};



// --------------------------------- End Drupal Behaviours -------------------------






// -------------------------------- Start JQuery ready -----------------------------

jQuery(document).ready(function(e) {
  jQuery('.respread-button-custom').hide();
  jQuery('.project-program-spending-sel').trigger('change');
  var ProId = jQuery('.project-program-spending-sel').val();
  // Ajax request for get the list of commitment by project
  jQuery.post( '/get-commitment-list-project/'+ProId, function( data ) {
    jQuery('.invoice_commitment').empty();  
    jQuery(".invoice_commitment").prepend("<option value=''>Select Commitment</option>").val('');
    jQuery.each(data,function(key, value) { 
    var opt = jQuery('<option>');
      opt.val(key).text(value);
      opt.appendTo('.invoice_commitment');  
    });
  })    
  // Ajax request for get the list of cost code by project
  jQuery.post( '/get-cost-code/'+ProId, function( data ) {
    jQuery('.invoice_cost_code').empty();
    jQuery.each(data,function(key, value) {
      var opt = jQuery('<option>');
      opt.val(key).text(value);
      opt.appendTo('.invoice_cost_code'); 
    });
    jQuery(".invoice_cost_code").prepend("<option value='0' selected='selected'>- None -</option>");
   })  
  // Get vendor by Commitment
  jQuery('.invoice_commitment').change(function () { 
       var commitmentId = jQuery(this).val();
       if(commitmentId) {
         jQuery.post( '/get-vendor-by-commitment/'+commitmentId, function( data ) {
           jQuery.each(data,function(key, value) {
             jQuery('.invoice_vendor').val(value);
             jQuery('.company_nid').val(key);
           });           
         });  
       }
       else {
         jQuery('.invoice_vendor').val('');
         jQuery('.company_nid').val('');
       }
       // Comparing commitment amount and invoice    
       var getCommitmentAmount = jQuery('.invoice_amount').val();
       if(getCommitmentAmount) {
         var ProNumber = jQuery('.project-program-spending-sel').val();
         jQuery.post( '/check-commitment-amount/'+ getCommitmentAmount +'/'+commitmentId, function( data ) { 
           if(data.access == 0) {
             //jQuery('.project-avail-status-amt .text-danger').text(data.message);
            //jQuery('.invoice_amount').addClass('error')
            //jQuery('.project-avail-status-amt .text-success').text('');
            //jQuery('.custom-submit-spending input').attr('disabled','disabled');
          }
          if(data.access == 1) {
            //jQuery('.project-avail-status-amt .text-danger').text('');  
            //jQuery('.invoice_amount').removeClass('error')
            //jQuery('.project-avail-status .text-success').text(data.message);
            //jQuery('.project-avail-status-amt .text-success').text('');
            //jQuery('.custom-submit-spending input').removeAttr('disabled');
          }     
        });
      } 
     
   });
  
  jQuery('.project-program-spending-sel').change(function () {
    var ProId = jQuery(this).val();    
    var queryProject = getUrlParameter('pid');
    if(queryProject) { 
      if(queryProject != ProId) {
        window.location.href="/program/spending";
      }
    }       
    // Ajax request for get the list of cost code by project
    jQuery.post( '/get-cost-code/'+ProId, function( data ) {
      jQuery('.invoice_cost_code').empty(); 
      jQuery.each(data,function(key, value) { 
      var opt = jQuery('<option>');
        opt.val(key).text(value);
        opt.appendTo('.invoice_cost_code'); 
    });
    jQuery(".invoice_cost_code").prepend("<option value='0' selected='selected'>- None -</option>");
    })
    // Ajax request for get the list of commitment by project
    jQuery.post( '/get-commitment-list-project/'+ProId, function( data ) {
      jQuery('.invoice_commitment').empty();  
    jQuery(".invoice_commitment").prepend("<option value=''>Select Commitment</option>").val('');
      jQuery.each(data,function(key, value) {
      var opt = jQuery('<option>');
        opt.val(key).text(value);
        opt.appendTo('.invoice_commitment');
    });
    })   
  });
  
  jQuery('.invoice_commitment').change(function(e) {
     var getCommitId = jQuery(this).val();
     var getPreviousCC = jQuery('.invoice_cost_code').val();
     if(getCommitId) {
       jQuery.post( '/get-cost-code/'+getCommitId, function( data ) {
       if(data != 0) { 
         jQuery.each(data,function(key, value) {         
         jQuery('.invoice_cost_code').empty();  
         jQuery(".invoice_cost_code").prepend("<option value='0'>Select Cost Code</option>").val('');
         jQuery.each(data,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.invoice_cost_code');
         });
         if(getPreviousCC != '0') {
             jQuery(".invoice_cost_code").val(getPreviousCC);
           }
        });
       }
       else {
         var ProId = jQuery('.project-program-spending-sel').val();
         // Ajax request for get the list of cost code by project
           jQuery.post( '/get-cost-code/'+ProId, function( data ) {
           jQuery('.invoice_cost_code').empty();  
           jQuery.each(data,function(key, value) {  
             var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.invoice_cost_code');  
         });
       jQuery(".invoice_cost_code").prepend("<option value='0' selected='selected'>Select Cost Code</option>");
          });
       }
      })
    }
    else {      
      var ProId = jQuery('.project-program-spending-sel').val();
      // Ajax request for get the list of cost code by project
      jQuery.post( '/get-cost-code/'+ProId, function( data ) {
      jQuery('.invoice_cost_code').empty(); 
      jQuery.each(data,function(key, value) { 
      var opt = jQuery('<option>');
        opt.val(key).text(value);
        opt.appendTo('.invoice_cost_code'); 
    });
    jQuery(".invoice_cost_code").prepend("<option value='0' selected='selected'>Select Cost Code</option>");
      });      
    }
    jQuery('.invoice_cost_code').change(function() {
      var getCC = jQuery(this).val();
      jQuery('.invoice_cost_code_value').val(getCC);
    });
    // Comparing commitment amount and invoice     
      var getCommitmentAmount = jQuery('.invoice_amount').val();
    if(getCommitmentAmount) {
      var ProNumber = jQuery('.project-program-spending-sel').val();
      jQuery.post( '/check-commitment-amount/'+ getCommitmentAmount +'/'+getCommitId, function( data ) { 
        if(data.access == 0) {
          //jQuery('.project-avail-status-amt .text-danger').text(data.message);
        //jQuery('.invoice_amount').addClass('error')
        //jQuery('.project-avail-status-amt .text-success').text('');
        //jQuery('.custom-submit-spending input').attr('disabled','disabled');
        }
        if(data.access == 1) {
        //jQuery('.project-avail-status-amt .text-danger').text('');  
        //jQuery('.invoice_amount').removeClass('error')
          //jQuery('.project-avail-status .text-success').text(data.message);
        //jQuery('.project-avail-status-amt .text-success').text('');
        //jQuery('.custom-submit-spending input').removeAttr('disabled');
        }     
      });
    }
  });
  
  var ProId = jQuery('.project-program-spending-sel').val();
  jQuery('.new-record-cus-btn').attr('for', ProId);     
  jQuery('.new-spending-link').click(function (e) {     
    e.preventDefault();
    var status = jQuery('.project_spending_main_cust').attr('for');
    var dataAttr = jQuery('.project_spending_main_cust').attr('data');
    jQuery('.custom-add-asset-button-success').hide();
    jQuery('.custom-add-asset-button').show();
  // ---------------------------------------------------------
  // Checking if conatiner already open and form in edit state
  // then 
    if(status == 'open' && jQuery('.project_spending_main_cust').attr('data') == 'edit') {   
      jQuery('.project_spending_main_cust').removeAttr('data'); 
      var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
      jQuery('.project-program-spending-sel').trigger('change');    
      jQuery('#project_spending_main_container').show();
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.rigth-side-form-field').show();
      jQuery('.custom-submit-reset').show();
      jQuery('.custom-submit-safety').show();   
    }
  // Checking if conatiner already Closed but the form in edit state
    else if(status == 'closed' && jQuery('.project_spending_main_cust').attr('data') == 'edit') {  
      jQuery('.project_spending_main_cust').removeAttr('data'); 
      var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
      jQuery('.project-program-spending-sel').trigger('change');    
      jQuery('#project_spending_main_container').show();
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.rigth-side-form-field').show();
      jQuery('.custom-submit-reset').show();
      jQuery('.custom-submit-safety').show();
    }   
    else if(status == 'open' && jQuery('.project_spending_main_cust').attr('data2') == 'querystring') {
      var pid = getUrlParameter('pid');     
      window.location.href="/program/spending?pid="+pid;    
    } 
    else if(status == 'closed') {
      jQuery('.project_spending_main_cust').attr('for','open'); 
      jQuery('.project_spending_main_cust').show();
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.custom-submit-reset').show();
      jQuery('.custom-submit-safety').show();   
      jQuery('.rigth-side-form-field').show();
    }
    else if(status == 'open') {
      jQuery('#project_spending_main_container').hide();
      jQuery('.project_spending_main_cust').attr('for','closed'); 
      jQuery('.custom-submit-spending').hide();
      jQuery('.upload_attachment_container').hide();
      jQuery('.custom-submit-reset').hide();
      jQuery('.rigth-side-form-field').hide();       
    }
    else if(status == 'open' && jQuery('.project_spending_main_cust').attr('data') == 'edit') { 
      jQuery('.project_spending_main_cust').removeAttr('data'); 
      var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
      jQuery('.project-program-sel-spending').val('').trigger('change');    
      jQuery('#project_spending_main_container').show();
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.custom-submit-reset').show();
      jQuery('.custom-submit-safety').show();   
      jQuery('.rigth-side-form-field').show();    
    }
    else if(jQuery( ".project_spending_main_cust" ).attr('data') == 'edit') {
      var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
      //jQuery('.project-program-spending-sel').val(getScheduleProId).trigger('change');
      jQuery('.project-program-sel-spending').val('').trigger('change');    
      jQuery('#project_spending_main_container').show();
      jQuery('.project_spending_main_cust').attr('for','open'); 
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.custom-submit-reset').show();
      jQuery('.custom-submit-safety').show();   
      jQuery('.rigth-side-form-field').show();
      }
    });
    var pid = getUrlParameter('pid');
    if(pid) { 
      jQuery('.project-program-spending-sel').val(pid).trigger('change');
      jQuery('.project_spending_main_cust').attr('for','open'); 
      jQuery('.project_spending_main_cust').show();
      jQuery('.custom-submit-spending').show();
      jQuery('.upload_attachment_container').show();
      jQuery('.custom-submit-reset').show();
      jQuery('.custom-submit-safety').show();   
      jQuery('.rigth-side-form-field').show();
    }
    else {
      jQuery('.project_spending_main_cust').hide();   
      jQuery('.custom-submit-spending').hide();
      jQuery('.upload_attachment_container').hide();
      jQuery('.custom-submit-reset').hide();
      jQuery('.rigth-side-form-field').hide();
      jQuery('.project_spending_main_cust').attr('for','closed');
    }
  jQuery('#clear-split-spread').dialog({
      autoOpen: false,
      width: 490,
      modal: true,
      resizable: false,
      buttons: {
      'Confirm': function () {      
      jQuery(this).dialog("close");
          jQuery('.main-clear-all-button').trigger('click'); 
      },
      'No': function () {       
      jQuery(this).dialog("close");
        }
      },
    open: function () {
        jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
        jQuery('.ui-dialog-titlebar').hide();
      }
    });
    jQuery('#nothingin-amt-field-dialog').dialog({
      autoOpen: false,
      width: 490,
      modal: true,
      resizable: false,
      buttons: {
        'Ok': function () {
          jQuery(this).dialog("close");         
        },        
      },
      open: function () {
        jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
        jQuery('.ui-dialog-titlebar').hide();
      }
    });
  });
  
// Common functions goes here
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
  return false;
};

// Function for pdf loading image on report page
function hideProgress(){
  jQuery(".report-loader2").hide();   
}

function isEmpty(td) {
  if (td.text == '' || td.text() == ' ' || td.html() == '&nbsp;' || td.is(":not(:visible)")) {
    return true;
  }
  return false;
}

jQuery(window).scroll(function(e){ 
  var el = jQuery('.fixedElement'); 
  var isPositionFixed = (el.css('position') == 'fixed');
  if (jQuery(this).scrollTop() > 200&& !isPositionFixed){ 
    jQuery('.fixedElement').css({'position': 'fixed', 'bottom': '0','z-index':'9999','width':'100%','border-top':'1px solid #fff','left':'0'}); 
  }
  if (jQuery(this).scrollTop() < 200 && isPositionFixed) {
    jQuery('.fixedElement').css({'position': 'static'}); 
  } 
});

function handleFiles(files) {
  var dvPreview = document.getElementById("dvPreview");
  var dvPreviewIframe = document.getElementById("dvPreviewIframe");
  dvPreview.innerHTML = "";
  dvPreviewIframe.innerHTML = "";
  var regex = /^([a-zA-Z0-9\s_\\.\-:])+(.jpg|.jpeg|.gif|.png|.bmp|.pdf)$/;
  for (var i = 0; i < files.length; i++) {
    var file = files[i];
    if (regex.test(file.name.toLowerCase())) {
      // If the file is either image or PDF.
      var node = document.createElement("DIV");
      if (files[i].type === 'application/pdf') {
        var dvPreviewFinal = dvPreviewIframe;
        var imgnode = document.createElement("IFRAME");
        imgnode.style = 'height:300px; width:100%';
      }
      else {
        var dvPreviewFinal = dvPreview;
        var imgnode = document.createElement("IMG");
      }
    // var dvPreviewFinal = dvPreviewIframe;
      // var imgnode = document.createElement("IFRAME");
      node.appendChild(imgnode);
      imgnode.src = window.URL.createObjectURL(files[i]);
      imgnode.onload = function() {
        window.URL.revokeObjectURL(this.src);
      }
    dvPreviewFinal.appendChild(node);
      jQuery('#dvPreview').show();
      jQuery('#dvPreviewIframe').show();
    }
    else {
      alert(file.name + " is not a valid Image OR PDF File.");
      dvPreview.innerHTML = "";
      dvPreviewIframe.innerHTML = "";
      return false;
    }
  }
}

function change_spending_auto_spread() {
  var format = function (num) {
  if (!num || num === "0" || num === 0) {
    return "$0";
  }
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
      return("$-" + formatted + ((parts) ? "." + parts[1].substr(1, 2) : ""));
    }
  else {
      return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));
    }
  };
  var assetvalarr = [];
  jQuery('.asset_description').each(function(index, el) {
    var this_val = $(this).val();
    assetvalarr.push(this_val);
  });
  jQuery.ajax({
    url: '/get-all-assets',
    type: 'POST',
    data: {data: assetvalarr},
  }).success(function(output) {
      var spread_final_total = 0.00;
      var spread_current_total = 0.00;
      var spread_new_total = 0.00;

      var getInvAmt = jQuery('.invoice_amount').val();
      var invAmtFnl = getInvAmt.replace(/[^\d\.\-]/g, '');

      jQuery.each(output, function(index1, el1) {
        jQuery('.asset_description').each(function(index, el) {
          if (jQuery(this).val() == index1) {
            var this_ele = jQuery(this).parents('tr');
            var this_ele_curr = this_ele.find('.get_current_asset_value');
            var current_asset_val = 0.00;
            if (el1.CurrentAsseVal && el1.CurrentAsseVal !== "0") {
              current_asset_val = el1.CurrentAsseVal;
            }

            var current_asset = parseFloat(current_asset_val);
            this_ele_curr.val(format(current_asset));
            this_ele.find('.get_current_asset_value_hidden').val(current_asset);
            spread_current_total += current_asset;
          }
        });
      });
      jQuery('.total_current_asset_val').val(spread_current_total);
      var granCurrentAsset_format = format(spread_current_total);
      if (granCurrentAsset_format == '$') {
        granCurrentAsset_format = '$0.00';
      }
      jQuery('.current_asset_val_total').text(format(granCurrentAsset_format));

      jQuery.each(output, function(index1, el1) {
        jQuery('.asset_description').each(function(index, el) {
          if (jQuery(this).val() == index1) {
            var current_asset_val = 0.00;
            if (el1.CurrentAsseVal && el1.CurrentAsseVal !== "0") {
              current_asset_val = el1.CurrentAsseVal;
            }

            var current_asset = parseFloat(current_asset_val);
            var this_ele = jQuery(this).parents('tr');
            var this_ele_curr = this_ele.find('.spread_amount');

            var spread_amt_val = (current_asset/spread_current_total)*invAmtFnl;
            spread_final_total += spread_amt_val;
            this_ele.find('.spread_amount').val(format(spread_amt_val));
          }
        });
      });
      jQuery('.spread-total-amount-count').text(format(spread_final_total));

      jQuery('.new_asset_value_spread').each(function(index1, el1) {
        var this_ele = jQuery(this).parents('tr');
        var spread_val = this_ele.find('.spread_amount').val().replace(/[^\d\.\-]/g, '');
        var current_val = this_ele.find('.get_current_asset_value').val().replace(/[^\d\.\-]/g, '');
        var new_val = parseFloat(spread_val) + parseFloat(current_val);
        spread_new_total += new_val;
        this_ele.find('.new_asset_value_spread').val(format(new_val));
      });
      var granNewAsset_format = format(spread_new_total);
      if (granNewAsset_format == '$') {
        granNewAsset_format = '$0.00';
      }
      else {
        // granNewAsset_format = granNewAsset_format.toFixed(2);
      }
      jQuery('.new_asset_val_total').text(granNewAsset_format);
    });
  }