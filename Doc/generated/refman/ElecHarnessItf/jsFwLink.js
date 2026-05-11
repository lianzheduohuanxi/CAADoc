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
 objet["enum"]["CATEhiProfileType"]=0;
objet["enum"][0]="../ElecHarnessItf/enum_CATEhiProfileType_24016.htm";
objet["enum"]["CatEhiInsertMode"]=1;
objet["enum"][1]="../ElecHarnessItf/enum_CatEhiInsertMode_22231.htm";
objet["enum"]["CatEhiSupportMode"]=2;
objet["enum"][2]="../ElecHarnessItf/enum_CatEhiSupportMode_24144.htm";
objet["interface"]["CATIEhiBnlSegmentExtremity"]=0;
objet["interface"][0]="../ElecHarnessItf/interface_CATIEhiBnlSegmentExtremity_47308.htm";
objet["interface"]["CATIEhiBranchable"]=1;
objet["interface"][1]="../ElecHarnessItf/interface_CATIEhiBranchable_26473.htm";
objet["interface"]["CATIEhiBundleSegment"]=2;
objet["interface"][2]="../ElecHarnessItf/interface_CATIEhiBundleSegment_32391.htm";
objet["interface"]["CATIEhiFLEX"]=3;
objet["interface"][3]="../ElecHarnessItf/interface_CATIEhiFLEX_17519.htm";
objet["interface"]["CATIEhiFactory"]=4;
objet["interface"][4]="../ElecHarnessItf/interface_CATIEhiFactory_22399.htm";
objet["interface"]["CATIEhiGeoBundle"]=5;
objet["interface"][5]="../ElecHarnessItf/interface_CATIEhiGeoBundle_24818.htm";
objet["interface"]["CATIEhiMechanicalImport"]=6;
objet["interface"][6]="../ElecHarnessItf/interface_CATIEhiMechanicalImport_39016.htm";
objet["interface"]["CATIEhiMultiBranchable"]=7;
objet["interface"][7]="../ElecHarnessItf/interface_CATIEhiMultiBranchable_36205.htm";
objet["interface"]["CATIEhiNetwork"]=8;
objet["interface"][8]="../ElecHarnessItf/interface_CATIEhiNetwork_22488.htm";
objet["interface"]["CATIEhiNetworkExtremity"]=9;
objet["interface"][9]="../ElecHarnessItf/interface_CATIEhiNetworkExtremity_40135.htm";
objet["interface"]["CATIEhiPositionPoint"]=10;
objet["interface"][10]="../ElecHarnessItf/interface_CATIEhiPositionPoint_32917.htm";
objet["interface"]["CATIEhiPrdWkbCfgAddin"]=11;
objet["interface"][11]="../ElecHarnessItf/interface_CATIEhiPrdWkbCfgAddin_33094.htm";
objet["interface"]["CATIEhiProtection"]=12;
objet["interface"][12]="../ElecHarnessItf/interface_CATIEhiProtection_27253.htm";
objet["interface"]["CATIEhiPrtWkbCfgAddin"]=13;
objet["interface"][13]="../ElecHarnessItf/interface_CATIEhiPrtWkbCfgAddin_33238.htm";
objet["interface"]["CATIEleUipDuplicate"]=14;
objet["interface"][14]="../ElecHarnessItf/interface_CATIEleUipDuplicate_30371.htm";
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