<?php
/**
 * Views plugin for reference fields formatters.
 */
class reference_views_plugin_display_reference_field extends views_plugin_display {
  function option_definition () {
    $options = parent::option_definition();

    $options['formatter_label'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  /**
   * Provide the summary for page options in the views UI.
   *
   * This output is returned as an array.
   */
  function options_summary(&$categories, &$options) {
    // It is very important to call the parent function here:
    parent::options_summary($categories, $options);

    $categories['reference_field'] = array(
      'title' => t('Formatter settings'),
    );

    $formatter_label = strip_tags($this->get_option('formatter_label'));
    if (empty($formatter_label)) {
      $formatter_label = t('None');
    }

    $options['formatter_label'] = array(
      'category' => 'reference_field',
      'title' => t('Formatter label'),
      'value' => $formatter_label,
    );

  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      case 'formatter_label':
        $form['#title'] .= t('Formatter label');
        $form['formatter_label'] = array(
          '#type' => 'textfield',
          '#description' => t('This will appear as the name of this formatter in node display settings.'),
          '#default_value' => $this->get_option('formatter_label'),
        );
        break;
    }
  }

  /**
   * Perform any necessary changes to the form values prior to storage.
   * There is no need for this function to actually store the data. <-- LIES!
   */
  function options_submit(&$form, &$form_state) {
    // It is very important to call the parent function here:
    parent::options_submit($form, $form_state);

    switch ($form_state['section']) {
      case 'formatter_label':
        $this->set_option('formatter_label', $form_state['values']['formatter_label']);

        // Clear CCK's cache of content_type_info so the the display formatters
        // list is refreshed.
        cache_clear_all('content_type_info', content_cache_tablename(), TRUE);
        break;
    }
  }

  /**
   * Validation for the plugin.
   *
   * Check the base and that we have the right arguments in the right place.
   */
  function validate() {
    $errors = parent::validate();

    // Check the base table.
    if (!in_array($this->view->base_table, array('node', 'users'))) {
      $errors[] = t('Display "@display" may only be used on node views.', array('@display' => $this->definition['title']));

      // No point in checking further: it's no good.
      return $errors;
    }

    // If on the right base, move on to the arguments.
    $arguments = $this->display->handler->get_option('arguments');

    // Check the first argument is the node:nid.
    $argument = array_shift($arguments);
    switch ($this->view->base_table) {
      case 'node':
        if ($argument['field'] != 'nid') {
          $errors[] = t('The "@display" display requires the first argument to be Node:nid.', array('@display' => $this->definition['title']));
        }
        elseif (!$argument['break_phrase']) {
          $errors[] = t('The "@display" display Node:nid argument needs to be set to accept multiple terms.', array('@display' => $this->definition['title']));
        }
        break;
      case 'users':
        if ($argument['field'] != 'uid') {
          $errors[] = t('The "@display" display requires the first argument to be User:uid.', array('@display' => $this->definition['title']));
        }
        elseif (!$argument['break_phrase']) {
          $errors[] = t('The "@display" display User:uid argument needs to be set to accept multiple terms.', array('@display' => $this->definition['title']));
        }
        break;
    }

    // If there is a second argument, it should be 'null' to avoid unexpected
    // results, as the CCK formatter sends in the current node id for theming
    // convenience.
    if (count($arguments)) {
      $argument = array_shift($arguments);
      if ($argument['field'] != 'null') {
        $errors[] = t('The "@display" display requires the second argument, if present, to be Global:null.', array('@display' => $this->definition['title']));
      }
    }

    return $errors;
  }

  /**
   * Returns items for hook_field_formatter_info().
   *
   * This is the same pattern as the block display plugin uses. It's neat ;)
   */
  function execute_hook_field_formatter_info() {
    $label = $this->get_option('formatter_label');
    if (empty($label)) {
      $label = t('@view: @display', array('@view' => $this->view->name, '@display' => $this->display->display_title));
    }
    $key = 'views' . '_' . $this->view->name . '_' . $this->display->id;

    // Lookup to convert view base table to corresponding CCK field formatter.
    $field_types = array(
      'node'  => 'nodereference',
      'users' => 'userreference',
    );
    $field_type = $field_types[$this->view->base_table];

    $formatters = array(
      $key => array(
        'label' => $label,
        'field types' => array($field_type),
        'multiple values' => CONTENT_HANDLE_MODULE,
        // These are for our own use in our formatter function,
        // so one common function can know which view and display it is
        // meant to be using.
        'extra arguments' => array(
          'view'    => $this->view->name,
          'display' => $this->display->id,
        ),
      ),
    );

    return $formatters;
  }
}
