FusionCharts Module
================================================================================

Description
--------------------------------------------------------------------------------
This module connects Drupal with the FusionCharts Free package.  FusionCharts
Free is a flash charting component that can be used to render data-driven & 
animated charts for your web applications and presentations.

This module provides both a user interface for creating charts as well as as an
API for developers to intergrate with other modules.

Installation
--------------------------------------------------------------------------------
1. Download the FusionCharts module and place in the appropriate modules directory
   of your website.

2. Download the FusionCharts free package from http://www.fusioncharts.com/free and
   place the downloaded FusionChartsFree folder inside this FusionCharts module folder.
   
3. Enable this module by navigating to:
     administer > site building > modules

Configuration
--------------------------------------------------------------------------------
1. Configure path of fusion chart. Fusion Chart is expected to be in the folder sites/all/libraries/FusionCharts
In case you are using a different path, set it in settings.php for the key fustion_charts_path  e.g. 
$conf['fusion_charts_path'] = 'sites/default/FusionCharts/'; //Note the training forward slash (/)

2. If you are using the paid version of Fusion Chart set the fusion_charts_free to FALSE in settings.php
e.g.
$conf['fusion_charts_free'] = FALSE;

API
--------------------------------------------------------------------------------
See API.txt


Content Type
--------------------------------------------------------------------------------
To create a FusionChart node 
  Create a chart by navigating to:
     create content > fusionchart

There is also a FusionChart filter available.  This allows you to reference a FusionChart node from inside another node. To do this go to administer -> settings -> filters and enable the FusionCharts filter for the appropriate input format.  Note this filter should be one of the last filters applied, and must come after the HTML corrector and HTML filter.

You can then include a FusionChart node by entering "[fusionchart:x|w:100|h:300]" in the body of another page (where x is the node id of the fusionchart and w and h are the width and height of the chart (optional))



Credits
--------------------------------------------------------------------------------
* Drupal module by Aaron Fulton
* FusionCharts Package by InfoSoft Global (P) Ltd.

