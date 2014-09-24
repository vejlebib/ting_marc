/**
 * Fetch values for Ajaxified ting marcXchange fields.
 */
(function($) {
  var selector = 'ting-marc-unprocessed',
    processing = 'ting-marc-processing',
    nodata = 'ting-marc-nodata';

  function ting_marc_fields(container) {
    var fields = [];

    $('.' + selector, container).each(function() {
      var data = $(this).data('ting-marc');
      if (data) {
        fields.push(data);
      }
      $(this).removeClass(selector);
      $(this).addClass(processing);
    });

    if (fields.length > 0) {
      $.post(
        Drupal.settings.basePath + Drupal.settings.pathPrefix + 'ting/marc/fields',
        {ting_marc_fields: fields},
        function(data) {
          $('.' + processing, container).each(function(){
            var field = $(this),
              _data = field.data('ting-marc');

            if (typeof(data[_data]) == "undefined") {
              field.addClass(nodata);
            }
            else {
              field.find('.field-item').html(data[_data]);
            }
            field.removeClass(processing);
          });
        }
      );
    }
  }

  Drupal.behaviors.ting_marc = {
    attach : function(context) {
      ting_marc_fields(context);
    }
  };

})(jQuery);
