<?php
	include 'inc/time.inc';
	include 'inc/html_function.inc';
	include 'inc/mysql_function.inc';
	include 'subsystem_file/aressystem/aressystem.inc';

	HTML_PrintHeader('E1039 slow control SUBSYSTEM AresSystem', True, "AresSystem");
	mysql_MakeConnection($link);
	
	Time_PrintTimeSelector($utime0, $utime1);

	ares_HTML_PrintLastMeasurement();
	
	ares_HTML_dump_plane_list();
	

	$fetch_data = ares_mysql_FetchData($link, $utime0, $utime1);

	ares_HTML_PrintMeasurementTable();
	

	ares_fetch_draw($fetch_data);



	HTML_PrintRear();
?>
