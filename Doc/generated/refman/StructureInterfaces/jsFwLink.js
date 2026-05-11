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
 objet["interface"]["CATIStrColorESSObjectSettingAtt"]=0;
objet["interface"][0]="../StructureInterfaces/interface_CATIStrColorESSObjectSettingAtt_68385.htm";
objet["interface"]["CATIStrColorSTDObjectSettingAtt"]=1;
objet["interface"][1]="../StructureInterfaces/interface_CATIStrColorSTDObjectSettingAtt_68356.htm";
objet["interface"]["CATIStrMaterialESSObjectSettingAtt"]=2;
objet["interface"][2]="../StructureInterfaces/interface_CATIStrMaterialESSObjectSettingAtt_77943.htm";
objet["interface"]["CATIStrPPGExecLogSettingAtt"]=3;
objet["interface"][3]="../StructureInterfaces/interface_CATIStrPPGExecLogSettingAtt_56650.htm";
objet["interface"]["CATIStrPathESSRessourcesSettingAtt"]=4;
objet["interface"][4]="../StructureInterfaces/interface_CATIStrPathESSRessourcesSettingAtt_79301.htm";
objet["interface"]["CATIStrTypeESSObjectSettingAtt"]=5;
objet["interface"][5]="../StructureInterfaces/interface_CATIStrTypeESSObjectSettingAtt_65401.htm";
objet["interface"]["CATIStructureFactory"]=6;
objet["interface"][6]="../StructureInterfaces/interface_CATIStructureFactory_41840.htm";
objet["interface"]["CATIStructureMember"]=7;
objet["interface"][7]="../StructureInterfaces/interface_CATIStructureMember_39380.htm";
objet["interface"]["CATIStructureObject"]=8;
objet["interface"][8]="../StructureInterfaces/interface_CATIStructureObject_39369.htm";
objet["interface"]["CATIStructurePlate"]=9;
objet["interface"][9]="../StructureInterfaces/interface_CATIStructurePlate_37573.htm";
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