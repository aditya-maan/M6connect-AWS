jQuery(document).ready(function (e) {
  var getPath = window.location.pathname; 
  jQuery('.listing-row-delete').click(function (e) {
  var hiderow = jQuery(this).parent().parent().parent().parent().parent().parent();  
    hiderow.hide(); 
  });
 
  //work order summary date field validate
  if(jQuery('body').hasClass('page-hcfm-add-work-order-summary')){  
    if(jQuery('.messages--error').hasClass('error')){ 
    var errorLi = jQuery('.messages__item').text();
    var errorText = errorLi.split('.');   
    for(var i=0; i<errorText.length; i++){
    if(errorText[i] === 'Period Start field is required'){
      jQuery('.wos-period-start').addClass('error');
    }
    if(errorText[i] === 'Period End field is required'){
      jQuery('.wos-period-end').addClass('error');
    }
    }
    }
  }
  //work on work order
  jQuery('.asset-facility-region').change(function(e){ 
  var getRegionId = jQuery(this).val();
  //console.log(getRegionId); 
  if(getRegionId) {
    jQuery.post( '/get-facility-list/'+getRegionId, function( data ) {
     if(data != 0) {
       // jQuery.each(data,function(key, value) {
       //console.log(key+','+value);  
       jQuery('.wo-facility').empty();  
       jQuery(".wo-facility").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-facility');
       });
      // });
     }
     else{
       jQuery('.wo-facility').empty(); 
       jQuery(".wo-facility").prepend("<option value=''>- None -</option>").val('');
     }   
    })
    jQuery.post( '/get-facility-region-data/'+getRegionId, function( data ) {
     if(data != 0) {        
       if(data && data['field_loccaton_region_address1_value']){         
       jQuery('.wo-region-address1').val(data['field_loccaton_region_address1_value']);
       }
       else{
       jQuery('.wo-region-address1').val('');
       }
       if(data && data['field_loccaton_region_address2_value']){         
       jQuery('.wo-region-address2').val(data['field_loccaton_region_address2_value']);
       }
       else{
       jQuery('.wo-region-address2').val('');
       }
       if(data && data['field_loccaton_region_city_value']){         
       jQuery('.wo-region-city').val(data['field_loccaton_region_city_value']);
       }
       else{
       jQuery('.wo-region-city').val('');
       }
       if(data && data['field_loccaton_region_state_value']){        
       jQuery('.wo-region-state').val(data['field_loccaton_region_state_value']);
       }
       else{
       jQuery('.wo-region-state').val('');
       }
       if(data && data['field_loccaton_region_zipcode_value']){        
       jQuery('.wo-region-zipcode').val(data['field_loccaton_region_zipcode_value']);
       }
       else{
       jQuery('.wo-region-zipcode').val('');
       }
       if(data && data['field_loccaton_region_country_value']){        
       jQuery('.wo-region-country').val(data['field_loccaton_region_country_value']);
       }
       else{
       jQuery('.wo-region-country').val('');
       }        
     }
     else{
       jQuery('.wo-region-address1').val('');
       jQuery('.wo-region-address1').val('');
       jQuery('.wo-region-city').val('');
       jQuery('.wo-region-state').val('');
       jQuery('.wo-region-zipcode').val('');
       jQuery('.wo-region-country').val('');
     }     
    })
  }
  else{
    jQuery('.wo-building').val('');
    jQuery('.wo-floor').val('');
    jQuery('.wo-region-address1').val('');
    jQuery('.wo-region-address1').val('');
    jQuery('.wo-region-city').val('');
    jQuery('.wo-region-state').val('');
    jQuery('.wo-region-zipcode').val('');
    jQuery('.wo-region-country').val('');
  }
  });
  var FullFacAddress = [];
  var WoBuilding = [];
  var WoFloor = [];
  jQuery('.wo-facility').change(function(e){
    var getFacilityId = jQuery(this).val();
  jQuery('.wo_facility_value').val(getFacilityId);
  FullFacAddress = [];
  WoBuilding = [];
  WoFloor = [];
  jQuery('.wo-building').val('');
  jQuery('.wo-floor').val('');
  if(getFacilityId) {
     jQuery.post( '/get-asset-list-facilityid/'+getFacilityId, function( data ) {
     if(data != 0) {
       // jQuery.each(data,function(key, value) {
       //console.log(key+','+value);  
       jQuery('.hcfm-asset').empty(); 
       jQuery(".hcfm-asset").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.hcfm-asset');
       });
      // });
     }
     else{
       jQuery('.hcfm-asset').empty(); 
       jQuery(".hcfm-asset").prepend("<option value=''>- None -</option>").val('');
     }   
    })
  }
  else{
    jQuery('.wo-building').val('');
    jQuery('.wo-floor').val('');
    
  }
  });
  
  jQuery('.wo-facility').change(function(e){
   var getFacilityId = jQuery(this).val();  
  if(getFacilityId) {
    jQuery.post( '/get-zone-floorlist/'+getFacilityId, function( data ) {
     if(data != 0) {
       // jQuery.each(data,function(key, value) {
       //console.log(key+','+value);  
       jQuery('.wo-floor').empty(); 
       jQuery(".wo-floor").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-floor');
       });
      // });
     }
     else{
       jQuery('.wo-floor').empty(); 
       jQuery(".wo-floor").prepend("<option value=''>- None -</option>").val('');
       
     }   
    })
  }
  else{
    jQuery('.wo-floor').empty(); 
    jQuery(".wo-floor").prepend("<option value=''>- None -</option>").val('');
   
    
  }
  });
  
  jQuery('.hcfm-asset').change(function(e){
    var getAssetId = jQuery(this).val();  
  if(getAssetId) {
    if(FullFacAddress){
      var FullFacAddressStrint = FullFacAddress.toString();
      //console.log(FullFacAddressStrint);
      jQuery('.wo-full-address').val(FullFacAddressStrint);
    }
    if(WoBuilding){
    var WoBuildingStrint = WoBuilding.toString();
      //console.log(WoBuildingStrint);
      jQuery('.wo-building').val(WoBuildingStrint);   
    }
    if(WoFloor){
    var WoFloorStrint = WoFloor.toString();
      //console.log(WoFloorStrint);
      jQuery('.wo-floor').val(WoFloorStrint);
    
    }
  }else{
    jQuery('.wo-full-address').val('');
    jQuery('.wo-building').val('');
    jQuery('.wo-floor').val('');
  }
  });
  
  
  
  
  
  //hcfm configure add facility
  jQuery('select.fa-region-country').change(function(e){   
  var getCountryCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getCountryCode) {
    var getCountryText = jQuery("select.fa-region-country option:selected").text();
    jQuery('input.fa-region-country-value').val(getCountryText);
    jQuery.post( '/get-state-list-countrycode/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.fa-region-state').empty();  
       jQuery(".fa-region-state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.fa-region-state');
       });
      // });
     }
     /*else{
       jQuery('.fa-region-state').empty(); 
       jQuery(".fa-region-state").prepend("<option value=''>- Select -</option>").val('');
     } */  
    })
    
  }else{
    jQuery('input.fa-region-country-value').val('');
  } 
  });
  jQuery('select.fa-region-state').change(function(e){   
  var getStateCode = jQuery(this).val();  
  //console.log(getStateCode);  
  if(getStateCode) {
    var getStateText = jQuery("select.fa-region-state option:selected").text();
    jQuery('input.fa-region-state-value').val(getStateText);    
  }else{
    jQuery('input.fa-region-state-value').val('');
  } 
  });
  
