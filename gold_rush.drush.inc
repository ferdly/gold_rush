<?php

/**
 * Coding Practices for this (demo) Module
 * * NOTE: the coding practices explained below are IMHO, they may or may not be
 *       agreed upon by the Drupal community and/or the Drush community at large
 *       further, they may or may not adhere to Drupal and/or Drush coding standards
 *       but, as we all know, that only starts to matter when you choose to publish
 *       your work, which is beyond the scope of what I am advocating. If you reach that
 *       juncture -- Congratulations! -- and that is the point at which these issues will
 *       start to matter.
 *
 */
/**
 * END Coding Practices for this (demo) Module
 */

/**
 * Drush Command Essential Functions
 * * the function below is the basis of implementing
 *      one or more Drush Commands
 * * the additional text that is required to support the 'drush help {command}' can
 *       get so long and involved it tends to obfuscate the critical 'syntactical' purpose
 *       the $items array;
 *       for this reason, I include only the most trivial descriptive
 *       string below, and implement a specific 'Utility Function',
 *       _render_help_documentation(), to overload and append the content to flesh-out
 *       a robust call to 'drush help {command}'
 */

/**
 * Implements hook_drush_command().
 */
function gold_rush_drush_command() {
/**
 *
 */
  $items['paydirt'] = array(
    'aliases' => array(
      'pd',
      'payd',
      ),
    'options' => array(
      'context' => 'is option',
      'claim' => 'is option',
      'stake' => 'is option',
      'dev' => 'is option',
    ),
  );
  $items['developer-vardump-gr'] = array(
    'aliases' => array(
      'devv-gr',
      ),
  );

_render_help_documentation_gr($items);

return $items;
}
/**
 * END Drush Command Essential Functions
 */

/**
 * Drush Naming Convention Functions
 * * these function will auto-magically be called based on the drush
 *       naming conventions
 * * they are the starting point for writing the code that implements your command
 * * these should manage only the 'drush specific' aspects of the command, including
 *       but not limited to:
 * * - implementing any drush UI, such as drush_choice()
 * * - validating argumants, aliases, and arguments
 */

/**
 * Callback for the drush-demo-command command
 */
function drush_gold_rush_paydirt() {
  $header = "Output from '" . __FUNCTION__ . "()':\r\n==========\r\n";
  drush_print($header);

  $print = drush_get_option('context', 0);
  $print = $print == 1 ? TRUE : FALSE;
  $print = TRUE;
  $context = _render_drush_context_gr($print);
  $options = $context['custom']['options'];
  unset($options['context']); //already evalauted

  /*<Validation Here>*/

  /*</Validation Here>*/
  $option_array['limit'] = $limit;
  $option_array['list'] = $list;
  $option_array['content_types'] = $content_type_after;
  $option_array['orderby'] = $orderby;
  $option_array['dev'] = $dev;
  _do_paydirt($option_array);
  return;
} //END function drush_paydirt($which_list = FALSE)


/**
 * Callback for the drush-demo-command command
 */
function drush_gold_rush_developer_vardump_gr() {
  _do_developer_vardump_gr();
}
/**
 * END Drush Naming Convention Functions
 */

/**
 * Drush Utility Functions
 * * functions here may facilitate one or more aspects
 * * since these functions are expected to be used over and over, the ending
 * *     "-gr" (gold rush) is added throughtout so that there aren't naming
 * *     conflicts. Rename accordingly each time you reuse any of these functions
 *
 */

function _render_help_documentation_gr(&$items) {
/**
  * $items Append & Overload below
  * description ONLY here
  * examples ONLY here
  * aliases isn't associative so NEVER here
  * others fleshed out for HELP command
  */
$items['paydirt']['description'] = "'paydirt' is a purposely inert command that merely renders Drush 'Context'. (see option 'context' below)";

$items['developer-vardump-gr']['description'] = "'developer-vardump-gr' is a very useful command that can be used to, well, dump variables while developing other commands. Three simple examples are included, adjust them by commenting and uncommenting for the effect you like, or append your own.";

$items['paydirt']['options']['context'] = 'Render Drush \'Context\' data, both core [\'drush\'] data, and [\'custom\'] that expresses useful data about the particular command as immediately called. NOTE: this option is often a default at first.';
$items['paydirt']['options']['dev'] = "A useful convention that extends any output beyond what a normal user may expect to include various developer output. NOTE: this option is mostly used during testing phase and probably should be removed before deployment.";

$items['node-tablelist']['examples']['drush paydirt --context'] = 'Render Drush \'Context\' data, both core [\'drush\'] data, and [\'custom\'] that expresses useful data about the particular command. NOTE: this option is often a default at first.';


  _render_help_documentation_gr_default($items);
}
function _render_help_documentation_gr_default(&$items) {
  foreach ($items as $command => $command_attributes) {
    if (empty($command_attributes['description'])) {
      $items[$command]['description'] = "Description for the drush command '{$command}'.";
    }
    $descr_example['Description as First Example'] = $items[$command]['description'];
    if (is_array($items[$command]['examples'])) {
      $items[$command]['examples'] = $descr_example + $items[$command]['examples'];
    }else{
      $items[$command]['examples'] = $descr_example;
    }
    if (is_array($command_attributes['arguments'])) {
      foreach ($command_attributes['arguments'] as $argument => $argument_descr) {
        if ($argument_descr == 'is argument') {
          $items[$command]['arguments'][$argument] = "Longer description of Argument '{$argument}'";
        }
      }
    }
    if (is_array($command_attributes['options'])) {
      foreach ($command_attributes['options'] as $option => $option_descr) {
        if ($option_descr == 'is option') {
          $items[$command]['options'][$option] = "Longer description of Option '{$option}'";
        }
      }
    }
  }
}

