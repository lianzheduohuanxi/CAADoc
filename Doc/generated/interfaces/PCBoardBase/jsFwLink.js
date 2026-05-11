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
 objet["enum"]["CatElectronicType"]=0;
objet["enum"][0]="../PCBoardBase/enum_CatElectronicType_20359.htm";
objet["interface"]["PCBArea"]=0;
objet["interface"][0]="../PCBoardBase/interface_PCBArea_11004.htm";
objet["interface"]["PCBBoard"]=1;
objet["interface"][1]="../PCBoardBase/interface_PCBBoard_11777.htm";
objet["interface"]["PCBComponent"]=2;
objet["interface"][2]="../PCBoardBase/interface_PCBComponent_16070.htm";
objet["interface"]["PCBHoleAndPattern"]=3;
objet["interface"][3]="../PCBoardBase/interface_PCBHoleAndPattern_22958.htm";
objet["interface"]["PCBObject"]=4;
objet["interface"][4]="../PCBoardBase/interface_PCBObject_12652.htm";
objet["interface"]["PCBWorkbench"]=5;
objet["interface"][5]="../PCBoardBase/interface_PCBWorkbench_15801.htm";
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