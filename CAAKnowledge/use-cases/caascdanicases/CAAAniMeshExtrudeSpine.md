---
```vbscript
title: "Creating Extrude along a Spine Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshExtrudeSpine"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeSpine.htm"
converted: "2026-05-11T17:31:51.640587"
```

---
## Analysis Modeler

| 
## Creating Extrude along a Spine Mesh Parts  

* * *

  This use case shows how to create a mesh part Extrude along a spine. This macro opens an Analysis document. Extrude along a spine mesh part can generate a 2D mesh from 1D mesh and 3D mesh from 2D mesh. In this macro 3D mesh from 2D surface mesh is created. Global specifications associated with the mesh part are set.   ![](images/ExtrAlongSpineMesh.gif)    
---|---  
This use case shows how to create a mesh part Extrude along a spine. This macro opens an Analysis document. Extrude along a spine mesh part can generate a 2D mesh from 1D mesh and 3D mesh from 2D mesh. In this macro 3D mesh from 2D surface mesh is created. Global specifications associated with the mesh part are set.   ![](images/ExtrAlongSpineMesh.gif)
  CAAAniMeshExtrudeSpine is launched in CATIA [1]. No open document is needed. [CAAAniMeshExtrudeSpine.catvbs](CAAAniMeshExtrudeSpineSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshExtrudeSpine.catvbs) (Windows only).    
  CAAAniMeshExtrudeSpine includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

| 

    ...

    '----------------------------------------------------------- 
```vbscript
'-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

      sDocPath=CATIA.SystemService.Environ("CATDocView")

```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```

```vbscript
    '----------------------------------------------------------- 
    'Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    ...  

---  

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### Extracting the List of Mesh Parts and Publications

    ...

    'Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```

```vbscript
    'Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```

    'Retrieved the published line that is the
```vbscript
'Retrieved the published line that is the
    'spine along which mesh will be extruded
```

```vbscript
    Set publications = product.Publications
    Set pubSpine = publications.Item("Spine")

```

```vbscript
Set publications = product.Publications
Set pubSpine = publications.Item("Spine")
    'Retrieve the analysis model
```

```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```

```vbscript
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create the reference of the surface mesh
    Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
```

    ...  

---  

According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of B-Rep elements inside the interactive application. In this macro reference is created from the surface mesh part.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of B-Rep elements inside the interactive application. In this macro reference is created from the surface mesh part.
    'Add the extrude with translation mesh part to the list of mesh parts

```vbscript
    Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSpine")
    'Assign the surface mesh part as support
    extrudeMesh.AddSupportFromReference NOTHING, reference
    'Set the global specifications
    extrudeMesh.SetGlobalSpecification "Condensation", 0
    extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
    extrudeMesh.SetGlobalSpecification "Length", "10.0 mm"
    extrudeMesh.SetGlobalSpecification "Lentgh1", "100.0 mm"

```

extrudeMesh.SetGlobalSpecification "Length", "10.0 mm"
extrudeMesh.SetGlobalSpecification "Lentgh1", "100.0 mm"
    'Set the specification; spine along which mesh will be extruded
    extrudeMesh.SetSpecificationFromPublication "Direction", product, pubSpine, 0
    'Retrieve the basic components and sub components

```vbscript
    Set basicComps = extrudeMesh.BasicComponents
    Set subBasicComps = basicComps.Item(1).BasicComponents
    'Retrieve each attribute and set its value

    Set subBasicComp1 = subBasicComps.Item("Type")
    subBasicComp1.SetValue "", 0, 0, 0, "Arithmetic"

    Set subBasicComp2 = subBasicComps.Item("NbNodes")
    subBasicComp2.SetValue "", 0, 0, 0, 20

    Set subBasicComp3 = subBasicComps.Item("Symmetric")
    subBasicComp3.SetValue "", 0, 0, 0, "TRUE"

    Set subBasicComp4 = subBasicComps.Item("Ratio")
    subBasicComp4.SetValue "", 0, 0, 0, 10
    'Update the mesh
    extrudeMesh.Update

```

    ...  

---  
#### The extruded mesh can be manipulated with the parameters like distribution type ( Uniform, Arithmetic, Geometric) number of layers, symmetry and ratio. To set these parameters we retrieve the list of basic components (BCs) from the mesh. From the first element of the list we retrieve one more list of the BCs. Then we retrieve each of the BCs by its name and set the values.
#### Epilog

    ...
    End Sub
    ...  

---  

To run the macro interactively CATDocView environment variable must be defined.  

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a extrude with symmetry mesh part and how to assign values to its global specifications.

Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
