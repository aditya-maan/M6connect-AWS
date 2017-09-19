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
  <div id="preface" class="<?php if (!$page['preface']) { print 'dispaly_none'; } else { print 'preface'; } ?>">
    <div class="container-fluid"><?php print render($page['preface']); ?></div>
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
            <div class="top_header clearfix">
              <?php if ($page['top_header']): ?>
              <?php print render($page['top_header']); ?>
              <?php endif; ?>
            </div>
            <div class="middle-page">
              <div class="box">
                <div class="inner-box <?php if (isset($node) && in_array($content_type, array('project'))) { print 'project_node_page'; } ?>">
                  <div class="<?php if (isset($node) && in_array($content_type, array('project'))) { print 'project_clear'; } ?>">
                    <div class="white-bg">
                      <div class="right_content clearfix">
                        <div class="content_inner_pages">
                          <div id="content" class="column" role="main">
                            <div class="content-page"> <?php print $messages; ?> <?php print render($page['help']); ?>
                              <?php if ($action_links): ?>
                              <ul class="action-links">
                                <?php print render($action_links); ?>
                              </ul>
                              <?php endif; ?>
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
