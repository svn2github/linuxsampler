<?php

// XML file with news data
$file = "news.xml";
// show all news entries by default
$max_items = -1;

function startElement($parser, $name, $attribs) {
    global $max_items;
    if ($max_items == 0) return;

    if ($name == "entry") {
        if (count($attribs) && isset($attribs["date"])) {
            $d = $attribs["date"];
            echo "<div class=\"news\">";
            echo "<span class=\"news_date\">$d</span> ";
        } else echo "<b>???</b> ";
    } else if ($name == "link") {
        $addr = (isset($attribs["ref"])) ? $attribs["ref"] : "";
        echo "<a href=\"$addr\">";
    } else if ($name == "list") {
        echo "<ul class=\"news\">";
    } else if ($name == "li") {
        echo "<li class=\"news\">";
    }
}

function endElement($parser, $name) {
    global $max_items;
    if ($max_items == 0) return;

    if ($name == "entry") { echo "</div>\n";
        if ($max_items > 0) $max_items--;
    }
    else if ($name == "link") echo "</a>";
    else if ($name == "list") echo "</ul>";
    else if ($name == "li") echo "</li>";
}

function characterData($parser, $data) {
    global $max_items;
    if ($max_items == 0) return;

    echo $data;
}

if (isset($HTTP_GET_VARS['max_items'])) {
    $max_items = $HTTP_GET_VARS['max_items'];
}

$xml_parser = xml_parser_create();
xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, false);
xml_set_element_handler($xml_parser, "startElement", "endElement");
xml_set_character_data_handler($xml_parser, "characterData");
if (!($fp = fopen($file, "r"))) {
    die("Could not open news XML file!");
}
while ($data = fread($fp, 4096)) {
    if (!xml_parse($xml_parser, $data, feof($fp))) {
        die(sprintf("XML error: %s at line %d",
                    xml_error_string(xml_get_error_code($xml_parser)),
                    xml_get_current_line_number($xml_parser)));
    }
}
xml_parser_free($xml_parser);

?>
