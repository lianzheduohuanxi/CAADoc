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
 objet["interface"]["EndCutESSObjectSettingAtt"]=0;
objet["interface"][0]="../CATStrFunctionalInterfaces/interface_EndCutESSObjectSettingAtt_67811.htm";
objet["interface"]["SddProduct"]=1;
objet["interface"][1]="../CATStrFunctionalInterfaces/interface_SddProduct_42258.htm";
objet["interface"]["SfdProduct"]=2;
objet["interface"][2]="../CATStrFunctionalInterfaces/interface_SfdProduct_42260.htm";
objet["interface"]["SfmConnectionParameters"]=3;
objet["interface"][3]="../CATStrFunctionalInterfaces/interface_SfmConnectionParameters_64240.htm";
objet["interface"]["SfmEndcut"]=4;
objet["interface"][4]="../CATStrFunctionalInterfaces/interface_SfmEndcut_41260.htm";
objet["interface"]["SfmEndcutManager"]=5;
objet["interface"][5]="../CATStrFunctionalInterfaces/interface_SfmEndcutManager_49760.htm";
objet["interface"]["SfmFactory"]=6;
objet["interface"][6]="../CATStrFunctionalInterfaces/interface_SfmFactory_42339.htm";
objet["interface"]["SfmFunctionFactory"]=7;
objet["interface"][7]="../CATStrFunctionalInterfaces/interface_SfmFunctionFactory_53736.htm";
objet["interface"]["SfmManager"]=8;
objet["interface"][8]="../CATStrFunctionalInterfaces/interface_SfmManager_42078.htm";
objet["interface"]["SfmMember"]=9;
objet["interface"][9]="../CATStrFunctionalInterfaces/interface_SfmMember_41159.htm";
objet["interface"]["SfmMember2Points"]=10;
objet["interface"][10]="../CATStrFunctionalInterfaces/interface_SfmMember2Points_49669.htm";
objet["interface"]["SfmMemberCurve"]=11;
objet["interface"][11]="../CATStrFunctionalInterfaces/interface_SfmMemberCurve_46915.htm";
objet["interface"]["SfmMemberPlane2Curves"]=12;
objet["interface"][12]="../CATStrFunctionalInterfaces/interface_SfmMemberPlane2Curves_58517.htm";
objet["interface"]["SfmMemberPointLength"]=13;
objet["interface"][13]="../CATStrFunctionalInterfaces/interface_SfmMemberPointLength_57126.htm";
objet["interface"]["SfmMemberPointUpToLimit"]=14;
objet["interface"][14]="../CATStrFunctionalInterfaces/interface_SfmMemberPointUpToLimit_63373.htm";
objet["interface"]["SfmMemberSurfSurf"]=15;
objet["interface"][15]="../CATStrFunctionalInterfaces/interface_SfmMemberSurfSurf_51613.htm";
objet["interface"]["SfmObject"]=16;
objet["interface"][16]="../CATStrFunctionalInterfaces/interface_SfmObject_41158.htm";
objet["interface"]["SfmObjectExt"]=17;
objet["interface"][17]="../CATStrFunctionalInterfaces/interface_SfmObjectExt_44255.htm";
objet["interface"]["SfmOpening"]=18;
objet["interface"][18]="../CATStrFunctionalInterfaces/interface_SfmOpening_42164.htm";
objet["interface"]["SfmOpeningContoursMgr"]=19;
objet["interface"][19]="../CATStrFunctionalInterfaces/interface_SfmOpeningContoursMgr_59594.htm";
objet["interface"]["SfmOperationFactory"]=20;
objet["interface"][20]="../CATStrFunctionalInterfaces/interface_SfmOperationFactory_55637.htm";
objet["interface"]["SfmPositioningStrategyManager"]=21;
objet["interface"][21]="../CATStrFunctionalInterfaces/interface_SfmPositioningStrategyManager_79796.htm";
objet["interface"]["SfmProfile"]=22;
objet["interface"][22]="../CATStrFunctionalInterfaces/interface_SfmProfile_42143.htm";
objet["interface"]["SfmReferences"]=23;
objet["interface"][23]="../CATStrFunctionalInterfaces/interface_SfmReferences_45615.htm";
objet["interface"]["SfmSlot"]=24;
objet["interface"][24]="../CATStrFunctionalInterfaces/interface_SfmSlot_39704.htm";
objet["interface"]["SfmSlots"]=25;
objet["interface"][25]="../CATStrFunctionalInterfaces/interface_SfmSlots_40509.htm";
objet["interface"]["SfmSplitPlate"]=26;
objet["interface"][26]="../CATStrFunctionalInterfaces/interface_SfmSplitPlate_45521.htm";
objet["interface"]["SfmSplitPlates"]=27;
objet["interface"][27]="../CATStrFunctionalInterfaces/interface_SfmSplitPlates_47016.htm";
objet["interface"]["SfmStandardContourParameters"]=28;
objet["interface"][28]="../CATStrFunctionalInterfaces/interface_SfmStandardContourParameters_77429.htm";
objet["interface"]["SfmStandardOpening"]=29;
objet["interface"][29]="../CATStrFunctionalInterfaces/interface_SfmStandardOpening_53284.htm";
objet["interface"]["SfmStandardPosStrategyParameters"]=30;
objet["interface"][30]="../CATStrFunctionalInterfaces/interface_SfmStandardPosStrategyParameters_89697.htm";
objet["interface"]["SfmStiffener"]=31;
objet["interface"][31]="../CATStrFunctionalInterfaces/interface_SfmStiffener_44398.htm";
objet["interface"]["SfmStiffenerOnFreeEdge"]=32;
objet["interface"][32]="../CATStrFunctionalInterfaces/interface_SfmStiffenerOnFreeEdge_60122.htm";
objet["interface"]["SfmSuperPlate"]=33;
objet["interface"][33]="../CATStrFunctionalInterfaces/interface_SfmSuperPlate_45523.htm";
objet["interface"]["SfmWeld"]=34;
objet["interface"][34]="../CATStrFunctionalInterfaces/interface_SfmWeld_39577.htm";
objet["interface"]["SfmWelds"]=35;
objet["interface"][35]="../CATStrFunctionalInterfaces/interface_SfmWelds_40382.htm";
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