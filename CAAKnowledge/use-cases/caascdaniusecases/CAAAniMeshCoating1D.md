---
title: "Creating 1D Coating Mesh Part"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAAniMeshCoating1D", "CAAAniMeshCoating1DSource", "CAAScdAniTechArticles", "CAAAniTocAnalysisDocument", "CAAScdAniUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1D.htm"
converted: "2026-05-11T11:06:32.346628"
---

## Analysis Modeler
		
		
## []Creating 1D Coating Mesh Part
		
	

---

	
		![](../CAAScrBase/images/atarget.gif)
		

[]This use case shows you how to create coating 1D 
		mesh part by extracting edge elements of an existing 2D mesh part. A coating 
		mesh can be extracted from a surface mesh part, advanced surface mesh Part, 
		octree triangle mesh part, coating 2D mesh part or any 2D transformed mesh 
		part. This functionality is available in FEM Surface (FMS) product.
		The macro opens an Analysis document which already contains a surface mesh 
		part. The coating mesh is created over this mesh part. At the end the mesh 
		part is updated to generate mesh.

		![](images/Coating1DMesh.gif)
		

 
		
	
	
		![](../CAAScrBase/images/ainfo.gif)
		

[]CAAAniMeshCoating1D is launched in CATIA [[1]]. 
		No open document is needed.
		

[CAAAniMeshCoating1D.catvbs] 
		is located in the CAAScdAniUseCases module.
		[Execute macro] (Windows only).
		

 
		
	
	
		![](../CAAScrBase/images/ascenari.gif)
		

[]CAAAniMeshCoating1D includes the following steps:
		

			
- [Prolog]
			
- [Extracting the List of Mesh Parts and Publications]
			
- [Creating Mesh part and Assigning Values to its 
			Attributes]
			
- [Epilog]
		
		
#### []Prolog
		
			
				
```
...
```

				
```
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

' Open the Analysis document
 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")

Set
 oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

				
```
...
```

				
			
		
		

Open the Analysis document. The Analysis document is fetched in the documentation 
		installation path, this path is already stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved: 
		the Analysis document and the Part document.
		
#### []Extracting the List of Mesh Parts and Publications
		
			
				
```
...
```

				
```
'Retrieve the Analysis Manager and Analysis Model

Set
 oAnalysisManager = oAnalysisDocument.Analysis
```

				
```
'Retreive the part document from Analysis manager

Set
 oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments

Set
 partDocument = oAnalysisLinkedDocuments.Item(1)

Set
 product = partDocument.Product
```

				
```
'Retrieve the analysis model from the list of models

Set
 oAnalysisModels = oAnalysisManager.AnalysisModels

Set
 oAnalysisModel = oAnalysisManager.Item(1)
```

				
```
'Retrieve mesh manager and mesh part 

Set 
oAnalysisMeshManager = oAnalysisModel.MeshManager

Set 
oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```

				
```
'Retrieve publications from product and retrieve the published surface and edge

Set
 publications1 = product.Publications

Set
 pubEdge = publications1.Item("Edge")
...
```

				
			
		
		

According to the general
		[
		Analysis Document] structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometrical 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of a B-Rep elements inside the interactive application. In 
		this macro the reference is created from the surface mesh part.
		
#### []Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
			
				
```
...

'Add the new Coating mesh part to the list of mesh parts

Set 
coat1D = oAnalysisMeshPart.Add ("MSHPart1DCoating") 
 

'Set the reference to the surface mesh part

coat1D.AddSupportFromReference product, reference1
 

'Assign value to the global specification

coat1D.SetGlobalSpecification "ExtractionType", 1
```

				
```
'Create the local specification

Set 
meshSpecs = coat2D.AnalysisMeshLocalSpecifications

Set 
spec = meshSpecs.Add("MSHCoatingLocalSpecification")
spec.SetAttribute "LocalExtractionType", 2

spec.AddSupportFromPublication "ConnectorList", product, pubFace

'Update the mesh part

coat1D.Update
```

				
```
...
```

				
			
		
		
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
		
#### []Epilog
		
			
				
```
...
 End Sub
...
```

				
			
		
		

To run the macro interactively CATDocView 
		environment variables must be defined.
	

 

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create 1D coating mesh parts and how to assign 
values to its global specifications.

[[Top]]

---

#### []References

	
		|[1]
		[Replaying 
		a Macro]
	
	
		|[[Top]]
	

---

*Copyright 2001, Dassault Systmes. All rights reserved.*