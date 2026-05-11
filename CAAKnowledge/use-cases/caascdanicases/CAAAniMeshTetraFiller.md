---
title: "Creating Tetrahedron Filler Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMeshTetraFiller"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshTetraFiller.htm"
converted: "2026-05-11T17:31:51.724099"
---
## Analysis Modeler

| 
## Creating Tetrahedron Filler Mesh Parts  
  
  
* * *

  This use case shows you how to create tetrahedron filler mesh part in an existing Analysis document linked to a Part document. A surface mesh part must exist to create a Tetrahedron Filler mesh part. The surface mesh may not be associated with geometry. If it is associated with geometry, this geometry can be either a solid or a set of connected faces. This scenario requires "FEM Solid (FMD) product". The macro opens an Analysis document which already contains a surface mesh part. This surface mesh part "Surface Mesh.1" is used to create tetrahedron filler mesh. Global specifications are assigned to this mesh part. Finally the mesh part is updated to generate mesh. ![](images/TetrahedronFiller.jpg)    
---|---  
  CAAAniMeshTetraFiller is launched in CATIA [1]. No open document is needed. [CAAAniMeshTetraFiller.catvbs](CAAAniMeshTetraFillerSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshTetraFiller.catvbs) (Windows only).    
  CAAAniMeshTetraFiller includes the following steps:

  1. Prolog
  2. Extracting from the Part Document the Reference Object for Meshing
  3. Creating Mesh Part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

| 
    
    
    ...
    
```vbscript
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
```

    
```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```vbscript
    ' ----------------------------------------------------------- 
    ' Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    
```

    ...  
  
```

---  
  
Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.
#### **Extracting the Reference Object from the Part Document for   Meshing**
    
    
    ...
    
    ' Retrieve the Analysis Manager
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
    ' Retrieve the part document and product
    Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
    Set PartDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    ' Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    ' Retrieve mesh manager and mesh part from the list of mesh parts specifying its name
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    Set oAnalysisMeshPart = oAnalysisMeshParts.Item("Surface Mesh.1")
    ' Create Reference from the mesh part.
    Set reference1 = oAnalysisManager.CreateReferenceFromObject(oAnalysisMeshPart)
```

    ...  
  
```

```

---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. 

The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive applications.
#### Creating Mesh Part and Assigning Values to its Attributes
    
    
    ...  
    
    ' Add the new Tetrahedron Filler mesh part to the list of mesh parts
```vbscript
    Set tetraFiller = oAnalysisMeshParts.Add("MHSPartGHS3D")
    ' Add reference previously created
    tetraFiller.AddSupportFromReference NOTHING, reference1
    ' Set the global Specifications
    tetraFiller.SetGlobalSpecification "Propagation", 1.5
    tetraFiller.SetGlobalSpecification "ElementOrder", "Parabolic"
    'Update the mesh part
    tetraFiller.Update
    ...  
  
```

```

---  
#### Epilog
    
    
    ...

```vbscript
End Sub 
    
```

    
    ...  
  
---  
  
To run the macro interactively CATDocView  environment variable must be defined. After running the macro the mesh may not be immediately visible, the user has to go to the Advanced Meshing Tools workbench to see the mesh.  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a mesh part and how to assign other mesh parts as supports.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._

 

 

 

 
