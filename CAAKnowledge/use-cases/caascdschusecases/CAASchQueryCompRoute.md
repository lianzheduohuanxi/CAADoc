---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CAASchQueryCompRoute", "CAADoc", "CAAInfLauchMacro", "CAASchAppBase", "CAASCHEDUApp", "CAASchQueryCompRoute_01", "CAASchAppUtilities", "CATIASchCntrLocation", "CAAScdInfUseCases", "CAASchPlatformModeler", "CAASchQueryCompRouteSource", "CAASchQueryCompRoute_02", "CAASCH_CompRoute01", "CAAScdSchUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryCompRoute.htm"
converted: "2026-05-11T11:06:32.551642"
---

## Schematics Platform Modeler
 
 
## []Querying Schematic Document Content
 
 
 
 

---

 
 
 
 ![](../CAAScrBase/images/atarget.gif)
 |[]This macro shows you how to query for 
 information from a Schematic design document.
 

The information includes the following:
 

 
- A list of all Schematic components (references or instances) in the 
 document.
 
- A list of all Schematic routes in the document.
 
- The placement matrix of a specific Schematic component instance.
 
- The defining route points of the route path of a specific Schematic 
 route instance.
 
- The position of a connector.
 
 

This macro open the CAASCH_CompRoute01.CATProduct document for querying 
 information.
 

 ![](images/CAASchQueryCompRoute_01.jpg)
 
 
 ![](../CAAScrBase/images/ainfo.gif)
 |[]CAASchQueryCompRoute is launched in CATIA 
 [[1]]. No open document is needed.

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
			
		

		

 [CAASchQueryCompRoute.CATScript ]
 is located in the CAAScdSchUseCases module.
 [Execute macro] (windows 
 only).
 
 
 ![](../CAAScrBase/images/ascenari.gif)
 |[]CAASchQueryCompRoute includes the 
 following steps:

 
- [Prolog]
 
- [Query for the name of the 
 current document in the session.]
 
- [Query for a list of 
 Schematic reference components in the document.]
 
- [Query for a list of 
 Schematic component instances in the document.]
 
- [Find the positioning matrix 
 of specific graphical image of a Schematic component instance.]
 
- [Query for a list of all the 
 connectors of a Schematic component instance.]
 
- [Query for a list of all the 
 Schematic route instances in the document.]
 
- [Query for a list of route 
 path definition points.]
 
 
#### []Prolog
 

The macro first loads the document: CAASCH_CompRoute01.CATProduct.
 
 
 |    ...

   
 ' Open the schematic document 

    Dim sFilePath

    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _

            "online\CAAScdSchUseCases\samples\CAASCH_CompRoute01.CATProduct")

 

    Dim objSchDoc As Document

    Set objSchDoc = CATIA.Documents.Open(sFilePath)

   
 ...
 
 
 

Next, the macro acquires the schematic root object from the document. 
 The schematic root is the top node of the object instance tree in a 
 schematic document.  
 
 
 |    ...

   
 ' Find the top node of the schematic object tree - schematic root.

    Dim objPrdRoot As Product

    Dim objSchRoot As SchematicRoot

    If ( Not ( objSchDoc Is Nothing ) ) Then

      Set objPrdRoot = objSchDoc.Product
 

      If ( Not ( objPrdRoot Is Nothing ) ) Then

        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")

      End If

    End If

   
 ...
 
 
 
#### []Query for the name of the 
 current document in the session
 

The SchSession interface provides the GetCurrentDocument method to 
 return the name of the current document.
 
 
 |    ...

       Set objSchSession = objSchRoot.GetSchematicSession

 

      

 '-----------------------------------------------------------------------

      
 '| Query the name of the current document 
 

      
 '-----------------------------------------------------------------------

       If ( Not ( objSchSession Is Nothing ) ) Then

          Set objCurDoc = objSchSession.GetCurrentDocument

   
 ...
 
 
 
#### []Query for a list of 
 Schematic reference components in the document
 

The SchematicRoot interface provides the GetRefComponents method to 
 return a list of Schematic component references in the document.
 
 
 |    ...

   
 ' ------------------------------------------------------------------------- 
 

   
 ' |  List schematic component references in the model

   
 ' ------------------------------------------------------------------------- 
 

    Set objSchLCompRefs = objSchRoot.GetRefComponents

   
 ...
 
 
 
#### []Query for a list of 
 Schematic component instances in the document
 

