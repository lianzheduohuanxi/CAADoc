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
 objet["define"]["CATSPPAttrKind"]=0;
objet["define"][0]="../DMAPSInterfaces/define_CATSPPAttrKind_21096.htm";
objet["define"]["NULL_string"]=1;
objet["define"][1]="../DMAPSInterfaces/define_NULL_string_17987.htm";
objet["enum"]["CATPcs3DViewerType"]=0;
objet["enum"][0]="../DMAPSInterfaces/enum_CATPcs3DViewerType_26691.htm";
objet["enum"]["CATSPP3DRenderStyle"]=1;
objet["enum"][1]="../DMAPSInterfaces/enum_CATSPP3DRenderStyle_28254.htm";
objet["enum"]["CATSPPAttributeFilter"]=2;
objet["enum"][2]="../DMAPSInterfaces/enum_CATSPPAttributeFilter_32984.htm";
objet["enum"]["CATSPPDisplayNameMode"]=3;
objet["enum"][3]="../DMAPSInterfaces/enum_CATSPPDisplayNameMode_32041.htm";
objet["enum"]["CATSPPExpandCollapseActivation"]=4;
objet["enum"][4]="../DMAPSInterfaces/enum_CATSPPExpandCollapseActivation_56320.htm";
objet["enum"]["CATSPPFilter"]=5;
objet["enum"][5]="../DMAPSInterfaces/enum_CATSPPFilter_17848.htm";
objet["enum"]["CATSPPFirstPPItemFilter"]=6;
objet["enum"][6]="../DMAPSInterfaces/enum_CATSPPFirstPPItemFilter_36536.htm";
objet["enum"]["CATSPPItemFilter"]=7;
objet["enum"][7]="../DMAPSInterfaces/enum_CATSPPItemFilter_23343.htm";
objet["enum"]["CATSPPListDisplayOrder"]=8;
objet["enum"][8]="../DMAPSInterfaces/enum_CATSPPListDisplayOrder_34959.htm";
objet["enum"]["CATSPPLogicalActivitiesFilter"]=9;
objet["enum"][9]="../DMAPSInterfaces/enum_CATSPPLogicalActivitiesFilter_53143.htm";
objet["enum"]["CATSPPResourceFilter"]=10;
objet["enum"][10]="../DMAPSInterfaces/enum_CATSPPResourceFilter_30803.htm";
objet["interface"]["CATINavigateObjectPPR"]=0;
objet["interface"][0]="../DMAPSInterfaces/interface_CATINavigateObjectPPR_34379.htm";
objet["interface"]["CATISPPAbstractActivity"]=1;
objet["interface"][1]="../DMAPSInterfaces/interface_CATISPPAbstractActivity_40630.htm";
objet["interface"]["CATISPPActivity"]=2;
objet["interface"][2]="../DMAPSInterfaces/interface_CATISPPActivity_25107.htm";
objet["interface"]["CATISPPActivityRoot"]=3;
objet["interface"][3]="../DMAPSInterfaces/interface_CATISPPActivityRoot_32088.htm";
objet["interface"]["CATISPPActivityType"]=4;
objet["interface"][4]="../DMAPSInterfaces/interface_CATISPPActivityType_32025.htm";
objet["interface"]["CATISPPActivityTypeFactory"]=5;
objet["interface"][5]="../DMAPSInterfaces/interface_CATISPPActivityTypeFactory_48240.htm";
objet["interface"]["CATISPPChildManagement"]=6;
objet["interface"][6]="../DMAPSInterfaces/interface_CATISPPChildManagement_37494.htm";
objet["interface"]["CATISPPConfig"]=7;
objet["interface"][7]="../DMAPSInterfaces/interface_CATISPPConfig_21764.htm";
objet["interface"]["CATISPPContainer"]=8;
objet["interface"][8]="../DMAPSInterfaces/interface_CATISPPContainer_26394.htm";
objet["interface"]["CATISPPFlowMgt"]=9;
objet["interface"][9]="../DMAPSInterfaces/interface_CATISPPFlowMgt_23140.htm";
objet["interface"]["CATISPPInitCreation"]=10;
objet["interface"][10]="../DMAPSInterfaces/interface_CATISPPInitCreation_31565.htm";
objet["interface"]["CATISPPItem"]=11;
objet["interface"][11]="../DMAPSInterfaces/interface_CATISPPItem_19444.htm";
objet["interface"]["CATISPPItemMgt"]=12;
objet["interface"][12]="../DMAPSInterfaces/interface_CATISPPItemMgt_23035.htm";
objet["interface"]["CATISPPLibTabSettingAtt"]=13;
objet["interface"][13]="../DMAPSInterfaces/interface_CATISPPLibTabSettingAtt_39442.htm";
objet["interface"]["CATISPPProcessContainer"]=14;
objet["interface"][14]="../DMAPSInterfaces/interface_CATISPPProcessContainer_40358.htm";
objet["interface"]["CATISPPProductIO"]=15;
objet["interface"][15]="../DMAPSInterfaces/interface_CATISPPProductIO_25667.htm";
objet["interface"]["CATISPPResourceManagement"]=16;
objet["interface"][16]="../DMAPSInterfaces/interface_CATISPPResourceManagement_45014.htm";
objet["interface"]["CATISPPTreeTabSettingAtt"]=17;
objet["interface"][17]="../DMAPSInterfaces/interface_CATISPPTreeTabSettingAtt_41917.htm";
objet["interface"]["CATISPPVerifTabSettingAtt"]=18;
objet["interface"][18]="../DMAPSInterfaces/interface_CATISPPVerifTabSettingAtt_44416.htm";
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