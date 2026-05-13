---
title: "CAAAniMeshAdvSurf.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniMeshAdvSurf"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshAdvSurfSource.htmmd"
converted: "2026-05-11T11:27:02.559371"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Open an analysis document
'                 Create an advanced surface mesh  
'                 assign the surface as support
'                 specify the global specifications
'                 create a local specifications and add domain specifications
'                 set attributes of domain specifications
'   Assumptions:   Looks for Pad.CATAnalysis in the directory
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```cpp
Sub CATMain(#)
' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")

  If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the Analysis Manager and Analysis Model
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

' Retreive the part document from Analysis manager
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

' Retrieve the analysis model from the list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

' Retrieve mesh manager and mesh part 
```
```vbscript
Set meshManager = oAnalysisModel.MeshManager
Set meshParts = meshManager.AnalysisMeshParts

' Retrieve publications from product and retrieve the published face.
```
```vbscript
Set publications1 = product.Publications
Set pubEdge = publications1.Item("Edge")
Set pubSurf = publications1.Item("Round Hole.1")

' Add the new Advanced surface mesh part to the list of mesh parts
```
```vbscript
Set surfPart = meshParts.Add ("MSHPartSmartSurf") 

' Add reference previously created
```
surfPart.AddSupportFromPublication product, pubSurf

```vbscript
' Set the global Specifications
surfPart.SetGlobalSpecification "GlobalMethod", "Frontal triangle"
```
surfPart.SetGlobalSpecification "GlobalSize", "20.0 mm"
surfPart.SetGlobalSpecification "MinimumSize", "1.0 mm"
surfPart.SetGlobalSpecification "ElementOrder", "Parabolic"
surfPart.SetGlobalSpecification "FaceAngle", "0.0 deg"
surfPart.SetGlobalSpecification "CurveAngle", "0.0 deg"
surfPart.SetGlobalSpecification "DetailsElimination", 1
surfPart.SetGlobalSpecification "StripOptimization", 1
surfPart.SetGlobalSpecification "CleanSize", "1.0 mm"
surfPart.SetGlobalSpecification "Offset", "0.0 mm"
surfPart.SetGlobalSpecification "OffsetFromThickness", "0.0 mm"
surfPart.SetGlobalSpecification "MinimizeTriangles", 1.
surfPart.SetGlobalSpecification "MinSizeForSag", "1.0 mm"
surfPart.SetGlobalSpecification "CurveCaptureTol", "1.0 mm"
surfPart.SetGlobalSpecification "OptimizeRegularity", 1
surfPart.SetGlobalSpecification "MeshRelSagValue", "1.0 mm"
surfPart.SetGlobalSpecification "MeshRelSag", 1
surfPart.SetGlobalSpecification "ConstraintSagValue", "1.0 mm"
surfPart.SetGlobalSpecification "CurveCapture", 1
surfPart.SetGlobalSpecification "MeshCapture", 1
surfPart.SetGlobalSpecification "MeshCapturTol", "1.0 mm"
surfPart.SetGlobalSpecification "MeshAbsSag", 2
surfPart.SetGlobalSpecification "MeshAbsSagValue", "1.0 mm"

' Add the domain specifications as local specifications and assign values to its attributes
```vbscript
Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHDistributionElement")
spec.SetAttribute "NbElements", 50
```
spec.SetAttribute "Type", "Isometric"
spec.AddSupportFromPublication "Supports", product, pubEdge

'Update the mesh part
surfPart.Update

```vbscript
End Sub

```

```vbscript
' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Open an analysis document
'                 Create an advanced surface mesh  
'                 assign the surface as support
'                 specify the global specifications
'                 create a local specifications and add domain specifications
'                 set attributes of domain specifications
'   Assumptions:   Looks for Pad.CATAnalysis in the directory
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```cpp
Sub CATMain(#)
' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")

  If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the Analysis Manager and Analysis Model
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

' Retreive the part document from Analysis manager
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

' Retrieve the analysis model from the list of models
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

' Retrieve mesh manager and mesh part 
```
```vbscript
Set meshManager = oAnalysisModel.MeshManager
Set meshParts = meshManager.AnalysisMeshParts

' Retrieve publications from product and retrieve the published face.
```
```vbscript
Set publications1 = product.Publications
Set pubEdge = publications1.Item("Edge")
Set pubSurf = publications1.Item("Round Hole.1")

' Add the new Advanced surface mesh part to the list of mesh parts
```
```vbscript
Set surfPart = meshParts.Add ("MSHPartSmartSurf") 

' Add reference previously created
```
surfPart.AddSupportFromPublication product, pubSurf

```vbscript
' Set the global Specifications
surfPart.SetGlobalSpecification "GlobalMethod", "Frontal triangle"
```
surfPart.SetGlobalSpecification "GlobalSize", "20.0 mm"
surfPart.SetGlobalSpecification "MinimumSize", "1.0 mm"
surfPart.SetGlobalSpecification "ElementOrder", "Parabolic"
surfPart.SetGlobalSpecification "FaceAngle", "0.0 deg"
surfPart.SetGlobalSpecification "CurveAngle", "0.0 deg"
surfPart.SetGlobalSpecification "DetailsElimination", 1
surfPart.SetGlobalSpecification "StripOptimization", 1
surfPart.SetGlobalSpecification "CleanSize", "1.0 mm"
surfPart.SetGlobalSpecification "Offset", "0.0 mm"
surfPart.SetGlobalSpecification "OffsetFromThickness", "0.0 mm"
surfPart.SetGlobalSpecification "MinimizeTriangles", 1.
surfPart.SetGlobalSpecification "MinSizeForSag", "1.0 mm"
surfPart.SetGlobalSpecification "CurveCaptureTol", "1.0 mm"
surfPart.SetGlobalSpecification "OptimizeRegularity", 1
surfPart.SetGlobalSpecification "MeshRelSagValue", "1.0 mm"
surfPart.SetGlobalSpecification "MeshRelSag", 1
surfPart.SetGlobalSpecification "ConstraintSagValue", "1.0 mm"
surfPart.SetGlobalSpecification "CurveCapture", 1
surfPart.SetGlobalSpecification "MeshCapture", 1
surfPart.SetGlobalSpecification "MeshCapturTol", "1.0 mm"
surfPart.SetGlobalSpecification "MeshAbsSag", 2
surfPart.SetGlobalSpecification "MeshAbsSagValue", "1.0 mm"

' Add the domain specifications as local specifications and assign values to its attributes
```vbscript
Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHDistributionElement")
spec.SetAttribute "NbElements", 50
```
spec.SetAttribute "Type", "Isometric"
spec.AddSupportFromPublication "Supports", product, pubEdge

'Update the mesh part
surfPart.Update

```vbscript
End Sub
```
```