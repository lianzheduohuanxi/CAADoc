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
 objet["collection"]["CATLISTP(CATIProduct)."]=0;
objet["collection"][0]="../ProductStructure/class_CATLISTP(CATIProduct)_33487.htm";
objet["class"]["CATPrdCommonFileSelection"]=0;
objet["class"][0]="../ProductStructure/class_CATPrdCommonFileSelection_45060.htm";
objet["class"]["CATPrsWorkModeServices"]=1;
objet["class"][1]="../ProductStructure/class_CATPrsWorkModeServices_38115.htm";
objet["interface"]["CATIAsmNavigateStruct"]=0;
objet["interface"][0]="../ProductStructure/interface_CATIAsmNavigateStruct_38747.htm";
objet["interface"]["CATIBlockMovable"]=1;
objet["interface"][1]="../ProductStructure/interface_CATIBlockMovable_28844.htm";
objet["interface"]["CATICtxMenuProvider"]=2;
objet["interface"][2]="../ProductStructure/interface_CATICtxMenuProvider_34621.htm";
objet["interface"]["CATICustomName"]=3;
objet["interface"][3]="../ProductStructure/interface_CATICustomName_25951.htm";
objet["interface"]["CATIMovable"]=4;
objet["interface"][4]="../ProductStructure/interface_CATIMovable_22275.htm";
objet["interface"]["CATIPrdObjectPublisher"]=5;
objet["interface"][5]="../ProductStructure/interface_CATIPrdObjectPublisher_40652.htm";
objet["interface"]["CATIPrdProperties"]=6;
objet["interface"][6]="../ProductStructure/interface_CATIPrdProperties_31152.htm";
objet["interface"]["CATIProduct"]=7;
objet["interface"][7]="../ProductStructure/interface_CATIProduct_22502.htm";
objet["interface"]["CATIProductFileSelection"]=8;
objet["interface"][8]="../ProductStructure/interface_CATIProductFileSelection_45243.htm";
objet["interface"]["CATIProductInSession"]=9;
objet["interface"][9]="../ProductStructure/interface_CATIProductInSession_36556.htm";
objet["interface"]["CATIProductSelection"]=10;
objet["interface"][10]="../ProductStructure/interface_CATIProductSelection_36659.htm";
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