---
title: "CAAAniPostProAcDesact.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CAAAniPostProAcDesact", "CATIA", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProActDeactSource.htm"
converted: "2026-05-11T17:31:51.738069"
---
```vbscript
```vbscript
```cpp
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

```

```

```vbscript
```cpp
    Sub CATMain(#)

```

```

```vbscript
```vbscript
```vbscript
    ' -----------------------------------------------------------
    ' Optional: allows to find the sample wherever it's installed
```cpp
      sDocPath=CATIA.SystemService.Environ("CATDocView")

        If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
```
```

```

```

```vbscript
```vbscript
          Err.Raise 9999,,"No Doc Path Defined"
```vbscript
```
```vbscript
        End If
    ' -----------------------------------------------------------

```

```

```

```vbscript
End If
```vbscript
```cpp
' -----------------------------------------------------------
    ' Open the CATAnalysis Document
```cpp
    sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
```
```

```

```

```vbscript
```vbscript
```cpp
    Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

```
```

```

```vbscript
```cpp
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```vbscript
```
    ' Retrieve the Analysis Manager
```

```

```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
```vbscript
```vbscript
    ' Retrieve the analysis model from the list of models
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
    Set oAnalysisModel = oAnalysisModels.Item(1)
    ' Retrieve the analysis cases and the first analysis case
```
```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
    Set oAnalysisCase = oAnalysisCases.Item(1)
    ' Retrieve the analysis cases and the first analysis case
```
```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)
    Set analysisImages1 = oAnalysisSet.AnalysisImages
    'activation of an  image
```
    '==============
    'we search image Disp_Symbol
```vbscript
    Set oAnalysisImage = analysisImages1.Item("Disp_Symbol")
    'we Activate the image
```
```

```

```

```vbscript
```vbscript
```vbscript
'we search image Disp_Symbol
```vbscript
Set oAnalysisImage = analysisImages1.Item("Disp_Symbol")
'we Activate the image
```
```

```

    oAnalysisImage.SetActivationStatus true
```vbscript
    'we update the  image
```

    oAnalysisImage.Update
```

```vbscript
```vbscript
```vbscript
    'deactivation of an  image
    '===============
    'we deactivate the image
```

```

```

```vbscript
```vbscript
```vbscript
'deactivation of an  image
'===============
'we deactivate the image
```

```

    oAnalysisImage.SetActivationStatus false
```vbscript
    'we update the  image
```

    oAnalysisImage.Update

```

```vbscript
```vbscript
    End Sub

```
```
