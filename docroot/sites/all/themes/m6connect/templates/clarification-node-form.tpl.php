<div class="clarification-node-form-wrapper">
  <div class="clarification-node-elements">
      <?php print drupal_render($form['recipient']); ?>
      <?php print drupal_render($form['recipient-company']); ?>
      <?php print drupal_render($form['rfp-node-id']); ?>
      <?php print drupal_render($form['msg_type']); ?>
      <?php print drupal_render($form['msg_type']); ?>
      <?php print drupal_render($form['title']); ?>
      <?php print drupal_render($form['body']); ?>
      <?php print drupal_render($form['field_clarification_attachment']); ?>
  </div>
<div class="node-actions">
	  <?php print drupal_render($form['actions']); ?>
      <div style="display:none;"><?php print drupal_render_children($form);?></div>
  </div>
</div>