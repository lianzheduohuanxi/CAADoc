---
```vbscript
title: "Inserting a Schematic Component into a Schematic Route"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_Sample", "CAADoc", "CATIASchComponent", "CAAScdSchUseCases", "CAASCH_RouteForPlacement", "CATIA", "CAASchAppBase", "CAASchAppUtilities", "CAASCHEDUApp", "CAASchPlatformModeler", "CAASchInsertComponent"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInsertComponent.htm"
converted: "2026-05-11T17:31:51.373120"
```

---
## Schematics Platform Modeler

| 
## Inserting a Schematic Component into a Schematic Route  

* * *

 This macro shows you how to insert a Schematic component into a Schematic route. The word "insert" refers to a process by which a Schematic route is split at a specific location (creating a new route) and a Schematic component is connected to the two routes, creating two connections. These connections are created through two connectors of the schematic component. These two connectors must be internally connected to each other by an "internal flow" object, which is aggregated by the Schematic component. This macro opens two documents: CAASCH_Sample.catalog and CAASCH_RouteForPlacement.CATProduct.  Notice the x-y coordinates of a point (80,50), as indicated in the screen shots. They will be used later in this use case. ![](images/CAASchInsertComponent_01.jpg) In this use case, two Schematic components are inserted into route using two different approaches.  
---|---  
 CAASchInsertComponent is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

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

[CAASchInsertComponent.CATScript i](CAASchInsertComponentSource.md)s located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchInsertComponent.CATScript) (Windows only).  
 CAASchInsertComponent includes the following steps:

CAASchInsertComponent includes the following steps:
  1. Prolog
  2. Get the Schematic reference component from the catalog
  3. Insert an instance of the Schematic reference component - approach 1
  4. Insert an instance of the Schematic reference component - approach 2

#### Prolog

3. Insert an instance of the Schematic reference component - approach 1
4. Insert an instance of the Schematic reference component - approach 2
The macro first loads two documents. CAASCH_Sample.catalog and CAASCH_RouteForPlacement.CATProduct. | 

        ...
The macro first loads two documents. CAASCH_Sample.catalog and CAASCH_RouteForPlacement.CATProduct. |
        ' ------------------------------------------------------------------------- 
        ' Open the catalog document 

```vbscript
        Dim sCtlgFilePath
        sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                "online\CAAScdSchUseCases\samples\CAASCH_Sample.catalog")

```vbscript
Dim sCtlgFilePath
sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim objSchCtlgDoc As Document
        Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)

```

```vbscript
Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)
        ' Open main schematic design document (for new component instances created here)
```

```vbscript
        Dim sFilePath
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

                "online\CAAScdSchUseCases\samples\CAASCH_RouteForPlacement.CATProduct")

```vbscript
Dim sFilePath
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)
```

        ...  

---  

Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document. 

        ...
Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.
        ' Find the top node of the schematic object tree - schematic root.

```vbscript
        Dim objPrdRoot As Product
        Dim objSchRoot As SchematicRoot
        If ( Not ( IsEmpty ( objSchDoc ) ) Then
          Set objPrdRoot = objSchDoc.Product 
          If ( Not ( IsEmpty ( objPrdRoot ) ) Then
            Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
          End If
        End If

```

        ...  

---  

The SchematicRoot interface provides a method to retrieve the graphical representation of a reference component from the catalog by name. This graphical representation is associated to a reference component in the catalog.

        ...
```vbscript
        Dim objSchGRRCVCtlg As SchGRR 

```

        ...

```vbscript
        If ( Not ( IsEmpty ( objSchRoot ) ) ) Then
```

```vbscript
           '-----------------------------------------------------------------------
           ' Get the symbol of a component from the component catalog.
           '-----------------------------------------------------------------------
           Set objSchGRRCVCtlg = objSchRoot.GetCompSymbolFromCatalog ("Control Valve",objSchCtlgDoc)
```

        ...  

---  
#### Get the Schematic reference component from the catalog

Given the graphical representation (symbol) from the previous step, the macro calls GetSchObjOwner to get the Schematic reference component that the symbol is associated with.

    ...  
```vbscript
         '---------------------------------------------------------------------  
         ' Get the owner of the symbol. That is, a reference component,  
         ' in the catalog.  
         '---------------------------------------------------------------------  
```

```vbscript
         Set objSchCntblCVRef = objSchGRRCVCtlg.GetSchObjOwner  
```

    ...  

---  

Through the GetInterface method, the macro obtains a handle on the SchComponent interface, which is needed for creating an instance of the Schematic reference component from the catalog.

    ...  
```vbscript
         If ( Not ( IsEmpty ( objSchCntblCVRef ) ) ) Then  

```

```vbscript
           Set objSchCompCVRef = objSchRoot.GetInterface ("CATIASchComponent",objSchCntblCVRef)  
```

    ...  

---  
#### Insert an instance of the Schematic reference component - approach 1

