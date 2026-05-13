---
title: "CAAAniMeshExtrudeSpine.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshExtrudeSpine", "CAAScrBase", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeSpineSource.htmmd"
converted: "2026-05-11T11:27:02.570935"
---

'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Create Extrude mesh along a spine mesh part
'                assign the Surface Mesh as support
'                specify the global specifications
'  Assumptions:   Looks for surface.CATAnalysis in the directory and surface Analysis Connection
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
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieved the published line that is the
```
'spine along which mesh will be extruded
```vbscript
Set publications = product.Publications
Set pubSpine = publications.Item("Spine")

'Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create the reference of the surface mesh
```
```vbscript
Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)

'Add the extrude with translation mesh part to the list of mesh parts
```
```vbscript
Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSpine")

'Assign the surface mesh part as support
```
extrudeMesh.AddSupportFromReference NOTHING, reference

```vbscript
'Set the global specifications
extrudeMesh.SetGlobalSpecification "Condensation", 1
```
extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
extrudeMesh.SetGlobalSpecification "Length", "500.0 mm"
extrudeMesh.SetGlobalSpecification "Lentgh1", "10.0 mm"

```vbscript
'Set the specification; spine along which mesh will be extruded
extrudeMesh.SetSpecificationFromPublication "Direction", product, pubSpine, 0
```

'Retrieve the basic components and sub components
```vbscript
Set basicComps = extrudeMesh.BasicComponents
Set subBasicComps = basicComps.Item(1).BasicComponents

'Retrieve each attribute and set its value
```

```vbscript
Set subBasicComp1 = subBasicComps.Item("Type")
subBasicComp1.SetValue "", 0, 0, 0, "Arithmetic"
```

```vbscript
Set subBasicComp2 = subBasicComps.Item("NbNodes")
subBasicComp2.SetValue "", 0, 0, 0, 20
```

```vbscript
Set subBasicComp3 = subBasicComps.Item("Symmetric")
subBasicComp3.SetValue "", 0, 0, 0, "TRUE"
```

```vbscript
Set subBasicComp4 = subBasicComps.Item("Ratio")
subBasicComp4.SetValue "", 0, 0, 0, 10
```

'Update the mesh
extrudeMesh.Update

```vbscript
End Sub

```

```vbscript
'COPYRIGHT DASSAULT SYSTEMES 2000

'***********************************************************************
'  Purpose:      Open an analysis document
'                Create Extrude mesh along a spine mesh part
'                assign the Surface Mesh as support
'                specify the global specifications
'  Assumptions:   Looks for surface.CATAnalysis in the directory and surface Analysis Connection
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
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

'Retrieve the analysis Manager 
```
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieved the published line that is the
```
'spine along which mesh will be extruded
```vbscript
Set publications = product.Publications
Set pubSpine = publications.Item("Spine")

'Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create the reference of the surface mesh
```
```vbscript
Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)

'Add the extrude with translation mesh part to the list of mesh parts
```
```vbscript
Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSpine")

'Assign the surface mesh part as support
```
extrudeMesh.AddSupportFromReference NOTHING, reference

```vbscript
'Set the global specifications
extrudeMesh.SetGlobalSpecification "Condensation", 1
```
extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
extrudeMesh.SetGlobalSpecification "Length", "500.0 mm"
extrudeMesh.SetGlobalSpecification "Lentgh1", "10.0 mm"

```vbscript
'Set the specification; spine along which mesh will be extruded
extrudeMesh.SetSpecificationFromPublication "Direction", product, pubSpine, 0
```

'Retrieve the basic components and sub components
```vbscript
Set basicComps = extrudeMesh.BasicComponents
Set subBasicComps = basicComps.Item(1).BasicComponents

'Retrieve each attribute and set its value
```

```vbscript
Set subBasicComp1 = subBasicComps.Item("Type")
subBasicComp1.SetValue "", 0, 0, 0, "Arithmetic"
```

```vbscript
Set subBasicComp2 = subBasicComps.Item("NbNodes")
subBasicComp2.SetValue "", 0, 0, 0, 20
```

```vbscript
Set subBasicComp3 = subBasicComps.Item("Symmetric")
subBasicComp3.SetValue "", 0, 0, 0, "TRUE"
```

```vbscript
Set subBasicComp4 = subBasicComps.Item("Ratio")
subBasicComp4.SetValue "", 0, 0, 0, 10
```

'Update the mesh
extrudeMesh.Update

```vbscript
End Sub
```
```