///////////// regiion site facility zone empty value ///
  var RegionValue =  jQuery('select.as-asset-region').val();
  if(!RegionValue){
    jQuery('.as-asset-site').empty(); 
    jQuery('.as-asset-facility').empty();
    jQuery('.as-asset-location').empty(); 
  }
  var SiteValue =  jQuery('select.as-asset-site').val();
  if(!SiteValue){    
    jQuery('.as-asset-facility').empty();
    jQuery('.as-asset-location').empty(); 
  }
  var FacilityValue =  jQuery('select.as-asset-facility').val();
  if(!FacilityValue){    
    jQuery('.as-asset-location').empty(); 
  }
  var ZoneValue =  jQuery('select.as-asset-location').val();
  if(!ZoneValue){    
    jQuery('.as-asset-location').empty(); 
  }
  //for compare dash
  
   var RegionValue =  jQuery('select.dash_asset_region_list').val();
  if(!RegionValue){
    jQuery('.dash_asset_site_list').empty(); 
    jQuery('.dash_asset_facility_list').empty();
    jQuery('.dash_asset_zone_list').empty(); 
  }
  var SiteValue =  jQuery('select.dash_asset_site_list').val();
  if(!SiteValue){    
    jQuery('.dash_asset_facility_list').empty();
    jQuery('.dash_asset_zone_list').empty();  
  }
  var FacilityValue =  jQuery('select.dash_asset_facility_list').val();
  if(!FacilityValue){    
    jQuery('.dash_asset_zone_list').empty(); 
  }
 ////////////



  //asset change region
  jQuery('select.as-asset-region').change(function(e){   
  var getRegionId = jQuery(this).val(); 
  //console.log(getRegionId); 
  if(getRegionId && (jQuery.type(getRegionId) === "string" ||  jQuery.type(getRegionId) === "array" && getRegionId.length < 2 && getRegionId.indexOf('all') !=0)) {   
    jQuery.post( '/get-locationdata/region/'+getRegionId, function( data ) {
      //console.log(data);
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
       //console.log(key+','+value);      
       jQuery('.as-asset-site').empty();  
       //jQuery(".as-asset-site").prepend("<option>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.as-asset-site');
       });
      // });
     }
     else{
      jQuery('.as-asset-site').empty(); 
      //jQuery(".as-asset-site").prepend("<option>- None -</option>").val('');  
    }    
    })
  }else{
    jQuery('.as-asset-site').empty(); 
    //jQuery(".as-asset-site").prepend("<option>- None -</option>").val('');  
  } 
  });
  //for compare dash
   jQuery('select.dash_asset_region_list').change(function(e){   
    var getRegionId = jQuery(this).val(); 
    //console.log(getRegionId); 
    if(getRegionId) {   
      jQuery.post( '/get-locationdata-compare/region/'+getRegionId, function( data ) {
        //console.log(data);
       if(data != 0 && data) {
        jQuery('.dash_asset_site_list').empty();
        jQuery('.dash_asset_site_list').prepend('<option value="all">All</option>').val('');
        jQuery.each(data,function(key, value) {
          var opt = jQuery('<option>');       
          opt.val(key).text(value);
          opt.appendTo('.dash_asset_site_list');
        });
       }
       else{
        jQuery('.dash_asset_site_list').empty(); 
        //jQuery(".as-asset-site").prepend("<option>- None -</option>").val('');  
      }    
      })
    }else{
      jQuery('.dash_asset_site_list').empty(); 
      //jQuery(".as-asset-site").prepend("<option>- None -</option>").val('');  
    } 
  });
  //asset change site
  jQuery('select.as-asset-site').change(function(e){   
    var getSiteId = jQuery(this).val(); 
    //console.log(getSiteId); 
    if(getSiteId && (jQuery.type(getSiteId) === "string" ||  jQuery.type(getSiteId) === "array" && getSiteId.length < 2)) {   
      jQuery.post( '/get-locationdata/site/'+getSiteId, function( data ) {
       if(data != 0 && data) {
        // jQuery.each(data,function(key, value) {        
         jQuery('.as-asset-facility').empty();  
         //jQuery(".as-asset-facility").prepend("<option>- Select -</option>").val('');
         jQuery.each(data,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.as-asset-facility');
         });
        //});
       }
       else{
        jQuery('.as-asset-facility').empty(); 
        //jQuery(".as-asset-facility").prepend("<option>- None -</option>").val('');  
      }  
      })
    }else{
      jQuery('.as-asset-facility').empty(); 
      //jQuery(".as-asset-facility").prepend("<option>- None -</option>").val('');  
    } 
  });
  //for compare dash
  jQuery('select.dash_asset_site_list').change(function(e){   
    var getSiteId = jQuery(this).val(); 
    //console.log(getSiteId); 
    if(getSiteId) {
      jQuery.post( '/get-locationdata-compare/site/'+getSiteId, function( data ) {
       if(data != 0 && data) {         
         jQuery('.dash_asset_facility_list').empty();
         jQuery('.dash_asset_facility_list').prepend('<option value="all">All</option>').val('');
         jQuery.each(data,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.dash_asset_facility_list');
         });       
       }
       else{
        jQuery('.dash_asset_facility_list').empty(); 
        //jQuery(".as-asset-facility").prepend("<option>- None -</option>").val('');  
      }  
      })
    }else{
      jQuery('.dash_asset_facility_list').empty(); 
      //jQuery(".as-asset-facility").prepend("<option>- None -</option>").val('');  
    } 
  });
  //asset change facility
  jQuery('select.as-asset-facility').change(function(e){   
    var getFacilityId = jQuery(this).val(); 
    //console.log(getFacilityId); 
    if(getFacilityId && (jQuery.type(getFacilityId) === "string" ||  jQuery.type(getFacilityId) === "array" && getFacilityId.length < 2)) {   
      jQuery.post( '/get-locationdata/facility/'+getFacilityId, function( data ) {
       if(data != 0 && data) {
        // jQuery.each(data,function(key, value) {        
         jQuery('.as-asset-location').empty();  
         //jQuery(".as-asset-location").prepend("<option>- Select -</option>").val('');
         jQuery.each(data,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.as-asset-location');
         });
        //});
       }  
       else{
        jQuery('.as-asset-location').empty(); 
        //jQuery(".as-asset-location").prepend("<option>- None -</option>").val('');  
      }  
      })
    }else{
      jQuery('.as-asset-location').empty(); 
      //jQuery(".as-asset-location").prepend("<option>- None -</option>").val('');  
    }
  });
  // for dashboard
  jQuery('select.dash_asset_facility_list').change(function(e){   
    var getFacilityId = jQuery(this).val(); 
    //console.log(getFacilityId); 
    if(getFacilityId) {   
      jQuery.post( '/get-locationdata-compare/facility/'+getFacilityId, function( data ) {
       if(data != 0 && data) {
        // jQuery.each(data,function(key, value) {        
         jQuery('.dash_asset_zone_list').empty();  
         //jQuery('.dash_asset_zone_list').prepend('<option value="all">All</option>').val('');
         //jQuery(".as-asset-location").prepend("<option>- Select -</option>").val('');
         jQuery.each(data,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.dash_asset_zone_list');
         });
        //});
       }  
       else{
        jQuery('.dash_asset_zone_list').empty(); 
        //jQuery(".as-asset-location").prepend("<option>- None -</option>").val('');  
      }  
      })
    }else{
      jQuery('.dash_asset_zone_list').empty(); 
      //jQuery(".as-asset-location").prepend("<option>- None -</option>").val('');  
    }
  });

  //work order accet change 
  jQuery('input.wo-asset-number-new').change(function(e){   
  var getAssetId = jQuery(this).context.value;  
  //console.log(getAssetId);  
  if(getAssetId) {    
    jQuery.post( '/get-workorderdata/asset/'+getAssetId, function( data ) {
      if(data != 0) {         
      if(data && data['field_asset_manuafacturer_value']){       
        jQuery('.wo-manufacturer').val(data['field_asset_manuafacturer_value']);
      }
      else{
        jQuery('.wo-manufacturer').val('');      
      }
      if(data && data['field_asset_model_number_value']){      
        jQuery('.wo-model-number').val(data['field_asset_model_number_value']);
      }
      else{
        jQuery('.wo-model-number').val('');      
      }
      if(data && data['field_asset_serial_number_value']){       
        jQuery('.wo-serial-number').val(data['field_asset_serial_number_value']);
      }
      else{
        jQuery('.wo-serial-number').val('');       
      }
      if(data && data['field_asset_account_number_target_id']){      
        jQuery('.wo-account-number').val(data['field_asset_account_number_target_id']);
      }
      else{
        jQuery('.wo-account-number').val('');      
      }
      if(data && data['field_asset_priority_rr_target_id']){       
        jQuery('.wo-priority-rr').val(data['field_asset_priority_rr_target_id']);
      }
      else{
        jQuery('.wo-priority-rr').val('');       
      }
      
      }  
    })
  }else{
    jQuery('.wo-manufacturer').val('');
    jQuery('.wo-model-number').val('');
    jQuery('.wo-serial-number').val('');
    jQuery('.wo-account-number').val('');
    jQuery('.wo-priority-rr').val('');
  }
  });
  
  
  jQuery(document).on('click', 'a.dashboard_asset_reset_btn', function(e) {  
    jQuery(this).parent().parent().parent().siblings().children().show();
    jQuery(this).parent().parent().parent().siblings().children().find('ul.select2-choices li.select2-search-choice').remove();
    jQuery(this).parent().parent().parent().siblings().children().find('option').removeAttr('selected');
  });
 
  var getMultiRegionIdText = 'region';
  var getMultiSiteIdText = 'site';
  var getMultiFacilityIdText = 'facility';
  var getMultiZoneIdText = 'zone';
  var getMultiStatusIdText = 'status';
  var getMultiRiskrankIdText = 'riskrank';
  var geMultitFilterIdText = 'filter';

  
  
  //hcfm config tab activate
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
  
  
  var locationactivetab = getUrlParameter('configlocationactivetab');  
  if(locationactivetab){
    jQuery('.hcfm-configure-container ul.nav li').removeClass('active');
  jQuery('.hcfm-configure-container ul.nav li.locationtab').addClass('active');
  jQuery('.hcfm-configure-container div.tab-content div').removeClass('active');
  jQuery('.hcfm-configure-container div.tab-content div.locationtab').addClass('active');
  
  jQuery('.hcfm-location-container-tab ul.nav li').removeClass('active');
  jQuery('.hcfm-location-container-tab ul.nav li.'+locationactivetab).addClass('active');
  jQuery('.hcfm-location-container-tab div.tab-content div').removeClass('active');
  jQuery('.hcfm-location-container-tab div.tab-content div.'+locationactivetab).addClass('active');
  }
  var configactivetab = getUrlParameter('configactivetab');
  if(configactivetab){
    jQuery('.hcfm-configure-container ul.nav li').removeClass('active');
  jQuery('.hcfm-configure-container ul.nav li.'+configactivetab).addClass('active');
  jQuery('.hcfm-configure-container div.tab-content div').removeClass('active');
  jQuery('.hcfm-configure-container div.tab-content div.'+configactivetab).addClass('active');
  }
  var configwoactivetab = getUrlParameter('configwoactivetab');  
  if(configwoactivetab){
    jQuery('.hcfm-configure-container ul.nav li').removeClass('active');
  jQuery('.hcfm-configure-container ul.nav li.workordertab').addClass('active');
  jQuery('.hcfm-configure-container div.tab-content div').removeClass('active');
  jQuery('.hcfm-configure-container div.tab-content div.workordertab').addClass('active');
  
  jQuery('.hcfm-workorder-container-tab ul.nav li').removeClass('active');
  jQuery('.hcfm-workorder-container-tab ul.nav li.'+configwoactivetab).addClass('active');
  jQuery('.hcfm-workorder-container-tab div.tab-content div').removeClass('active');
  jQuery('.hcfm-workorder-container-tab div.tab-content div.'+configwoactivetab).addClass('active');
  }
  var configresourceactivetab = getUrlParameter('configresourceactivetab');  
  if(configresourceactivetab){
    jQuery('.hcfm-configure-container ul.nav li').removeClass('active');
  jQuery('.hcfm-configure-container ul.nav li.resourcestab').addClass('active');
  jQuery('.hcfm-configure-container div.tab-content div').removeClass('active');
  jQuery('.hcfm-configure-container div.tab-content div.resourcestab').addClass('active');
  
  jQuery('.hcfm-resources-container-tab ul.nav li').removeClass('active');
  jQuery('.hcfm-resources-container-tab ul.nav li.'+configresourceactivetab).addClass('active');
  jQuery('.hcfm-resources-container-tab div.tab-content div').removeClass('active');
  jQuery('.hcfm-resources-container-tab div.tab-content div.'+configresourceactivetab).addClass('active');
  }
  var configassetactivetab = getUrlParameter('configassetactivetab');  
  if(configassetactivetab){
    jQuery('.hcfm-configure-container ul.nav li').removeClass('active');
  jQuery('.hcfm-configure-container ul.nav li.assettab').addClass('active');
  jQuery('.hcfm-configure-container div.tab-content div').removeClass('active');
  jQuery('.hcfm-configure-container div.tab-content div.assettab').addClass('active');
  
  jQuery('.hcfm-asset-container-tab ul.nav li').removeClass('active');
  jQuery('.hcfm-asset-container-tab ul.nav li.'+configassetactivetab).addClass('active');
  jQuery('.hcfm-asset-container-tab div.tab-content div').removeClass('active');
  jQuery('.hcfm-asset-container-tab div.tab-content div.'+configassetactivetab).addClass('active');
  }
  jQuery('.hcfm-configure-container ul.nav-tabs li.assettab').click(function(e){
  if(!configassetactivetab){
    jQuery('.hcfm-asset-container-tab ul.nav-tabs li').removeClass('active');
    jQuery('.hcfm-asset-container-tab div.tab-content div').removeClass('active');
    jQuery('.hcfm-asset-container-tab ul.nav-tabs li.config_asset_system').addClass('active');
    jQuery('.hcfm-asset-container-tab .tab-content .config_asset_system').addClass('active');
  }
  });
  jQuery('.hcfm-configure-container ul.nav-tabs li.locationtab').click(function(e){
  if(!locationactivetab){
    jQuery('.hcfm-location-container-tab ul.nav-tabs li').removeClass('active');
    jQuery('.hcfm-location-container-tab div.tab-content div').removeClass('active');
    jQuery('.hcfm-location-container-tab ul.nav-tabs li.config_location_region').addClass('active');
    jQuery('.hcfm-location-container-tab .tab-content .config_location_region').addClass('active');
  }
  });
  jQuery('.hcfm-configure-container ul.nav-tabs li.workordertab').click(function(e){
  if(!configwoactivetab){
    jQuery('.hcfm-workorder-container-tab ul.nav-tabs li').removeClass('active');
    jQuery('.hcfm-workorder-container-tab div.tab-content div').removeClass('active');
    jQuery('.hcfm-workorder-container-tab ul.nav-tabs li.config_workorder_problemcode').addClass('active');
    jQuery('.hcfm-workorder-container-tab .tab-content .workorder_problemcode').addClass('active');
  }
  });
  jQuery('.hcfm-configure-container ul.nav-tabs li.resourcestab').click(function(e){
  if(!configresourceactivetab){
    jQuery('.hcfm-resources-container-tab ul.nav-tabs li').removeClass('active');
    jQuery('.hcfm-resources-container-tab div.tab-content div').removeClass('active');
    jQuery('.hcfm-resources-container-tab ul.nav-tabs li.config_workorder_resource').addClass('active');
    jQuery('.hcfm-resources-container-tab .tab-content .config_workorder_resource').addClass('active');
  }
  });
  //************************ hcfm setting location >>region * start ***************
  var getLocationRegionCountry = jQuery('select.config_location_region_country').val();
  if(!getLocationRegionCountry){
  jQuery('.config_location_region_state').empty(); 
  jQuery(".config_location_region_state").prepend("<option value=''>- none -</option>").val('');
  }
  jQuery('select.config_location_region_country').change(function(e){   
  var getCountryCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getCountryCode) {
    var getCountryText = jQuery("select.config_location_region_country option:selected").text();
    jQuery('input.config_location_region_country_value').val(getCountryText);
    jQuery.post( '/get-state-list-countrycode/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_region_state').empty(); 
       jQuery(".config_location_region_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_location_region_state');
       });
      // });
     }
     else{
       jQuery('.config_location_region_state').empty(); 
         jQuery(".config_location_region_state").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode") === 0){
      if(jQuery('input.config_location_region_state_key').val()){   
        jQuery('select.config_location_region_state').val(jQuery('input.config_location_region_state_key').val());
      }
      }
    });
  }else{
    jQuery('input.config_location_region_country_value').val('');
    jQuery('.config_location_region_state').empty(); 
    jQuery(".config_location_region_state").prepend("<option value=''>- none -</option>").val('');
  }   
  });
  jQuery('select.config_location_region_state').change(function(e){   
  var getStateCode = jQuery(this).val();  
  //console.log(getStateCode);  
  if(getStateCode) {
    var getStateText = jQuery("select.config_location_region_state option:selected").text();
    jQuery('input.config_location_region_state_value').val(getStateText);   
  }else{
    jQuery('input.config_location_region_state_value').val('');
  } 
  }); 
  //************************ hcfm setting location >>region * end ***************
  //************************ hcfm setting location >>site * start ***************
  //change region  >> select country and state list
  /*jQuery('input.config_location_site_addresscopy').click(function() {
    if (jQuery(this).is(':checked')) {
    jQuery('.siteaddresscon').hide();
  } else {      
    jQuery('.siteaddresscon').show();
  };
  });*/
  if(jQuery('select.config_location_pick_region').val() != ''){
  jQuery('.siteaddress-outer').show();  
  }
  jQuery('select.config_location_pick_region').change(function(e){
    var getLocRegionPick = jQuery(this).val();
  if(getLocRegionPick) { 
    jQuery('.siteaddress-outer').show();
    jQuery.post( '/get-locationdata-country/region/'+getLocRegionPick, function( data ) {
    // console.log(data);
    if(data != 0 && data) {
      //if(data.field_locationregion_address_country) {
      //var RCountryCode = data.field_locationregion_address_country;
      //var RStateCode = data.field_locationregion_address_administrative_area;
      jQuery('select.config_location_site_country').val(data);
      jQuery.post( '/get-state-list-countrycode/'+data, function( data2 ) {
         if(data2 != 0 && data2) {
         jQuery.each(data2,function(key, value) {
          // console.log(key+','+value);  
          
           jQuery('.config_location_site_state').empty(); 
           jQuery(".config_location_site_state").prepend("<option value=''>- Select -</option>").val('');
           jQuery.each(data2,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.config_location_site_state');
           });
           
        });
         }
         else{
         jQuery('.config_location_site_state').empty(); 
         jQuery(".config_location_site_state").prepend("<option value=''>- none -</option>").val('');
         }   
      })
      //}
      
    }
    else{
        jQuery('select.config_location_site_country').val('');
      jQuery('.config_location_site_state').empty(); 
      jQuery(".config_location_site_state").prepend("<option value=''>- none -</option>").val('');
      }
    });
  }
  else{
    jQuery('select.config_location_site_country').val('');
    jQuery('.config_location_site_state').empty(); 
    jQuery(".config_location_site_state").prepend("<option value=''>- none -</option>").val('');
    jQuery('.siteaddress-outer').hide();
  }
  }); 
  //default site state none 
  var getLocationSiteCountry = jQuery('select.config_location_site_country').val();
  if(!getLocationSiteCountry){
  jQuery('.config_location_site_state').empty(); 
  jQuery(".config_location_site_state").prepend("<option value=''>- none -</option>").val('');
  }
  //change site country >> select state list
  jQuery('select.config_location_site_country').change(function(e){   
  var getCountryCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getCountryCode) {
    var getCountryText = jQuery("select.config_location_site_country option:selected").text();
    jQuery('input.config_location_site_country_value').val(getCountryText);
    jQuery.post( '/get-state-list-countrycode/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_site_state').empty(); 
       jQuery(".config_location_site_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_location_site_state');
       });
      // });
     }
     else{
       jQuery('.config_location_site_state').empty(); 
       jQuery(".config_location_site_state").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode") === 0){
      if(jQuery('input.config_location_site_state_key').val()){   
        jQuery('select.config_location_site_state').val(jQuery('input.config_location_site_state_key').val());
      }
      }
    })
  }else{
    jQuery('input.config_location_site_country_value').val('');
    jQuery('.config_location_site_state').empty(); 
    jQuery(".config_location_site_state").prepend("<option value=''>- none -</option>").val('');
  } 
  });
  jQuery('select.config_location_site_state').change(function(e){   
  var getStateCode = jQuery(this).val();  
  //console.log(getStateCode);  
  if(getStateCode) {
    var getStateText = jQuery("select.config_location_site_state option:selected").text();
    jQuery('input.config_location_site_state_value').val(getStateText);   
  }else{
    jQuery('input.config_location_site_state_value').val('');
  } 
  }); 
  //************************ hcfm setting location >>site * end ***************
  //************************ hcfm setting location >>facility * start ***************
  //change facility  >> select country and state list
  if(jQuery('select.config_location_pick_site').val() != ''){
  jQuery('.facilityaddress-outer').show();  
  }
  jQuery('select.config_location_pick_site').change(function(e){
    var getLocSitePick = jQuery(this).val();
  if(getLocSitePick) { 
    jQuery('.facilityaddress-outer').show();
    jQuery.post( '/get-locationdata-country/site/'+getLocSitePick, function( data ) {
    // console.log(data);
    if(data != 0 && data) {
      jQuery('select.config_location_facility_country').val(data);
      jQuery.post( '/get-state-list-countrycode/'+data, function( data2 ) {
       if(data2 != 0 && data2) {
         jQuery.each(data2,function(key, value) {
        // console.log(key+','+value);  
         jQuery('.config_location_facility_state').empty(); 
         jQuery(".config_location_facility_state").prepend("<option value=''>- Select -</option>").val('');
         jQuery.each(data2,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.config_location_facility_state');
         });
        });
       }
       else{
         jQuery('.config_location_facility_state').empty(); 
         jQuery(".config_location_facility_state").prepend("<option value=''>- none -</option>").val('');
       }   
      })
    }
    else{
        jQuery('select.config_location_facility_country').val('');
      jQuery('.config_location_facility_state').empty(); 
      jQuery(".config_location_facility_state").prepend("<option value=''>- none -</option>").val('');
      }
    });
  }
  else{
    jQuery('select.config_location_facility_country').val('');
    jQuery('.config_location_facility_state').empty(); 
    jQuery(".config_location_facility_state").prepend("<option value=''>- none -</option>").val('');
    jQuery('.facilityaddress-outer').hide();
  }
  });
  //default facility state none
  var getLocationFacilityCountry = jQuery('select.config_location_facility_country').val();
  if(!getLocationFacilityCountry){
  jQuery('.config_location_facility_state').empty(); 
  jQuery(".config_location_facility_state").prepend("<option value=''>- none -</option>").val('');
  }
  //change facility country >> select state list
  jQuery('select.config_location_facility_country').change(function(e){   
  var getCountryCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getCountryCode) {
    var getCountryText = jQuery("select.config_location_facility_country option:selected").text();
    jQuery('input.config_location_facility_country_value').val(getCountryText);
    jQuery.post( '/get-state-list-countrycode/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_facility_state').empty(); 
       jQuery(".config_location_facility_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_location_facility_state');
       });
      // });
     }
     else{
       jQuery('.config_location_facility_state').empty(); 
         jQuery(".config_location_facility_state").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode") === 0){
      if(jQuery('input.config_location_facility_state_key').val()){   
        jQuery('select.config_location_facility_state').val(jQuery('input.config_location_facility_state_key').val());
      }
      }
    })
  }else{
    jQuery('input.config_location_facility_country_value').val('');
    jQuery('.config_location_facility_state').empty(); 
    jQuery(".config_location_facility_state").prepend("<option value=''>- none -</option>").val('');
  } 
  });
  jQuery('select.config_location_facility_state').change(function(e){   
  var getStateCode = jQuery(this).val();  
  //console.log(getStateCode);  
  if(getStateCode) {
    var getStateText = jQuery("select.config_location_facility_state option:selected").text();
    jQuery('input.config_location_facility_state_value').val(getStateText);   
  }else{
    jQuery('input.config_location_facility_state_value').val('');
  } 
  }); 
  //************************ hcfm setting location >>facility * end ***************
  //************************ hcfm setting location >>location * start ***************
  //change zone  >> select country and state list
  if(jQuery('select.config_location_pick_facility').val() != ''){
  jQuery('.zoneaddress-outer').show();  
  }
  jQuery('select.config_location_pick_facility').change(function(e){
    var getLocFacilityPick = jQuery(this).val();
  if(getLocFacilityPick) { 
    jQuery('.zoneaddress-outer').show();
    jQuery.post( '/get-locationdata-country/facility/'+getLocFacilityPick, function( data ) {
    // console.log(data);
    if(data != 0 && data) {
      jQuery('select.config_location_location_country').val(data);
      jQuery.post( '/get-state-list-countrycode/'+data, function( data2 ) {
       if(data2 != 0 && data2) {
         jQuery.each(data2,function(key, value) {
        // console.log(key+','+value);  
         jQuery('.config_location_location_state').empty(); 
         jQuery(".config_location_location_state").prepend("<option value=''>- Select -</option>").val('');
         jQuery.each(data2,function(key, value) {
           var opt = jQuery('<option>');
           opt.val(key).text(value);
           opt.appendTo('.config_location_location_state');
         });
        });
       }
       else{
         jQuery('.config_location_location_state').empty(); 
         jQuery(".config_location_location_state").prepend("<option value=''>- none -</option>").val('');
       }   
      })
    }
    else{
        jQuery('select.config_location_location_country').val('');
      jQuery('.config_location_location_state').empty(); 
      jQuery(".config_location_location_state").prepend("<option value=''>- none -</option>").val('');
      }
    });
  }
  else{
    jQuery('select.config_location_location_country').val('');
    jQuery('.config_location_location_state').empty(); 
    jQuery(".config_location_location_state").prepend("<option value=''>- none -</option>").val('');
    jQuery('.zoneaddress-outer').hide();
  }
  });
  //default zone state none
  var getLocationZoneCountry = jQuery('select.config_location_location_country').val();
  if(!getLocationZoneCountry){
  jQuery('.config_location_location_state').empty(); 
  jQuery(".config_location_location_state").prepend("<option value=''>- none -</option>").val('');
  }
  //change zone country >> select state list
  jQuery('select.config_location_location_country').change(function(e){   
  var getCountryCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getCountryCode) {
    var getCountryText = jQuery("select.config_location_location_country option:selected").text();
    jQuery('input.config_location_location_country_value').val(getCountryText);
    jQuery.post( '/get-state-list-countrycode/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_location_state').empty(); 
       jQuery(".config_location_location_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_location_location_state');
       });
      // });
     }
     else{
       jQuery('.config_location_location_state').empty(); 
         jQuery(".config_location_location_state").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode") === 0){
      if(jQuery('input.config_location_location_state_key').val()){   
        jQuery('select.config_location_location_state').val(jQuery('input.config_location_location_state_key').val());
      }
      }
    })
  }else{
    jQuery('input.config_location_location_country_value').val('');
    jQuery('.config_location_location_state').empty(); 
    jQuery(".config_location_location_state").prepend("<option value=''>- none -</option>").val('');
  } 
  });
  jQuery('select.config_location_location_state').change(function(e){   
  var getStateCode = jQuery(this).val();  
  //console.log(getStateCode);  
  if(getStateCode) {
    var getStateText = jQuery("select.config_location_location_state option:selected").text();
    jQuery('input.config_location_location_state_value').val(getStateText);   
  }else{
    jQuery('input.config_location_location_state_value').val('');
  } 
  }); 
  //************************ hcfm setting location >>location * end ***************
  //zone change facility
  var OnFacilityNid = jQuery('select.config_location_pick_facility').val();
  if(OnFacilityNid == "") {   
    jQuery(".form-item-config-location-location-numberoffloor .ms-options-wrap .list-unstyled").empty(); 
    //jQuery(".config_location_location_numberoffloor").prepend("<option value=''>- Select -</option>").val('');
    jQuery(".form-item-config-location-location-numberoffloor .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-39" style="padding-left: 21px;"><input type="checkbox" value="none" title="none" id="ms-opt-39">none</label></li>').val(''); 
  }
  jQuery('select.config_location_pick_facility').change(function(e){   
  var getFacilityId = jQuery(this).val(); 
  // console.log(getFacilityId); 
  if(getFacilityId == "") {   
    jQuery(".form-item-config-location-location-numberoffloor .ms-options-wrap .list-unstyled").empty(); 
    //jQuery(".config_location_location_numberoffloor").prepend("<option value=''>- Select -</option>").val('');
    jQuery(".form-item-config-location-location-numberoffloor .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-39" style="padding-left: 21px;"><input type="checkbox" value="none" title="none" id="ms-opt-39">none</label></li>').val(''); 
  }
  });
  
  //location zone floor option trigger
  jQuery('.config_location_numberoffloor_btn').click(function () {    
    var LFloorOp = jQuery(".config_location_location_numberoffloor");
    var LFloorOpSelectedLength = LFloorOp[0].selectedOptions.length;
    if(LFloorOpSelectedLength && LFloorOpSelectedLength != 0){
    jQuery('select.config_location_location_floornumber_select').val(LFloorOpSelectedLength);
    jQuery('input.config_location_location_floornumber_addmore').trigger('mousedown');
    }   
  });
  //prefered vender set city option
  var getPreferredVendorState = jQuery('select.config_preferred_vendors_state').val();
  if(!getPreferredVendorState){
  jQuery('.config_preferred_vendors_city').empty(); 
  jQuery(".config_preferred_vendors_city").prepend("<option value=''>- none -</option>").val('');
  }
  
  jQuery('select.config_preferred_vendors_state').change(function(e){  
  var getPvCountryCode = jQuery('select.config_preferred_vendors_country').val();
  var getPvStateCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getPvCountryCode && getPvStateCode) {    
    jQuery.post( '/get-company-city/'+getPvCountryCode+'/'+getPvStateCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_city').empty();  
       jQuery(".config_preferred_vendors_city").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_city');
       });
      // });
     }
     else{
       jQuery('.config_preferred_vendors_city').empty(); 
         jQuery(".config_preferred_vendors_city").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/get-company-city/"+getPvCountryCode+"/"+getPvStateCode) === 0  && ajaxOptions.url==="/get-company-city/"+getPvCountryCode+"/"+getPvStateCode){
        var GetpfCity = jQuery('.config_preferred_vendors_city_value').val();     
        if(GetpfCity){
        jQuery('select.config_preferred_vendors_city').val(GetpfCity).trigger('change');
      }
      }     
    });
    
  }else{
    jQuery('.config_preferred_vendors_city').empty(); 
    jQuery(".config_preferred_vendors_city").prepend("<option value=''>- none -</option>").val('');
  }
  if(getPvCountryCode && getPvStateCode){ 
    jQuery.post( '/get-company-list-countrystatecity/'+getPvCountryCode+'/'+getPvStateCode+'/0', function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_company').empty(); 
       jQuery(".config_preferred_vendors_company").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_company');
       });
      // });
     }
     else{
       jQuery('.config_preferred_vendors_company').empty(); 
         jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    
  }else{
    //jQuery('.config_preferred_vendors_company').empty(); 
    //jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
  }
  //jQuery('.config_preferred_vendors_city_value').val('');   
  });
  
  
  //preferred vender set company option by country
  var getPreferredVendorCountry = jQuery('select.config_preferred_vendors_country').val();
  if(!getPreferredVendorCountry){
  jQuery('.config_preferred_vendors_company').empty(); 
  jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
  }
  
  jQuery('select.config_preferred_vendors_country').change(function(e){   
  var getPvCountryCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getPvCountryCode) {    
    jQuery.post( '/get-company-list-countrystatecity/'+getPvCountryCode+'/0/0', function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_company').empty(); 
       jQuery(".config_preferred_vendors_company").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_company');
       });
      // });
     }
     else{
       jQuery('.config_preferred_vendors_company').empty(); 
         jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    
    
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/get-company-list-countrystatecity/"+getPvCountryCode+"/0/0") === 0  && ajaxOptions.url==="/get-company-list-countrystatecity/"+getPvCountryCode+"/0/0"){
        var GetpfState = jQuery('.config_preferred_vendors_state_value').val();     
        if(GetpfState){
        jQuery('select.config_preferred_vendors_state').val(GetpfState).trigger('change');
      }
      }     
    });
    
    
    
  }else{
    jQuery('.config_preferred_vendors_company').empty(); 
    jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
  } 
  });
   //preferred vender set company option by city
  jQuery('select.config_preferred_vendors_city').change(function(e){
  var getPvCountryCode = jQuery('select.config_preferred_vendors_country').val();
  var getPvStateCode = jQuery('select.config_preferred_vendors_state').val(); 
  var getPvCityCode = jQuery(this).val(); 
  //console.log(getCountryCode);  
  if(getPvCountryCode && getPvStateCode && getPvCityCode) {   
    jQuery.post( '/get-company-list-countrystatecity/'+getPvCountryCode+'/'+getPvStateCode+'/'+getPvCityCode, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_company').empty(); 
       jQuery(".config_preferred_vendors_company").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_company');
       });
      // });
     }
     else{
       jQuery('.config_preferred_vendors_company').empty(); 
         jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    
  }else{
    //jQuery('.config_preferred_vendors_company').empty(); 
    //jQuery(".config_preferred_vendors_company").prepend("<option value=''>- none -</option>").val('');
  } 
  });
  
 
  if(jQuery('select.wo-region').val() == ''){
  jQuery('.wo-outside-vendors').empty();
  jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
    jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
  }else if(jQuery('select.wo-site').val() == ''){
    jQuery('.wo-outside-vendors').empty();
  jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
    jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
  }else if(jQuery('select.wo-facility').val() == ''){
    jQuery('.wo-outside-vendors').empty();
  jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
    jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
  }else if(jQuery('select.wo-location').val() == ''){
    jQuery('.wo-outside-vendors').empty();
  jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
    jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
  }
  jQuery('select.wo-region').change(function(e){  
  var getRegionID = jQuery(this).val();
    if(getRegionID) {   
    jQuery.post( '/get-location-address/region/'+getRegionID, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.wo-outside-vendors').empty(); 
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty(); 
       //jQuery(".wo-outside-vendors").prepend("<option value=''>- Select -</option>").val('');
       var cot = 0;
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-outside-vendors');
         
         var MulChe = jQuery('<li class=""><label for="ms-opt-'+cot+'" style="padding-left: 21px;"><input type="checkbox" value="'+key+'" title="'+value+'" id="ms-opt-'+cot+'">'+value+'</label></li>');
         MulChe.appendTo(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled");
         cot++;
       });
      // });
     }
     else{
       jQuery('.wo-outside-vendors').empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
     }   
    })    
  }
  });
  jQuery('select.wo-site').change(function(e){  
  var getRegionID = jQuery(this).val();
    if(getRegionID) {   
    jQuery.post( '/get-location-address/site/'+getRegionID, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.wo-outside-vendors').empty(); 
       //jQuery(".wo-outside-vendors").prepend("<option value=''>- Select -</option>").val('');
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       var cot = 0;
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-outside-vendors');
         var MulChe = jQuery('<li class=""><label for="ms-opt-'+cot+'" style="padding-left: 21px;"><input type="checkbox" value="'+key+'" title="'+value+'" id="ms-opt-'+cot+'">'+value+'</label></li>');
         MulChe.appendTo(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled");
         cot++;
       });
      // });
     }
     else{
       jQuery('.wo-outside-vendors').empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
     }   
    })    
  }
  });
  jQuery('select.wo-facility').change(function(e){  
  var getRegionID = jQuery(this).val();
    if(getRegionID) {   
    jQuery.post( '/get-location-address/facility/'+getRegionID, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.wo-outside-vendors').empty(); 
       //jQuery(".wo-outside-vendors").prepend("<option value=''>- Select -</option>").val('');
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       var cot = 0;
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-outside-vendors');
         var MulChe = jQuery('<li class=""><label for="ms-opt-'+cot+'" style="padding-left: 21px;"><input type="checkbox" value="'+key+'" title="'+value+'" id="ms-opt-'+cot+'">'+value+'</label></li>');
         MulChe.appendTo(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled");
         cot++;
       });
      // });
     }
     else{
       jQuery('.wo-outside-vendors').empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
     }   
    })    
  }
  });
  jQuery('select.wo-location').change(function(e){  
  var getRegionID = jQuery(this).val();
    if(getRegionID) {   
    jQuery.post( '/get-location-address/zone/'+getRegionID, function( data ) {
     if(data != 0 && data) {
       // jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.wo-outside-vendors').empty(); 
       //jQuery(".wo-outside-vendors").prepend("<option value=''>- Select -</option>").val('');
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       var cot = 0;
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-outside-vendors');
         var MulChe = jQuery('<li class=""><label for="ms-opt-'+cot+'" style="padding-left: 21px;"><input type="checkbox" value="'+key+'" title="'+value+'" id="ms-opt-'+cot+'">'+value+'</label></li>');
         MulChe.appendTo(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled");
         cot++;
       });
      // });
     }
     else{
       jQuery('.wo-outside-vendors').empty(); 
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").empty();
       jQuery(".form-item-wo-outside-vendors .ms-options-wrap .list-unstyled").prepend('<li class=""><label for="ms-opt-0" style="padding-left: 10px;">none</label></li>').val('');
     }   
    })    
  }
  });
  
  //****************************************** dashboard ***** start  ******************************************///  
  if(getPath == '/hcfm/dashboard') {
  var AssetFilter = {'assets_by_riskrank': 'Assets by Risk Rank','assets_by_rr_1000_square_foot':'Assets by Risk Rank / 1,000 Square Foot'};
  var WorkOrderFilter = {'pm_completion_rate' : 'PM Completion Rate','pm_to_cm_workorder_ratio' : 'PM to CM Work Order Ratio','pm_and_cm_work_orders' :'PM and CM Work Orders','pm_and_cm_work_orders_open':'PM and CM Work Orders Open','pm_and_cm_work_orders_closed':'PM and CM Work Orders Closed','pm_and_cm_work_orders_issued_waiting_for_parts' : 'PM and CM Work Orders Issued Waiting for Parts'};
  //console.log(AssetFilter);
  var DashboardTypeValue = jQuery('select.dashboard_type').val();
  if(!DashboardTypeValue || DashboardTypeValue == '-Select-'){
    jQuery('.dashboard_type_filter').empty(); 
      jQuery(".dashboard_type_filter").prepend("<option value=''>- None -</option>").val('');
  } 
  jQuery('select.dashboard_type').change(function () {
    var DViewBType = jQuery(this).val();
    //console.log(DViewBType);
    var DViewBTypeFilter = '';
    if(DViewBType && DViewBType == 'fm_assets'){
    DViewBTypeFilter = AssetFilter;   
      }
    else if(DViewBType && DViewBType == 'fm_work_orders'){
    DViewBTypeFilter = WorkOrderFilter; 
    }
    
    
    if(DViewBTypeFilter) {
    jQuery.each(DViewBTypeFilter,function(key, value) {
    // console.log(key+','+value);  
      jQuery('.dashboard_type_filter').empty(); 
      jQuery(".dashboard_type_filter").prepend("<option value=''>- Select -</option>").val('');
      jQuery.each(DViewBTypeFilter,function(key, value) {
      var opt = jQuery('<option>');
      opt.val(key).text(value);
      opt.appendTo('.dashboard_type_filter');
      });
    });
    }
    else{
      jQuery('.dashboard_type_filter').empty(); 
      jQuery(".dashboard_type_filter").prepend("<option value=''>- None -</option>").val('');
    }
  });
}
  
  //region change blank >> 

  
  jQuery('#hcfm-dashboard-data-container0-section').hide();  
  jQuery(document).on('click', '.dashboard_gocompare_btn', function(e) {
    jQuery('#hcfm-dashboard-data-container0-section').show();
    jQuery('#hcfm-dashboard-data-container1-section').hide();
  jQuery('.hcfm-dashboard-data-container1-section .clear-data').val('').trigger('change');
  jQuery('.hcfm-dashboard-data-container2-section .clear-data').html('');
  });
  jQuery('.dashboard_go_btn').click(function(e){
    jQuery('#hcfm-dashboard-data-container0-section').hide();
    jQuery('#hcfm-dashboard-data-container1-section').show();
  jQuery('.dashboardcompare-container .clear-data').val('').trigger('change');
  jQuery('.hcfm-dashboard-data-container3-section .clear-data').html('');
  });
  jQuery(document).on('click', '.dashboard_filter_reset', function(e) {
    jQuery('.hcfm-dashboard-data-container1-section .clear-data').val('').trigger('change');
  jQuery('.hcfm-dashboard-data-container2-section .clear-data').html(''); 
  });
  jQuery(document).on('click', '.dashboard_compare_reset', function(e) {
    jQuery('.dashboardcompare-container .clear-data').val('').trigger('change');
  jQuery('.hcfm-dashboard-data-container3-section .clear-data').html(''); 
  });
  
  //remove error on change tab
  jQuery(document).on('click', '.hcfm-configure-container li', function(e) {
  jQuery('.content-page .error').removeClass('messages--error messages');
  jQuery('.content-page .error').html('');
  });
  
  //****************************************** dashboard ***** end  ******************************************/// 
  

  if(getPath == '/hcfm/dashboard4') {
  // flip item start
  jQuery(".hcfm-dash-item-0").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn021").click(function(){
    jQuery(".hcfm-dash-item-0").flip(true);
  });  
  jQuery(".unflip-btn022").click(function(){
    jQuery(".hcfm-dash-item-0").flip(false);
  });
  
  jQuery(".hcfm-dash-item-1").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn121").click(function(){
    jQuery(".hcfm-dash-item-1").flip(true);
  });  
  jQuery(".unflip-btn122").click(function(){
    jQuery(".hcfm-dash-item-1").flip(false);
  });
  
  jQuery(".hcfm-dash-item-2").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn221").click(function(){
    jQuery(".hcfm-dash-item-2").flip(true);
  });  
  jQuery(".unflip-btn222").click(function(){
    jQuery(".hcfm-dash-item-2").flip(false);
  });
  
  jQuery(".hcfm-dash-item-3").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn321").click(function(){
    jQuery(".hcfm-dash-item-3").flip(true);
  });  
  jQuery(".unflip-btn322").click(function(){
    jQuery(".hcfm-dash-item-3").flip(false);
  });
  
  jQuery(".hcfm-dash-item-4").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn421").click(function(){
    jQuery(".hcfm-dash-item-4").flip(true);
  });  
  jQuery(".unflip-btn422").click(function(){
    jQuery(".hcfm-dash-item-4").flip(false);
  });
  
  jQuery(".hcfm-dash-item-5").flip({
    trigger: 'manual' 
  });
  jQuery(".flip-btn521").click(function(){
    jQuery(".hcfm-dash-item-5").flip(true);
  });  
  jQuery(".unflip-btn522").click(function(){
    jQuery(".hcfm-dash-item-5").flip(false);
  });
  
  jQuery(".hcfm-dash-item-6").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn621").click(function(){
    jQuery(".hcfm-dash-item-6").flip(true);
  });  
  jQuery(".unflip-btn622").click(function(){
    jQuery(".hcfm-dash-item-6").flip(false);
  });
  
  jQuery(".hcfm-dash-item-7").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn721").click(function(){
    jQuery(".hcfm-dash-item-7").flip(true);
  });  
  jQuery(".unflip-btn722").click(function(){
    jQuery(".hcfm-dash-item-7").flip(false);
  });
  
  jQuery(".hcfm-dash-item-8").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn821").click(function(){
    jQuery(".hcfm-dash-item-8").flip(true);
  });  
  jQuery(".unflip-btn822").click(function(){
    jQuery(".hcfm-dash-item-8").flip(false);
  });
  
  jQuery(".hcfm-dash-item-9").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn921").click(function(){
    jQuery(".hcfm-dash-item-9").flip(true);
  });  
  jQuery(".unflip-btn922").click(function(){
    jQuery(".hcfm-dash-item-9").flip(false);
  });
  
  jQuery(".hcfm-dash-item-10").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn1021").click(function(){
    jQuery(".hcfm-dash-item-10").flip(true);
  });  
  jQuery(".unflip-btn1022").click(function(){
    jQuery(".hcfm-dash-item-10").flip(false);
  });
  
  jQuery(".hcfm-dash-item-11").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn1121").click(function(){
    jQuery(".hcfm-dash-item-11").flip(true);
  });  
  jQuery(".unflip-btn1122").click(function(){
    jQuery(".hcfm-dash-item-11").flip(false);
  });
  
  // flip item end

  jQuery('.tile-item').each(function(e){
    var getTileStatus = jQuery(this).attr('tile-status'); 
    var getOpenStatus = jQuery(this).attr('open-status'); 
    if(getOpenStatus == 'small'){
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-small-btn').hide();      
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-resetcompare-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compareback-btn').hide();      
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-medium-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-mlsetting-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-large-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compare-btn').show();
      jQuery(this).children().find('.desh-sec-a').show();
      jQuery(this).children().find('.desh-sec-b').hide();
      jQuery(this).children().find('.desh-sec-c').hide(); 
    }
    else if(getOpenStatus == 'medium'){
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-small-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-medium-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-mlsetting-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-large-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compare-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-resetcompare-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compareback-btn').hide();
      jQuery(this).children().find('.desh-sec-a').hide();
      jQuery(this).children().find('.desh-sec-b').show();
      jQuery(this).children().find('.desh-sec-c').hide(); 
    }
    else if(getOpenStatus == 'large'){
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-small-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-medium-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-large-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-mlsetting-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compare-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-resetcompare-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compareback-btn').hide();
      jQuery(this).children().find('.desh-sec-a').hide();
      jQuery(this).children().find('.desh-sec-b').show();
      jQuery(this).children().find('.desh-sec-c').hide(); 
    }
    else if(getOpenStatus == 'compare'){
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-small-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-medium-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-large-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-mlsetting-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compare-btn').hide();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-resetcompare-btn').show();
      jQuery(this).children().children().siblings('.tile-expand-left').find('.tile-expand-compareback-btn').show();
      jQuery(this).children().find('.desh-sec-a').hide();
      jQuery(this).children().find('.desh-sec-b').hide();
      jQuery(this).children().find('.desh-sec-c').show(); 
    }    
  });
  
 
