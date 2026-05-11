---
title: "Creating 1D Mesh"
category: "general"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAScdAniUseCases", "CAAAniMesh1D"]
source_file: "Doc\online\CAAScdAniUseCases\CAAAniMesh1D.htm"
converted: "2026-05-11T17:31:51.602053"
---

## Analysis Modeler

| 

## Creating 1D Mesh  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This use case shows how to create 1D mesh parts in an existing analysis document. This scenario requires "FEM Surface (FMS)" product. This macro opens an Analysis document. It creates 1D (or beam) mesh part and and sets global specifications associated with this mesh part.  ![](images/BeamMesh.gif)    
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAAniMesh1D is launched in CATIA [1]. No open document is needed. [CAAAniMesh1D.catvbs](CAAAniMesh1DSource.htm) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMesh1D.catvbs) (Windows only).  
![](../CAAScrBase/images/ascenari.gif) |  CAAAniMesh1D includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog



#### Prolog

| 
    
    
    ...
    
    
    Sub CATMain()
    
    '----------------------------------------------------------- 
    'Optional: allows to find the sample wherever it's installed
    sDocPath=CATIA.SystemService.Environ("CATDocView")
    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
    Err.Raise 9999,,"No Doc Path Defined"
    End If
    '----------------------------------------------------------- 
    
    
    'Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Beam.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
    
    ...  
  
---  
  
Open the Analysis document. The Analysis document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved: the Analysis document and the Part document. 

#### Extracting the List of Mesh Parts and Publications
    
    
    ...
    
    
    'Retrieve the Analysis Manager and Analysis Model
    Set oAnalysisManager = oAnalysisDocument.Analysis
    
    
    'Retreive the part document from Analysis manager
    Set oAnalysisLinkedDocument = oAnalysisManager.LinkedDocuments
    Set partDocument = oAnalysisLinkedDocuments.Item(1)
    Set product = partDocument.Product
    			
    
    
    'Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisManager.Item(1)
    
    
    'Retrieve mesh manager and mesh part 
    Set oAnalysisMeshManager = oAnalysisModel.MeshManager
    Set oAnalysisMeshParts = oAnalysisMeshManager.AnalysisMeshParts
    
    
    
    'Retrieve publications from product and retrieve the published face.
    Set publications = product.Publications
    Set pubLine = publications.Item("Line.3")
    
    
    ...  
  
---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of Reference interface. This is equivalent to the selection of a B-Rep element inside the interactive applications. In this macro the reference is created from the published face.

#### Creating the Mesh Part and Assigning Values to its Attributes.
    
    
    ...
    'Add the new beam mesh part to the list of mesh parts
    Set beamPart = oAnalysisMeshParts.Add("MSHPart1D")
    
    beamPart.AddSupportFromPublication product, pubLine
    beamPart.SetGlobalSpecification "SizeValue", "10.0 mm"
    beamPart.SetGlobalSpecification "AbsoluteSag", 1
    beamPart.SetGlobalSpecification "AbsoluteSagValue", "1.1 mm"
    beamPart.SetGlobalSpecification "MinimumSizeValue", "1.1 mm"
    beamPart.SetGlobalSpecification "ElementOrder", "Parabolic"
    beamPart.SetGlobalSpecification "MeshCapture", 1
    beamPart.SetGlobalSpecification "MeshCaptureTol", "1.1 mm"
    beamPart.SetGlobalSpecification "CurveAngle", "40 deg"
    
    'Update the mesh part
    beamPart.Update 
    
    ...  
  

---  
  
Calling update on the mesh part computes the mesh.

#### Epilog
    
    
    ...
     End Sub
    ...  
  
---  
  
To run the macro interactively CATDocView environment variables must be defined. After running the macro the mesh may not be immediately visible, the user has to go to the Advanced Meshing Tools workbench to see the mesh.  
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to create a 1D mesh part and how to assign values to its global specifications.

[Top]

* * *

#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
