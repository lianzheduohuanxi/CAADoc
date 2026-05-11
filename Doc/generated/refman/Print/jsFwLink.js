var objet=new Array; 
     objet["class"]=new Array; 
     objet["exception"]=new Array; 
     objet["collection"]=new Array; 
     objet["notification"]=new Array; 
     objet["interface"]=new Array; 
     objet["struct"]=new Array; 
     objet["enum"]=new Array; 
     objet["define"]=new Array; 
     objet["typedef"]=new Array; 
     objet["function"]=new Array; 
 	var DSCharacteristic=new Array ; 
 objet["class"]["CATPrint2DRep"]=0;
objet["class"][0]="../Print/class_CATPrint2DRep_9438.htm";
objet["class"]["CATPrint2DRepImage"]=1;
objet["class"][1]="../Print/class_CATPrint2DRepImage_16733.htm";
objet["class"]["CATPrint3DRepImage"]=2;
objet["class"][2]="../Print/class_CATPrint3DRepImage_16741.htm";
objet["class"]["CATPrintAlbumDialog"]=3;
objet["class"][3]="../Print/class_CATPrintAlbumDialog_19496.htm";
objet["class"]["CATPrintCaptureDialog"]=4;
objet["class"][4]="../Print/class_CATPrintCaptureDialog_23718.htm";
objet["class"]["CATPrintDialog"]=5;
objet["class"][5]="../Print/class_CATPrintDialog_11469.htm";
objet["class"]["CATPrintFile"]=6;
objet["class"][6]="../Print/class_CATPrintFile_8847.htm";
objet["class"]["CATPrintPixelImageDevice"]=7;
objet["class"][7]="../Print/class_CATPrintPixelImageDevice_29847.htm";
objet["class"]["CATPrintSupportImage"]=8;
objet["class"][8]="../Print/class_CATPrintSupportImage_21919.htm";
objet["class"]["CATPrintTextImage"]=9;
objet["class"][9]="../Print/class_CATPrintTextImage_16020.htm";
objet["class"]["CATPrintViewerDialog"]=10;
objet["class"][10]="../Print/class_CATPrintViewerDialog_21667.htm";
objet["class"]["CATPrintViewerImage"]=11;
objet["class"][11]="../Print/class_CATPrintViewerImage_19575.htm";
objet["class"]["CATPrinterManagerDialog"]=12;
objet["class"][12]="../Print/class_CATPrinterManagerDialog_27830.htm";
objet["class"]["CATVectorImage"]=13;
objet["class"][13]="../Print/class_CATVectorImage_11363.htm";
function getDsCharacteristic(name,itype) { 
     var dsCh = null; 
     if (name!=null && itype!=null && itype == "class") { 
         dsCh = DSCharacteristic[name]; 
     } 
     if (dsCh == null) { 
        dsCh=itype; 
    }   
    return dsCh; 
 } 
 function locateObject(name,itype,NorP){ 
 if(name==null || itype==null || NorP==null) return 0; 
 var type = getDsCharacteristic(name,itype);    
 var findnum=objet[type][name]; 
 var findobj;   
 if(NorP==1 && findnum!=null){ findobj=objet[type][findnum+1];} 
 else {findobj=objet[type][findnum-1];}       
 //alert(findobj); 
 if(findobj!=null){      
   return 1; 
 }else{ 
    return 0; 
 } 
 } 
 function openLinkNP(name,itype,NorP){ 
 if(name==null || itype==null || NorP==null) return 0; 
 var type = getDsCharacteristic(name,itype);    
 var findnum=objet[type][name]; 
 var findobj;   
 if(NorP==1 && findnum!=null){ findobj=objet[type][findnum+1];} 
 else {findobj=objet[type][findnum-1];}       
 //alert(findobj); 
 if(findobj!=null){ 
     this.location=findobj; 
 } 
 }