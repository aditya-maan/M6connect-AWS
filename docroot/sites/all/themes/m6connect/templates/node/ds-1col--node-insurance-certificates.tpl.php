<?php

/**
 * @file
 * Display Suite 1 column template.
 */
 
 global $base_url;
 //pre($form);
 //kpr($form);
?>

<<?php print $ds_content_wrapper; print $layout_attributes; ?> class="ds-1col <?php print $classes;?> clearfix">
<?php if (isset($title_suffix['contextual_links'])): ?>
<?php print render($title_suffix['contextual_links']); ?>
<?php endif; ?>
<?php //print $ds_content; ?>
<!------------------------- content start -------------------->
<div class="row margin-5">
  <!--<div class="col-md-1 col-sm-1 col-xs-12 padding-5"></div>-->
  <div class="col-md-12 col-sm-12 col-xs-12 padding-5">
    <div class="row margin-10 margin-bottom-25">
      <div class="padding-10"><h3>Summary Information<br><hr></h3></div>
      <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
        <!--<h3>Submit New Insurance Certificate<br><hr></h3>-->
        <?php print render ($form['title']);?>
        <?php print render ($form['field_select_template']);?>
				<?php print render ($form['field_my_template']);?>
        <?php print render ($form['field_submit_to']);?>
        
        
        <?php print render ($form['group_submit_to_user_div']);?>
        
          <?php //print render ($form['submit_to_container']);?>
          <?php //print render ($form['submit_to_container']['submit_to_user']);?>
        
        <?php //print render ($form['submit_to_container_proj']);?>
          <?php //print render ($form['submit_to_container_proj']['submit_to_user_proj']);?>
        
        <?php //print render ($form['submit_to_container']['submit_to_user']);?>
        <?php //print render ($form['submit_to_container']['user_mark']);?> 
        <?php //print render ($form['submit_to_container2']);?>
        <?php ////print render ($form['field_submit_to_user_list']);?>
        <?php ////print render ($form['field_associate_to_project']);?>
        
        <?php print render ($form['submit_to_container_project']);?>
        
        <?php print render ($form['field_submit_to_user_markup']);?> 	
        
        <?php //print render ($form['field_submit_to_project']);?>
      	<div class="form-group">
        <h3>Additional Information <br>
          <hr>
        </h3>
        <!--<p>Are there additional insured parties listed on this certificate?  </p>-->
        </div>
        <label>Description of Operations or additional insured listed? <a href="<?php echo $base_url.'/sites/all/themes/m6connect/images/additional-insured.jpg'?>" onclick="window.open (this.href, 'child', 'height=800,width=800,left=300'); return false" id="additionalinsuredInfo" style="color:#337ab7; margin-left:10px;"><i class="fa fa-question-circle"></i></a></label>
        <?php print render ($form['field_description_of_operations']);?>
        <?php print render ($form['field_desc_of_operations']);?>
        <label>Is Company Listed as a Certificate Holder? <a href="<?php echo $base_url.'/sites/all/themes/m6connect/images/additional-insured2.jpg'?>" onclick="window.open (this.href, 'child', 'height=800,width=800,left=300'); return false" id="additionalinsuredInfo2" style="color:#337ab7; margin-left:10px;"><i class="fa fa-question-circle"></i></a></label>
        <?php print render ($form['field_is_company_listed_as_a_cer']);?>
        <?php print render ($form['field_individual_company_name_2']);?>
        <?php print render ($form['field_location_address']);?>
        <?php print render ($form['field_add_company_information']);?>
      </div>
      <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
        <!--<h3>Select Project and Contract<br><hr></h3>-->
        <?php //print render ($form['field_submit_to_project']);?>
        <?php //print render ($form['field_submit_to_contract']);?>
      </div>
    </div>
    <div class="row margin-10 margin-bottom-25">
      <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
        <h3>Insurer (Producer) Information <a href="<?php echo $base_url.'/sites/all/themes/m6connect/images/insurer-information.jpg'?>" onclick="window.open (this.href, 'child', 'height=800,width=800,left=300'); return false" id="insurerInfo" style="color:#337ab7; margin-left:10px;"><i class="fa fa-question-circle"></i></a><br>
          <hr>
        </h3>
        <?php print render ($form['field_insurance_company_name']);?>
        <?php print render ($form['field_insurance_agent_s_name']);?>
        <?php print render ($form['field_phone']);?>
        <?php print render ($form['field_email']);?>
        <?php print render ($form['field_insurer_address']);?>
      </div>
      <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
            <h3>Certificate Information<br>
              <hr></h3>
            <?php print render ($form['field_certificate_number']);?>
            <?php print render ($form['field_revision_number']);?>
         </div>
    </div>
    <div class="row margin-10 margin-bottom-25">
      	<div class="col-md-6 col-sm-6 col-xs-12 padding-10">
            <h3>Insured Information <a href="<?php echo $base_url.'/sites/all/themes/m6connect/images/insured-information.jpg'?>" onclick="window.open (this.href, 'child', 'height=800,width=800,left=300'); return false" id="insuredInfo" style="color:#337ab7; margin-left:10px;"><i class="fa fa-question-circle"></i></a><br>
              <hr>
            </h3>
            <?php print render ($form['field_individual_company_name']);?>
            <?php print render ($form['field_address']);?>
        </div>
        <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
            <h3>Selected Coverages <a href="<?php echo $base_url.'/sites/all/themes/m6connect/images/insurance-types.jpg'?>" onclick="window.open (this.href, 'child', 'height=800,width=800,left=300'); return false" id="typesInfo" style="color:#337ab7; margin-left:10px;"><i class="fa fa-question-circle"></i></a><br>
              <hr>
            </h3>
            <p>Please select all of the insurance types that are covered by this certificate and provide the policy number and effective dates for each type.</p>
            <?php print render ($form['field_commercial_select']);?>
            <?php print render ($form['field_commercial_general_liabili']);?>
    
            <?php print render ($form['field_automotive_select']);?>
            <?php print render ($form['field_automotive_liability']);?>
            
            <?php print render ($form['field_professional_liability_sel']);?>
            <?php print render ($form['field_professional_liability']);?>
    
            <?php print render ($form['field_builders_risk_select']);?>
            <?php print render ($form['field_builders_risk']);?>
    
            <?php print render ($form['field_garage_liability_select']);?>
            <?php print render ($form['field_garage_liability']);?>
    
            <?php print render ($form['field_excess_liability_select']);?>
            <?php print render ($form['field_excess_liability']);?>
    
            <?php print render ($form['field_workers_comp_select']);?>
            <?php print render ($form['field_workers_compensation_and_e']);?>
        </div>
    </div>
    <div class="row margin-10">
      <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
        <!--<h3>Sharing &amp; Notification Options<br><hr></h3>-->
        <?php //print render ($form['field_sharing_notification_optio']);?>
        <h3>Insurance Certificate Date <a href="<?php echo $base_url.'/sites/all/themes/m6connect/images/ins-csrt-date.jpg'?>" onclick="window.open (this.href, 'child', 'height=800,width=800,left=300'); return false" id="insdate" style="color:#337ab7; margin-left:10px;"><i class="fa fa-question-circle"></i></a></h3>
        <?php print render ($form['field_expiration_date']);?>
      </div>
      <div class="col-md-6 col-sm-6 col-xs-12 padding-10">
        <h3>Attach Certificate<br><hr></h3>
        <?php print render ($form['field_attach_certificates']);?>
      </div>
    </div>
    <?php //print render($form['actions']); ?>
    <?php //print drupal_render_children($form); ?>
	
  </div>
  <!--<div class="col-md-1 col-sm-1 col-xs-12 padding-5"></div>-->
</div>
<!------------------------- content end --------------------> 
</<?php print $ds_content_wrapper ?>>
<?php if (!empty($drupal_render_children)): ?>
  <?php print $drupal_render_children ?>
<?php endif; ?>

<style>
.node-insurance_certificates-form .form-field-name-field-description-of-operations label,
.node-insurance_certificates-form .form-field-name-field-is-company-listed-as-a-cer label,
.node-insurance_certificates-form .form-field-name-field-expiration-date span.fieldset-legend,
.node-insurance_certificates-form .form-field-name-field-expiration-date .form-item-field-expiration-date-und-0-value-date label{display:none;}

.node-insurance_certificates-form .form-field-name-field-description-of-operations label.option,
.node-insurance_certificates-form .form-field-name-field-is-company-listed-as-a-cer label.option {display:inline;}

.node-insurance_certificates-form .vertical-tabs {display:none;}

.node-insurance_certificates-form .form-field-name-field-cm-type{display:none;}
</style>