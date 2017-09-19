<?php

/**
 * @file
 * Provides support for Views integration.
 */

/**
 * Implements hook_views_data_alter().
 */
function project_issue_views_data_alter(&$data) {
  // Add multiple autocomplete ability and ability to limit to "projects with issue queue enabled".
  $data['field_data_field_project']['field_project_target_id']['filter']['handler'] = 'project_issue_handler_filter_issue_project';
  if (isset($data['search_api_index_project_issues'])) {
    $data['search_api_index_project_issues']['field_project']['filter']['handler'] = 'ProjectIssueHandlerFilterSearchApiIssueProject';
  }

  // Use our custom project-argument-aware handler for component.
  $data['field_data_field_issue_component']['field_issue_component_value']['filter']['handler'] = 'project_issue_handler_filter_dereference_list';
  $data['field_revision_field_issue_component']['field_issue_component_value']['filter']['handler'] = 'project_issue_handler_filter_dereference_list';
  if (isset($data['search_api_index_project_issues'])) {
    $data['search_api_index_project_issues']['field_issue_component']['filter']['handler'] = 'ProjectIssueHandlerFilterSearchApiDereferenceList';

    // … and version.
    $data['search_api_index_project_issues']['field_issue_version']['filter']['handler'] = 'ProjectIssueHandlerFilterSearchApiVersion';
  }

  // Use our meta statuses handler for status.
  $data['field_data_field_issue_status']['field_issue_status_value']['filter']['handler'] = 'project_issue_handler_filter_issue_status';
  $data['field_revision_field_issue_status']['field_issue_status_value']['filter']['handler'] = 'project_issue_handler_filter_issue_status';
  if (isset($data['search_api_index_project_issues'])) {
    $data['search_api_index_project_issues']['field_issue_status']['filter']['handler'] = 'SearchApiViewsHandlerFilterIssueStatus';
  }

  if (module_exists('tracker')) {
    // Swap out the handlers for the uid_touch filter and argument.
    $data['node']['uid_touch']['argument']['handler'] = 'views_handler_argument_tracker_comment_user_uid';
    $data['node']['uid_touch']['filter']['handler'] = 'views_handler_filter_tracker_comment_user_uid';
  }

  // Add our search result links.
  $data['views']['project_issue_search_links'] = array(
    'title' => t('Project issue search links'),
    'help' => t('Displays links for project issue searches.'),
    'area' => array(
      'handler' => 'project_issue_handler_area_issue_search_links',
    ),
  );

  // Add an area handler for a 'create child issue' link
  $data['views']['project_issue_create_child'] = array(
    'title' => t('Project issue create child link'),
    'help' => t('Displays a link for to create a child issue for the current project issue.'),
    'area' => array(
      'handler' => 'project_issue_handler_area_issue_create_child',
    ),
  );
}

/**
 * Implements hook_field_views_data_alter().
 */
function project_issue_field_views_data_alter(&$result, $field, $module) {
  if ($field['field_name'] == 'field_issue_status') {
    // Look for SQL storage, as we're going to add a SQL specific field.
    if ($field['storage']['type'] == 'field_sql_storage') {
      // Create a copy of the field.
      $copy_field = $result['field_data_field_issue_status']['field_issue_status'];

      // Tweak some details of our copied field.
      $copy_field['title'] = t('Open issue count');
      $copy_field['field']['handler'] = 'project_issue_handler_field_issue_status_open_count';

      $result['field_data_field_issue_status']['open_field_field_issue_status'] = $copy_field;
    }
  }
}

function project_issue_views_plugins() {
  $path = drupal_get_path('module', 'project_issue') . '/views/plugins';
  $views_path = drupal_get_path('module', 'views');
  return array(
    'style' => array(
      'project_issue_table' => array(
        'title' => t('Project issue table'),
        'help' => t('Table with colored rows depending on issue status.'),
        'handler' => 'project_issue_table_plugin_style',
        'parent' => 'table',
        'path' => $path,
        'theme' => 'views_view_table',
        'theme file' => 'theme.inc',
        'theme path' => "$views_path/theme",
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'row' => array(
      'project_issue_node' => array(
        'title' => t('Project issue node'),
        'help' => t('Display a project issue node with special styling.'),
        'handler' => 'project_issue_plugin_row_project_issue_node_view',
        'path' => $path,
        'theme' => 'project_issue_issue_link',
        'register theme' => FALSE,
        'base' => array('node'), // only works with 'node' as base.
        'uses fields' => FALSE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'access' => array(
      'project_issue_access_per_user_queue' => array(
        'title' => t('View per-user issue queues'),
        'help' => t('Access will be granted if the user is requested in the URL or for users viewing their own per-user issue queues.'),
        'handler' => 'project_issue_plugin_access_per_user_queue',
        'uses options' => TRUE,
        'path' => $path,
      ),
    ),
    'argument validator' => array(
      'project_issue_nid' => array(
        'title' => t('Project issue node'),
        'handler' => 'project_issue_plugin_argument_validate_project_issue_nid',
        'path' => $path,
      ),
      'project_nid_having_issue_queue' => array(
        'title' => t('Project with issue queue'),
        'handler' => 'project_issue_plugin_argument_validate_project_nid',
        'path' => $path,
        'parent' => 'project_nid',
      ),
    ),
  );
}
