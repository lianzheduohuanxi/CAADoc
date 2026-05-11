//---------------------------------------------------------------------------------------------------------------------------------------
// VD1 : IR IR-022766
//       Description : IE8 doc : Highlight for searching word in doc is not working on some OS 
//       Cause : Previous code was not ckeching for internet explorer version IE8 so it is creating problem on IE8
//       Fix : Now we are checking for IE8 also
function lib_bwcheck()
{ 
  this.ver=navigator.appVersion;
  this.agent=navigator.userAgent;
  this.dom=document.getElementById?1:0;
  //this.ie5=(this.ver.indexOf("MSIE 5")>-1 && this.dom)?1:0;
  //this.ie6=(this.ver.indexOf("MSIE 6")>-1 && this.dom)?1:0;
  //this.ie7=(this.ver.indexOf("MSIE 7")>-1 && this.dom)?1:0;
  // VD1 : IR IR-022766
  //this.ie8 = (this.ver.indexOf("MSIE 8") > -1 && this.dom) ? 1 : 0;
  // V2E
  this.ie_general = (this.ver.indexOf("MSIE") > -1 && this.dom) ? 1 : 0;
  // VD1 : IR IR-022766
  this.ie4=(document.all && !this.dom)?1:0;
  // VD1 : IR IR-022766
  this.ie = this.ie4 || this.ie_general;
  // VD1 : IR IR-022766
  this.mac=this.agent.indexOf("Mac")>-1;
  this.opera5=this.agent.indexOf("Opera 5")>-1;
  this.ns6=(this.dom && parseInt(this.ver) >= 5) ?1:0;
  browserVersion = parseInt(this.ver);
  this.ns4=(((navigator.appName.indexOf('Netscape') != -1) && (browserVersion == 4)) || typeof document.classes != "undefined")?1:0;
  // VD1 : IR IR-022766
  this.bw = (this.ie_general || this.ie4 || this.ns4 || this.ns6 || this.opera5 || this.dom)
  // VD1 : IR IR-022766
  return this
}

//---------------------------------------------------------------------------------------------------------------------------------------
var bw = new lib_bwcheck();
var n = 0;
var theframe = "DS_SEARCH";

/*
* Function returns applets document base.
*/
function getAppletCodeBase(){
	return document.location.href;
}

//---------------------------------------------------------------------------------------------------------------------------------------
function chercheSurPage(chaine,theframe)
{
  //alert("mot recherche : " + chaine);
  //alert("nom du frame : " + theframe);
  var where;
  var ok;
  where = window.parent.frames[theframe]; 

  if (chaine == "") { return false; }

  //alert ("chaine recherchee : " + chaine);
  if (!bw.ie)
  {
    // alert('LAYERS');
    where.focus();
    if (!where.find(chaine))
    {
      while(where.find(chaine, false, true))
      {
        n++;
      }
    }
    else
    {
        n++;
    }
    if (n == 0)
    {
//START QUOTE TRANSLATABLE 2
      alert("\"" + chaine + "\" word has not been found");
//END QUOTE TRANSLATABLE
    }
  }
  if (bw.ie)
  {
    //alert('ALL');
    var texte = where.document.body.createTextRange();
    for (var i = 0; i <= n && (ok = texte.findText(chaine)) != false; i++)
    {
      texte.moveStart("character", 1);
      texte.moveEnd("textedit");
    }
    if (ok)
    {
      texte.moveStart("character", -1);
      texte.findText(chaine);
      texte.select();
      texte.scrollIntoView();
      n++;
    }
    else
    {
      if (n > 0)
      {
        n = 0;
        chercheSurPage(chaine,theframe);
      }
      else
      {
//START QUOTE TRANSLATABLE 2
        alert("\"" + chaine + "\" word has not been found");
//END QUOTE TRANSLATABLE
      }
    }
  }
  return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------
function ShowPage (page,theframe,mot)
{
  var where;
  n = 0;

  // alert ("page : " + page + ", theframe : " + theframe + ", mot : " + mot);

  if ( theframe != "new" )
  { 
    where = window.parent.frames[theframe]; 
    //alert("chargement page");
    where.location.href = page;
    //alert("fin chargement page");
  }
  else
  {
    var loc = "CAACenMLPOpenPage.htm?page=" + page + ";mots=" + mot;
    var win = open(loc,"NEWPAGE");
    win.focus();
  }
  return;
}

//---------------------------------------------------------------------------------------------------------------------------------------
function temporisation(mot,dest)
{
  // alert("Entree temporisation : mot = " + mot + ", dest = " + dest);
  setTimeout("chercheSurPage('" + mot + "','" + dest+ "')",400);
}

//---------------------------------------------------------------------------------------------------------------------------------------
function top_location(page)
{
  top.location = page;
}

//---------------------------------------------------------------------------------------------------------------------------------------
function writhtml(html)
{
  document.writeln(html);
}
