<?php

/**
 * @file
 * Definition of project_issue_handler_area_issue_search_links.
 */

/**
 * Views area text handler for related links at the top of an issue search.
 */
class project_issue_handler_area_issue_search_links extends views_handler_area {

  function render($empty = FALSE) {
    $arg = NULL;
    // TODO: Move this to an admin setting on this handler, allowing one of the
    // argument handler to be selected as the source for the project node ID.
    if (isset($this->view->argument['nid'])) {
      $arg = $this->view->argument['nid']->get_value();
    }
    elseif (isset($this->view->argument['field_project'])) {
      // Used in SearchAPI-based views.
      $arg = $this->view->argument['field_project']->get_value();
    }
    $output = project_issue_query_result_links($arg);

    return $output;
  }

}
