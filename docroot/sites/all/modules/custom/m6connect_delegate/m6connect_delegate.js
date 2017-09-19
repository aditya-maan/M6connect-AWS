jQuery(document).ready(function(e) {
    jQuery('#revoke-delegation-access-dialog').dialog({
	  autoOpen: false,
	  width: 400,
	  modal: true,
	  resizable: false,
	  buttons: {
		'Confirm': function() {
		  jQuery( this ).dialog("close");
		  window.location = jQuery('#revoke-delegation-access-dialog').find('.revoke-src').text(); 
		},
		'Cancel': function() {
		  jQuery( this ).dialog("close");
		  jQuery(this).html('');
		}
	  },
	  open: function() {
		jQuery('.ui-dialog-buttonpane').find('button:contains("Confirm")').addClass('confirmButtonClass');
		jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
	  }
	});
	
	jQuery('.delegation-revoke-link').click(function(){
	  var userName = jQuery(this).closest('.delegation-user-box').find('.delegation-user-name').html();
	  var href = jQuery(this).attr('href');
	  jQuery('#revoke-delegation-access-dialog').html('<div class="revoke-delegation-dialog-wrapper row"><div class="col-md-2 revoke-delegation-access-icon"><i class="fa fa-times dalegation-fa-times"></i></div><div class="col-md-10 revoke-delegation-access-msg"><strong>Are you sure you would like to revoke the delegated access for '+userName+'?</strong></div><span class="revoke-src" style="display:none;">'+href+'</span></div>');
	  jQuery('#revoke-delegation-access-dialog').dialog('open');
	  return false;
	})
});
