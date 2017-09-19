Drupal.behaviors.m6connect_program = {	
  attach: function (context, settings) {	
     jQuery('.dataTables_paginate span a.paginate_button').click(function () {
      Drupal.attachBehaviors(jQuery('body'));     
	  var getPage = jQuery(this).text();
	  jQuery('.page_number_id').val(getPage);
    });	 
	 // =========================================
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
	// ==== Column resizer work end here ==== //
	
	// ===============================
	// Amount value setting for all pages
	// ===================================
	jQuery('#edit-estimate-amount').keyup(function (i) {
      jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('#edit-line-item-amt').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('#edit-plan-budget').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
	});
	jQuery('#edit-invoice-amount').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));	  
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
	jQuery('.commit-amt-quarter-one').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('.commit-amt-quarter-two').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });	
	jQuery('.commit-amt-quarter-three').keyup(function (i) {
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
	jQuery('.field_est_line_item_amt').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('.etc-amt-quarter-one-etc').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('.etc-amt-quarter-two-etc').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('.etc-amt-quarter-three-etc').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	jQuery('.etc-amt-quarter-fourth-etc').keyup(function (i) {
	  jQuery(this).val(format(jQuery(this).val()));
    });
	function format2(n, currency) {
      return currency + " " + n.toFixed().replace(/(\d)(?=(\d{3}))/g, "$1,");
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
	
	
	// For adding % sign
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
	jQuery(".field_conigency_percentage").keyup(function() {
	  if (jQuery(this).val().split('').pop() !== '%') {
	    jQuery(this).val($(this).val() + "%");
		jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });
	
	/*jQuery(".po_amt_sales_tax_per").keyup(function() {
	  if (jQuery(this).val().split('').pop() !== '%') {
	    jQuery(this).val($(this).val() + "%");
		jQuery(this).setCursorPosition( jQuery(this).val().length - 1)
      }
    });*/
	// ======================================
	  
	var ccVal = jQuery('.cost_code').val();
	jQuery('.ws_code').val(ccVal);  
    var getPath = window.location.pathname;	
	
	// =====================
	// Work for project Page
	if(getPath == '/program/projects') {
	  // Assing the project id in hiiden field
	  jQuery('.project_programe_main_pro').change(function (e) {
		var projectId = jQuery(this).val();
		jQuery('.project_id_ref').val(projectId);
	  });
	  jQuery('.project-number').change(function (e) {
	    var getNumber = jQuery(this).val();
		var ProNumber = jQuery('.project_programe_main_pro').val();
		jQuery.post( '/check-project-availablity/'+ getNumber +'/project/'+ProNumber, function( data ) { 
		  if(data.access == 0) {
		    jQuery('.project-avail-status .text-danger').text(data.message);
			jQuery('.project-avail-status .text-success').text('');
			//jQuery('.custom-submit-project-button input').attr('disabled','disabled');
		  }
		  if(data.access == 1) {
			jQuery('.project-avail-status .text-danger').text('');  
		    //jQuery('.project-avail-status .text-success').text(data.message);
			jQuery('.project-avail-status .text-success').text('');
			//jQuery('.custom-submit-project-button input').removeAttr('disabled');
		  }		  
		});
	  });
	   jQuery('.project-title').keyup(function (e) {
	    var getTitle = jQuery(this).val();
		var ProNumber = jQuery('.project_programe_main_pro').val();
		jQuery.post( '/check-title-availablity/'+ getTitle +'/project/'+ProNumber, function( data ) { 
		  if(data.access == '0') {
		    jQuery('.project-avail-status-title .text-danger').text(data.message);
			jQuery('.project-avail-status-title .text-success').text('');
			jQuery('.custom-submit-project-button input').attr('disabled','disabled');
		  }
		  if(data.access == '1') {
			jQuery('.project-avail-status-title .text-danger').text('');  
		    //jQuery('.project-avail-status .text-success').text(data.message);
			jQuery('.project-avail-status-title .text-success').text('');
			jQuery('.custom-submit-project-button input').removeAttr('disabled');
		  }		  
		});
	  });

    jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="project-location-region" ) {
        var site_val = jQuery('input[name="hidden-site-field"]').val();
        if (site_val != '') {
          jQuery('select.project-location-site').val(site_val);
          jQuery('select.project-location-site').trigger('change');
        }
        else {
          jQuery('select.project-location-facility').attr('disabled', true);
        }
      }
    });
    jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="project-location-site" ) {
        var site_val = jQuery('input[name="hidden-facility-field"]').val();
        if (site_val != '') {
          jQuery('select.project-location-facility').val(site_val);
        }
      }
    });

    jQuery('.custom-reset-button-project').click(function(event) {
      /* Act on the event */
      jQuery('.project_programe_main_pro').val('0');
      jQuery('.project_programe_main_pro').trigger('change');
    });
	}
	
	
	// ==== Work for estimate page ==== //
	else if(getPath == '/program/estimates') {
	  jQuery("#edit-inner-right-container-left .field_est_line_item_amt").each(function () {
  	    var getVal = jQuery(this).val();
		if(getVal) {
		  jQuery(this).trigger('keyup');
		}
	  });
	  jQuery("#edit-inner-right-container-right .field_conigency_percentage").each(function () {
  	    var getVal = jQuery(this).val();
		if(getVal) {
		  jQuery(this).trigger('keyup');
		}
	  });
	  
	  
	 /* var lineItemTotal = 0;
      jQuery("#edit-inner-right-container-left .field_est_line_item_amt").each(function () {
        var stval = parseFloat(jQuery(this).val());
        lineItemTotal += isNaN(stval) ? 0 : stval;
      });
	  jQuery('.line-item-total-count').text(format(lineItemTotal.toFixed(2)));*/
	  var attrFor = jQuery('#project_estimate_main_container').attr('for');
      if (typeof attrFor !== typeof undefined && attrFor !== false) {
        if(attrFor == 'open' && jQuery('.project_est_ref_nid').val() == '') {
	      jQuery('.project-action').css('pointer-events','none');
		  jQuery('.est-load-budget').css('pointer-events','none');		  
		  jQuery('.project-action button').css('background-image','linear-gradient(rgb(187, 179, 179) 0px, rgb(183, 178, 178) 100%)');
		  jQuery('.project-action button').css('border-color','#eee');
	    }
	  }
	  else {
	    jQuery('.project-action').css('pointer-events','auto');
		jQuery('.est-load-budget').css('pointer-events','auto');		  
	    jQuery('.project-action button').css('background-image','-webkit-linear-gradient(top,#5cb85c 0,#419641 100%)');
	    jQuery('.project-action button').css('border-color','#3e8f3e');
	  }	
	   // New line item work start here
	  jQuery('.estimate_cost_code').change(function (e) {
	    var getCode = jQuery(this).val();
		jQuery.post( '/get-contigency-status/'+getCode, function( data ) { 
		  if(data == 1) {
			jQuery('.line_item_contigency_status').val('TRUE');  
			jQuery('.line_item_amt').val('');
		    jQuery('.form-item-line-item-amt').hide();
			jQuery('.budget-contigency-section').show();
		  }
		  else {
			jQuery('.line_item_amt_contgency').val();
			jQuery('.line_item_per_contgency').val();
			jQuery('.line_item_contigency_status').val('FALSE');    
		    jQuery('.form-item-line-item-amt').show();
			jQuery('.budget-contigency-section').hide();
		  }
		});
	  });
	  jQuery('.custom-line-item-sub').click(function (e) {
	    var contigencyAmt = jQuery('.line_item_amt_contgency').val().replace('$', '');
		var contigencyPer = jQuery('.line_item_per_contgency').val().replace('%', '');
		if(contigencyAmt != '' && contigencyPer !== '') {
		  alert('Fill either Line Item Amount OR Allow Percentage!');
		  return false;
		}
		else {
		  return true;
		}
	  });
	  
	  // New line item work ends here
	  	
	  // Generating Popup if no estimate found on estimate page
	  jQuery('.nod-data-post-popup').click(function(e) {
	    e.preventDefault();
		jQuery('#estimate-approve-nodata-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>No estimate found, please create an estimate (by adding an Estimate Name above) to add budget line items to.</strong></p></div>');
		jQuery('#estimate-approve-nodata-dialog').dialog('open');
		e.preventDefault();
		return false;
	  });
	  // Popup for no estimate end here	  
	  
	  var projectId = jQuery('.project-program-sel').val();
	  jQuery('.project_ref_nid').val(projectId);		
	  jQuery('.edit-est', context).click(function (e) {		
        e.preventDefault();
		jQuery('#project_estimate_main_container').attr('for','open');
		jQuery('#project_estimate_main_container').attr('data','edit');			
		jQuery('#project_estimate_main_container').show();	
		jQuery('.main-estimate-submit-call').show();	
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();				  
	    var projectId = jQuery(this).attr('for');		
		jQuery('.project_est_ref_nid').val(projectId);	    
		
		jQuery('.project-program-sel-est-details').val(projectId).trigger('change');		  
	    jQuery('html, body').animate({
          scrollTop: "0px"
	    }, 800); 
      }); 	
	  // get budget id from query string.
	  /*var commitid = getUrlParameter('bid');
	  if(!isNaN(commitid)) { 
	    jQuery('.project-program-sel-est-details').val(commitid).trigger('change');
		jQuery('#project_estimate_main_container').attr('for','open');
		jQuery('#project_estimate_main_container').attr('data2','querystring');
		jQuery('#project_estimate_main_container').show();
		jQuery('.project_est_ref_nid').val(commitid);
	  } */
	jQuery('.estimate_name').change(function (e) {
	    var getTitle = jQuery(this).val();
		var ProNumber = jQuery('.project-program-sel').val();
		jQuery.post( '/check-title-availablity/'+ getTitle +'/budget/'+ProNumber, function( data ) { 
		  if(data.access == 0) {
		    jQuery('.project-avail-status-title .text-danger').text(data.message);
			jQuery('.project-avail-status-title .text-success').text('');
			jQuery('.main-estimate-submit-call').attr('disabled','disabled');
		  }
		  if(data.access == 1) {
			jQuery('.project-avail-status-title .text-danger').text('');  
		    //jQuery('.project-avail-status .text-success').text(data.message);
			jQuery('.project-avail-status-title .text-success').text('');
			jQuery('.main-estimate-submit-call').removeAttr('disabled');
		  }		  
		});
	  });
	  jQuery('.custom-reset-button').click(function (e) {
	    jQuery('#project_estimate_main_container').hide();
		jQuery('.custom-submit-commitment-reset').hide();
		jQuery('.main-estimate-submit-call').hide();
		jQuery('.custom-submit-reset').hide();
		jQuery('#project_estimate_main_container').attr('for', 'closed');
		jQuery('#project_estimate_main_container').attr('data', 'edit');
		jQuery('.project-action').css('pointer-events','auto');
		jQuery('.est-load-budget').css('pointer-events','auto');		  
		  jQuery('.project-action button').css('background-image','-webkit-linear-gradient(top,#5cb85c 0,#419641 100%)');
		  jQuery('.project-action button').css('border-color','#3e8f3e');	
	  });	
	  var pid = getUrlParameter('pid');
	  if(!isNaN(pid)) { 
		jQuery('#project_estimate_main_container').attr('for','open'); 
		jQuery('#project_estimate_main_container').show();
		jQuery('.program-project-sub-menu-links').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
		if(jQuery('.project_est_ref_nid').val() == '') {
		  // Disable Action buttons
		  jQuery('.project-action').css('pointer-events','none');
		  jQuery('.est-load-budget').css('pointer-events','none');		  
		  jQuery('.project-action button').css('background-image','linear-gradient(rgb(187, 179, 179) 0px, rgb(183, 178, 178) 100%)');
		  jQuery('.project-action button').css('border-color','#eee');
		}
		else {
		  //Enable action button
		  jQuery('.project-action').css('pointer-events','auto');
		  jQuery('.est-load-budget').css('pointer-events','auto');		  
		  jQuery('.project-action button').css('background-image','-webkit-linear-gradient(top,#5cb85c 0,#419641 100%)');
		  jQuery('.project-action button').css('border-color','#3e8f3e');	
		}
	  }
	  else {
		//Enable action button
		  jQuery('.project-action').css('pointer-events','auto');
		  jQuery('.est-load-budget').css('pointer-events','auto');		  
		  jQuery('.project-action button').css('background-image','-webkit-linear-gradient(top,#5cb85c 0,#419641 100%)');
		  jQuery('.project-action button').css('border-color','#3e8f3e');	
	  }
	  // Hidig the data for budget data for edit section
	  if(jQuery('.project_est_ref_nid').val() != '') {
	     jQuery('.project-details-full-mid').hide();
		 jQuery('.m6connect-custom-line-item-table').show()
	  }	  
	  else {
	    jQuery('.project-details-full-mid').show();
		jQuery('.m6connect-custom-line-item-table').hide()
	  }
	  jQuery('.field_est_line_item_amt').keyup(function (e) {
		var getId = jQuery(this).attr('id');
	    var contigencyAmt = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		var getSubtotal = jQuery('.line-item-total-sub-value').val();
		var getPer = (contigencyAmt/getSubtotal)*100;
		jQuery('#cost-code-per-'+getId+' input.field_conigency_percentage').val(format(getPer.toFixed(2)));
	  });
	  jQuery('.field_conigency_percentage').keyup(function (e) {
		var getId = jQuery(this).attr('id');
	    var contigencyPer = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		var getSubtotal = jQuery('.line-item-total-sub-value').val();
		var getAmt = (getSubtotal * contigencyPer)/100;	    		
		jQuery('#cost-code-amt-'+getId+' input.field_est_line_item_amt').val(format(getAmt.toFixed(2)));
	  });
	}		
	// ==== Work for Commitment page ==== //
	else if(getPath == '/program/commitments') {
	  jQuery('.commitment_for_etc').multiselect({
        columns: 1,
    	placeholder: 'Select ETC'
	  });
	  if(jQuery('.po_amt_discount_form').val() != '') { jQuery('.po_amt_discount').val(jQuery('.po_amt_discount_form').val()); jQuery('.po_amt_discount').trigger('keyup'); }
	  if(jQuery('.po_amt_sales_tax_amt_form').val() != '') { jQuery('.po_amt_sales_tax_amt').val(jQuery('.po_amt_sales_tax_amt_form').val()); }
	  //if(jQuery('.po_amt_sales_tax_per_form').val() != '') { jQuery('.po_amt_sales_tax_per').val(jQuery('.po_amt_sales_tax_per_form').val()); }
	  if(jQuery('.po_amt_other_cost_form').val() != '') { jQuery('.po_amt_other_cost').val(jQuery('.po_amt_other_cost_form').val()); jQuery('.po_amt_other_cost').trigger('keyup'); }
	  if(jQuery('.po_amt_discount_sh_form').val() != '') { jQuery('.po_amt_discount_sh').val(jQuery('.po_amt_discount_sh_form').val()); jQuery('.po_amt_discount_sh').trigger('keyup'); }
	  
	  var ProId = jQuery('.project-program-commitment-sel').val();
	   jQuery.post( '/get-cost-code/'+ProId, function( data ) {
	      jQuery('.cost_code_update').empty();
	      jQuery.each(data,function(key, value) {
		    var opt = jQuery('<option>');
    	    opt.val(key).text(value);
    	    opt.appendTo('.cost_code_update');
		  });
		  jQuery(".cost_code_update").prepend("<option value selected='selected'>- None -</option>");
		  var tblrows = jQuery(".project-mgmt-po-item-table tbody tr");
	      tblrows.each(function (index) {
          var tblrow = jQuery(this);
		  var getCC = tblrow.find(".ws_code_hidden").val();
		  if(getCC) {
		    tblrow.find(".cost_code_update").val(getCC);
		  }
		  else {		  
		    tblrow.find(".cost_code_update").val(jQuery('.cost_code_update').val());
		    tblrow.find(".ws_code_hidden").val(jQuery('.cost_code_update').val());
		  }
	    });    
	  });	
	  jQuery('.cost_code_update').change(function() {
   	    var id = jQuery(this).closest('tr').attr('id');  
		var getCC = jQuery(this).val();
		jQuery('#'+id+ ' .ws_code_hidden').val(getCC);
	  });	 	 	
	  jQuery('.project-program-commitment-sel').change(function () {
	    jQuery("select.commitment_for_etc option").prop("selected", false);
	    jQuery(".list-unstyled li input").prop("checked", false);		  
	  // Apply ui blocker
	  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
  	    var urlajax = ajaxOptions.url;
  	    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-commitment"){
          jQuery.blockUI({
                //theme:     true,
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
  	      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-commitment"){
            jQuery.unblockUI();
			if(jQuery('.commitment-number-filter select').val()) {
			  jQuery('.commitment-number-filter select').trigger('change');
			}
            if(jQuery('.company-name-filter select').val()) {
			  jQuery('.company-name-filter select').trigger('change');
			}
			if(jQuery('.record-type-filter select').val()) {
			  jQuery('.record-type-filter select').trigger('change');
			}
			if(jQuery('.cost-code-filter select').val()) {
			  jQuery('.cost-code-filter select').trigger('change');
			}
          }
        });	
	  });	  	
	  jQuery('.simple-button-for-commit').hide();	
	  jQuery('#commitment_number_select_cust').hide();	
	  jQuery('#commitment_number_input_cust').show();
	  
	  jQuery('#rest-all-filter-commit').click(function (e) {
	    //jQuery('.project-program-commitment-sel').trigger('change');
		jQuery('.new-record-reset-setting-btn').trigger('click');
	  });
	  
	  jQuery('.resesting').click(function (e) {
	    jQuery('.new-record-reset-setting-btn').trigger('click');
      }); 	
	  // Commitment type list work
	  jQuery('#commitment_number_select_cust_old').hide();	  
	  if (jQuery(".commitment_type").hasClass("commitment_type_half")) {
  	    jQuery(".commitment_type option[value='change purchase order']").attr('disabled','disabled');
		jQuery(".commitment_type option[value='potential change order']").attr('disabled','disabled');
		jQuery(".commitment_type option[value='change order']").attr('disabled','disabled');
		jQuery(".commitment_type option[value='contract amendment']").attr('disabled','disabled');		
		jQuery('#commitment_number_select_cust').hide();
		jQuery('#commitment_number_input_cust').show();		
      }
	  else {
	    jQuery(".commitment_type option[value='change purchase order']").removeAttr('disabled');
		jQuery(".commitment_type option[value='potential change order']").removeAttr('disabled');
		jQuery(".commitment_type option[value='change order']").removeAttr('disabled');
		jQuery(".commitment_type option[value='contract amendment']").removeAttr('disabled');		
		//jQuery('#commitment_number_select_cust').show();
		if(jQuery( "#commitment_number_select_cust" ).attr('data') == 'clsActive') {
		  jQuery('#commitment_number_select_cust').show();
		  jQuery('#commitment_number_input_cust').hide();	
		}
		else if(jQuery("#commitment_number_input_cust" ).attr('data') == 'clsActive') {
		  jQuery('#commitment_number_select_cust').hide();
		  jQuery('#commitment_number_input_cust').show();
		}
		else {
		  jQuery('#commitment_number_select_cust').hide();
		  jQuery('#commitment_number_input_cust').hide();
		}
		
		jQuery('.commitment_type').change(function (e) {
		  var typeVal = jQuery(this).val();
		  if(typeVal == 'purchase order' || typeVal == 'contract') {
		    jQuery('#commitment_number_input_cust').show();
			jQuery('#commitment_number_input_cust').attr('data', 'clsActive');
			jQuery('#commitment_number_select_cust').hide();
			jQuery('#commitment_number_select_cust').attr('data', 'clsDeactive');
		  }
		  else {
		    jQuery('#commitment_number_input_cust').hide();
			jQuery('#commitment_number_input_cust').attr('data', 'clsDeactive');
			jQuery('#commitment_number_select_cust').show();
			jQuery('#commitment_number_select_cust').attr('data', 'clsActive');
		  }
		});
		if(jQuery('.disbled-section').hasClass('container-disabled')) {
		  jQuery('.disbled-section').css('pointer-events', 'none');
		  jQuery('#alert-container-section').css('pointer-events', 'none');
		}
		else {
		  jQuery('.disbled-section').css('pointer-events', 'auto');
		  jQuery('#alert-container-section').css('pointer-events', 'auto');
		}		
	  }
	  // Work for unit cost table for edit section	  
	  jQuery('.po_total').trigger('keyup');
	  jQuery('.unit_cost').trigger('keyup');
	  jQuery('.po_quantity').trigger('change');	  
	  jQuery('.po_amt_discount').trigger('keyup');
	  var tblrows = jQuery(".project-mgmt-po-item-table tbody tr");
	  tblrows.each(function (index) {
        var tblrow = jQuery(this);
		var qty = tblrow.find(".unit_cost").val();
		var price = tblrow.find(".po_quantity").val();
		var subTotal = parseInt(qty,10) * parseFloat(price);
		if(!isNaN(subTotal)) {
		  var qty = tblrow.find(".po_total").val(format(subTotal));
		}
		if (!isNaN(subTotal)) { 
		  tblrow.find('.po_total').val(format(subTotal));
    	  var grandTotal = 0;
    	  jQuery(".po_total").each(function () {
            var stval = parseFloat(jQuery(this).val());
        	grandTotal += isNaN(stval) ? 0 : stval;
    	  });     	
		  (isNaN(grandTotal)) ? '' : jQuery('.final_po_total_amt').val(grandTotal);
		  (isNaN(grandTotal)) ? '' : jQuery('.total_po_amount').text(format(grandTotal.toFixed(2)));
		  (isNaN(grandTotal)) ? '' : jQuery('.total_po_amount_final').text(format(grandTotal.toFixed(2)));
		  jQuery('.commitment_cost_code_clone').val(jQuery('.cost_code').val());
		}	    
	  });
	  // Commitment page PO total calculation	  
	  var tblrows = jQuery(".project-mgmt-po-item-table tbody tr");
	  tblrows.each(function (index) {
        var tblrow = jQuery(this);
		tblrow.find('.unit_cost').on('keyup', function () {
	      var qty = tblrow.find(".unit_cost").val();
	  	  var price = tblrow.find(".po_quantity").val();		  
		  var qty = qty.replace(/[^\d\.\-]/g, '');
		  var price = price.replace(/[^\d\.\-]/g, '');		  
	  	  var subTotal = parseFloat(qty) * parseFloat(price);
		  if (!isNaN(subTotal)) { 
			tblrow.find('.po_total').val(format(subTotal)); 						
    	    var grandTotal = 0;
    	    jQuery(".po_total").each(function () {
			  var getVal = jQuery(this).val();	
              var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
        	  grandTotal += isNaN(stval) ? 0 : stval;
    	    }); 
			(isNaN(grandTotal)) ? '' : jQuery('.final_po_total_amt').val(grandTotal);			
			(isNaN(grandTotal)) ? '' : jQuery('.total_po_amount').text(format(grandTotal.toFixed(2)));
		    (isNaN(grandTotal)) ? '' : jQuery('.total_po_amount_final').text(format(grandTotal.toFixed(2)));
			jQuery('.commitment_cost_code_clone').val(jQuery('.cost_code').val());
		  }
		  jQuery('.po_total').trigger('keyup');
		  jQuery('.po_amt_discount').trigger('keyup');
		  jQuery('.po_amt_sales_tax_amt').trigger('keyup');
		  //jQuery('.po_amt_sales_tax_per').trigger('keyup');
		  jQuery('.po_amt_other_cost').trigger('keyup');
		  jQuery('.po_amt_discount_sh').trigger('keyup');
	    });
 	    tblrow.find('.po_quantity').on('keyup', function () {
	      var qty = tblrow.find(".unit_cost").val();		  
	  	  var price = tblrow.find(".po_quantity").val();
		  var qty = qty.replace(/[^\d\.\-]/g, '');
		  var price = price.replace(/[^\d\.\-]/g, '');
		  var subTotal = parseFloat(qty) * parseFloat(price);
		  if (!isNaN(subTotal)) { 
			tblrow.find('.po_total').val(format(subTotal));			
    	    var grandTotal = 0;
    	    jQuery(".po_total").each(function () {
			  var getVal = jQuery(this).val();
              var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
        	  grandTotal += isNaN(stval) ? 0 : stval;
    	    }); 					  
			(isNaN(grandTotal)) ? '' : jQuery('.final_po_total_amt').val(grandTotal);
		    (isNaN(grandTotal)) ? '' : jQuery('.total_po_amount').text(format(grandTotal.toFixed(2)));
		    (isNaN(grandTotal)) ? '' : jQuery('.total_po_amount_final').text(format(grandTotal.toFixed(2)));
		  }		  
			jQuery('.po_amt_discount').trigger('keyup');
		    jQuery('.po_amt_sales_tax_amt').trigger('keyup');		    
		    jQuery('.po_amt_other_cost').trigger('keyup');
		    jQuery('.po_amt_discount_sh').trigger('keyup');
			jQuery('.commitment_cost_code_clone').val(jQuery('.cost_code').val());
	    });	    						
	  });	  
	  // Remove data from po item details		
	  var tblrows = jQuery(".project-mgmt-po-item-table tbody tr");
		tblrows.each(function (index) {
		  var tblrow = jQuery(this);  
		  tblrow.find('.workflow-remove-submit').on('mousedown', function () {
			var etcId = parseInt(tblrow.find(".itemCount").val());
			var etcVal = parseInt(tblrow.find(".etc_status_id").val());					  
			var checkedValues = jQuery(".list-unstyled li input[type=checkbox]:checked").map(function () {
			  var getVal = jQuery(this).val();
			  if(getVal == etcVal) { 				
				  jQuery(".list-unstyled li input[value='" + etcVal + "']").prop("checked", false);
				  jQuery("select.commitment_for_etc option[value='" + etcVal + "']").prop("selected", false);
			  }
			});
			jQuery('.etc-loaded-data-inner #etc-'+etcId).remove();
		  });
		});
	  // End work of po item total
	  /*jQuery('.fa-times-filter').unbind('click').bind('click',function () {
  	    jQuery(this).parent().siblings('.filter-sort').trigger('click');
	  });*/
	  jQuery('.fa-times-filter').unbind('click').bind('click',function () {
  	    var getId = jQuery(this).attr('id');
		jQuery('.'+getId).trigger('click')
	  });
	  jQuery('.edit-commitment-detail', context).click(function (e) { 
	    jQuery('#project_commitment_main_container').attr('for','open');
		jQuery('#project_commitment_main_container').attr('data','edit');
		jQuery('#project_commitment_main_container').show();
		jQuery('#main-class').show();	
		jQuery('.custom-submit-commitment').show();  
		jQuery('.custom-submit-commitment-reset').show();
        e.preventDefault();
	    //var projectId = $(this).attr('for');
		var commitmentID = jQuery(this).attr('for');
	    var CommitemtUrlID = getUrlParameter('cid');
		  if(CommitemtUrlID) { 
	      if(commitmentID == CommitemtUrlID) {
		    jQuery('.project_commitment_nid').val(commitmentID);  
		  }  
		  else {
		    var proId = jQuery('.project-program-commitment-sel').val();	
		    window.location.href="/program/commitments?pid="+proId+'&cid='+commitmentID;
		  }
	    }
	    else {	  
	      jQuery('.project-program-sel-commitment').val(commitmentID).trigger('change');
	      jQuery('.project_commitment_nid').val(commitmentID);
		  
	    }		
	    jQuery('html, body').animate({
          scrollTop: "0px"
	     }, 800); 
      });		  	  
	  // Functionalty for commitment filter
	  jQuery('body .filter-sort').unbind('click').bind('click',function () {
	    var getId = jQuery(this).attr('id');		
		var getstatus = jQuery('body').find('.'+getId).attr('data');
		if(getstatus == 'hiddenCus') {
          jQuery('body').find('.'+getId).show();
		  jQuery('body').find('.rest-all-filter-commit').show();
		  jQuery('body').find('.'+getId).attr('data', 'showCus');  
		  jQuery('body').find('.'+getId+'-def').hide();
		}
		else if(getstatus == 'showCus') {
		  jQuery('body').find('.'+getId).hide();
		  jQuery('body').find('.rest-all-filter-commit').hide();
		  jQuery('body').find('.'+getId).attr('data', 'hiddenCus');  
		  if(jQuery('.'+getId+' form select').val()) {
		    jQuery('body').find('.'+getId+'-def').show();
		  }
		}
		jQuery('#rest-all-filter-commit').show();	
      });  
	  jQuery('.project_number').change(function () {
	    var commitId = jQuery('.project_commitment_nid').val();
        if(commitId != '') {
		  var getProject = jQuery('.project_number option:selected').text();
		  var getPro = getProject.split('|');		
	      var getMainPro = jQuery('.project-program-commitment-sel option:selected').text();
          if(getMainPro != getPro[0]) {
		    jQuery('.custom-submit-commitment').hide();
			jQuery('.custom-submit-commitment-reset').hide();
		    jQuery('.simple-button-for-commit').show();
		  }
		  else {
		    jQuery('.custom-submit-commitment').show();
			jQuery('.custom-submit-commitment-reset').show();
		    jQuery('.simple-button-for-commit').hide();
		  }
		}
	  });	  
	  jQuery('.simple-button-for-commit').click(function (e) {
        e.preventDefault();
		var getProject = jQuery('.project_number option:selected').text();
		var getPro = getProject.split('|');		
	    jQuery('#custom-commit-dialog').html('<div style="padding-bottom:25px;"><p>Are you sure you want to move this commitment to : "'+getPro[0]+'." This will also move the invoices and ETC associated with this commitment</p></div>');
	    jQuery('#custom-commit-dialog').dialog('open');
	    e.preventDefault();
	    return false;			  
      });
	  // Check commitment number availability
	  jQuery('.commitment_number').change(function (e) {
	    var getNumber = jQuery(this).val();
		var ProNumber = jQuery('.project-program-commitment-sel').val();
		jQuery.post( '/check-project-availablity/'+ getNumber +'/commitment/'+ProNumber, function( data ) { 
		  if(data.access == 0) {
		    jQuery('.project-avail-status .text-danger').text(data.message);
			jQuery('.project-avail-status .text-success').text('');
			//jQuery('.custom-submit-commitment input').attr('disabled','disabled');
		  }
		  if(data.access == 1) {
			jQuery('.project-avail-status .text-danger').text('');  
		    //jQuery('.project-avail-status .text-success').text(data.message);
			jQuery('.project-avail-status .text-success').text('');
			//jQuery('.custom-submit-commitment input').removeAttr('disabled');
		  }		  
		});
	  });
	  jQuery('.custom-reset-button').click(function (e) {
	    jQuery('#project_commitment_main_container').hide();
		jQuery('#alert-container-section').hide();
		jQuery('.custom-submit-commitment-reset').hide();
		jQuery('#main-class').hide();
		jQuery('#project_commitment_main_container').attr('for', 'closed');		
	  });
	  jQuery("input:checkbox.image-remove-update").click(function() {
	    var getFid = jQuery(this).val();
        var nodeId = jQuery(this).attr('for');
        jQuery.post( '/update-image-reove/'+getFid+'/'+nodeId, function( data ) { 
          jQuery('.project-program-sel-spending').val(nodeId).trigger('change');
        });
	  });
	  // =================================
	  // Additionalty Tax Invoice Calculation
	  jQuery('.po_amt_discount').keyup(function () {	    
	    var amt = jQuery('.total_po_amount').text();
		var getDiscount = jQuery(this).val();
		if(amt != '0') {		  	
		  var poAmtTotal = amt.replace(/[^\d\.\-]/g, '');
		  var discAmt = getDiscount.replace(/[^\d\.\-]/g, '');
		  jQuery('.po_amt_discount_form').val(discAmt);
		  var taxAmt = (isNaN(jQuery('.po_amt_sales_tax_amt').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_amt').val().replace(/[^\d\.\-]/g, '');		  
		  var taxPer = (isNaN(jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, '');
		  var getOtherCost = jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');
		  var otherCost = (isNaN(getOtherCost)) ? '' : jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');
		  var getSh = jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');		  
		  var sh = (isNaN(jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');
		  var taxPerAmt = ((poAmtTotal*taxPer)/100);
		  if(poAmtTotal == '') { poAmtTotal = 0; } 	  
		  if(discAmt == '') { discAmt = 0; } 	  
		  if(taxAmt == '') { taxAmt = 0; } 	  
		  if(otherCost == '') { otherCost = 0; }
		  if(sh == '') { sh = 0; } 	  
		  var disTotalAmt = (parseFloat(poAmtTotal) - parseFloat(discAmt) + parseFloat(taxAmt) + parseFloat(otherCost) + parseFloat(sh));		  		  
		}		
		(isNaN(disTotalAmt)) ? '' : jQuery('.final_po_total_amt').val(disTotalAmt);
		(isNaN(disTotalAmt)) ? '' : jQuery('.total_po_amount_final').text(format(disTotalAmt.toFixed(2)));			
	  });
	  jQuery('.po_amt_sales_tax_amt').keyup(function () {
		var amt = jQuery('.total_po_amount').text();  
	    var getTaxAmt = jQuery(this).val();    
		if(amt != '0') {
		  var poAmtTotal = amt.replace(/[^\d\.\-]/g, '');
		  var taxAmt = getTaxAmt.replace(/[^\d\.\-]/g, '');
		  var calculatePer = (taxAmt/poAmtTotal*100);
		  if(calculatePer != 0) {
		    var discAmt = (isNaN(calculatePer)) ? '' : jQuery('.po_amt_sales_tax_per').val(calculatePer);
			//jQuery('.po_amt_sales_tax_per').trigger('keyup');
		  }
		  else {
		    var discAmt = (isNaN(calculatePer)) ? '' : jQuery('.po_amt_sales_tax_per').val('');
		  }		  
		  jQuery('.po_amt_sales_tax_amt_form').val(taxAmt);		  
		  jQuery('.po_amt_sales_tax_per_form').val(calculatePer);		  		  		  
		  var discAmt = (isNaN(jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, '');		  
		  var taxPer = (isNaN(jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, '');		  		 
		  var getOtherCost = jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');  
		  var otherCost = (isNaN(getOtherCost)) ? '' : jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');
		  var getSh = jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');
		  var sh = (isNaN(jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, ''))) ? 0 : jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');		  
		  var taxPerAmt = ((poAmtTotal*taxPer)/100);		  
		  if(poAmtTotal == '') { poAmtTotal = 0; } 	  
		  if(discAmt == '') { discAmt = 0; } 	  
		  if(taxAmt == '') { taxAmt = 0; } 	  
		  if(otherCost == '') { otherCost = 0; }
		  if(sh == '') { sh = 0; } 	  		  
		  var disTotalAmt = (parseFloat(poAmtTotal) - parseFloat(discAmt) + parseFloat(taxAmt) + parseFloat(otherCost) + parseFloat(sh));		  
		}				
		(isNaN(disTotalAmt)) ? '' : jQuery('.final_po_total_amt').val(disTotalAmt);
		(isNaN(disTotalAmt)) ? '' : jQuery('.total_po_amount_final').text(format(disTotalAmt.toFixed(2)));	
	  });	  	  	  
	  jQuery('.po_amt_sales_tax_per').keyup(function () {
	    var getTaxPer = jQuery(this).val();		
	    var amt = jQuery('.total_po_amount').text();
		if(amt != '0') {
		  var poAmtTotal = amt.replace(/[^\d\.\-]/g, '');
		  var taxPer = getTaxPer.replace(/[^\d\.\-]/g, '');		  
		  var calculateAmt = (poAmtTotal*taxPer/100);		  		  
		  (isNaN(calculateAmt)) ? '' : jQuery('.po_amt_sales_tax_amt').val(calculateAmt);		  
		  jQuery('.po_amt_sales_tax_per_form').val(taxPer);
		  var discAmt = (isNaN(jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, '');		  
		  var taxPer = (isNaN(jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, '');
		  var getOtherCost = jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');
		  var otherCost = (isNaN(getOtherCost)) ? '' : jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');		  
		  var getSh = jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');
		  var sh = (isNaN(jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');
		  var taxPerAmt = ((poAmtTotal*taxPer)/100);
		  if(poAmtTotal == '') { poAmtTotal = 0; } 	  
		  if(discAmt == '') { discAmt = 0; } 	  
		  if(calculateAmt == '') { calculateAmt = 0; } 	  
		  if(otherCost == '') { otherCost = 0; }
		  if(sh == '') { sh = 0; } 	  		  
		  var disTotalAmt = (parseFloat(poAmtTotal) - parseFloat(discAmt) + parseFloat(calculateAmt) + parseFloat(otherCost) + parseFloat(sh));
		  (isNaN(disTotalAmt)) ? '' : jQuery('.final_po_total_amt').val(disTotalAmt);
		  (isNaN(disTotalAmt)) ? '' : jQuery('.total_po_amount_final').text(format(disTotalAmt.toFixed(2)));	
		}		
	  });
	  
	  jQuery('.po_amt_other_cost').keyup(function () {
	    var getOtherCost = jQuery(this).val();		
	    var amt = jQuery('.total_po_amount').text();
		if(amt != '0') {		  			  
		  var poAmtTotal = amt.replace(/[^\d\.\-]/g, '');
		  var otherCost = getOtherCost.replace(/[^\d\.\-]/g, '');		  
		  jQuery('.po_amt_other_cost_form').val(otherCost);
		  var taxAmt = (isNaN(jQuery('.po_amt_sales_tax_amt').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_amt').val().replace(/[^\d\.\-]/g, '');		  
		  var discAmt = (isNaN(jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, '');
		  var getSh = jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');
		  var sh = (isNaN(jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount_sh').val().replace(/[^\d\.\-]/g, '');
		  var taxPer = (isNaN(jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, '');	
		  var taxPerAmt = ((poAmtTotal*taxPer)/100);
		  if(poAmtTotal == '') { poAmtTotal = 0; } 	  
		  if(discAmt == '') { discAmt = 0; } 	  
		  if(taxAmt == '') { taxAmt = 0; } 	  
		  if(otherCost == '') { otherCost = 0; }
		  if(sh == '') { sh = 0; }
		  var disTotalAmt = (parseFloat(poAmtTotal) - parseFloat(discAmt) + parseFloat(taxAmt) + parseFloat(otherCost) + parseFloat(sh));
		  (isNaN(disTotalAmt)) ? '' : jQuery('.final_po_total_amt').val(disTotalAmt);
		  (isNaN(disTotalAmt)) ? '' : jQuery('.total_po_amount_final').text(format(disTotalAmt.toFixed(2)));	
		}		
	  });
	  
	  jQuery('.po_amt_discount_sh').keyup(function () {
	    var getShAmt = jQuery(this).val();		
	    var amt = jQuery('.total_po_amount').text();
		if(amt != '0') {
		  var poAmtTotal = amt.replace(/[^\d\.\-]/g, '');	
		  var sh = getShAmt.replace(/[^\d\.\-]/g, '');
		  jQuery('.po_amt_discount_sh_form').val(sh);		  
		  var discAmt = (isNaN(jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_discount').val().replace(/[^\d\.\-]/g, '');
		  var taxAmt = (isNaN(jQuery('.po_amt_sales_tax_amt').val().replace(/[^\d\.\-]/g, ''))) ? '' : jQuery('.po_amt_sales_tax_amt').val().replace(/[^\d\.\-]/g, '');
		  var getOtherCost = jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');
		  var otherCost = (isNaN(getOtherCost)) ? '' : jQuery('.po_amt_other_cost').val().replace(/[^\d\.\-]/g, '');		  
		  var taxPer = (isNaN(jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, ''))) ? 0 : jQuery('.po_amt_sales_tax_per').val().replace(/[^\d\.\-]/g, '');	
		  var taxPerAmt = ((poAmtTotal*taxPer)/100);		  
		  if(poAmtTotal == '') { poAmtTotal = 0; } 	  
		  if(discAmt == '') { discAmt = 0; } 	  
		  if(taxAmt == '') { taxAmt = 0; } 	  
		  if(otherCost == '') { otherCost = 0; }
		  if(sh == '') { sh = 0; }
		  var disTotalAmt = (parseFloat(poAmtTotal) - parseFloat(discAmt) + parseFloat(taxAmt)+ parseFloat(otherCost) + parseFloat(sh));
		  (isNaN(disTotalAmt)) ? '' : jQuery('.final_po_total_amt').val(disTotalAmt);
		  (isNaN(disTotalAmt)) ? '' : jQuery('.total_po_amount_final').text(format(disTotalAmt.toFixed(2)));	
		}		
	  });	  
      // ============================
	  jQuery('.filter-custom-range').unbind('click').bind('click',function () {
	      var getProId = jQuery(this).attr('for');  
	      var lastRowCommitNid = jQuery(".m6connect-program-commitment-table tr").last().attr('for');	  		
	      var totalRecords = jQuery(this).val();		  
		  var endRange = jQuery('.commitment-data-load-more-to').val();
	      jQuery.post( '/load-more-data/commit/'+ getProId +'/'+endRange, function( data ) { 
	        if(data.tableDate!=''){
		      jQuery(".m6connect-program-commitment-table tbody").html(data.tableDate);
			  Drupal.attachBehaviors(jQuery('body'));
		    }		  
	      });
	   });
	  	   // Triggering call back from etc drop down
	      jQuery(".ms-options ul li input").click(function (e) {
          if (jQuery(this).prop('checked')) {
            jQuery("select.commitment_for_etc option[value='" + jQuery(this).val() + "']").prop("selected", true);    
            jQuery('.commitment_for_etc').trigger('blur');
          }
          else {
            var projectnid = jQuery(this).val();
            if (jQuery('.etc-loaded-data-inner').length > 0) {
              jQuery('.etc-loaded-data-inner .load-etc-main').each(function(ele) {
                if (jQuery(this).attr('data') == projectnid) {
                  jQuery(this).find('.remove-etc-cust').trigger('click');
                }
              });
            }
          }
        });
	   //Remove etc data from table and conatiner
	  jQuery('.remove-etc-cust').click(function (e) {
	    var getEtcId = jQuery(this).attr('id');
		var tblrows = jQuery(".project-mgmt-po-item-table tbody tr");
	    tblrows.each(function (index) {
		  var tblrow = jQuery(this);  
		  var getTableRowId = tblrow.find('.itemCount').val();
    	  if(getTableRowId == getEtcId) {
		    jQuery(this).find('.workflow-remove-td input').trigger('mousedown');
		  }
	    });
	  });	  	  
	  
	  // Load data for po details conatiner	  
	  var tblrows = jQuery(".project-mgmt-po-item-table tbody tr");
	  tblrows.each(function (index) {
		var tblrow = jQuery(this);  
		var getEtcId = tblrow.find('.etc_status_id').val();
		jQuery(".list-unstyled li input[value='" + getEtcId + "']").prop("checked", true);		
		jQuery("select.commitment_for_etc option[value='" + getEtcId + "']").prop("selected", true);
	  });	 	
	   // =========================================================
	  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
        var urlajax = ajaxOptions.url;     
		if (urlajax.indexOf("/get-total-number-of-data/") === 0){ 
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
  	      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name==="select-commitment-number" || ajaxOptions.extraData._triggering_element_name==="select-company-name" || ajaxOptions.extraData._triggering_element_name==="select-record-type" || ajaxOptions.extraData._triggering_element_name==="select-cost-code")){
			
			if(jQuery('.commitment-number-filter select').val()) {
		      jQuery('.commitment-number-filter').attr('data','showCus');
			  jQuery('body').find('.commitment-number-filter-def').show();
		    }
		    if(jQuery('.company-name-filter select').val()) {
		      jQuery('.company-name-filter').attr('data','showCus');
			  jQuery('body').find('.company-name-filter-def').show();
		    }
		    if(jQuery('.record-type-filter select').val()) {
		      jQuery('.record-type-filter').attr('data','showCus');
			  jQuery('body').find('.record-type-filter-def').show();
		    }
		    if(jQuery('.cost-code-filter select').val()) {
		      jQuery('.cost-code-filter').attr('data','showCus');
			  jQuery('body').find('.cost-code-filter-def').show();
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
    				 "dom": 'Rfrtlip',
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
	  if (urlajax.indexOf("/reseting/commit/ajax") === 0) {
	    var rowcount = jQuery('.dataTables_wrapper').length;
		var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
      	if(rowcount == 0 && rowCountTable > 2) {
    	  jQuery('table.m6connect-custom-program-table').DataTable({
            //"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
    		"bPaginate": false,
			"paging": false,
    		"aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
    		"searching": false,
    		"dom": 'Rfrtlip',
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
	  if (urlajax.indexOf("/get-total-number-of-data/") === 0) {
	    jQuery.unblockUI();
	  }
	  if (urlajax.indexOf("/get-next-page-data") === 0){
	     var getPagerId = jQuery('.datatable_page_id').val();
		 if(getPagerId) {
	  	   if(jQuery('.page_number_id').val() != 'drop') {
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
	jQuery('.pager-load-more-to').change(function (e) {	
	  var getPager = jQuery(this).val();
	  jQuery('.datatable_page_id').val(getPager);
	  jQuery('.page_number_id').val('drop');		
	  if(getPager) {
	    jQuery('.page-range-'+getPager).trigger('click');
	  }
	}); 
	}	
	// ==================================
	// End work for commitment page
	// Start work for spending forcast	
	else if(getPath == '/program/spending-forcast') {	  		  		
	  jQuery('.page__title').hide();
	  var spentFor = getUrlParameter('forecast');
	  if(spentFor) {	
	     jQuery('.spending-forecast-select').val(spentFor);
			 jQuery('#'+ spentFor).trigger('click');
	  }
	  else {
	    // By default triggering last saved forecast
	    var getLastForecast = jQuery('.spending-forecast-select option').last().val();	  
	    jQuery('.spending-forecast-select option').last().prop('selected',true);
	    if(getLastForecast && getLastForecast != 'None') {	     
          jQuery('#'+ getLastForecast).trigger('click');
        } 
	  }
	  jQuery('.commit-amt-quarter-one').trigger('keyup');	  
	  jQuery('.commit-amt-quarter-two').trigger('keyup');
	  jQuery('.commit-amt-quarter-three').trigger('keyup');	
	  jQuery('.commit-amt-quarter-fourth').trigger('keyup');
	  jQuery('.etc-amt-quarter-fourth-etc').trigger('keyup');
	  jQuery('.etc-amt-quarter-one-etc').trigger('keyup');	
	  jQuery('.etc-amt-quarter-two-etc').trigger('keyup');	
	  
	    
	  jQuery('.project_programe_spending_forcast_pro').change(function () {
	    jQuery('.commit-amt-quarter-one').trigger('keyup'); 
	    jQuery('.commit-amt-quarter-three').trigger('keyup');
		
		var getPreviousGrandTotal = 0;
	    getPreviousGrandTotal = jQuery('.previous-year-grand-total').text().replace(/[^\d\.\-]/g, '');
	    
		if(getPreviousGrandTotal != '') {
	      if(getPreviousGrandTotal < 0) {	
	        (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;">Previous Year Total :<span class="text-danger">'+format(getPreviousGrandTotal)+'</span></div>');
	      }
	      else {
	       (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;">Previous Year Total :'+format(getPreviousGrandTotal)+'</div>');
	     }
	   }		    
	  });
	  
	  var commitTblrows = jQuery(".m6connect-program-spending-forcast-main-table tbody tr");
	  commitTblrows.each(function (index) {
        var tblrowCommit = jQuery(this);
		tblrowCommit.find('.commit-amt-quarter-one').on('keyup', function () {		  
  		var firstQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
    	if(firstQuarter && firstQuarter != '-') {
	      /*var tillDateAmt = tblrowCommit.find('commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, '');
		  if(tillDateAmt) {
		    tillDateAmt = tillDateAmt;
		  }
		  else {
		    tillDateAmt = 0.00;
		  }
	      */
		  var etcAmt = tblrowCommit.find(".commit-amt").text();		  
		  var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
		  // Now get all the quarter values
		  
		  var getFistQuarterText = tblrowCommit.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, '');
		  getFistQuarterText = (getFistQuarterText)?getFistQuarterText:0.00;
		  var getFistQuarterAmt = tblrowCommit.find('.commit-amt-quarter-one').val().replace(/[^\d\.\-]/g, '');
		  getFistQuarterAmt = (getFistQuarterAmt)?getFistQuarterAmt:0.00;
		  var getSecQuarterText = tblrowCommit.find('.commit-amt-quarter-two-text').text().replace(/[^\d\.\-]/g, '');
		  getSecQuarterText = (getSecQuarterText)?getSecQuarterText:0.00;
		  var getSecQuarterAmt = tblrowCommit.find('.commit-amt-quarter-two').val().replace(/[^\d\.\-]/g, '');
		  getSecQuarterAmt = (getSecQuarterAmt)?getSecQuarterAmt:0.00;
		  var getThirdQuarterText = tblrowCommit.find('.commit-amt-quarter-three-text').text().replace(/[^\d\.\-]/g, '');		  
		  getThirdQuarterText = (getThirdQuarterText)?getThirdQuarterText:0.00;
		  var getThirdQuarterAmt = tblrowCommit.find('.commit-amt-quarter-three').val().replace(/[^\d\.\-]/g, '');		  
		  getThirdQuarterAmt = (getThirdQuarterAmt)?getThirdQuarterAmt:0.00;
		  var getFourthQuarterText = tblrowCommit.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, '');
		  getFourthQuarterText = (getFourthQuarterText)?getFourthQuarterText:0.00;
		  var getFourthQuarterAmt = tblrowCommit.find('.commit-amt-quarter-fourth').val().replace(/[^\d\.\-]/g, '');
		  getFourthQuarterAmt = (getFourthQuarterAmt)?getFourthQuarterAmt:0.00;
			
		  //var quarterTotal = parseFloat(firstQuarter) + parseFloat(getThirdQuarter) + parseFloat(tillDateAmt) + parseFloat(getSecQuarter) + parseFloat(getFourthQuarter);
		  var quarterTotal = parseFloat(firstQuarter) + parseFloat(getFistQuarterText) + parseFloat(getSecQuarterText) + parseFloat(getSecQuarterAmt) + parseFloat(getThirdQuarterText) + parseFloat(getFourthQuarterText) + parseFloat(getFourthQuarterAmt);
		  var totalFnl = (quarterTotal)?quarterTotal:0.00;
		  tblrowCommit.find('.commit-total-spent').text(format(totalFnl.toFixed(2)));
		  (quarterTotal < 0)?tblrowCommit.find('.commit-total-spent').addClass('text-danger'):tblrowCommit.find('.commit-total-spent').removeClass('text-danger');
		  var totalSpent = tblrowCommit.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, '');
		  //tblrowCommit.find('.commit-total-spent').trigger('keyup');		  
		  var beyondYear = tblrowCommit.find('.commit-beyond-year').val().replace(/[^\d\.\-]/g, '');			
		  var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear)));
		  var preYearSpending = tblrowCommit.find('.previous-year-spendings').text().replace(/[^\d\.\-]/g, '');
		  var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear) + parseFloat(preYearSpending)));
		  tblrowCommit.find('.commit-varience-total-calc').text(format(varience.toFixed(2)));
		  if(varience < 0) { tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger'); }
		  else { 
		  		tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger'); 
		  }
		  (varience < 0)?tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger'):tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger');
		  }
		  var grandTotal = 0;
	      jQuery(".commit-total-spent").each(function () {
	        var getTotalSpent = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stval = parseFloat(getTotalSpent);
	        grandTotal += isNaN(stval) ? 0 : stval;
	      }); 
		  (isNaN(grandTotal)) ? '' : jQuery('.commit-total-spent-total').text(format(grandTotal.toFixed(2)));			  
		  if(grandTotal < 0) {
			jQuery('.commit-total-spent-total').addClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending :<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-total-spent-total').removeClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending :'+format(grandTotal.toFixed(2))+'</div>');
		  }
		  
		  var beyondGrandTotal = 0;
	      jQuery(".commit-beyond-year").each(function () {
	        var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalBeyond = parseFloat(getTotalBeyond);
	        beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	      }); 
		  
	      (isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));
		  
		  var getEtcFuture = jQuery('.etc-beyond-year-total-etc').text().replace(/[^\d\.\-]/g, '');
		  var beyondGrandTotal = parseFloat(getEtcFuture) + parseFloat(beyondGrandTotal);
			
		  if(beyondGrandTotal < 0) {
			jQuery('.commit-beyond-year-total').addClass('text-danger');									
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		  }
		  
		  // Varience total
		  var varGrandTotal = 0;
	      jQuery(".commit-varience-total-calc").each(function () {
	        var getTotalVar = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalVar = parseFloat(getTotalVar);
	        varGrandTotal += isNaN(stvalVar) ? 0 : stvalVar;
	      }); 
		  
	      (isNaN(varGrandTotal)) ? '' : jQuery('.commit-varience-total-calc-total').text(format(varGrandTotal.toFixed(2)));			  
		  (varGrandTotal < 0)?jQuery('.commit-varience-total-calc-total').addClass('text-danger'):jQuery('.commit-varience-total-calc-total').removeClass('text-danger');
		  // ==================
		  var quarterOneTxt = 0;
		  jQuery(".commit-amt-quarter-one-text").each(function () {
	        var getQuarterOneTxt = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOneTxt);
	        quarterOneTxt += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 	
		  (isNaN(quarterOneTxt)) ? '' : jQuery('.quarter-one-grand-total').text(format(quarterOneTxt.toFixed(2)));  		  
		  
		  var quarterOneAmt = 0;
		  jQuery(".commit-amt-quarter-one").each(function () {
	        var getQuarterOneAmt = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOneAmt);
	        quarterOneAmt += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 	
		  (isNaN(quarterOneAmt)) ? '' : jQuery('.quarter-one-grand-total-input').text(format(quarterOneAmt.toFixed(2))); 
		  
		  var previousYear = 0;
	      jQuery(".previous-year-spendings").each(function () {
	        var getPreviousYearTotal = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalPrev = parseFloat(getPreviousYearTotal);
	        previousYear += isNaN(stvalPrev) ? 0 : stvalPrev;
	      }); 
		  var quarterOne = 0;
	      jQuery(".commit-amt-quarter-one").each(function () {
	        var getQuarterOne = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOne);
	        quarterOne += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 		  
		  var quarterTwo = 0;
	      jQuery(".commit-amt-quarter-two").each(function () {
	        var getQuarterTwo = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQTwo = parseFloat(getQuarterTwo);
	        quarterTwo += isNaN(stvalQTwo) ? 0 : stvalQTwo;
	      }); 		  
		  var quarterThreeText = 0;
	      jQuery(".commit-amt-quarter-three-text").each(function () {
	        var getQuarterThreeText = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQThreeText = parseFloat(getQuarterThreeText);
	        quarterThreeText += isNaN(stvalQThreeText) ? 0 : stvalQThreeText;
	      }); 		  		  
		  var quarterThree = 0;
	      jQuery(".commit-amt-quarter-three").each(function () {
	        var getQuarterThree = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQuatarThree = parseFloat(getQuarterThree);
	        quarterThree += isNaN(stvalQuatarThree) ? 0 : stvalQuatarThree;
	      }); 		  
		  var quarterFour = 0;
	      jQuery(".commit-amt-quarter-fourth").each(function () {
	        var getQuarterFour = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQFour = parseFloat(getQuarterFour);
	        quarterFour += isNaN(stvalQFour) ? 0 : stvalQFour;
	      }); 
		  var spentTodate = previousYear + quarterOne + quarterTwo + quarterThreeText + quarterThree + quarterFour;
		  if(spentTodate < 0) {		    
			(isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : <span class="text-danger">'+format(spentTodate.toFixed(2))+'</span></div>');
		  }
		  else {
		    (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : '+format(spentTodate.toFixed(2))+'</div>');
		  }
		  // PFC Calculation
	  	  var pfcCal = previousYear + grandTotal + beyondGrandTotal;
		  if(pfcCal < 0) {       
		  (isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : <span class="text-danger">'+format(pfcCal.toFixed(2))+'</span></div>');
		  }
		  else {
			(isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : '+format(pfcCal.toFixed(2))+'</div>');
		  }
		});
		
		tblrowCommit.find('.commit-amt-quarter-two').on('keyup', function () {
		  var secondQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  if(secondQuarter && secondQuarter != '-') {			
			var etcAmt = tblrowCommit.find(".commit-amt").text();		  
			var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');		  
			// Now get all the quarter values
			/*var getFistQuarterText = tblrowCommit.find('.commit-amt-quarter-one').val().replace(/[^\d\.\-]/g, '');
			var thirdQuarter = tblrowCommit.find('.commit-amt-quarter-three').val().replace(/[^\d\.\-]/g, '');
			var tillDateAmt = tblrowCommit.find('.commit-amt-quarter-three-text').text().replace(/[^\d\.\-]/g, '');
			if(tillDateAmt) { tillDateAmt = tillDateAmt; }
			else {
			  tillDateAmt = tblrowCommit.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, '');
			}
			
			var getFourthQuarterText = tblrowCommit.find('.commit-amt-quarter-fourth').val().replace(/[^\d\.\-]/g, '');*/
			
			
			var getFistQuarterText = tblrowCommit.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, '');
		    getFistQuarterText = (getFistQuarterText)?getFistQuarterText:0.00;
		    var getFistQuarterAmt = tblrowCommit.find('.commit-amt-quarter-one').val().replace(/[^\d\.\-]/g, '');
		    getFistQuarterAmt = (getFistQuarterAmt)?getFistQuarterAmt:0.00;
		    var getSecQuarterText = tblrowCommit.find('.commit-amt-quarter-two-text').text().replace(/[^\d\.\-]/g, '');
		    getSecQuarterText = (getSecQuarterText)?getSecQuarterText:0.00;
		    var getSecQuarterAmt = tblrowCommit.find('.commit-amt-quarter-two').val().replace(/[^\d\.\-]/g, '');
		    getSecQuarterAmt = (getSecQuarterAmt)?getSecQuarterAmt:0.00;
		    var getThirdQuarterText = tblrowCommit.find('.commit-amt-quarter-three-text').text().replace(/[^\d\.\-]/g, '');		  
		    getThirdQuarterText = (getThirdQuarterText)?getThirdQuarterText:0.00;
		    var getThirdQuarterAmt = tblrowCommit.find('.commit-amt-quarter-three').val().replace(/[^\d\.\-]/g, '');		  
		    getThirdQuarterAmt = (getThirdQuarterAmt)?getThirdQuarterAmt:0.00;
		    var getFourthQuarterText = tblrowCommit.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, '');
		    getFourthQuarterText = (getFourthQuarterText)?getFourthQuarterText:0.00;
			var getFourthQuarterAmt = tblrowCommit.find('.commit-amt-quarter-fourth').text().replace(/[^\d\.\-]/g, '');
		    getFourthQuarterAmt = (getFourthQuarterAmt)?getFourthQuarterAmt:0.00;
			
			//var quarterTotal = parseFloat(thirdQuarter) + parseFloat(tillDateAmt) + parseFloat(getFistQuarterText) + parseFloat(secondQuarter) + parseFloat(getFourthQuarterText);	
			var quarterTotal = parseFloat(secondQuarter) + parseFloat(getFistQuarterText) + parseFloat(getFistQuarterAmt) + parseFloat(getSecQuarterText) + parseFloat(getThirdQuarterText) + parseFloat(getThirdQuarterAmt) + parseFloat(getFourthQuarterText) + parseFloat(getFourthQuarterAmt);
			
			var totalFnl = (quarterTotal)?quarterTotal:0.00;
			tblrowCommit.find('.commit-total-spent').text(format(totalFnl.toFixed(2)));		  
			(quarterTotal < 0)?tblrowCommit.find('.commit-total-spent').addClass('text-danger'):tblrowCommit.find('.commit-total-spent').removeClass('text-danger');
			var totalSpent = tblrowCommit.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, '');
			//tblrowCommit.find('.commit-total-spent').trigger('keyup');		  
			var beyondYear = tblrowCommit.find('.commit-beyond-year').val().replace(/[^\d\.\-]/g, '');
			//var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear)));
		    var preYearSpending = tblrowCommit.find('.previous-year-spendings').text().replace(/[^\d\.\-]/g, '');
		    var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear) + parseFloat(preYearSpending)));
		    tblrowCommit.find('.commit-varience-total-calc').text(format(varience.toFixed(2)));		    
			(varience < 0)?tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger'):tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger');
			// Saving data in database first
			/*var projectId = jQuery('.project_programe_spending_forcast_pro').val();
			var commitId = tblrowCommit.find('.commit-number').attr('id');			
			jQuery.post( '/spending-forecast-data/three/'+ projectId+'/'+commitId+'/'+thirdQuarter+'/'+quarterTotal+'/'+varience, function( data ) { 
		      if(data.access == 0) {}
		     if(data.access == 1) {}		  
		    });*/
			// ===== End saving data  
		  }
		  var grandTotal = 0;
	      jQuery(".commit-total-spent").each(function () {
	        var getTotalSpent = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stval = parseFloat(getTotalSpent);
	        grandTotal += isNaN(stval) ? 0 : stval;
	      }); 
		  (isNaN(grandTotal)) ? '' : jQuery('.commit-total-spent-total').text(format(grandTotal.toFixed(2)));			  
		  if(grandTotal < 0) {
			jQuery('.commit-total-spent-total').addClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-total-spent-total').removeClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:'+format(grandTotal.toFixed(2))+'</div>');
		  }
		  
		  var beyondGrandTotal = 0;
	      jQuery(".commit-beyond-year").each(function () {
	        var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalBeyond = parseFloat(getTotalBeyond);
	        beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	      }); 
		  
	      (isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));		
		  var getEtcFuture = jQuery('.etc-beyond-year-total-etc').text().replace(/[^\d\.\-]/g, '');
		  var beyondGrandTotal = parseFloat(getEtcFuture) + parseFloat(beyondGrandTotal);	  
		  if(beyondGrandTotal < 0) {
			jQuery('.commit-beyond-year-total').addClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		  }
		  // Varience total
		  var varGrandTotal = 0;
	      jQuery(".commit-varience-total-calc").each(function () {
	        var getTotalVar = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalVar = parseFloat(getTotalVar);
	        varGrandTotal += isNaN(stvalVar) ? 0 : stvalVar;
	      }); 
		  
	      (isNaN(varGrandTotal)) ? '' : jQuery('.commit-varience-total-calc-total').text(format(varGrandTotal.toFixed(2)));			  
		  (varGrandTotal < 0)?jQuery('.commit-varience-total-calc-total').addClass('text-danger'):jQuery('.commit-varience-total-calc-total').removeClass('text-danger');
		  var previousYear = 0;
	      jQuery(".previous-year-spendings").each(function () {
	        var getPreviousYearTotal = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalPrev = parseFloat(getPreviousYearTotal);
	        previousYear += isNaN(stvalPrev) ? 0 : stvalPrev;
	      }); 
		  var quarterOne = 0;
	      jQuery(".commit-amt-quarter-one").each(function () {
	        var getQuarterOne = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOne);
	        quarterOne += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 		  
		  var quarterTwo = 0;
	      jQuery(".commit-amt-quarter-two").each(function () {
	        var getQuarterTwo = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQTwo = parseFloat(getQuarterTwo);
	        quarterTwo += isNaN(stvalQTwo) ? 0 : stvalQTwo;
	      }); 		  
		  var quarterThreeText = 0;
	      jQuery(".commit-amt-quarter-three-text").each(function () {
	        var getQuarterThreeText = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQThreeText = parseFloat(getQuarterThreeText);
	        quarterThreeText += isNaN(stvalQThreeText) ? 0 : stvalQThreeText;
	      }); 		  		  
		  var quarterThree = 0;
	      jQuery(".commit-amt-quarter-three").each(function () {
	        var getQuarterThree = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQuatarThree = parseFloat(getQuarterThree);
	        quarterThree += isNaN(stvalQuatarThree) ? 0 : stvalQuatarThree;
	      }); 		  
		  var quarterFour = 0;
	      jQuery(".commit-amt-quarter-fourth").each(function () {
	        var getQuarterFour = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQFour = parseFloat(getQuarterFour);
	        quarterFour += isNaN(stvalQFour) ? 0 : stvalQFour;
	      }); 
		  var spentTodate = previousYear + quarterOne + quarterTwo + quarterThreeText + quarterThree + quarterFour;
		  if(spentTodate < 0) {		    
			(isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : <span class="text-danger">'+format(spentTodate.toFixed(2))+'</span></div>');
		  }
		  else {
		    (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : '+format(spentTodate.toFixed(2))+'</div>');
		  }
		   // PFC Calculation
	  	  var pfcCal = previousYear + grandTotal + beyondGrandTotal;
		  if(pfcCal < 0) {       
		  (isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : <span class="text-danger">'+format(pfcCal.toFixed(2))+'</span></div>');
		  }
		  else {
			(isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : '+format(pfcCal.toFixed(2))+'</div>');
		  }
		  var quarterOneTxt = 0;
		  jQuery(".commit-amt-quarter-one-text").each(function () {
	        var getQuarterOneTxt = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOneTxt);
	        quarterOneTxt += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 	
		  (isNaN(quarterOneTxt)) ? '' : jQuery('.quarter-one-grand-total').text(format(quarterOneTxt.toFixed(2)));  		  
		  
		  var quarterOneAmt = 0;
		  jQuery(".commit-amt-quarter-one").each(function () {
	        var getQuarterOneAmt = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOneAmt);
	        quarterOneAmt += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 	
		  (isNaN(quarterOneAmt)) ? '' : jQuery('.quarter-one-grand-total-input').text(format(quarterOneAmt.toFixed(2))); 
		});		
		
		tblrowCommit.find('.commit-amt-quarter-three').on('keyup', function () {
		  var thirdQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  if(thirdQuarter && thirdQuarter != '-') {			
			var etcAmt = tblrowCommit.find(".commit-amt").text();		  
			var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');		  
			// Now get all the quarter values			
			var getFistQuarterText = tblrowCommit.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, '');
		    getFistQuarterText = (getFistQuarterText)?getFistQuarterText:0.00;
		    var getFistQuarterAmt = tblrowCommit.find('.commit-amt-quarter-one').val().replace(/[^\d\.\-]/g, '');
		    getFistQuarterAmt = (getFistQuarterAmt)?getFistQuarterAmt:0.00;
		    var getSecQuarterText = tblrowCommit.find('.commit-amt-quarter-two-text').text().replace(/[^\d\.\-]/g, '');
		    getSecQuarterText = (getSecQuarterText)?getSecQuarterText:0.00;
		    var getSecQuarterAmt = tblrowCommit.find('.commit-amt-quarter-two').val().replace(/[^\d\.\-]/g, '');
		    getSecQuarterAmt = (getSecQuarterAmt)?getSecQuarterAmt:0.00;
		    var getThirdQuarterText = tblrowCommit.find('.commit-amt-quarter-three-text').text().replace(/[^\d\.\-]/g, '');		  
		    getThirdQuarterText = (getThirdQuarterText)?getThirdQuarterText:0.00;
		    var getThirdQuarterAmt = tblrowCommit.find('.commit-amt-quarter-three').val().replace(/[^\d\.\-]/g, '');		  
		    getThirdQuarterAmt = (getThirdQuarterAmt)?getThirdQuarterAmt:0.00;
		    var getFourthQuarterText = tblrowCommit.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, '');
		    getFourthQuarterText = (getFourthQuarterText)?getFourthQuarterText:0.00;
			var getFourthQuarterAmt = tblrowCommit.find('.commit-amt-quarter-fourth').val().replace(/[^\d\.\-]/g, '');
		    getFourthQuarterAmt = (getFourthQuarterAmt)?getFourthQuarterAmt:0.00;
			var quarterTotal = parseFloat(thirdQuarter) + parseFloat(getFistQuarterText) + parseFloat(getFistQuarterAmt) + parseFloat(getSecQuarterText) + parseFloat(getSecQuarterAmt) + parseFloat(getThirdQuarterText) + parseFloat(getFourthQuarterText) + parseFloat(getFourthQuarterAmt);
			var totalFnl = (quarterTotal)?quarterTotal:0.00;			
			tblrowCommit.find('.commit-total-spent').text(format(totalFnl.toFixed(2)));		  
			(quarterTotal < 0)?tblrowCommit.find('.commit-total-spent').addClass('text-danger'):tblrowCommit.find('.commit-total-spent').removeClass('text-danger');
			var totalSpent = tblrowCommit.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, '');
			//tblrowCommit.find('.commit-total-spent').trigger('keyup');		  
			var beyondYear = tblrowCommit.find('.commit-beyond-year').val().replace(/[^\d\.\-]/g, '');
			var preYearSpending = tblrowCommit.find('.previous-year-spendings').text().replace(/[^\d\.\-]/g, '');				
			var totalSpending = tblrowCommit.find('.commit-invoice-amt').text().replace(/[^\d\.\-]/g, '');										
			var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear) + parseFloat(preYearSpending)));
			(varience < 0)?tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger'):tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger');
		  }
		  var grandTotal = 0;
	      jQuery(".commit-total-spent").each(function () {
	        var getTotalSpent = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stval = parseFloat(getTotalSpent);
	        grandTotal += isNaN(stval) ? 0 : stval;
	      }); 
		  (isNaN(grandTotal)) ? '' : jQuery('.commit-total-spent-total').text(format(grandTotal.toFixed(2)));			  
		  if(grandTotal < 0) {
			jQuery('.commit-total-spent-total').addClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-total-spent-total').removeClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:'+format(grandTotal.toFixed(2))+'</div>');
		  }
		  
		  var beyondGrandTotal = 0;
	      jQuery(".commit-beyond-year").each(function () {
	        var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalBeyond = parseFloat(getTotalBeyond);
	        beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	      }); 
		  
	      (isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));		
		  var getEtcFuture = jQuery('.etc-beyond-year-total-etc').text().replace(/[^\d\.\-]/g, '');
		  var beyondGrandTotal = parseFloat(getEtcFuture) + parseFloat(beyondGrandTotal);	  
		  if(beyondGrandTotal < 0) {
			jQuery('.commit-beyond-year-total').addClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		  }
		  // Varience total
		  var varGrandTotal = 0;
	      jQuery(".commit-varience-total-calc").each(function () {
	        var getTotalVar = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalVar = parseFloat(getTotalVar);
	        varGrandTotal += isNaN(stvalVar) ? 0 : stvalVar;
	      }); 
		  
	      (isNaN(varGrandTotal)) ? '' : jQuery('.commit-varience-total-calc-total').text(format(varGrandTotal.toFixed(2)));			  
		  (varGrandTotal < 0)?jQuery('.commit-varience-total-calc-total').addClass('text-danger'):jQuery('.commit-varience-total-calc-total').removeClass('text-danger');
		  var previousYear = 0;
	      jQuery(".previous-year-spendings").each(function () {
	        var getPreviousYearTotal = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalPrev = parseFloat(getPreviousYearTotal);
	        previousYear += isNaN(stvalPrev) ? 0 : stvalPrev;
	      }); 
		  var quarterOne = 0;
	      jQuery(".commit-amt-quarter-one").each(function () {
	        var getQuarterOne = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOne);
	        quarterOne += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 		  
		  var quarterTwo = 0;
	      jQuery(".commit-amt-quarter-two").each(function () {
	        var getQuarterTwo = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQTwo = parseFloat(getQuarterTwo);
	        quarterTwo += isNaN(stvalQTwo) ? 0 : stvalQTwo;
	      }); 		  
		  var quarterThreeText = 0;
	      jQuery(".commit-amt-quarter-three-text").each(function () {
	        var getQuarterThreeText = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQThreeText = parseFloat(getQuarterThreeText);
	        quarterThreeText += isNaN(stvalQThreeText) ? 0 : stvalQThreeText;
	      }); 		  		  
		  var quarterThree = 0;
	      jQuery(".commit-amt-quarter-three").each(function () {
	        var getQuarterThree = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQuatarThree = parseFloat(getQuarterThree);
	        quarterThree += isNaN(stvalQuatarThree) ? 0 : stvalQuatarThree;
	      }); 		  
		  var quarterFour = 0;
	      jQuery(".commit-amt-quarter-fourth").each(function () {
	        var getQuarterFour = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQFour = parseFloat(getQuarterFour);
	        quarterFour += isNaN(stvalQFour) ? 0 : stvalQFour;
	      }); 
		  var spentTodate = previousYear + quarterOne + quarterTwo + quarterThreeText + quarterThree + quarterFour;
		  if(spentTodate < 0) {		    
			(isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : <span class="text-danger">'+format(spentTodate.toFixed(2))+'</span></div>');
		  }
		  else {
		    (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : '+format(spentTodate.toFixed(2))+'</div>');
		  }
		   // PFC Calculation
	  	  var pfcCal = previousYear + grandTotal + beyondGrandTotal;
		  if(pfcCal < 0) {       
		  (isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : <span class="text-danger">'+format(pfcCal.toFixed(2))+'</span></div>');
		  }
		  else {
			(isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : '+format(pfcCal.toFixed(2))+'</div>');
		  }
		  var quarterOneTxt = 0;
		  jQuery(".commit-amt-quarter-one-text").each(function () {
	        var getQuarterOneTxt = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOneTxt);
	        quarterOneTxt += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 	
		  (isNaN(quarterOneTxt)) ? '' : jQuery('.quarter-one-grand-total').text(format(quarterOneTxt.toFixed(2)));  		  
		  
		  var quarterOneAmt = 0;
		  jQuery(".commit-amt-quarter-one").each(function () {
	        var getQuarterOneAmt = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalQOne = parseFloat(getQuarterOneAmt);
	        quarterOneAmt += isNaN(stvalQOne) ? 0 : stvalQOne;
	      }); 	
		  (isNaN(quarterOneAmt)) ? '' : jQuery('.quarter-one-grand-total-input').text(format(quarterOneAmt.toFixed(2))); 
		});		
 	    tblrowCommit.find('.commit-amt-quarter-fourth').on('keyup', function () {
		  var fourthQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  //if(fourthQuarter && fourthQuarter != '-') {
		    var etcAmt = tblrowCommit.find(".commit-amt").text();		  
		    var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
			var getFistQuarterText = tblrowCommit.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, '');
		    getFistQuarterText = (getFistQuarterText)?getFistQuarterText:0.00;
		    var getFistQuarterAmt = tblrowCommit.find('.commit-amt-quarter-one').val().replace(/[^\d\.\-]/g, '');
		    getFistQuarterAmt = (getFistQuarterAmt)?getFistQuarterAmt:0.00;
		    var getSecQuarterText = tblrowCommit.find('.commit-amt-quarter-two-text').text().replace(/[^\d\.\-]/g, '');
		    getSecQuarterText = (getSecQuarterText)?getSecQuarterText:0.00;
		    var getSecQuarterAmt = tblrowCommit.find('.commit-amt-quarter-two').val().replace(/[^\d\.\-]/g, '');
		    getSecQuarterAmt = (getSecQuarterAmt)?getSecQuarterAmt:0.00;
		    var getThirdQuarterText = tblrowCommit.find('.commit-amt-quarter-three-text').text().replace(/[^\d\.\-]/g, '');		  
		    getThirdQuarterText = (getThirdQuarterText)?getThirdQuarterText:0.00;
		    var getThirdQuarterAmt = tblrowCommit.find('.commit-amt-quarter-three').val().replace(/[^\d\.\-]/g, '');		  
		    getThirdQuarterAmt = (getThirdQuarterAmt)?getThirdQuarterAmt:0.00;
		    var getFourthQuarterText = tblrowCommit.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, '');
		    getFourthQuarterText = (getFourthQuarterText)?getFourthQuarterText:0.00;			
			var getFourthQuarter = fourthQuarter;
			var updateFrtQtr = '0';
			if(getFourthQuarter && getFourthQuarter != '-') { updateFrtQtr = getFourthQuarter; } else { updateFrtQtr = '0'; }
			
			var quarterTotal = parseFloat(updateFrtQtr) + parseFloat(getFistQuarterText) + parseFloat(getFistQuarterAmt) + parseFloat(getSecQuarterText) + parseFloat(getSecQuarterAmt) + parseFloat(getThirdQuarterText) + parseFloat(getThirdQuarterAmt) + parseFloat(getFourthQuarterText);
			
			var totalFnl = (quarterTotal)?quarterTotal:0.00;
			tblrowCommit.find('.commit-total-spent').text(format(totalFnl.toFixed(2)));		  
			(quarterTotal < 0)?tblrowCommit.find('.commit-total-spent').addClass('text-danger'):tblrowCommit.find('.commit-total-spent').removeClass('text-danger');
			var totalSpent = tblrowCommit.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, '');
			var beyondYear = tblrowCommit.find('.commit-beyond-year').val().replace(/[^\d\.\-]/g, '');		  
			
			var preYearSpending = tblrowCommit.find('.previous-year-spendings').text().replace(/[^\d\.\-]/g, '');				
			var totalSpending = tblrowCommit.find('.commit-invoice-amt').text().replace(/[^\d\.\-]/g, '');										
			var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear) + parseFloat(preYearSpending)));
			tblrowCommit.find('.commit-varience-total-calc').text(format(varience.toFixed(2)));
			if(varience < 0) { tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger'); }
			else { tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger'); }
		    var grandTotal = 0;
	        jQuery(".commit-total-spent").each(function () {
	          var getTotalSpent = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stval = parseFloat(getTotalSpent);
	          grandTotal += isNaN(stval) ? 0 : stval;
	        }); 
		    (isNaN(grandTotal)) ? '' : jQuery('.commit-total-spent-total').text(format(grandTotal.toFixed(2)));			  
		    if(grandTotal < 0) {
			  jQuery('.commit-total-spent-total').addClass('text-danger');
			  (isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
		    }
		    else {
		      jQuery('.commit-total-spent-total').removeClass('text-danger');
			  (isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:'+format(grandTotal.toFixed(2))+'</div>');
		    }
			var beyondGrandTotal = 0;
	        jQuery(".commit-beyond-year").each(function () {
	          var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalBeyond = parseFloat(getTotalBeyond);
	          beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	        });
			(isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));	
		    var getEtcFuture = jQuery('.etc-beyond-year-total-etc').text().replace(/[^\d\.\-]/g, '');
		    var beyondGrandTotal = parseFloat(getEtcFuture) + parseFloat(beyondGrandTotal);		  
		    if(beyondGrandTotal < 0) {
			  jQuery('.commit-beyond-year-total').addClass('text-danger');
			  (isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		    }
		    else {
		      jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		    }
		    // Varience total
		    var varGrandTotal = 0;
	        jQuery(".commit-varience-total-calc").each(function () {
	          var getTotalVar = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalVar = parseFloat(getTotalVar);
	          varGrandTotal += isNaN(stvalVar) ? 0 : stvalVar;
	        });
			(isNaN(varGrandTotal)) ? '' : jQuery('.commit-varience-total-calc-total').text(format(varGrandTotal.toFixed(2)));			  
		    (varGrandTotal < 0)?jQuery('.commit-varience-total-calc-total').addClass('text-danger'):jQuery('.commit-varience-total-calc-total').removeClass('text-danger');
		    var previousYear = 0;
	        jQuery(".previous-year-spendings").each(function () {
	          var getPreviousYearTotal = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalPrev = parseFloat(getPreviousYearTotal);
	          previousYear += isNaN(stvalPrev) ? 0 : stvalPrev;
	        }); 
		    var quarterOne = 0;
	        jQuery(".commit-amt-quarter-one").each(function () {
	          var getQuarterOne = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalQOne = parseFloat(getQuarterOne);
	          quarterOne += isNaN(stvalQOne) ? 0 : stvalQOne;
	        }); 	
		    (isNaN(quarterOne)) ? '' : jQuery('.quarter-one-grand-total').text(format(quarterOne.toFixed(2)));
			var quarterTwo = 0;
	        jQuery(".commit-amt-quarter-two").each(function () {
	          var getQuarterTwo = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalQTwo = parseFloat(getQuarterTwo);
	          quarterTwo += isNaN(stvalQTwo) ? 0 : stvalQTwo;
	        }); 		
		    (isNaN(quarterTwo)) ? '' : jQuery('.quarter-two-grand-total').text(format(quarterTwo.toFixed(2)));
			var quarterThreeText = 0;
	        jQuery(".commit-amt-quarter-three-text").each(function () {
	          var getQuarterThreeText = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalQThreeText = parseFloat(getQuarterThreeText);
	          quarterThreeText += isNaN(stvalQThreeText) ? 0 : stvalQThreeText;
	        });
			var quarterThree = 0;
	        jQuery(".commit-amt-quarter-three").each(function () {
	          var getQuarterThree = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalQuatarThree = parseFloat(getQuarterThree);
	          quarterThree += isNaN(stvalQuatarThree) ? 0 : stvalQuatarThree;
	        });
		    (isNaN(quarterThree)) ? '' : jQuery('.commit-amt-quarter-three-total').text(format(quarterThree.toFixed(2))); 
			var quarterFour = 0;		  
	        jQuery(".commit-amt-quarter-fourth").each(function () {
	          var getQuarterFour = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalQFour = parseFloat(getQuarterFour);
	          quarterFour += isNaN(stvalQFour) ? 0 : stvalQFour;
	        }); 
		    (isNaN(quarterFour)) ? '' : jQuery('.commit-amt-quarter-fourth-total').text(format(quarterFour.toFixed(2)));
			var quarterFourInput = 0;		  
	        jQuery(".commit-amt-quarter-fourth").each(function () {
	          var getQuarterFourIn = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalQFourIn = parseFloat(getQuarterFourIn);
	          quarterFourInput += isNaN(stvalQFourIn) ? 0 : stvalQFourIn;
	        }); 
		    (isNaN(quarterFourInput)) ? '' : jQuery('.commit-amt-quarter-fourth-input').text(format(quarterFourInput.toFixed(2)));
			var spentTodate = previousYear + quarterOne + quarterTwo + quarterThreeText + quarterThree + quarterFour;
		    if(spentTodate < 0) {		    
			  (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : <span class="text-danger">'+format(spentTodate.toFixed(2))+'</span></div>'); 
			}
			else {
		      (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:4px solid #fff;">Forecast : '+format(spentTodate.toFixed(2))+'</div>');
		    } 
			 // PFC Calculation
	  	  var pfcCal = previousYear + grandTotal + beyondGrandTotal;
		  if(pfcCal < 0) {       
		  (isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : <span class="text-danger">'+format(pfcCal.toFixed(2))+'</span></div>');
		  }
		  else {
			(isNaN(pfcCal)) ? '' : jQuery('#project-final-cost-container').html('<div class="form-control" style="border-radius:0">Projected final cost : '+format(pfcCal.toFixed(2))+'</div>');
		  }
		    var quarterOneTxt = 0;
		    jQuery(".commit-amt-quarter-one-text").each(function () {
	          var getQuarterOneTxt = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalQOne = parseFloat(getQuarterOneTxt);
	          quarterOneTxt += isNaN(stvalQOne) ? 0 : stvalQOne;
	        }); 	
		    (isNaN(quarterOneTxt)) ? '' : jQuery('.quarter-one-grand-total').text(format(quarterOneTxt.toFixed(2)));
			var quarterOneAmt = 0;
		    jQuery(".commit-amt-quarter-one").each(function () {
	          var getQuarterOneAmt = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalQOne = parseFloat(getQuarterOneAmt);
	          quarterOneAmt += isNaN(stvalQOne) ? 0 : stvalQOne;
	        }); 	
		    (isNaN(quarterOneAmt)) ? '' : jQuery('.quarter-one-grand-total-input').text(format(quarterOneAmt.toFixed(2))); 		  
		  });		
		tblrowCommit.find('.commit-beyond-year').on('keyup', function () {		  
			var beyondYear = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		    var etcAmt = tblrowCommit.find(".commit-amt").text();		  
		    var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
			var getFistQuarter = tblrowCommit.find('.commit-amt-quarter-one').val().replace(/[^\d\.\-]/g, '');			
			var getSecQuarter = tblrowCommit.find('.commit-amt-quarter-two').val().replace(/[^\d\.\-]/g, '');			
			var getThirdQuarter = tblrowCommit.find('.commit-amt-quarter-three').val().replace(/[^\d\.\-]/g, '');			
			var tillDateAmt = tblrowCommit.find('.commit-amt-quarter-fourth').val().replace(/[^\d\.\-]/g, '');
			var getFourthQuarter = tblrowCommit.find('.commit-amt-quarter-fourth').val().replace(/[^\d\.\-]/g, '');
			
			var beyondYearTotal = beyondYear;
			var updateBeyTotal = '0';
			if(beyondYearTotal && beyondYearTotal != '-') {
			  updateBeyTotal = beyondYearTotal;
			}
			else {
			  updateBeyTotal = '0';
			}
			//var quarterTotal = parseFloat(getThirdQuarter) + parseFloat(tillDateAmt) + parseFloat(getFistQuarter) + parseFloat(getSecQuarter) + parseFloat(getFourthQuarter) + parseFloat(updateBeyTotal);
			var quarterTotal = parseFloat(getFistQuarter) + parseFloat(getSecQuarter) + parseFloat(getThirdQuarter) + parseFloat(getFourthQuarter) + parseFloat(tillDateAmt);
			
			var preYearSpending = tblrowCommit.find('.previous-year-spendings').text().replace(/[^\d\.\-]/g, '');				
			var totalSpending = tblrowCommit.find('.commit-invoice-amt').text().replace(/[^\d\.\-]/g, '');
			
			var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(preYearSpending)));
			var updateVar = parseFloat(varience) - parseFloat(updateBeyTotal);			
			tblrowCommit.find('.commit-varience-total-calc').text(format(updateVar.toFixed(2)));
			if(updateVar < 0) {
			  tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger');
			}
			else {
			  tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger');
			}
		  /****************************************************************************************************/
		   var grandTotal = 0;
	      jQuery(".commit-total-spent").each(function () {
	        var getTotalSpent = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stval = parseFloat(getTotalSpent);
	        grandTotal += isNaN(stval) ? 0 : stval;
	      }); 
		  (isNaN(grandTotal)) ? '' : jQuery('.commit-total-spent-total').text(format(grandTotal.toFixed(2)));			  
		  if(grandTotal < 0) {
			jQuery('.commit-total-spent-total').addClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-total-spent-total').removeClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:'+format(grandTotal.toFixed(2))+'</div>');
		  }
		  
		  var beyondGrandTotal = 0;
	      jQuery(".commit-beyond-year").each(function () {
	        var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalBeyond = parseFloat(getTotalBeyond);
	        beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	      }); 
		  
	      (isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));	
		  var getEtcFuture = jQuery('.etc-beyond-year-total-etc').text().replace(/[^\d\.\-]/g, '');
		  var beyondGrandTotal = parseFloat(getEtcFuture) + parseFloat(beyondGrandTotal);		  
		  if(beyondGrandTotal < 0) {
			jQuery('.commit-beyond-year-total').addClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		  }
		  // Varience total
		  var varGrandTotal = 0;
	      jQuery(".commit-varience-total-calc").each(function () {
	        var getTotalVar = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	        var stvalVar = parseFloat(getTotalVar);
	        varGrandTotal += isNaN(stvalVar) ? 0 : stvalVar;
	      }); 
		  
	      (isNaN(varGrandTotal)) ? '' : jQuery('.commit-varience-total-calc-total').text(format(varGrandTotal.toFixed(2)));			  
		  (varGrandTotal < 0)?jQuery('.commit-varience-total-calc-total').addClass('text-danger'):jQuery('.commit-varience-total-calc-total').removeClass('text-danger');
		});
	  });
	  var tblrows = jQuery(".m6connect-program-spending-forcast-main-table-etc tbody tr");	  
	  jQuery('.etc-amt-quarter-three-etc').trigger('keyup');
	  tblrows.each(function (index) {
        var tblrow = jQuery(this);
		tblrow.find('.etc-amt-quarter-one-etc').on('keyup', function () {
		  var firstQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  var q1 = '0';
		  if(firstQuarter && firstQuarter != '-') {  q1 = firstQuarter; }
		  var etcAmt = tblrow.find(".etc-amt").text();		  
		  var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
		  // Now get all the quarter values
		  var getFistQuarterAmt = q1;
		  var getSecQuarterAmt = tblrow.find('.etc-amt-quarter-two-etc').val().replace(/[^\d\.\-]/g, '');
		  var getThirdQuarterAmt = tblrow.find('.etc-amt-quarter-three-etc').val().replace(/[^\d\.\-]/g, '');
		  var getFourthQuarterAmt = tblrow.find('.etc-amt-quarter-fourth-etc').val().replace(/[^\d\.\-]/g, '');
		  var quarterTotal = parseFloat(getFistQuarterAmt) + parseFloat(getSecQuarterAmt) + parseFloat(getThirdQuarterAmt) + parseFloat(getFourthQuarterAmt);		
		  var totalFnl = (quarterTotal)?quarterTotal:0.00;
		  tblrow.find('.etc-total-spent').text(format(totalFnl.toFixed(2)));
		  var totalSpent = tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, '');
		  var beyondYear = tblrow.find('.etc-beyond-year').val().replace(/[^\d\.\-]/g, '');		  
		  var varience = parseFloat(etcAmtCal) - (parseFloat(quarterTotal) + parseFloat(beyondYear));
		  tblrow.find('.varience-total-calc').text(format(varience.toFixed(2)));			
		  (varience < 0)?tblrow.find('.varience-total-calc').addClass('text-danger'):tblrow.find('.varience-total-calc').removeClass('text-danger');
		  var previousYearTotal = 0; 
		  jQuery(".previous-year-etc").each(function () {
		    var getPrevVal = jQuery(this).val();	
			var stPrevVal = parseFloat(getPrevVal.replace(/[^\d\.\-]/g, ''));
			previousYearTotal += isNaN(stPrevVal) ? 0 : stPrevVal;
		  });					 
		  (isNaN(previousYearTotal)) ? '' : jQuery('.previous-year-grand-total-etc').text(format(previousYearTotal.toFixed(2)));
		  (previousYearTotal < 0)?jQuery('.previous-year-grand-total-etc').addClass('text-danger'):jQuery('.previous-year-grand-total-etc').removeClass('text-danger');
		  var quarterOneTotal = 0;
		  jQuery(".etc-amt-quarter-one-etc").each(function () {
		    var getQOneVal = jQuery(this).val();	
			var stQoneVal = parseFloat(getQOneVal.replace(/[^\d\.\-]/g, ''));
			quarterOneTotal += isNaN(stQoneVal) ? 0 : stQoneVal;
		  });					 
		  (isNaN(quarterOneTotal)) ? '' : jQuery('.quarter-one-grand-total-etc').text(format(quarterOneTotal.toFixed(2)));		
		  (quarterOneTotal < 0)?jQuery('.quarter-one-grand-total-etc').addClass('text-danger'):jQuery('.quarter-one-grand-total-etc').removeClass('text-danger');
		  var quarterTwoTotal = 0;
		  jQuery(".etc-amt-quarter-two-etc").each(function () {
		    var getqTwoVal = jQuery(this).val();	
			var stQTwoVal = parseFloat(getqTwoVal.replace(/[^\d\.\-]/g, ''));
			quarterTwoTotal += isNaN(stQTwoVal) ? 0 : stQTwoVal;
		  });
		  (isNaN(quarterTwoTotal)) ? '' : jQuery('.quarter-two-grand-total-etc').text(format(quarterTwoTotal.toFixed(2)));
		  (quarterTwoTotal < 0)?jQuery('.quarter-two-grand-total-etc').addClass('text-danger'):jQuery('.quarter-two-grand-total-etc').removeClass('text-danger');
		  var grandTotalThree = 0;
		  jQuery(".etc-amt-quarter-three-etc").each(function () {
		    var getVal = jQuery(this).val();	
			var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
			grandTotalThree += isNaN(stval) ? 0 : stval;
		  });
		  (isNaN(grandTotalThree)) ? '' : jQuery('.etc-amt-quarter-three-total-etc').text(format(grandTotalThree.toFixed(2)));		
		  (grandTotalThree < 0)?jQuery('.etc-amt-quarter-three-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-three-total-etc').removeClass('text-danger');
		  var grandTotalFour = 0;
		  jQuery(".etc-amt-quarter-fourth-etc").each(function () {
		    var getFrthVal = jQuery(this).val();	
			var stFrthval = parseFloat(getFrthVal.replace(/[^\d\.\-]/g, ''));
			grandTotalFour += isNaN(stFrthval) ? 0 : stFrthval;
		  });
		  (isNaN(grandTotalFour)) ? '' : jQuery('.etc-amt-quarter-fourth-total-etc').text(format(grandTotalFour.toFixed(2)));
		  (grandTotalFour < 0)?jQuery('.etc-amt-quarter-fourth-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-fourth-total-etc').removeClass('text-danger');
		  var currentYearTotal = 0;
		  jQuery(".etc-total-spent").each(function () {
		    var currentYear = jQuery(this).text();	
			var stcurrentYear = parseFloat(currentYear.replace(/[^\d\.\-]/g, ''));
			currentYearTotal += isNaN(stcurrentYear) ? 0 : stcurrentYear;
		  });
		  (isNaN(currentYearTotal)) ? '' : jQuery('.etc-total-spent-total').text(format(currentYearTotal.toFixed(2)));
		  (currentYearTotal < 0)?tblrow.find('.etc-total-spent-total').addClass('text-danger'):tblrow.find('.etc-total-spent-total').removeClass('text-danger');
		  var getAmtSpent = jQuery('#commitment-current-year div').text();
		  var getVal = getAmtSpent.split('$');
		  var finalAmt = parseFloat(getVal[1].replace(/[^\d\.\-]/g, ''));
		  var newAmt = (currentYearTotal + finalAmt);
		  jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending :'+format(newAmt.toFixed(2))+'</div>');
		  var futureYearTotal = 0;
		  jQuery(".etc-beyond-year").each(function () {
		    var beyondYear = jQuery(this).text();	
			var stbeyondYear = parseFloat(beyondYear.replace(/[^\d\.\-]/g, ''));
			futureYearTotal += isNaN(stbeyondYear) ? 0 : stbeyondYear;
		  });
		  (isNaN(futureYearTotal)) ? '' : jQuery('.etc-beyond-year-total-etc').text(format(futureYearTotal.toFixed(2)));
		  (futureYearTotal < 0)?tblrow.find('.etc-beyond-year-total-etc').addClass('text-danger'):tblrow.find('.etc-beyond-year-total-etc').removeClass('text-danger');
		  var getCommitFuture = jQuery('.commit-beyond-year-total').text().replace(/[^\d\.\-]/g, '');
		  var updateFuture = parseFloat(getCommitFuture) + parseFloat(futureYearTotal);
		  if(updateFuture < 0) {
	        jQuery('.commit-beyond-year-total').addClass('text-danger');
			(isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(updateFuture.toFixed(2))+'</span></div>');
		  }
		  else { 
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(updateFuture.toFixed(2))+'</div>');
		  }
		  var getAmtFut = jQuery('#commitment-beyond-next-year div').text();
		  var getValFut = getAmtFut.split('$');
		  var finalAmtFut = parseFloat(getValFut[1].replace(/[^\d\.\-]/g, ''));
		  var newAmtFut = (futureYearTotal + finalAmtFut);						
		  (isNaN(newAmtFut)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total :'+format(newAmtFut.toFixed(2))+'</div>');
		  var varienceTotal = 0;
		  jQuery(".varience-total-calc").each(function () {
		    var varienceYear = jQuery(this).text();	
			var stvarienceYear = parseFloat(varienceYear.replace(/[^\d\.\-]/g, ''));
			varienceTotal += isNaN(stvarienceYear) ? 0 : stvarienceYear;
		  });
		  (isNaN(varienceTotal)) ? '' : jQuery('.etc-varience-total-calc-total').text(format(varienceTotal.toFixed(2)));
		  (varienceTotal < 0)?tblrow.find('.etc-varience-total-calc-total').addClass('text-danger'):tblrow.find('.etc-varience-total-calc-total').removeClass('text-danger');
		});
		tblrow.find('.etc-amt-quarter-two-etc').on('keyup', function () {
		  var secondQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  var q2 = '0';
		  if(secondQuarter && secondQuarter != '-') {
		    q2 = secondQuarter;
		  }
		  var etcAmt = tblrow.find(".etc-amt").text();		  
		  var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');						
		  // Now get all the quarter values
		  var getFistQuarterAmt = tblrow.find('.etc-amt-quarter-one-etc').val().replace(/[^\d\.\-]/g, '');
		  var getSecQuarterAmt = q2;
		  var getThirdQuarterAmt = tblrow.find('.etc-amt-quarter-three-etc').val().replace(/[^\d\.\-]/g, '');
		  var getFourthQuarterAmt = tblrow.find('.etc-amt-quarter-fourth-etc').val().replace(/[^\d\.\-]/g, '');
		  
		  var quarterTotal = parseFloat(getFistQuarterAmt) + parseFloat(getSecQuarterAmt) + parseFloat(getThirdQuarterAmt) + parseFloat(getFourthQuarterAmt);		
		  var totalFnl = (quarterTotal)?quarterTotal:0.00;
		  tblrow.find('.etc-total-spent').text(format(totalFnl.toFixed(2)));
		  var totalSpent = tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, '');
		  var beyondYear = tblrow.find('.etc-beyond-year').val().replace(/[^\d\.\-]/g, '');		  
		  var varience = parseFloat(etcAmtCal) - (parseFloat(quarterTotal) + parseFloat(beyondYear));
		  tblrow.find('.varience-total-calc').text(format(varience.toFixed(2)));			
		  (varience < 0)?tblrow.find('.varience-total-calc').addClass('text-danger'):tblrow.find('.varience-total-calc').removeClass('text-danger');
			
			var previousYearTotal = 0;
			jQuery(".previous-year-etc").each(function () {
			  var getPrevVal = jQuery(this).val();	
			  var stPrevVal = parseFloat(getPrevVal.replace(/[^\d\.\-]/g, ''));
			  previousYearTotal += isNaN(stPrevVal) ? 0 : stPrevVal;
			});					 
		    (isNaN(previousYearTotal)) ? '' : jQuery('.previous-year-grand-total-etc').text(format(previousYearTotal.toFixed(2)));		
			(previousYearTotal < 0)?jQuery('.previous-year-grand-total-etc').addClass('text-danger'):jQuery('.previous-year-grand-total-etc').removeClass('text-danger');
			
			var quarterOneTotal = 0;
			jQuery(".etc-amt-quarter-one-etc").each(function () {
			  var getQOneVal = jQuery(this).val();	
			  var stQoneVal = parseFloat(getQOneVal.replace(/[^\d\.\-]/g, ''));
			  quarterOneTotal += isNaN(stQoneVal) ? 0 : stQoneVal;
			});					 
		    (isNaN(quarterOneTotal)) ? '' : jQuery('.quarter-one-grand-total-etc').text(format(quarterOneTotal.toFixed(2)));		
			(quarterOneTotal < 0)?jQuery('.quarter-one-grand-total-etc').addClass('text-danger'):jQuery('.quarter-one-grand-total-etc').removeClass('text-danger');
			
			var quarterTwoTotal = 0;
			jQuery(".etc-amt-quarter-two-etc").each(function () {
			  var getqTwoVal = jQuery(this).val();	
			  var stQTwoVal = parseFloat(getqTwoVal.replace(/[^\d\.\-]/g, ''));
			  quarterTwoTotal += isNaN(stQTwoVal) ? 0 : stQTwoVal;
			});					 
		    (isNaN(quarterTwoTotal)) ? '' : jQuery('.quarter-two-grand-total-etc').text(format(quarterTwoTotal.toFixed(2)));		
			(quarterTwoTotal < 0)?jQuery('.quarter-two-grand-total-etc').addClass('text-danger'):jQuery('.quarter-two-grand-total-etc').removeClass('text-danger');
			
			var grandTotalThree = 0;
			jQuery(".etc-amt-quarter-three-etc").each(function () {
			  var getVal = jQuery(this).val();	
			  var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
			  grandTotalThree += isNaN(stval) ? 0 : stval;
			});					 
		    (isNaN(grandTotalThree)) ? '' : jQuery('.etc-amt-quarter-three-total-etc').text(format(grandTotalThree.toFixed(2)));		
			(grandTotalThree < 0)?jQuery('.etc-amt-quarter-three-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-three-total-etc').removeClass('text-danger');
			
			var grandTotalFour = 0;
			jQuery(".etc-amt-quarter-fourth-etc").each(function () {
			  var getFrthVal = jQuery(this).val();	
			  var stFrthval = parseFloat(getFrthVal.replace(/[^\d\.\-]/g, ''));
			  grandTotalFour += isNaN(stFrthval) ? 0 : stFrthval;
			});					 
		    (isNaN(grandTotalFour)) ? '' : jQuery('.etc-amt-quarter-fourth-total-etc').text(format(grandTotalFour.toFixed(2)));		
			(grandTotalFour < 0)?jQuery('.etc-amt-quarter-fourth-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-fourth-total-etc').removeClass('text-danger');
			
			var currentYearTotal = 0;
			jQuery(".etc-total-spent").each(function () {
			  var currentYear = jQuery(this).text();	
			  var stcurrentYear = parseFloat(currentYear.replace(/[^\d\.\-]/g, ''));
			  currentYearTotal += isNaN(stcurrentYear) ? 0 : stcurrentYear;
			});
			(isNaN(currentYearTotal)) ? '' : jQuery('.etc-total-spent-total').text(format(currentYearTotal.toFixed(2)));		
			(currentYearTotal < 0)?tblrow.find('.etc-total-spent-total').addClass('text-danger'):tblrow.find('.etc-total-spent-total').removeClass('text-danger');
			var getAmtSpent = jQuery('#commitment-current-year div').text();
			var getVal = getAmtSpent.split('$');
			var finalAmt = parseFloat(getVal[1].replace(/[^\d\.\-]/g, ''));
			var newAmt = (currentYearTotal + finalAmt);
			jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending :'+format(newAmt.toFixed(2))+'</div>');
			
			var futureYearTotal = 0;
			jQuery(".etc-beyond-year").each(function () {
			  var beyondYear = jQuery(this).text();	
			  var stbeyondYear = parseFloat(beyondYear.replace(/[^\d\.\-]/g, ''));
			  futureYearTotal += isNaN(stbeyondYear) ? 0 : stbeyondYear;
			});
			(isNaN(futureYearTotal)) ? '' : jQuery('.etc-beyond-year-total-etc').text(format(futureYearTotal.toFixed(2)));		
			(futureYearTotal < 0)?tblrow.find('.etc-beyond-year-total-etc').addClass('text-danger'):tblrow.find('.etc-beyond-year-total-etc').removeClass('text-danger');
			
			var getCommitFuture = jQuery('.commit-beyond-year-total').text().replace(/[^\d\.\-]/g, '');
			var updateFuture = parseFloat(getCommitFuture) + parseFloat(futureYearTotal);
			if(updateFuture < 0) {
			  jQuery('.commit-beyond-year-total').addClass('text-danger');
			  (isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(updateFuture.toFixed(2))+'</span></div>');
		    }
		    else {
		      jQuery('.commit-beyond-year-total').removeClass('text-danger');
			  (isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(updateFuture.toFixed(2))+'</div>');
		    }			
			var getAmtFut = jQuery('#commitment-beyond-next-year div').text();
			var getValFut = getAmtFut.split('$');
			var finalAmtFut = parseFloat(getValFut[1].replace(/[^\d\.\-]/g, ''));
			var newAmtFut = (futureYearTotal + finalAmtFut);						
			(isNaN(newAmtFut)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total :'+format(newAmtFut.toFixed(2))+'</div>');
			
			var varienceTotal = 0;
			jQuery(".varience-total-calc").each(function () {
			  var varienceYear = jQuery(this).text();	
			  var stvarienceYear = parseFloat(varienceYear.replace(/[^\d\.\-]/g, ''));
			  varienceTotal += isNaN(stvarienceYear) ? 0 : stvarienceYear;
			});
			(isNaN(varienceTotal)) ? '' : jQuery('.etc-varience-total-calc-total').text(format(varienceTotal.toFixed(2)));		
			(varienceTotal < 0)?tblrow.find('.etc-varience-total-calc-total').addClass('text-danger'):tblrow.find('.etc-varience-total-calc-total').removeClass('text-danger');		
			
			
		  
		});
		
		tblrow.find('.etc-amt-quarter-three-etc').on('keyup', function () {
		  var thirdQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  var q3 = '0';
		  if(thirdQuarter && thirdQuarter != '-') {
		    q3 = thirdQuarter;
		  }
		  var etcAmt = tblrow.find(".etc-amt").text();		  
		  var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
		  // Now get all the quarter values
		  var getFistQuarterAmt = tblrow.find('.etc-amt-quarter-one-etc').val().replace(/[^\d\.\-]/g, '');
		  var getSecQuarterAmt = tblrow.find('.etc-amt-quarter-two-etc').val().replace(/[^\d\.\-]/g, '');
		  var getThirdQuarterAmt = q3;
		  var getFourthQuarterAmt = tblrow.find('.etc-amt-quarter-fourth-etc').val().replace(/[^\d\.\-]/g, '');		  
		  var quarterTotal = parseFloat(getFistQuarterAmt) + parseFloat(getSecQuarterAmt) + parseFloat(getThirdQuarterAmt) + parseFloat(getFourthQuarterAmt);		
		  var totalFnl = (quarterTotal)?quarterTotal:0.00;
		  tblrow.find('.etc-total-spent').text(format(totalFnl.toFixed(2)));
		  var totalSpent = tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, '');
		  var beyondYear = tblrow.find('.etc-beyond-year').val().replace(/[^\d\.\-]/g, '');		  
		  var varience = parseFloat(etcAmtCal) - (parseFloat(quarterTotal) + parseFloat(beyondYear));
		  tblrow.find('.varience-total-calc').text(format(varience.toFixed(2)));			
		  (varience < 0)?tblrow.find('.varience-total-calc').addClass('text-danger'):tblrow.find('.varience-total-calc').removeClass('text-danger');
		  var previousYearTotal = 0;
		  jQuery(".previous-year-etc").each(function () {
			  var getPrevVal = jQuery(this).val();	
			  var stPrevVal = parseFloat(getPrevVal.replace(/[^\d\.\-]/g, ''));
			  previousYearTotal += isNaN(stPrevVal) ? 0 : stPrevVal;
			});					 
		    (isNaN(previousYearTotal)) ? '' : jQuery('.previous-year-grand-total-etc').text(format(previousYearTotal.toFixed(2)));		
			(previousYearTotal < 0)?jQuery('.previous-year-grand-total-etc').addClass('text-danger'):jQuery('.previous-year-grand-total-etc').removeClass('text-danger');
			
			var quarterOneTotal = 0;
			jQuery(".etc-amt-quarter-one-etc").each(function () {
			  var getQOneVal = jQuery(this).val();	
			  var stQoneVal = parseFloat(getQOneVal.replace(/[^\d\.\-]/g, ''));
			  quarterOneTotal += isNaN(stQoneVal) ? 0 : stQoneVal;
			});					 
		    (isNaN(quarterOneTotal)) ? '' : jQuery('.quarter-one-grand-total-etc').text(format(quarterOneTotal.toFixed(2)));		
			(quarterOneTotal < 0)?jQuery('.quarter-one-grand-total-etc').addClass('text-danger'):jQuery('.quarter-one-grand-total-etc').removeClass('text-danger');
			
			var quarterTwoTotal = 0;
			jQuery(".etc-amt-quarter-two-etc").each(function () {
			  var getqTwoVal = jQuery(this).val();	
			  var stQTwoVal = parseFloat(getqTwoVal.replace(/[^\d\.\-]/g, ''));
			  quarterTwoTotal += isNaN(stQTwoVal) ? 0 : stQTwoVal;
			});					 
		    (isNaN(quarterTwoTotal)) ? '' : jQuery('.quarter-two-grand-total-etc').text(format(quarterTwoTotal.toFixed(2)));		
			(quarterTwoTotal < 0)?jQuery('.quarter-two-grand-total-etc').addClass('text-danger'):jQuery('.quarter-two-grand-total-etc').removeClass('text-danger');
			
			var grandTotalThree = 0;
			jQuery(".etc-amt-quarter-three-etc").each(function () {
			  var getVal = jQuery(this).val();	
			  var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
			  grandTotalThree += isNaN(stval) ? 0 : stval;
			});					 
		    (isNaN(grandTotalThree)) ? '' : jQuery('.etc-amt-quarter-three-total-etc').text(format(grandTotalThree.toFixed(2)));		
			(grandTotalThree < 0)?jQuery('.etc-amt-quarter-three-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-three-total-etc').removeClass('text-danger');
			
			var grandTotalFour = 0;
			jQuery(".etc-amt-quarter-fourth-etc").each(function () {
			  var getFrthVal = jQuery(this).val();	
			  var stFrthval = parseFloat(getFrthVal.replace(/[^\d\.\-]/g, ''));
			  grandTotalFour += isNaN(stFrthval) ? 0 : stFrthval;
			});					 
		    (isNaN(grandTotalFour)) ? '' : jQuery('.etc-amt-quarter-fourth-total-etc').text(format(grandTotalFour.toFixed(2)));		
			(grandTotalFour < 0)?jQuery('.etc-amt-quarter-fourth-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-fourth-total-etc').removeClass('text-danger');
			
			var currentYearTotal = 0;
			jQuery(".etc-total-spent").each(function () {
			  var currentYear = jQuery(this).text();	
			  var stcurrentYear = parseFloat(currentYear.replace(/[^\d\.\-]/g, ''));
			  currentYearTotal += isNaN(stcurrentYear) ? 0 : stcurrentYear;
			});
			(isNaN(currentYearTotal)) ? '' : jQuery('.etc-total-spent-total').text(format(currentYearTotal.toFixed(2)));		
			(currentYearTotal < 0)?tblrow.find('.etc-total-spent-total').addClass('text-danger'):tblrow.find('.etc-total-spent-total').removeClass('text-danger');
			var getAmtSpent = jQuery('#commitment-current-year div').text();
			var getVal = getAmtSpent.split('$');
			var finalAmt = parseFloat(getVal[1].replace(/[^\d\.\-]/g, ''));
			var newAmt = (currentYearTotal + finalAmt);
			jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending :'+format(newAmt.toFixed(2))+'</div>');
			
			var futureYearTotal = 0;
			jQuery(".etc-beyond-year").each(function () {
			  var beyondYear = jQuery(this).text();	
			  var stbeyondYear = parseFloat(beyondYear.replace(/[^\d\.\-]/g, ''));
			  futureYearTotal += isNaN(stbeyondYear) ? 0 : stbeyondYear;
			});
			(isNaN(futureYearTotal)) ? '' : jQuery('.etc-beyond-year-total-etc').text(format(futureYearTotal.toFixed(2)));		
			(futureYearTotal < 0)?tblrow.find('.etc-beyond-year-total-etc').addClass('text-danger'):tblrow.find('.etc-beyond-year-total-etc').removeClass('text-danger');
			
			var getCommitFuture = jQuery('.commit-beyond-year-total').text().replace(/[^\d\.\-]/g, '');
			var updateFuture = parseFloat(getCommitFuture) + parseFloat(futureYearTotal);
			if(updateFuture < 0) {
			  jQuery('.commit-beyond-year-total').addClass('text-danger');
			  (isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(updateFuture.toFixed(2))+'</span></div>');
		    }
		    else {
		      jQuery('.commit-beyond-year-total').removeClass('text-danger');
			  (isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(updateFuture.toFixed(2))+'</div>');
		    }			
			var getAmtFut = jQuery('#commitment-beyond-next-year div').text();
			var getValFut = getAmtFut.split('$');
			var finalAmtFut = parseFloat(getValFut[1].replace(/[^\d\.\-]/g, ''));
			var newAmtFut = (futureYearTotal + finalAmtFut);						
			(isNaN(newAmtFut)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total :'+format(newAmtFut.toFixed(2))+'</div>');
			
			var varienceTotal = 0;
			jQuery(".varience-total-calc").each(function () {
			  var varienceYear = jQuery(this).text();	
			  var stvarienceYear = parseFloat(varienceYear.replace(/[^\d\.\-]/g, ''));
			  varienceTotal += isNaN(stvarienceYear) ? 0 : stvarienceYear;
			});
			(isNaN(varienceTotal)) ? '' : jQuery('.etc-varience-total-calc-total').text(format(varienceTotal.toFixed(2)));		
			(varienceTotal < 0)?tblrow.find('.etc-varience-total-calc-total').addClass('text-danger'):tblrow.find('.etc-varience-total-calc-total').removeClass('text-danger');		
			
			
		  
		});
		
		tblrow.find('.etc-amt-quarter-fourth-etc').on('keyup', function () {
		  var fourthQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  var q4 = '0';
		  if(fourthQuarter && fourthQuarter != '-') {
		    q4 = fourthQuarter;
		  }
			var etcAmt = tblrow.find(".etc-amt").text();		  
			var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');						
			// Now get all the quarter values
			var getFistQuarterText = tblrow.find('.etc-amt-quarter-one-etc').text().replace(/[^\d\.\-]/g, '');
			var getSecQuarterText = tblrow.find('.etc-amt-quarter-two-etc').text().replace(/[^\d\.\-]/g, '');
			var getThirdText = tblrow.find('.etc-amt-quarter-three-etc').text().replace(/[^\d\.\-]/g, '');
			var getFourthQuarterText = q4;		  
			var quarterTotal = parseFloat(getFistQuarterText) + parseFloat(getSecQuarterText) + parseFloat(getThirdText) + parseFloat(getFourthQuarterText);		
			var totalFnl = (quarterTotal)?quarterTotal:0.00;
			tblrow.find('.etc-total-spent').text(format(totalFnl.toFixed(2)));
			var totalSpent = tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, '');
			var beyondYear = tblrow.find('.etc-beyond-year').val().replace(/[^\d\.\-]/g, '');		  
			var varience = parseFloat(etcAmtCal) - (parseFloat(quarterTotal) + parseFloat(beyondYear));
			tblrow.find('.varience-total-calc').text(format(varience.toFixed(2)));			
			(varience < 0)?tblrow.find('.varience-total-calc').addClass('text-danger'):tblrow.find('.varience-total-calc').removeClass('text-danger');
			
			var previousYearTotal = 0;
			jQuery(".previous-year-etc").each(function () {
			  var getPrevVal = jQuery(this).val();	
			  var stPrevVal = parseFloat(getPrevVal.replace(/[^\d\.\-]/g, ''));
			  previousYearTotal += isNaN(stPrevVal) ? 0 : stPrevVal;
			});					 
		    (isNaN(previousYearTotal)) ? '' : jQuery('.previous-year-grand-total-etc').text(format(previousYearTotal.toFixed(2)));		
			(previousYearTotal < 0)?jQuery('.previous-year-grand-total-etc').addClass('text-danger'):jQuery('.previous-year-grand-total-etc').removeClass('text-danger');
			
			var quarterOneTotal = 0;
			jQuery(".etc-amt-quarter-one-etc").each(function () {
			  var getQOneVal = jQuery(this).val();	
			  var stQoneVal = parseFloat(getQOneVal.replace(/[^\d\.\-]/g, ''));
			  quarterOneTotal += isNaN(stQoneVal) ? 0 : stQoneVal;
			});					 
		    (isNaN(quarterOneTotal)) ? '' : jQuery('.quarter-one-grand-total-etc').text(format(quarterOneTotal.toFixed(2)));		
			(quarterOneTotal < 0)?jQuery('.quarter-one-grand-total-etc').addClass('text-danger'):jQuery('.quarter-one-grand-total-etc').removeClass('text-danger');
			
			var quarterTwoTotal = 0;
			jQuery(".etc-amt-quarter-two-etc").each(function () {
			  var getqTwoVal = jQuery(this).val();	
			  var stQTwoVal = parseFloat(getqTwoVal.replace(/[^\d\.\-]/g, ''));
			  quarterTwoTotal += isNaN(stQTwoVal) ? 0 : stQTwoVal;
			});					 
		    (isNaN(quarterTwoTotal)) ? '' : jQuery('.quarter-two-grand-total-etc').text(format(quarterTwoTotal.toFixed(2)));		
			(quarterTwoTotal < 0)?jQuery('.quarter-two-grand-total-etc').addClass('text-danger'):jQuery('.quarter-two-grand-total-etc').removeClass('text-danger');
			
			var grandTotalThree = 0;
			jQuery(".etc-amt-quarter-three-etc").each(function () {
			  var getVal = jQuery(this).val();	
			  var stval = parseFloat(getVal.replace(/[^\d\.\-]/g, ''));
			  grandTotalThree += isNaN(stval) ? 0 : stval;
			});					 
		    (isNaN(grandTotalThree)) ? '' : jQuery('.etc-amt-quarter-three-total-etc').text(format(grandTotalThree.toFixed(2)));		
			(grandTotalThree < 0)?jQuery('.etc-amt-quarter-three-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-three-total-etc').removeClass('text-danger');
			
			var grandTotalFour = 0;
			jQuery(".etc-amt-quarter-fourth-etc").each(function () {
			  var getFrthVal = jQuery(this).val();	
			  var stFrthval = parseFloat(getFrthVal.replace(/[^\d\.\-]/g, ''));
			  grandTotalFour += isNaN(stFrthval) ? 0 : stFrthval;
			});					 
		    (isNaN(grandTotalFour)) ? '' : jQuery('.etc-amt-quarter-fourth-total-etc').text(format(grandTotalFour.toFixed(2)));		
			(grandTotalFour < 0)?jQuery('.etc-amt-quarter-fourth-total-etc').addClass('text-danger'):jQuery('.etc-amt-quarter-fourth-total-etc').removeClass('text-danger');
			
			var currentYearTotal = 0;
			jQuery(".etc-total-spent").each(function () {
			  var currentYear = jQuery(this).text();	
			  var stcurrentYear = parseFloat(currentYear.replace(/[^\d\.\-]/g, ''));
			  currentYearTotal += isNaN(stcurrentYear) ? 0 : stcurrentYear;
			});
			(isNaN(currentYearTotal)) ? '' : jQuery('.etc-total-spent-total').text(format(currentYearTotal.toFixed(2)));		
			(currentYearTotal < 0)?tblrow.find('.etc-total-spent-total').addClass('text-danger'):tblrow.find('.etc-total-spent-total').removeClass('text-danger');
			var getAmtSpent = jQuery('#commitment-current-year div').text();
			var getVal = getAmtSpent.split('$');
			var finalAmt = parseFloat(getVal[1].replace(/[^\d\.\-]/g, ''));
			var newAmt = (currentYearTotal + finalAmt);
			jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 4px solid #fff;">'+ new Date().getFullYear() +' Spending :'+format(newAmt.toFixed(2))+'</div>');
			
			var futureYearTotal = 0;
			jQuery(".etc-beyond-year").each(function () {
			  var beyondYear = jQuery(this).text();	
			  var stbeyondYear = parseFloat(beyondYear.replace(/[^\d\.\-]/g, ''));
			  futureYearTotal += isNaN(stbeyondYear) ? 0 : stbeyondYear;
			});
			(isNaN(futureYearTotal)) ? '' : jQuery('.etc-beyond-year-total-etc').text(format(futureYearTotal.toFixed(2)));		
			(futureYearTotal < 0)?tblrow.find('.etc-beyond-year-total-etc').addClass('text-danger'):tblrow.find('.etc-beyond-year-total-etc').removeClass('text-danger');
			
			var getCommitFuture = jQuery('.commit-beyond-year-total').text().replace(/[^\d\.\-]/g, '');
			var updateFuture = parseFloat(getCommitFuture) + parseFloat(futureYearTotal);
			if(updateFuture < 0) {
			  jQuery('.commit-beyond-year-total').addClass('text-danger');
			  (isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(updateFuture.toFixed(2))+'</span></div>');
		    }
		    else {
		      jQuery('.commit-beyond-year-total').removeClass('text-danger');
			  (isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(updateFuture.toFixed(2))+'</div>');
		    }			
			var getAmtFut = jQuery('#commitment-beyond-next-year div').text();
			var getValFut = getAmtFut.split('$');
			var finalAmtFut = parseFloat(getValFut[1].replace(/[^\d\.\-]/g, ''));
			var newAmtFut = (futureYearTotal + finalAmtFut);						
			(isNaN(newAmtFut)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total :'+format(newAmtFut.toFixed(2))+'</div>');
			
			var varienceTotal = 0;
			jQuery(".varience-total-calc").each(function () {
			  var varienceYear = jQuery(this).text();	
			  var stvarienceYear = parseFloat(varienceYear.replace(/[^\d\.\-]/g, ''));
			  varienceTotal += isNaN(stvarienceYear) ? 0 : stvarienceYear;
			});
			(isNaN(varienceTotal)) ? '' : jQuery('.etc-varience-total-calc-total').text(format(varienceTotal.toFixed(2)));		
			(varienceTotal < 0)?tblrow.find('.etc-varience-total-calc-total').addClass('text-danger'):tblrow.find('.etc-varience-total-calc-total').removeClass('text-danger');		
			
			
		  
		});
		tblrow.find('.etc-beyond-year').on('keyup', function () {
		  var beyondYear = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		  var by = '0';
		  if(beyondYear && beyondYear != '-') {
		    by = beyondYear;
		  }
		  var etcAmt = tblrow.find(".etc-amt").text();		  
		  var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');		  
		  var totalSpent = tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, '');		
		  var varience = parseFloat(etcAmtCal) - (parseFloat(totalSpent) + parseFloat(by));
		  tblrow.find('.varience-total-calc').text(format(varience.toFixed(2)));
		  if(varience < 0) { tblrow.find('.varience-total-calc').addClass('text-danger'); }
		  else { tblrow.find('.varience-total-calc').removeClass('text-danger'); }
		  var futureYearTotal = 0;
		  jQuery(".etc-beyond-year").each(function () {
		    var beyondYearCal = jQuery(this).val();	
			var stbeyondYear = parseFloat(beyondYearCal.replace(/[^\d\.\-]/g, ''));
			futureYearTotal += isNaN(stbeyondYear) ? 0 : stbeyondYear;
		  });
		  (isNaN(futureYearTotal)) ? '' : jQuery('.etc-beyond-year-total-etc').text(format(futureYearTotal.toFixed(2)));		
		  (futureYearTotal < 0)?tblrow.find('.etc-beyond-year-total-etc').addClass('text-danger'):tblrow.find('.etc-beyond-year-total-etc').removeClass('text-danger');
		  
		  var getCommitFuture = jQuery('.commit-beyond-year-total').text().replace(/[^\d\.\-]/g, '');
		  var updateFuture = parseFloat(getCommitFuture) + parseFloat(futureYearTotal);
		  if(updateFuture < 0) {
			jQuery('.commit-beyond-year-total').addClass('text-danger');
			(isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : <span class="text-danger">'+format(updateFuture.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(updateFuture)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total : '+format(updateFuture.toFixed(2))+'</div>');
		  }
		   
		  /*var getAmtFut = jQuery('#commitment-beyond-next-year div').text();
			var getValFut = getAmtFut.split('$');
			var finalAmtFut = parseFloat(getValFut[1].replace(/[^\d\.\-]/g, ''));
			var newAmtFut = (futureYearTotal + finalAmtFut);						
			(isNaN(newAmtFut)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;border-left:4px solid #fff;">Future Year Total :'+format(newAmtFut.toFixed(2))+'</div>');*/
			
		});			
	  });	
	  
	  jQuery('.custom-submit-forecast-save-as-button input').unbind('click').bind('click',function (e) {
	    e.preventDefault();
		var projectId = jQuery('.project_programe_spending_forcast_pro').val()
		var spendingData = [];
		var tblrows = jQuery(".m6connect-program-spending-forcast-main-table tbody tr");	  
	    tblrows.each(function (row, tr) {
		  tblrow = jQuery(this);
		  var q4 = tblrow.find('.commit-amt-quarter-fourth').val();
		  if(q4) { var q4Up = q4.replace(/[^\d\.\-]/g, ''); }
		  else { var q4Up = 0.00; }
		  var beyond = tblrow.find('.commit-beyond-year').val()
		  if(beyond) { var beyondUp = beyond.replace(/[^\d\.\-]/g, ''); }
		  else { var beyondUp = 0.00; }
		  if(quarter == 1) {
			var q1 = tblrow.find('.commit-amt-quarter-one').val();
		  	if(q1) { var q1Up = q1.replace(/[^\d\.\-]/g, ''); }
		  	else { var q1Up = 0.00; }
			
			var q2 = tblrow.find('.commit-amt-quarter-two').val();
		  	if(q2) { var q2Up = q2.replace(/[^\d\.\-]/g, ''); }
		  	else { var q2Up = 0.00; }
			
			var q3 = tblrow.find('.commit-amt-quarter-three').val();
		  	if(q3) { var q3Up = q3.replace(/[^\d\.\-]/g, ''); }
		  	else { var q3Up = 0.00; }
						
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one-text').text()!=''?tblrow.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-one').val()!=''?q1Up:0,
			  tblrow.find('.commit-amt-quarter-two').val()!=''?q2Up:0,
			  tblrow.find('.commit-amt-quarter-three').val()!=''?q3Up:0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  if(quarter == 2) {
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one').text()!=''?tblrow.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-two').text()!=''?tblrow.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  if(quarter == 3) {
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one').text()!=''?tblrow.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-two').text()!=''?tblrow.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  if(quarter == 4) {
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one').text()!=''?tblrow.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-two').text()!=''?tblrow.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }		    
		});		
        jQuery('#edit-forcast-update-data').val(spendingData);
		// Get spending data for etc
		var spendingEtcData = [];
		var tblrows = jQuery(".m6connect-program-spending-forcast-main-table-etc tbody tr");	  
	    tblrows.each(function (row, tr) {
		  tblrow = jQuery(this);
		  var q1 = tblrow.find('.etc-amt-quarter-one-etc').val();
		  if(q1) { var q1Up = q1.replace(/[^\d\.\-]/g, ''); }
		  else { var q1Up = 0.00; }
		  var q2 = tblrow.find('.etc-amt-quarter-two-etc').val();
		  if(q2) { var q2Up = q2.replace(/[^\d\.\-]/g, ''); }
		  else { var q2Up = 0.00; }
		  var q3 = tblrow.find('.etc-amt-quarter-three-etc').val();
		  if(q3) { var q3Up = q3.replace(/[^\d\.\-]/g, ''); }
		  else { var q3Up = 0.00; }
		  var q4 = tblrow.find('.etc-amt-quarter-fourth-etc').val();
		  if(q4) { var q4Up = q4.replace(/[^\d\.\-]/g, ''); }
		  else { var q4Up = 0.00; }
		  
		  var beyond = tblrow.find('.etc-beyond-year').val()
		  if(beyond) { var beyondUp = beyond.replace(/[^\d\.\-]/g, ''); }
		  else { var beyondUp = 0.00; }
		  spendingEtcData[row] = [
		  	jQuery('.project_programe_spending_forcast_pro').val(),
			tblrow.find('.etc-number').attr('id'),
			tblrow.find('.etc-amt-quarter-one').val()!=''?q1Up:0,
			tblrow.find('.etc-amt-quarter-two').val()!=''?q2Up:0,
			tblrow.find('.etc-amt-quarter-three').val()!=''?q3Up:0,
			tblrow.find('.etc-amt-quarter-fourth').val()!=''?q4Up:0,
			tblrow.find('.etc-total-spent').text()!=''?tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			tblrow.find('.etc-beyond-year').val()!=''?beyondUp:0,
			tblrow.find('.varience-total-calc').text()!=''?tblrow.find('.varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			'Nextrecord',
		  ]		  
		});		
        jQuery('#edit-forcast-update-data-etc').val(spendingEtcData);
		var getStatus = jQuery('.spending-forcast-edit-input').val();
		if(getStatus == 'true') {		  	
		  var getForecast = jQuery('.spending-forecast-select').val();
          var forcastName = jQuery(".spending-forecast-select option[value="+getForecast+"]").text();		
		  jQuery('#spending-forcast-option-dialog-saveas').html('<div class="text-center"><p>Provide a new name for your spending forecast.</p><p><input type="text" name="forcast name" class="forcast-name-by-user" value="'+forcastName+'"> <input type="hidden" value="'+projectId+'" class="forcast-project-id-cust"></p></div>');
		  jQuery('#spending-forcast-option-dialog-saveas').dialog('open');
		}
		else {
		  jQuery('.spending_forcast_pro_submit_call').trigger('click');
		}
	  });	 
	  
	  jQuery('.custom-submit-forecast-button input').unbind('click').bind('click',function (e) {
	    e.preventDefault();
		var projectId = jQuery('.project_programe_spending_forcast_pro').val()
		var spendingData = [];
		var tblrows = jQuery(".m6connect-program-spending-forcast-main-table tbody tr");	  
	    tblrows.each(function (row, tr) {
		  tblrow = jQuery(this);
		  
		  var q4 = tblrow.find('.commit-amt-quarter-fourth').val();
		  if(q4) { var q4Up = q4.replace(/[^\d\.\-]/g, ''); }
		  else { var q4Up = 0.00; }
			
		  var beyond = tblrow.find('.commit-beyond-year').val();
		  if(beyond) { var beyondUp = beyond.replace(/[^\d\.\-]/g, ''); }
		  else { var beyondUp = 0.00; }
		  var today = new Date();
		  var quarter = Math.floor((today.getMonth() + 3) / 3);
		  if(quarter == 1) {
		    var q1 = tblrow.find('.commit-amt-quarter-one').val();
		  	if(q1) { var q1Up = q1.replace(/[^\d\.\-]/g, ''); }
		  	else { var q1Up = 0.00; }
			
			var q2 = tblrow.find('.commit-amt-quarter-two').val();
		  	if(q2) { var q2Up = q2.replace(/[^\d\.\-]/g, ''); }
		  	else { var q2Up = 0.00; }
			
			var q3 = tblrow.find('.commit-amt-quarter-three').val();
		  	if(q3) { var q3Up = q3.replace(/[^\d\.\-]/g, ''); }
		  	else { var q3Up = 0.00; }
			
			var q4 = tblrow.find('.commit-amt-quarter-fourth').val();
		  	if(q4) { var q4Up = q4.replace(/[^\d\.\-]/g, ''); }
		  	else { var q4Up = 0.00; }
						
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one-text').text()!=''?tblrow.find('.commit-amt-quarter-one-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-one').val()!=''?q1Up:0,
			  tblrow.find('.commit-amt-quarter-two').val()!=''?q2Up:0,
			  tblrow.find('.commit-amt-quarter-three').val()!=''?q3Up:0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  if(quarter == 2) {
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one').text()!=''?tblrow.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-two').text()!=''?tblrow.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  if(quarter == 3) {
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one').text()!=''?tblrow.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-two').text()!=''?tblrow.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  if(quarter == 4) {
		    spendingData[row] = [
		  	  jQuery('.project_programe_spending_forcast_pro').val(),
			  tblrow.find('.commit-number').attr('id'),
			  tblrow.find('.commit-amt-quarter-one').text()!=''?tblrow.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-two').text()!=''?tblrow.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,
			  tblrow.find('.commit-total-spent').text()!=''?tblrow.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			  tblrow.find('.commit-beyond-year').val()!=''?beyondUp:0,
			  tblrow.find('.commit-varience-total-calc').text()!=''?tblrow.find('.commit-varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			  quarter,
			  'Nextrecord',
		    ]
		  }
		  
		  		  
		});		
        jQuery('#edit-forcast-update-data').val(spendingData);
		// Get spending data for etc
		var spendingEtcData = [];
		var tblrows = jQuery(".m6connect-program-spending-forcast-main-table-etc tbody tr");	  
	    tblrows.each(function (row, tr) {
		  tblrow = jQuery(this);
		  var q1 = tblrow.find('.etc-amt-quarter-one-etc').val();
		  if(q1) { var q1Up = q1.replace(/[^\d\.\-]/g, ''); }
		  else { var q1Up = 0.00; }
		  var q2 = tblrow.find('.etc-amt-quarter-two-etc').val();
		  if(q2) { var q2Up = q2.replace(/[^\d\.\-]/g, ''); }
		  else { var q2Up = 0.00; }
		  var q3 = tblrow.find('.etc-amt-quarter-three-etc').val();
		  if(q3) { var q3Up = q3.replace(/[^\d\.\-]/g, ''); }
		  else { var q3Up = 0.00; }
		  var q4 = tblrow.find('.etc-amt-quarter-fourth-etc').val();
		  if(q4) { var q4Up = q4.replace(/[^\d\.\-]/g, ''); }
		  else { var q4Up = 0.00; }
		  
		  var beyond = tblrow.find('.etc-beyond-year').val()
		  if(beyond) { var beyondUp = beyond.replace(/[^\d\.\-]/g, ''); }
		  else { var beyondUp = 0.00; }
		  var today = new Date();
		  var quarter = Math.floor((today.getMonth() + 3) / 3);
		  spendingEtcData[row] = [
		  	jQuery('.project_programe_spending_forcast_pro').val(),
			tblrow.find('.etc-number').attr('id'),
			tblrow.find('.etc-amt-quarter-one').val()!=''?q1Up:0,
			tblrow.find('.etc-amt-quarter-two').val()!=''?q2Up:0,
			tblrow.find('.etc-amt-quarter-three').val()!=''?q3Up:0,
			tblrow.find('.etc-amt-quarter-fourth').val()!=''?q4Up:0,
			tblrow.find('.etc-total-spent').text()!=''?tblrow.find('.etc-total-spent').text().replace(/[^\d\.\-]/g, ''):0,
			tblrow.find('.etc-beyond-year').val()!=''?beyondUp:0,
			tblrow.find('.varience-total-calc').text()!=''?tblrow.find('.varience-total-calc').text().replace(/[^\d\.\-]/g, ''):0,
			'Nextrecord',
		  ]	  
		});		
        jQuery('#edit-forcast-update-data-etc').val(spendingEtcData);
		var getStatus = jQuery('.spending-forcast-edit-input').val();
		if(getStatus == 'false') {
		  jQuery('#spending-forcast-option-dialog').html('<div class="text-center"><p>Provide a name for your spending forecast.</p><p> <input type="text" name="forcast name" class="forcast-name-by-user"> <input type="hidden" value="'+projectId+'" class="forcast-project-id-cust"></p></div>');
		  jQuery('#spending-forcast-option-dialog').dialog('open');
		}
		else {
		  jQuery('.spending_forcast_pro_submit_call').trigger('click');
		}
	  });	 
	  if(jQuery('.spending-forecast-select').val() == 'None') {
	    jQuery('.custom-submit-forecast-delete-button').hide();
		jQuery('.custom-submit-forecast-save-as-button').hide();
	  }
	  else {
	    jQuery('.custom-submit-forecast-delete-button').show();
		jQuery('.custom-submit-forecast-save-as-button').show();
	  }
	  jQuery('.custom-submit-forecast-delete-button').unbind('click').bind('click',function (e) {
		var ProId = jQuery('.project_programe_spending_forcast_pro').val();
		var getForecast = jQuery('.spending-forecast-select').val();
        var forcastName = jQuery(".spending-forecast-select option[value="+getForecast+"]").text();
		if(forcastName != 'None')
	    jQuery.post( '/remove-forecast-data/'+ ProId +'/'+forcastName, function( data ) {
		  if(data.out == 'success') {
		    window.location.href="/program/spending-forcast";
		  }
		  else {
		    window.location.href="/program/spending-forcast";
		  }
		});
	  });	  
	  jQuery('.add-new-spending-forecast').click(function (e) {
	    jQuery('.project_programe_spending_forcast_pro').trigger('change');
	  });
	  // Trigger previous forecast by select list
	  jQuery('.spending-forecast-select').change(function(e){
        var getForecast = jQuery(this).val();
        if(getForecast && getForecast != 'None') {
			    var getLastForecast = jQuery('.spending-forecast-select option').last().val();	
						window.location.href="/program/spending-forcast?forecast="+getForecast;
        }
		else {
		  
		}
      });
	  // ===============================
	  var today = new Date();
	  var quarter = Math.floor((today.getMonth() + 3) / 3);
	  if(quarter == 1) {
	    /*jQuery('.custom-quater-two-heading').hide();
	    jQuery('.custom-quater-three-heading').hide();
	    jQuery('.custom-quater-fourth-heading').hide();*/  
	  }
	  if(quarter == 2) {
	    jQuery('.custom-quater-one-heading').hide();
	    jQuery('.custom-quater-three-heading').hide();
	    jQuery('.custom-quater-fourth-heading').hide();  
	  }
	  if(quarter == 3) {
	    jQuery('.custom-quater-one-heading').hide();
	    jQuery('.custom-quater-two-heading').hide();
	    jQuery('.custom-quater-fourth-heading').hide();  
	  }
	  if(quarter == 4) {
	    jQuery('.custom-quater-one-heading').hide();
	    jQuery('.custom-quater-two-heading').hide();
	    jQuery('.custom-quater-three-heading').hide();  
	  }
	  if(jQuery('.show-left-span').hasClass('fa-angle-double-left')) {
	    jQuery('.custom-footer-bottom').addClass('col-md-4');
	  }
	  // ================================
	  
	  
	  //jQuery('.custom-quater-fourth-heading').hide();
	  jQuery('.show-left').unbind('click').bind('click',function () {
	    jQuery('.main-total-spent').hide();
		if(quarter == 1) {
	      jQuery('.custom-quater-two-heading').toggle('slide');
	      jQuery('.custom-quater-three-heading').toggle('slide');
	      jQuery('.custom-quater-fourth-heading').toggle('slide');
		  
		  if(jQuery('.show-left-span').hasClass('fa-angle-double-left')) {
		    jQuery('.custom-quater-one-heading').addClass('col-md-2');
		    jQuery('.custom-quater-two-heading').addClass('col-md-2');
	        jQuery('.custom-quater-three-heading').addClass('col-md-2');
	        jQuery('.custom-quater-fourth-heading').addClass('col-md-2');
			jQuery('.custom-footer-bottom').addClass('col-md-4');			
		  }		  
		  if(jQuery('.show-left-span').hasClass('fa-angle-double-right')) {
		    jQuery('.custom-quater-one-heading').removeClass('col-md-2');
		    jQuery('.custom-quater-two-heading').removeClass('col-md-2');
	        jQuery('.custom-quater-three-heading').removeClass('col-md-2');
	        jQuery('.custom-quater-fourth-heading').removeClass('col-md-2');
			jQuery('.custom-footer-bottom').removeClass('col-md-4');			
		  }
		}
	    if(quarter == 2) {
	      jQuery('.custom-quater-one-heading').toggle('slide');
	      jQuery('.custom-quater-three-heading').toggle('slide');
	      jQuery('.custom-quater-fourth-heading').toggle('slide');    
	      
        if(jQuery('.show-left-span').hasClass('fa-angle-double-left')) {
          jQuery('.custom-quater-one-heading').addClass('col-md-2');
          jQuery('.custom-quater-two-heading').addClass('col-md-2');
          jQuery('.custom-quater-three-heading').addClass('col-md-2');
          jQuery('.custom-quater-fourth-heading').addClass('col-md-2');
          jQuery('.custom-footer-bottom').addClass('col-md-4');     
        }     
        if(jQuery('.show-left-span').hasClass('fa-angle-double-right')) {
          jQuery('.custom-quater-one-heading').removeClass('col-md-2');
          jQuery('.custom-quater-two-heading').removeClass('col-md-2');
          jQuery('.custom-quater-three-heading').removeClass('col-md-2');
          jQuery('.custom-quater-fourth-heading').removeClass('col-md-2');
          jQuery('.custom-footer-bottom').removeClass('col-md-4');
        }
      }
	    if(quarter == 3) {
	      jQuery('.custom-quater-one-heading').toggle('slide');
	      jQuery('.custom-quater-two-heading').toggle('slide');
	      jQuery('.custom-quater-fourth-heading').toggle('slide');  
	    }
	    if(quarter == 4) {
	      jQuery('.custom-quater-one-heading').toggle('slide');
	      jQuery('.custom-quater-two-heading').toggle('slide');
	      jQuery('.custom-quater-three-heading').toggle('slide');  
	    }
		
		if(jQuery('.show-left-span').hasClass('fa-angle-double-left')) {
		  jQuery('.show-left-span').removeClass('fa-angle-double-left');
		  jQuery('.show-left-span').addClass('fa-angle-double-right');
		}else if(jQuery('.show-left-span').hasClass('fa-angle-double-right')) {
		  jQuery('.show-left-span').removeClass('fa-angle-double-right');
		  jQuery('.show-left-span').addClass('fa-angle-double-left');
		}
	  });
	  jQuery('.show-right').unbind('click').bind('click',function () {
	    if(quarter == 1) { jQuery('.custom-quater-one-heading').toggle('slide'); }
	    if(quarter == 2) { jQuery('.custom-quater-two-heading').toggle('slide'); }
	    if(quarter == 3) { jQuery('.custom-quater-three-heading').toggle('slide'); }
	    if(quarter == 4) { jQuery('.custom-quater-fourth-heading').toggle('slide');  }
		jQuery('.main-total-spent').show();			
		if(jQuery('.show-right-span').hasClass('fa-angle-double-left')) {
		  jQuery('.show-right-span').removeClass('fa-angle-double-left');
		  jQuery('.show-right-span').addClass('fa-angle-double-right');
		}else if(jQuery('.show-right-span').hasClass('fa-angle-double-right')) {
		  jQuery('.show-right-span').removeClass('fa-angle-double-right');
		  jQuery('.show-right-span').addClass('fa-angle-double-left');
		}
	  });
	}
	// ==== End work for spending forecast ==== //
	// ==== Work for Spending page ==== //
	// Start asset work
    else if(getPath == '/program/assets') {
    setTimeout(function() {
      jQuery(".messages--status").hide('fast', {}, 500)
    }, 5000);
	jQuery('.category-header-cust').hide();
	jQuery('.allocation-header-cust').hide();
	
	jQuery('.show-left-span-category').click(function (e) {
	  jQuery('.category-header-cust').show('fast');
	  jQuery('.category-header-live').hide('fast');
	  jQuery('.show-left-span-category').hide();
	  jQuery('.show-right-span-category').show();	  
	});
	jQuery('.show-right-span-category').click(function (e) {
	  jQuery('.category-header-cust').hide('fast');
	  jQuery('.category-header-live').show('fast');
	  jQuery('.show-left-span-category').show();
	  jQuery('.show-right-span-category').hide();
	});
	
	jQuery('.show-left-span-allocation').click(function (e) {
	  jQuery('.category-header-cust').hide('fast');
	  jQuery('.category-header-live').show('fast');
	  jQuery('.allocation-header-cust').show('fast');
	  jQuery('.show-left-span-allocation').hide();
	  jQuery('.show-right-span-allocation').show();
	});
	jQuery('.show-right-span-allocation').click(function (e) {
	  jQuery('.category-header-cust').hide('fast');
	  jQuery('.category-header-live').show('fast');
	  jQuery('.allocation-header-cust').hide('fast');
	  jQuery('.show-left-span-allocation').show();
	  jQuery('.show-right-span-allocation').hide();
	});
	
	
	jQuery('.edit-assets-detail').unbind('click').bind('click', function (e) {
      e.preventDefault();
      var projectId = jQuery(this).attr('for');
      jQuery('.project-program-sel-assets').val(projectId).trigger('change');
      jQuery('.project_asset_nid').val(projectId);
      jQuery('html, body').animate({
          scrollTop: "0px"
      }, 800); 
      jQuery('#project_program_asset_main_container').attr('for','open');
      jQuery('#project_program_asset_main_container').attr('data','edit'); 
	  jQuery('#project_program_asset_main_container').show();
      jQuery('.custom-reset-button-schedule-div').show();
    });
	jQuery('.custom-reset-button-schedule').click(function (e) {
      jQuery('#project_program_asset_main_container').hide();
      jQuery('.custom-reset-button-schedule-div').hide();
      jQuery('#project_program_asset_main_container').attr('for', 'closed');
    });
	
    jQuery('.project-program-assets-sel', context).change(function (e) {
	  
	}); 
	
	jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
  	var urlajax = ajaxOptions.url;
  	if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name==="select-assets")){
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
	});
	jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
  	  var urlajax = ajaxOptions.url;
  	  if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && (ajaxOptions.extraData._triggering_element_name==="select-assets")){
		    jQuery.unblockUI();
      		var rowcount = jQuery('.dataTables_wrapper').length;
			var rowCountTable = jQuery('.m6connect-custom-program-table tr').length;
      		if(rowcount == 0 && rowCountTable > 2) {
    	      jQuery('table.m6connect-custom-program-table').DataTable({
    			  //"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
    				"bPaginate": false,
					"paging": false,		
    				"aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
    				"searching": false,
    				 "dom": 'Rfrtlip',
        		});
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
    		"dom": 'Rfrtlip',
          });
  		}
	  }
	});
	jQuery('input:checkbox.image-remove-update').unbind('click').bind('click',function (e) {
	  var getFid = jQuery(this).val();
      var nodeId = jQuery(this).attr('for');
      jQuery.post( '/update-image-reove/'+getFid+'/'+nodeId, function( data ) { 
        jQuery('.project-program-sel-assets').val(nodeId).trigger('change');
      });
	});
	jQuery('.make-default-update').unbind('click').bind('click',function (e) {
	  var getFid = jQuery(this).val();
      var nodeId = jQuery(this).attr('for');
      jQuery('.make_default').val(getFid);
	});
	
  }	
	// ==== Work for Safety Page ==== //
	else if(getPath == '/program/safety') {
	  /*******************************************/
	  jQuery(document).ajaxStart(function () {
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
    }).ajaxStop(function () {
        jQuery.unblockUI();
    });
	  /*****************************************/
	  	
	  jQuery('.project-program-safety-sel', context).change(function (e) {});					
	  var safetyProId = jQuery('.project-program-safety-sel').val();
	  if(safetyProId != '') {
	    jQuery('.project_schedule_ref_nid').val(safetyProId);
	  }
	  jQuery('.project_safety_ref_nid').val(safetyProId);
	  // ==== Check if status alredy used ==== //		
	  jQuery.post( '/status-mark/project_safety/'+safetyProId, function( data ) { 
	  if(!isNaN(data.nodeNid) && data.nodeNid != '') {
	    //jQuery('.program-safety-status').attr('disabled', true);
		var getStatus = data.Mark;
		jQuery('.program-safety-status option[value="'+getStatus).attr("selected", true);
		jQuery('.status_mark_data_id').val(data.nodeNid);
		if(getStatus == 'reds') {
		  jQuery('.status-mark').show();   
		  jQuery('.status-mark').addClass('text-danger');		
		  jQuery('.status-mark').removeClass('text-warning');
		  jQuery('.status-mark').removeClass('text-success');
		}
		else if(getStatus == 'yellows') {
		  jQuery('.status-mark').show();  
		  jQuery('.status-mark').removeClass('text-danger');
		  jQuery('.status-mark').removeClass('text-success');
		  jQuery('.status-mark').addClass('text-warning');
		}
		else if(getStatus == 'greens') {
		  jQuery('.status-mark').show(); 
		  jQuery('.status-mark').addClass('text-success');
		  jQuery('.status-mark').removeClass('text-danger');
		  jQuery('.status-mark').removeClass('text-warning');
		}
	  }
	});
	// ==== End for satatus check work ==== //							  
	  
	  jQuery('.edit-safety-detail', context).click(function (e) {
		jQuery('#project_safety_main_container').attr('for','open');
		jQuery('#project_safety_main_container').attr('data','edit');			
		jQuery('#project_safety_main_container').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();
		jQuery('.program-safety-status-btn').show();
        e.preventDefault();
		var safetyID = jQuery(this).attr('for');
	    var safetyUrlID = getUrlParameter('sid');
		  if(safetyUrlID) { 
	      if(safetyID == safetyUrlID) {
		    jQuery('.project_safety_nid').val(safetyID);  
		  }  
		  else {
		    var proId = jQuery('.project-program-safety-sel').val();	
		    window.location.href="/program/safety?pid="+proId+'&sid='+safetyID;
		  }
	    }
	    else {	  
	      jQuery('.project-program-sel-safety').val(safetyID).trigger('change');
	      jQuery('.project_safety_nid').val(safetyID);
		  
	    }
	    /*var projectId = jQuery(this).attr('for');
	    jQuery('.project-program-sel-safety').val(projectId).trigger('change');
	    jQuery('.project_safety_nid').val(projectId);	  */
	     jQuery('html, body').animate({
           scrollTop: "0px"
	     }, 800); 
      });
	  var safetyId = getUrlParameter('sid');
	  if(!isNaN(safetyId)) { 
	    jQuery('.project-program-sel-safety').val(safetyId).trigger('change');
		jQuery('.project_safety_nid').val(safetyId);
		jQuery('#project_safety_main_container').attr('for','open');
		jQuery('#project_safety_main_container').attr('data2','querystring');
		jQuery('#project_safety_main_container').show();
		jQuery('.custom-submit-safety').show();
		jQuery('.program-safety-status-btn').show();
	  }
	  jQuery('.custom-reset-button').click(function (e) {
	    jQuery('#project_safety_main_container').hide();
		jQuery('.custom-submit-reset').hide();
		jQuery('#project_safety_main_container').attr('for', 'closed');
		jQuery('#project_safety_main_container').attr('data', 'edit');
	  });
	}			
	// ==== Work for Schedule page ==== //
	else if(getPath == '/program/schedule') {
	  var projectId = jQuery('.project-program-schedule-sel').val();
	  if(projectId != '') {
	    jQuery('.project_schedule_ref_nid').val(projectId);
		jQuery('.new-record-cus-btn').attr('for', projectId);
	  }	
      // ==== Check if status alredy used ==== //		
	  jQuery.post( '/status-mark/project_schedule/'+projectId, function( data ) { 
	    if(!isNaN(data.nodeNid) && data.nodeNid != ''){
		  var getStatus = data.Mark;
		  jQuery('.program-schedule-status option[value="'+getStatus).attr("selected", true);
		  jQuery('.status_mark_data_id').val(data.nodeNid);
		  if(getStatus == 'reds') {
		    jQuery('.status-mark').show();   
			jQuery('.status-mark').addClass('text-danger');		
			jQuery('.status-mark').removeClass('text-warning');
			jQuery('.status-mark').removeClass('text-success');
		  }
		  else if(getStatus == 'yellows') {
		    jQuery('.status-mark').show();  
			jQuery('.status-mark').removeClass('text-danger');
			jQuery('.status-mark').removeClass('text-success');
			jQuery('.status-mark').addClass('text-warning');			  
		  }
		  else if(getStatus == 'greens') {
		    jQuery('.status-mark').show(); 
			jQuery('.status-mark').addClass('text-success');
			jQuery('.status-mark').removeClass('text-danger');
			jQuery('.status-mark').removeClass('text-warning');
		  }  
		  //jQuery('.program-schedule-status').attr('disabled', true);
		}
      });
		// ==== End for satatus check work ==== //		
	  
	  // ====================================	  
	  //jQuery('.project-program-schedule-sel', context).change(function (e) {});	  	  	  
	  jQuery('.edit-schedule-detail', context).click(function (e) {		  
		jQuery('#project_program_schedule_main_container').css('overflow', 'visible');  
	    jQuery('#project_program_schedule_main_container').attr('for','open');
		jQuery('#project_program_schedule_main_container').attr('data','edit');			
		jQuery('#project_program_schedule_main_container').show();
		jQuery('.program-schedule-status-btn').show();		
		jQuery('.custom-submit-schedule-reset').show();
        e.preventDefault();
	    var projectId = jQuery(this).attr('for');
	    jQuery('.project-program-sel-schedule').val(projectId).trigger('change');
	    jQuery('.project_schedule_nid').val(projectId);	  
	    jQuery('html, body').animate({
          scrollTop: "200px"
	      }, 800); 
        });	
	  jQuery('.custom-reset-button').click(function (e) {
	    jQuery('#project_program_schedule_main_container').hide();
		jQuery('.custom-submit-schedule-reset').hide();
		jQuery('#project_program_schedule_main_container').attr('for', 'closed');
		jQuery('#project_program_schedule_main_container').attr('data', 'edit');
	  });
	  var scheduleId = getUrlParameter('scid');
	  if(!isNaN(scheduleId)) {
	    jQuery('.project-program-sel-schedule').val(scheduleId).trigger('change');
		  jQuery('.project_schedule_nid').val(scheduleId);
		  jQuery('#project_program_schedule_main_container').attr('for','open');
		  jQuery('#project_program_schedule_main_container').attr('data2','querystring');
		  jQuery('#project_program_schedule_main_container').show();
		  jQuery('.custom-submit-schedule-reset').show();		  
		  jQuery('.program-schedule-status').show();		  
		  //jQuery('.custom-submit-safety').show();		
	    } 
	  }
	// ==== Work for ETC page ==== //
	else if(getPath == '/program/etc') {
	  // ==== Check if status alredy used ==== //
	  var projectId = jQuery('.project-program-etc-sel').val();
	  jQuery.post( '/status-mark/project_etc/'+projectId, function( data ) { 
	    if(!isNaN(data.nodeNid) && data.nodeNid != ''){
	      var getStatus = data.Mark;
		  jQuery('.program-etc-status option[value="'+getStatus).attr("selected", true);
		  jQuery('.status_mark_data_id').val(data.nodeNid);
		  if(getStatus == 'reds') {
		    jQuery('.status-mark').show();   
		    jQuery('.status-mark').addClass('text-danger');		
		    jQuery('.status-mark').removeClass('text-warning');
		    jQuery('.status-mark').removeClass('text-success');
		  }
		  else if(getStatus == 'yellows') {
		    jQuery('.status-mark').show();  
		    jQuery('.status-mark').removeClass('text-danger');
		    jQuery('.status-mark').removeClass('text-success');
		    jQuery('.status-mark').addClass('text-warning');
		  }
		  else if(getStatus == 'greens') {
		    jQuery('.status-mark').show(); 
		    jQuery('.status-mark').addClass('text-success');
		    jQuery('.status-mark').removeClass('text-danger');
		    jQuery('.status-mark').removeClass('text-warning');
		  }
		  //jQuery('.program-etc-status').attr('disabled', true);
	    }
      });
	  // ==== End for satatus check work ==== //			  
	  jQuery('.edit-etc-detail', context).click(function (e) {
	    jQuery('.project_etc_main_cust').attr('for','open');
		jQuery('.project_etc_main_cust').attr('data','edit');			
		jQuery('.project_etc_main_cust').show();
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();
        e.preventDefault();
		// Additional operation
		var etcID = jQuery(this).attr('for');
	    var etcUrlID = getUrlParameter('eid');
	    if(etcUrlID) { 
	      if(etcID == etcUrlID) {
		    jQuery('.project_etc_nid').val(etcID);  
		  }  
		  else {
		    var proId = jQuery('.project-program-etc-sel').val();	
		    window.location.href="/program/etc?pid="+proId+'&eid='+etcID;
		  }
	    }
	    else {	  
	      jQuery('.project-program-sel-etc').val(etcID).trigger('change');
	      jQuery('.project_etc_nid').val(etcID);
		  
	    }	  	  
	    /*var projectId = jQuery(this).attr('for');
	    jQuery('.project-program-sel-etc').val(projectId).trigger('change');
	    jQuery('.project_etc_nid').val(projectId);	  */
	    jQuery('html, body').animate({
          scrollTop: "0px"
	    }, 800); 
      });	  
		
	  var ProId = jQuery('.project-program-etc-sel').val();
	  jQuery('.new-record-cus-btn').attr('for', ProId);				
	  // get commitment id from query string.
	  var commitid = getUrlParameter('eid');
	  if(!isNaN(commitid)) { 
	    jQuery('.project-program-sel-etc').val(commitid).trigger('change');
		jQuery('.project_etc_nid').val(commitid);
		jQuery('.project_etc_main_cust').attr('for','open');
		jQuery('.project_etc_main_cust').attr('data','edit');
		jQuery('.project_etc_main_cust').attr('data2','querystring');
		jQuery('.project_etc_main_cust').show();
		jQuery('.custom-submit-etc').show();
	  }	
	  jQuery('.custom-reset-button').click(function (e) {
	    jQuery('#project_etc_main_container').hide();
		jQuery('.custom-submit-etc').hide();
		jQuery('#project_etc_main_container').attr('for', 'closed');		
	  });   			
	}	
	// ==== Work for Photos page ==== //
	else if((getPath == '/program/photos')) {	  	
	  jQuery('.field-widget-image-image legend').hide();  
	  jQuery('#project_program_photos_main_container .form-type-file label').hide();  
	  var pid = getUrlParameter('pid');
	  if(!isNaN(pid)) {
	    jQuery('.project-program-photos-sel').val(pid);
      }
	  jQuery('.project-program-photos-sel').change(function() {
	    var photoId = jQuery(this).val();	
	    var pid = getUrlParameter('pid');
	    if(isNaN(pid)|| photoId != pid) { 
	      window.location.href="/program/photos?pid="+photoId;
	    }
	  });
    }
	// ==== Work for Report page ====//
    else if(getPath == '/program/reports') {
      jQuery('.no-data').click(function(e) {
	    e.preventDefault();
	    jQuery('#report-nodata-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You must select a project first.</strong></p></div>');
	    jQuery('#report-nodata-dialog').dialog('open');
	    e.preventDefault();
	    return false;
	  });
	  jQuery('.menu-toggle-inner-report').unbind('click').bind('click',function (e) {
	    jQuery('#project-pdf-data-render-area').toggle();
		jQuery('#project-pdf-data-render-section-full').toggle();
		jQuery('#project-pdf-data-render-section').toggle();
		jQuery('#project-report-links-pdf').toggle();
	  });
    }
	// ==== Work for Cost code page ==== //
    else if(getPath == '/program/add-cost-code') {
	  jQuery('.page__title').hide();
      jQuery('.edit-cc-detail', context).click(function (e) {
	    jQuery('#project_cost_code_main_container').attr('for','open');
	    jQuery('#project_cost_code_main_container').attr('data','edit');			
	    jQuery('#project_cost_code_main_container').show();
	    jQuery('.custom-submit-cost-code').show();	
	    e.preventDefault();
	    var ccID = jQuery(this).attr('for');
	    var costID = getUrlParameter('ccid');
	    if(costID) { 
	      if(ccID == costID) {
		    jQuery('.project_cost_code_nid').val(ccID);  
		  }  
		  else {
		    window.location.href="/program/add-cost-code?id="+ccID+'&ccid='+ccID;
		  }
	    }
	    else {	  
	      jQuery('.project-cost-code-sel').val(ccID).trigger('change');
	      jQuery('.project_cost_code_nid').val(ccID);	  		
	    }
	    jQuery('html, body').animate({
          scrollTop: "0px"
	    }, 800); 	  
      });
	  jQuery('.custom-reset-button-cc').click(function (e) {
        jQuery('#project_cost_code_main_container').hide();
        jQuery('.custom-reset-button-schedule-div').hide();
        jQuery('#project_cost_code_main_container').attr('for', 'closed');
      });
	  var costID = getUrlParameter('ccid');
	  if(!isNaN(costID)) { 
	    jQuery('.project-cost-code-sel').val(costID).trigger('change');
		jQuery('#project_cost_code_main_container').attr('for','open');
		jQuery('#project_cost_code_main_container').attr('data','edit');
		jQuery('#project_cost_code_main_container').attr('data2','querystring');
		jQuery('#project_cost_code_main_container').show();
		jQuery('.custom-submit-cost-code').show();
		jQuery('.project_cost_code_nid').val(costID);
	  }
	  jQuery('.manager_cost_code').change(function (e) {
        var getNumber = jQuery(this).val();
        var ProNumber = 0;
		var checkEdit = jQuery('.project_cost_code_nid').val();
		if(checkEdit == '') {
          jQuery.post( '/check-project-availablity/'+ getNumber +'/cost/'+ProNumber, function( data ) { 
            if(data.access == 0) {
              jQuery('.project-avail-status .text-danger').text(data.message);
              jQuery('.manager_cost_code').addClass('error')
              jQuery('.project-avail-status .text-success').text('');
              jQuery('.custom-submit-cost-code input').attr('disabled','disabled');
            }
            if(data.access == 1) {
              jQuery('.project-avail-status .text-danger').text('');  
              jQuery('.manager_cost_code').removeClass('error')
              jQuery('.project-avail-status .text-success').text('');
              jQuery('.custom-submit-cost-code input').removeAttr('disabled');
            }          
          });
		}
      });
    }
	// ==== Work for Default Milestone page ==== //
	else if(getPath == '/program/add-default-milestone') {
	  jQuery('.edit-milestone-detail', context).click(function (e) {
		jQuery('#project_default_milestone_main_container').attr('for','open');
		jQuery('#project_default_milestone_main_container').attr('data','edit');			
		jQuery('#project_default_milestone_main_container').show();
		jQuery('.custom-submit-default_milestone').show();
        e.preventDefault();
	    var projectId = jQuery(this).attr('for');
	    jQuery('.project-sel-default-milestone').val(projectId).trigger('change');
	    jQuery('.project_default_milestone_nid').val(projectId);	  
	     jQuery('html, body').animate({
           scrollTop: "0px"
	     }, 800); 
      });
	  var dmId = getUrlParameter('dm');
	  if(dmId) { 
	    jQuery('.project-sel-default-milestone').val(dmId).trigger('change');
		jQuery('.project_default_milestone_nid').val(dmId);
		jQuery('#project_default_milestone_main_container').attr('for','open');
		jQuery('#project_default_milestone_main_container').attr('data2','querystring');
		jQuery('#project_default_milestone_main_container').show();
		jQuery('.custom-submit-default_milestone').show();
	  } 
	}
	else if(getPath == '/program/manage-asset-category') {
	  jQuery('.page__title').hide();	
      jQuery('.edit-asset-setting-detail', context).click(function (e) {
	    jQuery('#project_asset_settings_main_container').attr('for','open');
        jQuery('#project_asset_settings_main_container').attr('data','edit');
	    e.preventDefault();
	    var projectId = jQuery(this).attr('for');
	    jQuery('.project-manage-category-sel').val(projectId).trigger('change');
        jQuery('.asseting_edit_id').val(projectId);    
        jQuery('html, body').animate({
          scrollTop: "0px"
        }, 800); 
      });    
    }
	else if(getPath == '/program/location') {
      jQuery('.page__title').hide();	
    }
	else if(getPath == '/program/lock-milestone-date') {
	jQuery('.page__title').hide();	
    jQuery('.edit-lock-milestone-detail', context).click(function (e) {
      jQuery("input:checkbox.milestone_status").click(function() {
        if(!jQuery(this).is(":checked")) {
          jQuery('.custom-submit-default_milestone_lock_date').hide();
          jQuery('.simple-button-for-lock').show();
        }
        else {
          jQuery('.custom-submit-default_milestone_lock_date').show();
          jQuery('.simple-button-for-lock').hide();
        }
      });
	  jQuery('#project_default_milestone_lock_date_main_container').attr('for','open');
      jQuery('#project_default_milestone_lock_date_main_container').attr('data','edit');
	  e.preventDefault();
	  var projectId = jQuery(this).attr('for');
	  jQuery('.project-sel-default-milestone-lock').val(projectId).trigger('change');
      jQuery('.project_default_milestone_lock_date_nid').val(projectId);    
      jQuery('html, body').animate({
        scrollTop: "0px"
      }, 800); 
    });
    var dmId = getUrlParameter('md');
    if(dmId) { 
      jQuery('.project-sel-default-milestone-lock').val(dmId).trigger('change');
      jQuery('.project_default_milestone_lock_date_nid').val(dmId);
      jQuery('#project_default_milestone_lock_date_main_container').attr('for','open');
      jQuery('#project_default_milestone_lock_date_main_container').attr('data2','querystring');
      jQuery("input:checkbox.milestone_status").click(function() {
      if(!jQuery(this).is(":checked")) {
        jQuery('.custom-submit-default_milestone_lock_date').hide();
        jQuery('.simple-button-for-lock').show();
      }
      else {
        jQuery('.custom-submit-default_milestone_lock_date').show();
        jQuery('.simple-button-for-lock').hide();
      }
    });
    } 
  }
    // For estimate edit cost code section
	var estId = jQuery('.project_est_details_nid').val();	
	if(!isNaN(estId)) {
	  jQuery('.project-program-sel-details').val(estId).trigger('change');
 	}							
	jQuery('.project-program-sel', context).change(function (e) {
	  var projectId = $(this).val();	  	
	  jQuery('.project_ref_nid').val(projectId);	  	  
	  jQuery('.new-budget-cost-code-link').attr('href', 'cost-code-details/'+projectId+'/nojs');
	});
  }
};

jQuery(document).ready(function(e) {  
  setTimeout(function() {
        jQuery(".messages--status").remove()
      }, 20000);	
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
	    return("$-" + formatted + ((parts) ? "." + parts[1].substr(1, 2) : ""));	  	    	  	
	  }
	  else {
	    return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));  
	  }	  
    };
	jQuery('.commit-amt-quarter-three').trigger('keyup');
    // =========================================
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
	// Column resizer work end here
	jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
  	    var urlajax = ajaxOptions.url;
  	    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData")){
		  if(ajaxOptions.extraData._triggering_element_name ==="select-commitment" || ajaxOptions.extraData._triggering_element_name ==="select-spending" || ajaxOptions.extraData._triggering_element_name ==="get-commitment" || ajaxOptions.extraData._triggering_element_name ==="get-spending") {		
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
	    }
	 }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
  	      var urlajax = ajaxOptions.url;
  	     if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData")){
		   if(ajaxOptions.extraData._triggering_element_name ==="select-commitment" || ajaxOptions.extraData._triggering_element_name ==="select-spending" || ajaxOptions.extraData._triggering_element_name ==="get-commitment" || ajaxOptions.extraData._triggering_element_name ==="get-spending") {	
		   jQuery.unblockUI();
		   if(jQuery('.commitment-number-filter select').val()) {
			  jQuery('.commitment-number-filter select').trigger('change');
			}
            if(jQuery('.company-name-filter select').val()) {
			  jQuery('.company-name-filter select').trigger('change');
			}
			if(jQuery('.record-type-filter select').val()) {
			  jQuery('.record-type-filter select').trigger('change');
			}
			if(jQuery('.cost-code-filter select').val()) {
			  jQuery('.cost-code-filter select').trigger('change');
			}
		   var rowCount = jQuery('.m6connect-custom-program-table tr').length;
		   if(rowCount > 2) {
			 var pageId = jQuery('.datatable_page_id').val();
			 var pageNumber = jQuery('.page_number_id').val();
			 //var pageId = jQuery('.datatable_page_id').val();
			 var getLastPager = 50;
			 var getLastPageNumber = 1;
			 if(pageId) {
			   getLastPager = pageId;
			 }
       var rowcount_dt = jQuery('.dataTables_wrapper').length;
       if(rowcount_dt == 0) {
		    jQuery('table.m6connect-custom-program-table').DataTable({
        	//"aLengthMenu": [[10, 20, 50, 100, -1], [10, 20, 50, 100, "All"]],
    			//"pageLength": getLastPager,
				  "bPaginate": false,
				  "paging": false,
				  "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
				  "searching": false,
				  "dom": 'Rfrtlip',
    		});
       }
			jQuery('.dataTables_length select').change(function () {
			  Drupal.attachBehaviors(jQuery('body'));  
	     	  var pageId = jQuery(this).val();
			  jQuery('.datatable_page_id').val(pageId);		
	  		});
			if(pageNumber) {
			  getLastPageNumber = pageNumber;
			   var pageNos = jQuery(".dataTables_paginate span a");
			   pageNos.each(function (index) {
  			     var page = jQuery(this).text();
  			     if(page == getLastPageNumber) {
    			   jQuery(this).trigger('click');
  				 }
			   });
			 }		 
		   }
		   var cCode = jQuery('.invoice_cost_code').val();
		   var getInvId = jQuery('.project_spending_nid').val();
		   if(getInvId != 0) {
		     jQuery('.invoice_commitment').trigger('change');
		   }
		   /*if(cCode == '0') {
		     jQuery('.invoice_commitment').trigger('change');
		   }*/
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
       }
      });	  
	   jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
  	    var urlajax = ajaxOptions.url;
		//console.log(ajaxOptions); 
  	    if (urlajax.indexOf("/load-spending-forecast") === 0){
			jQuery.blockUI({
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
	    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
  	      var urlajax = ajaxOptions.url;
  	      if (urlajax.indexOf("/load-spending-forecast") === 0){
		    jQuery.unblockUI();
	     }
      });	  
  var getPath = window.location.pathname;
  // Check for estimate approve status before submit estimate form
  // in approve or pending status.
  jQuery('.main-estimate-submit-call').click(function (e) {
	  e.preventDefault();
	  var getCurrStatus = jQuery('.estimate_status').val();
	  if(getCurrStatus == 'approved') {
	    var projectNid = jQuery('.project-program-sel').val();
	    jQuery.post( '/estimate-approve-status-title/'+projectNid, function( data ) {
	    var editEST = jQuery('.project_est_ref_nid').val();
		var currntNid = jQuery('.project_est_ref_nid').val();
	    if(data.appvovedNodeName != '' && !isNaN(data.approvedNid) && data.appvovedNodeName != null && data.approvedNid != currntNid){
		  jQuery('.approve_status_previous_approved').val(data.approvedNid);
		  jQuery('#estimate-approve-change-dialog').html('<div class="text-center" style="padding-bottom:25px; text-align:justify;"><strong><p>Would you like to make this budget your Approved Budget ?  </p><p><span style="color:#0F75BC">"'+data.appvovedNodeName+ '" </span>is already approved.</p><p>This may have an effect on your commitments with regard to the cost codes selected from the previous budget.  If this new budget cost codes are different than the previous then you will need to navigate to the Commitments tab and make the new cost code assignments for the affected Commitments.</strong></p></div>');
		  jQuery('#estimate-approve-change-dialog').dialog('open');
		  e.preventDefault();
		  return false;
		}
		else{
		  jQuery('#program-modify-estimates-form').trigger('submit');
		  return true;
		}
	  });
	  }
	  else {
	    jQuery('#program-modify-estimates-form').trigger('submit');
	  }
	});			
   // ==== End for estiamte page approve status. ==== //
  // ========================================
  // Commitment from etc confirmation dialog
  jQuery('.custom-submit-commit').click(function (e) {
	  e.preventDefault();
	  var getEtcStatus = jQuery('.etc_data_status').val();
	  if(getEtcStatus == '1') {
		var arr = [], str;
		jQuery('.etc-loaded-data-inner .load-etc-number').each(function(){
    	  var values = jQuery(this).text();
   		  arr.push(values);
		});
	    var etcNo = arr.join(',');  
		var dataContainer = jQuery('#etc-loaded-data-container').html();
		jQuery('.etc-loaded-data-container-area').val(dataContainer);		
		jQuery('#from-etc-dialog-container').html('<div class="etc-data-call text-center" style="padding-bottom:25px; text-align:justify;"><strong><p>Would you like to delete '+etcNo +' or just remove from the ETC forecast (uncheck In ETC)?</p></strong></div>');
		jQuery('#from-etc-dialog-container').dialog('open');
		e.preventDefault();
		return false;		
	  }
	  else {
	    jQuery('#program-modify-commitment-form').trigger('submit');
	  }
	});	
  // ==== End for commitment from etc ==== //
  // Work for default milestone duration popup  
  jQuery('.lock-milestone-detail').unbind('click').bind('click',function (e) {
    var milestoneRow = jQuery(this).closest("tr");
    var projectName = milestoneRow.find(".pro-name").text();
    e.preventDefault();
    var mileId = jQuery(this).attr('for');  
    jQuery('.project-sel-default-milestone-lock').val(mileId).trigger('change');
    jQuery('.project_default_milestone_lock_date_nid').val(mileId);
    jQuery('#lock-milestone-duration-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong><p>You are about to lock original dates for  the Project:'+projectName+'. </p></strong><p>Press continue to confirm or click Cancel to abort this operation.</p><input type="radio" name="lock_duration" class="lock-duration" value="lock" style="display:none;" checked="checked"><input type="hidden" name="milestone-id" class="milestone-id" value="'+mileId+'"></div>');
    jQuery('#lock-milestone-duration-dialog').dialog('open');
    e.preventDefault();
    return false;       
  });
  
  jQuery('.lock-milestone-submit-5').unbind('click').bind('click',function (e) {
    var milestoneRow = jQuery(this).closest("tr");
    var projectName = milestoneRow.find(".pro-name").text();
    e.preventDefault();
    var mileId = jQuery(this).attr('for');  
    jQuery('.project-sel-default-milestone-lock').val(mileId).trigger('change');
    jQuery('.project_default_milestone_lock_date_nid').val(mileId);
    jQuery('#lock-milestone-duration-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong><p>You are about to unlock original dates for 5 days for the Project:'+projectName+'. </p></strong><p>Press continue to confirm or click Cancel to abort this operation.</p><input type="radio" name="lock_duration" class="lock-duration" value="5" style="display:none;" checked="checked"><input type="hidden" name="milestone-id" class="milestone-id" value="'+mileId+'"></div>');
    jQuery('#lock-milestone-duration-dialog').dialog('open');
    e.preventDefault();
    return false;       
  });
  
  jQuery('.lock-milestone-submit-10').unbind('click').bind('click',function (e) {
    var milestoneRow = jQuery(this).closest("tr");
    var projectName = milestoneRow.find(".pro-name").text();    
    e.preventDefault();
	var mileId = jQuery(this).attr('for');
    jQuery('#lock-milestone-duration-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong><p>You are about to unlock original dates permanently for the Project:'+projectName+'. </p></strong><p>Press continue to confirm or click Cancel to abort this operation.</p><input type="radio" name="lock_duration" class="lock-duration" value="10" style="display:none;" checked="checked"><input type="hidden" name="milestone-id" class="milestone-id" value="'+mileId+'"></div>');
	jQuery('#lock-milestone-duration-dialog').dialog('open');
    e.preventDefault();
    return false;       
  });
  if(getPath == '/program/projects') {
    // get project id from query string.
	var proId = getUrlParameter('pid');
	if(proId) { 
	  jQuery('.project_id_ref').val(proId);
	  jQuery('.project_programe_main_pro').val(proId).trigger('change');
	}
  }
  // Work for commitment slide
  if(getPath == '/program/commitments') {	 
   jQuery('#project_commitment_main_container').hide();
	jQuery('#main-class').hide();	
	jQuery('.custom-submit-commitment').hide();	  
	jQuery('.custom-submit-commitment-reset').hide();
	jQuery('#project_commitment_main_container').attr('for','closed');
		  	 
    jQuery('#commitment_number_input_cust').removeAttr('data');
	jQuery('#commitment_number_select_cust').removeAttr('data');	  
	jQuery('.project-program-commitment-sel').trigger('change');
	// Ajax request to get the cost code list by project
	// And update cost code option in select list	
	var ProId = jQuery('.project-program-commitment-sel').val();
	   jQuery.post( '/get-cost-code/'+ProId, function( data ) {
	    jQuery('.cost_code_update').empty();	
	    jQuery.each(data,function(key, value) {
		  var opt = jQuery('<option>');
    	  opt.val(key).text(value);
    	  opt.appendTo('.cost_code_update');	
		});
		jQuery(".cost_code_update").prepend("<option value selected='selected'>- None -</option>");	
	  })
	jQuery('.project-program-commitment-sel').change(function () {
	  // Apply ui blocker
	  jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
  	    var urlajax = ajaxOptions.url;
  	    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-commitment"){
         jQuery.blockUI({
                //theme:     true,
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
  	     if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="select-commitment"){
           jQuery.unblockUI();
       }
      });	
	  jQuery('.project-details-right').css('pointer-events', 'auto');
	  /*jQuery('#main-class').css('display', 'block');
	  jQuery('#main-class').css('pointer-events', 'auto');*/
	  var ProId = jQuery(this).val();
	  var pid = getUrlParameter('pid');
	  if(pid) {
	    if(pid != ProId) {
		  window.location.href="/program/commitments?pid="+ProId;
		}
	  }  
	  jQuery.post( '/get-cost-code/'+ProId, function( data ) {
	    jQuery('.cost_code').empty();	
	    jQuery.each(data,function(key, value) {
		  var opt = jQuery('<option>');
    	  opt.val(key).text(value);
    	  opt.appendTo('.cost_code');	
		});
		jQuery(".cost_code").prepend("<option value selected='selected'>- None -</option>");
		
		jQuery('.cost_code_update').empty();	
	    jQuery.each(data,function(key, value) {
		  var opt = jQuery('<option>');
    	  opt.val(key).text(value);
    	  opt.appendTo('.cost_code_update');	
		});
		jQuery(".cost_code_update").prepend("<option value selected='selected'>- None -</option>");		
	  })
	});	
	/*jQuery('.cost_code').change(function () {
	  var getCC = jQuery(this).val();
	  jQuery('.ws_code').val(getCC);
	});*/	
	// Functionality for commitment button
	var ProId = jQuery('.project-program-commitment-sel').val();
	jQuery('.new-record-cus-btn').attr('for', ProId);			
    jQuery('.new-commitment-link').click(function (e) {
	  e.preventDefault();
	  var status = jQuery('#project_commitment_main_container').attr('for');
	  var dataAttr = jQuery('#project_commitment_main_container').attr('data');
	  if(status == 'open' && jQuery('#project_commitment_main_container').attr('data') == 'edit') {	 
	    jQuery('#project_commitment_main_container').removeAttr('data'); 
		var getProId = jQuery('.new-record-cus-btn').attr('for');
		//jQuery('.project-program-commitment-sel').val(getProId).trigger('change');
		jQuery('.project-program-sel-commitment').val('').trigger('change');
		jQuery('#project_commitment_main_container').show();
		jQuery('#main-class').show();	
		jQuery('.custom-submit-commitment').show();
		jQuery('.custom-submit-commitment-reset').show();
	  }
	  else if(status == 'closed' && jQuery('#project_commitment_main_container').attr('data') == 'edit') {	 
	    jQuery('#project_commitment_main_container').removeAttr('data'); 
		var getProId = jQuery('.new-record-cus-btn').attr('for');
		//jQuery('.project-program-commitment-sel').val(getProId).trigger('change');
		jQuery('.project-program-sel-commitment').val('').trigger('change');
		jQuery('#project_commitment_main_container').show();
		jQuery('#main-class').show();	
		jQuery('.custom-submit-commitment').show();
		jQuery('.custom-submit-commitment-reset').show();
	  }
	  else if(status == 'open' && jQuery('#project_commitment_main_container').attr('data2') == 'querystring') {
		var pid = getUrlParameter('pid');
	    if(!isNaN(pid)) { 
		  window.location.href="/program/commitments?pid="+pid;
		}	    
	  }	
	  else if(status == 'closed') {
	    jQuery('#project_commitment_main_container').attr('for','open');
		jQuery('#project_commitment_main_container').show();
		jQuery('.custom-submit-commitment').show();
		jQuery('.custom-submit-commitment-reset').show();
        jQuery('#main-class').show();
      }
	  else if(status == 'open') {
	    if(jQuery('.etc_data_status').val() == 1) {
		  var getProId = jQuery('.project-program-commitment-sel').val();
		  jQuery('.project-program-commitment-sel').val(getProId).trigger('change');
		  jQuery('#project_commitment_main_container').show();
		  jQuery('#main-class').show();	
		  jQuery('#alert-container-section').show();
		  jQuery('.custom-submit-commitment').show();
		  jQuery('.custom-submit-commitment-reset').show();  
		} 
		else { 
	      jQuery('#project_commitment_main_container').hide();
	      jQuery('#project_commitment_main_container').attr('for','closed'); 
	      jQuery('.custom-submit-commitment').hide();
		  jQuery('.custom-submit-commitment-reset').hide();
		  jQuery('#main-class').hide();
		}
	  }
	  else if(status == 'open' && jQuery('#project_commitment_main_container').attr('data') == 'edit') { 
	    jQuery('#project_commitment_main_container').removeAttr('data'); 
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    //jQuery('.project-program-commitment-sel').val(getProId).trigger('change');
		jQuery('.project-program-sel-commitment').val('').trigger('change');
	    jQuery('#project_commitment_main_container').show();
	    jQuery('.custom-submit-commitment').show();
		jQuery('.custom-submit-commitment-reset').show();
		jQuery('#main-class').show();
	  }
	  else if(jQuery( "#project_commitment_main_container" ).attr('data') == 'edit') {
	    var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
	    //jQuery('.project-program-commitment-sel').val(getScheduleProId).trigger('change');
		jQuery('.project-program-sel-commitment').val('').trigger('change');
	    jQuery('#project_commitment_main_container').show();
	    jQuery('#project_commitment_main_container').attr('for','open'); 
	    jQuery('.custom-submit-commitment').show();
		jQuery('.custom-submit-commitment-reset').show();
		jQuery('#main-class').show();
      }
    });	
	var pid = getUrlParameter('pid');
	if(pid) { 
	  jQuery('.project-program-commitment-sel').val(pid).trigger('change');
	  jQuery('#project_commitment_main_container').attr('for','open'); 
	  jQuery('#project_commitment_main_container').show();
	  jQuery('#main-class').show();	
	  jQuery('.custom-submit-commitment').show();
	  jQuery('.custom-submit-commitment-reset').show();
	}
	else {	  	
	  jQuery('#project_commitment_main_container').hide();
	  jQuery('#main-class').hide();	
	  jQuery('.custom-submit-commitment').hide();	  
	  jQuery('.custom-submit-commitment-reset').hide();
	  jQuery('#project_commitment_main_container').attr('for','closed');
	}
	var commitid = getUrlParameter('cid');
	if(commitid) { 
	  jQuery('.project-program-sel-commitment').val(commitid).trigger('change');
	  jQuery('#project_commitment_main_container').attr('for','open');
	  jQuery('#project_commitment_main_container').attr('data2','querystring');
	  jQuery('#project_commitment_main_container').show();
	  jQuery('.project_commitment_nid').val(commitid);
	} 	 
	// Functionalty for commitment button ends here    
    /*jQuery.blockUI({
                //theme:     true,
                baseZ: 2000,
                message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait while information are loading...</strong></div>',
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
			setTimeout(jQuery.unblockUI, 15000);*/
  }
  
  
  // Work for Estimate slide
  if(getPath == '/program/estimates') { 
    var ProId = jQuery('.project-program-sel').val();
	jQuery('.new-record-cus-btn').attr('for', ProId);			
    jQuery('.new-budget-link').click(function (e) {
	  e.preventDefault();
	  var status = jQuery('#project_estimate_main_container').attr('for');
	  var dataAttr = jQuery('#project_estimate_main_container').attr('data');
	  if(status == 'open' && jQuery('#project_estimate_main_container').attr('data') == 'edit') {	 
	    jQuery('#project_estimate_main_container').removeAttr('data'); 
		var getProId = jQuery('.new-record-cus-btn').attr('for');
		//jQuery('.project-program-sel').val(getProId).trigger('change');
		window.location.href="/program/estimates?pid="+getProId;
		jQuery('.project_est_ref_nid').val('');
		jQuery('#project_estimate_main_container').show();
		jQuery('.program-project-sub-menu-links').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
	  }
	  else if(status == 'open' && jQuery('#project_estimate_main_container').attr('data2') == 'querystring') {
		var pid = getUrlParameter('pid');	    
		window.location.href="/program/estimates?pid="+pid;		
	  }	
	  else if(status == 'closed' && jQuery('#project_estimate_main_container').attr('data') == 'edit') {	 
	    jQuery('#project_estimate_main_container').removeAttr('data'); 
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-sel').val(getProId).trigger('change');
	    jQuery('#project_estimate_main_container').show();
		jQuery('.program-project-sub-menu-links').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
	  }	 
	  else if(status == 'closed') {
	    jQuery('#project_estimate_main_container').attr('for','open');
		jQuery('#project_estimate_main_container').show();
		jQuery('.program-project-sub-menu-links').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
		
      }
	  else if(status == 'open') {
	    jQuery('#project_estimate_main_container').hide();
		jQuery('.program-project-sub-menu-links').hide();
		jQuery('.main-estimate-submit-call').hide();
		jQuery('.custom-submit-reset').hide();
	    jQuery('#project_estimate_main_container').attr('for','closed'); 
      }
	  else if(status == 'open' && jQuery('#project_estimate_main_container').attr('data') == 'edit') { 
	    jQuery('#project_estimate_main_container').removeAttr('data'); 
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-sel').val(getProId).trigger('change');
	    jQuery('#project_estimate_main_container').show();
		jQuery('.program-project-sub-menu-links').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
	  }
	  else if(jQuery( "#project_estimate_main_container" ).attr('data') == 'edit') {
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-sel').val(getProId).trigger('change');
	    jQuery('#project_estimate_main_container').show();
		jQuery('.program-project-sub-menu-links').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
	    jQuery('.project_estimate_main_container').attr('for','open'); 
      }
    });
	var pid = getUrlParameter('pid');
	if(!isNaN(pid)) { 
	  jQuery('#project_estimate_main_container').attr('for','open'); 
	  jQuery('#project_estimate_main_container').show();
	  jQuery('.program-project-sub-menu-links').show();
	  jQuery('.main-estimate-submit-call').show();
	  jQuery('.custom-submit-reset').show();
	  jQuery('.custom-submit-safety').show();		
	  
	  // Disable Action buttons
		jQuery('.project-action').css('pointer-events','none');
		jQuery('.est-load-budget').css('pointer-events','none');		  
		jQuery('.project-action button').css('background-image','linear-gradient(rgb(187, 179, 179) 0px, rgb(183, 178, 178) 100%)');
		jQuery('.project-action button').css('border-color','#eee');
	}
	else {
	  jQuery('#project_estimate_main_container').hide();
	  jQuery('.program-project-sub-menu-links').hide();
	  jQuery('.main-estimate-submit-call').hide();
	  jQuery('.custom-submit-reset').hide();
	  jQuery('#project_estimate_main_container').attr('for','closed');
	  //Enable action button
		jQuery('.project-action').css('pointer-events','auto');
		jQuery('.est-load-budget').css('pointer-events','auto');		  
	    jQuery('.project-action button').css('background-image','-webkit-linear-gradient(top,#5cb85c 0,#419641 100%)');
	    jQuery('.project-action button').css('border-color','#3e8f3e');	
	}
	jQuery('.project-program-sel').change(function () {
	  /*var getNewBudgetPro = jQuery(this).val();
	  var proIdAvail = getUrlParameter('pid');
	  if(proIdAvail) {
	    window.location.href="/program/estimates?pid="+getNewBudgetPro;
	  }*/
	  var commitid = getUrlParameter('bid');
	  if(!isNaN(commitid)) { 
	    jQuery('.project-program-sel-est-details').val(commitid).trigger('change');
	    jQuery('#project_estimate_main_container').attr('for','open');
	    jQuery('#project_estimate_main_container').attr('data2','querystring');
	    jQuery('#project_estimate_main_container').show();
		jQuery('.main-estimate-submit-call').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
	    jQuery('.project_est_ref_nid').val(commitid);
	  } 
	});
	// Functionalty for add new budget button ends here
  }    
  if(getPath == '/program/spending-forcast') {
    var spentFor = getUrlParameter('forecast');
	if(!spentFor) {
	  jQuery('.project_programe_spending_forcast_pro').trigger('change');
	}
    var getPreviousGrandTotal = 0;
	getPreviousGrandTotal = jQuery('.previous-year-grand-total').text().replace(/[^\d\.\-]/g, '');
	if(getPreviousGrandTotal != '') {
	  if(getPreviousGrandTotal < 0) {	
	  (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;">Previous Year Total :<span class="text-danger">'+format(getPreviousGrandTotal)+'</span></div>');
	  }
	  else {
	    (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;">Previous Year Total :'+format(getPreviousGrandTotal)+'</div>');
	  }
	}		    	    
  }
  // Work for spending slide
  
  
  // Work for schecule slide
  if(getPath == '/program/schedule') {
    jQuery('.project-schedule').hide();
	//jQuery('.status-mark').hide();
	jQuery('.program-schedule-status').change(function (e) {	  
	  var getStatus = jQuery(this).val();
	  if(getStatus == 'reds') {
		jQuery('.status-mark').show();   
	    jQuery('.status-mark').addClass('text-danger');		
		jQuery('.status-mark').removeClass('text-warning');
		jQuery('.status-mark').removeClass('text-success');
	  }else if(getStatus == 'yellows') {
		jQuery('.status-mark').show();  
		jQuery('.status-mark').removeClass('text-danger');
		jQuery('.status-mark').removeClass('text-success');
	    jQuery('.status-mark').addClass('text-warning');
		
      }else if(getStatus == 'greens') {
	    jQuery('.status-mark').show(); 
		jQuery('.status-mark').addClass('text-success');
		jQuery('.status-mark').removeClass('text-danger');
		jQuery('.status-mark').removeClass('text-warning');
	  }
	  else {
	    jQuery('.status-mark').hide();
	  }
	});
	
	var ProId = jQuery('.project-program-schedule-sel').val();
	jQuery('.new-record-cus-btn').attr('for', ProId);			
    jQuery('.new-schedule-link').click(function (e) {
	  e.preventDefault();
	  var status = jQuery('#project_program_schedule_main_container').attr('for');
	  var dataAttr = jQuery('#project_program_schedule_main_container').attr('data');
	  
	  if(status == 'open' && jQuery('#project_program_schedule_main_container').attr('data') == 'edit') {	 
	    jQuery('#project_program_schedule_main_container').removeAttr('data'); 
		var getProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-schedule-sel').val(getProId).trigger('change');
		jQuery('#project_program_schedule_main_container').show();
		jQuery('.program-schedule-status-btn').show();
		jQuery('.custom-submit-schedule-reset').show();
		jQuery('#project_program_schedule_main_container').css('overflow', 'visible');
		//jQuery('.custom-submit-safety').show();
	  }
	  else if(status == 'open' && jQuery('#project_program_schedule_main_container').attr('data2') == 'querystring') {
		var pid = getUrlParameter('pid');	    
		window.location.href="/program/schedule?pid="+pid;		
	  }	
	  else if(status == 'closed') {
	    jQuery('#project_program_schedule_main_container').attr('for','open');
		jQuery('#project_program_schedule_main_container').show();
		jQuery('.program-schedule-status-btn').show();
		jQuery('.custom-submit-schedule-reset').show();
		jQuery('#project_program_schedule_main_container').css('overflow', 'visible');
		//jQuery('.custom-submit-safety').show();
      }
	  else if(status == 'open') {
	    jQuery('#project_program_schedule_main_container').hide();
	    jQuery('#project_program_schedule_main_container').attr('for','closed'); 
		jQuery('.program-schedule-status-btn').hide();
		jQuery('.custom-submit-schedule-reset').hide();
	    //jQuery('.custom-submit-safety').hide();
      }
	  else if(status == 'open' && jQuery('#project_program_schedule_main_container').attr('data') == 'edit') { 
	    jQuery('#project_program_schedule_main_container').removeAttr('data'); 
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-schedule-sel').val(getProId).trigger('change');
	    jQuery('#project_program_schedule_main_container').show();
		jQuery('.program-schedule-status-btn').show();
		jQuery('.custom-submit-schedule-reset').show();
		jQuery('#project_program_schedule_main_container').css('overflow', 'visible');
	    //jQuery('.custom-submit-safety').show();
	  }
	  else if(jQuery( "#project_program_schedule_main_container" ).attr('data') == 'edit') {
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-safety-sel').val(getProId).trigger('change');
	    jQuery('#project_program_schedule_main_container').show();
		jQuery('.program-schedule-status-btn').show();
		jQuery('#project_program_schedule_main_container').css('overflow', 'visible');
	    jQuery('#project_program_schedule_main_container').attr('for','open'); 
	    jQuery('.custom-submit-safety').show();
		jQuery('.custom-submit-schedule-reset').show();
      }
    });
	var pid = getUrlParameter('pid');
	if(!isNaN(pid)) { 
	  jQuery('.project-program-schedule-sel').val(pid).trigger('change');
	  jQuery('#project_program_schedule_main_container').attr('for','open'); 
	  jQuery('#project_program_schedule_main_container').show();
	  jQuery('.program-schedule-status-btn').show();
	  jQuery('.custom-submit-schedule-reset').show();
	  jQuery('#project_program_schedule_main_container').css('overflow', 'visible');
	  //jQuery('.custom-submit-safety').show();
	}
	else {
	  jQuery('.project-program-schedule-sel').trigger('change');	
	  jQuery('#project_program_schedule_main_container').hide();
	  jQuery('.program-schedule-status-btn').hide();
	  jQuery('.custom-submit-schedule-reset').hide();
	  jQuery('#project_program_schedule_main_container').attr('for','closed');
	  //jQuery('.custom-submit-safety').show();
	}	
  }
  
  
  // work for etc tab
  if(getPath == '/program/etc') {	  	
    // Get list of commitment by type
	var ProId = jQuery('.project-program-etc-sel').val();
	jQuery.post( '/get-cost-code/'+ProId, function( data ) {
      jQuery('.etc_cost_code').empty();   
      jQuery.each(data,function(key, value) {
        var opt = jQuery('<option>');
        opt.val(key).text(value);
        opt.appendTo('.etc_cost_code'); 
      });
      jQuery(".etc_cost_code").prepend("<option value selected='selected'>Select Cost Code</option>");
    });
	
	
	jQuery.post( '/get-commitment-list-project/'+ProId, function( data ) {
	  jQuery('.etc_commitment').empty();	
	  jQuery(".etc_commitment").prepend("<option value=''>Select Commitment</option>").val('');
	  jQuery.each(data,function(key, value) {
	    var opt = jQuery('<option>');
    	opt.val(key).text(value);
    	opt.appendTo('.etc_commitment');
	  });
	});     
    jQuery('.project-program-etc-sel').trigger('change');	
	jQuery('.project-program-etc-sel').change(function (e) {
	  var ProId = jQuery(this).val();	  
	  // Ajax request for get the list of commitment by project
	  jQuery.post( '/get-commitment-list-project/'+ProId, function( data ) {
	    jQuery('.etc_commitment').empty();	
		jQuery(".etc_commitment").prepend("<option value=''>Select Commitment</option>").val('');
	    jQuery.each(data,function(key, value) {
		  var opt = jQuery('<option>');
    	  opt.val(key).text(value);
    	  opt.appendTo('.etc_commitment');
		});
	  })
	  // Ajax request for get the list of cost code by project
	  jQuery.post( '/get-cost-code/'+ProId, function( data ) {
	    jQuery('.etc_cost_code').empty();	
	    jQuery.each(data,function(key, value) {	
		  var opt = jQuery('<option>');
    		opt.val(key).text(value);
    		opt.appendTo('.etc_cost_code');	
		});
	  })	 
	  // Get list of commitment by type
	  /*jQuery('.etc_commitment_type').change(function(e){
	    var commitmentType = jQuery(this).val();
	      jQuery.post( '/get-commitment-list-by-type/'+ commitmentType +'/'+ ProId, function( data ) {
		    jQuery('.etc_commitment').empty();	
		    jQuery(".etc_commitment").prepend("<option value=''>Select Commitment</option>").val('');
	        jQuery.each(data,function(key, value) {
		      var opt = jQuery('<option>');
    	      opt.val(key).text(value);
    	      opt.appendTo('.etc_commitment');
		    });
	      })
	  });*/	  
	});
	/*jQuery('.etc_commitment').change(function(e){
	  var getCommitId = jQuery(this).val();	  
	  if(!isNaN(getCommitId)) {
	    jQuery.post( '/get-cost-code/'+getCommitId, function( data ) {		  
		  jQuery('.etc_cost_code').empty();
	      jQuery.each(data,function(key, value) {
	        var opt = jQuery('<option>');
    	    opt.val(key).text(value);
    	    opt.appendTo('.etc_cost_code');				
			jQuery('.etc_cost_code_value').val(key);
	      });
	    })
		jQuery.post( '/get-commitment-type/'+getCommitId, function( data ) {
		  jQuery('.etc_commitment_type option[value="'+data).attr("selected", true);
		  jQuery('.etc_commitment_type').attr('disabled', 'disabled');
		  jQuery('.etc_commitment_type_value').val(data);					  
	    })
	  }
	});*/
	jQuery('.etc_commitment').change(function(e){
	   var getCommitId = jQuery(this).val();
	   if(getCommitId) {
	     jQuery.post( '/get-cost-code/'+getCommitId, function( data ) {
		   if(data != 0) { 
		     jQuery.each(data,function(key, value) {
			   jQuery('.etc_cost_code').empty();	
			   jQuery(".etc_cost_code").prepend("<option value=''>Select Cost Code</option>").val('');
			   jQuery.each(data,function(key, value) {
			     var opt = jQuery('<option>');
			     opt.val(key).text(value);
			     opt.appendTo('.etc_cost_code');
			   });
		    });
		   }
		   else {
		     var ProId = jQuery('.project-program-etc-sel').val();
	  		 // Ajax request for get the list of cost code by project
	  	     jQuery.post( '/get-cost-code/'+ProId, function( data ) {
	    	   jQuery('.etc_cost_code').empty();	
	    	   jQuery.each(data,function(key, value) {	
		  	     var opt = jQuery('<option>');
    			 opt.val(key).text(value);
    			 opt.appendTo('.etc_cost_code');	
			   });
			 jQuery(".etc_cost_code").prepend("<option value selected='selected'>Select Cost Code</option>");
	        });
		   }
	    })
	  }
	  else {
	    var ProId = jQuery('.project-program-etc-sel').val();
	  	// Ajax request for get the list of cost code by project
	  	jQuery.post( '/get-cost-code/'+ProId, function( data ) {
	      jQuery('.etc_cost_code').empty();	
	      jQuery.each(data,function(key, value) {	
		    var opt = jQuery('<option>');
    	    opt.val(key).text(value);
    	    opt.appendTo('.etc_cost_code');	
		  });
		  jQuery(".etc_cost_code").prepend("<option value selected='selected'>Select Cost Code</option>");
	    });
	  }
    });
	jQuery('.etc_cost_code').change(function () {	  
	  jQuery('.etc_cost_code_value').val(jQuery(this).val());
	});
	
	
	
	jQuery('.new-etc-link').click(function (e) {
	  e.preventDefault();
	  var status = jQuery('.project_etc_main_cust').attr('for');
	  var dataAttr = jQuery('.project_etc_main_cust').attr('data');
      if(status == 'open' && jQuery('.project_etc_main_cust').attr('data') == 'edit') {
	    jQuery('.project_etc_main_cust').removeAttr('data'); 
		var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-etc-sel').val(getScheduleProId).trigger('change');		
		jQuery('#project_etc_main_container').show();
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();		
	  }
	  if(status == 'open' && jQuery('.project_etc_main_cust').attr('data2') == 'querystring') {
		var pid = getUrlParameter('pid');
	    if(!isNaN(pid)) { 
		  window.location.href="/program/etc?pid="+pid;
		}	    
	    jQuery('.project_etc_main_cust').removeAttr('data'); 
		jQuery('.project_etc_main_cust').removeAttr('data2'); 
		var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-etc-sel').val(getScheduleProId).trigger('change');		
		jQuery('#project_etc_main_container').show();
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();		
	  }	  
	  else if(status == 'closed' && jQuery('.project_etc_main_cust').attr('data') == 'edit') {	 
	    jQuery('#project_etc_main_cust').removeAttr('data'); 
		var getProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-etc-sel').trigger('change');
		jQuery('#project_etc_main_container').show();
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();		
	  }
	  else if(status == 'closed') {
		jQuery('.project_etc_main_cust').attr('for','open'); 
		jQuery('.project_etc_main_cust').show();
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();	
	  }
	  else if(status == 'open') {
	    jQuery('#project_etc_main_container').hide();
		jQuery('.project_etc_main_cust').attr('for','closed'); 
		jQuery('.custom-submit-etc').hide();
		jQuery('.program-etc-status-btn').hide();	
	  }
	  else if(status == 'open' && jQuery('.project_etc_main_cust').attr('data') == 'edit') {		  
		jQuery('.project_etc_main_cust').removeAttr('data'); 
		var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-etc-sel').val(getScheduleProId).trigger('change');		
		jQuery('#project_etc_main_container').show();
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();		
	  }	  
	  else if(jQuery( ".project_etc_main_cust" ).attr('data') == 'edit') {
	    var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-etc-sel').val(getScheduleProId).trigger('change');
		jQuery('#project_etc_main_container').show();
		jQuery('.project_etc_main_cust').attr('for','open'); 
		jQuery('.custom-submit-etc').show();
		jQuery('.program-etc-status-btn').show();			
	  }	  
	});	
	var pid = getUrlParameter('pid');
	if(!isNaN(pid)) { 
	  jQuery('.project_etc_main_cust').attr('for','open'); 
	  jQuery('.project_etc_main_cust').show();
	  jQuery('.custom-submit-etc').show();
	  //jQuery('.program-etc-status-btn').show();	
	} 
	else {
	  //jQuery('.status-mark').hide();
	  jQuery('.project_etc_main_cust').hide();	  
	  jQuery('.custom-submit-etc').hide();
	  jQuery('.program-etc-status-btn').hide();	
	  jQuery('.project_etc_main_cust').attr('for','closed');
	}	
	
	 var commitid = getUrlParameter('eid');
	 if(!isNaN(commitid)) { 
	   jQuery('.project-program-sel-etc').val(commitid).trigger('change');
	   jQuery('.project_etc_nid').val(commitid);
	   jQuery('.project_etc_main_cust').attr('for','open');
	   jQuery('.project_etc_main_cust').attr('data','edit');
	   jQuery('.project_etc_main_cust').attr('data2','querystring');
		jQuery('.project_etc_main_cust').show();
		jQuery('.custom-submit-etc').show();
	  } 
	
	
	jQuery('.program-etc-status').change(function (e) {
	  var getStatus = jQuery(this).val();
	  if(getStatus == 'reds') {
	    jQuery('.status-mark').show();   
	    jQuery('.status-mark').addClass('text-danger');		
		jQuery('.status-mark').removeClass('text-warning');
		jQuery('.status-mark').removeClass('text-success');
	  }
	  else if(getStatus == 'yellows') {
	    jQuery('.status-mark').show();  
		jQuery('.status-mark').removeClass('text-danger');
		jQuery('.status-mark').removeClass('text-success');
	    jQuery('.status-mark').addClass('text-warning');		
      }
	  else if(getStatus == 'greens') {
	    jQuery('.status-mark').show(); 
		jQuery('.status-mark').addClass('text-success');
		jQuery('.status-mark').removeClass('text-danger');
		jQuery('.status-mark').removeClass('text-warning');
	  }
	  else {
	    jQuery('.status-mark').hide();
	  }
	});    
  }  
  if(getPath == '/program/assets' || getPath == '/program/cm/assets') {
	jQuery('.page__title').hide();
    jQuery('.project-program-assets-sel').trigger('change');
	var ProId = jQuery('.project-program-assets-sel').val();
    jQuery('.new-record-cus-btn').attr('for', ProId);     
    jQuery('.new-assets-link').click(function (e) {
      e.preventDefault();
      var status = jQuery('#project_program_asset_main_container').attr('for');
      var dataAttr = jQuery('#project_program_asset_main_container').attr('data');
      if(status == 'open' && jQuery('#project_program_asset_main_container').attr('data') == 'edit') {   
        jQuery('#project_program_asset_main_container').removeAttr('data'); 
        var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
        jQuery('.project-program-sel-assets').val('').trigger('change');    
        jQuery('#project_program_asset_main_container').show();
        jQuery('#project_program_asset_main_container').show();
        jQuery('.custom-reset-button-schedule-div').show();    
      }
      else if(status == 'closed' && jQuery('#project_program_asset_main_container').attr('data') == 'edit') {  
        jQuery('#project_program_asset_main_container').removeAttr('data'); 
        var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
        jQuery('.project-program-sel-assets').val('').trigger('change');    
        jQuery('#project_program_asset_main_container').show();
        jQuery('.custom-reset-button-schedule-div').show();    
      }
      else if(status == 'open' && jQuery('#project_program_asset_main_container').attr('data2') == 'querystring') {
        var pid = getUrlParameter('aid');
        window.location.href="/program/asset?aid="+pid;    
      } 
      else if(status == 'closed') {
        jQuery('#project_program_asset_main_container').attr('for','open'); 
        jQuery('#project_program_asset_main_container').show();
        jQuery('.custom-reset-button-schedule-div').show();
  	  }
      else if(status == 'open') {
        jQuery('#project_program_asset_main_container').hide();
        jQuery('#project_program_asset_main_container').attr('for','closed'); 
        jQuery('.custom-reset-button-schedule-div').hide();
      }
      else if(status == 'open' && jQuery('#project_program_asset_main_container').attr('data') == 'edit') { 
        jQuery('#project_program_asset_main_container').removeAttr('data'); 
        var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
        jQuery('.project-program-sel-assets').val('').trigger('change');    
        jQuery('#project_program_asset_main_container').show();
        jQuery('.custom-reset-button-schedule-div').show();
      }
      else if(jQuery( "#project_program_asset_main_container" ).attr('data') == 'edit') {
        var getScheduleProId = jQuery('.new-record-cus-btn').attr('for');
        jQuery('.project-program-sel-assets').val('').trigger('change');    
        jQuery('#project_program_asset_main_container').show();
        jQuery('#project_program_asset_main_container').attr('for','open'); 
        jQuery('.custom-reset-button-schedule-div').show();
      }
    });
	var pid = getUrlParameter('aid');
    if(!isNaN(pid)) { 
      jQuery('.project-program-assets-sel').val(pid).trigger('change');
      jQuery('#project_program_asset_main_container').attr('for','open'); 
      jQuery('#project_program_asset_main_container').show();
      jQuery('.custom-reset-button-schedule-div').show();
    }
    else {
      jQuery('#project_program_asset_main_container').hide();   
      jQuery('.custom-reset-button-schedule-div').hide();
      jQuery('#project_program_asset_main_container').attr('for','closed');
    }
  }
  // work for safety tab  
  if(getPath == '/program/safety') {
    // Functionality for add new sagety button				
	var ProId = jQuery('.project-program-safety-sel').val();
	jQuery('.new-record-cus-btn').attr('for', ProId);			
    jQuery('.new-safety-link').click(function (e) {
	  e.preventDefault();
	  var status = jQuery('#project_safety_main_container').attr('for');
	  var dataAttr = jQuery('#project_safety_main_container').attr('data');
	  
	  if(status == 'open' && jQuery('#project_safety_main_container').attr('data') == 'edit') {	 
	    jQuery('#project_safety_main_container').removeAttr('data'); 
		var getProId = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-program-safety-sel').val(getProId).trigger('change');
		jQuery('#project_safety_main_container').show();
		jQuery('.program-safety-status-btn').show();
		jQuery('.custom-submit-safety').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
	  }
	  else if(status == 'open' && jQuery('#project_safety_main_container').attr('data2') == 'querystring') {
		var pid = getUrlParameter('pid');	    
		window.location.href="/program/safety?pid="+pid;		
	  }	
	  else if(status == 'closed') {
	    jQuery('#project_safety_main_container').attr('for','open');
		jQuery('#project_safety_main_container').show();
		jQuery('.program-safety-status-btn').show();
		jQuery('.custom-submit-safety').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
      }
	  else if(status == 'open') {
	    jQuery('#project_safety_main_container').hide();
		jQuery('.program-safety-status-btn').hide();
	    jQuery('#project_safety_main_container').attr('for','closed'); 
	    jQuery('.custom-submit-safety').hide();
		jQuery('.custom-submit-reset').hide();
      }
	  else if(status == 'open' && jQuery('#project_safety_main_container').attr('data') == 'edit') { 
	    jQuery('#project_safety_main_container').removeAttr('data'); 
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-safety-sel').val(getProId).trigger('change');
	    jQuery('#project_safety_main_container').show();
		jQuery('.program-safety-status-btn').show();
	    jQuery('.custom-submit-safety').show();
		jQuery('.custom-submit-reset').show();
	  }
	  else if(jQuery( "#project_safety_main_container" ).attr('data') == 'edit') {
	    var getProId = jQuery('.new-record-cus-btn').attr('for');
	    jQuery('.project-program-safety-sel').val(getProId).trigger('change');
	    jQuery('#project_safety_main_container').show();
	    jQuery('.project_safety_main_container').attr('for','open'); 
	    jQuery('.custom-submit-safety').show();
		jQuery('.program-safety-status-btn').show();
		jQuery('.custom-submit-reset').show();
		jQuery('.custom-submit-safety').show();		
      }
    });
	var pid = getUrlParameter('pid');
	if(!isNaN(pid)) { 
	  jQuery('.project-program-safety-sel').val(pid).trigger('change');
	  jQuery('#project_safety_main_container').attr('for','open'); 
	  jQuery('#project_safety_main_container').show();
	  jQuery('.custom-submit-safety').show();
	  jQuery('.program-safety-status-btn').show();
	  jQuery('.custom-submit-reset').show();
	  jQuery('.custom-submit-safety').show();		
	}
	else {
	  jQuery('.project-program-safety-sel').trigger('change');	
	  jQuery('#project_safety_main_container').hide();
	  jQuery('.program-safety-status-btn').hide();
	  jQuery('#project_safety_main_container').attr('for','closed');
	  jQuery('.custom-submit-safety').hide();
	  jQuery('.custom-submit-reset').hide();
	}	
  }
  else if(getPath == '/program/add-cost-code') {
    jQuery('.new-cc-link').click(function (e) {
	  e.preventDefault();
	  var status = jQuery('#project_cost_code_main_container').attr('for');
	  var dataAttr = jQuery('#project_cost_code_main_container').attr('data');
      if(status == 'open' && jQuery('#project_cost_code_main_container').attr('data') == 'edit') {
	    window.location.href="/program/add-cost-code?id=true";
	  }
	  if(status == 'open' && jQuery('#project_cost_code_main_container').attr('data2') == 'querystring') {
	    var id = getUrlParameter('id');
	    if(!isNaN(id)) { 
		  window.location.href="/program/add-cost-code?id="+id;
		}	    
	    jQuery('#project_cost_code_main_container').removeAttr('data'); 
		jQuery('#project_cost_code_main_container').removeAttr('data2'); 
		var getCCID = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-cost-code-sel').val(getCCID).trigger('change');		
		jQuery('#project_cost_code_main_container').show();
		jQuery('.custom-submit-cost-code').show();
	  }	  
	  else if(status == 'closed') {
		jQuery('#project_cost_code_main_container').attr('for','open'); 
		jQuery('#project_cost_code_main_container').show();
		jQuery('.custom-submit-cost-code').show();
	  }
	  else if(status == 'open') {
	    jQuery('#project_cost_code_main_container').hide();
		jQuery('.custom-submit-cost-code').hide();
		jQuery('#project_cost_code_main_container').attr('for','closed'); 
	  }
	  else if(status == 'open' && jQuery('#project_cost_code_main_container').attr('data') == 'edit') {		  
		jQuery('#project_cost_code_main_container').removeAttr('data'); 
		var getCCID = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-cost-code-sel').val(getCCID).trigger('change');
		jQuery('#project_cost_code_main_container').show();
		jQuery('.custom-submit-cost-code').show();
	  }	  
	  else if(jQuery( "#project_cost_code_main_container" ).attr('data') == 'edit') {
	    var getCCID = jQuery('.new-record-cus-btn').attr('for');
		jQuery('.project-cost-code-sel').val(getCCID).trigger('change');
		jQuery('#project_cost_code_main_container').show();
		jQuery('.custom-submit-cost-code').show();
		jQuery('.project_cost_code_main_container').attr('for','open'); 
	  }	  
	});	
	var pid = getUrlParameter('id');
	if(pid) { 
	  jQuery('#project_cost_code_main_container').attr('for','open'); 
	  jQuery('#project_cost_code_main_container').show();
	  jQuery('.custom-submit-cost-code').show();
	} 	
	else {	  
	  jQuery('#project_cost_code_main_container').hide();	  
	  jQuery('.custom-submit-cost-code').hide();
	  jQuery('#project_cost_code_main_container').attr('for','closed');
	}		
  }  
  if((getPath == '/program/estimates')) {
    jQuery('.project-program-sel').trigger('change');
  }
  if((getPath == '/program/photos')) {
	jQuery('.project-program-photos-sel').trigger('change');  
    var pid = getUrlParameter('pid');
	if(!isNaN(pid)) {
	  jQuery('.project-program-photos-sel').val(pid);
    }
	jQuery('.project-program-photos-sel').change(function() {
	  var photoId = jQuery(this).val();	
	  var pid = getUrlParameter('pid');
	  if(isNaN(pid) || photoId != pid) { 
	    window.location.href="/program/photos?pid="+photoId;
	  }
	});
	jQuery('#edit-f1-und legend').hide();  
    jQuery('#edit-f2-und legend').hide();
	jQuery('#edit-f3-und legend').hide();
	jQuery('#edit-f4-und legend').hide();
	jQuery('#edit-f5-und legend').hide();
  }
  if(getPath == '/program/reports') {
    jQuery('.project_programe_reports_sections').trigger('change');
	
  }
  // ===============================
  // Work for Default Milestone page
  // ================================
 else if(getPath == '/program/add-default-milestone' || getPath == '/program/cm/add-default-milestone') {
    // Functionality for add new sagety button        
  var ProId = jQuery('.project-default-milestone-sel').val();
  jQuery('.new-record-cus-btn').attr('for', ProId);     
    jQuery('.new-default-mile-link').click(function (e) {
    e.preventDefault();
    var status = jQuery('#project_default_milestone_main_container').attr('for');
    var dataAttr = jQuery('#project_default_milestone_main_container').attr('data');
    
    if(status == 'open' && jQuery('#project_default_milestone_main_container').attr('data') == 'edit') {   
      jQuery('#project_default_milestone_main_container').removeAttr('data'); 
    var getProId = jQuery('.new-record-cus-btn').attr('for');
    jQuery('.project-default-milestone-sel').val(getProId).trigger('change');
    jQuery('.project_default_milestone_nid').val('');
    jQuery('#project_default_milestone_main_container').show();   
    jQuery('.custom-submit-default_milestone').show();
    }
    else if(status == 'open' && jQuery('#project_default_milestone_main_container').attr('data2') == 'querystring') {
    var pid = getUrlParameter('pid');     
    window.location.href="/program/add-default-milestone?pid="+pid;   
    } 
    else if(status == 'closed') {
      jQuery('#project_default_milestone_main_container').attr('for','open');
    jQuery('#project_default_milestone_main_container').show();
    jQuery('.custom-submit-default_milestone').show();
      }
    else if(status == 'open') {
      jQuery('#project_default_milestone_main_container').hide();
      jQuery('#project_default_milestone_main_container').attr('for','closed'); 
      jQuery('.custom-submit-default_milestone').hide();
      }
    else if(status == 'open' && jQuery('#project_default_milestone_main_container').attr('data') == 'edit') { 
      jQuery('#project_default_milestone_main_container').removeAttr('data'); 
      var getProId = jQuery('.new-record-cus-btn').attr('for');
      jQuery('.project-default-milestone-sel').val(getProId).trigger('change');
      jQuery('#project_default_milestone_main_container').show();
      jQuery('.custom-submit-default_milestone').show();
    }
    else if(jQuery("#project_default_milestone_main_container").attr('data') == 'edit') {
      var getProId = jQuery('.new-record-cus-btn').attr('for');
      jQuery('.project-default-milestone-sel').val(getProId).trigger('change');
      jQuery('#project_default_milestone_main_container').show();
      jQuery('#project_default_milestone_main_container').attr('for','open'); 
      jQuery('.custom-submit-default_milestone').show();
      }
    });
  var pid = getUrlParameter('pid');
  if(!isNaN(pid)) { 
    jQuery('.project-default-milestone-sel').val(pid).trigger('change');
    jQuery('#project_default_milestone_main_container').attr('for','open'); 
    jQuery('#project_default_milestone_main_container').show();
    jQuery('.custom-submit-default_milestone').show();
  }
  else {
    jQuery('.project-default-milestone-sel').trigger('change'); 
    jQuery('#project_default_milestone_main_container').hide();
    jQuery('#project_default_milestone_main_container').attr('for','closed');
    jQuery('.custom-submit-default_milestone').hide();
  } 
  }
  // Work for default milestone lock date
  else if(getPath == '/program/lock-milestone-date') {
    // Functionality for add new sagety button          
    jQuery('.new-default-mile-lock-link').click(function (e) {
    e.preventDefault();
    var status = jQuery('#project_default_milestone_lock_date_main_container').attr('for');
    var dataAttr = jQuery('#project_default_milestone_lock_date_main_container').attr('data');    
    if(status == 'open' && jQuery('#project_default_milestone_lock_date_main_container').attr('data') == 'edit') {   
      jQuery('#project_default_milestone_lock_date_main_container').removeAttr('data'); 
    //var getProId = jQuery('.new-record-cus-btn').attr('for');
    //jQuery('.project-default-milestone-sel').val(getProId).trigger('change');
    jQuery('.project-sel-default-milestone-lock').val('').trigger('change');
    jQuery('.project_default_milestone_nid').val('');
    //jQuery('#project_default_milestone_lock_date_main_container').show();   
    //jQuery('.custom-submit-default_milestone_lock_date').show();
    }
    else if(status == 'open' && jQuery('#project_default_milestone_lock_date_main_container').attr('data2') == 'querystring') {
    var pid = getUrlParameter('pid');     
    window.location.href="/program/lock-milestone-date?pid="+pid;   
    } 
    else if(status == 'closed') {
      jQuery('#project_default_milestone_lock_date_main_container').attr('for','open');
    //jQuery('#project_default_milestone_lock_date_main_container').show();
    //jQuery('.custom-submit-default_milestone_lock_date').show();
      }
    else if(status == 'open') {
      //jQuery('#project_default_milestone_lock_date_main_container').hide();
      jQuery('#project_default_milestone_lock_date_main_container').attr('for','closed'); 
      //jQuery('.custom-submit-default_milestone_lock_date').hide();
      }
    else if(jQuery("#project_default_milestone_lock_date_main_container").attr('data') == 'edit') {
      jQuery('.project-default-milestone-sel').val('').trigger('change');
      //jQuery('#project_default_milestone_lock_date_main_container').show();
      jQuery('#project_default_milestone_lock_date_main_container').attr('for','open'); 
      //jQuery('.custom-submit-default_milestone_lock_date').show();
      }
    });
  var pid = getUrlParameter('pid');
  if(!isNaN(pid)) { 
    jQuery('.project-sel-default-milestone-lock').val('').trigger('change');
    jQuery('#project_default_milestone_lock_date_main_container').attr('for','open'); 
    jQuery('.project_default_milestone_lock_date_nid').val('');
    //jQuery('#project_default_milestone_lock_date_main_container').show();
    //jQuery('.custom-submit-default_milestone_lock_date').show();
  }
  else {
    jQuery('#project_default_milestone_lock_date_main_container').attr('for','closed'); 
    jQuery('.project-sel-default-milestone-lock').val('').trigger('change');
    jQuery('.project_default_milestone_lock_date_nid').val('');
    //jQuery('#project_default_milestone_lock_date_main_container').hide();   
    //jQuery('.custom-submit-default_milestone_lock_date').hide();
  } 
  }
  //estimate subtab  
  if((getPath == '/program/estimates/capital-request') || (getPath == '/program/estimates/estimate-schedule') || (getPath == '/program/estimates/supporting-estimates')) {
    jQuery('.project-program-sel').trigger('change');
	jQuery('.project-program-sel-est-details').trigger('change');
  }		
 // ==============================
  // Dialog box popup configuration
  // for estiamte approve
  // ==============================
  jQuery('#estimate-approve-change-dialog').dialog({
    autoOpen: false,
	width: 490,
	modal: true,
	resizable: false,
	buttons: {
	    'Continue': function () {
		  jQuery('select[name="approve-status-drop"]').val('ok');
		  jQuery(this).dialog("close");
		  jQuery('#routing-dialog-container').html('');
		  jQuery('form#program-modify-estimates-form').submit();
	    },
	    'Cancel': function () {
	      jQuery('select[name="approve-status-drop"]').val('cancel');
		  jQuery(this).dialog("close");
		  jQuery('#routing-dialog-container').html('');
		  jQuery('form#program-modify-estimates-form').submit();
	      }
    },
	open: function () {
	    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	    jQuery('.ui-dialog-titlebar').hide();
      }
  });	 
  // =================================
  // Dialog box for spending forecast
  jQuery('#spending-forcast-option-dialog').dialog({
    autoOpen: false,
	width: 490,
	modal: true,
	resizable: false,
	buttons: {
	    'Continue': function () {		  
		  var getName = jQuery('.forcast-name-by-user').val();
		  if(getName == '') {
		    jQuery('.forcast-name-by-user').addClass('error');
			return false;
		  }
		  else {
			var getProId = jQuery('.forcast-project-id-cust')  .val();
		    jQuery.post( '/check-for-previous-forecast/'+ getName +'/'+getProId, function( data ) { 
		      if(data.access == 0) {}
		      if(data.access == 1) {}		  
		    });  
		    jQuery('.forcast-name-by-user').removeClass('error');			
			jQuery('.spending-forcast-name-input').val(getName);			
			jQuery('.spending_forcast_pro_submit_call').trigger('click');
			jQuery(this).dialog("close");
		  }
	    },
	    'Cancel': function () {
	      //jQuery('select[name="approve-status-drop"]').val('cancel');
		  jQuery(this).dialog("close");
		  //jQuery('#routing-dialog-container').html('');
		  //jQuery('form#program-modify-estimates-form').submit();
	      }
    },
	open: function () {
	    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	    jQuery('.ui-dialog-titlebar').hide();
      }
  });
  // ================================
  // Dialog box for spending forecast save as
  jQuery('#spending-forcast-option-dialog-saveas').dialog({
    autoOpen: false,
	width: 490,
	modal: true,
	resizable: false,
	buttons: {
	    'Continue': function () {		  
		  var getName = jQuery('.forcast-name-by-user').val();
		  if(getName == '') {
		    jQuery('.forcast-name-by-user').addClass('error');
			return false;
		  }
		  else {
			var getProId = jQuery('.forcast-project-id-cust').val();
		    jQuery.post( '/check-for-previous-forecast/'+ getName +'/'+getProId, function( data ) { 
		      if(data.access == 0) {}
		      if(data.access == 1) {}		  
		    });  
		    jQuery('.forcast-name-by-user').removeClass('error');			
			jQuery('.spending-forcast-name-input').val('copy-'+getName);			
			jQuery('.spending_forcast_pro_submit_call').trigger('click');
			jQuery(this).dialog("close");
		  }
	    },
	    'Cancel': function () {
	      //jQuery('select[name="approve-status-drop"]').val('cancel');
		  jQuery(this).dialog("close");
		  //jQuery('#routing-dialog-container').html('');
		  //jQuery('form#program-modify-estimates-form').submit();
	      }
    },
	open: function () {
	    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	    jQuery('.ui-dialog-titlebar').hide();
      }
  });    
  // Dialog box for Commitemt From ETC
  // =================================
  jQuery('#from-etc-dialog-container').dialog({
    autoOpen: false,
	width: 490,
	modal: true,
	resizable: false,
	//buttons: { },
	buttons: {
	    'Remove ETC from Forecast and Delete from ETC.': function () {		  
		  jQuery('.etc_data_status_val').val('RemoveEtc');
		  jQuery(this).dialog("close");
		  jQuery('.main-commitment-submit-call').trigger('click');
	    },
		'Leave ETC in Forecast (leave In ETC checked).': function () {
		  jQuery('.etc_data_status_val').val('DoNothing');
		  jQuery(this).dialog("close");		  
		  jQuery('.main-commitment-submit-call').trigger('click');
	    },
	    'Remove ETC from Forecast but do NOT Delete.': function () {
	      jQuery('.etc_data_status_val').val('unCheck');
		  jQuery(this).dialog("close");
		  jQuery('.main-commitment-submit-call').trigger('click');
	      }
    },
	open: function () {
	    jQuery('.ui-dialog-buttonpane').find('button:contains("Remove ETC from Forecast and Delete from ETC.")').css('width','100%');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Leave ETC in Forecast (leave In ETC checked).")').css('width','100%');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Remove ETC from Forecast but do NOT Delete.")').css('width','100%');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Remove ETC from Forecast and Delete from ETC.")').css('margin-bottom','10px');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Leave ETC in Forecast (leave In ETC checked).")').css('margin-bottom','10px');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Remove ETC from Forecast but do NOT Delete.")').css('margin-bottom','10px');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Remove ETC from Forecast and Delete from ETC.")').css('text-align','left');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Leave ETC in Forecast (leave In ETC checked).")').css('text-align','left');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Remove ETC from Forecast but do NOT Delete.")').css('text-align','left');
	    jQuery('.ui-dialog-titlebar').hide();
      }
  });
  // =====================================
  // Dialog box popup configuration 
  // to check for data for project report
  // =====================================
  jQuery('#report-nodata-dialog').dialog({
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
  jQuery('#file-remove-dialog').dialog({
    autoOpen: false,
    width: 490,
    modal: true,
    resizable: false,
    buttons: {
      'Yes': function () {
	    var getUri = jQuery('.file-remove-data').val();
		jQuery.post(getUri, function( data ) { 
		  var getNodeId = getUri.split('/');
          jQuery('.project-program-sel-spending').val(getNodeId[3]).trigger('change');
        });
          
        jQuery(this).dialog("close");         
      },        
      'Cancel': function () {
        jQuery(this).dialog("close");
      }
	},
    open: function () {
      jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
    jQuery('.ui-dialog-titlebar').hide();
    }
  });
  
  // =================================
  // Dialog box for lock default milestone     
  // =====================================
  jQuery('#lock-milestone-duration-dialog').dialog({
    autoOpen: false,
  width: 490,
  modal: true,
  resizable: false,
  buttons: {
      'Continue': function () {
        //var duration = jQuery('input.lock-duration:checked').val();
		var duration = jQuery('.lock-duration').val();		
        var mileId = jQuery('.milestone-id').val();
        jQuery('.send-message').val(1);
		jQuery.post('/update-lock-status/'+ duration +'/'+mileId, function( data ) { 		  
        });
		jQuery(this).dialog("close");
		window.location.reload();
      },
      'Cancel': function () {
        jQuery('.lock-milestone-duration').val(0);
        jQuery(this).dialog("close");
      //jQuery('form#program-modify-estimates-form').submit();
      }
    },
  open: function () {
      jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
      jQuery('.ui-dialog-titlebar').hide();
      }
  });
  // =================================
  jQuery('#move-to-archive-dialog').dialog({
    autoOpen: false,
  width: 490,
  modal: true,
  resizable: false,
  buttons: {
      'Continue': function () {
      var duration = jQuery('input.make-archive:checked').val();
      var mileId = jQuery('.milestone-id').val();
      jQuery('.move-archive').val(projectId); 
      },
      'Cancel': function () {
        jQuery('.lock-milestone-duration').val(0);
      jQuery(this).dialog("close");
      //jQuery('form#program-modify-estimates-form').submit();
        }
    },
  open: function () {
      jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
      jQuery('.ui-dialog-titlebar').hide();
      }
  });  
  // =================================
  // Dialog box for lock default milestone     
  // =====================================  
  // =================================
  // Dialog box for lock default milestone  	 
  // =====================================  
  jQuery('#custom-commit-dialog').dialog({
    autoOpen: false,
	width: 490,
	modal: true,
	resizable: false,
	buttons: {
	    'Continue': function () {
			jQuery('.custom-submit-commitment .form-submit').trigger('click');
			jQuery(this).dialog("close");
		    //jQuery('form#program-modify-commitment-form').submit();
	    },
	    'Cancel': function () {
		  jQuery(this).dialog("close");
	      }
    },
	open: function () {
	    jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	    jQuery('.ui-dialog-titlebar').hide();
      }
  });
  // =========================
  // Dialog box configuration
  // for estimate tab for no data
  // ============================
  jQuery('#estimate-approve-nodata-dialog').dialog({
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
  // ========================
  // Dialog box configuration
  // for po item no data
  // ========================
  jQuery('#po-item-nodata-dialog').dialog({
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

  jQuery(document).on('click', '#upload_plus' ,function () {
    jQuery(this).parents('.upload_attachment_container').find('.asset-data-rendration input').click();
  });
});

 
  // ==================================
  // Function to get query string value
  // ==================================
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
  
 /* jQuery(window).load(function() {
	jQuery(".report-loader").fadeOut("slow");
})*/
/*jQuery('.report-loading').click(function (e) {
  jQuery(".report-loader").show();	  
});*/

function hideProgress(){
  jQuery(".report-loader2").hide();	  
}

jQuery(window).scroll(function(e){ 
  var el = jQuery('.fixedElement'); 
  var isPositionFixed = (el.css('position') == 'fixed');
  if (jQuery(this).scrollTop() > 200&& !isPositionFixed){ 
    //jQuery('.fixedElement').css({'position': 'fixed', 'bottom': '0','z-index':'9999','width':'1099px','border-top':'1px solid #fff','right':'15px'}); 
	jQuery('.fixedElement').css({'position': 'fixed', 'bottom': '0','z-index':'9999','width':'100%','border-top':'1px solid #fff','left':'0'}); 
  }
  if (jQuery(this).scrollTop() < 200 && isPositionFixed)
  {
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
		if(jQuery('#dvPreview').find('img').length > 0) {
          jQuery('#dvPreview').show();
		}
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