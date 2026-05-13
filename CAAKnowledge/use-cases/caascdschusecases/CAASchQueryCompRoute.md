---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScrJavaScript", "CAAScdSchUseCases", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASCH_CompRoute01", "CAASCHEDUApp", "CATIASchCntrLocation", "CAADoc", "CAASchQueryCompRouteSource", "CAASchAppBase", "CAASchQueryCompRoute", "CAASchAppUtilities", "CAASchQueryCompRoute_02", "CAASchQueryCompRoute_01"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryCompRoute.htmmd"
converted: "2026-05-11T11:27:02.604894"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document.  
     
     

#### Query for the name of the 
     current document in the session
     

The SchSession interface provides the GetCurrentDocument method to 
     return the name of the current document.
     
     

#### Query for a list of 
     Schematic reference components in the document
     

The SchematicRoot interface provides the GetRefComponents method to 
     return a list of Schematic component references in the document.
     
     

#### Query for a list of 
     Schematic component instances in the document
     

The SchematicRoot interface provides the GetComponents method to return 
     a list of Schematic component instances in the document.
     
     

#### Find the positioning matrix 
     of specific graphical image of a Schematic component instance
     

```vbscript
This macro provides the GetComponentImage internal Function to return a 
     specific SchGRRComp interface handle on a specific graphical image of a 
```
     component instance. This interface provides the GetTransformation2D method 
     to return the positioning matrix of the image.
     
     

#### Query for a list of all the 
     connectors of a Schematic component instance
     

The macro calls AppListConnectors to list all the connectors. Notice 
     that the input objFilter is an empty list which specifies no filtering is 
     requested.
     
     

For each connector in the returned list, the macro calls the method 
     calls GetPosition method to obtain the x-y coordinates of the connector 
     position.
     
     

#### Query for a list of all the 
     Schematic route instances in the document
     

The SchematicRoot interface provides the GetRoutes method to return a 
     list of Schematic route instances in the document.
     
     

#### Query for a list of route 
     path definition points
     

The macro calls the GetRoutePrimitives to get the graphical 
     representation of a specific Schematic route instance. Then it calls 
     GetPath to get a list of x-y coordinates for each defining points of the 
     route path.  
     
     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows how to query the data of a Schematic document and of its 
 object. A message logging the status of the critical steps is displayed at the 
 end of the use case.
 

 ![](images/CAASchQueryCompRoute_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*

 

```vbscript
...
            '------------------------------------------------------------------
            ' Get the route points x-y coordinates of the route. 
            '------------------------------------------------------------------
            If ( Not ( objSchRouteGraph Is Nothing ) ) Then

```vbscript
               Set objGRRRoute = GetRoutePrimitives (objSchRouteGraph,objSchRoot)

               If ( Not ( objGRRRoute Is Nothing ) ) Then
```

                  objGRRRoute.GetPath objSchLDbRoute

                  If ( Not ( objSchLDbRoute Is Nothing ) And _
                       intNbOut &gt; 3 ) Then

                     intNb = objSchLDbRoute.Count

```vbscript
                     Dim iIndex As Integer
                     Dim jIndex As integer
                     Dim dbX As Double
                     Dim dbY As Double
                     Dim intNbPoint As Integer
                     intNbPoint = intNbOut/2
```

                     If ( (intNbOut = intNb ) And  (intNbPoint &gt; 1) ) Then
```

```vbscript
...
                        
                        For iIndex = 1 To intNbPoint
                           jIndex = ((iIndex-1) * 2) + 1
                           dbX = objSchLDbRoute.Item(jIndex)
                           dbY = objSchLDbRoute.Item(jIndex+1)
     ...
                        Next
```