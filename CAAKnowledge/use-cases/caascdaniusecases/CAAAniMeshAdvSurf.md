---
title: "Creating Advanced Surface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAAniMeshAdvSurf", "CAAInfLauchMacro", "CAAScdInfUseCases", "CATIA", "CAAScdAniTechArticles", "CAAAniTocAnalysisDocument", "CAAScdAniUseCases", "CAAAniMeshAdvSurfSource", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshAdvSurf.htm"
converted: "2026-05-11T11:06:32.452835"
---

## Analysis Modeler
		
		
## []Creating Advanced Surface Mesh Parts
		
	

---

	
		![](../CAAScrBase/images/atarget.gif)
		

[]This use case shows you how to create Advanced surface 
		mesh part on an existing analysis document. This scenario requires "FEM 
		Surface (FMS)" product.
		

This macro opens an existing Analysis document. Advanced surface mesh 
		part is created and global specifications associated with this mesh part 
		are set. The local specification: *MSHDistributionElement* is created 
		around the edge of the hole. The mesh part is updated to generate mesh.
		

 
		

![](images/SurfaceMesh.gif)
		

 
		
	
	
		![](../CAAScrBase/images/ainfo.gif)
		

[]CAAAniMeshAdvSurf is launched in CATIA [[1]]. 
		No open document is needed.
		

[CAAAniMeshAdvSurf.catvbs] is 
		located in the CAAScdAniUseCases module.
		[Execute macro] (Windows only).
		

 
		
	
	
		![](../CAAScrBase/images/ascenari.gif)
		

[]CAAAniMeshAdvSurf includes the following steps:
		

			
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
' ----------------------------------------------------------- 

' Optional: allows to find the sample wherever it's installed

 sDocPath=CATIA.SystemService.Environ("CATDocView")

 If 
(Not CATIA.FileSystem.FolderExists(sDocPath))
 Then

 Err.Raise 9999,,"No Doc Path Defined"

 End If

' ----------------------------------------------------------- 

'Open the Analysis document
 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")

Set
 oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

				
```
...
```

				
			
		
		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document. 
		
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

Set
 pubSurf = publications1.Item("Round Hole.1")
```

				
```
...
```

				
			
		
		

According to the general
		[
		Analysis Document] structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of a B-Rep element inside the interactive application. Here 
		the reference is created from a published face.
		
#### []Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
			
				
```
...

'Add the new Advanced surface mesh part to the list of mesh parts

Set 
surfPart = meshParts.Add ("MSHPartSmartSurf")
```

				
```
'Add support from the published surface

surfPart.AddSupportFromPublication product, pubSurf
```

				

'Set the global 
				Specifications

				surfPart.SetGlobalSpecification "GlobalMethod", "Frontal triangle"

				surfPart.SetGlobalSpecification "GlobalSize", "20.0 mm"

				surfPart.SetGlobalSpecification "MinimumSize", "1.0 mm"

				surfPart.SetGlobalSpecification "ElementOrder", "Parabolic"

				surfPart.SetGlobalSpecification "FaceAngle", "0.0 deg"

				surfPart.SetGlobalSpecification "CurveAngle", "0.0 deg"

				surfPart.SetGlobalSpecification "DetailsElimination", 1

				surfPart.SetGlobalSpecification "StripOptimization", 1

				surfPart.SetGlobalSpecification "CleanSize", "1.0 mm"

				surfPart.SetGlobalSpecification "Offset", "0.0 mm"

				surfPart.SetGlobalSpecification "OffsetFromThickness", "0.0 mm"

				surfPart.SetGlobalSpecification "MinimizeTriangles", 1.

				surfPart.SetGlobalSpecification "MinSizeForSag", "1.0 mm"

				surfPart.SetGlobalSpecification "CurveCaptureTol", "1.0 mm"

				surfPart.SetGlobalSpecification "OptimizeRegularity", 1

				surfPart.SetGlobalSpecification "MeshRelSagValue", "1.0 mm"

				surfPart.SetGlobalSpecification "MeshRelSag", 1

				surfPart.SetGlobalSpecification "ConstraintSagValue", "1.0 mm"

				surfPart.SetGlobalSpecification "CurveCapture", 1

				surfPart.SetGlobalSpecification "MeshCapture", 1

				surfPart.SetGlobalSpecification "MeshCapturTol", "1.0 mm"

				surfPart.SetGlobalSpecification "MeshAbsSag", 2

				surfPart.SetGlobalSpecification "MeshAbsSagValue", "1.0 mm"

				

				

				'Add the domain specifications as local specifications 
				and assign values to its attributes

				Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications

				Set spec = meshSpecs.Add("MSHDistributionElement")

				spec.SetAttribute "NbElements", 50

				spec.SetAttribute "Type", "Isometric"

				spec.AddSupportFromPublication "Supports", product, pubEdge

				

				'Update the mesh part

				surfPart.Update

 
				

...
				
				
			
		
		

Here parameters are set with their respective units, this helps in 
		setting up of the parameters independent of the unit settings. Calling update on the mesh part computes the mesh.
		
#### []Epilog
		
			
				
```
...
 End Sub
...
```

				
			
		
		

To run the macro interactively CATDocView 
		environment variable must be defined.
	

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create advanced surface mesh parts and how to 
assign values to its local and global specifications.

[[Top]]

---

#### []References

	
		|[1]
		[Replaying 
		a Macro]
	
	
		|[[Top]]
	

---

*Copyright 2001, Dassault Systmes. All rights reserved.*