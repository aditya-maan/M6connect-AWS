// Acting on adding a worker feedback.
Drupal.ajax.prototype.commands.destroy_slider_m6reach = function(ajax, response, status) {
  // Hiding edit form, if shown.
  jQuery('#notes-table-vendor').hide();
  jQuery('.vendor-m6reach-edit').hide('700');
  jQuery('html, body').animate({
    scrollTop: "0px"
  }, 800);

  // Destroying any slider, if present.
  if (jQuery('.ui-slider').length > 0) {
    jQuery('.ui-slider').each(function(index, el) {
      jQuery(this).slider('destroy');
      jQuery(this).html('');
    });
  }
}

// Acting on removing a message from messaging in vendor manager.
Drupal.ajax.prototype.commands.removeMessage = function(ajax, response, status) {
  // Hiding edit form, if shown.
  var selector_ele = response.remove_ele;
  var options = {};
  jQuery(selector_ele).effect('explode', options, 700, function() {
    jQuery(selector_ele).remove();
  } );
  // jQuery(selector_ele).hide(800, function() {
  //   jQuery(selector_ele).remove();
  // });
}

Drupal.ajax.prototype.commands.initializeDataTables = function(ajax, response, status) {
  // This is used after adding a new vendor.
  if (jQuery('table.m6connect-custom-vendor-manager-main-table').length > 0) {
    if (jQuery('#vendor_m6reach_table').hasClass('add-m6reach-datatables-processed')) {
      jQuery('#vendor_m6reach_table').removeClass('add-m6reach-datatables-processed');
    }

    jQuery('table.m6connect-custom-vendor-manager-main-table').DataTable({
      "bPaginate": false,
      "paging": false,
      "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
      "searching": false,
      "info":     false,
      "order": [[ 3, "desc" ]],
    });

    // Adding processed class.
    jQuery('#vendor_m6reach_table').addClass('add-m6reach-datatables-processed');
  }
}


