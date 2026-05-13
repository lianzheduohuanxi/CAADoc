---
```vbscript
title: "Creating Octree Triangle Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshOctTriangle", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshOctTriangle.htmmd"
converted: "2026-05-11T17:31:51.677727"
```

---
## Analysis Modeler

|
## Creating Octree Triangle Mesh Parts

* * *

  This use case shows how to create octree triangle mesh part in an existing analysis document. This scenario requires "FEM Surface (FMS) product". This macro opens an Analysis document. Octree trianlge mesh part is created and global specifications associated with this mesh part are set. The local specification: _MSHLocalMeshSize_ is created specifying the edge of the hole as support. The mesh part is updated to generate mesh. ![](images/OctreeTriangleMesh.gif)
---|---
This use case shows how to create octree triangle mesh part in an existing analysis document. This scenario requires "FEM Surface (FMS) product". This macro opens an Analysis document. Octree trianlge mesh part is created and global specifications associated with this mesh part are set. The local specification: _MSHLocalMeshSize_ is created specifying the edge of the hole as support. The mesh part is updated to generate mesh. ![](images/OctreeTriangleMesh.gif)
  CAAAniMeshOctTriangle is launched in CATIA [1]. No open document is needed. [CAAAniMeshOctTriangle.catvbs](CAAAniMeshOctTriangleSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshOctTriangle.catvbs) (Windows only).
  CAAAniMeshOctTriangle includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

|

    ...

```vbscript
    ' -----------------------------------------------------------
```

```vbscript
```vbscript
```vbscript
' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed

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
        End If
```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Open the Analysis document
```vbscript
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Surface.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### Extracting the List of Mesh Parts and Publications

    ...

```vbscript
    ' Retrieve the Analysis Manager and Analysis Model
```

```vbscript
```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
```
    ' Retreive the part document from Analysis manager
```

```

```vbscript
```vbscript
    Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
```vbscript
```
```vbscript
```vbscript
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product

```
```

```

```

```vbscript
```vbscript
Set partDocument = oAnalysisLinkedDocuments.Item(1)
```vbscript
```
```vbscript
```vbscript
Set product = partDocument.Product
    ' Retrieve the analysis model from the list of models
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisModel = oAnalysisManager.Item(1)

```
```

```

```

```vbscript
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
```vbscript
Set oAnalysisModel = oAnalysisManager.Item(1)
    ' Retrieve mesh manager and mesh part
```
```

```

```

```vbscript
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

```
```

```

```

```vbscript
```vbscript
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```vbscript
```
    ' Retrieve publications from product and retrieve the published surface and edge
```

```

```vbscript
```vbscript
    Set publications1 = product.Publications
```vbscript
```
```vbscript
```vbscript
    Set pubEdge = publications1.Item("Edge")
    Set pubSurf = publications1.Item("Round Hole.1")

```
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro the reference is created from the published edge and published face.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro the reference is created from the published edge and published face.
```vbscript
```vbscript
    ' Add the new Octree Triangle mesh part to the list of mesh parts

```

```

```vbscript
```vbscript
```vbscript
    Set  octreePart = meshPart.Add ("MSHPartOctree2D")

```
```

```

```vbscript
```vbscript
Set  octreePart = meshPart.Add ("MSHPartOctree2D")
```vbscript
```
    ' Add support from the published surface
```

    octreePart.AddSupportFromPublication product, pubSurf

```vbscript
```vbscript
    ' Set the global Specifications
```
```

    octreePart.SetGlobalSpecification "SizeValue", "10.0 mm"
    octreePart.SetGlobalSpecification "AbsoluteSageValue", "3.0 mm"
    octreePart.SetGlobalSpecification "ElementOrder", "Parabolic"
    octreePart.SetGlobalSpecification "MinSizeForSags", "0.5 mm"
    octreePart.SetGlobalSpecification "MinGeometrySize", "0.5 mm"
    octreePart.SetGlobalSpecification "AbsoluteSag", 1
    octreePart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
    octreePart.SetGlobalSpecification "ProportionalSag", 1
    octreePart.SetGlobalSpecification "ProportionalSagValue", 0.5
    octreePart.SetGlobalSpecification "MaxWarpAngle", "1.0 rad"
    octreePart.SetGlobalSpecification "Criteria", "Shape"
    octreePart.SetGlobalSpecification "MeshGeometryViolation", "1.2 mm"
    octreePart.SetGlobalSpecification "InteriorSize", 2
    octreePart.SetGlobalSpecification "InteriorSizeValue", "5.0 mm"
    octreePart.SetGlobalSpecification "MinJacobian", 0.3
    octreePart.SetGlobalSpecification "MaxAttempts", 2
```vbscript
    ' Add the domain specifications as local specifications and assign it attributes
```

```

```vbscript
```vbscript
    Set meshspecs1 = octreePart.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
    Set spec1 = meshspecs1.Add("MSHLocalMeshSize")
```
```

    spec1.SetAttribute "MSHMeshSizeMag", "1.0 mm"
    spec1.AddSupportFromPublication "ConnectorList", Product, pubEdge
```vbscript
    'Update mesh part
```

    octreePart.Update
```

    ...

---

The association with the geometry of octree mesh part is established with the use of the method _AddSupportFromPublication._ All the global specifications are set using their names. To create a local mesh of specified size around an edge the global specification _MSHLocalMeshSize_  is created.
#### Epilog

    ...
```vbscript
    End Sub
    ...
```

---

To run the macro interactively CATDocView environment variable must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create octree triangle mesh parts and how to assign values to its local and global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