///////////////////////////////////updated extend / reduse start/////////////////
  
  function getUpdatedSmallTilePos() {
    var position = [];
    jQuery('.tile-item').each(function(e){
      var ap = jQuery(this).attr('original-pos');
      if(ap != ''){
        if(jQuery(this).attr('open-status') == 'small'){
          position.push(ap);
        }
      }
    }); 
    return position;
  };
  function getUpdatedMediumTilePos() {
    var position = [];
    jQuery('.tile-item').each(function(e){
      var ap = jQuery(this).attr('original-pos');
      if(ap != ''){
        if(jQuery(this).attr('open-status') == 'medium'){
          position.push(ap);
        }
      }
    }); 
    return position;
  };
  function getUpdatedLargeTilePos() {
    var position = [];
    jQuery('.tile-item').each(function(e){
      var ap = jQuery(this).attr('original-pos');
      if(ap != ''){
        if(jQuery(this).attr('open-status') == 'large'){
          position.push(ap);
        }
      }
    }); 
    return position;
  };

  function getUpdatedCompareTilePos() {
    var position = [];
    jQuery('.tile-item').each(function(e){
      var ap = jQuery(this).attr('original-pos');
      if(ap != ''){
        if(jQuery(this).attr('open-status') == 'compare'){
          position.push(ap);
        }
      }
    }); 
    return position;
  };

  function getUpdatedTilePosTrue(pos) {
    var posstaus = '';
    var posstausA = []; 
    var position = [];
    jQuery('.tile-item').each(function(e){
      var ap = jQuery(this).attr('updated-pos');
      if(ap != ''){
        position.push(ap);
      }
    });
    if(pos){
      for(var i=0; i<position.length; i++){
        if(jQuery.inArray(pos[i],position) != -1){
          posstausA.push(pos[i]);
        }
      }; 
    }
    if(pos.length == posstausA.length){
      posstaus = true;
    }else{
      posstaus = false;
    }
    return posstaus;
  };


