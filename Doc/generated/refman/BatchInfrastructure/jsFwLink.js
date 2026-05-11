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
 objet["class"]["CATBatStatePubCAA"]=0;
objet["class"][0]="../BatchInfrastructure/class_CATBatStatePubCAA_31792.htm";
objet["notification"]["CATBatchEndNotifCAA"]=0;
objet["notification"][0]="../BatchInfrastructure/class_CATBatchEndNotifCAA_35050.htm";
DSCharacteristic["CATBatchEndNotifCAA"]="notification";
objet["class"]["CATBatchLogCAA"]=1;
objet["class"][1]="../BatchInfrastructure/class_CATBatchLogCAA_27462.htm";
objet["notification"]["CATBatchNotif"]=1;
objet["notification"][1]="../BatchInfrastructure/class_CATBatchNotif_27625.htm";
DSCharacteristic["CATBatchNotif"]="notification";
objet["class"]["CATBatchParameters"]=2;
objet["class"][2]="../BatchInfrastructure/class_CATBatchParameters_35722.htm";
objet["define"]["SIZE_T_ID"]=0;
objet["define"][0]="../BatchInfrastructure/define_SIZE_T_ID_23085.htm";
objet["enum"]["ExportedByCATBatchUtils"]=0;
objet["enum"][0]="../BatchInfrastructure/enum_ExportedByCATBatchUtils_44275.htm";
objet["function"]["CATBatchParamToSplitAccess"]=0;
objet["function"][0]="../BatchInfrastructure/function_CATBatchParamToSplitAccess_195942.htm";
objet["function"]["CloseParameterFile"]=1;
objet["function"][1]="../BatchInfrastructure/function_CloseParameterFile_112587.htm";
objet["function"]["GetBatchPublisherCAA"]=2;
objet["function"][2]="../BatchInfrastructure/function_GetBatchPublisherCAA_58939.htm";
objet["function"]["GetBatchRootCAA"]=3;
objet["function"][3]="../BatchInfrastructure/function_GetBatchRootCAA_76562.htm";
objet["function"]["GetCATIBatchCAA"]=4;
objet["function"][4]="../BatchInfrastructure/function_GetCATIBatchCAA_44090.htm";
objet["function"]["GetOutputXMLFile"]=5;
objet["function"][5]="../BatchInfrastructure/function_GetOutputXMLFile_68829.htm";
objet["function"]["InitParameterFile"]=6;
objet["function"][6]="../BatchInfrastructure/function_InitParameterFile_110863.htm";
objet["interface"]["CATBatClientMonitorCAA"]=0;
objet["interface"][0]="../BatchInfrastructure/interface_CATBatClientMonitorCAA_44226.htm";
objet["interface"]["CATIBatchCAA"]=1;
objet["interface"][1]="../BatchInfrastructure/interface_CATIBatchCAA_27719.htm";
objet["interface"]["CATIBatchElementCAA"]=2;
objet["interface"][2]="../BatchInfrastructure/interface_CATIBatchElementCAA_37811.htm";
objet["interface"]["CATIBatchElementsCAA"]=3;
objet["interface"][3]="../BatchInfrastructure/interface_CATIBatchElementsCAA_39848.htm";
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