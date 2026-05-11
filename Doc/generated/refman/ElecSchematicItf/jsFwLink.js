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
 objet["interface"]["CATIEdiAssemblyConnector"]=0;
objet["interface"][0]="../ElecSchematicItf/interface_CATIEdiAssemblyConnector_44591.htm";
objet["interface"]["CATIEdiBusBar"]=1;
objet["interface"][1]="../ElecSchematicItf/interface_CATIEdiBusBar_23196.htm";
objet["interface"]["CATIEdiCable"]=2;
objet["interface"][2]="../ElecSchematicItf/interface_CATIEdiCable_21986.htm";
objet["interface"]["CATIEdiCableExtremity"]=3;
objet["interface"][3]="../ElecSchematicItf/interface_CATIEdiCableExtremity_37691.htm";
objet["interface"]["CATIEdiCableReference"]=4;
objet["interface"][4]="../ElecSchematicItf/interface_CATIEdiCableReference_36648.htm";
objet["interface"]["CATIEdiEquipment"]=5;
objet["interface"][5]="../ElecSchematicItf/interface_CATIEdiEquipment_28291.htm";
objet["interface"]["CATIEdiEquipmentReference"]=6;
objet["interface"][6]="../ElecSchematicItf/interface_CATIEdiEquipmentReference_46597.htm";
objet["interface"]["CATIEdiJunctionBox"]=7;
objet["interface"][7]="../ElecSchematicItf/interface_CATIEdiJunctionBox_31427.htm";
objet["interface"]["CATIEdiJunctionBoxReference"]=8;
objet["interface"][8]="../ElecSchematicItf/interface_CATIEdiJunctionBoxReference_51555.htm";
objet["interface"]["CATIEdiMatingConnector"]=9;
objet["interface"][9]="../ElecSchematicItf/interface_CATIEdiMatingConnector_39675.htm";
objet["interface"]["CATIEdiPin"]=10;
objet["interface"][10]="../ElecSchematicItf/interface_CATIEdiPin_20058.htm";
objet["interface"]["CATIEdiPlug"]=11;
objet["interface"][11]="../ElecSchematicItf/interface_CATIEdiPlug_21175.htm";
objet["interface"]["CATIEdiPlugReference"]=12;
objet["interface"][12]="../ElecSchematicItf/interface_CATIEdiPlugReference_34926.htm";
objet["interface"]["CATIEdiProduct"]=13;
objet["interface"][13]="../ElecSchematicItf/interface_CATIEdiProduct_25122.htm";
objet["interface"]["CATIEdiReferenceFactory"]=14;
objet["interface"][14]="../ElecSchematicItf/interface_CATIEdiReferenceFactory_41806.htm";
objet["interface"]["CATIEdiReplaceCable"]=15;
objet["interface"][15]="../ElecSchematicItf/interface_CATIEdiReplaceCable_32321.htm";
objet["interface"]["CATIEdiSocket"]=16;
objet["interface"][16]="../ElecSchematicItf/interface_CATIEdiSocket_23601.htm";
objet["interface"]["CATIEdiSocketReference"]=17;
objet["interface"][17]="../ElecSchematicItf/interface_CATIEdiSocketReference_39174.htm";
objet["interface"]["CATIEdiSwitch"]=18;
objet["interface"][18]="../ElecSchematicItf/interface_CATIEdiSwitch_23643.htm";
objet["interface"]["CATIEdiSwitchReference"]=19;
objet["interface"][19]="../ElecSchematicItf/interface_CATIEdiSwitchReference_39216.htm";
objet["interface"]["CATIEdiTerminalBoard"]=20;
objet["interface"][20]="../ElecSchematicItf/interface_CATIEdiTerminalBoard_34795.htm";
objet["interface"]["CATIEdiTerminalBoardReference"]=21;
objet["interface"][21]="../ElecSchematicItf/interface_CATIEdiTerminalBoardReference_56745.htm";
objet["interface"]["CATIEdiWidePin"]=22;
objet["interface"][22]="../ElecSchematicItf/interface_CATIEdiWidePin_24597.htm";
objet["interface"]["CATIEdiWire"]=23;
objet["interface"][23]="../ElecSchematicItf/interface_CATIEdiWire_21153.htm";
objet["interface"]["CATIEdiWireCtr"]=24;
objet["interface"][24]="../ElecSchematicItf/interface_CATIEdiWireCtr_24764.htm";
objet["interface"]["CATIEdiWireExtremity"]=25;
objet["interface"][25]="../ElecSchematicItf/interface_CATIEdiWireExtremity_35887.htm";
objet["interface"]["CATIEluWkbCfgAddin"]=26;
objet["interface"][26]="../ElecSchematicItf/interface_CATIEluWkbCfgAddin_30450.htm";
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