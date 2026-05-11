---
title: "CAAAniMeshSymmetry.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSymmetry", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSymmetrySource.htm"
converted: "2026-05-11T17:31:51.720607"
---

```vbscript
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

    
```vbscript
    Sub CATMain()
```vbscript
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```

    
```

    
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    ' ----------------------------------------------------------- 
    
```

    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
```

    ' Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```vbscript
    ' Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    ' Retrieve the published plane
    ' The mesh will be symmetric along this plane
    Set publications = product.Publications
    Set pubPlane = publications.Item("SymmetryPlane")
    ' Retrieve the analysis model
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create the reference of the surface mesh
    Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
    'Add the mesh part to list of mesh parts
    Set meshTrans = oAnalysisMeshParts.Add("MSHPartSymmetry")
    'Assign the reference to the mesh part
```

    meshTrans.AddSupportFromReference NOTHING, reference
    
```

    meshTrans.SetGlobalSpecification "Condensation", 0
    meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
    meshTrans.SetGlobalSpecification "NbCopies", 2
    'Set the specification; the plane of symmetry
    meshTrans.SetSpecificationFromPublication "Direction", product, pubPlane, 0
    'Update the mesh part
    meshTrans.Update
    
```vbscript
    End Sub
    
```

```