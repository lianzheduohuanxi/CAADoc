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
 objet["enum"]["CatAsmAutoSwitchToDesignMode"]=0;
objet["enum"][0]="../CATAssemblyInterfaces/enum_CatAsmAutoSwitchToDesignMode_60649.htm";
objet["enum"]["CatAsmConstraintCreationMode"]=1;
objet["enum"][1]="../CATAssemblyInterfaces/enum_CatAsmConstraintCreationMode_61470.htm";
objet["enum"]["CatAsmExtendMoveToFixT"]=2;
objet["enum"][2]="../CATAssemblyInterfaces/enum_CatAsmExtendMoveToFixT_45510.htm";
objet["enum"]["CatAsmPasteComponentMode"]=3;
objet["enum"][3]="../CATAssemblyInterfaces/enum_CatAsmPasteComponentMode_50942.htm";
objet["enum"]["CatAsmQuickConstraintMode"]=4;
objet["enum"][4]="../CATAssemblyInterfaces/enum_CatAsmQuickConstraintMode_53546.htm";
objet["enum"]["CatAsmRedundancyMode"]=5;
objet["enum"][5]="../CATAssemblyInterfaces/enum_CatAsmRedundancyMode_41920.htm";
objet["enum"]["CatAsmUpdateMode"]=6;
objet["enum"][6]="../CATAssemblyInterfaces/enum_CatAsmUpdateMode_34555.htm";
objet["enum"]["CatAsmUpdateStatusComputeMode"]=7;
objet["enum"][7]="../CATAssemblyInterfaces/enum_CatAsmUpdateStatusComputeMode_64554.htm";
objet["interface"]["AsmConstraintSettingAtt"]=0;
objet["interface"][0]="../CATAssemblyInterfaces/interface_AsmConstraintSettingAtt_52095.htm";
objet["interface"]["AsmGeneralSettingAtt"]=1;
objet["interface"][1]="../CATAssemblyInterfaces/interface_AsmGeneralSettingAtt_45187.htm";
objet["interface"]["AssemblyBoolean"]=2;
objet["interface"][2]="../CATAssemblyInterfaces/interface_AssemblyBoolean_36436.htm";
objet["interface"]["AssemblyFeature"]=3;
objet["interface"][3]="../CATAssemblyInterfaces/interface_AssemblyFeature_36613.htm";
objet["interface"]["AssemblyFeatures"]=4;
objet["interface"][4]="../CATAssemblyInterfaces/interface_AssemblyFeatures_38338.htm";
objet["interface"]["AssemblyHole"]=5;
objet["interface"][5]="../CATAssemblyInterfaces/interface_AssemblyHole_32364.htm";
objet["interface"]["AssemblyPocket"]=6;
objet["interface"][6]="../CATAssemblyInterfaces/interface_AssemblyPocket_35124.htm";
objet["interface"]["AssemblySplit"]=7;
objet["interface"][7]="../CATAssemblyInterfaces/interface_AssemblySplit_33897.htm";
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