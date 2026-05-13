---
```vbscript
title: "Querying for a List of Connected Objects"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAASCH_CompRoute01", "CAADoc", "CAAScdSchUseCases", "CAASchAppBase", "CATIA", "CAASCHEDUApp", "CAASchQueryConnectivity", "CAASchPlatformModeler", "CATIASchAppConnectable", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchQueryConnectivity.htmmd"
converted: "2026-05-11T17:31:51.464895"
```

---
## Schematics Platform Modeler

|
## Querying for a List of Connected Objects

* * *

 This macro shows you how to find a list of objects connected to a Schematic component instance or a Schematic route instance.In this use case, the macro query for a list of Schematic component instances and a list of Schematic route instance. For each member in the two lists, the macro searches for all the objects connected to the member.
---|---
 CAASchQueryConnectivity is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

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

[ CAASchQueryConnectivity.CATScript ](CAASchQueryConnectivitySource.md)is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchQueryConnectivity.CATScript) (Windows only).
 CAASchQueryConnectivity includes the following steps:

CAASchQueryConnectivity includes the following steps:
  1. Prolog
  2. Get a list of Schematic component instances and Schematic route instances in the document.
  3. Query for lists of connected objects.

#### Prolog

2. Get a list of Schematic component instances and Schematic route instances in the document.
3. Query for lists of connected objects.
The macro first loads the document: CAASCH_CompRoute01.CATProduct.  |     ...
```vbscript
```vbscript
    ' Open the schematic document

```

```

```vbscript
```vbscript
    Dim sFilePath
```vbscript
```
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

            "online/CAAScdSchUseCases/samples/CAASCH_CompRoute01.CATProduct")

```vbscript
```vbscript
Dim sFilePath
```vbscript
```
```vbscript
```vbscript
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
#### Get a list of Schematic component instances and Schematic route instances in the document

    ...
```vbscript
```vbscript
```vbscript
    ' -------------------------------------------------------------------------
    ' |  Get a list of all component instances and
    ' |  a list of all route instances in the model.
    ' -------------------------------------------------------------------------
```

```

```

```vbscript
    If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
```vbscript
       Set objSchLComps = objSchRoot.GetComponents
```vbscript
```
```vbscript
```vbscript
       Set objSchLRoutes = objSchRoot.GetRoutes
    End If
```
```

```

```

    ...

---
#### Query for lists of connected objects

```vbscript
```vbscript
For each member in the output list of component instants, the macro uses the AppListConnectables to find a list of Schematic component or route instances that are connected to the component instance member.

```

```

    ...
```vbscript
    If ( Not ( objSchLComps Is Nothing ) And _
```vbscript
         Not ( objSchRoot Is Nothing ) ) Then

```

```

```vbscript
If ( Not ( objSchLComps Is Nothing ) And _
```

Not ( objSchRoot Is Nothing ) ) Then
       intNb = objSchLComps.Count

    ...
```vbscript
       If (intNb > 0) Then
```

    ...

```vbscript
          For intIndex = 1 To intNb
```

    ...

```vbscript
```vbscript
```vbscript
            Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)

```
```

```

```vbscript
            If ( Not ( objAppCntbl Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
               '---------------------------------------------------------------
               '  AppListConnectables output 3 lists of objects.
               '
               '  If a component A is connected to another component B on
               '  one side and to a route C on the other side, then the
               '  output lists of objects will contain the following members.
               '
               '         objLCntblOther    objLCntrThis    objLCntrOther
               '         /--------------    /--------------  /----------------
               '           B               connector on A   connector on B
               '           C               connector on A   connector on C
               '---------------------------------------------------------------

```vbscript
               Set objLFilter = Nothing
```
```

```

```

               objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
                 objLCntrThis, objLCntrOther
    ...

---

```vbscript
For each member in the output list of route instants, the macro uses the AppListConnectables to find a list of Schematic component or route instances that are connected to the route instance member.
```

```vbscript
```vbscript
```vbscript
    '-------------------------------------------------------------------------
    ' |  For each route instance in the list, find connected objects
    '-------------------------------------------------------------------------
         If ( Not ( objSchLRoutes Is Nothing ) And _
```

```

```

```vbscript
```vbscript
```vbscript
' |  For each route instance in the list, find connected objects
'-------------------------------------------------------------------------
If ( Not ( objSchLRoutes Is Nothing ) And _
```

              Not ( objSchRoot Is Nothing ) ) Then

```

```

           intNb = objSchLRoutes.Count
    ...
```vbscript
           If (intNb > 0) Then
```

    ...
```vbscript
intNb = objSchLRoutes.Count
If (intNb > 0) Then
```vbscript
             For intIndex = 1 To intNb
```

```

    ...
```vbscript
```vbscript
               Set objAppCntbl = objSchRoot.GetInterface ("CATIASchAppConnectable",objPrd)
```vbscript
```
```vbscript
                 If ( Not ( objAppCntbl Is Nothing ) ) Then

```vbscript
                    Set objLFilter = Nothing

```
```

```

```

```vbscript
```vbscript
Set objLFilter = Nothing
                    objAppCntbl.AppListConnectables objLFilter, objLCntblOther, _
```
                      objLCntrThis, objLCntrOther
```

---

This macro provides the internal GenerateALine subroutine to report connected objects. It uses the GetPosition method of the SchCntrLocation interface to obtain the x-y coordinates of the connection points. SchCntrLocation is found based on the output list of connectors from the AppListConnectable method.

[Top]

* * *
#### In Short

This use case shows how to query the connectivity of Schematic objects in a Schematic document. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchQueryConnectivity_01.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
