<?php
/**
 * @file
 * Service related function.
 */

/**
 * Log messages to dblog.
 *
 * @param string $message
 *   Message to be logged.
 * @param array $data
 *   Paceholder data for message.
 */
function ting_mark_log($message, $data = array()) {
  if (variable_get('ting_mark_logging', 0)) {
    watchdog('ting_marc', $message, $data, WATCHDOG_DEBUG);
  }
}
