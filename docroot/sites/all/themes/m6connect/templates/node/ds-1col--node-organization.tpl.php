<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
global $user;
$account = user_load($user->uid);
//$node_id=arg(1);
//$nodeobj = node_load($node_id);
//$cuser = user_load($nodeobj->uid);
$summary_active = '';
$review_active = '';
$review_ratings_active = '';
if (!empty($_GET['d'])) {
  if ($_GET['d'] == 'ratings') {
    $review_active = 'in active';
  }
  if ($_GET['d'] == 'reviewratings') {
    $review_ratings_active = 'in active';
  }
}
else {
  $summary_active = 'in active';
}
?>

<article class="node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php if ($title_prefix || $title_suffix || $display_submitted || $unpublished || !$page && $title): ?>
  <header> <?php print render($title_prefix); ?>
    <?php if (!$page && $title): ?>
    <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
    <?php endif; ?>
    <?php print render($title_suffix); ?>
    <?php if ($display_submitted): ?>
    <p class="submitted"> <?php print $user_picture; ?> <?php print $submitted; ?> </p>
    <?php endif; ?>
    <?php if ($unpublished): ?>
    <mark class="unpublished"><?php print t('Unpublished'); ?></mark>
    <?php endif; ?>
  </header>
  <?php endif; ?>
  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
