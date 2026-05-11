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
 objet["enum"]["CATV4IV4V5SpecDraftMigrationEnum"]=0;
objet["enum"][0]="../CATIAV4Interfaces/enum_CATV4IV4V5SpecDraftMigrationEnum_63497.htm";
objet["enum"]["CATV4IV5V4AssociativityModeEnum"]=1;
objet["enum"][1]="../CATIAV4Interfaces/enum_CATV4IV5V4AssociativityModeEnum_60877.htm";
objet["enum"]["CATV4IV5V4ErrorFeatureCreationEnum"]=2;
objet["enum"][2]="../CATIAV4Interfaces/enum_CATV4IV5V4ErrorFeatureCreationEnum_70450.htm";
objet["enum"]["CATV4IV5V4InternalCurveCreationEnum"]=3;
objet["enum"][3]="../CATIAV4Interfaces/enum_CATV4IV5V4InternalCurveCreationEnum_73986.htm";
objet["interface"]["InteropSettingAtt"]=0;
objet["interface"][0]="../CATIAV4Interfaces/interface_InteropSettingAtt_31314.htm";
objet["interface"]["MigrBatchSettingAtt"]=1;
objet["interface"][1]="../CATIAV4Interfaces/interface_MigrBatchSettingAtt_34671.htm";
objet["interface"]["SpecV4SettingAtt"]=2;
objet["interface"][2]="../CATIAV4Interfaces/interface_SpecV4SettingAtt_29170.htm";
objet["interface"]["V4V5SpaceSettingAtt"]=3;
objet["interface"][3]="../CATIAV4Interfaces/interface_V4V5SpaceSettingAtt_34406.htm";
objet["interface"]["V4WritingSettingAtt"]=4;
objet["interface"][4]="../CATIAV4Interfaces/interface_V4WritingSettingAtt_34840.htm";
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