<?php
/**
 * @include file for m6drive.
 */


/************ Start Menu Callbacks *************/

/**
 * Menu callback for program/m6-drive
 */
function program_drive_listing_content() {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 

  global $company;
  global $user;

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true"></i></a>';   
  }
  else {
    $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
    '#suffix' => '</div>',
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-for-panel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-breadcrume']= array(
    '#markup' =>  m6drive_breadcrumb_for_folder(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-for-breadcrumb" class="col-md-8 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-4 padding-5 text-right"><span class="m6drive-more-action display-inline-block m6drive-more-option default-gray">'.l('<i class="fa fa-share-square padding-5" aria-hidden="true"></i>','share-m6drive/revoke/folder/multi/nojs', array('attributes'=> array('class'=>array('ctools-use-modal ctools-modal-assign-dashboard-popup-style'),'title'=>'Share With Others'),'html' => TRUE)).'<a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-delete-folder/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-archive-folder/folder/multi/nojs" title="Archive"><i class="fa fa-archive padding-5" aria-hidden="true"></i></a><a href="/m6drive-multiple-download/multi/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span><span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a href="javascript:void(0)" class="" title="Share With Others"><i class="fa fa-share-square padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Archive"><i class="fa fa-archive padding-5" aria-hidden="true"></i></a>
      <a href="javascript:void(0)" class="" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
      </div></div>',
  );
  $element['right-container']['drive-folder-listing'] = array(
    '#markup' => get_drive_listing_table_data(),
    '#prefix' => '<div class="clearfix"><div id="m6-drive-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
   );
  return $element;
}

/**
 * Menu callback for load-drive-data/%/%/%ctools_js
 */
function load_drive_data_callback($folder, $folderid, $ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  $m6driveActiveClass = 'active';
  $output = get_drive_listing_table_data($folder,$folderid);
  $output2 = _get_left_drive_panel($folder,$folderid, $m6driveActiveClass);
  $outputbreadcrumb = m6drive_breadcrumb_for_folder($folder,$folderid);
  ctools_include('ajax');
  $commands = array();
  $commands[] = ajax_command_html("#m6-drive-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-for-panel", $output2);
  $commands[] = ajax_command_html("#right-main-continter-for-breadcrumb", $outputbreadcrumb);
  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for addnew-m6drive/%/%ctools_js
 */
function m6drive_add_new_folder_callback($parentid, $ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'parent_id' => $parentid,
    );
    $output = ctools_modal_form_wrapper('m6drive_add_new_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_add_new_form', $parentid);
}

/**
 * Menu callback for uploadfile-m6drive/%/%ctools_js
 */
function m6drive_upload_new_file_callback($parentid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'parent_id' => $parentid,
      'title' => '<p class="asset-popup-title-custom">'.t('File Upload').'</p>',
    );
    $output = ctools_modal_form_wrapper('m6drive_upload_new_file_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
   return drupal_get_form('m6drive_upload_new_file_form', $parentid);
}

/**
 * Menu callback for share-m6drive/revoke/%/%/%ctools_js
 */
function m6drive_share_with_other_callback($sharetype, $shareid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'share_id' => $shareid,
      'share_type' => $sharetype,
      'title' => '<div class="asset-popup-title-custom">' . t('Share with others') . '</div>',
    );
    $output = ctools_modal_form_wrapper('m6drive_share_with_other_form', $form_state);
    if(!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_share_with_other_form', $sharetype, $shareid);
}

/**
 * Menu callback for m6drive-share-withme
 */
function m6drive_shared_withme_listing_content() {
  global $company, $user;

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if ($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true"></i></a>';   
  }
  else {
   $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class' => array('col-md-3', 'col-sm-3', 'col-xs-12', 'm6drive-details-left', 'margin-bottom-25', 'padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class' => array('col-md-9', 'col-sm-9', 'col-xs-12', 'm6drive-details-right', 'padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-for-share-panel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-shared-withme-breadcrumb']= array(
    '#markup' =>  m6drive_shraed_breadcrumb_for_folder(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-shared-withme-breadcrumb" class="col-md-9 padding-5">',
    '#suffix' => '</div><div class="right-main-continter-for-multiple col-md-3 padding-5 text-right"><span class="m6drive-more-action display-inline-block m6drive-more-option default-gray">
      <a href="/m6drive-multiple-download/multi/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Download">
      <i class="fa fa-download padding-5" aria-hidden="true"></i></a><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-delete-shared-folder/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Add to my Drive" href="/add-to-mydrive/nojs"><i class="fa fa-plus padding-5" aria-hidden="true"></i></a>
      </span><span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a href="javascript:void(0)" class="" title="Download">
      <i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="" title="Add to my Drive" href="javascript:void(0)"><i class="fa fa-plus padding-5" aria-hidden="true"></i></a></span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
      </div></div>',
  );
  $element['right-container']['drive-folder-listing'] = array(
    '#markup' => m6drive_share_withme_content(),
    '#prefix' => '<div class="clearfix"><div id="m6drive-share-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
  );
  return $element;
}

/**
 * Menu callback for share-load-drivedata/%/%/%ctools_js
 */
function share_load_drivedata_callback($folder, $folderid, $ajax = NULL) {
  global $user, $company;
  $m6driveActiveClass = 'active';
  $output = m6drive_share_withme_content($folder, $folderid);
  $output2 = _get_shared_left_drive_panel();
  $shraedbreadcrumb = m6drive_shraed_breadcrumb_for_folder($folder, $folderid);  
  ctools_include('ajax');
  $commands = array();
  $commands[] = ajax_command_html("#m6drive-share-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-for-share-panel", $output2);
  $commands[] = ajax_command_html("#right-main-continter-shared-withme-breadcrumb", $shraedbreadcrumb);
  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for m6drive-download/folder/%ctools_js
 */
function m6drive_download_callback($ajax = NULL){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('m6drive_download_form', $form_state);
    if(!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_download_form');
}

/**
 * Menu callback for m6drive-multiple-download/%/%
 */
function m6drive_download_multiple_folder_callback($type, $shareid) {
  global $base_path, $base_url, $user;
  $uid = uniqid();
  $dir = 'sites/default/files/';
  $fids = array();
  $tsmp = time();
  $check = 0;
  if ($type == 'folder' && !empty($shareid) && is_numeric($shareid)) {
    $folderName = get_folder_name_by_folderid($shareid);
    //$result =  m6drive_get_all_file_by_folderid($shareid); 
    $result = m6drive_get_inner_folder($shareid);
    $zipFilename = $folderName->foldername.'.zip';
    $zip = new ZipArchive();
    $zipname = $dir.$zipFilename; 
    $zip->open($zipname, ZIPARCHIVE::CREATE | ZIPARCHIVE::OVERWRITE);
    foreach($result as $record) {
      if (!empty($record->file)) {
        $fileObj = file_load($record->file);
        $fileName = $fileObj->filename;
        $objFile = file_copy($fileObj, $destination = 'temporary://'.$fileName.$uid.'.'.$fileName,  $replace = FILE_EXISTS_RENAME);
        $objFile->status=0;
        file_save($objFile);
        if ($objFile) {
          $path = drupal_realpath($objFile->uri);
          if (file_exists($path)) {
            $zip->addFile($path, $fileObj->filename);
            $check++; 
          }
        }
      }
    }
    $zip->close();
    if (file_exists($zipname)) {
      $file = file_save_data(file_get_contents($zipname), 'public://' . $zipFilename, $replace = FILE_EXISTS_REPLACE);
      $file->status=0;
      $file_Url = str_replace($base_url . $base_path, '', file_create_url($file->uri));
      file_save($file);
      drupal_goto($file_Url);
    }
    else {
      $file = file_save_data(file_get_contents($zipname), 'public:// '. $zipFilename, $replace = FILE_EXISTS_REPLACE);
      $file_Url = str_replace($base_url . $base_path, '', file_create_url($file->uri));
      drupal_goto($file_Url);
    }
  }
  drupal_exit();
}

/**
 * Menu callback for m6drive-delete-shared-folder/%/%/%ctools_js
 */
function m6drive_delete_shared_folder_callback($type, $deleteid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'delete_id' => $deleteid,
      'delete_type' => $type,
    );
    $output = ctools_modal_form_wrapper('m6drive_delete_shared_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_delete_shared_folder_form', $type, $deleteid);
}

/**
 * Menu callback for m6drive-delete-folder/%/%/%ctools_js
 */
function m6drive_delete_folder_callback($type, $deleteid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'delete_id' => $deleteid,
      'delete_type' => $type,
    );
    $output = ctools_modal_form_wrapper('m6drive_delete_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_delete_folder_form', $type, $deleteid);
}

/**
 * Menu callback for m6drive-trash-folder
 */
function m6drive_trash_folder_content() {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
  global $company, $user, $base_url; 

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true"></i></a>';   
  }
  else {
    $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-for-trashpanel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-breadcrume']= array(
    '#markup' =>  m6drive_trash_breadcrumb_for_folder(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-for-trash-breadcrumb" class="col-md-9 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-3 padding-5 text-right">
      <span class="m6drive-more-action display-inline-block m6drive-more-option default-gray">
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-restore/folder/multi/nojs" title="Restore"><i class="fa fa-recycle padding-5" aria-hidden="true"></i></a><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/remove-drive-permanent/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a> <a href="/m6drive-multiple-download/multi/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span> <span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a class="" href="javascript:void(0)" title="Restore"><i class="fa fa-recycle padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a> 
      <a href="javascript:void(0)" class="" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
      </div></div>',
  );
  $element['right-container']['drive-trash-folder-listing'] = array(
    '#markup' => m6drive_get_trash_drive_listing_table_data(),
    '#prefix' => '<div class="clearfix"><div class="" id="m6drive-trash-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
   );
  return $element;
}

/**
 * Menu callback for trash-load-drive-data/%/%/%ctools_js
 */
function m6drive_trash_load_drive_data_callback($folder, $folderid, $ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  $output = m6drive_get_trash_drive_listing_table_data($folder,$folderid);  
  $output2 = _get_shared_left_drive_panel($folder,$folderid);  
  $outputbreadcrumb =  m6drive_trash_breadcrumb_for_folder($folder,$folderid);
  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_html("#m6drive-trash-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-for-trashpanel", $output2);
  $commands[] = ajax_command_html("#right-main-continter-for-trash-breadcrumb", $outputbreadcrumb);

  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for remove-drive-permanent/%/%/%ctools_js
 */
function m6drive_remove_drive_permanent_callback($type, $deleteid, $ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'delete_id' => $deleteid,
      'delete_type' => $type,
    );
    $output = ctools_modal_form_wrapper('m6drive_remove_drive_permanent_form', $form_state);
   if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_remove_drive_permanent_form', $type, $deleteid);
}

/**
 * Menu callback for m6drive-archive
 */
function m6drive_archive_content() {
  global $company;
  global $user; 
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true"></i></a>';   
  }
  else {
    $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true"></i></a>';
  }
  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-for-archivepanel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-breadcrume']= array(
    '#markup' =>  m6drive_archive_breadcrumb_for_folder(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-for-archive-breadcrumb" class="col-md-9 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-3 padding-5 text-right">
      <span class="m6drive-more-action display-inline-block m6drive-more-option default-gray"><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-delete-folder/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-unarchive-folder/folder/multi/nojs" title="Unarchive"><i class="fa fa-archive" aria-hidden="true"></i></a> <a href="/m6drive-multiple-download/multi/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span><span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Unarchive"><i class="fa fa-archive" aria-hidden="true"></i></a> 
      <a href="javascript:void(0)" class="" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
      </div></div>',
  );
  $element['right-container']['drive-archive-folder-listing'] = array(
    '#markup' => m6drive_get_archive_drive_listing_table_data(),
    '#prefix' => '<div class="clearfix"><div id="m6drive-archive-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
   );
  return $element;
}

/**
 * Menu callback for archive-load-drive-data/%/%/%ctools_js
 */
function m6drive_archive_load_drive_data_callback($folder, $folderid, $ajax = NULL) {
  $output = m6drive_get_archive_drive_listing_table_data($folder,$folderid);
  $output2 = _get_shared_left_drive_panel($folder,$folderid);
  $outputbreadcrumb = m6drive_archive_breadcrumb_for_folder($folder,$folderid);
  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_html("#m6drive-archive-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-for-archivepanel", $output2);
  $commands[] = ajax_command_html("#right-main-continter-for-archive-breadcrumb", $outputbreadcrumb);

  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for m6drive-archive-folder/%/%/%ctools_js
 */
function m6drive_archive_folder_callback($type, $archiveid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'archive_id' => $archiveid,
      'archive_type' => $type,
    );
    $output = ctools_modal_form_wrapper('m6drive_archive_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_archive_folder_form', $type, $archiveid);
}

/**
 * Menu callback for m6drive-restore/%/%/%ctools_js
 */
function m6drive_restore_callback($type, $deleteid, $ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'delete_id' => $deleteid,
      'delete_type' => $type,
    );
    $output = ctools_modal_form_wrapper('m6drive_restore_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_restore_form', $type, $deleteid);
}

/**
 * Menu callback for m6drive-unarchive-folder/%/%/%ctools_js
 */
function m6drive_unarchive_folder_callback($type, $archiveid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'archive_id' => $archiveid,
      'archive_type' => $type,
    );
    $output = ctools_modal_form_wrapper('m6drive_unarchive_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_unarchive_folder_form', $type, $archiveid);
}

/**
 * Menu callback for project/drive
 */
function m6drive_projects_drive_content() {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
  global $company, $user;

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if ($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true" content="Grid view"></i></a>';   
  }
  else {
   $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true" content="List view"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );  
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-for-projectpanel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-breadcrume']= array(
    '#markup' =>  project_drive_breadcrumb(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-project-drive-breadcrumb" class="col-md-8 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-4 padding-5 text-right">
      <span class="m6drive-more-action display-inline-block m6drive-project-more-option default-gray">
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-share/folder/multi/nojs" title="Share With Others"><i class="fa fa-share-square padding-5" aria-hidden="true"></i></a>
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-archive/folder/multi/nojs" title="Archive"><i class="fa fa-archive" aria-hidden="true"></i></a>
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-trash/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a href="/m6drive-project-multiple-download/multi/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span><span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a class="" href="javascript:void(0)" title="Share With Others"><i class="fa fa-share-square padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Archive"><i class="fa fa-archive" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)"  title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
      </div></div>',
  );
  $element['right-container']['drive-folder-listing'] = array(
    '#markup' => m6drive_project_drive_listing_table_data(),
    '#prefix' => '<div class="clearfix"><div id="project-m6drive-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
  );
  return $element;
}

/**
 * Menu callback for project-load-drive/%/%/%ctools_js
 */
 function project_drive_load_data_callback($prjectnid = 0, $folder_id = 0, $ajax = NULL) {
  $m6driveActiveClass = 'active';
  $output = m6drive_project_drive_listing_table_data($prjectnid, $folder_id);
  $projectleftpanel = _get_shared_left_drive_panel($prjectnid, $m6driveActiveClass, $folder_id);  
  $projectbreadcrumb = project_drive_breadcrumb($prjectnid, $folder_id);
  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_html("#project-m6drive-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-for-projectpanel", $projectleftpanel);
  $commands[] = ajax_command_html("#right-main-continter-project-drive-breadcrumb", $projectbreadcrumb);

  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for project-drive-share/%/%/%ctools_js
 */
function project_drive_share_callback($sharetype, $shareid, $ajax = NULL) {
  if ($ajax){
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'share_id' => $shareid,
      'share_type' => $sharetype,
      'title' => '<div class="asset-popup-title-custom">'.t('Share with others').'</div>',
    );
    $output = ctools_modal_form_wrapper('project_drive_share_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('project_drive_share_form', $sharetype, $shareid);
}

/**
 * Menu callback for project/share-drive
 */
function m6drive_project_share_drive_content() {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
  global $company, $user;

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if ($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true" content="Grid view"></i></a>';   
  }
  else {
   $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true" content="List view"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-project-share-panel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-shared-withme-breadcrumb']= array(
    '#markup' =>   project_drive_shared_breadcrumb(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-project-share-breadcrumb" class="col-md-9 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-3 padding-5 text-right">
      <span class="m6drive-more-action display-inline-block m6drive-project-more-option default-gray"><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-delete-permanent/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Add to my Project Drive" href="/add-to-mydrive-project/nojs"><i class="fa fa-plus padding-5" aria-hidden="true"></i></a>
      </span>
      <span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
      <a class="" title="Add to my Project Drive" href="javascript:void(0)"><i class="fa fa-plus padding-5" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
      </div></div>',
  );
  $element['right-container']['drive-folder-listing'] = array(
    '#markup' => m6drive_project_drive_share_listing_content(),
    '#prefix' => '<div class="clearfix"><div class="" id="project-drive-share-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
   );
  return $element;
}

/**
 * Menu callback for project-share-load-drive/%/%/%ctools_js
 */
function project_drive_share_load_listing_content($projectnid, $folder_id, $ajax = NULL) {
  global $user, $company;

  $output = m6drive_project_drive_share_listing_content($projectnid, $folder_id);
  $leftdrivepanel = _get_shared_left_drive_panel($projectnid);
  $shraedbreadcrumb =  project_drive_shared_breadcrumb($projectnid, $folder_id);

  ctools_include('ajax');
  $commands = array();
  $commands[] = ajax_command_html("#project-drive-share-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-project-share-panel", $leftdrivepanel);
  $commands[] = ajax_command_html("#right-main-continter-project-share-breadcrumb", $shraedbreadcrumb);

  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for project-drive-archive/%/%/%ctools_js
 */
function project_drive_archive_folder_callback($type, $projectnid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('project_drive_archive_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('project_drive_archive_folder_form');
}

/**
 * Menu callback for project-drive-trash/%/%/%ctools_js
 */
function project_drive_trash_folder_callback($type, $projectnid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('project_drive_trash_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('project_drive_trash_folder_form');
}

/**
 * Menu callback for project/archive-drive
 */
function m6drive_project_archive_drive_content(){
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
  global $company, $user;

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true" content="Grid view"></i></a>';   
  }
  else {
    $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true" content="List view"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-project-archive-panel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-shared-withme-breadcrumb']= array(
    '#markup' => project_drive_archive_breadcrumb(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-project-archive-breadcrumb" class="col-md-9 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-3 padding-5 text-right">
    <span class="m6drive-more-action display-inline-block m6drive-project-more-option default-gray"><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-unarchive/folder/multi/nojs" title="Unarchive"><i class="fa fa-archive padding-5" aria-hidden="true"></i></a><a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-delete-permanent-trash/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a></span><span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
    <a class="" href="javascript:void(0)" title="Unarchive"><i class="fa fa-archive padding-5" aria-hidden="true"></i></a>
    <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o padding-5" aria-hidden="true"></i></a>
    </span>
    <span class="m6drive-more-action display-inline-block">
    <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload Files"><i class="fa fa-upload" aria-hidden="true"></i></a>
    </span>
     <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">'.$griddisplaybtn.'</span>
    </div></div>',
  );
  $element['right-container']['drive-folder-listing'] = array(
    '#markup' => m6drive_project_drive_archive_listing_content(),
    '#prefix' => '<div class="clearfix"><div id="project-drive-archive-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
   );
  return $element;
}

/**
 * Menu callback for project-archive-load-drive/%/%/%ctools_js
 */
function project_drive_archive_load_listing_content($projectnid, $folder_id, $ajax = NULL){
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
  global $user, $company;

  $output = m6drive_project_drive_archive_listing_content($projectnid, $folder_id);
  $leftdrivepanel = _get_shared_left_drive_panel($projectnid);
  $shraedbreadcrumb =  project_drive_archive_breadcrumb($projectnid, $folder_id);

  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_html("#project-drive-archive-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-project-archive-panel", $leftdrivepanel);
  $commands[] = ajax_command_html("#right-main-continter-project-archive-breadcrumb", $shraedbreadcrumb);

  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for project-drive-unarchive/%/%/%ctools_js
 */
function project_drive_unarchive_folder_callback($type, $projectnid, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('project_drive_unarchive_folder_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('project_drive_unarchive_folder_form');
}

/**
 * Menu callback for project/trash-drive
 */
function m6drive_project_trash_drive_content() {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  global $company, $user;
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if($optionview == 'List') {
    $griddisplaybtn = '<a href="javascript:void(0)" class="Grid" title="Grid view"><i class="fa fa-th padding-5" aria-hidden="true" content="Grid view"></i></a>';   
  }
  else {
   $griddisplaybtn = '<a href="javascript:void(0)" class="List" title="List view"><i class="fa fa-list padding-5" aria-hidden="true" content="List view"></i></a>';
  }

  $element['left-container']= array(
    '#type' => 'container',
    '#prefix' => '<div class="clearfix">',
    '#attributes' => array('class'=>array('col-md-3','col-sm-3','col-xs-12','m6drive-details-left','margin-bottom-25','padding-8')),
  );
  $element['right-container']= array(
    '#type' => 'container',
    '#suffix' => '</div>',
    '#attributes' => array('class'=>array('col-md-9','col-sm-9','col-xs-12','m6drive-details-right','padding-8')),
  );
  $element['left-container']['drive-panel'] = array(
    '#markup' => _get_shared_left_drive_panel(),
    '#prefix' => '<div class="left-main-container"><div id="left-main-continter-project-trash-panel">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-search-form']= array(
    '#markup' => drupal_render(drupal_get_form('program_drive_folder_serach_form')),
    '#prefix' => '<div class="row margin-5"><div class="margin-bottom-10 col-md-6 padding-5">',
    '#suffix' => '</div></div>',
  );
  $element['right-container']['folder-shared-withme-breadcrumb']= array(
    '#markup' => project_drive_trash_breadcrumb(),
    '#prefix' => '<div class="row margin-5 margin-bottom-10"><div id="right-main-continter-project-trash-breadcrumb" class="col-md-9 padding-5">',
    '#suffix' => '</div><div id="right-main-continter-for-multiple" class="col-md-3 padding-5 text-right">
      <span class="m6drive-more-action display-inline-block m6drive-project-more-option default-gray">
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/m6drive-project-restore-trash/folder/multi/nojs" title="Restore"><i class="fa fa-recycle padding-5" aria-hidden="true"></i></a>
      <a href="/m6drive-project-multiple-download/multi/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      <a class="ctools-use-modal ctools-modal-assign-dashboard-popup-style" href="/project-drive-delete-permanent-trash/folder/multi/nojs" title="Delete"><i class="fa fa-trash-o" aria-hidden="true"></i></a>
      </span><span class="display-inline-block m6drive-content-hover m6drive-default-gray-hover">
      <a class="" href="javascript:void(0)" title="Restore"><i class="fa fa-recycle padding-5" aria-hidden="true"></i></a>
      <a href="javascript:void(0)" class="" title="Download"><i class="fa fa-download padding-5" aria-hidden="true"></i></a>
      <a class="" href="javascript:void(0)" title="Delete"><i class="fa fa-trash-o" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-more-action display-inline-block">
      <a href="javascript:void(0)" class="trigger-upload-drive" title="Upload files"><i class="fa fa-upload" aria-hidden="true"></i></a>
      </span>
      <span class="m6drive-grid-list-action m6drive-more-action display-inline-block">' . $griddisplaybtn . '</span>
      </div></div>',
  );
  $element['right-container']['drive-folder-listing'] = array(
    '#markup' => m6drive_project_drive_trash_listing_content(),
    '#prefix' => '<div class="clearfix"><div id="project-drive-trash-datacontainer-main-cust">',
    '#suffix' => '</div></div>',
   );

  return $element;
}

/**
 * Menu callback for project-trash-load-drive/%/%/%ctools_js
 */
function project_drive_trash_load_listing_content($projectnid = 0, $folder_id = 0, $ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  $output = m6drive_project_drive_trash_listing_content($projectnid, $folder_id);  
  $leftdrivepanel = _get_shared_left_drive_panel($projectnid, $folder_id);
  $trashbreadcrumb =  project_drive_trash_breadcrumb($projectnid, $folder_id);  

  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_html("#project-drive-trash-datacontainer-main-cust", $output);
  $commands[] = ajax_command_html("#left-main-continter-project-trash-panel", $leftdrivepanel);
  $commands[] = ajax_command_html("#right-main-continter-project-trash-breadcrumb", $trashbreadcrumb);
  print ajax_render($commands);
  exit;
}

/**
 * Menu callback for project-delete-drive/%/%/%ctools_js
 */
function project_drive_delete_folder_file_callback($type, $projectnid, $ajax = NULL){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('project_drive_delete_folder_file_form', $form_state);
    if(!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('project_drive_delete_folder_file_form');
}

/**
 * Menu callback for project-drive-delete-permanent/%/%/%ctools_js
 */
function project_drive_delete_permanent_in_trash($type, $projectnid, $ajax = NULL){
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('project_drive_delete_permanent_in_trash_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('project_drive_delete_permanent_in_trash_form');
}

/**
 * Menu callback for m6drive-multiple-download/multi/%ctools_js
 */
function m6drive_download_multiple_folder_multi_callback($ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 

  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('m6drive_download_multiple_folder_multi_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_download_multiple_folder_multi_form');
}

/**
 * Menu callback for m6drive-project-multiple-download/multi/%ctools_js
 */
function m6drive_project_download_multiple_folder_multi_callback($ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('m6drive_project_download_multiple_folder_multi_form', $form_state);
    if(!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
   }
   return drupal_get_form('m6drive_project_download_multiple_folder_multi_form');
}

/**
 * Menu callback for addnew-m6drive-project/%/%/%ctools_js
 */
function project_drive_add_new_folder($projectnid, $folder_id, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'projectnid' => $projectnid,
      'folder_id' => $folder_id,
    );
    $output = ctools_modal_form_wrapper('m6drive_add_new_form_project', $form_state);
    if(!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_add_new_form_project', $projectnid, $folder_id);
}

/**
 * Menu callback for uploadfile-m6drive-project/%/%/%ctools_js
 */
function project_drive_add_new_file($projectnid, $folder_id, $ajax = NULL) {
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
      'projectnid' => $projectnid,
      'folder_id' => $folder_id,
      'title' => '<p class="asset-popup-title-custom">' . t('File Upload') . '</p>',
    );
    $output = ctools_modal_form_wrapper('m6drive_upload_new_file_form_project', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_upload_new_file_form_project', $projectnid, $folder_id);
}

/**
 * Menu callback for add-to-mydrive/%ctools_js
 */
function m6drive_add_tomydrive_callback($ajax = NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
    );
    $output = ctools_modal_form_wrapper('m6drive_add_tomydrive_form', $form_state);
    if(!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
  }
  return drupal_get_form('m6drive_add_tomydrive_form');
}

/**
 * Menu callback for add-to-mydrive-project/%ctools_js
 */
function m6drive_project_add_tomydrive_callback($ajax=NULL) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  

  if ($ajax) {
    ctools_include('ajax');
    ctools_include('modal');
    $form_state = array(
      'ajax' => TRUE,
     );
    $output = ctools_modal_form_wrapper('m6drive_project_add_tomydrive_form', $form_state);
    if (!empty($form_state['ajax_commands'])) {
      $output = $form_state['ajax_commands'];
    }
    print ajax_render($output);
    drupal_exit();
   }
  return drupal_get_form('m6drive_project_add_tomydrive_form');
}

/**
 * Menu callback for personal-drive-grid-view/%
 */
function m6drive_personal_drive_grid_view($gridviewval) {
  if (isset($gridviewval) && !empty($gridviewval)) {
    $_SESSION['detailview'] = $gridviewval;
  }
}

/************ End Menu Callbacks *************/




/************ Helper functions and form functions **************/

/**
 * Helper function to get drive left panel content.
 */
function _get_left_drive_panel($folder = 0, $folderid = 0, $m6driveActiveClass) {
  global $base_path, $company;
  global $user;

  if (!empty($company->nid)) {
    $node = node_load($company->nid);
    $companyTitle =  $node->title;
    if (!empty($companyTitle)) {
      $companyTitlevalue = (strlen($companyTitle) > 13) ? substr($companyTitle, 0, 10) . '...' : $companyTitle;
    }
    $company_email_trim = m6drive_get_primary_company_email($company->nid, $user->uid);
    if (!empty($company_email_trim)) {
      $company_email = (strlen($company_email_trim) > 29) ? substr($company_email_trim, 0, 27) . '...' : $company_email_trim;
    }

    if (!empty($user->mail)) {
      $user_email = (strlen($user->mail) > 29) ? substr($user->mail, 0, 27) . '...' : $user->mail;
    }
  }
  $current_path = current_path();
  $m6driveActiveClass = '';
  $m6driveshareActiveClass = '';
  $m6drivetrashActiveClass = '';
  $m6drivearchiveActiveClass = '';

  if ($current_path == 'program/m6-drive' || arg(0) == 'load-drive-data') {
    $m6driveActiveClass = 'active';  
  }
  elseif ($current_path == 'm6drive-share-withme' || arg(0) == 'share-load-drivedata') {
    $m6driveshareActiveClass = 'active'; 
  }
  elseif ($current_path == 'm6drive-trash-folder' || arg(0) == 'trash-load-drive-data') {
    $m6drivetrashActiveClass = 'active'; 
  }
  elseif ($current_path == 'm6drive-archive' || arg(0) == 'archive-load-drive-data') {
    $m6drivearchiveActiveClass = 'active'; 
  }
  $projectdriveActiveClass = '';
  $projectshareActiveClass = '';
  $projectarchiveActiveClass = '';
  $projecttrashActiveClass = '';

  if($current_path == 'project/drive' || arg(0) == 'project-load-drive'){
    $projectdriveActiveClass = 'active'; 
  }
  elseif($current_path == 'project/share-drive' || arg(0) == 'project-share-load-drive'){
    $projectshareActiveClass = 'active'; 
  }
  elseif($current_path == 'project/archive-drive' || arg(0) == 'project-archive-load-drive'){
    $projectarchiveActiveClass = 'active'; 
  }
  elseif($current_path == 'project/trash-drive' || arg(0) == 'project-trash-load-drive'){
    $projecttrashActiveClass = 'active'; 
  }

  $totalSpaceInDrive = _get_m6drive_total_space_user_uid($user->uid);
  $totalProjectSpace = _get_total_space_project_drive_by_uid($user->uid);

  $company_allocatespace = user_company_drive_total_space_count($company->nid);
  $user_allocatespace = user_personal_drive_total_space_count($user->uid);

  $personaldriveprogress = personal_drive_progress_bar();
  $companydriveprogress = company_project_drive_progress_bar();

  if($folderid == 0){
    if (arg(0) == 'project') {
      $content = '<div class="clearfix"><div class="m6-drive-buttons clearfix text-uppercase margin-bottom-20"><div class="clearfix">
      <a href="/addnew-m6drive/0/nojs" title="New Folder" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success">New Folder</a><a href="/uploadfile-m6drive/0/nojs" title="Upload File" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success triggering-upload">Upload</a></div></div>';
    }
    else {
      $content = '<div class="clearfix"><div class="m6-drive-buttons clearfix text-uppercase margin-bottom-20"><div class="clearfix"><a href="/addnew-m6drive/0/nojs" title="New Folder" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success">New Folder</a><a href="/uploadfile-m6drive/0/nojs" title="Upload File" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success triggering-upload">Upload</a></div></div>';
    }
    $content .= '<div class="clearfix blue_m6_logo_outer">
      <div class="clearfix blue_m6_logo"><h3><i class="fa fa-cloud-upload" aria-hidden="true"></i> My Personal Drive</h3><div class="clearfix margin-bottom-10 blue_m6_logo_mail"><a href="mailto:'.$user->mail.'"><i class="fa fa-envelope-o"></i> '.$user_email.'</a></div>
      </div>
      <ul class="list-unstyled m6-drive-list"><li><a class="'.$m6driveActiveClass.'" href="/program/m6-drive"><i class="fa fa-folder" aria-hidden="true"></i> My M6Drive</a></li><li><a class="'.$m6driveshareActiveClass.'" href="/m6drive-share-withme"><i class="fa fa-users" aria-hidden="true"></i> Shared with me</a></li><li><a class="'.$m6drivetrashActiveClass.'" href="/m6drive-trash-folder"><i class="fa fa-trash" aria-hidden="true"></i> Trash</a></li><li><a class="'.$m6drivearchiveActiveClass.'" href="/m6drive-archive"><i class="fa fa-archive" aria-hidden="true"></i> Archive</a></li></ul>
      '. $personaldriveprogress.'
      </div>
      <div class="clearfix blue_m6_logo_outer">
      <div class="clearfix margin-bottom-45"><h3 class="gray_m6_logo"><i class="fa fa-cloud-upload" aria-hidden="true"></i> '.$companyTitlevalue.' Drive</h3><div class="clearfix margin-bottom-10 blue_m6_logo_mail"><a href="mailto:'.$company_email_trim.'"><i class="fa fa-envelope-o"></i> '.$company_email.'</a></div><ul class="list-unstyled m6-drive-list"><li><a class="'.$projectdriveActiveClass.'" href="/project/drive"><i class="fa fa-cloud-upload" aria-hidden="true"></i> My Company Projects Drive</a></li><li><a class="'.$projectshareActiveClass.'" href="/project/share-drive"><i class="fa fa-users" aria-hidden="true"></i> Shared with me</a></li><li><a class="'.$projectarchiveActiveClass.'" href="/project/archive-drive"><i class="fa fa-archive" aria-hidden="true"></i> Archive</a></li><li><a class="'.$projecttrashActiveClass.'" href="/project/trash-drive"><i class="fa fa-trash" aria-hidden="true"></i> Trash</a></li></ul></div>
      ' . $companydriveprogress . '</div>
      </div>';
  }
  else {
    $content = '<div class="clearfix"><div class="m6-drive-buttons clearfix text-uppercase margin-bottom-20"><div class="clearfix"><a href="/addnew-m6drive/'.$folderid.'/nojs" title="New Folder" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success">New Folder</a><a href="/uploadfile-m6drive/'.$folderid.'/nojs" title="Upload File" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success triggering-upload">Upload</a></div></div>
      <div class="clearfix blue_m6_logo_outer">
      <div class="clearfix blue_m6_logo"><h3><i class="fa fa-cloud-upload" aria-hidden="true"></i> My Personal Drive</h3><div class="clearfix margin-bottom-10 blue_m6_logo_mail"><a href="mailto:'.$user->mail.'"><i class="fa fa-envelope-o"></i> '.$user_email.'</a></div></div>
      <ul class="list-unstyled m6-drive-list"><li><a class="'.$m6driveActiveClass.'" href="/program/m6-drive"><i class="fa fa-folder" aria-hidden="true"></i> My M6Drive</a></li><li><a class="'.$m6driveshareActiveClass.'" href="/m6drive-share-withme"><i class="fa fa-users" aria-hidden="true"></i> Shared with me</a></li><li><a class="'.$m6drivetrashActiveClass.'" href="/m6drive-trash-folder"><i class="fa fa-trash" aria-hidden="true"></i> Trash</a></li><li><a class="'.$m6drivearchiveActiveClass.'" href="/m6drive-archive"><i class="fa fa-archive" aria-hidden="true"></i> Archive</a></li></ul>
      '. $personaldriveprogress.'
      </div>
      <div class="clearfix blue_m6_logo_outer">
      <div class="clearfix margin-bottom-45"><h3 class="gray_m6_logo"><i class="fa fa-cloud-upload" aria-hidden="true"></i> '.$companyTitlevalue.' Drive</h3><div class="clearfix margin-bottom-10 blue_m6_logo_mail"><a href="mailto:'.$company_email_trim.'"><i class="fa fa-envelope-o"></i> '.$company_email.'</a></div><ul class="list-unstyled m6-drive-list"><li><a class="'.$projectdriveActiveClass.'" href="/project/drive"><i class="fa fa-cloud-upload" aria-hidden="true"></i> My Company Projects Drive</a></li><li><a class="'.$projectshareActiveClass.'" href="/project/share-drive"><i class="fa fa-users" aria-hidden="true"></i> Shared with me</a></li><li><a class="'.$projectarchiveActiveClass.'" href="/project/archive-drive"><i class="fa fa-archive" aria-hidden="true"></i> Archive</a></li><li><a class="'.$projecttrashActiveClass.'" href="/project/trash-drive"><i class="fa fa-trash" aria-hidden="true"></i> Trash</a></li></ul></div>
      '.$companydriveprogress.'
      </div>
      </div>';
  }
  return $content;
}

/**
 * Function to get form for drive search.
 */
function program_drive_folder_serach_form($form, &$form_state, $SearchKey) {
  $form['#attributes']['class'] = array('program_drive_folder_serach_form');
  $form['#attributes']['id'] = array('cust-bookmark-search-form');
  $form['search-folder'] = array(
    '#type' => 'textfield',
    '#default_value' => $SearchKey,
    '#attributes' => array('class'=> array('form-control', 'm6-drive-search-folder')),
    '#prefix' => '<div class="clearfix form-item">',
    '#suffix' => '</div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Search',
    '#attributes' => array('class' => array('search-button','cust-bookmark-search-sub')),
    '#submit'=> array('program_drive_folder_serach_submit'),
  );
  return $form;
}

/**
 * Submit handler for program_drive_folder_serach_form
 */
function program_drive_folder_serach_submit($form, &$form_state) {
  // We are using one form for search, but redirecting to different menu items
  // so checking here.
  $redirect = arg(0) == 'project' ? 'project/search' : 'm6drive/search';
  
  global $user, $company;
  $values = $form_state['values'];
  $foldervalue = str_replace(' ','_',$values['search-folder']);
  $searchkeypath = array('query' => array('searchvalue' => $foldervalue));
  drupal_goto($redirect, $searchkeypath);
  drupal_exit(0);
}

/**
 * Helper function to get Breadcrumbs for Drive.
 */
function m6drive_breadcrumb_for_folder($foldername = 0, $folderid = 0) {

  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  

  global $user, $company;
  global $base_url;
  $query = db_select('m6connect_m6drive', 'm6d');
  $query->fields('m6d',array('foldername'));
  $query->condition('m6d.user_uid', $user->uid);
  $query->condition('m6d.company_nid', $company->nid); 
  $query->condition('m6d.Id', $folderid); 
  $Currentfolder = $query->execute()->fetchField();
  $output = m6drive_get_parent_folder($folderid);
  if ($folderid == 0) {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom">
      <ul id="bc1" class="breadcrumb">
      <li class="m6drive-breadcrumb-droppable"><a class="use-ajax" href="/load-drive-data/0/0/nojs"">My M6Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
      </ul>
      </div>';
  }
  else {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
      <li  class="m6drive-breadcrumb-droppable" data="0"><a class="use-ajax" href="/load-drive-data/0/0/nojs"">My M6Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';

    // If this is a shared folder, and has been dragged into a folder,
    // then we need to check it's parent.
    $new_output = _get_parent_of_shared_folder($folderid);
    if ($new_output) {
      // If we are in, then it means that this folder is added to personal drive
      // from shared drive, and then dragged into any other folder.
      $new_outputs = m6drive_get_parent_folder($new_output);
      foreach ($new_outputs as $fldrId => $folderNameVal) {
        foreach ($folderNameVal as $foldKey => $fldVal) {
          if (_check_folder_eligibility_add_to_mydrive($foldKey)) {
            $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" data="'.$foldKey.'"><a class="use-ajax" href="/load-drive-data/'.$fldVal.'/'.$foldKey.'/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
          }
        }
      }

      // Adding the immediate parent also.
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->fields('m6d',array('foldername'));
      $query->condition('m6d.Id', $new_output); 
      $Current_new_folder = $query->execute()->fetchField();
      $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" data="'.$new_output.'"><a class="use-ajax" href="/load-drive-data/'.$Current_new_folder.'/'.$new_output.'/nojs">'.ucwords(str_replace('_',' ',$Current_new_folder)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    }
    foreach ($output as $fldrId => $folderNameVal) {
      foreach ($folderNameVal as $foldKey => $fldVal) {
        if (_check_folder_eligibility_add_to_mydrive($foldKey)) {
          $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" data="'.$foldKey.'"><a class="use-ajax" href="/load-drive-data/'.$fldVal.'/'.$foldKey.'/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
        }
      }
    }
    $breadcrumbVal .= '<li><a class="use-ajax" href="/load-drive-data/'.$foldername.'/'.$folderid.'/nojs">'.ucwords(str_replace('_',' ',$foldername)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    $breadcrumbVal .= '</li></ul></div>';
  }
  return $breadcrumbVal;
}

/**
 * Helper function to get drive table data.
 */
function get_drive_listing_table_data($folder = 0,$folderid = 0, $complteresults = array(), $only_result = FALSE) {
  global $company,$user, $base_url;
  $return = '';
  $companyName =  str_replace(' ','_',$company->title);
  $userName = str_replace(' ','_', $user->name);  
  $rows = array();
  $complteresult = array();
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');
  

  $header = array(
    array('data'=>'Drag Name','class'=>array('text-left','hidden','no-sort')),
    array('data'=>'<input type="checkbox" name="select-m6drive-folder-checkbox" class="form-checkbox select-m6drive-folder-checkbox">', 'class'=> array('text-center','hidden','no-sort')),
    array('data'=>'Name &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('personal_m6drive_filter_form',$folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Owner &nbsp;<i id="drive_filter_owner_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_owner_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('personal_m6drive_filter_using_owner_form',$folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Last Modified &nbsp;<i id="drive_filter_date_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_date_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('personal_m6drive_filter_using_date_form',$folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'File Size','class'=>array('text-left')),
    array('data'=>'Share with','class'=>array('text-left','no-sort')),
  );

  if ($only_result === FALSE) {
    if(!empty($folderid) && is_numeric($folderid)) {
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','trash_status'));
      $query->condition('m6d.parent_id', $folderid);
      $query->condition('m6d.trash_status',0,'=');
      $query->condition('m6d.archive_status', 0,'=');
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created Desc
      $record_1 = $query->execute()->fetchAll();

      // Getting add to my drive content.
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->join('m6connect_m6drive_addto_mydrive', 'm6ad', 'm6ad.folder_id = m6d.Id');
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','trash_status'));
      $query->condition('m6d.services','m6drive','=');
      $query->condition('m6d.trash_status', 0,'=');
      $query->condition('m6d.archive_status', 0,'=');
      $query->condition('m6ad.user_uid', $user->uid, '=');
      $query->condition('m6ad.parent_id', $folderid);
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created Desc
      $record_2 = $query->execute()->fetchAll();
      $record = array_merge($record_1, $record_2);

      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('file','user_uid','created_date','trash_status'));
      $querysub->condition('att.folder_id', $folderid);
      $querysub->condition('att.trash_status', 0,'=');
      $querysub->condition('att.archive_status', 0,'=');
      $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created Desc
      $recordsub = $querysub->execute()->fetchAll();
      $complteresult = array_merge($record, $recordsub);
    }
    else {
      $query = db_select('m6connect_m6drive', 'm6d');    
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','trash_status'));
      $query->condition('m6d.user_uid', $user->uid);
      $query->condition('m6d.company_nid', $company->nid);
      $query->condition('m6d.services','m6drive','=');
      $query->condition('m6d.parent_id',0,'=');
      $query->condition('m6d.trash_status', 0,'=');
      $query->condition('m6d.archive_status', 0,'=');
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
      $record_1 = $query->execute()->fetchAll();

      // Getting add to my drive content.
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->join('m6connect_m6drive_addto_mydrive', 'm6ad', 'm6ad.folder_id = m6d.Id');
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','trash_status'));
      $query->condition('m6d.services','m6drive','=');
      $query->condition('m6d.trash_status', 0,'=');
      $query->condition('m6d.archive_status', 0,'=');
      $query->condition('m6ad.user_uid', $user->uid, '=');
      $query->condition('m6ad.root', 1);
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created Desc
      $record_2 = $query->execute()->fetchAll();
      $record = array_merge($record_1, $record_2);

      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('file','user_uid','created_date','trash_status'));
      $querysub->condition('att.user_uid', $user->uid);
      $querysub->condition('att.company_nid', $company->nid);
      $querysub->condition('att.folder_id', 0,'=');
      $querysub->condition('att.trash_status', 0,'=');
      $querysub->condition('att.archive_status', 0,'=');
      $query->orderBy('att.created_date', 'DESC');//ORDER BY created Desc
      $recordsub = $querysub->execute()->fetchAll();
      // new code for shared table to my drive table fetch
       //$adtomydrive = get_folder_ad_to_mydrive_in_shared_table($user->uid);
      //
      $complteresult = array_merge($record, $recordsub);
    }
  }
  if ($only_result === TRUE && !empty($complteresults)) {
    $complteresult = $complteresults;
  }
  
  $foldericon = '';

  // Creating div structure.
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }

  $return .= '<div class="grid-view" style="' . $grid_display . '">';
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
  $return .= '<div class="grid-view-folders row margin-5">';
  // First handling only Folders.
  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $folders_present = FALSE;
  $files_present = FALSE;
  foreach ($complteresult as $key => $value) {
    if ($value->foldername) {
      $folders_present = TRUE;
    }
    if ($value->file && $filevalue = file_load($value->file)) {
      $files_present = TRUE;
    }
  }
  if (!$folders_present) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
  }
  else {
    foreach ($complteresult  as $values) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      if ($values->foldername) {
        $foldername = strlen($values->foldername) > 22 ? substr($values->foldername, 0, 19) . '...' : $values->foldername;
        $return .= '<div id="' . $values->Id . '" class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10 m6drive-folder-droppable m6drive-folder-dragable">';
        $return .= '<div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">' . $values->Id. '-folder</span></div>';
        $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="' . ucwords(str_replace('_',' ',$values->foldername)) . '" name="m6drive-folder-' . $values->Id . '" value="' . $values->Id . '-folder" class="form-checkbox m6drive-folder-checkbox"></div>';
        $foldericon = '<img src="' . $drive_folder_icon . '" class="padding-5" style="width:50px;">' . ucwords(str_replace('_', ' ', $foldername));
        $return .= '<div class="grid-item-anchor clearfix m6drive-drag-content-show">';
        $return .= l($foldericon, 'load-drive-data/' . $values->foldername . '/' . $values->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none', 'margin-5'), 'id' => 'estimate-td-' . $values->Id), 'html' => TRUE));
        $return .= '</div>'; //end grid-item-anchor.
        $return .= '</div>'; //end grid-view-folder-item
      }
    }
  }
  $return .= '</div>'; //end grid-view-folders

  // Then handling only Files.
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
  $return .= '<div class="grid-view-files row margin-5">';
  if (!$files_present) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
  }
  else {
    foreach ($complteresult  as $values) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      if ($values->file &&  $filevalue = file_load($values->file)) {
        $return .= '<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10 m6drive-folder-dragable">';
        $fid =  $values->file;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        //$img_url = image_style_url('user_image_large', $uri);
        $filename =  $filevalue->filename;
        $filename_str = strlen($filename) > 22 ? substr($filename, 0, 19) . '...' : $filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
        if ($fileicondrive) {
           $img_url = $fileicondrive;
        }
        else {
          $img_url = image_style_url('user_image_large', $uri);
          $img_url = '<img src= '.$img_url.'>';
        }
        $return .= '<div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">'.$fid.'-file</span></div>';
        $img_src = '<span class="orignal-img" style="display:none;">' . $filepath . '</span> ' .$img_url . '<div class="clearfix text-blue grid-item-anchor m6drive-drag-content-show">' . $filename_str . '</div>';
        $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-folder-checkbox"></div>';
        $return .= $img_src;
        $return .= '</div>'; // end grid-view-file-item.
      }
    }
  }
  $return .= '</div>'; // end grid-view-files.
  $return .= '</div>'; // end grid-view.
  
  // Creating table data.
  foreach ($complteresult  as $values) {
    $UserFnameLname =_get_user_data_by_uid($values->user_uid);
    if ($values->foldername) {
      $foldername_str = strlen($values->foldername) > 22 ? substr($values->foldername, 0, 19) . '...' : $values->foldername;
      $foldericon   ='<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">'.ucwords(str_replace('_',' ',$foldername_str));
      $foldername =  l($foldericon, 'load-drive-data/' . $values->foldername . '/' . $values->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));
      $share_with_url = m6drive_check_file_folder_shared('folder', $values->Id);
      $rows[] = array(
        'data' => array(
          array('data'=>'<span class="folder-ids" style="display:none;">'.$values->Id.'-folder</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-folder-checkbox"></div>', 'class'=> array('text-center','hidden')),
          array('data'=> $foldername, 'class' => array('text-left','m6drive-drag-content-show','drive-getting-folder')),
          array('data' => $UserFnameLname['realname'],'class' => array('text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('text-left')),
          array('data'=>'-','class'=>array('text-left')),
          array('data'=> $share_with_url,'class'=>array('text-left')),         
         ),
        'id' => array(''.$values->Id.''),   
        'class' => array('custom-odd','customsearchformydrive','m6drive-folder-droppable','m6drive-folder-dragable','m6drive-folderdelete-'.$values->Id.'-'.$company->nid.'-row'),
       );
    }
    if ($values->file &&  $filevalue = file_load($values->file)) {
      $fid =  $values->file;
             //$filevalue = file_load($fid);
      $uri = $filevalue->uri;
      $filename =  $filevalue->filename;
      $filename_str = strlen($filename) > 22 ? substr($filename, 0, 19) . '...' : $filename;
      $filetype = $filevalue->type;
      $filepath = file_create_url($uri);  
      $Attachment = l($filename_str, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id)));
      $share_with_url = m6drive_check_file_folder_shared('file', $fid);
      $rows[] = array(
        'data' => array(
          array('data'=>'<span class="folder-ids" style="display:none;">'.$fid.'-file</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-folder-checkbox"></div>', 'class'=> array('text-center','hidden')),
          array('data'=>  $Attachment, 'class' => array('text-left','m6drive-drag-content-show','drive-getting-folder')),
          array('data' => $UserFnameLname['realname'],'class' => array('text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('text-left')),
          array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('text-left')),
          array('data'=> $share_with_url,'class'=>array('text-left')),
                //array('data' => m6drive_folder_action_btn('file',$fid),'class' => array('col-md-2','text-left')),           
        ),  
        'class' => array('custom-odd','customsearchformydrive','m6drive-folder-dragable','m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
      );
    }
  }

  $return .= '<div class="list-view" style="' . $list_display . '">';
  $return .= theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-folder-name','table-striped','table-hover','table-bordered','text-center'))));
  $return .= '</div>';
  return $return;
}

/**
 * Function to get drive add new form.
 */
function m6drive_add_new_form($form, &$form_state, $parentid) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  global $user;
  $userprofile = user_load($user->uid);
  $fid = $userprofile->field_user_profile_photo['und'][0]['fid']; 
  $parentid = (isset($form_state['parent_id']) && is_numeric($form_state['parent_id'])) ? $form_state['parent_id']: $parentid;
  $form_state['parent_id'] = $parentid;
  $input = &$form_state['input'];
  $values = &$form_state['values'];

  $form['folder_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Folder Name'),
  );
  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();'))),      
    '#weight' => 10,  
  );
  $form['submit'] = array(
    '#value' => 'Submit', 
    '#type' => 'submit', 
    '#attributes' => array( 'class' => array('m6drive-add-new-form-submit')),
  );
  return $form;
}

/**
 * Submit handler for m6drive_add_new_form
 */
function m6drive_add_new_form_submit(&$form, &$form_state) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  global $user, $company;
  $values = $form_state['values'];
  $parentid = $form_state['parent_id'];
  $foldervalue = str_replace(' ', '_', $values['folder_name']);
  // Get Current folder name
  $query = db_select('m6connect_m6drive', 'm6d');
  $query->fields('m6d',array('foldername'));
  $query->condition('m6d.user_uid', $user->uid);
  $query->condition('m6d.company_nid', $company->nid); 
  $query->condition('m6d.Id', $parentid);      
  $Currentfolder = $query->execute()->fetchField();

  // Get parent folder name
  $output = m6drive_get_parent_folder($parentid);
  foreach($output as $key=>$values){
    $Parentfolder .=  implode("",$values)."/"; 
  }

  if (isset($Currentfolder) && !empty($Currentfolder)) {
    $foldername =  $Parentfolder.$Currentfolder.'/'.$foldervalue;
  }
  else {
    $foldername = $foldervalue;
  }

  $companyName =  str_replace(' ', '_', $company->title);
  $userName = str_replace(' ', '_', $user->name);

  if (isset($foldervalue) && !empty($foldervalue)) {
    $modifiedDate =  date('Y-m-d H:i:s');
    db_insert('m6connect_m6drive')
      ->fields(array(
        'company_nid'=> $company->nid,
        'user_uid'=> $user->uid,
        'services'=> 'm6drive',
        'created_date' =>$modifiedDate,
        'foldername' => $foldervalue,
        'parent_id' => $parentid,
        'trash_status' => 0,
        'archive_status' => 0,
      ))
      ->execute();

    if(!class_exists('S3')) include_once DRUPAL_ROOT . '/sites/all/libraries/awssdk1/S3.php';
    if(!defined('awsAccessKey')) define('awsAccessKey', 'AKIAJZCVB5B62KPYTLFA');
    if(!defined('awsSecretKey')) define('awsSecretKey', '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');
    $s3 = new S3(awsAccessKey, awsSecretKey);
    $s3->putObjectFile('M6Drive.txt', 'dev.repo.m6connect.com', 's3fs-private/'.$companyName.'/M6Drive/'.$userName.'/'.$foldername.'/M6Drive.txt', S3::ACL_PRIVATE);
   }

  if ($parentid == 0) {
    $form_state['ajax_commands'][] = ajax_command_html("#m6-drive-datacontainer-main-cust", get_drive_listing_table_data(0,0));
  }
  else {
    $form_state['ajax_commands'][] = ajax_command_html("#m6-drive-datacontainer-main-cust", get_drive_listing_table_data($Currentfolder, $parentid));
  }
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss(); 
  }
}

/**
 * Function to generate form to upload a new file.
 */
function m6drive_upload_new_file_form($form, &$form_state, $parentid) {
  global $user, $company;

  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  
 
  $totalSpaceInDrive = _get_m6drive_total_space_user_uid($user->uid, TRUE);
  $totalSpaceInDrive = $totalSpaceInDrive / 1073741824;
  $user_allocatespace = user_personal_drive_total_space_count($user->uid);
  
  if ($totalSpaceInDrive >= $user_allocatespace) {
    $form['total-space'] = array(
      '#markup' => '<div class="over-space-memmory"><p>Please contact <a href="mailto:support@m6connect.com">support@m6connect.com</a> for more space.</p></div>',
    );
    $form['cancel-button'] = array(
      '#markup' => l('<input type="button" class="btn btn primary form-submit" value="Close" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();'))),
    );
  }
  else {
    $parentid = (isset($form_state['parent_id']) && is_numeric($form_state['parent_id'])) ? $form_state['parent_id']: $parentid;
    $form_state['parent_id'] = $parentid; 
      //********************Get Current folder name******************//
    $query = db_select('m6connect_m6drive', 'm6d');
    $query->fields('m6d',array('foldername'));
    $query->condition('m6d.user_uid', $user->uid);
    $query->condition('m6d.company_nid', $company->nid); 
    $query->condition('m6d.Id', $parentid);      
    $Currentfolder = $query->execute()->fetchField();

    // Get parent folder name
    $output = m6drive_get_parent_folder($parentid);
    foreach($output as $key=>$values){
      $Parentfolder .=  implode("",$values)."/"; 
    }

    $companyName =  str_replace(' ', '_', $company->title);
    $userName = str_replace(' ', '_', $user->name);
    if (isset($Currentfolder) && !empty($Currentfolder)) {
      $folderlocation = ''.$companyName.'/M6Drive/'.$userName.'/'.$Parentfolder.$Currentfolder.'/';
    }
    else {
      $folderlocation = ''.$companyName.'/M6Drive/'.$userName.'/';
    }

    $form['#prefix'] = '<div class="m6drive-file-upload-custom">';
    $form['#suffix'] = '</div>';

    // Plupload 
    $form['m6drive-file'] = array(
      '#type' => 'plupload',
      "#upload_validators"  => array(
        "file_validate_size" => array(1024*1280*800),
        "file_validate_extensions" => array("txt pdf oxps pub pages docx pptx ppt indd pmd doc jpg jpeg png gif xls xlsx zip tar.gz tar sql rar mov gif mkv mp4"),
      ),
    );

    $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));

    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#submit'=> array('m6drive_upload_new_file_form_submit'),
      '#value' => 'Save',
      '#prefix' => '<div class="clearfix">',  
      '#suffix' => $closeButton.'</div>', 
    );
  }
  return $form;
}

