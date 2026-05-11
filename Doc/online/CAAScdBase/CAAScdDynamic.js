mechanicalin=new Image();
mechanicalin.src="images/CAAScdlogo_mechanicali.gif";
surfacicin=new Image();
surfacicin.src="images/CAAScdlogo_surfacici.gif";
analysisin=new Image();
analysisin.src="images/CAAScdlogo_analysisi.gif";
equipmentin=new Image();
equipmentin.src="images/CAAScdlogo_equipmenti.gif";
manufacturingin=new Image();
manufacturingin.src="images/CAAScdlogo_manufacturingi.gif";
DMUin=new Image();
DMUin.src="images/CAAScdlogo_DMUi.gif";
processdetin=new Image();
processdetin.src="images/CAAScdlogo_processdeti.gif";
workinstructionsin=new Image();
workinstructionsin.src="images/CAAScdlogo_mechanicali.gif";
factoryDMUin=new Image();
factoryDMUin.src="images/CAAScdlogo_DMUi.gif";
offlineprogrammingin=new Image();
offlineprogrammingin.src="images/CAAScdlogo_manufacturingi.gif";
infrastructurein=new Image();
infrastructurein.src="images/CAAScdlogo_infrastructurei.gif";
portalDMUin=new Image();
portalDMUin.src="images/CAAScdlogo_DMUi.gif";

mechanicalout=new Image();
mechanicalout.src="images/CAAScdlogo_mechanical.gif";
surfacicout=new Image();
surfacicout.src="images/CAAScdlogo_surfacic.gif";
analysisout=new Image();
analysisout.src="images/CAAScdlogo_analysis.gif";
equipmentout=new Image();
equipmentout.src="images/CAAScdlogo_equipment.gif";
manufacturingout=new Image();
manufacturingout.src="images/CAAScdlogo_manufacturing.gif";
DMUout=new Image();
DMUout.src="images/CAAScdlogo_DMU.gif";
processdetout=new Image();
processdetout.src="images/CAAScdlogo_processdet.gif";
workinstructionsout=new Image();
workinstructionsout.src="images/CAAScdlogo_mechanical.gif";
factoryDMUout=new Image();
factoryDMUout.src="images/CAAScdlogo_DMU.gif";
offlineprogrammingout=new Image();
offlineprogrammingout.src="images/CAAScdlogo_manufacturing.gif";
infrastructureout=new Image();
infrastructureout.src="images/CAAScdlogo_infrastructure.gif";
portalDMUout=new Image();
portalDMUout.src="images/CAAScdlogo_DMU.gif";

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
//  alert(navigator.appName);
//  NS="false"; 
  IE = true;
  doc="document.all";
  sty=".style";
}

function imgIn(imgName,layName)
{
//  if (document.all) {
//    document[imgName].src = eval(imgName + "in.src");
//  }
//  else
//  {
//    window.document.layers[layName].document[imgName].src = eval(imgName + "in.src");
//  }
  if (NS4)
  {
    window.document.layers[layName].document[imgName].src = eval(imgName + "in.src");
  }
  else
  {
    document[imgName].src = eval(imgName + "in.src");
  }
}

function imgOut(imgName,layName)
{
//  if (document.all)
//  {
//    document[imgName].src = eval(imgName + "out.src");
//  }
//  else
//  {
//    window.document.layers[layName].document[imgName].src = eval(imgName + "out.src");
//  }
  if (NS4)
  {
    window.document.layers[layName].document[imgName].src = eval(imgName + "out.src");
  }
  else
  {
    document[imgName].src = eval(imgName + "out.src");
  }
}

