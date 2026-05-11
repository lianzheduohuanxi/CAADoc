---
```vbscript
title: "Creating Surface Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshBasicSurf", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshBasicSurf.htm"
converted: "2026-05-11T17:31:51.615517"
```

---
## Analysis Modeler

| 
## Creating Surface Mesh Parts  

* * *

  This use case shows you how to create Octree triangle mesh part on an existing analysis document. This scenario requires "FEM Surface (FMS) product". The macro open an Analysis document. Mesh part surface mesh is created and global specifications associated with this mesh part are set. The local specification: _MSHLocalMeshSize_ is created, specifying the edge of the hole as support. Finally mesh part is updated to generate mesh. ![](images/BasicSurfMesh.gif)    
---|---  
This use case shows you how to create Octree triangle mesh part on an existing analysis document. This scenario requires "FEM Surface (FMS) product". The macro open an Analysis document. Mesh part surface mesh is created and global specifications associated with this mesh part are set. The local specification: _MSHLocalMeshSize_ is created, specifying the edge of the hole as support. Finally mesh part is updated to generate mesh. ![](images/BasicSurfMesh.gif)
  CAAAniMeshBasicSurf is launched in CATIA [1]. No open document is needed. [CAAAniMeshBasicSurf.catvbs](CAAAniMeshBasicSurfSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshBasicSurf.catvbs) (Windows only).  
  CAAAniMeshBasicSurf includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

| 

    ...

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
    '----------------------------------------------------------- 

```

```vbscript
End If
'-----------------------------------------------------------
    'Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
```

```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```

    ...  

---  

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path is already stored in the `sDocPath` variable. If this cariable is not valuated then error is raised. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### Extracting the List of Mesh Parts and Publications

    ...

    'Retrieve the Analysis Manager and Analysis Model
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

```

```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
    'Retreive the part document from Analysis manager
```

```vbscript
    Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product

```

```vbscript
Set product = partDocument.Product
    'Retrieve the analysis model from the list of models
```

```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisManager.Item(1)

```

```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisManager.Item(1)
    'Retrieve mesh manager and mesh part 
```

```vbscript
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts

```

```vbscript
Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    'Retrieve publications from product and retrieve the published surface and edge
```

```vbscript
    Set publications1 = product.Publications
    Set pubEdge = publications1.Item("Edge")
```

    ...  

---  

According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro the reference is created from the published face.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done by using the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro the reference is created from the published face.
    'Add the new basic surface mesh part to the list of mesh parts

```vbscript
    Set  surfPart = meshPart.Add ("MSHPartBasicSurf")

```

```vbscript
Set  surfPart = meshPart.Add ("MSHPartBasicSurf")
    'Add support from the published surface
    surfPart.AddSupportFromPublication product, pubSurf

    'Set the global Specifications
    surfPart.SetGlobalSpecification "GlobalMethod", 1
    surfPart.SetGlobalSpecification "QuadsOnly", 2
    surfPart.SetGlobalSpecification "ElementOrder", "Parabolic"
    surfPart.SetGlobalSpecification "DedicatedMesh", 1
    surfPart.SetGlobalSpecification "GlobalSize", "10.0 mm"
    surfPart.SetGlobalSpecification "Offset", "15.0 mm"
    surfPart.SetGlobalSpecification "TopologySize", "20.0 mm"
    surfPart.SetGlobalSpecification "TopologySag", 2
    surfPart.SetGlobalSpecification "SharpEdges", 1
    surfPart.SetGlobalSpecification "FaceAngle", "0 deg"
    surfPart.SetGlobalSpecification "OffsetFromThickness", 1
    surfPart.SetGlobalSpecification "MeshRelSag", 1
    surfPart.SetGlobalSpecification "MeshRelSagValue", "0.1 mm"
    surfPart.SetGlobalSpecification "CurveCapture", 1
    surfPart.SetGlobalSpecification "CurveCaptureTol", "1.1 mm"
    surfPart.SetGlobalSpecification "MeshCapture", 1
    surfPart.SetGlobalSpecification "MeshCaptureTol", "1.1 mm"
    surfPart.SetGlobalSpecification "MeshAbsSag", 1
    surfPart.SetGlobalSpecification "MeshAbsSaglValue", "1.1 mm"

    'Create local specification
```

```vbscript
    Set meshSpecs = surfPart.AnalysisMeshLocalSpecifications
    Set spec = meshSpecs.Add("MSHTopProjectCurve")
    spec.AddSupportFromPublication "ConnectorList", product1, pubCurve
    spec.SetAttribute "Tolerance", "500 mm"

```

```vbscript
    Set spec = meshSpecs.Add("MSHTopProjectPoint")
    spec.AddSupportFromPublication "ConnectorList", product1, pubPoint
    spec.SetAttribute "Tolerance", "500 mm"

```

spec.AddSupportFromPublication "ConnectorList", product1, pubPoint
spec.SetAttribute "Tolerance", "500 mm"
    'Update the mesh part

surfPart.Update

    ...  

---  
#### Here parameters are set with their respective units, this helps in setting up of the parameters independent of the unit settings. Calling update on the mesh part computes the mesh.
#### Epilog

    ...
     End Sub
    ...  

---  

To run the macro interactively CATDocView environment variables must be defined.  

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create basic surface mesh parts and how to assign values to its global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