function getHcfmDashboardUpdatedTile(DashParrentItem,DashChildItem) { 
  var getTitleStatus = DashParrentItem.attr('tile-status');
  var getOpenStatus = DashParrentItem.attr('open-status');
  var getChildTitleStatus = DashChildItem.attr('box-status');
  var getTileOriPos = DashParrentItem.attr('original-pos');
  var getTileUpdPos = DashParrentItem.attr('updated-pos');
  var TileIndex = DashParrentItem.index();
  var TileIndexLessOne = TileIndex-2;
  // console.log(TileIndex);
  // console.log(TileIndexLessOne);
  // console.log(getOpenStatus);
  var tilesmall = getUpdatedSmallTilePos();
  var tilemedium = getUpdatedMediumTilePos();
  var tilelarge = getUpdatedLargeTilePos();
  var tilecompare = getUpdatedCompareTilePos()
  // console.log('Small');
  // console.log(tilesmall);
  // console.log('Medium');
  // console.log(tilemedium);
  // console.log('large');
  // console.log(tilelarge);
  // console.log('compare');
  // console.log(tilecompare);

  var temparray = [];
var i,j,temparray,chunk = 3;
for (i=0,j=tilesmall.length; i<j; i+=chunk) {
 temparray.push(tilesmall.slice(i,i+chunk));
}
//console.log(temparray);
   
if(tilelarge) {      
 var mainArr =[];
 jQuery(tilelarge).each(function(index, element) {
   remain = [
      element,
    ]
  //console.log(index);
    for(var ii=0; ii<3; ii++) {
    
        remain.push(temparray[index][ii]);
    
   }
    mainArr.push(remain);
 });  
 //console.log(jQuery.merge(mainArr));
 var flatArray = [].concat.apply([], mainArr);
//console.log('flatArray');
// console.log(flatArray);
}

  var newtilealign = [];
  
  newtilealign =tilecompare.concat(flatArray).concat(tilemedium);
  //console.log(' array marge');
  //console.log(newtilealign);
  var newtlangth = newtilealign.length;
  var alltile = ["item0","item1","item2","item3","item4","item5","item6","item7","item8","item9","item10","item11"];
  tilefilter = alltile.filter(f => !newtilealign.includes(f));
  //console.log(newtilealign);
  //console.log(' destructive');

  //console.log(tilefilter);

  if(newtilealign){
    for(var i=0; i<newtlangth; i++){
      var elmm = jQuery("."+newtilealign[i]);
      if(newtilealign[i] == 'item0'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item1'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item2'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item3'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item4'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item5'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }

      if(newtilealign[i] == 'item6'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item7'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item8'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item9'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item10'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
      if(newtilealign[i] == 'item11'){
      //var elmm = jQuery("."+newtilealign[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev());
      jQuery("."+newtilealign[i]).insertBefore('.itemorder');
      }
    }
  }
  if(tilefilter){
    tilefilter.reverse();
    var tilefilterlangth = tilefilter.length;
    for(var i=0; i<tilefilterlangth; i++){
      var elmm = jQuery("."+tilefilter[i]);
      if(tilefilter[i] == 'item0'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertBefore(elm.prev().prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item1'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item2'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev().prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item3'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item4'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev().prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item5'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }

      if(tilefilter[i] == 'item6'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev().prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item7'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item8'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev().prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item9'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item10'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev().prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
      if(tilefilter[i] == 'item11'){
      //var elmm = jQuery("."+tilefilter[i]);
      //console.log(elmm); //elmm.insertAfter(elm.prev());
      jQuery("."+tilefilter[i]).insertAfter('.itemorder');
      }
    }
  }
  
}


jQuery(document).on('click', 'a.tile-expand-small-btn', function(e) {      
    var DashParrentItem = jQuery(this).parent().parent().parent();
    var DashChildItem = jQuery(this).parent().parent();
    var getTitleStatus = DashParrentItem.attr('tile-status'); 
    var getParrentItemOpenStatus = DashParrentItem.attr('open-status'); 
    var getComparebackStatus = DashChildItem.find('.desh-sec-c').children('.compare-back').attr('compareback-status');    
    DashParrentItem.attr('open-status','small');
    DashParrentItem.attr('tile-status','closed');
    DashParrentItem.attr('updated-pos','');
    jQuery(this).parent().parent().find('.desh-sec-a').show();
    jQuery(this).parent().parent().find('.desh-sec-b').hide();
    jQuery(this).parent().parent().find('.desh-sec-c').hide();

    jQuery(this).hide();
    jQuery(this).siblings('a.tile-expand-medium-btn').show();
    jQuery(this).siblings('a.tile-expand-large-btn').show();
    jQuery(this).siblings('a.tile-expand-mlsetting-btn').hide();
    jQuery(this).siblings('a.tile-expand-compare-btn').show();
    jQuery(this).siblings('a.tile-expand-normal-btn').hide();
    jQuery(this).siblings('a.tile-expand-resetcompare-btn').hide();
    jQuery(this).siblings('a.tile-expand-compareback-btn').hide();
    //console.log(getParrentItemOpenStatus);
    if(getParrentItemOpenStatus =='medium'){
      DashParrentItem.toggleClass('col-md-6').toggleClass('col-md-3');
      DashChildItem.toggleClass('tile-height-dubble').toggleClass('tile-height-normal');
    }
    if(getParrentItemOpenStatus =='large'){
      DashParrentItem.toggleClass('col-md-9').toggleClass('col-md-3');
      DashChildItem.toggleClass('tile-height-triple').toggleClass('tile-height-normal');
      DashChildItem.find('.desh-sec-b').toggleClass('tile-height-triple-inner').toggleClass('tile-height-dubble-inner');
    }
    if(getParrentItemOpenStatus =='compare'){
      DashParrentItem.toggleClass('col-md-12').toggleClass('col-md-3');
      DashChildItem.toggleClass('tile-height-dubble').toggleClass('tile-height-normal');
      DashChildItem.find('.desh-sec-b').toggleClass('tile-height-dubble-inner').toggleClass('tile-height-dubble-inner');      
      if(getComparebackStatus && getComparebackStatus == 'open'){
        jQuery(this).siblings('a.tile-expand-compareback-btn').trigger('click');
      }
    }
    getHcfmDashboardUpdatedTile(DashParrentItem,DashChildItem); 
  });

  jQuery(document).on('click', 'a.tile-expand-medium-btn', function(e) {
    var DashParrentItem = jQuery(this).parent().parent().parent();
    var DashParrentItemId = jQuery(this).parent().parent().parent().attr('id');
    var DashChildItem = jQuery(this).parent().parent();
    var getTitleStatus = DashParrentItem.attr('tile-status'); 
    var getParrentItemOpenStatus = DashParrentItem.attr('open-status');
    var getComparebackStatus = DashChildItem.find('.desh-sec-c').children('.compare-back').attr('compareback-status'); 
    DashParrentItem.attr('open-status','medium');
    DashParrentItem.attr('updated-pos','item'+DashParrentItem.index());
    jQuery(this).siblings('a.tile-expand-small-btn').show();
    jQuery(this).hide();
    jQuery(this).siblings('a.tile-expand-mlsetting-btn').show();
    jQuery(this).siblings('a.tile-expand-large-btn').show();
    jQuery(this).siblings('a.tile-expand-compare-btn').show();
    jQuery(this).siblings('a.tile-expand-normal-btn').hide();
    jQuery(this).siblings('a.tile-expand-resetcompare-btn').hide();
    jQuery(this).siblings('a.tile-expand-compareback-btn').hide();
//console.log(getParrentItemOpenStatus);
    if(getParrentItemOpenStatus =='small'){
      DashParrentItem.toggleClass('col-md-3').toggleClass('col-md-6');
      DashChildItem.toggleClass('tile-height-normal').toggleClass('tile-height-dubble');
    }
    if(getParrentItemOpenStatus =='large'){
      DashParrentItem.toggleClass('col-md-9').toggleClass('col-md-6');
      DashChildItem.toggleClass('tile-height-triple').toggleClass('tile-height-dubble');
      //DashChildItem.find('.desh-sec-b').toggleClass('tile-height-triple-inner').toggleClass('tile-height-dubble-inner');
    }
    if(getParrentItemOpenStatus =='compare'){
     // console.log('medium-compare');
      DashParrentItem.toggleClass('col-md-12').toggleClass('col-md-6');
      DashChildItem.toggleClass('tile-height-dubble').toggleClass('tile-height-dubble');
      //DashChildItem.removeClass('tile-height-compare');
      //DashChildItem.find('.desh-sec-b').removeClass('tile-height-dubble-inner');
     ////////// DashChildItem.find('.desh-sec-b').removeClass('tile-height-triple-inner').toggleClass('tile-height-dubble-inner');
      //DashChildItem.find('.desh-sec-b').addClass('tile-height-dubble-inner');
      if(getComparebackStatus && getComparebackStatus == 'open'){
        jQuery(this).siblings('a.tile-expand-compareback-btn').trigger('click');
      }
    }
    DashParrentItem.attr('tile-status','open');
    jQuery(this).parent().parent().find('.desh-sec-a').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').show();
    jQuery(this).parent().parent().find('.desh-sec-c').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').children().find('.graph-normal').show();
    jQuery(this).parent().parent().find('.desh-sec-b').children().find('.graph-large').hide();
    DashChildItem.find('.desh-sec-b').removeClass('tile-height-triple-inner');    
    DashChildItem.find('.desh-sec-b').addClass('tile-height-dubble-inner');

    getHcfmDashboardUpdatedTile(DashParrentItem,DashChildItem);    
    if(!(jQuery('#'+DashParrentItemId +' .graph-normal > div').length)){
      jQuery('#'+DashParrentItemId +' a.tile-expand-mediumcallback-btn').trigger('click');
    }
    
  });
  
  jQuery(document).on('click', 'a.tile-expand-large-btn', function(e) {
    var DashParrentItem = jQuery(this).parent().parent().parent();
    var DashParrentItemId = jQuery(this).parent().parent().parent().attr('id');
    var DashChildItem = jQuery(this).parent().parent();
    DashParrentItem.attr('updated-pos','item'+DashParrentItem.index());
    var getTitleStatus = DashParrentItem.attr('tile-status'); 
    var getParrentItemOpenStatus = DashParrentItem.attr('open-status');
    var getComparebackStatus = DashChildItem.find('.desh-sec-c').children('.compare-back').attr('compareback-status'); 
    DashParrentItem.attr('open-status','large');
    
    jQuery(this).siblings('a.tile-expand-small-btn').show();
    jQuery(this).siblings('a.tile-expand-medium-btn').show();
    jQuery(this).hide();
    jQuery(this).siblings('a.tile-expand-mlsetting-btn').show();
    jQuery(this).siblings('a.tile-expand-compare-btn').show();
    jQuery(this).siblings('a.tile-expand-normal-btn').hide();
    jQuery(this).siblings('a.tile-expand-resetcompare-btn').hide();
    jQuery(this).siblings('a.tile-expand-compareback-btn').hide();
    
    if(getParrentItemOpenStatus && getParrentItemOpenStatus =='small'){
      DashParrentItem.toggleClass('col-md-3').toggleClass('col-md-9');
      DashChildItem.toggleClass('tile-height-normal').toggleClass('tile-height-triple');
      //DashChildItem.find('.desh-sec-b').toggleClass('tile-height-dubble-inner').toggleClass('tile-height-triple-inner');
    }
    if(getParrentItemOpenStatus && getParrentItemOpenStatus =='medium'){
      DashParrentItem.toggleClass('col-md-6').toggleClass('col-md-9');
      DashChildItem.toggleClass('tile-height-dubble').toggleClass('tile-height-triple');
      //DashChildItem.find('.desh-sec-b').toggleClass('tile-height-dubble-inner').toggleClass('tile-height-triple-inner');
    }
    if(getParrentItemOpenStatus && getParrentItemOpenStatus =='compare'){
      DashParrentItem.toggleClass('col-md-12').toggleClass('col-md-9');
      DashChildItem.toggleClass('tile-height-dubble').toggleClass('tile-height-triple');
      DashChildItem.removeClass('tile-height-compare');
      //DashChildItem.find('.desh-sec-b').removeClass('tile-height-dubble-inner');     
      //DashChildItem.find('.desh-sec-b').addClass('tile-height-dubble-inner');
      if(getComparebackStatus && getComparebackStatus == 'open'){
        jQuery(this).siblings('a.tile-expand-compareback-btn').trigger('click');
      }
    }
    DashParrentItem.attr('tile-status','open');
    jQuery(this).parent().parent().find('.desh-sec-a').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').show();
    jQuery(this).parent().parent().find('.desh-sec-c').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').children().find('.graph-normal').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').children().find('.graph-large').show();
    DashChildItem.find('.desh-sec-b').removeClass('tile-height-dubble-inner');    
    DashChildItem.find('.desh-sec-b').addClass('tile-height-triple-inner');
    getHcfmDashboardUpdatedTile(DashParrentItem,DashChildItem);
    
    if(!(jQuery('#'+DashParrentItemId +' .graph-large > div').length)){
      jQuery('#'+DashParrentItemId +' a.tile-expand-largecallback-btn').trigger('click');
    }
  });
  
  jQuery(document).on('click', 'a.tile-expand-compare-btn', function(e) {
    var DashParrentItem = jQuery(this).parent().parent().parent();
    var DashParrentItemId = jQuery(this).parent().parent().parent().attr('id');
    var DashChildItem = jQuery(this).parent().parent();    
    var getTitleStatus = DashParrentItem.attr('tile-status'); 
    var getChildTitleStatus = DashChildItem.attr('box-status');
    var getParrentItemOpenStatus = DashParrentItem.attr('open-status');
    //DashChildItem.find('.desh-sec-a').hide();
    //DashChildItem.find('.desh-sec-b').hide();
    //DashChildItem.find('.desh-sec-c').show();
    DashParrentItem.attr('open-status','compare');
    DashParrentItem.attr('updated-pos','item'+DashParrentItem.index());
    jQuery(this).siblings('a.tile-expand-small-btn').show();
    jQuery(this).siblings('a.tile-expand-medium-btn').show();
    jQuery(this).siblings('a.tile-expand-large-btn').show();
    jQuery(this).hide();
    jQuery(this).siblings('a.tile-expand-mlsetting-btn').hide();
    jQuery(this).siblings('a.tile-expand-normal-btn').hide();
    jQuery(this).siblings('a.tile-expand-resetcompare-btn').show();
    jQuery(this).siblings('a.tile-expand-compareback-btn').show();
    
    if(getParrentItemOpenStatus && getParrentItemOpenStatus =='small'){
      DashParrentItem.toggleClass('col-md-3').toggleClass('col-md-12');
      DashChildItem.toggleClass('tile-height-normal').toggleClass('tile-height-dubble');
    }
    if(getParrentItemOpenStatus && getParrentItemOpenStatus =='medium'){
      DashParrentItem.toggleClass('col-md-6').toggleClass('col-md-12');
      DashChildItem.toggleClass('tile-height-dubble').toggleClass('tile-height-dubble');
    }
    if(getParrentItemOpenStatus && getParrentItemOpenStatus =='large'){
      DashParrentItem.toggleClass('col-md-9').toggleClass('col-md-12');
      DashChildItem.toggleClass('tile-height-triple').toggleClass('tile-height-dubble');
    }
    DashParrentItem.attr('tile-status','open');
    jQuery(this).parent().parent().find('.desh-sec-a').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').hide();
    jQuery(this).parent().parent().find('.desh-sec-c').show();
    

    getHcfmDashboardUpdatedTile(DashParrentItem,DashChildItem);
    if(!(jQuery('#'+DashParrentItemId +' .desh-sec-c .front-compare > div').length)){
      jQuery('#'+DashParrentItemId +' a.tile-expand-comparecallback-btn').trigger('click');
    }
  });

  jQuery(document).on('click', 'a.tile-expand-compareback-btn', function(e) {
    var DashParrentItem = jQuery(this).parent().parent().parent();
    var DashChildItem = jQuery(this).parent().parent();
    var CompareBackStatus = DashChildItem.find('.desh-sec-c').children().siblings('.compare-back').attr('compareback-status');
    if(CompareBackStatus == 'close'){
      DashChildItem.find('.desh-sec-c').children().siblings('.compare-back').show();
      DashChildItem.find('.desh-sec-c').children().siblings('.compare-back').attr('compareback-status','open');
      DashChildItem.addClass('tile-height-compare');
      jQuery(this).html('<img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-uparrow.png">');
    }else{
      DashChildItem.find('.desh-sec-c').children().siblings('.compare-back').hide();
      DashChildItem.find('.desh-sec-c').children().siblings('.compare-back').attr('compareback-status','close');
      DashChildItem.removeClass('tile-height-compare');
      jQuery(this).html('<img title="downarrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">');
    }
  });

  jQuery(document).on('click', 'a.tile-expand-resetcompare-btn', function(e) {
    var DashParrentItem = jQuery(this).parent().parent().parent();
    var DashChildItem = jQuery(this).parent().parent();    
    DashChildItem.find('.desh-sec-c').children().find('.compare-front').children().children().remove();
    DashChildItem.find('.desh-sec-c').children().find('.compare-front').children().children().remove();
  });
  ///////////////////////////////////updated extend / reduse end/////////////////



  
  /*********************************  new dashboard graph by js start*****************************************/
  /* var DasAssetSeries = Drupal.settings.m6connect_hcfm.graphData.NewGpDataArrayA;
    var DasAssetSeriesData = '';
    if(DasAssetSeries && DasAssetSeries.asset){
      var DasAssetSeriesData = DasAssetSeries.asset;
      //console.log(DasAssetSeries.asset);
      Highcharts.chart('asset-column-data-display', {
        chart: {
          type: 'column'
        },
        credits: {
          enabled: false
        },
        title: {
          text: 'Asset by Risk'
        },
        xAxis: {
          categories: ['J']
        },
        yAxis: {
          min: 0,
          title: {
            text: 'Asset'
          }
        },
        tooltip: {
          pointFormat: '<span style="color:{series.color}">{series.name}</span>: <b>{point.y}</b> ({point.percentage:.2f}%)<br/>',
          shared: true
        },
        plotOptions: {
          column: {
            stacking: 'percent'
          }
        },
        series: DasAssetSeriesData
      });
      }
    if(DasAssetSeries && DasAssetSeries.work_orders_open_pm){
      var DasAssetSeriesData = DasAssetSeries.work_orders_open_pm;
      //console.log(DasAssetSeries.work_orders_open_pm);
      Highcharts.chart('work_orders_open_pm-column-data-display', {
        chart: {
          type: 'pie',
          options3d: {
            enabled: true,
            alpha: 45,
            beta: 0
          }
        },
        credits: {
          enabled: false
        },
        title: {
          text: 'OPEN PMs'
        },
        tooltip: {
          pointFormat: '{series.name}: <b>{point.percentage:.2f}%</b>'
        },
        plotOptions: {
          pie: {
            allowPointSelect: true,
            cursor: 'pointer',
            depth: 35,
            dataLabels: {
              enabled: true,
              format: '{point.name}'
            }
          }
        },
        series: DasAssetSeriesData
      });
      }*/
  
  
  ///////////////////////////////// new dashboard graph by js end//////////////////////////////////////////
  /*
  * Display uiblock and unblock (please wait screen)  on Graph Load and Submit Setting  start
  */
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {  
      var urlajax = ajaxOptions.url;
      var hcfmgraphrander = '';
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData")){  
        if(ajaxOptions && ajaxOptions.extraData && ajaxOptions.extraData._triggering_element_value == 'Compare' || ajaxOptions.extraData._triggering_element_value == 'Submit'){
          var hcfmelvalue = ajaxOptions.extraData._triggering_element_value;
          var hcfmelname = ajaxOptions.extraData._triggering_element_name;      
          
          if(hcfmelname.split("hcfm_dashboard_compare_")){
            var hcfmmastername = hcfmelname.split("hcfm_dashboard_compare_");
            if(hcfmmastername && hcfmmastername[1]){
              hcfmgraphrander = 1;
            }
          }
          if(hcfmelname.split("hcfm_dashboard_ml_")){
            var hcfmmastername = hcfmelname.split("hcfm_dashboard_ml_");
            if(hcfmmastername && hcfmmastername[1]){
              hcfmgraphrander = 1;
            }
          }     
               
        }
      }
      if (urlajax.indexOf("hcfmdashtilerender") === 1){
        hcfmgraphrander = 1;
      }
      if(hcfmgraphrander){
            jQuery.blockUI({
              //theme:     true,
              baseZ: 2000,
              message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait...</strong></div>',
              css: {
                border: 'none',
                fadeIn: 700,
                fadeOut: 700,
                opacity: 0.96,
                //width: '11%',
                color: '#000',
                padding: '15px',
                cursor: 'wait',
                '-webkit-border-radius': '10px',
                '-moz-border-radius': '10px',
              }
            });
          } 
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      jQuery.unblockUI();
    });
  /*
  * Display uiblock and unblock (please wait screen)  on Graph Load and Submit Setting  end
  */
 
    /*
    * Hcfm Dashboard Graph Tiles Open Dispaly Save and Retrive Start
    */
    var HcfmDataRetrive = localStorage.getItem('hcfm_dash_save');
    if(HcfmDataRetrive){
      //console.log(HcfmDataRetrive);
      var HcfmDataRetriveobj = jQuery.parseJSON(HcfmDataRetrive);
      if(HcfmDataRetriveobj){
        jQuery(HcfmDataRetriveobj).each(function(index, element) {
          if(element.tilestatus == 'open'){
            //console.log(element.id);
            if(element.tileopenstatus == 'compare'){
              jQuery('#'+element.id +' a.tile-expand-compare-btn').click();
            }
            if(element.tileopenstatus == 'large'){
              jQuery('#'+element.id +' a.tile-expand-large-btn').click();
            }
            if(element.tileopenstatus == 'medium'){
              jQuery('#'+element.id +' a.tile-expand-medium-btn').click();
            }
          }
        });
      }
    }
    if(!HcfmDataRetrive){ 
      jQuery.post( '/hcfm-tile-configure/retrive', function( data ) { 
        if(data){
          var HcfmDataRetriveobj = jQuery.parseJSON(data);
          if(HcfmDataRetriveobj){
            jQuery(HcfmDataRetriveobj).each(function(index, element) {
              if(element.tilestatus == 'open'){
                //console.log(element.id);
                if(element.tileopenstatus == 'compare'){
                  jQuery('#'+element.id +' a.tile-expand-compare-btn').click();
                }
                if(element.tileopenstatus == 'large'){
                  jQuery('#'+element.id +' a.tile-expand-large-btn').click();
                }
                if(element.tileopenstatus == 'medium'){
                  jQuery('#'+element.id +' a.tile-expand-medium-btn').click();
                }
              }
            });
          }
        }
      });
    }
    /*
    * Hcfm Dashboard Graph Tiles Open Dispaly Save and Retrive End
    */
  } //Dashboard4 path end

  
  
});// reandy end

