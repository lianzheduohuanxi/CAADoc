---
```vbscript
title: "CAAAniMeshExtrudeSymm.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshExtrudeSymm", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeSymmSource.htm"
converted: "2026-05-11T17:31:51.648574"
```

---
```vbscript
```vbscript
```vbscript
    'COPYRIGHT DASSAULT SYSTEMES 2000
    '***********************************************************************
    '  Purpose:      Open an analysis document
    '                Create Extrude with Symmetry mesh
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

    Sub CATMain()
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then

```

```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
```

```

```

```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
```vbscript
```vbscript
    'Retrieve the analysis Manager
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
    'Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    'Retrieve the published plane
    'the mesh will be symmetric along this plane
    Set publications = product.Publications
    Set pubPlane = publications.Item("SymmetryPlane")
    'Retrieve the analysis model
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create the reference of the surface mesh
    Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
    'Add the extrude with translation mesh part to the list of mesh parts
    Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSymmetry")
    'Assign the surface mesh part as support
```

```

```

```vbscript
```vbscript
```vbscript
'Add the extrude with translation mesh part to the list of mesh parts
Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSymmetry")
'Assign the surface mesh part as support
```

```

    extrudeMesh.AddSupportFromReference NOTHING, reference
```vbscript
    'Set the global specifications
```

    extrudeMesh.SetGlobalSpecification "Condensation", 1
    extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
```vbscript
    'Set the specification; specifying the plane of symmetry
```

    extrudeMesh.SetSpecificationFromPublication "Direction", product, pubPlane, 0
```

```vbscript
```vbscript
```vbscript
    'Get the basic components and sub components
    Set basicComps = extrudeMesh.BasicComponents
    Set subBasicComps = basicComps.Item(1).BasicComponents
    'Retrieve each of the attributes by name and set their values
    Set subBasicComp1 = subBasicComps.Item("Type")
```

```

```

```vbscript
Set subBasicComps = basicComps.Item(1).BasicComponents
```vbscript
```vbscript
'Retrieve each of the attributes by name and set their values
Set subBasicComp1 = subBasicComps.Item("Type")
```

```

    subBasicComp1.SetValue "", 0, 0, 0, "Geometric"

    Set subBasicComp2 = subBasicComps.Item("NbNodes")
    subBasicComp2.SetValue "", 0, 0, 0, 20

    Set subBasicComp3 = subBasicComps.Item("Symmetric")
    subBasicComp3.SetValue "", 0, 0, 0, 2

    Set subBasicComp4 = subBasicComps.Item("Ratio")
    subBasicComp4.SetValue "", 0, 0, 0, 10
```vbscript
    'Update the mesh
```

    extrudeMesh.Update

```

```vbscript
    End Sub

```
