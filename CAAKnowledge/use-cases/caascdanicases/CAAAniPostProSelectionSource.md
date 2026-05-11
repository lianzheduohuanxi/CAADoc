---
title: "CAAAniPostProSelection.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniPostProSelection"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProSelectionSource.htm"
converted: "2026-05-11T17:31:51.768504"
---

```vbscript
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

    
```vbscript
    Sub CATMain()
```vbscript
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    ' ----------------------------------------------------------- 
    
```

    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
```

    ' Retrieve the Analysis Manager
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
    
```

    
    ' Retrieve the analysis model from the list of models
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```vbscript
    ' Retrieve the analysis cases and the first analysis case
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    ' Retrieve the analysis sets and analysis set by its name
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Restraints.1", catAnalysisSetSearchAll)
    
    Set analysisEntities1 = oAnalysisSet.AnalysisEntities
    Set analysisEntity1 = analysisEntities1.Item(1)
    'add selection (specificationgroups)  clamp on Image Von Mises Stress (nodal values) (no selection before ReplaceMode=True)
    '============================================================================
    
    Set reference1 = oAnalysisManager.CreateReferenceFromObject(analysisEntity1)
    
    Set analysisSet2 = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    Set analysisImages1 = analysisSet2.AnalysisImages
    Set analysisImage1 = analysisImages1.Item("Von Mises Stress (nodal values).1")
```

    analysisImage1.SetSelection reference1, True
    analysisImage1.Update 
```vbscript
    'add selection (usergroups) SurfaceGroup.1 on Image Von Mises Stress (nodal values) (ReplaceMode=False)
    '=====================================================================
    ' Get the list of groups and create reference from first group
    Set analysisSets2 = oAnalysisModel.AnalysisSets
    Set analysisSet3 = analysisSets2.ItemByType("GroupSet")
    Set analysisEntities2 = analysisSet3.AnalysisEntities
    Set analysisEntity2 = analysisEntities2.Item(1)
    Set reference2 = oAnalysisManager.CreateReferenceFromObject(analysisEntity2)
```

    
```

    ' Set the created reference for Selection in Von Mises Stress Image
    analysisImage1.SetSelection reference2, False
    analysisImage1.Update 
```vbscript
    'remove all selections on Image Von Mises Stress (nodal values)
    '======================================
    ' Remove all the selections and update
```

    analysisImage1.ResetSelection 
    analysisImage1.Update 
```vbscript
    'add selection (meshparts) OctreeTetrahedronMesh.1:Part1 on Image Von Mises Stress (nodal values) (ReplaceMode=True)
    '==========================================================================
    ' Retrieve the mesh part OCTREE Tetrahedron Filler
```

```vbscript
    Set analysisSets3 = oAnalysisModel.AnalysisSets
    Set oAnalysisMeshManager = analysisSets3.ItemByType("MSHMeshSet")
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set analysisMeshPart1 = oAnalysisMeshParts.Item("OCTREE Tetrahedron Mesh.1 : Part1")
    
```

    
    'Create reference from the mesh part and set the selection
```vbscript
    Set reference3 = oAnalysisManager.CreateReferenceFromObject(analysisMeshPart1)
    analysisImage1.SetSelection reference3, True
    analysisImage1.Update 
    
```

```vbscript
    End Sub
    
```

```