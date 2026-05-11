---
title: "Creating Seam Welding Connection Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshSeamWelding", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshSeamWelding.md"
converted: "2026-05-11T17:31:51.689200"
---
## Analysis Modeler

| 
## Creating Seam Welding Connection Mesh Parts  
  
  
* * *

  This use case shows you how to create seam welding connection mesh part. Seam weld can be defined as wire frame or 1D feature. This scenario requires "FEM Surface (FMS)". The macro opens an analysis document. Seam welding connection mesh can be created on line analysis connection and line analysis connection within one part. In this macro the mesh is created on line Analysis Connection which already exists in the document. The connection is assigned as support to the mesh part and it is updated to generate mesh. ![](images/SeamWeldingMesh.gif)    
---|---  
  CAAAniMeshSeamWelding is launched in CATIA [1]. No open document is needed. [CAAAniMeshSeamWelding.catvbs](CAAAniMeshSeamWeldingSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshSeamWelding.catvbs) (Windows only).    
  CAAAniMeshSeamWelding includes the following steps:

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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    
```

    
```

    **...**  
  
---  
  
Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. 
#### **Extracting the Reference Object from the Part Document for   Meshing**
    
    
    ...
    
    ' Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```vbscript
    ' Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    ' Retrieve the analysis model
    Set oAnalysisModels = oAnalysisManagar.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    'Retrieve the mesh manager and list of mesh parts
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager 
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
```

    
```

    'Retrieve the connection design manager and connection
```vbscript
    Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
    Set connSet = connection.AnalysisSets
    Set conn = connSet.ItemByType("ConnectionDesignSet")
    Set entity = conn.AnalysisEntities
    Set surfConn  = entity.Item(1)
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
    
```

    ...  
  
```

---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. 

The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application.
#### Creating Mesh Part and Assigning Values to its Attributes
    
    
    ...  
    
    'Add new Seam welding connection mesh part to the list of mesh parts
```vbscript
    Set seamWeld = oAnalysisMeshParts.Add ("MSHPartConnWeldSeam") 
    'Add previously created  reference line analysis connection as support
    seamWeld.AddSupportFromReference NOTHING, reference1
    'Assign values to global specifications
    seamWeld.SetGlobalSpecification "MaximalGap", "10.0 mm"
    seamWeld.SetGlobalSpecification "MeshStep", "10.0 mm"
    seamWeld.SetGlobalSpecification "StopUpdateOnError", 1
    seamWeld.SetGlobalSpecification "MiddleCombination", 2
    seamWeld.SetGlobalSpecification "Width", "4.0 mm"
    'Update the mesh
    seamWeld.Update
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
  
To run the macro interactively CATDocView environment variable must be defined.  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create seam welding mesh parts and how to assign values to its global attributes.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._

 

 

 

 
