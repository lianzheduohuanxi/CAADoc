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
 objet["collection"]["CATLISTP(CATIxPDMItem_var)"]=0;
objet["collection"][0]="../CATxPDMInterfaces/class_CATLISTP(CATIxPDMItem_var)_43295.htm";
objet["class"]["CATxPDMFileServices"]=0;
objet["class"][0]="../CATxPDMInterfaces/class_CATxPDMFileServices_31979.htm";
objet["class"]["CATxPDMProductServices"]=1;
objet["class"][1]="../CATxPDMInterfaces/class_CATxPDMProductServices_38629.htm";
objet["class"]["CATxPDMSessionServices"]=2;
objet["class"][2]="../CATxPDMInterfaces/class_CATxPDMSessionServices_38666.htm";
objet["class"]["CATxPDMSessionUIServices"]=3;
objet["class"][3]="../CATxPDMInterfaces/class_CATxPDMSessionUIServices_42623.htm";
objet["interface"]["CATIxPDMItem"]=0;
objet["interface"][0]="../CATxPDMInterfaces/interface_CATIxPDMItem_23450.htm";
objet["interface"]["CATIxPDMPartItem"]=1;
objet["interface"][1]="../CATxPDMInterfaces/interface_CATIxPDMPartItem_28975.htm";
objet["interface"]["CATIxPDMProductItem"]=2;
objet["interface"][2]="../CATxPDMInterfaces/interface_CATIxPDMProductItem_34434.htm";
objet["interface"]["CATIxPDMSendToService"]=3;
objet["interface"][3]="../CATxPDMInterfaces/interface_CATIxPDMSendToService_38135.htm";
objet["interface"]["CATIxPDMSession"]=4;
objet["interface"][4]="../CATxPDMInterfaces/interface_CATIxPDMSession_27844.htm";
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