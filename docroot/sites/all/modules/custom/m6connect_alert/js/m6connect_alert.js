jQuery(document).ready(function() {
    var flag = 0;
    var text_max = 160; 
    var edit_template_div = 0;      
    jQuery('#message-feedback').html(text_max + ' characters remaining');
    jQuery('.message-textarea-box').keyup(function() {
        var text_length = jQuery('.message-textarea-box').val().length;     
        var text_remaining = text_max - text_length;
        jQuery('#message-feedback').html(text_remaining + ' characters remaining');     
        edit_template_div = jQuery(".message-box-div").length;
        if(edit_template_div < 2){
            if(text_remaining == 0)
            { 
                if(flag == 0){              
                    clonee();
                    flag = 1;
                }           
            }
        }        
    });
    // edit template popup code
    var edit_temp_msg = jQuery("#alert_add_new_template_main_container .message-textarea-box").val();
    if(edit_temp_msg){
        var numChunks = Math.ceil(edit_temp_msg.length / 160);
        var subMsg = 0;var msg = '';var onetimeflag = 0;var cloneIndex = '';var cloneDiv = '';text_max = 160;
        for(var i=1, j=0; i <= numChunks; i++){
            subMsg = 160;
            msg = edit_temp_msg.substr(j, subMsg);        
            j = subMsg*i+1;        
            newLeangth = text_max - msg.length;
            if(onetimeflag == 0){
                jQuery("#alert_add_new_template_main_container .message-textarea-box").val(msg);
                jQuery("#message-feedback").html(newLeangth + ' characters remaining');
                onetimeflag = 1;                
            }
            else{                 
                 editClonee(msg, newLeangth);
            }
        }
    }

    jQuery(".alert-upload-image").change(function(){
        jQuery(".alert-remove-image").css('display', 'inline-block');
    });    

    jQuery(".alert-remove-image").click(function(){
        jQuery(".alert-upload-image").val('');
        jQuery(".alert-remove-image").css('display', 'none');
    });
});

function clonee(){
    var cloneIndex = jQuery(".message-box-div").length;    
	var cloneDiv = jQuery("#message-textarea-box-div").clone();

    cloneDiv.attr("id", "message-textarea-box-div" +  cloneIndex)   
    .insertAfter(jQuery('[id^=message-textarea-box-div]:last')); 

    cloneDiv.find("textarea").attr('id', "message-textarea-box"+cloneIndex);
    cloneDiv.children(".message-feedback").attr("id", "message-feedback"+cloneIndex);  
    
    cloneDiv.find("textarea").val('');
    cloneDiv.children(".message-feedback").empty();
    cloneDiv.find("textarea").focus();  

    var flag = cloneIndex;
    var text_max = 160;
    jQuery("#message-feedback"+cloneIndex).html(text_max + ' characters remaining');
    jQuery("#message-textarea-box"+cloneIndex).keyup(function() {
        var text_length_box = jQuery(this).val().length;         
        var text_remaining_box = text_max - text_length_box;
        cloneDiv.children(".message-feedback").html(text_remaining_box + ' characters remaining');
        if(text_remaining_box == 0)
        { 
            if(flag == cloneIndex){                              
                cloneIndex++; 
                clonee();
                flag = 0;
            }           
        }
    });        
}
// edit template popup function
function editClonee(msg, newLeangth){
    var text_max = 160;
    cloneIndex = jQuery(".message-box-div").length;    
    cloneDiv = jQuery("#message-textarea-box-div").clone();
    cloneDiv.attr("id", "message-textarea-box-div" +  cloneIndex)   
    .insertAfter(jQuery('[id^=message-textarea-box-div]:last')); 
    cloneDiv.find("textarea").attr('id', "message-textarea-box"+cloneIndex);
    cloneDiv.children(".message-feedback").attr("id", "message-feedback"+cloneIndex);
    cloneDiv.find("textarea").val(msg);    
    jQuery("#message-feedback"+cloneIndex).html(newLeangth + ' characters remaining');            
    cloneDiv.find("textarea").focus();  

    var flag = cloneIndex;       
    text_length_box = 0;text_remaining_box = 0;
    jQuery("#message-textarea-box"+cloneIndex).keyup(function() {
        var text_length_box = jQuery(this).val().length;          
        var text_remaining_box = text_max - text_length_box;         
        jQuery(this).closest(".message-box-div").find(".message-feedback").html(text_remaining_box + ' characters remaining');
        if(text_remaining_box == 0)
        { 
            if(flag == cloneIndex){                              
                cloneIndex++; 
                clonee();
                flag = 0;
            }           
        }
    });
}

function cloneeDiv(){
    var textarea_length = jQuery('.message-textarea-box').length;    
    if(textarea_length > 1){
        for(var len = textarea_length; len > 1; len--){
            jQuery(".message_main_container_overflow .message-box-div:last").remove();
        }        
    }
    var edit_alert_msg = jQuery(".message-textarea-box").val();
    if(edit_alert_msg){
        var numChunks = Math.ceil(edit_alert_msg.length / 160);
        var subMsg = 0;var msg = '';var onetimeflag = 0;var cloneIndex = '';var cloneDiv = '';text_max = 160;
        for(var i=1, j=0; i <= numChunks; i++){
            subMsg = 160;
            msg = edit_alert_msg.substr(j, subMsg);        
            j = subMsg*i+1;        
            newLeangth = text_max - msg.length;
            if(onetimeflag == 0){
                jQuery(".message-textarea-box").val(msg);
                jQuery("#message-feedback").html(newLeangth + ' characters remaining');
                onetimeflag = 1;                               
            }
            else{                 
                editClonee(msg, newLeangth);
            }
        }
    }
    else{
        var flag = 0;
        var text_max = 160;       
        jQuery('#message-feedback').html(text_max + ' characters remaining');
        jQuery('.message-textarea-box').keyup(function() {
            var text_length = jQuery('.message-textarea-box').val().length;     
            var text_remaining = text_max - text_length;
            jQuery('#message-feedback').html(text_remaining + ' characters remaining');                 
        });
    }
}

function alert_remove_img(templateId, attach_list_value){
    var datastring = "remove_img=1&templateID="+templateId+"&attachFid="+attach_list_value;
    jQuery.ajax({  
        type: "POST",  
        url: '/alert-remove-template-image',
        data: datastring,  
        success: function(data) {   
            document.getElementById("t_img_"+data).style.display = 'none';
            document.getElementById("del_alert_img_"+data).style.display = 'none';
        },
        //dataType: "json"
    });
}