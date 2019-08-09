<?php
//CONST
//{{{
$TABLE_DAT = 'hvmon_cham_fy2018';
$TABLE_CONF = 'hvmon_cham_fy2018_conf';
$GROUP_LIST = array( 'D1', 'D2', 'D3p', 'D3m', 'P4' );
$PLANE_LIST = array(
   'D1'  => array( 'U' , 'Up', 'X' , 'Xp', 'V', 'Vp' ),
   'D2'  => array( 'V' , 'Vp', 'Xp', 'X' , 'U', 'Up' ),
   'D3p' => array( 'V' , 'X' , 'U' , 'G'  ),
   'D3m' => array( 'V' , 'X' , 'U' , 'G'  ),
   'P4'  => array( 'V1', 'H1', 'V2', 'H2' ),
);




$DMM_CH_V = array(
   'D1'  => array( 'U'  => 101, 'Up' => 102, 'X'  => 103, 'Xp' => 104, 'V' => 105, 'Vp' => 106 ),
   'D2'  => array( 'V'  => 201, 'Vp' => 202, 'Xp' => 203, 'X'  => 204, 'U' => 205, 'Up' => 206 ),
   'D3p' => array( 'V'  => 301, 'X'  => 302, 'U'  => 303, 'G'  => 304 ),
   'D3m' => array( 'V'  => 311, 'X'  => 312, 'U'  => 313, 'G'  => 314 ),
   'P4'  => array( 'V1' => 213, 'H1' => 214, 'V2' => 215, 'H2' => 216 ),
   );
$DMM_CH_I = array(
   'D1'  => array( 'U'  => 107, 'Up' => 108, 'X'  => 109, 'Xp' => 110, 'V' => 111, 'Vp' => 112 ),
   'D2'  => array( 'V'  => 207, 'Vp' => 208, 'Xp' => 209, 'X'  => 210, 'U' => 211, 'Up' => 212 ),
   'D3p' => array( 'V'  => 305, 'X'  => 306, 'U'  => 307, 'G'  => 308 ),
   'D3m' => array( 'V'  => 315, 'X'  => 316, 'U'  => 317, 'G'  => 318 ),
   'P4'  => array( 'V1' => 217, 'H1' => 218, 'V2' => 219, 'H2' => 220 ),
   );
//}}}

function chamber_HTML_dump_plane_list()
//{{{
{
    global $GROUP_LIST, $PLANE_LIST;
	echo '<script type="text/javascript">',
	   " var plane_list = JSON.parse('",json_encode($PLANE_LIST),"');",
	   '</script>',"\n";
}
//}}}

function chamber_HTML_PrintMeasurementTable()
//{{{
{
    global $GROUP_LIST, $PLANE_LIST;
	echo '<table class="last">',"\n";
	foreach ($GROUP_LIST as $group) {
	   echo '<tr> <th rowspan="3" width="8%">',$group,'</th>';
	   foreach ($PLANE_LIST[$group] as $plane) echo '<th>',$plane,'</th>';
	   echo '</tr>  <tr>';
	   foreach ($PLANE_LIST[$group] as $plane) echo '<td><div id="last_V_',$group,$plane,'">?</div></td>';
	   echo '</tr>  <tr>';
	   foreach ($PLANE_LIST[$group] as $plane) echo '<td><div id="last_I_',$group,$plane,'">?</div></td>';
	   echo "</tr>\n";
	}
	echo "</table>\n";

	foreach ($GROUP_LIST as $group) {
	   echo '<table class="arr"> ';
	   echo '<tr> <td><h2>',$group,' &mdash; V (kV)</h2></td> <td><h2>',$group,' &mdash; I (&mu;A)</h2></td> </tr>';
	   echo '<tr> <td><div id="gr_',$group,'_V" style="width:95%; height:400px;"></div></td>  <td><div id="gr_',$group,'_I" style="width:95%; height:400px;"></div></td> </tr>';

	   echo "</table>\n";
	}
}
//}}}

function chamber_HTML_PrintLastMeasurement()
//{{{
{
	echo <<<EOT
	<p id="status">.</p>
	<h2>Last Measurement 
	  <div style="display: inline;" id="time_last"></div>
	  <div style="color: red;  display: inline;" id="time_last_warning"></div>
	</h2>
EOT;
}
//}}}

