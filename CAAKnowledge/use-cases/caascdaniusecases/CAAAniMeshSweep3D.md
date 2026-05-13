---
title: "Creating Sweep 3D Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshSweep3D", "CAAAniMeshSweep3DSource", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSweep3D.htmmd"
converted: "2026-05-11T11:27:02.488040"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document. 
		

#### **Extracting the Reference Object from the 
		Part Document for  Meshing**
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. 
		

The extraction of pre-defined geometrical arena is done by using the 
		Reference interface. This is equivalent to the selection of a B-Rep element 
		inside the interactive applications.
		

#### Creating Mesh Part and Assigning Values to its 
		Attributes
		
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variable must be defined.
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create mesh parts and how to assign other mesh 
parts as supports.

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
' Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis&quot;)
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
' Retrieve the analysis Manager 
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

'Retrieve the publications
```
```vbscript
Set publications = product.Publications
Set pubBody = publications.Item("PartBody")

' Retrieve the analysis model
```
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

```

...
```

```vbscript
...
```

```vbscript
'Add Sweep 3D mesh part to the list of mesh parts
```vbscript
Set sweep3D = oAnalysisMeshParts.Add ("MSHPartSweep3D") 

```

'Add support from the published body
sweep3D.AddSupportFromPublication product, pubBody
```

```vbscript
sweep3D.SetSpecificationFromPublication "Top", product, pubTopFace, 0
sweep3D.SetSpecificationFromPublication "Bottom", product, pubBotFace, 0

```vbscript
'Set the global specification
sweep3D.SetGlobalSpecification "ElementOrder", "Linear"
```
sweep3D.SetGlobalSpecification "GuideAngle", &quot;60 deg&quot;
sweep3D.SetGlobalSpecification "NbElements", 10
sweep3D.SetGlobalSpecification "DistributionType", "Arithmetic"
sweep3D.SetGlobalSpecification "Ratio", 5.0
sweep3D.SetGlobalSpecification "CaptureTol", 1.0

sweep3D.Update
...
```

```vbscript
...
```

```vbscript
...
```