---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIA", "CAASchDeleteSource", "CAAScrJavaScript", "CAASCH_Delete01", "CAAScdSchUseCases", "CATIASchRoute", "CAASchDelete_01", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASchDelete_02", "CAASCHEDUApp", "CATIASchAppConnectable", "CAASchDelete", "CAASchAppBase", "CAADoc", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchDelete.htmmd"
converted: "2026-05-11T11:27:02.631400"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

Using the GetSchBaseFactory method, a SchBaseFact interface handle is 
     obtained. The DeleteObject method of this interface is used in the next 
     step.
     
     

#### Delete a Schematic component
     

The macro finds the component to be deleted in the private 
     FindComponentInst function. This is based on a naming convention on the 
     Schematic component. FindComponentInst returns the first instance whose 
     name has the word "delete" embedded in it. The macro calls DeleteObject to 
     delete the component.
     
     

#### Delete a Schematic route
     

The word "inserted" in the comment below is used to describe a situation 
     where a Schematic component is connected to two Schematic routes through 
     two of its connectors. These connectors must be internally connected to 
     each other by an "internal flow" object. The latter is aggregated by the 
     Schematic component. For example, the highlighted "valve" in the screen 
     shot of the current document above has been inserted into the route.
     
     

This macro uses a private FindOpenConnector function to find the 2 
     unconnected ends of the 2 routes that are connected to each ends of the 
     component before it is deleted. With these 2 ends, the Concatenate method 
     of the SchRoute interface is then called to connect the 2 route into one. 
     Note that the input SchRoute interface handle (in this case, the objRoute2) 
     will be deleted implicitly by the Concatenate method. 
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to delete Schematic objects. A message logging the 
 status of the critical steps is displayed at the end of the use case. 
 

![](images/CAASchDelete_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*