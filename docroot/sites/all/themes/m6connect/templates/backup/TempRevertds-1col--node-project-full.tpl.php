<?php
/**
 * @file
 * Returns the HTML for a node.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728164
 */
 
 global $user;
 
?>

<article class=" dsr node-<?php print $node->nid; ?> <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
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
    //print render($content); 
	
	//******************************* Node content start *********************************//
    /*		
	echo 'project layout ';
	print $node->title;
	print render(field_view_field('node', $node, 'field_project_address_new', array()));	
	print render(field_view_field('node', $node, 'field_interested_list_mrk', array()));
	print render(field_view_field('node', $node, 'field_images', array()));
	print render(field_view_field('node', $node, 'og_group_ref', array()));
	print render(field_view_field('node', $node, 'field_project_address_new', array()));
	print render(field_view_field('node', $node, 'field_project_address', array()));
	print render(field_view_field('node', $node, 'field_public_description', array()));
	print render(field_view_field('node', $node, 'field_status', array()));
	print render(field_view_field('node', $node, 'field_complete_description', array()));
	print render(field_view_field('node', $node, 'field_pro_bidding_info', array()));
	print render(field_view_field('node', $node, 'field_projects_keywords', array()));
	
	print render(field_view_field('node', $node, 'field_project_diversity_type', array()));
	*/
	
	////////////////// tab access functionality start ////////////////////////
	$colaborateTabAccess = $inviteTabAccess = $interestedCompAccess = $interstedBidderAccess = 1;
	$aditional_user = m6connect_projects_uids_from_list($node);
    $aditional_user[] = $node->uid;
    $aditional_user = array_merge($aditional_user, _get_current_company_users($node->uid));
    if (!in_array($user->uid, $aditional_user)) {
	  $colaborateTabAccess = 0; 
	  $inviteTabAccess = 0;
	}
	
    if ($node->field_project_public['und'][0]['value'] == 0) {
      $cnodeUid = $node->uid;
      $companyusers = array();
      $companyusers = get_company_users_list_by_uid($cnodeUid);
      $companyusers = array_merge($companyusers, $aditional_user);
      $cmpyUserUids = array();
      $items = field_get_items('node', $node, 'field_rfp_invite_comapnies');
      foreach ($items as $item) {
        $fc = field_collection_field_get_entity($item);
        $inviteddata = (isset($fc->field_rfp_company_nid_email['und'])) ? $fc->field_rfp_company_nid_email['und'][0]['value'] : '';
        if (!empty($inviteddata) && is_numeric($inviteddata)) {
          $companyNode = node_load($inviteddata);
          $temp = og_get_group_members_properties($companyNode, array(), 'members__' . OG_STATE_ACTIVE, 'node');
          $cmpyUserUids = array_merge((array) $cmpyUserUids, (array) $temp);
        } else if (!empty($inviteddata)) {
          $temp = user_load_by_mail($inviteddata);
          if ($temp && isset($temp->uid)) {
            $cmpyUserUids = array_merge((array) $cmpyUserUids, array($temp->uid));
          }
        }
      }
      if ((!(array_key_exists(3, $user->roles)) || (array_key_exists(6, $user->roles)))) {
        if ((!in_array($user->uid, $companyusers)) && (!in_array($user->uid, $cmpyUserUids))) {
          /*$data = field_info_instances("node", 'project');

          foreach ($data as $fieldname => $fieldval) { //pre($fieldname);	
            if (!in_array($fieldname, array('field_public_description', 'og_group_ref', 'field_project_diversity_type'))) {
              $node->content[$fieldname]['#access'] = false;
            }
          }*/
          if (!in_array($user->uid, $aditional_user)) {
		    $colaborateTabAccess = $inviteTabAccess = $interestedCompAccess = $interstedBidderAccess = 0;	
          }
        }
      }
    }
    if ($node->uid != $user->uid && isset($user->roles[12]) && in_array($user->uid, _get_current_company_users($node->uid))) {
	  $colaborateTabAccess = $inviteTabAccess = $interstedBidderAccess = 0;	   
    }
    if ($node->uid != $user->uid && !(isset($user->roles[3]) || isset($user->roles[6]))){
      $colaborateTabAccess = 0;
    }
	$nodeview = node_view($node);
	//pre($nodeview);
	//pre('dfd');pre($content);
	
  ?>
  <!--  <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script> 
  <script src="http://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script> --> 
  <script type="text/javascript" src="/sites/all/themes/m6connect/js/tab.js"></script>
  <div class='project_page'>
    <div class="clearfix">
      <div class='col-md-12 col-sm-12 col-xs-12 company-header'> <?php print render(field_view_field('node', $node, 'field_images', array('label'=>'hidden'))); ?>
        <div class='company-header-stats clearafix'>
          <div class='row'>
            <div class='col-md-3 col-sm-3 col-xs-12 quick-fact-container quick-fact-logo'> </div>
            <div class='col-md-6 col-sm-6 col-xs-12 quick-fact-container'>
              <div class='quick-facts'><?php print $node->title;?></div>
              <div class='quick-fact-title'>Skanska USA</div>
            </div>
            <div class='col-md-3 col-sm-3 col-xs-12 quick-fact-container'> 
              <!--<div class='interactions-menu text-center'><a class='connect' href='#' title='Connect with Skanska!'>Follow</a>
                <a class='send-message' href='#' title='Send a Message to Skanska!'>Send Message</a></div>--> 
            </div>
          </div>
        </div>
      </div>
    </div>
    <div class='row'>
      <div id="pro-left-column" class='col-md-3 col-sm-3 col-xs-12'>
        <div class='company-profile-navigation project-profile-nav'>
          <ul class="nav nav-tabs profile-navigation-tabs" role="tablist">
            <li class="active"><a href="#Newsfeed" aria-controls="Newsfeed" role="tab" data-toggle="tab">Newsfeed <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <li><a href="#overview" aria-controls="overview" role="tab" data-toggle="tab">Project Overview <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <li><a href="#team" aria-controls="team" role="tab" data-toggle="tab">Project Team <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <li><a href="#diversity" aria-controls="diversity" role="tab" data-toggle="tab">Supplier Diversity <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <li><a href="#progress" aria-controls="progress" role="tab" data-toggle="tab">Project Progress <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <?php
            if ($interestedCompAccess) {
			?>
            <li><a href="#intcomp" aria-controls="intcomp" role="tab" data-toggle="tab">Interested Companies <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <?php 
			}
			if ($interstedBidderAccess) {
			?>
            <li><a href="#ibidders" aria-controls="ibidders" role="tab" data-toggle="tab">Interested Bidders <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <?php
			}
			?>
            <li><a href="#rfps" aria-controls="rfps" role="tab" data-toggle="tab">RFPs <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <?php
            if ($inviteTabAccess) {
			?>
            <li class="cust-pro-invite-tab"><a href="#invcomp" aria-controls="invcomp" role="tab" data-toggle="tab">Invite Companies <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <?php 
			}
			if ($colaborateTabAccess) {
			?>
            <li class="cust-pro-collaborate-tab"><a href="#collaborate" aria-controls="collaborate" role="tab" data-toggle="tab">Collaboration <span class="pull-right"><i class="fa fa-chevron-down"></i><i class="fa fa-chevron-right"></i></span></a></li>
            <?php } ?>
          </ul>
          <ul class="request-information">
            <li>
              <h3>Project Contact Information</h3>
              <hr>
              <div class="profile-navigation-map">
                <?php
                  $NodeCmpNid = _get_company_nid_by_group_content($node); //pre($NodeCmpNid);
                  $CompNode = node_load($NodeCmpNid);
                  $pimgpath = (isset($CompNode->field_logo['und']) && !empty($CompNode->field_logo['und'][0]['uri'])) ? $CompNode->field_logo['und'][0]['uri'] : 0;
                  if ($pimgpath) {
                    $pimagepath = image_style_url('thumbnail', $pimgpath);
                    echo '<img src="' . $pimagepath . '" /><br>';
                  }
                  
                ?>
                <div class="com-info">
                  <?php //$add = render(field_view_field('node', $node, 'field_project_address_new', array())); 
				//echo $add;
				$address = $comp = $tel = $email = '';
                $region = _get_company_region_address($CompNode);
                if(isset($CompNode->field_org_address['und'])){ //pre($CompNode->field_org_address); 
                  $address = (!empty($CompNode->field_org_address['und'][0]['thoroughfare']))?$CompNode->field_org_address['und'][0]['thoroughfare']:'';
                  $address .= (!empty($CompNode->field_org_address['und'][0]['locality']))?', '.$CompNode->field_org_address['und'][0]['locality']:'';
                }
				if(!empty($address)){
				  echo 'Contact: '.$address.'<br>';	
				}
				echo 'Company: '.$CompNode->title.'<br>';
                if(isset($CompNode->field_org_phone['und']) && !empty($CompNode->field_org_phone['und'][0]['value'])){ 
                  $tel = $CompNode->field_org_phone['und'][0]['value'];
				  echo 'Telephone: '.$tel.'<br>';  
                }//pre($CompNode->field_company_email['und']);
				if(isset($CompNode->field_company_email['und']) && !empty($CompNode->field_company_email['und'][0]['email'])){ 
                  $email = $CompNode->field_company_email['und'][0]['email'];
				  echo 'E-mail: '.$email.'<br>';  
                }
                			
				?>
                </div>
              </div>
            </li>
            <li style="margin-top:20px; background-color:#337ab7; color:white; font-weight: 500; text-align: center; font-size: 1.3em; text-transform: uppercase; padding: 8px;"> Request Information </li>
            <li class="express">
              <?php 
			  $account = menu_get_object('user');
              print flag_create_link('interested', $node->nid);?>
            </li>
          </ul>
        </div>
      </div>
      <div id="pro-mid-column" class='col-md-6 col-sm-6 col-xs-12'>
        <div class='company-profile-content-area'>
          <div class="tab-content">
            <div role="tabpanel" class="tab-pane fade in active" id="Newsfeed">
              <div class='newsfeed'>
                <h1>Latest News</h1>
                <div class="row news-item">
                  <div class="col-lg-12">
                    <div class="row">
                      <div class="col-lg-2" style="padding-top: 10px;"> <img src="http://xray-studios.com/images/skanska-profile-photo.png" alt="Skanska USA"></div>
                      <div class="col-lg-10" style="padding-top: 10px;"> <span style="color:#337ab7; font-weight:600;">Skanska USA</span><br>
                        <span style="font-size: .8em; color:#717171; font-style: italic;">May 29, 2014 10:30 AM CET</span> </div>
                    </div>
                    <hr style="width:90%;">
                    <h3>Skanska appointed preferred bidder for the Terminal Replacement Project at LaGuardia Airport in New York City</h3>
                    <p> LaGuardia Gateway Partners, in which Skanska is a partner, has been selected by the Port Authority of New York and New Jersey, USA, as the preferred bidder on the Terminal Replacement Project at LaGuardia Airport. </p>
                    <p> The PPP-contract includes taking over operations of the existing Central Terminal Building and designing, building, financing, operating and maintaining a new replacement terminal for a lease term through 2050. The selection enables LaGuardia Gateway Partners to enter into negotiation with the client in order to finalize the lease agreement and begin the process of achieving commercial and financial close. </p>
                    <p> The project is expected to be financed using equity, debt, passenger facility charges, retail and airline revenues. The total value of the construction contract is estimated by the Port Authority of New York and New Jersey to about USD 3.6 billion, about SEK 30.5 billion. </p>
                    <p> Skanska’s share of the equity investment will be up to 40 percent and the share of the construction contract is 70 percent, which will be divided between Skanska USA Building and Skanska USA Civil. No order bookings or investments will be accounted for until financial close, which is expected to be in 2016. Construction is expected to start immediately following financial close. </p>
                    <p> Skanska Infrastructure Development is a leader in the global Public Private Partnerships (PPP) market. The business unit invests in, develops and operates roads, hospitals, schools, power plants and other social infrastructure in partnership with the public sector. </p>
                    <p> <strong>Contact information</strong><br>
                      Contact: Mary Humphreys, Communications Manager<br>
                      Company: Skanska Infrastructure Development<br>
                      Telephone: +1 703 340 1235<br>
                      E-mail: Mary Humphreys » </p>
                  </div>
                </div>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="overview">
              <div class='public-profile'>
                <h1><?php print $node->title; ?></h1>
                <?php //pre($node); 
			      print render(field_view_field('node', $node, 'field_project_address_new', array()));
	              print render(field_view_field('node', $node, 'field_project_address', array()));
	              print render(field_view_field('node', $node, 'field_public_description', array()));
	              print render(field_view_field('node', $node, 'field_status', array()));
	              print render(field_view_field('node', $node, 'field_complete_description', array()));
	              print render(field_view_field('node', $node, 'field_pro_bidding_info', array()));
	              print render(field_view_field('node', $node, 'field_projects_keywords', array()));
                ?>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="team">
              <div class='employees'>
                <h1>Project Team</h1>
                <div class='row'>
                  <div class='col-lg-4'>
                    <div class='employee-tile'>
                      <div class='image'><img alt='persons name' src='https://hcware1.blob.core.windows.net/documents/corporate-business-headshots-in-Bellevue-Kirkland-Redmond-Seattle.jpg'></div>
                      <div class='employee-info'><strong>Jane Doe</strong> <em>VP of Customer Relations</em></div>
                      <div style='text-align: center; margin-top:20px;'><a href='#'>View Profile</a></div>
                    </div>
                  </div>
                  <div class='col-lg-4'>
                    <div class='employee-tile'>
                      <div class='image'><img alt='persons name' src='http://xray-studios.com/images/josh.jpg'></div>
                      <div class='employee-info'><strong>Joshua Barnes, M.S. PMP</strong> <em>Consultant</em></div>
                      <div style='text-align: center; margin-top:20px;'><a href='http://dev-m6connect.pantheon.io/content/joshua-barnes-ms-pmp'>View Profile</a></div>
                    </div>
                  </div>
                  <div class='col-lg-4'>
                    <div class='employee-tile'>
                      <div class='image'><img alt='persons name' src='http://www.slrlounge.com/wp-content/uploads/2013/07/412-620x412.jpg'></div>
                      <div class='employee-info'><strong>John Doe</strong> <em>Project Manager</em></div>
                      <div style='text-align: center; margin-top:20px;'><a href='#'>View Profile</a></div>
                    </div>
                  </div>
                </div>
                <div class='row'>
                  <div class='col-lg-4'>
                    <div class='employee-tile'>
                      <div class='image'><img alt='persons name' src='http://files.stablerack.com/WebFiles/79923/Traditional-Corporate-Headshot-Blog.jpg'></div>
                      <div class='employee-info'><strong>John Doe</strong> <em>Director</em></div>
                      <div style='text-align: center; margin-top:20px;'><a href='#'>View Profile</a></div>
                    </div>
                  </div>
                  <div class='col-lg-4'>
                    <div class='employee-tile'>
                      <div class='image'><img alt='persons name' src='http://cdn.photographyproject.com.au/wp-content/uploads/2013/01/corporate-headshot-photography-perth.jpg'></div>
                      <div class='employee-info'><strong>John Doe</strong> <em>VP of Operations</em></div>
                      <div style='text-align: center; margin-top:20px;'><a href='#'>View Profile</a></div>
                    </div>
                  </div>
                  <div class='col-lg-4'>&nbsp;</div>
                </div>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="diversity">
              <h1>Supplier Diversity</h1>
              <div class='diversity-summary'> <?php print render(field_view_field('node', $node, 'field_project_diversity_type', array())); ?> </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="progress">
              <div class='locations'>
                <h1>progress</h1>
                <p style="text-align: center; width:100%;"> <img src="http://www.panynj.gov/photo/airports/c06.jpg"></p>
                <p> <strong>Milestones to Date</strong></p>
                <ul>
                  <li> May 2015: The Port Authority's Board of Commissioners voted unanimously to begin the first phase of a new vision for an overall redevelopment of LaGuardia Airport by selecting LaGuardia Gateway Partners to develop a $3.6 billion world-class facility to serve approximately 50% of the passenger volume at LaGuardia. </li>
                  <li> December 2014: A Finding of No Significant Impact (FONSI) decision for the environmental assessment from the FAA was received, a major milestone critical to the demolition of the existing Hangars 2 &amp; 4 and ancillary support buildings. This will make way for new Central Terminal Building and aeronautical apron area.</li>
                  <li> November 2014: Erection of the precast concrete structure for the East Garage, was completed with the last section installed. The overall structure stands at 6 stories high and will provide 1100 public parking spaces when opened in the 2nd quarter of 2015. </li>
                  <li> July 2014: The East End Substation (EES) foundation is complete with the concrete structure erected. The new three-story Substation with an electrical capacity of 24 MW, would provide for more efficient handling of growing electrical demand and would accommodate electricity for future growth, including a new Central Terminal Building. </li>
                  <li> November 13, 2013: Design and construction of West Parking Garage authorized by PANYNJ Board of Commissioners. </li>
                  <li> September 18, 2013: Demolition of Hangars 2 and 4 and associated support structure authorized by PANYNJ Board of Commissioners pending environmental review. </li>
                  <li> July 24, 2013: Site, building and utility infrastructure program authorized by PANYNJ Board of Commissioners. </li>
                  <li> June 7, 2013: East End Substation construction commences. </li>
                  <li> April 24, 2013: Runway Safety Area Enhancement Program authorized by PANYNJ Board of Commissioners. </li>
                  <li> March 20, 2013: Design and construction of East Parking Garage authorized by PANYNJ Board of Commissioners. </li>
                  <li> December 6, 2012: Phase III Planning for Program authorized by PANYNJ Board of Commissioners. </li>
                  <li> November 27, 2012: East End Substation Foundation contract awarded. </li>
                  <li> August 1, 2012: East End Substation Foundation and Building contracts authorized by PANYNJ Board of Commissioners. </li>
                </ul>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="intcomp">
              <div class='locations'>
                <h1>Interested Companies</h1>
                <?php
                $nid = $node->nid;
                $nuid = $node->uid;
                $cmpcall = in_array($user->uid,_get_current_company_users($nuid));
                $cmpcall2 = in_array($user->uid, loadadinitation_project_user(node_load($nid)));
                if($user->uid == $nuid || $cmpcall || $cmpcall2) {
                  $userids = temprevertdsFlaggingQuery($nid);  
                  echo '<div class="cust-diversity-interested-co">';
                  $countcompany = 0;
                  foreach($userids as $k => $uid) {
                    $cuser = user_load($uid);	
                    $user_groups = og_get_groups_by_user($cuser, 'node');	
                    //pre($user_groups);
                    foreach($user_groups as $n => $gnid) { 
                      $countcompany++;
                  	  /****changed ****/
                    	$gnode = node_load($gnid);
                    	//echo  '<div>'.l($gnode->title, 'node/'.$gnid).'</div>'; 
                    	$isCompanyIndividual = is_company_individual_flag($gnid);
                    	if(!$isCompanyIndividual && $gnode->uid == $uid){
                    	  $comp =  '<div>'.l($gnode->title, 'node/'.$gnid).'</div>'; 
                    	  break;  	
                    	} else if($isCompanyIndividual && $gnode->uid == $uid){
                    	  $comp =  '<div>'.l($gnode->title, 'node/'.$gnid).'</div>';	
                    	}
                    }
                    echo $comp;
                  }
                  if($countcompany == 0){
                    echo '<div>At this time, no Companies have expressed interest on this project.</div>';
                  }
                  echo '</div>';
                }
                ?>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="ibidders">
              <div class='locations'>
                <h1>Interested Bidders</h1>
                <?php
                $cmpcall = in_array($user->uid, _get_current_company_users($node->uid));
                $cmpcall2 = in_array($user->uid, loadadinitation_project_user(node_load($node->nid)));
                if ($node->uid == $user->uid || $cmpcall || $cmpcall2) {
                  $output = '';
                  $nid = $node->nid;
                  $node = node_load($nid);
                  $items = field_get_items('node', $node, 'field_pro_bidding_info');
                  $output .= '<div class="Bidding-fc-list">';
                  foreach ($items as $item) {
                    $fc = field_collection_field_get_entity($item); //pre($fc);  
                    $itemid = $fc->item_id;
                    $output .= '<div class="form-group"><div class="row">';
                    $output .= '<div class="col-md-3 col-sm-3 col-xs-12">';
                    $output .= '<label>' . t('Bid Name:') . '</label>';
                    $output .= '<div class="Cust-bidfc-data">';
                    $output .= (isset($fc->field_proj_bid_name['und'])) ? $fc->field_proj_bid_name['und'][0]['value'] : '';
                    $output .= '</div>';
                    $output .= '</div>';
                    $output .= '<div class="col-md-3 col-sm-3 col-xs-12">';
                    $output .= '<label>' . t('Bid Date:') . '</label>';
                    $output .= '<div class="Cust-bidfc-data">';
                    $biddateval = (isset($fc->field_proj_bid_date['und'])) ? $fc->field_proj_bid_date['und'][0]['value'] : '';
                    $dtstmp = !empty($biddateval) ? strtotime($biddateval) : '';
                    $output .= date("j F Y", $dtstmp);
                    $output .= '</div>';
                    $output .= '</div>';
                    $output .= '<div class="col-md-3 col-sm-3 col-xs-12">';
                    $output .= '<label>' . t('Start:') . '</label>';
                    $output .= '<div class="Cust-bidfc-data">';
                    $biddateval1 = (isset($fc->field_proj_start_date['und'])) ? $fc->field_proj_start_date['und'][0]['value'] : '';
                    $dtstmp1 = !empty($biddateval1) ? strtotime($biddateval1) : '';
                    $output .= date("j F Y", $dtstmp1);
                    $output .= '</div>';
                    $output .= '</div>';
                    $output .= '<div class="col-md-3 col-sm-3 col-xs-12">';
                    $output .= '<label>' . t('Complete:') . '</label>';
                    $output .= '<div class="Cust-bidfc-data">';
                    $biddateval2 = (isset($fc->field_proj_complete_date['und'])) ? $fc->field_proj_complete_date['und'][0]['value'] : '';
                    $dtstmp2 = !empty($biddateval2) ? strtotime($biddateval2) : '';
                    $output .= date("j F Y", $dtstmp2);
                    $output .= '</div>';
                    $output .= '</div>';
                    $output .= '</div>';
                    $output .= '<div class="row">';
                    $output .= '<div class="col-md-12 col-sm-12 col-xs-12">';
                    $output .= '<label>' . t('Bidding Companies:') . '</label>';
                    $query2 = db_select('flagging', 'f')->fields('f', array('uid'))->condition('entity_id', $itemid, '=')->condition('entity_type', 'field_collection_item', '=');
                    $result2 = $query2->execute();                        
                    while ($record2 = $result2->fetchAssoc()) {
                      $counterc = 0;
                      $uid = $record2['uid'];                      
            			    $gids = _get_user_company_nid($uid);
                      if (!empty($gids)) {
              					$counterc++;
              					$gnode = node_load($gids);
                        $output .= '<div class="bid-co-name">' . $gnode->title . '</div>';
                      } else {
                        if ($counterc == 0) {
                          $output .= '<br/>At this time, no companies have selected that they will be bidding on this RFP.';
                        }
                      }
                    }
                    $output .= '</div>';
                    $output .= '</div></div>'; // .row .form-group
                  }
                  $output .= '</div>';
                  echo $output;
                }
                ?>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="rfps">
              <div class='locations'>
                <h1>RFPs</h1>
                <?php print views_embed_view('project_s_rfp_tab','block'); ?> </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="invcomp">
              <div class='locations'>
                <h1>Invite Companies</h1>
                <?php 
				  $block = module_invoke('m6connect_projects', 'block_view', 'my-project-search');
                  print render($block['content']);
				  //echo rfp_find_companies();
				?>
              </div>
            </div>
            <div role="tabpanel" class="tab-pane fade" id="collaborate">
              <div class='locations'>
                <h1>Collaboration</h1>
                <?php 
				  $block2 = module_invoke('m6connect_projects', 'block_view', 'my-project-colaborate');
                  print render($block2['content']);
				?>
              </div>
            </div>
          </div>
        </div>
      </div>
      <div id="pro-right-column" class='col-md-3 col-sm-3 col-xs-12'>
        <div class='photo-gallary'>
          <h2>Profile Photos</h2>
          <div class='row'> 
            <!--<div class="col-sm-4 image-tile"><img src="http://www.usa.skanska.com/cdn-1d099d818099560/Global/featured%20news/LGA_Stock.jpg"></div>
            <div class="col-sm-4 image-tile"><img src="https://media2.wnyc.org/i/620/372/l/80/1/BdewrzUCQAANIPZ.jpg"></div>
            <div class="col-sm-4 image-tile"><img src="http://www.curtissway.com/homepage%20images/laguardia_airport.jpg"></div>-->
            <?php
              $imgpath = (isset($node->field_images['und']) && !empty($node->field_images['und'][0]['uri'])) ? $node->field_images['und'][0]['uri'] : 0;
              if ($imgpath) {
                $imagepath = image_style_url('user_pic_32x32', $imgpath);
				echo '<div class="col-sm-4 image-tile"><img src="' . $imagepath . '" /></div>';
              }
			?>
          </div>
          <div class='row'>
            <div class='col-lg-12'><a href='#'>View All Photos</a></div>
          </div>
        </div>
        <div class='public-projects'>
          <h2>Subcontractor Opportunities</h2>
          <ul class='projects-list'>
            <li>Borings</li>
            <li>Concrete</li>
            <li>Demolition</li>
            <li>HazMat Disposal and Removal</li>
          </ul>
          <p style="text-align: right;"><a href="#">(View More)</a></p>
        </div>
        <div class="public-projects">
          <h2>Vendor Opportunities</h2>
          <ul class="projects-list">
            <li>CMU</li>
            <li>Curtain Wall</li>
            <li>Elevators</li>
            <li>HVAC</li>
            <li>Jetway Bridges</li>
          </ul>
          <p style="text-align: right;"><a href="#">(View More)</a></p>
        </div>
        <div class='public-rfps'>
          <h2>Design Consult. Opportunities</h2>
          <ul class="projects-list">
            <li>Archival Photography</li>
            <li>CADD Services</li>
            <li>Civil Engineering (Landside &amp; Airside)</li>
            <li>Demolition Documents</li>
            <li>Interim Conditions Design</li>
          </ul>
          <p style="text-align: right;"><a href="#">(View More)</a></p>
        </div>
      </div>
    </div>
  </div>
  <?php
	
	//******************************* Node content end *********************************//
	
	
	
  ?>
  <?php //print render($content['links']); ?>
  <?php //print render($content['comments']); ?>
</article>
<?php
  //drupal_add_library('system', 'ui.dialog');
  ?>
<div id='dialog-rfp-project-node-view'></div>
<span id="dialog-rfp-project-node-id" style="display:none;"><?php print $node->nid; ?></span>
<div id='dialog-thnakyou-invited'></div>
<span id="dialog-thnakyou-invited-node-id" style="display:none;"><?php print $node->nid; ?></span> 

<!--<script src="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.23/jquery-ui.min.js"></script> --> 
