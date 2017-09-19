<?php
//******************************************************dashbard 4 start *****************************************************/
function custom_hcfm_dashboard4_section_layout(){
  global $user, $company;
  drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.masonry.min.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/highcharts-3d.js');
  drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/funnel.js'); 
  drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/highcharts-more.js'); 
  drupal_add_js(drupal_get_path('module', 'm6connect_program') . '/js/jquery.multiselect.js');
  drupal_add_css(drupal_get_path('module', 'm6connect_program') . '/js/jquery.multiselect.css');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/exporting.js');
  module_load_include('inc', 'statuses', 'includes/utility/statuses.form');
  $TileId = array('a'=>'assets','b'=>'open_pms','c'=>'open_cms','d'=>'projects','e'=>'parts_on_order','f'=>'back_log','g'=>'work_order_focus','h'=>'square_foot','i'=>'labor','j'=>'labor_sf','k'=>'labor_use','l'=>'labor_forecast');
  $tilesData = variable_get('hcfm_dashboard_table_configure_list'); 
  $userCom = (isset($company,$company->nid) && !empty($company->nid) && is_numeric($company->nid) ? $company->nid: 'none');
  $output = '';  
  $output .= '<div class="hcfm-dashboard-section">';
  $output .=  '<div class="clserfix" style="display:none"><div class="text-right"><a href="javascript:void(0);" class="chart_width1">chart_width1</a><a href="javascript:void(0);" class="chart_width2">chart_width2</a><a href="javascript:void(0);" class="chart_width3">chart_width3</a></div></div>';
  $output .=  '<div class="clserfix"><div class="text-right">'.l('Configure','hcfm/dashboard/configure/nojs', array('html'=>TRUE,'attributes'=>array('class'=>array('ctools-use-modal','ctools-modal-assign-dashboard-popup-style','dashboard_configuration_btn')))).'</div></div>';
  // row One start  
  $output .= '<div class="row margin-5 levelone">'; 
  //col-md-4 start 
  $output .=   '<div class="col-md-4 col-sm-12 col-xs-12 padding-5 one-main-section">'; 
  $output .=     '<div class="hcfm_timeline_outer">';
  $output .=       '<div class="hcfm_cutom_statuses_box">';
  $output .=         render(drupal_get_form('statuses_box', $user, 'hcfm_user'));
  $output .=       '</div>';  
                    $GUdata = _get_user_mail_realname_by_uid($user->uid);
  $output .=      '<div class="hcfmcompany-user-list-contaner share-container">
                    <div class="dropdown">
              <a id="dLabel2" class="btn btn-default" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">'.ucfirst($GUdata['realname']).'</a>
                        <ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="dLabel2">';
              $company_users = m6connect_misc_get_company_users_by_cnid($company->nid);
                          foreach($company_users as $key=>$uid){
                  $Udata = _get_user_mail_realname_by_uid($uid);
              $output .= '<li>'.l(ucfirst($Udata['realname']), 'hcfm-switch-dashboard/hcfm_user/' . $uid . '/nojs', array('html' => TRUE, 'attributes' => array('title' => $Udata['realname'], 'class' => 'use-ajax'))).'</li>';
              }
  $output .=            '</ul>
            </div>
           </div>';
  $output .=       '<div id="cutom_statuses_stream_div">';                           
  $output .=         views_embed_view('hcfm_statuses_stream', 'block_1', $user->uid);
  $output .=       '</div>';
  $output .=     '</div>';
  $output .=   '</div>';
  //col-md-4 end  
  //col-md-10 start  
  $output .=   '<div class="col-md-8 col-sm-12 col-xs-12 padding-5 two-main-section">';
  //col-md-10 in row start 
  $output .=     '<div class="row margin-5 tile-section"><div class="itemorder"></div>';
  
                   $TileA = (isset($tilesData[$userCom]['user'][$user->uid]['data']['a']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['a']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['a']['id']:'a');  
  $output .=       '<div id="'.$TileId[$TileA].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item0" tile-status="closed" original-pos="item0" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';

  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
                        '.hcfm_dashboard_tile_callback($TileA).'
                          

                        <div class="tile-expand-left ajax-progress-hide">
                          <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                            <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                          </a>                          
                          <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                            <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                          </a>
                          <a href="/hcfmdashtilerender/'.$TileId[$TileA].'/normal/'.$TileA.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                            Medium
                          </a>
                          <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                            <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                          </a>
                          <a href="/hcfmdashtilerender/'.$TileId[$TileA].'/large/'.$TileA.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                            Large
                          </a>
                          <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                            <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                          </a>
                          <a href="/hcfmdashtilerender/'.$TileId[$TileA].'/compare/'.$TileA.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                            Compare
                          </a>
                          <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                            <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                          </a>
                          <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                            <img title="downarrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                          </a>                          
                          <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                            <img title="setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                          </a>
                        </div>
                      </div>';

  $output .=       '</div>';
                   $TileB = (isset($tilesData[$userCom]['user'][$user->uid]['data']['b']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['b']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['b']['id']:'b');
                   
  $output .=       '<div id="'.$TileId[$TileB].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item1" tile-status="closed" original-pos="item1" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileB).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileB].'/normal/'.$TileB.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileB].'/large/'.$TileB.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileB].'/compare/'.$TileB.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
            </div>';
  $output .=       '</div>';
                   $TileC = (isset($tilesData[$userCom]['user'][$user->uid]['data']['c']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['c']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['c']['id']:'c');
  $output .=       '<div id="'.$TileId[$TileC].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item2" tile-status="closed" original-pos="item2" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileC).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileC].'/normal/'.$TileC.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileC].'/large/'.$TileC.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileC].'/compare/'.$TileC.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileD = (isset($tilesData[$userCom]['user'][$user->uid]['data']['d']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['d']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['d']['id']:'d');
  $output .=       '<div id="'.$TileId[$TileD].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item3" tile-status="closed" original-pos="item3" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileD).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileD].'/normal/'.$TileD.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileD].'/large/'.$TileD.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileD].'/compare/'.$TileD.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileE = (isset($tilesData[$userCom]['user'][$user->uid]['data']['e']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['e']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['e']['id']:'e');
  $output .=       '<div id="'.$TileId[$TileE].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item4" tile-status="closed" original-pos="item4" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileE).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileE].'/normal/'.$TileE.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileE].'/large/'.$TileE.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileE].'/compare/'.$TileE.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileF = (isset($tilesData[$userCom]['user'][$user->uid]['data']['f']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['f']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['f']['id']:'f');  
  $output .=       '<div id="'.$TileId[$TileF].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item5" tile-status="closed" original-pos="item5" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileF).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileF].'/normal/'.$TileF.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileF].'/large/'.$TileF.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileF].'/compare/'.$TileF.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileG = (isset($tilesData[$userCom]['user'][$user->uid]['data']['g']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['g']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['g']['id']:'g');  
  $output .=       '<div id="'.$TileId[$TileG].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item6" tile-status="closed" original-pos="item6" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileG).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileG].'/normal/'.$TileG.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileG].'/large/'.$TileG.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileG].'/compare/'.$TileG.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileH = (isset($tilesData[$userCom]['user'][$user->uid]['data']['h']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['h']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['h']['id']:'h');  
  $output .=       '<div id="'.$TileId[$TileH].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item7" tile-status="closed" original-pos="item7" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileH).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileH].'/normal/'.$TileH.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileH].'/large/'.$TileH.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileH].'/compare/'.$TileH.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileI = (isset($tilesData[$userCom]['user'][$user->uid]['data']['i']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['i']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['i']['id']:'i');  
  $output .=       '<div id="'.$TileId[$TileI].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item8" tile-status="closed" original-pos="item8" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileI).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileI].'/normal/'.$TileI.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileI].'/large/'.$TileI.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileI].'/compare/'.$TileI.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileJ = (isset($tilesData[$userCom]['user'][$user->uid]['data']['j']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['j']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['j']['id']:'j');  
  $output .=       '<div id="'.$TileId[$TileJ].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item9" tile-status="closed" original-pos="item9" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileJ).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileJ].'/normal/'.$TileJ.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileJ].'/large/'.$TileJ.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileJ].'/compare/'.$TileJ.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileK = (isset($tilesData[$userCom]['user'][$user->uid]['data']['k']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['k']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['k']['id']:'k');  
  $output .=       '<div id="'.$TileId[$TileK].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item10" tile-status="closed" original-pos="item10" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">
            '.hcfm_dashboard_tile_callback($TileK).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileK].'/normal/'.$TileK.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileK].'/large/'.$TileK.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileK].'/compare/'.$TileK.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="Setting" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
                   $TileL = (isset($tilesData[$userCom]['user'][$user->uid]['data']['l']['id']) && !empty($tilesData[$userCom]['user'][$user->uid]['data']['l']['id'])?$tilesData[$userCom]['user'][$user->uid]['data']['l']['id']:'l');  
  $output .=       '<div id="'.$TileId[$TileL].'" class="col-md-3 padding-5 margin-bottom-10 tile-item item11" tile-status="closed" original-pos="item11" updated-pos="" compare-status="normal" open-status="small" tile-show="front">';
  $output .=         '<div style="box-shadow: none;" class="tile-thumbnail thumbnail relative tile-height-normal margin-0" box-status="small" style="background:#e0ecf5;">                        
            '.hcfm_dashboard_tile_callback($TileL).'
              <div class="tile-expand-left ajax-progress-hide">
                <a href="javascript:void(0);" class="tile-expand-small-btn padding-5">
                  <img title="Small" src="/sites/all/themes/m6connect/images/hcfm/hcfm-small.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-medium-btn padding-5">
                  <img title="Medium" src="/sites/all/themes/m6connect/images/hcfm/hcfm-medium.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileL].'/normal/'.$TileL.'/nojs" class="use-ajax tile-expand-mediumcallback-btn padding-5" style="display:none;">
                  Medium
                </a>
                <a href="javascript:void(0);" class="tile-full-btn tile-expand-large-btn padding-5">
                  <img title="Large" src="/sites/all/themes/m6connect/images/hcfm/hcfm-large.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileL].'/large/'.$TileL.'/nojs" class="use-ajax tile-full-btn tile-expand-largecallback-btn padding-5" style="display:none;">
                  Large
                </a>
                <a href="javascript:void(0);" class="tile-full-compare-btn tile-expand-compare-btn padding-5">
                  <img title="Compare" src="/sites/all/themes/m6connect/images/hcfm/hcfm-compare.png">
                </a>
                <a href="/hcfmdashtilerender/'.$TileId[$TileL].'/compare/'.$TileL.'/nojs" class="use-ajax tile-full-btn tile-expand-comparecallback-btn padding-5" style="display:none;">
                  Compare
                </a>
                <a href="javascript:void(0);" class="tile-reset-compare-btn tile-expand-resetcompare-btn padding-5">
                  <img title="Clear" src="/sites/all/themes/m6connect/images/hcfm/hcfm-delete.png">
                </a>
                <a href="javascript:void(0);" class="tile-expand-compareback-btn">
                  <img title="downarrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-downarrow.png">                  
                </a>
                <a href="javascript:void(0);" class="tile-expand-mlsetting-btn" tile-show="front" style="display:none;">
                  <img title="uparrow" src="/sites/all/themes/m6connect/images/hcfm/hcfm-setting.png">                  
                </a>
              </div>
              </div>';
  $output .=       '</div>';
  $output .=     '</div>';
  //col-md-10 in row end
  $output .=   '</div>';
  //col-md-10 end  
  $output .= '</div>';
  //row one end
  $output .= '</div>';  
  return $output; 
}


/////////////////////* dashboard configure start *************//////////////////////

function custom_hcfm_dashboard_configure_callback($ajax=NULL){
 // module_load_include('inc', 'm6connect_hcfm', 'includes/m6connect_hcfm');
  ctools_include('ajax');
  ctools_include('modal');
  if($ajax){
    $form_state = array(
      'title' => '<div style="font-size:15px;padding-top:10px;">Hcfm Configure</div>',
      'ajax' => TRUE,      
    );
    $output = ctools_modal_form_wrapper('custom_hcfm_dashboard_configure_section', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit(); 
  }
  else{
    return drupal_get_form('custom_hcfm_dashboard_configure_section'); 
  }
}

function custom_hcfm_dashboard_configure_section($form, &$form_state) {
  global $user,$company;
  $tiles_1['a'] = array('id'=>'a','title'=>'ASSETS','weight'=>0);
  $tiles_1['b'] = array('id'=>'b','title'=>'OPEN PMs','weight'=>0);
  $tiles_1['c'] = array('id'=>'c','title'=>'OPEN CMs','weight'=>0);
  $tiles_1['d'] = array('id'=>'d','title'=>'PROJECTS','weight'=>0);
  $tiles_1['e'] = array('id'=>'e','title'=>'PARTS ON ORDER','weight'=>0);
  $tiles_1['f'] = array('id'=>'f','title'=>'BACK LOG','weight'=>0);
  $tiles_1['g'] = array('id'=>'g','title'=>'WORK ORDER FOCUS','weight'=>0);
  $tiles_1['h'] = array('id'=>'h','title'=>'SQUARE FOOT','weight'=>0);
  $tiles_1['i'] = array('id'=>'i','title'=>'LABOR','weight'=>0);
  $tiles_1['j'] = array('id'=>'j','title'=>'LABOR / SF','weight'=>0);
  $tiles_1['k'] = array('id'=>'k','title'=>'LABOR USE','weight'=>0);
  $tiles_1['l'] = array('id'=>'l','title'=>'LABOR FORECAST','weight'=>0);
  $userCom = (isset($company,$company->nid) && !empty($company->nid) && is_numeric($company->nid) ? $company->nid: 'none');
  $tiles = variable_get('hcfm_dashboard_table_configure_list');  
  if(isset($tiles) && !empty($tiles[$userCom]['user'][$user->uid]['data'])){
    $tiles = $tiles[$userCom]['user'][$user->uid]['data'];
  }else{
    $tiles = $tiles_1;
  }
  $form['#tree'] = TRUE;
  foreach ($tiles as $id => $tile) {
    $form['tiles'][$tile['id']]['id'] = array(
      '#type' => 'hidden',
      '#value' =>$tile['id'],
    );
    $form['tiles'][$tile['id']]['title'] = array(
      '#type' => 'textfield',
      '#value' => $tile['title'],
    '#disabled' => TRUE,
    );
    $form['tiles'][$tile['id']]['weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      '#default_value' => $tile['weight'],
    );   
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save changes'));  
  $form['close'] = array(
        '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),        
    );
  return $form;
}

function custom_hcfm_dashboard_configure_section_submit($form, &$form_state) {  //pre($form_state['values']['tiles'],1);
  global $user,$company;  
  $tiles = array();
  $var = array();
  $getVar = variable_get('hcfm_dashboard_table_configure_list');
  if (isset($form_state['values']['tiles']) && !empty($form_state['values']['tiles'])) {
    usort($form_state['values']['tiles'], '_dashboard_configure_arraysort');  
    $tUP = array(0=>'a',1=>'b',2=>'c',3=>'d',4=>'e',5=>'f',6=>'g',7=>'h',8=>'i',9=>'j',10=>'k',11=>'l');
  foreach ($form_state['values']['tiles'] as $key => $tile) {
    $tiles[$tUP[$key]] = array(
    'id' => $tile['id'],
    'title' => $tile['title'],
    'weight' => $tile['weight'],
    );
  } 
  }
  
  $userCom = (isset($company,$company->nid) && !empty($company->nid) && is_numeric($company->nid) ? $company->nid: 'none');
  $var[$userCom] = array('user'=>array($user->uid =>array( 'data'=>$tiles)));  
  $dash_configure_final = array_replace_recursive($getVar ,$var); 
  //drup_msg($getVar );
  //drup_msg($var );
  //drup_msg($dash_configure_final ); 

  //drup_msg($form_state['values']['tiles']);
  variable_set('hcfm_dashboard_table_configure_list', $dash_configure_final);
  if((isset($form_state['ajax']))?(($form_state['ajax']==1)?true:false):false) {    
    $form_state['ajax_commands'][] = ctools_ajax_command_redirect('/hcfm/dashboard4');
    drupal_set_message(t('Configure have been saved.'));
  }
}
// Custom array sort function by weight.
function _dashboard_configure_arraysort($a, $b) {
  if (isset($a['weight']) && isset($b['weight'])) {
    return $a['weight'] < $b['weight'] ? -1 : 1;
  }
  return 0;
}

function theme_custom_hcfm_dashboard_configure_section($variables) {
  $form = $variables['form'];  
  $rows = array();
  foreach (element_children($form['tiles']) as $id) {
    $form['tiles'][$id]['weight']['#attributes']['class'] = array('tiles-order-weight');
    $rows[] = array(
      'data' => array(
        array('class' => array('tile-cross')),
        drupal_render($form['tiles'][$id]['title']),
        drupal_render($form['tiles'][$id]['weight']),
      ),
      'class' => array('draggable'),
    );
  }  
  $header = array('', t('Title'),'weight');
  $output = drupal_render($form['note']);
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'tiles-order')));
  $output .= drupal_render_children($form);  
  drupal_add_tabledrag('tiles-order', 'order', 'sibling', 'tiles-order-weight');  
  return $output;
}
///////////////////////////////////////////////////////* dashboard configure end ************************/////////////////////////////////////// 
function hcfm_dashboard_tile_callback($var){
  global $user,$company;  
  $output = '';  
  if(isset($var) && !empty($var)){
    if($var == 'a'){
      $output ='<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('a','normal').'</div>
                <div class="hcfm-dash-item-0 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn021"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('a','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('a','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn022"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('a','back','normal').'
                  </div>
                </div>
                <div class="hcfm-dash-item-0 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    '.hcfm_dash_tile_data_callback('a','front','compare').'
                  </div>
                  
                  <div id="Tile-a" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('a','back','compare').'
                    </div>
                  </div>
                </div>';
    }   
    if($var == 'b'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('b','normal').'</div>
                <div class="hcfm-dash-item-1 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn121"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('b','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('b','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn122"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('b','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-1 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('b','front','compare').'
                  '</div>
                  
                  <div id="Tile-b" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('b','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'c'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('c','normal').'</div>
                <div class="hcfm-dash-item-2 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn221"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('c','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('c','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn222"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('c','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-2 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('c','front','compare').' 
                  '</div>
                  
                  <div id="Tile-c" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('c','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'd'){      
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('d','normal').'</div>
                <div class="hcfm-dash-item-3 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn321"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('d','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('d','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn322"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('d','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-3 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">                    
                    './/hcfm_dash_tile_data_callback('d','front','compare').' 
                  '</div>
                 
                  <div id="Tile-d" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('d','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'e'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('e','normal').'</div>
                <div class="hcfm-dash-item-4 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn421"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('e','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('e','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn422"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('e','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-4 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">                    
                    './/hcfm_dash_tile_data_callback('e','front','compare').'
                  '</div>
                  
                  <div id="Tile-e" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('e','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'f'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('f','normal').'</div>
                <div class="hcfm-dash-item-5 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn521"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('f','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('f','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn522"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('f','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-5 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('f','front','compare').'
                  '</div>
               
                  <div id="Tile-f" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('f','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'g'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('g','normal').'</div>
                <div class="hcfm-dash-item-6 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn621"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('g','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('g','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn622"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('g','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-6 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('g','front','compare').'
                  '</div>
                  
                  <div id="Tile-g" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('g','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'h'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('h','normal').'</div>
                <div class="hcfm-dash-item-7 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn721"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('h','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('h','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn722"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('h','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-7 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('h','front','compare').'
                  '</div>
                 
                  <div id="Tile-h" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('h','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'i'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('i','normal').'</div>
                <div class="hcfm-dash-item-8 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn821"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('i','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('i','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn822"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('i','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-8 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('i','front','compare').'
                  '</div>
                  
                  <div id="Tile-i" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('i','back','compare').'
                    </div>
                  </div>
                </div>';
    }
    if($var == 'j'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('j','normal').'</div>
                <div class="hcfm-dash-item-9 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn921"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('j','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('j','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                      <div class="tile-flipcontrol" style="display: none;">
                        <a href="javascript:void(0);" class="unflip-btn922"><i class="fa fa-cog" aria-hidden="true"></i></a>
                      </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('j','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-9 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('j','front','compare').'
                  '</div>
                 
                  <div id="Tile-j" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('j','back','compare').'
                    </div>
                  </div>
                </div>';
    } 
    if($var == 'k'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('k','normal').'</div>
                <div class="hcfm-dash-item-10 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn1021"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('k','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('k','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="unflip-btn1022"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('k','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-10 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('k','front','compare').'
                  '</div>
                
                  <div id="Tile-k" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('k','back','compare').'
                    </div>
                  </div>
                </div>';
    } 
    if($var == 'l'){
      $output = '<div class="text-center desh-sec-a">'.hcfm_dash_tile_data_callback('l','normal').'</div>
                <div class="hcfm-dash-item-11 dash-item desh-sec-b tile-height-dubble-inner">
                  <div class="front">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="flip-btn1121"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    <div class="graph-normal">
                      './/hcfm_dash_tile_data_callback('l','front','normal').'
                    '</div>
                    <div class="graph-large">
                      './/hcfm_dash_tile_data_callback('l','front','large').'
                    '</div>
                  </div>
                  <div class="back">
                    <div class="clearfix">
                    <div class="tile-flipcontrol" style="display: none;">
                      <a href="javascript:void(0);" class="unflip-btn1122"><i class="fa fa-cog" aria-hidden="true"></i></a>
                    </div>
                    </div>
                    '.hcfm_dash_tile_data_callback('l','back','normal').'
                  </div>
                </div>

                <div class="hcfm-dash-item-11 dash-item desh-sec-c tile-height-dubble-inner">
                  <div class="front-compare clearfix">
                    './/hcfm_dash_tile_data_callback('l','front','compare').'
                  '</div>
                
                  <div id="Tile-l" class="compare-back" style="display:none;" compareback-status="close">
                    <div class="panel-body" >
                      '.hcfm_dash_tile_data_callback('l','back','compare').'
                    </div>
                  </div>
                </div>';
    }  
  }
  return $output;
}
//******************************************************dashbard 4 end *****************************************************/
function _hcfm_chart_intigration_column_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL) { 
 //drup_msg($getData);
 //drup_msg($getLab);
  $chart = array(
    //'#title' => t('Risk Rank'),
  '#chart_id' => $chart_id,
    '#type' => 'chart',
    '#chart_type' => 'column',  
  '#legend' => FALSE,
    '#data_labels' => TRUE,
  '#tooltips' => TRUE,
  );
  
  $chart['dashboard_column_chart'] = array(
    '#type' => 'chart_data',
    '#data' => $getData,  
  );  
  if(isset($getLab) && !empty($getLab)){
  $chart['dashboard_column_chart_xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' =>$getLab,
  );
  } 
  $example['chart'] = $chart;  
  $example['chart']['#width'] = 350;
  $example['chart']['#height'] = 414;
  $output = drupal_render($example);
  return $output;  
}

function _hcfm_chart_intigration_column_stacking_data_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) { 
  if($chart_id == 'asset'){
    $chart = array(
      '#type' => 'chart',
      '#chart_id' => $chart_id,
      '#chart_type' => 'column',
      '#title' => t('Column simple'),
     // '#legend_position' => 'bottom',
    ); 
  }else{
    $chart = array(
      '#type' => 'chart',
      '#chart_id' => $chart_id,
      '#chart_type' => 'column',
      '#title' => t('Column simple'),
      '#legend_position' => 'bottom',
    );
  }
  foreach($char as $key=>$value){
    $chart[$value['name']] =array('#type'=>'chart_data','#title'=>$value['name'],'#data'=>$value['data']); 
  }
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $getLab,
  );
  
  $example['chart'] = $chart;
  //drup_msg($example);
  return $example;
}

function _hcfm_chart_intigration_column_stacking_inc($getData,$getLab,$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) {
  $example = _hcfm_chart_intigration_column_stacking_data_inc($getData,$getLab,$char,$chart_id,$Ttitle,$status);
  $example['chart']['#title'] = $Ttitle;
  $example['chart']['#chart_id'] = $chart_id;
  
  //$example['chart']['#chart_id'] = $getLab;

  if($chart_id == 'available_labor'){
   $example['chart']['#stacking'] = FALSE;
   $example['chart']['#legend'] = FALSE;
  }
  else if($chart_id == 'labor_use_rate' ||$chart_id == 'asset' ){   
    $example['chart']['#stacking'] = FALSE;
  }else{
    $example['chart']['#stacking'] = TRUE;
  }  
  if (isset($status) && !empty($status) && $status == 'compare') {
    $example['chart']['#width'] = 340;
    $example['chart']['#height'] = 414;
  }else if (isset($status) && !empty($status) && $status == 'large') {
    $example['chart']['#width'] = 560;
    $example['chart']['#height'] = 621;
  }else{
    $example['chart']['#width'] = 350;
    $example['chart']['#height'] = 394;
  }
  
//drup_msg($example);
  return $example;
}

function _hcfm_chart_intigration_bar_stacking_data_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) { 
  $chart = array(
    '#type' => 'chart',
  '#chart_id' => $chart_id,
    '#chart_type' => 'bar',
    '#title' => t('Column simple'),
  '#legend_position' => 'bottom',
  );  
  foreach($char as $key=>$value){
    $chart[$value['name']] =array('#type'=>'chart_data','#title'=>$value['name'],'#data'=>$value['data']); 
  }
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $getLab,
  );
  $example['chart'] = $chart;
  return $example;
}

function _hcfm_chart_intigration_bar_stacking_inc($getData,$getLab,$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) {
  $example = _hcfm_chart_intigration_bar_stacking_data_inc($getData,$getLab,$char,$chart_id,$Ttitle,$status);
  $example['chart']['#title'] = $Ttitle;
  $example['chart']['#chart_id'] = $chart_id;
  $example['chart']['#stacking'] = TRUE;
 // $example['chart']['xaxis'] = $getLab;
  if (isset($status) && !empty($status) && $status == 'compare') {
    $example['chart']['#width'] = 340;
    $example['chart']['#height'] = 414;
  }else if (isset($status) && !empty($status) && $status == 'large') {
    $example['chart']['#width'] = 560;
    $example['chart']['#height'] = 621;
  }else{
    $example['chart']['#width'] = 350;
    $example['chart']['#height'] = 394;
  }
  return $example;
}

function _hcfm_chart_intigration_pie_column_stacking_data_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) { 
 //drup_msg($getData);
 //drup_msg($getLab);
  $chart = array(
    '#title' => $Ttitle,
  '#chart_id' => $chart_id,
    '#type' => 'chart',
   // '#chart_type' => 'column',  
  '#legend' => FALSE,
    //'#data_labels' => TRUE,
  '#tooltips' => TRUE,
  );
  
  $chart['dashboard_column_chart'] = array(
    '#type' => 'chart_data',
    '#chart_type' => 'column',
    '#data' => $getData,  
    '#legend' => TRUE,
    '#legend_position' => 'bottom',
    '#labels' => $getLab, 
  );  
  
/*foreach($char as $key=>$value){
    $chart[$value['name'].'_'.$key] =array('#type'=>'chart_data','#chart_type' => 'column','#title'=>$value['name'],'#data'=>array($value['data']),'#legend' => TRUE); 
  }*/
 
  $chart['dashboard_pie_chart'] = array(
    '#type' => 'chart_data',
    //'#title' => t('Risk Rank'),
    '#chart_type' => 'pie',
    '#data' => $getData,
     '#legend' => FALSE,
    '#labels' => $getLab,    
  );

  if(isset($getLab) && !empty($getLab)){
  /*$chart['dashboard_column_chart_xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' =>$getLab,
  );*/
  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $getLab,
  );
  } 
  $example['chart'] = $chart;  
  if (isset($status) && !empty($status) && $status == 'compare') {
    $example['chart']['#width'] = 340;
    $example['chart']['#height'] = 414;
  }else if (isset($status) && !empty($status) && $status == 'large') {
    $example['chart']['#width'] = 560;
    $example['chart']['#height'] = 621;
  }else{
    $example['chart']['#width'] = 350;
    $example['chart']['#height'] = 394;
  }
  //drup_msg($example);
  $output = drupal_render($example);
  return $output;  
}

function _hcfm_chart_intigration_pie_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) {   
  $Chart3D = array('work_orders_open_pm','work_orders_open_cm','work_orders_open_projects','work_orders_on_hold');
  $chart = array(
    '#title' => $Ttitle,
  '#chart_id' => $chart_id, //required
    '#type' => 'chart',
    '#chart_type' => 'pie',
  //'#attributes' => array('options3d' => array('enabled' => true,'alpha' => 45)),
  '#chart_library' => 'highcharts',
    '#legend_position' => 'bottom',
    '#data_labels' => TRUE,
  '#tooltips' => TRUE,
  );
  
  if(in_array($chart_id,$Chart3D)){
    $chart['dashboard_pie_chart'] = array(
      '#type' => 'chart_data', 
    '#data' => $char,    
    );
  }
  else{
    $chart['dashboard_pie_chart'] = array(
      '#type' => 'chart_data',
      //'#title' => t('Risk Rank'),
    '#data' => $getData,
    '#labels' => $getLab,
    );
  }
  $example['chart'] = $chart;
  if (isset($status) && !empty($status) && $status == 'compare') {
    $example['chart']['#width'] = 340;
    $example['chart']['#height'] = 414;
  }else if (isset($status) && !empty($status) && $status == 'large') {
    $example['chart']['#width'] = 560;
    $example['chart']['#height'] = 621;
  }else{
    $example['chart']['#width'] = 350;
    $example['chart']['#height'] = 394;
  }
  $output = drupal_render($example);
  return $output;
}

function _hcfm_chart_intigration_pyramid_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) {   
  $chart = array(
    '#title' => $Ttitle,
    '#chart_id' => $chart_id, //required
    '#type' => 'chart',
    '#chart_type' => 'pyramid',
    //'#attributes' => array('options3d' => array('enabled' => true,'alpha' => 45)),
    '#chart_library' => 'highcharts',
    '#legend_position' => 'bottom',
    '#data_labels' => TRUE,
    '#legend' => FALSE,
    '#tooltips' => TRUE,
  );
  $chart['dashboard_pie_chart'] = array(
    '#type' => 'chart_data',
    //'#title' => t('Risk Rank'),
    '#data' => $getData,
    '#labels' => $getLab,  
  );
  
  
  $example['chart'] = $chart;
  if (isset($status) && !empty($status) && $status == 'compare') {
    $example['chart']['#width'] = 300;
    $example['chart']['#height'] = 414;
  }else if (isset($status) && !empty($status) && $status == 'large') {
    $example['chart']['#width'] = 520;
    $example['chart']['#height'] = 621;
  }else{
    $example['chart']['#width'] = 350;
    $example['chart']['#height'] = 394;
  }
  
  $output = drupal_render($example);
  return $output;
}

function _hcfm_chart_intigration_gauge_inc($getData,$getLab = '',$obj=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) {   
  $chart = array(
  '#chart_id' => $chart_id,
  '#title' => $Ttitle,
  '#type' => 'chart',
  '#chart_type' => 'gauge',  
  '#legend' => FALSE,
  '#data_labels' => TRUE,
  '#tooltips' => TRUE,
  );
  /*
  $chart['dashboard_gauge_chart'] = array(
    '#type' => 'chart_data',
    '#data' => $getData,
    '#title' => $getLab,
  );
  $chart['dashboard_gauge_chart_xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' =>$getLab,
  );*/
  if(isset($obj) && !empty($obj)){
    foreach($obj as $key=>$value){
      $chart[$value['name']] =array('#type'=>'chart_data','#title'=>$value['name'],'#data'=>$value['data']); 
    }
  }else{
    $chart['dashboard_gauge_chart'] = array(
      '#type' => 'chart_data',
      '#data' => $getData,
      '#title' => $getLab,
    );
  }
  $example['chart'] = $chart;
  if (isset($status) && !empty($status) && $status == 'compare') {
    $example['chart']['#width'] = 340;
    $example['chart']['#height'] = 414;
  }else if (isset($status) && !empty($status) && $status == 'large') {
    $example['chart']['#width'] = 560;
    $example['chart']['#height'] = 621;
  }else{
    $example['chart']['#width'] = 350;
    $example['chart']['#height'] = 394;
  }
  
  //$output = drupal_render($example);
  //drup_msg($example);
  return $example;
}
function _hcfm_chart_synchronized_inc($getData,$getLab = '',$char=NULL,$chart_id=NULL,$Ttitle = NULL,$status=NULL) { 
  $gudata = array();
  if(isset($char) && !empty($char)){
    $count = count($char);

    foreach($char as $key=>$value){
     
      if (isset($status) && !empty($status) && $status == 'compare') {
        $gwidth =340;
        $gheight =385;
      }else if (isset($status) && !empty($status) && $status == 'large') {        
        $gwidth =560;
        $gheight =620;
      }else{
        $gwidth =350;
        $gheight =394;
      }
      $gudata[] = array(
        '#title' => $value['name'],
        '#chart_id' => $chart_id,
        '#type' => 'chart',
        '#chart_type' => 'column',
        '#legend' => FALSE,
        '#width' => $gwidth,
        '#height' => $gheight/$count,'synchronized_'.$key =>array(
          '#type' => 'chart_data',
          //'#chart_type' => $value['type'],
          '#data' => $value['data'],
          //'#title' => $value['name'],
        ),
        'xaxis' => array(
          '#type' => 'chart_xaxis',
          '#labels' => $getLab,
        )
      );
    }
  }
  


  $example = $gudata;
  //drup_msg($example);
  return $example;  
}

function hcfm_dash_tile_data_callback($TileId,$obj,$objextra){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $output = '';
  
  if(isset($TileId,$obj) && !empty($obj) && !empty($obj)){
  //dashboard Assets  
    if($TileId == 'a'){
      $Ttitle = 'Asset by Risk';
      $Ttype = 'asset';
      $DGrapLabel = '';
      $DGrapData = '';
      $DGrapExtra = '';
      $cDGrapLabel = '';
      $cDGrapData = '';
      $cDGrapExtra = '';
      if($obj == 'normal'){
        $Count = '';  
        $query= db_select('node','n');
        $query->leftjoin('field_data_field_asset_status','fdfsts','fdfsts.entity_id=n.nid');
        $query->fields('fdfsts',array('field_asset_status_target_id')); 
        $query->condition('fdfsts.field_asset_status_target_id',52651,'=');//active status
        $query->fields('n',array('nid'));
        $query->condition('n.type','fm_asset','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $Count = $query->execute()->rowCount();  
        $output .= '<div class="small-'.$TileId.'">';

        $output .=    '<div class="small-outer clearfix">';
        $output .=      '<div class="small-first-title first-sec clearfix">ASSETS</div>';
        $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                          <div class="">
                            <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-asseset.jpg">
                          </div>
                          <div class="two pull-right">
                            <div class="two-one">
                              
                            </div>
                            <div class="two-two">
                              
                            </div>
                          </div>
                        </div>';
        $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">ACTIVE ASSETS</div></div>';
        $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
        $output .=    '</div></div>';



        //$output .= '<br><br><h3>ASSETS</h3><strong>Total Asset : '.$Count.' </strong>';
        $output .= '</div>';    
      }
      
      if($obj == 'front'){
        $ReturnObj = '';
        $cReturnObj = '';
        $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
        $query->fields('hcfmdt');
        $query->condition('hcfmdt.user',$user->uid,'=');
        $query->condition('hcfmdt.company',$company->nid,'=');
        $query->condition('hcfmdt.type',$Ttype,'=');
        $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($TableResult) && !empty($TableResult)){
          $RegionId= unserialize($TableResult[$Ttype]['region']);
          $SiteId= unserialize($TableResult[$Ttype]['site']);
          $FacilityId= unserialize($TableResult[$Ttype]['facility']);
          $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
          $StatusId= unserialize($TableResult[$Ttype]['status']);  
          $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
          $FilterId= unserialize($TableResult[$Ttype]['filter']);

          
          $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
          $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
        }
        //////////////compare/////////////////////
        $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
        $cquery->fields('hcfmdt');
        $cquery->condition('hcfmdt.user',$user->uid,'=');
        $cquery->condition('hcfmdt.company',$company->nid,'=');
        $cquery->condition('hcfmdt.type',$Ttype,'=');
        //$cquery->condition('hcfmdt.tile_status','compare','=');
        $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);

          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }


          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }
        if(isset($objextra) && !empty($objextra)){
          if($objextra == 'normal'){
            $output .= '<div class="asset-column-data-display">
            <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
            //$GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($DGrapData,$DGrapLabel,$DGrapExtra,$Ttype,$Ttitle);
            $GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
            $output .= drupal_render($GraphDisplayRender);
            $output .= '</div>';
          }
          if($objextra == 'large'){
            $output .= '<div class="asset-column-data-display">
            <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
            $GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
            $output .= drupal_render($GraphDisplayRender);
            $output .= '</div>';
          }
          if($objextra == 'compare'){
            $output .= '<div class="asset-column-compare-data-display compare-front">';
            $GraphDisplayRender1 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
            $GraphDisplayRender2 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
            $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
            $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);
            $output .= '<div class="pull-left">'.$GraphDisplayRenderCompare1.'</div>';
            $output .= '<div class="pull-right">'.$GraphDisplayRenderCompare2.'</div>';
            $output .= '</div>';
          }
        }
      }
      if($obj == 'back'){
        if(isset($objextra) && !empty($objextra)){
          if($objextra == 'normal'){
            $output .= '<div class="asset-column-data-setting normal-back">';
            $GraphFormRender = drupal_get_form('hcfm_dashboard_asset_risk_form');
            $output .= drupal_render($GraphFormRender);
            $output .= '</div>'; 
          }
          if($objextra == 'compare'){
            $output .= '<div class="asset-column-compare-data-setting normal-back">';
            $GraphFormRender = drupal_get_form('hcfm_dashboard_asset_risk_form','compare');            
            $CompareGraphFormRender = drupal_render($GraphFormRender);
            $output .= $CompareGraphFormRender;
            $output .= '</div>'; 
          }
        }
      }
    }
  //dashboard OPEN PMs 
  if($TileId == 'b'){
    $Ttitle = 'OPEN PMs'; 
    if($obj == 'normal'){
      $Count = '';  
      $query= db_select('node','n');
      $query->leftjoin('field_data_field_wo_status','fdfwr','fdfwr.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
      $query->fields('n',array('nid'));
      $query->fields('fdfwr',array('field_wo_status_target_id'));
      $query->fields('fdftye',array('field_wo_type_target_id'));
      $query->condition('n.type','fm_work_order','=');
      $query->condition('fdfwr.field_wo_status_target_id',52951,'=');//Status:  Issued
      $query->condition('fdftye.field_wo_type_target_id',52921,'=');//type pm
      $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
      $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
      //$query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');//current month
      if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
      }
      $Count = $query->execute()->rowCount();  
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      "<div class='small-first-title first-sec clearfix'>OPEN PM'S</div>";
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-openpm.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">PLANNED WORK</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';

      //$output .= '<br><br><h3>'.$Ttitle.'</h3><strong>Total Open PMs : '.$Count.' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){    
      $ReturnObj = '';
      $Ttype = 'work_orders_open_pm';
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($TableResult) && !empty($TableResult)){
        $RegionId= unserialize($TableResult[$Ttype]['region']);
        $SiteId= unserialize($TableResult[$Ttype]['site']);
        $FacilityId= unserialize($TableResult[$Ttype]['facility']);
        $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
        $StatusId= unserialize($TableResult[$Ttype]['status']);  
        $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
        $FilterId= unserialize($TableResult[$Ttype]['filter']);

        $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
        $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
        
      }
     /////////////////////compare////////////////////
      $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
      $cquery->fields('hcfmdt');
      $cquery->condition('hcfmdt.user',$user->uid,'=');
      $cquery->condition('hcfmdt.company',$company->nid,'=');
      $cquery->condition('hcfmdt.type',$Ttype,'=');
      //$cquery->condition('hcfmdt.tile_status','compare','=');
      $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($cTableResult) && !empty($cTableResult)){
        $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
        $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
        $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
        $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
        $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
        $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
        $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
        $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
        $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
        $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
        $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
        $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
        $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
        $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
        
        $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
        $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
        $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
        $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

        if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
          $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
        }
        if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
          $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
        }

        if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
          $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
        }
        if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
          $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
        }

        if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
          $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
        }
        if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
          $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
        }

        $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
        $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
        $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
        $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
      }
   
    

      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_open_pm-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="work_orders_open_pm-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_open_pm-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
          $output .= '<div class="pull-left">'.$GraphDisplayRender1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRender2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_open_pm-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_open_pm_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_open_pm-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_open_pm_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard OPEN CMs
  if($TileId == 'c'){
    $Ttitle = 'OPEN CMs'; 
    if($obj == 'normal'){
      $Count = '';  
      $query= db_select('node','n');
      $query->leftjoin('field_data_field_wo_status','fdfwr','fdfwr.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
      $query->fields('n',array('nid'));
      $query->fields('fdfwr',array('field_wo_status_target_id'));
      $query->fields('fdftye',array('field_wo_type_target_id'));
      $query->condition('n.type','fm_work_order','=');
      $query->condition('fdfwr.field_wo_status_target_id',52951,'=');//Status:  Issued
      $query->condition('fdftye.field_wo_type_target_id',52926,'=');//type CM
      $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
      $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
     // $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');//current month
      if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
      }
      $Count = $query->execute()->rowCount();  
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      "<div class='small-first-title first-sec clearfix'>OPEN CM'S</div>";
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-opencm.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">PLANNED WORK</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>'.$Ttitle.'</h3><strong>Total Open CMs : '.$Count.' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){    
      $ReturnObj = '';
      $Ttype = 'work_orders_open_cm';
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($TableResult) && !empty($TableResult)){
        $RegionId= unserialize($TableResult[$Ttype]['region']);
        $SiteId= unserialize($TableResult[$Ttype]['site']);
        $FacilityId= unserialize($TableResult[$Ttype]['facility']);
        $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
        $StatusId= unserialize($TableResult[$Ttype]['status']);  
        $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
        $FilterId= unserialize($TableResult[$Ttype]['filter']);

        $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
        $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
      }
        /***********************compare************************/
      $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
      $cquery->fields('hcfmdt');
      $cquery->condition('hcfmdt.user',$user->uid,'=');
      $cquery->condition('hcfmdt.company',$company->nid,'=');
      $cquery->condition('hcfmdt.type',$Ttype,'=');
      //$cquery->condition('hcfmdt.tile_status','compare','=');
      $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }


    if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_open_cm-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="work_orders_open_cm-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_open_cm-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');      
          $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');      
          $output .= '<div class="pull-left">'.$GraphDisplayRender1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRender2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_open_cm-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_open_cm_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_open_cm-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_open_cm_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Open Projects
  if($TileId == 'd'){
    $Ttitle = 'Open Projects';
    if($obj == 'normal'){
    $Count = '';  
    $query= db_select('node','n');
    $query->leftjoin('field_data_field_wo_status','fdfwr','fdfwr.entity_id=n.nid');
    $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
    $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
    $query->fields('n',array('nid'));
    $query->fields('fdfwr',array('field_wo_status_target_id'));
    $query->fields('fdftye',array('field_wo_type_target_id'));
    $query->condition('n.type','fm_work_order','=');
    $query->condition('fdfwr.field_wo_status_target_id',52951,'=');//Status:  Issued
    $query->condition('fdftye.field_wo_type_target_id',52931,'=');//type project
    $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
    $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
    //$query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');//current month
    if(user_or_administrator_data()){
      $query->condition('n.uid',$user->uid,'=');
    }
    $Count = $query->execute()->rowCount();  
    $output .= '<div class="small-'.$TileId.'">';
    $output .=    '<div class="small-outer clearfix">';
    $output .=      '<div class="small-first-title first-sec clearfix">PROJECTS</div>';
    $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                      <div class="">
                        <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-projects.jpg">
                      </div>
                      <div class="two pull-right">
                        <div class="two-one">
                          
                        </div>
                        <div class="two-two">
                          
                        </div>
                      </div>
                    </div>';
    $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">OPEN PROJECT WORK ORDER</div></div>';
    $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
    $output .=    '</div></div>';
    //$output .= '<br><br><h3>PROJECTS</h3><strong>Total '.$Ttitle.' : '.$Count.' </strong>';
    $output .= '</div>';    
    }
    if($obj == 'front'){    
    $ReturnObj = '';
    $Ttype = 'work_orders_open_projects';
    $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
    $query->fields('hcfmdt');
    $query->condition('hcfmdt.user',$user->uid,'=');
    $query->condition('hcfmdt.company',$company->nid,'=');
    $query->condition('hcfmdt.type',$Ttype,'=');
    $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
    if(isset($TableResult) && !empty($TableResult)){
      $RegionId= unserialize($TableResult[$Ttype]['region']);
      $SiteId= unserialize($TableResult[$Ttype]['site']);
      $FacilityId= unserialize($TableResult[$Ttype]['facility']);
      $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
      $StatusId= unserialize($TableResult[$Ttype]['status']);  
      $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
      $FilterId= unserialize($TableResult[$Ttype]['filter']);
  
      $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
      $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    }   
    //////////////compare/////////////////////
    $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
    $cquery->fields('hcfmdt');
    $cquery->condition('hcfmdt.user',$user->uid,'=');
    $cquery->condition('hcfmdt.company',$company->nid,'=');
    $cquery->condition('hcfmdt.type',$Ttype,'=');
    //$cquery->condition('hcfmdt.tile_status','compare','=');
    $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
    if(isset($cTableResult) && !empty($cTableResult)){
      $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
      $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
      $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
      $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
      $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
      $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
      $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
      $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
      $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
      $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
      $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
      $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
      $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
      $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
      
      $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
      $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
      $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
      $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
      if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
        $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
      }
      if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
        $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
      }

      if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
        $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
      }
      if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
        $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
      }

      if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
        $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
      }
      if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
        $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
      }

      $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
      $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
      $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
      $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
    }
   
    if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_open_projects-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="work_orders_open_projects-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_open_projects-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');      
          $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');      
          $output .= '<div class="pull-left">'.$GraphDisplayRender1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRender2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_open_projects-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_open_projects_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_open_projects-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_open_projects_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Work Orders On Hold
  if($TileId == 'e'){
    $Ttitle = 'PARTS ON ORDER'; 
    if($obj == 'normal'){
      $Count = '';
      $query= db_select('node','n');
      $query->leftjoin('field_data_field_wo_status','fdfwr','fdfwr.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
      $query->fields('n',array('nid'));
      $query->fields('fdfwr',array('field_wo_status_target_id'));
      $query->fields('fdftye',array('field_wo_type_target_id'));
      $query->condition('n.type','fm_work_order','=');
      $query->condition('fdfwr.field_wo_status_target_id',52956,'=');//Status:  Awaiting Parts
      $query->condition('fdftye.field_wo_type_target_id',52931,'=');//type project
      $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
      $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
      //$query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');//current month
      if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
      }
      $Count = $query->execute()->rowCount();     
      $output .=  '<div class="small-'.$TileId.'">';
      /*<i class="fa fa-2x fa-circle" aria-hidden="true" style="color: red;"></i>
        <i class="fa fa-2x fa-long-arrow-right" aria-hidden="true" style="color: #219be3;"></i>
      */
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">NEED PARTS</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-needparts.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">OPEN WORK ORDER AWAITING PARTS</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>'.$Ttitle.'</h3><strong>Work Orders On Hold : '.$Count.' </strong>';
      $output .=  '</div>';    
    }
    if($obj == 'front'){    
      $ReturnObj = '';
      $Ttype = 'work_orders_on_hold';
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($TableResult) && !empty($TableResult)){
        $RegionId= unserialize($TableResult[$Ttype]['region']);
        $SiteId= unserialize($TableResult[$Ttype]['site']);
        $FacilityId= unserialize($TableResult[$Ttype]['facility']);
        $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
        $StatusId= unserialize($TableResult[$Ttype]['status']);  
        $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
        $FilterId= unserialize($TableResult[$Ttype]['filter']);
       
        $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
        $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
      }  
      //////////////compare/////////////////////
      $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
      $cquery->fields('hcfmdt');
      $cquery->condition('hcfmdt.user',$user->uid,'=');
      $cquery->condition('hcfmdt.company',$company->nid,'=');
      $cquery->condition('hcfmdt.type',$Ttype,'=');
      //$cquery->condition('hcfmdt.tile_status','compare','=');
      $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($cTableResult) && !empty($cTableResult)){
        $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
        $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
        $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
        $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
        $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
        $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
        $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
        $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
        $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
        $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
        $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
        $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
        $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
        $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
        $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
        $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
        
        if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
          $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
        }
        if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
          $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
        }

        if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
          $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
        }
        if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
          $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
        }

        if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
          $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
        }
        if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
          $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
        }

        $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
        $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);

        $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
        $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

        $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
        $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
      }

      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_on_hold-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="work_orders_on_hold-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_pie_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_on_hold-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
          $output .= '<div class="pull-left">'.$GraphDisplayRender1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRender2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_orders_on_hold-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_work_orders_on_hold_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_orders_on_hold-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_work_orders_on_hold_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Past Due Work Orders
  if($TileId == 'f'){
    $Ttitle = 'BACK LOG'; 
    if($obj == 'normal'){
      $Count = '';
      $query= db_select('node','n');
      $query->leftjoin('field_data_field_wo_status','fdfwr','fdfwr.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
      $query->fields('n',array('nid','title'));
      $query->fields('fdfwr',array('field_wo_status_target_id'));
      $query->fields('fdftye',array('field_wo_type_target_id'));
      $query->fields('fdfdaed',array('field_wo_date_completed_value'));
      $query->condition('n.type','fm_work_order','=');
      //$query->condition('fdfwr.field_wo_status_target_id',52956,'=');//Status:  Awaiting Parts
      //$query->condition('fdftye.field_wo_type_target_id',52931,'=');//type project
      $query->condition('fdfwr.field_wo_status_target_id',52951,'=');//Status:  Issued
          $currentDay = date('Y-m-d 00:00:00', time());
          //$query->condition('fdfdaed.field_wo_date_completed_value',$currentDay, '<');//current month
      if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
      }
      $Count = $query->execute()->rowCount();       
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">BACKLOG</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-backlog.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">PAST DUE WORK ORDERS</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>'.$Ttitle.'</h3><strong>Past Due Work Orders : '.$Count.' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){    
      $ReturnObj = '';
      $Ttype = 'past_due_work_orders';
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 

      if(isset($TableResult) && !empty($TableResult)){
        $RegionId= unserialize($TableResult[$Ttype]['region']);
        $SiteId= unserialize($TableResult[$Ttype]['site']);
        $FacilityId= unserialize($TableResult[$Ttype]['facility']);
        $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
        $StatusId= unserialize($TableResult[$Ttype]['status']);  
        $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
        $FilterId= unserialize($TableResult[$Ttype]['filter']);

     
        $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
        $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
      }
//////////////compare/////////////////////
      $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
      $cquery->fields('hcfmdt');
      $cquery->condition('hcfmdt.user',$user->uid,'=');
      $cquery->condition('hcfmdt.company',$company->nid,'=');
      $cquery->condition('hcfmdt.type',$Ttype,'=');
      //$cquery->condition('hcfmdt.tile_status','compare','=');
      $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }
      
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="past_due_work_orders-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="past_due_work_orders-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="past_due_work_orders-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
          $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
          $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);
          $output .= '<div class="pull-left">'.$GraphDisplayRenderCompare1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRenderCompare2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="past_due_work_orders-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_past_due_work_orders_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="past_due_work_orders-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_past_due_work_orders_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Work Order Ratio
  if($TileId == 'g'){
    $Ttitle = 'WORK ORDER FOCUS';
    if($obj == 'normal'){
      $Count = ''; 
      $db_or = db_or();
      $query= db_select('node','n');
      $query->leftjoin('field_data_field_wo_status','fdfwr','fdfwr.entity_id=n.nid');
      $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
      $query->fields('n',array('nid'));
      //$query->fields('fdfwr',array('field_wo_status_target_id'));
      $query->fields('fdftye',array('field_wo_type_target_id'));
      $db_or ->condition('fdftye.field_wo_type_target_id',52926,'=');
      $db_or ->condition('fdftye.field_wo_type_target_id',52921,'=');
      $query->condition('fdfwr.field_wo_status_target_id',59706,'=');//Status:  completed
      $query->condition($db_or);
      if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
      }
      $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC); 
      if(isset($ReturnObj) && !empty($ReturnObj)){
        $getGraphData = array_count_values(array_column($ReturnObj, 'field_wo_type_target_id'));
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $cgetLab = array();
        foreach($getGraphData as $riskKey => $risk) { 
          $cgetPer[$riskKey] = round((($risk/$getFinal )*100) , 2);
          if(is_numeric($riskKey)){     
            $cgetLab[$riskKey] =  _get_title_of_node($riskKey);     
          }
        }
        if(!empty($cgetPer[52921]) && !empty($cgetPer[52926])){
         // $Count = '<br>PM '.$cgetPer[52921].'%'.'<br>CM '.$cgetPer[52926].'%';
          $Count = 'PM '.$cgetPer[52921].'%'.'&nbsp; CM '.$cgetPer[52926].'%';
        }
        if(!empty($cgetPer[52921]) && empty($cgetPer[52926])){
          $Count = 'PM '.$cgetPer[52921].'%';       
        }
        if(empty($cgetPer[52921]) && !empty($cgetPer[52926])){
          $Count = 'CM '.$cgetPer[52926].'%';         
        }      
      }
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">WORK FOCUS</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-workfocus.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">PLANNED WORK</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><h3>'.$Ttitle.'</h3><strong>Work Order Ratio  '.$Count.' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){    
    $ReturnObj = '';
    $Ttype = 'work_order_ratio';
    $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
    $query->fields('hcfmdt');
    $query->condition('hcfmdt.user',$user->uid,'=');
    $query->condition('hcfmdt.company',$company->nid,'=');
    $query->condition('hcfmdt.type',$Ttype,'=');
    $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
    if(isset($TableResult) && !empty($TableResult)){
      $RegionId= unserialize($TableResult[$Ttype]['region']);
      $SiteId= unserialize($TableResult[$Ttype]['site']);
      $FacilityId= unserialize($TableResult[$Ttype]['facility']);
      $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
      $StatusId= unserialize($TableResult[$Ttype]['status']);  
      $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
      $WotypeId = unserialize($TableResult[$Ttype]['wo_type']);
      $FilterId= unserialize($TableResult[$Ttype]['filter']);     
      $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
      $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    }    
    //////////////compare/////////////////////
      $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
      $cquery->fields('hcfmdt');
      $cquery->condition('hcfmdt.user',$user->uid,'=');
      $cquery->condition('hcfmdt.company',$company->nid,'=');
      $cquery->condition('hcfmdt.type',$Ttype,'=');
      //$cquery->condition('hcfmdt.tile_status','compare','=');
      $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }
    if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){          
          $output .= '<div class="work_order_ratio-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_pyramid_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],0,$Ttype,'');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="work_order_ratio-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_pyramid_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],0,$Ttype,'','large');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_order_ratio-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_pyramid_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],0,$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_pyramid_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],0,$Ttype,$Ttitle.$subtitleB,'compare');
          $output .= '<div class="pull-left">'.$GraphDisplayRender1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRender2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="work_order_ratio-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_work_order_ratio_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="work_order_ratio-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_work_order_ratio_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Square Foot
  if($TileId == 'h'){
    $Ttitle = 'Square Foot';
    if($obj == 'normal'){
    $Count = '';
    $query = db_select('field_data_field_facility_floor_square_feet','fde0ecf5sf');
    $query->leftjoin('node','n','n.nid=fde0ecf5sf.entity_id');
    $query->fields('fde0ecf5sf',array('field_facility_floor_square_feet_value'));
    $query->condition('fde0ecf5sf.bundle','fm_facility','=');
    if(user_or_administrator_data()){
      $query->condition('n.uid',$user->uid,'=');
    }
    $result = $query->execute()->fetchAll();
    
    $TotalSf = 0;
    if(isset($result) && !empty($result)){
      foreach($result as $key=>$value){
        if(isset($value) && !empty($value->field_facility_floor_square_feet_value)){
          $real_integer = filter_var($value->field_facility_floor_square_feet_value, FILTER_SANITIZE_NUMBER_INT);
          $TotalSf += $real_integer; 
        }
      }
    }       
    $output .= '<div class="small-'.$TileId.'">';
    $output .=    '<div class="small-outer clearfix">';
    $output .=      '<div class="small-first-title first-sec clearfix">SQUARE FOOT</div>';
    $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                      <div class="">
                        <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-squarefoot.jpg">
                      </div>
                      <div class="two pull-right">
                        <div class="two-one">
                          
                        </div>
                        <div class="two-two">
                          
                        </div>
                      </div>
                    </div>';
    $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">TOTAL SQUARE FOOT</div></div>';
    $output .=      '<div class="small-count forth-sec clearfix">'.$TotalSf.'</div>';
    $output .=    '</div></div>';
    //$output .= '<br><br><h3>SQUARE FOOT</h3><strong>Total '.$Ttitle.' : '.$TotalSf.' </strong>';
    $output .= '</div>';    
    }
    if($obj == 'front'){ 
    $ReturnObj = '';
    $Ttype = 'square_foot';
    $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
    $query->fields('hcfmdt');
    $query->condition('hcfmdt.user',$user->uid,'=');
    $query->condition('hcfmdt.company',$company->nid,'=');
    $query->condition('hcfmdt.type',$Ttype,'=');
    $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
//pre( $TableResult );
   //pre($TableResult);
 if(isset($TableResult) && !empty($TableResult)){
      $RegionId= unserialize($TableResult[$Ttype]['region']);
      $SiteId= unserialize($TableResult[$Ttype]['site']);
      $FacilityId= unserialize($TableResult[$Ttype]['facility']);
      $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
      $StatusId= unserialize($TableResult[$Ttype]['status']);  
      $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
      $FilterId= unserialize($TableResult[$Ttype]['filter']);
     
      $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
          $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    }
      //////////////compare/////////////////////
        $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
        $cquery->fields('hcfmdt');
        $cquery->condition('hcfmdt.user',$user->uid,'=');
        $cquery->condition('hcfmdt.company',$company->nid,'=');
        $cquery->condition('hcfmdt.type',$Ttype,'=');
        //$cquery->condition('hcfmdt.tile_status','compare','=');
        $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }
//drup_msg($graphrenderdatanormal);
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          
         // drup_msg($graphrenderdatanormal['glabel']);
          $output .= '<div class="square_foot-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          //drup_msg($GraphDisplayRender);
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="square_foot-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= $GraphDisplayRender;
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="square_foot-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatanormal['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatanormal['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
          $output .= '<div class="pull-left">'.$GraphDisplayRender1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRender2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="square_foot-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_square_foot_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="square_foot-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_back_square_foot_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Labor Available
  if($TileId == 'i'){
    $Ttitle = 'Available Labor';  
    if($obj == 'normal'){
      $Count = '';
      $ftequery = db_select('field_data_field_facility_ftes','fde0ecf5sf');
      $ftequery->leftjoin('node','n','n.nid=fde0ecf5sf.entity_id');
      $ftequery->fields('fde0ecf5sf',array('field_facility_ftes_value'));
      $ftequery->condition('fde0ecf5sf.bundle','fm_facility','=');
      if(user_or_administrator_data()){
        $ftequery->condition('n.uid',$user->uid,'=');
      }
      $fteresult = $ftequery->execute()->fetchAll();
      
      $TotalFte = 0;
      if(isset($fteresult) && !empty($fteresult)){
        foreach($fteresult as $key=>$value){
          if(isset($value) && !empty($value->field_facility_ftes_value)){
            $real_integer = filter_var($value->field_facility_ftes_value, FILTER_SANITIZE_NUMBER_INT);
            $TotalFte += $real_integer; 
          }
        }
      }     
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">LABOR</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-labor.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">LABOR AVAILABLE FTE</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$TotalFte.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>LABOR</h3><strong>Total Labor Available : '.$TotalFte.' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){    
      $ReturnObj = '';
      $Ttype = 'available_labor';    
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($TableResult) && !empty($TableResult)){
        $RegionId= unserialize($TableResult[$Ttype]['region']);
        $SiteId= unserialize($TableResult[$Ttype]['site']);
        $FacilityId= unserialize($TableResult[$Ttype]['facility']);
        $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
        $StatusId= unserialize($TableResult[$Ttype]['status']);  
        $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
        $FilterId= unserialize($TableResult[$Ttype]['filter']);
        $ByWotype= unserialize($TableResult[$Ttype]['bytype']); 
        
      $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
          $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
        }
        //////////////compare/////////////////////
        $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
        $cquery->fields('hcfmdt');
        $cquery->condition('hcfmdt.user',$user->uid,'=');
        $cquery->condition('hcfmdt.company',$company->nid,'=');
        $cquery->condition('hcfmdt.type',$Ttype,'=');
        //$cquery->condition('hcfmdt.tile_status','compare','=');
        $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }



      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="available-labor-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_synchronized_inc('',$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="available-labor-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_synchronized_inc('',$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="available-labor-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_synchronized_inc('',$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_synchronized_inc('',$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');         
          $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
          $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);
          $output .= '<div class="pull-left"><div style="text-align: center;font-size:16px;font-weight: 600;" class="margin-top-10"><div class="clearfix" style="line-height: 12px;">'.$Ttitle.'</div><div style="font-size: 13px;text-transform: uppercase;" class="clearfix">'.$subtitleA.'</div></div>'.$GraphDisplayRenderCompare1.'</div>';
          $output .= '<div class="pull-right"><div style="text-align: center;font-size:16px;font-weight: 600;" class="margin-top-10"><div class="clearfix" style="line-height: 12px;">'.$Ttitle.'</div><div style="font-size: 13px;text-transform: uppercase;" class="clearfix">'.$subtitleB.'</div></div>'.$GraphDisplayRenderCompare2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="available-labor-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_available_labor_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="available-labor-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_available_labor_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard FTE / Square Foot
  if($TileId == 'j'){
    $Ttitle = 'FTE / Square Foot';
    if($obj == 'normal'){
      $Count = ''; 
      $feetquery = db_select('field_data_field_facility_floor_square_feet','fde0ecf5sf');
      $feetquery->leftjoin('node','n','n.nid=fde0ecf5sf.entity_id');
      $feetquery->fields('fde0ecf5sf',array('field_facility_floor_square_feet_value'));
      $feetquery->condition('fde0ecf5sf.bundle','fm_facility','=');
      if(user_or_administrator_data()){
        $feetquery->condition('n.uid',$user->uid,'=');
      }
      $feetresult = $feetquery->execute()->fetchAll();  
      $TotalSf = 0;
      if(isset($feetresult) && !empty($feetresult)){
        foreach($feetresult as $key=>$value){
        if(isset($value) && !empty($value->field_facility_floor_square_feet_value)){
          $real_integer = filter_var($value->field_facility_floor_square_feet_value, FILTER_SANITIZE_NUMBER_INT);
          $TotalSf += $real_integer; 
        }
        }
      }
      
      $ftequery = db_select('field_data_field_facility_ftes','fde0ecf5sf');
      $ftequery->leftjoin('node','n','n.nid=fde0ecf5sf.entity_id');
      $ftequery->fields('fde0ecf5sf',array('field_facility_ftes_value'));
      $ftequery->condition('fde0ecf5sf.bundle','fm_facility','=');
      if(user_or_administrator_data()){
        $ftequery->condition('n.uid',$user->uid,'=');
      }
      $fteresult = $ftequery->execute()->fetchAll();  
      $TotalFte = 0;
      if(isset($fteresult) && !empty($fteresult)){
        foreach($fteresult as $key=>$value){
        if(isset($value) && !empty($value->field_facility_ftes_value)){
          $real_integer = filter_var($value->field_facility_ftes_value, FILTER_SANITIZE_NUMBER_INT);
          $TotalFte += $real_integer; 
        }
        }
      } 
      
      $fte_sf = 0;
      if(isset($TotalSf,$TotalFte) && !empty($TotalSf) && !empty($TotalFte)){  
        $fte_sf = ($TotalSf/ $TotalFte);
      }
            
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">LABOR / SF</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-laborsf.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">SQUARE FOOT / FTE</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.round($fte_sf,2).' sf</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>LABOR / SF</h3><strong>'.$Ttitle.' : '.round($fte_sf,6).' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){
      $ReturnObj = '';
      $Ttype = 'fte_square_foot';
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
      if(isset($TableResult) && !empty($TableResult)){
        $RegionId= unserialize($TableResult[$Ttype]['region']);
        $SiteId= unserialize($TableResult[$Ttype]['site']);
        $FacilityId= unserialize($TableResult[$Ttype]['facility']);
        $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
        $StatusId= unserialize($TableResult[$Ttype]['status']);  
        $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
        $FilterId= unserialize($TableResult[$Ttype]['filter']);
        $ByWotype= unserialize($TableResult[$Ttype]['bytype']);
        
      $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
          $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
        }
        //////////////compare/////////////////////
        $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
        $cquery->fields('hcfmdt');
        $cquery->condition('hcfmdt.user',$user->uid,'=');
        $cquery->condition('hcfmdt.company',$company->nid,'=');
        $cquery->condition('hcfmdt.type',$Ttype,'=');
        //$cquery->condition('hcfmdt.tile_status','compare','=');
        $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }

      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="fte-square-foot-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_gauge_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="fte-square-foot-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_gauge_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="fte-square-foot-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_gauge_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_gauge_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
          $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
          $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);
          $output .= '<div class="pull-left">'.$GraphDisplayRenderCompare1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRenderCompare2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="fte-square-foot-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_fte_square_foot_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="fte-square-foot-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_fte_square_foot_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Labor Use Rate
  if($TileId == 'k'){
    $Ttitle = 'Labor Use Rate'; 
    if($obj == 'normal'){        
      $Count = '';            
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">LABOR USE</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-laboruse.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">WORK ORDER TIME / FTE</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>LABOR USE</h3><strong>'.$Ttitle.' : '.$Count.' </strong>';
      $output .= '</div>';    
    }
  if($obj == 'front'){
    $ReturnObj = '';
    $Ttype = 'labor_use_rate';
    $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
    $query->fields('hcfmdt');
    $query->condition('hcfmdt.user',$user->uid,'=');
    $query->condition('hcfmdt.company',$company->nid,'=');
    $query->condition('hcfmdt.type',$Ttype,'=');
    $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
    if(isset($TableResult) && !empty($TableResult)){
      $RegionId= unserialize($TableResult[$Ttype]['region']);
      $SiteId= unserialize($TableResult[$Ttype]['site']);
      $FacilityId= unserialize($TableResult[$Ttype]['facility']);
      $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
      $StatusId= unserialize($TableResult[$Ttype]['status']);  
      $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
      $FilterId= unserialize($TableResult[$Ttype]['filter']);
      

      $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
          $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
        }
        //////////////compare/////////////////////
        $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
        $cquery->fields('hcfmdt');
        $cquery->condition('hcfmdt.user',$user->uid,'=');
        $cquery->condition('hcfmdt.company',$company->nid,'=');
        $cquery->condition('hcfmdt.type',$Ttype,'=');
        //$cquery->condition('hcfmdt.tile_status','compare','=');
        $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }

          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }

      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="labor-use-rate-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
          $GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'large'){
          $output .= '<div class="labor-use-rate-column-data-display">
          <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
          $GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
          $output .= drupal_render($GraphDisplayRender);
          $output .= '</div>';
        }
        if($objextra == 'compare'){
          $output .= '<div class="labor-use-rate-column-compare-data-display compare-front">';
          $GraphDisplayRender1 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
          $GraphDisplayRender2 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
          $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
          $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);
          $output .= '<div class="pull-left">'.$GraphDisplayRenderCompare1.'</div>';
          $output .= '<div class="pull-right">'.$GraphDisplayRenderCompare2.'</div>';
          $output .= '</div>';
        }
      }
    }
    if($obj == 'back'){
      if(isset($objextra) && !empty($objextra)){
        if($objextra == 'normal'){
          $output .= '<div class="labor-use-rate-column-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_labor_use_rate_form');
          $output .= drupal_render($GraphFormRender);
          $output .= '</div>'; 
        }
        if($objextra == 'compare'){
          $output .= '<div class="labor-use-rate-column-compare-data-setting normal-back">';
          $GraphFormRender = drupal_get_form('hcfm_dashboard_labor_use_rate_form','compare');
          $CompareGraphFormRender = drupal_render($GraphFormRender);
          $output .= $CompareGraphFormRender;
          $output .= '</div>'; 
        }
      }
    }
  }
  //dashboard Labor Forecast
  if($TileId == 'l'){
    $Ttitle = 'Labor Forecast';
    if($obj == 'normal'){      
      $Count = '';      
      $output .= '<div class="small-'.$TileId.'">';
      $output .=    '<div class="small-outer clearfix">';
      $output .=      '<div class="small-first-title first-sec clearfix">LABOR NEEDS</div>';
      $output .=      '<div class="small-first-content clearfix"><div class="small-images second-sec clearfix">
                        <div class="">
                          <img src="/sites/all/themes/m6connect/images/hcfm/hcfm-laborneeds.jpg">
                        </div>
                        <div class="two pull-right">
                          <div class="two-one">
                            
                          </div>
                          <div class="two-two">
                            
                          </div>
                        </div>
                      </div>';
      $output .=      '<div class="small-second-title third-sec clearfix"><div class="small-second-title-inner clearfix">FUTURE WORK ORDER TIME  / FTE</div></div>';
      $output .=      '<div class="small-count forth-sec clearfix">'.$Count.'</div>';
      $output .=    '</div></div>';
      //$output .= '<br><br><h3>LABOR FORECAST</h3><strong>'.$Ttitle.' : '.$Count.' </strong>';
      $output .= '</div>';    
    }
    if($obj == 'front'){
      $ReturnObj = '';
      $Ttype = 'labor_forecast';
      $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
      $query->fields('hcfmdt');
      $query->condition('hcfmdt.user',$user->uid,'=');
      $query->condition('hcfmdt.company',$company->nid,'=');
      $query->condition('hcfmdt.type',$Ttype,'=');
      $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
     
        if(isset($TableResult) && !empty($TableResult)){
          $RegionId= unserialize($TableResult[$Ttype]['region']);
          $SiteId= unserialize($TableResult[$Ttype]['site']);
          $FacilityId= unserialize($TableResult[$Ttype]['facility']);
          $ZoneId= unserialize($TableResult[$Ttype]['zone']);  
          $StatusId= unserialize($TableResult[$Ttype]['status']);  
          $RiskrankId= unserialize($TableResult[$Ttype]['riskrank']);
          $FilterId= unserialize($TableResult[$Ttype]['filter']);
          


          $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);
          $graphrenderdatanormal = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
          // drup_msg($graphrenderdatanormal);
        }
        //////////////compare/////////////////////
        $cquery = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
        $cquery->fields('hcfmdt');
        $cquery->condition('hcfmdt.user',$user->uid,'=');
        $cquery->condition('hcfmdt.company',$company->nid,'=');
        $cquery->condition('hcfmdt.type',$Ttype,'=');
        //$cquery->condition('hcfmdt.tile_status','compare','=');
        $cTableResult = $cquery->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
        if(isset($cTableResult) && !empty($cTableResult)){
          $ARegionId= unserialize($cTableResult[$Ttype]['region_compare_a']);
          $ASiteId= unserialize($cTableResult[$Ttype]['site_compare_a']);
          $AFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_a']);
          $AZoneId= unserialize($cTableResult[$Ttype]['zone_compare_a']);  
          $AStatusId= unserialize($cTableResult[$Ttype]['status_compare_a']);  
          $ARiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_a']);
          $AFilterId= unserialize($cTableResult[$Ttype]['filter_compare_a']);
          $BRegionId= unserialize($cTableResult[$Ttype]['region_compare_b']);
          $BSiteId= unserialize($cTableResult[$Ttype]['site_compare_b']);
          $BFacilityId= unserialize($cTableResult[$Ttype]['facility_compare_b']);
          $BZoneId= unserialize($cTableResult[$Ttype]['zone_compare_b']);  
          $BStatusId= unserialize($cTableResult[$Ttype]['status_compare_b']);  
          $BRiskrankId= unserialize($cTableResult[$Ttype]['riskrank_compare_b']);
          $BFilterId= unserialize($cTableResult[$Ttype]['filter_compare_b']);
          
          $AsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_a']);
          $BsubTitle = unserialize($cTableResult[$Ttype]['subtitle_compare_b']);
          $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
          $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

          if(isset($ARegionId) && !empty($ARegionId) && $ARegionId['all'] == 'all'){
            $ARegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }
          if(isset($BRegionId) && !empty($BRegionId) && $BRegionId['all'] == 'all'){
            $BRegionId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid));
          }

          if(isset($ASiteId) && !empty($ASiteId) && $ASiteId['all'] == 'all'){
            $ASiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }
          if(isset($BSiteId) && !empty($BSiteId) && $BSiteId['all'] == 'all'){
            $BSiteId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid));
          }

          if(isset($AFilterId) && !empty($AFilterId) && $AFilterId['all'] == 'all'){
            $AFilterId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
          if(isset($BFacilityId) && !empty($BFacilityId) && $BFacilityId['all'] == 'all'){
            $BFacilityId = array_keys(hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid));
          }
        
          $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
          $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
          $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);
        }



      
      if(isset($objextra) && !empty($objextra)){
          if($objextra == 'normal'){
            $output .= '<div class="labor-forecast-column-data-display">
            <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';// normal-front
            //$GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($cgetPer,$laborforecastlabel,$laborforecastdata,$Ttype,$Ttitle);
            $GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'');
            $output .= drupal_render($GraphDisplayRender);
            // drup_msg($GraphDisplayRender);
            $output .= '</div>';
          }
          if($objextra == 'large'){
            $output .= '<div class="labor-forecast-column-data-display">
            <div style="text-align: center;font-size:15px;backface-visibility: hidden;" class="margin-top-10">'.$Ttitle.'</div>';
            $GraphDisplayRender = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatanormal['gdata'],$graphrenderdatanormal['glabel'],$graphrenderdatanormal['gextra'],$Ttype,'','large');
            $output .= drupal_render($GraphDisplayRender);
            $output .= '</div>';
          }
          if($objextra == 'compare'){
            $output .= '<div class="labor-forecast-column-compare-data-display compare-front">';
            $GraphDisplayRender1 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
            $GraphDisplayRender2 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
            $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
            $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);
            $output .= '<div class="pull-left">'.$GraphDisplayRenderCompare1.'</div>';
            $output .= '<div class="pull-right">'.$GraphDisplayRenderCompare2.'</div>';
            $output .= '</div>';
          }
        }
      }
      if($obj == 'back'){
        if(isset($objextra) && !empty($objextra)){
          if($objextra == 'normal'){
            $output .= '<div class="labor-forecast-column-data-setting normal-back">';
            $GraphFormRender = drupal_get_form('hcfm_dashboard_labor_forecast_form');
            $output .= drupal_render($GraphFormRender);
            $output .= '</div>'; 
          }
          if($objextra == 'compare'){
            $output .= '<div class="labor-forecast-column-compare-data-setting normal-back">';
            $GraphFormRender = drupal_get_form('hcfm_dashboard_labor_forecast_form','compare');
            $CompareGraphFormRender = drupal_render($GraphFormRender);
            $output .= $CompareGraphFormRender;
            $output .= '</div>'; 
          }
        }
      }
    }
  }  
  return $output;
}
//dashboard asset risk start
function hcfm_dashboard_asset_risk_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') {   
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-asset-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_asset_risk_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-asset-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_asset_risk_process2'),
    );
  }
  return $form;
}

