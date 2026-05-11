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
 objet["enum"]["CatDescriptionLengthType"]=0;
objet["enum"][0]="../GenKnowledgeInterfaces/enum_CatDescriptionLengthType_53587.htm";
objet["enum"]["CatOutPutFormatType"]=1;
objet["enum"][1]="../GenKnowledgeInterfaces/enum_CatOutPutFormatType_42542.htm";
objet["enum"]["CatShowResultType"]=2;
objet["enum"][2]="../GenKnowledgeInterfaces/enum_CatShowResultType_39108.htm";
objet["enum"]["CatSolveType"]=3;
objet["enum"][3]="../GenKnowledgeInterfaces/enum_CatSolveType_31565.htm";
objet["enum"]["CatVisualizationType"]=4;
objet["enum"][4]="../GenKnowledgeInterfaces/enum_CatVisualizationType_44952.htm";
objet["interface"]["ExpertCheck"]=0;
objet["interface"][0]="../GenKnowledgeInterfaces/interface_ExpertCheck_33201.htm";
objet["interface"]["ExpertCheckRuntime"]=1;
objet["interface"][1]="../GenKnowledgeInterfaces/interface_ExpertCheckRuntime_43597.htm";
objet["interface"]["ExpertReportObject"]=2;
objet["interface"][2]="../GenKnowledgeInterfaces/interface_ExpertReportObject_43589.htm";
objet["interface"]["ExpertReportObjects"]=3;
objet["interface"][3]="../GenKnowledgeInterfaces/interface_ExpertReportObjects_45659.htm";
objet["interface"]["ExpertRule"]=4;
objet["interface"][4]="../GenKnowledgeInterfaces/interface_ExpertRule_32386.htm";
objet["interface"]["ExpertRuleBase"]=5;
objet["interface"][5]="../GenKnowledgeInterfaces/interface_ExpertRuleBase_36806.htm";
objet["interface"]["ExpertRuleBaseComponentRuntime"]=6;
objet["interface"][6]="../GenKnowledgeInterfaces/interface_ExpertRuleBaseComponentRuntime_73303.htm";
objet["interface"]["ExpertRuleBaseComponentRuntimes"]=7;
objet["interface"][7]="../GenKnowledgeInterfaces/interface_ExpertRuleBaseComponentRuntimes_76753.htm";
objet["interface"]["ExpertRuleBaseRuntime"]=8;
objet["interface"][8]="../GenKnowledgeInterfaces/interface_ExpertRuleBaseRuntime_49422.htm";
objet["interface"]["ExpertRuleRuntime"]=9;
objet["interface"][9]="../GenKnowledgeInterfaces/interface_ExpertRuleRuntime_42042.htm";
objet["interface"]["ExpertRuleSet"]=10;
objet["interface"][10]="../GenKnowledgeInterfaces/interface_ExpertRuleSet_35719.htm";
objet["interface"]["ExpertRuleSetRuntime"]=11;
objet["interface"][11]="../GenKnowledgeInterfaces/interface_ExpertRuleSetRuntime_47595.htm";
objet["interface"]["KWECorrectFunction"]=12;
objet["interface"][12]="../GenKnowledgeInterfaces/interface_KWECorrectFunction_43725.htm";
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