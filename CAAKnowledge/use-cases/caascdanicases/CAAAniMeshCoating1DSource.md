---
```vbscript
title: "CAAAniMeshCoating1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshCoating1D", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1DSource.htmmd"
converted: "2026-05-11T17:31:51.623499"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:      Open an analysis document
    '                Create coating 1D mesh part
    '                assigning the surface mesh as support
    '                specify the global specifications
    '  Assumptions:   Looks for Surface.CATAnalysis in the directory and Surface Mesh.1
    '                mesh part
    '  Author:       bmw
    '  Languages:    VBScript
    '  Locales:      English
    '  CATIA Level:  V5R16
    '***********************************************************************

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
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed
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
    '-----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```vbscript
'-----------------------------------------------------------
    'Open the CATAnalysis Document
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
    'Retrieve the analysis Manager
```

```

```vbscript
```vbscript
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
```vbscript
```
    'Retrieve the part document and product
```

```

```vbscript
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
```vbscript
```
```vbscript
```vbscript
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```
```

```

```

```vbscript
```vbscript
```vbscript
    'Retrieve the published edge
```vbscript
    Set publications1 = product.Publications
    Set pubFace = publications1.Item("Edge")
```
```

```

```

```vbscript
    'Retrieve the analysis model
```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
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
    'Retrieve mesh manager and the surface mesh part by name
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create reference from the mesh part
```
```vbscript
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(oAnalysisMeshPart)
```
```

```

```

```vbscript
    'Add the new Coating mesh part to the list of mesh parts
```

```vbscript
```vbscript
    Set coat1D = oAnalysisMeshParts.Add ("MSHPart1DCoating")
```vbscript
```
    'Add the reference previously created
```

    coat2D.AddSupportFromReference NOTHING, reference1
```vbscript
```vbscript
    'Set the global specifications
```
```

    coat2D.SetGlobalSpecification "ExtractionType", 1

```

coat2D.SetGlobalSpecification "ExtractionType", 1
```vbscript
```vbscript
    'Create the local specification

```

```

```vbscript
```vbscript
    Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
    Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
```
```

    spec.SetAttribute "LocalExtractionType", 2

```

```vbscript
```vbscript
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
```
```

spec.SetAttribute "LocalExtractionType", 2
    spec.AddSupportFromPublication "ConnectorList", product, pubFace

```vbscript
    'Update mesh part
```

    coat1D.Update

```vbscript
```vbscript
    End Sub

```
```
