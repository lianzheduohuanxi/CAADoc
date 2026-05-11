---
title: "Creating Tetrahedron Filler Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshTetraFillerSource", "CAAInfLauchMacro", "CAAAniMeshTetraFiller"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshTetraFiller.htm"
converted: "2026-05-11T11:27:02.529704"
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
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. 
		

The extraction of pre-defined geometric elements is done with the help 
		of Reference interface. This is equivalent to the selection of a B-Rep element 
		inside the interactive applications.
		

#### Creating Mesh Part and Assigning Values to its 
		Attributes
		
		

#### Epilog
		
		

To run the macro interactively CATDocView  
		environment variable must be defined. After running the macro the mesh may not be immediately visible,
                the user has to go to the Advanced Meshing Tools workbench to see the mesh.
	

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create a mesh part and how to assign other mesh 
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
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
' ----------------------------------------------------------- 
' Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

...
```

```vbscript
...
```

```vbscript
' Retrieve the Analysis Manager
Set oAnalysisManager = oAnalysisDocument.Analysis

' Retrieve the part document and product
Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
Set PartDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
			
' Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

' Retrieve mesh manager and mesh part from the list of mesh parts specifying its name
Set oAnalysisMeshManager = oAnalysisModel.MeshManager
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")

' Create Reference from the mesh part.
Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)
...
```

```vbscript
...
```

```vbscript
' Add the new Tetrahedron Filler mesh part to the list of mesh parts
Set tetraFiller = oAnalysisMeshParts.Add("MHSPartGHS3D")

' Add reference previously created
tetraFiller.AddSupportFromReference NOTHING, reference1

' Set the global Specifications
tetraFiller.SetGlobalSpecification "Propagation", 1.5
tetraFiller.SetGlobalSpecification "ElementOrder", "Parabolic"

'Update the mesh part
tetraFiller.Update
...
```

```vbscript
...
```

```vbscript
...
```