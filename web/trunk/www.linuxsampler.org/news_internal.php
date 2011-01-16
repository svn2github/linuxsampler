<?php

// XML file with news data
$file = "news.xml";
// show all news entries by default
$max_items = -1;

$current_tag = array();
$current_tag_body_is_empty = true;
$current_link_ref = "";

function startElement($parser, $name, $attribs) {
    global $max_items;
    global $current_tag;
    global $current_tag_body_is_empty;
    global $current_link_ref;

    if ($max_items == 0) return;

    array_push($current_tag, $name);

    $current_tag_body_is_empty = true;

    if ($name == "entry") {
        if (count($attribs) && isset($attribs["date"])) {
            $d = $attribs["date"];
            // pack into a (single cell) table so (flaoting) images wont vertically overlap out of the news block border
            echo "<div class=\"news\"><table><tr><td>";
            echo "<span class=\"news_date\">$d</span> ";
        } else echo "<b>???</b> ";
    } else if ($name == "link") {
        $current_link_ref = (isset($attribs["ref"])) ? $attribs["ref"] : "";
        echo "<a href=\"$current_link_ref\">";
        if (count($attribs) && isset($attribs["img"])) {
            $pic = $attribs["img"]);
            echo "<img src=\"$pic\" style=\"float: left; margin: 4px;\">";
            $current_tag_body_is_empty = false;
        }
    } else if ($name == "list") {
        echo "<ul class=\"news\">";
    } else if ($name == "li") {
        echo "<li class=\"news\">";
    }
}

function endElement($parser, $name) {
    global $max_items;
    global $current_tag;
    global $current_tag_body_is_empty;
    global $current_link_ref;

    if ($max_items == 0) return;

    array_pop($current_tag);

    if ($name == "entry") {
        echo "</td></tr></table></div>\n";
        if ($max_items > 0) $max_items--;
    }
    else if ($name == "link") {
        if ($current_tag_body_is_empty) echo $current_link_ref;
        echo "</a>";
        $current_link_ref = ""; // reset
    }
    else if ($name == "list") echo "</ul>";
    else if ($name == "li") echo "</li>";
}

function characterData($parser, $data) {
    global $max_items;
    global $current_tag;
    global $current_tag_body_is_empty;

    $current_tag_body_is_empty = false;

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
