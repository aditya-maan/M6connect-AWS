<?php
/**
 * Start work for m6connect contract review  
 */

function contract_review() {
  $elements = array();
  $elements['prgram-scm-menu-items'] = array(
    '#markup' => m6connect_contract_list_menu(),
    '#prefix' => '<div class="clearfix csemanager-sub-menu-new margin-top-10 margin-bottom-45 scm-product-submenu-sp">',
    '#suffix' => '</div>',  
  );
  // Contact Review Form.
  $contact_review_form = drupal_get_form('contact_review_form');
  $elements['contact-review-form'] = array(
    '#type'       => 'markup',
    '#markup'     => drupal_render($contact_review_form),
  );
  return $elements;
}

function contact_review_form($form, &$form_state) {  
  global $user, $company;

  if(!isset($form_state['creview_storage'])){
    $tempIdentifer = uniqid();
    $form_state['creview_storage'] = array($tempIdentifer);
  }

  $form['outer-container'] = array(
    '#type'       => 'container',
    '#attributes' => array('class'=>array('row')),
  );
  $form['outer-container']['inner-container']['container-left'] = array(
    '#type'       => 'container',
    '#prefix'     => '<div class="col-md-6 inner-left">',
    '#suffix'     => '</div>',    
  );
  $form['outer-container']['inner-container']['container-right'] = array(
    '#type'       => 'container',
    '#prefix'     => '<div class="col-md-6 inner-right">',
    '#suffix'     => '</div>',    
  );
  $form['outer-container']['inner-container']['container-left']['leftmain-container'] = array(
    '#type'       => 'container',
    '#process'    => array('outer_contact_review_first_process'),
    '#attributes' => array('id'=>'main-leftmain-container'),
    '#theme'      => 'outer_contact_review_first_theme',
    '#prefix'     => '<div id="main-leftmain-container-div" class="contract-review">',
    '#suffix'     => '</div>',
  );
  
  /*global $user,$company;
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
*/



  // Form Actions.
  // Submit Button
  $form['actions']['submit'] = array(
    '#type'       => 'submit',
    '#value'      => t('Save and Continue'),
  );
  // Generate Button.
  $form['actions']['generate'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Generate'), '#', array('html' => TRUE, 'external' => TRUE, 'attributes' => array('class' => array('btn btn-success text-white')))),
  );
  // Back Button.
  $form['actions']['back'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Back'), 'contract-manager/pricing-key/new', array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  );  
  // Cancel Button.
  $form['actions']['reset'] = array(
    '#type'       => 'markup',
    '#markup'     => l(t('Cancel'), '#' , array('attributes' => array('class' => array('form-submit', 'cancel-button')))),
  ); 
  return $form;
}

function contact_review_form_submit($form, &$form_state) { dpm($form_state,'form_state submit');

}
function theme_outer_contact_review_first_theme($variables) { //dpm($variables,'$variables');
  $element = $variables['form'];
  $storage    = $variables['form']['#storage'];
  $output     = '';
  $rows = array();
  foreach ($storage as $uniqid) {
    $element['section-weight'][$uniqid]['#attributes']['class'] = array('sectionorder-weight'); 
    /*$output .= '<div class="draggable row row-'.$uniqid.'">';
    $output .= '<div class="col-md-6 showonhover">'.drupal_render($element['section-weight'][$uniqid]).'</div>';
    $output .= '<div class="col-md-6 showonhover">'.drupal_render($element['section-remove'][$uniqid]).'</div>';


    $output .= '<div class="col-md-6">'.drupal_render($element['section-name'][$uniqid]).'</div>';
    $output .= '<div class="col-md-6 contract-initiation-wrapper">'.drupal_render($element['section-titlegroup'][$uniqid]).'</div>';
    $output .= '<div class="col-md-12">'.drupal_render($element['section-description'][$uniqid]).'</div>';
    $output .= '<div class="col-md-6">'.drupal_render($element['section-addfromlibrary'][$uniqid]).'</div>';
    $output .= '<div class="col-md-6">'.drupal_render($element['section-highlight'][$uniqid]).'</div>';
    $output .= '</div>';*/
    

    $rows[] = array(
      'data' => array(
        array('class' => array('tile-cross','v-top')),
        array('data' => drupal_render($element['section-weight'][$uniqid])),
        array('data' => 
          '<div class="clearfix margin-bottom-25">
            <div class="form-inline">
              <div class="form-group">
                '.drupal_render($element['section-name'][$uniqid]).'
              </div>
              <div class="form-group">
                <div class="form-inline">
                  '.drupal_render($element['section-titlegroup'][$uniqid]).'
                </div>
              </div>
              <div class="form-group">
                '.drupal_render($element['section-remove'][$uniqid]).'
              </div>
            </div>
          </div>
          <div class="clearfix review-description margin-bottom-10">
            '.drupal_render($element['section-description'][$uniqid]).'
          </div>
          <div class="clearfix addfromlibrary-highlight">
            <div class="pull-left">
              '.drupal_render($element['section-addfromlibrary'][$uniqid]).'
            </div>
            <div class="pull-right">
              '.drupal_render($element['section-highlight'][$uniqid]).'
            </div>
          </div>'
        ),
        
      ),  
      'class' => array('draggable'),
    );





  }
  $header = array('', t('Title'),'weight');
  $output .= theme('table', array('rows' => $rows, 'attributes' => array('id' => 'tiles-order')));
  //$output .= drupal_render_children($element);
  $output .= drupal_render($element['workflow_add_new_row']);
  drupal_add_tabledrag('tiles-order', 'order', 'sibling', 'sectionorder-weight');
  return $output;
}

function  outer_contact_review_first_process($elements, &$form_state) {
  $storage = $form_state['creview_storage'];
  $elements['#storage'] = $storage;
  $elements['#tree'] = TRUE;
  foreach ($storage as $key => $uniqid) {
    $elements['section-name'][$uniqid] = array(
      '#type'       => 'textfield',
      '#attributes' => array('placeholder'=> 'Section Name'),
      '#parents'    => array('creview', $uniqid, 'section-name'),
    );
    $elements['section-titlegroup'][$uniqid] = array(
      '#type'    => 'radios',
      '#options' => array('Title','Section Heading'),
      '#parents' => array('creview', $uniqid, 'section-titlegroup'),
    );
    $elements['section-description'][$uniqid] = array(
      '#type'    => 'textarea',
      '#parents' => array('creview', $uniqid, 'section-description'),
    );
    $elements['section-addfromlibrary'][$uniqid] = array(
      '#type'    => 'markup',
      '#markup'  => l('+ Add From Library','javascript:void(0);'),
      '#parents' => array('creview', $uniqid, 'section-addfromlibrary'),
    );
    $elements['section-highlight'][$uniqid] = array(
      '#type'    => 'checkbox',
      '#title'   => t('Contract Highlight'),
      '#parents' => array('creview', $uniqid, 'section-highlight'),
    );
    $elements['section-remove'][$uniqid] = array(
      '#type' => 'button',
      '#value' => decode_entities('&#xf014;'),
      '#name' => 'workflow_remove_row',         
      "#limit_validation_errors" => array(),  
      '#attributes'=> array('style'=> array('font-family:FontAwesome;'),
    ),    
      '#submit'=> array('remove_row_submit_handler_section'),
      '#parents' => array('creview', $uniqid, 'section-remove'),
      '#ajax' => array(
        'callback' => 'remove_row_section_action_callback',
        'wrapper' => 'category-outer-listing',
        'method' => 'replace',
        'effect' => 'fade',
        'progress' => array('type'=> 'throbber', 'message'=> NULL),
      ),
    );
    $elements['section-weight'][$uniqid] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#title_display' => 'invisible',
      //'#attributes' => array('class'=>array('sectionorder-weight')),
      '#default_value' => $key,
      '#parents' => array('creview', $uniqid, 'section-weight'),
    );
  }
  $elements['workflow_add_new_row'] = array(
    '#type'                    =>'submit',
    '#value'                   => 'Add Section',
    '#name'                    => 'workflow_add_new_row',
    '#attributes'              => array('class'=>array('workflow-action-add-details'),'title'=>'Add Section'),
    "#limit_validation_errors" => array(),
    '#submit'                  => array('add_new_row_submit_handler_section'),
    '#ajax'                    => array(
      'callback' => 'add_new_row_section_action_callback',
      'wrapper'  => 'main-leftmain-container-div',
      'method'   => 'replace',
      'effect'   => 'fade',
    'progress'                 => array('type'=> 'throbber', 'message'=> NULL),
    ),
  );
  return $elements;
}

