
<?php
	include 'inc/time.inc';
	include 'inc/html_function.inc';
	include 'inc/mysql_function.inc';
	include 'subsystem_file/chamber/chamber.inc';

	HTML_PrintHeader('E1039 slow control SUBSYSTEM CHAMBER', True, "chamber");

	mysql_MakeConnection($link);
	chamber_mysql_FetchConf($link, $param);

	//this function DrawLastMeas has been copied to javascript/tmp/chamber.js
		//I wish to create a config file, but I can't always get root access to write into /javascript/tmp/chamber_conf.js
		//so if in the future the configuration changed, I can delete DrawLastMeas from javascript/tmp/chamber.js and open this function call
	//chamber_mysql_CreateScriptForLastMeas($link, $param);

	Time_PrintTimeSelector($utime0, $utime1);
	chamber_HTML_PrintLastMeasurement();
	
	chamber_HTML_dump_plane_list();

	$fetch_data = chamber_mysql_FetchData($link, $utime0, $utime1);
	
	chamber_HTML_PrintMeasurementTable();

	chamber_fetch_draw($fetch_data);


	HTML_PrintRear();
?>