//    print render($content);
//******************************* Node content start *********************************//
    ?>
  <div class='company-page'>
    <div class='company-profile-content-area'>
      <div class="tab-content">
        <div role="tabpanel" class="tab-pane fade" id="Newsfeed">
          <div class='newsfeed'> 
            <!--<div class="post-heading">Share With Others</div>--> 
            <!--<div class="dashboard-block-content">
                            <pre>
                        <?php
					//print render(drupal_get_form('statuses_box'));
					//print render(drupal_get_form('statuses_box', ''));
					//$blocknews = module_invoke('views', 'block_view', 'fbss_ur_stream-block_2');
					//print render($blocknews['content']);
					//$block = module_invoke('statuses', 'block_view', 'statuses');
					//print render($block['content']);
                        ?>
                            </pre>
                        </div>--> 
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="profile">
          <div class='public-profile'>
            <div class="post-heading clearfix"><?php print $node->title; ?>
              <?php
				$companies_detail = m6connect_misc_get_user_all_companies($user->uid);
				$set_follow = TRUE;
				foreach ($companies_detail as $key => $val) {
					if ($val->nid == arg(1)) {
						$set_follow = FALSE;
					}
				}
				if (!$set_follow) {
					//$newPath = drupal_lookup_path('alias','node/'.$node->nid.'/edit');
					echo '<div class="pull-right">';
					echo l('<i class="fa fa-cog"></i>', 'node/' . $node->nid . '/edit', array('html' => TRUE));
					echo '</div>';
				}
				?>
            </div>
            <div class="dashboard-block-content">
              <?php
				print render(field_view_field('node', $node, 'field_description', array()));
				print render(field_view_field('node', $node, 'field_organization_type', array()));
				print render(field_view_field('node', $node, 'field_government_taxonomy', array()));
				print render(field_view_field('node', $node, 'field_education_taxonomy', array()));

				print render(field_view_field('node', $node, 'field_tax_exempt_type', array()));
				print render(field_view_field('node', $node, 'field_denomination', array()));
				?>
              <?php print render(field_view_field('node', $node, 'step_co_public_profile', array())); ?> </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade <?php print $summary_active; ?>" id="summary">
          <div class='company-summary'>
            <div class="post-heading clearfix">Company Summary
              <?php
				if (!$set_follow) {
					//$newPath = drupal_lookup_path('alias','node/'.$node->nid.'/edit');
					echo '<div class="pull-right">';
					echo l('<i class="fa fa-cog"></i>', 'node/' . $node->nid . '/edit', array('query' => array('costep' => 'step_co_company_summary'), 'html' => TRUE));
					echo '</div>';
				}
				?>
            </div>
            <div class="dashboard-block-content">
              <?php
				$is_organization_type = array('governmental','religious','non-profit','educational');
				$field_organization_type_value = $node->field_organization_type['und'][0]['value'];
				
				print render(field_view_field('node', $node, 'field_owner_name', array()));
				print render(field_view_field('node', $node, 'field_description', array()));
			    print render(field_view_field('node', $node, 'field_company_tagline', array()));
					if(isset($node->field_organization_type['und'][0]['value']) && !in_array( $field_organization_type_value ,$is_organization_type)){
						print render(field_view_field('node', $node, 'field_legal_structure', array()));	
					}
				
				print render(field_view_field('node', $node, 'field_legal_name', array()));
					if(isset($node->field_organization_type['und'][0]['value']) && $field_organization_type_value !='governmental' &&  $field_organization_type_value !='religious' && $field_organization_type_value !='educational'){
						print render(field_view_field('node', $node, 'field_annual_revenue', array()));
					}
					if(isset($node->field_organization_type['und'][0]['value']) && $field_organization_type_value != 'governmental' &&  $field_organization_type_value !='religious'){
						print render(field_view_field('node', $node, 'field_year_founded', array()));
					}
						
				print render(field_view_field('node', $node, 'field_number_of_employees', array()));
				if(!empty($node->field_org_phone['und'][0]['value'])) {
				$phoneNumber = $node->field_org_phone['und'][0]['value'];
			    $phoneNumberval = get_international_formatPhoneNumber($phoneNumber);
				//print render(field_view_field('node', $node, 'field_org_phone', array()));
				  print '<div class="field field-name-field-org-phone">
				         <div class="field-label">Phone:&nbsp;</div>
				         <div class="field-items">' .$phoneNumberval.'</div>
				        </div>'; 
				 }
				print render(field_view_field('node', $node, 'field_org_address', array()));
				print render(field_view_field('node', $node, 'field_website', array()));
				?>
            </div>
          </div>
        </div>
        <!--Start company Gpo here ----------- -->
         <div role="tabpanel" class="tab-pane fade" id="companygpo">
            <div class="post-heading clearfix">Add Company GPO</div>
             <div class="dashboard-block-content">
              <?php
		       $companygpoform = drupal_get_form('add_new_company_gpo_form');
			   print render($companygpoform);  ?>
            </div>
         </div>
        <!--End  company Gpo here----------- -->

        <!-- Start Messaging (Vendor Manager) -->
        <?php
          // Show messages to only company admin.
        if (_is_user_company_admin($node)):
        ?>
        <div role="tabpanel" class="tab-pane fade" id="companymsgs">
          <div class="post-heading clearfix">Company Admin Messages</div>
          <div class="dashboard-block-content">
            <?php
              // Helper function defined in vendor module.
              if (_messages_available_for_company($node)) {
                $company_messages = _get_company_messages($node);
                print render($company_messages);
              }
              else {
              print 'No messages yet!';
              }
            ?>
          </div>
        </div>

        <div role="tabpanel" class="tab-pane fade" id="companyproducts">
          <div class="post-heading clearfix">Manage Products & Categories</div>
          <div class="dashboard-block-content">
            <?php
              // Helper function defined in vendor module.
              $companyproducts = _get_company_products_content($node);
              print $companyproducts;
            ?>
          </div>
        </div>
        <!-- <div role="tabpanel" class="tab-pane fade <?php print $review_ratings_active; ?>" id="reviewratings">
          <div class="post-heading clearfix">Review ratings and notes submitted by uninvited users.</div>
          <div class="dashboard-block-content">
            <?php
              // Helper function defined in vendor module.
              $company_messages = _get_pending_ratings_notes($node);
              print render($company_messages);
            ?>
          </div>
        </div> -->
        <?php endif; ?>

        <!-- Start Ratings (Vendor Manager) -->
        <?php
          // Showing this tab, only when allowed.
          $rate_status = _is_user_allowed_to_rate(); // Defined in vendor module.
          if ($rate_status > 0):
            $rate_sub_headings = '';
            if ($rate_status != 3) {
              /*if ($rate_status == 2 || $rate_status == 5 || $rate_status == 8) {
                $rate_sub_headings = t('Congratulations, Your scores are completed.');
              }
              elseif ($rate_status == 7 || $rate_status == 9) {
                $rate_sub_headings = t('Your scores are yet to be reviewed.');
              }
              else {
                $rate_sub_headings = t('Rank this vendor now.');
              }*/
              if ($rate_status == 2) {
                $rate_sub_headings = t('Congratulations, Your scores are completed.');
              }
              else {
                $rate_sub_headings = t('Rank this vendor now.');
              }
            }
        ?>
        <div role="tabpanel" class="tab-pane fade <?php print $review_active; ?>" id="vendorratings">
          <div class="post-heading clearfix">M6 Vendor Ratings<span class="ratings-sub-heading"><?php print $rate_sub_headings; ?></span></div>
          <div id="m6-company-logo-tool" style="display:none;">
            <?php
            $theme_path = drupal_get_path('theme', 'm6connect');
            $img_src = '<img src="/' . $theme_path . '/images/icon-42.png">';
            print $img_src;
            ?>
          </div>
          <div id="current-user-img-tool" style="display:none;">
            <?php
            $user_pic = isset($account->field_user_profile_photo['und']['0']['uri']) ? $account->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';
            $img_src = '<img typeof="foaf:Image" src="' . image_style_url('user_pic_40x40', $user_pic) . '">';
            print $img_src;
            ?>
          </div>
          <div id="current-company-img-tool" style="display:none;">
            <?php
            $company_pic = isset($node->field_logo['und']['0']['uri']) ? $node->field_logo['und']['0']['uri'] : '/sites/all/themes/m6connect/images/default_company_profile.jpg';
            $img_src = '<img typeof="foaf:Image" src="' . image_style_url('user_pic_40x40', $company_pic) . '">';
            print $img_src;
            ?>
          </div>
          <div id="m6-company-logo-tool-big" style="display:none;">
            <?php
            $theme_path = drupal_get_path('theme', 'm6connect');
            $img_src = '<img src="/' . $theme_path . '/images/icon-120.png">';
            print $img_src;
            ?>
          </div>
          <div id="current-user-img-tool-big" style="display:none;">
            <?php
            $user_pic = isset($account->field_user_profile_photo['und']['0']['uri']) ? $account->field_user_profile_photo['und']['0']['uri'] : 'public://images_13.png';
            $img_src = '<img typeof="foaf:Image" src="' . image_style_url('user_image_default', $user_pic) . '">';
            print $img_src;
            ?>
          </div>
          <div id="current-company-img-tool-big" style="display:none;">
            <?php
            $company_pic = isset($node->field_logo['und']['0']['uri']) ? $node->field_logo['und']['0']['uri'] : '/sites/all/themes/m6connect/images/default_company_profile.jpg';
            $img_src = '<img typeof="foaf:Image" src="' . image_style_url('user_image_default', $company_pic) . '">';
            print $img_src;
            ?>
          </div>
          <div class="dashboard-block-content">
            <?php
            if ($rate_status == 1) {
              // Getting the rating form on the basis of current node, vendor
              // and user.
              $rating_form = drupal_get_form('rating_node_form_vendor', 'company_page');
              print render($rating_form);
            }
            elseif ($rate_status == 2) {
              // When the user had already give ratings.
              // Showing the form, and letting the user update ratings again.
              $rating_form = drupal_get_form('rating_node_form_vendor', 'rated', 'company_page');
              print render($rating_form);
            }
            elseif ($rate_status == 3) {
              // This is the case when current user is the company admin of the
              // company whose profile is opened. Giving company admin the
              // feedback form does not makes any sense.
              // Although company admin can request feedback for his company
              // to others. So generating a form for this.
              $request_link = '<div class="m6reach-request-feedback pull-left margin-bottom-10" id="m6reach-request-feedback">';
              $request_link .= '<p>' . t('As company admin, you can request other commpanies to provide feedback for your company.') . '</p>
              <p>' . t('To invite other companies please click on the Request Feedback button below.') . '</p>';
              $request_link .= l(t('Request Feedback'), 'request-feedback-company/' . $node->nid .'/nojs', array('attributes' => array('class' => array('ctools-use-modal', 'ctools-modal-onboarding-message-popup-style', 'form-submit', 'text-white'))));
              $request_link .= '</div>';

              print $request_link;
            }
            elseif ($rate_status == 4) {
              // This is the case, when the user was requested directly by the
              // company admin to rate his company.
              // Here the company and user does not have any relation with any
              // vendor.
              if (empty($_GET['vendor'])) {
                $_GET['vendor'] = 'default';
              }
              $rating_form = drupal_get_form('rating_node_form_vendor', 'vendor_default');
              print render($rating_form);
            }
            elseif ($rate_status == 5) {
              // When the user had already given ratings.
              // Showing the form, providing option to update the ratings again.
              $rating_form = drupal_get_form('rating_node_form_vendor', 'vendor_default', 'rated');
              print render($rating_form);
            }
            elseif ($rate_status == 6) {
              // When a user is just browsing the page, and has not been invited
              // by either company admin or vendor manager.
              $rating_form = drupal_get_form('rating_node_form_vendor', 'anonymous');
              print render($rating_form);
            }
            elseif ($rate_status == 7 || $rate_status == 9) {
              // When a user is just browsing the page, and has not been invited
              // by either company admin or vendor manager. But has rated the
              // current company in the past and ratings are not approved.
              $unapproved_msg = $rate_status == 7 ? t('You have already rated, but your ratings are still waiting to be reviewed by company admin. Once company admin approves, your ratings shall be counted in Average M6 Ratings. Although you may update your ratings.') : t('You have already rated, but your ratings are disapproved by company admin and shall not be counted in Average M6 Ratings. You may update your ratings, or request company admin to approve your Ratings.');

              print '<div class="ratings-unapproved-message">' . $unapproved_msg . '</div>';
              $rating_form = drupal_get_form('rating_node_form_vendor', 'anonymous', 'rated', 'unapproved');
              print render($rating_form);
            }
            elseif ($rate_status == 8) {
              // When a user is just browsing the page, and has not been invited
              // by either company admin or vendor manager. But has rated the
              // current company in the past and ratings are approved.
              $rating_form = drupal_get_form('rating_node_form_vendor', 'anonymous', 'rated', 'approved');
              print render($rating_form);
            }
            ?>
          </div>
         </div>
       <?php endif; ?>
        <!-- End Ratings (Vendor Manager) -->
        
        <div role="tabpanel" class="tab-pane fade" id="diversity">
          <div class='diversity-summary'>
            <div class="post-heading clearfix">Diversity
              <?php
				if (!$set_follow) {
					//$newPath = drupal_lookup_path('alias','node/'.$node->nid.'/edit');
					echo '<div class="pull-right">';
					echo l('<i class="fa fa-cog"></i>', 'node/' . $node->nid . '/edit', array('query' => array('costep' => 'step_co_supplier_diversity'), 'html' => TRUE)); //http://dev-m6connect.pantheon.io/node/1250/edit?costep=step_co_supplier_diversity
					echo '</div>';
				}
				
				$cirtificate = m6connect_company_get_circtficat($node);
				if ($cirtificate) {
					echo '<div class="pull-right">';
					echo '<img src="/sites/all/themes/m6connect/images/certificate2.png" alt="cirtificate" style="width:24px" />';
					echo '</div>';
				}
				?>
            </div>
            <div class="dashboard-block-content">
            
             <!--<label>Diversity Credentials:</label>--> 
            <?php
			  
			  if(($node->nid) && is_numeric($node->nid)){  
				  
			   $diversityresult = get_diversity_credentials_doc_by_comapny_nid($node->nid);
			   
			   //print "<pre>"; print_r($result);
			   
			     foreach($diversityresult as $diverout){ 
					
					$credential_title = $diverout->credential_title;
					$credential_fid = $diverout->credential_fid;
					$credentialfile = file_load($credential_fid);
					$filecredentialuri = $credentialfile->uri;
					$filetypechk = $credentialfile->type;
					
					//print "<pre>"; print_r($credentialfile);
				  
				
				
				   if($filetypechk == 'image'){	  
				  $docimages = (isset($credentialfile->uri)) ? theme('image_style', array('style_name' => 'pic_60x60', 'path' => $credentialfile->uri, 'getsize' => TRUE)) : ''; 
				  }
				 
				  if($filetypechk == 'document'){	    
				  $docimages1 = file_create_url($filecredentialuri);
				  $docimages = '<a href="'.$docimages1.'">'.$credentialfile->filename.'</a>';
				  }
				  
				echo  '<div class="diversitydoc row margin-5" style="border-bottom: 1px solid #CCC;margin-bottom: 5px; padding:5px 0">
				       <div style="width:400px" class="diversity_tile col-md-4 padding-5 margin-bottom-10">'.$credential_title.'</div>
				       <div style="width:100px" class="diversity_docfile col-md-8 padding-5 margin-bottom-10">'.$docimages.'</div> 
				       </div>';
				 
				}  
			 } 
			 
			 ?> 
             
			<?php //print render(field_view_field('node', $node, 'field_diversity_credentials', array())); ?>
             <?php //print render(field_view_field('node', $node, 'field_diversity_program', array())); ?>
              </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="location">
          <div class='locations'>
            <div class="post-heading clearfix">
              <?php
				if (!$set_follow) {
					//$newPath = drupal_lookup_path('alias','node/'.$node->nid.'/edit');
					echo '<div class="pull-right">';
					echo l('<i class="fa fa-cog"></i>', 'node/' . $node->nid . '/edit', array('query' => array('costep' => 'step_co_location'), 'html' => TRUE));
					echo '</div>';
				}
				?>
            </div>
            <div class="dashboard-block-content"> <?php print render(field_view_field('node', $node, 'field_comp_locations', array())); ?> </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="businessTypes">
          <div class='business-types'>
            <div class="post-heading clearfix">Business Types
              <?php
				if (!$set_follow) {
					//$newPath = drupal_lookup_path('alias','node/'.$node->nid.'/edit');
					echo '<div class="pull-right">';
					echo l('<i class="fa fa-cog"></i>', 'node/' . $node->nid . '/edit', array('html' => TRUE));
					echo '</div>';
				}
				?>
            </div>
            <div class="dashboard-block-content">
              <?php
				print render(field_view_field('node', $node, 'field_facilities_construction', array()));
				print render(field_view_field('node', $node, 'field_regions', array()));
				print render(field_view_field('node', $node, 'field_industry_naicss', array()));
				print render(field_view_field('node', $node, 'field_products_service_unspsc', array()));
				?>
            </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="employees">
          <div class='employees'>
            <div class="post-heading clearfix">Employees</div>
            <div class="dashboard-block-content"> <?php print render(field_view_field('node', $node, 'field_number_of_employees', array())); ?> </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="view_all_emp">
          <div class='view_all_emp'>
            <div class="post-heading clearfix">Employees</div>
            <div class="dashboard-block-content">
              <div class="user-connection-outer"> <?php print views_embed_view('company_profile', 'block'); ?> </div>
            </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="view_all_pro">
          <div class='view_all_pro'>
            <div class="post-heading clearfix">Projects</div>
            <div class="dashboard-block-content">
              <div class="user-connection-outer row margin-5"> <?php print views_embed_view('public_posted_projects', 'block_4'); ?> </div>
            </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="view_all_rfp">
          <div class='view_all_rfp'>
            <div class="post-heading clearfix">RFPs</div>
            <div class="dashboard-block-content">
              <div class="user-connection-outer row margin-5"> <?php print views_embed_view('public_posted_projects', 'block_5'); ?> </div>
            </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="view-more-about">
          <div class='view-more-about'>
            <div class="post-heading clearfix">Contact Information
              <?php
				if (!$set_follow) {
					//$newPath = drupal_lookup_path('alias','node/'.$node->nid.'/edit');
					echo '<div class="pull-right">';
					echo l('<i class="fa fa-cog"></i>', 'node/' . $node->nid . '/edit', array('html' => TRUE));
					echo '</div>';
				}
				?>
            </div>
            <div class="dashboard-block-content company-view">
              <div class="content block">
                <div class="company-info margin-bottom-10 clearfix">
                  <?php
					$field_incorporated_state = render(field_view_field('node', $node, 'field_incorporated_state', array('label' => 'hidden')));
					$field_incorporated_country = render(field_view_field('node', $node, 'field_incorporated_country', array('label' => 'hidden')));
					if (!empty($field_incorporated_state) && !empty($field_incorporated_country)) {
					?>
                  <div class="pull-outer clearfix margin-bottom-10">
                    <div class="pull-left"><i class="fa fa-map-marker"></i></div>
                    <div class="pull-right">
                      <?php
						$org_add = render(field_view_field('node', $node, 'field_incorporated_state', array('label' => 'hidden')));
						$org_add2 = render(field_view_field('node', $node, 'field_incorporated_country', array('label' => 'hidden')));
						//echo '<a href="#location" aria-controls="location" role="tab" data-toggle="tab"><i class="fa fa-map-marker"></i>'.$org_add.'</a>';
						/////
						$add = $node->field_incorporated_state['und'][0]['value'] . ', ';
						$add.=$node->field_incorporated_country['und'][0]['value'];
						print l($add, '', array('html' => TRUE, 'attributes' => array('title' => $org_add, 'class' => 'profile-tab-open out-side field', 'aria-controls' => 'location', 'role' => 'tab', 'data-toggle' => 'tab'), 'fragment' => 'location'));
						/////
						//echo '<div class="pullleft">';
						//print l($org_add, '', array('html' => TRUE, 'attributes' => array('title' => $org_add,'aria-controls'=>'location','role'=>'tab','data-toggle'=>'tab'),'fragment' => 'location'));
						//echo '</div>';
						// echo '<div class="pullright">'; 
						//print l($org_add2, '', array('html' => TRUE, 'attributes' => array('title' => $org_add,'aria-controls'=>'location','role'=>'tab','data-toggle'=>'tab'),'fragment' => 'location'));
						//echo '</div>';
						?>
                    </div>
                  </div>
                  <?php } ?>
                  <?php
					$field_facilities_construction = render(field_view_field('node', $node, 'field_facilities_construction', array('label' => 'hidden')));
					if (!empty($field_facilities_construction)) {
					?>
                  <div class="pull-outer clearfix margin-bottom-10">
                    <div class="pull-left"><i class="fa fa-building-o"></i></div>
                    <div class="pull-right"> <?php print $field_facilities_construction; ?></div>
                  </div>
                  <?php } ?>
                  <?php
					$field_website = render(field_view_field('node', $node, 'field_website', array('label' => 'hidden')));
					if (!empty($field_website)) {
					?>
                  <div class="pull-outer clearfix margin-bottom-10">
                    <div class="pull-left"><i class="fa fa-envelope-o"></i></div>
                    <div class="pull-right"> <?php print $field_website; ?></div>
                  </div>
                  <?php } ?>
                  <?php
					$field_company_email = render(field_view_field('node', $node, 'field_company_email', array('label' => 'hidden')));
					if (!empty($field_company_email)) {
					?>
                  <div class="pull-outer clearfix margin-bottom-10">
                    <div class="pull-left"><i class="fa fa-envelope-o"></i></div>
                    <div class="pull-right"> <?php print render(field_view_field('node', $node, 'field_company_email', array('label' => 'hidden'))); ?></div>
                  </div>
                  <?php } ?>
                  <?php
					$field_org_phone = render(field_view_field('node', $node, 'field_org_phone', array('label' => 'hidden')));
					if (!empty($node->field_org_phone['und'][0]['value'])) {	
					 $phoneNumber = $node->field_org_phone['und'][0]['value'];
		             $phoneNumberval = get_international_formatPhoneNumber($phoneNumber);	
					?>
                  <div class="pull-outer clearfix margin-bottom-10">
                    <div class="pull-left"> <i class="fa fa-phone"></i></div>
                    <div class="pull-right"><?php print $phoneNumberval; ?> </div>
                  </div>
                  <?php } ?>
                  <?php
					$field_org_fax = render(field_view_field('node', $node, 'field_org_fax', array('label' => 'hidden')));
					if (!empty($field_org_fax)) {
					?>
                  <div class="pull-outer clearfix margin-bottom-10">
                    <div class="pull-left"><i class="fa fa-fax"></i></div>
                    <div class="pull-right"><?php print $field_org_fax; ?></div>
                  </div>
                  <?php } ?>
                </div>
              </div>
            </div>
            <div class="post-heading clearfix">Social Media</div>
            <div class="dashboard-block-content">
              <div class="row margin-5 text-center left-social-icons">
                <div class="col-md-3 col-xs-3 padding-5">
                  <?php
						//print render(field_view_field('node', $node, 'field_facebook', array('label' => 'hidden'))); 
					  if (isset($node->field_facebook['und']) && isset($node->field_facebook['und'][0]['value']) && !empty($node->field_facebook['und'][0]['value'])) {
						  $flink = $node->field_facebook['und'][0]['value'];
						  echo l('<i class="fa fa-facebook-square"></i>', $flink, array('html' => true));
					  }
					  ?>
                </div>
                <div class="col-md-3 col-xs-3 padding-5">
                  <?php
						//print render(field_view_field('node', $node, 'field_twitter', array('label' => 'hidden'))); 
						if (isset($node->field_twitter['und']) && isset($node->field_twitter['und'][0]['value']) && !empty($node->field_twitter['und'][0]['value'])) {
							$tlink = $node->field_twitter['und'][0]['value'];
							echo l('<i class="fa fa-twitter"></i>', $tlink, array('html' => true));
						}
						?>
                </div>
                <div class="col-md-3 col-xs-3 padding-5">
                  <?php
						//print render(field_view_field('node', $node, 'field_instagram', array('label' => 'hidden'))); 
						if (isset($node->field_instagram['und']) && isset($node->field_instagram['und'][0]['value']) && !empty($node->field_instagram['und'][0]['value'])) {
							$ilink = $node->field_instagram['und'][0]['value'];
							echo l('<i class="fa fa-instagram"></i>', $ilink, array('html' => true));
						}
						?>
                </div>
                <div class="col-md-3 col-xs-3 padding-5">
                  <?php
						  //print render(field_view_field('node', $node, 'field_instagram', array('label' => 'hidden'))); 
						  if (isset($node->field_skype['und']) && isset($node->field_skype['und'][0]['value']) && !empty($node->field_skype['und'][0]['value'])) {
							  $ilink = $node->field_skype['und'][0]['value'];
							  echo l('<i class="fa fa-skype"></i>', $ilink, array('html' => true));
						  }
						  ?>
                </div>
                <div class="col-md-3 col-xs-3 padding-5">
                  <?php
						//print render(field_view_field('node', $node, 'field_instagram', array('label' => 'hidden'))); 
						if (isset($node->field_linkdin['und']) && isset($node->field_linkdin['und'][0]['value']) && !empty($node->field_linkdin['und'][0]['value'])) {
							$ilink = $node->field_linkdin['und'][0]['value'];
							echo l('<i class="fa fa-linkedin-square"></i>', $ilink, array('html' => true));
						}
						?>
                </div>
              </div>
            </div>
          </div>
        </div>
        <div role="tabpanel" class="tab-pane fade" id="tab-photos">
          <div class='tab-photos'>
            <div class="post-heading clearfix">Photos</div>
            <div class="dashboard-block-content">
              <div class="user-connection-outer row margin-5 grid js-masonry">
                <?php
					/////////////////v4/////////////////////
				  $nid = $node->nid;
				  $nid = arg(1);
				  $fids = fn_get_own_shared_images($nid);

				  foreach ($fids as $key) {
					  echo '<div class="grid-item"><a href="javascript:"  onclick="updateimage(\'/download/attachments/' . $key . '\')"  data-toggle="modal" data-target="#myModal"><img src="/download/attachments/' . $key . '"/ alt="photo" /></a></div>';
				  }
					////////////image////////////////
				  ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <?php
