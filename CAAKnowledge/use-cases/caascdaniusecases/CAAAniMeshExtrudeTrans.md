---
title: "Creating Extrude with Translation Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAScrJavaScript", "CAAAniTocAnalysisDocument", "CAAScdInfUseCases", "CAAScdAniTechArticles", "CAAAniMeshExtrudeTrans", "CAAInfLauchMacro", "CAAAniMeshExtrudeTransSource"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeTrans.htm"
converted: "2026-05-11T11:27:02.538117"
---

---

		

Open the Analysis document. The Analysis document is retrieved in the 
		documentation installation path, this path has already been stored in the
		`sDocPath` variable. In the collection of documents, two documents 
		can be retrieved; the Analysis document and the Part document. 
		

#### Extracting the List of Mesh Parts and Publications
		
		

According to the general
		[
		Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures 
		to navigate or retrieve the required objects. First, from the **Document**, 
		we find the **Analysis Manager Object**, the **Analysis Models** and 
		the **Mesh Manager Objects**. The extraction of pre-defined geometric 
		elements is done with the help of Reference interface. This is equivalent 
		to the selection of B-Rep elements inside the interactive application. In 
		this macro reference is created from the published face.
		

#### Creating the Mesh Part and Assigning Values to 
		its Attributes.
		
		

#### The extruded mesh 
		can be manipulated with the parameters like distribution type ( Uniform, 
		Arithmetic, Geometric) number of layers, symmetry and ratio. To set these 
		parameters we retrieve the list of basic components (BCs) from the mesh. 
		From the first element of the list we retrieve one more list of the BCs. 
		Then we retrieve each of the BC by its name and set the values.
		

#### Epilog
		
		

To run the macro interactively CATDocView 
		environment variable must be defined.
	

![](../CAAScrBase/images/aendtask.gif)

[Top]

---

#### In Short

This use case has shown how to create extrude with translation mesh part and 
how to assign values to its global specifications.

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
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online\CAAScdAniUseCases\samples\Surface.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

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
```

```vbscript
' Retrieve the published line
' the mesh will be extruded with translation along this line
Set publications = product.Publications
Set pubDirection = publications.Item("Direction")

' Retrieve the analysis model
Set oAnalysisModels = oAnalysisManagar.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)

'Retrieve the mesh manager and list of mesh parts
Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")

'Create the reference of the surface mesh
Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
...
```

```vbscript
...

'Add the extrude with translation mesh part to the list of mesh parts
Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrTranslation")

'Assign the surface mesh part as support
extrudeMesh.AddSupportFromReference NOTHING, reference

'Set the global specifications
extrudeMesh.SetGlobalSpecification "Condensation", 0
extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
extrudeMesh.SetGlobalSpecification "Length", "10.0 mm"
extrudeMesh.SetGlobalSpecification "Length1", "100.0 mm"
```

```vbscript
'Set the specification; the direction of translation
extrudeMesh.SetSpecificationFromPublication "Direction", product, pubDirection, 0

'Retrieve the basic component and sub components
Set basicComps = extrudeMesh.BasicComponents
Set subBasicComps = basicComps.Item(1).BasicComponents

'Retrieve each of the attribute and set its value

Set subBasicComp1 = subBasicComps.Item("Type")
subBasicComp1.SetValue "", 0, 0, 0, "Arithmetic"

Set subBasicComp2 = subBasicComps.Item("NbNodes")
subBasicComp2.SetValue "", 0, 0, 0, 20

Set subBasicComp3 = subBasicComps.Item("Symmetric")
subBasicComp3.SetValue "", 0, 0, 0, 2

Set subBasicComp4 = subBasicComps.Item("Ratio")
subBasicComp4.SetValue "", 0, 0, 0, 10

'Update the mesh
extrudeMesh.Update

...
```

```vbscript
...
End Sub
...
```