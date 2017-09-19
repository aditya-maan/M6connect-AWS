
<?php
/**
 * @file Contains Menu Callback for Manage Asset Locations.
 * In Cost Manager, Cost Project Manager, Construction Manager.
 */

/**
 * Menu callback for Manage Asset Location.
 */
function program_project_manage_asset_location() {
  global $company;
  global $user;

  drupal_add_js(drupal_get_path('module', 'm6connect_program') . '/js/m6connect_asset_loc.js');

  $path = $_GET['q'];
  $arguments = explode('/', $path);

  $top_arg = 'cpm';
  if ($arguments[1] == 'cm') {
    $top_arg = 'cm';
  }
  elseif ($arguments[1] == 'cr') {
    $top_arg = 'cr';
  }
  else {
    $top_arg = 'cpm';
  }

  $location_region = drupal_get_form('cost_manager_config_location_region_form', $top_arg);
  $location_site = drupal_get_form('cost_manager_config_location_site_form', $top_arg);
  $location_facility = drupal_get_form('cost_manager_config_location_facility_form', $top_arg);
  $location_location = drupal_get_form('cost_manager_config_location_location_form', $top_arg);
  $location_facilitytype = cost_manager_config_facility_type_container($top_arg);

  $elements = array();
  $elements['prgram-project-menu-items'] = array(
    '#markup' => new_programe_manager_setting_link_content(),
    '#prefix' => '<div class="clearfix">',
    '#suffix' => '</div>',
  );
  $elements['container_tab']= array(
    '#markup' => 
        '
        <div class="hcfm-location-container-tab company-prequal-fields">
          
          <!-- Nav tabs -->
          <ul class="nav nav-tabs" role="tablist">
            <li role="presentation" class="active config_location_region"><a href="#locationregion" aria-controls="locationregion" role="tab" data-toggle="tab">Region</a></li>
            <li role="presentation" class="config_location_site"><a href="#locationsite" aria-controls="locationsite" role="tab" data-toggle="tab">Site</a></li>
            <li role="presentation" class="config_location_facilitytype"><a href="#locationfacilitytype" aria-controls="locationfacilitytype" role="tab" data-toggle="tab">Facility Type</a></li>
            <li role="presentation" class="config_location_facility"><a href="#locationfacility" aria-controls="locationfacility" role="tab" data-toggle="tab">Facility</a></li>
            <li role="presentation" class="config_location_location"><a href="#locationlocation" aria-controls="locationlocation" role="tab" data-toggle="tab">Zone</a></li>
          </ul>
          
          <!-- Tab panes -->
          <div class="tab-content">      
            <div role="tabpanel" class="tab-pane active config_location_region" id="locationregion">'.drupal_render($location_region).'</div>
            <div role="tabpanel" class="tab-pane config_location_site" id="locationsite">'.drupal_render($location_site).'</div>
            <div role="tabpanel" class="tab-pane config_location_facilitytype" id="locationfacilitytype">'.drupal_render($location_facilitytype).'</div>
            <div role="tabpanel" class="tab-pane config_location_facility" id="locationfacility">'.drupal_render($location_facility).'</div>
            <div role="tabpanel" class="tab-pane config_location_location" id="locationlocation">'.drupal_render($location_location).'</div>
          </div>
        </div>',
    '#prefix' => '<div class="clearfix margin-bottom-10">',
    '#suffix' => '</div>',
  );
  return $elements;
}

/**
 * Form callbacks.
 */
function cost_manager_config_location_region_form($form, &$form_state, $top_arg = '') {
  global $user,$company;
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg,
  );

  $form['#prefix'] = '
    <div class="clearfix relative">
      <div class="new-locationregion hcfm-add-new-btn">
      <a href="javascript:void(0);" class="new-locationregion-link green-round-btn" title="Create New Region">
      <i class="glyphicon glyphicon-plus"></i> New Region
      </a>
    </div>';
  $form['#suffix'] = '</div>';
  $form['#attributes']['class'][] = 'clearfix'; 

  $form['main-container-main']= array(
    '#type' => 'container', 
    '#prefix' => '<div class="locationregion-create-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['config_location_region_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Region Name'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_region_title'
      )
    ),
    '#weight' => 0,
    '#required' => TRUE,
    '#prefix' => '<div class="row"><div class="col-md-6">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['config_location_region_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Region Description'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_region_description'
      )
    ),
    '#weight' => 1,
    //'#required' => TRUE,
    '#prefix' => '<div class="col-md-6">',
    '#suffix' => '</div></div>',
  );
  
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;
  $form['main-container-main']['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#weight' => 5,
    '#prefix' => '<label>Address</label><div class="project-details-border margin-bottom-10" style="border:1px solid;padding:5px;">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_region_country'] = array(
    '#type' => 'select',  
    '#title' => t('Country'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_region_country'
      )
    ),
    '#options' => $countryNamesList1,
    '#empty_option' => t('- Select -'),
    //'#default_value' => 'US',
    '#prefix' => '<div class="col-md-6">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_region_country_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_region_country_value'
      )
    ),  
  );
  $form['main-container-main']['main-container']['config_location_region_address1'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address1'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_region_address1'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',  
  );   
  $form['main-container-main']['main-container']['config_location_region_address2'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address2'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_region_address2'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_region_city'] = array(
    '#type' => 'textfield', 
    '#title' => t('City'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_region_city'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );
//  $administrativeNamesList = addressfield_get_administrative_areas('US');
  $form['main-container-main']['main-container']['config_location_region_state'] = array(
    '#type' => 'select',  
    '#title' => t('State'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_region_state'
      )
    ),
    '#options' => _get_asset_loc_default_state(),
    '#validate' => TRUE,
    '#empty_option' => t('- Select -'),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $form['main-container-main']['main-container']['config_location_region_state_key'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_region_state_key'
      )
    )
  );
  $form['main-container-main']['main-container']['config_location_region_state_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_region_state_value'
      )
    )
  );    
  $form['main-container-main']['main-container']['config_location_region_zipcode'] = array(
    '#type' => 'textfield', 
    '#title' => t('Zip Code'),
    //'#parents' => array('facility_data',$uniqId,'fa_zipcode'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_region_zipcode'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  
  $form['main-container-main']['config_location_region_address'] = array(
    '#type' => 'hidden',
    '#title' => t('Region Address'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_region_address'
      )
    ),
    //'#weight' => 2,
    //'#required' => TRUE,  
  );
  $form['add_ntype'] = array('#type' => 'value', '#value' => 'fm_location_region');
  $form['user_uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'user-uid'
      )
    ),
  );
  $form['company_nid'] = array(
    '#type' => 'value',
    '#value' => $company->nid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'company-nid'
      )
    ),
  );
  $form['main-container-main']['node_nid'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'node-nid'
      )
    ),
    );
  $form['main-container-main']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('cm_custom_asset_configure_submit'),
    '#value' => t('Save'),
    '#weight' => 6, 
  );
  $form['main-container-main']['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit crb-config-location-region">', 
    '#weight' => 7,   
  );

  $header = array('Region Name','Description','Action'); 
  $table_data = asset_loc_table_content($user->uid, $company->nid, 'fm_location_region', $header, $top_arg);
  $form['table_datiles'] = array(
    '#markup' => $table_data,
    '#weight' => 8,
  ); 

  return $form;
}

function cost_manager_config_location_site_form($form, &$form_state, $top_arg = '') {
  global $user,$company;

  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg,
  );

  $form['#prefix'] = '
    <div class="clearfix relative">
      <div class="new-locationsite hcfm-add-new-btn">
      <a href="javascript:void(0);" class="new-locationsite-link green-round-btn" title="Create New Site">
      <i class="glyphicon glyphicon-plus"></i> New Site
      </a>
    </div>';
  $form['#suffix'] = '</div>';
  $form['#attributes']['class'][] = 'clearfix'; 
  $form['main-container-main']= array(
    '#type' => 'container', 
    '#prefix' => '<div class="locationsite-create-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $locationRegion = asset_loc_nodenid_nodetitle_by_node_type('fm_location_region', $company->nid, $user->uid, $top_arg);

  $form['main-container-main']['config_location_site_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Site Name'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_site_title'
      )
    ),
    '#required' => TRUE,
    '#weight' => 1,
    '#prefix' => '<div class="row"><div class="col-md-3">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['config_location_pick_region'] = array(
    '#type' => 'select',
    '#options' => $locationRegion,
    '#empty_option' => t('- Select -'),
    '#title' => t('Region'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_pick_region'
      )
    ),
    '#required' => TRUE,
    '#weight' => 2,
    '#prefix' => '<div class="col-md-3">',
    '#suffix' => '</div>',
  );
  
  $form['main-container-main']['config_location_site_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Site Description'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_site_description'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 3,
    '#prefix' => '<div class="col-md-6">',
    '#suffix' => '</div></div>',
  );  
  
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;
  $form['main-container-main']['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#weight' => 5,
    '#prefix' => '<label>Address</label><div class="project-details-border margin-bottom-10" style="border:1px solid;padding:5px;">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_site_country'] = array(
    '#type' => 'select',  
    '#title' => t('Country'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_site_country'
      )
    ),
    '#options' => $countryNamesList1,
    '#empty_option' => t('- Select -'),
    //'#default_value' => 'US',
    '#prefix' => '<div class="col-md-6" style="display:none">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_site_country_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_site_country_value'
      )
    ),
  );
  $form['main-container-main']['main-container']['config_location_site_address1'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address1'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_address1'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );   
  $form['main-container-main']['main-container']['config_location_site_address2'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address2'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_address2'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_site_city'] = array(
    '#type' => 'textfield', 
    '#title' => t('City'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_city'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );
 // $administrativeNamesList = addressfield_get_administrative_areas('US');
  $form['main-container-main']['main-container']['config_location_site_state'] = array(
    '#type' => 'select',  
    '#title' => t('State'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_state'
      )
    ),
    '#options' => _get_asset_loc_default_state(),
    '#validate' => TRUE,
    '#empty_option' => t('- Select -'),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['main-container']['config_location_site_state_key'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_state_key'
      )
    )
  );
  $form['main-container-main']['main-container']['config_location_site_state_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_state_value'
      )
    )
  );  
  $form['main-container-main']['main-container']['config_location_site_zipcode'] = array(
    '#type' => 'textfield', 
    '#title' => t('Zip Code'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_site_zipcode'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $form['add_ntype'] = array('#type' => 'value', '#value' => 'fm_location_site');
  $form['user_uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'user-uid'
      )
    ),  
  );
  $form['company_nid'] = array(
    '#type' => 'value',
    '#value' => $company->nid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'company-nid'
      )
    ),  
  );
  $form['main-container-main']['node_nid'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'node-nid'
      )
    ),    
  );
  $form['main-container-main']['config_location_site_address'] = array(
    '#type' => 'hidden',
    '#title' => t('Site Address'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_site_address'
      )
    ),
    //'#required' => TRUE,
  );
  $form['main-container-main']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('cm_custom_asset_configure_submit'),
    '#value' => t('Save'),  
    '#weight' => 6,
  );
  $form['main-container-main']['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit crb-config-location-site">',  
    '#weight' => 7,
  );

  $header = array('Site Name','Address','Description','Region Name','Action');
  $table_data = asset_loc_table_content($user->uid, $company->nid, 'fm_location_site', $header, $top_arg);
  $form['table_datiles'] = array(
    '#markup' => $table_data,
    '#weight' => 8,
  );
  return $form;
}

function cost_manager_config_location_facility_form($form, &$form_state, $top_arg = '') {
  global $user,$company;

  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg,
  );

  if (isset($form_state['top_arg_fs'])) {
    unset($form_state['top_arg_fs']);
  }

  $form_state['top_arg_fs'] = $top_arg;
  
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'm6connect_program') . '/js/jquery.multiselect.css' => array(
      'type' => 'file',
    ),
  );
  $form['#attached']['js'] = array(
    "jQuery(document).ready(function() {
      jQuery('select.config_location_facility_areatype').multiselect({
        columns: 2,
        placeholder: 'Select Area Type',
      });
    });" => array(
    'type' => 'inline',
    ),
    drupal_get_path('module', 'm6connect_program') . '/js/jquery.multiselect.js' => array(
      'type' => 'file',
    ),
  );

  $fmfacility = asset_loc_nodenid_nodetitle_by_node_type('fm_facility', $company->nid, $user->uid, $top_arg);
  // $fmfacility = array('none', 'none');

  $form['get_facility'] = array(
    '#type' => 'select',
    '#title'=> 'Select Facility',
    '#options' => $fmfacility,
    '#empty_option' => t('- Select -'),
    // '#default_value' => isset($_GET['cid'])?$_GET['cid']:0,
    '#attributes' => array('class'=> array('form-control fm-facility-sel')),
    '#ajax' => array(
      'callback'=> 'prog_loc_change_facility_nid_callback',
      'wrapper' => 'fm_facility_sel_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );

  $form['#prefix'] = '
    <div class="clearfix relative">
      <div class="new-locationfacility hcfm-add-new-btn">
      <a href="javascript:void(0);" class="new-locationfacility-link green-round-btn" title="Create New Facility">
      <i class="glyphicon glyphicon-plus"></i> New Facility
      </a>
    </div>';
  $form['#suffix'] = '</div>';

  $form['main_container_main']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('location-facility-container-section')),
    '#prefix' => '<div class="locationfacility-create-container margin-bottom-10">', 
    '#suffix' => '</div>',
    '#process' => array('cost_manager_config_location_facility_container_process'),
  );

  $form['#attributes']['class'][] = 'clearfix chosentoselectmultiple';

  $header = array('Facility Name','Description','Site Name','Region Name','Action');
  $table_data = asset_loc_table_content($user->uid, $company->nid, 'fm_facility', $header, $top_arg);
  $form['table_datiles'] = array(
    '#markup' => $table_data,
    '#weight' => 22,
  );
  
  return $form;
}

function cost_manager_config_location_location_form($form, &$form_state, $top_arg = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');
  $fm_location_location = asset_loc_nodenid_nodetitle_by_node_type('fm_location_location', $company->nid, $user->uid, $top_arg);

  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg,
  );

  if (isset($form_state['top_arg_fs'])) {
    unset($form_state['top_arg_fs']);
  }
  $form_state['top_arg_fs'] = $top_arg;

  $form['#attached']['js'] = array(
    "Drupal.behaviors.m6connect_cm_inline_js = {
      attach: function (context, settings) {
        jQuery('select.config_location_location_numberoffloor').multiselect({
          columns: 2,
          placeholder: 'Select Area Type',
        });
      }
    }" => array(
    'type' => 'inline',
    ),
  );

  $form['get_location_zone'] = array(
    '#type' => 'select',
    '#title'=> 'Select locaton zone',
    '#options' => $fm_location_location,
    //'#default_value' => isset($_GET['cid'])?$_GET['cid']:0,
    '#attributes' => array('class'=> array('form-control locaton-zone-sel')),
    '#empty_option' => t('- Select -'),
    '#ajax' => array(
      'callback'=> 'prog_loc_change_zone_nid_callback',
      'wrapper' => 'location_zone_main_container',
      'effect' => 'fade',
    ),
    '#prefix' => '<div class="clearfix" style="display:none;"><div class="pull-left form-inline">',
    '#suffix' => '</div></div>',
  );  
  $form['#prefix'] = '
    <div class="clearfix relative">
      <div class="new-locationlocation hcfm-add-new-btn">
      <a href="javascript:void(0);" class="new-locationlocation-link green-round-btn" title="Create New Zone">
      <i class="glyphicon glyphicon-plus"></i> New Zone
      </a>
    </div>';
  $form['#suffix'] = '</div>';  

  $form['#attributes']['class'][] = 'chosentoselectmultiple clearfix';
  //drup_msg($form_state['values']['config_location_pick_facility']);
  $FacilityListObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'node','Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('nid'),'OtherId'=>array('equal'=>array('type'=>'fm_facility'))); 
  $FacilityList =  _get_asset_loc_db_request($FacilityListObj);


  if (isset($FacilityList) && !empty($FacilityList)) {
    $FloorListsObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_facility_floor_name','addExpression'=>"CONCAT(entity_id, '_', delta)",'addExpression_value'=>"nid_delta",'Fetch'=>'fetchAllKeyed','CFields'=>'CFields','CFieldsNames'=>array('field_facility_floor_name_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_facility'),'IN'=>array('entity_id'=>$FacilityList)));
    $FloorLists =  _get_asset_loc_db_request($FloorListsObj);
  }

  $form_state['config_location_location_numberoffloor'] = array('none'=>'none');

  if (isset($form_state['values'],$form_state['input'],$form_state['triggering_element'],$form_state['triggering_element']['#type'],$form_state['triggering_element']['#name']) && $form_state['triggering_element']['#type']=='select' && $form_state['triggering_element']['#name']=='config_location_pick_facility' && !empty($form_state['triggering_element']['#value'])) {

    $facilityNid = $form_state['values']['config_location_pick_facility'];
    $NodeObj11 = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_facility_floor_name','addExpression'=>"CONCAT(entity_id, '_', delta)",'addExpression_value'=>"nid_delta",'Fetch'=>'fetchAllKeyed','CFields'=>'CFields','CFieldsNames'=>array('field_facility_floor_name_value'),'OtherId'=>array('equal'=>array('bundle'=>'facility'),'equal'=>array('entity_id'=>$form_state['triggering_element']['#value'])));
    $TableData11 =  _get_asset_loc_db_request($NodeObj11);
    $floorOption = array_flip($TableData11);

    if (!empty($floorOption)) {
      $form_state['config_location_location_numberoffloor'] = $floorOption;
    }
  }
  
  if(empty($form_state['location_option_wrapper']['location_option'])){
    $form_state['location_option_wrapper']['location_option'] = '';
  }
  $form['main_container_main'] = array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('location-location-container-section')),
    '#prefix' => '<div class="locationlocation-create-container margin-bottom-10">', 
    '#suffix' => '</div>',
    '#process' => array('cost_manager_config_location_location_container_process'),
  );
  
  $header = array('Zone Name','Description','Facility Name','Site Name','Region Name','Action'); 
  $table_data = asset_loc_table_content($user->uid, $company->nid, 'fm_location_location', $header, $top_arg);

  $form['table_datiles'] = array(
    '#markup' => $table_data,
    '#weight' => 22,
  );
  return $form;
}

function cost_manager_add_config_facilitytype_form($form, &$form_state, $top_arg = '') {
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  global $user, $company;

  $form['#prefix'] = '<div class="clearfix relative">';
  $form['#suffix'] = '</div>';
  $form['#attributes']['class'][] = 'clearfix'; 

  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg,
  );

  $form['main-container-main']= array(
    '#type' => 'container', 
    '#prefix' => '<div class="facilitytype-create-container margin-bottom-10">',
    '#suffix' => '</div>',
  );
  $form['main-container-main']['config_facility_type_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Facility Type Name'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_facility_type_title'
      )
    ),
    '#required' => TRUE,
  );
  $form['main-container-main']['config_facility_type_description'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_facility_type_description'
      )
    ),
    '#title' => t('Description'),
  );  
  $form['facility_type_node_nid'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'facility_type_node_nid'
      )
    ),
  );
  
  $form['add_ntype'] = array('#type' => 'value', '#value' => 'fm_facility_type');
  $form['user_uid'] = array('#type' => 'value', '#value' => $user->uid);
  $form['company_nid'] = array('#type' => 'value', '#value' => $company->nid);

  $form['main-container-main']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('cm_custom_asset_configure_submit'),
    '#value' => t('Save'),  
  );

  $form['main-container-main']['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit crb-config-facility-type">',  
  );

  $header = array('Facility Type Name','Description','Action'); 
  $table_data = asset_loc_table_content($user->uid, $company->nid, 'fm_facility_type', $header, $top_arg);
  $form['table_datiles'] = array(
    '#markup' => $table_data, 
  );
 
  return $form;
}

