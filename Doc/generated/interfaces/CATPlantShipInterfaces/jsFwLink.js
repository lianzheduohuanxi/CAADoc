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
 objet["enum"]["CatPspIDLApplicationID"]=0;
objet["enum"][0]="../CATPlantShipInterfaces/enum_CatPspIDLApplicationID_46647.htm";
objet["enum"]["CatPspIDLAttrDataType"]=1;
objet["enum"][1]="../CATPlantShipInterfaces/enum_CatPspIDLAttrDataType_45268.htm";
objet["enum"]["CatPspIDLDomainID"]=2;
objet["enum"][2]="../CATPlantShipInterfaces/enum_CatPspIDLDomainID_36764.htm";
objet["enum"]["CatPspIDLFlowCapability"]=3;
objet["enum"][3]="../CATPlantShipInterfaces/enum_CatPspIDLFlowCapability_50217.htm";
objet["enum"]["CatPspIDLFlowReality"]=4;
objet["enum"][4]="../CATPlantShipInterfaces/enum_CatPspIDLFlowReality_43785.htm";
objet["enum"]["CatPspIDLFunctionStatus"]=5;
objet["enum"][5]="../CATPlantShipInterfaces/enum_CatPspIDLFunctionStatus_50841.htm";
objet["enum"]["CatPspIDLPartConnectorType"]=6;
objet["enum"][6]="../CATPlantShipInterfaces/enum_CatPspIDLPartConnectorType_57923.htm";
objet["interface"]["PspAppFactory"]=0;
objet["interface"][0]="../CATPlantShipInterfaces/interface_PspAppFactory_35796.htm";
objet["interface"]["PspApplication"]=1;
objet["interface"][1]="../CATPlantShipInterfaces/interface_PspApplication_37170.htm";
objet["interface"]["PspAttribute"]=2;
objet["interface"][2]="../CATPlantShipInterfaces/interface_PspAttribute_34608.htm";
objet["interface"]["PspAttributeReport"]=3;
objet["interface"][3]="../CATPlantShipInterfaces/interface_PspAttributeReport_43934.htm";
objet["interface"]["PspBuildPart"]=4;
objet["interface"][4]="../CATPlantShipInterfaces/interface_PspBuildPart_34310.htm";
objet["interface"]["PspClass"]=5;
objet["interface"][5]="../CATPlantShipInterfaces/interface_PspClass_30455.htm";
objet["interface"]["PspCntrFlow"]=6;
objet["interface"][6]="../CATPlantShipInterfaces/interface_PspCntrFlow_33290.htm";
objet["interface"]["PspConnectable"]=7;
objet["interface"][7]="../CATPlantShipInterfaces/interface_PspConnectable_36897.htm";
objet["interface"]["PspConnector"]=8;
objet["interface"][8]="../CATPlantShipInterfaces/interface_PspConnector_34604.htm";
objet["interface"]["PspFunctional"]=9;
objet["interface"][9]="../CATPlantShipInterfaces/interface_PspFunctional_35778.htm";
objet["interface"]["PspGroup"]=10;
objet["interface"][10]="../CATPlantShipInterfaces/interface_PspGroup_30552.htm";
objet["interface"]["PspGroupable"]=11;
objet["interface"][11]="../CATPlantShipInterfaces/interface_PspGroupable_34401.htm";
objet["interface"]["PspID"]=12;
objet["interface"][12]="../CATPlantShipInterfaces/interface_PspID_28333.htm";
objet["interface"]["PspLightBend"]=13;
objet["interface"][13]="../CATPlantShipInterfaces/interface_PspLightBend_34078.htm";
objet["interface"]["PspLightConnector"]=14;
objet["interface"][14]="../CATPlantShipInterfaces/interface_PspLightConnector_41898.htm";
objet["interface"]["PspLightPart"]=15;
objet["interface"][15]="../CATPlantShipInterfaces/interface_PspLightPart_34370.htm";
objet["interface"]["PspListOfBSTRs"]=16;
objet["interface"][16]="../CATPlantShipInterfaces/interface_PspListOfBSTRs_35957.htm";
objet["interface"]["PspListOfDoubles"]=17;
objet["interface"][17]="../CATPlantShipInterfaces/interface_PspListOfDoubles_39858.htm";
objet["interface"]["PspListOfLongs"]=18;
objet["interface"][18]="../CATPlantShipInterfaces/interface_PspListOfLongs_36865.htm";
objet["interface"]["PspListOfObjects"]=19;
objet["interface"][19]="../CATPlantShipInterfaces/interface_PspListOfObjects_39835.htm";
objet["interface"]["PspLogicalLine"]=20;
objet["interface"][20]="../CATPlantShipInterfaces/interface_PspLogicalLine_36648.htm";
objet["interface"]["PspObject"]=21;
objet["interface"][21]="../CATPlantShipInterfaces/interface_PspObject_31228.htm";
objet["interface"]["PspPartConnector"]=22;
objet["interface"][22]="../CATPlantShipInterfaces/interface_PspPartConnector_40254.htm";
objet["interface"]["PspPhsyicalProduct"]=23;
objet["interface"][23]="../CATPlantShipInterfaces/interface_PspPhsyicalProduct_43681.htm";
objet["interface"]["PspPhysical"]=24;
objet["interface"][24]="../CATPlantShipInterfaces/interface_PspPhysical_33273.htm";
objet["interface"]["PspPlacePart"]=25;
objet["interface"][25]="../CATPlantShipInterfaces/interface_PspPlacePart_34229.htm";
objet["interface"]["PspResource"]=26;
objet["interface"][26]="../CATPlantShipInterfaces/interface_PspResource_33365.htm";
objet["interface"]["PspSpatial"]=27;
objet["interface"][27]="../CATPlantShipInterfaces/interface_PspSpatial_32203.htm";
objet["interface"]["PspStretchableData"]=28;
objet["interface"][28]="../CATPlantShipInterfaces/interface_PspStretchableData_42840.htm";
objet["interface"]["PspTempListFactory"]=29;
objet["interface"][29]="../CATPlantShipInterfaces/interface_PspTempListFactory_43673.htm";
objet["interface"]["PspWorkbench"]=30;
objet["interface"][30]="../CATPlantShipInterfaces/interface_PspWorkbench_34377.htm";
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