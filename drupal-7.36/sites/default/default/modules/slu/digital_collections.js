Drupal.behaviors.digitalCollectionsBehavoir = function (context) {
  // term location in URL is hardcoded as 5th element
  term = window.document.URL.split('/')[4];
  // Match against cck field class, 3rd parameter to new_fake_link is the URL relative to base_path()
  $('.field-field-dc-subject .field-item').each(function(i, dom) { new_fake_link(i, dom, 'collections/'+term+'/bysubject')});
  $('.field-field-dc-creator .field-item').each(function(i, dom) { new_fake_link(i, dom, 'collections/'+term+'/bycreator')});
};

/**
 * Turns each matching cck field to link
 */
function new_fake_link(i, dom, url) {
  label = jQuery.trim($('div', dom).text());
  value = jQuery.trim(jQuery.trim($(dom).text()).slice(label.length));
  label = $('div', dom).clone()
  $(dom).empty().append(label).append('<a href="/' + url + '/' + value + '">' + value +'</a>');
}
