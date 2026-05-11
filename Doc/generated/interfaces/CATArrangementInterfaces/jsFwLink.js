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
 objet["enum"]["CATArrangementAreaVisuMode"]=0;
objet["enum"][0]="../CATArrangementInterfaces/enum_CATArrangementAreaVisuMode_62285.htm";
objet["enum"]["CATArrangementItemResVisuMode"]=1;
objet["enum"][1]="../CATArrangementInterfaces/enum_CATArrangementItemResVisuMode_70762.htm";
objet["enum"]["CATArrangementRouteSection"]=2;
objet["enum"][2]="../CATArrangementInterfaces/enum_CATArrangementRouteSection_63460.htm";
objet["enum"]["CATArrangementRouteVisuMode"]=3;
objet["enum"][3]="../CATArrangementInterfaces/enum_CATArrangementRouteVisuMode_65687.htm";
objet["interface"]["ArrBOMReport"]=0;
objet["interface"][0]="../CATArrangementInterfaces/interface_ArrBOMReport_39134.htm";
objet["interface"]["ArrBendableString"]=1;
objet["interface"][1]="../CATArrangementInterfaces/interface_ArrBendableString_46477.htm";
objet["interface"]["ArrNomenclature"]=2;
objet["interface"][2]="../CATArrangementInterfaces/interface_ArrNomenclature_43634.htm";
objet["interface"]["ArrNomenclatureTree"]=3;
objet["interface"][3]="../CATArrangementInterfaces/interface_ArrNomenclatureTree_50253.htm";
objet["interface"]["ArrNomenclatures"]=4;
objet["interface"][4]="../CATArrangementInterfaces/interface_ArrNomenclatures_45359.htm";
objet["interface"]["ArrSystemLineProduct"]=5;
objet["interface"][5]="../CATArrangementInterfaces/interface_ArrSystemLineProduct_52340.htm";
objet["interface"]["ArrWorkbench"]=6;
objet["interface"][6]="../CATArrangementInterfaces/interface_ArrWorkbench_39260.htm";
objet["interface"]["ArrangementArea"]=7;
objet["interface"][7]="../CATArrangementInterfaces/interface_ArrangementArea_43052.htm";
objet["interface"]["ArrangementAreas"]=8;
objet["interface"][8]="../CATArrangementInterfaces/interface_ArrangementAreas_44777.htm";
objet["interface"]["ArrangementBoundaries"]=9;
objet["interface"][9]="../CATArrangementInterfaces/interface_ArrangementBoundaries_54516.htm";
objet["interface"]["ArrangementBoundary"]=10;
objet["interface"][10]="../CATArrangementInterfaces/interface_ArrangementBoundary_50585.htm";
objet["interface"]["ArrangementContour"]=11;
objet["interface"][11]="../CATArrangementInterfaces/interface_ArrangementContour_48896.htm";
objet["interface"]["ArrangementContours"]=12;
objet["interface"][12]="../CATArrangementInterfaces/interface_ArrangementContours_50966.htm";
objet["interface"]["ArrangementItemReservation"]=13;
objet["interface"][13]="../CATArrangementInterfaces/interface_ArrangementItemReservation_66895.htm";
objet["interface"]["ArrangementItemReservations"]=14;
objet["interface"][14]="../CATArrangementInterfaces/interface_ArrangementItemReservations_69885.htm";
objet["interface"]["ArrangementNode"]=15;
objet["interface"][15]="../CATArrangementInterfaces/interface_ArrangementNode_43202.htm";
objet["interface"]["ArrangementNodes"]=16;
objet["interface"][16]="../CATArrangementInterfaces/interface_ArrangementNodes_44927.htm";
objet["interface"]["ArrangementPathway"]=17;
objet["interface"][17]="../CATArrangementInterfaces/interface_ArrangementPathway_48700.htm";
objet["interface"]["ArrangementPathways"]=18;
objet["interface"][18]="../CATArrangementInterfaces/interface_ArrangementPathways_50770.htm";
objet["interface"]["ArrangementProduct"]=19;
objet["interface"][19]="../CATArrangementInterfaces/interface_ArrangementProduct_48700.htm";
objet["interface"]["ArrangementRectangle"]=20;
objet["interface"][20]="../CATArrangementInterfaces/interface_ArrangementRectangle_52152.htm";
objet["interface"]["ArrangementRectangles"]=21;
objet["interface"][21]="../CATArrangementInterfaces/interface_ArrangementRectangles_54452.htm";
objet["interface"]["ArrangementRun"]=22;
objet["interface"][22]="../CATArrangementInterfaces/interface_ArrangementRun_42034.htm";
objet["interface"]["ArrangementRuns"]=23;
objet["interface"][23]="../CATArrangementInterfaces/interface_ArrangementRuns_43644.htm";
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