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
 objet["class"]["CATExpertReportEnum"]=0;
objet["class"][0]="../KnowHow/class_CATExpertReportEnum_21329.htm";
objet["class"]["CATExpertRuleEnum"]=1;
objet["class"][1]="../KnowHow/class_CATExpertRuleEnum_17409.htm";
objet["class"]["CATExpertSolveModeEnum"]=2;
objet["class"][2]="../KnowHow/class_CATExpertSolveModeEnum_26960.htm";
objet["interface"]["CATICheck"]=0;
objet["interface"][0]="../KnowHow/interface_CATICheck_9335.htm";
objet["interface"]["CATICheckReport"]=1;
objet["interface"][1]="../KnowHow/interface_CATICheckReport_16753.htm";
objet["interface"]["CATIGenericRuleBaseComponent"]=2;
objet["interface"][2]="../KnowHow/interface_CATIGenericRuleBaseComponent_44790.htm";
objet["interface"]["CATIReportObject"]=3;
objet["interface"][3]="../KnowHow/interface_CATIReportObject_18209.htm";
objet["interface"]["CATIReportOptions"]=4;
objet["interface"][4]="../KnowHow/interface_CATIReportOptions_20453.htm";
objet["interface"]["CATIRule"]=5;
objet["interface"][5]="../KnowHow/interface_CATIRule_8660.htm";
objet["interface"]["CATIRuleBase"]=6;
objet["interface"][6]="../KnowHow/interface_CATIRuleBase_12322.htm";
objet["interface"]["CATIRuleBaseComponent"]=7;
objet["interface"][7]="../KnowHow/interface_CATIRuleBaseComponent_27649.htm";
objet["interface"]["CATIRuleBaseFactory"]=8;
objet["interface"][8]="../KnowHow/interface_CATIRuleBaseFactory_23441.htm";
objet["interface"]["CATIRuleSet"]=9;
objet["interface"][9]="../KnowHow/interface_CATIRuleSet_11393.htm";
objet["typedef"]["conflictingImportFunctionPtr"]=0;
objet["typedef"][0]="../KnowHow/typedef_conflictingImportFunctionPtr_44357.htm";
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