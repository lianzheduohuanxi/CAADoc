---
title: "Untitled"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAAScrBase", "CAASchInsertComponentSource", "CATIA", "CAAScrJavaScript", "CAASchInsertComponent_01", "CAAScdSchUseCases", "CAASchPlatformModeler", "CAAScdInfUseCases", "CAAInfLauchMacro", "CAASCH_Sample", "CAASCH_RouteForPlacement", "CAASchInsertComponent_02", "CAASCHEDUApp", "CAASchInsertComponent", "CATIASchComponent", "CAASchAppBase", "CAADoc", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInsertComponent.htm"
converted: "2026-05-11T11:27:02.647035"
---

---

 
 
     

Next, the macro acquires the schematic root object from the document. 
     The schematic root is the top node of the object instance tree in a 
     schematic document. 
     
     

The SchematicRoot interface provides a method to retrieve the graphical 
     representation of a reference component from the catalog by name. This 
     graphical representation is associated to a reference component in the 
     catalog.
     
     

#### Get the Schematic 
     reference component from the catalog
     

Given the graphical representation (symbol) from the previous step, the 
     macro calls GetSchObjOwner to get the Schematic reference component that 
     the symbol is associated with.
     
     

Through the GetInterface method, the macro obtains a handle on the 
     SchComponent interface, which is needed for creating an instance of the 
     Schematic reference component from the catalog.
     
     

#### Insert an instance of the Schematic 
     reference component - approach 1
     

The "insert" process includes the following.
     

       
- 
     

Create a new instance of the Schematic reference component.
       
- Spit the existing route into two pieces, creating a new route in the 
       process.
       
- Make all necessary connections between the new component instance and 
       the routes.
     
     

Approach 1 is specially designed for client application that has 
     dedicated graphical user interface to manage the checking of the 
     compatibility between the route and the component. In particular, the QueryConnectAbility and the IsTargetOKForInsert methods can be used to 
     filter out incompatible component-route combinations (perhaps accompanied 
     with client specific visual user feedbacks). Furthermore, when the route is 
     being selected and the "mouse" is traveling along the route path and right 
     before the left-mouse button clicking to define the placement location, the GetBestFitInsertInfo method can be used to make sure that the compatible 
     component will "fit" into the route..
     

#### Insert an instance of the Schematic 
     reference component - approach 2
     

An client application which doesn't want to deal with the details of the 
     compatibility checking should use approach 2. By calling the PlaceOnObject method, a Schematic component can be inserted into a route. All the 
     compatibility methods are implicitly called in the implementation of the PlaceOnObject method and are kept transparent to the application. There are 
     only two required input: the placement location and the object to be 
     connected to the new instance.
     

To figure out the placement location of the component instance, the 
     macro calls the private FindPlacementPoint function. There, the x-y 
     coordinates of the route path defining points are retrieved using the GetPath method of the SchGRRRoute interface. Given these, the macro takes 
     the mid point of the first two points in the path and returns its x-y 
     coordinates to be the placement location.
     

     
   
 
 

[Top]

---

 
 

#### In Short
 

This use case shows two ways to insert a Schematic object into a Schematic 
 route. A message logging the status of the critical steps is displayed at the 
 end of the use case. 
 

 ![](images/CAASchInsertComponent_02.jpg)
 

[Top]

---

 
 

#### References
 
 

---

 
 

*Copyright  2001, Dassault Systmes. All rights reserved.*

 

```vbscript
...
    ' ------------------------------------------------------------------------- 
    ' Open the catalog document 
    Dim sCtlgFilePath
    sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online\CAAScdSchUseCases\samples\CAASCH_Sample.catalog")

    Dim objSchCtlgDoc As Document
    Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)
```

```vbscript
' Open main schematic design document (for new component instances created here)
    Dim sFilePath
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
            "online\CAAScdSchUseCases\samples\CAASCH_RouteForPlacement.CATProduct")

    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)
    ...
```

```vbscript
...
    ' Find the top node of the schematic object tree - schematic root.
    Dim objPrdRoot As Product
    Dim objSchRoot As SchematicRoot
    If ( Not ( IsEmpty ( objSchDoc ) ) Then
      Set objPrdRoot = objSchDoc.Product 
      If ( Not ( IsEmpty ( objPrdRoot ) ) Then
        Set objSchRoot = objPrdRoot.GetTechnologicalObject(&quot;SchematicRoot&quot;)
      End If
    End If
```

```vbscript
...
```

```vbscript
...
    Dim objSchGRRCVCtlg As SchGRR
```

```vbscript
...

    If ( Not ( IsEmpty ( objSchRoot ) ) ) Then

       '-----------------------------------------------------------------------
       ' Get the symbol of a component from the component catalog.
       '-----------------------------------------------------------------------
       Set objSchGRRCVCtlg = objSchRoot.GetCompSymbolFromCatalog (&quot;Control Valve&quot;,objSchCtlgDoc)
    ...
```