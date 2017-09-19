<?php

function import_regions_form($form, &$form_state) {
	
	$result = db_query("SELECT vid FROM {taxonomy_vocabulary} WHERE name = :name", array(":name" => "Industry NAICS"))->fetchField();
	
	drupal_set_message($result);
	
	$form['upload_csv'] = array(
	'#title' => t('Upload csv for regions'),
	'#type' => 'managed_file',
	'#required' => TRUE,
	'#upload_validators' => array(
       'file_validate_extensions' => array('csv'),
     ),
  );
	
  $form['submit'] = array(
	'#type' => 'submit',
	'#value' => t('Submit'),
  );
	
	return $form;
}

function import_regions_form_submit($form, &$form_state) {
	$file = file_load($form_state['values']['upload_csv']);
	
	$url = drupal_realpath($file->uri);
	
	
	$handle = fopen($url, 'r');
	
	$row = fgetcsv($handle);
	foreach ($row as $i => $header) {
		$columns[$i] = trim($header);
	}

	while($csv_line = fgetcsv($handle,1024)) {
		//$a = array();
    for ($i = 0, $j = count($csv_line); $i < $j; $i++) {
			$record[$columns[$i]] = $csv_line[$i];
    }
		$result[] = $record;
	}
	
	
	if (is_array($result) && $result) {
		$batch = array(
			'title' => t('Working ...'),
			'operations' => array(),
			'finished' => 'import_finished_regions',
			'init_message' => t('Starting ...'),
			'progress_message' => t('Processed @current out of @total.'),
			'error_message' => t('An error occurred during processing'),
			'progressive' => FALSE,
			'file' => drupal_get_path('module', 'm6connect_misc') . '/includes/m6connect_misc.inc',
		);
		
		$progress = 0; // where to start
		$limit = 10; // how many to process for each run
		$max = count($result); // how many records to process until stop - can do query here to get max times to run
		while ($progress <= $max) {
			$batch['operations'][] = array('import_regions_batch_process', array($progress, $limit, array_slice($result, $progress, $limit)));
			$progress = $progress + $limit;
		}		
		batch_set($batch);
		
		batch_process('admin/regions');
  }
  else {
    drupal_set_message(t("Oops ! An error occured !"), 'error');
  }
}


/*
* Batch process callback for import regions
*/

function import_regions_batch_process($progress, $limit, $result, &$context) {
	foreach($result as $key => $record) {
		drupal_set_message("<pre>". print_r($record,1));
		if($record['region'] != '') {
			if($region = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['region'], ":parent" => 0,":vid" => 3))->fetchField()) {
				if($record['region1'] != '' ){
					if($region1 = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region1 AND tth.parent = :parent AND ttd.vid = :vid", array(":region1" => $record['region1'], ":parent" => $region,":vid" => 3))->fetchField()) {
						if($record['region2'] != '' ){
							if($region2 = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region2 AND tth.parent = :parent AND ttd.vid = :vid", array(":region2" => $record['region2'], ":parent" => $region1,":vid" => 3))->fetchField()) {
								
							}
							else {
								$term = new stdClass();
								$term->name = $record['region2'];
								$term->vid = 3;
								$term->parent = array($region1);
								taxonomy_term_save($term);
							}
						}
					}
					else {
						$term = new stdClass();
						$term->name = $record['region1'];
						$term->vid = 3;
						$term->parent = array($region);
						taxonomy_term_save($term);
						if($record['region2'] != '' ){
							$region1 = $term->tid;
							$term = new stdClass();
							$term->name = $record['region2'];
							$term->vid = 3;
							$term->parent = array($region1);
							taxonomy_term_save($term);
						}
					}
				}
			}
			else {
				$term = new stdClass();
				$term->name = $record['region'];
				$term->vid = 3;
				taxonomy_term_save($term);
				
				if($record['region1'] != '') {
					$region = $term->tid;
					
					$term = new stdClass();
					$term->name = $record['region1'];
					$term->vid = 3;
					$term->parent = array($region);
					taxonomy_term_save($term);
					if($record['region2'] != '') {						
						$region1 = $term->tid;						
						$term = new stdClass();
						$term->name = $record['region2'];
						$term->vid = 3;
						$term->parent = array($region1);
						taxonomy_term_save($term);
					}
				}
			}
		}
	}
}

