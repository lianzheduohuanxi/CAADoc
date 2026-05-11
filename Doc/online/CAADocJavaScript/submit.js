// Global variables
var NS4 = false;
var NS7 = false;
var IE  = false;
var Chrome  = false;
var Firefox = false;

//alert(navigator.appName);
//alert(navigator.appVersion);

/*
if (navigator.appName == "Netscape")
{
	NSVer = navigator.appVersion;
	NSVer = NSVer.substring(0,1);
	if (NSVer >= 5) {
		NS7 = true; // Mozilla
	} else {
		NS4 = true; // Netscape
	}
	window.defaultstatus="CAA Version 5";
} else {
	IE = true;  // Internet Explorer
}
*/
// Detects IE11 and above - IE11 returns Netscape in appName!
var isAtLeastIE11 = !!(navigator.userAgent.match(/Trident/) && !navigator.userAgent.match(/MSIE/));

if (navigator.appName == "Netscape" && !isAtLeastIE11) // Chrome or Firefox
{
  var exp=new RegExp("Chrome","g"); // To differentiate Chrome with Firefox
  if (navigator.appVersion.match(exp)) {
    Chrome = true;
  } else if (navigator.userAgent.match(/Firefox/)) {
	Firefox = true;
  }
} else { // IE
  IE = true;
}

// Link withtout prereq: to be used cautiously
function CAAlinkOutOfPreqs(iLink)
{
	url = '../' + iLink
	if (Firefox || Chrome) {
		// Mozilla
		window.parent.frames["CAAPage"].location = url;
	} else {
		// Netscape or IE
		// alert("Netscape or IE");
		//window.open(url, "CAAPage");
		window.open(url, window.name);
	}
}

// Link to a URL
function CAAlinkUrl(iUrl)
{
	window.open(iUrl, "_blank");
}


