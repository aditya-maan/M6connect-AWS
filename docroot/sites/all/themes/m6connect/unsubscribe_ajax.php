<?php
//error_reporting(0);
//require_once("../../../default/settings.php");
require_once("../../../default/settings_dbconn.php");
$dbObject 	=  new dbconn;

/******* plan unsubscribe *****/
$user_unsubscribe_id = "";
$user_unsubscribe_id = $_REQUEST['user_subscribe'];
if($user_unsubscribe_id != "")
{
	$sql = $dbObject->query("SELECT uid, rid FROM users_roles where uid = $user_unsubscribe_id AND rid NOT IN (1, 2, 3, 5, 6)", 4);
	$sql_update_order =  $dbObject->action_query("UPDATE uc_orders SET order_status='canceled' WHERE uid=$user_unsubscribe_id AND order_status='completed'", 1);
	$sql_delete = $dbObject->action_query("DELETE FROM users_roles where uid =$user_unsubscribe_id AND rid NOT IN (1, 2, 3, 5, 4, 6)");
	$sql_default_role = $dbObject->query("SELECT * FROM users_roles where uid =$user_unsubscribe_id", 4) ;
	echo count($sql_default_role);
	if (count($sql_default_role) > 0)
	{		
	   	$my_role[] =  "{$sql_default_role[0]['rid']}";	
		if ((in_array(3, $my_role) == 1)||(in_array(6, $my_role) ==1) ||(in_array(5, $my_role) ==1))
		{		
			$sql_free_role_insert = "";
		}
		else
		{		
			$sql_free_role_insert =  $dbObject->action_query("INSERT INTO users_roles (uid, rid) VALUES ($user_unsubscribe_id, 4)");
		}
	}
	else
	{	
		$sql_free_role_insert =  $dbObject->action_query("INSERT INTO users_roles (uid, rid) VALUES ($user_unsubscribe_id, 4)");
	}	
}
/******* plan choosing ajax data *****/
$user_plan_id = $_REQUEST['data_plan'];
if($user_plan_id != "")
{
	$sql_product_select = $dbObject->query("SELECT nid, model, sell_price FROM uc_products where nid= $user_plan_id", 4);
	$plan_data = "";
	if (count($sql_product_select) > 0) {
      $plan_data = $sql_product_select[0]['nid']."@@";
	  $plan_data .= $sql_product_select[0]['model']."@@";
	  $plan_data .= $sql_product_select[0]['sell_price'];
    }  
	echo $plan_data;
}
?>