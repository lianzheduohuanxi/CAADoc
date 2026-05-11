---
```vbscript
title: "Managing Internal Flow in a Schematic Reference Component"
category: "use-case"
module: "CAAScdSchUseCases"
tags: ["CATIASchCompFlow", "CAADoc", "CAASchInternalFlow", "CATIASchComponent", "CAAScdSchUseCases", "CATIA", "CAASchAppBase", "CAASCHEDUApp", "CAASchPlatformModeler", "CATIASchAppConnector", "CAASCH_Detail02", "CAASchAppUtilities"]
source_file: "Doc/online/CAAScdSchUseCases/CAASchInternalFlow.htm"
converted: "2026-05-11T17:31:51.390076"
```

---
## Schematics Platform Modeler

|
## Managing Internal Flow in a Schematic Reference Component

* * *

 This macro shows you how to manage internal flow objects aggregated under a Schematic reference component. This includes the following.

This macro shows you how to manage internal flow objects aggregated under a Schematic reference component. This includes the following.
  1. Adding an internal flow object to the reference component.
  2. Querying for a list of existing internal flow objects.
  3. Removing an internal flow object from the reference component.

In order for the instance of a Schematic reference component to be capable of being inserted into a route, the reference component must have at least one compatible internal flow object. An internal flow object references two connectors of the reference component. Through their connector positions, the orientation of the instance in the route is defined. This macro opens the CAASCH_Detail02.CATProduct document. The following screen shot shows an internal flow of a Schematic reference component. Notice the two connectors (in this case - Connector.1 and Connector.2) that must be defined. ![](images/CAASchInternalFlow_01.jpg)

2. Querying for a list of existing internal flow objects.
3. Removing an internal flow object from the reference component.
In order for the instance of a Schematic reference component to be capable of being inserted into a route, the reference component must have at least one compatible internal flow object. An internal flow object references two connectors of the reference component. Through their connector positions, the orientation of the instance in the route is defined. This macro opens the CAASCH_Detail02.CATProduct document. The following screen shot shows an internal flow of a Schematic reference component. Notice the two connectors (in this case - Connector.1 and Connector.2) that must be defined. ![](images/CAASchInternalFlow_01.jpg)
 CAASchInternalFlow is launched in CATIA [1]. No open document is needed.Special environment must be available to successfully run this macro:

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

[ CAASchInternalFlow.CATScript ](CAASchInternalFlowSource.md)is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchInternalFlow.CATScript) (Windows only).
 CAASchInternalFlow includes the following steps:

CAASchInternalFlow includes the following steps:
  1. Prolog
  2. Add an internal flow object to the Schematic reference component
  3. Query for a list of existing internal flow objects of a Schematic reference component
  4. Remove an internal flow objects from the Schematic reference component

#### Prolog

3. Query for a list of existing internal flow objects of a Schematic reference component
4. Remove an internal flow objects from the Schematic reference component
The macro first loads CAASCH_Detail02.CATProduct. |     ...
```vbscript
```vbscript
    ' Open main schematic P&ID design document (for new component instances created here)

```

```

```vbscript
    Dim sFilePath
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```

```

            "online\CAAScdSchUseCases\samples\CAASCH_Detail02.CATProduct")

```vbscript
Dim sFilePath
```vbscript
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
    Dim objSchDoc As Document
    Set objSchDoc = CATIA.Documents.Open(sFilePath)
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
    Dim objPrdRoot As Product
```vbscript
```vbscript
    Dim objSchRoot As SchematicRoot
    If ( Not ( objSchDoc Is Nothing ) ) Then
      Set objPrdRoot = objSchDoc.Product
      If ( Not ( objPrdRoot Is Nothing ) ) Then
        Set objSchRoot = objPrdRoot.GetTechnologicalObject("SchematicRoot")
      End If
    End If
```

```

```

    ...

---

The SchematicRoot interface provides the GetRefComponents method to find a list of all the Schematic reference component in the model. The macro takes the first one in the list and specifically requests for the SchComponent interface on the first member.

    ...
```vbscript
```vbscript
```vbscript
       '-----------------------------------------------------------------------
       ' Find a list of reference component in the model
       '-----------------------------------------------------------------------
```

```

```

```vbscript
```vbscript
       Set objLCompRefs = objSchRoot.GetRefComponents

```

```

```vbscript
```vbscript
       If ( Not ( objLCompRefs Is Nothing ) ) Then

          Set objCompRef = objLCompRefs.Item (1,"CATIASchComponent")
```

```

    ...

---
#### Add an internal flow object to the Schematic reference component

