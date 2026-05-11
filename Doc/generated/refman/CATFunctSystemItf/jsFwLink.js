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
objet["interface"]["CATIFsyFunctionalSystemSettingAtt"]=0;
objet["interface"][0]="../CATFunctSystemItf/interface_CATIFsyFunctionalSystemSettingAtt_72926.htm";
objet["interface"]["CATIFunctAction"]=1;
objet["interface"][1]="../CATFunctSystemItf/interface_CATIFunctAction_28455.htm";
objet["interface"]["CATIFunctActions"]=2;
objet["interface"][2]="../CATFunctSystemItf/interface_CATIFunctActions_30180.htm";
objet["interface"]["CATIFunctActionsGroup"]=3;
objet["interface"][3]="../CATFunctSystemItf/interface_CATIFunctActionsGroup_39715.htm";
objet["interface"]["CATIFunctActionsGroups"]=4;
objet["interface"][4]="../CATFunctSystemItf/interface_CATIFunctActionsGroups_42130.htm";
objet["interface"]["CATIFunctAssociation"]=5;
objet["interface"][5]="../CATFunctSystemItf/interface_CATIFunctAssociation_37634.htm";
objet["interface"]["CATIFunctAssociations"]=6;
objet["interface"][6]="../CATFunctSystemItf/interface_CATIFunctAssociations_39934.htm";
objet["interface"]["CATIFunctDescription"]=7;
objet["interface"][7]="../CATFunctSystemItf/interface_CATIFunctDescription_37797.htm";
objet["interface"]["CATIFunctDocument"]=8;
objet["interface"][8]="../CATFunctSystemItf/interface_CATIFunctDocument_31913.htm";
objet["interface"]["CATIFunctElement"]=9;
objet["interface"][9]="../CATFunctSystemItf/interface_CATIFunctElement_30074.htm";
objet["interface"]["CATIFunctFacet"]=10;
objet["interface"][10]="../CATFunctSystemItf/interface_CATIFunctFacet_26770.htm";
objet["interface"]["CATIFunctFacetManagers"]=11;
objet["interface"][11]="../CATFunctSystemItf/interface_CATIFunctFacetManagers_41180.htm";
objet["interface"]["CATIFunctFacetMgr"]=12;
objet["interface"][12]="../CATFunctSystemItf/interface_CATIFunctFacetMgr_31217.htm";
objet["interface"]["CATIFunctGenScriptMgr"]=13;
objet["interface"][13]="../CATFunctSystemItf/interface_CATIFunctGenScriptMgr_39061.htm";
objet["interface"]["CATIFunctMultiRepMgr"]=14;
objet["interface"][14]="../CATFunctSystemItf/interface_CATIFunctMultiRepMgr_36953.htm";
objet["interface"]["CATIFunctNodeGraphLayout"]=15;
objet["interface"][15]="../CATFunctSystemItf/interface_CATIFunctNodeGraphLayout_46223.htm";
objet["interface"]["CATIFunctObject"]=16;
objet["interface"][16]="../CATFunctSystemItf/interface_CATIFunctObject_28341.htm";
objet["interface"]["CATIFunctObjectProxy"]=17;
objet["interface"][17]="../CATFunctSystemItf/interface_CATIFunctObjectProxy_37711.htm";
objet["interface"]["CATIFunctObjects"]=18;
objet["interface"][18]="../CATFunctSystemItf/interface_CATIFunctObjects_30066.htm";
objet["interface"]["CATIFunctPosition"]=19;
objet["interface"][19]="../CATFunctSystemItf/interface_CATIFunctPosition_32119.htm";
objet["interface"]["CATIFunctScript"]=20;
objet["interface"][20]="../CATFunctSystemItf/interface_CATIFunctScript_28692.htm";
objet["interface"]["CATIFunctScripts"]=21;
objet["interface"][21]="../CATFunctSystemItf/interface_CATIFunctScripts_30417.htm";
objet["interface"]["CATIFunctVariant"]=22;
objet["interface"][22]="../CATFunctSystemItf/interface_CATIFunctVariant_30160.htm";
objet["interface"]["CATIFunctVariants"]=23;
objet["interface"][23]="../CATFunctSystemItf/interface_CATIFunctVariants_32000.htm";
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