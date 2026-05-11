---
title: "Querying Schematic Document Content"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_CompRoute01", "CAADoc", "CAASchQueryCompRoute", "CAAScdSchUseCases", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASchPlatformModeler", "CATIASchCntrLocation", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryCompRoute.md"
converted: "2026-05-11T17:31:51.448432"
---
## Schematics Platform Modeler

| 
## Querying Schematic Document Content  
  
  
* * *

 This macro shows you how to query for information from a Schematic design document. The information includes the following:

  1. A list of all Schematic components (references or instances) in the document.
  2. A list of all Schematic routes in the document.
  3. The placement matrix of a specific Schematic component instance.
  4. The defining route points of the route path of a specific Schematic route instance.
  5. The position of a connector.

This macro open the CAASCH_CompRoute01.CATProduct document for querying information. ![](images/CAASchQueryCompRoute_01.jpg)  
---|---  
 CAASchQueryCompRoute is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

  * Prerequisites:

>   1. RADE must be installed.
>   2. CAASchPlatformModeler.edu must exist in CAADoc folder.
> 

  * Setup:

>   1. Build CAASchAppBase.m and CAASchAppUtilities.m, located in CAASchPlatformModeler.edu (RADE is required). 
>   2. Copy generated DLLs, CAASchAppBase.dll and CAASchAppUtilities.m, respectively, to the run-time environment folder "intel_a\code\bin."
>   3. Copy CAASCHEDUApp.CATfct, located CAASchPlatformModeler.edu\CNext\resources\graphic, to the run-time environment folder "intel_a\resources\graphic."
>   4. Copy CAASchPlatformModeler.edu\CNext\code\dictionary\CAASchPlatformModeler.edu.dico to the run-time environment folder "intel_a\code\dictionary."
> 

[CAASchQueryCompRoute.CATScript ](CAASchQueryCompRouteSource.md) is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchQueryCompRoute.CATScript) (windows only).  
 CAASchQueryCompRoute includes the following steps:

  1. Prolog
  2. Query for the name of the current document in the session.
  3. Query for a list of Schematic reference components in the document.
  4. Query for a list of Schematic component instances in the document.
  5. Find the positioning matrix of specific graphical image of a Schematic component instance.
  6. Query for a list of all the connectors of a Schematic component instance.
  7. Query for a list of all the Schematic route instances in the document.
  8. Query for a list of route path definition points.

#### Prolog

The macro first loads the document: CAASCH_CompRoute01.CATProduct. |     ...  
    ' Open the schematic document   
```vbscript
    Dim sFilePath  
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _  
            "online\CAAScdSchUseCases\samples\CAASCH_CompRoute01.CATProduct")  
  
    Dim objSchDoc As Document  
    Set objSchDoc = CATIA.Documents.Open(sFilePath)  
    ...  
```

```

---  
  
Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document. 

    ...  
    ' Find the top node of the schematic object tree - schematic root.  
```vbscript
    Dim objPrdRoot As Product  
    Dim objSchRoot As SchematicRoot  
    If ( Not ( objSchDoc Is Nothing ) ) Then  
      Set objPrdRoot = objSchDoc.Product   
      If ( Not ( objPrdRoot Is Nothing ) ) Then  
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")  
      End If  
    End If  
    ...  
```

```

---  
#### Query for the name of the current document in the session

The SchSession interface provides the GetCurrentDocument method to return the name of the current document.

    ...  
```vbscript
       Set objSchSession = objSchRoot.GetSchematicSession  
```vbscript
       '-----------------------------------------------------------------------  
       '| Query the name of the current document    
       '-----------------------------------------------------------------------  
       If ( Not ( objSchSession Is Nothing ) ) Then  
          Set objCurDoc = objSchSession.GetCurrentDocument  
```

    ...  
```

```

---  
#### Query for a list of Schematic reference components in the document

The SchematicRoot interface provides the GetRefComponents method to return a list of Schematic component references in the document.

    ...  
```vbscript
    ' -------------------------------------------------------------------------    
    ' |  List schematic component references in the model  
    ' -------------------------------------------------------------------------    
```

```vbscript
    Set objSchLCompRefs = objSchRoot.GetRefComponents  
    ...  
```

```

---  
#### Query for a list of Schematic component instances in the document

