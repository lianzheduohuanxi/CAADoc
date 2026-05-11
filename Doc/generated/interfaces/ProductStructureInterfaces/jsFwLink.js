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
 objet["enum"]["CatFileType"]=0;
objet["enum"][0]="../ProductStructureInterfaces/enum_CatFileType_40640.htm";
objet["enum"]["CatProductSource"]=1;
objet["enum"][1]="../ProductStructureInterfaces/enum_CatProductSource_47634.htm";
objet["enum"]["CatRepType"]=2;
objet["enum"][2]="../ProductStructureInterfaces/enum_CatRepType_39656.htm";
objet["enum"]["CatWorkModeType"]=3;
objet["enum"][3]="../ProductStructureInterfaces/enum_CatWorkModeType_45790.htm";
objet["interface"]["Analyze"]=0;
objet["interface"][0]="../ProductStructureInterfaces/interface_Analyze_40312.htm";
objet["interface"]["AssemblyConvertor"]=1;
objet["interface"][1]="../ProductStructureInterfaces/interface_AssemblyConvertor_52793.htm";
objet["interface"]["Product"]=2;
objet["interface"][2]="../ProductStructureInterfaces/interface_Product_40279.htm";
objet["interface"]["ProductDocument"]=3;
objet["interface"][3]="../ProductStructureInterfaces/interface_ProductDocument_49169.htm";
objet["interface"]["Products"]=4;
objet["interface"][4]="../ProductStructureInterfaces/interface_Products_41084.htm";
objet["interface"]["Publication"]=5;
objet["interface"][5]="../ProductStructureInterfaces/interface_Publication_43869.htm";
objet["interface"]["Publications"]=6;
objet["interface"][6]="../ProductStructureInterfaces/interface_Publications_45134.htm";
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