function cost_manager_add_config_facility_areatype_form($form, &$form_state, $top_arg = '') {
  global $user, $company;
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  $form['#prefix'] = '
    <div class="clearfix relative">
      <div class="new-facilitytype hcfm-add-new-btn">
      <a href="javascript:void(0);" class="new-facilitytype-link green-round-btn" title="Create New Facility Type">
      <i class="glyphicon glyphicon-plus"></i> New Facility Type
      </a>
    </div>';
  $form['#suffix'] = '</div>';
  $form['#attributes']['class'][] = 'clearfix'; 

  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg,
  );

  $form['main-container-main']= array(
    '#type' => 'container', 
    '#prefix' => '<div class="facilitytype-create-container margin-bottom-10">',
    '#suffix' => '</div>',
  );  
  $form['main-container-main']['config_facility_area_type_title'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_facility_area_type_title'
      )
    ),
    '#title' => t('Area Type Name'),
    '#required' => TRUE,
  );
  $form['main-container-main']['config_facility_area_type_description'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_facility_area_type_description'
      )
    ),
    '#title' => t('Description'),
  ); 
  $form['facility_area_type_node_nid'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'facility_area_type_node_nid'
      )
    ),
  );

  $form['add_ntype'] = array('#type' => 'value', '#value' => 'fm_facility_area_type');
  $form['user_uid'] = array('#type' => 'value', '#value' => $user->uid);
  $form['company_nid'] = array('#type' => 'value', '#value' => $company->nid);

  $form['main-container-main']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('cm_custom_asset_configure_submit'),
    '#value' => t('Save'),  
  );
  $form['main-container-main']['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit crb-config-facility-area-type">', 
  );

  $header1 = array('Area Type Name','Description','Action'); 
  $table_data1 = asset_loc_table_content($user->uid, $company->nid, 'fm_facility_area_type', $header1, $top_arg);
  $form['table_datiles1'] = array(
    '#markup' => $table_data1,
  );
  return $form;
}

function cost_manager_config_facility_type_container($top_arg = '') {
  $element = array();
  $element['main-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('row')),
    //'#prefix' => '<div class="asset-create-container">',
    //'#suffix' => '</div>',
  );
  $element['main-container']['left-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('col-md-6','col-sm-6','col-xs-12','facilitytype-details-left')),
    '#weight' => 1,
  );
  $element['main-container']['right-container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('col-md-6','col-sm-6','col-xs-12','facilitytype-details-right')),
    '#weight' => 2,
  );
  $element['main-container']['left-container']['facility_type'] = array(
    '#markup' => drupal_render(drupal_get_form('cost_manager_add_config_facilitytype_form', $top_arg)),
  );
  $element['main-container']['right-container']['facility_area_type'] = array(
    '#markup' => drupal_render(drupal_get_form('cost_manager_add_config_facility_areatype_form', $top_arg)),
  );
  
  return $element;
}

/**
 * Helper function to get table content for asset location forms.
 */
function asset_loc_table_content($currentUserUid, $currentComNid, $type, $headervalue, $top_arg) {
  global $user,$company;
  $output = '';
    
  $header = array();
  foreach ($headervalue as $HValue) {
    $header[]=array(
      'data' =>  $HValue,
      'class' => array(
        'text-left' 
      ) 
    );
  }
    
  $rows = array ();

  if ($type == 'fm_location_region') {
    $query = db_select('node','n');
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->leftjoin('field_data_field_locationregion_description','fsd','fsd.entity_id=n.nid');

    if (!empty($top_arg)) {
      $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
      $query->condition('cmt.field_cm_type_value', $top_arg);
    }

    $query->fields('n',array('nid','title','type'));
    $query->fields('fsd',array('field_locationregion_description_value'));

    if(isset($currentComNid) && !empty($currentComNid) && $currentComNid != 0){
      $query->condition('ogm.gid',$currentComNid,'=');
    }

    if(isset($currentUserUid) && !empty($currentUserUid) && $currentUserUid != 0){
      $query->condition('n.uid',$currentUserUid,'=');
    }

    $query->condition('n.type',$type,'=');
    $result = $query->execute()->fetchAllAssoc('nid');
    if ($result && ! empty ( $result )){
      foreach ($result as $nid => $obj){
        $action = '<div class="btn-group hcfm-action-btn">
           <div class="dropdown">
             <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
             <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
             <li>
               '.l('Edit', url('program-loc-action/'.$type.'/'.$obj->nid.'/edit/nojs'), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax','edit-'.$type.'-detail'))) ).'
             </li>';
             
        if(_asset_loc_node_delete_access($obj->nid,$type) == TRUE) {
          $action .= '<li>
               '.l('Inactive', 'javascript:void(0);', array( 'external'=>TRUE)).'
             </li>';
        }
        else {
          $action .= '<li>
               '.l('Delete', url('program-loc-node-delete/nojs/'.$obj->nid . '/' . $top_arg), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'
             </li>';  
        }        
        $action .= '</ul>
           </div>
           </div>';   
      
        $rows [] = array (
          'data' => array (     
          array (
            'data' => $obj->title,
            'class' => array (
            'view-locationregion-title' 
            )
          ),
          array (
            'data' => $obj->field_locationregion_description_value,
            'class' => array (
            'view-locationregion-description' 
            )
          ),
          array (
            'data' => $action,
            'class' => array (
            'view-locationregion-action' 
            )
          ),
          ),
          'class' => array (
            'listing-row-' . $obj->nid,
          ) 
        );
      }
    }
  }

  if ($type == 'fm_location_site') {
    $query = db_select('node','n');
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->leftjoin('field_data_field_locationsite_description','fsd','fsd.entity_id=n.nid');
    $query->leftjoin('field_data_field_locationsite_address','flsa','flsa.entity_id=n.nid');
    $query->leftjoin('field_data_field_location_region','flre','flre.entity_id=n.nid');

    if (!empty($top_arg)) {
      $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
      $query->condition('cmt.field_cm_type_value', $top_arg);
    }

    $query->fields('n',array('nid','title','type'));
    $query->fields('fsd',array('field_locationsite_description_value'));
    $query->fields('flsa',array('field_locationsite_address_locality'));
    $query->fields('flre',array('field_location_region_target_id'));

    if(isset($currentComNid) && !empty($currentComNid) && $currentComNid != 0){
      $query->condition('ogm.gid',$currentComNid,'=');
    }

    if(isset($currentUserUid) && !empty($currentUserUid) && $currentUserUid != 0){
      $query->condition('n.uid',$currentUserUid,'=');
    }

    $query->condition('n.type',$type,'=');
    $result = $query->execute()->fetchAllAssoc('nid');

    if ($result && ! empty ( $result )){
      foreach ($result as $nid => $obj){
        $action = '<div class="btn-group hcfm-action-btn">
           <div class="dropdown">
             <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
             <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
             <li>
               '.l('Edit', url('program-loc-action/'.$type.'/'.$obj->nid.'/edit/nojs'), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax','edit-'.$type.'-detail'))) ).'
             </li>';
             
        if (_asset_loc_node_delete_access($obj->nid,$type) == TRUE) {
          $action .= '<li>
               '.l('Inactive', 'javascript:void(0);', array( 'external'=>TRUE)).'
             </li>';
        }
        else {
          $action .= '<li>
               '.l('Delete', url('program-loc-node-delete/nojs/'.$obj->nid . '/' . $top_arg), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'
             </li>';  
        }        
        $action .= '</ul>
           </div>
           </div>'; 
      
        $rows [] = array (
          'data' => array (     
          array (
            'data' => $obj->title,
            'class' => array (
            'view-locationsite-title' 
            )
          ),
          array (
            'data' => $obj->field_locationsite_address_locality,
            'class' => array (
            'view-locationsite-address' 
            )
          ),
          array (
            'data' => $obj->field_locationsite_description_value,
            'class' => array (
            'view-locationsite-description' 
            )
          ),
          array (
            'data' => (isset($obj->field_location_region_target_id)? _get_title_of_node($obj->field_location_region_target_id) :''),
            'class' => array (
            'view-locationsite-region' 
            )
          ),
          array (
            'data' => $action,
            'class' => array (
            'view-locationsite-action' 
            )
          ),
          ),
          'class' => array (
            'listing-row-' . $obj->nid 
          )
        );
      }
    }
  }

  if ($type == 'fm_facility') {
    $query = db_select('node','n');
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->leftjoin('field_data_field_facility_description','fsd','fsd.entity_id=n.nid');  
    $query->leftjoin('field_data_field_facility_location_site','flsite','flsite.entity_id=n.nid');
    $query->leftjoin('field_data_field_location_region','flre','flre.entity_id=flsite.field_facility_location_site_target_id');

    if (!empty($top_arg)) {
      $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
      $query->condition('cmt.field_cm_type_value', $top_arg);
    }

    $query->fields('n',array('nid','title','type'));
    $query->fields('fsd',array('field_facility_description_value'));  
    $query->fields('flsite',array('field_facility_location_site_target_id'));
      $query->fields('flre',array('field_location_region_target_id'));

    if(isset($currentComNid) && !empty($currentComNid) && $currentComNid != 0){
      $query->condition('ogm.gid',$currentComNid,'=');
    }

    if(isset($currentUserUid) && !empty($currentUserUid) && $currentUserUid != 0){
      $query->condition('n.uid',$currentUserUid,'=');
    }

    $query->condition('n.type',$type,'=');
    $result = $query->execute()->fetchAllAssoc('nid');

    if ($result && ! empty ( $result )) {
      foreach ($result as $nid => $obj) {
        $action = '<div class="btn-group hcfm-action-btn">
           <div class="dropdown">
             <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
             <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
             <li>
               '.l('Edit', url('program-loc-action/'.$type.'/'.$obj->nid.'/edit/nojs'), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax','edit-'.$type.'-detail'),'for'=>array($obj->nid))) ).'
             </li>';
             
        if(_asset_loc_node_delete_access($obj->nid,$type) == TRUE){
          $action .= '<li>
               '.l('Inactive', 'javascript:void(0);', array( 'external'=>TRUE)).'
             </li>';
        }
        else{
          $action .= '<li>
               '.l('Delete', url('program-loc-node-delete/nojs/'.$obj->nid . '/' . $top_arg), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'
             </li>';  
        }        
        $action .= '</ul>
           </div>
           </div>';   
      
        $rows [] = array (
          'data' => array (     
          array (
            'data' => $obj->title,
            'class' => array (
            'view-locationfacility-title' 
            )
          ),
          array (
            'data' => $obj->field_facility_description_value,
            'class' => array (
            'view-locationfacility-description' 
            )
          ),
          array (
            'data' => (isset($obj->field_facility_location_site_target_id)? _get_title_of_node($obj->field_facility_location_site_target_id) :''),
            'class' => array (
            'view-locationfacility-site' 
            )
          ),
          array (
            'data' => (isset($obj->field_location_region_target_id)? _get_title_of_node($obj->field_location_region_target_id) :''),
            'class' => array (
            'view-locationfacility-region' 
            )
          ),
          array (
            'data' => $action,
            'class' => array (
            'view-locationfacility-action' 
            )
          ),      
          ),
          'class' => array (
            'listing-row-' . $obj->nid 
          ) 
        );
      }
    }
  }

  if ($type == 'fm_location_location') {
    $query = db_select('node','n');
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->leftjoin('field_data_field_location_description','fsd','fsd.entity_id=n.nid');
    $query->leftjoin('field_data_field_location_facility','flfacility','flfacility.entity_id=n.nid');
    $query->leftjoin('field_data_field_facility_location_site','flsite','flsite.entity_id=flfacility.field_location_facility_target_id');
    $query->leftjoin('field_data_field_location_region','flre','flre.entity_id=flsite.field_facility_location_site_target_id');

    if (!empty($top_arg)) {
      $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
      $query->condition('cmt.field_cm_type_value', $top_arg);
    }

    $query->fields('n',array('nid','title','type'));
    $query->fields('fsd',array('field_location_description_value'));
    $query->fields('flfacility',array('field_location_facility_target_id'));
    $query->fields('flsite',array('field_facility_location_site_target_id'));
    $query->fields('flre',array('field_location_region_target_id'));

    if(isset($currentComNid) && !empty($currentComNid) && $currentComNid != 0){
      $query->condition('ogm.gid',$currentComNid,'=');
    }

    if(isset($currentUserUid) && !empty($currentUserUid) && $currentUserUid != 0){
      $query->condition('n.uid',$currentUserUid,'=');
    }

    $query->condition('n.type',$type,'=');
    $result = $query->execute()->fetchAllAssoc('nid');

    if ($result && ! empty ( $result )) {
      foreach ($result as $nid => $obj) {
        $action = '<div class="btn-group hcfm-action-btn">
           <div class="dropdown">
             <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
             <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
             <li>
               '.l('Edit', url('program-loc-action/'.$type.'/'.$obj->nid.'/edit/nojs'), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax','edit-'.$type.'-detail'),'for'=>array($obj->nid))) ).'
             </li>';
             
        if(_asset_loc_node_delete_access($obj->nid,$type) == TRUE){
          $action .= '<li>
               '.l('Inactive', 'javascript:void(0);', array( 'external'=>TRUE)).'
             </li>';
        }
        else{
          $action .= '<li>
               '.l('Delete', url('program-loc-node-delete/nojs/'.$obj->nid . '/' . $top_arg), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'
             </li>';  
        }        
        $action .= '</ul>
           </div>
           </div>';   
      
        $rows [] = array (
          'data' => array (     
          array (
            'data' => $obj->title,
            'class' => array (
            'view-locationlocation-title' 
            )
          ),      
          array (
            'data' => $obj->field_location_description_value,
            'class' => array (
            'view-locationlocation-description' 
            )
          ),
          array (
            'data' => (isset($obj->field_location_facility_target_id)? _get_title_of_node($obj->field_location_facility_target_id) :''),
            'class' => array (
            'view-locationlocation-facility' 
            )
          ),
          array (
            'data' => (isset($obj->field_facility_location_site_target_id)? _get_title_of_node($obj->field_facility_location_site_target_id) :''),
            'class' => array (
            'view-locationlocation-site' 
            )
          ),
          array (
            'data' => (isset($obj->field_location_region_target_id)? _get_title_of_node($obj->field_location_region_target_id) :''),
            'class' => array (
            'view-locationlocation-region' 
            )
          ),
          array (
            'data' => $action,
            'class' => array (
            'view-locationlocation-action' 
            )
          ),      
          ),
          'class' => array (
            'listing-row-' . $obj->nid 
          ) 
        );
      }
    }
  }

  if ($type == 'fm_facility_type') {
    $query = db_select('node','n');
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->leftjoin('field_data_field_facility_type_description','fsd','fsd.entity_id=n.nid');

    if (!empty($top_arg)) {
      $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
      $query->condition('cmt.field_cm_type_value', $top_arg);
    }

    $query->fields('n',array('nid','title','type'));  
    $query->fields('fsd',array('field_facility_type_description_value'));

    if(isset($currentComNid) && !empty($currentComNid) && $currentComNid != 0){
      $query->condition('ogm.gid',$currentComNid,'=');
    }

    if(isset($currentUserUid) && !empty($currentUserUid) && $currentUserUid != 0){
      $query->condition('n.uid',$currentUserUid,'=');
    }

    $query->condition('n.type',$type,'=');
    $result = $query->execute()->fetchAllAssoc('nid');

    if ($result && ! empty ( $result )) {
      foreach ($result as $nid => $obj) {
        $action = '<div class="btn-group hcfm-action-btn">
           <div class="dropdown">
             <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
             <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
             <li>
               '.l('Edit', url('program-loc-action/'.$type.'/'.$obj->nid.'/edit/nojs'), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax','edit-'.$type.'-detail'))) ).'
             </li>';
             
        if(_asset_loc_node_delete_access($obj->nid,$type) == TRUE){     
          $action .= '<li>
               '.l('Inactive', 'javascript:void(0);', array( 'external'=>TRUE)).'
             </li>';
        }
        else{
          $action .= '<li>
               '.l('Delete', url('program-loc-node-delete/nojs/'.$obj->nid . '/' . $top_arg), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'
             </li>';  
        }        
        $action .= '</ul>
           </div>
           </div>'; 
      
        $rows [] = array (
          'data' => array (     
          array (
            'data' => $obj->title,
            'class' => array (
            'view-facilitytype-title' 
            )
          ),
          array (
            'data' => $obj->field_facility_type_description_value,
            'class' => array (
            'view-facilitytype-description' 
            )
          ),
          array (
            'data' => $action,
            'class' => array (
            'view-facilitytype-action' 
            )
          ),      
          ),
          'class' => array (
            'listing-row-' . $obj->nid 
          ) 
        );
      }
    }
  }

  if ($type == 'fm_facility_area_type') {
    $query = db_select('node','n');
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->leftjoin('field_data_field_fareatype_description','fsd','fsd.entity_id=n.nid');

    if (!empty($top_arg)) {
      $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
      $query->condition('cmt.field_cm_type_value', $top_arg);
    }

    $query->fields('n',array('nid','title','type'));
    $query->fields('fsd',array('field_fareatype_description_value'));

    if(isset($currentComNid) && !empty($currentComNid) && $currentComNid != 0){
      $query->condition('ogm.gid',$currentComNid,'=');
    }
    if(isset($currentUserUid) && !empty($currentUserUid) && $currentUserUid != 0){
      $query->condition('n.uid',$currentUserUid,'=');
    }

    $query->condition('n.type',$type,'=');
    $result = $query->execute()->fetchAllAssoc('nid');

    if ($result && ! empty ( $result )) {
      foreach ($result as $nid => $obj) {
        $action = '<div class="btn-group hcfm-action-btn">
           <div class="dropdown">
             <button id="dLabel" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Actions</button>
             <ul class="dropdown-menu" role="menu" aria-labelledby="dLabel">
             <li>
               '.l('Edit', url('program-loc-action/'.$type.'/'.$obj->nid.'/edit/nojs'), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax','edit-'.$type.'-detail'))) ).'
             </li>';
             
        if(_asset_loc_node_delete_access($obj->nid,$type) == TRUE){     
          $action .= '<li>
               '.l('Inactive', 'javascript:void(0);', array( 'external'=>TRUE)).'
             </li>';
        }
        else{
          $action .= '<li>
               '.l('Delete', url('program-loc-node-delete/nojs/'.$obj->nid . '/' . $top_arg), array( 'external'=>TRUE, 'attributes'=> array('class'=>array('use-ajax ctools-modal-assign-dashboard-popup-style ctools-use-modal')))).'
             </li>';  
        }        
        $action .= '</ul>
           </div>
           </div>'; 
      
        $rows [] = array (
          'data' => array (     
          array (
            'data' => $obj->title,
            'class' => array (
            'view-facilityareatype-title' 
            )
          ),
          array (
            'data' => $obj->field_fareatype_description_value,
            'class' => array (
            'view-facilityareatype-description' 
            )
          ),
          array (
            'data' => $action,
            'class' => array (
            'view-facilityareatype-action' 
            )
          ),      
          ),
          'class' => array (
            'listing-row-' . $obj->nid 
          ) 
        );
      }
    }
  }

  $output .= theme ('table', array(
    'header' => $header,
    'rows' => $rows,
    'empty' => 'Not Available Yet',
    'attributes' => array (
      'id' => 'asset-detail-table',
      'class' => array (
          'asset-detail-table',
          'table',
          'table-bordered',
          'm6connect-custom-table',
          'table-hover',
          'table-striped',
          'table-full-width'
       
      )
    ),
    'sticky' => FALSE,
  )
  );
  return $output;
}

