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
 objet["collection"]["CATLISTV(CATICst_var)"]=0;
objet["collection"][0]="../ConstraintModelerInterfaces/class_CATLISTV(CATICst_var)_55744.htm";
objet["enum"]["CATFeatureType"]=0;
objet["enum"][0]="../ConstraintModelerInterfaces/enum_CATFeatureType_46678.htm";
objet["interface"]["CATIAncestry"]=0;
objet["interface"][0]="../ConstraintModelerInterfaces/interface_CATIAncestry_47203.htm";
objet["interface"]["CATIBloc"]=1;
objet["interface"][1]="../ConstraintModelerInterfaces/interface_CATIBloc_42820.htm";
objet["interface"]["CATIBlock"]=2;
objet["interface"][2]="../ConstraintModelerInterfaces/interface_CATIBlock_43676.htm";
objet["interface"]["CATICst"]=3;
objet["interface"][3]="../ConstraintModelerInterfaces/interface_CATICst_42196.htm";
objet["interface"]["CATICstData"]=4;
objet["interface"][4]="../ConstraintModelerInterfaces/interface_CATICstData_45462.htm";
objet["interface"]["CATIDimCst2"]=5;
objet["interface"][5]="../ConstraintModelerInterfaces/interface_CATIDimCst2_45041.htm";
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