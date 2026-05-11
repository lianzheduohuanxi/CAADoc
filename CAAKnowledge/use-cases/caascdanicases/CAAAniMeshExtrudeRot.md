---
```vbscript
title: "Creating Extrude with Rotation Mesh Parts"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniMeshExtrudeRot", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniMeshExtrudeRot.htm"
converted: "2026-05-11T17:31:51.633976"
```

---
## Analysis Modeler

| 
## Creating Extrude with Rotation Mesh Parts  

* * *

  This use case shows how to create extrude with rotation mesh part.  This macro opens an Analysis document. Extrude with rotation mesh part can create a 2D mesh from 1D mesh and 3D mesh from 2D mesh. In this macro 3D mesh from 2D mesh is created. Global specifications associated with the mesh part are set.   ![](images/ExtrWithRotMesh.gif)    
---|---  
This use case shows how to create extrude with rotation mesh part.  This macro opens an Analysis document. Extrude with rotation mesh part can create a 2D mesh from 1D mesh and 3D mesh from 2D mesh. In this macro 3D mesh from 2D mesh is created. Global specifications associated with the mesh part are set.   ![](images/ExtrWithRotMesh.gif)
  CAAAniMeshExtrudeRot is launched in CATIA [1]. No open document is needed. [CAAAniMeshExtrudeRot.catvbs](CAAAniMeshExtrudeRotSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshExtrudeRot.catvbs) (Windows only).    
  CAAAniMeshExtrudeRot includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog

#### Prolog

| 

    ...

    '----------------------------------------------------------- 
```vbscript
'-----------------------------------------------------------
    'Optional: allows to find the sample wherever it's installed

      sDocPath=CATIA.SystemService.Environ("CATDocView")
      sSep=CATIA.SystemService.Environ("ADL_ODT_SLASH")

```

```vbscript
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```

```vbscript
    '----------------------------------------------------------- 
    'Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Surface.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    ...  

---  

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. 
#### Extracting the List of Mesh Parts and Publications

    ...

    'Retrieve the analysis Manager 
```vbscript
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
```

```vbscript
    'Retrieve the part document and product
    Set oAnalysisLinkedDocuments = oAnalysisManagar.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
```

    'Retrieve the published line
```vbscript
'Retrieve the published line
    'the mesh will be rotated and extruded along this line
```

```vbscript
    Set publications = product.Publications
    Set pubAxis = publications.Item("Axis")
```

```vbscript
    'Retrieve the analysis model
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

---  

According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of B-Rep elements inside the interactive application. In this macro reference is created from the surface mesh part.
#### Creating the Mesh Part and Assigning Values to its Attributes.

    ...
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of B-Rep elements inside the interactive application. In this macro reference is created from the surface mesh part.
    'Add the extrude with translation mesh part to the list of mesh parts

```vbscript
    Set extrudeMesh = oAnalysisMeshParts.Add("MSHPartExtrRotation")
    'Assign the surface mesh part as support
    extrudeMesh.AddSupportFromReference NOTHING, reference
    'Set the global specifications
    extrudeMesh.SetGlobalSpecification "Condensation", 0
    extrudeMesh.SetGlobalSpecification "Tolerance", "1.0 mm"
    extrudeMesh.SetGlobalSpecification  "Angle", "120 deg"
    extrudeMesh.SetGlobalSpecification  "Angle1", "20 deg"
    'Set the specification; the axis of rotation
    extrudeMesh.SetSpecificationFromPublication "Direction", product, pubAxis, 0
```

```vbscript
    'Get the basic components and sub components
    Set basicComps = extrudeMesh.BasicComponents
    Set subBasicComps = basicComps.Item(1).BasicComponents
    'Retrieve each of the attributes by name and set their values
    Set subBasicComp1 = subBasicComps.Item("Type")
```

```vbscript
Set subBasicComps = basicComps.Item(1).BasicComponents
'Retrieve each of the attributes by name and set their values
Set subBasicComp1 = subBasicComps.Item("Type")
    subBasicComp1.SetValue "", 0, 0, 0, "Arithmetic"

    Set subBasicComp2 = subBasicComps.Item("NbNodes")
    subBasicComp2.SetValue "", 0, 0, 0, 20

    Set subBasicComp3 = subBasicComps.Item("Symmetric")
    subBasicComp3.SetValue "", 0, 0, 0, 2

    Set subBasicComp4 = subBasicComps.Item("Ratio")
    subBasicComp4.SetValue "", 0, 0, 0, 10
    'Update the mesh	
    extrudeMesh.Update

```

    ...  

---  
#### The extruded mesh can be manipulated with the parameters like distribution type ( Uniform, Arithmetic, Geometric) number of layers, symmetry and ratio. To set these parameters we retrieve the list of basic components (BCs) from the mesh. From the first element of the list we retrieve one more list of the BCs. Then we retrieve each of the BCs by its name and set the values.
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

This use case has shown how to create extrude with rotation mesh part and how to assign values to its global specifications.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
