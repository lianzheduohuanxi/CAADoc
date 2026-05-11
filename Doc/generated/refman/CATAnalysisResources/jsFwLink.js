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
 objet["class"]["CATEAnalysisAxis"]=0;
objet["class"][0]="../CATAnalysisResources/class_CATEAnalysisAxis_33839.htm";
objet["class"]["CATEAnalysisContextCheck"]=1;
objet["class"][1]="../CATAnalysisResources/class_CATEAnalysisContextCheck_49688.htm";
objet["class"]["CATEAnalysisEditionControl"]=2;
objet["class"][2]="../CATAnalysisResources/class_CATEAnalysisEditionControl_55530.htm";
objet["class"]["CATEAnalysisEditionCusto"]=3;
objet["class"][3]="../CATAnalysisResources/class_CATEAnalysisEditionCusto_50322.htm";
objet["class"]["CATEAnalysisEntityInit"]=4;
objet["class"][4]="../CATAnalysisResources/class_CATEAnalysisEntityInit_45614.htm";
objet["class"]["CATEAnalysisEntityPreproSubscriber"]=5;
objet["class"][5]="../CATAnalysisResources/class_CATEAnalysisEntityPreproSubscriber_80543.htm";
objet["class"]["CATEAnalysisEntityVisu"]=6;
objet["class"][6]="../CATAnalysisResources/class_CATEAnalysisEntityVisu_45974.htm";
objet["class"]["CATEAnalysisGroup"]=7;
objet["class"][7]="../CATAnalysisResources/class_CATEAnalysisGroup_35739.htm";
objet["class"]["CATEAnalysisSetInit"]=8;
objet["class"][8]="../CATAnalysisResources/class_CATEAnalysisSetInit_38965.htm";
objet["class"]["CATEAnalysisSupportFilter"]=9;
objet["class"][9]="../CATAnalysisResources/class_CATEAnalysisSupportFilter_53180.htm";
objet["class"]["CATEAnalysisUpgrade"]=10;
objet["class"][10]="../CATAnalysisResources/class_CATEAnalysisUpgrade_39002.htm";
objet["class"]["CATEAnalysisVisibility"]=11;
objet["class"][11]="../CATAnalysisResources/class_CATEAnalysisVisibility_46039.htm";
objet["class"]["CATECharacCollector"]=12;
objet["class"][12]="../CATAnalysisResources/class_CATECharacCollector_38958.htm";
objet["class"]["CATESamEnumManager"]=13;
objet["class"][13]="../CATAnalysisResources/class_CATESamEnumManager_36713.htm";
objet["class"]["CATESamImportDefineAdaptor"]=14;
objet["class"][14]="../CATAnalysisResources/class_CATESamImportDefineAdaptor_54570.htm";
objet["class"]["CATSamBasicComponentManagerAdaptor"]=15;
objet["class"][15]="../CATAnalysisResources/class_CATSamBasicComponentManagerAdaptor_78950.htm";
objet["class"]["CATSamToolsForExplicitation"]=16;
objet["class"][16]="../CATAnalysisResources/class_CATSamToolsForExplicitation_58346.htm";
objet["enum"]["CollectorArchiveFlag"]=0;
objet["enum"][0]="../CATAnalysisResources/enum_CollectorArchiveFlag_40150.htm";
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