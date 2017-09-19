<?php
global $user, $company;
module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
//module_load_include('module','m6connect_misc','custom/m6connect_misc/m6connect_misc');
module_load_include('inc', 'user_relationships', 'user_relationships_ui/user_relationships_ui.pages');
//relationships load
$relationships = user_relationships_load(array('approved' => $user->uid, 'approved' => FALSE, 'requestee_id' => $user->uid));
$relation_rows = array();
foreach ($relationships as $relationship) {
    $requester = user_load($relationship->requester_id);
    $relation_rows[] = array('name' => $requester->realname, 'links' => user_relationships_ui_get_table_row($relationship, $user));
}
//*************end***********
$user_obj = user_load($user->uid);
$companies_detail = m6connect_misc_get_user_all_companies($user->uid);
drupal_add_js(drupal_get_path('module', 'm6connect_dashboard') . '/m6connect_dash.js');

?>

<div class="container-fluid">
  <div class="text-center">
    <h2>Welcome To Your Dashboard</h2>
  </div>
  <div class="dashboard-block-fb clearfix">
    <div class="left-block-20 pull-left">
      <div class="dashboard-block-darkgray">
        <div class="dashboard-block-items form-group">
          <div class="dashboard-block-account">
            <div class="row margin-5">
              <div class="dashboard-user-pic col-md-3 padding-5"><img typeof="foaf:Image" src="<?php echo image_style_url('user_pic_40x40',$user_obj->field_user_profile_photo['und']['0']['uri']); ?>" alt=""></div>
              <div class="dashboard-user col-md-9 padding-5">
                <div class="dashboard-userneame clearfix form-group"> 
                  <!--<div class="pull-left"><a href="#" title="John Clark">John Clark</a></div>-->
                  <div class="pull-left">
                    <?php
					echo l(t($user_obj->realname), 'user/' . $user->uid, array('html' => TRUE, 'attributes' => array('title' => $user_obj->realname)));
					?>
                  </div>
                  <div class="pull-right">
                    <?php
					  echo l('<i class="fa fa-cog"></i>', 'user/' . $user->uid . '/edit', array('html' => TRUE, 'attributes' => array('title' => 'edit')));
					  ?>
                  </div>
                </div>
                <!--<div class="dashboard-logout"><a href="#" title="Log Out"><i class="fa fa-power-off"></i> Log Out</a></div>-->
                <div class="dashboard-logout">
                  <?php
					echo l('<i class="fa fa-power-off"></i> Log Out', 'user/logout', array('html' => TRUE, 'attributes' => array('title' => "Log Out")));
					?>
                </div>
              </div>
            </div>
          </div>
        </div>
        <div class="dashboard-block-items">
          <div class="dashboard-block-heading">Account</div>
          <div class="dashboard-block-content">
            <ul class="dashboard-block-list">
              <li> 
                <!--<a href="#" title="Dashboard Home"><i class="fa fa-compass"></i>Dashboard Home</a>--> 
                <?php echo l('<i class = "fa fa-compass"></i>Dashboard Home', 'custom/page1', array('html' => TRUE, 'attributes' => array('title' => "Dashboard Home"))); ?> </li>
              <li><a href="#" title="Profiles"><span class="dashboard-icons"><img src="/sites/all/themes/m6connect/images/icon-profile.png" alt="profile" /></span>Profiles</a>
                <ul>
                  <?php
					foreach ($companies_detail as $key => $val) {
					?>
                  <!--<a href="#" title="John Clark">John Clark</a>-->
                  <li><?php echo l($val->title, 'node/' . $val->nid, array('html' => TRUE, 'attributes' => array('title' => $val->title))); ?></li>
                  <?php } ?>
                  <!--<li><a href="#" title="John Clark">ESport Solutions</a></li>-->
                </ul>
              </li>
            </ul>
          </div>
        </div>
        <div class="dashboard-block-items">
          <div class="dashboard-block-heading">My Services</div>
          <div class="dashboard-block-content">
            <ul class="dashboard-block-list">
              <li> 
                <!--<a href="#" title="Projects"><i class="fa fa-file"></i>Projects</a>-->
                <?php
				echo l('<span class="dashboard-icons"><img src="/sites/all/themes/m6connect/images/icon-project.png" alt="project" /></span>Projects', 'projects', array('html' => TRUE, 'attributes' => array('title' => "Projects")));
				?>
              </li>
              <li> 
                <!--<a href="#" title="RFPs"><i class="fa fa-file"></i>RFPs</a>-->
                <?php
				echo l('<span class="dashboard-icons"><img src="/sites/all/themes/m6connect/images/icon-rfp.png" alt="rfp" /></span>RFPs', 'rfps/received', array('html' => TRUE, 'attributes' => array('title' => "RFPs")));
				?>
              </li>
              <li> 
                <!--<a href="#" title="Proposals"><i class="fa fa-thumbs-up"></i>Proposals</a>-->
                <?php
				echo l('<i class="fa fa-thumbs-up"></i>Proposals', 'proposals/sent', array('html' => TRUE, 'attributes' => array('title' => "Proposals")));
				?>
              </li>
            </ul>
            <h4>Available Services <i class="fa fa-cart-plus"></i></h4>
            <ul class="dashboard-block-list">
              <li><a href="#" title="Ranks"><i class="fa fa-square"></i>Ranks</a></li>
              <li><a href="#" title="OnBoarding"><i class="fa fa-square"></i>OnBoarding</a></li>
            </ul>
          </div>
        </div>
        <div class="dashboard-block-items">
          <div class="dashboard-block-heading">Connections</div>
          <div class="dashboard-block-content"> 
            <!-- accordion-->
             <?php if(count($relation_rows) > 0){ ?>
            <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
              <div class="panel panel-default">
                <div class="panel-heading" role="tab" id="headingOne">
                  <h4 class="panel-title">
                   
                    <i class="fa fa-arrow-circle-o-right"></i><a role="button" data-toggle="collapse" data-parent="#accordion" href="#collapseOne" aria-expanded="true" aria-controls="collapseOne"> <?php echo count($relation_rows); ?> Requests </a> </h4>
                </div>
                <div id="collapseOne" class="panel-collapse collapse" role="tabpanel" aria-labelledby="headingOne">
                  <?php foreach ($relation_rows as $key) { ?>
                  <div class="panel-body"> <?php echo $key['name'] . ' (' . $key['links'][1] . ')  ' . $key['links'][2]; ?> </div>
                  <?php } ?>
                </div>
              </div>
            </div>
            <?php } ?>
            
            <!-- accordion-->
            <ul class="dashboard-block-list">
              <li><a href="#" title="People"><span class="dashboard-icons"><img src="/sites/all/themes/m6connect/images/icon-people.png" alt="people" /></span>People</a>
                <ul>
                  <?php
