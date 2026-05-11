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
 objet["enum"]["CatProductSource"]=0;
objet["enum"][0]="../ProductStructureInterfaces/enum_CatProductSource_47634.htm";
objet["interface"]["CATICustoIconProduct"]=0;
objet["interface"][0]="../ProductStructureInterfaces/interface_CATICustoIconProduct_57743.htm";
objet["interface"]["CATIPrdHandleImpactsOnInstance"]=1;
objet["interface"][1]="../ProductStructureInterfaces/interface_CATIPrdHandleImpactsOnInstance_82138.htm";
objet["interface"]["CATIPrdHandleImpactsOnReference"]=2;
objet["interface"][2]="../ProductStructureInterfaces/interface_CATIPrdHandleImpactsOnReference_84921.htm";
objet["interface"]["CATIPrdHandlePDMObject"]=3;
objet["interface"][3]="../ProductStructureInterfaces/interface_CATIPrdHandlePDMObject_59916.htm";
objet["interface"]["CATIPrdPLMPersistency"]=4;
objet["interface"][4]="../ProductStructureInterfaces/interface_CATIPrdPLMPersistency_59610.htm";
objet["interface"]["CATIPrdTransactionalEventMgt"]=5;
objet["interface"][5]="../ProductStructureInterfaces/interface_CATIPrdTransactionalEventMgt_76887.htm";
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