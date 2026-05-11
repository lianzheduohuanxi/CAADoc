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
 objet["class"]["CATDECPartToPartConvertor"]=0;
objet["class"][0]="../CATDataExchControlAlgo/class_CATDECPartToPartConvertor_55743.htm";
objet["class"]["CATDECProductToPartConvertor"]=1;
objet["class"][1]="../CATDataExchControlAlgo/class_CATDECProductToPartConvertor_64037.htm";
objet["class"]["CATDECProductToProductConvertor"]=2;
objet["class"][2]="../CATDataExchControlAlgo/class_CATDECProductToProductConvertor_73495.htm";
objet["function"]["CATCreatePartToPartConvertor"]=0;
objet["function"][0]="../CATDataExchControlAlgo/function_CATCreatePartToPartConvertor_117448.htm";
objet["function"]["CATCreateProductToPartConvertor"]=1;
objet["function"][1]="../CATDataExchControlAlgo/function_CATCreateProductToPartConvertor_135578.htm";
objet["function"]["CATCreateProductToProductConvertor"]=2;
objet["function"][2]="../CATDataExchControlAlgo/function_CATCreateProductToProductConvertor_156036.htm";
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