(function ($) {
  'use strict';
  $(document).ready(function() {  
    $("#carousel-m6id-company").swiperight(function() {  
	  $("#carousel-m6id-company").carousel("prev");  
    });  
    $("#carousel-m6id-company").swipeleft(function() {  
	  $("#carousel-m6id-company").carousel("next");  
    });   
  });
}(jq1113));
