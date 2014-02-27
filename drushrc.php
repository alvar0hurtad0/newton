<?php
$options['shell-aliases']['pull'] = '!git pull';
$options['shell-aliases']['push'] = '!git pull && git push';
$options['shell-aliases']['traepaca'] = '!drush sql-sync @default.pro default && drush rsync @default.pro:sites/default/files default:sites/default/files && drush cc all && drush vset preprocess_css 0 --yes';

