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
 objet["collection"]["CATLISTP(CATPrintImage)"]=0;
objet["collection"][0]="../PrintBase/class_CATLISTP(CATPrintImage)_27026.htm";
objet["collection"]["CATLISTP(CATPrinter)"]=1;
objet["collection"][1]="../PrintBase/class_CATLISTP(CATPrinter)_21445.htm";
objet["collection"]["CATLISTV(CATPrintForm)"]=2;
objet["collection"][2]="../PrintBase/class_CATLISTV(CATPrintForm)_25334.htm";
objet["class"]["CATPrintDevice"]=0;
objet["class"][0]="../PrintBase/class_CATPrintDevice_13965.htm";
objet["class"]["CATPrintFileDevice"]=1;
objet["class"][1]="../PrintBase/class_CATPrintFileDevice_20029.htm";
objet["class"]["CATPrintFileGenerator"]=2;
objet["class"][2]="../PrintBase/class_CATPrintFileGenerator_26542.htm";
objet["class"]["CATPrintFileImage"]=3;
objet["class"][3]="../PrintBase/class_CATPrintFileImage_18184.htm";
objet["class"]["CATPrintForm"]=4;
objet["class"][4]="../PrintBase/class_CATPrintForm_11574.htm";
objet["class"]["CATPrintGenerator"]=5;
objet["class"][5]="../PrintBase/class_CATPrintGenerator_19106.htm";
objet["class"]["CATPrintImage"]=6;
objet["class"][6]="../PrintBase/class_CATPrintImage_12556.htm";
objet["class"]["CATPrintParameters"]=7;
objet["class"][7]="../PrintBase/class_CATPrintParameters_20935.htm";
objet["class"]["CATPrintStream"]=8;
objet["class"][8]="../PrintBase/class_CATPrintStream_14216.htm";
objet["class"]["CATPrintVisuParameters"]=9;
objet["class"][9]="../PrintBase/class_CATPrintVisuParameters_29181.htm";
objet["class"]["CATPrinter"]=10;
objet["class"][10]="../PrintBase/class_CATPrinter_9510.htm";
objet["class"]["CATPrinterDevice"]=11;
objet["class"][11]="../PrintBase/class_CATPrinterDevice_16983.htm";
objet["class"]["CATPrinterManager"]=12;
objet["class"][12]="../PrintBase/class_CATPrinterManager_18709.htm";
objet["enum"]["CATPrintBannerPosition"]=0;
objet["enum"][0]="../PrintBase/enum_CATPrintBannerPosition_28668.htm";
objet["enum"]["CATPrintClipping_State"]=1;
objet["enum"][1]="../PrintBase/enum_CATPrintClipping_State_28127.htm";
objet["enum"]["CATPrintColorMode"]=2;
objet["enum"][2]="../PrintBase/enum_CATPrintColorMode_18115.htm";
objet["enum"]["CATPrintLineAttribute"]=3;
objet["enum"][3]="../PrintBase/enum_CATPrintLineAttribute_26302.htm";
objet["enum"]["CATPrintLineCap"]=4;
objet["enum"][4]="../PrintBase/enum_CATPrintLineCap_14637.htm";
objet["enum"]["CATPrintLineSpecification"]=5;
objet["enum"][5]="../PrintBase/enum_CATPrintLineSpecification_35419.htm";
objet["enum"]["CATPrintMarkerAttribute"]=6;
objet["enum"][6]="../PrintBase/enum_CATPrintMarkerAttribute_30934.htm";
objet["enum"]["CATPrintOrientation"]=7;
objet["enum"][7]="../PrintBase/enum_CATPrintOrientation_22532.htm";
objet["enum"]["CATPrintRenderMode"]=8;
objet["enum"][8]="../PrintBase/enum_CATPrintRenderMode_19759.htm";
objet["enum"]["CATPrintRotation"]=9;
objet["enum"][9]="../PrintBase/enum_CATPrintRotation_17083.htm";
objet["enum"]["CATPrintStandard"]=10;
objet["enum"][10]="../PrintBase/enum_CATPrintStandard_16685.htm";
objet["enum"]["CATPrintTextAttribute"]=11;
objet["enum"][11]="../PrintBase/enum_CATPrintTextAttribute_26595.htm";
objet["enum"]["CATPrintTextClipping"]=12;
objet["enum"][12]="../PrintBase/enum_CATPrintTextClipping_24169.htm";
objet["enum"]["CATPrintTextSupport"]=13;
objet["enum"][13]="../PrintBase/enum_CATPrintTextSupport_22864.htm";
objet["enum"]["CATPrintUnit"]=14;
objet["enum"][14]="../PrintBase/enum_CATPrintUnit_11236.htm";
objet["interface"]["CATIPrintable"]=0;
objet["interface"][0]="../PrintBase/interface_CATIPrintable_15260.htm";
objet["interface"]["CATIPrintableDrafting"]=1;
objet["interface"][1]="../PrintBase/interface_CATIPrintableDrafting_28839.htm";
objet["interface"]["CATIPrintables"]=2;
objet["interface"][2]="../PrintBase/interface_CATIPrintables_16755.htm";
objet["interface"]["CATIPrinterManager"]=3;
objet["interface"][3]="../PrintBase/interface_CATIPrinterManager_22954.htm";
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