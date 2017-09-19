(function ($) {
  Drupal.behaviors.m6connect_vendor_cp = {
    attach: function (context, settings) {
      // Hiding status messages.
      setTimeout(function() {
          $(".messages--status").hide(700);
          $(".messages--error").hide(700);
        }, 20000);

      // Adding a new row in Become a vendor form.
      $('.container-inline', context).once('new-row', function() {
        $('.contact-email-first-name-text').blur(function() {
          $('.contact-email-add-new-custom').trigger('mousedown');
        })
      });

      $('.toggle-vendor-rating').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        var ele_class = $(this).attr('data');
        $('.' + ele_class).toggle(400);
        $(this).parents('.toggle-outer').toggleClass('toggle-m6reach-rating');
      });

      $('.toggle-vendor-rating-banner').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        var ele_class = $(this).attr('data');
        $('.' + ele_class).toggle(400);
        $(this).parents('.toggle-outer-banner').toggleClass('toggle-m6reach-rating-banner');
      });

      // Disabling submission of submit and showing message.
      $('.disable-submit-m6reach').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        $('#user-already-rated-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already rated this company.</strong></p></div>');
        $('#user-already-rated-dialog').dialog('open');
      });

      // Acting on clicking hide notes.
      $('.hide-notes-table').unbind('click').bind('click', function(event) {
        /* Act on the event */
        $('#notes-table-vendor').hide(500);
      });

      // Thumbs up request.
      $('.like-note-user').unbind('click').bind('click', function(event) {
        /* Act on the event */
        var note_id = $(this).attr('data');
        var curr_ele = $(this);

        if (curr_ele.hasClass('processed')) {
          $('#like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already bumped up this note.</strong></p></div>');
          $('#like-dislike-processed-dialog').dialog('open');
          return;
        }

        $.ajax({
          type: 'POST',
          url: '/thumbs-note/like',
          data: {note_id : note_id, where : 'm6reach'},
          beforeSend: function() {
            curr_ele.siblings('.pull-left').find('.vendor-spinner').show();
          },
          success: function(output) {
            // console.log(output);
            if (output == 'processed') {
              $('#like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already bumped this note.</strong></p></div>');
              $('#like-dislike-processed-dialog').dialog('open');

              if (!curr_ele.hasClass('processed')) {
                curr_ele.addClass('processed');
              }
              if (curr_ele.siblings('.dislike-note-user').hasClass('processed')) {
                curr_ele.siblings('.dislike-note-user').removeClass('processed');
              }
            }
            if (output !== 'failed' && output !== 'processed') {
              // If output is not failed, then query was successfull.
              // So we shall receive an object.
              var up_count = (!output.up_count) ? '0' : output.up_count;
              var down_count = (!output.down_count) ? '0' : output.down_count;

              curr_ele.siblings('.thumbs-up-count').text(up_count);
              curr_ele.siblings('.thumbs-down-count').text(down_count);

              if (!curr_ele.hasClass('processed')) {
                curr_ele.addClass('processed');
              }
              if (curr_ele.siblings('.dislike-note-user').hasClass('processed')) {
                curr_ele.siblings('.dislike-note-user').removeClass('processed');
              }

              var vendor_data = output.vendor_data;
              if (vendor_data.nid) {
                var like_vendor = '#vendor-like-' + vendor_data.nid;
                var dislike_vendor = '#vendor-dislike-' + vendor_data.nid;
                var vendor_up_count = (!vendor_data.data.thumbs_up) ? '0' : vendor_data.data.thumbs_up;
                var vendor_down_count = (!vendor_data.data.thumbs_down) ? '0' : vendor_data.data.thumbs_down;

                // Updating values in vendor table also.
                $(like_vendor).find('.thumbs-up-count').text(vendor_up_count);
                $(dislike_vendor).find('.thumbs-down-count').text(vendor_down_count);
              }
            }
          },
          complete: function() {
            $('.vendor-spinner').hide();
          },
        });
      });
      
      // Thumbs down request.
      $('.dislike-note-user').unbind('click').bind('click', function(event) {
        /* Act on the event */
        var note_id = $(this).attr('data');
        var curr_ele = $(this);

        if (curr_ele.hasClass('processed')) {
          $('#like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already unbumped this note.</strong></p></div>');
          $('#like-dislike-processed-dialog').dialog('open');
          return;
        }

        $.ajax({
          type: 'POST',
          url: '/thumbs-note/dislike',
          data: {note_id : note_id, where : 'm6reach'},
          beforeSend: function() {
            curr_ele.siblings('.pull-left').find('.vendor-spinner').show();
          },
          success: function(output) {
            if (output == 'processed') {
              $('#like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already unbumped this note.</strong></p></div>');
              $('#like-dislike-processed-dialog').dialog('open');

              if (!curr_ele.hasClass('processed')) {
                curr_ele.addClass('processed');
              }
              if (curr_ele.siblings('.like-note-user').hasClass('processed')) {
                curr_ele.siblings('.like-note-user').removeClass('processed');
              }
            }
            if (output !== 'failed' && output !== 'processed') {
              // If output is not failed, then query was successfull.
              // So we shall receive an object.
              var up_count = (!output.up_count) ? '0' : output.up_count;
              var down_count = (!output.down_count) ? '0' : output.down_count;

              curr_ele.siblings('.thumbs-up-count').text(up_count);
              curr_ele.siblings('.thumbs-down-count').text(down_count);

              if (!curr_ele.hasClass('processed')) {
                curr_ele.addClass('processed');
              }
              if (curr_ele.siblings('.like-note-user').hasClass('processed')) {
                curr_ele.siblings('.like-note-user').removeClass('processed');
              }

              var vendor_data = output.vendor_data;
              if (vendor_data.nid) {
                var like_vendor = '#vendor-like-' + vendor_data.nid;
                var dislike_vendor = '#vendor-dislike-' + vendor_data.nid;
                var vendor_up_count = (!vendor_data.data.thumbs_up) ? '0' : vendor_data.data.thumbs_up;
                var vendor_down_count = (!vendor_data.data.thumbs_down) ? '0' : vendor_data.data.thumbs_down;

                // Updating values in vendor table also.
                $(like_vendor).find('.thumbs-up-count').text(vendor_up_count);
                $(dislike_vendor).find('.thumbs-down-count').text(vendor_down_count);
              }
            }
          },
          complete: function() {
            $('.vendor-spinner').hide();
          },
        });
      });


      // Acting on pressing view notes button.
      $('.view-feedback-m6reach').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        $('#notes-table-vendor').show(500);
      });

      // Initialising slider on vendor m6reach page.
      var m6reach_rating_option = settings.m6reach_vendor_rating_options;
      var m6reach_rating_option_banner = settings.m6reach_vendor_rating_options_banner;
      var m6rank_ratings = settings.m6rank_ratings_js_data_options;
      var m6reach_attributes_options = settings.m6reach_attributes_options_js_data;
      var rating_attributes_otf_js_data = settings.rating_attributes_otf_js_data;
      var m6_company_logo = '';
      var user_logo = '';
      var m6_company_logo_big = '';
      var user_logo_big = '';

      // Getting tooltip data.
      if ($("#m6-company-logo-tool").length > 0) {
        m6_company_logo = $("#m6-company-logo-tool").html();
      }
      if ($("#current-user-img-tool").length > 0) {
        user_logo = $("#current-user-img-tool").html();
      }
      if ($("#current-company-img-tool").length > 0) {
        company_logo = $("#current-company-img-tool").html();
      }

      // Getting tooltip hover data big.
      if ($("#m6-company-logo-tool-big").length > 0) {
        m6_company_logo_big = $("#m6-company-logo-tool-big").html();
      }
      if ($("#current-user-img-tool-big").length > 0) {
        user_logo_big = $("#current-user-img-tool-big").html();
      }
      if ($("#current-company-img-tool-big").length > 0) {
        company_logo_big = $("#current-company-img-tool-big").html();
      }

      var company_tooltip = '<span class="custom-tooltip company-logo-tt">' + m6_company_logo + '</span>';
      var user_tooltip = '<span class="custom-tooltip user-img-tt">' + user_logo + '</span>';

      if (m6reach_rating_option !== undefined) {
        $.each(m6reach_rating_option, function(index, el) {
          // console.log(index);
          var slider_div = index;
          if ($("#" + slider_div + "-option").length > 0) {
            var handle = $('#edit-vendor-ratings').find('input[name=' + slider_div + ']');
            var default_val = 0;
            if (handle.val()) {
              default_val = handle.val();
            }
            if (el.value === 'M6 Rank' && m6rank_ratings !== undefined) {
              if (m6rank_ratings.user) {
                default_val = m6rank_ratings.user;
              }
            }
            $("#" + slider_div + "-option").slider({
              value: default_val,
              min: 0,
              max: 10,
              step: 1,
              animate: "slow",
              create: function( event, ui ) {
                // alert('Came');
                var new_el = '<a href="#" class="custom-ui-handle-disable" style="left: ' + el.rating * 10 + '%;"></a>';
                $("#" + slider_div + "-option").append(new_el);
                var slider_name = slider_div.replace(/_/g, " ");
                slider_name = slider_name.toLowerCase().replace(/\b[a-z]/g, function(letter) {
                    return letter.toUpperCase();
                });

                if (el.value === 'M6 Rank') {
                  if (m6rank_ratings !== undefined) {
                    // If we have ratings, then we put the ratings accordingly.
                    var new_el = '<a href="#" class="custom-ui-handle-disable m6-handle" style="left: ' + m6rank_ratings.m6 * 10 + '%;"></a>';
                    $("#" + slider_div + "-option").append(new_el);
                    var new_el2 = '<a href="#" class="custom-ui-handle-disable company-handle" style="left: ' + m6rank_ratings.company * 10 + '%;"></a>';
                    $("#" + slider_div + "-option").append(new_el2);

                    var tool_big_company = '<span class="custom-tooltip company-logo-tt">' + m6_company_logo + '<div class="tool-big-company" style="display:none;"><div class="tool-big-company-img">' + m6_company_logo_big + '</div><span class="tool-big-company-title">M6 Rank for this company.</span><span class="tool-big-company-ratings">Ratings - ' + m6rank_ratings.m6 + '</span></div></span>';
                    var tool_big_user = '<span class="custom-tooltip user-img-tt">' + user_logo + '<div class="tool-big-user" style="display:none;"><div class="tool-big-user-img">' + user_logo_big + '</div><span class="tool-big-user-title">Your Ratings for this company.</span><span class="tool-big-user-ratings">Ratings - ' + m6rank_ratings.user + '</span></div></span>';
                    var tool_big_company_profile = '<span class="custom-tooltip company-profile-img-tt">' + company_logo + '<div class="tool-big-company-profile" style="display:none;"><div class="tool-big-company-profile-img">' + company_logo_big + '</div><span class="tool-big-company-profile-title">Your company\'s average rating for this company.</span><span class="tool-big-company-profile-ratings">Ratings - ' + m6rank_ratings.company + '</span></div></span>';

                    // Trying to append tooltip.
                    // $("#" + slider_div + "-option").find(".ui-slider-handle").append(user_tooltip);
                    // $("#" + slider_div + "-option").find(".custom-ui-handle-disable").append(company_tooltip);
                    $("#" + slider_div + "-option").find(".ui-slider-handle").append(tool_big_user);
                    $("#" + slider_div + "-option").find(".company-handle").append(tool_big_company_profile);
                    $("#" + slider_div + "-option").find(".m6-handle").append(tool_big_company);
                  }
                }
                else {
                  var new_el = '<a href="#" class="custom-ui-handle-disable" style="left: ' + el.rating * 10 + '%;"></a>';
                  $("#" + slider_div + "-option").append(new_el);

                  var tool_big_company = '<span class="custom-tooltip company-logo-tt">' + m6_company_logo + '<div class="tool-big-company" style="display:none;"><div class="tool-big-company-img">' + m6_company_logo_big + '</div><span class="tool-big-company-title">' + slider_name + '</span><span class="tool-big-company-ratings">Ratings - ' + el.rating + '</span></div></span>';
                  var tool_big_user = '<span class="custom-tooltip user-img-tt">' + user_logo + '<div class="tool-big-user" style="display:none;"><div class="tool-big-user-img">' + user_logo_big + '</div><span class="tool-big-user-title">' + slider_name + '</span><span class="tool-big-user-ratings">Ratings - ' + default_val + '</span></div></span>';

                  // Trying to append tooltip.
                  // $("#" + slider_div + "-option").find(".ui-slider-handle").append(user_tooltip);
                  // $("#" + slider_div + "-option").find(".custom-ui-handle-disable").append(company_tooltip);
                  $("#" + slider_div + "-option").find(".ui-slider-handle").append(tool_big_user);
                  $("#" + slider_div + "-option").find(".custom-ui-handle-disable").append(tool_big_company);
                }
              },
              slide: function(event, ui) {
                if (el.value == 'M6 Rank') {
                  event.preventDefault();
                }
                else {
                  handle.val(ui.value);
                  $("#" + slider_div + "-option").find(".tool-big-user-ratings").text('Ratings - ' + ui.value);
                  if (rating_attributes_otf_js_data !== undefined) {
                    if (rating_attributes_otf_js_data.ratings) {
                      var new_arr_2 = [];
                      if (rating_attributes_otf_js_data.ratings[slider_div] !== undefined) {
                        var new_arr = rating_attributes_otf_js_data.ratings[slider_div];
                        for (var j = 0; j < new_arr.length; j++) {
                          new_arr_2.push(new_arr[j]);
                        }
                        var length_new_arr = new_arr_2.push(ui.value);
                        var total = 0;
                        for (var i = 0; i < length_new_arr; i++) {
                            total += new_arr_2[i] << 0;
                        }
                        var new_avg = total/length_new_arr;
                        var new_avg_tf = new_avg.toFixed(1);
                        $("#" + slider_div + "-option").find('.tool-big-company-ratings').text('Ratings - ' + new_avg_tf);
                        $("#" + slider_div + "-option").find('.custom-ui-handle-disable').css({
                          left: (new_avg * 10) + '%',
                        });
                      }
                    }
                  }
                }
              },
            }).each(function(index, el) {
              //
              // Add labels to slider whose values 
              // are specified by min, max and whose
              // step is set to 1
              //

              // Get the options for this slider
              var opt = $(this).data().uiSlider.options;
              
              // Get the number of possible values
              var vals = opt.max - opt.min;
              
              // Space out values
              var first = 1.9;
              var second = 3.9;
              var third = 5.9;
              var fourth = 7.9;
              for (var i = 0; i <= vals; i++) {
                if (first > i && first < i+1) {
                  var el = $('<label>Silver</label>').css('left','10.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (second > i && second < i+1) {
                  var el = $('<label>Gold</label>').css('left','35.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (third > i && third < i+1) {
                  var el = $('<label>Diamond</label>').css('left','59.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (fourth > i && fourth < i+1) {
                  var el = $('<label>Platinum</label>').css('left','84.5%');
                  $("#" + slider_div + "-option").append(el);
                }
              }
            });
          }
        });
      }

      if (m6reach_attributes_options !== undefined) {
        $.each(m6reach_attributes_options, function(index, el) {
          // console.log(index);
          var slider_div = index;
          if ($("#" + slider_div + "-option").length > 0) {
            var handle = $('#edit-vendor-ratings').find('input[name=' + slider_div + ']');
            var default_val = 0;
            if (handle.val()) {
              default_val = handle.val();
            }
            $("#" + slider_div + "-option").slider({
              value: default_val,
              min: 0,
              max: 10,
              step: 1,
              animate: "slow",
              create: function( event, ui ) {
                // alert('Came');
                var new_el = '<a href="#" class="custom-ui-handle-disable" style="left: ' + el.rating * 10 + '%;"></a>';
                $("#" + slider_div + "-option").append(new_el);
                var slider_name = slider_div.replace(/_/g, " ");
                slider_name = slider_name.toLowerCase().replace(/\b[a-z]/g, function(letter) {
                    return letter.toUpperCase();
                });

                var tool_big_company = '<span class="custom-tooltip company-logo-tt">' + company_logo + '<div class="tool-big-company" style="display:none;"><div class="tool-big-company-img">' + company_logo_big + '</div><span class="tool-big-company-title">' + slider_name + '</span><span class="tool-big-company-ratings">Ratings - ' + el.rating + '</span></div></span>';
                var tool_big_user = '<span class="custom-tooltip user-img-tt">' + user_logo + '<div class="tool-big-user" style="display:none;"><div class="tool-big-user-img">' + user_logo_big + '</div><span class="tool-big-user-title">' + slider_name + '</span><span class="tool-big-user-ratings">Ratings - ' + default_val + '</span></div></span>';

                // Trying to append tooltip.
                // $("#" + slider_div + "-option").find(".ui-slider-handle").append(user_tooltip);
                // $("#" + slider_div + "-option").find(".custom-ui-handle-disable").append(company_tooltip);
                $("#" + slider_div + "-option").find(".ui-slider-handle").append(tool_big_user);
                $("#" + slider_div + "-option").find(".custom-ui-handle-disable").append(tool_big_company);
              },
              slide: function(event, ui) {
                handle.val(ui.value);
                $("#" + slider_div + "-option").find(".tool-big-user-ratings").text('Ratings - ' + ui.value)
                if (rating_attributes_otf_js_data !== undefined) {
                  if (rating_attributes_otf_js_data.attributes) {
                    var new_arr_2 = [];
                    if (rating_attributes_otf_js_data.attributes[slider_div] !== undefined) {
                      var new_arr = rating_attributes_otf_js_data.attributes[slider_div];
                      for (var j = 0; j < new_arr.length; j++) {
                        new_arr_2.push(new_arr[j]);
                      }
                      var length_new_arr = new_arr_2.push(ui.value);
                      var total = 0;
                      for (var i = 0; i < length_new_arr; i++) {
                          total += new_arr_2[i] << 0;
                      }
                      var new_avg = total/length_new_arr;
                      var new_avg_tf = new_avg.toFixed(1);
                      $("#" + slider_div + "-option").find('.tool-big-company-ratings').text('Ratings - ' + new_avg_tf);
                      $("#" + slider_div + "-option").find('.custom-ui-handle-disable').css({
                        left: (new_avg * 10) + '%',
                      });
                    }
                  }
                }
              },
            }).each(function(index, el) {
              //
              // Add labels to slider whose values 
              // are specified by min, max and whose
              // step is set to 1
              //

              // Get the options for this slider
              var opt = $(this).data().uiSlider.options;
              
              // Get the number of possible values
              var vals = opt.max - opt.min;
              
              // Space out values
              var first = 1.9;
              var second = 3.9;
              var third = 5.9;
              var fourth = 7.9;
              for (var i = 0; i <= vals; i++) {
                if (first > i && first < i+1) {
                  var el = $('<label>Silver</label>').css('left','10.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (second > i && second < i+1) {
                  var el = $('<label>Gold</label>').css('left','35.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (third > i && third < i+1) {
                  var el = $('<label>Diamond</label>').css('left','59.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (fourth > i && fourth < i+1) {
                  var el = $('<label>Platinum</label>').css('left','84.5%');
                  $("#" + slider_div + "-option").append(el);
                }
              }
            });
          }
        });
      }

      if (m6reach_rating_option_banner !== undefined) {
        $.each(m6reach_rating_option_banner, function(index, el) {
          // console.log(index);
          var slider_div = index;
          if ($("#" + slider_div + "-option-banner").length > 0) {
            // var handle = $('.company-banner-ratings').find("#" + slider_div + "-option-banner");
            $("#" + slider_div + "-option-banner").slider({
              value: el.rating,
              min: 0,
              max: 10,
              step: 1,
              animate: "slow",
              create: function( event, ui ) {
                // Trying to append tooltip.
                $("#" + slider_div + "-option-banner").find(".ui-slider-handle").append(company_tooltip);
                $("#" + slider_div + "-option-banner").find(".ui-slider-handle").addClass('custom-ui-handle-disable');
              },
              slide: function(event, ui) {
                // handle.val(ui.value);
                event.preventDefault();
              },
            }).each(function(index, el) {
              //
              // Add labels to slider whose values 
              // are specified by min, max and whose
              // step is set to 1
              //

              // Get the options for this slider
              var opt = $(this).data().uiSlider.options;
              
              // Get the number of possible values
              var vals = opt.max - opt.min;
              
              // Space out values
              var first = 1.9;
              var second = 3.9;
              var third = 5.9;
              var fourth = 7.9;
              for (var i = 0; i <= vals; i++) {
                if (first > i && first < i+1) {
                  var el = $('<label>Silver</label>').css('left','10.5%');
                  $("#" + slider_div + "-option-banner").append(el);
                }
                if (second > i && second < i+1) {
                  var el = $('<label>Gold</label>').css('left','35.5%');
                  $("#" + slider_div + "-option-banner").append(el);
                }
                if (third > i && third < i+1) {
                  var el = $('<label>Diamond</label>').css('left','59.5%');
                  $("#" + slider_div + "-option-banner").append(el);
                }
                if (fourth > i && fourth < i+1) {
                  var el = $('<label>Platinum</label>').css('left','84.5%');
                  $("#" + slider_div + "-option-banner").append(el);
                }
              }
            });
          }
        });
      }
    }
  };

  $(document).ready(function($) {
    $('#like-dislike-processed-dialog').dialog({
      autoOpen: false,
      width: 490,
      modal: true,
      resizable: false,
      buttons: {
        'Ok': function () {
          $(this).dialog("close");
        },
      },
      open: function () {
        jQuery('.ui-dialog-titlebar').hide();
      },
    });

    $('#user-already-rated-dialog').dialog({
      autoOpen: false,
      width: 490,
      modal: true,
      resizable: false,
      buttons: {
        'Ok': function () {
          $(this).dialog("close");
        },
      },
      open: function () {
        jQuery('.ui-dialog-titlebar').hide();
      },
    });
    $('.toggle-outer > div').show();
    $('.toggle-vendor-rating').css('color', '#333');
  });
}(jQuery));

/**
 * Function to get query string value.
 */
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
  return false;
};