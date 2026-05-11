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
 objet["class"]["CATECloAppBendableAdapter"]=0;
objet["class"][0]="../CATCommonLayoutInterfaces/class_CATECloAppBendableAdapter_62362.htm";
objet["class"]["CATECloPartSelectionAdapter"]=1;
objet["class"][1]="../CATCommonLayoutInterfaces/class_CATECloPartSelectionAdapter_68428.htm";
objet["class"]["CATEEcvPercentFillAdapter"]=2;
objet["class"][2]="../CATCommonLayoutInterfaces/class_CATEEcvPercentFillAdapter_62786.htm";
objet["class"]["CATEcwLightNwkArcForPercentFill"]=3;
objet["class"][3]="../CATCommonLayoutInterfaces/class_CATEcwLightNwkArcForPercentFill_79127.htm";
objet["class"]["CATEcwLightNwkCableForPercentFill"]=4;
objet["class"][4]="../CATCommonLayoutInterfaces/class_CATEcwLightNwkCableForPercentFill_85352.htm";
objet["class"]["CATEcwLightNwkNodeForPercentFill"]=5;
objet["class"][5]="../CATCommonLayoutInterfaces/class_CATEcwLightNwkNodeForPercentFill_82404.htm";
objet["interface"]["CATICloAppBendable"]=0;
objet["interface"][0]="../CATCommonLayoutInterfaces/interface_CATICloAppBendable_49988.htm";
objet["interface"]["CATICloAppWeldOffset"]=1;
objet["interface"][1]="../CATCommonLayoutInterfaces/interface_CATICloAppWeldOffset_54146.htm";
objet["interface"]["CATICloPartRules"]=2;
objet["interface"][2]="../CATCommonLayoutInterfaces/interface_CATICloPartRules_47336.htm";
objet["interface"]["CATICloPartSelection"]=3;
objet["interface"][3]="../CATCommonLayoutInterfaces/interface_CATICloPartSelection_54644.htm";
objet["interface"]["CATIEcvPercentFill"]=4;
objet["interface"][4]="../CATCommonLayoutInterfaces/interface_CATIEcvPercentFill_50412.htm";
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