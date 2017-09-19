<?php if ($form['#user_profile_credental'] == FALSE){ ?>
<div class="my-form-wrapper-onboard clearfix">
  <div class="m6-onboarding-node-form margin-bottom-10 clearfix">
    <div class="user_credendial_login clearfix">
      <!--<div class="user_credendial_heading clearfix margin-bottom-10">User Login <i class="fa fa-chevron-right"></i></div>-->
 <!--     <ul class="list-unstyled list-inline custom-list">
        <li class="active">User Login</li>
      </ul>-->
      <?php if ($form['step_login_credendials']): ?>
      <div class="user_credendial_body clearfix">
        <?php //kpr($form); print render ($form['#step']['step_login_credendials']);//print render ($form['step_login_credendials']);?>
        <?php print render ($form['step_login_credendials']['user_credendial_email']); ?> <?php print render ($form['step_login_credendials']['user_credendial_password']); ?> </div>
      <?php endif; ?>
    </div>
    <div class="personal_information clearfix">
      <?php if ($form['step_ob_personal_information']): ?>
      <div class="user_credendial_body clearfix">
        <div class="personal_information_title clearfix"> <?php print render ($form['step_ob_personal_information']['title']); ?> </div>
        <div class="personal-information-fileds personal_information_border margin-bottom-10 clearfix">
            <div class="row"> 
              <div class="col-md-6 personal_information_email_address"> <?php print render ($form['step_ob_personal_information']['field_confirm_your_email_address']); ?> </div>
              <div class="col-md-6 personal_information_citizen"> <?php print render ($form['step_ob_personal_information']['field_are_you_a_us_citizen']); ?> </div>
            </div>
            <div class="row"> 
              <div class="col-md-6 personal_information_mobile_phone"> <?php print render ($form['step_ob_personal_information']['field_cellular_phone']); ?> </div>
              <div class="col-md-6 personal_information_phone"> <?php print render ($form['step_ob_personal_information']['field_phone']); ?> </div>
            </div>
            <div class="row">
              <div class="col-md-6 home_phone"> <?php print render ($form['step_ob_personal_information']['field_home_phone']); ?> </div>
              <div class="col-md-6 personal_information_alt_phone"> <?php print render ($form['step_ob_personal_information']['field_alt_phone']); ?> </div>
            </div>
        </div>
        <div class="personal_information_border margin-bottom-10 clearfix">
          <div class="facilities-construction-section clearfix"> <?php print render ($form['step_ob_personal_information']['field_facilities_construction']); ?> </div>
        </div>
        <div class="personal_information_border margin-bottom-10 clearfix">
          <div class="row">
            <div class="col-md-5 personal_information_license_number"> 
			<?php print render ($form['step_ob_personal_information']['field_drivers_license_number']); ?>
             <?php print render ($form['step_ob_personal_information']['field_drivers_license_issuance']); ?> 
             </div>
            <div class="col-md-7 personal_information_license_attach"> <?php print render ($form['step_ob_personal_information']['field_attach_driving_licence']); ?> </div>
            <!--<div class="col-md-2"></div>--> 
          </div>
        </div>
        <!--<div class="row">
              <div class="col-md-5 personal_information_license_plate_number"> <?php print render ($form['step_ob_personal_information']['field_vehicle_license_plate_numb']); ?> </div>
              <div class="col-md-7"></div>
            </div>-->
        <div class="personal_information_border margin-bottom-10 clearfix">
          <div class="personal_information_heading">
          <div class="clearfix"><strong>Vehicle Insurance Statement of Coverage</strong></div>
          <div class="clearfix fieldset-description">This information is considered private - it will be available to M6ID Managers for companies you work for.</div>
          </div>
          
          <div class="row">
            <div class="col-md-4 personal_information_insurance_statemen"><?php print render ($form['step_ob_personal_information']['field_vehicle_insurance_statemen']);?></div>
            <div class="col-md-4 personal_information_policy_expire"><?php print render ($form['step_ob_personal_information']['field_policy_expiration_date']);?></div>
            <div class="col-md-4 personal_information_license_plate_number"> <?php print render ($form['step_ob_personal_information']['field_vehicle_license_plate_numb']); ?> </div>
            <div class="col-md-4 personal_information_attach_copy"><?php print render ($form['step_ob_personal_information']['field_attach_copy']);?></div>
          </div>
        </div>
        <div class="personal_information_border margin-bottom-10 clearfix">
          <div class="personal_information_heading"> <?php print render ($form['step_ob_personal_information']['field_emergency_contact']); ?> </div>
          <div class="row">
            <div class="col-md-5 personal_information_emergency_first_name"> <?php print render ($form['step_ob_personal_information']['field_emergency_first_name']); ?> </div>
            <div class="col-md-2 personal_information_emergency_middle_name"> <?php print render ($form['step_ob_personal_information']['field_emergency_middle_name']); ?> </div>
            <div class="col-md-5 personal_information_emergency_last_name"> <?php print render ($form['step_ob_personal_information']['field_emergency_last_name']); ?> </div>
          </div>
          <div class="row">
            <div class="col-md-5 personal_information_emergency_phone_number"> <?php print render ($form['step_ob_personal_information']['field_emergency_phone_number']); ?> </div>
            <div class="col-md-7"> </div>
          </div>
        </div>
        <div class="personal_information_border margin-bottom-10 clearfix">
          <div class="personal_information_heading">
             <div class="clearfix"><strong>Credentials</strong></div>
             <div class="clearfix fieldset-description">This information is considered public and will be posted in your profile.</div>
          </div>
          <div class="ob_credentials"> <?php print render ($form['step_ob_personal_information']['field_onbarding_credentials']); ?> </div>
        </div>
        <div class="fields-extra clearfix" style="display:none;"> <?php print render ($form['step_ob_personal_information']['field_preferred_name']); ?> </div>
      </div>
      <?php endif; ?>
    </div>
    <!-- <div class="ob_credentials">
      <div class="clearfix">
        <?php //if ($form['step_ob_credentials']): ?>
        <ul class="list-unstyled list-inline custom-list">
          <li>General Information</li>


          <li class="active">Credentials</li>
          <li>Agreement</li>
          <li>Submissions</li>
          <li>Confirmation Login</li>
        </ul>
        <?php //endif; ?>
      </div>
      <?php //if ($form['step_ob_credentials']): ?>
      <div class="user_credendial_body clearfix">
        <?php //print render ($form['step_ob_credentials']);?>
        <?php //print render ($form['step_ob_credentials']['field_onbarding_credentials']); ?> </div>
      <?php //endif; ?>
    </div>-->
    <div class="ob_submitting clearfix">
      <div class="clearfix">
        <?php if ($form['step_ob_submitting']): ?>
        <!--<div class="user_credendial_heading margin-bottom-10">Personal Information <i class="fa fa-chevron-right"></i></div>
        <div class="user_credendial_heading margin-bottom-10">Credentials <i class="fa fa-chevron-right"></i></div>
        <div class="user_credendial_heading margin-bottom-10">Submitting <i class="fa fa-chevron-right"></i></div>-->
        <ul class="list-unstyled list-inline custom-list">
          <li>General Information</li>
          <!--<li>Credentials</li>-->
          <li class="active">Agreement</li>
          <li>Submissions</li>
          <!--<li>Confirmation Login</li>-->
        </ul>
        <?php endif; ?>
      </div>
      <?php if ($form['step_ob_submitting']): ?>
      <div class="user_credendial_body clearfix"> <?php print render ($form['step_ob_submitting']['group_ob_submitted_container']); ?> </div>
      <?php endif; ?>
    </div>
    <div class="ob_submission clearfix">
      <div class="clearfix">
        <?php if ($form['step_ob_submission']): ?>
        <ul class="list-unstyled list-inline custom-list">
          <li>General Information</li>
          <!--<li>Credentials</li>-->
          <li>Agreement</li>
          <li class="active">Submissions</li>
          <!--<li>Confirmation Login</li>-->
        </ul>
        <?php endif; ?>
      </div>
      <?php if ($form['step_ob_submission']): ?>
      <div class="user_credendial_body clearfix"> <?php print render ($form['step_ob_submission']['group_ob_submission_container']); ?> </div>
      <?php endif; ?>
    </div>
    <!--<div class="submit_login_credentials">
      <div class="clearfix">
        <?php //if ($form['step_submit_login_credentials']): ?>
        <ul class="list-unstyled list-inline custom-list">
          <li>General Information</li>
          <li>Credentials</li>
          <li>Agreement</li>
          <li>Submissions</li>
          <li class="active" title="Finalize your Submission for Onboarding by Logging in Below">Confirmation Login</li>
        </ul>
        <?php //endif; ?>
      </div>
      <?php //if ($form['step_submit_login_credentials']): ?>
      <div class="user_credendial_body clearfix">
        <?php //print render ($form['step_submit_login_credentials']);?>
        <?php //print render ($form['step_submit_login_credentials']['user_credendial_email_submitted']); ?> <?php //print render ($form['step_submit_login_credentials']['user_credendial_password_submitted']); ?> </div>
      <?php //endif; ?>
    </div>--> 
  </div>
  <div class="onboard-action clearfix">
    <?php  print render($form['actions']); ?>
  </div>
  <div class="clearfix" style="display:none;"><?php print drupal_render_children($form); ?></div>
</div>
<?php }else{ ?>
<div class="my-form-wrapper-onboard user-profile-vew-page clearfix">
  <div class="m6-onboarding-node-form margin-bottom-10 clearfix">    
    <div class="personal_information clearfix">
      <?php if ($form['step_ob_personal_information']): ?>
      <div class="user_credendial_body clearfix">        
        <div class="personal_information_border margin-bottom-10 clearfix">
          <div class="personal_information_heading">
             <div class="clearfix"><strong>Credentials</strong></div>
             <div class="clearfix fieldset-description">This information is considered public and will be posted in your profile.</div>
          </div>
          <div class="ob_credentials"> <?php print render ($form['step_ob_personal_information']['field_onbarding_credentials']); ?> </div>
        </div>
        <div class="fields-extra clearfix" style="display:none;"> <?php print render ($form['step_ob_personal_information']['field_preferred_name']); ?> </div>
      </div>
      <?php endif; ?>
    </div>
  </div>
  <div class="onboard-action clearfix">
    <?php  print render($form['actions']); ?>
  </div>
  <div class="clearfix" style="display:none;"><?php print drupal_render_children($form); ?></div>
</div>
	
<?php }?>