//dashboard asset risk end

//dashboard open pm start
function hcfm_dashboard_back_open_pm_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') {   
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_open_pm-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_open_pm_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_open_pm-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_open_pm_process2'),
    );
  }  
  return $form;
}

//dashboard open pm end

//dashboard open cm start
function hcfm_dashboard_back_open_cm_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') {
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_open_cm-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_open_cm_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_open_cm-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_open_cm_process2'),
    );
  }
  return $form;
}

//dashboard open cm end

//dashboard open projects start
function hcfm_dashboard_back_open_projects_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_open_projects-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_open_projects_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_open_projects-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_open_projects_process2'),
    );
  }
  return $form;
}

//dashboard open projects end

//dashboard Work Orders On Hold start
function hcfm_dashboard_back_work_orders_on_hold_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_on_hold-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_work_orders_on_hold_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_orders_on_hold-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_work_orders_on_hold_process2'),
    );
  }
  return $form;
}

//dashboard Work Orders On Hold end

//dashboard Past Due Work Orders start
function hcfm_dashboard_back_past_due_work_orders_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-past_due_work_orders-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_past_due_work_orders_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-past_due_work_orders-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_past_due_work_orders_process2'),
    );
  }
  return $form;
}

//dashboard Past Due Work Orders end

//dashboard Work Order Ratio start
function hcfm_dashboard_back_work_order_ratio_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_order_ratio-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_work_order_ratio_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-work_order_ratio-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_work_order_ratio_process2'),
    );
  }
  return $form;
}

