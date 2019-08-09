<?php

function mysql_MakeConnection(&$link)
//{{{
{
	
	$host = 'localhost';
	$user = 'ares';
	$pass = "";
	$db = "fermilab";
	$link = mysqli_connect($host, $user, $pass, $db);
	if (!link) {
		die('connect fail' . mysql_error());
	}

   SelectDB($link, $db);
}
//}}}

function SelectDB($link, $db)
//{{{
{
   mysqli_select_db($link, $db) or
      die("<em>!!ERROR!!</em><p>Failed in selecting '".$db."' via mysql_select_db.  Most likely the schema doesn't exist.\n");
}
//}}}



?>
