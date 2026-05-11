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
 objet["interface"]["AnalysisMaterial"]=0;
objet["interface"][0]="../CATMatInterfaces/interface_AnalysisMaterial_28616.htm";
objet["interface"]["Material"]=1;
objet["interface"][1]="../CATMatInterfaces/interface_Material_18974.htm";
objet["interface"]["MaterialDocument"]=2;
objet["interface"][2]="../CATMatInterfaces/interface_MaterialDocument_28695.htm";
objet["interface"]["MaterialFamilies"]=3;
objet["interface"][3]="../CATMatInterfaces/interface_MaterialFamilies_28452.htm";
objet["interface"]["MaterialFamily"]=4;
objet["interface"][4]="../CATMatInterfaces/interface_MaterialFamily_25521.htm";
objet["interface"]["MaterialManager"]=5;
objet["interface"][5]="../CATMatInterfaces/interface_MaterialManager_26775.htm";
objet["interface"]["Materials"]=6;
objet["interface"][6]="../CATMatInterfaces/interface_Materials_19894.htm";
objet["interface"]["PositionedMaterial"]=7;
objet["interface"][7]="../CATMatInterfaces/interface_PositionedMaterial_31913.htm";
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