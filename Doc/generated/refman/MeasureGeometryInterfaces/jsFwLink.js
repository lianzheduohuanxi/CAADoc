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
 objet["enum"]["CATExtend"]=0;
objet["enum"][0]="../MeasureGeometryInterfaces/enum_CATExtend_35853.htm";
objet["enum"]["CATIMeasurableType"]=1;
objet["enum"][1]="../MeasureGeometryInterfaces/enum_CATIMeasurableType_47948.htm";
objet["enum"]["CATMeasResultData"]=2;
objet["enum"][2]="../MeasureGeometryInterfaces/enum_CATMeasResultData_45921.htm";
objet["enum"]["CATMeasurableName"]=3;
objet["enum"][3]="../MeasureGeometryInterfaces/enum_CATMeasurableName_45827.htm";
objet["enum"]["CATSiCalculationType"]=4;
objet["enum"][4]="../MeasureGeometryInterfaces/enum_CATSiCalculationType_52041.htm";
objet["enum"]["CATSiMeasureEdgeType"]=5;
objet["enum"][5]="../MeasureGeometryInterfaces/enum_CATSiMeasureEdgeType_51394.htm";
objet["enum"]["CATSiMeasureSurfaceType"]=6;
objet["enum"][6]="../MeasureGeometryInterfaces/enum_CATSiMeasureSurfaceType_58259.htm";
objet["interface"]["CATIMeasurable"]=0;
objet["interface"][0]="../MeasureGeometryInterfaces/interface_CATIMeasurable_44471.htm";
objet["interface"]["CATIMeasurableAxisSystem"]=1;
objet["interface"][1]="../MeasureGeometryInterfaces/interface_CATIMeasurableAxisSystem_64074.htm";
objet["interface"]["CATIMeasurableCircle"]=2;
objet["interface"][2]="../MeasureGeometryInterfaces/interface_CATIMeasurableCircle_54354.htm";
objet["interface"]["CATIMeasurableCone"]=3;
objet["interface"][3]="../MeasureGeometryInterfaces/interface_CATIMeasurableCone_50551.htm";
objet["interface"]["CATIMeasurableCurve"]=4;
objet["interface"][4]="../MeasureGeometryInterfaces/interface_CATIMeasurableCurve_52812.htm";
objet["interface"]["CATIMeasurableCylinder"]=5;
objet["interface"][5]="../MeasureGeometryInterfaces/interface_CATIMeasurableCylinder_59031.htm";
objet["interface"]["CATIMeasurableLine"]=6;
objet["interface"][6]="../MeasureGeometryInterfaces/interface_CATIMeasurableLine_50587.htm";
objet["interface"]["CATIMeasurablePlane"]=7;
objet["interface"][7]="../MeasureGeometryInterfaces/interface_CATIMeasurablePlane_52451.htm";
objet["interface"]["CATIMeasurablePoint"]=8;
objet["interface"][8]="../MeasureGeometryInterfaces/interface_CATIMeasurablePoint_52894.htm";
objet["interface"]["CATIMeasurableSphere"]=9;
objet["interface"][9]="../MeasureGeometryInterfaces/interface_CATIMeasurableSphere_54665.htm";
objet["interface"]["CATIMeasurableSurface"]=10;
objet["interface"][10]="../MeasureGeometryInterfaces/interface_CATIMeasurableSurface_56593.htm";
objet["interface"]["CATIMeasurableVolume"]=11;
objet["interface"][11]="../MeasureGeometryInterfaces/interface_CATIMeasurableVolume_54938.htm";
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