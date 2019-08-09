
function chamber_JS_FetchAndDraw(data) {
//{{{
	JS_ConvertData (data);
	DrawLastMeas(data);
}
//}}}

function DrawLastMeas(data) {
//{{{
    SetLastMeasV(data[0], "D1U", 1.35, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[6], "D1U", 1, 4);
    SetLastMeasV(data[1], "D1Up", 1.35, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[7], "D1Up", 1, 4);
    SetLastMeasV(data[2], "D1X", 1.35, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[8], "D1X", 1, 4);
    SetLastMeasV(data[3], "D1Xp", 1.35, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[9], "D1Xp", 1, 4);
    SetLastMeasV(data[4], "D1V", 1.35, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[10], "D1V", 1, 4);
    SetLastMeasV(data[5], "D1Vp", 1.35, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[11], "D1Vp", 1, 4);
    SetLastMeasV(data[12], "D2V", 1.61, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[18], "D2V", 1, 4);
    SetLastMeasV(data[13], "D2Vp", 1.61, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[19], "D2Vp", 1, 4);
    SetLastMeasV(data[14], "D2Xp", 1.61, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[20], "D2Xp", 1, 4);
    SetLastMeasV(data[15], "D2X", 1.61, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[21], "D2X", 1, 4);
    SetLastMeasV(data[16], "D2U", 1.64, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[22], "D2U", 1, 4);
    SetLastMeasV(data[17], "D2Up", 1.64, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[23], "D2Up", 1, 4);
    SetLastMeasV(data[24], "D3pV", 2.23, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[28], "D3pV", 1, 4);
    SetLastMeasV(data[25], "D3pX", 2.23, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[29], "D3pX", 1, 4);
    SetLastMeasV(data[26], "D3pU", 2.23, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[30], "D3pU", 1, 4);
    SetLastMeasV(data[27], "D3pG", 1.4, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[31], "D3pG", 1, 4);
    SetLastMeasV(data[32], "D3mV", 2.23, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[36], "D3mV", 1, 4);
    SetLastMeasV(data[33], "D3mX", 2.23, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[37], "D3mX", 1, 4);
    SetLastMeasV(data[34], "D3mU", 2.23, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[38], "D3mU", 1, 4);
    SetLastMeasV(data[35], "D3mG", 1.4, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[39], "D3mG", 1, 4);
    SetLastMeasV(data[40], "P4V1", 1.85, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[44], "P4V1", 1, 4);
    SetLastMeasV(data[41], "P4H1", 1.85, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[45], "P4H1", 1, 4);
    SetLastMeasV(data[42], "P4V2", 1.85, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[46], "P4V2", 1, 4);
    SetLastMeasV(data[43], "P4H2", 1.85, -0.01, -0.005, 0.005, 0.01);
    SetLastMeasI(data[47], "P4H2", 1, 4);
}
//}}}

function chamber_JS_DrawData(data) {
//{{{
    var axis_fmt;
    var sampling;
    var days = (utime_end - utime_begin) / (24.0*60*60);
	alert("DrawData ares");
	
    if      (days <=0.5) { axis_fmt =       '%Hh%Mm';  sampling =  1; }
    else if (days <=  1) { axis_fmt =       '%Hh'   ;  sampling =  1; }
    else if (days <=  3) { axis_fmt =    '%d %Hh'   ;  sampling =  1; }
    else if (days <=  7) { axis_fmt = '%m/%d %Hh'   ;  sampling =  2; }
    else if (days <= 14) { axis_fmt = '%m/%d'       ;  sampling =  3; }
    else                 { axis_fmt = '%m/%d'       ;  sampling = 10; }

    var date_begin = new Date(1000*utime_begin);
    var date_end   = new Date(1000*utime_end  );
    var date_now   = new Date();
    $("#status").html( 'Fetching records from database server...' );
		//Tag #status is declared in HTML_PrintLastMeasurement
	var npt = data[0].length;
	var time_last = data[0][npt-1][0] * 1000;
	var date_last = new Date(time_last);

	$("#time_last").html( " @ " + JS_FormatDateTime(date_last) );

	/*
	//Keep this but not useful
	$("#time_last_warning").html("");
	if (sampling == 1) {
	   var minutes_warn = 15;
	   var minutes_noup = (date_now.getTime() - time_last) / 6e4; // msec -> minute
	   if (minutes_noup > minutes_warn) {
		  $("#time_last_warning").html(" !! No record for last " + Math.floor(minutes_noup) + " minutes !!");
	   }
	}
	*/
	$("#status").html( 'Drawing plots...' );
	var options = { xaxis: { mode: "time", timeformat: axis_fmt }, 
					selection: { mode: "y" }, 
					legend: { position: 'nw' }, 
					//lines: { show: false },  points: { show: true } 
		  };
	var idx_data = 0;
	var idx_plot = 0;
	for (let group in plane_list) {
	   for (let type of ['V', 'I']) {
		  var list_data = [];
		  for (let plane of plane_list[group]) {
			 list_data.push( { label: plane,  data: data[idx_data] } );
			 idx_data++;
		  }
		  let place = $("#gr_"+group+"_"+type);
		  let plot  = $.plot(place, list_data, options);
		  place.bind("plotselected", function(event, ranges) {
				$.each(plot.getYAxes(), function(_, axis) {
					  var opts = axis.options;
					  opts.min = ranges.yaxis.from;
					  opts.max = ranges.yaxis.to;
				   });
				plot.setupGrid();
				plot.draw();
				plot.clearSelection();
			 });
		  place.dblclick(function () {
				$.each(plot.getYAxes(), function(_, axis) {
					  var opts = axis.options;
					  opts.min = null;
					  opts.max = null;
				   });
				plot.setupGrid();
				plot.draw();
			 });
		  idx_plot++;
	   }
	}

	var str_stat = "Checked at <b>" + JS_FormatDateTime(date_now) + "</b>.  " + npt + " records.";
	if (sampling > 1) str_stat += "  Sampled down by " + sampling + ".";
	$("#status").html(str_stat);

	alert("DrawData done");
}
//}}}

function SetLastMeasV(data, label, V, dVm_E, dVm_W, dVp_W, dVp_E) {
//{{{
    var Vm_E = V + dVm_E;
    var Vm_W = V + dVm_W;
    var Vp_W = V + dVp_W;
    var Vp_E = V + dVp_E;
    var V_last    = data[ data.length-1 ][1];
    var div_label = "#last_V_" + label;
    $(div_label).html(V_last.toFixed(3) + " kV");

    if      (V_last < Vm_E || V_last > Vp_E) { $(div_label).css("background-color", "red"        ); }
    else if (V_last < Vm_W || V_last > Vp_W) { $(div_label).css("background-color", "yellow"     ); }
    else                                     { $(div_label).css("background-color", "transparent"); }
}
//}}}

function SetLastMeasI(data, label, I_W, I_E) {
//{{{
	var I_last    = data[ data.length-1 ][1];
    var div_label = "#last_I_" + label;
    $(div_label).html(I_last.toFixed(3) + " &mu;A");

    if      (I_last > I_E) { $(div_label).css("background-color", "red"        ); }
    else if (I_last > I_W) { $(div_label).css("background-color", "yellow"     ); }
    else                   { $(div_label).css("background-color", "transparent"); }
}
//}}}
