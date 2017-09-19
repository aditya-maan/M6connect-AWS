Drupal.behaviors.m6connect_m6_drive = {	
  attach: function (context, settings) {
    
    // Initilize data table for each and evey table of M6Drive
     //Drupal.attachBehaviors(jQuery('body'));
     jQuery(document).ajaxSend(function (event, XMLHttpRequest, ajaxOptions) {
      console.log(ajaxOptions);
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
             //"bInfo": false,
              "bDestroy": true,
             });
            }
          }
          if(urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="folder_name"){
           if(tblrowlenthper > 2){
             jQuery('table.m6connect-custom-m6drive-folder-name').DataTable({
             "bPaginate": true,
             "pageLength": 25,
             //"bLengthChange" : false,
             "sDom": 'Rfrtlip',  
             "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
             "searching": false,
             //"bInfo": false,
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
             //"bInfo": false,
              "bDestroy": true,
             });
            }
          }
          if(urlajax.indexOf("/system/ajax") === 0 && ajaxOptions.hasOwnProperty("extraData") && ajaxOptions.extraData._triggering_element_name==="folder_name"){
            if(tblrowlenthpro > 2){
             jQuery('table.m6connect-custom-m6drive-project-drive').DataTable({
              "bPaginate": true,
              "pageLength": 25,
              //"bLengthChange" : false,
              "sDom": 'Rfrtlip',  
             "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
             "searching": false,
             //"bInfo": false,
              "bDestroy": true,
             });
            }
            //  click
              jQuery('.customsearchformydrive').click(function(e) {
                    var is_checked = false;
                    
                    var check_box = jQuery(this).find('input[type=checkbox]').attr('name');

                    if (!jQuery(this).find('input[type=checkbox]').prop('disabled')) {
                      if(jQuery(this).find('input[type=checkbox]').is(':checked')) {
                        jQuery(this).find('input[type=checkbox]').attr('checked', false);
                        is_checked = false;
                        jQuery('.grid-view').find('input[name=' + check_box + ']').parents('.grid-view-folder-item').removeClass('activeClickclass');
                      }
                      else {
                        jQuery(this).find('input[type=checkbox]').attr('checked', true);
                        is_checked = true;
                        jQuery('.grid-view').find('input[name=' + check_box + ']').parents('.grid-view-folder-item').addClass('activeClickclass');
                      }
                    }
                    // jQuery(".m6drive-folder-checkbox").prop( "checked", this.checked); 
                    
                    // if (e.ctrlKey) {
                    //   //
                    // }
                    // else {
                    //   jQuery(this).siblings().removeClass('activeClickclass');
                    //   jQuery(this).siblings().find('input[type=checkbox]').attr('checked', false);
                    //   jQuery('.grid-view').find('input[name=' + check_box + ']').parents('.grid-view-folder-item').siblings().removeClass('activeClickclass');
                    // }
                    /*if(jQuery(this).is(":checked")) {
                       jQuery(this).prop("checked", false);
                    }
                    else{
                      jQuery(this).prop( "checked", true );
                    }*/
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
                      jQuery(".m6drive-content-hover").hide();
                      jQuery(".m6drive-more-option").show();
                      jQuery(".m6drive-project-more-option").show();
                      if (jQuery(this).hasClass('not-trashable-drive')) {
                        // console.log('In');
                        jQuery('.m6drive-project-more-option a').each(function() {
                          var href_a = jQuery(this).attr('href');
                          if (href_a.indexOf("project-drive-archive") >= 0 || href_a.indexOf("project-drive-trash") >= 0) {
                            jQuery(this).css({'color': '#999', 'pointer-events': 'none'});
                          }
                        });
                      }
                      if (jQuery(this).hasClass('not-shareable-drive')) {
                        // console.log('In share');
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
                      jQuery(".m6drive-content-hover").show();
                      jQuery(".m6drive-project-more-option").hide();
                      jQuery(".m6drive-more-option").hide();
                    }
                    // jQuery('.customsearchformydrive').removeClass('activeClickclass');
                    // jQuery(this).addClass('activeClickclass'); 
              });

            // end click
          }
          
          //jQuery(".m6drive_filter_sort_form").show();
          //jQuery(".m6drive_date_filter_sort_form").show();
          //jQuery(".m6drive_owner_filter_sort_form").show();
         
             
    }); 
  // Column resizer for all cost manager table
   jQuery("table.m6connect-custom-m6drive-folder-name th").resizable({
     handles: "e",
     minHeight: jQuery("table.m6connect-custom-m6drive-folder-name th:first").height(),
     maxHeight: jQuery("table.m6connect-custom-m6drive-folder-name th:first").height(),
     minWidth: 40,
     resize: function (event, ui) {
       var sizerID = "#" + jQuery(event.target).attr("id") + "-sizer";
       jQuery(sizerID).width(ui.size.width);
     }
   });
  	 // Triggering upload.
    jQuery(".m6drive-more-option").hide();
    jQuery(".m6drive-project-more-option").hide();
      
    jQuery('.trigger-upload-drive').unbind('click').bind('click',function () {
      jQuery('.triggering-upload').trigger('click');
    });

    jQuery('#edit-share-permission input[name=share_permission]').once().click(function() {
      var share_perm = jQuery(this).val();
      if (share_perm == 'r') {
        var new_html = '<i class="fa fa-eye" aria-hidden="true"></i> <span class="caret"></span>';
      }
      if(share_perm == 'r-o') {
        var new_html = '<i class="fa fa-pencil-square-o" aria-hidden="true"></i> <span class="caret"></span>';
      }
      if (share_perm == 'r-w-o') {
        var new_html = '<i class="fa fa-download" aria-hidden="true"></i> <span class="caret"></span>';
      }
      if (new_html !== undefined) {
        jQuery(this).parents('.dropdown-menu').siblings('.btn-primary').html(new_html);
      }
    });
    
    /*jQuery('.default-gray').hover(function(){ 
          jQuery(this).show('title');

    });*/
    // jQuery('.customsearchformydrive a').unbind('click').bind('click',function (evt) {
    //   //evt.preventDefault();
    //   //console.log(evt);
    //   //console.log(evt.originalEvent);
    //   // var parent_tr = jQuery(this).parents('.customsearchformydrive');
    //   // parent_tr.siblings().removeClass('activeClickclass');
    //   // if (parent_tr.hasClass('activeClickclass')) {
    //   //   parent_tr.removeClass('activeClickclass'); 
    //   // }
    //   // else {
    //   //   parent_tr.addClass('activeClickclass');
    //   // }

    //   if (evt.originalEvent !== undefined) {
    //     return false;
    //   }
    //   //console.log(evt.type + " prevented");
    // });

 jQuery('.fonclickBtn_popup').click(function () {
     // jQuery('.dropdown-menuv').slideToggle();
    });

  //   jQuery('#edit-share-permission').hide();
  //   jQuery('.form-item-share-permission .rs-icon-view').click(function () {
  //     jQuery('#edit-share-permission').slideToggle();
  //   });
  
  // jQuery('.permission_deniedshare').click(function () {
  //   alert('sdsds');
  //     //confirm("permission denied with share Item");
  //   });
  

  // 	  var countchecked = jQuery("table.m6connect-custom-m6drive-folder-name input[type=checkbox]:checked").length;
		// 	if(countchecked > 0) {
		// 	  jQuery(".m6drive-more-option").show();
		// 	}
		// 	else {
		// 	  jQuery(".m6drive-more-option").hide();
		// 	}

	 // var projectcountchecked = jQuery("table.m6connect-custom-m6drive-project-drive input[type=checkbox]:checked").length;
		// 	if(projectcountchecked > 0) {
		// 	  jQuery(".m6drive-project-more-option").show();
		// 	}
		// 	else {
		// 	  jQuery(".m6drive-project-more-option").hide();
		// 	}
        //=== start For My M6 Drive table data======================//
          // jQuery(".m6drive-more-option").hide();
      jQuery(".select-m6drive-folder-checkbox").click(function () {

           jQuery('.m6drive-folder-checkbox').attr('checked', this.checked);

              if(jQuery(this).is(":checked")) {
                 // jQuery(".m6drive-more-option").show();
                 jQuery(".m6drive-more-option").removeClass('default-gray');
                 jQuery(".m6drive-content-hover").hide();
                 jQuery(".m6drive-more-option").show();
                 
              } else {
                 // jQuery(".m6drive-more-option").hide();
                  jQuery(".m6drive-more-option").addClass('default-gray');
                  jQuery(".m6drive-content-hover").show();
                  jQuery(".m6drive-more-option").hide();
              }
         });
    jQuery(".m6connect-custom-m6drive-folder-name input[type=checkbox]").click(function(){
      var countchecked = jQuery("table input[type=checkbox]:checked").length;
      if(countchecked > 0) {
        // jQuery(".m6drive-more-option").show();
        jQuery(".m6drive-more-option").removeClass('default-gray');
         jQuery(".m6drive-content-hover").hide();
         jQuery(".m6drive-more-option").show();
      }
      else {
        // jQuery(".m6drive-more-option").hide();
        jQuery(".m6drive-more-option").addClass('default-gray');
         jQuery(".m6drive-content-hover").show();
        jQuery(".m6drive-more-option").hide();
      }
    });
      
    var getMultiple = jQuery('.for_multishare_test').val();
    if(getMultiple == '1') {
      var tblrows = jQuery(".m6connect-custom-m6drive-folder-name tbody tr");
      var multiArr = [];
      var getCC = '';
       tblrows.each(function (row, tr) {
           var tblrow = jQuery(this);
           if(tblrow.find(".m6drive-folder-checkbox").is(':checked')) {
         var getCC = tblrow.find(".m6drive-folder-checkbox").val();
              if(getCC !== ''){
               //multiArr[row] = [getCC];
               multiArr.push(getCC);
              }

            }
       });
       var multiArrFol = [];
       var getCC2 = '';
       tblrows.each(function (row, tr) {
           var tblrowNew = jQuery(this);
           if(tblrowNew.find(".m6drive-folder-checkbox").is(':checked')) {
         var getCC2 = tblrowNew.find(".m6drive-folder-checkbox").attr('data');
         //alert(getCC2);
         if(getCC2 != ''){
                multiArrFol.push(getCC2);
             }
            }
       });
         //jQuery('.multiple-share-ids').val(multiArr);
         console.log('hi2');
         jQuery('.multiple-share-ids').val(multiArr.join(','));
         jQuery('.multiple-folders').html(multiArrFol.join(', '));
         console.log(multiArrFol.join(', '));
     }

       //jQuery('#edit-m6drive-file-upload #edit-m6drive-file-upload-button').hide();
       //jQuery('#edit-m6drive-file-upload #edit-m6drive-file-remove-button').hide();
       jQuery('#m6drivefileremovebutton').hide();

     jQuery("#m6drivefileuploadbutton").click(function (e) {
          e.preventDefault();
            jQuery('.form-managed-file').find('input[name="m6drive-file_upload_button"]').trigger('mousedown'); 
       });
       jQuery("#m6drivefileremovebutton").click(function (e) {
          e.preventDefault();
            jQuery('.form-managed-file').find('input[name="m6drive-file_remove_button"]').trigger('mousedown'); 
       });
       
    if(jQuery('input[name="m6drive-file_remove_button"]').length == '0') {
       jQuery('#m6drivefileuploadbutton').show();
        jQuery('#m6drivefileremovebutton').hide();
    }
    else {
       jQuery('#m6drivefileuploadbutton').hide();
       jQuery('#m6drivefileremovebutton').show();
    }
    //================================= End For My M6 Drive table data===================================================//
    
    //================ start here for project drive multiple action perform=============================================//
    // jQuery(".m6drive-project-more-option").hide();
      jQuery(".select-m6drive-project-checkbox").click(function () {
           jQuery('.m6drive-project-checkbox').attr('checked', this.checked);
              if(jQuery(this).is(":checked")) {
                 // jQuery(".m6drive-project-more-option").show();
                 jQuery(".m6drive-project-more-option").removeClass('default-gray');
                 jQuery(".m6drive-project-more-option").show();
                 jQuery(".m6drive-content-hover").hide();  
                
              } else {
                 // jQuery(".m6drive-project-more-option").hide();
                 jQuery(".m6drive-project-more-option").addClass('default-gray');
                 jQuery(".m6drive-project-more-option").hide();
                 jQuery(".m6drive-content-hover").show();  
              }
         });
     
    jQuery(".m6connect-custom-m6drive-project-drive input[type=checkbox]").click(function(){
      var projectcountchecked = jQuery("table input[type=checkbox]:checked").length;
      if(projectcountchecked > 0) {
        // jQuery(".m6drive-project-more-option").show();
        jQuery(".m6drive-project-more-option").removeClass('default-gray');
        jQuery(".m6drive-project-more-option").show();
        jQuery(".m6drive-content-hover").hide(); 
      }
      else {
        // jQuery(".m6drive-project-more-option").hide();
        jQuery(".m6drive-project-more-option").addClass('default-gray');
        jQuery(".m6drive-project-more-option").hide();
        jQuery(".m6drive-content-hover").show(); 
      }
    });
    var projecttblrows = jQuery(".m6connect-custom-m6drive-project-drive tbody tr");
      var projectmultiArr = [];
      var projectval = '';
      projecttblrows.each(function (row, tr) {
           var projectrow = jQuery(this);
           if(projectrow.find(".m6drive-project-checkbox").is(':checked')) {
         var projectval = projectrow.find(".m6drive-project-checkbox").val();
              if(projectval !== ''){
               projectmultiArr.push(projectval);
              }

            }
    });
    jQuery('.multiple-project-drive-perform').val(projectmultiArr.join(','));

      var projectmultiArrFol = [];
       var projectvalshow = '';
       projecttblrows.each(function (row, tr) {
           var projectrowshow = jQuery(this);
           if(projectrowshow.find(".m6drive-project-checkbox").is(':checked')) {
         var projectvalshow = projectrowshow.find(".m6drive-project-checkbox").attr('data');
         if(projectvalshow != ''){
                projectmultiArrFol.push(projectvalshow);
             }
            }
       });
        
        jQuery('.multiple-project-folders-show').html(projectmultiArrFol.join(', '));

	   //================ End  here for project drive multiple action perform=============================================//

      // ========Add Drag Folder here for custom folder========//
      jQuery(".m6drive-display-none-drag").hide();
      var outputm6drivefolder = {};
      jQuery(".m6connect-custom-m6drive-folder-name tbody tr.m6drive-folder-dragable, #m6-drive-datacontainer-main-cust .grid-view .m6drive-folder-dragable").draggable({ 
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
            if(jQuery(this).find('.m6drive-drag-content-show').length){
            var chektype = jQuery(this).find('input[type=checkbox]').val();
            var typefolderorfile = chektype.split("-");
            rethtml = jQuery(this).find('.m6drive-drag-content-show').text();  

            }
              if(typefolderorfile[1] == 'folder'){
                 return jQuery('<div class="clearfix"><i class="fa fa-folder padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+rethtml+'</div></div></div>');
               }else{
                 return jQuery('<div class="clearfix"><i class="fa fa-file padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+rethtml+'</div></div></div>');
               }
            },
            start: function(event, ui) {
                outputm6drivefolder.tr = this;
                outputm6drivefolder.helper = ui.helper;
                outputm6drivefolder.div= this;
                jQuery(this).addClass('drivemove');  
               
                    
            }   
        });
       jQuery(".m6connect-custom-m6drive-folder-name tbody tr.m6drive-folder-droppable, #m6-drive-datacontainer-main-cust .grid-view .m6drive-folder-droppable").droppable({
        hoverClass: "ui-state-active",
        drop: function(event, ui) {
        var dragitem = ui.draggable;
        if (dragitem.hasClass('m6drive-folder-dragable')) {
          var mainitem = dragitem; 
          var folderorfiddrag = mainitem.find(".folder-ids").text();
          //alert(folderorfiddrag);
          var folderconentDrop = jQuery(this).attr('id');

          //alert(folderconentDrop);
          jQuery.get('/folders-drag-drop/'+folderorfiddrag+'/'+folderconentDrop)
            .done(function(data) {
              if (data == 'Success') {
                jQuery(outputm6drivefolder.tr).remove();
                jQuery(outputm6drivefolder.div).remove();
                jQuery(outputm6drivefolder.helper).remove();
              }
            else {
              // Showing dialogue box.
              jQuery('#drive-dialog-status-area').html('<div><p>The requested folder could not be dragged. It might be possible that you are trying to move a parent folder into a child folder. Please try again.</p></div>');
              jQuery('#drive-dialog-status-area').dialog('open');
            }
          });
          }
        }
      });
     // =======end drag Drag Folder here for custom folder===================//

     //===== For breadcrum menu main folder for drag Drag Folder================//
     jQuery("div.search-folder-breadcrumb-custom ul li.m6drive-breadcrumb-droppable").droppable({       
      tolerance: "pointer",
      hoverClass: "ui-state-active",
            drop: function(event, ui) {

              var dragitem = ui.draggable;
              if(dragitem.hasClass('m6drive-folder-dragable')){
              var mainitem = dragitem; 
              var FolderorFidDrag = mainitem.find(".folder-ids").text();
              //alert(FolderorFidDrag);
              var FolderIdDrop = jQuery(this).attr('data');
              //alert(FolderIdDrop);
              jQuery.get('/folders-drag-drop/'+FolderorFidDrag+'/'+FolderIdDrop)
                .done(function(data) {
              });
               
              }
            jQuery(outputm6drivefolder.tr).remove();
            jQuery(outputm6drivefolder.helper).remove();
        }
        
      });

    //===== End  breadcrum menu main folder for drag Drag Folder================//

    //=== drag and drop for project drive=============//

      var projectfoldrag = {};
      jQuery(".m6connect-custom-m6drive-project-drive tbody tr.project-drive-folder-dragable, #project-m6drive-datacontainer-main-cust .grid-view .project-drive-folder-dragable, #project-drive-share-datacontainer-main-cust .grid-view .project-drive-folder-dragable").draggable({ 
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
            var projectfolderorfile =projectchektype.split("-");
              
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
       jQuery(".m6connect-custom-m6drive-project-drive tbody tr.project-drive-folder-droppable, #project-m6drive-datacontainer-main-cust .grid-view .project-drive-folder-droppable, #project-drive-share-datacontainer-main-cust .grid-view .project-drive-folder-droppable").droppable({
            hoverClass: "ui-state-active",
            drop: function(event, ui) {

             var dragitemproject = ui.draggable;
             //console.log(dragitemproject);
              if(dragitemproject.hasClass('project-drive-folder-dragable')){
              var mainitemproject = dragitemproject; 
              var projectfoldrag = mainitemproject.find(".folder-ids").text();
              var projectNids = mainitemproject.find(".project-drive-nids").text();
              var projectfolderDrop = jQuery(this).attr('id');

              //console.log(projectfoldrag);
               //console.log(projectNids);
                //console.log(projectfolderDrop);
             
              jQuery.get('/project-drive-drag-drop/'+projectfoldrag+'/'+projectNids+'/'+projectfolderDrop)
                .done(function(data) {
              });
               
              }
            jQuery(ui.draggable).remove();
            jQuery(ui.helper).remove();
        }
        
      });
    //==== end drag and drop for project=============//
    // ======project folder breadcrum drop=========/// 
     jQuery("div.project-folder-breadcrumb-custom ul li.project-drive-folder-droppable").droppable({
            hoverClass: "ui-state-active",
            drop: function(event, ui) {
             var dragitemproject = ui.draggable;
             //console.log(dragitemproject);
              if(dragitemproject.hasClass('project-drive-folder-dragable')){
              var mainitemproject = dragitemproject; 
              var projectfoldrag = mainitemproject.find(".folder-ids").text();
              var proNids =  jQuery(this).attr('data');
              var projectNids = proNids.split("-");
              var projectfolDrop = jQuery(this).attr('id');
              var projectfolderDrop = projectfolDrop.split("-");

              //console.log(projectfoldrag);
              //console.log(projectNids[0]);
              //console.log(projectfolderDrop[0]);
             
              jQuery.get('/project-drive-drag-drop/'+projectfoldrag+'/'+projectNids[0]+'/'+projectfolderDrop[0])
                .done(function(data) {
              });
               
              }
            jQuery(ui.draggable).remove();
            jQuery(ui.helper).remove();
        }
        
      });
    // ======project folder breadcrum drop=========//
    // Add here for personal M6drive shared Drag and drop//
    var m6drivesharedfoldrag = {};
    jQuery(".m6connect-custom-m6drive-shared-folder-dragtable tbody tr.m6drive-folder-dragable, #m6drive-share-datacontainer-main-cust .grid-view .m6drive-folder-dragable").draggable({ 
            helper: "clone",
            cursor: "move",
            revert: function(event, ui) {
             if(jQuery(this).hasClass("drivemove")) {
               jQuery(this).removeClass("drivemove");
                return true;
              }
            },
            helper: function(event) {
            var rethtmlshare = jQuery(this).html();
            if(jQuery(this).find('.m6drive-drag-content-show').length){
            rethtmlshare = jQuery(this).find('.m6drive-drag-content-show').text(); 
            var sharechektype = jQuery(this).find('input[type=checkbox]').val();
            var sharefolderorfile = sharechektype.split("-");     
            }
               if(sharefolderorfile[1] == 'folder'){
                 return jQuery('<div class="clearfix"><i class="fa fa-folder padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+rethtmlshare+'</div></div></div>');
               }else{
                 return jQuery('<div class="clearfix"><i class="fa fa-file padding-5" aria-hidden="true"></i><div class="m6drive-drag-file-folder display-inline-block">'+rethtmlshare+'</div></div></div>');
               }
            },
            start: function(event, ui) {
                m6drivesharedfoldrag.tr = this;
                m6drivesharedfoldrag.div = this;
                m6drivesharedfoldrag.helper = ui.helper;
                jQuery(this).addClass('drivemove');        
            }
               
        });
       jQuery(".m6connect-custom-m6drive-shared-folder-dragtable tbody tr.m6drive-folder-droppable, #m6drive-share-datacontainer-main-cust .grid-view .m6drive-folder-droppable").droppable({
            hoverClass: "ui-state-active",
            drop: function(event, ui) {

             var dragitemshare = ui.draggable;
              if(dragitemshare.hasClass('m6drive-folder-dragable')){
              var mainitemshare = dragitemshare; 
              var folderorfiddrag = mainitemshare.find(".folder-ids").text();
              //alert(folderorfiddrag);
              var folderconentDrop = jQuery(this).attr('id');
              // console.log(folderorfiddrag);
              // console.log(folderconentDrop);
              //alert(folderconentDrop);
              jQuery.get('/folders-drag-drop/'+folderorfiddrag+'/'+folderconentDrop)
                .done(function(data) {
              });
               
              }
            jQuery(m6drivesharedfoldrag.tr).remove();
            jQuery(m6drivesharedfoldrag.div).remove();
            jQuery(m6drivesharedfoldrag.helper).remove();
        }
        
      });

       jQuery("div.search-folder-breadcrumb-custom-shared ul li.m6drive-shared-breadcrumb-droppable").droppable({ 
              hoverClass: "ui-state-active",      
              tolerance: "pointer",
              drop: function(event, ui) {

                var dragitem = ui.draggable;
                if(dragitem.hasClass('m6drive-folder-dragable')){
                var mainitem = dragitem; 
                var FolderorFidDrag = mainitem.find(".folder-ids").text();
                //alert(FolderorFidDrag);
                var FolderIdDrop = jQuery(this).attr('data');
                //alert(FolderIdDrop);
                jQuery.get('/folders-drag-drop/'+FolderorFidDrag+'/'+FolderIdDrop)
                  .done(function(data) {
                });
                 
                }
               jQuery(ui.draggable).remove();
               jQuery(ui.helper).remove();
          }
          
        });
     // Add here for personal M6drive shared Drag and drop// 
     
    jQuery('.customsearchformydrive').click(function(e) {
      var is_checked = false;
console.log('customsearchformydrive2');
      var check_box = jQuery(this).find('input[type=checkbox]').attr('name');

      if (!jQuery(this).find('input[type=checkbox]').prop('disabled')) {
        if(jQuery(this).find('input[type=checkbox]').is(':checked')) {
          jQuery(this).find('input[type=checkbox]').attr('checked', false);
          is_checked = false;
          jQuery('.grid-view').find('input[name=' + check_box + ']').parents('.grid-view-folder-item').removeClass('activeClickclass');
        }
        else {
          jQuery(this).find('input[type=checkbox]').attr('checked', true);
          is_checked = true;
          jQuery('.grid-view').find('input[name=' + check_box + ']').parents('.grid-view-folder-item').addClass('activeClickclass');
        }
      }
      // jQuery(".m6drive-folder-checkbox").prop( "checked", this.checked); 
      
      // if (e.ctrlKey) {
      //   //
      // }
      // else {
      //   jQuery(this).siblings().removeClass('activeClickclass');
      //   jQuery(this).siblings().find('input[type=checkbox]').attr('checked', false);
      //   jQuery('.grid-view').find('input[name=' + check_box + ']').parents('.grid-view-folder-item').siblings().removeClass('activeClickclass');
      // }
      /*if(jQuery(this).is(":checked")) {
         jQuery(this).prop("checked", false);
      }
      else{
        jQuery(this).prop( "checked", true );
      }*/
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
        jQuery(".m6drive-content-hover").hide();
        jQuery(".m6drive-more-option").show();
        jQuery(".m6drive-project-more-option").show();
        if (jQuery(this).hasClass('not-trashable-drive')) {
          // console.log('In');
          jQuery('.m6drive-project-more-option a').each(function() {
            var href_a = jQuery(this).attr('href');
            if (href_a.indexOf("project-drive-archive") >= 0 || href_a.indexOf("project-drive-trash") >= 0) {
              jQuery(this).css({'color': '#999', 'pointer-events': 'none'});
            }
          });
        }
        if (jQuery(this).hasClass('not-shareable-drive')) {
          // console.log('In share');
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
        jQuery(".m6drive-content-hover").show();
        jQuery(".m6drive-project-more-option").hide();
        jQuery(".m6drive-more-option").hide();
      }
      // jQuery('.customsearchformydrive').removeClass('activeClickclass');
      // jQuery(this).addClass('activeClickclass'); 
    });

    //========= Folder open dobble click event=============== //

    jQuery('.customsearchformydrive').dblclick(function () {
      // jQuery('.customsearchformydrive a').unbind('click');
      if (jQuery(this).find('.drive-getting-folder a.use-ajax').length > 0) {
        // If it is a folder than opening it.
        jQuery(this).find('.drive-getting-folder a').trigger('click');
      }
      if (jQuery(this).find('.drive-getting-folder .orignal-img').length > 0) {
        // If it is an image then display it.
        // Getting the original size image link.
        var img_src = jQuery(this).find('.orignal-img').text();
        // var img_src = jQuery(this).find('img').attr('src');
        if (img_src !== undefined) {
          window.location.href = img_src;
        }
      }
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
          is_checked = false;
        }
        else {
          jQuery('.list-view').find('input[name=' + check_box + ']').attr('checked', true);
          
          is_checked = true;
        }
      }

      if (jQuery(this).hasClass('activeClickclass')) {
        jQuery(this).removeClass('activeClickclass');
        jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').removeClass('activeClickclass');
      }
      else {
        jQuery(this).addClass('activeClickclass');
        jQuery('.list-view').find('input[name=' + check_box + ']').parents('.customsearchformydrive').addClass('activeClickclass');
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
        jQuery(".m6drive-content-hover").hide(); 
        jQuery(".m6drive-project-more-option").show();
        jQuery(".m6drive-more-option").show();

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
        jQuery(".m6drive-content-hover").show(); 
        jQuery(".m6drive-project-more-option").hide();
        jQuery(".m6drive-more-option").hide();

        jQuery('.m6drive-project-more-option a').each(function() {
          jQuery(this).css({'color': '', 'pointer-events': ''});
        });
      }
    });

    // drive filter sort show hide
     jQuery("#drive_filter_sort").click(function(e) {
        jQuery(".m6drive_filter_sort_form").toggle(); 
        e.preventDefault();    
     });
     jQuery("#drive_filter_date_sort").click(function(e) {
        jQuery(".m6drive_date_filter_sort_form").toggle(); 
        e.preventDefault();    
     });
     jQuery("#drive_filter_owner_sort").click(function(e) {
        jQuery(".m6drive_owner_filter_sort_form").toggle(); 
        e.preventDefault();    
     });
     
      
     
    // End drive filter sort show hide
  }

};