The SchematicRoot interface provides the GetComponents method to return 
 a list of Schematic component instances in the document.
 
 
 |    ...

   
 ' ------------------------------------------------------------------------- 
 

   
 ' |  List schematic component instances in the model

   
 ' ------------------------------------------------------------------------- 
 

 

 
    Set objSchLComps = objSchRoot.GetComponents

   
 ...
 
 
 
#### []Find the positioning matrix 
 of specific graphical image of a Schematic component instance
 

This macro provides the GetComponentImage internal Function to return a 
 specific SchGRRComp interface handle on a specific graphical image of a 
 component instance. This interface provides the GetTransformation2D method 
 to return the positioning matrix of the image.
 
 
 |    ...

            If ( Not ( objCompGraphInst Is Nothing ) ) Then

               Set objGRRCompInst = GetComponentImage (objCompGraphInst)

   
 ...

                  objGRRCompInst.GetTransformation2D objSchLDbComp

   
 ...
 
 
 
#### []Query for a list of all the 
 connectors of a Schematic component instance
 

The macro calls AppListConnectors to list all the connectors. Notice 
 that the input objFilter is an empty list which specifies no filtering is 
 requested.
 
 
 |    ...

           
 '------------------------------------------------------------------

           
 ' Get the connector locations of all component instances

           
 '------------------------------------------------------------------

            If ( Not ( objCntbl Is Nothing ) And  Not ( objGRR Is Nothing ) ) Then

               Set objLCntrs = objCntbl.AppListConnectors (objLFilter)

   
 ...
 
 
 

For each connector in the returned list, the macro calls the method 
 calls GetPosition method to obtain the x-y coordinates of the connector 
 position.
 
 
 |    ...

                     For iCntr = 1 To intNbCntr

                        Set objCntr = Nothing

                        Set objCntr = objLCntrs.Item (iCntr,"CATIASchCntrLocation")

                        If ( Not ( objCntr Is Nothing )) Then

                           objCntr.GetPosition objGRR, objLDbCntr

   
 ...
 
 
 
#### []Query for a list of all the 
 Schematic route instances in the document
 

The SchematicRoot interface provides the GetRoutes method to return a 
 list of Schematic route instances in the document.
 
 
 |    ...

   
 ' ------------------------------------------------------------------------- 
 

   
 ' |  List schematic route instances

   
 ' ------------------------------------------------------------------------- 
 

 

    Set objSchLRoutes = objSchRoot.GetRoutes

   
 ...
 
 
 
#### []Query for a list of route 
 path definition points
 

The macro calls the GetRoutePrimitives to get the graphical 
 representation of a specific Schematic route instance. Then it calls 
 GetPath to get a list of x-y coordinates for each defining points of the 
 route path.  
 
 
 
```
...

 
'------------------------------------------------------------------

 
' Get the route points x-y coordinates of the route. 

 
'------------------------------------------------------------------

 If 
( Not ( objSchRouteGraph Is Nothing ) )
 Then

 Set 
objGRRRoute = GetRoutePrimitives (objSchRouteGraph,objSchRoot)

 If 
( Not ( objGRRRoute Is Nothing ) )
 Then

 objGRRRoute.GetPath objSchLDbRoute

 If 
( Not ( objSchLDbRoute Is Nothing ) And _
 
 int
NbOut > 3 )
 Then

 
 int
Nb = objSchLDbRoute.Count

 Dim 
iIndex
 As 
Integer

 Dim 
jIndex
 As 
integer

 Dim 
dbX
 As 
Double

 Dim 
dbY
 As 
Double

 Dim 
intNbPoint
 As 
Integer
 
 int
NbPoint =
 int
NbOut/2

 If 
( (intNbOut =
 int
Nb ) And (intNbPoint > 1) )
 Then
```

 
```
...

 

 For 
iIndex = 1 To
 int
NbPoint
 jIndex = ((iIndex-1) * 2) + 1
 dbX = objSchLDbRoute.Item(jIndex)
 dbY = objSchLDbRoute.Item(jIndex+1)
 
...

 Next
```

 
 
 
 
 
 
 

[[Top]]

---

 
 
#### []In Short
 

This use case shows how to query the data of a Schematic document and of its 
 object. A message logging the status of the critical steps is displayed at the 
 end of the use case.
 

 ![](images/CAASchQueryCompRoute_02.jpg)
 

[[Top]]

---

 
 
#### []References
 
 
 |[1]
 |[
 Replaying a Macro]
 
 
 
 
 |[[Top]]
 
 
 

---

 
 

*Copyright 2001, Dassault Systmes. All rights reserved.*