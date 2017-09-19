<?php


class m6connect_program_handler_company_address_custom extends views_handler_field {

  function construct() {
	  parent::construct();
  }

  function query() {
	  $this->ensure_my_table();
	  $this->add_additional_fields();
  }
  
  function option_definition() {
	  $options = parent::option_definition();
	  $options['text'] = array('default' => '', 'translatable' => TRUE);
	  $options['destination'] = array('default' => FALSE, 'bool' => TRUE);
	  return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  function render($values) {
	$value = $this->get_value($values);
	dsm($value);
	dsm($values);
    $type = $this->get_value($values, 'type');
	$address1='';
	/*if($type == 'organization'){
      $nid = $this->get_value($values, 'nid');
	  $address = $this->get_value($values, 'field_org_address');
	  dsm($address);
	}*/
    return $address1;
  }
}
