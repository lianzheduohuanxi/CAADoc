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
 objet["class"]["CATEwrEquipotential"]=0;
objet["class"][0]="../ElecRoutingItf/class_CATEwrEquipotential_28663.htm";
objet["class"]["CATEwrWire"]=1;
objet["class"][1]="../ElecRoutingItf/class_CATEwrWire_15056.htm";
objet["class"]["CATEwrWireGroup"]=2;
objet["class"][2]="../ElecRoutingItf/class_CATEwrWireGroup_21441.htm";
objet["interface"]["CATIEwrFilter"]=0;
objet["interface"][0]="../ElecRoutingItf/interface_CATIEwrFilter_21027.htm";
objet["interface"]["CATIEwrRouteSegment"]=1;
objet["interface"][1]="../ElecRoutingItf/interface_CATIEwrRouteSegment_30832.htm";
objet["interface"]["CATIEwrUipBundleSegment"]=2;
objet["interface"][2]="../ElecRoutingItf/interface_CATIEwrUipBundleSegment_38975.htm";
objet["interface"]["CATIEwrUipEquipotentials"]=3;
objet["interface"][3]="../ElecRoutingItf/interface_CATIEwrUipEquipotentials_42379.htm";
objet["interface"]["CATIEwrUipWireGroups"]=4;
objet["interface"][4]="../ElecRoutingItf/interface_CATIEwrUipWireGroups_32905.htm";
objet["interface"]["CATIEwrUipWires"]=5;
objet["interface"][5]="../ElecRoutingItf/interface_CATIEwrUipWires_23845.htm";
objet["interface"]["CATIEwrWire"]=6;
objet["interface"][6]="../ElecRoutingItf/interface_CATIEwrWire_18571.htm";
objet["interface"]["CATIEwrWkbCfgAddin"]=7;
objet["interface"][7]="../ElecRoutingItf/interface_CATIEwrWkbCfgAddin_27756.htm";
objet["typedef"]["CATEwrFilterOption"]=0;
objet["typedef"][0]="../ElecRoutingItf/typedef_CATEwrFilterOption_27612.htm";
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