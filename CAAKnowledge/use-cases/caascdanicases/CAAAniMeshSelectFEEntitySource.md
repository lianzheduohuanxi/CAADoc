---
```vbscript
title: "CAAAniMeshSelectFEEntity.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSelectFEEntity", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSelectFEEntitySource.htm"
converted: "2026-05-11T17:31:51.697182"
```

---
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

    Sub CATMain()
    '----------------------------------------------------------- 
    'Optional: allows to find the sample wherever it's installed

      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```

```vbscript
    '----------------------------------------------------------- 
    'Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\AllElementsAndNode.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    'Retrieve the Selection object
    Set oSelection = oAnalysisDocument.Selection

    Dim InputObjectType(0)
    'Set the selection type
```

```vbscript
Dim InputObjectType(0)
'Set the selection type
    InputObjectType(0) = "AnalysisMeshElement"
```

```vbscript
    'Get the status
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh element", True )
    'Get the object in the selection
    Set oMeshElement = oSelection.Item(1).Value
    'Display message
```

```vbscript
'Get the object in the selection
Set oMeshElement = oSelection.Item(1).Value
'Display message
    MsgBox "Selected element: " & oMeshElement.Name
    'Clear selection
    oSelection.Clear
    'Set the selection type
    InputObjectType(0) = "AnalysisMeshNode"
```

```vbscript
    'Get the status
    oStatus = oSelection.SelectElement2 ( InputObjectType, "Select a mesh node", True )
    'Get the object in the selection
    Set oMeshNode = oSelection.Item(1).Value
    'Display message
```

```vbscript
'Get the object in the selection
Set oMeshNode = oSelection.Item(1).Value
'Display message
    MsgBox "Selected node: " & oMeshNode.Name
    'Clear selection
    oSelection.Clear 

```

    End Sub
