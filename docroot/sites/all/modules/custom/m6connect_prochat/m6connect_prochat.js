var socket = '';
var conn = '';
var yourConn = '';
var name;
var connectedUser;
var localVideo;
var localVideo1;
var remoteVideo;
var remoteVideo1;
var stream;

function typetoggle(option) {
    jQuery(".list-group-" + option).toggle();
    if (jQuery(".list-group-" + option).css("display").toLowerCase() == "none") {
        jQuery(".typetoggle-" + option).html('<i class="fa fa-plus"></i>');
    } else {
        jQuery(".typetoggle-" + option).html('<i class="fa fa-minus"></i>');
    }
}

function getGroupMember(gid, gname, username) {
    var groupdetailjson = {
        "group_id": gid,
        "group_name": gname
    };
    var sessionGroup = { "togroupid": gid, "togroupname": gname };
    sessionStorage.setItem('chatdata', JSON.stringify(sessionGroup));
    socket.emit("getgroupusersdetails", JSON.stringify(groupdetailjson), function(result) {
        var memberData = JSON.parse(result);
        var mdata = '';
        var parseRes = '';
        var mainMemArr = [];
        mdata += '<div id="prochat-group-user-list"><hr>';
        mdata += '<h3 class="dashboard-block-account margin-top-10 text-center">' + gname + ' Member </h3>';
        mdata += '<ul class="list-group margin-top-10">';
        if (mainMemArr) {
            Object.keys(memberData).map(function(objectKey) {
                var value = memberData[objectKey];
                if (username !== value['username']) {
                    var userfulldata = value['username'].split("@");
                    var realname = userfulldata[0] + ' ' + userfulldata[1];
                    mdata += '<li class="list-group-item get-user-popup" data-realname="' + realname + '" data-id="' + userfulldata[2] + '" data-name="' + value['username'] + '" style="cursor:pointer;">';
                    if (value['onlinestatus'] == 'Yes') {
                        mdata += '<span class="prochat-loggedin"></span>' + realname;
                    } else {
                        mdata += '<span class="prochat-loggedout"></span>' + realname;
                    }
                    mdata += '</li>';
                }
            });
            mdata += '</ul></div>';
        } else {
            mdata = 'No member found';
        }
        $("#prochat-group-user-list").html(mdata);
    });
}