/**
 * Submit handler for m6drive_upload_new_file_form
 */
function m6drive_upload_new_file_form_submit($form, &$form_state){
  global $user, $company;  
  $value = $form_state['values'];
  $filefid = $value['m6drive-file'];
  $parentid = $form_state['parent_id'];

  // Get Current folder name
  $query = db_select('m6connect_m6drive', 'm6d');
  $query->fields('m6d',array('foldername'));
  $query->condition('m6d.user_uid', $user->uid);
  $query->condition('m6d.company_nid', $company->nid); 
  $query->condition('m6d.Id', $parentid);      
  $Currentfolder = $query->execute()->fetchField();

  // Get parent folder name
  $output = m6drive_get_parent_folder($parentid);
  foreach($output as $key=>$values){
    $Parentfolder .=  implode("",$values)."/"; 
  }

  $companyName =  str_replace(' ','_',$company->title);
  $userName = str_replace(' ','_',$user->name); 

  if (isset($Currentfolder) && !empty($Currentfolder)) {
    $folderlocation = ''.$companyName.'/M6Drive/'.$userName.'/'.$Parentfolder.$Currentfolder.'/';
  }
  else {
    $folderlocation = ''.$companyName.'/M6Drive/'.$userName.'/';
  }

  $files = $value['m6drive-file'];  
  $saved_files = array();
  $scheme = 'public://';
  foreach ($files as $uploaded_file) {
    if ($uploaded_file['status'] == 'done') {
      $source = $uploaded_file['tmppath'];
      $destination = file_stream_wrapper_uri_normalize($scheme . $uploaded_file['name']);
      $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
      $file = plupload_file_uri_to_object($destination);
      $destination = file_stream_wrapper_uri_normalize('private://'.$folderlocation);
      file_save($file);
      file_prepare_directory($destination, FILE_CREATE_DIRECTORY|FILE_MODIFY_PERMISSIONS);
      $new_file = file_move($file, $destination, FILE_EXISTS_RENAME);
      $saved_files[] = $new_file;
    }
  }

  if(!empty($saved_files)){
    foreach($saved_files as $filevalue) {
      $modifiedDate =  date('Y-m-d H:i:s');
      db_insert('m6connect_m6drive_attachment')
        ->fields(array(
          'company_nid'=> $company->nid,
          'user_uid'=> $user->uid,
          'file' => $filevalue->fid,
          'created_date' => $modifiedDate,
          'folder_id' => $parentid,
          'trash_status' => 0,
          'archive_status' => 0,
          'services' => 'm6drive',
          ))
        ->execute();
    }
  }

  if($parentid == 0){
    $form_state['ajax_commands'][] = ajax_command_html("#m6-drive-datacontainer-main-cust", get_drive_listing_table_data(0,0));
  }
  else {
    $Currentfolder = get_folder_name_by_folderid($parentid);
    $form_state['ajax_commands'][] = ajax_command_html("#m6-drive-datacontainer-main-cust", get_drive_listing_table_data($Currentfolder->foldername, $parentid));
  }
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Helper function to generate drive share form.
 */
function m6drive_share_with_other_form($form, &$form_state, $sharetype, $shareid) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  $shareid = (isset($form_state['share_id']) && is_numeric($form_state['share_id'])) ? $form_state['share_id'] : $shareid;
  $sharetype = (isset($form_state['share_type'])) ? $form_state['share_type'] : $sharetype;
  $form_state['share_id']= $shareid; 
  $form_state['share_type'] = $sharetype;

  $form['share_email'] = array(
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control'),'placeholder'=>'Enter Email address...'),
    '#required' => TRUE,
    '#prefix' => '<div class="clearfix share_popupsection margin-bottom-45"><div class="clearfix"><label>People</label></div><div class="clearfix text-right"><label>Permissions</label></div><div class="clearfix"><div class="input-group">',
    '#element_validate' => array('m6drive_share_email_element_validate'),
  );

  $active = array('r' => t('<label for="ex1_3_1">Can View</label>'), 'r-o' => t('<label for="ex1_3_1">Can View & Organise</label>'), 'r-w-o' => t('<label for="ex1_3_1">Can View, Organise & Download</label>'));
  
  $form['share_permission'] = array(
    '#type' => 'radios',
    '#default_value' => 'r',
    '#options' => $active,
    '#prefix' => '<span class="input-group-btn">
      <div class="input-group-btn">
      <button data-toggle="dropdown" class="btn btn-primary dropdown-toggle onclickBtn_popup" style="margin:0;     height: 32px;"><i class="fa fa-eye" aria-hidden="true"></i> <span class="caret"></span></button>
      <ul class="dropdown-menu dropdown-menu-right">',
    '#suffix' => '</ul></div></span>
      </div>
      </div>
      </div>',
  );

  if (!is_numeric($shareid)) {
    $form['for_multiple'] = array(
      '#type' => 'hidden',
      '#value' => '1',
      '#attributes' => array('class' => array('for_multishare_test')),
    );
    $form['share_ids'] = array(
      '#type' => 'textarea',
      '#attributes'=> array('class'=> array('multiple-share-ids')),
      '#prefix' => '<div style="display:none;">',
      '#suffix' => '</div>'
    );
  }
  else {
    $form['for_multiple'] = array(
      '#type' => 'hidden',
      '#value' => '0',
      '#attributes' => array('class' => array('for_multishare_test')),
    );
  }
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click(); Drupal.attachBehaviors();')));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_share_with_other_submit'),
    '#value' => 'Done',
    '#prefix' => '<div class="clearfix margin-bottom-25">',
    '#suffix' => $closeButton . '</div></div></div>', 
  );

  return $form;
}

/**
 * Email validate for share email
 */
function m6drive_share_email_element_validate($element, &$form_state, $form) {
  if (!valid_email_address($element['#value'])) {
    form_error($element, t('Please enter a valid email address.'));
  }
}

/**
 * Submit handler for m6drive_share_with_other_form
 */
function m6drive_share_with_other_submit($form, &$form_state){
  global $user, $base_url;
  $shareid = $form_state['share_id'];
  $sharetype = $form_state['share_type']; 
  $values = $form_state['values']; 
  $share_email = $values['share_email'];
  $shreMultiple = $values['share_ids'];

  if ($values['share_permission']) {
    $permdrive = $values['share_permission']; 
  }
  else {
    $permdrive = 'r';
  }

  if(empty($shreMultiple)) {
    if (isset($sharetype) && is_numeric($shareid)) {
      $usersfulldetails = _get_user_details_by_og_email($share_email);
      if(!empty($usersfulldetails->uid)){
        $shareto_uid =  $usersfulldetails->uid;
      }
      else{
        $shareto_uid = 0;
      }

      if ($sharetype == 'folder') {
        $sharedate =  date('Y-m-d H:i:s');
        db_insert('m6connect_m6drive_shared')
          ->fields(array(
            'share_by_uid'=> $user->uid,
            'share_to_uid'=> $shareto_uid,
            'folder_id' => $shareid,
            'shared_date' => $sharedate,
            'email_id' => $share_email, 
            'fid' => NULL,
            'delete_status' => 0,
            'root' => 1,
            'services' => 'm6drive',
            'permissions' => $permdrive,
          ))
          ->execute();
      }
      if ($sharetype == 'file') {
        $sharedate =  date('Y-m-d H:i:s');
        db_insert('m6connect_m6drive_shared')
          ->fields(array(
            'share_by_uid'=> $user->uid,
            'share_to_uid'=> $shareto_uid,
            'folder_id' => NULL,
            'shared_date' => $sharedate,
            'email_id' => $share_email,
            'fid' => $shareid,
            'delete_status' => 0,
            'root' => 1,
            'services' => 'm6drive',
            'permissions' => $permdrive,
          ))
          ->execute();
      }
    }
  }
  else {
    $usersfulldetails = _get_user_details_by_og_email($share_email);
    if(!empty($usersfulldetails->uid)){
      $shareto_uid =  $usersfulldetails->uid;
    }
    else {
      $shareto_uid = 0;
    }
    $filefolder =  explode( ',' ,$shreMultiple);
    if (!empty($filefolder)) {
      foreach ($filefolder as $multKey => $multVal) {
        $getStatus = explode('-', $multVal);
        if ($getStatus[1] == 'folder') {
          $folderIdMul = $getStatus[0];
          _clear_child_folder_files_share($folderIdMul, $shareto_uid);
          _share_folder_and_files_personal($folderIdMul, $share_email, $permdrive);

          $sharedate =  date('Y-m-d H:i:s');

          db_delete('m6connect_m6drive_shared')
            ->condition('share_by_uid', $user->uid)
            ->condition('share_to_uid', $shareto_uid)
            ->condition('folder_id', $folderIdMul)
            ->execute();

          db_insert('m6connect_m6drive_shared')
            ->fields(array(
              'share_by_uid'=> $user->uid,
              'share_to_uid'=> $shareto_uid,
              'folder_id' =>  $folderIdMul,
              'shared_date' => $sharedate,
              'email_id' => $share_email, 
              'fid' => NULL,
              'delete_status' => 0,
              'root' => 1,
              'services' => 'm6drive',
              'permissions' => $permdrive,
            ))
            ->execute();
        }
        elseif ($getStatus[1] == 'file') {
          $fileIdMul = $getStatus[0];
          $sharedate =  date('Y-m-d H:i:s');

          db_delete('m6connect_m6drive_shared')
            ->condition('share_by_uid', $user->uid)
            ->condition('share_to_uid', $shareto_uid)
            ->condition('fid', $fileIdMul)
            ->execute();

          db_insert('m6connect_m6drive_shared')
            ->fields(array(
              'share_by_uid'=> $user->uid,
              'share_to_uid'=> $shareto_uid,
              'folder_id' => NULL,
              'shared_date' => $sharedate,
              'email_id' => $share_email,
              'fid' => $fileIdMul,
              'delete_status' => 0,
              'root' => 1,
              'services' => 'm6drive',
              'permissions' => $permdrive,
            ))
            ->execute();

        }
      }

      // Sending email when drive shared to user
      $folder_shareicon = $base_url . '/sites/all/themes/m6connect/images/folder_share.png';
      $file_shareicon = $base_url . '/sites/all/themes/m6connect/images/file_share_icon.png';
      $UserFnameLname =_get_user_data_by_uid($user->uid);
      $message = "<div style='padding:20px;background:#F5F5F5; border:1px solid #EEE; margin:60px 100px;'>";

      $folder_shared = 0;
      $file_shared = 0;

      $sh_message2 = '';
      if (!empty($filefolder)) {
        foreach ($filefolder as $multKey => $multVal) {
          $getStatus = explode('-', $multVal);
          if ($getStatus[1] == 'folder') {
            $folder_shared++;
            $folderIdMul = $getStatus[0];
            $getfoldername = get_folder_name_by_folderid($folderIdMul);
            $sh_message2 .= '<p><a style="text-decoration:none; font-size:16px;color:#265a7f;font-weight:700;" href="'.$base_url.'/m6drive-share-withme"><img style="vertical-align:bottom;padding:0 5px 0 0;" src="'.$folder_shareicon.'" alt="Drive"/>'.ucwords(str_replace('_',' ',$getfoldername->foldername)).'</a></p>';
          }
          elseif ($getStatus[1] == 'file') {
            $file_shared++;
            $fileIdMul = $getStatus[0];
            $fileObj =  file_load($fileIdMul);
            $url = file_create_url($fileObj->uri);
            $sh_message2 .= '<p><a style="text-decoration:none; font-size:16px;color:#265a7f;font-weight:700;" href="'.$url.'"><img style="vertical-align:bottom;padding:0 5px 0 0;" src="'.$file_shareicon.'" alt="File"/>'.$fileObj->filename.'</a></p>';
          }
        }
      }

      $folders_mark = ' a folder ';
      $files_mark = ' a file ';

      $sh_message = '';
      if ($folder_shared > 0) {
        $folders_mark = $folder_shared == 1 ? ' a folder ' : ' some folders ';
        $sh_message = '<p>' . ucwords($UserFnameLname['realname']) . ' has shared' . $folders_mark . 'with you on your Personal Drive:</p><br/>';
      }
      if ($file_shared > 0) {
        $files_mark = $file_shared == 1 ? ' a file ' : ' some files ';
        $sh_message = '<p>' . ucwords($UserFnameLname['realname']) . ' has shared' . $files_mark . 'with you on your Personal Drive:</p><br/>';
      }
      if ($folder_shared > 0 && $file_shared > 0) {
        $sh_message = '<p>' . ucwords($UserFnameLname['realname']) . ' has shared' . $folders_mark . 'and' . $files_mark . 'with you on your Personal Drive:</p><br/>';
      }

      $message .= $sh_message;
      $message .= $sh_message2;

      $message .= '<div>';
      $form =  ucwords($UserFnameLname['realname']);
      $params = array(
        'subject' => 'M6 Drive Shared With Me',
        'body' =>  $message,
        'sender' =>  $user->mail,
        'language' => language_default(),
        'module' => 'm6connect_misc',
        'key' => 'commitment_mail___invite_2_m6_notify_share',
        'build' => TRUE,
      );
      if (!empty($share_email)) {
        $mail_sent = drupal_mail($params['module'], $params['key'], $share_email, $params['language'], $params);
        watchdog('mail_sent', print_r($mail_sent, 1));
      }
    }
  }

  drupal_set_message('Successfully shared');
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/program/m6-drive');
  }
}

/**
 * Helper function to get share drive left panel content.
 */
function _get_shared_left_drive_panel($prjectnid = 0,  $current_path, $folder_id = 0) {
  global $base_path, $user, $company;

  if (!empty($company->nid)) {
    $node = node_load($company->nid);
    $companyTitle =  $node->title;
    if (!empty($companyTitle)) {
      $companyTitlevalue = (strlen($companyTitle) > 11) ? substr($companyTitle, 0, 8) . '...' : $companyTitle;
     }

    $company_email_trim = m6drive_get_primary_company_email($company->nid, $user->uid);
    if (!empty($company_email_trim)) {
      $company_email = (strlen($company_email_trim) > 24) ? substr($company_email_trim, 0, 21) . '...' : $company_email_trim;
    }

    if (!empty($user->mail)) {
      $user_email = (strlen($user->mail) > 24) ? substr($user->mail, 0, 21) . '...' : $user->mail;
    }
  }

  $current_path = current_path();

  if ($current_path == 'program/m6-drive' || arg(0) == 'load-drive-data') {
    $m6driveActiveClass = 'active';  
  }
  elseif ($current_path == 'm6drive-share-withme' || arg(0) == 'share-load-drivedata') {
    $m6driveshareActiveClass = 'active'; 
  }
  elseif ($current_path == 'm6drive-trash-folder' || arg(0) == 'trash-load-drive-data') {
    $m6drivetrashActiveClass = 'active'; 
  }
  elseif ($current_path == 'm6drive-archive'  || arg(0) == 'archive-load-drive-data') {
    $m6drivearchiveActiveClass = 'active'; 
  }
 
  // Project drive
  elseif ($current_path == 'project/drive' || arg(0) == 'project-load-drive') {
    $projectdriveActiveClass = 'active'; 
  }
  elseif ($current_path == 'project/share-drive' || arg(0) == 'project-share-load-drive') {
    $projectshareActiveClass = 'active'; 
  }
  elseif ($current_path == 'project/archive-drive' || arg(0) == 'project-archive-load-drive') {
    $projectarchiveActiveClass = 'active'; 
  }
  elseif($current_path == 'project/trash-drive' || arg(0) == 'project-trash-load-drive') {
    $projecttrashActiveClass = 'active'; 
  }

  $totalSpaceInDrive = _get_m6drive_total_space_user_uid($user->uid);
  $totalProjectSpace = _get_total_space_project_drive_by_uid($user->uid);

  $company_allocatespace = user_company_drive_total_space_count($company->nid);
  $user_allocatespace = user_personal_drive_total_space_count($user->uid);

  $personaldriveprogress = personal_drive_progress_bar();
  $companydriveprogress = company_project_drive_progress_bar();


  $content = '<div class="clearfix"><div class="m6-drive-buttons clearfix text-uppercase margin-bottom-20"><div class="clearfix"><a href="/addnew-m6drive-project/' . $prjectnid . '/' . $folder_id . '/nojs" title="New Folder" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success">New Folder</a><a href="/uploadfile-m6drive-project/' . $prjectnid . '/' . $folder_id . '/nojs" title="Upload File" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style btn btn-success triggering-upload">Upload</a></div></div>';

  $content .= '<div class="clearfix blue_m6_logo_outer">
    <div class="clearfix blue_m6_logo"><h3><i class="fa fa-cloud-upload" aria-hidden="true"></i> My Personal Drive</h3><div class="clearfix margin-bottom-10 blue_m6_logo_mail"><a href="mailto:'.$user->mail.'"><i class="fa fa-envelope-o"></i> '.$user_email.'</a></div></div><ul class="list-unstyled m6-drive-list"><li><a class="'.$m6driveActiveClass.'" href="/program/m6-drive"><i class="fa fa-folder" aria-hidden="true"></i> My M6Drive</a></li><li><a class="'.$m6driveshareActiveClass.'" href="/m6drive-share-withme"><i class="fa fa-users" aria-hidden="true"></i> Shared with me</a></li><li><a class="'.$m6drivetrashActiveClass.'" href="/m6drive-trash-folder"><i class="fa fa-trash" aria-hidden="true"></i> Trash</a></li><li><a class="'.$m6drivearchiveActiveClass.'" href="/m6drive-archive"><i class="fa fa-archive" aria-hidden="true"></i> Archive</a></li></ul>
    '.$personaldriveprogress.'
    </div>
    <div class="clearfix blue_m6_logo_outer">
    <div class="clearfix margin-bottom-45"><h3 class="gray_m6_logo"><i class="fa fa-cloud-upload" aria-hidden="true"></i> '.$companyTitlevalue.' Drive</h3><div class="clearfix margin-bottom-10 blue_m6_logo_mail"><a href="mailto:'.$company_email_trim.'"><i class="fa fa-envelope-o"></i> '.$company_email.'</a></div><ul class="list-unstyled m6-drive-list"><li><a class="'.$projectdriveActiveClass.'" href="/project/drive"><i class="fa fa-cloud-upload" aria-hidden="true"></i> My Company Projects Drive</a></li><li><a class="'.$projectshareActiveClass.'" href="/project/share-drive"><i class="fa fa-users" aria-hidden="true"></i> Shared with me</a></li><li><a class="'.$projectarchiveActiveClass.'" href="/project/archive-drive"><i class="fa fa-archive" aria-hidden="true"></i> Archive</a></li><li><a class="'.$projecttrashActiveClass.'" href="/project/trash-drive"><i class="fa fa-trash" aria-hidden="true"></i> Trash</a></li></ul></div>
    '.$companydriveprogress.'
    </div></div>';

  return $content;
}