(function ($) {
  Drupal.behaviors.m6connect_vendor = {
    attach: function (context, settings) {
      // Hiding status messages.
      setTimeout(function() {
          $(".messages--status").hide(700);
          $(".messages--error").hide(700);
        }, 20000);

      // Editing vendor spending.
      $('.edit-vendor-spending').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        var $href = $(this).attr('href');
        var $href_split = $href.split('/');
        var $vnid = $href_split[2];
        $('.vendor-spending-edit').hide();

        $('.vendor-spending-node-select').val($vnid);
        $('.vendor-spending-node-select').trigger('change');
        $('.vendor-spending-edit').show(700);
      });

      // Add new spending from ribbon. vendor-spending-edit
      $('.add-vendor-spending').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        $('.vendor-spending-edit-export-form').hide();
        var account_unit_desc = $('input[name=account_unit_desc]').val();
        var pl_name = $('input[name=pl_name]').val();
        var account_desc = $('input[name=account_desc]').val();
        if (account_unit_desc || pl_name || account_desc) {
          $('.vendor-select-vendor-trigger-me').val('none').trigger('change');
        }
        $('.vendor-spending-edit').toggle(700);
      });

      $('.toggle-vendor-spending-export-form').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        $('.vendor-spending-edit').hide();
        var account_unit_desc = $('input[name=account_unit_desc]').val();
        var pl_name = $('input[name=pl_name]').val();
        var account_desc = $('input[name=account_desc]').val();
        if (account_unit_desc || pl_name || account_desc) {
          $('.vendor-select-vendor-trigger-me').val('none').trigger('change');
        }
        $('.vendor-spending-edit-export-form').toggle(700);
      });
      $('.cancel-exporting-data').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        $('.vendor-spending-edit-export-form').hide(700);
      });

      // Cancel vendor spending edit.
      $('.cancel-button-vendor-spending').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        $('.vendor-spending-edit').hide(700);
        var account_unit_desc = $('input[name=account_unit_desc]').val();
        var pl_name = $('input[name=pl_name]').val();
        var account_desc = $('input[name=account_desc]').val();
        if (account_unit_desc || pl_name || account_desc) {
          $('.vendor-select-vendor-trigger-me').val('none').trigger('change');
        }
      });

      // Formatting the invoice amount on keyup.
      $('.edit-vendor-spending-invoice-amt').keyup(function (i) {
        $(this).val(format($(this).val()));
      });

      // Trying to initialise data tables.
      // if ($('#vendor_m6reach_table').find('.dataTables_wrapper').length === 0) {
      //   $('#vendor_m6reach_table', context).once('add-m6reach-datatables', function() {
      //     $('table.m6connect-custom-vendor-manager-main-table').DataTable({
      //       "bPaginate": false,
      //       "paging": false,
      //       "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
      //       "searching": false,
      //       "info":     false,
      //       "order": [[ 3, "desc" ]],
      //     });
      //   });
      // }

      $('.toggle-vendor-rating').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        var ele_class = $(this).attr('data');
        $('.' + ele_class).toggle(400);
        $(this).parents('.toggle-outer').toggleClass('toggle-m6reach-rating');
      });

      // Acting on clicking the ratings tab.
      // We have M6Rank in a hidden cell, and clicking on ratings tab we shall
      // be sorting the M6Rank.
      $('.custom-rating-sort').unbind('click').bind('click', function(e) {
        // Act on the event.
        e.preventDefault();
        $('.custom-rating-sort-it-instead').trigger('click');
      });

      $('.remove-m6reach-options').unbind('click').bind('click', function(event) {
        /* Act on the event */
        var cur_ele = $(this);
        var name = $(this).attr('data');
        var classes = this.className;
        var classes_split = classes.split(' ');
        var service = classes_split[3];

        $('.remove-data-details-service').text(service);
        $('.remove-data-details-name').text(name);

        $('#m6reach-service-remove').html('<div class="text-center" style="padding-bottom:25px;"><strong>Are you sure you want to remove - ' + name + '?</strong></p></div>');
        $('#m6reach-service-remove').dialog('open');
      });

      // Destroying slider, hiding form, when cancel is pressed.
      $('.cancel-button').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        $('#notes-table-vendor').hide();
        $('#form-for-messaging-div').hide();
        // Remove bootstrap class on notes table, if any.

        $('.vendor-m6reach-edit').hide('700');
        $('html, body').animate({
          scrollTop: "0px"
        }, 800);

        // Removing ajax processed class on ratings.
        if ($('#main-container-ratings-pre').hasClass('add-ratings-processed')) {
          $('#main-container-ratings-pre').removeClass('add-ratings-processed');
        }
        // And on tables too, to reinitialise data tables.
        if ($('#vendor_m6reach_table').hasClass('add-m6reach-datatables-processed')) {
          $('#vendor_m6reach_table').removeClass('add-m6reach-datatables-processed');
        }

        // Destroying any slider, if present.
        if ($('.ui-slider').length > 0) {
          $('.ui-slider').each(function(index, el) {
            $(this).slider('destroy');
            $(this).html('');
          });
        }
      });

      $('.trigger-edit').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        // Triggering edit link on the event.
        $('.edit-vendor-node-link').trigger('click');
      });

      // Handing file attachments clicks.
      $('#vendor-attach-fa').unbind('click').bind('click', function(e) {
        e.preventDefault();
        // Opening the file attachment window.
        $('input#vendor-messaging-upload').trigger('click');
      });

      // Handling showing canned messages.
      $('.add-canned-msg-link').unbind('click').bind('click', function(e) {
        e.preventDefault();
        $('.canned-msg-outer').show(['1000', 'clip']);
      });

      $('.close-canned-msg-box').unbind('click').bind('click', function(e) {
        e.preventDefault();
        $('.canned-msg-outer').hide(['1000', 'clip']);
      });

      // Destroying slider, hiding form, when cancel is pressed.
      // $('.cancel-button-messaging').unbind('click').bind('click', function(event) {
      //   /* Act on the event */
      //   event.preventDefault();
      //   // Hide notes table and remove col-md-6 class.
      //   $('#notes-table-vendor').hide();
      //   $('#notes-table-vendor').parent('.clearfix').removeClass('col-md-6');

      //   $('body').removeClass('scroll-top-processed');

      //   $('#form-for-messaging-div').hide();
      //   $('#form-for-messaging-div').html('');
        

      //   // Hide company markup.
      //   $('#company-markup-for-messaging-div').hide();
      //   $('#company-markup-for-messaging-div').html('');
      //   $('html, body').animate({
      //     scrollTop: "0px"
      //   }, 800);

      //   // And on tables too, to reinitialise data tables.
      //   if ($('#vendor_m6reach_table').hasClass('add-m6reach-datatables-processed')) {
      //     $('#vendor_m6reach_table').removeClass('add-m6reach-datatables-processed');
      //   }
      // });

      // When opening notes table, with messaging.
      // $('.view-feedback-m6reach-messaging').unbind('click').bind('click', function(event) {
      //   /* Act on the event */
      //   event.preventDefault();
      //   $('#notes-table-vendor').parent('.clearfix').addClass('col-md-6');
      //   $('#form-for-messaging-div').addClass('col-md-6');
      //   $('#notes-table-vendor').show(700);
      // });

      // Handling canned message.
      $('.canned-msg-item').unbind('click').bind('click', function(e) {
        e.preventDefault();

        // Getting the message.
        var msg = $(this).text();

        // Putting this text into the text field.
        if (msg != '') {
          $('.approval_feedback_message_msg').val(msg);
        }
      });

      // Acting on editing vendor node click.
      $('.edit-vendor-node-link').unbind('click').bind('click', function(event) {
        event.preventDefault();
        var $href = $(this).attr('href');
        var $href_split = $href.split('/');
        var $vnid = $href_split[2];

        // Hiding user messaging, if already opened.
        $('#form-for-messaging-div').hide();
        $('#form-for-messaging-div').html('');
        

        // Hide company markup.
        $('#company-markup-for-messaging-div').hide();
        $('#company-markup-for-messaging-div').html('');

        $('.vendor-m6reach-edit').hide('700');
        $('#notes-table-vendor').hide();
        $('html, body').animate({
          scrollTop: "0px"
        }, 800);

        // Destroying any slider, if present.
        if ($('.ui-slider').length > 0) {
          $('.ui-slider').each(function(index, el) {
            $(this).slider('destroy');
            $(this).html('');
          });
        }

        // Removing ajax processed class on ratings.
        if ($('#main-container-ratings-pre').hasClass('add-ratings-processed')) {
          $('#main-container-ratings-pre').removeClass('add-ratings-processed');
        }
        // And on tables too, to reinitialise data tables.
        if ($('#vendor_m6reach_table').hasClass('add-m6reach-datatables-processed')) {
          $('#vendor_m6reach_table').removeClass('add-m6reach-datatables-processed');
        }

        $('.vendor-node-select').val($vnid);
        $('.vendor-node-select').trigger('change');
      });

      // Acting on clicking hide notes.
      $('.hide-notes-table').unbind('click').bind('click', function(event) {
        /* Act on the event */
        $('#notes-table-vendor').hide(700);
        $('#notes-table-vendor').parent('.clearfix').removeClass('col-md-6');

        // Remove col-md-6 class.
        
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
        $('#notes-table-vendor').show(700);
      });

      // Initialising slider on vendor m6reach page.
      var m6reach_rating_option = settings.m6reach_vendor_rating_options;
      var rating_attributes_otf_js_data = settings.rating_attributes_otf_js_data;

      var company_logo = '';
      var user_logo = '';
      var m6_company_logo_big = '';
      var user_logo_big = '';
      if ($("#m6-vendor-company-logo-tool").length > 0) {
        company_logo = $("#m6-vendor-company-logo-tool").html();
      }
      if ($("#vendor-current-user-img-tool").length > 0) {
        user_logo = $("#vendor-current-user-img-tool").html();
      }

      // Getting tooltip hover data big.
      if ($("#m6-company-logo-tool-big").length > 0) {
        m6_company_logo_big = $("#m6-company-logo-tool-big").html();
      }
      if ($("#current-user-img-tool-big").length > 0) {
        user_logo_big = $("#current-user-img-tool-big").html();
      }

      var company_tooltip = '<span class="custom-tooltip company-logo-tt">' + company_logo + '</span>';
      var user_tooltip = '<span class="custom-tooltip user-img-tt">' + user_logo + '</span>';

      if (m6reach_rating_option !== undefined) {
        $('#main-container-ratings-pre', context).once('add-ratings', function() {
          $.each(m6reach_rating_option, function(index, el) {
            // console.log(index);
            var slider_div = index;
            if ($("#" + slider_div + "-option").length > 0) {
              var handle = $('#main-container-ratings-pre').find('input[name=' + slider_div + ']');
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
                  var slider_name = slider_div.replace(/_/g, " ");
                  slider_name = slider_name.toLowerCase().replace(/\b[a-z]/g, function(letter) {
                      return letter.toUpperCase();
                  });
                  // alert('Came');
                  var new_el = '<a href="#" class="custom-ui-handle-disable" style="left: ' + el.rating * 10 + '%;"></a>';
                  $("#" + slider_div + "-option").append(new_el);

                  // Trying to append tooltip.
                  var tool_big_company = '<span class="custom-tooltip company-logo-tt">' + company_logo + '<div class="tool-big-company" style="display:none;"><div class="tool-big-company-img">' + m6_company_logo_big + '</div><span class="tool-big-company-title">' + slider_name + '</span><span class="tool-big-company-ratings">Ratings - ' + el.rating + '</span></div></span>';
                  var tool_big_user = '<span class="custom-tooltip user-img-tt">' + user_logo + '<div class="tool-big-user" style="display:none;"><div class="tool-big-user-img">' + user_logo_big + '</div><span class="tool-big-user-title">' + slider_name + '</span><span class="tool-big-user-ratings">Ratings - ' + default_val + '</span></div></span>';

                  $("#" + slider_div + "-option").find(".ui-slider-handle").append(tool_big_user);
                  $("#" + slider_div + "-option").find(".custom-ui-handle-disable").append(tool_big_company);
                },
                slide: function(event, ui) {
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
        });
      }


      // Handling message sending in vendor manager messaging system.
      $('.add_new_approval_feedback_message').unbind('click').bind('click', function(event) {
        /* Act on the event */
        // Getting the message value.
        event.preventDefault();
        var formdata = $('.vendor-manager-messaging-form')[0];

        // Trying to save data using ajax.
        $.ajax({
          url: '/vendor-insert-message',
          type: 'POST',
          data: new FormData(formdata),
          contentType: false,
          cache: false,
          processData:false,
          beforeSend: function() {
            // Start spinner here.
            $('.vendor-message-spinner').show();
            // Disable submit button.
            $('.vendor-manager-messaging-form').find('.add_new_approval_feedback_message').css({
              'opacity': '0.5',
              'pointer-events': 'none',
            });
          },
          success: function(data) {
            if (data.success == 'Yes') {
              // If the message is stored succuessfully.
              var container = $('.bidder-feedback-msg-list');

              // Appending new message to the container.
              container.append(data.insert).animate({scrollTop: $('.bidder-feedback-msg-list').prop("scrollHeight")}, 2000);

              // Animating the text value, and removing it.
              $('.approval_feedback_message_msg').animate({color: '#FFFFFF'}, 600, function() {
                $(this).val('');
                $(this).css('color', '#555');
              });

              var tofromusernames = jQuery('.m6messaging-tofromnames').val();
              // if (myobj !== undefined) {
              if (tofromusernames != '') {
                // Generating a json and Sending sockets.
                var tofromusernames_split = tofromusernames.split(':');
                var fromusername = tofromusernames_split[0];
                var tousername = tofromusernames_split[1].split(',');
                var myobj = [{'fromusername':fromusername, 'tousername':tousername}];
                socket_messaging.emit("messageService_broadcast", JSON.stringify(myobj));
              }
              // var myobj = Drupal.settings.m6connect_vendor.socket_names;
              // if (myobj !== undefined) {
              //   // Sending sockets.
              //   console.log(myobj);
              //   socket_messaging.emit("messageService_broadcast", JSON.stringify(myobj));
              // }

              // Reattaching drupal behaviours, so that new ajax links get
              // processed again.
              Drupal.attachBehaviors();
            }
          },
          complete: function() {
            // Stop spinner here.
            $('.vendor-message-spinner').hide();
            // Enable submit button.
            $('.vendor-manager-messaging-form').find('.add_new_approval_feedback_message').css({
              'opacity': '1',
              'pointer-events': 'all',
            });
            // Hiding canned message and attachments div
            $('.canned-msg-outer').hide();
            $('#vendor-messaging-upload-filelist').hide();

            // Clearing any files uploaded.
            $('#vendor-messaging-upload').val('');
          }
        });
      });
    }
  };

  $(document).ready(function($) {
    // Unbinding all click events on 
    $('.custom-rating-sort').unbind('click');
    $('#m6reach-service-remove').dialog({
      autoOpen: false,
      width: 490,
      modal: true,
      resizable: false,
      buttons: {
        'Yes': function () {
          var service = $('.remove-data-details-service').text();
          var name = $('.remove-data-details-name').text();
          $('.rating-data-item').each(function(index, el) {
            if ($(this).find('.remove-m6reach-options').attr('data') == name) {
              // Hide this element.
              var parent_item = $(this).parent('.ratings-data-outer');
              $(this).hide(700, function() {
                $(this).remove();
                if (parent_item.find('.rating-data-item').length === 0) {
                  // If last item was removed.
                  if (service == 'canned') {
                    parent_item.html('<p>No canned messages added yet!</p>');
                  }
                  if (service == 'vendor') {
                    parent_item.html('<p>No vendor status yet!</p>');
                  }
                  if (service == 'attributes') {
                    parent_item.html('<p>No attributes added yet!</p>');
                  }
                }
              });
            }
          });

          $.ajax({
            type: 'POST',
            url: '/remove-m6reach-options',
            data: {setting : service, name : name},
            success:function(output) {
            }
          });
          $('.remove-data-details-service').text('');
          $('.remove-data-details-name').text('');
          $(this).dialog("close");
        },
        'Cancel': function () {
          $('.remove-data-details-service').text('');
          $('.remove-data-details-name').text('');
          $(this).dialog("close");
        }
      },
      open: function () {
        $('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
        $('.ui-dialog-titlebar').hide();
      }
    });

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
        $('.ui-dialog-titlebar').hide();
      },
    });

    // Blocking UI while data is being prepared for editing.
    $(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="vendor_node") {
        $.blockUI({
          baseZ: 2000,
          message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait...</strong></div>',
          css: {
            border: 'none',
            fadeIn: 700,
            fadeOut: 700,
            opacity: 0.96,
            color: '#000',
            padding: '15px',
            cursor: 'wait',
            '-webkit-border-radius': '10px',
            '-moz-border-radius': '10px',
          }
        });
      }
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="vendor_spending_node_edit") {
        $('.vendor-spending-edit').hide();
        $.blockUI({
          baseZ: 2000,
          message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait...</strong></div>',
          css: {
            border: 'none',
            fadeIn: 700,
            fadeOut: 700,
            opacity: 0.96,
            color: '#000',
            padding: '15px',
            cursor: 'wait',
            '-webkit-border-radius': '10px',
            '-moz-border-radius': '10px',
          }
        });
      }
      // if (urlajax.indexOf("/acknowledge-vendor") === 0 || urlajax.indexOf("/request-info-vendor") === 0) {
      //   $('.vendor-m6reach-edit').hide();
      //   $('.company-markup-for-messaging-div').hide();
      //   $('.form-for-messaging-div').hide();
      //   $('#notes-table-vendor').hide();
      //   $.blockUI({
      //     baseZ: 2000,
      //     message: '<div class="text-center"><img style="width:20px;" src="/sites/all/modules/custom/m6connect_misc/doc-upload-busy.gif" />&nbsp;<strong>Please wait...</strong></div>',
      //     css: {
      //       border: 'none',
      //       fadeIn: 700,
      //       fadeOut: 700,
      //       opacity: 0.96,
      //       color: '#000',
      //       padding: '15px',
      //       cursor: 'wait',
      //       '-webkit-border-radius': '10px',
      //       '-moz-border-radius': '10px',
      //     }
      //   });
      // }
    }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
      var urlajax = ajaxOptions.url;
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="vendor_node") {
        $.unblockUI();

        // Scrolling down the message list.
        var container = $('.bidder-feedback-msg-list');
        container.animate({scrollTop: container[0].scrollHeight}, "slow");
      }
      if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="vendor_spending_node_edit") {
        $.unblockUI();
        $('.vendor-spending-edit').show();
        $('html, body').animate({
          scrollTop: "0px"
        }, 800);
        $('.edit-vendor-spending-invoice-amt').each(function () {
          $(this).val(format($(this).val()));
        });
      }
      // if (urlajax.indexOf("/acknowledge-vendor") === 0 || urlajax.indexOf("/request-info-vendor") === 0) {
      //   $.unblockUI();
      //   $('html, body').animate({
      //     scrollTop: "0px"
      //   }, 800);
      //   var container = $('.bidder-feedback-msg-list');
      //   container.animate({scrollTop: container[0].scrollHeight}, "slow");
      //   $('.vendor-action :button').attr('aria-expanded', false);
      //   $('.vendor-action').find('.dropdown').removeClass('open');
      // }
    });
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

