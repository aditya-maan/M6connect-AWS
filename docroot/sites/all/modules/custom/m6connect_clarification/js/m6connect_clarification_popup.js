jQuery(document).ready(function () { 
  jQuery('body').addClass('modal-open');
  //alert('opened');
  jQuery('#modalContent').bind('remove', function() {
    jQuery('body').removeClass('modal-open');
	//alert('closed');
  });
});

//cus-rfp-clearification