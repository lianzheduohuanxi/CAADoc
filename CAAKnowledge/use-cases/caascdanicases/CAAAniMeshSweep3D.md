---
```vbscript
title: "Creating Sweep 3D Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSweep3D", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSweep3D.htmmd"
converted: "2026-05-11T17:31:51.713621"
```

---
## Analysis Modeler

|
## Creating Sweep 3D Mesh Parts

* * *

  This use case shows you how to create sweep 3D mesh parts.  The macro opens an Analysis document and creates Sweep 3D mesh. A surface mesh must exist and it may or may not be associated with geometry. If the surface mesh is associated with geometry, this geometry can be face or a set of connected faces. The sweep 3D mesh generates hexahedron elements and wedge elements from the surface mesh. In this macro the mesh is created on a surface mesh part. Values are assigned to the global specifications associated with this mesh part. This scenario requires "FEM Solid (FMD) product". ![](images/Sweep3D.gif)
---|---
This use case shows you how to create sweep 3D mesh parts.  The macro opens an Analysis document and creates Sweep 3D mesh. A surface mesh must exist and it may or may not be associated with geometry. If the surface mesh is associated with geometry, this geometry can be face or a set of connected faces. The sweep 3D mesh generates hexahedron elements and wedge elements from the surface mesh. In this macro the mesh is created on a surface mesh part. Values are assigned to the global specifications associated with this mesh part. This scenario requires "FEM Solid (FMD) product". ![](images/Sweep3D.gif)
  CAAAniMeshSweep3D is launched in CATIA [1]. No open document is needed. [CAAAniMeshSweep3D.catvbs](CAAAniMeshSweep3DSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshSweep3D.catvbs) (Windows only).
  CAAAniMeshSweep3D includes the following steps:

  1. Prolog
  2. Extracting from the Part Document the Reference Object for Meshing
  3. Creating Mesh Part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

|

    ...

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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

    ...

---

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### **Extracting the Reference Object from the Part Document for   Meshing**

    ...

```vbscript
    ' Retrieve the analysis Manager
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
    ' Retrieve the part document and product
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
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**.

The extraction of pre-defined geometrical arena is done by using the Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive applications.
#### Creating Mesh Part and Assigning Values to its Attributes

    ...

```vbscript
    'Add Sweep 3D mesh part to the list of mesh parts
```

```vbscript
```vbscript
    Set sweep3D = oAnalysisMeshParts.Add ("MSHPartSweep3D")
```vbscript
```
    'Add support from the published body
```

    sweep3D.AddSupportFromPublication product, pubBody

```

    sweep3D.SetSpecificationFromPublication "Top", product, pubTopFace, 0
    sweep3D.SetSpecificationFromPublication "Bottom", product, pubBotFace, 0
```vbscript
```vbscript
    'Set the global specification
```
```

    sweep3D.SetGlobalSpecification "ElementOrder", "Linear"
    sweep3D.SetGlobalSpecification "GuideAngle", "60 deg"
    sweep3D.SetGlobalSpecification "NbElements", 10
    sweep3D.SetGlobalSpecification "DistributionType", "Arithmetic"
    sweep3D.SetGlobalSpecification "Ratio", 5.0
    sweep3D.SetGlobalSpecification "CaptureTol", 1.0

    sweep3D.Update

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

To run the macro interactively CATDocView environment variable must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create mesh parts and how to assign other mesh parts as supports.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
