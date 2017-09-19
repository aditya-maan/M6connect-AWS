Drupal.behaviors.m6connect_programs = {  
  attach: function (context, settings) {

     jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
       var urlajax = ajaxOptions.url;
       if (urlajax.indexOf("/load-drive-data") === 0 || urlajax.indexOf("/share-load-drivedata") === 0 || urlajax.indexOf("/trash-load-drive-data") === 0 || urlajax.indexOf("/archive-load-drive-data") === 0){
        }
       if(urlajax.indexOf("/project-load-drive") === 0 || urlajax.indexOf("/project-share-load-drive") === 0 || urlajax.indexOf("/project-archive-load-drive") === 0 ||  urlajax.indexOf("/project-trash-load-drive") === 0){
    
       }
      }).ajaxComplete(function (event, XMLHttpRequest, ajaxOptions) {
          var urlajax = ajaxOptions.url;
          var tblrowlenthper = jQuery('.m6connect-custom-m6drive-folder-name tr').length;
          var tblrowlenthpro = jQuery('.m6connect-custom-m6drive-project-drive tr').length;
          if (urlajax.indexOf("/load-drive-data") === 0 || urlajax.indexOf("/share-load-drivedata") === 0 || urlajax.indexOf("/trash-load-drive-data") === 0 || urlajax.indexOf("/archive-load-drive-data") === 0){
            if(tblrowlenthper > 2){
             jQuery('table.m6connect-custom-m6drive-folder-name').DataTable({
             "bPaginate": true,
             "pageLength": 25,
             //"bLengthChange" : false,
             "sDom": 'Rfrtlip',  
             "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
             "searching": false,
              "bDestroy": true,
             });
            }
          }
         if( urlajax.indexOf("/project-load-drive") === 0 || urlajax.indexOf("/project-share-load-drive") === 0 || urlajax.indexOf("/project-archive-load-drive") === 0 ||  urlajax.indexOf("/project-trash-load-drive") === 0){
            if(tblrowlenthpro > 2){
             jQuery('table.m6connect-custom-m6drive-project-drive').DataTable({
             "bPaginate": true,
             "pageLength": 25,
             //"bLengthChange" : false,
             "sDom": 'Rfrtlip',  
             "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
             "searching": false,
              "bDestroy": true,
             });
            }
          }
        }); 
  // Column resizer for all cost manager table
     // Triggering upload.
    jQuery('.trigger-upload-drive').unbind('click').bind('click',function () {
      jQuery('.triggering-upload').trigger('click');
    });
    
     //================ Start here for m6drive drive serach perform==========// 
    jQuery(".select-m6drive-folder-checkbox").click(function () {
           jQuery('.m6drive-folder-checkbox').attr('checked', this.checked);
              if(jQuery(this).is(":checked")) {
                 jQuery(".m6drive-more-option").removeClass('default-gray');
              } else {
                  jQuery(".m6drive-more-option").addClass('default-gray');
              }
         });


    jQuery(".customsearchformydrive").once().click(function(e) {

      var is_checked = false;

      if (!jQuery(this).find('input[type=checkbox]').prop('disabled')) {
        if(jQuery(this).find('input[type=checkbox]').is(':checked')) {
          jQuery(this).find('input[type=checkbox]').attr('checked', false);
          is_checked = false;
        }
        else {
          jQuery(this).find('input[type=checkbox]').attr('checked', true);
          is_checked = true;
        }
      }
     
        var checkedvalue = jQuery(this).find('input[type=checkbox]').val();
        var checkedvalue = checkedvalue.replace('-folder','');
        // console.log(checkedvalue);
        // var foldername = jQuery(this).find('input[type=checkbox]').attr('data');
      if(jQuery(this).find('input[type=checkbox]').length == 1){
         jQuery.ajax({
                      url: '/getbreadcrumb/'+checkedvalue+'/nojs',
                      type: "POST",
                      success: function (data) {
                        if (jQuery("#right-main-continter-for-breadcrumb").length > 0) {
                          jQuery("#right-main-continter-for-breadcrumb").html(data);
                          jQuery('#right-main-continter-for-breadcrumb li:last').remove();
                          Drupal.attachBehaviors();
                        }
                        else {
                          jQuery("#right-main-continter-project-drive-breadcrumb").html(data);
                          jQuery('#right-main-continter-project-drive-breadcrumb li:last').remove();
                          Drupal.attachBehaviors();
                        }
                      }
            })
        }
        //jQuery(this).siblings().removeClass('activeClickclass');
        //jQuery(this).siblings().find('input[type=checkbox]').attr('checked', false);
     
      if (jQuery(this).hasClass('activeClickclass')) {
        jQuery(this).removeClass('activeClickclass');
      }
      else {
        jQuery(this).addClass('activeClickclass'); 
       
      }

      jQuery(this).siblings().each(function() {
        if(jQuery(this).find('input[type=checkbox]').is(':checked')) {
          is_checked = true;
        }
      });
      if(is_checked) {
        jQuery(".m6drive-more-option").removeClass('default-gray');
        jQuery(".m6drive-project-more-option").removeClass('default-gray');
        if (jQuery(this).hasClass('not-trashable-drive')) {
          jQuery('.m6drive-project-more-option a').each(function() {
            var href_a = jQuery(this).attr('href');
            if (href_a.indexOf("project-drive-archive") >= 0 || href_a.indexOf("project-drive-trash") >= 0) {
              jQuery(this).css({'color': '#999', 'pointer-events': 'none'});
            }
          });
        }
        if (jQuery(this).hasClass('not-shareable-drive')) {
          jQuery('.m6drive-project-more-option a').each(function() {
            var href_a = jQuery(this).attr('href');
            if (href_a.indexOf("project-drive-share") >= 0) {
              jQuery(this).css({'color': '#999', 'pointer-events': 'none'});
            }
          });
        }
      }
      else {
        jQuery(".m6drive-more-option").addClass('default-gray');
        jQuery(".m6drive-project-more-option").addClass('default-gray');
        jQuery('.m6drive-project-more-option a').each(function() {
          jQuery(this).css({'color': '', 'pointer-events': ''});
        });
      }
      // alert('val'+checkedvalue);
    });

