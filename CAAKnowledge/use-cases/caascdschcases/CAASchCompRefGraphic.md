---
title: "Managing the Graphical Representation of a Schematic Reference Component"
category: "use-case"
module: "CAAScdSchUseCases"
tags: "["CAAScdSchUseCases", "CAASchCompRefGraphic", "CATIA", "CATIASchGRR", "CATIASchCompGraphic", "CAASCH_Detail03"]"
source_file: "Doc/online/CAAScdSchUseCases/CAASchCompRefGraphic.htm"
converted: "2026-05-11T17:31:51.330224"
---
## Schematics Platform Modeler

|
## Managing the Graphical Representation of a Schematic Reference Component

* * *

 This macro shows you how to manage the graphical representations (symbols) of a schematic reference component. This macro opens the document CAASCH_Detail03.CATProduct that contains three component symbols. One of the symbols (the highlighted one) has been associated with an existing schematic reference component. This macro shows how to add the other two unassociated symbols to the same reference component. It also illustrates how to remove one of the 3 symbols from the reference component and how to query for a list of associated symbols. ![](images/CAASchCompRefGraphic_01.jpg)
---|---
This macro shows you how to manage the graphical representations (symbols) of a schematic reference component. This macro opens the document CAASCH_Detail03.CATProduct that contains three component symbols. One of the symbols (the highlighted one) has been associated with an existing schematic reference component. This macro shows how to add the other two unassociated symbols to the same reference component. It also illustrates how to remove one of the 3 symbols from the reference component and how to query for a list of associated symbols. ![](images/CAASchCompRefGraphic_01.jpg)
 CAASchCompRefGraphic is launched in CATIA [1]. No open document is needed. [CAASchCompRefGraphic.CATScript ](CAASchCompRefGraphicSource.md) is located in the CAAScdSchUseCases module. [Execute macro](macros/CAASchCompRefGraphic.CATScript) (Windows only).
 CAASchCompRefGraphic includes the following steps:

  1. Prolog
  2. Find a schematic reference component in the model
  3. Add a graphical representation to the schematic reference component
  4. Query for a list of graphical representation of the schematic reference component
  5. Remove a graphical representation from the schematic reference component

#### Prolog

4. Query for a list of graphical representation of the schematic reference component
5. Remove a graphical representation from the schematic reference component
The macro first loads CAASCH_Detail03.CATProduct. |     ...
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
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, _
```
```

```

            "online/CAAScdSchUseCases/samples/CAASCH_Detail03.CATProduct")

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
#### Find a schematic reference component in the model

Using the GetRefComponents method, a list of existing schematic reference component in the model can be obtained. Note that the output of this method is a list of objects. The member of this list can be retrieved using the Item method. The second argument of this method specifies a particular interface to be returned on this member reference component. In this case it is the SchCompGraphic interface.

    ...
```vbscript
```vbscript
    Dim objLCompRefs As SchListOfObjects
```vbscript
```
```vbscript
```vbscript
    Dim objCompRefGraphic As SchCompGraphic

```
```

```

```

```vbscript
    If ( Not ( objSchRoot Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
       '-----------------------------------------------------------------------
       ' Find a list of reference component in the model
       '-----------------------------------------------------------------------
```vbscript
       Set objLCompRefs = objSchRoot.GetRefComponents
```
```

```

```

```vbscript
       If ( Not ( objLCompRefs Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
          '--------------------------------------------------------------------
          ' Get a SchCompGraphic interface handle from a reference
          ' component
          '--------------------------------------------------------------------
```cpp
          Set objCompRefGraphic = objLCompRefs.Item (1,"CATIASchCompGraphic")
```
```

```

```

    ...

---
#### Add a graphical representation to the schematic reference component

The macro calls GetComponentSymbol to find a symbol that has not been associated with any reference component. Using the symbol, it then calls AddGraphicalRepresentation to add this symbol to the reference component. This method is called a second time to add the third symbol. At this point, the reference component has three graphical representations.

    ...
```vbscript
```vbscript
              Dim objUnassocSymbol As AnyObject
```
```

```vbscript
```vbscript
```vbscript
              '----------------------------------------------------------------
              ' Find a symbol that is not associated with any reference in
              ' the model
              '----------------------------------------------------------------
```vbscript
              Set objUnassocSymbol = GetComponentSymbol (objSchRoot)
```
```

```

```

```vbscript
              If ( Not ( objUnassocSymbol Is Nothing ) ) Then
```

```vbscript
```vbscript
```vbscript
                '--------------------------------------------------------------
                '  Add the second graphical representation to the reference
                '  component using the symbol just found
                '--------------------------------------------------------------
```

```

```

```vbscript
```vbscript
```vbscript
'  Add the second graphical representation to the reference
'  component using the symbol just found
'--------------------------------------------------------------
```

```

                objCompRefGraphic.AddGraphicalRepresentation objUnassocSymbol

```

    ...

---
#### Query for a list of graphical representation of the schematic reference component

ListGraphicalRepresentation returns a list of graphical representations. This list should contains three members.

    ...
```vbscript
```vbscript
              Dim objLGraphic As SchListOfObjects
```vbscript
```
```vbscript
              Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
```
```

```

    ...

---
#### Remove a graphical representation from the schematic reference component

The macro finds the first member of the list of graphical representations obtained from previous step and call RemoveGraphicalRepresentation to remove that symbol from the reference component.

    ...
```vbscript
```vbscript
                 Set objGRR = Nothing
```vbscript
```
```vbscript
                 If (intNbGraphic > 1) Then
```cpp
                    Set objGRR = objLGraphic.Item(intNbGraphic,"CATIASchGRR")
                    If ( Not (objGRR Is Nothing ) ) Then
```
```

```

                       objCompRefGraphic.RemoveGraphicalRepresentation objGRR
```vbscript
                       Set objLGraphic = objCompRefGraphic.ListGraphicalRepresentations
```vbscript
```
                       If ( Not ( objLGraphic Is Nothing ) ) Then
```

                          intNbGraphic = objLGraphic.Count
                          strMessage = strMessage & "Number of graphical representations"
                          strMessage = strMessage & "after calling "
                          strMessage = strMessage & " RemoveGraphicalRepresentation = " & intNbGraphic & vbCr
                       End If
```vbscript
```vbscript
                    End If
                 End If ' --- If (intNbGraphic > 1)
              End If '--- If ( Not ( objLGraphic Is Nothing ) ) Then

```

```

```

    ...

---

[Top]

* * *
#### In Short

This use case shows how to add, remove and query for a list of graphical representations of a schematic reference component. A message logging the status of the critical steps is displayed at the end of the use case.

![](images/CAASchCompRefGraphic_02.jpg)

[Top]

* * *
#### References

[1] | [ Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
