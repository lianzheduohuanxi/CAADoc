---
```vbscript
title: "Creating 1D Coating Mesh Part"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshCoating1D", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshCoating1D.htmmd"
converted: "2026-05-11T17:31:51.621507"
```

---
## Analysis Modeler

|
## Creating 1D Coating Mesh Part

* * *

  This use case shows you how to create coating 1D mesh part by extracting edge elements of an existing 2D mesh part. A coating mesh can be extracted from a surface mesh part, advanced surface mesh Part, octree triangle mesh part, coating 2D mesh part or any 2D transformed mesh part. This functionality is available in FEM Surface (FMS) product. The macro opens an Analysis document which already contains a surface mesh part. The coating mesh is created over this mesh part. At the end the mesh part is updated to generate mesh. ![](images/Coating1DMesh.gif)
---|---
This use case shows you how to create coating 1D mesh part by extracting edge elements of an existing 2D mesh part. A coating mesh can be extracted from a surface mesh part, advanced surface mesh Part, octree triangle mesh part, coating 2D mesh part or any 2D transformed mesh part. This functionality is available in FEM Surface (FMS) product. The macro opens an Analysis document which already contains a surface mesh part. The coating mesh is created over this mesh part. At the end the mesh part is updated to generate mesh. ![](images/Coating1DMesh.gif)
  CAAAniMeshCoating1D is launched in CATIA [1]. No open document is needed. [CAAAniMeshCoating1D.catvbs](CAAAniMeshCoating1DSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshCoating1D.catvbs) (Windows only).
  CAAAniMeshCoating1D includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

|

    ...

```vbscript
```vbscript
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed
```vbscript
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

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
    '-----------------------------------------------------------
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

Open the Analysis document. The Analysis document is fetched in the documentation installation path, this path is already stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved: the Analysis document and the Part document.
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
    Set pubEdge = publications1.Item("Edge")
```
```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometrical elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro the reference is created from the surface mesh part.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometrical elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro the reference is created from the surface mesh part.
```vbscript
```vbscript
    'Add the new Coating mesh part to the list of mesh parts

```

```

```vbscript
```vbscript
    Set coat1D = oAnalysisMeshPart.Add ("MSHPart1DCoating")
```vbscript
```
```vbscript
    'Set the reference to the surface mesh part
```
```

    coat1D.AddSupportFromReference product, reference1
```vbscript
    'Assign value to the global specification
```

    coat1D.SetGlobalSpecification "ExtractionType", 1

```

```vbscript
```vbscript
'Assign value to the global specification
```

coat1D.SetGlobalSpecification "ExtractionType", 1
```vbscript
    'Create the local specification
```

```

```vbscript
```vbscript
    Set meshSpecs = coat2D.AnalysisMeshLocalSpecifications
```vbscript
```
```vbscript
    Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
```
```

    spec.SetAttribute "LocalExtractionType", 2

```

```vbscript
```vbscript
Set spec = meshSpecs.Add("MSHCoatingLocalSpecification")
```
```

spec.SetAttribute "LocalExtractionType", 2
    spec.AddSupportFromPublication "ConnectorList", product, pubFace
```vbscript
    'Update the mesh part
```

    coat1D.Update

     ...

---
#### The local specification specifies the edges which are to be included or excluded while computing the coating mesh. You can specify multiple edges to one local specification. If you want to include some edges, and exclude some other then you need to create at least two local specifications. All the edges which are to be included, can be added as support to one local specification with the attribute "LocalExtractionType" valuated to 1. Similarly edges which are to be exclude can be added as support to other local specification with the attribute "LocalExtractionType" valuated to 2.
#### Epilog

    ...
```vbscript
     End Sub
```
    ...

---

To run the macro interactively CATDocView environment variables must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create 1D coating mesh parts and how to assign values to its global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
