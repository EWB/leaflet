<?php
// $Id: themekey_properties_debug_admin.inc,v 1.2.2.2 2009/12/28 19:35:55 mkalkbrenner Exp $

/**
 * @file
 * provides a debug mode for module ThemeKey.
 * @see themekey.module
 *
 * @author Markus Kalkbrenner | Cocomore AG
 *   @see http://drupal.org/user/124705
 */


/**
 * Form builder for the form to enable ThemeKey debug mode.
 *
 * @ingroup forms
 */
function _themekey_properties_debug_settings_form() {
  $form = array();
  $form['themekey_properties_debug'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debug Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE
  );

  $form['themekey_properties_debug']['themekey_properties_debug_show_values'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show themekey properties values'),
    '#default_value' => variable_get('themekey_properties_debug_show_values', FALSE),
    '#description' => t('Shows current values of themekey properties on every page in message box. Additionally you can start creating a corresponding Theme Switching Rule by clicking on a value.')
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return system_settings_form($form);
}
