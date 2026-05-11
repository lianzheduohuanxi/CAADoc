---
title: "CAAAniMeshNodesInterface.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshNodesInterface", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshNodesInterfaceSource.md"
converted: "2026-05-11T17:31:51.662070"
---

```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      Open an analysis document
    '                 Create nodes interface connection mesh part
    '                 assign the nodes interface analysis connection as support
    '                 specify the global specifications
    '   Assumptions:   Looks for WeldConnection.CATAnalysis in the directory and surface Analysis Connection
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R16
    ' ***********************************************************************
    
```

    
```vbscript
    Sub CATMain()
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
    
      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    ' ----------------------------------------------------------- 
    
```

    ' Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis")
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
    ' Retrieve the analysis model
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```

    
```

    'Retrieve the connection design manager and connection
```vbscript
    Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
    Set connSet = connection.AnalysisSets
    Set conn = connSet.ItemByType("ConnectionDesignSet")
    Set entity = conn.AnalysisEntities
    Set surfConn  = entity.Item(1)
```vbscript
    'Create reference from the surface analysis connection
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
    'Add nodes interface mesh part to the list of mesh  parts
    Set nodeMesh = oAnalysisMeshParts.Add ("MSHPartConnHalfPoint") 
    'Assign previously create reference as support
```

    nodeMesh.AddSupportFromReference NOTHING, reference1
    'Assign values to its global specifications
    nodeMesh.SetGlobalSpecification "Tolerance", "6 mm"
    nodeMesh.SetGlobalSpecification "StopUpdateOnError", 2
    nodeMesh.SetGlobalSpecification "MiddleCombination", 1
    
```

    
    'Update the mesh part
    nodeMesh.Update
    
```vbscript
    End Sub
    
```

```