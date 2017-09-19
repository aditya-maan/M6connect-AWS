<?php
/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
?>
<?php
global $user; 
$logged_user = $user->uid;
if (!$user->uid) {
   header("Location: ".$GLOBALS['base_url']);
}

if (arg(0) == 'node') {
  $nid = arg(1);
  }

$site_url = $GLOBALS['base_url'];
$path = current_path();
$node = node_load($nid);
$content_type = $node->type;
//echo $content_type;

function getLnt($zip){
//$url = "http://maps.googleapis.com/maps/api/geocode/json?address=".urlencode($zip)."&sensor=false";
$url = "https://maps.googleapis.com/maps/api/geocode/json?address=".urlencode($zip)."&key=AIzaSyC86LE_cOCq2I8F6b3OJ207wL19sERnzq8";
$result_string = file_get_contents($url);
$result = json_decode($result_string, true);
$result1[]=$result['results'][0];
$result2[]=$result1[0]['geometry'];
$result3[]=$result2[0]['location'];
return $result3[0];
}

function getDistance($zip1, $zip2){
$first_lat = getLnt($zip1);
$next_lat = getLnt($zip2);
$lat1 = $first_lat['lat'];
$lon1 = $first_lat['lng'];
$lat2 = $next_lat['lat'];
$lon2 = $next_lat['lng']; 
$theta=$lon1-$lon2;
$dist = sin(deg2rad($lat1)) * sin(deg2rad($lat2)) +
cos(deg2rad($lat1)) * cos(deg2rad($lat2)) *
cos(deg2rad($theta));
$dist = acos($dist);
$dist = rad2deg($dist);
$miles = $dist * 60 * 1.1515;
return $miles;
}

?>

<div id="page">
	<header class="header" id="header" role="banner">
		<div class="container-fluid"> <?php print render($page['header']); ?>
			<div id="top-navigation" class="row"> <?php print render($page['top_navigation']); ?> </div>
		</div>
	</header>
	<div id="navigation">
		<div class="container"><?php print render($page['navigation']); ?></div>
	</div>
	<div id="main">
		<div class="container-fluid">
		<?php if($page['top_header']): ?>
			<div class="top_header clearfix"> <?php print render($page['top_header']); ?> </div>
			<?php endif; ?>
			<div id="content" class="column" role="main">
				<div class="box">
					<div class="inner-box"> <a id="main-content"></a> <?php print $messages; ?> <?php print render($tabs); ?>
						<?php if ($action_links): ?>
						<ul class="action-links">
							<?php print render($action_links); ?>
						</ul>
						<?php endif; ?>
						<!-- content start -->

<?php
$title_search ="";
$sort_select = $_GET['sel_name'];
if(empty($_GET['search_proposal']) && (empty($_GET['sel_name'])))
{
  $title_search ="order by a.created desc";
}
else if(!empty($_GET['search_proposal']) && (!empty($_GET['sel_name'])))
{	
	if($_GET['sel_name'] == "name_asc")
	{
	  $key_sort =  "order by a.title asc";		
	}
	else if($_GET['sel_name'] == "name_desc")
	{		
	  $key_sort =  "order by a.title desc";	
	}
	else if($_GET['sel_name'] == "date_asc")
	{	
		$key_sort =  "order by a.created asc";			
	}
	else if($_GET['sel_name'] == "date_desc")
	{	  
		$key_sort =  "order by a.created desc";		
	}
	else if($_GET['sel_name'] == "bit_amt_value")
	{	  
		//$key_sort =  "order by g.field_proposal_bid_amount_value desc";
		$key_sort = "order by bid_amount DESC";		
	}
	$tit_value = $_GET['search_proposal'];
	$title_search =  "and a.title LIKE '%$tit_value%' $key_sort"; 
	
}
else if(($_GET['search_proposal'] == "") || ($_GET['sel_name'] != ""))
{	
	if($_GET['sel_name'] == "name_asc")
	{
	  $key_sort =  "order by a.title asc";		
	}
	else if($_GET['sel_name'] == "name_desc")
	{		
	  $key_sort =  "order by a.title desc";	
	}
	else if($_GET['sel_name'] == "date_asc")
	{	
		$key_sort =  "order by a.created asc";			
	}
	else if($_GET['sel_name'] == "date_desc")
	{	  
		$key_sort =  "order by a.created desc";		
	}
	else if($_GET['sel_name'] == "bit_amt_value")
	{	  
		//$key_sort =  "order by g.field_proposal_bid_amount_value desc";
		$key_sort = "order by bid_amount DESC";		
	}	
	$title_search =  " $key_sort";  	
}