The macro calls the GetInterface method to get a handle on the reference component for the SchCompFlow interface.

```vbscript
              Set objCompFlow = objSchRoot.GetInterface ( _
```

                "CATIASchCompFlow",objCompRef)

---

Next, the macro get a list of all connectors of the Schematic Component.
```vbscript
```vbscript
```vbscript
             '-----------------------------------------------------------------
             ' Find all the connectors associated with the reference
             ' component
             '-----------------------------------------------------------------
```

```

```

    ...
```vbscript
             Set objLCntr = objCntbl.AppListConnectors (objLFilter)
```

    ...

---

Method CreateListOfObject is called to create a list of connectors containing the first and the second connectors. This list is used as input to the AddInternalFlow method to add an internal flow object to the reference component..

    ...
```vbscript
```vbscript
```vbscript
             '-----------------------------------------------------------------
             ' Add internal flow to the reference component.
             ' 2 pairs:
             ' Flow 1: connector 1 to connector 2
             ' Flow 2: connector 1 to connector 3
             '-----------------------------------------------------------------
```

```

```

   ...
```vbscript
             Dim objFlow1 As SchInternalFlow
```vbscript
```vbscript
             Dim objFlow2 As SchInternalFlow
             Dim objCntr1 As SchAppConnector
             Dim objCntr2 As SchAppConnector
             Dim objCntr3 As SchAppConnector
             Dim objLCntr1 As SchListOfObjects
             Dim objLCntr2 As SchListOfObjects
             Dim objLFlow As SchListOfObjects

```

```

```

```vbscript
Dim objLCntr2 As SchListOfObjects
```vbscript
Dim objLFlow As SchListOfObjects
```

             intNbCntr = objLCntr.Count
```

```vbscript
             Set objLCntr1 = objSchTempListFact.CreateListOfObjects
```vbscript
```vbscript
             Set objLCntr2 = objSchTempListFact.CreateListOfObjects

             Set objCntr1 = Nothing
             Set objCntr2 = Nothing
             Set objCntr3 = Nothing

```

```

```

```vbscript
             If ( intNbCntr > 0 ) Then Set objCntr1 = objLCntr.Item(1,"CATIASchAppConnector")
```vbscript
```vbscript
             If ( intNbCntr > 1 ) Then Set objCntr2 = objLCntr.Item(2,"CATIASchAppConnector")
             If ( intNbCntr > 2 ) Then Set objCntr3 = objLCntr.Item(3,"CATIASchAppConnector")

             Set objFlow1 = Nothing
             If ( Not objLCntr1 Is Nothing ) Then
                If ( Not ( objCntr1 Is Nothing ) And _
```

                     Not ( objCntr2 Is Nothing ) ) Then
```

                   objLCntr1.Append (objCntr1)
                   objLCntr1.Append (objCntr2)
                   Set objFlow1 = objCompFlow.AddInternalFlow (objLCntr1)
```

    ...

---

Similarly, the macro creates a second list of connectors containing the first and the third connectors. This list is used as input to the AddInternalFlow method to add the second internal flow object to the reference component.

    ...
```vbscript
             Set objFlow2 = Nothing
```vbscript
```vbscript
             If ( Not objLCntr2 Is Nothing ) Then
                If ( Not ( objCntr1 Is Nothing ) And _
```

                     Not ( objCntr3 Is Nothing ) ) Then
```

                   objLCntr2.Append (objCntr1)
                   objLCntr2.Append (objCntr3)
                   Set objFlow2 = objCompFlow.AddInternalFlow (objLCntr2)
```

    ...

---
#### Query for a list of existing internal flow objects of a Schematic reference component

    ...
```vbscript
```vbscript
```vbscript
            '-----------------------------------------------------------------
            ' Return a list of all the internal flows
            ' associated to the reference component. There should be 2.
            '-----------------------------------------------------------------
```

```

```

```vbscript
                  Set objLFlow = objCompFlow.ListInternalFlows
```

    ...

---
#### Remove an internal flow objects from the Schematic reference component

    ...
```vbscript
                If ( Not ( objFlow2 Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
                   '-----------------------------------------------------------------
                   ' Remove "Flow 2" from the reference component
                   '-----------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'-----------------------------------------------------------------
' Remove "Flow 2" from the reference component
'-----------------------------------------------------------------
```

```

                   objCompFlow.RemoveInternalFlow objFlow2
                End If
```

    ...

---

[Top]

* * *
#### In Short

This use case shows how to manage internal flow objects of a Schematic reference component. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchInternalFlow_02.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
