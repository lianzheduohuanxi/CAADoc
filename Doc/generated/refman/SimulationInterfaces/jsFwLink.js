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
 objet["collection"]["CATIReplayList"]=0;
objet["collection"][0]="../SimulationInterfaces/class_CATIReplayList_30397.htm";
objet["define"]["LIST_ALL_BOTTOM"]=0;
objet["define"][0]="../SimulationInterfaces/define_LIST_ALL_BOTTOM_29839.htm";
objet["define"]["LIST_ALL_BOTTOM_C"]=1;
objet["define"][1]="../SimulationInterfaces/define_LIST_ALL_BOTTOM_C_32336.htm";
objet["define"]["LIST_ALL_TOP"]=2;
objet["define"][2]="../SimulationInterfaces/define_LIST_ALL_TOP_26844.htm";
objet["define"]["LIST_ALL_TOP_C"]=3;
objet["define"][3]="../SimulationInterfaces/define_LIST_ALL_TOP_C_28855.htm";
objet["define"]["LIST_EMPTY"]=4;
objet["define"][4]="../SimulationInterfaces/define_LIST_EMPTY_25185.htm";
objet["define"]["LIST_FORCED"]=5;
objet["define"][5]="../SimulationInterfaces/define_LIST_FORCED_25580.htm";
objet["define"]["LIST_FROM_CSO"]=6;
objet["define"][6]="../SimulationInterfaces/define_LIST_FROM_CSO_27742.htm";
objet["define"]["LIST_GLOBALNOTIF"]=7;
objet["define"][7]="../SimulationInterfaces/define_LIST_GLOBALNOTIF_30552.htm";
objet["define"]["LIST_LOCALNOTIF"]=8;
objet["define"][8]="../SimulationInterfaces/define_LIST_LOCALNOTIF_29458.htm";
objet["define"]["LIST_NONE"]=9;
objet["define"][9]="../SimulationInterfaces/define_LIST_NONE_24307.htm";
objet["define"]["LIST_UNDEFINED"]=10;
objet["define"][10]="../SimulationInterfaces/define_LIST_UNDEFINED_28196.htm";
objet["interface"]["CATIReplay"]=0;
objet["interface"][0]="../SimulationInterfaces/interface_CATIReplay_28181.htm";
objet["interface"]["CATIReplayChannel"]=1;
objet["interface"][1]="../SimulationInterfaces/interface_CATIReplayChannel_37372.htm";
objet["interface"]["CATIReplayChannelCameraMove"]=2;
objet["interface"][2]="../SimulationInterfaces/interface_CATIReplayChannelCameraMove_58887.htm";
objet["interface"]["CATIReplayChannelCameraMoveFactory"]=3;
objet["interface"][3]="../SimulationInterfaces/interface_CATIReplayChannelCameraMoveFactory_80926.htm";
objet["interface"]["CATIReplayChannelProductMove"]=4;
objet["interface"][4]="../SimulationInterfaces/interface_CATIReplayChannelProductMove_62614.htm";
objet["interface"]["CATIReplayChannelProductMoveFactory"]=5;
objet["interface"][5]="../SimulationInterfaces/interface_CATIReplayChannelProductMoveFactory_85381.htm";
objet["interface"]["CATIReplayChannelScalarObserver"]=6;
objet["interface"][6]="../SimulationInterfaces/interface_CATIReplayChannelScalarObserver_71514.htm";
objet["interface"]["CATIReplayChannelScalarObserverFactory"]=7;
objet["interface"][7]="../SimulationInterfaces/interface_CATIReplayChannelScalarObserverFactory_96465.htm";
objet["interface"]["CATIReplayFactory"]=8;
objet["interface"][8]="../SimulationInterfaces/interface_CATIReplayFactory_37844.htm";
objet["interface"]["CATISiList"]=9;
objet["interface"][9]="../SimulationInterfaces/interface_CATISiList_28067.htm";
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