Drupal.behaviors.m6connect_hcfm = {
  attach: function (context, settings) {
  var getPath = window.location.pathname; 

  function select2loadmore(adata,selecter){
    var mockData = function () {
      var myas = [];
      jQuery.each(adata,function(akey, avalue) {      
        //console.log(akey);console.log(avalue);
        myas.push({id:akey,text:avalue});
      //};
      });
      return myas;
    };     
    jQuery(selecter).select2({
      data : mockData(),
      // init selected from elements value
      initSelection    : function (element, callback) {
        var initialData = [];
        jQuery(element.val().split(",")).each(function () {
          initialData.push({
            id  : this,
            text: this
          });
        });
        callback(initialData);
      },
      // NOT NEEDED: These are just css for the demo data
      dropdownCssClass : 'capitalize',
      containerCssClass: 'capitalize',
      // configure as multiple select      
        //multiple : true,      
      // NOT NEEDED: text for loading more results
      formatLoadMore   : 'Loading more...',
      
      // query with pagination
      query : function (q) {
        var pageSize,
          results;
        pageSize = 20; // or whatever pagesize
        results  = [];
        if (q.term && q.term !== "") {
          // HEADS UP; for the _.filter function i use underscore (actually lo-dash) here
          results = _.filter(this.data, function (e) {
            return (e.text.toUpperCase().indexOf(q.term.toUpperCase()) >= 0);
          });
        } else if (q.term === "") {
          results = this.data;
        }
        q.callback({
          results: results.slice((q.page - 1) * pageSize, q.page * pageSize),
          more   : results.length >= q.page * pageSize
        });
      }
    });
  }
  
  if(getPath == '/hcfm/work_order') {
    //Drupal.attachBehaviors(jQuery('body'));
    if(context == document){
      jQuery.post( window.location.origin+'/hcfm/assetlist/description', function( adata ) {
        select2loadmore(adata,'.wo_asset_description_new');
      });
      jQuery.post( window.location.origin+'/hcfm/assetlist/number', function( adata ) {
        select2loadmore(adata,'.wo-asset-number-new');
      });
    }
    
    jQuery('.hcfmwo_attachment_send').hide();
    jQuery('.form-item-attach1-').on('change','.form-file',function(){
      jQuery('.hcfmwo_attachment_send').trigger('mousedown');
    });
    jQuery("input:checkbox.hcfm-image-remove-update").unbind('click').bind('click',function (e) {
    var getFid = jQuery(this).val();
    var nodeId = jQuery(this).attr('for');
    // console.log(getFid);
    // console.log(nodeId);
    if(getFid){
      jQuery(this).parent().hide();
      jQuery.post( '/hcfm-update-image-reove/'+getFid+'/'+nodeId, function( data ) { 
      // console.log(data);
       if(data.status == 'updated') {
        jQuery(this).parent().hide();
      }
      });
    }
    }); 
    
  }
  if(getPath == '/hcfm/asset' ||getPath == '/hcfm/work_order' ) {
    if(context == document){
      var rowCountTable = jQuery('.asset-detail-table-new tr').length;
      if(rowCountTable > 2) {
        jQuery('table.asset-detail-table-new').DataTable({
          "bPaginate": true,
          "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
          "searching": true,
          "bInfo" : false,      
        });
      }
    // Column resizer for all HCFM table
    jQuery("table.asset-detail-table-new th").resizable({
      handles: "e",
      minHeight: jQuery("table.asset-detail-table-new th:first").height(),
      maxHeight: jQuery("table.asset-detail-table-new th:first").height(),
      minWidth: 40,
      resize: function (event, ui) {
      var sizerID = "#" + jQuery(event.target).attr("id") + "-sizer";
      jQuery(sizerID).width(ui.size.width);
      }
    });
    }
  }
  if(getPath == '/hcfm/add/configure') {
    if(context == document){
    var rowCountTable = jQuery('.asset-detail-table tr').length;
      if(rowCountTable > 2) {  
        jQuery('table.asset-detail-table').DataTable({
          "bPaginate": true,
          "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
          "searching": true,
        });
      }
    // Column resizer for all HCFM table
    jQuery("table.asset-detail-table th").resizable({
      handles: "e",
      minHeight: jQuery("table.asset-detail-table th:first").height(),
      maxHeight: jQuery("table.asset-detail-table th:first").height(),
      minWidth: 40,
      resize: function (event, ui) {
      var sizerID = "#" + jQuery(event.target).attr("id") + "-sizer";
      jQuery(sizerID).width(ui.size.width);
      }
    });
    }
  }
  
  /*hcfm asset picture*/  
  var APurl = jQuery('.asset-pictures .file a').attr('href');
  if(APurl){
    jQuery('.picture-preview-out').html('<img src="'+APurl+'" style="height: 130px;width: 150px;">');
    jQuery('.asset-picture-url').val(APurl);
  }
  jQuery('input[name="asset_pictures_remove_button"]').mousedown(function (e) {
    jQuery('.picture-preview-out').html('');
    jQuery('.asset-picture-fid').val('');
    jQuery('.asset-picture-url').val('');
  });   
  
  
   jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
        if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="floornumber_addmore"){
      if(jQuery('input.config_location_facility_floornumber').val() != ""){
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
     if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="location_floornumber_addmore"){
       if(jQuery('select.config_location_location_floornumber_select').val() != ""){
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
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="floornumber_addmore"){
          jQuery.unblockUI();
      /*if(jQuery('select.fm-facility-sel').val() != ""){
        jQuery('.locationfacility-create-container').attr('for','open');
            jQuery('.locationfacility-create-container').attr('data','edit');
            jQuery('.locationfacility-create-container').show();
      }*/
        } 
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="location_floornumber_addmore"){
           jQuery.unblockUI();
        }    
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="floornumber_addmore"){
      //console.log(ajaxOptions);
      var fNodeNid = jQuery('input.fm_facility_node_nid').val();
      //console.log('fNodeNid');
      if(fNodeNid){
      jQuery.post( '/get-facility-floordata/'+fNodeNid, function( data ) {
        //console.log(data);  
        if(data != 0 && data && data.facilityfloor) {
        jQuery.each(data.facilityfloor,function(key, value) {
          //console.log(key+','+value);
          jQuery('input.config_location_facility_floor_'+key).val(value);
        });
        }
        if(data != 0 && data && data.facilitysf) {
        jQuery.each(data.facilitysf,function(key, value) {
          //console.log(key+','+value);
          jQuery('input.config_location_facility_floorsf_'+key).val(value);
        });
        }
      });
      }
    }
    
    if (urlajax.indexOf("/hcfm-action/fm_facility/") === 0 ){     
      var Fareatype = jQuery('input.facility_area_type_values').val();
      if(Fareatype){
       //console.log(Fareatype); 
       var Fareatypelist = Fareatype.split(',');
       //console.log(Fareatypelist);
       jQuery.each(Fareatypelist,function(key, Fareatypevalue) {  
       //console.log(Fareatypevalue);
         jQuery('select.config_location_facility_areatype option[value='+Fareatypevalue+']').attr("selected", true);
       }); 
      }
    }
    if (urlajax.indexOf("/hcfm-action/fm_work_order/") === 0 ){     
      var OutsideVender = jQuery('input.wo_outside_vendors_values').val();
      if(OutsideVender){
       // console.log(OutsideVender); 
       var Outsidevenderlist = OutsideVender.split(',');
       //console.log(Fareatypelist);
       jQuery.each(Outsidevenderlist,function(key, Outsidevendervalue) {  
       //console.log(Fareatypevalue);
         jQuery('select.wo-outside-vendors option[value='+Outsidevendervalue+']').attr("selected", true);
       }); 
      }
    }
    
    var LFloorArray = [];
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="config_location_pick_facility"){
    //console.log(urlajax);
    //console.log(ajaxOptions);
      var LFloors = jQuery('input.location_location_numberoffloor_values').val();
      
      if(LFloors){
       // console.log(LFloors); 
       var LFloorslist = LFloors.split(',');
       //console.log(Fareatypelist);
       jQuery.each(LFloorslist,function(key, LFloorsvalue) {  
       //console.log(LFloorsvalue);     
       LFloorArray.push(LFloorsvalue);
         jQuery('select.config_location_location_numberoffloor option[value='+LFloorsvalue+']').attr("selected", true);
         jQuery('select.config_location_location_numberoffloor').trigger('change');
         jQuery('input.location_location_numberoffloor_values').val('');
       });
       
       
       
       
       
       
       //location zone floor field 
      if(jQuery('input.fm_location_location_node_nid').val()){
        var LFloorOp = jQuery(".config_location_location_numberoffloor");
        var LFloorOpSelectedLength = LFloorOp[0].selectedOptions.length;
        var LFloorOpSelected =jQuery(".form-item-config-location-location-numberoffloor .ms-options-wrap .ms-options ul.list-unstyled li label input");
        //console.log( LFloorOp[0].options.length);
        for (var i = 0; i < LFloorOp[0].options.length; i++) {
        var LFloorIndex = '';
        var LFloorText = '';
        var LFloorValue = '';
        if(LFloorOp[0].options[i].selected ==true){
          LFloorIndex = LFloorOp[0].options[i].index;
          LFloorText = LFloorOp[0].options[i].text;
          LFloorValue = LFloorOp[0].options[i].value;     
          if(LFloorOpSelected[i].value == LFloorValue){     
          jQuery(LFloorOpSelected[LFloorIndex].closest('li')).addClass('selected');
          jQuery(LFloorOpSelected[LFloorIndex]).attr('checked',true);
          }
          
        }
        }
        //if(LFloorOpSelectedLength){
        jQuery('select.config_location_location_floornumber_select').val(LFloorOpSelectedLength);
        jQuery('.config_location_numberoffloor_btn').trigger('click');
        //}
      }
       
       
       
        
      }
      if(jQuery('select.config_location_location_floornumber_select').val() != ''){
        jQuery('select.config_location_location_floornumber_select').val('');
        jQuery('input.config_location_location_floornumber_addmore').trigger('mousedown');
      }
      
      
      
      
    }
    /*if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get_facility"){
      if(jQuery('select.fm-facility-sel').val() != ""){
        jQuery('.locationfacility-create-container').attr('for','open');
            jQuery('.locationfacility-create-container').attr('data','edit');
            jQuery('.locationfacility-create-container').show();
      }         
    }*/
    
    
    /*if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get_preferred_vendor"){
      console.log(urlajax);
      console.log(ajaxOptions);
      
      console.log(pfCountry);
     
      
    }
    var pfCountry = jQuery('select.config_preferred_vendors_country').val();
     if (urlajax.indexOf("/get-state-list-countrycode/"+pfCountry) === 0){
        console.log('in country');
        console.log(ajaxOptions);
        
      }*/
    //console.log(ajaxOptions);  
    //console.log(ajaxOptions);
    
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get_preferred_vendor"){
      var hasvcom = jQuery('select.config_preferred_vendors_company').val();
      // console.log(hasvcom); 
      if(hasvcom){
        jQuery('select.config_preferred_vendors_company').trigger('change');
      }
    }
    
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get_facility"){
      if(context == document){        
      var Fareatype = jQuery('input.facility_area_type_values').val();
      if(Fareatype){
         //console.log(Fareatype); 
         var Fareatypelist = Fareatype.split(',');
         //console.log(Fareatypelist);
         jQuery.each(Fareatypelist,function(key, Fareatypevalue) {  
         //console.log(Fareatypevalue);
         jQuery('select.config_location_facility_areatype option[value='+Fareatypevalue+']').attr("selected", true);
         }); 
      }
      }
    }
    //if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="get_workorder"){
    //work order edit opraction   
      if(context == document){      
      var OutsideVender = jQuery('input.wo_outside_vendors_values').val();
      if(OutsideVender){
         //console.log(OutsideVender); 
         var Outsidevenderlist = OutsideVender.split(',');
         //console.log(Fareatypelist);
         jQuery.each(Outsidevenderlist,function(key, Outsidevendervalue) {  
         //console.log(Fareatypevalue);
         jQuery('select.wo-outside-vendors option[value='+Outsidevendervalue+']').attr("selected", true);
         }); 
      }
      if(jQuery('input.wo-node-nid').val()){
        var WoutsidevendorOp = jQuery(".wo-outside-vendors");
        var WoutsidevendorOpSelected =jQuery(".form-item-wo-outside-vendors .ms-options-wrap .ms-options ul.list-unstyled li label input");
        //console.log( WoutsidevendorOp[0].options.length);
        for (var i = 0; i < WoutsidevendorOp[0].options.length; i++) {
        var areaIndex = '';
        var areaText = '';
        var areaValue = '';
        if(WoutsidevendorOp[0].options[i].selected ==true){
          areaIndex = WoutsidevendorOp[0].options[i].index;
          areaText = WoutsidevendorOp[0].options[i].text;
          areaValue = WoutsidevendorOp[0].options[i].value;
          //console.log(areaIndex);
          //console.log(areaText);
          //console.log(areaValue);
          if(WoutsidevendorOpSelected[i].value == areaValue){     
          jQuery(WoutsidevendorOpSelected[areaIndex].closest('li')).addClass('selected');
          jQuery(WoutsidevendorOpSelected[areaIndex]).attr('checked',true);
          }
        }
        }
      }
      }
    //}
    })
  
  //location zone
    var tblrows = jQuery("#location-option-wrapper .row");       
  tblrows.each(function (index) {
    var tblrow = jQuery(this);
    var getTotalSf = tblrow.find(".location_totalsf").val();
    var getSf = tblrow.find(".location_floorratiovalue").val();
    var getFloorratio = tblrow.find(".location_floorratio").val();
   
    tblrow.find(".location_floorratiovalue").keyup (function (e) {
    var SfValue = jQuery(this).val();
    var putFloorRatio = '';
    putFloorRatio = SfValue*100/getTotalSf; 
    tblrow.find(".location_floorratio").val(putFloorRatio);   
    });
    tblrow.find(".location_floorratio").keyup (function (e) {
    var FloorRatio = jQuery(this).val(); 
    var putSfValue = '';
    putSfValue = getTotalSf*FloorRatio/100;
    tblrow.find(".location_floorratiovalue").val(putSfValue);
    });
  }); 
  
