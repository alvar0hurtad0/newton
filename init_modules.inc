<?php

function gitano_init_modules() {
  $modules = Array();
  $modules[] = 'views';
  $modules[] = 'coffee';
  $modules[] = 'features';
  $modules[] = 'smtp';
  $modules[] = 'google_analytics';
  $modules[] = 'adminimal_theme';
  $modules[] = 'adminimal_admin_menu';

  return $modules;
}

