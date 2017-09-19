<?php if (!(module_exists('jquery_update') && module_exists('m6connect_misc'))) { ?>
<!--<script src="/sites/all/themes/m6connect/js/jquery1.11.3.min.js"></script>-->
<?php } ?>
<!--<script src="/sites/all/themes/m6connect/js/bootstrap.min.js"></script>
<script src="/sites/all/themes/m6connect/js/dropdown.js"></script>
<script src="/sites/all/themes/m6connect/js/collapse.js"></script>-->
<?php
// global $user;	//added by colan
 //pre($form['account']);
 //print "<pre>"; print_r($form['account']); die;

unset($form['account']['mail']['htmlmail_plaintext']);
$cuid = arg(1); 
$user = user_load($cuid);	

//pre($user);field_m6id_node
$site_url = $GLOBALS['base_url'];
?>

<div class="my-form-wrapper">
          
		<div class="user-profile-custom-wrapper">
			<div class="user-info-inner">
				<div class="info-inner row margin-5">
					<div class="form-wrapper cust-user-name cust-user-part-1 col-md-6 col-sm-6 col-xs-12 padding-5 margin-bottom-10">
                    <?php
					  print render($form['field_allow_routing_slip_access']);
					  print render($form['field_allow_onboarding_access']);
				      print render($form['field_allow_m6alert']);
				      print render($form['field_personal_m6drive_space']);
				      //print render($form['field_company_m6drive_space']);	
					  print render($form['field_first_name']);
					  print render($form['field_middle_name']);
					  print render($form['field_last_name']);
					  print render($form['account']['name']);
					  print render($form['account']['current_pass']);
 				      print render($form['account']['pass']);
					  ?>
                      <div class="personal_profile_hide">
                      <?php
					  print drupal_render($form['field_date_of_birth']);
					  print drupal_render($form['field_hide_date_of_birth']);
					  ?>
                      </div>
                      <?php
					  print drupal_render($form['field_gender']);
					  ?>
                      <div class="personal_profile_hide">
                      <?php
					  print render($form['field_hide_phone_number']);
					  print render($form['field_phone']);
					  ?>
                      </div>
                      
                      <?php
					  print render($form['field_mobile_phone']);
					  print render($form['field_user_profile_photo']);
					  print render($form['field_user_profile_cover_img']);
					  //print render ($form['field_job_titles']);
					  print render ($form['field_m6id']);
					  print render ($form['display_m6id']);
					  print render($form['account']['status']);
					  print render($form['account']['roles']);
					  print render ($form['field_automatically_receive_mail']);
					  print render ($form['field_receive_insurance_certific']);
					  print render($form['privatemsg']);
					  print render($form['actions']);
                     ?>
					</div>
					<div class="cust-user-part-2 col-md-6 col-sm-6 col-xs-12 padding-5 margin-bottom-10">
                    <?php
					//print render ($form['account']);
					
					  print drupal_render ($form['group_timezone_container']);
					  print drupal_render ($form['field_m6id_entity']);
					  print render ($form['account']['mail']);
					  print render ($form['field_confirm_your_email_address']);
					  print render ($form['field_address']);

					//print render ($form['field_user_title']);
					//print render ($form['field_responsibilities']);
					  print render ($form['field_alt_phone']);
					//print render ($form['field_mobile_phone']);
					  print render ($form['field_fax']);
					  print drupal_render($form['field_facebook_url']);
					  print drupal_render($form['field_linkedin_url']);
					  print drupal_render($form['field_twitter_url']);
					  print drupal_render($form['field_behance_url']);
					  ?>
					</div>
				</div>
			</div>
		</div>
	 
      <div style="display:none;"><?php print drupal_render_children($form); ?></div>		
</div>
<?php /* check to see if it is the owner of the profile before displaying this link 
  if ($GLOBALS['user']->uid == $user->uid): ?> 
    <div style="float:right" class="orders">
      <?php print l(t('View your order history'), "user/$user->uid/orders");?>
    </div>
  <?php endif; /* end of snippet */ ?>
<script>
function page_upgrade(){
window.location="<?php echo $site_url; ?>/upgrade-your-membership-subscription";
}
function myFunction() {
var current_user = "<?php echo $user->uid; ?>";
$.ajax({  
    type: 'POST',  
    url: '<?php echo $site_url; ?>/custom/unsubscribe/plan/'+current_user, 
    data: { user_subscribe: current_user },
    dataType : 'json',
    success: function(response) {
        if(response.result == 'success')
        {
            alert("Your Unsubscription request has been accepted. Your Recurring Payment has been cancelled. After your current plan period reached, the plan will be changed to Free plan Automatically. Thanks!");
            location.reload(); 
        }
        
        if(response.result == 'norebillid')
        {
            alert("Sorry! It seems that your unsubscription request is already in process or your plan has been changed already. If this is not your case, kindly contact site administrator.");
        }
        
         if(response.result == 'failed')
        {
            alert("Sorry! There was some problem in processing your request. Please refresh the page and try again.");
        }
  }
});
}
</script>
<div class="modal fade" id="myModal" role="dialog">
  <div class="modal-dialog modal-md">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal">&times;</button>
        <h4 class="modal-title">Membership Plan Upgrade</h4>
      </div>
      <div class="modal-body">
        <p class="text-upgrade">Are you sure want to unsubscribe the membership plan?</p>
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-default" data-dismiss="modal" id="ok_btn" onclick="myFunction()" >ok</button>
        <button type="button" class="btn btn-default" id="current_id" data-dismiss="modal">cancel</button>
      </div>
    </div>
  </div>
</div>
