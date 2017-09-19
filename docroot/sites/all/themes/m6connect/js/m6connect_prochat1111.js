var socket = '';
function typetoggle(option){
	jQuery(".list-group-"+option).toggle();
	if(jQuery(".list-group-"+option).css("display").toLowerCase() == "none"){  		
  		jQuery(".typetoggle-"+option).html('<i class="fa fa-plus"></i>');
  	}
  	else{
  		jQuery(".typetoggle-"+option).html('<i class="fa fa-minus"></i>');
  	}
}

(function ($) {
	Drupal.behaviors.m6connect_prochat = {
    attach: function (context, settings) {
    	$('.get-user-popup').unbind('click').bind('click', function(event){	      		
    		$("#dashboard-share-panel").removeClass("col-md-6");
    		$("#dashboard-share-panel").addClass("col-md-3 small-share");
    		$("#dashboard-chating-panel").show();
        //$('.single-window-chat').show();
        $('.usr-name').text($(this).text());
        $('.chat-user-name').val($(this).attr('data-name'));		        
    	});
    	$('.single-window-chat .close').unbind('click').bind('click', function(event){
    		$("#dashboard-share-panel").removeClass("col-md-3 small-share");
    		$("#dashboard-share-panel").addClass("col-md-6");
    		$("#dashboard-chating-panel").hide();
      	//$('.single-window-chat').hide();
    	});
    	$('.addon-sp').unbind('click').bind('click', function(event){
        var getMsg = $('.input-sp').val();
        var getUsername = $('.chat-user-name').val();
        //var socket = io('http://52.24.154.41:8080');		        
        /*msgval(getUsername, getMsg);
        function msgval(toname, data_msg){
          socket.emit('sendmessage', toname, data_msg);
          $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-info">').text(data_msg));
          $('.input-sp').val('');
        }*/
    	});
    }
	};
	$(document).ready(function () {
		// get loggedin user username define in prochat init hook
		var username = Drupal.settings.m6connect_prochat.username;	
		//socket = io.connect('http://ec2-52-42-181-7.us-west-2.compute.amazonaws.com:8084',{query: 'name='+username});
		// aws connection  		
		socket = io.connect('http://ec2-52-42-181-7.us-west-2.compute.amazonaws.com:8084');
  	var myobj = {"username":username};
  	socket.emit("usernamesubmit", JSON.stringify(myobj)); // connection with username on aws
  	// check user connection on aws
  	/*socket.on('connectionstatus' , function(msg){
			if(msg == "0"){
				alert("username already exists or some internally problems arise");
			}
			else{
				var myobj = {"username":username};
				sessionStorage.setItem('uname', JSON.stringify(myobj));			
		    }
		});*/
    socket.emit('getgroupdetails' , username, function (result){
      if(result){
        var output = '';
        output += '<ul class="list-group list-group">';
        /*$.each(result, function(index, value) {
          console.log(index);
          //console.log(value);
        });*/

        output += '</ul>';
        console.log(JSON.parse(result));
      }          
    });
  	$('.border-box').hide();
  	socket.on('message', function(msg){
    	$('.user-msg-input #messages').append($('<span>').text(msg));
    	$('.input-sp').val('');
    });
    $(document).on('click', ".go-pro-chat", function() {  	    	
    	$(".border-box").toggle();
	  });
		Drupal.ajax.prototype.commands.after_form_js = function(ajax, response, status) {
	    var form_state = Drupal.settings.addGroupData[0];
	    var groupjson = {  				
  			"group_name" : form_state.group_name,
  			"group_parent": form_state.parent_group,
  			"group_companyid": form_state.cid,
  			"group_type": form_state.group_type,
  			"group_author" : username[0]
  		};  			
  		socket.emit('groupdetail' , JSON.stringify(groupjson), function(response){
  			//console.log(response);
  			var gUser = form_state.group_user;
  	    var gusername = [];var i = 0;
  			Object.keys(gUser).forEach(function(key) {
  				gusername[i] = key;i++;
  			});
  			var groupuserjson = {
  				"group_id" : response,
  				"group_name" : form_state.group_name,
  				"friend_username": gusername,
  				"group_companyid": form_state.cid,
  			};	  			
  			socket.emit('addfriendtoagroup' , JSON.stringify(groupuserjson) , function (result){
        	console.log(result);
        });
  		});
		};
	});
}(jQuery));