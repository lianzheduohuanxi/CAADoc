---
title: "Creating Surface Welding Connection Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAAniMeshSrufaceWelding", "CAAAniMeshSurfaceWelding", "CAAScdAniTechArticles", "CAAAniTocAnalysisDocument", "CAAAniMeshSurfaceWeldingSource", "CAAScdAniUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSurfaceWelding.htm"
converted: "2026-05-11T11:06:32.428373"
---

## Analysis Modeler
		
		
## []Creating Surface Welding Connection Mesh Parts
		
	

---

	
		![](../CAAScrBase/images/atarget.gif)
		

[]This use case shows you how to create surface welding 
		connection mesh parts. This scenario requires "FEM Surface (FMS)".
		

The macro opens an analysis document. Seam welding connection mesh can 
		be created on surface analysis connection and surface analysis connection 
		within one part. In this macro the mesh is created on surface analysis connection 
		which already exists in the document. The connection is assigned as support 
		to the mesh part and it is updated to generate mesh.
		

![](images/SurfaceWeldMesh.gif)
		

 
		
	
	
		![](../CAAScrBase/images/ainfo.gif)
		

[]CAAAniMeshSrufaceWelding is launched in CATIA [[1]]. 
		No open document is needed.
		

[CAAAniMeshSurfaceWelding.catvbs] 
		is located in the CAAScdAniUseCases module.
		[Execute macro] (Windows 
		only).
		

 
		
	
	
		![](../CAAScrBase/images/ascenari.gif)
		

[]CAAAniMeshSurfaceWelding includes the following steps:
		

			
- [Prolog]
			
- [Extracting from the Part Document the Reference 
			Object for Meshing]
			
- [Creating Mesh Part and Assigning Values to its 
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
 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis")

Set
 oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

				****
```
...
```

				
			
		
		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document.
		
#### []**Extracting the Reference Object from the 
		Part Document for  Meshing**
		
			
				
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

'Retrieve the connection design manager and connection

Set 
connection = oAnalysisSet.ItemByType("ConnectionDesignManager")

Set 
connSet = connection.AnalysisSets

Set 
conn = connSet.ItemByType("ConnectionDesignSet")

Set 
entity = conn.AnalysisEntities

Set 
surfConn = entity.Item(1)

Set 
reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

...
```

				
			
		
		

According to the general
		[
		Analysis Document] structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. 
		

The extraction of pre-defined geometric elements is done with the help 
		of Reference interface. This is equivalent to the selection of a B-Rep elements 
		inside the interactive application.
		
#### []Creating Mesh Part and Assigning Values to its 
		Attributes
		
			
				
```
...
```

				
```
'Add new surface analysis connection mesh to the list of mesh parts

Set 
surfWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSurf") 

'Assign previously created reference as support

surfWeld.AddSupportFromReference NOTHING, reference1

'Assign values to its global attributes

surfWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
surfWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
surfWeld.SetGlobalSpecification "StopUpdateOnError", 2
surfWeld.SetGlobalSpecification "MiddleCombination", 10

'Update the mesh part

surfWeld.Update
...
```

				
			
		
		
#### []Epilog
		
			
				
```
...
```

				 End Sub
				
```
...
```

				
			
		
		

To run the macro interactively CATDocView and ADL_ODT_SLASH 
		environment variables must be defined.
	

![](../CAAScrBase/images/aendtask.gif)

[[Top]]

---

#### []In Short

This use case has shown how to create Surface Welding Connection mesh part and 
how to assign values to its global attributes.

[[Top]]

---

#### []References

	
		|[1]
		[Replaying 
		a Macro]
	
	
		|[[Top]]
	

---

*Copyright 2001, Dassault Systmes. All rights reserved.*