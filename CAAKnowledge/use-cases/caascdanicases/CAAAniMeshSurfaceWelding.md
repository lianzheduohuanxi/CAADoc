---
title: "Creating Surface Welding Connection Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniMeshSrufaceWelding", "CAAAniMeshSurfaceWelding", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSurfaceWelding.htm"
converted: "2026-05-11T17:31:51.707358"
---
## Analysis Modeler

|
## Creating Surface Welding Connection Mesh Parts

* * *

  This use case shows you how to create surface welding connection mesh parts. This scenario requires "FEM Surface (FMS)". The macro opens an analysis document. Seam welding connection mesh can be created on surface analysis connection and surface analysis connection within one part. In this macro the mesh is created on surface analysis connection which already exists in the document. The connection is assigned as support to the mesh part and it is updated to generate mesh. ![](images/SurfaceWeldMesh.gif)
---|---
This use case shows you how to create surface welding connection mesh parts. This scenario requires "FEM Surface (FMS)". The macro opens an analysis document. Seam welding connection mesh can be created on surface analysis connection and surface analysis connection within one part. In this macro the mesh is created on surface analysis connection which already exists in the document. The connection is assigned as support to the mesh part and it is updated to generate mesh. ![](images/SurfaceWeldMesh.gif)
  CAAAniMeshSrufaceWelding is launched in CATIA [1]. No open document is needed. [CAAAniMeshSurfaceWelding.catvbs](CAAAniMeshSurfaceWeldingSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshSurfaceWelding.catvbs) (Windows only).
  CAAAniMeshSurfaceWelding includes the following steps:

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
    ' Open the Analysis document
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/WeldConnections.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```

```

    **...**

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

```vbscript
    'Retrieve the connection design manager and connection
```

```vbscript
```vbscript
    Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
```vbscript
```
```vbscript
```vbscript
    Set connSet = connection.AnalysisSets
    Set conn = connSet.ItemByType("ConnectionDesignSet")
    Set entity = conn.AnalysisEntities
    Set surfConn  = entity.Item(1)
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)

```
```

```

```

    ...

---

According to the general [ Analysis Document](../use-cases/caascdaniusecases/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**.

The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application.
#### Creating Mesh Part and Assigning Values to its Attributes

    ...

```vbscript
    'Add new surface analysis connection mesh to the list of mesh parts
```

```vbscript
```vbscript
    Set surfWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSurf")
```vbscript
```
    'Assign previously created reference as support
```

    surfWeld.AddSupportFromReference NOTHING, reference1
```vbscript
    'Assign values to its global attributes
```

    surfWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
    surfWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
    surfWeld.SetGlobalSpecification "StopUpdateOnError", 2
    surfWeld.SetGlobalSpecification "MiddleCombination", 10
```vbscript
    'Update the mesh part
```

    surfWeld.Update
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

To run the macro interactively CATDocView and ADL_ODT_SLASH environment variables must be defined.

![image](../../assets/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create Surface Welding Connection mesh part and how to assign values to its global attributes.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)
---|---
[Top]

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
