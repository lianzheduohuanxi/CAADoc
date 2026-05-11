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
 objet["interface"]["RenderingEnvironment"]=0;
objet["interface"][0]="../CATRscInterfaces/interface_RenderingEnvironment_36454.htm";
objet["interface"]["RenderingEnvironmentWall"]=1;
objet["interface"][1]="../CATRscInterfaces/interface_RenderingEnvironmentWall_45091.htm";
objet["interface"]["RenderingEnvironments"]=2;
objet["interface"][2]="../CATRscInterfaces/interface_RenderingEnvironments_38754.htm";
objet["interface"]["RenderingLight"]=3;
objet["interface"][3]="../CATRscInterfaces/interface_RenderingLight_25467.htm";
objet["interface"]["RenderingLights"]=4;
objet["interface"][4]="../CATRscInterfaces/interface_RenderingLights_27077.htm";
objet["interface"]["RenderingShooting"]=5;
objet["interface"][5]="../CATRscInterfaces/interface_RenderingShooting_30460.htm";
objet["interface"]["RenderingShootings"]=6;
objet["interface"][6]="../CATRscInterfaces/interface_RenderingShootings_32415.htm";
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