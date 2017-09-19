// JavaScript Document
Drupal.behaviors.m6connect_companies = {
  attach:function(){
	Drupal.m6connectfav = {};
	//Start Add New Folder 
	Drupal.m6connectfav.build_addfolder_popup = function(response) {
	  //console.log(response);
	  jQuery("#dialog").html(response.html);
	  jQuery('.ui-dialog-titlebar').hide();
	  jQuery('#dialog').dialog('open');
	  // Form elements
	  var form_button = jQuery('#'+response.data.button['#attributes'].id);
	  var form_cancel_button = jQuery('#'+response.data.cancel['#attributes'].id);
	  var target_form = form_button.parents("form:first");
	  // When button click event is invoked send form to add folder menu callback
	  form_button.click(function() {
		jQuery.ajax({  
		  type: "GET",  
		  url: response.path,
		  data:  target_form.serialize() + "&js=1",  
		  success: function(data) {
		     jQuery.get( '/favorite-content').done(function( data ) {
			   jQuery('.favorite-replaceable',main).replaceWith(data.html);
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
		     });
			jQuery('#dialog').dialog('close');
		  },
		  dataType: "json"
		});
		return false;
	  });
	  // Cancel button click event handling
	  form_cancel_button.click(function() {
		jQuery('#dialog').dialog('close');
		return false;
	  });
	  
	}
	
	//Start Remove Bookmark 
	Drupal.m6connectfav.build_remove_popup = function(response) {
	  jQuery("#dialog").html(response.html);
	  jQuery('.ui-dialog-titlebar').hide();
	  jQuery('#dialog').dialog('open');
	  // Form elements
	  var form_button = jQuery('#'+response.data.button['#attributes'].id);
	  var form_cancel_button = jQuery('#'+response.data.cancel['#attributes'].id);
	  var target_form = form_button.parents("form:first");
	  form_button.click(function() {
		jQuery.ajax({  
		  type: "GET",  
		  url: response.path,
		  data:  target_form.serialize() + "&js=1",  
		  success: function(data) {
			jQuery.get( '/favorite-content').done(function( data ) {
			   jQuery('.favorite-replaceable',main).replaceWith(data.html);
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
		     });
			jQuery('#dialog').dialog('close');
		  },
		  dataType: "json"
		});
		return false;
	  });
	  // Cancel button click event handling
	  form_cancel_button.click(function() {
		jQuery('#dialog').dialog('close');
		return false;
	  });    
	}
	//End Remove Bookmark
	
	//Start Remove people Bookmark 
	Drupal.m6connectfav.build_remove_popup_people = function(response) { //alert('ff');//alert(response);
	  ///////////////////////////////////////
	  //Dialog Config
	  var opt = {
		autoOpen: false,
		width: 400,
		modal: true,
		resizable: false
	  };
	  var dd = jQuery("#dialog");
	  //var theDialog = jQuery("#dialog").dialog(opt);
	  var theDialog = dd.dialog(opt);
	  ///////////////////////////////////////
	  //jQuery("#dialog").html(response.html);
	  dd.html(response.html);
	  //theDialog.dialog.html(response.html);
	  //var html = '<div class="">hello</div>';
	  //jQuery("#dialog").html(html);
	  //jQuery("#dialog").html(response);
	  dd.html(response);
	  //theDialog.dialog.html(response);
	  jQuery('.ui-dialog-titlebar').hide();
	  //jQuery('#dialog').dialog('open');
	  theDialog.dialog('open');
	  
	  // Form elements
	  var form_button = jQuery('#ok-delete');
	  var form_cancel_button = jQuery('#cancel-delete');
	  var target_form = form_button.parents("form:first");
	  form_button.click(function() {
		jQuery.ajax({  
		  type: "GET",  
		  //url: response.path,
		  url: form_button.attr('href'),
		  data:  target_form.serialize() + "&js=1",  
		  success: function(data) {
			jQuery.get( '/favorite-content-new-people').done(function( data ) { //// new people change
			   //console.log(data);
			   //jQuery('.left-bookmark-block-data-people',main).replaceWith(data.html); //// new people change //favorite-replaceable-people
			   jQuery('.fav-all-container',main).replaceWith(data.html); //// new people change //favorite-replaceable-people
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
		     });
			//jQuery('#dialog').dialog('close');
			theDialog.dialog('close');
		  },
		  dataType: "json"
		});
		return false;
	  });
	  // Cancel button click event handling
	  form_cancel_button.click(function() {
		//jQuery('#dialog').dialog('close');
		theDialog.dialog('close');
		return false;
	  });    
	}
	//End Remove people Bookmark
	
	//Start Remove node Bookmark 
	Drupal.m6connectfav.build_remove_popup_node = function(response) {
	  jQuery("#dialog").html(response.html);
	  jQuery('.ui-dialog-titlebar').hide();
	  jQuery('#dialog').dialog('open');
	  // Form elements
	  var form_button = jQuery('#'+response.data.button['#attributes'].id);
	  var form_cancel_button = jQuery('#'+response.data.cancel['#attributes'].id);
	  var target_form = form_button.parents("form:first");
	  form_button.click(function() {
		jQuery.ajax({  
		  type: "GET",  
		  url: response.path,
		  data:  target_form.serialize() + "&js=1",  
		  success: function(data) {
			jQuery.get( '/favorite-content-new').done(function( data ) {
			   jQuery('.left-bookmark-block-data',main).replaceWith(data.html); // favorite-replaceable-people
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
		     });
			jQuery('#dialog').dialog('close');
		  },
		  dataType: "json"
		});
		return false;
	  });
	  // Cancel button click event handling
	  form_cancel_button.click(function() {
		jQuery('#dialog').dialog('close');
		return false;
	  });    
	}
	//End Remove node Bookmark
	
	//Start Rename Bookmark 
	Drupal.m6connectfav.build_rename_form = function(response) { 
	  var target_element_li = jQuery('#'+response.target_element_li);
	  // Hide element and add form to dom
	  target_element_li.find('a.bookmark-link').first().hide();
	  target_element_li.find('div.pull-right').first().hide();
      target_element_li.find('a.bookmark-link').first().after(response.html);
      // Form elements
      var form_button = jQuery('#'+response.data.button['#attributes'].id);
	  var form_lable = jQuery('.'+response.data['#attributes'].class +' input[name="label"]');
      var target_form = form_button.parents("form:first");
	  form_button.click(function() {
		jQuery.ajax({  
		  type: "GET",  
		  url: response.path,
		  data:  target_form.serialize() + "&js=1",  
		  success: function(data) {
			jQuery.get( '/favorite-content').done(function( data ) {
			   jQuery('.favorite-replaceable',main).replaceWith(data.html);
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
		    });
		  },
		  dataType: "json"
		});
	    return false;
	  });
	  form_lable.blur(function(){
	    jQuery.ajax({  
		  type: "GET",  
		  url: response.path,
		  data:  target_form.serialize() + "&js=1",  
		  success: function(data) {
			jQuery.get( '/favorite-content').done(function( data ) {
			   jQuery('.favorite-replaceable',main).replaceWith(data.html);
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
		    });
		  },
		  dataType: "json"
		});
	    return false;
	  });
	}
	//End Rename Bookmark
	
	// Dragable Content
	if(Drupal.settings.m6connect_company.company){ //alert('dsr');
	  var main = jQuery("body");
	  
	  //Dialog Config
	  jQuery('#dialog', main).dialog({
		autoOpen: false,
		width: 400,
		modal: true,
		resizable: false
	  });
	  
	  /*jQuery( "div.project-dragable a.cust-proj-title", main ).draggable({
		//revert: "invalid",
		//containment: "document",
		appendTo: "body",
		helper: "clone",
		cursor: "move"
	  });*/
	  
	  jQuery( "div.project-dragable", main ).draggable({
		//revert: "invalid",
		//containment: "document",
		appendTo: "body",
		//helper: "clone",
		opacity:0.9,
		zIndex:9999999,
		cursorAt: {top: 50, left: 50},
		cursor: "move",
		helper: function( event ) {
          var rethtml = jQuery(this).html();
		  if(jQuery(this).find('.company-image img').length){
			rethtml = jQuery(this).find('.company-image').html();			 
		  }else{
			rethtml = jQuery('<i style="width:100px;font-size:100px;z-index:9999999;" class="fa fa-fw fa-building"></i>'); 
		  }
		  return jQuery(rethtml);
        },
		start: function(event, ui){
            jQuery(this).css("z-index", 3000);        
        },
		drag: function(event, ui) {
		    
        },
        stop:function(){
		   
        }
	  });
	  
	  //Dragable in fav Container
	  jQuery( "li.dragable-favorite-container-li a.bookmark-link", main ).draggable({
		appendTo: "body",
		helper: "clone",
		cursor: "move"
	  });
	  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	  //Dropable Content
	  /*jQuery( ".dropable-favorite-folder",main ).droppable({
		accept: "#cust-company-listings .project-dragable .cust-proj-title",
		drop: function( event, ui ) {
		  var dragitem = ui.draggable;
		  var mainitem = dragitem.closest("div.project-box");
		  //mainitem.removeClass('project-dragable').addClass('project-not-dragable');
		  var nid = mainitem.find(".company-nid").text();
		  var folderconentId =0;
		  if(!jQuery(this).hasClass('root-leval')){
		    var folderconentId = jQuery(this).find('.bookmark-folder-id').text();
		  }
		  //return false;
		  jQuery.get( 'drag_drop_company/'+folderconentId+'/'+nid)
			.done(function( data ) {
			   jQuery('.favorite-replaceable',main).replaceWith(data.html);
			   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
			   //alert( "Data Loaded: " + data.html );
		  });
		}
	  });  */
	  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	  
	  //Dropable Bookmark
	  /*jQuery( ".dropable-favorite-folder",main ).droppable({
		accept: "#cust-company-listings .project-dragable .cust-proj-title, li.dragable-favorite-container-li a.bookmark-link",
		activeClass: "ui-state-hover",
        hoverClass: "ui-state-active",
		drop: function( event, ui ) {
		  var dragitem = ui.draggable;
		  //alert(dragitem.attr('class'));
		  if(dragitem.hasClass('cust-proj-title')){
			var mainitem = dragitem.closest("div.project-box");
			var nid = mainitem.find(".company-nid").text();
			var folderconentId =0;
			if(!jQuery(this).hasClass('root-leval')){
			  var drop_li_class = jQuery(this).attr('id');
			  //var folderconentId = drop_li_class.find('.bookmark-folder-id').text();
			  folderconentId = jQuery(this).find('.'+drop_li_class+'_folder').text();
			}
			//alert('nid=> '+nid+'   folderconentId =>'+folderconentId);
			//return false;
			jQuery.get( '/drag_drop_company/'+folderconentId+'/'+nid)
			  .done(function( data ) {
				 jQuery('.favorite-replaceable',main).replaceWith(data.html);
				 Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
			});
			return false;
		  }else if(dragitem.hasClass('bookmark-link')){
			  var mainitem = dragitem.closest("li.dragable-favorite-container-li");
			  var drag_li_class = mainitem.attr('id');
			  var drageconentId = mainitem.find("."+drag_li_class).text();
			  var dragtype = mainitem.find("."+drag_li_class+"_type").text();
			  var dropeconentId =0;
			  var droptype ='';
			  //alert(jQuery(this).attr('class'));
			  if(jQuery(this).hasClass('root-leval')){
				 dropeconentId =0;
				 droptype = 'root'; 
			  }else{
				var drop_li_class = jQuery(this).attr('id');
				dropeconentId = jQuery(this).find('.'+drop_li_class).text();
			    droptype = jQuery(this).find('.'+drop_li_class+'_type').text();  
			  }
			  //alert(dragtype+'=> '+drageconentId+'   '+droptype+' =>'+dropeconentId);
			  //return false;
			  if(drageconentId == dropeconentId){
				return false;  
			  }
			  jQuery.get( '/sort_drag_drop_company/'+drageconentId+'/'+dropeconentId,{ drag: dragtype, drop: droptype })
				.done(function( data ) {
				   jQuery('.favorite-replaceable',main).replaceWith(data.html);
				   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
			  });
			  return false;
		  }
		  return false;
		}
	  });*/
	  //End Dropable Bookmark
	  
	  jQuery( ".dropable-favorite-folder",main ).droppable({
		accept: "#cust-company-listings .project-dragable, li.dragable-favorite-container-li a.bookmark-link",
		activeClass: "ui-state-hover",
        hoverClass: "ui-state-active",
		greedy: true,        
        tolerance: "pointer",
		drop: function( event, ui ) {
		  var dragitem = ui.draggable;
		  //alert(dragitem.attr('class'));
		  if(dragitem.hasClass('project-dragable')){
			var mainitem = dragitem;  //.closest("div.project-box");
			var nid = mainitem.find(".company-nid").text();
			var folderconentId =0;
			var thisLink = mainitem.find('.cust-proj-title');
			if(!jQuery(this).hasClass('root-leval')){
			  var drop_li_class = jQuery(this).attr('id');
			  //var folderconentId = drop_li_class.find('.bookmark-folder-id').text();
			  folderconentId = jQuery(this).find('.'+drop_li_class+'_folder').text();
			}
			//alert('nid=> '+nid+'   folderconentId =>'+folderconentId);
			//return false;
			jQuery.get( '/drag_drop_company/'+folderconentId+'/'+nid)
			  .done(function( data ) {
				 jQuery('.favorite-replaceable',main).replaceWith(data.html);
				 Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
			});
			return false;
		  }else if(dragitem.hasClass('bookmark-link')){
			  var mainitem = dragitem.closest("li.dragable-favorite-container-li");
			  var drag_li_class = mainitem.attr('id');
			  var drageconentId = mainitem.find("."+drag_li_class).text();
			  var dragtype = mainitem.find("."+drag_li_class+"_type").text();
			  var dropeconentId =0;
			  var droptype ='';
			  //alert(jQuery(this).attr('class'));
			  if(jQuery(this).hasClass('root-leval')){
				 dropeconentId =0;
				 droptype = 'root'; 
			  }else{
				var drop_li_class = jQuery(this).attr('id');
				dropeconentId = jQuery(this).find('.'+drop_li_class).text();
			    droptype = jQuery(this).find('.'+drop_li_class+'_type').text();  
			  }
			  //alert(dragtype+'=> '+drageconentId+'   '+droptype+' =>'+dropeconentId);
			  //return false;
			  if(drageconentId == dropeconentId){
				return false;  
			  }
			  jQuery.get( '/sort_drag_drop_company/'+drageconentId+'/'+dropeconentId,{ drag: dragtype, drop: droptype })
				.done(function( data ) {
				   jQuery('.favorite-replaceable',main).replaceWith(data.html);
				   Drupal.attachBehaviors(jQuery('.custom-favorite-container'));
			  });
			  return false;
		  }
		  return false;
		}
	  });
	  
	  if(jQuery( "#invitees-list-favorite-dropable").length){
	  
		jQuery("#invitees-list-favorite-dropable").droppable({
		  accept: "li.dragable-favorite-container-li a.bookmark-link",
		  activeClass: "ui-state-hover",
		  hoverClass: "ui-state-active",
		  greedy: true,        
		  tolerance: "pointer",
		  drop: function( event, ui ) {
		    var temp = [];
		    jQuery('#invitees-list-favorite-dropable .remove-invitees').each(function(index, element) { 
			  var id = jQuery(this).attr('id');
			  if(!isNaN(parseInt(id))){
			    temp.push(id); 
			  } 
		    });
		    var alreadyInvited = temp.join(';');
			var dragitem = ui.draggable;
			var mainitem = dragitem.closest("li.dragable-favorite-container-li");
			var drag_li_class = mainitem.attr('id');
			var drageconentId = mainitem.find("."+drag_li_class).text();
			var dragtype = mainitem.find("."+drag_li_class+"_type").text();
			jQuery.get( '/invite-favorites/'+dragtype+'/'+drageconentId,{alreadyInvited:alreadyInvited}).done(function( data ) {
			   if(data.html){
				 var companies = jQuery('.invitees-list').html();
                 jQuery('.invitees-list').html(companies + data.html);
				 var nodeid = jQuery('.invite_nodeid_hidden').val();
				 var sess_selected_val = jQuery('.invitees-list').html();
				 sessionStorage.setItem("invitelater_" + nodeid, sess_selected_val);
			   }
			   Drupal.attachBehaviors(jQuery('#invitees-list-favorite-dropable'));
			});
			return false;
		  }
		});
	  
	  }
	  
	}
	
	
	
	
	//Add folder
	jQuery('.cust-company-search-form a.action-addfolder', main).click(function() {
	  jQuery.post( jQuery(this).attr("href"), { js: 1})
        .done(function( data ) {
          Drupal.m6connectfav.build_addfolder_popup(data);
      }, "json");
      return false;
    });
	
	//Remove Bookmark
	jQuery(".cust-company-search-form .action-remove", main).click(function() {
	  jQuery.post( jQuery(this).attr("href"), { js: 1})
        .done(function( data ) {
          Drupal.m6connectfav.build_remove_popup(data);
      }, "json");
      return false;
    });
	
    //Rename Bookmark
    jQuery(".cust-company-search-form .action-rename", main).click(function() {
	  var target_li = jQuery(this).closest('li').attr('id');
	  jQuery.post( jQuery(this).attr("href"), { js: 1})
        .done(function( data ) {
		  data.target_element_li = target_li;
          Drupal.m6connectfav.build_rename_form(data);
      }, "json");
      return false;
    });
	
	jQuery(".action-browse", main).click(function(e) {
	  /*e.preventDefault();
	  var target_li = jQuery(this).closest('li').attr('id');
	  var folder_id = jQuery('.'+target_li+'_folder').text();
	  jQuery.post( '/change-company-view-ajax/'+folder_id, { js: 1, favorite: folder_id})
        .done(function( data ) {
		  jQuery('.custom-companies-lists',main).replaceWith(data.html);
		  Drupal.attachBehaviors(jQuery('.custom-companies-lists'));
		  console.log(data);
      }, "json");
	  //alert(folder_id);
      return false;*/
    });
	
	/*jQuery(".show-favorite-checkbox", main).change(function(e) {
	  var checkLink = jQuery('.show-favorite-checkbox-link-query').text();
	  var cuurerntPath = Drupal.settings.m6connect_company.current_path;
	  if(jQuery(this).is(':checked')){
		window.location.href= checkLink; 
	  }else{
		window.location.href='/'+cuurerntPath+checkLink; 
	  }
    });*/
	//.companies-page-favorite .folder-node-list .bookmark-link
	jQuery('.companies-page-favorite .folder-clickable, .companies-page-favorite .folder-node-list').find('a.bookmark-link:first').unbind('click').bind('click',function(e){
	  //e.preventDefault();
	  if(jQuery(".show-favorite-checkbox").is(':checked')){
		var li_element = jQuery(this).closest('li');
		var target_li = li_element.attr('id');
		var folder_id = li_element.hasClass('root-leval-folder')?0:li_element.hasClass('folder-node-list')?jQuery('.'+target_li+'_item').text():jQuery('.'+target_li+'_folder').text();
		//var folder_id= li_element.hasClass('folder-node-list')?jQuery('.'+target_li+'_item').text():jQuery('.'+target_li+'_folder').text();
		jQuery('.company-favorite-folder-id').val(folder_id);
		var cpmpany_uid = '';
		if(li_element.hasClass('share-folder-li')){
			cpmpany_uid = jQuery('.main-container-favorite .sahre-company-uid').text();
		}
		jQuery.post( '/change-company-view/'+folder_id, { js: 1, favorite: folder_id , cpmpany_uid: cpmpany_uid})
		  .done(function( data ) {
			jQuery(data.replacewith,main).replaceWith(data.html);
			jQuery(data.filterreplacewith,main).replaceWith(data.filterHtml);
			Drupal.attachBehaviors(jQuery(data.replacewith));
			
			/*jQuery('.invitees-list').find('.remove-invitees').each(function(index, element) {
	          var removeID = jQuery(this).attr('id');
              jQuery('#cust-company-listings').find('#nid-'+removeID+' a.invite-to-rfp').css('display', 'none');
	          jQuery('#cust-company-listings').find('#nid-'+removeID+' span.added-to-rfp').css('display', 'block');
            });*/
		}, "json");
		/*if(jQuery('div'+jQuery(this).attr('href')).hasClass('in')){
		  //return false;	
		}*/
	  }else{
		jQuery('.company-favorite-folder-id').val(''); 
	  }
	});
	
	jQuery('.non-company-page-favorite .folder-clickable, .non-company-page-favorite .folder-node-list').find('a.bookmark-link:first').unbind('click').bind('click',function(){
	  if(jQuery(".show-favorite-checkbox").is(':checked')){
		var li_element = jQuery(this).closest('li');
		var target_li = li_element.attr('id');
		//var folder_id = jQuery('.'+target_li+'_folder').text();
		var folder_id = li_element.hasClass('root-leval-folder')?0:li_element.hasClass('folder-node-list')?jQuery('.'+target_li+'_item').text():jQuery('.'+target_li+'_folder').text();
		//var folder_id= li_element.hasClass('folder-node-list')?jQuery('.'+target_li+'_item').text():jQuery('.'+target_li+'_folder').text();
		//alert(folder_id);
		jQuery('.company-favorite-folder-id').val(folder_id);
		var cpmpany_uid = '';
		if(li_element.hasClass('share-folder-li')){
			cpmpany_uid = jQuery('.main-container-favorite .sahre-company-uid').text();
		}
		var currentnid = jQuery('.current-node-nid').first().text();
		jQuery.post( '/change-rfp-project-company-view/'+folder_id, { js: 1, favorite: folder_id, nid: currentnid, cpmpany_uid: cpmpany_uid })
		  .done(function( data ) {
			jQuery(data.replacewith,main).replaceWith(data.html);
			jQuery(data.filterreplacewith,main).replaceWith(data.filterHtml);
			Drupal.attachBehaviors(jQuery(data.replacewith));
			
			jQuery('.invitees-list').find('.remove-invitees').each(function(index, element) {
	          var removeID = jQuery(this).attr('id');
              jQuery('#cust-company-listings').find('#nid-'+removeID+' a.invite-to-rfp').css('display', 'none');
	          jQuery('#cust-company-listings').find('#nid-'+removeID+' span.added-to-rfp').css('display', 'block');
            });
		}, "json");
		//return false;	
		/*if(jQuery('div'+jQuery(this).attr('href')).hasClass('in')){
		  //return false;	
		}*/
	  }
	});
	
	// Company page  should be open on same page Start
	/*jQuery('.non-company-page-favorite .folder-node-list .bookmark-link').unbind('click').bind('click',function(){
	  event.preventDefault();	//alert('dsfds');
	  //if(jQuery(".show-favorite-checkbox").is(':checked')){ 
		var li_element = jQuery(this).closest('li');
		var target_li = li_element.attr('id');
		//var folder_id = jQuery('.'+target_li+'_folder').text();
		var nodenid = li_element.find('.bookmark-content-id').text(); //alert(nodenid);
		//jQuery('.company-favorite-folder-id').val(folder_id);
		//var currentnid = jQuery('.current-node-nid').text();
		jQuery.post( '/change-rfp-node-view/'+nodenid, { js: 1 })
		  .done(function( data ) {
			jQuery(data.replacewith,main).html(data.html);
			jQuery(data.filterreplacewith,main).replaceWith(data.filterHtml);
			Drupal.attachBehaviors(jQuery(data.replacewith));
		}, "json");
	  //}
	});*/
	// Company page  should be open on same page End
	
	// SHare Favorite Start
	jQuery(".share-favorite-checkbox").unbind('change').bind('change',function() {
	  var nid = jQuery(this).val();
	  var check = 0;
      if(jQuery(".share-favorite-checkbox").is(':checked')){
		check =1;  
	  }
	  jQuery.post( '/change-share-company-fav/'+nid, { check: check });
    });
	// SHare Favorite End
	
	// SHare Favorite Start
	jQuery(".show-favorite-checkbox").unbind('change').bind('change',function() {
      if(!jQuery(this).is(':checked')){
	    jQuery('.company-favorite-folder-id').val('');
	  }
    });
	// SHare Favorite End
	
	jQuery('.cust-favorite-filter').unbind('click').bind('click',function() {
	  jQuery('.company-favorite-folder-id').val('');
	  jQuery('#cust-company-search-form .co-submit').click();
	  //jQuery(this).remove();	
	});
	
	jQuery('.cust-rfp-favorite-filter').unbind('click').bind('click',function() {
	  jQuery('.company-favorite-folder-id').val('');
	  jQuery('#rfp-company-search-form .co-submit').click();
	  //jQuery(this).remove();	
	});
	
	
	//Remove people Bookmark
	jQuery(".action-remove-people", main).click(function() {
	  jQuery.post( jQuery(this).attr("href"), { js: 1})
        .done(function( data ) {
          Drupal.m6connectfav.build_remove_popup_people(data);
      }, "json");
      return false;
    });
	
	//Remove Bookmark
	jQuery(".action-remove-node", main).click(function() {
	  jQuery.post( jQuery(this).attr("href"), { js: 1})
        .done(function( data ) {
          Drupal.m6connectfav.build_remove_popup_node(data);
      }, "json");
      return false;
    });
  }
  //end Attach
};

Drupal.behaviors.m6connect_companies_bookmark = {
  attach:function(){
	
	jQuery(".bookmarkorganizer-index-table tr.folder a.action-remove").attr('title','Remove folder');
	jQuery(".bookmarkorganizer-index-table tr.folder a.action-rename").attr('title','Rename folder'); 
	
  }
}