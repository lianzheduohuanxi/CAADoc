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
 objet["class"]["CATFeatureAgent"]=0;
objet["class"][0]="../MechanicalModelerUI/class_CATFeatureAgent_28558.htm";
objet["class"]["CATFeatureImportAgent"]=1;
objet["class"][1]="../MechanicalModelerUI/class_CATFeatureImportAgent_39580.htm";
objet["class"]["CATMMUIPanelStateCmd"]=2;
objet["class"][2]="../MechanicalModelerUI/class_CATMMUIPanelStateCmd_36219.htm";
objet["class"]["CATMMUIStateCommand"]=3;
objet["class"][3]="../MechanicalModelerUI/class_CATMMUIStateCommand_34759.htm";
objet["class"]["CATMmuViewServices"]=4;
objet["class"][4]="../MechanicalModelerUI/class_CATMmuViewServices_33825.htm";
objet["class"]["CATPrtPanelStateCmd"]=5;
objet["class"][5]="../MechanicalModelerUI/class_CATPrtPanelStateCmd_34808.htm";
objet["class"]["CATPrtUpdateCom"]=6;
objet["class"][6]="../MechanicalModelerUI/class_CATPrtUpdateCom_28361.htm";
objet["interface"]["CATIPrtWksAddin"]=0;
objet["interface"][0]="../MechanicalModelerUI/interface_CATIPrtWksAddin_30821.htm";
objet["interface"]["CATIPrtWksConfiguration"]=1;
objet["interface"][1]="../MechanicalModelerUI/interface_CATIPrtWksConfiguration_47129.htm";
objet["typedef"]["CATFeatureAgentBehavior"]=0;
objet["typedef"][0]="../MechanicalModelerUI/typedef_CATFeatureAgentBehavior_44917.htm";
objet["typedef"]["CATImportAgentBehavior"]=1;
objet["typedef"][1]="../MechanicalModelerUI/typedef_CATImportAgentBehavior_42778.htm";
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