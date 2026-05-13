---
```vbscript
title: "CAAAniMeshOctTriangle.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshOctTriangle", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshOctTriangleSource.htmmd"
converted: "2026-05-11T17:31:51.679720"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Open an analysis document
    '                 Create an octree triangle mesh
    '                 assign the surface as support
    '                 specify the global specifications and assign values
    '   Assumptions:   Looks for Surface.CATAnalysis in the directory
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English
    '   CATIA Level:  V5R16
    ' ***********************************************************************
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```vbscript
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
```vbscript
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    'Open the analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    ' Retrieve the Analysis Manager and Analysis Model
```
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
    ' Retrieve the part document and product from Analysis manager
```
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
    Set partDocument1 = oAnalysisLinkedDocuments.Item(1)
    Set Product = partDocument1.Product
    ' Retrieve the analysis model from the list of models
```
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    ' Retrieve mesh manager and mesh part
```
```vbscript
    Set meshManagar = oAnalysisModel.MeshManager
    Set meshPart = meshManagar.AnalysisMeshParts
    ' Retrieve publications from product and retrieve the published face.
```
```vbscript
    Set Publications = Product.Publications
    Set pubSurf = Publications.Item("Round Hole.1")
    Set pubEdge = Publications.Item("Edge")
```
```

```

```

```vbscript
    ' Add the new Octree Triangle part to the list of mesh parts
```

```vbscript
```vbscript
    Set octreePart = meshPart.Add ("MSHPartOctree2D")
```vbscript
```
    ' Add the support from the published surface
```

    octreePart.AddSupportFromPublication Product, pubSurf
```vbscript
```vbscript
    ' Set the global Specifications
```
```

    octreePart.SetGlobalSpecification "SizeValue", "10.0 mm"
    octreePart.SetGlobalSpecification "AbsoluteSageValue", "3.0 mm"
    octreePart.SetGlobalSpecification "ElementOrder", "Parabolic"
    octreePart.SetGlobalSpecification "MinSizeForSags", "0.5 mm"
    octreePart.SetGlobalSpecification "MinGeometrySize", "0.5 mm"
    octreePart.SetGlobalSpecification "AbsoluteSag", 1
    octreePart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
    octreePart.SetGlobalSpecification "ProportionalSag", 1
    octreePart.SetGlobalSpecification "ProportionalSagValue", 0.5
    octreePart.SetGlobalSpecification "MaxWarpAngle", "1.0 rad"
    octreePart.SetGlobalSpecification "Criteria", "Shape"
    octreePart.SetGlobalSpecification "MeshGeometryViolation", "1.2 mm"
    octreePart.SetGlobalSpecification "InteriorSize", 2
    octreePart.SetGlobalSpecification "InteriorSizeValue", "5.0 mm"
    octreePart.SetGlobalSpecification "MinJacobian", 0.3
    octreePart.SetGlobalSpecification "MaxAttempts", 2
```

```vbscript
```vbscript
```vbscript
    ' Add the domain specifications as local specifications and assign it attributes
```vbscript
    Set meshspecs1 = octreePart.AnalysisMeshLocalSpecifications
    Set spec1 = meshspecs1.Add("MSHLocalMeshSize")
```
```

```

```

```vbscript
```vbscript
```vbscript
' Add the domain specifications as local specifications and assign it attributes
```vbscript
Set meshspecs1 = octreePart.AnalysisMeshLocalSpecifications
Set spec1 = meshspecs1.Add("MSHLocalMeshSize")
```
```

```

    spec1.SetAttribute "MSHMeshSizeMag", "1.0 mm"
    spec1.AddSupportFromPublication "ConnectorList", Product, pubEdge
```vbscript
    'Update mesh part
```

    octreePart.Update

```

```vbscript
```vbscript
    End Sub

```
```
