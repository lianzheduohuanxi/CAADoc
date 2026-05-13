---
```vbscript
title: "Creating Extrude with Symmetry Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshExtrudeSymm", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeSymm.htmmd"
converted: "2026-05-11T17:31:51.647580"
```

---
## Analysis Modeler

|
## Creating Extrude with Symmetry Mesh Parts

* * *

  This use case shows how to create extrude with symmetry mesh parts.  This macro opens an Analysis document. The extrude with symmetry mesh part can create a 2D mesh from 1D mesh and 3D mesh from 2D mesh. In this macro 3D mesh is created from 2D mesh. Global specifications associated with the mesh part are set.   ![](images/ExtrWithSymmMesh.gif)
---|---
This use case shows how to create extrude with symmetry mesh parts.  This macro opens an Analysis document. The extrude with symmetry mesh part can create a 2D mesh from 1D mesh and 3D mesh from 2D mesh. In this macro 3D mesh is created from 2D mesh. Global specifications associated with the mesh part are set.   ![](images/ExtrWithSymmMesh.gif)
  CAAAniMeshExtrudeSymm is launched in CATIA [1]. No open document is needed. [CAAAniMeshExtrudeSymm.catvbs](CAAAniMeshExtrudeSymmSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshExtrudeSymm.catvbs) (Windows only).
  CAAAniMeshExtrudeSymm includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

|

    ...

```vbscript
    '-----------------------------------------------------------
```

```vbscript
```vbscript
```vbscript
'-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")

```
```

```

```

```vbscript
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
```vbscript
        End If
    '-----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```vbscript
'-----------------------------------------------------------
    'Open the Analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### Extracting the List of Mesh Parts and Publications

    ...

```vbscript
    'Retrieve the analysis Manager
```

```vbscript
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
```vbscript
```
```vbscript
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```
```

```

```vbscript
```vbscript
```vbscript
    'Retrieve the part document and product
```vbscript
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```
```

```

```

```vbscript
    'Retrieve the published plane
```

```vbscript
```vbscript
```vbscript
'Retrieve the published plane
    'the mesh will be symmetric along this plane
```

```

```

```vbscript
```vbscript
    Set publications = product.Publications
```vbscript
```
```vbscript
```vbscript
    Set pubPlane = publications.Item("SymmetryPlane")

```
```

```

```

```vbscript
```vbscript
Set pubPlane = publications.Item("SymmetryPlane")
```vbscript
```
    'Retrieve the analysis model
```

```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
```vbscript
```
```vbscript
    Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```

```vbscript
```vbscript
```vbscript
    'Retrieve the mesh manager and list of mesh parts
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create the reference of the surface mesh
```
```vbscript
    Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
```
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of B-Rep elements inside the interactive application. In this macro reference is created from the surface mesh part.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of B-Rep elements inside the interactive application. In this macro reference is created from the surface mesh part.
```vbscript
```vbscript
    'Add the extrude with translation mesh part to the list of mesh parts

```

```

```vbscript
```vbscript
    Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrSymmetry")
```vbscript
```
    'Assign the surface mesh part as support
```

    extrudeMesh.AddSupportFromReference NOTHING, reference
```vbscript
```vbscript
    'Set the global specifications
```
```

    extrudeMesh.SetGlobalSpecification "Condensation", 0
    extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"

```

extrudeMesh.SetGlobalSpecification "Condensation", 0
extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
```vbscript
```vbscript
    'Set the specification; specifying the plane of symmetry
```
```

    extrudeMesh.SetSpecificationFromPublication "Direction", product, pubPlane, 0
```vbscript
```vbscript
    'Get the basic components and sub components

```

```

```vbscript
```vbscript
    Set basicComps = extrudeMesh.BasicComponents
```vbscript
```
```vbscript
    Set subBasicComps = basicComps.Item(1).BasicComponents
```
```

```

```vbscript
```vbscript
```vbscript
    'Retrieve each of the attributes by name and set their values
```vbscript
    Set subBasicComp1 = subBasicComps.Item("Type")
```
```

```

```

```vbscript
```vbscript
```vbscript
'Retrieve each of the attributes by name and set their values
```vbscript
Set subBasicComp1 = subBasicComps.Item("Type")
```
```

```

    subBasicComp1.SetValue "", 0, 0, 0, "Geometric"

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
```vbscript
    'Update the mesh
```

    extrudeMesh.Update

```

    ...

---
#### The extruded mesh can be manipulated with the parameters like distribution type ( Uniform, Arithmetic, Geometric) number of layers, symmetry and ratio. To set these parameters we retrieve the list of basic components (BCs) from the mesh. From the first element of the list we retrieve one more list of the BCs. Then we retrieve each of the BC by its name and set the values.
#### Epilog

    ...
```vbscript
    End Sub
    ...
```

---

To run the macro interactively CATDocView and ADL_ODT_SLASH environment variables must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create extrude with symmetry mesh parts and how to assign values to its global specifications.

Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
