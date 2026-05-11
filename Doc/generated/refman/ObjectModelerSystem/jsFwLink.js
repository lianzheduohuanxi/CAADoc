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
 objet["class"]["CATListPtrCATBaseUnknown"]=0;
objet["class"][0]="../ObjectModelerSystem/class_CATListPtrCATBaseUnknown_46989.htm";
objet["class"]["_SEQUENCE_CATBaseUnknown_ptr"]=1;
objet["class"][1]="../ObjectModelerSystem/class__SEQUENCE_CATBaseUnknown_ptr_56990.htm";
objet["interface"]["CATInterfaceEvents"]=0;
objet["interface"][0]="../ObjectModelerSystem/interface_CATInterfaceEvents_37726.htm";
objet["interface"]["LifeCycleObject"]=1;
objet["interface"][1]="../ObjectModelerSystem/interface_LifeCycleObject_32446.htm";
objet["typedef"]["CATCallback"]=0;
objet["typedef"][0]="../ObjectModelerSystem/typedef_CATCallback_25727.htm";
objet["typedef"]["CATCallbackEvent"]=1;
objet["typedef"][1]="../ObjectModelerSystem/typedef_CATCallbackEvent_32495.htm";
objet["typedef"]["CATSubscriberData"]=2;
objet["typedef"][2]="../ObjectModelerSystem/typedef_CATSubscriberData_33967.htm";
objet["typedef"]["CATSubscriberMethod"]=3;
objet["typedef"][3]="../ObjectModelerSystem/typedef_CATSubscriberMethod_37939.htm";
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