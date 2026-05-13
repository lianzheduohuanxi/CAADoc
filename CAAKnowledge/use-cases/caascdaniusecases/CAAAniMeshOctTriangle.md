---
title: "Creating Octree Triangle Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshOctTriangleSource", "CAAInfLauchMacro", "CAAAniMeshOctTriangle"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshOctTriangle.htmmd"
converted: "2026-05-11T11:27:02.536898"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document. 
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of a B-Rep elements inside the interactive application. In 
		this macro the reference is created from the published edge and published 
		face.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

The association with the geometry of octree mesh part is established 
		with the use of the method *AddSupportFromPublication. *All the global 
		specifications are set using their names. To create a local mesh of specified 
		size around an edge the global specification *MSHLocalMeshSize * is 
		created.
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variable must be defined.
	

 

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create octree triangle mesh parts and how to assign 
values to its local and global specifications.

 

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
```

```vbscript
' ----------------------------------------------------------- 
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
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```vbscript
...
```

```vbscript
...
```

```vbscript
' Retrieve the Analysis Manager and Analysis Model
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
' Retreive the part document from Analysis manager
```vbscript
Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```
```

```vbscript
' Retrieve the analysis model from the list of models
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)
```
```

```vbscript
' Retrieve mesh manager and mesh part 
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```
```

```vbscript
' Retrieve publications from product and retrieve the published surface and edge
```vbscript
Set publications1 = product.Publications
Set pubEdge = publications1.Item("Edge")
Set pubSurf = publications1.Item("Round Hole.1")
```
```

```vbscript
...
```

```vbscript
...
' Add the new Octree Triangle mesh part to the list of mesh parts
```vbscript
Set  octreePart = meshPart.Add ("MSHPartOctree2D")
```
```

```vbscript
' Add support from the published surface
octreePart.AddSupportFromPublication product, pubSurf
```

```vbscript
```vbscript
' Set the global Specifications
octreePart.SetGlobalSpecification "SizeValue", "10.0 mm"
```
octreePart.SetGlobalSpecification "AbsoluteSageValue", "3.0 mm"
octreePart.SetGlobalSpecification "ElementOrder", "Parabolic"
octreePart.SetGlobalSpecification "MinSizeForSags", "0.5 mm"
octreePart.SetGlobalSpecification "MinGeometrySize", "0.5 mm"
octreePart.SetGlobalSpecification "AbsoluteSag", 1
octreePart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
octreePart.SetGlobalSpecification "ProportionalSag", 1
octreePart.SetGlobalSpecification "ProportionalSagValue", 0.5
octreePart.SetGlobalSpecification "MaxWarpAngle", "1.0 rad"
octreePart.SetGlobalSpecification "Criteria", "Shape"
octreePart.SetGlobalSpecification "MeshGeometryViolation", "1.2 mm"
octreePart.SetGlobalSpecification "InteriorSize", 2
octreePart.SetGlobalSpecification "InteriorSizeValue", "5.0 mm"
octreePart.SetGlobalSpecification "MinJacobian", 0.3
octreePart.SetGlobalSpecification "MaxAttempts", 2

' Add the domain specifications as local specifications and assign it attributes
```vbscript
Set meshspecs1 = octreePart.AnalysisMeshLocalSpecifications
Set spec1 = meshspecs1.Add("MSHLocalMeshSize")
spec1.SetAttribute "MSHMeshSizeMag", "1.0 mm"
```
spec1.AddSupportFromPublication "ConnectorList", Product, pubEdge

'Update mesh part
octreePart.Update
...
```

```vbscript
...
```vbscript
End Sub
...
```
```