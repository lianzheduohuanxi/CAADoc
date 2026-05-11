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
 objet["class"]["CATESamImageDeformation"]=0;
objet["class"][0]="../CATAnalysisVisuInterfaces/class_CATESamImageDeformation_58466.htm";
objet["class"]["CATESamImageOwner"]=1;
objet["class"][1]="../CATAnalysisVisuInterfaces/class_CATESamImageOwner_46140.htm";
objet["enum"]["CATSamAxisSystemType"]=0;
objet["enum"][0]="../CATAnalysisVisuInterfaces/enum_CATSamAxisSystemType_51976.htm";
objet["enum"]["CATSamColorType"]=1;
objet["enum"][1]="../CATAnalysisVisuInterfaces/enum_CATSamColorType_42865.htm";
objet["enum"]["CATSamComparisonOperator"]=2;
objet["enum"][2]="../CATAnalysisVisuInterfaces/enum_CATSamComparisonOperator_61271.htm";
objet["enum"]["CATSamComplexPart"]=3;
objet["enum"][3]="../CATAnalysisVisuInterfaces/enum_CATSamComplexPart_46091.htm";
objet["enum"]["CATSamCoordinateSystem"]=4;
objet["enum"][4]="../CATAnalysisVisuInterfaces/enum_CATSamCoordinateSystem_56373.htm";
objet["enum"]["CATSamFilterDomain"]=5;
objet["enum"][5]="../CATAnalysisVisuInterfaces/enum_CATSamFilterDomain_47554.htm";
objet["enum"]["CATSamSymbolType"]=6;
objet["enum"][6]="../CATAnalysisVisuInterfaces/enum_CATSamSymbolType_44498.htm";
objet["enum"]["CATSamVisuTypeName"]=7;
objet["enum"][7]="../CATAnalysisVisuInterfaces/enum_CATSamVisuTypeName_47497.htm";
objet["interface"]["CATISPMProcess"]=0;
objet["interface"][0]="../CATAnalysisVisuInterfaces/interface_CATISPMProcess_44138.htm";
objet["interface"]["CATISPMProcessAccess"]=1;
objet["interface"][1]="../CATAnalysisVisuInterfaces/interface_CATISPMProcessAccess_54089.htm";
objet["interface"]["CATISamImage"]=2;
objet["interface"][2]="../CATAnalysisVisuInterfaces/interface_CATISamImage_41365.htm";
objet["interface"]["CATISamImageAttributes"]=3;
objet["interface"][3]="../CATAnalysisVisuInterfaces/interface_CATISamImageAttributes_59078.htm";
objet["interface"]["CATISamImageAxisSystem"]=4;
objet["interface"][4]="../CATAnalysisVisuInterfaces/interface_CATISamImageAxisSystem_58868.htm";
objet["interface"]["CATISamImageColorMap"]=5;
objet["interface"][5]="../CATAnalysisVisuInterfaces/interface_CATISamImageColorMap_53796.htm";
objet["interface"]["CATISamImageDeformation"]=6;
objet["interface"][6]="../CATAnalysisVisuInterfaces/interface_CATISamImageDeformation_61065.htm";
objet["interface"]["CATISamImageDisplayManager"]=7;
objet["interface"][7]="../CATAnalysisVisuInterfaces/interface_CATISamImageDisplayManager_67881.htm";
objet["interface"]["CATISamImageFactory"]=8;
objet["interface"][8]="../CATAnalysisVisuInterfaces/interface_CATISamImageFactory_52484.htm";
objet["interface"]["CATISamImageFilters"]=9;
objet["interface"][9]="../CATAnalysisVisuInterfaces/interface_CATISamImageFilters_52446.htm";
objet["interface"]["CATISamImageGroup"]=10;
objet["interface"][10]="../CATAnalysisVisuInterfaces/interface_CATISamImageGroup_48800.htm";
objet["interface"]["CATISamImageOutput"]=11;
objet["interface"][11]="../CATAnalysisVisuInterfaces/interface_CATISamImageOutput_50982.htm";
objet["interface"]["CATISamImageOwner"]=12;
objet["interface"][12]="../CATAnalysisVisuInterfaces/interface_CATISamImageOwner_48739.htm";
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