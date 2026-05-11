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
 objet["enum"]["CAT2DCstDiag"]=0;
objet["enum"][0]="../CATSketcherUseItf/enum_CAT2DCstDiag_20462.htm";
objet["enum"]["CAT2DCstGenericType"]=1;
objet["enum"][1]="../CATSketcherUseItf/enum_CAT2DCstGenericType_31595.htm";
objet["enum"]["CAT2DCstSearchMode"]=2;
objet["enum"][2]="../CATSketcherUseItf/enum_CAT2DCstSearchMode_29267.htm";
objet["enum"]["CAT2DCstType"]=3;
objet["enum"][3]="../CATSketcherUseItf/enum_CAT2DCstType_20862.htm";
objet["enum"]["CAT2DEltType"]=4;
objet["enum"][4]="../CATSketcherUseItf/enum_CAT2DEltType_20830.htm";
objet["enum"]["CAT2DImportMode"]=5;
objet["enum"][5]="../CATSketcherUseItf/enum_CAT2DImportMode_24803.htm";
objet["enum"]["CAT2DOffsetCornerType"]=6;
objet["enum"][6]="../CATSketcherUseItf/enum_CAT2DOffsetCornerType_35927.htm";
objet["enum"]["CAT2DOffsetModeType"]=7;
objet["enum"][7]="../CATSketcherUseItf/enum_CAT2DOffsetModeType_31554.htm";
objet["enum"]["CAT2DOffsetPropagType"]=8;
objet["enum"][8]="../CATSketcherUseItf/enum_CAT2DOffsetPropagType_35859.htm";
objet["enum"]["CAT2DOperatorType"]=9;
objet["enum"][9]="../CATSketcherUseItf/enum_CAT2DOperatorType_28423.htm";
objet["enum"]["CAT2DSolvingMode"]=10;
objet["enum"][10]="../CATSketcherUseItf/enum_CAT2DSolvingMode_26274.htm";
objet["enum"]["CATAutosearchMode"]=11;
objet["enum"][11]="../CATSketcherUseItf/enum_CATAutosearchMode_28154.htm";
objet["enum"]["CATContourClass"]=12;
objet["enum"][12]="../CATSketcherUseItf/enum_CATContourClass_25368.htm";
objet["enum"]["CATContourType"]=13;
objet["enum"][13]="../CATSketcherUseItf/enum_CATContourType_24069.htm";
objet["enum"]["CATSktPosDirection"]=14;
objet["enum"][14]="../CATSketcherUseItf/enum_CATSktPosDirection_30305.htm";
objet["enum"]["CATSktPosOrientationMode"]=15;
objet["enum"][15]="../CATSketcherUseItf/enum_CATSktPosOrientationMode_42895.htm";
objet["enum"]["CATSktPosOriginMode"]=16;
objet["enum"][16]="../CATSketcherUseItf/enum_CATSktPosOriginMode_31641.htm";
objet["enum"]["CATSktPosSupportMode"]=17;
objet["enum"][17]="../CATSketcherUseItf/enum_CATSktPosSupportMode_34155.htm";
objet["interface"]["IDMCircle2D"]=0;
objet["interface"][0]="../CATSketcherUseItf/interface_IDMCircle2D_22102.htm";
objet["interface"]["IDMCurve2D"]=1;
objet["interface"][1]="../CATSketcherUseItf/interface_IDMCurve2D_21289.htm";
objet["interface"]["IDMEllipse2D"]=2;
objet["interface"][2]="../CATSketcherUseItf/interface_IDMEllipse2D_23293.htm";
objet["interface"]["IDMLine2D"]=3;
objet["interface"][3]="../CATSketcherUseItf/interface_IDMLine2D_20321.htm";
objet["interface"]["IDMPlane"]=4;
objet["interface"][4]="../CATSketcherUseItf/interface_IDMPlane_20147.htm";
objet["interface"]["IDMPoint2D"]=5;
objet["interface"][5]="../CATSketcherUseItf/interface_IDMPoint2D_21316.htm";
objet["interface"]["IDMPolyline2D"]=6;
objet["interface"][6]="../CATSketcherUseItf/interface_IDMPolyline2D_24535.htm";
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