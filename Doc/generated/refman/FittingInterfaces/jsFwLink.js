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
 objet["define"]["CATSiFiShuttleAngle"]=0;
objet["define"][0]="../FittingInterfaces/define_CATSiFiShuttleAngle_33018.htm";
objet["enum"]["CATFitTrackMoveMode"]=0;
objet["enum"][0]="../FittingInterfaces/enum_CATFitTrackMoveMode_31927.htm";
objet["enum"]["CATFittingShuttleVector"]=1;
objet["enum"][1]="../FittingInterfaces/enum_CATFittingShuttleVector_41616.htm";
objet["enum"]["CATManipAutoInsertMode"]=2;
objet["enum"][2]="../FittingInterfaces/enum_CATManipAutoInsertMode_38482.htm";
objet["enum"]["CATManipClashMode"]=3;
objet["enum"][3]="../FittingInterfaces/enum_CATManipClashMode_28347.htm";
objet["enum"]["CatFitSampledRecordMode"]=4;
objet["enum"][4]="../FittingInterfaces/enum_CatFitSampledRecordMode_40340.htm";
objet["enum"]["CatFitSampledRep"]=5;
objet["enum"][5]="../FittingInterfaces/enum_CatFitSampledRep_27016.htm";
objet["interface"]["CATISampled"]=0;
objet["interface"][0]="../FittingInterfaces/interface_CATISampled_23372.htm";
objet["interface"]["CATIShot"]=1;
objet["interface"][1]="../FittingInterfaces/interface_CATIShot_20674.htm";
objet["interface"]["CATISiFiFittingSettingAtt"]=2;
objet["interface"][2]="../FittingInterfaces/interface_CATISiFiFittingSettingAtt_48590.htm";
objet["interface"]["CATISiFiManipSettingAtt"]=3;
objet["interface"][3]="../FittingInterfaces/interface_CATISiFiManipSettingAtt_43543.htm";
objet["interface"]["CATISiShuttle"]=4;
objet["interface"][4]="../FittingInterfaces/interface_CATISiShuttle_25967.htm";
objet["interface"]["CATISiShuttleFactory"]=5;
objet["interface"][5]="../FittingInterfaces/interface_CATISiShuttleFactory_37814.htm";
objet["interface"]["CATITrack"]=6;
objet["interface"][6]="../FittingInterfaces/interface_CATITrack_21381.htm";
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