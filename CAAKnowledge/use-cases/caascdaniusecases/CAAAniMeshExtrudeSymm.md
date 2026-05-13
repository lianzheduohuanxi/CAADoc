---
title: "Creating Extrude with Symmetry Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshExtrudeSymmSource", "CAAAniMeshExtrudeSymm", "CAAInfLauchMacro"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeSymm.htmmd"
converted: "2026-05-11T11:27:02.510506"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document. 
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done with the help of Reference interface. This is equivalent 
		to the selection of B-Rep elements inside the interactive application. In 
		this macro reference is created from the surface mesh part.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

#### The extruded mesh 
		can be manipulated with the parameters like distribution type ( Uniform, 
		Arithmetic, Geometric) number of layers, symmetry and ratio. To set these 
		parameters we retrieve the list of basic components (BCs) from the mesh. 
		From the first element of the list we retrieve one more list of the BCs. 
		Then we retrieve each of the BC by its name and set the values.
		

#### Epilog
		
		

To run the macro interactively CATDocView and ADL_ODT_SLASH 
		environment variables must be defined.
	

![image](../../assets/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create extrude with symmetry mesh parts and how 
to assign values to its global specifications.

Top]

---

#### References

---

*Copyright  2001, Dassault Systmes. All rights reserved.*

```vbscript
...
```

```vbscript
'----------------------------------------------------------- 
'Optional: allows to find the sample wherever it's installed

```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
'-----------------------------------------------------------
```

```vbscript
'Open the Analysis document 
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
...
```
```

```vbscript
...
```

```vbscript
'Retrieve the analysis Manager 
```vbscript
Set oAnalysisManagar = oAnalysisDocument.Analysis
Set oAnalysisSet = oAnalysisManagar.AnalysisSets

'Retrieve the part document and product
```
```vbscript
Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
Set partDocument = oAnalysisLinkedDocuments.Item(1)
Set product = partDocument.Product
```
```

```vbscript
'Retrieve the published plane
'the mesh will be symmetric along this plane
```vbscript
Set publications = product.Publications
Set pubPlane = publications.Item("SymmetryPlane")
```
```

```vbscript
'Retrieve the analysis model
```vbscript
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

&#39;Retrieve the mesh manager and list of mesh parts
```
```vbscript
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

&#39;Create the reference of the surface mesh
```
```vbscript
Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
...
```
```

```vbscript
...
&#39;Add the extrude with translation mesh part to the list of mesh parts
```vbscript
Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSymmetry")

&#39;Assign the surface mesh part as support
```
extrudeMesh.AddSupportFromReference NOTHING, reference

```vbscript
&#39;Set the global specifications
extrudeMesh.SetGlobalSpecification "Condensation", 0
```
extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
```

```vbscript
```vbscript
&#39;Set the specification; specifying the plane of symmetry
extrudeMesh.SetSpecificationFromPublication "Direction", product, pubPlane, 0
```

&#39;Get the basic components and sub components
```vbscript
Set basicComps = extrudeMesh.BasicComponents
Set subBasicComps = basicComps.Item(1).BasicComponents

&#39;Retrieve each of the attributes by name and set their values
```
```vbscript
Set subBasicComp1 = subBasicComps.Item("Type")
subBasicComp1.SetValue "", 0, 0, 0, "Geometric"
```

```vbscript
Set subBasicComp2 = subBasicComps.Item("NbNodes")
subBasicComp2.SetValue "", 0, 0, 0, 20
```

```vbscript
Set subBasicComp3 = subBasicComps.Item("Symmetric")
subBasicComp3.SetValue "", 0, 0, 0, 2
```

```vbscript
Set subBasicComp4 = subBasicComps.Item("Ratio")
subBasicComp4.SetValue "", 0, 0, 0, 10
```

&#39;Update the mesh
extrudeMesh.Update

...
```

```vbscript
...
```vbscript
End Sub
...
```
```