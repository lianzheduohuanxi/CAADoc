---
title: "Creating 1D Coating Mesh Part"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshCoating1D", "CAAAniMeshCoating1DSource", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1D.htmmd"
converted: "2026-05-11T11:27:02.516386"
---

---

		

Open the Analysis document. The Analysis document is fetched in the documentation 
		installation path, this path is already stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved: 
		the Analysis document and the Part document.
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometrical 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of a B-Rep elements inside the interactive application. In 
		this macro the reference is created from the surface mesh part.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

#### The local 
		specification specifies the edges which are to be included or excluded 
		while computing the coating mesh. You can specify multiple edges to one 
		local specification. If you want to include some edges, and exclude some 
		other then you need to create at least two local specifications. All the 
		edges which are to be included, can be added as support to one local 
		specification with the attribute "LocalExtractionType" valuated to 1. 
		Similarly edges which are to be exclude can be added as support to other 
		local specification with the attribute "LocalExtractionType" valuated to 
		2.
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variables must be defined.
	

 

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create 1D coating mesh parts and how to assign 
values to its global specifications.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
```

```vbscript
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
...
```
```

```vbscript
...

&#39;Add the new Coating mesh part to the list of mesh parts
```vbscript
Set coat1D = oAnalysisMeshPart.Add ("MSHPart1DCoating") 
 
&#39;Set the reference to the surface mesh part
coat1D.AddSupportFromReference product, reference1
```
 
&#39;Assign value to the global specification
coat1D.SetGlobalSpecification "ExtractionType", 1
```

```vbscript
'Create the local specification
```vbscript
Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2
```

spec.AddSupportFromPublication "ConnectorList", product, pubFace

&#39;Update the mesh part
coat1D.Update
```

```vbscript
...
```

```vbscript
...
```vbscript
 End Sub
```
...
```