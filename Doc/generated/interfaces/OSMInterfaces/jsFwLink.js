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
 objet["enum"]["CatSceneType"]=0;
objet["enum"][0]="../OSMInterfaces/enum_CatSceneType_15559.htm";
objet["interface"]["ProductScene"]=0;
objet["interface"][0]="../OSMInterfaces/interface_ProductScene_18532.htm";
objet["interface"]["ProductScenes"]=1;
objet["interface"][1]="../OSMInterfaces/interface_ProductScenes_19912.htm";
objet["interface"]["Scene"]=2;
objet["interface"][2]="../OSMInterfaces/interface_Scene_12779.htm";
objet["interface"]["SceneProductData"]=3;
objet["interface"][3]="../OSMInterfaces/interface_SceneProductData_23915.htm";
objet["interface"]["SceneWorkbench"]=4;
objet["interface"][4]="../OSMInterfaces/interface_SceneWorkbench_21176.htm";
objet["interface"]["Scenes"]=5;
objet["interface"][5]="../OSMInterfaces/interface_Scenes_13354.htm";
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