/**
 * Function to get shared drive breadcrumb.
 */
function m6drive_shraed_breadcrumb_for_folder($folder, $folderid) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 
  if ($folderid == 0) {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
      <li><a class="use-ajax" href="/share-load-drivedata/0/0/nojs">Shared with</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
      </ul></div>';
  }
  else {
    $output = m6drive_get_parent_folder($folderid);

    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom search-folder-breadcrumb-custom-shared"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/share-load-drivedata/0/0/nojs">Shared with</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';

    foreach ($output as $fldrId => $folderNameVal) {
      foreach($folderNameVal as $foldKey => $fldVal) {
        if (_check_folder_eligibility_share($foldKey)) {
          $breadcrumbVal .= '<li class="m6drive-shared-breadcrumb-droppable" data="' . $foldKey . '"><a class="use-ajax" href="/share-load-drivedata/'.$fldVal.'/'.$foldKey.'/nojs">'. ucwords(str_replace('_',' ',$fldVal)) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
        }
      }
    }
    $breadcrumbVal .= '<li><a class="use-ajax" href="/share-load-drivedata/'.$folder.'/'.$folderid.'/nojs">'.ucwords(str_replace('_',' ',$folder)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    $breadcrumbVal .= '</ul></div>';
  }
  return $breadcrumbVal;
}

/**
 * Helper function to get content for share drive.
 */
function m6drive_share_withme_content($folder = 0, $folderid = 0, $complteresults = array(), $only_result = FALSE) {
  global $user, $company, $base_url;
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');
  $output = array();
  $rows = array();
  $divstr_arr = array();
  $divstrinner_arr = array();
  $header = array(
    array('data'=>'Drag Name','class'=>array('text-left','hidden','no-sort')),
    array('data'=>'<input type="checkbox" name="select-m6drive-folder-checkbox" class="form-checkbox select-m6drive-folder-checkbox">', 'class'=> array('text-center','hidden','no-sort')),
    array('data'=>'Name &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('personal_share_m6drive_filter_form',$folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Shared by &nbsp;<i id="drive_filter_owner_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_owner_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('personal_share_m6drive_filter_owner_form', $folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Shared date','class'=>array('text-left','drive_filter_header')),
    array('data'=>'File Size','class'=>array('text-left')),
  );
  $foldericon = '';
  $companyusersdetail = '';
  $companyusersfullname = '';
  $optionview = 'List';
  $folders_present = FALSE;
  $files_present = FALSE;
  
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }
  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';

  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';

  if ((!empty($folderid) && is_numeric($folderid)) || $only_result === TRUE) {
    $sharedData =  get_m6drive_share_date_name($user->uid, $folderid);

    if (!empty($folderid)) {
      $query = db_select('m6connect_m6drive', 'm6d');    
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date'));
      $query->condition('m6d.parent_id', $folderid);
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
      $record = $query->execute()->fetchAll();
      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('user_uid','file','created_date'));
      $querysub->condition('att.folder_id', $folderid);
      $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created
      $recordsub = $querysub->execute()->fetchAll();
      $complteresult = array_merge($record, $recordsub);
    }

    if (!empty($complteresult)) {
      //
      if (!empty($complteresults)) {
        $complteresult = array_merge($complteresult, $complteresults);
      }
    }
    elseif (!empty($complteresults)) {
      $complteresult = $complteresults;
    }

    foreach ($complteresult  as $values) {
      $divstrinner_arr[] = $values;  
      $companyusersdetail = _get_user_data_by_uid($values->user_uid);
      $companyusersfullname = $companyusersdetail['realname'];

      if (m6connect_m6drive_sharedbyfolderID($values->Id, $user->uid)) {
        $query = m6connect_m6drive_sharedbyfolderID($values->Id, $user->uid);
        if ($query->permissions) {
          $permissionsfol = $query->permissions;
        }
        elseif (m6connect_m6drive_sharedbyfolderID($folderid, $user->uid)) {
          $query = m6connect_m6drive_sharedbyfolderID($folderid, $user->uid);
          if($query->permissions) {
            $permissionsfol = $query->permissions;
          }
          else {
            $permissionsfol =  getJustparent_folderID($folderid, $user->uid);
          }
        }
        else {
          $permissionsfol =  getJustparent_folderID($folderid, $user->uid);
        }
      }


      if ($values->foldername && _check_folder_eligibility_share($values->Id)) {
        if ($permissionsfol == 'r-w-o') {
          $Dragclass = 'm6drive-folder-dragable';
          $Dropclass = 'm6drive-folder-droppable';
          $attr = 'data="'.ucwords(str_replace('_',' ',$values->foldername)).'" value="'.$values->Id.'-folder" name="m6drive-shared-folder-'.$values->Id.'" class="form-checkbox m6drive-folder-checkbox"';
        }
        elseif ($permissionsfol == 'r-o') {
          $Dragclass = 'm6drive-folder-dragable';
          $Dropclass = 'm6drive-folder-droppable';
          $attr = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
        }
        else {
          $attr = 'data-attr ="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
        }

        $buttonoutput =  '<div class="btn-group"><div class="dropdown">
          <button id="" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="">
          <li>'.l('Download','m6drive-download/folder/'.$values->Id.'/nojs', array('attributes'=> array('class'=>array('')))).'</li>
          </ul></div></div>';

        $foldericon   = $Drive_folder_icon_image .ucwords(str_replace('_',' ',$values->foldername)).'';
        $foldername =  l($foldericon, 'share-load-drivedata/'.$values->foldername.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html'=>TRUE));
        $rows[] = array(
          'data' => array(
            array('data'=>'<span class="folder-ids" style="display:none;">'.$values->Id.'-folder</span>', 'class'=> array('m6drive-display-none-drag','hidden')), 
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.' ></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=> $foldername, 'class' => array('text-left','m6drive-drag-content-show','drive-getting-folder')),
            array('data' => $companyusersfullname,'class' => array('text-left')),
            array('data' => date('F d, Y', strtotime($sharedData->shared_date)),'class' => array('text-left')),
            array('data'=>'-','class'=>array('text-left')), 
          ),
          'id' => array(''.$values->Id.''),   
          'class' => array('custom-odd', $Dragclass, $Dropclass,'customsearchformydrive','m6drive-folderdelete-'.$values->Id.'-'.$company->nid.'-row'),
        );
      }
      if ($values->file && _check_file_eligibility_share($values->file) && $filevalue = file_load($values->file)) {
        $fid =  $values->file;
        $buttonoutput =  '<div class="btn-group"><div class="dropdown">
          <button id="" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="">
          <li>'.l('Download','m6drive-download/file/'.$fid.'/nojs', array('attributes'=> array('class'=>array('')))).'</li>
          </ul></div></div>';

        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id)));

        $queryfidPar = db_select('m6connect_m6drive_shared', 'd')
          ->fields('d')
          ->condition('fid', $fid)
          ->condition('share_to_uid', $user->uid)
          ->execute()
          ->fetchAll();

        if ($queryfidPar[0]->permissions) {
          $permissionsfolf = $queryfidPar[0]->permissions; 
          if($permissionsfolf == 'r-w-o'){
            $Dragclass = 'm6drive-folder-dragable';
            $Dropclass = 'm6drive-folder-droppable';
            $attrfile = 'data="'.$filename.'" value="'.$fid.'-file" name="m6drive-shared-file-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"';
          }
          elseif ($permissionsfolf == 'r-o') {
            $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
            $fileName = l($filename, 'javascript:',  array('external' => TRUE));
            $Dragclass = 'm6drive-folder-dragable';
            $Dropclass = 'm6drive-folder-droppable';
          }
          else {
            $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
            $fileName = l($filename, 'javascript:',  array('external' => TRUE));
          }
        }
        else {
          if($permissionsfol == 'r-w-o'){
            $attrfile = 'data="'.$filename.'" value="'.$fid.'-file" name="m6drive-shared-file-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"';
          }
          elseif ($permissionsfol == 'r-o') {
            $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
            $fileName = l($filename, 'javascript:',  array('external' => TRUE));
            $Dragclass = 'm6drive-folder-dragable';
            $Dropclass = 'm6drive-folder-droppable';
          }
          else {
            $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
            $fileName = l($filename, 'javascript:',  array('external' => TRUE));
          }
        }
        $rows[] = array(
          'data' => array(
            array('data'=>'<span class="folder-ids" style="display:none;">'.$fid.'-file</span>', 'class'=> array('m6drive-display-none-drag','hidden')),   
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attrfile.' ></div>', 'class'=> array('text-center','hidden')),
            array('data'=> $fileName, 'class' => array('text-left','m6drive-drag-content-show','drive-getting-folder')),
            array('data' => $companyusersfullname,'class' => array('text-left')),
            array('data' => date('F d, Y', strtotime($sharedData->shared_date)),'class' => array('text-left')),
            array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('text-left')),
          ),
          'class' => array('custom-odd', 'customsearchformydrive', $Dragclass,'m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
          );
      }
    }

    $return .= '<div class="grid-view" style="' . $grid_display . '">';
    $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
    $return .= '<div class="grid-view-folders row margin-5">';

    foreach ($divstrinner_arr as $key => $values) {
      if($values->Id) {
        $folders_present = TRUE;
      }
      if($values->file && $filevalue = file_load($values->file)){
        $files_present = TRUE;
      }
    }
    if(!$folders_present){
      $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
    }
    else {
      foreach($divstrinner_arr  as $values) {
        $companyusersdetail = _get_user_data_by_uid($values->user_uid);
        $companyusersfullname = $companyusersdetail['realname'];

        if (m6connect_m6drive_sharedbyfolderID($values->Id, $user->uid)) {
          $query = m6connect_m6drive_sharedbyfolderID($values->Id, $user->uid);
          if ($query->permissions) {
            $permissionsfol = $query->permissions;
          }
          elseif (m6connect_m6drive_sharedbyfolderID($folderid, $user->uid)) {
            $query = m6connect_m6drive_sharedbyfolderID($folderid, $user->uid);
            if ($query->permissions) {
              $permissionsfol = $query->permissions;
            }
            else {
              $permissionsfol =  getJustparent_folderID($folderid, $user->uid);
            }
          }
          else {
            $permissionsfol =  getJustparent_folderID($folderid, $user->uid);
          }
        }

        if ($values->foldername && _check_folder_eligibility_share($values->Id)) {
          if($permissionsfol == 'r-w-o'){
            $attr = 'data="'.ucwords(str_replace('_',' ',$values->foldername)).'" value="'.$values->Id.'-folder" name="m6drive-shared-folder-'.$values->Id.'" class="form-checkbox m6drive-folder-checkbox"';
            $Dragclass = 'm6drive-folder-dragable';
            $Dropclass = 'm6drive-folder-droppable';
          }
          elseif ($permissionsfol == 'r-o') {
            $attr = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
            $Dragclass = 'm6drive-folder-dragable';
            $Dropclass = 'm6drive-folder-droppable';
          }
          else {
            $attr = 'data-attr ="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
          }

          $buttonoutput =  '<div class="btn-group"><div class="dropdown">
            <button id="" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="">
            <li>'.l('Download','m6drive-download/folder/'.$values->Id.'/nojs', array('attributes'=> array('class'=>array('')))).'</li>
            </ul></div></div>';

          $foldericon = $Grid_folder_icon_image . ucwords(str_replace('_', ' ', $values->foldername)) . '';
          $return .= '<div id="'.$values->Id.'" class="'.$Dragclass.' '.$Dropclass.' grid-view-folder-item col-md-4 padding-5 margin-bottom-10">';
          $return .= '<div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">'.$values->Id.'-folder</span></div>';
          $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>';
          $return .= '<div class="grid-item-anchor clearfix m6drive-drag-content-show">';
          $return .=  l($foldericon, 'share-load-drivedata/'.$values->foldername.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html'=>TRUE));
          $return .= '</div>'; //end grid-item-anchor.
          $return .= '</div>'; //end grid-view-folder-item
        }
      }
    }
    $return .= '</div>'; //end grid-view-folders

    // Then handling only Files.
    $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
    $return .= '<div class="grid-view-files row margin-5">';
    if (!$files_present) {
      $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
    }
    else {
      foreach ($divstrinner_arr  as $values) {
        if ($values->file && _check_file_eligibility_share($values->file) && $filevalue = file_load($values->file)) {
          $fid =  $values->file;
          $buttonoutput =  '<div class="btn-group"><div class="dropdown">
            <button id="" class="btn btn-success" type="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Actions</button><ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="">
            <li>'.l('Download','m6drive-download/file/'.$fid.'/nojs', array('attributes'=> array('class'=>array('')))).'</li>
            </ul></div></div>';
          $uri = $filevalue->uri;
          $filename =  $filevalue->filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);

          $queryfidPar = db_select('m6connect_m6drive_shared', 'd')
            ->fields('d')
            ->condition('fid', $fid)
            ->condition('share_to_uid', $user->uid)
            ->execute()
            ->fetchAll();

          if ($queryfidPar[0]->permissions) {
              $permissionsfolf = $queryfidPar[0]->permissions; 
              if($permissionsfolf == 'r-w-o'){
                $attrfile = 'data="'.$filename.'" value="'.$fid.'-file" name="m6drive-shared-file-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"';
              } else if($permissionsfolf == 'r-o'){
                $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
                $fileName = l($filename, 'javascript:',  array('external' => TRUE));
              } else { 
                   $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
                   $fileName = l($filename, 'javascript:',  array('external' => TRUE));
              }
          }
          else {
              if($permissionsfol == 'r-w-o'){
                 $attrfile = 'data="'.$filename.'" value="'.$fid.'-file" name="m6drive-shared-file-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"';
              } else if($permissionsfol == 'r-o'){
                $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
                $fileName = l($filename, 'javascript:',  array('external' => TRUE));
                $Dragclass = 'm6drive-folder-dragable';
                $Dropclass = 'm6drive-folder-droppable';
              } else { 
                   $attrfile = 'data-attr="permission_denied" class="form-checkbox permission_deniedshare" disabled readonly';
                   $fileName = l($filename, 'javascript:',  array('external' => TRUE));
              }
          }
          $return .= '<div class="'.$Dragclass.' grid-view-folder-item col-md-2 padding-5 margin-bottom-10">';
          //$img_url = image_style_url('user_image_large', $uri);
          $filename =  $filevalue->filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);
          $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
          if($fileicondrive) {
             $img_url = $fileicondrive;
          }
          else {
            $img_url = image_style_url('user_image_large', $uri);
            $img_url = '<img src= '.$img_url.'>';
          }
          $img_src = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.$img_url.'<div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>';
          $return .= '<div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">'.$fid.'-file</span></div>';
          $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attrfile.' ></div>';
          $return .= $img_src;
          $return .= '</div>'; // end grid-view-file-item.
        }
      }
    }
   $return .= '</div>'; // end grid-view-files.
   $return .= '</div>'; // end grid-view for root.
  }
  else {
    /*========== For root folder shared drive on m6drive shared table==========*/
    $query = db_select('m6connect_m6drive_shared','srd');
    $query->fields('srd',array('id','folder_id','fid','share_by_uid','share_to_uid','shared_date', 'permissions'));
    $query->condition('srd.share_to_uid', $user->uid);
    $query->condition('srd.services', 'm6drive');
    $query->condition('srd.delete_status', 0, '=');
    $query->condition('srd.root', 1, '=');
    $query->orderBy('srd.shared_date', 'DESC');//ORDER BY created
    $record = $query->execute()->fetchAll();

    if($only_result === TRUE && !empty($complteresults)){
      $record = $complteresults;
    }

    // Creating table data.
    foreach ($record as $result) {
      $divstr_arr[] = $result;
  
      $companyusersdetail = _get_user_data_by_uid($result->share_by_uid);
      $companyusersfullname = $companyusersdetail['realname'];
      if (isset($result->folder_id) && empty($result->fid)) {
        $getfoldername = get_folder_name_by_folderid($result->folder_id);
        $foldericon   = $Drive_folder_icon_image .ucwords(str_replace('_',' ',$getfoldername->foldername)).'';
        $foldername =  l($foldericon, 'share-load-drivedata/'.$getfoldername->foldername.'/'.$result->folder_id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$result->folder_id),'html' =>TRUE));

        
        if($result->permissions == 'r-w-o'){
          $attr = 'data="'.ucwords(str_replace('_',' ',$getfoldername->foldername)).'" value="'.$result->folder_id.'-folder" name="m6drive-folder-'.$result->folder_id.'" class="form-checkbox m6drive-folder-checkbox"';
        } else if($result->permissions == 'r-o'){
          $attr = 'data-attr="permission_denied" class="form-checkbox" disabled readonly';
        } else { 
            $attr = 'data-attr="permission_denied" class="form-checkbox" disabled readonly';
        }
         $rows[] = array(
              'data' => array(
                array('data'=>'Drag Name', 'class'=> array('hidden')), 
                array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('text-center','hidden')),
                array('data'=> $foldername, 'class' => array('text-left','drive-getting-folder')),
                array('data' => $companyusersfullname,'class' => array('text-left')),
                array('data' => date('F d, Y', strtotime($result->shared_date)),'class' => array('text-left')),
                 array('data'=>'-','class'=>array('text-left')),
                //array('data' => m6drive_shared_content_btn('folder', $result->folder_id),'class' => array('col-md-2','text-left')),
              ),  
              'class' => array('custom-odd', 'customsearchformydrive','m6drive-folderdelete-'.$result->folder_id.'-'.$company->nid.'-row'),
        );
      }
    
      if (isset($result->fid) && empty($result->folder_id) && $filevalue = file_load($result->fid)) {
        $fid =  $result->fid;
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        
         if($result->permissions == 'r-w-o'){
          $attr = 'data="'.$filename.'" value="'.$fid.'-file" name="m6drive-folder-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"';
          $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$result->id))); 
          $filedatalink = $fileName;
        } else if($result->permissions == 'r-o'){
          $attr = 'data="permission_denied" class="form-checkbox  permission_deniedshare" disabled readonly ';

          $fileName = l($filename, 'javascript:',  array('external' => TRUE));
          $filedatalink = $fileName;

        } else { 
            $attr = 'data="permission_denied" class="form-checkbox  permission_deniedshare" disabled readonly';
            $fileName = l($filename, 'javascript:',  array('external' => TRUE));
            $filedatalink = $fileName;
        }

        $rows[] = array(
          'data' => array(
            array('data'=>'Drag Name', 'class'=> array('col-md-1','hidden')), 
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=> $filedatalink, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $companyusersfullname,'class' => array('col-md-3','text-left')),
            array('data' => date('F d, Y', strtotime($result->shared_date)),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('col-md-1','text-left')),
            //array('data' => m6drive_shared_content_btn('file', $fid),'class' => array('col-md-2','text-left')),
            
          ),  
          'class' => array('custom-odd','customsearchformydrive', 'm6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
        );
      }
    }
    
    // End table structure for root list
    /*========== For root folder shared drive on m6drive shared table==========*/
    $return .= '<div class="grid-view" style="' . $grid_display . '">';
    $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
    $return .= '<div class="grid-view-folders row margin-5">';
    // First handling only Folders.

    // start here for root grid view 
    foreach ($divstr_arr as $key => $value) {
      if ($value->folder_id) {
        $folders_present = TRUE;
      }
      if ($value->fid && $filevalue = file_load($value->fid)) {
        $files_present = TRUE;
      }
    }

    if (!$folders_present) {
      $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>';
    }
    else {
      foreach($divstr_arr  as $values) {
        $companyusersdetail = _get_user_data_by_uid($values->share_by_uid);
        $companyusersfullname = $companyusersdetail['realname'];
        if(isset($values->folder_id) && empty($values->fid)){
          $getfoldername = get_folder_name_by_folderid($values->folder_id);
          $foldericon   = $Grid_folder_icon_image .ucwords(str_replace('_',' ',$getfoldername->foldername)).'';
          $foldername =  l($foldericon, 'share-load-drivedata/'.$getfoldername->foldername.'/'.$values->folder_id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->folder_id),'html' =>TRUE));
          if($values->permissions == 'r-w-o'){
            $attr = 'data="'.ucwords(str_replace('_',' ',$getfoldername->foldername)).'" value="'.$values->folder_id.'-folder" name="m6drive-folder-'.$values->folder_id.'" class="form-checkbox m6drive-folder-checkbox"';
          } else if($values->permissions == 'r-o'){
            $attr = 'data-attr="permission_denied" class="form-checkbox" disabled readonly';
          } else { 
              $attr = 'data-attr="permission_denied" class="form-checkbox" disabled readonly';
          }

          $return .= '<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">';
          $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>';
          $return .= '<div class="grid-item-anchor clearfix">';
          $return .=  l($foldericon, 'share-load-drivedata/'.$getfoldername->foldername.'/'.$values->folder_id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->folder_id),'html' =>TRUE));
          $return .= '</div>'; //end grid-item-anchor.
          $return .= '</div>'; //end grid-view-folder-item
        }
      }
    }
    $return .= '</div>'; //end grid-view-folders

    // Then handling only Files.
    $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
    $return .= '<div class="grid-view-files row margin-5">';
    if(!$files_present){
        $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
    }
    else {
      foreach($divstr_arr  as $values) {
        if(isset($values->fid) && empty($values->folder_id) && $filevalue = file_load($values->fid)){
          $return .= '<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">';

          $fid =  $values->fid;
          $uri = $filevalue->uri;
          $filename =  $filevalue->filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);
          
           if($values->permissions == 'r-w-o'){
            $attr = 'data="'.$filename.'" value="'.$fid.'-file" name="m6drive-shared-file-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"';
            $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->id))); 
            $filedatalink = $fileName;
          } else if($values->permissions == 'r-o'){
            $attr = 'data="permission_denied" class="form-checkbox  permission_deniedshare" disabled readonly ';

            $fileName = l($filename, 'javascript:',  array('external' => TRUE));
            $filedatalink = $fileName;

          } else { 
              $attr = 'data="permission_denied" class="form-checkbox  permission_deniedshare" disabled readonly';
              $fileName = l($filename, 'javascript:',  array('external' => TRUE));
              $filedatalink = $fileName;
          }
          //$img_url = image_style_url('user_image_large', $uri);
          $filename =  $filevalue->filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);

          $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
          if($fileicondrive) {
             $img_url = $fileicondrive;
          }
          else {
            $img_url = image_style_url('user_image_large', $uri);
            $img_url = '<img src= '.$img_url.'>';
          }

          $img_src = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.$img_url.'<div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>';
          $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-folder-checkbox"></div>';
          $return .= $img_src;
          $return .= '</div>'; // end grid-view-file-item.
        }
      }
    }
    $return .= '</div>'; // end grid-view-files.
    $return .= '</div>'; // end grid-view for root.
  }
  // list view 
  $return .= '<div class="list-view" style="'. $list_display.'">';
  $return .= theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No Folders or File yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-folder-name','m6connect-custom-m6drive-shared-folder-dragtable','table-striped','table-hover','table-bordered','text-center'))));

  $return .= '</div>';
  return $return;
}

/**
 * Helper function to get drive download form.
 */
function m6drive_download_form($form, &$form_state) {
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-deleteids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="row margin-bottom-10"><div class="col-md-3 cross-icons"><i class="fa fa-download"></i></div><div class="col-md-9 remove-member" style="font-size:16px;">Download file now: <span class="multiple-show-folders-share"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_download_form_submit'),
    '#value' => 'Download',
    '#prefix' => '<div class="clearfix text-right m6drive-download-btn">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );
  return $form; 
}

/**
 * Submit handler for m6drive_download_form
 */
function m6drive_download_form_submit($form, &$form_state) {
  global $base_path,$base_url, $user;
  $uid = uniqid();
  $dir = 'sites/default/files/';
  $fids = array();
  $tsmp = time();
  $check = 0;

  $values = $form_state['values']; 
  $deleMultiple = $values['deleted_ids'];

  $filefolder =  explode( ',' ,$deleMultiple);
  // Start donload folder code

  if (!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0];
        $result =  m6drive_get_all_file_by_folderid($folderIdMul); 
        $folderName = get_folder_name_by_folderid($folderIdMul);
        $zipFilename = $folderName->foldername.'.zip';
        $zip = new ZipArchive();
        $zipname = $dir.$zipFilename; 
        $zip->open( $zipname,  ZIPARCHIVE::CREATE | ZIPARCHIVE::OVERWRITE );

        if (is_array( $result) && !empty($result)) {
          foreach ($result as $delta => $record) {
            if (isset($record->file)) {
              $fileObj = file_load($record->file);
              $fileName = $fileObj->filename;
              $objFile = file_copy($fileObj, $destination = 'temporary://'.$fileName.$uid.'.'.$fileName,  $replace = FILE_EXISTS_RENAME);
              $objFile->status=0;
              file_save($objFile);
              if ($objFile) {
                $path = drupal_realpath($objFile->uri);
                if (file_exists($path)) {
                  $zip->addFile($path, $fileObj->filename);
                  $check++; 
                }
              }
            }
          }
        }

        $zip->close();
        if (file_exists($zipname)) {
          $file = file_save_data(file_get_contents($zipname), 'public://'.$zipFilename,  $replace = FILE_EXISTS_REPLACE);
          $file->status=0;
          $file_Url = str_replace($base_url.$base_path,'',  file_create_url($file->uri));
          file_save($file);
        }
        else {
          $file = file_save_data(file_get_contents($zipname), 'public://'.$zipFilename,  $replace = FILE_EXISTS_REPLACE);
          $file_Url = str_replace($base_url.$base_path,'',  file_create_url($file->uri));
          file_save($file);
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        $result =  m6drive_get_all_file_by_folderid($folderIdMul); 
        $folderName = get_folder_name_by_folderid($folderIdMul);
        $zipFilename = $folderName->foldername.'.zip';
        $zip = new ZipArchive();
        $zipname = $dir.$zipFilename; 
        $zip->open( $zipname,  ZIPARCHIVE::CREATE | ZIPARCHIVE::OVERWRITE );

        if (is_array( $result) && !empty($result)) {
          foreach ($result as $delta => $record) {
            if (isset($record->file)) {
              $fileObj = file_load($record->file);
              $fileName = $fileObj->filename;
              $objFile = file_copy($fileObj, $destination = 'temporary://'.$fileName.$uid.'.'.$fileName,  $replace = FILE_EXISTS_RENAME);
              $objFile->status=0;
              file_save($objFile);
              if ($objFile) {
                $path = drupal_realpath($objFile->uri);
                if (file_exists($path)) {
                  $zip->addFile($path, $fileObj->filename);
                  $check++; 
                }
              }
            }
          }
        }
        $zip->close();
        if (file_exists($zipname)) {
          $file = file_save_data(file_get_contents($zipname), 'public://'.$zipFilename,  $replace = FILE_EXISTS_REPLACE);
          $file->status=0;
          $file_Url = str_replace($base_url.$base_path,'',  file_create_url($file->uri));
          file_save($file);
        }
        else {
          $file = file_save_data(file_get_contents($zipname), 'public://'.$zipFilename,  $replace = FILE_EXISTS_REPLACE);
          $file_Url = str_replace($base_url.$base_path,'',  file_create_url($file->uri));
          file_save($file);
        }
      }
    }
  }

  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();  
  }
}

/**
 * Function to get form for deleting shared folder.
 */
function m6drive_delete_shared_folder_form($form, &$form_state, $type, $deleteid) {
  $deleteid = (isset($form_state['delete_id']) && is_numeric($form_state['delete_id'])) ? $form_state['delete_id'] : $deleteid;
  $type = (isset($form_state['delete_type'])) ? $form_state['delete_type'] : $type;
  $form_state['delete_id']= $deleteid; 
  $form_state['delete_type'] = $type;

  $form['for_multiple'] = array(
    '#type' => 'hidden',
    '#value' => '1',
    '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-ids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="row margin-bottom-10"><div class="col-md-3 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-9 remove-member" style="font-size:16px;"> Are you sure you want to delete: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_delete_shared_folder_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );
  return $form; 
}

/**
 * Submit handler for m6drive_delete_shared_folder
 */
function m6drive_delete_shared_folder_submit($form, &$form_state) {
  global $user, $company;
  $deleteid = $form_state['delete_id'];
  $type = $form_state['delete_type'];
  $values = $form_state['values'];
  $deleMultiple = $values['deleted_ids'];
  $filefolder =  explode( ',' ,$deleMultiple);
  if(!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0];
        if(!empty($folderIdMul)){
          _delete_folder_file_from_share_project($folderIdMul);

          db_delete('m6connect_m6drive_shared')
            ->condition('folder_id', $folderIdMul)
            ->condition('share_to_uid', $user->uid)
            ->execute();
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        if(!empty($fileIdMul)){
          db_delete('m6connect_m6drive_shared')
            ->condition('fid', $fileIdMul)
            ->condition('share_to_uid', $user->uid)
            ->execute();
        }
      }
    }
  }
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/m6drive-share-withme');  
  }
}

/**
 * Function to get form for drive delete.
 */
function m6drive_delete_folder_form($form, &$form_state, $type, $deleteid) {
  $deleteid = (isset($form_state['delete_id']) && is_numeric($form_state['delete_id'])) ? $form_state['delete_id'] : $deleteid;
  $type = (isset($form_state['delete_type'])) ? $form_state['delete_type'] : $type;
  $form_state['delete_id']= $deleteid; 
  $form_state['delete_type'] = $type;

  if(!is_numeric($deleteid)) {
    $form['for_multiple'] = array(
      '#type' => 'hidden',
      '#value' => '1',
      '#attributes' => array('class' => array('for_multishare_test')),
    );
    $form['deleted_ids'] = array(
      '#type' => 'textarea',
      '#attributes'=> array('class'=> array('multiple-share-ids')),
      '#prefix' => '<div style="display:none;">',
      '#suffix' => '</div>'
    );
    
    $form['m6drive_action_title'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to delete:  '.$deleMultiple.'<span class="multiple-folders"></span> ?</div></div>',
    );
  }
  else {
    if ($type == 'folder' && is_numeric($deleteid)) {
      $Folder = get_folder_name_by_folderid($deleteid);
      $DeletedName = ucwords(str_replace('_',' ',$Folder->foldername)); 
    }
    else {
      $fileObj = file_load($deleteid);
      $DeletedName = $fileObj->filename;
    }
    $form['for_multiple'] = array(
      '#type' => 'hidden',
      '#value' => '0',
      '#attributes' => array('class' => array('for_multishare_test')),
    );
    $form['m6drive_action_title'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to delete <strong>'.$DeletedName.'</strong>?</div></div>',
    );
  }
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_delete_folder_form_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );
  return $form;
}

/**
 * Submit handler for m6drive_delete_folder_form
 */
function m6drive_delete_folder_form_submit($form, &$form_state) {
  global $user;
  global $company;
  $deleteid = $form_state['delete_id'];
  $type = $form_state['delete_type']; 
  $values = $form_state['values']; 
  $deleMultiple = $values['deleted_ids'];

  if (empty($deleMultiple)) {
    if ($type == 'folder' && is_numeric($deleteid)) {
      if (!empty($deleteid)) {
        $trash_status = db_update('m6connect_m6drive')
          ->fields(array(
            'trash_status' => 1,
          ))
          ->condition('Id', $deleteid,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();

        $update_attachment = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'trash_status' => 1,
          ))
          ->condition('folder_id',$deleteid,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();

        if($trash_status){
          $commands[] = ajax_command_remove('table.m6connect-custom-m6drive-folder-name tr.m6drive-folderdelete-'.$deleteid.'-'.$company->nid.'-row ');
        }
      }
    }

    if ($type == 'file' && is_numeric($deleteid)) {
      if (!empty($deleteid)) {
        $fid = $deleteid;
        $trash_status = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'trash_status' => 1,
          ))
          ->condition('file',  $fid)
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
      if ($trash_status) {
        $commands[] = ajax_command_remove('table.m6connect-custom-m6drive-folder-name tr.m6drive-folderdelete-'.$deleteid.'-'.$company->nid.'-row ');
      }
    }

    if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
      $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    }
  }
  else {
    $filefolder =  explode( ',' ,$deleMultiple);
    if(!empty($filefolder)) {
      foreach ($filefolder as $multKey => $multVal) {
        $getStatus = explode('-', $multVal);
        if ($getStatus[1] == 'folder') {
          $folderIdMul = $getStatus[0];
          // We need to check if the trash request is for a folder that has
          // been added to my drive by another user.
          // If so, then removing entry from the add to mydrive table.
          db_delete('m6connect_m6drive_addto_mydrive')
            ->condition('services', 'm6drive')
            ->condition('user_uid', $user->uid)
            ->condition('folder_id', $folderIdMul)
            ->execute();

          $trash_status = db_update('m6connect_m6drive')
            ->fields(array(
              'trash_status' => 1,
            ))
            ->condition('Id', $folderIdMul,'=')
            ->condition('user_uid', $user->uid)
            ->condition('company_nid', $company->nid)
            ->execute();

          $update_attachment = db_update('m6connect_m6drive_attachment')
            ->fields(array(
              'trash_status' => 1,
            ))
            ->condition('folder_id',$folderIdMul,'=')
            ->condition('user_uid', $user->uid)
            ->condition('company_nid', $company->nid)
            ->execute();
        }
        elseif($getStatus[1] == 'file') {
          $fileIdMul = $getStatus[0];
          // We need to check if the trash request is for a file that has
          // been added to my drive by another user.
          // If so, then removing entry from the add to mydrive table.
          db_delete('m6connect_m6drive_addto_mydrive')
            ->condition('services', 'm6drive')
            ->condition('user_uid', $user->uid)
            ->condition('file', $fileIdMul)
            ->execute();

          $trash_status = db_update('m6connect_m6drive_attachment')
            ->fields(array(
              'trash_status' => 1,
            ))
            ->condition('file',  $fileIdMul)
            ->condition('user_uid', $user->uid)
            ->condition('company_nid', $company->nid)
            ->execute();
        }
      }
    }

    if($deleteid == 0){
      $form_state['ajax_commands'][] = ajax_command_html("#m6-drive-datacontainer-main-cust", get_drive_listing_table_data(0,0));
    }
    else {
      $Currentfolder = get_folder_name_by_folderid($deleteid);
      $form_state['ajax_commands'][] = ajax_command_html("#m6-drive-datacontainer-main-cust", get_drive_listing_table_data($Currentfolder->foldername,  $deleteid));
    }

    if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
      $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    }
  }
}

