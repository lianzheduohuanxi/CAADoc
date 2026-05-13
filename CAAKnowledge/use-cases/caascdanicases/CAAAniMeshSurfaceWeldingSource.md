---
title: "CAAAniMeshSurfaceWelding.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniMeshSurfaceWelding", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSurfaceWeldingSource.htm"
converted: "2026-05-11T17:31:51.708641"
---
```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Open an analysis document
    '                 Create Surface welding connection mesh part
    '                 assign the surface analysis connection as support
    '                 specify the global specifications
    '   Assumptions:   Looks for WeldConnection.CATAnalysis in the directory and surface Analysis Connection
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R16
    ' ***********************************************************************
```

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```cpp
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```

```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
```vbscript
        End If
    ' -----------------------------------------------------------

```

```

```

```vbscript
```vbscript
```cpp
' -----------------------------------------------------------
    ' Open the CATAnalysis Document
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
```cpp
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```
```

```

```vbscript
```cpp
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
```
    ' Retrieve the analysis Manager
```

```

```vbscript
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
```vbscript
```
```vbscript
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```
```

```

```vbscript
```vbscript
```vbscript
    ' Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    ' Retrieve the analysis model
```
```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
```
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```
```

```

```

```vbscript
    'Retrieve the connection design manager and connection
```

```vbscript
```vbscript
    Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
```vbscript
```
```vbscript
```vbscript
    Set connSet = connection.AnalysisSets
    Set conn = connSet.ItemByType("ConnectionDesignSet")
    Set entity = conn.AnalysisEntities
    Set surfConn  = entity.Item(3)
```
```

```

```

```vbscript
```vbscript
```vbscript
    'Create reference from the surface analysis connection
```vbscript
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
    'Add new surface analysis connection mesh to the list of mesh parts
```
```vbscript
    Set surfWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSurf")
    'Assign previously created reference as support
```
```

```

```

```vbscript
```vbscript
```vbscript
'Add new surface analysis connection mesh to the list of mesh parts
```vbscript
Set surfWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSurf")
'Assign previously created reference as support
```
```

```

    surfWeld.AddSupportFromReference NOTHING, reference1
```vbscript
    'Assign values to its global attributes
```

    surfWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
    surfWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
    surfWeld.SetGlobalSpecification "StopUpdateOnError", 2
    surfWeld.SetGlobalSpecification "MiddleCombination", 10
```vbscript
    'Update the mesh part
```

    surfWeld.Update

```

```vbscript
```vbscript
    End Sub

```
```
