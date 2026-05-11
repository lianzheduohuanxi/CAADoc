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
 objet["define"]["CatAnnotatedViewCmdOption_NoAnimation"]=0;
objet["define"][0]="../NavigatorInterfaces/define_CatAnnotatedViewCmdOption_NoAnimation_87685.htm";
objet["define"]["CatAnnotatedViewCmdOption_NoToolbar"]=1;
objet["define"][1]="../NavigatorInterfaces/define_CatAnnotatedViewCmdOption_NoToolbar_80261.htm";
objet["enum"]["CatAnnotatedViewBehavior"]=0;
objet["enum"][0]="../NavigatorInterfaces/enum_CatAnnotatedViewBehavior_47217.htm";
objet["enum"]["CatDMUGroupPreviewHiddenObjectsDisplayMode"]=1;
objet["enum"][1]="../NavigatorInterfaces/enum_CatDMUGroupPreviewHiddenObjectsDisplayMode_106334.htm";
objet["enum"]["CatMarker2DType"]=2;
objet["enum"][2]="../NavigatorInterfaces/enum_CatMarker2DType_28737.htm";
objet["enum"]["CatMarker3DType"]=3;
objet["enum"][3]="../NavigatorInterfaces/enum_CatMarker3DType_28746.htm";
objet["enum"]["CatMarkerTextOrientation"]=4;
objet["enum"][4]="../NavigatorInterfaces/enum_CatMarkerTextOrientation_47951.htm";
objet["enum"]["CatSacSettingsEnum"]=5;
objet["enum"][5]="../NavigatorInterfaces/enum_CatSacSettingsEnum_34552.htm";
objet["interface"]["AnnotatedView"]=0;
objet["interface"][0]="../NavigatorInterfaces/interface_AnnotatedView_29783.htm";
objet["interface"]["AnnotatedViews"]=1;
objet["interface"][1]="../NavigatorInterfaces/interface_AnnotatedViews_31278.htm";
objet["interface"]["DMUDataFlow"]=2;
objet["interface"][2]="../NavigatorInterfaces/interface_DMUDataFlow_27149.htm";
objet["interface"]["DMUReview"]=3;
objet["interface"][3]="../NavigatorInterfaces/interface_DMUReview_25381.htm";
objet["interface"]["DMUReviews"]=4;
objet["interface"][4]="../NavigatorInterfaces/interface_DMUReviews_26416.htm";
objet["interface"]["Group"]=5;
objet["interface"][5]="../NavigatorInterfaces/interface_Group_22740.htm";
objet["interface"]["Groups"]=6;
objet["interface"][6]="../NavigatorInterfaces/interface_Groups_23315.htm";
objet["interface"]["Hyperlink"]=7;
objet["interface"][7]="../NavigatorInterfaces/interface_Hyperlink_25505.htm";
objet["interface"]["Hyperlinks"]=8;
objet["interface"][8]="../NavigatorInterfaces/interface_Hyperlinks_26540.htm";
objet["interface"]["Marker2D"]=9;
objet["interface"][9]="../NavigatorInterfaces/interface_Marker2D_24001.htm";
objet["interface"]["Marker2Ds"]=10;
objet["interface"][10]="../NavigatorInterfaces/interface_Marker2Ds_24921.htm";
objet["interface"]["Marker3D"]=11;
objet["interface"][11]="../NavigatorInterfaces/interface_Marker3D_24007.htm";
objet["interface"]["Marker3Ds"]=12;
objet["interface"][12]="../NavigatorInterfaces/interface_Marker3Ds_24927.htm";
objet["interface"]["MarkerSettingAtt"]=13;
objet["interface"][13]="../NavigatorInterfaces/interface_MarkerSettingAtt_34107.htm";
objet["interface"]["N4DNavigatorSettingAtt"]=14;
objet["interface"][14]="../NavigatorInterfaces/interface_N4DNavigatorSettingAtt_45608.htm";
objet["interface"]["NavigatorWorkbench"]=15;
objet["interface"][15]="../NavigatorInterfaces/interface_NavigatorWorkbench_37656.htm";
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