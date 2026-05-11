---
title: "Creating Nodes to Nodes Connection Mesh Parts"
category: "general"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniMeshNodesToNodesConnection", "CAAScdAniUseCases"]
source_file: "Doc\online\CAAScdAniUseCases\CAAAniMeshNodesToNodesConnection.htm"
converted: "2026-05-11T17:31:51.666256"
---

## Analysis Modeler

| 

## Creating Nodes to Nodes Connection Mesh Parts  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This use case shows how to create nodes to nodes connection mesh parts. This scenario requires "FEM Surface (FMS)" product. This macro opens an Analysis document and creates a nodes to nodes connection mesh part is created. This mesh part requires a point to point analysis connection as support. This connection can be created only if Generative Structural Analysis Product (GSA) is installed. The support already exist in the document and is assigned to the mesh part. Update is called on the mesh part to generate mesh.   ![](images/NodesToNodesMesh.gif)    
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAAniMeshNodesToNodesConnection is launched in CATIA [1]. No open document is needed. [ CAAAniMeshNodesToNodesConnection.catvbs](CAAAniMeshNodesToNodesConnectionSource.htm) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniMeshNodesToNodesConnection.catvbs) (Windows only).    
![](../CAAScrBase/images/ascenari.gif) |  CAAAniMeshNodesToNodesConnection includes the following steps:

  1. Prolog
  2. Extracting the List of Mesh Parts and Publications
  3. Creating Mesh part and Assigning Values to its Attributes
  4. Epilog



#### Prolog

| 
    
    
    ...
    
    
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    ' ----------------------------------------------------------- 
    ' Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\WeldConnections.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    ...  
  
---  
  
Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. 

#### Extracting the List of Mesh Parts and Publications
    
    
    ...
    
    
    ' Retrieve the analysis Manager 
    Set oAnalysisManagar = oAnalysisDocument.Analysis
    Set oAnalysisSet = oAnalysisManagar.AnalysisSets
    
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
    
    
    'Retrieve the connection design manager and connection
    Set connection = oAnalysisSet.ItemByType("ConnectionDesignManager")
    Set connSet = connection.AnalysisSets
    Set conn = connSet.ItemByType("ConnectionDesignSet")
    Set entity = conn.AnalysisEntities
    Set surfConn  = entity.Item(1)
    
    'Create reference from the surface analysis connection
    Set reference1 = oAnalysisManagar.CreateReferenceFromObject(surfConn)
    
    
    ...  
  
---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models** and the **Mesh Manager Objects**. The extraction of pre-defined geometric elements is done with the help of the Reference interface. This is equivalent to the selection of a B-Rep elements inside the interactive application.

#### Creating the Mesh Part and Assigning Values to its Attributes.
    
    
    ...
    
    'Add new nodes to nodes connection mesh part to the list of mesh parts
    Set nodeMesh = oAnalysisMeshParts.Add ("MSHPartConnPointPoint") 
    
    'Assign previously created reference as support
    nodeMesh.AddSupportFromReference NOTHING, reference1
    
    'Assign values to its global specifications
    nodeMesh.SetGlobalSpecification "Tolerance", 10.
    nodeMesh.SetGlobalSpecification "StopUpdateOnError", 2
    nodeMesh.SetGlobalSpecification "MiddleCombination", 12
    
    'Update the mesh part
    nodeMesh.Update
    
    ...  
  
---  
  
#### Epilog
    
    
    ...
     End Sub
    ...  
  
---  
  
To run the macro interactively CATDocView environment variable must be defined.  
  
 

![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to create a nodes to nodes connection mesh parts and how to assign values to its global specifications.

 

[Top]

* * *

#### References

[1]| [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
