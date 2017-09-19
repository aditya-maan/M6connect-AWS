// JavaScript Document

(function ($, Drupal) {

  Drupal.behaviors.custom_international_phone = {
	attach: function (context, settings) {
	  $(".international_phone-number").intlTelInput({
		autoHideDialCode: true,
		nationalMode: false,
		autoPlaceholder: true,
		utilsScript: "/sites/all/libraries/intl-tel-input/js/utils.js"
	  });
		
	  $(".international_phone-number").on("countrychange", function(e, countryData) {
		var phone_code_element = $(this).closest('div.international-phone-number-fields-group').find('.international-phone-number-country-code');
		if(phone_code_element.length && countryData.dialCode){
		  phone_code_element.val(countryData.dialCode);  
		}
		console.log(countryData);
	  });
	  
	  $(".international_phone-number").on("blur", function(e) {
		var countryData = $(this).intlTelInput("getSelectedCountryData");
		var phone_code_element = $(this).closest('div.international-phone-number-fields-group').find('.international-phone-number-country-code');
		if(phone_code_element.length && countryData.dialCode){
		  phone_code_element.val(countryData.dialCode);  
		}
		console.log(countryData);
	  });
	  
	  $('input.select-all-worker-checkbox').change(function () {
        $(this).closest('table.m6id-worker-to-project-table').find("input:checkbox").prop('checked', $(this).prop("checked"));
      });
	   /// for M6ID Invite Employee(s)
	   $('input.select-all-m6id-invite-emp').change(function () {
        $(this).closest('table.m6id-invite-emp-table').find("input:checkbox").prop('checked', $(this).prop("checked"));
      }); 
	  /// for M6ID Invite Employee(s)
	}
  };
  Drupal.ajax.prototype.commands.update_internation_phone_dial_code = function(ajax, response, status) {
	$(".international_phone-number").each(function(index, element) {
	  var phone_code_element = $(this).closest('div.international-phone-number-fields-group').find('.international-phone-number-country-code');
	  var countryData = $(this).intlTelInput("getSelectedCountryData");
	  if(phone_code_element.length && countryData.dialCode){
		phone_code_element.val(countryData.dialCode);  
	  }    
	}); 
  };
  
  Drupal.ajax.prototype.commands.console_log = function(ajax, data, status) {
	console.log(data);
  };
  
  jQuery(document).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
	
	if((urlajax.indexOf("/file/ajax/upload_container/excel_file_fid") == 0) && (ajaxOptions.extraData.hasOwnProperty('_triggering_element_value') && ajaxOptions.extraData._triggering_element_value == 'Upload')){
	  console.log(ajaxOptions);
	  jQuery('.m6id-invite-workflow-bulk-upload').trigger('mousedown');
	}
  });
}(jQuery, Drupal));

