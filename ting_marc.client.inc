<?php
/**
 * @file
 * Service related function.
 */

/**
 * Get object from service (cached).
 *
 * @param string $id
 *   Object identifier.
 *
 * @return NULL | TingMarcxchangeResult
 */
function ting_marc_load_object($id) {
  // Check cache.
  $cid = 'marcxchange:'.$id;
  $cache = cache_get($cid);
  if (!empty($cache)) {
    return $cache->data;
  }

  // Get object from service.
  $object = _ting_marc_load_object($id);
  cache_set($cid, $object);

  return $object;
}

/**
 * Get object directly from service (no cache).
 *
 * @param string $id
 *   Object identifier.
 *
 * @return NULL | TingMarcxchangeResult
 */
function _ting_marc_load_object($id) {
  module_load_include('client.inc', 'ting');
  // @todo Uncomment when moving to "new search" ting client.
  // $request = ting_get_request_factory('marcxchange');

  // @todo Remove next 5 lines when moving to "new search" ting client.
  $factory_data = ting_marc_ting_request_factory();
  $url = variable_get($factory_data['marcxchange'], FALSE);
  $agency = variable_get('ting_agency', FALSE);
  $profile = variable_get('ting_search_profile', '');
  $request = new TingMarcxchangeRequest($url, $agency, $profile);

  if (empty($request)) {
    return NULL;
  }

  $request->setId($id);
  $object = ting_execute($request);

  return $object;
}

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
