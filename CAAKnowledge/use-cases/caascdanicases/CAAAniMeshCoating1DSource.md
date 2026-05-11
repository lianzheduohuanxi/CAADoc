---
title: "CAAAniMeshCoating1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshCoating1D", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1DSource.htm"
converted: "2026-05-11T17:31:51.623499"
---

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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
```

    'Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    
```

    'Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```vbscript
    'Retrieve the published edge
    Set publications1 = product.Publications
    Set pubFace = publications1.Item("Edge")
```

    
```

    'Retrieve the analysis model
```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```vbscript
    'Retrieve mesh manager and the surface mesh part by name
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create reference from the mesh part
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(oAnalysisMeshPart)
```

    
```

    'Add the new Coating mesh part to the list of mesh parts
```vbscript
    Set coat1D = oAnalysisMeshParts.Add ("MSHPart1DCoating") 
    'Add the reference previously created
    coat2D.AddSupportFromReference NOTHING, reference1
    'Set the global specifications
    coat2D.SetGlobalSpecification "ExtractionType", 1
    
```

    
    'Create the local specification
```vbscript
    Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
    Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
    spec.SetAttribute "LocalExtractionType", 2
    
```

    spec.AddSupportFromPublication "ConnectorList", product, pubFace
    
    
    'Update mesh part
    coat1D.Update
    
    
```vbscript
    End Sub
    
```

```