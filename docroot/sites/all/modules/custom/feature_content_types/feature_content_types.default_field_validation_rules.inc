<?php
/**
 * @file
 * feature_content_types.default_field_validation_rules.inc
 */

/**
 * Implements hook_default_field_validation_rule().
 */
function feature_content_types_default_field_validation_rule() {
  $export = array();

  $rule = new stdClass();
  $rule->disabled = FALSE; /* Edit this to true to make a default rule disabled initially */
  $rule->api_version = 2;
  $rule->rulename = 'foundedyear';
  $rule->name = 'foundedyear';
  $rule->field_name = 'field_year_founded';
  $rule->col = 'value';
  $rule->entity_type = 'node';
  $rule->bundle = 'organization';
  $rule->validator = 'field_validation_php_validator';
  $rule->settings = array(
    'data' => '$curryear = date("Y");
if(!empty($this->value)){
  if(!($this->value > 1700 && $this->value <= $curryear)){
    $this->set_error();
  }
}',
    'bypass' => 0,
    'roles' => array(
      1 => 0,
      2 => 0,
      3 => 0,
      4 => 0,
    ),
    'errors' => 0,
  );
  $rule->error_message = 'Founded Year should be between 1701 to current year';
  $export['foundedyear'] = $rule;

  return $export;
}
