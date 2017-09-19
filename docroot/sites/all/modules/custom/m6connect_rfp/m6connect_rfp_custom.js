jQuery(document).ready(function($) {
	var base_url = window.location.origin;
	//Infinite Ajax Scroll configuration
  	if(jQuery('body').find('div.rfp-invite-companies-form').length){
	  //alert('test in');
		jQuery.ias({
		  container : '.pro-invite-co-scroll', 
		  item: '.project-box',
		  pagination: '.nav1',
	      next: '.nav1 a', 
		  loader: '<img src="'+base_url+'/sites/all/themes/m6connect/images/ajax-loader.gif"/>',
		  triggerPageThreshold: 0,
		  trigger: "See More", 
		});
  	}
  
 	// if((jQuery('body').hasClass('page-rfps-sent')) || (jQuery('body').hasClass('page-rfps-received'))){
  	if(jQuery('body').hasClass('page-rfps')){	
		jQuery.ias({
			container : '.company-list', // main container where data goes to append
			item: '.views-row', // single items
			pagination: '.rfp-page', // page navigation
			next: '.rfp-page a', // next page selector
			loader: '<img src="'+base_url+'/sites/all/themes/m6connect/images/ajax-loader.gif"/>', 
			triggerPageThreshold: 0, // show load more if scroll more than this
			trigger: "See More", 			
		});		
  	}
  
  	if(jQuery('body').find('div.view-routing-slip-center').length && jQuery('.company-list').find('div.views-row').length){	
		jQuery.ias({
			container : '.company-list', // main container where data goes to append
			item: '.views-row', // single items
			pagination: '.rfp-page', // page navigation
			next: '.rfp-page a', // next page selector
			loader: '<img src="'+base_url+'/sites/all/themes/m6connect/images/ajax-loader.gif"/>', 
			triggerPageThreshold: 0, // show load more if scroll more than this
			trigger: "See More", 			
		});		
  	}
	
	


  	// pagination for view all employee list on company profile page
  	if(jQuery('body').hasClass('section-company')){	
		jQuery.ias({
			container : '.view-company-profile', // main container where data goes to append
			item: '.view-content', // single items
			pagination: '.emp-page', // page navigation
			next: '.emp-page a', // next page selector
			loader: '<img src="'+base_url+'/sites/all/themes/m6connect/images/ajax-loader.gif"/>', 
			triggerPageThreshold: 0, // show load more if scroll more than this
			trigger: "See More", 
			
		});		
	}   
  
});