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
 objet["class"]["CATAnalysisGenerativeFEM"]=0;
objet["class"][0]="../CATAnalysisGPSInterfaces/class_CATAnalysisGenerativeFEM_55756.htm";
objet["interface"]["CATIGPSCfgAddin"]=0;
objet["interface"][0]="../CATAnalysisGPSInterfaces/interface_CATIGPSCfgAddin_41199.htm";
objet["interface"]["CATIGPSConnectionDesign"]=1;
objet["interface"][1]="../CATAnalysisGPSInterfaces/interface_CATIGPSConnectionDesign_57123.htm";
objet["interface"]["CATIGPSSensorFactory"]=2;
objet["interface"][2]="../CATAnalysisGPSInterfaces/interface_CATIGPSSensorFactory_51097.htm";
objet["interface"]["CATIGPSStructuralTemplate"]=3;
objet["interface"][3]="../CATAnalysisGPSInterfaces/interface_CATIGPSStructuralTemplate_62669.htm";
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