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
 objet["enum"]["SWKPostureSpec"]=0;
objet["enum"][0]="../DNBHumanModelingInterfaces/enum_SWKPostureSpec_43504.htm";
objet["interface"]["SWKAnthro"]=0;
objet["interface"][0]="../DNBHumanModelingInterfaces/interface_SWKAnthro_40896.htm";
objet["interface"]["SWKAnthroVariable"]=1;
objet["interface"][1]="../DNBHumanModelingInterfaces/interface_SWKAnthroVariable_51023.htm";
objet["interface"]["SWKBody"]=2;
objet["interface"][2]="../DNBHumanModelingInterfaces/interface_SWKBody_39239.htm";
objet["interface"]["SWKBodyElement"]=3;
objet["interface"][3]="../DNBHumanModelingInterfaces/interface_SWKBodyElement_46524.htm";
objet["interface"]["SWKCenterOfGravity"]=4;
objet["interface"][4]="../DNBHumanModelingInterfaces/interface_SWKCenterOfGravity_53122.htm";
objet["interface"]["SWKDOF"]=5;
objet["interface"][5]="../DNBHumanModelingInterfaces/interface_SWKDOF_38241.htm";
objet["interface"]["SWKErgo"]=6;
objet["interface"][6]="../DNBHumanModelingInterfaces/interface_SWKErgo_39215.htm";
objet["interface"]["SWKErgoCarry"]=7;
objet["interface"][7]="../DNBHumanModelingInterfaces/interface_SWKErgoCarry_43957.htm";
objet["interface"]["SWKErgoLiftLower"]=8;
objet["interface"][8]="../DNBHumanModelingInterfaces/interface_SWKErgoLiftLower_49504.htm";
objet["interface"]["SWKErgoPushPull"]=9;
objet["interface"][9]="../DNBHumanModelingInterfaces/interface_SWKErgoPushPull_47986.htm";
objet["interface"]["SWKErgoRULA"]=10;
objet["interface"][10]="../DNBHumanModelingInterfaces/interface_SWKErgoRULA_41803.htm";
objet["interface"]["SWKIKConstraint"]=11;
objet["interface"][11]="../DNBHumanModelingInterfaces/interface_SWKIKConstraint_48146.htm";
objet["interface"]["SWKIKManager"]=12;
objet["interface"][12]="../DNBHumanModelingInterfaces/interface_SWKIKManager_43594.htm";
objet["interface"]["SWKLineOfSight"]=13;
objet["interface"][13]="../DNBHumanModelingInterfaces/interface_SWKLineOfSight_46230.htm";
objet["interface"]["SWKLineOfSightNode"]=14;
objet["interface"][14]="../DNBHumanModelingInterfaces/interface_SWKLineOfSightNode_52304.htm";
objet["interface"]["SWKManikin"]=15;
objet["interface"][15]="../DNBHumanModelingInterfaces/interface_SWKManikin_41749.htm";
objet["interface"]["SWKManikinPart"]=16;
objet["interface"][16]="../DNBHumanModelingInterfaces/interface_SWKManikinPart_46492.htm";
objet["interface"]["SWKNode"]=17;
objet["interface"][17]="../DNBHumanModelingInterfaces/interface_SWKNode_39155.htm";
objet["interface"]["SWKSegment"]=18;
objet["interface"][18]="../DNBHumanModelingInterfaces/interface_SWKSegment_41824.htm";
objet["interface"]["SWKSegmentNode"]=19;
objet["interface"][19]="../DNBHumanModelingInterfaces/interface_SWKSegmentNode_46338.htm";
objet["interface"]["SWKVision"]=20;
objet["interface"][20]="../DNBHumanModelingInterfaces/interface_SWKVision_40911.htm";
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