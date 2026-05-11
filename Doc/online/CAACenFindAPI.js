// Valid for CAACenBase.doc only 

var NS4 = false;
var NS7 = false;
var IE  = false;

//alert(navigator.appName);
//alert(navigator.appVersion);

if (navigator.appName == "Netscape")
{
  NSVer = navigator.appVersion;
  NSVer = NSVer.substring(0,1);
  if (NSVer >= 5)
  {
    NS7 = true;
  } 
  else
  {
    NS4 = true;
  }
  doc="document";
  sty="";
  window.defaultstatus="CAA Version 5";
} else {
  IE = true;
  doc="document.all";
  sty=".style";
}

// Link to a URL
function CAAlinkUrl(iUrl)
{
  window.open(iUrl, "_blank");
}

// Link to CPP or IDL doc
function CAAlink(iLanguage, iFramework, iObjectType, iInterface, iMethod)
{
//  alert(window.name);
//  alert(window.frameElement);
//  alert(window.parent);
//  var frm = window.parent.frames;
//  for (i=0; i < frm.length; i++) 
//    alert(frm[i].name);

  var url, dir, name;

  if (iLanguage == "CPP")
  {
    dir = "../generated/refman/";
  }
  else
  {
    dir = "../generated/interfaces/";
  }

  if (!iFramework)
  {
    url = dir + "_index/main.htm";
  }
  else
  {
    if (!iObjectType && !iInterface)
    {
      url = dir + iFramework + ".htm";
    }
    else
    {
      name = iObjectType.toLowerCase() + "_" + iInterface.toLowerCase();
      if (!iMethod)
      {
        url = dir + iFramework + "/" + name + ".htm";
        //alert(url);
      }
      else
      {
        url = dir + iFramework + "/" + name + ".htm#" + iMethod;
      }
    }
  }
  //window.open(url, "CAAPage");
  if (NS7)
  {
    // Mozilla
    window.parent.frames["CAAPage"].location = url;
  }
  else
  {
    // Netscape or IE
	// alert("Netscape or IE");
    window.open(url, "CAAPage");
  }
}

// Link to Java doc
function CAAlinkJava(iPackage, iInterface, iMethod)
{
  var url, dir;
  frame = "CAAPage";
  dir = "../../docs/api/com/dassault_systemes/";

  if (!iPackage)
  {
    url = "../docs/api/_index/main.htm";
  }
  else
  {
    if (!iInterface)
    {
      url = dir + iPackage + ".htm";
    }
    else
    {
      if (!iMethod)
      {
        url = dir + iPackage + "/" + iInterface + ".htm";
      }
      else
      {
        url = dir + iPackage + "/" + iInterface + ".htm#" + iMethod;
      }
    }
  }
//  window.open(url, "CAAPage");
//  window.open(url, window.frame);
//  window.parent.frames["CAAPage"].location = url;
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
    window.open(url, "CAAPage");
  }
}

// Link to the Faq home pages
function CAAlinkFaq()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScrQuickRefs/CAAScrAutomationFAQ.htm";
  }
  else
  {
    url = "CAACenQuickRefs/CAACenFAQ.htm";
  }
//  window.open(url, "CAAPage");
  window.parent.frames["CAAPage"].location = url;
}

// Link to the What's New home pages
function CAAlinkWhatsNew()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScdBase/CAAScdScriptNews.htm";
  }
  else
  {
    url = "CAACenQuickRefs/CAACenWhatsNew.htm";
  }
//  window.open(url, "CAAPage");
  window.parent.frames["CAAPage"].location = url;
}

// Link to the Getting Started home pages
function CAAlinkGettingStarted()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScdInfUseCases/CAAInfGettingStarted.htm";
  }
  else
  {
    url = "CAAPdiBase/CAAPdiGettingStarted.htm";
  }
//  window.open(url, "CAAPage");
  window.parent.frames["CAAPage"].location = url;
}

// Link to the Site Map home pages
function CAAlinkSiteMap()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScdBase/CAAScdAutomationSiteMap.htm";
  }
  else
  {
    url = "CAACenWeb/CAACenSiteMap.htm";
  }
//  window.open(url, "CAAPage");
  window.parent.frames["CAAPage"].location = url;
}
