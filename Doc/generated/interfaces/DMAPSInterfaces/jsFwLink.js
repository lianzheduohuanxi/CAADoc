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
 objet["enum"]["ItemAssignmentType"]=0;
objet["enum"][0]="../DMAPSInterfaces/enum_ItemAssignmentType_27567.htm";
objet["interface"]["Activities"]=0;
objet["interface"][0]="../DMAPSInterfaces/interface_Activities_19259.htm";
objet["interface"]["Activity"]=1;
objet["interface"][1]="../DMAPSInterfaces/interface_Activity_17528.htm";
objet["interface"]["Item"]=2;
objet["interface"][2]="../DMAPSInterfaces/interface_Item_14987.htm";
objet["interface"]["Items"]=3;
objet["interface"][3]="../DMAPSInterfaces/interface_Items_15447.htm";
objet["interface"]["LibTabSettingAtt"]=4;
objet["interface"][4]="../DMAPSInterfaces/interface_LibTabSettingAtt_26655.htm";
objet["interface"]["Outputs"]=5;
objet["interface"][5]="../DMAPSInterfaces/interface_Outputs_16765.htm";
objet["interface"]["ProcessDocument"]=6;
objet["interface"][6]="../DMAPSInterfaces/interface_ProcessDocument_25534.htm";
objet["interface"]["Resource"]=7;
objet["interface"][7]="../DMAPSInterfaces/interface_Resource_17345.htm";
objet["interface"]["ResourceCollection"]=8;
objet["interface"][8]="../DMAPSInterfaces/interface_ResourceCollection_30492.htm";
objet["interface"]["Resources"]=9;
objet["interface"][9]="../DMAPSInterfaces/interface_Resources_18265.htm";
objet["interface"]["TreeTabSettingAtt"]=10;
objet["interface"][10]="../DMAPSInterfaces/interface_TreeTabSettingAtt_28283.htm";
objet["interface"]["VerifTabSettingAtt"]=11;
objet["interface"][11]="../DMAPSInterfaces/interface_VerifTabSettingAtt_30026.htm";
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