//dashboard Work Order Ratio end

//dashboard Square Root start
function hcfm_dashboard_back_square_foot_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-square_foot-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_square_foot_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-asset-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-square_foot-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_back_square_foot_process2'),
    );
  }
  return $form;
}

//dashboard Square Root end

//dashboard Available Labor start
function hcfm_dashboard_available_labor_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-use-rate-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-use-rate-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_available_labor_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-use-rate-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-use-rate-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_available_labor_process2'),
    );
  }
  return $form;
}
//dashboard Available Labor end

//dashboard FTE / Square Foot start
function hcfm_dashboard_fte_square_foot_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-use-rate-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-use-rate-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_fte_square_foot_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-use-rate-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-use-rate-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_fte_square_foot_process2'),
    );
  }
  return $form;
}
//dashboard FTE / Square Foot end

//dashboard Labor Use Rate start
function hcfm_dashboard_labor_use_rate_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-use-rate-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-use-rate-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_labor_use_rate_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-use-rate-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-use-rate-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_labor_use_rate_process2'),
    );
  }
  return $form;
}
//dashboard Labor Use Rate end

//dashboard labor forecast start
function hcfm_dashboard_labor_forecast_form($form,&$form_state,$tile_status='normal') {
  if ($tile_status == 'normal') { 
    $form['main-container-main'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-forecast-section padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-forecast-detail">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_labor_forecast_process'),
    );
  }else if ($tile_status == 'compare') { 
    $form['main-container-main2'] = array(
      '#type' => 'container',
      '#attributes' => array('class'=>array('hcfmdashboard-labor-forecast-section2 padding-10 margin-top-10')),
      '#prefix' => '<div class="hcfmdashboard-labor-forecast-detail2">', 
      '#suffix' => '</div>',
      '#process' => array('hcfmdashboard_labor_forecast_process2'),
    );
  }
  return $form;
}
//dashboard labor forecast end


