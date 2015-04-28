/*
  CrudeDoc Java Script (for previewing an article on a local machine)
  Copyright (c) 2015 Christian Schoenebeck. All rights reserved.
  http://www.crudebyte.com
*/

function crdLoadScript(url) {
    var head = document.getElementsByTagName("head")[0];
    var script = document.createElement("script");
    script.type = "text/javascript";
    script.src  = url;
    head.appendChild(script);
}

function crdDetectFeatures() {
    if ($.support["transform"]) {
        $("body").addClass("hasTransform");
    }
}

$(function() {
    crdLoadScript("jquery-1.11.2.js");
    crdLoadScript("jquery-ui.js");
    crdLoadScript("jquery.transform2d.js");

    crdDetectFeatures();
    $(document).tooltip();
    $("img[caption]").each(function() {
        $(this).after(
            "<div class='imgcptn'>" +
            $(this).attr("caption") + "</div>"
        );
    });
});
