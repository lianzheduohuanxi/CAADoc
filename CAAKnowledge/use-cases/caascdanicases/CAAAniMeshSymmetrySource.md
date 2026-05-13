---
title: "CAAAniMeshSymmetry.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniMeshSymmetry", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSymmetrySource.htm"
converted: "2026-05-11T17:31:51.720607"
---
```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Open an analysis document
    '                 Create Symmetry mesh
    '                 assign the Surface Mesh as support
    '                 specify the global specifications
    '   Assumptions:   Looks for surface.CATAnalysis in the directory and surface Analysis Connection
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
```
```

```

```

```vbscript
```cpp
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
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
    ' Retrieve the published plane
```
    ' The mesh will be symmetric along this plane
```vbscript
    Set publications = product.Publications
    Set pubPlane = publications.Item("SymmetryPlane")
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
    Set meshTrans = oAnalysisMeshParts.Add("MSHPartSymmetry")
    'Assign the reference to the mesh part
```
```

```

```

```vbscript
```vbscript
```vbscript
'Add the mesh part to list of mesh parts
```vbscript
Set meshTrans = oAnalysisMeshParts.Add("MSHPartSymmetry")
'Assign the reference to the mesh part
```
```

```

    meshTrans.AddSupportFromReference NOTHING, reference

```

meshTrans.AddSupportFromReference NOTHING, reference
    meshTrans.SetGlobalSpecification "Condensation", 0
    meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
    meshTrans.SetGlobalSpecification "NbCopies", 2
```vbscript
```vbscript
    'Set the specification; the plane of symmetry
```
```

    meshTrans.SetSpecificationFromPublication "Direction", product, pubPlane, 0
```vbscript
    'Update the mesh part
```

    meshTrans.Update

```vbscript
```vbscript
    End Sub

```
```