/**
 * Ajax callback for workflow_add_new_row.
 */
function add_new_row_section_action_callback(&$form, &$form_state) {
  return $form['outer-container']['inner-container']['container-left']['leftmain-container'];
}

/**
 * Submit handler for workflow_add_new_row
 */
function add_new_row_submit_handler_section(&$form, &$form_state) {
  $triggerElement = $form_state['triggering_element'];
  if ($triggerElement['#name'] == 'workflow_add_new_row') {
    $tempIdentifer = uniqid();
    $form_state['creview_storage'][]  = $tempIdentifer;
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for workflow_remove_row.
 */
function remove_row_section_action_callback(&$form, &$form_state) { //pre($form_state,1);
  return $form['outer-container']['inner-container']['container-left']['leftmain-container'];
}

/**
 * Submit handler for workflow_remove_row
 */
function remove_row_submit_handler_section(&$form, &$form_state) {  
  $triggerElement = $form_state['triggering_element'];
  if ($triggerElement['#name'] == 'workflow_remove_row') {
    if(isset($form_state['creview_storage'])){
      $identifier = $triggerElement['#parents'][1];
      foreach ($form_state['creview_storage'] as $key => $value) {
        if($form_state['creview_storage'][$key] == $identifier){
          unset($form_state['creview_storage'][$key]);
          unset($form_state['creview_storage_default_value'][$identifier]);      
        } 
      }             
    }
    $form_state['rebuild'] = TRUE;
  }  
}