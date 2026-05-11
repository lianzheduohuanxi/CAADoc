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
 objet["class"]["CATMf3DBehaviorAdapter"]=0;
objet["class"][0]="../CATMecModExtendItf/class_CATMf3DBehaviorAdapter_39499.htm";
objet["class"]["CATMmrReplaceAdapter"]=1;
objet["class"][1]="../CATMecModExtendItf/class_CATMmrReplaceAdapter_35589.htm";
objet["class"]["CATMmrUseSolidInsertionAdapt"]=2;
objet["class"][2]="../CATMecModExtendItf/class_CATMmrUseSolidInsertionAdapt_55231.htm";
objet["interface"]["CATIMmiAlgoConfigServices"]=0;
objet["interface"][0]="../CATMecModExtendItf/interface_CATIMmiAlgoConfigServices_49582.htm";
objet["interface"]["CATIMmiErrUpdate"]=1;
objet["interface"][1]="../CATMecModExtendItf/interface_CATIMmiErrUpdate_30958.htm";
objet["interface"]["CATIMmiFeatureAttributes"]=2;
objet["interface"][2]="../CATMecModExtendItf/interface_CATIMmiFeatureAttributes_47993.htm";
objet["interface"]["CATIMmiMechanicalSet"]=3;
objet["interface"][3]="../CATMecModExtendItf/interface_CATIMmiMechanicalSet_37887.htm";
objet["interface"]["CATIMmiMechanicalSetServices"]=4;
objet["interface"][4]="../CATMecModExtendItf/interface_CATIMmiMechanicalSetServices_57616.htm";
objet["interface"]["CATIMmiUpdateError"]=5;
objet["interface"][5]="../CATMecModExtendItf/interface_CATIMmiUpdateError_34621.htm";
objet["interface"]["CATMmiExtendServicesFactory"]=6;
objet["interface"][6]="../CATMecModExtendItf/interface_CATMmiExtendServicesFactory_55620.htm";
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