/**
 * Helper function to get Node ID (nid) and Node Title by node type.
 */
function asset_loc_nodenid_nodetitle_by_node_type($type = '', $cnid = 0, $uid = 0, $top_arg = '') {
  $output = array();

  if (empty($type)) {
    return $output;
  }
  
  $query = db_select('node', 'n');
  $query->fields('n', array('nid', 'title'));
  $query->orderBy('n.nid', 'DESC');
  
  if (!empty($top_arg)) {
    $query->join('field_data_field_cm_type','cmt','cmt.entity_id=n.nid');
    $query->condition('cmt.field_cm_type_value', $top_arg);
  }

  if(!empty($uid)){
    $query->condition('n.uid', $uid);
  }

  if(!empty($cnid)){
    $query->leftjoin('og_membership','ogm','ogm.etid=n.nid');
    $query->condition('ogm.gid', $cnid);
  }

  $query->condition('n.type', $type);
  $result = $query->execute()->fetchAll();

  if (!empty($result)) {
    foreach($result as $delta){
      $output[$delta->nid] = $delta->title;
    }
  }

  return $output;
}

/**
 * Helper function for processing form
 */
function cost_manager_config_location_facility_container_process($element, &$form_state) {
  global $user,$company;

  $top_arg = 'cpm';
  if (!empty($form_state['top_arg_fs'])) {
    $top_arg = $form_state['top_arg_fs'];
  }
  $element['config_location_facility_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Facitlity Name'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_title'
      )
    ),
    '#required' => TRUE,  
    '#weight' => 0,
    '#prefix' => '<div class="row"><div class="col-md-6">',
    '#suffix' => '</div>',
  );
  
  $locationSite = asset_loc_nodenid_nodetitle_by_node_type('fm_location_site', $company->nid, $user->uid, $top_arg);
  
  $element['config_location_pick_site'] = array(
  '#type' => 'select',
  '#options' => $locationSite,
  '#empty_option' => t('- Select -'),
  '#title' => t('Site'),
  '#attributes' => array(
    'class'=> array(
      'clear-data',
      'config_location_pick_site'
    )
  ),
  //'#required' => TRUE,
  '#weight' => 1,
  '#prefix' => '<div class="col-md-6">',
  '#suffix' => '</div></div>',
  );

  $facility_type = asset_loc_nodenid_nodetitle_by_node_type('fm_facility_type', $company->nid, $user->uid, $top_arg);
  
  $element['config_location_facility_facilitytype'] = array(
    '#type' => 'select',
    '#options' => $facility_type,
    '#empty_option' => t('- Select -'),
    '#title' => t('Facility Type'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_facilitytype'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 2,
    '#prefix' => '<div class="row"><div class="col-md-6">',
    '#suffix' => '</div>',
  );
 
 $element['config_location_facility_employees'] = array(
    '#type' => 'textfield',
    '#title' => t('Occupation'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_employees'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 4,
    '#prefix' => '<div class="col-md-6">',
    '#suffix' => '</div></div>',
  );
  
  $fm_facility_area_type = asset_loc_nodenid_nodetitle_by_node_type('fm_facility_area_type', $company->nid, $user->uid, $top_arg);

  $element['config_location_facility_areatype'] = array(
    '#title' => t('Area Type'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_areatype'
      )
    ),
    '#type' => 'select',
    '#options' => $fm_facility_area_type,
    '#multiple' => TRUE, 
    '#empty_option' => t('- Select -'),
    //'#required' => TRUE,
    '#weight' => 5, 
    '#prefix' => '<div class="row"><div class="col-md-6">',
    '#suffix' => '</div>',
  ); 
  
  $element['config_location_facility_ftes'] = array(
    '#type' => 'textfield',
    '#title' => t('Maintenance FTEs'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_ftes'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 6,
    '#prefix' => '<div class="col-md-6">',
    '#suffix' => '</div></div>',
  );
  
  $element['config_location_facility_description'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_description'
      )
    ),
    '#weight' => 7,
    '#title' => t('Description'),
    '#prefix' => '<div class="row"><div class="col-md-6">',
    '#suffix' => '</div>',
  );
  

  /************************************************************* floor process start *************************************************************/

  //$form_state['cache'] = TRUE;
  if (isset($form_state['option_count'])){
    $choice_count = $form_state['option_count'];
  }
  else{
    $choice_count =  empty($form_state['option']) ? 0 : count($form_state['option']);
  }

  $element['option_wrapper'] = array(
    '#tree' => FALSE,
    '#weight' => 11,
    //'#prefix' => '<div class="clearfix" id="option-wrapper">',
    //'#suffix' => '</div>',
  );
 /*$element['option_wrapper']['client_options'] = array(
  '#type' => 'select',
  '#title' => 'select option',
  '#attributes' => array(
    'class'=> array(
      'config_location_facility_floornumber_select'
    )
  ),
  '#options' => array('1' => 'floor1' , '2' => 'floor2','3' => 'floor3','4' => 'floor4','5' => 'floor5','6' => 'floor6','7' => 'floor7','8' => 'floor8','9' => 'floor9','10' => 'floor10','11' => 'floor11','12' => 'floor12','13' => 'floor13','14' => 'floor14','15' => 'floor15' ),
  '#weight' => 12,
  '#empty_option' => t('- Select -'),
  //'#prefix' => '<div style="display:none">',
  //'#suffix' => '</div>',
  );*/

  $element['option_wrapper']['option'] = array(
    '#prefix' => '<div id="client-options">',
    '#suffix' => '</div>',
    '#weight' => 13,
  );

  if (isset($form_state['option'])){
    $FLOOR = 0;
    $SF = 0;
    foreach ($form_state['option'] as $chid => $option){
      if ($chid % 2 == 0){
      ++$FLOOR;
      $key = 'floor_' . $FLOOR;
      $element['option_wrapper']['option'][$key] = $option;
      }
      else{
      ++$SF;
      $key = 'sf_' . $SF;
      $element['option_wrapper']['option'][$key] = $option;
      }
    }
  }

  $element['config_location_facility_floornumber'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of Floor(s)'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_floornumber'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 8,
    /*'#ajax' => array(
      'callback' => 'facility_floor_process_callback',
      'event' => 'blur',
      'wrapper' => 'workflow-container-section',
      'method' => 'replace',
      'effect' => 'fade',
    ),*/
    '#prefix' => '<div class="col-md-6 config-location-location-numberoffloor"><div class="relative"><div class="config_location_facility_floornumber_input">',
    '#suffix' => '</div>',
  );

  $element['option_wrapper']['client_more'] = array(
    '#type' => 'submit',
    '#value' => t('Go'),
    '#attributes' => array(
      'title' => t("click here to add more options."),
      'class'=> array(
        'config_location_facility_floornumber_addmore'
      ),
    ),
    '#name' => 'floornumber_addmore',
    '#weight' => 13,
    '#limit_validation_errors' => array(array('option')),
    '#submit' => array('cm_facility_floor_more_option_submit'),
    '#ajax' => array(
      'callback' => 'cm_client_option_js',
      'wrapper' => 'client-options',
      'effect' => 'fade',
      ),
    
    '#suffix' => '</div></div></div>',
  );

  $element['config_location_facility_floor_data'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_floor_data'
      )
    ),  
    //'#value' => array('tt'=>41,'pp'=>44), 
  );

  $element['config_location_facility_sf_data'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_sf_data'
      )
    ),  
    //'#value' => array('tt'=>41,'pp'=>44), 
  );
  /************************************************************* floor process end *************************************************************/
  
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;

  $element['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#weight' => 15,
    '#prefix' => '<label>Address</label><div class="project-details-border margin-bottom-10" style="border:1px solid;padding:5px;">',
    '#suffix' => '</div>',
  );

  $element['main-container']['config_location_facility_country'] = array(
    '#type' => 'select',  
    '#title' => t('Country'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_country'
      )
    ),
    '#options' => $countryNamesList1,
    '#empty_option' => t('- Select -'),
    //'#default_value' => 'US',
    '#prefix' => '<div class="col-md-6" style="display:none">',
    '#suffix' => '</div>',
  );
 
  $element['main-container']['config_location_facility_country_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_country_value'
      )
    ),
  );

  $element['main-container']['config_location_facility_address1'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address1'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_address1'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',  
  );

  $element['main-container']['config_location_facility_address2'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address2'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_facility_address2'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );

  $element['main-container']['config_location_facility_city'] = array(
    '#type' => 'textfield', 
    '#title' => t('City'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_facility_city'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );
  //$administrativeNamesList = addressfield_get_administrative_areas('US');
  
  $element['main-container']['config_location_facility_state'] = array(
    '#type' => 'select',  
    '#title' => t('State'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_facility_state'
      )
    ),
    '#options' => _get_asset_loc_default_state(),
    '#validate' => TRUE,
    '#empty_option' => t('- Select -'),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );

  $element['main-container']['config_location_facility_state_key'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_facility_state_key'
      )
    )
  );

  $element['main-container']['config_location_facility_state_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_facility_state_value'
      )
    )
  );

  $element['main-container']['config_location_facility_zipcode'] = array(
    '#type' => 'textfield', 
    '#title' => t('Zip Code'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_zipcode'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );

  $element['facility_area_type_values'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'facility_area_type_values'
      )
    ),
    '#prefix' => '<div style="display:none">',
    '#suffix' => '</div>'
  );

  $element['add_ntype'] = array('#type' => 'value', '#value' => 'fm_facility');

  $element['user_uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'user-uid'
      )
    ),
  );

  $element['company_nid'] = array(
    '#type' => 'value',
    '#value' => $company->nid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'company-nid'
      )
    ),
  );

  $element['fm_facility_node_nid'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'fm_facility_node_nid'
      )
    ),
  );
  
 $element['config_location_facility_address'] = array(
    '#type' => 'hidden',
    '#title' => t('Address'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_facility_address'
      )
    ),
    //'#required' => TRUE,
  );

  $element['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('cm_custom_asset_configure_submit'),
    '#value' => t('Save'),
    '#weight' => 20,
  );

  $element['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit crb-config-location-facility">', 
    '#weight' => 21,   
  );
  
  return $element;
}

/**
 * Helper function to process form data.
 */
function cost_manager_config_location_location_container_process($element, &$form_state) {
  global $user,$company;
  $top_arg = 'cpm';

  if (isset($form_state['top_arg_fs'])) {
    $top_arg = $form_state['top_arg_fs'];
  }

  $locationFacility = asset_loc_nodenid_nodetitle_by_node_type('fm_facility', $company->nid, $user->uid, $top_arg);

  if(isset($_SESSION['location_pick_facility_nid']) && !empty($_SESSION['location_pick_facility_nid'])){
    $location_pick_facility_nid = $_SESSION['location_pick_facility_nid'];
  }

    $element['config_location_pick_facility'] = array(
    '#type' => 'select',
    '#options' => $locationFacility,
    '#empty_option' => t('- Select -'),
    '#title' => t('Facility'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_pick_facility'
      )
    ),
    '#ajax' => array(
      'callback' => 'cm_location_facility_process_callback',
      'event' => 'change',
      'wrapper' => 'workflow-container-section-floor',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    '#required' => TRUE,
    '#weight' => 0,
    '#prefix' => '<div class="row"><div class="col-md-4">',
    '#suffix' => '</div>',
  );
  
  $element['config_location_location_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Zone Name'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_title'
      )
    ),
    '#required' => TRUE,
    '#weight' => 1,
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div><div class="col-md-4 config-location-location-numberoffloor"><div class="relative">',
  );
  
  $NodeObj10 = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'node','Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('nid'),'OtherId'=>array('equal'=>array('type'=>'fm_facility'))); 
  $TableData10 =  _get_asset_loc_db_request($NodeObj10);


  if(isset($TableData10) && !empty($TableData10)){
    $NodeObj11 = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_facility_floor_name','addExpression'=>"CONCAT(entity_id, '_', delta)",'addExpression_value'=>"nid_delta",'Fetch'=>'fetchAllKeyed','CFields'=>'CFields','CFieldsNames'=>array('field_facility_floor_name_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_facility'),'IN'=>array('entity_id'=>$TableData10)));
    $TableData11 =  _get_asset_loc_db_request($NodeObj11);
  }
  
  $element['config_location_location_numberoffloor'] = array(
    '#title' => t('Floor(s)'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_numberoffloor'
      )
    ),
    //'#required' => TRUE,
    '#type' => 'select',
    '#options' => isset($form_state['config_location_location_numberoffloor'])?$form_state['config_location_location_numberoffloor']:$TableData11,
    //'#empty_option' => t('- Select -'),
    '#weight' => 2,
    '#validated' => TRUE,
    '#multiple' => TRUE,
    /*'#ajax' => array(
      'callback' => 'location_floor_process_callback',
      'event' => 'change',
      'wrapper' => 'workflow-container-section',
      'method' => 'fade',
      'effect' => 'change',
    ),*/
    //'#prefix' => '<div class="location_location_numberoffloor_outer"><div class="col-md-3" id="config-location-location-numberoffloor">',
    //'#suffix' => '</div><div class="col-md-1">'.l('<input type="button" value="Go" class="config_location_numberoffloor_btn" />', 'javascript:void(0);', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('class' => array('numberoffloor_btn')))).'</div></div></div>',
    '#prefix' => '<div id="config-location-location-numberoffloor">',
    '#suffix' => '</div>',
  );
  
  
  $element['config_location_location_numberoffloor_btn2'] = array(
    '#markup' =>l('<input type="button" value="Go" class="btn btn-primary config_location_numberoffloor_btn" />', 'javascript:void(0);', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('class' => array('numberoffloor_btn')))),
    //'#suffix' => '<div class="">',
    '#suffix' => '</div></div></div>',
    '#weight' => 3,
  );
  
  
  
  
  $element['location_location_numberoffloor_values'] = array(
    '#type' => 'textfield',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'location_location_numberoffloor_values'
      )
    ),
    '#prefix' => '<div style="display:none">',
    '#suffix' => '</div>'
  );
  $element['config_location_zone_description'] = array(
    '#type' => 'textfield',
    '#title' => t('Zone Description'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_zone_description'
      )
    ),
    //'#default_value' => isset($form['faclitynode_nid']['#value'])?$form['faclitynode_nid']['#value']:'',
    //'#required' => TRUE,
    '#weight' => 4,
    '#prefix' => '<div class="row"><div class="col-md-4">',
    '#suffix' => '</div>',
  );
  $element['config_location_location_roomnumber'] = array(
    '#type' => 'textfield',
    '#title' => t('Room Number'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_roomnumber'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 5,
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );

  $fm_account_number = asset_loc_nodenid_nodetitle_by_node_type('fm_account_number', $company->nid, $user->uid, $top_arg);
  
  $element['config_location_department_number'] = array(
    '#type' => 'select',
    '#options' => $fm_account_number,
    '#empty_option' => t('- Select -'),
    '#title' => t('Department'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_department_number'
      )
    ),
    //'#required' => TRUE,
    '#weight' => 6,
    '#prefix' => '<div class="col-md-4" style="display:none;">',
    '#suffix' => '</div></div>',
  );
  
  
  
    /************************************************************* floor process start *************************************************************/ 

  //$form_state['cache'] = TRUE;
  if (isset($form_state['location_option_count'])){     
    $choice_count = $form_state['location_option_count'];
  }
  else{
    $choice_count =  empty($form_state['location_option']) ? 0 : count($form_state['location_option']);
  }

  $element['location_option_wrapper'] = array(
    '#tree' => FALSE,
    '#weight' => 11,
    '#prefix' => '<div class="clearfix" id="location-option-wrapper">',
    '#suffix' => '</div>',
  );
  $element['location_option_wrapper']['location_client_options'] = array(
    '#type' => 'select',
    '#title' => 'select option',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_floornumber_select'
      )
    ),
    '#options' => array('1' => 'floor1' , '2' => 'floor2','3' => 'floor3','4' => 'floor4','5' => 'floor5','6' => 'floor6','7' => 'floor7','8' => 'floor8','9' => 'floor9','10' => 'floor10','11' => 'floor11','12' => 'floor12','13' => 'floor13','14' => 'floor14','15' => 'floor15','floor'=>'floor' ),
    '#weight' => 12,
    '#empty_option' => t('- Select -'),
    '#prefix' => '<div style="display:none">',
    '#suffix' => '</div>',
  );

  $element['location_option_wrapper']['location_option'] = array(
    '#prefix' => '<div id="location-client-options">',
    '#suffix' => '</div>',
    '#weight' => 13,
  );

  if (isset($form_state['location_option'])) {
    $FLOOR = 0;
    $SF = 0;
    $FLOORRATIO = 0;
    $floorratiovalue =0;
    foreach ($form_state['location_option'] as $chid => $option){
      if ($chid % 4 == 0){
      ++$FLOOR;
      $key = 'floor_' . $FLOOR;
      $element['location_option_wrapper']['location_option'][$key] = $option;
      }
      else if ($chid % 4 == 1){
      ++$SF;
      $key = 'sf_' . $SF;
      $element['location_option_wrapper']['location_option'][$key] = $option;
      }
      else if ($chid % 4 == 2){
      ++$floorratiovalue;
      $key = 'floorratiovalue_' . $floorratiovalue;
      $element['location_option_wrapper']['location_option'][$key] = $option;
      } 
      else if ($chid % 4 == 3){
      ++$FLOORRATIO;
      $key = 'floorratio_' . $FLOORRATIO;
      $element['location_option_wrapper']['location_option'][$key] = $option;
      }
    }
  }

  $element['location_option_wrapper']['location_client_more'] = array(
    '#type' => 'submit',
    '#value' => t('Add options'),
    '#attributes' => array(
      'title' => t("click here to add more options."),
      'class'=> array(
        'config_location_location_floornumber_addmore'
      ),
    ),
    '#name' => 'location_floornumber_addmore',
    '#weight' => 13,
    '#limit_validation_errors' => array(array('option')),
    '#submit' => array('program_location_floor_more_option_submit'),
    '#ajax' => array(
      'callback' => 'cm_location_client_option_js',
      'wrapper' => 'location-client-options',
      'effect' => 'fade',
      ),
    '#prefix' => '<div style="display:none">',
    '#suffix' => '</div>',
  );
  $element['config_location_location_floor_data'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_floor_data'
      )
    ),  
    //'#value' => array('tt'=>41,'pp'=>44), 
  );
  $element['config_location_location_sf_data'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_sf_data'
      )
    ),  
    //'#value' => array('tt'=>41,'pp'=>44), 
  );
  /************************************************************* floor process end *************************************************************/
  
  $countryNamesList = json_decode(file_get_contents("http://country.io/names.json"), true);
  asort($countryNamesList);
  unset($countryNamesList['US']);
  $countryNamesList1 = array('US'=>'United States')+$countryNamesList;
  $element['main-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('row')),
    '#weight' => 15,
    '#prefix' => '<label>Address</label><div class="project-details-border margin-bottom-10" style="border:1px solid;padding:5px;">',
    '#suffix' => '</div>',
  );
  $element['main-container']['config_location_location_country'] = array(
    '#type' => 'select',  
    '#title' => t('Country'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_country'
      )
    ),
    '#options' => $countryNamesList1,
    '#empty_option' => t('- Select -'),
    //'#default_value' => 'US',
    '#prefix' => '<div class="col-md-6" style="display:none">',
    '#suffix' => '</div>',
  );
  $element['main-container']['config_location_location_country_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_country_value'
      )
    ),  
  );
  $element['main-container']['config_location_location_address1'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address1'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_address1'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',  
  );   
  $element['main-container']['config_location_location_address2'] = array(
    '#type' => 'textfield', 
    '#title' => t('Address2'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_address2'
      )
    ),
    '#prefix' => '<div class="col-md-12">',
    '#suffix' => '</div>',
  );
  $element['main-container']['config_location_location_city'] = array(
    '#type' => 'textfield', 
    '#title' => t('City'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_city'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>',
  );
 // $administrativeNamesList = addressfield_get_administrative_areas('US');
  $element['main-container']['config_location_location_state'] = array(
    '#type' => 'select',  
    '#title' => t('State'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_state'
      )
    ),
    '#options' => _get_asset_loc_default_state(),
    '#validate' => TRUE,
    '#empty_option' => t('- Select -'),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $element['main-container']['config_location_location_state_key'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_state_key'
      )
    )
  );
  $element['main-container']['config_location_location_state_value'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_state_value'
      )
    )
  );  
  $element['main-container']['config_location_location_zipcode'] = array(
    '#type' => 'textfield', 
    '#title' => t('Zip Code'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
      'config_location_location_zipcode'
      )
    ),
    '#prefix' => '<div class="col-md-4">',
    '#suffix' => '</div>'
  );
  $element['add_ntype'] = array('#type' => 'value', '#value' => 'fm_location_location');
  $element['user_uid'] = array(
    '#type' => 'value',
    '#value' => $user->uid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'user-uid'
      )
    ),  
  );
  $element['company_nid'] = array(
    '#type' => 'value',
    '#value' => $company->nid,
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'company-nid'
      )
    ),  
  );
  $element['fm_location_location_node_nid'] = array(
    '#type' => 'hidden',
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'fm_location_location_node_nid'
      )
    ),    
  ); 
  
  $element['config_location_location_address'] = array(
    '#type' => 'hidden',
    '#title' => t('Address'),
    '#attributes' => array(
      'class'=> array(
        'clear-data',
        'config_location_location_address'
      )
    ),
    //'#required' => TRUE,
  ); 
  $element['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('cm_custom_asset_configure_submit'),
    '#value' => t('Save'),  
    '#weight' => 20,
  );
  $element['cancel'] = array(
    '#type' => 'markup',
    '#markup' => '<input type="button" value="Cancel" class="form-submit crb-location-location">', 
    '#weight' => 21,   
  );
  return $element;
}

