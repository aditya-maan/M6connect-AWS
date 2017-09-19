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
?>

<div <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
<?php foreach ($rows as $id => $row): //pre($row); ?>


  <div class="<?php if ($row_classes[$id]) { print implode(' ', $row_classes[$id]); } ?> m6-gallery-item">
  <?php //if ($row_classes[$id]) { print 'class="' . implode(' ', $row_classes[$id]) .'"';  } ?>
  <div class="cover-img"> <?php print $row['node_gallery_media'];?></div>
  <div class="cover-info-stats">
    <div class="cover-info">
      <div class="cover-name"> <?php print $row['title'];?> </div>
      <div class="cover-by-wrap">
        <div class="cover-by-link text-ellipsis"> <span class="cover-by">by</span></div>
      </div>
    </div>
    <div class="cover-stat-fields-wrap">
      <div class="cover-stat-wrap"> <span class="cover-stat cover-stat-appreciations js-cover-stat-appreciations  beicons-pre beicons-pre-thumb ">547</span> <span class="cover-stat cover-stat-views beicons-pre beicons-pre-eye hide-phone">2519</span>
        <div class="featured tooltipi-container beicons-pre beicons-pre-featured-small">
          <div class="tooltipi"> Featured On: <strong>1/14/2016</strong> </div>
        </div>
      </div>
      <div class="cover-fields"> <a href="" title="Editorial Design" class="field-link">Editorial Design</a>, <a href="" title="Graphic Design" class="field-link">Graphic Design</a>, <a href="" title="Illustration" class="field-link">Illustration</a> </div>
    </div>
  </div>
</div>

<?php endforeach; ?>

</div>