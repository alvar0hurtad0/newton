<?php
function drush_newton_n_revert($environment='') 
{
    drush_print('Looking for features, it can take some seconds... \n\r');
    switch ($environment) {
    case 'pre':
        drush_shell_exec('drush @default.pre features --status=enabled');
        break;
    case 'pro':
        drush_shell_exec('drush @default.pro features --status=enabled');
        break;
    default:
        drush_shell_exec('drush features --status=enabled');
    }
    $cont=0;
    $features = array();
    $starts= array();

    $lastchar=' ';
    foreach (drush_shell_exec_output() as $line) {
        if ($cont == 0) {
            $header = str_split($line);
            for ($i=0;$i < sizeof($header);$i++) {
                if (($header[$i] !=' ') && ($lastchar == ' ')) {
                    $starts[]=$i;
                }
                $lastchar=$header[$i];
            }
        }

        if ($cont<10) {
            $out =' '.$cont.' - '.$line."\n\r";
        }
        else{
            $out =$cont.' - '.$line."\n\r";
        }
        $cont ++;
        $featurename = substr($line, $starts[1], $starts[2]-$starts[1]);
        $features[]= trim($featurename);
        printf($out);
    }

    $option = drush_prompt("Enter the name of the feature to revert, please (0 to cancel)", '0', false);
    if ($option > 0) {
        switch ($environment) {
        case 'pre':
            drush_shell_exec_interactive('drush @default.pre fr '.$features[$option]);
            break;
        case 'pro':
            drush_shell_exec_interactive('drush @default.pro fr '.$features[$option]);
            break;
        default:
            drush_shell_exec_interactive('drush  fr '.$features[$option]);
        }
    }
}