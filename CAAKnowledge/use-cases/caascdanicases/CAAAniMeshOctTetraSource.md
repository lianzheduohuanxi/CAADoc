---
```vbscript
title: "CAAAniMeshOctTetra.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshOctTetra"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshOctTetraSource.htmmd"
converted: "2026-05-11T17:31:51.673241"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose: Create an octree tetrahedron mesh
    '            assign the part body as support
    '            specify the global specifications
    '            create a local specifications and add local mesh size
    '            set attributes of domain specifications
    '   Assumptions:
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
    ' Open the CATAnalysis Document
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
    'Retrieve analysis manager
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
    ' Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```
```

```

```

```vbscript
    ' Retrieve the analysis model
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
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    ' Retrieve publications from product and retrieve the published face.
```
```vbscript
    Set publications = product.Publications
    Set pubedge = publications.Item("Edge")
    Set pubPartBody = publications.Item("PartBody")
```
```

```

```

```vbscript
    ' Add the new Octree tetrahedron mesh part to the list of mesh parts
```

```vbscript
```vbscript
    Set octreePart = oAnalysisMeshParts.Add ("MSHPartOctree3D")
```vbscript
```
    ' Add reference previously created
```

    octreePart.AddSupportFromPublication product, pubPartBody

```

```vbscript
```vbscript
' Add reference previously created
```

octreePart.AddSupportFromPublication product, pubPartBody
```vbscript
```vbscript
    ' Set the global Specifications
```
```

    octreePart.SetGlobalSpecification "SizeValue", "10.0 mm"
    octreePart.SetGlobalSpecification "AbsoluteSagValue", "3.0 mm"
    octreePart.SetGlobalSpecification "ElementOrder", "Parabolic"
    octreePart.SetGlobalSpecification "MaxInteriorSize", "1.2 mm"
    octreePart.SetGlobalSpecification "MinSizeForSags", "0.5 mm"
    octreePart.SetGlobalSpecification "MinGeometrySize", "0.5 mm"
    octreePart.SetGlobalSpecification "AbsoluteSag", 1
    octreePart.SetGlobalSpecification "MaxWarpAngle", "1.0 rad"
    octreePart.SetGlobalSpecification "Criteria", "Skewness"
    octreePart.SetGlobalSpecification "MeshGeometryViolation", 1
    octreePart.SetGlobalSpecification "InteriorSize", 1
    octreePart.SetGlobalSpecification "MinJacobian", 0.3
    octreePart.SetGlobalSpecification "MaxAttempts", 2
    octreePart.SetGlobalSpecification "MeshViolationValue", "0.5 mm"
    octreePart.SetGlobalSpecification "ProportionalSag", 1
    octreePart.SetGlobalSpecification "ProportionalSagValue", "0.5 mm"
```vbscript
    ' Add the Mesh local size as local specifications and assign it attributes
```

```

```vbscript
```vbscript
    Set meshspecs1 = octreePart.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
    Set spec1 = meshspecs1.Add("MSHLocalMeshSize")
```
```

    spec1.SetAttribute "MSHMeshSizeMag", "1.5 mm"
    spec1.AddSupportFromPublication "ConnectorList", product, pubedge
```vbscript
    'Update the mesh part
```

    octreePart.Update

```

```vbscript
```vbscript
    End Sub

```
```
