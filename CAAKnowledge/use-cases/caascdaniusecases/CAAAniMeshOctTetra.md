---
title: "Creating Octree Tetrahedron Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshOctTetra", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniMeshOctTetraSource", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshOctTetra.htmmd"
converted: "2026-05-11T11:27:02.532772"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document.
		

#### **Extracting the Product and Publications for 
		Meshing**
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done with the help of Reference interface. This is equivalent 
		to the selection of a B-Rep elements inside the interactive application. 
		In this macro reference is created from published body and published edge.
		

#### Creating Mesh Part and Assigning Values to its 
		Attributes
		
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variable must be defined. After running the macro the mesh may not be immediately visible,
                the user has to go to the Afvanced meshing tools workbench to see the mesh.
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create octree tetrahedron mesh parts and how to 
assign its local and global specifications.

 

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

```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 
&#39; Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
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
&#39; Retrieve the Analysis Manager and Analysis Model
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

&#39; Retrieve the part document from Analysis manager
```
```vbscript
Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```
```

```vbscript
&#39; Retrieve the analysis model from the list of models
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)

&#39; Retrieve mesh manager and mesh part 
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

&#39; Retrieve publications from product and retrieve the published face.
```
```vbscript
Set publications1 = product.Publications
Set pubEdge = publications1.Item("Edge")
Set pubPartBody = publications1.Item("PartBody")
...
```
```

```vbscript
...
```

```vbscript
&#39; Add the new Octree tetrahedron mesh part to the list of mesh parts
```vbscript
Set octreePart = meshParts.Add ("MSHPartOctree3D")

```

&#39; Add reference previously created
octreePart.AddSupportFromPublication product, pubPartBody

octreePart.SetGlobalSpecification "SizeValue", "10.0 mm"
octreePart.SetGlobalSpecification "AbsoluteSagValue", "3.0 mm"
octreePart.SetGlobalSpecification "ElementOrder", "Parabolic"
octreePart.SetGlobalSpecification "MaxInteriorSize", "1.2 mm"
octreePart.SetGlobalSpecification "MinSizeForSags", "0.5 mm"
octreePart.SetGlobalSpecification "MinGeometrySize", "0.5 mm"
octreePart.SetGlobalSpecification "AbsoluteSag", 1
octreePart.SetGlobalSpecification "MaxWarpAngle", "1.0 rad"
octreePart.SetGlobalSpecification "Criteria", "Skewness"
octreePart.SetGlobalSpecification "MeshGeometryViolation", 1
octreePart.SetGlobalSpecification "InteriorSize", 1
octreePart.SetGlobalSpecification "MinJacobian", 0.3
octreePart.SetGlobalSpecification "MaxAttempts", 2
octreePart.SetGlobalSpecification "MeshViolationValue", "0.5 mm"
octreePart.SetGlobalSpecification "ProportionalSag", 1
octreePart.SetGlobalSpecification "ProportionalSagValue", "0.5 mm"

&#39; Add the Mesh local size as local specifications and assign it attributes
```vbscript
Set meshspecs1 = octreePart.AnalysisMeshLocalSpecifications
Set spec1 = meshspecs1.Add("MSHLocalMeshSize")
spec1.SetAttribute "MSHMeshSizeMag", "1.5 mm"
```
spec1.AddSupportFromPublication "ConnectorList", product, pubedge

&#39;Update the mesh part
octreePart.Update

...
```

```vbscript
...
```

```vbscript
...
```