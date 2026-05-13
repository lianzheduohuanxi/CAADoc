---
```vbscript
title: "CAAAniMesh1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMesh1D"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMesh1DSource.htmmd"
converted: "2026-05-11T17:31:51.604045"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:  Create a 1D beam mesh part
    '                  assign the support
    '                  specify the global specifications
    '  Assumptions:  Looks for the published element Line.3 in the analysis doc
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Beam.CATAnalysis")
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
    'Retrieve the Analysis Managar and Analysis Model
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
    'Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    'Retrieve the analysis model from list of models
```
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve mesh manager and mesh part
```
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```
```

```

```

```vbscript
    'Retrieve publications from product and retrieve the published face.
```

```vbscript
```vbscript
    Set publications = product.Publications
```vbscript
```
```vbscript
```vbscript
    Set pubLine = publications.Item("Line.3")
    'Add the new beam mesh part to the list of mesh parts
```
```vbscript
    Set beamPart = oAnalysisMeshParts.Add("MSHPart1D")

```
```

```

```

```vbscript
```vbscript
```vbscript
'Add the new beam mesh part to the list of mesh parts
```vbscript
Set beamPart = oAnalysisMeshParts.Add("MSHPart1D")
```
```

```

    beamPart.AddSupportFromPublication product, pubLine
    beamPart.SetGlobalSpecification "SizeValue", "10.0 mm"
    beamPart.SetGlobalSpecification "AbsoluteSag", 1
    beamPart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
    beamPart.SetGlobalSpecification "MinimumSizeValue", "1.1 mm"
    beamPart.SetGlobalSpecification "ElementOrder", "Parabolic"
    beamPart.SetGlobalSpecification "MeshCapture", 1
    beamPart.SetGlobalSpecification "MeshCaptureTol", "1.1 mm"
    beamPart.SetGlobalSpecification "CurveAngle", "40 deg"

```vbscript
    'Update the mesh part
```

    beamPart.Update

```

```vbscript
```vbscript
    End Sub

```
```
