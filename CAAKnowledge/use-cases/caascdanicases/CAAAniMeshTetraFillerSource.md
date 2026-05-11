---
```vbscript
title: "CAAAniMeshTetraFiller.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshTetraFiller"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshTetraFillerSource.htm"
converted: "2026-05-11T17:31:51.726093"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:  Create a tetrahedron filler mesh part
    '                   assign the support as surface mesh part
    '                   specify the global specifications
    '   Assumptions:  Looks for Surface Mesh.1 in the analysis doc
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

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```

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
End If
```vbscript
```vbscript
' -----------------------------------------------------------
    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
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
    'Retrieve the Analysis Manager and Analysis Model
```

```

```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```

```vbscript
```vbscript
```vbscript
    'Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    'Retrieve the analysis model from list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    ' Retrieve mesh manager and mesh part from the list of mesh parts specifying its name
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")
    ' Create Reference from the mesh part.
    Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)
    ' Add the new Tetrahedron Filler mesh part to the list of mesh parts
    Set tetraFiller = oAnalysisMeshParts.Add ("MSHPartGHS3D")
```

```

```

```vbscript
```vbscript
    ' Add reference previously created
```

    tetraFiller.AddSupportFromReference NOTHING, reference1
```vbscript
    ' Set the global Specifications
```

    tetraFiller.SetGlobalSpecification "Propagation", 1.5
    tetraFiller.SetGlobalSpecification "ElementOrder", "Parabolic"
```vbscript
    'Update the mesh part
```

    tetraFiller.Update

```

```vbscript
    End Sub

```
