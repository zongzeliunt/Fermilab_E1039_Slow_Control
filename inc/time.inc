<?php
	/*
	#SAMPLE CODE 0
	//{{{
	#echo "today: ". date("y/m/d"). "<br>";
	#echo "today: ". date("y.m.d"). "<br>";
	#echo "today: ". date("y-m-d"). "<br>";
	#echo "today: ". date("l"). "<br>"; //week day
	#$date = date('y/m/d h:i:s', $time);
	#echo "time: ". $date. "<br>";
	#echo "time: ". time(). "<br>"; //generate time stamp
	#$temp=explode(" ",$date); 
	#echo $temp[0];
	//}}}
	*/

	/*
	#SAMPLE CODE 1 
	//{{{
	#1561739264
	#2019/6/28 10:27:44

	#$time_stamp = "1561739664";
	#2019/6/28 10:34:24
	

	echo now_time() . "<br>";	
	echo time_stamp_date($time_stamp) . "<br>";	
	echo time_stamp_time($time_stamp) . "<br>";	

	$y= 2019;
	$mo=6;
	$d=28;
	$h=10;
	$mi=34;
	$s=24;
	$result_time_stamp = input_time_to_time_stamp ($y, $mo, $d, $h, $mi, $s);
	echo $result_time_stamp . "<br>";
	//}}}
	*/

	/*
	#SAMPLE CODE 2 
	//{{{
	$dati0 = new DateTime();
	$dati1 = new DateTime();
	$tzoff = $dati0->getOffset();
	if (isset($_GET['Y0'])) { // assume all the time variables are set
	   $Y0 = $_GET['Y0'];   $M0 = $_GET['M0'];   $D0 = $_GET['D0'];
	   $Y1 = $_GET['Y1'];   $M1 = $_GET['M1'];   $D1 = $_GET['D1'];
	   $h0 = $_GET['h0']; //  $m0 = $_GET['m0'];   $s0 = $_GET['s0'];
	   $h1 = $_GET['h1']; //  $m1 = $_GET['m1'];   $s1 = $_GET['s1'];
	   $m0 = $s0 = 0;
	   $m1 = $s1 = 0;
	   $dati0->setDate ($Y0, $M0, $D0);   $dati0->setTime ($h0, $m0, $s0);
	   $dati1->setDate ($Y1, $M1, $D1);   $dati1->setTime ($h1, $m1, $s1);
	} else {
	   $dati1->setTimestamp($dati1->getTimestamp() + 3600); // rounded up at hour
	   $dati1->setTime();
	   $Y1 = $dati1->format('Y');
	   $M1 = $dati1->format('m');
	   $D1 = $dati1->format('d');
	   $h1 = $dati1->format('H');
	   $m1 = '00'; // $dati1->format('i');
	   $s1 = '00'; // $dati1->format('s');
	   $dati1->setTime($h1, 0, 0);
	
	   $dati0->setTimestamp($dati1->getTimestamp() - 24*3600); // 1 day
	   $Y0 = $dati0->format('Y');
	   $M0 = $dati0->format('m');
	   $D0 = $dati0->format('d');
	   $h0 = $dati0->format('H');
	   $m0 = $dati0->format('i');
	   $s0 = $dati0->format('s');
	
	   echo '<script type="text/javascript">',
	        '  document.getElementById("auto_refresh").checked = true;',
	        '</script>',"\n";
	}
	$utime0 = $dati0->getTimestamp();
	$utime1 = $dati1->getTimestamp();
	//}}}
	*/


	//{{{
    function now_time()
    {
      return time();
    }

	function time_stamp_date($time_stamp) 
	{
		$date = date('y/m/d h:i:s', $time_stamp);
		$temp=explode(" ",$date); 
		return $temp[0];
	}

	function time_stamp_time($time_stamp) 
	{
		$date = date('y/m/d h:i:s', $time_stamp);
		$temp=explode(" ",$date); 
		return $temp[1];
	}

	function input_time_to_time_stamp ($y, $mo, $d, $h, $mi, $s)
	{
		$result = mktime($h, $mi, $s, $mo, $d, $y);
		return $result;
	}
	//}}}	

	function Time_PrintTimeSelector(&$utime0, &$utime1)
	//{{{
	{
		$dati0 = new DateTime();
		$dati1 = new DateTime();
		if (isset($_GET['Y0'])) { // assume all the time variables are set
		   $Y0 = $_GET['Y0'];   $M0 = $_GET['M0'];   $D0 = $_GET['D0'];
		   $Y1 = $_GET['Y1'];   $M1 = $_GET['M1'];   $D1 = $_GET['D1'];
		   $h0 = $_GET['h0']; //  $m0 = $_GET['m0'];   $s0 = $_GET['s0'];
		   $h1 = $_GET['h1']; //  $m1 = $_GET['m1'];   $s1 = $_GET['s1'];
		   $m0 = $_GET['m0'];
		   $m1 = $_GET['m1'];
		   $s0 = 0;
		   $s1 = 0;
		   $dati0->setDate ($Y0, $M0, $D0);   $dati0->setTime ($h0, $m0, $s0);
		   $dati1->setDate ($Y1, $M1, $D1);   $dati1->setTime ($h1, $m1, $s1);
		} else {
		   $dati1->setTimestamp($dati1->getTimestamp() + 3600); // rounded up at hour
		   $dati1->setTime();
		   $Y1 = $dati1->format('Y');
		   $M1 = $dati1->format('m');
		   $D1 = $dati1->format('d');
		   $h1 = $dati1->format('H');
		   $m1 = '00'; // $dati1->format('i');
		   $s1 = '00'; // $dati1->format('s');
		   $dati1->setTime($h1, 0, 0);
		
		   $dati0->setTimestamp($dati1->getTimestamp() - 24*3600); // 1 day
		   $Y0 = $dati0->format('Y');
		   $M0 = $dati0->format('m');
		   $D0 = $dati0->format('d');
		   $h0 = $dati0->format('H');
		   $m0 = $dati0->format('i');
		   $s0 = $dati0->format('s');
		   echo '<script type="text/javascript">',
				'  document.getElementById("auto_refresh").checked = true;',
				'</script>',"\n";
		}
		$utime0 = $dati0->getTimestamp();
		$utime1 = $dati1->getTimestamp();
		echo '<script type="text/javascript">',
		   ' var utime_begin = ',$utime0,';',
		   ' var utime_end   = ',$utime1,';',
		   '</script>',"\n";
	
		PrintTimeSelectBox($Y0, $Y1, $M0, $M1, $D0, $D1, $h0, $h1, $m0, $m1, $s0, $s1);
	//}}}
	}


	function PrintTimeSelectBox	($Y0, $Y1, $M0, $M1, $D0, $D1, $h0, $h1, $m0, $m1, $s0, $s1)
	{
		//{{{
		echo <<<EOT
			<div align="center"> <form style="display: inline;" method="get"> 
			    <b>| Time Range: </b>
			   <input type="text" size="4" name="Y0" value="$Y0">/<input type="text" size="2" name="M0" value="$M0">/<input type="text" size="2" name="D0" value="$D0">
			   <input type="text" size="2" name="h0" value="$h0">h 
			   <input type="text" size="2" name="m0" value="$m0">m 
				...
			   <input type="text" size="4" name="Y1" value="$Y1">/<input type="text" size="2" name="M1" value="$M1">/<input type="text" size="2" name="D1" value="$D1">
			   <input type="text" size="2" name="h1" value="$h1">h
			   <input type="text" size="2" name="m1" value="$m1">m
			   <b>|</b>
			   <b>|</b> <input type="submit" value="S h o w"> <b>|</b>
			</form> </div>
		EOT;
		//}}}
	}

?>
