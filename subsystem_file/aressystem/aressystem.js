function alert_ares_ares_system() {
	alert("ARES system");
}


function Ares_JS_FetchAndDraw(data) {
//{{{
	JS_ConvertData (data);
	DrawLastMeas(data);
}
//}}}

function DrawLastMeas(data) {
//{{{
	setLastMeas (data[0], "spill");
	setLastMeas (data[1], "device_0");
	setLastMeas (data[2], "device_1");

}

function setLastMeas(data, label) {
    var data_last    = data[ data.length-1 ][1];
    var div_label = "#last_" + label;
	if (label == "spill") {
    	$(div_label).html(data_last);
	} else {
    	$(div_label).html(data_last.toFixed(3));
	}
}
//}}}

//{{{
function Ares_JS_DrawData(data) {
    var axis_fmt;
    var sampling;
    var days = (utime_end - utime_begin) / (24.0*60*60);
	
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

	$("#status").html( 'Drawing plots...' );
	var options = { xaxis: { mode: "time", timeformat: axis_fmt }, 
					selection: { mode: "y" }, 
					legend: { position: 'nw' }, 
					//lines: { show: false },  points: { show: true } 
    };


	var idx_data = 0;
	
	for (let plane_num in plane_list) {
		var list_data = [];
		plane = plane_list[plane_num];
		if (plane == "spill") {
			continue;
		}

	    list_data.push(data[plane_num]);
		let place = $("#gr_"+plane);
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
				  opts.min = 0;
				  opts.max = 10;
			   });
			plot.setupGrid();
			plot.draw();
		 });
	}

	var str_stat = "Checked at <b>" + JS_FormatDateTime(date_now) + "</b>.  " + npt + " records.";
	if (sampling > 1) str_stat += "  Sampled down by " + sampling + ".";
	$("#status").html(str_stat);

}

//}}}


