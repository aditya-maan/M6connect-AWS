<?php
 //$node = node_load($nid);
 $m6user = user_load($node->uid);  
 //print "<pre>"; print_r($m6user); 
 //module_load_include('inc', 'node', 'node.pages');
 //print "<pre>"; print_r($node); 
?>
<!-- Nav tabs -->
<ul class="nav nav-tabs tabs primary tabs-primary" role="tablist">
  <li role="presentation" class="active"><a href="#user_m6id_profile" aria-controls="user_m6id_profile" role="tab" data-toggle="tab">M6ID Profile</a></li>
  <li role="presentation"><a href="#user_m6id_status" aria-controls="user_m6id_status" role="tab" data-toggle="tab">M6ID Status</a></li>
</ul>
<!-- Nav tabs End -->
<div class="tab-content">
  <div role="tabpanel" class="tab-pane active" id="user_m6id_profile">
    <div class="clearfix onboarding-profile-view">
      <div class="clearfix onboarding-profile-view-first onboarding-profile-heighlight">
        <div class="row margin-5">
          <div class="col-md-9 col-sm-9 col-xs-12 padding-5">
            <div class="row margin-5 field-name-field-first-name">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>First Name:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $m6user->field_first_name['und']['0']['value']; ?> </div>
            </div>
            <div class="row margin-5 field-name-field-middle-name">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Middle Name:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $m6user->field_middle_name['und']['0']['value']; ?> </div>
            </div>
            <div class="row margin-5 field-name-field-last-name">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Last Name:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $m6user->field_last_name['und']['0']['value']; ?> </div>
            </div>
            <div class="row margin-5 field-name-field-date-of-birth">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Date Of Birth:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5">
                <?php if(!empty($m6user->field_date_of_birth['und']['0']['value'])){ print date("j F, Y", strtotime($m6user->field_date_of_birth['und']['0']['value']));} ?>
              </div>
            </div>
          </div>
          <div class="col-md-3 col-sm-3 col-xs-12 padding-5 text-right">
            <div class="field-name-field-profile-photo">
              <?php
            if(isset($m6user->field_user_profile_photo['und']) && !empty($m6user->field_user_profile_photo['und'][0]['uri'])){ 
      			 $user_profile = (isset($m6user->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'thumbnail', 'path' => $m6user->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : ''; 	
      		  } 
      		  ?>
              <?php print $user_profile ;?> </div>
          </div>
        </div>
      </div>
      <div class="clearfix onboarding-profile-view-second onboarding-profile-width onboarding-profile-heighlight">
        <div class="row margin-5 field-name-field-phone">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Mobile Phone Number:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> 
    		    <?php
    		    if(!empty($m6user->field_phone['und']['0']['value'])){
    			   $phone = $m6user->field_phone['und']['0']['value'];
    		       $phoneNumberval = get_international_formatPhoneNumber($phone);
    		       print $phoneNumberval; 
    		    }    		   
    		   ?> 
          </div>
        </div>
        <div class="row margin-5 field-name-field-mobile-Phone">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Work Phone Number:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> 
		      <?php			
    			if(!empty($m6user->field_mobile_phone['und']['0']['value'])){
  			   $mobilephone = $m6user->field_mobile_phone['und']['0']['value'];
  		       $mobileNumberval = get_international_formatPhoneNumber($mobilephone);
  		       print $mobileNumberval; 
  		      }
    			   //print $m6user->field_mobile_phone['und']['0']['value'];			
		      ?> 
          </div>
        </div>
        <div class="row margin-5 field-name-field-alt-Phone">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Alt Phone:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5">
           <?php
    		    if(!empty($m6user->field_alt_phone['und']['0']['value'])){
    			   $altphone =  $m6user->field_alt_phone['und']['0']['value'];
    		      $altphoneNumberval = get_international_formatPhoneNumber($altphone);
    		      // print $m6user->field_alt_phone['und']['0']['value'];
    			   print $altphoneNumberval;
    		    }
    		    ?> 
           </div>
        </div>
        <div class="row margin-5 field-name-field-job-titles">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Job Titles:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5">
            <?php 
    				$tid = $m6user->field_job_titles['und']['0']['target_id'];
    				$term = taxonomy_term_load($tid);
    				$name = $term->name;
    				print $name;
			   ?>
          </div>
        </div>
        <!--<div class="row margin-5 field-name-field-responsibilities">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5">Responsibilities:&nbsp;</div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> <?php //print $m6user->field_responsibilities['und']['0']['value']; ?> </div>
        </div>--> 
        <!--<div class="row margin-5 field-name-field-user-title">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5">Title:&nbsp;</div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> <?php //print $m6user->field_user_title['und']['0']['value']; ?> </div>
        </div>-->
        <div class="row margin-5 field-name-field-address">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Address:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5">
            <?php 
      			//print $address1 = $m6user->field_address['und']['0']['thoroughfare'];
      			//print $address2 = $m6user->field_address['und']['0']['premise']; 
      			//print $city = $m6user->field_address['und']['0']['locality']; 
      			//print $state = $m6user->field_address['und']['0']['administrative_area']; 
      			//print $postal_code = $m6user->field_address['und']['0']['postal_code']; 
      			//print $country = $m6user->field_address['und']['0']['country'];
		      print render(field_view_field('user', $m6user, 'field_address', array('label'=>'hidden')));   
			     ?>
          </div>
        </div>
      </div>
      <div class="clearfix onboarding-profile-view-third onboarding-profile-width onboarding-profile-heighlight">
        <div class="row margin-5 field-name-field-are-you-a-us-citizen">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Are you a US citizen?:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"><?php print $node->field_are_you_a_us_citizen['und']['0']['value']; ?></div>
        </div>
        <div class="row margin-5 field-name-field-organization-mail">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Personal E-mail address:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"><?php print $m6user->field_organization_mail['und']['0']['email'] ;?></div>
        </div>
        <div class="row margin-5 field-name-field-work-email-address">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Work Email Address:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> <?php print $m6user->field_confirm_your_email_address['und']['0']['email']; ?></div>
        </div>
        <div class="row margin-5 field-name-field-work-phone-number">
          <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Work Phone Number:&nbsp;</strong></div>
          <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> 
  		  <?php 
  		  if(!empty($node->field_phone['und']['0']['value'])){
  			$phonem6id = $node->field_phone['und']['0']['value'];
  		    $phonem6idval = get_international_formatPhoneNumber($phonem6id);
  		    //print $node->field_phone['und']['0']['value'];
  			print $phonem6idval; 
  		  }
  		   ?></div>
          </div>
          <div class="row margin-5 field-name-field-home-phone-number">
            <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Home Phone Number:&nbsp;</strong></div>
            <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> 
  		  <?php 
  		   if(!empty($node->field_home_phone['und']['0']['value'])){
  			$homephonem6id = $node->field_home_phone['und']['0']['value'];
  		    $homephonen6idval = get_international_formatPhoneNumber($homephonem6id);
  		    print $homephonen6idval ;
  		   //print $node->field_home_phone['und']['0']['value'];
  		   }
  		   ?></div>
          </div>
          <div class="row margin-5 field-name-field-cellular-phone-number">
            <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Cellular Phone Number:&nbsp;</strong></div>
            <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> 
  		  <?php 
  		  if(!empty($node->field_cellular_phone['und']['0']['value'])){
  			$cellularphone = $node->field_cellular_phone['und']['0']['value'];
  			$cellulardval = get_international_formatPhoneNumber($cellularphone);
  		    print $cellulardval;  
  		   //print $node->field_cellular_phone['und']['0']['value']; 
  		  }
  		  ?></div>
          </div>
          <div class="row margin-5 field-name-field-alt-phone">
            <div class="col-md-4 col-sm-4 col-xs-12 padding-5"><strong>Alternate Phone Number:&nbsp;</strong></div>
            <div class="col-md-8 col-sm-8 col-xs-12 padding-5"> 
  		  <?php
  		  if(!empty($node->field_alt_phone['und']['0']['value'])){
  			   
  			 $alternatePhone = $node->field_alt_phone['und']['0']['value'];
  			 $alternatePhoneval = get_international_formatPhoneNumber($alternatePhone);
  			 print $alternatePhoneval; 
  		     //print $node->field_alt_phone['und']['0']['value']; 
  		   }
  		  ?></div>
          </div>
      </div>
      <div class="clearfix onboarding-profile-view-fourth onboarding-profile-heighlight">
        <div class="panel panel-primary">
          <div class="panel-heading"><strong>Trade Category</strong> </div>
          <div class="panel-body">
            <div class="row margin-5 field-name-field-facilities">
              <div class="col-md-4 col-sm-6 col-xs-12 padding-5"><strong>Trade Category:&nbsp;</strong></div>
              <div class="col-md-8 col-sm-6 col-xs-12 padding-5">
                <?php 
				 // print $node->field_facilities_construction['und']['0']['value'];
				  //print render(field_view_field('node', $node, 'field_facilities_construction', array('label'=>'hidden')));
				   $facilities_construction = $node->field_facilities_construction['und']; 
				   foreach($facilities_construction as $facilitiesval){ 
						 $factid = $facilitiesval['tid'];
						 $facterm = taxonomy_term_load($factid);
						 $facname = $facterm->name;
						 print $facname . ' ';
			 
					}
				   ?>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div class="clearfix onboarding-profile-view-fourth onboarding-profile-heighlight">
      <div class="panel panel-primary">
        <div class="panel-heading"><strong>Driving Licence Information</strong> </div>
        <div class="panel-body">
        <div class="row margin-5">
          <div class="col-md-9 col-sm-9 col-xs-12 padding-5">
            <div class="row margin-5 field-name-field-drivers-license-number">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Drivers License Number:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_drivers_license_number['und']['0']['value']; ?> </div>
            </div>
            <div class="row margin-5 field-name-field-country-of-issuance">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Country of Issuance:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_drivers_license_issuance['und']['0']['country']; ?> </div>
            </div>
            <div class="row margin-5 field-name-field-country-of-issuance">
              <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>State of Issuance:&nbsp;</strong></div>
              <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_drivers_license_issuance['und']['0']['administrative_area']; ?> </div>
            </div>
          </div>
          <div class="col-md-3 col-sm-3 col-xs-12 padding-5 text-right">
            <div class="field-name-field-country-of-issuance">
           <?php
		   
		   foreach($node->field_attach_driving_licence['und'] as $attach_driving){      
			 $driving_fid = $attach_driving['fid'];
			 $drivingfile = file_load($driving_fid);
			 $drivinguri = $drivingfile->uri;
			 $drivingtypechk = $drivingfile->type;
		   
            if($drivinguri){ 
			   if($drivingtypechk == 'image'){	
				 $user_profile = (isset($drivingfile->uri)) ? theme('image_style', array('style_name' => 'thumbnail', 'path' => $drivingfile->uri, 'getsize' => TRUE)) : ''; 	
		    
			     print '<div class="margin-bottom-10">'.$user_profile.'</div>' ;
			   }
			   if($drivingtypechk == 'document'){
				 $drivingimages = file_create_url($drivinguri);
				 print '<div class="margin-bottom-10"><a href="'.$drivingimages.'">'.$drivingfile->filename.'</a></div>';
			   }
		    }
		   }
			  
			  ?> 
              
              </div>
          </div>
        </div>
        </div>
        </div>
      </div>
      <div class="clearfix onboarding-profile-view-fourth onboarding-profile-heighlight">
        <div class="panel panel-primary">
          <div class="panel-heading"><strong>Vehicle Insurance Statement of Coverage</strong> </div>
          <div class="panel-body">
            <div class="row margin-5">
              <div class="col-md-9 col-sm-9 col-xs-12 padding-5">
                <div class="row margin-5 field-name-field-facilities">
                  <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Company name:&nbsp;</strong></div>
                  <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_vehicle_insurance_statemen['und']['0']['value']; ?></div>
                </div>
                <div class="row margin-5 field-name-field-facilities">
                  <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Policy Expiration Date:&nbsp;</strong></div>
                  <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> 
				  <?php if(!empty($node->field_policy_expiration_date['und']['0']['value'])){print date("F j, Y",$node->field_policy_expiration_date['und']['0']['value']); }?>
                  </div>
                </div>
                <div class="row margin-5 field-name-field-facilities">
                  <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Vehicle License Plate Number:&nbsp;</strong></div>
                  <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_vehicle_license_plate_numb['und']['0']['value']; ?></div>
                </div>
              </div>
              <div class="col-md-3 col-sm-3 col-xs-12 padding-5 text-right">
               <?php 
       foreach($node->field_attach_copy['und'] as $attach_vehicle){      
			 $vehicle_fid = $attach_vehicle['fid'];
			 $vehiclefile = file_load($vehicle_fid);
			 $vehicleuri =  $vehiclefile->uri;
			 $vehicletypechk =  $vehiclefile->type;
		   
         if($vehicleuri){ 
			 if($vehicletypechk == 'image'){	
				 $vehicleimages = (isset($vehiclefile->uri)) ? theme('image_style', array('style_name' => 'thumbnail', 'path' => $vehiclefile->uri, 'getsize' => TRUE)) : ''; 	
		    
			     print '<div class="margin-bottom-10">'.$vehicleimages.'</div>';
			  }
			  if($vehicletypechk == 'document'){
				 $vehicledocument = file_create_url($vehicleuri);
				 print '<div class="margin-bottom-10"><a href="'.$vehicledocument.'">'.$vehiclefile->filename.'</a></div>';
			  }
		 }
      }
				
               ?>
                 </div>
            </div>
          </div>
        </div>
      </div>
      <div class="clearfix onboarding-profile-view-fourth onboarding-profile-heighlight">
        <div class="panel panel-primary">
          <div class="panel-heading"><strong>Emergency Contact</strong> </div>
          <div class="panel-body">
            <div class="row margin-5 field-name-field-facilities">
              <div class="col-md-4 col-sm-6 col-xs-12 padding-5"><strong>First Name:&nbsp;</strong></div>
              <div class="col-md-8 col-sm-6 col-xs-12 padding-5"><?php print $node->	field_emergency_first_name['und']['0']['value']; ?></div>
            </div>
            <div class="row margin-5 field-name-field-work-phone-number">
              <div class="col-md-4 col-sm-6 col-xs-12 padding-5"><strong>MI:&nbsp;</strong></div>
              <div class="col-md-8 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_emergency_middle_name['und']['0']['value']; ?></div>
            </div>
            <div class="row margin-5 field-name-field-work-phone-number">
              <div class="col-md-4 col-sm-6 col-xs-12 padding-5"><strong>Last Name:&nbsp;</strong></div>
              <div class="col-md-8 col-sm-6 col-xs-12 padding-5"> <?php print $node->field_emergency_last_name['und']['0']['value']; ?></div>
            </div>
            <div class="row margin-5 field-name-field-work-phone-number">
              <div class="col-md-4 col-sm-6 col-xs-12 padding-5"><strong>Cellular Phone Number:&nbsp;</strong></div>
              <div class="col-md-8 col-sm-6 col-xs-12 padding-5"> 
			  <?php 
			  if(!empty($node->field_emergency_phone_number['und']['0']['value'])){  
			   $emergencyphone = $node->field_emergency_phone_number['und']['0']['value'];  
			   $emergencyphoneval = get_international_formatPhoneNumber($emergencyphone);
			   print $emergencyphoneval;
			   //print $node->field_emergency_phone_number['und']['0']['value'];
			    
			  }
			  ?></div>
            </div>
          </div>
        </div>
      </div>
      <div class="clearfix onboarding-profile-view-fourth onboarding-profile-heighlight">
        <div class="panel panel-primary">
          <div class="panel-heading"><strong>Credentials</strong> </div>
          <div class="panel-body">
            <?php  
    		    $items = field_get_items('node', $node, 'field_onbarding_credentials');
    			  foreach ($items as $item) {
              $fcvalue = field_collection_field_get_entity($item); ?>
              <div class="onboarding-profile-heighlight clearfix">
                <div class="row margin-5">
                  <div class="col-md-9 col-sm-9 col-xs-12 padding-5">
                    <div class="row margin-5 field-name-field-facilities">
                      <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Credential Type:&nbsp;</strong></div>
                      <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5">
                        <?php	  
  				                echo $fcvalue->field_ob_credential_type['und'][0]['value'];
  				              ?>
                      </div>
                    </div>
                    <div class="row margin-5 field-name-field-facilities">
                      <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Title / Name of Credential:&nbsp;</strong></div>
                      <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5">
                        <?php	echo $fcvalue->field_title_name_of_credential['und'][0]['value'];?>
                      </div>
                    </div>
                    <div class="row margin-5 field-name-field-facilities">
                      <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Received / Presented by:&nbsp;</strong></div>
                      <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5">
                        <?php	echo $fcvalue->field_received_presented_by['und'][0]['value'];?>
                      </div>
                    </div>
                    <div class="row margin-5 field-name-field-facilities">
                      <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Received:&nbsp;</strong></div>
                      <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5">
                        <?php	if(!empty($fcvalue->field_ob_received['und'][0]['value'])){echo date("F j, Y", $fcvalue->field_ob_received['und'][0]['value']) ; }?>
                      </div>
                    </div>
                    <div class="row margin-5 field-name-field-facilities">
                      <div class="field-label col-md-6 col-sm-6 col-xs-12 padding-5"><strong>Expires:&nbsp;</strong></div>
                      <div class="field-items col-md-6 col-sm-6 col-xs-12 padding-5">
                        <?php if(!empty($fcvalue->field_ob_expires['und'][0]['value'])){ echo date("F j, Y", $fcvalue->field_ob_expires['und'][0]['value']);}?>
                      </div>
                    </div>
                  </div>
                  <div class="col-md-3 col-sm-3 col-xs-12 padding-5 text-right">
                    <?php
      					     //print $fcvalue->field_ob_attach_image['und']['0']['uri']; 
      		          if(isset($fcvalue->field_ob_attach_image['und']) && !empty($fcvalue->field_ob_attach_image['und'][0]['uri'])){ 
      			          if($fcvalue->field_ob_attach_image['und'][0]['type'] == 'image'){
      			            $obattachimages = (isset($fcvalue->field_ob_attach_image['und'])) ? theme('image_style', array('style_name' => 'thumbnail', 'path' => $fcvalue->field_ob_attach_image['und'][0]['uri'], 'getsize' => TRUE)) : ''; 	
      				          print '<div class="margin-bottom-10">'.$obattachimages.'</div>';
      			          }
      			          if($fcvalue->field_ob_attach_image['und'][0]['type'] == 'document'){
      				          $obfilename = $fcvalue->field_ob_attach_image['und'][0]['filename']; 
      				          $obattachdocument = file_create_url($fcvalue->field_ob_attach_image['und']['0']['uri']);
      				          print '<div class="margin-bottom-10"><a href="'.$obattachdocument.'">'.$obfilename.'</a></div>';  
      			          }				   
      		          }?>
                  </div>
                </div>
              </div>
            <?php } ?>
          </div>
        </div>
      </div>
    </div>
  </div>
  <!--Start M6ID Status-->
  <div role="tabpanel" class="tab-pane" id="user_m6id_status">
    <?php
	   if(!empty($node->uid) && is_numeric($node->uid)){
	    $m6idprofilestatus = onboarding_profile_status_tab($node->uid);
		print $m6idprofilestatus;
		
		}
	 ?>
  </div>
  <!----- End M6ID Status ----> 
  
</div>
