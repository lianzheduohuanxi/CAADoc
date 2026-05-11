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
 objet["interface"]["DMOOffset"]=0;
objet["interface"][0]="../SMTInterfaces/interface_DMOOffset_15467.htm";
objet["interface"]["DMOOffsets"]=1;
objet["interface"][1]="../SMTInterfaces/interface_DMOOffsets_16502.htm";
objet["interface"]["DMOThickness"]=2;
objet["interface"][2]="../SMTInterfaces/interface_DMOThickness_18727.htm";
objet["interface"]["DMOThicknesses"]=3;
objet["interface"][3]="../SMTInterfaces/interface_DMOThicknesses_21434.htm";
objet["interface"]["FreeSpace"]=4;
objet["interface"][4]="../SMTInterfaces/interface_FreeSpace_15346.htm";
objet["interface"]["FreeSpaces"]=5;
objet["interface"][5]="../SMTInterfaces/interface_FreeSpaces_16381.htm";
objet["interface"]["Merges"]=6;
objet["interface"][6]="../SMTInterfaces/interface_Merges_13369.htm";
objet["interface"]["OptimizerWorkBench"]=7;
objet["interface"][7]="../SMTInterfaces/interface_OptimizerWorkBench_27428.htm";
objet["interface"]["PartComp"]=8;
objet["interface"][8]="../SMTInterfaces/interface_PartComp_14686.htm";
objet["interface"]["PartComps"]=9;
objet["interface"][9]="../SMTInterfaces/interface_PartComps_15606.htm";
objet["interface"]["Silhouette"]=10;
objet["interface"][10]="../SMTInterfaces/interface_Silhouette_16669.htm";
objet["interface"]["Silhouettes"]=11;
objet["interface"][11]="../SMTInterfaces/interface_Silhouettes_17819.htm";
objet["interface"]["Simplifications"]=12;
objet["interface"][12]="../SMTInterfaces/interface_Simplifications_23067.htm";
objet["interface"]["SweptVolume"]=13;
objet["interface"][13]="../SMTInterfaces/interface_SweptVolume_17652.htm";
objet["interface"]["SweptVolumes"]=14;
objet["interface"][14]="../SMTInterfaces/interface_SweptVolumes_18917.htm";
objet["interface"]["ThreeDCuts"]=15;
objet["interface"][15]="../SMTInterfaces/interface_ThreeDCuts_16315.htm";
objet["interface"]["VibrationVolumes"]=16;
objet["interface"][16]="../SMTInterfaces/interface_VibrationVolumes_24682.htm";
objet["interface"]["Wrapping"]=17;
objet["interface"][17]="../SMTInterfaces/interface_Wrapping_14750.htm";
objet["interface"]["Wrappings"]=18;
objet["interface"][18]="../SMTInterfaces/interface_Wrappings_15670.htm";
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