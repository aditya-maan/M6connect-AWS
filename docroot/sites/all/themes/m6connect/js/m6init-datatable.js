/**
 * This JS file initializes data table on tables in M6 wherever m6init-datatable
 * class is used on tables.
 */

(function ($) {
  Drupal.behaviors.m6init_dt = {
    attach: function (context, settings) {
      // 
      if ($('table.m6init-datatable').length > 0) {
        // If we found a table, then proceeding further.
        $('table.m6init-datatable').each(function(index, el) {
          if ($(this).find('tr').length > 2) {
            // If there are some columms, then only use datatables, otherwise
            // it may throw error.
            if ($.fn.dataTable.isDataTable(this)) {
                $(this).DataTable();
            }
            else {
              if ($(this).hasClass('m6init-datatable-search-paginate')) {
                $(this).DataTable({
                  stateSave: true,
                  "bPaginate": false,
                  "bLengthChange": false,
                  "paging": true,
                  "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
                  "searching": true,
                  "bInfo": false,
                  // "scrollX": true,
                });
              }
              else {
                $(this).DataTable({
                  stateSave: true,
                  "bPaginate": false,
                  "paging": false,
                  "aoColumnDefs": [{ "bSortable": false, "aTargets": ["no-sort"]}],
                  "searching": false,
                  "info":     false,
                  // "scrollX": true,
                });
              }
            }
          }
        });
      }
    }
  };
}(jQuery));