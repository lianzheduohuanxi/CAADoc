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
 objet["enum"]["CD5SaveItem_Status"]=0;
objet["enum"][0]="../ENOCD5Interfaces/enum_CD5SaveItem_Status_28461.htm";
objet["enum"]["CD5SaveOperation_Scope"]=1;
objet["enum"][1]="../ENOCD5Interfaces/enum_CD5SaveOperation_Scope_36258.htm";
objet["interface"]["CD5Engine"]=0;
objet["interface"][0]="../ENOCD5Interfaces/interface_CD5Engine_19109.htm";
objet["interface"]["CD5EngineV6R2014x"]=1;
objet["interface"][1]="../ENOCD5Interfaces/interface_CD5EngineV6R2014x_25935.htm";
objet["interface"]["CD5EngineV6R2015"]=2;
objet["interface"][2]="../ENOCD5Interfaces/interface_CD5EngineV6R2015_24030.htm";
objet["interface"]["CD5ID"]=3;
objet["interface"][3]="../ENOCD5Interfaces/interface_CD5ID_16230.htm";
objet["interface"]["CD5IDs"]=4;
objet["interface"][4]="../ENOCD5Interfaces/interface_CD5IDs_16805.htm";
objet["interface"]["CD5Properties"]=5;
objet["interface"][5]="../ENOCD5Interfaces/interface_CD5Properties_23866.htm";
objet["interface"]["CD5Property"]=6;
objet["interface"][6]="../ENOCD5Interfaces/interface_CD5Property_21535.htm";
objet["interface"]["CD5SaveItem"]=7;
objet["interface"][7]="../ENOCD5Interfaces/interface_CD5SaveItem_21010.htm";
objet["interface"]["CD5SaveItems"]=8;
objet["interface"][8]="../ENOCD5Interfaces/interface_CD5SaveItems_22275.htm";
objet["interface"]["CD5SaveOperation"]=9;
objet["interface"][9]="../ENOCD5Interfaces/interface_CD5SaveOperation_28098.htm";
objet["interface"]["CD5Structure"]=10;
objet["interface"][10]="../ENOCD5Interfaces/interface_CD5Structure_22649.htm";
objet["interface"]["CD5Template"]=11;
objet["interface"][11]="../ENOCD5Interfaces/interface_CD5Template_21198.htm";
objet["interface"]["CD5TemplateType"]=12;
objet["interface"][12]="../ENOCD5Interfaces/interface_CD5TemplateType_26444.htm";
objet["interface"]["CD5TemplateTypes"]=13;
objet["interface"][13]="../ENOCD5Interfaces/interface_CD5TemplateTypes_28169.htm";
objet["interface"]["CD5Templates"]=14;
objet["interface"][14]="../ENOCD5Interfaces/interface_CD5Templates_22463.htm";
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