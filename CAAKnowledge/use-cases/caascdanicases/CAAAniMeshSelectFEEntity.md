---
```vbscript
title: "Selecting a mesh entity (node, element)"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSelectFEEntity", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSelectFEEntity.htm"
converted: "2026-05-11T17:31:51.695188"
```

---
## Analysis Modeler

|
## Selecting a mesh entity (node, element)

* * *

  This use case shows you how to select a mesh entity (node, element) using the **Selection** object. This scenario requires "GPS" product. The macro open an Analysis document. User is prompted to select a mesh element then to select a mesh node. After each selection a panel displays the mesh entity tag. ![](images/AllElementsModel.jpg)
---|---
This use case shows you how to select a mesh entity (node, element) using the **Selection** object. This scenario requires "GPS" product. The macro open an Analysis document. User is prompted to select a mesh element then to select a mesh node. After each selection a panel displays the mesh entity tag. ![](images/AllElementsModel.jpg)
  CAAAniMeshSelectFEEntity is launched in CATIA [1]. No open document is needed. [CAAAniMeshSelectFEEntity.catvbs](CAAAniMeshSelectFEEntitySource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshSelectFEEntity.catvbs) (Windows only).
  CAAAniMeshSelectFEEntity includes the following steps:

  1. Prolog
  2. Selecting a mesh element
  3. Selecting a mesh node
  4. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```

```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```vbscript
        End If
    '-----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```vbscript
'-----------------------------------------------------------
    'Open the Analysis document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\AllElementsAndNode.CATAnalysis")
```

```

```

```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```

```

```vbscript
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
    'Get the Selection object
```

```

```vbscript
```vbscript
    Set oSelection = oAnalysisDocument.Selection

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path is already stored in the `sDocPath` variable. If this variable is not valuated then error is raised. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. The **Selection** object is retrieved from the Analysis document.
#### Selecting a mesh element

    ...

```vbscript
    'Set the selection type
```

```vbscript
```vbscript
'Set the selection type
    InputObjectType(0) = "AnalysisMeshElement"
```

```

```vbscript
```vbscript
```vbscript
    'Get the status
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh element", True )
    'Get the object in the selection
```

```

```

```vbscript
```vbscript
    Set oMeshElement = oSelection.Item(1).Value

```

```

    ...

---

User is prompted to select a mesh element. The filter **AnalysisMeshElement** allows to select either a mesh element, a mesh edge or a mesh node.
#### Selecting a mesh node.

    ...

```vbscript
    'Set the selection type
```

```vbscript
```vbscript
'Set the selection type
    InputObjectType(0) = "AnalysisMeshNode"
```

```

```vbscript
```vbscript
```vbscript
    'Get the status
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh node", True )
    'Get the object in the selection
```

```

```

```vbscript
```vbscript
    Set oMeshNode = oSelection.Item(1).Value

```

```

    ...

---
#### User is prompted to select a mesh node. The filter **AnalysisMeshNode** allows to select a mesh node that does not belong to a mesh element.
#### Epilog

    ...
     End Sub
    ...

---

To run the macro interactively CATDocView environment variables must be defined.

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to use the **Selection** object in order to select mesh entites.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
