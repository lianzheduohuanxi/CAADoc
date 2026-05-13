---
title: "Creating a Schematic Component Instance (Placement)"
category: "use-case"
module: "CAAScdSchUseCases"
tags: "["CAADoc", "CAASCH_Sample", "CAASCH_RouteForPlacement2", "CAAScdSchUseCases", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASchPlaceComponent", "CAASchPlatformModeler", "CATIASchComponent2", "CAASchAppUtilities"]"
source_file: "Doc/online/CAAScdSchUseCases/CAASchPlaceComponent.htm"
converted: "2026-05-11T17:31:51.433971"
---
## Schematics Platform Modeler

|
## Creating a Schematic Component Instance (Placement)

* * *

 This macro shows you how to create a component instance in a 2D viewer of a Schematic document. It also shows how to create an instance and connect that to an existing one at the same time.To create a Schematic component instance, its reference component needs to be identified. This use case illustrates how to specify that reference based on a Schematic component catalog. ![](images/CAASchPlaceComponent_01.jpg) In this use case, the "Blocking Valve" and the "Control Valve" component references will be used.
---|---
 CAASchPlaceComponent is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

  * Prerequisites:

>   1. RADE must be installed.
>   2. CAASchPlatformModeler.edu must exist in CAADoc folder.
>

  * Setup:

>   1. Build CAASchAppBase.m and CAASchAppUtilities.m, located in CAASchPlatformModeler.edu (RADE is required).
>   2. Copy generated DLLs, CAASchAppBase.dll and CAASchAppUtilities.m, respectively, to the run-time environment folder "intel_a/code/bin."
>   3. Copy CAASCHEDUApp.CATfct, located CAASchPlatformModeler.edu/CNext/resources/graphic, to the run-time environment folder "intel_a/resources/graphic."
>   4. Copy CAASchPlatformModeler.edu/CNext/code/dictionary/CAASchPlatformModeler.edu.dico to the run-time environment folder "intel_a/code/dictionary."
>

[CAASchPlaceComponent.CATScript ](CAASchPlaceComponentSource.md) is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchPlaceComponent.CATScript) (windows only).
 CAASchPlaceComponent includes the following steps:

  1. Prolog
  2. Place a Schematic component instance in free space (not connected to any other object).
  3. Place a Schematic component instance and connect it to instance created in previous step.

#### Prolog

2. Place a Schematic component instance in free space (not connected to any other object).
3. Place a Schematic component instance and connect it to instance created in previous step.
The macro first loads two documents: CAASCH_Sample.catalog and CAASCH_RouteForPlacement2.CATProduct.  |

        ...
The macro first loads two documents: CAASCH_Sample.catalog and CAASCH_RouteForPlacement2.CATProduct.  |
```vbscript
```vbscript
        ' -------------------------------------------------------------------------
        ' Open the schematic document

```

```

```vbscript
```vbscript
        Dim sCtlgFilePath
```vbscript
```
```cpp
        sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

                "online/CAAScdSchUseCases/samples/CAASCH_Sample.catalog")

```vbscript
```vbscript
Dim sCtlgFilePath
```vbscript
```
```vbscript
```cpp
sCtlgFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim objSchCtlgDoc As Document
        Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)

```
```

```

```

```vbscript
```vbscript
Dim objSchCtlgDoc As Document
```vbscript
```
```vbscript
```cpp
Set objSchCtlgDoc = CATIA.Documents.Open(sCtlgFilePath)
        ' Open main schematic P&ID design document (for new component instances created here)
```
```

```

```

```vbscript
```vbscript
        Dim sFilePath
```vbscript
```
```cpp
        sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

                "online/CAAScdSchUseCases/samples/CAASCH_RouteForPlacement2.CATProduct")

```vbscript
```vbscript
Dim sFilePath
```vbscript
```
```vbscript
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
        Dim objSchDoc As Document
        Set objSchDoc = CATIA.Documents.Open(sFilePath)
```
```

```

```

        ...

---

Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.

    ...
Next, the macro acquires the schematic root object from the document. The schematic root is the top node of the object instance tree in a schematic document.
```vbscript
```vbscript
    ' Find the top node of the schematic object tree - schematic root.

```

```

```vbscript
```vbscript
    Dim objPrdRoot As Product
```vbscript
```
```vbscript
```vbscript
    Dim objSchRoot As SchematicRoot
    If ( Not ( objSchDoc Is Nothing ) ) Then
```
```vbscript
      Set objPrdRoot = objSchDoc.Product
      If ( Not ( objPrdRoot Is Nothing ) ) Then
```
```vbscript
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
      End If
```
    End If
```

```

```

    ...

---
#### Place a Schematic component instance in free space (not connected to any other object).

The SchematicRoot interface provides the GetCompSymbolFromCatalog method to retrieve the graphical representation of a specific Schematic component reference by name. In this case, the "Blocking Valve" is chosen. Based on this graphical representation, the macro calls the GetSchObjOwner to obtain the Schematic component reference.

    ...
```vbscript
```vbscript
```vbscript
       '-----------------------------------------------------------------------
       ' Get the first symbol from component catalog.
       '-----------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
       Set objSchGRRCtlg = objSchRoot.GetCompSymbolFromCatalog ("Blocking Valve",objSchCtlgDoc)
```
```

    ...
```vbscript
```vbscript
```vbscript
         '---------------------------------------------------------------------
         ' Get the owner of the first symbol. That is a reference component
         ' in the catalog.
         '---------------------------------------------------------------------
```vbscript
         Set objSchCntblRef = objSchGRRCtlg.GetSchObjOwner
