
 <?php
 
  if(!empty($node->nid)) {  
$items = field_get_items('node', $node, 'field_onbarding_credentials'); ?>
		<?php 	foreach($items as $item) {	
			 
			//print "<pre>"; print_r($item);
			$fcid = $item['value'];
			$fcvalue = field_collection_field_get_entity($item);
			
	    ?>
           
               
       <div class="block-block-68">
  		 <div class="pull-outer clearfix margin-bottom-10">
                    
	 					<div class="pull-left">
	    				  <i class="fa fa-trophy"></i>
					 	</div>
                        
	 					<div class="pull-right">
        					<div class="field-item">
                            <a href="/credentials-view-more/<?php print $node->uid; ?>/<?php print $fcid; ?>/nojs" class="ctools-use-modal ctools-modal-assign-dashboard-popup-style">
					<?php echo $fcvalue->field_title_name_of_credential['und'][0]['value'];?>
                          </a> 
					        </div>
  				       </div>
           </div>
		</div>
       
 <?php } }?>
 