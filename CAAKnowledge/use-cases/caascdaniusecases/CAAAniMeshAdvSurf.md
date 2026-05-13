---
title: "Creating Advanced Surface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniMeshAdvSurf", "CAAAniMeshAdvSurfSource", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshAdvSurf.htmmd"
converted: "2026-05-11T11:27:02.561890"
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
		the selection of a B-Rep element inside the interactive application. Here 
		the reference is created from a published face.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

Here parameters are set with their respective units, this helps in 
		setting up of the parameters independent of the unit settings. Calling update on the mesh part computes the mesh.
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variable must be defined.
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create advanced surface mesh parts and how to 
assign values to its local and global specifications.

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
'Open the Analysis document 
```cpp
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
'Retrieve the Analysis Manager and Analysis Model
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
'Retreive the part document from Analysis manager
```vbscript
Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```
```

```vbscript
'Retrieve the analysis model from the list of models
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)
```
```

```vbscript
'Retrieve mesh manager and mesh part 
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```
```

```vbscript
'Retrieve publications from product and retrieve the published surface and edge
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
'Add the new Advanced surface mesh part to the list of mesh parts
```vbscript
Set surfPart = meshParts.Add ("MSHPartSmartSurf")
```
```

```vbscript
'Add support from the published surface
surfPart.AddSupportFromPublication product, pubSurf
```

```vbscript
...
```vbscript
 End Sub
...
```
```