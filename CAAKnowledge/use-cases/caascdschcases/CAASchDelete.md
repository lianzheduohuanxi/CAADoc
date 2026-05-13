---
```vbscript
title: "Deleting Schematic Objects"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CAADoc", "CAASCH_Delete01", "CAAScdSchUseCases", "CAASchDelete", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CATIASchRoute", "CAASchPlatformModeler", "CATIASchAppConnectable", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchDelete.htmmd"
converted: "2026-05-11T17:31:51.359152"
```

---
## Schematics Platform Modeler

|
## Deleting Schematic Objects

* * *

 This macro shows you how to delete Schematic objects.This macro opens the document CAASCH_Delete01.CATProduct. It contains a schematic component that is connected to a schematic route at both ends (the highlighted object in the screen shot below). Notice that the instance name of this component has the word "delete" embedded in it. This word identifies the object to be deleted to the macro. ![](images/CAASchDelete_01.jpg)
---|---
 CAASchDelete is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

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

[ CAASchDelete.CATScript i](CAASchDeleteSource.md)s located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchDelete.CATScript) (Windows only).
 CAASchDelete includes the following steps:

CAASchDelete includes the following steps:
  1. Prolog
  2. Delete a Schematic component
  3. Delete a Schematic route

#### Prolog

2. Delete a Schematic component
3. Delete a Schematic route
The macro first loads CAASCH_Delete01.CATProduct. |     ...
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

            "online/CAAScdSchUseCases/samples/CAASCH_Delete01.CATProduct")

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

Using the GetSchBaseFactory method, a SchBaseFact interface handle is obtained. The DeleteObject method of this interface is used in the next step.

    ...
```vbscript
```vbscript
```vbscript
    Dim objSchBaseFact As SchBaseFactory

```
```

```

```vbscript
```vbscript
    If ( Not ( objSchRoot Is Nothing ) ) Then

```vbscript
       Set objSchBaseFact = objSchRoot.GetSchBaseFactory
```
```

```

    ...

---
#### Delete a Schematic component

The macro finds the component to be deleted in the private FindComponentInst function. This is based on a naming convention on the Schematic component. FindComponentInst returns the first instance whose name has the word "delete" embedded in it. The macro calls DeleteObject to delete the component.

    ...
```vbscript
```vbscript
       If ( Not ( objSchBaseFact Is Nothing ) ) Then

```

```

```vbscript
```vbscript
```vbscript
          Set objSchComp = FindComponentInst (objSchRoot)

```
```

```

```vbscript
```vbscript
          If ( Not ( objSchComp Is Nothing ) ) Then

```

```

             objSchBaseFact.DeleteObject objSchComp

    ...

---
#### Delete a Schematic route

The word "inserted" in the comment below is used to describe a situation where a Schematic component is connected to two Schematic routes through two of its connectors. These connectors must be internally connected to each other by an "internal flow" object. The latter is aggregated by the Schematic component. For example, the highlighted "valve" in the screen shot of the current document above has been inserted into the route.

    ...
```vbscript
```vbscript
```vbscript
       '-----------------------------------------------------------------------
       '  In this specific input model, we expects to find a component
       '  instance that has been inserted into a route.
       '
       '  After this component instance is deleted, the two routes on
       '  each side of the deleted component will be concatenated by the
       '  system to become one.
       '
       '-----------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
       Set objLRoutes = objSchRoot.GetRoutes
```
```

   ...

---

This macro uses a private FindOpenConnector function to find the 2 unconnected ends of the 2 routes that are connected to each ends of the component before it is deleted. With these 2 ends, the Concatenate method of the SchRoute interface is then called to connect the 2 route into one. Note that the input SchRoute interface handle (in this case, the objRoute2) will be deleted implicitly by the Concatenate method.

```vbscript
```vbscript
       Set objLRoutes = objSchRoot.GetRoutes
```vbscript
```
       If ( Not ( objLRoutes Is Nothing ) ) Then
```

          intNbRouteAfter = objLRoutes.Count
          strMessage = strMessage & "Number of routes in the model "
          strMessage = strMessage & "after deleting an inserted component "
          strMessage = strMessage & " = " & intNbRouteAfter & vbCr

```vbscript
          Dim  objRoute1 As SchRoute
```vbscript
```
```vbscript
```vbscript
          Dim  objRoute2 As SchRoute

          Dim  objRCntbl1 As SchConnectable
          Dim  objRCntbl2 As SchConnectable

          Dim  objAppRCntr1 As SchAppConnector
          Dim  objAppRCntr2 As SchAppConnector

```
```

```

```

```vbscript
```vbscript
Dim  objAppRCntr1 As SchAppConnector
```vbscript
```
```vbscript
```vbscript
Dim  objAppRCntr2 As SchAppConnector
          If  ( intNbRouteAfter > 0 ) Then
```
```

```

```

```vbscript
```vbscript
```vbscript
             Set objRoute1 = objLRoutes.Item (1, "CATIASchRoute")

```
```

```

```vbscript
             If ( Not ( objRoute1 Is Nothing ) ) Then
```vbscript
```vbscript
                Set objRCntbl1 = objSchRoot.GetInterface ( _
```
```

```

                  "CATIASchAppConnectable", objRoute1)
```vbscript
If ( Not ( objRoute1 Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
Set objRCntbl1 = objSchRoot.GetInterface ( _
                If ( Not ( objRCntbl1 Is Nothing ) ) Then
```
```vbscript
                   Set objAppRCntr1 = FindOpenConnector (objSchRoot,objRCntbl1)
                   Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                End If
```
             End If
             If ( Not ( objRoute2 Is Nothing ) ) Then
```vbscript
                Set objRCntbl2 = objSchRoot.GetInterface ( _
```
```

```

```

                  "CATIASchAppConnectable", objRoute2)
```vbscript
End If
```

End If
```vbscript
If ( Not ( objRoute2 Is Nothing ) ) Then
```vbscript
```vbscript
```vbscript
Set objRCntbl2 = objSchRoot.GetInterface ( _
                If ( Not ( objRCntbl2 Is Nothing ) ) Then
```
```vbscript
                   Set objAppRCntr2 = FindOpenConnector (objSchRoot,objRCntbl2)
                End If
```
             End If

```

```

```

```vbscript
             If ( Not ( objRoute1 Is Nothing ) And _
```vbscript
                   Not ( objAppRCntr1 Is Nothing ) And _
                   Not ( objAppRCntr2 Is Nothing ) ) Then
```vbscript
```vbscript
                Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
                If ( Not ( objRoute2 Is Nothing ) ) Then
```
```

```

                    objRoute1.Concatenate objAppRCntr1, objRoute2, objAppRCntr2
```

                    ...
Not ( objAppRCntr2 Is Nothing ) ) Then
```vbscript
```vbscript
Set objRoute2 = objLRoutes.Item (2, "CATIASchRoute")
```
```

If ( Not ( objRoute2 Is Nothing ) ) Then
objRoute1.Concatenate objAppRCntr1, objRoute2, objAppRCntr2
```vbscript
                End If
```vbscript
```vbscript
             End If
          End If
       End If  '--- If ( Not ( objLRoutes Is Nothing ) ...

```

```

```

    ...

---

[Top]

* * *
#### In Short

This use case shows how to delete Schematic objects. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchDelete_02.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