//print render(field_view_field('node', $node, 'field_logo', array('label'=>'hidden')));	
//print render(field_view_field('node', $node, 'field_company_profile_cover_img', array('label'=>'hidden')));
//print render(field_view_field('node', $node, 'field_number_of_employees', array()));
//print render(field_view_field('node', $node, 'step_co_public_profile', array()));
//echo "<h1><b>company summary</b></h1></br>";
//print $node->title;
//print render(field_view_field('node', $node, 'field_owner_name', array()));
//print render(field_view_field('node', $node, 'field_description', array()));
//print render(field_view_field('node', $node, 'field_legal_structure', array()));
//print render(field_view_field('node', $node, 'field_legal_name', array()));
//print render(field_view_field('node', $node, 'field_year_founded', array()));
//print render(field_view_field('node', $node, 'field_annual_revenue', array()));
//print render(field_view_field('node', $node, 'field_number_of_employees', array()));
//print render(field_view_field('node', $node, 'field_org_phone', array()));
//print render(field_view_field('node', $node, 'field_org_address', array()));
//print render(field_view_field('node', $node, 'field_website', array()));
//echo "<h1><b>Supplier diversity</b></h1></br>";
//print render(field_view_field('node', $node, 'field_diversity_program', array('label'=>'hidden')));
//echo "<h1><b>Location </b></h1></br>";
//print render(field_view_field('node', $node, 'step_co_location', array()));
//print render(field_view_field('node', $node, 'field-location-name', array()));
//print render(field_view_field('node', $node, 'field_comp_locations', array()));
//echo "<h1><b>Business types </b></h1></br>";
//print render(field_view_field('node', $node, 'field_facilities_construction', array()));
//print render(field_view_field('node', $node, 'field_regions', array()));
//print render(field_view_field('node', $node, 'field_industry_naicss', array()));
//print render(field_view_field('node', $node, 'field_products_service_unspsc', array()));
//******************************* Node content end *********************************//	
    ?>
  <?php print render($content['links']); ?> <?php print render($content['comments']); ?> </article>
