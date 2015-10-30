<?php
/**
 * @file
 * wysiwyg_feature.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function wysiwyg_feature_filter_default_formats() {
  $formats = array();

  // Exported format: Developer HTML.
  $formats['developer_html'] = array(
    'format' => 'developer_html',
    'name' => 'Developer HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(),
  );

  // Exported format: Editor.
  $formats['editor'] = array(
    'format' => 'editor',
    'name' => 'Editor',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_autop' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = array(
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_autop' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
    ),
  );

  // Exported format: Full HTML.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_autop' => array(
        'weight' => -48,
        'status' => 1,
        'settings' => array(),
      ),
      'htmlpurifier_basic' => array(
        'weight' => -47,
        'status' => 1,
        'settings' => array(
          'htmlpurifier_help' => 1,
          'htmlpurifier_basic_config' => array(
            'Attr.EnableID' => 0,
            'AutoFormat.AutoParagraph' => 1,
            'AutoFormat.Linkify' => 1,
            'AutoFormat.RemoveEmpty' => 0,
            'HTML.Allowed' => 'a[href|title|target|title],p,em,strong,cite,blockquote,code,ul,ol,li,dl,dt,dd,img[title|alt|src],div',
            'HTML.ForbiddenAttributes' => '',
            'HTML.ForbiddenElements' => '',
            'HTML.SafeObject' => 0,
            'Output.FlashCompat' => 0,
            'URI.DisableExternalResources' => 0,
            'URI.DisableResources' => 0,
            'Null_URI.Munge' => 1,
          ),
        ),
      ),
      'filter_url' => array(
        'weight' => -43,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
    ),
  );

  // Exported format: Plain text.
  $formats['plain_text'] = array(
    'format' => 'plain_text',
    'name' => 'Plain text',
    'cache' => 1,
    'status' => 1,
    'weight' => 10,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