/*
* Finish callback for vehicle import batch process
*/

function import_finished_regions() {
	drupal_set_message(t('Your regions has been successfully imported'));
}




function import_unspsc_form($form, &$form_state) {
	/* 
	$result = db_query("SELECT vid FROM {taxonomy_vocabulary} WHERE name = :name", array(":name" => "region"))->fetchField();
	
	drupal_set_message($result);	 */
	
	$form['upload_csv'] = array(
	'#title' => t('Upload csv for unspsc'),
	'#type' => 'managed_file',
	'#required' => TRUE,
	'#upload_validators' => array(
       'file_validate_extensions' => array('csv'),
     ),
  );
	
  $form['submit'] = array(
	'#type' => 'submit',
	'#value' => t('Submit'),
  );
	
	return $form;
}


function import_unspsc_form_submit($form, &$form_state) {
	$file = file_load($form_state['values']['upload_csv']);
	
	$url = drupal_realpath($file->uri);
	
	
	$handle = fopen($url, 'r');
	
	$row = fgetcsv($handle);
	foreach ($row as $i => $header) {
		$columns[$i] = trim($header);
	}
	
	while($csv_line = fgetcsv($handle,1024)) {
		//$a = array();
    for ($i = 0, $j = count($csv_line); $i < $j; $i++) {
			$record[$columns[$i]] = $csv_line[$i];
    }
		$result[] = $record;
	}
	
	
	if (is_array($result) && $result) {
		$batch = array(
			'title' => t('Working ...'),
			'operations' => array(),
			'finished' => 'import_finished_regions',
			'init_message' => t('Starting ...'),
			'progress_message' => t('Processed @current out of @total.'),
			'error_message' => t('An error occurred during processing'),
			'progressive' => FALSE,
			'file' => drupal_get_path('module', 'm6connect_misc') . '/includes/m6connect_misc.inc',
		);
		
		$progress = 0; // where to start
		$limit = 10; // how many to process for each run
		$max = count($result); // how many records to process until stop - can do query here to get max times to run
		while ($progress <= $max) {
			$batch['operations'][] = array('import_unspsc_batch_process', array($progress, $limit, array_slice($result, $progress, $limit)));
			$progress = $progress + $limit;
		}		
		batch_set($batch);
		
		batch_process('admin/UNSPSC');
  }
  else {
    drupal_set_message(t("Oops ! An error occured !"), 'error');
  }
}



/*
* Batch process callback for import regions
*/

function import_unspsc_batch_process($progress, $limit, $result, &$context) {
	$vid = 6;
	foreach($result as $key => $record) {
	   drupal_set_message("<pre>". print_r($record,1));
		if($record['Segment Title'] != '') {
			if($segment = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['Segment Title'], ":parent" => 0,":vid" => $vid))->fetchField()) {
				if($record['Family Title'] != '') {
					if($family = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['Family Title'], ":parent" => $segment,":vid" => $vid))->fetchField()) {
						if($record['Class Title'] != '') {
							if($class_title = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['Class Title'], ":parent" => $family,":vid" => $vid))->fetchField()) {
								if($record['Commodity Title'] != '') {
									if($commodity = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['Commodity Title'], ":parent" => $class_title,":vid" => $vid))->fetchField()) {
										
									}
									else {
										$term = new stdClass();
										$term->name = $record['Commodity Title'];
										$term->vid = $vid;
										$term->parent = array($class_title);
										taxonomy_term_save($term);
									}
								}
							}
							else {
								$term = new stdClass();
								$term->name = $record['Class Title'];
								$term->vid = $vid;
								$term->parent = array($family);
								taxonomy_term_save($term);
							}
						}
					}
					else {
						$term = new stdClass();
						$term->name = $record['Family Title'];
						$term->vid = $vid;
						$term->parent = array($segment);
						taxonomy_term_save($term);
					}
				}
			}
			else {
				$term = new stdClass();
				$term->name = $record['Segment Title'];
				$term->vid = $vid;
				taxonomy_term_save($term);
			}
		}
		//drupal_set_message("<pre>". print_r($record,1));
	}
}	



