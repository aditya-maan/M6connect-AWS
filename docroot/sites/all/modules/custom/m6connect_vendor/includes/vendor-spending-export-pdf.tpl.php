<?php
if (!empty($nodes)) {
  $node_count = count($nodes);
  $i = 1;
  $capital_total = 0;
  $expense_total = 0;
  $total_total = 0;  
  // Some styling.
  print '<style>table.under-border{border:1px solid #CCC;border-collapse: collapse;} table.under-border tr{border-bottom:1px solid #CCC;}table.under-border, table.under-border tr, table.under-border tr td, table.under-border tr th{padding:10px;line-height: 1.4;}</style>
        ';
  // .capital{ padding:8px; border-radius:4px; border:1px solid #265a7f;display:block;}
  foreach($nodes as $option => $option_name) {
    $nodess = _get_region_options_vendor_spending_export('nodes', $option);
    print '<table class="under-border" style="width:100%; margin:0;">
      <thead>
        <tr>
          <th style="background:#265a7f;color:#FFF;text-align:left;font-size:16px;" colspan="6">' . $option_name . '</th>
        </tr>
      </thead>
      <tbody>';

    $sub_capital_total_unformatted = 0;
    $sub_expense_total_unformatted = 0;
    $sub_total_total_unformatted = 0;
    $sub_capital_total = 0;
    $sub_expense_total = 0;
    $sub_total_total = 0;

    foreach ($nodess as $key => $value) {
      $node = node_load($value);
      $og_nid = $node->og_group_ref[LANGUAGE_NONE][0]['target_id'];
      $og_node = node_load($og_nid);
      $company_title = $og_node->title;
      $company_details_address = _get_vendor_company_details($og_node, TRUE, FALSE, 'custom_thumb_100_100');
      $company_details_img = _get_vendor_company_details($og_node, FALSE, TRUE, 'custom_thumb_100_100');

      $region = '-';
      $regions = _get_area_of_work_options($node);
      if (!empty($regions)) {
        $region = implode(',', $regions);
      }
      else {
        $regions = _get_area_of_work_options($og_node);
        if (!empty($regions)) {
          $region = implode(',', $regions);
        }
      }

      $diverArr = array('No diversity defined!');
      if (!empty($og_node->field_diversity_credentials['und'])) {
        $diverArr = array();
        foreach ($og_node->field_diversity_credentials['und'] as $diverKey => $diverVal) {
          $diverArr[] = node_load($diverVal['target_id'])->title;
        }
      }

      $capital_unformatted = _get_capital_expense_vendor_spending($node, 'capital');
      $expense_unformatted = _get_capital_expense_vendor_spending($node, 'expense');
      $total_unformatted = $capital_unformatted + $expense_unformatted;

      $sub_capital_total_unformatted += $capital_unformatted;
      $sub_expense_total_unformatted += $expense_unformatted;
      $sub_total_total_unformatted += $total_unformatted;

      $capital = _vendor_format_amount_currency($capital_unformatted);
      $expense = _vendor_format_amount_currency($expense_unformatted);
      $total = _vendor_format_amount_currency($total_unformatted);

      print '<tr>
          <td align="center" width="100">' . $company_details_img . '</td>
          <td align="center" width="100">' . $company_title . '<br/>' . $company_details_address . '<br/>' . $region . '</td>
          <td align="center" width="250">' . implode(', ', $diverArr) . '</td>
          <td align="center" width="100"><div class="amount-title">Capital</div><div class="capital">' . $capital . '</div></td>
          <td align="center" width="100"><div class="amount-title">Expense</div><div class="capital">' . $expense . '</div></td>
          <td align="center" width="100"><div class="amount-title">Total</div><div class="capital">' . $total . '</div></td>
        </tr>';

      // $rows[] = array(
      //   array('data' => $company_details, 'class'=>array('text-center')),
      //   array('data' => implode(',', $diverArr), 'class'=>array('text-center')),
      //   array('data' => $capital, 'class'=>array('text-center')),
      //   array('data' => $expense, 'class'=>array('text-center')),
      //   array('data' => $total, 'class'=>array('text-center')),
      // );
    }
    print '</tbody>';
    $sub_capital_total = _vendor_format_amount_currency($sub_capital_total_unformatted);
    $sub_expense_total = _vendor_format_amount_currency($sub_expense_total_unformatted);
    $sub_total_total = _vendor_format_amount_currency($sub_total_total_unformatted);
    print '<tfoot>
        <tr>
          <th align="right" colspan="3">SubTotal</th>
          <th align="center"><div class="capital">' . $sub_capital_total . '</div></th>
          <th align="center"><div class="capital">' . $sub_expense_total . '</div></th>
          <th align="center"><div class="capital">' . $sub_total_total . '</div></th>
        </tr>
      </tfoot>';
    print '</table>';
    // print theme('table', array('header' => $header, 'rows' => $rows, 'empty' => t('No Vendor(s) Yet'), 'sticky' => FALSE, 'attributes' => array('class' => array('table', 'm6connect-custom-table', 'm6connect-custom-vendor-manager-main-table', 'table-hover', 'table-bordered', 'text-center'))));
    if ($i != $node_count) {
      print '<pagebreak suppress="off" />';
    }
    $i++;
  }
}
else {
  print '<p> No Data found!</p>';
}
?>