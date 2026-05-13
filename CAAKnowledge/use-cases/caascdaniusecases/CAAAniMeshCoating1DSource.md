---
title: "CAAAniMeshCoating1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniMeshCoating1D"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1DSource.htmmd"
converted: "2026-05-11T11:27:02.539904"
---

'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Create coating 1D mesh part
'                assigning the surface mesh as support
'                specify the global specifications
'  Assumptions:   Looks for Surface.CATAnalysis in the directory and Surface Mesh.1
'                mesh part
'  Author:       bmw
'  Languages:    VBScript
'  Locales:      English 
'  CATIA Level:  V5R16
'***********************************************************************

```vbscript
Sub CATMain(#)
'----------------------------------------------------------- 
```
'Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
'----------------------------------------------------------- 

'Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the published edge
```
```vbscript
Set publications1 = product.Publications
Set pubFace = publications1.Item("Edge")

'Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve mesh manager and the surface mesh part by name
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create reference from the mesh part
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(oAnalysisMeshPart)

'Add the new Coating mesh part to the list of mesh parts
```
```vbscript
Set coat1D = oAnalysisMeshParts.Add ("MSHPart1DCoating") 

'Add the reference previously created
```
coat2D.AddSupportFromReference NOTHING, reference1

```vbscript
'Set the global specifications
coat2D.SetGlobalSpecification "ExtractionType", 1
```

'Create the local specification
```vbscript
Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2
```

spec.AddSupportFromPublication "ConnectorList", product, pubFace

'Update mesh part
coat1D.Update

```vbscript
End Sub

```

```vbscript
'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Create coating 1D mesh part
'                assigning the surface mesh as support
'                specify the global specifications
'  Assumptions:   Looks for Surface.CATAnalysis in the directory and Surface Mesh.1
'                mesh part
'  Author:       bmw
'  Languages:    VBScript
'  Locales:      English 
'  CATIA Level:  V5R16
'***********************************************************************

```vbscript
Sub CATMain(#)
'----------------------------------------------------------- 
```
'Optional: allows to find the sample wherever it's installed
```vbscript
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
'----------------------------------------------------------- 

'Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

&#39;Retrieve the published edge
```
```vbscript
Set publications1 = product.Publications
Set pubFace = publications1.Item("Edge")

'Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve mesh manager and the surface mesh part by name
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")

&#39;Create reference from the mesh part
```
```vbscript
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(oAnalysisMeshPart)

&#39;Add the new Coating mesh part to the list of mesh parts
```
```vbscript
Set coat1D = oAnalysisMeshParts.Add ("MSHPart1DCoating") 

&#39;Add the reference previously created
```
coat2D.AddSupportFromReference NOTHING, reference1

```vbscript
&#39;Set the global specifications
coat2D.SetGlobalSpecification "ExtractionType", 1
```
```

```vbscript
'Create the local specification
```vbscript
Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2
```

spec.AddSupportFromPublication "ConnectorList", product, pubFace

&#39;Update mesh part
coat1D.Update

```vbscript
End Sub
```
```