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
 objet["interface"]["Dressup"]=0;
objet["interface"][0]="../KinematicsInterfaces/interface_Dressup_25888.htm";
objet["interface"]["Dressups"]=1;
objet["interface"][1]="../KinematicsInterfaces/interface_Dressups_26693.htm";
objet["interface"]["Joint"]=2;
objet["interface"][2]="../KinematicsInterfaces/interface_Joint_24625.htm";
objet["interface"]["Joints"]=3;
objet["interface"][3]="../KinematicsInterfaces/interface_Joints_25200.htm";
objet["interface"]["KinematicsWorkbench"]=4;
objet["interface"][4]="../KinematicsInterfaces/interface_KinematicsWorkbench_41369.htm";
objet["interface"]["Mechanism"]=5;
objet["interface"][5]="../KinematicsInterfaces/interface_Mechanism_27366.htm";
objet["interface"]["MechanismCommand"]=6;
objet["interface"][6]="../KinematicsInterfaces/interface_MechanismCommand_35887.htm";
objet["interface"]["MechanismCommands"]=7;
objet["interface"][7]="../KinematicsInterfaces/interface_MechanismCommands_37727.htm";
objet["interface"]["Mechanisms"]=8;
objet["interface"][8]="../KinematicsInterfaces/interface_Mechanisms_28401.htm";
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