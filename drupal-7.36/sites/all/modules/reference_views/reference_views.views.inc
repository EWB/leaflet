<?php
/**
 * @file reference_views.views.inc
 * Contains implementations of Views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function reference_views_views_plugins() {
  return array(
    'display' => array(
      'reference_field' => array(
        'title' => t('Field formatter'),
        'help' => t("Display the view as a formatter for a nodereference field."),
        'handler' => 'reference_views_plugin_display_reference_field',
        'theme' => 'views_view',
        //'theme' => 'views_attach_display_node_content_view',
        //'theme file' => 'views_attach.theme.inc',
        //'theme path' => drupal_get_path('module', 'views_attach'),
        //'uses hook nodeapi' => TRUE,
        'uses hook field_formatter_info' => TRUE,
        'use ajax' => TRUE,
        'use pager' => TRUE,
        'use more' => FALSE,
        'accept attachments' => TRUE,
        'admin' => t('Field formatter'),
        //'help topic' => 'display-node-content',
      ),
    ),
  );
}

