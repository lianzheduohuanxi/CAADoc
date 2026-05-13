---
title: "CAAAniMeshTetraFiller.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniMeshTetraFiller"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshTetraFillerSource.htmmd"
converted: "2026-05-11T11:27:02.496459"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:  Create a tetrahedron filler mesh part
'                   assign the support as surface mesh part
'                   specify the global specifications           
'   Assumptions:  Looks for Surface Mesh.1 in the analysis doc
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```vbscript
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Manager and Analysis Model
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the analysis model from list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

' Retrieve mesh manager and mesh part from the list of mesh parts specifying its name
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")

' Create Reference from the mesh part.
```
```vbscript
Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)

' Add the new Tetrahedron Filler mesh part to the list of mesh parts
```
```vbscript
Set tetraFiller = oAnalysisMeshParts.Add ("MSHPartGHS3D") 

' Add reference previously created
```
tetraFiller.AddSupportFromReference NOTHING, reference1

```vbscript
' Set the global Specifications
tetraFiller.SetGlobalSpecification "Propagation", 1.5
```
tetraFiller.SetGlobalSpecification "ElementOrder", "Parabolic"

'Update the mesh part
tetraFiller.Update

```vbscript
End Sub

```

```vbscript
' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:  Create a tetrahedron filler mesh part
'                   assign the support as surface mesh part
'                   specify the global specifications           
'   Assumptions:  Looks for Surface Mesh.1 in the analysis doc
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```vbscript
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the Analysis Manager and Analysis Model
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the analysis model from list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

' Retrieve mesh manager and mesh part from the list of mesh parts specifying its name
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")

' Create Reference from the mesh part.
```
```vbscript
Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)

' Add the new Tetrahedron Filler mesh part to the list of mesh parts
```
```vbscript
Set tetraFiller = oAnalysisMeshParts.Add ("MSHPartGHS3D") 

' Add reference previously created
```
tetraFiller.AddSupportFromReference NOTHING, reference1

```vbscript
' Set the global Specifications
tetraFiller.SetGlobalSpecification "Propagation", 1.5
```
tetraFiller.SetGlobalSpecification "ElementOrder", "Parabolic"

'Update the mesh part
tetraFiller.Update

```vbscript
End Sub
```
```