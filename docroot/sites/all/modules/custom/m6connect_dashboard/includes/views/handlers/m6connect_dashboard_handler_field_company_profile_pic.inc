<?php

/**
 * @file
 * Definition of og_handler_field_og_membership_link_edit.
 */

/**
 * Field handler to present a link to edit membership.
 *
 * @ingroup views_field_handlers
 */
class m6connect_dashboard_handler_field_company_profile_pic extends views_handler_field_entity {

    function construct() {
        parent::construct();
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

    function query() {
        $this->ensure_my_table();
        $this->add_additional_fields();
    }

    function render($values) {
        if (!isset($values->_field_data['nid']['entity']->field_logo['und'])) {
            $output = '<img src="/sites/all/themes/m6connect/images/default_company_profile.jpg" style="">';
        } else {
            $output = '<img typeof="foaf:Image" src="' . image_style_url('media_thumbnail', $values->_field_data['nid']['entity']->field_logo['und'][0]['uri']) . '" alt="">';
        }

        return $output;
    }

}
