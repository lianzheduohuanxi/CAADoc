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
 objet["class"]["CATAsmConstraintServices"]=0;
objet["class"][0]="../CATAssemblyInterfaces/class_CATAsmConstraintServices_52077.htm";
objet["class"]["CATAsmConstraintSetServices"]=1;
objet["class"][1]="../CATAssemblyInterfaces/class_CATAsmConstraintSetServices_59718.htm";
objet["function"]["CATAsmCstSetFeatGetCont"]=0;
objet["function"][0]="../CATAssemblyInterfaces/function_CATAsmCstSetFeatGetCont_114234.htm";
objet["function"]["CreateConstraint"]=1;
objet["function"][1]="../CATAssemblyInterfaces/function_CreateConstraint_371686.htm";
objet["function"]["GetCATAsmConstraintSettingCtrl"]=2;
objet["function"][2]="../CATAssemblyInterfaces/function_GetCATAsmConstraintSettingCtrl_90367.htm";
objet["function"]["GetCATAsmGeneralSettingCtrl"]=3;
objet["function"][3]="../CATAssemblyInterfaces/function_GetCATAsmGeneralSettingCtrl_80981.htm";
objet["function"]["GetProductConnector"]=4;
objet["function"][4]="../CATAssemblyInterfaces/function_GetProductConnector_358011.htm";
objet["interface"]["CATIAsmConstraintSettingAtt"]=0;
objet["interface"][0]="../CATAssemblyInterfaces/interface_CATIAsmConstraintSettingAtt_62071.htm";
objet["interface"]["CATIAsmCstSetFeatFactory"]=1;
objet["interface"][1]="../CATAssemblyInterfaces/interface_CATIAsmCstSetFeatFactory_53630.htm";
objet["interface"]["CATIAsmCstSetFeature"]=2;
objet["interface"][2]="../CATAssemblyInterfaces/interface_CATIAsmCstSetFeature_44831.htm";
objet["interface"]["CATIAsmGeneralSettingAtt"]=3;
objet["interface"][3]="../CATAssemblyInterfaces/interface_CATIAsmGeneralSettingAtt_53727.htm";
objet["interface"]["CATIAsmSelectMove3D"]=4;
objet["interface"][4]="../CATAssemblyInterfaces/interface_CATIAsmSelectMove3D_41354.htm";
objet["interface"]["CATIAssyWorkBenchAddin"]=5;
objet["interface"][5]="../CATAssemblyInterfaces/interface_CATIAssyWorkBenchAddin_48374.htm";
objet["interface"]["CATIProdDraftingProperties"]=6;
objet["interface"][6]="../CATAssemblyInterfaces/interface_CATIProdDraftingProperties_59765.htm";
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