function CAAlink(iLanguage, iFramework, iObjectType, iInterface, iMethod)
{

/*	alert("iLanguage = "+iLanguage+
		  "\niFramework = "+iFramework+
		  "\niObjectType = "+iObjectType+
		  "\niInterface = "+iInterface+
		  "\nMethod = "+iMethod);
*/

	var url, dir, name;
	if (iLanguage == "CPP") {
		dir = "../../generated/refman/";
	} else if (iLanguage == "IDL") {
		dir = "../../generated/interfaces/";
	}

	if (!iFramework) {
		url = dir + "_index/main.htm";
	} else {
		if (iFramework == "Deprecated") { // Link to the deprecation page
			if (iLanguage == "CPP") {
				url = dir + "_index/Deprecated.htm";
			} else if (iLanguage == "IDL") {
				url = dir + "_index/CAADeprecatedIdx.htm";
			}
		} else if (iFramework == "HOME") {  // Link to the static home page
			url = dir + "_index/main.htm";
		} else if (iFramework == "TREE") {  // Link to the class hierarchy page
			url = dir + "_index/tree.htm";
		} else if (iFramework == "INDEX") { // Link to the master index page
			if (iLanguage == "CPP") {
				url = dir + "_index/HomeIdx.htm";
			} else if (iLanguage == "IDL") {
				url = dir + "_index/CAAHomeIdx.htm";
			}
		} else { 
			if (!iObjectType && !iInterface) {
				url = dir + iFramework + ".htm";
			} else {
				url = dir + iFramework + ".htm";
				var xmlFileName = null;
				xmlFileName = dir + iFramework + "/CAA" + iFramework + "Toc.xml";
				//alert ("XML file = "+xmlFileName);
				var newNode = null;
				try {
					//alert ("Try XML file = "+xmlFileName);
				    var xmlNode = null;
/*
 					if(IE) {
						// --- Internet Explorer
						//var xmlNode = new ActiveXObject("Microsoft.XMLDOM");
						var xmlNode = new ActiveXObject("Msxml2.DOMDocument");
						xmlNode.async = false;
						xmlNode.load(xmlFileName);
					} else {
						// --- Mozilla
						var req = new XMLHttpRequest();
						req.overrideMimeType("text/xml");
						req.open("GET", xmlFileName, false);
						req.send(null);
						xmlNode = req.responseXML;
					}
*/
					if (IE) {
						//var xmlNode = new ActiveXObject("Microsoft.XMLDOM");
						//var xmlNode = new ActiveXObject("Msxml2.DOMDocument");
						//xmlNode.async = false;
						//xmlNode.load(xmlFileName);
						//return xmlNode;
						var path = parent.parent.document.URL;
						if (path.match("http://") || path.match("https://")) {
							var req = new ActiveXObject("Msxml2.XMLHTTP");
							req.open("GET", xmlFileName, false, null, null);
							req.send("");
							while (req.readyState != 4) {
							}
							xmlNode = req.responseXML;
						} else {
							xmlNode = new ActiveXObject("Msxml2.DOMDocument");
							xmlNode.async = false;
							xmlNode.load(xmlFileName);
						}
					} else { // --- Mozilla
						//alert ("Coucou");
						var req = new XMLHttpRequest();
						req.overrideMimeType("text/xml");
						req.open("GET", xmlFileName, false);
						req.send(null);
						xmlNode = req.responseXML;
						//return req.responseXML;
					}

					newNode = xmlNode.getElementsByTagName('Root')[0];
					var i = 0;
					var found = "no";
					while(newNode.firstChild != null)
					{
						i++;
						var curchild = newNode.firstChild;
						newNode.removeChild(curchild);
						if(curchild.nodeType == 1 && curchild.nodeName != "parsererror") {
							var type = "";
							if (curchild.getAttribute("type")=="collection" ||
								curchild.getAttribute("type")=="exception" ||
								curchild.getAttribute("type")=="notification") {
								type = "class";
							} else {
								type = curchild.getAttribute("type");
							}
							//alert("Type = "+iObjectType+" -- Name = "+iInterface+" -- "+curchild.nodeName+" -- "+type+" -- "+iObjectType);
							if (iObjectType && iInterface && curchild.nodeName=="ITEM" && type==iObjectType) {
								//alert("Type = "+iObjectType+" -- Name = "+iInterface);
								/*
								// No need to decode the href attribute to find out the name.
								// Use the name attribute instead.
								var motif = iObjectType+"_"+iInterface;
								motif = motif.replace(/\(/,"\\("); // To match parentheses in collections
								motif = motif.replace(/\)/,"\\)"); 
								//alert("motif = "+motif);
								*/
								while(curchild.firstChild != null)
								{
									//alert("Dans while - curchild.firstChild.nodeName = "+curchild.firstChild.nodeName);
									var curGrandChild = curchild.firstChild;
									//alert("i = "+i+" -- curGrandChild.nodeType = "+curGrandChild.nodeType+" -- nodeName = "+curGrandChild.nodeName+" -- name = "+curGrandChild.getAttribute("href"));
									curchild.removeChild(curGrandChild);
									/*
									//if (curGrandChild.getAttribute('href').match(exp)) {
									if (curGrandChild.nodeType == 1 && curGrandChild.getAttribute('href').search(motif)!=-1) {
									//alert("i = "+i+" -- href = "+curGrandChild.getAttribute('href'));
										url = url.replace(/\.htm/,"");
										var urlTemp = curGrandChild.getAttribute('href');
										urlTemp = urlTemp.replace(/\.htm/,""); // To take _function* files ending with .htm into account
										url = url + "/" + urlTemp + ".htm";
										//url = url + "/" + curGrandChild.getAttribute('href') + ".htm";
										if (iMethod) {
											url = url + "#" + iMethod;
										}
										//alert ("url = "+url);
										found = "yes";
										break;
									} else if (curGrandChild.nodeType == 1 && curGrandChild.getAttribute('href').search("_"+iObjectType+"_"+iInterface)!=-1 && iObjectType=="function") {
										url = dir + iFramework + "/" + curGrandChild.getAttribute('href');
										found = "yes";
										break;
									}
									*/

									if (curGrandChild.nodeType == 1 && curGrandChild.getAttribute('name') == iInterface) {
										url = dir + iFramework + "/" + curGrandChild.getAttribute('href');
										if (iMethod) {
											url = url + "#" + iMethod;
										}
										//alert ("url = "+url);
										found = "yes";
										break;
									}
								}
							}
							if (found=="yes") { break; }
						}
						//alert ("type = "+curchild.getAttribute('type')+" -- name = "+curchild.getAttribute('name')+" -- id = "+curchild.getAttribute('id'));
						//node.insertBefore(curchild, importNode);
					}
				} catch(e) {
					// --- import XML not found
					alert ("import XML file "+xmlFileName+" not found");
				}
			}
		}
	}

//alert('url = '+url);
//window.open(url, "CAAPage");
//window.open(url, window.name);
	if (Firefox || Chrome) {
    // Mozilla
		window.parent.frames["CAAPage"].location = url;
	} else if (IE) {
		// IE
		// alert("Netscape or IE");
		//window.open(url, "CAAPage");
		window.open(url, window.name);
	}
}

