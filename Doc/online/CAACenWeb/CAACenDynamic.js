mechanicalin=new Image();
mechanicalin.src="images/CAACenlogo_mechanicali.gif";
surfacicin=new Image();
surfacicin.src="images/CAACenlogo_surfacici.gif";
analysisin=new Image();
analysisin.src="images/CAACenlogo_analysisi.gif";
equipmentin=new Image();
equipmentin.src="images/CAACenlogo_equipmenti.gif";
manufacturingin=new Image();
manufacturingin.src="images/CAACenlogo_manufacturingi.gif";
DMUin=new Image();
DMUin.src="images/CAACenlogo_DMUi.gif";
life_cyclein=new Image();
life_cyclein.src="images/CAACenlogo_life_cyclei.gif";
portalin=new Image();
portalin.src="images/CAACenlogo_portali.gif";
processdetin=new Image();
processdetin.src="images/CAACenlogo_processdeti.gif";
workinstructionsin=new Image();
workinstructionsin.src="images/CAACenlogo_mechanicali.gif";
//inspectionin=new Image();
//inspectionin.src="images/CAACenlogo_inspectioni.gif";
factoryDMUin=new Image();
factoryDMUin.src="images/CAACenlogo_DMUi.gif";
offlineprogrammingin=new Image();
offlineprogrammingin.src="images/CAACenlogo_manufacturingi.gif";
infrastructurein=new Image();
infrastructurein.src="images/CAACenlogo_infrastructurei.gif";
portalDMUin=new Image();
portalDMUin.src="images/CAACenlogo_DMUi.gif";
v5vpmin=new Image();
v5vpmin.src="images/CAACenlogo_v5vpmi.gif";

mechanicalout=new Image();
mechanicalout.src="images/CAACenlogo_mechanical.gif";
surfacicout=new Image();
surfacicout.src="images/CAACenlogo_surfacic.gif";
analysisout=new Image();
analysisout.src="images/CAACenlogo_analysis.gif";
equipmentout=new Image();
equipmentout.src="images/CAACenlogo_equipment.gif";
manufacturingout=new Image();
manufacturingout.src="images/CAACenlogo_manufacturing.gif";
DMUout=new Image();
DMUout.src="images/CAACenlogo_DMU.gif";
life_cycleout=new Image();
life_cycleout.src="images/CAACenlogo_life_cycle.gif";
portalout=new Image();
portalout.src="images/CAACenlogo_portal.gif";
workinstructionsout=new Image();
workinstructionsout.src="images/CAACenlogo_mechanical.gif";
processdetout=new Image();
processdetout.src="images/CAACenlogo_processdet.gif";
factoryDMUout=new Image();
factoryDMUout.src="images/CAACenlogo_DMU.gif";
//inspectionout=new Image();
//inspectionout.src="images/CAACenlogo_inspection.gif";
offlineprogrammingout=new Image();
offlineprogrammingout.src="images/CAACenlogo_manufacturing.gif";
infrastructureout=new Image();
infrastructureout.src="images/CAACenlogo_infrastructure.gif";
portalDMUout=new Image();
portalDMUout.src="images/CAACenlogo_DMU.gif";
v5vpmout=new Image();
v5vpmout.src="images/CAACenlogo_v5vpm.gif";

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

var menuBgColor   = 0;
var menuNumberSave = 0;
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

var submenuBgColor   = 0;
var submenuNumberSave = 0;
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


