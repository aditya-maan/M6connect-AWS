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
  <div id="navigation">
    <div class="container"><?php print render($page['navigation']); ?></div>
  </div>
  <?php $wrapperClass =''; if(isset($_SESSION['left_block_action']) && $_SESSION['left_block_action']=='open'){ $wrapperClass='active'; } ?>
  <div id="wrapper" class="<?php print $wrapperClass; ?> clearfix">
    <div id="sidebar-wrapper">
      <?php if ($page['left_content']): ?>
      <?php print render($page['left_content']); ?>
      <?php endif; ?>
    </div>
    <div id="page-content-wrapper">
      <div class="page-content inset">
        <div id="main">
          <div class="container-fluid">
            <div class="top_header clearfix">
              <?php if ($page['top_header']): ?>
              <?php print render($page['top_header']); ?>
              <?php endif; ?>
            </div>
            <div id="content" class="column" role="main">
              <div class="box">
                <div class="inner-box">
                  <div class="white-bg">
                    <div class="clearfix">
                      <div class="pull-left"><?php print $breadcrumb; ?> <a id="main-content"></a> <?php print render($title_prefix); ?>
                        <?php if ($title): ?>
                        <h1 class="page__title title" id="page-title">
                          <?php 
                                    if( arg(0)=='statuses' && is_numeric(arg(1)) && !arg(2)){											 
                                      $newbtitle = explode(' » ', $title);
                                      if(isset($newbtitle[1])){										 
                                        print $newbtitle[0].' with '.$newbtitle[1]; 
                                      }
                                    }else{
                                      print $title;	
                                    }
                                    
                                   ?>
                        </h1>
                        <?php endif; ?>
                        <?php print render($title_suffix); ?> </div>
                      <div class="pull-right">
                        <div class="highlighted"> <?php print render($page['highlighted']); ?> </div>
                      </div>
                    </div>
                    <?php print $messages; ?> <?php print render($tabs); ?> <?php print render($page['help']); ?>
                    <?php if ($action_links): ?>
                    <ul class="action-links">
                      <?php print render($action_links); ?>
                    </ul>
                    <?php endif; ?>
                    <?php if(arg(0)=='node' && is_numeric(arg(1)) && arg(2)=='edit'){
												  $node = menu_get_object();
													if($node->type=='contract'){
												    print render($page['content']);
													}
												}
										?>
                    <div class="contract-view-page">
                      <?php
												if(arg(0)=='node' && is_numeric(arg(1)) && empty(arg(2))){													
												  $node = menu_get_object();
													if($node->type=='contract'){
													  $contract_body = render(field_view_field('node', $node, 'body', array('label' => 'hidden')));
												    $contract_project = render(field_view_field('node', $node, 'field_contract_project_list', array('label' => 'hidden')));
													  $contract_upload = render(field_view_field('node', $node, 'field_file_upload', array('label' => 'hidden')));
														
														if(!empty($contract_body)){
															print '<div class="field field-label-inline clearfix">
																			<div class="field-label">Description:&nbsp;</div>
																			  <div class="contract-item">'
																			  .$contract_body.
																		    '</div>
																		 </div>';
														}
														if(!empty($contract_upload)){
															print '<div class="field field-label-inline clearfix">
																			<div class="field-label">File Upload:&nbsp;</div>
																			  <div class="contract-item">'
																			  .$contract_upload.
																		    '</div>
																		</div>';
														}
														if(!empty($contract_project)){
															print '<div class="field field-label-inline clearfix">
																			<div class="field-label">Project:&nbsp;</div>
																			  <div class="contract-item">'
																			  .$contract_project.
																		    '</div>
																		 </div>';
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
        </div>
      </div>
    </div>
  </div>
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