function CAAlinkJava(iPackage, iInterface, iMethod)
{
  var url, dir;
  dir = "../../docs/api/com/dassault_systemes/";

  if (!iPackage)
  {
    url = "../../docs/api/_index/main.html";
  }
  else
  {
    if (iPackage == "Deprecated")
    {
      url = "../../docs/api/_index/jDeprecatedIdx.html";
    }
    else
    {
      if (!iInterface)
      {
        url = "../../docs/api/_index/pkg/com.dassault_systemes." + iPackage + ".html";
      }
      else
      {
        if (!iMethod)
        {
          url = dir + iPackage + "/" + iInterface + ".html";
        }
        else
        {
          url = dir + iPackage + "/" + iInterface + ".html#" + iMethod;
        }
      }
    }
  }
//  window.open(url, "CAAPage");
//  window.open(url, window.name);
  if (NS7)
  {
    // Mozilla
//	alert("Mozilla");
    window.parent.frames["CAAPage"].location = url;
  }
  else
  {
    // Netscape or IE
//	alert("Netscape or IE");
//    window.open(url, "CAAPage");
    window.open(url, window.name);
  }
}

function insertLinkToTop()
{
	document.writeln('<table>');
	document.writeln('<tr>');
	document.writeln('<td width="100%"><hr class="top"></td>');
	document.writeln('<td><a href="#Top" class="top"><img src="../CAAIcons/images/butix_top.gif" alt="Top"></a></td>');
	document.writeln('</tr>');
	document.writeln('</table>');
}

function insertCopyright()
{
	document.writeln('<p class="copyright"><em>Copyright &#169; 1999-2017, Dassault Syst&#232;mes. All rights reserved.</em></p>');
}

function showImage(image) {
//	if (!IE) {
		var newImage = null;
		newImage = new Image();
		newImage.src = image;
		newImage.onload = function() {
			var W=newImage.width + 40;
			var H=newImage.height + 40;
			window.open(newImage.src, '_blank', 'width='+W+', height='+H+', toolbar=no, scrollbar=no, resizable=no, menubar=no');
		};
/*
	} else {
		var loaded = false;
		function loadHandler() {
			if (loaded) {
				return;
			}
			loaded = true;
		var W=newImage.width + 40;
		var H=newImage.height + 40;
		window.open(newImage.src, '_blank', 'width='+W+', height='+H+', toolbar=no, scrollbar=no, resizable=no, menubar=no');		

		}
		var newImage = null;
		newImage = new Image();
		newImage.src = image;
		newImage.onload = loadHandler;
		if (newImage.complete) {
			loadHandler();
		}
//		var W=newImage.width + 40;
//		var H=newImage.height + 40;
//		window.open(newImage.src, '_blank', 'width='+W+', height='+H+', toolbar=no, scrollbar=no, resizable=no, menubar=no');		
	}
*/
}
