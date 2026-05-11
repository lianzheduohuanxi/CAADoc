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
 objet["enum"]["CATStrSectionProperties"]=0;
objet["enum"][0]="../StructureInterfaces/enum_CATStrSectionProperties_45596.htm";
objet["enum"]["CatStrCreationMode"]=1;
objet["enum"][1]="../StructureInterfaces/enum_CatStrCreationMode_34261.htm";
objet["enum"]["CatStrCutbackType"]=2;
objet["enum"][2]="../StructureInterfaces/enum_CatStrCutbackType_32699.htm";
objet["enum"]["CatStrLinkMode"]=3;
objet["enum"][3]="../StructureInterfaces/enum_CatStrLinkMode_27781.htm";
objet["enum"]["CatStrMaterialOrientation"]=4;
objet["enum"][4]="../StructureInterfaces/enum_CatStrMaterialOrientation_50360.htm";
objet["enum"]["CatStrMemberExtremity"]=5;
objet["enum"][5]="../StructureInterfaces/enum_CatStrMemberExtremity_41135.htm";
objet["enum"]["CatStrPlacementPoint"]=6;
objet["enum"][6]="../StructureInterfaces/enum_CatStrPlacementPoint_38566.htm";
objet["enum"]["CatStrPlaneMode"]=7;
objet["enum"][7]="../StructureInterfaces/enum_CatStrPlaneMode_29148.htm";
objet["interface"]["ColorESSObjectSettingAtt"]=0;
objet["interface"][0]="../StructureInterfaces/interface_ColorESSObjectSettingAtt_49705.htm";
objet["interface"]["ColorSTDObjectSettingAtt"]=1;
objet["interface"][1]="../StructureInterfaces/interface_ColorSTDObjectSettingAtt_49676.htm";
objet["interface"]["MaterialESSObjectSettingAtt"]=2;
objet["interface"][2]="../StructureInterfaces/interface_MaterialESSObjectSettingAtt_57135.htm";
objet["interface"]["PPGExecLogSettingAtt"]=3;
objet["interface"][3]="../StructureInterfaces/interface_PPGExecLogSettingAtt_41015.htm";
objet["interface"]["PathESSRessourcesSettingAtt"]=4;
objet["interface"][4]="../StructureInterfaces/interface_PathESSRessourcesSettingAtt_58122.htm";
objet["interface"]["StrAnchorPoint"]=5;
objet["interface"][5]="../StructureInterfaces/interface_StrAnchorPoint_31254.htm";
objet["interface"]["StrAnchorPoints"]=6;
objet["interface"][6]="../StructureInterfaces/interface_StrAnchorPoints_32864.htm";
objet["interface"]["StrComputeServices"]=7;
objet["interface"][7]="../StructureInterfaces/interface_StrComputeServices_37885.htm";
objet["interface"]["StrCutback"]=8;
objet["interface"][8]="../StructureInterfaces/interface_StrCutback_26269.htm";
objet["interface"]["StrCutoutFeature"]=9;
objet["interface"][9]="../StructureInterfaces/interface_StrCutoutFeature_34391.htm";
objet["interface"]["StrFeatureFactory"]=10;
objet["interface"][10]="../StructureInterfaces/interface_StrFeatureFactory_36096.htm";
objet["interface"]["StrFoundation"]=11;
objet["interface"][11]="../StructureInterfaces/interface_StrFoundation_30008.htm";
objet["interface"]["StrFoundations"]=12;
objet["interface"][12]="../StructureInterfaces/interface_StrFoundations_31503.htm";
objet["interface"]["StrMember"]=13;
objet["interface"][13]="../StructureInterfaces/interface_StrMember_25385.htm";
objet["interface"]["StrMemberExtremity"]=14;
objet["interface"][14]="../StructureInterfaces/interface_StrMemberExtremity_38177.htm";
objet["interface"]["StrMembers"]=15;
objet["interface"][15]="../StructureInterfaces/interface_StrMembers_26420.htm";
objet["interface"]["StrNibblingFeature"]=16;
objet["interface"][16]="../StructureInterfaces/interface_StrNibblingFeature_37509.htm";
objet["interface"]["StrObject"]=17;
objet["interface"][17]="../StructureInterfaces/interface_StrObject_25384.htm";
objet["interface"]["StrObjectExt"]=18;
objet["interface"][18]="../StructureInterfaces/interface_StrObjectExt_28481.htm";
objet["interface"]["StrObjectFactory"]=19;
objet["interface"][19]="../StructureInterfaces/interface_StrObjectFactory_34319.htm";
objet["interface"]["StrPlate"]=20;
objet["interface"][20]="../StructureInterfaces/interface_StrPlate_24558.htm";
objet["interface"]["StrPlates"]=21;
objet["interface"][21]="../StructureInterfaces/interface_StrPlates_25478.htm";
objet["interface"]["StrSection"]=22;
objet["interface"][22]="../StructureInterfaces/interface_StrSection_26455.htm";
objet["interface"]["StrWorkbench"]=23;
objet["interface"][23]="../StructureInterfaces/interface_StrWorkbench_28533.htm";
objet["interface"]["TypeESSObjectSettingAtt"]=24;
objet["interface"][24]="../StructureInterfaces/interface_TypeESSObjectSettingAtt_47372.htm";
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