---
title: "Creating Advanced Surface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniMeshAdvSurf", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshAdvSurf.htm"
converted: "2026-05-11T17:31:51.608533"
---
## Analysis Modeler

|
## Creating Advanced Surface Mesh Parts

* * *

  This use case shows you how to create Advanced surface mesh part on an existing analysis document. This scenario requires "FEM Surface (FMS)" product. This macro opens an existing Analysis document. Advanced surface mesh part is created and global specifications associated with this mesh part are set. The local specification: _MSHDistributionElement_ is created around the edge of the hole. The mesh part is updated to generate mesh.   ![](images/SurfaceMesh.gif)
---|---
This use case shows you how to create Advanced surface mesh part on an existing analysis document. This scenario requires "FEM Surface (FMS)" product. This macro opens an existing Analysis document. Advanced surface mesh part is created and global specifications associated with this mesh part are set. The local specification: _MSHDistributionElement_ is created around the edge of the hole. The mesh part is updated to generate mesh.   ![](images/SurfaceMesh.gif)
  CAAAniMeshAdvSurf is launched in CATIA [1]. No open document is needed. [CAAAniMeshAdvSurf.catvbs](CAAAniMeshAdvSurfSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshAdvSurf.catvbs) (Windows only).
  CAAAniMeshAdvSurf includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```cpp
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```
```

```

```

```vbscript
```cpp
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
    'Open the Analysis document
```cpp
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
    'Retrieve the Analysis Manager and Analysis Model
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
    'Retreive the part document from Analysis manager
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
Set product = partDocument.Product
```vbscript
```
    'Retrieve the analysis model from the list of models
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
    'Retrieve mesh manager and mesh part
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
    'Retrieve publications from product and retrieve the published surface and edge
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

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive application. Here the reference is created from a published face.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive application. Here the reference is created from a published face.
```vbscript
```vbscript
    'Add the new Advanced surface mesh part to the list of mesh parts

```

```

```vbscript
```vbscript
```vbscript
    Set surfPart = meshParts.Add ("MSHPartSmartSurf")

```
```

```

```vbscript
```vbscript
Set surfPart = meshParts.Add ("MSHPartSmartSurf")
```vbscript
```
    'Add support from the published surface
```

    surfPart.AddSupportFromPublication product, pubSurf
```vbscript
```vbscript
'Set the global Specifications
```
```

```

surfPart.SetGlobalSpecification "GlobalMethod", "Frontal triangle"
surfPart.SetGlobalSpecification "GlobalSize", "20.0 mm"
surfPart.SetGlobalSpecification "MinimumSize", "1.0 mm"
surfPart.SetGlobalSpecification "ElementOrder", "Parabolic"
surfPart.SetGlobalSpecification "FaceAngle", "0.0 deg"
surfPart.SetGlobalSpecification "CurveAngle", "0.0 deg"
surfPart.SetGlobalSpecification "DetailsElimination", 1
surfPart.SetGlobalSpecification "StripOptimization", 1
surfPart.SetGlobalSpecification "CleanSize", "1.0 mm"
surfPart.SetGlobalSpecification "Offset", "0.0 mm"
surfPart.SetGlobalSpecification "OffsetFromThickness", "0.0 mm"
surfPart.SetGlobalSpecification "MinimizeTriangles", 1.
surfPart.SetGlobalSpecification "MinSizeForSag", "1.0 mm"
surfPart.SetGlobalSpecification "CurveCaptureTol", "1.0 mm"
surfPart.SetGlobalSpecification "OptimizeRegularity", 1
surfPart.SetGlobalSpecification "MeshRelSagValue", "1.0 mm"
surfPart.SetGlobalSpecification "MeshRelSag", 1
surfPart.SetGlobalSpecification "ConstraintSagValue", "1.0 mm"
surfPart.SetGlobalSpecification "CurveCapture", 1
surfPart.SetGlobalSpecification "MeshCapture", 1
surfPart.SetGlobalSpecification "MeshCapturTol", "1.0 mm"
surfPart.SetGlobalSpecification "MeshAbsSag", 2
surfPart.SetGlobalSpecification "MeshAbsSagValue", "1.0 mm"

```vbscript
```vbscript
'Add the domain specifications as local specifications and assign values to its attributes

```

```

```vbscript
```vbscript
Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
Set spec = meshSpecs.Add("MSHDistributionElement")
```
```

```

```vbscript
```vbscript
Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
Set spec = meshSpecs.Add("MSHDistributionElement")
```
```

```

spec.SetAttribute "NbElements", 50
spec.SetAttribute "Type", "Isometric"
spec.AddSupportFromPublication "Supports", product, pubEdge
```vbscript
'Update the mesh part
```

surfPart.Update

  ...

---

Here parameters are set with their respective units, this helps in setting up of the parameters independent of the unit settings. Calling update on the mesh part computes the mesh.
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

This use case has shown how to create advanced surface mesh parts and how to assign values to its local and global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
