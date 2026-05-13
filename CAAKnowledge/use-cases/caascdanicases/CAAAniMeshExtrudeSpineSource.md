---
title: "CAAAniMeshExtrudeSpine.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAScdAniUseCases", "CAAAniMeshExtrudeSpine"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeSpineSource.htm"
converted: "2026-05-11T17:31:51.642594"
---
```vbscript
```vbscript
```cpp
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:      Open an analysis document
    '                Create Extrude mesh along a spine mesh part
    '                assign the Surface Mesh as support
    '                specify the global specifications
    '  Assumptions:   Looks for surface.CATAnalysis in the directory and surface Analysis Connection
    '  Author:       bmw
    '  Languages:    VBScript
    '  Locales:      English
    '  CATIA Level:  V5R16
    '***********************************************************************
```

```

```

```cpp
    Sub CATMain(#)
```vbscript
```
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

```cpp
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
```vbscript
        End If
    '-----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```cpp
'-----------------------------------------------------------
    'Open the CATAnalysis Document
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
```cpp
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```
```

```

```vbscript
```cpp
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
```
    'Retrieve the analysis Manager
```

```

```vbscript
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
```vbscript
```
```vbscript
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```
```

```

```vbscript
```vbscript
```vbscript
    'Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    'Retrieved the published line that is the
```
    'spine along which mesh will be extruded
```vbscript
    Set publications = product.Publications
    Set pubSpine = publications.Item("Spine")
    'Retrieve the analysis model
```
```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
```
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create the reference of the surface mesh
```
```vbscript
    Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
```
```

```

```

```vbscript
    'Add the extrude with translation mesh part to the list of mesh parts
```

```vbscript
```vbscript
```vbscript
    Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSpine")

```
```

```

```vbscript
```vbscript
Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSpine")
```vbscript
```
    'Assign the surface mesh part as support
```

    extrudeMesh.AddSupportFromReference NOTHING, reference
```vbscript
```vbscript
    'Set the global specifications
```
```

    extrudeMesh.SetGlobalSpecification "Condensation", 1
    extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
    extrudeMesh.SetGlobalSpecification "Length", "500.0 mm"
    extrudeMesh.SetGlobalSpecification "Lentgh1", "10.0 mm"
```vbscript
```vbscript
    'Set the specification; spine along which mesh will be extruded
```
```

    extrudeMesh.SetSpecificationFromPublication "Direction", product, pubSpine, 0
```vbscript
    'Retrieve the basic components and sub components
```

```

```vbscript
```vbscript
    Set basicComps = extrudeMesh.BasicComponents
```vbscript
```
```vbscript
```vbscript
    Set subBasicComps = basicComps.Item(1).BasicComponents
    'Retrieve each attribute and set its value
```

```vbscript
    Set subBasicComp1 = subBasicComps.Item("Type")
```
```

```

    subBasicComp1.SetValue "", 0, 0, 0, "Arithmetic"

```vbscript
    Set subBasicComp2 = subBasicComps.Item("NbNodes")
    subBasicComp2.SetValue "", 0, 0, 0, 20
```

```vbscript
    Set subBasicComp3 = subBasicComps.Item("Symmetric")
    subBasicComp3.SetValue "", 0, 0, 0, "TRUE"
```

```vbscript
    Set subBasicComp4 = subBasicComps.Item("Ratio")
    subBasicComp4.SetValue "", 0, 0, 0, 10
```
```vbscript
    'Update the mesh
```

    extrudeMesh.Update

```

```vbscript
```vbscript
    End Sub

```
```