jQuery(document).ready(function(e) {
  
  // For personal tabaleData all m6drive table
  jQuery('.dataTables_length').hide();

  if(jQuery('.m6connect-custom-m6drive-folder-name tr').length > 2){
     jQuery('.dataTables_length').css("display","none");
        jQuery('table.m6connect-custom-m6drive-folder-name').DataTable({
            "bPaginate": true,
            //"bLengthChange" : false,
            "sDom": 'Rfrtlip',  
            "pageLength": 25,
            "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
            "searching": false,
             "bDestroy": true,
          });
   }
    // For Project tabaleData
  if(jQuery('.m6connect-custom-m6drive-project-drive tr').length > 2){
     jQuery('.dataTables_length').css("display","none");
        jQuery('table.m6connect-custom-m6drive-project-drive').DataTable({
            "bPaginate": true,
            //"bLengthChange" : false,
            "sDom": 'Rfrtlip',  
            "pageLength": 25,
            "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
            "searching": false,
             "bDestroy": true,
          });
   }
  // End
  jQuery(document).on('click', '.m6drive-grid-list-action a', function() {
    var view = this.className;
    if (view == 'Grid') {
      jQuery('.list-view').hide();
      jQuery('.grid-view').show(400);
      jQuery('.m6drive-grid-list-action').html('<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true" content="List view"></i></a>');
    }
    else {
      jQuery('.grid-view').hide();
      jQuery('.list-view').show(400);
      jQuery('.m6drive-grid-list-action').html('<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true" content="Grid view"></i></a>');
    }
    // jQuery.ajax({
    //   url: '/personal-drive-grid-view/'+view,
    //   type: "POST",
    //   success: function () {
    //     Drupal.attachBehaviors();
    //   },
    // });
    jQuery.get( '/personal-drive-grid-view/'+view)
      .done(function(data) {
    });
    // Drupal.attachBehaviors();
  });
});