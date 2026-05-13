---
title: "Creating 1D Mesh"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAScdAniUseCases", "CAAAniMesh1D"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMesh1D.htm"
converted: "2026-05-11T17:31:51.602053"
---
## Analysis Modeler

|
## Creating 1D Mesh

* * *

  This use case shows how to create 1D mesh parts in an existing analysis document. This scenario requires "FEM Surface (FMS)" product. This macro opens an Analysis document. It creates 1D (or beam) mesh part and and sets global specifications associated with this mesh part.  ![](images/BeamMesh.gif)
---|---
This use case shows how to create 1D mesh parts in an existing analysis document. This scenario requires "FEM Surface (FMS)" product. This macro opens an Analysis document. It creates 1D (or beam) mesh part and and sets global specifications associated with this mesh part.  ![](images/BeamMesh.gif)
  CAAAniMesh1D is launched in CATIA [1]. No open document is needed. [CAAAniMesh1D.catvbs](CAAAniMesh1DSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMesh1D.catvbs) (Windows only).
  CAAAniMesh1D includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

|

    ...

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    '-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed
```cpp
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
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Beam.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
```cpp
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```
```

```

    ...

---

Open the Analysis document. The Analysis document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved: the Analysis document and the Part document.
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
    'Retrieve publications from product and retrieve the published face.
```

```

```vbscript
```vbscript
    Set publications = product.Publications
```vbscript
```
```vbscript
```vbscript
    Set pubLine = publications.Item("Line.3")

```
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive applications. In this macro the reference is created from the published face.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive applications. In this macro the reference is created from the published face.
```vbscript
```vbscript
    'Add the new beam mesh part to the list of mesh parts

```

```

```vbscript
```vbscript
```vbscript
    Set beamPart = oAnalysisMeshParts.Add("MSHPart1D")

```
```

```

```vbscript
```vbscript
Set beamPart = oAnalysisMeshParts.Add("MSHPart1D")
    beamPart.AddSupportFromPublication product, pubLine
```
    beamPart.SetGlobalSpecification "SizeValue", "10.0 mm"
    beamPart.SetGlobalSpecification "AbsoluteSag", 1
    beamPart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
    beamPart.SetGlobalSpecification "MinimumSizeValue", "1.1 mm"
    beamPart.SetGlobalSpecification "ElementOrder", "Parabolic"
    beamPart.SetGlobalSpecification "MeshCapture", 1
    beamPart.SetGlobalSpecification "MeshCaptureTol", "1.1 mm"
    beamPart.SetGlobalSpecification "CurveAngle", "40 deg"
```vbscript
    'Update the mesh part
```

    beamPart.Update

```

    ...

---

Calling update on the mesh part computes the mesh.
#### Epilog

    ...
```vbscript
     End Sub
```
    ...

---

To run the macro interactively CATDocView environment variables must be defined. After running the macro the mesh may not be immediately visible, the user has to go to the Advanced Meshing Tools workbench to see the mesh.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a 1D mesh part and how to assign values to its global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
