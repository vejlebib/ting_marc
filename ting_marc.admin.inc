<?php

function ting_marc_overview_page() {
  $result = db_query("SELECT * FROM {ting_marc} ORDER BY ting_type, marc_field, marc_subfield", array(), array('fetch' => PDO::FETCH_ASSOC));

  $types = ting_marc_types(TRUE);

  $header = array(t('Type'), t('Field'), t('Subfield'), t('Label'), array('data' => t('Operations'), 'colspan' => '2'));
  $rows = array();
  foreach ($result as $data) {
    $row = array();
    $row[] = array('data'=> $types[$data['ting_type']]);
    $row[] = array('data'=> $data['marc_field']);
    $row[] = array('data'=> $data['marc_subfield']);
    $row[] = array('data'=> $data['marc_label']);
    $row[] = array('data' => l(t('edit'), TING_MARC_ADMIN . '/' . $data['id'] . '/edit'));
    $row[] = array('data' => l(t('delete'), TING_MARC_ADMIN . '/' . $data['id'] . '/delete'));
    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

function ting_marc_edit_item($form, &$form_state, $action, $item = NULL) {
  $form['action'] = array(
    '#type' => 'hidden',
    '#default_value' => $action,
  );

  $form['id'] = array(
    '#type' => 'hidden',
  );


  if ($action == 'add' || empty($item)) {
    $item = array(
      'ting_type' => '',
      'marc_field' => '',
      'marc_subfield' => '',
      'marc_label' => '',
    );
  }
  else {
    $res = db_query("SELECT * FROM {ting_marc} WHERE id=:id",
      array('id' => $item),
      array('fetch' => PDO::FETCH_ASSOC)
    );

    $item = $res->fetchAssoc();

    $form['id']['#default_value'] = $item['id'];
  }

  $types = ting_marc_types(TRUE);

  $form['ting_type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => $types,
    '#default_value' => $item['ting_type'],
    '#description' => t('Ting item type'),
  );

  $form['marc_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Marc field'),
    '#default_value' => $item['marc_field'],
    '#required' => TRUE,
  );

  $form['marc_subfield'] = array(
    '#type' => 'textfield',
    '#title' => t('Marc subfield'),
    '#default_value' => $item['marc_subfield'],
    '#required' => TRUE,
  );

  $form['marc_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#default_value' => $item['marc_label'],
    '#required' => TRUE,
  );

  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save'));

  return $form;
}

/**
 * Process menu and menu item add/edit form submissions.
 */
function ting_marc_edit_item_submit($form, &$form_state) {
  $item = &$form_state['values'];

  $id = $item['id'];
  $action = $item['action'];
  unset($item['action'], $item['id']);

  $fields = array(
    'ting_type' => $item['ting_type'],
    'marc_field' => $item['marc_field'],
    'marc_subfield' => $item['marc_subfield'],
    'marc_label' => $item['marc_label'],
  );

  if ($action == 'add') {
    db_insert('ting_marc')
      ->fields($fields)
      ->execute();
  }
  else {
    db_update('ting_marc')
      ->fields($fields)
      ->condition('id', $id)
      ->execute();
  }

  $form_state['redirect'] = TING_MARC_ADMIN;
}

function ting_marc_delete_item($id) {
  return drupal_get_form('ting_marc_delete_item_confirm', $id);
}

function ting_marc_delete_item_confirm($form, &$form_state, $id) {
  $form['#marc_id'] = $id;
  $caption = '<p>' . t('This action cannot be undone.') . '</p>';
  return confirm_form($form, t('Are you sure you want to delete this setting?'), TING_MARC_ADMIN, $caption, t('Delete'));
}

function ting_marc_delete_item_confirm_submit($form, &$form_state) {
  $id = $form['#marc_id'];
  $form_state['redirect'] = TING_MARC_ADMIN;

  db_delete('ting_marc')->condition('id', $id)->execute();

  drupal_set_message(t('Setting has been deleted.'));
}


function ting_marc_types($pair = false) {
  // Source: http://www.danbib.dk/docs/abm/types.xml
  $types = array(
    'Akvarel',
    'Anmeldelse',
    'Arkitekturtegning',
    'Artikel',
    'Avis',
    'Avis (net)',
    'Avisartikel',
    'Billedbog',
    'Billedbånd',
    'Billedkort',
    'Billedtæppe',
    'Blu ray',
    'Bog',
    'Bog stor skrift',
    'CD',
    'Cd (musik)',
    'CD-I',
    'CD-rom',
    'Cd-rom (mp3)',
    'DCC-bånd',
    'Dias',
    'Diskette',
    'DTBook',
    'DVD (film)',
    'DVD-rom',
    'Ebog',
    'Emnekasse',
    'Fastplade',
    'Film (net)',
    'Flipover-materiale',
    'Flonellografmateriale',
    'Foto',
    'Foto-cd',
    'Fotoreproduktion',
    'GameBoy',
    'GameBoy Advance',
    'Graphic novel',
    'Grafisk blad',
    'Grammofonplade',
    'Kassettelydbånd',
    'Kort',
    'Kunstreproduktion',
    'Laborativt materiale',
    'Legetøj',
    'Lydbog (bånd)',
    'Lydbog (cd)',
    'Lydbog (net)',
    'Lydbog (cd-mp3)',
    'Maleri',
    'Materiale til indlæringsapparat',
    'Mikroform',
    'Mini disc',
    'Musik (net)',
    'Måleapparat',
    'Netdokument',
    'Nintendo DS',
    'Node',
    'Pc-spil',
    'Pc-spil (net)',
    'Ordkort',
    'Originalkunst',
    'Periodikum',
    'Periodikum (net)',
    'Plakat',
    'Planche',
    'Playstation',
    'Playstation 2',
    'Playstation 3',
    'Postkort',
    'PSP',
    'Punktskrift',
    'Puslespil',
    'Sammensat materiale',
    'Sang',
    'Serie',
    'Spil',
    'Spolelydbånd',
    'Symbolkort',
    'Teaterdukke',
    'Teateropførelse',
    'Tegneserie',
    'Tegning',
    'Teknisk tegning',
    'Tidsskrift',
    'Tidsskrift (net)',
    'Tidsskriftsartikel',
    'Transparent',
    'Udstilling',
    'Udstillingsmontage',
    'Video',
    'Wii',
    'Xbox',
    'Xbox 360',
    'Øvelsesmodel',
    'Årbog',
  );

  $result = array();
  if ($pair) {
    foreach ($types as $type) {
      $result[$type] = t($type);
    }
  } else {
    $result = array_map('t', $types);
  }
  return $result;
}
