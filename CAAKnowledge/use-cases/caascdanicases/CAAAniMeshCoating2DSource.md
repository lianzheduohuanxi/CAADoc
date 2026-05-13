---
```vbscript
title: "CAAAniMeshCoating2D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshCoating2D"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating2DSource.htmmd"
converted: "2026-05-11T17:31:51.630483"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:      Open an analysis document
    '                Create coating 2D mesh part
    '                assigning the solid mesh as support
    '                specify the global specifications
    '  Assumptions:   Looks for Cube_R13_Freq.CATAnalysis in the directory and Octree mesh part
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
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
    Set oAnalysisManager = oAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
```
    'Retrieve the part document and product
```

```

```vbscript
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
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
Set partDocument = oAnalysisLinkedDocuments.Item(1)
```vbscript
```
```vbscript
```vbscript
Set product = partDocument.Product
    'Retrieve the published face
```
```

```

```

```vbscript
```vbscript
    Set publications1 = product.Publications
```vbscript
```
```vbscript
```vbscript
    Set pubFace = publications1.Item("Top")

```
```

```

```

```vbscript
```vbscript
Set publications1 = product.Publications
```vbscript
```
```vbscript
```vbscript
Set pubFace = publications1.Item("Top")
    'Retrieve the analysis model
```
```

```

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
    'Retrieve The mesh manager and the list of mesh parts
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    'Retrieve the already existing Octree mesh part
```
```vbscript
    Set oAnalysisMeshPart = oAnalysisMeshParts.Item(1)
    'Create reference from the mesh part
```
```vbscript
    Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)
    'Add the coating2D mesh to the list of mesh parts
```
```vbscript
    Set coat2D = oAnalysisMeshParts.Add ("MSHPart2DCoating")
    'Add the reference previously created
```
```

```

```

```vbscript
```vbscript
```vbscript
'Add the coating2D mesh to the list of mesh parts
```vbscript
Set coat2D = oAnalysisMeshParts.Add ("MSHPart2DCoating")
'Add the reference previously created
```
```

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
    'Add the local specification

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
    'Update the mesh part
```

    coat2D.Update

```vbscript
```vbscript
    End Sub

```
```
