   Drupal.behaviors.ProColInfiniteScroll = {
   attach: function (context, settings) {
    if (this.processed) return;
    this.processed=true;
    if (jQuery('#cust-company-listings-clbrte').length==0) return;
       var $container = jQuery('#cust-company-listings-clbrte');
         $container.infinitescroll({
           navSelector  : '.nav-clibrate',    // selector for the paged navigation
           nextSelector : '.nav-clibrate a',  // selector for the NEXT link (to page 2)
				 loading: {
					finishedMsg: "<em>Congratulations, you've reached the end of the internet.</em>",
					img: '/sites/all/themes/m6connect/images/ajax-loader.gif',
					msg: null,
					msgText: '',
					},
					state: {
						currPage: 0
					},
		   //nextSelector: "li.pager-next a",
		   //navSelector: "ul.pager",
           itemSelector : '#cust-company-listings-clbrte .project-box-clbrte',     // selector for all items you'll retrieve
		       contentSelector : '#cust-company-listings-clbrte',
           animate      : true,
           msgText  : Drupal.t("Loading new results..."),
           img: '/sites/all/themes/m6connect/images/ajax-loader.gif',
           donetext:Drupal.t('No more results to load.'),
		   //debug : true,
		   path: function(pageNumber) {
			   var path =  jQuery(".nav-clibrate a").attr("href");
			   path = path.slice(0,-1)+pageNumber;
			   return path;
		  },
		  errorCallback: function(){
        jQuery('.nav-clibrate').html("Congratulations! You have reached the end of internet.");
        jQuery('.nav-clibrate').css({display: 'block'});
      },
		  behavior: "twitter"
    });
 }
};