var menuState = 0;
function selectMenu(menuNumber)
{
  layName = "submenu" + menuNumber;

  if (menuState)
  {
    if (NS7)
	{
	  layTemp = "submenu" + menuState;
	  document.getElementById(layTemp).style.visibility = "hidden";
	}
	else
    {
      eval(doc + ".submenu" + menuState + sty ).visibility = "hidden";
    }
  }
  // make the layer visible
  if (NS7)
  {
    document.getElementById(layName).style.visibility = "visible";
  }
  else
  {
    eval(doc + ".submenu" + menuNumber + sty ).visibility = "visible";
  }
  menuState = menuNumber;
}

var menuBgColor   = 0
var menuNumberSave = 0
function menuColorBg(menuNumber)
{
  if (navigator.appName == "Netscape")
  {
  }
  else
  {
    if (menuNumberSave != 0)
    {
      menuDecolorBg(menuNumberSave);
    }
    menuBgColor = eval(doc + ".menu" + menuNumber + sty ).backgroundColor;
//    eval(doc + ".menu" + menuNumber + sty ).backgroundColor= "#6699CC";
    eval(doc + ".menu" + menuNumber + sty ).backgroundColor= "#FFFFFF";
  }
  menuNumberSave = menuNumber;
}
function menuDecolorBg(menuNumber)
{
  if (navigator.appName == "Netscape")
  {
  }
  else
  {
    if (menuNumber == 0)
    {
      eval(doc + ".menu" + menuNumberSave + sty).backgroundColor= menuBgColor;
    }
    else
    {
      eval(doc + ".menu" + menuNumber + sty).backgroundColor= menuBgColor;
    }
  }
}

var submenuBgColor   = 0
var submenuNumberSave = 0
function submenuColorBg(submenuNumber)
{
  if (navigator.appName == "Netscape")
  {
  }
  else
  {
    if (submenuNumberSave != 0)
    {
      submenuDecolorBg(submenuNumberSave);
    }
    submenuBgColor = eval(doc + ".submenu" + submenuNumber + sty ).backgroundColor;
//    eval(doc + ".submenu" + submenuNumber + sty ).backgroundColor= "#6699CC";
    eval(doc + ".submenu" + submenuNumber + sty ).backgroundColor= "#FFFFFF";
  }
  submenuNumberSave = submenuNumber;
}

function submenuDecolorBg(submenuNumber)
{
  if (navigator.appName == "Netscape")
  {
  }
  else
  {
    if (submenuNumber == 0)
    {
      eval(doc + ".submenu" + submenuNumberSave + sty).backgroundColor= submenuBgColor;
    }
    else
    {
      eval(doc + ".submenu" + submenuNumber + sty).backgroundColor= submenuBgColor;
    }
  }
}

function hide()
{
//  if (menuState != 0)
//  {
//    eval(doc + ".submenu" + menuState + sty ).visibility = "hidden";
//  }

  if (menuState != 0)
  {
    if (NS7)
    {
      layTemp = "submenu" + menuState;
      document.getElementById(layTemp).style.visibility = "hidden";
    }
    else
    {
      eval(doc + ".submenu" + menuState + sty ).visibility = "hidden";
    }
  }
}

function linkFaq()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScrQuickRefs/CAAScrAutomationFAQ.htm";
  }
  else
  {
    url = "CAACenQuickRefs/CAACenFAQ.htm";
  }
  window.open(url, "CAAPage");
}

function linkWhatsNew()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScdBase/CAAScdScriptNews.htm";
  }
  else
  {
    url = "CAACenQuickRefs/CAACenWhatsNew.htm";
  }
  window.open(url, "CAAPage");
}

function linkGettingStarted()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScdInfUseCases/CAAInfGettingStarted.htm";
  }
  else
  {
    url = "CAAPdiBase/CAAPdiGettingStarted.htm";
  }
  window.open(url, "CAAPage");
}

function linkSiteMap()
{
  if (window.top.CAAAutomation == 1)
  {
    url = "CAAScdBase/CAAScdAutomationSiteMap.htm";
  }
  else
  {
    url = "CAACenWeb/CAACenSiteMap.htm";
  }
  window.open(url, "CAAPage");
}
