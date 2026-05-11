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
 objet["enum"]["CatClashComputationType"]=0;
objet["enum"][0]="../SpaceAnalysisInterfaces/enum_CatClashComputationType_53942.htm";
objet["enum"]["CatClashExportType"]=1;
objet["enum"][1]="../SpaceAnalysisInterfaces/enum_CatClashExportType_43287.htm";
objet["enum"]["CatClashImportType"]=2;
objet["enum"][2]="../SpaceAnalysisInterfaces/enum_CatClashImportType_43220.htm";
objet["enum"]["CatClashInterferenceType"]=3;
objet["enum"][3]="../SpaceAnalysisInterfaces/enum_CatClashInterferenceType_55796.htm";
objet["enum"]["CatConflictComparison"]=4;
objet["enum"][4]="../SpaceAnalysisInterfaces/enum_CatConflictComparison_49353.htm";
objet["enum"]["CatConflictStatus"]=5;
objet["enum"][5]="../SpaceAnalysisInterfaces/enum_CatConflictStatus_41641.htm";
objet["enum"]["CatConflictType"]=6;
objet["enum"][6]="../SpaceAnalysisInterfaces/enum_CatConflictType_38102.htm";
objet["enum"]["CatDistanceComputationType"]=7;
objet["enum"][7]="../SpaceAnalysisInterfaces/enum_CatDistanceComputationType_61528.htm";
objet["enum"]["CatDistanceMeasureType"]=8;
objet["enum"][8]="../SpaceAnalysisInterfaces/enum_CatDistanceMeasureType_51155.htm";
objet["enum"]["CatGridPositionMode"]=9;
objet["enum"][9]="../SpaceAnalysisInterfaces/enum_CatGridPositionMode_44697.htm";
objet["enum"]["CatMeasurableName"]=10;
objet["enum"][10]="../SpaceAnalysisInterfaces/enum_CatMeasurableName_40819.htm";
objet["enum"]["CatSecWindowOpenMode"]=11;
objet["enum"][11]="../SpaceAnalysisInterfaces/enum_CatSecWindowOpenMode_46312.htm";
objet["enum"]["CatSectionBehavior"]=12;
objet["enum"][12]="../SpaceAnalysisInterfaces/enum_CatSectionBehavior_43080.htm";
objet["enum"]["CatSectionClippingMode"]=13;
objet["enum"][13]="../SpaceAnalysisInterfaces/enum_CatSectionClippingMode_50703.htm";
objet["enum"]["CatSectionGridStyle"]=14;
objet["enum"][14]="../SpaceAnalysisInterfaces/enum_CatSectionGridStyle_44875.htm";
objet["enum"]["CatSectionPlaneNormal"]=15;
objet["enum"][15]="../SpaceAnalysisInterfaces/enum_CatSectionPlaneNormal_48704.htm";
objet["enum"]["CatSectionPlaneOrigin"]=16;
objet["enum"][16]="../SpaceAnalysisInterfaces/enum_CatSectionPlaneOrigin_48698.htm";
objet["enum"]["CatSectionType"]=17;
objet["enum"][17]="../SpaceAnalysisInterfaces/enum_CatSectionType_36687.htm";
objet["interface"]["Clash"]=0;
objet["interface"][0]="../SpaceAnalysisInterfaces/interface_Clash_31159.htm";
objet["interface"]["ClashResult"]=1;
objet["interface"][1]="../SpaceAnalysisInterfaces/interface_ClashResult_36048.htm";
objet["interface"]["ClashResults"]=2;
objet["interface"][2]="../SpaceAnalysisInterfaces/interface_ClashResults_37313.htm";
objet["interface"]["Clashes"]=3;
objet["interface"][3]="../SpaceAnalysisInterfaces/interface_Clashes_32354.htm";
objet["interface"]["Conflict"]=4;
objet["interface"][4]="../SpaceAnalysisInterfaces/interface_Conflict_33096.htm";
objet["interface"]["Conflicts"]=5;
objet["interface"][5]="../SpaceAnalysisInterfaces/interface_Conflicts_34016.htm";
objet["interface"]["Distance"]=6;
objet["interface"][6]="../SpaceAnalysisInterfaces/interface_Distance_33018.htm";
objet["interface"]["Distances"]=7;
objet["interface"][7]="../SpaceAnalysisInterfaces/interface_Distances_33938.htm";
objet["interface"]["Inertia"]=8;
objet["interface"][8]="../SpaceAnalysisInterfaces/interface_Inertia_32321.htm";
objet["interface"]["Inertias"]=9;
objet["interface"][9]="../SpaceAnalysisInterfaces/interface_Inertias_33126.htm";
objet["interface"]["Measurable"]=10;
objet["interface"][10]="../SpaceAnalysisInterfaces/interface_Measurable_34815.htm";
objet["interface"]["MeasureSettingAtt"]=11;
objet["interface"][11]="../SpaceAnalysisInterfaces/interface_MeasureSettingAtt_44293.htm";
objet["interface"]["SPAWorkbench"]=12;
objet["interface"][12]="../SpaceAnalysisInterfaces/interface_SPAWorkbench_36841.htm";
objet["interface"]["Section"]=13;
objet["interface"][13]="../SpaceAnalysisInterfaces/interface_Section_32378.htm";
objet["interface"]["SectioningSettingAtt"]=14;
objet["interface"][14]="../SpaceAnalysisInterfaces/interface_SectioningSettingAtt_49926.htm";
objet["interface"]["Sections"]=15;
objet["interface"][15]="../SpaceAnalysisInterfaces/interface_Sections_33183.htm";
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