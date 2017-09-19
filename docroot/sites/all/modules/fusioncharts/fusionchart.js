function fusioncharts_clickbar(){
  var chartargs = '';
  var chartid = arguments[0];
  for (i=0; i<arguments.length; i++) {
   chartargs = chartargs + arguments[i] + '/';
  }
  $.get(Drupal.settings.fusioncharts['callback'] + chartargs ,
    function(data){
      updateChartXML(chartid, data);
    }
  );
}
