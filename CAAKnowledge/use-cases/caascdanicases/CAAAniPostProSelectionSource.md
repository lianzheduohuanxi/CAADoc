---
title: "CAAAniPostProSelection.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAScdAniUseCases", "CAAAniPostProSelection"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProSelectionSource.htm"
converted: "2026-05-11T17:31:51.768504"
---
```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Select groups and mesh part for visualization of image
    '   Assumptions:   Octree tetrahedron mesh part exists in the model
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
End If
```vbscript
```cpp
' -----------------------------------------------------------
    ' Open the CATAnalysis Document
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
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
    ' Retrieve the Analysis Manager
```

```

```vbscript
```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
```
    ' Retrieve the analysis model from the list of models
```

```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
    Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```

```vbscript
```vbscript
```vbscript
    ' Retrieve the analysis cases and the first analysis case
```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    ' Retrieve the analysis sets and analysis set by its name
```
```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)

    Set analysisEntities1 = oAnalysisSet.AnalysisEntities
    Set analysisEntity1 = analysisEntities1.Item(1)
    'add selection (specificationgroups)  clamp on Image Von Mises Stress (nodal values) (no selection before ReplaceMode=True)
```
    '============================================================================

```vbscript
    Set reference1 = oAnalysisManager.CreateReferenceFromObject(analysisEntity1)

    Set analysisSet2 = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    Set analysisImages1 = analysisSet2.AnalysisImages
    Set analysisImage1 = analysisImages1.Item("Von Mises Stress (nodal values).1")
```
```

```

```

```vbscript
```vbscript
Set analysisSet2 = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
```vbscript
```
```vbscript
```vbscript
Set analysisImages1 = analysisSet2.AnalysisImages
Set analysisImage1 = analysisImages1.Item("Von Mises Stress (nodal values).1")
```
```

```

    analysisImage1.SetSelection reference1, True
    analysisImage1.Update
```

```vbscript
```vbscript
```vbscript
    'add selection (usergroups) SurfaceGroup.1 on Image Von Mises Stress (nodal values) (ReplaceMode=False)
    '=====================================================================
    ' Get the list of groups and create reference from first group
```vbscript
    Set analysisSets2 = oAnalysisModel.AnalysisSets
    Set analysisSet3 = analysisSets2.ItemByType("GroupSet")
    Set analysisEntities2 = analysisSet3.AnalysisEntities
    Set analysisEntity2 = analysisEntities2.Item(1)
    Set reference2 = oAnalysisManager.CreateReferenceFromObject(analysisEntity2)
```
```

```

```

```vbscript
```vbscript
```vbscript
    ' Set the created reference for Selection in Von Mises Stress Image
```
```

    analysisImage1.SetSelection reference2, False
    analysisImage1.Update
```

```vbscript
```vbscript
```vbscript
    'remove all selections on Image Von Mises Stress (nodal values)
    '======================================
    ' Remove all the selections and update
```

```

```

```vbscript
```vbscript
```vbscript
'remove all selections on Image Von Mises Stress (nodal values)
'======================================
' Remove all the selections and update
```

```

    analysisImage1.ResetSelection
    analysisImage1.Update
```

```vbscript
```vbscript
```vbscript
    'add selection (meshparts) OctreeTetrahedronMesh.1:Part1 on Image Von Mises Stress (nodal values) (ReplaceMode=True)
    '==========================================================================
    ' Retrieve the mesh part OCTREE Tetrahedron Filler
```

```

```

```vbscript
```vbscript
    Set analysisSets3 = oAnalysisModel.AnalysisSets
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisMeshManager = analysisSets3.ItemByType("MSHMeshSet")
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set analysisMeshPart1 = oAnalysisMeshParts.Item("OCTREE Tetrahedron Mesh.1 : Part1")

```
```

```

```

```vbscript
```vbscript
Set analysisMeshPart1 = oAnalysisMeshParts.Item("OCTREE Tetrahedron Mesh.1 : Part1")
```vbscript
```
    'Create reference from the mesh part and set the selection
```

```

```vbscript
```vbscript
    Set reference3 = oAnalysisManager.CreateReferenceFromObject(analysisMeshPart1)
    analysisImage1.SetSelection reference3, True
```
    analysisImage1.Update

```

```vbscript
```vbscript
    End Sub

```
```
