---
title: "Untitled"
category: "use-case"
module: "CAAScdAniUseCases"
tags: ["CAAScrBase", "CATIA", "CAAScdAniUseCases", "CAAAniPostProOccurrence"]
source_file: "Doc/online/CAAScdAniUseCases/CAAAniPostProOccurrenceSource.htmmd"
converted: "2026-05-11T11:27:02.563972"
---

' COPYRIGHT DASSAULT SYSTEMES 2000

' ***********************************************************************
'   Purpose:      To Change the occurrence of an image
'   Assumptions:   Frequency case is computed with at least 4 occurrences
'   Author:       bmw
'   Languages:    VBScript
'   Locales:      English 
'   CATIA Level:  V5R16
' ***********************************************************************

```cpp
Sub CATMain(#)
' ----------------------------------------------------------- 
```
' Optional: allows to find the sample wherever it's installed
```cpp
  sDocPath=CATIA.SystemService.Environ("CATDocView")

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,"No Doc Path Defined"
    End If
```
' ----------------------------------------------------------- 

' Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, "online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis")
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)

' Retrieve the Analysis Manager
```
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis

' Retrieve the analysis model from the list of models
```
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

Set oAnalysisImages = oAnalysisSet.AnalysisImages
Set oAnalysisImage = oAnalysisImages.Item("Von Mises Stress (nodal values).1")

```

'Modify current occurrence of Image Von Mises Stress (nodal values)
'==================================================================
oAnalysisImage.SetCurrentOccurrence 4
oAnalysisImage.Update

```vbscript
End Sub

```

```cpp
&#39; COPYRIGHT DASSAULT SYSTEMES 2000

&#39; ***********************************************************************
&#39;   Purpose:      To Change the occurrence of an image
&#39;   Assumptions:   Frequency case is computed with at least 4 occurrences
&#39;   Author:       bmw
&#39;   Languages:    VBScript
&#39;   Locales:      English 
&#39;   CATIA Level:  V5R16
&#39; ***********************************************************************

```cpp
Sub CATMain(#)
&#39; ----------------------------------------------------------- 
```
&#39; Optional: allows to find the sample wherever it&#39;s installed
```cpp
  sDocPath=CATIA.SystemService.Environ(&quot;CATDocView&quot;)

    If (Not CATIA.FileSystem.FolderExists(sDocPath)) Then
      Err.Raise 9999,,&quot;No Doc Path Defined&quot;
    End If
```
&#39; ----------------------------------------------------------- 

&#39; Open the CATAnalysis Document
```cpp
sFilePath = CATIA.FileSystem.ConcatenatePaths(sDocPath, &quot;online/CAAScdAniUseCases/samples/Cube_R13_Freq.CATAnalysis&quot;)
Set oAnalysisDocument = CATIA.Documents.Open(sFilePath)
```
```

```vbscript
&#39; Retrieve the Analysis Manager
```vbscript
Set oAnalysisManager = oAnalysisDocument.Analysis
```
```

```vbscript
&#39; Retrieve the analysis model from the list of models
```vbscript
Set oAnalysisModels = oAnalysisManager.AnalysisModels
Set oAnalysisModel = oAnalysisModels.Item(1)
```
```

```vbscript
&#39; Retrieve the analysis cases and the first analysis case
```vbscript
Set oAnalysisCases = oAnalysisModel.AnalysisCases
Set oAnalysisCase = oAnalysisCases.Item(1)
```
```

```vbscript
&#39; Retrieve the analysis cases and the first analysis case
```vbscript
Set oAnalysisSets = oAnalysisCase.AnalysisSets
Set oAnalysisSet = oAnalysisSets.Item(&quot;Frequency Case Solution.1&quot;, catAnalysisSetSearchAll)

Set oAnalysisImages = oAnalysisSet.AnalysisImages
Set oAnalysisImage = oAnalysisImages.Item(&quot;Von Mises Stress (nodal values).1&quot;)

```

&#39;Modify current occurrence of Image Von Mises Stress (nodal values)
&#39;==================================================================
oAnalysisImage.SetCurrentOccurrence 4
oAnalysisImage.Update

```vbscript
End Sub
```
```