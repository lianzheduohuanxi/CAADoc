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
 objet["collection"]["CATLISTV(CATIMmiMechanicalFeature_var)"]=0;
objet["collection"][0]="../CATMecModLiveUseItf/class_CATLISTV(CATIMmiMechanicalFeature_var)_85346.htm";
objet["interface"]["CATIMmiMechanicalFeature"]=0;
objet["interface"][0]="../CATMecModLiveUseItf/interface_CATIMmiMechanicalFeature_48539.htm";
objet["interface"]["CATIMmiUseBodyContent"]=1;
objet["interface"][1]="../CATMecModLiveUseItf/interface_CATIMmiUseBodyContent_42122.htm";
objet["interface"]["CATIMmiUsePrtPart"]=2;
objet["interface"][2]="../CATMecModLiveUseItf/interface_CATIMmiUsePrtPart_34315.htm";
objet["interface"]["CATIMmiViewServices"]=3;
objet["interface"][3]="../CATMecModLiveUseItf/interface_CATIMmiViewServices_38227.htm";
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