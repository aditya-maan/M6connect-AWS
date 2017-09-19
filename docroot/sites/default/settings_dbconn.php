<?php
/**
* Configuration Colan infotech 
*
*/
class dbconn
{
	var $conn; // This is the database connection resource.
	var $host;  //The database hostname.
	var $login;  //The databse server login name.
	var $pass; //The database server password.
	var $dbname;
	function query($query,$method)	{//start method query
		$finArr = array();
		$result = mysql_query($query,$this->conn) or die("Error".mysql_error());
		
		if (!$error = mysql_error())
		{
			if ($method == 1)
				return $result;
			elseif ($method == 2)	{			
				while ($currObj == mysql_fetch_assoc($result))
					$resultArray[] = $currObj;
					return $resultArray;//returns the double dimensional array containing all the results
			}
			elseif ($method == 3)	{
				$resArray = mysql_fetch_assoc($result);		
				return $resArray;//this is for single row results.
			}
			elseif($method == 4) { 
				while($reArray = mysql_fetch_array($result))
					$finArr[] = $reArray;
				return $finArr;//Added for getting result in a Array with numeric index and column name
			}
			elseif($method == 5) { 
				$nRows	= mysql_num_rows($result);
				return $nRows;//Added for getting just record count ie number of records fetched by the query 
			}
			elseif($method == 6) { 
				$resObject	= mysql_fetch_object($result);
				return $resObject;//Added for getting result in a Array as object 
			}
		}
		else
			return $error;
	}//end method query
	//Function to execute only action queries ie  INSERT,UPDATE and DELETE queries which wont return any result.
	function action_query($query,$return_insert_id='')
	{
		$result = mysql_query($query,$this->conn) or die("Error".mysql_error());
		if($return_insert_id != "")
		{
			return mysql_insert_id();
		}//end of if
	}//end of action_query
	//This is the constructor of the database object.
	function query1($query)
	{
		$result = mysql_query($query);	
		if (mysql_error())
		{
			return 0;
		}
		else
		{
			return $result;
		}
	}
	
	function dbconn()  	{	 
        global $conf;
		/*$dbserver	=	$_SERVER['DB_HOST'].":".$_SERVER['DB_PORT'];
		$dbuser		=	$_SERVER['DB_USER'];
		$dbpass		= 	$_SERVER['DB_PASSWORD'];
		$dbname		=	$_SERVER['DB_NAME'];*/
		
		// Acquia DB Settings
		$dbserver=$dbuser=$dbpass=$dbname=$db_port='';
		if(isset($conf['acquia_hosting_site_info'],$conf['acquia_hosting_site_info']['db'])){
		  $dbserver	    =	key($conf['acquia_hosting_site_info']['db']['db_url_ha']);
		  $dbuser		=	$conf['acquia_hosting_site_info']['db']['user'];
		  $dbpass		= 	$conf['acquia_hosting_site_info']['db']['pass'];
		  $dbname		=	$conf['acquia_hosting_site_info']['db']['name'];
		  $db_port      =   $conf['acquia_hosting_site_info']['db']['port'];	
		}
		
		$dbserver = $dbserver.':'.$db_port;
		
		$this->host = $dbserver;
 		$this->login = $dbuser;
		$this->pass = $dbpass;
		$this->dbname = $dbname;
		if ($this->conn = mysql_connect($this->host,$this->login,$this->pass) or die(mysql_error()))
		{
			mysql_select_db($this->dbname,$this->conn) or die(mysql_error()." in line ".__LINE__);
			return $this->conn; 
		}
		else
			die(mysql_error());				
	}
}
//end class

?>
