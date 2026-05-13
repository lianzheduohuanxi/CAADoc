---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIA", "CAASchPlatformModeler", "CAASchInternalFlow", "CATIASchAppConnector", "CAAScrBase", "CAAScdInfUseCases", "CATIASchCompFlow", "CAASCHEDUApp", "CAASCH_Detail02", "CAAInfLauchMacro", "CAASchAppUtilities", "CAASchInternalFlow_02", "CAASchAppBase", "CATIASchComponent", "CAAScrJavaScript", "CAAScdSchUseCases", "CAASchInternalFlowSource", "CAASchInternalFlow_01", "CAADoc"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInternalFlow.htmmd"
converted: "2026-05-11T11:27:02.610339"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

The SchematicRoot interface provides the GetRefComponents method to find 
     a list of all the Schematic reference component in the model. The macro 
     takes the first one in the list and specifically requests for the 
     SchComponent interface on the first member.
     
     

#### Add an internal flow object to the 
     Schematic reference component
     

The macro calls the GetInterface method to get a handle on the reference 
     component for the SchCompFlow interface.
     
     

Next, the macro get a list of all connectors of the Schematic Component.
     
     

Method CreateListOfObject is called to create a list of connectors 
     containing the first and the second connectors. This list is used as input 
     to the AddInternalFlow method to add an internal flow object to the 
     reference component..
     
     

Similarly, the macro creates a second list of connectors containing the 
     first and the third connectors. This list is used as input to the 
     AddInternalFlow method to add the second internal flow object to the 
     reference component.
     
     

#### Query for a list of existing internal 
     flow objects of a Schematic reference component
     
     

#### Remove an internal flow objects from 
     the Schematic reference component
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to manage internal flow objects of a Schematic 
 reference component. A message logging the status of the critical steps is 
 displayed at the end of the use case.
 

 ![](images/CAASchInternalFlow_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*