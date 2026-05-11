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
 objet["class"]["CATAcquisitionAgent"]=0;
objet["class"][0]="../DialogEngine/class_CATAcquisitionAgent_25650.htm";
objet["class"]["CATAcquisitionFilter"]=1;
objet["class"][1]="../DialogEngine/class_CATAcquisitionFilter_27860.htm";
objet["class"]["CATBasicMultiDocumentCommand"]=2;
objet["class"][2]="../DialogEngine/class_CATBasicMultiDocumentCommand_46688.htm";
objet["class"]["CATCmdSwitchAgent"]=3;
objet["class"][3]="../DialogEngine/class_CATCmdSwitchAgent_21611.htm";
objet["class"]["CATCommandHeaderWithSDOForAgent"]=4;
objet["class"][4]="../DialogEngine/class_CATCommandHeaderWithSDOForAgent_52968.htm";
objet["class"]["CATCustomizableState"]=5;
objet["class"][5]="../DialogEngine/class_CATCustomizableState_27658.htm";
objet["class"]["CATCustomizableTransition"]=6;
objet["class"][6]="../DialogEngine/class_CATCustomizableTransition_39838.htm";
objet["class"]["CATDiaAction"]=7;
objet["class"][7]="../DialogEngine/class_CATDiaAction_14471.htm";
objet["class"]["CATDiaError"]=8;
objet["class"][8]="../DialogEngine/class_CATDiaError_13458.htm";
objet["class"]["CATDialogAgent"]=9;
objet["class"][9]="../DialogEngine/class_CATDialogAgent_16998.htm";
objet["class"]["CATDialogState"]=10;
objet["class"][10]="../DialogEngine/class_CATDialogState_17123.htm";
objet["class"]["CATDialogTransition"]=11;
objet["class"][11]="../DialogEngine/class_CATDialogTransition_25979.htm";
objet["class"]["CATEditAgent"]=12;
objet["class"][12]="../DialogEngine/class_CATEditAgent_14478.htm";
objet["class"]["CATIndicationAgent"]=13;
objet["class"][13]="../DialogEngine/class_CATIndicationAgent_23513.htm";
objet["collection"]["CATLISTP(CATDiaAction)"]=0;
objet["collection"][0]="../DialogEngine/class_CATLISTP(CATDiaAction)_27712.htm";
objet["collection"]["CATLISTP(CATDialogAgent)"]=1;
objet["collection"][1]="../DialogEngine/class_CATLISTP(CATDialogAgent)_32220.htm";
objet["collection"]["CATLISTP(CATDialogState)"]=2;
objet["collection"][2]="../DialogEngine/class_CATLISTP(CATDialogState)_32507.htm";
objet["class"]["CATMultiDocumentCommand"]=14;
objet["class"][14]="../DialogEngine/class_CATMultiDocumentCommand_33919.htm";
objet["class"]["CATOtherDocumentAgent"]=15;
objet["class"][15]="../DialogEngine/class_CATOtherDocumentAgent_29451.htm";
objet["class"]["CATPanelState"]=16;
objet["class"][16]="../DialogEngine/class_CATPanelState_15792.htm";
objet["class"]["CATPathElementAgent"]=17;
objet["class"][17]="../DialogEngine/class_CATPathElementAgent_25232.htm";
objet["notification"]["CATStateActivateNotification"]=0;
objet["notification"][0]="../DialogEngine/class_CATStateActivateNotification_47366.htm";
DSCharacteristic["CATStateActivateNotification"]="notification";
objet["notification"]["CATStateCancelNotification"]=1;
objet["notification"][1]="../DialogEngine/class_CATStateCancelNotification_41528.htm";
DSCharacteristic["CATStateCancelNotification"]="notification";
objet["class"]["CATStateCommand"]=18;
objet["class"][18]="../DialogEngine/class_CATStateCommand_18505.htm";
objet["class"]["CATStateCondition"]=19;
objet["class"][19]="../DialogEngine/class_CATStateCondition_22085.htm";
objet["notification"]["CATStateDesactivateNotification"]=2;
objet["notification"][2]="../DialogEngine/class_CATStateDesactivateNotification_56537.htm";
DSCharacteristic["CATStateDesactivateNotification"]="notification";
objet["define"]["CmdDeclareResource"]=0;
objet["define"][0]="../DialogEngine/define_CmdDeclareResource_24274.htm";
objet["define"]["CmdDeclareResourceFile"]=1;
objet["define"][1]="../DialogEngine/define_CmdDeclareResourceFile_31810.htm";
objet["interface"]["CATICmdSwitchAgent"]=0;
objet["interface"][0]="../DialogEngine/interface_CATICmdSwitchAgent_25814.htm";
objet["typedef"]["ActionMethod"]=0;
objet["typedef"][0]="../DialogEngine/typedef_ActionMethod_15794.htm";
objet["typedef"]["CATDlgEngBehavior"]=1;
objet["typedef"][1]="../DialogEngine/typedef_CATDlgEngBehavior_22708.htm";
objet["typedef"]["ConditionMethod"]=2;
objet["typedef"][2]="../DialogEngine/typedef_ConditionMethod_19899.htm";
objet["typedef"]["ElementProvider"]=3;
objet["typedef"][3]="../DialogEngine/typedef_ElementProvider_20113.htm";
objet["typedef"]["FilterMethod"]=4;
objet["typedef"][4]="../DialogEngine/typedef_FilterMethod_15797.htm";
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