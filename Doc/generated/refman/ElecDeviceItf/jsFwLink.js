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
 objet["class"]["CATElbDevice"]=0;
objet["class"][0]="../ElecDeviceItf/class_CATElbDevice_15332.htm";
objet["enum"]["CATElecDevice"]=0;
objet["enum"][0]="../ElecDeviceItf/enum_CATElecDevice_16097.htm";
objet["interface"]["CATIElbBackShell"]=0;
objet["interface"][0]="../ElecDeviceItf/interface_CATIElbBackShell_23113.htm";
objet["interface"]["CATIElbBackShellCnctPt"]=1;
objet["interface"][1]="../ElecDeviceItf/interface_CATIElbBackShellCnctPt_34077.htm";
objet["interface"]["CATIElbBundleCnctPt"]=2;
objet["interface"][2]="../ElecDeviceItf/interface_CATIElbBundleCnctPt_28296.htm";
objet["interface"]["CATIElbCavity"]=3;
objet["interface"][3]="../ElecDeviceItf/interface_CATIElbCavity_19393.htm";
objet["interface"]["CATIElbConnectorCnctPt"]=4;
objet["interface"][4]="../ElecDeviceItf/interface_CATIElbConnectorCnctPt_34790.htm";
objet["interface"]["CATIElbConnectorShell"]=5;
objet["interface"][5]="../ElecDeviceItf/interface_CATIElbConnectorShell_32952.htm";
objet["interface"]["CATIElbContactInstance"]=6;
objet["interface"][6]="../ElecDeviceItf/interface_CATIElbContactInstance_34999.htm";
objet["interface"]["CATIElbDeviceInstance"]=7;
objet["interface"][7]="../ElecDeviceItf/interface_CATIElbDeviceInstance_32605.htm";
objet["interface"]["CATIElbEquipment"]=8;
objet["interface"][8]="../ElecDeviceItf/interface_CATIElbEquipment_23931.htm";
objet["interface"]["CATIElbExternalSplice"]=9;
objet["interface"][9]="../ElecDeviceItf/interface_CATIElbExternalSplice_32816.htm";
objet["interface"]["CATIElbFactory"]=10;
objet["interface"][10]="../ElecDeviceItf/interface_CATIElbFactory_20787.htm";
objet["interface"]["CATIElbFillerPlugInstance"]=11;
objet["interface"][11]="../ElecDeviceItf/interface_CATIElbFillerPlugInstance_42008.htm";
objet["interface"]["CATIElbInternalSplice"]=12;
objet["interface"][12]="../ElecDeviceItf/interface_CATIElbInternalSplice_32764.htm";
objet["interface"]["CATIElbMountingEquipment"]=13;
objet["interface"][13]="../ElecDeviceItf/interface_CATIElbMountingEquipment_40535.htm";
objet["interface"]["CATIElbMountingEquipmentReference"]=14;
objet["interface"][14]="../ElecDeviceItf/interface_CATIElbMountingEquipmentReference_66129.htm";
objet["interface"]["CATIElbPrdWkbCfgAddin"]=15;
objet["interface"][15]="../ElecDeviceItf/interface_CATIElbPrdWkbCfgAddin_31482.htm";
objet["interface"]["CATIElbPrtWkbCfgAddin"]=16;
objet["interface"][16]="../ElecDeviceItf/interface_CATIElbPrtWkbCfgAddin_31626.htm";
objet["interface"]["CATIElbSingleConnector"]=17;
objet["interface"][17]="../ElecDeviceItf/interface_CATIElbSingleConnector_35301.htm";
objet["interface"]["CATIElbSingleConnectorReference"]=18;
objet["interface"][18]="../ElecDeviceItf/interface_CATIElbSingleConnectorReference_59073.htm";
objet["interface"]["CATIElbSupport"]=19;
objet["interface"][19]="../ElecDeviceItf/interface_CATIElbSupport_21050.htm";
objet["interface"]["CATIElbTermination"]=20;
objet["interface"][20]="../ElecDeviceItf/interface_CATIElbTermination_27401.htm";
objet["interface"]["CATIElbUipDevices"]=21;
objet["interface"][21]="../ElecDeviceItf/interface_CATIElbUipDevices_25064.htm";
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