/**
 * Get breadcrumb for trash drive.
 */
function m6drive_trash_breadcrumb_for_folder($folder, $folderid) {
  if ($folderid == 0) {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
      <li><a class="use-ajax" href="/trash-load-drive-data/0/0/nojs">My Trash</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
      </ul></div>';
  }
  else {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/trash-load-drive-data/0/0/nojs">My Trash</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    $new_outputs = m6drive_get_parent_folder($folderid);
    foreach ($new_outputs as $fldrId => $folderNameVal) {
      foreach ($folderNameVal as $foldKey => $fldVal) {
        $breadcrumbVal .= '<li><a class="use-ajax" href="/trash-load-drive-data/'.$fldVal.'/'.$foldKey.'/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
      }
    }
  $breadcrumbVal .= '<li><a class="use-ajax" href="/trash-load-drive-data/'.$folder.'/'.$folderid.'/nojs">'.ucwords(str_replace('_',' ',$folder)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
  $breadcrumbVal .= '</ul></div>';
 }
  return $breadcrumbVal;
}

/**
 * Function to get Trash drive listing.
 */
function m6drive_get_trash_drive_listing_table_data($folder = 0,$folderid = 0, $complteresults = array(), $only_result = FALSE) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  global $company, $user, $base_url;  
  $companyName =  str_replace(' ','_',$company->title);
  $userName = str_replace(' ','_', $user->name);  
  $rows = array();
  $complteresult = array();
  $header = array(
    array('data'=>'<input type="checkbox" name="select-m6drive-folder-checkbox" class="form-checkbox select-m6drive-folder-checkbox">', 'class'=> array('text-center','hidden','no-sort')),
    array('data'=>'Name &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('personal_trash_m6drive_filter_form',$folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Owner','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Last Modified','class'=>array('text-left','drive_filter_header')),
    array('data'=>'File Size','class'=>array('text-left')),
  );

  // Trash Status update
  $UserFnameLname =_get_user_data_by_uid($user->uid);

  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';
  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';

  if ($folderid != 0) {
    $updatestatus = m6drive_update_status_child_file_folder($folderid);
    foreach($updatestatus as $statusvalue) {
      db_update('m6connect_m6drive')
        ->fields(array(
          'trash_status' => 1,
        ))
        ->condition('Id', $statusvalue->Id,'=')
        ->condition('user_uid', $user->uid)
        ->condition('company_nid', $company->nid)
        ->execute();

      db_update('m6connect_m6drive_attachment')
        ->fields(array(
          'trash_status' => 1,
        ))
        ->condition('folder_id', $statusvalue->folder_id,'=')
        ->condition('user_uid', $user->uid)
        ->condition('company_nid', $company->nid)
        ->execute();
    }
  }

  if ($only_result === FALSE) {
    if (!empty($folderid) && is_numeric($folderid)) {
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','trash_status'));
      $query->condition('m6d.user_uid', $user->uid);
      $query->condition('m6d.company_nid', $company->nid);
      $query->condition('m6d.parent_id', $folderid);
      $query->condition('m6d.trash_status', 1,'=');
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
      $record = $query->execute()->fetchAll();
      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('file','created_date','trash_status'));
      $querysub->condition('att.user_uid', $user->uid);
      $querysub->condition('att.company_nid', $company->nid);
      $querysub->condition('att.folder_id', $folderid);
      $querysub->condition('att.trash_status', 1,'=');
      $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created
      $recordsub = $querysub->execute()->fetchAll();
      $complteresult = array_merge($record, $recordsub);
    }
    else {
      $query = db_select('m6connect_m6drive', 'm6d');    
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','trash_status'));
      $query->condition('m6d.user_uid', $user->uid);
      $query->condition('m6d.company_nid', $company->nid);
      $query->condition('m6d.services','m6drive','=');
      $query->condition('m6d.parent_id',0,'=');
      $query->condition('m6d.trash_status', 1,'=');
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
      $record = $query->execute()->fetchAll();
      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('file','created_date','trash_status'));
      $querysub->condition('att.user_uid', $user->uid);
      $querysub->condition('att.company_nid', $company->nid);
      $querysub->condition('att.folder_id', 0,'=');
      $querysub->condition('att.trash_status', 1,'=');
      $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created
      $recordsub = $querysub->execute()->fetchAll();
      $complteresult = array_merge($record, $recordsub);
    }
  }
  if($only_result === TRUE && !empty($complteresults)) {
    $complteresult = $complteresults;
  }

  $foldericon = '';

  // Creating div structure.
  $optionview = 'List';

  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }

  $return .= '<div class="grid-view" style="' . $grid_display . '">';
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
  $return .= '<div class="grid-view-folders row margin-5">';

  // First handling only Folders.
  $folders_present = FALSE;
  $files_present = FALSE;

  foreach ($complteresult as $key => $value) {
    if ($value->foldername) {
      $folders_present = TRUE;
    }
    if ($value->file && $filevalue = file_load($value->file)) {
      $files_present = TRUE;
    }
  }

  if (!$folders_present) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
  }
  else {
    foreach ($complteresult  as $values) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      if ($values->foldername) {
        $return .= '<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">';
        $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-folder-checkbox"></div>';
        $foldericon = $Grid_folder_icon_image .ucwords(str_replace('_',' ',$values->foldername)).'';
        $return .= '<div class="grid-item-anchor clearfix">';
        $return .= l($foldericon, 'trash-load-drive-data/'.$values->foldername.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none', 'margin-5'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));
        $return .= '</div>'; //end grid-item-anchor.
        $return .= '</div>'; //end grid-view-folder-item
      }
    }
  }

  $return .= '</div>'; //end grid-view-folders

  // Then handling only Files.
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
  $return .= '<div class="grid-view-files row margin-5">';

  if (!$files_present) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
  }
  else {
    foreach($complteresult  as $values) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      if ($values->file &&  $filevalue = file_load($values->file)) {
        $return .= '<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">';
        $fid =  $values->file;
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
        if($fileicondrive) {
          $img_url = $fileicondrive;
        }
        else {
          $img_url = image_style_url('user_image_large', $uri);
          $img_url = '<img src= '.$img_url.'>';
        }
        $img_src = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.$img_url.'<div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>';
        $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-folder-checkbox"></div>';
        $return .= $img_src;
        $return .= '</div>'; // end grid-view-file-item.
      }
    }
  }

  $return .= '</div>'; // end grid-view-files.
  $return .= '</div>'; // end grid-view.

  // Creating table data.
  foreach ($complteresult  as $values) {
    if ($values->foldername) {
      $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$values->foldername)).'';
      $foldername =  l($foldericon, 'trash-load-drive-data/'.$values->foldername.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));
      $rows[] = array(
        'data' => array(
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" value="'.$values->Id.'-folder" name="m6drive-folder-'.$values->Id.'" class="form-checkbox m6drive-folder-checkbox"></div>', 'class'=> array('text-center','hidden')),
          array('data'=> $foldername, 'class' => array('text-left','drive-getting-folder')),
          array('data' =>  $UserFnameLname['realname'],'class' => array('text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('text-left')),
          array('data'=>'-','class'=>array('text-left')),
        ),
        'class' => array('custom-odd','customsearchformydrive','m6drive-trash-folder-'.$values->Id.'-'.$company->nid.'-row'),
      );
    }
    if ($values->file  && $filevalue = file_load($values->file)) {
      $fid =  $values->file;
      $uri = $filevalue->uri;
      $filename =  $filevalue->filename;
      $filetype = $filevalue->type;
      $filepath = file_create_url($uri);  
      $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id))); 
      $rows[] = array(
        'data' => array(
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" value="'.$fid.'-file" name="m6drive-folder-'.$fid.'" class="form-checkbox m6drive-folder-checkbox"></div>', 'class'=> array('text-center','hidden')),
          array('data'=>  $Attachment, 'class' => array('text-left','drive-getting-folder')),
          array('data' => $UserFnameLname['realname'],'class' => array('text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('text-left')),
          array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('text-left')),
        ),
        'class' => array('custom-odd','customsearchformydrive','m6drive-trash-folder-'.$fid.'-'.$company->nid.'-row'),
      );
    }
  }

  $return .= '<div class="list-view" style="' . $list_display . '">'; 
  $return .= theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-folder-name','table-striped','table-hover','table-bordered','text-center'))));
  $return .= '</div>';
  return $return;
}

/**
 * Function to get form for remove from drive permanently.
 */
function m6drive_remove_drive_permanent_form($form, &$form_state, $type, $deleteid) {
  $deleteid = (isset($form_state['delete_id']) && is_numeric($form_state['delete_id'])) ? $form_state['delete_id'] : $deleteid;
  $type = (isset($form_state['delete_type'])) ? $form_state['delete_type'] : $type;
  $form_state['delete_id']= $deleteid; 
  $form_state['delete_type'] = $type;

  $form['for_multiple'] = array(
    '#type' => 'hidden',
    '#value' => '1',
    '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-ids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="row margin-bottom-10"><div class="col-md-3 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-9 remove-member" style="font-size:16px;"> Are you sure you want to delete permanent: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_remove_drive_permanent_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );

  return $form;
}

/**
 * Submit handler for m6drive_remove_drive_permanent
 */
function m6drive_remove_drive_permanent_submit($form, &$form_state) {
  global $user, $company;

  $values = $form_state['values']; 
  $deleMultiple = $values['deleted_ids'];
  $filefolder =  explode( ',' ,$deleMultiple);

  if (!class_exists('S3')) include_once DRUPAL_ROOT . '/sites/all/libraries/awssdk1/S3.php';
  if (!defined('awsAccessKey')) define('awsAccessKey', 'AKIAJZCVB5B62KPYTLFA');
  if (!defined('awsSecretKey')) define('awsSecretKey', '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');
  $s3 = new S3(awsAccessKey, awsSecretKey);

  if (!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folderMul = $getStatus[0];
        _delete_folder_and_file($folderMul);
        
        // Delete Folder also in share drive table
        db_delete('m6connect_m6drive_shared')->condition('folder_id', $folderMul)->condition('share_by_uid', $user->uid)->execute();
        
        // Praent folder delete 
        $Praent_folder_delete = db_delete('m6connect_m6drive')->condition('Id', $folderMul)->condition('user_uid', $user->uid)->condition('company_nid', $company->nid)->execute();

        if (!empty($folder)) {
          $s3->deleteObject($bucket, $folder, S3::ACL_PRIVATE);
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        if (!empty($fileIdMul)) {
          $fileObj = file_load($fileIdMul);
          file_delete($fileObj);

          $attachment_delete = db_delete('m6connect_m6drive_attachment')->condition('file', $fileIdMul)->condition('user_uid', $user->uid)->condition('company_nid', $company->nid)->execute();

          // Delete File also in share drive table
          db_delete('m6connect_m6drive_shared')->condition('fid', $fileIdMul)->condition('share_by_uid', $user->uid)->execute();
        }
      }
    }
  }

  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/m6drive-trash-folder');  
  }
}

/**
 * Helper function to get breadcrumb for archive drive.
 */
function m6drive_archive_breadcrumb_for_folder($folder, $folderid) {
  if($folderid == 0){  
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
      <li><a class="use-ajax" href="/archive-load-drive-data/0/0/nojs">My Archive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
      </ul></div>';
  }
  else {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/archive-load-drive-data/0/0/nojs">My Archive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    $new_outputs = m6drive_get_parent_folder($folderid);
    foreach ($new_outputs as $fldrId => $folderNameVal) {
      foreach ($folderNameVal as $foldKey => $fldVal) {
        $breadcrumbVal .= '<li><a class="use-ajax" href="/archive-load-drive-data/'.$fldVal.'/'.$foldKey.'/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
      }
    }
    $breadcrumbVal .= '<li><a class="use-ajax" href="/archive-load-drive-data/'.$folder.'/'.$folderid.'/nojs">'.ucwords(str_replace('_',' ',$folder)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    $breadcrumbVal .= '</ul></div>';
  }
  return $breadcrumbVal;
}

/**
 * Function to get archive drive listing.
 */
function m6drive_get_archive_drive_listing_table_data($folder = 0,$folderid = 0, $complteresults = array(), $only_result = FALSE) {
  global $company, $user, $base_url;  
  $companyName =  str_replace(' ','_',$company->title);
  $userName = str_replace(' ','_', $user->name);  
  $rows = array();
  $complteresult = array();
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  $header = array(
    array('data'=>'<input type="checkbox" name="select-m6drive-folder-checkbox" class="form-checkbox select-m6drive-folder-checkbox">', 'class'=> array('text-center','hidden','no-sort')),
    array('data'=>'Name  &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i><div class="m6drive_filter_sort_form m6drive_filter_sort " style="display:none;">'.render(drupal_get_form('personal_archive_m6drive_filter_form',$folder, $folderid)).'</div>','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Owner','class'=>array('text-left','drive_filter_header')),
    array('data'=>'Last Modified','class'=>array('text-left','drive_filter_header')),
    array('data'=>'File Size','class'=>array('text-left','drive_filter_header')),
  );

  // Archive Status update
  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';
  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';

  $UserFnameLname =_get_user_data_by_uid($user->uid);

  if ($folderid != 0) {
    $updatestatus = m6drive_update_status_child_file_folder($folderid);
    foreach($updatestatus as $statusvalue) {
        db_update('m6connect_m6drive')
          ->fields(array(
            'archive_status' => 1,
          ))
          ->condition('Id', $statusvalue->Id,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();

        db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'archive_status' => 1,
          ))
          ->condition('folder_id', $statusvalue->folder_id,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
  }

  if ($only_result === FALSE) {
    if (!empty($folderid) && is_numeric($folderid)) {
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','archive_status'));
      $query->condition('m6d.user_uid', $user->uid);
      $query->condition('m6d.company_nid', $company->nid);
      $query->condition('m6d.parent_id', $folderid);
      $query->condition('m6d.trash_status', 0,'=');
      $query->condition('m6d.archive_status', 1,'=');
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
      $record = $query->execute()->fetchAll();
      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('file','created_date','archive_status'));
      $querysub->condition('att.user_uid', $user->uid);
      $querysub->condition('att.company_nid', $company->nid);
      $querysub->condition('att.folder_id', $folderid);
      $querysub->condition('att.trash_status', 0,'=');
      $querysub->condition('att.archive_status', 1,'=');
      $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created
      $recordsub = $querysub->execute()->fetchAll();
      $complteresult = array_merge($record, $recordsub);
    }
    else {
      $query = db_select('m6connect_m6drive', 'm6d');    
      $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date','archive_status'));
      $query->condition('m6d.user_uid', $user->uid);
      $query->condition('m6d.company_nid', $company->nid);
      $query->condition('m6d.services','m6drive','=');
      //$query->condition('m6d.parent_id',0,'=');
      $query->condition('m6d.trash_status', 0,'=');
      $query->condition('m6d.archive_status', 1,'=');
      $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
      $record = $query->execute()->fetchAll();
      $querysub = db_select('m6connect_m6drive_attachment','att');    
      $querysub->fields('att',array('file','created_date','archive_status'));
      $querysub->condition('att.user_uid', $user->uid);
      $querysub->condition('att.company_nid', $company->nid);
      //$querysub->condition('att.folder_id', 0,'=');
      $querysub->condition('att.trash_status', 0,'=');
      $querysub->condition('att.archive_status', 1,'=');
      $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created
      $recordsub = $querysub->execute()->fetchAll();
      $complteresult = array_merge($record, $recordsub);
    }
  }
  if ($only_result === TRUE && !empty($complteresults)) {
    $complteresult = $complteresults;
  }
  $foldericon = '';
  // Creating div structure.
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }

  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }

  $return .= '<div class="grid-view" style="' . $grid_display . '">';
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
  $return .= '<div class="grid-view-folders row margin-5">';

  // First handling only Folders.
  $folders_present = FALSE;
  $files_present = FALSE;
  foreach ($complteresult as $key => $value) {
    if ($value->foldername) {
      $folders_present = TRUE;
    }
    if ($value->file && $filevalue = file_load($value->file)) {
      $files_present = TRUE;
    }
  }
  if (!$folders_present) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
  }
  else {
    foreach ($complteresult  as $values) {
      $UserFnameLname = _get_user_data_by_uid($values->user_uid);
      if ($values->foldername) {
        $return .= '<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">';
        $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-folder-checkbox"></div>';
        $foldericon =  $Grid_folder_icon_image .ucwords(str_replace('_',' ',$values->foldername)).'';
        $return .= '<div class="grid-item-anchor clearfix">';
        $return .= l($foldericon, 'archive-load-drive-data/'.$values->foldername.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none', 'margin-5'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));
        $return .= '</div>'; //end grid-item-anchor.
        $return .= '</div>'; //end grid-view-folder-item
      }
    }
  }
  $return .= '</div>'; //end grid-view-folders

  // Then handling only Files.
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
  $return .= '<div class="grid-view-files row margin-5">';
  if (!$files_present) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
  }
  else {
    foreach ($complteresult  as $values) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      if ($values->file &&  $filevalue = file_load($values->file)) {
        $return .= '<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">';
        $fid =  $values->file;
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);

        if ($fileicondrive) {
          $img_url = $fileicondrive;
        }
        else {
          $img_url = image_style_url('user_image_large', $uri);
          $img_url = '<img src= '.$img_url.'>';
        }
        $img_src = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.$img_url.'<div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>';
        $return .= '<div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-folder-checkbox"></div>';
        $return .= $img_src;
        $return .= '</div>'; // end grid-view-file-item.
      }
    }
  }

  $return .= '</div>'; // end grid-view-files.
  $return .= '</div>'; // end grid-view.

  // Creating table data.
  foreach ($complteresult  as $values) {
    if ($values->foldername) {
      $foldericon   = $Drive_folder_icon_image .ucwords(str_replace('_',' ',$values->foldername)).'';
      $foldername =  l($foldericon, 'archive-load-drive-data/'.$values->foldername.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));
      $rows[] = array(
        'data' => array(
           array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-folder-checkbox"></div>', 'class'=> array('text-center','hidden')),
          array('data'=> $foldername, 'class' => array('text-left','drive-getting-folder')),
          array('data' => $UserFnameLname['realname'],'class' => array('text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('text-left')),
          array('data'=>'-','class'=>array('text-left')),
        ),
        'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$values->Id.'-'.$company->nid.'-row'),
      );
    }
    if ($values->file && $filevalue = file_load($values->file)) {
      $fid =  $values->file;
      $uri = $filevalue->uri;
      $filename =  $filevalue->filename;
      $filetype = $filevalue->type;
      $filepath = file_create_url($uri);  
      $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id))); 
      $rows[] = array(
        'data' => array(
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-folder-checkbox"></div>', 'class'=> array('text-center','hidden')),
          array('data'=>  $Attachment, 'class' => array('text-left','drive-getting-folder')),
          array('data' => $UserFnameLname['realname'],'class' => array('text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('text-left')),
          array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('text-left')),
        ),
        'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
      );
    }
  }

  $return .= '<div class="list-view" style="' . $list_display . '">';  
  $return .=theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-folder-name','table-striped','table-hover','table-bordered','text-center'))));
  $return .= '</div>';
  return $return;
}

/**
 * Function to get m6drive archive form.
 */
function m6drive_archive_folder_form($form, &$form_state, $type, $deleteid) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  $archiveid = (isset($form_state['archive_id']) && is_numeric($form_state['archive_id'])) ? $form_state['archive_id'] : $archiveid;
  $type = (isset($form_state['archive_type'])) ? $form_state['archive_type'] : $type;
  $form_state['archive_id'] = $archiveid; 
  $form_state['archive_type'] = $type;

  $form['for_multiple'] = array(
    '#type' => 'hidden',
    '#value' => '1',
    '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-ids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to archive: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_archive_folder_form_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );

  return $form;
}

/**
 * Submit handler for m6drive_archive_folder_form
 */
function m6drive_archive_folder_form_submit($form, &$form_state){
  global $user, $company;
  $archiveid = $form_state['archive_id'];
  $type = $form_state['archive_type']; 
  $values = $form_state['values']; 
  $archiveMultiple = $values['deleted_ids'];
  $filefolder =  explode( ',' ,$archiveMultiple);

  if(!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0]; 

        // We need to check if the trash request is for a folder that has
        // been added to my drive by another user.
        // If so, then removing entry from the add to mydrive table.
        db_delete('m6connect_m6drive_addto_mydrive')
          ->condition('services', 'm6drive')
          ->condition('user_uid', $user->uid)
          ->condition('folder_id', $folderIdMul)
          ->execute();

        $archive_status = db_update('m6connect_m6drive')
          ->fields(array(
            'archive_status' => 1,
          ))
          ->condition('Id', $folderIdMul,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();

        $archive_attachment = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'archive_status' => 1,
          ))
          ->condition('folder_id', $folderIdMul,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];

        // We need to check if the trash request is for a file that has
        // been added to my drive by another user.
        // If so, then removing entry from the add to mydrive table.
        db_delete('m6connect_m6drive_addto_mydrive')
          ->condition('services', 'm6drive')
          ->condition('user_uid', $user->uid)
          ->condition('file', $fileIdMul)
          ->execute();

        $archive_files = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'archive_status' => 1,
          ))
          ->condition('file',  $fileIdMul)
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
    }
  }

  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/program/m6-drive');  
  }
}

/**
 * Function to get drive restore form.
 */
function m6drive_restore_form($form, &$form_state, $type, $deleteid) {
  $deleteid = (isset($form_state['delete_id']) && is_numeric($form_state['delete_id'])) ? $form_state['delete_id'] : $deleteid;
  $type = (isset($form_state['delete_type'])) ? $form_state['delete_type'] : $type;
  $form_state['delete_id']= $deleteid; 
  $form_state['delete_type'] = $type;

  $form['for_multiple'] = array(
    '#type' => 'hidden',
    '#value' => '1',
    '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-ids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="row margin-bottom-10"><div class="col-md-3 cross-icons"><i class="fa fa-recycle"></i></div><div class="col-md-9 remove-member" style="font-size:16px;"> Are you sure you want to restore: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_restore_form_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton . '</div></div></div>', 
  );

  return $form;
}

/**
 * Submit handler for m6drive_restore_form
 */
function m6drive_restore_form_submit($form, &$form_state) {
  global $user, $company;
  $values = $form_state['values']; 
  $deleMultiple = $values['deleted_ids'];
  $filefolder =  explode( ',' ,$deleMultiple);

  if(!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0];
        if (!empty($folderIdMul)) {
          db_update('m6connect_m6drive')
            ->fields(array(
              'trash_status' => 0,
            ))
            ->condition('Id', $folderIdMul,'=')
            ->condition('user_uid', $user->uid)
            ->condition('company_nid', $company->nid)
            ->execute();

          db_update('m6connect_m6drive_attachment')
            ->fields(array(
              'trash_status' => 0,
            ))
            ->condition('folder_id', $folderIdMul,'=')
            ->condition('user_uid', $user->uid)
            ->condition('company_nid', $company->nid)
            ->execute();
          $updatestatus = m6drive_update_status_child_file_folder($folderIdMul);

          foreach($updatestatus as $statusvalue) {
            db_update('m6connect_m6drive')
              ->fields(array(
                'trash_status' => 0,
              ))
              ->condition('Id', $statusvalue->Id,'=')
              ->condition('user_uid', $user->uid)
              ->condition('company_nid', $company->nid)
              ->execute();

            db_update('m6connect_m6drive_attachment')
              ->fields(array(
                'trash_status' => 0,
              ))
              ->condition('folder_id', $statusvalue->folder_id,'=')
              ->condition('user_uid', $user->uid)
              ->condition('company_nid', $company->nid)
              ->execute();
          }
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];

        $fid = $fileIdMul;
        $trash_status = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'trash_status' => 0,
          ))
          ->condition('file',  $fid)
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
    }
  }

  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/m6drive-trash-folder');  
  }
}

/**
 * Function to get drive unarchive folder form.
 */
function m6drive_unarchive_folder_form($form, &$form_state, $type, $archiveid) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  $archiveid = (isset($form_state['archive_id']) && is_numeric($form_state['archive_id'])) ? $form_state['archive_id'] : $archiveid;
  $type = (isset($form_state['archive_type'])) ? $form_state['archive_type'] : $type;
  $form_state['archive_id'] = $archiveid; 
  $form_state['archive_type'] = $type;

  $form['for_multiple'] = array(
    '#type' => 'hidden',
    '#value' => '1',
    '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-ids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-archive"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to unarchive: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_unarchive_folder_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );
  return $form;
}

/**
 * Submit handler for m6drive_unarchive_folder_form
 */
function m6drive_unarchive_folder_submit($form, &$form_state) {
  global $user;
  global $company;
  $archiveid = $form_state['archive_id'];
  $type = $form_state['archive_type']; 
  $values = $form_state['values']; 
  $archiveMultiple = $values['deleted_ids'];
  $filefolder =  explode( ',' ,$archiveMultiple);

  if(!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0]; 
        $archive_status = db_update('m6connect_m6drive')
          ->fields(array(
            'archive_status' => 0,
          ))
          ->condition('Id', $folderIdMul,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();

        $archive_attachment = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'archive_status' => 0,
          ))
          ->condition('folder_id', $folderIdMul,'=')
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        $archive_files = db_update('m6connect_m6drive_attachment')
          ->fields(array(
            'archive_status' => 0,
          ))
          ->condition('file',  $fileIdMul)
          ->condition('user_uid', $user->uid)
          ->condition('company_nid', $company->nid)
          ->execute();
      }
    }
  }

  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/m6drive-archive');  
  }
}

/**
 * Function to get breadcrumb for Project Drive.
 */
