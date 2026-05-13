---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdSchUseCases", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASchQueryConnectivity_01", "CAASchQueryConnectivity", "CAASCHEDUApp", "CAASchQueryConnectivitySource", "CAASCH_CompRoute01", "CATIASchAppConnectable", "CAASchAppBase", "CAADoc", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryConnectivity.htmmd"
converted: "2026-05-11T11:27:02.656223"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

#### Get a list of Schematic 
     component instances and Schematic route instances in the document
     
     

#### Query for lists of 
     connected objects
     

For each member in the output list of component instants, the macro uses 
     the AppListConnectables to find a list of Schematic component or route 
     instances that are connected to the component instance member.
     
     

For each member in the output list of route instants, the macro uses the 
     AppListConnectables to find a list of Schematic component or route 
     instances that are connected to the route instance member.
     
     

This macro provides the internal GenerateALine subroutine to report 
     connected objects. It uses the GetPosition method of the SchCntrLocation 
     interface to obtain the x-y coordinates of the connection points. 
     SchCntrLocation is found based on the output list of connectors from the 
     AppListConnectable method.
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to query the connectivity of Schematic objects in a 
 Schematic document. A message logging the status of the critical steps is 
 displayed at the end of the use case.
 

 ![](images/CAASchQueryConnectivity_01.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*