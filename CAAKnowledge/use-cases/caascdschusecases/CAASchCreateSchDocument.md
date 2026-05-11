---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAASchCreateSchDocumentSource", "CAAScdSchUseCases", "CAAScdInfUseCases", "CAASchSCH_Detail01", "CAASCH_Detail01", "CAASchCreateSchDocument", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchCreateSchDocument.htm"
converted: "2026-05-11T11:27:02.627785"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

#### Get a the current CNEXT session
     

Using the GeSchematicSession method, a handle on the SchSession 
     interface can be obtained. This interface provides a method to create a new 
     schematic document.
     
     

#### Create a new schematic document
     
     

#### Set the drawing standard of the 
     drafting viewer in the schematic document
     

A schematic document has a drafting viewer embedded in it. The drawing 
     standard of that drafting viewer can be set by calling the 
     SetDrawingStandard method. This macro also illustrates how to use the 
     GetDrawingStandard method to retrieve the drawing standard of a schematic 
     document.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to create a schematic document from the root of an 
 existing document. A message logging the status of the critical steps is 
 displayed at the end of the use case. 
 

 ![](images/CAASchCreateSchDocument.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*