/////graph calculation start /////
function hcmf_dashboard_graphdata($userUid,$companyNid,$Gtype,$Gobject,$Gtitle,$Gstate){
  global $user,$company;
  $GraphData = '';
  if (isset($Gtype) && !empty($Gtype)) {
    $RegionId= $Gobject['region'];
    $SiteId= $Gobject['site'];
    $FacilityId= $Gobject['facility'];
    $ZoneId= $Gobject['zone'];  
    $StatusId= $Gobject['status'];  
    $RiskrankId= $Gobject['riskrank'];
    $FilterId= $Gobject['filter'];
    $DGrapLabel = '';
    $DGrapData = '';
    $DGrapExtra = '';
    if ($Gtype == 'asset') {
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId)|| !empty($FilterId)){
        $query = db_select('node','n');
        $query->fields('n',array('nid','title','uid','status'));
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_asset_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_asset_region_target_id')); 
          $query->condition('fdfwr.field_asset_region_target_id',$RegionId,'IN');
        }
        else{
          $query->leftjoin('field_data_field_asset_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_asset_region_target_id'));
        }
        if(isset($SiteId) && !empty($SiteId)){
          $query->leftjoin('field_data_field_asset_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_asset_site_target_id')); 
          $query->condition('fdfws.field_asset_site_target_id',$SiteId,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $query->leftjoin('field_data_field_asset_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_asset_facility_target_id')); 
          $query->condition('fdfwf.field_asset_facility_target_id',$FacilityId,'IN');
        }
        if(isset($ZoneId) && !empty($ZoneId)){
          $query->leftjoin('field_data_field_asset_location','fdfwlo','fdfwlo.entity_id=n.nid');
          $query->fields('fdfwlo',array('field_asset_location_target_id')); 
          $query->condition('fdfwlo.field_asset_location_target_id',$WoZonNid,'IN');
        }
        if(isset($StatusId) && !empty($StatusId)){
          $query->leftjoin('field_data_field_asset_status','fdfwsta','fdfwsta.entity_id=n.nid');
          $query->fields('fdfwsta',array('field_asset_status_target_id')); 
          $query->condition('fdfwsta.field_asset_status_target_id',$StatusId,'IN');
        }
        if(isset($RiskrankId) && !empty($RiskrankId)){
          $query->leftjoin('field_data_field_asset_priority_rr','fdfwprr','fdfwprr.entity_id=n.nid');
          $query->fields('fdfwprr',array('field_asset_priority_rr_target_id')); 
          $query->leftjoin('field_data_field_asset_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_asset_region_target_id'));
          $query->condition('fdfwprr.field_asset_priority_rr_target_id',$RiskrankId,'IN');
        }
        else{
          $query->leftjoin('field_data_field_asset_priority_rr','fdfwprr','fdfwprr.entity_id=n.nid');    
          $query->fields('fdfwprr',array('field_asset_priority_rr_target_id'));
        }
        if(isset($FilterId) && !empty($FilterId)){
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->havingCondition('asset_created',array($day_start, $day_end), 'BETWEEN');    
          }
        }
        $query->condition('n.type','fm_asset','=');
        $query->addExpression("from_unixtime(n.created, '%M')", 'asset_month');
        $query->addExpression("from_unixtime(n.created, '%Y')", 'asset_year');
        $query->addExpression("from_unixtime(n.created, '%Y-%m-%d %h:%i:%s')", 'asset_created');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
          //$query->havingCondition('asset_year',date('Y'), '=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $renderType = 'field_asset_region_target_id';
        $getGraphData = array_count_values(array_column($ReturnObj , $renderType)); 
        $regionC = count($getGraphData);
        $dataTargetId = array();
        $dataMonth = array();
        $glab = array();
        foreach ($ReturnObj as $key => $value) {
          if($dataTargetId[$value['field_asset_priority_rr_target_id']] != $value[$renderType]){
            $dataTargetId[$value['field_asset_priority_rr_target_id']] = $value[$renderType];
            $dataMonth[$value['field_asset_priority_rr_target_id']][$value[$renderType]] = 1;
          }
          else{
            ++$dataMonth[$value['field_asset_priority_rr_target_id']][$value[$renderType]];
          }
        }
        $gdataK = array_keys($getGraphData);
        $arr = array();
        foreach ($dataMonth as $key => $monArr) {
          $j=0;
          foreach ($monArr as $mon => $monValue) {
            $glab[$mon]=_get_title_of_node($mon);
            for($i = $j; $i < $regionC; $i++)  {
              $nkey = array_search($mon, $gdataK);      
              if($nkey == $i){
                $arr[$key]['nid']= $key;
                $arr[$key]['name']= _get_title_of_node($key);
                $arr[$key]['data'][$i] = $monValue;
              } 
              else if(empty($arr[$key][$i])){
                $arr[$key]['nid']= $key;
                $arr[$key]['name']= _get_title_of_node($key);
                $arr[$key]['data'][$i] = 0;
              }
              if($j == 0){
                ++$j;
              }
            }
          }
        }
        
        $NGlab = array_values($glab);
        $DGrapLabel = $NGlab;
        $DGrapExtra = $arr;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'work_orders_open_pm') {
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $db_or = db_or();     
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->leftjoin('field_data_field_wo_status','fdfwst','fdfwst.entity_id=n.nid');
        $query->fields('fdfwst',array('field_wo_status_target_id'));        
        $query->condition('fdftye.field_wo_type_target_id',52921,'=');//pm        
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id')); 
          $query->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $query->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
        $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
        $query->fields('fdfwf',array('field_wo_facility_target_id')); 
        $query->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
        }
        if(isset($ZoneId) && !empty($ZoneId)){
        $query->leftjoin('field_data_field_wo_location','fdfwlo','fdfwlo.entity_id=n.nid');
        $query->fields('fdfwlo',array('field_wo_location_target_id')); 
        $query->condition('fdfwlo.field_wo_location_target_id',$WoZonNid,'IN');
        }
        if(isset($StatusId) && !empty($StatusId)){
        $query->leftjoin('field_data_field_wo_status','fdfsts','fdfsts.entity_id=n.nid');
        $query->fields('fdfsts',array('field_wo_status_target_id')); 
        $query->condition('fdfsts.field_wo_status_target_id',$StatusId,'IN');
        }else{
        $query->leftjoin('field_data_field_wo_status','fiaspr','fiaspr.entity_id=n.nid');
          $query->fields('fiaspr',array('field_wo_status_target_id'));
        } 
        if(isset($RiskrankId) && !empty($RiskrankId)){
        $query->leftjoin('field_data_field_wo_priority_rr','fdfprr','fdfprr.entity_id=n.nid');
        $query->fields('fdfprr',array('field_wo_priority_rr_target_id')); 
        $query->condition('fdfprr.field_wo_priority_rr_target_id',$RiskrankId,'IN');
        }
        if(isset($FilterId) && !empty($FilterId)){
          $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
        }
        $query->condition('n.type','fm_work_order','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC); 
     
    
        $getGraphData = array_count_values(array_column($ReturnObj, 'field_wo_status_target_id'));    
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
     
        $cgetPer = array();
        $cgetLab = array();
        $NewGpData= array();
        $NewGpDataArrayA= array();
        $NewGpDataArrayB= array();
        foreach($getGraphData as $riskKey => $risk) {     
          if(is_numeric($riskKey)){ 
            /*if(in_array($riskKey,array(52956,52951))){  
              if($riskKey ==52951 ){
                $cgetPer[] = round((($risk/$getFinal )*100) , 2);
                $cgetLab[] =  'PMs Due';//_get_title_of_node($riskKey);
                $NewGpDataArrayA[] = array('name'=>'PMs Due','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
              }else if($riskKey ==59706 ){    
                $cgetLab[] =  'PMs Closed';//_get_title_of_node($riskKey);  
                $cgetPer[] = round((($risk/$getFinal )*100) , 2);
                $NewGpDataArrayA[] = array('name'=>'PMs Closed','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
              } 
            }else{
              $cgetLab[] =  _get_title_of_node($riskKey); 
              $cgetPer[] = round((($risk/$getFinal )*100) , 2);
              $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
            }*/
            $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
          }
        }   
    
        if($cgetLab && $cgetPer){
          $NewGpData['type'] = 'pie';
          $NewGpData['name'] = 'PM Work Order';
          foreach($cgetPer as $key=>$value){
          $NewGpData['data'][]=array($cgetLab[$key],$value);
          }
        }        
        $NewGpDataArrayB =  array($NewGpData);        
        $DGrapLabel = $cgetLab;
        $DGrapData = $cgetPer;
        $DGrapExtra = $NewGpDataArrayA;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'work_orders_open_cm') {
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $db_or = db_or();
        $query = db_select('node','n');
        $query->fields('n',array('nid','title','uid','status'));
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->leftjoin('field_data_field_wo_status','fdfwst','fdfwst.entity_id=n.nid');
        $query->fields('fdfwst',array('field_wo_status_target_id'));
        $query->condition('fdftye.field_wo_type_target_id',52926,'=');        
        if(isset($RegionId) && !empty($RegionId)){
        $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
        $query->fields('fdfwr',array('field_wo_region_target_id')); 
        $query->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
        $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
        $query->fields('fdfws',array('field_wo_site_target_id')); 
        $query->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
        $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
        $query->fields('fdfwf',array('field_wo_facility_target_id')); 
        $query->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
        }
        if(isset($ZoneId) && !empty($ZoneId)){
        $query->leftjoin('field_data_field_wo_location','fdfwlo','fdfwlo.entity_id=n.nid');
        $query->fields('fdfwlo',array('field_wo_location_target_id')); 
        $query->condition('fdfwlo.field_wo_location_target_id',$WoZonNid,'IN');
        }
        if(isset($StatusId) && !empty($StatusId)){
        $query->leftjoin('field_data_field_wo_status','fdfsts','fdfsts.entity_id=n.nid');
        $query->fields('fdfsts',array('field_wo_status_target_id')); 
        $query->condition('fdfsts.field_wo_status_target_id',$StatusId,'IN');
        }else{
        $query->leftjoin('field_data_field_wo_status','fiaspr','fiaspr.entity_id=n.nid');
          $query->fields('fiaspr',array('field_wo_status_target_id'));
        } 
        if(isset($RiskrankId) && !empty($RiskrankId)){
        $query->leftjoin('field_data_field_wo_priority_rr','fdfprr','fdfprr.entity_id=n.nid');
        $query->fields('fdfprr',array('field_wo_priority_rr_target_id')); 
        $query->condition('fdfprr.field_wo_priority_rr_target_id',$RiskrankId,'IN');
        }
        if(isset($FilterId) && !empty($FilterId)){
          $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
        }
        $query->condition('n.type','fm_work_order','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $getGraphData = array_count_values(array_column($ReturnObj, 'field_wo_status_target_id'));    
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $cgetLab = array();
        $NewGpDataArrayA = array();
        foreach($getGraphData as $riskKey => $risk) { 
          //$cgetPer[] = round((($risk/$getFinal )*100) , 2);
          if(is_numeric($riskKey)){   
            /*if(in_array($riskKey,array(52956,52951))){    
              if($riskKey ==52951 ){  
                $cgetLab[] =  'CMs Due';//_get_title_of_node($riskKey);
                $NewGpDataArrayA[] = array('name'=>'CMs Due','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));     
              }else if($riskKey ==59706 ){        
                $cgetLab[] =  'CMs Closed';//_get_title_of_node($riskKey);
                $NewGpDataArrayA[] = array('name'=>'CMs Closed','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));  
              } 
            }else{
              $cgetLab[] =  _get_title_of_node($riskKey);
              $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
            }*/
            $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
          }
        }
        $DGrapLabel = $cgetLab;
        $DGrapData = $cgetPer;
        $DGrapExtra = $NewGpDataArrayA;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'work_orders_open_projects') {
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $db_or = db_or();     
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->leftjoin('field_data_field_wo_status','fdfwst','fdfwst.entity_id=n.nid');
            $query->fields('fdfwst',array('field_wo_status_target_id'));        
        $query->condition('fdftye.field_wo_type_target_id',52931,'=');//project
        //$db_or ->condition('fdfwst.field_wo_status_target_id',59706,'=');//completed
        //$db_or ->condition('fdfwst.field_wo_status_target_id',52951,'=');//issued
        //$query->condition($db_or);  
        if(isset($RegionId) && !empty($RegionId)){
        $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
        $query->fields('fdfwr',array('field_wo_region_target_id')); 
        $query->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
        $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
        $query->fields('fdfws',array('field_wo_site_target_id')); 
        $query->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
        $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
        $query->fields('fdfwf',array('field_wo_facility_target_id')); 
        $query->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
        }
        if(isset($ZoneId) && !empty($ZoneId)){
        $query->leftjoin('field_data_field_wo_location','fdfwlo','fdfwlo.entity_id=n.nid');
        $query->fields('fdfwlo',array('field_wo_location_target_id')); 
        $query->condition('fdfwlo.field_wo_location_target_id',$WoZonNid,'IN');
        }
        if(isset($StatusId) && !empty($StatusId)){
        $query->leftjoin('field_data_field_wo_status','fdfsts','fdfsts.entity_id=n.nid');
        $query->fields('fdfsts',array('field_wo_status_target_id')); 
        $query->condition('fdfsts.field_wo_status_target_id',$StatusId,'IN');
        }else{
        $query->leftjoin('field_data_field_wo_status','fiaspr','fiaspr.entity_id=n.nid');
          $query->fields('fiaspr',array('field_wo_status_target_id'));
        } 
        if(isset($RiskrankId) && !empty($RiskrankId)){
        $query->leftjoin('field_data_field_wo_priority_rr','fdfprr','fdfprr.entity_id=n.nid');
        $query->fields('fdfprr',array('field_wo_priority_rr_target_id')); 
        $query->condition('fdfprr.field_wo_priority_rr_target_id',$RiskrankId,'IN');
        }
        if(isset($FilterId) && !empty($FilterId)){
          $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
        }
        $query->condition('n.type','fm_work_order','=');
        if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $getGraphData = array_count_values(array_column($ReturnObj, 'field_wo_status_target_id'));    
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $cgetLab = array();
        $NewGpDataArrayA = array();
        foreach($getGraphData as $riskKey => $risk) { 
          //$cgetPer[] = round((($risk/$getFinal )*100) , 2);
          if(is_numeric($riskKey)){
            /*if(in_array($riskKey,array(52951,59706))){    
              if($riskKey ==52951 ){  
                $cgetLab[] =  'Project WOs Due';//_get_title_of_node($riskKey);     
                $NewGpDataArrayA[] = array('name'=>'Project WOs Due','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
              }else if($riskKey ==59706 ){        
                $cgetLab[] =  'Project WOs Closed';//_get_title_of_node($riskKey);  
                $NewGpDataArrayA[] = array('name'=>'Project WOs Closed','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
              }
            }else{
              $cgetLab[] =  _get_title_of_node($riskKey);
              $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
            }*/
            $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
          }
        } 

        $DGrapLabel = $cgetLab;
        $DGrapData = $cgetPer;
        $DGrapExtra = $NewGpDataArrayA;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'work_orders_on_hold') {
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){   
        $db_or = db_or();     
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->leftjoin('field_data_field_wo_status','fdfwst','fdfwst.entity_id=n.nid');
        $query->fields('fdfwst',array('field_wo_status_target_id'));        
        $db_or ->condition('fdfwst.field_wo_status_target_id',52956,'=');//Status:  Awaiting Parts    
        $db_or ->condition('fdfwst.field_wo_status_target_id',52951,'=');//Status:  Issued         
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id')); 
          $query->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $query->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $query->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
        }
        if(isset($ZoneId) && !empty($ZoneId)){
          $query->leftjoin('field_data_field_wo_location','fdfwlo','fdfwlo.entity_id=n.nid');
          $query->fields('fdfwlo',array('field_wo_location_target_id')); 
          $query->condition('fdfwlo.field_wo_location_target_id',$WoZonNid,'IN');
        }
        if(isset($StatusId) && !empty($StatusId)){
          $query->leftjoin('field_data_field_wo_status','fdfsts','fdfsts.entity_id=n.nid');
          $query->fields('fdfsts',array('field_wo_status_target_id')); 
          $query->condition('fdfsts.field_wo_status_target_id',$StatusId,'IN');
        }else{
          $query->leftjoin('field_data_field_wo_status','fiaspr','fiaspr.entity_id=n.nid');
          $query->fields('fiaspr',array('field_wo_status_target_id'));        
        } 
        if(isset($RiskrankId) && !empty($RiskrankId)){
          $query->leftjoin('field_data_field_wo_priority_rr','fdfprr','fdfprr.entity_id=n.nid');
          $query->fields('fdfprr',array('field_wo_priority_rr_target_id')); 
          $query->condition('fdfprr.field_wo_priority_rr_target_id',$RiskrankId,'IN');
        }
        if(isset($FilterId) && !empty($FilterId)){
          $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
        }
        $query->condition('n.type','fm_work_order','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $getGraphData = array_count_values(array_column($ReturnObj, 'field_wo_status_target_id'));    
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $cgetLab = array();
        $NewGpDataArrayA = array();
        foreach($getGraphData as $riskKey => $risk) { 
          //$cgetPer[] = round((($risk/$getFinal )*100) , 2);
          if(is_numeric($riskKey)){ 
            /*if(in_array($riskKey,array(52956,52951))){    
              if($riskKey ==52951 ){  
                $cgetLab[] =  'WOs Open';//_get_title_of_node($riskKey);  
                $NewGpDataArrayA[] = array('name'=>'WOs Open','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));    
              }else if($riskKey ==52956 ){        
                $cgetLab[] =  'WOs On Hold';//_get_title_of_node($riskKey); 
                $NewGpDataArrayA[] = array('name'=>'WOs Hold','x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
              } 
            }else{
              $cgetLab[] =  _get_title_of_node($riskKey);
              $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
            }*/
            $NewGpDataArrayA[] = array('name'=>_get_title_of_node($riskKey),'x'=>$risk,'y'=>round((($risk/$getFinal )*100) , 2));
          }
        }

        $DGrapLabel = $cgetLab;
        $DGrapData = $cgetPer;
        $DGrapExtra =$NewGpDataArrayA;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'past_due_work_orders') {
      $renderType = '';
      $ByWotype = '';
      if(isset($RegionId) && !empty($RegionId) && empty($SiteId) && empty($FacilityId) && empty($ZoneId)){
        $rcount = count($RegionId);
        if($rcount >1){
         $renderType = 'field_wo_region_target_id';     
        }else if($rcount == 1){
          $renderType = 'field_wo_site_target_id';
          $ByWotype = 'fm_location_site';
          $ByWotypeListNid = get_location_data_callback('region',array_keys($RegionId),false);
        }
      }else if(isset($SiteId,$RegionId) && !empty($SiteId) && !empty($RegionId)&& empty($FacilityId) && empty($ZoneId)){   
        $scount = count($SiteId);
        if($scount >1){        
          $renderType = 'field_wo_site_target_id';
        }else if($scount == 1){
          $renderType = 'field_wo_facility_target_id';
          $ByWotype = 'fm_facility';
          $ByWotypeListNid = get_location_data_callback('site',array_keys($SiteId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId) && empty($ZoneId)){   
        $fcount = count($FacilityId);
        if($fcount >1){
          $renderType = 'field_wo_facility_target_id';        
        }else if($fcount == 1){
          $renderType = 'field_wo_location_target_id';
          $ByWotype = 'fm_location_location';
          $ByWotypeListNid = get_location_data_callback('facility',array_keys($FacilityId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId,$ZoneId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId)&& !empty($ZoneId)){
        $renderType = 'field_wo_location_target_id';      
      }else{
        $renderType = 'field_wo_region_target_id';
        $ByWotype = 'fm_location_region';
        $ByWotypeListNid = hcfm_nodenid_nodetitle_by_node_type($ByWotype,$ComNid,$UserUid);
      }
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->fields('fdftye',array('field_wo_type_target_id'));  
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id')); 
          $query->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_region'){
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id')); 
          $query->condition('fdfwr.field_wo_region_target_id',array_keys($ByWotypeListNid) ,'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $query->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_site'){
         $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
         $query->fields('fdfws',array('field_wo_site_target_id')); 
         $query->condition('fdfws.field_wo_site_target_id',array_keys($ByWotypeListNid) ,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $query->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_facility'){
         $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $query->condition('fdfwf.field_wo_facility_target_id',array_keys($ByWotypeListNid) ,'IN');     
        }
        if(isset($ZoneId) && !empty($ZoneId)){
          $query->leftjoin('field_data_field_wo_location','fdfwlo','fdfwlo.entity_id=n.nid');
          $query->fields('fdfwlo',array('field_wo_location_target_id')); 
          $query->condition('fdfwlo.field_wo_location_target_id',$WoZonNid,'IN');
        }

        if(isset($StatusId) && !empty($StatusId)){
          $query->leftjoin('field_data_field_wo_status','fdfsts','fdfsts.entity_id=n.nid');
          $query->fields('fdfsts',array('field_wo_status_target_id')); 
          $query->condition('fdfsts.field_wo_status_target_id',$StatusId,'IN');
        }else{
          $query->leftjoin('field_data_field_wo_status','fiaspr','fiaspr.entity_id=n.nid');
          $query->fields('fiaspr',array('field_wo_status_target_id'));
        } 
        if(isset($RiskrankId) && !empty($RiskrankId)){
          $query->leftjoin('field_data_field_wo_priority_rr','fdfprr','fdfprr.entity_id=n.nid');
          $query->fields('fdfprr',array('field_wo_priority_rr_target_id')); 
          $query->condition('fdfprr.field_wo_priority_rr_target_id',$RiskrankId,'IN');
        }
        if(isset($FilterId) && !empty($FilterId)){
          $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
        }
        $query->condition('n.type','fm_work_order','=');
        if(user_or_administrator_data()){
        $query->condition('n.uid',$user->uid,'=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $backlogXX = '';
        $NewGpDataArrayB = array();
        $getGraphData = array_count_values(array_column($ReturnObj , $renderType)); 
        $regionC = count($getGraphData);
        $dataTargetId = array();
        $dataMonth = array();
        $glab = array();
        foreach ($ReturnObj as $key => $value) {
          if($dataTargetId[$value['field_wo_type_target_id']] != $value[$renderType]){
            $dataTargetId[$value['field_wo_type_target_id']] = $value[$renderType];
            $dataMonth[$value['field_wo_type_target_id']][$value[$renderType]] = 1;
          }
          else{
            ++$dataMonth[$value['field_wo_type_target_id']][$value[$renderType]];
          }
        }
        $gdataK = array_keys($getGraphData);
        $arr = array();
        foreach ($dataMonth as $key => $monArr) {
          $j=0;
          foreach ($monArr as $mon => $monValue) {
            $glab[$mon]=_get_title_of_node($mon);
            for($i = $j; $i < $regionC; $i++)  {
              $nkey = array_search($mon, $gdataK);      
              if($nkey == $i){
                $arr[$key]['nid']= $key;
                $arr[$key]['name']= _get_title_of_node($key);
                $arr[$key]['data'][$i ] = $monValue;
              } 
              else if(empty($arr[$key][$i])){
                $arr[$key]['nid']= $key;
                $arr[$key]['name']= _get_title_of_node($key);
                $arr[$key]['data'][$i] = 0;
              }
              if($j == 0){
                ++$j;
              }
            }
          }
        }
        $NGlab = array_values($glab);
        $backlogXX = $NGlab;
        $NewGpDataArrayB = $arr;

        $DGrapLabel = $backlogXX;
        $DGrapData = $cgetPer;
        $DGrapExtra = $NewGpDataArrayB;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'work_order_ratio') {
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_wo_region','fdfwst','fdfwst.entity_id=n.nid');
          $query->fields('fdfwst',array('field_wo_region_target_id')); 
          $query->condition('fdfwst.field_wo_region_target_id',$RegionId,'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $query->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $query->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
        }
        if(isset($ZoneId) && !empty($ZoneId)){
          $query->leftjoin('field_data_field_wo_location','fdfwlo','fdfwlo.entity_id=n.nid');
          $query->fields('fdfwlo',array('field_wo_location_target_id')); 
          $query->condition('fdfwlo.field_wo_location_target_id',$WoZonNid,'IN');
        }
        if(isset($StatusId) && !empty($StatusId)){
          $query->leftjoin('field_data_field_wo_status','fdfsts','fdfsts.entity_id=n.nid');
          $query->fields('fdfsts',array('field_wo_status_target_id')); 
          $query->condition('fdfsts.field_wo_status_target_id',$StatusId,'IN');
        }
        if(isset($RiskrankId) && !empty($RiskrankId)){
          $query->leftjoin('field_data_field_wo_priority_rr','fdfprr','fdfprr.entity_id=n.nid');
          $query->fields('fdfprr',array('field_wo_priority_rr_target_id')); 
          $query->condition('fdfprr.field_wo_priority_rr_target_id',$RiskrankId,'IN');
        }
        if(isset($WoTypeId) && is_numeric($WoTypeId) && !empty($WoTypeId)){     
          $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
          $query->fields('fdftye',array('field_wo_type_target_id'));
          $query->condition('fdftye.field_wo_type_target_id',$WoTypeId,'IN');
        }
        else{
          $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
          $query->fields('fdftye',array('field_wo_type_target_id'));
        }
        if(isset($FilterId) && !empty($FilterId)){
          $query->leftjoin('field_data_field_wo_date_completed','fdfdaed','fdfdaed.entity_id=n.nid');
          if(array_key_exists('today', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', time());
            $day_end = date('Y-m-d 23:59:59', time());
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('tomorrow', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("+1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("+1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('yesterday', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime("-1 day"));
            $day_end = date('Y-m-d 23:59:59', strtotime("-1 day"));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January last year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec last year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of last month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of last month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('last_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('monday last week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sundaylast week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('this_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of jan this year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec this year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of this month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of this month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('this_week', $FilterId)){
             $day_start = date('Y-m-d 00:00:00', strtotime('monday this week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday this week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }   
          if(array_key_exists('next_year', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of January next year'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of dec next year'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_month', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('first day of next month'));
            $day_end = date('Y-m-d 23:59:59', strtotime('last day of next month'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
          if(array_key_exists('next_week', $FilterId)){
            $day_start = date('Y-m-d 00:00:00', strtotime('mondayt next week'));
            $day_end = date('Y-m-d 23:59:59', strtotime('sunday next week'));
            $query->condition('fdfdaed.field_wo_date_completed_value',array($day_start, $day_end), 'BETWEEN');
          }
        }
        $query->condition('n.type','fm_work_order','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC); 

        $getGraphData = array_count_values(array_column($ReturnObj, 'field_wo_type_target_id'));    
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $cgetLab = array();
        foreach($getGraphData as $riskKey => $risk) { 
          $cgetPer[] = round((($risk/$getFinal )*100) , 2);
          if(is_numeric($riskKey)){     
          $cgetLab[] =  _get_title_of_node($riskKey);     
          }
        }

        $DGrapLabel = $cgetLab;
        $DGrapData = $cgetPer;
        //$DGrapExtra = $NewGpDataArrayB;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'square_foot') {
      $renderType = '';
      $ByWotype = '';
      if(isset($RegionId) && !empty($RegionId) && empty($SiteId) && empty($FacilityId) && empty($ZoneId)){
        $rcount = count($RegionId);
        if($rcount >1){
          $renderType = 'field_location_region_target_id';     
        }else if($rcount == 1){
          $renderType = 'field_facility_location_site_target_id';
          $ByWotype = 'fm_location_site';
          $ByWotypeListNid = get_location_data_callback('region',array_keys($RegionId),false);
        }
      }else if(isset($SiteId,$RegionId) && !empty($SiteId) && !empty($RegionId)&& empty($FacilityId) && empty($ZoneId)){   
        $scount = count($SiteId);
        if($scount >1){        
          $renderType = 'field_facility_location_site_target_id';
        }else if($scount == 1){
          $renderType = 'nid';
          $ByWotype = 'fm_facility';
          $ByWotypeListNid = get_location_data_callback('site',array_keys($SiteId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId) && empty($ZoneId)){   
        $fcount = count($FacilityId);
        $renderType = 'nid';
      }else{
        $renderType = 'field_location_region_target_id';
      }
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->fields('fdftye',array('field_wo_type_target_id'));
        $query->leftjoin('field_data_field_facility_floor_square_feet','fde0ecf5sf','fde0ecf5sf.entity_id=n.nid');
        $query->fields('fde0ecf5sf',array('field_facility_floor_square_feet_value'));
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_region'){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',array_keys($ByWotypeListNid),'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
          $query->condition('fdffls.field_facility_location_site_target_id',$SiteId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_site'){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
          $query->condition('fdffls.field_facility_location_site_target_id',array_keys($ByWotypeListNid),'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
          $query->condition('fdffls.field_facility_location_site_target_id',$SiteId,'IN');
          $query->condition('n.nid',$FacilityId,'IN');
        }
        $query->condition('n.type','fm_facility','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $query->leftjoin('field_data_field_cm_type','fdffcmty','fdffcmty.entity_id=n.nid');
        $query->fields('fdffcmty',array('field_cm_type_value'));
        $query->condition('fdffcmty.field_cm_type_value','hcfm','=');
        $query->condition('fde0ecf5sf.field_facility_floor_square_feet_value','','!=');
        //$ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        /*$getGraphData = array_count_values(array_column($ReturnObj, $renderType));   

        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $NcgetPer = array();
        $cgetLab = array();
        foreach($getGraphData as $riskKey => $risk) {     
          if(is_numeric($riskKey)){     
            $cgetLab[] =  _get_title_of_node($riskKey);     
          }
        }
        $rkey =array_flip(array_keys($getGraphData));
        $arrData1 = array();
        $NewGpDataArrayB = array();
        if(isset($ReturnObj) && !empty($ReturnObj)){
          foreach($ReturnObj as $key=>$valuec){
    //pre($valuec['field_facility_floor_square_feet_value']);
          if(isset($valuec) && !empty($valuec['field_facility_floor_square_feet_value']) && $valuec[$renderType]){
            $real_integer = filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);
            $TotalSf += $real_integer; 
            $cgetPer[$rkey[$valuec[$renderType]]] += filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);
            $NewGpDataArrayB[$rkey[$valuec[$renderType]]]['name'] =$cgetLab[$rkey[$valuec[$renderType]]];
            $NewGpDataArrayB[$rkey[$valuec[$renderType]]]['data'] += filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);
             //$arrData1[$valuec[$renderType]] = $TotalSf;
           }
          }
        }*/
        $ReturnObj =  $query->execute()->fetchAllKeyed(0,1);

        $getGraphData = array_count_values(array_column($ReturnObj, $renderType));   
        if(isset($ReturnObj ) && !empty($ReturnObj)){     
          $sfnids = array_keys($ReturnObj);
          $query1 = db_select('node','n');       
          $query1->fields('n',array('nid','title','uid','status'));   
          $query1->leftjoin('field_data_field_facility_floor_square_feet','fde0ecf5sf','fde0ecf5sf.entity_id=n.nid');
          $query1->fields('fde0ecf5sf',array('field_facility_floor_square_feet_value'));
          $query1->condition('fde0ecf5sf.field_facility_floor_square_feet_value',' ','!=');
          $query1->condition('n.nid',$sfnids,'IN');
          $sfValues = $query1->execute()->fetchAll(PDO::FETCH_ASSOC);
          $cgetLab = array();
          $cgetPer = array();
          $NewGpDataArrayB = array();
          if(isset($sfValues) && !empty($sfValues)){
            foreach($sfValues as $key=>$valuec){     
              if(isset($valuec) && !empty($valuec['field_facility_floor_square_feet_value'])){
                $real_integer = filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);
                $TotalSf += $real_integer; 
                $cgetLab[$valuec['nid']] = $valuec['title'];
                $cgetPer[$valuec['nid']] += filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);              
                $NewGpDataArrayB[$valuec['nid']]['name'] =$valuec['title']; 
                $NewGpDataArrayB[$valuec['nid']]['data'] += filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);               
              }
            }
          }
        }
        $DGrapLabel = array_values($cgetLab);//(isset($cgetLab) && !empty($cgetLab)?array_values($cgetLab)?$cgetLab);
        $DGrapData = array_values($cgetPer);//(isset($cgetPer) && !empty($cgetPer)?array_values($cgetPer)?$cgetPer);
        
        $DGrapExtra = array_values($NewGpDataArrayB);//(isset($NewGpDataArrayB) && !empty($NewGpDataArrayB)?array_values($NewGpDataArrayB)?$NewGpDataArrayB);
        
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'available_labor') {
      $renderType = '';
      $ByWotype = '';
      if(isset($RegionId) && !empty($RegionId) && empty($SiteId) && empty($FacilityId) && empty($ZoneId)){
        $rcount = count($RegionId);
        if($rcount >1){
         $renderType = 'field_location_region_target_id';     
        }else if($rcount == 1){
          $renderType = 'field_facility_location_site_target_id';
          $ByWotype = 'fm_location_site';
          $ByWotypeListNid = get_location_data_callback('region',array_keys($RegionId),false);
        }
      }else if(isset($SiteId,$RegionId) && !empty($SiteId) && !empty($RegionId)&& empty($FacilityId) && empty($ZoneId)){   
        $scount = count($SiteId);
        if($scount >1){        
          $renderType = 'field_facility_location_site_target_id';
        }else if($scount == 1){
          $renderType = 'nid';
          $ByWotype = 'fm_facility';
          $ByWotypeListNid = get_location_data_callback('site',array_keys($SiteId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId) && empty($ZoneId)){   
        $fcount = count($FacilityId);
        $renderType = 'nid';
      }else{
        $renderType = 'field_location_region_target_id';
      }
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $query = db_select('node','n');
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->fields('fdftye',array('field_wo_type_target_id'));
        $query->leftjoin('field_data_field_facility_ftes','fdfffte','fdfffte.entity_id=n.nid');
        $query->fields('fdfffte',array('field_facility_ftes_value'));
        if(isset($RegionId) && !empty($RegionId)){          
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_region'){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',array_keys($ByWotypeListNid),'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){          
          $query->condition('fdffls.field_facility_location_site_target_id',$SiteId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_site'){
          $query->condition('fdffls.field_facility_location_site_target_id',array_keys($ByWotypeListNid),'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $query->condition('n.nid',$FacilityId,'IN');
        }
        $query->condition('n.type','fm_facility','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $query->leftjoin('field_data_field_cm_type','fdffcmty','fdffcmty.entity_id=n.nid');
        $query->fields('fdffcmty',array('field_cm_type_value'));
        $query->condition('fdffcmty.field_cm_type_value','hcfm','=');
        $query->condition('fdfffte.field_facility_ftes_value','','!=');
        $ReturnObj = $query->execute()->fetchAll(PDO::FETCH_ASSOC);

        $getGraphData = array_count_values(array_column($ReturnObj, $renderType));
        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $NcgetPer = array();
        $cgetLab = array();
        foreach($getGraphData as $riskKey => $risk) {
         // $cgetPer[] = round((($risk/$getFinal )*100) , 2);   
          if(is_numeric($riskKey)){     
            $cgetLab[] =  _get_title_of_node($riskKey);     
          }
        }
        $rkey =array_flip(array_keys($getGraphData));
        $arrData1 = array();
        if(isset($ReturnObj) && !empty($ReturnObj)){
          foreach($ReturnObj as $key=>$valuec){
         
           if(isset($valuec) && !empty($valuec['field_facility_ftes_value']) && $valuec[$renderType]){
             $Fte_real_integer = filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
             $TotalFte += $Fte_real_integer ; 
             $cgetPer['0']['name']='FTE';
             $cgetPer['0']['data'][$rkey[$valuec[$renderType]]] += filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
             $cgetPer['1']['name']='HOURS';
             $cgetPer['1']['data'][$rkey[$valuec[$renderType]]] += round(filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT)*165,4);
             //$arrData1['fte'] = $TotalFte ;
           }
          }
        }

        $DGrapLabel = $cgetLab;
        $DGrapData = '';
        $DGrapExtra = $cgetPer;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'fte_square_foot') {
      $renderType = '';
      $ByWotype = '';
      if(isset($RegionId) && !empty($RegionId) && empty($SiteId) && empty($FacilityId) && empty($ZoneId)){
        $rcount = count($RegionId);
        if($rcount >1){
         $renderType = 'field_location_region_target_id';     
        }else if($rcount == 1){
          $renderType = 'field_facility_location_site_target_id';
          $ByWotype = 'fm_location_site';
          $ByWotypeListNid = get_location_data_callback('region',array_keys($RegionId),false);
        }
      }else if(isset($SiteId,$RegionId) && !empty($SiteId) && !empty($RegionId)&& empty($FacilityId) && empty($ZoneId)){   
        $scount = count($SiteId);
        if($scount >1){        
          $renderType = 'field_facility_location_site_target_id';
        }else if($scount == 1){
          $renderType = 'nid';
          $ByWotype = 'fm_facility';
          $ByWotypeListNid = get_location_data_callback('site',array_keys($SiteId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId) && empty($ZoneId)){   
        $fcount = count($FacilityId);
        $renderType = 'nid';
      }else{
        $renderType = 'field_location_region_target_id';
      }
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId) || !empty($FilterId)){
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->fields('fdftye',array('field_wo_type_target_id'));
        $query->leftjoin('field_data_field_facility_floor_square_feet','fde0ecf5sf','fde0ecf5sf.entity_id=n.nid');
        $query->fields('fde0ecf5sf',array('field_facility_floor_square_feet_value'));
        $query->leftjoin('field_data_field_facility_ftes','fdfffte','fdfffte.entity_id=n.nid');
        $query->fields('fdfffte',array('field_facility_ftes_value'));
        if(isset($RegionId) && !empty($RegionId)){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_region'){
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $query->condition('fdfflslr.field_location_region_target_id','','!=');
          $query->condition('fdfflslr.field_location_region_target_id',array_keys($ByWotypeListNid),'IN');
        }
        if(isset($SiteId) && !empty($SiteId)){          
          $query->condition('fdffls.field_facility_location_site_target_id',$SiteId,'IN');
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_site'){         
          $query->condition('fdffls.field_facility_location_site_target_id',array_keys($ByWotypeListNid),'IN');
        }
        if(isset($FacilityId) && !empty($FacilityId)){          
          $query->condition('n.nid',$FacilityId,'IN');
        }

        $query->condition('n.type','fm_facility','=');
        if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        }
        $query->leftjoin('field_data_field_cm_type','fdffcmty','fdffcmty.entity_id=n.nid');
        $query->fields('fdffcmty',array('field_cm_type_value'));
        $query->condition('fdffcmty.field_cm_type_value','hcfm','=');
        $query->condition('fde0ecf5sf.field_facility_floor_square_feet_value','','!=');
        $ReturnObj = $query->execute()->fetchAll(PDO::FETCH_ASSOC);

        $getGraphData = array_count_values(array_column($ReturnObj, $renderType));   

        foreach($getGraphData as $getCount) {
          $getFinal += $getCount;
        }
        $cgetPer = array();
        $NcgetPer = array();
        $cgetLab = array();
        foreach($getGraphData as $riskKey => $risk) {
         // $cgetPer[] = round((($risk/$getFinal )*100) , 2);   
          if(is_numeric($riskKey)){     
            $cgetLab[] =  _get_title_of_node($riskKey);     
          }
        }

        $rkey =array_flip(array_keys($getGraphData));
        $arrData1 = array();
        if(isset($ReturnObj) && !empty($ReturnObj)){
          foreach($ReturnObj as $key=>$valuec){
          //pre($valuec['field_facility_floor_square_feet_value']);
            if(isset($valuec) && !empty($valuec['field_facility_floor_square_feet_value']) && $valuec[$renderType]){
              $Sf_real_integer = filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);
              $TotalSf += $Sf_real_integer; 
              $cgetPer[$rkey[$valuec[$renderType]]] += filter_var($valuec['field_facility_floor_square_feet_value'], FILTER_SANITIZE_NUMBER_INT);
              $arrData1['sf'] = $TotalSf;
            }
            if(isset($valuec) && !empty($valuec['field_facility_ftes_value']) && $valuec[$renderType]){
              $Fte_real_integer = filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
              $TotalFte += $Fte_real_integer ; 
              //$cgetPer[$rkey[$valuec[$renderType]]] += filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
              //$arrData1['fte'] = $TotalFte ;
              if(!array_key_exists($valuec['nid'],$arrData1['fte'])){
                $arrData1['fte'][$valuec['nid']] += filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
              }
            }
          }
        }
        $Glab =  '';
        $Gdata =  '';
        if(isset($arrData1) && !empty($arrData1['sf'])&& !empty($arrData1['fte'])){
          $ftesvalues = array_values($arrData1['fte']);
          $ftestotal = array_sum($ftesvalues);
          $Gdata = array(round($arrData1['sf']/$ftestotal,2));
        }
        if(isset($cgetLab) && !empty($cgetLab)){
          $Glab = array(implode(',', $cgetLab));
        }

        $DGrapLabel = $Glab;
        $DGrapData = $Gdata;
        $DGrapExtra = $laborforecastdata;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'labor_use_rate') {
      $renderType1 = '';
      $renderType2 = '';
      $ByWotype = '';
      if(isset($RegionId) && !empty($RegionId) && empty($SiteId) && empty($FacilityId) && empty($ZoneId)){
        $rcount = count($RegionId);
        if($rcount >1){
         $renderType1= 'field_location_region_target_id'; 
         $renderType2 = 'field_wo_region_target_id'; 
        }else if($rcount == 1){
         // $renderTypeA = 'field_facility_location_site_target_id';
          $ByWotype = 'fm_location_site';
         $renderType1= 'field_facility_location_site_target_id'; 
         $renderType2 = 'field_wo_site_target_id'; 

          $ByWotypeListNid = get_location_data_callback('region',array_keys($RegionId),false);
        }
      }else if(isset($SiteId,$RegionId) && !empty($SiteId) && !empty($RegionId)&& empty($FacilityId) && empty($ZoneId)){   
        $scount = count($SiteId);
        if($scount >1){        
          //$renderTypeA = 'field_facility_location_site_target_id';
         $renderType1= 'field_facility_location_site_target_id'; 
         $renderType2 = 'field_wo_site_target_id'; 
        }else if($scount == 1){
       //   $renderTypeA = 'nid';
          $renderType1= 'nid'; 
          $renderType2 = 'field_wo_facility_target_id'; 
          $ByWotype = 'fm_facility';
          $ByWotypeListNid = get_location_data_callback('site',array_keys($SiteId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId) && empty($ZoneId)){   
        $fcount = count($FacilityId);
        $renderType1= 'nid'; 
        $renderType2 = 'field_wo_facility_target_id';
      }else{
        $renderType1= 'field_location_region_target_id'; 
        $renderType2 = 'field_wo_region_target_id';
      } 
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId)|| !empty($FilterId)){
        $db_or = db_or();
        $db_and = db_and();
        $db_or2 = db_or();
        $db_and2 = db_and();
        $query = db_select('node','n');
        $query->fields('n',array('nid','title','uid','status','type'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->fields('fdftye',array('field_wo_type_target_id'));
        $query->leftjoin('field_data_field_facility_ftes','fdfffte','fdfffte.entity_id=n.nid');
        $query->fields('fdfffte',array('field_facility_ftes_value'));
        $query->leftjoin('field_data_field_wo_time_charge','fdfwtch','fdfwtch.entity_id=n.nid');
        $query->fields('fdfwtch',array('field_wo_time_charge_value'));
        $query->leftjoin('field_data_field_cm_type','fdfcmty','fdfcmty.entity_id=n.nid');
        $query->fields('fdfcmty',array('field_cm_type_value'));
        if(isset($RegionId) && !empty($RegionId)){        
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $db_or2->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id'));
          $db_or2->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
          $query->condition($db_or2); 
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_region'){      
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $db_or2->condition('fdfflslr.field_location_region_target_id',array_keys($ByWotypeListNid),'IN');
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id'));
          $db_or2->condition('fdfwr.field_wo_region_target_id',array_keys($ByWotypeListNid),'IN');
          $query->condition($db_or2);
        }
        if(isset($SiteId) && !empty($SiteId)){      
          $db_or2->condition('fdffls.field_facility_location_site_target_id',$SiteId,'IN');
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $db_or2->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
          $query->condition($db_or2);
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_site'){
          $db_or2->condition('fdffls.field_facility_location_site_target_id',array_keys($ByWotypeListNid),'IN');
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $db_or2->condition('fdfws.field_wo_site_target_id',array_keys($ByWotypeListNid),'IN');
          $query->condition($db_or2);
        }
        if(isset($FacilityId) && !empty($FacilityId)){        
          $db_or2->condition('n.nid',$FacilityId,'IN');
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $db_or2->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'IN');
          $query->condition($db_or2);
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_facility'){
          //print 'in facility more';print "\n";  
          $db_or2->condition('n.nid',array_keys($ByWotypeListNid),'IN');
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $db_or2->condition('fdfwf.field_wo_facility_target_id',array_keys($ByWotypeListNid),'IN');
          $query->condition($db_or2);
        }
        $db_or->condition('n.type','fm_work_order','=');
        $db_and->condition('n.type','fm_facility','=');
        $db_and->condition('fdfcmty.field_cm_type_value','hcfm','=');
        $query->condition($db_or); 
        $db_or->condition($db_and);
        //if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        //}
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $rskey3 =  array();
        $getGraphData = array_count_values(array_column($ReturnObj, $renderType1));
        $rkey =array_flip(array_keys($getGraphData));
        $renderType = 'field_wo_type_target_id';      
        $getGraphData2 = array_count_values(array_column($ReturnObj, $renderType));
        $getGraphData23 = array_count_values(array_column($ReturnObj, $renderType2));
        $rkeyr2 =array_flip(array_keys($getGraphData23));
        $rskey3 = $rkey + $rkeyr2;
        if(isset($ReturnObj) && !empty($ReturnObj)){
          foreach($ReturnObj as $key=>$valuec){    
            if(isset($valuec[$renderType2]) && !empty($valuec[$renderType2])){
              $arrData1[$valuec[$renderType2]] = _get_title_of_node($valuec[$renderType2]);
            }
            if(isset($valuec[$renderType1]) && !empty($valuec[$renderType1])){
              $arrData1[$valuec[$renderType1]] = _get_title_of_node($valuec[$renderType1]);
            }
            foreach($rskey3 as $rnid2=>$rrkey){          
              if($valuec[$renderType2] == $rnid2){
                $cgetPer2['1']['name']= 'Total Wo Time Charge';
                $cgetPer2['1']['data'][$rrkey] += filter_var($valuec['field_wo_time_charge_value']);
              }else if(empty($cgetPer2['1']['data'][$rrkey])){
                $cgetPer2['1']['name']= 'Total Wo Time Charge';
                $cgetPer2['1']['data'][$rrkey] = 0;
              }
              if($valuec[$renderType1] == $rnid2){
                 $cgetPer2['0']['name']= 'Total FTE Hrs Available';
                 $cgetPer2['0']['data'][$rrkey] += filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
              }else if(empty($cgetPer2['0']['data'][$rrkey])){
                 $cgetPer2['0']['name']= 'Total FTE Hrs Available';
                 $cgetPer2['0']['data'][$rrkey] = 0;
              }
            }
          }
        }     
        ksort($cgetPer2);
        $laborforecastlabel = array_values($arrData1);
        $laborforecastdata = $cgetPer2;

        $DGrapLabel = $laborforecastlabel;
        $DGrapData = '';
        $DGrapExtra = $laborforecastdata;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
    if ($Gtype == 'labor_forecast') {
      $renderType1 = '';
      $renderType2 = '';
      $ByWotype = '';
      if(isset($RegionId) && !empty($RegionId) && empty($SiteId) && empty($FacilityId) && empty($ZoneId)){
        $rcount = count($RegionId);
        if($rcount >1){
         $renderType1= 'field_location_region_target_id'; 
         $renderType2 = 'field_wo_region_target_id'; 
        }else if($rcount == 1){         
          $ByWotype = 'fm_location_site';
         $renderType1= 'field_facility_location_site_target_id'; 
         $renderType2 = 'field_wo_site_target_id'; 
          $ByWotypeListNid = get_location_data_callback('region',array_keys($RegionId),false);
        }
      }else if(isset($SiteId,$RegionId) && !empty($SiteId) && !empty($RegionId)&& empty($FacilityId) && empty($ZoneId)){   
        $scount = count($SiteId);
        if($scount >1){         
          $renderType1= 'field_facility_location_site_target_id'; 
          $renderType2 = 'field_wo_site_target_id'; 
        }else if($scount == 1){
          $renderType1= 'nid'; 
          $renderType2 = 'field_wo_facility_target_id'; 
          $ByWotype = 'fm_facility';
          $ByWotypeListNid = get_location_data_callback('site',array_keys($SiteId),false);
        }
      }else if(isset($SiteId,$RegionId,$FacilityId) && !empty($SiteId) && !empty($RegionId) && !empty($FacilityId) && empty($ZoneId)){   
        $fcount = count($FacilityId);
        $renderType1= 'nid'; 
        $renderType2 = 'field_wo_facility_target_id';
      }else{
        $renderType1= 'field_location_region_target_id'; 
        $renderType2 = 'field_wo_region_target_id';
      } 
      if(!empty($RegionId) || !empty($SiteId) || !empty($FacilityId) || !empty($ZoneId) || !empty($StatusId) || !empty($RiskrankId)|| !empty($FilterId)){
        $db_or = db_or();
        $db_or2 = db_or();
        $query = db_select('node','n');       
        $query->fields('n',array('nid','title','uid','status'));  
        $query->leftjoin('field_data_field_wo_type','fdftye','fdftye.entity_id=n.nid');
        $query->fields('fdftye',array('field_wo_type_target_id'));
        $query->leftjoin('field_data_field_facility_ftes','fdfffte','fdfffte.entity_id=n.nid');
        $query->fields('fdfffte',array('field_facility_ftes_value'));
        $query->leftjoin('field_data_field_wo_estimated_time_1','fdfwesta','fdfwesta.entity_id=n.nid');
        $query->fields('fdfwesta',array('field_wo_estimated_time_1_value'));
        if(isset($RegionId) && !empty($RegionId)){        
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $db_or2->condition('fdfflslr.field_location_region_target_id',$RegionId,'IN');
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id'));
          $db_or2->condition('fdfwr.field_wo_region_target_id',$RegionId,'IN');
          $query->condition($db_or2);
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_region'){      
          $query->leftjoin('field_data_field_facility_location_site','fdffls','fdffls.entity_id=n.nid');
          $query->fields('fdffls',array('field_facility_location_site_target_id'));
          $query->leftjoin('field_data_field_location_region','fdfflslr','fdfflslr.entity_id=fdffls.field_facility_location_site_target_id');
          $query->fields('fdfflslr',array('field_location_region_target_id'));
          $db_or2->condition('fdfflslr.field_location_region_target_id',array_keys($ByWotypeListNid),'IN');
          $query->leftjoin('field_data_field_wo_region','fdfwr','fdfwr.entity_id=n.nid');
          $query->fields('fdfwr',array('field_wo_region_target_id'));
          $db_or2->condition('fdfwr.field_wo_region_target_id',array_keys($ByWotypeListNid),'IN');
          $query->condition($db_or2);
        }
        if(isset($SiteId) && !empty($SiteId)){      
          $db_or2->condition('fdffls.field_facility_location_site_target_id',$SiteId,'IN');
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $db_or2->condition('fdfws.field_wo_site_target_id',$SiteId,'IN');
          $query->condition($db_or2);
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_location_site'){
          $db_or2->condition('fdffls.field_facility_location_site_target_id',array_keys($ByWotypeListNid),'IN');
          $query->leftjoin('field_data_field_wo_site','fdfws','fdfws.entity_id=n.nid');
          $query->fields('fdfws',array('field_wo_site_target_id')); 
          $db_or2->condition('fdfws.field_wo_site_target_id',array_keys($ByWotypeListNid),'IN');
          $query->condition($db_or2);
        }
        if(isset($FacilityId) && !empty($FacilityId)){
          $db_or2->condition('n.nid',$FacilityId,'IN');
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $db_or2->condition('fdfwf.field_wo_facility_target_id',$FacilityId,'=');
          $query->condition($db_or2);
        }else if(isset($ByWotype) && !empty($ByWotype) && $ByWotype == 'fm_facility'){
          $query->leftjoin('field_data_field_wo_facility','fdfwf','fdfwf.entity_id=n.nid');
          $query->fields('fdfwf',array('field_wo_facility_target_id')); 
          $db_or2->condition('fdfwf.field_wo_facility_target_id',array_keys($ByWotypeListNid),'IN');
          $query->condition($db_or2);
        }
        $db_or->condition('n.type','fm_work_order','=');
        $db_or->condition('n.type','fm_facility','=');
        $query->condition($db_or);
        //if(user_or_administrator_data()){
          $query->condition('n.uid',$user->uid,'=');
        //}
        $ReturnObj = $query->execute()->fetchAllAssoc('nid', PDO::FETCH_ASSOC);

        $getGraphData = array_count_values(array_column($ReturnObj, $renderType1));
        $rkey =array_flip(array_keys($getGraphData));
        $arrData1 = array();
        if(isset($ReturnObj) && !empty($ReturnObj)){
          foreach($ReturnObj as $key=>$valuec){
            if(isset($valuec) && !empty($valuec['field_facility_ftes_value']) && is_numeric($valuec['field_facility_ftes_value']) && $valuec[$renderType1]){
              if(isset($valuec[$renderType1]) && !empty($valuec[$renderType1])){
                $arrData1[$valuec[$renderType1]] = _get_title_of_node($valuec[$renderType1]);
              }
              $real_integer2 = filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
              $TotalSf2 += $real_integer; 
              $cgetPer3['fte']['name'] = 'FTE Available';
              $cgetPer3['fte']['data'][$rkey[$valuec[$renderType1]]] += filter_var($valuec['field_facility_ftes_value'], FILTER_SANITIZE_NUMBER_INT);
              $cgetPer3['fte']['stack'] = 'FTE Available';    
            }
          }
        }
        $renderType = 'field_wo_type_target_id';        
        $getGraphData2 = array_count_values(array_column($ReturnObj, $renderType));
        $getGraphData23 = array_count_values(array_column($ReturnObj, $renderType2));
        $rkeyr2 =array_flip(array_keys($getGraphData23));        
        if(isset($ReturnObj) && !empty($ReturnObj)){
          foreach($ReturnObj as $key=>$valuec){
            if(isset($valuec['field_wo_estimated_time_1_value'],$valuec[$renderType2],$valuec[$renderType]) && !empty($valuec[$renderType2])&& !empty($valuec['field_wo_estimated_time_1_value']) && !empty($valuec[$renderType])){
              $arrData1[$valuec[$renderType2]] = _get_title_of_node($valuec[$renderType2]);
              foreach($rkeyr2 as $rnid2=>$rrkey){             
                if($valuec[$renderType2] == $rnid2){
                  $cgetPer3[$valuec[$renderType]]['name']= _get_title_of_node($valuec[$renderType]);
                  $cgetPer3[$valuec[$renderType]]['data'][$rrkey] += filter_var($valuec['field_wo_estimated_time_1_value'], FILTER_SANITIZE_NUMBER_INT);
                }else if(empty($cgetPer3[$valuec[$renderType]][$rnid2])){
                  $cgetPer3[$valuec[$renderType]]['name']= _get_title_of_node($valuec[$renderType]);
                  $cgetPer3[$valuec[$renderType]]['data'][$rrkey] = 0;
                }
              }
            }
          }
        }
        $laborforecastlabel = array_values($arrData1);
        $laborforecastdata = $cgetPer3  ;
        $DGrapLabel = $laborforecastlabel;
        $DGrapData = $cgetPer;
        $DGrapExtra = $laborforecastdata;
        $GraphData = array('glabel' =>$DGrapLabel,'gdata' =>$DGrapData,'gextra' => $DGrapExtra);
      }
    }
  }
  return $GraphData;
}
/////graph calculation end /////

/////callback start /////
function hcfmdashboard_asset_risk_callback($form,&$form_state){
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values,1);  
  $Ttype = 'asset';
  $Ttitle = 'Asset by Risk'; 
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_asset_risk_callback' && $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];  

    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_column_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_column_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = drupal_render($GraphDisplayRenderNormal);
    $DasColumnData1 = drupal_render($GraphDisplayRenderLarge);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
      db_merge('m6cocnnect_hcfm_dashboard_tiles')
      ->key(array('type' => 'asset', 'company' => $company->nid,'user'=>$user->uid))
      ->fields(array(
        'type' => 'asset',
        'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
        'user' => $user->uid,
        'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
        'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
        'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
        'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
        'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
        'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
        'timestamp' => time(),
      ))
      ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .asset-column-data-display", '<div class="asset-column-data-display">'.$DasColumnData.'</div>');      
    $commands[] = ajax_command_replace(".graph-large .asset-column-data-display", '<div class="asset-column-data-display">'.$DasColumnData1.'</div>');      
    $commands[] = ajax_command_invoke("a.unflip-btn022", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#assets .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
    
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_asset_risk_callback' && $form_state['triggering_element']['#value'] == 'Compare'){
    //pre($form_state['values']);
    $DasColumnData = '';
    $cDasColumnData = '';
    $CompareColumnData = '';
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];


    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
          $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);         
    $GraphDisplayRender1 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
    $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
    $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);

      if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => 'asset', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'asset',
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".asset-column-compare-data-display .pull-left", '<div class="asset-column-compare-data-display pull-left">'.$GraphDisplayRenderCompare1.'</div>');
      $commands[] = ajax_command_replace(".asset-column-compare-data-display .pull-right", '<div class="asset-column-compare-data-display pull-right">'.$GraphDisplayRenderCompare2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn022", 'trigger',array('click'));
    
  }  
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_open_pm_callback($form,&$form_state){//drup_msg($form_state['values']);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values);pre($form_state,1);
  //pre($form_state);
  $Ttype = 'work_orders_open_pm';
  $Ttitle = 'OPEN PMs';
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_open_pm_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
   // drup_msg('in con1');
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
  
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = $GraphDisplayRenderNormal;
    $DasColumnData1 = $GraphDisplayRenderLarge;
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'work_orders_open_pm', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'work_orders_open_pm',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .work_orders_open_pm-column-data-display", '<div class="work_orders_open_pm-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .work_orders_open_pm-column-data-display", '<div class="work_orders_open_pm-column-data-display">'.$DasColumnData1.'</div>');
    $commands[] = ajax_command_invoke("a.unflip-btn122", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#open_pms .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
  
  }  
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_open_pm_callback'&& $form_state['triggering_element']['#value'] =='Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];

    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
    
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL),  
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".work_orders_open_pm-column-compare-data-display .pull-left", '<div class="work_orders_open_pm-column-compare-data-display pull-left">'.$GraphDisplayRender1.'</div>');
      $commands[] = ajax_command_replace(".work_orders_open_pm-column-compare-data-display .pull-right", '<div class="work_orders_open_pm-column-compare-data-display pull-right">'.$GraphDisplayRender2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn122", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_open_cm_callback($form,&$form_state){//drup_msg($form_state);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values);pre($form_state,1);
  //pre($form_state);
  $Ttype = 'work_orders_open_cm';
  $Ttitle = 'OPEN CMs'; 
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_open_cm_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
  $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
    
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = $GraphDisplayRenderNormal;
    $DasColumnData1 = $GraphDisplayRenderLarge;  
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'work_orders_open_cm', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'work_orders_open_cm',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .work_orders_open_cm-column-data-display", '<div class="work_orders_open_cm-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .work_orders_open_cm-column-data-display", '<div class="work_orders_open_cm-column-data-display">'.$DasColumnData1.'</div>');
    $commands[] = ajax_command_invoke("a.unflip-btn222", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#open_cms .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
 
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_open_cm_callback'&& $form_state['triggering_element']['#value'] =='Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];

    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');      
    $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');      

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".work_orders_open_cm-column-compare-data-display .pull-left", '<div class="work_orders_open_cm-column-compare-data-display pull-left">'.$GraphDisplayRender1.'</div>');
      $commands[] = ajax_command_replace(".work_orders_open_cm-column-compare-data-display .pull-right", '<div class="work_orders_open_cm-column-compare-data-display pull-right">'.$GraphDisplayRender2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn222", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_open_projects_callback($form,&$form_state){//drup_msg($form_state);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                    //  drup_msg($values);         //pre($values);pre($form_state,1);
  //pre($form_state);
  $Ttype = 'work_orders_open_projects';
  $Ttitle = 'Open Projects';
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_open_projects_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
  
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);

    $GraphDisplayRenderNormal = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = $GraphDisplayRenderNormal;
    $DasColumnData1 = $GraphDisplayRenderLarge;
    
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'work_orders_open_projects', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'work_orders_open_projects',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .work_orders_open_projects-column-data-display", '<div class="work_orders_open_projects-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .work_orders_open_projects-column-data-display", '<div class="work_orders_open_projects-column-data-display">'.$DasColumnData1.'</div>');
    $commands[] = ajax_command_invoke("a.unflip-btn322", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#projects .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));

  }  
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_open_projects_callback'&& $form_state['triggering_element']['#value'] =='Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

    
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');      
    $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');      

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".work_orders_open_projects-column-compare-data-display .pull-left", '<div class="work_orders_open_projects-column-compare-data-display pull-left">'.$GraphDisplayRender1.'</div>');
      $commands[] = ajax_command_replace(".work_orders_open_projects-column-compare-data-display .pull-right", '<div class="work_orders_open_projects-column-compare-data-display pull-right">'.$GraphDisplayRender2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn322", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_work_orders_on_hold_callback($form,&$form_state){//drup_msg($form_state);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values);pre($form_state,1);
  //pre($form_state);
  $Ttype = 'work_orders_on_hold';
  $Ttitle = 'PARTS ON ORDER'; 
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_work_orders_on_hold_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
  $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
  
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_pie_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = $GraphDisplayRenderNormal;
    $DasColumnData1 = $GraphDisplayRenderLarge;   
      
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'work_orders_on_hold', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'work_orders_on_hold',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .work_orders_on_hold-column-data-display", '<div class="work_orders_on_hold-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .work_orders_on_hold-column-data-display", '<div class="work_orders_on_hold-column-data-display">'.$DasColumnData1.'</div>');
    $commands[] = ajax_command_invoke("a.unflip-btn422", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#parts_on_order .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
  
  }  
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_work_orders_on_hold_callback'&& $form_state['triggering_element']['#value'] =='Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];

    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
    $GraphDisplayRender1 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_pie_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".work_orders_on_hold-column-compare-data-display .pull-left", '<div class="work_orders_on_hold-column-compare-data-display pull-left">'.$GraphDisplayRender1.'</div>');
      $commands[] = ajax_command_replace(".work_orders_on_hold-column-compare-data-display .pull-right", '<div class="work_orders_on_hold-column-compare-data-display pull-right">'.$GraphDisplayRender2.'</div>');      
     // $commands[] = ajax_command_invoke("a.tile-expand-compareback-btn", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_past_due_work_orders_callback($form,&$form_state){//drup_msg($form_state);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values);
  //pre($form_state);
  $Ttype = 'past_due_work_orders';
  $Ttitle = 'BACK LOG'; 
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_past_due_work_orders_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
    //$ByWotype = $values['dash_by_work_order_type'];

    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = drupal_render($GraphDisplayRenderNormal);
    $DasColumnData1 = drupal_render($GraphDisplayRenderLarge);

        
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'past_due_work_orders', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'past_due_work_orders',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL),
      'bytype' => (isset($ByWotype) && !empty($ByWotype)?serialize($ByWotype):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace("graph-normal .past_due_work_orders-column-data-display", '<div class="past_due_work_orders-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .past_due_work_orders-column-data-display", '<div class="past_due_work_orders-column-data-display">'.$DasColumnData1.'</div>');
    
    $commands[] = ajax_command_invoke("a.unflip-btn522", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#back_log .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
 
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_past_due_work_orders_callback'&& $form_state['triggering_element']['#value'] == 'Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];
    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

   
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_bar_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
    $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
    $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".past_due_work_orders-column-compare-data-display .pull-left", '<div class="past_due_work_orders-column-compare-data-display pull-left">'.$GraphDisplayRenderCompare1.'</div>');
      $commands[] = ajax_command_replace(".past_due_work_orders-column-compare-data-display .pull-right", '<div class="past_due_work_orders-column-compare-data-display pull-right">'.$GraphDisplayRenderCompare2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn522", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_work_order_ratio_callback($form,&$form_state){//drup_msg($form_state);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values);pre($form_state,1);
  //pre($form_state);
  $Ttype = 'work_order_ratio';
  $Ttitle = 'WORK ORDER FOCUS';
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_work_order_ratio_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
  $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $WoTypeId= $values['dash_work_order_type_list'];
    $FilterId= $values['dash_asset_filter_list'];
  
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_pyramid_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_pyramid_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = $GraphDisplayRenderNormal;
    $DasColumnData1 = $GraphDisplayRenderLarge;

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'work_order_ratio', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'work_order_ratio',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL),
      'riskrank' => (isset($RiskrankId) && !empty($RiskrankId)?serialize($RiskrankId):NULL),
      'wo_type' => (isset($WoTypeId) && !empty($WoTypeId)?serialize($WoTypeId):NULL),  
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .work_order_ratio-column-data-display", '<div class="work_order_ratio-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .work_order_ratio-column-data-display", '<div class="work_order_ratio-column-data-display">'.$DasColumnData1.'</div>');
    $commands[] = ajax_command_invoke("a.unflip-btn622", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#work_order_focus .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
  
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_work_order_ratio_callback'&& $form_state['triggering_element']['#value'] =='Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_pyramid_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],0,$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_pyramid_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],0,$Ttype,$Ttitle.$subtitleB,'compare');

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".work_order_ratio-column-compare-data-display .pull-left", '<div class="work_order_ratio-column-compare-data-display pull-left">'.$GraphDisplayRender1.'</div>');
      $commands[] = ajax_command_replace(".work_order_ratio-column-compare-data-display .pull-right", '<div class="work_order_ratio-column-compare-data-display pull-right">'.$GraphDisplayRender2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn622", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_back_square_foot_callback($form,&$form_state){//drup_msg($form_state);
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values);pre($form_state,1);
  //pre($form_state);
  $Ttype = 'square_foot';
  $Ttitle = 'Square Foot';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_square_foot_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
   $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];    
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
    $ByWotype = $values['dash_by_work_order_type'];

    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = $GraphDisplayRenderNormal;
    $DasColumnData1 = $GraphDisplayRenderLarge;

    //drup_msg($DasColumnData);
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
    db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'square_foot', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'square_foot',
      'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
      'user' => $user->uid,
      'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
      'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
      'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
      'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
      'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
      'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL),
      'bytype' => (isset($ByWotype) && !empty($ByWotype)?serialize($ByWotype):NULL), 
      'timestamp' => time(),
    ))
    ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .square_foot-column-data-display", '<div class="square_foot-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .square_foot-column-data-display", '<div class="square_foot-column-data-display">'.$DasColumnData1.'</div>');
    
    $commands[] = ajax_command_invoke("a.unflip-btn722", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#square_foot .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
  
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_back_square_foot_callback'&& $form_state['triggering_element']['#value'] =='Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');

    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],0,$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_pie_column_stacking_data_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],0,$Ttype,$Ttitle.$subtitleB,'compare');

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".square_foot-column-compare-data-display .pull-left", '<div class="square_foot-column-compare-data-display pull-left">'.$GraphDisplayRender1.'</div>');
      $commands[] = ajax_command_replace(".square_foot-column-compare-data-display .pull-right", '<div class="square_foot-column-compare-data-display pull-right">'.$GraphDisplayRender2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn722", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_available_labor_callback($form,&$form_state){
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values,1);//pre($form_state,1);
  //pre($form_state);
  $Ttype = 'available_labor'; 
  $Ttitle = 'Available Labor';  
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_available_labor_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
   

    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_synchronized_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_synchronized_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = drupal_render($GraphDisplayRenderNormal);
    $DasColumnData1 = drupal_render($GraphDisplayRenderLarge);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
      db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'available_labor', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'available_labor',
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
          'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
          'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
          'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
          'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
          'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
          'timestamp' => time(),
      ))
      ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .available-labor-column-data-display", '<div class="available-labor-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .available-labor-column-data-display", '<div class="available-labor-column-data-display">'.$DasColumnData1.'</div>');
    
    $commands[] = ajax_command_invoke("a.unflip-btn822", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#labor .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
    
  }  
   if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_available_labor_callback'&& $form_state['triggering_element']['#value'] == 'Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?$BsubTitle:'');
   
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_synchronized_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_synchronized_inc('',$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
    $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
    $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".available-labor-column-compare-data-display .pull-left", '<div class="pull-left"><div style="text-align: center;font-size:16px;font-weight: 600;" class="margin-top-10"><div class="clearfix" style="line-height: 12px;">'.$Ttitle.'</div><div style="font-size: 13px;text-transform: uppercase;" class="clearfix">'.$subtitleA.'</div></div>'.$GraphDisplayRenderCompare1.'</div>');
      $commands[] = ajax_command_replace(".available-labor-column-compare-data-display .pull-right", '<div class="pull-right"><div style="text-align: center;font-size:16px;font-weight: 600;" class="margin-top-10"><div class="clearfix" style="line-height: 12px;">'.$Ttitle.'</div><div style="font-size: 13px;text-transform: uppercase;" class="clearfix">'.$subtitleB.'</div></div>'.$GraphDisplayRenderCompare2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn822", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_fte_square_foot_callback($form,&$form_state){
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values,1);//pre($form_state,1);
  //pre($form_state);
  $Ttitle = 'Square Foot / FTE'; 
  $Ttype = 'fte_square_foot';
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_fte_square_foot_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
    
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_gauge_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_gauge_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = drupal_render($GraphDisplayRenderNormal);
    $DasColumnData1 = drupal_render($GraphDisplayRenderLarge);

        
    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
      db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'fte_square_foot', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'fte_square_foot',
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
          'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
          'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
          'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
          'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
          'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
          'timestamp' => time(),
      ))
      ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .fte-square-foot-column-data-display", '<div class="fte-square-foot-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .fte-square-foot-column-data-display", '<div class="fte-square-foot-column-data-display">'.$DasColumnData1.'</div>');
    
    $commands[] = ajax_command_invoke("a.unflip-btn922", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#labor_sf .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
   
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_fte_square_foot_callback'&& $form_state['triggering_element']['#value'] == 'Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
    
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_gauge_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_gauge_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
    $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
    $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".fte-square-foot-column-compare-data-display .pull-left", '<div class="fte-square-foot-column-compare-data-display pull-left">'.$GraphDisplayRenderCompare1.'</div>');
      $commands[] = ajax_command_replace(".fte-square-foot-column-compare-data-display .pull-right", '<div class="fte-square-foot-column-compare-data-display pull-right">'.$GraphDisplayRenderCompare2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn922", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_labor_use_rate_callback($form,&$form_state){
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values,1);//pre($form_state,1);
  //pre($form_state);
  $Ttitle = 'Labor Use Rate'; 
  $Ttype = 'labor_use_rate';
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_labor_use_rate_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_column_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_column_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = drupal_render($GraphDisplayRenderNormal);
    $DasColumnData1 = drupal_render($GraphDisplayRenderLarge);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
      db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'labor_use_rate', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'labor_use_rate',
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
          'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
          'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
          'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
          'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
          'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
          'timestamp' => time(),
      ))
      ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .labor-use-rate-column-data-display", '<div class="labor-use-rate-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .labor-use-rate-column-data-display", '<div class="labor-use-rate-column-data-display">'.$DasColumnData1.'</div>');
    
    $commands[] = ajax_command_invoke("a.unflip-btn1022", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#labor_use .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
    
  }
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_labor_use_rate_callback'&& $form_state['triggering_element']['#value'] == 'Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
   
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
    $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
    $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".labor-use-rate-column-compare-data-display .pull-left", '<div class="labor-use-rate-column-compare-data-display pull-left">'.$GraphDisplayRenderCompare1.'</div>');
      $commands[] = ajax_command_replace(".labor-use-rate-column-compare-data-display .pull-right", '<div class="labor-use-rate-column-compare-data-display pull-right">'.$GraphDisplayRenderCompare2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn1022", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfmdashboard_labor_forecast_callback($form,&$form_state){
  global $user, $company;
  $commands = array();
  $values = $form_state['values'];                               //pre($values,1);//pre($form_state,1);
  //pre($form_state);
  $Ttype ='labor_forecast';
  $Ttitle = 'Labor Forecast';
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_labor_forecast_callback'&& $form_state['triggering_element']['#value'] == 'Submit'){
    $RegionId= $values['dash_asset_region_list'];
    $SiteId= $values['dash_asset_site_list'];
    $FacilityId= $values['dash_asset_facility_list'];
    $ZoneId= $values['dash_asset_zone_list'];
    $StatusId= $values['dash_asset_status_list'];
    $RiskrankId= $values['dash_asset_riskrank_list'];
    $FilterId= $values['dash_asset_filter_list'];
    
    $Gobject = array('region'=>$RegionId,'site'=>$SiteId,'facility'=>$FacilityId,'zone'=>$ZoneId,'status'=>$StatusId,'riskrank'=>$RiskrankId,'filter'=>$FilterId);          
    $graphrenderdata = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$Gobject,$Gtitle,$Gstate);
    $GraphDisplayRenderNormal = _hcfm_chart_intigration_column_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle);
    $GraphDisplayRenderLarge = _hcfm_chart_intigration_column_stacking_inc($graphrenderdata['gdata'],$graphrenderdata['glabel'],$graphrenderdata['gextra'],$Ttype,$Ttitle,'large');
    $DasColumnData = drupal_render($GraphDisplayRenderNormal);
    $DasColumnData1 = drupal_render($GraphDisplayRenderLarge);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles')){    
      db_merge('m6cocnnect_hcfm_dashboard_tiles')
        ->key(array('type' => 'labor_forecast', 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => 'labor_forecast',
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'region' => (isset($RegionId) && !empty($RegionId)?serialize($RegionId):NULL),     
          'site' => (isset($SiteId) && !empty($SiteId)?serialize($SiteId):NULL), 
          'facility' => (isset($FacilityId) && !empty($FacilityId)?serialize($FacilityId):NULL), 
          'zone' => (isset($ZoneId) && !empty($ZoneId)?serialize($ZoneId):NULL), 
          'status' => (isset($StatusId) && !empty($StatusId)?serialize($StatusId):NULL), 
          'filter' => (isset($FilterId) && !empty($FilterId)?serialize($FilterId):NULL), 
          'timestamp' => time(),
      ))
      ->execute();    
    }
    $commands[] = ajax_command_replace(".graph-normal .labor-forecast-column-data-display", '<div class="labor-forecast-column-data-display">'.$DasColumnData.'</div>');
    $commands[] = ajax_command_replace(".graph-large .labor-forecast-column-data-display", '<div class="labor-forecast-column-data-display">'.$DasColumnData1.'</div>');
    
    $commands[] = ajax_command_invoke("a.unflip-btn1122", 'trigger',array('click'));
    $commands[] = ajax_command_invoke("#labor_forecast .tile-expand-mlsetting-btn", 'attr',array('tile-show','front'));
    
  }  
  if(isset($form_state['triggering_element']['#ajax']['callback']) && $form_state['triggering_element']['#ajax']['callback'] == 'hcfmdashboard_labor_forecast_callback'&& $form_state['triggering_element']['#value'] == 'Compare'){
    $ARegionId = $values['adash_asset_region_list'];
    $ASiteId = $values['adash_asset_site_list'];
    $AFacilityId = $values['adash_asset_facility_list'];
    $AZoneId = $values['adash_asset_zone_list'];
    $AStatusId = $values['adash_asset_status_list'];
    $ARiskrankId = $values['adash_asset_riskrank_list'];
    $AFilterId = $values['adash_asset_filter_list'];

    $BRegionId = $values['bdash_asset_region_list'];
    $BSiteId = $values['bdash_asset_site_list'];
    $BFacilityId = $values['bdash_asset_facility_list'];
    $BZoneId = $values['bdash_asset_zone_list'];
    $BStatusId = $values['bdash_asset_status_list'];
    $BRiskrankId = $values['bdash_asset_riskrank_list'];
    $BFilterId = $values['bdash_asset_filter_list'];
    $AsubTitle = $values['adash_asset_subtitle_a'];
    $BsubTitle = $values['bdash_asset_subtitle_b'];
    $subtitleA = (isset($AsubTitle) && !empty($AsubTitle)?'<br>'.$AsubTitle:'');
    $subtitleB = (isset($BsubTitle) && !empty($BsubTitle)?'<br>'.$BsubTitle:'');
    
    $GobjectA = array('region'=>$ARegionId,'site'=>$ASiteId,'facility'=>$AFacilityId,'zone'=>$AZoneId,'status'=>$AStatusId,'riskrank'=>$ARiskrankId,'filter'=>$AFilterId);
    $GobjectB = array('region'=>$BRegionId,'site'=>$BSiteId,'facility'=>$BFacilityId,'zone'=>$BZoneId,'status'=>$BStatusId,'riskrank'=>$BRiskrankId,'filter'=>$BFilterId);
    $graphrenderdatacompareA = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectA,$Gtitle,$Gstate);
    $graphrenderdatacompareB = hcmf_dashboard_graphdata($user->uid,$company->nid,$Ttype,$GobjectB,$Gtitle,$Gstate);

    $GraphDisplayRender1 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareA['gdata'],$graphrenderdatacompareA['glabel'],$graphrenderdatacompareA['gextra'],$Ttype,$Ttitle.$subtitleA,'compare');
    $GraphDisplayRender2 = _hcfm_chart_intigration_column_stacking_inc($graphrenderdatacompareB['gdata'],$graphrenderdatacompareB['glabel'],$graphrenderdatacompareB['gextra'],$Ttype,$Ttitle.$subtitleB,'compare');
    $GraphDisplayRenderCompare1 = drupal_render($GraphDisplayRender1);
    $GraphDisplayRenderCompare2 = drupal_render($GraphDisplayRender2);

    if (db_table_exists('m6cocnnect_hcfm_dashboard_tiles_compare')){    
        db_merge('m6cocnnect_hcfm_dashboard_tiles_compare')
        ->key(array('type' => $Ttype, 'company' => $company->nid,'user'=>$user->uid))
        ->fields(array(
          'type' => $Ttype,
          'company' => (isset($company,$company->nid) && !empty($company->nid)?$company->nid:'none'),
          'user' => $user->uid,
          'subtitle_compare_a' => (isset($AsubTitle) && !empty($AsubTitle)?serialize($AsubTitle):NULL),
          'region_compare_a' => (isset($values['adash_asset_region_list']) && !empty($values['adash_asset_region_list'])?serialize($values['adash_asset_region_list']):NULL),
          'site_compare_a' => (isset($values['adash_asset_site_list']) && !empty($values['adash_asset_site_list'])?serialize($values['adash_asset_site_list']):NULL), 
          'facility_compare_a' => (isset($values['adash_asset_facility_list']) && !empty($values['adash_asset_facility_list'])?serialize($values['adash_asset_facility_list']):NULL), 
          'zone_compare_a' => (isset($AZoneId) && !empty($AZoneId)?serialize($AZoneId):NULL), 
          'status_compare_a' => (isset($AStatusId) && !empty($AStatusId)?serialize($AStatusId):NULL), 
          'filter_compare_a' => (isset($AFilterId) && !empty($AFilterId)?serialize($AFilterId):NULL), 
          'subtitle_compare_b' => (isset($BsubTitle) && !empty($BsubTitle)?serialize($BsubTitle):NULL),
          'region_compare_b' => (isset($values['bdash_asset_region_list']) && !empty($values['bdash_asset_region_list'])?serialize($values['bdash_asset_region_list']):NULL),
          'site_compare_b' => (isset($values['bdash_asset_site_list']) && !empty($values['bdash_asset_site_list'])?serialize($values['bdash_asset_site_list']):NULL), 
          'facility_compare_b' => (isset($values['bdash_asset_facility_list']) && !empty($values['bdash_asset_facility_list'])?serialize($values['bdash_asset_facility_list']):NULL), 
          'zone_compare_b' => (isset($BZoneId) && !empty($BZoneId)?serialize($BZoneId):NULL), 
          'status_compare_b' => (isset($BStatusId) && !empty($BStatusId)?serialize($BStatusId):NULL), 
          'filter_compare_b' => (isset($BFilterId) && !empty($BFilterId)?serialize($BFilterId):NULL), 
          'timestamp' => time(),
        ))
        ->execute();    
      }


      $commands[] = ajax_command_replace(".labor-forecast-column-compare-data-display .pull-left", '<div class="labor-forecast-column-compare-data-display pull-left">'.$GraphDisplayRenderCompare1.'</div>');
      $commands[] = ajax_command_replace(".labor-forecast-column-compare-data-display .pull-right", '<div class="labor-forecast-column-compare-data-display pull-right">'.$GraphDisplayRenderCompare2.'</div>');      
      //$commands[] = ajax_command_invoke("a.unflip-btn1122", 'trigger',array('click'));

  }
  return array('#type' => 'ajax','#commands' => $commands); 
}

function hcfm_dash_compare_callback($Action,$Object,$ajax=NULL){ //pre($Action);pre($Object);pre($ajax,1);
  global $user,$base_url,$base_path;  
  ctools_include('ajax');
  $commands = array();  
  if (isset($Action,$Object) && !empty($Action) && !empty($Object) && $ajax == TRUE) {    
    if ($Action == 'TileA') {
      if($Object =='normal'){
        $TileA = hcfm_dash_tile_data_callback('a','front','normal');
      }
      if($Object =='large'){
        $TileA = hcfm_dash_tile_data_callback('a','front','large');
      }
      //$TileA = drupal_get_form('hcfm_dashboard_asset_risk_form','compare');
      
      
      $commands[] = ajax_command_html("#assets .thumbnail .desh-sec-b .front", render($TileA));
    }
  }
  
  print ajax_render($commands);
  exit;
}
/////callback end /////

/////process1 start /////
function hcfmdashboard_asset_risk_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','asset','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/


  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }  
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list',
      

    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['region']) && !empty($TableResult['asset']['region'])?unserialize($TableResult['asset']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );

  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['site']) && !empty($TableResult['asset']['site'])?unserialize($TableResult['asset']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['facility']) && !empty($TableResult['asset']['facility'])?unserialize($TableResult['asset']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['zone']) && !empty($TableResult['asset']['zone'])?unserialize($TableResult['asset']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'hcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status']) && !empty($TableResult['asset']['status'])?unserialize($TableResult['asset']['status']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list',
    )
  ),  
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#options' => $fm_risk_rank,    
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['riskrank']) && !empty($TableResult['asset']['riskrank'])?unserialize($TableResult['asset']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div></div>',
  );
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,
  '#multiple'     => TRUE,
  '#default_value' => (isset($TableResult['asset']['filter']) && !empty($TableResult['asset']['filter'])?unserialize($TableResult['asset']['filter']):''),
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_asset_risk_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_assets',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix "><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_open_pm_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','work_orders_open_pm','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/

  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['region']) && !empty($TableResult['work_orders_open_pm']['region'])?unserialize($TableResult['work_orders_open_pm']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['site']) && !empty($TableResult['work_orders_open_pm']['site'])?unserialize($TableResult['work_orders_open_pm']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['facility']) && !empty($TableResult['work_orders_open_pm']['facility'])?unserialize($TableResult['work_orders_open_pm']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['zone']) && !empty($TableResult['work_orders_open_pm']['zone'])?unserialize($TableResult['work_orders_open_pm']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );

  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['riskrank']) && !empty($TableResult['work_orders_open_pm']['riskrank'])?unserialize($TableResult['work_orders_open_pm']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //'#suffix' => '</div>',
  );
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['filter']) && !empty($TableResult['work_orders_open_pm']['filter'])?unserialize($TableResult['work_orders_open_pm']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class=" padding-5">', 
  //'#suffix' => '</div></div>',   
  );
  $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
      'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_pm']['status']) && !empty($TableResult['work_orders_open_pm']['status'])?unserialize($TableResult['work_orders_open_pm']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //'#suffix' => '</div></div>',
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_open_pm_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#validate' => TRUE,
  '#name' => 'hcfm_dashboard_ml_open_pms',
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_open_cm_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','work_orders_open_cm','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['region']) && !empty($TableResult['work_orders_open_cm']['region'])?unserialize($TableResult['work_orders_open_cm']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['site']) && !empty($TableResult['work_orders_open_cm']['site'])?unserialize($TableResult['work_orders_open_cm']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['facility']) && !empty($TableResult['work_orders_open_cm']['facility'])?unserialize($TableResult['work_orders_open_cm']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['zone']) && !empty($TableResult['work_orders_open_cm']['zone'])?unserialize($TableResult['work_orders_open_cm']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['riskrank']) && !empty($TableResult['work_orders_open_cm']['riskrank'])?unserialize($TableResult['work_orders_open_cm']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //'#suffix' => '</div>',
  );
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['filter']) && !empty($TableResult['work_orders_open_cm']['filter'])?unserialize($TableResult['work_orders_open_cm']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class=" padding-5">', 
  //'#suffix' => '</div></div>',   
  );
  $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
      'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_cm']['status']) && !empty($TableResult['work_orders_open_cm']['status'])?unserialize($TableResult['work_orders_open_cm']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //'#suffix' => '</div></div>',
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_open_cm_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_open_cms',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_open_projects_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','work_orders_open_projects','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
    'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['region']) && !empty($TableResult['work_orders_open_projects']['region'])?unserialize($TableResult['work_orders_open_projects']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
    'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['site']) && !empty($TableResult['work_orders_open_projects']['site'])?unserialize($TableResult['work_orders_open_projects']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
    'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['facility']) && !empty($TableResult['work_orders_open_projects']['facility'])?unserialize($TableResult['work_orders_open_projects']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
    'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['zone']) && !empty($TableResult['work_orders_open_projects']['zone'])?unserialize($TableResult['work_orders_open_projects']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
    'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['riskrank']) && !empty($TableResult['work_orders_open_projects']['riskrank'])?unserialize($TableResult['work_orders_open_projects']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div>',
  );
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
    'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['filter']) && !empty($TableResult['work_orders_open_projects']['filter'])?unserialize($TableResult['work_orders_open_projects']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
    'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_open_projects']['status']) && !empty($TableResult['work_orders_open_projects']['status'])?unserialize($TableResult['work_orders_open_projects']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //  '#suffix' => '</div></div>',
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_open_projects_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_projects',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_work_orders_on_hold_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','work_orders_on_hold','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
    'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['region']) && !empty($TableResult['work_orders_on_hold']['region'])?unserialize($TableResult['work_orders_on_hold']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
    'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['site']) && !empty($TableResult['work_orders_on_hold']['site'])?unserialize($TableResult['work_orders_on_hold']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
    'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['facility']) && !empty($TableResult['work_orders_on_hold']['facility'])?unserialize($TableResult['work_orders_on_hold']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
    'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['zone']) && !empty($TableResult['work_orders_on_hold']['zone'])?unserialize($TableResult['work_orders_on_hold']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );

  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
    'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['riskrank']) && !empty($TableResult['work_orders_on_hold']['riskrank'])?unserialize($TableResult['work_orders_on_hold']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div>',
  );
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
    'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['filter']) && !empty($TableResult['work_orders_on_hold']['filter'])?unserialize($TableResult['work_orders_on_hold']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
    $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
    'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_orders_on_hold']['status']) && !empty($TableResult['work_orders_on_hold']['status'])?unserialize($TableResult['work_orders_on_hold']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
   // '#suffix' => '</div></div>',
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_work_orders_on_hold_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_parts_on_order',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_past_due_work_orders_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','past_due_work_orders','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
    'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['region']) && !empty($TableResult['past_due_work_orders']['region'])?unserialize($TableResult['past_due_work_orders']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
    'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['site']) && !empty($TableResult['past_due_work_orders']['site'])?unserialize($TableResult['past_due_work_orders']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
    'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility_selectAll+$asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['facility']) && !empty($TableResult['past_due_work_orders']['facility'])?unserialize($TableResult['past_due_work_orders']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
    'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['zone']) && !empty($TableResult['past_due_work_orders']['zone'])?unserialize($TableResult['past_due_work_orders']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
    'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['status']) && !empty($TableResult['past_due_work_orders']['status'])?unserialize($TableResult['past_due_work_orders']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div>',
  );
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
    'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['riskrank']) && !empty($TableResult['past_due_work_orders']['riskrank'])?unserialize($TableResult['past_due_work_orders']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div></div>',
  );
  
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
    'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['filter']) && !empty($TableResult['past_due_work_orders']['filter'])?unserialize($TableResult['past_due_work_orders']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  /*$by_work_order_type = array('fm_location_region'=>'Region','fm_location_site'=>'Site','fm_facility'=>'Facility','fm_location_location'=>'Zone');
  $element['dash_by_work_order_type'] = array( 
    '#title' => t('By Work Order Type'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
    'dash_by_work_order_type'
    )
  ), 
  '#type' => 'select',
  '#options' => $by_work_order_type,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['past_due_work_orders']['bytype']) && !empty($TableResult['past_due_work_orders']['bytype'])?unserialize($TableResult['past_due_work_orders']['bytype']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //'#suffix' => '</div></div>',   
  );*/
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_past_due_work_orders_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_back_log',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_work_order_ratio_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','work_order_ratio','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
    'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['region']) && !empty($TableResult['work_order_ratio']['region'])?unserialize($TableResult['work_order_ratio']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
    'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['site']) && !empty($TableResult['work_order_ratio']['site'])?unserialize($TableResult['work_order_ratio']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['facility']) && !empty($TableResult['work_order_ratio']['facility'])?unserialize($TableResult['work_order_ratio']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div></div>',
  );
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
    'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['zone']) && !empty($TableResult['work_order_ratio']['zone'])?unserialize($TableResult['work_order_ratio']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
    'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['status']) && !empty($TableResult['work_order_ratio']['status'])?unserialize($TableResult['work_order_ratio']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div>',
  );
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
    'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['riskrank']) && !empty($TableResult['work_order_ratio']['riskrank'])?unserialize($TableResult['work_order_ratio']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
   // '#suffix' => '</div></div>',
  );
 /* $fm_work_order_type = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_type');
  $element['dash_work_order_type_list'] = array(
    '#title' => t('Select Type'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
    'dash_work_order_type_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_type,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['wo_type']) && !empty($TableResult['work_order_ratio']['wo_type'])?unserialize($TableResult['work_order_ratio']['wo_type']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //  '#suffix' => '</div>',
  );*/
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
    'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['work_order_ratio']['filter']) && !empty($TableResult['work_order_ratio']['filter'])?unserialize($TableResult['work_order_ratio']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
 // '#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_work_order_ratio_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_work_order_focus',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_square_foot_process($element, &$form_state){{
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','square_foot','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
    'dash_asset_region_list'
    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['region']) && !empty($TableResult['square_foot']['region'])?unserialize($TableResult['square_foot']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
 // '#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
    'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['site']) && !empty($TableResult['square_foot']['site'])?unserialize($TableResult['square_foot']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
    'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['facility']) && !empty($TableResult['square_foot']['facility'])?unserialize($TableResult['square_foot']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class=" padding-5">',
  //'#suffix' => '</div></div>',
  );
  /*$location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
    'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['zone']) && !empty($TableResult['square_foot']['zone'])?unserialize($TableResult['square_foot']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="row margin-5"><div class=" padding-5">',
  '#suffix' => '</div>',
  );*/
  $fm_work_order_status = hcfm_nodenid_nodetitle_by_node_type('fm_work_order_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-status-list',
    'dash_asset_status_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_work_order_status,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['status']) && !empty($TableResult['square_foot']['status'])?unserialize($TableResult['square_foot']['status']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
  //  '#suffix' => '</div>',
  );
  /*
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
    'dash_asset_riskrank_list'
    )
  ),  
  '#type' => 'select',
  '#options' => $fm_risk_rank,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['riskrank']) && !empty($TableResult['square_foot']['riskrank'])?unserialize($TableResult['square_foot']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class=" padding-5">', 
   // '#suffix' => '</div></div>',
  );
  */
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
    'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['filter']) && !empty($TableResult['square_foot']['filter'])?unserialize($TableResult['square_foot']['filter']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
   // '#suffix' => '</div></div>',   
  );
  /*$by_work_order_type = array('fm_location_region'=>'Region','fm_location_site'=>'Site','fm_facility'=>'Facility','fm_location_location'=>'Zone');
  $element['dash_by_work_order_type'] = array( 
    '#title' => t('By Type'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
    'dash_by_work_order_type'
    )
  ), 
  '#type' => 'select',
  '#options' => $by_work_order_type,    
  //'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['square_foot']['bytype']) && !empty($TableResult['square_foot']['bytype'])?unserialize($TableResult['square_foot']['bytype']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class=" padding-5">', 
  //'#suffix' => '</div></div>',   
  );*/
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_square_foot_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_square_foot',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix"><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}}

