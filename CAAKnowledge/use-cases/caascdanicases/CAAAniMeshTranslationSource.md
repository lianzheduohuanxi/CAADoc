---
```vbscript
title: "CAAAniMeshTranslation.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshTranslation", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshTranslationSource.htm"
converted: "2026-05-11T17:31:51.732080"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Open an analysis document
    '                 Create Translation mesh
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
    Sub CATMain()

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```

```

```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```vbscript
        End If
    ' -----------------------------------------------------------

```

```

```

```vbscript
```vbscript
```vbscript
' -----------------------------------------------------------
    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
```

```

```

```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```

```

```vbscript
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
    ' Retrieve the analysis Manager
```

```

```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
```vbscript
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```

```

```vbscript
```vbscript
```vbscript
    ' Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    'Retrieve the published line
    Set publications = product.Publications
    Set pubDirection = publications.Item("Direction")
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
    Set meshTrans = oAnalysisMeshParts.Add("MSHPartTranslation")
    'Assign the reference to the mesh part
```

```

```

```vbscript
```vbscript
```vbscript
'Add the mesh part to list of mesh parts
Set meshTrans = oAnalysisMeshParts.Add("MSHPartTranslation")
'Assign the reference to the mesh part
```

```

    meshTrans.AddSupportFromReference NOTHING, reference

```

meshTrans.AddSupportFromReference NOTHING, reference
    meshTrans.SetGlobalSpecification "TranslationValue", "-100.0 mm"
    meshTrans.SetGlobalSpecification "Condensation", 0
    meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
    meshTrans.SetGlobalSpecification "NbCopies", 3
```vbscript
    'Set the specification; the the direction of translation
```

    meshTrans.SetSpecificationFromPublication "Direction", product, pubDirection, 0
```vbscript
    'Update the mesh
```

    meshTrans.Update

```vbscript
    End Sub

```
