---
title: "Creating Surface Welding Connection Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro", "CAAAniMeshSurfaceWelding", "CAAAniMeshSrufaceWelding", "CAAAniMeshSurfaceWeldingSource"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSurfaceWelding.htm"
converted: "2026-05-11T11:27:02.551797"
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
		of Reference interface. This is equivalent to the selection of a B-Rep elements 
		inside the interactive application.
		

#### Creating Mesh Part and Assigning Values to its 
		Attributes
		
		

#### Epilog
		
		

To run the macro interactively CATDocView and ADL_ODT_SLASH 
		environment variables must be defined.
	

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create Surface Welding Connection mesh part and 
how to assign values to its global attributes.

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
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
' Retrieve the analysis Manager 
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

' Retrieve the part document and product
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product

' Retrieve the analysis model
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts


'Retrieve the connection design manager and connection
Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
Set connSet = connection.AnalysisSets
Set conn = connSet.ItemByType("ConnectionDesignSet")
Set entity = conn.AnalysisEntities
Set surfConn  = entity.Item(1)
Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

...
```

```vbscript
...
```

```vbscript
'Add new surface analysis connection mesh to the list of mesh parts
Set surfWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSurf") 

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

```vbscript
...
```

```vbscript
...
```