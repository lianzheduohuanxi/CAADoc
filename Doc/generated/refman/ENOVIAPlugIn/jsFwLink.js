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
 objet["class"]["ENOVPublishAttributeNode"]=0;
objet["class"][0]="../ENOVIAPlugIn/class_ENOVPublishAttributeNode_35679.htm";
objet["class"]["ENOVPublishAttributeValue"]=1;
objet["class"][1]="../ENOVIAPlugIn/class_ENOVPublishAttributeValue_38513.htm";
objet["class"]["ENOVPublishEnvironment"]=2;
objet["class"][2]="../ENOVIAPlugIn/class_ENOVPublishEnvironment_31871.htm";
objet["class"]["ENOVPublishObject"]=3;
objet["class"][3]="../ENOVIAPlugIn/class_ENOVPublishObject_21093.htm";
objet["class"]["ENOVPublishObjectClass"]=4;
objet["class"][4]="../ENOVIAPlugIn/class_ENOVPublishObjectClass_30734.htm";
objet["class"]["ENOVPublishObjectNode"]=5;
objet["class"][5]="../ENOVIAPlugIn/class_ENOVPublishObjectNode_28337.htm";
objet["class"]["ENOVPublishStream"]=6;
objet["class"][6]="../ENOVIAPlugIn/class_ENOVPublishStream_21315.htm";
objet["class"]["ENOVPublishedBy"]=7;
objet["class"][7]="../ENOVIAPlugIn/class_ENOVPublishedBy_17778.htm";
objet["define"]["ENOVPublishAttributeNodeType"]=0;
objet["define"][0]="../ENOVIAPlugIn/define_ENOVPublishAttributeNodeType_46817.htm";
objet["define"]["ENOVPublishAttributeValueType"]=1;
objet["define"][1]="../ENOVIAPlugIn/define_ENOVPublishAttributeValueType_50069.htm";
objet["define"]["ENOVPublishByType"]=2;
objet["define"][2]="../ENOVIAPlugIn/define_ENOVPublishByType_21633.htm";
objet["define"]["ENOVPublishCreated"]=3;
objet["define"][3]="../ENOVIAPlugIn/define_ENOVPublishCreated_23205.htm";
objet["define"]["ENOVPublishEnvironmentType"]=4;
objet["define"][4]="../ENOVIAPlugIn/define_ENOVPublishEnvironmentType_42173.htm";
objet["define"]["ENOVPublishModified"]=5;
objet["define"][5]="../ENOVIAPlugIn/define_ENOVPublishModified_25049.htm";
objet["define"]["ENOVPublishNoAccess"]=6;
objet["define"][6]="../ENOVIAPlugIn/define_ENOVPublishNoAccess_24920.htm";
objet["define"]["ENOVPublishObjectClassType"]=7;
objet["define"][7]="../ENOVIAPlugIn/define_ENOVPublishObjectClassType_41036.htm";
objet["define"]["ENOVPublishObjectNodeType"]=8;
objet["define"][8]="../ENOVIAPlugIn/define_ENOVPublishObjectNodeType_38221.htm";
objet["define"]["ENOVPublishObjectType"]=9;
objet["define"][9]="../ENOVIAPlugIn/define_ENOVPublishObjectType_29305.htm";
objet["define"]["ENOVPublishReadOnly"]=10;
objet["define"][10]="../ENOVIAPlugIn/define_ENOVPublishReadOnly_25107.htm";
objet["define"]["ENOVPublishReadWrite"]=11;
objet["define"][11]="../ENOVIAPlugIn/define_ENOVPublishReadWrite_27069.htm";
objet["define"]["ENOVPublishStreamType"]=12;
objet["define"][12]="../ENOVIAPlugIn/define_ENOVPublishStreamType_29527.htm";
objet["define"]["ENOVPublishTypeBinary"]=13;
objet["define"][13]="../ENOVIAPlugIn/define_ENOVPublishTypeBinary_29491.htm";
objet["define"]["ENOVPublishTypeInteger"]=14;
objet["define"][14]="../ENOVIAPlugIn/define_ENOVPublishTypeInteger_31635.htm";
objet["define"]["ENOVPublishTypeList"]=15;
objet["define"][15]="../ENOVIAPlugIn/define_ENOVPublishTypeList_25482.htm";
objet["define"]["ENOVPublishTypeMonoValue"]=16;
objet["define"][16]="../ENOVIAPlugIn/define_ENOVPublishTypeMonoValue_36157.htm";
objet["define"]["ENOVPublishTypeOid"]=17;
objet["define"][17]="../ENOVIAPlugIn/define_ENOVPublishTypeOid_23184.htm";
objet["define"]["ENOVPublishTypeReal"]=18;
objet["define"][18]="../ENOVIAPlugIn/define_ENOVPublishTypeReal_25058.htm";
objet["define"]["ENOVPublishTypeSet"]=19;
objet["define"][19]="../ENOVIAPlugIn/define_ENOVPublishTypeSet_23452.htm";
objet["define"]["ENOVPublishTypeString"]=20;
objet["define"][20]="../ENOVIAPlugIn/define_ENOVPublishTypeString_29698.htm";
objet["define"]["ENOVPublishTypeTimestamp"]=21;
objet["define"][21]="../ENOVIAPlugIn/define_ENOVPublishTypeTimestamp_36746.htm";
objet["define"]["ENOVPublishTypeUid"]=22;
objet["define"][22]="../ENOVIAPlugIn/define_ENOVPublishTypeUid_23274.htm";
objet["define"]["ENOVPublishTypeVaultReference"]=23;
objet["define"][23]="../ENOVIAPlugIn/define_ENOVPublishTypeVaultReference_49548.htm";
objet["define"]["ENOVPublishUnchanged"]=24;
objet["define"][24]="../ENOVIAPlugIn/define_ENOVPublishUnchanged_27055.htm";
objet["define"]["ENOVPublishUnknown"]=25;
objet["define"][25]="../ENOVIAPlugIn/define_ENOVPublishUnknown_23998.htm";
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