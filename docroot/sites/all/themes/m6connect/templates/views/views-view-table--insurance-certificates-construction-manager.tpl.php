<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
 global $user;
 $user_fields = user_load($user->uid);
 //dpm($user_fields);
 $company = $user_fields->field_user_company['und'][0]['target_id'];
 //dpm($company);
?>
<table <?php if ($classes) { print 'class="table table-bordered table-hover m6connect-custom-table '. $classes . '" '; } ?><?php print $attributes; ?>>
   <?php if (!empty($title) || !empty($caption)) : ?>
     <caption><?php print $caption . $title; ?></caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <?php foreach ($header as $field => $label): ?>
          <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
            <?php print $label; ?>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody class="page-has-scroll">
    <?php  foreach ($rows as $row_count => $row): ?>
    	<?php
    	//dpm($row);
			$nodelink_class = explode('class="node-',$row['title']);
			$node_nid_arry = explode('">' ,$nodelink_class[1]);
			$node_nid = $node_nid_arry[0];
    	//if($row['field_submit_to'] == $company ) {
		?>
    		<tr id="inscrt-node-<?php print $node_nid;?>" class="page-scroll" <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
        <?php foreach ($row as $field => $content): ?>
        	<?php        	
        	//dpm($field);
        	//if($field != 'field_submit_to') {
    		?>
          <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <?php print $content; ?>
          </td>
    	<?php    		
        	//}
		?>
    
        <?php endforeach; ?>
      </tr>
    	<?php
    	//}
		?>
    <?php endforeach; ?>
  </tbody>
</table>
<!--<div id="icert-modal" class="modal fade" tabindex="-1" role="dialog" aria-labelledby="gridSystemModalLabel">
    <div class="modal-dialog" role="document">
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                <h4 class="modal-title" id="gridSystemModalLabel">Modal title</h4>
            </div>
            <div class="modal-body">
                <div class="row">
                    <div class="col-md-4">.col-md-4</div>
                    <div class="col-md-4 col-md-offset-4">.col-md-4 .col-md-offset-4</div>
                </div>
                <div class="row">
                    <div class="col-md-3 col-md-offset-3">.col-md-3 .col-md-offset-3</div>
                    <div class="col-md-2 col-md-offset-4">.col-md-2 .col-md-offset-4</div>
                </div>
                <div class="row">
                    <div class="col-md-6 col-md-offset-3">.col-md-6 .col-md-offset-3</div>
                </div>
                <div class="row">
                    <div class="col-sm-9">
                        Level 1: .col-sm-9
                        <div class="row">
                            <div class="col-xs-8 col-sm-6">
                                Level 2: .col-xs-8 .col-sm-6
                            </div>
                            <div class="col-xs-4 col-sm-6">
                                Level 2: .col-xs-4 .col-sm-6
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="modal-footer">
                <button type="button" class="btn btn-default" data-dismiss="modal">Ok</button>
            </div>
        </div><!-- /.modal-content -->
    <!--</div><!-- /.modal-dialog -->
<!--</div><!-- /.modal -->
<script>
    var cert_id;
    var nid;
    $('.div-insurance-cert li').on('click', function (e) {
      if ( $( this ).hasClass( "open" ) ) {
			
	  } else {
        e.preventDefault();
        //$("#icert-modal").modal('show');
        if (typeof this.id == 'string') {
            var icert = this.id.split('-tid-')[1].split('-nid-'), 
                icert_id = this.id,
                that_icert_txt_temp = $('#' + this.id + ' a').text(),
                that_icert_p = $(this).parents('.div-insurance-cert'),
                that_icert_p_text = that_icert_p.children('button').first().text(),
                protcl = (location.protocol == 'http:') ? 'http:' : 'https:',
                loc_host = location.host,
                dest_url = protcl + "//" + loc_host;
//alert(icert[1]);
            that_icert_p.children('button').first().text('Wait...');

            if (typeof icert[0] == 'string' && typeof icert[1] == 'string') {
              cert_id = icert[0];
              nid = icert[1];
              //alert( "Cert ID: " + cert_id + " NID: " + nid + " ");

              // var currentUrl = window.location.href;
              // currentUrl = currentUrl.substring(0, currentUrl.lastIndexOf('/')+1);
              // alert(currentUrl);

              //tempBase = 'http://m6connect-rick.localhost/';
              jQuery.ajax({
                  type: "POST",
                  url: dest_url + "/status/" + cert_id + "/" + nid,
                  data: { cert_id: cert_id, nid: nid }
                }).done(function( msg ) {
                  //alert( "status/" + cert_id + "/" + nid );
                  ////alert( "Data Saved: " + msg );
                  ////alert(msg.indexOf("Deleted"));
                  if(msg.indexOf("Deleted") != -1 ) {
                    ////alert('Delete it!');
                    $('#' + icert_id).parent().parent().parent().parent().hide();
                  }else {
                    ////alert('dont delete!');

                    var bs_caret = document.createElement("span");
                    $(bs_caret).addClass("caret");
                    that_icert_p.children('button').first().html(that_icert_txt_temp + " ");
                    that_icert_p.children('button').first().append(bs_caret);
                    $('#' + that_icert_p.attr('id') + ' li').removeClass('active');
                    $('#' + icert_id).addClass('active');
                  }
              });
            }
        }
		
	  }
    });
</script>