function chamber_mysql_FetchConf ($link, &$param, $ymd = '2099-12-31')
//{{{
{
	global $TABLE_CONF;
   $comm =
      'select A.plane, A.V, A.dVm_W, A.dVm_E, A.dVp_W, A.dVp_E, A.I_W, A.I_E, A.ts, A.person '.
      '  from '.$TABLE_CONF.' as A  where '.
      '    A.ts = (select max(B.ts) from '.$TABLE_CONF.' as B '.
      '               where A.plane = B.plane  and B.ts < "'.$ymd.' 23:59:59");';

   	$result = mysqli_query($link, $comm);

	if (!$result) die('Failed to execute a query:  '.mysqli_error($link));
	
   $param = array();
   while ($row = mysqli_fetch_row($result)) {
      $plane = $row[0];
      $param[$plane] = array(
         'V'      => $row[1], 
         'dVm_W'  => $row[2], 
         'dVm_E'  => $row[3], 
         'dVp_W'  => $row[4], 
         'dVp_E'  => $row[5], 
         'I_W'    => $row[6], 
         'I_E'    => $row[7], 
         'ts'     => $row[8], 
         'person' => $row[9], 
         );
	}
}
//}}}

function chamber_mysql_CreateScriptForLastMeas($link, $param)
//{{{
{
    global $GROUP_LIST, $PLANE_LIST;
	
	/*
	$myfile = fopen("javascript/tmp/chamber_conf.js", "w");
	fwrite($myfile, "function DrawLastMeas(data) {");

   	foreach ($GROUP_LIST         as $group) {
   		foreach ($PLANE_LIST[$group] as $plane) {
    	  	$idx_V = FindDataIndex($group, $plane, "V");
    	  	$idx_I = FindDataIndex($group, $plane, "I");
    	  	$name  = $group.$plane;
    	  	$V     = $param[$name]['V'];
    	  	$dVm_W = $param[$name]['dVm_W'];
    	  	$dVm_E = $param[$name]['dVm_E'];
    	  	$dVp_W = $param[$name]['dVp_W'];
    	  	$dVp_E = $param[$name]['dVp_E'];
    	  	$I_W   = $param[$name]['I_W'];
    	  	$I_E   = $param[$name]['I_E'];
			
			$txt = "	SetLastMeasV(data[,$idx_V,'], "',$name,'", ',$V,', ',$dVm_E,', ',$dVm_W,', ',$dVp_W,', ',$dVp_E,");"";	
			fwrite ($myfile, $txt);
    	  //echo '    SetLastMeasV(data[',$idx_V,'], "',$name,'", ',$V,', ',$dVm_E,', ',$dVm_W,', ',$dVp_W,', ',$dVp_E,");\n";
    	  //echo '    SetLastMeasI(data[',$idx_I,'], "',$name,'", ',$I_W,', ',$I_E,");\n";
   		}	
   	}
	fwrite($myfile, "}\n");
	fclose($myfile);
	*/

   echo
      '  <script type="text/javascript">',"\n",
      '  function DrawLastMeas(data) {',"\n";
   foreach ($GROUP_LIST         as $group) {
   foreach ($PLANE_LIST[$group] as $plane) {
      $idx_V = FindDataIndex($group, $plane, "V");
      $idx_I = FindDataIndex($group, $plane, "I");
      $name  = $group.$plane;
      $V     = $param[$name]['V'];
      $dVm_W = $param[$name]['dVm_W'];
      $dVm_E = $param[$name]['dVm_E'];
      $dVp_W = $param[$name]['dVp_W'];
      $dVp_E = $param[$name]['dVp_E'];
      $I_W   = $param[$name]['I_W'];
      $I_E   = $param[$name]['I_E'];
      echo '    SetLastMeasV(data[',$idx_V,'], "',$name,'", ',$V,', ',$dVm_E,', ',$dVm_W,', ',$dVp_W,', ',$dVp_E,");\n";
      echo '    SetLastMeasI(data[',$idx_I,'], "',$name,'", ',$I_W,', ',$I_E,");\n";
   }
   }
   echo "  }\n";
   echo "</script>\n";

}

