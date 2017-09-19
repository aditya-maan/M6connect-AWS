<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<?php global $user, $company, $base_url; ?>
<?php
$user_order_role = "";
$user_order_price = "";
$user_role_proposal = "";
$user_order_sku = "";
$content_type = '';
$node = new stdClass();
$nid = $company->nid;
if (arg(0) == 'node') {
    $nid = arg(1);
    $node = node_load($nid);
    $content_type = $node->type;
}

$site_url = $GLOBALS['base_url'];
$path = current_path();

//echo 'test'.getcwd();
?>
<?php if ($user->uid == 0) : ?>

<div id="page">
  <header class="header front_header clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4 col-sm-4 col-xs-12 logo-txt">
          <?php if ($logo): ?>
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
          <?php endif; ?>
          <?php if ($site_name || $site_slogan): ?>
          <div class="header__name-and-slogan" id="name-and-slogan">
            <?php if ($site_name): ?>
            <h1 class="header__site-name" id="site-name"> <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="header__site-link" rel="home"><span><?php print $site_name; ?></span></a> </h1>
            <?php endif; ?>
            <?php if ($site_slogan): ?>
            <div class="header__site-slogan" id="site-slogan"><?php print $site_slogan; ?></div>
            <?php endif; ?>
          </div>
          <?php endif; ?>
          <?php print render($page['header_logo']); ?> </div>
        <div class="col-md-8 col-sm-8 col-xs-12 text-right"> <?php print render($page['header']); ?> </div>
      </div>
    </div>
  </header>
  <?php if ($page['slider']): ?>
  <div class="page_slider clearfix relative">
    <div class="clearfix"> <?php print render($page['slider']); ?> </div>
  </div>
  <?php endif; ?>
  <div id="main">
    <div class="container">
      <div id="content" class="column clearfix" role="main">
        <div class="box clearfix">
          <div class="inner-box clearfix">
            <div class="front_data_tabs clearfix"> <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
              <?php if ($action_links): ?>
              <ul class="action-links">
                <?php print render($action_links); ?>
              </ul>
              <?php endif; ?>
              <?php if ($page['content']): ?>
	              <div class="clearfix margin-bottom-45"> <?php print render($page['content']); ?> </div>
              <?php endif; ?>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
  <?php if ($page['preface']): ?>
  <div class="clearfix margin-bottom-45">
    <div class="preface_inner"><?php print render($page['preface']); ?> </div>
  </div>
  <?php endif; ?>
  <?php if ($page['out_team']): ?>
  <div class="clearfix out_team margin-bottom-45">
    <div class="out_team_inner clearfix">
      <div class="container"> <?php print render($page['out_team']); ?> </div>
    </div>
  </div>
  <?php endif; ?>
  <div class="footer_content clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4 footer_left">
          <?php if ($page['footer_left']): ?>
          <?php print render($page['footer_left']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_center">
          <?php if ($page['footer_center']): ?>
          <?php print render($page['footer_center']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_right">
          <?php if ($page['footer_right']): ?>
          <?php print render($page['footer_right']); ?>
          <?php endif; ?>
        </div>
      </div>
      <div class="clearfix">
				<?php if ($page['footer_top']): ?>
        <?php print render($page['footer_top']); ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class="footer_message clearfix">
    <div class="container">
      <?php if ($page['footer']): ?>
      <?php print render($page['footer']); ?>
      <?php endif; ?>
    </div>
  </div>
</div>
<?php endif; ?>
<?php if ($user->uid != 0) : ?>
<div id="page">
  <header class="header" id="header" role="banner">
    <div class="container-fluid">
      <div id="top-navigation" class="row"><?php print render($page['top_navigation']); ?></div>
      <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" class="header__logo" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="header__logo-image" /></a>
      <?php endif; ?>
      <?php if ($site_name || $site_slogan): ?>
      <div class="header__name-and-slogan" id="name-and-slogan">
        <?php if ($site_name): ?>
        <h1 class="header__site-name" id="site-name"> <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" class="header__site-link" rel="home"><span><?php print $site_name; ?></span></a> </h1>
        <?php endif; ?>
        <?php if ($site_slogan): ?>
        <div class="header__site-slogan" id="site-slogan"><?php print $site_slogan; ?></div>
        <?php endif; ?>
      </div>
      <?php endif; ?>
      <?php print render($page['header']); ?> </div>
  </header>
  <?php if ($page['navigation']): ?>
  <div id="navigation">
    <div class="container"><?php print render($page['navigation']); ?></div>
  </div>
  <?php endif; ?>
  <div id="preface" class="<?php if (!$page['preface']) { print 'dispaly_none'; } else { print 'preface'; } ?>">
    <div class="preface_inner"><?php print render($page['preface']); ?></div>
  </div>
  <?php if((!path_is_admin(current_path())) || (arg(0)=='node' && !empty(arg(1)) && (is_numeric(arg(1)) || arg(1)=='add'))){ ?>
  <?php $wrapperClass =''; if(isset($_SESSION['left_block_action']) && $_SESSION['left_block_action']=='open'){ $wrapperClass='active'; } ?>
  <div id="wrapper" class="<?php print $wrapperClass; ?> clearfix">
    <div id="sidebar-wrapper">
      <?php if ($page['left_content']): ?>
      <?php print render($page['left_content']); ?>
      <?php endif; ?>
    </div>
    <div id="page-content-wrapper">
      <div class="page-content inset">
        <?php } ?>
        <div id="main">
          <div class="container-fluid">
						<?php if ($page['slider']): ?>
            <div class="page_slider clearfix relative">
              <div class="clearfix"> <?php print render($page['slider']); ?> </div>
            </div>
            <?php endif; ?>
            <div class="top_header clearfix">
              <?php if ($page['top_header']): ?>
              <?php print render($page['top_header']); ?>
              <?php endif; ?>
            </div>
            <div class="middle-page">
              <div class="box">
                <div class="inner-box <?php if (isset($node) && in_array($content_type, array('project'))) { print 'project_node_page'; } ?>"> 
                  <!--                  New Design start                      -->
                  <div class="<?php if (isset($node) && in_array($content_type, array('project'))) { print 'project_clear'; } ?>">
                    <div class="white-bg">
                      <div class="right_content clearfix">
                        <div class="content_inner_pages clearfix">
                          <?php
                             // Render the sidebars to see if there's anything in them.
                             $sidebar_first = render($page['sidebar_first']);
                             $sidebar_second = render($page['sidebar_second']);
                             ?>
                          <?php if ($sidebar_first || $sidebar_second): ?>
                          <aside class="sidebars"> <?php print $sidebar_first; ?> <?php print $sidebar_second; ?> </aside>
                          <?php endif; ?>
                          <div id="content" class="column" role="main">
                            <div class="content-page"> <?php print $breadcrumb; ?> <a id="main-content"></a> <?php print render($title_prefix); ?>
                              <?php if($content_type == 'my_proposal' && arg(0)=='node' && is_numeric(arg(1)) && empty(arg(2))){  ?>
                              <?php if ($title): ?>
                              <div class="clearfix">
                                <div class="pull-left">
                                  <h1 class="page__title title" id="page-title">
                                    <?php
                                if( arg(0)=='statuses' && is_numeric(arg(1)) && !arg(2)){ $newbtitle = explode(' » ', $title);
                                if(isset($newbtitle[1])){ print $newbtitle[0].' with '.$newbtitle[1]; } }else{ print $title; }
                              ?>
                                  </h1>
                                </div>
                                <?php endif; ?>
                                <div class="bfeedback-report-btn form-group pull-right"> <a href="/proposalsummary/<?php echo $node->nid; ?>"> <img src="<?php echo $base_url; ?>/sites/all/themes/m6connect/images/icon-news2.png"> PDF Report </a> </div>
                              </div>
                              <?php } 
                              /*--------------------*/
                            if($content_type =='onboarding_project' && arg(0)=='node' && is_numeric(arg(1)) && empty(arg(2))) {  ?>
                              <?php if ($title): ?>
                              <div class="clearfix margin-bottom-20">
                                <div class="pull-left">
                                  <h1 class="page__title title" id="page-title">
                                    <?php
                                    if( arg(0)=='statuses' && is_numeric(arg(1)) && !arg(2)){ $newbtitle = explode(' » ', $title);
                                   if(isset($newbtitle[1])){ print $newbtitle[0].' with '.$newbtitle[1]; } }//else{ print $title; }
                                     ?>
                                  </h1>
                                </div>
                                <?php endif; ?>
                                <?php if($node->uid == $user->uid){?>
                                <div class="pull-right"> <a href="/m6id-project-invite/<?php echo $node->nid; ?>/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-primary">Invite Companies</a> </div>
                                <?php } ?>
                              </div>
                              <?php } else { ?>
                              <?php if ($title): ?>
                              <?php if($content_type != 'my_proposal') { ?>
                              <h1 class="page__title title" id="page-title">
                                <?php
                                if( arg(0)=='statuses' && is_numeric(arg(1)) && !arg(2)){ 
								  $newbtitle = explode(' » ', $title);
                                  if(isset($newbtitle[1])){ 
								    print $newbtitle[0].' with '.$newbtitle[1]; 
								  } 
								}
								else { 								  
								  print $title; 
								}
                              ?>
                              </h1>
                              <?php } ?>
                              <?php endif; ?>
                              <?php } ?>
                              <?php print render($title_suffix); ?> <?php print $messages; ?>
                              <div class="<?php if (isset($node) && in_array($content_type, array('project'))) { print 'project_node_tabs'; } ?> clearfix">
                                <div class="<?php if (isset($node) && in_array($content_type, array('project'))) { print 'pull-left'; } ?>"> <?php print render($tabs); ?> <?php print render($page['help']); ?>
                                  <?php if ($action_links): ?>
                                  <ul class="action-links">
                                    <?php print render($action_links); ?>
                                  </ul>
                                  <?php endif; ?>
                                </div>
                                <div class="highlighted <?php if (isset($node) && in_array($content_type, array('project'))) { print 'pull-right'; } ?>"><?php print render($page['highlighted']); ?></div>
                              </div>
                              <?php print render($page['content']); ?> </div>
                          </div>
                        </div>
                        <div class="right_content_top clearfix">
                          <div class="right_content_top_inner">
                            <?php if ($page['right_content']): ?>
                            <?php print render($page['right_content']); ?>
                            <?php endif; ?>
                          </div>
                        </div>
                        <div class="right_content_bottom clearfix">
                          <div class="row margin-5">
                            <div class="col-md-9 col-sm-9 col-xs-12 padding-5">
                              <?php if ($page['company_navs']): ?>
                              <?php print render($page['company_navs']); ?>
                              <?php endif; ?>
                            </div>
                          </div>
                        </div>
                        <div class="clearfix out_team">
                          <div class="out_team_inner clearfix"> <?php print render($page['out_team']); ?> </div>
                        </div>
                      </div>
                      <div class="row margin-5 middle_content">
                        <div class="col-md-3 col-sm-3 col-xs-12 padding-5">
                          <div class="middle_one company-profile-navigation clearfix">
                            <div class="middle_one_top clearfix">
                              <?php if ($page['middle_one_top']): ?>
                              <?php print render($page['middle_one_top']); ?>
                              <?php endif; ?>
                            </div>
                            <div class="middle_one_bottom clearfix">
                              <?php if ($page['middle_one_bottom']): ?>
                              <?php print render($page['middle_one_bottom']); ?>
                              <?php endif; ?>
                            </div>
                          </div>
                        </div>
                        <div class="col-md-6 col-sm-6 col-xs-12 padding-5">
                          <div class="middle_two clearfix">
                            <div class="middle_two_inner">
                              <?php if ($page['middle_two']): ?>
                              <?php print render($page['middle_two']); ?>
                              <?php endif; ?>
                            </div>
                          </div>
                        </div>
                        <div class="col-md-3 col-sm-3 col-xs-12 padding-5">
                          <div class="middle_three clearfix">
                            <?php if ($page['middle_three']): ?>
                            <?php print render($page['middle_three']); ?>
                            <?php endif; ?>
                          </div>
                        </div>
                      </div>
                      <div class="bottom_content clearfix">
                        <div class="bottom_content_inner">
                          <?php if ($page['bottom_content']): ?>
                          <?php print render($page['bottom_content']); ?>
                          <?php endif; ?>
                        </div>
                      </div>
                    </div>
                  </div>
                  <div class="my-proposal-page"> 
                    <!-- view proposal page start -->
                    <?php if ($content_type == "my_proposal") { } ?>
                    <!-- view proposal page end -->
                    
                    <?php
                        $query_2 = db_select('users_roles', 'ur')
                                ->fields('ur', array('uid', 'rid'));
                        $db_or = db_or();
                        $db_or->condition(db_and()->condition('ur.uid', $user->uid, '=')->condition('ur.rid', array(1, 2, 3, 5, 6), 'NOT IN'));
                        $src_1 = $query_2->condition($db_or);
                        $result_2 = $src_1->execute();
                        foreach ($result_2 as $item_2) {
                            $user_order_role = $item_2->rid;
                        }

                        /** proposal query for fining user role start * */
                        $propsal_query = db_select('users_roles', 'up')
                                ->fields('up', array('uid', 'rid'));
                        $db_or_proposal = db_or();
                        $db_or_proposal->condition(db_and()->condition('up.uid', $user->uid, '=')->condition('up.rid', array(3, 5, 6), 'IN'));
                        $src_propsal = $propsal_query->condition($db_or_proposal);
                        $result_proposal = $src_propsal->execute();
                        foreach ($result_proposal as $item_proposal) {
                            $user_role_proposal = $item_proposal->rid;
                        }

                        /** proposal query for fining user role end * */
                        $query = db_select('uc_orders', 'o')
                                ->fields('o', array('order_id', 'uid', 'order_status', 'order_total'));
                        $db_or_1 = db_or();
                        $db_or_1->condition(db_and()->condition('o.uid', $user->uid, '=')->condition('o.order_status', 'completed', '='));
                        $query->orderBy('order_id', 'DESC');
                        $query->range(0, 1);
                        $src = $query->condition($db_or_1);
                        $result = $src->execute();
                        foreach ($result as $item) {
                            $user_order = $item->order_status;
                            $user_order_id = $item->order_id;
                            $user_order_price = $item->order_total;
                        }

                        if ($user_order_id != "") {
                            $query_1 = db_select('uc_order_products', 'p')
                                    ->condition('p.order_id', $user_order_id, '=')
                                    ->fields('p', array('order_id', 'title', 'model', 'price'));
                            $result_1 = $query_1->execute();
                            foreach ($result_1 as $item_1) {
                                $user_order_product = $item_1->title;
                                $user_order_sku = $item_1->model;
                                $user_order_price = $item_1->price;
                            }
                        }
                        ?>
                    <?php if($nid == 36){ ?>
                    <!--<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
                    <script src="/sites/all/themes/m6connect/js/dropdown.js"></script> 
                    <script src="/sites/all/themes/m6connect/js/collapse.js"></script>-->
                    <?php
                            // 
                            global $company; //pre($company,1);
                            $CompanyType = '';
                            $col_md_cls = 'col-md-4 ';
                            $is_individual = 0;
                            if (isset($company->field_type_of_company['und']) && isset($company->field_type_of_company['und'][0]['value']) && !empty($company->field_type_of_company['und'][0]['value'])) {
                                $CompanyType = $company->field_type_of_company['und'][0]['value'];
                                $is_individual = ($CompanyType == 'individual') ? 1 : 0;
                            }
                            if ($is_individual) {
                                $col_md_cls = 'col-md-6 ';
                            }
                            ?>
                    <script>
                                //jQuery.noConflict();
								jQuery(document).ready(function(e) {
                                  //jQuery('[data-toggle="tooltip"]').tooltip();
                                    jQuery('.select-plan a').click(function (e) {
                                        jQuery.preventDefault();
                                        jQuery(this).tab('show');
                                    }); 
                                });
                                /*jQuery(function () {
                                    jQuery('[data-toggle="tooltip"]').tooltip();
                                    jQuery('.select-plan a').click(function (e) {
                                        jQuery.preventDefault();
                                        jQuery(this).tab('show');
                                    })
                                });*/

                                var get_now = jQuery('.node-add-to-cart.form-submit').val('GET NOW');
                                jQuery('#edit-submit-948').val('GET LICENCE');
                                jQuery('#edit-submit-947').val('GET LICENCE');
                                jQuery('#edit-submit-946').val('GET LICENCE');

                            </script>
                    <?php } ?>
                    
                    <!--- upgrade page end modified by colan ---> 
                    
                  </div>
                </div>
                <div class="clearfix">
                  <?php
		  if (!empty($page['content_bottom_full'])) {
			print render($page['content_bottom_full']);
		  }
		  ?>
                </div>
              </div>
            </div>
          </div>
        </div>
        <?php if((!path_is_admin(current_path())) || (arg(0)=='node' && !empty(arg(1)) && (is_numeric(arg(1)) || arg(1)=='add'))){ ?>
      </div>
    </div>
  </div>
  <?php } ?>
  <div class="footer_content clearfix">
    <div class="container">
      <div class="row">
        <div class="col-md-4 footer_left">
          <?php if ($page['footer_left']): ?>
          <?php print render($page['footer_left']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_center">
          <?php if ($page['footer_center']): ?>
          <?php print render($page['footer_center']); ?>
          <?php endif; ?>
        </div>
        <div class="col-md-4 footer_right">
          <?php if ($page['footer_right']): ?>
          <?php print render($page['footer_right']); ?>
          <?php endif; ?>
        </div>
      </div>
      <div class="clearfix">
				<?php if ($page['footer_top']): ?>
        <?php print render($page['footer_top']); ?>
        <?php endif; ?>
      </div>
    </div>
  </div>
  <div class="footer_message clearfix">
    <div class="container">
      <?php if ($page['footer']): ?>
      <?php print render($page['footer']); ?>
      <?php endif; ?>
    </div>
  </div>

  <div class="container"><?php print render($page['bottom']); ?> </div>
</div>
<!--<script src="<?php //print $base_url . '/' . path_to_theme(); ?>/js/bootstrap.min.js"></script>-->
<?php endif; ?>

<!-- -- code modified by colan start --- --> 
<script>
        var page_alias = "<?php echo $path; ?>";
        if (page_alias == "proposals/sent")
        {
            $(".rpf-exposed-filter .views-exposed-form #edit-submit-proposals").val('Search');
        }
        if (page_alias == "proposals/draft")
        {
            $(".view-filters .views-exposed-form #edit-submit-proposals").val('Search');
        }

        if (page_alias == "cart")
        {
            $("th:nth-child(2)").text("Membership plan");
            $("#uc-cart-view-form .desc>a").attr("href", "javascript:void(null)");
        }
        if (page_alias == "cart/checkout")
        {
            $("th:nth-child(2)").text("Membership plan");
            $("#uc-cart-checkout-form .products>a").attr("href", "javascript:void(null)");
            var d = new Date(),
                    n = d.getMonth(),
                    y = d.getFullYear();

            $('#edit-panes-payment-details-cc-exp-month option:eq(' + n + ')').prop('selected', true);

            $('#edit-panes-payment-details-cc-exp-year option[value="' + y + '"]').prop('selected', true);
        }
        if (page_alias == "cart/checkout/review")
        {
            $(".order-review-table .products>a").attr("href", "javascript:void(null)");
        }
        var page_id = "<?php echo $nid; ?>";
        if (page_id == 36) {

            function change_button()
            {

                /*document.getElementById('edit-actions--5').innerHTML = '<input type="button" <?php
 //if (isset($user_result_role) && $user_result_role != "") {
 //   echo 'data-toggle="modal"';
 //   echo 'data-target="#myModal"'; 
 //}
?>onClick="check_plan(4)" data="Plan4" value="GET NOW" name="op" id="edit-submit-920" class="node-add-to-cart form-submit plan">';*/

                document.getElementById('edit-actions--2').innerHTML = '<input type="button" <?php
if (isset($user_result_role) && $user_result_role != "") {
    echo 'data-toggle="modal"';
    echo 'data-target="#myModal"';
}
?>onClick="check_plan(1)" data="Plan1" value="GET NOW" name="op" id="edit-submit-429" class="node-add-to-cart form-submit plan">';

                document.getElementById('edit-actions--3').innerHTML = '<input type="button" <?php
if (isset($user_result_role) && $user_result_role != "") {
    echo 'data-toggle="modal"';
    echo 'data-target="#myModal"';
}
?> onClick="check_plan(2)" data="Plan2" value="GET NOW" name="op" id="edit-submit-430" class="node-add-to-cart form-submit planactive">';

                document.getElementById('edit-actions--4').innerHTML = '<input type="button" <?php
if (isset($user_result_role) && $user_result_role != "") {
    echo 'data-toggle="modal"';
    echo 'data-target="#myModal"';
}
?> onClick="check_plan(3)" data="Plan3" value="GET NOW" name="op" id="edit-submit-431" class="node-add-to-cart form-submit plan">';
            }
            change_button();


            function check_plan(plan_id)
            {
                if (plan_id == 1) {
                    jQuery(".region-cart-silverplan form").addClass("myClass");
                    var plan_form = jQuery(".myClass").attr('id');
                }
                else if (plan_id == 2) {
                    jQuery(".region-cart-goldplan form").addClass("myClass1");
                    var plan_form = jQuery(".myClass1").attr('id');
                }
                else if (plan_id == 3) {
                    jQuery(".region-cart-corporateplan form").addClass("myClass2");
                    var plan_form = jQuery(".myClass2").attr('id');
                } else if (plan_id == 4) {
                    jQuery(".region-cart-payasyougoplan form").addClass("myClass3");
                    var plan_form = jQuery(".myClass3").attr('id');
                }
                var membership_role_no = "<?php echo $user_order_role; ?>";
                form_id = plan_form.substring(plan_form.lastIndexOf("-") + 1, plan_form.length);

                //alert(membership_role_no);
                //alert(form_id);	
                var plan_form_submit = document.getElementById('uc-product-add-to-cart-form-' + form_id);

                if ((membership_role_no == "") || (membership_role_no == 4))
                {
                    jQuery(plan_form_submit).submit();

                }
                else
                {
                    jQuery.ajax({
                        type: 'POST',
                        url: '<?php echo $site_url; ?>/sites/all/themes/m6connect/unsubscribe_ajax.php',
                        data: {data_plan: form_id},
                        success: function (response)
                        {
                            var my_data = response.split('@@');
                            my_click_plan_id = my_data[0];
                            my_click_plan_sku = my_data[1];
                            my_click_plan_price = my_data[2];
                            var user_order_price = "<?php echo $user_order_price; ?>";

                            //alert(user_order_price);
                            //alert(my_click_plan_price);
                            user_order_price = parseFloat(user_order_price);
                            my_click_plan_price = parseFloat(my_click_plan_price);
                            if (user_order_price == my_click_plan_price)
                            {
                                jQuery('#myModal').modal('show');
                                jQuery(".text-upgrade").text("you have currently choose this plan.Please select another plan");
                                jQuery("#current_id").text("close");
                                jQuery("#ok_btn").css("opacity", 0);
                            }
                            else if (user_order_price != my_click_plan_price)
                            {
                                if (user_order_price > my_click_plan_price)
                                {
                                    jQuery('#myModal').modal('show');
                                    jQuery("#ok_btn").css("opacity", 1);
                                    jQuery("#current_id").text("cancel");
                                    jQuery(".text-upgrade").text("Are you sure want to degrade this plan?");
                                    return false;
                                }
                                else
                                {
                                    jQuery('#myModal').modal('hide');
                                    jQuery(plan_form_submit).submit();
                                }
                            }
                        }
                    });

                    this.myFunction = function ()
                    {
                        jQuery(plan_form_submit).submit();
                    }
                }
            }

            jQuery('.node-add-to-cart.form-submit').each(function () {
                var button_data = jQuery(this).attr('data');
                var order_product_sku = "<?php echo $user_order_sku ?>";
                if (button_data == order_product_sku)
                {
                    jQuery(this).val('My Current Plan');

                }

            });


        }
    </script>
<?php
    if (isset($_SESSION['form_submitted']) && $_SESSION['form_submitted'] != '') {
        $form_submit_value = $_SESSION['form_submitted'];
        $form_submit_id_value = explode("_", $form_submit_value);
        if (isset($form_submit_id_value[6]) && $form_submit_id_value[6] != "") {
            ?>
<script>
                if ($('#edit-items-1-remove').length)
                {
                    $('#edit-items-0-remove').trigger('click');
                }
            </script>
<?php }
} ?>
<?php if ($nid == 36) { ?>
<style> 
.alert{margin-bottom:0px !important;} 
</style>
<div class="container pop_modal"> 
  
  <!-- Modal -->
  <div class="modal fade" id="myModal" role="dialog">
    <div class="modal-dialog modal-md">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal">&times;</button>
          <h4 class="modal-title" style="color:#3f8bc0">Membership Plan Upgrade</h4>
        </div>
        <div class="modal-body">
          <p class="text-upgrade"></p>
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-default" data-dismiss="modal" id="ok_btn" onclick="myFunction()" >yes</button>
          <button type="button" class="btn btn-default" id="current_id" data-dismiss="modal">cancel</button>
        </div>
      </div>
    </div>
  </div>
</div>
<?php } ?>
<?php

    /*     * ******  Start MaanSoftware work -> RFP owner can see his own rfp. ****** */

// Commented by MaansoftWare  (mikes team work)
    /* if( $user->uid != $user_rfp_id )
      {
      if(($content_type == "rfp") && ($user_order_role == 4)){
      header("Location: ".$GLOBALS['base_url']."/rfps/public?access=denied");
      }
      } */

// Added by Maansortware
    /* $onlyAuthuser = 1;
      foreach($user->roles as $roleId => $roleName){
      if($roleId!=2){
      $onlyAuthuser = 0;
      }
      }

      if (($content_type == "rfp") && (($user_order_role == 4) || $onlyAuthuser)) {
      //drupal_set_message($print);
      $status = check_rfp_user_ajax($node, $ajax = FALSE);
      if ($status == 0) {
      header("Location: " . $GLOBALS['base_url'] . "/rfps/public?access=denied");
      }
      } */

    if ($content_type == "rfp") {
        $status = check_rfp_user_ajax($node, $ajax = FALSE);
        if ($status == 0) {
            $_SESSION['agreed_membership_payment_popup'] = $node->nid;
           // header("Location: " . $GLOBALS['base_url'] . "/rfps/public?access=denied");
        }
    }




    /*     * *******************  End MaanSoftware work  **************************** */

    /*     * ********************** Proposal Upgrade Popup **************************** */
    /* if (($path == "node/add/my-proposal") && ($user_order_role == 4)) {
      header("Location: " . $GLOBALS['base_url'] . "/proposals/received?access=denied");
      } */
    /*     * ************************************************************************** */
    ?>
<script>
        /* < !-- popup starts -- >*/
        var my_role = "<?php echo $user_order_role; ?>";
//        var my_role_auth = "<?php // echo $onlyAuthuser;  ?>";
        //console.log('My Role: '+my_role);
        //console.log('Auth Role'+my_role_auth);
        //if (my_role == 4 || my_role_auth==1)
        //{

        /************** Proposal Upgrade Popup *******************/
        //$("#popup_lock-upgrade").attr("class", "pop_title");
        /*********************************************************/

        $('.view-id-rfps .row > .col-md-2.col-sm-2.col-xs-12:first-child a').each(function () {
            /*var a = $(this).attr('href');
            var partsOfStr = a.split('/');
            var site_a = partsOfStr[2];
            		 

            var listItem = $(this);
            var pos = $('.view-id-rfps .row > .col-md-2.col-sm-2.col-xs-12:first-child a').index(listItem);
            var pos_cor = pos + 1;*/
			
			

            /********  Start MaanSoftware work -> RFP owner can see his own rfp. *******/

            //Comment by Maansortware (Mikes team work)
            /*var b = "<?php //echo $user_rfp_node_1;         ?>";		
             var partsOfStr_1 = b.split('_');
             var site_b = partsOfStr_1.length;
             
             
             if(jQuery.inArray(site_a, partsOfStr_1) != -1) {  
             $(".view-id-rfps .views-row-"+pos_cor+" h3").attr("class","");
             } else {   
             $(".view-id-rfps .views-row-"+pos_cor+" h3").attr("class","pop_title");
             } */

            //Added by MaanSoftware
			var projectBox = $(this).closest('.company-item');
		    var rfp_nid = projectBox.data('nid');
            if (!isNaN(rfp_nid) && rfp_nid > 0) {
                $.post("/check-rfp-user-ajax/" + rfp_nid)
					.done(function (data) {
						if (data.status == 1) {
							projectBox.find('h3').attr('class','');
						} else {
							projectBox.find('h3').attr('class','pop_title');
						}
					});
            }

            /*********************  End MaanSoftware work  *****************************/
        });

        //}
       /* if (jQuery('body').hasClass('page-rfps')) {
            $(".pop_title").live('click', function () {
                //$("document").on('click',".pop_title", function () {	
                //$("#pop_content").fadeIn();
                //company-item
                var data_nid = jQuery(this).closest('.company-item').attr('data-nid');
                jQuery('#purchase-membershpip-dialog').html('<div><div class="text-center form-group"><strong>Pay Upon Award</strong></div><div class="text-center form-group"><strong>By opening this RFP your company agrees that upon Award, should you be successful in the bid effort, you will purchase an M6Connect Gold Membership. Be sure to include the cost of the Gold Membership in your bid.</strong></div><div class="form-element"><input type="checkbox" value="1" id="hide-rfp-access-popup" /><strong>&nbsp;&nbsp;Do not show in the future.</strong></div><span class="data-id" style="display:none;">' + data_nid + '</span></div>');
                jQuery('#purchase-membershpip-dialog').dialog('open');
                return false;
            });

            $(".pop_close").click(function () {
                $("#pop_content").fadeOut();
            });
        }*/

        $(".overlay").click(function () {
            $("#pop_content").fadeOut();
        });

        window.onkeydown = function (event) {
            if (event.keyCode === 27) {
                $("#pop_content").fadeOut();
            }
        };
<!-- popup ends -->
    </script> 

<!--- free plan popup start ---> 
<!--<div id="pop_content">
  <div class="overlay"></div>
  <div class="pop_text">
    <div class="pop-main-top"> <a href="#close" class="pop_close"> <img src="/sites/all/themes/m6connect/images/pop_close.png"/></a>
      <h2>Unlock this Feature Today!</h2>
      <div class="m6_pop_log"> <img src="/sites/all/themes/m6connect/images/icon-120.png"/> </div>
    </div>
    <div class="pop_text_inner">
      <p>Unlock the full power of M6Connect and access this content 
        by upgrading to one of our paid subscription levels. Click
        below to choose the subscription that is right for you!</p>
      <div class="m6_pop_list_im">
        <ul class="m6_pop_list">
          <li>View RFPs & Express Interest in Bidding
          <li>
          <li>Create & Send Proposals
          <li>
          <li>Connect with Other Companies
          <li>
          <li>Create & Post Projects
          <li>
          <li>Create & Send Contracts
          <li>
          <li>and Much More!
          <li> <img src="/sites/all/themes/m6connect/images/m6_pop_comp.png" class="compimg"/>
        </ul>
        <div class="m6_pop_upgrade_btn"> <a href="/upgrade-your-membership-subscription"> <img src="/sites/all/themes/m6connect/images/m6_pop_btn.png"/> </a> </div>
      </div>
    </div>
  </div>
</div>--> 

<!--- free plan popup end ---> 

<script>

        var getUrlParameter = function getUrlParameter(sParam) {
            var sPageURL = decodeURIComponent(window.location.search.substring(1)),
                    sURLVariables = sPageURL.split('&'),
                    sParameterName,
                    i;
            for (i = 0; i < sURLVariables.length; i++) {
                sParameterName = sURLVariables[i].split('=');
                if (sParameterName[0] === sParam) {
                    return sParameterName[1] === undefined ? true : sParameterName[1];
                }
            }
        };
        var tech = getUrlParameter('access');
        if (tech == "denied") {
            //$("#pop_content").fadeIn();
        }

        $(".pop_text .pop_close").click(function () {
            $("#pop_content").fadeOut();
        });
        edit_proposal = '<?php echo $content_type; ?>';
        if ((page_alias == "node/add/my-proposal") || (edit_proposal == 'my_proposal'))
        {

            $(document).ready(function () {

                $(".page-node-add-my-proposal #edit-submit").attr('value', 'Submit eProposal');
                $(".page-node-edit.node-type-my-proposal #edit-submit").attr('value', 'Submit eProposal');
                $("#comment-form #edit-actions #edit-submit").live("click", function () {



                    $text_sub = $(".create_pop_text_click #edit-subject").val();
                    if (($text_sub).trim() == '')
                    {
                        $("#proposal_pop_content").fadeIn();
                        $(".pro_required_title").text("Message for Proposal");
                        $(".pro_required").text("Please Enter the Subject");
                        return false;
                    }
                    //$text_com = $("#edit-comment-body #cke_edit-comment-body-und-0-value").val();	
                    /*if(($text_com).trim() == '' )
                     {
                     $("#proposal_pop_content").fadeIn();
                     $(".pro_required_title").text("Message for Proposal");
                     $(".pro_required").text("Please Enter the Message");			
                     return false;  
                     }	*/
                });
                $(".pro_close").click(function () {
                    $("#proposal_pop_content").fadeOut();
                });
                /*$("#edit-actions input#edit-submit").live("click", function () {

                    if (document.getElementById("edit-field-choose-from-the-options-li-und-submit-proposal-in-response-to-a-rfp").checked == true)
                    {

                        if ($('#field-submit-proposal-in-respons-values input:checkbox:checked').length > 0)
                        {
                            $('#field-field-sub-proposal-pjt-values input:checkbox').removeAttr('checked');
                            $('#field-submit-proposal-member-values input:checkbox').removeAttr('checked');
                            $('#field-submit-proposal-to-company-values input:checkbox').removeAttr('checked');
                            $("#confirm_title").text("Confirm Submission");
                            $("#confirm_content").text("Please confirm that you would like to submit this proposal to the individuals/companies selected. Once you submit this proposal, a notification will be sent to selected individuals/companies");
                            $("#current_okey").css('display', 'none');
                            $("#current_cancel").css('display', 'block');
                            $("#current_subproposal").css('display', 'block');
                            $("#confirm_pop_content").fadeIn();
                            return false;
                        }
                        else {
                            $("#proposal_pop_content").fadeIn();
                            $(".pro_required").text("Please select any one of the RFP");
                            return false;
                        }

                    }
                    if (document.getElementById("edit-field-choose-from-the-options-li-und-submit-proposal-in-response-to-a-project").checked == true)
                    {

                        if ($('#field-field-sub-proposal-pjt-values input:checkbox:checked').length > 0)
                        {
                            $('#field-submit-proposal-in-respons-values input:checkbox').removeAttr('checked');
                            $('#field-submit-proposal-member-values input:checkbox').removeAttr('checked');
                            $('#field-submit-proposal-to-company-values input:checkbox').removeAttr('checked');
                            $("#confirm_title").text("Confirm Submission");
                            $("#confirm_content").text("Please confirm that you would like to submit this proposal to the individuals/companies selected. Once you submit this proposal, a notification will be sent to selected individuals/companies");
                            $("#current_okey").css('display', 'none');
                            $("#current_cancel").css('display', 'block');
                            $("#current_subproposal").css('display', 'block');
                            $("#confirm_pop_content").fadeIn();
                            return false;
                        }
                        else
                        {
                            $("#proposal_pop_content").fadeIn();
                            $(".pro_required").text("Please select any one of the Project");
                            return false;
                        }

                    }
                    if (document.getElementById("edit-field-choose-from-the-options-li-und-submit-proposal-to-an-individual-member").checked == true)
                    {
                        if ($('#field-submit-proposal-member-values input:checkbox:checked').length > 0)
                        {
                            $('#field-submit-proposal-in-respons-values input:checkbox').removeAttr('checked');
                            $('#field-field-sub-proposal-pjt-values input:checkbox').removeAttr('checked');
                            $('#field-submit-proposal-to-company-values input:checkbox').removeAttr('checked');
                            $("#confirm_title").text("Confirm Submission");
                            $("#confirm_content").text("Please confirm that you would like to submit this proposal to the individuals/companies selected. Once you submit this proposal, a notification will be sent to selected individuals/companies");
                            $("#current_okey").css('display', 'none');
                            $("#current_cancel").css('display', 'block');
                            $("#current_subproposal").css('display', 'block');
                            $("#confirm_pop_content").fadeIn();
                            return false;
                        }
                        else {
                            $("#proposal_pop_content").fadeIn();
                            $(".pro_required").text("Please select any one of the Individual Member");
                            return false;
                        }
                    }
                    if (document.getElementById("edit-field-choose-from-the-options-li-und-submit-proposal-to-a-company").checked == true)
                    {

                        if ($('#field-submit-proposal-to-company-values input:checkbox:checked').length > 0)
                        {
                            $('#field-submit-proposal-in-respons-values input:checkbox').removeAttr('checked');
                            $('#field-field-sub-proposal-pjt-values input:checkbox').removeAttr('checked');
                            $('#field-submit-proposal-member-values input:checkbox').removeAttr('checked');
                            $("#confirm_title").text("Confirm Submission");
                            $("#confirm_content").text("Please confirm that you would like to submit this proposal to the individuals/companies selected. Once you submit this proposal, a notification will be sent to selected individuals/companies");
                            $("#current_okey").css('display', 'none');
                            $("#current_cancel").css('display', 'block');
                            $("#current_subproposal").css('display', 'block');
                            $("#confirm_pop_content").fadeIn();
                            return false;
                        }
                        else {
                            $("#proposal_pop_content").fadeIn();
                            $(".pro_required").text("Please select any one of the Company");
                            return false;
                        }

                    }



                });*/
                // confirm submit proposal
                /*$("#current_subproposal").click(function(){
                 
                 $("#edit-submit" ).trigger( "click" );
                 });*/

                $("#edit-field-proposal-bid-amount-und-0-value").attr('maxlength', '20');
                $("#edit-field-proposal-job-location input").blur(function () {
                    $add1 = $("#edit-field-proposal-job-location-und-0-thoroughfare").val();
                    $add2 = $("#edit-field-proposal-job-location-und-0-premise").val();
                    $city = $("#edit-field-proposal-job-location-und-0-locality").val();
                    $state = $("#edit-field-proposal-job-location-und-0-administrative-area").val();
                    $zip = $("#edit-field-proposal-job-location-und-0-postal-code").val();
                    $full_add = $add1 + ' ' + $add2 + ' ' + $city + ' ' + $state + ' ' + $zip;
                    var emb_map = '<iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d25895663.485556133!2d-95.665!3d37.599999999999994!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x54eab584e432360b%3A0x1c3bb99243deb742!2sUnited+States!5e0!3m2!1sen!2sin!4v1440572410597" width="510" height="350" frameborder="0" style="border:0" allowfullscreen></iframe>';
                    if ($add1 == '' || $city == '' || $state == '' || $zip == '')
                    {
                        var emb_map = '<iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d25895663.485556133!2d-95.665!3d37.599999999999994!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x54eab584e432360b%3A0x1c3bb99243deb742!2sUnited+States!5e0!3m2!1sen!2sin!4v1440572410597" width="510" height="350" frameborder="0" style="border:0" allowfullscreen></iframe>';
                        //alert('Enter All the Fields');
                    }
                    else
                    {
                        var emb_map = "<iframe width='510' height='350' frameborder='0' scrolling='no' marginheight='0' marginwidth='0' src='https://maps.google.com/maps?&amp;q=" + encodeURIComponent($full_add) + "&amp;output=embed'></iframe>";
                    }
                    $("#mymap").html(emb_map);
                });
                //for edit map section starts		
                $edit_add1 = $("#edit-field-proposal-job-location-und-0-thoroughfare").val();
                $edit_add2 = $("#edit-field-proposal-job-location-und-0-premise").val();
                $edit_city = $("#edit-field-proposal-job-location-und-0-locality").val();
                $edit_state = $("#edit-field-proposal-job-location-und-0-administrative-area").val();
                $edit_zip = $("#edit-field-proposal-job-location-und-0-postal-code").val();
                $edit_full_add = $edit_add1 + ' ' + $edit_add2 + ' ' + $edit_city + ' ' + $edit_state + ' ' + $edit_zip;
                if ($edit_add1 == '' || $edit_city == '' || $edit_state == '' || $edit_zip == '')
                {
                    var edit_emb_map = '<iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d25895663.485556133!2d-95.665!3d37.599999999999994!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x54eab584e432360b%3A0x1c3bb99243deb742!2sUnited+States!5e0!3m2!1sen!2sin!4v1440572410597" width="510" height="350" frameborder="0" style="border:0" allowfullscreen></iframe>';
                    //alert('Enter All the Fields');
                }
                else
                {
                    var edit_emb_map = "<iframe width='510' height='350' frameborder='0' scrolling='no' marginheight='0' marginwidth='0' src='https://maps.google.com/maps?&amp;q=" + encodeURIComponent($edit_full_add) + "&amp;output=embed'></iframe>";
                }
                $("#edit-field-mymap #mymap").html(edit_emb_map);
                //for edit map section ends


                $(".form-item.form-type-radio.form-item-field-choose-from-the-options-li-und:nth-child(1)").append("<div id='sub_menu1'></div>");
                $(".form-item.form-type-radio.form-item-field-choose-from-the-options-li-und:nth-child(2)").append("<div id='sub_menu2'></div>");
                $(".form-item.form-type-radio.form-item-field-choose-from-the-options-li-und:nth-child(3)").append("<div id='sub_menu3'></div>");
                $(".form-item.form-type-radio.form-item-field-choose-from-the-options-li-und:nth-child(4)").append("<div id='sub_menu4'></div>");
                var view_popup_permission = "<?php echo $user_role_proposal; ?>";
                // Rfp click starts
                $('#edit-field-choose-from-the-options-li-und-submit-proposal-in-response-to-a-rfp').click(function () {
                    $div_st1 = $("#edit-field-submit-proposal-in-respons").height() + 'px';
										
                    $('#sub_menu1').css('min-height', $div_st1);
                    $('#sub_menu2').css('min-height', '0px');
                    $('#sub_menu3').css('min-height', '0px');
                    //$('#sub_menu4').css('min-height','0px');		
                    $("#views-form-m6rfp-for-proposal-entityreference-view-widget-1 .entity-reference-view-widget-select.form-checkbox").live("click", function () {
                        var atLeastOneIsChecked1 = $('#views-form-m6rfp-for-proposal-entityreference-view-widget-1 :checkbox:checked').length;
                        //$cou_click1 = atLeastOneIsChecked1 * 20;
                        $cou_click1 = 20;
                        $div1 = $("#edit-field-submit-proposal-in-respons").height() + $cou_click1;
                        $('#sub_menu1').css('min-height', $div1 + 'px');
                    });
                    $('#edit-field-submit-proposal-in-respons-und-add-more').val("Click Here to Select the RFP to Submit this eProposal For");
                    if ($('input:radio:checked').length > 0)
                    {
                        $("#edit-field-submit-proposal-in-respons").css("display", "block");
                        $("#edit-field-field-sub-proposal-pjt").css("display", "none");
                        $("#edit-field-submit-proposal-member").css("display", "none");
                        $("#edit-field-submit-proposal-to-company").css("display", "none");
                    }
                });
                // Rfp click ends

                // Project click starts		
                $('#edit-field-choose-from-the-options-li-und-submit-proposal-in-response-to-a-project').click(function () {
                    $div_st2 = $("#edit-field-field-sub-proposal-pjt").height() + 'px';
                    $('#sub_menu2').css('min-height', $div_st2);
                    $('#sub_menu1').css('min-height', '0px');
                    $('#sub_menu3').css('min-height', '0px');
                    $("#views-form-m6project-for-proposal-entityreference-view-widget-1 .entity-reference-view-widget-select.form-checkbox").live("click", function () {
                        var atLeastOneIsChecked2 = $('#views-form-m6project-for-proposal-entityreference-view-widget-1 :checkbox:checked').length;
                        //$cou_click2 = atLeastOneIsChecked2 * 30;
                        $cou_click2 = 30;
                        $div2 = $("#edit-field-field-sub-proposal-pjt").height() + $cou_click2;
                        $('#sub_menu2').css('min-height', $div2 + 'px');
                    });
                    $('#edit-field-field-sub-proposal-pjt-und-add-more').val("Click Here to Select the Project to Submit this eProposal For");
                    if ($('input:radio:checked').length > 0)
                    {
                        $("#edit-field-field-sub-proposal-pjt").css("display", "block");
                        $("#edit-field-submit-proposal-in-respons").css("display", "none");
                        $("#edit-field-submit-proposal-member").css("display", "none");
                        $("#edit-field-submit-proposal-to-company").css("display", "none");
                    }

                });
                // Project click Ends

                // Members click starts			
                $('#edit-field-choose-from-the-options-li-und-submit-proposal-to-an-individual-member').click(function () {
                    $div_st3 = $("#edit-field-submit-proposal-member").height() + 'px';
                    $('#sub_menu3').css('min-height', $div_st3);
                    $('#sub_menu1').css('min-height', '0px');
                    $('#sub_menu2').css('min-height', '0px');
                    //$('#sub_menu4').css('min-height','0px');	
                    $("#views-form-m6individual-member-entityreference-view-widget-1 .entity-reference-view-widget-select.form-checkbox").live("click", function () {
                        var atLeastOneIsChecked3 = $('#views-form-m6individual-member-entityreference-view-widget-1 :checkbox:checked').length;
                        // $cou_click3 = atLeastOneIsChecked3 * 30;
                        $cou_click3 = 30;
                        $div3 = $("#edit-field-submit-proposal-member").height() + $cou_click3;
                        $('#sub_menu3').css('min-height', $div3 + 'px');
                    });
                    $('#edit-field-submit-proposal-member-und-add-more').val("Click Here to Select the Individual Member(s) to Submit this Proposal For");
                    if ($('input:radio:checked').length > 0)
                    {
                        $("#edit-field-submit-proposal-member").css("display", "block");
                        $("#edit-field-submit-proposal-to-company").css("display", "none");
                        $("#edit-field-submit-proposal-in-respons").css("display", "none");
                        $("#edit-field-field-sub-proposal-pjt").css("display", "none");
                    }
                });
                // Members click ends

                // Company click starts			
                $('#edit-field-choose-from-the-options-li-und-submit-proposal-to-a-company').click(function () {
									$div_st3 = $("#edit-field-submit-proposal-to-company").height() + 'px';
                    //$('#sub_menu4').css('min-height','100px'); 
                    $('#sub_menu1').css('min-height', '0px');
                    $('#sub_menu2').css('min-height', '0px');
                    $('#sub_menu3').css('min-height', $div_st3);
										
					/*					$("#views-form-m6companies-entityreference-view-widget-1 .entity-reference-view-widget-select.form-checkbox").live("click", function () {
                        var atLeastOneIsChecked3 = $('#views-form-m6companies-entityreference-view-widget-1 :checkbox:checked').length;
                        //$cou_click1 = atLeastOneIsChecked1 * 20;
                        $cou_click3 = 10;
                        $div3 = $("#edit-field-submit-proposal-to-company").height() + $cou_click3;
                        $('#sub_menu3').css('min-height', $div3 + 'px');
                    });*/
										
										
                    $('#edit-field-submit-proposal-to-company-und-add-more').val("Click Here to Select the company to Submit this eProposal For");
                    if ($('input:radio:checked').length > 0)
                    {
                        $("#edit-field-submit-proposal-to-company").css("display", "block");
                        $("#edit-field-submit-proposal-member").css("display", "none");
                        $("#edit-field-submit-proposal-in-respons").css("display", "none");
                        $("#edit-field-field-sub-proposal-pjt").css("display", "none");
                    }
                });
                // Company click ends			

                //if rfp,project,member,company is checked set min-height
                if ($('#edit-field-choose-from-the-options-li-und-submit-proposal-in-response-to-a-rfp').is(':checked'))
                {
                    $("#edit-field-submit-proposal-in-respons").css("display", "block");
                    $div_st1 = $("#edit-field-submit-proposal-in-respons").height() + 'px';
                    $('#sub_menu1').css('min-height', $div_st1);
                    $('#edit-field-submit-proposal-in-respons-und-add-more').val("Click Here to Select the RFP to Submit this eProposal For");
                }
                if ($('#edit-field-choose-from-the-options-li-und-submit-proposal-in-response-to-a-project').is(':checked'))
                {
                    $("#edit-field-field-sub-proposal-pjt").css("display", "block");
                    $div_st2 = $("#edit-field-field-sub-proposal-pjt").height() + 'px';
                    $('#sub_menu2').css('min-height', $div_st2);
                    $('#edit-field-field-sub-proposal-pjt-und-add-more').val("Click Here to Select the Projects to Submit this Proposal For");
                }
                if ($('#edit-field-choose-from-the-options-li-und-submit-proposal-to-an-individual-member').is(':checked'))
                {
                    $("#edit-field-submit-proposal-member").css("display", "block");
                    $div_st3 = $("#edit-field-submit-proposal-member").height() + 'px';
                    $('#sub_menu3').css('min-height', $div_st3);
                    $('#edit-field-submit-proposal-member-und-add-more').val("Click Here to Select the Individual Member(s) to Submit this Proposal For");
                }
                if ($('#edit-field-choose-from-the-options-li-und-submit-proposal-to-a-company').is(':checked'))
                {
                    $("#edit-field-submit-proposal-to-company").css("display", "block");
										$div_st3 = $("#edit-field-submit-proposal-to-company").height() + 'px';
                    $('#sub_menu3').css('min-height', $div_st3);
                    $('#edit-field-submit-proposal-to-company-und-add-more').val("Click Here to Select the Company to Submit this eProposal For");
                }
                //rfp is checked end min-height			


                // zip code validation starts
                /*$("#edit-field-proposal-bid-amount-und-0-value").keypress(function (e) {
                 //if the letter is not digit then display error and don't type anything
                 if (e.which != 8 && e.which != 0 && (e.which < 48 || e.which > 57)) {
                 //display error message
                 // $("#errmsg").html("Digits Only").show().fadeOut("slow");
                 return false;
                 }
                 }); */

                $('#edit-field-proposal-bid-amount-und-0-value').keyup(function (event) {

                    // skip for arrow keys
                    if (event.which >= 37 && event.which <= 40)
                        return;
                    // format number
                    $(this).val(function (index, value) {
                        return value
                                .replace(/\D/g, "")
                                .replace(/\B(?=(\d{3})+(?!\d))/g, ",")
                                ;
                    });
                });
                $("#edit-field-proposal-bid-amount-und-0-value").attr('onchange', 'fixit(this)');
                $('#edit-field-proposal-bid-amount .form-item.form-type-textfield.form-item-field-proposal-bid-amount-und-0-value').append('<input type="text" id="dol_sym" value=" $ " disabled/>');
                $('#edit-field-proposal-bid-amount-und-0-value').keyup(function () {
                    //$(this).val(function(i,v) {
                    // return '$' + v.replace('$',''); //remove exisiting, add back.
                    //});
                });
                $("#edit-field-proposal-job-location-und-0-postal-code").keypress(function (e) {
                    //if the letter is not digit then display error and don't type anything
                    if (e.which != 8 && e.which != 0 && (e.which < 48 || e.which > 57)) {
                        //display error message
                        // $("#errmsg").html("Digits Only").show().fadeOut("slow");
                        return false;
                    }
                });
                $("#edit-field-proposal-job-location-und-0-postal-code").keyup(function () {

                    var maxChars = 5;
                    if ($(this).val().length > maxChars) {
                        $(this).val($(this).val().substr(0, maxChars));
                        //Take action, alert or whatever suits          	
                    }
                });
                $(".form-item-title label").append("<strong class='form-required'>*</strong>");
                $(".form-item-field-proposal-scope-of-work-und-0-value label").append("<strong class='form-required'>*</strong>");
                $("#edit-field-proposal-bid-amount label").append("<strong class='form-required'>*</strong>");
                $("#edit-field-proposoal-bid-types>div>label").append("<strong class='form-required'>*</strong>");
                //popup comments starts
                $("#comment-form > div").addClass('create_pop_text_click');
                $("<div class='overlay'></div>").insertBefore(".create_pop_text_click");
                $("#comment-form #edit-actions").append('<a class="cancel_create_comment">Cancel</a>');
                $('#comment-form #edit-actions #edit-submit').val('Send New Message');
                $(".proposal_send_click").click(function () {
                    $serial_data_num = $(this).attr('data');
                    $("#serial_proposal_no").text(" " + $serial_data_num);
                    $("#comment-form").fadeIn();
                });
                $(".cancel_create_comment").click(function () {
                    $("#comment-form").fadeOut();
                });
                $(".overlay").click(function () {
                    $("#comment-form").fadeOut();
                });
                window.onkeydown = function (event) {
                    if (event.keyCode === 27) {
                        $("#comment-form").fadeOut();
                    }
                };
                //read popup starts
                $(".view_new_message").click(function () {
                    //alert($(this).attr('id'));		
                    $(".view_new_message_popup").fadeIn();
                });
                $(".cancel_create").click(function () {
                    $(".view_new_message_popup").fadeOut();
                    location.reload();
                });
                $(".view_new_message_popup .overlay").click(function () {
                    $(".view_new_message_popup").fadeOut();
                    location.reload();
                });
                //read popup ends

                //popup comments ends

                //starts
                /*
                 $("#navigation li a" ).live( "click", function() { 
                 alert("test");
                 $("#proposal_pop_content").fadeIn();
                 $(".pro_required_title").text("Auto Save Confirm");
                 $(".pro_required").text("Are you sure want to leave this page?");
                 $("#current_yes").css('display','block');
                 $("#current_no").css('display','block');
                 $(".current_pop").css('display','none');
                 return false;
                 
                 });
                 */
                //ends
<!--------------------------popup draft starts-------------------->

                $("#edit-actions input#edit-draft").live("click", function () {
                    $("#current_cancel").css('display', 'none');
                    $("#current_subproposal").css('display', 'none');
                    $("#confirm_title").text("Save as Draft");
                    $("#confirm_content").text("This proposal has been saved as a draft. You may continue working on this proposal and/or submit it at any time.");
                    $("#current_okey").css('display', 'block');
                    $("#confirm_pop_content").fadeIn();
                    return false;
                });
                $(".create_pop_text_new .close").click(function () {
                    $("#confirm_pop_content").fadeOut();
                });
                $(".create_pop_text_new .cancel_create").click(function () {
                    $("#confirm_pop_content").fadeOut();
                });
                $("#confirm_pop_content .overlay").click(function () {
                    $("#confirm_pop_content").fadeOut();
                });
                window.onkeydown = function (event) {
                    if (event.keyCode === 27) {
                        $("#confirm_pop_content").fadeOut();
                    }
                };
                $("#current_okey").click(function () {
                    $("#edit-draft").trigger("click");
                });
<!--------------------------popup draft ends-------------------->

                // Cancel Confirm submit proposal
                $("#current_subproposal").click(function () {
                    $("#edit-submit").trigger("click");
                });
                // Cancel Confirm submit proposal
                $("#current_cancel").click(function () {
                    $("#confirm_pop_content").fadeOut();
                });
            });
            //extra .00 in bit amount starts
            function fixit(obj) {
                obj.value = (obj.value) + '.00';
                //obj.value = parseFloat( obj.value ).toFixed( 2 )
            }
            //extra .00 in bit amount ends

            $('.node-type-my-proposal .message-close').text("Okey");
        }


        $(document).ready(function () {

            view_proposal = '<?php echo $content_type; ?>';
            if (view_proposal == 'my_proposal')
            {
                var author_contractor = $(".node-my-proposal > header .submitted a.username").text();
                $('#cont_name').html(author_contractor);
                var addresspro1 = $("div.thoroughfare").text();
                $('#addr-pro').html(addresspro1);
                var city_myproposal = $("span.locality").text();
                var postal = $(".postal-code").html();
                $('#addr-pro-city').html(city_myproposal );					
                var state_myproposal = $("span.state").text();
                $('#addr-pro-state').html(city_myproposal + " " + state_myproposal + " " + postal);
                var country_myproposal = $("span.country").text();
                $('#addr-pro-country').html(country_myproposal);
                $("#view_map").each(function () {
                    var embed = "<iframe width='238' height='238' frameborder='0' scrolling='no' marginheight='0' marginwidth='0' src='https://maps.google.com/maps?&amp;q=" + encodeURIComponent($(this).text()) + "&amp;output=embed'></iframe>";
                    $('#map_dis').html(embed);
                });
                //$("#my-proposal-node-form #edit-draft").val('Save as Draft');
                //$('#my-proposal-node-form #edit-submit').val('Save as Draft'); 

            }


        });
        function myFunctionCancel() {
            Drupal.CTools.Modal.dismiss();
        }

    </script>
<style>
  .droppable-controls #ajax_msg > div {  display: block !important; }
</style>

<!--- create Proposal popup start --->

<div id="proposal_pop_content">
  <div class="overlay"></div>
  <!--overlay-->
  
  <div class="proposal_pop_text">
    <div class="proposal_pop_text_inner"> 
      <!--<a href="#close" class="close"><img src="images/close.png" /></a>-->
      <h2 class="pro_required_title" style="font-weight:bold">Submit RFP For</h2>
      <p class="pro_required"></p>
      <button id="current_pop" class="pro_close"  type="button">close</button>
    </div>
    <!--pop text inner--> 
  </div>
  <!--pop text--> 
</div>
<!--pop content--> 

<!--- create Proposal popup end --->

<div id="confirm_pop_content">
  <div class="overlay"></div>
  <!--overlay-->
  <div class="create_pop_text_new" id="send_pop_text_new"> 
    
    <!--<div class="pop-main-top1">
                    <a href="#close" class="close"><img src="images/pop_close.png"/></a>
                    </div>-->
    <div class="create_new_pop_inner_con_sub">
      <h2 id="confirm_title"></h2>
      <p id="confirm_content"></p>
      <div class="create_new_btn_last" id="send_new_message">
        <input type="submit" style="display:none" class="form-submit " value="Okay" name="op" id="current_okey">
        <input type="button" style="display:none" class="form-submit " value="Cancel" name="op" id="current_cancel">
        <input type="submit" style="display:none" class="form-submit " value="Submit eProposal" name="op" id="current_subproposal">
        <!--<a href="#" class="cancel_create">Cancel</a>--> 
      </div>
    </div>
    <!--create_new_pop_inner1--> 
  </div>
  <!--create_pop_text_new_new--> 
</div>
<!--confirm_pop_content--> 