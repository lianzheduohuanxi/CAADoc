---
```vbscript
title: "CAAAniMeshBasicSurf.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshBasicSurf", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshBasicSurfSource.htmmd"
converted: "2026-05-11T17:31:51.617511"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:      Open an analysis document
    '                Create a basic surface mesh
    '                assign the surface as support
    '                specify the global specifications and assign values
    '  Assumptions:   Looks for Surface.CATAnalysis in the directory
    '  Author:       bmw
    '  Languages:    VBScript
    '  Locales:      English
    '  CATIA Level:  V5R16
    '***********************************************************************
```

```

```

```vbscript
    Sub CATMain(#)
```vbscript
```
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```
```

```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
        End If
```

```

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Open the Analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

```vbscript
    'Retrieve the Analysis Manager and Analysis Model
```

```vbscript
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
```
```

```vbscript
```vbscript
```vbscript
    'Retrieve the product from Analysis manager
```vbscript
    Set oAnalysisLinkedDocument = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocument.Item(1)
    Set product = partDocument.Product
    'Retrieve the analysis model from the list of models
```
```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve mesh manager and mesh part
```
```vbscript
    Set meshManagar = oAnalysisModel.MeshManager
    Set meshPart = meshManagar.AnalysisMeshParts
    'Retrieve publications from product and retrieve the published face.
```
```vbscript
    Set publications = product.Publications
    Set pubSurf = publications.Item("Round Hole.1")
    'Add the new basic surface mesh part to the list of mesh parts
```
```vbscript
    Set surfPart = meshPart.Add ("MSHPartBasicSurf")
    'Add the support from the published surface
```
```

```

```

```vbscript
```vbscript
```vbscript
'Add the new basic surface mesh part to the list of mesh parts
```vbscript
Set surfPart = meshPart.Add ("MSHPartBasicSurf")
'Add the support from the published surface
```
```

```

    surfPart.AddSupportFromPublication product, pubSurf

```

surfPart.AddSupportFromPublication product, pubSurf
```vbscript
```vbscript
    'Set the global Specifications
```
```

    surfPart.SetGlobalSpecification "GlobalMethod", 1
    surfPart.SetGlobalSpecification "QuadsOnly", 2
    surfPart.SetGlobalSpecification "ElementOrder", "Parabolic"
    surfPart.SetGlobalSpecification "DedicatedMesh", 1
    surfPart.SetGlobalSpecification "GlobalSize", "10.0 mm"
    surfPart.SetGlobalSpecification "Offset", "15.0 mm"
    surfPart.SetGlobalSpecification "TopologySize", "20.0 mm"
    surfPart.SetGlobalSpecification "TopologySag", 2
    surfPart.SetGlobalSpecification "SharpEdges", 1
    surfPart.SetGlobalSpecification "FaceAngle", "0 deg"
    surfPart.SetGlobalSpecification "OffsetFromThickness", 1
    surfPart.SetGlobalSpecification "MeshRelSag", 1
    surfPart.SetGlobalSpecification "MeshRelSagValue", "0.1 mm"
    surfPart.SetGlobalSpecification "CurveCapture", 1
    surfPart.SetGlobalSpecification "CurveCaptureTol", "1.1 mm"
    surfPart.SetGlobalSpecification "MeshCapture", 1
    surfPart.SetGlobalSpecification "MeshCaptureTol", "1.1 mm"
    surfPart.SetGlobalSpecification "MeshAbsSag", 1
    surfPart.SetGlobalSpecification "MeshAbsSaglValue", "1.1 mm"

```vbscript
```vbscript
    'Create local specification

```

```

```vbscript
```vbscript
    Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
    Set spec = meshSpecs.Add("MSHTopProjectCurve")
```
```

    spec.AddSupportFromPublication "ConnectorList", product1, pubCurve
    spec.SetAttribute "Tolerance", "500 mm"

```

```vbscript
```vbscript
    Set spec = meshSpecs.Add("MSHTopProjectPoint")
    spec.AddSupportFromPublication "ConnectorList", product1, pubPoint
```
    spec.SetAttribute "Tolerance", "500 mm"

```

spec.AddSupportFromPublication "ConnectorList", product1, pubPoint
spec.SetAttribute "Tolerance", "500 mm"
```vbscript
    'Update the mesh part
```

    surfPart.Update

```vbscript
```vbscript
    End Sub

```
```
