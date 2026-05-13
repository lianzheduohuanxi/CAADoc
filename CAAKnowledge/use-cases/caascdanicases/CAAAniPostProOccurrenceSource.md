---
title: "CAAAniPostProOccurrence.catvbs"
category: "use-case"
module: "CAAScdAniUseCases"
tags: "["CATIA", "CAAAniPostProOccurrence", "CAAScdAniUseCases"]"
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProOccurrenceSource.htm"
converted: "2026-05-11T17:31:51.761551"
---
```vbscript
```vbscript
```cpp
    ' COPYRIGHT DASSAULT SYSTEMES 2000
    ' ***********************************************************************
    '   Purpose:      To Change the occurrence of an image
    '   Assumptions:   Frequency case is computed with at least 4 occurrences
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
    ' Retrieve the Analysis Manager
```

```vbscript
```vbscript
```vbscript
    Set oAnalysisManager = oAnalysisDocument.Analysis

```
```

```

```vbscript
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```vbscript
```
    ' Retrieve the analysis model from the list of models
```

```

```vbscript
```vbscript
    Set oAnalysisModels = oAnalysisManager.AnalysisModels
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisModel = oAnalysisModels.Item(1)

```
```

```

```

```vbscript
```vbscript
Set oAnalysisModel = oAnalysisModels.Item(1)
```vbscript
```
    ' Retrieve the analysis cases and the first analysis case
```

```

```vbscript
```vbscript
    Set oAnalysisCases = oAnalysisModel.AnalysisCases
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisCase = oAnalysisCases.Item(1)

```
```

```

```

```vbscript
```vbscript
Set oAnalysisCase = oAnalysisCases.Item(1)
```vbscript
```
    ' Retrieve the analysis cases and the first analysis case
```

```

```vbscript
```vbscript
    Set oAnalysisSets = oAnalysisCase.AnalysisSets
```vbscript
```
```vbscript
```vbscript
    Set oAnalysisSet = oAnalysisSets.Item("Frequency Case Solution.1", catAnalysisSetSearchAll)

    Set oAnalysisImages = oAnalysisSet.AnalysisImages
    Set oAnalysisImage = oAnalysisImages.Item("Von Mises Stress (nodal values).1")
    'Modify current occurrence of Image Von Mises Stress (nodal values)
```
    '==================================================================
```

```

    oAnalysisImage.SetCurrentOccurrence 4
    oAnalysisImage.Update

```

```vbscript
```vbscript
    End Sub

```
```
