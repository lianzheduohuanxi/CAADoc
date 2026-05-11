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
 objet["interface"]["CATIMfg3DToolPathVisu"]=0;
objet["interface"][0]="../ToolPathEditorInterfaces/interface_CATIMfg3DToolPathVisu_53144.htm";
objet["interface"]["CATIMfg3DToolPathVisuData"]=1;
objet["interface"][1]="../ToolPathEditorInterfaces/interface_CATIMfg3DToolPathVisuData_61702.htm";
objet["interface"]["CATIMfgTPECutAreasEditor"]=2;
objet["interface"][2]="../ToolPathEditorInterfaces/interface_CATIMfgTPECutAreasEditor_59584.htm";
objet["interface"]["CATIMfgTPECutAreasUserHeader"]=3;
objet["interface"][3]="../ToolPathEditorInterfaces/interface_CATIMfgTPECutAreasUserHeader_69410.htm";
objet["interface"]["CATIMfgTPEExtraVisu"]=4;
objet["interface"][4]="../ToolPathEditorInterfaces/interface_CATIMfgTPEExtraVisu_49303.htm";
objet["interface"]["CATIMfgToolPathEditorHeader"]=5;
objet["interface"][5]="../ToolPathEditorInterfaces/interface_CATIMfgToolPathEditorHeader_67495.htm";
objet["interface"]["CATIMfgToolPathEditorUserHeader"]=6;
objet["interface"][6]="../ToolPathEditorInterfaces/interface_CATIMfgToolPathEditorUserHeader_79209.htm";
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