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
 objet["interface"]["CATIAerospaceSheetMetalFactory"]=0;
objet["interface"][0]="../CATSmaInterfaces/interface_CATIAerospaceSheetMetalFactory_60674.htm";
objet["interface"]["CATIStmCharacteristicCurves"]=1;
objet["interface"][1]="../CATSmaInterfaces/interface_CATIStmCharacteristicCurves_52861.htm";
objet["interface"]["CATIStmFlangeSurf"]=2;
objet["interface"][2]="../CATSmaInterfaces/interface_CATIStmFlangeSurf_29743.htm";
objet["interface"]["CATIStmJoggle"]=3;
objet["interface"][3]="../CATSmaInterfaces/interface_CATIStmJoggle_23775.htm";
objet["interface"]["CATIStmWeb"]=4;
objet["interface"][4]="../CATSmaInterfaces/interface_CATIStmWeb_20311.htm";
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