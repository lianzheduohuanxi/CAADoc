---
title: "CAAAniMeshCoating2D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshCoating2D", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating2DSource.htmmd"
converted: "2026-05-11T11:27:02.522986"
---

'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Create coating 2D mesh part
'                assigning the solid mesh as support
'                specify the global specifications
'  Assumptions:   Looks for Cube_R13_Freq.CATAnalysis in the directory and Octree mesh part
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
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the published face
```
```vbscript
Set publications1 = product.Publications
Set pubFace = publications1.Item("Top")

'Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve The mesh manager and the list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

'Retrieve the already existing Octree mesh part
```
```vbscript
Set oAnalysisMeshPart = oAnalysisMeshParts.Item(1)

'Create reference from the mesh part
```
```vbscript
Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)

'Add the coating2D mesh to the list of mesh parts
```
```vbscript
Set coat2D = oAnalysisMeshParts.Add ("MSHPart2DCoating") 

'Add the reference previously created
```
coat2D.AddSupportFromReference NOTHING, reference1

```vbscript
'Set the global specifications
coat2D.SetGlobalSpecification "ExtractionType", 1
```

'Add the local specification
```vbscript
Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2
```

spec.AddSupportFromPublication "ConnectorList", product, pubFace

'Update the mesh part
coat2D.Update

```vbscript
End Sub

```

```vbscript
'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Create coating 2D mesh part
'                assigning the solid mesh as support
'                specify the global specifications
'  Assumptions:   Looks for Cube_R13_Freq.CATAnalysis in the directory and Octree mesh part
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
'Optional: allows to find the sample wherever it&#39;s installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
'----------------------------------------------------------- 

'Open the CATAnalysis Document
```vbscript
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

&#39;Retrieve the published face
```
```vbscript
Set publications1 = product.Publications
Set pubFace = publications1.Item("Top")

'Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39;Retrieve The mesh manager and the list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

&#39;Retrieve the already existing Octree mesh part
```
```vbscript
Set oAnalysisMeshPart = oAnalysisMeshParts.Item(1)

&#39;Create reference from the mesh part
```
```vbscript
Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)

&#39;Add the coating2D mesh to the list of mesh parts
```
```vbscript
Set coat2D = oAnalysisMeshParts.Add ("MSHPart2DCoating") 

&#39;Add the reference previously created
```
coat2D.AddSupportFromReference NOTHING, reference1

```vbscript
&#39;Set the global specifications
coat2D.SetGlobalSpecification "ExtractionType", 1
```
```

```vbscript
&#39;Add the local specification
```vbscript
Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2
```

spec.AddSupportFromPublication "ConnectorList", product, pubFace

&#39;Update the mesh part
coat2D.Update

```vbscript
End Sub
```
```