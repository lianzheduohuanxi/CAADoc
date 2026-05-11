---
title: "Creating Preprocessing Data"
category: "general"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPrepro", "CAAScdAniUseCases"]
source_file: "Doc\online\CAAScdAniUseCases\CAAAniPrepro.htm"
converted: "2026-05-11T17:31:51.774983"
---

## Analysis Modeler

| 

## Creating Preprocessing Data  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This macro shows you how to create preprocessing commands on an existing Analysis document linked to a Part document and how to launch the computation. This scenario is related to the Generative Analysis products. It opens an Analysis document, and generates preprocessing data applied to the part attached to the Analysis document. This scenario retrieves the Restraint set to define a clamp on one face, retrieves the Load set in order to define a momentum on another face and compute the case. This last task launches the meshes, generates the finite element model for preprocessing and launches the solver in order to generate the finite element results. ![](images/MacroPrepro.jpg)    
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAAniPrepro is launched in CATIA [1]. No open document is needed. [CAAAniPrepro.CATScript](CAAAniPreproSource.htm) is located in the CAAScdAniUseCases module. [ Execute macro](macros/CAAAniPrepro.CATScript) (Windows only).    
![](../CAAScrBase/images/ascenari.gif) |  CAAAniPrepro includes the following steps:

  1. Prolog
  2. Extracting from the Part Document the Reference Object for Preprocessing
  3. Navigating into the Analysis Document in Order to Retrieve the Preprocessing Sets
  4. Defining the Boundaries
  5. Defining the Load
  6. Computing the Case
  7. Epilog



#### Prolog

| 
    
    
      ...
    
    
     ' ----------------------------------------------------------- 
        ' Optional: allows to find the sample wherever it's installed
        dim sDocPath As String 
        sDocPath=CATIA.SystemService.Environ("CATDocView")
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
          Err.Raise 9999,,"No Doc Path Defined"
        End If
        ' ----------------------------------------------------------- 
        ' Open the Analysis document 
        Dim oAnalysisDocument As Document
        Set oAnalysisDocument = CATIA.Documents.Open
            (sDocPath & "\CAAScdAniUseCases\samples\AnalysisCrank.CATAnalysis")
       ...  
  
---  
  
Open the Analysis document. The Analysis document is fetched in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved: the Analysis document and the Part document.

#### Extracting from the Part Document the Reference Object for Preprocessing
    
    
    ...
    ' Retrieve the Part document in order to compute the references for preprocessing
    Dim PartDocument As PartDocument
    Set PartDocument = documents1.Item(3)
    
    ' Retreive the Part from this document
    Dim part1 As Part
    Set part1 = PartDocument.Part
    
    ' Retrieve the References
    Dim referenceBound As Reference
    Set referenceBound = part1.CreateReferenceFromName("Selection_RSur:(Face:(Brp:(GSRotate.2...));None:());...)")
    
    Dim referenceLoad As Reference
    Set referenceLoad = part1.CreateReferenceFromName("Selection_RSur:(Face:(Brp:(GSMRotate.2...));None:());...)")
    
    ' Extract the product as input of preprocessing feature.
    Dim product1 As Product
    Set product1 = PartDocument.Product
    ...  
  
---  
  
The extraction of pre-defined geometrical arena is done by using the Reference interface. This is equivalent as the selection of a B-Rep element inside the interactive applications.

#### Navigating Inside the Analysis Document in Order to Retrieve the Preprocessing Sets
    
    
    ...
        'Start to scan the existing structure of the analysis document: Retrieve the Analysis Manager 
        
        Dim AnaManager As AnalysisManager
        Set AnaManager = oAnalysisDocument.Analysis
    
        ' Retrieve the AnalysisModels
        Dim AnaModels As AnalysisModels
        Set AnaModels = AnaManager.AnalysisModels
    
        ' To work with the first AnalysisModel of the collection
        Dim AnaModel As AnalysisModel
        >Set AnaModel = AnaModels.Item(1)
        
        ' Retrieve the AnalysisCases
        Dim Cases As AnalysisCases
         Set Cases=AnaModel.AnalysisCases
        
        ' To work with the first AnalysisCase of the collection
         Dim MyCase  As AnalysisCase
         Set MyCase=Cases.Item(1)
      ...  
  
---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **document** , we find the **Analysis manager Object** , the **Analysis models** and the **Analysis cases Objects**. From both last object (Analysis Model and Analysis case), you can get access to **Analysis Sets** and **Analysis entities** that defines the preprocessing actions.

#### Defining the Boundaries
    
    
      ...
        ' To work with the AnalysisSet of the collection that is typed for Boundary condition
        Dim MySet As AnalysisSet
        Set MySet= ListSets.ItemByType("RestraintSet")
    
        ' Retrieve the AnalysisEntities collection defined on the set.
        Dim anEntities As AnalysisEntities
        Set anEntities = MySet.AnalysisEntities
    
        ' Define an Analysis Entity on the set in order to Fix the referencebound of the part.
        Dim analysisEntity As AnalysisEntity
        Set analysisEntity = anEntities.Add("SAMClamp")
        analysisEntity.AddSupportFromProduct product1, referenceBound
      ...  
  
---  
  
From the collection of analysis sets defined on the analysis case, we retrieve the preprocessing set that allows you to define boundary conditions. This set is made of analysis entities. We add to this collection a fix (clamp) boundary condition and apply it on the reference extracted from the Part document.

#### Defining the Loads
    
    
      ...
        ' To work with the AnalysisSet of the collection that is typed for Loading condition
        Set MySet= ListSets.ItemByType("LoadSet")
    
        ' Retrieve the AnalysisEntities collection defined on the set.
       Set anEntities = MySet.AnalysisEntities
    
        ' Define an Analysis Entity on the set in order to load the referenceLoad of the part.
       Set analysisEntity = anEntities.Add("SAMMoment")
       
       analysisEntity.SetValue "SAMMomentVector","", 1, 1, 1, 100000.
       analysisEntity.SetValue "SAMMomentVector","", 2, 1, 1, 0.
       analysisEntity.SetValue "SAMMomentVector","", 3, 1, 1, 0.
       
        analysisEntity.AddSupportFromProduct product1, referenceLoad
      ...  
  
---  
  
From the collection of analysis sets defined on the analysis case, we retrieve the preprocessing set that allows you to define loading conditions. This set is made of analysis entities. We add to this collection a momentum, valuate the vector that defines this loading condition, and apply it on the reference extracted from the part document.

For more information about the physical types included inside analysis entities and the way to valuate them, refer to the reference [2]

#### Computing the Case
    
    
      ...
        ' Launch the computation of the Case 
        MyCase.Compute
      ...  
  
---  
  
This method will launch the mesher, generate the finite element model for preprocessing and launch the solver to generate the finite element results.

#### Epilog
    
    
    ...

End Sub 
    
    
    ...  
  
---  
  
   
  
![](../CAAScrBase/images/aendtask.gif)

[Top]

* * *

#### In Short

This use case has shown how to create preprocessing entities and launch a computation inside an Analysis document.

[Top]

* * *

#### References

[1] | [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[2] |  [ The Physical Types for Structural Analysis](../CAAScdAniTechArticles/CAAAniPreprocessingFeatures.htm)  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