function project_drive_breadcrumb($projectnid, $folder_id) {
  global $user, $company;

  if (empty($projectnid) && empty($folder_id)) {
   $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
      <li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
      </ul></div>';
  }
  elseif (empty($projectnid)) {
    $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';

    $query = db_select('m6connect_m6drive', 'm6d');
    $query->fields('m6d',array('foldername'));
    $query->condition('m6d.Id', $folder_id);
    $query->condition('m6d.services', 'm6drive_project');
    $Currentfolder = $query->execute()->fetchField();

    $output = m6drive_get_parent_folder($folder_id);
    foreach($output as $fldrId => $folderNameVal) {
      foreach($folderNameVal as $foldKey => $fldVal) {
        $get_key = $foldKey;
        if (is_array($fldVal)) {
          $foldKey = 0;
          $fldVal = $fldVal[0];
        }
        if (_check_folder_eligibility_add_to_mydrive($get_key)) {
          $breadcrumbVal .= '<li class="project-drive-folder-droppable" id="'.$foldKey.'-folderid" data="'.$projectnid.'projectnid"><a class="use-ajax" href="/project-load-drive/' . $projectnid. '/' . $foldKey . '/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
        }
      }
    }
    $breadcrumbVal .= '<li class="project-drive-folder-droppable" id="'.$folder_id.'-folderid" data="'.$projectnid.'-projectnid"><a class="use-ajax" href="/project-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'. ucwords(str_replace('_',' ',$Currentfolder)) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
  }
  elseif (is_string($projectnid) && !empty($projectnid) && !is_numeric($projectnid)) {
    $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    if ($projectnid == 'project') {
      $breadcrumbVal .= '<li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/project/0/nojs">M6 Project Postings</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    }
    if ($projectnid == 'rfp') {
      $breadcrumbVal .= '<li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/rfp/0/nojs">M6 RFP\'s</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    }

    // Users can upload custom folders in Project or RFP folders.
    // Getting here.
    if (!empty($folder_id)) {
      $output = m6drive_get_parent_folder($folder_id);
      foreach($output as $fldrId => $folderNameVal) {
        foreach($folderNameVal as $foldKey => $fldVal) {
          $get_key = $foldKey;
          if (is_array($fldVal)) {
            $foldKey = 0;
            $fldVal = $fldVal[0];
          }
          if (_check_folder_eligibility_add_to_mydrive($get_key)) {
            $breadcrumbVal .= '<li class="project-drive-folder-droppable" id="'.$foldKey.'-folderid" data="'.$projectnid.'-projectnid"><a class="use-ajax" href="/project-load-drive/' . $projectnid. '/' . $foldKey . '/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
          }
        }
      }
      
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->fields('m6d',array('foldername'));
      $query->condition('m6d.Id', $folder_id);
      $query->condition('m6d.services', 'm6drive_project');
      $Currentfolder = $query->execute()->fetchField();
      if (!empty($Currentfolder)) {
        $breadcrumbVal .= '<li><a class="use-ajax" href="/project-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'. str_replace('_',' ',$Currentfolder) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
      }
    }
  }
  else {
    $node = node_load($projectnid);
    $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';

    // Add project/rfp here. One case, if rfp is in project, then deal accordingly.
    $folders_nodes = _get_rfp_project_folders($node);
    if (!empty($folders_nodes)) {
      if ($user->uid != $node->uid) {
        foreach ($folders_nodes as $folder) {
          if ($folder != 'project' && $folder != 'rfp') {
            if (_get_share_date_projectnid_using_rfp_nid($projectnid) && $folder_node = node_load($folder)) {
              $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" id="'.$folder_id.'-folderid" data="'.$folder_node->nid.'-projectnid"><a class="use-ajax" href="/project-load-drive/' . $folder_node->nid . '/' . $folder_id . '/nojs">'.$folder_node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
            }
          }
        }
      }
      else {
        foreach ($folders_nodes as $folder) {
          if ($folder == 'project') {
            $breadcrumbVal .= '<li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/project/0/nojs">M6 Project Postings</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
          }
          elseif ($folder == 'rfp') {
            $breadcrumbVal .= '<li id="0-folderid" data="0-projectnid"><a class="use-ajax" href="/project-load-drive/rfp/0/nojs">M6 RFP\'s</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
          }
          else {
            $folder_node = node_load($folder);
            $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" id="'.$folder_id.'-folderid" data="'.$folder_node->nid.'-projectnid"><a class="use-ajax" href="/project-load-drive/' . $folder_node->nid . '/' . $folder_id . '/nojs">'.$folder_node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
          }
        }
      }
    }
    if (empty($folder_id)) {
      $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" id="'.$folder_id.'-folderid" data="'.$projectnid.'-projectnid"><a class="use-ajax" href="/project-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'.$node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    }
    else {
      $query = db_select('m6connect_m6drive', 'm6d');
      $query->fields('m6d',array('foldername'));
      // $query->condition('m6d.user_uid', $user->uid);
      // $query->condition('m6d.company_nid', $company->nid); 
      $query->condition('m6d.Id', $folder_id);
      $query->condition('m6d.services', 'm6drive_project');
      $Currentfolder = $query->execute()->fetchField();

      $output = m6drive_get_parent_folder($folder_id);
      foreach($output as $fldrId => $folderNameVal) {
        foreach($folderNameVal as $foldKey => $fldVal) {
          $get_key = $foldKey;
          if (is_array($fldVal)) {
            $foldKey = 0;
            $fldVal = $fldVal[0];
          }
          if (_check_folder_eligibility_add_to_mydrive($get_key)) {
            $breadcrumbVal .= '<li class="project-drive-folder-droppable" id="'.$foldKey.'-folderid" data="'.$projectnid.'-projectnid"><a class="use-ajax" href="/project-load-drive/' . $projectnid. '/' . $foldKey . '/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
          }
        }
      }
      $breadcrumbVal .= '<li><a class="use-ajax" href="/project-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'. str_replace('_',' ',$Currentfolder) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    }
   
    $breadcrumbVal .= '</ul></div>';
  }
  return $breadcrumbVal;
}



/******************** End Personal Drive *************************/


/******************** Start Project/Company Drive *************************/


/**
 * Helper function to get project drive listing.
 */
function m6drive_project_drive_listing_table_data($projectnid = 0, $folder_id = 0) {

  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js'); 
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');
  /*drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery-ias.min.js');
  drupal_add_library('system', 'ui.draggable');
  drupal_add_library('system', 'ui.droppable');
  module_load_include($type = 'inc', $module = 'bookmarkorganizer', $name = 'bookmarkorganizer');*/

  global $company, $user, $base_url;

  $header = array(
    array('data'=>'Drag Name','class'=>array('col-md-1','text-left','hidden','no-sort')),
    array('data'=>'Company Drag Name','class'=>array('col-md-1','text-left','hidden','no-sort')),
    array('data'=>'<input type="checkbox" name="select-m6drive-project-checkbox" class="form-checkbox select-m6drive-project-checkbox">', 'class'=> array('col-md-1','text-center','hidden','no-sort')),
    array('data'=>'Name  &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort " style="display:none;">'.render(drupal_get_form('company_project_m6drive_filter_form',$projectnid, $folder_id)).'</div>','class'=>array('col-md-4','text-left','drive_filter_header')),
    array('data'=>'Owner','class'=>array('col-md-2','text-left')),
    array('data'=>'Last Modified','class'=>array('col-md-2','text-left')),
    array('data'=>'File Size','class'=>array('col-md-1','text-left')),
    array('data'=>'Share with','class'=>array('col-md-2','text-left','no-sort')),
  );

  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';

  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';

  $check_for_add_to_my_drive = FALSE;
  if (empty($projectnid) && empty($folder_id)) {
    $check_for_add_to_my_drive = TRUE;
  }

  // Getting the data from the m6drive custom tables, to show in tables.
  // Creating div structure.
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }
  $divstr_arrfol = array();

  if (empty($folder_id)) {
    if (!empty($projectnid) && is_string($projectnid) && !is_numeric($projectnid)) {
      // Browsing either project documents or RFP folder.

      if ($projectnid == 'project') {
        // query get project
        $CuurCompNid = $company->nid;
        $companyAdminRoleUsers = _get_company_users_by_og_roles($CuurCompNid,'company admin');
        $isCompanyIndividual = is_company_individual_flag($CuurCompNid);
        $userid = $user->uid;

        $type = array('project'); 
        $or = db_or();
        $and = db_and();
        $query = db_select('node', 'n')->extend('PagerDefault');
        $query->fields('n', array('nid'));
        $query->leftJoin('og_membership', 'ogm', 'ogm.etid=n.nid');

        if (in_array($user->uid, $companyAdminRoleUsers)) {
          $company_emails_users = db_select('m6connect_og_membership_email', 'om')->fields('om', array('user_uid','company_email'))->condition('om.entity_id', $CuurCompNid, '=')->execute()->fetchAllKeyed(0,1);
          $company_email = array_map('strtolower',array_values($company_emails_users));
          $company_user = array_keys($company_emails_users);
          
          $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
          $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
          $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
          //Invited Company Access
          $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
          $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
          $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
          
          $query->where('((n.uid IN(:UserUid) and ogm.gid=:ogmid) or (n.status=1 AND (rcne.field_rfp_company_nid_email_value IS NOT NULL) AND
          ((rcne.field_rfp_company_nid_email_value=:companyNid) or(LOWER(rcne.field_rfp_company_nid_email_value) IN(:companyMail)))))', 
          array(':UserUid' => $company_user, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
        }
        else {
          $company_email = db_select('m6connect_og_membership_email', 'om')->fields('om', array('company_email'))->condition('om.entity_id', $company->nid, '=')->condition('om.user_uid', $userid, '=')->execute()->fetchColumn(0);
          $company_email = (!empty($company_email)) ? $company_email : '';
          $company_email = strtolower($company_email);
          //$company_users = _get_current_company_users($user->uid);
          $company_users = _get_company_users_by_group_company($company);
          $userCmpNid = _get_user_company_nid();
          $query->leftJoin('field_data_field_project_invite_comapnies', 'pic', 'pic.entity_id=n.nid');
          $query->leftJoin('field_data_field_company_nid_mail', 'pcne', 'pcne.entity_id = pic.field_project_invite_comapnies_value');
          $query->leftJoin('field_data_field_comapny_manager', 'pcimu', 'pcimu.entity_id = pic.field_project_invite_comapnies_value');
          //Invited Company Access
          $query->leftJoin('field_data_field_rfp_invite_comapnies', 'ric', 'ric.entity_id=n.nid');
          $query->leftJoin('field_data_field_rfp_company_nid_email', 'rcne', 'ric.field_rfp_invite_comapnies_value = rcne.entity_id');
          $query->leftJoin('field_data_field_co_invite_manager_uid', 'rcimu', 'ric.field_rfp_invite_comapnies_value = rcimu.entity_id');
          $query->where('((n.uid=:UserUid AND ogm.gid=:ogmid) OR (n.status=1 AND ((pcne.field_company_nid_mail_value=:companyNid OR pcne.field_company_nid_mail_value=:companyMail) AND 
           ((pcimu.field_comapny_manager_value IS NULL) OR FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0))  OR              
          ((rcne.field_rfp_company_nid_email_value=:companyNid) AND FIND_IN_SET(:UserUid,rcimu.field_co_invite_manager_uid_value)>0) OR
          ((rcne.field_rfp_company_nid_email_value IS NOT NULL) AND LOWER(rcne.field_rfp_company_nid_email_value)=:companyMail) OR
          ((pcne.field_company_nid_mail_value=:companyNid) AND FIND_IN_SET(:UserUid,pcimu.field_comapny_manager_value)>0)))', array(':UserUid' => $userid, ':ogmid' => $CuurCompNid, ':companyNid' => $CuurCompNid, ':companyMail' => $company_email));
        }

        $query->condition('n.status', 1, '=');
        $query->condition('n.type', $type, 'IN');
        $query->orderBy('n.created', 'DESC'); 
        $query->groupBy('n.nid');
        $query->limit(15);
        $myproject = $query->execute()->fetchAll();

        if (!empty($company->nid)) {
          $collaborationproject = get_collaboration_project_for_project_m6drive($user->uid, $company->nid);
          $result = array_merge($myproject, $collaborationproject);
        }
        // End project query here
        
        foreach($result as $record) {
          $node = node_load($record->nid);
          $ChkNidInArchive = _get_all_projectnid_in_archive_drive($user->uid, $node->nid);
          if ($ChkNidInArchive != $node->nid) {
            $comprealusername = '';
             $nodeTitletrim = '';
            //$comprealusername = _get_node_company_user_name($node->nid);
             $comprealusername =_get_user_data_by_uid($node->uid);
            //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.$node->title.'';
            $Follengthtrim = (strlen($node->title) > 22) ? substr($node->title, 0, 19).'...' : $node->title;
            $foldericon   = $Drive_folder_icon_image . $Follengthtrim; 
            $projectname =  l($foldericon, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));
            // For Grid folder and icon
            $foldericongrid   = $Grid_folder_icon_image  . $Follengthtrim; 
            $ProjectnameforGrid =  l($foldericongrid, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));
            // End Grid folder and icon 
            $share_with_url = m6drive_check_project_folder_shared('folder', $node->nid, 0);
            $rows[] = array(
              'data' => array(
                 array('data'=>'Drag Name','class'=>array('text-left','hidden')),
                 array('data'=>'<span class="project-drive-nids" style="display:none;">'.$node->nid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
                 array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                array('data'=> $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                array('data' => $comprealusername['realname'],'class' => array('col-md-2','text-left')),
                array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                array('data'=>'-','class'=>array('col-md-1','text-left')),
                array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
                //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
               ),
              'id' => array('0'), 
              'class' => array('not-trashable-drive', 'custom-odd','customsearchformydrive','m6drive-project-archive-'.$node->nid.'-'.$company->nid.'-row'),
            );
            //For dev str row folder
            $divprojectstrfol .='<div class="not-trashable-drive grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                     <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                    <div class="grid-item-anchor clearfix">'.$ProjectnameforGrid.'</div>
                              </div>';
           //End dev str row
          }
        }
      }
      if ($projectnid == 'rfp') {
        // Processing for RFP Documents.
        $RfpNodeList = m6drive_get_all_rfp_node_list();
        foreach($RfpNodeList as $key => $nid) { 
          $node = node_load($nid);
          $ChkNidInArchive = _get_all_projectnid_in_archive_drive($user->uid, $node->nid);
          if ($ChkNidInArchive != $node->nid) {
            $comprealusername = '';
             $nodeTitletrim = '';
            //$comprealusername = _get_node_company_user_name($node->nid);
             $comprealusername =_get_user_data_by_uid($node->uid);
            //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.$node->title.'';
            $Follengthtrim = (strlen($node->title) > 22) ? substr($node->title, 0, 19).'...' : $node->title;
            $foldericon   = $Drive_folder_icon_image . $Follengthtrim; 

            $projectname =  l($foldericon, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));

             // For Grid folder and icon
            $foldericongrid   = $Grid_folder_icon_image  . $Follengthtrim; 
            $ProjectnameforGrid =  l($foldericongrid, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));
            // End Grid folder and icon 

            $share_with_url = m6drive_check_project_folder_shared('folder', $node->nid, 0);
            $rows[] = array(
              'data' => array(
                 array('data'=>'Drag Name','class'=>array('text-left','hidden')),
                 array('data'=>'<span class="project-drive-nids" style="display:none;">'.$node->nid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
                 array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                array('data'=> $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                array('data' => $comprealusername['realname'],'class' => array('col-md-2','text-left')),
                array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                array('data'=>'-','class'=>array('col-md-1','text-left')),
                array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
                //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
               ),
              'id' => array('0'), 
              'class' => array('not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-'.$node->nid.'-'.$company->nid.'-row'),
            );
              //For dev str row folder
            $divprojectstrfol .='<div class="not-trashable-drive grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                     <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                    <div class="grid-item-anchor clearfix">'.$ProjectnameforGrid.'</div>
                              </div>';
           //End dev str row
          }
        }
      }
    }
    $foldericon = '';
    if (!empty($projectnid) && is_numeric($projectnid)) {
      $node = node_load($projectnid);
      $companyusersdetail =_get_user_data_by_uid($node->uid);
      $companyusersfullname =  $companyusersdetail['realname'];
      // For project images
      if ($node->type == 'project') {
        $fieldrfpdocumentArr =_get_all_rfp_nid_using_project_nid_project_drive($node->nid, $only_nids = TRUE);
        $uri =  $node->field_images['und'][0]['uri'];
        $fid =  $node->field_images['und'][0]['fid'];
        $filename = $node->field_images['und'][0]['filename'];
        if (!empty($fid)) {
          $ChkFidInArchive =_get_all_projectfid_in_archive_drive($user->uid,  $fid);
          if ($ChkFidInArchive != $fid) {
            $filepath = file_create_url($uri);  
            $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
            $share_with_url = m6drive_check_project_folder_shared('file', $projectnid, $fid);
            $rows[] = array(
              'data' => array(
                array('data'=>'Drag Name','class'=>array('text-left','hidden')),
                array('data'=> 'Drag name','class'=>array('col-md-1','text-left','hidden')),
                array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                array('data'=>   $Attachment, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                array('data' => $companyusersfullname,'class' => array('col-md-2','text-left')),
                array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-1','text-left')),
                array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
                //array('data' => project_drive_action_btn('file',$fid),'class' => array('col-md-2','text-left')), 
                ),  
              'class' => array('not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-'.$fid.'-'.$company->nid.'-row'),
            );
            //For div str row file
            $img_url = image_style_url('user_image_large', $uri);
            $divprojectstrfile .=' <div class="not-trashable-drive grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                       <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                         <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                        <img src="'.$img_url.'"> 
                         <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                  </div>';
            //End div str row file
          }
        }
        foreach($fieldrfpdocumentArr as $rfpnids) {
          $node = node_load($rfpnids);
          $comprealusername = '';
          $nodeTitletrim = '';
          //$comprealusername = _get_node_company_user_name($node->nid);
          $comprealusername =_get_user_data_by_uid($node->uid);
          //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.$node->title.'';
          $Follengthtrim = (strlen($node->title) > 22) ? substr($node->title, 0, 19).'...' : $node->title;
          $foldericon   = $Drive_folder_icon_image . $Follengthtrim; 

          $projectname =  l($foldericon, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));

          $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim; 
          $ProjectnameforGrid =  l($foldericongrid, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));

          $share_with_url = m6drive_check_project_folder_shared('folder', $node->nid, 0);
          $rows[] = array(
            'data' => array(
               array('data'=>'Drag Name','class'=>array('text-left','hidden')),
               array('data'=>'<span class="project-drive-nids" style="display:none;">'.$node->nid.'</span>', 'class'=> array('m6drive-display-none-drag')),
               array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=> $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $comprealusername['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
              array('data'=>'-','class'=>array('col-md-1','text-left')),
              array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
              //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
             ),
            'id' => array('0'), 
            'class' => array('not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-'.$node->nid.'-'.$company->nid.'-row'),
          );
          //For dev str row folder
          $divprojectstrfol .='<div class="not-trashable-drive grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                   <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                  <div class="grid-item-anchor clearfix">'.$ProjectnameforGrid.'</div>
                            </div>';
        }
      }
      else {
        $fieldrfpdocumentArr = _get_all_rfp_document_images_project_drive($node->nid);
        $uri =  $node->field_rfp_logo['und'][0]['uri'];
        $fid =  $node->field_rfp_logo['und'][0]['fid'];
        $filename = $node->field_rfp_logo['und'][0]['filename'];
        if(!empty($fid)) {
          $ChkFidInArchive =_get_all_projectfid_in_archive_drive($user->uid,  $fid);
          if($ChkFidInArchive != $fid) {
            $filepath = file_create_url($uri);  
            $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
            $share_with_url = m6drive_check_project_folder_shared('file', $projectnid, $fid);
            $rows[] = array(
              'data' => array(
                array('data'=>'Drag Name','class'=>array('text-left','hidden')),
                array('data'=> 'Drag name','class'=>array('col-md-1','text-left','hidden')),
                array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                array('data'=>   $Attachment, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                array('data' => $companyusersfullname,'class' => array('col-md-2','text-left')),
                array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-1','text-left')),
                array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
                //array('data' => project_drive_action_btn('file',$fid),'class' => array('col-md-2','text-left')), 
                ),  
              'class' => array('not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-'.$fid.'-'.$company->nid.'-row'),
            );
             //For dev str row file ==========
             $img_url = image_style_url('user_image_large', $uri);
             $divprojectstrfile .=' <div class="not-trashable-drive grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                       <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                         <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       <img src='.$img_url.'>
                         <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                  </div>';
             //End dev str row file==========

          }
        }
        foreach($fieldrfpdocumentArr as $projectfiles) {
          if(!empty($projectfiles['fid'])) {
            // $ChkFidInArchive =_get_all_projectfid_in_archive_drive($user->uid, $projectfiles['fid']);
            // if($ChkFidInArchive != $projectfiles['fid']){
              $filepath = file_create_url($projectfiles['uri']);  
              $Attachment = l($projectfiles['filename'], $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$projectfiles['fid'])));
              $share_with_url = m6drive_check_project_folder_shared('file', $projectnid, $projectfiles['fid']);
              $rows[] = array(
                'data' => array(
                  array('data'=>'Drag Name','class'=>array('text-left','hidden')),
                  array('data'=> 'Drag name','class'=>array('col-md-1','text-left','hidden')),
                  array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                  array('data'=>   $Attachment, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                  array('data' => $companyusersfullname,'class' => array('col-md-2','text-left')),
                  array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                  array('data'=> _get_m6drive_project_filesize_by_fid($projectfiles['fid']),'class'=>array('col-md-1','text-left')),
                  array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
                  //array('data' => project_drive_action_btn('file', $projectfiles['fid']),'class' => array('col-md-2','text-left')), 
                  ),  
                'class' => array('not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-'.$projectfiles['fid'].'-'.$company->nid.'-row'),
              );
              //For dev str row file ==========
             $fileicondrive = _get_file_icon_m6drive($projectfiles['filemime']);
             if ($fileicondrive) {
                $img_url = $fileicondrive;
             }
             else {
                $img_url = image_style_url('user_image_large', $projectfiles['uri']);
                $img_url = '<img src = ' . $img_url . '>';
             }
             $divprojectstrfile .= '<div class="not-trashable-drive grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                               <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"></div>
                         <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                        '.$img_url.'
                         <div class="clearfix text-blue grid-item-anchor">'.$projectfiles['filename'].'</div>
                  </div>';
             //End dev str row file==========
            // }
          }
        }
      }
    }
    elseif (empty($projectnid)) {
      // ===for Project Folder And RFP Folder Root.
      $comprealusername =_get_user_data_by_uid($user->uid);
      $Projectfoldericon   = $Drive_folder_icon_image. 'M6 Project Postings'; 
      $projectname =  l($Projectfoldericon, 'project-load-drive/project/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-0'),'html' => TRUE));

      $Projectfoldericongrid   =  $Grid_folder_icon_image. 'M6 Project Postings'; 
      $ProjectnameforGrid =  l($Projectfoldericongrid, 'project-load-drive/project/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-0'),'html' => TRUE));

      $rows[] = array(
        'data' => array(
          array('data'=>'Drag Name','class'=>array('text-left','hidden')),
          array('data'=>'<span class="project-drive-nids" style="display:none;">0</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="M6 Project Postings" name="m6drive-project-project" value="project-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
          array('data'=> $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
          array('data' =>  $comprealusername['realname'],'class' => array('col-md-2','text-left')),
          array('data' => '-','class' => array('col-md-2','text-left')),
          array('data'=>'-','class'=>array('col-md-1','text-left')),
          array('data'=> '-','class'=>array('col-md-2','text-left')),
          //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
         ),
        'id' => array('0'), 
        'class' => array('not-shareable-drive','not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-0-'.$company->nid.'-row'),
      );

      $divprojectstrfol .= '<div class="not-shareable-drive not-trashable-drive grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                               <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="M6 Project Postings" name="m6drive-project-project" value="project-folder" class="form-checkbox m6drive-project-checkbox"></div>
                              <div class="grid-item-anchor clearfix">'. $ProjectnameforGrid.'</div>
                        </div>';
      // ===for Rfp Folder
      $Rfpfoldericon   = $Drive_folder_icon_image. 'M6 RFP&apos;s'; 
      $Rfpname =  l($Rfpfoldericon, 'project-load-drive/rfp/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-0'),'html' => TRUE));

      $Rfpfoldericongrid   = $Grid_folder_icon_image. 'M6 RFP&apos;s'; 
      $Rfpnamegrid =  l($Rfpfoldericongrid, 'project-load-drive/rfp/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-0'),'html' => TRUE));

      $rows[] = array(
        'data' => array(
          array('data'=>'Drag Name','class'=>array('text-left','hidden')),
          array('data'=>'<span class="project-drive-nids" style="display:none;">0</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="M6 RFP&apos;s" name="m6drive-project-rfp" value="rfp-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
          array('data'=> $Rfpname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
          array('data' => $comprealusername['realname'],'class' => array('col-md-2','text-left')),
          array('data' => '-','class' => array('col-md-2','text-left')),
          array('data'=>'-','class'=>array('col-md-2','text-left')),
          array('data'=> '-','class'=>array('col-md-1','text-left')),
          //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
         ),
        'id' => array('0'), 
        'class' => array('not-shareable-drive','not-trashable-drive','custom-odd','customsearchformydrive','m6drive-project-archive-0-'.$company->nid.'-row'),
      );
      $divprojectstrfol .= '<div class="not-shareable-drive not-trashable-drive grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                               <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="M6 RFP&apos;s" name="m6drive-project-rfp" value="rfp-folder" class="form-checkbox m6drive-project-checkbox"></div>
                              <div class="grid-item-anchor clearfix">'.$Rfpnamegrid.'</div>
                        </div>';
    // End Rfp folder here
    }
    if (!empty($projectnid) && is_numeric($projectnid)) {
      $folder_id = $projectnid;
    }
  }

  if ($check_for_add_to_my_drive) {
    // If we are to check the add to my drive table, then we shall get all the
    // stored folder IDs or Project IDs and proceed.
    $query = db_select('m6connect_m6drive_addto_mydrive', 'm')
      ->fields('m')
      ->condition('services', 'm6drive_project')
      ->condition('user_uid', $user->uid)
      ->condition('root', 1)
      ->orderBy('created_date', 'DESC') //ORDER BY created
      ->execute()
      ->fetchAll();
    foreach ($query as $key => $value) {
      if ($value->folder_id) {
        // It is a folder, It may be a folder or a project(node).
        $sub_query = db_select('m6connect_m6drive', 'm')
          ->fields('m')
          ->condition('Id', $value->folder_id)
          ->execute();
        if ($sub_query->rowCount() > 0) {
          // It is a custom uploaded folder.
          $values = $sub_query->fetchObject();

          // In this case, we also need the node id/projectnid of this folder
          // so as to keep the breadcrumbs working.
          $prnid = 0;
          $parents = m6drive_get_parent_folder($values->Id);
          foreach ($parents as $key => $value) {
            foreach ($value as $key1 => $value1) {
              if (is_array($value1)) {
                $prnid = $key1;
              }
            }
          }
          $UserFnameLname =_get_user_data_by_uid($values->user_uid);
          $Follengthtrim = (strlen(ucwords(str_replace('_',' ',$values->foldername))) > 22) ? substr(ucwords(str_replace('_',' ',$values->foldername)), 0, 19).'...' : ucwords(str_replace('_',' ',$values->foldername));
          //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.ucwords(str_replace('_',' ',$values->foldername)).'';
          $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
          $foldername =  l($foldericon, 'project-load-drive/' . $prnid . '/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));

          $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
          $foldernamegrid =  l($foldericongrid, 'project-load-drive/' . $prnid . '/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));


          $share_with_url = m6drive_check_file_folder_shared('folder', $values->Id);
          $rows[] = array(
            'data' => array(
              array('data'=>'<span class="folder-ids" style="display:none;">'.$values->Id.'-folder</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
              array('data'=>'<span class="project-drive-nids" style="display:none;">'.$prnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=> $foldername, 'class' => array('col-md-4','text-left','m6drive-drag-content-show','drive-getting-folder')),
              array('data' => $UserFnameLname['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('col-md-2','text-left')),
              array('data'=>'-','class'=>array('col-md-1','text-left')),
              array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
             //array('data' => m6drive_folder_action_btn('folder',$values->Id),'class' => array('col-md-2','text-left')),           
            ),
            'id' => array(''.$values->Id.''),
            'class' => array('custom-odd', 'customsearchformydrive','project-drive-folder-dragable', 'project-drive-folder-droppable', 'm6drive-folderdelete-'.$values->Id.'-'.$company->nid.'-row'),
          );
          //For dev str row folder ==========
          $divprojectstrfol .='<div id="' . $values->Id . '"class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10 project-drive-folder-dragable project-drive-folder-droppable">
                              <div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">' . $values->Id. '-folder</span></div>
                              <div class="m6drive-display-none-drag" style="display: none;"><span class="project-drive-nids" style="display:none;">' . $prnid. '</span></div>
                                <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix m6drive-drag-content-show">'.$foldernamegrid.'</div>
                          </div>';
          //End dev str row==========
        }
        else {
          // It is a project.
          $node = node_load($value->folder_id);
          $comprealusername =_get_user_data_by_uid($node->uid);
          $Follengthtrim = (strlen($node->title) > 22) ? substr($node->title, 0, 19).'...' : $node->title;
          //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.$node->title.'';
          $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
          $projectname =  l($foldericon, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));

          $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
          $projectnamegrid =  l($foldericongrid, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));

          $share_with_url = m6drive_check_project_folder_shared('folder', $node->nid, 0);
          $rows[] = array(
            'data' => array(
              array('data'=>'Drag Name','class'=>array('text-left','hidden')),
              array('data'=>'<span class="project-drive-nids" style="display:none;">'.$node->nid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=> $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $comprealusername['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
              array('data'=>'-','class'=>array('col-md-1','text-left')),
              array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
              //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
             ),
            'id' => array('0'),
            'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$node->nid.'-'.$company->nid.'-row'),
          );
          //For dev str row folder ==========
          $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                               <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$projectnamegrid .'</div>
                          </div>';
          //End dev str row==========
        }
      }
      elseif ($value->file  && $filevalue = file_load($value->file)) {
        // File can be uploaded only.
        $file_query = db_select('m6connect_m6drive_attachment', 'f')
          ->fields('f')
          ->condition('file', $value->file)
          ->execute();
        if ($file_query->rowCount() > 0) {
          $values = $file_query->fetchObject();
          $UserFnameLname =_get_user_data_by_uid($values->user_uid);
          
          $fid =  $values->file;
          //$filevalue = file_load($fid);
          $uri = $filevalue->uri;
          $filename =  $filevalue->filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);  
          $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id))); 
          $share_with_url = m6drive_check_file_folder_shared('file', $fid);
          $rows[] = array(
            'data' => array(
              array('data'=>'<span class="folder-ids" style="display:none;">'.$fid.'-file</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
              array('data'=>'<span class="project-drive-nids" style="display:none;">'.$node->nid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $Attachment, 'class' => array('col-md-4','text-left', 'm6drive-drag-content-show','drive-getting-folder')),
              array('data' => $UserFnameLname['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('col-md-2','text-left')),
              array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('col-md-1','text-left')),
              array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
            ),  
            'class' => array('custom-odd','customsearchformydrive','project-drive-folder-dragable', 'm6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
          );
          //For dev str row file ==========
          $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
          if ($fileicondrive) {
            $img_url = $fileicondrive;
          }
          else {
            $img_url = image_style_url('user_image_large', $uri);
            $img_url = '<img src = ' . $img_url . '>';
          }
           $divprojectstrfile .= '<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10 project-drive-folder-dragable">
                            <div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">'.$fid.'-file</span></div>
                            <div class="m6drive-display-none-drag" style="display: none;"><span class="project-drive-nids" style="display:none;">' . $node->nid . '</span></div>
                            <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                            <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                            '.$img_url.'
                            <div class="clearfix text-blue grid-item-anchor m6drive-drag-content-show">'.$filename.'</div>
                            </div>';
           //End dev str row file==========
        }
      }
    }
  }

  // Getting folders and files from add to my drive for inner folders.
  $query = db_select('m6connect_m6drive_addto_mydrive', 'm')
    ->fields('m')
    ->condition('services', 'm6drive_project')
    ->condition('user_uid', $user->uid)
    ->condition('root', 0)
    ->condition('parent_id', $folder_id)
    ->orderBy('created_date', 'DESC') //ORDER BY created
    ->execute()
    ->fetchAll();
  foreach ($query as $key => $value) {
    if ($value->folder_id) {
      // It is a folder, It may be a folder or a project(node).
      $sub_query = db_select('m6connect_m6drive', 'm')
        ->fields('m')
        ->condition('Id', $value->folder_id)
        ->execute();
      if ($sub_query->rowCount() > 0) {
        // It is a custom uploaded folder.
        $values = $sub_query->fetchObject();

        // In this case, we also need the node id/projectnid of this folder
        // so as to keep the breadcrumbs working.
        $prnid = 0;
        $parents = m6drive_get_parent_folder($values->Id);
        foreach ($parents as $key => $value) {
          foreach ($value as $key1 => $value1) {
            if (is_array($value1)) {
              $prnid = $key1;
            }
          }
        }
        $UserFnameLname =_get_user_data_by_uid($values->user_uid);
        //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.ucwords(str_replace('_',' ',$values->foldername)).'';
        $Follengthtrim = (strlen(ucwords(str_replace('_',' ',$values->foldername))) > 22) ? substr(ucwords(str_replace('_',' ',$values->foldername)), 0, 19).'...' : ucwords(str_replace('_',' ',$values->foldername));

        $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
        $foldername =  l($foldericon, 'project-load-drive/' . $prnid . '/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));

        $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
        $foldernamegrid =  l($foldericongrid, 'project-load-drive/' . $prnid . '/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));

        $share_with_url = m6drive_check_file_folder_shared('folder', $values->Id);
        $rows[] = array(
         'data' => array(
           array('data'=>'<span class="folder-ids" style="display:none;">'.$values->Id.'-folder</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
           array('data'=>'<span class="project-drive-nids" style="display:none;">'.$prnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
           array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
           array('data'=> $foldername, 'class' => array('col-md-4','text-left','m6drive-drag-content-show','drive-getting-folder')),
           array('data' => $UserFnameLname['realname'],'class' => array('col-md-2','text-left')),
           array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('col-md-2','text-left')),
           array('data'=>'-','class'=>array('col-md-1','text-left')),
           array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
           //array('data' => m6drive_folder_action_btn('folder',$values->Id),'class' => array('col-md-2','text-left')),           
          ),
         'id' => array(''.$values->Id.''),
         'class' => array('custom-odd', 'customsearchformydrive','project-drive-folder-dragable', 'project-drive-folder-droppable', 'm6drive-folderdelete-'.$values->Id.'-'.$company->nid.'-row'),
          );
         //For dev str row folder ==========
           $divprojectstrfol .='<div id="' . $values->Id . '"class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10 project-drive-folder-dragable project-drive-folder-droppable">
                              <div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">' . $values->Id . '-folder</span></div>
                              <div class="m6drive-display-none-drag" style="display: none;"><span class="project-drive-nids" style="display:none;">' . $prnid. '</span></div>
                              <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix m6drive-drag-content-show">'.$foldernamegrid.'</div>
                          </div>';
          //End dev str row==========
      }
      else {
        // It is a project.
        $node = node_load($value->folder_id);
        $comprealusername =_get_user_data_by_uid($node->uid);
        //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.$node->title.'';
        $Follengthtrim = (strlen($node->title) > 22) ? substr($node->title, 0, 19).'...' : $node->title;

        $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
        $projectname =  l($foldericon, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));

        $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
        $projectnamegrid =  l($foldericongrid, 'project-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' => TRUE));


        $share_with_url = m6drive_check_project_folder_shared('folder', $node->nid, 0);
        $rows[] = array(
          'data' => array(
            array('data'=>'Drag Name', 'class' => array('col-md-1','text-left','hidden')),
           array('data'=>'<span class="project-drive-nids" style="display:none;">'.$node->nid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
           array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=> $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $comprealusername['realname'],'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-1','text-left')),
            array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
            //array('data' => project_drive_action_btn('folder',$node->nid),'class' => array('col-md-2','text-left')),           
           ),
          'id' => array('0'),
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$node->nid.'-'.$company->nid.'-row'),
        );
        //For dev str row folder ==========
           $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                              <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$projectnamegrid.'</div>
                          </div>';
          //End dev str row==========
      }
    }
    elseif ($value->file && $filevalue = file_load($value->file)) {
      // File can be uploaded only.
      $file_query = db_select('m6connect_m6drive_attachment', 'f')
        ->fields('f')
        ->condition('file', $value->file)
        ->execute();
      if ($file_query->rowCount() > 0) {
        $values = $file_query->fetchObject();
        $UserFnameLname =_get_user_data_by_uid($values->user_uid);
        
        $parents = m6drive_get_parent_folder($values->folder_id);
        foreach ($parents as $key => $value) {
          foreach ($value as $key1 => $value1) {
            if (is_array($value1)) {
              $prnid = $key1;
            }
          }
        }

        $fid =  $values->file;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);  
        $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id))); 
        $share_with_url = m6drive_check_file_folder_shared('file', $fid);
        $rows[] = array(
          'data' => array(
            array('data'=>'<span class="folder-ids" style="display:none;">'.$fid.'-file</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
             array('data'=>'<span class="project-drive-nids" style="display:none;">'.$prnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $Attachment, 'class' => array('col-md-4','text-left', 'm6drive-drag-content-show','drive-getting-folder')),
            array('data' => $UserFnameLname['realname'],'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('col-md-1','text-left')),
            array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
          ),  
          'class' => array('custom-odd','customsearchformydrive','project-drive-folder-dragable', 'm6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
        );
      }

      $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
      if ($fileicondrive) {
        $img_url = $fileicondrive;
      }
      else {
        $img_url = image_style_url('user_image_large', $uri);
        $img_url = '<img src = ' . $img_url . '>';
      }
       $divprojectstrfile .= '<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10 project-drive-folder-dragable">
                        <div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">'.$fid.'-file</span></div>
                        <div class="m6drive-display-none-drag" style="display: none;"><span class="project-drive-nids" style="display:none;">' . $prnid . '</span></div>
                        <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                        <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                        '.$img_url.'
                        <div class="clearfix text-blue grid-item-anchor m6drive-drag-content-show">'.$filename.'</div>
                        </div>';
    }
  }

  $check_company = m6drive_check_parent_folder_addto_mydrive($folder_id);
  // Getting folders and files from drive and attachment tables.
  $drive_query = db_select('m6connect_m6drive', 'm')
    ->fields('m')
    ->condition('services', 'm6drive_project')
    ->condition('parent_id', $folder_id);
  if ($check_for_add_to_my_drive || $projectnid == 'project' || $projectnid == 'rfp') {
    $drive_query->condition('user_uid', $user->uid);
  }
  if ($projectnid === 'project' && empty($folder_id)) {
    $drive_query->condition('root', 2);
  }
  if ($projectnid === 'rfp' && empty($folder_id)) {
    $drive_query->condition('root', 3);
  }
  if ($check_for_add_to_my_drive) {
    $drive_query->condition('root', 1);
  }
  if ($check_company === FALSE) {
    $drive_query->condition('company_nid', $company->nid);
  }
  $drive_query->condition('trash_status', 0);
  $drive_query->condition('archive_status', 0);
  $drive_query->orderBy('created_date', 'DESC'); //ORDER BY created
  $record = $drive_query->execute()->fetchAll();

  $querysub = db_select('m6connect_m6drive_attachment','m');    
  $querysub->fields('m',array('file','created_date','trash_status', 'user_uid'));
  $querysub->condition('m.services', 'm6drive_project');
  $querysub->condition('m.folder_id', $folder_id);
  if($check_for_add_to_my_drive || $projectnid == 'project' || $projectnid == 'rfp') {
    $querysub->condition('user_uid', $user->uid);
  }
  if($projectnid === 'project' && empty($folder_id)) {
    $querysub->condition('root', 2);
  }
  if($projectnid === 'rfp' && empty($folder_id)) {
    $querysub->condition('root', 3);
  }
  if($check_for_add_to_my_drive) {
    $querysub->condition('root', 1);
  }
  if ($check_company === FALSE) {
     $querysub->condition('company_nid', $company->nid);
  }
  $querysub->condition('m.trash_status', 0);
  $querysub->condition('m.archive_status', 0);
  $querysub->orderBy('m.created_date', 'DESC');  //ORDER BY created
  $recordsub = $querysub->execute()->fetchAll();
  $complteresult = array_merge($record, $recordsub);
  $foldericon = '';
  
  foreach ($complteresult as $values) {
    //$divstr_arrfol[] = $values;

    if ($values->foldername) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.ucwords(str_replace('_',' ',$values->foldername)).'';
      $Follengthtrim = (strlen(ucwords(str_replace('_',' ',$values->foldername))) > 22) ? substr(ucwords(str_replace('_',' ',$values->foldername)), 0, 19).'...' : ucwords(str_replace('_',' ',$values->foldername));

      $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
      $foldername =  l($foldericon, 'project-load-drive/'.$projectnid.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));

      $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
      $foldernamegrid =  l($foldericongrid, 'project-load-drive/'.$projectnid.'/'.$values->Id.'/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$values->Id),'html' => TRUE));

      $share_with_url = m6drive_check_file_folder_shared('folder', $values->Id);
      $rows[] = array(
       'data' => array(
         array('data'=>'<span class="folder-ids" style="display:none;">'.$values->Id.'-folder</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
        array('data'=>'<span class="project-drive-nids" style="display:none;">'.$projectnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
         array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
         array('data'=> $foldername, 'class' => array('col-md-4','text-left','m6drive-drag-content-show','drive-getting-folder')),
         array('data' => $UserFnameLname['realname'],'class' => array('col-md-2','text-left')),
         array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('col-md-2','text-left')),
         array('data'=>'-','class'=>array('col-md-1','text-left')),
         array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
         //array('data' => m6drive_folder_action_btn('folder',$values->Id),'class' => array('col-md-2','text-left')),           
        ),
       'id' => array(''.$values->Id.''),     
       'class' => array('custom-odd','customsearchformydrive','project-drive-folder-dragable','project-drive-folder-droppable','m6drive-folderdelete-'.$values->Id.'-'.$company->nid.'-row'),
        );
      //For dev str row folder ==========
        $divprojectstrfol .='<div id="' . $values->Id . '"class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10 project-drive-folder-dragable project-drive-folder-droppable">
                              <div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">' . $values->Id . '-folder</span></div>
                              <div class="m6drive-display-none-drag" style="display: none;"><span class="project-drive-nids" style="display:none;">' . $projectnid. '</span></div>
                                   <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.ucwords(str_replace('_',' ',$values->foldername)).'" name="m6drive-folder-'.$values->Id.'" value="'.$values->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix m6drive-drag-content-show">'.$foldernamegrid.'</div>
                          </div>';
      //End dev str row==========

    }
    if ($values->file && $filevalue = file_load($values->file)) {
      $UserFnameLname =_get_user_data_by_uid($values->user_uid);
      $fid =  $values->file;
      //$filevalue = file_load($fid);
      $uri = $filevalue->uri;
      $filename =  $filevalue->filename;
      $filetype = $filevalue->type;
      $filepath = file_create_url($uri);  
      $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$values->Id))); 
      $share_with_url = m6drive_check_file_folder_shared('file', $fid);
      //$img_url = image_style_url('user_image_large', $uri);
      $rows[] = array(
        'data' => array(
          array('data'=>'<span class="folder-ids" style="display:none;">'.$fid.'-file</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
           array('data'=>'<span class="project-drive-nids" style="display:none;">'.$projectnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
          array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
          array('data'=>  $Attachment, 'class' => array('col-md-4','text-left','m6drive-drag-content-show','drive-getting-folder')),
          array('data' => $UserFnameLname['realname'],'class' => array('col-md-2','text-left')),
          array('data' => date('F d, Y', strtotime($values->created_date)),'class' => array('col-md-2','text-left')),
          array('data'=> _get_m6drive_total_space_user_fid($fid),'class'=>array('col-md-1','text-left')),
          array('data'=> $share_with_url,'class'=>array('col-md-2','text-left')),
        ),  
        'class' => array('custom-odd','customsearchformydrive','project-drive-folder-dragable','m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
      );
      //For dev str row file ==========
      $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
      if($fileicondrive) {
         $img_url = $fileicondrive;
      }
      else {
        $img_url = image_style_url('user_image_large', $uri);
        $img_url = '<img src= '.$img_url.'>';
      }

      $divprojectstrfile .='<div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10 project-drive-folder-dragable">
                            <div class="m6drive-display-none-drag" style="display: none;"><span class="folder-ids" style="display:none;">'.$fid.'-file</span></div>
                            <div class="m6drive-display-none-drag" style="display: none;"><span class="project-drive-nids" style="display:none;">' . $projectnid . '</span></div>
                            <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-folder-'.  $fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                            <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                            '.$img_url.' 
                            <div class="clearfix text-blue grid-item-anchor m6drive-drag-content-show">'.$filename.'</div>
                            </div>';
      //End dev str row file==========
    }
  }
  $return .= '<div class="list-view" style="'.$list_display.'">';
  $return .= theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-project-drive','table-striped','table-hover','table-bordered','text-center'))));
  $return .= '</div>';
  // End here fir table List view structure========

  // start here for Grid  view structure========
  $return .= '<div class="grid-view" style="'.$grid_display.'">';
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
  $return .= '<div class="grid-view-folders row margin-5">';
  // First handling only Folders.
  if (empty($divprojectstrfol)) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
  }
  else {
    $return .= $divprojectstrfol; 
  }
  $return .= '</div>'; //end grid-view-folders
  // Then handling only Files.
  $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
  $return .= '<div class="grid-view-files row margin-5">';
  if (empty($divprojectstrfile)) {
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
  }
  else {
    $return .= $divprojectstrfile; 
  }
  $return .= '</div>'; // end grid-view-files.
  $return .= '</div>'; // end grid-view.
  // End here for Grid  view structure========

  return $return;
}

/**
 * Function to get form for sharing in company drive.
 */
