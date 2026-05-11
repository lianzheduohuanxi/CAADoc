---
```vbscript
title: "CAAAniMeshSweep3D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSweep3D", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSweep3DSource.htm"
converted: "2026-05-11T17:31:51.714618"
```

---
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

    Sub CATMain()

```vbscript
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```

```vbscript
    ' ----------------------------------------------------------- 
    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    ' Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```

```vbscript
    ' Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    'Retrieve the publications
    Set publications = product.Publications
    Set pubBody = publications.Item("PartBody")
    Set pubTopFace = publications.Item("Top")
    Set pubBotFace = publications.Item("Bottom")
    ' Retrieve the analysis model
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    'Add Sweep 3D mesh part to the list of mesh parts
    Set sweep3D = oAnalysisMeshParts.Add ("MSHPartSweep3D") 
    'Add support from the published body
```

```vbscript
'Add Sweep 3D mesh part to the list of mesh parts
Set sweep3D = oAnalysisMeshParts.Add ("MSHPartSweep3D")
'Add support from the published body
    sweep3D.AddSupportFromPublication product, pubBody

```

sweep3D.AddSupportFromPublication product, pubBody
    sweep3D.SetSpecificationFromPublication "Top", product, pubTopFace, 0

    sweep3D.SetSpecificationFromPublication "Bottom", product, pubBotFace, 0
    'Set the global specification
    sweep3D.SetGlobalSpecification "ElementOrder", "Linear"
    sweep3D.SetGlobalSpecification "GuideAngle", "60 deg"
    sweep3D.SetGlobalSpecification "NbElements", 10
    sweep3D.SetGlobalSpecification "DistributionType", "Arithmetic"
    sweep3D.SetGlobalSpecification "Ratio", 5.0
    sweep3D.SetGlobalSpecification "CaptureTol", 1.0

    sweep3D.Update

    End Sub
