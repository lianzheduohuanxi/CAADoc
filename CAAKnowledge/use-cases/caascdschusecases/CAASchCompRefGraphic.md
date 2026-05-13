---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIASchGRR", "CATIA", "CAASchCompRefGraphic_02", "CAAScrJavaScript", "CAASchCompRefGraphic", "CAAScdSchUseCases", "CAASchCompRefGraphic_01", "CAAScdInfUseCases", "CAASCH_Detail03", "CATIASchCompGraphic", "CAAInfLauchMacro", "CAASchCompRefGraphicSource"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCompRefGraphic.htmmd"
converted: "2026-05-11T11:27:02.648576"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document. 
     
     

#### Find a schematic reference 
     component in the model
     

Using the GetRefComponents method, a list of existing schematic 
     reference component in the model can be obtained. Note that the output of 
     this method is a list of objects. The member of this list can be retrieved 
     using the Item method. The second argument of this method specifies a 
     particular interface to be returned on this member reference component. In 
     this case it is the SchCompGraphic interface.
     
     

#### Add a graphical 
     representation to the schematic reference component
     

The macro calls GetComponentSymbol to find a symbol that has not been 
     associated with any reference component. Using the symbol, it then calls 
     AddGraphicalRepresentation to add this symbol to the reference component. 
     This method is called a second time to add the third symbol. At this point, 
     the reference component has three graphical representations.
     
     

#### Query for a list of 
     graphical representation of the schematic reference component
     

ListGraphicalRepresentation returns a list of graphical representations. 
     This list should contains three members.
     
     

#### Remove a graphical 
     representation from the schematic reference component
     

The macro finds the first member of the list of graphical 
     representations obtained from previous step and call 
     RemoveGraphicalRepresentation to remove that symbol from the reference 
     component.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to add, remove and query for a list of graphical 
 representations of a schematic reference component. A message logging the 
 status of the critical steps is displayed at the end of the use case. 
 

 ![](images/CAASchCompRefGraphic_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*