/**
 * Submit handler
 */
function cm_custom_asset_configure_submit($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values'];
  $options = array();

  if($values['add_ntype'] == 'fm_location_region'){
    $options = array('query'=>array('configlocationactivetab'=>'config_location_region'));

    if(isset($values['node_nid']) && !empty($values['node_nid']) && is_numeric($values['node_nid'])){
      $node = node_load($values['node_nid']);
      $node->title = $values['config_location_region_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];

      $node->field_locationregion_description['und'][0]['value'] = $values['config_location_region_description'];   
      if(isset($values['config_location_region_country']) && !empty($values['config_location_region_country']))
        $node->field_locationregion_address['und'][0]['country'] = $values['config_location_region_country'];
      if(isset($values['config_location_region_address1']) && !empty($values['config_location_region_address1']))
        $node->field_locationregion_address['und'][0]['thoroughfare'] = $values['config_location_region_address1'];
      if(isset($values['config_location_region_address2']) && !empty($values['config_location_region_address2']))
        $node->field_locationregion_address['und'][0]['premise'] = $values['config_location_region_address2'];
      if(isset($values['config_location_region_city']) && !empty($values['config_location_region_city']))
        $node->field_locationregion_address['und'][0]['locality'] = $values['config_location_region_city'];
      if(isset($values['config_location_region_state']) && !empty($values['config_location_region_state']))
        $node->field_locationregion_address['und'][0]['administrative_area'] = $values['config_location_region_state'];
      if(isset($values['config_location_region_zipcode']) && !empty($values['config_location_region_zipcode']))
        $node->field_locationregion_address['und'][0]['postal_code'] = $values['config_location_region_zipcode'];

      node_save($node);
    }
    else {
      $node = new stdClass();
      $node->type = $values['add_ntype'];
      $node->title = $values['config_location_region_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];

      $node->field_locationregion_description['und'][0]['value'] = $values['config_location_region_description'];
      if(isset($values['config_location_region_country']) && !empty($values['config_location_region_country']))
        $node->field_locationregion_address['und'][0]['country'] = $values['config_location_region_country'];
      if(isset($values['config_location_region_address1']) && !empty($values['config_location_region_address1']))
        $node->field_locationregion_address['und'][0]['thoroughfare'] = $values['config_location_region_address1'];
      if(isset($values['config_location_region_address2']) && !empty($values['config_location_region_address2']))
        $node->field_locationregion_address['und'][0]['premise'] = $values['config_location_region_address2'];
      if(isset($values['config_location_region_city']) && !empty($values['config_location_region_city']))
        $node->field_locationregion_address['und'][0]['locality'] = $values['config_location_region_city'];
      if(isset($values['config_location_region_state']) && !empty($values['config_location_region_state']))
        $node->field_locationregion_address['und'][0]['administrative_area'] = $values['config_location_region_state'];
      if(isset($values['config_location_region_zipcode']) && !empty($values['config_location_region_zipcode']))
        $node->field_locationregion_address['und'][0]['postal_code'] = $values['config_location_region_zipcode'];
      node_save($node);
    }
  }

  if ($values['add_ntype'] == 'fm_location_site') {
    $options = array('query'=>array('configlocationactivetab'=>'config_location_site'));

    if(isset($values['node_nid']) && !empty($values['node_nid']) && is_numeric($values['node_nid'])){
      $node = node_load($values['node_nid']);
      $node->title = $values['config_location_site_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_locationsite_description['und'][0]['value'] = $values['config_location_site_description'];
      if(isset($values['config_location_pick_region']) && !empty($values['config_location_pick_region']))
        $node->field_location_region['und'][0]['target_id'] = $values['config_location_pick_region'];   
      if(isset($values['config_location_site_country']) && !empty($values['config_location_site_country']))
        $node->field_locationsite_address['und'][0]['country'] = $values['config_location_site_country'];
      if(isset($values['config_location_site_address1']) && !empty($values['config_location_site_address1']))
        $node->field_locationsite_address['und'][0]['thoroughfare'] = $values['config_location_site_address1'];
      if(isset($values['config_location_site_address2']) && !empty($values['config_location_site_address2']))
        $node->field_locationsite_address['und'][0]['premise'] = $values['config_location_site_address2'];
      if(isset($values['config_location_site_city']) && !empty($values['config_location_site_city']))
        $node->field_locationsite_address['und'][0]['locality'] = $values['config_location_site_city'];
      if(isset($values['config_location_site_state']) && !empty($values['config_location_site_state']))
        $node->field_locationsite_address['und'][0]['administrative_area'] = $values['config_location_site_state'];
      if(isset($values['config_location_site_zipcode']) && !empty($values['config_location_site_zipcode']))
        $node->field_locationsite_address['und'][0]['postal_code'] = $values['config_location_site_zipcode'];
      node_save($node);
    }
    else {
      $node = new stdClass();
      $node->type = $values['add_ntype'];
      $node->title = $values['config_location_site_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_locationsite_description['und'][0]['value'] = $values['config_location_site_description'];
      if(isset($values['config_location_pick_region']) && !empty($values['config_location_pick_region']))
        $node->field_location_region['und'][0]['target_id'] = $values['config_location_pick_region'];   
      if(isset($values['config_location_site_country']) && !empty($values['config_location_site_country']))
        $node->field_locationsite_address['und'][0]['country'] = $values['config_location_site_country'];
      if(isset($values['config_location_site_address1']) && !empty($values['config_location_site_address1']))
        $node->field_locationsite_address['und'][0]['thoroughfare'] = $values['config_location_site_address1'];
      if(isset($values['config_location_site_address2']) && !empty($values['config_location_site_address2']))
        $node->field_locationsite_address['und'][0]['premise'] = $values['config_location_site_address2'];
      if(isset($values['config_location_site_city']) && !empty($values['config_location_site_city']))
        $node->field_locationsite_address['und'][0]['locality'] = $values['config_location_site_city'];
      if(isset($values['config_location_site_state']) && !empty($values['config_location_site_state']))
        $node->field_locationsite_address['und'][0]['administrative_area'] = $values['config_location_site_state'];
      if(isset($values['config_location_site_zipcode']) && !empty($values['config_location_site_zipcode']))
        $node->field_locationsite_address['und'][0]['postal_code'] = $values['config_location_site_zipcode'];
      node_save($node);
    }
  }

  if ($values['add_ntype'] == 'fm_facility_type') {
    $options = array('query'=>array('configlocationactivetab'=>'config_location_facilitytype'));

    if (isset($values['facility_type_node_nid']) && !empty($values['facility_type_node_nid']) && is_numeric($values['facility_type_node_nid'])) {
      $node = node_load($values['facility_type_node_nid']);
      $node->title = $values['config_facility_type_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      
      $node->field_facility_type_description['und'][0]['value'] = $values['config_facility_type_description'];
      node_save($node);
    }
    else {
      $node = new stdClass();
      $node->type = 'fm_facility_type';
      $node->title = $values['config_facility_type_title'];
      $node->uid = $user->uid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_facility_type_description['und'][0]['value'] = $values['config_facility_type_description'];
      node_save($node);
    }
  }

  if ($values['add_ntype'] == 'fm_facility_area_type') {
    $options = array('query'=>array('configlocationactivetab'=>'config_location_facilitytype'));

    if(isset($values['facility_area_type_node_nid']) && !empty($values['facility_area_type_node_nid']) && is_numeric($values['facility_area_type_node_nid']) ){
      $node = node_load($values['facility_area_type_node_nid']);
      $node->title = $values['config_facility_area_type_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_fareatype_description['und'][0]['value'] = $values['config_facility_area_type_description'];
      node_save($node);
    }
    else {
      $node = new stdClass();
      $node->type = 'fm_facility_area_type';
      $node->title = $values['config_facility_area_type_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_fareatype_description['und'][0]['value'] = $values['config_facility_area_type_description'];
      node_save($node);
    }
  }

  if($values['add_ntype'] == 'fm_facility'){
    $options = array('query'=>array('configlocationactivetab'=>'config_location_facility'));

    if(isset($values['fm_facility_node_nid']) && !empty($values['fm_facility_node_nid']) && is_numeric($values['fm_facility_node_nid'])){
      $node = node_load($values['fm_facility_node_nid']);
      $node->title = $values['config_location_facility_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_facility_number_of_floor['und'][0]['value'] = $values['config_location_facility_floornumber'];
      $node->field_facility_employees['und'][0]['value'] = $values['config_location_facility_employees'];
      $node->field_facility_ftes['und'][0]['value'] = $values['config_location_facility_ftes'];
      $node->field_facility_description['und'][0]['value'] = $values['config_location_facility_description'];
      if (isset($values['config_location_pick_site']) && !empty($values['config_location_pick_site']))
        $node->field_facility_location_site['und'][0]['target_id'] = $values['config_location_pick_site'];
      if (isset($values['config_location_facility_facilitytype']) && !empty($values['config_location_facility_facilitytype']))
        $node->field_facility_type['und'][0]['target_id'] = $values['config_location_facility_facilitytype'];   
      if (isset($values['config_location_facility_country']) && !empty($values['config_location_facility_country']))
        $node->field_facility_address['und'][0]['country'] = $values['config_location_facility_country'];
      if (isset($values['config_location_facility_address1']) && !empty($values['config_location_facility_address1']))
        $node->field_facility_address['und'][0]['thoroughfare'] = $values['config_location_facility_address1'];
      if (isset($values['config_location_facility_address2']) && !empty($values['config_location_facility_address2']))
        $node->field_facility_address['und'][0]['premise'] = $values['config_location_facility_address2'];
      if (isset($values['config_location_facility_city']) && !empty($values['config_location_facility_city']))
        $node->field_facility_address['und'][0]['locality'] = $values['config_location_facility_city'];
      if (isset($values['config_location_facility_state']) && !empty($values['config_location_facility_state']))
        $node->field_facility_address['und'][0]['administrative_area'] = $values['config_location_facility_state'];
      if (isset($values['config_location_facility_zipcode']) && !empty($values['config_location_facility_zipcode']))
        $node->field_facility_address['und'][0]['postal_code'] = $values['config_location_facility_zipcode'];
      if (isset($values['config_location_facility_areatype']) && !empty($values['config_location_facility_areatype'])) {
        $node->field_facility_area_type = '';
        $FareaType = 0;
        foreach($values['config_location_facility_areatype'] as $FatValue){
          $node->field_facility_area_type['und'][$FareaType]['target_id'] = $FatValue;
          $FareaType++;
        }
      }
      if(isset($values['config_location_facility_floornumber']) && !empty($values['config_location_facility_floornumber']) && is_numeric($values['config_location_facility_floornumber'])){
      $node->field_facility_floor_name = '';
      $node->field_facility_floor_square_feet = '';
      $floor_sf = 1;
          for($i=0; $i<$values['config_location_facility_floornumber']; $i++){
        if(isset($values['floor_'.$floor_sf]) && isset($values['sf_'.$floor_sf])){
            $node->field_facility_floor_name['und'][$i]['value'] = $values['floor_'.$floor_sf];     
          $node->field_facility_floor_square_feet['und'][$i]['value'] = $values['sf_'.$floor_sf];
        }
        $floor_sf++;  
        }
      }
      
      node_save($node);
    }
    else {
      $node = new stdClass();
      $node->title = $values['config_location_facility_title'];
      $node->uid = $user->uid;
      $node->type = $values['add_ntype'];
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_facility_number_of_floor['und'][0]['value'] = $values['config_location_facility_floornumber'];
      $node->field_facility_employees['und'][0]['value'] = $values['config_location_facility_employees'];
      $node->field_facility_ftes['und'][0]['value'] = $values['config_location_facility_ftes'];
      $node->field_facility_description['und'][0]['value'] = $values['config_location_facility_description'];
      if (isset($values['config_location_pick_site']) && !empty($values['config_location_pick_site']))
        $node->field_facility_location_site['und'][0]['target_id'] = $values['config_location_pick_site'];
      if (isset($values['config_location_facility_facilitytype']) && !empty($values['config_location_facility_facilitytype']))
        $node->field_facility_type['und'][0]['target_id'] = $values['config_location_facility_facilitytype'];   
      if (isset($values['config_location_facility_country']) && !empty($values['config_location_facility_country']))
        $node->field_facility_address['und'][0]['country'] = $values['config_location_facility_country'];
      if (isset($values['config_location_facility_address1']) && !empty($values['config_location_facility_address1']))
        $node->field_facility_address['und'][0]['thoroughfare'] = $values['config_location_facility_address1'];
      if (isset($values['config_location_facility_address2']) && !empty($values['config_location_facility_address2']))
        $node->field_facility_address['und'][0]['premise'] = $values['config_location_facility_address2'];
      if (isset($values['config_location_facility_city']) && !empty($values['config_location_facility_city']))
        $node->field_facility_address['und'][0]['locality'] = $values['config_location_facility_city'];
      if (isset($values['config_location_facility_state']) && !empty($values['config_location_facility_state']))
        $node->field_facility_address['und'][0]['administrative_area'] = $values['config_location_facility_state'];
      if (isset($values['config_location_facility_zipcode']) && !empty($values['config_location_facility_zipcode']))
        $node->field_facility_address['und'][0]['postal_code'] = $values['config_location_facility_zipcode'];
      if (isset($values['config_location_facility_areatype']) && !empty($values['config_location_facility_areatype'])) {
        $node->field_facility_area_type = '';
        $FareaType = 0;
        foreach ($values['config_location_facility_areatype'] as $FatValue) {
          $node->field_facility_area_type['und'][$FareaType]['target_id'] = $FatValue;
          $FareaType++;
        }
      }
      if (isset($values['config_location_facility_floornumber']) && !empty($values['config_location_facility_floornumber']) && is_numeric($values['config_location_facility_floornumber'])) {
        $node->field_facility_floor_name = '';
        $node->field_facility_floor_square_feet = '';
        $floor_sf = 1;
        for ($i = 0; $i < $values['config_location_facility_floornumber']; $i++) {
          if (isset($values['floor_'.$floor_sf]) && isset($values['sf_'.$floor_sf])) {
            $node->field_facility_floor_name['und'][$i]['value'] = $values['floor_'.$floor_sf];
            $node->field_facility_floor_square_feet['und'][$i]['value'] = $values['sf_'.$floor_sf];
          }
          $floor_sf++;
        }
      }
      node_save($node);
    }
  }

  if ($values['add_ntype'] == 'fm_location_location') {
    $options = array('query'=>array('configlocationactivetab'=>'config_location_location'));

    if (isset($values['fm_location_location_node_nid']) && !empty($values['fm_location_location_node_nid']) && is_numeric($values['fm_location_location_node_nid'])) {
      $node = node_load($values['fm_location_location_node_nid']);
      $node->title = $values['config_location_location_title'];
      $node->uid = $user->uid;
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_location_description['und'][0]['value'] = $values['config_location_zone_description'];
      $node->field_location_room_number['und'][0]['value'] = $values['config_location_location_roomnumber'];

      if (isset($values['config_location_pick_facility']) && !empty($values['config_location_pick_facility']))
        $node->field_location_facility['und'][0]['target_id'] = $values['config_location_pick_facility'];
      if (isset($values['config_location_facility_facilitytype']) && !empty($values['config_location_facility_facilitytype']))
        $node->field_location_department['und'][0]['target_id'] = $values['config_location_facility_facilitytype'];
      if (isset($values['config_location_location_country']) && !empty($values['config_location_location_country']))
        $node->field_location_zone_address['und'][0]['country'] = $values['config_location_location_country'];
      if (isset($values['config_location_location_address1']) && !empty($values['config_location_location_address1']))
        $node->field_location_zone_address['und'][0]['thoroughfare'] = $values['config_location_location_address1'];
      if (isset($values['config_location_location_address2']) && !empty($values['config_location_location_address2']))
        $node->field_location_zone_address['und'][0]['premise'] = $values['config_location_location_address2'];
      if (isset($values['config_location_location_city']) && !empty($values['config_location_location_city']))
        $node->field_location_zone_address['und'][0]['locality'] = $values['config_location_location_city'];
      if (isset($values['config_location_location_state']) && !empty($values['config_location_location_state']))
        $node->field_location_zone_address['und'][0]['administrative_area'] = $values['config_location_location_state'];
      if (isset($values['config_location_location_zipcode']) && !empty($values['config_location_location_zipcode']))
        $node->field_location_zone_address['und'][0]['postal_code'] = $values['config_location_location_zipcode'];
      if (isset($values['config_location_location_numberoffloor']) && !empty($values['config_location_location_numberoffloor'])) {
        $FloorCount = count($values['config_location_location_numberoffloor']);
        $node->field_location_floor_count['und'][0]['value'] = $FloorCount; 
        $FCount = 0;
        foreach ($values['config_location_location_numberoffloor'] as $numberoffloorkey=>$vv) {
          $node->field_location_floors['und'][$FCount]['value'] = $numberoffloorkey;
          $FCount ++;
        }
        $locationFloor = 0;
        $node->field_location_floor_name = '';      
        $node->field_location_total_sf = '';
        $node->field_location_sf = '';
        $node->field_location_floor_percentage = '';
        for ($i = 0; $i < $FloorCount; $i++) {
          ++$locationFloor;
          if (isset($values['floor_'.$locationFloor]) && isset($values['sf_'.$locationFloor])) {
            $node->field_location_floor_name['und'][$i]['value'] = $values['floor_'.$locationFloor];
            $node->field_location_total_sf['und'][$i]['value'] = $values['sf_'.$locationFloor];
            $node->field_location_sf['und'][$i]['value'] = check_plain($form_state['input']['floorratiovalue_'.$locationFloor]);
            $node->field_location_floor_percentage['und'][$i]['value'] = check_plain($form_state['input']['floorratio_'.$locationFloor]);
          }
          ++$FCount;
        }
      }
      
      node_save($node);
    }
    else {
      $node = new stdClass();
      $node->title = $values['config_location_location_title'];
      $node->uid = $user->uid;
      $node->type = $values['add_ntype'];
      $node->og_group_ref['und'][0]['target_id'] = $company->nid;
      $node->field_cm_type['und'][0]['value'] = $values['top_arg'];
      $node->field_location_description['und'][0]['value'] = $values['config_location_zone_description'];
      $node->field_location_room_number['und'][0]['value'] = $values['config_location_location_roomnumber'];
      if (isset($values['config_location_pick_facility']) && !empty($values['config_location_pick_facility']))
        $node->field_location_facility['und'][0]['target_id'] = $values['config_location_pick_facility'];
      if (isset($values['config_location_facility_facilitytype']) && !empty($values['config_location_facility_facilitytype']))
        $node->field_location_department['und'][0]['target_id'] = $values['config_location_facility_facilitytype'];    
      if (isset($values['config_location_location_country']) && !empty($values['config_location_location_country']))
        $node->field_location_zone_address['und'][0]['country'] = $values['config_location_location_country'];
      if (isset($values['config_location_location_address1']) && !empty($values['config_location_location_address1']))
        $node->field_location_zone_address['und'][0]['thoroughfare'] = $values['config_location_location_address1'];
      if (isset($values['config_location_location_address2']) && !empty($values['config_location_location_address2']))
        $node->field_location_zone_address['und'][0]['premise'] = $values['config_location_location_address2'];
      if (isset($values['config_location_location_city']) && !empty($values['config_location_location_city']))
        $node->field_location_zone_address['und'][0]['locality'] = $values['config_location_location_city'];
      if (isset($values['config_location_location_state']) && !empty($values['config_location_location_state']))
        $node->field_location_zone_address['und'][0]['administrative_area'] = $values['config_location_location_state'];
      if (isset($values['config_location_location_zipcode']) && !empty($values['config_location_location_zipcode']))
        $node->field_location_zone_address['und'][0]['postal_code'] = $values['config_location_location_zipcode'];    
      if (isset($values['config_location_location_numberoffloor']) && !empty($values['config_location_location_numberoffloor'])) {
        $FloorCount = count($values['config_location_location_numberoffloor']);
        $node->field_location_floor_count['und'][0]['value'] = $FloorCount; 
        $FCount = 0;
        foreach($values['config_location_location_numberoffloor'] as $numberoffloorkey=>$vv){
          $node->field_location_floors['und'][$FCount]['value'] = $numberoffloorkey;
          $FCount ++;
        }
        $locationFloor = 0;
        $node->field_location_floor_name = '';
        $node->field_location_total_sf = '';
        $node->field_location_sf = '';
        $node->field_location_floor_percentage = '';
        for ($i = 0; $i < $FloorCount; $i++){
          ++$locationFloor;
          if(isset($values['floor_'.$locationFloor]) && isset($values['sf_'.$locationFloor])){
            $node->field_location_floor_name['und'][$i]['value'] = $values['floor_'.$locationFloor];
            $node->field_location_total_sf['und'][$i]['value'] = $values['sf_'.$locationFloor];
            $node->field_location_sf['und'][$i]['value'] = check_plain($form_state['input']['floorratiovalue_'.$locationFloor]);
            $node->field_location_floor_percentage['und'][$i]['value'] = check_plain($form_state['input']['floorratio_'.$locationFloor]);
          }
          ++$FCount;
        }
      }
      node_save($node);
    }
  }

  $current_path = current_path();
  $form_state['redirect'] = array($current_path, $options);
}

/**
 * Helper function to delete nodes from program location.
 */
function prog_loc_node_delete_custom_callback($ajax, $nodeId = 0, $top_arg = '') {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'node_id' => $nodeId,
      'top_arg' => $top_arg,
    );
    $output = ctools_modal_form_wrapper('prog_loc_node_delete_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('prog_loc_node_delete_form', $nodeId, $top_arg);
}

/**
 * Form callback for node delete in program location.
 */
function prog_loc_node_delete_form($form, &$form_state, $nodeId = 0, $top_arg = '') {
  if(empty($nodeId)) {
    $nodeId = $form_state['node_id'];
  }
  if (empty($top_arg)) {
    $top_arg = $form_state['top_arg'];
  }
  $form['node_action_title'] = array(
    '#type' => 'markup',
    '#title' => t('status'),
    '#markup' => '<div class="group-action-status"><p>Are you sure you want to delete this Record ?</p></div>', 
  );
  $form['node_id'] = array(
    '#type' => 'hidden',
    '#value' => $nodeId, 
  );
  $form['top_arg'] = array(
    '#type' => 'hidden',
    '#value' => $top_arg, 
  );
  $form['submit_action_dgroup'] = array(
    '#type' => 'submit',
    '#value' => t('Confirm')
  );

  $form['submit_action_cancel']['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('group-delete-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),
    '#weight' => 10,
  );
  return $form;
}

/**
 * Submit handler for prog_loc_node_delete_form().
 */
function prog_loc_node_delete_form_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $options = array();
  $nodeId = $form_values['node_id'];
  $nodeType = _get_node_type_by_nid($nodeId);
  $top_arg = $form_values['top_arg'];

  $middle_arg = '';
  if ($top_arg == 'cm') {
    $middle_arg = 'cm/';
  }
  elseif ($top_arg == 'cr') {
    $middle_arg = 'cr/';
  }

  if($nodeType == 'fm_location_site') {
    $url = 'program/' . $middle_arg . 'location';
    $options = array('query'=>array('configlocationactivetab'=>'config_location_site'));
  }

  if($nodeType == 'fm_location_region') {
    $url = 'program/' . $middle_arg . 'location';
    $options = array('query'=>array('configlocationactivetab'=>'config_location_region'));
  }

  if($nodeType == 'fm_facility_type' || $nodeType == 'fm_facility_area_type') {
    $url = 'program/' . $middle_arg . 'location';
    $options = array('query'=>array('configlocationactivetab'=>'config_location_facilitytype'));
  }

  if(!empty($nodeId)) {
    node_delete($nodeId);
    drupal_set_message('Record has been deleted successfully!');
    if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
      $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
      $form_state['ajax_commands'][] = ctools_ajax_command_redirect($url, $delay = 0, $options);
    }
  }
}

/**
 * Ajax callback for facility form.
 */
function cm_facility_floor_more_option_submit($form, &$form_state) {
  $select = $form_state['input']['config_location_facility_floornumber'];

  $build = '';
  if (isset($form_state['triggering_element']['#value']) && !empty($form_state['triggering_element']['#value'])) {
    if (!empty($select) && is_numeric($select)) {
      $form_state['option_count'] = $select;
      $selectM = $select * 2;
      $FLOOR = 0;
      $SF = 0;
      $FLOOR1 = 0;
      $SF1 = 0;

      for ($j = 0; $j < $selectM; $j++){
        if ($j % 2 == 0){
          ++$FLOOR;
          
          $build[$j] =  array(
          '#type' => 'textfield',
          '#title' => 'Floor Name',
          '#name' => 'floor_'.$FLOOR,
          //'#parents' => array('facility_floor',$FLOOR,'floor_'.$FLOOR),
          '#attributes' => array(
            'class'=> array(
              'config_location_facility_floor_'.$FLOOR1
            ),
          ),
          '#required' => TRUE,
          '#prefix' => '<div class="row"><div class="col-md-6">',
          '#suffix' => '</div>',
          );
          $FLOOR1++;
        }
        else {
          ++$SF;    
          $build[$j] = array(
          '#type' => 'textfield',
          '#title' => 'SF',
          '#name' => 'sf_'.$SF,
          //'#parents' => array('facility_floor_sf',$SF,'sf_'.$SF),
          '#attributes' => array(
            'class'=> array(
              'config_location_facility_floorsf_'.$SF1
            ),
          ),
          '#required' => TRUE,
          '#prefix' => '<div class="col-md-6">',
          '#suffix' => '</div></div>',    
          );
          $SF1++;
        }
      }
    }
  }

  $form_state['c'] = $build;
  $form_state['option'] = $form_state['c'];
  unset($form_state['input']['option']);
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for zone form.
 */
function cm_location_facility_process_callback($form, &$form_state) {
  $commands = array();
  $values = $form_state['values'];

  $commands[] = ajax_command_replace("#config-location-location-numberoffloor", render($form['main_container_main']['config_location_location_numberoffloor']));
  
  return array('#type' => 'ajax','#commands' => $commands);
}

/**
 * Ajax callbacks for form.
 */
function cm_client_option_js($form,&$form_state){
  return $form['main_container_main']['option_wrapper']['option'];
}

function cm_location_client_option_js($form,&$form_state){
  //return $form['main_container'];
  return $form['main_container_main']['location_option_wrapper']['location_option'];
}

/**
 * Helper functions.
 */
function _asset_loc_node_delete_access($nid, $type='') {
  $output = '';
  global $company;
  if(!empty($nid) && is_numeric($nid)){
    if(isset($type) && !empty($type) && $type == 'fm_location_region'){
      $db_And = db_or();
      $query = db_select('node','n');

      $query->leftjoin('field_data_field_location_region','fdfasysdd','fdfasysdd.entity_id=n.nid');

      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->condition('om.gid', $company->nid, '=');

      $query->fields('n',array('nid','type','title'));

      $query->condition('fdfasysdd.field_location_region_target_id',$nid,'=');

      $result = $query->execute()->rowCount();
      if (isset($result) && !empty($result) && is_numeric($result)) {
        $output = TRUE;
      }
      else {
        $output = FALSE;
      }
    }
    if (!empty($type) && $type == 'fm_location_site') {
      $db_And = db_or();
      $query = db_select('node','n');

      $query->leftjoin('field_data_field_facility_location_site','fdfasysdd','fdfasysdd.entity_id=n.nid');

      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->condition('om.gid', $company->nid, '=');

      $query->fields('n',array('nid','type','title'));

      $query->condition('fdfasysdd.field_facility_location_site_target_id',$nid,'=');

      $result = $query->execute()->rowCount();
      if (isset($result) && !empty($result) && is_numeric($result)) {
        $output = TRUE;
      }
      else {
        $output = FALSE;
      }
    }
    if (!empty($type) && $type == 'fm_facility_type') {
      $query = db_select('node','n');
      $query->leftjoin('field_data_field_facility_type','fdfasys','fdfasys.entity_id=n.nid');
      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->condition('om.gid', $company->nid, '=');
      $query->fields('n',array('nid','type','title'));
      $query->condition('fdfasys.field_facility_type_target_id',$nid,'=');
      $result = $query->execute()->rowCount();

      if (!empty($result) && is_numeric($result)) {
        $output = TRUE;
      }
      else {
        $output = FALSE;
      }
    }
    if (isset($type) && !empty($type) && $type == 'fm_facility_area_type') {
      $query = db_select('node','n');
      $query->leftjoin('field_data_field_facility_area_type','fdfasys','fdfasys.entity_id=n.nid');
      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->condition('om.gid', $company->nid, '=');
      $query->fields('n',array('nid','type','title'));
      $query->condition('fdfasys.field_facility_area_type_target_id',$nid,'=');
      $result = $query->execute()->rowCount();
      if (isset($result) && !empty($result) && is_numeric($result)) {
        $output = TRUE;
      }
      else{
        $output = FALSE;
      }
    } 
    if (isset($type) && !empty($type) && $type == 'fm_facility') {
      $db_And = db_or();
      $query = db_select('node','n');

      $query->leftjoin('field_data_field_location_facility','fdfasysdd','fdfasysdd.entity_id=n.nid');

      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->condition('om.gid', $company->nid, '=');

      $query->fields('n',array('nid','type','title'));

      $query->condition('fdfasysdd.field_location_facility_target_id',$nid,'=');

      $result = $query->execute()->rowCount();
      if (isset($result) && !empty($result) && is_numeric($result)) {
        $output = TRUE;
      }
      else {
        $output = FALSE;
      }
    }
    if (isset($type) && !empty($type) && $type == 'fm_location_location') {
      return FALSE;
      $db_And = db_or();
      $query = db_select('node','n');

      $query->join('og_membership','om','om.etid=n.nid AND om.entity_type=:entityType', array(':entityType'=>'node'));
      $query->condition('om.gid', $company->nid, '=');
      
      $query->fields('n',array('nid','type','title'));

      $query->condition('n.type', $type);

      $result = $query->execute()->rowCount();
      
      if (isset($result) && !empty($result) && is_numeric($result)) {
        $output = TRUE;
      }
      else {
        $output = FALSE;
      }
    }
  }
  return $output;
}

function _get_asset_loc_db_request($NodeObj, $JoinField='') {
  $ReturnObj = '';
  //if($NodeObj['NodeType'] == 'asset'){
    $params = array('request'=>'request','NodeObj'=>$NodeObj,'JoinField'=>$JoinField );
  if(isset($params)&& !empty($params['request']) &&  isset($params['NodeObj']) && !empty($params['NodeObj'])){
    $NodeNid = (isset($params['NodeObj']['NodeNid'])?$params['NodeObj']['NodeNid']:'');
    $OgNodeNid = (isset($params['NodeObj']['OgNodeNid'])?$params['NodeObj']['OgNodeNid']:'');
    $OgUserUid = (isset($params['NodeObj']['OgUserUid'])?$params['NodeObj']['OgUserUid']:'');
    $OtherId = (isset($params['NodeObj']['OtherId'])?$params['NodeObj']['OtherId']:'');
    $NodeNidMulti = (isset($params['NodeObj']['NodeNidMulti'])?$params['NodeObj']['NodeNidMulti']:'');
    $UserUid = (isset($params['NodeObj']['UserUid'])?$params['NodeObj']['UserUid']:'');
    $UserUidMulti = (isset($params['NodeObj']['UserUidMulti'])?$params['NodeObj']['UserUidMulti']:'');
    $NodeType = (isset($params['NodeObj']['NodeType'])?$params['NodeObj']['NodeType']:'');
    $TableJoin = (isset($params['NodeObj']['TableJoin'])?$params['NodeObj']['TableJoin']:'');
    if(isset($NodeType) && !empty($NodeType)){
    
    if($TableJoin == 'TableJoin' && isset($params['NodeObj']['TableName']) && !empty($params['NodeObj']['TableName'])){
      $query= db_select($params['NodeObj']['TableName'], 'n');
      if(isset($params['NodeObj']['CFields']) && $params['NodeObj']['CFields'] == 'CFields'){
       $query->fields('n',$params['NodeObj']['CFieldsNames']); 
      }else{
        $query->fields('n');
      }
      if(isset($params['NodeObj']['TableRowId']) && !empty($params['NodeObj']['TableRowId']) && is_numeric($params['NodeObj']['TableRowId'])){
      $query->condition('n.id', $params['NodeObj']['TableRowId'], '=');
      }
    }
    else{
      $query= db_select('node', 'n');
      if($OgNodeNid && !empty($OgNodeNid)){
      $query->leftjoin('og_membership','nogm','nogm.etid=n.nid');     
      $query->condition('nogm.gid', $OgNodeNid, '=');
      }
      if($OgUserUid && !empty($OgUserUid)){
      $query->condition('n.uid', $OgUserUid, '=');
      }      
      $query->fields('n',array('nid','type','title','uid','status'));
      if(isset($params['JoinField']) && !empty($params['JoinField'])){
      foreach($params['JoinField'] as $fkey=>$fjoin){
        $field1 = str_replace("field_data_","",$fjoin);
        $field2 = explode('-',$fkey);
        $exField = $field1.$field2[1];
        $query->leftjoin($fjoin,$field2[0],$field2[0].'.entity_id=n.nid');
        $query->fields($field2[0],array($exField));     
      }
      }
      
      //if(!isset($params['NodeObj']['NodeStatus']) && $params['NodeObj']['NodeStatus'] ==0){   
      //$query->condition('n.status', 1, '=');
      //}
    }
     
    if(isset($params['NodeObj']['addExpression']) && !empty($params['NodeObj']['addExpression']) && isset($params['NodeObj']['addExpression_value']) && !empty($params['NodeObj']['addExpression_value'])){
      $query->addExpression($params['NodeObj']['addExpression'],$params['NodeObj']['addExpression_value']); 
    }
    if(isset($OtherId) && !empty($OtherId) && array_key_exists('equal', $OtherId)){
      foreach($OtherId['equal'] as $OtherKey=>$OtherValue){     
      $query->condition('n.'.$OtherKey, $OtherValue, '=');    
      }
    }
    if(isset($OtherId) && !empty($OtherId) && array_key_exists('IN', $OtherId)){
      foreach($OtherId['IN'] as $OtherKey=>$OtherValue){      
      $query->condition('n.'.$OtherKey, $OtherValue, 'IN');   
      }
    }
    
    if($NodeType != 'NoType'){
      $query->condition('n.type', $NodeType, '=');
    }
    if($NodeNid){
      $query->condition('n.nid', $NodeNid, '=');
    }
    elseif($NodeNidMulti){
      $query->condition('n.nid', $NodeNidMulti, 'IN');
    }  
    if($UserUid){
          $query->condition('n.uid', $UserUid, '=');
        }
    elseif($UserUidMulti){
      $query->condition('n.uid', $UserUidMulti, 'IN');
    }
    if(isset($params['NodeObj']['OrderBy']) && !empty($params['NodeObj']['OrderBy'])){
      foreach($params['NodeObj']['OrderBy'] as $OrderBy=>$OrderWith){
      $query->orderBy($OrderBy, $OrderWith);
      }
    }
        
    if(isset($params['NodeObj']['Fetch']) && $params['NodeObj']['Fetch'] == 'fetchAssoc'){
      $ReturnObj = $query->execute()->$params['NodeObj']['Fetch']();
    }
    else if(isset($params['NodeObj']['Fetch']) && $params['NodeObj']['Fetch'] == 'fetchCol'){
      $ReturnObj = $query->execute()->$params['NodeObj']['Fetch']();
    }else if(isset($params['NodeObj']['Fetch']) && $params['NodeObj']['Fetch'] == 'fetchAllKeyed'){
      $ReturnObj = $query->execute()->$params['NodeObj']['Fetch']();
    }
    else if(isset($params['NodeObj']['Fetch']) && $params['NodeObj']['Fetch'] == 'fetchColumn'){
      $ReturnObj = $query->execute()->$params['NodeObj']['Fetch'](0);
    }
    else{
      $ReturnObj = $query->execute()->fetchAll();
    }
    }
    $postData = json_encode($ReturnObj);
      $ReturnObj = json_decode($postData ,TRUE);      
  }
  /*}
  else{
    global $d8base_url;
  $data = array('request'=>'request','NodeObj'=>$NodeObj,'JoinField'=>$JoinField );
  //drup_msg($data);
  $postData = json_encode($data);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $d8base_url."/hcfm/dbrequest");
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($ch, CURLOPT_POST, true);
  curl_setopt($ch, CURLOPT_POSTFIELDS, $postData);
  curl_setopt($ch, CURLOPT_HEADER, false);  
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
    'Content-Type: application/json',                                                                                
    'Content-Length: ' . strlen($postData)                                                                       
  ));         
  // execute the request  
  $output = curl_exec($ch);   
  //drup_msg($output);
  $ReturnObj = json_decode($output,TRUE);
  }*/
  return $ReturnObj;
}

function _get_asset_loc_default_state(){
  $administrative_areas = array(
    'AZ' => t('Abu Dhabi'),
    'FU' => t('Fujairah'),
    'UQ' => t('Umm al-Quwain'),
    'SH' => t('Sharjah'),
    'DU' => t('Dubai'),
    'RK' => t('Ras al-Khaimah'),
    'AJ' => t('Ajmān'),
    'B' => 'Buenos Aires',
    'K' => 'Catamarca',
    'H' => 'Chaco',
    'U' => 'Chubut',
    'C' => 'Ciudad de Buenos Aires',
    'X' => 'Córdoba',
    'W' => 'Corrientes',
    'E' => 'Entre Ríos',
    'P' => 'Formosa',
    'Y' => 'Jujuy',
    'L' => 'La Pampa',
    'F' => 'La Rioja',
    'M' => 'Mendoza',
    'N' => 'Misiones',
    'Q' => 'Neuquén',
    'R' => 'Río Negro',
    'A' => 'Salta',
    'J' => 'San Juan',
    'D' => 'San Luis',
    'Z' => 'Santa Cruz',
    'S' => 'Santa Fe',
    'G' => 'Santiago del Estero',
    'V' => 'Tierra del Fuego',
    'T' => 'Tucumán',
    'ACT' => 'Australian Capital Territory',
    'NSW' => 'New South Wales',
    'NT' => 'Northern Territory',
    'QLD' => 'Queensland',
    'SA' => 'South Australia',
    'TAS' => 'Tasmania',
    'VIC' => 'Victoria',
    'WA' => 'Western Australia',
    'AC' => 'Acre',
    'AL' => 'Alagoas',
    'AM' => 'Amazonas',
    'AP' => 'Amapá',
    'BA' => 'Bahia',
    'CE' => 'Ceará',
    'DF' => 'Distrito Federal',
    'ES' => 'Espírito Santo',
    'GO' => 'Goiás',
    'MA' => 'Maranhão',
    'MG' => 'Minas Gerais',
    'MS' => 'Mato Grosso do Sul',
    'MT' => 'Mato Grosso',
    'PA' => 'Pará',
    'PB' => 'Paraíba',
    'PE' => 'Pernambuco',
    'PI' => 'Piauí',
    'PR' => 'Paraná',
    'RJ' => 'Rio de Janeiro',
    'RN' => 'Rio Grande do Norte',
    'RO' => 'Rondônia',
    'RR' => 'Roraima',
    'RS' => 'Rio Grande do Sul',
    'SC' => 'Santa Catarina',
    'SE' => 'Sergipe',
    'SP' => 'São Paulo',
    'TO' => 'Tocantins',
    'AB' => t('Alberta'),
    'BC' => t('British Columbia'),
    'MB' => t('Manitoba'),
    'NB' => t('New Brunswick'),
    'NL' => t('Newfoundland and Labrador'),
    'NT' => t('Northwest Territories'),
    'NS' => t('Nova Scotia'),
    'NU' => t('Nunavut'),
    'ON' => t('Ontario'),
    'PE' => t('Prince Edward Island'),
    'QC' => t('Quebec'),
    'SK' => t('Saskatchewan'),
    'YT' => t('Yukon Territory'),
    'AI' => 'Aysén del General Carlos Ibáñez del Campo',
    'AN' => 'Antofagasta',
    'AR' => 'Araucanía',
    'AP' => 'Arica y Parinacota',
    'AT' => 'Atacama',
    'BI' => 'Biobío',
    'CO' => 'Coquimbo',
    'LI' => 'Libertador General Bernardo O\'Higgins',
    'LL' => 'Los Lagos',
    'LR' => 'Los Ríos',
    'MA' => 'Magallanes y de la Antártica Chilena',
    'ML' => 'Maule',
    'RM' => 'Metropolitana de Santiago',
    'TA' => 'Tarapacá',
    'VS' => 'Valparaíso',
    '34' => t('Anhui Sheng'),
    '92' => t('Macau'),
    '11' => t('Beijing Shi'),
    '50' => t('Chongqing Shi'),
    '35' => t('Fujian Sheng'),
    '62' => t('Gansu Sheng'),
    '44' => t('Guangdong Sheng'),
    '45' => t('Guangxi Zhuangzuzizhiqu'),
    '52' => t('Guizhou Sheng'),
    '46' => t('Hainan Sheng'),
    '13' => t('Hebei Sheng'),
    '41' => t('Henan Sheng'),
    '23' => t('Heilongjiang Sheng'),
    '42' => t('Hubei Sheng'),
    '43' => t('Hunan Sheng'),
    '22' => t('Jilin Sheng'),
    '32' => t('Jiangsu Sheng'),
    '36' => t('Jiangxi Sheng'),
    '21' => t('Liaoning Sheng'),
    '15' => t('Neimenggu Zizhiqu'),
    '64' => t('Ningxia Huizuzizhiqu'),
    '63' => t('Qinghai Sheng'),
    '37' => t('Shandong Sheng'),
    '14' => t('Shanxi Sheng'),
    '61' => t('Shaanxi Sheng'),
    '31' => t('Shanghai Shi'),
    '51' => t('Sichuan Sheng'),
    '71' => t('Taiwan'),
    '12' => t('Tianjin Shi'),
    '54' => t('Xizang Zizhiqu'),
    '91' => t('Hong Kong'),
    '65' => t('Xinjiang Weiwuerzizhiqu'),
    '53' => t('Yunnan Sheng'),
    '33' => t('Zhejiang Sheng'),
    'AMA' => 'Amazonas',
    'ANT' => 'Antioquia',
    'ARA' => 'Arauca',
    'ATL' => 'Atlántico',
    'BOL' => 'Bolívar',
    'BOY' => 'Boyacá',
    'CAL' => 'Caldas',
    'CAQ' => 'Caquetá',
    'CAS' => 'Casanare',
    'CAU' => 'Cauca',
    'CES' => 'Cesar',
    'COR' => 'Córdoba',
    'CUN' => 'Cundinamarca',
    'CHO' => 'Chocó',
    'GUA' => 'Guainía',
    'GUV' => 'Guaviare',
    'HUI' => 'Huila',
    'LAG' => 'La Guajira',
    'MAG' => 'Magdalena',
    'MET' => 'Meta',
    'NAR' => 'Nariño',
    'NSA' => 'Norte de Santander',
    'PUT' => 'Putumayo',
    'QUI' => 'Quindío',
    'RIS' => 'Risaralda',
    'SAP' => 'San Andrés, Providencia y Santa Catalina',
    'SAN' => 'Santander',
    'SUC' => 'Sucre',
    'TOL' => 'Tolima',
    'VAC' => 'Valle del Cauca',
    'VAU' => 'Vaupés',
    'VID' => 'Vichada',
    '37' => 'Harjumaa',
    '39' => 'Hiiumaa',
    '44' => 'Ida-Virumaa',
    '49' => 'Jõgevamaa',
    '51' => 'Järvamaa',
    '57' => 'Läänemaa',
    '59' => 'Lääne-Virumaa',
    '65' => 'Põlvamaa',
    '67' => 'Pärnumaa',
    '70' => 'Raplamaa',
    '74' => 'Saaremaa',
    '78' => 'Tartumaa',
    '82' => 'Valgamaa',
    '84' => 'Viljandimaa',
    '86' => 'Võrumaa',
    'ALX' => t('Alexandria'),
    'ASN' => t('Aswan'),
    'AST' => t('Asyut'),
    'BH' => t('Beheira'),
    'BNS' => t('Beni Suef'),
    'C' => t('Cairo'),
    'DK' => t('Dakahlia'),
    'DT' => t('Damietta'),
    'FYM' => t('Faiyum'),
    'GH' => t('Gharbia'),
    'GZ' => t('Giza'),
    'IS' => t('Ismailia'),
    'KFS' => t('Kafr el-Sheikh'),
    'MT' => t('Matruh'),
    'MN' => t('Minya'),
    'MNF' => t('Monufia'),
    'WAD' => t('New Valley'),
    'SIN' => t('North Sinai'),
    'PTS' => t('Port Said'),
    'KB' => t('Qalyubia'),
    'KN' => t('Qena'),
    'BA' => t('Red Sea'),
    'SHR' => t('Sharqia'),
    'SHG' => t('Sohag'),
    'JS' => t('South Sinai'),
    'SUZ' => t('Suez'),
    'LX' => t('Luxor'),
    'C' => "A Coruña",
    'VI' => 'Alava',
    'AB' => 'Albacete',
    'A' => 'Alicante',
    'AL' => "Almería",
    'O' => 'Asturias',
    'AV' => "Ávila",
    'BA' => 'Badajoz',
    'PM' => 'Baleares',
    'B' => 'Barcelona',
    'BU' => 'Burgos',
    'CC' => "Cáceres",
    'CA' => "Cádiz",
    'S' => 'Cantabria',
    'CS' => "Castellón",
    'CE' => 'Ceuta',
    'CR' => 'Ciudad Real',
    'CO' => "Córdoba",
    'CU' => 'Cuenca',
    'GI' => 'Girona',
    'GR' => 'Granada',
    'GU' => 'Guadalajara',
    'SS' => "Guipúzcoa",
    'H' => 'Huelva',
    'HU' => 'Huesca',
    'J' => "Jaén",
    'LO' => 'La Rioja',
    'GC' => 'Las Palmas',
    'LE' => "León",
    'L' => "Lleida",
    'LU' => 'Lugo',
    'M' => 'Madrid',
    'MA' => "Málaga",
    'ML' => 'Melilla',
    'MU' => 'Murcia',
    'NA' => 'Navarra',
    'OR' => 'Ourense',
    'P' => 'Palencia',
    'PO' => 'Pontevedra',
    'SA' => 'Salamanca',
    'TF' => 'Santa Cruz de Tenerife',
    'SG' => 'Segovia',
    'SE' => 'Sevilla',
    'SO' => 'Soria',
    'T' => 'Tarragona',
    'TE' => 'Teruel',
    'TO' => 'Toledo',
    'V' => 'Valencia',
    'VA' => 'Valladolid',
    'BI' => 'Vizcaya',
    'ZA' => 'Zamora',
    'Z' => 'Zaragoza',
    'Kowloon' => t('Kowloon'),
    'Hong Kong Island' => t('Hong Kong Island'),
    'New Territories' => t('New Territories'),
    'AC' => t('Aceh'),
    'BA' => t('Bali'),
    'BB' => t('Bangka Belitung'),
    'BT' => t('Banten'),
    'BE' => t('Bengkulu'),
    'JK' => t('DKI Jakarta'),
    'YO' => t('D.I. Yogyakarta'),
    'GO' => t('Gorontalo'),
    'JA' => t('Jambi'),
    'JB' => t('Jawa Barat'),
    'JT' => t('Jawa Tengah'),
    'JI' => t('Jawa Timur'),
    'KB' => t('Kalimantan Barat'),
    'KS' => t('Kalimantan Selatan'),
    'KT' => t('Kalimantan Tengah'),
    'KI' => t('Kalimantan Timur'),
    'KR' => t('Kepulauan Riau'),
    'LA' => t('Lampung'),
    'MA' => t('Maluku'),
    'MU' => t('Maluku Utara'),
    'NB' => t('Nusa Tenggara Barat'),
    'NT' => t('Nusa Tenggara Timur'),
    'PA' => t('Papua'),
    'PB' => t('Papua Barat'),
    'RI' => t('Riau'),
    'SR' => t('Sulawesi Barat'),
    'SN' => t('Sulawesi Selatan'),
    'ST' => t('Sulawesi Tengah'),
    'SG' => t('Sulawesi Tenggara'),
    'SA' => t('Sulawesi Utara'),
    'SB' => t('Sumatera Barat'),
    'SS' => t('Sumatera Selatan'),
    'SU' => t('Sumatera Utara'),
    'CW' => 'Co Carlow',
    'CN' => 'Co Cavan',
    'CE' => 'Co Clare',
    'CO' => 'Co Cork',
    'DL' => 'Co Donegal',
    'D' => 'Co Dublin',
    'D1' => 'Dublin 1',
    'D2' => 'Dublin 2',
    'D3' => 'Dublin 3',
    'D4' => 'Dublin 4',
    'D5' => 'Dublin 5',
    'D6' => 'Dublin 6',
    'D6W' => 'Dublin 6w',
    'D7' => 'Dublin 7',
    'D8' => 'Dublin 8',
    'D9' => 'Dublin 9',
    'D10' => 'Dublin 10',
    'D11' => 'Dublin 11',
    'D12' => 'Dublin 12',
    'D13' => 'Dublin 13',
    'D14' => 'Dublin 14',
    'D15' => 'Dublin 15',
    'D16' => 'Dublin 16',
    'D17' => 'Dublin 17',
    'D18' => 'Dublin 18',
    'D19' => 'Dublin 19',
    'D20' => 'Dublin 20',
    'D21' => 'Dublin 21',
    'D22' => 'Dublin 22',
    'D23' => 'Dublin 23',
    'D24' => 'Dublin 24',
    'G' => 'Co Galway',
    'KY' => 'Co Kerry',
    'KE' => 'Co Kildare',
    'KK' => 'Co Kilkenny',
    'LS' => 'Co Laois',
    'LM' => 'Co Leitrim',
    'LK' => 'Co Limerick',
    'LD' => 'Co Longford',
    'LH' => 'Co Louth',
    'MO' => 'Co Mayo',
    'MH' => 'Co Meath',
    'MN' => 'Co Monaghan',
    'OY' => 'Co Offaly',
    'RN' => 'Co Roscommon',
    'SO' => 'Co Sligo',
    'TA' => 'Co Tipperary',
    'WD' => 'Co Waterford',
    'WH' => 'Co Westmeath',
    'WX' => 'Co Wexford',
    'WW' => 'Co Wicklow',
    'AP' => t('Andhra Pradesh'),
    'AR' => t('Arunachal Pradesh'),
    'AS' => t('Assam'),
    'BR' => t('Bihar'),
    'CT' => t('Chhattisgarh'),
    'GA' => t('Goa'),
    'GJ' => t('Gujarat'),
    'HP' => t('Himachal Pradesh'),
    'HR' => t('Haryana'),
    'JH' => t('Jharkhand'),
    'JK' => t('Jammu & Kashmir'),
    'KA' => t('Karnataka'),
    'KL' => t('Kerala'),
    'MH' => t('Maharashtra'),
    'MN' => t('Manipur'),
    'ML' => t('Meghalaya'),
    'MP' => t('Madhya Pradesh'),
    'MZ' => t('Mizoram'),
    'NL' => t('Nagaland'),
    'OR' => t('Odisha'),
    'PB' => t('Punjab'),
    'RJ' => t('Rajasthan'),
    'SK' => t('Sikkim'),
    'TN' => t('Tamil Nadu'),
    'TG' => t('Telangana'),
    'TR' => t('Tripura'),
    'UP' => t('Uttar Pradesh'),
    'UT' => t('Uttarakhand'),
    'WB' => t('West Bengal'),   
    'AN' => t('Andaman & Nicobar'),
    'CH' => t('Chandigarh'),
    'DN' => t('Dadra & Nagar Haveli'),
    'DD' => t('Daman & Diu'),
    'DL' => t('Delhi'),
    'LD' => t('Lakshadweep'),
    'PY' => t('Puducherry'),
    'AG' => 'Agrigento',
    'AL' => 'Alessandria',
    'AN' => 'Ancona',
    'AO' => 'Aosta',
    'AP' => 'Ascoli Piceno',
    'AQ' => "L'Aquila",
    'AR' => 'Arezzo',
    'AT' => 'Asti',
    'AV' => 'Avellino',
    'BA' => 'Bari',
    'BG' => 'Bergamo',
    'BI' => 'Biella',
    'BL' => 'Belluno',
    'BN' => 'Benevento',
    'BO' => 'Bologna',
    'BR' => 'Brindisi',
    'BS' => 'Brescia',
    'BT' => 'Barletta-Andria-Trani',
    'BZ' => 'Bolzano/Bozen',
    'CA' => 'Cagliari',
    'CB' => 'Campobasso',
    'CE' => 'Caserta',
    'CH' => 'Chieti',
    'CI' => 'Carbonia-Iglesias',
    'CL' => 'Caltanissetta',
    'CN' => 'Cuneo',
    'CO' => 'Como',
    'CR' => 'Cremona',
    'CS' => 'Cosenza',
    'CT' => 'Catania',
    'CZ' => 'Catanzaro',
    'EN' => 'Enna',
    'FC' => 'Forlì-Cesena',
    'FE' => 'Ferrara',
    'FG' => 'Foggia',
    'FI' => 'Firenze',
    'FM' => 'Fermo',
    'FR' => 'Frosinone',
    'GE' => 'Genova',
    'GO' => 'Gorizia',
    'GR' => 'Grosseto',
    'IM' => 'Imperia',
    'IS' => 'Isernia',
    'KR' => 'Crotone',
    'LC' => 'Lecco',
    'LE' => 'Lecce',
    'LI' => 'Livorno',
    'LO' => 'Lodi',
    'LT' => 'Latina',
    'LU' => 'Lucca',
    'MB' => 'Monza e Brianza',
    'MC' => 'Macerata',
    'ME' => 'Messina',
    'MI' => 'Milano',
    'MN' => 'Mantova',
    'MO' => 'Modena',
    'MS' => 'Massa-Carrara',
    'MT' => 'Matera',
    'NA' => 'Napoli',
    'NO' => 'Novara',
    'NU' => 'Nuoro',
    'OG' => 'Ogliastra',
    'OR' => 'Oristano',
    'OT' => 'Olbia-Tempio',
    'PA' => 'Palermo',
    'PC' => 'Piacenza',
    'PD' => 'Padova',
    'PE' => 'Pescara',
    'PG' => 'Perugia',
    'PI' => 'Pisa',
    'PN' => 'Pordenone',
    'PO' => 'Prato',
    'PR' => 'Parma',
    'PT' => 'Pistoia',
    'PU' => 'Pesaro e Urbino',
    'PV' => 'Pavia',
    'PZ' => 'Potenza',
    'RA' => 'Ravenna',
    'RC' => 'Reggio Calabria',
    'RE' => 'Reggio Emilia',
    'RG' => 'Ragusa',
    'RI' => 'Rieti',
    'RM' => 'Roma',
    'RN' => 'Rimini',
    'RO' => 'Rovigo',
    'SA' => 'Salerno',
    'SI' => 'Siena',
    'SO' => 'Sondrio',
    'SP' => 'La Spezia',
    'SR' => 'Siracusa',
    'SS' => 'Sassari',
    'SV' => 'Savona',
    'TA' => 'Taranto',
    'TE' => 'Teramo',
    'TN' => 'Trento',
    'TO' => 'Torino',
    'TP' => 'Trapani',
    'TR' => 'Terni',
    'TS' => 'Trieste',
    'TV' => 'Treviso',
    'UD' => 'Udine',
    'VA' => 'Varese',
    'VB' => 'Verbano-Cusio-Ossola',
    'VC' => 'Vercelli',
    'VE' => 'Venezia',
    'VI' => 'Vicenza',
    'VR' => 'Verona',
    'VS' => 'Medio Campidano',
    'VT' => 'Viterbo',
    'VV' => 'Vibo Valentia',
    '13' => 'Clarendon',
    '09' => 'Hanover',
    '01' => 'Kingston',
    '12' => 'Manchester',
    '04' => 'Portland',
    '02' => 'St. Andrew',
    '06' => 'St. Ann',
    '14' => 'St. Catherine',
    '11' => 'St. Elizabeth',
    '08' => 'St. James',
    '05' => 'St. Mary',
    '03' => 'St. Thomas',
    '07' => 'Trelawny',
    '10' => 'Westmoreland',
    '01' => t('Hokkaido'),
    '02' => t('Aomori'),
    '03' => t('Iwate'),
    '04' => t('Miyagi'),
    '05' => t('Akita'),
    '06' => t('Yamagata'),
    '07' => t('Fukushima'),
    '08' => t('Ibaraki'),
    '09' => t('Tochigi'),
    '10' => t('Gunma'),
    '11' => t('Saitama'),
    '12' => t('Chiba'),
    '13' => t('Tokyo'),
    '14' => t('Kanagawa'),
    '15' => t('Niigata'),
    '16' => t('Toyama'),
    '17' => t('Ishikawa'),
    '18' => t('Fukui'),
    '19' => t('Yamanashi'),
    '20' => t('Nagano'),
    '21' => t('Gifu'),
    '22' => t('Shizuoka'),
    '23' => t('Aichi'),
    '24' => t('Mie'),
    '25' => t('Shiga'),
    '26' => t('Kyoto'),
    '27' => t('Osaka'),
    '28' => t('Hyogo'),
    '29' => t('Nara'),
    '30' => t('Wakayama'),
    '31' => t('Tottori'),
    '32' => t('Shimane'),
    '33' => t('Okayama'),
    '34' => t('Hiroshima'),
    '35' => t('Yamaguchi'),
    '36' => t('Tokushima'),
    '37' => t('Kagawa'),
    '38' => t('Ehime'),
    '39' => t('Kochi'),
    '40' => t('Fukuoka'),
    '41' => t('Saga'),
    '42' => t('Nagasaki'),
    '43' => t('Kumamoto'),
    '44' => t('Oita'),
    '45' => t('Miyazaki'),
    '46' => t('Kagoshima'),
    '47' => t('Okinawa'),
    '11' => t('Seoul'),
    '26' => t('Busan'),
    '27' => t('Daegu'),
    '30' => t('Daejeon'),
    '29' => t('Gwangju'),
    '28' => t('Incheon'),
    '31' => t('Ulsan'),
    '43' => t('Chungcheongbuk-do'),
    '44' => t('Chungcheongnam-do'),
    '42' => t('Gangwon-do'),
    '41' => t('Gyeonggi-do'),
    '47' => t('Gyeongsangbuk-do'),
    '48' => t('Gyeongsangnam-do'),
    '49' => t('Jeju-do'),
    '45' => t('Jeollabuk-do'),
    '46' => t('Jeollanam-do'),
    '50' => t('Sejong'),
    'AST' => t('Astana'),
    'ALA' => t('Almaty'),
    'ALM' => t('Almaty region'),
    'AKM' => t('Aqmola region'),
    'AKT' => t('Aqtöbe region'),
    'ATY' => t('Atyraū region'),
    'ZAP' => t('Batys Qazaqstan region'),
    'MAN' => t('Mangghystaū region'),
    'YUZ' => t('Ongtüstik Qazaqstan region'),
    'PAV' => t('Pavlodar region'),
    'KAR' => t('Qaraghandy region'),
    'KUS' => t('Qostanay region'),
    'KZY' => t('Qyzylorda region'),
    'VOS' => t('Shyghys Qazaqstan region'),
    'SEV' => t('Soltüstik Qazaqstan region'),
    'ZHA' => t('Zhambyl region'),
    'AGU' => 'Aguascalientes',
    'BCN' => 'Baja California',
    'BCS' => 'Baja California Sur',
    'CAM' => 'Campeche',
    'COA' => 'Coahuila',
    'COL' => 'Colima',
    'CHP' => 'Chiapas',
    'CHH' => 'Chihuahua',
    'DIF' => 'Distrito Federal',
    'DUG' => 'Durango',
    'MEX' => 'Estado de México',
    'GUA' => 'Guanajuato',
    'GRO' => 'Guerrero',
    'HID' => 'Hidalgo',
    'JAL' => 'Jalisco',
    'MIC' => 'Michoacán',
    'MOR' => 'Morelos',
    'NAY' => 'Nayarit',
    'NLE' => 'Nuevo León',
    'OAX' => 'Oaxaca',
    'PUE' => 'Puebla',
    'QUE' => 'Queretaro',
    'ROO' => 'Quintana Roo',
    'SLP' => 'San Luis Potosí',
    'SIN' => 'Sinaloa',
    'SON' => 'Sonora',
    'TAB' => 'Tabasco',
    'TAM' => 'Tamaulipas',
    'TLA' => 'Tlaxcala',
    'VER' => 'Veracruz',
    'YUC' => 'Yucatán',
    'ZAC' => 'Zacatecas',
    '01' => t('Johor'),
    '02' => t('Kedah'),
    '03' => t('Kelantan'),
    '14' => t('Kuala Lumpur'),
    '15' => t('Labuan'),
    '04' => t('Melaka'),
    '05' => t('Negeri Sembilan'),
    '06' => t('Pahang'),
    '08' => t('Perak'),
    '09' => t('Perlis'),
    '07' => t('Pulau Pinang'),
    '16' => t('Putrajaya'),
    '12' => t('Sabah'),
    '13' => t('Sarawak'),
    '10' => t('Selangor'),
    '11' => t('Terengganu'),
    'AMA' => 'Amazonas',
    'ANC' => 'Ancash',
    'APU' => 'Apurimac',
    'ARE' => 'Arequipa',
    'AYA' => 'Ayacucho',
    'CAJ' => 'Cajamarca',
    'CAL' => 'Callao',
    'CUS' => 'Cusco',
    'HUV' => 'Huancavelica',
    'HUC' => 'Huanuco',
    'ICA' => 'Ica',
    'JUN' => 'Junin',
    'LAL' => 'La Libertad',
    'LAM' => 'Lambayeque',
    'LIM' => 'Lima',
    'LOR' => 'Loreto',
    'MDD' => 'Madre de Dios',
    'MOQ' => 'Moquegua',
    'PAS' => 'Pasco',
    'PIU' => 'Piura',
    'PUN' => 'Puno',
    'SAM' => 'San Martin',
    'TAC' => 'Tacna',
    'TUM' => 'Tumbes',
    'UCA' => 'Ucayali',
    'MOW' => t('Moskva'),
    'SPE' => t('Sankt-Peterburg'),
    'AD' => t('Adygeya, Respublika'),
    'AL' => t('Altay, Respublika'),
    'BA' => t('Bashkortostan, Respublika'),
    'BU' => t('Buryatiya, Respublika'),
    'CE' => t('Chechenskaya Respublika'),
    'CU' => t('Chuvashskaya Respublika'),
    'DA' => t('Dagestan, Respublika'),
    'IN' => t('Ingushetiya, Respublika'),
    'KB' => t('Kabardino-Balkarskaya Respublika'),
    'KL' => t('Kalmykiya, Respublika'),
    'KC' => t('Karachayevo-Cherkesskaya Respublika'),
    'KR' => t('Kareliya, Respublika'),
    'KK' => t('Khakasiya, Respublika'),
    'KO' => t('Komi, Respublika'),
    'ME' => t('Mariy El, Respublika'),
    'MO' => t('Mordoviya, Respublika'),
    'SA' => t('Sakha, Respublika [Yakutiya]'),
    'SE' => t('Severnaya Osetiya-Alaniya, Respublika'),
    'TA' => t('Tatarstan, Respublika'),
    'TY' => t('Tyva, Respublika [Tuva]'),
    'UD' => t('Udmurtskaya Respublika'),
    'ALT' => t('Altayskiy kray'),
    'KAM' => t('Kamchatskiy kray'),
    'KHA' => t('Khabarovskiy kray'),
    'KDA' => t('Krasnodarskiy kray'),
    'KYA' => t('Krasnoyarskiy kray'),
    'PER' => t('Permskiy kray'),
    'PRI' => t('Primorskiy kray'),
    'STA' => t('Stavropolskiy kray'),
    'ZAB' => t('Zabaykalskiy kray'),
    'AMU' => t('Amurskaya oblast'),
    'ARK' => t('Arkhangelskaya oblast'),
    'AST' => t('Astrakhanskaya oblast'),
    'BEL' => t('Belgorodskaya oblast'),
    'BRY' => t('Bryanskaya oblast'),
    'CHE' => t('Chelyabinskaya oblast'),
    'IRK' => t('Irkutskaya oblast'),
    'IVA' => t('Ivanovskaya oblast'),
    'KGD' => t('Kaliningradskaya oblast'),
    'KLU' => t('Kaluzhskaya oblast'),
    'KEM' => t('Kemerovskaya oblast'),
    'KIR' => t('Kirovskaya oblast'),
    'KOS' => t('Kostromskaya oblast'),
    'KGN' => t('Kurganskaya oblast'),
    'KRS' => t('Kurskaya oblast'),
    'LEN' => t('Leningradskaya oblast'),
    'LIP' => t('Lipetskaya oblast'),
    'MAG' => t('Magadanskaya oblast'),
    'MOS' => t('Moskovskaya oblast'),
    'MUR' => t('Murmanskaya oblast'),
    'NIZ' => t('Nizhegorodskaya oblast'),
    'NGR' => t('Novgorodskaya oblast'),
    'NVS' => t('Novosibirskaya oblast'),
    'OMS' => t('Omskaya oblast'),
    'ORE' => t('Orenburgskaya oblast'),
    'ORL' => t('Orlovskaya oblast'),
    'PNZ' => t('Penzenskaya oblast'),
    'PSK' => t('Pskovskaya oblast'),
    'ROS' => t('Rostovskaya oblast'),
    'RYA' => t('Ryazanskaya oblast'),
    'SAK' => t('Sakhalinskaya oblast'),
    'SAM' => t('Samarskaya oblast'),
    'SAR' => t('Saratovskaya oblast'),
    'SMO' => t('Smolenskaya oblast'),
    'SVE' => t('Sverdlovskaya oblast'),
    'TAM' => t('Tambovskaya oblast'),
    'TOM' => t('Tomskaya oblast'),
    'TUL' => t('Tulskaya oblast'),
    'TVE' => t('Tverskaya oblast'),
    'TYU' => t('Tyumenskaya oblast'),
    'ULY' => t('Ulyanovskaya oblast'),
    'VLA' => t('Vladimirskaya oblast'),
    'VGG' => t('Volgogradskaya oblast'),
    'VLG' => t('Vologodskaya oblast'),
    'VOR' => t('Voronezhskaya oblast'),
    'YAR' => t('Yaroslavskaya oblast'),
    'YEV' => t('Yevreyskaya avtonomnaya oblast'),
    'CHU' => t('Chukotskiy avtonomnyy okrug'),
    'KHM' => t('Khanty-Mansiyskiy avtonomnyy okrug-Yugra'),
    'NEN' => t('Nenetskiy avtonomnyy okrug'),
    'YAN' => t('Yamalo-Nenetskiy avtonomnyy okrug'),
    '01' => t('Adana'),
    '02' => t('Adıyaman'),
    '03' => t('Afyon'),
    '04' => t('Ağrı'),
    '68' => t('Aksaray'),
    '05' => t('Amasya'),
    '06' => t('Ankara'),
    '07' => t('Antalya'),
    '75' => t('Ardahan'),
    '08' => t('Artvin'),
    '09' => t('Aydın'),
    '10' => t('Balıkesir'),
    '74' => t('Bartın'),
    '72' => t('Batman'),
    '69' => t('Bayburt'),
    '11' => t('Bilecik'),
    '12' => t('Bingöl'),
    '13' => t('Bitlis'),
    '14' => t('Bolu'),
    '15' => t('Burdur'),
    '16' => t('Bursa'),
    '17' => t('Çanakkale'),
    '18' => t('Çankırı'),
    '19' => t('Çorum'),
    '20' => t('Denizli'),
    '21' => t('Diyarbakır'),
    '81' => t('Düzce'),
    '22' => t('Edirne'),
    '23' => t('Elazığ'),
    '24' => t('Erzincan'),
    '25' => t('Erzurum'),
    '26' => t('Eskişehir'),
    '27' => t('Gaziantep'),
    '28' => t('Giresun'),
    '29' => t('Gümüşhane'),
    '30' => t('Hakkari'),
    '31' => t('Hatay'),
    '76' => t('Iğdır'),
    '32' => t('Isparta'),
    '34' => t('İstanbul'),
    '35' => t('İzmir'),
    '46' => t('Kahramanmaraş'),
    '78' => t('Karabük'),
    '70' => t('Karaman'),
    '36' => t('Kars'),
    '37' => t('Kastamonu'),
    '38' => t('Kayseri'),
    '71' => t('Kırıkkale'),
    '39' => t('Kırklareli'),
    '40' => t('Kırşehir'),
    '79' => t('Kilis'),
    '41' => t('Kocaeli'),
    '42' => t('Konya'),
    '43' => t('Kütahya'),
    '44' => t('Malatya'),
    '45' => t('Manisa'),
    '47' => t('Mardin'),
    '33' => t('Mersin'),
    '48' => t('Muğla'),
    '49' => t('Muş'),
    '50' => t('Nevşehir'),
    '51' => t('Niğde'),
    '52' => t('Ordu'),
    '80' => t('Osmaniye'),
    '53' => t('Rize'),
    '54' => t('Sakarya'),
    '55' => t('Samsun'),
    '56' => t('Siirt'),
    '57' => t('Sinop'),
    '58' => t('Sivas'),
    '63' => t('Şanlıurfa'),
    '73' => t('Şırnak'),
    '59' => t('Tekirdağ'),
    '60' => t('Tokat'),
    '61' => t('Trabzon'),
    '62' => t('Tunceli'),
    '64' => t('Uşak'),
    '65' => t('Van'),
    '77' => t('Yalova'),
    '66' => t('Yozgat'),
    '67' => t('Zonguldak'),
    'TXG' => t('Taichung City'),
    'TPE' => t('Taipei City'),
    'TTT' => t('Taitung County'),
    'TNN' => t('Tainan City'),
    'ILA' => t('Yilan County'),
    'HUA' => t('Hualien County'),
    'Kinmen County' => t('Kinmen County'),
    'NAN' => t('Nantou County'),
    'PIF' => t('Pingtung County'),
    'MIA' => t('Miaoli County'),
    'TAO' => t('Taoyuan County'),
    'KHH' => t('Kaohsiung City'),
    'KEE' => t('Keelung City'),
    'Lienchiang County' => t('Lienchiang County'),
    'YUN' => t('Yunlin County'),
    'TPQ' => t('New Taipei City'),
    'HSZ' => t('Hsinchu City'),
    'HSQ' => t('Hsinchu County'),
    'CYI' => t('Chiayi City'),
    'CYQ' => t('Chiayi County'),
    'CHA' => t('Changhua County'),
    'PEN' => t('Penghu County'),
    '43' => t('Crimea'),
    '05' => t('Vinnyts\'ka oblast'),
    '07' => t('Volyns\'ka oblast'),
    '12' => t('Dnipropetrovsk Oblast'),
    '14' => t('Donetsk Oblast'),
    '18' => t('Zhytomyrs\'ka oblast'),
    '21' => t('Zakarpats\'ka oblast'),
    '23' => t('Zaporiz\'ka oblast'),
    '26' => t('Ivano-Frankivs\'ka oblast'),
    '30' => t('Kiev Oblast'),
    '35' => t('Kirovohrads\'ka oblast'),
    '09' => t('Luhans\'ka oblast'),
    '46' => t('Lviv Oblast'),
    '48' => t('Mykolaivs\'ka oblast'),
    '51' => t('Odessa Oblast'),
    '53' => t('Poltavs\'ka oblast'),
    '56' => t('Rivnens\'ka oblast'),
    '40' => t('Sevastopol\' city'),
    '59' => t('Sums\'ka oblast'),
    '61' => t('Ternopil\'s\'ka oblast'),
    '63' => t('Kharkiv Oblast'),
    '65' => t('Khersons\'ka oblast'),
    '68' => t('Khmel\'nyts\'ka oblast'),
    '71' => t('Cherkas\'ka oblast'),
    '77' => t('Chernivets\'ka oblast'),
    '74' => t('Chernihivs\'ka oblast'),
    'AL' => t('Alabama'),
    'AK' => t('Alaska'),
    'AZ' => t('Arizona'),
    'AR' => t('Arkansas'),
    'CA' => t('California'),
    'CO' => t('Colorado'),
    'CT' => t('Connecticut'),
    'DE' => t('Delaware'),
    'DC' => t('District of Columbia'),
    'FL' => t('Florida'),
    'GA' => t('Georgia'),
    'HI' => t('Hawaii'),
    'ID' => t('Idaho'),
    'IL' => t('Illinois'),
    'IN' => t('Indiana'),
    'IA' => t('Iowa'),
    'KS' => t('Kansas'),
    'KY' => t('Kentucky'),
    'LA' => t('Louisiana'),
    'ME' => t('Maine'),
    'MD' => t('Maryland'),
    'MA' => t('Massachusetts'),
    'MI' => t('Michigan'),
    'MN' => t('Minnesota'),
    'MS' => t('Mississippi'),
    'MO' => t('Missouri'),
    'MT' => t('Montana'),
    'NE' => t('Nebraska'),
    'NV' => t('Nevada'),
    'NH' => t('New Hampshire'),
    'NJ' => t('New Jersey'),
    'NM' => t('New Mexico'),
    'NY' => t('New York'),
    'NC' => t('North Carolina'),
    'ND' => t('North Dakota'),
    'OH' => t('Ohio'),
    'OK' => t('Oklahoma'),
    'OR' => t('Oregon'),
    'PA' => t('Pennsylvania'),
    'RI' => t('Rhode Island'),
    'SC' => t('South Carolina'),
    'SD' => t('South Dakota'),
    'TN' => t('Tennessee'),
    'TX' => t('Texas'),
    'UT' => t('Utah'),
    'VT' => t('Vermont'),
    'VA' => t('Virginia'),
    'WA' => t('Washington'),
    'WV' => t('West Virginia'),
    'WI' => t('Wisconsin'),
    'WY' => t('Wyoming'),    
    'AA' => t('Armed Forces (Americas)'),
    'AE' => t('Armed Forces (Europe, Canada, Middle East, Africa)'),
    'AP' => t('Armed Forces (Pacific)'),
    'AS' => t('American Samoa'),
    'FM' => t('Federated States of Micronesia'),
    'GU' => t('Guam'),
    'MH' => t('Marshall Islands'),
    'MP' => t('Northern Mariana Islands'),
    'PW' => t('Palau'),
    'PR' => t('Puerto Rico'),
    'VI' => t('Virgin Islands'),  
    'Z' => 'Amazonas',
    'B' => 'Anzoátegui',
    'C' => 'Apure',
    'D' => 'Aragua',
    'E' => 'Barinas',
    'F' => 'Bolívar',
    'G' => 'Carabobo',
    'H' => 'Cojedes',
    'Y' => 'Delta Amacuro',
    'W' => 'Dependencias Federales',
    'A' => 'Distrito Federal',
    'I' => 'Falcón',
    'J' => 'Guárico',
    'K' => 'Lara',
    'L' => 'Mérida',
    'M' => 'Miranda',
    'N' => 'Monagas',
    'O' => 'Nueva Esparta',
    'P' => 'Portuguesa',
    'R' => 'Sucre',
    'S' => 'Táchira',
    'T' => 'Trujillo',
    'X' => 'Vargas',
    'U' => 'Yaracuy',
    'V' => 'Zulia',
  );

  return $administrative_areas;
}

/**
 * Ajax callback for fm_facility form.
 */
function prog_loc_change_facility_nid_callback($form,&$form_state){
  ctools_include('ajax');
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];

  if($form_state['triggering_element']['#name'] == 'get_facility') {
    $NodeType = $form_state['values']['add_ntype'];
    $NodeNid = $form_state['values']['get_facility'];
    //config location facility
    if($NodeType == 'fm_facility' && $NodeNid && !empty($NodeNid)){
      $query= db_select('node', 'n');
      $query->leftjoin('field_data_field_facility_location_site' ,'flr', 'flr.entity_id=n.nid');      
      $query->leftjoin('field_data_field_facility_number_of_floor' ,'ffnof', 'ffnof.entity_id=n.nid');
      $query->leftjoin('field_data_field_facility_ftes' ,'ffft', 'ffft.entity_id=n.nid');
      $query->leftjoin('field_data_field_facility_employees' ,'ffem', 'ffem.entity_id=n.nid');
      $query->leftjoin('field_data_field_facility_type' ,'ffty', 'ffty.entity_id=n.nid');
      $query->leftjoin('field_data_field_facility_address' ,'fla' ,'fla.entity_id=n.nid');
      $query->leftjoin('field_data_field_facility_description' ,'fde' ,'fde.entity_id=n.nid');
      $query->fields('n',array('nid','title')); 
      $query->fields('ffft',array('field_facility_ftes_value'));
      $query->fields('ffem',array('field_facility_employees_value'));
      $query->fields('ffty',array('field_facility_type_target_id'));    
      $query->fields('flr',array('field_facility_location_site_target_id'));
      $query->fields('ffnof',array('field_facility_number_of_floor_value'));
        $query->fields('fde',array('field_facility_description_value'));
      $query->fields('fla',array('field_facility_address_country','field_facility_address_thoroughfare','field_facility_address_premise','field_facility_address_locality','field_facility_address_administrative_area','field_facility_address_postal_code'));
      $query->condition('n.nid', $NodeNid , '=');
      $query->condition('n.type', $NodeType, '=');
      $CData= $query->execute()->fetchAll();
      
      
      $NodeObj111 = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_facility_area_type','Fetch'=>'fetchAllKeyed','CFields'=>'CFields','CFieldsNames'=>array('delta','field_facility_area_type_target_id'),'OtherId'=>array('equal'=>array('bundle'=>'facility'),'equal'=>array('entity_id'=>$NodeNid ))); 
      $TableData111 =  _get_asset_loc_db_request($NodeObj111);

      $commands[] = ajax_command_invoke("select.config_location_pick_site", 'val',array($CData[0]->field_facility_location_site_target_id));  
      $commands[] = ajax_command_invoke("input.config_location_facility_title", 'val',array($CData[0]->title)); 
      $commands[] = ajax_command_invoke("select.config_location_facility_facilitytype", 'val',array($CData[0]->field_facility_type_target_id));
      $commands[] = ajax_command_invoke("input.config_location_facility_employees", 'val',array($CData[0]->field_facility_employees_value));
      $commands[] = ajax_command_invoke("input.config_location_facility_ftes", 'val',array($CData[0]->field_facility_ftes_value));
      $commands[] = ajax_command_invoke("input.config_location_facility_description", 'val',array($CData[0]->field_facility_description_value));
      $commands[] = ajax_command_invoke("input.config_location_facility_floornumber", 'val',array($CData[0]->field_facility_number_of_floor_value));
      if(isset($CData[0]->field_facility_number_of_floor_value) && !empty($CData[0]->field_facility_number_of_floor_value)){
      $commands[] = ajax_command_invoke("select.config_location_facility_floornumber_select", 'val',array($CData[0]->field_facility_number_of_floor_value));
      $commands[] = ajax_command_invoke("input.config_location_facility_floornumber_addmore", 'trigger',array('mousedown'));
      }
      else{
        $commands[] = ajax_command_invoke("select.config_location_facility_floornumber_select", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_floornumber_addmore", 'trigger',array('mousedown'));
      }
      $commands[] = ajax_command_invoke("select.config_location_facility_country", 'val',array($CData[0]->field_facility_address_country));
      $commands[] = ajax_command_invoke("select.config_location_facility_country", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.config_location_facility_address1", 'val',array($CData[0]->field_facility_address_thoroughfare));
      $commands[] = ajax_command_invoke("input.config_location_facility_address2", 'val',array($CData[0]->field_facility_address_premise));
      $commands[] = ajax_command_invoke("input.config_location_facility_city", 'val',array($CData[0]->field_facility_address_locality));
      $commands[] = ajax_command_invoke("select.config_location_facility_state", 'val',array($CData[0]->field_facility_address_administrative_area));
      $commands[] = ajax_command_invoke("input.config_location_facility_state_key", 'val',array($CData[0]->field_facility_address_administrative_area));
      $commands[] = ajax_command_invoke("input.config_location_facility_zipcode", 'val',array($CData[0]->field_facility_address_postal_code));
      $commands[] = ajax_command_invoke("input.facility_area_type_values", 'val',array($TableData111)); 
      $commands[] = ajax_command_invoke("input.fm_facility_node_nid", 'val',array($CData[0]->nid));     
    }
    else{
      $commands[] = ajax_command_invoke("select.config_location_pick_site", 'val',array('')); 
      $commands[] = ajax_command_invoke("input.config_location_facility_title", 'val',array('')); 
      $commands[] = ajax_command_invoke("select.config_location_facility_facilitytype", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_employees", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_ftes", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_floornumber", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_facility_floornumber_select", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_floornumber_addmore", 'trigger',array('mousedown'));
      $commands[] = ajax_command_invoke("select.config_location_facility_country", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_facility_country", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.config_location_facility_address1", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_address2", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_city", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_facility_state", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_state_key", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_facility_zipcode", 'val',array(''));   
      $commands[] = ajax_command_invoke("input.facility_area_type_values", 'val',array(''));  
      $commands[] = ajax_command_invoke("input.fm_facility_node_nid", 'val',array(''));
    }
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * AJax callback for fm_location_location form.
 */
function prog_loc_change_zone_nid_callback($form,&$form_state){
  ctools_include('ajax');
  $commands = array();
  $triggeringElement = $form_state['triggering_element'];

  if($form_state['triggering_element']['#name'] == 'get_location_zone') {
    $NodeType = $form_state['values']['add_ntype'];
    $NodeNid = $form_state['values']['get_location_zone'];

    if($NodeType == 'fm_location_location' && $NodeNid && !empty($NodeNid)){
      $query= db_select('node', 'n');
      $query->leftjoin('field_data_field_location_facility' ,'flr', 'flr.entity_id=n.nid');      
      $query->leftjoin('field_data_field_location_description' ,'ffnof', 'ffnof.entity_id=n.nid');
      $query->leftjoin('field_data_field_location_room_number' ,'ffft', 'ffft.entity_id=n.nid');
      $query->leftjoin('field_data_field_location_department' ,'ffty', 'ffty.entity_id=n.nid');
      $query->leftjoin('field_data_field_location_zone_address' ,'fla' ,'fla.entity_id=n.nid');
      $query->leftjoin('field_data_field_location_floor_count' ,'flfco' ,'flfco.entity_id=n.nid');
      $query->fields('n',array('nid','title'));
      $query->fields('ffft',array('field_location_room_number_value'));
      $query->fields('ffty',array('field_location_department_target_id'));    
      $query->fields('flr',array('field_location_facility_target_id'));
      $query->fields('ffnof',array('field_location_description_value'));
      $query->fields('flfco',array('field_location_floor_count_value'));
      $query->fields('fla',array('field_location_zone_address_country','field_location_zone_address_thoroughfare','field_location_zone_address_premise','field_location_zone_address_locality','field_location_zone_address_administrative_area','field_location_zone_address_postal_code'));
      $query->condition('n.nid', $NodeNid , '=');
      $query->condition('n.type', $NodeType, '=');
      $CData= $query->execute()->fetchAll();
      
      $commands[] = ajax_command_invoke("select.config_location_pick_facility", 'val',array($CData[0]->field_location_facility_target_id));
      $commands[] = ajax_command_invoke("select.config_location_pick_facility", 'trigger',array('change'));
      //$commands[] = ajax_command_invoke("select.config_location_location_numberoffloor", 'trigger',array('change'));  
     // $commands[] = ajax_command_invoke("input.config_location_location_numberoffloor", 'val',array($CData[0]->title));
      $commands[] = ajax_command_invoke("input.config_location_location_title", 'val',array($CData[0]->title)); 
      $commands[] = ajax_command_invoke("input.config_location_zone_description", 'val',array($CData[0]->field_location_description_value));    
      $commands[] = ajax_command_invoke("input.config_location_location_roomnumber", 'val',array($CData[0]->field_location_room_number_value));
      $commands[] = ajax_command_invoke("select.config_location_department_number",  'val',array($CData[0]->field_location_department_target_id));    
      //$commands[] = ajax_command_invoke("input.config_location_location_address",  'val',array($CData[0]->title));  
      if(isset($CData[0]->field_location_floor_count_value) && !empty($CData[0]->field_location_floor_count_value)){
        //$commands[] = ajax_command_invoke("select.config_location_location_floornumber_select", 'val',array($CData[0]->field_location_floor_count_value));
       // $commands[] = ajax_command_invoke("input.config_location_location_floornumber_addmore", 'trigger',array('mousedown'));
      }
      
      $FloorListsObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_location_floors','addExpression'=>"CONCAT(entity_id, '_', delta)",'addExpression_value'=>"nid_delta",'Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('field_location_floors_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_facility'),'equal'=>array('entity_id'=>$NodeNid)));
      $FloorLists =  _get_asset_loc_db_request($FloorListsObj);
    
      $commands[] = ajax_command_invoke("input.location_location_numberoffloor_values", 'val',array($FloorLists));
      
      
      $commands[] = ajax_command_invoke("select.config_location_location_country", 'val',array($CData[0]->field_location_zone_address_country));
      $commands[] = ajax_command_invoke("select.config_location_location_country", 'trigger',array('change'));
      //$commands[] = ajax_command_invoke("input.config_location_location_country_value", 'val',array($CData[0]->title));
      $commands[] = ajax_command_invoke("input.config_location_location_address1", 'val',array($CData[0]->field_location_zone_address_thoroughfare));
      $commands[] = ajax_command_invoke("input.config_location_location_address2", 'val',array($CData[0]->field_location_zone_address_premise));
      $commands[] = ajax_command_invoke("input.config_location_location_city", 'val',array($CData[0]->field_location_zone_address_locality));
      $commands[] = ajax_command_invoke("select.config_location_location_state", 'val',array($CData[0]->field_location_zone_address_administrative_area));
      $commands[] = ajax_command_invoke("input.config_location_location_state_key", 'val',array($CData[0]->field_location_zone_address_administrative_area));
      //$commands[] = ajax_command_invoke("input.config_location_location_state_value", 'val',array($CData[0]->title));
      $commands[] = ajax_command_invoke("input.config_location_location_zipcode", 'val',array($CData[0]->field_location_zone_address_postal_code));
      $commands[] = ajax_command_invoke("input.fm_location_location_node_nid", 'val',array($CData[0]->nid));  
    }
    else{
      $commands[] = ajax_command_invoke("select.config_location_pick_facility", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_pick_facility", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.config_location_location_title", 'val',array('')); 
      $commands[] = ajax_command_invoke("input.config_location_zone_description", 'val',array(''));   
      $commands[] = ajax_command_invoke("input.config_location_location_roomnumber", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_department_number",  'val',array(''));  
      $commands[] = ajax_command_invoke("input.location_location_numberoffloor_values", 'val',array(''));   
      $commands[] = ajax_command_invoke("select.config_location_location_country", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_location_country", 'trigger',array('change'));
      $commands[] = ajax_command_invoke("input.config_location_location_address1", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_location_address2", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_location_city", 'val',array(''));
      $commands[] = ajax_command_invoke("select.config_location_location_state", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_location_state_key", 'val',array(''));
      $commands[] = ajax_command_invoke("input.config_location_location_zipcode", 'val',array(''));
      $commands[] = ajax_command_invoke("input.fm_location_location_node_nid", 'val',array(''));
    }
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function program_location_floor_more_option_submit($form, &$form_state) {
  $select = $form_state['input']['location_client_options'];
  $build = '';
  if (isset($form_state['triggering_element']['#value']) &&  !empty($form_state['triggering_element']['#value'])) {
    if (isset($select) && !empty($select) && is_numeric($select)) {
      //$FloorName = '';
      //$FloorDelta = '';
      $FloorNameDelta =array();
      if (isset($form_state['input']['config_location_pick_facility']) && isset($form_state['input']['config_location_location_numberoffloor']) ) {
        $FacilityNid = $form_state['input']['config_location_pick_facility'];
        $FacilityFloorValues = $form_state['input']['config_location_location_numberoffloor'];
        $LocationZoneEditNid = $form_state['input']['fm_location_location_node_nid'];
        $FloorNameDelta =array();
        $FloorSquareFeetDelta =array();
        $FloorSquareFeetValueDelta =array();
        $FloorSquareFeetRatioDelta =array();
        if (isset($LocationZoneEditNid) && !empty($LocationZoneEditNid)) {
          $FloorNameObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_location_floor_name','Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('field_location_floor_name_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_location_location'),'equal'=>array('entity_id'=>$LocationZoneEditNid)));
          $FloorNameDelta =  _get_asset_loc_db_request($FloorNameObj);
         
          
          $FloorSquareFeetObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_location_total_sf','Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('field_location_total_sf_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_location_location'),'equal'=>array('entity_id'=>$LocationZoneEditNid)));
          $FloorSquareFeetDelta =  _get_asset_loc_db_request($FloorSquareFeetObj );
          
          
          $FloorSquareFeetValueObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_location_sf','Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('field_location_sf_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_location_location'),'equal'=>array('entity_id'=>$LocationZoneEditNid)));
          $FloorSquareFeetValueDelta =  _get_asset_loc_db_request($FloorSquareFeetValueObj );
          
          
          $FloorSquareFeetRatioObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_location_floor_percentage','Fetch'=>'fetchCol','CFields'=>'CFields','CFieldsNames'=>array('field_location_floor_percentage_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_location_location'),'equal'=>array('entity_id'=>$LocationZoneEditNid)));
          $FloorSquareFeetRatioDelta =  _get_asset_loc_db_request($FloorSquareFeetRatioObj );
        }
        else{
          if(isset($FacilityNid) && !empty($FacilityNid)){
          $FloorNameObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_facility_floor_name','addExpression'=>"CONCAT(entity_id, '_', delta)",'addExpression_value'=>"nid_delta",'Fetch'=>'fetchAll','CFields'=>'CFields','CFieldsNames'=>array('field_facility_floor_name_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_facility'),'equal'=>array('entity_id'=>$FacilityNid)));
          $FloorNameDeta =  _get_asset_loc_db_request($FloorNameObj);
            $FloorNameList1 = array();
            foreach($FloorNameDeta as $value){
                    $FloorNameList1[$value['nid_delta']] =  $value['field_facility_floor_name_value'];
                  }
          $FloorNameList =  $FloorNameList1;  
           
          $FloorSquareFeetObj = array('NodeType'=>'NoType','TableJoin'=>'TableJoin','TableName'=>'field_data_field_facility_floor_square_feet','addExpression'=>"CONCAT(entity_id, '_', delta)",'addExpression_value'=>"nid_delta",'Fetch'=>'fetchAll','CFields'=>'CFields','CFieldsNames'=>array('field_facility_floor_square_feet_value'),'OtherId'=>array('equal'=>array('bundle'=>'fm_facility'),'equal'=>array('entity_id'=>$FacilityNid)));
          $FloorSquareFeetDeta =  _get_asset_loc_db_request($FloorSquareFeetObj);
            $FloorSquareFeetList1 = array();
            foreach($FloorSquareFeetDeta as $value){
                    $FloorSquareFeetList1[$value['nid_delta']] =  $value['field_facility_floor_square_feet_value'];
                  }
          
          
          $FloorSquareFeetList =  $FloorSquareFeetList1;  
              
          }   
        }
        
        
        if(isset($FloorNameList) && !empty($FloorNameList)){
          foreach($FloorNameList as $Fnkey=>$Fnvalue){
          if(in_array($Fnkey,$FacilityFloorValues)){
          $FloorNameDelta[] = $Fnvalue; 
          }
          }
        }
        
        if(isset($FloorSquareFeetList) && !empty($FloorSquareFeetList)){
          foreach($FloorSquareFeetList as $Fsfkey=>$Fsfvalue){
          if(in_array($Fsfkey,$FacilityFloorValues)){
          $FloorSquareFeetDelta[] = $Fsfvalue;  
          }
          }
        }
      }
      
      $form_state['location_option_count'] = $select;
      $selectM = $select*4;
      $FLOOR = 0;
      $SF = 0;
      $FLOOR1 = 0;
      $SF1 = 0;
      $FloorRatioValue = 0;
      $FloorRatioValue1 = 0;
      $FloorRatio = 0;
      $FloorRatio1 = 0;
      $build = '';
      
      for ($j = 0; $j < $selectM; $j++) {
        if ($j % 4 == 0) {
          ++$FLOOR;
          $build[$j] =  array(
            '#type' => 'textfield',
            '#title' => 'Floor Name',
            '#name' => 'floor_'.$FLOOR,
            //'#parents' => array('facility_floor',$FLOOR,'floor_'.$FLOOR),
            '#value' => $FloorNameDelta[$FLOOR1],
            '#attributes' => array(
              'class'=> array(
              'config_location_location_floor_'.$FLOOR1
              )
            ),
            '#required' => TRUE,      
            '#prefix' => '<div class="row"><div class="col-md-3">',
            '#suffix' => '</div>',
          );
          $FLOOR1++;
        }
        elseif ($j % 4 == 1) {
          ++$SF;
          $build[$j] = array(
            '#type' => 'textfield',
            '#title' => 'Zone SF',
            '#name' => 'sf_'.$SF,
            //'#parents' => array('facility_floor_sf',$SF,'sf_'.$SF),
            '#value' => $FloorSquareFeetDelta[$SF1],
            '#disabled' => TRUE,
            '#attributes' => array(
              'class'=> array(
              'location_totalsf','config_location_location_floorsf_'.$SF1
              )
            ),
            '#required' => TRUE,
            '#prefix' => '<div class="col-md-3">',
            '#suffix' => '</div>',    
          );
          $SF1++;
        }
        elseif ($j % 4 == 2) {
          ++$FloorRatioValue;
          $build[$j] = array(
            '#type' => 'textfield',
            '#title' => 'SF',
            '#name' => 'floorratiovalue_'.$FloorRatioValue,
            //'#parents' => array('facility_floor_sf',$SF,'sf_'.$SF),
            '#value' => $FloorSquareFeetValueDelta[$FloorRatioValue1],
            '#attributes' => array(
              'class'=> array(
              'location_floorratiovalue','config_location_location_floorratiovalue_'.$FloorRatioValue1
              )
            ),
            '#required' => TRUE,
            '#prefix' => '<div class="col-md-3">',
            '#suffix' => '</div>',    
          );
          $FloorRatioValue1++;
        }
        elseif ($j % 4 == 3){
          ++$FloorRatio;
          $build[$j] = array(
            '#type' => 'textfield',
            '#title' => 'Zone %',
            '#name' => 'floorratio_'.$FloorRatio,
            '#value' => $FloorSquareFeetRatioDelta[$FloorRatio1],
            //'#parents' => array('facility_floor_sf',$SF,'sf_'.$SF),
            '#attributes' => array(
              'class'=> array(
              'location_floorratio','config_location_location_floorratio_'.$FloorRatio1
              )
            ),
            '#required' => TRUE,
            '#prefix' => '<div class="col-md-3">',
            '#suffix' => '</div></div>',    
          );
          $FloorRatio1++;
        }
      }
    }
  }
  $form_state['c'] = $build;
  
  $form_state['location_option'] = $form_state['c'];
  unset($form_state['input']['location_option']);
  $form_state['rebuild'] = TRUE;
}