<script>
    jQuery('document').ready(function () {
        //fews feed show
        jQuery('.profile-tab-open').click(function () {
            //debugger;
            if (this.classList[1] == "out-side") {
                jQuery('#middle-content-nav li').each(function () {
                    jQuery(this).removeClass('active');
                });
            }
            jQuery('#block-statuses-statuses').hide();
        });
        jQuery('#newsfeed-open').click(function () {
            jQuery('#user-feeds .tab-pane').each(function () {
                jQuery(this).removeClass('active');
                jQuery(this).removeClass('in');
            });
            jQuery('#block-statuses-statuses').show();
        });
				
				if (jQuery('body').hasClass('node-type-organization')) {
					jQuery('#block-statuses-statuses').hide();
				}
				
				
        grid = jQuery('.grid').masonry({
            // specify itemSelector so stamps do get laid out
            itemSelector: '.grid-item',
            columnWidth: 172
        });
        jQuery('#photo-contaner').click(function () {
            setTimeout(function () {
                grid.masonry();
            }, 200);
        });
        jQuery('#user-Notification').click(function () {
            setTimeout(function () {
//                jQuery('#user-Notification').parent().toggleClass('open');
            }, 200);

        });
<?php
$groups = og_get_groups_by_user();
//echo '<pre>';
//print_r(arg(1));
//print_r($groups);
//die('end');
if (in_array(arg(1), $groups['node'])) {
    ?>
            jQuery('#block-statuses-statuses').prepend('<div class="company-status-title company-status-title-inner">Share With Others </div>');
    <?php
} else {
    ?>
            jQuery('#block-statuses-statuses').prepend('<div class="company-status-title company-status-title-inner">News Feeds </div>');

    <?php
}
?>
        jQuery('#statuses-box--2').prepend('<div class="user-profile-share-image"><?php print $rcuser_profile_photo = (isset($cuser->field_user_profile_photo['und'])) ? theme('image_style', array('style_name' => 'dashboard-user-feed-pic-img_52_52', 'path' => $cuser->field_user_profile_photo['und'][0]['uri'], 'getsize' => TRUE)) : ''; ?></div>');
        var htm = jQuery('#share-connection').html();
        jQuery('#block-statuses-statuses').prepend(htm);
        jQuery('#share-connection').html('');
        jQuery('#block-statuses-statuses').css('position', 'relative');
        jQuery('#block-statuses-statuses .share-container').css('position', 'absolute');
        jQuery('#block-statuses-statuses .share-container').css('top', '97px');
        jQuery('#block-statuses-statuses .share-container').css('left', '360px');
        // jQuery(".dropdownF").dropdown();

    });
    function updateimage(path) {
        jQuery('#model-img').attr('src', '');
        jQuery('#model-img').attr('src', path);
    }
</script> 