function hcfmdashboard_available_labor_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','available_labor','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);  
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list',

    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['available_labor']['region']) && !empty($TableResult['available_labor']['region'])?unserialize($TableResult['available_labor']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['available_labor']['site']) && !empty($TableResult['available_labor']['site'])?unserialize($TableResult['available_labor']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['available_labor']['facility']) && !empty($TableResult['available_labor']['facility'])?unserialize($TableResult['available_labor']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div></div>',
  );
  /*$location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['zone']) && !empty($TableResult['asset']['zone'])?unserialize($TableResult['asset']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );*/
 /* $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'hcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status']) && !empty($TableResult['asset']['status'])?unserialize($TableResult['asset']['status']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );*/
  /*$fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list',
    )
  ),  
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#options' => $fm_risk_rank,    
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['riskrank']) && !empty($TableResult['asset']['riskrank'])?unserialize($TableResult['asset']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div></div>',
  );*/
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,
  '#multiple'     => TRUE,
  '#default_value' => (isset($TableResult['available_labor']['filter']) && !empty($TableResult['available_labor']['filter'])?unserialize($TableResult['available_labor']['filter']):''),
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_available_labor_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_labor',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix "><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_fte_square_foot_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','fte_square_foot','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);  
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list',

    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['fte_square_foot']['region']) && !empty($TableResult['fte_square_foot']['region'])?unserialize($TableResult['fte_square_foot']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['fte_square_foot']['site']) && !empty($TableResult['fte_square_foot']['site'])?unserialize($TableResult['fte_square_foot']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['fte_square_foot']['facility']) && !empty($TableResult['fte_square_foot']['facility'])?unserialize($TableResult['fte_square_foot']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div></div>',
  );
  /*$location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['zone']) && !empty($TableResult['asset']['zone'])?unserialize($TableResult['asset']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );*/
 /* $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'hcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status']) && !empty($TableResult['asset']['status'])?unserialize($TableResult['asset']['status']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );*/
  /*$fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list',
    )
  ),  
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#options' => $fm_risk_rank,    
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['riskrank']) && !empty($TableResult['asset']['riskrank'])?unserialize($TableResult['asset']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div></div>',
  );*/
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,
  '#multiple'     => TRUE,
  '#default_value' => (isset($TableResult['fte_square_foot']['filter']) && !empty($TableResult['fte_square_foot']['filter'])?unserialize($TableResult['fte_square_foot']['filter']):''),
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_fte_square_foot_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_labor_sf',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix "><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_labor_use_rate_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','labor_use_rate','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);  
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list',

    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['labor_use_rate']['region']) && !empty($TableResult['labor_use_rate']['region'])?unserialize($TableResult['labor_use_rate']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['labor_use_rate']['site']) && !empty($TableResult['labor_use_rate']['site'])?unserialize($TableResult['labor_use_rate']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['labor_use_rate']['facility']) && !empty($TableResult['labor_use_rate']['facility'])?unserialize($TableResult['labor_use_rate']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div></div>',
  );
  /*$location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['zone']) && !empty($TableResult['asset']['zone'])?unserialize($TableResult['asset']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );*/
 /* $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'hcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status']) && !empty($TableResult['asset']['status'])?unserialize($TableResult['asset']['status']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );*/
  /*$fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list',
    )
  ),  
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#options' => $fm_risk_rank,    
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['riskrank']) && !empty($TableResult['asset']['riskrank'])?unserialize($TableResult['asset']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div></div>',
  );*/
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,
  '#multiple'     => TRUE,
  '#default_value' => (isset($TableResult['labor_use_rate']['filter']) && !empty($TableResult['labor_use_rate']['filter'])?unserialize($TableResult['labor_use_rate']['filter']):''),
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_labor_use_rate_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_labor_use',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix "><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_labor_forecast_process($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','labor_forecast','=');
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);  
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
   $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $element['dash_asset_region_list'] = array(
  '#title' => t('Select Region'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-region-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-region-list',
      'dash_asset_region_list',

    )
  ),
  '#type' => 'select',
  '#options' => $asset_region_selectAll+$asset_region,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['labor_forecast']['region']) && !empty($TableResult['labor_forecast']['region'])?unserialize($TableResult['labor_forecast']['region']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
    $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $element['dash_asset_site_list'] = array(
  '#title' => t('Select Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-site-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-site-list',
      'dash_asset_site_list'
    )
  ),
  '#options' => $location_site_selectAll+$location_site,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['labor_forecast']['site']) && !empty($TableResult['labor_forecast']['site'])?unserialize($TableResult['labor_forecast']['site']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div>',
  
  );
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
    $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $element['dash_asset_facility_list'] = array(
  '#title' => t('Select Facility '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-facility-d',
      'hcfm-normal-selectallfield',
      'hcfmdash-facility-list',
      'dash_asset_facility_list'
    )
  ),
  '#options' => $asset_facility,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['labor_forecast']['facility']) && !empty($TableResult['labor_forecast']['facility'])?unserialize($TableResult['labor_forecast']['facility']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="padding-5">',
  //'#suffix' => '</div></div>',
  );
  /*$location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $element['dash_asset_zone_list'] = array(
  '#title' => t('Select Zone '),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'as-asset-location',
      'hcfmdash-zone-list',
      'dash_asset_zone_list'
    )
  ),
  '#options' => $location_location,
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['zone']) && !empty($TableResult['asset']['zone'])?unserialize($TableResult['asset']['zone']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
  //'#suffix' => '</div>',
  );*/
 /* $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $element['dash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'hcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status']) && !empty($TableResult['asset']['status'])?unserialize($TableResult['asset']['status']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );*/
  /*$fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $element['dash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-riskrank-list',
      'dash_asset_riskrank_list',
    )
  ),  
  '#type' => 'select',
  '#multiple'     => TRUE,
  '#options' => $fm_risk_rank,    
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#default_value' => (isset($TableResult['asset']['riskrank']) && !empty($TableResult['asset']['riskrank'])?unserialize($TableResult['asset']['riskrank']):''),
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div></div>',
  );*/
  
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  $element['dash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
    'class'=> array(
      'clear-data',
      'hcfmdash-filter-list',
      'dash_asset_filter_list'
    )
  ), 
  '#type' => 'select',
  '#options' => $DashboardFilter,
  '#multiple'     => TRUE,
  '#default_value' => (isset($TableResult['labor_forecast']['filter']) && !empty($TableResult['labor_forecast']['filter'])?unserialize($TableResult['labor_forecast']['filter']):''),
  ////'#attributes'=> array('class'=> array('form-control')),
  '#empty_option' => 'None',
  '#select2' => array(
    'width' => '150',
    'minimumResultsForSearch' => '1',
  ),
  '#multiple'     => TRUE,
  //'#default_value' => 'this_month',
  //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
  //  '#suffix' => '</div></div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_labor_forecast_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_ml_labor_forecast',
  '#validate' => TRUE,
  '#value' => t('Submit'),
  '#prefix' => '</div><div class="clearfix "><div class="form-item"><label>&nbsp;</label><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}