function project_drive_share_form($form, &$form_state, $sharetype, $shareid) {
  $shareid = (isset($form_state['share_id']) && is_numeric($form_state['share_id'])) ? $form_state['share_id'] : $shareid;
  $sharetype = (isset($form_state['share_type'])) ? $form_state['share_type'] : $sharetype;
  $form_state['share_id']= $shareid; 
  $form_state['share_type'] = $sharetype;

  $form['share_email'] = array(
    '#type' => 'textfield',
    '#attributes'=> array('class'=> array('form-control'),'placeholder'=>'Enter Email address...'),
    '#required' => TRUE,
    '#prefix' => '<div class="clearfix share_popupsection margin-bottom-45">
      <div class="clearfix"><label>People</label></div><div class="clearfix text-right"><label>Permissions</label></div><div class="clearfix"><div class="input-group">',
    '#element_validate' => array('project_drive_email_element_validate'),
  );

  $active = array('r' => t('<label for="ex1_3_1">Can View</label>'), 'r-o' => t('<label for="ex1_3_1">Can View & Organise</label>'), 'r-w-o' => t('<label for="ex1_3_1">Can View, Organise & Download</label>'));

   $form['share_permission'] = array(
    '#type' => 'radios',
    '#default_value' => 'r',
    '#options' => $active,
    '#prefix' => '<span class="input-group-btn">
      <div class="input-group-btn">
      <button data-toggle="dropdown" class="btn btn-primary dropdown-toggle onclickBtn_popup" style="margin:0;     height: 32px;"><i class="fa fa-eye" aria-hidden="true"></i> <span class="caret"></span></button>
      <ul class="dropdown-menu dropdown-menu-right">',
    '#suffix' => '</ul></div></span>
      </div>
      </div>
      </div>',
  );

  $form['multiple_projectnid'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-project-drive-perform clearfix')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('project_drive_share_submit'),
    '#value' => 'Done',
    '#prefix' => '<div class="clearfix margin-bottom-25">',  
    '#suffix' => $closeButton.'</div>', 
  );

  return $form;
}

/**
 * Project drive email validator.
 */
function project_drive_email_element_validate($element, &$form_state, $form) {
  if (!valid_email_address($element['#value'])) {
    form_error($element, t('Please enter a valid email address.'));
  }
}

/**
 * Submit handler for project_drive_share_form
 */
function project_drive_share_submit($form, &$form_state) {
  global $user, $base_url;
  $shareid = $form_state['share_id'];
  $sharetype = $form_state['share_type']; 
  $values = $form_state['values']; 
  $share_email = $values['share_email'];
  $sharedate =  date('Y-m-d H:i:s');
  $projectMultiple = $values['multiple_projectnid'];
  $projectfolder =  explode( ',' ,$projectMultiple);

  if($values['share_permission']) {
    $permdrive = $values['share_permission']; 
  }
  else {
    $permdrive = 'r';
  }
  if (!empty($projectfolder)) {
    $usersfulldetails = _get_user_details_by_og_email($share_email);
    if (!empty($usersfulldetails->uid)) {
      $shareto_uid =  $usersfulldetails->uid;
    }
    else {
      $shareto_uid = 0;
    }
    foreach($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $projectIdMul = $getStatus[0];
        _clear_child_folder_files_share($projectIdMul, $share_to_uid);

        // First handling any children if present.
        _share_folder_and_files_project($projectIdMul, $share_email, $permdrive);
        $sharedate =  date('Y-m-d H:i:s');

        // Checking if it a node or uploaded folder in the drive.
        $query = db_select('m6connect_m6drive', 'm')
          ->fields('m')
          ->condition('Id', $projectIdMul)
          ->execute()
          ->rowCount();

        if ($query > 0) {
          db_delete('m6connect_m6drive_shared')
            ->condition('share_by_uid', $user->uid)
            ->condition('share_to_uid', $shareto_uid)
            ->condition('folder_id', $projectIdMul)
            ->execute();

          db_insert('m6connect_m6drive_shared')
            ->fields(array(
              'share_by_uid' => $user->uid,
              'folder_id' => $projectIdMul,
              'shared_date' => $sharedate,
              'email_id' => $share_email,
              'share_to_uid'=> $shareto_uid,
              'fid' => 0,
              'root' => 1,
              'services' => 'm6drive_project',
              'permissions' => $permdrive,
            ))
            ->execute();
        }
        else {
          // Making sure, that double entry is not processed.
          db_delete('m6connect_project_drive_shared')
            ->condition('share_by_uid', $user->uid)
            ->condition('share_to_uid', $shareto_uid)
            ->condition('project_nid', $projectIdMul)
            ->execute();

          db_insert('m6connect_project_drive_shared')
            ->fields(array(
              'share_by_uid'=> $user->uid,
              'share_to_uid'=> $shareto_uid,
              'project_nid' =>  $projectIdMul,
              'shared_date' => $sharedate,
              'email_id' => $share_email, 
              'fid' => 0,
              'services' => 'm6drive_project',
              'permissions' => $permdrive,
            ))
            ->execute();
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];

        $query = db_select('m6connect_m6drive_attachment', 'm')
          ->fields('m')
          ->condition('file', $fileIdMul)
          ->execute()
          ->rowCount();

        if ($query > 0) {
          db_delete('m6connect_m6drive_shared')
            ->condition('share_by_uid', $user->uid)
            ->condition('share_to_uid', $shareto_uid)
            ->condition('fid', $fileIdMul)
            ->execute();

          db_insert('m6connect_m6drive_shared')
            ->fields(array(
              'share_by_uid' => $user->uid,
              'shared_date' => $sharedate,
              'email_id' => $share_email,
              'share_to_uid'=> $shareto_uid,
              'fid' => $fileIdMul,
              'services' => 'm6drive_project',
              'root' => 1,
              'permissions' => $permdrive,
            ))
            ->execute();
        }
        else {
          db_delete('m6connect_project_drive_shared')
            ->condition('share_by_uid', $user->uid)
            ->condition('share_to_uid', $shareto_uid)
            ->condition('fid', $fileIdMul)
            ->execute();

          db_insert('m6connect_project_drive_shared')
            ->fields(array(
              'share_by_uid' => $user->uid,
              'shared_date' => $sharedate,
              'email_id' => $share_email,
              'share_to_uid'=> $shareto_uid,
              'fid' => $fileIdMul,
              'services' => 'm6drive_project',
              'permissions' => $permdrive,
            ))
            ->execute();
        }
      }
    }
  }

  // Sending email when drive shared to user
  $folder_shareicon = $base_url . '/sites/all/themes/m6connect/images/folder_share.png';
  $file_shareicon = $base_url . '/sites/all/themes/m6connect/images/file_share_icon.png';
  $UserFnameLname =_get_user_data_by_uid($user->uid);
  $message = "<div style='padding:20px;background:#F5F5F5; border:1px solid #EEE; margin:60px 100px;'>";

  $folder_shared = 0;
  $file_shared = 0;

  // Getting user's company name.shareto_uid
  $company_title = t('Company');
  $company_data = _get_companies_details_by_user_uid($shareto_uid);
  if (!empty($company_data[0]->title)) {
    $company_title = ucwords($company_data[0]->title);
  }

  $sh_message2 = '';
  if (!empty($projectfolder)) {
    foreach ($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $folder_shared++;
        $folderIdMul = $getStatus[0];
        $getfoldername = get_folder_name_by_folderid($folderIdMul);
        $sh_message2 .= '<p><a style="text-decoration:none; font-size:16px;color:#265a7f;font-weight:700;" href="'.$base_url.'/m6drive-share-withme"><img style="vertical-align:bottom;padding:0 5px 0 0;" src="'.$folder_shareicon.'" alt="Drive"/>'.ucwords(str_replace('_',' ',$getfoldername->foldername)).'</a></p>';
      }
      elseif ($getStatus[1] == 'file') {
        $file_shared++;
        $fileIdMul = $getStatus[0];
        $fileObj =  file_load($fileIdMul);
        $url = file_create_url($fileObj->uri);
        $sh_message2 .= '<p><a style="text-decoration:none; font-size:16px;color:#265a7f;font-weight:700;" href="'.$url.'"><img style="vertical-align:bottom;padding:0 5px 0 0;" src="'.$file_shareicon.'" alt="File"/>'.$fileObj->filename.'</a></p>';
      }
    }
  }

  $folders_mark = ' a folder ';
  $files_mark = ' a file ';

  $sh_message = '';
  if ($folder_shared > 0) {
    $folders_mark = $folder_shared == 1 ? ' a folder ' : ' some folders ';
    $sh_message = '<p>' . ucwords($UserFnameLname['realname']) . ' has shared' . $folders_mark . 'with you on your ' . $company_title . ' Drive:</p><br/>';
  }
  if ($file_shared > 0) {
    $files_mark = $file_shared == 1 ? ' a file ' : ' some files ';
    $sh_message = '<p>' . ucwords($UserFnameLname['realname']) . ' has shared' . $files_mark . 'with you on your ' . $company_title . ' Drive:</p><br/>';
  }
  if ($folder_shared > 0 && $file_shared > 0) {
    $sh_message = '<p>' . ucwords($UserFnameLname['realname']) . ' has shared' . $folders_mark . 'and' . $files_mark . 'with you on your ' . $company_title . ' Drive:</p><br/>';
  }

  $message .= $sh_message;
  $message .= $sh_message2;

  $message .= '<div>';
  $form =  ucwords($UserFnameLname['realname']);
  $params = array(
    'subject' => 'M6 Drive Shared With Me',
    'body' =>  $message,
    'sender' =>  $user->mail,
    'language' => language_default(),
    'module' => 'm6connect_misc',
    'key' => 'commitment_mail___invite_2_m6_notify_share',
    'build' => TRUE,
  );
  if (!empty($share_email)) {
    $mail_sent = drupal_mail($params['module'], $params['key'], $share_email, $params['language'], $params);
    watchdog('mail_sent', print_r($mail_sent, 1));
  }

  drupal_set_message('Successfully shared');
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/project/drive');
  }
}

/**
 * Function to generate project share drive breadcrumbs.
 */
function project_drive_shared_breadcrumb($projectnid = 0, $folder_id = 0) {
  global $user, $company;
  if (empty($projectnid)) {
    $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
      <li><a class="use-ajax" href="/project-share-load-drive/0/0/nojs">Shared with</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
      </ul></div>';
  }
  else {
   $node = node_load($projectnid);
   if (empty($folder_id)) {
     $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/project-share-load-drive/0/0/nojs">Shared with</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
     $folders_nodes = _get_rfp_project_folders($node);
     if (!empty($folders_nodes)) {
       foreach ($folders_nodes as $folder) {
          if ($folder != 'project' && $folder != 'rfp') {
            if (_get_share_date_projectnid_using_rfp_nid($projectnid) && $folder_node = node_load($folder)) {
              $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" id="'.$folder_id.'-folderid" data="'.$folder_node->nid.'-projectnid"><a class="use-ajax" href="/project-share-load-drive/' . $folder_node->nid . '/' . $folder_id . '/nojs">'.$folder_node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
            }
          }
        }
      }
     $breadcrumbVal .= '<li class="project-drive-folder-droppable" id="'.$folder_id.'-folderid" data="'.$projectnid.'-projectnid"><a class="use-ajax" href="/project-share-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'.$node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
   }
   else {
     $breadcrumbVal = '<div class="project-folder-breadcrumb-custom search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/project-share-load-drive/0/0/nojs">Shared with</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';

     $folders_nodes = _get_rfp_project_folders($node);
     if (!empty($folders_nodes)) {
       foreach ($folders_nodes as $folder) {
          if ($folder != 'project' && $folder != 'rfp') {
            if (_get_share_date_projectnid_using_rfp_nid($folder) && $folder_node = node_load($folder)) {
              $breadcrumbVal .= '<li class="m6drive-breadcrumb-droppable" id="'.$folder_id.'-folderid" data="'.$folder_node->nid.'-projectnid"><a class="use-ajax" href="/project-share-load-drive/' . $folder_node->nid . '/' . $folder_id . '/nojs">'.$folder_node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
            }
          }
        }
      }
     // $breadcrumbVal .= '<li><a class="use-ajax" href="/project-load-drive/' . $projectnid . '/0/nojs">'.$node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
     $query = db_select('m6connect_m6drive', 'm6d');
     $query->fields('m6d',array('foldername'));
     $query->condition('m6d.Id', $folder_id);
     $query->condition('m6d.services', 'm6drive_project');
     $Currentfolder = $query->execute()->fetchField();

     $output = m6drive_get_parent_folder($folder_id);
     foreach($output as $fldrId => $folderNameVal) {
       foreach($folderNameVal as $foldKey => $fldVal) {
        $get_key = $foldKey;
         if (is_array($fldVal)) {
           $foldKey = 0;
           $fldVal = $fldVal[0];
         }
        if (_check_folder_eligibility_share($get_key)) {
          $breadcrumbVal .= '<li class="project-drive-folder-droppable" id="'.$foldKey.'-folderid" data="'.$projectnid.'-projectnid"><a class="use-ajax" href="/project-share-load-drive/' . $projectnid. '/' . $foldKey . '/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
        }
       }
     }
     $breadcrumbVal .= '<li><a class="use-ajax" href="/project-share-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'. str_replace('_',' ',$Currentfolder) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
   }

   $breadcrumbVal .= '</ul></div>';
  }
  return $breadcrumbVal;
}

/**
 * Helper function to get project share drive content.
 */
function m6drive_project_drive_share_listing_content($projectnid = 0, $folder_id = 0) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');  

  global $company, $user, $base_url;
  $rows = array();
  $header = array(
  array('data' =>'','class' => array('col-md-1','text-left','hidden','no-sort')),
  array('data' =>'','class' => array('col-md-1','text-left','hidden','no-sort')),
  array('data'=>'<input type="checkbox" name="select-m6drive-project-checkbox" class="form-checkbox select-m6drive-project-checkbox">', 'class'=> array('col-md-1','text-center','hidden','no-sort')),
  array('data'=>'Name  &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('company_project_share_m6drive_filter_form',$projectnid, $folder_id)).'</div>','class'=>array('col-md-4','text-left','drive_filter_header')),
  array('data'=>'Shared by','class'=>array('col-md-2','text-left')),
  array('data'=>'Shared date','class'=>array('col-md-2','text-left')),
  array('data'=>'File Size','class'=>array('col-md-3','text-left')),
  //array('data'=>'Action', 'class'=>array('col-md-2','text-left')), 
  );
  // Creating div structure.
  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';
  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';

  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }

  if ($projectnid == 0 && $folder_id == 0) {
    $query = db_select('m6connect_project_drive_shared', 'pds');    
    $query->fields('pds',array('id','share_by_uid','share_to_uid','project_nid','email_id','fid','shared_date', 'permissions'));
    $query->condition('pds.share_to_uid', $user->uid);
    $query->orderBy('pds.shared_date', 'DESC');//ORDER BY created
    $record = $query->execute()->fetchAll();
    foreach($record as $key => $value) {
      if (isset($value->project_nid) && is_numeric($value->project_nid) && $value->project_nid != 0) {
        $ProjectNid = $value->project_nid;
        $projectnid_in_trash = _get_all_projectnid_in_trash_drive($user->uid, $ProjectNid);
        if ($ProjectNid != $projectnid_in_trash) {
          $Node = node_load($ProjectNid);
          //$Usersdetail = _get_user_mail_realname_by_uid($Node->uid);
          //$Usersfullname =  $Usersdetail['realname']; 
          $Usersdetail = _get_user_data_by_uid($Node->uid);
          $Usersfullname =  $Usersdetail['realname'];

          $Dateproject = _get_share_date_projectnid_using_rfp_nid($ProjectNid);
          if ($Dateproject) {
            $Usersdetail = _get_user_data_by_uid($Dateproject->share_by_uid);
            $Usersfullname =  $Usersdetail['realname'];
          }

          $Follengthtrim = (strlen($Node->title) > 22) ? substr($Node->title, 0, 19).'...' : $Node->title;
          $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
          $foldername =  l($foldericon, 'project-share-load-drive/'.$ProjectNid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$ProjectNid),'html' =>TRUE)); 

          $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
          $foldernamegrid =  l($foldericongrid, 'project-share-load-drive/'.$ProjectNid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$ProjectNid),'html' =>TRUE)); 

          if($value->permissions == 'r-w-o'){
            $attr = 'data="'.$Node->title.'" name="m6drive-project-'.$ProjectNid.'" value="'.$ProjectNid.'-folder" class="form-checkbox m6drive-project-checkbox"';
             $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';
          } else if($value->permissions == 'r-o'){
            $attr = 'data-attr="permission_denied" name="m6drive-project-'.$ProjectNid.'" class="form-checkbox" disabled readonly';
            $Dragclass = 'project-drive-folder-dragable';
            $Dropclass = 'project-drive-folder-droppable';

          } else { 
              $attr = 'data-attr="permission_denied" name="m6drive-project-'.$ProjectNid.'" class="form-checkbox" disabled readonly';
          }
          $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($value->shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=>'-','class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('folder',  $ProjectNid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$ProjectNid.'-'.$company->nid.'-row'),
          );
          //For dev str row folder ==========
           $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                  <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
          //End dev str row==========
        }
      }
      if (isset($value->fid) && is_numeric($value->fid) && $value->fid != 0 && $filevalue = file_load($value->fid)) {
        $fid =  $value->fid;
        $projectfid_in_trash = _get_all_projectfid_in_trash_drive($user->uid, $fid);
        if ($fid != $projectfid_in_trash) {
          //$filevalue = file_load($fid);
          $uri = $filevalue->uri;
          $filename =  $filevalue->filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);
          //$Usersdetail = _get_user_mail_realname_by_uid($filevalue->uid);
          //$Usersfullname =  $Usersdetail['realname'];

          $Usersdetail = _get_user_data_by_uid($value->share_by_uid);
          $Usersfullname =  $Usersdetail['realname'];

          $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 

          if($value->permissions == 'r-w-o'){
            $attr = 'data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"';
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else if($value->permissions == 'r-o'){
            $attr = 'data="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly ';
            $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else { 
              $attr = 'data="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly';
              $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
          }


          $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.' ></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($value->shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
          );
          //For dev str row file ==========
             // $img_url = image_style_url('user_image_large', $uri);
              $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
              $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                  <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.' ></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
          //End dev str row file========== 

         }
      }
    }

    // Need to check if any folder is shared withing the projects folder.
    $query = db_select('m6connect_m6drive_shared', 's')
      ->fields('s')
      ->condition('share_to_uid', $user->uid)
      ->condition('services', 'm6drive_project')
      ->condition('root', 1)
      ->orderBy('shared_date', 'DESC'); //ORDER BY created
    $records = $query->execute()->fetchAll();
    if (!empty($records)) {
      foreach ($records as $key => $value) {
        if (isset($value->folder_id)) {
          $parent_folders = m6drive_get_parent_folder($value->folder_id);
          // Getting the nid for this folder.
          foreach($parent_folders as $fldrId => $folderNameVal) {
            if (is_array($folderNameVal)) {
              $keys_arr = array_keys($folderNameVal);
              $projectnid = $keys_arr[0];
              break;
            }
          }
          
          $share_by_uid = $value->share_by_uid;
          $shared_date = $value->shared_date;
          $foldername = get_folder_name_by_folderid($value->folder_id);
          $folderName = $foldername->foldername;

          $Usersdetail = _get_user_data_by_uid($share_by_uid);
          $Usersfullname =  $Usersdetail['realname'];

          $Follengthtrim = (strlen($folderName) > 22) ? substr($folderName, 0, 19).'...' : $folderName;
          $foldericon   = $Drive_folder_icon_image . $Follengthtrim;
          // $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$folderName)).'';

          $foldername =  l($foldericon, 'project-share-load-drive/'.$projectnid.'/'. $value->folder_id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$projectnid),'html' =>TRUE)); 

          $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim;
          $foldernamegrid =  l($foldericongrid, 'project-share-load-drive/'.$projectnid.'/'. $value->folder_id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$projectnid),'html' =>TRUE)); 

          if($value->permissions == 'r-w-o'){
            $attr = 'data="'.$folderName.'" name="m6drive-project-'.$projectnid.'" value="'.$value->folder_id.'-folder" class="form-checkbox m6drive-project-checkbox"';
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else if($value->permissions == 'r-o'){
            $attr = 'data-attr="permission_denied" name="m6drive-project-'.$projectnid.'" class="form-checkbox" disabled readonly';
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else { 
              $attr = 'data-attr="permission_denied" name="m6drive-project-'.$projectnid.'" class="form-checkbox" disabled readonly';
          }



          $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=>'-','class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('folder',  $ProjectNid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$projectnid.'-'.$value->folder_id.'-row'),
          );
           //For dev str row folder ==========
           $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                 <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
          //End dev str row==========
        }
        elseif(isset($value->fid) && $filevalue = file_load($value->fid)) {
          $fid = $value->fid;
         // $filevalue = file_load($value->fid);
          $uri = $filevalue->uri;
          $filename =  $filevalue->filename;
          $filename_str = (strlen($filename) > 22) ? substr($filename, 0, 19).'...' : $filename;
          $filetype = $filevalue->type;
          $filepath = file_create_url($uri);
          //$Usersdetail = _get_user_mail_realname_by_uid($filevalue->uid);
          //$Usersfullname =  $Usersdetail['realname'];

          $share_by_uid = $value->share_by_uid;
          $shared_date = $value->shared_date;

          $Usersdetail = _get_user_data_by_uid($share_by_uid);
          $Usersfullname =  $Usersdetail['realname'];  

          $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename_str, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 
          // if($filelink == 'none'){
          //   $fileName = l($filename, 'javascript:',  array('external' => TRUE));
          // }
          if($value->permissions == 'r-w-o'){
            $attr = 'data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"';
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else if($value->permissions == 'r-o'){
            $attr = 'data="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly ';
            $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
             $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else { 
              $attr = 'data="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly';
              $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
          }
          $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' => '<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.' ></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$fid.'-'.$value->folder_id.'-row'),
          );
           //For dev str row file ==========
              //$img_url = image_style_url('user_image_large', $uri);
             $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
              $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                   <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.' ></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename_str.'</div>
                </div>';
          //End dev str row file========== 
        }
      }
    }
    $projectnid = 0;
  }

  if ($projectnid != 0) {
    if ($folder_id == 0) {
      $query = db_select('m6connect_project_drive_shared', 'pds');
      $query->fields('pds',array('id','share_by_uid','share_to_uid','project_nid','shared_date', 'permissions'));
      $query->condition('pds.share_to_uid', $user->uid);
      $query->condition('pds.project_nid', $projectnid);
      $query->orderBy('pds.shared_date', 'DESC');//ORDER BY created
      $record = $query->execute()->fetchObject();
      $node = node_load($projectnid);
      
      $shared_date =  $record->shared_date;
      $shared_permissions =  $record->permissions;
      $Usersfullname = _get_user_data_by_uid($record->share_by_uid);
  
      if($node->type == 'project'){

        $fieldrfpdocumentArr =_get_all_rfp_nid_using_project_nid_project_drive($node->nid, $only_nids = TRUE);

        $uri =  $node->field_images['und'][0]['uri'];
        $fid =  $node->field_images['und'][0]['fid'];
        $filemime =  $node->field_images['und'][0]['filemime'];
        if (!empty($fid)) {
          $filename = $node->field_images['und'][0]['filename'];
          $filename_str = (strlen($filename) > 22) ? substr($filename, 0, 19).'...' : $filename;
          $filepath = file_create_url($uri);
          $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename_str, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 

          if($shared_permissions == 'r-w-o'){
              $attr = 'data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"';
              $Dragclass = 'project-drive-folder-dragable';
              $Dropclass = 'project-drive-folder-droppable';

          }else if($shared_permissions == 'r-o'){
              $attr = 'data-attr="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly ';
              $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
                $Dragclass = 'project-drive-folder-dragable';
               $Dropclass = 'project-drive-folder-droppable';

          } else{ 
                $attr = 'data-attr="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly';
                $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
          }

          $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $Usersfullname['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
          );
           //For dev str row file ==========
                //$img_url = image_style_url('user_image_large', $uri);
                $fileicondrive = _get_file_icon_m6drive($filemime);
                if($fileicondrive) {
                   $img_url = $fileicondrive;
                }
                else {
                  $img_url = image_style_url('user_image_large', $uri);
                  $img_url = '<img src= '.$img_url.'>';
                }
                $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                      <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>
                         <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                         '.$img_url.' 
                         <div class="clearfix text-blue grid-item-anchor">'.$filename_str.'</div>
                  </div>';
            //End dev str row file========== 
        }
        foreach($fieldrfpdocumentArr as $rfpnids) {
          $node = node_load($rfpnids);
          $Dateproject = _get_share_date_projectnid_using_rfp_nid($rfpnids);
          if ($Dateproject) {
            $shared_date =  $Dateproject->shared_date;
            $shared_permissions =  $Dateproject->permissions;
            $Usersfullname = _get_user_data_by_uid($Dateproject->share_by_uid);
          }
          $comprealusername = '';
          $nodeTitletrim = '';
          //$comprealusername = _get_node_company_user_name($node->nid);
          $comprealusername =_get_user_data_by_uid($node->uid);
          //$foldericon   ='<i class="fa fa-folder padding-5" aria-hidden="true"></i>'.$node->title.'';
          $Follengthtrim = (strlen($node->title) > 22) ? substr($node->title, 0, 19).'...' : $node->title;
          $foldericon   = $Drive_folder_icon_image . $Follengthtrim; 
          if($shared_permissions == 'r-w-o'){
            $attr = 'data="'.$node->title.'" name="m6drive-project-'.$node->nid.'" value="'.$node->nid.'-folder" class="form-checkbox m6drive-project-checkbox"';
             $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';
          } else if($shared_permissions == 'r-o'){
            $attr = 'data-attr="permission_denied" name="m6drive-project-'.$node->nid.'" class="form-checkbox" disabled readonly';
            $Dragclass = 'project-drive-folder-dragable';
            $Dropclass = 'project-drive-folder-droppable';

          } else { 
              $attr = 'data-attr="permission_denied" name="m6drive-project-'.$node->nid.'" class="form-checkbox" disabled readonly';
          }
          $projectname  =  l($foldericon, 'project-share-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' =>TRUE)); 

          $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim; 
          $projectnamegrid  =  l($foldericongrid, 'project-share-load-drive/'.$node->nid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$node->nid),'html' =>TRUE)); 

            $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $projectname, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' =>  $Usersfullname['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=>'-','class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('folder',  $ProjectNid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$node->nid.'-'.$folder_id.'-row'),
          );
           //For dev str row folder ==========
           $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                 <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>
                                <div class="grid-item-anchor clearfix">'.$projectnamegrid.'</div>
                          </div>';
          //End dev str row==========
        
        }
      }
      else{
        $Dateproject = _get_share_date_projectnid_using_rfp_nid($node->nid);
        if ($Dateproject) {
          $shared_date =  $Dateproject->shared_date;
          $shared_permissions =  $Dateproject->permissions;
          $Usersfullname = _get_user_data_by_uid($Dateproject->share_by_uid);
        }
        $fieldrfpdocumentArr = _get_all_rfp_document_images_project_drive($node->nid);

        $uri =  $node->field_rfp_logo['und'][0]['uri'];
        $fid =  $node->field_rfp_logo['und'][0]['fid'];
        $filename = $node->field_rfp_logo['und'][0]['filename'];
        $filemime = $node->field_rfp_logo['und'][0]['filemime'];
        if(!empty($fid)) {
            $filepath = file_create_url($uri);  
            $Attachment = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
             $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 

            if($shared_permissions == 'r-w-o'){
              $attr = 'data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"';
                $Dragclass = 'project-drive-folder-dragable';
               $Dropclass = 'project-drive-folder-droppable';

            } else if($shared_permissions == 'r-o'){
              $attr = 'data="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly ';
              $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
                $Dragclass = 'project-drive-folder-dragable';
               $Dropclass = 'project-drive-folder-droppable';

            } else { 
                $attr = 'data="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly';
                $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
            }

             $rows[] = array(
            'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.' ></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $Usersfullname['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$fid.'-'.$company->nid.'-row'),
            );
             //For dev str row file ==========
             // $img_url = image_style_url('user_image_large', $uri);
              $fileicondrive = _get_file_icon_m6drive($filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
              $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                  <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.' ></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
          //End dev str row file========== 

          
        }
        foreach($fieldrfpdocumentArr as $projectfiles) {
          if(!empty($projectfiles['fid'])) {
            // $ChkFidInArchive =_get_all_projectfid_in_archive_drive($user->uid, $projectfiles['fid']);
            // if($ChkFidInArchive != $projectfiles['fid']){
              $filepath = file_create_url($projectfiles['uri']);

              //$Attachment = l($projectfiles['filename'], $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$projectfiles['fid'])));

              $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($projectfiles['filename'], $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 

              if($shared_permissions == 'r-w-o'){
                $attr = 'data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"';
                  $Dragclass = 'project-drive-folder-dragable';
                 $Dropclass = 'project-drive-folder-droppable';

              }else if($shared_permissions == 'r-o'){
                $attr = 'data="permission_denied" name="m6drive-project-'.$projectfiles['fid'].'" class="form-checkbox  permission_deniedshare" disabled readonly ';
                $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($projectfiles['filename'], 'javascript:',  array('external' => TRUE));
                 $Dragclass = 'project-drive-folder-dragable';
                 $Dropclass = 'project-drive-folder-droppable';

              }else { 
                  $attr = 'data="permission_denied" name="m6drive-project-'.$projectfiles['fid'].'" class="form-checkbox  permission_deniedshare" disabled readonly';
                  $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($projectfiles['filename'], 'javascript:',  array('external' => TRUE));
              }
              
              $rows[] = array(
              'data' => array(
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' =>'','class' => array('col-md-1','text-left','hidden')),
              array('data' => '<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.' ></div>', 'class'=> array('col-md-1','text-center','hidden')),
              array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
              array('data' => $Usersfullname['realname'],'class' => array('col-md-2','text-left')),
              array('data' => date('F d, Y', strtotime($shared_date)),'class' => array('col-md-2','text-left')),
              array('data'=> _get_m6drive_project_filesize_by_fid($projectfiles['fid']),'class'=>array('col-md-3','text-left')),
              //array('data' => project_drive_share_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
             ),  
            'class' => array('custom-odd','customsearchformydrive','m6drive-folderdelete-'.$projectfiles['fid'].'-'.$folder_id.'-row'),
          );
              //For dev str row file ==========
             $fileicondrive = _get_file_icon_m6drive($projectfiles['filemime']);
             if ($fileicondrive) {
                $img_url = $fileicondrive;
             }
             else {
                $img_url = image_style_url('user_image_large', $projectfiles['uri']);
                $img_url = '<img src = ' . $img_url . '>';
             }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                   <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.' ></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$projectfiles['filename'].'</div>
                </div>';
             //End dev str row file==========
            // }
          }
        }
      }
    }

    if ($folder_id == 0) {
      $folder_id = $projectnid;
    }

    $query = db_select('m6connect_m6drive', 'm6d');
    $query->fields('m6d',array('Id','parent_id','company_nid','user_uid','foldername','created_date'));
    $query->condition('m6d.parent_id', $folder_id);
    $query->orderBy('m6d.created_date', 'DESC');//ORDER BY created
    $record = $query->execute()->fetchAll();
    $querysub = db_select('m6connect_m6drive_attachment','att');
    $querysub->fields('att',array('user_uid','file','created_date'));
    $querysub->condition('att.folder_id', $folder_id);
    $querysub->orderBy('att.created_date', 'DESC');//ORDER BY created
    $recordsub = $querysub->execute()->fetchAll();
    $complteresult = array_merge($record, $recordsub);
    foreach ($complteresult as $value) {
      if (isset($value->foldername) && _check_folder_eligibility_share($value->Id)) {
        $share_by_uid = db_select('m6connect_m6drive_shared', 's')
          ->fields('s', array('share_by_uid', 'shared_date','permissions'))
          ->condition('folder_id', $value->Id)
          ->condition('share_to_uid', $user->uid)
          ->range(0, 1)
          ->execute()
          ->fetchAssoc();

        if ($share_by_uid['share_by_uid'] == 0) {
          $share_by_uid['share_by_uid'] = $value->user_uid;
        }

        $Usersdetail = _get_user_data_by_uid($share_by_uid['share_by_uid']);
        $Usersfullname =  $Usersdetail['realname'];

        $Follengthtrim = (strlen($value->foldername) > 22) ? substr(str_replace('_', ' ', $value->foldername), 0, 19).'...' : str_replace('_', ' ', $value->foldername);
        $foldericon   = $Drive_folder_icon_image . $Follengthtrim; 
        $foldername =  l($foldericon, 'project-share-load-drive/'.$projectnid.'/'. $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$projectnid),'html' =>TRUE));

        $foldericongrid   = $Grid_folder_icon_image . $Follengthtrim; 
        $foldernamegrid =  l($foldericongrid, 'project-share-load-drive/'.$projectnid.'/'. $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$projectnid),'html' =>TRUE));  


        if($share_by_uid['permissions'] == 'r-w-o'){
            $attr = 'data="'.$value->foldername.'" name="m6drive-project-'.$projectnid.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"';
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else if($share_by_uid['permissions'] == 'r-o'){
            $attr = 'data-attr="permission_denied" name="m6drive-project-'.$projectnid.'" class="form-checkbox  permission_deniedshare" disabled readonly ';
             $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

            
          } else { 
              $attr = 'data-attr="permission_denied" name="m6drive-project-'.$projectnid.'" class="form-checkbox  permission_deniedshare" disabled readonly';
           
          }

        $rows[] = array(
          'data' => array(
            array('data'=>'<span class="folder-ids" style="display:none;">'.$value->Id.'-folder</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
             array('data'=>'<span class="project-drive-nids" style="display:none;">'.$projectnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','m6drive-drag-content-show','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($share_by_uid['shared_date'])),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_share_action_btn('folder',  $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),
          'id' => array(''.$value->Id.''),   
          'class' => array('custom-odd', $Dragclass, $Dropclass, 'customsearchformydrive','m6drive-folderdelete-'.$projectnid.'-'.$value->Id.'-row'),
        );
         //For dev str row folder ==========
           $divprojectstrfol .= '<div id="' . $value->Id . '"class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10 ' . $Dragclass . ' ' . $Dropclass . '">
                              <div class="m6drive-display-none-drag"><span class="folder-ids" style="display:none;">'.$value->Id.'-folder</span></div>
                              <div class="m6drive-display-none-drag"><span class="project-drive-nids" style="display:none;">'.$projectnid.'</span></div>
                                <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>
                                <div class="grid-item-anchor clearfix m6drive-drag-content-show">'.$foldernamegrid.'</div>
                          </div>';
          //End dev str row==========
      }
      elseif(isset($value->file) && _check_file_eligibility_share($value->file) && $filevalue = file_load($value->file)) {
        $fid = $value->file;
        //$filevalue = file_load($value->file);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filename_str = (strlen($filename) > 22) ? substr($filename, 0, 19).'...' : $filename;

        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        //$Usersdetail = _get_user_mail_realname_by_uid($filevalue->uid);
        //$Usersfullname =  $Usersdetail['realname'];

        $share_by_uid = db_select('m6connect_m6drive_shared', 's')
          ->fields('s', array('share_by_uid', 'shared_date', 'permissions'))
          ->condition('fid', $value->file)
          ->condition('share_to_uid', $user->uid)
          ->range(0, 1)
          ->execute()
          ->fetchAssoc();

        if ($share_by_uid['share_by_uid'] == 0) {
          $share_by_uid['share_by_uid'] = $value->user_uid;
        }

        $Usersdetail = _get_user_data_by_uid($share_by_uid['share_by_uid']);
        $Usersfullname =  $Usersdetail['realname'];  

        $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename_str, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 
        if($share_by_uid['permissions'] == 'r-w-o'){
            $attr = 'data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"';
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';

          } else if($share_by_uid['permissions'] == 'r-o'){
            $attr = 'data-attr="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly ';
            $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
              $Dragclass = 'project-drive-folder-dragable';
             $Dropclass = 'project-drive-folder-droppable';
             
          } else { 
              $attr = 'data-attr="permission_denied" name="m6drive-project-'.$fid.'" class="form-checkbox  permission_deniedshare" disabled readonly';
              $fileName = '<span class="orignal-img" style="display:none;">'.$filepath.'</span>'.l($filename, 'javascript:',  array('external' => TRUE));
          }
        $rows[] = array(
          'data' => array(
            array('data'=>'<span class="folder-ids" style="display:none;">'.$fid.'-file</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
             array('data'=>'<span class="project-drive-nids" style="display:none;">'.$projectnid.'</span>', 'class'=> array('m6drive-display-none-drag','hidden')),
            array('data' => '<div class="form-item form-type-checkbox"><input type="checkbox" '.$attr.'></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','m6drive-drag-content-show','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($share_by_uid['shared_date'])),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_share_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive', $Dragclass,'m6drive-folderdelete-'.$fid.'-'.$value->folder_id.'-row'),
        );
         //For dev str row file ==========
         //$img_url = image_style_url('user_image_large', $uri);
          $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
          if($fileicondrive) {
             $img_url = $fileicondrive;
          }
          else {
            $img_url = image_style_url('user_image_large', $uri);
            $img_url = '<img src= '.$img_url.'>';
          }
         $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10 ' . $Dragclass . '">
                      <div class="m6drive-display-none-drag"><span class="folder-ids" style="display:none;">'.$fid.'-file</span></div>
                      <div class="m6drive-display-none-drag"><span class="project-drive-nids" style="display:none;">'.$projectnid.'</span></div>
                      <div class="form-item form-type-checkbox hidden"><input type="checkbox" '.$attr.'></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor m6drive-drag-content-show">'.$filename_str.'</div>
                </div>';
         //End dev str row file==========
      }
    }
  }
   $return .= '<div class="list-view" style="'.$list_display.'">';
   $return .= theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-project-drive','table-striped','table-hover','table-bordered','text-center'))));
   $return .= '</div>';
  // End here fir table List view structure========

   // start here for Grid  view structure========
   $return .= '<div class="grid-view" style="'.$grid_display.'">';
   $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
   $return .= '<div class="grid-view-folders row margin-5">';
  // First handling only Folders.
   if(empty($divprojectstrfol)){
   $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
   }
   $return .= $divprojectstrfol; 
   $return .= '</div>'; //end grid-view-folders
  // Then handling only Files.
   $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
   $return .= '<div class="grid-view-files row margin-5">';
   if(empty($divprojectstrfile)){
   $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
   }
   $return .= $divprojectstrfile; 
   $return .= '</div>'; // end grid-view-files.
   $return .= '</div>'; // end grid-view.
  // End here for Grid  view structure========

   return $return;
}

/**
 * Function to generate form for for archive folder in project drive.
 */
function project_drive_archive_folder_form($form, &$form_state){
  $form['multiple_projectnid'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-project-drive-perform')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>',
  );
   $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-archive"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to archive: <span class="multiple-project-folders-show"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('project_drive_archive_folder_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );  

  return $form; 
}

/**
 * Submit handler for project_drive_archive_folder_form
 */
function project_drive_archive_folder_submit($form, &$form_state){
  global $user;
  global $company;
  $values = $form_state['values']; 
  $projectMultiple = $values['multiple_projectnid'];


  $projectfolder =  explode(',' ,$projectMultiple);
  if (!empty($projectfolder)) {
    foreach($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        // There are no files on root folder of project drive.
        // Only projects are present. So we check only here, if the folder is
        // project folder or inner folder.
        $projectnidMul = $getStatus[0];
        if (!empty($projectnidMul)) {
          // We need to check if the archive request is for a folder that has
          // been added to my drive by another user.
          // If so, then removing entry from the add to mydrive table.
          db_delete('m6connect_m6drive_addto_mydrive')
            ->condition('services', 'm6drive_project')
            ->condition('user_uid', $user->uid)
            ->condition('folder_id', $projectnidMul)
            ->execute();

          // Handling this folder's children, if present.
          _archive_folder_and_file_project($projectnidMul);

          // Acting on the current folder.
          $query = db_select('m6connect_m6drive', 'm')
            ->fields('m')
            ->condition('Id', $projectnidMul)
            ->condition('services', 'm6drive_project')
            ->condition('company_nid', $company->nid)
            ->condition('user_uid', $user->uid)
            ->execute()
            ->rowCount();
          if ($query > 0) {
            // This is the case when the folder is inner folder.
            // In this case, just updating the archive status in table.
            db_update('m6connect_m6drive')
              ->fields(array(
                'archive_status' => 1,
                'root' => 1,
              ))
              ->condition('Id', $projectnidMul)
              ->execute();
          }
          else {
            // Here we need to confirm that the request is by the owner himself
            // and not any other user with whom this project is shared.
            $query = db_select('m6connect_m6drive_addto_mydrive', 'm')
              ->fields('m')
              ->condition('user_uid', $user->uid)
              ->condition('folder_id', $projectnidMul)
              ->execute()
              ->rowCount();
            if ($query == 0) {
              // Processing further if eligible.
              // First deleting the archive entry. Although it would be already
              // deleted.
              db_delete('m6connect_project_drive_archive')
                ->condition('user_uid', $user_uid)
                ->condition('project_nid', $projectnidMul)
                ->condition('services', 'm6drive_project')
                ->execute();

              // Inserting a new record in table.
              db_insert('m6connect_project_drive_archive')
                ->fields(array(
                   'user_uid'=> $user->uid,
                   'project_nid' => $projectnidMul,
                   'fid' => 0, 
                   'archive_status' => 1,
                   'services' => 'm6drive_project',
                ))
                ->execute();
            }
          }
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        if (!empty($fileIdMul)) {
          // We need to check if the archive request is for a file that has
          // been added to my drive by another user.
          // If so, then removing entry from the add to mydrive table.
          db_delete('m6connect_m6drive_addto_mydrive')
            ->condition('services', 'm6drive_project')
            ->condition('user_uid', $user->uid)
            ->condition('file', $fileIdMul)
            ->execute();

          // As file can not be present in root folder, so we are sure that the
          // file is in inner folder, and hence present in attachment table.
          // So changing archive status there.
          db_update('m6connect_m6drive_attachment')
            ->fields(array(
              'archive_status' => 1,
              'root' => 1,
            ))
            ->condition('file', $fileIdMul)
            ->condition('user_uid', $user->uid)
            ->execute();
        }
      }
    }
  }
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
        $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
        $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/project/drive'); 
        
  }
}

/**
 * Form for trashing project drive.
 */
function project_drive_trash_folder_form($form, &$form_state) {
  $form['multiple_projectnid'] = array(
      '#type' => 'textarea',
      '#attributes'=> array('class'=> array('multiple-project-drive-perform')),
      '#prefix' => '<div style="display:none;">',
      '#suffix' => '</div>'
  );
   $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-archive"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to delete: <span class="multiple-project-folders-show"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('project_drive_trash_folder_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );

  return $form;
}

/**
 * Submit handler for project_drive_trash_folder_form().
 */
function project_drive_trash_folder_submit($form, &$form_state) {
  global $user;
  global $company;
  $values = $form_state['values']; 
  $projectMultiple = $values['multiple_projectnid'];

  $projectfolder =  explode(',' ,$projectMultiple);

  if (!empty($projectfolder)) {
    foreach($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        // There are no files on root folder of project drive.
        // Only projects are present. So we check only here, if the folder is
        // project folder or inner folder.
        $projectnidMul = $getStatus[0];
        if (!empty($projectnidMul)) {
          // We need to check if the trash request is for a folder that has
          // been added to my drive by another user.
          // If so, then removing entry from the add to mydrive table.
          db_delete('m6connect_m6drive_addto_mydrive')
            ->condition('services', 'm6drive_project')
            ->condition('user_uid', $user->uid)
            ->condition('folder_id', $projectnidMul)
            ->execute();

          // Handling this folder's children, if present.
          _trash_folder_and_file_project($projectnidMul);

          // Acting on the current folder.
          $query = db_select('m6connect_m6drive', 'm')
            ->fields('m')
            ->condition('Id', $projectnidMul)
            ->condition('services', 'm6drive_project')
            ->condition('company_nid', $company->nid)
            ->condition('user_uid', $user->uid)
            ->execute()
            ->rowCount();

          if ($query > 0) {
            // This is the case when the folder is inner folder.
            // In this case, just updating the archive status in table.
            db_update('m6connect_m6drive')
              ->fields(array(
                'trash_status' => 1,
                'root' => 1,
              ))
              ->condition('Id', $projectnidMul)
              ->execute();
          }
          else {
            // Here we need to confirm that the request is by the owner himself
            // and not any other user with whom this project is shared.
            $query = db_select('m6connect_m6drive_addto_mydrive', 'm')
              ->fields('m')
              ->condition('user_uid', $user->uid)
              ->condition('folder_id', $projectnidMul)
              ->execute()
              ->rowCount();
            if ($query == 0) {
              // Processing further if eligible.
              // First deleting the trash entry. Although it would be already
              // deleted.
              db_delete('m6connect_project_drive_trash')
                ->condition('user_uid', $user_uid)
                ->condition('project_nid', $projectnidMul)
                ->condition('services', 'm6drive_project')
                ->execute();

              // Inserting a new record in table.
              db_insert('m6connect_project_drive_trash')
                ->fields(array(
                   'user_uid'=> $user->uid,
                   'project_nid' => $projectnidMul,
                   'fid' => 0, 
                   'trash_status' => 1,
                   'services' => 'm6drive_project',
                ))
                ->execute();
            }
          }
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        if (!empty($fileIdMul)) {
          // We need to check if the archive request is for a file that has
          // been added to my drive by another user.
          // If so, then removing entry from the add to mydrive table.
          db_delete('m6connect_m6drive_addto_mydrive')
            ->condition('services', 'm6drive_project')
            ->condition('user_uid', $user->uid)
            ->condition('file', $fileIdMul)
            ->execute();

          // As file can not be present in root folder, so we are sure that the
          // file is in inner folder, and hence present in attachment table.
          // So changing archive status there.
          db_update('m6connect_m6drive_attachment')
            ->fields(array(
              'trash_status' => 1,
              'root' => 1,
            ))
            ->condition('file', $fileIdMul)
            ->condition('user_uid', $user->uid)
            ->execute();
        }
      }
    }
  }

  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] = ctools_ajax_command_redirect('/project/drive');
  }
}