// Display file names when uploading in messaging.
updateList = function() {
  var input = document.getElementById('vendor-messaging-upload');
  var output = document.getElementById('vendor-messaging-upload-filelist');

  // Clearing previous files if any.
  jQuery('#vendor-messaging-upload-filelist').html('');
  jQuery('#vendor-messaging-upload-filelist').append('<div class="filelist-outer"></div>');
  // output.innerHTML = '<div class="filelist-outer">';
  for (var i = 0; i < input.files.length; ++i) {
    jQuery('.filelist-outer').append('<span class="filelist-item">' + input.files.item(i).name + '</span>');
  }
  jQuery('#vendor-messaging-upload-filelist').show(['1000', 'clip']);
}

var refreshVendorMessageContent = function() {
  if (jQuery('#vendor-manager-messaging-form').length > 0) {
    // This means that we are on the company profile page.
    // Here we only send this request when a user is actually on message tab.
    var last_ele_id = 0;
    if (jQuery('.bidder-feedback-msg').length > 0) {
      var last_ele = jQuery('.bidder-feedback-msg').last();
      if (last_ele) {
        last_ele_id = last_ele.attr('id');
      }
    }
    if (last_ele_id > 0) {
      jQuery.post( "/vendor-refresh-message", {id:last_ele_id}).done(function(data) {
        if (data.success == 'Yes') {
          // If the message is stored succuessfully.
          var container = $('.bidder-feedback-msg-list');

          // Appending new message to the container.
          container.append(data.insert).animate({scrollTop: $('.bidder-feedback-msg-list').prop("scrollHeight")}, 2000);

          // Reattaching drupal behaviours, so that new ajax links get
          // processed again.
          Drupal.attachBehaviors();
        }
      });
    }
  }
}

var format = function (num) {
  if (!num || num === "0" || num === 0) {
    return "$0";
  }
  var str = num.toString().replace("$", ""), parts = false, output = [], i = 1, formatted = null;
  str = str.replace("-", ""), parts = false, output = [], i = 1, formatted = null;
  if (str.indexOf(".") > 0) {
    parts = str.split(".");
    str = parts[0];
  }
  str = str.split("").reverse();
  for (var j = 0, len = str.length; j < len; j++) {
    if (str[j] != ",") {
      output.push(str[j]);
      if (i % 3 == 0 && j < (len - 1)) {
        output.push(",");
      }
    i++;
    }
  }
  formatted = output.reverse().join("");
    if(num.toString().indexOf("-") != -1) {
      return("$-" + formatted + ((parts) ? "." + parts[1].substr(1, 2) : ""));
    }
  else {
      return("$" + formatted + ((parts) ? "." + parts[1].substr(0, 2) : ""));
    }
  };