function _render_drush_context_gr($print = FALSE) {
  $file_line = '[File: ' . basename(__FILE__) . '; Line: ' . __LINE . ';]';
  $print = $print !== TRUE ? FALSE : TRUE;

  $context = drush_get_context();
  $command = $context['command'];

  $argument_values = $command['arguments'];
  $argument_keys = array_keys($command['argument-description']);
  $count_argument_values = count($argument_values);
  $count_argument_keys = count($argument_keys);
  if ($count_argument_keys > $count_argument_values) {
    foreach ($argument_keys as $index => $key) {
      if (empty($argument_values[$index])) {
        $argument_values[$index] = "missing_argument";
      }
    }
  }
  if ($count_argument_values > $count_argument_keys) {
    foreach ($argument_values as $index => $value) {
      if (empty($argument_keys[$index])) {
        $argument_keys[$index] = "extra_arg_{$index}";
      }
    }
  }
  $option_keys = $command['options'];
  $option_values = $context['cli'];
  foreach ($option_keys as $key => $descr) {
    $option_array[$key] = empty($option_values[$key]) ? 'not_provided' : $option_values[$key];
  }


  $developer_friedly_array = array();
  $dfa = array();
  $dfa_drush = array();
  $dfa_drush['command'] = $command['command'];
  $dfa_drush['argument-description'] = $command['argument-description'];
  $dfa_drush['arguments'] = $command['arguments'];
  $dfa_drush['options'] = $command['options'];
  $dfa_drush['cli'] = $context['cli'];
  $dfa_drush['aliases'] = $command['aliases'];
  $dfa_custom = array();
  $hook = 'drush_' . $command['commandfile'] . '_';
  $hook .= str_replace('-', '_', $command['command-hook']) . '()';
  $dfa_custom['command_hook_function'] = $hook;
  $dfa_custom['arguments'] = array_combine($argument_keys, $argument_values);
  $dfa_custom['options'] = $option_array;
  $developer_friedly_array['drush'] = $dfa_drush;
  $developer_friedly_array['custom'] = $dfa_custom;
  if ($print) {

    $header = "Output from '" . __FUNCTION__ . "()':\r\n" . $file_line . "\r\n======================================\r\n";
    $output = print_r($developer_friedly_array, TRUE);
    drush_print($header . $output);
  }
  return $developer_friedly_array;
}

/**
 * END Drush Utility Functions
 */


/**
 * Drush Specific Functions
 * * including functions that are called by the 'Drush Naming Convention Functions'
 *   \_ aka the '_do()' functions
 * * the 'Drush Naming Convention Fuctions' :
 * * - are the functions that are called automatically by way of the the drush command name
 *
 */
/**
 * Example function.
 */

function _do_paydirt($options_array = array()) {
  // $header = "Output from '" . __FUNCTION__ . "()':\r\n==========\r\n";
  // drush_print(print_r($options_array, TRUE));
}

// function _do_convert_fahrenheit_to_celcius($degrees_fahrenheit) {
//   $degrees_celcius = $degrees_fahrenheit;
//   $degrees_celcius -= 32;
//   $degrees_celcius *= 5;
//   $degrees_celcius /= 9;
//   $degrees_celcius = round($degrees_celcius,2);

//   $degrees_to_celcius_string = "{$degrees_fahrenheit} degrees Fahrenheit\r\nis equal to\r\n{$degrees_celcius} degrees Celcius";
//   drush_print($degrees_to_celcius_string);
// }

function _do_developer_vardump_gr() {
  $header = "Output from '" . __FUNCTION__ . "()':\r\n==========\r\n";

  $output = 'Hello World!';
  drush_print($header . $output);
  return;

  $thing_array = array();
  $i = -1;
  $i++;
  $thing[$i]['thing'] = 'Corvette';
  $thing[$i]['type'] = 'Little';
  $thing[$i]['color'] = 'Red';
  $i++;
  $thing[$i]['thing'] = 'Meanies';
  $thing[$i]['type'] = 'Screaming';
  $thing[$i]['color'] = 'Blue';
  $i++;
  $thing[$i]['thing'] = 'Fox';
  $thing[$i]['type'] = 'Quick';
  $thing[$i]['color'] = 'Brown';
  $output = print_r($thing, TRUE);
  drush_print($header . $output);
  return;

  $type_array = node_type_get_types();
  $output = print_r($type_array, TRUE);
  drush_print($header . $output);
  return;

}

/**
 * END Drush Specific Functions
 */
