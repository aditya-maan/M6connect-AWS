jQuery(document).ready(function (e) {
  var getPath = window.location.pathname; 
  jQuery('.listing-row-delete').click(function (e) {
  var hiderow = jQuery(this).parent().parent().parent().parent().parent().parent();  
    hiderow.hide(); 
  });
  /*jQuery('.new-asset-link').click(function (e) {
    jQuery('.asset-create-container').toggle(); 
  });*/
  
  /*var getUpdatedTilePos = function getUpdatedTilePos() {
  var position = [];
  jQuery('.tile-item').each(function(e){
  var ap = jQuery(this).attr('updated-pos');
  if(ap != ''){
    position.push(ap);
  }
  }); 
  return position;
};




var getUpdatedTilePosTrue = function getUpdatedTilePosTrue(pos) {
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
};*/


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
       jQuery.each(data,function(key, value) {
       //console.log(key+','+value);  
       jQuery('.wo-facility').empty();  
       jQuery(".wo-facility").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-facility');
       });
      });
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
    
   /* jQuery.post( '/get-facility-list-data/'+getFacilityId, function( data ) {
     if(data != 0) {
            
       if(data && data['field_facility_building_value']){        
       //jQuery('.wo-building').val(data['field_facility_building_value']);
       WoBuilding.push(data['field_facility_building_value']);
       }
       else{
       jQuery('.wo-building').val('');
       
       }
       if(data && data['field_facility_floor_value']){        
        //jQuery('.wo-floor').val(data['field_facility_floor_value']);
        WoFloor.push(data['field_facility_floor_value']);
       }
       else{
       jQuery('.wo-floor').val('');
       
       }       
       if(data && data['field_facility_address1_value']){       
        //jQuery('.fac-region-address1').val(data['field_facility_address1_value']);
        FullFacAddress.push(data['field_facility_address1_value']);
       }
       else{
       jQuery('.fac-region-address1').val('');
       
       }
       if(data && data['field_facility_address2_value']){       
        //jQuery('.fac-region-address2').val(data['field_facility_address2_value']);
        FullFacAddress.push(data['field_facility_address2_value']);
       }
       else{
       jQuery('.fac-region-address2').val('');
       
       }
       if(data && data['field_facility_city_value']){       
        //jQuery('.fac-region-city').val(data['field_facility_city_value']);
        FullFacAddress.push(data['field_facility_city_value']);
       }
       else{
       jQuery('.fac-region-city').val('');
       
       }
       if(data && data['field_facility_state_value_value']){        
        //jQuery('.fac-region-state').val(data['field_facility_state_value_value']);
       FullFacAddress.push(data['field_facility_state_value_value']);
       }
       else{
       jQuery('.fac-region-state').val('');
       
       }
       if(data && data['field_facility_zipcode_value']){        
        //jQuery('.fac-region-zipcode').val(data['field_facility_zipcode_value']);
        FullFacAddress.push(data['field_facility_zipcode_value']);
       }
       else{
       jQuery('.fac-region-zipcode').val('');
      
       }
       if(data && data['field_facility_country_value_value']){        
        //jQuery('.fac-region-country').val(data['field_facility_country_value_value']);
        FullFacAddress.push(data['field_facility_country_value_value']);
       }
       else{
       jQuery('.fac-region-country').val('');
       
       }       
     }
     else{
         
       jQuery('.wo-building').val('');
       jQuery('.wo-floor').val('');
       jQuery('.fac-region-country').val('');
       jQuery('.fac-region-address1').val('');
       jQuery('.fac-region-address2').val('');
       jQuery('.fac-region-city').val('');
       jQuery('.fac-region-state').val('');
       jQuery('.fac-region-zipcode').val('');
       jQuery('.wo-full-address').val('');
     }     
    })*/
     jQuery.post( '/get-asset-list-facilityid/'+getFacilityId, function( data ) {
     if(data != 0) {
       jQuery.each(data,function(key, value) {
       //console.log(key+','+value);  
       jQuery('.hcfm-asset').empty(); 
       jQuery(".hcfm-asset").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.hcfm-asset');
       });
      });
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
       jQuery.each(data,function(key, value) {
       //console.log(key+','+value);  
       jQuery('.wo-floor').empty(); 
       jQuery(".wo-floor").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.wo-floor');
       });
      });
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
    jQuery.post( '/get-state-list-countrycode-program/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.fa-region-state').empty();  
       jQuery(".fa-region-state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.fa-region-state');
       });
      });
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
  
  //asset change region
  jQuery('select.as-asset-region').change(function(e){   
  var getRegionId = jQuery(this).val(); 
  //console.log(getRegionId); 
  if(getRegionId) {   
    jQuery.post( '/get-locationdata/region/'+getRegionId, function( data ) {
      //console.log(data);
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
       //console.log(key+','+value);      
       jQuery('.as-asset-site').empty();  
       jQuery(".as-asset-site").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.as-asset-site');
       });
      });
     }
     else{
      jQuery('.as-asset-site').empty(); 
      jQuery(".as-asset-site").prepend("<option value=''>- None -</option>").val(''); 
    }    
    })
  }else{
    jQuery('.as-asset-site').empty(); 
    jQuery(".as-asset-site").prepend("<option value=''>- None -</option>").val(''); 
  } 
  });
  //asset change site
  jQuery('select.as-asset-site').change(function(e){   
  var getSiteId = jQuery(this).val(); 
  //console.log(getSiteId); 
  if(getSiteId) {   
    jQuery.post( '/get-locationdata/site/'+getSiteId, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {        
       jQuery('.as-asset-facility').empty();  
       jQuery(".as-asset-facility").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.as-asset-facility');
       });
      });
     }
     else{
      jQuery('.as-asset-facility').empty(); 
      jQuery(".as-asset-facility").prepend("<option value=''>- None -</option>").val(''); 
    }  
    })
  }else{
    jQuery('.as-asset-facility').empty(); 
    jQuery(".as-asset-facility").prepend("<option value=''>- None -</option>").val(''); 
  } 
  });
  //asset change facility
  jQuery('select.as-asset-facility').change(function(e){   
  var getFacilityId = jQuery(this).val(); 
  //console.log(getFacilityId); 
  if(getFacilityId) {   
    jQuery.post( '/get-locationdata/facility/'+getFacilityId, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {        
       jQuery('.as-asset-location').empty();  
       jQuery(".as-asset-location").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.as-asset-location');
       });
      });
     }  
     else{
      jQuery('.as-asset-location').empty(); 
      jQuery(".as-asset-location").prepend("<option value=''>- None -</option>").val(''); 
    }  
    })
  }else{
    jQuery('.as-asset-location').empty(); 
    jQuery(".as-asset-location").prepend("<option value=''>- None -</option>").val(''); 
  }
  });
  //system change sub system
  /*jQuery('select.as-asset-system').change(function(e){   
  var getSystemId = jQuery(this).val(); 
  //console.log(getFacilityId); 
  if(getSystemId) {   
    jQuery.post( '/get-asset-subsystem/'+getSystemId, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {        
       jQuery('.as-asset-sub-system').empty();  
       jQuery(".as-asset-sub-system").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.as-asset-sub-system');
       });
      });
     }  
     else{
      jQuery('.as-asset-sub-system').empty(); 
      jQuery(".as-asset-sub-system").prepend("<option value=''>- Select -</option>").val(''); 
    }  
    })
  }else{
    jQuery('.as-asset-sub-system').empty(); 
    jQuery(".as-asset-sub-system").prepend("<option value=''>- Select -</option>").val(''); 
  }
  });*/
  //work order accet change 
  jQuery('select.wo-asset-number').change(function(e){   
  var getAssetId = jQuery(this).val();  
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
      /*if(data && data['field_asset_region_target_id']){      
        jQuery('.wo-region').val(data['field_asset_region_target_id']);
      }
      else{
       jQuery('.wo-region').val('');       
      } 
      if(data && data['field_asset_site_target_id']){      
        jQuery('.wo-site').val(data['field_asset_site_target_id']);
      }
      else{
        jQuery('.wo-site').val('');      
      } 
      if(data && data['field_asset_facility_target_id']){      
        jQuery('.wo-facility').val(data['field_asset_facility_target_id']);
      }
      else{
        jQuery('.wo-facility').val('');      
      }
      if(data && data['field_asset_location_target_id']){      
        jQuery('.wo-location').val(data['field_asset_location_target_id']);
      }
      else{
        jQuery('.wo-location').val('');      
      }    */ 
      }  
    })
  }else{
    jQuery('.wo-manufacturer').val('');
    jQuery('.wo-model-number').val('');
    jQuery('.wo-serial-number').val('');
    jQuery('.wo-account-number').val('');
    jQuery('.wo-priority-rr').val('');
  /*  jQuery('.wo-region').val('');
    jQuery('.wo-site').val('');
    jQuery('.wo-facility').val('');
    jQuery('.wo-location').val(''); */
  }
  });
  
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
    jQuery.post( '/get-state-list-countrycode-program/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_region_state').empty(); 
       jQuery(".config_location_region_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_location_region_state');
       });
      });
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
      if (urlajax.indexOf("/get-state-list-countrycode-program") === 0){
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
  jQuery('select.config_location_pick_region').change(function(e){
    var getLocRegionPick = jQuery(this).val();
  if(getLocRegionPick) { 
    jQuery.post( '/get-locationdata-country-prog/region/'+getLocRegionPick, function( data ) {
    // console.log(data);
    if(data != 0 && data) {
      jQuery('select.config_location_site_country').val(data);
      jQuery.post( '/get-state-list-countrycode-program/'+data, function( data2 ) {
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
    jQuery.post( '/get-state-list-countrycode-program/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_site_state').empty(); 
       jQuery(".config_location_site_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
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
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode-program") === 0){
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
  jQuery('select.config_location_pick_site').change(function(e){
    var getLocSitePick = jQuery(this).val();
  if(getLocSitePick) { 
    jQuery.post( '/get-locationdata-country-prog/site/'+getLocSitePick, function( data ) {
    console.log(data);
    if(data != 0 && data) {
      jQuery('select.config_location_facility_country').val(data);
      jQuery.post( '/get-state-list-countrycode-program/'+data, function( data2 ) {
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
    jQuery.post( '/get-state-list-countrycode-program/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_facility_state').empty(); 
       jQuery(".config_location_facility_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
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
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode-program") === 0){
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
  jQuery('select.config_location_pick_facility').change(function(e){
    var getLocFacilityPick = jQuery(this).val();
  if(getLocFacilityPick) { 
    jQuery.post( '/get-locationdata-country-prog/facility/'+getLocFacilityPick, function( data ) {
    // console.log(data);
    if(data != 0 && data) {
      jQuery('select.config_location_location_country').val(data);
      jQuery.post( '/get-state-list-countrycode-program/'+data, function( data2 ) {
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
    jQuery.post( '/get-state-list-countrycode-program/'+getCountryCode, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_location_location_state').empty(); 
       jQuery(".config_location_location_state").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
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
    jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      //console.log(urlajax);
      //console.log(ajaxOptions); 
      if (urlajax.indexOf("/get-state-list-countrycode-program") === 0){
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
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_city').empty();  
       jQuery(".config_preferred_vendors_city").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_city');
       });
      });
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
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_company').empty(); 
       jQuery(".config_preferred_vendors_company").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_company');
       });
      });
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
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_company').empty(); 
       jQuery(".config_preferred_vendors_company").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_company');
       });
      });
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
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_company').empty(); 
       jQuery(".config_preferred_vendors_company").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_company');
       });
      });
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
  
  //preferred vender set user option by company
 /* var getPreferredVendorCompany = jQuery('select.config_preferred_vendors_company').val();
  if(!getPreferredVendorCompany){
  jQuery('.config_preferred_vendors_user').empty(); 
  jQuery(".config_preferred_vendors_user").prepend("<option value=''>- none -</option>").val('');
  }
  
  jQuery('select.config_preferred_vendors_company').change(function(e){   
  var getPvCompanyCode = jQuery(this).val();  
  //console.log(getCountryCode);  
  if(getPvCompanyCode) {    
    jQuery.post( '/get-company-user-comnid/'+getPvCompanyCode, function( data ) {
     if(data != 0 && data) {
       jQuery.each(data,function(key, value) {
      // console.log(key+','+value);  
       jQuery('.config_preferred_vendors_user').empty();  
       jQuery(".config_preferred_vendors_user").prepend("<option value=''>- Select -</option>").val('');
       jQuery.each(data,function(key, value) {
         var opt = jQuery('<option>');
         opt.val(key).text(value);
         opt.appendTo('.config_preferred_vendors_user');
       });
      });
     }
     else{
       jQuery('.config_preferred_vendors_user').empty(); 
         jQuery(".config_preferred_vendors_user").prepend("<option value=''>- none -</option>").val('');
     }   
    })
    
  }else{
    jQuery('.config_preferred_vendors_user').empty(); 
    jQuery(".config_preferred_vendors_user").prepend("<option value=''>- none -</option>").val('');
  } 
  });*/
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
       jQuery.each(data,function(key, value) {
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
      });
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
       jQuery.each(data,function(key, value) {
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
      });
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
       jQuery.each(data,function(key, value) {
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
      });
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
       jQuery.each(data,function(key, value) {
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
      });
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
  /*
  jQuery('select.dashboard_view_by_type_filter').change(function () {
    var DViewBTypeFilterV = jQuery(this).val();
    if(DViewBTypeFilterV == 'assets_by_riskrank'){
    jQuery('.hcfm-dashboard-asset-container-section').show();
    }
    else{
    jQuery('.hcfm-dashboard-asset-container-section').hide();  
    }
    
  });
  
      
  */}
  
  //region change blank >> 
/*  var DasRegion = jQuery('select.dashboard-region').val();
  console.log(DasRegion);
  if(!DasRegion){
  jQuery('.dashboard-site').empty(); 
  jQuery(".dashboard-site").prepend("<option value=''>- none -</option>").val('');
  jQuery('.dashboard-facility').empty(); 
  jQuery(".dashboard-facility").prepend("<option value=''>- none -</option>").val('');
  jQuery('.dashboard-location').empty(); 
  jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');    
  }
  jQuery(document).on('change', '.dashboard-region', function(e) {
    var DasRegionNid = jQuery(this).val();
  console.log(DasRegionNid);
  if(DasRegionNid){
    jQuery('.dashboard-facility').empty(); 
    jQuery(".dashboard-facility").prepend("<option value=''>- none -</option>").val('');
    jQuery('.dashboard-location').empty(); 
    jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');
  }
  else{
      jQuery('.dashboard-site').empty(); 
    jQuery(".dashboard-site").prepend("<option value=''>- none -</option>").val('');
    jQuery('.dashboard-facility').empty(); 
    jQuery(".dashboard-facility").prepend("<option value=''>- none -</option>").val('');
    jQuery('.dashboard-location').empty(); 
    jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');  
  } 
  });
  //site change blank >> 
  var DasSite = jQuery('select.dashboard-site').val();
  console.log(DasSite);
  if(!DasSite){ 
  jQuery('.dashboard-facility').empty(); 
  jQuery(".dashboard-facility").prepend("<option value=''>- none -</option>").val('');
  jQuery('.dashboard-location').empty(); 
  jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');    
  }
  jQuery(document).on('change', '.dashboard-site', function(e) {
    var DasSiteNid = jQuery(this).val();
  console.log(DasSiteNid);
  if(DasSiteNid){   
    jQuery('.dashboard-location').empty(); 
    jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');
  }
  else{      
    jQuery('.dashboard-facility').empty(); 
    jQuery(".dashboard-facility").prepend("<option value=''>- none -</option>").val('');
    jQuery('.dashboard-location').empty(); 
    jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');  
  } 
  });
  //facility change blank >> 
  var DasFacility = jQuery('select.dashboard-facility').val();
  console.log(DasFacility);
  if(!DasFacility){   
  jQuery('.dashboard-location').empty(); 
  jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');    
  }
  jQuery(document).on('change', '.dashboard-facility', function(e) {
    var DasFacilityNid = jQuery(this).val();
  console.log(DasFacilityNid);
  if(!DasFacilityNid){    
    jQuery('.dashboard-location').empty(); 
    jQuery(".dashboard-location").prepend("<option value=''>- none -</option>").val('');  
  } 
  });*/
  
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
  if(getPath == '/hcfm/dashboard2' || getPath == '/hcfm/dashboard3') {
  jQuery("#card-1").flip({
    trigger: 'manual'
  });  
  jQuery(".flip-btn121").click(function(){
    jQuery("#card-1").flip(true);
  });  
  jQuery(".unflip-btn122").click(function(){
    jQuery("#card-1").flip(false);
  });  
  
  jQuery("#card-2").flip({
    trigger: 'manual'
  }); 
  jQuery(".flip-btn221").click(function(){
    jQuery("#card-2").flip(true);
  });  
  jQuery(".unflip-btn222").click(function(){
    jQuery("#card-2").flip(false);
  }); 
    
  jQuery("#card-3").flip({
    trigger: 'manual'
  }); 
  jQuery(".flip-btn321").click(function(){
    jQuery("#card-3").flip(true);
  });  
  jQuery(".unflip-btn322").click(function(){
    jQuery("#card-3").flip(false);
  });
  
  jQuery(".flip-btn111").click(function(){
    jQuery("#card-1").hide();
    jQuery(".secton-comp-two").hide();  
    jQuery(".secton-comp-three").hide();
    jQuery("#card-11").show();  
    jQuery('.secton-comp-one').removeClass('col-md-4');
    jQuery('.secton-comp-one').addClass('col-md-12');
  }); 
  jQuery(".flip-btn112").click(function(){
    jQuery("#card-1").show();
    jQuery(".secton-comp-two").show();  
    jQuery(".secton-comp-three").show();
    jQuery("#card-11").hide();  
    jQuery('.secton-comp-one').removeClass('col-md-12');
    jQuery('.secton-comp-one').addClass('col-md-4');
  });
  
  jQuery(".flip-btn211").click(function(){
    jQuery("#card-2").hide(); 
    jQuery(".secton-comp-one").hide();
    jQuery(".secton-comp-three").hide();  
    jQuery("#card-22").show();  
    jQuery('.secton-comp-two').removeClass('col-md-4');
    jQuery('.secton-comp-two').addClass('col-md-12');
  }); 
  jQuery(".flip-btn212").click(function(){
    jQuery("#card-2").show();
    jQuery(".secton-comp-one").show();
    jQuery(".secton-comp-three").show();  
    jQuery("#card-22").hide();  
    jQuery('.secton-comp-two').removeClass('col-md-12');
    jQuery('.secton-comp-two').addClass('col-md-4');
  });
  
  jQuery(".flip-btn311").click(function(){
    jQuery("#card-3").hide();
    jQuery(".secton-comp-one").hide();
    jQuery(".secton-comp-two").hide();  
    jQuery("#card-33").show();  
    jQuery('.secton-comp-three').removeClass('col-md-4');
    jQuery('.secton-comp-three').addClass('col-md-12');
  }); 
  jQuery(".flip-btn312").click(function(){
    jQuery("#card-3").show();
    jQuery(".secton-comp-one").show();
    jQuery(".secton-comp-two").show();  
    jQuery("#card-33").hide();  
    jQuery('.secton-comp-three').removeClass('col-md-12');
    jQuery('.secton-comp-three').addClass('col-md-4');
  });

  }
  if(getPath == '/hcfm/dashboard3') {
  /*jQuery( init );

function init() {
  jQuery('#makeMeDraggable').draggable( {
    containment: 'parent',
    cursor: 'move',
    snap: '#contentouter'
  } );
}
*/

/*

  jQuery('.draggable-text').draggable({
    cursor: 'move',
    //delay: 200,
    containment: 'parent'
  });
*/

  // draggable item moov start
  jQuery('.draggable-item-1').draggable({
    cursor: 'move',
    //delay: 200,
    containment: 'parent'
  });
  jQuery('.draggable-item-2').draggable({
    cursor: 'move',
    //delay: 200,
    containment: 'parent'
  });
  jQuery('.draggable-item-3').draggable({
    cursor: 'move',
    //delay: 200,
    containment: 'parent'
  });
  // draggable item moov end

  // flip item start
  jQuery(".draggable-item-1").flip({
    trigger: 'manual'
  });
  jQuery(".flip-btn221").click(function(){
    jQuery(".draggable-item-1").flip(true);
  });  
  jQuery(".unflip-btn222").click(function(){
    jQuery(".draggable-item-1").flip(false);
  });
  jQuery(".draggable-item-2").flip({
    trigger: 'manual'
  }); 
  jQuery(".draggable-item-3").flip({
    trigger: 'manual'
  }); 
  // flip item end
  
  
  
  jQuery(".draggable-item-1").hide();
  jQuery(".draggable-item-2").hide();
  jQuery(".draggable-item-3").hide();
  
  jQuery(document).on('click', '.dash-total-asset', function(e) {
    jQuery('.draggable-item-1').toggle();
    if (jQuery('.draggable-item-1').attr('draggable-item-open')) {
        jQuery('.draggable-item-1').removeAttr('draggable-item-open');
      } else {
        jQuery('.draggable-item-1').attr('draggable-item-open', 'draggable-item-1');
      }
    });
  jQuery(document).on('click', '.dash-total-workorder', function(e) {
    jQuery('.draggable-item-2').toggle();
    if (jQuery('.draggable-item-2').attr('draggable-item-open')) {
        jQuery('.draggable-item-2').removeAttr('draggable-item-open');
      } else {
        jQuery('.draggable-item-2').attr('draggable-item-open', 'draggable-item-2');
      }
    });
  jQuery(document).on('click', '.dash-timeline', function(e) {
    jQuery('.draggable-item-3').toggle();
    if (jQuery('.draggable-item-3').attr('draggable-item-open')) {
        jQuery('.draggable-item-3').removeAttr('draggable-item-open');
      } else {
        jQuery('.draggable-item-3').attr('draggable-item-open', 'draggable-item-3');
      }
    });
    
  
  jQuery('.dash-configure-save').click(function (e) {
      e.preventDefault();
    var DashConf = [];
    var DashAtt = [];
    var DashStyle = [];
      jQuery('.draggablecontentouter .draggableitem').each(function () {
    var DashAttValue = jQuery(this).attr('draggable-item-open');
    if(DashAttValue){
      var DashStyleValue = jQuery(this).attr('style');         
      //DashAtt.push(DashAttValue);
     // DashStyle.push(DashStyleValue);
      DashConf.push({'attr':DashAttValue,'style':DashStyleValue});
      
    }
      });
    
    // console.log(DashConf);
    data = JSON.stringify(DashConf);
    jQuery.post('/hcfm/dashboardconfigure-final/'+data);
    });

  }


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
    
  jQuery('.tile-item .thumbnail').click(function (e) {   
    //var DashStyleValue = jQuery(this).toggleClass('tile-height-normal').toggleClass('tile-height-dubble');
    //var DashClassValue = jQuery(this).parent().toggleClass('col-md-3').toggleClass('col-md-6');   
    });   
  jQuery(document).on('click', '.tile-section .tile-item', function(e) {
    /*if (jQuery(this).attr('tile-status')) {
        jQuery(this).removeAttr('tile-status');
      } else {
        jQuery(this).attr('tile-status', 'open');
      }*/
  });
  
  
  function getUpdatedTilePos() {
  var position = [];
  jQuery('.tile-item').each(function(e){
    var ap = jQuery(this).attr('updated-pos');
    if(ap != ''){
    position.push(ap);
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

  jQuery('.tile-item').each(function(e){
  var ap = jQuery(this).attr('tile-status');  
  if(ap == 'closed'){ 
    jQuery(this).children().find('.desh-sec-b').hide();
    jQuery(this).children().find('.desh-sec-a').show(); 
  }else if(ap == 'open'){
    jQuery(this).children().find('.desh-sec-a').hide();
    jQuery(this).children().find('.desh-sec-b').show();
  }
  });

  jQuery(document).on('click', 'a.tile-expand-btn', function(e) {
  
  
    var DashParrentItem = jQuery(this).parent().parent().parent();
      var DashChildItem = jQuery(this).parent().parent();
    DashParrentItem.toggleClass('col-md-3').toggleClass('col-md-6');
    DashChildItem.toggleClass('tile-height-normal').toggleClass('tile-height-dubble');
    var getTitleStatus = DashParrentItem.attr('tile-status'); 
    // console.log(getTitleStatus);
    if (getTitleStatus == 'open') {
        DashParrentItem.attr('tile-status','closed');
    jQuery(this).parent().parent().find('.desh-sec-b').hide();
    jQuery(this).parent().parent().find('.desh-sec-a').show();
      } else {
        DashParrentItem.attr('tile-status','open');
    jQuery(this).parent().parent().find('.desh-sec-a').hide();
    jQuery(this).parent().parent().find('.desh-sec-b').show();
      }
      
    
    
    var getTileOriPos = DashParrentItem.attr('original-pos');
    var getTileUpdPos = DashParrentItem.attr('updated-pos'); 
    // console.log(getTileOriPos); 
    // console.log(getTileUpdPos); 
    
    var TileIndex = DashParrentItem.index();
    
    var item0status = jQuery('.item0').attr('tile-status');
    var item1status = jQuery('.item1').attr('tile-status');
    var item2status = jQuery('.item2').attr('tile-status');
    var item3status = jQuery('.item3').attr('tile-status');
    var item4status = jQuery('.item4').attr('tile-status');
    var item5status = jQuery('.item5').attr('tile-status');
    var item6status = jQuery('.item6').attr('tile-status');
    var item7status = jQuery('.item7').attr('tile-status');
    var item8status = jQuery('.item8').attr('tile-status');
    var item9status = jQuery('.item9').attr('tile-status');
    var item10status = jQuery('.item10').attr('tile-status'); 
    var item11status = jQuery('.item11').attr('tile-status');
    
    
    
    var Tile0UpdPos = jQuery('.item0').attr('updated-pos'); 
    var Tile1UpdPos = jQuery('.item1').attr('updated-pos'); 
    var Tile2UpdPos = jQuery('.item2').attr('updated-pos'); 
    var Tile3UpdPos = jQuery('.item3').attr('updated-pos'); 
    var Tile4UpdPos = jQuery('.item4').attr('updated-pos'); 
    var Tile5UpdPos = jQuery('.item5').attr('updated-pos'); 
    var Tile6UpdPos = jQuery('.item6').attr('updated-pos'); 
    var Tile7UpdPos = jQuery('.item7').attr('updated-pos'); 
    var Tile8UpdPos = jQuery('.item8').attr('updated-pos'); 
    var Tile9UpdPos = jQuery('.item9').attr('updated-pos'); 
    var Tile10UpdPos = jQuery('.item10').attr('updated-pos');   
    var Tile11UpdPos = jQuery('.item11').attr('updated-pos'); 
    //tile 1
    //console.log('status1');
//    console.log(item1status);
//    console.log(item4status);
//    console.log(item5status);

    /* if(TileIndex ==2){
     if(getTileOriPos == 'item0' && getTileUpdPos == '' && (Tile0UpdPos && Tile1UpdPos)){
      //jQuery('.item0').insertBefore('.item1');
      DashParrentItem.attr('updated-pos','item2');
      console.log('shifton1');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item2' && (Tile0UpdPos && Tile1UpdPos)){
     // jQuery('.item0').insertBefore('.item1');
      DashParrentItem.attr('updated-pos','');
      console.log('shifton1');
    }
   
   }
*/






    
    if(getTileOriPos == 'item0' && getTileUpdPos == '' && TileIndex ==0 && (item1status == 'closed' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item0').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','item0');
    // console.log('shifton1');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item0' && TileIndex ==0 && (item1status == 'closed' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item0').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff1');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item0' && TileIndex ==0 && (item1status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    jQuery('.item1').attr('updated-pos','item0');
    // console.log('shiftoff11');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item1' && TileIndex ==0 && (item1status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    jQuery('.item1').attr('updated-pos','item0');
    // console.log('shiftoff111');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == '' && TileIndex ==1 && (item1status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shiftoff112');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item1' && TileIndex ==1 && (item1status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff1123');
    }
    
    else if(getTileOriPos == 'item0' && getTileUpdPos == '' && TileIndex ==1 && (item1status == 'closed' && item2status == 'closed' && item3status == 'closed')){
      //jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shiftoff112');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item1' && TileIndex ==1 && (item1status == 'closed' && item2status == 'closed' && item3status == 'closed')){
      //jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff1123');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == '' && TileIndex ==2 && (Tile3UpdPos && Tile4UpdPos)){
      //jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item2');
    // console.log('shiftoff1123');
    }
    else if(getTileOriPos == 'item0' && getTileUpdPos == 'item2' && TileIndex ==2 && (Tile3UpdPos && Tile4UpdPos)){
      //jQuery('.item0').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff1123');
    }
    //tile 2 if 1 closed
    //console.log('status2');
//    console.log(item0status);
//    console.log(item4status);
//    console.log(item5status);
    if(getTileOriPos == 'item1' && getTileUpdPos == '' && TileIndex ==1 && (item0status == 'closed' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item1').insertBefore('.item0');
    DashParrentItem.attr('updated-pos','item0');
    // console.log('shifton2');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == 'item0' && TileIndex ==1 && (item0status == 'closed' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item1').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff2');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == 'item0' && TileIndex ==0 && (item0status == 'closed' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item1').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff23');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == '' && TileIndex ==1 && (item0status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item1').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shifton22');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == 'item1' && TileIndex ==1 && (item0status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item1').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff22');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == 'item0' && TileIndex ==0 && (item0status == 'open' && item4status == 'closed' && item5status == 'closed')){
      jQuery('.item1').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff223');
    }
    
    else if(getTileOriPos == 'item1' && getTileUpdPos == '' && TileIndex ==2 && (item4status == 'open' && item0status == 'closed' &&  item2status == 'closed' && item3status == 'closed')){
      jQuery('.item1').insertBefore('.item0');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shiftoff223');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == 'item1' && TileIndex ==1 && (item4status == 'open' && item0status == 'closed'  &&  item2status == 'closed' && item3status == 'closed')){
      jQuery('.item1').insertAfter('.item0');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff223');
    }
    
    else if(getTileOriPos == 'item1' && getTileUpdPos == '' && TileIndex ==3 && (Tile3UpdPos && Tile4UpdPos)){
      jQuery('.item1').insertBefore('.item0');
    DashParrentItem.attr('updated-pos','item2');
    // console.log('shiftoff223');
    }
    else if(getTileOriPos == 'item1' && getTileUpdPos == 'item2' && TileIndex ==2 && (Tile3UpdPos && Tile4UpdPos)){
      jQuery('.item1').insertAfter('.item0');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff223');
    }
    
    
    
    //tile 3 
    if(getTileOriPos == 'item2' && getTileUpdPos == '' && TileIndex ==2 && (item0status == 'open' && item1status == 'closed' && item3status == 'closed' && item4status == 'closed')){
      jQuery('.item2').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == 'item1' && TileIndex ==1 && (item0status == 'open' && item1status == 'closed' && item3status == 'closed' && item4status == 'closed')){
      jQuery('.item2').insertAfter('.item1');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == '' && TileIndex ==2 && (item0status == 'open' && item1status == 'open' && item3status == 'closed' && item4status == 'closed')){
      //jQuery('.item2').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','item2');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == 'item2' && TileIndex ==2 && (item0status == 'open' && item1status == 'open' && item3status == 'closed' && item4status == 'closed')){
      //jQuery('.item2').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','');
    // console.log('shifton');
    }
    //1 and 2 close
    else if(getTileOriPos == 'item2' && getTileUpdPos == '' && TileIndex ==2 && (item0status == 'closed' && item1status == 'closed' && item3status == 'closed' && item4status == 'closed')){
      //jQuery('.item2').insertBefore('.item1');
    DashParrentItem.addClass('pull-right');
    DashParrentItem.attr('updated-pos','item2');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == 'item2' && TileIndex ==2 && (item0status == 'closed' && item1status == 'closed' && item3status == 'closed' && item4status == 'closed')){
      //jQuery('.item2').insertBefore('.item1');
    DashParrentItem.removeClass('pull-right');
    DashParrentItem.attr('updated-pos','');
    // console.log('shifton');
    }
    
    else if(getTileOriPos == 'item2' && getTileUpdPos == '' && TileIndex ==3 && (item0status == 'closed' && item1status == 'closed' && item3status == 'closed' && item4status == 'open')){
      jQuery('.item2').insertBefore('.item0');
    //DashParrentItem.addClass('pull-right');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == 'item1' && TileIndex ==1 && (item0status == 'closed' && item1status == 'closed' && item3status == 'closed' && item4status == 'open')){
      jQuery('.item2').insertAfter('.item1');
    //DashParrentItem.removeClass('pull-right');
    DashParrentItem.attr('updated-pos','');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == '' && TileIndex ==4 && (Tile3UpdPos && Tile4UpdPos)){
      //jQuery('.item3').insertBefore('.item0');
    DashParrentItem.addClass('pull-right');
    DashParrentItem.attr('updated-pos','item4');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item2' && getTileUpdPos == 'item4' && TileIndex ==4 && (Tile3UpdPos && Tile4UpdPos)){
      //jQuery('.item3').insertAfter('.item2');
    DashParrentItem.removeClass('pull-right');
    DashParrentItem.attr('updated-pos','');
    // console.log('shifton');
    }
    
    //tile 4 
    if(getTileOriPos == 'item3' && getTileUpdPos == '' && TileIndex ==3 && (item0status == 'open' && item1status == 'closed' && item2status == 'closed' && item4status == 'closed')){
      jQuery('.item3').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item3' && getTileUpdPos == 'item1' && TileIndex ==1 && (item0status == 'open' && item1status == 'closed' && item2status == 'closed' && item4status == 'closed')){
      jQuery('.item3').insertAfter('.item2');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    else if(getTileOriPos == 'item3' && getTileUpdPos == '' && TileIndex ==3 && (item0status == 'open' && item1status == 'open' && item2status == 'closed' && item4status == 'closed')){
      jQuery('.item3').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item2');
    // console.log('shiftoff');
    }
    else if(getTileOriPos == 'item3' && getTileUpdPos == 'item2' && TileIndex ==3 && (item0status == 'open' && item1status == 'open' && item2status == 'closed' && item4status == 'closed')){
      jQuery('.item3').insertAfter('.item2');
    DashParrentItem.attr('updated-pos','');
    console.log('shiftoff');
    }
    // 1, 2, 3 closed
    else if(getTileOriPos == 'item3' && getTileUpdPos == '' && TileIndex ==3 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item4status == 'closed')){
      jQuery('.item3').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item2');
    DashParrentItem.addClass('pull-right');
    // console.log('shiftoff');
    }
    else if(getTileOriPos == 'item3' && getTileUpdPos == 'item2' && TileIndex ==3 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item4status == 'closed')){
      jQuery('.item3').insertAfter('.item2');
    DashParrentItem.attr('updated-pos','');
    DashParrentItem.removeClass('pull-right');
    // console.log('shiftoff');
    }
    
    
    else if(getTileOriPos == 'item3' && getTileUpdPos == '' && TileIndex ==4 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item4status == 'open')){
      jQuery('.item3').insertBefore('.item0');
    //DashParrentItem.addClass('pull-right');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item3' && getTileUpdPos == 'item1' && TileIndex ==1 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item4status == 'open')){
      jQuery('.item3').insertAfter('.item2');
    //DashParrentItem.removeClass('pull-right');
    DashParrentItem.attr('updated-pos','');
    // console.log('shifton');
    }
    
    // console.log('getTileOriPos : '+getTileOriPos);
    // console.log('getTileUpdPos : '+getTileUpdPos);
    // console.log('index : '+TileIndex);
    
    
    
    //tile 5
    //console.log('status5');
//    console.log(item0status);
//    console.log(item1status);
//    console.log(item5status);
    if(getTileOriPos == 'item4' && getTileUpdPos == '' && TileIndex ==4 && (item0status == 'closed' && item1status == 'closed' && item5status == 'closed')){
      jQuery('.item4').insertBefore('.item0');
    DashParrentItem.attr('updated-pos','item0');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item4' && getTileUpdPos == 'item0' && TileIndex ==0 && (item0status == 'closed' && item1status == 'closed' && item5status == 'closed')){
      jQuery('.item4').insertBefore('.item5');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    else if(getTileOriPos == 'item4' && getTileUpdPos == '' && TileIndex ==4 && (item0status == 'open' && item1status == 'closed' && item2status == 'closed'&& item3status == 'closed')){
      jQuery('.item4').insertBefore('.item1');
    DashParrentItem.attr('updated-pos','item1');
    // console.log('shiftoff');
    }
    else if(getTileOriPos == 'item4' && getTileUpdPos == 'item1' && TileIndex ==1 && (item0status == 'open' && item1status == 'closed' && item2status == 'closed'&& item3status == 'closed')){
      jQuery('.item4').insertAfter('.item3');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    
    //tile 6
    //console.log('status6');
//    console.log(item0status);
//    console.log(item1status);
//    console.log(item4status);
    if(getTileOriPos == 'item5' && getTileUpdPos == '' && TileIndex ==5 && (item0status == 'closed' && item1status == 'closed' && item4status == 'closed')){
      jQuery('.item5').insertBefore('.item0');
    DashParrentItem.attr('updated-pos','item0');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item5' && getTileUpdPos == 'item0' && TileIndex ==0 && (item0status == 'closed' && item1status == 'closed' && item4status == 'closed')){
      jQuery('.item5').insertBefore('.item6');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    
    //tile 7
    if(getTileOriPos == 'item6' && getTileUpdPos == '' && TileIndex ==6 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed')){
      jQuery('.item6').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item2');
    DashParrentItem.addClass('pull-right');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item6' && getTileUpdPos == 'item2' && TileIndex ==2 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed')){
      jQuery('.item6').insertBefore('.item7');
    DashParrentItem.attr('updated-pos','');
    DashParrentItem.removeClass('pull-right');
    // console.log('shiftoff');
    }
    
    //tile 8
    if(getTileOriPos == 'item7' && getTileUpdPos == '' && TileIndex ==7 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed' && item4status == 'closed' && item5status == 'closed' && item6status == 'closed')){
      jQuery('.item7').insertBefore('.item2');
    DashParrentItem.attr('updated-pos','item2');
    DashParrentItem.addClass('pull-right');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item7' && getTileUpdPos == 'item2' && TileIndex ==2 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed' && item4status == 'closed' && item5status == 'closed' && item6status == 'closed')){
      jQuery('.item7').insertAfter('.item6');
    DashParrentItem.attr('updated-pos','');
    DashParrentItem.removeClass('pull-right');
    // console.log('shiftoff');
    }
    
    
    //tile 9
   // console.log('status9');
//    console.log(item4status);
//    console.log(item5status);
//    console.log(item6status);
//    console.log(item7status);
    if(getTileOriPos == 'item8' && getTileUpdPos == '' && TileIndex ==8 && (item4status == 'closed' && item5status == 'closed' && item6status == 'closed' && item7status == 'closed')){
      jQuery('.item8').insertBefore('.item4');
    DashParrentItem.attr('updated-pos','item4');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item8' && getTileUpdPos == 'item4' && TileIndex ==4 && (item4status == 'closed' && item5status == 'closed' && item6status == 'closed' && item7status == 'closed')){
      jQuery('.item8').insertBefore('.item9');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    
    //tile 10
    //console.log('status10');
//    console.log(item4status);
//    console.log(item5status);
//    console.log(item6status);
//    console.log(item7status);
//    console.log(item8status);
    if(getTileOriPos == 'item9' && getTileUpdPos == '' && TileIndex ==9 && (item4status == 'closed' && item5status == 'closed' && item6status == 'closed'     && item7status == 'closed' && item8status == 'closed')){
      jQuery('.item9').insertBefore('.item4');
    DashParrentItem.attr('updated-pos','item4');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item9' && getTileUpdPos == 'item4' && TileIndex ==4 && (item4status == 'closed' && item5status == 'closed' && item6status == 'closed'     && item7status == 'closed' && item8status == 'closed')){
      jQuery('.item9').insertBefore('.item10');
    DashParrentItem.attr('updated-pos','');
    // console.log('shiftoff');
    }
    
    
     //tile 11
    if(getTileOriPos == 'item10' && getTileUpdPos == '' && TileIndex ==10 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed' && item4status == 'closed' && item5status == 'closed' && item6status == 'closed' && item7status == 'closed' && item8status == 'closed' && item9status == 'closed')){
      jQuery('.item10').insertBefore('.item6');
    DashParrentItem.attr('updated-pos','item6');
    DashParrentItem.addClass('pull-right');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item10' && getTileUpdPos == 'item6' && TileIndex ==6 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed' && item4status == 'closed' && item5status == 'closed' && item6status == 'closed' && item7status == 'closed' && item8status == 'closed' && item9status == 'closed')){
      jQuery('.item10').insertBefore('.item11');
    DashParrentItem.attr('updated-pos','');
    DashParrentItem.removeClass('pull-right');
    // console.log('shiftoff');
    }
    
     //tile 12
    if(getTileOriPos == 'item11' && getTileUpdPos == '' && TileIndex ==11 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed' && item4status == 'closed' && item5status == 'closed' && item6status == 'closed' && item7status == 'closed' && item8status == 'closed' && item9status == 'closed' && item10status == 'closed')){
      jQuery('.item11').insertBefore('.item6');
    DashParrentItem.attr('updated-pos','item6');
    DashParrentItem.addClass('pull-right');
    // console.log('shifton');
    }
    else if(getTileOriPos == 'item11' && getTileUpdPos == 'item6' && TileIndex ==6 && (item0status == 'closed' && item1status == 'closed' && item2status == 'closed' && item3status == 'closed' && item4status == 'closed' && item5status == 'closed' && item6status == 'closed' && item7status == 'closed' && item8status == 'closed' && item9status == 'closed' && item10status == 'closed')){
      jQuery('.item11').insertAfter('.item10');
    DashParrentItem.attr('updated-pos','');
    DashParrentItem.removeClass('pull-right');
    // console.log('shiftoff');
    }
    
   var Pos1 = ["item0",];
   var Pos12 = ["item0", "item1",];
   var Pos123 = ["item0", "item1", "item2"];
   var Pos1234 = ["item0", "item1", "item2", "item3", "item4"];
   var Pos12345 = ["item0", "item1", "item2", "item3", "item4", "item5"];
   var Pos123456 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6"];
   var Pos1234567 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7"];
   var Pos12345678 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8"];
   var Pos123456789 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9"];
   var Pos12345678910 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9", "item10"];
   var Pos12345678911 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9", "item10", "item11"];
   var Pos12345678912 = ["item0", "item1", "item2", "item3", "item4", "item5", "item6", "item7", "item8", "item9", "item10", "item11", "item12"];
   
   var PosOneTwoThree = '';
   if(TileIndex ==7){
     if(getUpdatedTilePosTrue(PosOneTwoThree = ["item0", "item1", "item2"])){
       DashParrentItem.attr('updated-pos','item7');
     }
     if(getUpdatedTilePosTrue(PosOneTwoThree)){
       DashParrentItem.attr('updated-pos','item7');
     }
     
   }
   
   
    
   console.log(getUpdatedTilePos()); 
      
});
  
  /****************************/
  
  
  
  
  
    
  }


 /*jQuery("input:checkbox.hcfm-image-remove-update").click(function() {
      var getFid = jQuery(this).val();
      var nodeId = jQuery(this).attr('for');
      console.log(getFid);
      console.log(nodeId);
      jQuery.post( '/hcfm-update-image-reove/'+getFid+'/'+nodeId, function( data ) { 
       console.log(data);
        if(data.status == 'updated') {
        jQuery(this).parent().hide();
      }
      });
    }); 
*/

});// reandy end

Drupal.behaviors.m6connect_prog_asset_loc = {
  attach: function (context, settings) {
  var getPath = window.location.pathname; 
  if(getPath == '/hcfm/work_order') {
    //Drupal.attachBehaviors(jQuery('body'));
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
  if(getPath == '/hcfm/add/configure') {
    if(context == document){  
    jQuery('table.asset-detail-table').DataTable({
      "bPaginate": true,
      "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
      "searching": false,
    });
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
      jQuery.post( '/get-facility-floordata-program/'+fNodeNid, function( data ) {
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
     if (urlajax.indexOf("/get-state-list-countrycode-program/"+pfCountry) === 0){
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
  
  } //attach end
}

