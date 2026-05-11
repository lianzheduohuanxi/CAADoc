
var MAIN_FRAMENAME = "CAAPage";
//var NS7 = false;
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
  if (NSVer >= 5)
  {
    NS7 = true;
  } 
} else if (navigator.appName == "Microsoft Internet Explorer")
{
  IE = true;
} else {
  alert('Unsupported browser '+navigator.appName);
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

//-------------------------------------------------------------------	
// Create a Toc in a html file
//-------------------------------------------------------------------	
function createToc(isH3) {
    var docBody = document.body;
//-    var tocList = document.getElementById("toc");

    var tabBody = document.getElementById("body");
    var nodes = null;
    if (tabBody != null) {
      nodes = tabBody;
//alert('table');
    } else {
      nodes = docBody;
//alert('body');
    }

    var tocDiv = document.getElementById("toc");
    var tocListItem = null;
    var tocSubList = null;
//    alert('h2List.length = '+h2List.length);
    var i=0;
    var subList = "false";
    var isH2 = "false";


    var tocList = document.createElement("UL");
	//tocList.className = "toc";

    // R208 replaces previous toc build based upon H2 tags having the body
    // element as parent. Any H2, and H3, are processed whatever their locations
    // in the DOM, that is, for instance, even if their are located in a table. 
    var h2List = document.getElementsByTagName("h2");
    if (h2List.length > 0) {

    var parent = h2List[1].parentNode;
    while (i<parent.childNodes.length) {
        if (parent.childNodes[i].tagName=="H2") {
            subList = "false";
            isH2 = "true";
            //var tab1 = new Array(2);
            var tab = extractData(parent.childNodes[i]);
            //    alert('tab[0] = '+tab[0]+'tab[1] = '+tab[1]);

            tocListItem = document.createElement("LI");
            var tocListItemA = document.createElement("A");
            tocListItemA.innerHTML = tab[0];
            tocListItemA.href = "#"+tab[1];
  	    	tocListItemA.target = MAIN_FRAMENAME;
            tocListItem.appendChild(tocListItemA);
            tocList.appendChild(tocListItem);
        } else if (parent.childNodes[i].tagName=="H3" && isH2=="true" && !isH3) {
//alert('H3 - '+docBody.childNodes[i].innerHTML);
            if(subList=="false") {
                tocSubList = document.createElement("UL");
                tocListItem.appendChild(tocSubList);
            }
            var tab = extractData(parent.childNodes[i]);
            var subListItem = document.createElement("LI");
            var subListItemA = document.createElement("A");
            subListItemA.innerHTML = tab[0];
            subListItemA.href = "#"+tab[1];
  	    	subListItemA.target = MAIN_FRAMENAME;
            subListItem.appendChild(subListItemA);
            tocSubList.appendChild(subListItem);
            subList = "true";
        }
        i++;
        continue;
        }
}
//------------------------------------------------------------------------------
// H2 and H3 toc build, replaced in R208 - See just above
/*
    while (i<nodes.childNodes.length) {
//alert('h2List['+i+'].innerHTML = '+h2List[i].innerHTML);
        if (nodes.childNodes[i].tagName=="H2") {
//alert('H2 - '+docBody.childNodes[i].innerHTML);
            subList = "false";

            //var tab1 = new Array(2);
            var tab = extractData(nodes.childNodes[i].innerHTML);
            //    alert('tab[0] = '+tab[0]+'tab[1] = '+tab[1]);

            tocListItem = document.createElement("LI");
            var tocListItemA = document.createElement("A");
            tocListItemA.innerHTML = tab[0];
            tocListItemA.href = "#"+tab[1];
  	    	tocListItemA.target = MAIN_FRAMENAME;
            tocListItem.appendChild(tocListItemA);
            tocList.appendChild(tocListItem);
 
        } else if (nodes.childNodes[i].tagName=="H3") {
//alert('H3 - '+docBody.childNodes[i].innerHTML);
            if(subList=="false") {
                tocSubList = document.createElement("UL");
                tocListItem.appendChild(tocSubList);
            }
            var tab = extractData(nodes.childNodes[i].innerHTML);
            var subListItem = document.createElement("LI");
            var subListItemA = document.createElement("A");
            subListItemA.innerHTML = tab[0];
            subListItemA.href = "#"+tab[1];
  	    	subListItemA.target = MAIN_FRAMENAME;
            subListItem.appendChild(subListItemA);
            tocSubList.appendChild(subListItem);
            subList = "true";
        }
        i++;
        continue;
    }
*/
    tocDiv.appendChild(tocList);
}

/*
function extractData(textToScan) {
    var temp;
    var i1;
    var i2;
    var anchor;
    var tab;
    if (IE) {
      temp = textToScan.split("</A>");
      //alert('temp[0] = '+temp[0]+' temp[1] = '+temp[1]);
      i1 = temp[0].indexOf("=");
      i2 = temp[0].indexOf(">");
      //alert('i1 = '+i1+' i2 = '+i2);
      anchor = temp[0].substring(i1+1, i2);
      tab = new Array(2);
      tab[0] = temp[1];
      tab[1] = anchor;
      //alert('tab[0] = '+tab[0]+' tab[1] = '+tab[1]);
    }
	} else if (Firefox || Chrome) {
      temp = textToScan.split("</a>");
      //alert('temp[0] = '+temp[0]+' temp[1] = '+temp[1]);
      i1 = temp[0].indexOf("=");
      i2 = temp[0].indexOf(">");
      //alert('i1 = '+i1+' i2 = '+i2);
      anchor = temp[0].substring(i1+2, i2-1);
      //alert('anchor = '+anchor);
      tab = new Array(2);
      tab[0] = temp[1];
      tab[1] = anchor;
      //alert('tab[0] = '+tab[0]+' tab[1] = '+tab[1]);
    }
    return tab;
}
*/
function extractData(nodeToScan) {
	//alert('textContent = '+nodeToScan.innerText);
    // nodeToScan is a H2 or H3
	// extracts the text in data[0] and the anchor in data[1]
    var data;
	data = new Array(2);
	if (IE) {
		data[0] = nodeToScan.innerText;
	//} else if (NS7) {
	} else if (Firefox || Chrome) {
		data[0] = nodeToScan.textContent;
	}
	//the A tag should be unique in H2 or H3
	data[1] = nodeToScan.getElementsByTagName("a")[0].name;
	
    return data;
}
