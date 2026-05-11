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
 objet["class"]["CATMf3DBehavior2Adapter"]=0;
objet["class"][0]="../MechanicalModeler/class_CATMf3DBehavior2Adapter_39703.htm";
objet["class"]["CATMfCkeServices"]=1;
objet["class"][1]="../MechanicalModeler/class_CATMfCkeServices_27335.htm";
objet["class"]["CATMmrAlgoConfigServices"]=2;
objet["class"][2]="../MechanicalModeler/class_CATMmrAlgoConfigServices_43458.htm";
objet["class"]["CATMmrApplicativeAttributes"]=3;
objet["class"][3]="../MechanicalModeler/class_CATMmrApplicativeAttributes_52289.htm";
objet["class"]["CATMmrBRepScanServices"]=4;
objet["class"][4]="../MechanicalModeler/class_CATMmrBRepScanServices_38564.htm";
objet["class"]["CATMmrFeatureAttributes"]=5;
objet["class"][5]="../MechanicalModeler/class_CATMmrFeatureAttributes_41911.htm";
objet["class"]["CATMmrImportComparator"]=6;
objet["class"][6]="../MechanicalModeler/class_CATMmrImportComparator_39571.htm";
objet["class"]["CATMmrInterPartCopy"]=7;
objet["class"][7]="../MechanicalModeler/class_CATMmrInterPartCopy_32750.htm";
objet["class"]["CATMmrLinearBodyServices"]=8;
objet["class"][8]="../MechanicalModeler/class_CATMmrLinearBodyServices_43591.htm";
objet["class"]["CATMmrShapeFeaturePropertiesAdapter"]=9;
objet["class"][9]="../MechanicalModeler/class_CATMmrShapeFeaturePropertiesAdapter_76920.htm";
objet["function"]["CATBRepDecode"]=0;
objet["function"][0]="../MechanicalModeler/_function_CATBRepDecode.htm";
objet["function"]["CATBRepDecodeAxis"]=1;
objet["function"][1]="../MechanicalModeler/_function_CATBRepDecodeAxis.htm";
objet["function"]["CATBRepDecodeCellInBody"]=2;
objet["function"][2]="../MechanicalModeler/function_CATBRepDecodeCellInBody_118662.htm";
objet["function"]["CATBRepDecodeExtremity"]=3;
objet["function"][3]="../MechanicalModeler/_function_CATBRepDecodeExtremity.htm";
objet["function"]["CATBRepDecodePlanarSubElement"]=4;
objet["function"][4]="../MechanicalModeler/_function_CATBRepDecodePlanarSubElement.htm";
objet["function"]["CATMmrGetCanonicBRepFromGeometricalElement"]=5;
objet["function"][5]="../MechanicalModeler/function_CATMmrGetCanonicBRepFromGeometricalElement_205602.htm";
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