// jQuery(".search-folder-breadcrumb-custom ul li p").click(function(){
// alert(dataref);
//       var dataref = jQuery(this).attr('dataref');
//       // jQuery('.customsearchformydrive').removeClass('activeClickclass');
//       //  jQuery(this).addClass('activeClickclass');
      
//        // jQuery.ajax({
//        //              url: dataref,
//        //              type: "POST",
//        //          })

//     });



    jQuery(".m6connect-custom-m6drive-search-folder-name input[type=checkbox]").click(function(){

        var checkedvalue = jQuery(this).val();
        jQuery(this).addClass('test');
      	//alert(checkedvalue);
		    // jQuery.ajax({
      //               url: 'm6drive/search/breadcrumb/'+checkedvalue,
      //               type: "POST",
      //               data: {
      //                   "folderchecked": checkedvalue
      //               },
      //               dataType: "text",
      //           })m6drive-project-more-option
        var countchecked = jQuery("table input[type=checkbox]:checked").length;
          if(countchecked > 0) {
            if (jQuery(".m6drive-more-option").length > 0) {
              jQuery(".m6drive-more-option").removeClass('default-gray');
            }
            else {
              jQuery(".m6drive-project-more-option").removeClass('default-gray');
            }
            jQuery(".m6connect-custom-m6drive-search-folder-name tr").removeClass('select');
          }
          else {
            if (jQuery(".m6drive-more-option").length > 0) {
              jQuery(".m6drive-more-option").addClass('default-gray');
            }
            else {
              jQuery(".m6drive-project-more-option").addClass('default-gray');
            }
            jQuery(".m6connect-custom-m6drive-search-folder-name tr").addClass('select');
          }
    });

    var projecttblrows = jQuery(".m6connect-custom-m6drive-search-folder-name tbody tr");
      var projectmultiArr = [];
      var projectval = '';
      projecttblrows.each(function (row, tr) {
           var projectrow = jQuery(this);
           if(projectrow.find(".m6drive-folder-checkbox").is(':checked')) {
         var projectval = projectrow.find(".m6drive-folder-checkbox").val();
              if(projectval !== ''){
               projectmultiArr.push(projectval);
              }

            }
    });

      var projectmultiArrFol = [];
       var projectvalshow = '';
       projecttblrows.each(function (row, tr) {
           var projectrowshow = jQuery(this);
           if(projectrowshow.find(".m6drive-folder-checkbox").is(':checked')) {
         var projectvalshow = projectrowshow.find(".m6drive-folder-checkbox").attr('data');
         if(projectvalshow != ''){
                projectmultiArrFol.push(projectvalshow);
             }
            }
       });
       
      if (jQuery('.multiple-project-drive-perform').length > 0 && projectmultiArr.length > 0) {
        jQuery('.multiple-project-drive-perform').val(projectmultiArr.join(','));
        jQuery('.multiple-project-folders-show').html(projectmultiArrFol.join(', '));
      }
      if (jQuery('.multiple-share-ids').length > 0 && projectmultiArr.length > 0) {
        console.log('hi1');

        jQuery('.multiple-share-ids').val(projectmultiArr.join(','));
        jQuery('.multiple-folders').html(projectmultiArrFol.join(', '));
        console.log(projectmultiArrFol.join(', '));
      }
      
     //================ End here here for m6drive drive serach perform==========//

     // Add Drag Folder here for custom serach folder
      jQuery(".m6drive-display-none-drag").hide();
      var outm6drivefolder = {};
      jQuery(".m6connect-custom-m6drive-search-folder-name tbody tr.m6drive-folder-dragable, .page-m6drive-search #m6-drive-datacontainer-main-cust .grid-view .m6drive-folder-dragable").draggable({ 
            helper: "clone",
            cursor: "move",
            revert: function(event, ui) {
             if(jQuery(this).hasClass("drivemove")) {
               jQuery(this).removeClass("drivemove");
                return true;
              }
            },
            helper: function(event) {
            var rethtml = jQuery(this).html();
            if(jQuery(this).find('.m6drive-drag-content-show').length) {
            rethtml = jQuery(this).find('.m6drive-drag-content-show').text();
            var chektype = jQuery(this).find('input[type=checkbox]').val();
            var typefolderorfile = chektype.split("-");
            }
               if(typefolderorfile[1] == 'folder'){
                 return jQuery('<div class="clearfix"><i class="fa fa-folder padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+rethtml+'</div></div></div>');
               }else{
                 return jQuery('<div class="clearfix"><i class="fa fa-file padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+rethtml+'</div></div></div>');
               }
            },
            start: function(event, ui) {
                outm6drivefolder.tr = this;
                outm6drivefolder.helper = ui.helper;
                jQuery(this).addClass('drivemove'); 
            }
            
        });
       jQuery(".m6connect-custom-m6drive-search-folder-name tbody tr.m6drive-folder-droppable, .page-m6drive-search #m6-drive-datacontainer-main-cust .grid-view .m6drive-folder-droppable").droppable({
            hoverClass: "ui-state-active",
            drop: function(event, ui) {

             var dragitem = ui.draggable;
              if (dragitem.hasClass('m6drive-folder-dragable')) {
                var mainitem = dragitem; 
                var folderorfiddrag = mainitem.find(".folder-ids").text();
                var folderconentDrop = jQuery(this).attr('id');
                jQuery.get( '/folders-drag-drop/'+folderorfiddrag+'/'+folderconentDrop)
                  .done(function(data) {
                    if (data == 'Success') {
                      jQuery(outm6drivefolder.tr).remove();
                      jQuery(outm6drivefolder.helper).remove();
                    }
                    else {
                    // Showing dialogue box.
                    jQuery('#drive-dialog-status-area').html('<div><p>The requested folder could not be dragged. It might be possible that you are trying to move a parent folder into a child folder. Please try again.</p></div>');
                    Drupal.attachBehaviors(jQuery('body'));
                    jQuery('#drive-dialog-status-area').dialog('open');
                    }
                });
              }
        }
        
      });
     // end drag Drag Folder here for custom serach folder/////// 

     //======== Project search drag and drop================//
       var projectfoldrag = {};
      jQuery("div#project-m6drive-datacontainer-main-cust .m6connect-custom-m6drive-search-folder-name tbody tr.project-drive-folder-dragable, .page-project-search #project-m6drive-datacontainer-main-cust .grid-view .project-drive-folder-dragable").draggable({ 
            helper: "clone",
            cursor: "move",
            revert: function(event, ui) {
             if(jQuery(this).hasClass("drivemove")) {
               jQuery(this).removeClass("drivemove");
                return true;
              }
            },
            helper: function(event) {
            var projecthtml = jQuery(this).html();
            if(jQuery(this).find('.m6drive-drag-content-show').length){
            projecthtml = jQuery(this).find('.m6drive-drag-content-show').text(); 
            var projectchektype = jQuery(this).find('input[type=checkbox]').val();
            var projectfolderorfile = projectchektype.split("-");        
            }
               if(projectfolderorfile[1] == 'folder'){
                 return jQuery('<div class="clearfix"><i class="fa fa-folder padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+projecthtml+'</div></div></div>');
               }else{
                 return jQuery('<div class="clearfix"><i class="fa fa-file padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+projecthtml+'</div></div></div>');
               }
            },
            start: function(event, ui) {
                projectfoldrag.tr = this;
                projectfoldrag.helper = ui.helper;
                jQuery(this).addClass('drivemove');        
            }   
        });
      jQuery("div#project-m6drive-datacontainer-main-cust .m6connect-custom-m6drive-search-folder-name tbody tr.project-drive-folder-droppable, .page-project-search #project-m6drive-datacontainer-main-cust .grid-view .project-drive-folder-droppable").droppable({
            hoverClass: "ui-state-active",
            drop: function(event, ui) {

             var dragitemproject = ui.draggable;
             //console.log(dragitemproject);
              if(dragitemproject.hasClass('project-drive-folder-dragable')){
              var mainitemproject = dragitemproject; 
              var projectfoldrag = mainitemproject.find(".folder-ids").text();
              var projectNids = mainitemproject.find(".project-drive-nids").text();
              var projectfolderDrop = jQuery(this).attr('id');
              jQuery.get('/project-drive-drag-drop/'+projectfoldrag+'/'+projectNids+'/'+projectfolderDrop)
                .done(function(data) {
                  if (data == 'Success') {
                    jQuery(ui.draggable).remove();
                    jQuery(ui.helper).remove();
                  }
                  else {
                  // Showing dialogue box.
                  jQuery('#drive-dialog-status-area').html('<div><p>The requested folder could not be dragged. It might be possible that you are trying to move a parent folder into a child folder, or trying to move a folder into another project. Please try again.</p></div>');
                  Drupal.attachBehaviors(jQuery('body'));
                  jQuery('#drive-dialog-status-area').dialog('open');
                  }
              });
               
              }
        }
        
      });
     //======= End Project search drag and drop=============//

     //========= Folder open dobble click event=============== //

     jQuery('.customsearchformydrive').dblclick(function () {
       // jQuery('.customsearchformydrive a').unbind('click');
        jQuery(this).find('.drive-getting-folder a').trigger('click');
     });
    jQuery('.grid-view-folder-item').dblclick(function () {
      // jQuery('.customsearchformydrive a').unbind('click');
      if (jQuery(this).find('.grid-item-anchor a').length > 0) {
        // If it is a folder than opening it.
        jQuery(this).find('.grid-item-anchor a').trigger('click');
      }
      else {
      // if (jQuery(this).find('img').length > 0) {
        // If it is an image then display it.
        // Getting the original size image link.
        var img_src = jQuery(this).find('.orignal-img').text();
        // var img_src = jQuery(this).find('img').attr('src');
        if (img_src !== undefined) {
          window.location.href = img_src;
        }
      }
    });

    //========= End Folder open dobble click event=============== //
    // Grid - List View - Personal Drive.
    jQuery('.grid-view-folder-item').click(function(e) {
      var is_checked = false;
      var check_box = jQuery(this).find('input[type=checkbox]').attr('name');

      if (!jQuery('.list-view').find('input[name=' + check_box + ']').prop('disabled')) {
        if (jQuery('.list-view').find('input[name=' + check_box + ']').is(':checked')) {
          jQuery('.list-view').find('input[name=' + check_box + ']').attr('checked', false);
          jQuery(this).removeClass('activeClickclass');
          jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').removeClass('activeClickclass');
          is_checked = false;
        }
        else {
          jQuery('.list-view').find('input[name=' + check_box + ']').attr('checked', true);
          jQuery(this).addClass('activeClickclass');
          jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').addClass('activeClickclass');
          is_checked = true;
        }
      }

      /*if (e.ctrlKey) {
        //
      }
      else {
        jQuery(this).siblings().removeClass('activeClickclass');
        if (jQuery(this).parents('.grid-view-files').length > 0) {
          // This means that file was clicked.
          // Removing classes from folders also.
          jQuery('.grid-view-folders .grid-view-folder-item').each(function() {
            jQuery(this).removeClass('activeClickclass');
          });
        }
        else {
          // This is the case when the folder was clicked.
          // Removing classes from files.
          jQuery('.grid-view-files .grid-view-folder-item').each(function() {
            jQuery(this).removeClass('activeClickclass');
          });
        }
        jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').siblings().removeClass('activeClickclass');
        jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').siblings().find('input[type=checkbox]').attr('checked', false);
      }*/

      jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').siblings().each(function() {
        if(jQuery(this).find('input[type=checkbox]').is(':checked')) {
          is_checked = true;
        }
      });

      if(is_checked) {
        jQuery(".m6drive-more-option").removeClass('default-gray');
        jQuery(".m6drive-project-more-option").removeClass('default-gray');
        if (jQuery(this).hasClass('not-trashable-drive')) {
          jQuery('.m6drive-project-more-option a').each(function() {
            var href_a = jQuery(this).attr('href');
            if (href_a.indexOf("project-drive-archive") >= 0 || href_a.indexOf("project-drive-trash") >= 0) {
              jQuery(this).css({'color': '#999', 'pointer-events': 'none'});
            }
          });
        }
        if (jQuery(this).hasClass('not-shareable-drive')) {
          jQuery('.m6drive-project-more-option a').each(function() {
            var href_a = jQuery(this).attr('href');
            if (href_a.indexOf("project-drive-share") >= 0) {
              jQuery(this).css({'color': '#999', 'pointer-events': 'none'});
            }
          });
        }
      }
      else {
        jQuery(".m6drive-more-option").addClass('default-gray');
        jQuery(".m6drive-project-more-option").addClass('default-gray');
        jQuery('.m6drive-project-more-option a').each(function() {
          jQuery(this).css({'color': '', 'pointer-events': ''});
        });
      }
    });
 }
};

