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
 objet["class"]["CATBodyTessellator"]=0;
objet["class"][0]="../Tessellation/class_CATBodyTessellator_24552.htm";
objet["class"]["CATCellTessellator"]=1;
objet["class"][1]="../Tessellation/class_CATCellTessellator_24477.htm";
objet["class"]["CATCurveTessellator"]=2;
objet["class"][2]="../Tessellation/class_CATCurveTessellator_26508.htm";
objet["class"]["CATSurfaceTessellator"]=3;
objet["class"][3]="../Tessellation/class_CATSurfaceTessellator_30473.htm";
objet["class"]["CATTessEdgeIter"]=4;
objet["class"][4]="../Tessellation/class_CATTessEdgeIter_18725.htm";
objet["class"]["CATTessFanIter"]=5;
objet["class"][5]="../Tessellation/class_CATTessFanIter_17357.htm";
objet["class"]["CATTessPointIter"]=6;
objet["class"][6]="../Tessellation/class_CATTessPointIter_20678.htm";
objet["class"]["CATTessPointPolyIter"]=7;
objet["class"][7]="../Tessellation/class_CATTessPointPolyIter_28024.htm";
objet["class"]["CATTessPolyIter"]=8;
objet["class"][8]="../Tessellation/class_CATTessPolyIter_19135.htm";
objet["class"]["CATTessStripeIter"]=9;
objet["class"][9]="../Tessellation/class_CATTessStripeIter_22342.htm";
objet["class"]["CATTessTrianIter"]=10;
objet["class"][10]="../Tessellation/class_CATTessTrianIter_20534.htm";
objet["class"]["CATTessVertexIter"]=11;
objet["class"][11]="../Tessellation/class_CATTessVertexIter_22460.htm";
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