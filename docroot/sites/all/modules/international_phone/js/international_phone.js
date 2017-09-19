(function ($) {

  Drupal.behaviors.international_phone = {
    attach: function (context, settings) {
      $(".international_phone-number").intlTelInput({
		 autoHideDialCode: true,
		 nationalMode: false,
        //utilsScript: "lib/libphonenumber/build/utils.js"
      });
    }
  };

}(jQuery));