The SchematicRoot interface provides the GetComponents method to return a list of Schematic component instances in the document.

    ...  
```vbscript
    ' -------------------------------------------------------------------------    
    ' |  List schematic component instances in the model  
    ' -------------------------------------------------------------------------    
```

   
```vbscript
    Set objSchLComps = objSchRoot.GetComponents  
    ...  
```

```

---  
#### Find the positioning matrix of specific graphical image of a Schematic component instance

This macro provides the GetComponentImage internal Function to return a specific SchGRRComp interface handle on a specific graphical image of a component instance. This interface provides the GetTransformation2D method to return the positioning matrix of the image.

    ...  
```vbscript
            If ( Not ( objCompGraphInst Is Nothing ) ) Then  
```vbscript
               Set objGRRCompInst = GetComponentImage (objCompGraphInst)  
    ...  
                  objGRRCompInst.GetTransformation2D objSchLDbComp  
    ...  
```

```

---  
#### Query for a list of all the connectors of a Schematic component instance

The macro calls AppListConnectors to list all the connectors. Notice that the input objFilter is an empty list which specifies no filtering is requested.

    ...  
```vbscript
            '------------------------------------------------------------------  
            ' Get the connector locations of all component instances  
            '------------------------------------------------------------------  
```

```vbscript
            If ( Not ( objCntbl Is Nothing ) And  Not ( objGRR Is Nothing ) ) Then  
```vbscript
               Set objLCntrs = objCntbl.AppListConnectors (objLFilter)  
    ...  
```

```

---  
  
```vbscript
For each connector in the returned list, the macro calls the method calls GetPosition method to obtain the x-y coordinates of the connector position.

```

    ...  
```vbscript
                     For iCntr = 1 To intNbCntr  
```vbscript
                        Set objCntr = Nothing  
                        Set objCntr = objLCntrs.Item (iCntr,"CATIASchCntrLocation")  
                        If ( Not ( objCntr Is Nothing )) Then  
                           objCntr.GetPosition objGRR, objLDbCntr  
    ...  
```

```

---  
#### Query for a list of all the Schematic route instances in the document

The SchematicRoot interface provides the GetRoutes method to return a list of Schematic route instances in the document.

    ...  
```vbscript
    ' -------------------------------------------------------------------------    
    ' |  List schematic route instances  
    ' -------------------------------------------------------------------------    
```

  
```vbscript
    Set objSchLRoutes = objSchRoot.GetRoutes  
    ...  
```

```

---  
#### Query for a list of route path definition points

The macro calls the GetRoutePrimitives to get the graphical representation of a specific Schematic route instance. Then it calls GetPath to get a list of x-y coordinates for each defining points of the route path. 
    
    
        ...
```vbscript
                '------------------------------------------------------------------
                ' Get the route points x-y coordinates of the route. 
                '------------------------------------------------------------------
```

```vbscript
                If ( Not ( objSchRouteGraph Is Nothing ) ) Then
    
```vbscript
                   Set objGRRRoute = GetRoutePrimitives (objSchRouteGraph,objSchRoot)
    
```

```vbscript
                   If ( Not ( objGRRRoute Is Nothing ) ) Then
    
```

                      objGRRRoute.GetPath objSchLDbRoute
    
```vbscript
                      If ( Not ( objSchLDbRoute Is Nothing ) And _
                           intNbOut > 3 ) Then
    
```

                         intNb = objSchLDbRoute.Count
    
```vbscript
                         Dim iIndex As Integer
                         Dim jIndex As integer
                         Dim dbX As Double
                         Dim dbY As Double
                         Dim intNbPoint As Integer
                         intNbPoint = intNbOut/2
    
```

```vbscript
                         If ( (intNbOut = intNb ) And  (intNbPoint > 1) ) Then
    
```

    
        ...
                            
```vbscript
                            For iIndex = 1 To intNbPoint
                               jIndex = ((iIndex-1) * 2) + 1
                               dbX = objSchLDbRoute.Item(jIndex)
                               dbY = objSchLDbRoute.Item(jIndex+1)
         ...
                            Next   
  
```

```

---  
  
[Top]

* * *
#### In Short

This use case shows how to query the data of a Schematic document and of its object. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchQueryCompRoute_02.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
