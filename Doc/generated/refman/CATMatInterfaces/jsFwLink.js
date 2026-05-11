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
 objet["interface"]["CATIFamilyFeature"]=0;
objet["interface"][0]="../CATMatInterfaces/interface_CATIFamilyFeature_30029.htm";
objet["interface"]["CATILibraryFeature"]=1;
objet["interface"][1]="../CATMatInterfaces/interface_CATILibraryFeature_31865.htm";
objet["interface"]["CATIMaterialDocument"]=2;
objet["interface"][2]="../CATMatInterfaces/interface_CATIMaterialDocument_35731.htm";
objet["interface"]["CATIMaterialFeature"]=3;
objet["interface"][3]="../CATMatInterfaces/interface_CATIMaterialFeature_33565.htm";
objet["interface"]["CATIMaterialSupport"]=4;
objet["interface"][4]="../CATMatInterfaces/interface_CATIMaterialSupport_34253.htm";
objet["interface"]["CATIPositionedMaterial"]=5;
objet["interface"][5]="../CATMatInterfaces/interface_CATIPositionedMaterial_39841.htm";
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