```
```

```

```

    ...

---

Method PlaceInSpace is then called to create a new instance of the "Blocking Valve" reference component in the design document. Note that the placement position and orientation are defined by a 6-words double-array (db6Array) which is an input to the method.
```vbscript
```vbscript
```vbscript
    '--------------------------------------------------------------------------
    ' Component instance (to be created below) orientation matrix.
    ' x-axis = (1.0,0.0)
    ' y-axis = (0.0,1.0)
    ' origin = (100.0,300.0)
    '--------------------------------------------------------------------------
```

```

```

```vbscript
```cpp
    Dim db6Array(6) As CATSafeArrayVariant
```vbscript
```
    db6Array(0)=1.0
    db6Array(1)=0.0
    db6Array(2)=0.0
    db6Array(3)=1.0
    db6Array(4)=145.0
    db6Array(5)=130.0
```

```

```vbscript
```vbscript
```vbscript
           '-------------------------------------------------------------------
           ' Place an instance of the catalog reference in an empty space in
           ' the design document
           ' Note that the target document is an input to PlaceInSpace
           '-------------------------------------------------------------------
```cpp
           Set objSchComp2Ref = objSchRoot.GetInterface ("CATIASchComponent2",objSchCntblRef)
           If ( Not ( objSchComp2Ref Is Nothing ) ) Then
```
```

```

```

    ...
```vbscript
```cpp
Set objSchComp2Ref = objSchRoot.GetInterface ("CATIASchComponent2",objSchCntblRef)
```
```

If ( Not ( objSchComp2Ref Is Nothing ) ) Then
              objSchComp2Ref.PlaceInSpace objSchGRRCtlg,db6Array,objSchDoc,objSchCompInstA

    ...

```vbscript
           End If
```vbscript
```vbscript
         End If
       End If
```

```

```

    ...

---
#### Place a Schematic component instance and connect it to instance created in previous step

As in previous step, the macro find the reference component from the catalog by the name of the graphical representation of the component. In this case, the name is "Control Valve"

    ...
```vbscript
```vbscript
       Set objSchGRRCVCtlg = objSchRoot.GetCompSymbolFromCatalog ("Control Valve",objSchCtlgDoc)
```
```

    ...
```vbscript
```vbscript
```vbscript
         '---------------------------------------------------------------------
         ' Get the owner of the second symbol. That is a reference component
         ' in the catalog.
         '---------------------------------------------------------------------
```vbscript
         Set objSchCntblCVRef = objSchGRRCVCtlg.GetSchObjOwner
```
```

```

```

    ...

---

Unlike previous step, instead of specifying a placement position, the macro obtains the SchComponent interface from the "Blocking Valve" component instance (created in previous step) and creates an Control Valve component instance by calling the PlaceOnComponentWithInfo method of the interface.

In the comment section of the following code segments, instance A refers to "Blocking Valve" instance that was created in previous step and instance B refers to "Control Valve" instance the macro is about to create.

    ...
```vbscript
```vbscript
```vbscript
              '----------------------------------------------------------------
              '  1- QueryConnectAbility.
              '     Ask the reference of the new instance B for information
              '     to use in compatibility checking. The objCompRefPlaceInfo
              '     is an output and should be used as a "black box".
              '     It is the input to the next call.
              '
              '  2- IsTargetOKForPlace
              '     Check whether A is compatible to B in making a connection.
              '     A is the first instance, it is the "target".
              '     objCompatInfo is an output and should be used as
              '     a "black box". It is an input to the next call.
              '
              '  3- GetBestFitPlaceInfo
              '     Input the placement location, close to the x-y location of
              '     the connector of objSchCompInstA (A) that you want to connect
              '     B to.
              '     objFinalPlaceInfo is an output and should be used as
              '     a "black box". It is an input to the next call.
              '
              '  4- PlaceOnComponentWithInfo
              '     Place a new instance with the black box info.
              '
              '----------------------------------------------------------------
              ' -- step 1
```

```

```

```vbscript
```vbscript
              Set objCompRefPlaceInfo = objSchCompCVRef.QueryConnectAbility _
                (objSchGRRCVCtlg)
```
```vbscript
              ' -- step 2
```

              objSchCompatInstA.IsTargetOKForPlace objSchGRRCompInstA, _
                objCompRefPlaceInfo, objCompatInfo, bYesCompat

```cpp
              Dim db2Pt(2) As CATSafeArrayVariant
```vbscript
```
```vbscript
              '-- 6.50 is the relative x coordinate of the right connector
              '-- from the symbol origin of the "Blocking Valve" instance.
```

              db2Pt(0) = 145.0 + 6.50
              db2Pt(1) = 130.0

```

```

```vbscript
              If ( bYesCompat ) Then
```

    ...
```vbscript
If ( bYesCompat ) Then
                 bFindAllSolutions = false
```vbscript
                 ' -- step 3
```

                 objSchCompatInstA.GetBestFitPlaceInfo db2Pt, objCompatInfo, _
                   objFinalPlaceInfo, bFindAllSolutions

```

```vbscript
                 If ( Not ( objFinalPlaceInfo is Nothing ) ) Then
```vbscript
```vbscript
                    ' -- step 4
```vbscript
                    Set objSchCompInstB = objSchCompCVRef.PlaceOnComponentWithInfo _
```
```

```

                      (objFinalPlaceInfo)
```

    ...

---

[Top]

* * *
#### In Short

This use case shows how to create component instances. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchPlaceComponent_02.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
