---
title: "Creating Nodes Interface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CAAInfLauchMacro", "CAAScdInfUseCases", "CAAAniMeshNodesInterfaceSource", "CAAAniMeshNodesInterface", "CAAScdAniTechArticles", "CAAAniTocAnalysisDocument", "CAAScdAniUseCases", "CATIA", "CAAScrJavaScript"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshNodesInterface.htm"
converted: "2026-05-11T11:06:32.423800"
---

## Analysis Modeler
 
## []Creating Nodes Interface Mesh Parts

---

 
 
	![](../CAAScrBase/images/atarget.gif)
 

[]This use case shows how to create nodes interface 
		mesh parts. This scenario requires "FEM Surface (FMS)".
		

This macro opens an Analysis document. Mesh part nodes interface mesh  
		is created. This mesh part requires a point analysis interface connection 
		as support. The support already exist in the document and is assigned to 
		the mesh part. The mesh part is updated to generate mesh.
		

 
 

		![](images/NodesInterfaceMesh.gif)
 

 
 
	![](../CAAScrBase/images/ainfo.gif)
 

[]CAAAniMeshNodesInterface is launched in CATIA [[1]]. 
 No open document is needed.
 

		[
		CAAAniMeshNodesInterface.catvbs] 
 is located in the CAAScdAniUseCases module. [Execute 
 macro] (Windows only).
 

 
 
	![](../CAAScrBase/images/ascenari.gif)
 

[]CAAAniMeshNodesInterface includes the following steps:
 

 
- [Prolog]
 
- [Extracting the List of Mesh Parts and 
		Publications]
		
- [Creating Mesh part and Assigning Values to its Attributes]
		
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

			
```
...
```

 

Open the Analysis document. The Analysis document is retrieved in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved; 
		the Analysis document and the Part document. 
		
#### []Extracting the List of Mesh Parts and 
		Publications
 
 
 
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

' Retreive the analysis model

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

'Create reference from the surface analysis connection

Set 
reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
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
		elements is done by using the Reference interface. This is equivalent to the 
		selection of a B-Rep element inside the interactive application. In this 
		macro reference is created from the analysis connection.
#### []Creating the Mesh Part and 
		Assigning Values to its Attributes.
 
 
```
...

'Add nodes interface mesh part to the list of mesh parts

Set 
nodeMesh = oAnalysisMeshParts.Add ("MSHPartConnHalfPoint") 

'Assign previously create reference as support

nodeMesh.AddSupportFromReference NOTHING, reference1

'Assign values to its global specifications

nodeMesh.SetGlobalSpecification "Tolerance", "6 mm"
nodeMesh.SetGlobalSpecification "StopUpdateOnError", 2
nodeMesh.SetGlobalSpecification "MiddleCombination", 1

nodeMesh.Update

...
```

		
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

This use case has shown how to create nodes interface mesh parts and how to 
assign values to its global specifications.

 

[[Top]]

---

#### []References
 
 
 |[1]|[Replaying 
 a Macro]
 |[[Top]]

---

*Copyright 2001, Dassault Systmes. All rights 
reserved.*