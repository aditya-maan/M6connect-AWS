<?php

$plugin = array(
  'title' => t('Node changes comment & edit form'),
  'single' => TRUE,
  'category' => t('Node changes'),
  'render callback' => 'nodechanges_edit_callback',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * If the user has access, and node’s comments are open, show a comment & edit
 * form.
 */
function nodechanges_edit_callback($subtype, $conf, $args, $context = NULL) {
  $block = new stdClass();
  if (isset($context->keyword) && $context->keyword === 'node' && isset($context->data) && nodechanges_get_field_name('comment_node_' . $context->data->type) && node_access('update', $context->data) && $context->data->comment == COMMENT_NODE_OPEN) {
    $context->data->nodechanges_in_block = TRUE;
    module_load_include('inc', 'node', 'node.pages');
    $block->subject = t('Add new comment');
    $block->content = drupal_get_form($context->data->type . '_node_form', $context->data);
  }
  return $block;
}
