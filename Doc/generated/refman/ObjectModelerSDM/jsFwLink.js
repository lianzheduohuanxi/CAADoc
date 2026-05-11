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
 objet["function"]["CreateModel"]=0;
objet["function"][0]="../ObjectModelerSDM/function_CreateModel_94770.htm";
objet["function"]["CreateModelFromSchema"]=1;
objet["function"][1]="../ObjectModelerSDM/function_CreateModelFromSchema_208622.htm";
objet["function"]["DeleteModel"]=2;
objet["function"][2]="../ObjectModelerSDM/function_DeleteModel_40838.htm";
objet["function"]["GetContainerFromModel"]=3;
objet["function"][3]="../ObjectModelerSDM/function_GetContainerFromModel_99360.htm";
objet["function"]["GetModelFromContainer"]=4;
objet["function"][4]="../ObjectModelerSDM/function_GetModelFromContainer_114685.htm";
objet["function"]["GetModelFromFile"]=5;
objet["function"][5]="../ObjectModelerSDM/function_GetModelFromFile_101163.htm";
objet["function"]["SaveFileFromModel"]=6;
objet["function"][6]="../ObjectModelerSDM/function_SaveFileFromModel_88862.htm";
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