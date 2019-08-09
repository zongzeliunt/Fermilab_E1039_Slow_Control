
function FormatDateTime(date) {
//    return date.toString();

    var YY = date.getFullYear();  
    var MM = date.getMonth() + 1;  
    var DD = date.getDate();
    var hh = date.getHours();
    var mm = date.getMinutes();
    var ss = date.getSeconds();
    if (MM < 10) MM = '0'+MM;
    if (DD < 10) DD = '0'+DD;
    if (hh < 10) hh = '0'+hh;
    if (mm < 10) mm = '0'+mm;
    if (ss < 10) ss = '0'+ss;
    return YY+'/'+MM+'/'+DD+' '+hh+':'+mm+':'+ss;
}

function ConvertData(data) {
   tzoff = (new Date()).getTimezoneOffset() * 60; // timezone offset in second unit
   data.forEach(function(x1){
      x1.forEach(function(x2){
         x2[0] = (parseInt(x2[0]) - tzoff) * 1000; // timezone offset & unit conversion (sec -> msec)
         x2[1] = Math.abs(x2[1]);
      });
   });
}

function SetLastMeasV(data, label, V, dVm_E, dVm_W, dVp_W, dVp_E) {
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

function SetLastMeasI(data, label, I_W, I_E) {
    var I_last    = data[ data.length-1 ][1];
    var div_label = "#last_I_" + label;
    $(div_label).html(I_last.toFixed(3) + " &mu;A");
    if      (I_last > I_E) { $(div_label).css("background-color", "red"        ); }
    else if (I_last > I_W) { $(div_label).css("background-color", "yellow"     ); }
    else                   { $(div_label).css("background-color", "transparent"); }
}

function alert_ARES() {
	alert("ARES");
}

function FetchAndDraw_1(fetch_data) {
	document.getElementById("data_0").innerHTML = fetch_data;
	alert("ARES");
	//document.getElementById("data_0").innerHTML = "1234";
}

//
// utime_begin & utime_end have to be defined by the PHP part
//
function FetchAndDraw_bak() {
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
    $.post(
        "fetch.php",
        { "utime_begin" : utime_begin,
          "utime_end"   : utime_end  , 
          "sampling"    : sampling    },
        function(data, status) {
	    $("#status").html( 'Tabularizing last measurement...' );
	    var npt = data[0].length;
            var time_last = data[0][npt-1][0] * 1000;
	    var date_last = new Date(time_last);

	    $("#time_last").html( " @ " + FormatDateTime(date_last) );
            $("#time_last_warning").html("");
            if (sampling == 1) {
               var minutes_warn = 15;
               var minutes_noup = (date_now.getTime() - time_last) / 6e4; // msec -> minute
               if (minutes_noup > minutes_warn) {
                  $("#time_last_warning").html(" !! No record for last " + Math.floor(minutes_noup) + " minutes !!");
                  //$("#time_last_warning").css ("color", "red");
               }
            }

	    ConvertData (data);
            DrawLastMeas(data);

	    $("#status").html( 'Drawing plots...' );
	    var options = { xaxis: { mode: "time", timeformat: axis_fmt }, 
                            selection: { mode: "y" }, 
			    legend: { position: 'nw' }, 
//			    lines: { show: false },  points: { show: true } 
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
            var str_stat = "Checked at <b>" + FormatDateTime(date_now) + "</b>.  " + npt + " records.";
            if (sampling > 1) str_stat += "  Sampled down by " + sampling + ".";
	    $("#status").html(str_stat);
        },
        "json" );
}

/*
$(function () {
    FetchAndDraw();
});
*/

////////////////////////////////////////////////////////////////
//
// Variables and functions for auto page refresh
//
var refresh_interval = 120; // in sec unit
var time_to_refresh = refresh_interval;
function CountDown() {
    if (document.getElementById("auto_refresh").checked) {
    if (time_to_refresh > 1) {
        time_to_refresh -= 1;
    } else {
       //var time_now = Date.now();
       //FetchAndDraw();
	self.location.reload();
        time_to_refresh = refresh_interval;
    }
    }	
	var date = new Date();
    document.getElementById("counter").innerHTML = time_to_refresh;	
	//document.getElementById("auto_refresh").checked = true;
    document.getElementById("current_time").innerHTML = date;

    setTimeout("CountDown()",1000)
}
