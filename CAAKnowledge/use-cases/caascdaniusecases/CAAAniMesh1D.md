---
title: "Creating 1D Mesh"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAInfLauchMacro", "CAAAniMesh1D", "CAAAniMesh1DSource"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMesh1D.htm"
converted: "2026-05-11T11:27:02.507888"
---

---

		

Open the Analysis document. The Analysis document is fetched in the documentation 
		installation path, this path has already been stored in the `sDocPath` 
		variable. In the collection of documents, two documents can be retrieved: 
		the Analysis document and the Part document. 
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done with the help of Reference interface. This is equivalent 
		to the selection of a B-Rep element inside the interactive applications. 
		In this macro the reference is created from the published face.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

Calling update on the mesh part computes the mesh.
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variables must be defined. After running the macro the mesh may not be immediately visible,
                the user has to go to the Advanced Meshing Tools workbench to see the mesh.
	

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create a 1D mesh part and how to assign values 
to its global specifications.

[Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*



```vbscript
...
```

```vbscript
Sub CATMain()

'----------------------------------------------------------- 
'Optional: allows to find the sample wherever it&#39;s installed
sDocPath=CATIA.SystemService.Environ("CATDocView")
If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
Err.Raise 9999,,"No Doc Path Defined"
End If
'-----------------------------------------------------------
```

```vbscript
'Open the Analysis document 
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Beam.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

```vbscript
...
```

```vbscript
...
```

```vbscript
'Retrieve the Analysis Manager and Analysis Model
Set oAnalysisManager = oAnalysisDocument.Analysis
```

```vbscript
'Retreive the part document from Analysis manager
Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```

```vbscript
'Retrieve the analysis model from the list of models
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)
```

```vbscript
'Retrieve mesh manager and mesh part 
Set oAnalysisMeshManager = oAnalysisModel.MeshManager
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```

```vbscript
'Retrieve publications from product and retrieve the published face.
Set publications = product.Publications
Set pubLine = publications.Item("Line.3")
```

```vbscript
...
```

```vbscript
...
'Add the new beam mesh part to the list of mesh parts
Set beamPart = oAnalysisMeshParts.Add("MSHPart1D")

beamPart.AddSupportFromPublication product, pubLine
beamPart.SetGlobalSpecification "SizeValue", "10.0 mm"
beamPart.SetGlobalSpecification "AbsoluteSag", 1
beamPart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
beamPart.SetGlobalSpecification "MinimumSizeValue", "1.1 mm"
beamPart.SetGlobalSpecification "ElementOrder", "Parabolic"
beamPart.SetGlobalSpecification "MeshCapture", 1
beamPart.SetGlobalSpecification "MeshCaptureTol", "1.1 mm"
beamPart.SetGlobalSpecification "CurveAngle", "40 deg"

&#39;Update the mesh part
beamPart.Update 

...
```

```vbscript
...
 End Sub
...
```