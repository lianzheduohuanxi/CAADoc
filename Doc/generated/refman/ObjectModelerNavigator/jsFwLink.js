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
 objet["class"]["CATNavigController"]=0;
objet["class"][0]="../ObjectModelerNavigator/class_CATNavigController_41544.htm";
objet["class"]["CATNavigInstance"]=1;
objet["class"][1]="../ObjectModelerNavigator/class_CATNavigInstance_37631.htm";
objet["class"]["CATNodeExtension"]=2;
objet["class"][2]="../ObjectModelerNavigator/class_CATNodeExtension_38013.htm";
objet["enum"]["CATNavigNodeState"]=0;
objet["enum"][0]="../ObjectModelerNavigator/enum_CATNavigNodeState_38652.htm";
objet["interface"]["CATIGraphLink"]=0;
objet["interface"][0]="../ObjectModelerNavigator/interface_CATIGraphLink_35659.htm";
objet["interface"]["CATIGraphNode"]=1;
objet["interface"][1]="../ObjectModelerNavigator/interface_CATIGraphNode_35555.htm";
objet["interface"]["CATINavigContainer"]=2;
objet["interface"][2]="../ObjectModelerNavigator/interface_CATINavigContainer_43693.htm";
objet["interface"]["CATINavigElement"]=3;
objet["interface"][3]="../ObjectModelerNavigator/interface_CATINavigElement_40156.htm";
objet["interface"]["CATINavigModify"]=4;
objet["interface"][4]="../ObjectModelerNavigator/interface_CATINavigModify_38626.htm";
objet["interface"]["CATINavigNodeCtrl"]=5;
objet["interface"][5]="../ObjectModelerNavigator/interface_CATINavigNodeCtrl_41500.htm";
objet["interface"]["CATINavigateFilter"]=6;
objet["interface"][6]="../ObjectModelerNavigator/interface_CATINavigateFilter_43598.htm";
objet["interface"]["CATINavigateObject"]=7;
objet["interface"][7]="../ObjectModelerNavigator/interface_CATINavigateObject_43364.htm";
objet["interface"]["CATINavigateProvider"]=8;
objet["interface"][8]="../ObjectModelerNavigator/interface_CATINavigateProvider_47717.htm";
objet["interface"]["CATIRedrawEvent"]=9;
objet["interface"][9]="../ObjectModelerNavigator/interface_CATIRedrawEvent_38711.htm";
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