---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAAniPostProSelection", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProSelectionSource.htm"
converted: "2026-05-11T11:27:02.525163"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Select groups and mesh part for visualization of image
'   Assumptions:   Octree tetrahedron mesh part exists in the model
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

Sub CATMain()

' ----------------------------------------------------------- 
' Optional: allows to find the sample wherever it's installed
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the Analysis Manager
Set oAnalysisManager = oAnalysisDocument.Analysis

' Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

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
analysisImage1.SetSelection reference1, True
analysisImage1.Update 

'add selection (usergroups) SurfaceGroup.1 on Image Von Mises Stress (nodal values) (ReplaceMode=False)
'=====================================================================

' Get the list of groups and create reference from first group
Set analysisSets2 = oAnalysisModel.AnalysisSets
Set analysisSet3 = analysisSets2.ItemByType("GroupSet")
Set analysisEntities2 = analysisSet3.AnalysisEntities
Set analysisEntity2 = analysisEntities2.Item(1)
Set reference2 = oAnalysisManager.CreateReferenceFromObject(analysisEntity2)

' Set the created reference for Selection in Von Mises Stress Image
analysisImage1.SetSelection reference2, False
analysisImage1.Update 

'remove all selections on Image Von Mises Stress (nodal values)
'======================================

' Remove all the selections and update
analysisImage1.ResetSelection 
analysisImage1.Update 

'add selection (meshparts) OctreeTetrahedronMesh.1:Part1 on Image Von Mises Stress (nodal values) (ReplaceMode=True)
'==========================================================================

' Retrieve the mesh part OCTREE Tetrahedron Filler
Set analysisSets3 = oAnalysisModel.AnalysisSets
Set oAnalysisMeshManager = analysisSets3.ItemByType("MSHMeshSet")
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set analysisMeshPart1 = oAnalysisMeshParts.Item("OCTREE Tetrahedron Mesh.1 : Part1")

'Create reference from the mesh part and set the selection
Set reference3 = oAnalysisManager.CreateReferenceFromObject(analysisMeshPart1)
analysisImage1.SetSelection reference3, True
analysisImage1.Update 

End Sub



```vbscript
&#39; COPYRIGHT DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      Select groups and mesh part for visualization of image
&#39;   Assumptions:   Octree tetrahedron mesh part exists in the model
&#39;   Author:       bmw
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R16
&#39; ***********************************************************************

Sub CATMain()

&#39; ----------------------------------------------------------- 
&#39; Optional: allows to find the sample wherever it&#39;s installed
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
&#39; ----------------------------------------------------------- 


&#39; Open the CATAnalysis Document
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)


&#39; Retrieve the Analysis Manager
Set oAnalysisManager = oAnalysisDocument.Analysis
```

```vbscript
&#39; Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39; Retrieve the analysis cases and the first analysis case
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)

&#39; Retrieve the analysis sets and analysis set by its name
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item(&quot;Restraints.1&quot;, catAnalysisSetSearchAll)

Set analysisEntities1 = oAnalysisSet.AnalysisEntities
Set analysisEntity1 = analysisEntities1.Item(1)

&#39;add selection (specificationgroups)  clamp on Image Von Mises Stress (nodal values) (no selection before ReplaceMode=True)
&#39;============================================================================

Set reference1 = oAnalysisManager.CreateReferenceFromObject(analysisEntity1)

Set analysisSet2 = oAnalysisSets.Item(&quot;Frequency Case Solution.1&quot;, catAnalysisSetSearchAll)
Set analysisImages1 = analysisSet2.AnalysisImages
Set analysisImage1 = analysisImages1.Item(&quot;Von Mises Stress (nodal values).1&quot;)
analysisImage1.SetSelection reference1, True
analysisImage1.Update 

&#39;add selection (usergroups) SurfaceGroup.1 on Image Von Mises Stress (nodal values) (ReplaceMode=False)
&#39;=====================================================================

&#39; Get the list of groups and create reference from first group
Set analysisSets2 = oAnalysisModel.AnalysisSets
Set analysisSet3 = analysisSets2.ItemByType(&quot;GroupSet&quot;)
Set analysisEntities2 = analysisSet3.AnalysisEntities
Set analysisEntity2 = analysisEntities2.Item(1)
Set reference2 = oAnalysisManager.CreateReferenceFromObject(analysisEntity2)
```

```vbscript
&#39; Set the created reference for Selection in Von Mises Stress Image
analysisImage1.SetSelection reference2, False
analysisImage1.Update 

&#39;remove all selections on Image Von Mises Stress (nodal values)
&#39;======================================

&#39; Remove all the selections and update
analysisImage1.ResetSelection 
analysisImage1.Update 

&#39;add selection (meshparts) OctreeTetrahedronMesh.1:Part1 on Image Von Mises Stress (nodal values) (ReplaceMode=True)
&#39;==========================================================================

&#39; Retrieve the mesh part OCTREE Tetrahedron Filler
Set analysisSets3 = oAnalysisModel.AnalysisSets
Set oAnalysisMeshManager = analysisSets3.ItemByType(&quot;MSHMeshSet&quot;)
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set analysisMeshPart1 = oAnalysisMeshParts.Item(&quot;OCTREE Tetrahedron Mesh.1 : Part1&quot;)
```

```vbscript
&#39;Create reference from the mesh part and set the selection
Set reference3 = oAnalysisManager.CreateReferenceFromObject(analysisMeshPart1)
analysisImage1.SetSelection reference3, True
analysisImage1.Update 

End Sub
```