jQuery(document).ready(function(e) {
  // For personal tabaleData all m6drive table
  if(jQuery('.m6connect-custom-m6drive-search-folder-name tr').length > 2){
        jQuery('table.m6connect-custom-m6drive-search-folder-name').DataTable({
            "bPaginate": true,
            "pageLength": 25,
            //"bLengthChange" : false,
            "sDom": 'Rfrtlip', 
            "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
            "searching": false,
             "bDestroy": true,
          });
   }
  jQuery(document).on('click', '.m6drive-grid-list-action a', function() {
    var view = this.className;
    if (view == 'Grid') {
      jQuery('.list-view').hide();
      jQuery('.grid-view').show(400);
      jQuery('.m6drive-grid-list-action').html('<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true"></i></a>');
    }
    else {
      jQuery('.grid-view').hide();
      jQuery('.list-view').show(400);
      jQuery('.m6drive-grid-list-action').html('<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true"></i></a>');
    }
    jQuery.get( '/personal-drive-grid-view/'+view)
      .done(function(data) {
    });
    //Drupal.attachBehaviors();
  });

  jQuery('#drive-dialog-status-area').dialog({
  autoOpen: false,
  width: 490,
  modal: true,
  resizable: false,
  closeOnEscape: true,
  buttons: {
      'Ok': function () {
        jQuery(this).dialog("close");
        jQuery('#drive-dialog-status-area').html('');
      }
    },
  open: function () {
      // jQuery('.ui-dialog-buttonpane').find('button:contains("Cancel")').addClass('cancelButtonClass');
      jQuery('.ui-dialog-titlebar').hide();
  }
  });
});

function myAjaxsearch(){
  // alert('test');
}