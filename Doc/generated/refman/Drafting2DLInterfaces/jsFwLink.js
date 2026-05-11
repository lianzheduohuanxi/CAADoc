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
 objet["class"]["CAT2DLDrawingServices"]=0;
objet["class"][0]="../Drafting2DLInterfaces/class_CAT2DLDrawingServices_43361.htm";
objet["class"]["CAT2DLayoutServices"]=1;
objet["class"][1]="../Drafting2DLInterfaces/class_CAT2DLayoutServices_39670.htm";
objet["enum"]["CAT2DLClippingProfileMode"]=0;
objet["enum"][0]="../Drafting2DLInterfaces/enum_CAT2DLClippingProfileMode_51524.htm";
objet["enum"]["CAT2DLViewSide"]=1;
objet["enum"][1]="../Drafting2DLInterfaces/enum_CAT2DLViewSide_30127.htm";
objet["enum"]["CatClippingFrameReframeOnMode"]=2;
objet["enum"][2]="../Drafting2DLInterfaces/enum_CatClippingFrameReframeOnMode_61985.htm";
objet["enum"]["CatDedicatedFilterType"]=3;
objet["enum"][3]="../Drafting2DLInterfaces/enum_CatDedicatedFilterType_45337.htm";
objet["enum"]["CatInsureViewNamesUniquenessScope"]=4;
objet["enum"][4]="../Drafting2DLInterfaces/enum_CatInsureViewNamesUniquenessScope_76755.htm";
objet["enum"]["CatViewBackgroundMode"]=5;
objet["enum"][5]="../Drafting2DLInterfaces/enum_CatViewBackgroundMode_42948.htm";
objet["enum"]["CatViewFilterCreationMode"]=6;
objet["enum"][6]="../Drafting2DLInterfaces/enum_CatViewFilterCreationMode_52119.htm";
objet["enum"]["CatVisuBackgroundMode"]=7;
objet["enum"][7]="../Drafting2DLInterfaces/enum_CatVisuBackgroundMode_43006.htm";
objet["interface"]["CATI2DLBackWkbAddin"]=0;
objet["interface"][0]="../Drafting2DLInterfaces/interface_CATI2DLBackWkbAddin_40424.htm";
objet["interface"]["CATI2DLMainWkbAddin"]=1;
objet["interface"][1]="../Drafting2DLInterfaces/interface_CATI2DLMainWkbAddin_40585.htm";
objet["interface"]["CATI2DLayoutClipping"]=2;
objet["interface"][2]="../Drafting2DLInterfaces/interface_CATI2DLayoutClipping_43899.htm";
objet["interface"]["CATI2DLayoutLayout"]=3;
objet["interface"][3]="../Drafting2DLInterfaces/interface_CATI2DLayoutLayout_40403.htm";
objet["interface"]["CATI2DLayoutSheet"]=4;
objet["interface"][4]="../Drafting2DLInterfaces/interface_CATI2DLayoutSheet_38160.htm";
objet["interface"]["CATI2DLayoutView"]=5;
objet["interface"][5]="../Drafting2DLInterfaces/interface_CATI2DLayoutView_36623.htm";
objet["interface"]["CATID2o2DLSettingAtt"]=6;
objet["interface"][6]="../Drafting2DLInterfaces/interface_CATID2o2DLSettingAtt_42711.htm";
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