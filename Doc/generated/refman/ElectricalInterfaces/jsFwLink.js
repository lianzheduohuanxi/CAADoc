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
 objet["interface"]["CATIEleDocServices"]=0;
objet["interface"][0]="../ElectricalInterfaces/interface_CATIEleDocServices_38913.htm";
objet["interface"]["CATIEleDrawingServices"]=1;
objet["interface"][1]="../ElectricalInterfaces/interface_CATIEleDrawingServices_47267.htm";
objet["interface"]["CATIEleUipFilteringCriteria"]=2;
objet["interface"][2]="../ElectricalInterfaces/interface_CATIEleUipFilteringCriteria_59435.htm";
objet["interface"]["CATIEleUipSystems"]=3;
objet["interface"][3]="../ElectricalInterfaces/interface_CATIEleUipSystems_37670.htm";
objet["interface"]["CATIElec2DRepresentation"]=4;
objet["interface"][4]="../ElectricalInterfaces/interface_CATIElec2DRepresentation_51804.htm";
objet["interface"]["CATIElecAttrAccess"]=5;
objet["interface"][5]="../ElectricalInterfaces/interface_CATIElecAttrAccess_38723.htm";
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