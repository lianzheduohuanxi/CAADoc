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
 objet["class"]["CATOptAlgorithmAdapter"]=0;
objet["class"][0]="../OptimizationInterfaces/class_CATOptAlgorithmAdapter_49286.htm";
objet["class"]["CATOptAlgorithmUIFactoryAdapter"]=1;
objet["class"][1]="../OptimizationInterfaces/class_CATOptAlgorithmUIFactoryAdapter_72833.htm";
objet["class"]["CATOptValuesAndDerivativesAdapter"]=2;
objet["class"][2]="../OptimizationInterfaces/class_CATOptValuesAndDerivativesAdapter_79909.htm";
objet["define"]["CATOptGenericAlgorithmCATIType"]=0;
objet["define"][0]="../OptimizationInterfaces/define_CATOptGenericAlgorithmCATIType_68162.htm";
objet["define"]["CATOptOptimizationPackageName"]=1;
objet["define"][1]="../OptimizationInterfaces/define_CATOptOptimizationPackageName_66978.htm";
objet["define"]["CATOptTerminationNoImprovement"]=2;
objet["define"][2]="../OptimizationInterfaces/define_CATOptTerminationNoImprovement_71949.htm";
objet["define"]["CATOptTerminationTime"]=3;
objet["define"][3]="../OptimizationInterfaces/define_CATOptTerminationTime_47692.htm";
objet["define"]["OPTNLSFileName"]=4;
objet["define"][4]="../OptimizationInterfaces/define_OPTNLSFileName_34451.htm";
objet["interface"]["CATIKwoWorkshopAddin"]=0;
objet["interface"][0]="../OptimizationInterfaces/interface_CATIKwoWorkshopAddin_47368.htm";
objet["interface"]["CATIOptAlgorithm"]=1;
objet["interface"][1]="../OptimizationInterfaces/interface_CATIOptAlgorithm_40476.htm";
objet["interface"]["CATIOptAlgorithmUIFactory"]=2;
objet["interface"][2]="../OptimizationInterfaces/interface_CATIOptAlgorithmUIFactory_58564.htm";
objet["interface"]["CATIOptCntSatisfaction"]=3;
objet["interface"][3]="../OptimizationInterfaces/interface_CATIOptCntSatisfaction_52042.htm";
objet["interface"]["CATIOptFactory"]=4;
objet["interface"][4]="../OptimizationInterfaces/interface_CATIOptFactory_37486.htm";
objet["interface"]["CATIOptFreeParameter"]=5;
objet["interface"][5]="../OptimizationInterfaces/interface_CATIOptFreeParameter_47419.htm";
objet["interface"]["CATIOptGoal"]=6;
objet["interface"][6]="../OptimizationInterfaces/interface_CATIOptGoal_33345.htm";
objet["interface"]["CATIOptOptimization"]=7;
objet["interface"][7]="../OptimizationInterfaces/interface_CATIOptOptimization_46240.htm";
objet["interface"]["CATIOptProblem"]=8;
objet["interface"][8]="../OptimizationInterfaces/interface_CATIOptProblem_37275.htm";
objet["interface"]["CATIOptUpdateManagement"]=9;
objet["interface"][9]="../OptimizationInterfaces/interface_CATIOptUpdateManagement_53939.htm";
objet["interface"]["CATIOptValuesAndDerivativesAccess"]=10;
objet["interface"][10]="../OptimizationInterfaces/interface_CATIOptValuesAndDerivativesAccess_82139.htm";
objet["interface"]["CATIOptimizationLog"]=11;
objet["interface"][11]="../OptimizationInterfaces/interface_CATIOptimizationLog_45764.htm";
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