?>


						
<div class="m6_view_proposal">
  <div class="m6_main_view">

	
    <div class="right_m6_view list_inbox_pro">
      <div class="m6_own_con">
        <div class="m6_own" id="m6_prop1">
		<div class="clearfix">
 		<form name="listSearcFrm" id="seach_award" method="GET" >
          <div class="left_m6_prop1">
            <input placeholder="Search Proposals" name="search_proposal" id="s" value="" type="text">
            <input type="submit" style="border:0px;" class="search_m6_prop1" name="search" id="search" value="Search"  />
		 </div>
          <div class="right_m6_prop1">
			<select  name="sel_name" id="order_proposal" onchange="if (this.value) window.location.href='?sel_name='+this.value">
			 <option value="name_asc"> Proposal Name (A-Z)</option>
              <option value="name_desc"> Proposal Name (Z-A)</option>
              <option value="date_desc"> Created Date (Newest - Oldest)</option>
              <option value="date_asc"> Created Date (Oldest - Newest)</option>
              <option value="bit_amt_value"> Bid Amount (Highest to Lowest)</option>              
            </select>
          </div>		 
		</form>
		<script>
		 function changeTest(obj){
			document.getElementById("seach_award").submit();
		  }
		</script>
</div>
	
<ul id="content_msg">
<?php