/////process1 end /////

/////process2 start /////
function hcfmdashboard_asset_risk_process2($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','asset','=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult['asset']['subtitle_compare_a']) && !empty($TableResult['asset']['subtitle_compare_a'])?unserialize($TableResult['asset']['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );  
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['region_compare_a']) && !empty($TableResult['asset']['region_compare_a'])?unserialize($TableResult['asset']['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );

  
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['site_compare_a']) && !empty($TableResult['asset']['site_compare_a'])?unserialize($TableResult['asset']['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['facility_compare_a']) && !empty($TableResult['asset']['facility_compare_a'])?unserialize($TableResult['asset']['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['zone_compare_a']) && !empty($TableResult['asset']['zone_compare_a'])?unserialize($TableResult['asset']['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status_compare_a']) && !empty($TableResult['asset']['status_compare_a'])?unserialize($TableResult['asset']['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['riskrank_compare_a']) && !empty($TableResult['asset']['riskrank_compare_a'])?unserialize($TableResult['asset']['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult['asset']['filter_compare_a']) && !empty($TableResult['asset']['filter_compare_a'])?unserialize($TableResult['asset']['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult['asset']['subtitle_compare_b']) && !empty($TableResult['asset']['subtitle_compare_b'])?unserialize($TableResult['asset']['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['region_compare_b']) && !empty($TableResult['asset']['region_compare_b'])?unserialize($TableResult['asset']['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['site_compare_b']) && !empty($TableResult['asset']['site_compare_b'])?unserialize($TableResult['asset']['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['facility_compare_b']) && !empty($TableResult['asset']['facility_compare_b'])?unserialize($TableResult['asset']['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['zone_compare_b']) && !empty($TableResult['asset']['zone_compare_b'])?unserialize($TableResult['asset']['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['status_compare_b']) && !empty($TableResult['asset']['status_compare_b'])?unserialize($TableResult['asset']['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['asset']['riskrank_compare_b']) && !empty($TableResult['asset']['riskrank_compare_b'])?unserialize($TableResult['asset']['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Filter'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult['asset']['filter_compare_b']) && !empty($TableResult['asset']['filter_compare_b'])?unserialize($TableResult['asset']['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_asset_risk_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_assets',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_open_pm_process2($element, &$form_state){
  global $user,$company;
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type','work_orders_open_pm','=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="hcfm-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult['work_orders_open_pm']['subtitle_compare_a']) && !empty($TableResult['work_orders_open_pm']['subtitle_compare_a'])?unserialize($TableResult['work_orders_open_pm']['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  ); 
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['region_compare_a']) && !empty($TableResult['work_orders_open_pm']['region_compare_a'])?unserialize($TableResult['work_orders_open_pm']['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  ); 
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['site_compare_a']) && !empty($TableResult['work_orders_open_pm']['site_compare_a'])?unserialize($TableResult['work_orders_open_pm']['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );  
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['facility_compare_a']) && !empty($TableResult['work_orders_open_pm']['facility_compare_a'])?unserialize($TableResult['work_orders_open_pm']['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  ); 
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['zone_compare_a']) && !empty($TableResult['work_orders_open_pm']['zone_compare_a'])?unserialize($TableResult['work_orders_open_pm']['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
 
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['status_compare_a']) && !empty($TableResult['work_orders_open_pm']['status_compare_a'])?unserialize($TableResult['work_orders_open_pm']['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['riskrank_compare_a']) && !empty($TableResult['work_orders_open_pm']['riskrank_compare_a'])?unserialize($TableResult['work_orders_open_pm']['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult['work_orders_open_pm']['filter_compare_a']) && !empty($TableResult['work_orders_open_pm']['filter_compare_a'])?unserialize($TableResult['work_orders_open_pm']['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
 $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult['work_orders_open_pm']['subtitle_compare_b']) && !empty($TableResult['work_orders_open_pm']['subtitle_compare_b'])?unserialize($TableResult['work_orders_open_pm']['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );  
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['region_compare_b']) && !empty($TableResult['work_orders_open_pm']['region_compare_b'])?unserialize($TableResult['work_orders_open_pm']['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );  
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['site_compare_b']) && !empty($TableResult['work_orders_open_pm']['site_compare_b'])?unserialize($TableResult['work_orders_open_pm']['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );  
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['facility_compare_b']) && !empty($TableResult['work_orders_open_pm']['facility_compare_b'])?unserialize($TableResult['work_orders_open_pm']['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['zone_compare_b']) && !empty($TableResult['work_orders_open_pm']['zone_compare_b'])?unserialize($TableResult['work_orders_open_pm']['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['status_compare_b']) && !empty($TableResult['work_orders_open_pm']['status_compare_b'])?unserialize($TableResult['work_orders_open_pm']['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult['work_orders_open_pm']['riskrank_compare_b']) && !empty($TableResult['work_orders_open_pm']['riskrank_compare_b'])?unserialize($TableResult['work_orders_open_pm']['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  ); 
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult['work_orders_open_pm']['filter_compare_b']) && !empty($TableResult['work_orders_open_pm']['filter_compare_b'])?unserialize($TableResult['work_orders_open_pm']['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_open_pm_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_open_pms',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_back_open_cm_process2($element, &$form_state){
  global $user,$company;
  $TRtype = 'work_orders_open_cm';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );  
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );  
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );  
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_open_cm_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_open_cms',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_back_open_projects_process2($element, &$form_state){
  global $user,$company;
  $TRtype ='work_orders_open_projects';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );  
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_open_projects_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_projects',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_back_work_orders_on_hold_process2($element, &$form_state){
  global $user,$company;
  $TRtype ='work_orders_on_hold';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );  
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' =>  $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_work_orders_on_hold_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_parts_on_order',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_back_past_due_work_orders_process2($element, &$form_state){
  global $user,$company;
  $TRtype = 'past_due_work_orders';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_past_due_work_orders_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_back_log',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_back_work_order_ratio_process2($element, &$form_state){
  global $user,$company;
  $TRtype = 'work_order_ratio';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC);
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week'); 
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  
  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /*** *******************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  
  
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_work_order_ratio_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_work_order_focus',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_back_square_foot_process2($element, &$form_state){
  global $user,$company;
  $TRtype = 'square_foot';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_back_square_foot_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_square_foot',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_available_labor_process2($element, &$form_state){
  global $user,$company;
  $TRtype ='available_labor';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_available_labor_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_labor',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_fte_square_foot_process2($element, &$form_state){
  global $user,$company;
  $TRtype = 'fte_square_foot';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );
  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_fte_square_foot_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_labor_sf',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
}

function hcfmdashboard_labor_use_rate_process2($element, &$form_state){
  global $user,$company;
  $TRtype = 'labor_use_rate';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

 /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
  '#type' => 'button',
  '#ajax' => array(
    'callback' => 'hcfmdashboard_labor_use_rate_callback',
    'event' => 'click',
    'wrapper' => 'workflow-container-section',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array('type' => 'none'),
  ),
  '#name' => 'hcfm_dashboard_compare_labor_use',
  '#validate' => TRUE,
  '#value' => t('Compare'),
  '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
  '#suffix' => '</div></div></div>',
  );
  return $element;
} 

function hcfmdashboard_labor_forecast_process2($element, &$form_state){
  global $user,$company;
  $TRtype ='labor_forecast';
  $UserUid = (isset($user)&& $user->uid == 2 ? 0:$user->uid);
  $ComNid= (isset($company )&& $company->nid == 645 ? 0:$company->nid);
  $query = db_select('m6cocnnect_hcfm_dashboard_tiles_compare','hcfmdt');
  $query->fields('hcfmdt');
  $query->condition('hcfmdt.user',$user->uid,'=');
  $query->condition('hcfmdt.company',$company->nid,'=');
  $query->condition('hcfmdt.type',$TRtype,'=');  
  $TableResult = $query->execute()->fetchAllAssoc('type', PDO::FETCH_ASSOC); 
  $asset_region = hcfm_nodenid_nodetitle_by_node_type('fm_location_region',$ComNid,$UserUid);
  $asset_region_selectAll = array();
  if(count($asset_region) > 0){
    $asset_region_selectAll = array('all'=>'All');
  }
  $location_site = hcfm_nodenid_nodetitle_by_node_type('fm_location_site',$ComNid,$UserUid);
  $location_site_selectAll = array();
  if(count($location_site) > 0){
    $location_site_selectAll = array('all'=>'All');
  }
  $asset_facility = hcfm_nodenid_nodetitle_by_node_type('fm_facility',$ComNid,$UserUid);
  $asset_facility_selectAll = array();
  if(count($asset_facility) > 0){
    $asset_facility_selectAll = array('all'=>'All');
  }
  $location_location = hcfm_nodenid_nodetitle_by_node_type('fm_location_location',$ComNid,$UserUid);
  $fm_asset_status = hcfm_nodenid_nodetitle_by_node_type('fm_asset_status');
  $fm_risk_rank = hcfm_nodenid_nodetitle_by_node_type('fm_risk_rank');
  $DashboardFilter = array('today'=>'Today','tomorrow'=>'Tomorrow','yesterday'=>'Yesterday','last_year'=>'Last Year','last_month'=>'Last Month','last_week'=>'Last Week','this_year'=>'This Year','this_month'=>'This Month','this_week'=>'This Week','next_year'=>'Next Year','next_month'=>'Next Month','next_week'=>'Next Week');
  //drupal_add_js(drupal_get_path('module', 'm6connect_hcfm') . '/js/jquery.flip.min.js');
    
  /*$element['asset_riskrank_data'] = array(  
  '#markup' => '<div class="asset_riskrank_data"></div>',
  '#prefix' => '<div class="row"><div class="col-md-6">', 
    '#suffix' => '</div></div>',
  );*/
  $element['compare-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#prefix' => '<div class="asset-compare-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectiona')),    
  );
  $element['compare-container']['compare-right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-6','col-sm-6','col-xs-12','compare-sectionb')),    
  );
  $element['compare-container']['compare-left-container']['adash_asset_subtitle_a'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_a']) && !empty($TableResult[$TRtype]['subtitle_compare_a'])?unserialize($TableResult[$TRtype]['subtitle_compare_a']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-left-container']['adash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'ahcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_a']) && !empty($TableResult[$TRtype]['region_compare_a'])?unserialize($TableResult[$TRtype]['region_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'ahcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_a']) && !empty($TableResult[$TRtype]['site_compare_a'])?unserialize($TableResult[$TRtype]['site_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-left-container']['adash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'ahcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_a']) && !empty($TableResult[$TRtype]['facility_compare_a'])?unserialize($TableResult[$TRtype]['facility_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*
  $element['compare-container']['compare-left-container']['adash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'ahcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_a']) && !empty($TableResult[$TRtype]['zone_compare_a'])?unserialize($TableResult[$TRtype]['zone_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_a']) && !empty($TableResult[$TRtype]['status_compare_a'])?unserialize($TableResult[$TRtype]['status_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-left-container']['adash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_a']) && !empty($TableResult[$TRtype]['riskrank_compare_a'])?unserialize($TableResult[$TRtype]['riskrank_compare_a']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );
  */
  
  $element['compare-container']['compare-left-container']['adash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'ahcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_a']) && !empty($TableResult[$TRtype]['filter_compare_a'])?unserialize($TableResult[$TRtype]['filter_compare_a']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  /**********************************************************************/
  $element['compare-container']['compare-right-container']['bdash_asset_subtitle_b'] = array(
    '#title' => t('Title'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',        
        'dash_asset_subtitle',
      )
    ),
    '#type' => 'textfield',    
    '#default_value' => (isset($TableResult[$TRtype]['subtitle_compare_b']) && !empty($TableResult[$TRtype]['subtitle_compare_b'])?unserialize($TableResult[$TRtype]['subtitle_compare_b']):''),
    '#field_prefix' => '<div class="select2-container select2-container-multi" style="width: 195px;">',
    '#field_suffix' => '</div>',
    //'#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_region_list'] = array(
    '#title' => t('Select Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-region',
        'bhcfmdash-region-list',
        'dash_asset_region_list',
        'hcfm-compare-selectallfield',

      )
    ),
    '#type' => 'select',
    '#options' => $asset_region_selectAll+$asset_region,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['region_compare_b']) && !empty($TableResult[$TRtype]['region_compare_b'])?unserialize($TableResult[$TRtype]['region_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    '#prefix' => '<div class="dash-form-field hcfm-dash-form-outer clearfix margin-bottom-10">',
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_site_list'] = array(
    '#title' => t('Select Site'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-site',
        'bhcfmdash-site-list',
        'dash_asset_site_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $location_site_selectAll+$location_site,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['site_compare_b']) && !empty($TableResult[$TRtype]['site_compare_b'])?unserialize($TableResult[$TRtype]['site_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div>',  
  );
  $element['compare-container']['compare-right-container']['bdash_asset_facility_list'] = array(
    '#title' => t('Select Facility '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-facility',
        'bhcfmdash-facility-list',
        'dash_asset_facility_list',
        'hcfm-compare-selectallfield',
      )
    ),
    '#options' => $asset_facility_selectAll+$asset_facility,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['facility_compare_b']) && !empty($TableResult[$TRtype]['facility_compare_b'])?unserialize($TableResult[$TRtype]['facility_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="padding-5">',
    //'#suffix' => '</div></div>',
  );
  /*  
  $element['compare-container']['compare-right-container']['bdash_asset_zone_list'] = array(
    '#title' => t('Select Zone '),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'Eas-asset-location',
        'bhcfmdash-zone-list',
        'dash_asset_zone_list'
      )
    ),
    '#options' => $location_location,
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['zone_compare_b']) && !empty($TableResult[$TRtype]['zone_compare_b'])?unserialize($TableResult[$TRtype]['zone_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#prefix' => '<div class="row margin-5"><div class="padding-5">',
    //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_status_list'] = array(
    '#title' => t('Select Status'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-status-list',
        'dash_asset_status_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_asset_status,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['status_compare_b']) && !empty($TableResult[$TRtype]['status_compare_b'])?unserialize($TableResult[$TRtype]['status_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),  
  //'#prefix' => '<div class="padding-5">', 
  //'#suffix' => '</div>',
  );
  $element['compare-container']['compare-right-container']['bdash_asset_riskrank_list'] = array(
    '#title' => t('Select Risk Rank'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-riskrank-list',
        'dash_asset_riskrank_list',
      )
    ),  
    '#type' => 'select',
    '#multiple'     => TRUE,
    '#options' => $fm_risk_rank,    
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#default_value' => (isset($TableResult[$TRtype]['riskrank_compare_b']) && !empty($TableResult[$TRtype]['riskrank_compare_b'])?unserialize($TableResult[$TRtype]['riskrank_compare_b']):''),
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,  
    //'#prefix' => '<div class="padding-5">', 
    //'#suffix' => '</div></div>',
  );*/
  
  
  $element['compare-container']['compare-right-container']['bdash_asset_filter_list'] = array( 
    '#title' => t('Select Timeline'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'bhcfmdash-filter-list',
        'dash_asset_filter_list'
      )
    ), 
    '#type' => 'select',
    '#options' => $DashboardFilter,
    '#multiple'     => TRUE,
    '#default_value' => (isset($TableResult[$TRtype]['filter_compare_b']) && !empty($TableResult[$TRtype]['filter_compare_b'])?unserialize($TableResult[$TRtype]['filter_compare_b']):''),
    ////'#attributes'=> array('class'=> array('form-control')),
    '#empty_option' => 'None',
    '#select2' => array(
      'width' => '150',
      'minimumResultsForSearch' => '1',
    ),
    '#multiple'     => TRUE,
    //'#default_value' => 'this_month',
    //'#prefix' => '<div class="row margin-5"><div class="col-md-4 padding-5">', 
    '#suffix' => '</div>',   
  );

  $element['dashboard_asset_submit'] = array(
    //'#markup' => l('<input type="button" class="btn btn primary form-submit" value="Submit" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_submit_btn')))),
    '#type' => 'button',
    '#ajax' => array(
      'callback' => 'hcfmdashboard_labor_forecast_callback',
      'event' => 'click',
      'wrapper' => 'workflow-container-section',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type' => 'none'),
    ),
    '#name' => 'hcfm_dashboard_compare_labor_forecast',
    '#validate' => TRUE,
    '#value' => t('Compare'),
    '#prefix' => '<div class="clearfix text-center"><div class="form-item"><div class="display-inline-block">'.l('<input type="button" class="btn btn primary form-submit" value="Reset" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('dashboard_asset_reset_btn')))).'</div><div class="display-inline-block">',
    '#suffix' => '</div></div></div>',
  );
  return $element;
}
/////process2 end /////

function hcfmdashtile_render_callback($masterid,$action,$tileid,$ajax=NULL){
  global $user;
  ctools_include('ajax');
  $commands = array();
  //pre($masterid);
  //pre($action);
  //pre($tileid);
  //pre($ajax);
  if(isset($action) && !empty($action)){
    if($action == 'normal'||$action =='large'){
      $renderData = hcfm_dash_tile_data_callback($tileid,'front',$action);
      $commands[] = ajax_command_html('#'.$masterid .' .graph-'.$action, $renderData);
    }
    if($action == 'compare'){
      $renderData = hcfm_dash_tile_data_callback($tileid,'front',$action);
      $commands[] = ajax_command_html('#'.$masterid .' .desh-sec-c .front-compare', $renderData);
    }
  }

  print ajax_render($commands);
  exit;
}