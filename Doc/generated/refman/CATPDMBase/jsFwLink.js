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
 objet["class"]["CATPDMCATIAServices"]=0;
objet["class"][0]="../CATPDMBase/class_CATPDMCATIAServices_21312.htm";
objet["class"]["CATPDMCSServices"]=1;
objet["class"][1]="../CATPDMBase/class_CATPDMCSServices_16951.htm";
objet["class"]["CATPDMServices"]=2;
objet["class"][2]="../CATPDMBase/class_CATPDMServices_14296.htm";
objet["function"]["DisconnectEV5Server"]=0;
objet["function"][0]="../CATPDMBase/function_DisconnectEV5Server_34173.htm";
objet["function"]["E2ESendTo"]=1;
objet["function"][1]="../CATPDMBase/function_E2ESendTo_1806165.htm";
objet["function"]["ExtractDocsToFileDirectory"]=2;
objet["function"][2]="../CATPDMBase/function_ExtractDocsToFileDirectory_499127.htm";
objet["function"]["ExtractDocumentSetToFileDirectory"]=3;
objet["function"][3]="../CATPDMBase/function_ExtractDocumentSetToFileDirectory_185514.htm";
objet["function"]["GetDocumentSetFromV_IDAndRevision"]=4;
objet["function"][4]="../CATPDMBase/function_GetDocumentSetFromV_IDAndRevision_586887.htm";
objet["function"]["GetIIsFromPVS"]=5;
objet["function"][5]="../CATPDMBase/function_GetIIsFromPVS_308981.htm";
objet["function"]["LoadFromPDM"]=6;
objet["function"][6]="../CATPDMBase/function_LoadFromPDM_217776.htm";
objet["function"]["OpenCatalogDocumentFromV_ID"]=7;
objet["function"][7]="../CATPDMBase/function_OpenCatalogDocumentFromV_ID_122525.htm";
objet["function"]["OpenCatalogDocumentFromV_ID_AND_V_version"]=8;
objet["function"][8]="../CATPDMBase/function_OpenCatalogDocumentFromV_ID_AND_V_version_269958.htm";
objet["function"]["OpenPartAndDocumentFromV_ID"]=9;
objet["function"][9]="../CATPDMBase/function_OpenPartAndDocumentFromV_ID_202556.htm";
objet["function"]["OpenPartAndDocumentFrom_V_ID_And_V_version"]=10;
objet["function"][10]="../CATPDMBase/function_OpenPartAndDocumentFrom_V_ID_And_V_version_390828.htm";
objet["function"]["RunServerCode"]=11;
objet["function"][11]="../CATPDMBase/function_RunServerCode_155404.htm";
objet["function"]["SaveCatalogDocument"]=12;
objet["function"][12]="../CATPDMBase/function_SaveCatalogDocument_42925.htm";
objet["function"]["SavePartAndDocument"]=13;
objet["function"][13]="../CATPDMBase/function_SavePartAndDocument_42715.htm";
objet["function"]["SaveToPDM"]=14;
objet["function"][14]="../CATPDMBase/function_SaveToPDM_91195.htm";
objet["function"]["SetEV5PersistencyMode"]=15;
objet["function"][15]="../CATPDMBase/function_SetEV5PersistencyMode_223085.htm";
objet["function"]["StartEV5Server"]=16;
objet["function"][16]="../CATPDMBase/function_StartEV5Server_383904.htm";
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