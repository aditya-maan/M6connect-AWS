Drupal.behaviors.m6connect_program = {	
  attach: function (context, settings) {
    jQuery('.dataTables_paginate span a.paginate_button').click(function () {
      Drupal.attachBehaviors(jQuery('body'));     
	  var getPage = jQuery(this).text();
	  jQuery('.page_number_id').val(getPage);
    });	
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
	jQuery('.field_est_line_item_amt').keyup(function (i) {
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
	    return("$-" + formatted + ((parts) ? "." + parts[1].substr(1, 2) : ""));	  	    	  	
	  }
	  else {
	    return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));  
	  }	  
    }; 	  
	// =======================================	  
   // Getting the current path 
   // for different tab for cost manager page
   var getPath = window.location.pathname;	
    if(getPath == '/program/spending-forcast' || getPath == '/program/cm/spending-forcast' || getPath == '/program/cr/spending-forcast') {
	  // By default triggering last saved forecast
	  var getLastForecast = jQuery('.spending-forecast-select option').last().val();	  
	  jQuery('.spending-forecast-select option').last().prop('selected',true);
	  if(getLastForecast && getLastForecast != 'None') {	     
        jQuery('#'+ getLastForecast).trigger('click');
      }		  	
	  var forecast = getUrlParameter('forecast');
	  if(forecast) { jQuery('select.spending-forecast-select').val(forecast).trigger('change'); }	  
	  	  		  	
	  jQuery('.commit-amt-quarter-fourth').trigger('keyup');
	  jQuery('.project_programe_spending_forcast_pro').change(function () {
	    jQuery('.commit-amt-quarter-three').trigger('keyup');
		jQuery('.commit-amt-quarter-fourth').trigger('keyup');
		var getPreviousGrandTotal = 0;
	    getPreviousGrandTotal = jQuery('.previous-year-grand-total').text().replace(/[^\d\.\-]/g, '');
	    if(getPreviousGrandTotal != '') {
	      if(getPreviousGrandTotal < 0) {	
	        (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">Previous Year Total :<span class="text-danger">'+format(getPreviousGrandTotal)+'</span></div>');
	      }
	      else {
	       (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">Previous Year Total :'+format(getPreviousGrandTotal)+'</div>');
	     }
	   }		    
	  });	  
	  var commitTblrows = jQuery(".m6connect-program-spending-forcast-main-table tbody tr");
	  commitTblrows.each(function (index) {
        var tblrowCommit = jQuery(this);			
 	    tblrowCommit.find('.commit-amt-quarter-fourth').on('keyup', function () {
		  var fourthQuarter = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		    var etcAmt = tblrowCommit.find(".commit-amt").text();		  
		    var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
		    // ======================
			// Get All quarter values		    
			var getFistQuarter = tblrowCommit.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, '');			
			var getSecQuarter = tblrowCommit.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, '');			
			var getThirdQuarter = tblrowCommit.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, '');			
			var tillDateAmt = tblrowCommit.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, '');
			var getFourthQuarter = fourthQuarter;
			var updateFrtQtr = '0';
			if(getFourthQuarter && getFourthQuarter != '-') { updateFrtQtr = getFourthQuarter; }
			else { updateFrtQtr = '0'; }
			
			var quarterTotal = parseFloat(getThirdQuarter) + parseFloat(tillDateAmt) + parseFloat(getFistQuarter) + parseFloat(getSecQuarter) + parseFloat(updateFrtQtr);
			// ===================================================
			// Assign quarterTotal to current year spending column
			tblrowCommit.find('.commit-total-spent').text(format(quarterTotal.toFixed(2)));		  			
			(quarterTotal < 0)?tblrowCommit.find('.commit-total-spent').addClass('text-danger'):tblrowCommit.find('.commit-total-spent').removeClass('text-danger');
			// Varience caluction
			var totalSpent = tblrowCommit.find('.commit-total-spent').text().replace(/[^\d\.\-]/g, '');			
			var beyondYear = tblrowCommit.find('.commit-beyond-year').val().replace(/[^\d\.\-]/g, '');		  			
			var preYearSpending = tblrowCommit.find('.previous-year-spendings').text().replace(/[^\d\.\-]/g, '');				
			var totalSpending = tblrowCommit.find('.commit-invoice-amt').text().replace(/[^\d\.\-]/g, '');										
			var varience = parseFloat(etcAmtCal) - ((parseFloat(quarterTotal) + parseFloat(beyondYear) + parseFloat(preYearSpending)));			
			tblrowCommit.find('.commit-varience-total-calc').text(format(varience.toFixed(2)));
			(varience < 0)?tblrowCommit.find('.commit-varience-total-calc').addClass('text-danger'):tblrowCommit.find('.commit-varience-total-calc').removeClass('text-danger');
			// ==== Current year spending grand total ==== //
		    var grandTotal = 0;
	        jQuery(".commit-total-spent").each(function () {
	          var getTotalSpent = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stval = parseFloat(getTotalSpent);
	          grandTotal += isNaN(stval) ? 0 : stval;
	        }); 
		    (isNaN(grandTotal)) ? '' : jQuery('.commit-total-spent-total').text(format(grandTotal.toFixed(2)));
			(grandTotal < 0)?jQuery('.commit-total-spent-total').addClass('text-danger'):jQuery('.commit-total-spent-total').removeClass('text-danger');
			if(grandTotal < 0) {
			  (isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
			}
			else {
			  (isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:'+format(grandTotal.toFixed(2))+'</div>');
			}
			// ==== Future year grand total ==== //
			var beyondGrandTotal = 0;
	        jQuery(".commit-beyond-year").each(function () {
	          var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	          var stvalBeyond = parseFloat(getTotalBeyond);
	          beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	        }); 		  
	        (isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));			  
		    if(beyondGrandTotal < 0) {
			  jQuery('.commit-beyond-year-total').addClass('text-danger');
			  (isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		    }
		    else {
		      jQuery('.commit-beyond-year-total').removeClass('text-danger');
			  (isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		    }
		    // ==== Previous year Q1 Q2 Q3 Q4 and Till date grand total ==== //
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
	          var getQuarterTwo = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalQTwo = parseFloat(getQuarterTwo);
	          quarterTwo += isNaN(stvalQTwo) ? 0 : stvalQTwo;
	        }); 		
		    (isNaN(quarterTwo)) ? '' : jQuery('.quarter-two-grand-total').text(format(quarterTwo.toFixed(2)));  		  
		    		    
		    var quarterThree = 0;
	        jQuery(".commit-amt-quarter-three").each(function () {
	          var getQuarterThree = jQuery(this).text().replace(/[^\d\.\-]/g, '');
	          var stvalQuatarThree = parseFloat(getQuarterThree);
	          quarterThree += isNaN(stvalQuatarThree) ? 0 : stvalQuatarThree;
	        });
		    (isNaN(quarterThree)) ? '' : jQuery('.commit-amt-quarter-three-total').text(format(quarterThree.toFixed(2)));
			
		    var quarterFour = 0;		  
	        jQuery(".commit-amt-quarter-fourth-text").each(function () {
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
		  
		    var spentTodate = previousYear + quarterOne + quarterTwo + quarterThree + quarterFour;
		    if(spentTodate < 0) {		    
			  (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:1px solid #fff;">Spent to Date : <span class="text-danger">'+format(spentTodate.toFixed(2))+'</span></div>');
		    }
		    else {
		      (isNaN(spentTodate)) ? '' : jQuery('#spent-to-date-container').html('<div style="display:block;padding: 6px;color: #fff;border-left:1px solid #fff;">Spent to Date : '+format(spentTodate.toFixed(2))+'</div>');
		    } 		  
		  });		
		  tblrowCommit.find('.commit-beyond-year').on('keyup', function () {
			var beyondYear = jQuery(this).val().replace(/[^\d\.\-]/g, '');
		    var etcAmt = tblrowCommit.find(".commit-amt").text();		  
		    var etcAmtCal = etcAmt.replace(/[^\d\.\-]/g, '');
			// ======================
			// Get All quarter values
			var getFistQuarter = tblrowCommit.find('.commit-amt-quarter-one').text().replace(/[^\d\.\-]/g, '');			
			var getSecQuarter = tblrowCommit.find('.commit-amt-quarter-two').text().replace(/[^\d\.\-]/g, '');			
			var getThirdQuarter = tblrowCommit.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, '');			
			var tillDateAmt = tblrowCommit.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, '');
			var getFourthQuarter = tblrowCommit.find('.commit-amt-quarter-fourth').val().replace(/[^\d\.\-]/g, '');
			
			var beyondYearTotal = beyondYear;
			var updateBeyTotal = '0';
			if(beyondYearTotal && beyondYearTotal != '-') { updateBeyTotal = beyondYearTotal; }
			else { updateBeyTotal = '0'; }
			
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
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:<span class="text-danger">'+format(grandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-total-spent-total').removeClass('text-danger');
			(isNaN(grandTotal)) ? '' : jQuery('#commitment-current-year').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">'+ new Date().getFullYear() +' Spending Forecast:'+format(grandTotal.toFixed(2))+'</div>');
		  }
		  
		  var beyondGrandTotal = 0;
	      jQuery(".commit-beyond-year").each(function () {
	        var getTotalBeyond = jQuery(this).val().replace(/[^\d\.\-]/g, '');
	        var stvalBeyond = parseFloat(getTotalBeyond);
	        beyondGrandTotal += isNaN(stvalBeyond) ? 0 : stvalBeyond;
	      }); 
		  
	      (isNaN(beyondGrandTotal)) ? '' : jQuery('.commit-beyond-year-total').text(format(beyondGrandTotal.toFixed(2)));			  
		  if(beyondGrandTotal < 0) {
			jQuery('.commit-beyond-year-total').addClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;">Future Year Total : <span class="text-danger">'+format(beyondGrandTotal.toFixed(2))+'</span></div>');
		  }
		  else {
		    jQuery('.commit-beyond-year-total').removeClass('text-danger');
			(isNaN(beyondGrandTotal)) ? '' : jQuery('#commitment-beyond-next-year').html('<div style="display: block;padding: 6px;color: #fff;">Future Year Total : '+format(beyondGrandTotal.toFixed(2))+'</div>');
		  }
		});							  
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
		  
		  var beyond = tblrow.find('.commit-beyond-year').val()
		  if(beyond) { var beyondUp = beyond.replace(/[^\d\.\-]/g, ''); }
		  else { var beyondUp = 0.00; }
		  
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
			'Nextrecord',
		  ]		  
		});		
        jQuery('#edit-forcast-update-data').val(spendingData);
		// Get spending data for etc
		var spendingEtcData = [];
		var tblrows = jQuery(".m6connect-program-spending-forcast-main-table-etc tbody tr");	  
	    tblrows.each(function (row, tr) {
		  tblrow = jQuery(this);
		  var q3 = tblrow.find('.etc-amt-quarter-three').val();
		  var q4 = tblrow.find('.etc-amt-quarter-fourth').val();
		  
		  if(q3) { var q3Up = q3.replace(/[^\d\.\-]/g, ''); }
		  else { var q3Up = 0.00; }
		  
		  if(q4) { var q4Up = q4.replace(/[^\d\.\-]/g, ''); }
		  else { var q4Up = 0.00; }
		  
		  var beyond = tblrow.find('.etc-beyond-year').val()
		  if(beyond) { var beyondUp = beyond.replace(/[^\d\.\-]/g, ''); }
		  else { var beyondUp = 0.00; }
		  
		  spendingEtcData[row] = [
		  	jQuery('.project_programe_spending_forcast_pro').val(),
			tblrow.find('.etc-number').attr('id'),
			tblrow.find('.etc-amt-quarter-one').text()!=''?tblrow.find('.etc-amt-quarter-one').text().replace(/[^\d\.\-]/g, ''):0,
			tblrow.find('.etc-amt-quarter-two').text()!=''?tblrow.find('.etc-amt-quarter-two').text().replace(/[^\d\.\-]/g, ''):0,
			/*tblrow.find('.commit-amt-quarter-three').text()!=''?tblrow.find('.commit-amt-quarter-three').text().replace(/[^\d\.\-]/g, ''):0,
			tblrow.find('.commit-amt-quarter-fourth-text').text()!=''?tblrow.find('.commit-amt-quarter-fourth-text').text().replace(/[^\d\.\-]/g, ''):0,
			tblrow.find('.commit-amt-quarter-fourth').val()!=''?q4Up:0,*/
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
		  jQuery('#spending-forcast-option-dialog').html('<div class="text-center"><strong>Welcome to Spending Forecast...</strong></p><p>Enter name for spending forecast: <input type="text" name="forcast name" class="forcast-name-by-user"> <input type="hidden" value="'+projectId+'" class="forcast-project-id-cust"></p></div>');
		  jQuery('#spending-forcast-option-dialog').dialog('open');
		}
		else {
		  jQuery('.spending_forcast_pro_submit_call').trigger('click');
		}
	  });	  	  	 
	  jQuery('.add-new-spending-forecast').click(function (e) {
	    jQuery('.project_programe_spending_forcast_pro').trigger('change');
	  });
	  // Trigger previous forecast by select list
	  jQuery('.spending-forecast-select').change(function(e){
        var getForecast = jQuery(this).val();
		if(getForecast == 'None') {
		  window.location.href="/program/spending-forcast?status=new";
		}
        if(getForecast && getForecast != 'None') {	     
          jQuery('#'+ getForecast).trigger('click');
        }
      });
	  // Work for expand and collapse table columns
	  jQuery('.custom-quater-one-heading').hide();
	  jQuery('.custom-quater-two-heading').hide();
	  jQuery('.custom-quater-three-heading').hide();
	  jQuery('.custom-quater-fourth-heading').hide();
	  /*jQuery('.custom-current-year-heading').hide();
	  jQuery('.future-year-heading').hide();
	  jQuery('.varience-heading').hide();*/
	  jQuery('.show-left').unbind('click').bind('click',function () {
	    jQuery('.custom-quater-one-heading').toggle('slide');
	    jQuery('.custom-quater-two-heading').toggle('slide');
	    jQuery('.custom-quater-three-heading').toggle('slide');
		if(jQuery('.show-left-span').hasClass('fa-angle-double-left')) {
		  jQuery('.show-left-span').removeClass('fa-angle-double-left');
		  jQuery('.show-left-span').addClass('fa-angle-double-right');
		}else if(jQuery('.show-left-span').hasClass('fa-angle-double-right')) {
		  jQuery('.show-left-span').removeClass('fa-angle-double-right');
		  jQuery('.show-left-span').addClass('fa-angle-double-left');
		}
	  });
	  jQuery('.show-right').unbind('click').bind('click',function () {
	    jQuery('.custom-quater-fourth-heading').toggle('slide');
		if(jQuery('.show-right-span').hasClass('fa-angle-double-left')) {
		  jQuery('.show-right-span').removeClass('fa-angle-double-left');
		  jQuery('.show-right-span').addClass('fa-angle-double-right');
		}else if(jQuery('.show-right-span').hasClass('fa-angle-double-right')) {
		  jQuery('.show-right-span').removeClass('fa-angle-double-right');
		  jQuery('.show-right-span').addClass('fa-angle-double-left');
		}
	  });
	}  
  }
};

jQuery(document).ready(function(e) {
  var getPath = window.location.pathname;	
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
	    return("$-" + formatted + ((parts) ? "." + parts[1].substr(1, 2) : ""));	  	    	  	
	  }
	  else {
	    return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));  
	  }	  
    }; 	
  if(getPath == '/program/spending-forcast' || getPath == '/program/cm/spending-forcast' || getPath == '/program/cr/spending-forcast') {
    jQuery('.project_programe_spending_forcast_pro').trigger('change');
    var getPreviousGrandTotal = 0;
	getPreviousGrandTotal = jQuery('.previous-year-grand-total').text().replace(/[^\d\.\-]/g, '');
	if(getPreviousGrandTotal != '') {
	  if(getPreviousGrandTotal < 0) {	
	  (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">Previous Year Total :<span class="text-danger">'+format(getPreviousGrandTotal)+'</span></div>');
	  }
	  else {
	    (isNaN(getPreviousGrandTotal)) ? '' : jQuery('#commitment-forcast-total-main').html('<div style="display: block;padding: 6px;color: #fff;border-left: 1px solid #fff;">Previous Year Total :'+format(getPreviousGrandTotal)+'</div>');
	  }
	}		    	      
  }
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
};