---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshNodesToNodesConnection", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshNodesToNodesConnectionSource.htmmd"
converted: "2026-05-11T11:27:02.558387"
---

' COPYRIGTH DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      Open an analysis document
'                 Create nodes to nodes welding connection mesh part
'                 assign the nodes to nodes analysis connection as support
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

' Retreive the analysis model
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
Set surfConn  = entity.Item(4)

'Create reference from the surface analysis connection
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

'Add new nodes to nodes connection mesh part to the list of mesh parts
```
```vbscript
Set nodeMesh = oAnalysisMeshParts.Add ("MSHPartConnPointPoint") 

```

'Assign previously created reference as support
nodeMesh.AddSupportFromReference NOTHING, reference1

'Assign values to its global specifications
nodeMesh.SetGlobalSpecification "Tolerance", 10.
nodeMesh.SetGlobalSpecification "StopUpdateOnError", 2
nodeMesh.SetGlobalSpecification "MiddleCombination", 12

'Update the mesh part
nodeMesh.Update

```vbscript
End Sub

```

```vbscript
&#39; COPYRIGTH DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      Open an analysis document
&#39;                 Create nodes to nodes welding connection mesh part
&#39;                 assign the nodes to nodes analysis connection as support
&#39;                 specify the global specifications
&#39;   Assumptions:   Looks for WeldConnection.CATAnalysis in the directory and surface Analysis Connection
&#39;   Author:       bmw
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R16
&#39; ***********************************************************************

```vbscript
Sub CATMain(#)

&#39; ----------------------------------------------------------- 
```
&#39; Optional: allows to find the sample wherever it&#39;s installed
```vbscript
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 

&#39; Open the Analysis document 
```vbscript
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

&#39; Retreive the analysis model
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
Set surfConn  = entity.Item(4)

&#39;Create reference from the surface analysis connection
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

&#39;Add new nodes to nodes connection mesh part to the list of mesh parts
```
```vbscript
Set nodeMesh = oAnalysisMeshParts.Add (&quot;MSHPartConnPointPoint&quot;) 

```

&#39;Assign previously created reference as support
nodeMesh.AddSupportFromReference NOTHING, reference1

&#39;Assign values to its global specifications
nodeMesh.SetGlobalSpecification &quot;Tolerance&quot;, 10.
nodeMesh.SetGlobalSpecification &quot;StopUpdateOnError&quot;, 2
nodeMesh.SetGlobalSpecification &quot;MiddleCombination&quot;, 12

&#39;Update the mesh part
nodeMesh.Update

```vbscript
End Sub
```
```