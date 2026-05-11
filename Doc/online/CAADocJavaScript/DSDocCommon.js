// =======================================================================
// === Common Functions
// === Copyright © Dassault Systemes / Chandak Rashmi (Aug 19 2016)
// =======================================================================
// === This Javascript Library contains general functions for the online
// === doc runtime infrastructure.
// =======================================================================
/**
* Loads a file and returns its content.
*/
function loadFile(url, type)
{
    var req = null;
    if (window.XMLHttpRequest) req = new XMLHttpRequest();
    else if (window.ActiveXObject) req = new ActiveXObject("Microsoft.XMLHTTP");
    if (req == null) throw new Error("XMLHttpRequest not supported.");

    // --- sync mode
    req.open("GET", url, false);

    req.send(null);
    if (type == "txt")
        return req.responseText;
    return req.responseXML;
}

// =======================================================================
/**
* This function loads the given xml file and returns its root node.
*/
function loadXML(xmlUrl)
{
    if (document.all) {
        // --- Internet Explorer
        var xmlNode = new ActiveXObject("Msxml2.DOMDocument");
        xmlNode.async = false;
        xmlNode.load(xmlUrl);
        return xmlNode;
    }
    else {
        // --- Mozilla
        var req = new XMLHttpRequest();
        req.overrideMimeType("text/xml");
        req.open("GET", xmlUrl, false);
        req.send(null);
        return req.responseXML;
    }
}

// =======================================================================
function loadFile_mod(url, type)
{
    var xmlhttp;
    try {
        xmlhttp = new ActiveXObject('Msxml2.XMLHTTP');
    }
    catch (e) {
        try {
            xmlhttp = new ActiveXObject('Microsoft.XMLHTTP');
        }
        catch (e2) {
            try {
                xmlhttp = new XMLHttpRequest();
            }
            catch (e3) {
                xmlhttp = false;
            }
        }
    }

    if (xmlhttp == null) throw new Error("XMLHttpRequest not supported.");
    xmlhttp.open("GET", url, false);
    xmlhttp.send(null);

    if (type == "txt")
        return xmlhttp.responseText;
    return xmlhttp.responseXML;
}
