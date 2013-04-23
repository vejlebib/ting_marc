<?php
/**
 * @file
 *
 * Template for ting_marc_data block.
 *
 * Variables:
 *   $rows - array of array('label' => '...', 'text' => '...').
 */

foreach ($rows as $row):
?>

<div class="panel-pane pane-entity-field materials" style="display: block;">
  <div class="pane-content" style="display: block;">
    <div class="field field-label-inline clearfix">
      <div class="field-label"><?php echo t($row['label']); ?>:&nbsp;</div>
      <div class="field-items">
        <div class="field-item"><?php echo $row['text']; ?></div>
      </div>
    </div>
  </div>
</div>

<?php
endforeach;
