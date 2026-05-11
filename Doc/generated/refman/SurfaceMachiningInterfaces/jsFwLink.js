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
 objet["interface"]["CATIMfg5AxisSpiralMilling"]=0;
objet["interface"][0]="../SurfaceMachiningInterfaces/interface_CATIMfg5AxisSpiralMilling_67497.htm";
objet["interface"]["CATIMfgMultiAxisContourDriven"]=1;
objet["interface"][1]="../SurfaceMachiningInterfaces/interface_CATIMfgMultiAxisContourDriven_79495.htm";
objet["interface"]["CATIMfgMultiAxisCurveMachining"]=2;
objet["interface"][2]="../SurfaceMachiningInterfaces/interface_CATIMfgMultiAxisCurveMachining_81653.htm";
objet["interface"]["CATIMfgMultiAxisCurveMachiningAuxDrive"]=3;
objet["interface"][3]="../SurfaceMachiningInterfaces/interface_CATIMfgMultiAxisCurveMachiningAuxDrive_108850.htm";
objet["interface"]["CATIMfgMultiAxisIsoparametricMachining"]=4;
objet["interface"][4]="../SurfaceMachiningInterfaces/interface_CATIMfgMultiAxisIsoparametricMachining_109677.htm";
objet["interface"]["CATIMfgMultiAxisSweeping"]=5;
objet["interface"][5]="../SurfaceMachiningInterfaces/interface_CATIMfgMultiAxisSweeping_65689.htm";
objet["interface"]["CATISmgFactory"]=6;
objet["interface"][6]="../SurfaceMachiningInterfaces/interface_CATISmgFactory_46608.htm";
objet["interface"]["CATISmgMachiningAreaChecks"]=7;
objet["interface"][7]="../SurfaceMachiningInterfaces/interface_CATISmgMachiningAreaChecks_69405.htm";
objet["interface"]["CATISmgMachiningAreaForbiddenZone"]=8;
objet["interface"][8]="../SurfaceMachiningInterfaces/interface_CATISmgMachiningAreaForbiddenZone_90441.htm";
objet["interface"]["CATISmgMachiningAreaGuidingCurves"]=9;
objet["interface"][9]="../SurfaceMachiningInterfaces/interface_CATISmgMachiningAreaGuidingCurves_91116.htm";
objet["interface"]["CATISmgMachiningAreaParts"]=10;
objet["interface"][10]="../SurfaceMachiningInterfaces/interface_CATISmgMachiningAreaParts_67512.htm";
objet["interface"]["CATISmgNcGeometryManager"]=11;
objet["interface"][11]="../SurfaceMachiningInterfaces/interface_CATISmgNcGeometryManager_65320.htm";
objet["interface"]["CATISmgNcGeometryParameter"]=12;
objet["interface"][12]="../SurfaceMachiningInterfaces/interface_CATISmgNcGeometryParameter_70893.htm";
objet["interface"]["CATISmgProgramAddin"]=13;
objet["interface"][13]="../SurfaceMachiningInterfaces/interface_CATISmgProgramAddin_54240.htm";
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