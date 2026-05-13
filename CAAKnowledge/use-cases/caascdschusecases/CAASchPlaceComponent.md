---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CAASchPlaceComponent_01", "CATIA", "CAAScrJavaScript", "CAAScdSchUseCases", "CATIASchComponent2", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASCH_Sample", "CAASchPlaceComponentSource", "CAASCH_RouteForPlacement2", "CAASchPlaceComponent", "CAASCHEDUApp", "CAASchAppBase", "CAADoc", "CAASchAppUtilities", "CAASchPlaceComponent_02"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchPlaceComponent.htmmd"
converted: "2026-05-11T11:27:02.629767"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.
     
     

#### Place a 
     Schematic component instance in free space (not connected to any other 
     object).
     

The SchematicRoot interface provides the GetCompSymbolFromCatalog method 
     to retrieve the graphical representation of a specific Schematic component 
     reference by name. In this case, the "Blocking Valve" is chosen. Based on 
     this graphical representation, the macro calls the GetSchObjOwner to obtain 
     the Schematic component reference.
     
     

Method PlaceInSpace is then called to create a new instance of the 
     "Blocking Valve" reference component in the design document. Note that the 
     placement position and orientation are defined by a 6-words double-array 
     (db6Array) which is an input to the method.
     
     

#### Place a 
     Schematic component instance and connect it to instance created in previous 
     step
     

As in previous step, the macro find the reference component from the 
     catalog by the name of the graphical representation of the component. In 
     this case, the name is "Control Valve"
     
     

Unlike previous step, instead of specifying a placement position, the 
     macro obtains the SchComponent interface from the "Blocking Valve" 
     component instance (created in previous step) and creates an Control Valve 
     component instance by calling the PlaceOnComponentWithInfo method of the 
     interface. 
     

In the comment section of the following code segments, instance A refers 
     to "Blocking Valve" instance that was created in previous step and instance 
     B refers to "Control Valve" instance the macro is about to create.
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to create component instances. A message logging the 
 status of the critical steps is displayed at the end of the use case.
 

 ![](images/CAASchPlaceComponent_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*

 

```vbscript
...
    ' ------------------------------------------------------------------------- 
    ' Open the schematic document 
```vbscript
    Dim sCtlgFilePath
    sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_Sample.catalog")
```

```vbscript
    Dim objSchCtlgDoc As Document
    Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)
```
```

```vbscript
' Open main schematic P&amp;ID design document (for new component instances created here)
```vbscript
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online/CAAScdSchUseCases/samples/CAASCH_RouteForPlacement2.CATProduct")
```

```vbscript
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)
    ...
```
```