/**
 * Function to generate breadcrumbs for project archive drive.
 */
function project_drive_archive_breadcrumb($projectnid = 0, $folder_id = 0) {
  global $user, $company;
  if($projectnid == 0) {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
                      <li><a class="use-ajax" href="/project-archive-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
                      </ul></div>';
  }
  else {
   $node = node_load($projectnid);
   if ($folder_id == 0) {
     $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/project-archive-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
     $breadcrumbVal .= '<li><a class="use-ajax" href="/project-archive-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'.$node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
   }
   else {
     $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/project-archive-load-drive/0/0/nojs">Project Drive</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
     // $breadcrumbVal .= '<li><a class="use-ajax" href="/project-load-drive/' . $projectnid . '/0/nojs">'.$node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
     $query = db_select('m6connect_m6drive', 'm6d');
     $query->fields('m6d',array('foldername'));
     $query->condition('m6d.user_uid', $user->uid);
     $query->condition('m6d.company_nid', $company->nid); 
     $query->condition('m6d.Id', $folder_id);
     $query->condition('m6d.services', 'm6drive_project');
     $Currentfolder = $query->execute()->fetchField();

     $output = m6drive_get_parent_folder($folder_id);
     foreach($output as $fldrId => $folderNameVal) {
       foreach($folderNameVal as $foldKey => $fldVal) {
        $get_key = $foldKey;
        if (is_array($fldVal)) {
          $foldKey = 0;
          $fldVal = $fldVal[0];
        }
        if (_check_folder_eligibility_archive_trash($get_key, 'archive')) {
          $breadcrumbVal .= '<li><a class="use-ajax" href="/project-archive-load-drive/' . $projectnid. '/' . $foldKey . '/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
        }
       }
     }
     $breadcrumbVal .= '<li><a class="use-ajax" href="/project-archive-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'. str_replace('_',' ',$Currentfolder) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
   }
    
   $breadcrumbVal .= '</ul></div>';
  }
   return $breadcrumbVal;  
}

/**
 * Function to generate content for project drive archive.
 */
function m6drive_project_drive_archive_listing_content($projectnid = 0, $folder_id = 0) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css');

  global $company, $user, $base_url;  
  $header = array(
  array('data'=>'<input type="checkbox" name="select-m6drive-project-checkbox" class="form-checkbox select-m6drive-project-checkbox">', 'class'=> array('col-md-1','text-center','hidden','no-sort')),
  array('data'=>'Name  &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('company_project_archive_m6drive_filter_form',$projectnid, $folder_id)).'</div>','class'=>array('col-md-4','text-left','drive_filter_header')),
  array('data'=>'Owner','class'=>array('col-md-2','text-left')),
  array('data'=>'Last Modified','class'=>array('col-md-2','text-left')),
  array('data'=>'File Size','class'=>array('col-md-3','text-left')),
  //array('data'=>'Action', 'class'=>array('col-md-2','text-left')), 
  );
  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';
  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';
  // Creating div structure.
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }
 
  if ($projectnid == 0 && $folder_id == 0) {
    // This is the case, when we are on the root folder.
    $query = db_select('m6connect_project_drive_archive', 'pda');
    $query->fields('pda',array('id','user_uid','project_nid','fid','archive_status'));
    $query->condition('pda.user_uid', $user->uid);
    $query->condition('pda.archive_status', 1,'=');
    $record = $query->execute()->fetchAll();
    foreach($record as $key => $value) {
      if (isset($value->project_nid) && is_numeric($value->project_nid) && $value->project_nid != 0 && _check_folder_eligibility_archive_trash($value->project_nid, 'archive')) {
        $ProjectNid = $value->project_nid;
        $Node = node_load($ProjectNid); 
        //$Usersdetail = _get_node_company_user_name($Node->nid);
        //$Usersfullname =  $Usersdetail['user_name'];
        $Userdetail = _get_user_data_by_uid($Node->uid);
        $Usersfullname = $Userdetail['realname'];

        $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$Node->title)).'';
        $foldername =  l($foldericon, 'project-archive-load-drive/'.$ProjectNid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$ProjectNid),'html' =>TRUE));

        $foldericongrid   = $Grid_folder_icon_image . ucwords(str_replace('_',' ',$Node->title)).'';
        $foldernamegrid =  l($foldericongrid, 'project-archive-load-drive/'.$ProjectNid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$ProjectNid),'html' =>TRUE));

        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$Node->title.'" name="m6drive-project-'.$ProjectNid.'" value="'.$ProjectNid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', $Node->created),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' =>  project_drive_archive_action_btn('folder', $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$ProjectNid.'-'.$company->nid.'-row'),
        );
         //For dev str row folder ==========
          $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                               <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$Node->title.'" name="m6drive-project-'.$ProjectNid.'" value="'.$ProjectNid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'. $foldernamegrid.'</div>
                          </div>';
        //End dev str row==========
      }
      if (isset($value->fid) && is_numeric($value->fid) && $value->fid != 0 && _check_file_eligibility_archive_trash($value->fid, 'archive')  && $filevalue = file_load($value->fid)) {
        $fid =  $value->fid;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);
        //$Usersdetail = _get_node_company_user_name($filevalue->uid);
        //$Usersdetail = _get_user_mail_realname_by_uid($filevalue->uid);
        //$Usersfullname =  $Usersdetail['realname'];
        $Usersdetail = _get_user_data_by_uid($filevalue->uid);
        $Usersfullname =  $Usersdetail['realname'];


        $nodecreated = $filevalue->timestamp;
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 
        $rows[] = array(
          'data' => array(
             array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', $nodecreated),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_archive_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$fid.'-'.$company->nid.'-row'),
        );
        //For dev str row file ==========
             //$img_url = image_style_url('user_image_large',  $uri);
            $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
            if($fileicondrive) {
               $img_url = $fileicondrive;
            }
            else {
              $img_url = image_style_url('user_image_large', $uri);
              $img_url = '<img src= '.$img_url.'>';
            }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                   <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
             //End dev str row file==========
      }
    }

    // If we are browsing the root, then need to check if any subfolder from
    // a project folder was archived. Meaning only a subfolder from a project
    // folder was archived and not the whole project folder.
    $drive_query = db_select('m6connect_m6drive', 'm')
      ->fields('m')
      ->condition('services', 'm6drive_project')
      ->condition('company_nid', $company->nid)
      ->condition('user_uid', $user->uid)
      ->condition('root', 1)
      ->condition('archive_status', 1)
      ->orderBy('created_date', 'DESC'); //ORDER BY created
    $record = $drive_query->execute()->fetchAll();
    $querysub = db_select('m6connect_m6drive_attachment','m');
    $querysub->fields('m',array('file','created_date','trash_status'));
    $querysub->condition('m.user_uid', $user->uid);
    $querysub->condition('m.services', 'm6drive_project');
    $querysub->condition('m.company_nid', $company->nid);
    $querysub->condition('m.archive_status', 1);
    $querysub->condition('m.root', 1);
    $querysub->orderBy('m.created_date', 'DESC');//ORDER BY created
    $recordsub = $querysub->execute()->fetchAll();
    $complteresult = array_merge($record, $recordsub);

    $UserFnameLname =_get_user_data_by_uid($user->uid);
    $Usersfullname = $UserFnameLname['realname'];

    foreach ($complteresult as $value) {
      if (isset($value->foldername) && _check_folder_eligibility_archive_trash($value->Id, 'archive')) {
        // When the very first folder is browsed, then the projectnid or folder_id
        // are 0. But when we are browsing a sub folder in the root of archive,
        // we need a projectnid. So trying to get projectnid here.
        $output = m6drive_get_parent_folder($value->Id);
        foreach($output as $fldrId => $folderNameVal) {
          foreach($folderNameVal as $foldKey => $fldVal) {
            if (is_array($fldVal)) {
              $projectnid = $foldKey;
            }
          }
        }
        $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldername =  l($foldericon, 'project-archive-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE)); 

        $foldericongrid   = $Grid_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldernamegrid =  l($foldericongrid, 'project-archive-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE)); 

        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' =>  project_drive_archive_action_btn('folder', $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$value->Id.'-'.$company->nid.'-row'),
        );
        //For dev str row folder ==========
          $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
        //End dev str row==========
      }
      if (isset($value->file) && _check_file_eligibility_archive_trash($value->file, 'archive') && $filevalue = file_load($value->file)) {
        $fid =  $value->file;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);  
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
        $rows[] = array(
          'data' => array(
             array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_archive_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$fid.'-'.$company->nid.'-row'),
        );
        //For dev str row file ==========
             //$img_url = image_style_url('user_image_large',  $uri);
              $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                    <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
             //End dev str row file==========
      }
    }
    // Setting back the projectnid to 0, else the below query would be treated
    // true.
    $projectnid = 0;
  }

  if ($projectnid != 0) {
    // This is the case when we are browsing the project folder in the archive
    // directory.
    if ($folder_id == 0) {
      // As the project node files do not have any entry in the attachment table,
      // only project folder is archived. Project files are not archived, because
      // if a folder is archived, it is not visible in the projects directory.
      // So, here we dynamically get these files.
      $node = node_load($projectnid);
      $Userdetail = _get_user_data_by_uid($node->uid);
      $Usersfullname = $Userdetail['realname'];

      $fid =  $node->field_images['und'][0]['fid'];
      if(!empty($fid)) {
        $uri =  $node->field_images['und'][0]['uri'];
        $filename = $node->field_images['und'][0]['filename'];
        $filemime = $node->field_images['und'][0]['filemime'];
        $filepath = file_create_url($uri);
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 
        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
             array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_archive_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$fid.'-'.$company->nid.'-row'),
        );
         //For dev str row file ==========
              //$img_url = image_style_url('user_image_large',  $uri);
              $fileicondrive = _get_file_icon_m6drive($filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                     <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
             //End dev str row file==========
      }
      $fieldrfpdocumentArr =_get_all_rfp_nid_using_project_nid_project_drive($projectnid);
      foreach($fieldrfpdocumentArr as $projectfiles) {
        if (!empty($projectfiles['fid'])) {
          $ChkFidInArchive =_get_all_projectfid_in_archive_drive($user->uid, $projectfiles['fid']);
          if ($ChkFidInArchive != $projectfiles['fid']) {
            $filepath = file_create_url($projectfiles['uri']);  
            $Attachment = l($projectfiles['filename'], $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$projectfiles['fid']))); 
            $rows[] = array(
              'data' => array(
                array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                array('data'=> $Attachment, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
                array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                array('data'=> _get_m6drive_project_filesize_by_fid($projectfiles['fid']),'class'=>array('col-md-3','text-left')),
                //array('data' => project_drive_archive_action_btn('file', $projectfiles['fid']),'class' => array('col-md-2','text-left')), 
                ),  
              'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$projectfiles['fid'].'-'.$company->nid.'-row'),
            );
             //For dev str row file ==========
              //$img_url = image_style_url('user_image_large', $projectfiles['uri']);
              $fileicondrive = _get_file_icon_m6drive($projectfiles['filemime']);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $projectfiles['uri']);
                $img_url = '<img src= '.$img_url.'>';
              }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                     <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$projectfiles['filename'].'</div>
                </div>';
             //End dev str row file==========
          }
        }
      }
    }

    // After we have fetched files for project folder from nodes, we need the
    // folders in the project folder, or sub folders.
    if ($folder_id == 0) {
      $folder_id = $projectnid;
    }

    $drive_query = db_select('m6connect_m6drive', 'm')
      ->fields('m')
      ->condition('services', 'm6drive_project')
      ->condition('company_nid', $company->nid)
      ->condition('user_uid', $user->uid)
      ->condition('parent_id', $folder_id)
      ->condition('archive_status', 1)
      ->orderBy('created_date', 'DESC');  //ORDER BY created
    $record = $drive_query->execute()->fetchAll();
    $querysub = db_select('m6connect_m6drive_attachment','m');    
    $querysub->fields('m',array('file','created_date','archive_status'));
    $querysub->condition('m.user_uid', $user->uid);
    $querysub->condition('m.services', 'm6drive_project');
    $querysub->condition('m.company_nid', $company->nid);
    $querysub->condition('m.folder_id', $folder_id);
    $querysub->condition('m.archive_status', 1);
    $querysub->orderBy('m.created_date', 'DESC'); //ORDER BY created
    $recordsub = $querysub->execute()->fetchAll();
    $complteresult = array_merge($record, $recordsub);

    $UserFnameLname =_get_user_data_by_uid($user->uid);
    $Usersfullname = $UserFnameLname['realname'];

    foreach ($complteresult as $value) {
      if (isset($value->foldername) && _check_folder_eligibility_archive_trash($value->Id, 'archive')) {
        $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldername =  l($foldericon, 'project-archive-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE)); 

        $foldericongrid   = $Grid_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldernamegrid =  l($foldericongrid, 'project-archive-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE)); 


        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' =>  project_drive_archive_action_btn('folder', $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$value->Id.'-'.$company->nid.'-row'),
        );
          //For dev str row folder ==========
          $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                  <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
        //End dev str row==========
      }
      if (isset($value->file) && _check_file_eligibility_archive_trash($value->file, 'archive')  && $filevalue = file_load($value->file)) {
        $fid =  $value->file;
       //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);  
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
        $rows[] = array(
          'data' => array(
             array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_archive_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','m6drive-project-archive-'.$fid.'-'.$company->nid.'-row'),
        );
      //For dev str row file ==========
      $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
      if($fileicondrive) {
         $img_url = $fileicondrive;
      }
      else {
        $img_url = image_style_url('user_image_large', $uri);
        $img_url = '<img src= '.$img_url.'>';
      }
      $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                      <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
      //End dev str row file==========
      }
    }
  }
  $return .= '<div class="list-view" style="'.$list_display.'">';
  $return .=theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-project-drive','table-striped','table-hover','table-bordered','text-center'))));
  $return .= '</div>';
  // End here fir table List view structure========
   // start here for Grid  view structure========
   $return .= '<div class="grid-view" style="'.$grid_display.'">';
   $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
   $return .= '<div class="grid-view-folders row margin-5">';
  // First handling only Folders.
   if(empty($divprojectstrfol)){
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
   }
   $return .= $divprojectstrfol; 
   $return .= '</div>'; //end grid-view-folders
  // Then handling only Files.
   $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
   $return .= '<div class="grid-view-files row margin-5">';
   if(empty($divprojectstrfile)){
    $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
   }
   $return .= $divprojectstrfile; 
   $return .= '</div>'; // end grid-view-files.
   $return .= '</div>'; // end grid-view.
  // End here for Grid  view structure========

  return $return;
}

/**
 * Function to generate form for unarchive project folder.
 */
function project_drive_unarchive_folder_form($form, &$form_state) {
  $form['multiple_projectnid'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-project-drive-perform')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
   $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-archive"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to unarchive: <span class="multiple-project-folders-show"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('project_drive_unarchive_folder_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );

  return $form; 
}

/**
 * Submit handler for project_drive_unarchive_folder_form
 */
function project_drive_unarchive_folder_submit($form, &$form_state) {
  global $user;
  global $company;
  $values = $form_state['values']; 
  $projectMultiple = $values['multiple_projectnid'];
  $projectfolder =  explode(',' ,$projectMultiple);
  if (!empty($projectfolder)) {
    foreach($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        // There are no files on root folder of project drive.
        // Only projects are present. So we check only here, if the folder is
        // project folder or inner folder.
        $projectnidMul = $getStatus[0];
        if (!empty($projectnidMul)) {
          // First handling this folder's children, if present.
          _unarchive_folder_and_file_project($projectnidMul);

          // Acting on the current folder.
          $query = db_select('m6connect_m6drive', 'm')
            ->fields('m')
            ->condition('Id', $projectnidMul)
            ->condition('services', 'm6drive_project')
            ->condition('company_nid', $company->nid)
            ->condition('user_uid', $user->uid)
            ->execute()
            ->rowCount();
          if ($query > 0) {
            // This is the case when the folder is inner folder.
            // In this case, just updating the archive status in table.
            db_update('m6connect_m6drive')
              ->fields(array(
                'archive_status' => 0,
                'root' => 0,
              ))
              ->condition('Id', $projectnidMul)
              ->execute();
          }
          else {
            // Deleting the archive entry.
            db_delete('m6connect_project_drive_archive')
              ->condition('user_uid', $user->uid)
              ->condition('project_nid', $projectnidMul)
              ->condition('services', 'm6drive_project')
              ->execute();
          }
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        if (!empty($fileIdMul)) {
          // As file can not be present in root folder, so we are sure that the
          // file is in inner folder, and hence present in attachment table.
          // So changing archive status there.
          db_update('m6connect_m6drive_attachment')
            ->fields(array(
              'archive_status' => 0,
              'root' => 0,
            ))
            ->condition('file', $fileIdMul)
            ->execute();
        }
      }
    }
  }

  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
        $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
        $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/project/archive-drive'); 
  }
}

/**
 * Helper function to get breadcrumb for project trash drive.
 */
function project_drive_trash_breadcrumb($projectnid = 0, $folder_id = 0) {
  global $user, $company;
  if($projectnid == 0) {
    $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb">
                       <li><a class="use-ajax" href="/project-trash-load-drive/0/0/nojs">Project Trash</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>
                       </ul></div>';
  }
  else {
    $node = node_load($projectnid);
    if ($folder_id == 0) {
      $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/project-trash-load-drive/0/0/nojs">Project Trash</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
      $breadcrumbVal .= '<li><a class="use-ajax" href="/project-trash-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'.$node->title.'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
    }
    else {
      $breadcrumbVal = '<div class="search-folder-breadcrumb-custom"><ul id="bc1" class="breadcrumb"><li><a class="use-ajax" href="/project-trash-load-drive/0/0/nojs">Project Trash</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';

        $query = db_select('m6connect_m6drive', 'm6d');
        $query->fields('m6d',array('foldername'));
        $query->condition('m6d.user_uid', $user->uid);
        $query->condition('m6d.company_nid', $company->nid); 
        $query->condition('m6d.Id', $folder_id);
        $query->condition('m6d.services', 'm6drive_project');
        $Currentfolder = $query->execute()->fetchField();

        $output = m6drive_get_parent_folder($folder_id);
        foreach($output as $fldrId => $folderNameVal) {
          foreach($folderNameVal as $foldKey => $fldVal) {
           $get_key = $foldKey;
           if (is_array($fldVal)) {
             $foldKey = 0;
             $fldVal = $fldVal[0];
           }
           if (_check_folder_eligibility_archive_trash($get_key, 'trash')) {
             $breadcrumbVal .= '<li><a class="use-ajax" href="/project-trash-load-drive/' . $projectnid. '/' . $foldKey . '/nojs">'.ucwords(str_replace('_',' ',$fldVal)).'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
           }
          }
        }
        $breadcrumbVal .= '<li><a class="use-ajax" href="/project-trash-load-drive/' . $projectnid . '/' . $folder_id . '/nojs">'. str_replace('_',' ',$Currentfolder) .'</a>&nbsp;<i class="fa fa-caret-right" aria-hidden="true"></i></li>';
      }
      $breadcrumbVal .= '</ul></div>';
    }
  return $breadcrumbVal;
}

/**
 * Helper function to get content for project trash drive.
 */
