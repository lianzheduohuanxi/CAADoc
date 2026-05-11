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
 objet["collection"]["CATLISTV(CATICatalogChapter_var)"]=0;
objet["collection"][0]="../ComponentsCatalogsInterfaces/class_CATLISTV(CATICatalogChapter_var)_87347.htm";
objet["collection"]["CATLISTV(CATICatalogDescription_var)"]=1;
objet["collection"][1]="../ComponentsCatalogsInterfaces/class_CATLISTV(CATICatalogDescription_var)_101852.htm";
objet["collection"]["CATLISTV(CATICatalogKeyword_var)"]=2;
objet["collection"][2]="../ComponentsCatalogsInterfaces/class_CATLISTV(CATICatalogKeyword_var)_87974.htm";
objet["collection"]["CATLISTV(CATICatalogPersistentQuery_var)"]=3;
objet["collection"][3]="../ComponentsCatalogsInterfaces/class_CATLISTV(CATICatalogPersistentQuery_var)_118181.htm";
objet["interface"]["CATICATALOGWorkshopAddin"]=0;
objet["interface"][0]="../ComponentsCatalogsInterfaces/interface_CATICATALOGWorkshopAddin_69864.htm";
objet["interface"]["CATICatalogBrowser"]=1;
objet["interface"][1]="../ComponentsCatalogsInterfaces/interface_CATICatalogBrowser_59050.htm";
objet["interface"]["CATICatalogBrowserFactory"]=2;
objet["interface"][2]="../ComponentsCatalogsInterfaces/interface_CATICatalogBrowserFactory_74537.htm";
objet["interface"]["CATICatalogChapter"]=3;
objet["interface"][3]="../ComponentsCatalogsInterfaces/interface_CATICatalogChapter_58676.htm";
objet["interface"]["CATICatalogChapterFactory"]=4;
objet["interface"][4]="../ComponentsCatalogsInterfaces/interface_CATICatalogChapterFactory_74163.htm";
objet["interface"]["CATICatalogDescription"]=5;
objet["interface"][5]="../ComponentsCatalogsInterfaces/interface_CATICatalogDescription_67316.htm";
objet["interface"]["CATICatalogEnable"]=6;
objet["interface"][6]="../ComponentsCatalogsInterfaces/interface_CATICatalogEnable_56516.htm";
objet["interface"]["CATICatalogInstantiation"]=7;
objet["interface"][7]="../ComponentsCatalogsInterfaces/interface_CATICatalogInstantiation_72227.htm";
objet["interface"]["CATICatalogKeyword"]=8;
objet["interface"][8]="../ComponentsCatalogsInterfaces/interface_CATICatalogKeyword_59033.htm";
objet["interface"]["CATICatalogLink"]=9;
objet["interface"][9]="../ComponentsCatalogsInterfaces/interface_CATICatalogLink_53592.htm";
objet["interface"]["CATICatalogPersistentQuery"]=10;
objet["interface"][10]="../ComponentsCatalogsInterfaces/interface_CATICatalogPersistentQuery_77726.htm";
objet["interface"]["CATICatalogQuery"]=11;
objet["interface"][11]="../ComponentsCatalogsInterfaces/interface_CATICatalogQuery_55587.htm";
objet["interface"]["CATICatalogQueryResult"]=12;
objet["interface"][12]="../ComponentsCatalogsInterfaces/interface_CATICatalogQueryResult_67505.htm";
objet["interface"]["CATICatalogSynchronize"]=13;
objet["interface"][13]="../ComponentsCatalogsInterfaces/interface_CATICatalogSynchronize_67556.htm";
objet["typedef"]["CATCciCatalogBrowserDisplayOptions"]=0;
objet["typedef"][0]="../ComponentsCatalogsInterfaces/typedef_CATCciCatalogBrowserDisplayOptions_100675.htm";
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