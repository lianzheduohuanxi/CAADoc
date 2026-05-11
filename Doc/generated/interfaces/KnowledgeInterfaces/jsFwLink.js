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
 objet["enum"]["CatAlgorithmType"]=0;
objet["enum"][0]="../KnowledgeInterfaces/enum_CatAlgorithmType_31129.htm";
objet["enum"]["CatOptimizationType"]=1;
objet["enum"][1]="../KnowledgeInterfaces/enum_CatOptimizationType_36739.htm";
objet["interface"]["Angle"]=0;
objet["interface"][0]="../KnowledgeInterfaces/interface_Angle_22474.htm";
objet["interface"]["BoolParam"]=1;
objet["interface"][1]="../KnowledgeInterfaces/interface_BoolParam_25127.htm";
objet["interface"]["Check"]=2;
objet["interface"][2]="../KnowledgeInterfaces/interface_Check_22461.htm";
objet["interface"]["ConstraintSatisfaction"]=3;
objet["interface"][3]="../KnowledgeInterfaces/interface_ConstraintSatisfaction_46023.htm";
objet["interface"]["DesignTable"]=4;
objet["interface"][4]="../KnowledgeInterfaces/interface_DesignTable_26987.htm";
objet["interface"]["Dimension"]=5;
objet["interface"][5]="../KnowledgeInterfaces/interface_Dimension_25358.htm";
objet["interface"]["EnumParam"]=6;
objet["interface"][6]="../KnowledgeInterfaces/interface_EnumParam_25141.htm";
objet["interface"]["FeatureGenerator"]=7;
objet["interface"][7]="../KnowledgeInterfaces/interface_FeatureGenerator_34212.htm";
objet["interface"]["Formula"]=8;
objet["interface"][8]="../KnowledgeInterfaces/interface_Formula_23686.htm";
objet["interface"]["FreeParameter"]=9;
objet["interface"][9]="../KnowledgeInterfaces/interface_FreeParameter_29637.htm";
objet["interface"]["FreeParameters"]=10;
objet["interface"][10]="../KnowledgeInterfaces/interface_FreeParameters_31132.htm";
objet["interface"]["IntParam"]=11;
objet["interface"][11]="../KnowledgeInterfaces/interface_IntParam_24315.htm";
objet["interface"]["KnowledgeActivateObject"]=12;
objet["interface"][12]="../KnowledgeInterfaces/interface_KnowledgeActivateObject_47316.htm";
objet["interface"]["KnowledgeObject"]=13;
objet["interface"][13]="../KnowledgeInterfaces/interface_KnowledgeObject_32165.htm";
objet["interface"]["KnowledgeSheetSettingAtt"]=14;
objet["interface"][14]="../KnowledgeInterfaces/interface_KnowledgeSheetSettingAtt_49933.htm";
objet["interface"]["LanguageSheetSettingAtt"]=15;
objet["interface"][15]="../KnowledgeInterfaces/interface_LanguageSheetSettingAtt_47546.htm";
objet["interface"]["Law"]=16;
objet["interface"][16]="../KnowledgeInterfaces/interface_Law_21765.htm";
objet["interface"]["Length"]=17;
objet["interface"][17]="../KnowledgeInterfaces/interface_Length_23044.htm";
objet["interface"]["List"]=18;
objet["interface"][18]="../KnowledgeInterfaces/interface_List_22113.htm";
objet["interface"]["ListParameter"]=19;
objet["interface"][19]="../KnowledgeInterfaces/interface_ListParameter_29701.htm";
objet["interface"]["Loop"]=20;
objet["interface"][20]="../KnowledgeInterfaces/interface_Loop_22099.htm";
objet["interface"]["Optimization"]=21;
objet["interface"][21]="../KnowledgeInterfaces/interface_Optimization_28654.htm";
objet["interface"]["OptimizationConstraint"]=22;
objet["interface"][22]="../KnowledgeInterfaces/interface_OptimizationConstraint_46337.htm";
objet["interface"]["OptimizationConstraints"]=23;
objet["interface"][23]="../KnowledgeInterfaces/interface_OptimizationConstraints_48867.htm";
objet["interface"]["Optimizations"]=24;
objet["interface"][24]="../KnowledgeInterfaces/interface_Optimizations_30034.htm";
objet["interface"]["Parameter"]=25;
objet["interface"][25]="../KnowledgeInterfaces/interface_Parameter_25302.htm";
objet["interface"]["ParameterSet"]=26;
objet["interface"][26]="../KnowledgeInterfaces/interface_ParameterSet_28335.htm";
objet["interface"]["ParameterSets"]=27;
objet["interface"][27]="../KnowledgeInterfaces/interface_ParameterSets_29715.htm";
objet["interface"]["Parameters"]=28;
objet["interface"][28]="../KnowledgeInterfaces/interface_Parameters_26337.htm";
objet["interface"]["RealParam"]=29;
objet["interface"][29]="../KnowledgeInterfaces/interface_RealParam_25089.htm";
objet["interface"]["Relation"]=30;
objet["interface"][30]="../KnowledgeInterfaces/interface_Relation_24463.htm";
objet["interface"]["Relations"]=31;
objet["interface"][31]="../KnowledgeInterfaces/interface_Relations_25383.htm";
objet["interface"]["ReportGenerationSheetSettingAtt"]=32;
objet["interface"][32]="../KnowledgeInterfaces/interface_ReportGenerationSheetSettingAtt_69714.htm";
objet["interface"]["Rule"]=33;
objet["interface"][33]="../KnowledgeInterfaces/interface_Rule_22066.htm";
objet["interface"]["SetOfEquation"]=34;
objet["interface"][34]="../KnowledgeInterfaces/interface_SetOfEquation_29661.htm";
objet["interface"]["StrParam"]=35;
objet["interface"][35]="../KnowledgeInterfaces/interface_StrParam_24317.htm";
objet["interface"]["ToleranceSheetSettingAtt"]=36;
objet["interface"][36]="../KnowledgeInterfaces/interface_ToleranceSheetSettingAtt_49910.htm";
objet["interface"]["Unit"]=37;
objet["interface"][37]="../KnowledgeInterfaces/interface_Unit_22098.htm";
objet["interface"]["Units"]=38;
objet["interface"][38]="../KnowledgeInterfaces/interface_Units_22558.htm";
objet["interface"]["UnitsSheetSettingAtt"]=39;
objet["interface"][39]="../KnowledgeInterfaces/interface_UnitsSheetSettingAtt_41162.htm";
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