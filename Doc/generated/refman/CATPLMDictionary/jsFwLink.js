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
 objet["define"]["_VPMDicPRIMITIVETypeNumber"]=0;
objet["define"][0]="../CATPLMDictionary/define__VPMDicPRIMITIVETypeNumber_44758.htm";
objet["enum"]["VPMDicCONTENT"]=0;
objet["enum"][0]="../CATPLMDictionary/enum_VPMDicCONTENT_19319.htm";
objet["enum"]["VPMDicPERSISTENT"]=1;
objet["enum"][1]="../CATPLMDictionary/enum_VPMDicPERSISTENT_22694.htm";
objet["enum"]["VPMDicPRIMITIVEType"]=2;
objet["enum"][2]="../CATPLMDictionary/enum_VPMDicPRIMITIVEType_28291.htm";
objet["enum"]["VPMDicTYPE"]=3;
objet["enum"][3]="../CATPLMDictionary/enum_VPMDicTYPE_16816.htm";
objet["enum"]["VPMDicVISIBILITY"]=4;
objet["enum"][4]="../CATPLMDictionary/enum_VPMDicVISIBILITY_22611.htm";
objet["function"]["GetVPMIDicMgr"]=0;
objet["function"][0]="../CATPLMDictionary/function_GetVPMIDicMgr_38816.htm";
objet["interface"]["VPMIDicElement"]=0;
objet["interface"][0]="../CATPLMDictionary/interface_VPMIDicElement_25227.htm";
objet["interface"]["VPMIDicMgr"]=1;
objet["interface"][1]="../CATPLMDictionary/interface_VPMIDicMgr_20331.htm";
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