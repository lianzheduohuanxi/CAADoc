var xrefwindow;

function xref(fic, val) {
  xrefwindow=window.open(fic+"#"+val, 'xref', 'toolbar=no,resizable=yes,height=150,width=450,scrollbars=yes,screenX=5,screenY=5,top=5,left=5'); 
  if (navigator.appName == "Netscape") 
  	window.top.onfocus=function() { window.xrefwindow.close(); }
  else
  	window.onfocus=function() { window.xrefwindow.close(); };
  return;
  }

function xrefToc(val) {
  return xref('../CAAScdBase/CAAScdTocXrefs.htm', val);
  }
