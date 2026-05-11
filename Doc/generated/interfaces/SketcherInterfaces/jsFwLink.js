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
 objet["enum"]["CatGeometricType"]=0;
objet["enum"][0]="../SketcherInterfaces/enum_CatGeometricType_29220.htm";
objet["interface"]["Axis2D"]=0;
objet["interface"][0]="../SketcherInterfaces/interface_Axis2D_20839.htm";
objet["interface"]["Circle2D"]=1;
objet["interface"][1]="../SketcherInterfaces/interface_Circle2D_21967.htm";
objet["interface"]["ControlPoint2D"]=2;
objet["interface"][2]="../SketcherInterfaces/interface_ControlPoint2D_28215.htm";
objet["interface"]["Curve2D"]=3;
objet["interface"][3]="../SketcherInterfaces/interface_Curve2D_21385.htm";
objet["interface"]["Ellipse2D"]=4;
objet["interface"][4]="../SketcherInterfaces/interface_Ellipse2D_22786.htm";
objet["interface"]["Factory2D"]=5;
objet["interface"][5]="../SketcherInterfaces/interface_Factory2D_22901.htm";
objet["interface"]["GeometricElement"]=6;
objet["interface"][6]="../SketcherInterfaces/interface_GeometricElement_32182.htm";
objet["interface"]["Geometry2D"]=7;
objet["interface"][7]="../SketcherInterfaces/interface_Geometry2D_23801.htm";
objet["interface"]["Hyperbola2D"]=8;
objet["interface"][8]="../SketcherInterfaces/interface_Hyperbola2D_24546.htm";
objet["interface"]["Line2D"]=9;
objet["interface"][9]="../SketcherInterfaces/interface_Line2D_20792.htm";
objet["interface"]["Parabola2D"]=10;
objet["interface"][10]="../SketcherInterfaces/interface_Parabola2D_23526.htm";
objet["interface"]["Point2D"]=11;
objet["interface"][11]="../SketcherInterfaces/interface_Point2D_21397.htm";
objet["interface"]["Sketch"]=12;
objet["interface"][12]="../SketcherInterfaces/interface_Sketch_21197.htm";
objet["interface"]["Spline2D"]=13;
objet["interface"][13]="../SketcherInterfaces/interface_Spline2D_21988.htm";
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