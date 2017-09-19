<div class="user-reg-custom-wrapper">
  <div class="reg-user-info-wrapper">
    <div class="user-info-inner clearfix">
        <div class="form-wrapper cust-user-name clearfix">
          <div class="row field_names">
            <div class="col-md-6 margin-bottom-25 field_first_name"> <?php print render ($form['field_first_name']); ?> </div>
            <div class="col-md-6 margin-bottom-25 field_last_name"> <?php print render ($form['field_last_name']); ?> </div>
          </div>

          <div class="row field_date_gender">
            <div class="col-md-6 margin-bottom-25 field_date_of_birth"> <?php print render ($form['field_date_of_birth']); ?> </div>
            <div class="col-md-6 margin-bottom-25 field_date_gender_data"> <?php print render ($form['field_gender']); ?> </div>
          </div>
          <div class="row field_phone_timezone">
            <div class="col-md-6 margin-bottom-25 organigation-phone"> <?php print render ($form['field_phone']); ?> </div>
            <div class="col-md-6 margin-bottom-25 organigation-time-zone"> <?php print drupal_render ($form['group_timezone_container']); ?> </div>
          </div>
          <div class="row field_email_confirm_email">
            <div class="col-md-6 margin-bottom-25 field_account_email_address"><?php print render ($form['account']['mail']); ?> </div>
            <div class="col-md-6 margin-bottom-25 field_confirm_your_email_address"><?php print render ($form['field_confirm_your_email_address']); ?> </div>
          </div>
          <div class="clearfix field_account_password"> <?php print render ($form['account']); ?></div>
          <div class="clearfix margin-bottom-10 field_account_captcha"> <?php print render($form['captcha']); ?></div>
          <div class="clearfix margin-bottom-15 organigation-service_agreement">
            <div class="clearfix form-service_agreement"> 
              <?php  print drupal_render($form['field_service_agreement']); ?>
            </div>
          </div>
          <div class="clearfix text-center form-actions"> <?php print render ($form['actions']); ?></div>
        </div>
    </div>
  </div>
  <div style="display:none;"> <?php print drupal_render_children($form); ?> </div>
</div>
