---
title: "Creating 2D Coating Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniMeshCoating2DSource", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshCoating1D", "CAAInfLauchMacro", "CAAAniMeshCoating2D"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating2D.htmmd"
converted: "2026-05-11T11:27:02.492268"
---

---

		

Open the Analysis document. The Analysis document is fetched in the documentation 
		installation path, this path is already stored in the `sDocPath` 
		variable. If this variable is not valuated then error is raised. In the collection of documents, two documents can be retrieved: 
		the Analysis document and the Part document. 
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of a B-Rep elements inside the interactive application. In 
		this macro the reference is created from the octree tetrahedron mesh part.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

#### The local 
		specification specifies the faces which are to be included or excluded 
		while computing the coating mesh. You can specify multiple faces to one 
		local specification. If you want to include some faces, and exclude some 
		other then you need to create at least two local specifications. All the 
		faces which are to be included, can be added as support to one local 
		specification with the attribute "LocalExtractionType" valuated to 
		1. Similarly faces which are to be exclude can be added as support to other 
		local specification with the attribute "LocalExtractionType" valuated to 
		2.
		

 
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variables must be defined. After running the macro the mesh may not be immediately visible,
                the user has to go to the Advanced Meshing Tools workbench to see the mesh.
	

 

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create 2D coating mesh parts and how to assign 
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
'----------------------------------------------------------- 
'Optional: allows to find the sample wherever it&#39;s installed
```vbscript
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
'----------------------------------------------------------- 

'Open the Analysis document 
```vbscript
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
'Retrieve the analysis Manager 
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```
```

```vbscript
&#39;Retrieve the published face
```vbscript
Set publications1 = product.Publications
Set pubFace = publications1.Item("Top")

'Retreive the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39;Retrive The mesh manager and the list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

&#39;Retrieve the already existing Octree mesh part
```
```vbscript
Set oAnalysisMeshPart = oAnalysisMeshParts.Item(1)
```
```

```vbscript
&#39;Create reference from the mesh part
```vbscript
Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)

```

...
```

```vbscript
...

&#39;Add the new Coating mesh part to the list of mesh parts
```vbscript
Set coat2D = oAnalysisMeshPart.Add ("MSHPart2DCoating") 
 
&#39;Set the reference to the surface mesh part
coat2D.AddSupportFromReference product, reference1
```
 
&#39;Assign value to the global specification
coat2D.SetGlobalSpecification "ExtractionType", 1
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

...
```

```vbscript
...
```vbscript
End Sub
...
```
```