Drupal.behaviors.m6connect_scm_casemanager = {
  attach: function (context, settings) {
    var getPath = window.location.pathname; 
    /*
    * scm case manager 
    */
    if(getPath == '/scm/buy-change') {
      /*jQuery('input.conditional-element').each(function(e){
        var checkedValue = jQuery(this).val();
        //console.log(checkedValue);        
        jQuery(this).addClass('rvalue-'+checkedValue);       
        if( jQuery(this).is(":checked") ){           
          jQuery(this).parent().parent().attr('datavalue',checkedValue);
        }
        jQuery('.conditional-element').click(function(e){  
          var dval1 = jQuery(this).val(); 
          var tval = jQuery(this).parent().parent().attr('datavalue');
          console.log(dval1);
          console.log(tval);
         // if(jQuery(this).val() == 0){
            if(tval ==0 ){
              //jQuery(this).parent().parent().find('.rvalue-2').trigger('click');
              jQuery(this).parent().parent().attr('datavalue',2);
              console.log(jQuery(this).attr('id'));
              crid =jQuery(this).parent().parent().find('.rvalue-2').attr('id') ;
              console.log(crid);
              //jQuery('#'+crid).trigger('click');

            }
            if(tval ==2 ){
              //jQuery(this).parent().parent().find('.rvalue-1').trigger('click');
              jQuery(this).parent().parent().attr('datavalue',1);
              console.log(jQuery(this).attr('id'));
              crid = jQuery(this).parent().parent().find('.rvalue-1').attr('id');
              console.log(crid);
              //jQuery('#'+crid).trigger('click');
            }
            if(tval ==1 ){
              //jQuery(this).parent().parent().find('.rvalue-0').trigger('click');
              jQuery(this).parent().parent().attr('datavalue',0);
              console.log(jQuery(this).attr('id'));
              crid = jQuery(this).parent().parent().find('.rvalue-0').attr('id');
              console.log(crid);
              //jQuery('#'+crid).trigger('click');
            }
          //}
        });
      });*/

    }
  }
};