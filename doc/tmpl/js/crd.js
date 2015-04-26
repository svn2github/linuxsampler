/*
  CrudeDoc Java Script
  Copyright (c) 2015 Christian Schoenebeck. All rights reserved.
  http://www.crudebyte.com
*/

function crdWindowHeight() {
    return window.innerHeight ||
           document.documentElement.clientHeight ||
           document.getElementsByTagName('body')[0].clientHeight;
}

function crdScrollTo(e) {
    $('html, body').animate({
        scrollTop: $( "#" + $(e).attr("section") ).offset().top - 68
    }, 300);
}

function crdOnScroll() {
    //var headers = $("body > article :header:in-viewport");
    var headers = $("body > article :header");
    var wst = $(window).scrollTop();
    if (wst <= 0) {
        for (var i = 0; i < headers.length; ++i) {
            $("body > aside *[section]").removeClass("current");
            var link = $("body > aside *[section='" + headers[i].id + "']");
            $(link).addClass("current");
            return;
        }
    }
    var wh  = crdWindowHeight();
    for (var i = headers.length - 1; i >= 0; --i) {
        var offset = headers[i].offsetTop - wst + wh/2;
        if (headers[i].id.length > 0 && (offset <= 0 || offset <= wh)) {
            $("body > aside *[section]").removeClass("current");
            var link = $("body > aside *[section='" + headers[i].id + "']");
            $(link).addClass("current");
            break;
        }
    }
}

function crdOnWindowResize() {
    var wh = crdWindowHeight();
    $("nav > ul > li ul").css("max-height", wh - 70);
}

function crdDetectFeatures() {
    if ($.support["transform"]) {
        $("body").addClass("hasTransform");
    }
}

$(function() {
    crdDetectFeatures();
    $(document).tooltip();
    $("article img[caption]").each(function() {
        $(this).after(
            "<div class='imgcptn'>" +
            $(this).attr("caption") + "</div>"
        );
    });
    $("body > aside *[section]").click(function(e) {
        //e.preventDefault();
        crdScrollTo(this);
        return false;
    });
    crdOnScroll();
    $(window).resize(function() {
        crdOnWindowResize();
    });
});

$(document).ready(function() {
    crdOnWindowResize();
});

var _crdScrollTimeout;

$(window).scroll(function() {
    crdOnScroll();
});