(function($) {
    Drupal.behaviors.m6connect_prochat = {
        attach: function(context, settings) {
            /*$('.get-user-popup').unbind('click').bind('click', function(event){
            console.log("hello");
                $("#dashboard-share-panel").removeClass("col-md-6");
                $("#dashboard-share-panel").addClass("col-md-3 span-share");
                $("#dashboard-chating-panel").show();
            //$('.single-window-chat').show();
            $('.usr-name').text($(this).text());
            $('.chat-user-name').val($(this).attr('data-name'));                
            });*/
            /*$('.single-window-chat .close').unbind('click').bind('click', function(event){
                $("#dashboard-share-panel").removeClass("col-md-3 span-share");
                $("#dashboard-share-panel").addClass("col-md-6");
                $("#dashboard-chating-panel").hide();
            //$('.single-window-chat').hide();
            });*/
            /*$('.addon-sp').unbind('click').bind('click', function(event){
            var getMsg = $('.input-sp').val();
            var getUsername = $('.chat-user-name').val();
            //var socket = io('http://52.24.154.41:8080');              
            msgval(getUsername, getMsg);
            function msgval(toname, data_msg){
              socket.emit('sendmessage', toname, data_msg);
              $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-info">').text(data_msg));
              $('.input-sp').val('');
            }
            });*/
        }
    };
    $(document).ready(function() {
        // remove all session storage on load
        sessionStorage.removeItem('chatdata');
        sessionStorage.removeItem('currUser');
        // get loggedin user username define in prochat init hook
        var username = Drupal.settings.m6connect_prochat.username;
        var prochatCompanyId = Drupal.settings.m6connect_prochat.prochatCompanyId;
        //socket = io.connect('http://ec2-52-42-181-7.us-west-2.compute.amazonaws.com:8084',{query: 'name='+username});
        // aws connection       
        //socket = io.connect('http://ec2-52-42-181-7.us-west-2.compute.amazonaws.com:8084');
        socket = io.connect('https://www.m6cliq.info');
        // connection for audio and video
        conn = io("https://www.m6cliq.info");

        var myobj = { "username": username };
        socket.emit("usernamesubmit", JSON.stringify(myobj)); // connection with username on aws
        // for audio call
        var userval = { "name": username[0] };
        console.log(JSON.stringify(userval));

        conn.emit("connectionsetup", JSON.stringify(userval));
        var configuration = {
            'iceServers': [
                { url: 'stun:stun.l.google.com:19302' },

                {
                    url: 'turn:35.167.177.200:3478',
                    credential: 'test',
                    username: 'test'
                }
            ]
        };
        yourConn = new RTCPeerConnection(configuration);
        localVideo = document.querySelector('#localVideo');
        remoteVideo = document.querySelector('#remoteVideo');


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

        $('.border-box').hide();
        // receive message globally
        socket.on('message', function(msg, time) {
            var newmsg = msg.replace(/["']/g, "");
            if (time) {
                var chatTime = new Date(time).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
                newmsg = newmsg + '  <span class="chatTime">' + chatTime + '</span>';
            }
            $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-success text-right">').html(newmsg));
            $('.user-messages').scrollTop($('.user-messages')[0].scrollHeight);
        });
        $(document).on('click', ".go-pro-chat", function() {
            $(".border-box").toggle();
        });
        // get and print group listing
        socket.emit('getgroupdetails', username, function(result) {
            if (result) {
                groupData = JSON.parse(result);
                console.log(groupData);
                var output = '';
                var filteredGroupData = [];
                Object.keys(groupData).map(function(objectKey, index) {
                    var value = groupData[objectKey];
                    if (!filteredGroupData[value['grouptype']]) {
                        filteredGroupData[value['grouptype']] = [];
                        filteredGroupData[value['grouptype']].push({ 'gid': value['groupid'], 'name': value['groupname'] });
                    } else {
                        filteredGroupData[value['grouptype']].push({ 'gid': value['groupid'], 'name': value['groupname'] });
                    }
                });
                Object.keys(filteredGroupData).map(function(objectKey) {
                    output += '<h3 class="dashboard-block-account margin-top-10 text-center">' + objectKey + ' Type Group List';
                    output += '<span class="pull-right typetoggle-' + objectKey + '" style="cursor:pointer;" onclick="typetoggle(\'' + objectKey + '\')">';
                    output += '<i class="fa fa-plus"></i></span><h3>';
                    output += '<ul class="list-group list-group-' + objectKey + '" style="display:none;">';
                    Object.keys(filteredGroupData[objectKey]).map(function(groupdata, index) {
                        if (groupdata) {
                            output += '<li class="list-group-item">';
                            output += '<a onclick="getGroupMember(' + filteredGroupData[objectKey][groupdata]['gid'] + ', \'' + filteredGroupData[objectKey][groupdata]['name'] + '\', \'' + username[0] + '\')" style="cursor: pointer;font-size: 15px;color: #0f75bc;">';
                            output += filteredGroupData[objectKey][groupdata]['name'] + '</a>';
                            output += '</li>';
                        }
                    });
                    output += '</ul>';
                });
                $("#prochatgrouplisting").html(output);
            }
        });

        // function for save group and it's member
        Drupal.ajax.prototype.commands.after_form_js = function(ajax, response, status) {
            var form_state = Drupal.settings.addGroupData[0];
            var groupjson = {
                "group_name": form_state.group_name,
                "group_parent": form_state.parent_group,
                "group_companyid": form_state.cid,
                "group_type": form_state.group_type,
                "group_author": username[0]
            };
            socket.emit('groupdetail', JSON.stringify(groupjson), function(response) {
                //console.log(response);
                var gUser = form_state.group_user;
                var gusername = [];
                var i = 0;
                Object.keys(gUser).forEach(function(key) {
                    gusername[i] = key;
                    i++;
                });
                var groupuserjson = {
                    "group_id": response,
                    "group_name": form_state.group_name,
                    "friend_username": gusername,
                    "group_companyid": form_state.cid,
                };
                socket.emit('addfriendtoagroup', JSON.stringify(groupuserjson), function(result) {
                    if (result == 1) {
                        location.reload();
                    }
                });
            });
        };
        // function for open chat window
        $(document).on('click', ".get-user-popup", function() {
            $("#dashboard-share-panel").removeClass("col-md-6");
            $("#dashboard-share-panel").addClass("col-md-3 span-share");
            $("#dashboard-chating-panel").show();
            //$('.single-window-chat').show();                      
            var schatdata = JSON.parse(sessionStorage.getItem('chatdata'));
            var openChat = $(this).attr('data-name');
            var usrDataId = $(this).attr('data-id');
            var userDataRealName = $(this).attr('data-realname');
            var siteUrl = Drupal.settings.m6connect_prochat.base_url + Drupal.settings.basePath;
            var userProfile = siteUrl + 'user' + Drupal.settings.basePath + usrDataId;
            var chatUserHtml = '<a href="' + userProfile + '" target="_blank">' + userDataRealName + '</a>';
            $('.usr-name').html(chatUserHtml);
            console.log(openChat);
            if (sessionStorage.currUser) {
                if (openChat !== sessionStorage.currUser) {
                    $('.user-msg-input #messages span').remove();
                    sessionStorage.setItem("currUser", openChat);
                    var getMessage = {
                        "fromusername": username[0],
                        "tousername": openChat,
                        "groupid": schatdata.togroupid,
                        "lastchatid": 0
                    }
                    socket.emit("sendingmessgaelist", JSON.stringify(getMessage), function(rescall) {
                        var fullChatMsg = JSON.parse(rescall);
                        var revFullChatMsg = $(fullChatMsg).toArray().reverse();
                        Object.keys(revFullChatMsg).map(function(objectKey) {
                            var fullChatData = revFullChatMsg[objectKey];
                            fullChatMsg = fullChatData.message;
                            msgChatId = fullChatData.chatid;
                            if (fullChatData.deliveredtime) {
                                var chatTime = new Date(fullChatData.deliveredtime).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
                                if (fullChatData.isfile == 1) {
                                    var re = /(?:\.([^.]+))?$/;
                                    var ext = re.exec(fullChatMsg);
                                    var fileExt = ext[1].toLowerCase();
                                    /*if(fullChatMsg.indexOf("@$$@") > -1){
                                        var filenamesplit = fullChatMsg.split("@$$@");
                                        var filename = filenamesplit[1];
                                    }*/
                                    if (fileExt == 'jpg' || fileExt == 'png' || fileExt == 'gif') {
                                        //fullChatMsg = '<span class="filechat" id="chatFileImage" data-src="'+fullChatMsg+'" data-toggle="modal" data-target="#myModal"><img id="chatFileImage" src="'+fullChatMsg+'" style="height:100px; width:100px;" /></span>';
                                        fullChatMsg = '<span class="filechat" id="chatFileImage-' + msgChatId + '" data-src="' + fullChatMsg + '"><embed id="chatFileImage" src="' + fullChatMsg + '" style="height:100px; width:100px;" /></span>';
                                    }
                                    if (fileExt == 'pdf') {
                                        fullChatMsg = '<a class="filechatpdf" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-pdf-o fa-3x" aria-hidden="true"></i></a>';
                                    }
                                    if (fileExt == 'xlsx') {
                                        fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-excel-o fa-3x" aria-hidden="true"></i></a>';
                                    }
                                    if (fileExt == 'docx') {
                                        fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-word-o fa-3x" aria-hidden="true"></i></a>';
                                    }
                                    if (fileExt == 'txt') {
                                        fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-text-o fa-3x" aria-hidden="true"></i></a>';
                                    }
                                    fullChatMsg += '<br/><span class="chatTime">' + chatTime + '</span>';
                                } else {
                                    fullChatMsg = fullChatMsg + '  <span class="chatTime">' + chatTime + '</span>';
                                }
                            }
                            if (fullChatData.fromusername == username[0]) {
                                $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-info">').html(fullChatMsg));
                            } else {
                                $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-success text-right">').html(fullChatMsg));
                            }
                        });
                        $('.user-messages').scrollTop($('.user-messages')[0].scrollHeight);
                    });
                }
            } else {
                sessionStorage.setItem("currUser", openChat);
                var getMessage = {
                        "fromusername": username[0],
                        "tousername": openChat,
                        "groupid": schatdata.togroupid,
                        "lastchatid": 0
                    }
                    //console.log(getMessage);
                socket.emit("sendingmessgaelist", JSON.stringify(getMessage), function(rescall) {
                    var fullChatMsg = JSON.parse(rescall);
                    var revFullChatMsg = $(fullChatMsg).toArray().reverse();
                    Object.keys(revFullChatMsg).map(function(objectKey) {
                        var fullChatData = revFullChatMsg[objectKey];
                        //console.log(fullChatData);
                        fullChatMsg = fullChatData.message;
                        msgChatId = fullChatData.chatid;
                        if (fullChatData.deliveredtime) {
                            var chatTime = new Date(fullChatData.deliveredtime).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
                            if (fullChatData.isfile == 1) {
                                var re = /(?:\.([^.]+))?$/;
                                var ext = re.exec(fullChatMsg);
                                var fileExt = ext[1].toLowerCase();
                                /*if(fullChatMsg.indexOf("@$$@") > -1){
                                    var filenamesplit = fullChatMsg.split("@$$@");
                                    var filename = filenamesplit[1];
                                }*/
                                if (fileExt == 'jpg' || fileExt == 'png' || fileExt == 'gif') {
                                    //fullChatMsg = '<span class="filechat" id="chatFileImage" data-src="'+fullChatMsg+'" data-toggle="modal" data-target="#myModal"><img id="chatFileImage" src="'+fullChatMsg+'" style="height:100px; width:100px;" /></span>';
                                    fullChatMsg = '<span class="filechat" id="chatFileImage-' + msgChatId + '" data-src="' + fullChatMsg + '"><embed id="chatFileImage" src="' + fullChatMsg + '" style="height:100px; width:100px;" /></span>';
                                }
                                if (fileExt == 'pdf') {
                                    fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-pdf-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                if (fileExt == 'xlsx') {
                                    fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-excel-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                if (fileExt == 'docx') {
                                    fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-word-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                if (fileExt == 'txt') {
                                    fullChatMsg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + fullChatMsg + '"><i class="fa fa-file-text-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                fullChatMsg += '<br/><span class="chatTime">' + chatTime + '</span>';
                            } else {
                                fullChatMsg = fullChatMsg + '  <span class="chatTime">' + chatTime + '</span>';
                            }
                        }
                        if (fullChatData.fromusername == username[0]) {
                            $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-info">').html(fullChatMsg));
                        } else {
                            $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-success text-right">').html(fullChatMsg));
                        }
                    });
                    $('.user-messages').scrollTop($('.user-messages')[0].scrollHeight);
                });
            }
            $('.chat-user-name').val($(this).attr('data-name'));
        });
        // function for close chat window
        $(document).on('click', ".single-window-chat .close", function() {
            $("#dashboard-share-panel").removeClass("col-md-3 span-share");
            $("#dashboard-share-panel").addClass("col-md-6");
            $("#dashboard-chating-panel").hide();
            //$('.single-window-chat').hide();
        });
        $(document).on('keypress', ".input-sp", function(e) {
            var key = e.which;
            if (key == 13) {
                $(".addon-sp").click();
                return false;
            }
        });
        // function for send chat on click on send button
        $(document).on('click', ".addon-sp", function() {
            var getMsg = $('.emojionearea-editor').html();
            var getUsername = $('.chat-user-name').val();
            if (getMsg) {
                msgval(getUsername, getMsg);
            }
        });

        function msgval(toname, data_msg) {
            var chatdata = JSON.parse(sessionStorage.getItem('chatdata'));
            var chatfineldata = { 'togroupid': chatdata.togroupid, 'togroupname': chatdata.togroupname, 'fromusername': username[0], 'tousername': toname, 'message': data_msg, 'isfile': 0 };
            socket.emit('sendmessage', JSON.stringify(chatfineldata), function(data) {
                //console.log(data);
                var chatTime = new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
                data_msg = data_msg + '  <span class="chatTime">' + chatTime + '</span>';
                $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-info">').html(data_msg));
                //$('.input-sp').html('');
                $('.emojionearea-editor').html('');
                $('.user-messages').scrollTop($('.user-messages')[0].scrollHeight);
            });
        }
        // user is typing script
        var typingTimer; //timer identifier
        var doneTypingInterval = 2000; //time in ms, 5 second for example
        //on keyup, start the countdown
        $(document).on('keyup', ".input-sp", function(e) {
            clearTimeout(typingTimer);
            var getUsername = $('.chat-user-name').val();
            detailfortyping = {
                'fromusername': username[0],
                'tousername': getUsername,
                'status': 1
            }
            socket.emit("typingstatus", JSON.stringify(detailfortyping));
            typingTimer = setTimeout(doneTyping, doneTypingInterval);
        });
        //on keydown, clear the countdown 
        $(document).on('keydown', ".input-sp", function(e) {
            clearTimeout(typingTimer);
            var getUsername = $('.chat-user-name').val();
            detailfortyping = {
                'fromusername': username[0],
                'tousername': getUsername,
                'status': 1
            }
            socket.emit("typingstatus", JSON.stringify(detailfortyping));
            typingTimer = setTimeout(doneTyping, doneTypingInterval);
        });
        //user is "finished typing," do something
        function doneTyping() {
            var getUsername = $('.chat-user-name').val();
            detailfortyping = {
                'fromusername': username[0],
                'tousername': getUsername,
                'status': 0
            }
            socket.emit("typingstatus", JSON.stringify(detailfortyping));
        }
        // get response from server that user is typing or not
        socket.on("checktypingstatus", function(status) {
            var getUsername = $('.chat-user-name').val();
            var userfulldata = getUsername.split("@");
            var realname = userfulldata[0] + ' ' + userfulldata[1];
            if (status == 1) {
                $(".userType").html(realname + ' is typing');
            } else {
                $(".userType").html('');
            }
        });
        // attachment functionality starts
        $(document).on('click', '.emojionearea-button-upload', function(e) {
            $("#fileattachment").trigger("click");
            $('.progress').show();
            $('.progress-bar').text('0%');
            $('.progress-bar').width('0%');
        });
        $(document).on('change', '#fileattachment', function(e) {
            var files = $(this)[0].files;
            if (files.length > 0) {
                // create a FormData object which will be sent as the data payload in the
                // AJAX request
                var formData = new FormData();
                // loop through all the selected files and add them to the formData object
                for (var i = 0; i < files.length; i++) {
                    var file = files[i];
                    // add the files to formData object for the data payload
                    formData.append('uploads[]', file, file.name);
                }
                $.ajax({
                    url: 'https://www.m6cliq.info/upload',
                    type: 'POST',
                    data: formData,
                    processData: false,
                    contentType: false,
                    success: function(imageData) {
                        console.log('upload successful!\n' + imageData);
                        if (imageData) {
                            var toname = $('.chat-user-name').val();
                            var chatdata = JSON.parse(sessionStorage.getItem('chatdata'));
                            var chatfineldata = { 'togroupid': chatdata.togroupid, 'togroupname': chatdata.togroupname, 'fromusername': username[0], 'tousername': toname, 'message': imageData, 'isfile': 1 };
                            socket.emit('sendmessage', JSON.stringify(chatfineldata), function(data) {
                                var chatTime = new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });
                                //data_msg = '<a href="'+imageData+'"><img src="'+imageData+'"></a>';
                                var re = /(?:\.([^.]+))?$/;
                                var ext = re.exec(imageData);
                                var fileExt = ext[1].toLowerCase();
                                if (fileExt == 'jpg' || fileExt == 'png' || fileExt == 'gif') {
                                    //fullChatMsg = '<span class="filechat" id="chatFileImage" data-src="'+fullChatMsg+'" data-toggle="modal" data-target="#myModal"><img id="chatFileImage" src="'+fullChatMsg+'" style="height:100px; width:100px;" /></span>';
                                    data_msg = '<span class="filechat" id="chatFileImage-' + msgChatId + '" data-src="' + imageData + '"><embed id="chatFileImage" src="' + imageData + '" style="height:100px; width:100px;" /></span>';
                                }
                                if (fileExt == 'pdf') {
                                    data_msg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + imageData + '"><i class="fa fa-file-pdf-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                if (fileExt == 'xlsx') {
                                    data_msg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + imageData + '"><i class="fa fa-file-excel-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                if (fileExt == 'docx') {
                                    data_msg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + imageData + '"><i class="fa fa-file-word-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                if (fileExt == 'txt') {
                                    data_msg = '<a class="filechatfile" id="chatFileImage-' + msgChatId + '" href="' + imageData + '"><i class="fa fa-file-text-o fa-3x" aria-hidden="true"></i></a>';
                                }
                                data_msg += '<br/><span class="chatTime">' + chatTime + '</span>';
                                $('.user-msg-input #messages').append($('<span class="list-group-item list-group-item-info">').html(data_msg));
                                $('.emojionearea-editor').html('');
                                $('.user-messages').scrollTop($('.user-messages')[0].scrollHeight);
                            });
                        }
                    },
                    xhr: function() {
                        var xhr = new XMLHttpRequest();
                        xhr.upload.addEventListener('progress', function(evt) {
                            if (evt.lengthComputable) {
                                var percentComplete = evt.loaded / evt.total;
                                percentComplete = parseInt(percentComplete * 100);
                                $('.progress-bar').text(percentComplete + '%');
                                $('.progress-bar').width(percentComplete + '%');
                                if (percentComplete === 100) {
                                    $('.progress-bar').html('Done');
                                    setTimeout(function() {
                                        $('.progress').hide();
                                    }, 2000);
                                }
                            }
                        }, false);
                        return xhr;
                    }
                });
            }
        });
        // show attachment in model popup
        $(document).on('click', '.filechat', function(e) {
            var attachData = $(this).attr("data-src");
            $("#single_image").html('<img id="openchatfiles" src="' + attachData + '" height="705" width="865">');
            $("#single_image").trigger("click");
        });


        // create new group popup functionality starts
        $(document).on('change', '.grouptypelisting', function(e) {
            var jsondata = {
                "companyid": prochatCompanyId[0],
                "grouptype": this.value,
                "username": username[0]
            }
            socket.emit('groupacctogrouptype', JSON.stringify(jsondata), function(result) {
                var typegroupdata = JSON.parse(result);
                var typeselectlist = '<option value="0">Select parent group</option>';
                Object.keys(typegroupdata).map(function(objectKey) {
                    var value = typegroupdata[objectKey];
                    if (value) {
                        typeselectlist += '<option value="' + value['groupid'] + '">' + value['groupname'] + '</option>';
                    }
                });
                $("#parent-group-list select").html(typeselectlist);
            });
        });

        /************** script for audio call ***************/
        /*$(document).on("click", ".audio-call", function(){
            var name;var connectedUser;         
            var getUsername = $('.chat-user-name').val();           
            if (username[0].length > 0) {
                send({
                    type: "login",
                    name: username[0]
                });
            }
        });*/
        function send(message) {
            //attach the other peer username to our messages 
            if (connectedUser) {
                message.name = connectedUser;
            }
            conn.emit('message', JSON.stringify(message));
            //   conn.send(JSON.stringify(message)); 
        };
        conn.on("tuning", function(msg) {
            // console.log("Got message", msg.data);
            var data = JSON.parse(msg);
            console.log(data);
            switch (data.type) {
                case "login":
                    console.log("hello test");
                    handleLogin(data.success);
                    break;
                    //when somebody wants to call us 
                case "offer":
                    prepareCall();

                    yourConn.setRemoteDescription(new RTCSessionDescription(data.offer));

                    handleOffer(data.offer, data.toname, data.fromname);
                    // yourConn.setRemoteDescription(new RTCSessionDescription(data.offer));

                    break;
                case "answer":
                    handleAnswer(data.answer);

                    break;
                    //when a remote peer sends an ice candidate to us 
                case "candidate":
                    handleCandidate(data.candidate);
                    break;
                case "leave":
                    handleLeave();
                    break;
                default:
                    break;
            }
        });
        var callBtn = document.querySelector("#callBtn");
        var navigator = window.navigator;
        navigator.getMedia = (navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia);

        function handleLogin(success) {

            if (success === false) {
                alert("Ooops...try a different username");
            } else {


                var callToUsername = $('.chat-user-name').val();
                console.log("clicked on callbutton:-");
                if (callToUsername.length > 0) {
                    connectedUser = callToUsername;
                    var fuser = username[0].split("@");
                    var fusername = fuser[0] + ' ' + fuser[1];
                    var touser = connectedUser.split("@");
                    var tousername = touser[0] + ' ' + touser[1];
                    $(".callfromCall").html(fusername);
                    $(".calltoCall").html(tousername);
                    $('.audio-call-window').show();
                    $('#callWindow').show();

                    initiateCall();

                    console.log("333");
                    console.log(yourConn);


                    // create an offer 

                } else {

                    console.log("handle login not possible");
                }

            }
        };

        //initiating a call 
        callBtn.addEventListener("click", function() {
            // initialize audio call object
            handleLogin(true);
        });
        $(document).on("click", ".disconnectBtn", function() {
            console.log("Call disconnect");
            localVideo.src = "";
            remoteVideo.src = "";

            send({
                type: "leave"
            });


            // handleLeave();
            //$("#callWindow").dialog("close");
        });
        //when somebody sends us an offer 
        function handleOffer(offer, toname, fromname) {
            /*localVideo = document.querySelector('#localVideo');
            remoteVideo = document.querySelector('#remoteVideo');*/
            alert("hey" + toname + "///" + fromname);
            connectedUser = fromname;
            if (toname == username[0]) {
                // remoteVideo.src = null;
                // localVideo.src = null;



                var fuser = fromname.split("@");
                var fusername = fuser[0] + ' ' + fuser[1];
                var touser = toname.split("@");
                var tousername = touser[0] + ' ' + touser[1];
                $(".fromCall").html(fusername);
                $(".toCall").html(tousername);
                $(".audio-call-window").show();
                $('#callWindow').show();

            }
        };



        $(document).on("click", ".acceptBtn", function() {

            answerCall();


        });
        //when we got an answer from a remote user
        function handleAnswer(answer) {
            console.log("got answer:-");
            console.log(answer);
            yourConn.setRemoteDescription(new RTCSessionDescription(answer));



        };

        //when we got an ice candidate from a remote user 
        function handleCandidate(candidate) {
            console.log("ice candidate:-");
            console.log(candidate +
                yourConn);
            yourConn.addIceCandidate(new RTCIceCandidate(candidate));
        };
        //hang up 
        /*hangUpBtn.addEventListener("click", function() {
            send({
                type: "leave"
            });
            handleLeave();
        });*/
        function handleLeave() {

            if (yourConn) {
                console.log("inside leave");
                yourConn.close();
                // localVideo.src = "";
                // remoteVideo.src = "";

            } else {
                console.log("outside leave");

            }
        };



        ///here we start again to code./......
        function prepareCall() {
            // yourConn = new RTCPeerConnection(configuration);
            yourConn.onicecandidate = onIceCandidateHandler;
            yourConn.onaddstream = onAddStreamHandler;
        };

        function onIceCandidateHandler(evt) {
            if (!evt || !evt.candidate) return;
            send({
                type: "candidate",
                candidate: event.candidate
            });
        };

        function onAddStreamHandler(evt) {
            remoteVideo.src = URL.createObjectURL(evt.stream);
        };

        function initiateCall() {
            prepareCall();
            navigator.getUserMedia({ "audio": true, "video": true }, function(stream) {
                localVideo.src = URL.createObjectURL(stream);
                yourConn.addStream(stream);
                createAndSendOffer();
            }, function(error) { console.log(error); });
        };

        function createAndSendOffer() {
            yourConn.createOffer(
                function(offer) {
                    var off = new RTCSessionDescription(offer);
                    yourConn.setLocalDescription(new RTCSessionDescription(off),
                        function() {
                            //wsc.send(JSON.stringify({ "sdp": off }));
                            send({
                                type: "offer",
                                offer: off
                            });

                        },
                        function(error) {
                            console.log(error);
                        }
                    );
                },
                function(error) {
                    console.log(error);
                }, { 'iceRestart': true }
            );
        };

        function answerCall() {
            // prepareCall();
            // get the local stream, show it in the local video element and send it
            navigator.getUserMedia({ "audio": true, "video": true }, function(stream) {



                localVideo.src = URL.createObjectURL(stream);
                yourConn.addStream(stream);
                createAndSendAnswer();
                // yourConn.setRemoteDescription(new RTCSessionDescription(offer));

            }, function(error) { console.log(error); });
        };

        function createAndSendAnswer() {
            yourConn.createAnswer(
                function(answer) {
                    var ans = new RTCSessionDescription(answer);
                    yourConn.setLocalDescription(ans, function() {
                            // wsc.send(JSON.stringify({ "sdp": ans }));
                            send({
                                type: "answer",
                                answer: ans
                            });
                        },
                        function(error) {
                            console.log(error);
                        }
                    );
                },
                function(error) {
                    console.log(error);
                }
            );
        }
    });
}(jQuery));