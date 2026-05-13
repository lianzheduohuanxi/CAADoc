---
title: "CAAAniMeshSeamWelding.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshSeamWelding", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSeamWeldingSource.htmmd"
converted: "2026-05-11T11:27:02.535659"
---

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

```vbscript
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the Analysis document 
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

' Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

'Retrieve the connection design manager and connection
```
```vbscript
Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
Set connSet = connection.AnalysisSets
Set conn = connSet.ItemByType("ConnectionDesignSet")
Set entity = conn.AnalysisEntities
Set surfConn  = entity.Item(2)
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

'Add new Seam welding connection mesh part to the list of mesh parts
```
```vbscript
Set seamWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSeam") 

```

'Add previously created  reference line analysis connection as support
seamWeld.AddSupportFromReference NOTHING, reference1

'Assign values to global specifications
seamWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
seamWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
seamWeld.SetGlobalSpecification "StopUpdateOnError", 1
seamWeld.SetGlobalSpecification "MiddleCombination", 2
seamWeld.SetGlobalSpecification "Width", "4.0 mm"

'Update the mesh
seamWeld.Update

```vbscript
End Sub

```

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

```vbscript
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the Analysis document 
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

' Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

'Retrieve the connection design manager and connection
```
```vbscript
Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
Set connSet = connection.AnalysisSets
Set conn = connSet.ItemByType("ConnectionDesignSet")
Set entity = conn.AnalysisEntities
Set surfConn  = entity.Item(2)
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

'Add new Seam welding connection mesh part to the list of mesh parts
```
```vbscript
Set seamWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSeam") 

```

'Add previously created  reference line analysis connection as support
seamWeld.AddSupportFromReference NOTHING, reference1

'Assign values to global specifications
seamWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
seamWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
seamWeld.SetGlobalSpecification "StopUpdateOnError", 1
seamWeld.SetGlobalSpecification "MiddleCombination", 2
seamWeld.SetGlobalSpecification "Width", "4.0 mm"

'Update the mesh
seamWeld.Update

```vbscript
End Sub
```
```