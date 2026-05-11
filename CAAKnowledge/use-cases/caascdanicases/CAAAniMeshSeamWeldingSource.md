---
```vbscript
title: "CAAAniMeshSeamWelding.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSeamWelding", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSeamWeldingSource.htm"
converted: "2026-05-11T17:31:51.690703"
```

---
```vbscript
```vbscript
```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Open an analysis document
    '                 Create Seam welding connection mesh part
    '                 assign the seam welding analysis connection as support
    '                 specify the global specifications
    '   Assumptions:   Looks for WeldConnection.CATAnalysis in the directory and surface Analysis Connection
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
    ' Open the Analysis document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis")
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
    ' Retrieve the analysis model
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```

```

```

```vbscript
    'Retrieve the connection design manager and connection
```

```vbscript
    Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
```vbscript
```vbscript
    Set connSet = connection.AnalysisSets
    Set conn = connSet.ItemByType("ConnectionDesignSet")
    Set entity = conn.AnalysisEntities
    Set surfConn  = entity.Item(2)
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
```

```

```

```vbscript
```vbscript
```vbscript
    'Add new Seam welding connection mesh part to the list of mesh parts
    Set seamWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSeam")
    'Add previously created  reference line analysis connection as support
```

```

```

```vbscript
```vbscript
```vbscript
'Add new Seam welding connection mesh part to the list of mesh parts
Set seamWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSeam")
'Add previously created  reference line analysis connection as support
```

```

    seamWeld.AddSupportFromReference NOTHING, reference1
```vbscript
    'Assign values to global specifications
```

    seamWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
    seamWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
    seamWeld.SetGlobalSpecification "StopUpdateOnError", 1
    seamWeld.SetGlobalSpecification "MiddleCombination", 2
    seamWeld.SetGlobalSpecification "Width", "4.0 mm"
```vbscript
    'Update the mesh
```

    seamWeld.Update

```

```vbscript
    End Sub

```