function import_naics_form($form, &$form_state) {

	
	$form['upload_csv'] = array(
	'#title' => t('Upload csv for naics'),
	'#type' => 'managed_file',
	'#required' => TRUE,
	'#upload_validators' => array(
       'file_validate_extensions' => array('csv'),
     ),
  );
	
  $form['submit'] = array(
	'#type' => 'submit',
	'#value' => t('Submit'),
  );
	
	return $form;
}

function import_naics_form_submit($form, &$form_state) {
	$file = file_load($form_state['values']['upload_csv']);
	
	$url = drupal_realpath($file->uri);
	
	
	$handle = fopen($url, 'r');
	
	$row = fgetcsv($handle);
	foreach ($row as $i => $header) {
		$columns[$i] = trim($header);
	}

	while($csv_line = fgetcsv($handle,1024)) {
		//$a = array();
    for ($i = 0, $j = count($csv_line); $i < $j; $i++) {
			$record[$columns[$i]] = $csv_line[$i];
    }
		$result[] = $record;
	}
	
	
	if (is_array($result) && $result) {
		$batch = array(
			'title' => t('Working ...'),
			'operations' => array(),
			'finished' => 'import_finished_regions',
			'init_message' => t('Starting ...'),
			'progress_message' => t('Processed @current out of @total.'),
			'error_message' => t('An error occurred during processing'),
			'progressive' => FALSE,
			'file' => drupal_get_path('module', 'm6connect_misc') . '/includes/m6connect_misc.inc',
		);
		
		$progress = 0; // where to start
		$limit = 10; // how many to process for each run
		$max = count($result); // how many records to process until stop - can do query here to get max times to run
		while ($progress <= $max) {
			$batch['operations'][] = array('import_naics_batch_process', array($progress, $limit, array_slice($result, $progress, $limit)));
			$progress = $progress + $limit;
		}		
		batch_set($batch);
		
		batch_process('admin/naics');
  }
  else {
    drupal_set_message(t("Oops ! An error occured !"), 'error');
  }
}


/*
* Batch process callback for import naics
*/

function import_naics_batch_process($progress, $limit, $result, &$context) {
	$vid = 5;
	foreach($result as $key => $record) {
		//drupal_set_message("<pre>". print_r($record,1));
		if($record['naics'] != '') {
			$naics = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['naics'], ":parent" => 0,":vid" => $vid))->fetchField();
			if($naics != '') {
				if($record['naics1'] != '') {
					$naics1 = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['naics1'], ":parent" => $naics,":vid" => $vid))->fetchField();
					if($naics1 != '') {
						if($record['naics2'] != '') {
							$naics2 = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['naics2'], ":parent" => $naics1,":vid" => $vid))->fetchField();
							if($naics2 != '') {
								if($record['naics3'] != '') {
									$naics3 = db_query("SELECT ttd.tid FROM taxonomy_term_data ttd INNER JOIN taxonomy_term_hierarchy tth ON ttd.tid = tth.tid WHERE ttd.name LIKE :region AND tth.parent = :parent AND ttd.vid = :vid", array(":region" => $record['naics3'], ":parent" => $naics2,":vid" => $vid))->fetchField();
									if($naics3 != '') {
									}
									else {
										$term = new stdClass();
										$term->name = $record['naics3'];
										$term->vid = $vid;
										$term->parent = array($naics2);
										taxonomy_term_save($term);
									}
								}
							}
							else {
								$term = new stdClass();
								$term->name = $record['naics2'];
								$term->vid = $vid;
								$term->parent = array($naics1);
								taxonomy_term_save($term);
							}
						}
					}
					else {
						$term = new stdClass();
						$term->name = $record['naics1'];
						$term->vid = $vid;
						$term->parent = array($naics);
						taxonomy_term_save($term);
					}
				}
			}
			else {
				$term = new stdClass();
				$term->name = $record['naics'];
				$term->vid = $vid;
				taxonomy_term_save($term);
			}
		}
	}
}