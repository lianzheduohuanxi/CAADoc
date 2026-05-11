---
```vbscript
title: "Specifying Occurrences for Images"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CATIA", "CAAAniPostProOccurrence", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProOccurrence.htm"
converted: "2026-05-11T17:31:51.760018"
```

---
## Analysis Modeler

| 
## Specifying Occurrences for Images  

* * *

  This use case shows you how to change the occurrence of an image, created under frequency case. The macro opens an Analysis document which already contains a computed frequency case and images. The occurrence of the image is changed and the image is updated.   ![](images/ActivateDeactivate.gif)    
---|---  
This use case shows you how to change the occurrence of an image, created under frequency case. The macro opens an Analysis document which already contains a computed frequency case and images. The occurrence of the image is changed and the image is updated.   ![](images/ActivateDeactivate.gif)
  CAAAniPostProOccurrence is launched in CATIA [1]. No open document is needed. [CAAAniPostProOccurrence.catvbs](CAAAniPostProOccurrenceSource.md) is located in the CAAScdAniUseCases module. [Execute macro](macros/CAAAniPostProOccurrence.catvbs) (Windows only).    
  CAAAniPostProOccurrence includes the following steps:

  1. Prolog
  2. Retrieve Analysis Cases and Analysis Sets from the Analysis Document
  3. Setting the occurrence
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
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
```

```vbscript
    ' ----------------------------------------------------------- 
    ' Open the Analysis document 
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```

    ...  

---  

Open the Analysis document. The Analysis document is retrieved in the documentation installation path, this path has already been stored in the `sDocPath` variable. In the collection of documents, two documents can be retrieved; the Analysis document and the Part document. 
#### **Retrieve Analysis Cases and Analysis Sets from Analysis Document**

    ...

    ' Retrieve the Analysis Manager
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```

```vbscript
    ' Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
```

    ' Retrieve the analysis cases and the first analysis case
```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)

```

```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
    ' Retrieve the analysis cases and the first analysis case
```

```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)

```

```vbscript
Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    ' Get the list of image and retrieve the Von Mises Stress image by its name
```

```vbscript
    Set oAnalysisImages = oAnalysisSet.AnalysisImages
    Set oAnalysisImage = oAnalysisImages.Item("Von Mises Stress (nodal values).1")

```

    ...  

---  

According to the general [ Analysis Document](../CAAScdAniTechArticles/CAAAniTocAnalysisDocument.md) structure, this macro uses some standard procedures to navigate or retrieve the required objects. First, from the **Document** , we find the **Analysis Manager Object** , the **Analysis Models**. 

The Analysis case is retrieved from list of cases by its index. The model contains only one analysis case hence we pass 1 to the method _Item._ Otherwise we pass the appropriate index of the Frequency case if there are more Analysis cases. The analysis image is retrieved from the list of images by its name. The name is same as that appears in the tree, in the interactive environment.
#### Setting the Occurrence

    ...  

```vbscript
    'Modify current occurrence of Image Von Mises Stress (nodal values)
    '==================================================================
    oAnalysisImage.SetCurrentOccurrence 4
    oAnalysisImage.Update
```

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

This use case has shown how to specify occurrences for images.

[Top]

* * *
#### References

[1] |  [Replaying a Macro](../CAAScdInfUseCases/CAAInfLauchMacro.md)  
---|---  
[Top]  

* * *

_Copyright 2001, Dassault Systmes. All rights reserved._
