(function ($) {
  Drupal.behaviors.m6connect_worker_feedback = {
    attach: function (context, settings) {
      // Hiding status messages.
      setTimeout(function() {
          jQuery(".messages--status").hide(700);
          jQuery(".messages--error").hide(700);
        }, 7000);

      // Destroying slider, hiding form, when cancel is pressed.
      $('.cancel-button').unbind('click').bind('click', function(event) {
        /* Act on the event */
        event.preventDefault();
        $('.worker-feedback-m6reach-edit').hide('500');
        $('#notes-table-worker-feedback').hide();
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
      });

      // Acting on editing vendor node click.
      $('.edit-worker-feedback-link').unbind('click').bind('click', function(event) {
        event.preventDefault();
        var $href = $(this).attr('href');
        var $href_split = $href.split('/');
        var $vnid = $href_split[2];

        $('.worker-feedback-m6reach-edit').hide('500');
        $('#notes-table-worker-feedback').hide();
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
        $('.worker-selector-select').val($vnid);
        $('.worker-selector-select').trigger('change');
      });

      // Acting on clicking hide notes.
      $('.hide-notes-table').unbind('click').bind('click', function(event) {
        // Act on the event 
        $('#notes-table-worker-feedback').hide(500);
      });

      // Thumbs up request.
      $('.like-note-user').unbind('click').bind('click', function(event) {
        /* Act on the event */
        var note_id = $(this).attr('data');
        var curr_ele = $(this);

        if (curr_ele.hasClass('processed')) {
          $('#vwf-like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already bumped up this note.</strong></p></div>');
          $('#vwf-like-dislike-processed-dialog').dialog('open');
          return;
        }

        $.ajax({
          type: 'POST',
          url: '/thumbs-note/like',
          data: {note_id : note_id, where : 'worker_feedback'},
          beforeSend: function() {
            curr_ele.siblings('.pull-left').find('.vendor-spinner').show();
          },
          success: function(output) {
            // console.log(output);
            if (output == 'processed') {
              $('#vwf-like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already bumped this note.</strong></p></div>');
              $('#vwf-like-dislike-processed-dialog').dialog('open');

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

              var worker_data = output.worker_data;
              if (worker_data.uid) {
                var like_worker = '#worker-like-' + worker_data.uid;
                var dislike_worker = '#worker-dislike-' + worker_data.uid;
                var worker_up_count = (!worker_data.data.thumbs_up) ? '0' : worker_data.data.thumbs_up;
                var worker_down_count = (!worker_data.data.thumbs_down) ? '0' : worker_data.data.thumbs_down;

                // Updating values in worker table also.
                $(like_worker).find('.thumbs-up-count').text(worker_up_count);
                $(dislike_worker).find('.thumbs-down-count').text(worker_down_count);
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
          $('#vwf-like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already unbumped this note.</strong></p></div>');
          $('#vwf-like-dislike-processed-dialog').dialog('open');
          return;
        }

        $.ajax({
          type: 'POST',
          url: '/thumbs-note/dislike',
          data: {note_id : note_id, where : 'worker_feedback'},
          beforeSend: function() {
            curr_ele.siblings('.pull-left').find('.vendor-spinner').show();
          },
          success: function(output) {
            if (output == 'processed') {
              $('#vwf-like-dislike-processed-dialog').html('<div class="text-center" style="padding-bottom:25px;"><strong>You have already unbumped this note.</strong></p></div>');
              $('#vwf-like-dislike-processed-dialog').dialog('open');

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

              var worker_data = output.worker_data;
              if (worker_data.uid) {
                var like_worker = '#worker-like-' + worker_data.uid;
                var dislike_worker = '#worker-dislike-' + worker_data.uid;
                var worker_up_count = (!worker_data.data.thumbs_up) ? '0' : worker_data.data.thumbs_up;
                var worker_down_count = (!worker_data.data.thumbs_down) ? '0' : worker_data.data.thumbs_down;

                // Updating values in worker table also.
                $(like_worker).find('.thumbs-up-count').text(worker_up_count);
                $(dislike_worker).find('.thumbs-down-count').text(worker_down_count);
              }
            }
          },
          complete: function() {
            $('.vendor-spinner').hide();
          },
        });
      });


      // Acting on pressing view notes button.
      $('.view-feedback-worker').unbind('click').bind('click', function(event) {
         // Act on the event 
        event.preventDefault();
        $('#notes-table-worker-feedback').show(500);
      });

      // Initialising slider on worker feedback page.
      var worker_feddback_rating_options = settings.worker_feddback_rating_options;
      console.log(worker_feddback_rating_options);
      if (worker_feddback_rating_options !== undefined) {
        $.each(worker_feddback_rating_options, function(index, el) {
          // console.log(index);
          var slider_div = index;
          if ($("#" + slider_div + "-option").length > 0) {
            var handle = $('#worker-feedback-edit-form-main-container').find('input[name=' + slider_div + ']');
            $("#" + slider_div + "-option").slider({
              value: 0,
              min: 0,
              max: 10,
              step: 1,
              animate: "slow",
              create: function( event, ui ) {
                // alert('Came');
                var new_el = '<a href="#" class="custom-ui-handle-disable" style="left: ' + el.rating * 10 + '%;"></a>';
                $("#" + slider_div + "-option").append(new_el);
              },
              slide: function(event, ui) {
                handle.val(ui.value);
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
              var first = 3.3;
              var second = 6.6;
              var third = 9.9;
              for (var i = 0; i <= vals; i++) {
                if (first > i && first < i+1) {
                  var el = $('<label>Silver</label>').css('left','16.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (second > i && second < i+1) {
                  var el = $('<label>Gold</label>').css('left','48.5%');
                  $("#" + slider_div + "-option").append(el);
                }
                if (third > i && third < i+1) {
                  var el = $('<label>Platinum</label>').css('left','78%');
                  $("#" + slider_div + "-option").append(el);
                }
              }
            });
          }
        });
      }

      // Blocking UI while data is being prepared for editing.
      jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
        var urlajax = ajaxOptions.url;
        if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="worker_selector") {
          jQuery.blockUI({
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
      }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
        var urlajax = ajaxOptions.url;
        if (urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="worker_selector") {
          jQuery.unblockUI();
        }
      });
      
      // Acting on adding a worker feedback.
      Drupal.ajax.prototype.commands.destroy_slider_vendor = function(ajax, response, status) {
        // Hiding edit form, if shown.
        $('.worker-feedback-m6reach-edit').hide('500');
        $('#notes-table-worker-feedback').hide();
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
      }
    }
  };

  $(document).ready(function($) {
    $('#vwf-like-dislike-processed-dialog').dialog({
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