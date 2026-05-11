---
title: "CAAAniMeshCoating2D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshCoating2D"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating2DSource.md"
converted: "2026-05-11T17:31:51.630483"
---

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

    
```vbscript
    Sub CATMain()
```vbscript
    '----------------------------------------------------------- 
    'Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    '----------------------------------------------------------- 
    
```

    'Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
```

    'Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
    
```

    'Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    
```

    'Retrieve the published face
```vbscript
    Set publications1 = product.Publications
    Set pubFace = publications1.Item("Top")
    
```

    'Retrieve the analysis model
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```vbscript
    'Retrieve The mesh manager and the list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    'Retrieve the already existing Octree mesh part
    Set oAnalysisMeshPart = oAnalysisMeshParts.Item(1)
    'Create reference from the mesh part
    Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)
    'Add the coating2D mesh to the list of mesh parts
    Set coat2D = oAnalysisMeshParts.Add ("MSHPart2DCoating") 
    'Add the reference previously created
```

    coat2D.AddSupportFromReference NOTHING, reference1
    'Set the global specifications
    coat2D.SetGlobalSpecification "ExtractionType", 1
    
```

    
    'Add the local specification
```vbscript
    Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
    Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
    spec.SetAttribute "LocalExtractionType", 2
    
```

    spec.AddSupportFromPublication "ConnectorList", product, pubFace
    
    'Update the mesh part
    coat2D.Update
    
```vbscript
    End Sub
    
```

```