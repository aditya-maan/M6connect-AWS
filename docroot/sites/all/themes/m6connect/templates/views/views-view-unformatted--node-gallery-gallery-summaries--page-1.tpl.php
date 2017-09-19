<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>

<?php foreach ($rows as $id => $row): //pre($row);
  //foreach($rows as $r): //pre($r); 
?>


  <div class="<?php if ($classes_array[$id]) { print $classes_array[$id]; } ?> m6-gallery-item">
    <?php print $row; ?>
  <!--<div class="cover-img"> <a href="" class="cover-img-link"><img src="" alt="Toumba Magazine"></a> </div>
  <div class="cover-info-stats">
    <div class="cover-info">
      <div class="cover-name"> <a href="" class="projectName cover-name-link">Toumba Magazine</a> </div>
      <div class="cover-by-wrap">
        <div class="cover-by-link text-ellipsis"> <span class="cover-by">by</span> <a class="single-owner-link" href=""> <span class="js-mini-profile">Dimitris Papazoglou</span> </a> </div>
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
  </div> -->
</div>

<?php endforeach; ?>


