---
title: "CAAAniPostProAcDesact.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAAniPostProAcDesact", "CATIA", "CAAScdAniUseCases"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProActDeactSource.htm"
converted: "2026-05-11T17:31:51.738069"
---

```vbscript
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      To demonstrate activation and deactivation of image
    '   Assumptions:   displacement symbol image exists in the document
    '   Author:       bmw
    '   Languages:    VBScript
    '   Locales:      English 
    '   CATIA Level:  V5R16
    ' ***********************************************************************
```

    
```vbscript
    Sub CATMain()
```vbscript
    ' ----------------------------------------------------------- 
    ' Optional: allows to find the sample wherever it's installed
      sDocPath=CATIA.SystemService.Environ("CATDocView")
    
        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```

```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
        End If
    ' ----------------------------------------------------------- 
    
```

    ' Open the CATAnalysis Document
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online\CAAScdAniUseCases\samples\Cube_R13_Freq.CATAnalysis")
```vbscript
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
    
```

    ' Retrieve the Analysis Manager
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
    ' Retrieve the analysis model from the list of models
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    ' Retrieve the analysis cases and the first analysis case
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    ' Retrieve the analysis cases and the first analysis case
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    Set analysisImages1 = oAnalysisSet.AnalysisImages
    'activation of an  image
    '==============
    'we search image Disp_Symbol
    Set oAnalysisImage = analysisImages1.Item("Disp_Symbol")
    'we Activate the image
```

    oAnalysisImage.SetActivationStatus true
    'we update the  image
    oAnalysisImage.Update
```vbscript
    'deactivation of an  image
    '===============
    'we deactivate the image
```

    oAnalysisImage.SetActivationStatus false
    'we update the  image
    oAnalysisImage.Update
    
```

```vbscript
    End Sub
    
```

```