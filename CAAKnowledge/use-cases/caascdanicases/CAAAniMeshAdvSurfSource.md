---
```vbscript
title: "CAAAniMeshAdvSurf.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshAdvSurf", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshAdvSurfSource.htmmd"
converted: "2026-05-11T17:31:51.610526"
```

---
```vbscript
```vbscript
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
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```vbscript
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
```vbscript
' -----------------------------------------------------------
    ' Open the Analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```
```

```

```vbscript
```vbscript
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
```
    ' Retrieve the Analysis Manager and Analysis Model
```

```

```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
```vbscript
```vbscript
    ' Retreive the part document from Analysis manager
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```
```

```

```

```vbscript
    ' Retrieve the analysis model from the list of models
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
    ' Retrieve mesh manager and mesh part
```vbscript
    Set meshManager = oAnalysisModel.MeshManager
    Set meshParts = meshManager.AnalysisMeshParts
```
```

```

```

```vbscript
    ' Retrieve publications from product and retrieve the published face.
```

```vbscript
```vbscript
    Set publications1 = product.Publications
```vbscript
```
```vbscript
```vbscript
    Set pubEdge = publications1.Item("Edge")
    Set pubSurf = publications1.Item("Round Hole.1")

```
```

```

```

```vbscript
```vbscript
Set pubEdge = publications1.Item("Edge")
```vbscript
```
```vbscript
```vbscript
Set pubSurf = publications1.Item("Round Hole.1")
    ' Add the new Advanced surface mesh part to the list of mesh parts
```
```

```

```

```vbscript
```vbscript
    Set surfPart = meshParts.Add ("MSHPartSmartSurf")
```vbscript
```
    ' Add reference previously created
```

    surfPart.AddSupportFromPublication product, pubSurf

```

```vbscript
```vbscript
' Add reference previously created
```

surfPart.AddSupportFromPublication product, pubSurf
```vbscript
```vbscript
    ' Set the global Specifications
```
```

    surfPart.SetGlobalSpecification "GlobalMethod", "Frontal triangle"
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

```vbscript
    ' Add the domain specifications as local specifications and assign values to its attributes
```

```

```vbscript
```vbscript
    Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
    Set spec = meshSpecs.Add("MSHDistributionElement")
```
```

    spec.SetAttribute "NbElements", 50
    spec.SetAttribute "Type", "Isometric"
    spec.AddSupportFromPublication "Supports", product, pubEdge
```vbscript
    'Update the mesh part
```

    surfPart.Update

```

```vbscript
```vbscript
    End Sub

```
```
