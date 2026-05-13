---
```vbscript
title: "CAAAniMeshSelectFEEntity.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSelectFEEntity", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSelectFEEntitySource.htmmd"
converted: "2026-05-11T17:31:51.697182"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:      Open an analysis document
    '                Select a mesh element
    '                Select a mesh node
    '  Assumptions:   Looks for AllElementsAndNode.CATAnalysis in the directory
    '  Author:       jgw
    '  Languages:    VBScript
    '  Locales:      English
    '  CATIA Level:  V5R21
    '***********************************************************************
```

```

```

```vbscript
    Sub CATMain(#)
```vbscript
```
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```
```

```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
        End If
```

```

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Open the Analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/AllElementsAndNode.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    'Retrieve the Selection object
```
```vbscript
    Set oSelection = oAnalysisDocument.Selection

    Dim InputObjectType(0)
    'Set the selection type
```
```

```

```

```vbscript
```vbscript
Dim InputObjectType(0)
```vbscript
```
```vbscript
'Set the selection type
    InputObjectType(0) = "AnalysisMeshElement"
```
```

```

```vbscript
```vbscript
```vbscript
    'Get the status
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh element", True )
    'Get the object in the selection
```vbscript
    Set oMeshElement = oSelection.Item(1).Value
    'Display message
```
```

```

```

```vbscript
```vbscript
```vbscript
'Get the object in the selection
```vbscript
Set oMeshElement = oSelection.Item(1).Value
'Display message
```
```

```

```vbscript
    MsgBox "Selected element: " & oMeshElement.Name
```vbscript
```
    'Clear selection
```

    oSelection.Clear
```vbscript
```vbscript
    'Set the selection type
    InputObjectType(0) = "AnalysisMeshNode"
```
```

```

```vbscript
```vbscript
```vbscript
    'Get the status
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh node", True )
    'Get the object in the selection
```vbscript
    Set oMeshNode = oSelection.Item(1).Value
    'Display message
```
```

```

```

```vbscript
```vbscript
```vbscript
'Get the object in the selection
```vbscript
Set oMeshNode = oSelection.Item(1).Value
'Display message
```
```

```

```vbscript
    MsgBox "Selected node: " & oMeshNode.Name
```vbscript
```
    'Clear selection
```

    oSelection.Clear

```

```vbscript
```vbscript
    End Sub

```
```
