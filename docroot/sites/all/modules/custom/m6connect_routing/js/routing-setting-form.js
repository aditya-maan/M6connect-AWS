Number.prototype.padLeft = function (n,str){
  return Array(n-String(this).length+1).join(str||'0')+this;
}

Drupal.behaviors.m6connect_routing_setting = {
  attach: function () {
	  
	jQuery("input.rs-type-prefix, input.rs-type-starting-number").keyup(function(event) {
	  var tr = jQuery(this).closest('tr');
	  var markup = tr.find('input.rs-type-prefix').val().toUpperCase();
	  markup = markup.replace(/\s+/, "");
	  tr.find('input.rs-type-prefix').val(markup);
	  var startingNumber = tr.find('input.rs-type-starting-number').val();
	  if(startingNumber!=''){
		startingNumber=padLeft(startingNumber,5);
		markup += ' '+startingNumber;  
	  }
	  /*if(tr.find('input.rs-type-year-extention:checked').val()==1){
		markup +=tr.find('input.rs-type-starting-number-markup').data('year');
	  }*/
	  markup +=tr.find('input.rs-type-starting-number-markup').data('year');
	  tr.find('input.rs-type-starting-number-markup').val(markup);
	});

	jQuery("input.rs-type-year-extention").change(function(event) {
	  var tr = jQuery(this).closest('tr');
	  var markup = tr.find('input.rs-type-prefix').val().toUpperCase();
	  markup = markup.replace(/\s+/, "");
	  var startingNumber = tr.find('input.rs-type-starting-number').val();
	  if(startingNumber!=''){
		startingNumber=padLeft(startingNumber,5); 
		markup += ' '+startingNumber;   
	  }
	  if(tr.find('input.rs-type-year-extention:checked').val()==1){
		markup +=tr.find('input.rs-type-starting-number-markup').data('year');
	  }
	  tr.find('input.rs-type-starting-number-markup').val(markup);
	});
	
	jQuery('.rs-type-delete-link').click(function(e) {
	  var triggerClass = jQuery(this).attr('id');
      jQuery('#routing-setting-type-dialog').dialog({
		  autoOpen: true,
		  width: 500,
		  modal: true,
		  resizable: false,
		  buttons: {
			  'Confirm': function () {
				  jQuery('.'+triggerClass).click();
				  jQuery(this).dialog("close");
				  jQuery(this).html('');
			  },
			  'Cancel': function () {
				  jQuery(this).dialog("close");
				  jQuery(this).html('');
			  }
		  },
		  open: function () {
			  jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
			  jQuery(this).html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to delete this routing slip type?</strong></div>');
			  jQuery('.ui-dialog-titlebar').hide();
		  }
	  });
    });
  }
};

function padLeft(nr, n, str){
    return Array(n-String(nr).length+1).join(str||'0')+nr;
}
  