function FindDataIndex($group, $plane, $type)
{
   global $GROUP_LIST, $PLANE_LIST;
   $offset_group = array( 0, 12, 24, 32, 40 );
   $offset_type  = ($type == "V"  ?  0  :  1);

   for ($ig = 0; $ig < count($GROUP_LIST); $ig++) {
      if ($GROUP_LIST[$ig] != $group) continue;
      $n_pl = count($PLANE_LIST[$group]);
      for ($ip = 0; $ip < $n_pl; $ip++) {
         if ($PLANE_LIST[$group][$ip] == $plane) return $offset_group[$ig] + $n_pl*$offset_type + $ip;
      }
   }
   return -1;
}
//}}}

function chamber_mysql_FetchData ($link, $utime0, $utime1)
//{{{
{
    global $GROUP_LIST, $PLANE_LIST, $TABLE_DAT;
	$utime_begin = $utime0;
	$utime_end   = $utime1;
	//$sampling    = $_POST['sampling'];
	echo "ARES!!!! mysql_FetchData<br>";
	echo "begin time: ".$utime_begin ." ". date('y/m/d h:i:s', $utime_begin). "<br>";
	echo "end time: ".$utime_end . " ". date('y/m/d h:i:s', $utime_end). "<br>";
	echo "<br><br>";

	$n_ch = 0;
	$query = 'SELECT UNIX_TIMESTAMP(timestamp)';
	foreach ($GROUP_LIST as $group) {
	   foreach ($PLANE_LIST[$group] as $plane) $query .= ', '.$group.$plane.'_V';
	   foreach ($PLANE_LIST[$group] as $plane) $query .= ', '.$group.$plane.'_I';
	   $n_ch += 2 * count($PLANE_LIST[$group]);
	}
	$query .= '  FROM '.$TABLE_DAT.' WHERE true ';
	
	/*
	echo $query."<br>";
	D1U_V, D1Up_V, D1X_V, D1Xp_V, D1V_V, D1Vp_V, 
	D1U_I, D1Up_I, D1X_I, D1Xp_I, D1V_I, D1Vp_I, 
	D2V_V, D2Vp_V, D2Xp_V, D2X_V, D2U_V, D2Up_V, 
	D2V_I, D2Vp_I, D2Xp_I, D2X_I, D2U_I, D2Up_I, 
	D3pV_V, D3pX_V, D3pU_V, D3pG_V, 
	D3pV_I, D3pX_I, D3pU_I, D3pG_I, 
	D3mV_V, D3mX_V, D3mU_V, D3mG_V, 
	D3mV_I, D3mX_I, D3mU_I, D3mG_I, 
	P4V1_V, P4H1_V, P4V2_V, P4H2_V, 
	P4V1_I, P4H1_I, P4V2_I, P4H2_I
	*/



	if ($utime_begin) $query .= ' and UNIX_TIMESTAMP(timestamp) > '.$utime_begin;
	if ($utime_end)   $query .= ' and UNIX_TIMESTAMP(timestamp) < '.$utime_end;
	//if ($sampling)    $query .= ' and id mod '.$sampling.' = 0';
	$query .= ' order by timestamp;';
	
	$result = mysqli_query($link, $query);
	if (!$result) { die('Failed to execute a query:  '.mysqli_error($link)); }
	
	$values = array();
	for ($i_ch = 0; $i_ch < $n_ch; $i_ch++) $values[] = array();

	/*	
	foreach ($GROUP_LIST as $group) {
		echo $group. ": ";
   		foreach ($PLANE_LIST[$group] as $plane){ 
			echo $plane. " ";
		}
		echo "<br>";
	}
	*/

	while ($row = mysqli_fetch_row($result)) {
	   $ts = $row[0];
	   for ($i_ch = 0; $i_ch < $n_ch; $i_ch++) {
	      $val = $row[$i_ch+1];
	      $values[$i_ch][] = array($ts, $val);
	   }
	}
	$close_flag = mysqli_close($link);
	if (! $close_flag) { print('<p>Dis-connection faild</p>'); }
	
	return json_encode($values);

}
//}}}

function chamber_fetch_draw($fetch_data)
//{{{
{
//I don't need the time range here, utime_begin and utime_end are all write to html part, calling JS functions will automatically use these time range values.
echo <<<EOT
    <script language="javascript">
		chamber_JS_FetchAndDraw($fetch_data)
		chamber_JS_DrawData($fetch_data)
	</script>
EOT;
}
//}}}

?>