$sql_node3 = db_query('SELECT a.title,a.nid,a.uid,a.status,a.created,b.entity_id,b.field_proposal_number_value,
c.entity_id,c.field_submit_proposal_in_respons_target_id,
d.entity_id,d.field_field_sub_proposal_pjt_target_id,
e.entity_id,e.field_submit_proposal_member_target_id,
f.entity_id,f.field_submit_proposal_to_company_target_id,
g.entity_id,g.field_proposal_bid_amount_value,
h.entity_id,h.field_proposoal_bid_types_value,
i.entity_id,i.field_proposal_job_location_administrative_area,i.field_proposal_job_location_locality,i.field_proposal_job_location_postal_code,  
CONVERT(REPLACE(g.field_proposal_bid_amount_value,:ReplaceFrom,:ReplaceTo), DECIMAL(10,2)) bid_amount 
FROM node AS a 
LEFT JOIN field_revision_field_proposal_number AS b ON a.nid=b.entity_id 
LEFT JOIN field_data_field_submit_proposal_in_respons AS c ON a.nid=c.entity_id 
LEFT JOIN field_revision_field_field_sub_proposal_pjt AS d ON a.nid=d.entity_id 
LEFT JOIN field_revision_field_submit_proposal_member AS e ON a.nid=e.entity_id 
LEFT JOIN field_revision_field_submit_proposal_to_company AS f ON a.nid=f.entity_id 
LEFT JOIN field_data_field_proposal_bid_amount AS g ON a.nid=g.entity_id
LEFT JOIN field_data_field_proposoal_bid_types AS h ON a.nid=h.entity_id  
LEFT JOIN field_data_field_proposal_job_location AS i ON a.nid=i.entity_id
WHERE a.type=:type '.$title_search, array(':type'=>'my_proposal',':ReplaceFrom'=>',',':ReplaceTo'=>''));

$sql_node4 = $sql_node3->fetchAll();
$sql_node = array();
if($sql_node4 && !empty($sql_node4)){
  $sql_node	= json_decode(json_encode($sql_node4), true);
}





	        for ($f = 0; $f < count($sql_node); $f++) {					
				$id = $sql_node[$f]['field_proposal_number_value'];
			    $node_pro_id = $sql_node[$f]['nid'];
				$node_owner = $sql_node[$f]['uid'];		
				$node_owner_status = $sql_node[$f]['status'];		
				
                 $title = $sql_node[$f]['title'];
                 $bit_amount = $sql_node[$f]['field_proposal_bid_amount_value'];				 
                 $bit_type = $sql_node[$f]['field_proposoal_bid_types_value'];				 
                 $city = $sql_node[$f]['field_proposal_job_location_locality'];				 
                 $state = $sql_node[$f]['field_proposal_job_location_administrative_area'];				 
				 $target_id = $sql_node[$f]['field_submit_proposal_in_respons_target_id'];
				 $target_id1 = $sql_node[$f]['field_field_sub_proposal_pjt_target_id'];
				 $target_id2 = $sql_node[$f]['field_submit_proposal_member_target_id'];
				 $target_id3 = $sql_node[$f]['field_submit_proposal_to_company_target_id'];
				 $zip_code = $sql_node[$f]['field_proposal_job_location_postal_code'];
				 
				  $rr = 0;
				  $target_member='';
				 if( $target_id != ""){
                   $target_member = $target_id;                 
				 }
				else if($target_id1 != ""){
                   $target_member = $target_id1;                 
				 }
				 else if($target_id2 != ""){				
                   $target_member = $target_id2;
					$rr=1;
				 }
				 else if($target_id3 != ""){				
                   $target_member = $target_id3;                 
				 }	
				 if(!is_numeric($target_member)){
					continue; 
				 }			 
				 $com_date = date('m/d/Y g:i A', $sql_node[$f]['created']);
				 if( $rr =="1"){					 
					 $userquery = db_select('users','u');
					 $userquery->join('realname','r','r.uid=u.uid');
					 $userquery->fields('u');
					 $userquery->fields('r',array('realname'));
					 $userquery->condition('u.uid',$target_member,'=');
					 $userdetails = $userquery->execute()->fetchAssoc();
					 $valu_fold = array($userdetails);
					 $sub_proposal_for = $valu_fold[0]['realname'];				
				 }else{		
				  $nodedetails = db_select('node','n')->fields('n')->condition('n.nid',$target_member)->execute()->fetchAssoc();
	              $valu_fold = array($nodedetails);
                  $sub_proposal_for = $valu_fold[0]['title'];
				 } 

				$userid1 = $valu_fold[0]['uid'];								
				/*if((($userid1 == $logged_user) && ($node_owner_status == 1)) || ($node_owner == $logged_user)) {*/
				
				$proposalSubmitterAccess = (($CurrCompNid == _get_company_nid_by_group_content($propNode)) && ((($node_owner == $logged_user))))?1:0;
                $proposalReceiverAccess = ((($node_owner_status == 1) && (in_array($CurrCompNid,_get_company_nids_by_proposal_target_node($targetNode)))) && ((($userid1 == $logged_user) || (is_proposal_project_collabarated($propNode)))))?1:0;
if($proposalSubmitterAccess || $proposalReceiverAccess){
				
				//zip code user location starts
		   
			/*$query_zip = db_select('node','zip')
					  ->fields('zip',array('vid')); 
					  $db_or_zip_vid = db_or();  
					  $db_or_zip_vid->condition(db_and()->condition('zip.type','organization', '=')->condition('zip.uid', $node_owner, '='));  
					  $src_cont_zip_vid =  $query_zip->condition($db_or_zip_vid);  
					  $result_cont_zip_vid = $src_cont_zip_vid->execute()->fetchAll();
					$zip_node = $result_cont_zip_vid[0]->vid;
				
			$query_zip_code = db_select('field_data_field_org_address','zipfl')
					  ->condition('zipfl.entity_id', $zip_node, '=')
					  ->fields('zipfl',array('field_org_address_postal_code'));  
					   $result_zip_final = $query_zip_code->execute()->fetchAll();
					 $zip_code_user = $result_zip_final[0]->field_org_address_postal_code;*/
			
		  //zip code user location ends
		  
		   //read msg starts
			$query_status1 = db_select('read_unread_message','tes')
				->fields('tes',array('proposal_id','comment_id','user_id','staus'));
				$db_or_cont_vid = db_or();  
				$db_or_cont_vid->condition(db_and()->condition('tes.proposal_id',$id, '=')->condition('tes.user_id', $logged_user, '='));  
			//echo '<pre>'; print_r($db_or_cont_vid); echo '</pre>';
				$src_cont_company_vid =  $query_status1->condition($db_or_cont_vid); 
			  
				$result_status1 = $src_cont_company_vid->execute()->fetchAll(); 
				//echo '<pre>'; print_r($result_status1); echo '</pre>';
				$read_cmd_id = '';
			  foreach($result_status1 as $item_read)
			   {
				$read_cmd_id .= $item_read->comment_id.'@';	
				 }
				$read_cmd_id_fin =  explode('@',$read_cmd_id);
				// echo '<pre>'; print_r($read_cmd_id_fin); echo '</pre>';
			//read msg ends
			
			$query_comment = db_select('comment','com')
			  ->condition('com.nid', $node_pro_id, '=')
			  ->fields('com',array('cid','uid','subject','created'));  
			   $query_comment->orderBy('cid', 'DESC');  
			   $result_comment = $query_comment->execute();
			  $result_comment_count = $query_comment->execute()->fetchAll();
				$sub1= count($result_comment_count);
				$j =0;
				foreach($result_comment_count as $item_read_st)
					{
					$read_cmd_id_st[$j] = $item_read_st->cid;	
					$j++;  }
				//echo '<pre>'; print_r($read_cmd_id_st); echo '</pre>';	
				$cmb_in = array_intersect($read_cmd_id_st,$read_cmd_id_fin);
				$sub2 = count($cmb_in);
				$unread_msg = $sub1 - $sub2;
				//echo $node_owner;
				//echo $zip_code;
				
	//logo image starts
	 
	$query_logo = db_select('node','logo')
					  ->fields('logo',array('nid')); 
					  $db_or_logo_vid = db_or();  
					  $db_or_logo_vid->condition(db_and()->condition('logo.type','organization', '=')->condition('logo.uid', $userid1, '='));  
					  $src_cont_logo_vid =  $query_logo->condition($db_or_logo_vid);  
					  $result_cont_logo_vid = $src_cont_logo_vid->execute()->fetchAll();
					$logo_node = $result_cont_logo_vid[0]->nid;
					
	$query_logo_code = db_select('field_data_field_logo','logof1')
					  ->condition('logof1.entity_id', $logo_node, '=')
					  ->fields('logof1',array('field_logo_fid'));  
					   $result_logo_final = $query_logo_code->execute()->fetchAll();
					 $logo_code_user = $result_logo_final[0]->field_logo_fid;
					 
	$query_logo_image = db_select('file_managed','logoimg')
					  ->condition('logoimg.fid', $logo_code_user, '=')
					  ->fields('logoimg',array('uri'));  
					   $result_logo_image = $query_logo_image->execute()->fetchAll();
					 $logo_code_uri = $result_logo_image[0]->uri;
					 $value=explode("://",$logo_code_uri,2);
						//print_r($value);
						$logo_path = $value[0];	
						$logo_code_img = $value[1];
	//echo $userid1.'---'; echo $logo_node.'---'; echo  $logo_code_user.'----'; echo $logo_code_img.'---';
	//logo image ends
			
		  
?>

            <li class="prop_m6con1">
              <div class="m6_prop1_img">
			  <a href="/<?php echo drupal_get_path_alias('node/'.$node_pro_id);?>">
			  <div class="default_cmp">
			  <?php if($logo_code_img == '') {?>
			  <i class="fa fa-fw fa-building"></i>
			  <?php } ?>
			  <?php if($logo_path == 'private') { ?>
			  <img src="/sites/default/files/private/styles/thumbnail/private/<?php echo $logo_code_img; ?>">
			  <?php } ?>
			  <?php if($logo_path == 'public') { ?>
			  <img src="/sites/default/files/styles/thumbnail/public/<?php echo $logo_code_img; ?>">
			  <?php } ?>			  
			  </div>
			  <span>PR: <?php  echo $id; ?></span>
			  </a></div>
              <div class="m6_prop1_cont">
				<a href="/<?php echo drupal_get_path_alias('node/'.$node_pro_id);?>">
                <h4 class="search_class"><?php echo $title; ?></h4>
				</a>
				<?php if($sub_proposal_for !='') { ?>
                <p class="search_class"><label>Submitted For:&nbsp </label><?php echo $sub_proposal_for; ?></p>
				<?php } ?>
                <ul>
				<?php if($city !='' && $state !='') { ?>
                  <li><img src="/sites/default/files/images/gray_m6.png"><?php echo $city?>, <?php echo $state; ?></li>
				 <?php } 
				 if($bit_type != '') {
				 ?>
                  <li><img src="/sites/default/files/images/fixed_m6.png"><?php echo  $bit_type; ?></li>
				  <?php } 
				  if($bit_amount != '') {
				  ?>
                  <li>$<span class="bit_proposal_amt"><?php echo $bit_amount; ?></span></li>
				  <?php } ?>
                </ul>
              </div>
              <div class="m6_prop1_created">
                <ul>
                  <li>
                    <label>Created:</label>
                    <span class="date"><a href="/<?php echo drupal_get_path_alias('node/'.$node_pro_id);?>"><?php echo $com_date; ?></a></span></li>
                   <!--<li class="created_sp"><img src="/sites/default/files/images/blue_img.png"> 
				  <?php		
					//echo $zip_code.'-own-'.$zip_code_user.'-test';
					//$distance = getDistance($zip_code,$zip_code_user); 		
					//echo number_format($distance,2);
				  ?> miles from you</li>-->
                   <?php if($unread_msg > 0) { ?>
                  <li class="un_msg"><a href="/<?php echo drupal_get_path_alias('node/'.$node_pro_id);?>">(<?php echo $unread_msg; ?>) Unread Messages</a></li>
				  <?php } ?> 
                </ul>
              </div>
              <div class="m6_actions">
                <div class="col-md-2 col-sm-2 col-xs-12 text-right action">
                  <div class="btn-group" style="margin-top:40px;">
                    <div class="dropdown">
                      <button aria-expanded="false" aria-haspopup="true" class="btn btn-success" data-toggle="dropdown" id="dLabel" type="button">Actions</button>
                      <ul aria-labelledby="dLabel" class="dropdown-menu" role="menu">
                        <li><a href="/<?php echo drupal_get_path_alias('node/'.$node_pro_id);?>">Open</a></li>                        
                      </ul>
                    </div>
                  </div>
                </div>
              </div>
            </li>	

	<?php  
				}
			}
	
	?>			

          </ul>
          <div class="clearfix text-center" id="view_more"><a href="javascript:" >See More</a></div>
        </div>
      </div>
    </div>
	
	
  </div>
  <!-- <div id="pagination"></div>-->
</div>

					<!-- content end -->
						<?php print $feed_icons; ?> </div>
				</div>
			</div>
			
						<?php
      // Render the sidebars to see if there's anything in them.
      $sidebar_first  = render($page['sidebar_first']);    
    ?>
			<?php if ($sidebar_first): ?>
			<aside class="sidebars"> <?php print $sidebar_first; ?> <?php print $sidebar_second; ?> </aside>
			<?php endif; ?>
		</div>
	</div>
	<div id="footer-message">
		<div class="container"> <?php print render($page['footer']); ?> </div>
	</div>
	<div class="container"><?php print render($page['bottom']); ?> </div>
</div>


<?php
  $query_2 = db_select('users_roles', 'ur') 
  ->fields('ur', array('uid', 'rid')) ;
  $db_or = db_or();  
  $db_or->condition(db_and()->condition('ur.uid', $user->uid, '=')->condition('ur.rid', array(1, 2, 3, 5, 6), 'NOT IN'));
  $src_1 =  $query_2->condition($db_or);  
  $result_2 = $src_1->execute();  
  foreach($result_2 as $item_2)
  { 
    $user_order_role = $item_2->rid; 	 
  } 
  
?>

<link href="<?php echo $site_url; ?>/sites/all/themes/m6connect/css/simplePagination.css" type="text/css" rel="stylesheet"/>
<script src="<?php echo $site_url; ?>/sites/all/themes/m6connect/js/jquery.simplePagination.js"></script>

<script> 
  
   jQuery(function($) {				
				
<!-- popup starts -->
var my_role = "<?php echo $user_order_role; ?>";
/************** Proposal Upgrade Popup *******************/ 
/*if (my_role == 4){
  $("#popup_lock-upgrade").attr("class","pop_title");
}
$(".pop_title").click(function(){
	$("#pop_content").fadeIn();	
	return false;
});*/
/*********************************************************/ 

	
 $(".pop_close").click(function(){ 
    $("#pop_content").fadeOut();
  });

  // search start
/*$("#s").on("keyup click input", function () {
	if (this.value.length > 0) {
	  $(".prop_m6con1").show().filter(function () {
	   return $(this).find('.search_class').text().toLowerCase().indexOf($("#s").val().toLowerCase()) == -1;

	  }).hide();

	}
	else {
	  $(".prop_m6con1").show();
	}
});
  

$(".search_m6_prop1").on("click", function () {
	if ($("#s").val().length > 0) {
	  $(".prop_m6con1").show().filter(function () {
	   return $(this).find('.search_class').text().toLowerCase().indexOf($("#s").val().toLowerCase()) == -1;

	  }).hide();

	}
	else {
	  $(".prop_m6con1").show();
	}

});
*/  
  
  
  
  var $divs = $("li.prop_m6con1");
  /*document.getElementById("order_proposal").onchange = function () {
    if (document.getElementById("order_proposal").value == "name_asc") {				
			var alphabeticallyOrderedDivs = $divs.sort(function (a, b) {
			return $(a).find("h4").text() > $(b).find("h4").text();
			});
			 $("ul#content_msg").html(alphabeticallyOrderedDivs);     
    } 
	
	if (document.getElementById("order_proposal").value == "name_desc") {				
			var alphabeticallyOrderedDivs = $divs.sort(function (a, b) {
			return $(a).find("h4").text() < $(b).find("h4").text();
			});
			 $("ul#content_msg").html(alphabeticallyOrderedDivs);     
    }
	
	if (document.getElementById("order_proposal").value == "bit_amt_value") {
		
			 var numericallyOrderedDivs = $divs.sort(function (a, b) {
        return $(a).find(".bit_proposal_amt").text().replace(/,/g, '') < $(b).find(".bit_proposal_amt").text().replace(/,/g, '');
    });
		$("ul#content_msg").html(numericallyOrderedDivs);
     
    } 
	
	if (document.getElementById("order_proposal").value == "date_desc") {	
			 var numericallyOrderedDivs = $divs.sort(function (a, b) {
			 return new Date( $(a).find(".date").text() ) < new Date( $(b).find(".date").text() );
    });
		$("ul#content_msg").html(numericallyOrderedDivs);     
    } 
	
	if (document.getElementById("order_proposal").value == "date_asc") {		
			 var numericallyOrderedDivs = $divs.sort(function (a, b) {
			 return new Date( $(a).find(".date").text() ) > new Date( $(b).find(".date").text() );
    });
		$("ul#content_msg").html(numericallyOrderedDivs);
     
    } 
	    
  };*/

// pagination

                var items = $("#content_msg li.prop_m6con1");

               // var numItems = items.length;
//				if(numItems <= 10 ) 
//				{
//				document.getElementById("pagination").style.display = "none";
//				}
//                var perPage = 10;
//
//                // only show the first 2 (or "first per_page") items initially
//                items.slice(perPage).hide();

                // now setup pagination
          //      $("#pagination").pagination({
//                    items: numItems,
//                    itemsOnPage: perPage,
//                    cssStyle: "light-theme",
//                    onPageClick: function(pageNumber) { // this is where the magic happens
//                        // someone changed page, lets hide/show lis appropriately
//                        var showFrom = perPage * (pageNumber - 1);
//                        var showTo = showFrom + perPage;
//
//                        items.hide() // first hide everything, then show for the new page
//                             .slice(showFrom, showTo).show();
//                    }
//                });



    /********************infinite scroll work start**********************/
													
                                                    var i = 0;
                                                    window.currentitems = 0;
                                                    $('#content_msg li.proposal-m6-container').each(function () {
                                                        if (i >= 15) {
                                                            $(this).hide();
                                                        }
                                                        i++;
                                                        window.currentitems = 15;
                                                    });

                                                    $('#view_more').click(function(){
                                                         var current  =  window.currentitems;  
                                                         current = current + 15;
                                                         
                                                         var k = 1;
                                                         $('#content_msg li.proposal-m6-container').each(function () {
                                                              
                                                             if(current >= k){
                                                                 $(this).show();
																
                                                             }
															 
															 
                                                             k++;
                                                         });
                                                         window.currentitems = current;
														 if(current > k) 
														{
														document.getElementById("view_more").style.display = "none";
														}
														 
                                                    });
													 var numItems = items.length;
				if(numItems <= 15 ) 
				{
				document.getElementById("view_more").style.display = "none";
				}
                                                    /********************infinite scroll work end**********************/
  
});

</script>


<!--- free plan popup start --->
                         <div id="pop_content">
                          <div class="overlay"></div><!--overlay-->	
                           <div class="pop_text">
                           
                           <div class="pop-main-top">  
							 <a href="#close" class="pop_close">
							 <img src="../sites/all/themes/m6connect/images/pop_close.png"/></a>
                               <h2>Unlock this Feature Today!</h2>
                               <div class="m6_pop_log">
							   <img src="../sites/all/themes/m6connect/images/m6_pop_log.png"/>
							   </div>
                               </div>
                           <div class="pop_text_inner">
                               <p>Unlock the full power of M6Connect and access this content 
by upgrading to one of our paid subscription levels. Click
below to choose the subscription that is right for you!</p>
                              <div class="m6_pop_list_im">
                               <ul class="m6_pop_list"> 
                               <li>View RFPs & Express Interest in Bidding<li>
                               <li>Create & Send Proposals<li>
                               <li>Connect with Other Companies<li>
                               <li>Create & Post Projects<li>
                               <li>Create & Send Contracts<li>
                               <li>and Much More!<li>
                                <img src="../sites/all/themes/m6connect/images/m6_pop_comp.png" class="compimg"/>
                               </ul>
                              
                               
                              <div class="m6_pop_upgrade_btn">
							  <a href="/upgrade-your-membership-subscription">
							  <img src="../sites/all/themes/m6connect/images/m6_pop_btn.png"/>
							  </a>
							  </div>
                               </div><!------m6_pop_list_im--->
                                </div><!--pop text inner-->
                           </div><!--pop text-->
                        </div><!--pop content-->
                     
<!--- free plan popup end --->