---
title: "Creating Symmetry Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAAniMeshSymmetrySource", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniTocAnalysisDocument", "CAAAniMeshSymmetry", "CAAScdAniUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSymmetry.htm"
converted: "2026-05-11T11:06:32.463973"
---

## Analysis Modeler
		
		
## []Creating Symmetry Mesh Parts
		
	

---

	
		![](../CAAScrBase/images/atarget.gif)
		

[]This use case shows how to create a symmetry mesh 
		part. Symmetry transformation can be applied to a 1D, 2D and 3D mesh. This 
		scenario requires "FEM Surface (FMS)" product to create 1D or 2D transformed 
		mesh part and FEM Solid (FMD) product to create 3D transformed mesh part.
		

This macro opens an Analysis document. A symmetry mesh part is created 
		on a Surface mesh part. The surface mesh part already exists in the document.
		

 
		

![](images/SymmetryMesh.gif)
		

 
		
	
	
		![](../CAAScrBase/images/ainfo.gif)
		

[]CAAAniMeshSymmetry is launched in CATIA [[1]]. 
		No open document is needed.
		

[CAAAniMeshSymmetry.catvbs] 
		is located in the CAAScdAniUseCases module.
		[Execute macro] (Windows only).
		

 
		
	
	
		![](../CAAScrBase/images/ascenari.gif)
		

[]CAAAniMeshSymmetry includes the following steps:
		

			
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

' Open the Analysis document
 
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
' Retrieve the analysis Manager 

Set 
oAnalysisManagar = oAnalysisDocument.Analysis

Set 
oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product

Set 
oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments

Set 
partDocument = oAnalysisLinkedDocuments.Item(1)

Set 
product = partDocument.Product

' Retrieve the analysis model

Set 
oAnalysisModels = oAnalysisManagar.AnalysisModels

Set 
oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts

Set 
oAnalysisMeshManager = oAnalysisModel.MeshManager 

Set 
oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

Set 
surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create the reference of the surface mesh

Set 
reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
...
```

				
			
		
		

According to the general
		[
		Analysis Document] structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done by using the Reference interface. This is equivalent to 
		the selection of B-Rep elements inside the interactive application. In this 
		macro the reference is created from the surface mesh part.
		
#### []Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
			
				
```
...

'Add the mesh part to list of mesh parts

Set 
meshTrans = oAnalysisMeshParts.Add("MSHPartSymmetry")

'Assign the reference to the mesh part

meshTrans.AddSupportFromReference NOTHING, reference

meshTrans.SetGlobalSpecification "Condensation", 0
meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
meshTrans.SetGlobalSpecification "NbCopies", 2

'Set the specification; the plane of symmetry

meshTrans.SetSpecificationFromPublication "Direction", product, pubPlane, 0

'Update the mesh part

meshTrans.Update

...
```

				
				
			
		
		
#### []Epilog
		
			
				
```
...
 End Sub
...
```

				
			
		
		

To run the macro interactively CATDocView and ADL_ODT_SLASH 
		environment variables must be defined.
	

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create a symmetry mesh part and how to assign 
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