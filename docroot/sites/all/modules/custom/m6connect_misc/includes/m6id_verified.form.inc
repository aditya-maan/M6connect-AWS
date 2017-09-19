<?php

function m6id_verified_form($form,&$form_state){
  $form['m6id_container_one']= array(
    '#type' => 'container',
	'#attributes'=> array('class'=> array('m6id_container_one_inner','m6id_container_one_login')),
	'#prefix' => '<div class="m6id_container_one_section m6id_container_section">',
	'#suffix' => '</div>',
  );
  $form['m6id_container_two']= array(
    '#type' => 'container',
	'#attributes'=> array('class'=> array('m6id_container_one_inner','m6id_container_one_login')),
	'#prefix' => '<div class="m6id_container_one_section m6id_container_section">',
	'#suffix' => '</div>',
  );
  $form['m6id_container_three']= array(
    '#type' => 'container',
	'#attributes'=> array('class'=> array('m6id_container_one_inner','m6id_container_one_login')),
	'#prefix' => '<div class="m6id_container_one_section m6id_container_section">',
	'#suffix' => '</div>',
  );
  $form['m6id_container_four']= array(
    '#type' => 'container',
	'#attributes'=> array('class'=> array('m6id_container_one_inner','m6id_container_one_login')),
	'#prefix' => '<div class="m6id_container_one_section m6id_container_section">',
	'#suffix' => '</div>',
  );
  return $form;	
}