function m6drive_project_drive_trash_listing_content($projectnid = 0, $folder_id = 0) {
  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');
  drupal_add_js(drupal_get_path('theme', 'm6connect') . '/js/jquery.dataTables.min.js');
  drupal_add_css(drupal_get_path('theme', 'm6connect') . '/css/jquery.dataTables.min.css'); 

  global $company, $user, $base_url;  
  $header = array(
  array('data'=>'<input type="checkbox" name="select-m6drive-project-checkbox" class="form-checkbox select-m6drive-project-checkbox">', 'class'=> array('col-md-1','text-center','hidden','no-sort')),
  array('data'=>'Name &nbsp;<i id="drive_filter_sort" class="fa fa-caret-down filter-sort" aria-hidden="true"></i> <div class="m6drive_filter_sort_form m6drive_filter_sort" style="display:none;">'.render(drupal_get_form('company_project_trash_m6drive_filter_form',$projectnid, $folder_id)).'</div>','class'=>array('col-md-4','text-left','drive_filter_header')),
  array('data'=>'Owner','class'=>array('col-md-2','text-left')),
  array('data'=>'Last Modified','class'=>array('col-md-2','text-left')),
  array('data'=>'File Size','class'=>array('col-md-3','text-left')),
  //array('data'=>'Action', 'class'=>array('col-md-2','text-left')), 
  );

  $drive_folder_icon = $base_url . '/sites/all/themes/m6connect/images/drive-folder-icon.png';
  $Drive_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:40px;">';
  $Grid_folder_icon_image = '<img src="'.$drive_folder_icon.'" class="padding-5" style="width:50px;">';

  // Creating div structure.
  $optionview = 'List';
  if (isset($_SESSION['detailview'])) {
    $optionview =  $_SESSION['detailview'];
  }
  if ($optionview == 'List') {
    $grid_display =  'display:none';
    $list_display =  'display:block';
  }
  else {
    $grid_display =  'display:block';
    $list_display =  'display:none';
  }
  if ($projectnid == 0 && $folder_id == 0) {
    // This is the case, when we are on the root folder.
    $query = db_select('m6connect_project_drive_trash', 'pdt');
    $query->fields('pdt',array('id','user_uid','project_nid','fid','trash_status'));
    $query->condition('pdt.user_uid', $user->uid);
    $record = $query->execute()->fetchAll();

    foreach($record as $key => $value) {
      if (isset($value->project_nid) && is_numeric($value->project_nid) && $value->project_nid != 0 && _check_folder_eligibility_archive_trash($value->project_nid, 'trash')) {
        $ProjectNid = $value->project_nid;
        $Node = node_load($ProjectNid);

        $Userdetail = _get_user_data_by_uid($Node->uid);
        $Usersfullname = $Userdetail['realname'];

        $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$Node->title)).'';
        $foldername =  l($foldericon, 'project-trash-load-drive/'.$ProjectNid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$ProjectNid),'html' =>TRUE));

        $foldericongrid   = $Grid_folder_icon_image . ucwords(str_replace('_',' ',$Node->title)).'';
        $foldernamegrid =  l($foldericongrid, 'project-trash-load-drive/'.$ProjectNid.'/0/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$ProjectNid),'html' =>TRUE));

        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$Node->title.'" name="m6drive-project-'.$ProjectNid.'" value="'.$ProjectNid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', $Node->created),'class' => array('col-md-2','text-left')),
             array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_delete_trash_action_btn('folder', $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$ProjectNid.'-'.$company->nid.'-row'),
        );
         //For dev str row folder ==========
         $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                  <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$Node->title.'" name="m6drive-project-'.$ProjectNid.'" value="'.$ProjectNid.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
         //End dev str row==========
      }
      if(isset($value->fid) && is_numeric($value->fid) && $value->fid != 0 && _check_file_eligibility_archive_trash($value->fid, 'trash') &&  $filevalue = file_load($value->fid)) {
        $fid =  $value->fid;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);

        $Usersdetail = _get_user_data_by_uid($filevalue->uid);
        $Usersfullname =  $Usersdetail['realname'];

        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 
        $rows[] = array(
          'data' => array(
             array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', $filevalue->timestamp),'class' => array('col-md-2','text-left')),
             array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_delete_trash_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$fid.'-'.$company->nid.'-row'),
        );
         //For dev str row file ==========
        
          $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
          if($fileicondrive) {
             $img_url = $fileicondrive;
          }
          else {
            $img_url = image_style_url('user_image_large', $uri);
            $img_url = '<img src= '.$img_url.'>';
          }
         $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                      <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.' 
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
         //End dev str row file==========
      }
    }

    // If we are browsing the root, then need to check if any subfolder from
    // a project folder was trashed. Meaning only a subfolder from a project
    // folder was trashed and not the whole project folder.
    $drive_query = db_select('m6connect_m6drive', 'm')
      ->fields('m')
      ->condition('services', 'm6drive_project')
      ->condition('company_nid', $company->nid)
      ->condition('user_uid', $user->uid)
      ->condition('root', 1)
      ->condition('trash_status', 1)
      ->orderBy('created_date', 'DESC'); //ORDER BY created
    $record = $drive_query->execute()->fetchAll();
    $querysub = db_select('m6connect_m6drive_attachment','m');
    $querysub->fields('m',array('file','created_date','trash_status'));
    $querysub->condition('m.user_uid', $user->uid);
    $querysub->condition('m.services', 'm6drive_project');
    $querysub->condition('m.company_nid', $company->nid);
    $querysub->condition('m.trash_status', 1);
    $querysub->condition('m.root', 1);
    $querysub->orderBy('m.created_date', 'DESC'); //ORDER BY created
    $recordsub = $querysub->execute()->fetchAll();
    $complteresult = array_merge($record, $recordsub);

    $UserFnameLname =_get_user_data_by_uid($user->uid);
    $Usersfullname = $UserFnameLname['realname'];

    foreach ($complteresult as $value) {
      if (isset($value->foldername) && _check_folder_eligibility_archive_trash($value->Id, 'trash')) {
        // When the very first folder is browsed, then the projectnid or folder_id
        // are 0. But when we are browsing a sub folder in the root of archive,
        // we need a projectnid. So trying to get projectnid here.
        $output = m6drive_get_parent_folder($value->Id);
        foreach($output as $fldrId => $folderNameVal) {
          foreach($folderNameVal as $foldKey => $fldVal) {
            if (is_array($fldVal)) {
              $projectnid = $foldKey;
            }
          }
        }
        
        $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldername =  l($foldericon, 'project-trash-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE)); 

        $foldericongrid   = $Grid_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldernamegrid =  l($foldericongrid, 'project-trash-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE)); 

        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' =>  project_drive_archive_action_btn('folder', $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$value->Id.'-'.$company->nid.'-row'),
        );
        //For dev str row folder ==========
        $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                  <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
         //End dev str row==========
      }
      if (isset($value->file) && _check_file_eligibility_archive_trash($value->file, 'trash') && $filevalue = file_load($value->file)) {
        $fid =  $value->file;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);  
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
        $rows[] = array(
          'data' => array(
             array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_archive_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$fid.'-'.$company->nid.'-row'),
        );
         //For dev str row file ==========
              //$img_url = image_style_url('user_image_large', $uri);
              $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                                    <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                      '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
             //End dev str row file==========
      }
    }
    // Setting back the projectnid to 0, else the below query would be treated
    // true.
    $projectnid = 0;
  }

  if ($projectnid != 0) {
    // This is the case when we are browsing the project folder in the trash
    // directory.

    if ($folder_id == 0) {
      // As the project node files do not have any entry in the attachment table,
      // only project folder is trashed. Project files are not trashed, because
      // if a folder is trashed, it is not visible in the projects directory.
      // So, here we dynamically get these files.
      $node = node_load($projectnid);

      $Userdetail = _get_user_data_by_uid($node->uid);
      $Usersfullname = $Userdetail['realname'];

      $uri =  $node->field_images['und'][0]['uri'];
      $fid =  $node->field_images['und'][0]['fid'];
      if (!empty($fid)) {
        $filename = $node->field_images['und'][0]['filename'];
        $filemime = $node->field_images['und'][0]['filemime'];
        $filepath = file_create_url($uri);
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid))); 
        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y',  $node->created),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_delete_trash_action_btn('file', $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$fid.'-'.$company->nid.'-row'),
        );
         //For dev str row file ==========
              //$img_url = image_style_url('user_image_large', $uri);
              $fileicondrive = _get_file_icon_m6drive($filemime);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $uri);
                $img_url = '<img src= '.$img_url.'>';
              }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                                    <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                      '.$img_url.'<div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
             //End dev str row file==========
      } 
      $fieldrfpdocumentArr =_get_all_rfp_nid_using_project_nid_project_drive($projectnid);
      foreach ($fieldrfpdocumentArr as $projectfiles) {
        if (!empty($projectfiles['fid'])) {
          $ChkFidInArchive =_get_all_projectfid_in_archive_drive($user->uid, $projectfiles['fid']);
          if ($ChkFidInArchive != $projectfiles['fid']) {
            $filepath = file_create_url($projectfiles['uri']);  
            $Attachment = l($projectfiles['filename'], $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$projectfiles['fid']))); 
            $rows[] = array(
              'data' => array(
               array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
                array('data'=>   $Attachment, 'class' => array('col-md-4','text-left','drive-getting-folder')),
                array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
                array('data' => date('F d, Y', $node->created),'class' => array('col-md-2','text-left')),
                 array('data'=> _get_m6drive_project_filesize_by_fid($projectfiles['fid']),'class'=>array('col-md-3','text-left')),
                //array('data' => project_drive_delete_trash_action_btn('file', $projectfiles['fid']),'class' => array('col-md-2','text-left')), 
                ),  
              'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$projectfiles['fid'].'-'.$company->nid.'-row'),
            );
             //For dev str row file ==========
             
              $fileicondrive = _get_file_icon_m6drive($projectfiles['filemime']);
              if($fileicondrive) {
                 $img_url = $fileicondrive;
              }
              else {
                $img_url = image_style_url('user_image_large', $projectfiles['uri']);
                $img_url = '<img src= '.$img_url.'>';
              }
             $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                                     <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$projectfiles['filename'].'" name="m6drive-project-'.$projectfiles['fid'].'" value="'.$projectfiles['fid'].'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'<div class="clearfix text-blue grid-item-anchor">'.$projectfiles['filename'].'</div>
                </div>';
             //End dev str row file==========
          }
        }
      }
    }

    // After we have fetched files for project folder from nodes, we need the
    // folders in the project folder, or sub folders.
    if ($folder_id == 0) {
      $folder_id = $projectnid;
    }

    $drive_query = db_select('m6connect_m6drive', 'm')
      ->fields('m')
      ->condition('services', 'm6drive_project')
      ->condition('company_nid', $company->nid)
      ->condition('user_uid', $user->uid)
      ->condition('parent_id', $folder_id)
      ->condition('trash_status', 1)
      ->orderBy('created_date', 'DESC'); //ORDER BY created
    $record = $drive_query->execute()->fetchAll();
    $querysub = db_select('m6connect_m6drive_attachment','m');    
    $querysub->fields('m',array('file','created_date','trash_status'));
    $querysub->condition('m.user_uid', $user->uid);
    $querysub->condition('m.services', 'm6drive_project');
    $querysub->condition('m.company_nid', $company->nid);
    $querysub->condition('m.folder_id', $folder_id);
    $querysub->condition('m.trash_status', 1);
    $querysub->orderBy('m.created_date', 'DESC');//ORDER BY created
    $recordsub = $querysub->execute()->fetchAll();
    $complteresult = array_merge($record, $recordsub);

    $UserFnameLname =_get_user_data_by_uid($user->uid);
    $Usersfullname = $UserFnameLname['realname'];

    foreach ($complteresult as $value) {
      if (isset($value->foldername) && _check_folder_eligibility_archive_trash($value->Id, 'trash')) {
        $foldericon   = $Drive_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldername =  l($foldericon, 'project-trash-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE));

        $foldericongrid   = $Grid_folder_icon_image . ucwords(str_replace('_',' ',$value->foldername)).'';
        $foldernamegrid =  l($foldericongrid, 'project-trash-load-drive/'.$projectnid.'/' . $value->Id . '/nojs', array('attributes' => array('class' => array('use-ajax','pointer-events-none'),'id'=>'estimate-td-'.$value->Id),'html' =>TRUE));

        $rows[] = array(
          'data' => array(
            array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $foldername, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' =>  $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=>'-','class'=>array('col-md-3','text-left')),
            //array('data' =>  project_drive_archive_action_btn('folder', $ProjectNid),'class' => array('col-md-2','text-left')),           
           ),
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$value->Id.'-'.$company->nid.'-row'),
        );
        //For dev str row folder ==========
        $divprojectstrfol .='<div class="grid-view-folder-item col-md-4 padding-5 margin-bottom-10">
                                   <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$value->foldername.'" name="m6drive-project-'.$value->Id.'" value="'.$value->Id.'-folder" class="form-checkbox m6drive-project-checkbox"></div>
                                <div class="grid-item-anchor clearfix">'.$foldernamegrid.'</div>
                          </div>';
         //End dev str row==========
      }
      if (isset($value->file) && _check_file_eligibility_archive_trash($value->file, 'trash') && $filevalue = file_load($value->file)) {
        $fid =  $value->file;
        //$filevalue = file_load($fid);
        $uri = $filevalue->uri;
        $filename =  $filevalue->filename;
        $filetype = $filevalue->type;
        $filepath = file_create_url($uri);  
        $fileName = l($filename, $filepath, array('attributes' => array('class' => array(''),'id'=>'estimate-td-'.$fid)));
        $rows[] = array(
          'data' => array(
             array('data'=>'<div class="form-item form-type-checkbox"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>', 'class'=> array('col-md-1','text-center','hidden')),
            array('data'=>  $fileName, 'class' => array('col-md-4','text-left','drive-getting-folder')),
            array('data' => $Usersfullname,'class' => array('col-md-2','text-left')),
            array('data' => date('F d, Y', strtotime($value->created_date)),'class' => array('col-md-2','text-left')),
            array('data'=> _get_m6drive_project_filesize_by_fid($fid),'class'=>array('col-md-3','text-left')),
            //array('data' => project_drive_archive_action_btn('file',  $fid),'class' => array('col-md-2','text-left')),           
           ),  
          'class' => array('custom-odd','customsearchformydrive','project-drive-delete-'.$fid.'-'.$company->nid.'-row'),
        );
        //For dev str row file ==========
       
          $fileicondrive = _get_file_icon_m6drive($filevalue->filemime);
          if($fileicondrive) {
             $img_url = $fileicondrive;
          }
          else {
            $img_url = image_style_url('user_image_large', $uri);
            $img_url = '<img src= '.$img_url.'>';
          }
        $divprojectstrfile .=' <div class="grid-view-folder-item col-md-2 padding-5 margin-bottom-10">
                     <div class="form-item form-type-checkbox hidden"><input type="checkbox" data="'.$filename.'" name="m6drive-project-'.$fid.'" value="'.$fid.'-file" class="form-checkbox m6drive-project-checkbox"></div>
                       <span class="orignal-img" style="display:none;">'.$filepath.'</span>
                       '.$img_url.'
                       <div class="clearfix text-blue grid-item-anchor">'.$filename.'</div>
                </div>';
        //End dev str row file==========
      }
    }
  }
  $return .= '<div class="list-view" style="'.$list_display.'">';
  $return .= theme('table', array('header' => $header, 'rows' => $rows, 'empty' => 'No file or folders yet','attributes'=>array('class'=>array('table','m6connect-custom-m6drive-project-drive','table-striped','table-hover','table-bordered','text-center'))));
  $return .= '</div>';
  // End here fir table List view structure========  
  // start here for Grid  view structure========
   $return .= '<div class="grid-view" style="'.$grid_display.'">';
   $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Folders') . '</h3></div>';
   $return .= '<div class="grid-view-folders row margin-5">';
  // ====First handling only Folders.
   if(empty($divprojectstrfol)){
   $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No folders yet</strong></div>'; 
   }
   $return .= $divprojectstrfol; 
   $return .= '</div>'; //==end grid-view-folders
  // ====Then handling only Files.
   $return .= '<div class="grid-title clearfix"><h3 class="text-blue">' . t('Files') . '</h3></div>';
   $return .= '<div class="grid-view-files row margin-5">';
   if(empty($divprojectstrfile)){
   $return .= '<div class="col-md-9 col-sm-9 col-xs-12 empty message text-center"><strong>No files yet</strong></div>';
   }
   $return .= $divprojectstrfile; 
   $return .= '</div>'; //==end grid-view-files.
   $return .= '</div>'; //==end grid-view.
  // End here for Grid  view structure========

   return $return;
}

/**
 * Function to get form for deleting file from project drive.
 */
function project_drive_delete_folder_file_form($form, &$form_state) {
  $form['multiple_projectnid'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-project-drive-perform')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
   $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to delete: <span class="multiple-project-folders-show"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('project_drive_delete_folder_file_form_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );

  return $form;
}

/**
 * Submit handler for project_drive_delete_folder_file_form
 */
function project_drive_delete_folder_file_form_submit($form, &$form_state){
  global $user;
  global $company;
  $values = $form_state['values']; 
  $projectMultiple = $values['multiple_projectnid'];
  $projectfolder =  explode(',' ,$projectMultiple);

  if(!empty($projectfolder)) {
    foreach($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);

      if($getStatus[1] == 'folder'){
        $projectnidMul = $getStatus[0];
        if(!empty($projectnidMul)){
          $trash_status =  db_insert('m6connect_project_drive_trash')
            ->fields(array(
              'user_uid'=> $user->uid,
              'project_nid'=> $projectnidMul,
              'fid' => 0,
              'trash_status' => 0,
            ))
            ->execute();
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        if (!empty($fileIdMul)) {
          $trash_status =  db_insert('m6connect_project_drive_trash')
            ->fields(array(
              'user_uid'=> $user->uid,
              'project_nid'=> 0,
              'fid' => $fileIdMul,
              'trash_status' => 0,
            ))
            ->execute();
        }
      }
    }
  }
 if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/project/share-drive');
  }
}

/**
 * Function to generate form for multiple download
 */
function m6drive_download_multiple_folder_multi_form($form, &$form_state) {
  $form['for_multiple'] = array(
    '#type' => 'hidden',
    '#value' => '1',
    '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-share-ids')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="row margin-bottom-10"><div class="col-md-3 cross-icons"><i class="fa fa-download"></i></div><div class="col-md-9 remove-member" style="font-size:16px;">Download file now: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_download_multiple_folder_multi_form_submit'),
    '#value' => 'Download',
    '#prefix' => '<div class="clearfix text-right m6drive-download-btn">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );
  return $form; 
}

/**
 * Submit handler for personal drive download.
 */
function m6drive_download_multiple_folder_multi_form_submit($form, &$form_state){
  global $base_path, $base_url, $user;
  $uid = uniqid();
  $getFolderId = $form_state['values']['deleted_ids'];
  $dirLive = 'sites/default/files/';
  $zipName = 'M6DriveFolderData';
  $getMultipleData = explode(',',$getFolderId);

  if (isset($_SESSION['down_arr'])) {
    unset($_SESSION['down_arr']);
  }

  foreach($getMultipleData as $dataDelta => $dataVal) {
    $getDataType = explode('-',$dataVal);
    if($getDataType[1] == 'folder') {
      // If the request is for a folder.
      $foldername = t('M6DriveZip') . '/';
      $query = db_select('m6connect_m6drive', 'm')
        ->fields('m')
        ->condition('Id', $getDataType[0])
        ->execute();
      $result = $query->fetchObject();
      $parents = m6drive_get_parent_folder($getDataType[0]);

      // Adding folders and subfolders.
      foreach ($parents as $key => $value) {
        $shifted = array_shift($value);
        $foldername .=  $shifted . '/';
      }

      $foldername .= $result->foldername;
      _get_download_array_company($getDataType[0], $foldername, FALSE, FALSE);
    }
    else if($getDataType[1] == 'file'){
      // If the request is for a file.
      if ($fileObj = file_load($getDataType[0])) {
        $query = db_select('m6connect_m6drive_attachment', 'da');
        $query->fields('da', array('id', 'root'));
        $query->addField('da','folder_id','foldername');
        $query->addField('da','folder_id','parent');
        $query->fields('da', array('file'));
        $query->condition('da.file', $getDataType[0], '=');
        $getFileData = $query->execute()->fetchObject();

        // Preparing file path.
        $file_only_path = t('M6DriveZip') . '/';
        if (empty($getFileData->parent)) {
          // It means it is on root.
          $file_only_path .= $fileObj->filename;
        }
        else {
          $parents = m6drive_get_parent_folder($getFileData->parent);

          // Now adding sub folders.
          foreach ($parents as $key => $value) {
            $shifted = array_shift($value);
            $file_only_path .=  $shifted . '/'; 
          }

          // Adding the parent itself.
          $current_parent = get_folder_name_by_folderid($getFileData->parent);
          if (!empty($current_parent)) {
            $file_only_path .= $current_parent->foldername . '/';
          }

          $file_only_path .= $fileObj->filename;
        }

        $_SESSION['down_arr'][] = array(
          'id' => $getDataType[0],
          'file' => $getDataType[0],
          'path' => $file_only_path,
        );
      }
    }
  }

  if (isset($_SESSION['down_arr'])) {
    // If we have an array to download, then processing further.
    $archiveArr = $_SESSION['down_arr'];
    $archive_name = $dirLive . $zipName . '.zip'; // Archive name.
    @unlink($archive_name); // Removing any file with same.

    $zip = new ZipArchive();

    // Trying to create a zip.
    if ($zip->open($archive_name, ZipArchive::CREATE|ZipArchive::OVERWRITE) === TRUE) {
      foreach ($archiveArr as $delta => $record) {
        if (isset($record['file']) && $fileObj = file_load($record['file'])) {
          $fileName = $fileObj->filename;
          $objFile = file_copy($fileObj, $destination = 'temporary://'.$fileName.$uid.'.'.$fileName,  $replace = FILE_EXISTS_RENAME);
          if ($objFile) {
            $objFile->status = 0;
            file_save($objFile);
            $path = drupal_realpath($objFile->uri);
            if (file_exists($path)) {
              $r_path = '';
              $r_path .= $record['path'];
              // $r_path .= $fileObj->filename;
              $zip->addFile($path, $r_path);
            }
          }
        }
      }
      $zip->close();
    }
    else {
      watchdog('Drive', 'Zip not opening', $variables = array(), $severity = WATCHDOG_NOTICE, $link = NULL);
    }
  }
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();  
    $form_state['ajax_commands'][] = ctools_ajax_command_redirect($base_url.'/'.$archive_name);
  }
  $form_state['redirect'] = $base_url . '/' . $archive_name;
}

/**
 * Form callback to show a form to add a new folder in m6drive project tab.
 */
function m6drive_add_new_form_project($form, &$form_state, $projectnid = 0, $folder_id = 0) {
  global $user;  
  $userprofile = user_load($user->uid);
  $fid = $userprofile->field_user_profile_photo['und'][0]['fid']; 

  $projectnid = (isset($form_state['projectnid'])) ? $form_state['projectnid']: $projectnid;
  $form_state['projectnid'] = $projectnid; 

  $folder_id = (isset($form_state['folder_id'])) ? $form_state['folder_id']: $folder_id;
  $form_state['folder_id'] = $folder_id;

  $input = &$form_state['input'];
  $values = &$form_state['values'];
  $form['folder_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Folder Name'),
  );  
  $form['close'] = array(
    '#markup' => '&nbsp;&nbsp;' . l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('assign-bid-packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();'))),      
  '#weight' => 10,  
  );
  $form['submit'] = array(
    '#value' => 'Submit', 
    '#type' => 'submit', 
  '#attributes' => array( 'class' => array('m6drive-add-new-form-submit')),
  );
  return $form;
}

/**
 * Submit handler for m6drive_add_new_form_project().
 */
function m6drive_add_new_form_project_submit(&$form, &$form_state) {
  global $user, $company;
  $folder_zero = FALSE;
  $values = $form_state['values'];
  $companyName =  str_replace(' ','_',$company->title);
  $userName = str_replace(' ','_',$user->name);

  $projectnid = (!empty($form_state['projectnid'])) ? $form_state['projectnid'] : (!empty($projectnid) ? $projectnid : 0);
  $folder_id = (!empty($form_state['folder_id'])) ? $form_state['folder_id'] : (!empty($folder_id) ? $folder_id : 0);

  $root = 0;
  if (empty($projectnid) && empty($folder_id)) {
    $root = 1;
  }
  if (empty($folder_id)) {
    $folder_zero = TRUE;
  }

  $projectName = '';
  if (is_string($projectnid) && !empty($projectnid) && !is_numeric($projectnid)) {
    // This is the case, when a folder is being added to the project or rfp
    // folder root. If a 
    if ($projectnid == 'project') {
      $projectName = 'M6_Project_Postings/';
      if ($folder_zero) {
        // Making it root only if uploading on root.
        $root = 2;
      }
    }
    if ($projectnid == 'rfp') {
      $projectName = 'M6_RFPs/';
      if ($folder_zero) {
        // Making it root only if uploading on root.
        $root = 3;
      }
    }
  }
  
  if (is_numeric($projectnid) && !empty($projectnid)) {
    $project = node_load($projectnid);
    $node_folders = _get_rfp_project_folders($project);
    if (!empty($node_folders)) {
      foreach ($node_folders as $folder) {
        if ($folder == 'project') {
          $projectName .= 'M6_Project_Postings/';
        }
        else if ($folder == 'rfp') {
          $projectName .= 'M6_RFPs/';
        }
        else {
          $folder_node = node_load($folder);
          $projectName .= str_replace(' ', '_', $folder_node->title);
          $projectName .= '/';
        }
      }
    }

    $projectName .= str_replace(' ','_',$project->title);
    $projectName .= '/';
  }

  if ($folder_id == 0 && is_numeric($projectnid)) {
    $folder_id = $projectnid;
  }

  if (!empty($folder_id)) {
    // Getting current folder name.
    $query = db_select('m6connect_m6drive', 'm6d');
    $query->fields('m6d',array('foldername'));
    $query->condition('m6d.user_uid', $user->uid);
    $query->condition('m6d.company_nid', $company->nid); 
    $query->condition('m6d.Id', $folder_id);
    $Currentfolder = $query->execute()->fetchField();
  }

  $foldervalue = str_replace(' ','_',$values['folder_name']);

  // Getting parent folders if any.
  $output = m6drive_get_parent_folder($folder_id);
  
  $Parentfolder = '';
  foreach($output as $key=>$values) {
    $shifted = array_shift($values);
    if (is_array($shifted)) {
      // If this entry is array, then this means that it is the node entry.
      // Meaning project name, which we are attaching manually.
      continue;
    }
    // $Parentfolder .=  implode("",$values)."/"; 
    $Parentfolder .=  $shifted . "/"; 
  }

  if(isset($Currentfolder) && !empty($Currentfolder)){
    $foldername =  $Parentfolder.$Currentfolder.'/'.$foldervalue;
  }else{
    $foldername = $foldervalue;
  }

  if(isset($foldervalue) && !empty($foldervalue)) {
   $modifiedDate =  date('Y-m-d H:i:s');
   db_insert('m6connect_m6drive')
    ->fields(array(
        'company_nid'=> $company->nid,
        'user_uid'=> $user->uid,
        'services'=> 'm6drive_project',
        'created_date' =>$modifiedDate,
        'foldername' => $foldervalue,
        'parent_id' => $folder_id,
        'trash_status' => 0,
        'archive_status' => 0,
        'root' => $root,
      ))
    ->execute();

    if(!class_exists('S3')) include_once DRUPAL_ROOT . '/sites/all/libraries/awssdk1/S3.php';
    if(!defined('awsAccessKey')) define('awsAccessKey', 'AKIAJZCVB5B62KPYTLFA');
    if(!defined('awsSecretKey')) define('awsSecretKey', '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');
    $s3 = new S3(awsAccessKey, awsSecretKey);
    $s3->putObjectFile('M6Drive.txt', 'dev.repo.m6connect.com', 's3fs-private/'.$companyName.'/ProjectDocuments/'.$projectName.$foldername.'/M6Drive.txt', S3::ACL_PRIVATE);
  }
  if ($folder_zero) {
    $form_state['ajax_commands'][] = ajax_command_html("#project-m6drive-datacontainer-main-cust", m6drive_project_drive_listing_table_data($projectnid, 0));
  }
  else {
    $form_state['ajax_commands'][] = ajax_command_html("#project-m6drive-datacontainer-main-cust", m6drive_project_drive_listing_table_data($projectnid, $folder_id));
  }
  if ((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Form to upload file on m6drive project tab.
 */
function m6drive_upload_new_file_form_project($form, &$form_state, $projectnid = 0, $folder_id = 0) {
  global $user, $company;

  drupal_add_js(drupal_get_path('module', 'm6connect_m6_drive') . '/js/m6connect_m6_drive.js');  

  $form['#prefix'] = '<div class="m6drive-file-upload-custom">';
  $form['#suffix'] = '</div>';
  $totalProjectSpace = _get_total_space_project_drive_by_uid($user->uid, TRUE);
  $totalProjectSpace = $totalProjectSpace/1048576;
  $company_allocatespace = user_company_drive_total_space_count($company->nid);
  if($totalProjectSpace >= $company_allocatespace){
   $form['total-space'] = array(
    '#markup' => '<div class="over-space-memmory"><p>Please contact <a href="mailto:support@m6connect.com">support@m6connect.com</a> for more space.</p></div>',
    );
   $form['cancel-button'] = array(
    '#markup' => l('<input type="button" class="btn btn primary form-submit" value="Close" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();Drupal.attachBehaviors();'))),
    );
  }
  else {
  // plupload
  $form['m6drive-file'] = array(
    '#type' => 'plupload',
    //'#autoupload' => TRUE,
    //'#autosubmit' => TRUE,
    "#upload_validators"  => array(
       "file_validate_size" => array(1024*1280*800),
       "file_validate_extensions" => array("txt pdf oxps pub pages docx pptx ppt indd pmd doc jpg jpeg png gif xls xlsx zip tar.gz tar sql rar mov gif mkv mp4"),
     ),
  );
  
  // end plup load======
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));

  //$uploadbutton = '<input type="button" id="m6drivefileuploadbutton" class="btn btn primary form-submit" value="Upload" />';
  //$Removebutton = '<input type="button" id="m6drivefileremovebutton" class="btn btn primary form-submit" value="Remove" />';

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_upload_new_file_form_project_submit'),
    '#value' => 'Save',
    //'#prefix' => '<div class="clearfix">',  
   // '#suffix' => $closeButton.'</div></div></div>', 
    '#prefix' => '<div class="clearfix">',  
    '#suffix' => $closeButton.'</div>', 
  );
 }  
  return $form;
}

/**
 * Submit handler for m6drive_upload_new_file_form_project.
 */
function m6drive_upload_new_file_form_project_submit($form, &$form_state) {
  global $user, $company;
  $folder_zero = FALSE;
  $value = $form_state['values'];
  $companyName =  str_replace(' ','_',$company->title);
  $userName = str_replace(' ','_',$user->name);
  //$filefid = $value['m6drive-file'];

  $projectnid = (isset($form_state['projectnid'])) ? $form_state['projectnid'] : (isset($projectnid) ? $projectnid : 0);
  $folder_id = (isset($form_state['folder_id'])) ? $form_state['folder_id'] : (isset($folder_id) ? $folder_id : 0);

  $root = 0;
  if (empty($projectnid) && empty($folder_id)) {
    $root = 1;
  }
  if (empty($folder_id)) {
    $folder_zero = TRUE;
  }

  $projectName = '';
  if (is_string($projectnid) && !empty($projectnid) && !is_numeric($projectnid)) {
    // This is the case, when a file is being uploaded to the project or rfp
    // folder.
    if ($projectnid == 'project') {
      $projectName = 'M6_Project_Postings/';
      if ($folder_zero) {
        // Making it root only if uploading on root.
        $root = 2;
      }
    }
    if ($projectnid == 'rfp') {
      $projectName = 'M6_RFPs/';
      if ($folder_zero) {
        // Making it root only if uploading on root.
        $root = 3;
      }
    }
  }
  
  if (is_numeric($projectnid) && !empty($projectnid)) {
    $project = node_load($projectnid);
    $node_folders = _get_rfp_project_folders($project);
    if (!empty($node_folders)) {
      foreach ($node_folders as $folder) {
        if ($folder == 'project') {
          $projectName .= 'M6_Project_Postings/';
        }
        else if ($folder == 'rfp') {
          $projectName .= 'M6_RFPs/';
        }
        else {
          $folder_node = node_load($folder);
          $projectName .= str_replace(' ', '_', $folder_node->title);
          $projectName .= '/';
        }
      }
    }

    $projectName .= str_replace(' ','_',$project->title);
    $projectName .= '/';
  }

  if ($folder_id == 0 && is_numeric($projectnid)) {
    $folder_id = $projectnid;
  }

  // Current folder name.
  if (!empty($folder_id)) {
    $query = db_select('m6connect_m6drive', 'm6d');
    $query->fields('m6d',array('foldername', 'company_nid', 'user_uid'));
    $query->condition('m6d.Id', $folder_id);
    $qr_res = $query->execute()->fetchObject();
    $Currentfolder = $qr_res->foldername;
    if ($qr_res->user_uid != $user->uid && isset($qr_res->user_uid)) {
      $original_company = node_load($qr_res->company_nid);
      $original_user = node_load($qr_res->user_uid);
      $companyName =  str_replace(' ','_',$original_company->title);
      $userName =  str_replace(' ','_',$original_user->name);
    }
  }

  // Parent folder name.
  $output = m6drive_get_parent_folder($folder_id);

  $Parentfolder = '';
  foreach($output as $key=>$values) {
    $shifted = array_shift($values);
    if (is_array($shifted)) {
      continue;
    }
    // $Parentfolder .=  implode("",$values)."/"; 
    $Parentfolder .=  $shifted . "/"; 
  }
 
  if(isset($Currentfolder) && !empty($Currentfolder)) {
     $folderlocation = ''.$companyName.'/ProjectDocuments/'.$projectName.$Parentfolder.$Currentfolder.'/';
  }
  else {
     $folderlocation = ''.$companyName.'/ProjectDocuments/'.$projectName;
  }
  // print $folderlocation; die;
  //=====for file save here using plupload
  $files = $value['m6drive-file'];  
  $saved_files = array();
  $scheme = 'public://';
  foreach($files as $uploaded_file) {
    if($uploaded_file['status'] == 'done') {
      $source = $uploaded_file['tmppath'];
      $destination = file_stream_wrapper_uri_normalize($scheme . $uploaded_file['name']);
      $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
      $file = plupload_file_uri_to_object($destination);
      $destination = file_stream_wrapper_uri_normalize('private://'.$folderlocation);
      file_save($file);
      file_prepare_directory($destination, FILE_CREATE_DIRECTORY|FILE_MODIFY_PERMISSIONS);
      $new_file = file_move($file, $destination, FILE_EXISTS_RENAME);
      $saved_files[] = $new_file;
      //file_delete($file, TRUE);
    }
  }
  //=====end file save here using plupload
  if(!empty($saved_files)){
    $modifiedDate =  date('Y-m-d H:i:s');
    foreach($saved_files as $filevalue) {
      db_insert('m6connect_m6drive_attachment')
        ->fields(array(
          'company_nid'=> $company->nid,
          'user_uid'=> $user->uid,
          'file' => $filevalue->fid,
          'created_date' => $modifiedDate,
          'folder_id' => $folder_id,
          'trash_status' => 0,
          'archive_status' => 0,
          'services' => 'm6drive_project',
          'root' => $root,
        ))
        ->execute();
    }
  }
  if ($folder_zero) {
    $form_state['ajax_commands'][] = ajax_command_html("#project-m6drive-datacontainer-main-cust", m6drive_project_drive_listing_table_data($projectnid, 0));
  }
  else {
    $form_state['ajax_commands'][] = ajax_command_html("#project-m6drive-datacontainer-main-cust", m6drive_project_drive_listing_table_data($projectnid, $folder_id));
  }
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false) {
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Function to 
 */
function m6drive_add_tomydrive_form($form, &$form_state) {
   
  $form['for_multiple'] = array(
      '#type' => 'hidden',
      '#value' => '1',
      '#attributes' => array('class' => array('for_multishare_test')),
  );
  $form['deleted_ids'] = array(
      '#type' => 'textarea',
      '#attributes'=> array('class'=> array('multiple-share-ids')),
      '#prefix' => '<div style="display:none;">',
      '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    //'#title' => t('status'),
    '#markup' => '<div class="row margin-bottom-10"><div class="col-md-3 cross-icons"><i class="fa fa-plus"></i></div><div class="col-md-9 remove-member" style="font-size:16px;"> Are you sure you want add to my drive: <span class="multiple-folders"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_add_tomydrive_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );  

  return $form; 
}

/**
 * Submit handler for m6drive_add_tomydrive_form
 */
function m6drive_add_tomydrive_submit($form, &$form_state) {
  global $user;
  global $company;
 
  $values = $form_state['values'];
  $deleMultiple = $values['deleted_ids'];
  $filefolder =  explode(',' ,$deleMultiple);
  if(!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0];
        // If it is a folder, then just cleaning its child folders (if any present)
        // and saving it as is.
        _clean_add_to_my_drive_folder($folderIdMul, 'm6drive');

        // Deleting itself, if already present.
        db_delete('m6connect_m6drive_addto_mydrive')
          ->condition('user_uid', $user->uid)
          ->condition('folder_id', $folderIdMul)
          ->condition('services', 'm6drive')
          ->execute();

        // Saving it as is.
        db_insert('m6connect_m6drive_addto_mydrive')
          ->fields(array(
            'user_uid' => $user->uid,
            'services' => 'm6drive',
            'created_date' => date('Y-m-d H:i:s'),
            'folder_id' => $folderIdMul,
            'root' => 1,
          ))
          ->execute();
      }
      else if($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        // If it is a file, then just making an entry, but after deleting it.
        db_delete('m6connect_m6drive_addto_mydrive')
          ->condition('user_uid', $user->uid)
          ->condition('services', 'm6drive')
          ->condition('file', $fileIdMul)
          ->execute();

        // Creating a new entry.
        db_insert('m6connect_m6drive_addto_mydrive')
          ->fields(array(
            'user_uid' => $user->uid,
            'services' => 'm6drive',
            'created_date' => date('Y-m-d H:i:s'),
            'file' => $fileIdMul,
            'root' => 1,
          ))
          ->execute();
      }
    }
  }
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Function to get form for add to my drive in project drive.
 */
function m6drive_project_add_tomydrive_form($form, &$form_state) {
  $form['multiple_projectnid'] = array(
      '#type' => 'textarea',
      '#attributes'=> array('class'=> array('multiple-project-drive-perform')),
      '#prefix' => '<div style="display:none;">',
      '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-download"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want add to my drive: <span class="multiple-project-folders-show"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('m6drive_project_add_tomydrive_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );  

  return $form; 
}

/**
 * Submit handler for m6drive_project_add_tomydrive_form
 */
function m6drive_project_add_tomydrive_submit($form, &$form_state) {
  global $user;
  global $company;
  
  $values = $form_state['values'];
  $deleMultiple = $values['multiple_projectnid'];
  $filefolder =  explode(',' ,$deleMultiple);
  if(!empty($filefolder)) {
    foreach ($filefolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if($getStatus[1] == 'folder') {
        $folderIdMul = $getStatus[0];
        // If it is a folder, then just cleaning its child folders (if any present)
        // and saving it as is.
        _clean_add_to_my_drive_folder($folderIdMul, 'm6drive_project');

        // Deleting itself, if already present.
        db_delete('m6connect_m6drive_addto_mydrive')
          ->condition('user_uid', $user->uid)
          ->condition('folder_id', $folderIdMul)
          ->condition('services', 'm6drive_project')
          ->execute();

        // Saving it as is.
        db_insert('m6connect_m6drive_addto_mydrive')
          ->fields(array(
            'user_uid' => $user->uid,
            'services' => 'm6drive_project',
            'created_date' => date('Y-m-d H:i:s'),
            'folder_id' => $folderIdMul,
            'root' => 1,
          ))
          ->execute();
      }
      else if($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        // If it is a file, then just making an entry, but after deleting it.
        db_delete('m6connect_m6drive_addto_mydrive')
          ->condition('user_uid', $user->uid)
          ->condition('services', 'm6drive_project')
          ->condition('file', $fileIdMul)
          ->execute();

        // Creating a new entry.
        db_insert('m6connect_m6drive_addto_mydrive')
          ->fields(array(
            'user_uid' => $user->uid,
            'services' => 'm6drive',
            'created_date' => date('Y-m-d H:i:s'),
            'file' => $fileIdMul,
            'root' => 1,
          ))
          ->execute();
      }
    }
  }
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
  }
}

/**
 * Function to generate form for project drive delete permanent.
 */
function project_drive_delete_permanent_in_trash_form($form, &$form_state) {
  $form['multiple_projectnid'] = array(
    '#type' => 'textarea',
    '#attributes'=> array('class'=> array('multiple-project-drive-perform')),
    '#prefix' => '<div style="display:none;">',
    '#suffix' => '</div>'
  );
  $form['m6drive_action_title'] = array(
    '#type' => 'markup',
    '#markup' => '<div class="group-action-status row margin-bottom-10"><div class="col-md-2 cross-icons"><i class="fa fa-times"></i></div><div class="col-md-10 remove-member" style="font-size:16px;"> Are you sure you want to delete permanent: <span class="multiple-project-folders-show"></span> ?</div></div>',
  );
  $closeButton = l('<input type="button" class="btn btn primary form-submit" value="Cancel" />', 'javascript:void(0);', array('external' => TRUE, 'html' => TRUE, 'attributes' => array('class' => array('packages-popup-close'), 'onclick' => 'jQuery("span.popups-close").click();')));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#submit'=> array('project_drive_delete_permanent_in_trash_submit'),
    '#value' => 'Confirm',
    '#prefix' => '<div class="clearfix text-right">',  
    '#suffix' => $closeButton.'</div></div></div>', 
  );

  return $form;
}

/**
 * Submit handler for project_drive_delete_permanent_in_trash_form.
 */
function project_drive_delete_permanent_in_trash_submit($form, &$form_state){
  global $user;
  global $company;
  $values = $form_state['values']; 
  $projectMultiple = $values['multiple_projectnid'];

  $projectfolder =  explode(',' ,$projectMultiple);

  if (!empty($projectfolder)) {
    foreach($projectfolder as $multKey => $multVal) {
      $getStatus = explode('-', $multVal);
      if ($getStatus[1] == 'folder') {
        $projectnidMul = $getStatus[0];
        if (!empty($projectnidMul)) {
          // Recursively removing the child files and folders from share.
          _delete_folder_file_from_share_project($projectnidMul);

          $query = db_select('m6connect_m6drive', 'm')
            ->fields('m')
            ->condition('Id', $projectnidMul)
            ->execute()
            ->rowCount();

          if ($query > 0) {
            // Removing the folder from the m6drive_shared table.
            db_delete('m6connect_m6drive_shared')
              ->condition('folder_id', $projectnidMul)
              ->condition('share_to_uid', $user->uid)
              ->execute();
          }
          else {
            // If the folder is not in m6connect_m6drive table, then it means
            // that it is project node, so removing from the project share table.
            db_delete('m6connect_project_drive_shared')
              ->condition('project_nid', $projectnidMul)
              ->condition('share_to_uid', $user->uid)
              ->execute();
          }
        }
      }
      elseif ($getStatus[1] == 'file') {
        $fileIdMul = $getStatus[0];
        $query = db_select('m6connect_m6drive_attachment', 'm')
          ->fields('m')
          ->condition('file', $fileIdMul)
          ->execute()
          ->rowCount();

        if ($query > 0) {
          db_delete('m6connect_m6drive_shared')
            ->condition('fid', $fileIdMul)
            ->condition('share_to_uid', $user->uid)
            ->execute();
        }
        else {
          db_delete('m6connect_project_drive_shared')
            ->condition('fid', $fileIdMul,'=')
            ->condition('share_to_uid', $user->uid)
            ->execute();
        }
      }
    }
  }
  if((isset($form_state['ajax'])) ? (($form_state['ajax'] == 1) ? true : false) : false){
    $form_state['ajax_commands'][] = ctools_modal_command_dismiss();
    $form_state['ajax_commands'][] =ctools_ajax_command_redirect('/project/share-drive'); 
  }
}