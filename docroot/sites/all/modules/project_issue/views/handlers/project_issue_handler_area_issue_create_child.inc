<?php

/**
 * @file
 * Definition of project_issue_handler_area_issue_create_child.
 */

/**
 * Views area text handler for creating a new child issue.
 */
class project_issue_handler_area_issue_create_child extends views_handler_area {

  function render($empty = FALSE) {
    // Get the ID of the current issue (and prospective parent) from the
    // argument.
    $parent_nid = $this->view->argument['nid']->get_value();

    return l(
      t('Add child issue'),
      'node/add/project-issue/' . node_load(node_load($parent_nid)->field_project[LANGUAGE_NONE][0]['target_id'])->field_project_machine_name[LANGUAGE_NONE][0]['value'],
      array(
        'query' => array(
          'field_issue_parent' => $parent_nid,
        ),
      )
    );
  }

}
