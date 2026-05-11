---
title: "CAAAniMeshCoating1D.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshCoating1D", "CAAScdAniUseCases", "CATIA"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1DSource.htm"
converted: "2026-05-11T11:06:32.400474"
---

```
'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************

' Purpose: Open an analysis document

' Create coating 1D mesh part

' assigning the surface mesh as support

' specify the global specifications

' Assumptions: Looks for Surface.CATAnalysis in the directory and Surface Mesh.1

' mesh part

' Author: bmw

' Languages: VBScript

' Locales: English 

' CATIA Level: V5R16

'***********************************************************************

Sub 
CATMain()

'----------------------------------------------------------- 

'Optional: allows to find the sample wherever it's installed

 sDocPath=CATIA.SystemService.Environ("CATDocView")

 If 
(Not CATIA.FileSystem.FolderExists(sDocPath))
 Then

 Err.Raise 9999,,"No Doc Path Defined"

 End If

'----------------------------------------------------------- 

'Open the CATAnalysis Document

sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")

Set
 oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the analysis Manager 

Set 
oAnalysisManagar = oAnalysisDocument.Analysis

'Retrieve the part document and product

Set 
oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments

Set 
partDocument = oAnalysisLinkedDocuments.Item(1)

Set 
product = partDocument.Product

'Retrieve the published edge

Set 
publications1 = product.Publications

Set 
pubFace = publications1.Item("Edge")

'Retrieve the analysis model

Set 
oAnalysisModels = oAnalysisManagar.AnalysisModels

Set 
oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve mesh manager and the surface mesh part by name

Set 
oAnalysisMeshManager = oAnalysisModel.MeshManager 

Set 
oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

Set 
oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create reference from the mesh part

Set 
reference1 = oAnalysisManagar.CreateReferenceFromObject(oAnalysisMeshPart)

'Add the new Coating mesh part to the list of mesh parts

Set 
coat1D = oAnalysisMeshParts.Add ("MSHPart1DCoating") 

'Add the reference previously created

coat2D.AddSupportFromReference NOTHING, reference1

'Set the global specifications

coat2D.SetGlobalSpecification "ExtractionType", 1
```

```
'Create the local specification

Set 
meshSpecs = coat2D.AnalysisMeshLocalSpecifications

Set 
spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2

spec.AddSupportFromPublication "ConnectorList", product, pubFace

'Update mesh part

coat1D.Update

End Sub
```