/*  if(getPath == '/hcfm/dashboard4') {
  jQuery('#Tile-a select.bhcfmdash-region-list').multiselect({
      columns: 1,
    placeholder: 'Select region'
    });
     jQuery('#Tile-a select.bhcfmdash-site-list').multiselect({
      columns: 2,
    placeholder: 'Select site'
    });
  }*/
  if(getPath == '/hcfm/add/configure') {
    jQuery('select.config_location_location_numberoffloor').multiselect({
      columns: 1,
    placeholder: 'Select Floor(s)'
    });
    jQuery('select.config_location_facility_areatype').multiselect({
    columns: 2,
    placeholder: 'Select Area Type',   
    });
    jQuery('select.config_preferred_vendors_user').multiselect({
    columns: 2,
    placeholder: 'Select User',  
    });
  }
  if(getPath == '/hcfm/work_order') {
    jQuery('select.wo-outside-vendors').multiselect({
    columns: 2,
    placeholder: 'Select Vendors',   
    });
    jQuery('select.wo-outside-vendors-1').multiselect({
    columns: 2,
    placeholder: 'Select Vendors',   
    });
  }
    //location facility area type field
  if(jQuery('input.fm_facility_node_nid').val()){
    var FareatypeOp = jQuery(".config_location_facility_areatype");
    var FareatypeOpSelected =jQuery(".form-item-config-location-facility-areatype .ms-options-wrap .ms-options ul.list-unstyled li label input");
    //console.log( FareatypeOp[0].options.length);
    for (var i = 0; i < FareatypeOp[0].options.length; i++) {
    var areaIndex = '';
    var areaText = '';
    var areaValue = '';
    if(FareatypeOp[0].options[i].selected ==true){
      areaIndex = FareatypeOp[0].options[i].index;
      areaText = FareatypeOp[0].options[i].text;
      areaValue = FareatypeOp[0].options[i].value;
      //console.log(areaIndex);
      //console.log(areaText);
      //console.log(areaValue);
      if(FareatypeOpSelected[i].value == areaValue){      
      jQuery(FareatypeOpSelected[areaIndex].closest('li')).addClass('selected');
      jQuery(FareatypeOpSelected[areaIndex]).attr('checked',true);
      }
    }
    }
  }
  
  
  //****************************************** add new btn and close and edit ***** start  ******************************************///
  jQuery('.hcfm-action-btn .dropdown ul.dropdown-menu li a.use-ajax').click(function (e) {
      jQuery(this).closest('.dropdown').removeClass('open');
    }); 
  /////////////////////  asset system start ////////////////
  jQuery('.assetsystem-create-container').hide();
  jQuery('.assetsystem-create-container').attr('for','closed');
  //click on close btn
  jQuery('.crb-config-asset-system').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.assetsystem-create-container').hide();    
      jQuery('.assetsystem-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_asset_system-detail').click(function (e) {
      jQuery('.assetsystem-create-container').attr('for','open');
      jQuery('.assetsystem-create-container').attr('data','edit');
      jQuery('.assetsystem-create-container').show();         
      e.preventDefault();      
    }); 
  //click on add new
  jQuery('.new-assetsystem-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.assetsystem-create-container').attr('for');
    var dataAttr = jQuery('.assetsystem-create-container').attr('data');
    if(status == 'open' && jQuery('.assetsystem-create-container').attr('data') == 'edit') {
    jQuery('.assetsystem-create-container').removeAttr('data');   
    jQuery('.assetsystem-create-container').show(); 
    jQuery('.assetsystem-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.assetsystem-create-container').attr('data') == 'edit') {   
        jQuery('.assetsystem-create-container').removeAttr('data');         
    jQuery('.assetsystem-create-container').show();     
    jQuery('.assetsystem-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.assetsystem-create-container').attr('for','open');
    jQuery('.assetsystem-create-container').show(); 
    jQuery('.assetsystem-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.assetsystem-create-container').hide();
      jQuery('.assetsystem-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.assetsystem-create-container').attr('data') == 'edit') { 
      jQuery('.assetsystem-create-container .clear-data').val('');
      jQuery('.assetsystem-create-container').removeAttr('data');     
    jQuery('.assetsystem-create-container').show();   
    }
    else if(jQuery( ".assetsystem-create-container" ).attr('data') == 'edit') {   
      jQuery('.assetsystem-create-container').show();
    jQuery('.assetsystem-create-container').attr('for','open');
      }   
  });
  /////////////////////  asset system end ////////////////
  /////////////////////  asset sub system start ////////////////
  jQuery('.assetsubsystem-create-container').hide();
  jQuery('.assetsubsystem-create-container').attr('for','closed');
  //click on close btn
  jQuery('.crb-config-asset-subsystem').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.assetsubsystem-create-container').hide();    
      jQuery('.assetsubsystem-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_asset_sub_system-detail').click(function (e) {
      jQuery('.assetsubsystem-create-container').attr('for','open');
      jQuery('.assetsubsystem-create-container').attr('data','edit');
      jQuery('.assetsubsystem-create-container').show();         
      e.preventDefault();      
    }); 
  //click on add new
  jQuery('.new-assetsubsystem-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.assetsubsystem-create-container').attr('for');
    var dataAttr = jQuery('.assetsubsystem-create-container').attr('data');
    if(status == 'open' && jQuery('.assetsubsystem-create-container').attr('data') == 'edit') {
    jQuery('.assetsubsystem-create-container').removeAttr('data');    
    jQuery('.assetsubsystem-create-container').show();  
    jQuery('.assetsubsystem-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.assetsubsystem-create-container').attr('data') == 'edit') {   
        jQuery('.assetsubsystem-create-container').removeAttr('data');         
    jQuery('.assetsubsystem-create-container').show();      
    jQuery('.assetsubsystem-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.assetsubsystem-create-container').attr('for','open');
    jQuery('.assetsubsystem-create-container').show();  
    jQuery('.assetsubsystem-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.assetsubsystem-create-container').hide();
      jQuery('.assetsubsystem-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.assetsubsystem-create-container').attr('data') == 'edit') { 
      jQuery('.assetsubsystem-create-container .clear-data').val('');
      jQuery('.assetsubsystem-create-container').removeAttr('data');    
    jQuery('.assetsubsystem-create-container').show();    
    }
    else if(jQuery( ".assetsubsystem-create-container" ).attr('data') == 'edit') {    
      jQuery('.assetsubsystem-create-container').show();
    jQuery('.assetsubsystem-create-container').attr('for','open');
      }   
  });
  /////////////////////  asset sub system end ////////////////
  /////////////////////  asset device type start ////////////////
  jQuery('.assetdevicetype-create-container').hide();
  jQuery('.assetdevicetype-create-container').attr('for','closed');
  //click on close btn
  jQuery('.crb-config-asset-devicetype').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.assetdevicetype-create-container').hide();    
      jQuery('.assetdevicetype-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_asset_device_type-detail').click(function (e) {
      jQuery('.assetdevicetype-create-container').attr('for','open');
      jQuery('.assetdevicetype-create-container').attr('data','edit');
      jQuery('.assetdevicetype-create-container').show();         
      e.preventDefault();      
    }); 
  //click on add new
  jQuery('.new-assetdevicetype-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.assetdevicetype-create-container').attr('for');
    var dataAttr = jQuery('.assetdevicetype-create-container').attr('data');
    if(status == 'open' && jQuery('.assetdevicetype-create-container').attr('data') == 'edit') {
    jQuery('.assetdevicetype-create-container').removeAttr('data');   
    jQuery('.assetdevicetype-create-container').show(); 
    jQuery('.assetdevicetype-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.assetdevicetype-create-container').attr('data') == 'edit') {   
        jQuery('.assetdevicetype-create-container').removeAttr('data');         
    jQuery('.assetdevicetype-create-container').show();     
    jQuery('.assetdevicetype-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.assetdevicetype-create-container').attr('for','open');
    jQuery('.assetdevicetype-create-container').show(); 
    jQuery('.assetdevicetype-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.assetdevicetype-create-container').hide();
      jQuery('.assetdevicetype-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.assetdevicetype-create-container').attr('data') == 'edit') { 
      jQuery('.assetdevicetype-create-container .clear-data').val('');
      jQuery('.assetdevicetype-create-container').removeAttr('data');     
    jQuery('.assetdevicetype-create-container').show();   
    }
    else if(jQuery( ".assetdevicetype-create-container" ).attr('data') == 'edit') {   
      jQuery('.assetdevicetype-create-container').show();
    jQuery('.assetdevicetype-create-container').attr('for','open');
      }   
  });
  /////////////////////  asset device type end ////////////////
  /////////////////////  asset status start ////////////////
  jQuery('.assetstatus-create-container').hide();
  jQuery('.assetstatus-create-container').attr('for','closed');
  //click on close btn
  jQuery('.crb-config-asset-status').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.assetstatus-create-container').hide();    
      jQuery('.assetstatus-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_asset_status-detail').click(function (e) {
      jQuery('.assetstatus-create-container').attr('for','open');
      jQuery('.assetstatus-create-container').attr('data','edit');
      jQuery('.assetstatus-create-container').show();         
      e.preventDefault();      
    }); 
  //click on add new
  jQuery('.new-assetstatus-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.assetstatus-create-container').attr('for');
    var dataAttr = jQuery('.assetstatus-create-container').attr('data');
    if(status == 'open' && jQuery('.assetstatus-create-container').attr('data') == 'edit') {
    jQuery('.assetstatus-create-container').removeAttr('data');   
    jQuery('.assetstatus-create-container').show(); 
    jQuery('.assetstatus-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.assetstatus-create-container').attr('data') == 'edit') {   
        jQuery('.assetstatus-create-container').removeAttr('data');         
    jQuery('.assetstatus-create-container').show();     
    jQuery('.assetstatus-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.assetstatus-create-container').attr('for','open');
    jQuery('.assetstatus-create-container').show(); 
    jQuery('.assetstatus-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.assetstatus-create-container').hide();
      jQuery('.assetstatus-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.assetstatus-create-container').attr('data') == 'edit') { 
      jQuery('.assetstatus-create-container .clear-data').val('');
      jQuery('.assetstatus-create-container').removeAttr('data');     
    jQuery('.assetstatus-create-container').show();   
    }
    else if(jQuery( ".assetstatus-create-container" ).attr('data') == 'edit') {   
      jQuery('.assetstatus-create-container').show();
    jQuery('.assetstatus-create-container').attr('for','open');
      }   
  }); 
  /////////////////////  asset status end ////////////////
  /////////////////////  fm account number start ////////////////
  jQuery('.accountnumber-create-container').hide();
  jQuery('.accountnumber-create-container').attr('for','closed');
  //click on close btn
  jQuery('.crb-account-number').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.accountnumber-create-container').hide();    
      jQuery('.accountnumber-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_account_number-detail').click(function (e) {
      jQuery('.accountnumber-create-container').attr('for','open');
      jQuery('.accountnumber-create-container').attr('data','edit');
      jQuery('.accountnumber-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-accountnumber-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.accountnumber-create-container').attr('for');
    var dataAttr = jQuery('.accountnumber-create-container').attr('data');
    if(status == 'open' && jQuery('.accountnumber-create-container').attr('data') == 'edit') {
    jQuery('.accountnumber-create-container').removeAttr('data');   
    jQuery('.accountnumber-create-container').show(); 
    jQuery('.accountnumber-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.accountnumber-create-container').attr('data') == 'edit') {   
        jQuery('.accountnumber-create-container').removeAttr('data');         
    jQuery('.accountnumber-create-container').show();     
    jQuery('.accountnumber-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.accountnumber-create-container').attr('for','open');
    jQuery('.accountnumber-create-container').show(); 
    jQuery('.accountnumber-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.accountnumber-create-container').hide();
      jQuery('.accountnumber-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.accountnumber-create-container').attr('data') == 'edit') { 
      jQuery('.accountnumber-create-container .clear-data').val('');
      jQuery('.accountnumber-create-container').removeAttr('data');     
    jQuery('.accountnumber-create-container').show();   
    }
    else if(jQuery( ".accountnumber-create-container" ).attr('data') == 'edit') {   
      jQuery('.accountnumber-create-container').show();
    jQuery('.accountnumber-create-container').attr('for','open');
      }   
  }); 
  /////////////////////  fm account number end ////////////////
  /////////////////////  fm risk rank  start ////////////////
  jQuery('.assetriskrank-create-container').hide();
  jQuery('.assetriskrank-create-container').attr('for','closed'); 
  //click on close btn
  jQuery('.crb-config-riskrank').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.assetriskrank-create-container').hide();    
      jQuery('.assetriskrank-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_risk_rank-detail').click(function (e) {
      jQuery('.assetriskrank-create-container').attr('for','open');
      jQuery('.assetriskrank-create-container').attr('data','edit');
      jQuery('.assetriskrank-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-assetriskrank-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.assetriskrank-create-container').attr('for');
    var dataAttr = jQuery('.assetriskrank-create-container').attr('data');
    if(status == 'open' && jQuery('.assetriskrank-create-container').attr('data') == 'edit') {
    jQuery('.assetriskrank-create-container').removeAttr('data');   
    jQuery('.assetriskrank-create-container').show(); 
    jQuery('.assetriskrank-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.assetriskrank-create-container').attr('data') == 'edit') {   
        jQuery('.assetriskrank-create-container').removeAttr('data');         
    jQuery('.assetriskrank-create-container').show();     
    jQuery('.assetriskrank-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.assetriskrank-create-container').attr('for','open');
    jQuery('.assetriskrank-create-container').show(); 
    jQuery('.assetriskrank-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.assetriskrank-create-container').hide();
      jQuery('.assetriskrank-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.assetriskrank-create-container').attr('data') == 'edit') { 
      jQuery('.assetriskrank-create-container .clear-data').val('');
      jQuery('.assetriskrank-create-container').removeAttr('data');     
    jQuery('.assetriskrank-create-container').show();   
    }
    else if(jQuery( ".assetriskrank-create-container" ).attr('data') == 'edit') {   
      jQuery('.assetriskrank-create-container').show();
    jQuery('.assetriskrank-create-container').attr('for','open');
      }   
  }); 
  /////////////////////  fm risk rank  end ////////////////
  /////////////////////  fm problem code  start ////////////////
  jQuery('.woproblemcode-create-container').hide();
  jQuery('.woproblemcode-create-container').attr('for','closed'); 
  //click on close btn
  jQuery('.crb-config-wo-problemcode').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.woproblemcode-create-container').hide();    
      jQuery('.woproblemcode-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_problem_code-detail').click(function (e) {
      jQuery('.woproblemcode-create-container').attr('for','open');
      jQuery('.woproblemcode-create-container').attr('data','edit');
      jQuery('.woproblemcode-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-woproblemcode-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.woproblemcode-create-container').attr('for');
    var dataAttr = jQuery('.woproblemcode-create-container').attr('data');
    if(status == 'open' && jQuery('.woproblemcode-create-container').attr('data') == 'edit') {
    jQuery('.woproblemcode-create-container').removeAttr('data');   
    jQuery('.woproblemcode-create-container').show(); 
    jQuery('.woproblemcode-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.woproblemcode-create-container').attr('data') == 'edit') {   
        jQuery('.woproblemcode-create-container').removeAttr('data');         
    jQuery('.woproblemcode-create-container').show();     
    jQuery('.woproblemcode-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.woproblemcode-create-container').attr('for','open');
    jQuery('.woproblemcode-create-container').show(); 
    jQuery('.woproblemcode-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.woproblemcode-create-container').hide();
      jQuery('.woproblemcode-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.woproblemcode-create-container').attr('data') == 'edit') { 
      jQuery('.woproblemcode-create-container .clear-data').val('');
      jQuery('.woproblemcode-create-container').removeAttr('data');     
    jQuery('.woproblemcode-create-container').show();   
    }
    else if(jQuery( ".woproblemcode-create-container" ).attr('data') == 'edit') {   
      jQuery('.woproblemcode-create-container').show();
    jQuery('.woproblemcode-create-container').attr('for','open');
      }   
  });
  /////////////////////  fm problem code  end ////////////////
  /////////////////////  work order type  start ////////////////
  jQuery('.wotype-create-container').hide();
  jQuery('.wotype-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-wo-type').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.wotype-create-container').hide();    
      jQuery('.wotype-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_work_order_type-detail').click(function (e) {
      jQuery('.wotype-create-container').attr('for','open');
      jQuery('.wotype-create-container').attr('data','edit');
      jQuery('.wotype-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-wotype-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.wotype-create-container').attr('for');
    var dataAttr = jQuery('.wotype-create-container').attr('data');
    if(status == 'open' && jQuery('.wotype-create-container').attr('data') == 'edit') {
    jQuery('.wotype-create-container').removeAttr('data');    
    jQuery('.wotype-create-container').show();  
    jQuery('.wotype-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.wotype-create-container').attr('data') == 'edit') {   
        jQuery('.wotype-create-container').removeAttr('data');         
    jQuery('.wotype-create-container').show();      
    jQuery('.wotype-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.wotype-create-container').attr('for','open');
    jQuery('.wotype-create-container').show();  
    jQuery('.wotype-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.wotype-create-container').hide();
      jQuery('.wotype-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.wotype-create-container').attr('data') == 'edit') { 
      jQuery('.wotype-create-container .clear-data').val('');
      jQuery('.wotype-create-container').removeAttr('data');    
    jQuery('.wotype-create-container').show();    
    }
    else if(jQuery( ".wotype-create-container" ).attr('data') == 'edit') {    
      jQuery('.wotype-create-container').show();
    jQuery('.wotype-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order type  end ////////////////
  /////////////////////  work order status  start ////////////////
  jQuery('.wostatus-create-container').hide();
  jQuery('.wostatus-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-wo-status').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.wostatus-create-container').hide();    
      jQuery('.wostatus-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_work_order_status-detail').click(function (e) {
      jQuery('.wostatus-create-container').attr('for','open');
      jQuery('.wostatus-create-container').attr('data','edit');
      jQuery('.wostatus-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-wostatus-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.wostatus-create-container').attr('for');
    var dataAttr = jQuery('.wostatus-create-container').attr('data');
    if(status == 'open' && jQuery('.wostatus-create-container').attr('data') == 'edit') {
    jQuery('.wostatus-create-container').removeAttr('data');    
    jQuery('.wostatus-create-container').show();  
    jQuery('.wostatus-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.wostatus-create-container').attr('data') == 'edit') {   
        jQuery('.wostatus-create-container').removeAttr('data');         
    jQuery('.wostatus-create-container').show();      
    jQuery('.wostatus-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.wostatus-create-container').attr('for','open');
    jQuery('.wostatus-create-container').show();  
    jQuery('.wostatus-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.wostatus-create-container').hide();
      jQuery('.wostatus-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.wostatus-create-container').attr('data') == 'edit') { 
      jQuery('.wostatus-create-container .clear-data').val('');
      jQuery('.wostatus-create-container').removeAttr('data');    
    jQuery('.wostatus-create-container').show();    
    }
    else if(jQuery( ".wostatus-create-container" ).attr('data') == 'edit') {    
      jQuery('.wostatus-create-container').show();
    jQuery('.wostatus-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order status  end ////////////////
  /////////////////////  fm skill  start ////////////////
  jQuery('.woskill-create-container').hide();
  jQuery('.woskill-create-container').attr('for','closed'); 
  //click on close btn
  jQuery('.crb-config-wo-skill').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.woskill-create-container').hide();    
      jQuery('.woskill-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_skill-detail').click(function (e) {
      jQuery('.woskill-create-container').attr('for','open');
      jQuery('.woskill-create-container').attr('data','edit');
      jQuery('.woskill-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-woskill-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.woskill-create-container').attr('for');
    var dataAttr = jQuery('.woskill-create-container').attr('data');
    if(status == 'open' && jQuery('.woskill-create-container').attr('data') == 'edit') {
    jQuery('.woskill-create-container').removeAttr('data');   
    jQuery('.woskill-create-container').show(); 
    jQuery('.woskill-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.woskill-create-container').attr('data') == 'edit') {   
        jQuery('.woskill-create-container').removeAttr('data');         
    jQuery('.woskill-create-container').show();     
    jQuery('.woskill-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.woskill-create-container').attr('for','open');
    jQuery('.woskill-create-container').show(); 
    jQuery('.woskill-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.woskill-create-container').hide();
      jQuery('.woskill-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.woskill-create-container').attr('data') == 'edit') { 
      jQuery('.woskill-create-container .clear-data').val('');
      jQuery('.woskill-create-container').removeAttr('data');     
    jQuery('.woskill-create-container').show();   
    }
    else if(jQuery( ".woskill-create-container" ).attr('data') == 'edit') {   
      jQuery('.woskill-create-container').show();
    jQuery('.woskill-create-container').attr('for','open');
      }   
  });
  /////////////////////  fm skill  end ////////////////
  /////////////////////  work order priorty  start ////////////////
  jQuery('.wopriorty-create-container').hide();
  jQuery('.wopriorty-create-container').attr('for','closed'); 
  //click on close btn
  jQuery('.crb-config-wo-priorty').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.wopriorty-create-container').hide();    
      jQuery('.wopriorty-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_priorty-detail').click(function (e) {
      jQuery('.wopriorty-create-container').attr('for','open');
      jQuery('.wopriorty-create-container').attr('data','edit');
      jQuery('.wopriorty-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-wopriorty-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.wopriorty-create-container').attr('for');
    var dataAttr = jQuery('.wopriorty-create-container').attr('data');
    if(status == 'open' && jQuery('.wopriorty-create-container').attr('data') == 'edit') {
    jQuery('.wopriorty-create-container').removeAttr('data');   
    jQuery('.wopriorty-create-container').show(); 
    jQuery('.wopriorty-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.wopriorty-create-container').attr('data') == 'edit') {   
        jQuery('.wopriorty-create-container').removeAttr('data');         
    jQuery('.wopriorty-create-container').show();     
    jQuery('.wopriorty-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.wopriorty-create-container').attr('for','open');
    jQuery('.wopriorty-create-container').show(); 
    jQuery('.wopriorty-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.wopriorty-create-container').hide();
      jQuery('.wopriorty-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.wopriorty-create-container').attr('data') == 'edit') { 
      jQuery('.wopriorty-create-container .clear-data').val('');
      jQuery('.wopriorty-create-container').removeAttr('data');     
    jQuery('.wopriorty-create-container').show();   
    }
    else if(jQuery( ".wopriorty-create-container" ).attr('data') == 'edit') {   
      jQuery('.wopriorty-create-container').show();
    jQuery('.wopriorty-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order priorty  end ////////////////
  /////////////////////  work order resource  start ////////////////
  jQuery('.woresource-create-container').hide();
  jQuery('.woresource-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-wo-resource').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.woresource-create-container').hide();    
      jQuery('.woresource-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_resource-detail').click(function (e) {
      jQuery('.woresource-create-container').attr('for','open');
      jQuery('.woresource-create-container').attr('data','edit');
      jQuery('.woresource-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-woresource-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.woresource-create-container').attr('for');
    var dataAttr = jQuery('.woresource-create-container').attr('data');
    if(status == 'open' && jQuery('.woresource-create-container').attr('data') == 'edit') {
    jQuery('.woresource-create-container').removeAttr('data');    
    jQuery('.woresource-create-container').show();  
    jQuery('.woresource-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.woresource-create-container').attr('data') == 'edit') {   
        jQuery('.woresource-create-container').removeAttr('data');         
    jQuery('.woresource-create-container').show();      
    jQuery('.woresource-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.woresource-create-container').attr('for','open');
    jQuery('.woresource-create-container').show();  
    jQuery('.woresource-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.woresource-create-container').hide();
      jQuery('.woresource-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.woresource-create-container').attr('data') == 'edit') { 
      jQuery('.woresource-create-container .clear-data').val('');
      jQuery('.woresource-create-container').removeAttr('data');    
    jQuery('.woresource-create-container').show();    
    }
    else if(jQuery( ".woresource-create-container" ).attr('data') == 'edit') {    
      jQuery('.woresource-create-container').show();
    jQuery('.woresource-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order resource  end ////////////////
  /////////////////////  work order special tag  start ////////////////
  jQuery('.specialtag-create-container').hide();
  jQuery('.specialtag-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-wo-needed-permit').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.specialtag-create-container').hide();    
      jQuery('.specialtag-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_special_tag-detail').click(function (e) {
      jQuery('.specialtag-create-container').attr('for','open');
      jQuery('.specialtag-create-container').attr('data','edit');
      jQuery('.specialtag-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-specialtag-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.specialtag-create-container').attr('for');
    var dataAttr = jQuery('.specialtag-create-container').attr('data');
    if(status == 'open' && jQuery('.specialtag-create-container').attr('data') == 'edit') {
    jQuery('.specialtag-create-container').removeAttr('data');    
    jQuery('.specialtag-create-container').show();  
    jQuery('.specialtag-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.specialtag-create-container').attr('data') == 'edit') {   
        jQuery('.specialtag-create-container').removeAttr('data');         
    jQuery('.specialtag-create-container').show();      
    jQuery('.specialtag-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.specialtag-create-container').attr('for','open');
    jQuery('.specialtag-create-container').show();  
    jQuery('.specialtag-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.specialtag-create-container').hide();
      jQuery('.specialtag-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.specialtag-create-container').attr('data') == 'edit') { 
      jQuery('.specialtag-create-container .clear-data').val('');
      jQuery('.specialtag-create-container').removeAttr('data');    
    jQuery('.specialtag-create-container').show();    
    }
    else if(jQuery( ".specialtag-create-container" ).attr('data') == 'edit') {    
      jQuery('.specialtag-create-container').show();
    jQuery('.specialtag-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order special tag  end ////////////////
  /////////////////////  work order needed permit  start ////////////////
  jQuery('.neededpermit-create-container').hide();
  jQuery('.neededpermit-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-wo-special-tag').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.neededpermit-create-container').hide();    
      jQuery('.neededpermit-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_needed_permit-detail').click(function (e) {
      jQuery('.neededpermit-create-container').attr('for','open');
      jQuery('.neededpermit-create-container').attr('data','edit');
      jQuery('.neededpermit-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-neededpermit-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.neededpermit-create-container').attr('for');
    var dataAttr = jQuery('.neededpermit-create-container').attr('data');
    if(status == 'open' && jQuery('.neededpermit-create-container').attr('data') == 'edit') {
    jQuery('.neededpermit-create-container').removeAttr('data');    
    jQuery('.neededpermit-create-container').show();  
    jQuery('.neededpermit-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.neededpermit-create-container').attr('data') == 'edit') {   
        jQuery('.neededpermit-create-container').removeAttr('data');         
    jQuery('.neededpermit-create-container').show();      
    jQuery('.neededpermit-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.neededpermit-create-container').attr('for','open');
    jQuery('.neededpermit-create-container').show();  
    jQuery('.neededpermit-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.neededpermit-create-container').hide();
      jQuery('.neededpermit-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.neededpermit-create-container').attr('data') == 'edit') { 
      jQuery('.neededpermit-create-container .clear-data').val('');
      jQuery('.neededpermit-create-container').removeAttr('data');    
    jQuery('.neededpermit-create-container').show();    
    }
    else if(jQuery( ".neededpermit-create-container" ).attr('data') == 'edit') {    
      jQuery('.neededpermit-create-container').show();
    jQuery('.neededpermit-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order needed permit   end ////////////////
  /////////////////////  location region  start ////////////////
  jQuery('.locationregion-create-container').hide();
  jQuery('.locationregion-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-location-region').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.locationregion-create-container').hide();    
      jQuery('.locationregion-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_location_region-detail').click(function (e) {
      jQuery('.locationregion-create-container').attr('for','open');
      jQuery('.locationregion-create-container').attr('data','edit');
      jQuery('.locationregion-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-locationregion-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.locationregion-create-container').attr('for');
    var dataAttr = jQuery('.locationregion-create-container').attr('data');
    if(status == 'open' && jQuery('.locationregion-create-container').attr('data') == 'edit') {
    jQuery('.locationregion-create-container').removeAttr('data');    
    jQuery('.locationregion-create-container').show();  
    jQuery('.locationregion-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.locationregion-create-container').attr('data') == 'edit') {   
        jQuery('.locationregion-create-container').removeAttr('data');         
    jQuery('.locationregion-create-container').show();      
    jQuery('.locationregion-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.locationregion-create-container').attr('for','open');
    jQuery('.locationregion-create-container').show();  
    jQuery('.locationregion-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.locationregion-create-container').hide();
      jQuery('.locationregion-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.locationregion-create-container').attr('data') == 'edit') { 
      jQuery('.locationregion-create-container .clear-data').val('');
      jQuery('.locationregion-create-container').removeAttr('data');    
    jQuery('.locationregion-create-container').show();    
    }
    else if(jQuery( ".locationregion-create-container" ).attr('data') == 'edit') {    
      jQuery('.locationregion-create-container').show();
    jQuery('.locationregion-create-container').attr('for','open');
      }   
  });
  /////////////////////  location region  end ////////////////
  /////////////////////  location site  start ////////////////
  jQuery('.locationsite-create-container').hide();
  jQuery('.locationsite-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-location-site').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.locationsite-create-container').hide();    
      jQuery('.locationsite-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_location_site-detail').click(function (e) {
      jQuery('.locationsite-create-container').attr('for','open');
      jQuery('.locationsite-create-container').attr('data','edit');
      jQuery('.locationsite-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-locationsite-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.locationsite-create-container').attr('for');
    var dataAttr = jQuery('.locationsite-create-container').attr('data');
    if(status == 'open' && jQuery('.locationsite-create-container').attr('data') == 'edit') {
    jQuery('.locationsite-create-container').removeAttr('data');    
    jQuery('.locationsite-create-container').show();  
    jQuery('.locationsite-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.locationsite-create-container').attr('data') == 'edit') {   
        jQuery('.locationsite-create-container').removeAttr('data');         
    jQuery('.locationsite-create-container').show();      
    jQuery('.locationsite-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.locationsite-create-container').attr('for','open');
    jQuery('.locationsite-create-container').show();  
    jQuery('.locationsite-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.locationsite-create-container').hide();
      jQuery('.locationsite-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.locationsite-create-container').attr('data') == 'edit') { 
      jQuery('.locationsite-create-container .clear-data').val('');
      jQuery('.locationsite-create-container').removeAttr('data');    
    jQuery('.locationsite-create-container').show();    
    }
    else if(jQuery( ".locationsite-create-container" ).attr('data') == 'edit') {    
      jQuery('.locationsite-create-container').show();
    jQuery('.locationsite-create-container').attr('for','open');
      }   
  });
  /////////////////////  location site  end ////////////////
  /////////////////////  facility type and facility area type  start ////////////////
  jQuery('.facilitytype-create-container').hide();
  jQuery('.facilitytype-create-container').attr('for','closed');  
  //click on close btn
  jQuery('.crb-config-facility-type').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.facilitytype-create-container').hide();    
      jQuery('.facilitytype-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_facility_type-detail').click(function (e) {
      jQuery('.facilitytype-create-container').attr('for','open');
      jQuery('.facilitytype-create-container').attr('data','edit');
      jQuery('.facilitytype-create-container').show();         
      e.preventDefault();      
    });
    //click on close btn
  jQuery('.crb-config-facility-area-type').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.facilitytype-create-container').hide();    
      jQuery('.facilitytype-create-container').attr('for', 'closed');   
    });
  //click on edit btn
  jQuery('.edit-fm_facility_area_type-detail').click(function (e) {
      jQuery('.facilitytype-create-container').attr('for','open');
      jQuery('.facilitytype-create-container').attr('data','edit');
      jQuery('.facilitytype-create-container').show();         
      e.preventDefault();      
    });
  //click on add new
  jQuery('.new-facilitytype-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.facilitytype-create-container').attr('for');
    var dataAttr = jQuery('.facilitytype-create-container').attr('data');
    if(status == 'open' && jQuery('.facilitytype-create-container').attr('data') == 'edit') {
    jQuery('.facilitytype-create-container').removeAttr('data');    
    jQuery('.facilitytype-create-container').show();  
    jQuery('.facilitytype-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.facilitytype-create-container').attr('data') == 'edit') {   
        jQuery('.facilitytype-create-container').removeAttr('data');         
    jQuery('.facilitytype-create-container').show();      
    jQuery('.facilitytype-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.facilitytype-create-container').attr('for','open');
    jQuery('.facilitytype-create-container').show();  
    jQuery('.facilitytype-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.facilitytype-create-container').hide();
      jQuery('.facilitytype-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.facilitytype-create-container').attr('data') == 'edit') { 
      jQuery('.facilitytype-create-container .clear-data').val('');
      jQuery('.facilitytype-create-container').removeAttr('data');    
    jQuery('.facilitytype-create-container').show();    
    }
    else if(jQuery( ".facilitytype-create-container" ).attr('data') == 'edit') {    
      jQuery('.facilitytype-create-container').show();
    jQuery('.facilitytype-create-container').attr('for','open');
      }   
  });
  /////////////////////  facility type and facility area type  end ////////////////
  /////////////////////  fm facility  start ////////////////
  if(jQuery('select.fm-facility-sel').val() && jQuery('select.fm-facility-sel').val() != ''){
    jQuery('.locationfacility-create-container').show();
    jQuery('.locationfacility-create-container').attr('for','open');
  }
  else if(jQuery('select.fm-facility-sel').val() == '' && jQuery('.locationfacility-create-container').attr('for') == 'open'){
    jQuery('.locationfacility-create-container').show();
    jQuery('.locationfacility-create-container').attr('for','open');
  }
  else{
    jQuery('.locationfacility-create-container').hide();
    jQuery('.locationfacility-create-container').attr('for','closed');
  }
    //click on close btn
  jQuery('.crb-config-location-facility').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.locationfacility-create-container').hide();    
      jQuery('.locationfacility-create-container').attr('for', 'closed');
    jQuery('select.fm-facility-sel').val('').trigger('change');
    
        
    jQuery('input.config_location_facility_floornumber').val('');
    jQuery('input.config_location_facility_floornumber_addmore').trigger('mousedown');
    });
  //click on edit btn
  jQuery('.edit-fm_facility-detail').unbind('click').bind('click',function (e) {
    e.preventDefault();
    var getFacilityId = jQuery(this).attr('for');
    
    // console.log(getFacilityId);
    jQuery('select.fm-facility-sel').val(getFacilityId).trigger('change');
      jQuery('.locationfacility-create-container').attr('for','open');
      jQuery('.locationfacility-create-container').attr('data','edit');
      jQuery('.locationfacility-create-container').show(); 
        
            
    });
  //click on add new
  jQuery('.new-locationfacility-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.locationfacility-create-container').attr('for');
    var dataAttr = jQuery('.locationfacility-create-container').attr('data');
    if(status == 'open' && jQuery('.locationfacility-create-container').attr('data') == 'edit') {
    jQuery('.locationfacility-create-container').removeAttr('data');    
    jQuery('.locationfacility-create-container').show();  
    jQuery('.locationfacility-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.locationfacility-create-container').attr('data') == 'edit') {   
        jQuery('.locationfacility-create-container').removeAttr('data');         
    jQuery('.locationfacility-create-container').show();      
    jQuery('.locationfacility-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.locationfacility-create-container').attr('for','open');
    jQuery('.locationfacility-create-container').show();  
    jQuery('.locationfacility-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.locationfacility-create-container').hide();
      jQuery('.locationfacility-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.locationfacility-create-container').attr('data') == 'edit') { 
      jQuery('.locationfacility-create-container .clear-data').val('');
      jQuery('.locationfacility-create-container').removeAttr('data');    
    jQuery('.locationfacility-create-container').show();    
    }
    else if(jQuery( ".locationfacility-create-container" ).attr('data') == 'edit') {    
      jQuery('.locationfacility-create-container').show();
    jQuery('.locationfacility-create-container').attr('for','open');
      }   
  });
  /////////////////////  fm facility  end ////////////////
  /////////////////////  location zone  start ////////////////
  if(jQuery('select.locaton-zone-sel').val() && jQuery('select.locaton-zone-sel').val() != ''){
    jQuery('.locationlocation-create-container').show();
    jQuery('.locationlocation-create-container').attr('for','open');
  }
  else if(jQuery('select.locaton-zone-sel').val() == '' && jQuery('.locationlocation-create-container').attr('for') == 'open'){
    jQuery('.locationlocation-create-container').show();
    jQuery('.locationlocation-create-container').attr('for','open');
  }
  else{
    jQuery('.locationlocation-create-container').hide();
    jQuery('.locationlocation-create-container').attr('for','closed');
  }
    //click on close btn
  jQuery('.crb-location-location').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.locationlocation-create-container').hide();    
      jQuery('.locationlocation-create-container').attr('for', 'closed');
    jQuery('select.locaton-zone-sel').val('').trigger('change');
    
        
    jQuery('select.config_location_location_floornumber_select').val('');
    jQuery('input.config_location_location_floornumber_addmore').trigger('mousedown');
    });
  //click on edit btn
  jQuery('.edit-fm_location_location-detail').unbind('click').bind('click',function (e) {
    e.preventDefault();
    var getZoneId = jQuery(this).attr('for');
    
    // console.log(getZoneId);
    jQuery('select.locaton-zone-sel').val(getZoneId).trigger('change');
      jQuery('.locationlocation-create-container').attr('for','open');
      jQuery('.locationlocation-create-container').attr('data','edit');
      jQuery('.locationlocation-create-container').show(); 
        
            
    });
  //click on add new
  jQuery('.new-locationlocation-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.locationlocation-create-container').attr('for');
    var dataAttr = jQuery('.locationlocation-create-container').attr('data');
    if(status == 'open' && jQuery('.locationlocation-create-container').attr('data') == 'edit') {
    jQuery('.locationlocation-create-container').removeAttr('data');    
    jQuery('.locationlocation-create-container').show();  
    jQuery('.locationlocation-create-container .clear-data').val('');   
    }
    else if(status == 'closed' && jQuery('.locationlocation-create-container').attr('data') == 'edit') {   
        jQuery('.locationlocation-create-container').removeAttr('data');         
    jQuery('.locationlocation-create-container').show();      
    jQuery('.locationlocation-create-container .clear-data').val('');   
    }
    else if(status == 'closed') {
    jQuery('.locationlocation-create-container').attr('for','open');
    jQuery('.locationlocation-create-container').show();  
    jQuery('.locationlocation-create-container .clear-data').val('');     
    }
    else if(status == 'open') {
    jQuery('.locationlocation-create-container').hide();
      jQuery('.locationlocation-create-container').attr('for','closed');    
    }
    else if(status == 'open' && jQuery('.locationlocation-create-container').attr('data') == 'edit') { 
      jQuery('.locationlocation-create-container .clear-data').val('');
      jQuery('.locationlocation-create-container').removeAttr('data');    
    jQuery('.locationlocation-create-container').show();    
    }
    else if(jQuery( ".locationlocation-create-container" ).attr('data') == 'edit') {    
      jQuery('.locationlocation-create-container').show();
    jQuery('.locationlocation-create-container').attr('for','open');
      }   
  });
  /////////////////////  location zone  end ////////////////
  /////////////////////  asset start ////////////////
  if(jQuery('input.asset-node-nid').val()){
    jQuery('.asset-create-container').show();
    jQuery('.asset-create-container').attr('for','open');
  }
  else{
    jQuery('.asset-create-container').hide();
    jQuery('.asset-create-container').attr('for','closed');
  }
  //click on close btn
  jQuery('.crb-asset').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.asset-create-container').hide();    
      jQuery('.asset-create-container').attr('for', 'closed');    
    });
  //click on edit btn
  jQuery('.edit-fm_asset-detail').click(function (e) {
      jQuery('.asset-create-container').attr('for','open');
      jQuery('.asset-create-container').attr('data','edit');
      jQuery('.asset-create-container').show();         
      //e.preventDefault();      
    }); 
  //click on add new
  jQuery('.new-asset-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.asset-create-container').attr('for');
    var dataAttr = jQuery('.asset-create-container').attr('data');
    if(status == 'open' && jQuery('.asset-create-container').attr('data') == 'edit') {
    jQuery('.asset-create-container').removeAttr('data');   
    jQuery('.asset-create-container').show(); 
    jQuery('.asset-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.asset-create-container').attr('data') == 'edit') {   
        jQuery('.asset-create-container').removeAttr('data');         
    jQuery('.asset-create-container').show();     
    jQuery('.asset-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.asset-create-container').attr('for','open');
    jQuery('.asset-create-container').show(); 
    jQuery('.asset-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.asset-create-container').hide();
      jQuery('.asset-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.asset-create-container').attr('data') == 'edit') { 
      jQuery('.asset-create-container .clear-data').val('');
      jQuery('.asset-create-container').removeAttr('data');     
    jQuery('.asset-create-container').show();   
    }
    else if(jQuery( ".asset-create-container" ).attr('data') == 'edit') {   
      jQuery('.asset-create-container').show();
    jQuery('.asset-create-container').attr('for','open');
      }   
  });
  /////////////////////  asset end ////////////////
  /////////////////////  work order start ////////////////
  //jQuery('.workorder-create-container').hide();
  //jQuery('.workorder-create-container').attr('for','closed');
  
  
  if(jQuery('select.workorder-sel').val() && jQuery('select.workorder-sel').val() != ''){
    jQuery('.workorder-create-container').show();
    jQuery('.workorder-create-container').attr('for','open');
  }
  else if(jQuery('select.workorder-sel').val() == '' && jQuery('.workorder-create-container').attr('for') == 'open'){
    jQuery('.workorder-create-container').show();
    jQuery('.workorder-create-container').attr('for','open');
  }
  else{
    jQuery('.workorder-create-container').hide();
    jQuery('.workorder-create-container').attr('for','closed');
  }
  
  
  
  
  //click on close btn
  jQuery('.crb-workorder').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.workorder-create-container').hide();    
      jQuery('.workorder-create-container').attr('for', 'closed');    
    jQuery('.workorder-create-container .clear-data-close').val('');  
    });
  //click on edit btn
  /*jQuery('.edit-fm_work_order-detail').click(function (e) {
      jQuery('.workorder-create-container').attr('for','open');
      jQuery('.workorder-create-container').attr('data','edit');
      jQuery('.workorder-create-container').show();         
      e.preventDefault();      
    }); */
  
  
  jQuery('.edit-fm_work_order-detail').unbind('click').bind('click',function (e) {
    e.preventDefault();
    var getWorkOrderId = jQuery(this).attr('for');
    
    // console.log(getWorkOrderId);
    jQuery('select.workorder-sel').val(getWorkOrderId).trigger('change');
      jQuery('.workorder-create-container').attr('for','open');
      jQuery('.workorder-create-container').attr('data','edit');
      jQuery('.workorder-create-container').show(); 
            
    });
  
  //click on add new
  jQuery('.new-workorder-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.workorder-create-container').attr('for');
    var dataAttr = jQuery('.workorder-create-container').attr('data');
    if(status == 'open' && jQuery('.workorder-create-container').attr('data') == 'edit') {
    jQuery('.workorder-create-container').removeAttr('data');   
    jQuery('.workorder-create-container').show(); 
    jQuery('.workorder-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.workorder-create-container').attr('data') == 'edit') {   
        jQuery('.workorder-create-container').removeAttr('data');         
    jQuery('.workorder-create-container').show();     
    jQuery('.workorder-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.workorder-create-container').attr('for','open');
    jQuery('.workorder-create-container').show(); 
    jQuery('.workorder-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.workorder-create-container').hide();
      jQuery('.workorder-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.workorder-create-container').attr('data') == 'edit') { 
      jQuery('.workorder-create-container .clear-data').val('');
      jQuery('.workorder-create-container').removeAttr('data');     
    jQuery('.workorder-create-container').show();   
    }
    else if(jQuery( ".workorder-create-container" ).attr('data') == 'edit') {   
      jQuery('.workorder-create-container').show();
    jQuery('.workorder-create-container').attr('for','open');
      }   
  });
  /////////////////////  work order  end ////////////////
  /////////////////////  preferred vender start ////////////////
  if(jQuery('select.preferred-vendor-sel').val() && jQuery('select.preferred-vendor-sel').val() != ''){
    jQuery('.preferredvendor-create-container').show();
    jQuery('#pv-container-section').show();
    jQuery('.preferredvendor-create-container').attr('for','open');
  }
  else if(jQuery('select.preferred-vendor-sel').val() == '' && jQuery('.preferredvendor-create-container').attr('for') == 'open'){
    jQuery('.preferredvendor-create-container').show();
    jQuery('#pv-container-section').show();
    jQuery('.preferredvendor-create-container').attr('for','open');
  }
  else{
    jQuery('.preferredvendor-create-container').hide();
    jQuery('#pv-container-section').hide();
    jQuery('.preferredvendor-create-container').attr('for','closed');
  }
    
  //click on close btn
  jQuery('.crb-config-preferred-vendor').unbind('click').bind('click',function (e) {
    Drupal.attachBehaviors(jQuery('body'));
      jQuery('.preferredvendor-create-container').hide(); 
    jQuery('#pv-container-section').hide();   
      jQuery('.preferredvendor-create-container').attr('for', 'closed');    
    jQuery('.preferredvendor-create-container .clear-data-close').val('');  
    }); 
  jQuery('.edit-fm_preferred_vendor-detail').unbind('click').bind('click',function (e) {
    e.preventDefault();
    var getPreferredVendorId = jQuery(this).attr('for');
    
    // console.log(getPreferredVendorId);
    jQuery('select.preferred-vendor-sel').val(getPreferredVendorId).trigger('change');
      jQuery('.preferredvendor-create-container').attr('for','open');
      jQuery('.preferredvendor-create-container').attr('data','edit');
      jQuery('.preferredvendor-create-container').show(); 
    jQuery('#pv-container-section').show();
        
            
    });
  
  //click on add new
  jQuery('.new-preferredvendor-link').unbind('click').bind('click',function (e) {
    //Drupal.attachBehaviors(jQuery('body'));
    e.preventDefault();
    var status = jQuery('.preferredvendor-create-container').attr('for');
    var dataAttr = jQuery('.preferredvendor-create-container').attr('data');
    if(status == 'open' && jQuery('.preferredvendor-create-container').attr('data') == 'edit') {
    jQuery('.preferredvendor-create-container').removeAttr('data');   
    jQuery('.preferredvendor-create-container').show(); 
    jQuery('#pv-container-section').show();
    jQuery('.preferredvendor-create-container .clear-data').val('');    
    }
    else if(status == 'closed' && jQuery('.preferredvendor-create-container').attr('data') == 'edit') {   
        jQuery('.preferredvendor-create-container').removeAttr('data');         
    jQuery('.preferredvendor-create-container').show(); 
    jQuery('#pv-container-section').show();   
    jQuery('.preferredvendor-create-container .clear-data').val('');    
    }
    else if(status == 'closed') {
    jQuery('.preferredvendor-create-container').attr('for','open');
    jQuery('.preferredvendor-create-container').show(); 
    jQuery('#pv-container-section').show();
    jQuery('.preferredvendor-create-container .clear-data').val('');      
    }
    else if(status == 'open') {
    jQuery('.preferredvendor-create-container').hide();
    jQuery('#pv-container-section').hide();
      jQuery('.preferredvendor-create-container').attr('for','closed');   
    }
    else if(status == 'open' && jQuery('.preferredvendor-create-container').attr('data') == 'edit') { 
      jQuery('.preferredvendor-create-container .clear-data').val('');
      jQuery('.preferredvendor-create-container').removeAttr('data');     
    jQuery('.preferredvendor-create-container').show(); 
    jQuery('#pv-container-section').show(); 
    }
    else if(jQuery( ".preferredvendor-create-container" ).attr('data') == 'edit') {   
      jQuery('.preferredvendor-create-container').show();
    jQuery('#pv-container-section').show();
    jQuery('.preferredvendor-create-container').attr('for','open');
      }   
  });
  /////////////////////  preferred vendar  end ////////////////
  //****************************************** add new btn and close and edit ***** end  ******************************************///

  if(getPath == '/hcfm/dashboard4') {    
    //dashboard tile structure save start
    window.onbeforeunload = function(e) {
      e = e || window.event;    
      // For IE and Firefox prior to version 4
      if (e) {
        //e.returnValue = 'Any string';
        var TileData =[];
        jQuery('.tile-item').each(function(index, element) {
          var TData = '';
          var TiId = jQuery(this).attr('id');
          var TiStatus = jQuery(this).attr('tile-status');
          var TiOpenStatus = jQuery(this).attr('open-status');
          TData = {'index':index,'id':TiId,'tilestatus':TiStatus,'tileopenstatus':TiOpenStatus};
          TileData.push(TData);   
        });
        var myJsonString = JSON.stringify(TileData);
        localStorage.setItem('hcfm_dash_save', myJsonString);
        jQuery.post( '/hcfm-tile-configure/save/'+myJsonString);
      }    
      // For Safari
      //return 'Any string';
    };
    //dashboard tile structure save end 

    /***************** available labor chart  synchronized tile   start***************************/
    /*  jQuery('.available-labor-column-data-display').bind('mousemove touchmove touchstart', function (e) {
          var chart,
              point,
              i,
              event;

          for (i = 0; i < Highcharts.charts.length; i = i + 1) {
              chart = Highcharts.charts[i];
              event = chart.pointer.normalize(e.originalEvent); // Find coordinates within the chart
              if(chart.series[0]){
                point = chart.series[0].searchPoint(event, true); // Get the hovered point
              }
              if (point) {
                  point.highlight(e);
              }
          }
      });

      Highcharts.Pointer.prototype.reset = function () {
          return undefined;
      };


      Highcharts.Point.prototype.highlight = function (event) {
          this.onMouseOver(); // Show the hover marker
          this.series.chart.tooltip.refresh(this); // Show the tooltip
          this.series.chart.xAxis[0].drawCrosshair(event, this); // Show the crosshair
      };




      function syncExtremes(e) {
          var thisChart = this.chart;

          if (e.trigger !== 'syncExtremes') { // Prevent feedback loop
              Highcharts.each(Highcharts.charts, function (chart) {
                  if (chart !== thisChart) {
                      if (chart.xAxis[0].setExtremes) { // It is null while updating
                          chart.xAxis[0].setExtremes(e.min, e.max, undefined, false, { trigger: 'syncExtremes' });
                      }
                  }
              });
          }
      }*/

    /********************* available labor chart  synchronized tile   end ***********************/
  }
 
  
  
  
  
  
  
  //if(getPath == '/hcfm/dashboard4') {
  /* jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    var urlajax = ajaxOptions.url;
    var DasAssetSeries = Drupal.settings.m6connect_hcfm.graphData.NewGpDataArrayA;
    var DasAssetSeriesData = '';
  
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="hcfm_dashboard_asset"){ 
      if(DasAssetSeries && DasAssetSeries.asset){
      var DasAssetSeriesData = DasAssetSeries.asset;
      //console.log(DasAssetSeries.asset);
      Highcharts.chart('asset-column-data-display', {
        chart: {
          type: 'column'
        },
        credits: {
          enabled: false
        },
        title: {
          text: 'Asset by Risk'
        },
        xAxis: {
          categories: ['J']
        },
        yAxis: {
          min: 0,
          title: {
            text: 'Asset'
          }
        },
        tooltip: {
          pointFormat: '<span style="color:{series.color}">{series.name}</span>: <b>{point.y}</b> ({point.percentage:.2f}%)<br/>',
          shared: true
        },
        plotOptions: {
          column: {
            stacking: 'percent'
          }
        },
        series: DasAssetSeriesData
      });
      }
    }
    if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="hcfm_dashboard_back_open_pm"){
      if(DasAssetSeries && DasAssetSeries.work_orders_open_pm){
      var DasAssetSeriesData = DasAssetSeries.work_orders_open_pm;
      //console.log(DasAssetSeries.work_orders_open_pm);
      Highcharts.chart('work_orders_open_pm-column-data-display', {
        chart: {
          type: 'pie',
          options3d: {
            enabled: true,
            alpha: 45,
            beta: 0
          }
        },
        credits: {
          enabled: false
        },
        title: {
          text: 'OPEN PMs'
        },
        tooltip: {
          pointFormat: '{series.name}: <b>{point.percentage:.2f}%</b>'
        },
        plotOptions: {
          pie: {
            allowPointSelect: true,
            cursor: 'pointer',
            depth: 35,
            dataLabels: {
              enabled: true,
              format: '{point.name}'
            }
          }
        },
        series: DasAssetSeriesData
      });
      }
    }
  });
  */
  //}
  //dashboard selectall field start
   var getMultiRegionIdText = 'region';
  var getMultiSiteIdText = 'site';
  var getMultiFacilityIdText = 'facility';
  var getMultiZoneIdText = 'zone';
  var getMultiStatusIdText = 'status';
  var getMultiRiskrankIdText = 'riskrank';
  var geMultitFilterIdText = 'filter';
 ////normal sec
  jQuery( ".hcfmdash-"+getMultiRegionIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    //console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list').removeClass('allSelected');
      //jQuery('.hcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .hcfmdash-'+getMultiRegionIdText+'-list').select2();
    }
  });

  jQuery( ".hcfmdash-"+getMultiSiteIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    //console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list').removeClass('allSelected');
      //jQuery('.hcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .hcfmdash-'+getMultiSiteIdText+'-list').select2();
    }
  });

  jQuery( ".hcfmdash-"+getMultiFacilityIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    //console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list').removeClass('allSelected');
      //jQuery('.hcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .hcfmdash-'+getMultiFacilityIdText+'-list').select2();
    }
  });

  ///compare a
  jQuery( ".ahcfmdash-"+getMultiRegionIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    //console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list').removeClass('allSelected');
      //jQuery('.ahcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiRegionIdText+'-list').select2();
    }
  });

  jQuery( ".ahcfmdash-"+getMultiSiteIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    ////console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list').removeClass('allSelected');
      //jQuery('.ahcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiSiteIdText+'-list').select2();
    }
  });

  jQuery( ".ahcfmdash-"+getMultiFacilityIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    ////console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list').removeClass('allSelected');
      //jQuery('.ahcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .ahcfmdash-'+getMultiFacilityIdText+'-list').select2();
    }
  });

  ///compare b
  jQuery( ".bhcfmdash-"+getMultiRegionIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    ////console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list').removeClass('allSelected');
      //jQuery('.bhcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiRegionIdText+'-list').select2();
    }
  });

  jQuery( ".bhcfmdash-"+getMultiSiteIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    //console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list').removeClass('allSelected');
      //jQuery('.bhcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiSiteIdText+'-list').select2();
    }
  });

  jQuery( ".bhcfmdash-"+getMultiFacilityIdText+"-list" ).change(function() {
    var optionsVals = jQuery(this).val();  
    //console.log(optionsVals);
    var masterId = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
    jQuery( optionsVals ).each(function(index,elements) {
      if(elements && elements =='all'){
        jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list').addClass('allSelected');                        
      }
    });
    if(jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list').hasClass('allSelected')) {
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list > option').prop("selected","selected");
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list option[value="all"]').prop("selected", false);
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list').removeClass('allSelected');
      //jQuery('.bhcfmdash-region-list').trigger( "change" ); 
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list').select2('destroy');
      jQuery('#'+masterId+' .bhcfmdash-'+getMultiFacilityIdText+'-list').select2();
    }
  });
  //dashboard selectall field end
  //dashboard click on setting button start
  jQuery('.tile-expand-mlsetting-btn').unbind('click').bind('click',function (e) {
    var mastersec = jQuery(this).parent().parent().parent().attr('id')
    //console.log(mastersec);
    var mlstatus = jQuery(this).attr('tile-show');
    //jQuery('.tile-flipcontrol  .setting-btn').click();
    var mlclass = jQuery('#'+mastersec +' .tile-flipcontrol  a').attr('class');
   // console.log(mlstatus);
    //console.log(mlclass);
    var res = mlclass.split("-btn");
   // console.log(res);
    var newun = Number(res[1]) + Number(1);
    if(mlstatus && mlstatus =='front'){
      jQuery(this).attr('tile-show','back');
      jQuery('#'+mastersec +' a.'+mlclass).click();
      // console.log('#'+mastersec +' a.'+mlclass);
    }else if(mlstatus && mlstatus =='back'){
      jQuery(this).attr('tile-show','front');
      //unflip-btn022
      if(mastersec == 'assets'){
        jQuery('#'+mastersec +' a.unflip-btn0'+newun).click();
      }else{
        jQuery('#'+mastersec +' a.unflip-btn'+newun).click();
      }
      //console.log('#'+mastersec +' a.unflip-btn'+newun);
    }
    
  });
  //dashboard click on setting button end
  //dashboard graph form  after submit setting close start
  
    jQuery(".form-submit", context).click(function (e) {      
      var getTrivalue = jQuery(this).val();
      if(getTrivalue && getTrivalue =='Compare'){
        var hasoncompare = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('class');        
        if(hasoncompare && hasoncompare.indexOf('desh-sec-c')){
          var masterid = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');          
          jQuery('#'+ masterid+' .tile-expand-compareback-btn').trigger('click');
        }
      }
      if(getTrivalue && getTrivalue =='Submit'){
        var hasonmediumlarge = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('class'); 
        if(hasonmediumlarge && hasonmediumlarge.indexOf('desh-sec-b')){
          var masterid = jQuery(this).parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().parent().attr('id');
          jQuery('#'+ masterid+' .tile-expand-mlsetting-btn').trigger('click');   
        }
      }
    });
  //dashboard graph form  after submit setting close end
  } //attach end
}

