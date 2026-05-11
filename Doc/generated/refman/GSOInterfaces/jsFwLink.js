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
 objet["interface"]["CATIGSMDevelop"]=0;
objet["interface"][0]="../GSOInterfaces/interface_CATIGSMDevelop_20693.htm";
objet["interface"]["CATIGSMTransfer"]=1;
objet["interface"][1]="../GSOInterfaces/interface_CATIGSMTransfer_22232.htm";
objet["interface"]["CATIGSMUnfold"]=2;
objet["interface"][2]="../GSOInterfaces/interface_CATIGSMUnfold_19252.htm";
objet["interface"]["CATIGSOBump"]=3;
objet["interface"][3]="../GSOInterfaces/interface_CATIGSOBump_16872.htm";
objet["interface"]["CATIGSOFactory"]=4;
objet["interface"][4]="../GSOInterfaces/interface_CATIGSOFactory_20852.htm";
objet["interface"]["CATIGSOFactoryGeo"]=5;
objet["interface"][5]="../GSOInterfaces/interface_CATIGSOFactoryGeo_25137.htm";
objet["interface"]["CATIGSOWrapCurve"]=6;
objet["interface"][6]="../GSOInterfaces/interface_CATIGSOWrapCurve_23677.htm";
objet["interface"]["CATIGSOWrapSurface"]=7;
objet["interface"][7]="../GSOInterfaces/interface_CATIGSOWrapSurface_26870.htm";
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