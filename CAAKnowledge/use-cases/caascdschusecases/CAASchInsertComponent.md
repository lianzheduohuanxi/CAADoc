---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASchInsertComponent_02", "CAAScrBase", "CAADoc", "CAAInfLauchMacro", "CAASchAppBase", "CAASCHEDUApp", "CAASCH_RouteForPlacement", "CAASCH_Sample", "CAASchAppUtilities", "CATIASchComponent", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAASchInsertComponent_01", "CAASchInsertComponent", "CAAScdSchUseCases", "CAASchInsertComponentSource", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInsertComponent.htm"
converted: "2026-05-11T11:06:32.660662"
---

## Schematics Platform Modeler
 
 
## []Inserting a Schematic Component into a Schematic 
 Route
 
 
 
 

---

 
 
 
 ![](../CAAScrBase/images/atarget.gif)
 |[]This macro shows you how to insert a 
 Schematic component into a Schematic route.
 

The word "insert" refers to a process by which a Schematic route is 
 split at a specific location (creating a new route) and a Schematic 
 component is connected to the two routes, creating two connections. These 
 connections are created through two connectors of the schematic component. 
 These two connectors must be internally connected to each other by an 
 "internal flow" object, which is aggregated by the Schematic component.
 

This macro opens two documents: CAASCH_Sample.catalog and 
 CAASCH_RouteForPlacement.CATProduct. 
 

Notice the x-y coordinates of a point (80,50), as indicated in the 
 screen shots. They will be used later in this use case.
 

 ![](images/CAASchInsertComponent_01.jpg)
 

In this use case, two Schematic components are inserted into route using 
 two different approaches.
 
 
 ![](../CAAScrBase/images/ainfo.gif)
 |[]CAASchInsertComponent is launched in 
 CATIA [[1]]. No open document is needed.

Special 
		environment must be available to successfully run this macro:
		

			
- Prerequisites:
		
		
> 
			

				
- RADE must be installed.
				
- CAASchPlatformModeler.edu must exist in CAADoc folder.
			
		

		

			
- Setup:
		
		
> 
			

				
- Build CAASchAppBase.m and CAASchAppUtilities.m, located in 
				CAASchPlatformModeler.edu (RADE is required). 
				
- Copy generated DLLs, CAASchAppBase.dll and CAASchAppUtilities.m, respectively, to the run-time environment 
				folder "intel_a\code\bin."
				
- Copy CAASCHEDUApp.CATfct, located CAASchPlatformModeler.edu\CNext\resources\graphic, 
				to the run-time environment folder "intel_a\resources\graphic."
				
- Copy CAASchPlatformModeler.edu\CNext\code\dictionary\CAASchPlatformModeler.edu.dico 
				to the run-time environment folder "intel_a\code\dictionary."
			
		

		

 [CAASchInsertComponent.CATScript i]s 
 located in the CAAScdSchUseCases module.
 [Execute macro] (Windows 
 only).
 
 
 ![](../CAAScrBase/images/ascenari.gif)
 |[]CAASchInsertComponent includes the 
 following steps:

 
- [Prolog]
 
- [Get the Schematic 
 reference component from the catalog]
 
- [Insert an instance of the Schematic 
 reference component - approach 1]
 
- [Insert an instance of the Schematic 
 reference component - approach 2]
 
 
#### []Prolog
 

The macro first loads two documents. CAASCH_Sample.catalog and 
 CAASCH_RouteForPlacement.CATProduct.
 
 
 
```
...

 
' ------------------------------------------------------------------------- 

 
' Open the catalog document 

 Dim 
sCtlgFilePath
 sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
 "online\CAAScdSchUseCases\samples\CAASCH_Sample.catalog")

 Dim 
objSchCtlgDoc
 As 
Document

 Set 
objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)
```

 
```
' Open main schematic design document (for new component instances created here)

 Dim 
sFilePath
 sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
 "online\CAAScdSchUseCases\samples\CAASCH_RouteForPlacement.CATProduct")

 Dim 
objSchDoc
 As 
Document

 Set 
objSchDoc = CATIA.Documents.Open(sFilePath)
 
...
```

 
 
 
 

Next, the macro acquires the schematic root object from the document. 
 The schematic root is the top node of the object instance tree in a 
 schematic document. 
 
 
 
```
...

 
' Find the top node of the schematic object tree - schematic root.

 Dim 
objPrdRoot
 As 
Product

 Dim 
objSchRoot
 As 
SchematicRoot

 If 
( Not ( IsEmpty ( objSchDoc ) )
 Then

 Set 
objPrdRoot = objSchDoc.Product 

 If 
( Not ( IsEmpty ( objPrdRoot ) )
 Then

 Set 
objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")

 End If

 End If
```

 
```
...
```

 
 
 
 

The SchematicRoot interface provides a method to retrieve the graphical 
 representation of a reference component from the catalog by name. This 
 graphical representation is associated to a reference component in the 
 catalog.
 
 
 
```
...

 Dim 
objSchGRRCVCtlg
 As 
SchGRR
```

 
```
...

 If 
( Not ( IsEmpty ( objSchRoot ) ) )
 Then

 
'-----------------------------------------------------------------------

 
' Get the symbol of a component from the component catalog.

 
'-----------------------------------------------------------------------

 Set 
objSchGRRCVCtlg = objSchRoot.GetCompSymbolFromCatalog ("Control Valve",objSchCtlgDoc)
 
...
```

 
 
 
 
#### []Get the Schematic 
 reference component from the catalog
 

Given the graphical representation (symbol) from the previous step, the 
 macro calls GetSchObjOwner to get the Schematic reference component that 
 the symbol is associated with.
 
 
 |    ...

        
 '---------------------------------------------------------------------

        
 ' Get the owner of the symbol. That is, a reference component,

        
 ' in the catalog.

        
 '---------------------------------------------------------------------

         Set objSchCntblCVRef = objSchGRRCVCtlg.GetSchObjOwner

   
 ...
 
 
 

Through the GetInterface method, the macro obtains a handle on the 
 SchComponent interface, which is needed for creating an instance of the 
 Schematic reference component from the catalog.
 
 
 |    ...

         If ( Not ( IsEmpty ( objSchCntblCVRef ) ) ) Then

 

           Set objSchCompCVRef = objSchRoot.GetInterface ("CATIASchComponent",objSchCntblCVRef)

   
 ...
 
 
 
#### []Insert an instance of the Schematic 
 reference component - approach 1
 

The "insert" process includes the following.
 

 
- 
 
- 
- 

||

#### []

||

[]

---

#### []

![](images/CAASchInsertComponent_02.jpg)

[]

---

#### []
|||[]
|||
||[]

---

**