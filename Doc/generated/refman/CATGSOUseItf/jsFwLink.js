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
 objet["enum"]["CATGSMDevelopMethod"]=0;
objet["enum"][0]="../CATGSOUseItf/enum_CATGSMDevelopMethod_24188.htm";
objet["enum"]["CATGSMTypeOfTransfer"]=1;
objet["enum"][1]="../CATGSOUseItf/enum_CATGSMTypeOfTransfer_26193.htm";
objet["enum"]["CATGSMUnfoldEdgeToTearPositioning"]=2;
objet["enum"][2]="../CATGSOUseItf/enum_CATGSMUnfoldEdgeToTearPositioning_61128.htm";
objet["enum"]["CATGSMUnfoldSurfaceType"]=3;
objet["enum"][3]="../CATGSOUseItf/enum_CATGSMUnfoldSurfaceType_32630.htm";
objet["enum"]["CATGSMUnfoldTargetOrientationMode"]=4;
objet["enum"][4]="../CATGSOUseItf/enum_CATGSMUnfoldTargetOrientationMode_61169.htm";
objet["enum"]["CATGSOWrapCurveRefDirType"]=5;
objet["enum"][5]="../CATGSOUseItf/enum_CATGSOWrapCurveRefDirType_36961.htm";
objet["enum"]["CATGSOWrapCurveRefSpineType"]=6;
objet["enum"][6]="../CATGSOUseItf/enum_CATGSOWrapCurveRefSpineType_42552.htm";
objet["enum"]["CATGSOWrapCurveSurfaceCst"]=7;
objet["enum"][7]="../CATGSOUseItf/enum_CATGSOWrapCurveSurfaceCst_37194.htm";
objet["enum"]["CATGSOWrapCurveTargSpineType"]=8;
objet["enum"][8]="../CATGSOUseItf/enum_CATGSOWrapCurveTargSpineType_45505.htm";
objet["enum"]["CATGSOWrapSurfaceRefDirType"]=9;
objet["enum"][9]="../CATGSOUseItf/enum_CATGSOWrapSurfaceRefDirType_41938.htm";
objet["interface"]["CATIGSMUseDevelop"]=0;
objet["interface"][0]="../CATGSOUseItf/interface_CATIGSMUseDevelop_23455.htm";
objet["interface"]["CATIGSMUseSurfaceSimplification"]=1;
objet["interface"][1]="../CATGSOUseItf/interface_CATIGSMUseSurfaceSimplification_57880.htm";
objet["interface"]["CATIGSMUseTransfer"]=2;
objet["interface"][2]="../CATGSOUseItf/interface_CATIGSMUseTransfer_25348.htm";
objet["interface"]["CATIGSMUseUnfold"]=3;
objet["interface"][3]="../CATGSOUseItf/interface_CATIGSMUseUnfold_21705.htm";
objet["interface"]["CATIGSOUseBump"]=4;
objet["interface"][4]="../CATGSOUseItf/interface_CATIGSOUseBump_18689.htm";
objet["interface"]["CATIGSOUseFactory"]=5;
objet["interface"][5]="../CATGSOUseItf/interface_CATIGSOUseFactory_23641.htm";
objet["interface"]["CATIGSOUseFactoryGeo"]=6;
objet["interface"][6]="../CATGSOUseItf/interface_CATIGSOUseFactoryGeo_28775.htm";
objet["interface"]["CATIGSOUseWrapCurve"]=7;
objet["interface"][7]="../CATGSOUseItf/interface_CATIGSOUseWrapCurve_27063.htm";
objet["interface"]["CATIGSOUseWrapSurface"]=8;
objet["interface"][8]="../CATGSOUseItf/interface_CATIGSOUseWrapSurface_30844.htm";
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