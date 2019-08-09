function JS_ConvertData(data) {
//{{{
   tzoff = (new Date()).getTimezoneOffset() * 60; // timezone offset in second unit
   data.forEach(function(x1){
      x1.forEach(function(x2){
         x2[0] = (parseInt(x2[0]) - tzoff) * 1000; // timezone offset & unit conversion (sec -> msec)
         x2[1] = Math.abs(x2[1]);
      });
   });
}
//}}}


function JS_ShowCurrentTime() {
	var date = new Date();
    document.getElementById("current_time").innerHTML = date;
    setTimeout("JS_ShowCurrentTime()",1000)
}

function JS_CountDown() {
//{{{
    if (document.getElementById("auto_refresh").checked) {
		if (time_to_refresh > 1) {
			time_to_refresh -= 1;
		} else {
			self.location.reload();
			time_to_refresh = refresh_interval;
		}
    }	
    document.getElementById("counter").innerHTML = time_to_refresh;	
    setTimeout("JS_CountDown()",1000)
}
//}}}

function alert_ares_global() {
	alert("ARES global");
}

function alert_ares_global_2() {
	alert("ARES global 2");
}

function JS_FormatDateTime(date) {
//{{{
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
//}}}

$(function () {
    //alert_ares();
});

