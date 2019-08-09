<?php


//CONST
//{{{
$TABLE_DAT = 'mysubsystem';
$GROUP_LIST = array('spill', 'device_0', 'device_1');


//}}}

function ares_HTML_dump_plane_list()
//{{{
{
    global $GROUP_LIST;
	echo '<script type="text/javascript">',
	   " var plane_list = JSON.parse('",json_encode($GROUP_LIST),"');",
	   '</script>',"\n";
}
//}}}

function ares_mysql_FetchData($link, $utime0, $utime1)
//{{{
{
    global $GROUP_LIST, $TABLE_DAT;
	$utime_begin = $utime0;
	$utime_end   = $utime1;
	//$sampling    = $_POST['sampling'];
	/*
	echo "ARES!!!! ares mysql_FetchData<br>";
	echo "begin time: ".$utime_begin ." ". date('y/m/d h:i:s', $utime_begin). "<br>";
	echo "end time: ".$utime_end . " ". date('y/m/d h:i:s', $utime_end). "<br>";
	echo "<br><br>";
	*/

	$n_ch = count($GROUP_LIST);

	$query = 'SELECT UNIX_TIMESTAMP(ts)';
	foreach ($GROUP_LIST as $group) {
		$query .= ', '.$group;
	}
	$query .= '  FROM '.$TABLE_DAT.' WHERE true ';
	if ($utime_begin) $query .= ' and UNIX_TIMESTAMP(ts) > '.$utime_begin;
	if ($utime_end)   $query .= ' and UNIX_TIMESTAMP(ts) < '.$utime_end;
	$query .= ' order by ts;';

	$result = mysqli_query($link, $query);
	if (!$result) { die('Failed to execute a query:  '.mysqli_error($link)); }
	
	$values = array();
	for ($i_ch = 0; $i_ch < $n_ch; $i_ch++) $values[] = array();



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


function ares_HTML_PrintMeasurementTable()
//{{{
{
    global $GROUP_LIST;
	/*
    echo '<table class="last">';
    echo '    <tr>';
    echo '        <th>表头信息</th>';
    echo '        <th>表头信息</th>';
    echo '    </tr>';
    echo '    <tr>';
    echo '        <td>1-1</td>';
    echo '        <td>1-2</td>';
    echo '    </tr>';
    echo '    <tr>';
    echo '        <td>2-1</td>';
    echo '        <td>2-2</td>';
    echo '    </tr>';
    echo '</table>';
	*/

	//th is head, tr is row, td is colnum
	
	//table class are in local.css
	echo '<table class="last">',"\n";
	echo '<tr>'; 
	foreach ($GROUP_LIST as $group) {
		echo '	<th>',$group,'</th>';
	}
	echo '</tr>';
	echo '<tr>'; 
	foreach ($GROUP_LIST as $group) {
		echo '	<td><div id="last_',$group,'">last_',$group,'</div></td>';
	}
	echo '</tr>';
	echo '</table>';
	


	//table ares is in local.css
	foreach ($GROUP_LIST as $group) {
		if ($group == "spill") {
			continue;
		}
	   echo '<table class="ares"> ';
	   echo '<tr> <td><h2>',$group,'</h2></td>';
	   echo '<tr> <td><div id="gr_',$group,'" style="width:95%; height:400px;"></div></td></tr>';

	   echo "</table>\n";
	}
}
//}}}

function ares_HTML_PrintLastMeasurement()
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

function ares_fetch_draw($fetch_data)
//{{{
{
//I don't need the time range here, utime_begin and utime_end are all write to html part, calling JS functions will automatically use these time range values.
echo <<<EOT
    <script language="javascript">
		Ares_JS_FetchAndDraw($fetch_data)
		Ares_JS_DrawData($fetch_data)
	</script>
EOT;
}
//}}}



?>
