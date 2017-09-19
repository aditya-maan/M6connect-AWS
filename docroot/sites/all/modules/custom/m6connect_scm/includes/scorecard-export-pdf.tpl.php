<?php

if (!empty($node)) {

  for ($i = 0; $i < 4; $i++) {
    $data = '';

    if ($i === 0) {
      print '<h3>' . t('SUMMARY') . '</h3><br/>';
      
      module_load_include('inc', 'm6connect_scm', 'includes/supply.chain.manager.decision');
      $b_arr = array();
      $data =  render(decision_main_container2_process(array(), $b_arr));
      
      print render($data);
    }

    if ($i === 1) {
      print '<h3>' . t('STAKEHOLDER RATINGS') . '</h3><br/>';

      $scorecard_nid = _fetching_scorecard_information_active('scm_scorecard');
      $scorecard_node = node_load($scorecard_nid);
      $data = _get_group_ratings_content_evaluate($scorecard_node);
      $data = str_replace('<div class="display-inline-block select-product-display-image padding-right-10"><img src="https://dev.m6connect.com/sites/all/themes/m6connect/images/scorecard_company_icon_small.png"></div>', '', $data);

      print render($data);
    }

    if ($i === 2) {
      print '<h3>' . t('COMMENTS') . '</h3><br/>';

      module_load_include('inc', 'm6connect_scm', 'includes/supply.chain.manager.decision');
      $data = render(comments_main_container2_process(array(), $form_state));

      print render($data);
    }

    if ($i === 3) {
      print '<h3>' . t('JUSTIFICATION') . '</h3><br/>';

      $data = render(justification_main_container2_process(array(), $form_state));

      print render($data);
    }

    // Page breaks.
    if ($i < 3) {
      print '<pagebreak suppress="off" />';
    }
  }
}
else {
  print t('Could not process due to some problem.');
}