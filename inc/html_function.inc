<?php
function HTML_PrintHeader($title, $show_refresh_menu, $sub_system = "")
{
   echo <<<EOT
   <html>
   <head>
     <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
     <script language="javascript" type="text/javascript" src="javascript/jquery/jquery.js"></script>
     <script language="javascript" type="text/javascript" src="javascript/flot/jquery.flot.js"></script>
     <script language="javascript" type="text/javascript" src="javascript/flot/jquery.flot.selection.js"></script>
     <script language="javascript" type="text/javascript" src="script.js"></script>
EOT;

	if ($sub_system == "chamber") {
		echo "\n";
	 	echo '	<script language="javascript" type="text/javascript" src="subsystem_file/chamber/chamber.js"></script>';
		echo "\n";
	}
	if ($sub_system == "AresSystem") {
		echo "\n";
	 	echo '	<script language="javascript" type="text/javascript" src="subsystem_file/aressystem/aressystem.js"></script>';
		echo "\n";
	}


   echo <<<EOT
     <link href="local.css" rel="stylesheet" type="text/css">
     <title>$title</title>
   </head>
   <body>

   <h1><a class="title" href="?">$title</a>
       <div style="text-align: right;  font-size: 50%;  float: right;"><a class="title" href=".">[top]</a></div></h1>

	<div align="center"><b>| <a href="main.php">Main</a> | | <a href="conf-overview.php">Config</a> | | <a href="help.php">Help</a> | </b> </div>

EOT;
	
	if ($sub_system == "main") {
		echo '<div align="center"><b>| <a href="chamber.php">Chamber</a> | <a href="AresSystem.php">AresSystem</a> | </b><br></div>';
	}
   echo <<<EOT
	<div align="center">
	<b>Current_time:</b><p id=current_time>current_time</p>
	<script language="JavaScript">JS_ShowCurrentTime()</script> 
	</div>
EOT;

   if ($show_refresh_menu) {
		show_auto_refresh();
   }
}

function show_auto_refresh () {
echo <<<EOT
	<div align ="center">
	<script language="javascript"> 
		var refresh_interval = 10;
		var time_to_refresh = refresh_interval;
	</script>
	<br>

   	<b>|</b>
      <input type="checkbox" id="auto_refresh">
      <b>Auto-refresh</b> in <span id=counter> </span> sec.
	  <script language="JavaScript">JS_CountDown()</script> 
	<b>|</b>
	<!--
	<script language="javascript"> 
      document.getElementById("auto_refresh").checked ;
	</script>
	-->
	</div>
EOT;

}


function HTML_MainGlobalMessage () {
	$message_list = get_broad_cast_message();
echo <<<EOT
	<div align="center">
	<textarea rows="10" cols="30">
	Broadcast message
EOT;
	echo "\n";
	for ($i = 0; $i < count($message_list); $i ++ ) {
		echo $message_list[$i];
	}
echo <<<EOT
	</textarea>
	</div>
EOT;
}

function get_broad_cast_message () {
	$fl = fopen("broadcast.txt", "r");

	$message_list = [];
	for ($i = 0; $i < 10; $i ++ ) {
		$line = fgets($fl);
		if (feof($fl)) {
			break;
		}
		array_push($message_list, $line);
	}
	fclose($fl);
	return $message_list;
}

function HTML_PrintRear() {
echo <<<EOT
	</body>
	</html>
EOT;
}



?>
