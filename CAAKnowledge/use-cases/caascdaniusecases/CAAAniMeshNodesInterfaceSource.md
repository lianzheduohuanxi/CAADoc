---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniMeshNodesInterface"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshNodesInterfaceSource.htmmd"
converted: "2026-05-11T11:27:02.567880"
---

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

```cpp
Sub CATMain(#)

' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed

```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")
  sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the Analysis document 
```cpp
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
Set surfConn  = entity.Item(1)

'Create reference from the surface analysis connection
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

'Add nodes interface mesh part to the list of mesh  parts
```
```vbscript
Set nodeMesh = oAnalysisMeshParts.Add ("MSHPartConnHalfPoint") 

```

'Assign previously create reference as support
nodeMesh.AddSupportFromReference NOTHING, reference1

'Assign values to its global specifications
nodeMesh.SetGlobalSpecification "Tolerance", "6 mm"
nodeMesh.SetGlobalSpecification "StopUpdateOnError", 2
nodeMesh.SetGlobalSpecification "MiddleCombination", 1

'Update the mesh part
nodeMesh.Update

```vbscript
End Sub

```

```cpp
&#39; COPYRIGHT DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      Open an analysis document
&#39;                 Create nodes interface connection mesh part
&#39;                 assign the nodes interface analysis connection as support
&#39;                 specify the global specifications
&#39;   Assumptions:   Looks for WeldConnection.CATAnalysis in the directory and surface Analysis Connection
&#39;   Author:       bmw
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R16
&#39; ***********************************************************************

```cpp
Sub CATMain(#)

&#39; ----------------------------------------------------------- 
```
&#39; Optional: allows to find the sample wherever it&#39;s installed

```cpp
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)
  sSep=CATIA.SystemService.Environ(&quot;ADL_ODT_SLASH&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 

&#39; Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

&#39; Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

&#39; Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

&#39; Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39;Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

&#39;Retrieve the connection design manager and connection
```
```vbscript
Set connection = oAnalysisSet.ItemByType(&quot;ConnectionDesignManager&quot;)
Set connSet = connection.AnalysisSets
Set conn = connSet.ItemByType(&quot;ConnectionDesignSet&quot;)
Set entity = conn.AnalysisEntities
Set surfConn  = entity.Item(1)

&#39;Create reference from the surface analysis connection
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

&#39;Add nodes interface mesh part to the list of mesh  parts
```
```vbscript
Set nodeMesh = oAnalysisMeshParts.Add (&quot;MSHPartConnHalfPoint&quot;) 

```

&#39;Assign previously create reference as support
nodeMesh.AddSupportFromReference NOTHING, reference1

&#39;Assign values to its global specifications
nodeMesh.SetGlobalSpecification &quot;Tolerance&quot;, &quot;6 mm&quot;
nodeMesh.SetGlobalSpecification &quot;StopUpdateOnError&quot;, 2
nodeMesh.SetGlobalSpecification &quot;MiddleCombination&quot;, 1
```

```vbscript
&#39;Update the mesh part
nodeMesh.Update

```vbscript
End Sub
```
```