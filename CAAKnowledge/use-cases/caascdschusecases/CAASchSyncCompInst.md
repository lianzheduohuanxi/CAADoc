---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CAASCH_SyncCompInst", "CATIA", "CAAScrJavaScript", "CAAScdSchUseCases", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASchSyncCompInst_01", "CAASchSyncCompInst", "CAASchSyncCompInstSource", "CATIASchComponent", "CATIASchUpdateInstances"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchSyncCompInst.htmmd"
converted: "2026-05-11T11:27:02.663875"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

         Then, the SchUpdateInstances interface is requested on the schematic root. This
         interface provides a method for updating component instances.
         

             
         
         

             The SchematicRoot interface provides the GetRefComponents method to find 
     a list of all the Schematic eference components in the model. The macro 
     takes the first one in the list and specifically requests for the 
     SchComponent interface.
     
     

#### Update component instances
     

The macro calls UpdateAllInstancesFromReference method of SchUpdateInstance interface
         to update all the component instances for the specified reference component.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to update component instances after the changes in the corresponding
     catalog reference. A message logging the status of the critical steps is 
 displayed at the end of the use case.
 

 ![](images/CAASchSyncCompInst_01.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2007, Dassault Systmes. All rights reserved.*