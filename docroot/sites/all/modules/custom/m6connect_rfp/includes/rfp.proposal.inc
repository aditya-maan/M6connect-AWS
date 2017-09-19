<?php

//**************** start Rfp proposal summary Report ****************//

function rfp_proposal_summary_report($nid){

  //echo $nid; die;
	 
	global $user, $base_url, $base_path;
    $node = node_load($nid);
	//print_r($node); die;
	$content = theme('rfp_proposal_summary_report', array('node' => $node));
	//print $content;
	//drupal_exit(0); 
	
    include_once(libraries_get_path('mpdf') . '/mpdf.php');
    $mpdf = new mPDF('c'); 
	$mpdf->SetHTMLFooter('<table width="100%" style="vertical-align: bottom; font-size: 10pt; margin:0px 0 0 0px;"><tr><td width="33%"><img style="width:80px;" src="'.$base_url.'/sites/all/themes/m6connect/images/bidder_report_footer.png" alt="logo"/></td>
<td width="33%" align="center" style="font-style: normal;">{PAGENO}/{nbpg}</td>
<td width="33%" align="right"><span style="font-style: normal;">Print Date:{DATE j-m-Y}</span></td></tr></table>');

$mpdf->SetHTMLFooter('<table width="100%" style="vertical-align: bottom; font-size: 10pt; margin:0px 0 0 0px;"><tr><td width="33%"><img style="width:80px;" src="'.$base_url.'/sites/all/themes/m6connect/images/bidder_report_footer.png" alt="logo"/></td>
<td width="33%" align="center" style="font-style: normal;">{PAGENO}/{nbpg}</td>
<td width="33%" align="right"><span style="font-style: normal;">Print Date:{DATE j-m-Y}</span></td></tr></table>', 'E'); 

    $mpdf->setAutoTopMargin = 'stretch';
    $mpdf->setAutoBottomMargin = 'stretch';
    $mpdf->WriteHTML($content);
	
    $file_content = $mpdf->Output('report.pdf', 'I');
	//print $content;
	
}
//****************  Rfp proposal summary Report ****************//

?>