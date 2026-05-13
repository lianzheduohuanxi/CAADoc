---
```vbscript
title: "Creating Octree Tetrahedron Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshOctTetra"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshOctTetra.htmmd"
converted: "2026-05-11T17:31:51.671739"
```

---
## Analysis Modeler

|
## Creating Octree Tetrahedron Mesh Parts

* * *

  This macro shows you how to create an octree tetrahedron mesh parts. This macro opens an Analysis document and creates an octree tetrahedron mesh part. Global specifications associated with this mesh part are set. The local specification: _MSHLocalMeshSize_ is created at one of the edges of the part. This scenario requires "FEM Solid (FMD) product". ![](images/OctreeMesh.gif)
---|---
This macro shows you how to create an octree tetrahedron mesh parts. This macro opens an Analysis document and creates an octree tetrahedron mesh part. Global specifications associated with this mesh part are set. The local specification: _MSHLocalMeshSize_ is created at one of the edges of the part. This scenario requires "FEM Solid (FMD) product". ![](images/OctreeMesh.gif)
  CAAAniMeshOctTetra is launched in CATIA [1]. No open document is needed. [CAAAniMeshOctTetra.catvbs](CAAAniMeshOctTetraSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshOctTetra.catvbs) (Windows only).
  CAAAniMeshOctTetra includes the following steps:

  1. Prolog
  2. Extracting the Product and Publications for Meshing
  3. Creating Mesh Part and Assigning Values to its Attributes
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### **Extracting the Product and Publications for Meshing**

    ...

```vbscript
    ' Retrieve the Analysis Manager and Analysis Model
```

```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
```vbscript
```vbscript
    ' Retrieve the part document from Analysis manager
```vbscript
    Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```
```

```

```

```vbscript
    ' Retrieve the analysis model from the list of models
```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
    Set oAnalysisModel = oAnalysisManager.Item(1)
```
```

```

```vbscript
```vbscript
```vbscript
    ' Retrieve mesh manager and mesh part
```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    ' Retrieve publications from product and retrieve the published face.
```
```vbscript
    Set publications1 = product.Publications
    Set pubEdge = publications1.Item("Edge")
    Set pubPartBody = publications1.Item("PartBody")
```
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro reference is created from published body and published edge.
#### Creating Mesh Part and Assigning Values to its Attributes

    ...

```vbscript
    ' Add the new Octree tetrahedron mesh part to the list of mesh parts
```

```vbscript
```vbscript
    Set octreePart = meshParts.Add ("MSHPartOctree3D")
```vbscript
```
    ' Add reference previously created
```

    octreePart.AddSupportFromPublication product, pubPartBody

```

```vbscript
```vbscript
' Add reference previously created
```

octreePart.AddSupportFromPublication product, pubPartBody
    octreePart.SetGlobalSpecification "SizeValue", "10.0 mm"
    octreePart.SetGlobalSpecification "AbsoluteSagValue", "3.0 mm"
    octreePart.SetGlobalSpecification "ElementOrder", "Parabolic"
    octreePart.SetGlobalSpecification "MaxInteriorSize", "1.2 mm"
    octreePart.SetGlobalSpecification "MinSizeForSags", "0.5 mm"
    octreePart.SetGlobalSpecification "MinGeometrySize", "0.5 mm"
    octreePart.SetGlobalSpecification "AbsoluteSag", 1
    octreePart.SetGlobalSpecification "MaxWarpAngle", "1.0 rad"
    octreePart.SetGlobalSpecification "Criteria", "Skewness"
    octreePart.SetGlobalSpecification "MeshGeometryViolation", 1
    octreePart.SetGlobalSpecification "InteriorSize", 1
    octreePart.SetGlobalSpecification "MinJacobian", 0.3
    octreePart.SetGlobalSpecification "MaxAttempts", 2
    octreePart.SetGlobalSpecification "MeshViolationValue", "0.5 mm"
    octreePart.SetGlobalSpecification "ProportionalSag", 1
    octreePart.SetGlobalSpecification "ProportionalSagValue", "0.5 mm"
```vbscript
    ' Add the Mesh local size as local specifications and assign it attributes
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

    spec1.SetAttribute "MSHMeshSizeMag", "1.5 mm"
    spec1.AddSupportFromPublication "ConnectorList", product, pubedge
```vbscript
    'Update the mesh part
```

    octreePart.Update

```

    ...

---
#### Epilog

    ...

```vbscript
```vbscript
End Sub

```
```

    ...

---

To run the macro interactively CATDocView environment variable must be defined. After running the macro the mesh may not be immediately visible, the user has to go to the Afvanced meshing tools workbench to see the mesh.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create octree tetrahedron mesh parts and how to assign its local and global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
