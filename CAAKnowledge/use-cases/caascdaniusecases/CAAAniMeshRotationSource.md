---
title: "CAAAniMeshRotation.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshRotation", "CAAScrBase", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshRotationSource.htmmd"
converted: "2026-05-11T11:27:02.539007"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Open an analysis document
'                 Create Rotation mesh
'                 assign the Surface Mesh as support
'                 specify the global specifications
'   Assumptions:   Looks for surface.CATAnalysis in the directory and surface Analysis Connection
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

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the published line 
```
' the mesh will be rotated along this line
```vbscript
Set publications = product.Publications
Set pubAxis = publications.Item("Axis")

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
Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create the reference of the surface mesh
```
```vbscript
Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)

'Add the mesh part to list of mesh parts
```
```vbscript
Set meshTrans = oAnalysisMeshParts.Add("MSHPartRotation")

```

'Assign the reference to the mesh part
meshTrans.AddSupportFromReference NOTHING, reference

meshTrans.SetGlobalSpecification "RotationValue", "60 deg"
meshTrans.SetGlobalSpecification "Condensation", 0
meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
meshTrans.SetGlobalSpecification "NbCopies", 2

```vbscript
'Set the specification; the axis of rotation
meshTrans.SetSpecificationFromPublication "Direction", product, pubAxis, 0
```

'Update the mesh
meshTrans.Update

```vbscript
End Sub

```

```cpp
' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Open an analysis document
'                 Create Rotation mesh
'                 assign the Surface Mesh as support
'                 specify the global specifications
'   Assumptions:   Looks for surface.CATAnalysis in the directory and surface Analysis Connection
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

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the published line 
```
' the mesh will be rotated along this line
```vbscript
Set publications = product.Publications
Set pubAxis = publications.Item("Axis")

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
Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create the reference of the surface mesh
```
```vbscript
Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)

'Add the mesh part to list of mesh parts
```
```vbscript
Set meshTrans = oAnalysisMeshParts.Add("MSHPartRotation")

```

'Assign the reference to the mesh part
meshTrans.AddSupportFromReference NOTHING, reference

meshTrans.SetGlobalSpecification "RotationValue", "60 deg"
meshTrans.SetGlobalSpecification "Condensation", 0
meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
meshTrans.SetGlobalSpecification "NbCopies", 2

```vbscript
'Set the specification; the axis of rotation
meshTrans.SetSpecificationFromPublication "Direction", product, pubAxis, 0
```

'Update the mesh
meshTrans.Update

```vbscript
End Sub
```
```