The "insert" process includes the following.

  * Create a new instance of the Schematic reference component.

        * Spit the existing route into two pieces, creating a new route in the 
               process.

        * Make all necessary connections between the new component instance and 
               the routes.

    Approach 1 is specially designed for client application that has 
         dedicated graphical user interface to manage the checking of the 
         compatibility between the route and the component. In particular, the QueryConnectAbility and the IsTargetOKForInsert methods can be used to 
         filter out incompatible component-route combinations (perhaps accompanied 
         with client specific visual user feedbacks). Furthermore, when the route is 
         being selected and the "mouse" is traveling along the route path and right 
         before the left-mouse button clicking to define the placement location, the GetBestFitInsertInfo method can be used to make sure that the compatible 
         component will "fit" into the route..

             ...  
```vbscript
                  '----------------------------------------------------------------  
                  '  Insert a component into a route.  
                  '  
                  '  Approach 1 - with compatibility information.  
                  '  1- QueryConnectAbility.  
                  '     Ask the reference of the component for information  
                  '     to use in compatibility checking. The objCompRefPlaceInfo  
                  '     is an output and should be used as a "black box".   
                  '     It is the input to the next call.  
                  '  
                  '  2- IsTargetOKForInsert  
                  '     Check whether the route is compatible to the component  
                  '     in making connections.  
                  '     The route instance is the "target".   
                  '     objCompatInfo is an output and should be used as   
                  '     a "black box". It is an input to the next call.  
                  '  
                  '  3- GetBestFitInsertInfo  
                  '     Input the placement location, close to middle of the route  
                  '     objFinalInsertInfo is an output and should be used as  
                  '     a "black box". It is an input to the next call.  
                  '  
                  '  4- InsertIntoRouteWithInfo  
                  '     Place a new component instance with the black box info.  
                  '     The route will be broken up into 2 pieces (shorten the  
                  '     existing route and create a new route instance).  
                  '     The new component instance will be connected to the  
                  '     2 routes on each of the 2 sides (left and right).    
                  '----------------------------------------------------------------  
                  ' -- step 1   
```

```vbscript
                  Set objCompRefPlaceInfo = objSchCompCVRef.QueryConnectAbility _  
                    (objSchGRRCVCtlg)   
                  ' -- step 2   
                  objSchCompatRoute.IsTargetOKForInsert objCompRefPlaceInfo, _  
                    objCompatInfo, bYesCompat  

                  Dim db2Pt(2) As CATSafeArrayVariant  
                  '-- a point at the middle of the route  
                  db2Pt(0) = 80.0  
                  db2Pt(1) = 50.0  

```

```vbscript
                  If ( bYesCompat ) Then  
```

        ...  
```vbscript
If ( bYesCompat ) Then
                     bFindAllSolutions = false  
                     ' -- step 3   
                     objSchCompatRoute.GetBestFitInsertInfo db2Pt, objCompatInfo, _  
                       objFinalInsertInfo, bFindAllSolutions  

```

```vbscript
                     If ( Not ( IsEmpty ( objFinalInsertInfo ) ) ) Then  
                        ' -- step 4   
                        objSchCompCVRef.InsertIntoRouteWithInfo objFinalI
    nsertInfo, _  
                          objSchCompInst,objSchRouteInst  
```

        ...  

    ---  
    #### Insert an instance of the Schematic 
         reference component - approach 2

reference component - approach 2
    An client application which doesn't want to deal with the details of the 
         compatibility checking should use approach 2. By calling the PlaceOnObject method, a Schematic component can be inserted into a route. All the 
         compatibility methods are implicitly called in the implementation of the PlaceOnObject method and are kept transparent to the application. There are 
         only two required input: the placement location and the object to be 
         connected to the new instance.

             ...  
```vbscript
                     Dim db6Matrix(6) As CATSafeArrayVariant  
                     db6Matrix(0)=1.0  
                     db6Matrix(1)=0.0  
                     db6Matrix(2)=0.0  
                     db6Matrix(3)=1.0  
                     db6Matrix(4)=db2Pt(0)  
                     db6Matrix(5)=db2Pt(1)  

```

```vbscript
db6Matrix(4)=db2Pt(0)
db6Matrix(5)=db2Pt(1)
                     objSchCompCVRef.PlaceOnObject objSchGRRCVCtlg, db6Matrix, _  
                       objSchCntblRouteInst, objSchCompInst2  
```

        ...  

    ---  

    To figure out the placement location of the component instance, the 
         macro calls the private FindPlacementPoint function. There, the x-y 
         coordinates of the route path defining points are retrieved using the GetPath method of the SchGRRRoute interface. Given these, the macro takes 
         the mid point of the first two points in the path and returns its x-y 
         coordinates to be the placement location.

    [Top]

    * * *

    #### In Short

    This use case shows two ways to insert a Schematic object into a Schematic 
     route. A message logging the status of the critical steps is displayed at the 
     end of the use case. 

     ![](images/CAASchInsertComponent_02.jpg)

    [Top]

    * * *

    #### References

         [1]
         | [
         Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)

         | 

         [Top]

    * * *

    _Copyright  2001, Dassault Systmes. All rights reserved._