$relationship_types = user_relationships_types_load();
foreach ($relationship_types as $key => $val) {
    ?>
                  <li> 
                    <!--<a href="#" title="Friends">Friends</a>-->
                    <?php
					  echo l($val->name, 'user/' . $user->uid . '/relationships/' . $val->rtid, array('html' => TRUE, 'attributes' => array('title' => $val->name)));
					  ?>
                  </li>
                  <?php } ?>
                </ul>
              </li>
            </ul>
            <div class="gray-text"> 
              <!--                            <h4><i class="fa fa-plus"></i> Create New Catagory</h4>-->
              <h4><i class="fa fa-eye"></i> Find People</h4>
            </div>
            <ul class="dashboard-block-list">
              <li><a href="#" title="Companies Followed"><i class="fa fa-building"></i>Companies Followed</a>
                <ul>
                  <li><a href="#" title="Emsick Design Company">Emsick Design Company</a></li>
                  <li><a href="#" title="Betty White Industries">Betty White Industries</a></li>
                </ul>
              </li>
            </ul>
            <div class="gray-text">
              <?php
				echo l('<h4><i class="fa fa-eye"></i> Find Companies</h4>', 'companies', array('html' => TRUE, 'attributes' => array('title' => "Companies")));
				?>
            </div>
            <ul class="dashboard-block-list">
              <li><a href="#" title="M6Cliques"><i class="fa fa-bullseye"></i>M6Cliques</a>
                <ul >
                  <div id="private_groups">
                    <?php
					  print views_embed_view('copy_group_list', 'block_2');
					  ?>
                  </div>
                </ul>
              </li>
            </ul>
            <div class="gray-text">
              <h4>
                <?php
				  echo l(' <i class="fa fa-plus"></i> Create Clique', 'add/group/private', array('html' => TRUE, 'attributes' => array('title' => "Create Clique")));
				  ?>
              </h4>
            </div>
            <ul class="dashboard-block-list">
              <li><a href="#" title="Groups"><i class="fa fa-users"></i>Groups</a>
                <ul>
                  <div id="public_groups">
                    <?php
						print views_embed_view('copy_group_list', 'block_1');
						?>
                  </div>
                </ul>
              </li>
            </ul>
            <div class="gray-text">
              <h4>
                <?php
				  echo l(' <i class="fa fa-plus"></i> Create Group', 'add/group/public', array('html' => TRUE, 'attributes' => array('title' => "Create Group")));
				  ?>
              </h4>
              <h4><i class="fa fa-eye"></i> Find Groups</h4>
            </div>
          </div>
        </div>
        <div class="dashboard-block-items">
          <div class="dashboard-block-heading clearfix">Favorites <span class="pull-right"> 
            <!--work--> 
            <i class="fa fa-cog"></i>
            <?php
                            //echo l('<i class="fa fa-cog"></i>', 'javascript:void(0);', array('html' => TRUE, 'external' => true, 'attributes' => array('class' => array('user_profile', 'custom-m6connect-misc-link'), 'title' => 'Notification', 'id' => 'user-Notification-gear', 'data-target' => '#', 'data-toggle' => 'dropdown', 'role' => 'button', 'aria-haspopup' => 'true', 'aria-expanded' => 'false')));
                            //echo '<div class="dropdown-menu" ><div class="user-notification-outer">';
                            ?>
            <!--end--> 
            </span></div>
          <div class="dashboard-block-content">
            <ul class="dashboard-block-list">
              <li><a href="#" title="Frank Emsick"><i class="fa fa-smile-o"></i>Frank Emsick</a></li>
              <li><a href="#" title="ESport Solutions LLC"><i class="fa fa-building"></i>ESport Solutions LLC</a></li>
              <li><a href="#" title="Project ABC"><span class="dashboard-icons"><img src="/sites/all/themes/m6connect/images/icon-project.png" alt="project" /></span>Project ABC</a></li>
              <li><a href="#" title="Billy Bob Thortan"><i class="fa fa-smile-o"></i>Billy Bob Thortan</a></li>
              <li><a href="#" title="Landmark Proposal"><i class="fa fa-thumbs-up"></i>Landmark Proposal</a></li>
              <li><a href="#" title="RFP: Sandhills Project"><span class="dashboard-icons"><img src="/sites/all/themes/m6connect/images/icon-rfp.png" alt="rfp" /></span>RFP: Sandhills Project</a></li>
            </ul>
          </div>
        </div>
        <div class="dashboard-block-items">
          <div class="dashboard-block-heading clearfix">Bookmark Folders <span class="pull-right"><i class="fa fa-cog"></i></span></div>
          <div class="dashboard-block-content">
            <form class="dashboard-block-search">
              <div class="form-group">
                <button type="submit" class="btn btn-default search-button">Search</button>
                <input type="text" class="form-control" id="search">
              </div>
            </form>
            <ul class="dashboard-block-list">
              <li><a href="#" title="All Bookmarks & Folders"><i class="fa fa-folder-o"></i>All Bookmarks & Folders</a></li>
              <li><a href="#" title="Projects"><i class="fa fa-folder-o"></i>Projects</a></li>
              <li><a href="#" title="RFPs"><i class="fa fa-folder-o"></i>RFPs</a></li>
              <li><a href="#" title="Proposals"><i class="fa fa-folder-o"></i>Proposals</a></li>
              <li><a href="#" title="People"><i class="fa fa-folder-o"></i>People</a></li>
              <li><a href="#" title="Companies"><i class="fa fa-folder-o"></i>Companies</a>
                <ul class="dashboard-block-small-list">
                  <li><a href="#" title="Emsick Industries">Emsick Industries <span class="pull-right"><i class="fa fa-trash-o"></i> <i class="fa fa-star"></i></span></a></li>
                  <li><a href="#" title="ESport Solutions LLC">ESport Solutions LLC <span class="pull-right"><i class="fa fa-arrow-circle-o-right"></i> <i class="fa fa-trash-o"></i> <i class="fa fa-star"></i></span></a></li>
                  <li><a href="#" title="Lund-Ross Constructors">Lund-Ross Constructors <span class="pull-right"><i class="fa fa-trash-o"></i> <i class="fa fa-star"></i></span></a></li>
                  <li><a href="#" title="Metropolitan Comm...">Metropolitan Comm... <span class="pull-right"><i class="fa fa-arrow-circle-o-right"></i> <i class="fa fa-trash-o"></i> <i class="fa fa-star"></i></span></a></li>
                </ul>
              </li>
            </ul>
          </div>
        </div>
      </div>
    </div>
    <div class="left-block-28 pull-left">
      <div class="dashboard-block-lightgray">
        <div class="dashboard-block-content">
 
        </div>
      </div>
    </div>
    <div class="left-block-28 pull-left">
      <div class="dashboard-block-lightgray">
        <div class="dashboard-block-content group_newsfeed">
          <?php

			print render(drupal_get_form('statuses_box', $company, 'og'));
                        ?>
            <div id="cutom_statuses_stream_div">
                            <?php
			print views_embed_view('cutom_statuses_stream', 'block_1', $company->nid);
			?>
            </div>
        </div>
      </div>
    </div>
    <!--  <div class="left-block-24 pull-left">
              <div class="dashboard-block-lightgray">
                  <h3 class="dashboard-block-title">Recommended Companies</h3>
              </div>
          </div> --> 
  </div>
</div>
