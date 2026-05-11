---
title: "Activating - Deactivating Images"
category: "general"
module: "CAAScdAniUseCases"
tags: ["CAAAniPostProAcDesact", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc\online\CAAScdAniUseCases\CAAAniPostProAcDesact.htm"
converted: "2026-05-11T17:31:51.736569"
---

## Analysis Modeler

| 

## Activating - Deactivating Images  
  
---|---  
  
* * *

![](../CAAScrBase/images/atarget.gif) |  This use case shows you how to change activation status of image. The macro opens an Analysis document which already contains a computed Frequency case and image. The activation status of "Translational displacement vector.1" image is changed.   ![](images/ActivateDeactivate.gif)    
---|---  
![](../CAAScrBase/images/ainfo.gif) |  CAAAniPostProAcDesact is launched in CATIA [1]. No open document is needed. [ CAAAniPostProAcDesact.catvbs](CAAAniPostProActDeactSource.htm) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPostProAcDesact.catvbs) (Windows only).    
![](../CAAScrBase/images/ascenari.gif) |  CAAAniPostProAcDesact includes the following steps:

  1. Prolog
  2. Retrieve Analysis Cases and Analysis Sets from the Analysis Document
  3. Changing the Activation Status
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
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
    
    ...  
  
---  
  
Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document.

#### **Retrieve Analysis Cases and Analysis Sets from Analysis Document**
    
    
    ...
    
    
    ' Retrieve the Analysis Manager
    Set oAnalysisManager = oAnalysisDocument.Analysis
    			
    ' Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    
    
    
    ' Retrieve the analysis cases and the first analysis case
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    
    
    ' Retrieve the analysis cases and the Frequency case solution
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    Set analysisImages1 = oAnalysisSet.AnalysisImages
    
    
    
    ...  
  
---  
  
According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.htm) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Model**. 

The Analysis case is retrieved from list of cases by its index. The model contains only one analysis case hence we pass 1 to the method _Item._ Otherwise we pass the appropriate index of the desired analysis case if there are more Analysis cases. The analysis case is retrieved from the list of image by its name. The name is same as that appears in the tree, in the interactive environment.

#### Changing the Activation Status
    
    
    ...  
    
    
    'activation of an  image
    '==============
    'we search image Disp_Symbol
    Set oAnalysisImage = analysisImages1.Item("Disp_Symbol")
    
    'we Activate the image
    oAnalysisImage.SetActivationStatus true
    
    'we update the  image
    oAnalysisImage.Update
    
    'deactivation of an  image
    '===============
    'we deactivate the image
    oAnalysisImage.SetActivationStatus false
    
    'we update the  image
    oAnalysisImage.Update
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

This use case has shown how to change the activation status of an image.

[Top]

* * *

#### References

[1]| [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.htm)  
---|---  
[Top]  
  
* * *

_Copyright 2001, Dassault Systmes. All rights reserved._

 

 

 

 
