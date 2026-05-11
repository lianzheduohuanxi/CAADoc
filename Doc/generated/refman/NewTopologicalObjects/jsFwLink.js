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
 objet["class"]["CATPositionPtFaceOperator"]=0;
objet["class"][0]="../NewTopologicalObjects/class_CATPositionPtFaceOperator_53871.htm";
objet["class"]["CATPositionPtVolOperator"]=1;
objet["class"][1]="../NewTopologicalObjects/class_CATPositionPtVolOperator_51950.htm";
objet["class"]["CATRecomposeShells"]=2;
objet["class"][2]="../NewTopologicalObjects/class_CATRecomposeShells_38949.htm";
objet["class"]["CATSmartBodyDuplicator"]=3;
objet["class"][3]="../NewTopologicalObjects/class_CATSmartBodyDuplicator_47130.htm";
objet["class"]["CATTopCAACompliantJournalChecker"]=4;
objet["class"][4]="../NewTopologicalObjects/class_CATTopCAACompliantJournalChecker_73067.htm";
objet["class"]["CATTopEdgePropagation"]=5;
objet["class"][5]="../NewTopologicalObjects/class_CATTopEdgePropagation_44725.htm";
objet["class"]["CATTopMultiResult"]=6;
objet["class"][6]="../NewTopologicalObjects/class_CATTopMultiResult_37372.htm";
objet["class"]["CATTopOperator"]=7;
objet["class"][7]="../NewTopologicalObjects/class_CATTopOperator_32562.htm";
objet["class"]["CATTopPositionPtFaceOperator"]=8;
objet["class"][8]="../NewTopologicalObjects/class_CATTopPositionPtFaceOperator_61907.htm";
objet["class"]["CATTopPropagationEdge"]=9;
objet["class"][9]="../NewTopologicalObjects/class_CATTopPropagationEdge_44204.htm";
objet["class"]["CATTopRelimitByVolume"]=10;
objet["class"][10]="../NewTopologicalObjects/class_CATTopRelimitByVolume_44706.htm";
objet["class"]["CATTopSewSkin"]=11;
objet["class"][11]="../NewTopologicalObjects/class_CATTopSewSkin_30859.htm";
objet["function"]["CATCheckTopology"]=0;
objet["function"][0]="../NewTopologicalObjects/function_CATCheckTopology_111133.htm";
objet["function"]["CATCreatePositionPtFaceOperator"]=1;
objet["function"][1]="../NewTopologicalObjects/_function_CATCreatePositionPtFaceOperator.htm";
objet["function"]["CATCreatePositionPtVolOperator"]=2;
objet["function"][2]="../NewTopologicalObjects/function_CATCreatePositionPtVolOperator_247835.htm";
objet["function"]["CATCreateRecomposeShells"]=3;
objet["function"][3]="../NewTopologicalObjects/function_CATCreateRecomposeShells_132804.htm";
objet["function"]["CATCreateSewSkin"]=4;
objet["function"][4]="../NewTopologicalObjects/function_CATCreateSewSkin_137687.htm";
objet["function"]["CATCreateTopClashOperator"]=5;
objet["function"][5]="../NewTopologicalObjects/function_CATCreateTopClashOperator_167606.htm";
objet["function"]["CATCreateTopEdgePropagation"]=6;
objet["function"][6]="../NewTopologicalObjects/function_CATCreateTopEdgePropagation_173789.htm";
objet["function"]["CATCreateTopPositionPtFaceOperator"]=7;
objet["function"][7]="../NewTopologicalObjects/function_CATCreateTopPositionPtFaceOperator_257717.htm";
objet["interface"]["CATTopClashOperator"]=0;
objet["interface"][0]="../NewTopologicalObjects/interface_CATTopClashOperator_43378.htm";
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