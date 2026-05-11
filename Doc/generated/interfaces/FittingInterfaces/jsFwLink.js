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
 objet["enum"]["CATFittingShuttleVector"]=0;
objet["enum"][0]="../FittingInterfaces/enum_CATFittingShuttleVector_41616.htm";
objet["enum"]["CATManipAutoInsertMode"]=1;
objet["enum"][1]="../FittingInterfaces/enum_CATManipAutoInsertMode_38482.htm";
objet["enum"]["CATManipClashMode"]=2;
objet["enum"][2]="../FittingInterfaces/enum_CATManipClashMode_28347.htm";
objet["enum"]["CatSampledAnalysisMode"]=3;
objet["enum"][3]="../FittingInterfaces/enum_CatSampledAnalysisMode_38614.htm";
objet["enum"]["CatSampledSplitType"]=4;
objet["enum"][4]="../FittingInterfaces/enum_CatSampledSplitType_32781.htm";
objet["enum"]["CatShuttleMoveMode"]=5;
objet["enum"][5]="../FittingInterfaces/enum_CatShuttleMoveMode_30509.htm";
objet["enum"]["CatShuttleVector"]=6;
objet["enum"][6]="../FittingInterfaces/enum_CatShuttleVector_27660.htm";
objet["enum"]["DMUTrackMoveMode"]=7;
objet["enum"][7]="../FittingInterfaces/enum_DMUTrackMoveMode_26840.htm";
objet["interface"]["FittingSettingAtt"]=0;
objet["interface"][0]="../FittingInterfaces/interface_FittingSettingAtt_32078.htm";
objet["interface"]["ManipSettingAtt"]=1;
objet["interface"][1]="../FittingInterfaces/interface_ManipSettingAtt_28823.htm";
objet["interface"]["Sampled"]=2;
objet["interface"][2]="../FittingInterfaces/interface_Sampled_20080.htm";
objet["interface"]["Sampleds"]=3;
objet["interface"][3]="../FittingInterfaces/interface_Sampleds_20885.htm";
objet["interface"]["SampledsNode"]=4;
objet["interface"][4]="../FittingInterfaces/interface_SampledsNode_24619.htm";
objet["interface"]["Shot"]=5;
objet["interface"][5]="../FittingInterfaces/interface_Shot_18566.htm";
objet["interface"]["Shots"]=6;
objet["interface"][6]="../FittingInterfaces/interface_Shots_19026.htm";
objet["interface"]["Shuttle"]=7;
objet["interface"][7]="../FittingInterfaces/interface_Shuttle_20188.htm";
objet["interface"]["Shuttles"]=8;
objet["interface"][8]="../FittingInterfaces/interface_Shuttles_20993.htm";
objet["interface"]["Track"]=9;
objet["interface"][9]="../FittingInterfaces/interface_Track_18925.htm";
objet["interface"]["Tracks"]=10;
objet["interface"][10]="../FittingInterfaces/interface_Tracks_19500.htm";
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