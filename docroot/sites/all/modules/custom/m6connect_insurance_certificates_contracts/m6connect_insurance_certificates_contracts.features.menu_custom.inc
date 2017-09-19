<?php
/**
 * @file
 * m6connect_insurance_certificates_contracts.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function m6connect_insurance_certificates_contracts_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: main-menu.
  $menus['main-menu'] = array(
    'menu_name' => 'main-menu',
    'title' => 'Main menu',
    'description' => 'The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.',
  );
  // Exported menu: menu-insurance-certificates-rfp.
  $menus['menu-insurance-certificates-rfp'] = array(
    'menu_name' => 'menu-insurance-certificates-rfp',
    'title' => 'Insurance Certificate RFP Center',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Insurance Certificate RFP Center');
  t('Main menu');
  t('The <em>Main</em> menu is used on many sites to show the major sections of the site, often in a top navigation bar.');


  return $menus;
}
