---
title: "Creating Translation Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshTranslation", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshTranslation.htm"
converted: "2026-05-11T17:31:51.730103"
---
## Analysis Modeler

| 
## Creating Translation Mesh Parts  
  
  
* * *

  This use case shows how to create a translation mesh part. A translation mesh can be created on 1D, 2D or 3D mesh part. This scenario requires "FEM Surface (FMS)" product to create 1D or 2D transformed mesh part and FEM Solid (FMD) product to create 3D transformed mesh part. This macro opens an Analysis document. A translation mesh part is created on a surface mesh part. The surface mesh part already exist in the document.   ![](images/TranslationMesh.gif)    
---|---  
  CAAAniMeshTranslation is launched in CATIA [1]. No open document is needed. [CAAAniMeshTranslation.catvbs](CAAAniMeshTranslationSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshTranslation.catvbs) (Windows only).    
  CAAAniMeshTranslation includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    
```

    
    ...  
  
```

---  
  
Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. 
#### Extracting the List of Mesh Parts and Publications
    
    
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
    Set surfMesh = oAnalysisMeshParts.Item("Surface Mesh.1")
    'Create the reference of the surface mesh
    Set reference = oAnalysisManagar.CreateReferenceFromObject(surfMesh)
```

    ...  
  
```

```

---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application. In this macro reference is created from surface mesh part.
#### Creating the Mesh Part and Assigning Values to its Attributes.
    
    
    ...
    'Add the mesh part to list of mesh parts
```vbscript
    Set meshTrans = oAnalysisMeshParts.Add("MSHPartTranslation")
    'Assign the reference to the mesh part
    meshTrans.AddSupportFromReference NOTHING, reference
    
```

    meshTrans.SetGlobalSpecification "TranslationValue", "-100.0 mm"
    meshTrans.SetGlobalSpecification "Condensation", 0
    meshTrans.SetGlobalSpecification "Tolerance", "1.0 mm"
    meshTrans.SetGlobalSpecification "NbCopies", 3
    'Set the specification; the the direction of translation
    meshTrans.SetSpecificationFromPublication "Direction", product, pubDirection, 0
    'Update the mesh
    meshTrans.Update
    ...  
  

```

---  
#### Epilog
    
    
    ...
    End Sub
    ...  
  
```

---  
  
To run the macro interactively CATDocView environment variable must be defined.  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *
#### In Short

This use case has shown how to create a translation mesh part and how to assign values to its global specifications.

 

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
