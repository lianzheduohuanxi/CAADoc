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
 objet["enum"]["CATFunctOrientationDirection"]=0;
objet["enum"][0]="../CATFunctSystemItf/enum_CATFunctOrientationDirection_54449.htm";
objet["interface"]["FunctActionsGroup"]=0;
objet["interface"][0]="../CATFunctSystemItf/interface_FunctActionsGroup_32231.htm";
objet["interface"]["FunctActionsGroups"]=1;
objet["interface"][1]="../CATFunctSystemItf/interface_FunctActionsGroups_34186.htm";
objet["interface"]["FunctAssociation"]=2;
objet["interface"][2]="../CATFunctSystemItf/interface_FunctAssociation_30538.htm";
objet["interface"]["FunctAssociations"]=3;
objet["interface"][3]="../CATFunctSystemItf/interface_FunctAssociations_32378.htm";
objet["interface"]["FunctFacetManagers"]=4;
objet["interface"][4]="../CATFunctSystemItf/interface_FunctFacetManagers_33492.htm";
objet["interface"]["FunctGenScriptMgr"]=5;
objet["interface"][5]="../CATFunctSystemItf/interface_FunctGenScriptMgr_31741.htm";
objet["interface"]["FunctMultiRepMgr"]=6;
objet["interface"][6]="../CATFunctSystemItf/interface_FunctMultiRepMgr_30005.htm";
objet["interface"]["FunctNodeGraphLayout"]=7;
objet["interface"][7]="../CATFunctSystemItf/interface_FunctNodeGraphLayout_37619.htm";
objet["interface"]["FunctScript"]=8;
objet["interface"][8]="../CATFunctSystemItf/interface_FunctScript_23676.htm";
objet["interface"]["FunctScripts"]=9;
objet["interface"][9]="../CATFunctSystemItf/interface_FunctScripts_24941.htm";
objet["interface"]["FunctionalAction"]=10;
objet["interface"][10]="../CATFunctSystemItf/interface_FunctionalAction_30270.htm";
objet["interface"]["FunctionalActions"]=11;
objet["interface"][11]="../CATFunctSystemItf/interface_FunctionalActions_32110.htm";
objet["interface"]["FunctionalDescription"]=12;
objet["interface"][12]="../CATFunctSystemItf/interface_FunctionalDescription_40162.htm";
objet["interface"]["FunctionalDocument"]=13;
objet["interface"][13]="../CATFunctSystemItf/interface_FunctionalDocument_33953.htm";
objet["interface"]["FunctionalElement"]=14;
objet["interface"][14]="../CATFunctSystemItf/interface_FunctionalElement_31997.htm";
objet["interface"]["FunctionalFacet"]=15;
objet["interface"][15]="../CATFunctSystemItf/interface_FunctionalFacet_28462.htm";
objet["interface"]["FunctionalFacetMgr"]=16;
objet["interface"][16]="../CATFunctSystemItf/interface_FunctionalFacetMgr_33203.htm";
objet["interface"]["FunctionalObject"]=17;
objet["interface"][17]="../CATFunctSystemItf/interface_FunctionalObject_30149.htm";
objet["interface"]["FunctionalObjectProxy"]=18;
objet["interface"][18]="../CATFunctSystemItf/interface_FunctionalObjectProxy_40065.htm";
objet["interface"]["FunctionalObjects"]=19;
objet["interface"][19]="../CATFunctSystemItf/interface_FunctionalObjects_31989.htm";
objet["interface"]["FunctionalPosition"]=20;
objet["interface"][20]="../CATFunctSystemItf/interface_FunctionalPosition_34181.htm";
objet["interface"]["FunctionalSystemSettingAtt"]=21;
objet["interface"][21]="../CATFunctSystemItf/interface_FunctionalSystemSettingAtt_51860.htm";
objet["interface"]["FunctionalVariant"]=22;
objet["interface"][22]="../CATFunctSystemItf/interface_FunctionalVariant_32094.htm";
objet["interface"]["FunctionalVariants"]=23;
objet["interface"][23]="../CATFunctSystemItf/interface_FunctionalVariants_34049.htm";
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