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
 objet["interface"]["CATIUdfFactory"]=0;
objet["interface"][0]="../MechanicalCommands/interface_CATIUdfFactory_28876.htm";
objet["interface"]["CATIUdfFeature"]=1;
objet["interface"][1]="../MechanicalCommands/interface_CATIUdfFeature_28696.htm";
objet["interface"]["CATIUdfFeatureInstance"]=2;
objet["interface"][2]="../MechanicalCommands/interface_CATIUdfFeatureInstance_43117.htm";
objet["interface"]["CATIUdfFeatureSet"]=3;
objet["interface"][3]="../MechanicalCommands/interface_CATIUdfFeatureSet_33229.htm";
objet["interface"]["CATIUdfFeatureUser"]=4;
objet["interface"][4]="../MechanicalCommands/interface_CATIUdfFeatureUser_35165.htm";
objet["interface"]["CATIUdfInstantiate"]=5;
objet["interface"][5]="../MechanicalCommands/interface_CATIUdfInstantiate_35376.htm";
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